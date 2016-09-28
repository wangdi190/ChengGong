#if !defined(AFX_MODIDLG_H__17A601B4_2D0B_4101_83B0_CEFF214A8C96__INCLUDED_)
#define AFX_MODIDLG_H__17A601B4_2D0B_4101_83B0_CEFF214A8C96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ModiDlg.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// CModiDlg dialog

class CModiDlg : public CDialog
{
// Construction
public:
	CModiDlg(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CModiDlg)
	enum { IDD = IDD_DIALOG_MODI };
	CListCtrl	m_list_sys;
	CListCtrl	m_list;
	CListCtrl	m_list_tfm;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CModiDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CModiDlg)
	afx_msg void OnButton1();
	virtual BOOL OnInitDialog();
	afx_msg void OnClickList(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnClickLISTTfm(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnModi();
	afx_msg void OnRadioRl();
	afx_msg void OnRadioSys();
	afx_msg void OnBtnSys();
	afx_msg void OnClickListSys(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnBtnSysdata();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	int m_nPos, m_iTable;
	float m_fPmax, m_fValue;
	void ListStation();
	void ListSys();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MODIDLG_H__17A601B4_2D0B_4101_83B0_CEFF214A8C96__INCLUDED_)
