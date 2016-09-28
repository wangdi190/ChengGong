#if !defined(AFX_CFGZMDLG_H__DABA9700_5F60_4064_85F5_E708BE20F5B1__INCLUDED_)
#define AFX_CFGZMDLG_H__DABA9700_5F60_4064_85F5_E708BE20F5B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CfgZmDlg.h : header file
//
#include "ptdefine.h" 
/////////////////////////////////////////////////////////////////////////////
// CCfgZmDlg dialog

class CCfgZmDlg : public CDialog
{
// Construction
public:
	CCfgZmDlg(CWnd* pParent = NULL);   // standard constructor
	N_APDINFO tmp;
// Dialog Data
	//{{AFX_DATA(CCfgZmDlg)
	enum { IDD = IDD_ZOOMDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCfgZmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCfgZmDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnFromfm1();
	afx_msg void OnFromfm2();
	virtual void OnOK();
	afx_msg void OnZoomin();
	afx_msg void OnZoomout();
	afx_msg void OnDefzm1();
	afx_msg void OnDefzm2();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void EnableAll();
	void SetItemEnable(int id,bool enable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFGZMDLG_H__DABA9700_5F60_4064_85F5_E708BE20F5B1__INCLUDED_)
