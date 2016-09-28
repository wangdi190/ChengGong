#if !defined(AFX_SETHISDLG_H__832653CB_42F1_4FAF_A19F_6F4660A41F06__INCLUDED_)
#define AFX_SETHISDLG_H__832653CB_42F1_4FAF_A19F_6F4660A41F06__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SetHisDlg.h : header file
//
#include "gdata.h"
/////////////////////////////////////////////////////////////////////////////
// SetHisDlg dialog

class SetHisDlg : public CDialog
{
// Construction
public:
	SetHisDlg(CWnd* pParent = NULL);   // standard constructor
	gdata *dbm;
// Dialog Data
	//{{AFX_DATA(SetHisDlg)
	enum { IDD = IDD_CFGHIS };
	CDateTimeCtrl	m_time2;
	CDateTimeCtrl	m_time1;
	CDateTimeCtrl	m_date2;
	CDateTimeCtrl	m_date1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SetHisDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SetHisDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnGethislist();
	virtual void OnCancel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void EnableItem(int id, bool enable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SETHISDLG_H__832653CB_42F1_4FAF_A19F_6F4660A41F06__INCLUDED_)
