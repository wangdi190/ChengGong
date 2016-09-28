#if !defined(AFX_CHRGWIN_H__ED5B7C6D_F744_4EA5_BF1C_972831619FD3__INCLUDED_)
#define AFX_CHRGWIN_H__ED5B7C6D_F744_4EA5_BF1C_972831619FD3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChrgWin.h : header file
//
#include "pwptdef.h"
/////////////////////////////////////////////////////////////////////////////
// CChrgWin window

class CChrgWin : public CWnd
{
// Construction
public:
	CChrgWin();
	SHOWCFG *scf;
	int wx,wy;
	CDIB mdc;
// Attributes
public:

// Operations
public:
	void ReDraw();
	BOOL Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChrgWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChrgWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChrgWin)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LOGFONT lf;
	void Show(CDC&dc);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHRGWIN_H__ED5B7C6D_F744_4EA5_BF1C_972831619FD3__INCLUDED_)
