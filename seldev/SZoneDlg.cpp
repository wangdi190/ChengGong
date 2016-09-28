// SZoneDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "SZoneDlg.h"
#include "dbapi.h"
#include "userapi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SZoneDlg dialog


SZoneDlg::SZoneDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SZoneDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SZoneDlg)
	//}}AFX_DATA_INIT
	def=NULL;
	num=0;
}

SZoneDlg::~SZoneDlg()
{
	if(def!=NULL) delete def;
}

void SZoneDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SZoneDlg)
	DDX_Control(pDX, IDC_COMBO1, m_cb);
	DDX_Control(pDX, IDC_NAME, m_name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SZoneDlg, CDialog)
	//{{AFX_MSG_MAP(SZoneDlg)
	ON_CBN_SELCHANGE(IDC_COMBO1, OnSelchangeCombo1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SZoneDlg message handlers

BOOL SZoneDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	dbok=LSI_InitNTDbi();
	if(!dbok){
		MessageBox("数据库平台未启动","错误",MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	}
	ad.dtype=ad.dtype>2 ? 0:ad.dtype;
	m_cb.SetCurSel(ad.dtype);
	GetData();
	SetToLst();
	m_name.SetCurSel(GetIndex(ad.did));
	return TRUE; 
}


//返回数据
void SZoneDlg::GetData()
{
	switch(ad.dtype)
	{
	case 0:case 1: //区域的发电和负荷
		GetZoneData();
		break;
	case 2:			//断面
		GetDmData();
		break;
	}
}

//返回数据
void SZoneDlg::GetZoneData()
{
	int i,j;
	DWORD idi;
	visualpw_Zone *zn;
	MEMTABLE *mtb;
	num=0;
	if(!LSI_GetTableID("visualpw","Zone",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	num=mtb->userec;
	if(def!=NULL) delete def;
	def=NULL;
	if(num==0) return;

	def=new DEVDEF[num];
	if(def==NULL){
		num=0;
		return;
	}
	zn=(visualpw_Zone*)mtb->data;
	for(i=0;i<num;i++)
	{
		strcpy(def[i].name,zn[i].Name);
		def[i].id=zn[i].NU;
	}
}

void SZoneDlg::GetDmData()
{
	int i,j;
	DWORD idi;
	common_PreDefSF *dm;
	MEMTABLE *mtb;
	num=0;
	if(!LSI_GetTableID("common","PreDefSF",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	num=mtb->userec;
	if(def!=NULL) delete def;
	def=NULL;
	if(num==0) return;

	def=new DEVDEF[num];
	if(def==NULL){
		num=0;
		return;
	}
	dm=(common_PreDefSF*)mtb->data;
	for(i=0;i<num;i++)
	{
		strcpy(def[i].name,dm[i].Name);
		def[i].id=dm[i].ID;
	}
}


//返回序号
int SZoneDlg::GetIndex(int id)
{
	int i;
	for(i=0;i<num;i++){
		if(id==(int)def[i].id) return i;
	}
	return 0;
}

//设置到列表框
void SZoneDlg::SetToLst()
{
	int i;
	char p[128];
	m_name.ResetContent();
	for(i=0;i<num;i++){
		sprintf(p,"ID:%d  %s",def[i].id,def[i].name);
		m_name.AddString(p);
	}
}

void SZoneDlg::OnOK() 
{
	int i;
	i=m_name.GetCurSel();
	if(i==LB_ERR){
		strcpy(ad.name,"无效");
		ad.did=-1;
	}else{
		strcpy(ad.name,def[i].name);
		ad.did=def[i].id;
	}
	CDialog::OnOK();
}

void SZoneDlg::OnSelchangeCombo1() 
{
	int i;
	i=m_cb.GetCurSel();
	if(i==CB_ERR)  return;
	ad.dtype=i;
	GetData();
	SetToLst();
}
