#if !defined(AFX_TESTWIN_H__9AB55A52_CB19_4CE4_9455_694D1BDC3878__INCLUDED_)
#define AFX_TESTWIN_H__9AB55A52_CB19_4CE4_9455_694D1BDC3878__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestWin.h : header file
//
#include "base0.h"
#include "jhsyslibl.h"
#include "shockwaveflash.h"
#include "closewin.h"

typedef struct SUBW_PARAM{//运行子窗口属性定义
	HWND  hwnd;			//窗口
	CRect rts;			//窗口原始大小
	CRect rt;			//占用的矩形
	CRect rtw;			//窗口矩形
	BYTE  outline;		//外框风格
    BYTE  left;			//左对齐
    BYTE  right;		//右对齐
    BYTE  top;			//上对齐
    BYTE  bottom;		//下对齐
	BYTE  mode;			//模式
}SUBW_PARAM;

typedef struct ROBJ{	//运行对象
	BASE0 *bs;		  	//对象地址
}ROBJ;
typedef struct RAML{	//动画对象
	BASE0 *bs;			//对象地址
	CRect rt;			//占用的矩形区
	CGIFAnm gfaml;	    //属性地址
}RAML;

typedef struct RSCRTXT{	//滚动文本对象
	BASE0 *bs;			//对象地址
	N_SRLTEXT *stx;		//属性地址
	CRect rt;			//占用的矩形区
	int xl,yl;			//当前位置
	int w,h;			//宽、高
}RSCRTXT;

typedef struct RSELFCTL{
	CRect rt;			//占用的矩形区
	int   sid;			//对象自生ID
	BYTE  cansize;		//能否改变大小
	SUBW_PARAM swp;		//窗口相关参数  
	N_SELFCTL *stl;		//属性地址
}RSELFCTL;

typedef struct RFLOW{	//潮流线对象
	BASE0  *bs;			//对象地址
	N_FLOW *flw;		//属性地址
	HRGN  hrgn;			//区域
	int   ptsum;		//点数
	POINT pt[20];		//点
	CRect rt;			//占用的矩形区
}RFLOW;

/*typedef struct RTREND{	//潮流线对象
	BASE0  *bs;			//对象地址
	N_TREND *td;		//属性地址
	BYTE jg;			//间隔
	BYTE seg;			//段数
	BYTE js;			//当前计数
	CRect rt;			//占用的矩形区
}RTREND;*/


//按钮控制运行参数格式
typedef struct RPUSH{	//76
	BASE0  *bs;			//对象地址
	CRect  rt;			//占用的矩形区
	N_PUSH *psh;		//属性地址
}RPUSH;

typedef struct RACTOBJ{	//活动对象
	BASE0    *bs;		//对象地址
	N_ACTOBJ *act;		//属性地址
	CRect  rt;			//占用的矩形区
	double curval;		//实时值
	double maxv;		//最大值
	double minv;		//最小值
	CDRect  oldrt;		//原来的位置
	CDRect  currt;		//当前位置
	WORD   picw,pich;	//显示图片的宽高
	short  picj;		//图片的记录号
	BYTE   js;			//当前计数
	DPOINT  *pt;			//路经
	int    ptsum;		//点数
}RACTOBJ;



typedef struct RFLASH{
	CRect rt;			//占用的矩形区
	N_FLASH *fsh;		//属性地址
	CShockwaveFlash fshw;//flash窗口
}RFLASH;
/////////////////////////////////////////////////////////////////////////////
// TestWin window

class TestWin : public CWnd
{
// Construction
public:
	TestWin();

// Attributes
public:

// Operations
public:
	void SetPage();
	BOOL Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(TestWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~TestWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(TestWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnClose();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void pqjs(int i);
	void ComputZoom();
	void EndTest();
	void GetActPicMsg(int i);
	void CreateFlwRgn(int j);
	void GetSflRunParam(SUBW_PARAM&pad,RSELFCTL&pas);
	void ClrStrEnter(char *str);
	int  GetLineNum(char *str);
	void GetObjFromDbm();
	
	void MovePic(CPoint point);
	void RunFunctModule(char *mstring);
	HWND GetSlfCtl(int id);
	void RunPushCmd(int j);
	void ShowPush(int j);
	int  IsInPush(CPoint point);
	void AutoSetActValue(int i);
	void ShowD(HDC hdc, CRect rt);
	void ShowC();
	void ShowB(HDC hdc,CRect rt);
	void ShowA();
	void demodtime(HDC hdc);
	void ShowAFlow(HDC hdc);
	void ShowFlow(HDC hdc);
	void demoactobj(HDC hdc);
	void ShowScrTxt(HDC hdc);
	void ShowAScrTxt(HDC hdc, int j,int mode=0);
	void ShowGifAml(HDC hdc);
	void DemoStatus(HDC hdc,int enable=1);
	void DemoAnalog(HDC hdc,int enable=1);
	void FreeMem();
	void ShowActObj(HDC hdc,int x,int y,int k);
	void Show(HDC hdc, CRect rt);
	void ComputMaxXY();
	void ChangeCtlSize(CRect rtd,SUBW_PARAM&pas,int ly=1);
	CDIB mbg; //背景画面
	CDIB msr; //显示画面
	CDIB mtp; //中间画面
	double oldzm; //原有放大倍数
	int oldsel;
	CRect srt;
	CPoint pt1;
	int xmax,ymax;

	int dnbz;
	int dx,dy;
	int wx,wy;
	int wd,hg;  //界面的宽高
	int cp;
	int flwjg;  //潮流线动态间隔
	//////////////运行时对象指针/////////////////////
	ROBJ *r_da;		//日期对象  
	int dtsum;		//个数
	ROBJ *r_tm;		//时间对象
	int tmsum;		//个数
	RAML *r_am;		//动画对象
	int amsum;		//个数
	RSCRTXT *r_sc;	//滚动文本对象
	int scsum;		//个数
	RSELFCTL *r_sf; //自助控件
	int sfsum;		//个数
	RFLOW    *r_fw; //潮流线
	int fwsum;		//个数	
	RPUSH    *r_ph; //按钮
	int phsum;		//个数
	RACTOBJ  *r_at; //活动对象
	int atsum;		//个数
	RFLASH   *r_fsh;//FLASH对象
	int fssum;		//个数


	CCloseWin clsw;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_TESTWIN_H__9AB55A52_CB19_4CE4_9455_694D1BDC3878__INCLUDED_)
