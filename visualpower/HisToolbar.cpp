// HisToolbar.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "HisToolbar.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// HisToolbar

HisToolbar::HisToolbar()
{
	CFont font;
	color=GetSysColor(COLOR_3DFACE);
	font.CreateFont(16,8,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"宋体" );
	font.GetLogFont(&lf);
	font.DeleteObject();
	mdc.Create(1,1);
	mdc1.Create(1,1);
	img.Create(IDB_BITMAP3,8,0,RGB(0xc0c0c0,0xc0c0c0,0xc0c0c0));
	hour=0;min=0;sec=0;
	year=1980;
	mon=1;
	day=1;
	cursp=5;
}

HisToolbar::~HisToolbar()
{
}


BEGIN_MESSAGE_MAP(HisToolbar, CToolBar)
	//{{AFX_MSG_MAP(HisToolbar)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_WINDOWPOSCHANGED()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// HisToolbar message handlers

void HisToolbar::OnSize(UINT nType, int cx, int cy) 
{
	CRect rt;
	CToolBar::OnSize(nType, cx, cy);
	GetItemRect(0,&rt); 
	rt1=rt;
	GetItemRect(12,&rt); 
	rt2=rt;
	GetItemRect(3,&rt); 
	rt3=rt;
	rt3.top+=3;
	rt3.bottom-=3;
	rw=rt2.Width();
	rh=rt2.Height();
	mdc.SizeChange(rw,rh);
	mdc1.SizeChange(rt1.Width(),rt1.Height());
}

void HisToolbar::OnPaint() 
{
	CRect rt;
	CToolBar::OnPaint();
	CClientDC dc(this);
	GLRectc(mdc1.m_hDC,rt1,0x7f7f7f,color,0);
	mdc1.BitBltRect(dc.m_hDC,rt1,rt1);
	cobj.simg.Draw(&dc,13,CPoint(rt1.left+3,rt1.top+2),ILD_NORMAL);
	ShowSegTime(dc.m_hDC);
	ShowSpeed(dc.m_hDC);
}



void HisToolbar::showdigit(CDC&dc, int x,int y,int d)
{
	int c1,c2;
	c1=d/10;
	c2=d%10;
	img.Draw(&dc,c1,CPoint(x,y),ILD_NORMAL);
	img.Draw(&dc,c2,CPoint(x+10,y),ILD_NORMAL);
}


//显示时段
void HisToolbar::ShowSegTime(HDC hdc)
{
	char p[100];
	CRect rt;
	CDC dc;
	LOGFONT lf1;
	dc.Attach(mdc.m_hDC);
	mdc.FillBG(color);
	rt=CRect(0,0,rw,rh);
	rt.left+=2;
	dc.FillSolidRect(rt,0);
	dc.Draw3dRect(rt,0,0xffffff);
	rt.left+=4;
	rt.top+=11;
	showdigit(dc, rt.left,rt.top,hour);
	rt.left+=18;
	img.Draw(&dc,10,CPoint(rt.left,rt.top),ILD_NORMAL);
	rt.left+=10;
	showdigit(dc, rt.left,rt.top,min);
	rt.left+=18;
	img.Draw(&dc,10,CPoint(rt.left,rt.top),ILD_NORMAL);
	rt.left+=10;
	showdigit(dc, rt.left,rt.top,sec);
	rt=CRect(0,0,rw,rh);
	rt.bottom=rt.top+12;
	rt.left+=6;
	lf1=lf;
	lf1.lfHeight=-12;
	lf1.lfWidth=0;
	GetDateStr(p);
	GLDDrawText(dc.m_hDC,&rt,&lf1,p,0xff00,0,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	mdc.BitBltRect(hdc,CRect(0,0,rw,rh),rt2);
	dc.Detach();
}

//返回日期串
void HisToolbar::GetDateStr(char *str)
{
	char p2[20],p3[20];
	GetDtStr(mon,p2);
	GetDtStr(day,p3);
	sprintf(str,"%d-%s-%s",year,p2,p3);
}

void HisToolbar::SetDate(int y, int m, int d,int h, int m1, int s)
{
	year=y;
	mon=m;
	day=d;
	hour=h;
	min=m1;
	sec=s;
	ReDraw();
}




void HisToolbar::ReDraw()
{
	CClientDC dc(this);
	ShowSegTime(dc.m_hDC);
}
//显示速度
void HisToolbar::ShowSpeed(HDC hdc)
{
	int w,h;

	CRect rt;
	CDC dc;
	dc.Attach(mdc.m_hDC);
	mdc.FillBG(color);
	w=rt2.Width();
	h=rt2.Height();

	rt=CRect(0,0,w,h);
	rt.left+=2;
	dc.FillSolidRect(rt,0);
	dc.Draw3dRect(rt,0,0xffffff);
	rt.left+=4;
	rt.top+=3;
	showdigit(dc, rt.left,rt.top,cursp);
	rt=CRect(0,0,rw,rh);
	rt.bottom=rt.top+12;
	rt.left+=6;
	mdc.BitBltRect(hdc,CRect(0,0,w,h),rt3);
	dc.Detach();
}

void HisToolbar::SetSpeed(int sp)
{
	cursp=sp<0 ? 0:sp;
	cursp=sp>60 ? 60:sp;
	CClientDC dc(this);
	ShowSpeed(dc.m_hDC);
}

void HisToolbar::OnWindowPosChanged(WINDOWPOS FAR* lpwndpos) 
{
	CToolBar::OnWindowPosChanged(lpwndpos);
	if(IsFloating())
	{
		CWnd * pw=((CWnd* )m_pDockBar)->GetParent();
		pw->ModifyStyle(WS_SYSMENU,0,0);
	}
	
}
