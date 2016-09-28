// NavWin.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "NavWin.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj  cobj;		//公共对象
/////////////////////////////////////////////////////////////////////////////
// CNavWin

CNavWin::CNavWin()
{
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

CNavWin::~CNavWin()
{
}


BEGIN_MESSAGE_MAP(CNavWin, CWnd)
	//{{AFX_MSG_MAP(CNavWin)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_SETCURSOR()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CNavWin message handlers

BOOL CNavWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

void CNavWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	if(cx>100&&cy>100)
	{
		wx=cx;
		wy=cy;
		ComputDWin();
	}
	
}

void CNavWin::OnPaint() 
{
	CPaintDC dc(this); 
	dc.FillSolidRect(CRect(0,0,wx,wy),0xffffff);
	Show(dc);
}

int CNavWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	
	return 0;
}

BOOL CNavWin::Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd) 
{
	WNDCLASS wndcls;
	memset(&wndcls, 0,sizeof(WNDCLASS));   
    wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hCursor = NULL;
	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpszClassName ="popupwin";
	AfxRegisterClass(&wndcls);
	return CreateEx (WS_EX_TOPMOST|WS_EX_DLGMODALFRAME|WS_EX_TOOLWINDOW    , "popupwin","",dwStyle,rt.left,rt.top,rt.Width(),rt.Height(),pParentWnd->m_hWnd,NULL);
}

void CNavWin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	dnbz=1;
	SetCapture();
	pt1=point;
	cobj.dbm->msdwn=1;
	CWnd::OnLButtonDown(nFlags, point);
}

void CNavWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	dnbz=0;
	ReleaseCapture();
	cobj.dbm->msdwn=0;
	if(cobj.dbm->scf.showdgx==1)
	{
		cobj.swin->sct.DrawDgxinMem(cobj.swin->msr,cobj.dbm->curzoom,cobj.swin->dx,cobj.swin->dy);
	}
	cobj.swin->CreateAllrgn();
	cobj.swin->EndShow();

	CWnd::OnLButtonUp(nFlags, point);
}

void CNavWin::OnMouseMove(UINT nFlags, CPoint point) 
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
			dzm=(double)cobj.dbm->zw/dwx;
			cobj.swin->dx=(int)(-dzm*dx);
			cobj.swin->dy=(int)(-dzm*dy);
			cobj.swin->DrawShow();
			cobj.swin->ComputZCenter();
			crt=CRect(dx,dy,dx+w,dy+h);
			Show(dc);
			pt1=point;
		}
	}
	CWnd::OnMouseMove(nFlags, point);
}

BOOL CNavWin::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(nHitTest == HTCLIENT)
	{
		if(cursor==1)
		{
		   SetCursor(cobj.hcur[0]);
		   return TRUE;
		};
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}


//计算本画布的宽高
void CNavWin::ComputDWin()
{
	double a1,a2;
	a1=wx/(double)wy;
	a2=cobj.dbm->page.head.width/(double)cobj.dbm->page.head.height;
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

void CNavWin::ShowBg()
{
	double zm=cobj.dbm->curzoom;
	dzm=(double)dwx/(double)(cobj.dbm->page.head.width);
	cobj.dbm->curzoom=dzm;
	cobj.swin->Set3DEnv();//设置3D环境
	CRect rt=CRect(0,0,dwx,dwy);
	cobj.dbm->ShowBkgd(mdc,rt);
	cobj.dbm->ShowStatic(mdc,0,0,rt);
	cobj.dbm->curzoom=zm;
}


void CNavWin::Show(CDC &dc)
{
	CRect rt;
	int w1,h1,a;
	DWORD color;
	tmp.CopyDIB(mdc);
	w1=crt.Width()/4;
	h1=crt.Height()/4;
	a=w1>h1 ? h1:w1;
	color=cobj.dbm->page.head.BgColor;
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
void CNavWin::ZoomChange()
{
	ComputCrt();
	if(!IsWindowVisible()) return;


	CClientDC dc(this);
	Show(dc);
}

void CNavWin::MoveCvs()
{
	ZoomChange();
}
//计算镜头矩形
void CNavWin::ComputCrt()
{
	dzm=(double)dwx/cobj.dbm->zw;
	dx=-(int)(cobj.swin->dx*dzm);
	dy=-(int)(cobj.swin->dy*dzm);
	w=(int)(cwx*dzm);
	h=(int)(cwy*dzm);
	crt=CRect(dx,dy,dx+w,dy+h);
}

void CNavWin::GetCursor(CPoint point)
{
	CRect rt;
	rt=crt;
	rt.OffsetRect(ddx,ddy);
	if(rt.PtInRect(point)) cursor=1;
	else cursor=0;
}


//画布窗口发生变化
void CNavWin::WinSizeChange(int cx, int cy)
{
	if(cx==0||cy==0) return;
	if(m_hWnd==0)    return;
	cwx=cx;
	cwy=cy;
	ComputCrt();
	CClientDC dc(this);
	Show(dc);
}

void CNavWin::PageChange()
{
	ComputDWin();
	ComputCrt();
	Invalidate();
}

void CNavWin::OnClose() 
{
	ShowWindow(SW_HIDE);
	
	//CWnd::OnClose();
}
