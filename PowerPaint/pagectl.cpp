// pagectl.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "pagectl.h"
#include "comobj.h"
#include "gdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern gdata dbm;
extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// pagectl

pagectl::pagectl()
{
	mdc.Create(1,1);
	dx=0;
}

pagectl::~pagectl()
{
}


BEGIN_MESSAGE_MAP(pagectl, CWnd)
	//{{AFX_MSG_MAP(pagectl)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CREATE()
	ON_COMMAND(ID_PAGEDOWN, OnPagedown)
	ON_COMMAND(ID_PAGEUP, OnPageup)
	ON_COMMAND(ID_LEFT, OnLeft)
	ON_COMMAND(ID_RIGHT, OnRight)
	ON_UPDATE_COMMAND_UI(ID_PAGEDOWN, OnUpdatePagedown)
	ON_UPDATE_COMMAND_UI(ID_PAGEUP, OnUpdatePageup)
	ON_UPDATE_COMMAND_UI(ID_RIGHT, OnUpdateRight)
	ON_UPDATE_COMMAND_UI(ID_LEFT, OnUpdateLeft)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY_EX(TTN_NEEDTEXT, 0,OnTip)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// pagectl message handlers

BOOL pagectl::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	//cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

void pagectl::OnPaint() 
{
	CPaintDC dc(this); 
	ShowOnMdc();
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx-108,wy));
}

void pagectl::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	tb1.MoveWindow(wx-108,0,wx,wy);
	if((wx-108)>0) mdc.SizeChange(wx-108,wy);
}


int pagectl::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	tb1.CreateEx(this,TBSTYLE_TRANSPARENT |TBSTYLE_FLAT|TBSTYLE_TOOLTIPS|TBSTYLE_LIST,WS_CHILD|WS_VISIBLE|CBRS_TOP);
	tb1.LoadToolBar(IDR_CTLBAR);
	return 0;
}

void pagectl::OnUpdatePagedown(CCmdUI* pCmdUI)	{pCmdUI->Enable(dx<dbm.pagesum-5 ? 1:0);}
void pagectl::OnUpdatePageup(CCmdUI* pCmdUI)	{pCmdUI->Enable(dx>0 ? 1:0);}
void pagectl::OnUpdateRight(CCmdUI* pCmdUI)		{pCmdUI->Enable(dx<dbm.pagesum-1 ? 1:0);}
void pagectl::OnUpdateLeft(CCmdUI* pCmdUI)		{pCmdUI->Enable(dx>0 ? 1:0);}


//在内存中先画
void pagectl::ShowOnMdc()
{
	int i,w;
	char p[100];
	DWORD c1;
	SIZE sz;
	CRect rt;
	LOGFONT lf;
	c1=GetSysColor(COLOR_3DFACE);
	mdc.FillBG(0x7f7f7f);

	mdc.CRectc(CRect(0,wy-4,wx,wy),c1,c1,0);
	mdc.CLine(CPoint(0,0),CPoint(wx-108,0),0);
	mdc.CLine(CPoint(0,wy-4),CPoint(wx,wy-4),0xffffff);
	mdc.CLine(CPoint(0,0),CPoint(0,wy-5),0);
	w=0;
	lf=cobj.sysfont;
	lf.lfHeight=14;
	lf.lfWidth=7;
	//显示页面
	for(i=dx;i<dbm.pagesum;i++){
		sz=GLDGetTextSize(mdc.m_hDC,&cobj.sysfont,dbm.page[i].head.Name);
		if(i==dbm.curpage){
			rt.left=w-2;
			rt.top=2;
			rt.bottom=wy-3;
			rt.right=rt.left+sz.cx+36;
			mdc.CRectc(rt,c1,c1,0);
			sprintf(p,"%d-%s",i,dbm.page[i].head.Name);
			mdc.CTextOut(p,rt,&lf,0,0,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
			rt.bottom--;
			mdc.CLine(CPoint(rt.left,rt.bottom),CPoint(rt.left,rt.top),0xffffff);
			mdc.CLine(CPoint(rt.left,rt.top),CPoint(rt.right,rt.top),0xffffff);
			mdc.CLine(CPoint(rt.right,rt.top),CPoint(rt.right,rt.bottom-1),0);
			w=w+sz.cx+36;
		}else{
			rt.left=w;
			rt.top=2;
			rt.bottom=wy-3;
			rt.right=rt.left+sz.cx+8;
			mdc.CTextOut(dbm.page[i].head.Name,rt,&lf,0,0,DT_SINGLELINE|DT_VCENTER|DT_CENTER);
			w=w+sz.cx+8;
			rt.left=rt.right-2;
			rt.bottom-=3;
			mdc.CDraw3DRect(rt,0,0xc0c0c0);
		}
		if(w>(wx-108)) break;
	}
	mdc.CLine(CPoint(wx-109,1),CPoint(wx-109,wy-4),0xffffff);
}

void pagectl::OnPagedown() 
{
	dx+=5;
	if(dx>=dbm.pagesum) dx=dbm.pagesum-1;
	DrawShow();
}

void pagectl::OnPageup() 
{
	dx-=5;
	if(dx<0) dx=0;
	DrawShow();
}

void pagectl::OnLeft() 
{
	dx--;
	if(dx<0) dx=0;
	DrawShow();
	
}

void pagectl::OnRight() 
{
	dx++;
	if(dx>=dbm.pagesum) dx=dbm.pagesum-1;
	DrawShow();
}



BOOL pagectl::OnTip(UINT id, NMHDR * pNMHDR, LRESULT * pResult )
{

	char text[256];
	char *lp;
	TOOLTIPTEXT *pTTT = (TOOLTIPTEXT *)pNMHDR;
    UINT nID =pNMHDR->idFrom;
	AfxLoadString(pNMHDR->idFrom,text,255);
	text[255]=0;
	lp=strrchr(text,'\n');
	if(lp!=NULL) {
		lp++;
		strcpy(pTTT->lpszText,lp);
	}
	else strcpy(pTTT->lpszText,"");
    return(TRUE);
}

void pagectl::DrawShow()
{
	CClientDC dc(this);
	ShowOnMdc();
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx-108,wy));
}


void pagectl::OnLButtonDown(UINT nFlags, CPoint point) 
{
	
	int i;
	i=GetSelPage(point);
	if(i>=0&&i!=dbm.curpage){
		dbm.GoToPage(i);
		if(i==dx){
			dx--;
			if(dx<=0) dx=0;
		}
		DrawShow();
		cobj.cvs->DrawShow();
		GetParent()->SendMessage(1007,100,i);
	}
	CWnd::OnLButtonDown(nFlags, point);
}

//返回选择的页面
int pagectl::GetSelPage(CPoint point)
{
	int i,x1,x2;
	SIZE sz;
	x1=0;
	for(i=dx;i<dbm.pagesum;i++){
		sz=GLDGetTextSize(mdc.m_hDC,&cobj.sysfont,dbm.page[i].head.Name);
		if(i==dbm.curpage) 	x2=x1+sz.cx+36;
		else x2=x1+sz.cx+8;
		if(point.x>=x1&&point.x<x2) return i;
		x1=x2;
	}
	return -1;
}

void pagectl::AddPage()
{
	OnSize(SIZE_RESTORED,wx,wy);
}

