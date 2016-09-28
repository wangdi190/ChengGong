// TextDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "TextDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// TextDlg dialog


TextDlg::TextDlg(char *str,int n,CWnd* pParent /*=NULL*/)
	: CDialog(TextDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(TextDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	p=str;
	count=n;
}


void TextDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(TextDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(TextDlg, CDialog)
	//{{AFX_MSG_MAP(TextDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// TextDlg message handlers

BOOL TextDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	SetDlgItemText(IDC_TEXT,p);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void TextDlg::OnOK() 
{
	GetDlgItemText(IDC_TEXT,p,count);	
	CDialog::OnOK();
}
