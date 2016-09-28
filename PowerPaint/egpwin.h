#if !defined(AFX_EGPWIN_H__31F921C4_719B_44DA_9BC7_6B408B056367__INCLUDED_)
#define AFX_EGPWIN_H__31F921C4_719B_44DA_9BC7_6B408B056367__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// egpwin.h : header file
//
#include "typewin.h"
/////////////////////////////////////////////////////////////////////////////
// egpwin window

class egpwin : public CWnd
{
// Construction
public:
	egpwin();
	int wx,wy;
	CMenu menu;
// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(egpwin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReOpenGrp();
	virtual ~egpwin();

	// Generated message map functions
protected:
	//{{AFX_MSG(egpwin)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnOpenegrp();
	afx_msg void OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnSaveegrp();
	afx_msg void OnSaveas();
	afx_msg void OnAddempty();
	afx_msg void OnPastenormal();
	afx_msg void OnPastealarm();
	afx_msg void OnDelaegrp();
	afx_msg void OnCopytodesk();
	afx_msg void OnSetup();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SaveEGP(char *filename);
	void NewTypeSel(int cmd);
	void ComputMax();
	void ShowEPIC();
	void SetYScroll();
	void computpage();
	void ReDrawObj();
	void LoadEGP(char *filename);
	void AddAllStr();
	CTypeWin twin;
	CScrollBar bar;
	CDIB mdc;
	int dy,selpic;
	char filenm[256];
	char fbz;
	BYTE m_curtype;
	BYTE m_cursubtype;
	DWORD fcolor;  //系统标准前景颜色
	int dx,maxy; //最大值

};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EGPWIN_H__31F921C4_719B_44DA_9BC7_6B408B056367__INCLUDED_)
