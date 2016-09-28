// SelDVDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "SelDVDlg.h"
#include "dbapi.h"
#include "userapi.h"
#include "pysel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
//设备访问类型表：
/*
0="PT" 1="发电机" 2="开关,刀闸",3="负荷",4="电容",5="电抗",6="接地",7="二绕组变压器"
8="三绕组变压器",9="静态无功补偿器",10="逆变、变流器"
33=母线 34=交流 35=直流
*/
char *devtbl[]={"PT",		//PT
				"Gen",		//发电机
				"Switch",   //开关
				"Load",		//负荷
				"Shunt",	//电容
				"Sreact",	//电抗
				"GND",		//接地
				"Tfm1",		//2绕组变压器
			    "Tfm2",		//3绕组变压器
			    "SVC",		//静态无功补偿装置
				"CVT",		//逆变器
				"Bus",		//母线
			    "Line",		//交流
			    "DCLine",	//直流
				}; 


char *dvnm[]={"PT","发电机","开关,刀闸","负荷","电容","电抗","接地","二绕组变压器",
"三绕组变压器","静态无功补偿器","逆变、变流器","母线","交流","直流"};
/////////////////////////////////////////////////////////////////////////////
// SelDVDlg dialog

SelDVDlg::SelDVDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelDVDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelDVDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	num=0;
	stsum=0;
	numt=0;
	font.CreateFont(30,15,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"楷体" );
	def=NULL;
	st=NULL;
	deft=NULL;
	dbok=false;
}

SelDVDlg::~SelDVDlg()
{

	if(def!=NULL)	delete def;
	if(st!=NULL)	delete st;
	if(deft!=NULL)	delete deft;
	font.DeleteObject();
}


void SelDVDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelDVDlg)
	DDX_Control(pDX, IDC_LIST2, m_lst2);
	DDX_Control(pDX, IDC_LIST1, m_lst);
	DDX_Control(pDX, IDC_DTYPE, m_dtype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelDVDlg, CDialog)
	//{{AFX_MSG_MAP(SelDVDlg)
	ON_BN_CLICKED(IDC_SHOWALL, OnShowall)
	ON_LBN_SELCHANGE(IDC_LIST2, OnSelchangeList2)
	ON_EN_CHANGE(IDC_PYJS, OnChangePyjs)
	ON_NOTIFY(LVN_COLUMNCLICK, IDC_LIST1, OnColumnclickList1)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelDVDlg message handlers

BOOL SelDVDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	dbok=LSI_InitNTDbi();
	if(!dbok){
		MessageBox("数据库平台未启动","错误",MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	}
	LSI_CheckUser("sa","");
	DWORD sty=m_lst.GetExtendedStyle();
	m_lst.SetExtendedStyle(sty|LVS_EX_GRIDLINES|LVS_EX_FLATSB|LVS_EX_FULLROWSELECT);
	m_lst.SetBkColor(0xf0ffff);
	m_lst.SetTextBkColor(0xf0ffff);
	m_lst.SetTextColor(0);
	m_lst.InsertColumn(0,"设备编号(ID)",LVCFMT_LEFT,100,0);
	m_lst.InsertColumn(1,"  设备名称",LVCFMT_LEFT,220,0);

	ti=sd.dtype>=33 ? sd.dtype-22:sd.dtype;
	if(ti>13||ti<0){
		MessageBox("设备类型不存在！");	
		return false;
	}
	m_dtype.SetFont(&font);
	GetStation();
	SetToSTLst();
	GetData();
	SetDlgItemInt(IDC_NU,sd.did);
	SetDlgItemText(IDC_NAME,sd.name);
	OnShowall();
	return TRUE; 
}


void SelDVDlg::GetStation()
{
	DWORD idi;
	MEMTABLE *mtb;
	visualpw_Station *ss;
	int i,j;
	if(!LSI_GetTableID(sd.dbname,"Station",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	stsum=mtb->userec;
	if(st!=NULL) delete st;
	st=new STATION[stsum];
	if(st==NULL)
	{
		stsum=0;
		return;
	}
	ss=(visualpw_Station*)mtb->data;
	for(i=0;i<stsum;i++)
	{
		st[i].id=ss[i].NU;
		strcpy(st[i].name,ss[i].Name);
	}
	OrderStationByName();
}

//读取数据
void SelDVDlg::GetData()
{
	DWORD idi;
	MEMTABLE *mtb;
	int t,i,j;
	char sql[256];
	num=0;
	t=ti;
	if(t>13||t<0) return;
	
	if(!LSI_GetTableID(sd.dbname,devtbl[t],idi)) return;
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
	case 0: //PT
		pt=(visualpw_PT *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=pt[i].NU;
			def[i].stno=pt[i].Station;
			strcpy(def[i].name,pt[i].Name);
		}
		break;
	case 1: //发电机 
		gen=(visualpw_Gen *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=gen[i].NU;
			def[i].stno=gen[i].Station;
			strcpy(def[i].name,gen[i].Name);
		}
		break;
	case 2:	//开关，刀闸
		swt=(visualpw_Switch *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=swt[i].NU;
			def[i].stno=swt[i].Station;
			strcpy(def[i].name,swt[i].Name);
		}
		break;
	case 3: //负荷
		load=(visualpw_Load *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=load[i].NU;
			def[i].stno=load[i].Station;
			strcpy(def[i].name,load[i].Name);
		}
		break;
	case 4:  //电容
		sht=(visualpw_Shunt *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=sht[i].NU;
			def[i].stno=sht[i].Station;
			strcpy(def[i].name,sht[i].Name);
		}
		break;
	case 5:  //电抗
		srt=(visualpw_Sreact *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=srt[i].NU;
			def[i].stno=srt[i].Station;
			strcpy(def[i].name,srt[i].Name);
		}
		break;
	case 6:  //接地
		gnd=(visualpw_GND *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=gnd[i].NU;
			def[i].stno=gnd[i].Station;
			strcpy(def[i].name,gnd[i].Name);
		}
		break;

	case 7: //2绕变
		tfm1=(visualpw_Tfm1 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm1[i].NU;
			def[i].stno=tfm1[i].Station;
			strcpy(def[i].name,tfm1[i].Name);
		}
		break;
	case 8: //三绕变
		tfm2=(visualpw_Tfm2 *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=tfm2[i].NU;
			def[i].stno=tfm2[i].Station;
			strcpy(def[i].name,tfm2[i].Name);
		}
		break;
	case 9: //SVC
		svc=(visualpw_SVC *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=svc[i].NU;
			def[i].stno=svc[i].Station;
			strcpy(def[i].name,svc[i].Name);
		}
		break;
	case 10://逆变器
		cvt=(visualpw_CVT *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=cvt[i].NU;
			def[i].stno=cvt[i].Station;
			strcpy(def[i].name,cvt[i].Name);
		}
		break;
	case 11: //母线
		bus=(visualpw_Bus *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=bus[i].NU;
			def[i].stno=bus[i].Station;
			strcpy(def[i].name,bus[i].Name);
		}
		break;
	case 12: //交流输电线
		line=(visualpw_Line *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=line[i].NU;
			def[i].stno=line[i].Stationf;
			strcpy(def[i].name,line[i].Name);
		}
		break;
	case 13: //直流输电线
		dcl=(visualpw_DCLine *)mtb->data;
		for(i=0;i<num;i++){
			def[i].id=dcl[i].NU;
			def[i].stno=dcl[i].Stationf;
			strcpy(def[i].name,dcl[i].Name);
		}
		break;
	}
	sprintf(sql,"选择的设备类型:%s",dvnm[t]);
	m_dtype.SetWindowText(sql);
}

//设置到列表框
void SelDVDlg::SetToLst()
{
	int i;
	char p[128];
	m_lst.DeleteAllItems( );
	
	for(i=0;i<numt;i++){
		sprintf(p,"%d",deft[i].id);
		m_lst.InsertItem(i,p);
		m_lst.SetItemText(i,1,deft[i].name);
	}
	i=GetItemIndex(sd.did);
	if(i>=0){
		m_lst.SetHotItem(i);
		m_lst.SetSelectionMark(i);
	}
}

//设置到列表框
void SelDVDlg::SetToSTLst()
{
	int i;
	m_lst2.ResetContent();
	for(i=0;i<stsum;i++){
		m_lst2.AddString(st[i].name);
	}
}

void SelDVDlg::OnOK() 
{
	int i=m_lst.GetSelectionMark();
	if(i==-1){
		MessageBox("未选择一个设备，不能保存！\n请选择取消退出。","错误",MB_ICONSTOP);
		return;
	}
	strcpy(sd.name,deft[i].name);
	sd.did=deft[i].id;
	CDialog::OnOK();
}

int SelDVDlg::GetItemIndex(int id)
{
	int i;
	for(i=0;i<numt;i++)
	{
		if(id==deft[i].id) return i;
	}
	return -1;
}


//全部显示
void SelDVDlg::OnShowall() 
{
	numt=num;
	if(deft!=NULL) delete deft;
	deft=new DEVDEF[numt];
	memcpy(deft,def,numt*sizeof(DEVDEF));
	SetToLst();
}

void SelDVDlg::OnSelchangeList2() 
{
	int i,j,m,n,stnu;
	m_lst.DeleteAllItems( );
	m=m_lst2.GetCurSel();
	if(m==LB_ERR) return;
	stnu=st[m].id;
	n=0;
	for(i=0;i<num;i++) if(def[i].stno==stnu) n++;
	if(n==0) return;
	numt=n;
	if(deft!=NULL) delete deft;
	deft=new DEVDEF[n];
	j=0;
	for(i=0;i<num;i++)
	{
		if(def[i].stno==stnu)
		{
			deft[j]=def[i];
			j++;
		}
	}
	OrderDevByName();
	SetToLst();
}

//站按名字排序
void SelDVDlg::OrderStationByName()
{
	int i,j;
	STATION tmp;
	for(i=0;i<stsum-1;i++)
	{
		for(j=i+1;j<stsum;j++)
		{
			if(strcmp(st[i].name,st[j].name)>0)
			{
				tmp=st[i];
				st[i]=st[j];
				st[j]=tmp;
			}

		}
	}
}


//设备按名字排序
void SelDVDlg::OrderDevByName()
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

//设备按ID排序
void SelDVDlg::OrderDevByID()
{
	int i,j;
	DEVDEF tmp;
	for(i=0;i<numt-1;i++)
	{
		for(j=i+1;j<numt;j++)
		{
			if(deft[i].id>deft[j].id)
			{
				tmp=deft[i];
				deft[i]=deft[j];
				deft[j]=tmp;
			}

		}
	}
}

void SelDVDlg::OnChangePyjs() 
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
	SetToLst();
	
}

void SelDVDlg::OnColumnclickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	i=pNMListView ->iSubItem; //按下的列
	switch(i)
	{
	case 0:
		OrderDevByID();
		break;
	case 1:
		OrderDevByName();
		break;
	}
	SetToLst();
	*pResult = 0;
}
