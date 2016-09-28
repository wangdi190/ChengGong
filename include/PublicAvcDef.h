#if !defined(AFX_AVCDEFPUBLIC_H__INCLUDED_)
#define AFX_AVCDEFPUBLIC_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//visualpw_Station的status字段状态位
const short STATION_LOCKED=0x10;//1<<8;   //闭锁位

//visualpw_Tfm1的status字段状态位
//visualpw_Tfm2的status字段状态位
const short TRANSFORM_LASTUP=1<<0;   //最后动作升位
const short TRANSFORM_HREGU=1<<1;   //高压有载调压位
const short TRANSFORM_MREGU=1<<2;   //中压有载调压位
const short TRANSFORM_LREGU=1<<3;   //低压有载调压位

const short TRANSFORM_LOCKED=0x10;//1<<8;   //闭锁位

//visualpw_Shunt的status字段状态位
const short SHUNT_LOCKED=0x10;//1<<8;   //闭锁位

//visualpw_Gen的status字段状态位
const short GENERATOR_PNOR_CTRLV = 0;//P正常，控制电压 平衡机
const short GENERATOR_FIXPQ = 1;//固定P、Q输出
const short GENERATOR_FIXP_CTRLV = 2;//固定P输出，控制电压 PV节点
const short GENERATOR_PNOR_FIXQ = 3;//P正常,固定Q输出

//电压等级
const unsigned char VOLTAGE_DEG_380 = 0;//380V
const unsigned char VOLTAGE_DEG_3K = 1;//3kV
const unsigned char VOLTAGE_DEG_6K = 2;//6kV
const unsigned char VOLTAGE_DEG_10K = 3;//10kV
const unsigned char VOLTAGE_DEG_35K = 4;//35kV
const unsigned char VOLTAGE_DEG_63K = 5;//63kV
const unsigned char VOLTAGE_DEG_110K = 6;//110kV
const unsigned char VOLTAGE_DEG_220K = 7;//220kV
const unsigned char VOLTAGE_DEG_330K = 8;//330kV
const unsigned char VOLTAGE_DEG_500K = 9;//500kV
const unsigned char VOLTAGE_DEG_60K = 10;//60kV
const unsigned char VOLTAGE_DEG_132K = 11;//132kV
const unsigned char VOLTAGE_DEG_13K8 = 12;//13.8kV
const unsigned char VOLTAGE_DEG_13K2 = 13;//13.2kV
const unsigned char VOLTAGE_DEG_33K = 14;//33kV
const unsigned char VOLTAGE_DEG_24K = 15;//24kV
const unsigned char VOLTAGE_DEG_20K = 16;//20kV

//****TISLAND的SeResult成员取值********************
const unsigned char SE_SUCCESS = 0;//计算成功
const unsigned char SE_INVALID = 1;//电气岛无效
const unsigned char SE_INOBSERV = 2;//不可观测
const unsigned char SE_NOCONVERGE = 3;//不收敛
const unsigned char SE_ERROR = 4;//计算错误
const unsigned char SE_ELIGIBLELOW = 5;//合格率过低
//*********************************************************

//****TISLAND的OpfResult成员取值*******************
const unsigned char OPF_SUCCESS = 0;//计算成功
const unsigned char OPF_NOCONVERGE = 1;//不收敛
const unsigned char OPF_ERROR = 2;//计算错误
//*********************************************************

/******************************************************************
**类名：SHADY_TABLE
**描述：SHADY_TABLE对应于数据库的可疑数据表
******************************************************************/
struct SHADY_TABLE
{
	BYTE bType;//可疑数据类型，见下文的成员取值
	char szInfo[160];
};

//****SHADY_TABLE的bType成员取值**********************
const unsigned char SHADINESS_NONMEASURE=6;   //伪量测信息
const unsigned char SHADINESS_ERRORDATA=5;   //可疑量测
const unsigned char SHADINESS_BADDATA=4;   //坏数据
const unsigned char SHADINESS_BRANCH_BALANCE=3;   //支路不平衡
const unsigned char SHADINESS_NODE_BALANCE  =2;   //节点不平衡
const unsigned char SHADINESS_SWITCH_BRANCH =1;   //可疑开关支路组合
const unsigned char SHADINESS_OTHER_CASE    =0;   //其他拓扑不平衡数据
//*********************************************************

const unsigned char AVC_QUIT=1;
const unsigned char AVC_OPERATE_LOCK=2;

//优化配置定义
const unsigned short STUS_DEVLOCKED=0x0100;			//闭锁状态
const unsigned short STUS_DEVOPFED=0x0200;			//优化状态
const unsigned short AVC_RUN=0x0300;
const unsigned short AVC_OPERATE_NORMAL=0x400;

//厂长专用
const unsigned short STUS_VALUETYPE=0x0400;			//力率定值，默认为采用无功定值
//电机专用
const unsigned short STUS_GEN_P_CV=0x0100;			//正常P，电压控制
const unsigned short STUS_GEN_P_Q=0x0200;			//P、Q电机
const unsigned short STUS_GEN_FIXP_CV=0x0400;		//固定P、电压控制
const unsigned short STUS_GEN_P_FIQ=0x0400;			//正常P、固定Q
//变压器专用
const unsigned short STUS_CTRL_HI=0x0800;			//高压可调
const unsigned short STUS_CTRL_MID=0x0400;			//中压可调
const unsigned short STUS_CTRL_HM=0x0c00;			//高中压可调
const unsigned short STUS_CTRLV_HIG=0x3000;			//监测高压侧电压
const unsigned short STUS_CTRLV_MID=0x2000;			//监测中压侧电压
const unsigned short STUS_CTRLV_LOW=0x1000;			//监测低压侧电压
const unsigned short STUS_GATETFM=0x0300;				//关口变压器

//母线专用
const unsigned short STUS_GATEBUS=0x0300;			//关口母线
const unsigned short STUS_ENFORCE_V=0x0400;			//制电压限值监测
const unsigned short STUS_ENFORCE_VC=0x0800;		//制电压变化监测 
const unsigned short STUS_BUS_PQBUS=0x0001;			//负荷母线


typedef struct AVCLimitParam			//AVC控制定值参数
{
	AVCLimitParam(){	memset(this, 0, sizeof(AVCLimitParam));}
	DWORD nu;			//定值编号
	float bvol;			//基础电压
	float voldn;		//电压下限
	float volup;		//电压上限
	float cosdn;		//功率因数下限
	float cosup;		//功率因数上限
	float gcosdn;		//关口功率因数下限
	float gcosup;		//关口功率因数上限
	int capnum;			//电容器控制数量
	int xfmnum;			//变压器控制数量
	CTime startt;		//起始时间
	CTime endt;			//终止时间
}AVCLimitParam;	


typedef struct BusVoltageRate				//电压合格率信息
{
	BusVoltageRate(){memset(this, 0, sizeof(BusVoltageRate));}
	BYTE type;			//类型0系统、1区域、2变电站、3母线
	DWORD zoneNU;		//上级编号，母线为厂站 ，厂站为区域
	DWORD parentNU;		//上级编号，母线为厂站 ，厂站为区域
	DWORD NU;
	char Name[64];
	BYTE datetype;		//时间类型0日数据、1小时数据
	float fvolleavel;		//电压等级
	float fmaxvalue;		//越限幅度
	float fminvalue;		//越限幅度
	UINT outtime;		//越限时长(秒)
	UINT alltime;		//总时长(秒)
}BusVoltageRate;

const BYTE VolRate_system=0;
const BYTE VolRate_zone=1;
const BYTE VolRate_sub=2;
const BYTE VolRate_bus=3; 

typedef struct CtrlInfo					//控制信息
{
	CTime tm;			//时间
	float oldpos;		//原始状态
	float newpos;		//调整状态
	float oldv[3];		//原始电压，如果是变压器就是各侧；
	float newv[3];		//调整电压
	float oldcos;		//原始功率因数
	float newcos;		//调整功率因数
}CtrlInfo;

typedef struct DistribCtrlRate			//控制分布信息
{
	DistribCtrlRate()
	{
		Name[0]=0;
		ctrlinfo.RemoveAll();
	}
	~DistribCtrlRate()
	{
		int count = ctrlinfo.GetSize();
		for(int i=0; i<count; i++)
		{
			CtrlInfo* ptmp = (CtrlInfo*)ctrlinfo.GetAt(i);
			if(ptmp!=NULL)
				delete ptmp;
		}
		ctrlinfo.RemoveAll();
	}
	BYTE type;			//控制设备类型
	DWORD zone;			//区域
	DWORD Station;		//厂站
	DWORD NU;
	char Name[64];
	BYTE datetype;		//时间类型0日数据、1小时数据
	CPtrArray ctrlinfo;
}DistribCtrlRate;

typedef struct DevCosRate				//设备功率因数合格率信息
{
	DevCosRate(){memset(this, 0, sizeof(DevCosRate));}
	BYTE devtype;		//设备
	DWORD zoneNU;		//区域
	DWORD stationNU;	//厂站
	DWORD NU;
	char Name[64];
	BYTE gatetype;		//关口类型0普通、1关口
	float fcos;			//越限幅度
	UINT outtime;		//越限时长(秒)
	UINT alltime;		//总时长(秒)
}DevCosRate;


//********定义实时展示指标**********严格对应RealAVCCapably表的顺序*******************************
typedef enum SystemCapably
{
	VolRate_System=0,
	VolRate_SystemOut,
	VolRate_500,
	VolRate_220,
	VolRate_110,
	VolRate_35,
	VolRate_10,
	CosRate_System,
	CosRate_SystemOut,
	DevAct_System,
	DevAct_Trans,
	DevAct_Shunt,
	AVCAct_System,
	AVCAct_Trans,
	AVCAct_Shunt,
	AVCAct_RefuseNum,
	PowerLoss_SystemP,
	PowerLoss_SystemQ,
	PowerLoss_TransP,
	PowerLoss_TransQ,
	PowerLoss_LineP,
	PowerLoss_LineQ,
	PowerLoss_AVC,
	LockInfo_System,
	LockInfo_Bus,
	LockInfo_Trans,
	LockInfo_Shunt,
	ZoneInfo_Island,
	ZoneInfo_CtrlZone=28,
	VolRate_AVCVol=29,
	LockInfo_SystemNum=30,
	PowerLoss_ShuntQ=31,
	PowerLoss_GenP=32,
	PowerLoss_GenQ=33,
	PowerLoss_LoadP=34,
	PowerLoss_LoadQ=35,
	Capably_End
}SystemCapably;


//*********定义实时展示指标****************************************


//关于三态数据状态的描述
//厂站
const BYTE RUNDATA_STA_OldVolOut=0x01;				//原始电压越限
const BYTE RUNDATA_STA_VolOut=0x02;					//电压越限
const BYTE RUNDATA_STA_OldCosOut=0x04;				//原始无功越限
const BYTE RUNDATA_STA_CosOut=0x08;					//无功越限
const BYTE RUNDATA_STA_CtrlCmd=0x10;				//有控制指令
//挂三种牌，电压变化牌（电压类不为0就挂），无功变化牌（无类不为0就挂），控制指令牌（存在RUNDATA_STA_CtrlCmd就挂）

//母线
const BYTE RUNDATA_BUS_OldVolOut=0x01;				//原始电压越限
const BYTE RUNDATA_BUS_VolOut=0x02;				//电压越限
//挂一种牌，电压变化牌，只要不为0就应该挂牌

//变压器
const BYTE RUNDATA_TFM_OldCosOut=0x01;		//原始无功越限
const BYTE RUNDATA_TFM_CosOut=0x02;				//无功越限
const BYTE CTRLDATA_TFM_TfmDn=0x04;				//变压器降档
const BYTE CTRLDATA_TFM_TfmUp=0x08;				//变压器升档
//挂二种牌，无功变化牌，控制指令牌（升档指令牌或降档指令牌）

//电容
const BYTE CTRLDATA_SHUNT_ShuntClose=0x01;			//电容退出
const BYTE CTRLDATA_SHUNT_ShuntOpen=0x02;			//电容器投入
//挂一种牌，控制指令牌（投入指令牌或退出指令牌）




#endif // !defined(AFX_AVCDEFPUBLIC_H__INCLUDED_)
