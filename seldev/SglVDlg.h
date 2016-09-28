#if !defined(AFX_SGLVDLG_H__03C44EE6_DFA1_48D4_A9D9_65E6FB777E0E__INCLUDED_)
#define AFX_SGLVDLG_H__03C44EE6_DFA1_48D4_A9D9_65E6FB777E0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SglVDlg.h : header file
//
#include "mstruct.h"
#include "visualdb.h"
/////////////////////////////////////////////////////////////////////////////
// SglVDlg dialog

class SglVDlg : public CDialog
{
// Construction
public:
	void GetData(int dtype);
	SglVDlg(CWnd* pParent = NULL);   // standard constructor
	~SglVDlg();
	SELSINGLE_DEV ad;
	DEVDEF *def;
	int num;
	bool   dbok;
	int    recno;
// Dialog Data
	//{{AFX_DATA(SglVDlg)
	enum { IDD = IDD_SVALDLG };
	CComboBox	m_xs;
	CComboBox	m_dev;
	CListBox	m_ldev;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SglVDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SglVDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDev();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int  GetIndex(int id);
	void SetXsMode();
	void SetToLst();
	visualpw_Gen *gen;
	visualpw_Line *line;
	visualpw_DCLine *dcl;
	visualpw_Bus  *bus;
	visualpw_Load *load;
	visualpw_Tfm1 *tfm1;
	visualpw_Tfm2 *tfm2;
	visualpw_Shunt *sht;
	visualpw_Sreact *srt;
	visualpw_SVC  *svc;
	visualpw_Zone *zon;
	common_PreDefSF* defsf;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SGLVDLG_H__03C44EE6_DFA1_48D4_A9D9_65E6FB777E0E__INCLUDED_)
