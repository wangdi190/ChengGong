#if !defined(AFX_SELVLEV_H__5CB6B567_2B85_4C60_917E_4FE95114765A__INCLUDED_)
#define AFX_SELVLEV_H__5CB6B567_2B85_4C60_917E_4FE95114765A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SelVLev.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CSelVLev dialog

class CSelVLev : public CDialog
{
// Construction
public:
	CSelVLev(CWnd* pParent = NULL);   // standard constructor
	BYTE vl;
// Dialog Data
	//{{AFX_DATA(CSelVLev)
	enum { IDD = IDD_VLEVDLG };
	CListBox	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CSelVLev)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CSelVLev)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SELVLEV_H__5CB6B567_2B85_4C60_917E_4FE95114765A__INCLUDED_)
