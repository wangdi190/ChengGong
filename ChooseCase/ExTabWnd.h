#if !defined(AFX_EXTABWND_H__BD213676_F074_4FB3_8CE6_7612E5572618__INCLUDED_)
#define AFX_EXTABWND_H__BD213676_F074_4FB3_8CE6_7612E5572618__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ExTabWnd.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CExTabWnd window
#include "BtnST.h"
#define CAPTION_BKCOLOR RGB(209,209,165)
#define CAPTION_CLCOLOR RGB(215, 255, 215)

class CExTabWnd : public CWnd
{
// Construction
public:
	CExTabWnd();

// Attributes
public:
	CPtrArray m_ptab;			//CButtonST类型
	CRect m_caprect;
	CRect m_childrect;
	CPtrArray m_view;			//CDialog类型
	CUIntArray m_viewID;		//对话框ID
	BYTE m_cursel;				//当前选择
	CString szcaption;
// Operations
public:
	void AddView(CDialog* pview, UINT viewID, LPCSTR szname);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CExTabWnd)
	protected:
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CExTabWnd();

	// Generated message map functions
protected:
	//{{AFX_MSG(CExTabWnd)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void showtabview(LPARAM lParam);
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_EXTABWND_H__BD213676_F074_4FB3_8CE6_7612E5572618__INCLUDED_)
