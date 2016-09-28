#if !defined(AFX_LAYERWIN_H__31E08E2D_8EF3_4B9E_86D5_B8431C6C36F0__INCLUDED_)
#define AFX_LAYERWIN_H__31E08E2D_8EF3_4B9E_86D5_B8431C6C36F0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// layerwin.h : header file
//
#include "jhsyslibl.h"
#include "ptdefine.h"
/////////////////////////////////////////////////////////////////////////////
// layerwin window

class layerwin : public CWnd
{
// Construction
public:
	layerwin();
	int wx,wy;
// Attributes
public:

// Operations
public:
	void DrawCurLayerPic();
	void DrawLayerPic();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(layerwin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void AddLayer();
	virtual ~layerwin();

	// Generated message map functions
protected:
	//{{AFX_MSG(layerwin)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnAddlayer();
	afx_msg void OnDelcurlayer();
	afx_msg void OnGotop();
	afx_msg void OnGobottom();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Show();
	LOGFONT lf,lf1;
	CDIB mdc;
	CDIB sdc[MAXLAYER];
	int dy,maxl;
	DWORD fcolor;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERWIN_H__31E08E2D_8EF3_4B9E_86D5_B8431C6C36F0__INCLUDED_)
