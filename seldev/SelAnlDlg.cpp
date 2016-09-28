// SelAnlDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "SelAnlDlg.h"
#include "dbapi.h"
#include "userapi.h"
#include "pysel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *tblnm[]={"Gen",		//发电机
			   "Line",		//交流
			   "DCLine",	//直流
			   "Bus",		//母线
			   "Load",		//负荷
			   "Tfm1",		//2绕组变压器
			   "Tfm2",		//3绕组变压器
			   "Shunt",		//电容
			   "Sreact",	//电抗
			   "SVC",		//静态无功补偿装置
			   "Zone",		//区域
			   "Grid",		//电网
			   "Hvcondata", //特高压
			   "PreDefSF",	//预定断面
			   "Relation",	//关系表量测
			   "UnEquMeas",	//非设备量测
};	
char *fld[]={"intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "intNU","strName",
			 "ID","Name"};
char *xs1[]={"电压等级","电压标幺值","电压绝对值","相角显示"};//母线
char *xs2[]={"始端有功和无功","末端有功和无功","电流","首有功","首无功","末有功","末有功"};//交流线路
char *xs3[]={"变压器档位","高端有功","高端无功","高端电流","低端有功","低端无功","低端电流","中端有功","中端无功","中端电流"};//变压器
char *xs4[]={"显示始端有功","显示末端有功","电流"};//直流
char *xs5[]={"投入容量","投入组数"};//电容
char *xs6[]={"有功发电","有功负荷","有功需求","小时费用"};//区域
char *xs7[]={"有功+j无功格式","有功","无功"};//发电机、负荷
char *xs8[]={"系统发电总有功","系统发电总无功","旋转备份","总在线容量","总有功负荷","总无功负荷"};//电网
char *xs9[]={"当前值","最大值","最小值"};//断面
/////////////////////////////////////////////////////////////////////////////
// SelAnlDlg dialog

SelAnlDlg::SelAnlDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelAnlDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelAnlDlg)
	//}}AFX_DATA_INIT
	num=0;
	def=NULL;
	numt=0;
	deft=NULL;
}

SelAnlDlg::~SelAnlDlg()
{
	if(def!=NULL) delete def;
	def=NULL;
	if(deft!=NULL) delete deft;
	deft=NULL;
}
void SelAnlDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelAnlDlg)
	DDX_Control(pDX, IDC_XS, m_xs);
	DDX_Control(pDX, IDC_LDEV, m_ldev);
	DDX_Control(pDX, IDC_DEV, m_dev);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelAnlDlg, CDialog)
	//{{AFX_MSG_MAP(SelAnlDlg)
	ON_CBN_SELCHANGE(IDC_DEV, OnSelchangeDev)
	ON_EN_CHANGE(IDC_PYJS, OnChangePyjs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelAnlDlg message handlers

BOOL SelAnlDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	dbok=LSI_InitNTDbi();
	if(!dbok){
		MessageBox("数据库平台未启动","错误",MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	}
	m_dev.SetCurSel(ad.dtype);
	GetData(ad.dtype);
	SetToLst();
	m_ldev.SetCurSel(GetIndex(ad.did));
	SetXSMode();
	return TRUE;
}
//返回数据
void SelAnlDlg::GetData(int dtype)
{
	int i,j;
	DWORD idi;
	MEMTABLE *mtb;

	if(dtype==11){
		if(def!=NULL) delete def;
		def=NULL;
		num=0;
		return;
	}
	if(dtype<0||dtype>15) return;
	if(dtype>=13 && dtype<=15)
	{
		if(!LSI_GetTableID("common",tblnm[dtype],idi)) return;
	}
	else
	{
		if(!LSI_GetTableID(ad.mdbnm,tblnm[dtype],idi)) return;
	}
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	num=mtb->userec;
	if(def!=NULL) delete def;
	def=new DEVDEF[num];
	if(def==NULL){
		num=0;
		return;
	}
	switch(dtype)
	{
	case 0: //发电机
		gen=(visualpw_Gen *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=gen[i].NU;
			strcpy(def[i].name,gen[i].Name);
		}
		break;
	case 1: //交流输电线
		line=(visualpw_Line *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=line[i].NU;
			strcpy(def[i].name,line[i].Name);
		}
		break;
	case 2: //直流输电线
		dcl=(visualpw_DCLine *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=dcl[i].NU;
			strcpy(def[i].name,dcl[i].Name);
		}
		break;
	case 3: //母线
		bus=(visualpw_Bus *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=bus[i].NU;
			strcpy(def[i].name,bus[i].Name);
		}
		break;
	case 4: //负荷
		load=(visualpw_Load *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=load[i].NU;
			strcpy(def[i].name,load[i].Name);
		}
		break;
	case 5: //2绕变
		tfm1=(visualpw_Tfm1 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm1[i].NU;
			strcpy(def[i].name,tfm1[i].Name);
		}
		break;
	case 6: //三绕变
		tfm2=(visualpw_Tfm2 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm2[i].NU;
			strcpy(def[i].name,tfm2[i].Name);
		}
		break;
	case 7: //电容
		sht=(visualpw_Shunt *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=sht[i].NU;
			strcpy(def[i].name,sht[i].Name);
		}
		break;
	case 8: //电抗
		srt=(visualpw_Sreact *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=srt[i].NU;
			strcpy(def[i].name,srt[i].Name);
		}
		break;
	case 9: //SVC
		svc=(visualpw_SVC *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=svc[i].NU;
			strcpy(def[i].name,svc[i].Name);
		}
		break;
	case 10: //区域
		zon=(visualpw_Zone *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=zon[i].NU;
			strcpy(def[i].name,zon[i].Name);
		}
		break;
	case 12: //高压互联
		/*hvc=(visualpw_Hvcondata *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=hvc[i].ID;
			strcpy(def[i].name,hvc[i].Name1);
		}*/
		break;
	case 13: //预定义断面
		defsf=(common_PreDefSF *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=defsf[i].ID;
			strcpy(def[i].name,defsf[i].Name);
		}
		break;
	/*case 14: //系统
		sys=(visualpw_SysGD *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=sys[i].ID;
			strcpy(def[i].name,sys[i].Name);
		}
		break;*/
	case 14: //设备量测
		rel=(common_Relation *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=rel[i].NU;
			strcpy(def[i].name,rel[i].MeasID);
		}
		break;
	case 15: //非设备量测
		unequ=(common_UnEquMeas *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=unequ[i].NU;
			strcpy(def[i].name,unequ[i].Name);
		}
		break;
	}
}
//设置到列表框
void SelAnlDlg::SetToLst()
{
	int i;
	char p[128];
	m_ldev.ResetContent();
	for(i=0;i<num;i++){
		sprintf(p,"ID:%d [%s]",def[i].id,def[i].name);
		m_ldev.AddString(p);
	}
}
//返回序号
int SelAnlDlg::GetIndex(int id)
{
	int i;
	for(i=0;i<num;i++){
		if(id==def[i].id) return i;
	}
	return 0;
}

void SelAnlDlg::OnSelchangeDev() 
{
	int i;
	i=m_dev.GetCurSel();
	ad.dtype=(BYTE)i;
	GetData(ad.dtype);
	SetToLst();
	m_ldev.SetCurSel(0);
	SetXSMode();
	if(ad.dtype==5 || ad.dtype==6)
		m_xs.SetCurSel(1);
	else
		m_xs.SetCurSel(0);

}

void SelAnlDlg::OnOK() 
{
	int i,n;
	ad.xsmode=m_xs.GetCurSel();
	i=m_ldev.GetCurSel();
	if(i==LB_ERR){
		if(ad.dtype==11){
			ad.did=0;
			strcpy(ad.name,"系统统计");
		}else{
			ad.did=-1;
			strcpy(ad.name,"没选择设备");
		}
		CDialog::OnOK();
		return;
	}
	if(deft!=NULL)
	{
		ad.did=deft[i].id;
		n=strlen(deft[i].name);
		n=n>23 ? 23:n;
		strncpy(ad.name,deft[i].name,n);
		ad.name[n]=0;
	}
	else
	{
		ad.did=def[i].id;
		n=strlen(def[i].name);
		n=n>23 ? 23:n;
		strncpy(ad.name,def[i].name,n);
		ad.name[n]=0;
	}
	CDialog::OnOK();
}

//设置显示模式
void SelAnlDlg::SetXSMode()
{
	int i;
	m_xs.ResetContent();
	switch(ad.dtype){
	case 0:
		m_xs.EnableWindow(true);
		for(i=0;i<3;i++) m_xs.AddString(xs7[i]);
		break;
	case 1: //交流线路
		m_xs.EnableWindow(true);
		for(i=0;i<7;i++) m_xs.AddString(xs2[i]);
		break;
	case 2://直流线路
		m_xs.EnableWindow(true);
		for(i=0;i<3;i++) m_xs.AddString(xs4[i]);
		break;
	case 3:  //节点或母线
		m_xs.EnableWindow(true);
		for(i=0;i<4;i++) m_xs.AddString(xs1[i]);
		break;
	case 4:  //负荷
		m_xs.EnableWindow(true);
		for(i=0;i<3;i++) m_xs.AddString(xs7[i]);
		break;
	case 5:  //2绕组变压器
		m_xs.EnableWindow(true);
		for(i=0;i<7;i++) m_xs.AddString(xs3[i]);
		break;
	case 6:  //3绕组
		m_xs.EnableWindow(true);
		for(i=0;i<10;i++) m_xs.AddString(xs3[i]);
		break;
	case 7:  case 8: //电容器 电抗器
		m_xs.EnableWindow(true);
		for(i=0;i<2;i++) m_xs.AddString(xs5[i]);
		break;
	case 9:
		m_xs.EnableWindow(false);
		m_xs.AddString("静态无功投入容量");
		break;
	case 10:
		m_xs.EnableWindow(true);
		for(i=0;i<2;i++) m_xs.AddString(xs6[i]);
		break;
	case 11:
		m_xs.EnableWindow(true);
		for(i=0;i<6;i++) m_xs.AddString(xs8[i]);
		break;
	case 12:
		m_xs.EnableWindow(false);
		break;
	case 13://断面
		m_xs.EnableWindow(true);
		for(i=0;i<3;i++) m_xs.AddString(xs9[i]);
		break;
	case 14:
	case 15:
		m_xs.EnableWindow(false);
		m_xs.AddString("量测值");
		break;
	}
	m_xs.SetCurSel(ad.xsmode);
}

void SelAnlDlg::OnChangePyjs() 
{
	int i,n;
	PySel psl;
	char str[16];
	if(num==0) return;
	GetDlgItemText(IDC_PYJS,str,10);
	if(deft!=NULL) delete deft;
	deft=new DEVDEF[num];
	n=0;
	for(i=0;i<num;i++)
	{
		if(psl.IsThisPy(str,def[i].name))
		{
			deft[n]=def[i];
			n++;
		}
	}
	numt=n;
	OrderDevByName();
	SetDevList();
}

void SelAnlDlg::SetDevList()
{
	int i;
	char p[128];
	m_ldev.ResetContent();
	for(i=0;i<numt;i++){
		sprintf(p,"ID:%d [%s]",deft[i].id,deft[i].name);
		m_ldev.AddString(p);
	}
}

//设备按名字排序
void SelAnlDlg::OrderDevByName()
{
	int i,j;
	DEVDEF tmp;
	for(i=0;i<numt-1;i++)
	{
		for(j=i+1;j<numt;j++)
		{
			if(strcmp(deft[i].name,deft[j].name)>0)
			{
				tmp=deft[i];
				deft[i]=deft[j];
				deft[j]=tmp;
			}

		}
	}
}
