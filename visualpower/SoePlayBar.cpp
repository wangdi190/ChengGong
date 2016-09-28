// SoePlayBar.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "SoePlayBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SoePlayBar

SoePlayBar::SoePlayBar()
{
	CFont font;
	color=GetSysColor(COLOR_3DFACE);
	font.CreateFont(16,8,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,DEFAULT_PITCH,"宋体" );
	font.GetLogFont(&lf);
	font.DeleteObject();
	mdc.Create(1,1);
}

SoePlayBar::~SoePlayBar()
{
}


BEGIN_MESSAGE_MAP(SoePlayBar, CToolBar)
	//{{AFX_MSG_MAP(SoePlayBar)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SoePlayBar message handlers

void SoePlayBar::OnSize(UINT nType, int cx, int cy) 
{
	CRect rt;
	CToolBar::OnSize(nType, cx, cy);
	GetItemRect(4,&rt); 
	rt1=rt;
	rt1.left+=4;
	rt1.top+=2;
	rt1.right-=4;
	rt1.bottom-=2;
	rt2=rt1;
	rt2.OffsetRect(-rt1.left,-rt1.top);
	rw=rt.Width();
	rh=rt.Height();
	mdc.SizeChange(rw,rh);	
}

void SoePlayBar::OnPaint() 
{
	char p[100];
	CRect rt;
	CToolBar::OnPaint();
	CClientDC dc(this);
	mdc.FillBG(0);
	GL3DRect(mdc.m_hDC,rt2,0);
	sprintf(p,"时间:%04d-%02d-%02d  %02d:%02d:%02d  %04d",year,mon,day,hour,min,sec,ms); //时分秒,毫秒
	rt=rt2;
	rt.left+=4;
	GLDDrawText(mdc.m_hDC,&rt,&lf,p,0xff00,0,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	mdc.BitBlt(dc.m_hDC,rt1);
}


//设置新时间
void SoePlayBar::SetNewDate(CTime &tm, int newms)
{
	char p[100];
	CRect rt;
	year=tm.GetYear();
	mon=tm.GetMonth();
	day=tm.GetDay();
	hour=tm.GetHour();
	min=tm.GetMinute();
	sec=tm.GetSecond();
	ms=newms;
	CClientDC dc(this);
	mdc.FillBG(0);
	GL3DRect(mdc.m_hDC,rt2,0);
	sprintf(p,"时间:%04d-%02d-%02d  %02d:%02d:%02d  %04d",year,mon,day,hour,min,sec,ms); //时分秒,毫秒
	rt=rt2;
	rt.left+=4;
	GLDDrawText(mdc.m_hDC,&rt,&lf,p,0xff00,0,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	mdc.BitBlt(dc.m_hDC,rt1);
}
