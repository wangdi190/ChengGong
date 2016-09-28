#if !defined(AFX_CFGALMDLG_H__B221C4EC_061A_41D4_92D2_02636CF78ABC__INCLUDED_)
#define AFX_CFGALMDLG_H__B221C4EC_061A_41D4_92D2_02636CF78ABC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CfgAlmDlg.h : header file
//
#include "pwptdef.h"
#include "visualdb.h"
#include "readrltd.h"
#include "PublicAvcDef.h"
/////////////////////////////////////////////////////////////////////////////
// CCfgAlmDlg dialog

class CCfgAlmDlg : public CDialog
{
// Construction
public:
	CCfgAlmDlg(CWnd* pParent = NULL);   // standard constructor
	ALMSAVE tmp;
	int cursel;
	common_PreLimit  lmt[7];	//预警的7个阀值
	int  lmtsum;
	ReadRltD rrd;				//数据库读取对象
// Dialog Data
	//{{AFX_DATA(CCfgAlmDlg)
	enum { IDD = IDD_PRECFGDLG };
	CListBox	m_lst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCfgAlmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCfgAlmDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeList1();
	afx_msg void OnSound();
	afx_msg void OnPop();
	afx_msg void OnFlash();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SaveCfg();
	void GetParam();
	void SetParam();
	void SetCurAalm();
	void SetChange();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFGALMDLG_H__B221C4EC_061A_41D4_92D2_02636CF78ABC__INCLUDED_)
