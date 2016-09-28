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
///�����ṹ����
//1.���ݿⶨ��
typedef struct  _DATABASE{
	char  d_name[15];			//���ݿ�����
	char  d_description[32];	//����
	short d_id;					//�ڲ���ʶ��ID��
	char  reserved[8];			//����
}DATABASE;
//2.���ݿ��
typedef struct  _DBTABLE{
	char  t_name[15];			//����
	char  t_description[32];	//����
	short t_id;					//�ڲ���ʶ��ID��
	DWORD t_len;				//������
	BYTE  t_type;				//������0=һ�� 1=ѭ����
	short d_id;					//�������ݿ�
	BYTE  t_level;				//���ʼ���0-5��
	char  reserved[8];			//����
}DBTABLE;
//3.��������
typedef struct  _DBFIELD{
	char  f_name[15];			//����
	char  f_description[32];	//����
	BYTE  f_type;				//��������
	short f_id;					//�ڲ���ʶ��ID��
	WORD  f_len;				//�򳤶�
	BYTE  f_key;				//�Ƿ��
	BYTE  f_mask;				//�Ƿ�����
	float f_deftval;			//ȱʡֵ
	WORD  f_offset;				//�ֽ�ƫ����
	short t_id;					//�������ݱ�
	short d_id;					//�������ݿ�
	char  reserved[8];			//����
}DBFIELD;
//4.���붨��
typedef struct _DBMASK{
	char  m_name[15];			//������
	char  m_description[32];	//����
	BYTE  m_pos;				//λ��
	short f_id;					//������
	short t_id;					//�������ݱ�
	short d_id;					//�������ݿ�
	char  reserved[4];			//����
}DBMASK;
//5.�û�����
typedef struct _USER{
	char name[15];				//�û���
	char password[15];			//����
	BYTE level;					//����
	BYTE attrib;				//����
	char reserved[15];			//����
}USER;

//NT���ݿ�ƽ̨�ӿ���
//�ڴ��еĽṹ
//1.������
typedef struct M_DBFIELD{
	DBFIELD  field;				//������
	BYTE     n_mk;				//�������
	DBMASK   *mask;				//�����
}M_DBFIELD;
//2.��
typedef struct M_TABLE{
	DBTABLE    table;			//���ݱ�
	BYTE       n_fd;			//�����
	M_DBFIELD  *field;			//������
}M_TABLE;
//3.���ݿ�
typedef struct M_DBASE{
	DATABASE   dbase;		     //���ݿ�
	BYTE       n_tb;			 //������
	BYTE       enable;			 //�Ƿ񱾵���Ч
	M_TABLE    *table;			 //������
}M_DBASE;

//���ݿ�ģ���ļ��ṹ
typedef struct DMLSTRUCT{
	int  flag;			//=0xdb8003
	int  dbsum;			//���ݿ���
	char reserved[40];	//����
}DMLSTRUCT;

//�ڴ����ݿ�ʵ��
typedef struct  _RECATTR{		//����¼����
	unsigned char changed:1;	//�仯
	unsigned char select: 1;	//ѡ���б�־
	unsigned char update: 1;	//������±�־
	unsigned char del:1;		//ɾ�����
	unsigned char reserved:4;	//����
	unsigned char chg[24];		//���ڱ����ı仯(���192����)
}RECATTR;

typedef struct  _MEMTABLE{
	DWORD id;					//Ψһ�ı�ID
	int   userec;				//��ʹ�ü�¼��
	int   recmax;				//��¼�����
	int   reclen;				//��¼����
	unsigned char  chgtran:1;	//�仯�Ƿ���Ҫ����
	unsigned char  recchange:1;	//�Ƿ�����ⲿ�ı仯����
	unsigned char  change:1;	//���ݿ���Ƿ��޸Ĺ�
	unsigned char  reserved:5;	//���ౣ��
	M_TABLE  *tbl;				//���ṹ��ַ
	M_DBASE  *dbb;				//���ݿ�ṹָ��
	char     *data;				//��¼����
	RECATTR  *recattr;			//��¼����
}MEMTABLE;


#endif