#if !defined(AFX_DEFV30_H__INCLUDED_)
#define AFX_DEFV30_H__INCLUDED_
#include "jhsyslibl.h"
#include "pwptdef.h"


//保存格式V5.0版
////////////////////////////////////////////////
typedef struct N5_BASATTR{   //对象基本属性  
	WORD  type;				 //对象类型
	BYTE  belong:3;			 //所属端子 只有组合图元才有效
	BYTE  reserved:5;		 //保留
	WORD  ID;				 //对象ID
	WORD  size;              //对象字节数
	char  nouse[16];		 //保留未用
}N5_BASATTR;

typedef struct N5_DBX{		 //多边形 type=1  r1
	BYTE  fill:1;		     //0=不填充 1=填充
	BYTE  close:1;			 //封闭
	BYTE  fillmode:2;		 //填充模式
	BYTE  ltype:3;			 //线类型
	BYTE  bgmode:1;			 //背景模式 0=前景 1=北京
	DWORD lcolor;			 //线颜色
	DWORD bcolor1;			 //填充颜色1
	char  nouse[16];		 //保留未用
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N5_DBX;


typedef  struct N5_RECT{	 //矩形 type=2 r2
	DRECT  rt;				 //矩形
	BYTE   fill:1;			 //0=不填充 1=填充 
	BYTE   fillmode:3;		 //填充方式 
	BYTE   type:2;			 //0=一般矩形  1=凹 2=凸 
	BYTE   reserved:2;		 //保留
	DWORD  lcolor;			 //线颜色
	DWORD  bcolor1;			 //填充颜色1
	char   nouse[16];		 //保留未用
}N5_RECT;

typedef N5_RECT N5_CIRCLE;	 //园 type=3  r3


typedef struct N5_HSIN{		 //正弦半波形 type=4  r4
	DRECT  rt;				 //矩形
	BYTE   hv:1;			 //水平或垂直 0=水平 1=垂直
	BYTE   pirodic:7;		 //周期数
	DWORD  color;			 //线颜色
	char   nouse[16];		 //保留未用
}N5_HSIN;

typedef struct N5_SIN{		 //正弦波形  type=5 r5
	DRECT rt;				 //矩形
	BYTE  hv:1;			     //线类型 0=水平 1=垂直
	BYTE  pirodic:7;		 //周期数
	WORD  startdeg;			 //开始角度0-359
	DWORD color;			 //线颜色
	char  nouse[16];		 //保留未用
}N5_SIN;

typedef struct N5_ARC{		 //园弧 type=6  r6
	DRECT  rt;				 //矩形
	DWORD  color;			 //颜色
	WORD   start;			 //开始角度
	WORD   end;				 //结束角度	
	char   nouse[16];		 //保留未用
}N5_ARC;

typedef struct N5_ARROW{     //方向箭头  type=7  r7
	DPOINT  pt[2];			 //两点坐标
	DWORD   color;			 //线颜色
	char    nouse[16];		 //保留未用
}N5_ARROW;

typedef struct N5_GLASS{     //玻璃层    type=8
	DRECT  rt;				 //矩形
	BYTE   depth;			 //深度
	BYTE   outline:1;		 //是否画边线
	BYTE   reserved:7;		 //保留
	DWORD  color;			 //颜色
	DWORD  lcolor;			 //边线色
	char   nouse[16];		 //保留未用
}N5_GLASS;

typedef struct N5_TEXT{      //文本  type=10    r9
	DRECT   rt;				 //矩形
	double  zm;				 //绘图时的倍率
	LOGFONT font;			 //字体
    DWORD   color;			 //颜色
	BYTE    autofit:1;		 //自适应
    BYTE    style:2;		 //式样
	BYTE    reserved:5;
	WORD    angle;			 //角度
	char    nouse[16];		 //保留未用
    char    text[1];		 //文本内容,后跟所有的字符
}N5_TEXT;

typedef struct N5_ESITE{	 //电气端子type=11
	DRECT  rt;				 //矩形
	DWORD  color;			 //端子显示颜色
	BYTE   solder:1;		 //焊接 0=焊接 1=没焊
	BYTE   reserved:7;		 //保留
	char   nouse[16];		 //保留未用
}N5_ESITE;

typedef struct N5_EGPMB{	 //组合图元母板 type=12 
	DRECT  rt;				 //矩形
	DWORD  color;			 //颜色
	BYTE   mode:1;			 //0=不显 1=显示
	BYTE   reserved:7;		 //保留
	char   nouse[16];		 //保留未用
}N5_EGPMB;

typedef struct N5_COORDINATE{ //坐标 type=13
	DRECT  rt;				 //矩形
	long   xmin;			 //X方向最小值
	long   xmax;			 //X方向最大值
	long   ymin;			 //Y方向最小值
	long   ymax;			 //Y方向最大值
	DWORD  colorc;			 //坐标线颜色
	DWORD  colorw;			 //水线颜色
	DWORD  colort;			 //文本颜色
	BYTE   xdot;			 //X坐标点数
	BYTE   ydot;			 //Y坐标点数
	BYTE   wxdraw:1;		 //X方向水线是否画
	BYTE   wydraw:1;		 //y方向水线是否画
	BYTE   xvshow:1;		 //x坐标值显示
	BYTE   yvshow:1;		 //y坐标值显示
	BYTE   reserved:4;		 //保留未用
	LOGFONT fontx;			 //X字符显示字体
	LOGFONT fonty;			 //Y字符显示字体
	char    nouse[64];		 //保留未用
}N5_COORDINATE;

typedef struct N5_TABLE{	 //表格线 type=14
	DRECT  rt;				 //矩形
	DWORD  color;			 //线颜色
	double width;			 //线宽度
	BYTE   dbline;			 //边线加粗
	WORD   line;			 //行数
	char   nouse[64];		 //保留未用
}N5_TABLE;


typedef struct N5_IMG{		 //静态图形type=15
	DRECT rt;				 //矩形
	BYTE  shadow:1;			 //阴影
	BYTE  zoom:1;			 //支持缩放出0=No 1=Yes
	BYTE  reserved:6;		 //保留
	BYTE  depth;		     //透明度
	WORD  imgID;			 //ID
	char  nouse[16];		 //保留未用
}N5_IMG;

typedef struct N5_PATH{		 //路径 type=16  r10
	WORD  ID;				 //路经ID
	char  nouse[32];		 //保留未用
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N5_PATH;


typedef struct N5_SPIC{	     //静态小图标type=17
	DRECT rt;				 //矩形
	WORD  picID;			 //ID
	BYTE  zoom:1;			 //支持放缩 0=no 1=yes
	BYTE  reserved:7;		 //保留
	char  nouse[16];		 //保留未用
}N5_SPIC;


///////////////////特殊动态类//////////////////////////////////////////////

//动态仪表1
typedef struct N5_METER1     //仪表参数   type=32
{
	DPOINT  pt[2];			//2个点坐标 第1点是指针顶部 第二点是园心
	LOGFONT font;			//数字字体
	float   Vmin;			//最小值
	float	Vmax;			//最大值
	BYTE    showarc;		//是否显示弧线
	BYTE    shownum;		//是否显示数字
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
	BYTE    stype;			//刻度类型
	BYTE    lstype;			//小刻度类型
	char    reserved[32];	//保留32字节
}N5_METER1;
//动态仪表2
typedef struct N5_METER2     //水平刻度 type=33
{
	DRECT	rt;
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
	char    reserved[32];	//保留32字节
}N5_METER2;

//动态仪表3
typedef struct N5_METER3     //垂直刻度 type=34
{
	DRECT	rt;
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
	char    reserved[32];	//保留32字节
}N5_METER3;

//动态仪表4
typedef struct N5_METER4       //基本仪表参数(数码) type=35
{
	DRECT	rt;
	BYTE    num;			 //总位数
	BYTE    numdot;			 //小数位数
	DWORD   bcr;			 //边框颜色
	DWORD   ncr[2];			 //整数和小数部分的颜色
	char    reserved[32];	//保留32字节
}N5_METER4;

typedef struct N5_ANL{       //模拟量显示结构 type=64 r11
	DRECT    rt;			 //矩形
	LOGFONT  lf;		     //字体
	COLORREF acolor;	     //告警颜色
	COLORREF ncolor;	     //正常颜色
	BYTE     xs:4;			 //小数位
	BYTE     style:4;		 //显示风格
	WORD     angle;			 //显示角度=度*10
	char     dev_name[64];	 //设备名
	char     tablename[24];	 //内存库中的表明
	char     fieldname[24];	 //表中的域名
	long	 did;			 //设备ID
	BYTE     dbmode;		 //数据模式0=旧模式 1=新模式
	BYTE     dtype:4;		 //设备类型 0=发电机 1=交流线路 2=直流线路 3=母线 4=负荷  5=2绕组变压器 
							 //	6=3绕组变压器 7=电容器 8=电抗器 9=SVC
	BYTE     xsmode:4;		 //见下面,不同对象有不同的含义
	char     nouse[16];		 //保留未用
}N5_ANL;


/*
	xsmode定义：
	节点：  0=按电压等级和标幺值显示 1=显示电压绝对值和相角
	线路：  0=始端   1=末端
	变压器：0=三绕组 1=二绕组
 */
typedef struct N5_RESERVOIR{ //水库对象   type=65
	DWORD color;			 //线颜色
	DWORD ncolor;			 //正常时颜色
	DWORD hcolor;			 //高水位颜色
	DWORD lcolor;			 //低水位颜色
	char  dev_name[64];		 //水库名
	char  rev[32];			 //保留32字节
	long  did;				 //水库ID
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N5_RESERVOIR;

typedef struct N5_ELEGRPA{   //组合图元显示结构type=66  r13
	DRECT    rt;			 //矩形
	BYTE     type:2;		 //数据类型类型 0=状态量 1=设备 2=站 3=公司
	BYTE     subtype:6;		 //子类型 当type=1 时为设备类型
	WORD     egrpid;		 //组合图元ID号
	BYTE     showno:1;		 //绘图时的显示号0和1
	byte     sitesum:2;		 //端子数
	BYTE     genrev:1;		 //是否显示发电机备份(发电机时有效)
	BYTE     runshow:1;		 //运行时是否显示
	BYTE     reserved:3;	 //保留
	D_SITE   site[3];		 //三个端子
	char     dev_name[64];	 //设备名
	char     cimname[64];	 //CIM的名字
	char     cimid[64];		 //CIM中的ID
	long     did;			 //设备记录号
	char     nouse[32];		 //保留未用
}N5_ELEGRPA;


//定义单点数据源（只能选择其中一点数据)
typedef struct _SINGLEDBS5{  //单点数据源
	char  name[64];			 //设备名字
	int   did;				 //设备ID
	BYTE  dtype;			 //设备类型
	BYTE  xsmode;			 //值索引
	char  nouse[32];		 //未用
}SINGLEDBS5,DBSRC5;

typedef struct MTRRANGE5{	 //仪表运行参数及限值
	BYTE     ptype;			 //参数类型 0=使用自定义 1=使用数据库
	float    vmin;			 //最小值
	float    vmax;			 //最大值
	BYTE	 alarm;			 //是否支持告警刻度 0=没有 1,2=有
	float	 val[4];		 //2段值(起点终点)
	DWORD    color[2];		 //2段颜色
}MTRRANGE5;

typedef struct N5_ELEGRPYB{  //组合图元仪表结构 type=67 
	DRECT	 rt;			 //矩形
	WORD     egrpid;		 //组合图元ID号
	BYTE     dbsum;			 //数据源个数
	DBSRC5   dbs[8];		 //16个数据源，对应16个顺序仪表和数据
	MTRRANGE5 pam[8];		 //用户自定义量程
}N5_ELEGRPYB;


typedef struct N5_SYSPIE{     //饼图结构数据 type=68
	DRECT   rt;				 //矩形
	WORD    ID;				 //ID号
	DWORD   fcolor;			 //字符色
	LOGFONT lf;				 //字体
	BYTE    type;			 //类型
	DWORD   color[6];		 //6个颜色 最大6个部分
	char    rev[64];		 //保留
}N5_SYSPIE;


typedef struct N5_BAR{		 //棒图 type=69
	DRECT rt;				 //矩形
	float max;				 //最大值
	float min;				 //最小值
	BYTE  xy:1;              //0=x方向 1=Y方向
    BYTE  outline:1;		 //外框
    BYTE  style:3;			 //式样
	BYTE  reserved:4;		 //保留
    DWORD ncolor;			 //正常颜色
    DWORD acolor;			 //告警颜色
    float aval;				 //告警值
    SINGLEDBS5 dsrc;		 //数据源
	char  nouse[32];		 //保留未用
}N5_BAR;


typedef struct N5_PIE{        //饼图结构数据 type=70
	DRECT   rt;				 //矩形
	DWORD   fcolor;			 //字符色
	DWORD   color[3];		 //3个颜色
	LOGFONT lf;				 //字体
	char    name[32];		 //区域名称
	int     did;			 //区域ID
	BYTE    type;			 //类型
	char    nouse[32];		 //保留未用
}N5_PIEPAM;

typedef struct N5_DATE{       //日期格式     type=71 r14
	DRECT   rt;				 //矩形
	double  zm;
	BYTE    fmt:4;			 //日期格式 0=yyyy-mm-dd 1=mm/dd/yyyy 2=yyyy年mm月dd日
	BYTE    outline:2;		 //边框 0=无 1=凹 2=凸
	BYTE    tran:1;			 //背景透明吗？0=No 1=Yes
	BYTE    shadow:1;		 //字体阴影显示
	DWORD   outcolor;		 //边线色
	DWORD   fcolor;			 //字符颜色
	DWORD   bcolor;			 //背景色
	LOGFONT font;			 //字体
}N5_DATE;

typedef N5_DATE N5_TIME;     //时间格式     type=72 r15



typedef struct N5_GIFAML{    //动画图形  type=73
	DRECT rt;				 //矩形
	char  fname[256];		 //文件名
	WORD  rec;				 //GIF图形内部记录,显示用
	//BYTE  type;				 //关联类型：状态量,设备,站
	SINGLEDBS5 dsrc;		 //数据源
	char  nouse[32];		 //保留未用
}N54_GIFAML;

typedef struct N5_SRLTEXT{	 //滚动文本  type=74
	DRECT   rt;				 //矩形
	double  zm;				 
	BYTE direct:3;			 //方向   0=静态文本 1=上下 2=左右 
							 //3=下上 4=右左
	BYTE glass:1;			 //是否用玻璃层 0=No 1=Yes
	BYTE outline:1;			 //是否有外框
	BYTE align:2;		     //排列方式 0=居左 1=居中 2=居右
	BYTE reserved:1;
	BYTE depth;				 //深度
	DWORD fcolor;			 //边框
	DWORD gcolor;			 //玻璃颜色
	DWORD tcolor;			 //文本颜色
	LOGFONT lf;				 //文字字体
	char text[1];			 //文字串
}N5_SRLTEXT;

typedef struct N5_PUSH{		 //按钮格式   type=75
	DRECT   rt;				 //矩形
	double  zm;
	BYTE   style:4;			 //按钮式样0=普通按钮 1=不可见按钮
							 //2=滑过凸形按钮 3=滑过凹形按钮 
							 //4=滑动变色 5=图标按钮
	BYTE  cmdtype:4;		 //命令类型
	char  title[64];		 //按钮标题
	WORD  spicid;			 //小图标ID号
	WORD  cmdnum;		     //自定义时的WM_COMMAND消息wParam
	char  command[64];		 //命令字符串
	DWORD color1;			 //颜色1
	DWORD color2;			 //颜色2
	int   selfid;			 //要控制的自助控件的ID
	LOGFONT lf;				 //字体
	BYTE  tosta;			 //目标状态,打开画面时用
	BYTE  autlin:1;			 //位图按钮时,自动边线
	BYTE  shadow:1;			 //阴影
	BYTE  reserved:6;		 //保留
	char  nouse[64];		    //保留未用
}N5_PUSH;

typedef struct N5_SELFCTL{  //自助控件  type=76
	DRECT rt;			    //矩形
	char  dllname[256];		//动态连接库名
    DWORD style;			//属性,由控件设置
    int	  id;				//ID号,以便相互控制
    char  lkbuf[255];		//启动时的连接缓冲区
    BYTE  aleft:1;			//左对齐
    BYTE  aright:1;			//右对齐
    BYTE  atop:1;			//上对齐
    BYTE  abottom:1;		//下对齐
	BYTE  mode:1;			//类型:0=编辑位置 1=其他暂未用
	BYTE  reserved:3;		//保留
	char  nouse[32];		 //保留未用
}N5_SELFCTL;


typedef struct N5_FLOW{		//潮流线    type=77 r16
	BYTE  style:3;			//式样 0=一般线条 1=只显有功 2=只显无功 3=同时显示
	BYTE  direct:1;			//方向0=潮流方向与画线方向一致 1=与画线方向相反
	BYTE  type:2;			//类型 0=交流 1=直流
	BYTE  reserved:2;		//保留
	BYTE  vl;				//电压等级	 
	D_SITEB site[2];		//端子
	DWORD color1;			//有功颜色
	DWORD color2;			//无功颜色
	char  dev_name[64];		//设备名
	char  cimname[64];		//CIM的名字
	char  cimid[64];		//CIM中的ID
	long  did;				//设备记录号(ID)
	BYTE  linewidth;		//线宽
	char  nouse[32];		//保留未用
	WORD  ptsum;			//点总数
	DPOINT pt[1];			//后跟所有的点
}N5_FLOW;



typedef struct N5_CONLINE{	//连接线  type=78 r17
	BYTE	solder1:1;		//焊接点1显示0=不显示 1=显示
	BYTE	solder2:1;		//焊接点2显示0=不显示 1=显示
	BYTE    conobj:1;		//连接到设备标志 =0 未连接 =1 已连接
	BYTE    reserved:5;		//保留
	BYTE	vl;				//电压等级
	LOGOBJ  lobj[2];		//两个端子连接的对象
	WORD	ptsum;			//点总数
	DPOINT	pt[1];			//后跟所有的点
}N5_CONLINE;

typedef struct N5_BUS{		//母线  type=79 r18
	DRECT   rt;				 //矩形
	BYTE    type:2;			//类型
	BYTE    valarm:2;		//电压告警状态 0=正常 1=越下限 2=越上限
	BYTE    reserved:4;		//保留
	BYTE	vl;				//电压等级
	WORD    eid;			//组合图元ID
	char    dev_name[64];	//设备名
	char    cimname[64];	//CIM的名字
	char    cimid[64];		//CIM中的ID
	long    did;			//设备ID号
	char    nouse[32];		//保留未用
}N5_BUS;

typedef struct N5_ACTOBJ{	//小型活动对象  type=80
	DRECT   rt;				 //矩形
	short   gid;			//图形ID
	WORD	pathid;			//所属path ID
	BYTE	runmode:1;		//运行模式 0=自动 1=同步
	BYTE	speed:3;		//自动运行速率 0,1,2,3
	BYTE    reserved:4;		//保留
	float	skip;			//自动步长
	SINGLEDBS5 dsrc;		//数据源
	char     nouse[32];		//保留未用
}N5_ACTOBJ;

typedef struct N5_FLASH{	//FLASH对象  type=81
	DRECT rt;				 //矩形
	char  fname[256];		//swf文件名
	BYTE  playmode:1;		//播放模式0=一次 1=循环
	BYTE  align_left:1;		//左对齐
	BYTE  align_top:1;		//上对齐
	BYTE  align_right:1;	//右对齐
	BYTE  align_buttom:1;	//下对齐
	BYTE  reserved:4;		//保留
	char  nouse[32];		//保留未用
}N5_FLASH;


typedef struct N5_PCTPIE{	//百分比饼图 type=82
	DRECT   rt;				//矩形
	double  zm;
	char    dev_name[64];   //设备名
	int     did;			//设备ID
	BYTE    type;			//数据类型 0=传输线 1=发电机
	DWORD   color1,color2;  //两个颜色
	DWORD   fcolor;			//字体颜色
	LOGFONT lf;				//数字字体
	float   maxv;			//最大值
	char    nouse[32];		 //保留未用
}N5_PCTPIE;


//虚拟仪表相关结构
typedef struct N5_ISTMT{	//仪表结构 type=83
	DRECT   rt;				//占用的矩形
	char    type;			//表类型
	char    dev_name[64];   //设备名
	int     did;			//设备ID
	char    nouse[64];		//未用
}N5_ISTMT;

//区域
typedef struct N5_ZONE{		//区域    type=83
	DWORD lcolor;			//边线颜色
	char  zone_name[64];	//区域名
	long  did;				//区域(ID)
	LOGFONT lf;				//字体
	DWORD fcolor;			//字体颜色
	char  nouse[32];		//未用
	WORD  ptsum;			//点总数
	DPOINT pt[1];			//后跟所有的点
}N5_ZONE;


typedef struct N5_MTTEXT{	//区域    type=84
	DRECT rt;				//占用的矩形
	DWORD fcolor;			//颜色
	char  name[64];			//名字
	int   did;				//(ID)
	BYTE  type;				//类型
	LOGFONT lf;				//字体
	char  text[256];		//文本缓冲
	char  rev[64];
}N5_MTTEXT;




///////////////////////////////////////////////////////////////////////////////////////////
//保存格式V4.0
////////////////////////////////////////////////
typedef struct N4_BASATTR{    //对象基本属性  
	BYTE  type;				 //对象类型
	BYTE  belong:3;			 //所属端子 只有组合图元才有效
	BYTE  reserved:5;		 //保留
	WORD  ID;				 //对象ID
	WORD  size;              //对象字节数
	char  nouse[16];		 //保留未用
}N4_BASATTR;


//动态仪表1
typedef struct N4_METER1     //仪表参数   type=32
{
	DPOINT  pt[2];			//2个点坐标 第1点是指针顶部 第二点是园心
	LOGFONT font;			//数字字体
	float   Vmin;			//最小值
	float	Vmax;			//最大值
	BYTE    showarc;		//是否显示弧线
	BYTE    shownum;		//是否显示数字
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
	char    reserved[32];	//保留32字节
}N4_METER1;
//动态仪表2
typedef struct N4_METER2     //水平刻度 type=33
{
	DRECT	rt;
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
	char    reserved[32];	//保留32字节
}N4_METER2;

//动态仪表3
typedef struct N4_METER3     //垂直刻度 type=34
{
	DRECT	rt;
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
	char    reserved[32];	//保留32字节
}N4_METER3;

//动态仪表4
typedef struct N4_METER4       //基本仪表参数(数码) type=35
{
	DRECT	rt;
	BYTE    num;			 //总位数
	BYTE    numdot;			 //小数位数
	DWORD   bcr;			 //边框颜色
	DWORD   ncr[2];			 //整数和小数部分的颜色
	char    reserved[32];	//保留32字节
}N4_METER4;

typedef struct N4_DATE{       //日期格式     type=71 r14
	DRECT   rt;				 //矩形
	double  zm;
	BYTE    fmt:4;			 //日期格式 0=yyyy-mm-dd 1=mm/dd/yyyy 2=yyyy年mm月dd日
	BYTE    outline:2;		 //边框 0=无 1=凹 2=凸
	BYTE    tran:1;			 //背景透明吗？0=No 1=Yes
	BYTE    shadow:1;		 //字体阴影显示
	DWORD   outcolor;		 //边线色
	DWORD   fcolor;			 //字符颜色
	DWORD   bcolor;			 //背景色
	LOGFONT font;			 //字体
	char    nouse[16];		 //保留未用
}N4_DATE;

typedef N4_DATE N4_TIME;     //时间格式     type=72 r15

typedef struct N4_SRLTEXT{	 //滚动文本  type=74
	DRECT   rt;				 //矩形
	double  zm;				 
	BYTE direct:3;			 //方向   0=静态文本 1=上下 2=左右 
							 //3=下上 4=右左
	BYTE glass:1;			 //是否用玻璃层 0=No 1=Yes
	BYTE outline:1;			 //是否有外框
	BYTE align:2;		     //排列方式 0=居左 1=居中 2=居右
	BYTE reserved:1;
	BYTE depth;				 //深度
	DWORD fcolor;			 //边框
	DWORD gcolor;			 //玻璃颜色
	DWORD tcolor;			 //文本颜色
	char    nouse[16];		 //保留未用
	LOGFONT lf;				 //文字字体
	char text[1];			 //文字串
}N4_SRLTEXT;

typedef struct N4_SELFCTL{   //自助控件  type=76
	DRECT rt;				 //矩形
	char  dllname[64];		//动态连接库名
    DWORD style;			//属性,由控件设置
    int	  id;				//ID号,以便相互控制
    char  lkbuf[255];		//启动时的连接缓冲区
    BYTE  aleft:1;			//左对齐
    BYTE  aright:1;			//右对齐
    BYTE  atop:1;			//上对齐
    BYTE  abottom:1;		//下对齐
	BYTE  mode:1;			//类型:0=编辑位置 1=其他暂未用
	BYTE  reserved:3;		//保留
	char     nouse[64];		//保留未用
}N4_SELFCTL;

typedef struct N4_CONLINE{	//连接线  type=78 r17
	BYTE	solder1:1;		//焊接点1显示0=不显示 1=显示
	BYTE	solder2:1;		//焊接点2显示0=不显示 1=显示
	BYTE    conobj:1;		//连接到设备标志 =0 未连接 =1 已连接
	BYTE    reserved:5;		//保留
	char    nouse[16];		//保留未用
	BYTE	vl;				//电压等级
	LOGOBJ  lobj[2];		//两个端子连接的对象
	WORD	ptsum;			//点总数
	DPOINT	pt[1];			//后跟所有的点
}N4_CONLINE;

typedef struct N4_FLASH{	//FLASH对象  type=81
	DRECT rt;				 //矩形
	char  fname[128];		//swf文件名
	BYTE  playmode:1;		//播放模式0=一次 1=循环
	BYTE  align_left:1;		//左对齐
	BYTE  align_top:1;		//上对齐
	BYTE  align_right:1;	//右对齐
	BYTE  align_buttom:1;	//下对齐
	BYTE  reserved:4;		//保留
	char    nouse[16];		 //保留未用
}N4_FLASH;


typedef struct N4_DBX{		 //多边形 type=1  r1
	BYTE  fill:1;		     //0=不填充 1=填充
	BYTE  fillmode:3;		 //填充模式
	BYTE  ltype:3;			 //线类型
	BYTE  bgmode:1;			 //背景模式 0=前景 1=北京
	char  nouse[16];		 //保留未用
	DWORD lcolor;			 //线颜色
	DWORD bcolor1;			 //填充颜色1
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N4_DBX;

typedef  struct N4_RECT{	 //矩形 type=2 r2
	DRECT  rt;				 //矩形
	BYTE   fill:1;			 //0=不填充 1=填充 
	BYTE   fillmode:3;		 //填充方式 
	BYTE   type:2;			 //0=一般矩形  1=凹 2=凸 
	BYTE   reserved:2;		 //保留
	char    nouse[16];		 //保留未用
	DWORD  lcolor;			 //线颜色
	DWORD  bcolor1;			 //填充颜色1
}N4_RECT;

typedef N4_RECT N4_CIRCLE;	 //园 type=3  r3
    

typedef struct N4_HSIN{		 //正弦半波形 type=4  r4
	DRECT  rt;				 //矩形
	BYTE   hv:1;			 //水平或垂直 0=水平 1=垂直
	BYTE   pirodic:7;		 //周期数
	DWORD  color;			 //线颜色
	char    nouse[16];		 //保留未用
}N4_HSIN;



typedef struct N4_SIN{		 //正弦波形  type=5 r5
	DRECT rt;				 //矩形
	BYTE  hv:1;			     //线类型 0=水平 1=垂直
	BYTE  pirodic:7;		 //周期数
	WORD  startdeg;			 //开始角度0-359
	DWORD color;			 //线颜色
	char    nouse[16];		 //保留未用
}N4_SIN;


typedef struct N4_ARC{		 //园弧 type=6  r6
	DRECT  rt;				 //矩形
	DWORD  color;			 //颜色
	WORD   start;			 //开始角度
	WORD   end;				 //结束角度	
	char    nouse[16];		 //保留未用
}N4_ARC;

typedef struct N4_ARROW{     //方向箭头  type=7  r7
	DPOINT  pt[2];			 //两点坐标
	DWORD   color;			 //线颜色
	char    nouse[16];		 //保留未用
}N4_ARROW;

typedef struct N4_GLASS{     //玻璃层    type=8
	DRECT  rt;				 //矩形
	BYTE   depth;			 //深度
	BYTE   outline:1;		 //是否画边线
	BYTE   reserved:7;		 //保留
	DWORD  color;			 //颜色
	DWORD  lcolor;			 //边线色
	char    nouse[16];		 //保留未用
}N4_GLASS;


typedef struct N4_TEXT{      //文本  type=10    r9
	DRECT   rt;				 //矩形
	double  zm;				 //绘图时的倍率
	LOGFONT font;			 //字体
    DWORD   color;			 //颜色
	BYTE    autofit:1;		 //自适应
    BYTE    style:2;		 //式样
	BYTE    reserved:5;
	char    nouse[16];		 //保留未用
	WORD    angle;			 //角度
    char    text[1];		 //文本内容,后跟所有的字符
}N4_TEXT;

typedef struct N4_ESITE{	 //电气端子type=11
	DRECT  rt;				 //矩形
	DWORD  color;			 //端子显示颜色
	BYTE   solder:1;		 //焊接 0=焊接 1=没焊
	BYTE   reserved:7;		 //保留
	char    nouse[16];		 //保留未用
}N4_ESITE;

typedef struct N4_EGPMB{	 //组合图元母板 type=12 
	DRECT  rt;				 //矩形
	DWORD  color;			 //颜色
	BYTE   mode:1;			 //0=不显 1=显示
	BYTE   reserved:7;		 //保留
	char    nouse[16];		 //保留未用
}N4_EGPMB;

typedef struct N4_COORDINATE{ //坐标 type=13
	DRECT  rt;				 //矩形
	long   xmin;			 //X方向最小值
	long   xmax;			 //X方向最大值
	long   ymin;			 //Y方向最小值
	long   ymax;			 //Y方向最大值
	DWORD  colorc;			 //坐标线颜色
	DWORD  colorw;			 //水线颜色
	DWORD  colort;			 //文本颜色
	BYTE   xdot;			 //X坐标点数
	BYTE   ydot;			 //Y坐标点数
	BYTE   wxdraw:1;		 //X方向水线是否画
	BYTE   wydraw:1;		 //y方向水线是否画
	BYTE   xvshow:1;		 //x坐标值显示
	BYTE   yvshow:1;		 //y坐标值显示
	BYTE   reserved:4;		 //保留未用
	LOGFONT fontx;			 //X字符显示字体
	LOGFONT fonty;			 //Y字符显示字体
	double zm;				 //绘图时的倍率
	char    nouse[64];		 //保留未用
}N4_COORDINATE;

typedef struct N4_TABLE{	 //表格线 type=14
	DRECT  rt;				 //矩形
	DWORD  color;			 //线颜色
	double width;			 //线宽度
	BYTE   dbline;			 //边线加粗
	WORD   line;			 //行数
	char    nouse[64];		 //保留未用
}N4_TABLE;


typedef struct N4_IMG{		 //静态图形type=15
	DRECT rt;				 //矩形
	BYTE  shadow:1;			 //阴影
	BYTE  zoom:1;			 //支持缩放出0=No 1=Yes
	BYTE  reserved:6;		 //保留
	BYTE  depth;		     //透明度
	WORD  imgID;			 //ID
	char    nouse[16];		 //保留未用
}N4_IMG;

typedef struct N4_PATH{		 //路径 type=16  r10
	WORD  ID;				 //路经ID
	char    nouse[16];		 //保留未用
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N4_PATH;

typedef struct N4_SPIC{	     //静态小图标type=17
	DRECT rt;				 //矩形
	WORD  picID;			 //ID
	BYTE  zoom:1;			 //支持放缩 0=no 1=yes
	BYTE  reserved:7;		 //保留
	char    nouse[16];		 //保留未用
}N4_SPIC;
typedef struct N4_ANL{       //模拟量显示结构 type=64 r11
	DRECT    rt;			 //矩形
	double   zm;			 //绘图时的倍率
	LOGFONT  lf;		     //字体
	COLORREF acolor;	     //告警颜色
	COLORREF ncolor;	     //正常颜色
	BYTE     xs:4;			 //小数位
	BYTE     style:4;		 //显示风格
	WORD     angle;			 //显示角度=度*10
	char     dev_name[32];	 //设备名
	long	 did;			 //设备ID
	BYTE     dtype:4;		 //设备类型 0=发电机 1=交流线路 2=直流线路 3=母线 4=负荷  5=2绕组变压器 
							 //	6=3绕组变压器 7=电容器 8=电抗器 9=SVC
	BYTE     xsmode:4;		 //见下面,不同对象有不同的含义
	char    nouse[16];		 //保留未用
}N4_ANL;
/*
	xsmode定义：
	节点：  0=按电压等级和标幺值显示 1=显示电压绝对值和相角
	线路：  0=始端   1=末端
	变压器：0=三绕组 1=二绕组
 */
typedef struct N4_RESERVOIR{  //水库对象   type=65
	DWORD color;			 //线颜色
	DWORD ncolor;			 //正常时颜色
	DWORD hcolor;			 //高水位颜色
	DWORD lcolor;			 //低水位颜色
	char rev[32];			 //保留32字节
	char  dev_name[32];		 //水库名
	long  did;				 //水库ID
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N4_RESERVOIR;



typedef struct N4_ELEGRPA{   //组合图元显示结构type=66  r13
	DRECT    rt;			 //矩形
	BYTE     type:2;		 //数据类型类型 0=状态量 1=设备 2=站 3=公司
	BYTE     subtype:6;		 //子类型 当type=1 时为设备类型
	WORD     egrpid;		 //组合图元ID号
	BYTE     showno:1;		 //绘图时的显示号0和1
	byte     sitesum:2;		 //端子数
	BYTE     genrev:1;		 //是否显示发电机备份(发电机时有效)
	BYTE     runshow:1;		 //运行时是否显示
	BYTE     reserved:3;	 //保留
	D_SITE   site[3];		 //三个端子
	char     dev_name[32];	 //设备名
	long     did;			 //设备记录号
	char	 rev[24];		 //保留
	char     nouse[8];		 //保留未用
}N4_ELEGRPA;

typedef struct _DBSRC4{   //单点数据源
	char  name[32];			 //设备名字
	int   did;				 //设备ID
	BYTE  dtype;			 //设备类型0=发电机 1=交流线路...
	BYTE  yh;				 //优化前后 0=优化前 1=优化后 暂没用
	BYTE  xsmode;			 //值索引
}DBSRC4;

typedef struct MTRRANGE4{	 //仪表运行参数及限值
	BYTE     ptype;			 //参数类型 0=使用自定义 1=使用数据库
	float    vmin;			 //最小值
	float    vmax;			 //最大值
	BYTE	 alarm;			 //是否支持告警刻度 0=没有 1,2=有
	float	 val[4];		 //2段值(起点终点)
	DWORD    color[2];		 //2段颜色
}MTRRANGE4;

typedef struct N4_ELEGRPYB{  //组合图元仪表结构 type=67 
	DRECT	 rt;			 //矩形
	WORD     egrpid;		 //组合图元ID号
	BYTE     dbsum;			 //数据源个数
	char	 rev[24];		 //保留
	DBSRC4    dbs[8];		 //16个数据源，对应16个顺序仪表和数据
	MTRRANGE4 umr[8];		 //用户自定义量程
}N4_ELEGRPYB;



typedef struct N4_PUSH{		 //按钮格式   type=75
	DRECT   rt;				 //矩形
	double  zm;
	BYTE  style:4;			 //按钮式样0=普通按钮 1=不可见按钮
							 //2=滑过凸形按钮 3=滑过凹形按钮 
							 //4=滑动变色 5=图标按钮
	BYTE  cmdtype:4;		 //命令类型
	char  title[32];		 //按钮标题
	WORD  spicid;			 //小图标ID号
	WORD  cmdnum;		     //自定义时的WM_COMMAND消息wParam
	char  command[64];		 //命令字符串
	DWORD color1;			 //颜色1
	DWORD color2;			 //颜色2
	int   selfid;			 //要控制的自助控件的ID
	LOGFONT lf;				 //字体
	BYTE  tosta;			 //目标状态,打开画面时用
	BYTE  autlin:1;			 //位图按钮时,自动边线
	BYTE  shadow:1;			 //阴影
	BYTE  reserved:6;		 //保留
	char     nouse[30];		 //保留未用
}N4_PUSH;


typedef struct N4_FLOW{		//潮流线    type=77 r16
	BYTE  style:3;			//式样 0=一般线条 1=只显有功 2=只显无功 3=同时显示
	BYTE  direct:1;			//方向0=潮流方向与画线方向一致 1=与画线方向相反
	BYTE  type:2;			//类型 0=交流 1=直流
	BYTE  reserved:2;		//保留
	BYTE  vl;				//电压等级	 
	D_SITEB site[2];		//端子
	DWORD color1;			//有功颜色
	DWORD color2;			//无功颜色
	char  dev_name[32];		//设备名
	long  did;				//设备记录号(ID)
	char    nouse[32];		 //保留未用
	WORD  ptsum;			//点总数
	DPOINT pt[1];			//后跟所有的点
}N4_FLOW;



typedef struct N4_BUS{		//母线  type=79 r18
	DRECT   rt;				//矩形
	BYTE    type:2;			//类型
	BYTE    valarm:2;		//电压告警状态 0=正常 1=越下限 2=越上限
	BYTE    reserved:4;		//保留
	char    nouse[16];		//保留未用
	BYTE	vl;				//电压等级
	WORD    eid;			//组合图元ID
	char    dev_name[32];	//设备名
	long    did;			//设备ID号
}N4_BUS;


//区域
typedef struct N4_ZONE{		//区域    type=83
	DWORD lcolor;			//边线颜色
	char    nouse[64];		 //保留未用
	char  zone_name[32];	//区域名
	long  did;				//区域(ID)
	LOGFONT lf;				//字体
	DWORD fcolor;			//字体颜色
	WORD  ptsum;			//点总数
	DPOINT pt[1];			//后跟所有的点
}N4_ZONE;


typedef struct N4_GIFAML{    //动画图形  type=73
	DRECT rt;				 //矩形
	char  fname[64];		 //文件名
	WORD  rec;				 //GIF图形内部记录,显示用
	BYTE  type;				 //关联类型：状态量,设备,站
	DBSRC4 dsrc;			 //数据源
	char    nouse[16];		 //保留未用
}N4_GIFAML;

typedef struct N4_ACTOBJ{	//小型活动对象  type=80
	DRECT   rt;				 //矩形
	short   gid;			//图形ID
	WORD	pathid;			//所属path ID
	BYTE	runmode:1;		//运行模式 0=自动 1=同步
	BYTE	speed:3;		//自动运行速率 0,1,2,3
	BYTE    reserved:4;		//保留
	float	skip;			//自动步长
	DBSRC4 dsrc;			//数据源
	char    nouse[64];		 //保留未用
}N4_ACTOBJ;

typedef struct N4_WEATHER	//区域天气type=84
{
	DRECT   rt;	
	char    name[32];   //区域名
	int     did;			//设备ID
	LOGFONT lf;				//字体
	DWORD fcolor;			//字体颜色
	char    reserved[32];
}N4_WEATHER;

typedef struct N4_SYSPIE{     //饼图结构数据 type=68
	DRECT   rt;				 //矩形
	WORD    ID;				 //ID号
	DWORD   fcolor;			 //字符色
	LOGFONT lf;				 //字体
	BYTE    type;			 //类型
	DWORD   color[6];		 //6个颜色 最大6个部分
	char    rev[64];		 //保留
}N4_SYSPIE;

typedef struct N4_BAR{		 //棒图 type=69
	DRECT rt;				 //矩形
	float max;				 //最大值
	float min;				 //最小值
	BYTE  xy:1;              //0=x方向 1=Y方向
    BYTE  outline:1;		 //外框
    BYTE  style:3;			 //式样
	BYTE  reserved:4;		 //保留
    DWORD ncolor;			 //正常颜色
    DWORD acolor;			 //告警颜色
    float aval;				 //告警值
    DBSRC4 dsrc;			 //数据源
	char  nouse[32];		 //保留未用
}N4_BAR;


typedef struct N4_PIE{       //饼图结构数据 type=70
	DRECT   rt;				 //矩形
	DWORD   fcolor;			 //字符色
	DWORD   color[3];		 //3个颜色
	LOGFONT lf;				 //字体
	char    name[32];		 //区域名称
	int     did;			 //区域ID
	BYTE    type;			 //类型
	char    nouse[32];		 //保留未用
}N4_PIEPAM;

//保存格式V3.0
////////////////////////////////////////////////
typedef struct N3_BASATTR{    //对象基本属性  
	BYTE  type;				 //对象类型
	BYTE  belong:3;			 //所属端子 只有组合图元才有效
	BYTE  reserved:5;		 //保留
	WORD  ID;				 //对象ID
	WORD  size;              //对象字节数
}N3_BASATTR;

typedef struct N3_DBX{		 //多边形 type=1  r1
	BYTE  fill:1;		     //0=不填充 1=填充
	BYTE  close:1;			 //封闭
	BYTE  fillmode:2;		 //填充模式
	BYTE  ltype:3;			 //线类型
	BYTE  bgmode:1;			 //背景模式 0=前景 1=北京
	DWORD lcolor;			 //线颜色
	DWORD bcolor1;			 //填充颜色1
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N3_DBX;

typedef  struct N3_RECT{	 //矩形 type=2 r2
	DRECT  rt;				 //矩形
	BYTE   fill:1;			 //0=不填充 1=填充 
	BYTE   fillmode:3;		 //填充方式 
	BYTE   type:2;			 //0=一般矩形  1=3D矩形/(园)球体 
	BYTE   reserved:2;		 //保留
	DWORD  lcolor;			 //线颜色
	DWORD  bcolor1;			 //填充颜色1
}N3_RECT;

typedef N3_RECT N3_CIRCLE;	 //园 type=3  r3
    

typedef struct N3_HSIN{		 //正弦半波形 type=4  r4
	DRECT  rt;				 //矩形
	BYTE   hv:1;			 //水平或垂直 0=水平 1=垂直
	BYTE   pirodic:7;		 //周期数
	DWORD  color;			 //线颜色
}N3_HSIN;



typedef struct N3_SIN{		 //正弦波形  type=5 r5
	DRECT rt;				 //矩形
	BYTE  hv:1;			     //线类型 0=水平 1=垂直
	BYTE  pirodic:7;		 //周期数
	WORD  startdeg;			 //开始角度0-359
	DWORD color;			 //线颜色
}N3_SIN;


typedef struct N3_ARC{		 //园弧 type=6  r6
	DRECT  rt;				 //矩形
	DWORD  color;			 //颜色
	WORD   start;			 //开始角度
	WORD   end;				 //结束角度	
}N3_ARC;

typedef struct N3_ARROW{     //方向箭头  type=7  r7
	DPOINT  pt[2];			 //两点坐标
	DWORD   color;			 //线颜色	
}N3_ARROW;

typedef struct N3_GLASS{     //玻璃层    type=8
	DRECT  rt;				 //矩形
	BYTE   depth;			 //深度
	BYTE   outline:1;		 //是否画边线
	BYTE   reserved:7;		 //保留
	DWORD  color;			 //颜色
	DWORD  lcolor;			 //边线色
}N3_GLASS;

/*typedef struct N3_CBAR{    //圆拄棒图  type=9  r8
	DPOINT pt[4];			 //4个角坐标
	BYTE  xy;				 //XY方向0=x 1=y
	BYTE  outline;		     //外框
	DWORD color;		     //线颜色
}N3_CBAR;*/

typedef struct N3_TEXT{      //文本  type=10    r9
	DRECT   rt;				 //矩形
	double  zm;				 //绘图时的倍率
	LOGFONT font;			 //字体
    DWORD   color;			 //颜色
	BYTE    autofit:1;		 //自适应
    BYTE    style:2;		 //式样
	BYTE    reserved:5;
	WORD    angle;			 //角度
    char    text[1];		 //文本内容,后跟所有的字符
}N3_TEXT;

typedef struct N3_ESITE{	 //电气端子type=11
	DRECT  rt;				 //矩形
	DWORD  color;			 //端子显示颜色
	BYTE   solder:1;		 //焊接 0=焊接 1=没焊
	BYTE   reserved:7;		 //保留
}N3_ESITE;

typedef struct N3_EGPMB{	 //组合图元母板 type=12 
	DRECT  rt;				 //矩形
	DWORD  color;			 //颜色
	BYTE   mode:1;			 //0=不显 1=显示
	BYTE   reserved:7;		 //保留
}N3_EGPMB;

typedef struct N3_COORDINATE{ //坐标 type=13
	DRECT  rt;				 //矩形
	long   xmin;			 //X方向最小值
	long   xmax;			 //X方向最大值
	long   ymin;			 //Y方向最小值
	long   ymax;			 //Y方向最大值
	DWORD  colorc;			 //坐标线颜色
	DWORD  colorw;			 //水线颜色
	DWORD  colort;			 //文本颜色
	BYTE   xdot;			 //X坐标点数
	BYTE   ydot;			 //Y坐标点数
	BYTE   wxdraw:1;		 //X方向水线是否画
	BYTE   wydraw:1;		 //y方向水线是否画
	BYTE   xvshow:1;		 //x坐标值显示
	BYTE   yvshow:1;		 //y坐标值显示
	BYTE   reserved:4;		 //保留未用
	LOGFONT fontx;			 //X字符显示字体
	LOGFONT fonty;			 //Y字符显示字体
	double zm;				 //绘图时的倍率
}N3_COORDINATE;

typedef struct N3_TABLE{	 //表格线 type=14
	DRECT  rt;				 //矩形
	DWORD  color;			 //线颜色
	double width;			 //线宽度
	BYTE   dbline;			 //边线加粗
	WORD   line;			 //行数
}N3_TABLE;


typedef struct N3_IMG{		 //静态图形type=15
	DRECT rt;				 //矩形
	BYTE  shadow:1;			 //阴影
	BYTE  zoom:1;			 //支持缩放出0=No 1=Yes
	BYTE  reserved:6;		 //保留
	BYTE  depth;		     //透明度
	WORD  imgID;			 //ID
}N3_IMG;

typedef struct N3_PATH{		 //路径 type=16  r10
	WORD  ID;				 //路经ID
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N3_PATH;

typedef struct N3_SPIC{	     //静态小图标type=17
	DRECT rt;				 //矩形
	WORD  picID;			 //ID
	BYTE  zoom:1;			 //支持放缩 0=no 1=yes
	BYTE  reserved:7;		 //保留
}N_3SPIC;


///////////////////特殊动态类//////////////////////////////////////////////

//动态仪表1
typedef struct N3_METER1     //仪表参数   type=32
{
	DPOINT  pt[2];			//2个点坐标 第1点是指针顶部 第二点是园心
	LOGFONT font;			//数字字体
	float   Vmin;			//最小值
	float	Vmax;			//最大值
	BYTE    showarc;		//是否显示弧线
	BYTE    shownum;		//是否显示数字
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
	BYTE    stype;			//刻度类型
	BYTE    lstype;			//小刻度类型
	char    reserved[30];	//保留32字节
}N3_METER1;
//动态仪表2
typedef struct N3_METER2     //水平刻度 type=33
{
	DRECT	rt;
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
	char    reserved[32];	//保留32字节
}N3_METER2;

//动态仪表3
typedef struct N3_METER3     //垂直刻度 type=34
{
	DRECT	rt;
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
	char    reserved[32];	//保留32字节
}N3_METER3;

//动态仪表4
typedef struct N3_METER4       //基本仪表参数(数码) type=35
{
	DRECT	rt;
	BYTE    num;			 //总位数
	BYTE    numdot;			 //小数位数
	DWORD   bcr;			 //边框颜色
	DWORD   ncr[2];			 //整数和小数部分的颜色
}N3_METER4;


/////////////
typedef struct N3_ANL{       //模拟量显示结构 type=64 r11
	DRECT    rt;			 //矩形
	double   zm;			 //绘图时的倍率
	LOGFONT  lf;		     //字体
	COLORREF acolor;	     //告警颜色
	COLORREF ncolor;	     //正常颜色
	BYTE     xs:4;			 //小数位
	BYTE     style:4;		 //显示风格
	WORD     angle;			 //显示角度=度*10
	char     dev_name[24];	 //设备名
	long	 did;			 //设备ID
	BYTE     dtype:4;		 //设备类型 0=发电机 1=交流线路 2=直流线路 3=母线 4=负荷  5=2绕组变压器 
							 //	6=3绕组变压器 7=电容器 8=电抗器 9=SVC
	BYTE     xsmode:4;		 //见下面,不同对象有不同的含义
	char     nouse[8];		 //保留未用
}N3_ANL;
/*
	xsmode定义：
	节点：  0=按电压等级和标幺值显示 1=显示电压绝对值和相角
	线路：  0=始端   1=末端
	变压器：0=三绕组 1=二绕组
 */
typedef struct N3_RESERVOIR{ //水库对象   type=65
	DWORD color;			 //线颜色
	DWORD ncolor;			 //正常时颜色
	DWORD hcolor;			 //高水位颜色
	DWORD lcolor;			 //低水位颜色
	char  rev[32];			 //保留32字节
	char  dev_name[24];		 //水库名
	long  did;				 //水库ID
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N3_RESERVOIR;


typedef struct _SINGLEDBS3{   //单点数据源
	char  name[24];			 //设备名字
	int   did;				 //设备ID
	BYTE  dtype;			 //设备类型
	BYTE  yh;				 //优化前后 0=优化前 1=优化后 暂没用
	BYTE  xsmode;			 //值索引
}SINGLEDBS3,DBSRC3;

typedef struct MTRRANGE3{	 //仪表运行参数及限值
	BYTE     ptype;			 //参数类型 0=使用自定义 1=使用数据库
	float    vmin;			 //最小值
	float    vmax;			 //最大值
	BYTE	 alarm;			 //是否支持告警刻度 0=没有 1,2=有
	float	 val[4];		 //2段值(起点终点)
	DWORD    color[2];		 //2段颜色
}MTRRANGE3;


typedef struct N3_ELEGRPA{   //组合图元显示结构type=66  r13
	DRECT    rt;			 //矩形
	BYTE     type:2;		 //数据类型类型 0=状态量 1=设备 2=站 3=公司
	BYTE     subtype:6;		 //子类型 当type=1 时为设备类型
	WORD     egrpid;		 //组合图元ID号
	BYTE     showno:1;		 //绘图时的显示号0和1
	byte     sitesum:2;		 //端子数
	BYTE     genrev:1;		 //是否显示发电机备份(发电机时有效)
	BYTE     runshow:1;		 //运行时是否显示
	BYTE     reserved:3;	 //保留
	D_SITE   site[3];		 //三个端子
	char     dev_name[24];	 //设备名
	long     did;			 //设备记录号
	char     nouse[8];		 //保留未用
}N3_ELEGRPA;




typedef struct N3_ELEGRPYB{  //组合图元仪表结构 type=67 
	DRECT	 rt;			 //矩形
	WORD     egrpid;		 //组合图元ID号
	BYTE     dbsum;			 //数据源个数
	DBSRC3    dbs[8];		 //8个数据源，对应8个顺序仪表和数据
	MTRRANGE3 umr[8];		 //用户自定义量程
}N3_ELEGRPYB;



typedef struct N3_TREND{	 //趋势  type=68
   DRECT rt;				 //矩形
   BYTE  seg;				 //时间段数
   BYTE  jg;					 //间隔
   float max;				 //最大值
   float min;				 //最小值
   DWORD lcolor;			 //线颜色
   DWORD bcolor;			 //背景色
   DWORD wcolor;			 //水线色
   BYTE  border:1;			 //边框
   BYTE  tran:1;			 //背景透明
   BYTE  reserved:6;		 //保留
   char  ds_name[24];		 //模拟量名
   long  jlh;				 //相关记录号
   char     nouse[8];		 //保留未用
}N3_TREND;

typedef struct N3_BAR{		 //棒图 type=69
	DRECT rt;				 //矩形
	float max;				 //最大值
	float min;				 //最小值
	BYTE  xy:1;              //0=x方向 1=Y方向
    BYTE  outline:1;		 //外框
    BYTE  style:3;			 //式样
	BYTE  reserved:4;		 //保留
    DWORD ncolor;			 //正常颜色
    DWORD acolor;			 //告警颜色
    float aval;				 //告警值
    SINGLEDBS3 dsrc;		 //数据源
	char     nouse[8];		 //保留未用
}N3_BAR;


typedef struct N3_PIE{        //饼图结构数据 type=70
	DRECT   rt;				 //矩形
	BYTE    style:2;		 //0=一般 1=分离 2=立体 3=分离立体
	BYTE    outline:1;		 //包围线 0=无 1=有
	BYTE    shad:1;			 //过渡色 0=否 1=是
	BYTE    sum:4;			 //饼数
	DWORD   fcolor;			 //字符色
	WORD    angle;			 //起始角度0-360度
	DWORD   color[8];		 //8个颜色
	NPIEDAT pd[8];			 //8个数据
	char    name[24];		 //区域名称
	int     did;			 //区域ID
	char    nouse[8];		 //保留未用
}N3_PIEPAM;

typedef struct N3_DATE{       //日期格式     type=71 r14
	DRECT   rt;				 //矩形
	double  zm;
	BYTE    fmt:4;			 //日期格式 0=yyyy-mm-dd 1=mm/dd/yyyy 2=yyyy年mm月dd日
	BYTE    outline:2;		 //边框 0=无 1=凹 2=凸 3=
	BYTE    tran:1;			 //背景透明吗？0=No 1=Yes
	BYTE    shadow:1;		 //字体阴影显示
	DWORD   outcolor;		 //边线色
	DWORD   fcolor;			 //字符颜色
	DWORD   bcolor;			 //背景色
	LOGFONT font;			 //字体
}N3_DATE;

typedef N3_DATE N3_TIME;     //时间格式     type=72 r15



typedef struct N3_GIFAML{    //动画图形  type=73
	DRECT rt;				 //矩形
	char  fname[64];		 //文件名
	WORD  rec;				 //GIF图形内部记录,显示用
	BYTE  type;				 //关联类型：状态量,设备,站
	SINGLEDBS3 dsrc;		 //数据源
}N3_GIFAML;

typedef struct N3_SRLTEXT{	 //滚动文本  type=74
	DRECT   rt;				 //矩形
	double  zm;				 
	BYTE direct:3;			 //方向   0=静态文本 1=上下 2=左右 
							 //3=下上 4=右左
	BYTE glass:1;			 //是否用玻璃层 0=No 1=Yes
	BYTE outline:1;			 //是否有外框
	BYTE align:2;		     //排列方式 0=居左 1=居中 2=居右
	BYTE reserved:1;
	BYTE depth;				 //深度
	DWORD fcolor;			 //边框
	DWORD gcolor;			 //玻璃颜色
	DWORD tcolor;			 //文本颜色
	LOGFONT lf;				 //文字字体
	char text[1];			 //文字串
}N3_SRLTEXT;

typedef struct N3_PUSH{		 //按钮格式   type=75
	DRECT   rt;				 //矩形
	double  zm;
	BYTE   style:4;			 //按钮式样0=普通按钮 1=不可见按钮
							 //2=滑过凸形按钮 3=滑过凹形按钮 
							 //4=滑动变色 5=图标按钮
	BYTE  cmdtype:4;		 //命令类型
	char  title[32];		 //按钮标题
	WORD  spicid;			 //小图标ID号
	WORD  cmdnum;		     //自定义时的WM_COMMAND消息wParam
	char  command[45];		 //命令字符串
	DWORD color1;			 //颜色1
	DWORD color2;			 //颜色2
	int   selfid;			 //要控制的自助控件的ID
	LOGFONT lf;				 //字体
	BYTE  tosta;			 //目标状态,打开画面时用
	BYTE  autlin:1;			 //位图按钮时,自动边线
	BYTE  shadow:1;			 //阴影
	BYTE  reserved:6;		 //保留
	char  nouse[6];		     //保留未用
}N3_PUSH;

typedef struct N3_SELFCTL{   //自助控件  type=76
	DRECT rt;				 //矩形
	char  dllname[64];		//动态连接库名
    DWORD style;			//属性,由控件设置
    int	  id;				//ID号,以便相互控制
    char  lkbuf[255];		//启动时的连接缓冲区
    BYTE  aleft:1;			//左对齐
    BYTE  aright:1;			//右对齐
    BYTE  atop:1;			//上对齐
    BYTE  abottom:1;		//下对齐
	BYTE  mode:1;			//类型:0=编辑位置 1=其他暂未用
	BYTE  reserved:3;		//保留
	char     nouse[8];		 //保留未用
}N3_SELFCTL;


typedef struct N3_FLOW{		//潮流线    type=77 r16
	BYTE nouse1:3;			//没用
	BYTE  direct:1;			//方向0=潮流方向与画线方向一致 1=与画线方向相反
	BYTE  type:2;			//类型 0=交流 1=直流
	BYTE  reserved:2;		//保留
	BYTE  vl;				//电压等级	 
	D_SITEB site[2];		//端子
	DWORD color1;			//有功颜色
	DWORD color2;			//无功颜色
	char  dev_name[24];		//设备名
	long  did;				//设备记录号(ID)
	BYTE  linewidth;		//线宽
	char    nouse[7];		//保留未用
	WORD  ptsum;			//点总数
	DPOINT pt[1];			//后跟所有的点
}N3_FLOW;



typedef struct N3_CONLINE{	//连接线  type=78 r17
	BYTE	solder1:1;		//焊接点1显示0=不显示 1=显示
	BYTE	solder2:1;		//焊接点2显示0=不显示 1=显示
	BYTE    conobj:1;		//连接到设备标志 =0 未连接 =1 已连接
	BYTE    reserved:5;		//保留
	BYTE	vl;				//电压等级
	LOGOBJ  lobj[2];		//两个端子连接的对象
	WORD	ptsum;			//点总数
	DPOINT	pt[1];			//后跟所有的点
}N3_CONLINE;

typedef struct N3_BUS{		//母线  type=79 r18
	DRECT   rt;				 //矩形
	BYTE    type:2;			//类型
	BYTE    valarm:2;		//电压告警状态 0=正常 1=越下限 2=越上限
	BYTE    reserved:4;		//保留
	BYTE	vl;				//电压等级
	WORD    eid;			//组合图元ID
	char    dev_name[24];	//设备名
	long    did;			//设备ID号
	char    nouse[8];		 //保留未用
}N3_BUS;

typedef struct N3_ACTOBJ{	//小型活动对象  type=80
	DRECT   rt;				 //矩形
	short   gid;			//图形ID
	WORD	pathid;			//所属path ID
	BYTE	runmode:1;		//运行模式 0=自动 1=同步
	BYTE	speed:3;		//自动运行速率 0,1,2,3
	BYTE    reserved:4;		//保留
	float	skip;			//自动步长
	SINGLEDBS3 dsrc;			//数据源
	char     nouse[8];		 //保留未用
}N3_ACTOBJ;

typedef struct N3_FLASH{	//FLASH对象  type=81
	DRECT rt;				 //矩形
	char  fname[128];		//swf文件名
	BYTE  playmode:1;		//播放模式0=一次 1=循环
	BYTE  align_left:1;		//左对齐
	BYTE  align_top:1;		//上对齐
	BYTE  align_right:1;	//右对齐
	BYTE  align_buttom:1;	//下对齐
	BYTE  reserved:4;		//保留
}N3_FLASH;


typedef struct N3_PCTPIE{	//百分比饼图 type=82
	DRECT   rt;				 //矩形
	double  zm;
	char    dev_name[24];   //设备名
	int     did;			//设备ID
	BYTE    type;			//数据类型 0=传输线 1=发电机
	DWORD   color1,color2;  //两个颜色
	DWORD   fcolor;			//字体颜色
	LOGFONT lf;				//数字字体
	float   maxv;			//最大值
	char    nouse[8];		 //保留未用
}N3_PCTPIE;

//区域
typedef struct N3_ZONE{		//区域    type=83
	DWORD lcolor;			//边线颜色
	char  zone_name[24];	//区域名
	long  did;				//区域(ID)
	LOGFONT lf;				//字体
	DWORD fcolor;			//字体颜色
	WORD  ptsum;			//点总数
	DPOINT pt[1];			//后跟所有的点
}N3_ZONE;

typedef struct N3_MTTEXT{	//多行文本   type=84
	DRECT rt;				//占用的矩形
	DWORD fcolor;			//颜色
	char  name[40];			//名字
	int   did;				//(ID)
	BYTE  type;				//类型
	LOGFONT lf;				//字体
	char  text[256];		//文本缓冲
	char  rev[64];
}N3_MTTEXT;
///////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////
//以下为2.0结构

typedef struct _SINGLEDBS2{   //单点数据源
	char  name[24];			 //设备名字
	int   did;				 //设备ID
	BYTE  dtype;			 //设备类型
	BYTE  yh;				 //优化前后 0=优化前 1=优化后 暂没用
	BYTE  xsmode;			 //值索引
}SINGLEDBS2,DBSRC2;

typedef struct MTRRANGE2{	 //仪表运行参数及限值
	BYTE     ptype;			 //参数类型 0=使用自定义 1=使用数据库
	float    vmin;			 //最小值
	float    vmax;			 //最大值
	BYTE	 alarm;			 //是否支持告警刻度 0=没有 1,2=有
	float	 val[4];		 //2段值(起点终点)
	DWORD    color[2];		 //2段颜色
}MTRRANGE2;

typedef struct N2_BASATTR{    //对象基本属性  
	BYTE  type;				 //对象类型
	BYTE  belong;			 //所属端子 只有组合图元才有效
	DWORD ID;				 //对象ID
	WORD  size;              //对象字节数
}N2_BASATTR;

typedef struct N2_DBX{		 //多边形 type=1  r1
	BYTE  fill;			     //0=不填充 1=填充
	BYTE  fillmode;			 //填充方式
	BYTE  close;			 //0=不封闭   1=封闭 
	BYTE  ltype;			 //线类型
	BYTE  autozoom;			 //是否自动放大线条
	BYTE  lmode;			 //模式 0=正常 1=边框
	BYTE  endcap;			 //线头模式
	double width;			 //线宽度
	DWORD lcolor;			 //线颜色
	DWORD bcolor1;			 //填充颜色1
	DWORD bcolor2;			 //填充颜色2
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N2_DBX;

typedef  struct N2_RECT{		 //矩形 type=2 r2
	DPOINT pt[4];			 //4个角坐标
	BYTE   fill;			 //0=不填充 1=填充 
	BYTE   fillmode;		 //填充方式 
	BYTE   autozoom;		 //是否自动放大线条
	BYTE   type;			 //0=一般矩形  1=3D矩形/(园)球体 
	double width;			 //线宽度
	DWORD  lcolor;			 //线颜色
	DWORD  bcolor1;			 //填充颜色1
	DWORD  bcolor2;			 //填充颜色2
}N2_RECT;

typedef N2_RECT N2_CIRCLE;	 //园 type=3  r3
    

typedef struct N2_HSIN{		 //正弦半波形 type=4  r4
	DPOINT pt[4];			 //4个角坐标
	BYTE  ltype;			 //线类型
	BYTE  lmode;			 //模式 0=正常 1=边框
	BYTE  endcap;			 //线头模式
    BYTE  pirodic;			 //周期数
	BYTE  autozoom;			 //是否自动放大线条
	double  width;			 //线宽度
	DWORD color;			 //线颜色
	DWORD bcolor;			 //填充色
}N2_HSIN;



typedef struct N2_SIN{		 //正弦波形  type=5 r5
	DPOINT pt[4];			 //4个角坐标
	BYTE  ltype;			 //线类型 0=水平 1=垂直
	WORD  startdeg;			 //开始角度0-359
	char  reserved[9];		 //保留
	BYTE  pirodic;			 //周期数
	DWORD color;			 //线颜色
	char resed[4];			 //保留
}N2_SIN;


typedef struct N2_ARC{		 //园弧 type=6  r6
	DPOINT  pt[4];			 //4个角坐标
	DWORD   color;			 //颜色
	BYTE  autozoom;			 //是否自动放大线条
	double  width;			 //宽度
	WORD    start;			 //开始角度
	WORD    end;			 //结束角度	
}N2_ARC;

typedef struct N2_ARROW{      //方向箭头  type=7  r7
	DPOINT  pt[2];			 //两点坐标
	BYTE    autozoom;		 //是否自动放大线条
	double  width;			 //线宽度
	DWORD   color;			 //线颜色	
}N2_ARROW;

typedef struct N2_GLASS{      //玻璃层    type=8
	DPOINT  pt[4];			 //4个角坐标
	BYTE    depth;			 //深度
	DWORD   color;			 //线颜色
	BYTE    outline;		 //是否画边线
	DWORD   ocolor;			 //边线色
}N2_GLASS;

typedef struct N2_CBAR{       //圆拄棒图  type=9  r8
	DPOINT pt[4];			 //4个角坐标
	BYTE  xy;				 //XY方向0=x 1=y
	BYTE  outline;		     //外框
	DWORD color;		     //线颜色
}N2_CBAR;

typedef struct N2_TEXT{       //文本  type=10    r9
	DPOINT  pt[4];			 //4个角坐标
	double  zm;				 //绘图时的倍率
	LOGFONT font;			 //字体
    DWORD   color;			 //颜色
    char    style;			 //式样
    BYTE    autofill;		 //自动充满
    char    text[45];		 //文本内容
}N2_TEXT;

typedef struct N2_ESITE{		 //电气端子type=11
	DPOINT pt[4];			 //4个角坐标
	DWORD  color;			 //端子显示颜色
	BYTE   solder;			 //焊接 0=焊接 1=没焊
}N2_ESITE;

typedef struct N2_EGPMB{	 //组合图元母板 type=12 
	DPOINT pt[4];			 //4个角坐标
	BYTE   mode;			 //0=不显 1=显示
	DWORD  color;			 //颜色
}N2_EGPMB;

typedef struct N2_COORDINATE{ //坐标 type=13
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
	char  reserved[8];		 //保留8字节
}N2_COORDINATE;

typedef struct N2_TABLE{		 //表格线 type=14
	DPOINT pt[4];			 //4个角坐标
	DWORD  color;			 //线颜色
	double   width;			 //线宽度
	BYTE   dbline;			 //边线加粗
	WORD   line;			 //行数
	char   reserved[4];		 //保留4字节
}N2_TABLE;


typedef struct N2_IMG{		 //静态图形type=15
	DPOINT pt[4];			 //4个角坐标
	BYTE  shadow;			 //阴影
	BYTE  depth;		     //透明度
	BYTE  zoom;				 //支持缩放出0=No 1=Yes
	WORD  imgID;			 //ID
}N2_IMG;

typedef struct N2_PATH{		 //路径 type=16  r10
	WORD  ID;				 //路经ID
	double  start;			 //起点坐标
	double  end;			 //终点坐标
	DWORD color;			 //编辑时显示颜色
	WORD  ptsum;			 //点总数
	DPOINT pt[1];			 //后跟所有的点
}N2_PATH;

typedef struct N2_SPIC{	     //静态小图标type=17
	DPOINT pt[4];			 //4个角坐标
	WORD  picID;			 //ID
	BYTE  zoom;				 //支持放缩 0=no 1=yes
	char  reserved[10];		 //备用
}N2_SPIC;

/////////////
typedef struct N2_ANL{        //模拟量显示结构 type=64 r11
	DPOINT   pt[4];			 //4个角坐标
	double   zm;			 //绘图时的倍率
	LOGFONT  lf;		     //字体
	COLORREF acolor;	     //告警颜色
	COLORREF ncolor;	     //正常颜色
	BYTE     xs;			 //小数位
	BYTE     style;		     //显示风格
	BYTE     direction;		 //方向0=x方向 1=Y方向
	R_ANL    rval[5];		 //实时值
	char     dev_name[24];	 //设备名
	long	 did;			 //设备ID
	BYTE     dtype;			 //设备类型 0=发电机 1=交流线路 2=直流线路 3=母线 4=负荷  5=2绕组变压器 
							 //	6=3绕组变压器 7=电容器 8=电抗器 9=SVC
	BYTE     yh;			 //优化 0=优化前 1=优化后
	BYTE     xsmode;		 //见下面,不同对象有不同的含义
	char     reserved[23];   //保留
}N2_ANL;
/*
	xsmode定义：
	节点：  0=按电压等级和标幺值显示 1=显示电压绝对值和相角
	线路：  0=始端   1=末端
	变压器：0=三绕组 1=二绕组
 */



typedef struct N2_ELEGRPA{    //组合图元显示结构type=66  r13
	DPOINT   pt[4];			 //4个角坐标
	BYTE     type;			 //数据类型类型 0=状态量 1=设备 2=站 3=公司
	BYTE     subtype;		 //子类型 当type=1 时为设备类型
	WORD     egrpid;		 //组合图元ID号
	BYTE     showno;		 //绘图时的显示号0和1
	R_STA	 rval[3];		 //当前端子的状态
	byte     sitesum;		 //端子数
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
	char     reserve[2];	 //保留  
	char     dev_name[24];	 //设备名
	long     did;			 //设备记录号
	char     reserved[8];	 //保留8字节
}N2_ELEGRPA;


/*typedef struct N2_CURE{		 //曲线    type=67;
	DPOINT pt[4];			 //4个角坐标
	double zm;				 //绘图时的倍率
	BYTE   tran;			 //背景透明
	DWORD  bcolor;			 //背景色
	DWORD  wcolor;			 //暗影颜色
	BYTE   water;			 //是否显示水线
	BYTE   border;			 //边框
	DWORD  color;			 //曲线色
	DWORD  blcolor;			 //边线颜色
	DWORD  tcolor;			 //文本颜色
	LOGFONT font;			 //字体
	BYTE   showtxt;			 //是否显示文本
	double lwidth;			 //线宽
	float  vmax;			 //最大值
	float  vmin;			 //最小值
	SINGLEDBS dsrc;			 //数据源
	CURDATA   v1[97];		 //曲线数据;
}N2_CURE;*/



typedef struct N2_TREND{		 //趋势  type=68
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
   char  ds_name[24];		 //模拟量名
   long  jlh;				 //相关记录号
}N2_TREND;

typedef struct N2_BAR{		 //棒图 type=69
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
    SINGLEDBS2 dsrc;		 //数据源
}N2_BAR;


typedef struct N2_PIE{        //饼图结构数据 type=70
	DPOINT  pt[4];			 //4个角坐标
	WORD    ID;				 //ID号
	BYTE    style;			 //0=一般 1=分离 2=立体 3=分离立体
	BYTE    outline;		 //包围线 0=无 1=有
	BYTE    shad;			 //过渡色 0=否 1=是
	BYTE    sum;			 //饼数
	DWORD   fcolor;			 //字符色
	WORD    angle;			 //起始角度0-360度
	DWORD   color[8];		 //8个颜色
	NPIEDAT pd[8];			 //8个数据
	char    name[24];		 //区域名称
	int     did;			 //区域ID
	BYTE    type;			 //未用
	BYTE    yh;				 //优化0=优化前 1=优化后
	char    reserved[32];	 //保留字节
}N2_PIEPAM;

typedef struct N2_DATE{       //日期格式     type=71 r14
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
}N2_DATE;

typedef struct N2_TIME{		 //时间格式     type=72 r15
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
}N2_TIME;

typedef struct N2_GIFAML{     //静态图形  type=73
	DPOINT  pt[4];			 //4个角坐标
	char  fname[64];		 //文件名
	WORD  rec;				 //GIF图形内部记录,显示用
	BYTE  type;				 //关联类型：状态量,设备,站
	R_STA rval;				 //当前状态
	SINGLEDBS2 dsrc;		 //数据源
}N2_GIFAML;

typedef struct N2_SRLTEXT{	 //滚动文本  type=74
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
}N2_SRLTEXT;

typedef struct N2_PUSH{		 //按钮格式   type=75
	DPOINT  pt[4];			 //4个角坐标
	double  zm;
	BYTE  style;			 //按钮式样0=普通按钮 1=不可见按钮
							 //2=滑过凸形按钮 3=滑过凹形按钮 
							 //4=滑动变色 5=图标按钮
	char  title[32];		 //按钮标题
	WORD  spicid;			 //小图标ID号
	BYTE  autlin;			 //位图按钮时,自动边线
	BYTE  fstyle;			 //文本显示属性
	BYTE  shadow;			 //阴影
	BYTE  cmdtype;			 //命令类型
	WORD  cmdnum;		     //自定义时的WM_COMMAND消息wParam
	char  command[45];		 //命令字符串
	DWORD color1;			 //颜色1
	DWORD color2;			 //颜色2
	int   selfid;			 //要控制的自助控件的ID
	LOGFONT lf;				 //字体
	WORD  id;				 //自身ID
	BYTE  down;				 //压下状态
	BYTE  edit;				 //编辑状态
	char reserved[8];		 //保留字节
}N2_PUSH;

typedef struct N2_SELFCTL{   //自助控件  type=76
	DPOINT  pt[4];			//4个角坐标
	char  dllname[64];		//动态连接库名
    DWORD style;			//属性,由控件设置
    int	  id;				//ID号,以便相互控制
    char  lkbuf[255];		//启动时的连接缓冲区
    BYTE  aleft;			//左对齐
    BYTE  aright;			//右对齐
    BYTE  atop;				//上对齐
    BYTE  abottom;			//下对齐
	BYTE  mode;				//类型:0=编辑位置 1=其他暂未用
    BYTE  reserved1[3];		//保留

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
    char reserved[108];										//保留字节,留着发展
}N2_SELFCTL;


typedef struct N2_FLOW{		//潮流线    type=77 r16
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
	BYTE  linestyle;		//线条类型 0=圆形 1=方形 2=线条
	char  reserved[33];		//模拟量名
	char  dev_name[24];		//设备名
	long  did;				//设备记录号(ID)
	WORD  ptsum;			//点总数
	DPOINT pt[1];			//后跟所有的点
}N2_FLOW;


typedef struct N2_CONLINE{	//连接线  type=78 r17
	BYTE    autozoom;		//是否自动放大线条
	double  width;			//线宽度
	BYTE	shadow;			//阴影
	BYTE	solder1;		//焊接点1显示0=不显示 1=显示
	BYTE	solder2;		//焊接点2显示0=不显示 1=显示
	BYTE	vl;				//电压等级
	BYTE    conobj;			//连接到设备标志 =0 未连接 =1 已连接
	BYTE    el;				//带电状态 =0 不带电 =1 带电
	LOGOBJ  lobj[2];		//两个端子连接的对象
	char	rev[2];			//保留
	WORD	ptsum;			//点总数
	DPOINT	pt[1];			//后跟所有的点
}N2_CONLINE;

typedef struct N2_BUS{		//母线  type=79 r18
	DPOINT  pt[4];			//4个角坐标
	BYTE    type;			//类型
	BYTE    shadow;			//阴影
	BYTE	vl;				//电压等级
	R_STA	rval;			//实时值
	char    yh;				//优化前后
	char    valarm;			//电压告警状态 0=正常 1=越下限 2=越上限
	WORD    eid;			//组合图元ID
	char	rev[30];		//保留
	char    dev_name[24];	//设备名
	long    did;			//设备ID号
}N2_BUS;

typedef struct N2_ACTOBJ{	//小型活动对象  type=80
	DPOINT  pt[4];			//4个角坐标
	short   gid;			//图形ID
	WORD	pathid;			//所属path ID
	BYTE	runmode;		//运行模式 0=自动 1=同步
	BYTE	speed;			//自动运行速率 0,1,2,3
	float	skip;			//自动步长
	SINGLEDBS2 dsrc;		//数据源
	char	rev[64];		//保留
}N2_ACTOBJ;

typedef struct N2_FLASH{		//FLASH对象  type=81
	DPOINT  pt[4];			//4个角坐标
	char  fname[128];		//swf文件名
	BYTE  playmode;			//播放模式0=一次 1=循环
	BYTE  align_left;		//左对齐
	BYTE  align_top;		//上对齐
	BYTE  align_right;		//右对齐
	BYTE  align_buttom;		//下对齐
	char  reserved[28];		//保留
}N2_FLASH;


typedef struct N2_PCTPIE{	//百分比饼图 type=82
	DPOINT  pt[4];			//4个角坐标
	double  zm;
	char    dev_name[24];   //设备名
	int     did;			//设备ID
	BYTE    type;			//数据类型 0=传输线 1=发电机
	DWORD   color1,color2;  //两个颜色
	DWORD   fcolor;			//字体颜色
	LOGFONT lf;				//数字字体
	float   maxv;			//最大值
	float   curval;			//当前值
	char    reserved[24];	//保留备用
}N2_PCTPIE;

////////////////////////////////////////////////////////////////////////////////////////////////

#endif