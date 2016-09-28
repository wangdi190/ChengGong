#if !defined(AFX_DGXCRDLG_H__64550AFA_4C72_4508_886A_617F6636B79B__INCLUDED_)
#define AFX_DGXCRDLG_H__64550AFA_4C72_4508_886A_617F6636B79B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DgxCrDlg.h : header file
//
#include "pwptdef.h"
/////////////////////////////////////////////////////////////////////////////
// DgxCrDlg dialog

class DgxCrDlg : public CDialog
{
// Construction
public:
	DgxCrDlg(CWnd* pParent = NULL);   // standard constructor
	void ReDraw();
	SHOWCFG *scf;
	int wx,wy;
	CDIB mdc;
// Dialog Data
	//{{AFX_DATA(DgxCrDlg)
	enum { IDD = IDD_COLORDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DgxCrDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DgxCrDlg)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	LOGFONT lf;
	void Show(CDC&dc);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DGXCRDLG_H__64550AFA_4C72_4508_886A_617F6636B79B__INCLUDED_)
