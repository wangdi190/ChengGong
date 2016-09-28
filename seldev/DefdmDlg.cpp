// DefdmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "seldev.h"
#include "DefdmDlg.h"
#include "userapi.h"
#include "dbapi.h"
#include "pysel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DefdmDlg dialog


DefdmDlg::DefdmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DefdmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DefdmDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	line=NULL;			//线路
	dcline=NULL;		//直流线路
	tfm1=NULL;
	tfm2=NULL;
	gen=NULL;
	deft=NULL;
	lsum=0;
	dlsum=0;
	ltype=0;
	curdm=0;
	t1sum=0;
	t2sum=0;
	gsum=0;
	numt=0;
}

DefdmDlg::~DefdmDlg()
{
	if(line!=NULL)   delete line;			//线路
	if(dcline!=NULL) delete dcline;		//直流线路
	if(tfm1!=NULL)   delete tfm1;
	if(tfm2!=NULL)   delete tfm2;
	if(gen!=NULL)    delete gen;
	if(deft!=NULL)   delete deft;
}

void DefdmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DefdmDlg)
	DDX_Control(pDX, IDC_ACDC, m_acdc);
	DDX_Control(pDX, IDC_DEFINED, m_defined);
	DDX_Control(pDX, IDC_LINEID, m_lineid);
	DDX_Control(pDX, IDC_LINE, m_line);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DefdmDlg, CDialog)
	//{{AFX_MSG_MAP(DefdmDlg)
	ON_CBN_SELCHANGE(IDC_ACDC, OnSelchangeAcdc)
	ON_BN_CLICKED(IDC_ADDDM, OnAdddm)
	ON_BN_CLICKED(IDC_MODIDM, OnModidm)
	ON_LBN_DBLCLK(IDC_DEFINED, OnDblclkDefined)
	ON_BN_CLICKED(IDC_DELETEDM, OnDeletedm)
	ON_BN_CLICKED(IDC_DELETELINE, OnDeleteline)
	ON_LBN_DBLCLK(IDC_LINE, OnDblclkLine)
	ON_LBN_SELCHANGE(IDC_DEFINED, OnSelchangeDefined)
	ON_BN_CLICKED(IDC_ADDYS, OnAddys)
	ON_BN_CLICKED(IDC_SUBYS, OnSubys)
	ON_EN_CHANGE(IDC_PYJS, OnChangePyjs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DefdmDlg message handlers

BOOL DefdmDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	if(!LSI_InitNTDbi())
	{
		MessageBox("数据库平台初始化错误!","错误",MB_OK|MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	};
	LSI_CheckUser("sa","");
	m_acdc.SetCurSel(0);
	ReadLine();
	ReadDCLine();
	ReadTfm2();
	ReadGen();
	ReadPredef();
	GetDev();
	SetLineList();
	SetDmList();
	SetEdit();
	SetLineID();
	return TRUE;  
}

//读取交流线路
void DefdmDlg::ReadLine()
{
	DWORD idi;
	visualpw_Line *ln;
	MEMTABLE *mtb;
	int i,j;
	lsum=0;	
	if(!LSI_GetTableID("visualpw","Line",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	lsum=mtb->userec;
	if(line!=NULL) delete line;
	line=new DEVDEF[lsum+10];
	if(line==NULL)
	{
		lsum=0;
		return;
	}
	ln=(visualpw_Line*)mtb->data;
	for(i=0;i<lsum;i++)
	{
		line[i].id=ln[i].NU;
		strcpy(line[i].name,ln[i].Name);
		line[i].stno=ln[i].Stationf;
	}
}


//读取交流线路
void DefdmDlg::ReadTfm2()
{
	DWORD idi;
	visualpw_Tfm2 *tf;
	MEMTABLE *mtb;
	int i,j;
	t2sum=0;	
	if(!LSI_GetTableID("visualpw","Tfm2",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	t2sum=mtb->userec;
	if(tfm2!=NULL) delete tfm2;
	tfm2=new DEVDEF[t2sum+10];
	if(tfm2==NULL)
	{
		t2sum=0;
		return;
	}
	tf=(visualpw_Tfm2*)mtb->data;
	for(i=0;i<t2sum;i++)
	{
		tfm2[i].id=tf[i].NU;
		strcpy(tfm2[i].name,tf[i].Name);
		//memcpy(tfm2[i].name,tf[i].Name,24);
		tfm2[i].stno=tf[i].Station;
	}
}


//读取发电机
void DefdmDlg::ReadGen()
{
	DWORD idi;
	visualpw_Gen *tg;
	MEMTABLE *mtb;
	int i,j;
	gsum=0;	
	if(!LSI_GetTableID("visualpw","Gen",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	gsum=mtb->userec;
	if(gen!=NULL) delete gen;
	gen=new DEVDEF[gsum+10];
	if(gen==NULL)
	{
		gsum=0;
		return;
	}
	tg=(visualpw_Gen*)mtb->data;
	for(i=0;i<gsum;i++)
	{
		gen[i].id=tg[i].NU;
		strcpy(gen[i].name,tg[i].Name);
		//memcpy(gen[i].name,tg[i].Name,24);
		gen[i].stno=tg[i].Station;
	}
}

//读取交流线路
void DefdmDlg::ReadDCLine()
{
	DWORD idi;
	visualpw_DCLine *ln;
	MEMTABLE *mtb;
	int i,j;
	dlsum=0;	
	if(!LSI_GetTableID("visualpw","DCLine",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	if(mtb->userec<=0) return;
	dlsum=mtb->userec;
	if(dcline!=NULL) delete dcline;
	dcline=new DEVDEF[dlsum+10];
	if(dcline==NULL)
	{
		dlsum=0;
		return;
	}
	ln=(visualpw_DCLine*)mtb->data;
	for(i=0;i<dlsum;i++)
	{
		dcline[i].id=ln[i].NU;
		strcpy(dcline[i].name,ln[i].Name);
		dcline[i].stno=ln[i].Stationf;
	}
	
}


//读取预定义断面数据
void DefdmDlg::ReadPredef()
{
	DWORD idi;
	common_PreDefSF *pre;
	MEMTABLE *mtb;
	int i,j;
	dmsum=0;	
	if(!LSI_GetTableID("common","PreDefSF",idi)) return;
	j=LOWORD(idi);
	mtb=(MEMTABLE *)LSI_GetTableAdd(j);
	if(mtb==NULL) return;
	if(mtb->userec<=0) return;
	dmsum=mtb->userec;
	dmsum=dmsum>128 ? 128:dmsum;
	pre=(common_PreDefSF*)mtb->data;
	for(i=0;i<dmsum;i++)
	{
		dm[i]=pre[i];
	}
}


void DefdmDlg::GetDev()
{
	int i;
	selnum=0;
	def=NULL;
	switch(ltype)
	{
	case 0:
		selnum=lsum;
		def=line;
		break;
	case 1:
		selnum=dlsum;
		def=dcline;
		break;
	case 2:
		selnum=t2sum;
		def=tfm2;
		break;
	case 3:
		selnum=gsum;
		def=gen;
		break;
	default:
		return;
	}
	if(selnum==NULL) return;
	deft=new DEVDEF[selnum];
	if(deft==NULL) return;
	numt=selnum;
	for(i=0;i<numt;i++) deft[i]=def[i];
	
}
//设置线路
void DefdmDlg::SetLineList()
{

	int i;
	char p[100];
	m_line.ResetContent();
	for(i=0;i<numt;i++)
	{
		sprintf(p,"ID:%06d [%s]",deft[i].id,deft[i].name);
		m_line.AddString(p);
	}
}

//设置断面
void DefdmDlg::SetDmList()
{
	int i;
	m_defined.ResetContent();
	for(i=0;i<dmsum;i++)
	{
		m_defined.AddString(dm[i].Name);
	}
	m_defined.SetCurSel(curdm);
}
//设置编辑
void DefdmDlg::SetEdit()
{
	char p[100];
	if(curdm>=dmsum) return;
	SetDlgItemText(IDC_DMNAME,dm[curdm].Name);
	sprintf(p,"%2.2f",dm[curdm].Vmax);
	SetDlgItemText(IDC_RL,p);
	sprintf(p,"%2.2f",dm[curdm].Par*100);
	SetDlgItemText(IDC_PAR,p);
	SetDlgItemText(IDC_MSG,dm[curdm].msg);
}
//设置断面定义的线路
void DefdmDlg::SetLineID()
{
	int i,n;
	char p[100],name[32];
	DMLS *ls;
	char *lp;
	m_lineid.ResetContent();
	if(curdm>=dmsum) return;
	lp=dm[curdm].DevID+2;
	ls=(DMLS*)lp;
	n=dm[curdm].Nline;
	for(i=0;i<n;i++)
	{
		GetLineName(name,ls[i].type,ls[i].id);
		sprintf(p,"[%s] ID:%06d [%s]",ls[i].ys==0 ? "+":"-",ls[i].id,name);
		m_lineid.AddString(p);
	}
}

void DefdmDlg::OnSelchangeAcdc() 
{
	ltype=m_acdc.GetCurSel();
	if(deft!=NULL) delete deft;
	deft=NULL;
	numt=0;
	GetDev();
	SetLineList();
}

//添加一个断面
void DefdmDlg::OnAdddm() 
{
	char p[100];
	common_PreDefSF tmp;
	if(dmsum>=128)
	{
		MessageBox("断面定义已满(最大128),不能添加新断面","错误",MB_OK|MB_ICONSTOP);
		return;
	};
	
	memset(&tmp,0,sizeof(common_PreDefSF));
	GetDlgItemText(IDC_DMNAME,tmp.Name,44);
	if(IsHaveDm(tmp.Name))
	{
		MessageBox("同样名字的断面已定义！","错误",MB_OK|MB_ICONSTOP);
		return;
	};
	GetDlgItemText(IDC_RL,p,16);
	tmp.Vmax=(float)atof(p);
	GetDlgItemText(IDC_PAR,p,16);
	tmp.Par=(float)(atof(p)/100);
	if(strlen(tmp.Name)==0||tmp.Vmax==0||tmp.Par==0)
	{
		MessageBox("断面名字为空或参数错！","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	tmp.ID=GetAID();
	//添加到新的
	dm[dmsum]=tmp;
	dmsum++;
	SetDmList();
}

bool DefdmDlg::IsHaveDm(char *name)
{
	int i;
	for(i=0;i<dmsum;i++)
	{
		if(strcmp(name,dm[i].Name)==0) 	return true;
	}
	return false;
}


bool DefdmDlg::IsHaveDm1(char *name,int jlh)
{
	int i;
	for(i=0;i<dmsum;i++)
	{
		if(jlh==i) continue;
		if(strcmp(name,dm[i].Name)==0) return true;
	}
	return false;
}


bool DefdmDlg::IsSaveID(int id)
{
	int i;
	for(i=0;i<dmsum;i++)
	{
		if(id==(int)dm[i].ID) return true;

	}
	return false;
}

int DefdmDlg::GetAID()
{
	int i;
	for(i=0;i<dmsum+1;i++)
	{
		if(!IsSaveID(i)) return i;
	}
	return dmsum+100;
}

//修改断面
void DefdmDlg::OnModidm() 
{
	int i;
	char p[100];
	common_PreDefSF tmp;
	i=m_defined.GetCurSel();
	if(i==LB_ERR) 
	{
		MessageBox("选择一个断面才能修改！","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	memset(&tmp,0,sizeof(common_PreDefSF));
	GetDlgItemText(IDC_DMNAME,tmp.Name,44);
	if(IsHaveDm1(tmp.Name,i))
	{
		MessageBox("不能修改为已存在的名字！","错误",MB_OK|MB_ICONSTOP);
		return;
	};
	GetDlgItemText(IDC_RL,p,16);
	tmp.Vmax=(float)atof(p);
	GetDlgItemText(IDC_PAR,p,16);
	tmp.Par=(float)(atof(p)/100);
	if(strlen(tmp.Name)==0||tmp.Vmax==0||tmp.Par==0)
	{
		MessageBox("断面名字为空或参数错！","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	curdm=i;
	dm[i].Par=tmp.Par;
	strcpy(dm[i].Name,tmp.Name);
	dm[i].Vmax=tmp.Vmax;

	GetDlgItemText(IDC_MSG,dm[i].msg,44);

	SetDmList();

}

//双击预定义断面
void DefdmDlg::OnDblclkDefined() 
{
	int i;
	i=m_defined.GetCurSel();
	if(i==LB_ERR) 	return;
	curdm=i;
	SetEdit();
	SetLineID();	
}


//删除一个断面
void DefdmDlg::OnDeletedm() 
{
	int i,j;
	j=m_defined.GetCurSel();
	if(j==LB_ERR) return;
	if(dmsum<=0) return;
	for(i=j;i<dmsum-1;i++)
	{
		dm[i]=dm[i+1];
	}
	dmsum--;
	if(curdm>=dmsum)
	{
		curdm=0;
	}
	SetEdit();
	SetLineID();
	m_defined.SetCurSel(curdm);
}

//删除一个线路
void DefdmDlg::OnDeleteline() 
{
	int i,n,j;
	DMLS *ls;
	char *lp;
	j=m_lineid.GetCurSel();
	if(j==LB_ERR)   return;
	if(curdm>=dmsum) return;
	lp=dm[curdm].DevID+2;
	ls=(DMLS*)lp;
	n=dm[curdm].Nline;
	if(n==0) return;
	for(i=j;i<n-1;i++)
	{
		ls[i]=ls[i+1];
	}
	n--;
	dm[curdm].Nline=n;
	SetLineID();
}

//双击添加线路
void DefdmDlg::OnDblclkLine() 
{
	int n,j;
	DMLS *ls,ld;
	char *lp;
	j=m_line.GetCurSel();
	if(j==LB_ERR)   return;
	if(curdm>=dmsum) return;
	if(dm[curdm].Nline>=26)
	{
		MessageBox("一个断面最大支持26条线路，已满，不能添加!","错误",MB_OK);
		return;
	}
	ld.type=(BYTE)m_acdc.GetCurSel();
	ld.id=deft[j].id;
	lp=dm[curdm].DevID+2;
	ls=(DMLS*)lp;
	n=dm[curdm].Nline;
	ls[n]=ld;
	ls[n].ys=0;
	n++;
	dm[curdm].Nline=n;
	SetLineID();
}

//保存退出
void DefdmDlg::OnOK() 
{
	LSI_UpdateAll("common.PreDefSF",dm,dmsum);
	CDialog::OnOK();
}


void DefdmDlg::GetLineName(char *name,int type,int id)
{
	int i;
	name[0]=0;
	switch(type)
	{
	case 0:
		for(i=0;i<lsum;i++)
		{
			if(id==line[i].id)
			{
				strcpy(name,line[i].name);
				break;
			}
		}
		break;
	case 1:
		for(i=0;i<dlsum;i++)
		{
			if(id==dcline[i].id)
			{
				strcpy(name,dcline[i].name);
				break;
			}
		}
		break;
	case 2://三绕变
		for(i=0;i<t2sum;i++)
		{
			if(id==tfm2[i].id)
			{
				strcpy(name,tfm2[i].name);
				break;
			}
		}
		break;
	case 3: //发电机
		for(i=0;i<gsum;i++)
		{
			if(id==gen[i].id)
			{
				strcpy(name,gen[i].name);
				break;
			}
		}

		break;
	}
}



void DefdmDlg::OnSelchangeDefined() 
{
	int i;
	i=m_defined.GetCurSel();
	if(i==LB_ERR) 	return;
	curdm=i;
	SetEdit();
	SetLineID();
}

void DefdmDlg::OnAddys() 
{
	int n,j;
	DMLS *ls;
	char *lp;
	j=m_lineid.GetCurSel();
	if(j==LB_ERR)   return;
	if(curdm>=dmsum) return;
	lp=dm[curdm].DevID+2;
	ls=(DMLS*)lp;
	n=dm[curdm].Nline;
	if(n==0) return;
	ls[j].ys=0;
	SetLineID();
	
}

void DefdmDlg::OnSubys() 
{
	int n,j;
	DMLS *ls;
	char *lp;
	j=m_lineid.GetCurSel();
	if(j==LB_ERR)   return;
	if(curdm>=dmsum) return;
	lp=dm[curdm].DevID+2;
	ls=(DMLS*)lp;
	n=dm[curdm].Nline;
	if(n==0) return;
	ls[j].ys=1;
	SetLineID();
}

//设备按名字排序
void DefdmDlg::OrderDevByName()
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

void DefdmDlg::OnChangePyjs() 
{
	int i,n;
	PySel psl;
	char str[16];
	if(selnum==0) return;
	GetDlgItemText(IDC_PYJS,str,10);
	if(deft!=NULL) delete deft;
	deft=new DEVDEF[selnum];
	n=0;
	for(i=0;i<selnum;i++)
	{
		if(psl.IsThisPy(str,def[i].name))
		{
			deft[n]=def[i];
			n++;
		}
	}
	numt=n;
	OrderDevByName();
	SetLineList();
}
