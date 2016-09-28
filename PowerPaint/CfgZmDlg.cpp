// CfgZmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "CfgZmDlg.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj  cobj;

BOOL GetPw0ile(char *filename,char *path,int &pageno,HWND hWndParent);
/////////////////////////////////////////////////////////////////////////////
// CCfgZmDlg dialog


CCfgZmDlg::CCfgZmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCfgZmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCfgZmDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCfgZmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCfgZmDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCfgZmDlg, CDialog)
	//{{AFX_MSG_MAP(CCfgZmDlg)
	ON_BN_CLICKED(IDC_FROMFM1, OnFromfm1)
	ON_BN_CLICKED(IDC_FROMFM2, OnFromfm2)
	ON_BN_CLICKED(IDC_ZOOMIN, OnZoomin)
	ON_BN_CLICKED(IDC_ZOOMOUT, OnZoomout)
	ON_BN_CLICKED(IDC_DEFZM1, OnDefzm1)
	ON_BN_CLICKED(IDC_DEFZM2, OnDefzm2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCfgZmDlg message handlers

BOOL CCfgZmDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	char p[100];
	CheckDlgButton(IDC_ZOOMOUT,tmp.enableout);
	CheckDlgButton(IDC_ZOOMIN,tmp.enablein);
	CheckDlgButton(IDC_DEFZM1,tmp.defzm1);
	CheckDlgButton(IDC_DEFZM2,tmp.defzm2);
	sprintf(p,"%2.2f",tmp.outstart);
	SetDlgItemText(IDC_FDBS1,p);
	sprintf(p,"%2.2f",tmp.instart);
	SetDlgItemText(IDC_FDBS2,p);
	SetDlgItemText(IDC_FNM1,tmp.outname);
	SetDlgItemText(IDC_FNM2,tmp.inname);
	SetDlgItemInt(IDC_HM1,tmp.outno);
	SetDlgItemInt(IDC_HM2,tmp.inno);
	sprintf(p,"%2.2f",tmp.zm1);
	SetDlgItemText(IDC_ZM1,p);
	sprintf(p,"%2.2f",tmp.zm2);
	SetDlgItemText(IDC_ZM2,p);
	EnableAll();
	return TRUE;  
}

//来自文件
void CCfgZmDlg::OnFromfm1() 
{
	int pno;
	char *lp;
	char fnm[256],path[256];
	strcpy(path,cobj.path[1].path);
	if(!GetPw0ile(fnm,path,pno,m_hWnd)) return;
	lp=strrchr(fnm,'\\');
	if(lp!=NULL) lp++;
	else lp=fnm;
	SetDlgItemText(IDC_FNM1,lp);
	SetDlgItemInt(IDC_HM1,pno);
}
//来自文件
void CCfgZmDlg::OnFromfm2() 
{
	int pno;
	char *lp;
	char fnm[256],path[256];
	strcpy(path,cobj.path[1].path);
	if(!GetPw0ile(fnm,path,pno,m_hWnd)) return;
	lp=strrchr(fnm,'\\');
	if(lp!=NULL) lp++;
	else lp=fnm;
	SetDlgItemText(IDC_FNM2,lp);
	SetDlgItemInt(IDC_HM2,pno);
}

void CCfgZmDlg::OnOK() 
{
	char p[100];
	memset(&tmp,0,sizeof(N_APDINFO));
	tmp.enableout=IsDlgButtonChecked(IDC_ZOOMOUT);
	tmp.enablein=IsDlgButtonChecked(IDC_ZOOMIN);
	tmp.defzm1=IsDlgButtonChecked(IDC_DEFZM1);
	tmp.defzm2=IsDlgButtonChecked(IDC_DEFZM2);
	if(tmp.enableout==1)
	{
		GetDlgItemText(IDC_FDBS1,p,12);
		tmp.outstart=(float)atof(p);
		if(tmp.outstart<=0)
		{
			MessageBox("放大控制的放大倍数<=0\n请重新输入。","错误",MB_OK|MB_ICONSTOP);
			return;
		}
		GetDlgItemText(IDC_FNM1,tmp.outname,24);
		if(strlen(tmp.outname)<4)
		{
			MessageBox("放大控制文件名有错！\n请重新输入。","错误",MB_OK|MB_ICONSTOP);
			return;
		}
		tmp.outno=GetDlgItemInt(IDC_HM1);
	}
	if(tmp.enablein==1){
		GetDlgItemText(IDC_FDBS2,p,12);
		tmp.instart=(float)atof(p);
		if(tmp.instart<=0){
			MessageBox("缩小控制的放大倍数<=0\n请重新输入。","错误",MB_OK|MB_ICONSTOP);
			return;
		}
		GetDlgItemText(IDC_FNM2,tmp.inname,24);
		if(strlen(tmp.inname)<4){
			MessageBox("缩小控制文件名有错！\n请重新输入。","错误",MB_OK|MB_ICONSTOP);
			return;
		}
		tmp.inno=GetDlgItemInt(IDC_HM2);
	}
	if(tmp.enableout==1&&tmp.enablein==1){
		if(tmp.instart>tmp.outstart){
			MessageBox("一般来讲,放大控制倍数应大于缩小控制倍数！\n请重新输入。","错误",MB_OK|MB_ICONSTOP);
			return;
		}
	}
	if(tmp.defzm1==1&&tmp.enableout==1){
		GetDlgItemText(IDC_ZM1,p,12);
		tmp.zm1=(float)atof(p);
		if(tmp.zm1<=0){
			MessageBox("放大指定的放大倍数<=0\n请重新输入。","错误",MB_OK|MB_ICONSTOP);
			return;
		}

	}
	if(tmp.defzm2==1&&tmp.enablein==1){
		GetDlgItemText(IDC_ZM2,p,12);
		tmp.zm2=(float)atof(p);
		if(tmp.zm2<=0){
			MessageBox("缩小指定的放大倍数<=0\n请重新输入。","错误",MB_OK|MB_ICONSTOP);
			return;
		}
	}
	CDialog::OnOK();
}

void CCfgZmDlg::SetItemEnable(int id,bool enable)
{
	CWnd *wnd=GetDlgItem(id);
	if(wnd!=NULL){
		wnd->EnableWindow(enable);
	}
}

void CCfgZmDlg::EnableAll()
{
	SetItemEnable(IDC_FDBS1,tmp.enableout==0 ? false:true);
	SetItemEnable(IDC_FDBS2,tmp.enablein==0 ? false:true);
	SetItemEnable(IDC_FNM1,tmp.enableout==0 ? false:true);
	SetItemEnable(IDC_FNM2,tmp.enablein==0 ? false:true);
	SetItemEnable(IDC_HM1,tmp.enableout==0 ? false:true);
	SetItemEnable(IDC_HM2,tmp.enablein==0 ? false:true);
	SetItemEnable(IDC_FROMFM1,tmp.enableout==0 ? false:true);
	SetItemEnable(IDC_FROMFM2,tmp.enablein==0 ? false:true);
	SetItemEnable(IDC_ZM1,tmp.defzm1==0 ? false:true);
	SetItemEnable(IDC_ZM2,tmp.defzm2==0 ? false:true);
}

void CCfgZmDlg::OnZoomin() 
{
	tmp.enablein=IsDlgButtonChecked(IDC_ZOOMIN);
	EnableAll();
}

void CCfgZmDlg::OnZoomout() 
{
	tmp.enableout=IsDlgButtonChecked(IDC_ZOOMOUT);
	EnableAll();
}

void CCfgZmDlg::OnDefzm1() 
{
	tmp.defzm1=IsDlgButtonChecked(IDC_DEFZM1);
	EnableAll();
}

void CCfgZmDlg::OnDefzm2() 
{
	tmp.defzm2=IsDlgButtonChecked(IDC_DEFZM2);
	EnableAll();
}
