#if !defined(AFX_PRTMODE_H__AE0A4CD6_328C_43B9_8296_C4BEE36C26A4__INCLUDED_)
#define AFX_PRTMODE_H__AE0A4CD6_328C_43B9_8296_C4BEE36C26A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// PrtMode.h : header file
//
typedef struct _PMODE{
	int mode;
	int px;
}PMODE;
/////////////////////////////////////////////////////////////////////////////
// CPrtMode dialog

class CPrtMode : public CDialog
{
// Construction
public:
	CPrtMode(PMODE *lppm,CWnd* pParent = NULL);   // standard constructor
	PMODE *pm;
// Dialog Data
	//{{AFX_DATA(CPrtMode)
	enum { IDD = IDD_PRTDLG };
	CComboBox	m_com2;
	CComboBox	m_com1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPrtMode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CPrtMode)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRTMODE_H__AE0A4CD6_328C_43B9_8296_C4BEE36C26A4__INCLUDED_)
