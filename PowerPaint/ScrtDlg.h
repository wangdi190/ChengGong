#if !defined(AFX_SCRTDLG_H__590AC2D9_321E_4ABF_81C6_4687290B0958__INCLUDED_)
#define AFX_SCRTDLG_H__590AC2D9_321E_4ABF_81C6_4687290B0958__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScrtDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// ScrtDlg dialog

class ScrtDlg : public CDialog
{
// Construction
public:
	ScrtDlg(char *str,int n,CWnd* pParent = NULL);   // standard constructor
	char *p;
	int count;
// Dialog Data
	//{{AFX_DATA(ScrtDlg)
	enum { IDD = IDD_SCRTEXT };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ScrtDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(ScrtDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCRTDLG_H__590AC2D9_321E_4ABF_81C6_4687290B0958__INCLUDED_)
