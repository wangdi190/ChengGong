#if !defined(AFX_PUBLICPW_H__INCLUDED_)
#define AFX_PUBLICPW_H__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//变电站类型
const int STATION_W=1;		//水电
const int STATION_H=2;		//火电
const int STATION_T=3;		//变电站
const int STATION_C=4;		//换流站
const int STATION_O=5;		//其他

//发电机类型
const int GEN_TYPE_UNKOWN=0;
const int GEN_TYPE_THERMAL=1;		//火电机组
const int GEN_TYPE_HYDRO=2;		//水电机组

//变压器子对象
const int SUBEQUIP_NAME=0;
const int TRANSF_SUB_HIG=1;	//变压器子对象高绕组
const int TRANSF_SUB_MID=2;	//变压器子对象中绕组
const int TRANSF_SUB_LOW=3;	//变压器子对象低绕组

/*
//电力对象类型
const int EQUIP_TYPE_UNK=0;//未知设备
const int EQUIP_TYPE_GEN=1;	//发电机
const int EQUIP_TYPE_BUS=2;	//母线
const int EQUIP_TYPE_LINE=3;	//线路
const int EQUIP_TYPE_BITRS=4;	//双绕组变
const int EQUIP_TYPE_TRITRS=5;//三绕组变
const int EQUIP_TYPE_LOAD=6;	//负荷
const int EQUIP_TYPE_SHUNT=7;	//并联无功设备
const int EQUIP_TYPE_SWITCH=8;//开关
const int EQUIP_TYPE_DCLINE=9;//直流线路
const int EQUIP_TYPE_REACT=10;//电抗器
const int EQUIP_TYPE_SVC=11; //静止无功补偿器
const int EQUIP_TYPE_MEASUREMENT=12; //量测关系
const int EQUIP_TYPE_SUB=20; //厂站
const int EQUIP_TYPE_TERM=21; //终端
const int EQUIP_TYPE_BAY=22; //间隔
const int EQUIP_TYPE_AREA=23; //区域
*/

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
	EQUIP_ALARM_UNKONW       //未知
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
	EQUIP_TYPE_GND,			//接地刀闸
	EQUIP_TYPE_DUMMY		 //未设备24
}EQUIP_TYPE;

const char tblname[EQUIP_TYPE_DUMMY][32]={"未知设备","PT","发电机","开关","负荷","电容","电抗",
				"2绕组变压器","3绕组变压器","静态无功补偿装置","母线","交流线路","直流线路",
				"接地","区域","厂站","系统","终端","间隔","系统指标","量测关系","非设备量测",
				"预定断面","子对象表","接地刀闸"};

//EQUIPMENT_STATE			设备状态类型
const unsigned long EQUIPMENT_FIX_STATE=0xff;		//检修状态   0~7位为检修状态预留
const unsigned long EQUIPMENT_FIX_STATE_NOW=0x01;	//当前检修
const unsigned long EQUIPMENT_FIX_STATE_NEXT=0x02;	//次日检修
const unsigned long EQUIPMENT_BACKUP_STATE_COLD=0x11;	//冷备			冷备和热备时线路不带电，sta ele都为0， 充电是线路带电sta=0, ele=1
const unsigned long EQUIPMENT_BACKUP_STATE_CHAGING=0x12;	//充电
const unsigned long EQUIPMENT_BACKUP_STATE_HOT=0x13;	//热备
const unsigned long EQUIPMENT_BACKUP_STATE_RUN=0x14;	//运行

const unsigned long EQUIPMENT_RELAY_STATE=0xff00;		//保护状态   8~15位为继电保护状态预留
const unsigned long EQUIPMENT_RELAY_STATE_ON=0x0100;	//保护发生
const unsigned long EQUIPMENT_FAULT_STATE_ON=0x0200;	//故障发生
const unsigned long EQUIPMENT_RELAYDEV_STATE_ON=0x0400;	//二次设备保护发生

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



//量测类型
enum MEASURE_TYPE
{
	MEASURE_TYPE_UN=0,		
	MEASURE_TYPE_V=1,		//电压
	MEASURE_TYPE_P=2,		//有功
	MEASURE_TYPE_Q=3,		//无功
	MEASURE_TYPE_S=4,		//视在功率
	MEASURE_TYPE_I=5,		//电流
	MEASURE_TYPE_Pf=6,		//功率因数
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
	MEASURE_TYPE_UNSORT=23	//未分类
};

#endif // !defined(AFX_PUBLICPW_H__INCLUDED_)
