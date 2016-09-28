// PrtMode.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "PrtMode.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CPrtMode dialog


CPrtMode::CPrtMode(PMODE *lppm,CWnd* pParent /*=NULL*/)
	: CDialog(CPrtMode::IDD, pParent)
{
	//{{AFX_DATA_INIT(CPrtMode)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	pm=lppm;
}


void CPrtMode::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CPrtMode)
	DDX_Control(pDX, IDC_COMBO2, m_com2);
	DDX_Control(pDX, IDC_COMBO1, m_com1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CPrtMode, CDialog)
	//{{AFX_MSG_MAP(CPrtMode)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPrtMode message handlers

HBRUSH CPrtMode::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_SCROLLBAR){
   		pDC->SetBkMode(TRANSPARENT);
     	HBRUSH B = CreateSolidBrush(0xffffff);
     	return (HBRUSH)B;
  	}
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

BOOL CPrtMode::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	m_com1.SetCurSel(0);
	m_com2.SetCurSel(0);
	
	return TRUE; 
}

void CPrtMode::OnOK() 
{
	int a,b;
	a=m_com1.GetCurSel();
	b=m_com2.GetCurSel();
	pm->mode=a;
	pm->px=b;
	CDialog::OnOK();
}
