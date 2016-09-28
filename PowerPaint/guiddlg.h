#if !defined(AFX_GUIDDLG_H__B1A70E36_7BA1_48D7_B08D_6E15F9C25437__INCLUDED_)
#define AFX_GUIDDLG_H__B1A70E36_7BA1_48D7_B08D_6E15F9C25437__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// guiddlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// guiddlg dialog

class guiddlg : public CDialog
{
// Construction
public:
	guiddlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(guiddlg)
	enum { IDD = IDD_GUIDEDLG };
	CComboBox	m_style;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(guiddlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(guiddlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	virtual void OnOK();
	afx_msg void OnModic();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void DispCtlColor(int id, int color);
	DWORD tcolor;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GUIDDLG_H__B1A70E36_7BA1_48D7_B08D_6E15F9C25437__INCLUDED_)
