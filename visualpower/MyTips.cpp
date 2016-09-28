// MyTips.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "MyTips.h"
#include "jhsyslibl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// MyTips

MyTips::MyTips()
{
	CFont font;
	font.CreateFont(14,7,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
	CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
	DEFAULT_PITCH,"ËÎÌå" );
	font.GetLogFont(&lf);
	font.DeleteObject();
	str[0]=0;
	lsum=0;
}

MyTips::~MyTips()
{

}


BEGIN_MESSAGE_MAP(MyTips, CWnd)
	//{{AFX_MSG_MAP(MyTips)
	ON_WM_SIZE()
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MyTips message handlers

BOOL MyTips::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
	return CWnd::PreCreateWindow(cs);
}

void MyTips::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	wx=cx;
	wy=cy;
	
}

void MyTips::OnPaint() 
{
	int i;
	CRect rt;
	CPaintDC dc(this);
	rt=CRect(0,0,wx,wy);
	GLRectc(dc.m_hDC,rt,0xd0ffff,0xf0ffff,0);
	dc.Draw3dRect(rt,0,0);
	for(i=0;i<lsum;i++)
	{
		rt.left=5;
		rt.top=5+i*20;
		rt.right=wx-5;
		rt.bottom=rt.top+20;
	    GLDDrawText(dc.m_hDC,&rt,&lf,sl[i].str,0,0,DT_LEFT|DT_SINGLELINE);
	}
}

//ÉèÖÃ×Ö·û´®
void MyTips::SetText(char *text)
{
	CRect rt,rt1;
	int i,n,w,h,wmax,w1,h1;
	CPoint pt;
	SIZE size;
	char *lp;
	CClientDC dc(this); 
	strcpy(str,text);
	n=strlen(str);
	lsum=1;
	lp=str;
	sl[0].str=lp;
	for(i=0;i<n;i++)
	{
		if(lp[i]==0xa)
		{
			lp[i]=0;
			sl[lsum].str=lp+i+1;
			lsum++;
			if(lsum>=7) break;
		}
	}

	wmax=0;
	for(i=0;i<lsum;i++)
	{
		size=GLDGetTextSize(dc.m_hDC,&lf,sl[i].str);
		sl[i].width=size.cx;
		if(sl[i].width>wmax) wmax=sl[i].width;
	}

	hg=5+lsum*20;
	wd=wmax+10;
	GetParent()->GetClientRect(&rt);
	w=rt.Width();
	h=rt.Height();
	rt1=CRect(0,0,wd,hg);
	rt1.OffsetRect(mpt);
	w1=rt1.right-w;
	h1=rt1.bottom-h;
	pt.x=0;
	pt.y=0;
	if(w1>0) pt.x=-w1;
	if(h1>0) pt.y=-h1;
	rt1.OffsetRect(pt);
 	MoveWindow(&rt1);
	Invalidate();
}