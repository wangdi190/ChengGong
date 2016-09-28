#if !defined(AFX_ADDFDLG_H__DDA7E905_FF1B_405E_BF1D_85C9EC09501B__INCLUDED_)
#define AFX_ADDFDLG_H__DDA7E905_FF1B_405E_BF1D_85C9EC09501B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AddFDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// AddFDlg dialog

class AddFDlg : public CDialog
{
// Construction
public:
	AddFDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(AddFDlg)
	enum { IDD = IDD_ADDFILEP };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AddFDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AddFDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ADDFDLG_H__DDA7E905_FF1B_405E_BF1D_85C9EC09501B__INCLUDED_)
