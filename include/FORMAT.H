#if !defined(format_h)
#define format_h

class CMemDC;
typedef struct _SCR_FORMAT{  //屏幕格式化文件头
 WORD     Version;           //文件版本号=2000
 char     Name[40];		     //画面名字
 char     bgflag;            //背景属性 0=文件形式 1=映象保存在本文件中 压缩格式大小为bgsize; 
 COLORREF BkColor;			 //背景颜色
 char     BgStyle;			 //背景画法 0正常1居中2平铺
 WORD     Width;			 //宽度
 WORD     Height;			 //高度;
 WORD	  ObjSum;            //对象总数
 DWORD    fsize;			 //文件字节数
 DWORD    attribsize;        //属性字节数
 DWORD    dbsize;            //数据字节数
 DWORD    bgsize;	         //背景图形字节数
 char resved[118];			 //保留118字节
 }SCR_FORMAT;
//FMT文件存储顺序
/*
 [00000]:文件头
 [xxxxx]:OBJ
 [yyyyy]:db
 [zzzzz]:bgimg
  */
typedef struct _ATTRIB_OBJ{  //所有的对象通用属性
 BYTE  type;				 //对象类型
 BYTE  enable;				 //0=无效 1=有效
 short x1,y1,x2,y2;          //所占的矩形区域
 WORD  size;                 //对象字节数
 DWORD offset;               //对象偏移量
}ATTRIB_OBJ;
//对象类型定义
/*	0=静态图形
	1=动画
	2=按钮
	3=模拟量
	4=状态量
	5=累加量
	6=曲线
	7=棒图
	8=饼图
	9=趋势图
	10=设备
	11=站
	12=表
	13=线
	14=多边形(封闭和不封闭）
	15=图形元素
	16=文本
	17=时间
	18=日期
	19=站、设备实时表格
	20=凸矩形
	21=凹矩形
	22=玻璃层
	23=公共控制
	24=控制点
	25=AVI电影
	26=自动滚动文本
	27=自助控件(*.dll)
	28=立体园柱
*/
typedef struct OBJ_CIRBAR{ //立体柱
	BYTE  type;            //0=园柱 1=立方体
	BYTE  outline;		   //是否有外框
	BYTE  shad;			   //过渡色 0=否 1=是
	DWORD color;		   //颜色
	char reserved[12];	   //保留12字节为将来备用
}OBJ_CIRBAR;


typedef struct _OBJ_IMG{//静态图形
 char  fname[64];		//文件名
 BYTE  tranbk;          //背景透明
 BYTE  shadow;          //阴影显示0没有 1-3有效
 DWORD BkColor;         //透明颜色
 BYTE  depth;			//透明度
 CMemDC *dc;			//图形DC指针
}OBJ_IMG;

typedef OBJ_IMG OBJ_GIFAML;//GIF动画


typedef struct OBJ_LINE{//线
   BYTE  width;		    //线宽度
   DWORD color;			//线颜色
   BYTE  shadow;        //阴影显示0没有 1-3有效
}OBJ_LINE;

typedef struct OBJ_DBX{ //多边形
   char  close;			//<0不封闭 >=0填充 封闭
   char  outline;       //是否画边框 0=No 1=Yes
   BYTE  width;			//线宽度
   DWORD fcolor;		//线颜色
   DWORD bcolor1;		//填充第一颜色
   DWORD bcolor2;		//填充第二颜色
   WORD  ptsum;			//点总数
   POINT pt;            //后跟所有的点           
}OBJ_DBX;

typedef struct OBJ_TX{  //矩形，园
   char  type;          //0=空矩形	1=实矩 2=空园 3=实园
   char  style;         //填充方式0-9
   char  outline;       //是否画边框 0=No 1=Yes
   BYTE  width;			//线宽度
   DWORD fcolor;		//线颜色
   DWORD bcolor1;		//填充第一颜色
   DWORD bcolor2;		//填充第二颜色
   BYTE  shadow;		//阴影
}OBJ_TX;

typedef struct OBJ_GLASS{
   BYTE  outline;		//轮廓
   DWORD bcolor;		//玻璃色
   DWORD fcolor;		//边线色
   BYTE  depth;			//深度
}OBJ_GLASS;
typedef struct OBJ_TEXT{//文本格式
   LOGFONT font;        //字体
   DWORD   color;		//颜色
   char    style;		//式样
   BYTE    shadow;		//阴影
   char    text[45];	//文本内容
}OBJ_TEXT;

typedef struct OBJ_PUSH{//按钮格式
   BYTE style;          //按钮式样0=普通按钮 1=不可见按钮
						//2=滑过凸形按钮 3=滑过凹形按钮 
						//4=滑动变色 
   char title[32];		//按钮标题
   BYTE shadow;			//阴影
   BYTE cmdtype;        //命令类型
   WORD cmdnum;		    //自定义时的WM_COMMAND消息wParam
   char command[45];	//命令字符串
   DWORD color1;		//颜色1
   DWORD color2;		//颜色2
   int   selfid;		//要控制的自助控件的ID
   char reserved[8];    //保留字节
}OBJ_PUSH;

typedef struct OBJ_SRLTEXT{//滚动文本
   BYTE direct;			//方向   0=静态文本 1=上下 2=左右 
						//3=下上 4=右左
   BYTE tstyle;			//文本样式
   BYTE glass;			//是否用玻璃层
   BYTE depth;			//深度
   DWORD bcolor;		//边框
   DWORD gcolor;		//玻璃颜色
   DWORD tcolor;		//文本颜色
   LOGFONT lf;			//文字字体
   BYTE  align;		    //排列方式
   WORD  id;			//ID号
   char text[256];		//文字串
}OBJ_SRLTEXT;


typedef struct OBJ_SMSG{//状态类的动态点
   int msgid;			//信号ID；包括状态量，设备，站
   BYTE grpn;           //图号
   BYTE status;			//当前状态
   BYTE alarm;			//是否告警
}OBJ_SMSG;

typedef struct OBJ_3DRT{//3D矩形
   BYTE  width;		    //线宽
}OBJ_3DRT;

typedef struct OBJ_ANL{      //模拟量显示结构
 int      Id;				 //模拟量ID
 char     unit[10];			 //单位字符串
 float    max;				 //最大值
 float    min;				 //最小值
 LOGFONT  lf;		         //字体
 COLORREF acolor;		     //告警颜色
 COLORREF ncolor;	         //正常颜色
 BYTE     ws;			     //显示位数
 BYTE     xs;				 //小数位
 BYTE     style;		     //字体显示 0=正常 1=凹 2=凸
 BYTE     xsmode;			 //显示方式 0=数字显示 1=水平标尺显示
							 //2=竖直标尺
 BYTE     shadow;			 //阴影
 float    curval;			 //当前值
 BYTE     alarm;			 //告警
 }OBJ_ANL;

typedef struct OBJ_RAT{      //累加显示结构
 int      Id;				 //累加量ID
 LOGFONT  lf;		         //字体
 COLORREF acolor;		     //告警颜色
 COLORREF color;	         //正常颜色
 BYTE     style;		     //字体显示 0=正常 1=凹 2=凸
 DWORD    curval;			 //当前值
 BYTE     alarm;			 //告警
 }OBJ_RAT;

typedef struct OBJ_DTIME{    //时间日期格式
 BYTE    type;				 //0=正常显示 1=用户定义字体显示
 BYTE    outline;			 //边框 0=无 1=凹 2=凸
 DWORD   fcolor;			 //颜色
 DWORD   bcolor;			 //背景色
 LOGFONT font;				 //字体
 BYTE    style;			     //字体显示 0=正常 1=凹 2=凸
}OBJ_DTIME;;

typedef struct OBJ_BAR{		 //棒图
   int  xy;                  //0=x方向 1=Y方向
   int  id1;				 //模拟量
   int  id2;				 //模拟量
   int  id3;				 //模拟量
   float max;				 //最大值
   float min;				 //最小值
   DWORD color1;			 //第一棒颜色
   DWORD color2;			 //第二棒颜色
   DWORD color3;			 //第二棒颜色
   float val[3];			 //当前值
}OBJ_BAR;

typedef struct OBJ_TREND{	 //趋势
   int  id;					 //模拟量ID
   BYTE seg;				 //时间段数
   BYTE jg;					 //间隔
   float max;				 //最大值
   float min;				 //最小值
   BYTE  shadow;			 //阴影
   float val[9];			 //最大8段数
}OB_TREND;

typedef struct OBJ_FORM{     //设备实时YC、YX表格
   BYTE  type;				 //0=设备、1=站 2=设备资料 
   int   id;                 //站、设备ID
   char  name[32];			 //表格名字
   BYTE  bgtr;				 //背景透明
   DWORD acolor;			 //告警颜色
   DWORD ncolor;			 //正常颜色
}OBJ_FORM;

typedef struct OBJ_QX{       //曲线
   int   id;                 //模拟量ID
   float max;			     //最大值
   float min;				 //最小值
   BYTE  bgtr;				 //背景透明
   BYTE  shadow;			 //阴影
   DWORD color[5];			 //0背景色 1背景线色 2-4三条曲线色
   float val1[96];			 //共96点15分间隔计24小时	 
   float val2[96];				
   float val3[96];			 
   //第一条线=昨日曲线 第二条线上周 第三条线=今日线
}OBJ_QX;
 
typedef struct OBJ_COMCTL{	//公共控制
   BYTE  type;				//0=编辑 1=列表框 2=组合框 3=TREE 
   WORD  eid;				//编辑框ID值
   BYTE  outline;			//外框风格
   DWORD wstyle;            //风格
   BYTE  left;				//左对齐
   BYTE  right;				//右对齐
   BYTE  top;				//上对齐
   BYTE  bottom;			//下对齐
   short width;				//保留宽度
   short height;			//保留高度
   char  str[320];			//保存其他与此相关的信息(如列表信息等)
}OBJ_COMCTL;


typedef struct OBJ_CONTROL{ //控制点=YK、YT
   BYTE type;				//0=YK;1=YT;2=自定义点
   int  id;					//YK、YT id值
   BYTE check;				//是否反校
   WORD group;				//组号
   WORD rtu;				//RTU号
   WORD num;				//顺序号
   char name[26];			//YK点名称
}OBJ_CONTROL;

typedef struct OBJ_SELFCTL{ //自助控件
   char  dllname[64];		//动态连接库名
   DWORD style;				//属性,由控件设置
   int   id;				//ID号,以便相互控制
   char  lkbuf[255];		//启动时的连接缓冲区
   BYTE  aleft;				//左对齐
   BYTE  aright;			//右对齐
   BYTE  atop;				//上对齐
   BYTE  abottom;			//下对齐
   short awdth;				//保留宽度
   short ahght;				//保留高度
   HINSTANCE hinst;         //DLL的事例
   HWND  hwnd;				//窗口句柄
   void  *rc;				//初始化产生的资源(如果有)
   int  (WINAPI*DfGetVer)();//返回版本号
   void (WINAPI*DfDrawDemo)(HDC,RECT,DWORD,char *);    //演示绘图
   void*(WINAPI*DfInit)(HWND,HWND&,RECT,int,DWORD,char*);//初始化
   void (WINAPI*DfClose)(void *rc);		  //关闭
   void (WINAPI*DfAbout)();				  //关于该控件
   void (WINAPI*DfSetParam)(DWORD&,char*);//配置参数
   char reserved[120];		              //保留字节,留着发展
}OBJ_SELFCTL;

#endif