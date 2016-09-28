// LoginDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "LoginDlg.h"
#include "pwptdef.h"
#include "middll.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// LoginDlg dialog


LoginDlg::LoginDlg(CWnd* pParent /*=NULL*/)
	: CDialog(LoginDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(LoginDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	tm=0;
	rdbz=0;
	memset(&sur,0,sizeof(SAVUSR));
}


void LoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(LoginDlg)
	DDX_Control(pDX, IDC_USERNAME, m_nlst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(LoginDlg, CDialog)
	//{{AFX_MSG_MAP(LoginDlg)
	ON_WM_CTLCOLOR()
	ON_CBN_SELCHANGE(IDC_USERNAME, OnSelchangeUsername)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// LoginDlg message handlers
HBRUSH LoginDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_SCROLLBAR){
   		pDC->SetBkMode(TRANSPARENT);
     	HBRUSH B = CreateSolidBrush(0xffffff);
     	return (HBRUSH)B;
  	}
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

BOOL LoginDlg::OnInitDialog() 
{
	int i;
	CDialog::OnInitDialog();
	//添加你的用户列表程序，以便显示
	LoadSavCfg();
	if(rdbz==1){
		for(i=0;i<sur.usum;i++) m_nlst.AddString(sur.ulst[i].name);
		m_nlst.SelectString(0,sur.name);
		SetDlgItemText(IDC_PASSWORD,sur.password);
	}
	CheckDlgButton(IDC_SAVEUSRPW,1);
	if(!V_CanUse()){
		MessageBox("内存库平台未启动！\n请首先启动内存库平台，然后再启动本程序。","错误",MB_ICONSTOP);
		CDialog::OnCancel();
	}
	
	return TRUE; 	             
}

void LoginDlg::OnOK() 
{
	int ck,type;
	char pass[64],urnm[64];
	pass[0]=0;
	urnm[0]=0;
	GetDlgItemText(IDC_USERNAME,urnm,19);
	GetDlgItemText(IDC_PASSWORD,pass,19);
	if(!V_CheckUser(urnm, pass,type))
	{
		MessageBox("用户或密码错!","错误",MB_OK|MB_ICONSTOP);
		tm++;
		if(tm>=3) CDialog::OnCancel();
		return;
	}
	ck=IsDlgButtonChecked(IDC_SAVEUSRPW);
	if(ck==1)
	{
		strcpy(sur.name,urnm);
		strcpy(sur.password,pass);
	}
	if(ck==0)
	{
		strcpy(sur.name,urnm);
		strcpy(sur.password,"");	
	}
	AddToList(urnm);
	Savesfg();
	cobj.SetCurUser(urnm,pass,type);
	cobj.userlev=type;
	CDialog::OnOK();
}

void LoginDlg::LoadSavCfg() //读入配置
{
	FILE *fp;
	rdbz=0;
	fp=fopen("visualsystem.usr","r+b");
	if(fp==NULL) return;
	fread(&sur,sizeof(SAVUSR),1,fp);
	if(!Decode())
	{
		rdbz=0;
		fclose(fp);
		memset(&sur,0,sizeof(SAVUSR));//清零
		return;
	}
	rdbz=1;
	fclose(fp);
}

void LoginDlg::Savesfg()//保存配置
{
	FILE *fp;
	fp=fopen("visualsystem.usr","w+b");
	if(fp==NULL) return;
	Encode();//加密编码
	fwrite(&sur,sizeof(SAVUSR),1,fp);
	fclose(fp);
}

//将用户添加到列表
void LoginDlg::AddToList(char *name)
{
	int i,j;
	bool ok=false;
	for(i=0;i<sur.usum;i++){
		if(strcmp(name,sur.ulst[i].name)==0){
			ok=true;
			j=i;
		}
	}
	if(ok) return;	//如果已存在，则直接返回
	
	if(sur.usum<0) sur.usum=0;
	if(sur.usum>8) sur.usum=8; //最多8个

	for(i=7;i>0;i--){ //向后移动一个记录
		sur.ulst[i]=sur.ulst[i-1];
	}
	strcpy(sur.ulst[0].name,name);
	sur.usum++;
	if(sur.usum>8) sur.usum=8; //最多8个
	
}

//加密编码
void LoginDlg::Encode()
{
	int i;
	char *lp;
	char a;
	a=0;
	lp=(char*)&sur;
	for(i=0;i<sizeof(SAVUSR)-2;i++)
	{
		a+=lp[i];
	}
	sur.ecode=a;
	for(i=0;i<sizeof(SAVUSR)-2;i++)
	{
		lp[i]^=a;
	}
	a=0;
	for(i=0;i<sizeof(SAVUSR)-2;i++)
	{
		a^=lp[i];
	}
	sur.ccode=a;
}
//解码
bool LoginDlg::Decode()
{
	int i;
	char *lp;
	char a;
	a=0;
	lp=(char*)&sur;
	for(i=0;i<sizeof(SAVUSR)-2;i++)
	{
		a^=lp[i];
	}
	if(a!=sur.ccode) return false;
	a=sur.ecode;
	for(i=0;i<sizeof(SAVUSR)-2;i++)
	{
		lp[i]^=a;
	}
	if(sur.usum<0||sur.usum>8) return false;
	return true;
}

void LoginDlg::OnSelchangeUsername() 
{
	SetDlgItemText(IDC_PASSWORD,"");
}
