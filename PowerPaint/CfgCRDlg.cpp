// CfgCRDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "CfgCRDlg.h"
#include "gdata.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern gdata dbm;
extern comobj cobj;
extern char *lst_vl[];
/////////////////////////////////////////////////////////////////////////////
// CCfgCRDlg dialog


CCfgCRDlg::CCfgCRDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCfgCRDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CCfgCRDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CCfgCRDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CCfgCRDlg)
	DDX_Control(pDX, IDC_VLNAME, m_vn);
	DDX_Control(pDX, IDC_COLORR, m_r);
	DDX_Control(pDX, IDC_COLORG, m_g);
	DDX_Control(pDX, IDC_COLORB, m_b);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CCfgCRDlg, CDialog)
	//{{AFX_MSG_MAP(CCfgCRDlg)
	ON_WM_PAINT()
	ON_EN_CHANGE(IDC_COLORB, OnChangeColorb)
	ON_EN_CHANGE(IDC_COLORG, OnChangeColorg)
	ON_EN_CHANGE(IDC_COLORR, OnChangeColorr)
	ON_BN_CLICKED(IDC_PALLT, OnPallt)
	ON_LBN_SELCHANGE(IDC_VLNAME, OnSelchangeVlname)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CCfgCRDlg message handlers


void CCfgCRDlg::ShowColor()
{
	CWnd *wnd=GetDlgItem(IDC_SCOLOR);
	wnd->InvalidateRect(NULL);
	wnd->UpdateData();
	CClientDC dc(wnd);
	dc.FillSolidRect(CRect(0,0,50,95),cobj.vcolor[cursel]);
	dc.Draw3dRect(CRect(0,0,50,95),0,0xffffff);

}

void CCfgCRDlg::DWTORGB(DWORD cr)
{
	R=(BYTE)(cr&0xff);
	G=(BYTE)((cr>>8)&0xff);
	B=(BYTE)((cr>>16)&0xff);
}

BOOL CCfgCRDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	int i;
	for(i=0;i<20;i++){
		m_vn.AddString(lst_vl[i]);
	}
	m_vn.SetCurSel(0);
	cursel=0;
	DWTORGB(cobj.vcolor[cursel]);
	SetDlgItemInt(IDC_COLORR,R);
	SetDlgItemInt(IDC_COLORG,G);
	SetDlgItemInt(IDC_COLORB,B);
	ShowColor();
	
	return TRUE;  
}

void CCfgCRDlg::OnPaint() 
{
	CPaintDC dc(this);
	ShowColor();
}

void CCfgCRDlg::OnChangeColorb() 
{
	int i;
	char p[100];
	GetDlgItemText(IDC_COLORB,p,4);
	i=atoi(p);
	B=i>255 ? 255:(BYTE)i;
	cobj.vcolor[cursel]=RGB(R,G,B);
	ShowColor();
	
}

void CCfgCRDlg::OnChangeColorg() 
{
	int i;
	char p[100];
	GetDlgItemText(IDC_COLORG,p,4);
	i=atoi(p);
	G=i>255 ? 255:(BYTE)i;
	cobj.vcolor[cursel]=RGB(R,G,B);
	ShowColor();
	
}

void CCfgCRDlg::OnChangeColorr() 
{
	int i;
	char p[100];
	GetDlgItemText(IDC_COLORR,p,4);
	i=atoi(p);
	R=i>255 ? 255:(BYTE)i;
	cobj.vcolor[cursel]=RGB(R,G,B);
	ShowColor();
	
}

void CCfgCRDlg::OnPallt() 
{
	CColorDialog cdlg(cobj.vcolor[cursel],0,this);
	if(cdlg.DoModal()==IDOK){
		cobj.vcolor[cursel]=cdlg.GetColor();
		DWTORGB(cobj.vcolor[cursel]);
		SetDlgItemInt(IDC_COLORR,R);
		SetDlgItemInt(IDC_COLORG,G);
		SetDlgItemInt(IDC_COLORB,B);
		ShowColor();
	}
}

void CCfgCRDlg::OnSelchangeVlname() 
{
	cursel=m_vn.GetCurSel();
	DWTORGB(cobj.vcolor[cursel]);
	SetDlgItemInt(IDC_COLORR,R);
	SetDlgItemInt(IDC_COLORG,G);
	SetDlgItemInt(IDC_COLORB,B);
	ShowColor();
}

void CCfgCRDlg::OnOK() 
{
	bool rtn=cobj.SetColor(lst_vl[cursel],R,G,B);
	if(rtn){
		MessageBox("成功修改颜色表！","修改颜色",MB_OK);
	}else{
		MessageBox("未能成功修改颜色表！","错误",MB_OK|MB_ICONSTOP);
	}
}
