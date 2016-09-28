// SysVBar.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "SysVBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
/////////////////////////////////////////////////////////////////////////////
// CSysVBar

CSysVBar::CSysVBar()
{
	CFont cf;
	mdc.Create(1,1);
	mdc1.Create(112,28);
	color=GetSysColor(COLOR_3DFACE);
	cf.CreateFont(20,9,0,0,600,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"Gulim");
	cf.GetLogFont(&lf1);
	cf.DeleteObject();
	img.Create(IDB_BITMAP4,16,0,RGB(0,0,0));
	hour=0;min=0;sec=0;
	x=623;
	memset(&pwv,0,sizeof(PWSYSSUM));
}

CSysVBar::~CSysVBar()
{
	KillTimer(100);
}


BEGIN_MESSAGE_MAP(CSysVBar, CWnd)
	//{{AFX_MSG_MAP(CSysVBar)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CSysVBar message handlers

BOOL CSysVBar::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

int CSysVBar::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	SetTimer(100,500,NULL);
	
	return 0;
}

void CSysVBar::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	wx=cx;
	wy=cy;
	mdc.SizeChange(wx,wy);
	x=wx-113;
	x=x<623 ? 623:x;
	
}

void CSysVBar::OnPaint() 
{
	CPaintDC dc(this); 
	Show(dc);
}

void CSysVBar::OnTimer(UINT nIDEvent) 
{
	int os;
	CTime ct;
	if(nIDEvent==100&&IsWindowVisible()){
		ct=ct.GetCurrentTime();
		os=ct.GetSecond();
		if(os!=sec){
			hour=ct.GetHour();
			min=ct.GetMinute();
			sec=os;
			ShowTime();
		}
	}
	CWnd::OnTimer(nIDEvent);
}


void CSysVBar::Show(CDC &dc)
{
	char p[100];
	mdc.FillBG(color);
	mdc.CLine(CPoint(0,0),CPoint(wx,0),0xffffff);
	mdc.CRectc(CRect(0,3,wx,wy),0xffffe0,0xffffed,0);
	mdc.CDraw3DRect(CRect(0,3,wx,wy),0x7f7f7f,0xffffff);
	sprintf(p,"全局总发电有功:%2.2fMW  总发电无功:%2.2fMVar  用电负荷:P=%2.2fMW",pwv.GenP,pwv.GenQ,pwv.LoadP);
	mdc.CTextOut(p,CRect(4,6,x-10,wy-2),&lf1,0,0);
	ShowSegTime(mdc.m_hDC);
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx,wy));
}

void CSysVBar::DrawShow()
{
	CClientDC dc(this);
	Show(dc);
}

void CSysVBar::showdigit(CDC&dc, int x,int y,int d)
{
	int c1,c2;
	c1=d/10;
	c2=d%10;
	img.Draw(&dc,c1,CPoint(x,y),ILD_NORMAL);
	img.Draw(&dc,c2,CPoint(x+12,y),ILD_NORMAL);
}

//显示时段
void CSysVBar::ShowSegTime(HDC hdc)
{

	CRect rt;
	CDC dc;
	dc.Attach(mdc1.m_hDC);
	rt=CRect(0,0,112,28);
	dc.FillSolidRect(rt,0);
	rt.left+=4;
	rt.top+=2;
	showdigit(dc, rt.left,rt.top,hour);
	rt.left+=24;
	img.Draw(&dc,10,CPoint(rt.left,rt.top),ILD_NORMAL);
	rt.left+=14;
	showdigit(dc, rt.left,rt.top,min);
	rt.left+=24;
	img.Draw(&dc,10,CPoint(rt.left,rt.top),ILD_NORMAL);
	rt.left+=14;
	showdigit(dc, rt.left,rt.top,sec);
	mdc1.BitBltRect(hdc,CRect(0,0,112,28),CRect(x,4,x+112,31));
	dc.Detach();
}

//显示时间
void CSysVBar::ShowTime()
{
	CClientDC dc(this);
	ShowSegTime(dc.m_hDC);
}
