// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "gdata.h"
#include "comobj.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern gdata dbm;
extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_UPDATE_COMMAND_UI(ID_MOVEPIC, OnUpdateMovepic)
	ON_UPDATE_COMMAND_UI(ID_NORMAL, OnUpdateNormal)
	ON_UPDATE_COMMAND_UI(ID_PARTZOOM, OnUpdatePartzoom)
	ON_UPDATE_COMMAND_UI(ID_ZOOMIO, OnUpdateZoomio)
	ON_UPDATE_COMMAND_UI(ID_LINE_ADDDOT, OnUpdateLineAdddot)
	ON_UPDATE_COMMAND_UI(ID_LINE_SUBDOT, OnUpdateLineSubdot)
	ON_UPDATE_COMMAND_UI(ID_CUTLINE, OnUpdateCutline)
	ON_UPDATE_COMMAND_UI(ID_BINDLINE, OnUpdateBindline)
	ON_UPDATE_COMMAND_UI(ID_CLEARIMG, OnUpdateClearimg)
	ON_UPDATE_COMMAND_UI(ID_CUTIMG, OnUpdateCutimg)
	ON_UPDATE_COMMAND_UI(ID_TRANIMG, OnUpdateTranimg)
	ON_UPDATE_COMMAND_UI(ID_PAINTIMG, OnUpdatePaintimg)
	ON_UPDATE_COMMAND_UI(ID_BRIGHTIMG, OnUpdateBrightimg)
	ON_UPDATE_COMMAND_UI(ID_SETREGON, OnUpdateSetregon)
	ON_UPDATE_COMMAND_UI(ID_CUTREGON, OnUpdateCutregon)
	ON_UPDATE_COMMAND_UI(ID_EDIT_CUT, OnUpdateEditCut)
	ON_UPDATE_COMMAND_UI(ID_GOTOTOP, OnUpdateGototop)
	ON_UPDATE_COMMAND_UI(ID_GOTOBUTTOM, OnUpdateGotobuttom)
	ON_UPDATE_COMMAND_UI(ID_EDIT_UNDO, OnUpdateEditUndo)
	ON_UPDATE_COMMAND_UI(IDC_STRAIGHT, OnUpdateStraight)
	ON_UPDATE_COMMAND_UI(ID_IMGSTRATCH, OnUpdateImgstratch)
	ON_UPDATE_COMMAND_UI(ID_FILTER_GRAY, OnUpdateFilterGray)
	ON_UPDATE_COMMAND_UI(ID_FILTER_REV, OnUpdateFilterRev)
	ON_UPDATE_COMMAND_UI(ID_FILTER_SMOTH, OnUpdateFilterSmoth)
	ON_UPDATE_COMMAND_UI(ID_FILTER_WL, OnUpdateFilterWl)
	ON_UPDATE_COMMAND_UI(ID_TRAN_MIR, OnUpdateTranMir)
	ON_UPDATE_COMMAND_UI(ID_TRAN_UD, OnUpdateTranUd)
	ON_UPDATE_COMMAND_UI(ID_BD_BRIGHT, OnUpdateBdBright)
	ON_UPDATE_COMMAND_UI(ID_BD_BLK, OnUpdateBdBlk)
	ON_UPDATE_COMMAND_UI(ID_BD_BLACK, OnUpdateBdBlack)
	ON_UPDATE_COMMAND_UI(IDC_CUTNOUSE, OnUpdateCutnouse)
	ON_UPDATE_COMMAND_UI(IDC_SHOWGUIDE, OnUpdateShowguide)
	ON_UPDATE_COMMAND_UI(IDC_EGPTOSGL, OnUpdateEgptosgl)
	ON_UPDATE_COMMAND_UI(IDC_SHOWSITE, OnUpdateShowsite)
	ON_UPDATE_COMMAND_UI(IDC_NOCONDEV, OnUpdateNocondev)
	ON_UPDATE_COMMAND_UI(IDC_NOCDEV, OnUpdateNocdev)
	ON_WM_CLOSE()
	ON_COMMAND(IDC_BASTL, OnBastl)
	ON_UPDATE_COMMAND_UI(IDC_BASTL, OnUpdateBastl)
	ON_COMMAND(IDC_ACTTL, OnActtl)
	ON_UPDATE_COMMAND_UI(IDC_ACTTL, OnUpdateActtl)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
	cobj.mwin=&m_wndView;
	
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect rect;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	// create a view to occupy the client area of the frame
	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!tb1.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!tb1.LoadToolBar(IDR_BASGRP))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!tb2.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!tb2.LoadToolBar(IDR_ACTGRP))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	m_wndStatusBar.SetPaneInfo(4,ID_SEPARATOR,SBPS_NORMAL,160);
	m_wndStatusBar.SetPaneInfo(3,ID_SEPARATOR,SBPS_NORMAL,320);
	m_wndStatusBar.SetPaneInfo(2,ID_SEPARATOR,SBPS_NORMAL,140);
	m_wndStatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_NORMAL,100);
	m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_STRETCH,300);

	m_wndStatusBar.SetPaneText(2," 放缩比例:1倍");
	m_wndStatusBar.SetPaneText(3,"visualpw");

	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	tb1.EnableDocking(CBRS_ALIGN_ANY);
	
	tb2.EnableDocking(CBRS_ALIGN_ANY);
	
	tb1.SetWindowText("基本工具栏");
	tb2.SetWindowText("活动工具栏");
	m_wndToolBar.SetWindowText("操作工具栏");

	RecalcLayout();
	m_wndToolBar.GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	DockControlBar(&tb1,(UINT)0,&rect);
	DockControlBar(&tb2,(UINT)0,&rect);
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	cs.style = WS_OVERLAPPED | WS_CAPTION | FWS_ADDTOTITLE
		| WS_THICKFRAME | WS_SYSMENU | WS_MINIMIZEBOX | WS_MAXIMIZEBOX | WS_MAXIMIZE;

	cs.dwExStyle &= ~WS_EX_CLIENTEDGE;
	cs.lpszClass = AfxRegisterWndClass(0);
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers
void CMainFrame::OnSetFocus(CWnd* pOldWnd)
{
	// forward focus to the view window
	m_wndView.SetFocus();
}

BOOL CMainFrame::OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo)
{
	// let the view have first crack at the command
	if (m_wndView.OnCmdMsg(nID, nCode, pExtra, pHandlerInfo))
		return TRUE;

	// otherwise, do default handling
	return CFrameWnd::OnCmdMsg(nID, nCode, pExtra, pHandlerInfo);
}


void CMainFrame::OnUpdateMovepic(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(cobj.cursor==102 ? true:false);
}

void CMainFrame::OnUpdateNormal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(cobj.cursor==0 ? 1:0);
}

void CMainFrame::OnUpdatePartzoom(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(cobj.cursor==103 ? true:false);
}

void CMainFrame::OnUpdateZoomio(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(cobj.cursor==104 ? 1:0);
}

void CMainFrame::OnUpdateLineAdddot(CCmdUI* pCmdUI) 
{
	bool b1=false;
	b1|=dbm.SelIsThisType(1);
	b1|=dbm.SelIsThisType(16);
	b1|=dbm.SelIsThisType(77);
	b1|=dbm.SelIsThisType(78);
	b1|=dbm.SelIsThisType(83);
	b1&=dbm.selbz==1 ? true:false;
	pCmdUI->Enable(b1);
	pCmdUI->SetCheck(cobj.cursor==106 ? 1:0);
}

void CMainFrame::OnUpdateLineSubdot(CCmdUI* pCmdUI) 
{
	bool b1=false;
	b1|=dbm.SelIsThisType(1);
	b1|=dbm.SelIsThisType(16);
	b1|=dbm.SelIsThisType(77);
	b1|=dbm.SelIsThisType(78);
	b1|=dbm.SelIsThisType(83);
	b1&=dbm.selbz==1 ? true:false;
	pCmdUI->Enable(b1);
	pCmdUI->SetCheck(cobj.cursor==107 ? 1:0);
}

void CMainFrame::OnUpdateCutline(CCmdUI* pCmdUI) 
{
	bool b1=false;
	b1|=dbm.SelIsThisType(1);
	b1|=dbm.SelIsThisType(16);
	b1|=dbm.SelIsThisType(77);
	b1|=dbm.SelIsThisType(78);
	b1&=dbm.selbz==1 ? true:false;
	pCmdUI->Enable(b1);
	pCmdUI->SetCheck(cobj.cursor==108 ? 1:0);
}

void CMainFrame::OnUpdateBindline(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.CanBindlineSel());
}

void CMainFrame::OnUpdateClearimg(CCmdUI* pCmdUI) 
{
	bool nb;
	if(cobj.curzoom==1) nb=true;else false;
	pCmdUI->Enable(dbm.SelIsThisType(15)&nb);
}

void CMainFrame::OnUpdateCutimg(CCmdUI* pCmdUI) 
{
	bool nb;
	if(cobj.curzoom==1) nb=true;else false;
	pCmdUI->Enable(dbm.SelIsThisType(15)&nb);
}

void CMainFrame::OnUpdateTranimg(CCmdUI* pCmdUI) 
{
	bool nb;
	if(cobj.curzoom==1) nb=true;else false;
	pCmdUI->Enable(dbm.SelIsThisType(15)&nb);
}

void CMainFrame::OnUpdatePaintimg(CCmdUI* pCmdUI) 
{
	bool nb;
	if(cobj.curzoom==1) nb=true;else false;
	pCmdUI->Enable(dbm.SelIsThisType(15)&nb);
}

void CMainFrame::OnUpdateBrightimg(CCmdUI* pCmdUI) 
{
	bool nb;
	if(cobj.curzoom==1) nb=true;else false;
	pCmdUI->Enable(dbm.SelIsThisType(15)&nb);
}

void CMainFrame::OnUpdateSetregon(CCmdUI* pCmdUI) 
{
	bool nb;
	if(cobj.curzoom==1) nb=true;else false;
	pCmdUI->Enable(dbm.SelIsThisType(15)&nb);
}

void CMainFrame::OnUpdateCutregon(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.selrgn);
}

void CMainFrame::OnUpdateEditCut(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.selbz>0 ? true:false);
}

void CMainFrame::OnUpdateGototop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.selbz>0 ? true:false);
}

void CMainFrame::OnUpdateGotobuttom(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.selbz>0 ? true:false);
}

void CMainFrame::OnUpdateEditUndo(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(cobj.unp.curstep>0 ? 1:0);
}



void CMainFrame::OnUpdateStraight(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.selbz> 0 ? true:false);
}

void CMainFrame::OnUpdateImgstratch(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(15));
}

void CMainFrame::OnUpdateFilterGray(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(15));
}


void CMainFrame::OnUpdateFilterRev(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(15));
}

void CMainFrame::OnUpdateFilterSmoth(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(15));
}

void CMainFrame::OnUpdateFilterWl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(15));
}

void CMainFrame::OnUpdateTranMir(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(15));
}

void CMainFrame::OnUpdateTranUd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(15));
}

void CMainFrame::OnUpdateBdBright(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(15));
}

void CMainFrame::OnUpdateBdBlk(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(15));
}

void CMainFrame::OnUpdateBdBlack(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(15));
}

void CMainFrame::OnUpdateCutnouse(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(15));
}

void CMainFrame::OnUpdateShowguide(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(cobj.gshow==1 ? true:false);
}

void CMainFrame::OnUpdateEgptosgl(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(dbm.SelIsThisType(66)||dbm.SelIsThisType(67));
}

void CMainFrame::OnUpdateShowsite(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(cobj.showsite);
}

void CMainFrame::OnUpdateNocondev(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(cobj.nocondev);
}

void CMainFrame::OnUpdateNocdev(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(cobj.nocdev);
}

void CMainFrame::OnClose() 
{
	int result;
	if(dbm.editbz==1){
	  result=MessageBox("编辑数据发生变化, 是否需要保存?\n按[否]将丢失数据.",
		"提示",MB_YESNOCANCEL);
	  if(result==IDYES)	cobj.wwin->OnFileSave();
	  if(result==IDCANCEL) return;
	}
	CFrameWnd::OnClose();
}



void CMainFrame::OnBastl() 
{
	if(tb1.IsWindowVisible()) tb1.ShowWindow(SW_HIDE);
	else tb1.ShowWindow(SW_SHOW);
	RecalcLayout();
	
}

void CMainFrame::OnUpdateBastl(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(tb1.IsWindowVisible()==TRUE ? 1:0);
	
}

void CMainFrame::OnActtl() 
{
	if(tb2.IsWindowVisible()) tb2.ShowWindow(SW_HIDE);
	else tb2.ShowWindow(SW_SHOW);
	RecalcLayout();
}

void CMainFrame::OnUpdateActtl(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(tb2.IsWindowVisible()==TRUE ? 1:0);
}

void CMainFrame::OnSize(UINT nType, int cx, int cy) 
{
	CFrameWnd::OnSize(nType, cx, cy);
	
	RecalcLayout();
}
