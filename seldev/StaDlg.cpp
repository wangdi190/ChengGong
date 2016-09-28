// StaDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "StaDlg.h"
#include "dbapi.h"
#include "userapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *tblnms[]={"Gen",		//发电机
			   "Line",		//交流
			   "DCLine",	//直流
			   "Bus",		//母线
			   "Load",		//负荷
			   "Tfm1",		//2绕组变压器
			   "Tfm2",		//3绕组变压器
			   "Shunt",		//电容
			   "Sreact",	//电抗
			   "SVC",		//静态无功补偿装置
			   "Switch"};   //开关
/////////////////////////////////////////////////////////////////////////////
// StaDlg dialog


StaDlg::StaDlg(CWnd* pParent /*=NULL*/)
	: CDialog(StaDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(StaDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	def=NULL;
}

StaDlg::~StaDlg()
{
	if(def!=NULL) delete def;
}
void StaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(StaDlg)
	DDX_Control(pDX, IDC_LDEV, m_ldev);
	DDX_Control(pDX, IDC_DEV, m_dev);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(StaDlg, CDialog)
	//{{AFX_MSG_MAP(StaDlg)
	ON_CBN_SELCHANGE(IDC_DEV, OnSelchangeDev)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// StaDlg message handlers

BOOL StaDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	dbok=LSI_InitNTDbi();
	if(!dbok){
		MessageBox("数据库平台未启动","错误",MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	}
	LSI_CheckUser("sa","");
	m_dev.SetCurSel(ad.dbs.dtype);
	GetData(ad.dbs.dtype);
	SetToLst();
	m_ldev.SetCurSel(GetIndex(ad.dbs.did));
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void StaDlg::GetData(int dtype)
{

	DWORD idi;
	MEMTABLE *mtb;
	int t,i,j;
	num=0;
	t=dtype;
	if(t>10||t<0) return;
	if(!LSI_GetTableID(ad.mdbnm,tblnms[t],idi)) return;
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
	switch(t)
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
		
	case 2:	//直流输电线
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
	case 5://2绕变
		tfm1=(visualpw_Tfm1 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm1[i].NU;
			strcpy(def[i].name,tfm1[i].Name);
		}
		break;
	case 6://三绕变
		tfm2=(visualpw_Tfm2 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm2[i].NU;
			strcpy(def[i].name,tfm2[i].Name);
		}
		break;
	case 7://电容
		sht=(visualpw_Shunt *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=sht[i].NU;
			strcpy(def[i].name,sht[i].Name);
		}
		break;
	case 8://电抗
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
	case 10://开关，刀闸
		swt=(visualpw_Switch *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=swt[i].NU;
			strcpy(def[i].name,swt[i].Name);
		}
		break;
	}
}

void StaDlg::SetToLst()
{
	int i;
	char p[128];
	m_ldev.ResetContent();
	for(i=0;i<num;i++){
		sprintf(p,"ID:%d [%s]",def[i].id,def[i].name);
		m_ldev.AddString(p);
	}
}

void StaDlg::OnSelchangeDev() 
{
	int i;
	i=m_dev.GetCurSel();
	ad.dbs.dtype=(BYTE)i;
	GetData(ad.dbs.dtype);
	SetToLst();
	m_ldev.SetCurSel(0);
}

//返回序号
int StaDlg::GetIndex(int id)
{
	int i;
	for(i=0;i<num;i++){
		if(id==def[i].id) return i;
	}
	return 0;
}

void StaDlg::OnOK() 
{
	int i;
	i=m_ldev.GetCurSel();
	if(i==LB_ERR){
		i=-1;
		ad.dbs.did=-1;
		strcpy(ad.dbs.name,"没选择设备");
		CDialog::OnOK();
	}
	ad.dbs.did=def[i].id;
	strcpy(ad.dbs.name,def[i].name);
	CDialog::OnOK();
}
