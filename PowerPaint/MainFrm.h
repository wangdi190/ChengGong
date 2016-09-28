// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINFRM_H__1AF056DE_15DB_4EEA_8E69_C68AA15B09F4__INCLUDED_)
#define AFX_MAINFRM_H__1AF056DE_15DB_4EEA_8E69_C68AA15B09F4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MainWin.h"

class CMainFrame : public CFrameWnd
{
	
public:
	CMainFrame();
protected: 
	DECLARE_DYNAMIC(CMainFrame)

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	public:
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
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;
	CMainWin    m_wndView;
	CToolBar    tb1,tb2;	//¹¤¾ßÌõ
// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSetFocus(CWnd *pOldWnd);
	afx_msg void OnUpdateMovepic(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNormal(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePartzoom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateZoomio(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLineAdddot(CCmdUI* pCmdUI);
	afx_msg void OnUpdateLineSubdot(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCutline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBindline(CCmdUI* pCmdUI);
	afx_msg void OnUpdateClearimg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCutimg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTranimg(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePaintimg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBrightimg(CCmdUI* pCmdUI);
	afx_msg void OnUpdateSetregon(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCutregon(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditCut(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGototop(CCmdUI* pCmdUI);
	afx_msg void OnUpdateGotobuttom(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEditUndo(CCmdUI* pCmdUI);
	afx_msg void OnUpdateStraight(CCmdUI* pCmdUI);
	afx_msg void OnUpdateImgstratch(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilterGray(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilterRev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilterSmoth(CCmdUI* pCmdUI);
	afx_msg void OnUpdateFilterWl(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTranMir(CCmdUI* pCmdUI);
	afx_msg void OnUpdateTranUd(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBdBright(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBdBlk(CCmdUI* pCmdUI);
	afx_msg void OnUpdateBdBlack(CCmdUI* pCmdUI);
	afx_msg void OnUpdateCutnouse(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowguide(CCmdUI* pCmdUI);
	afx_msg void OnUpdateEgptosgl(CCmdUI* pCmdUI);
	afx_msg void OnUpdateShowsite(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNocondev(CCmdUI* pCmdUI);
	afx_msg void OnUpdateNocdev(CCmdUI* pCmdUI);
	afx_msg void OnClose();
	afx_msg void OnBastl();
	afx_msg void OnUpdateBastl(CCmdUI* pCmdUI);
	afx_msg void OnActtl();
	afx_msg void OnUpdateActtl(CCmdUI* pCmdUI);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__1AF056DE_15DB_4EEA_8E69_C68AA15B09F4__INCLUDED_)
