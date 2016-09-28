#if !defined(AFX_PATRDLG_H__EB21511D_A71D_4BA8_9775_3D8B5C93A4F2__INCLUDED_)
#define AFX_PATRDLG_H__EB21511D_A71D_4BA8_9775_3D8B5C93A4F2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PatrDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// PatrDlg dialog

class PatrDlg : public CDialog
{
// Construction
public:
	PatrDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(PatrDlg)
	enum { IDD = IDD_PAGEATTR };
	CComboBox	m_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(PatrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(PatrDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PATRDLG_H__EB21511D_A71D_4BA8_9775_3D8B5C93A4F2__INCLUDED_)
