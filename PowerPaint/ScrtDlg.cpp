// ScrtDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "ScrtDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// ScrtDlg dialog


ScrtDlg::ScrtDlg(char *str,int n,CWnd* pParent /*=NULL*/)
	: CDialog(ScrtDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(ScrtDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	p=str;
	count=n;
}


void ScrtDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(ScrtDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(ScrtDlg, CDialog)
	//{{AFX_MSG_MAP(ScrtDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// ScrtDlg message handlers

BOOL ScrtDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetDlgItemText(IDC_TEXT,p);
	
	return TRUE; 
}

void ScrtDlg::OnOK() 
{
	GetDlgItemText(IDC_TEXT,p,count);
	CDialog::OnOK();
}
