#if !defined(AFX_ALMDLG_H__B50D67F8_7A35_4050_AE3D_63F332A5DFD2__INCLUDED_)
#define AFX_ALMDLG_H__B50D67F8_7A35_4050_AE3D_63F332A5DFD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AlmDlg.h : header file
//
#include "visualdb.h"
#include "userapi.h"
#include "mstruct.h"


/////////////////////////////////////////////////////////////////////////////
// AlmDlg dialog

class AlmDlg : public CDialog
{
// Construction
public:
	AlmDlg(CWnd* pParent = NULL);   // standard constructor
	int type;
	bool dbok;
	//定义基本数据指针
	visualpw_Gen  *gen;
	visualpw_Tfm1 *tfm1;
	visualpw_Tfm2 *tfm2;
	visualpw_Bus  *bus;
	visualpw_Line *line;
	visualpw_DCLine *dcline;
	common_PreDefSF *pdf;
	visualpw_SysAlarm *alm;
	int gsum,tsum1,tsum2,bsum,lsum,dlsum,pdsum,amsum;
	int gid,t1id,t2id,bid,lid,dlid,pdid,almid;
	//表地址
	MEMTABLE *mgen,*mtf1,*mtf2,*mbus,*mlin,*mdlin,*mpdf,*malm;
// Dialog Data
	//{{AFX_DATA(AlmDlg)
	enum { IDD = IDD_ALMLSTDLG };
	CListCtrl	m_lst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(AlmDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(AlmDlg)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ComputDmAlm(DMLS*dl,int num,float &pl,float &ql,float &pqs);
	bool GetLineDataPQ(float &Pcur,float &Qcur,int id,int type);
	void SetBus();
	void SetDM();
	void SetTran();
	void SetGen();
	void SetLine();
	void SetList();
	void GetTableID();
	void GetRltDbAdd();
	void *GetTblAdd(int tid,int &n,MEMTABLE **data);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ALMDLG_H__B50D67F8_7A35_4050_AE3D_63F332A5DFD2__INCLUDED_)
