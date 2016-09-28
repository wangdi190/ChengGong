#if !defined(AFX_MIDDLL_H__INCLUDED_)
#define AFX_MIDDLL_H__INCLUDED_

#include "pwptdef.h"
#include "visualdb.h"
#include "PublicAvcDef.h"
///////////////////////////////////////////////////////////////////
typedef struct _DEVDEF{	//设备
	char name[24];		//设备名
	int  id;			//设备ID
}DEVDEF,SELRESERVOIR;	
//一下数据用来实现数据选择
typedef struct _SELDATA_DEV{	//数据交换结构
	char mdbnm[256];			//数据库名
	char name[24];				//设备名
	int  did;					//设备ID
	BYTE dtype;					//设备类型
	BYTE xsmode;				//显示模式
	/*
	xsmode定义：
	节点：  0=按电压等级和标幺值显示 1=显示电压绝对值和相角
	线路：  0=始端   1=末端
	变压器：0=三绕组 1=二绕组
	*/
	BYTE yh;					//优化前后
	BYTE tseg;					//时段
	int  mtype;					//运行方式
	char extend[128];			//其他
}SELDATA_DEV;



typedef struct _SELSINGLE_DEV{	//单值数据交换结构
	char mdbnm[256];			//数据库名
	SINGLEDBS dbs;				//数据源
	char extend[128];			//其他
}SELSINGLE_DEV;


typedef struct _SELECTDEV		//选择关联设备
{
	char  dbname[256];			//数据库名
	char  name[24];				//设备名字
	int   did;					//设备ID
	BYTE  type;					//主类型
	BYTE  dtype;				//设备类型 type=2时
	/*
	0="PT" 1="发电机" 2="开关,刀闸",3="负荷",4="电容",5="电抗",
	6="接地",7="二绕组变压器"
	8="三绕组变压器",9="静态无功补偿器",10="逆变、变流器"
	33=母线 34=交流 35=直流
	*/ 
}SELECTDEV;

typedef struct _SELECTPIE		//选择百分饼图参数
{
	char  dbname[256];			//数据库名
	char  name[24];				//设备名字
	int   did;					//设备ID
	BYTE  dtype;				//设备类型	0=交流线路 1=直流线路 2=发电机 
}SELECTPIE;

typedef struct my_user
{
	WORD  id;					//用户ID
	char  Name[15];				//用户名
	char  password[16];			//用户密码
	char  type;					//用户类型
	char  exp[32];				//注解
}my_user;


//PMUSVR结构
/*typedef struct _PSvrIpPort
{
	DWORD ip;
	WORD  port;
}PSvrIpPort;



//低频震荡参数读取格式
typedef struct LowFLPam
{
	DWORD  LineID;						//线路ID
	BYTE  Type;							//类型交流或直流
	BYTE  UnitNo;						//装置号
	BYTE  Index;						//数据序号
	BYTE  DotPs;						//原始数据点数/每秒
	float  MaxV;						//最大幅值限制
}LowFLPam;


/////////////////////////////////////////////////////////////////////////////////////////
//n-1故障读取数据结构
typedef struct N1Data{
	int  id;			//设备ID
	char type;			//故障类型
	float val;			//值
}N1Data;
//告警结果
typedef struct SYSALARM
{
	WORD  Alarm;						//告警状态0,1
	WORD  num;							//发生告警的设备个数
	char  picname[32];					//推出画面名称
	WORD  picno;						//推出画面序号
}SYSALARM;
*/


//seldev.dll函数接口	
bool WINAPI Select_device(SELECTDEV&indata);
bool WINAPI SelAnlSHow(SELDATA_DEV &indata);
bool WINAPI SelSingleAnl(SELSINGLE_DEV&indata);
bool WINAPI SelDevSta(SELSINGLE_DEV&indata);
bool WINAPI SelZone(SELDATA_DEV&indata);
bool WINAPI GetNameByID(SELECTDEV&dev);
bool WINAPI SelPie(SELECTPIE&indata);
bool WINAPI SelReservoir(SELRESERVOIR&indata);

//BJ_SCFileDLL.dll函数接口
//itype为1＝line,2=bus
void WINAPI NT_GetDevBusID(DWORD inu,BYTE itype,int &nf,int &nt);
//itype为1＝bus,2=line
int WINAPI NT_GetDevID(DWORD inu,BYTE itype);
BOOL WINAPI NT_Tfm(int ZoneNU);
BOOL WINAPI NT_Gen(int ZoneNU);

BOOL WINAPI NT_ShowEffect(int iCtgDev,BYTE byType,char* pDirDB);
BOOL WINAPI NT_ShowAllCtg();

//灵敏度计算的相关接口BJ_SCFileDLL.dll函数接口
int  WINAPI NT_CreateDAT(char *FileNameDat);
int  WINAPI NT_FileOutInput(char *FileNameOut,int sentype);
int  WINAPI NT_FileConvertInput(char *FileConvert);

//CUserApi.dll函数接口
bool WINAPI V_GetAllUSer(my_user *usr, int &un, int usrmax);
void WINAPI V_Encryptpwd(char *pwd,char *name,char *encrypt);
bool WINAPI V_CheckUser(char *name, char *pw,int &type);
bool WINAPI V_ChangePassword(char *name, char *newpw);
bool WINAPI V_DeleteAUser(char *name);
bool WINAPI V_AddNewUser(void *usrdata);
bool WINAPI V_CanUse();




/////////////////////////////////////////////////////////////////////////////
// CHisProvider
// See HisProvider.cpp for the implementation of this class
//
//历史数据类型定义
const int HIS_GEN=0;		//发电机
const int HIS_LOAD=1;		//负荷
const int HIS_SHUNT=2;		//电容
const int HIS_SREACT=3;		//电抗
const int HIS_TFM1=4;		//双绕组变
const int HIS_TFM2=5;		//三绕组变
const int HIS_BUS=6;		//母线
const int HIS_LINE=7;		//交流线路
const int HIS_SWITCH=8;		//开关
const int HIS_DCLINE=9;		//直流线路
const int HIS_GND=10;		//接地
const int HIS_RUNTYPE=11;	//运行方式
const int HIS_SEN=12;		//灵敏度
const int HIS_SVC=13;		//静态无功补偿
const int HIS_STATION=14;	//变电站
const int HIS_ZONE=15;		//区域
const int HIS_BUSV=16;		//电压考核曲线
const int HIS_PT=17;		//PT
const int HIS_CVT=18;		//CTV
const int HIS_END=19;		//最后一张历史表序号，添加新表此表顺延！！！
//打开数据提供者,初始化数据库连接
BOOL WINAPI IniProvider();

//关闭数据提供者
void WINAPI	CloseProvider();
//***********************************************************************************//
//先调IniProvider,在调用后面的函数,若不需要了可用CloseProvider关闭数据库连接,释放内存//
//***********************************************************************************//

//保存历史数据
void WINAPI	SaveHisData();

//***********************************************************************************//
//下面三个是历史数据播放函数接口,按顺序调用,GetNextSection的tmCur,可由GetFirstSection//
//的tmList中的值任意选取                                                             //
//***********************************************************************************//
//注册需要播放的数据(pRecord:数据记录指针，num:数量，type:类型)
int WINAPI RegPlayData(DWORD* pRecord,int num,int type);

//获取历史数据断面数(tmStart:开始时间，tmEnd:结束的时间，tmList:断面数时间列表，iMaxSection:tmList可返回最大数)(暂未实现)
int WINAPI GetSectionList(time_t tmStart,time_t tmEnd,time_t* pList,int iMaxSection);

//开始获取数据
BOOL WINAPI	BeginGettingData();

//获取历史数据断面，并存入内存历史库(tmCur:要播放的数据段时间，tmNext:下一个要播放的时间段)(暂未实现)
BOOL WINAPI	GetNextSection(time_t tmCur,time_t &tmNext);

//获取历史数据断面，并存入内存历史库(tmCur:要播放的数据段时间，tmNext:下一个要播放的时间段)(暂未实现)
BOOL WINAPI	GetPreSection(time_t tmCur,time_t &tmNext);

//清除全部注册数据
void WINAPI ClearAllRegData();

//google earth接口
//激活google earth
BOOL WINAPI AttachEarthClient(CWnd* pParent);
//释放google earth
BOOL WINAPI DetachEarthClient();
//定位窗口位置
BOOL WINAPI MoveEarthWnd(CRect* pRect,BOOL bShow=TRUE);
//////////////////////////////////////////////////////////////////////////////////////////
//AVCProperty.dll
//设备类型定义
#define DEV_TRANS2 1			//双绕组设备
#define DEV_TRANS3 2			//三绕组设备
#define DEV_GEN 3				//电机设备

//绘图工具：变压器AVC参数设定
//编辑态显示的图形，byType=2,三绕组；byType=1,两绕组
void WINAPI OpenPropertyDlg(DWORD dwTransNo,BYTE byType);

//VisAVCPQVDll.dll
//主程序调用AVC、PQV接口
//建立窗口(主程序启动时调用)
HWND WINAPI	CreateAVCPQVWnd(CWnd* pParent);
//显示窗口(右键设备右键菜单调用)
BOOL WINAPI	ShowAVCPQVWnd(DWORD devnu,BYTE devtype,BOOL bShow=TRUE);
//关闭窗口(主程序关闭时调用)
void WINAPI	CloseAVCPQVWnd();
//////////////////////////////////////////////////////////////////////////////////////////
//VisHisSOE.dll
void WINAPI LoadNewSOEFile(char* filepath);				//加载新的SOE数据文件，完成新数据入库
void WINAPI GetHisSoe(char** phissoe, int* soelen);		//完成历史记录查询和结果空间返回 soelen指空间总长度, 具体多少个SoeInfo结构体数目为：soenum/sizeof(SoeInfo)
void WINAPI ReleaseHisSoe();

//变压器反时限监视DynMonitorCli.dll
//建立窗口
HWND  WINAPI CreateSvigilWnd(CWnd* pParent,BOOL bShow);
//显示指定变压器
BOOL WINAPI ShowDynTrans(DWORD dwTrans,BYTE byThreeWind,BOOL bShow);
void WINAPI SetAutoShow(BOOL bShow);

//短路电流计算及维护模块(唐工编写的)
//scswitch.dll
//生成GD文件保存--固定参数文件
int WINAPI CreateGDFile(char *mFileName,BYTE itype,BYTE bySign);
//itype =1 为LINE， itype=2 为DCLine,返回值=0 为成功，其他为失败
bool WINAPI  NT_DLSJ(BYTE itype,DWORD linenu);
//故障信息维护	
void WINAPI ShowDlg_GZXXWH(BOOL Module = FALSE);

//评估历史回放EstDemo.dll
HWND  WINAPI CreateDemoWnd(CWnd* pParent,BOOL bShow);

#endif