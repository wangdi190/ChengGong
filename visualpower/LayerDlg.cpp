// LayerDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "LayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CLayerDlg dialog


CLayerDlg::CLayerDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CLayerDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CLayerDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CLayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CLayerDlg)
	DDX_Control(pDX, IDC_LIST1, m_list);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CLayerDlg, CDialog)
	//{{AFX_MSG_MAP(CLayerDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CLayerDlg message handlers
HBRUSH CLayerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_SCROLLBAR) {
   		pDC->SetBkMode(TRANSPARENT);
     	HBRUSH B = CreateSolidBrush(0xffffff); 
     	return (HBRUSH)B;
  	} 
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

BOOL CLayerDlg::OnInitDialog() 
{
	int i;
	char p[100];
	CDialog::OnInitDialog();
	m_list.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_GRIDLINES|LVS_EX_CHECKBOXES|LVS_EX_MULTIWORKAREAS);
	m_list.InsertColumn(0,"显示状态",LVCFMT_LEFT,80,0);
	m_list.InsertColumn(1,"层名称",LVCFMT_LEFT,175,0);
	m_list.InsertColumn(2,"对象个数",LVCFMT_LEFT,80,0);
	for(i=0;i<dbm->page.laysum;i++){
	  m_list.InsertItem(i,"显示");
	  m_list.SetItemText(i,1,dbm->page.layer[i].name);
	  sprintf(p,"%d",dbm->page.layer[i].objnum);
	  m_list.SetItemText(i,2,p);
	  if(dbm->page.layer[i].show==0) m_list.SetCheck(i,false);
	  else  m_list.SetCheck(i,true);
	}
	return TRUE;
}

void CLayerDlg::OnOK() 
{
	int i;
	for(i=0;i<dbm->page.laysum;i++){
		dbm->page.layer[i].show=m_list.GetCheck(i);
	}
	CDialog::OnOK();
}

void CLayerDlg::EnablePush(int id, bool enable)
{
	CWnd *hw=GetDlgItem(id);
	if(hw!=NULL) hw->EnableWindow(enable);
}
