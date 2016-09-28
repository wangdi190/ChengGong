// comobj.h: interface for the comobj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMOBJ_H__5A159CFD_9EC6_4AEA_B869_93948FE28E98__INCLUDED_)
#define AFX_COMOBJ_H__5A159CFD_9EC6_4AEA_B869_93948FE28E98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "histoolbar.h"
#include "mainfrm.h"
#include "mainwin.h"
#include "scadawin.h"
#include "msalmwin.h"
#include "lowfwin.h"
#include "gdata.h"
#include "navwin.h"
#include "chrgwin.h"
#include "soeplaybar.h"
//管理公共对象：小图标，位图，组合图元等

typedef struct I_HOTKEY{//热键定义
   BYTE type;			//类型0=字符或数字 1=F0-F9键
   BYTE kvalue;			//键值
   char filename[64];   //NP文件名
   WORD index;			//画面索引
}I_HOTKEY;

typedef struct I_MENU{  //预定义界面菜单
   char itemname[32];	//菜单显示名
   char filename[32];   //PW文件名
   WORD index;			//画面索引
   int  cmdid;			//命令ID
}I_MENU;
typedef struct I_GROUP{
	char popname[32];
	I_MENU *pm;
	int pmsum;
	CMenu menu;			//菜单
}I_GROUP;




class comobj  
{
public:
	comobj();
	virtual ~comobj();
	CImageList simg;			//32*32图标
	CMenu menu;					//主菜单
	HCURSOR  hcur[11];			//光标
	DWORD    vcolor[25];		//系统颜色
	CMenu pmenu;				//设备右键菜单
	CMenu rmenu;				//界面切换右键菜单
	CMenu fmenu;				//全屏显示时的右键菜单
	CMenu dmenu;				//等高线菜单
	CMenu fwmenu;				//潮流菜单
	CMenu platemenu;			//挂牌菜单

	CMenu amenu;				//告警菜单
	CMenu tmenu;				//告警表格菜单
	CMemDC  amdc;				//告警图形
	char curnm[32];				//当前用户名
	char curpw[32];				//当前用户密码
	int  utype;					//用户类型
	int  autotp;				//是否启动图形拓扑着色
	/////由pagemg来
	I_GROUP gp[10];				//预定义菜单，最多10组
	int curgp,gpsum;			//菜单个数	
	I_MENU  mainpage;			//主页
	I_MENU  Lowfpage;			//低频震荡页面
	BYTE	mpok;				//主页是否打开成功OK
	char runpath[256];			//界面文件路经
	char startpath[256];		//程序启动目录
	char senfilepath[256];		//灵敏度文件保存目录
	
	char sndfile[256];
	char lowfsnd[256];

	I_HOTKEY  *hotkey;			//热键指针
	int  hotsum;				//当前热键数
	//盗版标志
	int daoban;					//盗版标志
	//平台是否准备好
	bool dbok;					//true=已打开 false=未打开
	//母线图形关联关系
	BUSFILE *fbus;				//已关联
	int      fsum;				//关联个数
	//公共字体
	LOGFONT font1;				//显示盗版用字体
	/////////////////////////////////////////////////////////
	//系统大型缓冲区
	char *sysbuf;//缓冲区地址
	int  syssize;//空间大小
	/////////////////////////////////////////////////////////
	int  userlev;				//用户登录级别

	 //需要显示的变压器
	SHOW_EQU showtrans[400];
	int shownum;
public:
	void Syspiebar();
	void Zonebar();
	void SaveShowTrans();
	void N12eft3d();;
	void ManuDlperator();
	void DlDlperator();
	void N_1Operator(int rev,int readnum);
	void FunctChange();
	void SetNewCursor(int newcur);
	void ReShowToolBar();
	void SetToNeedMode(int mode);
	void MakeMenu();
	bool GetHotPic(BYTE type,BYTE val,char *fnm,int &index);
	void ReadIni_File();
	void SetToLocalFile(char *infile, char *outfile);
	bool GetCMDPage(int id,char *fnm,int&num);
	void GetMenu(FILE*fp);
	int  TypeTran(int type,int subtype);
	void ReadDefColor();
	void SetVLColor(char *vlname,DWORD color);
	void SetCurUser(char *user,char *pw,int ut);
	void ShowSimg(HDC hdc,int x,int y,int index, int width=0, int height=0);
	void LoadImg();
	void InitParam();
	bool IsFileExist(char *filename);
public:
	void Btnreturn();
	void StartSoe();
	void HisSpup();
	void HisSpdown();
	void Nexthmi();
	void Showdgx();
	void OnShowdgx();
	void Lasthmi();
	void Cfgattr();
	void Newpage();
	void Mainpage(bool first=true);
	void ReOpenFile(char *filename);
	bool PutHotKeyPic(BYTE type, BYTE val);
	void GoToCMDPage(int id);
	void MdlSelLine();
	void Byqwd();
	void Tranrev();
	void Genrevq();
	void Genrev();
	void Linesen();
	void Bussen();
	void Senopr();
	void Zoomall();
	void Savetojpg();
	void Savetobmp();
	void Zoomnml();
	void PrintPage();
	void Dmflow();
	void Starthis();
	void ToLowf();
	void CloseHisPrc();
	void ResetFunct(int resetzoom,int issetfun=0);
	bool GetBusGrp(int id,char *grpname,int &pno);
	void LoadBusRalate();
	CMainFrame *fwin; //框架窗口
	CMainWin   *mwin; //主窗口
	HisToolbar *hbar; //历史重演工具条
	CToolBar   *sbar; //SCADA工具条
	MsAlmWin   *vbar; //统计棒
	ScadaWin   *swin; //scada窗口
	CStatusBar *tbar; //状态条地址
	CToolBar   *dmbar;
	CToolBar   *sebar;
	CNavWin    *nwin;
	CChrgWin   *cwin; //色谱窗口
	SoePlayBar *ebar; //SOE回放工具条
	FunToolBar *funbar;
	gdata      *dbm;
private:
	void N1FunSet(int n1type);
	void ReadShortCC();
	void ReadN1GZ(int n1type);
	void GetLOWFSndFile(FILE *fp);
	void GetSndFile(FILE *fp);
	void GetLowfFile(FILE *fp);
	void GetSysMemory();
	char *GetMenuName(char *nbuf, char *lbuf);
	void TestDir(char *path);
	void ReadAutotp(FILE*fp);
	bool AnalyHotKey(char *kstr,BYTE &type,BYTE &val);
	int  FindKey(char *key);
	void ReadHotKey(FILE*fp);
	void AddHotKey(I_HOTKEY hk);
	void ComputCMD();
	void ReadSubMenu(FILE*fp);
	void GetMainPage(FILE*fp);
	int  IsKeyw(char *buf);
	void AnalyseLine(FILE *fp,char *line);
	bool ReadLine(FILE*fp,char *buf);
	void AddMenuItem(char *nm,char *fnm,WORD index);
};

#endif // !defined(AFX_COMOBJ_H__5A159CFD_9EC6_4AEA_B869_93948FE28E98__INCLUDED_)
