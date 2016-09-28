#if !defined(AFX_STFLWDLG_H__D3ECE396_6488_4159_ADBF_67E96A2D48C1__INCLUDED_)
#define AFX_STFLWDLG_H__D3ECE396_6488_4159_ADBF_67E96A2D48C1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StFlwDlg.h : header file
//
#include "pwptdef.h"
#include "gdata.h"

/////////////////////////////////////////////////////////////////////////////
// StFlwDlg dialog

class StFlwDlg : public CDialog
{
// Construction
public:
	StFlwDlg(CWnd* pParent = NULL);   // standard constructor
	~StFlwDlg();
	gdata *dbm;		//数据库指针
	DMSECT  tmp;    //临时存储
	DMSECT  dms[10];	//断面
	int     dmsum;	//断面数
// Dialog Data
	//{{AFX_DATA(StFlwDlg)
	enum { IDD = IDD_SECTFLOW };
	CListBox	m_lst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StFlwDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(StFlwDlg)
	virtual BOOL OnInitDialog();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	virtual void OnOK();
	afx_msg void OnSelchangeList1();
	afx_msg void OnModip();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void AddList();
	void LoadCfgS();
	void SaveCfgS();
	void EnableItem(int id,bool  enable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STFLWDLG_H__D3ECE396_6488_4159_ADBF_67E96A2D48C1__INCLUDED_)
