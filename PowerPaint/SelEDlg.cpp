// SelEDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "SelEDlg.h"
#include "comobj.h"
#include "gdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern comobj cobj;
extern gdata dbm;
/////////////////////////////////////////////////////////////////////////////
// SelEDlg dialog


SelEDlg::SelEDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SelEDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SelEDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	w=1;
	h=1;
	elsum=0;
	selid=-1;
	mdc.Create(1,1);
}


void SelEDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SelEDlg)
	DDX_Control(pDX, IDC_SCROL, m_scr);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SelEDlg, CDialog)
	//{{AFX_MSG_MAP(SelEDlg)
	ON_WM_PAINT()
	ON_WM_HSCROLL()
	ON_WM_SIZE()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SelEDlg message handlers

BOOL SelEDlg::OnInitDialog() 
{
	int i,n;
	CDialog::OnInitDialog();
	dx=0;
	selpic=0;
	//取符合条件的图元，只取站
	elsum=0;
	for(i=0;i<cobj.egpsum;i++)
	{
		if(cobj.egp[i].type==2){
			el[elsum].jlh=i;
			el[elsum].id=cobj.egp[i].id;
			elsum++;
		}
		if(elsum>=128) break;
	}
	if(elsum>5) n=elsum-5;
	else n=0;
	m_scr.SetScrollRange(0,n);
	m_scr.SetScrollPos(0);
	if(elsum>0) selid=el[0].id;else selid=-1;
	return TRUE; 
}

void SelEDlg::OnPaint() 
{
	CPaintDC dc1(this); 
	ShowEle();
}

void SelEDlg::ShowEle()
{
	CRect rt,rt1;
	int i,j,k,w1,h1,m,t;
	CWnd *wnd;
	wnd=GetDlgItem(IDC_TY);
	if(wnd==NULL) return;
	wnd->GetWindowRect(&rt);
	w1=rt.Width();
	h1=rt.Height();
	if(w1>w||h1>h){
		mdc.SizeChange(w1,h1);
		w=w1;
		h=h1;
	}
	CClientDC dc(wnd);
	rt=CRect(0,0,w,h);
	mdc.FillBG(0xc0c0c0);
	mdc.CDraw3DRect(rt,0x7f7f7f,0xffffff);
	m=w/5;

	//显示图元
	for(i=0;i<5;i++)
	{
		j=dx+i;
		if(j>=elsum) break;
		k=el[j].jlh;
		if(k>cobj.egpsum||k<0) break;
		rt1.left=i*m+10;
		rt1.top=10;
		rt1.right=rt1.left+m-20;
		rt1.bottom=h-10;
		t=cobj.typeidx[k];
		if(k==selpic){
			mdc.FillSolidRect(rt1,0);
			mdc.CDraw3DRect(rt1,0xffffff,0xffffff);
			dbm.PreShowEGP(mdc,t,rt1,0,0xffffff,1);
		}
		else  {
			mdc.FillSolidRect(rt1,0xff0000);
			mdc.CDraw3DRect(rt1,0,0);
			dbm.PreShowEGP(mdc,t,rt1,0,0,1);
		}
	}
	mdc.BitBlt(dc.m_hDC,rt);
}

void SelEDlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	CRect rt;
    int n,sx,odx;	
	sx=cobj.egpsum-1;
	odx=dx;
	switch(nSBCode){
	case SB_LINERIGHT: 
		 dx=dx<sx-1 ? dx+1:sx;break;
	case SB_LINELEFT:
		 dx=dx>0 ? dx-1:0;break;
    case SB_PAGEDOWN:
		 dx=dx<sx-5 ? dx+5:sx;
		 break;
	case SB_PAGEUP:
		 dx=dx>5 ?  dx-5:0;
		 break;
	case SB_THUMBTRACK:
	case SB_THUMBPOSITION:
		dx=nPos;break;
	};
	n=odx-dx;
	m_scr.SetScrollPos(dx);
	if(n!=0){
		ShowEle();
	};	
	CDialog::OnHScroll(nSBCode, nPos, pScrollBar);
}

void SelEDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int i,j,m,k;
	CRect rt;
	m=w/5;
	for(i=0;i<5;i++)
	{
		j=dx+i;
		if(j>=elsum) break;
		k=el[j].jlh;
		rt.left=i*m+10;
		rt.top=10;
		rt.right=rt.left+m-20;
		rt.bottom=h-10;
		if(rt.PtInRect(point)){
			selpic=k;
			selid=el[j].id;
			ShowEle();
			break;
		}
	}
	CDialog::OnLButtonDown(nFlags, point);
}
