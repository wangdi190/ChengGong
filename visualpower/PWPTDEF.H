#if !defined(AFX_PWPTDEF_H__INCLUDED_)
#define AFX_PWPTDEF_H__INCLUDED_

#include "jhsyslibl.h"
#include "shockwaveflash.h"


#define  MAXPAGE  128
#define  MAXSPIC  64
#define  MAXEGRP  256
#define  MAXGIF   64
#define  MAXLAYER 8
#define  MAXUNDO  64
#define  MAXCONTOUR    1200
#define  MAXSIZE  10000
#define  MAXLWF   12

#define UPDATETM  50
#define LOWFSTEP  6

#define  DRAW

class DObj;

typedef struct SHOW_EQU{// 显示设备定义
	char devname[32];//设备名
	char devtype;//设备类型
	bool bshow;//是否显示
}SHOW_EQU;

//电力系统参数合计
typedef struct PWSYSSUM{
	float  GenMax;						//全网发电总容量
	float  GenP;						//全网发电有功
	float  GenQ;						//全网发电无功
	float  StopP;						//全网停机总容量
	float  UpRes;						//全网上旋转备用
	float  DownRes;						//全网下旋转备用
	float  LoadMax;						//全网设计总负荷
	float  LoadP;						//全网用电负荷
}PWSYSSUM;


//开关SOE序列
typedef struct NSOES
{
	DWORD swtid;	//开关ID
	BYTE  sta;		//动作状态0=开，1=合
	CTime tm;		//时间
	WORD  ms;		//毫秒
}NSOES;

//短路电流信息
typedef struct DLDL{
	BYTE   enable;						//数据是否有效
	WORD   high;						//显示高度
	DWORD  SwtNU;						//开关编号ID
	BYTE   GType;						//故障类型
	DWORD  LineNU;						//线路编号
	BYTE   LineType;					//线路类型
	CTime  DTime;						//计算时间
	float  TrPos;						//故障位置
	float  Imax;						//最大电流
	float  Isc;							//短路电流
	float  Usc;							//计算后电压
	float  over;						//越限率
}DLDL;

//访问设备的运行参数
typedef struct _READDEV{	 //用于访问设备的运行数据
	int   recno;			 //数据表中绝对记录号
							 //(第一次带入的参数可能是-1，以后返回正确的记录号)
	int   did;				 //设备ID
	BYTE  dtype;			 //设备类型
	BYTE  sta:2;			 //运行状态 0=停运、开 1=运行、合　
	BYTE  ele:1;			 //带电状态 0=不带电 1=带电
	BYTE  rp:1;				 //检修状态 0=正常,1=检修
	BYTE  trb:1;			 //故障状态 0=正常,1=故障
	BYTE  xsmode:3;			 //显示模式
	char  alarmhilo;		 //高低告警
	char  alarmband;		 //越范围告警
	float value[32];		 //最多可返回１６个浮点数，值的定义在程序中确认
}READDEV;

//读取仪表数据
typedef struct _YBDATA   
{
	int   recno;			 //数据表中绝对记录号
	int   did;				 //设备ID
	BYTE  dtype;			 //类型 0=指标
	BYTE  vtype;			 //值类型
	float curval;			 //当前值
	float vmax;				 //量程最大值
	float vmin;				 //量程最小值
	float vmax1;			 //第一段最大值
	float vmin1;			 //第一段最小值
	float vmax2;			 //第二段最大值
	float vmin2;			 //第二段最小值
}YBDATA;

//低频震荡缓冲区结构
typedef struct _LFDATA
{
	int    LineID;		//线路ID
	BYTE   Type;		//类型交流或直流
	float  frq;			//本数据的频率(1秒的平均频率)
	float  lfp;			//低频震荡功率(1秒的平均功率)
}LFDATA;

typedef struct _LFSDATA //用于显示的数据(已归+-5)
{
	int    LineID;		//线路ID
	BYTE   Type;		//类型交流或直流
	float  frq;			//本数据的频率(1秒的平均频率)
	float  lfp;			//低频震荡功率(1秒的平均功率)
	float  lfd[120];	//1秒数据,120点
}LFSDATA;

////////////////xsmode的含义///////////////////////////////////////////////////////
//1.按设备访问时
//	xsmode定义：
//	节点：  0=按电压等级和标幺值显示 1=显示电压绝对值和相角
//	线路：  0=始端   1=末端
//	变压器：0=三绕组 1=二绕组
//2.按单个值和曲线访问时
//  xsmode和dtype的关系
//	dtype=0:       发电机
//	     xsmode=0  有功
//		 xsmode=1  无功
//	dtype=1:	   线路
//		 xsmode=0  起端有功
//		 xsmode=1  起端无功
//		 xsmode=2  末端有功
//		 xsmode=3  末端无功
//	dtype=2:	   母线	
//	     xsmode=0  电压绝对值
//	dtype=3:	   负荷
//		 xsmode=0  有功
//		 xsmode=1  无功

////////////////////////////////////////////////

typedef struct PRTMODE{ //打印模式
   BYTE  nobg;		//不打印背景
   BYTE  color;		//彩色打印
   BYTE  border;	//打印边框
   BYTE  center;	//图形居中
}PRTMODE;


typedef struct N_NEWCOLOR{  //编辑时设置颜色时用
   DWORD bcolor1;			//背景颜色1
   DWORD bcolor2;			//背景颜色2
   DWORD tcolor;			//文本颜色
   DWORD lcolor;			//线条颜色
   BYTE  fillmode;			//填充模式
   BYTE  bc1;				//背景颜色1需要修改	
   BYTE  bc2;				//背景颜色2需要修改	
   BYTE  tc;				//线条颜色 需要修改	
   BYTE  lc;				//背景颜色1需要修改	
   BYTE  fm;				//填充模式需要修改	
}N_NEWCOLOR;

typedef struct N_PRTMODE{	//打印模式
   BYTE  nobg;				//不打印背景
   BYTE  wtob;				//白线变黑
   BYTE  allb;				//全部为黑
   BYTE  border;			//打印边框
   BYTE  center;			//图形居中
}N_PRTMODE;

typedef struct N_MemPic{	//内存图形
	WORD   inuse;			//使用者计数
	BYTE   tranmode;		//透明模式
	DWORD  trancolor;		//透明颜色
	WORD   id;				//内部ID号
	CMemDC dc;				//图形DC指针
}N_MemPic;

typedef struct N_MPicHD{	//磁盘图形格式头
	DWORD  start;			//0x10891111;标识新的位图开始
	WORD   inuse;			//使用者计数
	WORD   id;				//内部ID号
	DWORD  sPerline;		//每行字节数
	WORD   nWidth;			//宽度
	WORD   nHeight;			//高度
	BYTE   bits;			//图形颜色位数	
	DWORD  size;			//图形字节数
	DWORD  psize;			//压缩后字节数
}N_MPicHD;

//////////////////////////////////////////////////////////////
typedef struct N_ELEGRP{	//组合图元:内存中的存放结构
	WORD  inuse;			//使用者计数
	BYTE  type;				//类型 仪表时代表仪表的个数
	char  name[15];			//名字
	BYTE  subtype;			//子类型
	BYTE  sitesum;			//端子数,
	DRECT srt[3];			//3个端子位置
	BYTE  index[8];			//仪表的序号
	char  reserved[18];		//保留字节18
	WORD  id;				//内部ID号
	WORD  bsum1;			//图形数1
	DObj *bs1;				//图形1
	DRECT rt1;				//占用的矩形
	WORD  bsum2;			//图形数2
	DObj *bs2;				//图形2
	DRECT rt2;				//占用的矩形
}N_ELEGRP;
typedef N_ELEGRP N_EGRPSAVE;//组合图元存储格式



typedef struct N_MGifAml{	//GIF动画图形(只存第一帧)
	BYTE used;				//0=空闲 1=占用
	char fnm[64];			//GIF动画文件名
	CMImage dc;				//图形DC指针
}N_MGifAml;


typedef struct  N_PHEAD{	//图标组结构,文件头,标识为图型组GGP
   DWORD flag;				//=0xf9876761
   DWORD version;			//=0x300
   WORD  picsum;			//图形总数
}N_PHEAD;



typedef struct  N_PDATA{	//图形数据
	DWORD  start;			//0x10891111;标识新的位图开始
	DWORD  sPerline;		//每行字节数
	WORD   nWidth;			//宽度
	WORD   nHeight;			//高度
	BYTE   tranflag;		//透明标志
	BYTE   tranmode;		//透明模式0=在小于256色时 用tranindex透明 
							//1=使用trancolor透明
	BYTE   press;			//压缩标志
	BYTE   tranindex;		//透明索引
	DWORD  trancolor;		//透明颜色
	BYTE   bits;			//图形颜色位数	
	DWORD  size;			//图形字节数
	DWORD  psize;			//压缩后字节数
	WORD   id;				//ID号
	WORD   inuse;			//使用者计数
}N_PDATA;

typedef struct N_SMALLPIC{	//本pwf图形结构,经常使用的图片,和pwf文件一同保存
    WORD  inuse;			//使用者计数
	BYTE  tranmode;			//透明模式
	DWORD trancolor;		//透明颜色
	WORD  id;				//内部ID号
	CMImage img;			//图片
}N_SMALLPIC;

///////////////////////////组合图元////////////////////////////
typedef struct  N_EGPHEAD{	//组合图元结构,文件头,标识为图型组ELEGRP
	DWORD flag;				//=0x20010215;
	DWORD version;			//=0x200
	WORD  picsum;			//组合图形总数
	BYTE  press;			//压缩标志
	DWORD size;				//压缩前字节数
	DWORD psize;			//压缩后字节数
}N_EGPHEAD;

typedef struct  N_EGPDATA{	//图形数据
    DWORD    start;			//0x10891112;标识新的组合图元开始	
	N_EGRPSAVE sav;			//图元组的参数
	DWORD    size1;			//第一组合图元字节数
	DWORD    size2;			//第二组合图元字节数
}N_EGPDATA;

//////////////////////////////////////////////////////////////////
//磁盘文件保存格式
typedef struct N_OBJSAVE{	//对象保存信息
	DWORD offset;			//偏移量
	DWORD size;				//字节数
}N_OBJSAVE;

typedef struct N_PWFHEAD{	//屏幕格式化文件头
	WORD     Version;		//文件版本号=3200
	WORD     pagesum;		//页面数
	WORD	 spicsum;		//小图形对象总数
	WORD     mpicsum;		//内存图片对象总数
	WORD     egpsum;		//组合图元对象总数
	WORD     apdsum;		//附加信息对象总数
	DWORD    fsize;			//文件字节数
	N_OBJSAVE  spic;		//小图
	N_OBJSAVE  mpic;		//内存图
	N_OBJSAVE  epic;		//图元
	N_OBJSAVE  apdinfo;		//与图元相关的附加信息
	char reserved[128];		//保留128字节用于未来发展
	N_OBJSAVE  page[1];		//页面偏移
}N_PWFHEAD;
//保存顺序
//0=PWFHEAD头
//1=OBJSAVE[];数量与pagesum相同
//3=spic;
//4=mpic;
//5=epic;
//6=appendinfo;
//7=every page


typedef struct N_SUBPWF{     //子界面文件头
	WORD     flag;			 //0xcccc; 用于验证页面的开头
	char     Name[32];		 //画面名字
	BYTE     type;			 //类型 0=接线图 1=程序 2=地理
	WORD     width;			 //宽度
	WORD     height;		 //高度
	WORD     laysum;		 //层数
	DWORD	 BgColor;		 //背景颜色
	short    imgID;			 //背景图片ID号<0表示无
	char     showbyrt;		 //是否按指定矩形推出画面
	short    x1,y1,x2,y2;	 //指定的矩形
	///////////////
	unsigned char senflag:1; //灵敏度标志
	unsigned char no3dflag:1;//不允许3D标志
	unsigned char nonuse:6;  //保留，暂无用
	char     resved[9];		 //保留10字节（待用）
}N_SUBPWF;

typedef struct N_LAYERS{	//层文件保存结构结构
	WORD    flag;			//0xffff;用于验证层面开始
    char	name[25];		//层名字
	WORD    objnum;			//obj的数量	
	DWORD   size;			//对象子节数
	DWORD   psize;			//压缩后子节数
	char	resed[4];		//保留
}N_LAYERS;
//图形文件磁盘结构
struct  N_IMGDISK{
	BYTE   index;			 //索引号
	BYTE   type;			 //图形类型 0=一般位图 1=动画
	BYTE   frame;			 //动画的帧数
	WORD   width;			 //宽度
	WORD   height;			 //高度
	BYTE   bitcolor;		 //颜色位数
	DWORD  size;			 //图形压缩后的字节数
	char   imgdata[1];		 //图形
};
//动画文件磁盘结构
struct  N_AMLDISK{
	int    x,y;				 //绘图的X,Y位置
	int    w,h;				 //宽高
	BYTE   disposal;		 //显示模式
	BYTE   tranflag;		 //透明标志
	BYTE   tranIndex;		 //透明颜色
	WORD   delay;			 //延迟时间
	DWORD  size;			 //单幅画面压缩后的字节数
	char   imgdata[1];		 //图形(<256色时包含调色板);
};

////////////////////////////////////////////////
typedef struct N_layer{		//层结构
    char	name[25];		//层名字
	BYTE	show;			//是否显示
	BYTE	select;			//是否参与选择
	DObj    *obj;			//对象地址指针
	WORD    objnum;			//obj的数量	
	char	resed[4];		//保留
}N_LAYER;

//定义页面结构
typedef struct N_PAGEPWF{    //页面结构
	BYTE     index;			 //图号
    N_SUBPWF head;           //每页头结构
	N_LAYER  layer[MAXLAYER];//图层定义8层 
	int      laysum;		 //层数
	int      curlay;		 //当前层
	int		 zw1,zh1;		     //缩放后的宽高
}N_PAGEPWF;

////////////////////////////////////////////////
typedef struct N_BASATTR{    //对象基本属性  
	WORD  type;				 //对象类型
	BYTE  belong;			 //所属端子 只有组合图元才有效
	DWORD ID;				 //对象ID
	WORD  size;              //对象字节数
}N_BASATTR;

typedef struct N_DBX{		 //多边形 type=1  r1
	DPOINT pta[4];			 //4个角坐标
	BYTE  fill;				 //0=不填充 1=填充
	BYTE  fillmode;			 //填充方式
	BYTE  close;			 //0=不封闭 1=封闭 
	BYTE  ltype;			 //线类型
	BYTE  bgmode;			 //背景模式 0=前景 1=北京
	DWORD lcolor;			 //线颜色
	DWORD bcolor1;			 //填充颜色1
	DWORD bcolor2;			 //填充颜色2
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N_DBX;

typedef  struct N_RECT{		 //矩形 type=2 r2
	DPOINT pt[4];			 //4个角坐标
	BYTE   fill;			 //0=不填充 1=填充 
	BYTE   fillmode;		 //填充方式 
	BYTE   type;			 //0=一般矩形  1=3D矩形/(园)球体 
	DWORD  lcolor;			 //线颜色
	DWORD  bcolor1;			 //填充颜色1
}N_RECT;

typedef N_RECT N_CIRCLE;	 //园 type=3  r3
    

typedef struct N_HSIN{		 //正弦半波形 type=4  r4
	DPOINT pt[4];			 //4个角坐标
	BYTE  ltype;			 //线类型 
	BYTE  lmode;			 //模式 0=正常 1=边框
    BYTE  pirodic;			 //周期数
	DWORD color;			 //线颜色
}N_HSIN;



typedef struct N_SIN{		 //正弦波形  type=5 r5
	DPOINT pt[4];			 //4个角坐标
	BYTE  ltype;			 //线类型 0=水平 1=垂直
	WORD  startdeg;			 //开始角度0-359
	BYTE  pirodic;			 //周期数
	DWORD color;			 //线颜色
}N_SIN;

typedef struct N_ARC{		 //园弧 type=6  r6
	DPOINT  pt[4];			 //4个角坐标
	DWORD   color;			 //颜色
	short    start;			 //开始角度
	short    end;			 //结束角度	
}N_ARC;

typedef struct N_ARROW{      //方向箭头  type=7  r7
	DPOINT pta[4];			 //4个角坐标
	DPOINT  pt[2];			 //两点坐标
	DWORD   color;			 //线颜色	
}N_ARROW;

typedef struct N_GLASS{      //玻璃层    type=8
	DPOINT  pt[4];			 //4个角坐标
	BYTE    depth;			 //深度
	DWORD   color;			 //线颜色
	BYTE    outline;		 //是否画边线
	DWORD   ocolor;			 //边线色
}N_GLASS;

typedef struct N_CBAR{       //圆拄棒图  type=9  r8
	DPOINT pt[4];			 //4个角坐标
	BYTE  xy;				 //XY方向0=x 1=y
	BYTE  outline;		 //外框
	DWORD color;		     //线颜色
}N_CBAR;

typedef struct N_TEXT{       //文本  type=10    r9
	DPOINT  pt[4];			 //4个角坐标
	double  zm;				 //绘图时的倍率
	LOGFONT font;			 //字体
    DWORD   color;			 //颜色
    char    style;			 //式样
    BYTE    autofill;		 //自动充满
    char    text[45];		 //文本内容
}N_TEXT;

typedef struct N_ESITE{		 //电气端子type=11
	DPOINT pt[4];			 //4个角坐标
	DWORD  color;			 //端子显示颜色
	BYTE   solder;			 //焊接 0=焊接 1=没焊
}N_ESITE;

typedef struct N_EGPMB{		 //组合图元母板 type=12 
	DPOINT pt[4];			 //4个角坐标
	BYTE   mode;			 //0=不显 1=显示
	DWORD  color;			 //颜色
}N_EGPMB;

typedef struct N_COORDINATE{ //坐标 type=13
	DPOINT pt[4];			 //4个角坐标
	long  xmin;				 //X方向最小值
	long  xmax;				 //X方向最大值
	long  ymin;				 //Y方向最小值
	long  ymax;				 //Y方向最大值
	DWORD  colorc;			 //坐标线颜色
	DWORD  colorw;			 //水线颜色
	DWORD  colort;			 //文本颜色
	BYTE   xdot;			 //X坐标点数
	BYTE   ydot;			 //Y坐标点数
	BYTE   wxdraw;			 //X方向水线是否画
	BYTE   wydraw;			 //y方向水线是否画
	BYTE   xvshow;			 //x坐标值显示
	BYTE   yvshow;			 //y坐标值显示
	LOGFONT fontx;			 //X字符显示字体
	LOGFONT fonty;			 //Y字符显示字体
	double zm;				 //绘图时的倍率
}N_COORDINATE;

typedef struct N_TABLE{		 //表格线 type=14
	DPOINT pt[4];			 //4个角坐标
	DWORD  color;			 //线颜色
	double   width;			 //线宽度
	BYTE   dbline;			 //边线加粗
	WORD   line;			 //行数
}N_TABLE;


typedef struct N_IMG{		 //静态图形type=15
	DPOINT pt[4];			 //4个角坐标
	BYTE  shadow:1;			 //阴影
	BYTE  zoom:1;			 //支持缩放出0=No 1=Yes
	BYTE  depth;		     //透明度
	WORD  imgID;			 //ID
}N_IMG;

typedef struct N_PATH{		 //路径 type=16  r10
	DPOINT   pta[4];		 //4个角坐标
	WORD  ID;				 //路经ID
	double  start;			 //起点坐标
	double  end;			 //终点坐标
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N_PATH;

typedef struct N_SPIC{	     //静态小图标type=17
	DPOINT pt[4];			 //4个角坐标
	WORD  picID;			 //ID
	BYTE  zoom;				 //支持放缩 0=no 1=yes
}N_SPIC;

///////////////////////特殊动态类/////////////////////////////////////
//动态仪表1
typedef struct N_METER1     //仪表参数   type=32
{
	DPOINT  pt[2];			//2个点坐标 第1点是指针顶部 第二点是园心
	LOGFONT font;			//数字字体
	float   Vmin;			//最小值
	float	Vmax;			//最大值
	BYTE    showarc;		//是否显示弧线
	BYTE    shownum;		//是否显示数字 0=不显 1=外侧 2=内侧
	BYTE    numdot;			//小数点
	BYTE    rev;			//反向
	BYTE    scale;			//刻度数
	BYTE    scales;			//每格的小刻度数
	BYTE    slen;			//刻度长度
	BYTE    angle;			//仪表倾角,指针总的偏转角度/2
	BYTE    pstyle;			//指针式样
	DWORD   pcr;			//指针颜色
	BYTE    axw;			//轴的宽度
	BYTE    pw;				//箭头宽度
	DWORD   scr;			//刻度颜色
	BYTE	alarm;			//是否支持告警刻度 0=没有 1,2=有
	float	val[4];			//2段值(起点终点)
	DWORD	cr[2];			//最多支持2段颜色
	float   curval;			//当前值
	double  zm;
	BYTE    stype;			//刻度类型
	BYTE    lstype;			//小刻度类型
}N_METER1;
//动态仪表2
typedef struct N_METER2     //水平刻度 type=33
{
	DPOINT  pt[4];			//4个角坐标
	float   Vmin;			//最小值
	float	Vmax;			//最大值
	BYTE    rev;			//反向
	BYTE    scale;			//刻度数
	BYTE    scales;			//每格的小刻度数
	BYTE    showbl;			//是否显示底线
	BYTE    shownum;		//是否显示数字0没有 1=显示
	BYTE    numdot;			//小数点
	DWORD	scr;			//刻度颜色
	DWORD	pcr;			//指针颜色
	BYTE	alarm;			//是否支持告警刻度 0=没有 1,2=有
	float	val[4];			//2段值(起点终点)
	DWORD	cr[2];			//最多支持2段颜色
	float   curval;			//当前值
}N_METER2;

//动态仪表3
typedef struct N_METER3     //垂直刻度 type=34
{
	DPOINT  pt[4];			//4个角坐标
	float   Vmin;			//最小值
	float	Vmax;			//最大值
	BYTE    rev;			//反向
	BYTE    scale;			//刻度数
	BYTE    scales;			//每格的小刻度数
	BYTE    showbl;			//是否显示底线
	BYTE    shownum;		//是否显示数字0没有 1=左边数字 2=右边数字
	BYTE    numdot;			//小数点
	DWORD	scr;			//刻度颜色
	DWORD	pcr;			//指针颜色
	BYTE	alarm;			//是否支持告警刻度 0=没有 1,2=有
	float	val[4];			//2段值(起点终点)
	DWORD	cr[2];			//最多支持2段颜色
	float   curval;			//当前值
}N_METER3;

//动态仪表4
typedef struct N_METER4     //基本仪表参数(数码) type=35
{
	DPOINT   pt[4];			//4个角坐标
	BYTE     num;			//总位数
	BYTE     numdot;		//小数位数
	DWORD    bcr;			//边框颜色
	DWORD    ncr[2];		//整数和小数部分的颜色
	double   curval;		//当前值
}N_METER4;


//定义单点数据源（只能选择其中一点数据)
typedef struct _SINGLEDBS{   //单点数据源
	char  name[64];			 //设备名字
	int   did;				 //设备ID
	BYTE  dtype;			 //设备类型0=发电机 1=线路 2=母线 3=负荷  4=变压器 5=电容器/电抗器
	BYTE  xsmode;			 //值索引
}SINGLEDBS,DBSRC;
/*  xsmode和dtype的关系
	dtype=0:       发电机
	     xsmode=0  有功
		 xsmode=1  无功
	dtype=1:	   线路
		 xsmode=0  起端有功
		 xsmode=1  起端无功
		 xsmode=2  末端有功
		 xsmode=3  末端无功
	dtype=2:	   母线	
	     xsmode=0  电压标幺值
		 xsmode=1  电压绝对值
		 xsmode=2  相角
	dtype=3:	   负荷
		 xsmode=0  有功
		 xsmode=1  无功
	dtype=4:	   变压器
	     xsmode=0  高档位分接头
		 xsmode=1  中档位分接头
	dtype=5:	   电容器
		 xsmode=?  投入容量
*/
/////////////////////以下为动态运行对象///////////////////////////////
typedef struct R_ANL{		 //模拟量实时值
	float curval;			 //当前值
	unsigned char alarm:2;	 //是否越限0=正常 1=下限 2=上限
	unsigned char ele:1;	 //带电状态
	unsigned char resd:5;	 //坏数据
	char reserved;			 //保留
}R_ANL;

typedef struct R_FLW{		 //线路实时值
	float p;				 //有功当前值
	float q;				 //无功当前值
	unsigned char enable:1;	 //当前值是否有效
	unsigned char ele:1;	 //带电状态
	unsigned char overlmt:2; //越限 0=正常 1=越下限 2=越上限
	unsigned char  show:1;   //是否显连接线
	unsigned char sta:1;	 //状态 0=停运 1=运行
	unsigned char nouse:2;	 //未用
	char  reserved[3];		 //保留
}R_FLW;



typedef struct R_STA{		 //状态量实时值
	unsigned char zt:1;		 //当前状态
	unsigned char enable:1;	 //当前值是否有效
	unsigned char ele:1;	 //带电状态
	unsigned char reserve:5; //未用
	char red[4];			 //保留
}R_STA,R_DEV;


/////////////////////////////////////////////////////////////////////////////
typedef struct N_ANL{        //模拟量显示结构 type=64 r11
	DPOINT   pt[4];			 //4个角坐标
	LOGFONT  lf;		     //字体
	COLORREF acolor;	     //告警颜色
	COLORREF ncolor;	     //正常颜色
	BYTE     xs;			 //小数位
	BYTE     direction;		 //方向0=x方向 1=Y方向
	BYTE     xsmode;		 //见下面,不同对象有不同的含义
	READDEV  vr;			 //设备的实时值		 
	char     dev_name[64];	 //设备名
}N_ANL;

typedef struct N_RESERVOIR{  //水库对象   type=65
	DPOINT  pta[4];			 //4个角坐标
	READDEV vr;				 //实时数据
	HRGN    hrgn;			 //暂存，无需删除
	DWORD	color;			 //线颜色
	DWORD	ncolor;			 //正常时颜色
	DWORD	hcolor;			 //高水位颜色
	DWORD	lcolor;			 //低水位颜色
	char	dev_name[64];	 //水库名
	long	did;			 //水库ID
	WORD	ptsum;			 //点总数
	DPOINT	pt[1];			 //后跟所有的点
}N_RESERVOIR;


typedef struct D_SITE{		 //运行端子定义 
	DRECT  srt;				 //本端子矩形位置
	BYTE   vl;				 //电压等级	 
	BYTE   sitn;			 //连接到的端子号
	long   id;				 //对象ID(图形系统内的唯一ID)
}D_SITE;


typedef struct D_SITEB{		 //线类端子定义 
	BYTE   sitn;			 //连接到的端子号
	long   id;				 //对象ID(图形系统内的唯一ID)
}D_SITEB;


typedef struct D_SITEC{		 //搜索端子参数定义 
	char   vl;				 //电压等级	 
	BYTE   sitn;			 //连接到的端子号
	long   id;				 //对象ID(图形系统内的唯一ID)
	BYTE   nlayer;			 //对象所在层面
	int    jlh;				 //本端子的图元逻辑记录
	BYTE   etype;			 //排斥的类型(不参与搜索)
	DRECT  srt;				 //比较的矩形
	DPOINT cpt;				 //返回的中心点
}D_SITEC;

typedef struct N_ELEGRPA{    //组合图元显示结构type=66  r13
	DPOINT   pt[4];			 //4个角坐标
	BYTE     type:2;		 //数据类型 0=状态量 1=设备 2=站 3=公司
	BYTE     subtype:6;		 //子类型 当type=1 时为设备类型
	int      egrpid;		 //组合图元ID号
	BYTE     showno;		 //绘图时的显示号0和1
	byte     sitesum;		 //端子数
	D_SITE   site[3];		 //三个端子
	READDEV  vr;			 //设备的实时值	
	short    dydeg;			 //动态角度(需要动态显示的图形)
	float    Ps;			 //视在功率
	BYTE     genrev:1;		 //是否显示发电机备份(发电机时有效)
	BYTE     runshow:1;		 //运行时是否显示
	char     dev_name[64];	 //设备名
	long     did;			 //设备记录号
}N_ELEGRPA;

typedef struct MTRRANGE{	 //仪表限值
	BYTE     ptype;			 //参数类型 0=使用自定义 1=使用数据库
	float    vmin;			 //最小值
	float    vmax;			 //最大值
	BYTE	 alarm;			 //是否支持告警刻度 0=没有 1,2=有
	float	 val[4];		 //2段值(起点终点)
	DWORD    color[2];		 //2段颜色
}MTRRANGE;


typedef struct N_ELEGRPYB{   //组合图元仪表结构 type=67
	DPOINT   pt[4];			 //4个角坐标
	WORD     egrpid;		 //组合图元ID号
	BYTE     dbsum;			 //数据源个数
	DBSRC    dbs[8];		 //8个数据源，对应8个顺序仪表和数据
	MTRRANGE umr[8];		 //用户自定义量程
	float    curval[8];		 //8个值
	float    newval[8];		 //读取的值
	BYTE     show;			 //=0无需显示 1=需要显示
}N_ELEGRPYB;



typedef struct N_TREND{		 //趋势  type=68
   DPOINT pt[4];			 //4个角坐标
   int  id;					 //保留ID内部用
   BYTE seg;				 //时间段数
   BYTE jg;					 //间隔
   float max;				 //最大值
   float min;				 //最小值
   DWORD lcolor;			 //线颜色
   DWORD bcolor;			 //背景色
   DWORD wcolor;			 //水线色
   BYTE  border;			 //边框
   BYTE  tran;				 //背景透明
   BYTE  width;				 //线宽度
   R_ANL rval;				 //实时数据
   float qx[25];			 //总共24点数据
   char  ds_name[64];		 //模拟量名
   long  jlh;				 //相关记录号
}N_TREND;


typedef struct N_SYSPIE{     //饼图结构数据 type=68
	DPOINT  pt[4];			 //4个角坐标
	WORD    ID;				 //ID号
	DWORD   fcolor;			 //字符色
	LOGFONT lf;				 //字体
	BYTE    type;			 //类型
	DWORD   color[6];		 //6个颜色 最大6个部分
	PWSYSSUM val;
	double  vl[4];			 //4个值
	double  maxv;			 //最大值
	int    error;
	int    num;				 //饼个数
}N_SYSPIE;

typedef struct N_BAR{		 //棒图 type=69
	DPOINT pt[4];			 //4个角坐标
	int   id;				 //保留ID内部用
	float max;				 //最大值
	float min;				 //最小值
	BYTE  xy:1;              //0=x方向 1=Y方向
    BYTE  outline:1;		 //外框
    BYTE  style:3;			 //式样
	BYTE  reserved:3;		 //保留
    DWORD ncolor;			 //正常颜色
    DWORD acolor;			 //告警颜色
    float aval;				 //告警值
    R_ANL rval;				 //当前值
    SINGLEDBS dsrc;			 //数据源
}N_BAR;

typedef struct _NPIEDAT{	 //饼图数据结构
	char name[12];			 //数据名称
	float value;			 //值
}NPIEDAT;



typedef struct N_PIE{        //饼图结构数据 type=70
	DPOINT  pt[4];			 //4个角坐标
	WORD    ID;				 //ID号
	DWORD   fcolor;			 //字符色
	DWORD   color[3];		 //3个颜色
	LOGFONT lf;				 //字体
	char    name[24];		 //区域名称
	int     did;			 //区域ID
	BYTE    type;			 //未用
	float   maxv;			 //最大值
	float   pcur;			 //当前值
	float   qcur;			 //无功值
}N_PIEPAM;


typedef struct N_DATE{       //日期格式     type=71 r14
	DPOINT  pt[4];			 //4个角坐标
	BYTE    fmt;			 //日期格式 0=yyyy-mm-dd 1=mm/dd/yyyy 2=yyyy年mm月dd日
	BYTE    outline;		 //边框 0=无 1=正常 2=凹 3=凸
	BYTE    tran;			 //背景透明吗？0=No 1=Yes
	BYTE    style;			 //字体显示 0=正常 1=凹 2=凸
	BYTE    shadow;			 //字体阴影显示
	DWORD   outcolor;		 //边线色
	DWORD   fcolor;			 //字符颜色
	DWORD   bcolor;			 //背景色
	LOGFONT font;			 //字体
	CTime   tm;				 //时间
}N_DATE,N_TIME;				 //时间格式     type=72 r15


typedef struct N_GIFAML{     //静态图形  type=73
	DPOINT  pt[4];			 //4个角坐标
	char  fname[60];		 //文件名
	CGIFAnm *gfm;			 //动画类指针
	WORD  rec;				 //GIF图形内部记录,显示用
	BYTE  type;				 //关联类型：状态量,设备,站
	BYTE  zt;				 //当前状态
	SINGLEDBS dsrc;			 //数据源
}N_GIFAML;


typedef struct N_SRLTEXT{	 //滚动文本  type=74
	DPOINT  pt[4];			 //4个角坐标
	BYTE direct:3;			 //方向   0=静态文本 1=上下 2=左右 
							 //3=下上 4=右左
	BYTE tstyle:2;			 //文本样式 0=正常 1=凹 2=凸
	BYTE glass:1;			 //是否用玻璃层 0=No 1=Yes
	BYTE outline:1;			 //是否有外框
	BYTE  align:2;		     //排列方式 0=居左 1=居中 2=居右
	BYTE  shadow:1;			 //是否阴影
	BYTE depth;				 //深度
	DWORD fcolor;			 //边框
	DWORD gcolor;			 //玻璃颜色
	DWORD tcolor;			 //文本颜色
	LOGFONT lf;				 //文字字体
	WORD  id;				 //ID号
	char text[252];			 //文字串
	short pos;				 //当前位置
	WORD  wh;				 //宽或高
}N_SRLTEXT;

typedef struct N_PUSH{		 //按钮格式   type=75
	DPOINT  pt[4];			 //4个角坐标
	char  title[64];		 //按钮标题
	WORD  spicid;			 //小图标ID号
	BYTE  style:3;			 //按钮式样0=普通按钮 1=不可见按钮
							 //2=滑过凸形按钮 3=滑过凹形按钮 
							 //4=滑动变色 5=图标按钮
	BYTE  autlin:1;			 //位图按钮时,自动边线
	BYTE  fstyle:2;			 //文本显示属性
	BYTE  shadow:1;			 //阴影
	BYTE  down:1;			 //压下状态
	BYTE  edit:1;			 //编辑状态
	BYTE  cmdtype;			 //命令类型
	WORD  cmdnum;		     //自定义时的WM_COMMAND消息wParam
	char  command[64];		 //命令字符串
	DWORD color1;			 //颜色1
	DWORD color2;			 //颜色2
	int   selfid;			 //要控制的自助控件的ID
	LOGFONT lf;				 //字体
	WORD  id;				 //自身ID
	BYTE  tosta;			 //推出状态
}N_PUSH;



typedef struct N_SELFCTL{    //自助控件  type=76
	DPOINT  pt[4];			 //4个角坐标
	char  dllname[256];		 //动态连接库名
    DWORD style;			 //属性,由控件设置
    int	  id;				 //ID号,以便相互控制
    char  lkbuf[255];		 //启动时的连接缓冲区
    BYTE  aleft:1;			 //左对齐
    BYTE  aright:1;			 //右对齐
    BYTE  atop:1;			 //上对齐
    BYTE  abottom:1;		 //下对齐
	BYTE  mode:1;			 //类型:0=位置固定 1=自动对齐
    HINSTANCE hinst;         //DLL的事例
    HWND  hwnd;				 //窗口句柄
	HMENU hmenu;			 //控件菜单
    void  *rc;				 //初始化产生的资源(如果有)
    int   (WINAPI*DfGetVer)();//返回版本号
    void  (WINAPI*DfDrawDemo)(HDC,RECT,DWORD,char *);		//演示绘图
    void  *(WINAPI*DfInit)(HWND,HWND&,RECT,int,DWORD,char*);//初始化
    void  (WINAPI*DfClose)(void *rc);						//关闭
    void  (WINAPI*DfAbout)();								//关于该控件
    void  (WINAPI*DfSetParam)(DWORD&,char*);				//配置参数
	void  (WINAPI*DfPrint)(HDC,RECT,BYTE);					//提供打印支持
	HMENU (WINAPI*DfLoadMenu)();							//配置参数
}N_SELFCTL;

typedef struct R_FLOW{		//潮流运行参数
	char     pjs;			//有功起点计数
	char     qjs;			//无功起点计数
	char     ijs;			//电流起点计数
	unsigned char  canrun:1;//是否满足条件显示潮流线 0=不满足 1=满足
	unsigned char  pdir:1;	//有功方向
	unsigned char  qdir:1;  //无功方向
	unsigned char  idir:1;	//电流方向
	unsigned char  rev:4;	//保留
	char     reserved;		//保留1字节
}R_FLOW;

typedef struct N_FLOW{		//潮流线    type=77 r16
	DPOINT pta[4];			 //4个角坐标
	HRGN    hrgn;			//区域，临时数据，无需删除
	R_FLOW  rf;				//运行参数
	READDEV vr;				//实时数据
	BYTE  vl;				//电压等级	 
	D_SITEB site[2];		//端子
	DWORD color1;			//有功颜色
	DWORD color2;			//无功颜色
//	BYTE  style:2;			//式样 0=一般线条 1=只显有功 2=只显无功 3=同时显示
	BYTE  direct:1;			//正反方向 0=正向 1=反向
	BYTE  type:1;			//类型 0=交流 1=直流
	BYTE  linewidth;		//线宽
	float ps;				//视在功率
	BYTE  pv;				//有功速度
	BYTE  qv;				//无功速度
	BYTE  iv;				//电流速度
	char  dev_name[64];		//设备名
	long  did;				//设备记录号(ID)
	int   lowfbz;			//低频振荡标志
	float *fpt;				//低频震荡数据
	int	  flen;				//低频震荡数据长度
	WORD  ptsum;			//点总数
	DPOINT stapt;			//显示线路状态的坐标位置，此位置在加载线路负载饼图是根据饼图位置同步
	DPOINT pt[1];			//后跟所有的点
}N_FLOW;

typedef struct LOGOBJ{		//连接线用的连接对象记录
	BYTE  layer;			//所在层
	short jlh;				//记录号
	unsigned char sitn:3;		//连接的端子
	unsigned char reserved:5;	//保留
}LOGOBJ;

typedef struct N_CONLINE{	//连接线  type=78 r17
	DPOINT  pta[4];			//4个角坐标
	BYTE    el:1;			//带电状态 =0 不带电 =1 带电
	BYTE    conobj:1;		//连接到设备标志 =0 未连接 =1 已连接
	BYTE	vl;				//电压等级
	LOGOBJ  lobj[2];		//两个端子连接的对象
	WORD	ptsum;			//点总数
	DPOINT	pt[1];			//后跟所有的点
}N_CONLINE;

typedef struct N_BUS{		//母线  type=79 r18
	DPOINT  pt[4];			//4个角坐标
	BYTE    type;			//类型
	BYTE	vl;				//电压等级
	READDEV vr;				//实时值
	float   vn1;			//n-1指标，母线
	int     eid;			//组合图元ID
	char    dev_name[64];	//设备名
	long    did;			//设备记录号
	float   daymax;
	float   daymin;
}N_BUS;

typedef struct N_ACTOBJ{	//小型活动对象  type=80
	DPOINT  pt[4];			//4个角坐标
	short   gid;			//图形ID
	WORD	pathid;			//所属path ID
	BYTE	runmode;		//运行模式 0=自动 1=同步
	BYTE	speed;			//自动运行速率 0,1,2,3
	float	skip;			//自动步长
	SINGLEDBS dsrc;			//数据源
}N_ACTOBJ;



typedef struct N_FLASH{		//FLASH对象  type=81
	DPOINT  pt[4];			//4个角坐标
	char  fname[128];		//swf文件名
	BYTE  playmode:1;		//播放模式0=一次 1=循环
	BYTE  align_left:1;		//左对齐
	BYTE  align_top:1;		//上对齐
	BYTE  align_right:1;	//右对齐
	BYTE  align_buttom:1;	//下对齐
}N_FLASH;

typedef struct N_PCTPIE{	//百分比饼图 type=82
	DPOINT  pt[4];			//4个角坐标
	char    dev_name[64];   //设备名
	int     did;			//设备ID
	BYTE    type;			//数据类型 0=传输线 1=发电机
	DWORD   color1,color2;  //两个颜色
	DWORD   fcolor;			//字体颜色
	LOGFONT lf;				//数字字体
	float   maxv;			//最大值
	float   curval;			//当前值
	float   vn1;			//n-1指标，线路
	int   showdl;			//显示短路状态
}N_PCTPIE;

typedef struct N_ZONE{		//区域   type=83
	DPOINT pta[4];			//4个角坐标
	READDEV vr;				//实时值
	float   dyval;			//动态值
	DWORD lcolor;			//边线颜色
	char  zone_name[64];	//区域名
	long  did;				//区域(ID)
	LOGFONT lf;				//字体
	DWORD fcolor;			//字体颜色
	WORD  ptsum;			//点总数
	DPOINT pt[1];			//后跟所有的点
}N_ZONE;

typedef struct N_MTTEXT{	//区域    type=84
	DPOINT  pt[4];			//4个角坐标
	DWORD fcolor;			//颜色
	char  name[64];			//名字
	BYTE  sta;				//状态值
	int   did;				//(ID)
	BYTE  type;				//类型
	LOGFONT lf;				//字体
	char  text[256];		//文本缓冲
	int   offset[64];		//偏移位置量
	int   lstsum;			//列表个数
}N_MTTEXT;

typedef struct N_WEATHER	//区域天气 type=85
{
	DPOINT  pt[4];			//4个角坐标
	char    name[64];		//区域名
	int     did;			//设备ID
	LOGFONT lf;				//字体
	DWORD	fcolor;			//字体颜色
	char    reserved[20];	//
}N_WEATHER;

typedef struct N_APDINFO{	//附加信息,用于画面的综合控制
	BYTE    pageno;			//页面序号
	BYTE    enableout;		//是否启动放大推画面
	float   outstart;		//启动的放大倍数
	char    outname[25];	//放大画面名字
	BYTE    outno;			//放大画面序号
	BYTE    enablein;		//是否启动缩小推画面
	float   instart;		//启动的缩小倍数
	char    inname[25];	    //缩小画面名字
	BYTE    inno;			//缩小画面序号
	BYTE    defzm1,defzm2;  //是否指定放大、缩小倍数
	float   zm1,zm2;        //显示时的倍数
	char    reserved[54];	//保留今后扩展用
}N_APDINFO;

typedef struct SUBW_PARAM{//运行子窗口属性定义
	HWND  hwnd;			//窗口
	CDRect rts;			//窗口原始大小
	CRect rt;			//占用的矩形
	CRect rtw;			//窗口矩形
    BYTE  left;			//左对齐
    BYTE  right;		//右对齐
    BYTE  top;			//上对齐
    BYTE  bottom;		//下对齐
	BYTE  mode;
}SUBW_PARAM;

typedef struct ROBJ{	//运行对象
	DObj *bs;		  	//对象地址
}ROBJ;

typedef struct RANL{	//模拟量对象
	DObj *bs;			//对象地址
	int recno;			//运行时设备的绝对记录号，与数据库有关
	CDRect rt;			//对象占用的矩形
	N_ANL *anl;			//对象属性地址
}RANL;

typedef struct RMTXT{	//多行对象
	DObj *bs;			//对象地址
	int recno;			//运行时设备的绝对记录号，与数据库有关
	CDRect rt;			//对象占用的矩形
	N_MTTEXT *txt;		//对象属性地址
}RMTXT;

typedef struct RSTA{	//状态量对象
	DObj *bs;			//对象地址
	int  recno;			//绝对记录号
	CDRect rt;			//占用的矩形区
	N_ELEGRPA *elg;		//对象地址
}RSTA;


typedef struct RSWT		//开关对象
{	
	DObj *bs;			//对象地址
	N_ELEGRPA *elg;		//对象地址
	DPOINT opt;			//原始位置
	double deep;		//深度
	int   subtype;		//设备的subtype
	int	  recno;		//运行时设备的绝对记录号,与数据库有关
	int   order;		//动作序号
	NSOES soe[4];		//可以保留4个动作
	int   soesum;		//当前SOE个数
	DLDL  dl;			//短路电流信息	
	HRGN  hrgn;			//显示所占的区域
}RSWT;


typedef struct RREV{	//需要备用3DBAR显示的对象
	DObj *bs;			//对象地址
	N_ELEGRPA *elg;		//对象地址
	DPOINT opt;			//原始位置
	double deep;		//深度
	int   subtype;		//设备的subtype
	int	  recno;		//运行时设备的绝对记录号,与数据库有关
	HRGN  hrgn;			//显示所占的区域
}RREV;					

typedef struct RBUS{	//母线 对象
	DObj *bs;			//对象地址
	int recno;			//运行时设备的绝对记录号，与数据库有关
	CDRect rt;			//占用的矩形区
	HRGN  hrgn;
	N_BUS *bus;			//属性地址
}RBUS;

typedef struct RSEN{	//用于显示灵敏度(用于动态显示)
	DObj *bs;			//对象地址
	N_ELEGRPA *elg;		//对象地址
	int   rtype;		//灵敏度类型
	float senvalue;		//灵敏度值
	int   did;			//母线ID
	DPOINT opt;			//原始位置
	double deep;		//深度
	HRGN  hrgn;			//电容器灵敏度所占的区域
}RSEN;

//显示N-1故障的设备收集
typedef struct N1BAR{	//用于显示灵敏度(用于动态显示)
	int    devid;		//设备ID
	char   name[32];	//设备名字
	BYTE   type;		//0=发电机，1=负荷 2=变压器 3=线路
	DPOINT opt;			//原始位置
	double deep;		//深度
	DWORD  color;		//显示颜色
	int    Hbar;		//棒高度
	int    index;
	int    selbz;		//选择标志
	float  vn1;			//值
	HRGN  hrgn;			//区域
}N1BAR;



typedef struct RMETER  {//仪表对象
	DObj  *bs;			//对象地址
	N_ELEGRPYB *mtr;	//属性地址
	int    recno[6];	//运行时的数据绝对记录号
	CDRect  rt;			//占用的矩形区
}RMETER;

typedef struct RBAR{	//棒图对象 70
	DObj  *bs;			//对象地址
	int recno;			//运行时设备的绝对记录号，与数据库有关
	N_BAR  *bar;		//属性地址
	CDRect  rt;			//占用的矩形区
}RBAR;

typedef struct RPIE{	//饼图对象
	DObj  *bs;			//对象地址
	int recno;			//运行时设备的绝对记录号，与数据库有关
	N_PIE  *pie;		//属性地址
	CDRect rt;			//占用的矩形区
	HRGN  hrgn;			//区域
	double deep;		//深度
	DPOINT opt;			//原始位置
}RPIE;

typedef struct RSPIE{	//饼图对象
	DObj  *bs;			//对象地址
	int recno;			//运行时设备的绝对记录号，与数据库有关
	N_SYSPIE  *pie;		//属性地址
	CDRect rt;			//占用的矩形区
	HRGN  hrgn;			//区域
	double deep;		//深度
	DPOINT opt;			//原始位置
}RSPIE;

typedef struct RCONL{	//连接线对象
	DObj *bs;			//对象地址
	CDRect rt;			//占用的矩形区
	N_CONLINE *lin;		//属性地址
}RCONL;

typedef struct RAML{	//动画对象
	DObj *bs;			//对象地址
	int recno;			//运行时设备的绝对记录号，与数据库有关
	N_GIFAML *ngf;		//属性地址
	CDRect rt;			//占用的矩形区
	BYTE  zt;			//运行状态0=停止 1=运行
	BYTE  enable;		//zt是否有效
	CGIFAnm gfaml;	    //动画类
}RAML;

typedef struct RSCRTXT{	//滚动文本对象
	DObj *bs;			//对象地址
	N_SRLTEXT *stx;		//属性地址
	CDRect rt;			//占用的矩形区
}RSCRTXT;
 
typedef struct RSELFCTL{
	DObj *bs;			//对象地址
	CDRect rt;			//占用的矩形区
	int   sid;			//对象自生ID
	BYTE  cansize;		//能否改变大小
	SUBW_PARAM swp;		//窗口相关参数  
	N_SELFCTL *stl;		//属性地址
}RSELFCTL;
  
typedef struct RFLOW{	//潮流线对象
	DObj  *bs;			//对象地址
	N_FLOW *flw;		//属性地址
	int   recno;		//运行时设备的绝对记录号，与数据库有关
	int   ptime;		//有功计数次数
	int   qtime;		//无功计数次数
	int   itime;		//电流计数次数
	HRGN  hrgn;			//区域
	int   ptsum;		//点数
	POINT pt[20];		//点
	CRect rt;			//占用的矩形区
	///低频震荡要求参数
	double mdot;		//每50毫秒需要移动的数据点数,带小数
	int    curdot;		//当前节拍点（0-19）
	LFSDATA lfdcur;		//当前正在显示的低频震荡数据
	int    lfflag;		//低频震荡标记
}RFLOW;


typedef struct RRES{	//水库对象
	DObj  *bs;			//对象地址
	N_RESERVOIR *res;	//属性地址
	HRGN  hrgn;			//区域
}RRES;

//按钮控制运行参数格式
typedef struct RPUSH{	//76
	DObj  *bs;			//对象地址
	CDRect  rt;			//占用的矩形区
	N_PUSH *psh;		//属性地址
}RPUSH;

typedef struct RACTOBJ{	//活动对象
	DObj    *bs;		//对象地址
	N_ACTOBJ *act;		//属性地址
	int recno;			//运行时设备的绝对记录号，与数据库有关
	CRect  rt;			//占用的矩形区
	double curval;		//实时值
	double maxv;		//最大值
	double minv;		//最小值
	CDRect  oldrt;		//原来的位置
	CDRect  currt;		//当前位置
	WORD   picw,pich;	//显示图片的宽高
	short  picj;		//图片的记录号
	BYTE   js;			//当前计数
	DPOINT  *pt;		//路经
	int    ptsum;		//点数
}RACTOBJ;

typedef struct RFLASH{
	CRect rt;			 //占用的矩形区
	N_FLASH *fsh;		 //属性地址
	CShockwaveFlash fshw;//flash窗口
}RFLASH;

typedef struct RPPIE{
	DObj  *bs;			//对象地址
	int recno;			//运行时设备的绝对记录号，与数据库有关
	CDRect rt;			//占用的矩形区
	N_PCTPIE *ppe;		//属性地址
}RPPIE;

typedef struct RZONE{	//动画对象
	DObj *bs;			//对象地址
	int recno;			//运行时设备的绝对记录号，与数据库有关
	CDRect rt;			//占用的矩形区
	N_ZONE *zon;		//对象的指针
	HRGN  hrgn;			//区域
	int     js;			//计数
	double  step;		//步长
}RZONE;

/////////////////////////////////////////////////////////////////////
//建立索引库所需的结构
typedef struct C_NODE{  //节点
	int  nodeid;		//节点ID
	BYTE ele;			//带电状态 0=不 1=带
	BYTE red[3];
}C_NODE;


typedef struct C_SITE{	 //端子定义
	BYTE   vl;			 //电压等级
	BYTE   red[3];
	DRECT	srt;		 //端子矩形区
	int		id;			 //端子ID
	int		nodeid;		 //连接到的节点ID
}C_SITE;


typedef struct C_SITEA{	 //端子定义
	BYTE    vl;			 //端子电压等级
	BYTE     red[3];
	DPOINT	npt;		 //端子点位置
	DRECT   srt;		 //端子的矩形区
	int		id;			 //端子ID
	int		nodeid;		 //连接到的节点ID
}C_SITEA;

typedef struct C_SITEB{	 //端子定义
	BYTE    vl;			 //端子电压等级
	BYTE     red[3];
	DPOINT	npt;		 //端子点位置
	DRECT   srt;		 //端子的矩形区
	int		id;			 //端子ID
	int		nodeid;		 //连接到的节点ID
}C_SITEB;

typedef struct C_BUS{	 //母线
	int		id;			 //唯一的ID(与图元的不同) 
	DObj	*bs;		 //结构地址
	N_BUS	*bus;		 //参数地址
	BYTE	status;		 //状态 0=正常 1=有问题
	C_SITE	msite;		 //本设备端子
}C_BUS;

typedef struct C_LINE{	 //线路
	int		id;			 //唯一的ID(与图元的不同)
	DObj	*bs;		 //结构地址
	N_FLOW	*lin;		 //参数地址
	BYTE	status;		 //状态 0=正常 1=有问题
	C_SITEB msite[2];	 //本设备端子
}C_LINE;


typedef struct C_DEV{	 //设备
	int		id;			 //唯一的ID(与图元的不同) 
	DObj	*bs;		 //结构地址
	N_ELEGRPA *ele;		 //参数地址
	BYTE	type;		 //类型
	BYTE	status;		 //状态 0=正常 1=有问题
	C_SITE	msite[3];	 //本设备端子(最大3端子)
	BYTE	sitsum;		 //端子数
	BYTE     red[3];
}C_DEV;


typedef struct C_CONLINE{//连接线
	DObj	*bs;		 //结构地址
	N_CONLINE *conl;	 //参数地址
	BYTE	status;		 //状态 0=正常 1=有问题
	C_SITEA msite[2];	 //本设备端子
}C_CONLINE;


//////////////////////统计用结构///////////////////////////////////
/*typedef struct STATES{//统计结果
	int		devsum;		//设备数
	int		stopsum;	//停运数
}STATES;*/



//访问计算数据
typedef struct _READDEV_FLW{ //用于访问线路的P,Q
	int  did;				 //设备ID
	BYTE dtype;				 //设备类型
	R_FLW val;				 //可返回P,Q,越限
	float maxp;				 //有功上限
	float ptdf;				 //有功分配因子
}READDEV_FLW;

//访问组合图源相关数据(状态值 含带电状态)
typedef struct _READDEV_STA{ //设备的数据访问
	int  did;				 //设备ID
	int  recno;				 //绝对记录号
	BYTE subtype;			 //设备类型 0=PT 1=发电机 2=开关,刀闸 3=负荷 4=电容 5=电抗 6=接地 7=二绕组变压器",8=三绕组变压器
	BYTE zt;				 //状态
	BYTE ele;				 //带电
	BYTE rp;				 //检修状态
	BYTE trb;				 //
	CTime tm;				 //开关动作时间(开关时有效)
}READDEV_STA;

//访问区域有功及其损耗计算数据
typedef struct _READZONE_PL{ //用于访问线路的P,Q
	int  did;				 //区域ID
	BYTE type;				 //类型
	float Pgen;				 //区域总有功出力
	float Plos;				 //区域有功损耗
}READZONE_PL;
//访问百分饼图数据
typedef struct _READPPCTPIE{ //用于访问百分饼图数据
	int  did;				 //设备ID
	BYTE type;				 //类型
	float MaxV;				 //最大值
	float curval;			 //当前值
}READPPCTPIE;
//定义颜色表
typedef struct DEFCOLOR{     //颜色表
	char VLName[16];		 //电压名
	BYTE R,G,B;				 //颜色分量
}DEFCOLOR;
//灵敏度
typedef struct SSEN
{
	DWORD  NU;				//设备相关ID
	BYTE   type;			//设备类型
	/*
	0=发电机
	1=负荷
	2=电容
	3=两绕组变压器
	4=三绕组变压器
	*/
	float senval;			//灵敏度值(%)
}SSEN;
//访问灵敏度数据
typedef struct READSEN
{
	int ssum;				//灵敏度个数
	SSEN se[15];			//灵敏度值
}READSEN;

////////////////////////////////////////////////////////////////////////////
//以下定义用于读取设备的浏览信息
//0.发电机
typedef struct GenData{
	char	gname[64];		//发电机名
	int		gid;			//发电机ID
	char	bname[64];		//连接的母线名
	int     bid;			//母线的ID
	float	sngKV_LVL;		//电压等级
	float	sngGEN_MW;		//发电机有功出力	
	float	sngGEN_MVAR;	//发电机无功出力
	float	sngMAX_MW;		//有功上限
	float	sngChk_MW;		//检修有功
}GenData;
//1.交流线路
typedef struct LinData{
	char    lname[64];		//线路名
	int     lid;			//线路ID
	int     bus_idf;		//母线起点ID
	int     bus_idt;		//母线终点ID
	char    bfnm[64];		//起端母线名称
	char    btnm[64];		//末端母线名称
	float   vl;				//电压等级
	float	sngMW;			//流向末端有功
	float	sngMVAR;		//流向末端无功
	float   Pmax;			//容量
}LinData;
//2.直流线路
typedef struct DLinData{
	char    lname[64];		//线路名
	int     lid;			//线路ID
	int     bus_idf;		//母线起点ID
	int     bus_idt;		//母线终点ID
	char    bfnm[64];		//起端母线名称
	char    btnm[64];		//末端母线名称
	float   vl;				//电压等级
	float	sngMW;			//首端有功功率
	float	sngMVAR;		//首端无功功率
	float   Pmax;			//容量
}DLinData;
//3.母线
typedef struct BusData{
	char    bname[64];		//母线名称
	int     bid;			//母线ID
	float	sngKV_LVL;		//电压等级
	float	sngVOLTAGE_PU;	//电压幅值;ＰＵ
	float	sngVOLTAGE_DEG; //电压相角
	float   vb;				//母线实际电压值
	float   Vmax;			//最大电压
	float   Vmin;			//最小电压
	float   Hilimit;		//上限
	float   Lolimit;		//电压下限
}BusData;
//4.负荷
typedef struct LoadData{
	char	lname[64];		//负荷名称
	int		lid;			//负荷ID
	float   vl;				//电压等级
	int		intsta;			//负荷状态；1＝投入，0＝退出
	float	sngPL;			//初始有功负荷，MW
	float	sngQL;			//初始无功负荷，MVAR
}LoadData;
//5.变压器2绕组
typedef struct TrfData1{
	char    tname[64];		//变压器名称
	int     tid;			//变压器ID
	float   hlv;			//高电压等级
	float   tagh;			//高档位
	float   maxp;			//最大值(额定功率)
	float   curp;			//当前有功
	float   curq;			//当前无功
	float   Tcur;			//当前温度
	float   Tmax;			//最大温度
}TrfData1;

//6.变压器3绕组
typedef struct TrfData2{
	char    tname[64];		//变压器名称
	int     tid;			//变压器ID
	float   hlv;			//高电压等级
	float   tagh;			//高档位
	float   mlv;			//中电压等级
	float   tagm;			//中档位
	float   llv;			//低电压等级
	float   tagl;			//低档位
	float   maxp;			//最大值(额定功率)
	float   curp;			//当前有功
	float   curq;			//当前无功
	float   Tcur;			//当前温度
	float   Tmax;			//最大温度
}TrfData2;

//7.电容器
typedef struct ShuData{
	int     devid;			//设备ID
	char    sname[64];		//设备名称
	int     busid;			//母线ID
	char    bname[64];		//节点名称
	float   vl;				//电压等级
	float   qst;			//电容步长
	float   c;				//投入容量
	char    sta;			//投运状态
}SHuData;

//8.串联电抗
typedef struct SrdData{
	char	name[64];		//设备名称
	int		id;				//设备ID
	float   vl;				//电压等级
	char	sta;			//投入状态；1＝投入，0＝退出
	float	sngZX;			//串联电抗
}SrdData;

//9.SVC投切
typedef struct  SvcData{
	char    sname[64];		//名称
	int     id;				//SVCid
	int     busid;			//母线id
	char    bname[64];		//母线名称
	float   vl;				//电压等级
	float   Q;				//投入容量
	char    sta;			//投入状态；1＝投入，0＝退出
}SvcData;


//界面相关结构
typedef struct I_DBF{   //数据库名
	char name[256];		//数据库名
}I_HTTP;




typedef struct I_APP{   //应用定义
	char name[64];		//应用名称
	char appno;			//应用编号
}I_APP;

typedef struct MENUINI{  //初始化菜单结构
	char text[45];
	char filenm[64];
}MENUINI;

typedef struct _SHOWSAVESET{
	DWORD head;					//=0x20030300
	int sound;					//是否播放音效
	int	showsite;				//是否显示端子
	int showdgx;				//是否显示等高线0=不显 1=显示
	int showover;				//输电线过负荷 0=不显 1=显示
	int dgxcolor;				//等高线1=彩色 0=黑白
	int dgxmode;				//等高线模式0=依赖母线形状 1=依赖于中心点
	int dgxtran;				//等高线背景透明 0=不透明 1=透明(保留背景图案)
	int Nouse;					//未用
}SHOWSAVESET;


typedef struct  _HISHMI{		//历史界面结构，用于返回功能
	char mode;					//mode=0表示正常切换回来mode=1表示自动放大切换
	char filename[256];			//界面文件名
	int  picno;					//界面序号
	double zoom;				//切换时的放大倍数
	int  dx;					//水平方向偏移量
	int  dy;					//垂直方向偏移量
	char showdgx;				//是否显示等高线0=不显 1=显示
	char showrev;				//发电机储备 1=有功 2=无功 3=变压器
	char ctrtype;				//等高线类型
	char lookdown;				//是否俯视
	double vx,vy;				//镜头中心点
	WORD  cursor;				//当前光标
}HISHMI;

typedef struct _CTLMENU{		//控件菜单新旧ID对照表
	HWND hWnd;					//窗口句柄
	int oldid;					//旧ID
	int newid;					//新ID
}CTLMENU;

//////////////////////////////////////////////////////////////////////
//母线关联图形关系结构
typedef struct BUSFILE{ //母线文件关联结构
	char name[24];		//母线名称
	long id;			//母线ID
	char grpfile[24];   //文件名
	BYTE index;         //图形中的序号
}BUSFILE;

typedef struct GBUS{	//来自于图形中的母线
	char name[24];		//母线名称
	long id;			//母线ID
}GBUS;

typedef struct BFHEAD{  //保存头文件
	WORD flag;			//标志0xd0
	WORD version;		//版本
	WORD sum;			//个数
}BFHEAD;
////////////////////////////////////////////////////////////////////////
//断面潮流结构
typedef struct DMLINE{
	BYTE  type;			//0=交流线路 1=直流线路
	int   id;			//0=设备ID
	int   jlh;			//数据库中的记录号
}DMLINE;

typedef struct DMSECT{	//单个断面结构
	char   name[16];	//断面名称
	BYTE   lsum;		//线路总数
	DMLINE ls[32];		//最大32条线路
	float  Imax;		//最大电流容量
	float  Icur;		//当前电流 
	float  Pmax;		//有功容量
	float  Pcur;		//当前有功
	int   segsum;		//段数
	int   dmsdot[10];	//每段终点，第一段起点为0 第二段起点为第一段终点+1
	DPOINT pt[500];		//最大500点
}DMSECT;

//自定义断面存储结构
typedef struct DMSAVE{
	WORD flag;		  //头标志 =0xc0
    WORD version;	  //版本号 0x10
	BYTE dmsum;		  //断面个数
	//后跟所有的断面 
}DMSAVE;


//历史文件中的文件相关结构
//文件列表
typedef struct FILEINFO{				//文件信息
	char  filename[64];					//文件名
	DWORD fsize;						//文件大小
	DWORD offset;						//在文件中的偏移量
}FILEINFO;

//历史数据库头
typedef struct HISHEAD{
	DWORD  fileflag;					//文件标志=0x10101010
	DWORD  version;						//版本号=0x10000000;
	WORD   sizehead;					//结构字节大小
	char   name[24];					//名字=可视化历史库
	WORD   year;						//年
	BYTE   mon;							//月
	BYTE   day;							//日
	BYTE   fnum;						//界面文件个数
	DWORD  offselist;					//文件列表的偏移量
	char   reserved[64];				//保留64字节
}HISHEAD;

//////////////////////////////////////////////////////////
//俯视文字输出特殊结构
typedef struct _TEXTM
{
	DPOINT pt1[4];	//放大后俯视前位置
	DPOINT pt2[4];  //旋转后位置
	char  str[32];	//显示的字符串
	int   fw,fh;	//字体的高度、宽度
}TEXTM;

////////////////////////////////////////////////////////////////////////////////////
//低频震荡传输数据结构
typedef  struct _PHead	//通信头
{
	WORD  flag;			//头标志=0xcc;
	BYTE  funct;		//功能
	DWORD packsize;		//包大小
}PHead;

typedef struct _SENDLFDATA //发送数据(1秒钟的数据)
{
	WORD  flag;			//头标志=0xcc;
	BYTE  funct;		//功能
	DWORD packsize;		//包大小
	BYTE  nline;		//线路数，每线路需要一个LFDATA传输
	LFDATA lfd[1];		//实际发送的数据量以lfd中的有效数据量为准
}SENDLFDATA;

//低频震荡内存缓冲结构(每线路一个)
typedef struct LOWFMEM
{
	DWORD  LineID;		//线路ID
	BYTE   Type;		//类型交流或直流
	float  maxv;		//最大限幅值
	float  frq;			//本数据的频率(1秒的平均频率)
	float  lfp;			//低频震荡功率(1秒的平均功率)
	float  lfd[25];		//1秒数据
}LOWFMEM;


typedef struct SHOWCFG{
	WORD ver;					//版本=0x1000;
	char first;					//第一次标志 0=第一次 1=否
	char showdgx;				//是否显示等高线0=不显 1=显示
	char gendyn;				//动态显示发电机 
	char showrev;				//发电机储备 1=有功 2=无功 3=变压器
	char flowover;				//过流推出
	char ctrtype;				//等高线类型0=母线电压 1=母线电压低 2=母线电压高 3=输电线状态 
								//4=节点电价
	char tranbg;				//等高线透明背景
	BYTE smooth;				//等高线平滑度1-30;
	BYTE oneline;				//等高线是否单线 0=过渡色 1=单线
	CTR_COLOR cr[20];			//当前系统运行的等高线颜色目前6种 其他留作备用 
	char reserved1;				//未用1
	char cpu;					//CPU性能0=低CPU 1=高CPU
	char lowf1;					//低频震荡显示
	char lmd;					//灵敏度显示
	float Pref;					//潮流箭头参考有功值
	float Qref;					//潮流箭头参考无功值
	float Iref;					//电流潮流参考值
	float vppe;					//百分饼图的开始显示值，缺省为50%
	float senzoom;				//灵敏度放大倍数
	float pqzoom;				//有功无功放大倍数
	float tpzoom;				//变压器功率放大倍数
	float tptzoom;				//变压器温度放大倍数
	DWORD syscolor[40];			//颜色配置,用于棒图等
	BYTE  swtsum;				//开关动作顺序个数
	char  ftype;				//当前潮流显示类型
	DWORD sencolor[5];			//灵敏度颜色
	float gen3dminp;			//发电机3D显示时的最小容量
	char reserved[99];			//保留备用
	BYTE showplate;					//显示挂牌 0不显示，1全部显示，2显示保护信息，3显示当前检修，4显示次日检修，5显示接地， 6事故故障 7冷备 8热备 9充电 10二次保护动作
}SHOWCFG;


//负荷和实时数据
typedef struct FLOADDATA
{
	float FValue;
	float RValue;
	BYTE  hour;
}FLOADDATA;

//告警结果
typedef struct SYSALARM
{
	WORD  Alarm;						//告警状态0,1
	WORD  num;							//发生告警的设备个数
	char  picname[32];					//推出画面名称
	WORD  picno;						//推出画面序号
}SYSALARM;


typedef struct N1Data{
	int  id;			//设备ID
	char type;			//故障类型
	BYTE  Group;		//分组类型
	float val;			//值
}N1Data;

//PMUSVR结构
typedef struct _PSvrIpPort
{
	DWORD ip;
	WORD  port;
}PSvrIpPort;


typedef struct LowFLPam
{
	DWORD  LineID;						//线路ID
	BYTE  Type;							//类型交流或直流
	BYTE  UnitNo;						//装置号
	BYTE  Index;						//数据序号
	BYTE  DotPs;						//原始数据点数/每秒
	float  MaxV;						//最大幅值限制
}LowFLPam;


//报警配置
typedef struct ALMCFG
{
	BYTE sound; //声音
	BYTE pop;	//是否弹出
	BYTE flash; //闪烁
	char reserved[13]; //保留
}ALMCFG;

//报警配置的保存结构
typedef struct ALMSAVE
{
	int flag;		//flag=0xd0d0;
	ALMCFG cfg[7];
}ALMSAVE;


//================挂牌信息结构
int const MAXPLATE=300; //最大挂牌数量

typedef struct _PlateInfo
{
	_PlateInfo()
	{
		m_devid=0;
		m_platetype=0;
		//		m_name[0]=0;
		m_rgn=NULL;
		memset(this, 0, sizeof(_PlateInfo));
	};
	DWORD m_devid;		//设备ID
	BYTE m_typemenu;	//设备枚举类型
	BYTE m_subtype;		//图形内部设别类型
	BYTE m_platetype;	//挂牌类型，与图片定义顺序一致
	//	char m_name[64];
	HRGN m_rgn;			//挂牌区域
	CPoint m_center;		//挂牌中心位置
	//	void* m_pdev;		//挂牌对象
	//	bool m_sta;			//用于表示挂牌的有效性，true有效，false无效，当无效时不能删除，避免读写错误，如果有新的挂牌进入可以填写在无效的位置
}PlateInfo;
//================挂牌信息结构


#endif