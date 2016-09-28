// NavgDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "NavgDlg.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern comobj  cobj;		//公共对象

/////////////////////////////////////////////////////////////////////////////
// NavgDlg dialog


NavgDlg::NavgDlg(CWnd* pParent /*=NULL*/)
	: CDialog(NavgDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(NavgDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	tmp.Create(320,240);
	mdc.Create(320,240);
	wx=320;
	wy=240;
	dwx=1;
	dwy=1;
	ddx=1;
	ddy=1;
	cwx=1;
	cwy=1;
	crt=CRect(0,0,1,1);
	dx=1;
	dy=1;
	dzm=1;
	cursor=0;
	pt1=CPoint(1,1);
	dnbz=0;
	w=1;
	h=1;
}


void NavgDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(NavgDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(NavgDlg, CDialog)
	//{{AFX_MSG_MAP(NavgDlg)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// NavgDlg message handlers

void NavgDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(cx>100&&cy>100)
	{
		wx=cx;
		wy=cy;
		ComputDWin();
	}
	
}

void NavgDlg::OnPaint() 
{
	CPaintDC dc(this);
	Show(dc);
}

void NavgDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	dnbz=1;
	SetCapture();
	pt1=point;
	dbm->msdwn=1;
	CDialog::OnLButtonDown(nFlags, point);
}

void NavgDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	dnbz=0;
	ReleaseCapture();
	dbm->msdwn=0;
	if(dbm->scf.showdgx==1){
			cobj.swin->sct.DrawDgxinMem(dbm->curzoom,cobj.swin->dx,cobj.swin->dy);
	}
	cobj.swin->CreateAllrgn();
	cobj.swin->EndShow();
	CDialog::OnLButtonUp(nFlags, point);
}

void NavgDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	int sx,sy,oldx,oldy,ax,ay;
	double dzm;
	CClientDC dc(this);
	if(dnbz==0) GetCursor(point);
	if(dx<0||dy<0) return;

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
			ax=cobj.swin->dx;
			ay=cobj.swin->dy;
			dzm=(double)dbm->zw/dwx;
			cobj.swin->dx=(int)(-dzm*dx);
			cobj.swin->dy=(int)(-dzm*dy);
			cobj.swin->DrawShow();
			cobj.swin->ComputZCenter();
			crt=CRect(dx,dy,dx+w,dy+h);
			Show(dc);
			pt1=point;
		}
	}
	CDialog::OnMouseMove(nFlags, point);
}

BOOL NavgDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(nHitTest == HTCLIENT)
	 {
		if(cursor==1)
		{
		   SetCursor(cobj.hcur[0]);
		   return TRUE;
		};
	   }
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

//计算本画布的宽高
void NavgDlg::ComputDWin()
{
	double a1,a2;
	a1=wx/(double)wy;
	a2=dbm->page.head.width/(double)dbm->page.head.height;
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

void NavgDlg::ShowBg()
{
	double zm=dbm->curzoom;
	dzm=(double)dwx/(double)(dbm->page.head.width);
	dbm->curzoom=dzm;
	Set3DEnv(dbm->curang,dwx,dwy,dbm->lookdown);//设置3D环境
	CRect rt=CRect(0,0,dwx,dwy);
	dbm->ShowBkgd(mdc,rt);
	dbm->ShowStatic(mdc,0,0,rt);
	dbm->curzoom=zm;
	Set3DEnv(dbm->curang,dbm->zw,dbm->zh,dbm->lookdown);//设置3D环境
}

void NavgDlg::Show(CDC &dc)
{
	CRect rt;
	int w1,h1,a;
	DWORD color;
	tmp.CopyDIB(mdc);
	w1=crt.Width()/4;
	h1=crt.Height()/4;
	a=w1>h1 ? h1:w1;
	color=dbm->page.head.BgColor;
	color=color^0xffffff;
	tmp.CDrawGlass(crt,0xff0000,0xc0c0c0,1,50);
	rt=crt;
	rt.left++;
	rt.top++;
	rt.right--;
	rt.bottom--;
	tmp.CLine(CPoint(rt.left,rt.top),CPoint(rt.left+a,rt.top),color);
	tmp.CLine(CPoint(rt.left,rt.top),CPoint(rt.left,rt.top+a),color);

	tmp.CLine(CPoint(rt.right,rt.top),CPoint(rt.right-a,rt.top),color);
	tmp.CLine(CPoint(rt.right,rt.top),CPoint(rt.right,rt.top+a),color);

	tmp.CLine(CPoint(rt.left,rt.bottom),CPoint(rt.left+a,rt.bottom),color);
	tmp.CLine(CPoint(rt.left,rt.bottom),CPoint(rt.left,rt.bottom-a),color);

	tmp.CLine(CPoint(rt.right,rt.bottom),CPoint(rt.right-a,rt.bottom),color);
	tmp.CLine(CPoint(rt.right,rt.bottom),CPoint(rt.right,rt.bottom-a),color);
	CPoint pt=rt.CenterPoint();
	CPoint p1,p2;
	p1=pt;p2=pt;
	p1.Offset(-a/2,0);
	p2.Offset(a/2+1,0);
	tmp.CLine(p1,p2,color);
	p1=pt;p2=pt;
	p1.Offset(0,-a/2);
	p2.Offset(0,a/2+1);
	tmp.CLine(p1,p2,color);
	tmp.BitBltRect(dc.m_hDC,CRect(0,0,dwx,dwy),
		CRect(ddx,ddy,ddx+dwx+1,ddy+dwy+1));
}

//镜头发生变化
void NavgDlg::ZoomChange()
{
	ComputCrt();
	CClientDC dc(this);
	Show(dc);
}

void NavgDlg::MoveCvs()
{
	ZoomChange();
}
//计算镜头矩形
void NavgDlg::ComputCrt()
{
	dzm=(double)dwx/dbm->zw;
	dx=-(int)(cobj.swin->dx*dzm);
	dy=-(int)(cobj.swin->dy*dzm);
	w=(int)(cwx*dzm);
	h=(int)(cwy*dzm);
	crt=CRect(dx,dy,dx+w,dy+h);
}

void NavgDlg::GetCursor(CPoint point)
{
	CRect rt;
	rt=crt;
	rt.OffsetRect(ddx,ddy);
	if(rt.PtInRect(point)) cursor=1;
	else cursor=0;
}


//画布窗口发生变化
void NavgDlg::WinSizeChange(int cx, int cy)
{
	if(cx==0||cy==0) return;
	if(m_hWnd==0)    return;
	cwx=cx;
	cwy=cy;
	ComputCrt();
	CClientDC dc(this);
	Show(dc);
}

void NavgDlg::PageChange()
{
	ComputDWin();
	ComputCrt();
	Invalidate();
}
