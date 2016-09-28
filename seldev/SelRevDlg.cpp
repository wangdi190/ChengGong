// SelRevDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "SelRevDlg.h"
#include "visualdb.h"
#include "userapi.h"
#include "dbapi.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SelRevDlg dialog


SelRevDlg::SelRevDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelRevDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelRevDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	def=NULL;
	num=0;
}

SelRevDlg::~SelRevDlg()
{
	if(def!=NULL) delete def;
}

void SelRevDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelRevDlg)
	DDX_Control(pDX, IDC_LIST1, m_lst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelRevDlg, CDialog)
	//{{AFX_MSG_MAP(SelRevDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelRevDlg message handlers

BOOL SelRevDlg::OnInitDialog() 
{
	bool dbok;
	CDialog::OnInitDialog();
	dbok=LSI_InitNTDbi();
	if(!dbok){
		MessageBox("数据库平台未启动","错误",MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	}
	GetData();
	SetToLst();
	m_lst.SetCurSel(GetIndex(ad.id));
	
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//返回数据
void SelRevDlg::GetData()
{
	/*int i,j;
	DWORD idi;
	waterele_reservoir *wr;
	MEMTABLE *mtb;
	num=0;
	if(!LSI_GetTableID("waterele","reservoir",idi)) return;
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
	wr=(waterele_reservoir*)mtb->data;
	for(i=0;i<num;i++)
	{
		strcpy(def[i].name,wr[i].Name);
		def[i].id=wr[i].ID;
	}*/
}

void SelRevDlg::SetToLst()
{
	int i;
	char p[100];
	m_lst.ResetContent();
	for(i=0;i<num;i++)
	{
		sprintf(p,"%d:%s",def[i].id,def[i].name);
		m_lst.AddString(p);
	}
}

int SelRevDlg::GetIndex(int id)
{
	int i;
	for(i=0;i<num;i++)
	{
		if(id==def[i].id) return i;
	}
	return -1;
}

void SelRevDlg::OnOK() 
{
	int i;
	i=m_lst.GetCurSel();
	if(i==LB_ERR){
		MessageBox("必须选择一个水库！","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	ad.id=def[i].id;	
	strcpy(ad.name,def[i].name);
	CDialog::OnOK();
}
