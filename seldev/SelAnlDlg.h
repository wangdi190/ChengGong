#if !defined(AFX_SELANLDLG_H__D5EDC654_F89A_4AC0_8227_688C44D96AFF__INCLUDED_)
#define AFX_SELANLDLG_H__D5EDC654_F89A_4AC0_8227_688C44D96AFF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelAnlDlg.h : header file
//
#include "mstruct.h"
#include "visualdb.h"
/////////////////////////////////////////////////////////////////////////////
// SelAnlDlg dialog

class SelAnlDlg : public CDialog
{
// Construction
public:
	SelAnlDlg(CWnd* pParent = NULL);   // standard constructor
	~SelAnlDlg();
	SELDATA_DEV ad;
	DEVDEF *def,*deft;
	int num,numt;
	bool dbok;
// Dialog Data
	//{{AFX_DATA(SelAnlDlg)
	enum { IDD = IDD_SELANLDEV };
	CComboBox	m_xs;
	CListBox	m_ldev;
	CComboBox	m_dev;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelAnlDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelAnlDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDev();
	virtual void OnOK();
	afx_msg void OnChangePyjs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OrderDevByName();
	void SetDevList();
	void SetXSMode();
	int GetIndex(int id);
	void SetToLst();
	void GetData(int dtype);
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
	visualpw_SysGD *sys;
//	visualpw_Hvcondata *hvc;
	common_PreDefSF *defsf;
	common_UnEquMeas *unequ;
	common_Relation *rel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELANLDLG_H__D5EDC654_F89A_4AC0_8227_688C44D96AFF__INCLUDED_)
