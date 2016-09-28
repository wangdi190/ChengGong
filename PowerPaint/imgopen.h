#if !defined(AFX_IMGOPEN_H__169A76F9_0E8D_46E1_92A8_DA85320C9734__INCLUDED_)
#define AFX_IMGOPEN_H__169A76F9_0E8D_46E1_92A8_DA85320C9734__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// imgopen.h : header file
//
#include "jhsyslibl.h"
/////////////////////////////////////////////////////////////////////////////
// imgopen dialog

class imgopen : public CFileDialog
{
	DECLARE_DYNAMIC(imgopen)

public:
	imgopen(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	~imgopen();
	BOOL m_showpreview;
	CMImage img;
	int w,h;
// Dialog Data
		//{{AFX_VIRTUAL(imgopen)
		protected:
		virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
		//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(imgopen)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnSHowpreview();
	afx_msg void OnDepth();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OnDraw(LPARAM lParam);
	void OnNotify(LPNMHDR pnmh);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_IMGOPEN_H__169A76F9_0E8D_46E1_92A8_DA85320C9734__INCLUDED_)
