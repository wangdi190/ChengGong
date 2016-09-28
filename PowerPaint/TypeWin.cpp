// TypeWin.cpp : implementation file
//

#include "stdafx.h"
#include "TypeWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CTypeWin

CTypeWin::CTypeWin()
{
	mdc.Create(1,1);
	wx=1;
	wy=1;
	fcolor=GetSysColor(COLOR_3DFACE);
	CFont font;
	font.CreateFont(14,7,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"宋体" );
	font.GetLogFont(&lf);
	font.DeleteObject();
	ssum=0;
	dx=0;
	cursel = 0;
}

CTypeWin::~CTypeWin()
{
}


BEGIN_MESSAGE_MAP(CTypeWin, CWnd)
	//{{AFX_MSG_MAP(CTypeWin)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CTypeWin message handlers

BOOL CTypeWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))	return FALSE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW),NULL, NULL);
	return TRUE;
}

int CTypeWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	xbar.Create(SBS_HORZ   ,CRect(0,0,1,1),this,101);
	xbar.ShowScrollBar();
	
	return 0;
}

void CTypeWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;wy=cy;
	if(wx>90&&wy>10) mdc.SizeChange(wx-80,wy);
	xbar.MoveWindow(1,0,79,wy);	
}

void CTypeWin::OnPaint() 
{
	CPaintDC dc(this); 
	mdc.FillBG(fcolor);
	Show();
	mdc.BitBltRect(dc.m_hDC,CRect(0,0,wx,wy),CRect(80,0,wx,wy));
}

//加入一个选择串
bool CTypeWin::AddSelStr(char *name, int cmd)
{
	SIZE sz;
	if(ssum>=32) return false;
	CClientDC dc(this);
	strcpy(tsl[ssum].name,name);
	tsl[ssum].COMMAND=cmd;
	tsl[ssum].sel=0;
	sz=GLDGetTextSize(dc.m_hDC,&lf,name);
	tsl[ssum].len=sz.cx+22;
	if(ssum==0) tsl[ssum].start=0;
	else tsl[ssum].start=tsl[ssum-1].start+tsl[ssum-1].len;
	ssum++;
	if(ssum>3) xbar.SetScrollRange(0,ssum-3);
	return true;
}

//设置当前选定
void CTypeWin::SetCursel(int index)
{
	int x1,x2;
	if(index<0||index>=ssum) return;
	cursel=index;
	x1=tsl[index].start-tsl[dx].start;
	x2=x1+tsl[index].len;
	if(x1>(wx-80)||x2<0) {
		dx=cursel>0 ? cursel-1:cursel;	
	};
	ReDraw();
}
//显示选择
void CTypeWin::Show()
{
	int x1,x2,i,j,k;
	POINT pt[6];
	CRect rt,rt1;
	mdc.FillBG(fcolor);
	k=tsl[dx].start;
	for(i=ssum;i>=0;i--){
		x1=tsl[i].start-k;
		x2=x1+tsl[i].len;
		rt=CRect(x1,2,x2,wy);
		rt1=CRect(x1,0,x2,wy);
		if(x1>wx) continue;
		if(x2<0)  continue;
		pt[0].x=x1-9;pt[0].y=0;
		pt[1].x=x1+9;pt[1].y=wy-2;
		pt[2].x=x2-9;pt[2].y=wy-2;
		pt[3].x=x2+9;pt[3].y=0;
		pt[4]=pt[0];
		GLPolygonc(mdc.m_hDC,pt,4,0xffffff,0xffffff,0);
		mdc.CDrawDbx(pt,5,0);
		mdc.CTextOut(tsl[i].name,rt,&lf,0,0,DT_CENTER);
	}
	//画被选中的标题
	i=cursel;
	x1=tsl[i].start-k;
	{
		x2=x1+tsl[i].len;
		rt=CRect(x1,2,x2,wy);
		rt1=CRect(x1,0,x2,wy);
		if(!(x1>wx||x2<0)){
			pt[0].x=x1-9;pt[0].y=0;
			pt[1].x=x1+10;pt[1].y=wy-1;
			pt[2].x=x2-10;pt[2].y=wy-1;
			pt[3].x=x2+9;pt[3].y=0;
			GLPolygonc(mdc.m_hDC,pt,4,0xffffff,0xffffff,0);
			for(j=4;j>0;j--) pt[j]=pt[j-1]; 
			pt[0].x=0;pt[0].y=0;
			pt[5].x=wx;pt[5].y=0;
			mdc.CDrawDbx(pt,6,0);
			mdc.CTextOut(tsl[i].name,rt,&lf,0,0,DT_CENTER);
		}
	}
}

void CTypeWin::ReDraw()
{
	CClientDC dc(this);
	mdc.FillBG(fcolor);
	Show();
	mdc.BitBltRect(dc.m_hDC,CRect(0,0,wx,wy),CRect(80,0,wx,wy));
}

void CTypeWin::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int sx,sy;
	sx=dx;
	switch(nSBCode){
	case SB_PAGEDOWN:
	case SB_LINEDOWN:
		dx=dx<ssum-2 ? dx+1:dx;	
		break;
	case SB_PAGEUP:
	case SB_LINEUP:
		dx=dx>0 ? dx-1:0;
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		dx=nPos;
		break;  
	};
	sy=dx-sx;
	if(sy!=0){
		xbar.SetScrollPos(dx);
		ReDraw();
	};
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}

void CTypeWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	int i,x,x1,x2,xp;
	if(dx<0||dx>=ssum) return;
	x=tsl[dx].start;
	xp=point.x-80;
	if(xp<0) return;
	for(i=dx;i<ssum;i++){
		x1=tsl[i].start-x;
		x2=x1+tsl[i].len;
		if(xp>x1&&xp<x2){
			cursel=i;
			ReDraw();
			GetParent()->SendMessage(WM_COMMAND,tsl[i].COMMAND);
		}
	}
	CWnd::OnLButtonUp(nFlags, point);
}
