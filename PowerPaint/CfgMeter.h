#if !defined(AFX_CFGMETER_H__BDFEB8DB_C19C_4E68_972B_A13EED9BD245__INCLUDED_)
#define AFX_CFGMETER_H__BDFEB8DB_C19C_4E68_972B_A13EED9BD245__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CfgMeter.h : header file
//
#include "ptdefine.h"
/////////////////////////////////////////////////////////////////////////////
// CCfgMeter dialog

class CCfgMeter : public CDialog
{
// Construction
public:
	CCfgMeter(CWnd* pParent = NULL);   // standard constructor
	N_ELEGRPYB tmp;
// Dialog Data
	//{{AFX_DATA(CCfgMeter)
	enum { IDD = IDD_YBDBSRC };
	CComboBox	m_ds;
	CListCtrl	m_lst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCfgMeter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCfgMeter)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnDbsrc();
	afx_msg void OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnPaint();
	afx_msg void OnUserdef();
	afx_msg void OnDeluser();
	afx_msg void OnModiparam();
	afx_msg void OnModicolor1();
	afx_msg void OnModicolor2();
	afx_msg void OnSelchangeDs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void  GetAlarmPam();
	void  SetVallist(int i);
	float GetItemData(int id);
	void SetItemData(int id,float val);
	void ShowColor(int id, DWORD color);
	void EnableItem(int id, bool enable);
	void SetDefPam(int i);
	void DrawMeter();
	void ShowMeter();
	void SetList();
	void GetTName(int type,int xs,char *nm1,char *nm2);
	CRect rt;
	CDIB mdc;
	int sw,sh;
	int ejlh;	//图源ID
	int sel;//当前选择的仪表
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFGMETER_H__BDFEB8DB_C19C_4E68_972B_A13EED9BD245__INCLUDED_)
