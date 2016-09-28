#if !defined(AFX_STADLG_H__AA167297_9154_4366_B602_1AABC484EB28__INCLUDED_)
#define AFX_STADLG_H__AA167297_9154_4366_B602_1AABC484EB28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// StaDlg.h : header file
//
#include "mstruct.h"
#include "visualdb.h"
/////////////////////////////////////////////////////////////////////////////
// StaDlg dialog

class StaDlg : public CDialog
{
// Construction
public:
	StaDlg(CWnd* pParent = NULL);   // standard constructor
	~StaDlg();
	SELSINGLE_DEV ad;
	DEVDEF *def;
	int num;
	bool dbok;
// Dialog Data
	//{{AFX_DATA(StaDlg)
	enum { IDD = IDD_SELSTA };
	CListBox	m_ldev;
	CComboBox	m_dev;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(StaDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(StaDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeDev();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int  GetIndex(int id);
	void GetData(int dtype);
	void SetToLst();
	visualpw_PT *pt;
	visualpw_Switch *swt;
	visualpw_GND *gnd;
	visualpw_CVT *cvt;
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

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_STADLG_H__AA167297_9154_4366_B602_1AABC484EB28__INCLUDED_)
