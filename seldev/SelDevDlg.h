#if !defined(AFX_SELDEVDLG_H__607DA8AF_94CD_4468_9576_2595FE33EAEA__INCLUDED_)
#define AFX_SELDEVDLG_H__607DA8AF_94CD_4468_9576_2595FE33EAEA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelDevDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// SelDevDlg dialog

class SelDevDlg : public CDialog
{
// Construction
public:
	SelDevDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(SelDevDlg)
	enum { IDD = IDD_SELDEV };
	CListCtrl	m_lst;
	CStatic	m_dtype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelDevDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelDevDlg)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELDEVDLG_H__607DA8AF_94CD_4468_9576_2595FE33EAEA__INCLUDED_)
