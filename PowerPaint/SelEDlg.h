#if !defined(AFX_SELEDLG_H__A36B0536_507D_4905_B828_5B1835DA01D7__INCLUDED_)
#define AFX_SELEDLG_H__A36B0536_507D_4905_B828_5B1835DA01D7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelEDlg.h : header file
//
#include "jhsyslibl.h"

typedef struct ELEM{
	int jlh;
	WORD id;
}ELEM;
/////////////////////////////////////////////////////////////////////////////
// SelEDlg dialog

class SelEDlg : public CDialog
{
// Construction
public:
	SelEDlg(CWnd* pParent = NULL);   // standard constructor
	int w,h;
	int dx;
	int selpic;
	int selid;
	CDIB mdc;

	ELEM el[128]; //×î´ó128¸ö;
	int elsum;
// Dialog Data
	//{{AFX_DATA(SelEDlg)
	enum { IDD = IDD_SELELEGRP };
	CScrollBar	m_scr;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SelEDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SelEDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowEle();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELEDLG_H__A36B0536_507D_4905_B828_5B1835DA01D7__INCLUDED_)
