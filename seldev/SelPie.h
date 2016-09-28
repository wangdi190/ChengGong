#if !defined(AFX_SELPIE_H__3EC0430C_BCDC_4626_9673_4BB52EBF83E4__INCLUDED_)
#define AFX_SELPIE_H__3EC0430C_BCDC_4626_9673_4BB52EBF83E4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelPie.h : header file
//
#include "mstruct.h"
#include "visualdb.h"
/////////////////////////////////////////////////////////////////////////////
// CSelPie dialog

class CSelPie : public CDialog
{
// Construction
public:
	CSelPie(CWnd* pParent = NULL);   // standard constructor
	~CSelPie();
	SELECTPIE ad;
	DEVDEF *def;
	int num;
	bool dbok;
// Dialog Data
	//{{AFX_DATA(CSelPie)
	enum { IDD = IDD_SELPIE };
	CListBox	m_lst;
	CComboBox	m_type;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelPie)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelPie)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeCombo1();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int GetIndex(int id);
	void SetToList();
	void GetData();
	visualpw_Line *line;
	visualpw_DCLine *dcl;
	visualpw_Gen *gen;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELPIE_H__3EC0430C_BCDC_4626_9673_4BB52EBF83E4__INCLUDED_)
