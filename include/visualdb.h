#if !defined(_DB_STRUCT_H_)
#define _DB_STRUCT_H_
/************************************************/
//本头文件由“数据库设计软件”自动生成
//2015-12-7
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
	char  Name[64];						//发电机名
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
	CTime  LogTime;						//数据时标
}visualpw_Gen,*LPvisualpw_Gen;
//开关刀闸
typedef struct visualpw_Switch
{
	DWORD  NU;							//开关编号
	char  Name[64];						//开关名字
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
	CTime  LogTime;						//数据时标
}visualpw_Switch,*LPvisualpw_Switch;
//负荷
typedef struct visualpw_Load
{
	DWORD  NU;							//负荷编号
	char  Name[64];						//负荷名称
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
	CTime  LogTime;						//数据时标
}visualpw_Load,*LPvisualpw_Load;
//电容
typedef struct visualpw_Shunt
{
	DWORD  NU;							//电容设备编号
	char  Name[64];						//电容设备名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Q;							//投入无功
	float  I;							//电流
	float  RVol;						//额定电压
	float  Qmax;						//最大无功输出
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	float  Qchk;						//检修容量
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	float  VL;							//电压等级
	short  status;						//综合状态
	DWORD  CtrlType;					//控制类型定义
	CTime  LogTime;						//数据时标
}visualpw_Shunt,*LPvisualpw_Shunt;
//电抗
typedef struct visualpw_Sreact
{
	DWORD  NU;							//电抗器变号
	char  Name[64];						//电抗器名
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
	DWORD  CtrlType;					//控制类型定义
	float  RVol;						//额定电压
	float  Qmax;						//最大无功输出
	CTime  LogTime;						//数据时标
}visualpw_Sreact,*LPvisualpw_Sreact;
//2绕组变压器
typedef struct visualpw_Tfm1
{
	DWORD  NU;							//2绕变编号
	char  Name[64];						//2绕变名
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
	DWORD  CtrlType;					//控制类型定义
	float  CosDn;						//功率因数下限
	float  CosUp;						//功率因数上限
	CTime  LogTime;						//数据时标
}visualpw_Tfm1,*LPvisualpw_Tfm1;
//3绕组变压器
typedef struct visualpw_Tfm2
{
	DWORD  NU;							//3绕变编号
	char  Name[64];						//3绕变名
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
	DWORD  CtrlType;					//控制类型定义
	float  CosDn;						//功率因数下限
	float  CosUp;						//功率因数上限
	CTime  LogTime;						//数据时标
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
	CTime  LogTime;						//数据时标
}visualpw_SVC,*LPvisualpw_SVC;
//母线
typedef struct visualpw_Bus
{
	DWORD  NU;							//母线编号
	char  Name[64];						//母线名称
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
	DWORD  CtrlType;					//控制类型定义
	CTime  LogTime;						//数据时标
}visualpw_Bus,*LPvisualpw_Bus;
//交流线
typedef struct visualpw_Line
{
	DWORD  NU;							//交流线编号
	char  Name[64];						//交流线名称
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
	BYTE  EquiSta;						//等值状态
	CTime  LogTime;						//数据时标
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
	CTime  LogTime;						//数据时标
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
	char  Name[64];						//接地名称
	DWORD  Station;						//所属站号
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	CTime  LogTime;						//数据时标
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
	CTime  LogTime;						//数据时标
}visualpw_Zone,*LPvisualpw_Zone;
//站
typedef struct visualpw_Station
{
	DWORD  NU;							//站号
	char  Name[64];						//站名
	DWORD  zoneNU;						//所属区域
	float  VL;							//电压等级
	int  Type;							//厂站类型
	char  ID[24];						//变电站标识
	short  status;						//综合状态
	DWORD  CtrlType;					//控制类型定义
	CTime  LogTime;						//数据时标
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
	CTime  LogTime;						//数据时标
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
	char  Name[64];						//名称
	char  ID[24];						//绕组标识
	char  TID[24];						//变压器标识
	float  baseKV;						//基准电压
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
	CTime  LogTime;						//数据时标
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
	CTime  LogTime;						//数据时标
}visualpw_Conductor,*LPvisualpw_Conductor;
//保护信息表
typedef struct visualpw_Relay
{
	DWORD  ID;							//保护ID号
	DWORD  Station;						//厂站号
	char  Name[64];						//保护名称
	BYTE  RelayType;					//保护类型
	BYTE  YX;							//遥信状态
	DWORD  BayID;						//间隔ID
	DWORD  DevID;						//关联设备ID
	DWORD  DevNU;						//关联设备编号
	char  DevName[64];					//关联设备名称
	CTime  LogTime;						//数据时标
}visualpw_Relay,*LPvisualpw_Relay;
//遥信定义表
typedef struct visualpw_YX
{
	DWORD  ID;							//遥信ID
	char  Name[64];						//遥信名称
	DWORD  DevID;						//设备ID
	BYTE  DevType;						//设备类型
	char  DevName[64];					//设备名称
	BYTE  YX;							//遥信状态
	CTime  LogTime;						//数据时标
}visualpw_YX,*LPvisualpw_YX;
//遥测定义表
typedef struct visualpw_YC
{
	DWORD  ID;							//遥测ID
	char  Name[64];						//遥测名称
	DWORD  DevID;						//设备ID
	BYTE  DevType;						//设备类型
	char  DevName[64];					//设备名称
	BYTE  MeasType;						//遥测类型
	BYTE  MeasPos;						//遥测位置
	float  YC;							//遥测值
	CTime  LogTime;						//数据时标
}visualpw_YC,*LPvisualpw_YC;
//遥控遥信关系表
typedef struct visualpw_YKYX
{
	DWORD  NU;							//编号
}visualpw_YKYX,*LPvisualpw_YKYX;
//系统网损日数据表
typedef struct visualpw_SysPowerLoss
{
	CTime  LogTime;						//统计时间
	BYTE  IsToDay;						//是否当日数据
	float  PowerP;						//总有功
	float  PowerQ;						//总无功
	float  LoadP;						//负荷有功
	float  LoadQ;						//负荷无功
	float  ShuntQ;						//补偿无功
	float  LossP;						//有功网损
	float  LossQ;						//无功网损
	float  TheoryLossP;					//理论有功网损
	float  TheoryLossQ;					//理论无功网损
}visualpw_SysPowerLoss,*LPvisualpw_SysPowerLoss;
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
	DWORD  Nu;							//测试编号（0为专用编号，非0
	char  Name[64];						//案例名称
	char  Info[200];					//案例信息
	CTime  TestTime;					//案例测试时间
	BYTE  TestType;						//案例测试方法
	CTime  ProcTime;					//过程计算选择时间
	BYTE  RunSta;						//运行状态1运2完
	short  TopuRun;						//拓扑运行状态
	short  SeRun;						//状态估计运行状态
	short  OpfRun;						//优化计算运行状态
	char  Result[64];					//仿真过程基本结论
}common_RunType,*LPcommon_RunType;
//母线关联值
typedef struct common_BusV
{
	DWORD  Nu;							//编号
	char  Name[64];						//设备名
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
	char  VName[64];					//可视化中设备名字
	BYTE  DevType;						//设备类型
	BYTE  MeasType;						//量测类型
	char  MeasName[64];					//量测名称
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
	char  Name[64];						//名称
	float  Value;						//运用值
}common_PreLimit,*LPcommon_PreLimit;
//虚拟开关关连关系
typedef struct common_VSwitch
{
	DWORD  SwtNU;						//开关ID
	char  Name[64];						//开关名字
	DWORD  VSwtNU;						//所属虚拟开关NU
	DWORD  LineNU;						//所属线路
}common_VSwitch,*LPcommon_VSwitch;
//预定义断面潮流
typedef struct common_PreDefSF
{
	DWORD  ID;							//断面ID
	char  Name[64];						//断面名字
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
	char  Name[64];						//参数名
	float  Param;						//参数值
}common_AppParam,*LPcommon_AppParam;
//子对象表
typedef struct common_SubObject
{
	DWORD  NU;							//序号
	char  Name[64];						//名称
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
	char  Name[64];						//名称
	float  max;							//最大值
	float  min;							//最小值
	float  val;							//值
	BYTE  type;							//量测类型
	char  ID[32];						//标识
	char  PID[32];						//父标识
}common_UnEquMeas,*LPcommon_UnEquMeas;
//控制连接关系表
typedef struct common_LinkRelation
{
	DWORD  NU;							//设备NU
	char  Name[64];						//设备名称
	DWORD  Station;						//厂站编号
	DWORD  Zone;						//区域编号
	BYTE  DevType;						//设备类型
	DWORD  Bus1;						//关联母线1
	char  BusName1[64];					//关联母线1
	char  LinkDev1[128];				//连接的开关设备，用,号隔开
	DWORD  Bus2;						//关联母线2
	char  BusName2[64];					//关联母线2
	char  LinkDev2[128];				//连接的开关设备，用,号隔开
	DWORD  Bus3;						//关联母线3
	char  BusName3[64];					//关联母线3
	char  LinkDev3[128];				//连接的开关设备，用,号隔开
}common_LinkRelation,*LPcommon_LinkRelation;
//极限基础电压表
typedef struct common_BVoltage
{
	WORD  NU;							//编号
	char  Name[32];						//名称
	float  BaseVol;						//基础电压
	float  StanVol;						//标定电压
	float  Dn1;							//下行电压
	float  Up1;							//上行电压
	float  Dn2;							//下行电压
	float  Up2;							//上行电压
	float  Dn3;							//下行电压
	float  Up3;							//上行电压
}common_BVoltage,*LPcommon_BVoltage;
//系统运行参数
typedef struct common_SysRunParam
{
	BYTE  ParamType;					//参数类别
	char  ParamName[64];				//参数名称
	char  ParamValue[128];				//参数
}common_SysRunParam,*LPcommon_SysRunParam;
//=================仿真计算库===============
//发电机
typedef struct emluator_mGen
{
	DWORD  NU;							//编号
	char  Name[64];						//名称
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
	char  Name[64];						//名称
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
	char  Name[64];						//名称
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
	char  Name[64];						//名称
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
	char  Name[64];						//名称
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
	char  Name[64];						//名称
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
	char  Name[64];						//名称
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
	char  Name[64];						//名称
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
	char  Name[64];						//名称
	float  statval;						//统计值
}emluator_mStat,*LPemluator_mStat;
//=================评估库===============
//项目表
typedef struct estimator_project
{
	DWORD  NU;							//项目编号
	char  Name[64];						//项目名称
	char  AVC[64];						//被评估AVC
	BYTE  Type;							//类型
	char  projectpath[128];				//项目路径
}estimator_project,*LPestimator_project;
//评估
typedef struct estimator_estimate
{
	DWORD  NU;							//编号
	char  description[64];				//评估描述
	DWORD  project;						//项所属项目
	char  report[64];					//报告评估
}estimator_estimate,*LPestimator_estimate;
//评估案例
typedef struct estimator_estcase
{
	DWORD  NU;							//案例编号
	char  Name[64];						//案例名称
	DWORD  project;						//项所属项目
	short  casetype;					//案例类型
	BYTE  onlie;						//在线案例
	char  descr[256];					//案例描述
}estimator_estcase,*LPestimator_estcase;
//断面定义
typedef struct estimator_sectdef
{
	DWORD  NU;							//断面编号
	char  Name[64];						//断面名称
	char  Path[64];						//断面路径
	DWORD  estcase;						//所属评案例
	CTime  dtime;						//断面时间
	char  descr[256];					//案例描述
}estimator_sectdef,*LPestimator_sectdef;
//发电机
typedef struct estimator_eGen
{
	DWORD  NU;							//编号
	char  Name[64];						//名称
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
	char  Name[64];						//名称
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
	char  Name[64];						//名称
	DWORD  MU;							//宿主变
	float  rateP;						//额定容量
	float  rateVI;						//额定电压
	float  rateVJ;						//额定电压
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
	float  TapPos;						//当前档位
	float  Pi;							//I端有功
	float  Qi;							//I端无功
	float  Pj;							//J端有功
	float  Qj;							//J端无功
	float  I;							//电流
	BYTE  sta;							//状态
	short  status;						//综合状态
	int  station;						//厂站
	int  island;						//电力岛
	DWORD  Parallel;					//并联支路
}estimator_eTfm,*LPestimator_eTfm;
//线路
typedef struct estimator_eLine
{
	DWORD  NU;							//编号
	char  Name[64];						//名称
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
	DWORD  Parallel;					//并联支路
}estimator_eLine,*LPestimator_eLine;
//负荷
typedef struct estimator_eLoad
{
	DWORD  NU;							//编号
	char  Name[64];						//名称
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
	char  Name[64];						//名称
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
	BYTE  IsVirtual;					//虚拟标志
}estimator_eShunt,*LPestimator_eShunt;
//串补
typedef struct estimator_eSerial
{
	DWORD  NU;							//编号
	char  Name[64];						//名称
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
	char  Name[64];						//名称
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
	char  MeasID[64];					//量测ID
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
	char  Name[64];						//内容名称
	short  casetype;					//案例类型
	int  estkeep;						//评估保持时间
	char  dsite[64];					//数据位置
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
	char  Name[64];						//案例名称
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
//=================AVC库===============
//网络设置表
typedef struct refavc_NetSet_table
{
	DWORD  shNo;						//编号
	char  szName[64];					//网口名称
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
	char  Name[64];						//名称
}refavc_yk_table,*LPrefavc_yk_table;
//遥调表
typedef struct refavc_yt_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shOrderNo;					//序号
	BYTE  VlPos;						//电压侧位置
	BYTE  byCommandType;				//命令形式
	DWORD  shUpNo;						//升命令对象号
	BYTE  byUpInverse;					//升命令取反
	DWORD  shDownNo;					//降命令对象号
	BYTE  byDownInverse;				//降命令取反
	DWORD  shStopNo;					//撤消命令对象号
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
	char  Name[64];						//名称
}refavc_yt_table,*LPrefavc_yt_table;
//保护信息表
typedef struct refavc_relay_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shOrderNo;					//序号
	char  szName[64];					//保护名称
	short  shAddress;					//地址
}refavc_relay_table,*LPrefavc_relay_table;
//保护状态表
typedef struct refavc_RelayYx_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shOrderNo;					//序号
	char  szName[64];					//保护状态名
	DWORD  shUnitNo;					//单元号
	DWORD  shSourceNo;					//数据源号
	DWORD  shFrameOrder;				//报文序号
	BYTE  byStatus;						//保护状态
	BYTE  byInverter;					//反向标志
	BYTE  byRefresh;					//更新状态
	short  shWarnMode;					//告警方式
	BYTE  byUpdateNum;					//更新计数
}refavc_RelayYx_table,*LPrefavc_RelayYx_table;
//T节点表
typedef struct refavc_tNode_table
{
	DWORD  shTnodeNo;					//T接点编号
	char  szName[64];					//T接名
	BYTE  byVolDegree;					//电压等级
	DWORD  shAreaNo;					//所在区域号
	DWORD  shZoneNo;					//所在区段号
	int  iPointNo;						//连接点号
}refavc_tNode_table,*LPrefavc_tNode_table;
//等值变压器表
typedef struct refavc_equTrans_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shMasterNo;					//主变压器号
	DWORD  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	float  fCapacity;					//额定容量
	BYTE  byReguType;					//调压方式
	BYTE  byStatus;						//工作状态
	BYTE  byLock;						//闭锁状态
	BYTE  byCtrlType;					//优化控制类型
	DWORD  shTapYcNo;					//档位遥测序号
	float  fResistance;					//电阻值
	float  fReactance;					//电抗值
	float  fConductance;				//电导值
	float  fSusceptance;				//电纳值
	float  fMinRatio;					//最小变比
	float  fMaxRatio;					//最大变比
	float  fStepSize;					//档位步长
	DWORD  iFromPoint;					//首端连接点号
	int  iToPoint;						//末端连接点号
	DWORD  shFromPNo;					//首端有功量测序号
	DWORD  shFromQNo;					//首端无功量测序号
	DWORD  shFromINo;					//首端电流量测序号
	DWORD  shToPNo;						//末端有功量测序号
	DWORD  shToQNo;						//末端无功量测序号
	DWORD  shToINo;						//末端电流量测序号
	float  fBaseVol;					//基准电压
	char  szName[64];					//名称
}refavc_equTrans_table,*LPrefavc_equTrans_table;
//闭锁定义表
typedef struct refavc_lock_table
{
	DWORD  shLockNo;					//编号
	BYTE  byEventType;					//闭锁事件类型
	char  shEvent[64];					//闭锁事件描述
	DWORD  shEventNo;					//闭锁事件序号
	BYTE  byObjectType;					//闭锁对象类型
	DWORD  shObjectFac;					//闭锁对象厂号
	DWORD  shObjectNo;					//闭锁对象序号
	char  shObjectName[64];				//闭锁对象名称
	short  shWarnMode;					//告警方式
	BYTE  byUnlockType;					//解除方式
}refavc_lock_table,*LPrefavc_lock_table;
//区域表
typedef struct refavc_area_table
{
	DWORD  shAreaNo;					//区域号
	char  szAreaName[64];				//区域名
	float  fPA;							//计划有功输出
	float  fPLA;						//传输交换容差
}refavc_area_table,*LPrefavc_area_table;
//地域表
typedef struct refavc_zone_table
{
	DWORD  shZoneNo;					//区段号
	char  szZoneName[64];				//区段名
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
	DWORD  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fMax1st;						//一级最大值
	float  fMin1st;						//一级最小值
	float  fMax2st;						//二级最大值
	float  fMin2st;						//二级最小值
	float  fMax3st;						//三级最大值
	float  fMin3st;						//三级最小值
	char  szName[64];					//名称
}refavc_VolLimit_table,*LPrefavc_VolLimit_table;
//电压变化限值表
typedef struct refavc_VolVar_table
{
	DWORD  shLimitNo;					//限值集号
	DWORD  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fMax1st;						//一级最大值
	float  fMin1st;						//一级最小值
	float  fMax2st;						//二级最大值
	float  fMin2st;						//二级最小值
	float  fMax3st;						//三级最大值
	float  fMin3st;						//三级最小值
	char  szName[64];					//名称
}refavc_VolVar_table,*LPrefavc_VolVar_table;
//无功定值表
typedef struct refavc_qSetLim_table
{
	DWORD  shLimitNo;					//约束集号
	DWORD  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fUpLimit;					//无功/功率因数高限
	float  fLowLimit;					//无功/功率因数低限
	BYTE  vlpos;						//电压侧
	char  szName[64];					//名称
}refavc_qSetLim_table,*LPrefavc_qSetLim_table;
//电压限值表
typedef struct refavc_vSetLim_table
{
	DWORD  shLimitNo;					//约束集号
	DWORD  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fUpLimit;					//电压高限
	float  fLowLimit;					//电压低限
	BYTE  vlpos;						//电压侧
	char  szName[64];					//名称
}refavc_vSetLim_table,*LPrefavc_vSetLim_table;
//优化事件表
typedef struct refavc_opfEvent_table
{
	DWORD  shEventNo;					//编号
	BYTE  byEventType;					//事件类型
	DWORD  shSourceFac;					//事件厂号
	DWORD  shSourceNo;					//事件序号
	BYTE  byYxVal;						//遥信值
	float  fChangeLimit;				//遥测变化限值绝对值
	short  shRelay;						//启动延时
	float  fLastValue;					//上次采样值
}refavc_opfEvent_table,*LPrefavc_opfEvent_table;
//优化时间表
typedef struct refavc_opfStart_table
{
	DWORD  shTimeNo;					//编号
	CTime  tStartTime;					//启动时刻
}refavc_opfStart_table,*LPrefavc_opfStart_table;
//遥测变化限值表
typedef struct refavc_opfYcLim_table
{
	DWORD  shLimitNo;					//编号
	DWORD  shYcFac;						//遥测厂号
	DWORD  shYcNo;						//遥测序号
	float  fChangeLimit;				//变化量绝对值限值
}refavc_opfYcLim_table,*LPrefavc_opfYcLim_table;
//优化参数设置表
typedef struct refavc_opfSet_table
{
	DWORD  shAutoId;					//编号
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
	DWORD  iIslandNo;					//电力岛号
	DWORD  iNodeNum;					//节点数
	DWORD  iGenNum;						//发电机数
	DWORD  iLoadNum;					//负荷数
	short  shSeTime;					//状态估计时间
	BYTE  bySeResult;					//se结果
	short  shOpfTime;					//优化计算时间
	BYTE  byOpfResult;					//opf结果
	DWORD  iMeasNum;					//估计量测点数
	DWORD  iEligibleNum;				//估计后合格点数
	char  szRefGen[200];				//平衡机
}refavc_tIsland_table,*LPrefavc_tIsland_table;
//计算节点表
typedef struct refavc_tmpNode_table
{
	DWORD  iNodeNo;						//节点号
	DWORD  iIslandNo;					//电力岛号
	DWORD  shFacNo;						//所在厂号
	DWORD  shAreaNo;					//所在区域号
	DWORD  shZoneNo;					//所在区段号
	short  byBusType;					//母线类型
	BYTE  byCtrlType;					//优化控制类型
	float  fBaseVol;					//基准电压
	float  fYcVol;						//遥测电压值
	float  fVolWeight;					//电压权值
	float  fVolStep;					//电压权值步长
	BYTE  byJPV;						//电压限制状态
	BYTE  byJPC;						//电压变化限制状态
	float  fSeVoltage;					//se电压值
	float  fSeAngle;					//se电压相角
	DWORD  shLimitNo;					//电压限制集号
	DWORD  shVarLimNo;					//无功变化限制集号
	char  Name[64];						//名称
	float  VolUpLimit;					//电压控制上限
	float  VolDnLimit;					//电压控制下限
	float  CosUpLimit;					//功率控制上限
	float  CosDnLimit;					//功率控制下限
	DWORD  SysNU;						//系统内部编号
	BYTE  IsGate;						//关口标志
}refavc_tmpNode_table,*LPrefavc_tmpNode_table;
//计算变压器表
typedef struct refavc_tmpTrans_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shMasterNo;					//主变压器号
	DWORD  iTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	float  fCapacity;					//额定容量
	float  fRateKVi;					//额定电压i
	float  fRateKVj;					//额定电压j
	float  fBaseKVi;					//基准电压i
	float  fBaseKVj;					//基准电压i
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
	float  fTapPos;						//当前档位
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
	DWORD  iFromNode;					//首端节点号
	DWORD  iToPoint;					//末端节点号
	float  fSeFromP;					//首端有功
	float  fSeFromQ;					//首端无功
	float  fSeFromI;					//首端电流
	float  fSeToP;						//末端有功
	float  fSeToQ;						//末端无功
	float  fSeToI;						//末端电流
	DWORD  iIslandNo;					//电力岛号
	char  Name[64];						//名称
	DWORD  SysNU;						//系统内部编号
	BYTE  IsGate;						//关口标志
	float  CosUpLimit;					//功率控制上限
	float  CosDnLimit;					//功率控制下限
	DWORD  Parallel;					//并联支路
}refavc_tmpTrans_table,*LPrefavc_tmpTrans_table;
//计算无功设备表
typedef struct refavc_tmpShunt_table
{
	DWORD  shFacNo;						//厂号
	DWORD  iShuntNo;					//编号
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
	DWORD  iFromNode;					//首端节点号
	DWORD  iToPoint;					//末端节点号
	float  fSeQ;						//无功估计值
	DWORD  iIslandNo;					//电力岛号
	char  Name[64];						//名称
	DWORD  SysNU;						//系统内部编号
	BYTE  IsVirtual;					//虚拟标志
}refavc_tmpShunt_table,*LPrefavc_tmpShunt_table;
//计算发电机表
typedef struct refavc_tmpGen_table
{
	DWORD  shFacNo;						//厂号
	DWORD  iGenNo;						//发电机号
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
	DWORD  iNodeNo;						//节点号
	float  fSeP;						//有功估计值
	float  fSeQ;						//无功估计值
	DWORD  iIslandNo;					//电力岛号
	char  Name[64];						//名称
	DWORD  SysNU;						//系统内部编号
}refavc_tmpGen_table,*LPrefavc_tmpGen_table;
//计算负荷表
typedef struct refavc_tmpLoad_table
{
	DWORD  shFacNo;						//厂号
	DWORD  iLoadNo;						//编号
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
	DWORD  iNodeNo;						//节点号
	float  fSeP;						//有功估计值
	float  fSeQ;						//无功估计值
	DWORD  iIslandNo;					//电力岛号
	char  Name[64];						//名称
	DWORD  SysNU;						//系统内部编号
}refavc_tmpLoad_table,*LPrefavc_tmpLoad_table;
//计算线路表
typedef struct refavc_tmpLine_table
{
	DWORD  iLineNo;						//线路号
	DWORD  shFromFac;					//首端厂号
	DWORD  shToFac;						//末端厂号
	float  fResistance;					//电阻值
	float  fReactance;					//电抗值
	float  fConductance;				//电导值
	float  fSusceptance;				//电纳值
	float  fFromCapacity;				//线路首端容量
	float  fToCapacity;					//线路末端容量
	float  fBaseKV;						//额定电压
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
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fSeFromP;					//首端有功估计
	float  fSeFromQ;					//首端无功估计
	float  fSeFromI;					//首端电流估计
	float  fSeToP;						//末端有功估计
	float  fSeToQ;						//末端无功估计
	float  fSeToI;						//末端电流估计
	DWORD  iIslandNo;					//电力岛号
	char  Name[64];						//名称
	DWORD  SysNU;						//系统内部编号
	DWORD  Parallel;					//并联支路
}refavc_tmpLine_table,*LPrefavc_tmpLine_table;
//计算母线表
typedef struct refavc_tmpBus_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shBusNo;						//母线号
	DWORD  iNodeNo;						//节点号
	short  byBusType;					//母线类型
	BYTE  byCtrlType;					//优化控制类型
	float  fBaseVol;					//基准电压
	float  fYcVol;						//遥测电压值
	float  fVolWeight;					//电压权值
	float  fVolStep;					//电压权值步长
	BYTE  byJPV;						//电压限制状态
	BYTE  byJPC;						//电压变化限制状态
	DWORD  shLimitNo;					//电压限制集号
	DWORD  shVarLimNo;					//无功变化限制集号
	char  Name[64];						//名称
	DWORD  iIslandNo;					//电力岛号
	float  VolUpLimit;					//电压控制上限
	float  VolDnLimit;					//电压控制下限
	float  CosUpLimit;					//功率控制上限
	float  CosDnLimit;					//功率控制下限
	DWORD  SysNU;						//系统内部编号
	BYTE  IsGate;						//关口标志
}refavc_tmpBus_table,*LPrefavc_tmpBus_table;
//优化计算控制信息表
typedef struct refavc_opfRes_table
{
	DWORD  shAutoId;					//编号
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
	DWORD  iNodeNo;						//节点号
	DWORD  iIslandNo;					//电力岛号
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
	DWORD  iNodeNo;						//节点号
	DWORD  iIslandNo;					//电力岛号
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
	DWORD  iLineNo;						//线路号
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fFromMW;						//线路首端有功
	float  fFromMvar;					//线路首端无功
	float  fToMW;						//线路末端有功
	float  fToMvar;						//线路末端无功
}refavc_preLine_table,*LPrefavc_preLine_table;
//优化后线路表
typedef struct refavc_postLine_table
{
	DWORD  iLineNo;						//线路号
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fFromMW;						//线路首端有功
	float  fFromMvar;					//线路首端无功
	float  fToMW;						//线路末端有功
	float  fToMvar;						//线路末端无功
}refavc_postLine_table,*LPrefavc_postLine_table;
//优化前变压器表
typedef struct refavc_preTrans_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shMasterNo;					//主变压器号
	DWORD  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
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
	DWORD  shFacNo;						//厂号
	DWORD  shMasterNo;					//主变压器号
	DWORD  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
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
	DWORD  shFacNo;						//厂号
	DWORD  shMasterNo;					//主变压器号
	DWORD  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fFromBaseVol;				//首端基准电压
	float  fToBaseVol;					//末端基准电压
	float  fPreRatio;					//优化前变比
	float  fPostRatio;					//优化后变比
}refavc_opfTrans_table,*LPrefavc_opfTrans_table;
//优化控制无功表
typedef struct refavc_opfShunt_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shShuntNo;					//编号
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fPreVar;						//优化前容量
	float  fPostVar;					//优化后容量
}refavc_opfShunt_table,*LPrefavc_opfShunt_table;
//VQC定值表
typedef struct refavc_VqcSet_table
{
	DWORD  shFacNo;						//厂号
	BYTE  byType;						//变压器类型
	DWORD  shTransNo;					//变压器号
	char  szFacName[64];				//厂站名
	char  szTransName[64];				//变压器名
	float  fHiVolSet;					//电压定值上限
	float  fLowVolSet;					//电压定值下限
	float  fHiVarSet;					//无功/功率因数定值上限
	float  fLowVarSet;					//无功/功率因数定值下限
	BYTE  byStatus;						//发送状态
}refavc_VqcSet_table,*LPrefavc_VqcSet_table;
//控制命令表
typedef struct refavc_opfCmd_table
{
	DWORD  tmOrder;						//序号
	DWORD  shFacNo;						//厂号
	BYTE  byType;						//设备类型
	DWORD  shDeviceNo;					//设备编号
	char  szFacName[64];				//厂站名
	char  szDevName[64];				//设备名
	DWORD  SwitchNU;					//开关编号
	char  YKSwitch[64];					//遥控开关
	int  YKPoint;						//遥控点号
	BYTE  byCommand;					//命令（分升/合降）
	float  shCurTap;					//当前档位
	float  shEndTap;					//目标档位
	BYTE  byStatus;						//控制状态
	CTime  CreatTime;					//创建时间
	CTime  YKTime;						//控制时间
	char  YKInfo[64];					//控制信息
	BYTE  YKState;						//遥控标识
	char  CtrlType[16];					//控制方法
}refavc_opfCmd_table,*LPrefavc_opfCmd_table;
//发电机优化表
typedef struct refavc_opfGen_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shGenNo;						//发电机号
	DWORD  iNodeNo;						//节点号
	float  fPreP;						//优化前有功
	float  fPostP;						//优化后有功
	float  fPreQ;						//优化前无功
	float  fPostQ;						//优化后无功
}refavc_opfGen_table,*LPrefavc_opfGen_table;
//发电机PQ曲线表
typedef struct refavc_genPQ_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shGenNo;						//发电机号
	DWORD  shOrderNo;					//序号
	float  fP;							//有功出力
	float  fMaxQ;						//最大无功
	float  fMinQ;						//最小无功
}refavc_genPQ_table,*LPrefavc_genPQ_table;
//母线优化结果表
typedef struct refavc_opfBus_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shBusNo;						//母线号
	char  szFacName[64];				//厂站名
	char  szBusName[64];				//母线名
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
	DWORD  iLineNo;						//线路号
	char  szName[64];					//线路名
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
	DWORD  shFacNo;						//厂号
	BYTE  byType;						//变压器类型
	DWORD  shTransNo;					//变压器号
	char  szFacName[64];				//厂站名
	char  szTransName[64];				//变压器名
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
	DWORD  shFacNo;						//厂号
	DWORD  shShuntNo;					//编号
	char  szFacName[64];				//厂站名
	char  szName[64];					//设备名
	float  fYcQ;						//无功遥测
	float  fSeQ;						//状态估计无功
	float  fOpfQ;						//优化无功
	float  fPostQ;						//控制后无功遥测
}refavc_opfWgsb_table,*LPrefavc_opfWgsb_table;
//发电机优化结果表
typedef struct refavc_opfFdj_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shGenNo;						//发电机号
	char  szFacName[64];				//厂站名
	char  szName[64];					//发电机名
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
	DWORD  iIslandNo;					//电力岛号
	BYTE  byStaType;					//估计统计类型
	BYTE  byVolDegree;					//电压等级序号
	float  fVolSeAccu;					//估计合格率
}refavc_VolSeSta_table,*LPrefavc_VolSeSta_table;
//母线电压越限表
typedef struct refavc_BusExcee_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shBusNo;						//母线号
	char  szFacName[64];				//厂站名
	char  szBusName[64];				//母线名
	float  fYcVol;						//遥测电压值
	float  fSeVol;						//状态估计电压值
	float  fOpfVol;						//优化电压值
}refavc_BusExcee_table,*LPrefavc_BusExcee_table;
//变压器损耗表
typedef struct refavc_LossByq_table
{
	DWORD  shFacNo;						//厂号
	BYTE  byType;						//变压器类型
	DWORD  shTransNo;					//变压器号
	char  szFacName[64];				//厂站名
	char  szTransName[64];				//变压器名
	float  fPrePLoss;					//优化前有功损耗
	float  fPostPLoss;					//优化后有功损耗
	float  fPreQLoss;					//优化前无功损耗
	float  fPostQLoss;					//优化后无功损耗
}refavc_LossByq_table,*LPrefavc_LossByq_table;
//线路损耗表
typedef struct refavc_LossLine_table
{
	DWORD  iLineNo;						//线路号
	char  szName[64];					//线路名
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
	DWORD  shObjectFac;					//闭锁对象厂号
	char  szFacName[64];				//闭锁对象厂名
	DWORD  shObjectNo;					//闭锁对象号
	char  szObectName[64];				//闭锁对象名
	char  szLockInfo[100];				//闭锁信息
}refavc_curLock_table,*LPrefavc_curLock_table;
//反时限控制表
typedef struct refavc_DevCtrl_table
{
	DWORD  shOrderNo;					//序号
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
	WORD  rule_no;						//规则编号
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
//控制限值表
typedef struct refavc_SetLim_table
{
	DWORD  shLimitNo;					//约束集号
	DWORD  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fVolUp;						//电压高限
	float  fVolLow;						//电压低限
	float  fVarUp;						//无功上限
	float  fVarDown;					//无功下限
	WORD  fTransNum;					//变压器可调节次数
	WORD  fShuntNum;					//电容器可调节次数
	BYTE  vlpos;						//电压侧
	char  szName[64];					//名称
	float  fBaseVol;					//基准电压
}refavc_SetLim_table,*LPrefavc_SetLim_table;
//AVC系统默认运行参数
typedef struct refavc_Avc_RunParam
{
	DWORD  NU;							//序号
	CTime  starttime;					//起始时间
	CTime  endtime;						//终止时间
	short  type;						//时段类别
	char  tyname[64];					//时段类别名称
	float  BaseVol;						//基准电压
	WORD  capnum;						//电容控制次数
	WORD  tfmnum;						//变压器控制次数
	float  GateCosup;					//关口功率上限
	float  GateCosdn;					//关口功率下限
	float  FacCosup;					//厂站功率上限
	float  FacCosdn;					//厂站功率下限
	float  Volup;						//电压上限
	float  Voldn;						//电压下限
}refavc_Avc_RunParam,*LPrefavc_Avc_RunParam;
//设备遥控信息定义表
typedef struct refavc_DevYk_table
{
	DWORD  NU;							//设备编号
	char  Name[64];						//设备名称
	BYTE  DevType;						//设备类型
	char  YKType[32];					//遥控类型
	char  YKName[64];					//遥控名称
	char  LinkSwitch[64];				//遥控开关
	DWORD  SwitchNU;					//开关编号
	DWORD  UpPoint;						//分/升点号
	DWORD  DnPoint;						//合/降点号
	BYTE  RevFlag;						//反向标识
	short  DelayTime;					//延迟时间
}refavc_DevYk_table,*LPrefavc_DevYk_table;
//系统网损日数据表
typedef struct refavc_SysPowerLoss
{
	CTime  LogTime;						//统计时间
	char  OpfType[32];					//优化方法
	float  PowerP;						//总有功
	float  PowerQ;						//总无功
	float  LoadP;						//负荷有功
	float  LoadQ;						//负荷无功
	float  ShuntQ;						//补偿无功
	float  LossP;						//有功网损
	float  LossQ;						//无功网损
	int  CtrlTfm;						//变压器控制数
	int  CtrlShunt;						//电容器控制数
	float  OpfLossP;					//有功网损
	float  OpfLossQ;					//无功网损
}refavc_SysPowerLoss,*LPrefavc_SysPowerLoss;
//=================研究库===============
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
//控制限值表
typedef struct studypw_SetLim_table
{
	DWORD  shLimitNo;					//约束集号
	DWORD  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fVolUp;						//电压高限
	float  fVolLow;						//电压低限
	float  fVarUp;						//无功上限
	float  fVarDown;					//无功下限
	WORD  fTransNum;					//变压器可调节次数
	WORD  fShuntNum;					//电容器可调节次数
	BYTE  vlpos;						//电压侧
	char  szName[64];					//名称
	float  fBaseVol;					//基准电压
}studypw_SetLim_table,*LPstudypw_SetLim_table;
//=================AVC评价信息库===============
//高软电气岛信息表
typedef struct ScadaAVC_PasIsland
{
	DWORD  NU;							//序号
	DWORD  IslandID;					//岛号
	DWORD  Station;						//平衡机厂号
	char  StaName[64];					//平衡机厂名
	DWORD  GenID;						//平衡机ID
	char  GenName[64];					//平衡机名
	DWORD  NodeNum;						//节点数
	BYTE  State;						//收敛性
	BYTE  Obisle;						//可观测性
	BYTE  BadDataP;						//有功坏数据
	BYTE  BadDataQ;						//无功坏数据
	CTime  SERunTime;					//运行时间
	CTime  LogTime;						//数据时标
}ScadaAVC_PasIsland,*LPScadaAVC_PasIsland;
//高软计算信息表
typedef struct ScadaAVC_PasRunInfo
{
	CTime  RunTime;						//运行时间
	char  RunInfo[200];					//运行信息
	CTime  LogTime;						//数据时标
}ScadaAVC_PasRunInfo,*LPScadaAVC_PasRunInfo;
//高软SE参数表
typedef struct ScadaAVC_PasSEParam
{
	BYTE  Run_State;					//当前运行状态
	BYTE  Pause_State;					//暂停计算状态
	CTime  RunTime;						//计算时间
	BYTE  Conv_State;					//当前收敛状态
	float  Measure_Rate;				//遥测覆盖率
	DWORD  CycleTime;					//运行周期(分)
	DWORD  MaxIter;						//最大迭代次数
	float  EpsP;						//有功收敛精度
	float  EpsQ1;						//无功收敛精度
	float  SE_Rate;						//当前状估合格率
	float  SE_DayRate;					//当日状估合格率
	float  SE_MonRate;					//月状估合格率
	float  SE_YearRate;					//年状估合格率
	CTime  LogTime;						//数据时标
}ScadaAVC_PasSEParam,*LPScadaAVC_PasSEParam;
//高软SE量测一览表
typedef struct ScadaAVC_PasSEMeasure
{
	DWORD  Station;						//厂站号
	DWORD  DevID;						//设备ID
	BYTE  DevType;						//设备类型
	BYTE  MeasType;						//量测类型
	BYTE  MeasPos;						//量测位置
	char  MeasInfo[64];					//量测名称
	DWORD  Island;						//岛号
	float  Meas_value;					//量测值
	float  SE_value;					//状态估计值
	float  Err_value;					//误差百分数
	float  Error;						//不合格量测
	float  BadData;						//坏数据
	float  DHisRate;					//日合格统计率
	float  MHisRate;					//月合格统计率
}ScadaAVC_PasSEMeasure,*LPScadaAVC_PasSEMeasure;
//AVC厂站信息表
typedef struct ScadaAVC_AVCStation
{
	DWORD  ID;							//厂站ID
	char  Name[64];						//厂站名称
	DWORD  Zone;						//区域ID
	BYTE  CtrlOut;						//控制退出
	BYTE  AVCCtrl;						//AVC自动控制
	DWORD  CtrlID;						//控制时段编号
	BYTE  Lock_Sta;						//厂站闭锁状态
	BYTE  DevLock_Sta;					//厂站设备闭锁状态
	float  Vol_rate;					//电压合格率
	float  Loss_P;						//有功网损
	float  Loss_Q;						//无功网损
	float  Bachup_Q;					//无功备用
	DWORD  DCtrlNum;					//日动作数
	DWORD  H24CtrlNum;					//24小时动作数
	DWORD  MCtrlNum;					//月动作数
	CTime  LogTime;						//数据时标
}ScadaAVC_AVCStation,*LPScadaAVC_AVCStation;
//AVC母线信息表
typedef struct ScadaAVC_AVCBus
{
	DWORD  BusID;						//母线ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//母线名称
	DWORD  CtrlID;						//控制时段编号
	BYTE  Ctr_Sta;						//是否控制
	BYTE  Cal_Sta;						//是否参与计算
	BYTE  Lock_Sta;						//闭锁状态
	BYTE  IsGate;						//关口标识
	float  Volup;						//电压上限
	float  Voldn;						//电压下限
	float  Cosup;						//功率上限
	float  Cosdn;						//功率下限
	float  DVol_rate;					//日电压合格率
	float  H24Vol_rate;					//24小时电压合格率
	float  MVol_rate;					//月电压合格率
	float  DCos_rate;					//日无功合格率
	float  H24Cos_rate;					//24小时无功合格率
	float  MCos_rate;					//月无功合格率
	CTime  LogTime;						//数据时标
}ScadaAVC_AVCBus,*LPScadaAVC_AVCBus;
//AVC变压器信息表
typedef struct ScadaAVC_AVCTrans
{
	DWORD  ID;							//变压器ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//变压器名称
	DWORD  CtrlID;						//控制时段ID
	BYTE  Cal_Sta;						//参与计算标识
	BYTE  Lock_Sta;						//闭锁标识
	short  LimitNumber;					//控制次数限制
	DWORD  UpYXID;						//升档遥信ID
	DWORD  UpYKNO;						//升档遥控点号
	DWORD  DnYXID;						//降档遥信ID
	DWORD  DnYKNO;						//降档遥控点号
	DWORD  LinkBusID;					//关联母线ID
	BYTE  IsGate;						//关口变压器
	DWORD  DCtrlNum;					//日控制次数
	DWORD  DAVCCtrlNum;					//日AVC控制次数
	DWORD  DAVCActNum;					//日AVC动作次数
	DWORD  H24CtrlNum;					//24小时控制次数
	DWORD  H24AVCCtrlNum;				//24小时AVC控制次数
	DWORD  H24AVCActNum;				//24小时AVC动作次数
	DWORD  MCtrlNum;					//月控制次数
	DWORD  MAVCCtrlNum;					//月AVC控制次数
	DWORD  MAVCActNum;					//月AVC动作次数
	DWORD  YCtrlNum;					//年控制次数
	DWORD  YAVCCtrlNum;					//年AVC控制次数
	DWORD  YAVCActNum;					//年AVC动作次数
	CTime  LogTime;						//数据时标
}ScadaAVC_AVCTrans,*LPScadaAVC_AVCTrans;
//AVC无功设备信息表
typedef struct ScadaAVC_AVCShunt
{
	DWORD  ID;							//电容ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//电容名称
	DWORD  CtrlID;						//控制时段ID
	BYTE  Cal_Sta;						//参与计算
	BYTE  Lock_Sta;						//闭锁状态
	WORD  LimitNum;						//动作次数限制
	DWORD  YXID;						//遥信ID
	DWORD  YKNO;						//遥控点号
	DWORD  BusID;						//控制母线ID
	DWORD  BreakID;						//控制开关ID
	DWORD  DCtrlNum;					//日动作数量
	DWORD  DAVCCtrlNum;					//日AVC控制数量
	DWORD  DAVCActNum;					//日AVC动作数量
	DWORD  H24CtrlNum;					//24小时动作数量
	DWORD  H24AVCCtrlNum;				//24小时AVC控制数量
	DWORD  H24AVCActNum;				//24小时AVC动作数量
	DWORD  MCtrlNum;					//月动作数量
	DWORD  MAVCCtrlNum;					//月AVC控制数量
	DWORD  MAVCActNum;					//月AVC动作数量
	DWORD  YCtrlNum;					//年动作数量
	DWORD  YAVCCtrlNum;					//年AVC控制数量
	DWORD  YAVCActNum;					//年AVC动作数量
	DWORD  DRunTime;					//日运行时长
	DWORD  H24RunTime;					//24小时运行时长
	DWORD  MRunTime;					//月运行时长
	DWORD  YRunTime;					//年运行时长
	CTime  LogTime;						//数据时标
}ScadaAVC_AVCShunt,*LPScadaAVC_AVCShunt;
//AVC区域信息表
typedef struct ScadaAVC_AVCZone
{
	DWORD  ID;							//区域编号
	char  Name[120];					//区域名称
	float  Vol_rate;					//电压合格率
	float  Cos_rate;					//无功合格率
	double  Loss_P;						//有功降损总计
	double  Loss_Q;						//无功降损总计
	DWORD  Shunt_Ctrl;					//无功控制数
	DWORD  Trans_Ctrl;					//变压器控制数
	float  H24Vol_rate;					//24小时电压合格率
	float  H24Cos_rate;					//24小时无功合格率
	float  H24LossP_rate;				//24小时有功网损率
	float  H24LossQ_rate;				//24小时无功网损率
	DWORD  H24Shunt_Ctrl;				//24小时无功控制数
	DWORD  H24Trans_Ctrl;				//24小时变压器控制数
	float  MVol_rate;					//月电压合格率
	float  MCos_rate;					//月无功合格率
	float  MLossP_rate;					//月有功网损率
	float  MLossQ_rate;					//月无功网损率
	DWORD  MShunt_Ctrl;					//月无功控制数
	DWORD  MTrans_Ctrl;					//月变压器控制数
	float  YVol_rate;					//年电压合格率
	float  YCos_rate;					//年无功合格率
	float  YLossP_rate;					//年有功网损率
	float  YLossQ_rate;					//年无功网损率
	DWORD  YShunt_Ctrl;					//年无功控制数
	DWORD  YTrans_Ctrl;					//年变压器控制数
	CTime  LogTime;						//数据时标
}ScadaAVC_AVCZone,*LPScadaAVC_AVCZone;
//AVC运行参数信息表
typedef struct ScadaAVC_AVCCtrRunParam
{
	CTime  DateLog;						//系统运行日志时间
	char  SysInfo[24];					//系统信息
	char  RunMsg[64];					//运行信息
	DWORD  RunNum;						//运行次数
	CTime  StartTime;					//启动时间
	CTime  AvcTime;						//AVC结束时间
	BYTE  Run_Sta;						//运行状态
	BYTE  Auto_Sta;						//自动控制状态
	BYTE  Quit_Sta;						//程序退出状态
	BYTE  Cmd_Sta;						//命令下发状态
	BYTE  Remote_Sta;					//远动状态
	BYTE  Enable_Sta;					//AVC可用标志
	WORD  Cycvol;						//采样周期
	int  Ctrlmtd;						//控制算法
	BYTE  Ctrl_CP;						//电容控制状态
	BYTE  Ctrl_Cos;						//区域无功控制状态
	BYTE  Ctrl_Vol;						//区域电压控制状态
	WORD  Xfre_space;					//主变调档时间间隔
	WORD  CPOut_space;					//电容投入退出时间间隔
	WORD  CPIn_space;					//电容退出投入时间间隔
	WORD  Zone_space;					//区域控制时间间隔
	float  Xfr_overload;				//主变过载系数
	float  AvcUse_Rate;					//AVC可用率
	DWORD  AvcClosedTime;				//AVC闭环运行时长
	DWORD  CtrlNum;						//AVC控制指令数
	DWORD  CtrlSucNum;					//AVC控制成功数
	float  CtrlSuc_Rate;				//AVC控制成功率
	DWORD  MaxCtrlNum;					//最大可动设备数
	DWORD  CP_RefuseNum;				//容抗拒动次数
	DWORD  XF_RefuseNum;				//变压器拒动次数
	float  lossdec;						//日降损量
}ScadaAVC_AVCCtrRunParam,*LPScadaAVC_AVCCtrRunParam;
//AVC时段定义表
typedef struct ScadaAVC_AVCTimePart
{
	DWORD  ID;							//序号
	char  Name[64];						//时段名称
	float  VUp1;						//电压上限1
	float  VDn1;						//电压下限1
	float  CP_Num1;						//电容可控次数1
	float  XF_Num1;						//变压器可控次数1
	float  CosUp1;						//功率因数上限1
	float  CosDn1;						//功率因数下限1
	CTime  Tm1;							//时段1分割点
	float  VUp2;						//电压上限2
	float  VDn2;						//电压下限2
	float  CP_Num2;						//电容可控次数2
	float  XF_Num2;						//变压器可控次数2
	float  CosUp2;						//功率因数上限2
	float  CosDn2;						//功率因数下限2
	CTime  Tm2;							//时段2分割点
	float  VUp3;						//电压上限3
	float  VDn3;						//电压下限3
	float  CP_Num3;						//电容可控次数3
	float  XF_Num3;						//变压器可控次数3
	float  CosUp3;						//功率因数上限3
	float  CosDn3;						//功率因数下限3
	CTime  Tm3;							//时段3分割点
	float  VUp4;						//电压上限4
	float  VDn4;						//电压下限4
	float  CP_Num4;						//电容可控次数4
	float  XF_Num4;						//变压器可控次数4
	float  CosUp4;						//功率因数上限4
	float  CosDn4;						//功率因数下限4
	CTime  Tm4;							//时段4分割点
	float  VUp5;						//电压上限5
	float  VDn5;						//电压下限5
	float  CP_Num5;						//电容可控次数5
	float  XF_Num5;						//变压器可控次数5
	float  CosUp5;						//功率因数上限5
	float  CosDn5;						//功率因数下限5
	CTime  Tm5;							//时段1分割点
	float  VUp6;						//电压上限6
	float  VDn6;						//电压下限6
	float  CP_Num6;						//电容可控次数6
	float  XF_Num6;						//变压器可控次数6
	float  CosUp6;						//功率因数上限6
	float  CosDn6;						//功率因数下限6
	CTime  LogTime;						//数据时标
}ScadaAVC_AVCTimePart,*LPScadaAVC_AVCTimePart;
//AVC告警类型表
typedef struct ScadaAVC_AVCWarnType
{
	DWORD  KeyID;						//序号
	DWORD  ID;							//告警ID
	char  TypeName[24];					//告警名称
	short  ot;							//告警设备类型
	char  txt[32];						//告警内容
	BYTE  qskip;						//抑止告警标志
	BYTE  qlock;						//闭锁复归方式
	BYTE  qsend;						//告警发送标志
	int  deltm;							//复归延时时间
}ScadaAVC_AVCWarnType,*LPScadaAVC_AVCWarnType;
//AVC告警定义表
typedef struct ScadaAVC_AVCWarnInfo
{
	DWORD  StationID;					//厂站ID
	DWORD  DevID;						//设备ID
	DWORD  WarnID;						//告警类型ID
	BYTE  qlock;						//闭锁复归方式
	BYTE  stat;							//闭锁状态
	WORD  almtype;						//告警类型
	CTime  ontm;						//动作时间
	CTime  offtm;						//复归时间
	BYTE  IsDone;						//处理标志
}ScadaAVC_AVCWarnInfo,*LPScadaAVC_AVCWarnInfo;
//AVC保护定义表
typedef struct ScadaAVC_AVCRelayInfo
{
	DWORD  StationID;					//厂站ID
	DWORD  RelayID;						//保护ID
	BYTE  state;						//保护状态
	short  qlock;						//闭锁复归方式
	DWORD  DevId;						//关联设备ID
	CTime  OnTm;						//动作时间
	CTime  OffTm;						//复归时间
	BYTE  IsDone;						//处理标志
}ScadaAVC_AVCRelayInfo,*LPScadaAVC_AVCRelayInfo;
//AVC控制策略表
typedef struct ScadaAVC_AVCCtrlCmd
{
	DWORD  KeyID;						//序号
	CTime  LogTime;						//策略时间
	char  DevName[64];					//设备名称
	DWORD  StationID;					//厂站ID
	DWORD  DevID;						//设备ID
	DWORD  DevSub;						//控制设备下标
	CTime  IssTm;						//发送时刻
	CTime  CmdTm;						//执行时刻
	char  cause_info[80];				//控制原因
	char  result_info[80];				//措施
	char  Cmd_info[120];				//命令描述
	char  CmdType[8];					//命令类型
	short  CtrlType;					//操作类型
	char  rslttype[12];					//处理状态
	BYTE  qcheck;						//命令确认
	BYTE  qaut;							//自控命令
	DWORD  seq;							//命令编号
	DWORD  ZoneID;						//责任区ID
	DWORD  resp;						//责任区
}ScadaAVC_AVCCtrlCmd,*LPScadaAVC_AVCCtrlCmd;
//AVC控制区域表
typedef struct ScadaAVC_AVCCtrlZone
{
	DWORD  KeyID;						//序号
	char  Name[64];						//区域名称
	DWORD  VovNum;						//电压考核越限数
	DWORD  QovNum;						//无功考核越限数
	float  wloss;						//区域网损值
	DWORD  NormCp;						//可控电容数
	DWORD  NormXf;						//可控变压器数
	DWORD  LockCp;						//闭锁电容数
	DWORD  LockXf;						//闭锁变压器数
	float  VarIn;						//已投入无功总容量
	float  VarOff;						//未投入无功总容量
	float  Cosfi;						//关口功率因数
	float  score;						//区域状态得分
	CTime  LogTime;						//数据时标
}ScadaAVC_AVCCtrlZone,*LPScadaAVC_AVCCtrlZone;
//AVC区域交换表
typedef struct ScadaAVC_AVCAreaChange
{
	DWORD  KeyID;						//序号
	DWORD  objtype;						//对象类型
	DWORD  objID;						//对象ID
	DWORD  objcdID;						//对象测点ID
	float  value;						//对象值
	DWORD  datdir;						//数据传输方向
}ScadaAVC_AVCAreaChange,*LPScadaAVC_AVCAreaChange;
//AVC操作事件表
typedef struct ScadaAVC_AVCCtrlEvent
{
	DWORD  KeyID;						//序号
	char  user[24];						//用户名
	CTime  CmdTime;						//操作时刻
	char  opefunc[64];					//操作项
	char  text[120];					//操作内容
}ScadaAVC_AVCCtrlEvent,*LPScadaAVC_AVCCtrlEvent;
//AVC电压越限事件表
typedef struct ScadaAVC_AVCVoltEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//站名
	DWORD  BusID;						//母线ID
	char  BusName[64];					//母线名称
	float  val;							//电压值
	float  limit;						//电压限值
	CTime  EventTime;					//事件时间
}ScadaAVC_AVCVoltEvent,*LPScadaAVC_AVCVoltEvent;
//AVC变压器控制事件表
typedef struct ScadaAVC_AVCTransEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//厂站名称
	DWORD  TransID;						//变压器ID
	char  TransName[64];				//变压器名称
	DWORD  WindID;						//控制绕组ID
	CTime  Optime;						//操作时间
	WORD  pretap;						//操作前档位
	WORD  afttap;						//操作后档位
	float  preVol;						//操作前电压
	float  aftVol;						//操作后电压
	char  opttype[8];					//命令类型
	BYTE  qAVC;							//AVC命令标志
	float  preHVol;						//控制前高压电压
	float  preHP;						//控制前高压有功
	float  preHQ;						//控制前高压无功
	float  preMVol;						//控制前中压电压
	float  preMP;						//控制前中压有功
	float  preMQ;						//控制前中压无功
	float  preLVol;						//控制前低压电压
	float  preLP;						//控制前低压有功
	float  preLQ;						//控制前低压无功
	float  aftHVol;						//控制后高压电压
	float  aftHP;						//控制后高压有功
	float  aftHQ;						//控制后高压无功
	float  aftMVol;						//控制后中压电压
	float  aftMP;						//控制后中压有功
	float  aftMQ;						//控制后中压无功
	float  aftLVol;						//控制后低压电压
	float  aftLP;						//控制后低压有功
	float  aftLQ;						//控制后低压无功
	CTime  EventTime;					//事件时间
}ScadaAVC_AVCTransEvent,*LPScadaAVC_AVCTransEvent;
//AVC电容控制事件表
typedef struct ScadaAVC_AVCShuntEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//厂站名称
	DWORD  ShuntID;						//电容ID
	char  ShuntName[64];				//电容名称
	CTime  opttime;						//操作时间
	char  opttype[8];					//命令类型
	BYTE  qavc;							//AVC指令标志
	BYTE  qopen;						//操作后运行状态
	float  preVol;						//操作前电压
	float  aftVol;						//操作后电压
	CTime  EventTime;					//事件时间
}ScadaAVC_AVCShuntEvent,*LPScadaAVC_AVCShuntEvent;
//AVC统计信息表
typedef struct ScadaAVC_AVCStateInfo
{
	DWORD  KeyID;						//序号
	DWORD  DevID;						//设备ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//设备名称
	DWORD  numall;						//日动作次数
	DWORD  numavc;						//日成功次数
	DWORD  numorder;					//日下令次数
	DWORD  numfail;						//日失败次数
	float  sucrate;						//日成功数
	CTime  timelog;						//日期时标
}ScadaAVC_AVCStateInfo,*LPScadaAVC_AVCStateInfo;
//高软厂站表
typedef struct ScadaAVC_PasStation
{
	DWORD  ID;							//厂站ID
	char  Name[64];						//厂站名称
	DWORD  IsLand;						//岛号
	CTime  SERunTime;					//状估运行时间
	BYTE  Error_sta;					//不合格量测标志
	BYTE  Bad_sta;						//坏数据标志
	float  Se_rate;						//量测合格率
}ScadaAVC_PasStation,*LPScadaAVC_PasStation;
//AVC运行参数表
typedef struct ScadaAVC_AVCRunParam
{
	DWORD  ID;							//序号
	CTime  srttm;						//开始时间
	CTime  endtm;						//结束时间
	WORD  Type;							//时段类型
	char  Msg[32];						//时段描述
	WORD  CPNum;						//电容可用次数
	WORD  XfrNum;						//变压器可用次数
	float  CosUp;						//关口功率因数上限
	float  CosDn;						//关口功率因数下限
	float  SCosUp;						//厂站功率因数上限
	float  SCosDn;						//厂站功率因数下限
	float  V6Up;						//6KV上限
	float  V6Dn;						//6KV下限
	float  V10Up;						//10KV上限
	float  V10Dn;						//10KV下限
	float  V35Up;						//35KV上限
	float  V35Dn;						//35KV下限
	float  V110Up;						//110KV上限
	float  V110Dn;						//110KV下限
	float  V220Up;						//220KV上限
	float  V220Dn;						//220KV下限
	float  V330Up;						//330KV上限
	float  V330Dn;						//330KV下限
	CTime  LogTime;						//数据时标
}ScadaAVC_AVCRunParam,*LPScadaAVC_AVCRunParam;
//=================过程数据库===============
//站
typedef struct ProcessData_Station
{
	DWORD  NU;							//站号
	char  Name[64];						//站名
	DWORD  zoneNU;						//所属区域
	float  VL;							//电压等级
	int  Type;							//厂站类型
	DWORD  CtrlType;					//控制类型定义
	short  SeData;						//状态估计可疑数据
	short  CtrlNum;						//优化控制数量
	WORD  CtrlSta;						//控制状态按位标注
}ProcessData_Station,*LPProcessData_Station;
//区域
typedef struct ProcessData_Zone
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
}ProcessData_Zone,*LPProcessData_Zone;
//发电机
typedef struct ProcessData_Gen
{
	DWORD  NU;							//发电机号
	char  Name[64];						//发电机名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  MaxP;						//有功上限
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	DWORD  Node;						//节点
	float  VL;							//电压等级
	BYTE  Isbalance;					//平衡机
	WORD  Island;						//电气岛
	float  P;							//有功出力
	float  Q;							//无功出力
	float  SeP;							//有功出力
	float  SeQ;							//无功出力
	float  OpfP;						//有功出力
	float  OpfQ;						//无功出力
}ProcessData_Gen,*LPProcessData_Gen;
//母线
typedef struct ProcessData_Bus
{
	DWORD  NU;							//母线编号
	char  Name[64];						//母线名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  MaxV;						//电压上限
	float  MinV;						//电压下限
	float  Vl;							//电压等级
	float  V;							//节点电压(pu)
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	DWORD  Node;						//节点
	DWORD  cNode;						//合并节点
	WORD  Island;						//电气岛
	float  Vb;							//电压
	float  deg;							//相角
	float  SeVb;						//电压
	float  Sedeg;						//相角
	float  OpfVb;						//电压
	float  Opfdeg;						//相角
	WORD  CtrlSta;						//控制状态按位标注
}ProcessData_Bus,*LPProcessData_Bus;
//负荷
typedef struct ProcessData_Load
{
	DWORD  NU;							//负荷编号
	char  Name[64];						//负荷名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	DWORD  Node;						//节点
	float  VL;							//电压等级
	short  status;						//综合状态
	WORD  Island;						//电气岛
	float  P;							//有功负荷
	float  Q;							//无功负荷
	float  I;							//电流
	float  SeP;							//有功负荷
	float  SeQ;							//无功负荷
	float  OpfP;						//有功负荷
	float  OpfQ;						//无功负荷
}ProcessData_Load,*LPProcessData_Load;
//交流线
typedef struct ProcessData_Line
{
	DWORD  NU;							//交流线编号
	char  Name[64];						//交流线名称
	DWORD  Stationf;					//首端站
	DWORD  Stationt;					//末端站
	float  MaxP;						//有功上限
	float  VL;							//电压等级
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	DWORD  NodeF;						//首节点
	DWORD  NodeT;						//末节点
	BYTE  EquiSta;						//等值状态
	WORD  Island;						//电气岛
	float  Pf;							//始端有功
	float  Qf;							//始端无功
	float  Pt;							//末端有功
	float  Qt;							//末端无功
	float  I;							//电流值
	float  SePf;						//始端有功
	float  SeQf;						//始端无功
	float  SePt;						//末端有功
	float  SeQt;						//末端无功
	float  SeI;							//电流值
	float  OpfPf;						//始端有功
	float  OpfQf;						//始端无功
	float  OpfPt;						//末端有功
	float  OpfQt;						//末端无功
	float  OpfI;						//电流值
}ProcessData_Line,*LPProcessData_Line;
//2绕组变压器
typedef struct ProcessData_Tfm1
{
	DWORD  NU;							//2绕变编号
	char  Name[64];						//2绕变名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  tap;							//变压器分接头
	float  Pmax;						//变压器最大有功(容量)
	float  P;							//高压侧有功
	float  Q;							//高压侧无功
	float  I;							//高压侧电流
	float  P2;							//低压侧有功
	float  Q2;							//低压侧无功
	float  I2;							//低压侧电流
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	DWORD  NodeH;						//高压节点
	DWORD  NodeL;						//低压节点
	float  VL;							//电压等级
	BYTE  IsGate;						//关口
	int  Island;						//电气岛
	float  CosDn;						//功率因数下限
	float  CosUp;						//功率因数上限
	float  SeP;							//高压侧有功
	float  SeQ;							//高压侧无功
	float  SeP2;						//低压侧有功
	float  SeQ2;						//低压侧无功
	float  Setap;						//变压器分接头
	float  OpfP;						//高压侧有功
	float  OpfQ;						//高压侧无功
	float  OpfP2;						//低压侧有功
	float  OpfQ2;						//低压侧无功
	float  Opftap;						//变压器分接头
	WORD  CtrlSta;						//控制状态按位标注
}ProcessData_Tfm1,*LPProcessData_Tfm1;
//3绕组变压器
typedef struct ProcessData_Tfm2
{
	DWORD  NU;							//3绕变编号
	char  Name[64];						//3绕变名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  TapH;						//变压器分接头
	float  TapM;						//中端分接头位置
	float  Pmax;						//变压器最大有功(容量)
	float  P;							//高压侧有功
	float  Q;							//高压侧无功
	float  I;							//高压侧电流
	float  P2;							//中压侧有功
	float  Q2;							//中压侧无功
	float  I2;							//中压侧电流
	float  P3;							//低压侧有功
	float  Q3;							//低压侧无功
	float  I3;							//低压侧电流
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[24];						//标识
	DWORD  NodeH;						//高压节点
	DWORD  NodeM;						//中压节点
	DWORD  NodeL;						//低压节点
	float  VL;							//电压等级
	BYTE  IsGate;						//关口
	int  Island;						//电气岛
	float  CosDn;						//功率因数下限
	float  CosUp;						//功率因数上限
	float  SeP;							//高压侧有功
	float  SeQ;							//高压侧无功
	float  SeP2;						//中压侧有功
	float  SeQ2;						//中压侧无功
	float  SeP3;						//低压侧有功
	float  SeQ3;						//低压侧无功
	float  SeTapH;						//变压器分接头
	float  SeTapM;						//中端分接头位置
	float  OpfP;						//高压侧有功
	float  OpfQ;						//高压侧无功
	float  OpfP2;						//中压侧有功
	float  OpfQ2;						//中压侧无功
	float  OpfP3;						//低压侧有功
	float  OpfQ3;						//低压侧无功
	float  OpfTapH;						//变压器分接头
	float  OpfTapM;						//中端分接头位置
	WORD  CtrlSta;						//控制状态按位标注
}ProcessData_Tfm2,*LPProcessData_Tfm2;
//电容
typedef struct ProcessData_Shunt
{
	DWORD  NU;							//电容设备编号
	char  Name[64];						//电容设备名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  RVol;						//额定电压
	float  Qmax;						//最大无功输出
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	float  VL;							//电压等级
	short  status;						//综合状态
	WORD  Island;						//电气岛
	float  Q;							//投入无功
	float  I;							//电流
	float  SeQ;							//投入无功
	float  SeI;							//电流
	float  OpfQ;						//投入无功
	float  OpfI;						//电流
	WORD  CtrlSta;						//控制状态按位标注
}ProcessData_Shunt,*LPProcessData_Shunt;
//电抗
typedef struct ProcessData_Sreact
{
	DWORD  NU;							//电抗器变号
	char  Name[64];						//电抗器名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[24];						//标识
	DWORD  Node1;						//节点1
	DWORD  Node2;						//节点2
	float  VL;							//电压等级
	short  status;						//综合状态
	float  RVol;						//额定电压
	float  Qmax;						//最大无功输出
	float  Q;							//投入电抗
	float  I;							//电流
	float  SeQ;							//投入电抗
	float  SeI;							//电流
	float  OpfQ;						//投入电抗
	float  OpfI;						//电流
	WORD  CtrlSta;						//控制状态按位标注
}ProcessData_Sreact,*LPProcessData_Sreact;
//变压器绕组
typedef struct ProcessData_Winding
{
	DWORD  NU;							//绕组编号
	char  Name[64];						//名称
	char  ID[24];						//绕组标识
	char  TID[24];						//变压器标识
	float  baseKV;						//基准电压
	float  ratedKV;						//额定电压
	float  ratedMVA;					//额定容量
	float  fR;							//电阻
	float  fX;							//电抗
	float  fB;							//电纳
	BYTE  Type;							//绕组类型
	BYTE  Tmax;							//最大档位
	BYTE  Tmin;							//最小档位
	BYTE  Tnor;							//正常档位
	float  step;						//档位步长
	float  P;							//有功功率
	float  Q;							//无功功率
	short  Tap;							//档位
	float  SeP;							//有功功率
	float  SeQ;							//无功功率
	short  SeTap;						//档位
	float  OpfP;						//有功功率
	float  OpfQ;						//无功功率
	short  OpfTap;						//档位
}ProcessData_Winding,*LPProcessData_Winding;
//系统网损日数据表
typedef struct ProcessData_SysPowerLoss
{
	CTime  LogTime;						//统计时间
	BYTE  IsToDay;						//是否当日数据
	float  PowerP;						//总有功
	float  PowerQ;						//总无功
	float  LoadP;						//负荷有功
	float  LoadQ;						//负荷无功
	float  ShuntQ;						//补偿无功
	float  LossP;						//有功网损
	float  LossQ;						//无功网损
	float  OpfPowerP;					//总有功
	float  OpfPowerQ;					//总无功
	float  OpfLoadP;					//负荷有功
	float  OpfLoadQ;					//负荷无功
	float  OpfShuntQ;					//补偿无功
	float  OpfLossP;					//有功网损
	float  OpfLossQ;					//无功网损
}ProcessData_SysPowerLoss,*LPProcessData_SysPowerLoss;
//开关刀闸
typedef struct ProcessData_Switch
{
	DWORD  NU;							//开关编号
	char  Name[64];						//开关名字
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
}ProcessData_Switch,*LPProcessData_Switch;
//控制命令表
typedef struct ProcessData_opfCmd
{
	DWORD  tmOrder;						//序号
	DWORD  shFacNo;						//厂号
	BYTE  byType;						//设备类型
	DWORD  shDeviceNo;					//设备编号
	char  szFacName[64];				//厂站名
	char  szDevName[64];				//设备名
	DWORD  SwitchNU;					//开关编号
	char  YKSwitch[64];					//遥控开关
	int  YKPoint;						//遥控点号
	BYTE  byCommand;					//命令（分升/合降）
	float  shCurTap;					//当前档位
	float  shEndTap;					//目标档位
	BYTE  byStatus;						//控制状态
	CTime  CreatTime;					//创建时间
	CTime  YKTime;						//控制时间
	char  YKInfo[64];					//控制信息
	BYTE  YKState;						//遥控标识
	char  CtrlType[16];					//控制方法
}ProcessData_opfCmd,*LPProcessData_opfCmd;
//=================AVC评价库===============
//高软SE参数表
typedef struct AssessAVC_PasSEParam
{
	CTime  RunTime;						//计算时间
	BYTE  Conv_State;					//当前收敛状态
	float  Measure_Rate;				//遥测覆盖率
	float  SE_Rate;						//当前状估合格率
	char  RunInfo[86];					//运行信息
}AssessAVC_PasSEParam,*LPAssessAVC_PasSEParam;
//AVC厂站信息表
typedef struct AssessAVC_AVCStation
{
	DWORD  ID;							//厂站ID
	char  Name[64];						//厂站名称
	DWORD  Zone;						//区域ID
	BYTE  CtrlOut;						//控制退出
	BYTE  AVCCtrl;						//AVC自动控制
	DWORD  CtrlID;						//控制时段编号
	WORD  Lock_Num;						//厂站闭锁当日累计
	DWORD  DevLock_Num;					//厂站设备闭锁当日累计
	float  VL;							//电压等级
	float  DVolRate;					//当日电压合格率
	float  DCosRate;					//当日功率因数合格率
	DWORD  DVAll_Time;					//日电压总时长
	DWORD  DVOut_Time;					//日电压越限时长
	DWORD  DCAll_Time;					//日功率总时长
	DWORD  DCOut_Time;					//日功率越限时长
	float  H24VolRate;					//24小时电压合格率
	float  H24CosRate;					//24小时功率合格率
	DWORD  H24VAll_Time;				//日电压总时长
	DWORD  H24VOut_Time;				//日电压越限时长
	DWORD  H24CAll_Time;				//日功率总时长
	DWORD  H24COut_Time;				//日功率越限时长
	DWORD  DActNum;						//日动作数
	DWORD  DAvcCtrlNum;					//日AVC控制数
	DWORD  DAvcActNum;					//日AVC动作数
	DWORD  H24ActNum;					//24小时动作数
	DWORD  H24AvcCtrlNum;				//日AVC控制数
	DWORD  H24AvcActNum;				//日AVC动作数
	CTime  LogTime;						//数据时标
}AssessAVC_AVCStation,*LPAssessAVC_AVCStation;
//AVC母线信息表
typedef struct AssessAVC_AVCBus
{
	DWORD  BusID;						//母线ID
	DWORD  ZoneID;						//区域ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//母线名称
	float  VL;							//电压等级
	DWORD  CtrlID;						//控制时段编号
	BYTE  IsGate;						//关口标识
	BYTE  Run_Sta;						//运行状态
	BYTE  Ctr_Sta;						//是否控制
	BYTE  Cal_Sta;						//是否参与计算
	BYTE  Limit_Sta;					//越限状态
	BYTE  Lock_Sta;						//闭锁状态
	float  Volup;						//电压上限
	float  Voldn;						//电压下限
	float  Cosup;						//功率上限
	float  Cosdn;						//功率下限
	WORD  DLock_Num;					//闭锁当日累计
	WORD  DLock_Time;					//闭锁当日累计时间
	float  DVolmax;						//日电压
	float  DVolmin;						//日电压
	float  DLoadP;						//母线负荷有功
	float  DLoadQ;						//母线负荷无功
	WORD  DVolOutNum;					//越限次数
	WORD  DVolEvent;					//越限事件数
	WORD  DCtrlEvent;					//控制事件数
	float  DVol_rate;					//日电压合格率
	DWORD  DAll_Time;					//日总时长
	DWORD  DOut_Time;					//日越限时长
	WORD  H24Lock_Num;					//闭锁上日累计
	WORD  H24Lock_Time;					//闭锁上日累计时间
	float  H24Volmax;					//日电压
	float  H24Volmin;					//日电压
	int  H24VolEvent;					//越限事件数
	int  H24CtrlEvent;					//控制事件数
	float  H24Vol_rate;					//24小时电压合格率
	DWORD  H24All_Time;					//24小时总时长
	DWORD  H24Out_Time;					//24小时越限时长
	CTime  LogTime;						//当前数据时标
}AssessAVC_AVCBus,*LPAssessAVC_AVCBus;
//AVC变压器信息表
typedef struct AssessAVC_AVCTrans
{
	DWORD  ID;							//变压器ID
	DWORD  ZoneID;						//区域ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//变压器名称
	DWORD  CtrlID;						//控制时段ID
	BYTE  Run_Sta;						//运行状态
	BYTE  Ctrl_Sta;						//参与控制标识
	BYTE  Lock_Sta;						//闭锁状态
	BYTE  Limit_Sta;					//越限状态
	DWORD  BusHID;						//高压母线ID
	DWORD  BusMID;						//中压母线ID
	DWORD  BusLID;						//低压母线ID
	BYTE  IsGate;						//关口变压器
	float  Cosup;						//功率上限
	float  Cosdn;						//功率下限
	WORD  DCtrlLimitNum;				//控制限值次数
	WORD  DTimeLimitNum;				//当前时段限值次数
	float  DHiP;						//高压有功
	float  DHiQ;						//高压无功
	float  DMaxS;						//日最高负载
	float  DCosRate;					//功率因数合格率
	WORD  DLock_Num;					//闭锁次数
	WORD  DLock_Time;					//闭锁当日累计时间
	float  DAll_Time;					//总时长
	float  DOut_Time;					//总时长
	DWORD  DActNum;						//日控制次数
	DWORD  DAVCCtrlNum;					//日AVC控制次数
	DWORD  DAVCActNum;					//日AVC动作次数
	WORD  H24CtrlLimit;					//日控制限值次数
	float  H24CosRate;					//24小时功率因数合格率
	float  H24MaxS;						//日最高负载
	float  H24All_Time;					//总时长
	float  H24Out_Time;					//总时长
	WORD  H24Lock_Num;					//闭锁次数
	WORD  H24Lock_Time;					//闭锁当日累计时间
	DWORD  H24ActNum;					//24小时控制次数
	DWORD  H24AVCCtrlNum;				//24小时AVC控制次数
	DWORD  H24AVCActNum;				//24小时AVC动作次数
	CTime  LogTime;						//数据时标
}AssessAVC_AVCTrans,*LPAssessAVC_AVCTrans;
//AVC无功设备信息表
typedef struct AssessAVC_AVCShunt
{
	DWORD  ID;							//电容ID
	DWORD  ZoneID;						//厂站ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//电容名称
	float  VL;							//电压等级
	DWORD  CtrlID;						//控制时段ID
	BYTE  Run_Sta;						//运行状态
	BYTE  Ctrl_Sta;						//控制状态
	BYTE  Lock_Sta;						//闭锁状态
	DWORD  BreakerID;					//开关ID
	DWORD  BusID;						//控制母线ID
	DWORD  BreakID;						//控制开关ID
	WORD  DayLimitNum;					//动作次数限制
	WORD  TimeLimitNum;					//时段限制次数
	BYTE  DLock_Num;					//闭锁次数
	BYTE  DLock_Time;					//闭锁时间
	DWORD  DActNum;						//日动作数量
	DWORD  DAVCCtrlNum;					//日AVC控制数量
	DWORD  DAVCActNum;					//日AVC动作数量
	DWORD  DRunTime;					//日运行时长
	float  DAll_Time;					//总时长
	DWORD  H24ActNum;					//24小时动作数量
	DWORD  H24AVCCtrlNum;				//24小时AVC控制数量
	DWORD  H24AVCActNum;				//24小时AVC动作数量
	WORD  H24LimitNum;					//动作次数限制
	DWORD  H24RunTime;					//24小时运行时长
	float  H24All_Time;					//总时长
	BYTE  H24Lock_Num;					//闭锁次数
	BYTE  H24Lock_Time;					//闭锁时间
	CTime  LogTime;						//数据时标
}AssessAVC_AVCShunt,*LPAssessAVC_AVCShunt;
//AVC系统统计表
typedef struct AssessAVC_AVCSystem
{
	CTime  SysTime;						//统计时间
	char  Name[120];					//区域名称
	BYTE  AVCAll_Time;					//AVC运行总时长
	BYTE  AVCOut_Time;					//AVC退出时长
	BYTE  AVCOpen_Time;					//AVC控制退出时长
	float  AvcUse_Rate;					//AVC可用率
	DWORD  Vol_AllTime;					//电压总时长
	DWORD  Vol_OutTime;					//电压越限时长
	DWORD  Bus_Num;						//母线数量
	DWORD  OutBus_Num;					//越限母线数量
	float  Vol_rate;					//电压合格率
	DWORD  Cos_AllTime;					//无功总时长
	DWORD  Cos_OutTime;					//无功越限时长
	DWORD  Trans_Num;					//无功监控数量
	DWORD  OutCos_Num;					//无功越限数量
	float  Cos_rate;					//无功合格率
	float  Loss_P;						//当前有功网损总计
	float  Loss_Q;						//当前无功网损总计
	float  Gen_P;						//发电机有功总计
	float  Gen_Q;						//发电机无功总计
	float  Load_P;						//负荷有功总计
	float  Load_Q;						//负荷无功总计
	float  Trans_P;						//变压器有功总计
	float  Trans_Q;						//变压器无功总计
	float  Line_P;						//线路有功总计
	float  Line_Q;						//线路无功总计
	float  lossdec;						//AVC日降损量
	DWORD  AVCLock_Num;					//AVC闭锁次数数
	DWORD  DevLock_Num;					//设备闭锁次数
	DWORD  ScadaEventNum;				//越限事件数
	DWORD  AVCEventNum;					//AVC越限事件数
	DWORD  AVCCtrlEveNum;				//AVC控制事件数
	DWORD  Shunt_Act;					//无功动作数
	DWORD  Trans_Act;					//变压器动作数
	DWORD  AVCCtrl_Num;					//AVC控制总数
	DWORD  CtrlFail_Num;				//控制失败总数
	DWORD  AVCCP_CtrlNum;				//AVC容抗控制次数
	DWORD  AVCXF_CtrlNum;				//变压器控制次数
	DWORD  CP_RefuseNum;				//容抗拒动次数
	DWORD  XF_RefuseNum;				//变压器拒动次数
	float  H24Vol_rate;					//电压合格率
	float  H24Cos_rate;					//无功合格率
	float  H24lossdec;					//AVC日降损量
	DWORD  H24Shunt_Ctrl;				//无功控制数
	DWORD  H24Trans_Ctrl;				//变压器控制数
	DWORD  H24Ctrl_Num;					//控制总数
	DWORD  H24Fail_Num;					//控制失败总数
	DWORD  H24CP_RefNum;				//容抗拒动次数
	DWORD  H24XF_RefNum;				//变压器拒动次数
	float  H24AvcUse_Rate;				//AVC可用率
	BYTE  H24AVC_Time;					//AVC运行总时长
	BYTE  H24Open_Time;					//AVC控制退出时长
	CTime  LogTime;						//数据时标
}AssessAVC_AVCSystem,*LPAssessAVC_AVCSystem;
//AVC告警定义表
typedef struct AssessAVC_AVCWarnInfo
{
	DWORD  StationID;					//厂站ID
	DWORD  DevID;						//设备ID
	DWORD  WarnID;						//告警ID
	BYTE  WarnType;						//告警类型/保护
	char  WarnInfo[32];					//告警类型描述
	BYTE  lockstat;						//闭锁状态
	CTime  ontm;						//动作时间
	CTime  offtm;						//复归时间
}AssessAVC_AVCWarnInfo,*LPAssessAVC_AVCWarnInfo;
//AVC控制策略表
typedef struct AssessAVC_AVCCtrlCmd
{
	DWORD  KeyID;						//序号
	CTime  LogTime;						//策略时间
	char  DevName[64];					//设备名称
	DWORD  StationID;					//厂站ID
	DWORD  DevID;						//设备ID
	DWORD  DevSub;						//控制设备下标
	CTime  IssTm;						//发送时刻
	CTime  CmdTm;						//执行时刻
	char  cause_info[80];				//控制原因
	char  result_info[80];				//措施
	char  Cmd_info[120];				//命令描述
	char  CmdType[8];					//命令类型
	short  CtrlType;					//操作类型
	char  rslttype[12];					//处理状态
	BYTE  qcheck;						//命令确认
	BYTE  qaut;							//自控命令
	DWORD  seq;							//命令编号
	DWORD  ZoneID;						//责任区ID
	DWORD  resp;						//责任区
}AssessAVC_AVCCtrlCmd,*LPAssessAVC_AVCCtrlCmd;
//AVC控制区域表
typedef struct AssessAVC_AVCCtrlZone
{
	DWORD  KeyID;						//序号
	char  Name[64];						//区域名称
	DWORD  VovNum;						//电压考核越限数
	DWORD  QovNum;						//无功考核越限数
	float  wloss;						//区域网损值
	DWORD  NormCp;						//可控电容数
	DWORD  NormXf;						//可控变压器数
	DWORD  LockCp;						//闭锁电容数
	DWORD  LockXf;						//闭锁变压器数
	float  VarIn;						//已投入无功总容量
	float  VarOff;						//未投入无功总容量
	float  Cosfi;						//关口功率因数
	float  score;						//区域状态得分
}AssessAVC_AVCCtrlZone,*LPAssessAVC_AVCCtrlZone;
//AVC操作事件表
typedef struct AssessAVC_AVCCtrlEvent
{
	DWORD  KeyID;						//序号
	char  user[24];						//用户名
	CTime  CmdTime;						//操作时刻
	char  opefunc[64];					//操作项
	char  text[120];					//操作内容
}AssessAVC_AVCCtrlEvent,*LPAssessAVC_AVCCtrlEvent;
//AVC越限事件表
typedef struct AssessAVC_AVCVoltEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//站名
	BYTE  DevType;						//设备类型
	DWORD  DevID;						//设备ID
	char  DevName[64];					//设备名称
	float  val;							//数值
	float  limitdn;						//限值
	float  limitup;						//限值
	BYTE  ByScada;						//事件来源1来源于SCADA
	CTime  EventTime;					//事件时间
	CTime  OffTime;						//结束时间
	DWORD  CmdID;						//控制事件ID
}AssessAVC_AVCVoltEvent,*LPAssessAVC_AVCVoltEvent;
//AVC变压器控制事件表
typedef struct AssessAVC_AVCTransEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//厂站名称
	DWORD  TransID;						//变压器ID
	char  TransName[64];				//变压器名称
	DWORD  WindID;						//控制绕组ID
	CTime  Optime;						//操作时间
	WORD  pretap;						//操作前档位
	WORD  afttap;						//操作后档位
	float  preVol;						//操作前电压
	float  aftVol;						//操作后电压
	char  opttype[20];					//命令类型
	BYTE  qAVC;							//AVC命令标志
	float  preHVol;						//控制前高压电压
	float  preHP;						//控制前高压有功
	float  preHQ;						//控制前高压无功
	float  preMVol;						//控制前中压电压
	float  preMP;						//控制前中压有功
	float  preMQ;						//控制前中压无功
	float  preLVol;						//控制前低压电压
	float  preLP;						//控制前低压有功
	float  preLQ;						//控制前低压无功
	float  aftHVol;						//控制后高压电压
	float  aftHP;						//控制后高压有功
	float  aftHQ;						//控制后高压无功
	float  aftMVol;						//控制后中压电压
	float  aftMP;						//控制后中压有功
	float  aftMQ;						//控制后中压无功
	float  aftLVol;						//控制后低压电压
	float  aftLP;						//控制后低压有功
	float  aftLQ;						//控制后低压无功
	BYTE  ByScada;						//事件来源1来源于SCADA
	CTime  EventTime;					//事件时间
	DWORD  CmdID;						//控制事件ID
}AssessAVC_AVCTransEvent,*LPAssessAVC_AVCTransEvent;
//AVC电容控制事件表
typedef struct AssessAVC_AVCShuntEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//厂站名称
	DWORD  ShuntID;						//电容ID
	char  ShuntName[64];				//电容名称
	CTime  opttime;						//操作时间
	char  opttype[20];					//命令类型
	BYTE  qavc;							//AVC指令标志
	BYTE  qopen;						//操作后运行状态
	float  preVol;						//操作前电压
	float  aftVol;						//操作后电压
	BYTE  ByScada;						//事件来源1来源于SCADA
	CTime  EventTime;					//事件时间
	DWORD  CmdID;						//控制事件ID
}AssessAVC_AVCShuntEvent,*LPAssessAVC_AVCShuntEvent;
//AVC运行参数表
typedef struct AssessAVC_AVCRunParam
{
	DWORD  ID;							//序号
	CTime  srttm;						//开始时间
	CTime  endtm;						//结束时间
	WORD  Type;							//时段类型
	char  Msg[32];						//时段描述
	WORD  CPNum;						//电容可用次数
	WORD  XfrNum;						//变压器可用次数
	float  CosUp;						//关口功率因数上限
	float  CosDn;						//关口功率因数下限
	float  SCosUp;						//厂站功率因数上限
	float  SCosDn;						//厂站功率因数下限
	float  V6Up;						//6KV上限
	float  V6Dn;						//6KV下限
	float  V10Up;						//10KV上限
	float  V10Dn;						//10KV下限
	float  V35Up;						//35KV上限
	float  V35Dn;						//35KV下限
	float  V110Up;						//110KV上限
	float  V110Dn;						//110KV下限
	float  V220Up;						//220KV上限
	float  V220Dn;						//220KV下限
	float  V330Up;						//330KV上限
	float  V330Dn;						//330KV下限
	CTime  LogTime;						//数据时标
}AssessAVC_AVCRunParam,*LPAssessAVC_AVCRunParam;
//AVC时段定义表
typedef struct AssessAVC_AVCTimePart
{
	DWORD  ID;							//序号
	char  Name[64];						//时段名称
	float  VUp1;						//电压上限1
	float  VDn1;						//电压下限1
	float  CP_Num1;						//电容可控次数1
	float  XF_Num1;						//变压器可控次数1
	float  CosUp1;						//功率因数上限1
	float  CosDn1;						//功率因数下限1
	CTime  Tm1;							//时段1分割点
	float  VUp2;						//电压上限2
	float  VDn2;						//电压下限2
	float  CP_Num2;						//电容可控次数2
	float  XF_Num2;						//变压器可控次数2
	float  CosUp2;						//功率因数上限2
	float  CosDn2;						//功率因数下限2
	CTime  Tm2;							//时段2分割点
	float  VUp3;						//电压上限3
	float  VDn3;						//电压下限3
	float  CP_Num3;						//电容可控次数3
	float  XF_Num3;						//变压器可控次数3
	float  CosUp3;						//功率因数上限3
	float  CosDn3;						//功率因数下限3
	CTime  Tm3;							//时段3分割点
	float  VUp4;						//电压上限4
	float  VDn4;						//电压下限4
	float  CP_Num4;						//电容可控次数4
	float  XF_Num4;						//变压器可控次数4
	float  CosUp4;						//功率因数上限4
	float  CosDn4;						//功率因数下限4
	CTime  Tm4;							//时段4分割点
	float  VUp5;						//电压上限5
	float  VDn5;						//电压下限5
	float  CP_Num5;						//电容可控次数5
	float  XF_Num5;						//变压器可控次数5
	float  CosUp5;						//功率因数上限5
	float  CosDn5;						//功率因数下限5
	CTime  Tm5;							//时段1分割点
	float  VUp6;						//电压上限6
	float  VDn6;						//电压下限6
	float  CP_Num6;						//电容可控次数6
	float  XF_Num6;						//变压器可控次数6
	float  CosUp6;						//功率因数上限6
	float  CosDn6;						//功率因数下限6
	CTime  LogTime;						//数据时标
}AssessAVC_AVCTimePart,*LPAssessAVC_AVCTimePart;
//AVC网损事件表
typedef struct AssessAVC_AVCLossEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//站名
	char  Name[64];						//描述
	float  val1;						//网损值1
	float  val2;						//网损值2
	BYTE  ByScada;						//事件来源1来源于SCADA
	CTime  EventTime;					//事件时间
	DWORD  CmdID;						//控制事件ID
}AssessAVC_AVCLossEvent,*LPAssessAVC_AVCLossEvent;
//AVC实时运行性能表
typedef struct AssessAVC_RealAVCCapably
{
	DWORD  NU;							//序号
	char  Type[64];						//性能类别
	char  Name[64];						//描述
	float  Value;						//数值
}AssessAVC_RealAVCCapably,*LPAssessAVC_RealAVCCapably;
//=================Tvisualpw===============
//PT表
typedef struct Tvisualpw_PT
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
}Tvisualpw_PT,*LPTvisualpw_PT;
//发电机
typedef struct Tvisualpw_Gen
{
	DWORD  NU;							//发电机号
	char  Name[64];						//发电机名
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
	CTime  LogTime;						//数据时标
}Tvisualpw_Gen,*LPTvisualpw_Gen;
//开关刀闸
typedef struct Tvisualpw_Switch
{
	DWORD  NU;							//开关编号
	char  Name[64];						//开关名字
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
	CTime  LogTime;						//数据时标
}Tvisualpw_Switch,*LPTvisualpw_Switch;
//负荷
typedef struct Tvisualpw_Load
{
	DWORD  NU;							//负荷编号
	char  Name[64];						//负荷名称
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
	CTime  LogTime;						//数据时标
}Tvisualpw_Load,*LPTvisualpw_Load;
//电容
typedef struct Tvisualpw_Shunt
{
	DWORD  NU;							//电容设备编号
	char  Name[64];						//电容设备名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Q;							//投入无功
	float  I;							//电流
	float  RVol;						//额定电压
	float  Qmax;						//最大无功输出
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	float  Qchk;						//检修容量
	BYTE  Tsta;							//故障状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	float  VL;							//电压等级
	short  status;						//综合状态
	DWORD  CtrlType;					//控制类型定义
	CTime  LogTime;						//数据时标
}Tvisualpw_Shunt,*LPTvisualpw_Shunt;
//电抗
typedef struct Tvisualpw_Sreact
{
	DWORD  NU;							//电抗器变号
	char  Name[64];						//电抗器名
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
	DWORD  CtrlType;					//控制类型定义
	float  RVol;						//额定电压
	float  Qmax;						//最大无功输出
	CTime  LogTime;						//数据时标
}Tvisualpw_Sreact,*LPTvisualpw_Sreact;
//2绕组变压器
typedef struct Tvisualpw_Tfm1
{
	DWORD  NU;							//2绕变编号
	char  Name[64];						//2绕变名
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
	DWORD  CtrlType;					//控制类型定义
	float  CosDn;						//功率因数下限
	float  CosUp;						//功率因数上限
	CTime  LogTime;						//数据时标
}Tvisualpw_Tfm1,*LPTvisualpw_Tfm1;
//3绕组变压器
typedef struct Tvisualpw_Tfm2
{
	DWORD  NU;							//3绕变编号
	char  Name[64];						//3绕变名
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
	DWORD  CtrlType;					//控制类型定义
	float  CosDn;						//功率因数下限
	float  CosUp;						//功率因数上限
	CTime  LogTime;						//数据时标
}Tvisualpw_Tfm2,*LPTvisualpw_Tfm2;
//静态无功补偿
typedef struct Tvisualpw_SVC
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
	CTime  LogTime;						//数据时标
}Tvisualpw_SVC,*LPTvisualpw_SVC;
//母线
typedef struct Tvisualpw_Bus
{
	DWORD  NU;							//母线编号
	char  Name[64];						//母线名称
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
	DWORD  CtrlType;					//控制类型定义
	CTime  LogTime;						//数据时标
}Tvisualpw_Bus,*LPTvisualpw_Bus;
//交流线
typedef struct Tvisualpw_Line
{
	DWORD  NU;							//交流线编号
	char  Name[64];						//交流线名称
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
	BYTE  EquiSta;						//等值状态
	CTime  LogTime;						//数据时标
}Tvisualpw_Line,*LPTvisualpw_Line;
//直流线
typedef struct Tvisualpw_DCLine
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
	CTime  LogTime;						//数据时标
}Tvisualpw_DCLine,*LPTvisualpw_DCLine;
//逆变器、变流器
typedef struct Tvisualpw_CVT
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
}Tvisualpw_CVT,*LPTvisualpw_CVT;
//接地
typedef struct Tvisualpw_GND
{
	DWORD  NU;							//接地编号
	char  Name[64];						//接地名称
	DWORD  Station;						//所属站号
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[24];						//标识
	DWORD  Node;						//节点
	CTime  LogTime;						//数据时标
}Tvisualpw_GND,*LPTvisualpw_GND;
//区域
typedef struct Tvisualpw_Zone
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
	CTime  LogTime;						//数据时标
}Tvisualpw_Zone,*LPTvisualpw_Zone;
//站
typedef struct Tvisualpw_Station
{
	DWORD  NU;							//站号
	char  Name[64];						//站名
	DWORD  zoneNU;						//所属区域
	float  VL;							//电压等级
	int  Type;							//厂站类型
	char  ID[24];						//变电站标识
	short  status;						//综合状态
	DWORD  CtrlType;					//控制类型定义
	CTime  LogTime;						//数据时标
}Tvisualpw_Station,*LPTvisualpw_Station;
//按节点电压排序
typedef struct Tvisualpw_VotOutage
{
	int  NU;							//设备编号
	char  type;							//设备类型
	float  Defl;						//风险指标
	BYTE  Group;						//分组类型
}Tvisualpw_VotOutage,*LPTvisualpw_VotOutage;
//按支路排序
typedef struct Tvisualpw_LineOutage
{
	int  NU;							//设备编号
	char  type;							//类型
	float  Defl;						//风险指标
	BYTE  Group;						//分组类型
}Tvisualpw_LineOutage,*LPTvisualpw_LineOutage;
//节点电压和支路合成
typedef struct Tvisualpw_AllOutage
{
	int  NU;							//设备编号
	char  type;							//类型
	float  Defl;						//风险指标
	BYTE  Group;						//分组类型
}Tvisualpw_AllOutage,*LPTvisualpw_AllOutage;
//系统指标
typedef struct Tvisualpw_SysGD
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
}Tvisualpw_SysGD,*LPTvisualpw_SysGD;
//系统告警
typedef struct Tvisualpw_SysAlarm
{
	WORD  Alarm;						//告警状态0,1
	WORD  num;							//发生告警的设备个数
	char  picname[32];					//推出画面名称
	WORD  picno;						//推出画面序号
}Tvisualpw_SysAlarm,*LPTvisualpw_SysAlarm;
//系统告警
typedef struct Tvisualpw_Ace
{
	DWORD  ID;							//标识ID
	float  CurVal;						//当前值
	CTime  datatime;					//数据时间
	BYTE  alarm;						//告警
	BYTE  ack;							//确认
}Tvisualpw_Ace,*LPTvisualpw_Ace;
//短路电流计算结果
typedef struct Tvisualpw_ShortCC
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
}Tvisualpw_ShortCC,*LPTvisualpw_ShortCC;
//用于仪表显示
typedef struct Tvisualpw_Meter
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
}Tvisualpw_Meter,*LPTvisualpw_Meter;
//分区表
typedef struct Tvisualpw_Area
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
	CTime  LogTime;						//数据时标
}Tvisualpw_Area,*LPTvisualpw_Area;
//电压无功控制表
typedef struct Tvisualpw_AVC
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
}Tvisualpw_AVC,*LPTvisualpw_AVC;
//发电机PQV参数表
typedef struct Tvisualpw_PQV
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
}Tvisualpw_PQV,*LPTvisualpw_PQV;
//负载统计表
typedef struct Tvisualpw_ldstate
{
	DWORD  NU;							//编号
	BYTE  type;							//类型
	float  LDmax;						//日最大负载
	CTime  LDmaxT;						//最大负载出现时间
	DWORD  LDoverT;						//日负载过载时长
}Tvisualpw_ldstate,*LPTvisualpw_ldstate;
//高压联网运行数据
typedef struct Tvisualpw_Hvcondata
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
}Tvisualpw_Hvcondata,*LPTvisualpw_Hvcondata;
//变压器动态监视
typedef struct Tvisualpw_DynMonitor
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
}Tvisualpw_DynMonitor,*LPTvisualpw_DynMonitor;
//事故影响
typedef struct Tvisualpw_CtgEffect
{
	DWORD  CtgNU;						//事故设备号
	char  CtgName[32];					//事故设备名
	int  CtgType;						//事故设备类型
	float  fSecurity;					//风险指标
	DWORD  EftNU;						//异态设备号
	char  EftName[32];					//异态设备名
	int  EftType;						//异态设备类型
	float  EftVal;						//异态程度
}Tvisualpw_CtgEffect,*LPTvisualpw_CtgEffect;
//全网性数据
typedef struct Tvisualpw_Grid
{
	float  GenMax;						//全网发电总容量
	float  GenP;						//全网发电有功
	float  GenQ;						//全网发电无功
	float  StopP;						//全网停机总容量
	float  UpRes;						//全网上旋转备用
	float  DownRes;						//全网下旋转备用
	float  LoadMax;						//全网设计总负荷
	float  LoadP;						//全网用电负荷
}Tvisualpw_Grid,*LPTvisualpw_Grid;
//变压器绕组
typedef struct Tvisualpw_Winding
{
	DWORD  NU;							//绕组编号
	char  Name[64];						//名称
	char  ID[24];						//绕组标识
	char  TID[24];						//变压器标识
	float  baseKV;						//基准电压
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
	CTime  LogTime;						//数据时标
}Tvisualpw_Winding,*LPTvisualpw_Winding;
//导线表
typedef struct Tvisualpw_Conductor
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
	CTime  LogTime;						//数据时标
}Tvisualpw_Conductor,*LPTvisualpw_Conductor;
//保护信息表
typedef struct Tvisualpw_Relay
{
	DWORD  ID;							//保护ID号
	DWORD  Station;						//厂站号
	char  Name[64];						//保护名称
	BYTE  RelayType;					//保护类型
	BYTE  YX;							//遥信状态
	DWORD  BayID;						//间隔ID
	DWORD  DevID;						//关联设备ID
	DWORD  DevNU;						//关联设备编号
	char  DevName[64];					//关联设备名称
	CTime  LogTime;						//数据时标
}Tvisualpw_Relay,*LPTvisualpw_Relay;
//遥信定义表
typedef struct Tvisualpw_YX
{
	DWORD  ID;							//遥信ID
	char  Name[64];						//遥信名称
	DWORD  DevID;						//设备ID
	BYTE  DevType;						//设备类型
	char  DevName[64];					//设备名称
	BYTE  YX;							//遥信状态
	CTime  LogTime;						//数据时标
}Tvisualpw_YX,*LPTvisualpw_YX;
//遥测定义表
typedef struct Tvisualpw_YC
{
	DWORD  ID;							//遥测ID
	char  Name[64];						//遥测名称
	DWORD  DevID;						//设备ID
	BYTE  DevType;						//设备类型
	char  DevName[64];					//设备名称
	BYTE  MeasType;						//遥测类型
	BYTE  MeasPos;						//遥测位置
	float  YC;							//遥测值
	CTime  LogTime;						//数据时标
}Tvisualpw_YC,*LPTvisualpw_YC;
//遥控遥信关系表
typedef struct Tvisualpw_YKYX
{
}Tvisualpw_YKYX,*LPTvisualpw_YKYX;
//系统网损日数据表
typedef struct Tvisualpw_SysPowerLoss
{
	CTime  LogTime;						//统计时间
	BYTE  IsToDay;						//是否当日数据
	float  PowerP;						//总有功
	float  PowerQ;						//总无功
	float  LoadP;						//负荷有功
	float  LoadQ;						//负荷无功
	float  ShuntQ;						//补偿无功
	float  LossP;						//有功网损
	float  LossQ;						//无功网损
	float  TheoryLossP;					//理论有功网损
	float  TheoryLossQ;					//理论无功网损
}Tvisualpw_SysPowerLoss,*LPTvisualpw_SysPowerLoss;
//=================Trefavc===============
//网络设置表
typedef struct Trefavc_NetSet_table
{
	DWORD  shNo;						//编号
	char  szName[64];					//网口名称
	BYTE  byProtocol;					//传输协议
	int  iPort;							//传输端口
	char  szDestIpAddr[24];				//目标IP
	char  szSouIpAddr[24];				//源IP
}Trefavc_NetSet_table,*LPTrefavc_NetSet_table;
//遥控表
typedef struct Trefavc_yk_table
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
	char  Name[64];						//名称
}Trefavc_yk_table,*LPTrefavc_yk_table;
//遥调表
typedef struct Trefavc_yt_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shOrderNo;					//序号
	BYTE  VlPos;						//电压侧位置
	BYTE  byCommandType;				//命令形式
	DWORD  shUpNo;						//升命令对象号
	BYTE  byUpInverse;					//升命令取反
	DWORD  shDownNo;					//降命令对象号
	BYTE  byDownInverse;				//降命令取反
	DWORD  shStopNo;					//撤消命令对象号
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
	char  Name[64];						//名称
}Trefavc_yt_table,*LPTrefavc_yt_table;
//保护信息表
typedef struct Trefavc_relay_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shOrderNo;					//序号
	char  szName[64];					//保护名称
	short  shAddress;					//地址
}Trefavc_relay_table,*LPTrefavc_relay_table;
//保护状态表
typedef struct Trefavc_RelayYx_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shOrderNo;					//序号
	char  szName[64];					//保护状态名
	DWORD  shUnitNo;					//单元号
	DWORD  shSourceNo;					//数据源号
	DWORD  shFrameOrder;				//报文序号
	BYTE  byStatus;						//保护状态
	BYTE  byInverter;					//反向标志
	BYTE  byRefresh;					//更新状态
	short  shWarnMode;					//告警方式
	BYTE  byUpdateNum;					//更新计数
}Trefavc_RelayYx_table,*LPTrefavc_RelayYx_table;
//T节点表
typedef struct Trefavc_tNode_table
{
	DWORD  shTnodeNo;					//T接点编号
	char  szName[64];					//T接名
	BYTE  byVolDegree;					//电压等级
	DWORD  shAreaNo;					//所在区域号
	DWORD  shZoneNo;					//所在区段号
	int  iPointNo;						//连接点号
}Trefavc_tNode_table,*LPTrefavc_tNode_table;
//等值变压器表
typedef struct Trefavc_equTrans_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shMasterNo;					//主变压器号
	DWORD  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	float  fCapacity;					//额定容量
	BYTE  byReguType;					//调压方式
	BYTE  byStatus;						//工作状态
	BYTE  byLock;						//闭锁状态
	BYTE  byCtrlType;					//优化控制类型
	DWORD  shTapYcNo;					//档位遥测序号
	float  fResistance;					//电阻值
	float  fReactance;					//电抗值
	float  fConductance;				//电导值
	float  fSusceptance;				//电纳值
	float  fMinRatio;					//最小变比
	float  fMaxRatio;					//最大变比
	float  fStepSize;					//档位步长
	DWORD  iFromPoint;					//首端连接点号
	int  iToPoint;						//末端连接点号
	DWORD  shFromPNo;					//首端有功量测序号
	DWORD  shFromQNo;					//首端无功量测序号
	DWORD  shFromINo;					//首端电流量测序号
	DWORD  shToPNo;						//末端有功量测序号
	DWORD  shToQNo;						//末端无功量测序号
	DWORD  shToINo;						//末端电流量测序号
	float  fBaseVol;					//基准电压
	char  szName[64];					//名称
}Trefavc_equTrans_table,*LPTrefavc_equTrans_table;
//闭锁定义表
typedef struct Trefavc_lock_table
{
	DWORD  shLockNo;					//编号
	BYTE  byEventType;					//闭锁事件类型
	char  shEvent[64];					//闭锁事件描述
	DWORD  shEventNo;					//闭锁事件序号
	BYTE  byObjectType;					//闭锁对象类型
	DWORD  shObjectFac;					//闭锁对象厂号
	DWORD  shObjectNo;					//闭锁对象序号
	char  shObjectName[64];				//闭锁对象名称
	short  shWarnMode;					//告警方式
	BYTE  byUnlockType;					//解除方式
}Trefavc_lock_table,*LPTrefavc_lock_table;
//区域表
typedef struct Trefavc_area_table
{
	DWORD  shAreaNo;					//区域号
	char  szAreaName[64];				//区域名
	float  fPA;							//计划有功输出
	float  fPLA;						//传输交换容差
}Trefavc_area_table,*LPTrefavc_area_table;
//地域表
typedef struct Trefavc_zone_table
{
	DWORD  shZoneNo;					//区段号
	char  szZoneName[64];				//区段名
	BYTE  byIT;							//优化类型
	BYTE  byLT;							//最小损耗类型
	BYTE  byMIZ;						//最大有功输出状态标志
	float  fLossDead;					//有功网损减少死区
	float  fLimitDead;					//电压越限减少死区
	float  fPrePLoss;					//优化前有功网损
	float  fPostPLoss;					//优化后有功网损
	float  fPreQLoss;					//优化前无功网损
	float  fPostQLoss;					//优化后无功网损
}Trefavc_zone_table,*LPTrefavc_zone_table;
//电压限值表
typedef struct Trefavc_VolLimit_table
{
	DWORD  shLimitNo;					//限值集号
	DWORD  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fMax1st;						//一级最大值
	float  fMin1st;						//一级最小值
	float  fMax2st;						//二级最大值
	float  fMin2st;						//二级最小值
	float  fMax3st;						//三级最大值
	float  fMin3st;						//三级最小值
	char  szName[64];					//名称
}Trefavc_VolLimit_table,*LPTrefavc_VolLimit_table;
//电压变化限值表
typedef struct Trefavc_VolVar_table
{
	DWORD  shLimitNo;					//限值集号
	DWORD  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fMax1st;						//一级最大值
	float  fMin1st;						//一级最小值
	float  fMax2st;						//二级最大值
	float  fMin2st;						//二级最小值
	float  fMax3st;						//三级最大值
	float  fMin3st;						//三级最小值
	char  szName[64];					//名称
}Trefavc_VolVar_table,*LPTrefavc_VolVar_table;
//无功定值表
typedef struct Trefavc_qSetLim_table
{
	DWORD  shLimitNo;					//约束集号
	DWORD  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fUpLimit;					//无功/功率因数高限
	float  fLowLimit;					//无功/功率因数低限
	BYTE  vlpos;						//电压侧
	char  szName[64];					//名称
}Trefavc_qSetLim_table,*LPTrefavc_qSetLim_table;
//电压限值表
typedef struct Trefavc_vSetLim_table
{
	DWORD  shLimitNo;					//约束集号
	DWORD  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fUpLimit;					//电压高限
	float  fLowLimit;					//电压低限
	BYTE  vlpos;						//电压侧
	char  szName[64];					//名称
}Trefavc_vSetLim_table,*LPTrefavc_vSetLim_table;
//优化事件表
typedef struct Trefavc_opfEvent_table
{
	DWORD  shEventNo;					//编号
	BYTE  byEventType;					//事件类型
	DWORD  shSourceFac;					//事件厂号
	DWORD  shSourceNo;					//事件序号
	BYTE  byYxVal;						//遥信值
	float  fChangeLimit;				//遥测变化限值绝对值
	short  shRelay;						//启动延时
	float  fLastValue;					//上次采样值
}Trefavc_opfEvent_table,*LPTrefavc_opfEvent_table;
//优化时间表
typedef struct Trefavc_opfStart_table
{
	DWORD  shTimeNo;					//编号
	CTime  tStartTime;					//启动时刻
}Trefavc_opfStart_table,*LPTrefavc_opfStart_table;
//遥测变化限值表
typedef struct Trefavc_opfYcLim_table
{
	DWORD  shLimitNo;					//编号
	DWORD  shYcFac;						//遥测厂号
	DWORD  shYcNo;						//遥测序号
	float  fChangeLimit;				//变化量绝对值限值
}Trefavc_opfYcLim_table,*LPTrefavc_opfYcLim_table;
//优化参数设置表
typedef struct Trefavc_opfSet_table
{
	DWORD  shAutoId;					//编号
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
}Trefavc_opfSet_table,*LPTrefavc_opfSet_table;
//电气岛表
typedef struct Trefavc_tIsland_table
{
	DWORD  iIslandNo;					//电力岛号
	DWORD  iNodeNum;					//节点数
	DWORD  iGenNum;						//发电机数
	DWORD  iLoadNum;					//负荷数
	short  shSeTime;					//状态估计时间
	BYTE  bySeResult;					//se结果
	short  shOpfTime;					//优化计算时间
	BYTE  byOpfResult;					//opf结果
	DWORD  iMeasNum;					//估计量测点数
	DWORD  iEligibleNum;				//估计后合格点数
	char  szRefGen[200];				//平衡机
}Trefavc_tIsland_table,*LPTrefavc_tIsland_table;
//计算节点表
typedef struct Trefavc_tmpNode_table
{
	DWORD  iNodeNo;						//节点号
	DWORD  iIslandNo;					//电力岛号
	DWORD  shFacNo;						//所在厂号
	DWORD  shAreaNo;					//所在区域号
	DWORD  shZoneNo;					//所在区段号
	short  byBusType;					//母线类型
	BYTE  byCtrlType;					//优化控制类型
	float  fBaseVol;					//基准电压
	float  fYcVol;						//遥测电压值
	float  fVolWeight;					//电压权值
	float  fVolStep;					//电压权值步长
	BYTE  byJPV;						//电压限制状态
	BYTE  byJPC;						//电压变化限制状态
	float  fSeVoltage;					//se电压值
	float  fSeAngle;					//se电压相角
	DWORD  shLimitNo;					//电压限制集号
	DWORD  shVarLimNo;					//无功变化限制集号
	char  Name[64];						//名称
	float  VolUpLimit;					//电压控制上限
	float  VolDnLimit;					//电压控制下限
	float  CosUpLimit;					//功率控制上限
	float  CosDnLimit;					//功率控制下限
	DWORD  SysNU;						//系统内部编号
	BYTE  IsGate;						//关口标志
}Trefavc_tmpNode_table,*LPTrefavc_tmpNode_table;
//计算变压器表
typedef struct Trefavc_tmpTrans_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shMasterNo;					//主变压器号
	DWORD  iTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	float  fCapacity;					//额定容量
	float  fRateKVi;					//额定电压i
	float  fRateKVj;					//额定电压j
	float  fBaseKVi;					//基准电压i
	float  fBaseKVj;					//基准电压i
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
	float  fTapPos;						//当前档位
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
	DWORD  iFromNode;					//首端节点号
	DWORD  iToPoint;					//末端节点号
	float  fSeFromP;					//首端有功
	float  fSeFromQ;					//首端无功
	float  fSeFromI;					//首端电流
	float  fSeToP;						//末端有功
	float  fSeToQ;						//末端无功
	float  fSeToI;						//末端电流
	DWORD  iIslandNo;					//电力岛号
	char  Name[64];						//名称
	DWORD  SysNU;						//系统内部编号
	BYTE  IsGate;						//关口标志
	float  CosUpLimit;					//功率控制上限
	float  CosDnLimit;					//功率控制下限
	DWORD  Parallel;					//并联支路
}Trefavc_tmpTrans_table,*LPTrefavc_tmpTrans_table;
//计算无功设备表
typedef struct Trefavc_tmpShunt_table
{
	DWORD  shFacNo;						//厂号
	DWORD  iShuntNo;					//编号
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
	DWORD  iFromNode;					//首端节点号
	DWORD  iToPoint;					//末端节点号
	float  fSeQ;						//无功估计值
	DWORD  iIslandNo;					//电力岛号
	char  Name[64];						//名称
	DWORD  SysNU;						//系统内部编号
	BYTE  IsVirtual;					//虚拟标志
}Trefavc_tmpShunt_table,*LPTrefavc_tmpShunt_table;
//计算发电机表
typedef struct Trefavc_tmpGen_table
{
	DWORD  shFacNo;						//厂号
	DWORD  iGenNo;						//发电机号
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
	DWORD  iNodeNo;						//节点号
	float  fSeP;						//有功估计值
	float  fSeQ;						//无功估计值
	DWORD  iIslandNo;					//电力岛号
	char  Name[64];						//名称
	DWORD  SysNU;						//系统内部编号
}Trefavc_tmpGen_table,*LPTrefavc_tmpGen_table;
//计算负荷表
typedef struct Trefavc_tmpLoad_table
{
	DWORD  shFacNo;						//厂号
	DWORD  iLoadNo;						//编号
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
	DWORD  iNodeNo;						//节点号
	float  fSeP;						//有功估计值
	float  fSeQ;						//无功估计值
	DWORD  iIslandNo;					//电力岛号
	char  Name[64];						//名称
	DWORD  SysNU;						//系统内部编号
}Trefavc_tmpLoad_table,*LPTrefavc_tmpLoad_table;
//计算线路表
typedef struct Trefavc_tmpLine_table
{
	DWORD  iLineNo;						//线路号
	DWORD  shFromFac;					//首端厂号
	DWORD  shToFac;						//末端厂号
	float  fResistance;					//电阻值
	float  fReactance;					//电抗值
	float  fConductance;				//电导值
	float  fSusceptance;				//电纳值
	float  fFromCapacity;				//线路首端容量
	float  fToCapacity;					//线路末端容量
	float  fBaseKV;						//额定电压
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
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fSeFromP;					//首端有功估计
	float  fSeFromQ;					//首端无功估计
	float  fSeFromI;					//首端电流估计
	float  fSeToP;						//末端有功估计
	float  fSeToQ;						//末端无功估计
	float  fSeToI;						//末端电流估计
	DWORD  iIslandNo;					//电力岛号
	char  Name[64];						//名称
	DWORD  SysNU;						//系统内部编号
	DWORD  Parallel;					//并联支路
}Trefavc_tmpLine_table,*LPTrefavc_tmpLine_table;
//计算母线表
typedef struct Trefavc_tmpBus_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shBusNo;						//母线号
	DWORD  iNodeNo;						//节点号
	short  byBusType;					//母线类型
	BYTE  byCtrlType;					//优化控制类型
	float  fBaseVol;					//基准电压
	float  fYcVol;						//遥测电压值
	float  fVolWeight;					//电压权值
	float  fVolStep;					//电压权值步长
	BYTE  byJPV;						//电压限制状态
	BYTE  byJPC;						//电压变化限制状态
	DWORD  shLimitNo;					//电压限制集号
	DWORD  shVarLimNo;					//无功变化限制集号
	char  Name[64];						//名称
	DWORD  iIslandNo;					//电力岛号
	float  VolUpLimit;					//电压控制上限
	float  VolDnLimit;					//电压控制下限
	float  CosUpLimit;					//功率控制上限
	float  CosDnLimit;					//功率控制下限
	DWORD  SysNU;						//系统内部编号
	BYTE  IsGate;						//关口标志
}Trefavc_tmpBus_table,*LPTrefavc_tmpBus_table;
//优化计算控制信息表
typedef struct Trefavc_opfRes_table
{
	DWORD  shAutoId;					//编号
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
}Trefavc_opfRes_table,*LPTrefavc_opfRes_table;
//量测不足表
typedef struct Trefavc_MeasAna_table
{
	int  iNoBalanceBran;				//不平衡支路数
	int  iNoBalanceNode;				//不平衡支路数
	int  iBSNoMatch;					//开关潮流不匹配数
	int  iBadData;						//坏数据数
	int  iShadMeas;						//可疑量测数
	int  iDummyMeas;					//伪量测数
}Trefavc_MeasAna_table,*LPTrefavc_MeasAna_table;
//优化前节点表
typedef struct Trefavc_preNode_table
{
	DWORD  iNodeNo;						//节点号
	DWORD  iIslandNo;					//电力岛号
	float  fVoltage;					//电压值
	float  fVolAngle;					//电压相角
	float  fGenMW;						//发电有功
	float  fGenMvar;					//发电无功
	float  fLoadMW;						//负荷有功
	float  fLoadMvar;					//负荷无功
	float  fShuntMW;					//并联支路有功
	float  fShuntMvar;					//并联支路无功
}Trefavc_preNode_table,*LPTrefavc_preNode_table;
//优化后节点表
typedef struct Trefavc_postNode_table
{
	DWORD  iNodeNo;						//节点号
	DWORD  iIslandNo;					//电力岛号
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
}Trefavc_postNode_table,*LPTrefavc_postNode_table;
//优化前线路表
typedef struct Trefavc_preLine_table
{
	DWORD  iLineNo;						//线路号
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fFromMW;						//线路首端有功
	float  fFromMvar;					//线路首端无功
	float  fToMW;						//线路末端有功
	float  fToMvar;						//线路末端无功
}Trefavc_preLine_table,*LPTrefavc_preLine_table;
//优化后线路表
typedef struct Trefavc_postLine_table
{
	DWORD  iLineNo;						//线路号
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fFromMW;						//线路首端有功
	float  fFromMvar;					//线路首端无功
	float  fToMW;						//线路末端有功
	float  fToMvar;						//线路末端无功
}Trefavc_postLine_table,*LPTrefavc_postLine_table;
//优化前变压器表
typedef struct Trefavc_preTrans_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shMasterNo;					//主变压器号
	DWORD  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fFromMW;						//首端有功
	float  fFromMvar;					//首端无功
	float  fToMW;						//末端有功
	float  fToMvar;						//末端无功
	float  fFromPf;						//首端功率因数
	float  fToPf;						//末端功率因数
}Trefavc_preTrans_table,*LPTrefavc_preTrans_table;
//优化后变压器表
typedef struct Trefavc_postTran_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shMasterNo;					//主变压器号
	DWORD  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fFromMW;						//首端有功
	float  fFromMvar;					//首端无功
	float  fToMW;						//末端有功
	float  fToMvar;						//末端无功
	float  fFromPf;						//首端功率因数
	float  fToPf;						//末端功率因数
}Trefavc_postTran_table,*LPTrefavc_postTran_table;
//优化控制变压器表
typedef struct Trefavc_opfTrans_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shMasterNo;					//主变压器号
	DWORD  shTransNo;					//变压器号
	BYTE  byVolSide;					//电压侧
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fFromBaseVol;				//首端基准电压
	float  fToBaseVol;					//末端基准电压
	float  fPreRatio;					//优化前变比
	float  fPostRatio;					//优化后变比
}Trefavc_opfTrans_table,*LPTrefavc_opfTrans_table;
//优化控制无功表
typedef struct Trefavc_opfShunt_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shShuntNo;					//编号
	DWORD  iFromNode;					//首端节点号
	DWORD  iToNode;						//末端节点号
	float  fPreVar;						//优化前容量
	float  fPostVar;					//优化后容量
}Trefavc_opfShunt_table,*LPTrefavc_opfShunt_table;
//VQC定值表
typedef struct Trefavc_VqcSet_table
{
	DWORD  shFacNo;						//厂号
	BYTE  byType;						//变压器类型
	DWORD  shTransNo;					//变压器号
	char  szFacName[64];				//厂站名
	char  szTransName[64];				//变压器名
	float  fHiVolSet;					//电压定值上限
	float  fLowVolSet;					//电压定值下限
	float  fHiVarSet;					//无功/功率因数定值上限
	float  fLowVarSet;					//无功/功率因数定值下限
	BYTE  byStatus;						//发送状态
}Trefavc_VqcSet_table,*LPTrefavc_VqcSet_table;
//控制命令表
typedef struct Trefavc_opfCmd_table
{
	DWORD  tmOrder;						//序号
	DWORD  shFacNo;						//厂号
	BYTE  byType;						//设备类型
	DWORD  shDeviceNo;					//设备编号
	char  szFacName[64];				//厂站名
	char  szDevName[64];				//设备名
	DWORD  SwitchNU;					//开关编号
	char  YKSwitch[64];					//遥控开关
	int  YKPoint;						//遥控点号
	BYTE  byCommand;					//命令（分升/合降）
	float  shCurTap;					//当前档位
	float  shEndTap;					//目标档位
	BYTE  byStatus;						//控制状态
	CTime  CreatTime;					//创建时间
	CTime  YKTime;						//控制时间
	char  YKInfo[64];					//控制信息
	BYTE  YKState;						//遥控标识
	char  CtrlType[16];					//控制方法
}Trefavc_opfCmd_table,*LPTrefavc_opfCmd_table;
//发电机优化表
typedef struct Trefavc_opfGen_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shGenNo;						//发电机号
	DWORD  iNodeNo;						//节点号
	float  fPreP;						//优化前有功
	float  fPostP;						//优化后有功
	float  fPreQ;						//优化前无功
	float  fPostQ;						//优化后无功
}Trefavc_opfGen_table,*LPTrefavc_opfGen_table;
//发电机PQ曲线表
typedef struct Trefavc_genPQ_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shGenNo;						//发电机号
	DWORD  shOrderNo;					//序号
	float  fP;							//有功出力
	float  fMaxQ;						//最大无功
	float  fMinQ;						//最小无功
}Trefavc_genPQ_table,*LPTrefavc_genPQ_table;
//母线优化结果表
typedef struct Trefavc_opfBus_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shBusNo;						//母线号
	char  szFacName[64];				//厂站名
	char  szBusName[64];				//母线名
	float  fYcVol;						//遥测电压值
	float  fSeVol;						//状态估计电压值
	float  fSeDev;						//量测估计偏差
	float  fSeAngle;					//状态估计电压相角
	float  fOpfVol;						//优化电压值
	float  fOpfAngle;					//优化电压相角
	float  fPostVol;					//控制后电压值
}Trefavc_opfBus_table,*LPTrefavc_opfBus_table;
//线路优化结果表
typedef struct Trefavc_opfLine_table
{
	DWORD  iLineNo;						//线路号
	char  szName[64];					//线路名
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
}Trefavc_opfLine_table,*LPTrefavc_opfLine_table;
//变压器优化结果表
typedef struct Trefavc_opfByq_table
{
	DWORD  shFacNo;						//厂号
	BYTE  byType;						//变压器类型
	DWORD  shTransNo;					//变压器号
	char  szFacName[64];				//厂站名
	char  szTransName[64];				//变压器名
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
}Trefavc_opfByq_table,*LPTrefavc_opfByq_table;
//无功设备优化结果表
typedef struct Trefavc_opfWgsb_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shShuntNo;					//编号
	char  szFacName[64];				//厂站名
	char  szName[64];					//设备名
	float  fYcQ;						//无功遥测
	float  fSeQ;						//状态估计无功
	float  fOpfQ;						//优化无功
	float  fPostQ;						//控制后无功遥测
}Trefavc_opfWgsb_table,*LPTrefavc_opfWgsb_table;
//发电机优化结果表
typedef struct Trefavc_opfFdj_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shGenNo;						//发电机号
	char  szFacName[64];				//厂站名
	char  szName[64];					//发电机名
	float  fYcP;						//有功遥测
	float  fYcQ;						//无功遥测
	float  fSeP;						//状态估计有功
	float  fSeQ;						//状态估计无功
	float  fOpfP;						//优化有功
	float  fOpfQ;						//优化无功
	float  fPostP;						//控制后有功遥测
	float  fPostQ;						//控制后无功遥测
}Trefavc_opfFdj_table,*LPTrefavc_opfFdj_table;
//电压估计统计表
typedef struct Trefavc_VolSeSta_table
{
	DWORD  iIslandNo;					//电力岛号
	BYTE  byStaType;					//估计统计类型
	BYTE  byVolDegree;					//电压等级序号
	float  fVolSeAccu;					//估计合格率
}Trefavc_VolSeSta_table,*LPTrefavc_VolSeSta_table;
//母线电压越限表
typedef struct Trefavc_BusExcee_table
{
	DWORD  shFacNo;						//厂号
	DWORD  shBusNo;						//母线号
	char  szFacName[64];				//厂站名
	char  szBusName[64];				//母线名
	float  fYcVol;						//遥测电压值
	float  fSeVol;						//状态估计电压值
	float  fOpfVol;						//优化电压值
}Trefavc_BusExcee_table,*LPTrefavc_BusExcee_table;
//变压器损耗表
typedef struct Trefavc_LossByq_table
{
	DWORD  shFacNo;						//厂号
	BYTE  byType;						//变压器类型
	DWORD  shTransNo;					//变压器号
	char  szFacName[64];				//厂站名
	char  szTransName[64];				//变压器名
	float  fPrePLoss;					//优化前有功损耗
	float  fPostPLoss;					//优化后有功损耗
	float  fPreQLoss;					//优化前无功损耗
	float  fPostQLoss;					//优化后无功损耗
}Trefavc_LossByq_table,*LPTrefavc_LossByq_table;
//线路损耗表
typedef struct Trefavc_LossLine_table
{
	DWORD  iLineNo;						//线路号
	char  szName[64];					//线路名
	float  fPrePLoss;					//优化前有功损耗
	float  fPostPLoss;					//优化后有功损耗
	float  fPreQLoss;					//优化前无功损耗
	float  fPostQLoss;					//优化后无功损耗
}Trefavc_LossLine_table,*LPTrefavc_LossLine_table;
//当前闭锁表
typedef struct Trefavc_curLock_table
{
	CTime  tLockTime;					//闭锁时间
	BYTE  byObjectType;					//闭锁对象类型
	DWORD  shObjectFac;					//闭锁对象厂号
	char  szFacName[64];				//闭锁对象厂名
	DWORD  shObjectNo;					//闭锁对象号
	char  szObectName[64];				//闭锁对象名
	char  szLockInfo[100];				//闭锁信息
}Trefavc_curLock_table,*LPTrefavc_curLock_table;
//反时限控制表
typedef struct Trefavc_DevCtrl_table
{
	DWORD  shOrderNo;					//序号
	float  fVolIntegral;				//电压积分量
	float  fVolSecIncreas;				//电压二级增量
	short  shVolHop;					//电压跳变数
	float  fCosIntegral;				//力率积分面积
	float  fCosSecIncreas;				//力率二级增量
	short  shCosHop;					//力率跳变数
}Trefavc_DevCtrl_table,*LPTrefavc_DevCtrl_table;
//规则表
typedef struct Trefavc_Rule_table
{
	WORD  rule_no;						//规则编号
	short  order_no;					//序号
	BYTE  v_status;						//电压状态
	BYTE  cos_status;					//功率因数状态
	BYTE  t_status;						//变压器当前状
	BYTE  c_status;						//补偿装置状态
	BYTE  t_action;						//变压器动作
	BYTE  c_action;						//补偿装置动作
}Trefavc_Rule_table,*LPTrefavc_Rule_table;
//可疑量测表
typedef struct Trefavc_shady_table
{
	BYTE  bType;						//类型
	char  szInfo[160];					//信息
}Trefavc_shady_table,*LPTrefavc_shady_table;
//控制限值表
typedef struct Trefavc_SetLim_table
{
	DWORD  shLimitNo;					//约束集号
	DWORD  shOrderNo;					//序号
	CTime  tStartTime;					//起始时间
	CTime  tEndTime;					//终止时间
	float  fVolUp;						//电压高限
	float  fVolLow;						//电压低限
	float  fVarUp;						//无功上限
	float  fVarDown;					//无功下限
	WORD  fTransNum;					//变压器可调节次数
	WORD  fShuntNum;					//电容器可调节次数
	BYTE  vlpos;						//电压侧
	char  szName[64];					//名称
	float  fBaseVol;					//基准电压
}Trefavc_SetLim_table,*LPTrefavc_SetLim_table;
//AVC系统默认运行参数
typedef struct Trefavc_Avc_RunParam
{
	DWORD  NU;							//序号
	CTime  starttime;					//起始时间
	CTime  endtime;						//终止时间
	short  type;						//时段类别
	char  tyname[64];					//时段类别名称
	float  BaseVol;						//基准电压
	WORD  capnum;						//电容控制次数
	WORD  tfmnum;						//变压器控制次数
	float  GateCosup;					//关口功率上限
	float  GateCosdn;					//关口功率下限
	float  FacCosup;					//厂站功率上限
	float  FacCosdn;					//厂站功率下限
	float  Volup;						//电压上限
	float  Voldn;						//电压下限
}Trefavc_Avc_RunParam,*LPTrefavc_Avc_RunParam;
//设备遥控信息定义表
typedef struct Trefavc_DevYk_table
{
	DWORD  NU;							//设备编号
	char  Name[64];						//设备名称
	BYTE  DevType;						//设备类型
	char  YKType[32];					//遥控类型
	char  YKName[64];					//遥控名称
	char  LinkSwitch[64];				//遥控开关
	DWORD  SwitchNU;					//开关编号
	DWORD  UpPoint;						//分/升点号
	DWORD  DnPoint;						//合/降点号
	BYTE  RevFlag;						//反向标识
	short  DelayTime;					//延迟时间
}Trefavc_DevYk_table,*LPTrefavc_DevYk_table;
//系统网损日数据表
typedef struct Trefavc_SysPowerLoss
{
	CTime  LogTime;						//统计时间
	char  OpfType[32];					//优化方法
	float  PowerP;						//总有功
	float  PowerQ;						//总无功
	float  LoadP;						//负荷有功
	float  LoadQ;						//负荷无功
	float  ShuntQ;						//补偿无功
	float  LossP;						//有功网损
	float  LossQ;						//无功网损
	int  CtrlTfm;						//变压器控制数
	int  CtrlShunt;						//电容器控制数
	float  OpfLossP;					//有功网损
	float  OpfLossQ;					//无功网损
}Trefavc_SysPowerLoss,*LPTrefavc_SysPowerLoss;
//=================TScadaAVC===============
//高软电气岛信息表
typedef struct TScadaAVC_PasIsland
{
	DWORD  NU;							//序号
	DWORD  IslandID;					//岛号
	DWORD  Station;						//平衡机厂号
	char  StaName[64];					//平衡机厂名
	DWORD  GenID;						//平衡机ID
	char  GenName[64];					//平衡机名
	DWORD  NodeNum;						//节点数
	BYTE  State;						//收敛性
	BYTE  Obisle;						//可观测性
	BYTE  BadDataP;						//有功坏数据
	BYTE  BadDataQ;						//无功坏数据
	CTime  SERunTime;					//运行时间
	CTime  LogTime;						//数据时标
}TScadaAVC_PasIsland,*LPTScadaAVC_PasIsland;
//高软计算信息表
typedef struct TScadaAVC_PasRunInfo
{
	CTime  RunTime;						//运行时间
	char  RunInfo[200];					//运行信息
	CTime  LogTime;						//数据时标
}TScadaAVC_PasRunInfo,*LPTScadaAVC_PasRunInfo;
//高软SE参数表
typedef struct TScadaAVC_PasSEParam
{
	BYTE  Run_State;					//当前运行状态
	BYTE  Pause_State;					//暂停计算状态
	CTime  RunTime;						//计算时间
	BYTE  Conv_State;					//当前收敛状态
	float  Measure_Rate;				//遥测覆盖率
	DWORD  CycleTime;					//运行周期(分)
	DWORD  MaxIter;						//最大迭代次数
	float  EpsP;						//有功收敛精度
	float  EpsQ1;						//无功收敛精度
	float  SE_Rate;						//当前状估合格率
	float  SE_DayRate;					//当日状估合格率
	float  SE_MonRate;					//月状估合格率
	float  SE_YearRate;					//年状估合格率
	CTime  LogTime;						//数据时标
}TScadaAVC_PasSEParam,*LPTScadaAVC_PasSEParam;
//高软SE量测一览表
typedef struct TScadaAVC_PasSEMeasure
{
	DWORD  Station;						//厂站号
	DWORD  DevID;						//设备ID
	BYTE  DevType;						//设备类型
	BYTE  MeasType;						//量测类型
	BYTE  MeasPos;						//量测位置
	char  MeasInfo[64];					//量测名称
	DWORD  Island;						//岛号
	float  Meas_value;					//量测值
	float  SE_value;					//状态估计值
	float  Err_value;					//误差百分数
	float  Error;						//不合格量测
	float  BadData;						//坏数据
	float  DHisRate;					//日合格统计率
	float  MHisRate;					//月合格统计率
}TScadaAVC_PasSEMeasure,*LPTScadaAVC_PasSEMeasure;
//AVC厂站信息表
typedef struct TScadaAVC_AVCStation
{
	DWORD  ID;							//厂站ID
	char  Name[64];						//厂站名称
	DWORD  Zone;						//区域ID
	BYTE  CtrlOut;						//控制退出
	BYTE  AVCCtrl;						//AVC自动控制
	DWORD  CtrlID;						//控制时段编号
	BYTE  Lock_Sta;						//厂站闭锁状态
	BYTE  DevLock_Sta;					//厂站设备闭锁状态
	float  Vol_rate;					//电压合格率
	float  Loss_P;						//有功网损
	float  Loss_Q;						//无功网损
	float  Bachup_Q;					//无功备用
	DWORD  DCtrlNum;					//日动作数
	DWORD  H24CtrlNum;					//24小时动作数
	DWORD  MCtrlNum;					//月动作数
	CTime  LogTime;						//数据时标
}TScadaAVC_AVCStation,*LPTScadaAVC_AVCStation;
//AVC母线信息表
typedef struct TScadaAVC_AVCBus
{
	DWORD  BusID;						//母线ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//母线名称
	DWORD  CtrlID;						//控制时段编号
	BYTE  Ctr_Sta;						//是否控制
	BYTE  Cal_Sta;						//是否参与计算
	BYTE  Lock_Sta;						//闭锁状态
	BYTE  IsGate;						//关口标识
	float  Volup;						//电压上限
	float  Voldn;						//电压下限
	float  Cosup;						//功率上限
	float  Cosdn;						//功率下限
	float  DVol_rate;					//日电压合格率
	float  H24Vol_rate;					//24小时电压合格率
	float  MVol_rate;					//月电压合格率
	float  DCos_rate;					//日无功合格率
	float  H24Cos_rate;					//24小时无功合格率
	float  MCos_rate;					//月无功合格率
	CTime  LogTime;						//数据时标
}TScadaAVC_AVCBus,*LPTScadaAVC_AVCBus;
//AVC变压器信息表
typedef struct TScadaAVC_AVCTrans
{
	DWORD  ID;							//变压器ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//变压器名称
	DWORD  CtrlID;						//控制时段ID
	BYTE  Cal_Sta;						//参与计算标识
	BYTE  Lock_Sta;						//闭锁标识
	short  LimitNumber;					//控制次数限制
	DWORD  UpYXID;						//升档遥信ID
	DWORD  UpYKNO;						//升档遥控点号
	DWORD  DnYXID;						//降档遥信ID
	DWORD  DnYKNO;						//降档遥控点号
	DWORD  LinkBusID;					//关联母线ID
	BYTE  IsGate;						//关口变压器
	DWORD  DCtrlNum;					//日控制次数
	DWORD  DAVCCtrlNum;					//日AVC控制次数
	DWORD  DAVCActNum;					//日AVC动作次数
	DWORD  H24CtrlNum;					//24小时控制次数
	DWORD  H24AVCCtrlNum;				//24小时AVC控制次数
	DWORD  H24AVCActNum;				//24小时AVC动作次数
	DWORD  MCtrlNum;					//月控制次数
	DWORD  MAVCCtrlNum;					//月AVC控制次数
	DWORD  MAVCActNum;					//月AVC动作次数
	DWORD  YCtrlNum;					//年控制次数
	DWORD  YAVCCtrlNum;					//年AVC控制次数
	DWORD  YAVCActNum;					//年AVC动作次数
	CTime  LogTime;						//数据时标
}TScadaAVC_AVCTrans,*LPTScadaAVC_AVCTrans;
//AVC无功设备信息表
typedef struct TScadaAVC_AVCShunt
{
	DWORD  ID;							//电容ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//电容名称
	DWORD  CtrlID;						//控制时段ID
	BYTE  Cal_Sta;						//参与计算
	BYTE  Lock_Sta;						//闭锁状态
	WORD  LimitNum;						//动作次数限制
	DWORD  YXID;						//遥信ID
	DWORD  YKNO;						//遥控点号
	DWORD  BusID;						//控制母线ID
	DWORD  BreakID;						//控制开关ID
	DWORD  DCtrlNum;					//日动作数量
	DWORD  DAVCCtrlNum;					//日AVC控制数量
	DWORD  DAVCActNum;					//日AVC动作数量
	DWORD  H24CtrlNum;					//24小时动作数量
	DWORD  H24AVCCtrlNum;				//24小时AVC控制数量
	DWORD  H24AVCActNum;				//24小时AVC动作数量
	DWORD  MCtrlNum;					//月动作数量
	DWORD  MAVCCtrlNum;					//月AVC控制数量
	DWORD  MAVCActNum;					//月AVC动作数量
	DWORD  YCtrlNum;					//年动作数量
	DWORD  YAVCCtrlNum;					//年AVC控制数量
	DWORD  YAVCActNum;					//年AVC动作数量
	DWORD  DRunTime;					//日运行时长
	DWORD  H24RunTime;					//24小时运行时长
	DWORD  MRunTime;					//月运行时长
	DWORD  YRunTime;					//年运行时长
	CTime  LogTime;						//数据时标
}TScadaAVC_AVCShunt,*LPTScadaAVC_AVCShunt;
//AVC区域信息表
typedef struct TScadaAVC_AVCZone
{
	DWORD  ID;							//区域编号
	char  Name[120];					//区域名称
	float  Vol_rate;					//电压合格率
	float  Cos_rate;					//无功合格率
	double  Loss_P;						//有功降损总计
	double  Loss_Q;						//无功降损总计
	DWORD  Shunt_Ctrl;					//无功控制数
	DWORD  Trans_Ctrl;					//变压器控制数
	float  H24Vol_rate;					//24小时电压合格率
	float  H24Cos_rate;					//24小时无功合格率
	float  H24LossP_rate;				//24小时有功网损率
	float  H24LossQ_rate;				//24小时无功网损率
	DWORD  H24Shunt_Ctrl;				//24小时无功控制数
	DWORD  H24Trans_Ctrl;				//24小时变压器控制数
	float  MVol_rate;					//月电压合格率
	float  MCos_rate;					//月无功合格率
	float  MLossP_rate;					//月有功网损率
	float  MLossQ_rate;					//月无功网损率
	DWORD  MShunt_Ctrl;					//月无功控制数
	DWORD  MTrans_Ctrl;					//月变压器控制数
	float  YVol_rate;					//年电压合格率
	float  YCos_rate;					//年无功合格率
	float  YLossP_rate;					//年有功网损率
	float  YLossQ_rate;					//年无功网损率
	DWORD  YShunt_Ctrl;					//年无功控制数
	DWORD  YTrans_Ctrl;					//年变压器控制数
	CTime  LogTime;						//数据时标
}TScadaAVC_AVCZone,*LPTScadaAVC_AVCZone;
//AVC运行参数信息表
typedef struct TScadaAVC_AVCCtrRunParam
{
	CTime  DateLog;						//系统运行日志时间
	char  SysInfo[24];					//系统信息
	char  RunMsg[64];					//运行信息
	DWORD  RunNum;						//运行次数
	CTime  StartTime;					//启动时间
	CTime  AvcTime;						//AVC结束时间
	BYTE  Run_Sta;						//运行状态
	BYTE  Auto_Sta;						//自动控制状态
	BYTE  Quit_Sta;						//程序退出状态
	BYTE  Cmd_Sta;						//命令下发状态
	BYTE  Remote_Sta;					//远动状态
	BYTE  Enable_Sta;					//AVC可用标志
	WORD  Cycvol;						//采样周期
	int  Ctrlmtd;						//控制算法
	BYTE  Ctrl_CP;						//电容控制状态
	BYTE  Ctrl_Cos;						//区域无功控制状态
	BYTE  Ctrl_Vol;						//区域电压控制状态
	WORD  Xfre_space;					//主变调档时间间隔
	WORD  CPOut_space;					//电容投入退出时间间隔
	WORD  CPIn_space;					//电容退出投入时间间隔
	WORD  Zone_space;					//区域控制时间间隔
	float  Xfr_overload;				//主变过载系数
	float  AvcUse_Rate;					//AVC可用率
	DWORD  AvcClosedTime;				//AVC闭环运行时长
	DWORD  CtrlNum;						//AVC控制指令数
	DWORD  CtrlSucNum;					//AVC控制成功数
	float  CtrlSuc_Rate;				//AVC控制成功率
	DWORD  MaxCtrlNum;					//最大可动设备数
	DWORD  CP_RefuseNum;				//容抗拒动次数
	DWORD  XF_RefuseNum;				//变压器拒动次数
	float  lossdec;						//日降损量
}TScadaAVC_AVCCtrRunParam,*LPTScadaAVC_AVCCtrRunParam;
//AVC时段定义表
typedef struct TScadaAVC_AVCTimePart
{
	DWORD  ID;							//序号
	char  Name[64];						//时段名称
	float  VUp1;						//电压上限1
	float  VDn1;						//电压下限1
	float  CP_Num1;						//电容可控次数1
	float  XF_Num1;						//变压器可控次数1
	float  CosUp1;						//功率因数上限1
	float  CosDn1;						//功率因数下限1
	CTime  Tm1;							//时段1分割点
	float  VUp2;						//电压上限2
	float  VDn2;						//电压下限2
	float  CP_Num2;						//电容可控次数2
	float  XF_Num2;						//变压器可控次数2
	float  CosUp2;						//功率因数上限2
	float  CosDn2;						//功率因数下限2
	CTime  Tm2;							//时段2分割点
	float  VUp3;						//电压上限3
	float  VDn3;						//电压下限3
	float  CP_Num3;						//电容可控次数3
	float  XF_Num3;						//变压器可控次数3
	float  CosUp3;						//功率因数上限3
	float  CosDn3;						//功率因数下限3
	CTime  Tm3;							//时段3分割点
	float  VUp4;						//电压上限4
	float  VDn4;						//电压下限4
	float  CP_Num4;						//电容可控次数4
	float  XF_Num4;						//变压器可控次数4
	float  CosUp4;						//功率因数上限4
	float  CosDn4;						//功率因数下限4
	CTime  Tm4;							//时段4分割点
	float  VUp5;						//电压上限5
	float  VDn5;						//电压下限5
	float  CP_Num5;						//电容可控次数5
	float  XF_Num5;						//变压器可控次数5
	float  CosUp5;						//功率因数上限5
	float  CosDn5;						//功率因数下限5
	CTime  Tm5;							//时段1分割点
	float  VUp6;						//电压上限6
	float  VDn6;						//电压下限6
	float  CP_Num6;						//电容可控次数6
	float  XF_Num6;						//变压器可控次数6
	float  CosUp6;						//功率因数上限6
	float  CosDn6;						//功率因数下限6
	CTime  LogTime;						//数据时标
}TScadaAVC_AVCTimePart,*LPTScadaAVC_AVCTimePart;
//AVC告警类型表
typedef struct TScadaAVC_AVCWarnType
{
	DWORD  KeyID;						//序号
	DWORD  ID;							//告警ID
	char  TypeName[24];					//告警名称
	short  ot;							//告警设备类型
	char  txt[32];						//告警内容
	BYTE  qskip;						//抑止告警标志
	BYTE  qlock;						//闭锁复归方式
	BYTE  qsend;						//告警发送标志
	int  deltm;							//复归延时时间
}TScadaAVC_AVCWarnType,*LPTScadaAVC_AVCWarnType;
//AVC告警定义表
typedef struct TScadaAVC_AVCWarnInfo
{
	DWORD  StationID;					//厂站ID
	DWORD  DevID;						//设备ID
	DWORD  WarnID;						//告警类型ID
	BYTE  qlock;						//闭锁复归方式
	BYTE  stat;							//闭锁状态
	WORD  almtype;						//告警类型
	CTime  ontm;						//动作时间
	CTime  offtm;						//复归时间
	BYTE  IsDone;						//处理标志
}TScadaAVC_AVCWarnInfo,*LPTScadaAVC_AVCWarnInfo;
//AVC保护定义表
typedef struct TScadaAVC_AVCRelayInfo
{
	DWORD  StationID;					//厂站ID
	DWORD  RelayID;						//保护ID
	BYTE  state;						//保护状态
	short  qlock;						//闭锁复归方式
	DWORD  DevId;						//关联设备ID
	CTime  OnTm;						//动作时间
	CTime  OffTm;						//复归时间
	BYTE  IsDone;						//处理标志
}TScadaAVC_AVCRelayInfo,*LPTScadaAVC_AVCRelayInfo;
//AVC控制策略表
typedef struct TScadaAVC_AVCCtrlCmd
{
	DWORD  KeyID;						//序号
	CTime  LogTime;						//策略时间
	char  DevName[64];					//设备名称
	DWORD  StationID;					//厂站ID
	DWORD  DevID;						//设备ID
	DWORD  DevSub;						//控制设备下标
	CTime  IssTm;						//发送时刻
	CTime  CmdTm;						//执行时刻
	char  cause_info[80];				//控制原因
	char  result_info[80];				//措施
	char  Cmd_info[120];				//命令描述
	char  CmdType[8];					//命令类型
	short  CtrlType;					//操作类型
	char  rslttype[12];					//处理状态
	BYTE  qcheck;						//命令确认
	BYTE  qaut;							//自控命令
	DWORD  seq;							//命令编号
	DWORD  ZoneID;						//责任区ID
	DWORD  resp;						//责任区
}TScadaAVC_AVCCtrlCmd,*LPTScadaAVC_AVCCtrlCmd;
//AVC控制区域表
typedef struct TScadaAVC_AVCCtrlZone
{
	DWORD  KeyID;						//序号
	char  Name[64];						//区域名称
	DWORD  VovNum;						//电压考核越限数
	DWORD  QovNum;						//无功考核越限数
	float  wloss;						//区域网损值
	DWORD  NormCp;						//可控电容数
	DWORD  NormXf;						//可控变压器数
	DWORD  LockCp;						//闭锁电容数
	DWORD  LockXf;						//闭锁变压器数
	float  VarIn;						//已投入无功总容量
	float  VarOff;						//未投入无功总容量
	float  Cosfi;						//关口功率因数
	float  score;						//区域状态得分
	CTime  LogTime;						//数据时标
}TScadaAVC_AVCCtrlZone,*LPTScadaAVC_AVCCtrlZone;
//AVC区域交换表
typedef struct TScadaAVC_AVCAreaChange
{
	DWORD  KeyID;						//序号
	DWORD  objtype;						//对象类型
	DWORD  objID;						//对象ID
	DWORD  objcdID;						//对象测点ID
	float  value;						//对象值
	DWORD  datdir;						//数据传输方向
}TScadaAVC_AVCAreaChange,*LPTScadaAVC_AVCAreaChange;
//AVC操作事件表
typedef struct TScadaAVC_AVCCtrlEvent
{
	DWORD  KeyID;						//序号
	char  user[24];						//用户名
	CTime  CmdTime;						//操作时刻
	char  opefunc[64];					//操作项
	char  text[120];					//操作内容
}TScadaAVC_AVCCtrlEvent,*LPTScadaAVC_AVCCtrlEvent;
//AVC电压越限事件表
typedef struct TScadaAVC_AVCVoltEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//站名
	DWORD  BusID;						//母线ID
	char  BusName[64];					//母线名称
	float  val;							//电压值
	float  limit;						//电压限值
	CTime  EventTime;					//事件时间
}TScadaAVC_AVCVoltEvent,*LPTScadaAVC_AVCVoltEvent;
//AVC变压器控制事件表
typedef struct TScadaAVC_AVCTransEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//厂站名称
	DWORD  TransID;						//变压器ID
	char  TransName[64];				//变压器名称
	DWORD  WindID;						//控制绕组ID
	CTime  Optime;						//操作时间
	WORD  pretap;						//操作前档位
	WORD  afttap;						//操作后档位
	float  preVol;						//操作前电压
	float  aftVol;						//操作后电压
	char  opttype[8];					//命令类型
	BYTE  qAVC;							//AVC命令标志
	float  preHVol;						//控制前高压电压
	float  preHP;						//控制前高压有功
	float  preHQ;						//控制前高压无功
	float  preMVol;						//控制前中压电压
	float  preMP;						//控制前中压有功
	float  preMQ;						//控制前中压无功
	float  preLVol;						//控制前低压电压
	float  preLP;						//控制前低压有功
	float  preLQ;						//控制前低压无功
	float  aftHVol;						//控制后高压电压
	float  aftHP;						//控制后高压有功
	float  aftHQ;						//控制后高压无功
	float  aftMVol;						//控制后中压电压
	float  aftMP;						//控制后中压有功
	float  aftMQ;						//控制后中压无功
	float  aftLVol;						//控制后低压电压
	float  aftLP;						//控制后低压有功
	float  aftLQ;						//控制后低压无功
	CTime  EventTime;					//事件时间
}TScadaAVC_AVCTransEvent,*LPTScadaAVC_AVCTransEvent;
//AVC电容控制事件表
typedef struct TScadaAVC_AVCShuntEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//厂站名称
	DWORD  ShuntID;						//电容ID
	char  ShuntName[64];				//电容名称
	CTime  opttime;						//操作时间
	char  opttype[8];					//命令类型
	BYTE  qavc;							//AVC指令标志
	BYTE  qopen;						//操作后运行状态
	float  preVol;						//操作前电压
	float  aftVol;						//操作后电压
	CTime  EventTime;					//事件时间
}TScadaAVC_AVCShuntEvent,*LPTScadaAVC_AVCShuntEvent;
//AVC统计信息表
typedef struct TScadaAVC_AVCStateInfo
{
	DWORD  KeyID;						//序号
	DWORD  DevID;						//设备ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//设备名称
	DWORD  numall;						//日动作次数
	DWORD  numavc;						//日成功次数
	DWORD  numorder;					//日下令次数
	DWORD  numfail;						//日失败次数
	float  sucrate;						//日成功数
	CTime  timelog;						//日期时标
}TScadaAVC_AVCStateInfo,*LPTScadaAVC_AVCStateInfo;
//高软厂站表
typedef struct TScadaAVC_PasStation
{
	DWORD  ID;							//厂站ID
	char  Name[64];						//厂站名称
	DWORD  IsLand;						//岛号
	CTime  SERunTime;					//状估运行时间
	BYTE  Error_sta;					//不合格量测标志
	BYTE  Bad_sta;						//坏数据标志
	float  Se_rate;						//量测合格率
}TScadaAVC_PasStation,*LPTScadaAVC_PasStation;
//AVC运行参数表
typedef struct TScadaAVC_AVCRunParam
{
	DWORD  ID;							//序号
	CTime  srttm;						//开始时间
	CTime  endtm;						//结束时间
	WORD  Type;							//时段类型
	char  Msg[32];						//时段描述
	WORD  CPNum;						//电容可用次数
	WORD  XfrNum;						//变压器可用次数
	float  CosUp;						//关口功率因数上限
	float  CosDn;						//关口功率因数下限
	float  SCosUp;						//厂站功率因数上限
	float  SCosDn;						//厂站功率因数下限
	float  V6Up;						//6KV上限
	float  V6Dn;						//6KV下限
	float  V10Up;						//10KV上限
	float  V10Dn;						//10KV下限
	float  V35Up;						//35KV上限
	float  V35Dn;						//35KV下限
	float  V110Up;						//110KV上限
	float  V110Dn;						//110KV下限
	float  V220Up;						//220KV上限
	float  V220Dn;						//220KV下限
	float  V330Up;						//330KV上限
	float  V330Dn;						//330KV下限
	CTime  LogTime;						//数据时标
}TScadaAVC_AVCRunParam,*LPTScadaAVC_AVCRunParam;
//=================TAssessAVC===============
//高软SE参数表
typedef struct TAssessAVC_PasSEParam
{
	CTime  RunTime;						//计算时间
	BYTE  Conv_State;					//当前收敛状态
	float  Measure_Rate;				//遥测覆盖率
	float  SE_Rate;						//当前状估合格率
	char  RunInfo[86];					//运行信息
}TAssessAVC_PasSEParam,*LPTAssessAVC_PasSEParam;
//AVC厂站信息表
typedef struct TAssessAVC_AVCStation
{
	DWORD  ID;							//厂站ID
	char  Name[64];						//厂站名称
	DWORD  Zone;						//区域ID
	BYTE  CtrlOut;						//控制退出
	BYTE  AVCCtrl;						//AVC自动控制
	DWORD  CtrlID;						//控制时段编号
	WORD  Lock_Num;						//厂站闭锁当日累计
	DWORD  DevLock_Num;					//厂站设备闭锁当日累计
	float  VL;							//电压等级
	float  DVolRate;					//当日电压合格率
	float  DCosRate;					//当日功率因数合格率
	DWORD  DVAll_Time;					//日电压总时长
	DWORD  DVOut_Time;					//日电压越限时长
	DWORD  DCAll_Time;					//日功率总时长
	DWORD  DCOut_Time;					//日功率越限时长
	float  H24VolRate;					//24小时电压合格率
	float  H24CosRate;					//24小时功率合格率
	DWORD  H24VAll_Time;				//日电压总时长
	DWORD  H24VOut_Time;				//日电压越限时长
	DWORD  H24CAll_Time;				//日功率总时长
	DWORD  H24COut_Time;				//日功率越限时长
	DWORD  DActNum;						//日动作数
	DWORD  DAvcCtrlNum;					//日AVC控制数
	DWORD  DAvcActNum;					//日AVC动作数
	DWORD  H24ActNum;					//24小时动作数
	DWORD  H24AvcCtrlNum;				//日AVC控制数
	DWORD  H24AvcActNum;				//日AVC动作数
	CTime  LogTime;						//数据时标
}TAssessAVC_AVCStation,*LPTAssessAVC_AVCStation;
//AVC母线信息表
typedef struct TAssessAVC_AVCBus
{
	DWORD  BusID;						//母线ID
	DWORD  ZoneID;						//区域ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//母线名称
	float  VL;							//电压等级
	DWORD  CtrlID;						//控制时段编号
	BYTE  IsGate;						//关口标识
	BYTE  Run_Sta;						//运行状态
	BYTE  Ctr_Sta;						//是否控制
	BYTE  Cal_Sta;						//是否参与计算
	BYTE  Limit_Sta;					//越限状态
	BYTE  Lock_Sta;						//闭锁状态
	float  Volup;						//电压上限
	float  Voldn;						//电压下限
	float  Cosup;						//功率上限
	float  Cosdn;						//功率下限
	WORD  DLock_Num;					//闭锁当日累计
	WORD  DLock_Time;					//闭锁当日累计时间
	float  DVolmax;						//日电压
	float  DVolmin;						//日电压
	float  DLoadP;						//母线负荷有功
	float  DLoadQ;						//母线负荷无功
	int  DVolEvent;						//越限事件数
	int  DCtrlEvent;					//控制事件数
	float  DVol_rate;					//日电压合格率
	DWORD  DAll_Time;					//日总时长
	DWORD  DOut_Time;					//日越限时长
	WORD  H24Lock_Num;					//闭锁上日累计
	WORD  H24Lock_Time;					//闭锁上日累计时间
	float  H24Volmax;					//日电压
	float  H24Volmin;					//日电压
	int  H24VolEvent;					//越限事件数
	int  H24CtrlEvent;					//控制事件数
	float  H24Vol_rate;					//24小时电压合格率
	DWORD  H24All_Time;					//24小时总时长
	DWORD  H24Out_Time;					//24小时越限时长
	CTime  LogTime;						//当前数据时标
}TAssessAVC_AVCBus,*LPTAssessAVC_AVCBus;
//AVC变压器信息表
typedef struct TAssessAVC_AVCTrans
{
	DWORD  ID;							//变压器ID
	DWORD  ZoneID;						//区域ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//变压器名称
	DWORD  CtrlID;						//控制时段ID
	BYTE  Run_Sta;						//运行状态
	BYTE  Ctrl_Sta;						//参与控制标识
	BYTE  Lock_Sta;						//闭锁状态
	BYTE  Limit_Sta;					//越限状态
	DWORD  BusHID;						//高压母线ID
	DWORD  BusMID;						//中压母线ID
	DWORD  BusLID;						//低压母线ID
	BYTE  IsGate;						//关口变压器
	float  Cosup;						//功率上限
	float  Cosdn;						//功率下限
	WORD  DCtrlLimitNum;				//控制限值次数
	WORD  DTimeLimitNum;				//当前时段限值次数
	float  DHiP;						//高压有功
	float  DHiQ;						//高压无功
	float  DMaxS;						//日最高负载
	float  DCosRate;					//功率因数合格率
	WORD  DLock_Num;					//闭锁次数
	WORD  DLock_Time;					//闭锁当日累计时间
	float  DAll_Time;					//总时长
	float  DOut_Time;					//总时长
	DWORD  DActNum;						//日控制次数
	DWORD  DAVCCtrlNum;					//日AVC控制次数
	DWORD  DAVCActNum;					//日AVC动作次数
	WORD  H24CtrlLimit;					//日控制限值次数
	float  H24CosRate;					//24小时功率因数合格率
	float  H24MaxS;						//日最高负载
	float  H24All_Time;					//总时长
	float  H24Out_Time;					//总时长
	WORD  H24Lock_Num;					//闭锁次数
	WORD  H24Lock_Time;					//闭锁当日累计时间
	DWORD  H24ActNum;					//24小时控制次数
	DWORD  H24AVCCtrlNum;				//24小时AVC控制次数
	DWORD  H24AVCActNum;				//24小时AVC动作次数
	CTime  LogTime;						//数据时标
}TAssessAVC_AVCTrans,*LPTAssessAVC_AVCTrans;
//AVC无功设备信息表
typedef struct TAssessAVC_AVCShunt
{
	DWORD  ID;							//电容ID
	DWORD  ZoneID;						//厂站ID
	DWORD  StationID;					//厂站ID
	char  Name[64];						//电容名称
	float  VL;							//电压等级
	DWORD  CtrlID;						//控制时段ID
	BYTE  Run_Sta;						//运行状态
	BYTE  Ctrl_Sta;						//控制状态
	BYTE  Lock_Sta;						//闭锁状态
	DWORD  BreakerID;					//开关ID
	DWORD  BusID;						//控制母线ID
	DWORD  BreakID;						//控制开关ID
	WORD  DayLimitNum;					//动作次数限制
	WORD  TimeLimitNum;					//时段限制次数
	BYTE  DLock_Num;					//闭锁次数
	BYTE  DLock_Time;					//闭锁时间
	DWORD  DActNum;						//日动作数量
	DWORD  DAVCCtrlNum;					//日AVC控制数量
	DWORD  DAVCActNum;					//日AVC动作数量
	DWORD  DRunTime;					//日运行时长
	float  DAll_Time;					//总时长
	DWORD  H24ActNum;					//24小时动作数量
	DWORD  H24AVCCtrlNum;				//24小时AVC控制数量
	DWORD  H24AVCActNum;				//24小时AVC动作数量
	WORD  H24LimitNum;					//动作次数限制
	DWORD  H24RunTime;					//24小时运行时长
	float  H24All_Time;					//总时长
	BYTE  H24Lock_Num;					//闭锁次数
	BYTE  H24Lock_Time;					//闭锁时间
	CTime  LogTime;						//数据时标
}TAssessAVC_AVCShunt,*LPTAssessAVC_AVCShunt;
//AVC系统统计表
typedef struct TAssessAVC_AVCSystem
{
	CTime  SysTime;						//统计时间
	char  Name[120];					//区域名称
	BYTE  AVC_Sta;						//AVC运行状态
	BYTE  AVCCtrl_Sta;					//AVC控制状态
	BYTE  AVCAll_Time;					//AVC运行总时长
	BYTE  AVCOpen_Time;					//AVC控制退出时长
	float  Vol_rate;					//电压合格率
	float  Cos_rate;					//无功合格率
	float  Loss_P;						//当前有功网损总计
	float  Loss_Q;						//当前无功网损总计
	float  Gen_P;						//发电机有功总计
	float  Gen_Q;						//发电机无功总计
	float  Load_P;						//负荷有功总计
	float  Load_Q;						//负荷无功总计
	float  Trans_P;						//变压器有功总计
	float  Trans_Q;						//变压器无功总计
	float  Line_P;						//线路有功总计
	float  Line_Q;						//线路无功总计
	float  lossdec;						//AVC日降损量
	DWORD  AVCLock_Num;					//AVC闭锁次数数
	DWORD  DevLock_Num;					//设备闭锁次数数
	DWORD  Shunt_Ctrl;					//无功控制数
	DWORD  Trans_Ctrl;					//变压器控制数
	DWORD  CtrlAll_Num;					//控制总数
	DWORD  CtrlFail_Num;				//控制失败总数
	DWORD  CP_RefuseNum;				//容抗拒动次数
	DWORD  XF_RefuseNum;				//变压器拒动次数
	float  AvcUse_Rate;					//AVC可用率
	float  H24Vol_rate;					//电压合格率
	float  H24Cos_rate;					//无功合格率
	float  H24lossdec;					//AVC日降损量
	DWORD  H24Shunt_Ctrl;				//无功控制数
	DWORD  H24Trans_Ctrl;				//变压器控制数
	DWORD  H24Ctrl_Num;					//控制总数
	DWORD  H24Fail_Num;					//控制失败总数
	DWORD  H24CP_RefNum;				//容抗拒动次数
	DWORD  H24XF_RefNum;				//变压器拒动次数
	float  H24AvcUse_Rate;				//AVC可用率
	BYTE  H24AVC_Time;					//AVC运行总时长
	BYTE  H24Open_Time;					//AVC控制退出时长
	CTime  LogTime;						//数据时标
}TAssessAVC_AVCSystem,*LPTAssessAVC_AVCSystem;
//AVC告警定义表
typedef struct TAssessAVC_AVCWarnInfo
{
	DWORD  StationID;					//厂站ID
	DWORD  DevID;						//设备ID
	DWORD  WarnID;						//告警ID
	BYTE  WarnType;						//告警类型/保护
	char  WarnInfo[32];					//告警类型描述
	BYTE  lockstat;						//闭锁状态
	CTime  ontm;						//动作时间
	CTime  offtm;						//复归时间
}TAssessAVC_AVCWarnInfo,*LPTAssessAVC_AVCWarnInfo;
//AVC控制策略表
typedef struct TAssessAVC_AVCCtrlCmd
{
	DWORD  KeyID;						//序号
	CTime  LogTime;						//策略时间
	char  DevName[64];					//设备名称
	DWORD  StationID;					//厂站ID
	DWORD  DevID;						//设备ID
	DWORD  DevSub;						//控制设备下标
	CTime  IssTm;						//发送时刻
	CTime  CmdTm;						//执行时刻
	char  cause_info[80];				//控制原因
	char  result_info[80];				//措施
	char  Cmd_info[120];				//命令描述
	char  CmdType[8];					//命令类型
	short  CtrlType;					//操作类型
	char  rslttype[12];					//处理状态
	BYTE  qcheck;						//命令确认
	BYTE  qaut;							//自控命令
	DWORD  seq;							//命令编号
	DWORD  ZoneID;						//责任区ID
	DWORD  resp;						//责任区
}TAssessAVC_AVCCtrlCmd,*LPTAssessAVC_AVCCtrlCmd;
//AVC控制区域表
typedef struct TAssessAVC_AVCCtrlZone
{
	DWORD  KeyID;						//序号
	char  Name[64];						//区域名称
	DWORD  VovNum;						//电压考核越限数
	DWORD  QovNum;						//无功考核越限数
	float  wloss;						//区域网损值
	DWORD  NormCp;						//可控电容数
	DWORD  NormXf;						//可控变压器数
	DWORD  LockCp;						//闭锁电容数
	DWORD  LockXf;						//闭锁变压器数
	float  VarIn;						//已投入无功总容量
	float  VarOff;						//未投入无功总容量
	float  Cosfi;						//关口功率因数
	float  score;						//区域状态得分
}TAssessAVC_AVCCtrlZone,*LPTAssessAVC_AVCCtrlZone;
//AVC操作事件表
typedef struct TAssessAVC_AVCCtrlEvent
{
	DWORD  KeyID;						//序号
	char  user[24];						//用户名
	CTime  CmdTime;						//操作时刻
	char  opefunc[64];					//操作项
	char  text[120];					//操作内容
}TAssessAVC_AVCCtrlEvent,*LPTAssessAVC_AVCCtrlEvent;
//AVC电压越限事件表
typedef struct TAssessAVC_AVCVoltEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//站名
	BYTE  DevType;						//设备类型
	DWORD  DevID;						//设备ID
	char  DevName[64];					//设备名称
	float  val;							//数值
	float  limitdn;						//限值
	float  limitup;						//限值
	BYTE  ByScada;						//事件来源1来源于SCADA
	CTime  EventTime;					//事件时间
	CTime  OffTime;						//结束时间
	DWORD  CmdID;						//控制事件ID
}TAssessAVC_AVCVoltEvent,*LPTAssessAVC_AVCVoltEvent;
//AVC变压器控制事件表
typedef struct TAssessAVC_AVCTransEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//厂站名称
	DWORD  TransID;						//变压器ID
	char  TransName[64];				//变压器名称
	DWORD  WindID;						//控制绕组ID
	CTime  Optime;						//操作时间
	WORD  pretap;						//操作前档位
	WORD  afttap;						//操作后档位
	float  preVol;						//操作前电压
	float  aftVol;						//操作后电压
	char  opttype[20];					//命令类型
	BYTE  qAVC;							//AVC命令标志
	float  preHVol;						//控制前高压电压
	float  preHP;						//控制前高压有功
	float  preHQ;						//控制前高压无功
	float  preMVol;						//控制前中压电压
	float  preMP;						//控制前中压有功
	float  preMQ;						//控制前中压无功
	float  preLVol;						//控制前低压电压
	float  preLP;						//控制前低压有功
	float  preLQ;						//控制前低压无功
	float  aftHVol;						//控制后高压电压
	float  aftHP;						//控制后高压有功
	float  aftHQ;						//控制后高压无功
	float  aftMVol;						//控制后中压电压
	float  aftMP;						//控制后中压有功
	float  aftMQ;						//控制后中压无功
	float  aftLVol;						//控制后低压电压
	float  aftLP;						//控制后低压有功
	float  aftLQ;						//控制后低压无功
	BYTE  ByScada;						//事件来源1来源于SCADA
	CTime  EventTime;					//事件时间
	DWORD  CmdID;						//控制事件ID
}TAssessAVC_AVCTransEvent,*LPTAssessAVC_AVCTransEvent;
//AVC电容控制事件表
typedef struct TAssessAVC_AVCShuntEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//厂站名称
	DWORD  ShuntID;						//电容ID
	char  ShuntName[64];				//电容名称
	CTime  opttime;						//操作时间
	char  opttype[20];					//命令类型
	BYTE  qavc;							//AVC指令标志
	BYTE  qopen;						//操作后运行状态
	float  preVol;						//操作前电压
	float  aftVol;						//操作后电压
	BYTE  ByScada;						//事件来源1来源于SCADA
	CTime  EventTime;					//事件时间
	DWORD  CmdID;						//控制事件ID
}TAssessAVC_AVCShuntEvent,*LPTAssessAVC_AVCShuntEvent;
//AVC运行参数表
typedef struct TAssessAVC_AVCRunParam
{
	DWORD  ID;							//序号
	CTime  srttm;						//开始时间
	CTime  endtm;						//结束时间
	WORD  Type;							//时段类型
	char  Msg[32];						//时段描述
	WORD  CPNum;						//电容可用次数
	WORD  XfrNum;						//变压器可用次数
	float  CosUp;						//关口功率因数上限
	float  CosDn;						//关口功率因数下限
	float  SCosUp;						//厂站功率因数上限
	float  SCosDn;						//厂站功率因数下限
	float  V6Up;						//6KV上限
	float  V6Dn;						//6KV下限
	float  V10Up;						//10KV上限
	float  V10Dn;						//10KV下限
	float  V35Up;						//35KV上限
	float  V35Dn;						//35KV下限
	float  V110Up;						//110KV上限
	float  V110Dn;						//110KV下限
	float  V220Up;						//220KV上限
	float  V220Dn;						//220KV下限
	float  V330Up;						//330KV上限
	float  V330Dn;						//330KV下限
	CTime  LogTime;						//数据时标
}TAssessAVC_AVCRunParam,*LPTAssessAVC_AVCRunParam;
//AVC时段定义表
typedef struct TAssessAVC_AVCTimePart
{
	DWORD  ID;							//序号
	char  Name[64];						//时段名称
	float  VUp1;						//电压上限1
	float  VDn1;						//电压下限1
	float  CP_Num1;						//电容可控次数1
	float  XF_Num1;						//变压器可控次数1
	float  CosUp1;						//功率因数上限1
	float  CosDn1;						//功率因数下限1
	CTime  Tm1;							//时段1分割点
	float  VUp2;						//电压上限2
	float  VDn2;						//电压下限2
	float  CP_Num2;						//电容可控次数2
	float  XF_Num2;						//变压器可控次数2
	float  CosUp2;						//功率因数上限2
	float  CosDn2;						//功率因数下限2
	CTime  Tm2;							//时段2分割点
	float  VUp3;						//电压上限3
	float  VDn3;						//电压下限3
	float  CP_Num3;						//电容可控次数3
	float  XF_Num3;						//变压器可控次数3
	float  CosUp3;						//功率因数上限3
	float  CosDn3;						//功率因数下限3
	CTime  Tm3;							//时段3分割点
	float  VUp4;						//电压上限4
	float  VDn4;						//电压下限4
	float  CP_Num4;						//电容可控次数4
	float  XF_Num4;						//变压器可控次数4
	float  CosUp4;						//功率因数上限4
	float  CosDn4;						//功率因数下限4
	CTime  Tm4;							//时段4分割点
	float  VUp5;						//电压上限5
	float  VDn5;						//电压下限5
	float  CP_Num5;						//电容可控次数5
	float  XF_Num5;						//变压器可控次数5
	float  CosUp5;						//功率因数上限5
	float  CosDn5;						//功率因数下限5
	CTime  Tm5;							//时段1分割点
	float  VUp6;						//电压上限6
	float  VDn6;						//电压下限6
	float  CP_Num6;						//电容可控次数6
	float  XF_Num6;						//变压器可控次数6
	float  CosUp6;						//功率因数上限6
	float  CosDn6;						//功率因数下限6
	CTime  LogTime;						//数据时标
}TAssessAVC_AVCTimePart,*LPTAssessAVC_AVCTimePart;
//AVC网损事件表
typedef struct TAssessAVC_AVCLossEvent
{
	DWORD  KeyID;						//序号
	DWORD  StationID;					//厂站ID
	char  StationName[64];				//站名
	char  Name[64];						//描述
	float  val1;						//网损值1
	float  val2;						//网损值2
	BYTE  ByScada;						//事件来源1来源于SCADA
	CTime  EventTime;					//事件时间
	DWORD  CmdID;						//控制事件ID
}TAssessAVC_AVCLossEvent,*LPTAssessAVC_AVCLossEvent;
//AVC实时运行性能表
typedef struct TAssessAVC_RealAVCCapably
{
	DWORD  NU;							//序号
	char  Type[64];						//性能类别
	char  Name[64];						//描述
	float  Value;						//数值
}TAssessAVC_RealAVCCapably,*LPTAssessAVC_RealAVCCapably;
#endif