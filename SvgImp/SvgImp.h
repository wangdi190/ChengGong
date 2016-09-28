
// The following ifdef block is the standard way of creating macros which make exporting 
// from a DLL simpler. All files within this DLL are compiled with the SVGIMP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see 
// SVGIMP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
#ifdef SVGIMP_EXPORTS
#define SVGIMP_API __declspec(dllexport)
#else
#define SVGIMP_API __declspec(dllimport)
#endif

#include "..\PowerPaint\ptdefine.h"
#include <vector>

enum PWTYPE //PW0类型，属性N_BASATTR里的type
{
	N_DBX_TYPE=1,
	N_RECT_TYPE=2,
	N_CIRCLE_TYPE=3,
	N_ARC_TYPE=6,
	N_TEXT_TYPE=10,	//文本
	N_ESITE_TYPE=11,//端子
	N_IMG_TYPE=15,  //图形
	N_SPIC_TYPE=17, //小图
	N_ANL_TYPE=64,		//模拟量
	N_ELEGRPA_TYPE=66,
	N_PUSH_TYPE=75,		//按钮
	N_FLOW_TYPE=77,		//潮流线
	N_CONLINE_TYPE=78,	//连接线
	N_BUS_TYPE=79		//母线
};

//组合图议案类型类型，属性N_ELEGRPA里的type,和PWTYPE互为补充         
//设备类型 0=PT 1=发电机 2=开关,刀闸 3=负荷 4=电容 5=电抗 6=接地 7=二绕组变压器",8=三绕组变压器
enum EGPTYPE 
{
	EGP_PT=0,//0=PT
	EGP_GEN=1,//1=发电机
	EGP_SWT=2,//2=开关
	EGP_LOD=3,//3=负荷
	EGP_SHT=4,//4=电容器
	EGP_RTR=5,//5=电抗器
	EGP_ERH=6,//6=接地
	EGP_TF2=7,//7=2绕组变压器
	EGP_TF3=8,//8=3绕组变压器
	EGP_SVC=9,//9=静止无功补偿器
	EGP_CVT=10//10=静止无功补偿器
};

enum SYMTYPE //对称类型
{
	SYM_NONE=0,
	SYM_ORIG=1,
	SYM_YAXIS=2,
	SYM_XAXIS=3,
	SYM_YXPOS=4,
	SYM_YXNEG=5
};

SVGIMP_API typedef struct SVG_GRAPH //图形，对应BASE0对象
{
	N_BASATTR attr;
	void* graph;
	SYMTYPE sym;
	float fAngle;//图元旋转角
}SVG_GRAPH;
SVGIMP_API typedef std::vector<SVG_GRAPH*> SVGGRAPHVTR;

SVGIMP_API typedef struct SVG_ELEGRP //内存图元,对应N_ELEGRP
{
	WORD  id;				//内部ID号
	BYTE  type;				//类型
	char  name[15];			//名字
	BYTE  subtype;			//子类型
	BYTE  sitesum;			//端子数,仪表时代表仪表的个数
	DRECT srt[3];			//3个端子位置

	SVGGRAPHVTR g1Vtr;
	DRECT rt1;				//占用的矩形
	SVGGRAPHVTR g2Vtr;
	DRECT rt2;				//占用的矩形
}SVG_ELEGRP;
SVGIMP_API typedef std::vector<SVG_ELEGRP*> SVGELEGRPVTR;

SVGIMP_API typedef struct SVG_LAYER //图层,对应N_layer
{
	char szName[25];
	SVGGRAPHVTR gVtr;
}SVG_LAYER;

SVGIMP_API typedef struct SVG_PAGE  //画面页
{
	int dx;
	int dy;
	WORD width;		//宽
	WORD height;	//高
	DWORD bgcolor;	//背景色

	SVGELEGRPVTR egrpVtr;  //图元
	SVG_LAYER layer[MAXLAYER]; //图层
	int laynum;					//图层数
}SVG_PAGE;

//SVG导入函数
SVGIMP_API int SvgImport(char* pSvgFile,char* pStyle,SVG_PAGE** page);
//释放SVG_PAGE对象
SVGIMP_API void ReleaseSvgPage(SVG_PAGE* page);


