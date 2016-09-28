// YbGdDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "YbGdDlg.h"
#include "comobj.h"
#include "DObj.h"
#include "bclass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// YbGdDlg dialog


YbGdDlg::YbGdDlg(CWnd* pParent /*=NULL*/)
	: CDialog(YbGdDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(YbGdDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	r_sf=NULL;
	r_ph=NULL;
	r_yb=NULL;
	r_fsh=NULL;
	

	sfsum=0;
	phsum=0;
	ybsum=0;
	fssum=0;

	allupdate=0;
	t1=0;
	t2=0;
	mbg.Create(1,1);
	msr.Create(1,1);
	dbm.msr=&msr;
	updatergn=NULL;
}

YbGdDlg::~YbGdDlg()
{
	KillTimer(101);
	KillTimer(103);
	if(updatergn!=NULL) DeleteObject(updatergn);
	updatergn=NULL;
	FreeMem(); //释放内存

}

void YbGdDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(YbGdDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(YbGdDlg, CDialog)
	//{{AFX_MSG_MAP(YbGdDlg)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// YbGdDlg message handlers

BOOL YbGdDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetTimer(101,500,NULL);	  //动画和滚动文本定时
	SetTimer(103,5000,NULL);  //自动刷新数据
	return TRUE;  
}

void YbGdDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	wx=cx;
	wy=cy;
	srt=CRect(0,0,wx,wy);
	if(cx>10&&cy>10) //开始运行时低于10*10的窗口大小不运行以下函数
	{	
		mbg.SizeChange(cx,cy);
		msr.SizeChange(cx,cy);
		ShowA(mbg);
		CreateAllrgn();
	}
}

void YbGdDlg::OnPaint() 
{
	CRect rt;
	CPaintDC dc(this);
	rt=srt;
	msr.CopyDIB(mbg);
	dbm.ShowAct(msr,0,0,rt);
	msr.BitBlt(dc.m_hDC,rt);

}

void YbGdDlg::OnTimer(UINT nIDEvent) 
{
	HDC hdc;
	if(!IsWindowVisible()) return;
	hdc=::GetDC(m_hWnd);
	switch(nIDEvent)
	{
	case 101:
		if(SetDynMeter()) ShowDynObj(hdc);
		break;
	case 103:
		UpdateAllData();
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

//打开一个文件
void YbGdDlg::OPenFile(char *filename,int picno)
{
	char fnm[256];
	cobj.SetToLocalFile(filename,fnm);
	if(dbm.CheckFileIndex(fnm,picno))
	{
		FreeMem(); //释放内存
		dbm.OpenPwFile(fnm,picno);
		InitMoveObj();
		return;
	}
}


//释放资源
void YbGdDlg::FreeMem() //释放内存
{
	int i;

	if(phsum!=0) delete []r_ph;
	if(ybsum!=0) delete []r_yb;
	
	r_ph=NULL;
	r_yb=NULL;	
	
	phsum=0;
	ybsum=0;
	

	//释放自助控件
	for(i=0;i<sfsum;i++){
		
	   if(r_sf[i].stl->hwnd!=NULL&&r_sf[i].stl->hinst!=NULL&&
		   r_sf[i].stl->DfClose!=NULL)
	   {
			 ::SendMessage(r_sf[i].stl->hwnd,WM_CLOSE,0,0);
			 r_sf[i].stl->DfClose(r_sf[i].stl->rc);
			 r_sf[i].stl->hwnd=0;
			 r_sf[i].stl->rc=0;
		 }
	   if(r_sf[i].stl->hinst!=NULL){
		    if(r_sf[i].stl->hmenu!=NULL) DestroyMenu(r_sf[i].stl->hmenu);
 			FreeLibrary(r_sf[i].stl->hinst);
			r_sf[i].stl->hinst=0;
			r_sf[i].stl->hmenu=NULL;
	   }
	};

	if(sfsum!=0) delete []r_sf;
	r_sf=NULL;
	sfsum=0;

	//释放flash控件
	for(i=0;i<fssum;i++)	r_fsh[i].fshw.DestroyWindow();
	if(fssum>0) delete []r_fsh;
	r_fsh=NULL;
	fssum=0;
}

void YbGdDlg::InitMoveObj()
{
	int   objsum[100];			
	dbm.TJObjSum(objsum);

	//返回需要处理的活动对象
	ybsum=objsum[67];				//仪表
	if(ybsum>0) r_yb=new RMETER[ybsum];
	phsum=objsum[75];
	if(phsum>0) r_ph=new RPUSH[phsum];	//按钮
	sfsum=objsum[76];
	if(sfsum>0) r_sf=new RSELFCTL[sfsum];//自助控件
	fssum=objsum[81];
	if(fssum>0) r_fsh=new RFLASH[fssum];//FLASH对象
	dbm.page.head.type=0;
	
	//将动态点连接过来
	GetObjFromDbm();
	
	dbm.lookdown=0;
	dbm.curang=0;
	dbm.scf.showrev=0;
	SetFirstPosition();
	Set3DEnv();//设置3D环境
	///////////////////////
	
	UpdateAllData();
	EndShow();
}


bool YbGdDlg::UpdateAllData()
{
	bool b=false;
	if(!cobj.dbok) return false;
	if(t2==1) return false;
	t2=1;
	b=UpDateMeter();
	//数据变化后的处理
	if(b==true)
	{
		allupdate=1;
	}
	t2=0;
	return  b;
}


//从库中提取数据
void YbGdDlg::GetObjFromDbm()
{
	CRect rt;
	char fnm[256];
	N_layer *clay;
	R_FLW rfw;
	int i,j, csft,cpsh,cyb,cfsh;
	csft=0;	cpsh=0;	cyb=0;  cfsh=0;
	rfw.ele=1;
	//设置自助控件菜单为0/////////////////////////
	dbm.cmsum=0;					//当前应用总数
	dbm.popsum=0;					//弹出菜单个数
	//////////////////////////////////////////////
	for(i=0;i<dbm.page.laysum;i++)
	{
	  clay=&dbm.page.layer[i];
	  for(j=0;j<clay->objnum;j++)
	  {
		switch(clay->obj[j].attr.type)
		{
		case 67:
			r_yb[cyb].bs=&clay->obj[j];
			r_yb[cyb].mtr=(N_ELEGRPYB *)r_yb[cyb].bs->buf;
			r_yb[cyb].rt=r_yb[cyb].bs->ort;
			memset(r_yb[cyb].recno,0,4*6);
			cyb++;
			break;
		case 75:
			r_ph[cpsh].bs=&clay->obj[j];
			r_ph[cpsh].rt=clay->obj[j].ort;
			r_ph[cpsh].psh=(N_PUSH*)clay->obj[j].buf;
			cpsh++;
			break;
        case 76:
			r_sf[csft].bs=&clay->obj[j];
			r_sf[csft].rt=clay->obj[j].ort;
			r_sf[csft].rt.GetRECT(rt);
			r_sf[csft].sid=clay->obj[j].attr.ID;
			r_sf[csft].cansize=1;
			r_sf[csft].stl=(N_SELFCTL*)clay->obj[j].buf;
			//调入模块
			r_sf[csft].bs->InitSelfCtl();
			if(r_sf[csft].stl->hinst!=NULL&&r_sf[csft].stl->DfInit!=NULL){ 
				r_sf[csft].stl->rc=r_sf[csft].stl->DfInit(m_hWnd,r_sf[csft].stl->hwnd,
					rt,r_sf[csft].stl->id,r_sf[csft].stl->style,r_sf[csft].stl->lkbuf);
				}
				else r_sf[csft].stl->hwnd=NULL;
			GetSflRunParam(r_sf[csft].swp,r_sf[csft]);
			//准备菜单			
			if(r_sf[csft].stl->hmenu!=NULL)
				dbm.SetChildMenu(r_sf[csft].stl->hwnd,r_sf[csft].stl->hmenu);
			/////////////////////
			csft++;
			break;
		case 81:
			clay->obj[j].ort.GetRECT(r_fsh[cfsh].rt);
			r_fsh[cfsh].fsh=(N_FLASH*)clay->obj[j].buf;
			r_fsh[cfsh].fshw.Create("",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,130+cfsh);
			cobj.SetToLocalFile(r_fsh[cfsh].fsh->fname,fnm);//找到文件
			r_fsh[cfsh].fshw.SetMovie(fnm);
			if(r_fsh[cfsh].fsh->playmode==1) r_fsh[cfsh].fshw.SetLoop(TRUE);
			cfsh++;
			break;
		 };
	   }
	};
}

//调整第一次的位置
void YbGdDlg::SetFirstPosition()
{
	dbm.scf.lmd=0;
	dbm.lookdown=0;
	dbm.curang=0;
	dbm.scf.showrev=0;
	dbm.curzoom=1;
	dbm.zw=dbm.page.head.width;
	dbm.zh=dbm.page.head.height;
	//调整自助控件的窗口大小
	ChangeAllSft();
}

//设置3D环境参数
void YbGdDlg::Set3DEnv()
{
	msr.Set3DEnv(dbm.curang,dbm.zw,dbm.zh,dbm.lookdown);//设置3D环境
	mbg.Set3DEnv(dbm.curang,dbm.zw,dbm.zh,dbm.lookdown);//设置3D环境
}

//操作结束时的显示
void YbGdDlg::EndShow()
{
	CRect rt;
	HDC hdc=::GetDC(m_hWnd);
	rt=srt;
	//将对象显示到背景上
	ShowA(mbg);
	//再显示3D对象
	msr.CopyDIB(mbg);
	dbm.ShowAct(msr,0,0,rt);
	msr.BitBlt(hdc,rt);
	::ReleaseDC(m_hWnd,hdc);
}

//刷新仪表
bool YbGdDlg::UpDateMeter()
{
	bool rtn=false;
	int i,k;
	YBDATA tmp;
	for(i=0;i<ybsum;i++)
	{
		for(k=0;k<r_yb[i].mtr->dbsum;k++)
		{
			memset(&tmp,0,sizeof(YBDATA));
			tmp.did=r_yb[i].mtr->dbs[k].did;
			if(tmp.did<0) continue;
			tmp.recno=r_yb[i].recno[k];
			tmp.dtype=r_yb[i].mtr->dbs[k].dtype;
			tmp.vtype=r_yb[i].mtr->dbs[k].xsmode;
			rrd.ReadYbData(tmp);
			r_yb[i].recno[k]=tmp.recno;
			rtn|=SetYbVal(r_yb[i].mtr[0],tmp,k);
		}
  	}
	return rtn;
}

void YbGdDlg::ChangeAllSft()
{
	int i;
	CRect rt;
	for(i=0;i<sfsum;i++){
	  if(r_sf[i].cansize==1)  ChangeCtlSize(srt,r_sf[i].swp);
	};
	//调整FLASH位置
	for(i=0;i<fssum;i++){
		rt=r_fsh[i].rt;
		if(r_fsh[i].fsh->align_left==1) rt.left=0;
		if(r_fsh[i].fsh->align_top==1)  rt.top=0;
		if(r_fsh[i].fsh->align_right==1) rt.right=wx;
		if(r_fsh[i].fsh->align_buttom==1) rt.bottom=wy;
		r_fsh[i].fshw.MoveWindow(rt);
	}
}

//基本图形显示到背景上，以便活动对象显示
void YbGdDlg::ShowA(CDIB&mdc)
{
	CRect rt;
	rt=srt;
	dbm.ShowBkgd(mdc,rt);
	dbm.ShowBgDbx(mdc,0,0,srt,0);
	dbm.ShowStatic(mdc,0,0,srt);
}


//按属性改变窗口的矩形
void YbGdDlg::ChangeCtlSize(CRect rtd,SUBW_PARAM&pas)
{
	int cdx,cdy,cx,cy;
	CRect rt;
	CDRect art;
	art=pas.rts;
	art.ActRtToScr(dbm.curzoom);
	art.GetRECT(rt);
	cdx=rtd.left;
	cdy=rtd.top;
	cx=rtd.Width();
	cy=rtd.Height();
	if(pas.left==1)		rt.left=0;
	if(pas.top==1)		rt.top=0;
	if(pas.right==1)	rt.right=cx;
	if(pas.bottom==1)	rt.bottom=cy;
	pas.rtw=rt;
	pas.rt=rt;
	if(pas.hwnd!=NULL) ::MoveWindow(pas.hwnd,(int)pas.rtw.left,(int)pas.rtw.top,
		 (int)pas.rtw.Width(),(int)pas.rtw.Height(),true);
}

//设置仪表值
bool YbGdDlg::SetYbVal(N_ELEGRPYB &yb,YBDATA &data,int j)
{
	bool rtn=false;
	if(j>7||j<0) return rtn;
	if(yb.umr[j].ptype==1) //使用读取的参数
	{
		yb.umr[j].vmax=data.vmax;
		yb.umr[j].vmin=data.vmin;
		yb.umr[j].val[0]=data.vmin1;
		yb.umr[j].val[1]=data.vmax1;
		yb.umr[j].val[2]=data.vmin2;
		yb.umr[j].val[3]=data.vmax2;
	}
	if(yb.newval[j]!=data.curval)
	{
		yb.newval[j]=data.curval;
		rtn=true;
	}
	return rtn;
}

void YbGdDlg::PaintShow(HDC hdc, CRect rt)
{
	int w,h;
	CRect rt1;
	rt1=rt;
	w=rt.Width();
	h=rt.Height();
	CRect rt2=CRect(0,0,w,h);
	mbg.BitBltRect(msr.m_hDC,rt,rt2);
	msr.BitBltRect(hdc,rt2,rt);
}

//设置动态仪表
bool YbGdDlg::SetDynMeter()
{
	bool rtn=false;
	int i,k,bz;
	float v1,v2,v3;
	for(i=0;i<ybsum;i++)
	{
		bz=0;
		for(k=0;k<r_yb[i].mtr->dbsum;k++)
		{
			v1=r_yb[i].mtr->newval[k];
			v2=r_yb[i].mtr->curval[k];
			if(v1==v2) continue;
			v3=v2-v1;
			v3=v3>0 ? v3:-v3;
			if(v3<0.01)
			{
				r_yb[i].mtr->curval[k]=r_yb[i].mtr->newval[k];
				
			}else{
				r_yb[i].mtr->curval[k]=(float)((r_yb[i].mtr->newval[k]+r_yb[i].mtr->curval[k])/2);
			}
			bz=1;
			rtn=true;
		}
		if(bz==1) r_yb[i].mtr->show=1;
  	}
	return rtn;
}

void YbGdDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int j;
	SetCapture();
	j=IsInPush(point);
	if(j>=0){
		r_ph[j].psh->down=1;
		ShowPush(j);
	}
	CDialog::OnLButtonDown(nFlags, point);
}

void YbGdDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int j;
	ReleaseCapture();
	j=IsInPush(point);
	if(j>=0)
	{
		r_ph[j].psh->down=0;
		ShowPush(j);
		RunPushCmd(j);
	}
	CDialog::OnLButtonUp(nFlags, point);
}


//查看属标是否在按钮中
int YbGdDlg::IsInPush(CPoint point)
{
	int i;
	CDPoint apt;
	apt.SetPOINT(point);
	apt.ScrPtToAct(1);
	for(i=0;i<phsum;i++)
	{
	  if(r_ph[i].rt.PtInRect(apt)) return i;
	}
	return -1;
}

//显示按钮
void YbGdDlg::ShowPush(int j)
{
	CRect rt;
	CDRect art;
	if(j<0||j>=phsum) return;
	CClientDC dc(this);
	r_ph[j].bs->ShowPush(dc.m_hDC,0,0);
}


//运行按钮命令
void YbGdDlg::RunPushCmd(int j)
{
	HWND hw;
	switch(r_ph[j].psh->cmdtype)
	{
	case 0: WinExec(r_ph[j].psh->command,SW_SHOW); break;
	case 1: //打开画面
		break;
	case 2: //发送CMD消息
		GetParent()->PostMessage(WM_COMMAND,r_ph[j].psh->cmdnum);
		break;
	case 3: 
		hw=GetSlfCtl(r_ph[j].psh->selfid);
		if(hw!=NULL) ::PostMessage(hw,WM_COMMAND,r_ph[j].psh->cmdnum,0);
		break;
	case 4: //退出程序
		break;
	case 5: //执行功能模块
		RunFunctModule(r_ph[j].psh->command);
		break;
	}
}

//返回自助控件的窗口
HWND YbGdDlg::GetSlfCtl(int id)
{
	int i;
	for(i=0;i<sfsum;i++)
	{
		if(id==r_sf[i].stl->id)
		{
			return r_sf[i].stl->hwnd;
		}
	};
	return NULL;
}


void YbGdDlg::CreateAllrgn()  
{
	Set3DEnv();//设置3D环境
	CreatePaintRgn(); //生成动态刷新区域，只有数据刷新时或环境变化时
}

void YbGdDlg::CreatePaintRgn()
{
	HRGN hrgn1=NULL;
	if(updatergn!=NULL) DeleteObject(updatergn);
	updatergn=NULL;
	hrgn1=DY_GetYBRgn(hrgn1,r_yb,ybsum,srt,0,0,1);
	updatergn=hrgn1;
	dbm.SignPaintObj(hrgn1,0,0);//标记需要刷新的对象
}

//int k1=0;

//显示动态对象
void YbGdDlg::ShowDynObj(HDC hdc)
{

	if(t1==1) return;
	if(allupdate==1) //被完全更新
	{
		ShowA(mbg);
		ShowC(hdc,srt);
		allupdate=0;
		return;
	}
	t1=1;
//	char p[100];
//	CClientDC dc(0);
	//HBRUSH hb=CreateSolidBrush(0xff);
	//刷新客户区
	if(updatergn!=NULL)
	{
		SaveDC(hdc);
		//FillRgn(hdc,updatergn,hb);
		SelectObject(hdc,updatergn);
		ShowC(hdc,updatergn);
		RestoreDC(hdc,-1);
		//sprintf(p,"k1=%d ",k1);
		//dc.TextOut(100,10,p);
		//k1++;
	}
	t1=0;
	//DeleteObject(hb);
}

void YbGdDlg::ShowC(HDC hdc,HRGN hrgn)
{
	int w,h;
	CRect rt,rt2;
	GetRgnBox(hrgn,rt);
	rt&=srt;
	w=rt.Width();
	h=rt.Height();
	rt2=CRect(0,0,w,h);
	OffsetRgn(hrgn,-rt.left,-rt.top);
	SaveDC(msr.m_hDC);
	SelectObject(msr.m_hDC,hrgn);
	mbg.BitBltRect(msr.m_hDC,rt,rt2);
	RestoreDC(msr.m_hDC,-1);
	OffsetRgn(hrgn,rt.left,rt.top);
	dbm.ShowAct(msr,0,0,rt);
	msr.BitBltRect(hdc,rt2,rt);
}

void YbGdDlg::ShowC(HDC hdc,CRect rtshow)
{
	int w,h;
	CRect rt,rt2;
	rt=rtshow;
	rt&=srt;
	w=rt.Width();
	h=rt.Height();
	rt2=CRect(0,0,w,h);
	mbg.BitBltRect(msr.m_hDC,rt,rt2);
	dbm.ShowAct(msr,0,0,rt);
	msr.BitBltRect(hdc,rt2,rt);
}

//分区发生变化通知到各控件
void YbGdDlg::AreaChange()
{
	int i,wparam;
	HWND hw;
	wparam=2072;
	for(i=0;i<sfsum;i++)
	{
		hw=r_sf[i].stl->hwnd;
		if(hw!=NULL) ::PostMessage(hw,WM_COMMAND,wparam,0);
	};
}