#if !defined(AFX_SPIWIN_H__5C9D8406_75C4_4713_8B9E_B71D301E4BBC__INCLUDED_)
#define AFX_SPIWIN_H__5C9D8406_75C4_4713_8B9E_B71D301E4BBC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// spiwin.h : header file
//
#include "jhsyslibl.h"
/////////////////////////////////////////////////////////////////////////////
// spiwin window

class spiwin : public CWnd
{
// Construction
public:
	spiwin();
	CMenu menu;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(spiwin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReOpen();
	virtual ~spiwin();

	// Generated message map functions
protected:
	//{{AFX_MSG(spiwin)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnAddspic();
	afx_msg void OnOpenspic();
	afx_msg void OnSavespic();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDelspic();
	afx_msg void OnDelnouse();
	afx_msg void OnCopytodesk();
	afx_msg void OnDefptn();
	afx_msg void OnDefact();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool DeleteAPIC(int recno);
	int  colornums(int bits);
	void SaveGGP(char *filename);
	void LoadGGP(char *filename);
	void AddImg(char *filename);
	void SetYScroll();
	void computpage();
	void ShowAimg(int index, CRect &rt);
	void ShowImg();
	int wx,wy;
	CScrollBar   yscroll;
	CDIB mdc;
	int pgsum,curpg,selpic;
	LOGFONT lf;
	int maxy;
	int dx,dy;
	
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SPIWIN_H__5C9D8406_75C4_4713_8B9E_B71D301E4BBC__INCLUDED_)
