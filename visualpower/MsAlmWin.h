#if !defined(AFX_MSALMWIN_H__CC807133_10F8_42D4_BC82_8B68A7534827__INCLUDED_)
#define AFX_MSALMWIN_H__CC807133_10F8_42D4_BC82_8B68A7534827__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MsAlmWin.h : header file
//
#include "jhsyslibl.h"
#include "pwptdef.h"
#include "middll.h"
#include "GzTblDlg.h"
#include "readrltd.h"
/////////////////////////////////////////////////////////////////////////////
// MsAlmWin window

class MsAlmWin : public CWnd
{
// Construction
public:
	MsAlmWin();
	SYSALARM alm[7]; //7个高警
	int cursel;
	ALMSAVE  alsv;	 //预警动作配置
	CRect oldrt;
	CPoint oldpt;
	GzTblDlg  *gzw[5]; //5个故障信息窗口
	ReadRltD  rrd;

	

// Attributes
public:
	BOOL Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MsAlmWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MsAlmWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(MsAlmWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnShowlst();
	afx_msg void OnPushpic();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void MoveMyWin(CPoint point);
	int  GetCursor(CPoint point);
	void Show(CDC &dc);
	void RelayChild();
	void DrawShow();
	void PlayAlmSound();
	void ShowLowFCom();
	void CheckPushTbl();
	void FlashShow();
	void ReadData();
	void LoadAlmCfg();
	int wx,wy;
	LOGFONT lf1;
	CDIB mdc;
	int  zt,zt2,cursor;
	DWORD color;
	int dwnbz;
	int sounding;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MSALMWIN_H__CC807133_10F8_42D4_BC82_8B68A7534827__INCLUDED_)
