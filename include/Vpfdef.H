#if !defined(AFX_NTPTDEF_H__INCLUDED_)
#define AFX_NTPTDEF_H__INCLUDED_

#include "jhdclib3.h"

#define  MAXPAGE 128
#define  MAXSPIC 64
#define  MAXEGRP 256
#define  MAXGIF  64

class Vpfobj;



typedef struct N_SUBPWF{	//子界面文件头
	char     Name[64];		//画面名字
	unsigned long BgColor;	//背景颜色
	unsigned char zoom:1;	//是否可放缩
	unsigned char move:1;	//是否可移动
	unsigned char posdlg:2;	 //对话框时的打开位置
	unsigned char resd:4;	 //未用完
	short    imgID;			//背景图片ID号<0表示无
	WORD     width;			//宽度
	WORD     height;		//高度;
	WORD	 ObjSum;        //对象总数
	DWORD    size;			//总字节数
	DWORD    psize;			//压缩后字节数
	char     resved[12];	//保留12字节
}N_SUBPWF;


typedef struct PRTMODE{		//打印模式
   BYTE  nobg;				//不打印背景
   BYTE  color;				//彩色打印
   BYTE  border;			//打印边框
   BYTE  center;			//图形居中
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


typedef struct N_MGifAml{	//GIF动画图形(只存第一帧)
	BYTE used;				//0=空闲 1=占用
	char fnm[64];			//GIF动画文件名
	CMImage dc;				//图形DC指针
}N_MGifAml;

typedef struct N_ELEGRP{	//组合图元 :内存中的存放结构
	WORD  inuse;			//使用者计数
	BYTE  type;				//类型
	char  name[15];			//名字
	BYTE  subtype;			//子类型
	BYTE  sitesum;			//端子数
	POINT pt[3];			//端子位置
	char  reserved[26];		//保留字节26
	WORD  id;				//内部ID号
	WORD  bsum1;			//图形数1
	Vpfobj *bs1;				//图形1
	CRect rt1;				//占用的矩形
	WORD  bsum2;			//图形数2
	Vpfobj *bs2;				//图形2
	CRect rt2;				//占用的矩形
}N_ELEGRP;



typedef struct  N_PHEAD{	//图标组结构,文件头,标识为图型组GGP
   DWORD flag;				//=0xf9876761
   DWORD version;			//=0x100
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
typedef N_ELEGRP N_EGRPSAVE;//组合图元存储格式
typedef struct  N_EGPHEAD{	//组合图元结构,文件头,标识为图型组ELEGRP
	DWORD flag;				//=0x20010215;
	DWORD version;			//=0x100
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

typedef struct N_VPFHEAD{	//可视化文件头
	WORD     Version;		//文件版本号=3000
	WORD     pagesum;		//页面数
	WORD	 spicsum;		//小图形对象总数
	WORD     mpicsum;		//内存图片对象总数
	WORD     egpsum;		//组合图元对象总数
	DWORD    fsize;			//文件字节数
	N_OBJSAVE  spic;		//小图
	N_OBJSAVE  mpic;		//内存图
	N_OBJSAVE  epic;		//图元
	N_OBJSAVE  page[1];		//页面偏移
}N_VPFHEAD;
//保存顺序
//0=PWFHEAD头
//1=OBJSAVE[];数量与pagesum相同
//3=spic;
//4=mpic;
//5=mpic;
//6->3+pagesum=every page



//图形文件磁盘结构
struct  N_IMGDISK{
	BYTE   index;			//索引号
	BYTE   type;			//图形类型 0=一般位图 1=动画
	BYTE   frame;			//动画的帧数
	WORD   width;			//宽度
	WORD   height;			//高度
	BYTE   bitcolor;		//颜色位数
	DWORD  size;			//图形压缩后的字节数
	char   imgdata[1];		//图形
};
//动画文件磁盘结构
struct  N_AMLDISK{
	int    x,y;				//绘图的X,Y位置
	int    w,h;				//宽高
	BYTE   disposal;		//显示模式
	BYTE   tranflag;		//透明标志
	BYTE   tranIndex;		//透明颜色
	WORD   delay;			//延迟时间
	DWORD  size;			//单幅画面压缩后的字节数
	char   imgdata[1];		//图形(<256色时包含调色板);
};


//定义页面结构
typedef struct N_PAGEPWF{   //页面结构
    N_SUBPWF head;          //每页头结构
	Vpfobj   *obj;			//对象地址指针
	WORD     objnum;		//obj的数量	
	int      zoom;		    //放缩比例为本zoom/100 max=1000  min=30;
	int      zw,zh;		    //缩放后的宽高
}N_PAGEPWF;

////////////////////////////////////////////////
////////////////////////////////////////////////
typedef struct N_BASATTR{   //对象基本属性  
	BYTE  type;				//对象类型
	BYTE  belong;			//所属端子 只有组合图元才有效
	WORD  ID;				//对象ID
	WORD  size;             //对象字节数
	short x1,y1,x2,y2;		//对象所占的矩形
}N_BASATTR;

typedef struct N_LINE{		//线   type=1
	BYTE  width;			//线宽度
	DWORD color;			//线颜色
	BYTE  flow;				//0=一般线 1=流动形线
	BYTE  shadow;			//阴影
}N_LINE;

typedef struct N_DBX{		//多边形 type=2
	BYTE  fill;			    //0=不填充  =1填充
	BYTE  fillmtd;			//填充方法0=单色 1=过渡
	BYTE  fillmode;		    //填充方式 0-7;
	BYTE  linewidth;		//线宽度
	BYTE  flow;				//0=一般线 1=流动
	BYTE  outline;			//是否画边框 0=No 1=Yes
	BYTE  shadow;			//阴影
	DWORD linecolor;		//线颜色
	DWORD bcolor1;			//填充第一颜色
	DWORD bcolor2;			//填充第二颜色
	WORD  ptsum;			//点总数
	POINT pt[1];			//后跟所有的点
}N_DBX;

typedef struct N_EGRP{		//空心园和矩形 type=3
	BYTE  type;				//类型0=园 1=矩型 2=凹矩形 3=凸矩形
	BYTE  width;			//线宽度
	DWORD color;			//线颜色
	BYTE  shadow;			//阴影
}N_EGRP;

typedef struct N_SGRP{	    //实心园和矩形 type=4
    BYTE  type;				//类型0=园 1=矩形 2=球体 3=带边矩形
	BYTE  fillmode;		    //填充方式 0-7;
	DWORD bcolor1;			//填充第一颜色
	DWORD bcolor2;			//填充第二颜色
	BYTE  shadow;			//阴影
}N_SGRP;

typedef struct N_HSIN{		//正弦半波形 type=5
    BYTE  vh;				//方向0=水平1=垂直
	BYTE  wave;				//波形0=左边或上边 1=右边或下边
	BYTE  pirodic;			//周期数
	BYTE  width;			//线宽度
	DWORD color;			//线颜色
	BYTE  shadow;			//阴影
}N_HSIN;
typedef struct N_SIN{		//正弦波形  type=6
	BYTE  vh;				//方向0=水平1=垂直
	BYTE  width;			//线宽度
	BYTE  pirodic;			//周期数
	DWORD color;			//线颜色
	BYTE  shadow;			//阴影
}N_SIN;

typedef struct N_GLASS{     //玻璃层    type=7
	BYTE  depth;			//深度
	DWORD color;			//线颜色
	BYTE  outline;			//是否画边线
	DWORD ocolor;			//边线色
}N_GLASS;

typedef struct N_ARROW{     //方向箭头  type=8
	BYTE  width;			//线宽度
	DWORD color;			//线颜色
	BYTE  shadow;			//阴影
}N_ARROW;

typedef struct N_CBAR{      //圆拄棒图  type=9
	BYTE  xy;				//XY方向0=x 1=y
	BYTE  outline;		    //外框
	DWORD color;		    //线颜色
}N_CBAR;

typedef struct N_TEXT{      //文本  type=10
	LOGFONT font;			//字体
    DWORD   color;			//颜色
    char    style;			//式样
    BYTE    shadow;			//阴影
    char    text[45];		//文本内容
}N_TEXT;

typedef struct N_IMG{		//静态图形type=11
	BYTE  shadow;			//阴影
	BYTE  depth;		    //透明度
	BYTE  zoom;				//支持缩放出0=No 1=Yes
	WORD  imgID;			//ID
}N_IMG;

typedef struct N_SPIC{	    //静态小图标type=12
	WORD  picID;			//ID
	BYTE  shadow;			//阴影
	char  reserved[10];		//备用
}N_SPIC;

typedef struct N_ESITE{		//电气端子type=13
    DWORD color;			//端子显示颜色
	BYTE  solder;			//焊接 0=焊接 1=没焊
}N_ESITE;

typedef struct N_EGPMB{		//组合图元母板 type=14
	BYTE  mode;				//0=运行时不显 1=运行时显示
	DWORD color;			//颜色
}N_EGPMB;

typedef struct N_ARC{		//园弧 type=15
	DWORD color;			//颜色
	BYTE  width;			//宽度
	WORD  start;			//开始角度
	WORD  end;				//结束角度	
	BYTE  shadow;			//阴影
}N_ARC;

typedef struct N_PATH{		//路径 type=16
	WORD  ID;				//路经ID
	double  start;			//起点坐标
	double  end;			//终点坐标
	DWORD color;			//编辑时显示颜色
	WORD  ptsum;			//点总数
	POINT pt[1];			//后跟所有的点
}N_PATH;


/////////////////////以下为动态运行对象///////////////////////////////
typedef struct R_ANL{		//模拟量实时值
	float curval;			//当前值
	unsigned char alarm:1;	//是否越限
	unsigned char enable:1;	//当前值是否有效
	unsigned char old:1;	//老数据
	unsigned char manu:1;	//手动值
	unsigned char bad:1;	//坏数据
	unsigned char ele:1;	//带电状态
	unsigned char nouse:2;	//未用
	char  reserved;			//保留
}R_ANL;

typedef struct R_RAT{		//累加量实时值
	DWORD currat;			//当前值
	unsigned char alarm:1;	//是否越限
	unsigned char enable:1;	//当前值是否有效
	unsigned char nouse:6;	//未用
}R_RAT;
typedef struct R_STA{		//状态量实时值
	unsigned char old:1;	//老数据
	unsigned char manu:1;	//手动值
	unsigned char bad:1;	//坏数据
	unsigned char reservedl:1;//保留;
	unsigned char zt:1;		//当前状态
	unsigned char alarm:1;	//是否告警
	unsigned char enable:1;	//当前值是否有效
	unsigned char ele:1;	//带电状态
	char red[4];			//保留
}R_STA,R_DEV,R_STA;

/////////////
typedef struct N_ANL{       //模拟量显示结构 type=64
	char     unit[10];		//单位字符串
	float    max;			//最大值
	float    min;			//最小值
	float    almval;		//标尺告警点
	LOGFONT  lf;		    //字体
	COLORREF acolor;	    //告警颜色
	COLORREF ncolor;	    //正常颜色
	BYTE     xs;			//小数位
	BYTE     style;		    //显示风格
	BYTE     xsmode;		//显示方式 0=数字显示 1=水平标尺显示
							//2=竖直标尺 3=饼图百分比 4=无符号数字
	BYTE     direction;		//方向
	R_ANL    rval;			//实时值
	char     ds_name[15];	//数据源名或ID
	short	 jlh;			//相关记录号
}N_ANL;

typedef struct N_RAT{       //累加显示结构type=65
	LOGFONT  lf;		    //字体
	COLORREF acolor;		//告警颜色
	COLORREF color;	        //正常颜色
	BYTE     style;		    //字体显示 0=正常 1=凹 2=凸
	BYTE     shadow;		//阴影
	R_RAT	 rval;			//实时值
	char     ds_name[15];	//数据源名或ID
	short	 jlh;			//相关记录号
}N_RAT;

typedef struct D_SITE{		//运行端子定义
	short x,y;				//本端位置	
	BYTE  vl;				//绘图时预定义的电压等级	 
	BYTE  sitn;				//连接到的端子号
	short id;				//连接设备的对象顺序记录号
}D_SITE;

typedef struct N_ELEGRPA{   //组合图元显示结构type=66
	BYTE     type;			//数据类型类型 0=状态量 1=设备 2=站 3=公司
	BYTE     subtype;		//子类型 当type=1 时为设备类型
	WORD     egrpid;		//组合图元ID号
	BYTE     showno;		//绘图时的显示号0和1
	R_STA	 rval[3];		//当前端子的状态
	byte     sitesum;		//端子数
	D_SITE   site[3];		//三个端子
	char     ds_name[15];	//数据源名
	short    jlh;			//相关记录号
	char     reserved[8];	//保留8字节
}N_ELEGRPA;

typedef struct N_CURE{		//曲线    type=68;
	WORD  curid;			 //曲线ID号
	BYTE  dot;				 //曲线点数8-96点
	BYTE  ndot[3];			 //每条线的有效点数
	BYTE  tran;				 //背景透明
	BYTE  shadow;			 //阴影
	DWORD bcolor;			 //背景色
	DWORD wcolor;			 //暗影颜色
	BYTE  border;			 //边框
	DWORD color[3];			 //三条曲线色
	float vmax;				 //最大值
	float vmin;				 //最小值
	float v1[97],v2[97],v3[97];//曲线数据;
}N_CURE;

typedef struct N_TREND{		//趋势  type=69
   int  id;					//保留ID内部用
   BYTE seg;				//时间段数
   BYTE jg;					//间隔
   float max;				//最大值
   float min;				//最小值
   DWORD lcolor;			//线颜色
   DWORD bcolor;			//背景色
   DWORD wcolor;			//水线色
   BYTE  border;			//边框
   BYTE  tran;				//背景透明
   BYTE  width;				//线宽度
   R_ANL rval;				//实时数据
   float qx[25];			//总共24点数据
   char  ds_name[15];		//模拟量名
   short jlh;				//相关记录号
}N_TREND;

typedef struct N_BAR{		//棒图 type=70
   int   xy;                //0=x方向 1=Y方向
   int   id;				//保留ID内部用
   float max;				//最大值
   float min;				//最小值
   BYTE  outline;			//外框
   BYTE  shadow;			//阴影
   BYTE  style;				//式样
   DWORD ncolor;			//正常颜色
   DWORD acolor;			//告警颜色
   float aval;				//告警值
   float val;				//初始值
   R_ANL rval;				//当前值
   char  ds_name[15];		//模拟量名
   short jlh;				//相关记录号	
}N_BAR;

typedef struct _NPIEDAT{	//饼图数据结构
	char name[12];			//数据名称
	float value;			//值
}NPIEDAT;

typedef struct N_PIE{       //饼图结构数据 type=71
	WORD   ID;				//ID号
	BYTE   style;			//0=一般 1=分离 2=立体 3=分离立体
	BYTE   outline;			//包围线 0=无 1=有
	BYTE   shad;			//过渡色 0=否 1=是
	BYTE   sum;				//饼数
	DWORD  fcolor;			//字符色
	WORD   angle;			//起始角度0-360度
	DWORD  color[8];		//8个颜色
	NPIEDAT pd[8];			//8个数据 
	char   reserved[12];	//保留字节
}N_PIEPAM;

typedef struct N_DATE{      //日期格式     type=72
	BYTE    fmt;			//日期格式 0=yyyy-mm-dd 1=mm/dd/yyyy 2=yyyy年mm月dd日
	BYTE    outline;		//边框 0=无 1=正常 1=凹 2=凸
	BYTE    tran;			//背景透明吗？0=No 1=Yes
	DWORD   outcolor;		//边线色
	DWORD   fcolor;			//字符颜色
	DWORD   bcolor;			//背景色
	LOGFONT font;			//字体
	BYTE    style;			//字体显示 0=正常 1=凹 2=凸
	BYTE    shadow;			//字体阴影显示
	CTime   tm;				//时间
}N_DATE;

typedef struct N_TIME{		//时间格式     type=73
	BYTE    fmt;			//时间格式 0=hh:mm:ss 1=hh:mm 2=hh时mm分ss秒
							//3=hh点mm分ss秒 4=mm分ss秒	
	BYTE    outline;		//边框 0=无 1=正常 1=凹 2=凸
	BYTE    tran;			//背景透明吗？0=No 1=Yes
	DWORD   outcolor;		//边线色
	DWORD   fcolor;			//字符颜色
	DWORD   bcolor;			//背景色
	LOGFONT font;			//字体
	BYTE    style;			//字体显示 0=正常 1=凹 2=凸
	BYTE    shadow;			//字体阴影显示
	CTime   tm;				//时间
}N_TIME;

typedef struct N_GIFAML{    //静态图形  type=74
	char  fname[64];		//文件名
	WORD  rec;				//GIF图形内部记录,显示用
	BYTE  type;				//关联类型：状态量,设备,站
	R_STA rval;				//当前状态
	char  ds_name[15];		//数据名
	short jlh;				//相关记录号	
}N_GIFAML;

typedef struct N_SRLTEXT{	//滚动文本  type=75
	BYTE direct;			//方向   0=静态文本 1=上下 2=左右 
							//3=下上 4=右左
	BYTE tstyle;			//文本样式 0=正常 1=凹 2=凸
	BYTE glass;				//是否用玻璃层 0=No 1=Yes
	BYTE outline;			//是否有外框
	BYTE depth;				//深度
	DWORD fcolor;			//边框
	DWORD gcolor;			//玻璃颜色
	DWORD tcolor;			//文本颜色
	LOGFONT lf;				//文字字体
	BYTE  align;		    //排列方式 0=居左 1=居中 2=居右
	BYTE  shadow;			//是否阴影
	WORD  id;				//ID号
	char text[256];			//文字串
}N_SRLTEXT;

typedef struct N_PUSH{		//按钮格式   type=76
	BYTE  style;			//按钮式样0=普通按钮 1=不可见按钮
							//2=滑过凸形按钮 3=滑过凹形按钮 
							//4=滑动变色 5=图标按钮
	char  title[32];		//按钮标题
	WORD  spicid;			//小图标ID号
	BYTE  autlin;			//位图按钮时,自动边线
	BYTE  fstyle;			//文本显示属性
	BYTE  shadow;			//阴影
	BYTE  cmdtype;			//命令类型
	WORD  cmdnum;		    //自定义时的WM_COMMAND消息wParam
	char  command[45];		//命令字符串
	DWORD color1;			//颜色1
	DWORD color2;			//颜色2
	int   selfid;			//要控制的自助控件的ID
	LOGFONT lf;				//字体
	WORD  id;				//自身ID
	BYTE  down;				//压下状态
	BYTE  enable;			//是否有效
	char reserved[8];		//保留字节
}N_PUSH;

typedef struct N_COMCTL{	//公共控制  type=77
	BYTE  type;				//0=编辑 1=列表框 2=组合框 3=TREE 
    WORD  eid;				//编辑框ID值
    BYTE  outline;			//外框风格
    DWORD wstyle;           //风格
    BYTE  left;				//左对齐
    BYTE  right;			//右对齐
    BYTE  top;				//上对齐
    BYTE  bottom;			//下对齐
    short width;			//保留宽度
    short height;			//保留高度
    char  str[320];			//保存其他与此相关的信息(如列表信息等)
}N_COMCTL;

typedef struct N_SELFCTL{   //自助控件  type=78
    char  dllname[64];		//动态连接库名
    DWORD style;			//属性,由控件设置
    int   id;				//ID号,以便相互控制
    char  lkbuf[255];		//启动时的连接缓冲区
    BYTE  aleft;			//左对齐
    BYTE  aright;			//右对齐
    BYTE  atop;				//上对齐
    BYTE  abottom;			//下对齐
    short awdth;			//保留宽度
    short ahght;			//保留高度
    HINSTANCE hinst;        //DLL的事例
    HWND  hwnd;				//窗口句柄
    void  *rc;				//初始化产生的资源(如果有)
    int  (WINAPI*DfGetVer)();//返回版本号
    void (WINAPI*DfDrawDemo)(HDC,RECT,DWORD,char *);    //演示绘图
    void*(WINAPI*DfInit)(HWND,HWND&,RECT,int,DWORD,char*);//初始化
    void (WINAPI*DfClose)(void *rc);		  //关闭
    void (WINAPI*DfAbout)();				  //关于该控件
    void (WINAPI*DfSetParam)(DWORD&,char*);//配置参数
    char reserved[120];		              //保留字节,留着发展
}N_SELFCTL;

typedef struct R_FLOW{      //潮流运行参数
	char     js;		    //起点计数
	unsigned char  f:1;     //显示起点标志
	unsigned char direct:2; //方向
	unsigned char rev:5;
}R_FLOW;

typedef struct N_FLOW{		//潮流线    type=79
	R_FLOW  rf;				//运行参数
	char  rev[2];			//(暂不用）
	BYTE  width;			//线宽度
	BYTE  shadow;			//阴影
	DWORD acolor;			//告警颜色
	DWORD color1;			//正常线颜色
	DWORD color2;			//正常间颜色
	BYTE  style;			//式样 0=线1=箭头 2=园 3=矩形
	R_ANL rval;				//当前值
	D_SITE site[2];			//连接=0时无连接
	char  ds_name[15];		//模拟量名
	short jlh;				//相关记录号	
	WORD  ptsum;			//点总数
	POINT pt[1];			//后跟所有的点
}N_FLOW;


typedef struct N_CONLINE{	//连接线  type=80
	BYTE  width;			//线宽度
	BYTE  shadow;			//阴影
	BYTE  solder1;			//焊接点1显示0=不显示 1=显示
	BYTE  solder2;			//焊接点2显示0=不显示 1=显示
	BYTE  vl;				//电压等级
	D_SITE site[2];			//连接=0时无连接
	char  rev[10];			//保留
	WORD  ptsum;			//点总数
	POINT pt[1];			//后跟所有的点
}N_CONLINE;

typedef struct N_BUS{		//母线  type=81
	BYTE  type;				//类型
	BYTE  shadow;			//阴影
	BYTE  vl;				//电压等级
	R_STA rval;				//实时值
	char  rev[6];			//保留
	char  ds_name[15];		//数据源名
	short jlh;				//相关记录号	
}N_BUS;

typedef struct N_ACTOBJ{	//小型活动对象  type=82
	short gid;				//图形ID
	WORD  pathid;			//所属path ID
	BYTE  runmode;			//运行模式 0=自动 1=同步
	BYTE  speed;			//自动运行速率 0,1,2,3
	float skip;				//自动步长
	char  ds_name[15];		//数据源名
	short jlh;				//相关记录号
	char  rev[64];			//保留
}N_ACTOBJ;


typedef struct N_SPLITASS{  //分割部件 type=83
    BYTE  type;				//0=X方向 1=Y方向
    BYTE  outline;			//外框风格
    BYTE  left;				//左对齐
    BYTE  right;			//右对齐
    BYTE  top;				//上对齐
    BYTE  bottom;			//下对齐
    BYTE  pos;				//初始位置 0=自然位置 1=1/2处 2=1/3处 
	BYTE  reserved;			//保留
    short height;			//保留高度
}N_SPLITASS;
///////////////////////////////////////////////////////////////////////
//以下结构运行时用
typedef struct _SPLSUBWIN{  //分割器控制的子窗口参数
  CRect ort;				//原始位置
  BYTE  outline;			//外框风格
  DWORD wstyle;				//风格
  BYTE  left;				//左对齐
  BYTE  right;				//右对齐
  BYTE  top;				//上对齐
  BYTE  bottom;				//下对齐
  short width;				//保留宽度
  short height;				//保留高度 
  HWND  hwnd;				//窗口
}SPLSUBWIN;

typedef struct SUBW_PARAM{	//运行子窗口属性定义
	HWND  hwnd;				//窗口
	CRect rts;				//窗口原始大小
	CRect rt;				//占用的矩形
	CRect rtw;				//窗口矩形
	BYTE  outline;			//外框风格
    BYTE  left;				//左对齐
    BYTE  right;			//右对齐
    BYTE  top;				//上对齐
    BYTE  bottom;			//下对齐
	short width;			//保留宽度
	short height;			//保留高度
}SUBW_PARAM;


typedef struct ROBJ{		//运行对象
	Vpfobj *bs;		  		//对象地址
}ROBJ;

typedef struct RANL{		//模拟量对象
	Vpfobj *bs;				//对象地址
	CRect rt;				//对象占用的矩形
	N_ANL *anl;				//对象属性地址
}RANL;
typedef struct RRAT{		//累加量对象
	Vpfobj *bs;				//对象地址
	CRect rt;				//占用的矩形区
	N_RAT *rat;				//对象地址
}RAT;
typedef struct RSTA{		//状态量对象
	Vpfobj *bs;				//对象地址
	CRect rt;				//占用的矩形区
	N_ELEGRPA *elg;			//对象地址
}RSTA;


typedef struct RAML{		//动画对象
	Vpfobj  *bs;			//对象地址
	CRect   rt;				//占用的矩形区
	N_GIFAML *gif;			//属性地址
	CGIFAnm gfaml;			//动画实例
}RAML;

typedef struct RSCRTXT{		//动画对象
	Vpfobj *bs;				//对象地址
	N_SRLTEXT *stx;			//属性地址
	CRect rt;				//占用的矩形区
	int xl,yl;				//当前位置
	int w,h;				//宽、高
}RSCRTXT;

typedef struct RSELFCTL{
	CRect rt;				//占用的矩形区
	int   sid;				//对象自生ID
	BYTE  cansize;			//能否改变大小
	SUBW_PARAM swp;			//窗口相关参数  
	N_SELFCTL *stl;			//属性地址
}RSELFCTL;

typedef struct RFLOW{		//潮流线对象
	Vpfobj  *bs;			//对象地址
	N_FLOW *flw;			//属性地址
	HRGN  hrgn;				//区域
	int   ptsum;			//点数
	POINT pt[20];			//点
	CRect rt;				//占用的矩形区
}RFLOW;

typedef struct RCURE{		//曲线对象 68
	Vpfobj  *bs;			//对象地址
	N_CURE  *cure;			//曲线对象
	CRect rt;				//占用的矩形区
}RCURE;

typedef struct RTREND{		//潮流线对象
	Vpfobj  *bs;			//对象地址
	N_TREND *td;			//属性地址
	BYTE jg;				//间隔
	BYTE seg;				//段数
	BYTE js;				//当前计数
	CRect rt;				//占用的矩形区
}RTREND;


//按钮控制运行参数格式
typedef struct RPUSH{		//76
	Vpfobj  *bs;			//对象地址
	CRect   rt;				//占用的矩形区
	N_PUSH *psh;			//属性地址
}RPUSH;

//公共控制运行参数格式
typedef struct RCOMCTL{		//77
	CRect  rt;				//占用的矩形区
	int    sid;				//对象自生ID
	BYTE   cansize;			//能否改变大小
	SUBW_PARAM swp;			//窗口相关参数  
	N_COMCTL *com;			//属性地址
	CWnd     *cwin;			//对象窗口地址
}RCOMCTL;

//分割器运行参数格式
typedef struct RSPL{		//80
	CRect rt;				//占用的矩形区
	int   sid;				//对象自生ID
	CRect rt1;				//第一矩形
	CRect rt2;				//第二矩形
	CRect rts1;				//原旧窗口1大小
	CRect rts2;				//原旧窗口2大小
	SUBW_PARAM swp;			//本对象参数
	int   Init;				//是否已被初始化
	int   pos;				//当前位置
	SUBW_PARAM swp1[8];		//第一部分窗口
	SUBW_PARAM swp2[8];		//第二部分窗口
	int  sum1;				//第一部分窗口数 最大8个
	int  sum2;				//第二部分窗口数 最大8个
	N_SPLITASS  *spl;		//属性地址
}RSPL;


typedef struct RACTOBJ{		//活动对象
	Vpfobj    *bs;			//对象地址
	N_ACTOBJ *act;			//属性地址
	CRect  rt;				//占用的矩形区
	double curval;			//实时值
	double maxv;			//最大值
	double minv;			//最小值
	CRect  oldrt;			//原来的位置
	CRect  currt;			//当前位置
	WORD   picw,pich;		//显示图片的宽高
	short  picj;			//图片的记录号
	BYTE   js;				//当前计数
	POINT  *pt;				//路经
	int    ptsum;			//点数
}RACTOBJ;

typedef struct RUNPATH{		//运行路径
  char path[256];
}RUNPATH;

#endif