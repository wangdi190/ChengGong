#if !defined(AFX_TLSWIN_H__D23118D0_24E3_4C35_B777_523433358ECC__INCLUDED_)
#define AFX_TLSWIN_H__D23118D0_24E3_4C35_B777_523433358ECC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// tlswin.h : header file
//

typedef struct TOOLWIN{
	CWnd *wnd;      //窗口
	char str[24];   //标题串
	CRect selrt;    //选择矩形区
	int  index;	    //序号
	int  active;    //是否活动
	int  height;	//最小高度
	CRect rtw;		//窗口矩形位置
	int sel;		//鼠标滑过，显示选择 0=没有 1=选择 2=菜单
	int menu;		//是否有菜单
	CMenu  cmenu;	//菜单
}TOOLWIN;

#include "spiwin.h"
#include "egpwin.h"
#include "naviwin.h"
#include "layerwin.h"
#include "editobj.h"
#include "jhsyslibl.h"
/////////////////////////////////////////////////////////////////////////////
// tlswin window

class tlswin : public CWnd
{
// Construction
public:
	tlswin();
	int wx,wy;
	NaviWin		navw;
	egpwin		egpw;
	spiwin		spiw;
	layerwin	layw;
	editobj     objw;
	TOOLWIN		tw[4];
	CDIB    mdc;
// Attributes
public:

// Operations
public:
	void ReFreshWin();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(tlswin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	bool IsEditActive();
	void EnableEditTool();
	virtual ~tlswin();

	// Generated message map functions
protected:
	//{{AFX_MSG(tlswin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnEditchange();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DrawShow();
	int GetSel(CPoint point,int &sel);
	void DrawATitle(CDC&dc,int index);
	void ShowTitle(CDC&dc);
	void ComputSelWin();
	CImageList img;
	int oldsel,olds;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TLSWIN_H__D23118D0_24E3_4C35_B777_523433358ECC__INCLUDED_)
