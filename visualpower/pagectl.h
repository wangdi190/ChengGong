#if !defined(AFX_PAGECTL_H__927212CD_4BBB_47FD_B376_02A7D4D70045__INCLUDED_)
#define AFX_PAGECTL_H__927212CD_4BBB_47FD_B376_02A7D4D70045__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// pagectl.h : header file
//
#include "jhsyslibl.h"
/////////////////////////////////////////////////////////////////////////////
// pagectl window

class pagectl : public CWnd
{
// Construction
public:
	pagectl();
	CToolBar tb1;
	CDIB mdc;
	int dx;
	LOGFONT lf;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(pagectl)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void DrawShow();
	virtual ~pagectl();

	// Generated message map functions
protected:
	//{{AFX_MSG(pagectl)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnPagedown();
	afx_msg void OnPageup();
	afx_msg void OnRight();
	afx_msg void OnLeft();
	afx_msg void OnUpdateLeft(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePagedown(CCmdUI* pCmdUI);
	afx_msg void OnUpdatePageup(CCmdUI* pCmdUI);
	afx_msg void OnUpdateRight(CCmdUI* pCmdUI);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnTip(UINT id, NMHDR * pNMHDR, LRESULT * pResult );
	afx_msg void OnDelchild();
	afx_msg void OnUpdateDelchild(CCmdUI* pCmdUI);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int GetSelPage(CPoint point);
	void ShowOnMdc();
	int wy;
	int wx;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PAGECTL_H__927212CD_4BBB_47FD_B376_02A7D4D70045__INCLUDED_)
