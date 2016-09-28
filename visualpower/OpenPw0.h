#if !defined(AFX_OPENPW0_H__899E34D7_923A_42B0_830F_A224C8477185__INCLUDED_)
#define AFX_OPENPW0_H__899E34D7_923A_42B0_830F_A224C8477185__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// OpenPw0.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// OpenPw0 dialog

class OpenPw0 : public CFileDialog
{
	DECLARE_DYNAMIC(OpenPw0)

public:
	OpenPw0(BOOL bOpenFileDialog, // TRUE for FileOpen, FALSE for FileSaveAs
		LPCTSTR lpszDefExt = NULL,
		LPCTSTR lpszFileName = NULL,
		DWORD dwFlags = OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		LPCTSTR lpszFilter = NULL,
		CWnd* pParentWnd = NULL);
	int curpage;

// Dialog Data
	//{{AFX_DATA(OpenPw0)
	CComboBox	m_page;
	//}}AFX_DATA

	//{{AFX_VIRTUAL(OpenPw0)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL
protected:
	//{{AFX_MSG(OpenPw0)
		// NOTE - the ClassWizard will add and remove member functions here.
	afx_msg void OnSelchangePage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetFilePage(char *filename);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_OPENPW0_H__899E34D7_923A_42B0_830F_A224C8477185__INCLUDED_)
