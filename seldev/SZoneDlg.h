#if !defined(AFX_SZONEDLG_H__4B744283_39D6_45CF_9F56_5CB224DDF233__INCLUDED_)
#define AFX_SZONEDLG_H__4B744283_39D6_45CF_9F56_5CB224DDF233__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// SZoneDlg.h : header file
//
#include "mstruct.h"
#include "visualdb.h"
/////////////////////////////////////////////////////////////////////////////
// SZoneDlg dialog

class SZoneDlg : public CDialog
{
// Construction
public:
	SZoneDlg(CWnd* pParent = NULL);   // standard constructor
	~SZoneDlg();
	SELDATA_DEV ad;
	DEVDEF *def;
	int num;
	bool dbok;
// Dialog Data
	//{{AFX_DATA(SZoneDlg)
	enum { IDD = IDD_SELZONE };
	CComboBox	m_cb;
	CListBox	m_name;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(SZoneDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(SZoneDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeCombo1();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void GetDmData();
	void GetZoneData();
	void GetData();
	int GetIndex(int id);
	void SetToLst();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SZONEDLG_H__4B744283_39D6_45CF_9F56_5CB224DDF233__INCLUDED_)
