// MenuWin.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "MenuWin.h"
#include "comobj.h"
#include "dobj.h"
#include "bclass.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// MenuWin

MenuWin::MenuWin()
{
	dx=0;
	dy=0;
	curpos=0;
	hmax=0;
	mbg.Create(1,1);
	msr.Create(1,1);
	dbm.msr=&msr;

	r_da=NULL;	
	r_tm=NULL;	
	r_am=NULL;	
	r_sc=NULL;	
	r_sf=NULL;  
	r_fsh=NULL; 
	r_ph=NULL;  

	dtsum=0;	
	fssum=0;	
	sfsum=0;	
	scsum=0;	
	amsum=0;	
	tmsum=0;	
	phsum=0;	
}

MenuWin::~MenuWin()
{
}


BEGIN_MESSAGE_MAP(MenuWin, CWnd)
	//{{AFX_MSG_MAP(MenuWin)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	ON_WM_RBUTTONDOWN()
	ON_WM_VSCROLL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MenuWin message handlers

BOOL MenuWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

int MenuWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	char fname[256];
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//打开菜单界面
	cobj.SetToLocalFile("index.pw0",fname);
	dbm.OpenPwFile(fname,0);
	pw=dbm.page.head.width;	
	ph=dbm.page.head.height;
	InitMoveObj();
	return 0;
}

void MenuWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	srt=CRect(0,0,wx,wy);
	if(cx>10&&cy>10){ //开始运行时低于10*10的窗口大小不运行以下函数
		mbg.SizeChange(cx,cy);
		msr.SizeChange(cx,cy);
		ShowA(mbg);
	}
	hmax=ph-wy;
	if(hmax<0) SetScrollRange(SB_VERT,0,0);
	else SetScrollRange(SB_VERT,0,hmax);
	     
}

void MenuWin::OnPaint() 
{
	CPaintDC dc(this);
	msr.CopyDIB(mbg);
	dbm.ShowAct(msr,dx,dy,srt);
	msr.BitBlt(dc.m_hDC,srt);
	dtupdate=1;   //时间更新标志
}


//基本图形显示到背景上，以便活动对象显示
void MenuWin::ShowA(CDIB&mdc)
{
	CRect rt;
	rt=srt;
	dbm.ShowBkgd(mdc,rt);
	dbm.ShowBgDbx(mdc,dx,dy,srt,0);
	dbm.ShowStatic(mdc,dx,dy,srt);
}

//操作结束时的显示
void MenuWin::EndShow()
{
	CRect rt;
	HDC hdc=::GetDC(m_hWnd);
	rt=srt;
	//将对象显示到背景上
	ShowA(mbg);
	//再显示3D对象
	msr.CopyDIB(mbg);
	dbm.ShowAct(msr,dx,dy,rt);
	msr.BitBlt(hdc,rt);
	::ReleaseDC(m_hWnd,hdc);
}

void MenuWin::FreeMem() //释放内存
{
	int i;
	if(dtsum!=0) delete []r_da;
	if(tmsum!=0) delete []r_tm;
	if(scsum!=0) delete []r_sc;
	if(phsum!=0) delete []r_ph;

	r_da=NULL;
	r_tm=NULL;
	r_sc=NULL;
	r_ph=NULL;
	
	
	dtsum=0;
	tmsum=0;
	scsum=0;
	phsum=0;

	

	//释放动画
	for(i=0;i<amsum;i++)	r_am[i].gfaml.FreeMem();
	if(amsum!=0) delete []r_am;
	r_am=NULL;
	amsum=0;
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


void MenuWin::InitMoveObj()
{
	int objsum[100];
	dbm.scf.lmd=0;
	dbm.lookdown=0;
	dbm.curang=0;
	cursor=0;
	dbm.scf.showrev=0;
	dbm.TJObjSum(objsum);

	//返回需要处理的活动对象
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
	fssum=objsum[81];
	if(fssum>0) r_fsh=new RFLASH[fssum];//FLASH对象

	//将动态点连接过来
	GetObjFromDbm();
	dbm.ZoomPage(0);
	Set3DEnv();//设置3D环境
	//重新计算页面大小
	EndShow();
}

//从库中提取数据
void MenuWin::GetObjFromDbm()
{
	CRect rt;
	char fnm[256];
	N_layer *clay;
	R_FLW rfw;
	int i,j, cgif,csft,cpsh,cdat,ctim,cstx,cfsh;

	cgif=0;	csft=0; cstx=0;
	cpsh=0;	cdat=0;	ctim=0;
	cfsh=0; 
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
		case 71:
			r_da[cdat].bs=&clay->obj[j];
			cdat++;
			break;
		case 72:
			r_tm[ctim].bs=&clay->obj[j];
			ctim++;
			break;
		case 73:
			r_am[cgif].bs=(DObj*)&clay->obj[j];
			r_am[cgif].rt=r_am[cgif].bs->ort;
			r_am[cgif].ngf=(N_GIFAML *)r_am[cgif].bs->buf;
			cobj.SetToLocalFile(r_am[cgif].ngf->fname,fnm);
			r_am[cgif].gfaml.ReadGifFile(fnm);
			r_am[cgif].ngf->gfm=&r_am[cgif].gfaml;
			if(r_am[cgif].ngf->type==4){
				r_am[cgif].zt=1;
				r_am[cgif].enable=1;
			}else {
				r_am[cgif].zt=0;
				r_am[cgif].enable=1;
			}
			cgif++;
			break;
		case 74:
			r_sc[cstx].rt=clay->obj[j].ort;
			r_sc[cstx].bs=(DObj*)&clay->obj[j];
			r_sc[cstx].stx=(N_SRLTEXT*)clay->obj[j].buf;
			if(r_sc[cstx].stx->direct==2||r_sc[cstx].stx->direct==4){
					 ClrStrEnter(r_sc[cstx].stx->text);
			 };
			cstx++;
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
		 }
	   }
	};
}

//设置3D环境参数
void MenuWin::Set3DEnv()
{
	msr.Set3DEnv(dbm.curang,dbm.zw,dbm.zh,dbm.lookdown);//设置3D环境
	mbg.Set3DEnv(dbm.curang,dbm.zw,dbm.zh,dbm.lookdown);//设置3D环境
}


//返回当前光标
int MenuWin::GetCursor(CPoint point)
{
	int i;
	CPoint pt,pt1;
	pt=point;
	pt.Offset(-dx,-dy);
	for(i=0;i<phsum;i++)
	{
		if(r_ph[i].bs->PtIsInObj(pt)) return 5;
	}
	return 0;
}


void MenuWin::OnMouseMove(UINT nFlags, CPoint point) 
{
	cursor=GetCursor(point);
	CWnd::OnMouseMove(nFlags, point);
}

void MenuWin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	MouseLBDown(point);
	CWnd::OnLButtonDown(nFlags, point);
}

void MenuWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	
	MouseLBUp(point);
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL MenuWin::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	
	if(nHitTest == HTCLIENT)
	 {
		switch(cursor)
		{
		case 5:	 SetCursor(cobj.hcur[3]);	return TRUE;
		};
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}


//查看属标是否在按钮中
int MenuWin::IsInPush(CPoint point)
{
	int i;
	CDPoint apt;
	apt.SetPOINT(point);
	apt.Offset(-dx,-dy);
	apt.ScrPtToAct(dbm.curzoom);
	for(i=0;i<phsum;i++)
	{
	  if(r_ph[i].rt.PtInRect(apt)) return i;
	}
	return -1;
}

//鼠标左键按下
void MenuWin::MouseLBDown(CPoint point)
{
	int j;
	SetCapture();
	//先察看是否在按钮上
	j=IsInPush(point);
	if(j>=0)
	{
		r_ph[j].psh->down=1;
		ShowPush(j);
	}
}

//鼠标左键放开
void MenuWin::MouseLBUp(CPoint point)
{
	int j;
	CRect rt;
	ReleaseCapture();
	j=IsInPush(point);
	if(j<0) return;
	r_ph[j].psh->down=0;
	ShowPush(j);
	RunPushCmd(j);
	EndShow();
}

//运行按钮命令
void MenuWin::RunPushCmd(int j)
{
	HWND hw;
	char fm[256];
	char fnm[64];
	int i,n,index,mode;
	switch(r_ph[j].psh->cmdtype)
	{
	case 0: WinExec(r_ph[j].psh->command,SW_SHOW); break;
	case 1: //打开画面
		n=sscanf(r_ph[j].psh->command,"%s %d",fnm,&index);
		
		mode=r_ph[j].psh->tosta;
		if(n!=2) return;
		//命令有效
		cobj.SetToLocalFile(fnm,fm);
		
		if(cobj.dbm->CheckFileIndex(fm,index))
		{
			cobj.swin->FreeMem();
			cobj.dbm->OpenPwFile(fm,index);
			cobj.swin->InitMoveObj();
			cobj.SetToNeedMode(mode); 
			i=cobj.mwin->GetVWIndex(cobj.swin);
			if(i>=0) cobj.mwin->GoToPage(i);
			//cobj.mwin->ptl.Invalidate();
			return;
		}
		break;  
	case 2: //发送CMD消息
		GetParent()->PostMessage(WM_COMMAND,r_ph[j].psh->cmdnum);
		break;
	case 3: 
		hw=GetSlfCtl(r_ph[j].psh->selfid);
		if(hw!=NULL) ::PostMessage(hw,WM_COMMAND,r_ph[j].psh->cmdnum,0);
		break;
	case 4: //打开WEB页面
		cobj.mwin->OPenWeb(r_ph[j].psh->command,r_ph[j].psh->title);
		break;
	case 5: //打开Google earth
		cobj.mwin->OPenGoogleEarth(NULL,r_ph[j].psh->title);
		break;
	}
}


//返回自助控件的窗口
HWND MenuWin::GetSlfCtl(int id)
{
	int i;
	for(i=0;i<sfsum;i++){
		if(id==r_sf[i].stl->id)
			return r_sf[i].stl->hwnd;
	};
	return NULL;
}

//显示按钮
void MenuWin::ShowPush(int j)
{
	CRect rt;
	CDRect art;
	if(j<0||j>=phsum) return;
	CClientDC dc(this);
	art=r_ph[j].rt;
	art.ActRtToScr(dbm.curzoom);
	art.Offset(dx,dy);
	art.GetRECT(rt);
	rt&=srt;	
	if(!rt.IsRectEmpty()) PaintShow(dc.m_hDC,rt);
}

void MenuWin::PaintShow(HDC hdc, CRect rt)
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
	msr.BitBltRect(hdc,rt2,rt);
}

void MenuWin::OnRButtonDown(UINT nFlags, CPoint point) 
{
	int cmd;
	selpush=IsInPush(point);
	if(cursor==5&&selpush>=0)//在新窗口中打开界面
	{
		cmd=r_ph[selpush].psh->cmdtype;
		if(cmd==1)  cobj.mwin->NewEmptywindow();//只有打开新可视化才执行
		if(cmd==1||cmd==4||cmd==5) RunPushCmd(selpush);
	}
	CWnd::OnRButtonDown(nFlags, point);
}

void MenuWin::DrawShow()
{
	CClientDC dc(this);
	ShowA(mbg);
}


void MenuWin::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int olddy;
	olddy=dy;
	switch(nSBCode)
	{
	case SB_LINEDOWN:
		curpos+=20;
		break;
	case SB_LINEUP:
		curpos-=20;
		break;
	case SB_PAGEDOWN:
		curpos+=100;
		break;
	case SB_PAGEUP:
		curpos-=100;
		break;
	case SB_BOTTOM:
		curpos=0;
		break;
	case SB_TOP:
		curpos=hmax;
		break;
	case SB_THUMBPOSITION:
		curpos=nPos;
		break;
	}
	if(curpos>=hmax) curpos=hmax;
	if(curpos<0) curpos=0;
	dy=-curpos;

	if(olddy!=dy)
	{
		SetScrollPos(SB_VERT,curpos);
		EndShow();
	}
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}
