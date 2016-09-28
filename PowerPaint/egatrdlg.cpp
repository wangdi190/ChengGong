// egatrdlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "egatrdlg.h"
#include "comobj.h"
#include "gdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern comobj  cobj;
extern gdata   dbm;
char *dtp[]={"PT","发电机","开关,刀闸","负荷","电容","电抗","接地","二绕组变压器","三绕组变压器","静态无功补偿器","逆变、变流器"};
char *stpy[]={"虚拟仪表","设备","厂站","区域","双图模拟量"};
/////////////////////////////////////////////////////////////////////////////
// egatrdlg dialog


egatrdlg::egatrdlg(int cursel,CWnd* pParent /*=NULL*/)
	: CDialog(egatrdlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(egatrdlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	sel=cursel;
}


void egatrdlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(egatrdlg)
	DDX_Control(pDX, IDC_SITESUM, m_ssum);
	DDX_Control(pDX, IDC_SUBTYPE, m_stype);
	DDX_Control(pDX, IDC_TYPE, m_type);
	DDX_Control(pDX, IDC_MSG, m_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(egatrdlg, CDialog)
	//{{AFX_MSG_MAP(egatrdlg)
	ON_CBN_SELCHANGE(IDC_TYPE, OnSelchangeType)
	ON_BN_CLICKED(IDC_ANALYSE, OnAnalyse)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// egatrdlg message handlers

BOOL egatrdlg::OnInitDialog() 
{
	int i;
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_NAME,cobj.egp[sel].name);
	for(i=0;i<4;i++){
	  m_type.AddString(stpy[i]);
	}
	for(i=0;i<11;i++){
	  m_stype.AddString(dtp[i]);
	}
	m_type.SetCurSel(cobj.egp[sel].type);
	m_stype.SetCurSel(cobj.egp[sel].subtype);
	m_ssum.SetCurSel(cobj.egp[sel].sitesum);
	m_ssum.EnableWindow(false);	
	if(cobj.egp[sel].type==1){
		m_stype.EnableWindow(true);	
	}else{
		m_stype.EnableWindow(false);
	}
	return TRUE;
}

void egatrdlg::OnSelchangeType() 
{
	int k;
	k=m_type.GetCurSel();
	cobj.egp[sel].type=k;
	if(k==1){
		m_stype.EnableWindow(true);	
	}else{
		m_stype.EnableWindow(false);
	}
}

void egatrdlg::OnAnalyse() 
{
	N_ELEGRP *el;
	el=&cobj.egp[sel];
	switch(el->type)
	{
	case 0: //分析仪表
		AnalyseMeter();
		break;
	case 1: //分析设备
		Analysedev();
		break;
	default:
		MessageBox("非仪表和设备类无需分析");
		break;
	}
}

void egatrdlg::OnOK() 
{
	GetDlgItemText(IDC_NAME,cobj.egp[sel].name,15);
	cobj.egp[sel].type=m_type.GetCurSel();
	cobj.egp[sel].subtype=m_stype.GetCurSel();
	CDialog::OnOK();
}


//分析设备
void egatrdlg::Analysedev()
{
	int i,j,n,type;
	char p[100];
	CDRect  art;
	BASE0 *bs[3];
	N_ELEGRP *el;
	m_msg.ResetContent();
	m_msg.AddString("开始分析:");
	el=&cobj.egp[sel];
	el->sitesum=0;
	cobj.egp[sel].type=m_type.GetCurSel();
	cobj.egp[sel].subtype=m_stype.GetCurSel();
	//将所属置0
	for(i=0;i<el->bsum1;i++){
	  el->bs1[i].attr.belong=0;
	}
	for(i=0;i<el->bsum2;i++){
	  el->bs2[i].attr.belong=0;
	}
	for(i=0;i<el->bsum1;i++){
		if(el->bs1[i].attr.type==11){ //type=11为电气端子
			el->bs1[i].ort.GetDRECT(el->srt[el->sitesum]);
			el->bs1[i].attr.belong=el->sitesum+1;
			el->sitesum++;
		}
	  if(el->sitesum>=3) break;
	}
	sprintf(p,"找到端子%d个",el->sitesum);
	m_msg.AddString(p);
	m_ssum.SetCurSel(cobj.egp[sel].sitesum);
	
	//如果不是变压器，就退出处理
	if(cobj.egp[sel].type!=1||(cobj.egp[sel].type==1&&
		cobj.egp[sel].subtype!=7&&cobj.egp[sel].subtype!=8))
	{
		m_msg.AddString("分析完毕");
		for(i=0;i<el->bsum1;i++){
			el->bs1[i].attr.belong=1;
		}
		for(i=0;i<el->bsum2;i++){
			el->bs2[i].attr.belong=1;
		}
		return;
	}

	//查找相交圆
	n=0;
	/*for(i=0;i<el->sitesum;i++){
		for(j=0;j<el->bsum1;j++){
			type=el->bs1[j].attr.type;
		 if((type==3||type==6)&&el->bs1[j].attr.belong==0){
			 art.SetDRECT(el->srt[i]);
			 art&=el->bs1[j].ort;
			 if(!art.IsRectEmpty()){
				bs[i]=&el->bs1[j];
				bs[i]->attr.belong=i+1;
				n++;
				break;
			 }
			}
		}
	}*/
	for(i=0;i<el->sitesum;i++)
	{
		//先分析圆的
		for(j=0;j<el->bsum1;j++)
		{
			type=el->bs1[j].attr.type;
			if(type==3&&el->bs1[j].attr.belong==0)
			{
				art.SetDRECT(el->srt[i]);
				art&=el->bs1[j].ort;
				if(!art.IsRectEmpty())
				{
					bs[n]=&el->bs1[j];
					bs[n]->attr.belong=i+1;
					n++;
					break;
				}
			}
		}
	}
	for(i=n;i<el->sitesum;i++)
	{
		//先分析圆弧的
		for(j=0;j<el->bsum1;j++)
		{
			type=el->bs1[j].attr.type;
		    if(type==6&&el->bs1[j].attr.belong==0)
			{
				art.SetDRECT(el->srt[i]);
				art&=el->bs1[j].ort;
				if(!art.IsRectEmpty())
				{
					bs[n]=&el->bs1[j];
					bs[n]->attr.belong=i+1;
					n++;
					break;
				}
			}
		}
	}
	sprintf(p,"找到符合要求的圆%d个",n);
	m_msg.AddString(p);
	switch(n){
	case 0:
		strcpy(p,"错误：变压器无端子");
		break;
	case 1:
		strcpy(p,"错误：一个端子的变压器，无法运行");
		break;
	case 2:
		strcpy(p,"这是一个2饶组的变压器");
		cobj.egp[sel].subtype=7;
		break;
	case 3:
		strcpy(p,"这是一个3饶组的变压器");
		cobj.egp[sel].subtype=8;
		break;
	}
	m_msg.AddString(p);
	m_stype.SetCurSel(cobj.egp[sel].subtype);
	if(n!=el->sitesum){
		m_msg.AddString("绘制的图形不满足要求!");
		return;
	}
	CDRect rt1,rt2;
	CDPoint pt1,pt2;
	//开始计算着色图形
	for(i=0;i<el->sitesum;i++)
	{
		rt1=bs[i]->ort;
		for(j=0;j<el->bsum1;j++)
		{
			if(el->bs1[j].attr.belong==0)
			{
				rt2=el->bs1[j].ort;
				pt1=CDPoint(rt2.left,rt2.top);
				pt2=CDPoint(rt2.right,rt2.bottom);
				if(rt1.PtInRect(pt1)&&rt1.PtInRect(pt2)) el->bs1[j].attr.belong=i+1;
			}
		}
	}
	for(i=0;i<el->sitesum;i++)
	{
		rt1=bs[i]->ort;
		rt1.left--;rt1.top--;
		rt1.right++;
		rt1.bottom++;
		for(j=0;j<el->bsum2;j++)
		{
			if(el->bs2[j].attr.belong==0)
			{
				rt2=el->bs2[j].ort;
				pt1=CDPoint(rt2.left,rt2.top);
				pt2=CDPoint(rt2.right,rt2.bottom);
				if(rt1.PtInRect(pt1)&&rt1.PtInRect(pt2)) el->bs2[j].attr.belong=i+1;
			}
		}
	}
	m_msg.AddString("设备分析完毕...");


}
//分析仪表
void egatrdlg::AnalyseMeter()
{
	int i,n;
	BYTE ind[32];
	char p[100];
	CDRect  art;
	N_ELEGRP *el;
	m_msg.ResetContent();
	m_msg.AddString("开始分析:");
	el=&cobj.egp[sel];
	el->sitesum=0;
	//查找仪表
	n=0;
	for(i=0;i<el->bsum1;i++)
	{
		switch(el->bs1[i].attr.type)
		{
		case 32:case 33:case 34:case 35:
		ind[n]=(BYTE)i;
		n++;
		break;
		}
		if(n>=32) break;
	}
	sprintf(p,"找到仪表部件%d个",n);
	m_msg.AddString(p);
	if(n>8)	m_msg.AddString("仪表太多，只取前8个仪表部件");
	m_msg.AddString("将分析结果保存");
	n=n>8 ? 8:n;
	el->sitesum=n;
	for(i=0;i<n;i++)
	{
		el->index[i]=ind[i];
	}
	m_msg.AddString("仪表分析完毕...");
}