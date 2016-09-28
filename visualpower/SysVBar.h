#if !defined(AFX_SYSVBAR_H__136984FB_C2B4_4E6D_BC41_A29D1C114240__INCLUDED_)
#define AFX_SYSVBAR_H__136984FB_C2B4_4E6D_BC41_A29D1C114240__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SysVBar.h : header file
//
#include "jhsyslibl.h"
#include "pwptdef.h"
/////////////////////////////////////////////////////////////////////////////
// CSysVBar window

class CSysVBar : public CWnd
{
// Construction
public:
	CSysVBar();
	//系统统计值
	PWSYSSUM  pwv;
	int wx,wy;
	DWORD color;
// Attributes
public:

// Operations
public:
	void DrawShow();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSysVBar)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CSysVBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(CSysVBar)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void Show(CDC&dc);
	void ShowTime();
	void ShowSegTime(HDC hdc);
	void showdigit(CDC&dc, int x,int y,int d);
	LOGFONT lf1;
	CImageList img;
	int hour,min,sec; //时分秒
	CDIB mdc,mdc1;
	int x;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SYSVBAR_H__136984FB_C2B4_4E6D_BC41_A29D1C114240__INCLUDED_)
