// PatrDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "PatrDlg.h"
#include "gdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern gdata dbm;
/////////////////////////////////////////////////////////////////////////////
// PatrDlg dialog


PatrDlg::PatrDlg(CWnd* pParent /*=NULL*/)
	: CDialog(PatrDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(PatrDlg)
	//}}AFX_DATA_INIT
}


void PatrDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(PatrDlg)
	DDX_Control(pDX, IDC_TYPE, m_type);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(PatrDlg, CDialog)
	//{{AFX_MSG_MAP(PatrDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// PatrDlg message handlers

BOOL PatrDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_NAME,dbm.cpage->head.Name);
	m_type.SetCurSel(dbm.cpage->head.type);
	SetDlgItemInt(IDC_WIDTH,dbm.cpage->head.width);
	SetDlgItemInt(IDC_HEIGHT,dbm.cpage->head.height);
	CheckDlgButton(IDC_SHOWBYRT,dbm.cpage->head.showbyrt);
	CheckDlgButton(IDC_ENABLESEN,dbm.cpage->head.senflag);
	//验证数据
	if(dbm.cpage->head.x1>dbm.cpage->head.x2) 
	{
		dbm.cpage->head.x1=0;
		dbm.cpage->head.x2=1024;
	}
	if(dbm.cpage->head.y1>dbm.cpage->head.y2)
	{
		dbm.cpage->head.y1=0;
		dbm.cpage->head.y2=768;
	}
	SetDlgItemInt(IDC_X1,dbm.cpage->head.x1);
	SetDlgItemInt(IDC_Y1,dbm.cpage->head.y1);
	SetDlgItemInt(IDC_X2,dbm.cpage->head.x2);
	SetDlgItemInt(IDC_Y2,dbm.cpage->head.y2);
	return TRUE; 
}

void PatrDlg::OnOK() 
{
	int w,h,j;
	j=dbm.curpage;
	GetDlgItemText(IDC_NAME,dbm.cpage->head.Name,32);
	w=GetDlgItemInt(IDC_WIDTH);
	h=GetDlgItemInt(IDC_HEIGHT);
	w=w<200 ? 200:w;
	w=w>15000 ? 15000:w;
	h=h<200  ? 200:h;
	h=h>6000 ? 6000:h;
	dbm.cpage->head.width=w;
	dbm.cpage->head.height=h;
	dbm.cpage->head.type=m_type.GetCurSel();
	dbm.cpage->head.showbyrt=IsDlgButtonChecked(IDC_SHOWBYRT);
	dbm.cpage->head.senflag=IsDlgButtonChecked(IDC_ENABLESEN);
	dbm.cpage->head.x1=GetDlgItemInt(IDC_X1);
	dbm.cpage->head.y1=GetDlgItemInt(IDC_Y1);
	dbm.cpage->head.x2=GetDlgItemInt(IDC_X2);
	dbm.cpage->head.y2=GetDlgItemInt(IDC_Y2);
	dbm.drawbz=1; //设置为编辑发生变化
	CDialog::OnOK();
}

