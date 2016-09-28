// GetNMDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "GetNMDlg.h"
#include "middll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// GetNMDlg dialog


GetNMDlg::GetNMDlg(CWnd* pParent /*=NULL*/)
	: CDialog(GetNMDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(GetNMDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	dbm=NULL;
}


void GetNMDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(GetNMDlg)
	DDX_Control(pDX, IDC_NUM, m_num);
	DDX_Control(pDX, IDC_PROGRESS1, m_prg);
	DDX_Control(pDX, IDC_PNAME, m_pname);
	DDX_Control(pDX, IDC_LNAME, m_lname);
	DDX_Control(pDX, IDC_DNAME, m_dname);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(GetNMDlg, CDialog)
	//{{AFX_MSG_MAP(GetNMDlg)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// GetNMDlg message handlers

BOOL GetNMDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetTimer(100,200,NULL);
	return TRUE;
}

void GetNMDlg::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent==100)
	{
		KillTimer(100);
		RunGet();
	}
	CDialog::OnTimer(nIDEvent);
}

void GetNMDlg::RunGet()
{
	int i,j,k,m,djlh;
	SELECTDEV sd;
	BYTE type,subtype,vl;
	char dev_name[25];
	char p[100];
	BASE0 *obj;
	strcpy(sd.dbname,"visualpw");
	sd.type=2;
	for(i=0;i<dbm->pagesum;i++)
	{
		m_pname.SetWindowText(dbm->page[i].head.Name);
		for(j=0;j<dbm->page[i].laysum;j++)
		{
			sprintf(p,"%d层",j);
			m_lname.SetWindowText(p);
			obj=dbm->page[i].layer[j].obj;
			m=dbm->page[i].layer[j].objnum;
			m_prg.SetRange(0,m);
			for(k=0;k<m;k++)
			{
				m_prg.SetPos(k);
				sprintf(p,"%d/%d",k,m);
				m_num.SetWindowText(p);
				if(!obj[k].GetDevType(type,subtype,vl,dev_name,djlh)) continue;
				if(type!=2) continue;
				if(djlh==-1) continue;
				//调用数据源设置程序		
				sd.name[0]=0;
				sd.did=djlh;
				sd.dtype=subtype;
				if(GetNameByID(sd)){
				   obj[k].SetDevSource(sd.name,sd.did);	
				   sprintf(p,"更新设备id=%d 名字=%s",sd.did,sd.name);
				   m_dname.SetWindowText(p);
				}
				//Sleep(1);
			}
		}
	}
	dbm->editbz=0;
	CDialog::OnCancel();
}
