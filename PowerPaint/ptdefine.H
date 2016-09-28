#if !defined(AFX_NTPTDEF_H__INCLUDED_)
#define AFX_NTPTDEF_H__INCLUDED_

#include "jhsyslibl.h"

#define  MAXPAGE  128
#define  MAXSPIC  64
#define  MAXEGRP  1024
#define  MAXGIF   64
#define  MAXLAYER 8
#define  MAXUNDO  64
#define  MAXSIZE  10000

class BASE0;


//剪贴板结构
typedef struct _CLPDATA
{
	int   flag;//=0x1f9d3445
	int   objsum;
	int   objsize;
	char  reserved[128];
}CLPDATA;
/////////////////////////////////////////////////////////////
typedef struct _UNDOSTEP{//UNDO动作
  BYTE  type;	//操作 0=无效 1=移动 2=删除 3=添加 4=页面切换 
				//5=层面切换  	
  int   objsum;	//对象数
  BASE0 *bakbs;	//对象
}UNDOSTEP;

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
	BYTE  type;				//类型
	char  name[15];			//名字
	BYTE  subtype;			//子类型
	BYTE  sitesum;			//端子数,仪表时代表仪表的个数
	DRECT srt[3];			//3个端子位置
	BYTE  index[16];		//仪表的序号 ,最多16个仪表
	char  reserved[10];		//保留字节20
	WORD  id;				//内部ID号
	WORD  bsum1;			//图形数1
	BASE0 *bs1;				//图形1
	DRECT  rt1;				//占用的矩形
	WORD  bsum2;			//图形数2
	BASE0 *bs2;				//图形2
	DRECT rt2;				//占用的矩形
}N_ELEGRP;

typedef struct N_ETNAME
{
	char  name1[64];   //SVG名字
	char  name2[64];	
	float em11,em12,em21,em22,edx,edy; 
	DRECT rt1,rt2;
}N_ETNAME;

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
	unsigned char nonuse:7;  //保留，暂无用
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
	BASE0   *obj;			//对象地址指针
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
	int		 zw,zh;		     //缩放后的宽高
}N_PAGEPWF;

////////////////////////////////////////////////
typedef struct N_BASATTR{    //对象基本属性  
	WORD  type;				 //对象类型
	BYTE  belong;			 //所属端子 只有组合图元才有效
	DWORD ID;				 //对象ID
	WORD  size;              //对象字节数
}N_BASATTR;

typedef struct N_DBX{		 //多边形 type=1  r1
	BYTE  fill;			     //0=不填充 1=填充
	BYTE  fillmode;			 //填充方式
	BYTE  close;			 //0=不封闭   1=封闭 
	BYTE  ltype;			 //线类型
	BYTE  autozoom;			 //是否自动放大线条
	BYTE  lmode;			 //模式 0=正常 1=边框
	BYTE  bgmode;			 //背景模式
	double width;			 //线宽度
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
	BYTE   autozoom;		 //是否自动放大线条
	BYTE   type;			 //0=平面 1=凹 2=凸
	double width;			 //线宽度
	DWORD  lcolor;			 //线颜色
	DWORD  bcolor1;			 //填充颜色1
	DWORD  bcolor2;			 //填充颜色2
}N_RECT;

typedef N_RECT N_CIRCLE;	 //园 type=3  r3
    

typedef struct N_HSIN{		 //正弦半波形 type=4  r4
	DPOINT pt[4];			 //4个角坐标
	BYTE  ltype;			 //线类型
	BYTE  lmode;			 //模式 0=正常 1=边框
	BYTE  endcap;			 //线头模式
    BYTE  pirodic;			 //周期数
	BYTE  autozoom;			 //是否自动放大线条
	double  width;			 //线宽度
	DWORD color;			 //线颜色
	DWORD bcolor;			 //填充色
}N_HSIN;



typedef struct N_SIN{		 //正弦波形  type=5 r5
	DPOINT pt[4];			 //4个角坐标
	BYTE  ltype;			 //线类型 0=水平 1=垂直
	WORD  startdeg;			 //开始角度0-359
	BYTE  pirodic;			 //周期数
	DWORD color;			 //线颜色
	char resed[4];			 //保留
}N_SIN;


typedef struct N_ARC{		 //园弧 type=6  r6
	DPOINT  pt[4];			 //4个角坐标
	DWORD   color;			 //颜色
	BYTE  autozoom;			 //是否自动放大线条
	double  width;			 //宽度
	short    start;			 //开始角度
	short    end;			 //结束角度	
}N_ARC;

typedef struct N_ARROW{      //方向箭头  type=7  r7
	DPOINT  pt[2];			 //两点坐标
	BYTE    autozoom;		 //是否自动放大线条
	double  width;			 //线宽度
	DWORD   color;			 //线颜色	
}N_ARROW;

typedef struct N_GLASS{      //玻璃层    type=8
	DPOINT  pt[4];			 //4个角坐标
	BYTE    depth;			 //深度
	DWORD   color;			 //线颜色
	BYTE    outline;		 //是否画边线
	DWORD   ocolor;			 //边线色
}N_GLASS;


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
	double width1;			 //坐标线宽
	double width2;			 //水线线宽
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
	BYTE  shadow;			 //阴影
	BYTE  depth;		     //透明度
	BYTE  zoom;				 //支持缩放出0=No 1=Yes
	WORD  imgID;			 //ID
}N_IMG;

typedef struct N_PATH{		 //路径 type=16  r10
	WORD  ID;				 //路经ID
	double  start;			 //起点坐标
	double  end;			 //终点坐标
	DWORD color;			 //编辑时显示颜色
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N_PATH;

typedef struct N_SPIC{	     //静态小图标type=17
	DPOINT pt[4];			 //4个角坐标
	WORD  picID;			 //ID
	BYTE  zoom;				 //支持放缩 0=no 1=yes
}N_SPIC;
///////////////////特殊动态类//////////////////////////////////////////////

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
}N_METER3;

//动态仪表4
typedef struct N_METER4     //基本仪表参数(数码) type=35
{
	DPOINT  pt[4];			//4个角坐标
	BYTE    num;			//总位数
	BYTE    numdot;			//小数位数
	DWORD   bcr;			//边框颜色
	DWORD   ncr[2];			//整数和小数部分的颜色
}N_METER4;


/////////////////////以下为动态运行对象///////////////////////////////

typedef struct R_ANL{		 //模拟量实时值 
	float curval;			 //当前值
	unsigned char alarm:1;	 //是否越限
	unsigned char enable:1;	 //当前值是否有效
	unsigned char ele:1;	 //带电状态
	unsigned char resd:5;	 //坏数据
	char reserved;			 //保留		 
}R_ANL;

typedef struct R_FLW{		 //线路实时值  
	float p;				 //有功当前值
	float q;				 //无功当前值
	unsigned char enable:1;	 //当前值是否有效
	unsigned char ele:1;	 //带电状态
	unsigned char nouse:6;	 //未用
	char  reserved[3];		 //保留
}R_FLW;


typedef struct R_STA{		 //状态量实时值
	unsigned char zt:1;		 //当前状态
	unsigned char enable:1;	 //当前值是否有效
	unsigned char ele:1;	 //带电状态
	unsigned char reserve:5; //未用
	char red[4];			 //保留
}R_STA,R_DEV,R_STA;

//定义单点数据源（只能选择其中一点数据)
typedef struct _SINGLEDBS{   //单点数据源
	char  name[64];			 //设备名字
	int   did;				 //设备ID
	BYTE  dtype;			 //设备类型
	BYTE  xsmode;			 //值索引
}SINGLEDBS,DBSRC;
// xsmode和dtype的关系见<读入设备运行value顺序定义.doc>文档

/////////////
typedef struct N_ANL{        //模拟量显示结构 type=64 r11
	DPOINT   pt[4];			 //4个角坐标
	double   zm;			 //绘图时的倍率
	LOGFONT  lf;		     //字体
	COLORREF acolor;	     //告警颜色
	COLORREF ncolor;	     //正常颜色
	BYTE     xs;			 //小数位
	BYTE     style;		     //显示风格
	BYTE     direction;		 //方向0=x方向 1=Y方向
	R_ANL    rval[16];		 //实时值
	char     dev_name[64];	 //设备名
	long	 did;			 //设备ID
	BYTE     dtype;			 //设备类型 0=发电机 1=交流线路 2=直流线路 3=母线 4=负荷  5=2绕组变压器 
							 //	6=3绕组变压器 7=电容器 8=电抗器 9=SVC
	BYTE     xsmode;		 //见下面,不同对象有不同的含义
}N_ANL;

typedef struct N_RESERVOIR{  //水库对象   type=65
	DWORD color;			 //线颜色
	DWORD ncolor;			 //正常时颜色
	DWORD hcolor;			 //高水位颜色
	DWORD lcolor;			 //低水位颜色
	char  dev_name[64];		 //水库名
	long  did;				 //水库ID
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
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

typedef struct N_ELEGRPA{    //组合图元显示结构type=66 
	DPOINT   pt[4];			 //4个角坐标
	BYTE     type;			 //数据类型类型 0=仪表 1=设备 2=站 3=公司
	BYTE     subtype;		 //子类型 当type=1 时为设备类型
	WORD     egrpid;		 //组合图元ID号
	BYTE     showno;		 //绘图时的显示号0和1
	R_STA	 rval[3];		 //当前端子的状态
	BYTE     sitesum;		 //端子数
	D_SITE   site[3];		 //三个端子
	short    dydeg;			 //动态角度(需要动态显示的图形)
	float    p;				 //有功(与设备有关)
	float    q;				 //无功(与设备有关)
	float    maxp;			 //最大有功
	float    minp;			 //最小有功
	short    angle;			 //发电机角度
	float    sen;			 //灵敏度=0时,不显示
	BYTE     genrev;		 //是否显示发电机备份(发电机时有效)
	BYTE     runshow;		 //运行时是否显示
	char     dev_name[64];	 //设备名
	long     did;			 //设备记录号
}N_ELEGRPA;


typedef struct MTRRANGE{	 //仪表运行参数及限值
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
	MTRRANGE pam[8];		 //用户自定义量程
}N_ELEGRPYB;


typedef struct N_SYSPIE{     //饼图结构数据 type=68
	DPOINT  pt[4];			 //4个角坐标
	WORD    ID;				 //ID号
	DWORD   fcolor;			 //字符色
	LOGFONT lf;				 //字体
	BYTE    type;			 //类型
	DWORD   color[6];		 //6个颜色 最大6个部分
	char    rev[64];		 //保留
}N_SYSPIE;

typedef struct N_BAR{		 //棒图 type=69
	DPOINT pt[4];			 //4个角坐标
	int   xy;                //0=x方向 1=Y方向
	int   id;				 //保留ID内部用
	float max;				 //最大值
	float min;				 //最小值
    BYTE  outline;			 //外框
    BYTE  style;			 //式样
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
}N_PIEPAM;

typedef struct N_DATE{       //日期格式     type=71 r14
	DPOINT  pt[4];			 //4个角坐标
	double  zm;
	BYTE    fmt;			 //日期格式 0=yyyy-mm-dd 1=mm/dd/yyyy 2=yyyy年mm月dd日
	BYTE    outline;		 //边框 0=无 1=正常 1=凹 2=凸
	BYTE    tran;			 //背景透明吗？0=No 1=Yes
	DWORD   outcolor;		 //边线色
	DWORD   fcolor;			 //字符颜色
	DWORD   bcolor;			 //背景色
	LOGFONT font;			 //字体
	BYTE    style;			 //字体显示 0=正常 1=凹 2=凸
	BYTE    shadow;			 //字体阴影显示
	CTime   tm;				 //时间
}N_DATE;

typedef struct N_TIME{		 //时间格式     type=72 r15
	DPOINT  pt[4];			 //4个角坐标
	double  zm;
	BYTE    fmt;			 //时间格式 0=hh:mm:ss 1=hh:mm 2=hh时mm分ss秒
							 //3=hh点mm分ss秒 4=mm分ss秒	
	BYTE    outline;		 //边框 0=无 1=正常 1=凹 2=凸
	BYTE    tran;			 //背景透明吗？0=No 1=Yes
	DWORD   outcolor;		 //边线色
	DWORD   fcolor;			 //字符颜色
	DWORD   bcolor;			 //背景色
	LOGFONT font;			 //字体
	BYTE    style;			 //字体显示 0=正常 1=凹 2=凸
	BYTE    shadow;			 //字体阴影显示
	CTime   tm;				 //时间
}N_TIME;

typedef struct N_GIFAML{     //静态图形  type=73
	DPOINT  pt[4];			 //4个角坐标
	char  fname[256];		 //文件名
	WORD  rec;				 //GIF图形内部记录,显示用
	BYTE  type;				 //关联类型：状态量,设备,站
	R_STA rval;				 //当前状态
	SINGLEDBS dsrc;			 //数据源
}N_GIFAML;

typedef struct N_SRLTEXT{	 //滚动文本  type=74
	DPOINT  pt[4];			 //4个角坐标
	double  zm;
	BYTE direct;			 //方向   0=静态文本 1=上下 2=左右 
							 //3=下上 4=右左
	BYTE tstyle;			 //文本样式 0=正常 1=凹 2=凸
	BYTE glass;				 //是否用玻璃层 0=No 1=Yes
	BYTE outline;			 //是否有外框
	BYTE depth;				 //深度
	DWORD fcolor;			 //边框
	DWORD gcolor;			 //玻璃颜色
	DWORD tcolor;			 //文本颜色
	LOGFONT lf;				 //文字字体
	BYTE  align;		     //排列方式 0=居左 1=居中 2=居右
	BYTE  shadow;			 //是否阴影
	WORD  id;				 //ID号
	char text[256];			 //文字串
}N_SRLTEXT;

typedef struct N_PUSH{		 //按钮格式   type=75
	DPOINT  pt[4];			 //4个角坐标
	double  zm;
	BYTE  style;			 //按钮式样0=普通按钮 1=不可见按钮
							 //2=滑过凸形按钮 3=滑过凹形按钮 
							 //4=滑动变色 5=图标按钮
	char  title[64];		 //按钮标题
	WORD  spicid;			 //小图标ID号
	BYTE  autlin;			 //位图按钮时,自动边线
	BYTE  fstyle;			 //文本显示属性
	BYTE  shadow;			 //阴影
	BYTE  cmdtype;			 //命令类型
	WORD  cmdnum;		     //自定义时的WM_COMMAND消息wParam
	char  command[64];		 //命令字符串
	DWORD color1;			 //颜色1
	DWORD color2;			 //颜色2
	int   selfid;			 //要控制的自助控件的ID
	LOGFONT lf;				 //字体
	WORD  id;				 //自身ID
	BYTE  down;				 //压下状态
	BYTE  edit;				 //编辑状态
	BYTE  tosta;			 //目标状态,打开画面时用
}N_PUSH;

typedef struct N_SELFCTL{   //自助控件  type=76
	DPOINT  pt[4];			//4个角坐标
	char  dllname[256];		//动态连接库名
    DWORD style;			//属性,由控件设置
    int	  id;				//ID号,以便相互控制
    char  lkbuf[255];		//启动时的连接缓冲区
    BYTE  aleft;			//左对齐
    BYTE  aright;			//右对齐
    BYTE  atop;				//上对齐
    BYTE  abottom;			//下对齐
	BYTE  mode;				//类型:0=编辑位置 1=其他暂未用
    HINSTANCE hinst;        //DLL的事例
	HMENU hmenu;			 //控件菜单
    HWND  hwnd;				//窗口句柄
    void  *rc;				//初始化产生的资源(如果有)
    int  (WINAPI*DfGetVer)();//返回版本号
    void (WINAPI*DfDrawDemo)(HDC,RECT,DWORD,char *);		//演示绘图
    void*(WINAPI*DfInit)(HWND,HWND&,RECT,int,DWORD,char*);	//初始化
    void (WINAPI*DfClose)(void *rc);						//关闭
    void (WINAPI*DfAbout)();								//关于该控件
    void (WINAPI*DfSetParam)(DWORD&,char*);					//配置参数
	void (WINAPI*DfPrint)(HDC,RECT,BYTE);					//提供打印支持
	HMENU (WINAPI*DfLoadMenu)();							//配置参数
}N_SELFCTL;

typedef struct R_FLOW{		//潮流运行参数
	char     pjs;			//有功起点计数
	char     qjs;			//无功起点计数
	unsigned char  canrun:1;//是否满足条件显示潮流线 0=不满足 1=满足
	unsigned char  pdir:1;	//有功方向
	unsigned char  qdir:1;  //无功方向
	unsigned char  rev:5;	//保留
	char     reserved;		//保留1字节
}R_FLOW;

typedef struct N_FLOW{		//潮流线    type=77 r16
	R_FLOW  rf;				//运行参数
	BYTE  style;			//式样 0=一般线条 1=只显有功 2=只显无功 3=同时显示
	R_FLW rval;				//当前值
	BYTE  vl;				//电压等级	 
	D_SITEB site[2];		//端子
	DWORD color1;			//有功颜色
	DWORD color2;			//无功颜色
	BYTE  yh;				//优化0=优化前 1=优化后
	BYTE  direct;			//方向0=潮流方向与画线方向一致 1=与画线方向相反
	BYTE  type;				//类型 0=交流 1=直流
	BYTE  linewidth;		//线条宽度
	char  dev_name[64];		//设备名
	long  did;				//设备记录号(ID)
	WORD  ptsum;			//点总数
	DPOINT pt[1];			//后跟所有的点
}N_FLOW;

typedef struct LOGOBJ{		//连接线用的连接对象记录
	BYTE  layer;			//所在层
	short jlh;				//记录号
	unsigned char sitn:3;	//连接的端子
	unsigned char reserved:5;	//保留
}LOGOBJ;

typedef struct N_CONLINE{	//连接线  type=78 r17
	BYTE    autozoom;		//是否自动放大线条
	double  width;			//线宽度
	BYTE	shadow;			//阴影
	BYTE	solder1;		//焊接点1显示0=不显示 1=显示
	BYTE	solder2;		//焊接点2显示0=不显示 1=显示
	BYTE	vl;				//电压等级
	BYTE    conobj;			//连接到设备标志 =0 未连接 =1 已连接
	BYTE    el;				//带电状态 =0 不带电 =1 带电
	LOGOBJ  lobj[2];		//两个端子连接的对象
	WORD	ptsum;			//点总数
	DPOINT	pt[1];			//后跟所有的点
}N_CONLINE;

typedef struct N_BUS{		//母线  type=79 r18
	DPOINT  pt[4];			//4个角坐标
	BYTE    type;			//类型
	BYTE    shadow;			//阴影
	BYTE	vl;				//电压等级
	R_STA	rval;			//实时值
	char    yh;				//优化前后
	char    valarm;			//电压告警状态 0=正常 1=越下限 2=越上限
	WORD    eid;			//组合图元ID
	char    dev_name[64];	//设备名
	long    did;			//设备ID号
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
	char  fname[256];		//swf文件名
	BYTE  playmode;			//播放模式0=一次 1=循环
	BYTE  align_left;		//左对齐
	BYTE  align_top;		//上对齐
	BYTE  align_right;		//右对齐
	BYTE  align_buttom;		//下对齐
}N_FLASH;


typedef struct N_PCTPIE{	//百分比饼图 type=82
	DPOINT  pt[4];			//4个角坐标
	double  zm;
	char    dev_name[64];   //设备名
	int     did;			//设备ID
	BYTE    type;			//数据类型 0=传输线 1=发电机
	DWORD   color1,color2;  //两个颜色
	DWORD   fcolor;			//字体颜色
	LOGFONT lf;				//数字字体
	float   maxv;			//最大值
	float   curval;			//当前值
}N_PCTPIE;

typedef struct N_ZONE{		//区域    type=83
	DWORD lcolor;			//边线颜色
	char  zone_name[64];	//区域名
	long  did;				//区域(ID)
	LOGFONT lf;				//字体
	DWORD fcolor;			//字体颜色
	WORD  ptsum;			//点总数
	DPOINT pt[1];			//后跟所有的点
}N_ZONE;

typedef struct N_MTTEXT{	//多行文本    type=84
	DPOINT  pt[4];			//4个角坐标
	DWORD fcolor;			//颜色
	char  name[64];			//名字
	BYTE  sta;				//状态值
	int   did;				//(ID)
	BYTE  type;				//类型
	LOGFONT lf;				//字体
	char  text[256];		//文本缓冲
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
//////////////////////////////////////////////////////////////////////////////////////////
//定义颜色表
typedef struct DEFCOLOR{    //颜色表
	char VLName[16];		//电压名
	BYTE R,G,B;				//颜色分量
}DEFCOLOR;
//////////////////////////////////////////////////////////////////////////////////////////


//访问组合图源相关数据(状态值 含带电状态)
typedef struct _READDEV_STA{ //设备的数据访问
	int  did;				 //设备ID
	int  recno;				 //绝对记录号
	BYTE subtype;			 //设备类型 0=PT 1=发电机 2=开关,刀闸 3=负荷 4=电容 5=电抗 6=接地 7=二绕组变压器",8=三绕组变压器
	R_STA sta;				 //状态，有效,带电
}READDEV_STA;

//访问设备的运行参数
typedef struct _READDEV{	 //用于访问设备的运行数据
	int   recno;			 //数据表中绝对记录号
							 //(第一次带入的参数可能是-1，以后返回正确的记录号)
	int   did;				 //设备ID
	BYTE  dtype;			 //设备类型
	BYTE  sta;				 //运行状态 0=停运、开 1=运行、合　
	BYTE  ele;				 //带电状态
	BYTE  enable;			 //返回值是否有效  
	float value[16];		 //最多可返回１６个浮点数，值的定义在程序中确认
	char extend[127];		 //其他
}READDEV;

//灵敏度
typedef struct SSEN
{
	WORD  NU;				//设备相关ID
	BYTE  type;				//设备类型
	float senval;			//灵敏度值(%)
}SSEN;

//访问灵敏度数据
typedef struct READSEN
{
	int ssum;				//灵敏度个数
	SSEN se[15];			//灵敏度值
}READSEN;

//电力系统参数合计
typedef struct PWSYSSUM{
	float Pgen; //系统总有功出力
	float Qgen; //系统总无功出力
	float Pl;	//系统总负荷P
	float Ql;	//系统总负荷Q
	float Prg;  //发电机旋转备份
	float Pall; //系统在线总装机容量
}PWSYSSUM;

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

typedef struct KWSIZE //关键字长度
{
	int sn; //开始串长度
	int en; //结束串长度
}KWSIZE;

#endif