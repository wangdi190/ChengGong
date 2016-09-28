#if !defined(AFX_FUNTOOLBAR_H__5C8C7C0C_A474_4FEC_9125_A131CD8A016C__INCLUDED_)
#define AFX_FUNTOOLBAR_H__5C8C7C0C_A474_4FEC_9125_A131CD8A016C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// FunToolBar.h : header file
//
#include "jhsyslibl.h"
/////////////////////////////////////////////////////////////////////////////
// FunToolBar window

class FunToolBar : public CToolBar
{
// Construction
public:
	FunToolBar();
	CRect rt;
	int curft;		//当前功能号
// Attributes
public:
	void ReDrawNewFt();
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(FunToolBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~FunToolBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(FunToolBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void Showft();
	DWORD color;
	LOGFONT lf;
	CRect rt1,rt2;
	int rw,rh;
	CDIB mdc;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FUNTOOLBAR_H__5C8C7C0C_A474_4FEC_9125_A131CD8A016C__INCLUDED_)
