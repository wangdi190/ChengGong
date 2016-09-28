#if !defined(AFX_NAVGDLG_H__491CE033_527A_42A1_BABE_A072C7E15BA3__INCLUDED_)
#define AFX_NAVGDLG_H__491CE033_527A_42A1_BABE_A072C7E15BA3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// NavgDlg.h : header file
//
#include "jhsyslibl.h"
#include "gdata.h"
/////////////////////////////////////////////////////////////////////////////
// NavgDlg dialog

class NavgDlg : public CDialog
{
// Construction
public:
	NavgDlg(CWnd* pParent = NULL);   // standard constructor
	void PageChange();
	void ComputDWin();
	void MoveCvs();
	void ShowBg();
	void ZoomChange();
	void WinSizeChange(int cx, int cy);
	gdata *dbm;
// Dialog Data
	//{{AFX_DATA(NavgDlg)
	enum { IDD = IDD_NVGDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(NavgDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(NavgDlg)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetCursor(CPoint point);
	void ComputCrt();
	void Show(CDC &dc);
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

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_NAVGDLG_H__491CE033_527A_42A1_BABE_A072C7E15BA3__INCLUDED_)
