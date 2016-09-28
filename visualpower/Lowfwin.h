#if !defined(AFX_LOWFWIN_H__7FFF62DC_F7BF_4F89_9C71_2DBBD97DD7C6__INCLUDED_)
#define AFX_LOWFWIN_H__7FFF62DC_F7BF_4F89_9C71_2DBBD97DD7C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// Lowfwin.h : header file
//

#include "jhsyslibl.h"
#include "clisock.h"
#include "pwptdef.h"
#include "readrltd.h"


typedef struct CONCFG //连接配置
{
	in_addr laddr;    //本地地址
	in_addr saddr;	  //服务器地址
	WORD port;		  //服务器口号
}CONCFG;


typedef struct LFData
{
	int 	LineID;		//线路ID
	BYTE	Type;		//类型交流或直流
	int     bsum;		//缓冲区包总数
	float   maxv;		//最大限幅值
	double  pha;		//相位
	float   lastv;		//上次的幅值
	LFSDATA  data[8];	//接收的数据,可以缓冲8秒数据
	//BYTE valid;			//数据有效
}LFData;

/////////////////////////////////////////////////////////////////////////////
// Lowfwin window

class Lowfwin : public CWnd
{
// Construction
public:
	Lowfwin();
	clisock cliw;		//客户SOCK窗口
	CONCFG concfg[4];	//连接配置
	int  consum;		//配置总数
	int  curcon;		//当前配置
	int wx,wy;
	CDIB mdc;
	float sfr;			//当前频率
	float sval;			//当前幅值
	int   curtype;		//当前显示的类型
	int   curid;		//当前ID
	char  name[24];		//线路名称
	float *vpt;			//低频震荡数据
	int	  vlen;			//低频震荡数据长度
	int   showbl;		//显示的倍率
	int   curfct;		//当前功能，0=正常 1=显示连接服务器状态 2=显示波形
	///////////////////////////////////////////////////////////////////////
	//数据
	int nLine;			//线路数
	LFData lwf[MAXLWF];	//低拼震荡数据,最大12
	int lbdown;			//鼠标压下标志
	int islowf;			//是否低频振荡状态
	ReadRltD  *rrd;
// Attributes
public:
	void SetFunct(int funct);
	bool GetABufData(LFSDATA &lfd,int id,int type);
// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(Lowfwin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	
	bool IsLowFLine(int id,int type);
	void EndLowf();
	void StartLowf();
	void LowFShow();
	virtual ~Lowfwin();

	// Generated message map functions
protected:
	//{{AFX_MSG(Lowfwin)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg int  OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnConnect();
	afx_msg void OnRecData();
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CheckCon();
	void RecFlowLowF(char *buf,DWORD len);
	void SetLowFData(LFDATA &lfd);
	void DemoLowFData();
	void InitLowfLine();
	void DrawControll();
	void SendCheck();
	void LoginSvr();
	DWORD ChangeHL(DWORD param);
	void CreateConCfg();
	void Draw();
	LOGFONT lf;
	DWORD fcolor;
	CSliderCtrl sld;
	int svrchk;
	int sounding;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_LOWFWIN_H__7FFF62DC_F7BF_4F89_9C71_2DBBD97DD7C6__INCLUDED_)
