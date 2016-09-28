// comobj.h: interface for the comobj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_COMOBJ_H__5A159CFD_9EC6_4AEA_B869_93948FE28E98__INCLUDED_)
#define AFX_COMOBJ_H__5A159CFD_9EC6_4AEA_B869_93948FE28E98__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "workwin.h"
#include "canvas.h"
#include "pagectl.h"
#include "naviwin.h"
#include "mainwin.h"
#include "spiwin.h"
#include "egpwin.h"
#include "layerwin.h"
#include "undoop.h"
#include "tlswin.h"
#include "editobj.h"


//管理公共对象：小图标，位图，组合图元等
typedef struct FONTLIST{
  char FaceName[LF_FACESIZE]; 
}FONTLIST;

typedef struct RUNPATH{
  char path[256];
}RUNPATH;


class comobj  
{
public:
	comobj();
	virtual ~comobj();

	BYTE  shadow;				//是否投影
	BYTE  fill;					//是否填充
	BYTE  fillmode;				//填充模式
	BYTE  outline;				//是否有边线
	DWORD outcolor;				//边线色
	DWORD bcolor1;				//背景颜色
	DWORD bcolor2;				//背景颜色
	DWORD tcolor;				//文本颜色
	DWORD ncolor;				//模拟量正常颜色
	DWORD acolor;				//模拟量告警颜色
	BYTE  close;				//是否封闭
	BYTE  linewd;				//线宽度
	BYTE  mcline;				//是否联动线路
	BYTE  tmode;				//文本模式 0=无 1=阴影 2=空心 3=凹 4=凸
	LOGFONT font;				//当前字体
	BYTE  vl;					//设备电压等级
	//窗体颜色
	DWORD ebcolor;				//组合图元对话框背景
	//字体数据
	FONTLIST fontlist[100];		//字体名字
	int  fzs;					//字体总数
	int  fontindex;				//字体索引
	bool IsInfont(char *name);
	void GetFontName();
	//图形样板
	int  patternID;				//样板ID号,初始为-1;
	//小图片
	N_SMALLPIC  spic[MAXSPIC];	//小图片 最大为MAXSPIC
	int spicsum;				//图片总数
	//内存图片
	N_MemPic  mpic[100];		//内存中的图片
	int mpicsum;				//图片数,最大=100
	//组合图元
	N_ETNAME segp[MAXEGRP];		//SVG转换时的名字
	N_ELEGRP egp[MAXEGRP];		//组合图元
	int egpsum;					//当前的组合图元数
	int  typeidx[MAXEGRP];		//选择类型后保存的索引
	int  selsum;				//选择类型的图元数
	//GIF动画片
	N_MGifAml gal[MAXGIF];		//GIF动画
	int cursor;					//当前光标
	RUNPATH path[2];			//所有相关路径

	LOGFONT sysfont;			//系统用字体
	CMenu   menu1;				//菜单
	HCURSOR hcur[20];			//光标
	int test;					//测试状态
    double curzoom;				//当前的放大倍数
	//编辑选择配置
	DWORD vcolor[25];			//系统颜色

	WORD  gwide;				//网格宽度
	BYTE  gstyle;				//网格式样
	DWORD gcolor;				//上次编辑时网格颜色
	BYTE  gshow;				//是否显示
	int edobj;					//编辑属性状态
	undoop  unp;				//UNDO定义
	//标注显示--标志
	int nocondev;//未连接的设备
	int nocdev;  //未关联库的设备
	int showsite;//显示端子
	//剪贴板CJH_PW0类型
	UINT  clptype;
public:
	void ResetAEgpRt(int i,CDRect &rtr);
	void ResetEgpRt();
	void DelAMpic(int j);
	void SetVLColor(char *vlname,DWORD color);
	int  GetFontIndex(char *facename);
	void SetToLocalFile(char *infile,char *outfile);
	bool IsFileExist(char *filename);
	int  GetGifAnlRec(char *filename);
	void AddGifAnlUse(int i);
	void DelAGifAnl(int i);
	void OpenGifAnl(int i,char *filename);
	int  GetNoUseGal();
	void AddMpic(char *filename, int id);
	int  GetANoUseMPICID();
	int  GetEGPRecNo(int id);
	int  GetANoUseEGPID();
	void AddAEGP(int num, int index, N_BASATTR &attr, void *obuf);
	bool AddAEmptyEGP(int type);
	void LoadMemPic(FILE *fp);
	void LoadEGP(FILE *fp,WORD ver);
	void LoadSPic(FILE *fp);
	int  GetEleGrpSize(int num,int index);
	int  SaveEGrp(FILE *fp);
	int  SaveMPic(FILE *fp);
	int  colornums(int bits);
	int  SaveSpic(FILE *fp);
	int  GetANoUsePICID();
	void FreeMem();
	void InitParam();
	int  GetPICRecno(int id);
	void SpicAddSubUse(int id,int time);
	int  GetMPICRecno(int id);
	void MpicAddSubUse(int id,int time);
	void FreeEgp(int num, int index);
private:
	void InitPath();
//所有的需要交叉的子窗口指针定义
public:
	bool IsSameWhithOther(int index);
	bool SetColor(char *vname,BYTE r,BYTE g,BYTE b);
	void ReadDefColor();
	NaviWin   *nwin;
	workwin   *wwin;
	canvas    *cvs;
	pagectl   *pgcw;
	CMainWin  *mwin;
	egpwin    *egpw;
	spiwin    *spiw;
	layerwin  *layw;
	tlswin    *tlsw;
	editobj   *objw;
};

#endif // !defined(AFX_COMOBJ_H__5A159CFD_9EC6_4AEA_B869_93948FE28E98__INCLUDED_)
