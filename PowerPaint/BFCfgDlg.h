#if !defined(AFX_BFCFGDLG_H__8B2D7A85_8AE0_4741_9A60_CF4E071CC523__INCLUDED_)
#define AFX_BFCFGDLG_H__8B2D7A85_8AE0_4741_9A60_CF4E071CC523__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// BFCfgDlg.h : header file
//

#include "ptdefine.h"


/////////////////////////////////////////////////////////////////////////////
// BFCfgDlg dialog

class BFCfgDlg : public CDialog
{
// Construction
public:
	BFCfgDlg(CWnd* pParent = NULL);   // standard constructor
	~BFCfgDlg();
	BUSFILE *fbus;		//已关联
	GBUS    *gbus;		//图形中的BUS未关联
	int   fsum,gsum;	//关联母线个数和图形母线个数
	N_PAGEPWF  *cpage;	//当前页面地址
// Dialog Data
	//{{AFX_DATA(BFCfgDlg)
	enum { IDD = IDD_RALATEDLG };
	CComboBox	m_pno;
	CListCtrl	m_rf;
	CListBox	m_bus;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(BFCfgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(BFCfgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnAdd();
	afx_msg void OnDelete();
	afx_msg void OnOpenpwf();
	afx_msg void OnSelchangePageno();
	virtual void OnOK();
	afx_msg void OnClearra();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SaveCfg();
	void AddToListCtl();
	void DelAFbusRec(int j);
	void DelAGbusRec(int  j);
	bool IsInFBus(long id);
	bool IsInGBus(long id);
	bool AddFBus(BUSFILE &nbfile);
	void ReadCfg();
	void AddToGBusList();
	bool AddABus(GBUS &newbus);
	void GetBus();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_BFCFGDLG_H__8B2D7A85_8AE0_4741_9A60_CF4E071CC523__INCLUDED_)
