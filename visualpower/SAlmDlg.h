#if !defined(AFX_SALMDLG_H__30C23585_A562_46C0_B425_E399130FFFE2__INCLUDED_)
#define AFX_SALMDLG_H__30C23585_A562_46C0_B425_E399130FFFE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SAlmDlg.h : header file
//
#include "jhsyslibl.h"
#include "pwptdef.h"
#include "middll.h"
#include "GzTblDlg.h"
#include "readrltd.h"
/////////////////////////////////////////////////////////////////////////////
// CSAlmDlg dialog

class CSAlmDlg : public CDialog
{
// Construction
public:
	CSAlmDlg(CWnd* pParent = NULL);   // standard constructor
	~CSAlmDlg();
	SYSALARM alm[6]; //6个高警
	int cursel;
	int wx,wy;
	ALMSAVE  alsv;	 //预警动作配置
	void DrawShow();
	CRect oldrt;
	CPoint oldpt;
	GzTblDlg  gzw[6]; //5个故障信息窗口
	ReadRltD  rrd;
// Dialog Data
	//{{AFX_DATA(CSAlmDlg)
	enum { IDD = IDD_ALARMDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSAlmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSAlmDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnShowlst();
	afx_msg void OnPushpic();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void LoadAlmCfg();
	void CheckPushTbl();
	void PlayAlmSound();
	void RelayChild();
	void MoveMyWin(CPoint point);
	int  GetCursor(CPoint point);
	void FlashShow();
	void ReadData();
	void Show(CDC&dc);
	void ShowLowFCom();
	LOGFONT lf1;
	CDIB mdc;
	int  zt,zt2,cursor;
	DWORD color;
	int dwnbz;
	int sounding;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SALMDLG_H__30C23585_A562_46C0_B425_E399130FFFE2__INCLUDED_)
