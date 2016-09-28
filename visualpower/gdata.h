// gdata.h: interface for the gdata class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GDATA_H__B29BAF22_9BE9_41FD_942E_40DE448A63E6__INCLUDED_)
#define AFX_GDATA_H__B29BAF22_9BE9_41FD_942E_40DE448A63E6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "pwptdef.h"


class gdata
{
public:
	gdata();
	virtual ~gdata();
public:
	void ShowTy(CDIB &mdc,int dx,int dy,CRect rt);
	void ShowBgDbx(CDIB &mdc,int dx,int dy,CRect rt,int high);
	void ShowStatic(CDIB &mdc,int dx,int dy,CRect rt);
	void MSDownShow(CDIB &mdc,int dx,int dy,CRect rt);
	void ShowAct(CDIB &mdc,int dx,int dy,CRect rt);
	void ShowBkgd(CDIB&mdc,CRect rt);
	bool CheckFileIndex(char *filenm, int index);
	bool ZoomPage(int mode);
	bool OpenPwFile(char *fname,int pageno);
	bool OpenHisPwFile(char *hisfile,char *hmifile,int pageno);
	void FreeMem();
	int  GetMPICRecno(int id);
	int  GetPICRecno(int id);
	int  GetEGPRecNo(int id);
public:
	void ShowSwtSccBarj(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum);
	void ShowSwtSccBar(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum);
	bool IsOpenedFile(char *newfile);
	void GetDevObjToTy();
	void FreeMemTyLayer();
	void GetObjRect(CRect &rt);
	DWORD GetDefColor(int index,float val);
	void AddRtnHmi(HISHMI &newhmi);
	bool GetARtnHmi(HISHMI &hmi);
	void SignPaintObj(HRGN hrgn,int dx,int dy);
	void GetSectFLwName(char *nm);
	void Showdms(CDIB&mdc, int dx,int dy,DMSECT *dm,int dmsum,CDRect *srt);
	bool LastHmiIsMode1();
	void ComputeZnZoom(RPIE *r_pe, int pesum,int wy);
	void ComputeSenzomm(RSEN *r_sen,int sesum,int wy);
	void ComputeTpzoom(RREV *r_tr,int trsum,int wy);
	void ComputeTptzoom(RREV *r_tr, int trsum, int wy);
	void ComputePqZoom(RREV *r_rv,int rvsum,int wy);
	void CreateN1EftRgn(N1BAR *r_n1,int n1sum);
	void CreateSPieRgn(RSPIE  *r_spe,int spesum);
	void CreateZnRgn(RPIE  *r_pe,int pesum);
	void CreateSwtSccRgn(RSWT *r_sw,int swsum);
	void CreateSwtRgn(RSWT *r_sw,int swsum);
	void CreateN1Rgn(N1BAR *r_n1,int n1sum);
	void CreateFlwRgn(RFLOW *r_fw,int fwsum);
	void CreateResRgn(RRES  *r_rs,int  rssum);
	void CreateSenRgn(RSEN  *r_sen,int sesum);
	void CreateRevRgn(RREV  *r_rv,int rvsum);
	void CreateTranRevRgn(RREV  *r_tr,int trsum);
	void CreateTranTRgn(RREV  *r_tr,int trsum);
	void SHowN1EftBarj(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum);
	void SHowN1EftBar(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum);
	void SHowSpieBarj(CDIB&mdc,CRect rt,int dx,int dy,RSPIE *r_spe,int spesum);
	void SHowSpieBar(CDIB&mdc,CRect rt,int dx,int dy,RSPIE *r_spe,int spesum);
	void SHowZoneBarj(CDIB&mdc,CRect rt,int dx,int dy,RPIE *r_pe,int pesum);
	void SHowZoneBar(CDIB&mdc,CRect rt,int dx,int dy,RPIE *r_pe,int pesum);
	void SHowSwtBarj(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum);
	void SHowSwtBar(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum);
	void SHowN1Barj(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum);
	void SHowN1Bar(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum);
	void SHowTranTBar(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum);
	void SHowTranTBarj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum);
	void SHowTranRevBarP(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum);
	void SHowTranRevBarPj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum);
	void SHowRevBarPj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum);
	void SHowGenBarQ(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum);
	void SHowGenBarQj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum);
	void SHowRevBarP(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum);
	void SHowSenBarj(CDIB&mdc,CRect rt,int dx,int dy,RSEN *r_sen,int sesum);
	void SHowSenBar(CDIB&mdc,CRect rt,int dx,int dy,RSEN *r_sen,int sesum);
	bool FindAGenCircle(int id,CDRect &rt,CDRect zrt);
	void TJObjSum(int *objsum);
	bool GetChildSendMsg(int id_in, int&id_out, HWND&hwnd);
	void SetChildMenu(HWND hwnd,HMENU hm);
	bool GetALastHmi(HISHMI &hmi);
	void AddOpenHmi(HISHMI &newhmi,char mode=0);
	void LoadShowSet();
	void SaveShowSet();
	void SaveToJpg(HWND hwnd,int width,int height,char *fname);
	void SaveToBmp(HWND hwnd,int width,int height,char *fname);
	void PrintShow(HDC hdc, BYTE pm, int dx, int dy);
	//定义对象区
	N_PAGEPWF  page;			//读入的页面
	N_layer    *clayer;			//当前层
	int		   curpage;			//当前页面
	N_APDINFO  apd;				//附加控制信息
	int        apdenable;		//附加信息是否有效
	////////////投影的设备////////////////////////
	N_LAYER  tylayer;			//投影层
	char       filename[256];	//界面文件名
	//-------------------------------------------
	//过程中的状态
	int selbz;					//有选择的对象
	//历史打开的界面
	HISHMI  hishmi[32];			//可以返回到前面32个画面
	int		curhmi;				//当前hmi
	HISHMI  rtnhmi[32];			//需要返回的界面32个
	int     currtn;			    //当前返回的位置
	//控件菜单对照表
	CTLMENU   ctlmenu[200];		//最大200个
	int cmsum;					//当前应用总数
	int popsum;					//弹出菜单个数
	//初始化文件
	char curfile[256];			//当前界面文件名 
	//基本位图图形缓冲定义
	//小图片
	N_SMALLPIC  spic[MAXSPIC];	//小图片 最大为MAXSPIC
	int spicsum;				//图片总数
	//内存图片
	N_MemPic  mpic[100];		//内存中的图片
	int mpicsum;				//图片数,最大=100
	//组合图元
	N_ELEGRP egp[MAXEGRP];		//组合图元
	int egpsum;					//当前的组合图元数
	//////显示属性配置
	SHOWCFG  scf;				//显示属性配置
	//鼠标操作状态
	int msdwn;					//鼠标左键是否按下0=未按下 1=按下 
	//数据库状态
	int  dbzt;					//历史库浏览状态 0=正常 1=浏览历史
	//各种标志
	////////当前的显示参数///////////////////////////////////
	double curzoom;				//当前的放大倍数
	int    zw,zh;				//当前的图形宽、高
	int	   curang;				//当前旋转角度0-360;
	int    lookdown;			//俯视 0=正常 1=俯视
	/////////////////////////////////////////////////////////
	//发电机备用棒图比例放大参数
	float  pqzm;				//放大比例
	float  hbas;				//基本高度
	/////////////////////////////////////////////////////////
	int		n1bz;
	double	n1zm;			  //n-1母线
//	double	n1linezm;         //n-1支路
	/////////////////////////////////////////////////////////
	//历史回放参数
	time_t hlist[2048]; //历史断面列表
	int    hsum;		//历史断面数
	int    hisjs;		//历史回放计数
	int    hspeed;		//历史回放速度
	BOOL   hdbok;		//历史数据
	int    curtm;		//当前时段
	int    hisplay;		//正在播放标志
	/////////////////////////////////////////////////////////
	CDIB   *msr;        //关联画布的指针
	/////////////////////////////////////////////////////////
	int     curopzt;	
	//当前操作状态  0=正常 1=断面潮流 2=灵敏度 3=低频震荡 4=历史回访 
	//				5=soe回访 6=短路计算 
	//////////////////SOE回放数据////////////////////////////
	NSOES  *soe;	//SOE数据
	int    soesum;	//SOE个数
	/////////////////////////////////////////////////////////
	double znzoom;	//区域柱图放大倍数
private:
	void AddTyAObject(N_BASATTR &attr, void *obuf);
	bool PosIsOk(double x,double y,int start);
	void CreatePctpie();
	void AddCurLayerAObject(N_BASATTR &attr, void *obuf);
	void AddPctPie(double x,double y,int id,int lindex,char *name);
	void ShowDaoBan(CDIB&mdc,CRect rt);
	void SetScfDefaultvalue();
	void GetMenuItem(HWND hwnd,HMENU hmenu);
	void FillBgImg(HDC hdc,CRect rt,int k);
	void AddAEGP(int num, int index, N_BASATTR &attr, void *obuf);
	bool AddAEmptyEGP(int type);
	bool LoadPage(FILE *fp,WORD ver);
	void LoadMemPic(FILE *fp);
	void LoadEGP(FILE *fp,WORD ver);
	void LoadSPic(FILE *fp);
	void InitParam();
	void FreeEgp(int num, int index);

public:
	///////////////////挂牌显示///////////////////////////////
	void DeletePlate(long id, BYTE newValue);
	void AddPlate(PlateInfo pltinfo);
	PlateInfo m_PlateInfo[MAXPLATE];		//挂牌信息记录
	int m_PlateNum;							//挂牌数

	void ShowPlatte(CDIB& mdc);		//显示挂牌
};

#endif // !defined(AFX_GDATA_H__B29BAF22_9BE9_41FD_942E_40DE448A63E6__INCLUDED_)
