#if !defined(AFX_CONFIGTRANS_H__49487009_A606_4BA2_AC2F_9E257008C41A__INCLUDED_)
#define AFX_CONFIGTRANS_H__49487009_A606_4BA2_AC2F_9E257008C41A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConfigTrans.h : header file
//
#include "middll.h"
#include "readrltd.h"
/////////////////////////////////////////////////////////////////////////////
// CConfigTrans dialog

class CConfigTrans : public CDialog
{
// Construction
public:
	CConfigTrans(CWnd* pParent = NULL);   // standard constructor
	ReadRltD *rrd;
// Dialog Data
	//{{AFX_DATA(CConfigTrans)
	enum { IDD = IDD_DIALOG_CFGTRA };
	CListBox	m_lstShow;
	CListBox	m_lstHide;
	int		m_iType;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CConfigTrans)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CConfigTrans)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonAdd();
	afx_msg void OnButtonDel();
	afx_msg void OnRadioType();
	afx_msg void OnRadioType2();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void LoadTrans();
	SHOW_EQU m_show[400];
	int m_shownum;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CONFIGTRANS_H__49487009_A606_4BA2_AC2F_9E257008C41A__INCLUDED_)
