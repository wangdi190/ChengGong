#if !defined(__LIB_H)
#define __LIB_H

#define EDIT_FLOAT  0
#define EDIT_STR    1
#define EDIT_CHAR   2
#define EDIT_SHORT  3
#define EDIT_INT    4
#define EDIT_BYTE   5
#define EDIT_WORD   6
#define EDIT_DWORD  7
#define EDIT_DOUBLE 8
#define EDIT_DTIME  9
#define EDIT_DATE   10
#define EDIT_TIME   11
#define EDIT_BOOL   12
#define EDIT_bool	13
#define EDIT_FILE   14
#define EDIT_FONT   15
#define EDIT_COLOR  16
#define EDIT_GIF    17
#define EDIT_BYTEA  18
#define EDIT_AVI    19
#define EDIT_DLL    20
#define EDIT_SWF	21

#define  MAXTNM   24     //列最大
#define  MAXENM   128    //行最大
#define  MAXITEM  MAXTNM*MAXENM+24  //最大的数据项


#define  DataChanged  1001 //数据发生变化
#define  DBLCLKLINE   1002 //双击选中一记录
#define  ColorChange  1003 //颜色变化
#define  FontChange   1004 //字体发生变化
#define  FileChange   1005 //文件发生变化
#define  RBUTTONDOWN  1006 //文件发生变化
;
typedef struct _DBEDIT{  //数据编辑结构
  char  type;            //0=float 1=str 2=char 3=short 4=int 5=BYTE 6=WORD 7=DWORD
  char  *addr;           //数据交换缓冲区地址
  BYTE  strmax;          //字符串长度
  char  canedit;         //0=不可编辑 1=可编辑
  char  index;	         //<0无效 >=0&&<24时为列表编辑
   BYTE  xs;				 //小数位
  DWORD fcolor;			 //前景颜色
  DWORD bcolor;			 //背景颜色
}DBEDIT;

typedef struct _ENAME{   //单项名字
  char name[32];
  int  img;
}ENAME;

typedef struct _TNAME{   //标题名字
  char name[32];
  int  w;                //宽度
  int  img;
}TNAME;

typedef struct _dFIELD{  //C++中数据域属性
  BYTE  type;            //0=float 1=str 2=char 3=short 4=int 5=BYTE 6=WORD 7=DWORD
  BYTE  strmax;          //数据域字符长度
  char  fieldname[64];   //域名
  char  index;           //列表选项 取值范围-1,0-23
  BYTE  edit;            //允许编辑
  char  image;           //图形号  
  WORD  width;           //显示宽度
  BYTE  xs;				 //小数位数
}dFIELD;

typedef struct _PRICEPOWER{ //曲线
  double *power; //X地址
  double *price; //Y地址
}PRICEPOWER;

typedef struct __LISTNAME{
 char name[32];  //32个字节
}LISTNAME;
typedef struct _LISTITEM{
  int itemsum;      //单项数量	最大24项
  LISTNAME name[32];//字符串资料
}LISTITEM;

typedef struct _QXDATA{ //最大288点
  char name[16];
  float yvalue[288];    //Y方向值
}QXDATA;

typedef struct _BARDATA{ //棒图结构
  DWORD color;           //颜色
  char name[26];         //名字
  float value;           //当前值
  float max;			 //最小值
  float min;			 //最大值
}BARDATA;


typedef struct L2TITLE{ //第二级标题
  char name[64];  //名字
  BYTE from;	  //开始位置
  BYTE end;		  //结束位置	
}L2TITLE;

#endif