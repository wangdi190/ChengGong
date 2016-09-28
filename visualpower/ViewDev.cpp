// ViewDev.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "ViewDev.h"
#include "comobj.h"
#include "middll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern comobj  cobj;		//公共对象
/////////////////////////////////////////////////////////////////////////////
// CViewDev dialog


CViewDev::CViewDev(CWnd* pParent /*=NULL*/)
	: CDialog(CViewDev::IDD, pParent)
{
	//{{AFX_DATA_INIT(CViewDev)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	curtype=-1;
	dataok=0;
}


void CViewDev::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CViewDev)
	DDX_Control(pDX, IDC_LIST1, m_lst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CViewDev, CDialog)
	//{{AFX_MSG_MAP(CViewDev)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CViewDev message handlers

BOOL CViewDev::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetData();
	
	return TRUE;  
}


bool CViewDev::SetParam(int type, char *name, int id)
{
	void *data;
	switch(type){
	case 0:
		memset(&gd,0,sizeof(GenData));
		gd.gid=id;
		strcpy(gd.gname,name);
		data=&gd;
		break;
	case 1:
		memset(&ld,0,sizeof(LinData));
		ld.lid=id;
		strcpy(ld.lname,name);
		data=&ld;
		break;
	case 2:
		memset(&dd,0,sizeof(DLinData));
		dd.lid=id;
		strcpy(dd.lname,name);
		data=&dd;
		break;
	case 3:
		memset(&bd,0,sizeof(BusData));
		bd.bid=id;
		strcpy(bd.bname,name);
		data=&bd;
		break;
	case 4:
		memset(&ldd,0,sizeof(LoadData));
		ldd.lid=id;
		strcpy(ldd.lname,name);
		data=&ldd;
		break;
	case 5:	
		memset(&td1,0,sizeof(TrfData1));
		td1.tid=id;
		strcpy(td1.tname,name);
		data=&td1;
		break;
	case 6:	
		memset(&td2,0,sizeof(TrfData2));
		td2.tid=id;
		strcpy(td2.tname,name);
		data=&td2;
		break;
	case 7:
		memset(&sd,0,sizeof(ShuData));
		sd.devid=id;
		strcpy(sd.bname,name);
		data=&sd;
		break;
	case 8:
		memset(&srd,0,sizeof(SrdData));
		srd.id=id;
		strcpy(srd.name,name);
		data=&srd;
		break;
	case 9:
		memset(&svd,0,sizeof(SvcData));
		svd.id=id;
		strcpy(svd.sname,name);
		data=&svd;
		break;
	default:
		return false;
	}
	if(!rrd->ReadDevViewMsg(data,type)) return false;
	curtype=type;
	
	return true;
}


//设置数据
void CViewDev::SetData()
{
	switch(curtype){
	case 0:  //发电机
		SetGenData();
		break;
	case 1: //交流输电线
		SetLineData();
		break;
	case 2: //直流线路
		SetDlineData();
		break;
	case 3: //母线
		SetBusData();
		break;
	case 4://负荷
		SetLoadData();
		break;
	case 5: //2绕组变压器
		SetTranData1();
		break;
	case 6: //3绕组变压器
		SetTranData2();
		break;
	case 7: //电容器
		SetShuData();
		break;
	case 8: //电抗器
		SetSrdData();
		break;
	case 9: //静态无功补偿装置
		SetSvcData();
		break;
	}
}
//设置发电机
extern char *glst[];

void CViewDev::SetGenData()
{
	int i;
	char p[100];
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"  项     目",LVCFMT_LEFT,100,0);
	m_lst.InsertColumn(1,"  当前值",LVCFMT_LEFT,160,0);
	for(i=0;i<3;i++) m_lst.InsertItem(i,glst[i]);
	m_lst.SetItemText(0,1,gd.gname);
	sprintf(p,"%2.2fMW",gd.sngGEN_MW);
	m_lst.SetItemText(1,1,p);
	sprintf(p,"%2.2fMVar",gd.sngGEN_MVAR);
	m_lst.SetItemText(2,1,p);
}

extern char *llst[];

void CViewDev::SetLineData()
{
	int i;
	char p[100];
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"  项     目",LVCFMT_LEFT,100,0);
	m_lst.InsertColumn(1,"  当前值",LVCFMT_LEFT,160,0);
	for(i=0;i<4;i++) m_lst.InsertItem(i,llst[i]);
	m_lst.SetItemText(0,1,ld.lname);
	sprintf(p,"%d",ld.lid);
	m_lst.SetItemText(1,1,p);
	sprintf(p,"%2.2fMW",ld.sngMW);
	m_lst.SetItemText(2,1,p);
	sprintf(p,"%2.2fMVal",ld.sngMVAR);
	m_lst.SetItemText(3,1,p);
}

extern char *dllst[];

void CViewDev::SetDlineData()
{
	int i;
	char p[100];
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"  项     目",LVCFMT_LEFT,100,0);
	m_lst.InsertColumn(1,"  值       ",LVCFMT_LEFT,160,0);
	for(i=0;i<4;i++) m_lst.InsertItem(i,dllst[i]);
	m_lst.SetItemText(0,1,dd.lname);
	sprintf(p,"%d",dd.lid);
	m_lst.SetItemText(1,1,p);
	sprintf(p,"%2.2fMW",dd.sngMW);
	m_lst.SetItemText(2,1,p);
	sprintf(p,"%2.2fMVar",dd.sngMVAR);
	m_lst.SetItemText(3,1,p);
}

extern char  *blst[];

void CViewDev::SetBusData()
{
	int i;
	char p[100];
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"  项     目",LVCFMT_LEFT,100,0);
	m_lst.InsertColumn(1,"  当前值",LVCFMT_LEFT,200,0);
	for(i=0;i<5;i++) m_lst.InsertItem(i,blst[i]);
	m_lst.SetItemText(0,1,bd.bname);
	sprintf(p,"%d",bd.bid);
	m_lst.SetItemText(1,1,p);
	sprintf(p,"%2.2f",bd.sngVOLTAGE_PU);
	m_lst.SetItemText(2,1,p);
	sprintf(p,"%2.2fKV",bd.vb);
	m_lst.SetItemText(3,1,p);
	sprintf(p,"%2.2f",bd.sngVOLTAGE_DEG);
	m_lst.SetItemText(4,1,p);
}

extern char *dlst[];

void CViewDev::SetLoadData()
{
	int i;
	char p[100];
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"  项     目",LVCFMT_LEFT,160,0);
	m_lst.InsertColumn(1,"  值       ",LVCFMT_LEFT,140,0);
	for(i=0;i<6;i++) m_lst.InsertItem(i,dlst[i]);
	m_lst.SetItemText(0,1,ldd.lname);
	sprintf(p,"%d",ldd.lid);
	m_lst.SetItemText(1,1,p);
	sprintf(p,"%s",ldd.intsta==0 ? "退出":"投入");
	m_lst.SetItemText(2,1,p);
	sprintf(p,"%2.2fKV",ldd.vl);
	m_lst.SetItemText(3,1,p);
	sprintf(p,"%2.2fMW",ldd.sngPL);
	m_lst.SetItemText(4,1,p);
	sprintf(p,"%2.2fMVar",ldd.sngQL);
	m_lst.SetItemText(5,1,p);
}

extern char  *tlst1[];

void CViewDev::SetTranData1()
{
	int i;
	char p[100];
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"  项     目",LVCFMT_LEFT,100,0);
	m_lst.InsertColumn(1,"  当前值",LVCFMT_LEFT,200,0);
	for(i=0;i<9;i++) m_lst.InsertItem(i,tlst1[i]);
	m_lst.SetItemText(0,1,td1.tname);
	sprintf(p,"%d",td1.tid);
	m_lst.SetItemText(1,1,p);
	sprintf(p,"%2.2fKV",td1.hlv);
	m_lst.SetItemText(2,1,p);
	sprintf(p,"%2.2f",td1.tagh);
	m_lst.SetItemText(3,1,p);
	sprintf(p,"%2.2fMVA",td1.maxp);
	m_lst.SetItemText(4,1,p);
	sprintf(p,"%2.2fMW",td1.curp);
	m_lst.SetItemText(5,1,p);
	sprintf(p,"%2.2fMvar",td1.curq);
	m_lst.SetItemText(6,1,p);
	sprintf(p,"%2.2f℃",td1.Tcur);
	m_lst.SetItemText(7,1,p);
	sprintf(p,"%2.2f℃",td1.Tmax);
	m_lst.SetItemText(8,1,p);
}

extern char  *tlst2[];
void CViewDev::SetTranData2()
{
	int i;
	char p[100];
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"  项     目",LVCFMT_LEFT,100,0);
	m_lst.InsertColumn(1,"  当前值",LVCFMT_LEFT,200,0);
	for(i=0;i<13;i++) m_lst.InsertItem(i,tlst2[i]);
	m_lst.SetItemText(0,1,td2.tname);
	sprintf(p,"%d",td2.tid);
	m_lst.SetItemText(1,1,p);
	sprintf(p,"%2.2fKV",td2.hlv);
	m_lst.SetItemText(2,1,p);
	sprintf(p,"%2.2f",td2.tagh);
	m_lst.SetItemText(3,1,p);
	sprintf(p,"%2.2fKV",td2.mlv);
	m_lst.SetItemText(4,1,p);
	sprintf(p,"%2.2f",td2.tagm);
	m_lst.SetItemText(5,1,p);
	sprintf(p,"%2.2fKV",td2.llv);
	m_lst.SetItemText(6,1,p);
	sprintf(p,"%2.2f",td2.tagl);
	m_lst.SetItemText(7,1,p);
	sprintf(p,"%2.2fMVA",td2.maxp);
	m_lst.SetItemText(8,1,p);
	sprintf(p,"%2.2fMW",td2.curp);
	m_lst.SetItemText(9,1,p);
	sprintf(p,"%2.2fMvar",td2.curq);
	m_lst.SetItemText(10,1,p);
	sprintf(p,"%2.2f℃",td2.Tcur);
	m_lst.SetItemText(11,1,p);
	sprintf(p,"%2.2f℃",td2.Tmax);
	m_lst.SetItemText(12,1,p);
}

extern char  *slst[];
void CViewDev::SetShuData()
{
	int i;
	char p[100];
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"  项     目",LVCFMT_LEFT,100,0);
	m_lst.InsertColumn(1,"  当前值",LVCFMT_LEFT,200,0);
	for(i=0;i<7;i++) m_lst.InsertItem(i,slst[i]);
	m_lst.SetItemText(0,1,sd.bname);
	sprintf(p,"%d",sd.devid);
	m_lst.SetItemText(1,1,p);
	m_lst.SetItemText(2,1,sd.bname);
	sprintf(p,"%2.2fKV",sd.vl);
	m_lst.SetItemText(3,1,p);
	strcpy(p,sd.sta==0 ? "退出":"投入");
	m_lst.SetItemText(4,1,p);
	sprintf(p,"%2.5fMVar",sd.c);
	m_lst.SetItemText(5,1,p);
	if(sd.qst!=0){
		sprintf(p,"%d",(int)(sd.c/sd.qst));
		m_lst.SetItemText(6,1,p);
	}else m_lst.SetItemText(5,1,"未知组数");
}

//静态无工补偿装置
extern char  *svlst[];

void CViewDev::SetSvcData()
{
	int i;
	char p[100];
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"  项     目",LVCFMT_LEFT,100,0);
	m_lst.InsertColumn(1,"  当前值",LVCFMT_LEFT,200,0);
	for(i=0;i<6;i++) m_lst.InsertItem(i,slst[i]);
	m_lst.SetItemText(0,1,svd.sname);
	sprintf(p,"%d",svd.id);
	m_lst.SetItemText(1,1,p);
	m_lst.SetItemText(2,1,svd.bname);
	sprintf(p,"%2.2fKV",svd.vl);
	m_lst.SetItemText(3,1,p);
	sprintf(p,"%s",sd.sta==0 ? "退出":"投入");
	m_lst.SetItemText(4,1,p);
	sprintf(p,"%2.5f",svd.Q);
	m_lst.SetItemText(5,1,p);
}
//串联电抗

extern char  *srlst[];
void CViewDev::SetSrdData()
{
	int i;
	char p[100];
	m_lst.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FLATSB);
	m_lst.InsertColumn(0,"  项     目",LVCFMT_LEFT,160,0);
	m_lst.InsertColumn(1,"  值",LVCFMT_LEFT,140,0);
	for(i=0;i<4;i++) m_lst.InsertItem(i,srlst[i]);
	m_lst.SetItemText(0,1,srd.name);
	sprintf(p,"%d",srd.id);
	m_lst.SetItemText(1,1,p);
	sprintf(p,"%s",srd.sta==0 ? "退出":"投入");
	m_lst.SetItemText(2,1,p);
	sprintf(p,"%2.4f",srd.sngZX);
	m_lst.SetItemText(3,1,p);
}
