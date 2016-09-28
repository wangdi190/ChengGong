#if !defined(AFX_EGATRDLG_H__F053749A_E40E_498F_A3B7_BCFDA3C67FD8__INCLUDED_)
#define AFX_EGATRDLG_H__F053749A_E40E_498F_A3B7_BCFDA3C67FD8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// egatrdlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// egatrdlg dialog

class egatrdlg : public CDialog
{
// Construction
public:
	egatrdlg(int cursel,CWnd* pParent = NULL);   // standard constructor
	int sel;
// Dialog Data
	//{{AFX_DATA(egatrdlg)
	enum { IDD = IDD_EGPATTR };
	CComboBox	m_ssum;
	CComboBox	m_stype;
	CComboBox	m_type;
	CListBox	m_msg;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(egatrdlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(egatrdlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeType();
	afx_msg void OnAnalyse();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Analysedev();
	void AnalyseMeter();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EGATRDLG_H__F053749A_E40E_498F_A3B7_BCFDA3C67FD8__INCLUDED_)
