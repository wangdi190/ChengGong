// prtmode.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "prtmode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// prtmode dialog


prtmode::prtmode(PMODE *lppm,CWnd* pParent /*=NULL*/)
	: CDialog(prtmode::IDD, pParent)
{
	//{{AFX_DATA_INIT(prtmode)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pm=lppm;
}


void prtmode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(prtmode)
	DDX_Control(pDX, IDC_COMBO2, m_com2);
	DDX_Control(pDX, IDC_COMBO1, m_com1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(prtmode, CDialog)
	//{{AFX_MSG_MAP(prtmode)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// prtmode message handlers
HBRUSH prtmode::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_SCROLLBAR){
   		pDC->SetBkMode(TRANSPARENT);
     	HBRUSH B = CreateSolidBrush(0xffffff);
     	return (HBRUSH)B;
  	}
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

BOOL prtmode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	m_com1.SetCurSel(0);
	m_com2.SetCurSel(0);
		
	
	return TRUE;
}

void prtmode::OnOK()
{
	int a,b;
	a=m_com1.GetCurSel();
	b=m_com2.GetCurSel();
	pm->mode=a;
	pm->px=b;
	
	CDialog::OnOK();
}
