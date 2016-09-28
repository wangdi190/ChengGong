#if !defined(AFX_DEFDMDLG_H__6909574B_5426_40B3_80B8_78D435602796__INCLUDED_)
#define AFX_DEFDMDLG_H__6909574B_5426_40B3_80B8_78D435602796__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DefdmDlg.h : header file
//
#include "mstruct.h"
#include "visualdb.h"

/////////////////////////////////////////////////////////////////////////////
// DefdmDlg dialog

class DefdmDlg : public CDialog
{
// Construction
public:
	DefdmDlg(CWnd* pParent = NULL);   // standard constructor
	~DefdmDlg();
	DEVDEF  *line;			//线路
	DEVDEF  *dcline;		//直流线路
	DEVDEF  *tfm1;			//2绕变
	DEVDEF  *tfm2;
	DEVDEF  *gen;			//发电机
	int lsum,dlsum,t1sum,t2sum,gsum;
	
	DEVDEF  *deft,*def;
	int numt,selnum;
			//数量
	common_PreDefSF dm[128];	//断面(最大128个断面)
	int		dmsum;
	int    ltype;			//线路类型;
	int    curdm;
    bool   dbok;
// Dialog Data
	//{{AFX_DATA(DefdmDlg)
	enum { IDD = IDD_DEFSECTDLG };
	CComboBox	m_acdc;
	CListBox	m_defined;
	CListBox	m_lineid;
	CListBox	m_line;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DefdmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DefdmDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeAcdc();
	afx_msg void OnAdddm();
	afx_msg void OnModidm();
	afx_msg void OnDblclkDefined();
	afx_msg void OnDeletedm();
	afx_msg void OnDeleteline();
	afx_msg void OnDblclkLine();
	virtual void OnOK();
	afx_msg void OnSelchangeDefined();
	afx_msg void OnAddys();
	afx_msg void OnSubys();
	afx_msg void OnChangePyjs();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void OrderDevByName();
	void GetDev();
	void ReadGen();
	void GetLineName(char *name,int type,int id);
	bool IsSaveID(int id);
	int  GetAID();
	bool IsHaveDm(char *name);
	bool IsHaveDm1(char *name,int jlh);
	void SetLineID();
	void SetEdit();
	void SetDmList();
	void SetLineList();
	void ReadTfm2();
	void ReadDCLine();
	void ReadLine();
	void ReadPredef();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DEFDMDLG_H__6909574B_5426_40B3_80B8_78D435602796__INCLUDED_)
