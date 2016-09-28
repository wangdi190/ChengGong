#if !defined(AFX_HISTOOLBAR_H__27062D27_24C5_4AE5_8801_0524C7E70165__INCLUDED_)
#define AFX_HISTOOLBAR_H__27062D27_24C5_4AE5_8801_0524C7E70165__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// HisToolbar.h : header file
//
#include "jhsyslibl.h"
/////////////////////////////////////////////////////////////////////////////
// HisToolbar window

class HisToolbar : public CToolBar
{
// Construction
public:
	HisToolbar();
	CDIB mdc,mdc1;
// Attributes
public:

// Operations
public:
	void SetSpeed(int sp);
	void ReDraw();
	void SetDate(int y, int m, int d,int h, int m1, int s);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(HisToolbar)
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~HisToolbar();

	// Generated message map functions
protected:
	//{{AFX_MSG(HisToolbar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnWindowPosChanged(WINDOWPOS FAR* lpwndpos);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void ShowSpeed(HDC hdc);
	void GetDateStr(char *str);
	void ShowSegTime(HDC hdc);
	void showdigit(CDC&dc, int x,int y,int d);
	DWORD color;
	LOGFONT lf;
	CRect rt1,rt2,rt3;
	CImageList img;
	int rw,rh;
	int hour,min,sec; // ±∑÷√Î
	int year,mon,day; 
	int cursp;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_HISTOOLBAR_H__27062D27_24C5_4AE5_8801_0524C7E70165__INCLUDED_)
