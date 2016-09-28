// ScadaWin.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "ScadaWin.h"
#include "comobj.h"
#include "middll.h"
#include "DObj.h"
#include "stflwdlg.h"
#include "sendlg.h"
#include "viewdev.h"
#include "math.h"
#include "CrossObj.h"
#include "bclass.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj  cobj;		//公共对象
extern char *usertype[];
extern CMainFrame* pFrame;

extern char *buff;

char *stypenm[]={"发电机","负荷","电容","两绕组变压器","三绕组变压器"};





//int mk1=0;

DWORD WINAPI ReadRLtData(LPVOID arg) //读取实时平台数据
{   
	/*CClientDC dc(0);
	char p[100];*/
	ScadaWin *swin;
	swin=(ScadaWin*)arg;
    for(;;){
	   /*sprintf(p,"mk1=%d",mk1);
	   dc.TextOut(10,10,p);
	   mk1++;*/
	   if(swin->dbm.hisplay==1) //读取历史
	   {
			swin->ReadHisData();
	   }
	   
	   swin->UpdateAllData();
	   SuspendThread(swin->hThread_rd);
	}
	return 0;   
}

/////////////////////////////////////////////////////////////////////////////
// ScadaWin

ScadaWin::ScadaWin()
{
	winmode=0;
	t1=0;
	t2=0;
	mbg.Create(1,1);
	msr.Create(1,1);
	dbm.msr=&msr;
	dx=0;
	dy=0;
	wx=0;
	wy=0;
	enabletimer=1;
	r_cl=NULL;
	r_st=NULL;	
	r_bs=NULL;
	r_pe=NULL;
	r_ba=NULL;
	r_an=NULL;
	r_da=NULL;  
	r_tm=NULL;
	r_am=NULL;
	r_sc=NULL;
	r_sf=NULL;
	r_fw=NULL;
	r_ph=NULL;
	r_at=NULL;
	r_yb=NULL;
	r_fsh=NULL;
	r_ppie=NULL;
	r_sen=NULL;
	r_rv=NULL;
	r_tr=NULL;
	r_rs=NULL;
	r_zn=NULL;
	r_n1=NULL;
	r_sw=NULL;
	r_mt=NULL;	//多行文本对象
	r_spe=NULL; //系统饼图
	
	spesum=0;
	mtsum=0;	//数量
	rssum=0;
	trsum=0;  
	rvsum=0;
	stsum=0;
	clsum=0;
	bssum=0;
	pesum=0;
	basum=0;
	ansum=0;
	dtsum=0;
	tmsum=0;
	amsum=0;
	scsum=0;
	sfsum=0;
	fwsum=0;
	phsum=0;
	atsum=0;
	ybsum=0;
	fssum=0;
	ppsum=0;
	sesum=0;
	znsum=0;
	n1sum=0;
	swsum=0;

	cursor=0;
	rcursor=0;
	dnbz=0;
	pb=NULL;
	dmsum=0; //断面数
	SetDgxParam();
	updatergn=NULL;

	hThread_rd=NULL;
	dwThreadID=0;
}

ScadaWin::~ScadaWin()
{
	
}


BEGIN_MESSAGE_MAP(ScadaWin, CWnd)
	//{{AFX_MSG_MAP(ScadaWin)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_SETCURSOR()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_MOUSEWHEEL()
	ON_COMMAND(IDC_VIEWDEV, OnViewdev)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDC_LOWZOOM, OnLowzoom)
	ON_COMMAND(1800, OnMainPage)
	ON_COMMAND(IDC_RESVJS, OnResvjs)
	ON_WM_DESTROY()
	ON_COMMAND_RANGE(39000,39500,OnCommandRange)
	ON_COMMAND(IDC_AVCOPT, OnAvcopt)
	ON_COMMAND(IDC_PQVOPT, OnPqvopt)
	ON_COMMAND(IDC_N12EFT, OnN12eft)
	ON_COMMAND(IDC_N12EFT3D, OnN12eft3d)
	ON_COMMAND(IDC_GENMSG, OnGenmsg)
	ON_COMMAND(IDC_TRANMSG, OnTranmsg)
	ON_COMMAND(IDC_SVOPT, OnSvopt)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

//ON_COMMAND_RANGE(39000,39500,OnCommandRange)
/////////////////////////////////////////////////////////////////////////////
// ScadaWin message handlers

BOOL ScadaWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}


int ScadaWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	//打开数据库(基本实时库)
	SetCurDbf(0);
	////////////低频震荡窗口///////////////////////////////////////
	lwin.rrd=&rrd;
	lwin.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,111);
	lwin.ShowWindow(SW_HIDE);
	///////////////////////////////////////////////////////////////
	dmwin.rrd=&rrd;
	dmwin.Create(IDD_DMDLG,this); 
	dmwin.ShowWindow(SW_HIDE); 
	///////////////////////////////////////////////////////////////
	//设置定时器
	SetTimer(101,UPDATETM,NULL);	  //动画和滚动文本定时
	SetTimer(102,1000,NULL);			  //时钟显示
	SetTimer(103,5000,NULL);		  //自动刷新数据
	SetTimer(104,1000,NULL);		  //历史回放
	//生成提示条
	twin.Create("","",WS_CHILD|WS_VISIBLE|WS_CLIPCHILDREN,CRect(0,0,1,1),this,110);
	twin.ShowWindow(SW_HIDE);
	hThread_rd =CreateThread (NULL,0,ReadRLtData,this,CREATE_SUSPENDED,&dwThreadID);

	//创建变压器监视窗口
	SvWnd=CreateSvigilWnd(this,TRUE);
	::GetWindowRect(SvWnd,&svcrt);
	::ShowWindow(SvWnd,SW_HIDE);
	int sw=GetSystemMetrics(SM_CXSCREEN);
	::MoveWindow(SvWnd,sw-svcrt.Width()-10,80,svcrt.Width(),svcrt.Height(),false);
	return 0;
}

void ScadaWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	srt=CRect(0,0,wx,wy);
	if(cx>10&&cy>10) //开始运行时低于10*10的窗口大小不运行以下函数
	{
		if(dbm.lookdown==1)
		{
			ToMyZm(1.15);
			CreateAllrgn();
		}
		else if(dbm.page.head.showbyrt==0) SetFirstPosition();
		else if(dbm.page.head.showbyrt==1) ComputShowByRt();
		
		mbg.SizeChange(cx,cy);
		msr.SizeChange(cx,cy);
		sct.ScrSizeChange(wx,wy);
		if(dbm.scf.showdgx==1&&dbm.page.head.type>0) sct.DrawDgxinMem(msr,dbm.curzoom,dx,dy);
		ShowA(mbg);
	}
}

void ScadaWin::OnPaint() 
{
	CRect *rt,rt1;
	RGNDATA *lp;
	int i,n,m,r,ks;
	CRgn rgn;
	rgn.CreateRectRgn(0,0,10,10);
	r=GetUpdateRgn( &rgn,FALSE);
	CPaintDC dc(this);
	ks=GetKeyState(VK_LCONTROL);
	if(r!=NULLREGION||r!=ERROR)
	{
		n=rgn.GetRegionData((LPRGNDATA)buff,65535);
		if(n!=ERROR||n!=NULLREGION)
		{
			lp=(RGNDATA*)buff;
			m=lp->rdh.nCount;
			rt=(CRect*)lp->Buffer;
			for(i=0;i<m;i++)
			{
				rt1=rt[i];
				if((ks<0||cursor==1)&&dnbz==1) Show(dc.m_hDC,rt1);
				else PaintShow(dc.m_hDC,rt1);
			}
		}
	}
	rgn.DeleteObject();
	dtupdate=1;   //时间更新标志
}


//操作结束时的显示
void ScadaWin::EndShow()
{
	CRect rt;
	HDC hdc=::GetDC(m_hWnd);
	rt=srt;
	//将对象显示到背景上
	ShowA(mbg);
	//再显示3D对象
	msr.CopyDIB(mbg);
	dbm.ShowAct(msr,dx,dy,rt);
	Show3DObj(msr,rt);//俯视图显示
	//dbm.ShowTy(msr,dx,dy,srt);
	if(dbm.curopzt==1) dbm.Showdms(msr,-rt.left+dx,-rt.top+dy,dms,dmsum,dmsrt);
	msr.BitBlt(hdc,rt);
	::ReleaseDC(m_hWnd,hdc);
}
      
//显示等高线
void ScadaWin::ShowDgx(CDIB&mdc)    
{
	if(dbm.scf.showdgx==0||dbm.page.head.type<1)  return;
	Set3DEnv();//设置3D环境
	sct.DrawDGX(mdc); 
}
 
    

void ScadaWin::Show(HDC hdc, CRect rt)
{
	int w,h;
	CRect rt1;
	rt1=rt;
	rt1.OffsetRect(-dx,-dy);
	w=rt.Width();
	h=rt.Height();
	CRect rt2=CRect(0,0,w,h);
	dbm.ShowBkgd(msr,rt1);
	dbm.MSDownShow(msr,dx,dy,rt);
	Show3DObjj(msr,rt);
	msr.BitBltRect(hdc,rt2,rt);
}

void ScadaWin::PaintShow(HDC hdc, CRect rt)
{
	int w,h;
	CRect rt1;
	rt1=rt;
	rt1.OffsetRect(-dx,-dy);
	w=rt.Width();
	h=rt.Height();
	CRect rt2=CRect(0,0,w,h);
	mbg.BitBltRect(msr.m_hDC,rt,rt2);
	dbm.ShowAct(msr,dx,dy,rt);
	if(dbm.curopzt==1) dbm.Showdms(msr,-rt.left+dx,-rt.top+dy,dms,dmsum,dmsrt);//显示断面潮流
	Show3DObj(msr,rt);
	msr.BitBltRect(hdc,rt2,rt);
}


//根据条件显示3D对象
void ScadaWin::Show3DObj(CDIB&mdc,CRect rt)
{
	int i;
	switch(dbm.scf.showrev)
	{
	case 1:		//发电机有功
		dbm.SHowRevBarP(mdc,rt,dx,dy,r_rv,rvsum);
		//ShowFuntTitle(mdc,rt,0);
		break;
	case 2:		//发电机无功
		dbm.SHowGenBarQ(mdc,rt,dx,dy,r_rv,rvsum);
		//ShowFuntTitle(mdc,rt,1);
		break;
	case 3:		//变压器有功
		dbm.ComputeTpzoom(r_tr,trsum,wy);
		dbm.SHowTranRevBarP(mdc,rt,dx,dy,r_tr,trsum);
		//ShowFuntTitle(mdc,rt,2);
		break;
	case 4:		//变压器温度柱图
		dbm.ComputeTptzoom(r_tr,trsum,wy);
		//ShowFuntTitle(mdc,rt,7);
		break;
	case 5: case 6:case 7://n-1故障排序
		dbm.SHowN1Bar(mdc,rt,dx,dy,r_n1,n1sum);
	    //ShowFuntTitle(mdc,rt,dbm.scf.showrev+3);
		break;
	case 8:					//开关SOE回放
		dbm.SHowSwtBar(mdc,rt,dx,dy,r_sw,swsum);
		break;
	case 9:					//短路电流
		dbm.ShowSwtSccBar(mdc,rt,dx,dy,r_sw,swsum);
		break;
	case 10:   //区域柱图
		dbm.SHowZoneBar(mdc,rt,dx,dy,r_pe,pesum);
		break;
	case 11:   //系统柱图
		dbm.SHowSpieBar(mdc,rt,dx,dy,r_spe,spesum);
		break;
	case 12:   //N1Eft柱图
		dbm.SHowN1EftBar(mdc,rt,dx,dy,r_n1,n1sum);
		break;
	} 
	if(dbm.scf.lmd!=0)
	{
		dbm.ComputeSenzomm(r_sen,sesum,wy);
		ShowSelFlag(mdc.m_hDC,dx,dy);
		dbm.SHowSenBar(mdc,rt,dx,dy,r_sen,sesum);
		i=sentype==0 ? 3:4;
		if(sentype>=0&&sentype<2)	ShowFuntTitle(mdc,rt,i);
	}
}

//简化3D图形
void ScadaWin::Show3DObjj(CDIB&mdc,CRect rt)
{
	if(dbm.lookdown==0) return;
	switch(dbm.scf.showrev)
	{
	case 1:
		dbm.SHowRevBarPj(mdc,rt,dx,dy,r_rv,rvsum);
		break;
	case 2:
		dbm.SHowGenBarQj(mdc,rt,dx,dy,r_rv,rvsum);
		break;
	case 3:
		dbm.ComputeTpzoom(r_tr,trsum,wy);
		dbm.SHowTranRevBarPj(mdc,rt,dx,dy,r_tr,trsum);
		break;
	case 4:
		dbm.ComputeTptzoom(r_tr,trsum,wy);
		dbm.SHowTranTBarj(mdc,rt,dx,dy,r_tr,trsum);
		break;
	case 5: case 6:case 7:
		dbm.SHowN1Barj(mdc,rt,dx,dy,r_n1,n1sum);
		break;
	case 8:
		dbm.SHowSwtBarj(mdc,rt,dx,dy,r_sw,swsum);
		break;
	case 9:
		dbm.ShowSwtSccBarj(mdc,rt,dx,dy,r_sw,swsum);
		break;
	case 10:
		dbm.SHowZoneBarj(mdc,rt,dx,dy,r_pe,pesum);
		break;
	case 11:   //系统柱图
		dbm.SHowSpieBarj(mdc,rt,dx,dy,r_spe,spesum);
		break;
	case 12:
		dbm.SHowN1EftBarj(mdc,rt,dx,dy,r_n1,n1sum);
		break;
	}
	if(dbm.scf.lmd!=0){
		dbm.ComputeSenzomm(r_sen,sesum,wy);
		ShowSelFlag(mdc.m_hDC,dx,dy);
		dbm.SHowSenBarj(mdc,rt,dx,dy,r_sen,sesum);
	}
}


//基本图形显示到背景上，以便活动对象显示
void ScadaWin::ShowA(CDIB&mdc)
{
	CRect rt;
	rt=srt;
	rt.OffsetRect(-dx,-dy);
	dbm.ShowBkgd(mdc,rt);
	dbm.ShowBgDbx(mdc,dx,dy,srt,0);
	ShowDgx(mdc);
	dbm.ShowStatic(mdc,dx,dy,srt);
	dbm.ShowPlatte(mdc);
	ShowDmDraw(mdc.m_hDC,dmpt,segsum,dmsdot);
}

void ScadaWin::ShowC(HDC hdc,HRGN hrgn)
{
	int i,w,h;
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
	dbm.ShowAct(msr,dx,dy,rt);
	for(i=0;i<atsum;i++)
	{
	   if(r_at[i].pt!=NULL&&r_at[i].ptsum!=0) ShowActObj(msr.m_hDC,-rt.left+dx,-rt.top+dy,i);
	}
	ShowSelFlag(msr.m_hDC,-rt.left+dx,-rt.top+dy);
	if(dbm.curopzt==1) dbm.Showdms(msr,-rt.left+dx,-rt.top+dy,dms,dmsum,dmsrt);
	msr.BitBltRect(hdc,rt2,rt);
}


void ScadaWin::ShowC(HDC hdc,CRect rtshow)
{
	int i,w,h;
	CRect rt,rt2;
	rt=rtshow;
	rt&=srt;
	w=rt.Width();
	h=rt.Height();
	rt2=CRect(0,0,w,h);
	mbg.BitBltRect(msr.m_hDC,rt,rt2);
	dbm.ShowAct(msr,dx,dy,rt);
	for(i=0;i<atsum;i++)
	{
		if(r_at[i].pt!=NULL&&r_at[i].ptsum!=0) 
		 ShowActObj(msr.m_hDC,-rt.left+dx,-rt.top+dy,i);
	}
	Show3DObj(msr,rt);//俯视图显示
	ShowSelFlag(msr.m_hDC,-rt.left+dx,-rt.top+dy);
	if(dbm.curopzt==1) dbm.Showdms(msr,-rt.left+dx,-rt.top+dy,dms,dmsum,dmsrt);
	msr.BitBltRect(hdc,rt2,rt);
}




void ScadaWin::DrawShow()
{
	CClientDC dc(this);
	Show(dc,CRect(0,0,wx+1,wy+1));
}


//计算镜头中心点
void ScadaWin::ComputZCenter()
{
	if(xmax<=0){
	  vx=(double)((-dx+wx/2)/dbm.curzoom);
	}else{
	  vx=(double)(dbm.page.head.width/(double)2);
	}
	if(ymax<=0){
	  vy=(double)((-dy+wy/2)/dbm.curzoom);
	}else{
	  vy=(double)(dbm.page.head.height/(double)2);	
	}
}

void ScadaWin::InitMoveObj(HISHMI *hmi,int mode)
{
	int   objsum[100];			
	enabletimer=0;
	dmsum=0;
	dbm.scf.lmd=0;
	dbm.lookdown=0;
	dbm.curang=0;
	cursor=0;
	rcursor=0;
	dbm.scf.showrev=0;
	dbm.TJObjSum(objsum);

	//返回需要处理的活动对象
	ansum=objsum[64];				//模拟量
	if(ansum!=0) r_an=new RANL[ansum];
	mtsum=objsum[84];				//模拟量
	if(mtsum!=0) r_mt=new RMTXT[mtsum];
	rssum=objsum[65];				//水库
	if(rssum!=0) r_rs=new RRES[rssum];
	stsum=objsum[66];				//状态量和设备
	if(stsum!=0) r_st=new RSTA[stsum];
	ybsum=objsum[67];				//仪表
	if(ybsum>0) r_yb=new RMETER[ybsum];
	spesum=objsum[68];
	if(spesum>0) r_spe=new RSPIE[spesum];
	n_spe=spesum;
	basum=objsum[69];				//棒图
	if(basum!=0) r_ba=new RBAR[basum];
	pesum=objsum[70];				//饼图
	if(pesum!=0) r_pe=new RPIE[pesum];
	n_pie=pesum;
	dtsum=objsum[71];
	if(dtsum>0) r_da=new ROBJ[dtsum];   //日期
	tmsum=objsum[72];
	if(tmsum>0) r_tm=new ROBJ[tmsum];	//时间
	amsum=objsum[73];
	if(amsum>0) r_am=new RAML[amsum];	//GIF动画
	scsum=objsum[74];
	if(scsum>0) r_sc=new RSCRTXT[scsum];//滚动文本
	phsum=objsum[75];
	if(phsum>0) r_ph=new RPUSH[phsum];	//按钮
	sfsum=objsum[76];
	if(sfsum>0) r_sf=new RSELFCTL[sfsum];//自助控件
	fwsum=objsum[77];				//潮流线 
	if(fwsum>0) r_fw=new RFLOW[fwsum];   
	clsum=objsum[78];				//连接线
	if(clsum!=0) r_cl=new RCONL[clsum];
	bssum=objsum[79];				//母线
	if(bssum!=0) r_bs=new RBUS[bssum];
	atsum=objsum[80];
	if(atsum>0) r_at=new RACTOBJ[atsum];//活动对象
	fssum=objsum[81];
	if(fssum>0) r_fsh=new RFLASH[fssum];//FLASH对象
	ppsum=objsum[82];
	if(ppsum>0) r_ppie=new RPPIE[ppsum];//百分饼图
	znsum=objsum[83];
	if(znsum>0) r_zn=new RZONE[znsum]; //区域

	if(sfsum!=0||fssum!=0) dbm.page.head.type=0;
	//将动态点连接过来
	GetObjFromDbm();

	if(dbm.dbzt==1) RegistHis();
	//为网络拓扑收集参数
	if(dbm.page.head.type>0) CollectDevice(); //是接线图或地理接线图
	//将需要俯视的元件分离出来
	GetRevSenSum();
	SetRRevSen();
	Order3dPos(); //计算位置
	oldsel=-1;

	GetDevSum();  //统计设备个数
	switch(mode)
	{
	case 0:
		dbm.ZoomPage(0);
		Set3DEnv();//设置3D环境
		SetFirstPosition();
		ComputZCenter();
		break;
	case 1:
		dx=hmi->dx;
		dy=hmi->dy;
		dbm.curzoom=hmi->zoom;
		dbm.scf.showdgx=hmi->showdgx;
		dbm.scf.showrev=hmi->showrev;
		dbm.scf.ctrtype=hmi->ctrtype;
		dbm.lookdown=hmi->lookdown;
		vx=hmi->vx;
		vy=hmi->vy;
		break;
	case 2:
		if(hmi->mode==0) break;
		dbm.curzoom=hmi->zoom;
		ComputMaxXY();
		dx=xmax/2;
		dy=ymax/2;
		ComputZCenter();
		break;
	}
	//重新计算页面大小
	ZoomChange();
	if(dbm.page.head.showbyrt==1)
	{
		ComputShowByRt();
	}
	//设置等高线参数
	SetDgxParam();
	SetContourParam();
	///////////////////////
	UpdateAllData();

	//允许定时器工作
	enabletimer=1;
	t2=0;
	///////////////////////////////////////////////////////////////
	dtupdate=1;
	if(dbm.page.head.type==0)
	{
		if(cobj.nwin!=NULL) cobj.nwin->ShowWindow(SW_HIDE);
	}
	if(cobj.nwin!=NULL) cobj.nwin->PageChange();
	SetStatusZoom();
	//EndShow();
	//CreateAllrgn();
	//启动刷新程序
	dbm.msdwn=0;
}


//设置等高线参数
void ScadaWin::SetContourParam()
{
	int i;
	CRect rt;
	switch(dbm.scf.ctrtype)
	{
	case 0:case 1:case 2:   //节点电压
		sct.csum=bssum>MAXCONTOUR ? MAXCONTOUR:bssum;
		for(i=0;i<bssum;i++)
		{
			r_bs[i].bs->ort.GetRECT(rt);
			sct.SetRectPos(rt,i);
		}     
		break;
	case 3:  //输电线
	case 5:  //输电线
		sct.csum=fwsum>MAXCONTOUR ? MAXCONTOUR:fwsum;
		for(i=0;i<fwsum;i++) sct.SetNPOINTPos(r_fw[i].flw->pt,r_fw[i].flw->ptsum,i);
		break;
	case 4:  //变压器
		sct.csum=trsum>MAXCONTOUR ? MAXCONTOUR:trsum;
		for(i=0;i<trsum;i++)
		{
			r_tr[i].bs->ort.GetRECT(rt);
			sct.SetRectPos(rt,i);
		}
		break;
	}
	sct.MemSetPb();
}

int kk=0;
//刷新数据
bool ScadaWin::UpdateAllData()
{
	bool b=false;
	if(!cobj.dbok) return false;
	if(t2==1) return false;
	t2=1;
	b|=UpDateAnl();
	b|=UpDateMttxt();
	b|=UpDateBar();
	UpDateAct();
	b|=UpDatePPie();
	b|=UpDatePie();
	b|=UpDateSysPie();
	b|=UpdateFlow();
	b|=UpdateBus();
	b|=UpdateStatus();
	b|=UpdateTranformer();
	b|=UpdateDmData();
	UpdateGifaml();
	UpDateMeter();
	//数据变化后的处理
	if(b==true)
	{
		if(dbm.scf.showdgx==1)	sct.DrawDgxinMem(msr,dbm.curzoom,dx,dy);
		nettp.CheckConlEle();
		allupdate=1;
	}
	t2=0;
	return  b;
}

//刷新模拟量
bool ScadaWin::UpDateAnl()
{
	int i;
	bool rtn=false;;
	READDEV ran; //模拟量参数
	for(i=0;i<ansum;i++)
	{
	  if(r_an[i].anl->vr.did<0) continue;
	  ran=r_an[i].anl->vr;
	  if(!rrd.ReadDevData(ran)) continue;
	  rtn|=r_an[i].bs->SetAnlVal(ran);
	}
	return rtn;
}

//刷新多行文本
bool ScadaWin::UpDateMttxt()
{
	int i;
	bool rtn=false;;
	READDEV ran; //模拟量参数
	for(i=0;i<mtsum;i++)
	{
	  if(r_mt[i].txt->did<0) continue;
	  ran.did=r_mt[i].txt->did;
	  ran.dtype=r_mt[i].txt->type;
	  ran.recno=r_mt[i].recno;
	  rrd.ReadDevData(ran);
	  if(ran.sta!=r_mt[i].txt->sta)
	  {
			r_mt[i].txt->sta=ran.sta;
			r_mt[i].recno=ran.recno;
			rtn=true;
	  }
	}
	return rtn;
}

//刷新棒图
bool ScadaWin::UpDateBar()
{
	float fnewval;
	int i,j;
	READDEV ran;
	bool rtn=false;
	for(i=0;i<basum;i++)
	{
		if(r_ba[i].bar->dsrc.xsmode>0)//存在动态断面信息
		{
			rrd.SortPreDm();//对预定义断面按负载排序
			break;
		}
	}
	rrd.SortPreDm();//对预定义断面按负载排序
	for(i=0;i<basum;i++)
	{
		if(r_ba[i].bar->dsrc.xsmode>0)//动态断面信息
		{
			rtn=rrd.GetDynPreDm(r_ba[i].bar->dsrc.xsmode,r_ba[i].bar);	
		}
		else //指定断面值
		{
			j=r_ba[i].bar->dsrc.did;
			if(j<0) continue;
			ran.recno=r_ba[i].recno;
			ran.did=j;
			ran.dtype=r_ba[i].bar->dsrc.dtype;
			rrd.ReadDevData(ran);
			r_ba[i].recno=ran.recno;
			r_ba[i].bar->max=ran.value[2];
			r_ba[i].bar->min=ran.value[3];
			fnewval=GetSingleVal(ran,r_ba[i].bar->dsrc.xsmode);
			if(fabs(r_ba[i].bar->rval.curval-fnewval)>0.01)
				rtn=true;
			r_ba[i].bar->rval.curval=fnewval;
		}
  	}
	return rtn;
}



//刷新仪表
void ScadaWin::UpDateMeter()
{
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
			SetYbVal(r_yb[i].mtr[0],tmp,k);
		}
  	}
}

//刷新活动对象
void ScadaWin::UpDateAct()
{
	int i,j;
	float val;
	READDEV ran;
	for(i=0;i<atsum;i++)
	{
		if(r_at[i].pt==NULL||r_at[i].ptsum==0) continue;
		if(r_at[i].act->runmode!=1) continue;
		j=r_at[i].act->dsrc.did;
		if(j<0) continue;
		ran.recno=r_at[i].recno;
		ran.did=j;
		ran.dtype=r_at[i].act->dsrc.dtype;
		rrd.ReadDevData(ran);
		r_at[i].recno=ran.recno;
		val=GetSingleVal(ran,r_at[i].act->dsrc.xsmode);
		if(r_at[i].curval!=(double)val)
		{
			r_at[i].curval=(double)val;
			ComputActRect(i);
		}
	}
}

//刷新饼图
bool ScadaWin::UpDatePie()
{
	bool rtn=false;
	int i,j;
	READDEV ran;
	for(i=0;i<pesum;i++){
		j=r_pe[i].pie->did;
		if(j<0) continue;
		ran.recno=r_pe[i].recno;
		ran.did=j;
		ran.dtype=0;
		ran.xsmode=r_pe[i].pie->type;
		if(rrd.ReadZoneAnl(ran))
		{
			r_pe[i].recno=ran.recno;
			if( r_pe[i].pie->pcur!=ran.value[0]||r_pe[i].pie->qcur!=ran.value[1]||r_pe[i].pie->maxv!=ran.value[2])
			{
				r_pe[i].pie->pcur=ran.value[0];
				r_pe[i].pie->qcur=ran.value[1];
				r_pe[i].pie->maxv=ran.value[2];
				rtn=true;
			}
		}
	}
	return rtn;
}

//刷新饼图
bool ScadaWin::UpDateSysPie()
{
	bool rtn=false;
	int i;
	PWSYSSUM val;
	double vmax;
	rrd.ReadPwSys(val);
	for(i=0;i<spesum;i++){
		if(memcmp(&val,&r_spe[i].pie->val,sizeof(PWSYSSUM))==0) continue;
		rtn=true;
		r_spe[i].pie->val=val;
		switch(r_spe[i].pie->type)
		{
		case 0: //系统发电
			r_spe[i].pie->num=3;
			vmax=val.GenMax;
			if(vmax==0) 
			{
				r_spe[i].pie->vl[0]=0;
				r_spe[i].pie->vl[1]=0;
				r_spe[i].pie->vl[2]=0;
				r_spe[i].pie->vl[3]=0;
				r_spe[i].pie->error=1; //错误数据
			}else{
				r_spe[i].pie->vl[0]=val.GenP/vmax;
				r_spe[i].pie->vl[1]=val.UpRes/vmax;
				r_spe[i].pie->vl[2]=val.StopP/vmax;
				r_spe[i].pie->vl[3]=val.DownRes/vmax;
				r_spe[i].pie->error=0;
			}
			break;
		case 1://系统负荷
			r_spe[i].pie->num=2;
			vmax=val.LoadMax;
			if(vmax==0) 
			{
				r_spe[i].pie->vl[0]=0;
				r_spe[i].pie->vl[1]=0;
				r_spe[i].pie->error=1; //错误数据
			}else{
				r_spe[i].pie->vl[0]=val.LoadP/vmax;
				r_spe[i].pie->vl[1]=1.00-r_spe[i].pie->vl[0];
				r_spe[i].pie->error=0;
			}
			break;
		}
		
	}
	return rtn;
}


//刷新百分饼图
bool ScadaWin::UpDatePPie()
{
	int i,j;
	float mv,cv;
	double p,q,ps;
	bool rtn=false;
	READDEV ran;
	for(i=0;i<ppsum;i++)
	{
		j=r_ppie[i].ppe->did;
		if(j<0) continue;
		ran.recno=r_ppie[i].recno;
		ran.did=j;
		ran.dtype=r_ppie[i].ppe->type+1;
		if(rrd.ReadDevData(ran))
		{
			r_ppie[i].recno=ran.recno;
			if(dbm.scf.ftype<4)
			{
				mv=ran.value[4];
				p=ran.value[0];
				q=ran.value[1];
				ps=sqrt(p*p+q*q);
				cv=(float)ps;//ran.value[0];

			}else{
				mv=ran.value[6];
				cv=ran.value[7];
			}
			if(r_ppie[i].ppe->maxv!=mv){
				r_ppie[i].ppe->maxv=mv;
				rtn=true;
			};
			if(r_ppie[i].ppe->curval!=cv)
			{
				r_ppie[i].ppe->curval=cv;
				rtn=true;
			};
			r_ppie[i].recno=ran.recno;
		}else{
			r_ppie[i].ppe->curval=0;
		}
	}
	return rtn;
}



//刷新潮流线数据
bool ScadaWin::UpdateFlow()
{
	bool bl,rtn=false;
	int i,j,k;
	READDEV  ran;
	k=dbm.scf.ctrtype;
	for(i=0;i<fwsum;i++)
	{
		j=r_fw[i].flw->did;

		if(j<0) continue;
		ran.recno=r_fw[i].recno;
		ran.did=j;
		ran.dtype=r_fw[i].flw->type+1; //交流或直流
		if(!rrd.ReadDevData(ran)){
		   if(k==3 || k==5) rtn|=sct.SetContourEnable(i);
		   memset(&r_fw[i].flw->vr,0,sizeof(READDEV));
		}else{
	  	  bl=SetFlowData(i,ran);
		  if((k==3 ||k==5)&&bl) SetAContourVal(i); //如果是3,设置输电线值
		  rtn|=bl;
		}
		r_fw[i].recno=ran.recno;
	}
	return rtn;
}


//刷新母线数据
bool ScadaWin::UpdateBus()
{
	bool bl,rtn=false;
	int i,j,k;
	READDEV ran;//用于读取母线电压
	ran.dtype=3;
	k=dbm.scf.ctrtype;
	for(i=0;i<bssum;i++)
	{
		bl=false;
		j=r_bs[i].bus->did;
		if(j<0) continue;
		//读入母线数据
		ran.recno=r_bs[i].recno;
		ran.did=j;
		if(!rrd.ReadDevData(ran))
		{
		  if(k<3) rtn|=sct.SetContourEnable(i);
		  memset(&r_bs[i].bus->vr,0,sizeof(READDEV));
		}else{
			
			if(memcmp(&r_bs[i].bus->vr,&ran,sizeof(READDEV))!=0)
			{
				memcpy(&r_bs[i].bus->vr,&ran,sizeof(READDEV));
		    	if(k<3) SetAContourVal(i);
				rtn=true;
			}
			r_bs[i].recno=ran.recno;
		}
		
	}
	return rtn;
}

void ScadaWin::ChangeShow()//wd
{
	//if(bShowProcessData == false)
	for (int i=0;i<stsum;i++)
	{
		r_st[i].recno = -1;
	}
	
	for (i=0;i<fwsum;i++)//潮流线
	{
		r_fw[i].recno=-1;
	}

	for (i=0; i<bssum; i++)//母线
	{
		r_bs[i].recno = -1;
	}

	for (i=0; i<trsum; i++)//变压器备用
	{
		r_tr[i].recno = -1;
	}

	for (i=0; i<swsum; i++)//开关
	{
		r_sw[i].recno = -1;
	}

}

//刷新组合图元的状态
bool ScadaWin::UpdateStatus()
{
	int i,k;
	bool rtn=false;
	READDEV ran;
	READDEV_STA tmp;
	N_ELEGRPA *elg;	
	k=0;
	for(i=0;i<stsum;i++)
	{
		elg=r_st[i].elg;
		if (elg->type == 2)
		{
			//TRACE("111");
			ran.dtype=100;//elg->subtype;
			ran.recno=r_st[i].recno;
			ran.did = r_st[i].elg->did;
			
			if(rrd.ReadDevData(ran))
			{ //读取成功后，保存数据
				r_st[i].recno=ran.recno;
				memcpy(&r_st[i].elg->vr, &ran, sizeof(READDEV));
			}
			else
				memset(&r_st[i].elg->vr,0,sizeof(READDEV));
			
		}

		if(r_st[i].elg->type!=1) continue;
		elg=r_st[i].elg;
		tmp.did=elg->did;
		if(tmp.did<0)			 continue;
		
		switch(elg->subtype)
		{
		case 0:case 2:case 6: case 10://开关或无模拟量装置
			tmp.subtype=elg->subtype;
			tmp.recno=r_st[i].recno;
			if(rrd.ReadStaData(tmp)){ //读取成功后，保存数据
				if(elg->vr.sta!=tmp.zt||elg->vr.ele!=tmp.ele)
				{
					elg->vr.sta=tmp.zt;
					elg->vr.ele=tmp.ele;
					rtn=true;
				}
				r_st[i].recno=tmp.recno;
			}else{
				memset(&r_st[i].elg->vr,0,sizeof(READDEV));
			
			}
			
			break;
		case 1:case 3:case 4:case 5: case 9: //有模拟量的装置
			ran.did=elg->did;
			ran.recno=r_st[i].recno;
			ran.dtype=cobj.TypeTran(2,elg->subtype); //转换成可读的类型
			if(ran.dtype==-1) break;
			if(rrd.ReadDevData(ran))
			{
				rtn|=r_st[i].bs->SetDevAnl(ran);
				r_st[i].recno=ran.recno;
			}else{
				memset(&r_st[i].elg->vr,0,sizeof(READDEV));
			}
			break;
		}
	}
	return rtn;
}

//刷新厂站数据
bool ScadaWin::UpdateStation()
{
	return true;
}


//刷新变压器数据
bool ScadaWin::UpdateTranformer()
{
	int i;
	bool rtn=false;
	N_ELEGRPA *elg;	
	READDEV ran;
	for(i=0;i<trsum;i++)
	{
		if(r_tr[i].elg->type!=1) continue;
		elg=r_tr[i].elg;
		if(elg->did<0) continue;
		

		switch(elg->subtype)
		{
		case 7:case 8:
			ran.did=elg->did;
			ran.recno=r_tr[i].recno;
			ran.dtype=cobj.TypeTran(2,elg->subtype); //转换成可读的类型
			if(ran.dtype==-1) break;
			if(rrd.ReadDevData(ran))
			{
				rtn|=r_tr[i].bs->SetDevAnl(ran,i);
				r_st[i].recno=ran.recno;
			}else{
				memset(&r_tr[i].elg->vr,0,sizeof(READDEV));
			}
			SetAContourVal(i);
			break;
		}
	}
	return rtn;
}



//刷新动画控制数据
void ScadaWin::UpdateGifaml()
{
	int i,j;
	READDEV_STA tmp;
	for(i=0;i<amsum;i++)
	{
		r_am[i].zt=1;
		r_am[i].enable=1;
		j=r_am[i].ngf->dsrc.did;
		if(j<0) continue;
		tmp.did=j;
		switch(r_am[i].ngf->dsrc.dtype)
		{
		case 0: //发电机
			tmp.subtype=1;
			break;
		case 1: //线路
			tmp.subtype=34;
			break;
		case 2: //直流线路
			tmp.subtype=35;
			break;
		case 3: //母线
			tmp.subtype=33;
			break;
		case 4: //负荷
			tmp.subtype=3;
			break;
		}
		tmp.recno=r_am[i].recno;
		rrd.ReadStaData(tmp);
		r_am[i].zt=tmp.zt;
		r_am[i].enable=1;
		r_am[i].recno=tmp.recno;
	}
}

void ScadaWin::CreateAllrgn()  
{
	dbm.CreateFlwRgn(r_fw,fwsum); //潮流线
	dbm.CreateResRgn(r_rs,rssum); //水库
	if(dbm.lookdown==1)
	{
		switch(dbm.scf.showrev)          
		{
		case 1:case 2: 
			dbm.ComputePqZoom(r_rv,rvsum,wy);
			dbm.CreateRevRgn(r_rv,rvsum);
			break;
		case 3:
			dbm.ComputeTpzoom(r_tr,trsum,wy);
			dbm.CreateTranRevRgn(r_tr,trsum);
			break;
		case 4:
			dbm.ComputeTptzoom(r_tr,trsum,wy);
			dbm.CreateTranTRgn(r_tr,trsum);
			break;
		case 5: case 6:case 7:
			ComputeN1Zoom(r_n1,n1sum,dbm.n1zm,wy);
			dbm.CreateN1Rgn(r_n1,n1sum);
			break;
		case 8://开关SOE
			dbm.CreateSwtRgn(r_sw,swsum);
			break;
		case 9://开关短路电流
			dbm.CreateSwtSccRgn(r_sw,swsum);
			break;
		case 10: //区域柱图
			dbm.ComputeZnZoom(r_pe,pesum,wy);
			dbm.CreateZnRgn(r_pe,pesum);
			break;
		case 11://系统柱图
			dbm.CreateSPieRgn(r_spe,spesum);
			break;
		case 12:
			ComputeN1Zoom(r_n1,n1sum,dbm.n1zm,wy);
			dbm.CreateN1EftRgn(r_n1,n1sum);
			break;

		}
		if(dbm.scf.lmd==1)  dbm.CreateSenRgn(r_sen,sesum);
	}
	CreatePaintRgn(); //生成动态刷新区域，只有数据刷新时或环境变化时
}





BOOL ScadaWin::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(nHitTest == HTCLIENT)
	 {
		switch(cursor)
		{
		case 1:  SetCursor(cobj.hcur[0]);	return TRUE;
		case 2:  SetCursor(cobj.hcur[1]);	return TRUE;
		case 3:  SetCursor(cobj.hcur[2]);	return TRUE;
		case 4:  
		case 5:	 SetCursor(cobj.hcur[3]);	return TRUE;
		case 6:  case 9:
				 SetCursor(cobj.hcur[4]);	return TRUE;
		case 7:  SetCursor(cobj.hcur[7]);	return TRUE;
		case 8:  SetCursor(cobj.hcur[8]);	return TRUE;
		case 10: SetCursor(cobj.hcur[9]);	return TRUE;
		case 11: SetCursor(cobj.hcur[10]);	return TRUE;
		case 12: SetCursor(cobj.hcur[7]);	return TRUE;
		};
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}

void ScadaWin::OnTimer(UINT nIDEvent) 
{
	HDC hdc;
	if(!IsWindowVisible()) return;  //窗口不可见直接返回，定时器无效
	if(enabletimer==0) return;
	hdc=::GetDC(m_hWnd);
	switch(nIDEvent)
	{
	case 101:
		SetDynMeter();
		ShowDynObj(hdc); //正常时的动态显示
		break;
    case 102:
		Showdtime(hdc);
		CheckPopTips();  //提示条驱动
		break;
	case 103:			 //自动刷新数据(5秒定时器)
		if(dbm.hisplay==0&&dnbz==0&&dbm.curopzt!=5)
		{
			ResumeThread(hThread_rd);
		}
		break;
	case 104:  //历史播放
		if(dbm.hisplay==1&&dnbz==0) PlayHis(); //播放历史数据
		if(dbm.hisplay==2&&dnbz==0) PlaySoe(); //播放SOE
		break;
	}
	::ReleaseDC(m_hWnd,hdc);
	CWnd::OnTimer(nIDEvent);
}

void ScadaWin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	SuspendThread(hThread_rd);
	if(twin.IsWindowVisible()) twin.ShowWindow(SW_HIDE);
	//////////////保存压下前的状态////////////////////
	dzoom=dbm.curzoom;			
	ddx=dx;
	ddy=dy;			
	dangle=dbm.curang;	
	dlk=dbm.lookdown;
	//////////////////////////////////////////////////
	
//	if(cursor!=0)
//	{
		enabletimer=0;
		dnbz=1;
		dbm.msdwn=1;
//	}
	MouseLBDown(point);
	//SetFocus();
	CWnd::OnLButtonDown(nFlags, point);
}

//鼠标左键按下
void ScadaWin::MouseLBDown(CPoint point)
{
	int j,ks;
	pt1=point;
	pt2=point;
	oldpt=point;
	oldrt=CRect(0,0,0,0);
	oldang=dbm.curang;
	SetCapture();
	ks=GetKeyState(VK_LCONTROL);
	if(ks<0)
	{
		DrawShow();
		return;
	}
	//先察看是否在按钮上
	switch(cursor)
	{
	case 2: //局部放大
		DrawXorRect(CRect(pt1,pt2)); 
		break;
	case 6:  case 7: case 8: case 9: case 11:
		polysum=0;
		oldpt=point;
		AddPoint(point);
		break;
	case 1:case 3:
		DrawShow();
		break;
	default:
		j=IsInPush(point);
		if(j>=0){
			r_ph[j].psh->down=1;
			ShowPush(j);
		break;
		}
	}
}

void ScadaWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	enabletimer=1;
	dbm.msdwn=0;
	MouseLBUp(point);
	allupdate=0;
	t2=0;
	CWnd::OnLButtonUp(nFlags, point);
}

//鼠标左键放开
void ScadaWin::MouseLBUp(CPoint point)
{
	int j;
	CRect rt;
	ReleaseCapture();
	pt2=point;
	switch(cursor)
	{
	case 6: case 9://统计断面潮流，用户自定义断面
		AddDmPt();
		break;
	case 7:case 8:
		ComputSen();
		break;
	case 10:
		Order3dPos(); //计算位置
		break;
	case 5: //正常光标时
		j=IsInPush(point);
		if(j<0) break;
		r_ph[j].psh->down=0;
		ShowPush(j);
		RunPushCmd(j);
		break;
	case 2: //局部放大
		rt=CRect(pt1,pt2);
		rt.NormalizeRect();
		rt.OffsetRect(-dx,-dy);
		DrawXorRect(CRect(0,0,0,0));
		PartZoom(rt);
		break;
	case 12: //短路电流计算
		ComputScc();
		break;
	}  
	dnbz=0;
	if(NeedDrawDgx())  sct.DrawDgxinMem(msr,dbm.curzoom,dx,dy);
	EndShow();
	CreateAllrgn();
	ResumeThread(hThread_rd);

}

void ScadaWin::OnMouseMove(UINT nFlags, CPoint point) 
{
	int ks;
	cursor=GetCursor(point);
	MouseOnPush(nFlags,point);
	ks=GetKeyState(VK_LCONTROL);

	if(ks<0||cursor==1) MovePic(point);
	else MouseMove(point);
	CWnd::OnMouseMove(nFlags, point);
}

//滚轮操作
BOOL ScadaWin::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	/*double oldz;
	int mode;
	oldz=dbm.curzoom;
	mode=0;
	if(zDelta>0)  //拖动放大
	{
		dbm.ZoomPage(1);
		mode=1;
	}else{//拖动缩小
		dbm.ZoomPage(2);
		mode=2;
	}
	if(oldz!=dbm.curzoom){
		ZoomChange(); //放大后的计算
		EndShow();
		CreateAllrgn();
	}
	SetStatusZoom();*/
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}

void ScadaWin::OnViewdev() 
{
	int type;
	char p[100];
	CViewDev dlg;
	dlg.rrd=&rrd;
	type=cobj.TypeTran(seltype,selsubtype);
	if(type==-1)
	{
		sprintf(p,"名称=%s  标识id=%d",selid,dsjlh);
		MessageBox(p,"设备信息");
		return;
	}
	if(!dlg.SetParam(type,selid,dsjlh))
	{
		sprintf(p,"设备:\n %s id:%d在数据库中不存在",selid,dsjlh);
		MessageBox(p,"错误",MB_ICONSTOP);	
		return;
	}
	//显示数据
	dlg.DoModal();
}


void ScadaWin::OnCommandRange(UINT id)
{
	HWND hwnd;
	int  wparam;
	if(id<39300)
	{
		CloseLowfWin();
		cobj.GoToCMDPage(id);
		return;
	}
	if(id>=39300&&id<=39500)
	{
		if(dbm.GetChildSendMsg(id,wparam,hwnd))//有该ID
		{ 
			::SendMessage(hwnd,WM_COMMAND,wparam,0);
 		}
	}
}

void ScadaWin::OnMainPage()
{
	CloseLowfWin();
	cobj.Mainpage(false);
}



void ScadaWin::CreatePaintRgn()
{
	HRGN hrgn,hrgn1=NULL;
	if(updatergn!=NULL) DeleteObject(updatergn);
	updatergn=NULL;
	if(dbm.lookdown==0)
	{
		hrgn1=DY_GetActObjRgn(hrgn1,r_at,atsum,dx,dy,dbm.curzoom);
		hrgn1=DY_GetScrtxtRgn(hrgn1,r_sc,scsum,srt,dx,dy,dbm.curzoom);
		hrgn1=DY_GetYBRgn(hrgn1,r_yb,ybsum,srt,dx,dy,dbm.curzoom);
		hrgn1=DY_GetGifAmlRgn(hrgn1,r_am,amsum,srt,dx,dy,dbm.curzoom);
		hrgn1=DY_GetGenRgn(msr,hrgn1,r_rv,rvsum,srt,dx,dy,dbm.scf.gendyn,dbm.curzoom);
	}
	//再看潮流线
	if(dbm.curopzt==3) hrgn=GetLowUpdateRgn();
	else hrgn=GetFlowUpdateRgn();
	if(hrgn!=NULL) hrgn=GetLookDownRgn(hrgn);
	if(hrgn!=NULL) OffsetRgn(hrgn,dx,dy);
	if(hrgn==NULL&&hrgn1==NULL)
	{
		dbm.SignPaintObj(hrgn1,dx,dy);//标记需要刷新的对象	
		return;
	}
	if(hrgn1==NULL) hrgn1=CreateRectRgn(0,0,1,1);
	CombineRgn(hrgn1,hrgn1,hrgn,RGN_OR);
	DeleteObject(hrgn);
	hrgn=CreateRectRgn(0,0,wx,wy);
	CombineRgn(hrgn1,hrgn1,hrgn,RGN_AND);
	DeleteObject(hrgn);
	updatergn=hrgn1;
	dbm.SignPaintObj(hrgn1,dx,dy);//标记需要刷新的对象
}

//返回低频震荡需要刷新的区域
HRGN ScadaWin::GetLowUpdateRgn()
{
	int i;
	CRect rt,rt3;
	N_FLOW *flw;
	HRGN hrgn=NULL;
	for(i=0;i<fwsum;i++)
	{
		flw=r_fw[i].flw;
		//if(r_fw[i].lfflag==0) continue;
		rt=r_fw[i].rt;
		rt3=srt;
		rt3.OffsetRect(-dx,-dy);
		rt&=rt3;
		if(!rt.IsRectEmpty())
		{
			if(hrgn==NULL)
			{
				hrgn=CreateRectRgn(0,0,1,1);
				CombineRgn(hrgn,r_fw[i].hrgn,hrgn,RGN_COPY);
			}else CombineRgn(hrgn,hrgn,r_fw[i].hrgn,RGN_OR);
		}
	}
	return hrgn;
}

HRGN ScadaWin::GetFlowUpdateRgn()
{
	int i;
	CRect rt,rt3;
	N_FLOW *flw;
	HRGN hrgn=NULL;
	for(i=0;i<fwsum;i++)
	{
		flw=r_fw[i].flw;
		rt=r_fw[i].rt;
		rt3=srt;
		rt3.OffsetRect(-dx,-dy);
		rt&=rt3;
		if(!rt.IsRectEmpty())
		{
			if(hrgn==NULL){
				hrgn=CreateRectRgn(0,0,1,1);
				CombineRgn(hrgn,r_fw[i].hrgn,hrgn,RGN_COPY);
			}
			else CombineRgn(hrgn,hrgn,r_fw[i].hrgn,RGN_OR);
		}
	}

	return hrgn;
}


HRGN ScadaWin::GetLookDownRgn(HRGN oldrgn)
{
	int i;
	HRGN hrgn=oldrgn;
	if(dbm.lookdown==0) return hrgn;
	if(dbm.scf.lmd!=1)
	{
		switch(dbm.scf.showrev)
		{
		case 1:case 2:
			for(i=0;i<rvsum;i++) if(r_rv[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_rv[i].hrgn,RGN_DIFF);
			break;
		case 3: case 4:
			for(i=0;i<trsum;i++) if(r_tr[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_tr[i].hrgn,RGN_DIFF);
			break;
		case 5: case 6:case 7: case 12:
			for(i=0;i<n1sum;i++) if(r_n1[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_n1[i].hrgn,RGN_DIFF);
			break;
		case 8: case 9:
			for(i=0;i<swsum;i++) if(r_sw[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_sw[i].hrgn,RGN_DIFF);
			break;
		case 10:
			for(i=0;i<pesum;i++) if(r_pe[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_pe[i].hrgn,RGN_DIFF);
			break;
		case 11:
			for(i=0;i<spesum;i++) if(r_spe[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_spe[i].hrgn,RGN_DIFF);
			break;
		}
	}
	if(dbm.scf.lmd==1)
	{
		for(i=0;i<sesum;i++) if(r_sen[i].hrgn!=NULL) CombineRgn(hrgn,hrgn,r_sen[i].hrgn,RGN_DIFF);
	}
	return hrgn;
}



//鼠标移动
void ScadaWin::MouseMove(CPoint point)
{
	CPoint pt,ptt;
	CRect rt;
	if(dnbz==1){
     ptt=pt2;
	 pt2=point;
	 rt=CRect(pt1,pt2);
	 rt.NormalizeRect();
	 switch(cursor)
	 {
	 case 2: //局部放大
		DrawXorRect(rt);
		break;
	 case 3: //拖动放大
		ZoomInOut();		
		break;
	 case 10://旋转
		Rotate();
		break;
	 case 6: case 7: case 8: case 9: case 11: case 12:
		AddPoint(point);
        DrawStatArea();
		break;
	   }
	}
}

void ScadaWin::MovePic(CPoint point)
{
	int x,y;
	int oldx,oldy,sx,sy;
	if(dnbz!=1||(xmax>0&&ymax>0)) return;
	oldx=dx;
	oldy=dy;
	if(xmax<0)
	{
		x=point.x-pt1.x;
		dx+=x;
		dx=dx>0 ? 0:dx;
		dx=dx<xmax ? xmax:dx;
	}
	if(ymax<0)
	{
		y=point.y-pt1.y;
		dy+=y;
		dy=dy>0 ? 0:dy;
		dy=dy<ymax ? ymax:dy;
	}
	sx=dx-oldx;
	sy=dy-oldy;
	if(sx!=0||sy!=0)	ScrollWindow(sx,sy,srt,srt);
	pt1=point;
	ComputZCenter();
	if(cobj.nwin!=NULL) cobj.nwin->MoveCvs();
};





///////////////接收子窗口发来的消息，配合子窗口的动作///////////////////
//message=1200  
//wParam=1   返回当前的运行模式号
//		 2   取得兄弟控件的窗口句柄
//       3   找到文件地址，返回给调用程序
//		 4   返回当前时段
LRESULT ScadaWin::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	char tnm[256];
	if(message==1200)
	{
		switch(wParam)
		{
		case 1:
			return 0;//当前运行方式号
		case 2:
			return (int)GetSlfCtl((int)lParam);
		case 3:
			cobj.SetToLocalFile((char *)lParam,tnm);
			strcpy((char*)lParam,tnm);
			return true;
		case 4:    //返回启动目录
			strcpy((char*)lParam,cobj.startpath);
			return 0;
		}
	}
	return CWnd::WindowProc(message, wParam, lParam);
}


void ScadaWin::OnRButtonDown(UINT nFlags, CPoint point) 
{
	if(dbm.curopzt==1) DmFlowSwitch();
	else RButtonMenu(point);
	CWnd::OnRButtonDown(nFlags, point);
}


//点中设备弹出右键菜单的处理
void ScadaWin::RButtonMenu(CPoint point)
{
	CMenu *mm;
	CPoint pt;
	pt=point;
	lfpos=pt;
	ClientToScreen(&pt);
	//首先看N-1,N-2右键菜单
	if(dbm.scf.showrev>=5&&dbm.scf.showrev<=7&&cursor==4)
	{
		mm=cobj.pmenu.GetSubMenu(1); //弹参数修改菜单
		mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
		return;
	}
	//再查看区域饼图菜单
	if(seltype==13)
	{
		mm=cobj.pmenu.GetSubMenu(2); //弹参数修改菜单
		mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
		return;
	}
	//未选中设备后的弹出菜单
	if(seltype==255)  //弹出界面切换菜单
	{
		switch(winmode)
		{
		case 0:
			cobj.rmenu.TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
			return;
		case 1:
			mm=cobj.fmenu.GetSubMenu(0); //弹参数修改菜单
			if(dbm.page.head.type>0&&n_ge>0) mm->EnableMenuItem(IDC_GENREV,0);
			else mm->EnableMenuItem(IDC_GENREV,1);
			if(dbm.page.head.type>0&&(n_ge>0||n_sh>0)) mm->EnableMenuItem(IDC_GENREVQ,0);
			else mm->EnableMenuItem(IDC_GENREVQ,1);
			if(dbm.page.head.type>0&&n_tr>0) mm->EnableMenuItem(IDC_BYQWD,0);
			else mm->EnableMenuItem(IDC_BYQWD,1);
			if(dbm.page.head.type>0&&n_tr>0) mm->EnableMenuItem(IDC_TRANREV,0);
			else mm->EnableMenuItem(IDC_TRANREV,1);
			
			if(dbm.page.head.type>0) mm->EnableMenuItem(ID_ROTATE,0);
			else mm->EnableMenuItem(ID_ROTATE,1);
			if(dbm.page.head.type>0) mm->EnableMenuItem(ID_ZOOMIO,0);
			else mm->EnableMenuItem(ID_ZOOMIO,1);
			if(dbm.page.head.type>0) mm->EnableMenuItem(ID_MOVEPIC,0);
			else mm->EnableMenuItem(ID_MOVEPIC,1);
			if(dbm.page.head.type>0) mm->EnableMenuItem(IDC_SHOWDGX,0);
			else mm->EnableMenuItem(IDC_SHOWDGX,1);
			if(dbm.page.head.type>0) mm->EnableMenuItem(IDC_BASFLOW,0);
			else mm->EnableMenuItem(IDC_BASFLOW,1);

			if(mm!=NULL) mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,cobj.mwin);
			return;
		}
	}
	mm=cobj.pmenu.GetSubMenu(0); //弹参数修改菜单
	cursor=255;
	if(mm!=NULL)
	{
		if(SelIsTran()) mm->EnableMenuItem(IDC_AVCOPT,0);
		else mm->EnableMenuItem(IDC_AVCOPT,1);
		if(SelIsGen()) mm->EnableMenuItem(IDC_PQVOPT,0);
		else mm->EnableMenuItem(IDC_PQVOPT,1);
		if(SelIsTran()) mm->EnableMenuItem(IDC_SVOPT,0);
		else mm->EnableMenuItem(IDC_SVOPT,1);
		if(SelCanZoomLowF()) mm->EnableMenuItem(IDC_LOWZOOM,0);
		else mm->EnableMenuItem(IDC_LOWZOOM,1);
		if(seltype==6&&selsubtype==0) mm->EnableMenuItem(IDC_RESVJS,0);
		else mm->EnableMenuItem(IDC_RESVJS,1);
		if(seltype==2) mm->EnableMenuItem(ID_INPUTPARAM,0);
		else mm->EnableMenuItem(ID_INPUTPARAM,1);
		if(seltype==2) mm->EnableMenuItem(IDC_VIEWDEV,0);
		else mm->EnableMenuItem(IDC_VIEWDEV,1);
		mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
	}
}


bool ScadaWin::UpdateDmData()
{
	int i,j;
	bool rtn=false;
	double I,v,pcur,ps,p,q;
	READDEV  ran;
	if(dbm.curopzt!=1) return false;
	//读取断面潮流
	for(j=0;j<dmsum;j++)
	{
		I=0;
		pcur=0;
		for(i=0;i<dms[j].lsum;i++)
		{
			ran.recno=dms[j].ls[i].jlh;
			ran.did=dms[j].ls[i].id;
			ran.dtype=dms[j].ls[i].type+1; //交流或直流
			if(rrd.ReadDevData(ran))
			{
				v=ran.value[7];
				I+=v;
				p=ran.value[0];
				q=ran.value[1];
				ps=sqrt(p*p+q*q);//视在功率
				pcur+=ps;
			}
		}
		if(dms[j].Icur!=I)
		{
			dms[j].Icur=(float)I;
			rtn=true;
		}
		if(dms[j].Pcur!=pcur)
		{
			dms[j].Pcur=(float)pcur;
			rtn=true;
		}
	}

	return rtn;
}



//是否需要切换到低频震荡画面
void ScadaWin::TurnToLowF()
{
	int i;
	if(dbm.curopzt==3) return; //已经处于低频震荡
	//切换到低频震荡状态
	cobj.SetToNeedMode(6);
	//切换到低频震荡画面
	i=cobj.mwin->GetVWIndex(cobj.swin);
	if(i>=0) cobj.mwin->GoToPage(i);
}



//低频震荡放大
void ScadaWin::OnLowzoom() 
{
	int x,y;
	CRect rt;
	lwin.vpt=r_fw[seljlh].flw->fpt;
	lwin.vlen=r_fw[seljlh].flw->flen;
	lwin.sval=0;
	lwin.sfr=0;
	lwin.curtype=r_fw[seljlh].flw->type;
	lwin.curid=r_fw[seljlh].flw->did;
	strcpy(lwin.name,r_fw[seljlh].flw->dev_name);
	rt=CRect(lfpos.x,lfpos.y,lfpos.x+254,lfpos.y+144);
	x=wx-rt.right;
	y=wy-rt.bottom;
	x=x>0 ? 0:x;
	y=y>0 ? 0:y;
	rt.OffsetRect(x,y);
	lwin.SetFunct(2);
	lwin.MoveWindow(&rt);
}





void (WINAPI *TurnReservoir)(int id);

//水电发电计算
void ScadaWin::OnResvjs()
{
	HINSTANCE hinst;
	char name[256];
	cobj.SetToLocalFile("turnresv.dll",name);
	hinst=LoadLibrary(name);
	if(hinst==NULL)
	{
		MessageBox("turnresv.dll不存在，不能计算！");
		return;
	}
	(FARPROC&)TurnReservoir=GetProcAddress(hinst,"TurnReservoir");
	if(TurnReservoir!=NULL) TurnReservoir(dsjlh);
	FreeLibrary(hinst);
}


void ScadaWin::SetDgxParam()
{
	sct.SetCfg(dbm.scf.smooth,dbm.scf.oneline,dbm.scf.tranbg,dbm.scf.ctrtype,dbm.scf.cr);
}

void ScadaWin::FlowSel(int sel)
{
	if(dbm.scf.ftype!=sel)
	{
		dbm.scf.ftype=sel;
		dbm.SaveShowSet();
	}
	EndShow();
}





//注册所有设备历史回放
void ScadaWin::RegistHisAllDev()
{
	His_RegistFlow(r_fw,fwsum);
	His_RegistBus(r_bs,bssum);
	His_RegistDev(r_st,stsum);
}
//播放历史
void ScadaWin::PlayHis()
{
	dbm.hisjs++;
	if(dbm.hisjs>dbm.hspeed)
	{
		if(dbm.curtm>=dbm.hsum)
		{
			dbm.hisplay=0;
			return;
		}
		dbm.hisjs=0;
	}
	ResumeThread(hThread_rd);
}

//播放历史SOE
void ScadaWin::PlaySoe()
{
	dbm.curtm++;
	if(dbm.curtm>=dbm.soesum)
	{
		dbm.hisplay=0;
		return;
	}
	//设置一个值
	SetANewSoe(dbm.soe[dbm.curtm]);
	//显示
	cobj.ebar->SetNewDate(dbm.soe[dbm.curtm].tm,dbm.soe[dbm.curtm].ms);
	Order3dPos();
	CreateAllrgn();
	EndShow();

}

//读取历史数据
void ScadaWin::ReadHisData()
{
	time_t tm1,tm2;
	if(dbm.curtm<=dbm.hsum)
	{
		tm1=dbm.hlist[dbm.curtm];
		GetNextSection(tm1,tm2);
		SetCurHisDTime();
		dbm.curtm++;
	}
}

void ScadaWin::SetCurHisDTime()
{
	CTime tm;
	time_t tm1;
	if(dbm.curtm>=dbm.hsum) return;
	tm1=dbm.hlist[dbm.curtm];
	tm=CTime(tm1);
	cobj.hbar->SetDate(tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute(),tm.GetSecond());
}

void ScadaWin::RegistHis()
{
	//清除原注册
	ClearAllRegData();
	//注册本页面
	RegistHisAllDev();
	BeginGettingData();
}

void ScadaWin::OnDestroy() 
{
	enabletimer=0;
	TerminateThread(hThread_rd,0);
	CloseHandle(hThread_rd);
	//设置定时器
	KillTimer(101);	 //动画和滚动文本定时
	KillTimer(102);	 //时钟显示
	KillTimer(103);  //趋势显示
	KillTimer(104);		
	FreeMem();		 //释放内存
	////////////////////////
	if(pb!=NULL) delete pb;
	pb=NULL;
	if(updatergn!=NULL) DeleteObject(updatergn);
	CWnd::OnDestroy();
}

//打开一个文件
bool ScadaWin::FileOpen(char *filename,int pageno,HISHMI *hmi,int mode) 
{
	CloseLowfWin();
	allupdate=0;
	FreeMem();
	if(!dbm.OpenPwFile(filename,pageno))
	{
		MessageBox("文件不存在或打开了不识别的版本！\n请用格式转换工具转换。\n打开文件失败");
		return false;
	}
	InitMoveObj(hmi,mode);

	EndShow();
	CreateAllrgn();
	return true;
}

//察看选择的设备是否是变压器,发电机
bool ScadaWin::SelIsTran()
{
	if(seltype!=2) return false;
	if(selsubtype!=7&&selsubtype!=8) return false;
	if(seljlh<0) return false;
	return true;
}

//察看选择的设备是否是变压器,发电机
bool ScadaWin::SelIsGen()
{
	if(seltype!=2) return false;
	if(selsubtype!=1) return false;
	if(seljlh<0) return false;
	return true;
}

//变压器AVC监视
void ScadaWin::OnAvcopt() 
{
	int type,id;
	if(!SelIsTran()) return;
	type=selsubtype-6;
	if(seljlh<0||seljlh>=stsum) return;
	id=r_st[seljlh].elg->did;
	//ShowAVCPQVWnd(id,type,TRUE);//ZQ 2009.12.20 delete temp
}

//发电机PQV曲线监视
void ScadaWin::OnPqvopt() 
{
	int type,id;
	if(!SelIsGen()) return;
	type=3;
	if(seljlh<0||seljlh>=stsum) return;
	id=r_st[seljlh].elg->did;
	//ShowAVCPQVWnd(id,type,TRUE);//ZQ 2009.12.20 delete temp
}

void ScadaWin::SetCurFunction(FUN_STATUS newfun)
{
	m_PreFun=m_CurFun;	
	m_CurFun=newfun;
	cobj.funbar->ReDrawNewFt();
}

void ScadaWin::OnN12eft() 
{
	if(seljlh<0||seljlh>=n1sum) return;
	NT_ShowEffect(r_n1[seljlh].devid,r_n1[seljlh].type,dbm.dbzt==0 ? "visualpw":"studypw");
}

void ScadaWin::OnN12eft3d() 
{
	cobj.N12eft3d();
}

void ScadaWin::ReadN1EFT()
{
	int num,i,j;
	float v1,v2;
	N1Data data[100],td;

	int type=0;
	DWORD id=0;
	float fSec=0.0;
	char buff[32]={0};
	if(!GetN1Sel(id,type,fSec)) return;

	//清空原数据
	SetN1EftData(data,0);
	if(!rrd.Readn1Eft((DWORD)id,type,num,data,100)) return;
	data[0].val=fSec;//第一个是选中的设备，恢复原值
	for(i=0;i<num;i++)
	{
		v1=data[i].val;
		v1=v1<0 ? -v1:v1;
		for(j=i+1;j<num;j++)
		{
			v2=data[j].val;
			v2=v2<0 ? -v2:v2;
			if(v1>v2)
			{
				td=data[i];
				data[i]=data[j];
				data[j]=td;
				v1=v2;
			}
		}
	}

	//设置数据
	SetN1EftData(data,num);
}

bool ScadaWin::GetN1Sel(DWORD &dwID,int &type,float &fSec)
{
	if(seljlh<0||seljlh>=n1sum) return false;

	dwID=r_n1[seljlh].devid;
	type=r_n1[seljlh].type;
	fSec=r_n1[seljlh].vn1;
	return true;
}

void ScadaWin::SetN1EftData(N1Data *data,int num)
{
	int i,j,k,t;
	double a;
	for(j=0;j<n1sum;j++)
	{
		r_n1[j].vn1=0;//先置0
		r_n1[j].index=0;
		r_n1[j].selbz=0;
	}
	if(num==0) return;
	a=100/num;
	for(i=0;i<num;i++)
	{
		k=data[i].id;
		t=data[i].type;
		for(j=0;j<n1sum;j++)
		{
			if(k==r_n1[j].devid&&t==r_n1[j].type)
			{
				r_n1[j].vn1=data[i].val;
				r_n1[j].index=i+1;
				if(data[i].Group==1) r_n1[j].selbz=1;
				else r_n1[j].selbz=0;
				switch(t)//发电机//负荷//电容//两绕组变//三绕组变//母线//线路
				{
				case 0://发电机
					r_n1[j].color=dbm.scf.sencolor[0];
					break;
				case 1://双绕主变
					r_n1[j].color=dbm.scf.sencolor[3];
					break;
				case 2://三绕变
					r_n1[j].color=dbm.scf.sencolor[4];
					break;
				case 3://线路
					r_n1[j].color=dbm.scf.sencolor[6];
					break;
				case 4://负荷
					r_n1[j].color=dbm.scf.sencolor[1];
					break;
				case 5://电容
					r_n1[j].color=dbm.scf.sencolor[2];
					break;
				case 6://母线
					r_n1[j].color=dbm.scf.sencolor[5];
					break;
				}
				r_n1[j].Hbar=100+(int)(a*i);
				break;
			}
		}
	}
}

void ScadaWin::OnGenmsg() 
{
	int zid;
	//取分区ID
	if(seljlh<0||seljlh>=pesum) return;
	zid=r_pe[seljlh].pie->did;
	
	NT_Gen(zid);
}

void ScadaWin::OnTranmsg() 
{
	int zid;
	//取分区ID
	if(seljlh<0||seljlh>=pesum) return;
	zid=r_pe[seljlh].pie->did;
	NT_Tfm(zid);
}

void ScadaWin::OnSvopt() 
{
	int type,id;
	if(!SelIsTran()) return;
	type=selsubtype-7;
	if(seljlh<0||seljlh>=stsum) return;
	id=r_st[seljlh].elg->did;
	ShowDynTrans(id,type,TRUE);
}
