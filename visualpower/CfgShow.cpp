// CfgShow.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "CfgShow.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
double vl[]={1.1, 1.05, 1.0,0.95,0.9,
		   0.98,0.97,0.96,0.95,0.94,
		   1.06,1.05,1.04,1.03,1.02,
		   80,70,60,50,40,
		   1.05, 0.9, 0.8,0.65,0.5,
		   80,70,60,50,40};
DWORD  cr[]={0xff,0x7f7f,0xff00,0x7f7f00,0xff0000,
			0xff00,0x7fc000,0xc0c000,0xc04000,0xff0000,
			0xff,0x40c0,0x7f7f,0xc040,0xff00,
			0xff,0x7fff,0xffff,0,0xff00,
			0xff,0x40ff,0x7fff,0xb07f,0xff00,
			0xff,0x7fff,0xffff,0xff00,0xffffff};
char    *ut[]={"pu","pu","pu","%","%","%"};

int     qz[]={0,1,2,0,2,0};
int     fl[]={127,255,0,0,0,0};


DWORD scr[]={0xff,0xff00,0xffc0c0,0xff7f7f,0xff7f7f,0xff00,0xff7f7f,0xff00,0x7f7fff,0xff7f7f,0x7f7fff,0xff7f7f,
		     0x7f7fff,0xff7f7f,0xff7f,0xff00,0xff,0xff7f,0xff,0x7f7f7f};
DWORD sencr[]={0xff7f,0xffff,0xff,0xff7f00,0xff0000};
/////////////////////////////////////////////////////////////////////////////
// CCfgShow dialog


CCfgShow::CCfgShow(CWnd* pParent /*=NULL*/)
	: CDialog(CCfgShow::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCfgShow)
	//}}AFX_DATA_INIT
	CFont cf;
	cf.CreateFont(-12,0,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"Arial" );
	cf.GetLogFont(&lf);
	cf.DeleteObject();
}


void CCfgShow::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCfgShow)
	DDX_Control(pDX, IDC_SENCTYPE, m_senctype);
	DDX_Control(pDX, IDC_CNAME, m_cname);
	DDX_Control(pDX, IDC_DGXTYPE, m_dgxtype);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCfgShow, CDialog)
	//{{AFX_MSG_MAP(CCfgShow)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_DEFAULTCOLOR, OnDefaultcolor)
	ON_CBN_SELCHANGE(IDC_DGXTYPE, OnSelchangeDgxtype)
	ON_EN_KILLFOCUS(IDC_SMOOTH, OnKillfocusSmooth)
	ON_EN_KILLFOCUS(IDC_V1, OnKillfocusV1)
	ON_EN_KILLFOCUS(IDC_V2, OnKillfocusV2)
	ON_EN_KILLFOCUS(IDC_V3, OnKillfocusV3)
	ON_EN_KILLFOCUS(IDC_V4, OnKillfocusV4)
	ON_EN_KILLFOCUS(IDC_V5, OnKillfocusV5)
	ON_BN_CLICKED(IDC_CC1, OnC1)
	ON_BN_CLICKED(IDC_CC2, OnC2)
	ON_BN_CLICKED(IDC_CC3, OnC3)
	ON_BN_CLICKED(IDC_CC4, OnC4)
	ON_BN_CLICKED(IDC_CC5, OnC5)
	ON_CBN_SELCHANGE(IDC_CNAME, OnSelchangeCname)
	ON_BN_CLICKED(IDC_MODISC, OnModisc)
	ON_BN_CLICKED(IDC_MODISC2, OnModisc2)
	ON_CBN_SELCHANGE(IDC_SENCTYPE, OnSelchangeSenctype)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCfgShow message handlers

BOOL CCfgShow::OnInitDialog() 
{
	int i,j;
	char p[100];
	CDialog::OnInitDialog();
	CheckDlgButton(IDC_GENDT,tmpcfg.gendyn);
	CheckDlgButton(IDC_FLOWPIE,tmpcfg.flowover);
	CheckDlgButton(IDC_TRANDGX,tmpcfg.tranbg);
	CheckDlgButton(IDC_ONELINE,tmpcfg.oneline);
	CheckDlgButton(IDC_CPU,tmpcfg.cpu);
	m_dgxtype.SetCurSel(tmpcfg.ctrtype);

	sprintf(p,"%2.2f",tmpcfg.Pref);
	SetDlgItemText(IDC_ARROWP,p);
	
	sprintf(p,"%2.2f",tmpcfg.Qref);
	SetDlgItemText(IDC_ARROWQ,p);

	sprintf(p,"%2.2f",tmpcfg.vppe);
	SetDlgItemText(IDC_VPPE,p);

	sprintf(p,"%2.2f",tmpcfg.Iref);
	SetDlgItemText(IDC_ARROWI,p);
	sprintf(p,"%2.2f",tmpcfg.gen3dminp);
	SetDlgItemText(IDC_GEN3DMINP,p);
	//检查旧版本的系统颜色(此段程序将来需要删除)
	j=0;
	for(i=0;i<10;i++)
	{
		if(tmpcfg.syscolor[i]==0) j++;
	}
	if(j>5) //有一半以上的颜色未配置，则设置缺省值
	{
		for(i=0;i<21;i++)	tmpcfg.syscolor[i]=scr[i];
		
	}
	if(tmpcfg.ver<0x1001) for(i=0;i<5;i++)	tmpcfg.sencolor[i]=sencr[i];
	//////////////////////////////////
	if(tmpcfg.first==0){ //第一次设置缺省值
		for(i=0;i<6;i++)    SetDefaultval(i);
		for(i=0;i<20;i++) 	tmpcfg.syscolor[i]=scr[i];
	}
	i=tmpcfg.ctrtype;
	if(i<6){
		ShowVal(IDC_V1,tmpcfg.cr[i].value[0]);
		ShowVal(IDC_V2,tmpcfg.cr[i].value[1]);
		ShowVal(IDC_V3,tmpcfg.cr[i].value[2]);
		ShowVal(IDC_V5,tmpcfg.cr[i].value[4]);
		ShowVal(IDC_V4,tmpcfg.cr[i].value[3]);
	}
	i=tmpcfg.smooth;    
	i=i<1 ? 1:i;     
	i=i>30 ? 30:i;
	tmpcfg.smooth=i;
	SetDlgItemInt(IDC_SMOOTH,i);
	tmpcfg.first=1;
	curs=0;
	sens=0;
	m_cname.SetCurSel(0);
	m_senctype.SetCurSel(0);
	return TRUE; 
}

void CCfgShow::ShowColor(int id, DWORD color)
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

void CCfgShow::OnPaint() 
{
	CPaintDC dc(this);
	int i;
	i=m_dgxtype.GetCurSel();
	ShowColor(IDC_C1,tmpcfg.cr[i].color[0]);
	ShowColor(IDC_C2,tmpcfg.cr[i].color[1]);
	ShowColor(IDC_C3,tmpcfg.cr[i].color[2]);
	ShowColor(IDC_C4,tmpcfg.cr[i].color[3]);
	ShowColor(IDC_C5,tmpcfg.cr[i].color[4]);
	ShowMap();
	ShowColor(IDC_SYSCOLOR,tmpcfg.syscolor[curs]);
	ShowColor(IDC_SENCOLOR,tmpcfg.sencolor[sens]);
}

void CCfgShow::ShowVal(int id, float val)
{
	char p[100];
	sprintf(p,"%2.2f",val);
	SetDlgItemText(id,p);
}
//设置缺省颜色
void CCfgShow::OnDefaultcolor() 
{
	int i;
	i=m_dgxtype.GetCurSel();
	SetDefaultval(i);
	ShowColor(IDC_C1,tmpcfg.cr[i].color[0]);
	ShowColor(IDC_C2,tmpcfg.cr[i].color[1]);
	ShowColor(IDC_C3,tmpcfg.cr[i].color[2]);
	ShowColor(IDC_C4,tmpcfg.cr[i].color[3]);
	ShowColor(IDC_C5,tmpcfg.cr[i].color[4]);
	ShowVal(IDC_V1,tmpcfg.cr[i].value[0]);
	ShowVal(IDC_V2,tmpcfg.cr[i].value[1]);
	ShowVal(IDC_V3,tmpcfg.cr[i].value[2]);
	ShowVal(IDC_V4,tmpcfg.cr[i].value[3]);
	ShowVal(IDC_V5,tmpcfg.cr[i].value[4]);
	ShowMap();
}

void CCfgShow::OnSelchangeDgxtype() 
{
	int i;
	i=m_dgxtype.GetCurSel();
	tmpcfg.ctrtype=i;
	ShowColor(IDC_C1,tmpcfg.cr[i].color[0]);
	ShowColor(IDC_C2,tmpcfg.cr[i].color[1]);
	ShowColor(IDC_C3,tmpcfg.cr[i].color[2]);
	ShowColor(IDC_C4,tmpcfg.cr[i].color[3]);
	ShowColor(IDC_C5,tmpcfg.cr[i].color[4]);

	ShowVal(IDC_V1,tmpcfg.cr[i].value[0]);
	ShowVal(IDC_V2,tmpcfg.cr[i].value[1]);
	ShowVal(IDC_V3,tmpcfg.cr[i].value[2]);
	ShowVal(IDC_V4,tmpcfg.cr[i].value[3]);
	ShowVal(IDC_V5,tmpcfg.cr[i].value[4]);

	ShowMap();
}

void CCfgShow::OnKillfocusSmooth() 
{
	char p[100];
	int i;
	GetDlgItemText(IDC_SMOOTH,p,3);
	i=atoi(p);
	if(i>30) i=30;
	if(i<1) i=1;
	tmpcfg.smooth=i;
	SetDlgItemInt(IDC_SMOOTH,i);
}

void CCfgShow::OnKillfocusV1() 
{
	int i;
	char p[100];
	double v;
	GetDlgItemText(IDC_V1,p,12);
	v=atof(p);
	if(!CmpValue(0,(float)v)) return;
	i=tmpcfg.ctrtype;
	tmpcfg.cr[i].value[0]=(float)v;
	ShowMap();
}

void CCfgShow::OnKillfocusV2() 
{
	int i;
	char p[100];
	double v;
	GetDlgItemText(IDC_V2,p,12);
	v=atof(p);
	if(!CmpValue(1,(float)v)) return;
	i=tmpcfg.ctrtype;
	tmpcfg.cr[i].value[1]=(float)v;
	ShowMap();
}

void CCfgShow::OnKillfocusV3() 
{
	int i;
	char p[100];
	double v;
	GetDlgItemText(IDC_V3,p,12);
	v=atof(p);
	if(!CmpValue(2,(float)v)) return;
	i=tmpcfg.ctrtype;
	tmpcfg.cr[i].value[2]=(float)v;
	ShowMap();
}

void CCfgShow::OnKillfocusV4() 
{
	int i;
	char p[100];
	double v;
	GetDlgItemText(IDC_V4,p,12);
	v=atof(p);
	if(!CmpValue(3,(float)v)) return;
	i=tmpcfg.ctrtype;
	tmpcfg.cr[i].value[3]=(float)v;
	ShowMap();
}

void CCfgShow::OnKillfocusV5() 
{
	int i;
	char p[100];
	double v;
	GetDlgItemText(IDC_V5,p,12);
	v=atof(p);
	if(!CmpValue(4,(float)v)) return;
	i=tmpcfg.ctrtype;
	tmpcfg.cr[i].value[4]=(float)v;
	ShowMap();
}

void CCfgShow::OnC1() 
{
	int i;
	int r,g,b,r1,r2,g1,g2,b1,b2;
	i=tmpcfg.ctrtype;
	CColorDialog cdlg(tmpcfg.cr[tmpcfg.ctrtype].color[0],0,this);
	if(cdlg.DoModal()==IDOK){
	  tmpcfg.cr[i].color[0]=cdlg.GetColor();
	  //重新计算相临两点
	  r1=GetRValue(tmpcfg.cr[i].color[0]);
	  g1=GetGValue(tmpcfg.cr[i].color[0]);
	  b1=GetBValue(tmpcfg.cr[i].color[0]);
	  r2=GetRValue(tmpcfg.cr[i].color[2]);
	  g2=GetGValue(tmpcfg.cr[i].color[2]);
	  b2=GetBValue(tmpcfg.cr[i].color[2]);
	  r=(BYTE)((r1+r2)/2);
	  g=(BYTE)((g1+g2)/2);
	  b=(BYTE)((b1+b2)/2);
	  tmpcfg.cr[i].color[1]=RGB(r,g,b);
	  ShowColor(IDC_C1,tmpcfg.cr[tmpcfg.ctrtype].color[0]);
	  ShowColor(IDC_C2,tmpcfg.cr[tmpcfg.ctrtype].color[1]);
	  ShowMap();
	}
}

void CCfgShow::OnC2() 
{
	CColorDialog cdlg(tmpcfg.cr[tmpcfg.ctrtype].color[1],0,this);
	if(cdlg.DoModal()==IDOK){
	  tmpcfg.cr[tmpcfg.ctrtype].color[1]=cdlg.GetColor();
	  ShowColor(IDC_C2,tmpcfg.cr[tmpcfg.ctrtype].color[1]);
	  ShowMap();
	}
}

void CCfgShow::OnC3() 
{
	int i;
	int r,g,b,r1,r2,g1,g2,b1,b2;
	i=tmpcfg.ctrtype;
	CColorDialog cdlg(tmpcfg.cr[tmpcfg.ctrtype].color[2],0,this);
	if(cdlg.DoModal()==IDOK){
	  tmpcfg.cr[i].color[2]=cdlg.GetColor();
	  //重新计算相临两点
	  r1=GetRValue(tmpcfg.cr[i].color[2]);
	  g1=GetGValue(tmpcfg.cr[i].color[2]);
	  b1=GetBValue(tmpcfg.cr[i].color[2]);
	  r2=GetRValue(tmpcfg.cr[i].color[0]);
	  g2=GetGValue(tmpcfg.cr[i].color[0]);
	  b2=GetBValue(tmpcfg.cr[i].color[0]);
	  r=(BYTE)((r1+r2)/2);
	  g=(BYTE)((g1+g2)/2);
	  b=(BYTE)((b1+b2)/2);
	  tmpcfg.cr[i].color[1]=RGB(r,g,b);
	  r2=GetRValue(tmpcfg.cr[i].color[4]);
	  g2=GetGValue(tmpcfg.cr[i].color[4]);
	  b2=GetBValue(tmpcfg.cr[i].color[4]);
	  r=(BYTE)((r1+r2)/2);
	  g=(BYTE)((g1+g2)/2);
	  b=(BYTE)((b1+b2)/2);
	  tmpcfg.cr[i].color[3]=RGB(r,g,b);
	  ShowColor(IDC_C2,tmpcfg.cr[tmpcfg.ctrtype].color[1]);
	  ShowColor(IDC_C3,tmpcfg.cr[tmpcfg.ctrtype].color[2]);
	  ShowColor(IDC_C4,tmpcfg.cr[tmpcfg.ctrtype].color[3]);
	  ShowMap();
	}
}

void CCfgShow::OnC4() 
{
	CColorDialog cdlg(tmpcfg.cr[tmpcfg.ctrtype].color[3],0,this);
	if(cdlg.DoModal()==IDOK){
	  tmpcfg.cr[tmpcfg.ctrtype].color[3]=cdlg.GetColor();
	  ShowColor(IDC_C4,tmpcfg.cr[tmpcfg.ctrtype].color[3]);
	  ShowMap();
	}
}

void CCfgShow::OnC5() 
{
	int i;
	int r,g,b,r1,r2,g1,g2,b1,b2;
	i=tmpcfg.ctrtype;
	CColorDialog cdlg(tmpcfg.cr[tmpcfg.ctrtype].color[4],0,this);
	if(cdlg.DoModal()==IDOK){
	  tmpcfg.cr[tmpcfg.ctrtype].color[4]=cdlg.GetColor();
	  r1=GetRValue(tmpcfg.cr[i].color[4]);
	  g1=GetGValue(tmpcfg.cr[i].color[4]);
	  b1=GetBValue(tmpcfg.cr[i].color[4]);
	  r2=GetRValue(tmpcfg.cr[i].color[2]);
	  g2=GetGValue(tmpcfg.cr[i].color[2]);
	  b2=GetBValue(tmpcfg.cr[i].color[2]);
	  r=(BYTE)((r1+r2)/2);
	  g=(BYTE)((g1+g2)/2);
	  b=(BYTE)((b1+b2)/2);
	  tmpcfg.cr[i].color[3]=RGB(r,g,b);
	  ShowColor(IDC_C4,tmpcfg.cr[tmpcfg.ctrtype].color[3]);
	  ShowColor(IDC_C5,tmpcfg.cr[tmpcfg.ctrtype].color[4]);
	  ShowMap();
	}
}

void CCfgShow::OnOK() 
{
	char p[100];
	tmpcfg.gendyn=IsDlgButtonChecked(IDC_GENDT);
	tmpcfg.flowover=IsDlgButtonChecked(IDC_FLOWPIE);
	tmpcfg.tranbg=IsDlgButtonChecked(IDC_TRANDGX);
	tmpcfg.oneline=IsDlgButtonChecked(IDC_ONELINE);
	tmpcfg.cpu=IsDlgButtonChecked(IDC_CPU);

	GetDlgItemText(IDC_ARROWP,p,15);
	tmpcfg.Pref=(float)atof(p);
	GetDlgItemText(IDC_ARROWQ,p,15);
	tmpcfg.Qref=(float)atof(p);
	GetDlgItemText(IDC_ARROWI,p,15);
	tmpcfg.Iref=(float)atof(p);
	GetDlgItemText(IDC_VPPE,p,15);
	tmpcfg.vppe=(float)atof(p);

	GetDlgItemText(IDC_GEN3DMINP,p,15);
	tmpcfg.gen3dminp=(float)atof(p);

	if(tmpcfg.Pref<=0) {
		MessageBox("有功潮流线箭头参考功率必须大于0","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	if(tmpcfg.Qref<=0) {
		MessageBox("无功潮流线箭头参考功率必须大于0","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	if(tmpcfg.Iref<=0) {
		MessageBox("电流潮流线箭头参考电流必须大于0","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	if(tmpcfg.vppe<0||tmpcfg.vppe>=1){
		MessageBox("线路百分饼图阀值必须介于0.00-1.00之间","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	if(tmpcfg.gen3dminp<0){
		MessageBox("发电机备用显示时的最小容量必须大于或等于0","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	CDialog::OnOK();
}

void CCfgShow::SetDefaultval(int i)
{
	tmpcfg.cr[i].value[0]=(float)vl[i*5];
	tmpcfg.cr[i].value[1]=(float)vl[i*5+1];
	tmpcfg.cr[i].value[2]=(float)vl[i*5+2];
	tmpcfg.cr[i].value[3]=(float)vl[i*5+3];
	tmpcfg.cr[i].value[4]=(float)vl[i*5+4];
	tmpcfg.cr[i].color[0]=cr[i*5];
	tmpcfg.cr[i].color[1]=cr[i*5+1];
	tmpcfg.cr[i].color[2]=cr[i*5+2];
	tmpcfg.cr[i].color[3]=cr[i*5+3];
	tmpcfg.cr[i].color[4]=cr[i*5+4];
	strcpy(tmpcfg.cr[i].unit,ut[i]);
	tmpcfg.cr[i].vhow=(char)qz[i];
	tmpcfg.cr[i].emptyfill=(BYTE)fl[i];
}
//显示图谱
void CCfgShow::ShowMap()
{
	int i,j,y1,y2;
	POINT p1,p2;
	double v,h,yl;
	char p[100];
	CRect rt,rt1,rt2;
	CDIB mdc;
	CWnd *wnd;
	CTR_COLOR *cr;
	wnd=GetDlgItem(IDC_DEMOCOLOR);
	wnd->GetWindowRect(&rt);
	rt.OffsetRect(-rt.left,-rt.top);
	if(rt.Height()<2) return;
	i=m_dgxtype.GetCurSel();
	cr=(CTR_COLOR*)&tmpcfg.cr[i];
	mdc.Create(rt.Width(),rt.Height());
	mdc.FillBG(0xffffff);
	h=cr->value[0]-cr->value[4];
	if(h==0) return;
	yl=(rt.Height()-20)/h;
	y1=10;
	rt1.left=90;rt1.right=rt.Width()-4;
	rt2.left=0;rt2.right=80;
	p1.x=82;p2.x=89;
	for(j=1;j<5;j++){
		v=cr->value[j];
		if(v<cr->value[4]) v=cr->value[4];
		if(v>cr->value[0]) v=cr->value[0];
		v=v-cr->value[4];
		y2=rt.Height()-(int)(yl*v)-10;
		rt1.top=y1;
		rt1.bottom=y2+1;
		mdc.CRectc(rt1,cr->color[j-1],cr->color[j],1);
		p1.y=y1;p2.y=y1;
		mdc.CLine(p1,p2,0);
		p1.y=y2;p2.y=y2;
		mdc.CLine(p1,p2,0);
		rt2.top=y1-10;rt2.bottom=y1+10;
		sprintf(p,"%2.2f% s",cr->value[j-1],cr->unit);
		mdc.CTextOut(p,rt2,&lf,0,0,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		y1=y2;
	}
	rt2.top=y1-10;rt2.bottom=y1+10;
	sprintf(p,"%2.2f% s",cr->value[4],cr->unit);
	mdc.CTextOut(p,rt2,&lf,0,0,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
	mdc.CDraw3DRect(rt,0,0xffffff);
	CClientDC dc(wnd);
	mdc.BitBlt(dc.m_hDC,rt);
}

bool CCfgShow::CmpValue(int j,float val)
{
	int i;
	char p[100];
	i=tmpcfg.ctrtype;
	switch(j)
	{
	case 0:
		if(val>=tmpcfg.cr[i].value[1]) return true;
		sprintf(p,"输入的值应大于%2.2f",tmpcfg.cr[i].value[1]);
		MessageBox(p,"错误",MB_ICONSTOP);
		ShowVal(IDC_V1,tmpcfg.cr[i].value[0]);
		break;
	case 1:
		if(val<=tmpcfg.cr[i].value[j-1]&&val>=tmpcfg.cr[i].value[j+1]) return true;
		sprintf(p,"输入的值应介于%2.2f和%2.2f",tmpcfg.cr[i].value[j+1],tmpcfg.cr[i].value[j-1]);
		MessageBox(p,"错误",MB_ICONSTOP);
		ShowVal(IDC_V2,tmpcfg.cr[i].value[1]);
		break;
	case 2:
		if(val<=tmpcfg.cr[i].value[j-1]&&val>=tmpcfg.cr[i].value[j+1]) return true;
		sprintf(p,"输入的值应介于%2.2f和%2.2f",tmpcfg.cr[i].value[j+1],tmpcfg.cr[i].value[j-1]);
		MessageBox(p,"错误",MB_ICONSTOP);
		ShowVal(IDC_V3,tmpcfg.cr[i].value[2]);
		break;
	case 3:
		if(val<=tmpcfg.cr[i].value[j-1]&&val>=tmpcfg.cr[i].value[j+1]) return true;
		sprintf(p,"输入的值应介于%2.2f和%2.2f",tmpcfg.cr[i].value[j+1],tmpcfg.cr[i].value[j-1]);
		MessageBox(p,"错误",MB_ICONSTOP);
		ShowVal(IDC_V4,tmpcfg.cr[i].value[3]);
		break;
	case 4:
		if(val<=tmpcfg.cr[i].value[3]) return true;
		sprintf(p,"输入的值应小于%2.2f",tmpcfg.cr[i].value[3]);
		MessageBox(p,"错误",MB_ICONSTOP);
		ShowVal(IDC_V5,tmpcfg.cr[i].value[4]);
		break;
	}
	return false;
}

void CCfgShow::SetItemEnable(int id,bool enable)
{
	CWnd *wnd=GetDlgItem(id);
	if(wnd!=NULL){
		wnd->EnableWindow(enable);
	}
}



void CCfgShow::OnSelchangeCname() 
{
	int i;
	i=m_cname.GetCurSel();
	if(i==CB_ERR) return;
	curs=i;
	ShowColor(IDC_SYSCOLOR,tmpcfg.syscolor[curs]);
}

//修改颜色
void CCfgShow::OnModisc() 
{
	CColorDialog cdlg(tmpcfg.syscolor[curs],0,this);
	if(cdlg.DoModal()==IDOK){
	  tmpcfg.syscolor[curs]=cdlg.GetColor();
	  ShowColor(IDC_SYSCOLOR,tmpcfg.syscolor[curs]);
	}
}
//修改灵敏度颜色
void CCfgShow::OnModisc2() 
{
	CColorDialog cdlg(tmpcfg.sencolor[sens],0,this);
	if(cdlg.DoModal()==IDOK){
	  tmpcfg.sencolor[sens]=cdlg.GetColor();
	  ShowColor(IDC_SENCOLOR,tmpcfg.sencolor[sens]);
	}
}

void CCfgShow::OnSelchangeSenctype() 
{
	int i;
	i=m_senctype.GetCurSel();
	if(i==CB_ERR) return;
	sens=i;
	ShowColor(IDC_SENCOLOR,tmpcfg.sencolor[sens]);
}

