#if !defined(AFX_MSTRUCT_H__INCLUDED_)
#define AFX_MSTRUCT_H__INCLUDED_



typedef struct _DEVDEF{	//设备
	char name[64];		//设备名
	int  id;			//设备ID
	int  stno;			//站号
}DEVDEF;	


typedef struct _SELRESERVOIR{	//设备
	char name[64];		//设备名
	int  id;			//设备ID
}SELRESERVOIR;

typedef struct _STATION
{
	char name[64];		//设备名
	int  id;			//设备ID
}STATION;
//以下数据用来实现数据选择
typedef struct _SELDATA_DEV{ //数据交换结构
	char mdbnm[256];		 //数据库名
	char name[64];			 //设备名
	int  did;				 //设备ID
	BYTE dtype;				 //设备类型
	BYTE xsmode;			 //显示模式
	/*
	xsmode定义：
	节点：  0=按电压等级和标幺值显示 1=显示电压绝对值和相角
	线路：  0=始端   1=末端
	变压器：0=三绕组 1=二绕组
	*/
	BYTE tseg;				 //时段
	char extend[128];		 //其他
}SELDATA_DEV;

//定义单点数据源（只能选择其中一点数据)
typedef struct _SINGLEDBS{   //单点数据源
	char  name[64];			 //设备名字
	int   did;				 //设备ID
	BYTE  dtype;			 //设备类型0=发电机 1=交流线路 2=直流线路 3=母线 4=负荷 5=预定义断面
	BYTE  xsmode;			 //值索引
}SINGLEDBS;

/*  xsmode和dtype的关系
	dtype=0:       发电机
	     xsmode=0  有功
		 xsmode=1  无功
	dtype=1:	   线路
		 xsmode=0  起端有功
		 xsmode=1  起端无功
		 xsmode=2  末端有功
		 xsmode=3  末端无功
	dtype=2:	   线路
		 xsmode=0  起端有功
		 xsmode=1  末端有功
	dtype=3:	   母线	
	     xsmode=0  电压标幺值
		 xsmode=1  电压绝对值
		 xsmode=2  相角
	dtype=4:	   负荷
		 xsmode=0  有功
		 xsmode=1  无功
*/


typedef struct _SELSINGLE_DEV //单值数据交换结构
{
	char mdbnm[256];		 //数据库名
	SINGLEDBS dbs;			 //数据源
	char extend[128];		 //其他
}SELSINGLE_DEV;


typedef struct _SELECTDEV    //选择设备参数
{
	char  dbname[256];		 //数据库名
	char  name[64];			 //设备名字
	int   did;				 //设备ID
	BYTE  type;				 //主类型
	BYTE  dtype;			 //设备类型 type=2时
	/*
	0="PT" 1="发电机" 2="开关,刀闸",3="负荷",4="电容",5="电抗",
	6="接地",7="二绕组变压器"
	8="三绕组变压器",9="静态无功补偿器",10="逆变、变流器"
	33=母线 34=交流 35=直流
	*/ 
}SELECTDEV;


typedef struct _SELECTPIE    //选择百分饼图参数
{
	char  dbname[256];		 //数据库名
	char  name[64];			 //设备名字
	int   did;				 //设备ID
	BYTE  dtype;			 //设备类型	0=交流线路 1=直流线路 2=发电机 
}SELECTPIE;

typedef struct _DMLS
{
	int id;			//线路ID
	BYTE type:4;	//线路类型
	BYTE ys:1;		//运算方法 0=+ 1=-
	BYTE nouse:3;	//未用
}DMLS;

#endif;