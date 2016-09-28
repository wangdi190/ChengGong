#if !defined(AFX_YBSELDLG_H__46485A69_2D2C_4D8B_AE0B_57502FF789A9__INCLUDED_)
#define AFX_YBSELDLG_H__46485A69_2D2C_4D8B_AE0B_57502FF789A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YbSelDlg.h : header file
//
#include "mstruct.h"
#include "visualdb.h"
/////////////////////////////////////////////////////////////////////////////
// YbSelDlg dialog

class YbSelDlg : public CDialog
{
// Construction
public:
	YbSelDlg(CWnd* pParent = NULL);   // standard constructor
	~YbSelDlg();

	DEVDEF *def;
	int num;

	SINGLEDBS tmp;
// Dialog Data
	//{{AFX_DATA(YbSelDlg)
	enum { IDD = IDD_YBSELDLG };
	CComboBox	m_yb;
	CComboBox	m_fld;
	CListBox	m_devlst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(YbSelDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(YbSelDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeYbsel();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetData(int dtype);
	void SetToLst();
	void SetXsMode();
	int  GetIndex(int id);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YBSELDLG_H__46485A69_2D2C_4D8B_AE0B_57502FF789A9__INCLUDED_)
