// TestWin.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "TestWin.h"
#include "gdata.h"
#include "comobj.h"
#include "bclass.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj cobj;
extern gdata dbm;
extern CImageList  othimg;

int testflag=0;
/////////////////////////////////////////////////////////////////////////////
// TestWin

TestWin::TestWin()
{
	mbg.Create(1,1);
	msr.Create(1,1);
	mtp.Create(1,1);
	cp=0;
	dx=0;
	dy=0;
	r_da=NULL;  
	r_tm=NULL;
	r_am=NULL;
	r_sc=NULL;
	r_sf=NULL;
	r_fw=NULL;
	r_ph=NULL;
	r_at=NULL;
	r_fsh=NULL;
	dnbz=0;
}

TestWin::~TestWin()
{
}


BEGIN_MESSAGE_MAP(TestWin, CWnd)
	//{{AFX_MSG_MAP(TestWin)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// TestWin message handlers

BOOL TestWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))	return FALSE;
	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW),NULL, NULL);
	return TRUE;
}

int TestWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	int w,h;
	w=GetSystemMetrics(SM_CXSCREEN);
	h=GetSystemMetrics(SM_CYSCREEN);
	clsw.Createtun(WS_POPUPWINDOW|WS_VISIBLE|WS_EX_TOPMOST,CRect(w-250,h-60,w-10,h-20),this);
	return 0;
}

void TestWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	int i;
	CRect rt;
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	srt=CRect(0,0,wx,wy);
	ComputMaxXY();
	if(cx>mbg.nWidth||cy>mbg.nHeight) mbg.SizeChange(cx,cy);
	if(cx>msr.nWidth||cy>msr.nHeight) msr.SizeChange(cx,cy);
	if(cx>mtp.nWidth||cy>mtp.nHeight) mtp.SizeChange(cx,cy);
	//调整自助控件的窗口大小
	for(i=0;i<sfsum;i++){
	  if(r_sf[i].cansize==1){
		  ChangeCtlSize(CRect(0,0,cx,cy),r_sf[i].swp);
	  }
	};
	//调整FLASH位置
	for(i=0;i<fssum;i++){
		rt=r_fsh[i].rt;
		rt.OffsetRect(dx,dy);
		if(r_fsh[i].fsh->align_left==1) rt.left=0;
		if(r_fsh[i].fsh->align_top==1)  rt.top=0;
		if(r_fsh[i].fsh->align_right==1) rt.right=wx;
		if(r_fsh[i].fsh->align_buttom==1) rt.bottom=wy;
		r_fsh[i].fshw.MoveWindow(rt,true);
	}
}

void TestWin::OnPaint() 
{
	CRect *rt,rt1;
	RGNDATA *lp;
	char buff[1024];
	int i,n,m;
	CRgn rgn;
	rgn.CreateRectRgn(0,0,10,10);
	int r=GetUpdateRgn( &rgn);
	CPaintDC dc(this);
	if(r!=NULLREGION||r!=ERROR){
		n=rgn.GetRegionData((LPRGNDATA)buff,1024);
		if(n!=ERROR||n!=NULLREGION){
			lp=(RGNDATA*)buff;
			m=lp->rdh.nCount;
			rt=(CRect*)lp->Buffer;
			for(i=0;i<m;i++){
				rt1=rt[i];
 	 			Show(dc,rt1);
			}
		}
	 }
}


BOOL TestWin::Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd) 
{
	WNDCLASS wndcls;
	memset(&wndcls, 0,sizeof(WNDCLASS));   
    wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hCursor = NULL;
	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpszClassName ="popupwin";
	AfxRegisterClass(&wndcls);
	return CreateEx (0, "popupwin","",dwStyle,rt.left,rt.top,rt.Width(),rt.Height(),pParentWnd->m_hWnd,NULL);
}

//按属性改变窗口的矩形
void TestWin::ChangeCtlSize(CRect rtd,SUBW_PARAM&pas,int ly)
{
	/*int cdx,cdy,cx,cy;
	CRect rt;
	rt=pas.rt;
	cdx=rtd.left;
	cdy=rtd.top;
	rt.OffsetRect(-cdx,-cdy);
	cx=rtd.Width();
	cy=rtd.Height();
	if(pas.left==1)		rt.left=ly;
	if(pas.top==1)		rt.top=ly;
	if(pas.right==1)	rt.right=cx-ly;
	if(pas.bottom==1)	rt.bottom=cy-ly;
	rt.OffsetRect(dx,dy);
	pas.rt=rt;
	pas.rtw=GLDrawCtrlOutline(msr.m_hDC,rt,pas.outline);
	if(pas.hwnd!=NULL) ::MoveWindow(pas.hwnd,pas.rtw.left,pas.rtw.top,
		 pas.rtw.Width(),pas.rtw.Height(),true);
		 */
}

//计算x,y方向可以移动的数
void TestWin::ComputMaxXY()
{
	dbm.cpage->zw=(int)((double)(dbm.cpage->head.width*cobj.curzoom));
	dbm.cpage->zh=(int)((double)(dbm.cpage->head.height*cobj.curzoom));
	xmax=wx-dbm.cpage->zw;
	ymax=wy-dbm.cpage->zh;
}

void TestWin::Show(HDC hdc, CRect rt)
{
	int i,w,h;
	CRect rt1,rt2;
	if(dnbz==1){  //滚动时全显示
		rt1=rt;
		rt1.OffsetRect(-dx,-dy);
		w=rt1.right-rt1.left+1;
		h=rt1.bottom-rt1.top+1;
		rt2=CRect(0,0,w,h);
		dbm.ShowBkgd(msr,rt1);
		dbm.TestShow(msr,-rt.left+dx,-rt.top+dy,rt1);
		for(i=0;i<atsum;i++){
			ShowActObj(msr.m_hDC,rt.left,rt.top,i);
		}
		msr.BitBltRect(hdc,rt2,rt);
	}
	if(dnbz==0){//静态时显示
		rt1=rt;
		rt1.OffsetRect(dx,dy);
		rt2=rt;
		rt2.OffsetRect(-dx,-dy);
		mbg.BitBltRect(mtp.m_hDC,rt,rt);
		dbm.TestShow1(mtp,dx,dy,rt2,0);
		for(i=0;i<atsum;i++){
			ShowActObj(msr.m_hDC,rt.left,rt.top,i);
		}
				
		mtp.BitBltRect(hdc,rt,rt);
	}
}

//显示小图标
void TestWin::ShowActObj(HDC hdc,int x,int y,int k)
{
	int i,w,h;
	CPoint cpt;
	CRect rt;
	CDRect art;
	art=r_at[k].currt;
	art.ActRtToScr(cobj.curzoom);
	art.GetRECT(rt);
	rt.OffsetRect(dx-x,dy-y);
	cpt=rt.CenterPoint();
	i=r_at[k].picj;
	if(i<0){
		CDC dc;
	    dc.Attach(hdc);
	    othimg.Draw(&dc,12,CPoint(cpt.x-8,cpt.y-8),ILD_NORMAL);
	    dc.Detach();
		return;
	}
	w=cobj.spic[i].img.nWidth;
	h=cobj.spic[i].img.nHeight;
	w=w>(rt.right-rt.left) ? rt.right-rt.left:w;
	h=h>(rt.bottom-rt.top) ? rt.bottom-rt.top:h;
	cobj.spic[i].img.Show(hdc,cpt.x-w/2,cpt.y-h/2,w,h);
}

void TestWin::FreeMem() //释放内存
{
	int i;
	if(r_da!=NULL&&dtsum!=0) delete []r_da;
	if(r_tm!=NULL&&tmsum!=0) delete []r_tm;
	if(r_am!=NULL&&amsum!=0) delete []r_am;
	if(r_sc!=NULL&&scsum!=0) delete []r_sc;
	if(r_ph!=NULL&&phsum!=0) delete []r_ph;
	if(r_at!=NULL&&atsum!=0) delete []r_at;
	r_da=NULL;
	r_tm=NULL;
	r_am=NULL;
	r_sc=NULL;
	r_ph=NULL;
	r_at=NULL;
	
	for(i=0;i<sfsum;i++){
	   if(r_sf[i].stl->hwnd!=NULL&&r_sf[i].stl->hinst!=NULL&&
		   r_sf[i].stl->DfClose!=NULL)
		 {
			 ::SendMessage(r_sf[i].stl->hwnd,WM_CLOSE,0,0);
			 r_sf[i].stl->DfClose(r_sf[i].stl->rc);
			 r_sf[i].stl->hwnd=0;
			 r_sf[i].stl->rc=0;
		 }
	};

	if(r_sf!=NULL&&sfsum!=0) delete []r_sf;
	r_sf=NULL;
	sfsum=0;
	
	for(i=0;i<fwsum;i++) if(r_fw[i].hrgn!=NULL) DeleteObject(r_fw[i].hrgn);
	if(r_fw!=NULL&&fwsum!=0) delete []r_fw;
	r_fw=NULL;
	fwsum=0;

	for(i=0;i<fssum;i++){
		r_fsh[i].fshw.CloseWindow();
	}
	if(r_fsh!=NULL&&fssum!=0) delete []r_fsh;
	r_fsh=NULL;
	fssum=0;
}
int ks=0;
void TestWin::OnTimer(UINT nIDEvent) 
{
	HDC hdc;
	if(dnbz==0){
	 hdc=::GetDC(m_hWnd);
	 switch(nIDEvent)
	 {
	  case 100:
		  DemoAnalog(hdc);
		  DemoStatus(hdc);
		  break;
	  case 101:
		  ShowGifAml(hdc);
		  ShowScrTxt(hdc);
		  demoactobj(hdc);
		  ks++;
		  if(ks>=flwjg){
			  ks=0;
			  ShowFlow(hdc);
		  }
		  break;
	  case 102:
		  demodtime(hdc);
		  break;
	 }
	 ::ReleaseDC(m_hWnd,hdc);
	}
	CWnd::OnTimer(nIDEvent);
}



//演示模拟量
BYTE kk=0;
void TestWin::DemoAnalog(HDC hdc,int enable)
{
	int i,j;
	CRect rt;
	CDRect art;
	N_LAYER *clay;
	R_ANL  anl;
	anl.curval=(float)(rand()%1000);  //随机数
	anl.enable=(unsigned)enable;
	anl.alarm=anl.curval>500 ? 1:0;
	for(i=0;i<dbm.cpage->laysum;i++){
		clay=&dbm.cpage->layer[i];
		for(j=0;j<clay->objnum;j++){
			kk++;
			if(kk%3==0&&enable==1)
			if(clay->obj[j].SetAnlVal(anl)){
				art=clay->obj[j].ort;
				art.ActRtToScr(cobj.curzoom);
				art.GetRECT(rt);
				rt.bottom+=4;
				rt.OffsetRect(dx,dy);
				rt&=srt;
				if(!rt.IsRectEmpty()) ShowD(hdc,rt);
			};
			if(enable==0){
				anl.alarm=0;
				clay->obj[j].SetAnlVal(anl);
			}
		}
	}
}


R_STA  sta;
//演示状态量
void TestWin::DemoStatus(HDC hdc,int enable)
{
	int i,j;
	CRect rt;
	CDRect art;
	N_LAYER *clay;
	sta.ele=1;
	sta.enable=(unsigned)enable;
	sta.zt=sta.zt==0 ? 1:0;
	for(i=0;i<dbm.cpage->laysum;i++){
		clay=&dbm.cpage->layer[i];
		for(j=0;j<clay->objnum;j++){
		kk++;
		if(kk%5==0&&enable==1){
			if(clay->obj[j].SetStaVal(sta)){
				art=clay->obj[j].ort;
				art.ActRtToScr(cobj.curzoom);
				art.GetRECT(rt);
				rt.OffsetRect(dx,dy);
				rt&=srt;		
				if(!rt.IsRectEmpty()) ShowD(hdc,rt);
			}
		}
		if(enable==0){
			clay->obj[j].SetStaVal(sta);
		}
	}
	}
}


//显示GIF动画
void TestWin::ShowGifAml(HDC hdc)
{
	int i,w,h,x,y;
	CRect rt,rt1;
	CDRect art;
	for(i=0;i<amsum;i++){
	 art=r_am[i].bs->ort;
	 art.ActRtToScr(cobj.curzoom);
	 art.GetRECT(rt);
	 w=rt.Width();
	 h=rt.Height();
	 rt.OffsetRect(dx,dy);
	 x=(rt.right+rt.left)/2-w/2;
	 y=(rt.top+rt.bottom)/2-h/2;
	 if(r_am[i].gfaml.CanShow()){
		BitBlt(r_am[i].gfaml.m_hDC,0,0,w,h,mtp.m_hDC,x,y,SRCCOPY);
	  }
	  r_am[i].gfaml.Show(hdc,x,y,w,h);
	 }
}

void TestWin::ShowAScrTxt(HDC hdc, int j,int mode)
{
	CRect rt,rt1,rt2,rt3;
	CDRect art;
	int w,h;
	DWORD align;
	N_SRLTEXT *a;
	LOGFONT font;
	a=(N_SRLTEXT*)r_sc[j].stx;
	art=r_sc[j].bs->ort;
	art.ActRtToScr(cobj.curzoom);
	art.GetRECT(rt1);
	rt2=rt1;
	rt2.OffsetRect(dx,dy);
	rt2&=srt;
	if(!rt2.IsRectEmpty()){
	 w=rt1.Width();
	 h=rt1.Height();
	 rt=CRect(0,0,w,h);
	 font=a->lf;
	 font.lfHeight=font.lfHeight;
	 font.lfWidth=font.lfWidth;
	 switch(a->align){
	  case 1:  align=DT_CENTER;break;
	  case 2:  align=DT_RIGHT; break;
	  default: align=DT_LEFT;
	  };
	 rt3=rt1;
	 rt3.OffsetRect(dx,dy);
	 mtp.BitBltRect(msr.m_hDC,rt3,rt);
	 if(a->glass) msr.CDrawGlass(rt,a->gcolor,a->fcolor,a->outline,a->depth);
	 switch(a->direct){
	  case 0:
		if(mode==0)
		  msr.CTextOut(a->text,rt,&font,a->tcolor,a->tstyle,a->align);
		  break;
	  case 1:
		  r_sc[j].yl++;
		  if(r_sc[j].yl>r_sc[j].h) r_sc[j].yl=0;
		  rt2=CRect(5,h-r_sc[j].yl,w-5,h);
		  msr.CTextOut(a->text,rt2,&font,a->tcolor,a->tstyle,a->align);
		  break;
	  case 3:
		  r_sc[j].yl--;
		  if(r_sc[j].yl<=0) r_sc[j].yl=r_sc[j].h;
		  rt2=CRect(5,h-r_sc[j].yl,w-5,h);
		  msr.CTextOut(a->text,rt2,&font,a->tcolor,a->tstyle,a->align);
		  break;
	  case 4:
		  r_sc[j].xl++;
		  if(r_sc[j].xl>r_sc[j].w) r_sc[j].xl=0;
		  rt2=CRect(r_sc[j].xl-r_sc[j].w+w,3,w,h-3);
		  msr.CTextOut(a->text,rt2,&font,a->tcolor,a->tstyle,a->align);
		  break;
	  case 2:
		  r_sc[j].xl--;
		  if(r_sc[j].xl<=0) r_sc[j].xl=r_sc[j].w;
		  rt2=CRect(r_sc[j].xl-r_sc[j].w+w,3,w,h-3);
		  msr.CTextOut(a->text,rt2,&font,a->tcolor,a->tstyle,a->align);
		  break;
	  };
	  rt1.OffsetRect(dx,dy);
	  msr.BitBltRect(hdc,rt,rt1);
	}
}
//刷新显示
void TestWin::ShowScrTxt(HDC hdc)
{
	int i;
	for(i=0;i<scsum;i++){
		ShowAScrTxt(hdc,i);
	};
}

//演示活动对象
void TestWin::demoactobj(HDC hdc)
{
	int i;
	CRect rt;
	CDRect art;
	for(i=0;i<atsum;i++){
		r_at[i].js++;
		if(r_at[i].js>=r_at[i].act->speed){
		  	r_at[i].js=0;
			AutoSetActValue(i);
			art=r_at[i].oldrt;
			art.ActRtToScr(cobj.curzoom);
			art.GetRECT(rt);
			rt.OffsetRect(dx,dy);
			rt&=srt;
			if(!rt.IsRectEmpty()) ShowB(hdc,rt);
			art=r_at[i].currt;
			art.ActRtToScr(cobj.curzoom);
			art.GetRECT(rt);
			rt.OffsetRect(dx,dy);
			rt&=srt;
			if(!rt.IsRectEmpty()) ShowB(hdc,rt);
		}
	}
}

//自动设置活动对象的值
void TestWin::AutoSetActValue(int i)
{
	double n,q;
	int w,h;
	if(r_at[i].ptsum==0) return;
	n=r_at[i].act->skip;
	q=r_at[i].curval;
	q=q+n;
	if(q>r_at[i].maxv) q=r_at[i].minv;
	r_at[i].curval=q;
	DPOINT pt=GetPosition(r_at[i].pt,r_at[i].ptsum,r_at[i].minv,r_at[i].maxv,r_at[i].curval);
	r_at[i].oldrt=r_at[i].currt;
	w=r_at[i].picw/2;
	h=r_at[i].pich/2;
	r_at[i].currt=CDRect(pt.x-w,pt.y-h,pt.x+w,pt.y+h);
}

//潮流线显示
void TestWin::ShowFlow(HDC hdc)
{
	
	int i;
	for(i=0;i<fwsum;i++) pqjs(i);
	ShowAFlow(hdc);
}

//显示一条潮流线
void TestWin::ShowAFlow(HDC hdc)
{
	int i,w,h;
	HRGN hrgn;
	CRect rt,rt1,rt2,rt3;
	HRGN oldrgn;
	hrgn=CreateRectRgn(0,0,1,1);
	for(i=0;i<fwsum;i++) CombineRgn(hrgn,hrgn,r_fw[i].hrgn,RGN_OR);
	GetRgnBox(hrgn,&rt);
	rt3=srt;
	rt3.OffsetRect(-dx,-dy);
	rt&=rt3;
	if(!rt.IsRectEmpty())
	{
		rt.left-=5;   rt.top-=6;
		rt.right+=6;  rt.bottom+=6;
		w=rt.Width(); h=rt.Height();
		rt1=CRect(0,0,w,h);
		rt2=rt;
		rt2.OffsetRect(dx,dy);
		mtp.BitBltRect(msr.m_hDC,rt2,rt1);
		for(i=0;i<fwsum;i++)  r_fw[i].bs->ShowFlow(msr.m_hDC,-rt.left,-rt.top);
		OffsetRgn(hrgn,dx,dy);
 		oldrgn=(HRGN)::SelectObject(hdc,hrgn);
		rt.OffsetRect(dx,dy);
		msr.BitBltRect(hdc,rt1,rt);
		::SelectObject(hdc,oldrgn);
	}
	DeleteObject(hrgn);
}

//定时演示日期时间
void TestWin::demodtime(HDC hdc)
{
	int i;
	CRect rt;
	CDRect art;
	N_DATE *d;
	N_TIME *t;
	int day,sec;
	CTime tm;
	tm=CTime::GetCurrentTime();
	day=tm.GetDay();
	sec=tm.GetSecond();
	for(i=0;i<dtsum;i++){
		d=(N_DATE*)r_da[i].bs->buf;
		if(d->tm.GetDay()!=day){
			d->tm=tm;
			art=r_da[i].bs->ort;
			art.ActRtToScr(cobj.curzoom);
			art.GetRECT(rt);
			rt.OffsetRect(dx,dy);
			rt&=srt;		
			if(!rt.IsRectEmpty()) Show(hdc,rt);
		}
	}
	for(i=0;i<tmsum;i++){
		t=(N_TIME*)r_tm[i].bs->buf;
		if(t->tm.GetSecond()!=sec){
			t->tm=tm;
			art=r_tm[i].bs->ort;
			art.ActRtToScr(cobj.curzoom);
			art.GetRECT(rt);
			rt.OffsetRect(dx,dy);
			rt&=srt;		
			if(!rt.IsRectEmpty()) Show(hdc,rt);
		}
	}
}

//基本图形显示到背景上，以便活动对象显示
void TestWin::ShowA()
{
	CRect rt=CRect(0,0,wx,wy);
	rt.OffsetRect(-dx,-dy);
 	dbm.ShowBkgd(mbg,rt);
 	dbm.TestShow2(mbg,dx,dy,rt);
}

void TestWin::ShowB(HDC hdc,CRect rt)
{
	int i,w,h;
	w=rt.Width();
	h=rt.Height();
	mtp.BitBltRect(msr.m_hDC,rt,CRect(0,0,w,h));
	for(i=0;i<atsum;i++){
	 ShowActObj(msr.m_hDC,rt.left,rt.top,i);
	}
	msr.BitBltRect(hdc,CRect(0,0,w,h),rt);	
}

//将活动对象全显时到动态背景上
void TestWin::ShowC()
{
	CRect rt;
	rt=CRect(0,0,wx,wy);
	rt.OffsetRect(-dx,-dy);
	mtp.CopyDIB(mbg);
 	dbm.TestShow1(mtp,dx,dy,rt,0);
}
void TestWin::ShowD(HDC hdc, CRect rt)
{
	int i;
	CRect rt1,rt2;
	rt1=rt;
	rt1.OffsetRect(dx,dy);
	rt2=rt;
	rt2.OffsetRect(-dx,-dy);
	mbg.BitBltRect(mtp.m_hDC,rt,rt);
	dbm.TestShow1(mtp,dx,dy,rt2,0);
	for(i=0;i<atsum;i++){
			ShowActObj(msr.m_hDC,rt.left,rt.top,i);
	}
	mtp.BitBltRect(hdc,rt,rt);
}
//查看属标是否在按钮中
int TestWin::IsInPush(CPoint point)
{
	int i;
	for(i=0;i<phsum;i++){
	  if(r_ph[i].rt.PtInRect(point)) return i;
	}
	return -1;
}

//显示按钮
void TestWin::ShowPush(int j)
{
	CRect rt;
	if(j<0||j>=phsum) return;
	HDC hdc=::GetDC(m_hWnd);
	rt=r_ph[j].rt;
	rt.OffsetRect(dx,dy);
	rt&=srt;		
	if(!rt.IsRectEmpty()) Show(hdc,rt);
	::ReleaseDC(m_hWnd,hdc);
}

void TestWin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int j;
	j=IsInPush(point);
	if(j>=0){
		r_ph[j].psh->down=1;
	    ShowPush(j);
		return;
	}
	pt1=point;
	dnbz=1;
	SetCapture();
	CWnd::OnLButtonDown(nFlags, point);
}

void TestWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int j;
	ReleaseCapture();
	j=IsInPush(point); 
	if(j>=0){
		r_ph[j].psh->down=0;
	    ShowPush(j);
		RunPushCmd(j);
	}
	if(dnbz==1){
		ShowA();
 		ShowC();
	}
	dnbz=0;
	CWnd::OnLButtonUp(nFlags, point);
}

void TestWin::OnMouseMove(UINT nFlags, CPoint point) 
{
	int j;
	j=IsInPush(point);
	if(oldsel!=j){
		if(oldsel>=0&&oldsel<phsum) r_ph[oldsel].psh->down=0;
		ShowPush(oldsel);
	}
	if(j>=0){
		BYTE k=r_ph[j].psh->style;
		if(nFlags==MK_LBUTTON) r_ph[j].psh->down=1;
		else if(k==1||k==2||k==4||k==6) r_ph[j].psh->down=1;
		if(j!=oldsel) ShowPush(j);
		oldsel=j;
	}else{
		oldsel=-1;
	}
	if(dnbz==1) MovePic(point);
	CWnd::OnMouseMove(nFlags, point);
}


//运行按钮命令
void TestWin::RunPushCmd(int j)
{
	HWND hw;
	switch(r_ph[j].psh->cmdtype){
	case 0: WinExec(r_ph[j].psh->command,SW_SHOW); break;
	case 1: //打开画面
		MessageBox("打开界面功能正确");
		break;
	case 2: //发送CMD消息
		MessageBox("发送CMD消息功能正确");
		break;
	case 3: 
		hw=GetSlfCtl(r_ph[j].psh->selfid);
		if(hw!=NULL) ::PostMessage(hw,WM_COMMAND,r_ph[j].psh->cmdnum,0);
		break;
	case 4: //退出程序
		MessageBox("退出系统功能正确");
		break;
	case 5: //执行功能模块
		RunFunctModule(r_ph[j].psh->command);
		break;
	}
}

//返回自助控件的窗口
HWND TestWin::GetSlfCtl(int id)
{
	int i;
	for(i=0;i<sfsum;i++){
		if(id==r_sf[i].stl->id)
			return r_sf[i].stl->hwnd;
	};
	return NULL;
}

/**************************************************************
执行功能模块
mstring的格式：库  函数名  int参数 串参数
函数标准：void funct(int param1,char *str)
funct必须是打开一个对话框或者立即执行完毕的函数
     不能为POPUP窗口
***************************************************************/
void TestWin::RunFunctModule(char *mstring)
{
	char filename[256];
	char dllname[45]; //动态连接库名
	char fnm[45];	  //函数名	
	char pstr[45];	  //串参数
	int  pint;		  //int参数
	void (WINAPI*mfunct)(int param,char *str);    //模块函数
	pint=0;
	pstr[0]=0;
	dllname[0]=0;
	sscanf(mstring,"%s %s %d %s",dllname,fnm,&pint,pstr);
	if(strlen(dllname)<4){
		MessageBox("模块名错误！","错误",MB_ICONERROR|MB_OK);
		return;
	}
	cobj.SetToLocalFile(dllname,filename);

	HINSTANCE hinst=LoadLibrary(filename);
	if(hinst!=NULL){
	  (FARPROC&)mfunct=GetProcAddress(hinst,"fnm");
	  if(mfunct!=NULL) mfunct(pint,pstr);
	   else MessageBox("指定的函数不存在！","错误",MB_ICONERROR|MB_OK);
	  FreeLibrary(hinst);
	}else{
		MessageBox("指定的模块不存在！","错误",MB_ICONERROR|MB_OK);
	}
}

void TestWin::MovePic(CPoint point)
{
	int x,y;
	int oldx,oldy,sx,sy;
	if(dnbz!=1||xmax>0||ymax>0) return;
	oldx=dx;
	oldy=dy;
	if(xmax<0){
		x=point.x-pt1.x;
		dx+=x;
		dx=dx>0 ? 0:dx;
		dx=dx<xmax ? xmax:dx;
	}
	if(ymax<0){
		y=point.y-pt1.y;
		dy+=y;
		dy=dy>0 ? 0:dy;
		dy=dy<ymax ? ymax:dy;
	}
	sx=oldx-dx;
	sy=oldy-dy;
	if(sx!=0||sy!=0){
		ScrollWindow(-sx,-sy);
	}
	pt1=point;
};

void TestWin::SetPage()
{
	cp=dbm.curpage;
	wd=dbm.page[cp].head.width;
	hg=dbm.page[cp].head.height;
	mbg.SizeChange(wx,wy);
	msr.SizeChange(wx,wy);
	mtp.SizeChange(wx,wy);
	//保存原有的放大倍数
	oldzm=cobj.curzoom;
	ComputZoom();
	dnbz=0;
	////////////////////
	dtsum=dbm.GetObjSum(71);
	if(dtsum>0) r_da=new ROBJ[dtsum]; //日期
	tmsum=dbm.GetObjSum(72);
	if(tmsum>0) r_tm=new ROBJ[tmsum]; //时间
	amsum=dbm.GetObjSum(73);
	if(amsum>0) r_am=new RAML[amsum]; //GIF动画
	scsum=dbm.GetObjSum(74);
	if(scsum>0) r_sc=new RSCRTXT[scsum]; //滚动文本
	sfsum=dbm.GetObjSum(76);
	if(sfsum>0) r_sf=new RSELFCTL[sfsum];//自助控件
	fwsum=dbm.GetObjSum(77);
	if(fwsum>0) r_fw=new RFLOW[fwsum];   //潮流线 
	phsum=dbm.GetObjSum(75);
	if(phsum>0) r_ph=new RPUSH[phsum];	 //按钮
	atsum=dbm.GetObjSum(80);
	if(atsum>0) r_at=new RACTOBJ[atsum]; //活动对象
	fssum=dbm.GetObjSum(81);
	if(fssum>0) r_fsh=new RFLASH[fssum]; //FLASH对象
	//将动态点连接过来
	GetObjFromDbm();
	flwjg=fwsum/40;
	oldsel=-1;
	//设置定时器
	SetTimer(100,2000,NULL);  //模拟数据定时
 	SetTimer(101,50,NULL);	  //动画和滚动文本定时
	SetTimer(102,500,NULL);	  //时钟显示
    ShowA();
  	ShowC();
	OnSize(SIZE_RESTORED,wx,wy);
}

//从库中提取数据
void TestWin::GetObjFromDbm()
{
	char fnm[256];
	N_layer *clay;
	int i,j,canl,crat,csta,cgif,ccom,csft,cpsh,cdat,ctim,
		ctrd,cstx,cyk,cflw,cspl,cact,cfsh;
	N_GIFAML *gf;
	SIZE size;
	canl=0;	crat=0;	csta=0;	cgif=0;	ccom=0;	csft=0;
	cpsh=0;	cdat=0;	ctim=0;	ctrd=0;	cstx=0; cyk=0;
	cflw=0; cspl=0; cact=0; cfsh=0;
	for(i=0;i<dbm.cpage->laysum;i++){
	  clay=&dbm.cpage->layer[i];
	  for(j=0;j<clay->objnum;j++){
		switch(clay->obj[j].attr.type){
		case 71:
			r_da[cdat].bs=&clay->obj[j];
			cdat++;
			break;
		case 72:
			r_tm[ctim].bs=&clay->obj[j];
			ctim++;
			break;
		case 73:
			r_am[cgif].bs=(BASE0*)&clay->obj[j];
			r_am[cgif].bs->ort.GetRECT(r_am[cgif].rt);
			gf=(N_GIFAML *)r_am[cgif].bs->buf;
			cobj.SetToLocalFile(gf->fname,fnm);
			r_am[cgif].gfaml.ReadGifFile(fnm);
			cgif++;
			break;
		case 74:
			clay->obj[j].ort.GetRECT(r_sc[cstx].rt);
			r_sc[cstx].bs=(BASE0*)&clay->obj[j];
			r_sc[cstx].stx=(N_SRLTEXT*)clay->obj[j].buf;
			if(r_sc[cstx].stx->direct==1||r_sc[cstx].stx->direct==3){
				size=GLDGetTextSize(mbg.m_hDC,&r_sc[cstx].stx->lf,r_sc[cstx].stx->text);
				r_sc[cstx].h=r_sc[cstx].rt.Height()+size.cy*GetLineNum(r_sc[cstx].stx->text);
			};
			if(r_sc[cstx].stx->direct==2||r_sc[cstx].stx->direct==4){
			 ClrStrEnter(r_sc[cstx].stx->text);
			 size=GLDGetTextSize(mbg.m_hDC,&r_sc[cstx].stx->lf,r_sc[cstx].stx->text);
		     r_sc[cstx].w=r_sc[cstx].rt.Width()+size.cx;	     
			};
			r_sc[cstx].xl=0;
			r_sc[cstx].yl=0;
			cstx++;
			break;
		case 75:
			r_ph[cpsh].bs=&clay->obj[j];
			clay->obj[j].ort.GetRECT(r_ph[cpsh].rt);
			r_ph[cpsh].psh=(N_PUSH*)clay->obj[j].buf;
			cpsh++;
			break;
        case 76:
			clay->obj[j].ort.GetRECT(r_sf[csft].rt);
			r_sf[csft].sid=clay->obj[j].attr.ID;
			r_sf[csft].cansize=1;
			r_sf[csft].stl=(N_SELFCTL*)clay->obj[j].buf;
			if(r_sf[csft].stl->hinst!=NULL&&r_sf[csft].stl->DfInit!=NULL){ 
				r_sf[csft].stl->rc=r_sf[csft].stl->DfInit(m_hWnd,r_sf[csft].stl->hwnd,
					r_sf[csft].rt,r_sf[csft].stl->id,r_sf[csft].stl->style,r_sf[csft].stl->lkbuf);
				}
				else r_sf[csft].stl->hwnd=NULL;
			GetSflRunParam(r_sf[csft].swp,r_sf[csft]);
			csft++;
			break;
		case 77:
			clay->obj[j].ort.GetRECT(r_fw[cflw].rt);
			r_fw[cflw].bs=&clay->obj[j];
			r_fw[cflw].flw=(N_FLOW*)clay->obj[j].buf;
			r_fw[cflw].flw->rf.pjs=0;
			r_fw[cflw].flw->rf.qjs=15;
			CreateFlwRgn(cflw);
			cflw++;
			break;
		case 80:
			clay->obj[j].ort.GetRECT(r_at[cact].rt);
			r_at[cact].oldrt=CDRect(-1000,-100,0,0);
			r_at[cact].currt=CDRect(-1000,-1000,0,0);
			r_at[cact].js=0;
			r_at[cact].act=(N_ACTOBJ*)clay->obj[j].buf;
			GetActPicMsg(cact);
			cact++;
			break;
		case 81:
			clay->obj[j].ort.GetRECT(r_fsh[cfsh].rt);
			r_fsh[cfsh].fsh=(N_FLASH*)clay->obj[j].buf;
			r_fsh[cfsh].fshw.Create("",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,130+cfsh);
			r_fsh[cfsh].fshw.SetMovie(r_fsh[cfsh].fsh->fname);
			if(r_fsh[cfsh].fsh->playmode==1) r_fsh[cfsh].fshw.SetLoop(TRUE);
			cfsh++;
			break;
		};
		}
	};
}

//返回字符串的行数
int TestWin::GetLineNum(char *str)
{
	int i,len,n;	
	n=1;
	len=strlen(str);
	for(i=0;i<len;i++){
		if(str[i]==0xd) n++; 
	};
	return n;
}

//清除自符串中的回车键
void TestWin::ClrStrEnter(char *str)
{
	int i,len;	
	len=strlen(str);
	for(i=0;i<len;i++){
	  if(str[i]==0xd||str[i]==0xa) str[i]=' '; 
	};
}

//返回自助控件的参数
void TestWin::GetSflRunParam(SUBW_PARAM&pad,RSELFCTL&pas)
{
	pad.bottom=pas.stl->abottom;
	pad.left=pas.stl->aleft;
	pad.mode=pas.stl->mode;
	pad.outline=0;
	pad.right=pas.stl->aright;
	pad.top=pas.stl->atop;
	pad.rts=pas.rt;
	pad.rt=pas.rt;
	pad.rtw=pas.rt;
	pad.hwnd=pas.stl->hwnd;
}

//生成潮流的区域
void TestWin::CreateFlwRgn(int j)
{
	int i,ptsum;
	double w;
	CRect rt;
	HRGN hrgn1,hrgn2;
	POINT *pt;
	ptsum=r_fw[j].flw->ptsum;
	ptsum=ptsum>20 ? 20:ptsum;
	for(i=0;i<ptsum;i++){
		r_fw[j].pt[i].x=(int)(r_fw[j].flw->pt[i].x*cobj.curzoom);
		r_fw[j].pt[i].y=(int)(r_fw[j].flw->pt[i].y*cobj.curzoom);
	};	
	pt=r_fw[j].pt;
	w=5*cobj.curzoom;
	hrgn1=BCreateLineRGN(CPoint(pt[0]),CPoint(pt[1]),w);
	for(i=1;i<ptsum-1;i++){
		hrgn2=BCreateLineRGN(CPoint(pt[i]),CPoint(pt[i+1]),w);
	    CombineRgn(hrgn1,hrgn1,hrgn2,RGN_OR);
	    DeleteObject(hrgn2);
	};
	r_fw[j].hrgn=hrgn1;
	GetRgnBox(hrgn1,&r_fw[j].rt);
	rt=r_fw[j].rt;
	r_fw[j].ptsum=ptsum;
	for(i=0;i<ptsum;i++){
		pt[i].x=pt[i].x-rt.left+8;
		pt[i].y=pt[i].y-rt.top+8;
	};
}

//返回图片信息
void TestWin::GetActPicMsg(int i){
	int j,k,w,h,w1,h1;
	j=cobj.GetPICRecno(r_at[i].act->gid);
	r_at[i].picj=j;
	if(j<0){
		r_at[i].picw=24;
		r_at[i].pich=16;
	}else
	{
	w=r_at[i].rt.Width();
	h=r_at[i].rt.Height();
	w1=cobj.spic[j].img.nWidth;
	h1=cobj.spic[j].img.nHeight;
	w=w1>w ? w:w1;
	h=h1>h ? h:h1;
	r_at[i].picw=w;
	r_at[i].pich=h;
	}

	r_at[i].curval=0;	//实时值
	r_at[i].maxv=100;	//最大值
	r_at[i].minv=0;		//最小值
	//查找路经
	N_PATH *ph;
	r_at[i].pt=NULL;
	r_at[i].ptsum=0;
	for(k=0;k<dbm.cpage->laysum;k++){
	for(j=0;j<dbm.cpage->layer[k].objnum;j++){
		if(dbm.cpage->layer[k].obj[j].attr.type==16){
		ph=(N_PATH*)dbm.cpage->layer[k].obj[j].buf;
		if(ph->ID==r_at[i].act->pathid){
			r_at[i].pt=ph->pt;
			r_at[i].ptsum=ph->ptsum;
			r_at[i].curval=ph->start;	//实时值
			r_at[i].maxv=ph->end;		//最大值
			r_at[i].minv=ph->start;		//最小值
			break;
		}
		}
	}
	}
}


void TestWin::EndTest()
{
	testflag=0;
	KillTimer(100);
	KillTimer(101);
	KillTimer(102);
	mbg.SizeChange(1,1);
	msr.SizeChange(1,1);
	mtp.SizeChange(1,1);
	DemoAnalog(0,0);
	DemoStatus(0,0);
	FreeMem();
	//恢复原有的放大倍数
	cobj.curzoom=oldzm;
}

LRESULT TestWin::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	char tnm[256];
	if(message==1200){
		switch(wParam){
		case 3:
			cobj.SetToLocalFile((char *)lParam,tnm);
			strcpy((char*)lParam,tnm);
			return true;
		}
	}
	return CWnd::WindowProc(message, wParam, lParam);
}


void TestWin::OnClose() 
{
	EndTest();
	CWnd::OnClose();
}
//计算放大倍数
void TestWin::ComputZoom()
{
	double a1,a2;
	srt=CRect(0,0,wx,wy);
	if(dbm.cpage->head.type>0){
		a1=(double)wx/(double)wy;
		a2=(double)dbm.cpage->head.width/(double)dbm.cpage->head.height;
		if(a1>a2)
		{
			cobj.curzoom=(double)wy/(double)dbm.cpage->head.height;
		}else{
			cobj.curzoom=(double)wx/(double)dbm.cpage->head.width;
		}
		ComputMaxXY();
		dx=xmax/2;
		dy=ymax/2;
	}else{
	  cobj.curzoom=1;
	  ComputMaxXY();
	  dx=0;
	  dy=0;
	}
}

void TestWin::pqjs(int i)
{
	N_FLOW *flw;
	flw=r_fw[i].flw;
	if(flw->style==0) return;  //无需动态显示
	if(flw->direct==0){
		flw->rf.pjs++;
		flw->rf.qjs++;
		if(flw->rf.pjs>31)	flw->rf.pjs=0;
		if(flw->rf.qjs>31)	flw->rf.qjs=0;
	}else{
		flw->rf.pjs--;
		flw->rf.qjs--;
		if(flw->rf.pjs<0)	flw->rf.pjs=31;
		if(flw->rf.qjs<0)	flw->rf.qjs=31;
	}
}
