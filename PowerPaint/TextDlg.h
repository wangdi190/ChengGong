#if !defined(AFX_TEXTDLG_H__5F09B255_5CCD_46F2_9892_03F766A239A2__INCLUDED_)
#define AFX_TEXTDLG_H__5F09B255_5CCD_46F2_9892_03F766A239A2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TextDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// TextDlg dialog

class TextDlg : public CDialog
{
// Construction
public:
	TextDlg(char *str,int n,CWnd* pParent = NULL);   // standard constructor
	char *p;
	int count;
// Dialog Data
	//{{AFX_DATA(TextDlg)
	enum { IDD = IDD_TEXTDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TextDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(TextDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TEXTDLG_H__5F09B255_5CCD_46F2_9892_03F766A239A2__INCLUDED_)
