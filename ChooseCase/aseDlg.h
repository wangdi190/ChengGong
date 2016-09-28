#if !defined(AFX_ASEDLG_H__B1D7B62A_6CA5_4146_95C6_8E638876F329__INCLUDED_)
#define AFX_ASEDLG_H__B1D7B62A_6CA5_4146_95C6_8E638876F329__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// aseDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CaseDlg dialog


class CaseDlg : public CDialog
{
// Construction
public:
	CaseDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CaseDlg)
	enum { IDD = IDD_CASE_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CaseDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CaseDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnBtnSave();
	afx_msg void OnBtnQuit();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	CString szName, szDescription;
	//bool b;
	
	void InitData(CString szName, CString szDescription);
	CString m_szPath;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ASEDLG_H__B1D7B62A_6CA5_4146_95C6_8E638876F329__INCLUDED_)
