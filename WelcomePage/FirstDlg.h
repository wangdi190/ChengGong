#if !defined(AFX_FIRSTDLG_H__D65E2445_B392_4AE5_8B59_E1C074DEA2AF__INCLUDED_)
#define AFX_FIRSTDLG_H__D65E2445_B392_4AE5_8B59_E1C074DEA2AF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FirstDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFirstDlg dialog
#include "resource.h"

class CFirstDlg : public CDialog
{
// Construction
public:
	CFirstDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CFirstDlg)
	enum { IDD = IDD_FIRST_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFirstDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFirstDlg)
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CBitmap m_capbitmap;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRSTDLG_H__D65E2445_B392_4AE5_8B59_E1C074DEA2AF__INCLUDED_)
