#if !defined(AFX_SELREVDLG_H__E173A093_E5F0_439F_8EAF_66388594C0EA__INCLUDED_)
#define AFX_SELREVDLG_H__E173A093_E5F0_439F_8EAF_66388594C0EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelRevDlg.h : header file
//
#include "mstruct.h"
/////////////////////////////////////////////////////////////////////////////
// SelRevDlg dialog

class SelRevDlg : public CDialog
{
// Construction
public:
	SelRevDlg(CWnd* pParent = NULL);   // standard constructor
	~SelRevDlg();
	SELRESERVOIR ad;
	DEVDEF *def;
	int num;
// Dialog Data
	//{{AFX_DATA(SelRevDlg)
	enum { IDD = IDD_SELRESVR };
	CListBox	m_lst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelRevDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelRevDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int  GetIndex(int id);
	void SetToLst();
	void GetData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELREVDLG_H__E173A093_E5F0_439F_8EAF_66388594C0EA__INCLUDED_)
