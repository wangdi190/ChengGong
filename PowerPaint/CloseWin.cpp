// CloseWin.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "CloseWin.h"
#include "jhsyslibl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern CImageList  othimg;
/////////////////////////////////////////////////////////////////////////////
// CCloseWin

CCloseWin::CCloseWin()
{
	CFont cfnt;
	cfnt.CreateFont(16,8,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"宋体" );
	cfnt.GetLogFont(&lf);
	cfnt.DeleteObject();
}

CCloseWin::~CCloseWin()
{
}


BEGIN_MESSAGE_MAP(CCloseWin, CWnd)
	//{{AFX_MSG_MAP(CCloseWin)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CCloseWin message handlers

BOOL CCloseWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))	return FALSE;
	//cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW),NULL, NULL);
	return TRUE;
}

void CCloseWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
}

void CCloseWin::OnPaint() 
{
	CPaintDC dc(this); 
	dc.FillSolidRect(CRect(0,0,wx,wy),0xffffff);
	dc.Draw3dRect(CRect(0,0,wx,wy),0,0);
	othimg.Draw(&dc,2,CPoint(3,3),ILD_NORMAL);
	GLDDrawText(dc.m_hDC,CRect(32,1,wx-1,wy-1),&lf,"点击这里关闭测试窗口...",
		0,0,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
}

BOOL CCloseWin::Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd) 
{
	WNDCLASS wndcls;
	wnd=pParentWnd;
	memset(&wndcls, 0,sizeof(WNDCLASS));   
    wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hCursor = NULL;
	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpszClassName ="popupwin";
	AfxRegisterClass(&wndcls);
	return CreateEx (0, "popupwin","", dwStyle,rt.left,rt.top,rt.Width(),rt.Height(),pParentWnd->m_hWnd,NULL);
}

void CCloseWin::OnClose() 
{
	CWnd::OnClose();
}

void CCloseWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	wnd->PostMessage(WM_CLOSE,0);
	CWnd::OnLButtonUp(nFlags, point);
}
