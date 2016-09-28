#if !defined(AFX_YBGDDLG_H__32003C2C_49E5_4F78_B60C_28D140A29220__INCLUDED_)
#define AFX_YBGDDLG_H__32003C2C_49E5_4F78_B60C_28D140A29220__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// YbGdDlg.h : header file
//
#include "gdata.h"
#include "readrltd.h"
/////////////////////////////////////////////////////////////////////////////
// YbGdDlg dialog

class YbGdDlg : public CDialog
{
// Construction
public:
	YbGdDlg(CWnd* pParent = NULL);   // standard constructor
	void AreaChange();
	~YbGdDlg();
public:
	void OPenFile(char *filename,int picno);
	int wx,wy;
	gdata dbm;
	ReadRltD rrd;	 //数据库读取对象
	CDIB mbg;				//背景画面
	CDIB msr;				//显示画面
// Dialog Data
	//{{AFX_DATA(YbGdDlg)
	enum { IDD = IDD_GDDLG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(YbGdDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(YbGdDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void ShowC(HDC hdc,CRect rtshow);
	void ShowC(HDC hdc,HRGN hrgn);
	void ShowDynObj(HDC hdc);
	void CreatePaintRgn();
	void CreateAllrgn();
	HWND GetSlfCtl(int id);
	void RunPushCmd(int j);
	void ShowPush(int j);
	int  IsInPush(CPoint point);
	bool SetDynMeter();
	void PaintShow(HDC hdc, CRect rt);
	bool SetYbVal(N_ELEGRPYB &yb,YBDATA &data,int j);
	void ChangeCtlSize(CRect rtd,SUBW_PARAM&pas);
	void ShowA(CDIB&mdc);
	void ChangeAllSft();
	bool UpDateMeter();
	void EndShow();
	void Set3DEnv();
	void SetFirstPosition();
	void GetObjFromDbm();
	bool UpdateAllData();
	void InitMoveObj();
	void FreeMem(); //释放内存
	//////////////运行时对象指针/////////////////////
	RSELFCTL *r_sf; //自助控件
	int   sfsum;	//个数
	RPUSH    *r_ph; //按钮
	int phsum;		//个数
	RMETER   *r_yb; //仪表
	int ybsum;		//个数
	RFLASH   *r_fsh;//FLASH对象
	int fssum;		//个数

	int t1,t2;
	int	allupdate;
	HRGN updatergn;		//刷新区域
	CRect srt;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_YBGDDLG_H__32003C2C_49E5_4F78_B60C_28D140A29220__INCLUDED_)
