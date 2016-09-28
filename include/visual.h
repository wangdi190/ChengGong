#if !defined(_DB_STRUCT_H_)
#define _DB_STRUCT_H_
/************************************************/
//本头文件由“数据库设计软件”自动生成
//2010-11-25
//星海高科技产业股份有限公司
/************************************************/
//掩码预定义值
//=================可视化电力系统库===============
//PT表
typedef struct visualpw_PT
{
	DWORD  NU;							//PT编号
	char  Name[32];						//PT名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	short  status;						//综合状态
}visualpw_PT,*LPvisualpw_PT;
//发电机
typedef struct visualpw_Gen
{
	DWORD  NU;							//发电机号
	char  Name[32];						//发电机名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  MaxP;						//有功上限
	float  Par;							//有功出力百分比告警限
	float  CurPar;						//当前使用的告警率
	float  Pchk;						//检修功率
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	float  P;							//有功出力
	float  Q;							//无功出力
	float  V;							//机端电压
	float  angle;						//角度
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	float  Qmax;						//最大可用无功
	float  Qmaxi;						//最大进相无功
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	BYTE  Type;							//类型
	float  VL;							//电压等级
	short  status;						//综合状态
}visualpw_Gen,*LPvisualpw_Gen;
//开关刀闸
typedef struct visualpw_Switch
{
	DWORD  NU;							//开关编号
	char  Name[32];						//开关名字
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//开关状态
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node1;						//节点1
	DWORD  Node2;						//节点2
	float  VL;							//电压等级
	short  status;						//综合状态
}visualpw_Switch,*LPvisualpw_Switch;
//负荷
typedef struct visualpw_Load
{
	DWORD  NU;							//负荷编号
	char  Name[32];						//负荷名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  MaxP;						//有功上限
	float  MinP;						//有功下限
	float  P;							//有功负荷
	float  Q;							//无功负荷
	float  I;							//电流
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	float  VL;							//电压等级
	short  status;						//综合状态
}visualpw_Load,*LPvisualpw_Load;
//电容
typedef struct visualpw_Shunt
{
	DWORD  NU;							//电容设备编号
	char  Name[32];						//电容设备名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Q;							//投入无功
	float  I;							//电流
	float  Qmax;						//最大无功输出
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	float  Qchk;						//检修容量
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	float  VL;							//电压等级
	short  status;						//综合状态
}visualpw_Shunt,*LPvisualpw_Shunt;
//电抗
typedef struct visualpw_Sreact
{
	DWORD  NU;							//电抗器变号
	char  Name[32];						//电抗器名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Zx;							//投入电抗
	float  I;							//电流
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node1;						//节点1
	DWORD  Node2;						//节点2
	float  VL;							//电压等级
	short  status;						//综合状态
}visualpw_Sreact,*LPvisualpw_Sreact;
//2绕组变压器
typedef struct visualpw_Tfm1
{
	DWORD  NU;							//2绕变编号
	char  Name[32];						//2绕变名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	WORD  Tallow;						//过载允许时间(分)
	WORD  Tover;						//已连续过载时间(分)
	float  tap;							//变压器分接头
	float  Pmax;						//变压器最大有功(容量)
	float  Par;							//变压器负载率警告限
	float  CurPar;						//当前使用的告警率
	float  P;							//高压侧有功
	float  Q;							//高压侧无功
	float  I;							//高压侧电流
	float  P2;							//低压侧有功
	float  Q2;							//低压侧无功
	float  I2;							//低压侧电流
	float  Tcur;						//当前温度
	float  Tmax;						//最高温度
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  NodeH;						//高压节点
	DWORD  NodeL;						//低压节点
	float  VL;							//电压等级
	short  status;						//综合状态
}visualpw_Tfm1,*LPvisualpw_Tfm1;
//3绕组变压器
typedef struct visualpw_Tfm2
{
	DWORD  NU;							//3绕变编号
	char  Name[32];						//3绕变名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	WORD  Tallow;						//过载允许时间(分)
	WORD  Tover;						//已连续过载时间(分)
	float  TapH;						//高端分接头位置
	float  TapM;						//中端分接头位置
	float  TapL;						//低端分接头位置
	float  Pmax;						//变压器最大有功(容量)
	float  Par;							//变压器负载率警告限
	float  CurPar;						//当前使用的告警率
	float  P;							//高压侧有功
	float  Q;							//高压侧无功
	float  I;							//高压侧电流
	float  P2;							//中压侧有功
	float  Q2;							//中压侧无功
	float  I2;							//中压侧电流
	float  P3;							//低压侧有功
	float  Q3;							//低压侧无功
	float  I3;							//低压侧电流
	float  Tcur;						//当前温度
	float  Tmax;						//最高温度
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  NodeH;						//高压节点
	DWORD  NodeM;						//中压节点
	DWORD  NodeL;						//低压节点
	float  VL;							//电压等级
	short  status;						//综合状态
}visualpw_Tfm2,*LPvisualpw_Tfm2;
//静态无功补偿
typedef struct visualpw_SVC
{
	DWORD  NU;							//SVC编号
	char  Name[32];						//SVC名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Qmax;						//最大无功输出
	float  Qmin;						//最小无功输出
	float  Q;							//无功输出
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	short  status;						//综合状态
}visualpw_SVC,*LPvisualpw_SVC;
//母线
typedef struct visualpw_Bus
{
	DWORD  NU;							//母线编号
	char  Name[32];						//母线名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  MaxV;						//电压上限
	float  MinV;						//电压下限
	float  HiLimit;						//电压告警上限
	float  LoLimit;						//电压告警下限
	float  PreVhi;						//预警使用的上限
	float  PreVlo;						//预警使用的下限
	float  Vl;							//电压等级
	float  V;							//节点电压(pu)
	float  Vb;							//电压实际值
	float  DayMax;						//日最大值
	float  DayMin;						//日最小值
	float  deg;							//相角
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  AlarmHiLo;					//越上下限0，1，2
	BYTE  AlarmBand;					//越5%限0，1
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	DWORD  cNode;						//合并节点
	short  status;						//综合状态
}visualpw_Bus,*LPvisualpw_Bus;
//交流线
typedef struct visualpw_Line
{
	DWORD  NU;							//交流线编号
	char  Name[32];						//交流线名称
	DWORD  Stationf;					//首端站
	DWORD  Stationt;					//末端站
	int  Zonef;							//起始区域域号
	int  Zonet;							//终点区域域号
	float  Imax;						//电流最大值
	float  MaxP;						//有功上限
	float  Par;							//输电线负载率告警限
	float  CurPar;						//当前使用的告警率
	float  VL;							//电压等级
	float  Pf;							//始端有功
	float  Qf;							//始端无功
	float  Pt;							//末端有功
	float  Qt;							//末端无功
	float  I;							//电流值
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  NodeF;						//首节点
	DWORD  NodeT;						//末节点
	short  status;						//综合状态
}visualpw_Line,*LPvisualpw_Line;
//直流线
typedef struct visualpw_DCLine
{
	DWORD  NU;							//直流线编号
	char  Name[32];						//直流线名称
	DWORD  Stationf;					//首端站
	DWORD  Stationt;					//末端站
	int  Zonef;							//起始区域域号
	int  Zonet;							//终点区域域号
	float  Imax;						//电流最大值
	float  Maxp;						//有功上限
	float  Par;							//输电线负载率告警限
	float  CurPar;						//当前使用的告警率
	float  VL;							//电压等级
	float  Pf;							//始端有功
	float  Qf;							//始端无功
	float  Pt;							//末端有功
	float  Qt;							//末端无功
	float  I;							//电流值
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  NodeF;						//首节点
	DWORD  NodeT;						//末节点
	short  status;						//综合状态
}visualpw_DCLine,*LPvisualpw_DCLine;
//逆变器、变流器
typedef struct visualpw_CVT
{
	DWORD  NU;							//设备编号
	char  Name[32];						//设备名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	short  status;						//综合状态
}visualpw_CVT,*LPvisualpw_CVT;
//接地
typedef struct visualpw_GND
{
	DWORD  NU;							//接地编号
	char  Name[32];						//接地名称
	DWORD  Station;						//所属站号
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
}visualpw_GND,*LPvisualpw_GND;
//区域
typedef struct visualpw_Zone
{
	DWORD  NU;							//区域编号
	char  Name[32];						//区域名称
	float  Pgen;						//发电有功
	float  Qgen;						//无功发电
	float  GenMax;						//发电机容量
	float  Pld;							//有功负荷
	float  Qld;							//无功负荷
	float  LdMax;						//负荷最大值
	float  ZoneLP;						//区域有功负荷
	float  ZoneLQ;						//区域无功负荷
	short  Sub50;						//500kV变电站数
	short  Sub22;						//220kV变电站数
	float  TransMW;						//变电站容量
}visualpw_Zone,*LPvisualpw_Zone;
//站
typedef struct visualpw_Station
{
	DWORD  NU;							//站号
	char  Name[32];						//站名
	DWORD  zoneNU;						//所属区域
	float  VL;							//电压等级
	int  Type;							//厂站类型
	char  ID[24];						//变电站标识
	short  status;						//综合状态
}visualpw_Station,*LPvisualpw_Station;
//按节点电压排序
typedef struct visualpw_VotOutage
{
	int  NU;							//设备编号
	char  type;							//设备类型
	float  Defl;						//风险指标
	BYTE  Group;						//分组类型
}visualpw_VotOutage,*LPvisualpw_VotOutage;
//按支路排序
typedef struct visualpw_LineOutage
{
	int  NU;							//设备编号
	char  type;							//类型
	float  Defl;						//风险指标
	BYTE  Group;						//分组类型
}visualpw_LineOutage,*LPvisualpw_LineOutage;
//节点电压和支路合成
typedef struct visualpw_AllOutage
{
	int  NU;							//设备编号
	char  type;							//类型
	float  Defl;						//风险指标
	BYTE  Group;						//分组类型
}visualpw_AllOutage,*LPvisualpw_AllOutage;
//系统指标
typedef struct visualpw_SysGD
{
	DWORD  ID;							//指标标识ID
	char  Name[24];						//指标名称
	float  zb;							//当前指标
	float  Vmax;						//量程最大值
	float  Vmin;						//量程最小值
	float  Vmax1;						//第一段最大值
	float  Vmin1;						//第一段最小值
	float  Vmax2;						//第二段最大值
	float  Vmin2;						//第二段最小值
}visualpw_SysGD,*LPvisualpw_SysGD;
//系统告警
typedef struct visualpw_SysAlarm
{
	WORD  Alarm;						//告警状态0,1
	WORD  num;							//发生告警的设备个数
	char  picname[32];					//推出画面名称
	WORD  picno;						//推出画面序号
}visualpw_SysAlarm,*LPvisualpw_SysAlarm;
//系统告警
typedef struct visualpw_Ace
{
	DWORD  ID;							//标识ID
	float  CurVal;						//当前值
	CTime  datatime;					//数据时间
	BYTE  alarm;						//告警
	BYTE  ack;							//确认
}visualpw_Ace,*LPvisualpw_Ace;
//短路电流计算结果
typedef struct visualpw_ShortCC
{
	DWORD  SwtNU;						//开关编号ID
	BYTE  GType;						//故障类型
	DWORD  LineNU;						//线路编号
	BYTE  LineType;						//线路类型
	CTime  DTime;						//计算时间
	float  TrPos;						//故障位置
	float  Imax;						//最大电流
	float  Isc;							//短路电流
	float  Usc;							//计算后电压
}visualpw_ShortCC,*LPvisualpw_ShortCC;
//用于仪表显示
typedef struct visualpw_Meter
{
	int  ID;							//唯一的ID号
	char  Name[32];						//名称
	float  Value;						//当前值
	float  Vmax;						//最大值
	float  Vmin;						//最小值
	float  Vmax1;						//第一段最大值
	float  Vmin1;						//第一段最小值
	float  Vmax2;						//第二段最大值
	float  Vmin2;						//第二段最小值
	BYTE  AreaNo;						//分区序号
	BYTE  FieldNo;						//字段序号
}visualpw_Meter,*LPvisualpw_Meter;
//分区表
typedef struct visualpw_Area
{
	DWORD  NU;							//分区号
	char  Name[32];						//分区名称
	DWORD  AColor;						//区域颜色
	float  Security;					//安全指标
	float  LDFactor;					//容载比
	float  LDFactorT;					//主变容载比
	float  LDFactorL;					//线路容载比
	float  LDFactorG;					//发电容载比
	float  LDFactorS;					//无功容载比
	float  Energy;						//电量平衡
	float  VolRate;						//电压合格率
	float  LDRate;						//负荷水平
	float  OverLoading;					//重载率
	float  OverLoadingT;				//主变重载率
	float  OverLoadingL;				//线路重载率
}visualpw_Area,*LPvisualpw_Area;
//电压无功控制表
typedef struct visualpw_AVC
{
	DWORD  NU;							//变压器号
	char  Name[64];						//设备名称
	float  fVol;						//监测电压值
	float  fVar;						//监测无功值
	BYTE  POS;							//九区图位置
	BYTE  byTransType;					//变压器类型
	char  Property[256];				//属性
	char  PreValues[96];				//最近的变化值
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
}visualpw_AVC,*LPvisualpw_AVC;
//发电机PQV参数表
typedef struct visualpw_PQV
{
	DWORD  GenNU;						//发电机编号
	char  Name[64];						//设备名称
	DWORD  BusNU;						//所属母线号
	BYTE  Gentype;						//电机隐凸极属性
	float  FacS;						//出厂额定容量
	float  FacU;						//出厂额定电压
	float  FacF;						//出厂额定频率
	float  xd;							//D轴电抗
	float  xq;							//Q轴电抗
	float  imax;						//最大励磁电流
	float  eqmax;						//最大磁通
	char  Property[256];				//属性
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
}visualpw_PQV,*LPvisualpw_PQV;
//负载统计表
typedef struct visualpw_ldstate
{
	DWORD  NU;							//编号
	BYTE  type;							//类型
	float  LDmax;						//日最大负载
	CTime  LDmaxT;						//最大负载出现时间
	DWORD  LDoverT;						//日负载过载时长
}visualpw_ldstate,*LPvisualpw_ldstate;
//高压联网运行数据
typedef struct visualpw_Hvcondata
{
	DWORD  ID;							//ID值
	char  Name1[40];					//名字
	char  Name2[40];					//名字
	float  Vlimit;						//限值
	float  Curval;						//当前值
	char  sta;							//运行状态
	CTime  datetm;						//日期时间
	char  Alarm;						//告警
	char  Ack;							//确认
}visualpw_Hvcondata,*LPvisualpw_Hvcondata;
//变压器动态监视
typedef struct visualpw_DynMonitor
{
	DWORD  NU;							//序号
	char  Name[32];						//名称
	BYTE  Winding;						//绕组类型
	BYTE  Mode;							//工作模式
	float  Normal1;						//正常限值1
	int  NorTime1;						//正常限值1时长
	float  Normal2;						//正常限值2
	int  NorTime2;						//正常限值2时长
	float  Normal3;						//正常限值3
	int  NorTime3;						//正常限值3时长
	float  Contingency1;				//事故限值1
	int  CtgTime1;						//事故限值1时长
	float  Contingency2;				//事故限值2
	int  CtgTime2;						//事故限值2时长
	float  Contingency3;				//事故限值3
	int  CtgTime3;						//事故限值3时长
	char  Buffer[240];					//缓存数据
}visualpw_DynMonitor,*LPvisualpw_DynMonitor;
//事故影响
typedef struct visualpw_CtgEffect
{
	DWORD  CtgNU;						//事故设备号
	char  CtgName[32];					//事故设备名
	int  CtgType;						//事故设备类型
	float  fSecurity;					//风险指标
	DWORD  EftNU;						//异态设备号
	char  EftName[32];					//异态设备名
	int  EftType;						//异态设备类型
	float  EftVal;						//异态程度
}visualpw_CtgEffect,*LPvisualpw_CtgEffect;
//全网性数据
typedef struct visualpw_Grid
{
	float  GenMax;						//全网发电总容量
	float  GenP;						//全网发电有功
	float  GenQ;						//全网发电无功
	float  StopP;						//全网停机总容量
	float  UpRes;						//全网上旋转备用
	float  DownRes;						//全网下旋转备用
	float  LoadMax;						//全网设计总负荷
	float  LoadP;						//全网用电负荷
}visualpw_Grid,*LPvisualpw_Grid;
//变压器绕组
typedef struct visualpw_Winding
{
	DWORD  NU;							//绕组编号
	char  ID[24];						//绕组标识
	char  TID[24];						//变压器标识
	float  ratedKV;						//额定电压
	float  ratedMVA;					//额定容量
	float  fShortLoss;					//短路损耗
	float  fShortVol;					//短路电压
	float  fNoLoadLoss;					//空载损耗
	float  fR;							//电阻
	float  fX;							//电抗
	float  fB;							//电纳
	float  fR0;							//零电阻
	float  fX0;							//零电抗
	BYTE  Type;							//绕组类型
	BYTE  Tmax;							//最大档位
	BYTE  Tmin;							//最小档位
	BYTE  Tnor;							//正常档位
	float  step;						//档位步长
}visualpw_Winding,*LPvisualpw_Winding;
//导线表
typedef struct visualpw_Conductor
{
	DWORD  NU;							//编号
	BYTE  Type;							//类型
	char  LID[24];						//线路标识
	float  fR;							//电阻
	float  fX;							//电抗
	float  fB;							//电纳
	float  fG;							//电导
	float  fR0;							//零序电阻
	float  fX0;							//零序电抗
	float  fB0;							//零序电纳
	float  fG0;							//零序电导
}visualpw_Conductor,*LPvisualpw_Conductor;
//=================公共库===============
//用户表
typedef struct common_user
{
	WORD  id;							//用户ID
	char  Name[15];						//用户名
	char  password[16];					//用户密码
	char  type;							//用户类型
	DWORD  limit;						//权限(32位)
	char  exp[28];						//注解
}common_user,*LPcommon_user;
//电压颜色
typedef struct common_Color
{
	char  VLName[16];					//电压名称
	BYTE  R;							//红色分量
	BYTE  G;							//绿色分量
	BYTE  B;							//兰色分量
}common_Color,*LPcommon_Color;
//实时负荷预测8点
typedef struct common_FLoad
{
	float  FValue;						//负荷预测值
	float  RValue;						//负荷实际值
	BYTE  hour;							//整点小时数
}common_FLoad,*LPcommon_FLoad;
//运行方式
typedef struct common_RunType
{
	DWORD  Nu;							//编号
	char  Name[24];						//名
	BYTE  State;						//状态
}common_RunType,*LPcommon_RunType;
//母线关联值
typedef struct common_BusV
{
	DWORD  Nu;							//编号
	char  Name[24];						//设备名
	float  HGD_MaxV;					//丰大白天电压上限
	float  HGD_MinV;					//丰大白天电压下限
	float  HGW_MaxV;					//丰大晚上电压上限
	float  HGW_MinV;					//丰大晚上电压下限
	float  HSD_MaxV;					//丰小白天电压上限
	float  HSD_MinV;					//丰小白天电压下限
	float  HSW_MaxV;					//丰小晚上电压上限
	float  HSW_MinV;					//丰小晚上电压下限
	float  LGD_MaxV;					//枯大白天电压上限
	float  LGD_MinV;					//枯大白天电压下限
	float  LGW_MaxV;					//枯大晚上电压上限
	float  LGW_MinV;					//枯大晚上电压下限
	float  LSD_MaxV;					//枯小白天电压上限
	float  LSD_MinV;					//枯小白天电压下限
	float  LSW_MaxV;					//枯小晚上电压上限
	float  LSW_MinV;					//枯小晚上电压下限
	float  ESD_MaxV;					//特殊白天电压上限
	float  ESD_MinV;					//特殊白天电压下限
	float  ESW_MaxV;					//特殊晚上电压上限
	float  ESW_MinV;					//特殊晚上电压下限
}common_BusV,*LPcommon_BusV;
//转换关系表
typedef struct common_Relation
{
	int  NU;							//序号
	int  VNu;							//可视化中的设备ID
	char  VName[32];					//可视化中设备名字
	BYTE  DevType;						//设备类型
	BYTE  MeasType;						//量测类型
	char  MeasID[32];					//量测标识
	BYTE  MeasPos;						//量测位置
	DWORD  Station;						//所属站号
	float  SectVal;						//初始断面值
	float  SeVal;						//状态估计值
	float  EmVal;						//仿真计算值
	BYTE  quality;						//质量标志
	float  SndVal;						//发送值
	float  wStep;						//权重步长
}common_Relation,*LPcommon_Relation;
//预警配置
typedef struct common_PreLimit
{
	WORD  ID;							//ID号
	char  Name[24];						//名称
	float  Value;						//运用值
}common_PreLimit,*LPcommon_PreLimit;
//虚拟开关关连关系
typedef struct common_VSwitch
{
	DWORD  SwtNU;						//开关ID
	char  Name[32];						//开关名字
	DWORD  VSwtNU;						//所属虚拟开关NU
	DWORD  LineNU;						//所属线路
}common_VSwitch,*LPcommon_VSwitch;
//预定义断面潮流
typedef struct common_PreDefSF
{
	DWORD  ID;							//断面ID
	char  Name[45];						//断面名字
	float  curval;						//当前断面值
	float  Vmax;						//断面容量值
	float  Par;							//断面负载率告警限
	float  CurPar;						//当前使用的告警限
	BYTE  Nline;						//线路数
	char  DevID[256];					//断面ID,最大26条线路
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	float  Pcur;						//断面有功
	float  Qcur;						//断面无功
	char  msg[45];						//提示文本
}common_PreDefSF,*LPcommon_PreDefSF;
//灵敏度结果表
typedef struct common_Sen
{
	DWORD  NU;							//设备相关ID
	BYTE  type;							//设备类型
	float  senval;						//灵敏度值
}common_Sen,*LPcommon_Sen;
//应用参数
typedef struct common_AppParam
{
	DWORD  NU;							//序号
	char  Name[32];						//参数名
	float  Param;						//参数值
}common_AppParam,*LPcommon_AppParam;
//子对象表
typedef struct common_SubObject
{
	DWORD  NU;							//序号
	char  Name[32];						//名称
	char  ID[32];						//对象标识
	BYTE  Type;							//对象类型
	DWORD  Station;						//厂站
	DWORD  PNU;							//父设备号
	BYTE  PType;						//父设备类型
}common_SubObject,*LPcommon_SubObject;
//非设备量测
typedef struct common_UnEquMeas
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  max;							//最大值
	float  min;							//最小值
	float  val;							//值
	BYTE  type;							//量测类型
	char  ID[32];						//标识
	char  PID[32];						//父标识
}common_UnEquMeas,*LPcommon_UnEquMeas;
//=================仿真计算库===============
//发电机
typedef struct emluator_mGen
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  VL;							//电压等级
	float  rateP;						//额定容量
	float  rateV;						//额定电压
	float  IX;							//内部电抗
	DWORD  node;						//节点
	float  P;							//有功
	float  Q;							//无功
	float  I;							//电流
	float  V;							//机端电压
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
}emluator_mGen,*LPemluator_mGen;
//母线
typedef struct emluator_mBus
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  VL;							//电压等级
	DWORD  node;						//节点
	float  V;							//电压
	float  deg;							//相角
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
}emluator_mBus,*LPemluator_mBus;
//变压器
typedef struct emluator_mTfm
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	DWORD  MU;							//宿主变
	float  rateP;						//额定容量
	float  VLI;							//I电压等级
	float  VLJ;							//J电压等级
	DWORD  nodeI;						//节点I
	DWORD  nodeJ;						//节点J
	float  R;							//电阻
	float  X;							//电抗
	float  B;							//电纳
	float  R0;							//零电阻
	float  X0;							//零电抗
	float  T;							//当前变比
	float  TMX;							//最大变比
	float  TMN;							//最小变比
	float  step;						//步长
	float  Pi;							//I端有功
	float  Qi;							//I端无功
	float  Pj;							//J端有功
	float  Qj;							//J端无功
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
}emluator_mTfm,*LPemluator_mTfm;
//线路
typedef struct emluator_mLine
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  VL;							//电压等级
	float  rateP;						//额定容量
	DWORD  nodeI;						//I节点
	DWORD  nodeJ;						//J节点
	float  R;							//电阻
	float  X;							//电抗
	float  B;							//电纳
	float  R0;							//零序电阻
	float  X0;							//零序电抗
	float  B0;							//零序电纳
	float  Pi;							//I端有功
	float  Qi;							//I端无功
	float  Pj;							//J端有功
	float  Qj;							//J端无功
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  stationf;						//首端厂站
	int  stationt;						//末端厂站
}emluator_mLine,*LPemluator_mLine;
//负荷
typedef struct emluator_mLoad
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  VL;							//电压等级
	DWORD  node;						//节点
	float  Pmax;						//最大负荷
	float  P;							//有功
	float  Q;							//无功
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
}emluator_mLoad,*LPemluator_mLoad;
//并补
typedef struct emluator_mShunt
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  rateQ;						//额定容量
	float  rateV;						//额定电压
	float  VL;							//电压等级
	DWORD  node;						//节点
	float  Q;							//无功
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
}emluator_mShunt,*LPemluator_mShunt;
//串补
typedef struct emluator_mSerial
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  rateQ;						//额定容量
	float  rateV;						//额定电压
	float  VL;							//电压等级
	float  Zk;							//阻抗
	DWORD  nodeI;						//节点I
	DWORD  nodeJ;						//节点J
	float  Q;							//无功
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
}emluator_mSerial,*LPemluator_mSerial;
//直流线
typedef struct emluator_mDLine
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  rateP;						//额定容量
	float  VL;							//电压等级
	DWORD  nodeI;						//节点I
	DWORD  nodeJ;						//节点J
	float  R;							//电阻
	float  Xi;							//I端电抗
	float  Xj;							//J端电抗
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  stationf;						//首端厂站
	int  stationt;						//末端厂站
}emluator_mDLine,*LPemluator_mDLine;
//仿真结果统计项
typedef struct emluator_mStat
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  statval;						//统计值
}emluator_mStat,*LPemluator_mStat;
//=================评估库===============
//项目表
typedef struct estimator_project
{
	DWORD  NU;							//项目编号
	char  Name[32];						//项目名称
	char  AVC[32];						//被评估AVC
	BYTE  Type;							//类型
	char  projectpath[128];				//项目路径
}estimator_project,*LPestimator_project;
//评估
typedef struct estimator_estimate
{
	DWORD  NU;							//编号
	char  description[32];				//评估描述
	DWORD  project;						//项所属项目
	char  report[32];					//报告评估
}estimator_estimate,*LPestimator_estimate;
//评估案例
typedef struct estimator_estcase
{
	DWORD  NU;							//案例编号
	char  Name[32];						//案例名称
	DWORD  project;						//项所属项目
	short  casetype;					//案例类型
	BYTE  onlie;						//在线案例
	char  descr[256];					//案例描述
}estimator_estcase,*LPestimator_estcase;
//断面定义
typedef struct estimator_sectdef
{
	DWORD  NU;							//断面编号
	char  Name[32];						//断面名称
	char  Path[32];						//断面路径
	DWORD  estcase;						//所属评案例
	CTime  dtime;						//断面时间
	char  descr[256];					//案例描述
}estimator_sectdef,*LPestimator_sectdef;
//发电机
typedef struct estimator_eGen
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  VL;							//电压等级
	float  rateP;						//额定容量
	float  rateV;						//额定电压
	float  IX;							//内部电抗
	DWORD  node;						//节点
	float  P;							//有功
	float  Q;							//无功
	float  I;							//电流
	float  V;							//机端电压
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
	int  island;						//电力岛
}estimator_eGen,*LPestimator_eGen;
//母线
typedef struct estimator_eBus
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  VL;							//电压等级
	float  V;							//电压
	float  deg;							//相角
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
	int  island;						//电力岛
}estimator_eBus,*LPestimator_eBus;
//变压器
typedef struct estimator_eTfm
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	DWORD  MU;							//宿主变
	float  rateP;						//额定容量
	float  VLI;							//I电压等级
	float  VLJ;							//J电压等级
	DWORD  nodeI;						//节点I
	DWORD  nodeJ;						//节点J
	float  R;							//电阻
	float  X;							//电抗
	float  B;							//电纳
	float  R0;							//零电阻
	float  X0;							//零电抗
	float  T;							//当前变比
	float  TMX;							//最大变比
	float  TMN;							//最小变比
	float  step;						//步长
	float  Pi;							//I端有功
	float  Qi;							//I端无功
	float  Pj;							//J端有功
	float  Qj;							//J端无功
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
	int  island;						//电力岛
}estimator_eTfm,*LPestimator_eTfm;
//线路
typedef struct estimator_eLine
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  VL;							//电压等级
	float  rateP;						//额定容量
	DWORD  nodeI;						//I节点
	DWORD  nodeJ;						//J节点
	float  R;							//电阻
	float  X;							//电抗
	float  B;							//电纳
	float  R0;							//零序电阻
	float  X0;							//零序电抗
	float  B0;							//零序电纳
	float  Pi;							//I端有功
	float  Qi;							//I端无功
	float  Pj;							//J端有功
	float  Qj;							//J端无功
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  stationf;						//首端站
	int  stationt;						//末端站
	int  island;						//电力岛
}estimator_eLine,*LPestimator_eLine;
//负荷
typedef struct estimator_eLoad
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  VL;							//电压等级
	DWORD  node;						//节点
	float  Pmax;						//最大负荷
	float  P;							//有功
	float  Q;							//无功
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
	int  island;						//电力岛
}estimator_eLoad,*LPestimator_eLoad;
//并补
typedef struct estimator_eShunt
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  rateQ;						//额定容量
	float  rateV;						//额定电压
	float  VL;							//电压等级
	DWORD  node;						//节点
	float  Q;							//无功
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
	int  island;						//电力岛
}estimator_eShunt,*LPestimator_eShunt;
//串补
typedef struct estimator_eSerial
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  rateQ;						//额定容量
	float  rateV;						//额定电压
	float  VL;							//电压等级
	float  Zk;							//阻抗
	DWORD  nodeI;						//节点I
	DWORD  nodeJ;						//节点J
	float  Q;							//无功
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
	int  island;						//电力岛
}estimator_eSerial,*LPestimator_eSerial;
//直流线
typedef struct estimator_eDLine
{
	DWORD  NU;							//编号
	char  Name[32];						//名称
	float  rateP;						//额定容量
	float  VL;							//电压等级
	DWORD  nodeI;						//节点I
	DWORD  nodeJ;						//节点J
	float  R;							//电阻
	float  Xi;							//I端电抗
	float  Xj;							//J端电抗
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  stationf;						//首端厂站
	int  stationt;						//末端厂站
	int  island;						//电力岛
}estimator_eDLine,*LPestimator_eDLine;
//案例量测
typedef struct estimator_casemeas
{
	DWORD  NU;							//编号
	DWORD  estcase;						//所属案例
	DWORD  casedev;						//案例设备
	DWORD  casesec;						//所属断面
	BYTE  mkattr;						//生成属性
	char  MeasID[32];					//量测ID
	float  val;							//人工值
	float  Vmx;							//最大值
	float  Vmn;							//最小值
	BYTE  quality;						//质量标志
}estimator_casemeas,*LPestimator_casemeas;
//案例设备
typedef struct estimator_caseequ
{
	DWORD  NU;							//编号
	DWORD  estcase;						//所属案例
	char  random;						//随机设备
	BYTE  dtype;						//设备类型
	DWORD  dNU;							//设备编号
	short  action;						//设备动作
	short  targe;						//动作目标
}estimator_caseequ,*LPestimator_caseequ;
//案例模版
typedef struct estimator_CASETEMP
{
	DWORD  NU;							//编号
	char  Name[32];						//内容名称
	short  casetype;					//案例类型
	int  estkeep;						//评估保持时间
	char  dsite[32];					//数据位置
	short  scircle;						//断面发送周期
	int  target;						//评价指标
}estimator_CASETEMP,*LPestimator_CASETEMP;
//AVC控制指令表
typedef struct estimator_avcctrl
{
	DWORD  NU;							//时间序号
	DWORD  dev;							//设备序号
	BYTE  dtype;						//设备类型
	BYTE  ctrl;							//控制指令
	BYTE  project;						//项所属项目
	DWORD  estimate;					//所属评估
	DWORD  estcase;						//所属案例
	int  status;						//指令状态
}estimator_avcctrl,*LPestimator_avcctrl;
//评估结果集
typedef struct estimator_estresult
{
	DWORD  NU;							//序号
	DWORD  project;						//项所属项目
	DWORD  estimate;					//所属评估
	DWORD  estcase;						//所属案例
	char  Name[32];						//案例名称
	DWORD  casetemp;					//案例模板
	DWORD  secttime;					//断面发送时间
	DWORD  esttime;						//评估时间
	BYTE  quality;						//案例质量
	float  ctrl;						//控制评价
	float  loss;						//损耗评价
	float  voltage;						//电压评价
	float  action;						//动作数评价
	float  reserve;						//无功备用评价
	float  stability;					//稳定性评价
	float  lock;						//闭锁评价
	float  load;						//负载评价
	float  speed;						//速度评价
	char  appendix[32];					//附属文件
}estimator_estresult,*LPestimator_estresult;
//电力岛
typedef struct estimator_eIsland
{
	int  iIslandNo;						//电力岛号
	int  iNodeNum;						//节点数
	int  iGenNum;						//发电机数
	int  iLoadNum;						//负荷数
	short  shSeTime;					//状态估计时间
	BYTE  bySeResult;					//状态估计结果
	short  shOpfTime;					//优化计算时间
	BYTE  byOpfResult;					//优化计算结果
	int  iMeasNum;						//估计量测数
	int  iEligibleNum;					//估计合格数
	char  szRefGen[48];					//平衡机
}estimator_eIsland,*LPestimator_eIsland;
//雷达权重
typedef struct estimator_RADARWT
{
	DWORD  NU;							//序号
	char  Name[32];						//名称
	float  maxVal;						//最大值
	float  minVal;						//最小值
	float  weight;						//权重
}estimator_RADARWT,*LPestimator_RADARWT;
//=================研究态===============
//PT表
typedef struct studypw_PT
{
	DWORD  NU;							//PT编号
	char  Name[32];						//PT名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	short  status;						//综合状态
}studypw_PT,*LPstudypw_PT;
//发电机
typedef struct studypw_Gen
{
	DWORD  NU;							//发电机号
	char  Name[32];						//发电机名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  MaxP;						//有功上限
	float  Par;							//有功出力百分比告警限
	float  CurPar;						//当前使用的告警率
	float  Pchk;						//检修功率
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	float  P;							//有功出力
	float  Q;							//无功出力
	float  V;							//机端电压
	float  angle;						//角度
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	float  Qmax;						//最大可用无功
	float  Qmaxi;						//最大进相无功
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	BYTE  Type;							//类型
	float  VL;							//电压等级
	short  status;						//综合状态
}studypw_Gen,*LPstudypw_Gen;
//开关刀闸
typedef struct studypw_Switch
{
	DWORD  NU;							//开关编号
	char  Name[32];						//开关名字
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//开关状态
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node1;						//节点1
	DWORD  Node2;						//节点2
	float  VL;							//电压等级
	short  status;						//综合状态
}studypw_Switch,*LPstudypw_Switch;
//负荷
typedef struct studypw_Load
{
	DWORD  NU;							//负荷编号
	char  Name[32];						//负荷名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  MaxP;						//有功上限
	float  MinP;						//有功下限
	float  P;							//有功负荷
	float  Q;							//无功负荷
	float  I;							//电流
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	float  VL;							//电压等级
	short  status;						//综合状态
}studypw_Load,*LPstudypw_Load;
//电容
typedef struct studypw_Shunt
{
	DWORD  NU;							//电容设备编号
	char  Name[32];						//电容设备名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Q;							//投入无功
	float  I;							//电流
	float  Qmax;						//最大无功输出
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	float  Qchk;						//检修容量
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	float  VL;							//电压等级
	short  status;						//综合状态
}studypw_Shunt,*LPstudypw_Shunt;
//电抗
typedef struct studypw_Sreact
{
	DWORD  NU;							//电抗器变号
	char  Name[32];						//电抗器名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Zx;							//投入电抗
	float  I;							//电流
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node1;						//节点1
	DWORD  Node2;						//节点2
	float  VL;							//电压等级
	short  status;						//综合状态
}studypw_Sreact,*LPstudypw_Sreact;
//2绕组变压器
typedef struct studypw_Tfm1
{
	DWORD  NU;							//2绕变编号
	char  Name[32];						//2绕变名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	WORD  Tallow;						//过载允许时间(分)
	WORD  Tover;						//已连续过载时间(分)
	float  tap;							//变压器分接头
	float  Pmax;						//变压器最大有功(容量)
	float  Par;							//变压器负载率警告限
	float  CurPar;						//当前使用的告警率
	float  P;							//高压侧有功
	float  Q;							//高压侧无功
	float  I;							//高压侧电流
	float  P2;							//低压侧有功
	float  Q2;							//低压侧无功
	float  I2;							//低压侧电流
	float  Tcur;						//当前温度
	float  Tmax;						//最高温度
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  NodeH;						//高压节点
	DWORD  NodeL;						//低压节点
	float  VL;							//电压等级
	short  status;						//综合状态
}studypw_Tfm1,*LPstudypw_Tfm1;
//3绕组变压器
typedef struct studypw_Tfm2
{
	DWORD  NU;							//3绕变编号
	char  Name[32];						//3绕变名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	WORD  Tallow;						//过载允许时间(分)
	WORD  Tover;						//已连续过载时间(分)
	float  TapH;						//高端分接头位置
	float  TapM;						//中端分接头位置
	float  TapL;						//低端分接头位置
	float  Pmax;						//变压器最大有功(容量)
	float  Par;							//变压器负载率警告限
	float  CurPar;						//当前使用的告警率
	float  P;							//高压侧有功
	float  Q;							//高压侧无功
	float  I;							//高压侧电流
	float  P2;							//中压侧有功
	float  Q2;							//中压侧无功
	float  I2;							//中压侧电流
	float  P3;							//低压侧有功
	float  Q3;							//低压侧无功
	float  I3;							//低压侧电流
	float  Tcur;						//当前温度
	float  Tmax;						//最高温度
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  NodeH;						//高压节点
	DWORD  NodeM;						//中压节点
	DWORD  NodeL;						//低压节点
	float  VL;							//电压等级
	short  status;						//综合状态
}studypw_Tfm2,*LPstudypw_Tfm2;
//静态无功补偿
typedef struct studypw_SVC
{
	DWORD  NU;							//SVC编号
	char  Name[32];						//SVC名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Qmax;						//最大无功输出
	float  Qmin;						//最小无功输出
	float  Q;							//无功输出
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	short  status;						//综合状态
}studypw_SVC,*LPstudypw_SVC;
//母线
typedef struct studypw_Bus
{
	DWORD  NU;							//母线编号
	char  Name[32];						//母线名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  MaxV;						//电压上限
	float  MinV;						//电压下限
	float  HiLimit;						//电压告警上限
	float  LoLimit;						//电压告警下限
	float  PreVhi;						//预警使用的上限
	float  PreVlo;						//预警使用的下限
	float  Vl;							//电压等级
	float  V;							//节点电压(pu)
	float  Vb;							//电压实际值
	float  DayMax;						//日最大值
	float  DayMin;						//日最小值
	float  deg;							//相角
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  AlarmHiLo;					//越上下限0，1，2
	BYTE  AlarmBand;					//越5%限0，1
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	DWORD  cNode;						//合并节点
	short  status;						//综合状态
}studypw_Bus,*LPstudypw_Bus;
//交流线
typedef struct studypw_Line
{
	DWORD  NU;							//交流线编号
	char  Name[32];						//交流线名称
	DWORD  Stationf;					//首端站
	DWORD  Stationt;					//末端站
	int  Zonef;							//起始区域域号
	int  Zonet;							//终点区域域号
	float  Imax;						//电流最大值
	float  MaxP;						//有功上限
	float  Par;							//输电线负载率告警限
	float  CurPar;						//当前使用的告警率
	float  VL;							//电压等级
	float  Pf;							//始端有功
	float  Qf;							//始端无功
	float  Pt;							//末端有功
	float  Qt;							//末端无功
	float  I;							//电流值
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  NodeF;						//首节点
	DWORD  NodeT;						//末节点
	short  status;						//综合状态
}studypw_Line,*LPstudypw_Line;
//直流线
typedef struct studypw_DCLine
{
	DWORD  NU;							//直流线编号
	char  Name[32];						//直流线名称
	DWORD  Stationf;					//首端站
	DWORD  Stationt;					//末端站
	int  Zonef;							//起始区域域号
	int  Zonet;							//终点区域域号
	float  Imax;						//电流最大值
	float  Maxp;						//有功上限
	float  Par;							//输电线负载率告警限
	float  CurPar;						//当前使用的告警率
	float  VL;							//电压等级
	float  Pf;							//始端有功
	float  Qf;							//始端无功
	float  Pt;							//末端有功
	float  Qt;							//末端无功
	float  I;							//电流值
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  NodeF;						//首节点
	DWORD  NodeT;						//末节点
	short  status;						//综合状态
}studypw_DCLine,*LPstudypw_DCLine;
//逆变器、变流器
typedef struct studypw_CVT
{
	DWORD  NU;							//设备编号
	char  Name[32];						//设备名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	short  status;						//综合状态
}studypw_CVT,*LPstudypw_CVT;
//接地
typedef struct studypw_GND
{
	DWORD  NU;							//接地编号
	char  Name[32];						//接地名称
	DWORD  Station;						//所属站号
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
}studypw_GND,*LPstudypw_GND;
//区域
typedef struct studypw_Zone
{
	DWORD  NU;							//区域编号
	char  Name[32];						//区域名称
	float  Pgen;						//发电有功
	float  Qgen;						//无功发电
	float  GenMax;						//发电机容量
	float  Pld;							//有功负荷
	float  Qld;							//无功负荷
	float  LdMax;						//负荷最大值
	float  ZoneLP;						//区域有功负荷
	float  ZoneLQ;						//区域无功负荷
	short  Sub50;						//500kV变电站数
	short  Sub22;						//220kV变电站数
	float  TransMW;						//变电站容量
}studypw_Zone,*LPstudypw_Zone;
//站
typedef struct studypw_Station
{
	DWORD  NU;							//站号
	char  Name[32];						//站名
	DWORD  zoneNU;						//所属区域
	float  VL;							//电压等级
	int  Type;							//厂站类型
	char  ID[24];						//变电站标识
	short  status;						//综合状态
}studypw_Station,*LPstudypw_Station;
//按节点电压排序
typedef struct studypw_VotOutage
{
	int  NU;							//设备编号
	char  type;							//设备类型
	float  Defl;						//风险指标
	BYTE  Group;						//分组类型
}studypw_VotOutage,*LPstudypw_VotOutage;
//按支路排序
typedef struct studypw_LineOutage
{
	int  NU;							//设备编号
	char  type;							//类型
	float  Defl;						//风险指标
	BYTE  Group;						//分组类型
}studypw_LineOutage,*LPstudypw_LineOutage;
//节点电压和支路合成
typedef struct studypw_AllOutage
{
	int  NU;							//设备编号
	char  type;							//类型
	float  Defl;						//风险指标
	BYTE  Group;						//分组类型
}studypw_AllOutage,*LPstudypw_AllOutage;
//系统指标
typedef struct studypw_SysGD
{
	DWORD  ID;							//指标标识ID
	char  Name[24];						//指标名称
	float  zb;							//当前指标
	float  Vmax;						//量程最大值
	float  Vmin;						//量程最小值
	float  Vmax1;						//第一段最大值
	float  Vmin1;						//第一段最小值
	float  Vmax2;						//第二段最大值
	float  Vmin2;						//第二段最小值
}studypw_SysGD,*LPstudypw_SysGD;
//系统告警
typedef struct studypw_SysAlarm
{
	WORD  Alarm;						//告警状态0,1
	WORD  num;							//发生告警的设备个数
	char  picname[32];					//推出画面名称
	WORD  picno;						//推出画面序号
}studypw_SysAlarm,*LPstudypw_SysAlarm;
//系统告警
typedef struct studypw_Ace
{
	DWORD  ID;							//标识ID
	float  CurVal;						//当前值
	CTime  datatime;					//数据时间
	BYTE  alarm;						//告警
	BYTE  ack;							//确认
}studypw_Ace,*LPstudypw_Ace;
//短路电流计算结果
typedef struct studypw_ShortCC
{
	DWORD  SwtNU;						//开关编号ID
	BYTE  GType;						//故障类型
	DWORD  LineNU;						//线路编号
	BYTE  LineType;						//线路类型
	CTime  DTime;						//计算时间
	float  TrPos;						//故障位置
	float  Imax;						//最大电流
	float  Isc;							//短路电流
	float  Usc;							//计算后电压
}studypw_ShortCC,*LPstudypw_ShortCC;
//用于仪表显示
typedef struct studypw_Meter
{
	int  ID;							//唯一的ID号
	char  Name[32];						//名称
	float  Value;						//当前值
	float  Vmax;						//最大值
	float  Vmin;						//最小值
	float  Vmax1;						//第一段最大值
	float  Vmin1;						//第一段最小值
	float  Vmax2;						//第二段最大值
	float  Vmin2;						//第二段最小值
	BYTE  AreaNo;						//分区序号
	BYTE  FieldNo;						//字段序号
}studypw_Meter,*LPstudypw_Meter;
//分区表
typedef struct studypw_Area
{
	DWORD  NU;							//分区号
	char  Name[32];						//分区名称
	DWORD  AColor;						//区域颜色
	float  Security;					//安全指标
	float  LDFactor;					//容载比
	float  LDFactorT;					//主变容载比
	float  LDFactorL;					//线路容载比
	float  LDFactorG;					//发电容载比
	float  LDFactorS;					//无功容载比
	float  Energy;						//电量平衡
	float  VolRate;						//电压合格率
	float  LDRate;						//负荷水平
	float  OverLoading;					//重载率
	float  OverLoadingT;				//主变重载率
	float  OverLoadingL;				//线路重载率
}studypw_Area,*LPstudypw_Area;
//电压无功控制表
typedef struct studypw_AVC
{
	DWORD  NU;							//变压器号
	char  Name[64];						//设备名称
	float  fVol;						//监测电压值
	float  fVar;						//监测无功值
	BYTE  POS;							//九区图位置
	BYTE  byTransType;					//变压器类型
	char  Property[256];				//属性
	char  PreValues[96];				//最近的变化值
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
}studypw_AVC,*LPstudypw_AVC;
//发电机PQV参数表
typedef struct studypw_PQV
{
	DWORD  GenNU;						//发电机编号
	char  Name[64];						//设备名称
	DWORD  BusNU;						//所属母线号
	BYTE  Gentype;						//电机隐凸极属性
	float  FacS;						//出厂额定容量
	float  FacU;						//出厂额定电压
	float  FacF;						//出厂额定频率
	float  xd;							//D轴电抗
	float  xq;							//Q轴电抗
	float  imax;						//最大励磁电流
	float  eqmax;						//最大磁通
	char  Property[256];				//属性
	BYTE  alarm;						//预警结果
	BYTE  ack;							//告警确认
}studypw_PQV,*LPstudypw_PQV;
//负载统计表
typedef struct studypw_ldstate
{
	DWORD  NU;							//编号
	BYTE  type;							//类型
	float  LDmax;						//日最大负载
	CTime  LDmaxT;						//最大负载出现时间
	DWORD  LDoverT;						//日负载过载时长
}studypw_ldstate,*LPstudypw_ldstate;
//高压联网运行数据
typedef struct studypw_Hvcondata
{
	DWORD  ID;							//ID值
	char  Name1[40];					//名字
	char  Name2[40];					//名字
	float  Vlimit;						//限值
	float  Curval;						//当前值
	char  sta;							//运行状态
	CTime  datetm;						//日期时间
	char  Alarm;						//告警
	char  Ack;							//确认
}studypw_Hvcondata,*LPstudypw_Hvcondata;
//变压器动态监视
typedef struct studypw_DynMonitor
{
	DWORD  NU;							//序号
	char  Name[32];						//名称
	BYTE  Winding;						//绕组类型
	BYTE  Mode;							//工作模式
	float  Normal1;						//正常限值1
	int  NorTime1;						//正常限值1时长
	float  Normal2;						//正常限值2
	int  NorTime2;						//正常限值2时长
	float  Normal3;						//正常限值3
	int  NorTime3;						//正常限值3时长
	float  Contingency1;				//事故限值1
	int  CtgTime1;						//事故限值1时长
	float  Contingency2;				//事故限值2
	int  CtgTime2;						//事故限值2时长
	float  Contingency3;				//事故限值3
	int  CtgTime3;						//事故限值3时长
	char  Buffer[240];					//缓存数据
}studypw_DynMonitor,*LPstudypw_DynMonitor;
//事故影响
typedef struct studypw_CtgEffect
{
	DWORD  CtgNU;						//事故设备号
	char  CtgName[32];					//事故设备名
	int  CtgType;						//事故设备类型
	float  fSecurity;					//风险指标
	DWORD  EftNU;						//异态设备号
	char  EftName[32];					//异态设备名
	int  EftType;						//异态设备类型
	float  EftVal;						//异态程度
}studypw_CtgEffect,*LPstudypw_CtgEffect;
//全网性数据
typedef struct studypw_Grid
{
	float  GenMax;						//全网发电总容量
	float  GenP;						//全网发电有功
	float  GenQ;						//全网发电无功
	float  StopP;						//全网停机总容量
	float  UpRes;						//全网上旋转备用
	float  DownRes;						//全网下旋转备用
	float  LoadMax;						//全网设计总负荷
	float  LoadP;						//全网用电负荷
}studypw_Grid,*LPstudypw_Grid;
//变压器绕组
typedef struct studypw_Winding
{
	DWORD  NU;							//绕组编号
	char  ID[24];						//绕组标识
	char  TID[24];						//变压器标识
	float  ratedKV;						//额定电压
	float  ratedMVA;					//额定容量
	float  fShortLoss;					//短路损耗
	float  fShortVol;					//短路电压
	float  fNoLoadLoss;					//空载损耗
	float  fR;							//电阻
	float  fX;							//电抗
	float  fB;							//电纳
	float  fR0;							//零电阻
	float  fX0;							//零电抗
	BYTE  Type;							//绕组类型
	BYTE  Tmax;							//最大档位
	BYTE  Tmin;							//最小档位
	BYTE  Tnor;							//正常档位
	float  step;						//档位步长
}studypw_Winding,*LPstudypw_Winding;
//导线表
typedef struct studypw_Conductor
{
	DWORD  NU;							//编号
	BYTE  Type;							//类型
	char  LID[24];						//线路标识
	float  fR;							//电阻
	float  fX;							//电抗
	float  fB;							//电纳
	float  fG;							//电导
	float  fR0;							//零序电阻
	float  fX0;							//零序电抗
	float  fB0;							//零序电纳
	float  fG0;							//零序电导
}studypw_Conductor,*LPstudypw_Conductor;
//=================AVC库===============
//网络设置表
typedef struct refavc_NetSet_table
{
	short  shNo;						//编号
	char  szName[50];					//网口名称
	BYTE  byProtocol;					//传输协议
	int  iPort;							//传输端口
	char  szDestIpAddr[24];				//目标IP
	char  szSouIpAddr[24];				//源IP
}refavc_NetSet_table,*LPrefavc_NetSet_table;
//遥控表
typedef struct refavc_yk_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shOrderNo;					//设备号
	DWORD  shSwitchNo;					//开关号
	DWORD  shYxOrder;					//遥信点号
	DWORD  shYKNo;						//遥控点号
	WORD  DayMaxCtrlNum;				//日最大控制数
	WORD  BackBlankTime;				//反向间隔时间
	CTime  LastCtrlTime;				//上次控制时间
	WORD  ActNum;						//动作次数
	WORD  RefuseNum;					//拒动次数
	BYTE  Priority;						//控制优先级
}refavc_yk_table,*LPrefavc_yk_table;
//遥调表
typedef struct refavc_yt_table
{
	short  shFacNo;						//厂号
	short  shOrderNo;					//序号
	BYTE  VlPos;						//电压侧位置
	BYTE  byCommandType;				//命令形式
	short  shUpNo;						//升命令对象号
	BYTE  byUpInverse;					//升命令取反
	short  shDownNo;					//降命令对象号
	BYTE  byDownInverse;				//降命令取反
	short  shStopNo;					//撤消命令对象号
	BYTE  byStopInverse;				//急停命令取反
	BYTE  byCurrentPos;					//当前位置
	BYTE  byTopPos;						//最高位置
	BYTE  byBottomPos;					//最低位置
	short  DayMaxActNum;				//日最大调节数
	WORD  HdDelayTime;					//滑档延时
	WORD  CdDelayTime;					//错档延时
	WORD  SameBlankTime;				//同向间隔时间
	WORD  BackBlankTime;				//反向间隔时间
	BYTE  LastCtrl;						//上次控制
	CTime  LastCtrlTime;				//上次控制时间
	WORD  shActNum;						//调节次数
	WORD  RefuseNum;					//拒动次数
}refavc_yt_table,*LPrefavc_yt_table;
//保护信息表
typedef struct refavc_relay_table
{
	short  shFacNo;						//厂号
	short  shOrderNo;					//序号
	char  szName[50];					//保护名称
	short  shAddress;					//地址
}refavc_relay_table,*LPrefavc_relay_table;
//保护状态表
typedef struct refavc_RelayYx_table
{
	short  shFacNo;						//厂号
	short  shOrderNo;					//序号
	char  szName[50];					//保护状态名
	short  shUnitNo;					//单元号
	short  shSourceNo;					//数据源号
	short  shFrameOrder;				//报文序号
	BYTE  byStatus;						//保护状态
	BYTE  byInverter;					//反向标志
	BYTE  byRefresh;					//更新状态
	short  shWarnMode;					//告警方式
	BYTE  byUpdateNum;					//更新计数
}refavc_RelayYx_table,*LPrefavc_RelayYx_table;
//T节点表
typedef struct refavc_tNode_table
{
	short  shTnodeNo;					//T接点编号
	char  szName[50];					//T接名
	BYTE  byVolDegree;					//电压等级
	short  shAreaNo;					//所在区域号
	short  shZoneNo;					//所在区段号
	int  iPointNo;						//连接点号
}refavc_tNode_table,*LPrefavc_tNode_table;
//等值变压器表
typedef struct refavc_equTrans_table
{
	short  shFacNo;						//厂号
	short  shMasterNo;					//主变压器号
	short  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	float  fCapacity;					//额定容量
	BYTE  byReguType;					//调压方式
	BYTE  byStatus;						//工作状态
	BYTE  byLock;						//闭锁状态
	BYTE  byCtrlType;					//优化控制类型
	short  shTapYcNo;					//档位遥测序号
	float  fResistance;					//电阻值
	float  fReactance;					//电抗值
	float  fConductance;				//电导值
	float  fSusceptance;				//电纳值
	float  fMinRatio;					//最小变比
	float  fMaxRatio;					//最大变比
	float  fStepSize;					//档位步长
	int  iFromPoint;					//首端连接点号
	int  iToPoint;						//末端连接点号
	short  shFromPNo;					//首端有功量测序号
	short  shFromQNo;					//首端无功量测序号
	short  shFromINo;					//首端电流量测序号
	short  shToPNo;						//末端有功量测序号
	short  shToQNo;						//末端无功量测序号
	short  shToINo;						//末端电流量测序号
	float  fBaseVol;					//基准电压
}refavc_equTrans_table,*LPrefavc_equTrans_table;
//闭锁定义表
typedef struct refavc_lock_table
{
	short  shLockNo;					//编号
	BYTE  byEventType;					//闭锁事件类型
	char  shEvent[32];					//闭锁事件描述
	short  shEventNo;					//闭锁事件序号
	BYTE  byObjectType;					//闭锁对象类型
	short  shObjectFac;					//闭锁对象厂号
	short  shObjectNo;					//闭锁对象序号
	char  shObjectName[32];				//闭锁对象名称
	short  shWarnMode;					//告警方式
	BYTE  byUnlockType;					//解除方式
}refavc_lock_table,*LPrefavc_lock_table;
//区域表
typedef struct refavc_area_table
{
	short  shAreaNo;					//区域号
	char  szAreaName[50];				//区域名
	float  fPA;							//计划有功输出
	float  fPLA;						//传输交换容差
}refavc_area_table,*LPrefavc_area_table;
//地域表
typedef struct refavc_zone_table
{
	short  shZoneNo;					//区段号
	char  szZoneName[50];				//区段名
	BYTE  byIT;							//优化类型
	BYTE  byLT;							//最小损耗类型
	BYTE  byMIZ;						//最大有功输出状态标志
	float  fLossDead;					//有功网损减少死区
	float  fLimitDead;					//电压越限减少死区
	float  fPrePLoss;					//优化前有功网损
	float  fPostPLoss;					//优化后有功网损
	float  fPreQLoss;					//优化前无功网损
	float  fPostQLoss;					//优化后无功网损
}refavc_zone_table,*LPrefavc_zone_table;
//电压限值表
typedef struct refavc_VolLimit_table
{
	DWORD  shLimitNo;					//限值集号
	short  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fMax1st;						//一级最大值
	float  fMin1st;						//一级最小值
	float  fMax2st;						//二级最大值
	float  fMin2st;						//二级最小值
	float  fMax3st;						//三级最大值
	float  fMin3st;						//三级最小值
}refavc_VolLimit_table,*LPrefavc_VolLimit_table;
//电压变化限值表
typedef struct refavc_VolVar_table
{
	DWORD  shLimitNo;					//限值集号
	short  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fMax1st;						//一级最大值
	float  fMin1st;						//一级最小值
	float  fMax2st;						//二级最大值
	float  fMin2st;						//二级最小值
	float  fMax3st;						//三级最大值
	float  fMin3st;						//三级最小值
}refavc_VolVar_table,*LPrefavc_VolVar_table;
//无功定值表
typedef struct refavc_qSetLim_table
{
	DWORD  shLimitNo;					//约束集号
	short  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fUpLimit;					//无功/功率因数高限
	float  fLowLimit;					//无功/功率因数低限
	BYTE  vlpos;						//电压侧
}refavc_qSetLim_table,*LPrefavc_qSetLim_table;
//电压限值表
typedef struct refavc_vSetLim_table
{
	DWORD  shLimitNo;					//约束集号
	short  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fUpLimit;					//电压高限
	float  fLowLimit;					//电压低限
	BYTE  vlpos;						//电压侧
}refavc_vSetLim_table,*LPrefavc_vSetLim_table;
//优化事件表
typedef struct refavc_opfEvent_table
{
	short  shEventNo;					//编号
	BYTE  byEventType;					//事件类型
	short  shSourceFac;					//事件厂号
	short  shSourceNo;					//事件序号
	BYTE  byYxVal;						//遥信值
	float  fChangeLimit;				//遥测变化限值绝对值
	short  shRelay;						//启动延时
	float  fLastValue;					//上次采样值
}refavc_opfEvent_table,*LPrefavc_opfEvent_table;
//优化时间表
typedef struct refavc_opfStart_table
{
	short  shTimeNo;					//编号
	CTime  tStartTime;					//启动时刻
}refavc_opfStart_table,*LPrefavc_opfStart_table;
//遥测变化限值表
typedef struct refavc_opfYcLim_table
{
	short  shLimitNo;					//编号
	short  shYcFac;						//遥测厂号
	short  shYcNo;						//遥测序号
	float  fChangeLimit;				//变化量绝对值限值
}refavc_opfYcLim_table,*LPrefavc_opfYcLim_table;
//优化参数设置表
typedef struct refavc_opfSet_table
{
	short  shAutoId;					//编号
	BYTE  byRunMode;					//运行方式
	BYTE  byControlMode;				//控制执行方式
	BYTE  bySetType;					//无功定值类型
	short  shMaxCmd;					//1次最多控制数量
	BYTE  byCtrlFail;					//控制过程异常处理
	BYTE  byObjPreAct;					//控制时未操作控制对象动作
	short  shSeTime;					//状态估计计算时间限值
	short  shOpfTime;					//优化计算时间限值
	short  shTriggerCyc;				//触发周期
	short  shCalWarn;					//优化计算启动告警方式
	short  shCtrlWarn;					//优化控制启动告警方式
	short  shCtrlEndWarn;				//优化控制成功告警方式
	short  shFailWarn;					//优化失败告警方式
	short  shAutoLockWarn;				//自动闭锁告警方式
	float  fBaseMva;					//基准容量
	short  shMaxTapReg;					//变压器最大连续调档数
}refavc_opfSet_table,*LPrefavc_opfSet_table;
//电气岛表
typedef struct refavc_tIsland_table
{
	int  iIslandNo;						//电力岛号
	int  iNodeNum;						//节点数
	int  iGenNum;						//发电机数
	int  iLoadNum;						//负荷数
	short  shSeTime;					//状态估计时间
	BYTE  bySeResult;					//se结果
	short  shOpfTime;					//优化计算时间
	BYTE  byOpfResult;					//opf结果
	int  iMeasNum;						//估计量测点数
	int  iEligibleNum;					//估计后合格点数
	char  szRefGen[200];				//平衡机
}refavc_tIsland_table,*LPrefavc_tIsland_table;
//计算节点表
typedef struct refavc_tmpNode_table
{
	int  iNodeNo;						//节点号
	int  iIslandNo;						//电力岛号
	short  shFacNo;						//所在厂号
	short  shAreaNo;					//所在区域号
	short  shZoneNo;					//所在区段号
	BYTE  byBusType;					//母线类型
	BYTE  byCtrlType;					//优化控制类型
	float  fBaseVol;					//基准电压
	float  fYcVol;						//遥测电压值
	float  fVolWeight;					//电压权值
	float  fVolStep;					//电压权值步长
	BYTE  byJPV;						//电压限制状态
	BYTE  byJPC;						//电压变化限制状态
	float  fSeVoltage;					//se电压值
	float  fSeAngle;					//se电压相角
	short  shLimitNo;					//电压限制集号
	short  shVarLimNo;					//电压变化限制集号
	char  Name[32];						//名称
}refavc_tmpNode_table,*LPrefavc_tmpNode_table;
//计算变压器表
typedef struct refavc_tmpTrans_table
{
	short  shFacNo;						//厂号
	short  shMasterNo;					//主变压器号
	int  iTransNo;						//变压器号
	BYTE  byVolSide;					//电压侧
	float  fCapacity;					//额定容量
	BYTE  byReguType;					//调压方式
	BYTE  byStatus;						//工作状态
	BYTE  byLock;						//闭锁状态
	BYTE  byCtrlType;					//优化控制类型
	float  fResistance;					//电阻值
	float  fReactance;					//电抗值
	float  fConductance;				//电导值
	float  fSusceptance;				//电纳值
	float  fMinRatio;					//最小变比
	float  fMaxRatio;					//最大变比
	float  fCurrentRatio;				//当前变比
	float  fStepSize;					//档位步长
	float  fYcFromP;					//首端有功量测
	float  fFromPWeight;				//首端有功权值
	float  fFromPStep;					//首端有功权值步长
	float  fYcFromQ;					//首端无功量测
	float  fFromQWeight;				//首端无功权值
	float  fFromQStep;					//首端无功权值步长
	float  fYcFromI;					//首端电流量测
	float  fFromIWeight;				//首端电流权值
	float  fFromIStep;					//首端电流权值步长
	float  fYcToP;						//末端有功量测
	float  fToPWeight;					//末端有功权值
	float  fToPStep;					//末端有功权值步长
	float  fYcToQ;						//末端无功量测
	float  fToQWeight;					//末端无功权值
	float  fToQStep;					//末端无功权值步长
	float  fYcToI;						//末端电流量测
	float  fToIWeight;					//末端电流权值
	float  fToIStep;					//末端电流权值步长
	int  iFromNode;						//首端节点号
	int  iToPoint;						//末端节点号
	float  fSeFromP;					//首端有功
	float  fSeFromQ;					//首端无功
	float  fSeFromI;					//首端电流
	float  fSeToP;						//末端有功
	float  fSeToQ;						//末端无功
	float  fSeToI;						//末端电流
	int  iIslandNo;						//电力岛号
	char  Name[32];						//名称
}refavc_tmpTrans_table,*LPrefavc_tmpTrans_table;
//计算无功设备表
typedef struct refavc_tmpShunt_table
{
	short  shFacNo;						//厂号
	int  iShuntNo;						//编号
	float  fRateVol;					//额定电压
	float  fCapacity;					//额定容量
	BYTE  byStatus;						//工作状态
	BYTE  byLock;						//闭锁状态
	BYTE  byCtrlType;					//优化控制类型
	float  fYcP;						//有功量测
	float  fPWeight;					//有功量测权值
	float  fPStep;						//有功量测权值步长
	float  fYcQ;						//无功量测
	float  fQWeight;					//无功量测权值
	float  fQStep;						//无功量测权值步长
	float  fYcI;						//电流量测
	float  fIWeight;					//电流量测权值
	float  fIStep;						//电流量测权值步长
	int  iFromNode;						//首端节点号
	int  iToPoint;						//末端节点号
	float  fSeQ;						//无功估计值
	int  iIslandNo;						//电力岛号
	char  Name[32];						//名称
}refavc_tmpShunt_table,*LPrefavc_tmpShunt_table;
//计算发电机表
typedef struct refavc_tmpGen_table
{
	short  shFacNo;						//厂号
	int  iGenNo;						//发电机号
	float  fRatedS;						//额定功率
	float  fRatedP;						//额定出力
	float  fRatedVol;					//额定电压
	BYTE  byStatus;						//工作状态
	float  fYcP;						//有功遥测
	float  fPWeight;					//有功遥测权值
	float  fPStep;						//有功遥测权值步长
	float  fYcQ;						//无功遥测
	float  fQWeight;					//无功遥测权值
	float  fQStep;						//无功遥测权值步长
	float  fMaxP;						//最大有功
	float  fMinP;						//最小有功
	float  fMaxQ;						//最大无功
	float  fMinQ;						//最小无功
	float  fMaxI;						//上限电流
	BYTE  byRunMode;					//运行模式
	float  fVolUpper;					//电压上限
	float  fVolLower;					//电压下限
	int  iNodeNo;						//节点号
	float  fSeP;						//有功估计值
	float  fSeQ;						//无功估计值
	int  iIslandNo;						//电力岛号
	char  Name[32];						//名称
}refavc_tmpGen_table,*LPrefavc_tmpGen_table;
//计算负荷表
typedef struct refavc_tmpLoad_table
{
	short  shFacNo;						//厂号
	int  iLoadNo;						//编号
	BYTE  byStatus;						//工作状态
	float  fYcP;						//有功遥测
	float  fPWeight;					//有功遥测权值
	float  fPStep;						//有功遥测权值步长
	float  fYcQ;						//无功遥测
	float  fQWeight;					//无功遥测权值
	float  fQStep;						//无功遥测权值步长
	float  fMaxP;						//最大有功
	float  fMinP;						//最小有功
	float  fMaxQ;						//最大无功
	float  fMinQ;						//最小无功
	int  iNodeNo;						//节点号
	float  fSeP;						//有功估计值
	float  fSeQ;						//无功估计值
	int  iIslandNo;						//电力岛号
	char  Name[32];						//名称
}refavc_tmpLoad_table,*LPrefavc_tmpLoad_table;
//计算线路表
typedef struct refavc_tmpLine_table
{
	int  iLineNo;						//线路号
	short  shFromFac;					//首端厂号
	short  shToFac;						//末端厂号
	float  fResistance;					//电阻值
	float  fReactance;					//电抗值
	float  fConductance;				//电导值
	float  fSusceptance;				//电纳值
	float  fFromCapacity;				//线路首端容量
	float  fToCapacity;					//线路末端容量
	float  fMaxI;						//电流限值
	float  fYcFromP;					//首端有功量测
	float  fFromPWeight;				//首端有功权值
	float  fFromPStep;					//首端有功权值步长
	float  fYcFromQ;					//首端无功量测
	float  fFromQWeight;				//首端无功权值
	float  fFromQStep;					//首端无功权值步长
	float  fYcFromI;					//首端电流量测
	float  fFromIWeight;				//首端电流权值
	float  fFromIStep;					//首端电流权值步长
	float  fYcToP;						//末端有功量测
	float  fToPWeight;					//末端有功权值
	float  fToPStep;					//末端有功权值步长
	float  fYcToQ;						//末端无功量测
	float  fToQWeight;					//末端无功权值
	float  fToQStep;					//末端无功权值步长
	float  fYcToI;						//末端电流量测
	float  fToIWeight;					//末端电流权值
	float  fToIStep;					//末端电流权值步长
	int  iFromNode;						//首端节点号
	int  iToNode;						//末端节点号
	float  fSeFromP;					//首端有功估计
	float  fSeFromQ;					//首端无功估计
	float  fSeFromI;					//首端电流估计
	float  fSeToP;						//末端有功估计
	float  fSeToQ;						//末端无功估计
	float  fSeToI;						//末端电流估计
	int  iIslandNo;						//电力岛号
	char  Name[32];						//名称
}refavc_tmpLine_table,*LPrefavc_tmpLine_table;
//计算母线表
typedef struct refavc_tmpBus_table
{
	short  shFacNo;						//厂号
	short  shBusNo;						//母线号
	int  iNodeNo;						//节点号
	BYTE  byBusType;					//母线类型
	BYTE  byCtrlType;					//优化控制类型
	float  fBaseVol;					//基准电压
	float  fYcVol;						//遥测电压值
	float  fVolWeight;					//电压权值
	float  fVolStep;					//电压权值步长
	BYTE  byJPV;						//电压限制状态
	BYTE  byJPC;						//电压变化限制状态
	short  shLimitNo;					//电压限制集号
	short  shVarLimNo;					//电压变化限制集号
	char  Name[32];						//名称
}refavc_tmpBus_table,*LPrefavc_tmpBus_table;
//优化计算控制信息表
typedef struct refavc_opfRes_table
{
	short  shAutoId;					//编号
	CTime  tStartTime;					//启动时间
	CTime  tEndTime;					//结束时间
	BYTE  byResult;						//计算控制结果
	float  fSeEligible;					//遥测估计合格率
	short  shOperateTime;				//控制执行时间
	float  fPrePLoss;					//优化前有功网损
	float  fPostPLoss;					//优化后有功网损
	float  fPreQLoss;					//优化前无功网损
	float  fPostQLoss;					//优化后无功网损
	short  shCmdNum;					//控制命令数量
	short  shCmdSucNum;					//控制命令成功数量
	char  szStartReason[100];				//启动原因
	char  szComment[200];				//说明
}refavc_opfRes_table,*LPrefavc_opfRes_table;
//量测不足表
typedef struct refavc_MeasAna_table
{
	int  iNoBalanceBran;				//不平衡支路数
	int  iNoBalanceNode;				//不平衡支路数
	int  iBSNoMatch;					//开关潮流不匹配数
	int  iBadData;						//坏数据数
	int  iShadMeas;						//可疑量测数
	int  iDummyMeas;					//伪量测数
}refavc_MeasAna_table,*LPrefavc_MeasAna_table;
//优化前节点表
typedef struct refavc_preNode_table
{
	int  iNodeNo;						//节点号
	int  iIslandNo;						//电力岛号
	float  fVoltage;					//电压值
	float  fVolAngle;					//电压相角
	float  fGenMW;						//发电有功
	float  fGenMvar;					//发电无功
	float  fLoadMW;						//负荷有功
	float  fLoadMvar;					//负荷无功
	float  fShuntMW;					//并联支路有功
	float  fShuntMvar;					//并联支路无功
}refavc_preNode_table,*LPrefavc_preNode_table;
//优化后节点表
typedef struct refavc_postNode_table
{
	int  iNodeNo;						//节点号
	int  iIslandNo;						//电力岛号
	float  fVoltage;					//电压值
	float  fVolAngle;					//电压相角
	float  fGenMW;						//发电有功
	float  fGenMvar;					//发电无功
	float  fLoadMW;						//负荷有功
	float  fLoadMvar;					//负荷无功
	float  fShuntMW;					//并联支路有功
	float  fShuntMvar;					//并联支路无功
	float  fPSen;						//有功灵敏度
	float  fQSen;						//无功灵敏度
	float  fSenLoss;					//灵敏度损耗因子
}refavc_postNode_table,*LPrefavc_postNode_table;
//优化前线路表
typedef struct refavc_preLine_table
{
	int  iLineNo;						//线路号
	int  iFromNode;						//首端节点号
	int  iToNode;						//末端节点号
	float  fFromMW;						//线路首端有功
	float  fFromMvar;					//线路首端无功
	float  fToMW;						//线路末端有功
	float  fToMvar;						//线路末端无功
}refavc_preLine_table,*LPrefavc_preLine_table;
//优化后线路表
typedef struct refavc_postLine_table
{
	int  iLineNo;						//线路号
	int  iFromNode;						//首端节点号
	int  iToNode;						//末端节点号
	float  fFromMW;						//线路首端有功
	float  fFromMvar;					//线路首端无功
	float  fToMW;						//线路末端有功
	float  fToMvar;						//线路末端无功
}refavc_postLine_table,*LPrefavc_postLine_table;
//优化前变压器表
typedef struct refavc_preTrans_table
{
	short  shFacNo;						//厂号
	short  shMasterNo;					//主变压器号
	short  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	int  iFromNode;						//首端节点号
	int  iToNode;						//末端节点号
	float  fFromMW;						//首端有功
	float  fFromMvar;					//首端无功
	float  fToMW;						//末端有功
	float  fToMvar;						//末端无功
	float  fFromPf;						//首端功率因数
	float  fToPf;						//末端功率因数
}refavc_preTrans_table,*LPrefavc_preTrans_table;
//优化后变压器表
typedef struct refavc_postTran_table
{
	short  shFacNo;						//厂号
	short  shMasterNo;					//主变压器号
	short  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	int  iFromNode;						//首端节点号
	int  iToNode;						//末端节点号
	float  fFromMW;						//首端有功
	float  fFromMvar;					//首端无功
	float  fToMW;						//末端有功
	float  fToMvar;						//末端无功
	float  fFromPf;						//首端功率因数
	float  fToPf;						//末端功率因数
}refavc_postTran_table,*LPrefavc_postTran_table;
//优化控制变压器表
typedef struct refavc_opfTrans_table
{
	short  shFacNo;						//厂号
	short  shMasterNo;					//主变压器号
	short  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	int  iFromNode;						//首端节点号
	int  iToNode;						//末端节点号
	float  fFromBaseVol;				//首端基准电压
	float  fToBaseVol;					//末端基准电压
	float  fPreRatio;					//优化前变比
	float  fPostRatio;					//优化后变比
}refavc_opfTrans_table,*LPrefavc_opfTrans_table;
//优化控制无功表
typedef struct refavc_opfShunt_table
{
	short  shFacNo;						//厂号
	short  shShuntNo;					//编号
	int  iFromNode;						//首端节点号
	int  iToNode;						//末端节点号
	float  fPreVar;						//优化前容量
	float  fPostVar;					//优化后容量
}refavc_opfShunt_table,*LPrefavc_opfShunt_table;
//VQC定值表
typedef struct refavc_VqcSet_table
{
	short  shFacNo;						//厂号
	BYTE  byType;						//变压器类型
	short  shTransNo;					//变压器号
	char  szFacName[50];				//厂站名
	char  szTransName[50];				//变压器名
	float  fHiVolSet;					//电压定值上限
	float  fLowVolSet;					//电压定值下限
	float  fHiVarSet;					//无功/功率因数定值上限
	float  fLowVarSet;					//无功/功率因数定值下限
	BYTE  byStatus;						//发送状态
}refavc_VqcSet_table,*LPrefavc_VqcSet_table;
//控制命令表
typedef struct refavc_opfCmd_table
{
	int  tmOrder;						//序号
	short  shFacNo;						//厂号
	BYTE  byType;						//设备类型
	short  shDeviceNo;					//设备编号
	char  szFacName[50];				//厂站名
	char  szDevName[50];				//设备名
	BYTE  byCommand;					//命令
	short  shCurTap;					//当前档位
	short  shEndTap;					//目标档位
	BYTE  byStatus;						//控制状态
}refavc_opfCmd_table,*LPrefavc_opfCmd_table;
//发电机优化表
typedef struct refavc_opfGen_table
{
	short  shFacNo;						//厂号
	short  shGenNo;						//发电机号
	int  iNodeNo;						//节点号
	float  fPreP;						//优化前有功
	float  fPostP;						//优化后有功
	float  fPreQ;						//优化前无功
	float  fPostQ;						//优化后无功
}refavc_opfGen_table,*LPrefavc_opfGen_table;
//发电机PQ曲线表
typedef struct refavc_genPQ_table
{
	short  shFacNo;						//厂号
	short  shGenNo;						//发电机号
	short  shOrderNo;					//序号
	float  fP;							//有功出力
	float  fMaxQ;						//最大无功
	float  fMinQ;						//最小无功
}refavc_genPQ_table,*LPrefavc_genPQ_table;
//母线优化结果表
typedef struct refavc_opfBus_table
{
	short  shFacNo;						//厂号
	short  shBusNo;						//母线号
	char  szFacName[50];				//厂站名
	char  szBusName[50];				//母线名
	float  fYcVol;						//遥测电压值
	float  fSeVol;						//状态估计电压值
	float  fSeDev;						//量测估计偏差
	float  fSeAngle;					//状态估计电压相角
	float  fOpfVol;						//优化电压值
	float  fOpfAngle;					//优化电压相角
	float  fPostVol;					//控制后电压值
}refavc_opfBus_table,*LPrefavc_opfBus_table;
//线路优化结果表
typedef struct refavc_opfLine_table
{
	int  iLineNo;						//线路号
	char  szName[50];					//线路名
	float  fYcFromP;					//首端有功遥测
	float  fYcFromQ;					//首端无功遥测
	float  fYcToP;						//末端有功遥测
	float  fYcToQ;						//末端无功遥测
	float  fSeFromP;					//状态估计首端有功
	float  fSeFromQ;					//状态估计首端无功
	float  fSeToP;						//状态估计末端有功
	float  fSeToQ;						//状态估计末端无功
	float  fOpfFromP;					//优化首端有功
	float  fOpfFromQ;					//优化首端无功
	float  fOpfToP;						//优化末端有功
	float  fOpfToQ;						//优化末端无功
	float  fPostFromP;					//控制后首端有功遥测
	float  fPostFromQ;					//控制后首端无功遥测
	float  fPostToP;					//控制后末端有功遥测
	float  fPostToQ;					//控制后末端无功遥测
}refavc_opfLine_table,*LPrefavc_opfLine_table;
//变压器优化结果表
typedef struct refavc_opfByq_table
{
	short  shFacNo;						//厂号
	BYTE  byType;						//变压器类型
	short  shTransNo;					//变压器号
	char  szFacName[50];				//厂站名
	char  szTransName[50];				//变压器名
	float  fYcHiP;						//高压侧有功遥测
	float  fYcHiQ;						//高压侧无功遥测
	float  fYcMidP;						//中压侧有功遥测
	float  fYcMidQ;						//中压侧无功遥测
	float  fYcLowP;						//低压侧有功遥测
	float  fYcLowQ;						//低压侧无功遥测
	float  fPreHiRatio;					//优化前高压变比
	float  fPreMidRatio;				//优化前中压变比
	float  fSeHiP;						//状态估计高压侧有功
	float  fSeHiQ;						//状态估计高压侧无功
	float  fSeMidP;						//状态估计中压侧有功
	float  fSeMidQ;						//状态估计中压侧无功
	float  fSeLowP;						//状态估计低压侧有功
	float  fSeLowQ;						//状态估计低压侧无功
	float  fOpfHiP;						//优化高压侧有功
	float  fOpfHiQ;						//优化高压侧无功
	float  fOpfMidP;					//优化中压侧有功
	float  fOpfMidQ;					//优化中压侧无功
	float  fOpfLowP;					//优化低压侧有功
	float  fOpfLowQ;					//优化低压侧无功
	float  fPostHiRatio;				//优化后高压变比
	float  fPostMidRatio;				//优化后中压变比
	float  fPostHiP;					//控制后高压侧有功遥测
	float  fPostHiQ;					//控制后高压侧无功遥测
	float  fPostMidP;					//控制后中压侧有功遥测
	float  fPostMidQ;					//控制后中压侧无功遥测
	float  fPostLowP;					//控制后低压侧有功遥测
	float  fPostLowQ;					//控制后低压侧无功遥测
}refavc_opfByq_table,*LPrefavc_opfByq_table;
//无功设备优化结果表
typedef struct refavc_opfWgsb_table
{
	short  shFacNo;						//厂号
	short  shShuntNo;					//编号
	char  szFacName[50];				//厂站名
	char  szName[50];					//设备名
	float  fYcQ;						//无功遥测
	float  fSeQ;						//状态估计无功
	float  fOpfQ;						//优化无功
	float  fPostQ;						//控制后无功遥测
}refavc_opfWgsb_table,*LPrefavc_opfWgsb_table;
//发电机优化结果表
typedef struct refavc_opfFdj_table
{
	short  shFacNo;						//厂号
	short  shGenNo;						//发电机号
	char  szFacName[50];				//厂站名
	char  szName[50];					//发电机名
	float  fYcP;						//有功遥测
	float  fYcQ;						//无功遥测
	float  fSeP;						//状态估计有功
	float  fSeQ;						//状态估计无功
	float  fOpfP;						//优化有功
	float  fOpfQ;						//优化无功
	float  fPostP;						//控制后有功遥测
	float  fPostQ;						//控制后无功遥测
}refavc_opfFdj_table,*LPrefavc_opfFdj_table;
//电压估计统计表
typedef struct refavc_VolSeSta_table
{
	int  iIslandNo;						//电力岛号
	BYTE  byStaType;					//估计统计类型
	BYTE  byVolDegree;					//电压等级序号
	float  fVolSeAccu;					//估计合格率
}refavc_VolSeSta_table,*LPrefavc_VolSeSta_table;
//母线电压越限表
typedef struct refavc_BusExcee_table
{
	short  shFacNo;						//厂号
	short  shBusNo;						//母线号
	char  szFacName[50];				//厂站名
	char  szBusName[50];				//母线名
	float  fYcVol;						//遥测电压值
	float  fSeVol;						//状态估计电压值
	float  fOpfVol;						//优化电压值
}refavc_BusExcee_table,*LPrefavc_BusExcee_table;
//变压器损耗表
typedef struct refavc_LossByq_table
{
	short  shFacNo;						//厂号
	BYTE  byType;						//变压器类型
	short  shTransNo;					//变压器号
	char  szFacName[50];				//厂站名
	char  szTransName[50];				//变压器名
	float  fPrePLoss;					//优化前有功损耗
	float  fPostPLoss;					//优化后有功损耗
	float  fPreQLoss;					//优化前无功损耗
	float  fPostQLoss;					//优化后无功损耗
}refavc_LossByq_table,*LPrefavc_LossByq_table;
//线路损耗表
typedef struct refavc_LossLine_table
{
	int  iLineNo;						//线路号
	char  szName[50];					//线路名
	float  fPrePLoss;					//优化前有功损耗
	float  fPostPLoss;					//优化后有功损耗
	float  fPreQLoss;					//优化前无功损耗
	float  fPostQLoss;					//优化后无功损耗
}refavc_LossLine_table,*LPrefavc_LossLine_table;
//当前闭锁表
typedef struct refavc_curLock_table
{
	CTime  tLockTime;					//闭锁时间
	BYTE  byObjectType;					//闭锁对象类型
	short  shObjectFac;					//闭锁对象厂号
	char  szFacName[50];				//闭锁对象厂名
	short  shObjectNo;					//闭锁对象号
	char  szObectName[50];				//闭锁对象名
	char  szLockInfo[100];				//闭锁信息
}refavc_curLock_table,*LPrefavc_curLock_table;
//反时限控制表
typedef struct refavc_DevCtrl_table
{
	short  shOrderNo;					//序号
	float  fVolIntegral;				//电压积分量
	float  fVolSecIncreas;				//电压二级增量
	short  shVolHop;					//电压跳变数
	float  fCosIntegral;				//力率积分面积
	float  fCosSecIncreas;				//力率二级增量
	short  shCosHop;					//力率跳变数
}refavc_DevCtrl_table,*LPrefavc_DevCtrl_table;
//规则表
typedef struct refavc_Rule_table
{
	BYTE  rule_no;						//规则编号
	short  order_no;					//序号
	BYTE  v_status;						//电压状态
	BYTE  cos_status;					//功率因数状态
	BYTE  t_status;						//变压器当前状
	BYTE  c_status;						//补偿装置状态
	BYTE  t_action;						//变压器动作
	BYTE  c_action;						//补偿装置动作
}refavc_Rule_table,*LPrefavc_Rule_table;
//可疑量测表
typedef struct refavc_shady_table
{
	BYTE  bType;						//类型
	char  szInfo[160];					//信息
}refavc_shady_table,*LPrefavc_shady_table;
#endif