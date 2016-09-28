#if !defined(AFX_GZTBLDLG_H__7AD310D6_FE86_4A7B_92B4_AA29356ED232__INCLUDED_)
#define AFX_GZTBLDLG_H__7AD310D6_FE86_4A7B_92B4_AA29356ED232__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// GzTblDlg.h : header file
//
#include "visualdb.h"
#include "userapi.h"
#include "PublicAvcDef.h"

typedef struct _DMLS
{
	int id;			//线路ID
	BYTE type:4;	//线路类型
	BYTE ys:1;		//运算方法 0=+ 1=-
	BYTE nouse:3;	//未用
}DMLS;

//告警信息结构
typedef struct ALMMSG
{
	char name[32];
	DWORD id;
	float val[6];
	int   check;
	int   alarm;
}ALMMSG;
/////////////////////////////////////////////////////////////////////////////
// GzTblDlg dialog

class GzTblDlg : public CDialog
{
// Construction
public:
	GzTblDlg(CWnd* pParent = NULL);   // standard constructor
	~GzTblDlg();
	int  type;  //告警类型
	bool dbok;
	int  alarm; //告警和闪动
	int  sound;	//音效控制
	int  alsum;	//告警的设备数
	ALMMSG  *msg;
	int msgsum;
	int  init;
	//定义基本数据指针
	visualpw_Gen  *gen;
	visualpw_Tfm1 *tfm1;
	visualpw_Tfm2 *tfm2;
	visualpw_Bus  *bus;
	visualpw_Line *line;
	visualpw_DCLine *dcline;
	common_PreDefSF *pdf;
	visualpw_SysAlarm *alm;

	int gsum,tsum1,tsum2,bsum,lsum,dlsum,pdsum,asum;
	int gid,t1id,t2id,bid,lid,dlid,pdid,sid;
	//表地址
	MEMTABLE *mgen,*mtf1,*mtf2,*mbus,*mlin,*mdlin,*mpdf,*malm;
	//需要修改告警标志的域位置
	int fpos[8];
	int showmode;		//显示模式0=只显示告警 1=全部显示
	void SetList();
// Dialog Data
	//{{AFX_DATA(GzTblDlg)
	enum { IDD = IDD_TABLEDLG };
	CListCtrl	m_lst;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(GzTblDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(GzTblDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnReload();
	afx_msg void OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckall();
	afx_msg void OnUncheckall();
	afx_msg void OnSound();
	afx_msg void OnShowall();
	afx_msg void OnShowalm();
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CheckHvc(int check,DWORD id);
	void CheckAce(int check,DWORD id);
	void CheckBus(int check,DWORD id);
	void CheckDM(int check,DWORD id);
	void CheckTran(int check,DWORD id);
	void CheckGen(int check,DWORD id);
	void CheckLine(int check,DWORD id);
	void CheckAAlarm(int check,DWORD id);
	void GetFieldPos();
	void SetFieldTran(MEMTABLE *tbl,int jlh,int pos,int value);
	int  GetPos(MEMTABLE *tbl);
	void SetHvc();
	void SetHvc1();
	void SetAce();
	void SetAce1();
	void SetBus1();
	void SetDM1();
	void SetTran1();
	void SetGen1();
	void SetLine1();
	void TimeRefreshAlarm();
	void SetHeader();
	void ComputDmAlm(DMLS*dl,int num,float &pl,float &ql,float &pqs);
	bool GetLineDataPQ(float &Pcur,float &Qcur,int id,int type);
	void SetACE();
	void SetBus();
	void SetDM();
	void SetTran();
	void SetGen();
	void SetLine();
	void GetTableID();
	void GetRltDbAdd();
	void *GetTblAdd(int tid,int &n,MEMTABLE **data);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_GZTBLDLG_H__7AD310D6_FE86_4A7B_92B4_AA29356ED232__INCLUDED_)
