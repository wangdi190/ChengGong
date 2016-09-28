#if !defined(AFX_SOESELDLG_H__C9606B00_8290_43E1_AAE0_50C9D8189410__INCLUDED_)
#define AFX_SOESELDLG_H__C9606B00_8290_43E1_AAE0_50C9D8189410__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SoeSelDlg.h : header file
//
#include "pwptdef.h"
/////////////////////////////////////////////////////////////////////////////
// SoeSelDlg dialog

class SoeSelDlg : public CDialog
{
// Construction
public:
	SoeSelDlg(CWnd* pParent = NULL);   // standard constructor
	NSOES  *soe; //soeÄÚÈÝ
	int soesum;	 //soe¸öÊý
// Dialog Data
	//{{AFX_DATA(SoeSelDlg)
	enum { IDD = IDD_SOEDLG };
	CDateTimeCtrl	m_time2;
	CDateTimeCtrl	m_time1;
	CDateTimeCtrl	m_date2;
	CDateTimeCtrl	m_date1;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SoeSelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	// Generated message map functions
	//{{AFX_MSG(SoeSelDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnGetselsoe();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AutoCreateData();
	void EnableItem(int id, bool enable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOESELDLG_H__C9606B00_8290_43E1_AAE0_50C9D8189410__INCLUDED_)
