#if !defined(AFX_FACDIALOG_H__686B49E2_A787_4472_A183_6712EBB5E223__INCLUDED_)
#define AFX_FACDIALOG_H__686B49E2_A787_4472_A183_6712EBB5E223__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FacDialog.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CFacDialog dialog

class CFacDialog : public CDialog
{
// Construction
public:
	CFacDialog(CWnd* pParent = NULL);   // standard constructor
	~CFacDialog();   // standard constructor

	void LoadZoneInfo();
	void LoadStationInfo();
	int m_stationnum;
	visualpw_Station* m_pstation;
// Dialog Data
	//{{AFX_DATA(CFacDialog)
	enum { IDD = IDD_DIALOG_FAC };
	CListCtrl	m_faclist;
	CComboBox	m_ComZone;
	CComboBox	m_ComGroup;
	CString	m_zone;
	CString	m_group;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFacDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CFacDialog)
	virtual void OnOK();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickListStation(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditControl();
	afx_msg void OnChangeEditGroup();
	afx_msg void OnButtonChange();
	afx_msg void OnSelchangeComboGroup();
	afx_msg void OnSelchangeComboZone();
	afx_msg void OnReflesh();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FACDIALOG_H__686B49E2_A787_4472_A183_6712EBB5E223__INCLUDED_)
