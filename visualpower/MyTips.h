#if !defined(AFX_MYTIPS_H__516AEDFC_95C1_43FA_854E_232C8C39CFC3__INCLUDED_)
#define AFX_MYTIPS_H__516AEDFC_95C1_43FA_854E_232C8C39CFC3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyTips.h : header file
//

typedef struct STRLINE{
	char *str;
	int  width;
}STRLINE;
/////////////////////////////////////////////////////////////////////////////
// MyTips window

class MyTips : public CWnd
{
// Construction
public:
	MyTips();
	int len;
	CPoint mpt;		//鼠标的位置
// Attributes
public:

// Operations
public:
	void SetText(char *text);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(MyTips)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~MyTips();

	// Generated message map functions
protected:
	//{{AFX_MSG(MyTips)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int wx,wy;
	LOGFONT lf;
	char str[256];	//字符串
	STRLINE sl[7];	//最大4行
	int lsum;		//当前行数
	int hg,wd;		//窗口的宽和高
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MYTIPS_H__516AEDFC_95C1_43FA_854E_232C8C39CFC3__INCLUDED_)
