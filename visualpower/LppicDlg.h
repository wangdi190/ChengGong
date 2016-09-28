#if !defined(AFX_LPPICDLG_H__DEDC4C92_6666_436A_BCA5_548AAB592A48__INCLUDED_)
#define AFX_LPPICDLG_H__DEDC4C92_6666_436A_BCA5_548AAB592A48__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LppicDlg.h : header file
//
#include "pwptdef.h"
/////////////////////////////////////////////////////////////////////////////
// CLppicDlg dialog

class CLppicDlg : public CDialog
{
// Construction
public:
	CLppicDlg(CWnd* pParent = NULL);   // standard constructor
	LPPICSAVE tmp;
// Dialog Data
	//{{AFX_DATA(CLppicDlg)
	enum { IDD = IDD_CFGLPPIC };
	CListBox	m_lst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLppicDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLppicDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAddnew();
	afx_msg void OnDelsel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetList();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LPPICDLG_H__DEDC4C92_6666_436A_BCA5_548AAB592A48__INCLUDED_)
