// layerwin.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "layerwin.h"
#include "gdata.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern gdata dbm;
extern comobj cobj;
bool EditText(char *str,int n,HWND hWndParent);
/////////////////////////////////////////////////////////////////////////////
// layerwin

layerwin::layerwin()
{
	CFont font;
	font.CreateFont(16, 8,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"ËÎÌå" );
	font.GetLogFont(&lf);
	font.DeleteObject();
	lf1=lf;
	lf1.lfHeight=12;lf1.lfWidth=6;
	mdc.Create(1,1);
	int i;
	for(i=0;i<MAXLAYER;i++) sdc[i].Create(40,30);
	dy=0;maxl=0;
	fcolor=GetSysColor(COLOR_3DFACE);
}

layerwin::~layerwin()
{
}


BEGIN_MESSAGE_MAP(layerwin, CWnd)
	//{{AFX_MSG_MAP(layerwin)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONDBLCLK()
	ON_WM_VSCROLL()
	ON_COMMAND(IDC_ADDLAYER, OnAddlayer)
	ON_COMMAND(IDC_DELCURLAYER, OnDelcurlayer)
	ON_COMMAND(IDC_GOTOP, OnGotop)
	ON_COMMAND(IDC_GOBOTTOM, OnGobottom)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// layerwin message handlers

BOOL layerwin::PreCreateWindow(CREATESTRUCT& cs) 
{
   if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

void layerwin::OnSize(UINT nType, int cx, int cy) 
{
	int n;
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	mdc.SizeChange(wx,wy);
	n=wy/40;
	n=dbm.cpage->laysum-n;
	n=n<0 ? 0:n;
	SetScrollRange(SB_VERT,0,n);
	maxl=n;
}

void layerwin::OnPaint() 
{
	CPaintDC dc(this); 
	mdc.FillBG(0xf0ffff);
	Show();
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx,wy));
}

int layerwin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	DrawLayerPic();
	
	return 0;
}

//»­Ã¿²ãÍ¼Æ¬
void layerwin::DrawLayerPic()
{
	int i;
	double oldzm;
	CRect rt;
	oldzm=cobj.curzoom;
	cobj.curzoom=40/(double)dbm.cpage->head.width;
	rt=CRect(0,0,40,30);
	for(i=0;i<dbm.cpage->laysum;i++){
	 if(i>=MAXLAYER) break;
	 dbm.ShowBkgd(sdc[i],rt);
	 dbm.ShowLayer(sdc[i],i,0,0);
	 sdc[i].CDraw3DRect(CRect(0,0,40,30),0,0);
	}
	cobj.curzoom=oldzm;
}

void layerwin::Show()
{
	int i,k;
	char p[100];
	DWORD color;
	CRect rt,rt1,rt2,rt3,rt4;
	rt.left=10;
	rt1.left=0;
	rt1.right=wx;
	rt.right=50;
	rt2.left=55;
	rt2.right=70;
	rt3.left=75;
	rt3.right=wx-4;
	for(i=0;i<dbm.cpage->laysum;i++){
		k=dy+i;
		if(k>=dbm.cpage->laysum) break;
		rt1.top=i*40;
		rt4=rt1;
		rt4.left=74;rt4.right=wx-2;
		rt4.top+=5;rt4.bottom=rt4.top+32;
		if(k==dbm.cpage->curlay) mdc.CRectc(rt4,0x7f0000,0x7f0000,0);
		rt1.bottom=rt1.top+2;
		mdc.CDraw3DRect(rt1,0x7f7f7f,0xffffff);
		
		rt.top=5+i*40;
		rt.bottom=rt.top+30;
		sdc[k].BitBltRect(mdc.m_hDC,CRect(0,0,39,29),rt);
		rt2.top=5+i*40;
		rt2.bottom=rt2.top+15;
		if(dbm.cpage->layer[k].show==0) 
		DrawFrameControl(mdc.m_hDC,&rt2,DFC_BUTTON,DFCS_BUTTONCHECK);
		else DrawFrameControl(mdc.m_hDC,&rt2,DFC_BUTTON,DFCS_CHECKED);

		rt2.top=22+i*40;
		rt2.bottom=rt2.top+15;
		if(dbm.cpage->curlay!=k) 
		DrawFrameControl(mdc.m_hDC,&rt2,DFC_BUTTON,DFCS_BUTTONRADIO);
		else DrawFrameControl(mdc.m_hDC,&rt2,DFC_BUTTON,DFCS_BUTTONRADIO|DFCS_CHECKED);

		rt3.top=5+i*40;
		rt3.bottom=rt3.top+20;
		if(k==dbm.cpage->curlay) color=0xffffff;else color=0;
		mdc.CTextOut(dbm.cpage->layer[k].name,rt3,&lf,color,0,0);
		sprintf(p,"¶ÔÏó¸öÊý:%d",dbm.cpage->layer[k].objnum);
		rt3.top=23+i*40;
		rt3.bottom=rt3.top+12;
		mdc.CTextOut(p,rt3,&lf1,color,0,0);
	}
	rt1.top=i*40;
	rt1.bottom=rt1.top+2;
	mdc.CDraw3DRect(rt1,0x7f7f7f,0xffffff);
}

void layerwin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int i,n,k,max;
	CRect rt;
	max=wy/40;
	if(point.x<55) return;
	rt.left=55;
	rt.right=70;
	for(i=0;i<max;i++){
		rt.top=5+i*40;
		rt.bottom=rt.top+15;
		if(rt.PtInRect(point)){
			n=dy+i;
			if(n>=dbm.cpage->laysum) return;
			k=dbm.cpage->layer[n].show;
			k=k==0 ? 1:0;
			dbm.cpage->layer[n].show=k;
			Invalidate();
			cobj.cvs->LayerChange();
			return;
		}
	}
	rt.right=wx;
	for(i=0;i<max;i++){
		rt.top=5+i*40;
		rt.bottom=rt.top+40;
		if(rt.PtInRect(point)){
			n=dy+i;
			if(n>=dbm.cpage->laysum) return;
			dbm.cpage->curlay=n; //¸³Óèµ±Ç°²ãºÅ
			dbm.clayer=&dbm.cpage->layer[n];
			Invalidate();
			cobj.cvs->LayerChange();
			return;
		}
	}
	CWnd::OnLButtonDown(nFlags, point);
}

void layerwin::OnLButtonDblClk(UINT nFlags, CPoint point) 
{
	int n;
	if(point.x<70) return;
	n=point.y/40+dy;
	if(n<dbm.cpage->laysum){
		EditText(dbm.cpage->layer[n].name,24,m_hWnd);
		Invalidate();
	}
	CWnd::OnLButtonDblClk(nFlags, point);
}

void layerwin::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CRect rt;
    int n,sy,ody;	
	sy=maxl;
	ody=dy;
	switch(nSBCode){
	case SB_LINEDOWN: 
		 dy=dy<sy-1 ? dy+1:sy;
		 break;
	case SB_LINEUP:
		 dy=dy>0 ? dy-1:0;
		 break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		dy=nPos;break;
	};
	n=ody-dy;
	SetScrollPos(SB_VERT,dy);
	if(n!=0) Invalidate();
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void layerwin::AddLayer()
{
	OnSize(SIZE_RESTORED,wx,wy);
}

//»­Ã¿²ãÍ¼Æ¬
void layerwin::DrawCurLayerPic()
{
	int i;
	double oldzm;
	CRect rt;
	oldzm=cobj.curzoom;
	cobj.curzoom=40/(double)dbm.cpage->head.width;
	rt=CRect(0,0,40,30);
	i=dbm.cpage->curlay;
	if(i>=MAXLAYER) return;
	dbm.ShowBkgd(sdc[i],rt);
	dbm.ShowLayer(sdc[i],i,0,0);
	sdc[i].CDraw3DRect(CRect(0,0,40,30),0,0);
	cobj.curzoom=oldzm;
}

void layerwin::OnAddlayer() 
{
	cobj.wwin->SendMessage(WM_COMMAND,IDC_ADDLAYER,0);
}

void layerwin::OnDelcurlayer() 
{
	cobj.wwin->SendMessage(WM_COMMAND,IDC_DELCURLAYER,0);
}

//Í¼²ãÖÃ¶¥
void layerwin::OnGotop() 
{
	N_layer  tmp;
	int j;
	j=dbm.cpage->curlay;
	tmp=dbm.cpage->layer[0];
	dbm.cpage->layer[0]=dbm.cpage->layer[j];
	dbm.cpage->layer[j]=tmp;
	dbm.cpage->curlay=0; //¸³Óèµ±Ç°²ãºÅ
	dbm.clayer=&dbm.cpage->layer[0];
	Invalidate();
	cobj.cvs->LayerChange();
}
//Í¼²ãÖÃµ×
void layerwin::OnGobottom() 
{
	N_layer  tmp;
	int i,j;
	i=dbm.cpage->laysum-1;
	if(i<0||i>7) return;
	j=dbm.cpage->curlay;
	tmp=dbm.cpage->layer[i];
	dbm.cpage->layer[i]=dbm.cpage->layer[j];
	dbm.cpage->layer[j]=tmp;
	dbm.cpage->curlay=i; //¸³Óèµ±Ç°²ãºÅ
	dbm.clayer=&dbm.cpage->layer[i];
	Invalidate();
	cobj.cvs->LayerChange();
}
