// CfgMeter.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "CfgMeter.h"
#include "middll.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

char *dbtype[]={"系统指标","发电机","二绕变","三绕变","交流线路","直流线路","负荷","仪表数据","电容","电抗",
				"SVC","区域","系统"};
  
char *xsm0[]={"当前指标"};
char *xsm1[]={"有功","无功"};
extern comobj  cobj;
/////////////////////////////////////////////////////////////////////////////
// CCfgMeter dialog


CCfgMeter::CCfgMeter(CWnd* pParent /*=NULL*/)
	: CDialog(CCfgMeter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCfgMeter)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	sw=100;
	sh=100;
	mdc.Create(sw,sh);
}


void CCfgMeter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCfgMeter)
	DDX_Control(pDX, IDC_DS, m_ds);
	DDX_Control(pDX, IDC_LIST1, m_lst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCfgMeter, CDialog)
	//{{AFX_MSG_MAP(CCfgMeter)
	ON_BN_CLICKED(IDC_DBSRC, OnDbsrc)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST1, OnDblclkList1)
	ON_NOTIFY(NM_CLICK, IDC_LIST1, OnClickList1)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_USERDEF, OnUserdef)
	ON_BN_CLICKED(IDC_DELUSER, OnDeluser)
	ON_BN_CLICKED(IDC_MODIPARAM, OnModiparam)
	ON_BN_CLICKED(IDC_MODICOLOR1, OnModicolor1)
	ON_BN_CLICKED(IDC_MODICOLOR2, OnModicolor2)
	ON_CBN_SELCHANGE(IDC_DS, OnSelchangeDs)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCfgMeter message handlers

BOOL CCfgMeter::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_lst.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES);
	m_lst.InsertColumn(0,"序号",LVCFMT_LEFT,45,0);
	m_lst.InsertColumn(1,"数据源名",LVCFMT_LEFT,120,0);
	m_lst.InsertColumn(2,"类型",LVCFMT_LEFT,75,0);
	m_lst.InsertColumn(3,"值名",LVCFMT_LEFT,75,0);
	m_lst.InsertColumn(4,"ID",LVCFMT_LEFT,54,0);
	m_lst.InsertColumn(5,"参数",LVCFMT_LEFT,60,0);
	m_lst.InsertColumn(6,"量程",LVCFMT_LEFT,89,0);
	m_lst.InsertColumn(7,"刻度段",LVCFMT_LEFT,50,0);
	m_lst.InsertColumn(8,"第一段",LVCFMT_LEFT,100,0);
	m_lst.InsertColumn(9,"第二段",LVCFMT_LEFT,100,0);
	SetList();
	ejlh=cobj.GetEGPRecNo(tmp.egrpid);
	sel=-1;
	return TRUE;
}

void CCfgMeter::SetList()
{
	int i;
	char nm1[24],nm2[24];
	char p[100];
	m_lst.DeleteAllItems();
	for(i=0;i<tmp.dbsum;i++)
	{
		sprintf(p,"%d",i+1);
	    m_lst.InsertItem(i,p);
	    m_lst.SetItemText(i,1,tmp.dbs[i].name);
		if(tmp.dbs[i].did>=0)
		{
			GetTName(tmp.dbs[i].dtype,tmp.dbs[i].xsmode,nm1,nm2);
			m_lst.SetItemText(i,2,nm1);
			m_lst.SetItemText(i,3,nm2);
		}
		sprintf(p,"%d",tmp.dbs[i].did);
		m_lst.SetItemText(i,4,p);
		SetVallist(i);
	}
}

void CCfgMeter::SetVallist(int i)
{
	char p[100];
	if(tmp.pam[i].ptype==0)
	{
			m_lst.SetItemText(i,5,"自定义");
	}else{
			m_lst.SetItemText(i,5,"读库");
	}
	sprintf(p,"%2.2f->%2.2f",tmp.pam[i].vmin,tmp.pam[i].vmax);
	m_lst.SetItemText(i,6,p);
	sprintf(p,"%d",tmp.pam[i].alarm);
	m_lst.SetItemText(i,7,p);
	if(tmp.pam[i].alarm>0)
	{
		sprintf(p,"%2.2f->%2.2f",tmp.pam[i].val[0],tmp.pam[i].val[1]);
		m_lst.SetItemText(i,8,p);
	}else{
		m_lst.SetItemText(i,8,"");
	}
	if(tmp.pam[i].alarm>0)
	{
		sprintf(p,"%2.2f->%2.2f",tmp.pam[i].val[2],tmp.pam[i].val[3]);
		m_lst.SetItemText(i,9,p);
	}else
	{
		m_lst.SetItemText(i,9,"");
	}
}
void CCfgMeter::GetTName(int type,int xs,char *nm1,char *nm2)
{
	strcpy(nm1,"未定义");
	strcpy(nm2,"未定义");
	if(type<0||type>7) return;
	strcpy(nm1,dbtype[type]);
	switch(type)
	{
	case 0: //系统指标
		if(xs==0) 	strcpy(nm2,xsm0[xs]);
		break;
	case 1:case 2:case 3:case 4:case 5:case 6:
		if(xs>0&&xs<2) strcpy(nm2,xsm1[xs]);
		break;
	case 7:
		strcpy(nm2,"");
		break;
	}
}




void CCfgMeter::OnOK() 
{
	GetAlarmPam();
	CDialog::OnOK();
}

//获取数据源
void CCfgMeter::OnDbsrc() 
{
	int i;
	SINGLEDBS ybs;
	i=m_lst.GetSelectionMark();
	if(i<0) return;
	sel=i;
	ybs=tmp.dbs[i];
	//调用数据源设置程序
	if(SelYbDbs(ybs))
	{
		tmp.dbs[i]=ybs;
		SetList();
	}
	
}

void CCfgMeter::OnDblclkList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	OnDbsrc();
	
	*pResult = 0;
}

void CCfgMeter::OnClickList1(NMHDR* pNMHDR, LRESULT* pResult) 
{
	int i;
	i=m_lst.GetSelectionMark();
	if(i>=0)
	{
		GetAlarmPam();
		sel=i;
		ShowMeter();
		SetDefPam(i);
	}
	*pResult = 0;
}

void CCfgMeter::OnPaint() 
{
	CPaintDC dc(this);
	ShowMeter();
	ShowColor(IDC_COLOR1,tmp.pam[sel].color[0]);
	ShowColor(IDC_COLOR2,tmp.pam[sel].color[1]);
}

//显示仪表
void CCfgMeter::ShowMeter()
{
	int w,h;
	CRect rts,rtd;
	CWnd *wnd=GetDlgItem(IDC_MTSHW);
	CClientDC dc(wnd);
	wnd->GetWindowRect(&rt);
	rt.OffsetRect(-rt.left,-rt.top);
	w=rt.Width()-4;
	h=rt.Height()-4;
	if(sw!=w||sh!=h)
	{
		mdc.SizeChange(w,h);
		sw=w;
		sh=h;
	}
	mdc.FillBG(0);//GetSysColor);//COLOR_3DFACE));
	DrawMeter();
	rts=CRect(0,0,sw,sh);
	rtd=rts;
	rtd.OffsetRect(2,2);
	mdc.BitBltRect(dc.m_hDC,rts,rtd);
}


void CCfgMeter::DrawMeter()
{
	int i,j,k,dx,dy;
	BASE0 *bs,bbs;
	double xl,yl,w1,w2,h1,h2,a;
	CDRect rt,rt1,rt2;
	if(ejlh<0||ejlh>=cobj.egpsum) return; //超出范围
	bs=cobj.egp[ejlh].bs1;
	j=cobj.egp[ejlh].bsum1;
	rt1.SetDRECT(cobj.egp[ejlh].rt1);
	if(bs==NULL||j<=0)	return;
	//计算宽高
	if(sel>=0&&sel<cobj.egp[ejlh].sitesum)
	{
		k=cobj.egp[ejlh].index[sel];
	} else k=-1;

	//原来的宽高
	w2=rt1.Width();
	h2=rt1.Height();
	if(w2==0||h2==0) return;
	a=w2/h2;
	if(a>1)
	{
		w1=sw;
		h1=sw/a;
	}else{
		h1=sh;
		w1=sh*a;
	}
	dx=(int)((sw-w1)/2);
	dy=(int)((sh-h1)/2);
	rt.left=0;rt.top=0;rt.right=w1;rt.bottom=h1;
	rt2.left=0;		rt2.top=0;
	rt2.right=rt.left;	rt2.bottom=rt.top;
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	for(i=0;i<j;i++){
	   	bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.SetSelected();
		bbs.MoveObject2(rt2,xl,yl);
		if(k>=0){
			if(i!=k) bbs.SetColor(0x7f7f7f);
			else bbs.SetColor(0xff);
		}
		bbs.SetSObjZM(xl);
		bbs.ShowE(mdc,dx,dy);
		bbs.FreeMem();
	};
}

//设定为自定义量程
void CCfgMeter::OnUserdef() 
{
	if(sel<0)
	{
		MessageBox("没有选择一个仪表！","错误",MB_ICONSTOP|MB_OK);
		return;
	}
	if(sel<0||sel>=tmp.dbsum) return;
	tmp.pam[sel].ptype=0;
	m_lst.SetItemText(sel,5,"自定义参数");
}

//删除自定义
void CCfgMeter::OnDeluser() 
{
	if(sel<0)
	{
		MessageBox("没有选择一个仪表！","错误",MB_ICONSTOP|MB_OK);
		return;
	}
	if(sel<0||sel>=tmp.dbsum) return;
	tmp.pam[sel].ptype=1;
	m_lst.SetItemText(sel,5,"读取参数");
}


void CCfgMeter::EnableItem(int id, bool enable)
{
	CWnd *wnd;
	wnd=GetDlgItem(id);
	if(wnd==NULL) return;
	wnd->EnableWindow(enable);
}

void CCfgMeter::ShowColor(int id, DWORD color)
{
	CRect rt;
	CWnd *wnd;
	wnd=GetDlgItem(id);
	wnd->GetWindowRect(&rt);
	rt.OffsetRect(-rt.left,-rt.top);
	CClientDC dc(wnd);
	wnd->UpdateWindow();
	dc.FillSolidRect(&rt,color);
	dc.Draw3dRect(&rt,0,0xffffff);
}


void CCfgMeter::SetItemData(int id,float val)
{
	char p[100];
	sprintf(p,"%2.2f",val);
	SetDlgItemText(id,p);
}

float CCfgMeter::GetItemData(int id)
{
	char p[100];
	GetDlgItemText(id,p,15);
	return (float)atof(p);
}
//设置自定义参数
void CCfgMeter::SetDefPam(int i)
{
	//置参数
	if(i>=tmp.dbsum) return;
	//先有效
	SetItemData(IDC_VMIN,tmp.pam[i].vmin);
	SetItemData(IDC_VMAX,tmp.pam[i].vmax);
	SetItemData(IDC_V1,tmp.pam[i].val[0]);
	SetItemData(IDC_V2,tmp.pam[i].val[1]);
	SetItemData(IDC_V3,tmp.pam[i].val[2]);
	SetItemData(IDC_V4,tmp.pam[i].val[3]);
	ShowColor(IDC_COLOR1,tmp.pam[i].color[0]);
	ShowColor(IDC_COLOR2,tmp.pam[i].color[1]);
	m_ds.SetCurSel(tmp.pam[i].alarm);
}

void CCfgMeter::OnModiparam() 
{
	GetAlarmPam();
	MessageBox("信息已被更新到仪表！","提示",MB_OK);
}

void CCfgMeter::OnModicolor1() 
{
	if(sel<0||sel>=tmp.dbsum) return;
	CColorDialog cdlg(tmp.pam[sel].color[0],0,this);
	if(cdlg.DoModal()==IDOK)
	{
		tmp.pam[sel].color[0]=cdlg.GetColor();
		ShowColor(IDC_COLOR1,tmp.pam[sel].color[0]);
	}
}

void CCfgMeter::OnModicolor2() 
{
	if(sel<0||sel>=tmp.dbsum) return;
	CColorDialog cdlg(tmp.pam[sel].color[0],0,this);
	if(cdlg.DoModal()==IDOK)
	{
		tmp.pam[sel].color[0]=cdlg.GetColor();
		ShowColor(IDC_COLOR2,tmp.pam[sel].color[1]);
	}
}

void CCfgMeter::OnSelchangeDs() 
{
	int i;
	if(sel<0||sel>=tmp.dbsum) return;
	i=m_ds.GetCurSel();
	if(i==CB_ERR) return;
	tmp.pam[sel].alarm=i;
}


void CCfgMeter::GetAlarmPam()
{
	//修改参数
	float vmax,vmin,v1,v2,v3,v4;
	if(sel<0||sel>=tmp.dbsum) return;
	vmax=GetItemData(IDC_VMAX);
	vmin=GetItemData(IDC_VMIN);
	v1=GetItemData(IDC_V1);
	v2=GetItemData(IDC_V2);
	v3=GetItemData(IDC_V3);
	v4=GetItemData(IDC_V4);
	tmp.pam[sel].vmax=vmax;
	tmp.pam[sel].vmin=vmin;
	tmp.pam[sel].val[0]=v1;
	tmp.pam[sel].val[1]=v2;
	tmp.pam[sel].val[2]=v3;
	tmp.pam[sel].val[3]=v4;	
}
