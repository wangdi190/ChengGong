#if !defined(AFX_FIRSTDLG_H__6F5B6D0C_7867_4BC9_BA55_771E51823CFE__INCLUDED_)
#define AFX_FIRSTDLG_H__6F5B6D0C_7867_4BC9_BA55_771E51823CFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FirstDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// FirstDlg dialog

#include "resource.h"
//#include "PhraseXml.h"
#include "aseDlg.h"
#include "MyListCtrl.h"

class FirstDlg : public CDialog
{
// Construction
public:
	FirstDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(FirstDlg)
	enum { IDD = IDD_FIRST_DIALOG };
	CListCtrl	m_listcase;
	CEdit	m_edit_description;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FirstDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(FirstDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnRclickListCase(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickListCase(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeleteCase();
	afx_msg void OnModifyCase();
	afx_msg void OnAddCase();
	afx_msg void OnPaint();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	//PhraseXml m_xml;
	void EnumCaseFolder();
	void Init();
	BOOL DeleteDirectory(char* psDirName);
	void CheckRuntype();

	CString m_szPath;

	int m_nSelectedItem;//ÓÒ¼üÑ¡ÖÐÏî
	CString m_szSelectedName, m_szSelectedDescription;
	bool m_bAdd;
	CBitmap m_capbitmap;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FIRSTDLG_H__6F5B6D0C_7867_4BC9_BA55_771E51823CFE__INCLUDED_)
