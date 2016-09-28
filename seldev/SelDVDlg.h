#if !defined(AFX_SELDVDLG_H__B4B85E7C_E3A1_442A_B851_1271431FEF9D__INCLUDED_)
#define AFX_SELDVDLG_H__B4B85E7C_E3A1_442A_B851_1271431FEF9D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelDVDlg.h : header file
//
#include "mstruct.h"
#include "visualdb.h"
/////////////////////////////////////////////////////////////////////////////
// SelDVDlg dialog

class SelDVDlg : public CDialog
{
// Construction
public:
	SelDVDlg(CWnd* pParent = NULL);   // standard constructor
	~SelDVDlg();
	SELECTDEV sd;
	DEVDEF *def;
	int num;
	int ti;
	CFont font;
	bool dbok;
	STATION *st;
	int stsum;
	DEVDEF *deft;
	int numt;
// Dialog Data
	//{{AFX_DATA(SelDVDlg)
	enum { IDD = IDD_SELDEV };
	CListBox	m_lst2;
	CListCtrl	m_lst;
	CStatic	m_dtype;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelDVDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelDVDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnShowall();
	afx_msg void OnSelchangeList2();
	afx_msg void OnChangePyjs();
	afx_msg void OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OrderDevByID();
	void OrderDevByName();
	void OrderStationByName();
	void SetToSTLst();
	void GetStation();
	int GetItemIndex(int id);
	void GetData();
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

#endif // !defined(AFX_SELDVDLG_H__B4B85E7C_E3A1_442A_B851_1271431FEF9D__INCLUDED_)
