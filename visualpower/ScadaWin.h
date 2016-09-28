#if !defined(AFX_SCADAWIN_H__7A8EC773_EF15_496E_AC5C_288A59EB20D5__INCLUDED_)
#define AFX_SCADAWIN_H__7A8EC773_EF15_496E_AC5C_288A59EB20D5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ScadaWin.h : header file
//
#include "resource.h"
#include "mytips.h"
#include "gdata.h"
#include "nettpy.h"
#include "middll.h"
#include "Lowfwin.h"
#include "dmjsdlg.h"
#include "readrltd.h"
////////////////////////////////////////////////////////////////////////////////////////////////////
enum FUN_STATUS//可视化功能状态
{
	FUN_BASE=0,		//基本潮流状态
	FUN_DGXBUS=1,	//母线等高线
	FUN_DGXBUSL=2,	//母线等高线低
	FUN_DGXBUSH=3,	//母线等高线高
	FUN_DGXLINE=4,	//输电线等高线
	FUN_DGXTRAS=5,	//变压器等高线
	FUN_DGXLOAD=6,	//负荷等高线
	FUN_DMFLOW=7,	//断面潮流
	FUN_SENOPR=8,	//灵敏度
	FUN_REVGEN=9,	//发电机备用
	FUN_REVGENQ=10,	//发电机无功备用
	FUN_REVTRANS=11,//变压器备用
	FUN_TRANSTEMP=12,//变压器温度
	FUN_N1BUS=13,	//N1母线
	FUN_N1BRA=14,	//N1支路
	FUN_N1ALL=15,	//N1全部
	FUN_N1BUSF=16,	//预测N1母线
	FUN_N1BRAF=17,	//预测N1支路
	FUN_N1ALLF=18,	//预测N1全部
	FUN_N1EFT=19,	//N1影响
	FUN_ZONE=20	,	//分区信息
	FUN_SPIE=21,	//系统棒图
	FUN_SOE=22,		//SOE回放
	FUN_LOWF=23		//低频震荡
};
/////////////////////////////////////////////////////////////////////////////
// ScadaWin window

class ScadaWin : public CWnd
{
// Construction
public:
	ScadaWin();
	BOOL Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd);
// Attributes
public:
	CDIB mbg;				//背景画面
	CDIB msr;				//显示画面
	int winmode;			//当前模式 0=子窗口 1=全屏方式
	int t1,t2;				
	int wx,wy;				//窗口尺寸(像素单位)
	HWND   SvWnd;			//变压器反时限监视的窗口
	CRect  svcrt;			//sv窗口的位置
	MyTips   twin;			//提示窗口
	DmJsDlg  dmwin;			//断面监视窗口
	int dx,dy;				//图形和屏幕的偏移量(像素单位)
	int cursor,rcursor;		//当前鼠标状态
	int enabletimer;		//定时器是否可以工作
	//图形拓扑所用参数
	CNetTpy nettp;
	//等高线
	BYTE *pb;				//计算的等高线值
	//等高线
	CSysContour sct;		//等高线参数
	//灵敏度标记点
	DPOINT  senpoint;
	int		sentype;		//当前灵敏度类型
	//断面数据
	CDRect  dmsrt[10];		//用于提示条区域框确定
	DMSECT  dms[10];		//断面
	int     dmsum;			//断面数
	/////////低频震荡放大窗口///////////
	POINT lfpos;			//显示位置
	Lowfwin lwin;
	////////////////////////////////////
	//鼠标压下前的参数
	double dzoom;			//压下前的放大倍数
	int    ddx,ddy;			//压下前的偏移量
	int    dangle;			//压下前的角度
	int    dlk;				//压下前的俯视状态
	//////几个决定菜单功能的参数///////////////////
	int n_ge;		//发电机个数
	int n_tr;		//变压器个数
	int n_sh;		//电容器个数
	int n_se;		//灵敏度显示
	int n_pie;		//区域饼图
	int n_spe;		//系统饼图数
	//断面潮流统计用绘图参数
	POINT ptpoly[300];//最多300个点
	int   polysum;	  //多边形点数
	int   segsum;	  //段数
	int   dmsdot[10]; //每段终点，第一段起点为0 第二段起点为第一段终点+1
	POINT dmpt[500];  //最多300个点
	/////////////////////////////////////////////////
	gdata dbm;       //数据对象
	ReadRltD rrd;	 //数据库读取对象
	//线程句柄参数
	HANDLE  hThread_rd;
	DWORD   dwThreadID;
	int		allupdate;
	////////////////////////////////////////////////////////////
	FUN_STATUS m_PreFun;	
	FUN_STATUS m_CurFun;
	////////////////////////////////////////////////////////////
// Operations
public:
	void SetLineSccData(DLDL &sc);
	void SetSwtSccData(DLDL &sc);
	void CleaseDlFlash();
	void SetCurDbf(int newdbzt);
	bool FileOpen(char *filename,int pageno,HISHMI *hmi=NULL,int mode=0);
	void Set3DEnv();
	void ToMyZm(double zmx);
	void SetCurHisDTime();
	void ResetAllData(int ele=0);
	void ReadHisData();
	void RegistHisAllDev();
	void SetN1Data(int n1type,N1Data *data,int num);
	void FlowSel(int sel);
	void SetDgxParam();
	void CloseLowfWin();
	void InitLowFData();
	void InitLowFData(LFDATA* pLF);
	void FlwZoomChange();
	void SetStatusZoom();
	void SetStatusBarMsg();
	void CursorChange(int newcursor);
	void ChangeDgxcfg();
	void ZoomChange();
	void ShowActObj(HDC hdc,int x,int y,int k);
	void PrintPage(HDC hdc, BYTE pm, int dx, int dy);
	bool SetFlowData(int i,READDEV  &ran);
	void CreateAllrgn();
	bool UpdateAllData();
	void InitMoveObj(HISHMI *hmi=NULL,int mode=0);
	void ComputZCenter();
	void ShowA(CDIB&mdc);
	void SetFirstPosition();
	void FreeMem();
	void DrawShow();
	void EndShow();
	void Order3dPos();

	void Show3DObj(CDIB&mdc,CRect rt);
	void Show3DObjj(CDIB&mdc,CRect rt);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(ScadaWin)
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_VIRTUAL

// Implementation
public:
	void ReadN1EFT();
	void SetCurFunction(FUN_STATUS newfun);
	void CleaseSwtSoe();
	void CollectN1Device();
	void TurnToLowF();
	void LoadPreDefineSfw();
	void GetCurHmi(HISHMI &newhmi);
	virtual ~ScadaWin();

	// Generated message map functions
protected:
	//{{AFX_MSG(ScadaWin)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnPaint();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg BOOL OnMouseWheel(UINT nFlags, short zDelta, CPoint pt);
	afx_msg void OnViewdev();
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLowzoom();
	afx_msg void OnMainPage();
	afx_msg void OnResvjs();
	afx_msg void OnDestroy();
	afx_msg void OnCommandRange(UINT id);
	afx_msg void OnAvcopt();
	afx_msg void OnPqvopt();
	afx_msg void OnN12eft();
	afx_msg void OnN12eft3d();
	afx_msg void OnGenmsg();
	afx_msg void OnTranmsg();
	afx_msg void OnSvopt();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void SetN1EftData(N1Data *data,int num);
	bool GetN1Sel(DWORD &dwID,int &type,float &fSec);
	void ComputScc();
	bool SelIsGen();
	bool SelIsTran();
	void SetANewSoe(NSOES &asoe);
	void DmFlowSwitch();
	void AddDmPt();
	void RegistHis();
	bool ComputShowByRt();
	//显示等高线
	void ShowDgx(CDIB&mdc);
	void Rotate();
	void ShowDynObj(HDC hdc);
	void ShowSelFlag(HDC hdc,int sx,int sy);
	void CollectDevice();
	
	void RButtonMenu(CPoint point);
	void DrawStatArea();
	void ZoomInOut();
	HWND GetSlfCtl(int id);
	void SetSenData(READSEN&sn);
	void MovePic(CPoint point);
	void MouseMove(CPoint point);
	void MouseOnPush(UINT nFlags,CPoint point);
	int  GetCursor(CPoint point);
	void PartZoom(CRect rt);
	void RunPushCmd(int j);
	void ComputSen();
	void UserSflw();
	void SectFlw();
	void ShowPush(int j);
	int  IsInPush(CPoint point);
	void AddPoint(CPoint point);
	void DrawXorRect(CRect rt);
	void MouseLBUp(CPoint point);
	void MouseLBDown(CPoint point);
	
	void CheckPopTips();

	CString PhraseType(BYTE bType, BYTE bSB);

	void CheckPopTips_WD();//wd 2015-07-09 add

	void Showdtime(HDC hdc);
	void ReSetAllContourVal();
	int  Getspeed(double value,int type=0);
	bool SetAContourVal(int i);
	void ComputActRect(int i);
	void GetActPicMsg(int i);
	bool UpDateSysPie();
	bool UpDateMttxt();
	bool UpDatePPie();
	void UpDateAct();
	bool UpDateBar();
	void UpDateMeter();
	void UpdateGifaml();
	bool UpdateStatus();
	bool UpdateTranformer();

	bool UpdateStation();

	bool UpdateBus();
	bool UpdateFlow();
	bool UpDateAnl();
	bool UpDatePie();
	bool UpdateDmData();
	void SetContourParam();
	void SetRRevSen();
	void GetRevSenSum();
	void GetObjFromDbm();
	void Show(HDC hdc, CRect rt);
	void PaintShow(HDC hdc, CRect rt);
	void ChangeAllSft();
	void ChangeCtlSize(CRect rtd,SUBW_PARAM&pas);
	void ComputMaxXY();
	void ShowC(HDC hdc,HRGN hrgn);
	void ShowC(HDC hdc,CRect rtshow);
private:
	void  SetYbVal(N_ELEGRPYB &yb,YBDATA &data,int j);
	void  PlayHis();
	void  PlaySoe();
	void  AddN1Data(N1BAR &nbar);
	void  CreatePaintRgn();
	HRGN  GetLookDownRgn(HRGN oldrgn);
	HRGN  GetFlowUpdateRgn();
	HRGN  GetLowUpdateRgn();
	void  GetDevSum();
	void  SetDynMeter();
	bool  SelCanZoomLowF();
	void  UpdateLowFData(RFLOW &fw);
	bool  NeedDrawDgx();
	void  ShowFuntTitle(CDIB&mdc,CRect rt,int type);
	bool  ZoomInCheckBus();
	bool  PartZoomChkBus();
	bool  ZoomOutCheckBus();
	bool  ZoomOutApdOpen();
	bool  ZoomInApdOpen();
	

	double oldzm;	//原有放大倍数
	double  vx,vy;	//放大中心点
	int oldsel;
	CRect srt,oldrt;
	CPoint pt1,pt2,oldpt;
	int xmax,ymax;
	int dnbz;
	int oldang; //原来的角度
	BYTE  seltype,selsubtype;//当前选择的类型
	int   seljlh;			 //当前选择记录号
	int   dsjlh;			 //选择设备的数据源记录号
	char  selid[32];		 //选择信号的名称
	//以下五项用于提示条的显示
	CPoint tpint;	  //提示所占位置
	int otype,ostype; //选择的旧提示类型
	int oldcur;		  //旧光标
	int oldjlh;		  //旧记录号
	
	//////////////运行时对象指针/////////////////////
	RANL  *r_an;    //模拟量
	int   ansum;    //模拟量总数
	RMTXT *r_mt;	//多行文本对象
	int   mtsum;	//数量
	RRES  *r_rs;	//水库
	int   rssum;	//水库总数
	RSTA  *r_st;	//状态量和部分设备
	int	  stsum;	//个数
	ROBJ  *r_da;	//日期对象  
	int   dtsum;	//个数
	ROBJ  *r_tm;	//时间对象
	int   tmsum;	//个数
	RAML  *r_am;	//动画对象
	int   amsum;	//个数
	RSCRTXT *r_sc;	//滚动文本对象
	int   scsum;	//个数
	RSELFCTL *r_sf; //自助控件
	int   sfsum;	//个数
	RFLOW *r_fw;	//潮流线
	int fwsum;		//个数	
	RPUSH    *r_ph; //按钮
	int phsum;		//个数
	RACTOBJ  *r_at; //活动对象
	int atsum;		//个数
	RBAR     *r_ba; //棒图
	int basum;		//个数
	RPIE     *r_pe; //饼图对象
	int pesum;		//个数
	RSPIE    *r_spe; //系统饼图
	int  spesum;
	RBUS     *r_bs; //母线
	int bssum;		//个数
	RCONL    *r_cl; //连接线
	int clsum;		//个数
	RMETER   *r_yb; //仪表
	int ybsum;		//个数
	RFLASH   *r_fsh;//FLASH对象
	int fssum;		//个数
	RPPIE    *r_ppie;//百分饼图对象
	int ppsum;		//个数
	RSEN  *r_sen;	//灵敏度
	int    sesum;	//灵敏度个数
	RREV  *r_rv;	//需要备用3DBAR显示对象 包括发电机,电容器两种设备(目前)
	int    rvsum;	//备用对象显示个数
	RREV  *r_tr;	//变压器备用
	int   trsum;    //变压器个数
	RZONE  *r_zn;	//区域
	int    znsum;	//区域个数
	RSWT   *r_sw;	//开关
	int    swsum;	//开关数量
	int dtupdate;   //时间更新标志
	
	////////////////////////////////////////
	HRGN updatergn;	//刷新区域
	////////////////////////////////////////
	N1BAR   *r_n1;
	int     n1sum;
public:
	void ChangeShow();
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_SCADAWIN_H__7A8EC773_EF15_496E_AC5C_288A59EB20D5__INCLUDED_)
