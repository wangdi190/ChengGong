#if !defined(AFX_ERRORSHOWDLG_H__25AB4737_8739_4131_B769_AF4BA6868BAA__INCLUDED_)
#define AFX_ERRORSHOWDLG_H__25AB4737_8739_4131_B769_AF4BA6868BAA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ErrorShowDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CErrorShowDlg dialog
#ifndef __AFXEXT_H__
#include <afxext.h>
#endif

#include "resource.h"

class CErrorShowDlg : public CDialog
{
// Construction
public:
	CErrorShowDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CErrorShowDlg)
	enum { IDD = IDD_ERRORSHOWDLG_DIALOG };
	CListCtrl	m_list;
	CString	m_szinfo;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CErrorShowDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CErrorShowDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
//	void ShowInfo(CString str);
	int m_iTableID;
	DWORD m_NU;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ERRORSHOWDLG_H__25AB4737_8739_4131_B769_AF4BA6868BAA__INCLUDED_)
