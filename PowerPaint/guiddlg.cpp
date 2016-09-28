// guiddlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "guiddlg.h"
#include "gdata.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern gdata dbm;
extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// guiddlg dialog


guiddlg::guiddlg(CWnd* pParent /*=NULL*/)
	: CDialog(guiddlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(guiddlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	tcolor=cobj.gcolor;
}


void guiddlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(guiddlg)
	DDX_Control(pDX, IDC_STYPE, m_style);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(guiddlg, CDialog)
	//{{AFX_MSG_MAP(guiddlg)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_MODIC, OnModic)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// guiddlg message handlers

BOOL guiddlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetDlgItemInt(IDC_GSIZE,cobj.gwide);
	m_style.SetCurSel(cobj.gstyle);
	
	return TRUE;  
}

void guiddlg::OnPaint() 
{
	CPaintDC dc(this); 
	DispCtlColor(IDC_COLOR,tcolor);
}

void guiddlg::OnOK() 
{
	int s;
	s=GetDlgItemInt(IDC_GSIZE);
	if(s<10){
		MessageBox("网格线太小，会影响绘图视觉效果！/n请重新输入网格大小");
		return;
	}
	if(s>400){
		MessageBox("太大的网格线达不到绘图定位目的！/n请重新输入网格大小");
		return;
	}
	cobj.gwide=s;
	cobj.gstyle=m_style.GetCurSel();
	cobj.gcolor=tcolor;
	CDialog::OnOK();
}

void guiddlg::OnModic() 
{
	CColorDialog cdlg(tcolor,0,this);
	if(cdlg.DoModal()==IDOK){
	 tcolor=cdlg.GetColor();
	 DispCtlColor(IDC_COLOR,tcolor);
	}
}


void guiddlg::DispCtlColor(int id, int color)
{
	RECT rt;
	HWND hwnd;
	HDC hdc;
	rt.left=0;rt.top=0;rt.right=36;rt.bottom=20;
	hwnd=::GetDlgItem(m_hWnd,id);
	hdc=::GetDC(hwnd);
	::UpdateWindow(hwnd);
	CDC dc;
	dc.Attach(hdc);
	dc.FillSolidRect(&rt,color);
	dc.Draw3dRect(&rt,0,0xffffff);
	dc.Detach();
	::ReleaseDC(hwnd,hdc);
}
