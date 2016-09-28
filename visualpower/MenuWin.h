#if !defined(AFX_MENUWIN_H__4422A330_EFE3_44B0_B025_7649FC1C0380__INCLUDED_)
#define AFX_MENUWIN_H__4422A330_EFE3_44B0_B025_7649FC1C0380__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MenuWin.h : header file
//
#include "gdata.h"
/////////////////////////////////////////////////////////////////////////////
// MenuWin window

class MenuWin : public CWnd
{
// Construction
public:
	MenuWin();
	int wx,wy;
	int pw,ph;				//页面的高度和宽度
	int selpush;			//选择的按钮
	CDIB mbg;				//背景画面
	CDIB msr;				//显示画面
// Attributes
public:
	gdata dbm;       //数据对象
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MenuWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MenuWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(MenuWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	ROBJ  *r_da;	//日期对象  
	int   dtsum;	//个数
	ROBJ  *r_tm;	//时间对象
	int   tmsum;	//个数
	RAML  *r_am;	//动画对象
	int   amsum;	//个数
	RSCRTXT *r_sc;	//滚动文本对象
	int   scsum;	//个数
	RSELFCTL *r_sf; //自助控件
	int   sfsum;	//个数
	RFLASH   *r_fsh;//FLASH对象
	int fssum;		//个数
	RPUSH    *r_ph; //按钮
	int phsum;		//个数

	void DrawShow();
	HWND GetSlfCtl(int id);
	void RunPushCmd(int j);
	void PaintShow(HDC hdc, CRect rt);
	void ShowPush(int j);
	int  IsInPush(CPoint point);
	void MouseLBUp(CPoint point);
	void MouseLBDown(CPoint point);
	int  GetCursor(CPoint point);
	void Set3DEnv();
	void GetObjFromDbm();
	void InitMoveObj();
	void FreeMem();
	void EndShow();
	void ShowA(CDIB&mdc);
	CRect srt;
	int dtupdate;   //时间更新标志
	int dx,dy;
	int cursor;
	int hmax,curpos;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MENUWIN_H__4422A330_EFE3_44B0_B025_7649FC1C0380__INCLUDED_)
