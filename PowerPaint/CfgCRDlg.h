#if !defined(AFX_CFGCRDLG_H__E24650B9_91CA_46B9_90C2_69D879B668DC__INCLUDED_)
#define AFX_CFGCRDLG_H__E24650B9_91CA_46B9_90C2_69D879B668DC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CfgCRDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCfgCRDlg dialog

class CCfgCRDlg : public CDialog
{
// Construction
public:
	CCfgCRDlg(CWnd* pParent = NULL);   // standard constructor
	int cursel;
	BYTE R,G,B;
// Dialog Data
	//{{AFX_DATA(CCfgCRDlg)
	enum { IDD = IDD_CFGCOLOR };
	CListBox	m_vn;
	CEdit	m_r;
	CEdit	m_g;
	CEdit	m_b;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCfgCRDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCfgCRDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnChangeColorb();
	afx_msg void OnChangeColorg();
	afx_msg void OnChangeColorr();
	afx_msg void OnPallt();
	afx_msg void OnSelchangeVlname();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DWTORGB(DWORD cr);
	void ShowColor();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFGCRDLG_H__E24650B9_91CA_46B9_90C2_69D879B668DC__INCLUDED_)
