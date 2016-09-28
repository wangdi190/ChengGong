#if !defined(_DB_STRUCT_H_)
#define _DB_STRUCT_H_
/************************************************/
//本头文件由“数据库设计软件”自动生成
//2013-7-6
//星海高科技产业股份有限公司
/************************************************/
//掩码预定义值
//=================可视化电力系统库===============
//PT表
typedef struct visualpw_PT
{
	DWORD  NU;							//PT编号
	char  Name[64];						//PT名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[32];						//标识
}visualpw_PT,*LPvisualpw_PT;
//发电机
typedef struct visualpw_Gen
{
	DWORD  NU;							//发电机号
	char  Name[64];						//发电机名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  vl;							//电压等级
	BYTE  Type;							//类型
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
	float  angle;						//角度
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	float  Qmax;						//最大可用无功
	float  Qmaxi;						//最大进相无功
	int  Synsta;						//综合状态
	char  ID[32];						//标识
	DWORD  Node;						//节点
	char  ControlArea[32];				//调度关系
	float  UtilizationHou;				//利用小时数
	float  Suffocate;					//受阻容量
	float  Electrovalency;				//机组电价
	CTime  OperationTime;				//投产时间
	BYTE  AGCsta;						//AGC状态
	float  TimingSpeed;					//电机调速速率
	float  TimingSpeed1;				//电机下爬坡率
	float  UpWhirl;						//上旋备用
	float  DownWhirl;					//下旋备用
	float  WindSpeed;					//风速
	float  WindPath;					//风向
}visualpw_Gen,*LPvisualpw_Gen;
//开关刀闸
typedef struct visualpw_Switch
{
	DWORD  NU;							//开关编号
	char  Name[64];						//开关名字
	DWORD  Station;						//所属站
	float  vl;							//电压等级
	BYTE  Type;							//类型
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//开关状态
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	int  Synsta;						//综合状态
	char  ID[32];						//标识
	DWORD  Node1;						//节点1
	DWORD  Node2;						//节点2
	CTime  ShiftTime;					//变位时间
}visualpw_Switch,*LPvisualpw_Switch;
//负荷
typedef struct visualpw_Load
{
	DWORD  NU;							//负荷编号
	char  Name[64];						//负荷名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  vl;							//电压等级
	float  MaxP;						//有功上限
	float  MinP;						//有功下限
	float  P;							//有功负荷
	float  Q;							//无功负荷
	float  I;							//电流
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	int  Synsta;						//综合状态
	char  ID[32];						//标识
	DWORD  Node;						//节点
}visualpw_Load,*LPvisualpw_Load;
//电容
typedef struct visualpw_Shunt
{
	DWORD  NU;							//电容设备编号
	char  Name[64];						//电容设备名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  vl;							//电压等级
	float  Q;							//投入无功
	float  Qmax;						//最大无功输出
	float  I;							//电流
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	float  Qchk;						//检修容量
	int  Synsta;						//综合状态
	char  ID[32];						//标识
	DWORD  Node1;						//节点1
	DWORD  Node2;						//节点2
}visualpw_Shunt,*LPvisualpw_Shunt;
//电抗
typedef struct visualpw_Sreact
{
	DWORD  NU;							//电抗器变号
	char  Name[64];						//电抗器名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  vl;							//电压等级
	float  Qmax;						//最大无功输出
	float  Zx;							//投入电抗
	float  I;							//电流
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	int  Synsta;						//综合状态
	char  ID[32];						//标识
	DWORD  Node1;						//节点1
	DWORD  Node2;						//节点2
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
	float  vl_H;						//高压侧电压等级
	float  vl_L;						//低压侧电压等级
	float  tap;							//变压器分接头
	float  Pmax;						//变压器最大容量
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
	int  Synsta;						//综合状态
	char  ID[32];						//标识
	DWORD  Node1;						//节点1
	DWORD  Node2;						//节点2
	float  UtilizationHou;				//利用小时数
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
	float  vl_H;						//高压侧电压等级
	float  vl_M;						//中压侧电压等级
	float  vl_L;						//低压侧电压等级
	float  TapH;						//高端分接头位置
	float  TapM;						//中端分接头位置
	float  TapL;						//低端分接头位置
	float  Pmax;						//变压器最大容量
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
	int  Synsta;						//综合状态
	char  ID[32];						//标识
	DWORD  NodeH;						//高压节点
	DWORD  NodeM;						//中压节点
	DWORD  NodeL;						//低压节点
	float  UtilizationHou;				//利用小时数
}visualpw_Tfm2,*LPvisualpw_Tfm2;
//静态无功补偿
typedef struct visualpw_SVC
{
	DWORD  NU;							//SVC编号
	char  Name[24];						//SVC名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Qmax;						//最大无功输出
	float  Qmin;						//最小无功输出
	float  Q;							//无功输出
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  Tsta;							//故障状态
	char  ID[32];						//标识
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
	DWORD  Node;						//节点
	float  PreVlo;						//预警使用的下限
	float  vl;							//电压等级
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
	int  Synsta;						//综合状态
	char  ID[32];						//标识
}visualpw_Bus,*LPvisualpw_Bus;
//交流线
typedef struct visualpw_Line
{
	DWORD  NU;							//交流线编号
	char  Name[64];						//交流线名称
	DWORD  Station;						//所属站
	int  Zonef;							//起始区域域号
	int  Zonet;							//终点区域域号
	float  vl;							//电压等级
	float  Imax;						//电流最大值
	float  MaxP;						//有功上限
	float  Par;							//输电线负载率告警限
	float  CurPar;						//当前使用的告警率
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
	int  Synsta;						//综合状态
	char  ID[32];						//标识
	DWORD  NodeF;						//首端节点
	DWORD  NodeT;						//末端节点
}visualpw_Line,*LPvisualpw_Line;
//直流线
typedef struct visualpw_DCLine
{
	DWORD  NU;							//直流线编号
	char  Name[24];						//直流线名称
	DWORD  Station;						//所属站
	int  Zonef;							//起始区域域号
	int  Zonet;							//终点区域域号
	float  Imax;						//电流最大值
	float  Maxp;						//有功上限
	float  Par;							//输电线负载率告警限
	float  CurPar;						//当前使用的告警率
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
	char  ID[32];						//标识
	DWORD  NodeF;						//首端节点
	DWORD  NodeT;						//末端节点
}visualpw_DCLine,*LPvisualpw_DCLine;
//逆变器、变流器
typedef struct visualpw_CVT
{
	DWORD  NU;							//设备编号
	char  Name[24];						//设备名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  Tsta;							//故障状态
	char  ID[32];						//标识
}visualpw_CVT,*LPvisualpw_CVT;
//区域
typedef struct visualpw_Zone
{
	DWORD  NU;							//区域编号
	char  Name[64];						//区域名称
	float  progen_generat;				//省调机组总出力
	float  total_load;					//全网总负荷
	float  UpSpare;						//实时上旋备用
	float  DownSpare;					//实时下旋备用
	float  progenvalue;					//省调装机容量
	float  transvalue;					//地区变电容量
	char  ID[32];						//标识
	DWORD  TxtColor;					//文字颜色
	DWORD  BKColor;						//填充颜色
}visualpw_Zone,*LPvisualpw_Zone;
//站
typedef struct visualpw_Station
{
	DWORD  NU;							//站号
	char  Name[64];						//站名
	DWORD  zoneNU;						//所属区域
	BYTE  Type;							//厂站类型
	float  vl;							//电压等级
	int  Synsta;						//综合状态
	char  ID[32];						//标识
	char  ControlArea[32];				//调度关系
	BYTE  Property;						//产权
	char  Subjection[32];				//所属集团
	float  LastPower;					//存煤水位
	CTime  LastPowerRTime;				//存煤水位上报时间
	float  LastPowerTime;				//存煤水位使用时间(小时)
	char  PW0FileName[32];				//厂站对应PW0文件名
	float  PowerMeterGen;				//日发电量
	float  PowerMeterLoad;				//日用电量
}visualpw_Station,*LPvisualpw_Station;
//按节点电压排序
typedef struct visualpw_VotOutage
{
	int  NU;							//设备编号
	char  type;							//设备类型
	float  Defl;						//电压偏移量
}visualpw_VotOutage,*LPvisualpw_VotOutage;
//按支路排序
typedef struct visualpw_LineOutage
{
	int  NU;							//设备编号
	char  type;							//类型
	float  Defl;						//电压偏移量
}visualpw_LineOutage,*LPvisualpw_LineOutage;
//节点电压和支路合成
typedef struct visualpw_AllOutage
{
	int  NU;							//设备编号
	char  type;							//类型
	float  Defl;						//过载量
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
//ACE
typedef struct visualpw_ACE
{
	DWORD  ID;							//标识ID
	float  CurVal;						//当前值
	CTime  datatime;					//数据时间
	BYTE  alarm;						//告警
	BYTE  ack;							//确认
	float  Index;						//指标
}visualpw_ACE,*LPvisualpw_ACE;
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
	char  Name[24];						//名称
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
	char  Name[64];						//分区名称
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
	int  Synsta;						//综合状态
}visualpw_Area,*LPvisualpw_Area;
//应用参数
typedef struct visualpw_AppParam
{
	float  OverRate;					//重载率
	float  HisMaxLoad;					//历史最大负荷
}visualpw_AppParam,*LPvisualpw_AppParam;
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
//检修表
typedef struct visualpw_DevRepair
{
	CTime  RecTime;						//登记时间
	DWORD  DevNU;						//设备编号
	BYTE  DevType;						//设备类型
	DWORD  Station;						//厂站
	CTime  StartTime;					//检修起始时间
	CTime  EndTime;						//检修结束时间
	BYTE  State;						//有效标识
	char  Comment[512];					//注释内容
	DWORD  GroundDevNU;					//接地设备编号
	BYTE  GroundDevType;				//接地设备类型
}visualpw_DevRepair,*LPvisualpw_DevRepair;
//挂牌表
typedef struct visualpw_SignBrand
{
	CTime  RecTime;						//登记时间
	BYTE  SignType;						//挂牌类型
	DWORD  DevNU;						//设备编号
	BYTE  DevType;						//设备类型
	BYTE  State;						//有效标识
	char  Comment[512];					//注释内容
	DWORD  GroundDevNU;					//接地设备编号
	BYTE  GroundDevType;				//接地设备类型
}visualpw_SignBrand,*LPvisualpw_SignBrand;
//保护信息表
typedef struct visualpw_Protector
{
	DWORD  DNu;							//保护设备编号
	char  Name[64];						//保护名称
	DWORD  Station;						//厂站
	BYTE  DevType;						//关联设备类别
	BYTE  Alarm;						//告警级别
	BYTE  State;						//告警状态
	char  Comment[256];					//标注信息
	CTime  EventTime;					//保护动作时间
	short  MilliSecond;					//保护动作时间(毫秒)
}visualpw_Protector,*LPvisualpw_Protector;
//压板信息表
typedef struct visualpw_KeepPlate  
{
	DWORD  NU;							//压板编号
	DWORD  Station;						//所在厂站
	DWORD  Border;						//所在屏柜
	char  Name[64];						//压板名称
	BYTE  State;						//压板投退状态
	BYTE  MisState;						//压板误投退状态
	DWORD  StatePos;					//压板投退状态点号
	DWORD  MisStatePos;					//压板误投退状态点号
}visualpw_KeepPlate  ,*LPvisualpw_KeepPlate  ;
//负荷预测风电预测表
typedef struct visualpw_ForcastPlan
{
	CTime  PlanTime;					//计划产生时间
	BYTE  PlanType;						//计划类型（预测、计划）
	DWORD  DevID;						//预测计划设备ID
	float  PlanValue;					//预测计划值
	DWORD  Index;						//计划序号
	float  RealValue;					//实际值
	float  LastValue;					//昨日值
}visualpw_ForcastPlan,*LPvisualpw_ForcastPlan;
//机组计划表
typedef struct visualpw_GenPlan
{
	CTime  PlanTime;					//计划时间
	DWORD  GenID;						//机组对象
	double  PlanValue;					//计划值
	float  RealValue;					//实际值
	float  LastValue;					//昨日值
}visualpw_GenPlan,*LPvisualpw_GenPlan;
//系统数据表
typedef struct visualpw_SystemData
{
	DWORD  ID;							//序号
	char  Name[64];						//名称
	float  Value;						//数值
	float  MaxValue;					//最大限值
	float  MinValue;					//最小限值
	char  Unit[32];						//数值单位
}visualpw_SystemData,*LPvisualpw_SystemData;
//AGC表
typedef struct visualpw_AGC
{
	DWORD  NU;							//编号
	char  Name[64];						//机组名称
	float  MaxP;						//装机容量
	float  Index;						//调节性能
}visualpw_AGC,*LPvisualpw_AGC;
//接地刀闸
typedef struct visualpw_GND
{
	DWORD  NU;							//开关编号
	char  Name[64];						//开关名字
	DWORD  Station;						//所属站
	float  vl;							//电压等级
	BYTE  Type;							//类型
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//开关状态
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	int  Synsta;						//综合状态
	char  ID[32];						//标识
	DWORD  Node1;						//节点1
	DWORD  Node2;						//节点2
	CTime  ShiftTime;					//变位时间
}visualpw_GND,*LPvisualpw_GND;
//事故影响
typedef struct visualpw_CtgEffect
{
	DWORD  CtgNU;						//事故设备号
	char  CtgName[64];					//事故设备名
	int  CtgType;						//事故设备类型
	float  fSecurity;					//风险指标
	DWORD  EftNU;						//异态设备号
	char  EftName[64];					//异态设备名
	int  EftType;						//异态设备类型
	float  EftVal;						//异态程度
}visualpw_CtgEffect,*LPvisualpw_CtgEffect;
//二次保护设备状态表
typedef struct visualpw_RelayDevState
{
	DWORD  NU;							//设备编号
	char  Name[64];						//二次设备名称
	DWORD  Station;						//所在厂站
	char  RelayType[32];				//二次设备类型
	DWORD  DevNU;						//所属一次设备对象
	BYTE  DevType;						//一次设备类型
	BYTE  Sta;							//保护设备状态
	char  ID[32];						//保护设备标识
	CTime  LastTime;					//最后动作时间
	char  Comment[72];					//最后动作内容
}visualpw_RelayDevState,*LPvisualpw_RelayDevState;
//电量信息
typedef struct visualpw_PowerMeter
{
	DWORD  ID;							//编号
	char  egp[32];						//查询关键字
	char  Name[64];						//名称
	float  Value;						//电量
	CTime  LastTime;					//记录时间
	BYTE  PowerType;					//电量类型（用、发）
	char  Unit[24];						//单位
	BYTE  AttrType;						//归属对象类型
	DWORD  AttrID;						//归属对象内存库编号
}visualpw_PowerMeter,*LPvisualpw_PowerMeter;
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
//灵敏度结果表
typedef struct common_Sen
{
	DWORD  NU;							//设备相关ID
	char  Name[64];						//设备名称
	BYTE  type;							//设备类型
	float  senval;						//灵敏度值
	DWORD  NU_N1;						//N1设备
	char  Name_N1[64];					//N1设备名称
	BYTE  Type_N1;						//N1设备类型
	CTime  ReTimer;						//产生时间
}common_Sen,*LPcommon_Sen;
//实时负荷预测8点
typedef struct common_FLoad
{
	BYTE  FType;						//预测类型
	float  FValue;						//负荷预测值
	float  RValue;						//负荷实际值
	CTime  hour;						//预测值时间
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
	DWORD  MNu;							//序号
	DWORD  VNu1;						//可视化中的设备ID1
	char  MName[64];					//量测名称
	char  VName1[64];					//设备名称1
	char  MeasID[64];					//量测标识
	BYTE  DevType1;						//设备类型1
	BYTE  MeasType;						//量测类型
	BYTE  MeasPos1;						//量测位置1
	DWORD  Station;						//所属站号
	BYTE  quality;						//质量标志
	DWORD  VNu2;						//可视化中的设备ID2
	char  VName2[64];					//设备名称2
	BYTE  DevType2;						//设备类型2
	BYTE  MeasPos2;						//量测位置2
}common_Relation,*LPcommon_Relation;
//预定义断面潮流
typedef struct common_PreDefSF
{
	DWORD  ID;							//断面ID
	char  Name[45];						//断面名字
	float  curval;						//当前断面值
	float  Vmax;						//断面容量大值
	float  Vmin;						//断面容量小值
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
//字段说明
typedef struct common_Field
{
	DWORD  shTableNo;					//表编号
	short  shFieldNo;					//字段编号
	char  szFieldName[50];				//字段名
	BYTE  byDataType;					//数据类型
	short  shFieldAttrib;				//属性
	float  szDefaultVal;				//缺省值
	float  szMaxVal;					//最大值
	float  szMinVal;					//最小值
	char  szEnumString[100];				//枚举字符串
}common_Field,*LPcommon_Field;
//非量测表
typedef struct common_UnEquMeas
{
	DWORD  NU;							//编号
	char  Name[64];						//名称
	float  max;							//最大值
	float  min;							//最小值
	float  val;							//值
	BYTE  type;							//量测类型
	char  ID[64];						//标识
	char  PID[64];						//父标识
	DWORD  Station;						//所属站号
}common_UnEquMeas,*LPcommon_UnEquMeas;
//子对象表
typedef struct common_SubObject
{
	DWORD  NU;							//序号
	char  Name[64];						//名称
	char  ID[64];						//对象标识
	BYTE  Type;							//对象类型
	DWORD  Station;						//厂站
	DWORD  PNU;							//父设备号
	BYTE  PType;						//父设备类型
}common_SubObject,*LPcommon_SubObject;
//环境表
typedef struct common_Environment
{
	BYTE  EnType;						//环境类型
	CTime  RecTime;						//信息时间
	char  Comment[128];					//标注信息
	BYTE  State;						//环境状态
	float  PosX;						//坐标位置X
	float  PosY;						//坐标位置Y
	float  Length;						//坐标长
	float  Width;						//坐标高
	char  SourcePath[128];				//资源路径
}common_Environment,*LPcommon_Environment;
//气象表
typedef struct common_Meteor
{
	BYTE  MeType;						//气象类型
	CTime  RecTime;						//信息时间
	char  Comment[128];					//标注信息
	DWORD  ZoneNU;						//区域编号
	BYTE  State;						//环境状态
	float  PosX;						//坐标位置X
	float  PosY;						//坐标位置Y
	float  Length;						//坐标长
	float  Width;						//坐标高
	char  SourcePath[128];				//资源路径
}common_Meteor,*LPcommon_Meteor;
//和谐日数据
typedef struct common_HexieD
{
	DWORD  NameID;						//编号
	char  Name[64];						//名称
	CTime  Time1;						//时间
	float  Value;						//数值
}common_HexieD,*LPcommon_HexieD;
//和谐年月数据
typedef struct common_HexieYM
{
	DWORD  NameID;						//编号
	BYTE  Type;							//类型(月、年)
	char  Name[64];						//名称
	CTime  Time1;						//时间
	float  Value;						//数值
}common_HexieYM,*LPcommon_HexieYM;
//电网装机变电统计表
typedef struct common_GenTransSta
{
	DWORD  ID;							//编号
	char  Name[64];						//名称
	WORD  DevNumber;					//设备台数
	float  Capacity;					//容量
	DWORD  OwnerID;						//父设备ID
	char  Type[16];						//类型
}common_GenTransSta,*LPcommon_GenTransSta;
//接口应用状态表
typedef struct common_InterfaceAppSt
{
	WORD  ID;							//接口编号
	char  Name[64];						//接口名称
	char  NameExe[64];					//接口程序名称
	char  InterfaceSta[10];				//接口状态
	char  AppName[64];					//应用名称
	BYTE  AppSta;						//应用状态
	BYTE  AppDataSta;					//应用数据处理状态
	CTime  AppRunTime;					//应用数据更新时间
	char  AppInfomation[255];				//应用运行描述
}common_InterfaceAppSt,*LPcommon_InterfaceAppSt;
//系统颜色表
typedef struct common_SystemColor
{
	DWORD  ID;							//颜色编号
	char  Name[64];						//颜色描述
	DWORD  Color;						//正常颜色
	DWORD  AlarmColor;					//告警颜色
}common_SystemColor,*LPcommon_SystemColor;
//接口应用状态表三区
typedef struct common_IIIAppSt
{
	WORD  ID;							//接口编号
	char  Name[64];						//接口名称
	char  NameExe[64];					//接口程序名称
	char  InterfaceSta[10];				//接口状态
	char  AppName[64];					//应用名称
	BYTE  AppSta;						//应用状态
	BYTE  AppDataSta;					//应用数据处理状态
	CTime  AppRunTime;					//应用数据更新时间
	char  AppInfomation[255];				//应用运行描述
}common_IIIAppSt,*LPcommon_IIIAppSt;
//快捷键定义
typedef struct common_KeyBoard
{
	BYTE  ControlObject;				//控制目标(1W,2V)
	char  CtrlInfo[32];					//说明
	char  AcceKey[5];					//快捷键
	char  ModifyKey[17];				//组合键
	char  CtrlParam[32];				//控制参数
}common_KeyBoard,*LPcommon_KeyBoard;
//=================低频震荡采集装置===============
//低频震荡线路
typedef struct pmu_lfline
{
	DWORD  LineID;						//线路ID
	BYTE  Type;							//类型交流或直流
	BYTE  LFsta;						//低频振荡状态
	CTime  StartTime;					//起始时间
	CTime  EndTime;						//结束时间
	float  LFFreq;						//振荡频率
	float  LFValue;						//振荡幅值
}pmu_lfline,*LPpmu_lfline;
//pmu数据服务器配置
typedef struct pmu_pmusvr
{
	DWORD  ip;							//服务器IP地址
	WORD  port;							//服务器口号
}pmu_pmusvr,*LPpmu_pmusvr;
//=================水电数据库===============
//水库数据库
typedef struct waterele_reservoir
{
	WORD  ID;							//水库标识
	char  Name[24];						//水库名称
	int  GenNU;							//关联发电机ID
	float  Uplevel;						//上游水位
	float  DownLevel;					//下游水位
	float  WaterInput;					//来水量
	float  P;							//有功出力
	float  WaterUse;					//引用流量
}waterele_reservoir,*LPwaterele_reservoir;
//=================研究态===============
//PT表
typedef struct studypw_PT
{
	DWORD  NU;							//PT编号
	char  Name[24];						//PT名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[32];						//标识
}studypw_PT,*LPstudypw_PT;
//发电机
typedef struct studypw_Gen
{
	DWORD  NU;							//发电机号
	char  Name[24];						//发电机名
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
	float  angle;						//角度
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	float  Qmax;						//最大可用无功
	float  Qmaxi;						//最大进相无功
	BYTE  Tsta;							//故障状态
	char  ID[32];						//标识
}studypw_Gen,*LPstudypw_Gen;
//开关刀闸
typedef struct studypw_Switch
{
	DWORD  NU;							//开关编号
	char  Name[24];						//开关名字
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//开关状态
	CTime  rptm1;						//检修开始时间
	CTime  rptm2;						//检修结束时间
	BYTE  Tsta;							//故障状态
	char  ID[32];						//标识
}studypw_Switch,*LPstudypw_Switch;
//负荷
typedef struct studypw_Load
{
	DWORD  NU;							//负荷编号
	char  Name[24];						//负荷名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  MaxP;						//有功上限
	float  MinP;						//有功下限
	float  P;							//有功负荷
	float  Q;							//无功负荷
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[32];						//标识
}studypw_Load,*LPstudypw_Load;
//电容
typedef struct studypw_Shunt
{
	DWORD  NU;							//电容设备编号
	char  Name[24];						//电容设备名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Q;							//投入无功
	float  Qmax;						//最大无功输出
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	float  Qchk;						//检修容量
	BYTE  Tsta;							//故障状态
	char  ID[32];						//标识
}studypw_Shunt,*LPstudypw_Shunt;
//电抗
typedef struct studypw_Sreact
{
	DWORD  NU;							//电抗器变号
	char  Name[24];						//电抗器名
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Zx;							//投入电抗
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  Tsta;							//故障状态
	char  ID[32];						//标识
}studypw_Sreact,*LPstudypw_Sreact;
//2绕组变压器
typedef struct studypw_Tfm1
{
	DWORD  NU;							//2绕变编号
	char  Name[24];						//2绕变名
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
	char  ID[32];						//标识
}studypw_Tfm1,*LPstudypw_Tfm1;
//3绕组变压器
typedef struct studypw_Tfm2
{
	DWORD  NU;							//3绕变编号
	char  Name[24];						//3绕变名
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
	char  ID[32];						//标识
}studypw_Tfm2,*LPstudypw_Tfm2;
//静态无功补偿
typedef struct studypw_SVC
{
	DWORD  NU;							//SVC编号
	char  Name[24];						//SVC名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	float  Qmax;						//最大无功输出
	float  Qmin;						//最小无功输出
	float  Q;							//无功输出
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  Tsta;							//故障状态
	char  ID[32];						//标识
}studypw_SVC,*LPstudypw_SVC;
//母线
typedef struct studypw_Bus
{
	DWORD  NU;							//母线编号
	char  Name[24];						//母线名称
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
	char  ID[32];						//标识
}studypw_Bus,*LPstudypw_Bus;
//交流线
typedef struct studypw_Line
{
	DWORD  NU;							//交流线编号
	char  Name[24];						//交流线名称
	DWORD  Station;						//所属站
	int  Zonef;							//起始区域域号
	int  Zonet;							//终点区域域号
	float  Imax;						//电流最大值
	float  MaxP;						//有功上限
	float  Par;							//输电线负载率告警限
	float  CurPar;						//当前使用的告警率
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
	char  ID[32];						//标识
}studypw_Line,*LPstudypw_Line;
//直流线
typedef struct studypw_DCLine
{
	DWORD  NU;							//直流线编号
	char  Name[24];						//直流线名称
	DWORD  Station;						//所属站
	int  Zonef;							//起始区域域号
	int  Zonet;							//终点区域域号
	float  Imax;						//电流最大值
	float  Maxp;						//有功上限
	float  Par;							//输电线负载率告警限
	float  CurPar;						//当前使用的告警率
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
	char  ID[32];						//标识
}studypw_DCLine,*LPstudypw_DCLine;
//逆变器、变流器
typedef struct studypw_CVT
{
	DWORD  NU;							//设备编号
	char  Name[24];						//设备名称
	DWORD  Station;						//所属站
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	BYTE  Tsta;							//故障状态
	char  ID[32];						//标识
}studypw_CVT,*LPstudypw_CVT;
//接地
typedef struct studypw_GND
{
	DWORD  NU;							//接地编号
	char  Name[24];						//接地名称
	DWORD  Station;						//所属站号
	int  ZoneNU;						//所属区域号
	BYTE  ele;							//带电状态
	BYTE  sta;							//运行状态
	char  ID[32];						//标识
}studypw_GND,*LPstudypw_GND;
//区域
typedef struct studypw_Zone
{
	DWORD  NU;							//区域编号
	char  Name[24];						//区域名称
	float  total_los;					//有功损耗
	float  total_gen;					//有功发电
	float  demand;						//有功需求
	float  cost;						//单位发电额费用
	float  curlr;						//当前负荷率
	float  lastlr;						//上次负荷率
	float  nextlr;						//未来负荷率
	char  ID[32];						//标识
}studypw_Zone,*LPstudypw_Zone;
//站
typedef struct studypw_Station
{
	DWORD  NU;							//站号
	char  Name[24];						//站名
	DWORD  zoneNU;						//所属区域
	char  ID[32];						//标识
}studypw_Station,*LPstudypw_Station;
//按节点电压排序
typedef struct studypw_VotOutage
{
	int  NU;							//设备编号
	char  type;							//设备类型
	float  Defl;						//电压偏移量
}studypw_VotOutage,*LPstudypw_VotOutage;
//按支路排序
typedef struct studypw_LineOutage
{
	int  NU;							//设备编号
	char  type;							//类型
	float  Defl;						//电压偏移量
}studypw_LineOutage,*LPstudypw_LineOutage;
//节点电压和支路合成
typedef struct studypw_AllOutage
{
	int  NU;							//设备编号
	char  type;							//类型
	float  Defl;						//过载量
}studypw_AllOutage,*LPstudypw_AllOutage;
//按节点电压排序
typedef struct studypw_VotOutagef
{
	int  NU;							//设备编号
	char  type;							//设备类型
	float  Defl;						//电压偏移量
}studypw_VotOutagef,*LPstudypw_VotOutagef;
//按支路排序
typedef struct studypw_LineOutagef
{
	int  NU;							//设备编号
	char  type;							//设备类型
	float  Defl;						//电压偏移量
}studypw_LineOutagef,*LPstudypw_LineOutagef;
//节点电压和支路合成
typedef struct studypw_AllOutagef
{
	int  NU;							//设备编号
	char  type;							//设备类型
	float  Defl;						//电压偏移量
}studypw_AllOutagef,*LPstudypw_AllOutagef;
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
	char  Name[24];						//名称
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
//应用参数
typedef struct studypw_AppParam
{
	float  OverRate;					//重载率
	float  HisMaxLoad;					//历史最大负荷
}studypw_AppParam,*LPstudypw_AppParam;
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
//=================三区临时表===============
//压板信息表
typedef struct IIIzone_KeepPlate  
{
	DWORD  NU;							//压板编号
	DWORD  Station;						//所在厂站
	DWORD  Border;						//所在屏柜
	char  Name[64];						//压板名称
	BYTE  State;						//压板投退状态
	BYTE  MisState;						//压板误投退状态
	DWORD  StatePos;					//压板投退状态点号
	DWORD  MisStatePos;					//压板误投退状态点号
}IIIzone_KeepPlate  ,*LPIIIzone_KeepPlate  ;
//环境表
typedef struct IIIzone_Environment
{
	BYTE  EnType;						//环境类型
	CTime  RecTime;						//信息时间
	char  Comment[128];					//标注信息
	BYTE  State;						//环境状态
	float  PosX;						//坐标位置X
	float  PosY;						//坐标位置Y
	float  Length;						//坐标长
	float  Width;						//坐标高
	char  SourcePath[128];				//资源路径
}IIIzone_Environment,*LPIIIzone_Environment;
//气象表
typedef struct IIIzone_Meteor
{
	BYTE  MeType;						//气象类型
	CTime  RecTime;						//信息时间
	char  Comment[128];					//标注信息
	DWORD  ZoneNU;						//区域编号
	BYTE  State;						//环境状态
	float  PosX;						//坐标位置X
	float  PosY;						//坐标位置Y
	float  Length;						//坐标长
	float  Width;						//坐标高
	char  SourcePath[128];				//资源路径
}IIIzone_Meteor,*LPIIIzone_Meteor;
//接口应用状态表三区
typedef struct IIIzone_IIIAppSt
{
	WORD  ID;							//接口编号
	char  Name[64];						//接口名称
	char  NameExe[64];					//接口程序名称
	char  InterfaceSta[10];				//接口状态
	char  AppName[64];					//应用名称
	BYTE  AppSta;						//应用状态
	BYTE  AppDataSta;					//应用数据处理状态
	CTime  AppRunTime;					//应用数据更新时间
	char  AppInfomation[255];				//应用运行描述
}IIIzone_IIIAppSt,*LPIIIzone_IIIAppSt;
#endif