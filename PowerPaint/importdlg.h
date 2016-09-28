#if !defined(AFX_IMPORTDLG_H__998A4ECB_1F28_403A_BE2A_C9F14383C657__INCLUDED_)
#define AFX_IMPORTDLG_H__998A4ECB_1F28_403A_BE2A_C9F14383C657__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ImportDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CImportDlg dialog

class CImportDlg : public CDialog
{
// Construction
public:
	CImportDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CImportDlg)
	enum { IDD = IDD_IMPORT_SVG };
	CListCtrl	m_lsCtrl;
	CString	m_strScr;
	CString	m_strDir;
	BOOL	m_bCheckAll;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CImportDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CImportDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnCheckAll();
	afx_msg void OnBtnscr();
	afx_msg void OnBtndir();
	afx_msg void OnClickListSvg(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeSrcpath();
	afx_msg void OnChangeDirpath();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	BOOL LoadDirSvg(char* pExt);
};

BOOL OpenDir(CWnd* parent, CString& strPath,char * strRootFolder,LPCTSTR cDlgName);

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMPORTDLG_H__998A4ECB_1F28_403A_BE2A_C9F14383C657__INCLUDED_)
