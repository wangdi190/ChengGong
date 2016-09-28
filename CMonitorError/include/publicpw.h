#if !defined(AFX_PUBLICPW_H__INCLUDED_)
#define AFX_PUBLICPW_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//变电站类型
/*const int STATION_W=1;		//水电
const int STATION_H=2;		//火电
const int STATION_T=3;		//变电站
const int STATION_C=4;		//换流站
const int STATION_O=5;		//其他*/
typedef enum _ZONE_TYPE			//区域定义
{
	ZONE_GEOGAREA=1,	//地域定义
	ZONE_POROVINCE,		//省定义
	ZONE_REGION,		//地区定义
	ZONE_POWERSTATION	//电厂定义
}ZONE_TYPE;

typedef enum _STATION_TYPE			//厂站类别定义
{
	STATION_W=1,		//水电
	STATION_H,		//火电
	STATION_F,		//风电
	STATION_PH,		//光伏
	STATION_NU,		//核电
	STATION_T,		//变电站
	STATION_C,		//换流站
	STATION_V,		//虚拟站
	STATION_O		//其他
}STATION_TYPE;

typedef enum _GEN_TYPE			//发电机类型
{
	GEN_W=1,		//水电
	GEN_H,			//火电
	GEN_F,		//风电
	GEN_PH,		//光伏
	GEN_NU,		//核电
	GEN_O		//其他
}GEN_TYPE;

typedef enum _SWITCH_TYPE			//开关类型
{
	SWITCH_BREAK=1,		//断路器
	SWITCH_DISCON,		//刀闸
	SWITCH_GROUND		//地刀
}SWITCH_TYPE;

typedef enum _TRANSFORMER_TYPE			//变压器类型
{
	TRANSFORMER_NORMAL=1,	//正常
	TRANSFORMER_STATION		//站用变
}TRANSFORMER_TYPE;

typedef enum _CAPAC_TYPE			//容抗类型
{
	CAPAC_SERIES=1,		//串联
	CAPAC_PARALLEL		//并联
}CAPAC_TYPE;

//发电机类型
//const int GEN_TYPE_UNKOWN=0;
//const int GEN_TYPE_THERMAL=1;		//火电机组
//const int GEN_TYPE_HYDRO=2;		//水电机组

//设备子对象
const int SUBEQUIP_NAME=0;  //设备名字
const int TRANSF_SUB_HIG=1;	//变压器子对象高绕组
const int TRANSF_SUB_MID=2;	//变压器子对象中绕组
const int TRANSF_SUB_LOW=3;	//变压器子对象低绕组

//量测位置
const int MEAS_POS_FROMH=1;  //设备首端/变压器高
const int MEAS_POS_TOL=2;	//设备末端/双绕变低，三绕变压器中
const int MEAS_POS_LOW=3;	//三绕变压器低压侧

//变压器绕组类型
const int WINDING_TYPE_HIGH=1;  //高
const int WINDING_TYPE_MID=2;  //中
const int WINDING_TYPE_LOW=3;  //低


//EQUIPMENT_STATE			设备状态类型
const unsigned long EQUIPMENT_FIX_STATE=0xff;		//检修状态   0~7位为检修状态预留
const unsigned long EQUIPMENT_FIX_STATE_NOW=0x01;	//当前检修
const unsigned long EQUIPMENT_FIX_STATE_NEXT=0x02;	//次日检修

const unsigned long EQUIPMENT_RELAY_STATE=0xff00;		//保护状态   8~15位为继电保护状态预留
const unsigned long EQUIPMENT_RELAY_STATE_ON=0x0100;	//保护发生
const unsigned long EQUIPMENT_FAULT_STATE_ON=0x200;     //故障发生
const unsigned long EQUIPMENT_RELAYDEV_STATE_ON=0x0400;	//设备保护发生

const unsigned long EQUIPMENT_GROUP_STATE=0xff0000;		//接地状态   16~23位为接地状态预留
const unsigned long EQUIPMENT_GROUP_STATE_ON=0x010000;	//接地发生

const unsigned long EQUIPMENT_DEV_STATE=0xff000000;		//设备运行状态   16~23位为接地状态预留
const unsigned long EQUIPMENT_DEV_STATE_VUP=0x01000000;		//电压越上限
const unsigned long EQUIPMENT_DEV_STATE_VDOWN=0x02000000;	//电压越下限
const unsigned long EQUIPMENT_DEV_STATE_SUP=0x04000000;		//容量越限
const unsigned long EQUIPMENT_DEV_STATE_IUP=0x08000000;		//电流越限
const unsigned long EQUIPMENT_DEV_STATE_TUP=0x10000000;		//温度越限
const unsigned long EQUIPMENT_DEV_STATE_CHANGE=0x20000000;	//状态变化
//=============EQUIPMENT_STATE			设备状态类型


//电力对象类型
/*const int EQUIP_TYPE_UNK=0;			//未知设备
const int EQUIP_TYPE_PT=1;			//PT
const int EQUIP_TYPE_GEN=2;			//发电机
const int EQUIP_TYPE_SWITCH=3;		//开关
const int EQUIP_TYPE_LOAD=4;		//负荷
const int EQUIP_TYPE_SHUNT=5;		//并联无功设备
const int EQUIP_TYPE_REACT=6;		//电抗器
const int EQUIP_TYPE_BITRS=7;		//双绕组变
const int EQUIP_TYPE_TRITRS=8;		//三绕组变
const int EQUIP_TYPE_SVC=9;			//静止无功补偿器
const int EQUIP_TYPE_BUS=10;		//母线
const int EQUIP_TYPE_LINE=11;		//线路
const int EQUIP_TYPE_DCLINE=12;		//直流线路
const int EQUIP_TYPE_GROUP=13;		//接地
const int EQUIP_TYPE_AREA=14;		//区域
const int EQUIP_TYPE_SUB=15;		//厂站
const int EQUIP_TYPE_SYSTEM=16;		//系统
const int EQUIP_TYPE_TERM=17;		 //终端
const int EQUIP_TYPE_BAY=18;		 //间隔
const int EQUIP_TYPE_SystemTarget=19; //系统指标
const int EQUIP_TYPE_MEASUREMENT=20; //量测关系
const int EQUIP_TYPE_UnDevMEASUR=21; //非设备量测关系
const int EQUIP_TYPE_Relation=22;	 //断面
const int EQUIP_TYPE_DUMMY=23;		 //未设备*/

typedef enum _EQUIP_ALARM
{
	EQUIP_ALARM_NORMAL=0,     //正常
	EQUIP_ALARM_STOP,       //停运
	EQUIP_ALARM_G,          //挂牌
	EQUIP_ALARM_GND,        //接地
	EQUIP_ALARM_HOT,        //热备用
	EQUIP_ALARM_QUIT,       //退出运行
	EQUIP_ALARM_REPAIR,     //检修
	EQUIP_ALARM_CHARGE,     //充电
	EQUIP_ALARM_COLD,        //冷备用
	EQUIP_ALARM_UNKONW       //不足道
}EQUIP_ALARM;

typedef enum _EQUIP_TYPE
{
	EQUIP_TYPE_UNK=0,			//未知设备
	EQUIP_TYPE_PT,			//PT
	EQUIP_TYPE_GEN,			//发电机
	EQUIP_TYPE_SWITCH,		//开关
	EQUIP_TYPE_LOAD,		//负荷
	EQUIP_TYPE_SHUNT,		//并联无功设备
	EQUIP_TYPE_REACT,		//电抗器
	EQUIP_TYPE_BITRS,		//双绕组变
	EQUIP_TYPE_TRITRS,		//三绕组变
	EQUIP_TYPE_SVC,			//静止无功补偿器
	EQUIP_TYPE_BUS,		//母线
	EQUIP_TYPE_LINE,		//线路
	EQUIP_TYPE_DCLINE,		//直流线路
	EQUIP_TYPE_GROUP,		//接地
	EQUIP_TYPE_AREA,		//区域
	EQUIP_TYPE_SUB,		//厂站
	EQUIP_TYPE_SYSTEM,		//系统
	EQUIP_TYPE_TERM,		 //终端
	EQUIP_TYPE_BAY,		 //间隔
	EQUIP_TYPE_SystemTarget, //系统指标
	EQUIP_TYPE_MEASUREMENT, //量测关系
	EQUIP_TYPE_UnDevMEASUR, //非设备量测关系
	EQUIP_TYPE_Relation,	 //断面
	EQUIP_TYPE_SubObject,	 //子对象表
	EQUIP_TYPE_GND,	 //接地到砸
	EQUIP_TYPE_DUMMY		 //未设备24
}EQUIP_TYPE;

const char tblname[EQUIP_TYPE_DUMMY][32]={"未知设备","PT","发电机","开关","负荷","电容","电抗",
				"2绕组变压器","3绕组变压器","静态无功补偿装置","母线","交流线路","直流线路",
				"接地","区域","厂站","系统","终端","间隔","系统指标","量测关系","非设备量测",
				"预定断面","子对象表"};

//设备量测类型和显示标识
enum GEN_MEASURE_TYPE
{
	GEN_MEASURE_TYPE_UN=0,	//占位	
	GEN_MEASURE_TYPE_P,	//有功
	GEN_MEASURE_TYPE_Q,	//无功
	GEN_MEASURE_TYPE_Ang,	//工角
	GEN_MEASURE_TYPE_AGC,	//AGC状态
	GEN_MEASURE_TYPE_ContrlSpeed,	//调速速率
	GEN_MEASURE_TYPE_DownSpeed,	//下爬坡速率
	GEN_MEASURE_TYPE_UpWhirl,	//上旋备用
	GEN_MEASURE_TYPE_DownWhirl,	//下旋备用
	GEN_MEASURE_TYPE_END	//终止	
};
enum BUS_MEASURE_TYPE
{
	BUS_MEASURE_TYPE_UN=0,	//占位	
	BUS_MEASURE_TYPE_V,	//电压实际值
	BUS_MEASURE_TYPE_PU,	//电压标幺值
	BUS_MEASURE_TYPE_AngF,	//角度或频率
	BUS_MEASURE_TYPE_END	//终止	
};
enum ACLine_MEASURE_TYPE
{
	ACLine_MEASURE_TYPE_UN=0,	//占位	
	ACLine_MEASURE_TYPE_Pf,	//首端有功
	ACLine_MEASURE_TYPE_Qf,	//首端无功
	ACLine_MEASURE_TYPE_Pt,	//末端有功
	ACLine_MEASURE_TYPE_Qt,	//末端无功
	ACLine_MEASURE_TYPE_I,	//电流
	ACLine_MEASURE_TYPE_Par,//当前负载率
	ACLine_MEASURE_TYPE_END	//终止	
};
enum DCLine_MEASURE_TYPE
{
	DCLine_MEASURE_TYPE_UN=0,	//占位	
	DCLine_MEASURE_TYPE_P,	//首端有功
	DCLine_MEASURE_TYPE_Q,	//首端无功
	DCLine_MEASURE_TYPE_I,	//电流
	DCLine_MEASURE_TYPE_Par,//当前负载率
	DCLine_MEASURE_TYPE_END	//终止	
};
enum Trans2_MEASURE_TYPE
{
	Trans2_MEASURE_TYPE_UN=0,	//占位	
	Trans2_MEASURE_TYPE_Par,//当前负载率
	Trans2_MEASURE_TYPE_Ph,	//高压有功
	Trans2_MEASURE_TYPE_Qh,	//高压无功
	Trans2_MEASURE_TYPE_Ih,	//高压电流
	Trans2_MEASURE_TYPE_Tap,//档位
	Trans2_MEASURE_TYPE_Pl,	//低压有功
	Trans2_MEASURE_TYPE_Ql,	//低压无功
	Trans2_MEASURE_TYPE_Il,	//低压电流
	Trans2_MEASURE_TYPE_T,	//油温
	Trans2_MEASURE_TYPE_END	//终止	
};
enum Trans3_MEASURE_TYPE
{
	Trans3_MEASURE_TYPE_UN=0,	//占位	
	Trans3_MEASURE_TYPE_Par,//当前负载率
	Trans3_MEASURE_TYPE_Ph,	//高压有功
	Trans3_MEASURE_TYPE_Qh,	//高压无功
	Trans3_MEASURE_TYPE_Ih,	//高压电流
	Trans3_MEASURE_TYPE_Taph,//高压档位
	Trans3_MEASURE_TYPE_Pm,	//中压有功
	Trans3_MEASURE_TYPE_Qm,	//中压无功
	Trans3_MEASURE_TYPE_Im,	//中压电流
	Trans3_MEASURE_TYPE_Tapm,//中压档位
	Trans3_MEASURE_TYPE_Pl,	//低压有功
	Trans3_MEASURE_TYPE_Ql,	//低压无功
	Trans3_MEASURE_TYPE_Il,	//低压电流
	Trans3_MEASURE_TYPE_T,	//油温
	Trans3_MEASURE_TYPE_END	//终止	
};
enum Load_MEASURE_TYPE
{
	Load_MEASURE_TYPE_UN=0,	//占位	
	Load_MEASURE_TYPE_P,	//有功
	Load_MEASURE_TYPE_Q,	//无功
	Load_MEASURE_TYPE_I,	//电流
	Load_MEASURE_TYPE_END	//终止	
};
enum Shunt_MEASURE_TYPE
{
	Shunt_MEASURE_TYPE_UN=0,	//占位	
	Shunt_MEASURE_TYPE_Q,	//无功
	Shunt_MEASURE_TYPE_I,	//电流
	Shunt_MEASURE_TYPE_END	//终止	
};
enum SVC_MEASURE_TYPE
{
	SVC_MEASURE_TYPE_UN=0,	//占位	
	SVC_MEASURE_TYPE_Q,	//无功
	SVC_MEASURE_TYPE_END	//终止	
};
enum SYS_MEASURE_TYPE
{
	SYS_MEASURE_TYPE_UN=0,	//占位	
	SYS_MEASURE_TYPE_GenP,	//发电总有功
	SYS_MEASURE_TYPE_GenQ,	//发电总无功
	SYS_MEASURE_TYPE_WhirlBack,	//旋转备份
	SYS_MEASURE_TYPE_TotalRun,	//总在线容量
	SYS_MEASURE_TYPE_LoadP,	//总有功负荷
	SYS_MEASURE_TYPE_LoadQ,	//总无功负荷
	SYS_MEASURE_TYPE_END	//终止	
};
enum Area_MEASURE_TYPE
{
	Area_MEASURE_TYPE_UN=0,	//占位	
	Area_MEASURE_TYPE_GenCapa,	//装机容量
	Area_MEASURE_TYPE_TransCapa,	//变电容量
	Area_MEASURE_TYPE_GenP,	//机组出力
	Area_MEASURE_TYPE_LoadP,	//总负荷
	Area_MEASURE_TYPE_UpWhirl,	//上旋备用
	Area_MEASURE_TYPE_DownWhirl,	//下旋备用
	Area_MEASURE_TYPE_END	//终止	
};
enum Station_MEASURE_TYPE
{
	Station_MEASURE_TYPE_UN=0,	//占位	
	Station_MEASURE_TYPE_LastPower,	//存煤水位
	Station_MEASURE_TYPE_LastPowerT,	//存煤水位运行时间
	Station_MEASURE_TYPE_END	//终止	
};
enum Section_MEASURE_TYPE
{
	Section_MEASURE_TYPE_UN=0,	//占位	
	Section_MEASURE_TYPE_CurVal,	//当前值
	Section_MEASURE_TYPE_CurPar,	//当前负载
	Section_MEASURE_TYPE_Max,	//最大值
	Section_MEASURE_TYPE_Min,	//最小值
	Section_MEASURE_TYPE_END	//终止	
};
enum UnEquip_MEASURE_TYPE
{
	UnEquip_MEASURE_TYPE_UN=0,	//占位	
	UnEquip_MEASURE_TYPE_Value,	//当前值
	UnEquip_MEASURE_TYPE_END	//终止	
};

//量测类型
enum MEASURE_TYPE
{
	MEASURE_TYPE_UN=0,
	MEASURE_TYPE_V=1,		//电压  1
	MEASURE_TYPE_P=2,		//有功  1
	MEASURE_TYPE_Q=3,		//无功  1
	MEASURE_TYPE_S=4,		//视在功率
	MEASURE_TYPE_I=5,		//电流  1
	MEASURE_TYPE_Pf=6,		//功率因数  1
	MEASURE_TYPE_T=7,		//温度
	MEASURE_TYPE_Pos=8,		//档位
	MEASURE_TYPE_f=9,		//频率
	MEASURE_TYPE_Ang=10,	//相角
	MEASURE_TYPE_YX=11,		//遥信
	MEASURE_TYPE_Va=12,		//a相电压
	MEASURE_TYPE_Vb=13,		//b相电压
	MEASURE_TYPE_Vc=14,		//c相电压
	MEASURE_TYPE_Vab=15,		//ab线电压
	MEASURE_TYPE_Vbc=16,		//bc线电压
	MEASURE_TYPE_Vca=17,		//ca线电压
	MEASURE_TYPE_Ia=18,		//a相电流
	MEASURE_TYPE_Ib=19,		//b相电流
	MEASURE_TYPE_Ic=20,		//c相电流
	MEASURE_TYPE_Rl=21,		//保护信号
	MEASURE_TYPE_ETS=22,	//事故总信号
	MEASURE_TYPE_WINDDIR=23,	//风向
	MEASURE_TYPE_WINDDEL=24,	//风速
	MEASURE_TYPE_FIXVALUE=25,	//定值
	MEASURE_TYPE_COUNT=26,	//计算
	MEASURE_TYPE_UNSORT=27	//未分类
};

#endif // !defined(AFX_PUBLICPW_H__INCLUDED_)
