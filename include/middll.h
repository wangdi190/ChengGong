#if !defined(AFX_MIDDLL_H__INCLUDED_)
#define AFX_MIDDLL_H__INCLUDED_

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
typedef struct _PSvrIpPort
{
	DWORD ip;
	WORD  port;
}PSvrIpPort;

//seldev.dll函数接口	
bool WINAPI SelAnlSHow(SELDATA_DEV &indata);
bool WINAPI SelSingleAnl(SELSINGLE_DEV&indata);
bool WINAPI SelDevSta(SELSINGLE_DEV&indata);
bool WINAPI SelZone(SELDATA_DEV&indata);
bool WINAPI GetNameByID(SELECTDEV&dev);
bool WINAPI SelPie(SELECTPIE&indata);
bool WINAPI SelReservoir(SELRESERVOIR&indata);
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
//NT_DEVICE.DLL函数接口
bool WINAPI NT_SelDev(SELECTDEV &indata);
bool WINAPI NT_EditDev(int &intNU,char *devname,int type,int subtype);

//历史库操作browhis.dll函数接口
bool WINAPI SelHisFile(char *path,int &sum,int &year,int &month,int&day);
int  WINAPI GotoNextTime(int &hour,int &min,int &sec);
int  WINAPI GotoSegTime(int &hour,int &min,int &sec,int n);
void WINAPI StopBrowHis();
bool WINAPI InitDbPlat();
bool WINAPI OpenhDlg(char *filename,char *hmifile,int &page);

//灵敏度计算的相关接口NT_SCFileDLL.dll函数接口
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


#endif