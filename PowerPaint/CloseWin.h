#if !defined(AFX_CLOSEWIN_H__0FB4FD01_8E7D_4FE2_A36A_4CC37AA323B6__INCLUDED_)
#define AFX_CLOSEWIN_H__0FB4FD01_8E7D_4FE2_A36A_4CC37AA323B6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CloseWin.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CCloseWin window

class CCloseWin : public CWnd
{
// Construction
public:
	CCloseWin();
	int wx,wy;
	CWnd *wnd;
	BOOL Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd) ;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCloseWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CCloseWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(CCloseWin)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnClose();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LOGFONT lf;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CLOSEWIN_H__0FB4FD01_8E7D_4FE2_A36A_4CC37AA323B6__INCLUDED_)
