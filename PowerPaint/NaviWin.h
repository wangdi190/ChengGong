#if !defined(AFX_NAVIWIN_H__552453F3_6C6A_493F_947C_C4F9FFC71099__INCLUDED_)
#define AFX_NAVIWIN_H__552453F3_6C6A_493F_947C_C4F9FFC71099__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NaviWin.h : header file
//
#include "jhsyslibl.h"
/////////////////////////////////////////////////////////////////////////////
// NaviWin window

class NaviWin : public CWnd
{
// Construction
public:
	NaviWin();
	void PageChange();
	void ComputDWin();
	void MoveCvs();
	void WinSizeChange(int cx,int cy);
	void Objchange();
	void ZoomChange();
	void ShowBg();
	int closebz;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NaviWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~NaviWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(NaviWin)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetCursor(CPoint point);
	void Show(CDC&dc);
	void ComputCrt();
	CDIB mdc,tmp;
	int wx,wy;
	int dwx,dwy,ddx,ddy;
	int cwx,cwy;
	CRect crt;
	int dx,dy;
	double dzm;
	int cursor;
	CPoint pt1;
	int dnbz;
	int w,h;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVIWIN_H__552453F3_6C6A_493F_947C_C4F9FFC71099__INCLUDED_)
