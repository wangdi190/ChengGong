// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__5C1B0580_8D5A_4BDE_8E6C_53A04F5D9A5F__INCLUDED_)
#define AFX_MAINFRM_H__5C1B0580_8D5A_4BDE_8E6C_53A04F5D9A5F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainWin.h"
#include "histoolbar.h"
#include "soeplaybar.h"
#include "funToolBar.h"
class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CMainWin    m_wndView;
	HisToolbar  m_hisbar;
	CToolBar    m_dmbar;
	CToolBar    m_senbar;
	SoePlayBar  m_soebar;
	CToolBar    m_mdlbar;
	FunToolBar  m_funbar;   //功能显示工具条
// Operations
public:
	void ShowHbar(int show);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	

// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnUpdateFilePrint(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMovepic(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePartzoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomio(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomnml(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNavigation(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomall(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNormal(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLasthmi(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowdgx(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSectflw(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDmflow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCfgattr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSenopr(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBussen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLinesen(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGenrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGenrevq(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowcrmap(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBasflow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowsys(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStarthis(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEndhis(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlay(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFastrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFastfw(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGototop(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePause(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCtllayer(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTranrev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSectdf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowstf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRotate(CCmdUI* pCmdUI);
	afx_msg void OnMove(int x, int y);
	afx_msg void OnUpdateApp(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLowf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateByqwd(CCmdUI* pCmdUI);
	afx_msg void OnDgxselcb();
	afx_msg void OnUpdateDgxselcb(CCmdUI* pCmdUI);
	afx_msg void OnDgxbus();
	afx_msg void OnUpdateDgxbus(CCmdUI* pCmdUI);
	afx_msg void OnDgxbushi();
	afx_msg void OnDgxbuslo();
	afx_msg void OnUpdateDgxbushi(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDgxbuslo(CCmdUI* pCmdUI);
	afx_msg void OnLineload();
	afx_msg void OnUpdateLineload(CCmdUI* pCmdUI);
	afx_msg void OnTranload();
	afx_msg void OnUpdateTranload(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNormalns(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNexthmi(CCmdUI* pCmdUI);
	afx_msg void OnFlow();
	afx_msg void OnUpdateFlow(CCmdUI* pCmdUI);
	afx_msg void OnNoflow();
	afx_msg void OnUpdateNoflow(CCmdUI* pCmdUI);
	afx_msg void OnFlowp();
	afx_msg void OnUpdateFlowp(CCmdUI* pCmdUI);
	afx_msg void OnFlowq();
	afx_msg void OnUpdateFlowq(CCmdUI* pCmdUI);
	afx_msg void OnFlowpq();
	afx_msg void OnUpdateFlowpq(CCmdUI* pCmdUI);
	afx_msg void OnFlowi();
	afx_msg void OnUpdateFlowi(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNbus(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNbusf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNflow(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNflowf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateN1all(CCmdUI* pCmdUI);
	afx_msg void OnUpdateN1allf(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDefinesect(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpenmenuwin(CCmdUI* pCmdUI);
	afx_msg void OnUpdateOpensoe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateClosesoe(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePlaysoe(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePausesoe(CCmdUI* pCmdUI);
	afx_msg void OnUpdateDldljs(CCmdUI* pCmdUI);
	afx_msg void OnUpdateMselline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBtnreturn(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZonebar(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSyspiebar(CCmdUI* pCmdUI);
	afx_msg void OnToolPaint();
	afx_msg void OnToolDbm();
	afx_msg void OnToolHisld();
	afx_msg void OnToolSect();
	afx_msg void OnUpdateToolSect(CCmdUI* pCmdUI);
	afx_msg void OnToolSe();
	afx_msg void OnUpdateToolSe(CCmdUI* pCmdUI);
	afx_msg void OnToolEm();
	afx_msg void OnUpdateToolEm(CCmdUI* pCmdUI);
	afx_msg void OnToolCasemg();
	afx_msg void OnToolEst();
	afx_msg void OnChange();
	afx_msg void OnUpdateChange(CCmdUI* pCmdUI);
	afx_msg void OnShowplate();
	afx_msg void OnUpdateShowplate(CCmdUI* pCmdUI);
	afx_msg void OnShowjxPlate();
	afx_msg void OnUpdateShowjxPlate(CCmdUI* pCmdUI);
	afx_msg void OnNoPlate();
	afx_msg void OnUpdateNoPlate(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	//gdata *dbm;
	unsigned char m_byCurDM;
	LRESULT OnMyMessage(WPARAM wParam, LPARAM lParam); 
	LRESULT OnMyMapMessage(WPARAM wParam, LPARAM lParam) ;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__5C1B0580_8D5A_4BDE_8E6C_53A04F5D9A5F__INCLUDED_)
