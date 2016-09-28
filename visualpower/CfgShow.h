#if !defined(AFX_CFGSHOW_H__D858EAA4_EAF4_462A_B2B4_985EB3C57E01__INCLUDED_)
#define AFX_CFGSHOW_H__D858EAA4_EAF4_462A_B2B4_985EB3C57E01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CfgShow.h : header file
//
#include "pwptdef.h"
/////////////////////////////////////////////////////////////////////////////
// CCfgShow dialog

class CCfgShow : public CDialog
{
// Construction
public:
	CCfgShow(CWnd* pParent = NULL);   // standard constructor
	SHOWCFG tmpcfg;
	LOGFONT lf;
	//int     pos1,pos2,pos3,pos4;
	int     curs; //当前选择的系统颜色
	int     sens; //当前灵敏度颜色序号
// Dialog Data
	//{{AFX_DATA(CCfgShow)
	enum { IDD = IDD_DISPATTR };
	CComboBox	m_senctype;
	CComboBox	m_cname;
	CComboBox	m_dgxtype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCfgShow)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CCfgShow)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnDefaultcolor();
	afx_msg void OnSelchangeDgxtype();
	afx_msg void OnKillfocusSmooth();
	afx_msg void OnKillfocusV1();
	afx_msg void OnKillfocusV2();
	afx_msg void OnKillfocusV3();
	afx_msg void OnKillfocusV4();
	afx_msg void OnKillfocusV5();
	afx_msg void OnC1();
	afx_msg void OnC2();
	afx_msg void OnC3();
	afx_msg void OnC4();
	afx_msg void OnC5();
	virtual void OnOK();
	afx_msg void OnSelchangeCname();
	afx_msg void OnModisc();
	afx_msg void OnModisc2();
	afx_msg void OnSelchangeSenctype();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetItemEnable(int id,bool enable);
	bool CmpValue(int j,float val);
	void ShowMap();
	void SetDefaultval(int i);
	void ShowVal(int id,float val);
	void ShowColor(int id,DWORD color);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CFGSHOW_H__D858EAA4_EAF4_462A_B2B4_985EB3C57E01__INCLUDED_)
