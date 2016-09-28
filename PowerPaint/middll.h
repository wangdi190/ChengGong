#if !defined(AFX_MIDDLL_H__INCLUDED_)
#define AFX_MIDDLL_H__INCLUDED_


///////////////////////////////////////////////////////////////////

typedef struct _SELRESERVOIR{	//设备
	char name[64];		//设备名
	int  id;			//设备ID
}SELRESERVOIR;	
//一下数据用来实现数据选择
typedef struct _SELDATA_DEV{	//数据交换结构
	char mdbnm[256];			//数据库名
	char name[64];				//设备名
	int  did;					//设备ID
	BYTE dtype;					//设备类型
	BYTE xsmode;				//显示模式
	/*
	xsmode定义：
	节点：  0=按电压等级和标幺值显示 1=显示电压绝对值和相角
	线路：  0=始端   1=末端
	变压器：0=三绕组 1=二绕组
	*/
	BYTE tseg;					//时段
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
	char  name[64];				//设备名字
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
	char  name[64];				//设备名字
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
typedef struct _PSvrIpPort
{
	DWORD ip;
	WORD  port;
}PSvrIpPort;

//seldev.dll函数接口
bool WINAPI Select_device(SELECTDEV&indata);	
bool WINAPI SelAnlSHow(SELDATA_DEV &indata);
bool WINAPI SelSingleAnl(SELSINGLE_DEV&indata);
bool WINAPI SelDevSta(SELSINGLE_DEV&indata);
bool WINAPI SelZone(SELDATA_DEV&indata);
bool WINAPI GetNameByID(SELECTDEV&dev);
bool WINAPI GetIDByName(SELECTDEV&dev);
bool WINAPI SelPie(SELECTPIE&indata);
bool WINAPI SelReservoir(SELRESERVOIR&indata);
bool WINAPI SelYbDbs(SINGLEDBS&meter);
//readdata.dll函数接口
bool WINAPI InitMemDbf();
bool WINAPI ReadColorData(DEFCOLOR*cr,int &crsum);
bool WINAPI SetColorData(char *vname,BYTE R,BYTE G,BYTE B);
bool WINAPI GetHmiPath(char  *path);
void WINAPI RegistFileOK(HWND hwnd);
void WINAPI UnRegistFileOK(HWND hwnd);
bool WINAPI GetLastRecFile(char *filename);
bool WINAPI SendHmiFile(char *filename);
bool WINAPI ReadDevViewMsg(void *data,int dtype);
bool WINAPI ReadStaData(READDEV_STA&data);
bool WINAPI ReadDevData(READDEV&data);
void WINAPI SetCurDbf(char *dbfname);
void WINAPI SetSenDemo(int type);
bool WINAPI ReadSenData(READSEN&sn);
bool WINAPI ReadPwSys(PWSYSSUM&ps);
bool WINAPI IsLowFLine(DWORD lineid,int type);
int  WINAPI ReadPmuSvrIpPort(PSvrIpPort *pip);




//CUserApi.dll函数接口
bool WINAPI V_GetAllUSer(my_user *usr, int &un, int usrmax);
void WINAPI V_Encryptpwd(char *pwd,char *name,char *encrypt);
bool WINAPI V_CheckUser(char *name, char *pw,int &type);
bool WINAPI V_ChangePassword(char *name, char *newpw);
bool WINAPI V_DeleteAUser(char *name);
bool WINAPI V_AddNewUser(void *usrdata);
bool WINAPI V_CanUse();
////////////////////////////////////////////////////////////////////////////////
//接口AVCProperty.dll
//设备类型定义
#define DEV_TRANS2 1			//双绕组设备
#define DEV_TRANS3 2			//三绕组设备
#define DEV_GEN 3				//电机设备

//绘图工具：变压器AVC参数设定
//编辑态显示的图形，byType=2,三绕组；byType=1,两绕组
void WINAPI OpenPropertyDlg(DWORD dwTransNo,BYTE byType);


//主程序调用AVC、PQV接口
//建立窗口(主程序启动时调用)
HWND WINAPI	CreateAVCPQVWnd(CWnd* pParent);
//显示窗口(右键设备右键菜单调用)
BOOL WINAPI	ShowAVCPQVWnd(DWORD devnu,BYTE devtype,BOOL bShow=TRUE);
//关闭窗口(主程序关闭时调用)
void WINAPI	CloseAVCPQVWnd();
//////////////////////////////////////////////////////////////////////////////////

//CimRead.dll接口函数
bool WINAPI IsCimOpen();
void WINAPI FreeCim();
bool WINAPI ReadPowerCimFile(char *filename);
bool WINAPI CimSwitch(char *oldname,char *newname,int &vl);

bool WINAPI Cimtransformer(char *oldname,char *newname);
bool WINAPI CimGenerator(char *oldname,char *newname,int &vl);
bool WINAPI CimConpensator(char *oldname,char *newname);
bool WINAPI CimAcLine(char *oldname,char *newname,int &vl);

bool WINAPI CimBusName(char *oldname,char *newname,int &vl);
bool WINAPI CimLoadName(char *oldname,char *newname);

//从CIM返回ID
char* WINAPI IDtoNuName(DWORD ID,int Type,DWORD &iNU);

#endif