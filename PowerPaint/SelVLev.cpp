// SelVLev.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "SelVLev.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern char *lst_vl[];
/////////////////////////////////////////////////////////////////////////////
// CSelVLev dialog


CSelVLev::CSelVLev(CWnd* pParent /*=NULL*/)
	: CDialog(CSelVLev::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSelVLev)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	vl=0;
}


void CSelVLev::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSelVLev)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSelVLev, CDialog)
	//{{AFX_MSG_MAP(CSelVLev)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSelVLev message handlers

BOOL CSelVLev::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int i;
	for(i=0;i<20;i++){
		m_list.AddString(lst_vl[i]);
	}
	m_list.SetCurSel(0);
	
	return TRUE; 
}

void CSelVLev::OnOK() 
{
	int n;
	n=m_list.GetCurSel();
	if(n==LB_ERR){
		MessageBox("请选择一个电压后，再选择！");
		return;
	}
	vl=(BYTE)n;
	CDialog::OnOK();
}
