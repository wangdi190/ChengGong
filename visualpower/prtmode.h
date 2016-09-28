#if !defined(AFX_PRTMODE_H__7B9530F6_93BF_4A09_8F8E_FB2B74540CCB__INCLUDED_)
#define AFX_PRTMODE_H__7B9530F6_93BF_4A09_8F8E_FB2B74540CCB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// prtmode.h : header file
//
typedef struct _PMODE{
	int mode;
	int px;
}PMODE;
/////////////////////////////////////////////////////////////////////////////
// prtmode dialog

class prtmode : public CDialog
{
// Construction
public:
	prtmode(PMODE *lppm,CWnd* pParent = NULL);   // standard constructor
	PMODE *pm;
// Dialog Data
	//{{AFX_DATA(prtmode)
	enum { IDD = IDD_PRTDLG };
	CComboBox	m_com2;
	CComboBox	m_com1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(prtmode)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(prtmode)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_PRTMODE_H__7B9530F6_93BF_4A09_8F8E_FB2B74540CCB__INCLUDED_)
