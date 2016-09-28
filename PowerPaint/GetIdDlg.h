#if !defined(AFX_GETIDDLG_H__A57DA00B_8BA0_47D4_A487_2F6D0A493A94__INCLUDED_)
#define AFX_GETIDDLG_H__A57DA00B_8BA0_47D4_A487_2F6D0A493A94__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GetIdDlg.h : header file
//
#include "gdata.h"
/////////////////////////////////////////////////////////////////////////////
// GetIdDlg dialog

class GetIdDlg : public CDialog
{
// Construction
public:
	GetIdDlg(CWnd* pParent = NULL);   // standard constructor
	gdata *dbm;
// Dialog Data
	//{{AFX_DATA(GetIdDlg)
	enum { IDD = IDD_GETIDDLG };
	CProgressCtrl	m_prg;
	CStatic	m_pname;
	CStatic	m_num;
	CStatic	m_lname;
	CStatic	m_dname;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GetIdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GetIdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void RunGet();
	bool GetAnlMemID(char *name,BYTE &type,int &id);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GETIDDLG_H__A57DA00B_8BA0_47D4_A487_2F6D0A493A94__INCLUDED_)
