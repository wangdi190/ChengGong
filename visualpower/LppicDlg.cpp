// LppicDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "LppicDlg.h"
#include "comobj.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj  cobj;	//公共对象
BOOL GetPw0File(char *filename,char *path,int &pageno,HWND hWndParent);
/////////////////////////////////////////////////////////////////////////////
// CLppicDlg dialog


CLppicDlg::CLppicDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLppicDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLppicDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLppicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLppicDlg)
	DDX_Control(pDX, IDC_LIST1, m_lst);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLppicDlg, CDialog)
	//{{AFX_MSG_MAP(CLppicDlg)
	ON_BN_CLICKED(IDC_ADDNEW, OnAddnew)
	ON_BN_CLICKED(IDC_DELSEL, OnDelsel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLppicDlg message handlers

BOOL CLppicDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetList();
	CheckDlgButton(IDC_AUTOLOOP,tmp.run);
	SetDlgItemInt(IDC_JGSJ,tmp.jgsj);
	
	return TRUE;
}

void CLppicDlg::OnAddnew() 
{
	int i,pageno;
	char fnm[512],path[256],*lp;
	if(tmp.psum>=16)
	{
		MessageBox("循环画面已超过16个，不能添加新的画面！","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	strcpy(path,cobj.runpath);
	if(!GetPw0File(fnm,path,pageno,m_hWnd)) return;
	lp=strrchr(fnm,'\\');
	if(lp==NULL) return;
	lp++;
	i=tmp.psum;
	strcpy(tmp.pnm[i].picname,lp);
	tmp.pnm[i].picno=pageno;
	tmp.psum++;	
	SetList();
}

void CLppicDlg::OnDelsel() 
{
	int i,k;
	if(tmp.psum<=0) return;
	k=m_lst.GetCurSel();
	if(k==LB_ERR)
	{
		MessageBox("先选择一个画面然后再删除！","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	for(i=k;i<tmp.psum-1;i++)
	{
		tmp.pnm[i]=tmp.pnm[i+1];
	}
	tmp.psum--;
	SetList();
}

void CLppicDlg::OnOK() 
{
	tmp.jgsj=GetDlgItemInt(IDC_JGSJ);
	if(tmp.jgsj<5)
	{
		MessageBox("自动播放时间间隔必须不小于5秒","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	tmp.run=IsDlgButtonChecked(IDC_AUTOLOOP);
	CDialog::OnOK();
}

void CLppicDlg::SetList()
{
	int i;
	m_lst.ResetContent();
	for(i=0;i<tmp.psum;i++)
	{
		m_lst.AddString(tmp.pnm[i].picname);
	}
}