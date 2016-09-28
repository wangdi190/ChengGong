// SelPie.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "SelPie.h"
#include "dbapi.h"
#include "userapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CSelPie dialog


CSelPie::CSelPie(CWnd* pParent /*=NULL*/)
	: CDialog(CSelPie::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelPie)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	def=NULL;
	num=0;
}

CSelPie::~CSelPie()
{
	if(def!=NULL) delete def;
}


void CSelPie::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelPie)
	DDX_Control(pDX, IDC_LIST1, m_lst);
	DDX_Control(pDX, IDC_COMBO1, m_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelPie, CDialog)
	//{{AFX_MSG_MAP(CSelPie)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelPie message handlers

BOOL CSelPie::OnInitDialog() 
{
	int i;
	CDialog::OnInitDialog();
	dbok=LSI_InitNTDbi();
	if(!dbok){
		MessageBox("数据库平台未启动","错误",MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	}
	LSI_CheckUser("sa","");
	GetData();
	SetToList();
	i=GetIndex(ad.did);
	m_lst.SetCurSel(i);
	m_type.SetCurSel(ad.dtype);
	return TRUE; 
}


char *dbnm[]={"Line","DCLine","Gen"};
void CSelPie::GetData()
{
	int i,j;
	DWORD idi;
	MEMTABLE *mtb;
	num=0;
	if(ad.dtype<0||ad.dtype>2) return;
	if(!LSI_GetTableID(ad.dbname,dbnm[ad.dtype],idi)) return;
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
	switch(ad.dtype)
	{
	case 0: //交流输电线
		line=(visualpw_Line *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=line[i].NU;
			strcpy(def[i].name,line[i].Name);
		}
		break;
	case 1: //直流输电线
		dcl=(visualpw_DCLine *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=dcl[i].NU;
			strcpy(def[i].name,dcl[i].Name);
		}
		break;
	case 2:	//发电机 
		gen=(visualpw_Gen *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=gen[i].NU;
			strcpy(def[i].name,gen[i].Name);
		}
		break;
	}
}

void CSelPie::SetToList()
{
	int i;
	char p[100];
	m_lst.ResetContent();
	for(i=0;i<num;i++){
		sprintf(p,"id=%d :  %s",def[i].id,def[i].name);
		m_lst.AddString(p);
	}
}

int CSelPie::GetIndex(int id)
{
	int i;
	for(i=0;i<num;i++){
		if(id==def[i].id) return i;
	}
	return -1;
}

void CSelPie::OnSelchangeCombo1() 
{
	int i;
	i=m_type.GetCurSel();
	ad.dtype=i;
	GetData();
	SetToList();
	m_lst.SetCurSel(0);
}

void CSelPie::OnOK() 
{
	int i;
	i=m_lst.GetCurSel();
	if(i>=0&&i<num){
		ad.did=def[i].id;
		strcpy(ad.name,def[i].name);
	}
	CDialog::OnOK();
}
