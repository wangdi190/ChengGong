// MainWin.h : interface of the CMainWin class
//
/////////////////////////////////////////////////////////////////////////////

#if !defined(AFX_MAINWIN_H__C027D443_C050_419F_9DA2_F08CEEA8B190__INCLUDED_)
#define AFX_MAINWIN_H__C027D443_C050_419F_9DA2_F08CEEA8B190__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "workwin.h"
#include "tlswin.h"
#include "splitass.h"
#include "testwin.h"
/////////////////////////////////////////////////////////////////////////////
// CMainWin window

class CMainWin : public CWnd
{
// Construction
public:
	CMainWin();
	workwin  wkw;
	tlswin   tlw;
	SplitAss spl;
// Attributes
public:
	void PageChange(int page);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainWin)
	public:
	virtual BOOL OnCmdMsg(UINT nID, int nCode, void* pExtra, AFX_CMDHANDLERINFO* pHandlerInfo);
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CMainWin)
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnPrint();
	afx_msg void OnTest();
	afx_msg void OnPutout();
	afx_msg void OnUpdatePutout(CCmdUI* pCmdUI);
	afx_msg void OnTohmidir();
	afx_msg void OnBusralate();
	afx_msg void OnZmctl();
	afx_msg void OnUpdateTosqrt(CCmdUI* pCmdUI);
	afx_msg void OnGetnm();
	afx_msg void OnGetid();
	afx_msg void OnOutsvg();
	afx_msg void OnLoadcim();
	afx_msg void OnSvgname();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	TestWin tstw; //²âÊÔ´°¿Ú
	HWND  tmphwnd;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINWIN_H__C027D443_C050_419F_9DA2_F08CEEA8B190__INCLUDED_)
