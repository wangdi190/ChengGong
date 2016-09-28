// NaviWin.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "NaviWin.h"
#include "comobj.h"
#include "gdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern gdata dbm;
extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// NaviWin

NaviWin::NaviWin()
{
	mdc.Create(1,1);
	tmp.Create(1,1);
	cwx=1;cwy=1;
	closebz=0;
	cursor=0;
	dnbz=0;
}

NaviWin::~NaviWin()
{
}


BEGIN_MESSAGE_MAP(NaviWin, CWnd)
	//{{AFX_MSG_MAP(NaviWin)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// NaviWin message handlers

BOOL NaviWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

void NaviWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	ComputDWin();
}

void NaviWin::OnPaint() 
{
	CPaintDC dc(this);
	dc.FillSolidRect(CRect(0,0,wx,wy),0xffffff);
	Show(dc);
}

void NaviWin::Show(CDC &dc)
{
	CRect rt;
	int w1,h1,a;
	DWORD color;
	tmp.CopyDIB(mdc);
	w1=crt.Width()/4;
	h1=crt.Height()/4;
	a=w1>h1 ? h1:w1;
	color=dbm.cpage->head.BgColor;
	color=color^0xffffff;
	tmp.CDrawGlass(crt,0xff0000,0xc0c0c0,1,50);
	rt=crt;
	rt.left++;
	rt.top++;
	rt.right--;
	rt.bottom--;
	CPoint pt=rt.CenterPoint();
	CPoint p1,p2;
	p1=pt;p2=pt;
	p1.Offset(-a/2,0);
	p2.Offset(a/2,0);
	tmp.CLine(p1,p2,color);
	p1=pt;p2=pt;
	p1.Offset(0,-a/2);
	p2.Offset(0,a/2);
	tmp.CLine(p1,p2,color);
	tmp.BitBltRect(dc.m_hDC,CRect(0,0,dwx,dwy),
		CRect(ddx,ddy,ddx+dwx+1,ddy+dwy+1));
}

void NaviWin::GetCursor(CPoint point)
{
	CRect rt;
	rt=crt;
	rt.OffsetRect(ddx,ddy);
	if(rt.PtInRect(point)) cursor=1;
	else cursor=0;
}

//计算镜头矩形
void NaviWin::ComputCrt()
{
	dzm=(double)dwx/dbm.cpage->zw;
	dx=-(int)(dbm.dx*dzm);
	dy=-(int)(dbm.dy*dzm);
	w=(int)(cwx*dzm);
	h=(int)(cwy*dzm);
	crt=CRect(dx,dy,dx+w,dy+h);
}

//计算本画布的宽高
void NaviWin::ComputDWin()
{
	double a1,a2;
	a1=wx/(double)wy;
	a2=dbm.cpage->head.width/(double)dbm.cpage->head.height;
	if(a1>a2){
		dwy=wy;
		dwx=(int)(dwy*a2);
		ddy=0;
		ddx=(wx-dwx)/2;
	}else{
		dwx=wx;
		dwy=(int)(dwx/a2);
		ddx=0;
		ddy=(wy-dwy)/2;
	}
	mdc.SizeChange(dwx+10,dwy+10);
	mdc.SizeChange(dwx+10,dwy+10);
	ShowBg();
}

void NaviWin::PageChange()
{
	ComputDWin();
	ZoomChange();
	Invalidate();
}

void NaviWin::MoveCvs()
{
	ZoomChange();
}

//画布窗口发生变化
void NaviWin::WinSizeChange(int cx, int cy)
{
	if(cx==0||cy==0) return;
	cwx=cx;
	cwy=cy;
	ComputCrt();
	CClientDC dc(this);
	Show(dc);
}

//对象增减
void NaviWin::Objchange()
{
	ShowBg();
	CClientDC dc(this);
	Show(dc);
}

//镜头发生变化
void NaviWin::ZoomChange()
{
	ComputCrt();
	CClientDC dc(this);
	Show(dc);
}

void NaviWin::ShowBg()
{
	double zm=cobj.curzoom;
	dzm=(double)dwx/(double)dbm.cpage->head.width;
	cobj.curzoom=dzm;
	CRect rt=CRect(0,0,dwx,dwy);
	dbm.ShowBkgd(mdc,rt);
	dbm.Showobject(mdc,0,0,rt,0);
	cobj.curzoom=zm;
}

void NaviWin::OnMouseMove(UINT nFlags, CPoint point) 
{
	int sx,sy,oldx,oldy,ax,ay;
	double dzm;
	CClientDC dc(this);
	if(dnbz==0) GetCursor(point);
	if(dnbz==1&&cursor==1){
		oldx=dx;
		oldy=dy;
		sx=point.x-pt1.x;
		sy=point.y-pt1.y;
		dx+=sx;
		dy+=sy;
		dx=dx<0 ? 0:dx;
		dy=dy<0 ? 0:dy;
		dx=(dx+w)>dwx ? dwx-w:dx;
		dy=(dy+h)>dwy ? dwy-h:dy;
		if(oldx!=dx||oldy!=dy){
			ax=dbm.dx;
			ay=dbm.dy;
			dzm=(double)dbm.cpage->zw/dwx;
			dbm.dx=(int)(-dzm*dx);
			dbm.dy=(int)(-dzm*dy);
			cobj.cvs->ScrollWindow(dbm.dx-ax,dbm.dy-ay);
			cobj.cvs->ComputZCenter();
			crt=CRect(dx,dy,dx+w,dy+h);
			Show(dc);
			pt1=point;
		}
	}
	CWnd::OnMouseMove(nFlags, point);
}

void NaviWin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	dnbz=1;
	SetCapture();
	pt1=point;
	CWnd::OnLButtonDown(nFlags, point);
}

void NaviWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	dnbz=0;
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}

BOOL NaviWin::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(nHitTest == HTCLIENT)
	 {
		if(cursor==1)
		{
		   SetCursor(cobj.hcur[2]);
		   return TRUE;
		};
	 }
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}
