#if !defined(_DBSCDEF_H)
#define _DBSCDEF_H



#define  DB_CHAR     0
#define  DB_BYTE     1
#define  DB_SHORT    2
#define  DB_WORD	 3
#define  DB_INT      4
#define  DB_DWORD	 5
#define  DB_FLOAT    6
#define  DB_DOUBLE   7
#define  DB_DTIME    8
#define  DB_DATE     9
#define  DB_TIME	 10
///基本结构定义
//1.数据库定义
typedef struct  _DATABASE{
	char  d_name[15];			//数据库名字
	char  d_description[32];	//描述
	short d_id;					//内部标识的ID号
	char  reserved[8];			//保留
}DATABASE;
//2.数据库表
typedef struct  _DBTABLE{
	char  t_name[15];			//表名
	char  t_description[32];	//描述
	short t_id;					//内部标识的ID号
	DWORD t_len;				//表长度
	BYTE  t_type;				//表类型0=一般 1=循环表
	short d_id;					//所属数据库
	BYTE  t_level;				//访问级别0-5；
	char  reserved[8];			//保留
}DBTABLE;
//3.数据域定义
typedef struct  _DBFIELD{
	char  f_name[15];			//域名
	char  f_description[32];	//描述
	BYTE  f_type;				//数据类型
	short f_id;					//内部标识的ID号
	WORD  f_len;				//域长度
	BYTE  f_key;				//是否键
	BYTE  f_mask;				//是否掩码
	float f_deftval;			//缺省值
	WORD  f_offset;				//字节偏移量
	short t_id;					//所属数据表
	short d_id;					//所属数据库
	char  reserved[8];			//保留
}DBFIELD;
//4.掩码定义
typedef struct _DBMASK{
	char  m_name[15];			//掩码名
	char  m_description[32];	//描述
	BYTE  m_pos;				//位置
	short f_id;					//所属域
	short t_id;					//所属数据表
	short d_id;					//所属数据库
	char  reserved[4];			//保留
}DBMASK;
//5.用户定义
typedef struct _USER{
	char name[15];				//用户名
	char password[15];			//口令
	BYTE level;					//级别
	BYTE attrib;				//属性
	char reserved[15];			//保留
}USER;

//NT数据库平台接口类
//内存中的结构
//1.数据域
typedef struct M_DBFIELD{
	DBFIELD  field;				//数据域
	BYTE     n_mk;				//掩码个数
	DBMASK   *mask;				//掩码表
}M_DBFIELD;
//2.表
typedef struct M_TABLE{
	DBTABLE    table;			//数据表
	BYTE       n_fd;			//域个数
	M_DBFIELD  *field;			//数据域
}M_TABLE;
//3.数据库
typedef struct M_DBASE{
	DATABASE   dbase;		     //数据库
	BYTE       n_tb;			 //表个数
	BYTE       enable;			 //是否本地有效
	M_TABLE    *table;			 //数据域
}M_DBASE;

//数据库模板文件结构
typedef struct DMLSTRUCT{
	int  flag;			//=0xdb8003
	int  dbsum;			//数据库数
	char reserved[40];	//保留
}DMLSTRUCT;

//内存数据库实体
typedef struct  _RECATTR{		//表记录属性
	unsigned char changed:1;	//变化
	unsigned char select: 1;	//选择中标志
	unsigned char update: 1;	//最近更新标志
	unsigned char del:1;		//删除标记
	unsigned char reserved:4;	//保留
	unsigned char chg[24];		//用于标记域的变化(最大192个域)
}RECATTR;

typedef struct  _MEMTABLE{
	DWORD id;					//唯一的表ID
	int   userec;				//已使用记录数
	int   recmax;				//记录最大数
	int   reclen;				//记录长度
	unsigned char  chgtran:1;	//变化是否需要传播
	unsigned char  recchange:1;	//是否接收外部的变化数据
	unsigned char  change:1;	//数据库表是否被修改过
	unsigned char  reserved:5;	//空余保留
	M_TABLE  *tbl;				//表结构地址
	M_DBASE  *dbb;				//数据库结构指针
	char     *data;				//记录数据
	RECATTR  *recattr;			//记录属性
}MEMTABLE;


#endif