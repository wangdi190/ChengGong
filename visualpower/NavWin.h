#if !defined(AFX_NAVWIN_H__92869E53_9632_46F5_8E30_1C9F4DB42373__INCLUDED_)
#define AFX_NAVWIN_H__92869E53_9632_46F5_8E30_1C9F4DB42373__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NavWin.h : header file
//
#include "jhsyslibl.h"
#include "gdata.h"
/////////////////////////////////////////////////////////////////////////////
// CNavWin window

class CNavWin : public CWnd
{
// Construction
public:
	CNavWin();

// Attributes
public:

// Operations
public:
	void MoveCvs();
	void ZoomChange();
	void WinSizeChange(int cx, int cy);
	void PageChange();
	BOOL Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CNavWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CNavWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CNavWin)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	
	
	void GetCursor(CPoint point);
	void ComputCrt();
	
	
	void Show(CDC &dc);
	void ShowBg();
	void ComputDWin();
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

#endif // !defined(AFX_NAVWIN_H__92869E53_9632_46F5_8E30_1C9F4DB42373__INCLUDED_)
