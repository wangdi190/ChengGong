#if !defined(AFX_ZONEDLG_H__213581A6_249C_467C_A8C3_5159FA3AC0EC__INCLUDED_)
#define AFX_ZONEDLG_H__213581A6_249C_467C_A8C3_5159FA3AC0EC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ZoneDlg.h : header file
//

#include "visualdb.h"
/////////////////////////////////////////////////////////////////////////////
// CZoneDlg dialog

class CZoneDlg : public CDialog
{
// Construction
public:
	CZoneDlg(CWnd* pParent = NULL);   // standard constructor
	~CZoneDlg();
	char dbfile[256]; //数据库名
	visualpw_Zone *zone;		  //区域
	int  num;
	int  mode;
	bool dbok;
// Dialog Data
	//{{AFX_DATA(CZoneDlg)
	enum { IDD = IDD_DEVZONE };
	CComboBox	m_mode;
	CListCtrl	m_lst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CZoneDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CZoneDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCreate();
	afx_msg void OnDelete();
	afx_msg void OnModi();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AppendData(visualpw_Zone &tmp);
	void ModiData(int i,visualpw_Zone&tmp);
	bool IsExistID(int id);
	void SetToList();
	void GetData();
	void ModeChange();
	void EnableItem(int id,bool enable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ZONEDLG_H__213581A6_249C_467C_A8C3_5159FA3AC0EC__INCLUDED_)
