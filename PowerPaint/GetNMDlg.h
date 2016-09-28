#if !defined(AFX_GETNMDLG_H__3FC3D836_2A04_45B8_87B9_3AE91CB19D77__INCLUDED_)
#define AFX_GETNMDLG_H__3FC3D836_2A04_45B8_87B9_3AE91CB19D77__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetNMDlg.h : header file
//
#include "gdata.h"
/////////////////////////////////////////////////////////////////////////////
// GetNMDlg dialog

class GetNMDlg : public CDialog
{
// Construction
public:
	GetNMDlg(CWnd* pParent = NULL);   // standard constructor
	gdata *dbm;
// Dialog Data
	//{{AFX_DATA(GetNMDlg)
	enum { IDD = IDD_GETNAME };
	CStatic	m_num;
	CProgressCtrl	m_prg;
	CStatic	m_pname;
	CStatic	m_lname;
	CStatic	m_dname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GetNMDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GetNMDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void RunGet();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETNMDLG_H__3FC3D836_2A04_45B8_87B9_3AE91CB19D77__INCLUDED_)
