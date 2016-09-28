// Vpfdata.h: interface for the Vpfdata class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_Vpfdata_H__EE2EAB95_CA63_4190_9615_A9B87A81C116__INCLUDED_)
#define AFX_Vpfdata_H__EE2EAB95_CA63_4190_9615_A9B87A81C116__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "jhdclib3.h"
#include "vpfdef.h"
#include "vpfobj.h"


#define  TYPE_ANALOG 0
#define  TYPE_STATUS 1
#define  TYPE_RATE   2
#define  TYPE_FLOW   3
#define  TYPE_TREND  4
#define  TYPE_ACTIVE 5
#define  TYPE_GIFAML 6

//管理总的绘图数据
class Vpfdata  
{
public:
	Vpfdata();
	virtual ~Vpfdata();
public:
	//定义对象区
	N_PAGEPWF  page;
	int  dnbz,dx,dy;	
	HWND m_hWnd;					//相关窗口
	CWnd *wnd;
	HWND platwnd;					//运行窗口句柄，对对话框而言，是指启动对话框的父窗口
	N_SMALLPIC  spic[MAXSPIC];		//小图片 最大为MAXSPIC
	N_MemPic	mpic[100];			//内存中的图片
	N_ELEGRP	egp[MAXEGRP];		//组合图元
	int    spicsum,mpicsum,egpsum;	//当前的组合图元数
	DWORD  vcolor[7];				//系统颜色
	int    selpsh,oldsel,dnpsh,spljl,cursor;
	RCURE    *r_cur;	//曲线对象
	ROBJ     *r_pi;		//饼图
	RANL	 *r_an;		//模拟量
	RSTA     *r_st;		//状态量和部分设备
	RRAT     *r_ra;		//累加量
	ROBJ	 *r_da;		//日期对象  
	ROBJ	 *r_tm;		//时间对象
	RAML	 *r_am;		//动画对象
	RSCRTXT  *r_sc;		//滚动文本对象
	RSELFCTL *r_sf;		//自助控件
	RFLOW    *r_fw;		//潮流线
	RTREND   *r_td;		//趋势
	RPUSH    *r_ph;		//按钮
	RACTOBJ  *r_at;		//活动对象
	RCOMCTL  *r_com;	//标准控件
	RSPL     *r_spl;	//分割器
	int  dtsum,tmsum,amsum,scsum, sfsum;
	int  fwsum,tdsum,phsum,splsum,atsum;
	int  ansum,stsum,rasum,comsum,pisum;
	int  cursum;
public:
	bool VSetText(int id,char *str,CRect&rt);
	int SetBgColor(DWORD bcolor);
	bool  ZoomPage(int mode);
	bool  VSetLineEnable(int id,BYTE enable);
	bool  VSetEgrpEnable(int recno,BYTE enable);
	bool  VSetPicDepth(BYTE depth,int id);
	void  PrintPage();
	bool  SetCureColor(WORD curid,int index,DWORD color);
	bool  SetCureData(WORD curid,int index,int ndot,float *val);
	bool  AddNewPath(char *pathname);
	void  InitDialog();
	void  Show(HDC hdc, CRect rt);
	void  ShowA();
	void  ShowC();
	void  OnTimer1000(HDC hdc);
	void  OnTimer500(HDC hdc);
	void  OnTimer50(HDC hdc);
	void  OnSize(int cx,int cy);
	void  OnSplMove(CPoint point);
	int   GetCursor(CPoint point);
	void  ShowPush(int j);
	void  OnSplDown(CPoint point);
	void  OnSplUp(CPoint point);
	void  SetToLocalFile(char *infile, char *outfile);
	bool  OpenNpFile(char *fname,int picn);
	void  FreeMem();
	void  SetPage();
	void  ClosePage();
	bool  GoToPage(int pageno=0);
	int   GetDrawSize(int sz);
	int   GetPICRecno(int id);
	void  ActRtToScr(CRect&rt);
	int   GetMPICRecno(int id);
	int   GetEGPRecNo(int id);
	bool  GetDevSiteParam(int id,int sitn,BYTE &vlev,BYTE &ele);
	void  UpdateAnalog(HDC hdc,Vpfobj *bs,R_ANL&v);
	void  UpdateStatus(HDC hdc,Vpfobj*bs,R_STA&v);
	void  UpdateRate(HDC hdc,Vpfobj*bs,R_RAT&v);

private:
	void  autoactobj(HDC hdc);
	void  OnSizeCtl(int cx, int cy);
	void  ComputMaxXY();
	short GetActSize(int sz);
	void  ScrRtToAct(CRect&rt);
	void  ScrPtToAct(CPoint&pt);
	void  ActPtToScr(CPoint&pt);
	void  ShowAllobj(CDIB &mdc, int dx, int dy,CRect rt);
	void  Run_ShowOnBg(CDIB &mdc,int dx,int dy,CRect rt);
	void  Showobject(CDIB &mdc, int dx, int dy,CRect rt);
	void  ShowBkgd(CDIB&mdc,CRect rt);
	bool  CheckFileIndex(char *filenm,int index);
	void  PrintShow(HDC hdc,BYTE pm,int zx,int zy);
	int   GetSum(int type);
	void  PreShowEGPEx(CDIB&mdc,int num, CRect rt,int index,int dx,int dy);
	void  PreShowEGP(CDIB&mdc,int num, CRect rt,int index);
	void  SaveToJpg(CDIB&mdc,char *fname);
	void  SaveToBmp(CDIB &mdc,char *fname);
	void  LoadPage(FILE *fp);
	void  ClearSelect();
	void  InitParam();
	//绘图过程中的状态
	int   selbz;				//有选择的对象
	//初始化文件
	char  curfile[256];	        //当前界面文件名
	int   frz;				    //屏幕冻结
	int   curzoom;			    //当前放大倍数
	CRect  srt;					//
	int wx,wy;
	RUNPATH  path[5];			//最大支持5套路径
	int  pathsum;				//有效路径数
private:
	int    wd,hg,flwjg,oldz,xmax,ymax;
	CDIB   mbg;			//背景画面
	CDIB   msr;			//显示画面
	CDIB   mtp;			//中间画面
	
	CPoint pt1;
	CFont  font,sfont;
	//动态数据定义

	CPoint oldp1,oldp2;
	int ks;
	
	
private:
	void PrintActiveObj(HDC hdc,int zx,int zy);
	void ShowB(HDC hdc,CRect rt);
	void GetSplRunParam(SUBW_PARAM&pad,RSPL&pas);
	void GetObjFromDbm();
	void FreeMemRun();
	void Showdtime(HDC hdc);
	void ShowGifAml(HDC hdc,int mode=0);
	int  GetLineNum(char *str);
	void ClrStrEnter(char *str);
	void ShowAScrTxt(HDC hdc, int j,int mode=0);
	void ShowScrTxt(HDC hdc);
	void ShowFlow(HDC hdc);
	void ShowActGrp(CDIB &mdc,int dx, int dy);
	void TestShow1(CDIB &mdc, int dx, int dy,CRect rt);
	void TestShow2(CDIB &mdc, int dx, int dy,CRect rt);
	void TestShow(CDIB &mdc, int dx, int dy,CRect rt);
	void CreateFlwRgn(int j);
	void ShowTrend(HDC hdc);
	void ShowAllPush(CDIB&mdc);
	int  IsInPush(CPoint point);
	
	void GetActPicMsg(int i);
	void ShowActObj(HDC hdc,int x,int y,int k);
	void AutoSetActValue(int i);
	bool IsFileExist(char *filename);
	void ShowAFlow(HDC hdc, int i);
	CWnd * InitComCtl(N_COMCTL *cm, CRect rt);
	void ShowCtlOutline(HDC hdc,int sx,int sy);
	void InitSplitass();
	int  ComputPos(int wh, int type);
	void GetSflRunParam(SUBW_PARAM&pad,RSELFCTL&pas);
	void GetComRunParam(SUBW_PARAM&pad,RCOMCTL&pas);
	void GetHwInRT(CRect rt,SUBW_PARAM *spw,int &sum);
	void ComputSplDrawLine(CPoint point,CPoint &p1,CPoint &p2);
	void ChangeCtlSize(CRect rtd,SUBW_PARAM&pas,int ly=1);
	void ComputSplRect(int j);
	void ReSizeObj(CRect rts,CRect rtd,CRect rt,CRect &rtr);
	int  GetOutLineWidth(int type);
	void CreatePaintRGN();


	void  AddAObject(N_BASATTR &attr, void *obuf);
	void  FillBgImg(HDC hdc,CRect rt,int k);
	//以下为图形部分
	void  FreeEgp(int num, int index);
	void  LoadSPic(FILE *fp);
	void  LoadEGP(FILE *fp);
	void  LoadMemPic(FILE *fp);
	bool  AddAEmptyEGP(int type);
	void  AddAEGP(int num, int index, N_BASATTR &attr, void *obuf);
	int   GetANoUseEGPID();
	void  FreeGrpMem();		  //释放图形类型	
};

#endif // !defined(AFX_Vpfdata_H__EE2EAB95_CA63_4190_9615_A9B87A81C116__INCLUDED_)
