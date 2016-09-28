// GzTblDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "GzTblDlg.h"
#include "dbapi.h"
#include "math.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *title[]={"线路负载预警列表","发电机负载预警列表","变压器负载预警列表","预定义断面预警列表","母线电压预警列表","15分钟ACE平均值","特高压联网"};

//本程序用于监视预警详细信息
/////////////////////////////////////////////////////////////////////////////
// GzTblDlg dialog


GzTblDlg::GzTblDlg(CWnd* pParent /*=NULL*/)
	: CDialog(GzTblDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(GzTblDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	type=0;
	alarm=0;
	msg=NULL;
	msgsum=0;
	sound=1;
	alsum=0;
	showmode=0; 
}
GzTblDlg::~GzTblDlg()
{
	KillTimer(100);
	if(msg!=NULL) delete msg;
}

void GzTblDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GzTblDlg)
	DDX_Control(pDX, IDC_LIST1, m_lst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GzTblDlg, CDialog)
	//{{AFX_MSG_MAP(GzTblDlg)
	ON_WM_SIZE()
	ON_WM_TIMER()
	ON_WM_CTLCOLOR()
	ON_BN_CLICKED(IDC_RELOAD, OnReload)
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, OnItemchangedList1)
	ON_COMMAND(IDC_CHECKALL, OnCheckall)
	ON_COMMAND(IDC_UNCHECKALL, OnUncheckall)
	ON_BN_CLICKED(IDC_SOUND, OnSound)
	ON_COMMAND(IDC_SHOWALL, OnShowall)
	ON_COMMAND(IDC_SHOWALM, OnShowalm)
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GzTblDlg message handlers

HBRUSH GzTblDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_SCROLLBAR) {
   		pDC->SetBkMode(TRANSPARENT);
     	HBRUSH B = CreateSolidBrush(0xf0ffff); 
     	return (HBRUSH)B;
  	} 
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

BOOL GzTblDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	init=1;
	//检测数据库平台是否启动
	dbok=LSI_InitNTDbi();
	if(!dbok)
	{
		MessageBox("数据库平台未启动");	
		return false;
	}
	LSI_CheckUser("sa","");
	//获取实时库ID和实际共享地址
	GetTableID();
	GetRltDbAdd();
	GetFieldPos();
	SetHeader();
	SetList();
	SetWindowText(title[type]);
	SetTimer(100,2000,NULL);
	init=0;
	CheckDlgButton(IDC_SOUND,sound);
	return TRUE;
}

int GzTblDlg::GetPos(MEMTABLE *tbl)
{
	int i;
	for(i=0;i<tbl->tbl->n_fd;i++)
	{
		if(strcmp("ack",tbl->tbl->field[i].field.f_name)==0) return i;
	}
	return -1;
}

//返回告警"PreAlarm"域的位置
void GzTblDlg::GetFieldPos()
{
	fpos[0]=GetPos(mgen);
	fpos[1]=GetPos(mtf1);
	fpos[2]=GetPos(mtf2);
	fpos[3]=GetPos(mbus);
	fpos[4]=GetPos(mlin);
	fpos[5]=GetPos(mdlin);
	fpos[6]=GetPos(mpdf);
}

//设置表的域传输
void GzTblDlg::SetFieldTran(MEMTABLE *tbl,int jlh,int pos,int value)
{
	LSI_SetChangedField(tbl->id, jlh,pos);
}

//返回需要的表ID
void GzTblDlg::GetTableID()
{
	DWORD idi;
	if(LSI_GetTableID("visualpw","Gen",idi))		gid=LOWORD(idi);
	if(LSI_GetTableID("visualpw","Tfm1",idi))		t1id=LOWORD(idi);
	if(LSI_GetTableID("visualpw","Tfm2",idi))		t2id=LOWORD(idi);
	if(LSI_GetTableID("visualpw","Bus",idi))		bid=LOWORD(idi);
	if(LSI_GetTableID("visualpw","Line",idi))		lid=LOWORD(idi);
	if(LSI_GetTableID("visualpw","DCLine",idi))		dlid=LOWORD(idi);
	if(LSI_GetTableID("common","PreDefSF",idi))		pdid=LOWORD(idi);
	if(LSI_GetTableID("visualpw","SysAlarm",idi))	sid=LOWORD(idi);
}

void * GzTblDlg::GetTblAdd(int tid,int &n,MEMTABLE **mm)
{
	MEMTABLE *tbl;
	n=0;
	if(tid==-1) return NULL;
	tbl=(MEMTABLE *)LSI_GetTableAdd(tid);
	if(tbl==NULL) return NULL; 
	n=tbl->userec;//取得数据库中的记录数
	*mm=tbl;
	return tbl->data;
}
//返回数据库地址
void GzTblDlg::GetRltDbAdd()
{
	gen=(visualpw_Gen  *)GetTblAdd(gid,gsum,&mgen);
	tfm1=(visualpw_Tfm1  *)GetTblAdd(t1id,tsum1,&mtf1);
	tfm2=(visualpw_Tfm2  *)GetTblAdd(t2id,tsum2,&mtf2);
	bus=(visualpw_Bus  *)GetTblAdd(bid,bsum,&mbus);
	line=(visualpw_Line  *)GetTblAdd(lid,lsum,&mlin);
	dcline=(visualpw_DCLine  *)GetTblAdd(dlid,dlsum,&mdlin);
	pdf=(common_PreDefSF  *)GetTblAdd(pdid,pdsum,&mpdf);
	alm=(visualpw_SysAlarm  *)GetTblAdd(sid,asum,&malm);
}

void GzTblDlg::SetHeader()
{
	switch(type)
	{
	case 0: //线路
		m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB|LVS_EX_CHECKBOXES);
		m_lst.InsertColumn(0,"名  称",LVCFMT_LEFT,100,0);
		m_lst.InsertColumn(1,"负载率%",LVCFMT_RIGHT,60,0);
		m_lst.InsertColumn(2,"当前(MVA)",LVCFMT_RIGHT,80,0);
		m_lst.InsertColumn(3,"容量(MVA)",LVCFMT_RIGHT,80,0);
		m_lst.InsertColumn(4,"有功(MW)",LVCFMT_RIGHT,60,0);
		m_lst.InsertColumn(5,"无功(MVar)",LVCFMT_RIGHT,80,0);
		
		break;
	case 1: //发电机
		m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB|LVS_EX_CHECKBOXES);
		m_lst.InsertColumn(0,"名  称",LVCFMT_LEFT,100,0);
		m_lst.InsertColumn(1,"负载率%",LVCFMT_RIGHT,60,0);
		m_lst.InsertColumn(2,"容量(MW)",LVCFMT_RIGHT,80,0);
		m_lst.InsertColumn(3,"有功(MW)",LVCFMT_RIGHT,60,0);
		m_lst.InsertColumn(4,"无功(MVar)",LVCFMT_RIGHT,80,0);
		m_lst.InsertColumn(5,"检修(MW)",LVCFMT_RIGHT,60,0);
		break;
	case 2: //变压器
		m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB|LVS_EX_CHECKBOXES);
		m_lst.InsertColumn(0,"名  称",LVCFMT_LEFT,100,0);
		m_lst.InsertColumn(1,"负载率%",LVCFMT_RIGHT,60,0);
		m_lst.InsertColumn(2,"当前(MVA)",LVCFMT_RIGHT,80,0);
		m_lst.InsertColumn(3,"容量(MVA)",LVCFMT_RIGHT,80,0);
		m_lst.InsertColumn(4,"有功(MW)",LVCFMT_RIGHT,60,0);
		m_lst.InsertColumn(5,"无功(MVar)",LVCFMT_RIGHT,80,0);
		break;
	case 3: //断面
		m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB|LVS_EX_CHECKBOXES);
		m_lst.InsertColumn(0,"名  称",LVCFMT_LEFT,100,0);
		m_lst.InsertColumn(1,"负载率%",LVCFMT_RIGHT,60,0);
		m_lst.InsertColumn(2,"当前(MVA)",LVCFMT_RIGHT,80,0);
		m_lst.InsertColumn(3,"容量(MVA)",LVCFMT_RIGHT,80,0);
		break;
	case 4: //母线
		m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB|LVS_EX_CHECKBOXES);
		m_lst.InsertColumn(0,"名  称",LVCFMT_LEFT,140,0);
		m_lst.InsertColumn(1,"当前电压(KV)",LVCFMT_RIGHT,100,0);
		m_lst.InsertColumn(2,"允许范围(KV)",LVCFMT_RIGHT,120,0);
		m_lst.InsertColumn(3,"预警范围(KV)",LVCFMT_RIGHT,120,0);
		m_lst.InsertColumn(4,"裕度(KV)",LVCFMT_RIGHT,60,0);
		break;
	case 5: //ACE
		m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB|LVS_EX_CHECKBOXES);
		m_lst.InsertColumn(0,"确认",LVCFMT_LEFT,40,0);
		m_lst.InsertColumn(1,"当前值(MW)",LVCFMT_LEFT,80,0);
		m_lst.InsertColumn(2,"时间",LVCFMT_RIGHT,100,0);
		m_lst.InsertColumn(3,"越限",LVCFMT_RIGHT,60,0);
		break;
	case 6:
		m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB|LVS_EX_CHECKBOXES);
		m_lst.InsertColumn(0,"确认",LVCFMT_LEFT,40,0);
		m_lst.InsertColumn(1,"当前值(MW)",LVCFMT_LEFT,80,0);
		m_lst.InsertColumn(2,"时间",LVCFMT_RIGHT,100,0);
		m_lst.InsertColumn(3,"越限",LVCFMT_RIGHT,60,0);
		break;
	}
}

void GzTblDlg::SetList()
{
	GetRltDbAdd();
	switch(type)
	{
	case 0: //线路
		SetLine();
		break;
	case 1: //发电机
		SetGen();
		break;
	case 2: //变压器
		SetTran();
		break;
	case 3: //断面
		SetDM();
		break;
	case 4: //母线
		SetBus();
		break;
	case 5://ace
		SetACE();
		break;
	case 6:
		SetHvc();
		break;
	}
}


//定时刷新告警状态
void GzTblDlg::TimeRefreshAlarm()
{
	GetRltDbAdd();
	switch(type)
	{
	case 0: //线路
		SetLine1();
		break;
	case 1: //发电机
		SetGen1();
		break;
	case 2: //变压器
		SetTran1();
		break;
	case 3: //断面
		SetDM1();
		break;
	case 4: //母线
		SetBus1();
		break;
	case 5: //ACE
		SetAce1();
		break;
	case 6:
		SetHvc1();
		break;
	}
}


//设置HVC
void GzTblDlg::SetHvc()
{
	/*int i,n;
	CTime tm;
	char p[100];
	n=0;
	m_lst.DeleteAllItems();
   	for(i=0;i<hsum;i++)
	{
		if(hvc[i].Alarm==0&&showmode==0) continue;
		m_lst.InsertItem(n,"");
		sprintf(p,"%2.2f",hvc[i].Curval);
		m_lst.SetItemText(n,1,p);
		tm=hvc[i].datetm;
		sprintf(p,"%d-%d-%d %d:%d",tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute());
		m_lst.SetItemText(n,2,p);
		if(hvc[i].Alarm==1) m_lst.SetItemText(n,3,"越限");
		else m_lst.SetItemText(n,3,"正常");
		m_lst.SetCheck(n,hvc[i].Ack);
		m_lst.SetItemData(n,hvc[i].ID);
		n++;
	}*/
}

//设置Hvc
void GzTblDlg::SetHvc1()
{
	/*int i,gj,n;
	gj=0;
	n=0;
    //先看交流
	for(i=0;i<hsum;i++)
	{
		if(hvc[i].Ack==0&&hvc[i].Alarm==1)
		{
			gj=1;
		}
		if(hvc[i].Alarm==1) n++;
	}
	alarm=gj;
	if(alsum!=n)
	{
		SetHvc();
	}
	alsum=n;*/
}


//设置ACE
void GzTblDlg::SetACE()
{
	/*int i,n;
	CTime tm;
	char p[100];
	n=0;
	m_lst.DeleteAllItems();
   	for(i=0;i<esum;i++)
	{
		m_lst.InsertItem(n,"");
		sprintf(p,"%2.2f",ace[i].CurVal);
		m_lst.SetItemText(n,1,p);
		tm=ace[i].datatime;
		sprintf(p,"%d-%d-%d %d:%d",tm.GetYear(),tm.GetMonth(),tm.GetDay(),tm.GetHour(),tm.GetMinute());
		m_lst.SetItemText(n,2,p);
		if(ace[i].alarm==1) m_lst.SetItemText(n,3,"越限");
		else m_lst.SetItemText(n,3,"正常");
		m_lst.SetCheck(n,ace[i].ack);
		n++;
	}*/
}

//设置Ace
void GzTblDlg::SetAce1()
{
	/*int i,gj,n;
	gj=0;
	n=0;
    //先看交流
	for(i=0;i<esum;i++)
	{
		if(ace[i].ack==0&&ace[i].alarm==1) gj=1;
		n++;
	}
	alarm=gj;
	if(alsum!=n)
	{
		SetACE();
	}
	alsum=n;*/
}

//设置线路
void GzTblDlg::SetLine()
{
	int i,n;
	char p[100];
	double a,b;
	n=0;
	m_lst.DeleteAllItems();
    //先看交流
	for(i=0;i<lsum;i++)
	{
		if(line[i].alarm==0&&showmode==0) continue;
		b=sqrt(line[i].Pf*line[i].Pf+line[i].Qf*line[i].Qf);
		if(line[i].MaxP!=0) a=b/line[i].MaxP;
		else continue;
		m_lst.InsertItem(n,line[i].Name);
		sprintf(p,"%2.2f",a*100);
		m_lst.SetItemText(n,1,p);
		sprintf(p,"%2.2f",b);
		m_lst.SetItemText(n,2,p);
		sprintf(p,"%2.2f",line[i].MaxP);
		m_lst.SetItemText(n,3,p);
		sprintf(p,"%2.2f",line[i].Pf);
		m_lst.SetItemText(n,4,p);
		sprintf(p,"%2.2f",line[i].Qf);
		m_lst.SetItemText(n,5,p);
		m_lst.SetItemData(n,line[i].NU);
		m_lst.SetCheck(n,line[i].ack);
		n++;
	}
	//再看直流
	for(i=0;i<dlsum;i++)
	{
		if(dcline[i].alarm==0&&showmode==0) continue;
		b=sqrt(dcline[i].Pf*dcline[i].Pf+dcline[i].Qf*dcline[i].Qf);
		if(dcline[i].Maxp!=0) a=b/dcline[i].Maxp;
		else continue;
		m_lst.InsertItem(n,dcline[i].Name);
		sprintf(p,"%2.2f",a*100);
		m_lst.SetItemText(n,1,p);
		sprintf(p,"%2.2f",b);
		m_lst.SetItemText(n,2,p);
		sprintf(p,"%2.2f",dcline[i].Maxp);
		m_lst.SetItemText(n,3,p);

		sprintf(p,"%2.2f",dcline[i].Pf);
		m_lst.SetItemText(n,4,p);
		sprintf(p,"%2.2f",dcline[i].Qf);
		m_lst.SetItemText(n,5,p);

		m_lst.SetItemData(n,dcline[i].NU);
		m_lst.SetCheck(n,dcline[i].ack);
		n++;
	}
}

//设置线路
void GzTblDlg::SetLine1()
{
	int i,gj,n;
	gj=0;
	n=0;
    //先看交流
	for(i=0;i<lsum;i++)
	{
		if(line[i].alarm==0) continue;
		if(line[i].ack==0) gj=1;
		n++;
	}
	//再看直流
	for(i=0;i<dlsum;i++)
	{
		if(dcline[i].alarm==0) continue;
		if(dcline[i].ack==0) gj=1;	
		n++;
	}
	alarm=gj;
	if(alsum!=n)
	{
		alm[0].Alarm=1;
		alm[0].num=n;
		SetLine();
	}
	alsum=n;
}

//设置发电机
void GzTblDlg::SetGen()
{
	int i,n;
	char p[100];
	double a,b;
	n=0;
	m_lst.DeleteAllItems();
    //先看交流
	for(i=0;i<gsum;i++)
	{
		if(gen[i].alarm==0&&showmode==0) continue;
		b=gen[i].MaxP;
		if(b!=0) a=gen[i].P/b;
		else continue;
		m_lst.InsertItem(n,gen[i].Name);
		sprintf(p,"%2.2f",a*100);
		m_lst.SetItemText(n,1,p);
		sprintf(p,"%2.2f",gen[i].MaxP);
		m_lst.SetItemText(n,2,p);

		sprintf(p,"%2.2f",gen[i].P);
		m_lst.SetItemText(n,3,p);
		sprintf(p,"%2.2f",gen[i].Q);
		m_lst.SetItemText(n,4,p);
		sprintf(p,"%2.2f",gen[i].Pchk);
		m_lst.SetItemText(n,5,p);
				
		m_lst.SetItemData(n,gen[i].NU);
		m_lst.SetCheck(n,gen[i].ack);
	}
}

//设置发电机
void GzTblDlg::SetGen1()
{
	int i,gj,n;
	gj=0;
	n=0;
    //先看交流
	for(i=0;i<gsum;i++)
	{
		if(gen[i].alarm==0) continue;
		n++;
		if(gen[i].ack==0) gj=1;
	}
	alarm=gj;
	if(alsum!=n)
	{
		alm[1].Alarm=1;
		alm[1].num=n;	
		SetGen();
	}
	alsum=n;
}

//设置变压器
void GzTblDlg::SetTran()
{
	int i,n;
	char p[100];
	double a,b;
	n=0;
	m_lst.DeleteAllItems();
    //先看2绕变
	for(i=0;i<tsum1;i++)
	{
		if(tfm1[i].alarm==0&&showmode==0) continue;
		b=sqrt(tfm1[i].P*tfm1[i].P+tfm1[i].Q*tfm1[i].Q);
		if(tfm1[i].Pmax!=0) a=b/tfm1[i].Pmax;
		else continue;
		m_lst.InsertItem(n,tfm1[i].Name);
		sprintf(p,"%2.2f",a*100);
		m_lst.SetItemText(n,1,p);

		sprintf(p,"%2.2f",b);
		m_lst.SetItemText(n,2,p);

		sprintf(p,"%2.2f",tfm1[i].Pmax);
		m_lst.SetItemText(n,3,p);


		sprintf(p,"%2.2f",tfm1[i].P);
		m_lst.SetItemText(n,4,p);
		sprintf(p,"%2.2f",tfm1[i].Q);
		m_lst.SetItemText(n,5,p);
			
		m_lst.SetItemData(n,tfm1[i].NU);
		m_lst.SetCheck(n,tfm1[i].ack);
		n++;
	}
	//先看2绕变
	for(i=0;i<tsum2;i++)
	{
		if(tfm2[i].alarm==0&&showmode==0) continue;
		b=sqrt(tfm2[i].P*tfm2[i].P+tfm2[i].Q*tfm2[i].Q);
		if(tfm2[i].Pmax!=0) a=b/tfm2[i].Pmax;
		else continue;
		m_lst.InsertItem(n,tfm2[i].Name);
		sprintf(p,"%2.2f",a*100);
		m_lst.SetItemText(n,1,p);
		sprintf(p,"%2.2f",b);
		m_lst.SetItemText(n,2,p);
		sprintf(p,"%2.2f",tfm2[i].Pmax);
		m_lst.SetItemText(n,3,p);
		sprintf(p,"%2.2f",tfm2[i].P);
		m_lst.SetItemText(n,4,p);
		sprintf(p,"%2.2f",tfm2[i].Q);
		m_lst.SetItemText(n,5,p);
		m_lst.SetItemData(n,tfm2[i].NU);
		m_lst.SetCheck(n,tfm2[i].ack);
		n++;
	}
}

//设置变压器
void GzTblDlg::SetTran1()
{
	int i,gj,n;
	gj=0;
	n=0;
    //先看2绕变
	for(i=0;i<tsum1;i++)
	{
		if(tfm1[i].alarm==0) continue;
		if(tfm1[i].ack==0) gj=1;
		n++;
	}
	//先看2绕变
	for(i=0;i<tsum2;i++)
	{
		if(tfm2[i].alarm==0) continue;
		if(tfm2[i].ack==0) gj=1;
		n++;
	}
	alarm=gj;
	if(n!=alsum)
	{
		alm[2].Alarm=1;
		alm[2].num=n;
		SetTran();
	}
	alsum=n;
}
//计算一个断面的告警
void GzTblDlg::ComputDmAlm(DMLS*dl,int num,float &pl,float &ql,float &pqs)
{
	int i;
	float p,q;
	double pz,qz,psum,ps;
	pz=0;
	qz=0;
	psum=0;
	for(i=0;i<num;i++)
	{
		if(!GetLineDataPQ(p,q,dl[i].id,dl[i].type)) continue;
		if(dl[i].ys==0) pz+=p; else pz-=p;
		if(dl[i].ys==0) qz+=q; else qz-=q;
		ps=p;//sqrt(p*p+q*q);
		if(dl[i].ys==0) psum+=ps;
		else psum-=ps;
	}
	pl=(float)pz;
	ql=(float)qz;
	pqs=(float)psum;
}


//返回线路的P,Q值
bool GzTblDlg::GetLineDataPQ(float &Pcur,float &Qcur,int id,int type)
{
	int i;
	switch(type)
	{
	case 0://交流
		for(i=0;i<lsum;i++)
		{
			if(id==(int)line[i].NU)
			{
				Pcur=line[i].Pf;
				Qcur=line[i].Qf;
				return true;
			}
		}
		break;
	case 1: //直流
		for(i=0;i<dlsum;i++)
		{
			if(id==(int)dcline[i].NU)
			{
				Pcur=dcline[i].Pf;
				Qcur=dcline[i].Qf;
				return true;
			}
		}
		break;
	case 2: //三绕变
		for(i=0;i<tsum2;i++)
		{
			if(id==(int)tfm2[i].NU)
			{
				Pcur=tfm2[i].P;
				Qcur=tfm2[i].Q;
				return true;
			}
		}
		break;
	case 3: //发电机
		for(i=0;i<gsum;i++)
		{
			if(id==(int)gen[i].NU)
			{
				Pcur=gen[i].P;
				Qcur=gen[i].Q;
				return true;
			}
		}
		break;
	}
	return true;
}

//设置断面
void GzTblDlg::SetDM()
{
	int i,n,m;
	DMLS *dl;
	char *lp;
	float p,q,ps;
	char str[100];
	double a;
	n=0;
	m_lst.DeleteAllItems();
    
	for(i=0;i<pdsum;i++)
	{
		if(pdf[i].alarm==0&&showmode==0) continue;
		lp=pdf[i].DevID+2;
		m=pdf[i].Nline;
		dl=(DMLS*)lp;
		if(pdf[i].Vmax==0) continue;
		ps=pdf[i].curval;
		//ComputDmAlm(dl,m,p,q,ps);
		a=ps/pdf[i].Vmax;
		a=a<0 ? -a:a;
		if(a<pdf[i].CurPar && showmode==0) continue;
		m_lst.InsertItem(n,pdf[i].Name);
		sprintf(str,"%2.2f",a*100);
		m_lst.SetItemText(n,1,str);
		sprintf(str,"%2.2f",ps);
		m_lst.SetItemText(n,2,str);
		sprintf(str,"%2.2f~%2.2f",pdf[i].Pcur,pdf[i].Vmax);
		m_lst.SetItemText(n,3,str);
		m_lst.SetItemData(n,pdf[i].ID);
		m_lst.SetCheck(n,pdf[i].ack);
		n++;
	}
}

//设置断面
void GzTblDlg::SetDM1()
{
	int i,m,n,gj;
	DMLS *dl;
	char *lp;
	float p,q,ps,max;
	double a;
    n=0;
	gj=0;
	for(i=0;i<pdsum;i++)
	{
		lp=pdf[i].DevID+2;
		m=pdf[i].Nline;
		dl=(DMLS*)lp;
		if(pdf[i].Vmax==0 && pdf[i].Pcur==0) //分母为0
		{
			pdf[i].alarm=0;
			continue;
		}
		ps=pdf[i].curval;
		max=pdf[i].Vmax;
		if(pdf[i].Pcur<0 && ps<0)
			max=pdf[i].Pcur;
		//ComputDmAlm(dl,m,p,q,ps);
		a=ps/max; 
		a=a<0 ? -a:a;
		pdf[i].alarm=a>pdf[i].CurPar ? 1:0;
		if(pdf[i].alarm==1)
		{
			n++;
			if(pdf[i].ack==0) 	gj=1;
		}
	}
	if(alsum!=n)
	{
		alm[3].Alarm=1;
		alm[3].num=n;
		SetDM();
	}
	alsum=n;
	alarm=gj;
}


//设置母线
void GzTblDlg::SetBus()
{
	int i,n;
	float v1,v2;
	char p[100];
	n=0;
	m_lst.DeleteAllItems();
    //先看交流
	for(i=0;i<bsum;i++)
	{
		if(bus[i].alarm==0&&showmode==0) continue;
		m_lst.InsertItem(n,bus[i].Name);
		sprintf(p,"%2.2f",bus[i].Vb);
		m_lst.SetItemText(n,1,p);
		v1=bus[i].MaxV;
		v2=bus[i].MinV;
		if(v1!=0&&v2!=0)
		{
			sprintf(p,"%2.2f--%2.2f",v2,v1);
			m_lst.SetItemText(n,2,p);
			sprintf(p,"%2.2f-%2--%2.2f",v2+1.5,v1-1.5);
			m_lst.SetItemText(n,3,p);
		}
		if(bus[i].alarm==0)
		{
			v1=bus[i].MaxV-bus[i].Vb;
			v2=bus[i].Vb-bus[i].MinV;
			v1=v1<v2 ? v1:v2;
			if(v1>=0) sprintf(p,"%2.2f",v1);
			else strcpy(p,"===");
			if(bus[i].MaxV==0||bus[i].MinV==0||bus[i].Vb==0) m_lst.SetItemText(n,4,"===");
			else m_lst.SetItemText(n,4,p);
		}else m_lst.SetItemText(n,4,"===");


		m_lst.SetItemData(n,bus[i].NU);
		m_lst.SetCheck(n,bus[i].ack);

		n++;
	}
}

//设置母线
void GzTblDlg::SetBus1()
{
	int i,n,gj;
	gj=0;
	n=0;
	for(i=0;i<bsum;i++)
	{
		if(bus[i].alarm==0) continue;
		n++;
		if(bus[i].ack==0) gj=1;
	}
	alarm=gj;
	if(alsum!=n)
	{
		alm[4].Alarm=1;
		alm[4].num=n;
		SetBus();
	}
	alsum=n;
}


void GzTblDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	if(m_lst)
		m_lst.MoveWindow(CRect(0,25,cx,cy));
}

void GzTblDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 100:  //定时扫描告警设备
		TimeRefreshAlarm();
		break;
	}
	CDialog::OnTimer(nIDEvent);
}

void GzTblDlg::OnReload() 
{
	SetList();
}


void GzTblDlg::OnItemchangedList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int cursel,oldstate,newstate,check;
	DWORD id;
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	oldstate=pNMListView->uNewState;
	newstate=pNMListView->uOldState;
	if(init==0)
	{
		cursel=pNMListView->iItem;
		if(newstate!=0x1000&&newstate!=0x2000) return;
		check=m_lst.GetCheck(cursel);
		id=m_lst.GetItemData(cursel);
		CheckAAlarm(check,id);
	}
	*pResult = 0;
}


void GzTblDlg::CheckAAlarm(int check,DWORD id)
{
	switch(type)
	{
	case 0: //线路
		CheckLine(check,id);
		break;
	case 1: //发电机
		CheckGen(check,id);
		break;
	case 2: //变压器
		CheckTran(check,id);
		break;
	case 3: //断面
		CheckDM(check,id);
		break;
	case 4: //母线
		CheckBus(check,id);
		break;
	case 5: //ACE
		CheckAce(check,id);
		break;
	case 6:
		CheckHvc(check,id);
		break;
	}
}

//设置HVC
void GzTblDlg::CheckHvc(int check,DWORD id)
{
	/*int i;
    //先看交流
	for(i=0;i<hsum;i++)
	{
		if(hvc[i].ID!=id) continue;
		if(hvc[i].Ack==check) return;
		hvc[i].Ack=check;
		SetFieldTran(mhvc,i,7,1);
	}*/
}


//设置母线
void GzTblDlg::CheckAce(int check,DWORD id)
{
	/*int i;
    //先看交流
	for(i=0;i<esum;i++)
	{
		if(ace[i].ID!=id) continue;
		if(ace[i].ack==check) return;
		ace[i].ack=check;
		SetFieldTran(mbus,i,4,1);
	}*/
}

//设置母线
void GzTblDlg::CheckBus(int check,DWORD id)
{
	int i;
    //先看交流
	for(i=0;i<bsum;i++)
	{
		if(bus[i].NU!=id) continue;
		if(bus[i].ack==check) return;
		bus[i].ack=check;
		SetFieldTran(mbus,i,fpos[3],1);
	}
}

//设置断面
void GzTblDlg::CheckDM(int check,DWORD id)
{
	int i;
    for(i=0;i<pdsum;i++)
	{
		if(pdf[i].ID!=id) continue;
		if(pdf[i].ack==check) return;
		pdf[i].ack=check;
		SetFieldTran(mpdf,i,fpos[6],7);
	}
}

//设置变压器
void GzTblDlg::CheckTran(int check,DWORD id)
{
	int i;
    //先看2绕变
	for(i=0;i<tsum1;i++)
	{
		if(tfm1[i].NU!=id) continue;
		if(tfm1[i].ack==check) return;
		tfm1[i].ack=check;
		SetFieldTran(mtf1,i,fpos[1],1);
	}
	//先看2绕变
	for(i=0;i<tsum2;i++)
	{
		if(tfm2[i].NU!=id) continue;
		if(tfm2[i].ack==check) return;
		tfm2[i].ack=check;
		SetFieldTran(mtf2,i,fpos[2],1);
	
	}
}

//设置发电机
void GzTblDlg::CheckGen(int check,DWORD id)
{
	int i;
    //先看交流
	for(i=0;i<gsum;i++)
	{
		if(gen[i].NU!=id) continue;
		if(gen[i].ack==check) return;
		gen[i].ack=check;
		SetFieldTran(mgen,i,fpos[0],1);
	}
}

//设置线路
void GzTblDlg::CheckLine(int check,DWORD id)
{
	int i;
    //先看交流
	for(i=0;i<lsum;i++)
	{
		if(line[i].NU!=id) continue;
		if(line[i].ack==check) return;
		line[i].ack=check;
		SetFieldTran(mlin,i,fpos[4],1);
		return;
	}
	//再看直流
	for(i=0;i<dlsum;i++)
	{
		if(dcline[i].NU!=id) continue;
		if(dcline[i].ack==check) return;
		dcline[i].ack=check;
		SetFieldTran(mdlin,i,fpos[5],1);
		return;
	}
}


//全部确认
void GzTblDlg::OnCheckall() 
{
	int i,n;
	DWORD id;
	n=m_lst.GetItemCount();
	for(i=0;i<n;i++)
	{
		id=m_lst.GetItemData(i);
		CheckAAlarm(1,id);
		m_lst.SetCheck(i,1);
	}
}

//取消全部确认
void GzTblDlg::OnUncheckall() 
{
	int i,n;
	DWORD id;
	n=m_lst.GetItemCount();
	for(i=0;i<n;i++)
	{
		id=m_lst.GetItemData(i);
		CheckAAlarm(0,id);
		m_lst.SetCheck(i,0);
	}
}

//音效控制
void GzTblDlg::OnSound() 
{
    sound=IsDlgButtonChecked(IDC_SOUND);
}

void GzTblDlg::OnShowall() 
{
	showmode=1;
	SetList();
	
}

void GzTblDlg::OnShowalm() 
{
	showmode=0;
	SetList();
}

int GzTblDlg::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	// TODO: Add your specialized creation code here
	
	return 0;
}
