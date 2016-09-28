#if !defined(AFX_CHILDFRM_H__1F2E0873_8DEC_46D1_BDC6_40B7F6CF0BE6__INCLUDED_)
#define AFX_CHILDFRM_H__1F2E0873_8DEC_46D1_BDC6_40B7F6CF0BE6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ChildFrm.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CChildFrm window

class CChildFrm : public CWnd
{
// Construction
public:
	CChildFrm();

// Attributes
public:
	char pagename[256]; //画面名字
	int wx,wy;
	HWND hwnd;		//子窗口句柄
	int  type;		//窗口类型  0=swin 1=web页面 2=google页面
	void *rc;		//资源地址
	CRect rt;		//标题显示位置
// Operations
public:
	int  PSoeSum();
	int  Soebz();
	int  PAngle();
	int  PN1bz();
	int  PFtype();
	int  PCurrtn();
	int  PCtrtype();
	int  PHisplay();
	int  PDbzt();
	BOOL PHdbok();
	int  PRev();
	int  PDevn(int sel);
	int  PSenflag();
	int  PSen();
	int  PDmflow();
	int  PDgx();
	int  PCurhmi();
	int  PCursor();
	int  PType();
	int  Lowf();
	BOOL Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd);
	void DelResource();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChildFrm)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CChildFrm();

	// Generated message map functions
protected:
	//{{AFX_MSG(CChildFrm)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHILDFRM_H__1F2E0873_8DEC_46D1_BDC6_40B7F6CF0BE6__INCLUDED_)
