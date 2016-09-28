#if !defined(AFX_VIEWDEV_H__0914D511_CC08_4425_AAE4_3F63FCBF72CA__INCLUDED_)
#define AFX_VIEWDEV_H__0914D511_CC08_4425_AAE4_3F63FCBF72CA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ViewDev.h : header file
//
#include "pwptdef.h"
#include "readrltd.h"
/////////////////////////////////////////////////////////////////////////////
// CViewDev dialog

class CViewDev : public CDialog
{
// Construction
public:
	bool SetParam(int type,char *name,int id);
	CViewDev(CWnd* pParent = NULL);   // standard constructor
	int      curtype;	//当前设备类型
	GenData		gd;
	LinData		ld;
	DLinData	dd;
	BusData		bd;
	LoadData	ldd;
	TrfData1	td1;
	TrfData2	td2;
	ShuData		sd;
	SvcData		svd;
	SrdData     srd;
	int dataok;
	ReadRltD  *rrd;
// Dialog Data
	//{{AFX_DATA(CViewDev)
	enum { IDD = IDD_VIEWDEV };
	CListCtrl	m_lst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CViewDev)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CViewDev)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetSrdData();
	void SetSvcData();
	void SetShuData();
	void SetTranData1();
	void SetTranData2();
	void SetLoadData();
	void SetBusData();
	void SetDlineData();
	void SetLineData();
	void SetGenData();
	void SetData();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VIEWDEV_H__0914D511_CC08_4425_AAE4_3F63FCBF72CA__INCLUDED_)
