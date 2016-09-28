// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "VisualPower.h"
#include "comobj.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *usertype[]={"系统管理员","系统维护员","调度员","浏览用户"};
extern comobj  cobj;		//公共对象

//断面数据映射到库对象(bySect=0:SCADA断面，bySect=1:状态估计断面，bySect=2:评估断面)
int __stdcall MapSectionToObj(const void* pDB,unsigned char bySect);

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

#define WM_MY_MESSAGE (WM_USER+100) 
#define WM_MAP_MESSAGE (WM_USER+101) 

IMPLEMENT_DYNAMIC(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
	ON_WM_CREATE()
	ON_WM_SETFOCUS()
	ON_UPDATE_COMMAND_UI(ID_FILE_PRINT, OnUpdateFilePrint)
	ON_UPDATE_COMMAND_UI(ID_MOVEPIC, OnUpdateMovepic)
	ON_UPDATE_COMMAND_UI(ID_PARTZOOM, OnUpdatePartzoom)
	ON_UPDATE_COMMAND_UI(ID_ZOOMIO, OnUpdateZoomio)
	ON_UPDATE_COMMAND_UI(ID_ZOOMNML, OnUpdateZoomnml)
	ON_UPDATE_COMMAND_UI(IDC_NAVIGATION, OnUpdateNavigation)
	ON_UPDATE_COMMAND_UI(ID_ZOOMALL, OnUpdateZoomall)
	ON_UPDATE_COMMAND_UI(ID_NORMAL, OnUpdateNormal)
	ON_UPDATE_COMMAND_UI(ID_LASTHMI, OnUpdateLasthmi)
	ON_UPDATE_COMMAND_UI(IDC_SHOWDGX, OnUpdateShowdgx)
	ON_UPDATE_COMMAND_UI(IDC_SECTFLW, OnUpdateSectflw)
	ON_UPDATE_COMMAND_UI(IDC_DMFLOW, OnUpdateDmflow)
	ON_UPDATE_COMMAND_UI(IDC_CFGATTR, OnUpdateCfgattr)
	ON_UPDATE_COMMAND_UI(IDC_SENOPR, OnUpdateSenopr)
	ON_UPDATE_COMMAND_UI(IDC_BUSSEN, OnUpdateBussen)
	ON_UPDATE_COMMAND_UI(IDC_LINESEN, OnUpdateLinesen)
	ON_UPDATE_COMMAND_UI(IDC_GENREV, OnUpdateGenrev)
	ON_UPDATE_COMMAND_UI(IDC_GENREVQ, OnUpdateGenrevq)
	ON_UPDATE_COMMAND_UI(IDC_SHOWCRMAP, OnUpdateShowcrmap)
	ON_UPDATE_COMMAND_UI(IDC_BASFLOW, OnUpdateBasflow)
	ON_UPDATE_COMMAND_UI(IDC_SHOWSYS, OnUpdateShowsys)
	ON_UPDATE_COMMAND_UI(IDC_STARTHIS, OnUpdateStarthis)
	ON_UPDATE_COMMAND_UI(IDC_ENDHIS, OnUpdateEndhis)
	ON_UPDATE_COMMAND_UI(ID_PLAY, OnUpdatePlay)
	ON_UPDATE_COMMAND_UI(ID_FASTREV, OnUpdateFastrev)
	ON_UPDATE_COMMAND_UI(ID_FASTFW, OnUpdateFastfw)
	ON_UPDATE_COMMAND_UI(ID_GOTOTOP, OnUpdateGototop)
	ON_UPDATE_COMMAND_UI(ID_PAUSE, OnUpdatePause)
	ON_UPDATE_COMMAND_UI(IDC_CTLLAYER, OnUpdateCtllayer)
	ON_UPDATE_COMMAND_UI(IDC_TRANREV, OnUpdateTranrev)
	ON_UPDATE_COMMAND_UI(IDC_SECTDF, OnUpdateSectdf)
	ON_UPDATE_COMMAND_UI(IDC_SHOWSTF, OnUpdateShowstf)
	ON_UPDATE_COMMAND_UI(ID_ROTATE, OnUpdateRotate)
	ON_WM_MOVE()
	ON_UPDATE_COMMAND_UI_RANGE(39300,39500, OnUpdateApp)
	ON_UPDATE_COMMAND_UI(IDC_LOWF, OnUpdateLowf)
	ON_UPDATE_COMMAND_UI(IDC_BYQWD, OnUpdateByqwd)
	ON_COMMAND(ID_DGXSELCB, OnDgxselcb)
	ON_UPDATE_COMMAND_UI(ID_DGXSELCB, OnUpdateDgxselcb)
	ON_COMMAND(IDC_DGXBUS, OnDgxbus)
	ON_UPDATE_COMMAND_UI(IDC_DGXBUS, OnUpdateDgxbus)
	ON_COMMAND(IDC_DGXBUSHI, OnDgxbushi)
	ON_COMMAND(IDC_DGXBUSLO, OnDgxbuslo)
	ON_UPDATE_COMMAND_UI(IDC_DGXBUSHI, OnUpdateDgxbushi)
	ON_UPDATE_COMMAND_UI(IDC_DGXBUSLO, OnUpdateDgxbuslo)
	ON_COMMAND(IDC_LINELOAD, OnLineload)
	ON_UPDATE_COMMAND_UI(IDC_LINELOAD, OnUpdateLineload)
	ON_COMMAND(IDC_TRANLOAD, OnTranload)
	ON_UPDATE_COMMAND_UI(IDC_TRANLOAD, OnUpdateTranload)
	ON_UPDATE_COMMAND_UI(ID_NORMALNS, OnUpdateNormalns)
	ON_UPDATE_COMMAND_UI(IDC_NEXTHMI, OnUpdateNexthmi)
	ON_COMMAND(IDC_FLOW, OnFlow)
	ON_UPDATE_COMMAND_UI(IDC_FLOW, OnUpdateFlow)
	ON_COMMAND(IDC_NOFLOW, OnNoflow)
	ON_UPDATE_COMMAND_UI(IDC_NOFLOW, OnUpdateNoflow)
	ON_COMMAND(IDC_FLOWP, OnFlowp)
	ON_UPDATE_COMMAND_UI(IDC_FLOWP, OnUpdateFlowp)
	ON_COMMAND(IDC_FLOWQ, OnFlowq)
	ON_UPDATE_COMMAND_UI(IDC_FLOWQ, OnUpdateFlowq)
	ON_COMMAND(IDC_FLOWPQ, OnFlowpq)
	ON_UPDATE_COMMAND_UI(IDC_FLOWPQ, OnUpdateFlowpq)
	ON_COMMAND(IDC_FLOWI, OnFlowi)
	ON_UPDATE_COMMAND_UI(IDC_FLOWI, OnUpdateFlowi)
	ON_UPDATE_COMMAND_UI(IDC_NBUS, OnUpdateNbus)
	ON_UPDATE_COMMAND_UI(IDC_NBUSF, OnUpdateNbusf)
	ON_UPDATE_COMMAND_UI(IDC_NFLOW, OnUpdateNflow)
	ON_UPDATE_COMMAND_UI(IDC_NFLOWF, OnUpdateNflowf)
	ON_UPDATE_COMMAND_UI(IDC_N1ALL, OnUpdateN1all)
	ON_UPDATE_COMMAND_UI(IDC_N1ALLF, OnUpdateN1allf)
	ON_UPDATE_COMMAND_UI(IDC_DEFINESECT, OnUpdateDefinesect)
	ON_UPDATE_COMMAND_UI(IDC_OPENMENUWIN, OnUpdateOpenmenuwin)
	ON_UPDATE_COMMAND_UI(IDC_OPENSOE, OnUpdateOpensoe)
	ON_UPDATE_COMMAND_UI(IDC_CLOSESOE, OnUpdateClosesoe)
	ON_UPDATE_COMMAND_UI(IDC_PLAYSOE, OnUpdatePlaysoe)
	ON_UPDATE_COMMAND_UI(IDC_PAUSESOE, OnUpdatePausesoe)
	ON_UPDATE_COMMAND_UI(IDC_DLDLJS, OnUpdateDldljs)
	ON_UPDATE_COMMAND_UI(IDC_MSELLINE, OnUpdateMselline)
	ON_UPDATE_COMMAND_UI(ID_BTNRETURN, OnUpdateBtnreturn)
	ON_UPDATE_COMMAND_UI(IDC_ZONEBAR, OnUpdateZonebar)
	ON_UPDATE_COMMAND_UI(IDC_SYSPIEBAR, OnUpdateSyspiebar)
	ON_COMMAND(ID_TOOL_PAINT, OnToolPaint)
	ON_COMMAND(ID_TOOL_DBM, OnToolDbm)
	ON_COMMAND(ID_TOOL_HISLD, OnToolHisld)
	ON_COMMAND(ID_TOOL_SECT, OnToolSect)
	ON_UPDATE_COMMAND_UI(ID_TOOL_SECT, OnUpdateToolSect)
	ON_COMMAND(ID_TOOL_SE, OnToolSe)
	ON_UPDATE_COMMAND_UI(ID_TOOL_SE, OnUpdateToolSe)
	ON_COMMAND(ID_TOOL_EM, OnToolEm)
	ON_UPDATE_COMMAND_UI(ID_TOOL_EM, OnUpdateToolEm)
	ON_COMMAND(ID_TOOL_CASEMG, OnToolCasemg)
	ON_COMMAND(ID_TOOL_EST, OnToolEst)
	ON_COMMAND(ID_CHANGE, OnChange)
	ON_UPDATE_COMMAND_UI(ID_CHANGE, OnUpdateChange)
	ON_COMMAND(IDC_SHOWPLATE, OnShowplate)
	ON_UPDATE_COMMAND_UI(IDC_SHOWPLATE, OnUpdateShowplate)
	ON_COMMAND(IDC_SHOWJX_PLATE, OnShowjxPlate)
	ON_UPDATE_COMMAND_UI(IDC_SHOWJX_PLATE, OnUpdateShowjxPlate)
	ON_MESSAGE(WM_MY_MESSAGE, OnMyMessage) 
	ON_MESSAGE(WM_MAP_MESSAGE, OnMyMapMessage) 
	ON_COMMAND(IDC_NO_PLATE, OnNoPlate)
	ON_UPDATE_COMMAND_UI(IDC_NO_PLATE, OnUpdateNoPlate)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()
//ON_UPDATE_COMMAND_UI_RANGE(39300,39500, OnUpdateApp)
static UINT indicators[] =
{
	ID_SEPARATOR,           
	ID_SEPARATOR,
	ID_SEPARATOR,
	ID_SEPARATOR,
};

//ON_UPDATE_COMMAND_UI_RANGE(39300,39500, OnUpdateApp)
/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

LRESULT CMainFrame::OnMyMessage(WPARAM wParam, LPARAM lParam)  
{  
	char fm[256]={0};
	HISHMI newhmi;
	int index;
	cobj.swin->GetCurHmi(newhmi);
	cobj.SetToLocalFile("avcclient.pw0",fm);

	cobj.swin->FreeMem();
	cobj.dbm->OpenPwFile(fm, 0);
	cobj.swin->InitMoveObj();
	cobj.dbm->AddOpenHmi(newhmi);
	cobj.mwin->ptl.DrawShow();
	cobj.SetToNeedMode(0);  

	return NULL;  
} 

LRESULT CMainFrame::OnMyMapMessage(WPARAM wParam, LPARAM lParam) 
{
	char fm[256]={0};
	HISHMI newhmi;
	int index;
	cobj.swin->GetCurHmi(newhmi);
	cobj.SetToLocalFile("220kV潮流图.pw0",fm);
//	if(cobj.dbm->CheckFileIndex(fm,index))
//	{
		cobj.swin->FreeMem();
		cobj.dbm->OpenPwFile(fm, 0);
		cobj.swin->InitMoveObj();
		cobj.dbm->AddOpenHmi(newhmi);
		cobj.mwin->ptl.DrawShow();
		cobj.SetToNeedMode(0);  
//	}
	return NULL;  
}

CMainFrame::CMainFrame()
{
	m_byCurDM=0;		
}

CMainFrame::~CMainFrame()
{
	
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	CRect rect;
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)	return -1;

	//取地址
	cobj.fwin=this;				//框架窗口
	cobj.mwin=&m_wndView;		//主窗口
	cobj.hbar=&m_hisbar;		//历史重演工具条
	cobj.sbar=&m_wndToolBar;	//SCADA工具条
	cobj.tbar=&m_wndStatusBar;  //状态条
	cobj.dmbar=&m_dmbar;
	cobj.sebar=&m_senbar;
	cobj.ebar=&m_soebar;
	cobj.funbar=&m_funbar;
	//装入上次设置的显示属性
	
	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS |CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_funbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		|  CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_funbar.LoadToolBar(IDR_FUNBAR))
	{
		TRACE0("Failed to create function toolbar\n");
		return -1;      // fail to create
	}

	if (!m_hisbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_hisbar.LoadToolBar(IDR_HISBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_dmbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),1200) ||
		!m_dmbar.LoadToolBar(IDR_DMBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_senbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),1201) ||
		!m_senbar.LoadToolBar(IDR_SENBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_mdlbar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),1201) ||
		!m_mdlbar.LoadToolBar(IDR_MDLBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_soebar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC,CRect(0,0,0,0),1201) ||
		!m_soebar.LoadToolBar(IDR_SWSOEBAR))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndView.Create(NULL, NULL, AFX_WS_DEFAULT_VIEW,
		CRect(0, 0, 0, 0), this, AFX_IDW_PANE_FIRST, NULL))
	{
		TRACE0("Failed to create view window\n");
		return -1;
	}
	
	m_hisbar.SetButtonInfo(0,ID_SHOWTEXT,TBBS_SEPARATOR,40);
	m_hisbar.SetButtonInfo(12,ID_SHOWTEXT,TBBS_SEPARATOR,85);
	m_soebar.SetButtonInfo(4,IDC_SOEMSG,TBBS_SEPARATOR,285);
	m_funbar.SetButtonInfo(1,IDC_SOEMSG,TBBS_SEPARATOR,148);
	
	m_hisbar.EnableDocking(CBRS_ALIGN_ANY);
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	m_dmbar.EnableDocking(CBRS_ALIGN_ANY);
	m_senbar.EnableDocking(CBRS_ALIGN_ANY);
	m_soebar.EnableDocking(CBRS_ALIGN_ANY);
	m_mdlbar.EnableDocking(CBRS_ALIGN_ANY);
	m_funbar.EnableDocking(CBRS_ALIGN_ANY);

	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);
	DockControlBar(&m_funbar);
	DockControlBar(&m_hisbar);
	DockControlBar(&m_dmbar);
	DockControlBar(&m_senbar);
	DockControlBar(&m_soebar);
	DockControlBar(&m_mdlbar);


	
	RecalcLayout();
	m_wndToolBar.GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	DockControlBar(&m_funbar,(UINT)0,&rect);
	DockControlBar(&m_hisbar,(UINT)0,&rect);
	DockControlBar(&m_dmbar,(UINT)0,&rect);
	DockControlBar(&m_senbar,(UINT)0,&rect);
	DockControlBar(&m_soebar,(UINT)0,&rect);
	DockControlBar(&m_mdlbar,(UINT)0,&rect);

	
	m_wndStatusBar.SetPaneInfo(3,ID_SEPARATOR,SBPS_NORMAL,90);
	m_wndStatusBar.SetPaneInfo(2,ID_SEPARATOR,SBPS_NORMAL,200);
	m_wndStatusBar.SetPaneInfo(1,ID_SEPARATOR,SBPS_NORMAL,100);
	m_wndStatusBar.SetPaneInfo(0,ID_SEPARATOR,SBPS_STRETCH,200);

	
	
	//设置当前用户
	cobj.swin->SetStatusBarMsg();
	m_funbar.ShowWindow(SW_SHOW);
	m_hisbar.ShowWindow(SW_HIDE);
	m_dmbar.ShowWindow(SW_HIDE);
	m_senbar.ShowWindow(SW_HIDE);
	m_soebar.ShowWindow(SW_HIDE);
	m_mdlbar.ShowWindow(SW_HIDE);

	m_wndToolBar.SetWindowText("快捷操作工具");
	m_funbar.SetWindowText("功能状态工具");
	m_hisbar.SetWindowText("历史重演工具");
	m_dmbar.SetWindowText("断面潮流工具");
	m_senbar.SetWindowText("灵敏度工具");
	m_soebar.SetWindowText("开关SOE回放工具");
	m_mdlbar.SetWindowText("短路电流计算");
	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
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

void CMainFrame::ShowHbar(int show)
{
	m_hisbar.ShowWindow(show);
	RecalcLayout();
}


void CMainFrame::OnUpdateFilePrint(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
}

void CMainFrame::OnUpdateMovepic(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PCursor()==1 ? true :false);
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}

void CMainFrame::OnUpdatePartzoom(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PType()==2 ? true :false);
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}

void CMainFrame::OnUpdateZoomio(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PType()==3 ? true :false);
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}

void CMainFrame::OnUpdateZoomnml(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}

void CMainFrame::OnUpdateNavigation(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
}

void CMainFrame::OnUpdateZoomall(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}

void CMainFrame::OnUpdateNormal(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PCursor()==0 ? true :false);
}

void CMainFrame::OnUpdateLasthmi(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PCurhmi()>0 ? true:false);
}

void CMainFrame::OnUpdateShowdgx(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
	pCmdUI->SetCheck(m_wndView.PDgx()>0 ? 1:0);	
}

void CMainFrame::OnUpdateSectflw(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
	pCmdUI->SetCheck(m_wndView.PCursor()==6 ? 1:0);
}

void CMainFrame::OnUpdateDmflow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PDmflow());
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}

void CMainFrame::OnUpdateCfgattr(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(cobj.daoban==0 ? true:false);
}

void CMainFrame::OnUpdateSenopr(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PSen());
	pCmdUI->Enable(m_wndView.PType()>0&&m_wndView.PSenflag()==1&&m_wndView.PDevn(0)>0&&m_wndView.PLowf()==0 ? true:false);
}

void CMainFrame::OnUpdateBussen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
	pCmdUI->SetCheck(m_wndView.PCursor()==8 ? 1:0);
}

void CMainFrame::OnUpdateLinesen(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
	pCmdUI->SetCheck(m_wndView.PCursor()==7 ? 1:0);
}

void CMainFrame::OnUpdateGenrev(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PDevn(1)==0||m_wndView.PLowf()==1 ? false:true);
	pCmdUI->SetCheck(m_wndView.PRev()==1 ? 1:0);
}

void CMainFrame::OnUpdateGenrevq(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0&&(m_wndView.PDevn(1)>0||m_wndView.PDevn(2)>0)&&m_wndView.PLowf()==0 ? true:false);
	pCmdUI->SetCheck(m_wndView.PRev()==2 ? 1:0);
}

void CMainFrame::OnUpdateShowcrmap(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0&&m_wndView.PDgx()>0  ? true:false);
	pCmdUI->SetCheck(cobj.cwin->IsWindowVisible() ? 1:0);
}

void CMainFrame::OnUpdateBasflow(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
}

void CMainFrame::OnUpdateShowsys(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(cobj.vbar->IsWindowVisible());
}

void CMainFrame::OnUpdateStarthis(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PHdbok()==FALSE&&m_wndView.PLowf()==0&&m_wndView.PType()>0 ? true:false);
}

void CMainFrame::OnUpdateEndhis(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PHdbok()==TRUE&&m_wndView.PLowf()==0 ? true:false);
}


void CMainFrame::OnUpdatePlay(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PDbzt()==1 ? true:false);
	pCmdUI->SetCheck(m_wndView.PHisplay()==1);
}

void CMainFrame::OnUpdateFastrev(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PDbzt()==1 ? true:false);
}

void CMainFrame::OnUpdateFastfw(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PDbzt()==1 ? true:false);
}

void CMainFrame::OnUpdateGototop(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PDbzt()==1 ? true:false);
}

void CMainFrame::OnUpdatePause(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PDbzt()==1 ? true:false);
	pCmdUI->SetCheck(m_wndView.PHisplay()==0 ? 1:0);
}


void CMainFrame::OnUpdateApp(CCmdUI* pCmdUI)
{
	pCmdUI->SetCheck(0);
}

void CMainFrame::OnUpdateCtllayer(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
}

void CMainFrame::OnUpdateTranrev(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0&&m_wndView.PDevn(3)>0&&m_wndView.PLowf()==0 ? true:false);
	pCmdUI->SetCheck(m_wndView.PRev()==3 ? 1:0);
}

void CMainFrame::OnUpdateSectdf(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
	pCmdUI->SetCheck(m_wndView.PCursor()==9 ? 1:0);
}

void CMainFrame::OnUpdateShowstf(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
}



void CMainFrame::OnUpdateRotate(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PCursor()==10 ? 1:0);
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
}

void CMainFrame::OnMove(int x, int y) 
{
	CFrameWnd::OnMove(x, y);
	m_wndView.MoveChildWin();
	
}

void CMainFrame::OnUpdateLowf(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
	pCmdUI->SetCheck(m_wndView.PLowf());
}


void CMainFrame::OnUpdateByqwd(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0&&m_wndView.PDevn(3)>0 ? true:false);
	pCmdUI->SetCheck(m_wndView.PRev()==4 ? 1:0);
}

void CMainFrame::OnDgxselcb()
{
	int j;
	CPoint pt;
	CRect  rt;
	CMenu *mm;
	j=m_wndToolBar.CommandToIndex(ID_DGXSELCB);
	m_wndToolBar.GetItemRect(j,&rt);
	pt=CPoint(rt.left,31);
	ClientToScreen(&pt);
	mm=cobj.dmenu.GetSubMenu(0); //弹参数修改菜单
	mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
}

void CMainFrame::OnUpdateDgxselcb(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0&&m_wndView.PDgx()!=0 ? true:false);
}

void CMainFrame::OnDgxbus() 
{
	cobj.swin->SetCurFunction(FUN_DGXBUS);
	cobj.dbm->scf.ctrtype=0;
	m_wndView.ToolBarDgxSel();
}

void CMainFrame::OnUpdateDgxbus(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PCtrtype()==0 ? 1:0);
	
}

void CMainFrame::OnDgxbushi() 
{
	cobj.swin->SetCurFunction(FUN_DGXBUSH);
	cobj.dbm->scf.ctrtype=2;
	m_wndView.ToolBarDgxSel();
}

void CMainFrame::OnDgxbuslo() 
{
	cobj.swin->SetCurFunction(FUN_DGXBUSL);
	cobj.dbm->scf.ctrtype=1;
	m_wndView.ToolBarDgxSel();
}

void CMainFrame::OnUpdateDgxbushi(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PCtrtype()==2 ? 1:0);
}

void CMainFrame::OnUpdateDgxbuslo(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PCtrtype()==1 ? 1:0);
}

void CMainFrame::OnLineload() 
{
	cobj.swin->SetCurFunction(FUN_DGXLINE);
	cobj.dbm->scf.ctrtype=5;
	m_wndView.ToolBarDgxSel();
}

void CMainFrame::OnUpdateLineload(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PCtrtype()==5 ? 1:0);
}

void CMainFrame::OnTranload() 
{
	cobj.swin->SetCurFunction(FUN_DGXTRAS);
	cobj.dbm->scf.ctrtype=4;
	m_wndView.ToolBarDgxSel();
}

void CMainFrame::OnUpdateTranload(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PCtrtype()==4 ? 1:0);
}


void CMainFrame::OnUpdateNormalns(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PCurang()!=0 ? true:false);
}

void CMainFrame::OnUpdateNexthmi(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PCurrtn()>0 ? true:false);
}

void CMainFrame::OnFlow() 
{
	int j;
	CPoint pt;
	CRect rt;
	CMenu *mm;
	j=m_wndToolBar.CommandToIndex(IDC_FLOW);
	m_wndToolBar.GetItemRect(j,&rt);
	pt=CPoint(rt.left,31);
	ClientToScreen(&pt);
	mm=cobj.fwmenu.GetSubMenu(0); //弹参数修改菜单
	mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
}

void CMainFrame::OnNoflow(){ cobj.swin->FlowSel(0);}
void CMainFrame::OnFlowp() { cobj.swin->FlowSel(1);}
void CMainFrame::OnFlowq() { cobj.swin->FlowSel(2);}
void CMainFrame::OnFlowpq(){ cobj.swin->FlowSel(3);}
void CMainFrame::OnFlowi() { cobj.swin->FlowSel(4);}


void CMainFrame::OnUpdateFlow(CCmdUI* pCmdUI)  {	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);}
void CMainFrame::OnUpdateNoflow(CCmdUI* pCmdUI){	pCmdUI->SetCheck(m_wndView.PFtype()==0 ? 1:0);}
void CMainFrame::OnUpdateFlowp(CCmdUI* pCmdUI) {	pCmdUI->SetCheck(m_wndView.PFtype()==1 ? 1:0);}
void CMainFrame::OnUpdateFlowq(CCmdUI* pCmdUI) {	pCmdUI->SetCheck(m_wndView.PFtype()==2 ? 1:0);}
void CMainFrame::OnUpdateFlowpq(CCmdUI* pCmdUI){	pCmdUI->SetCheck(m_wndView.PFtype()==3 ? 1:0);}
void CMainFrame::OnUpdateFlowi(CCmdUI* pCmdUI) {	pCmdUI->SetCheck(m_wndView.PFtype()==4 ? 1:0);}


void CMainFrame::OnUpdateNbus(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PN1bz()==0 ? 1:0);
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}

void CMainFrame::OnUpdateNbusf(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PN1bz()==3 ? 1:0);
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}

void CMainFrame::OnUpdateNflow(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PN1bz()==1 ? 1:0);
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}

void CMainFrame::OnUpdateNflowf(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PN1bz()==4 ? 1:0);
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}

void CMainFrame::OnUpdateN1all(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PN1bz()==2 ? 1:0);
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}

void CMainFrame::OnUpdateN1allf(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PN1bz()==5 ? 1:0);
	pCmdUI->Enable(m_wndView.PType()==0||m_wndView.PLowf()==1 ? false:true);
}


void CMainFrame::OnUpdateDefinesect(CCmdUI* pCmdUI) 
{
	//pCmdUI->Enable(cobj.userlev>1 ? false:true);
	pCmdUI->Enable(false);
}

void CMainFrame::OnUpdateOpenmenuwin(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.showmnwin==1 ? 1:0);
}

void CMainFrame::OnUpdateOpensoe(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PSoebz()==1||m_wndView.PType()==0 ? false:true);
}

void CMainFrame::OnUpdateClosesoe(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PSoebz()==0 ? false:true);
}

void CMainFrame::OnUpdatePlaysoe(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PSoeSum()>0 ? true:false);
	pCmdUI->SetCheck(m_wndView.PHisplay()==2 ? 1:0);	
}

void CMainFrame::OnUpdatePausesoe(CCmdUI* pCmdUI) 
{
	pCmdUI->SetCheck(m_wndView.PHisplay()==0 ? 1:0);
}

void CMainFrame::OnUpdateDldljs(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()==0 ? false:true);
}


void CMainFrame::OnUpdateMselline(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PType()>0 ? true:false);
	pCmdUI->SetCheck(m_wndView.PCursor()==12 ? 1:0);
}

void CMainFrame::OnUpdateBtnreturn(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(cobj.dbm->page.head.type>0 ? true:false);	
	
}

void CMainFrame::OnUpdateZonebar(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PDevn(4)>0 ? true:false);
	if(m_wndView.PDevn(4)>0)
	{
		pCmdUI->SetCheck(cobj.dbm->scf.showrev==10?true:false);
	}
}

void CMainFrame::OnUpdateSyspiebar(CCmdUI* pCmdUI) 
{
	pCmdUI->Enable(m_wndView.PDevn(5)>0 ? true:false);
}

void CMainFrame::OnToolPaint() 
{
	HWND hwnd=::FindWindow(NULL,"VisualPaintGD");
	if(hwnd==NULL)
	{
		PROCESS_INFORMATION li;
		STARTUPINFO  st;
		memset(&li,0,sizeof(PROCESS_INFORMATION));
		memset(&st,0,sizeof(STARTUPINFO));
		st.cb=sizeof(STARTUPINFO);
		st.wShowWindow=SW_NORMAL;
		st.dwFlags=STARTF_USESHOWWINDOW;
		CreateProcess(NULL,"VisualPaintGD.exe",NULL,NULL,FALSE,0,NULL,NULL,&st,&li);
	}
	else
	{
		::ShowWindow(hwnd,SW_SHOWNORMAL);
	}
}

void CMainFrame::OnToolDbm()
{
	HWND hwnd=::FindWindow(NULL,"VisDBM");
	if(hwnd==NULL)
	{
		PROCESS_INFORMATION li;
		STARTUPINFO  st;
		memset(&li,0,sizeof(PROCESS_INFORMATION));
		memset(&st,0,sizeof(STARTUPINFO));
		st.cb=sizeof(STARTUPINFO);
		st.wShowWindow=SW_NORMAL;
		st.dwFlags=STARTF_USESHOWWINDOW;
		CreateProcess(NULL,"VisDBM.exe",NULL,NULL,FALSE,0,NULL,NULL,&st,&li);
	}
	else
	{
		::ShowWindow(hwnd,SW_SHOWNORMAL);
	}
}

void CMainFrame::OnToolHisld() 
{
	HWND hwnd=::FindWindow(NULL,"HisChange");
	if(hwnd==NULL)
	{
		PROCESS_INFORMATION li;
		STARTUPINFO  st;
		memset(&li,0,sizeof(PROCESS_INFORMATION));
		memset(&st,0,sizeof(STARTUPINFO));
		st.cb=sizeof(STARTUPINFO);
		st.wShowWindow=SW_NORMAL;
		st.dwFlags=STARTF_USESHOWWINDOW;
		CreateProcess(NULL,"HisChange.exe",NULL,NULL,FALSE,0,NULL,NULL,&st,&li);
	}
	else
	{
		::ShowWindow(hwnd,SW_SHOWNORMAL);
	}
}
// SecImport.lib EstDemo.lib psapi.lib 
// VisAVCPQV.lib
void CMainFrame::OnToolSect() 
{
	m_byCurDM=0;
	MapSectionToObj("visualpw",m_byCurDM);	
}

void CMainFrame::OnUpdateToolSect(CCmdUI* pCmdUI) 
{
	if(m_byCurDM==0)
		pCmdUI->SetCheck(FALSE);//暂时不使用
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnToolSe() 
{
	m_byCurDM=1;
	MapSectionToObj("visualpw",m_byCurDM);	
}

void CMainFrame::OnUpdateToolSe(CCmdUI* pCmdUI) 
{
	if(m_byCurDM==1)
		pCmdUI->SetCheck(FALSE);//暂时不使用
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnToolEm() 
{
	m_byCurDM=2;
	MapSectionToObj("visualpw",m_byCurDM);	
}

void CMainFrame::OnUpdateToolEm(CCmdUI* pCmdUI) 
{
	if(m_byCurDM==2)
		pCmdUI->SetCheck(FALSE);//暂时不使用
	else
		pCmdUI->SetCheck(FALSE);
}

void CMainFrame::OnToolCasemg() 
{
	HWND hwnd=::FindWindow(NULL,"案例管理");
	if(hwnd==NULL)
	{
		PROCESS_INFORMATION li;
		STARTUPINFO  st;
		memset(&li,0,sizeof(PROCESS_INFORMATION));
		memset(&st,0,sizeof(STARTUPINFO));
		st.cb=sizeof(STARTUPINFO);
		st.wShowWindow=SW_NORMAL;
		st.dwFlags=STARTF_USESHOWWINDOW;
		CreateProcess(NULL,"CaseManage.exe",NULL,NULL,FALSE,0,NULL,NULL,&st,&li);
	}
	else
	{
		::ShowWindow(hwnd,SW_SHOWNORMAL);
	}
}

void CMainFrame::OnToolEst() 
{
	HWND hwnd=::FindWindow(NULL,"仿真评估");
	if(hwnd==NULL)
	{
		PROCESS_INFORMATION li;
		STARTUPINFO  st;
		memset(&li,0,sizeof(PROCESS_INFORMATION));
		memset(&st,0,sizeof(STARTUPINFO));
		st.cb=sizeof(STARTUPINFO);
		st.wShowWindow=SW_NORMAL;
		st.dwFlags=STARTF_USESHOWWINDOW;
		CreateProcess(NULL,"Evaluate.exe",NULL,NULL,FALSE,0,NULL,NULL,&st,&li);
	}
	else
	{
		::ShowWindow(hwnd,SW_SHOWNORMAL);
	}
}


void CMainFrame::OnChange() 
{
	if(bShowProcessData == false)
		bShowProcessData = true;
	else
		bShowProcessData = false;
	AfxMessageBox("切换成功");

	cobj.swin->ChangeShow();
}

void CMainFrame::OnUpdateChange(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(bShowProcessData==false?0:1);
}

void CMainFrame::OnShowplate() 
{
	// TODO: Add your command handler code here
	int j;
	CPoint pt;
	CRect rt;
	CMenu *mm;
	j=m_wndToolBar.CommandToIndex(IDC_SHOWPLATE);
	m_wndToolBar.GetItemRect(j,&rt);
	pt=CPoint(rt.left,31);
	ClientToScreen(&pt);
	mm=cobj.platemenu.GetSubMenu(0); //弹参数修改菜单
	mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
}

void CMainFrame::OnUpdateShowplate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	
}

void CMainFrame::OnShowjxPlate() 
{
	// TODO: Add your command handler code here
	cobj.dbm->scf.showplate=3;
	cobj.dbm->SaveShowSet();
	cobj.swin->EndShow();
}

void CMainFrame::OnUpdateShowjxPlate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(cobj.dbm->scf.showplate==3 ? 1:0);
}

void CMainFrame::OnNoPlate() 
{
	// TODO: Add your command handler code here
	cobj.dbm->scf.showplate=0;
	cobj.dbm->SaveShowSet();
	cobj.swin->EndShow();
}

void CMainFrame::OnUpdateNoPlate(CCmdUI* pCmdUI) 
{
	// TODO: Add your command update UI handler code here
	pCmdUI->SetCheck(cobj.dbm->scf.showplate==0 ? 1:0);
}
