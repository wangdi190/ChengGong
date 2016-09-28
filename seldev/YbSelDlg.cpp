// YbSelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "YbSelDlg.h"
#include "userapi.h"
#include "dbapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *ybtnm[]={"SysGD","Gen","Tfm1","Tfm2","Line","DCLine","Load","Meter"};

char *yxs1[]={"当前指标"};
char *yxs2[]={"有功","无功"};
/////////////////////////////////////////////////////////////////////////////
// YbSelDlg dialog


YbSelDlg::YbSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(YbSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(YbSelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	num=0;
	def=NULL;
}

YbSelDlg::~YbSelDlg()
{
	if(def!=NULL) delete def;
}


void YbSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(YbSelDlg)
	DDX_Control(pDX, IDC_YBSEL, m_yb);
	DDX_Control(pDX, IDC_SELFLD, m_fld);
	DDX_Control(pDX, IDC_DEVLST, m_devlst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(YbSelDlg, CDialog)
	//{{AFX_MSG_MAP(YbSelDlg)
	ON_CBN_SELCHANGE(IDC_YBSEL, OnSelchangeYbsel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// YbSelDlg message handlers

BOOL YbSelDlg::OnInitDialog() 
{
	int i;
	CDialog::OnInitDialog();
	GetData(tmp.dtype);
	SetToLst();
	SetXsMode();
	m_yb.SetCurSel(tmp.dtype);
	i=GetIndex(tmp.did);
	m_devlst.SetCurSel(i);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void YbSelDlg::GetData(int dtype)
{
	visualpw_SysGD *sgd;
	visualpw_Gen   *gen;
	visualpw_Tfm1  *tf1;
	visualpw_Tfm2  *tf2;
	visualpw_Line  *lin;
	visualpw_DCLine *dln;
	visualpw_Load  *ld;
	visualpw_Meter *mtr;
	int i,j;
	DWORD idi;
	MEMTABLE *mtb;
	if(dtype<0||dtype>7) return;
	if(!LSI_GetTableID("visualpw",ybtnm[dtype],idi)) return;
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
	case 0:  //指标
		sgd=(visualpw_SysGD *)mtb->data;
		for(i=0;i<num;i++)
		{
			strcpy(def[i].name,sgd[i].Name);
			def[i].id=sgd[i].ID;
		}
		break;
	case 1: //发电机
		gen=(visualpw_Gen *)mtb->data;
		for(i=0;i<num;i++)
		{
			def[i].id=gen[i].NU;
			strcpy(def[i].name,gen[i].Name);
		}
		break;
	case 2: //2绕变
		tf1=(visualpw_Tfm1 *)mtb->data;
		for(i=0;i<num;i++)
		{
			def[i].id=tf1[i].NU;
			strcpy(def[i].name,tf1[i].Name);
		}
		break;
	case 3: //3绕变
		tf2=(visualpw_Tfm2 *)mtb->data;
		for(i=0;i<num;i++)
		{
			def[i].id=tf2[i].NU;
			strcpy(def[i].name,tf2[i].Name);
		}
		break;
	case 4: //交流
		lin=(visualpw_Line *)mtb->data;
		for(i=0;i<num;i++)
		{
			def[i].id=lin[i].NU;
			strcpy(def[i].name,lin[i].Name);
		}
		break;
	case 5: //直流
		dln=(visualpw_DCLine *)mtb->data;
		for(i=0;i<num;i++)
		{
			def[i].id=dln[i].NU;
			strcpy(def[i].name,dln[i].Name);
		}
		break;
	case 6: //负荷
		ld=(visualpw_Load *)mtb->data;
		for(i=0;i<num;i++)
		{
			def[i].id=ld[i].NU;
			strcpy(def[i].name,ld[i].Name);
		}
		break;
	case 7: //仪表
		mtr=(visualpw_Meter *)mtb->data;
		for(i=0;i<num;i++)
		{
			def[i].id=mtr[i].ID;
			strcpy(def[i].name,mtr[i].Name);
		}
	}
}


void YbSelDlg::SetToLst()
{
	int i;
	char p[128];
	m_devlst.ResetContent();
	for(i=0;i<num;i++){
		sprintf(p,"ID:%d [%s]",def[i].id,def[i].name);
		m_devlst.AddString(p);
	}
}


void YbSelDlg::SetXsMode()
{
	int i;
	m_fld.ResetContent();
	switch(tmp.dtype)
	{
	case 0: //指标
		for(i=0;i<1;i++) m_fld.AddString(yxs1[i]);
		break;
	case 1:case 2:case 3:case 4:case 5:case 6:
		for(i=0;i<2;i++) m_fld.AddString(yxs2[i]);
		break;
	case 7:
		break;
	}
	m_fld.SetCurSel(tmp.xsmode);
}

void YbSelDlg::OnSelchangeYbsel() 
{
	int i;
	i=m_yb.GetCurSel();
	tmp.dtype=(BYTE)i;
	GetData(tmp.dtype);
	SetToLst();
	m_devlst.SetCurSel(0);
	SetXsMode();
	m_fld.SetCurSel(0);
}

void YbSelDlg::OnOK() 
{
	int i;
	tmp.xsmode=m_fld.GetCurSel();
	i=m_devlst.GetCurSel();
	if(i==LB_ERR){
		tmp.did=-1;
		strcpy(tmp.name,"没选择设备");
		CDialog::OnOK();
	}
	tmp.did=def[i].id;
	strcpy(tmp.name,def[i].name);
	tmp.xsmode=m_fld.GetCurSel();
	CDialog::OnOK();
}


//返回序号
int YbSelDlg::GetIndex(int id)
{
	int i;
	for(i=0;i<num;i++){
		if(id==def[i].id) return i;
	}
	return 0;
}
