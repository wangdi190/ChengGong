#if !defined(AFX_LAYERDLG_H__04807CE7_4A3C_484A_B3A5_4E3E50BFA506__INCLUDED_)
#define AFX_LAYERDLG_H__04807CE7_4A3C_484A_B3A5_4E3E50BFA506__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// LayerDlg.h : header file
//
#include "gdata.h"
/////////////////////////////////////////////////////////////////////////////
// CLayerDlg dialog

class CLayerDlg : public CDialog
{
// Construction
public:
	CLayerDlg(CWnd* pParent = NULL);   // standard constructor
	gdata *dbm;
// Dialog Data
	//{{AFX_DATA(CLayerDlg)
	enum { IDD = IDD_LAYERDLG };
	CListCtrl	m_list;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CLayerDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CLayerDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void EnablePush(int id, bool enable);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LAYERDLG_H__04807CE7_4A3C_484A_B3A5_4E3E50BFA506__INCLUDED_)
