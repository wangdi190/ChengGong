#if !defined(AFX_SOEPLAYBAR_H__38270BA0_3D03_4CD8_A4A3_93E92C3990B3__INCLUDED_)
#define AFX_SOEPLAYBAR_H__38270BA0_3D03_4CD8_A4A3_93E92C3990B3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SoePlayBar.h : header file
//
#include "jhsyslibl.h"
/////////////////////////////////////////////////////////////////////////////
// SoePlayBar window

class SoePlayBar : public CToolBar
{
// Construction
public:
	SoePlayBar();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SoePlayBar)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetNewDate(CTime &tm,int newms);
	virtual ~SoePlayBar();

	// Generated message map functions
protected:
	//{{AFX_MSG(SoePlayBar)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	DWORD color;
	LOGFONT lf;
	CRect rt1,rt2;
	int rw,rh;
	CDIB mdc;
	int hour,min,sec,ms; // ±∑÷√Î,∫¡√Î
	int year,mon,day; 
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SOEPLAYBAR_H__38270BA0_3D03_4CD8_A4A3_93E92C3990B3__INCLUDED_)
