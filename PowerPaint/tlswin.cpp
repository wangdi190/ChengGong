// tlswin.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "tlswin.h"
#include "gdata.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern gdata dbm;
extern comobj cobj;
extern char *tlstr[];
int hg[]={120,120,120,120,120,120};
/////////////////////////////////////////////////////////////////////////////
// tlswin

tlswin::tlswin()
{
	int i;
	tw[0].wnd=&egpw;
	tw[1].wnd=&spiw;
	tw[2].wnd=&layw;
	tw[3].wnd=&objw;
	for(i=0;i<4;i++){
		tw[i].active=0;
		strcpy(tw[i].str,tlstr[i]);
		tw[i].height=hg[i];
		tw[i].sel=0;
		tw[i].menu=1;
	}
	tw[0].active=1;
	tw[3].menu=0;
	tw[0].cmenu.LoadMenu(IDR_ELEMENU);
	tw[1].cmenu.LoadMenu(IDR_SPICMG);
	tw[2].cmenu.LoadMenu(IDR_LMENU);
	mdc.Create(1,1);
	img.Create(IDR_TLIMG,16,0,RGB(255,0,255));
	oldsel=-1;
	olds=-1;
	cobj.nwin=&navw;
	cobj.egpw=&egpw;
	cobj.spiw=&spiw;
	cobj.layw=&layw;
	cobj.objw=&objw;

}

tlswin::~tlswin()
{
	tw[0].cmenu.DestroyMenu();
	tw[1].cmenu.DestroyMenu();
	tw[2].cmenu.DestroyMenu();
}


BEGIN_MESSAGE_MAP(tlswin, CWnd)
	//{{AFX_MSG_MAP(tlswin)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()
	ON_COMMAND(DataChanged,  OnEditchange)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// tlswin message handlers

BOOL tlswin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	//cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);

	return TRUE;
}

int tlswin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	navw.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,100);
	egpw.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,101);
	spiw.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,102);
	layw.Create("","",WS_CHILD|WS_VISIBLE|WS_VSCROLL,CRect(0,0,1,1),this,103);
	objw.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,104);
	return 0;
}

void tlswin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	mdc.SizeChange(wx,30);
	ComputSelWin();
	navw.MoveWindow(CRect(0,0,wx,175));
}

void tlswin::OnPaint() 
{
	CPaintDC dc(this);
	ShowTitle(dc);
	dc.FillSolidRect(CRect(0,wy-25,wx,wy),GetSysColor(COLOR_3DFACE));
}
//计算选择窗口
void tlswin::ComputSelWin()
{
	int i,h,y;
	h=wy-100-175;
	if(h<0) return;
	y=175;
	for(i=0;i<4;i++){
		tw[i].sel=0;
		if(tw[i].active==1){  //只能保证有一个活动窗口
			tw[i].selrt=CRect(0,y,wx,y+25);
			y+=25;
			tw[i].rtw=CRect(0,y,wx,y+h);
			y+=h;
			tw[i].wnd->MoveWindow(tw[i].rtw);
		}else{
			tw[i].selrt=CRect(0,y,wx,y+25);
			y+=25;
			tw[i].rtw=CRect(0,0,1,1);
			tw[i].wnd->MoveWindow(tw[i].rtw);
		};
	}
}

void tlswin::ShowTitle(CDC&dc)
{
	int i;
	for(i=0;i<5;i++){
		DrawATitle(dc, i);
	}
}

void tlswin::OnMouseMove(UINT nFlags, CPoint point) 
{
	int i,sel;
	CClientDC dc(this);
	i=GetSel(point,sel);
	if(i!=oldsel){
		DrawATitle(dc,oldsel);
		if(i>=0) DrawATitle(dc,i);
	}
	if(i==oldsel&&sel!=olds) DrawATitle(dc,i);
	oldsel=i;
	olds=sel;
	CWnd::OnMouseMove(nFlags, point);
}

void tlswin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CMenu *mm;
	int i,j,sel;
	CPoint pt;
	j=GetSel(point,sel);
	if(j>=0){
		switch(sel){
		case 1:   //切换显示
			for(i=0;i<4;i++) tw[i].active=0;
			tw[j].active=1;
			ComputSelWin();
			DrawShow();
			break;
		case 2:   //打开菜单
			pt=point;
			ClientToScreen(&pt);
			mm=tw[j].cmenu.GetSubMenu(0);
			mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,tw[j].wnd);
			break;
		}
	}
	CWnd::OnLButtonUp(nFlags, point);
}

void tlswin::DrawATitle(CDC &dc, int index)
{
	LOGFONT lf;
	CRect rt,rt1;
	CDC dc1;
	DWORD c1,c2;
	if(index>3||index<0) return;
	c1=0x7f7f7f;
	c2=0xffffff;
	rt=CRect(0,0,wx,25);
	rt1=CRect(40,5,wx-25,wy);
	dc1.Attach(mdc.m_hDC);
	lf=cobj.sysfont;
	lf.lfHeight=14;
	lf.lfWidth=7;
	mdc.CRectc(rt,c1,c2,1);
	
	mdc.CDraw3DRect(CRect(-1,0,wx+1,2),0x7f7f7f,0xffffff);
	if(tw[index].active==1) img.Draw(&dc1,1,CPoint(20,5),ILD_NORMAL);
	else img.Draw(&dc1,0,CPoint(20,5),ILD_NORMAL);
	if(tw[index].menu==1) img.Draw(&dc1,2,CPoint(wx-20,5),ILD_NORMAL);
	mdc.CTextOut(tw[index].str,rt1,&lf,0,0,0);
	mdc.CDraw3DRect(CRect(2,4,4,18),0xffffff,0);
	mdc.CDraw3DRect(CRect(5,4,7,18),0xffffff,0);
	
	if(tw[index].sel==1) mdc.CDraw3DRect(CRect(20,5,wx-25,22),0xffffff,0);
	if(tw[index].sel==2) mdc.CDraw3DRect(CRect(wx-20,5,wx-2,22),0xffffff,0);
	mdc.BitBltRect(dc.m_hDC,rt,tw[index].selrt);

	dc1.Detach();
}

int tlswin::GetSel(CPoint point,int &sel)
{
	int i,rtn;
	CRect rt,rt1,rt2;
	rtn=-1;
	sel=0;
	for(i=0;i<4;i++){
		tw[i].sel=0;
		rt=tw[i].selrt;
		rt1=CRect(rt.left+20,rt.top+5,rt.right-25,rt.top+22);
		rt2=CRect(rt.right-20,rt.top+5,rt.right-2,rt.top+22);
		if(rt1.PtInRect(point)&&tw[i].active==0){
			tw[i].sel=1;
			sel=1;
			rtn=i;
		}else if(rt2.PtInRect(point)&&tw[i].menu==1&&tw[i].active==1)
		{
			tw[i].sel=2;
			sel=2;
			rtn=i;
		};
	}
	return rtn;
}

void tlswin::DrawShow()
{
	CClientDC dc(this);
	ShowTitle(dc);
}


void tlswin::ReFreshWin()
{
	layw.AddLayer();
	cobj.pgcw->AddPage();
	layw.DrawCurLayerPic();
	layw.Invalidate();
}

//让编辑框有效
void tlswin::EnableEditTool()
{
	int i;
	for(i=0;i<4;i++) tw[i].active=0;
	tw[3].active=1;
	ComputSelWin();
	DrawShow();
}

bool tlswin::IsEditActive()
{
	return tw[3].active==0 ? false:true;
}


//编辑发生变化
void tlswin::OnEditchange()
{
	cobj.cvs->DrawShow();
}