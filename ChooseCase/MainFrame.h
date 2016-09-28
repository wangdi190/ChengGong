#if !defined(AFX_MAINFRAME_H__11381ADF_39CC_4610_B2C2_F474BEADB3EE__INCLUDED_)
#define AFX_MAINFRAME_H__11381ADF_39CC_4610_B2C2_F474BEADB3EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MainFrame.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CMainFrame window
#include "ExTabWnd.h"
#include "FirstDlg.h"


class CMainFrame : public CWnd
{
// Construction
public:
	CMainFrame();

// Attributes
public:
	CBitmap m_capbitmap;
	CExTabWnd	m_tab;

	FirstDlg m_firsttab;
//	CErrorShowDlg m_errortab;
//	CModiDlg m_moditab;
	//CLineparamDlg m_linetab;
	//CTransparamDlg m_trantab;
	//CBusparamDlg m_bustab;
//	CMainDlg m_maindlg;
// Operations
public:
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRAME_H__11381ADF_39CC_4610_B2C2_F474BEADB3EE__INCLUDED_)
