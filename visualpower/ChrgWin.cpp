// ChrgWin.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "ChrgWin.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char    *ut[];
char *dgxs[]={"节点电压","节点电压低","节点电压高","输电线负载","变压器负载","输电线PTDF"};

int  en[]={63,63,63,63,43,63};

/////////////////////////////////////////////////////////////////////////////
// CChrgWin

CChrgWin::CChrgWin()
{
	mdc.Create(1,1);
	CFont cf;
	cf.CreateFont(-12,0,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"Arial" );
	cf.GetLogFont(&lf);
	cf.DeleteObject();
	scf=NULL;
}

CChrgWin::~CChrgWin()
{
}


BEGIN_MESSAGE_MAP(CChrgWin, CWnd)
	//{{AFX_MSG_MAP(CChrgWin)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CLOSE()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CChrgWin message handlers

BOOL CChrgWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

void CChrgWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	wx=cx;
	wy=cy;
	mdc.SizeChange(wx,wy);
	
}

void CChrgWin::OnPaint() 
{
	CPaintDC dc(this); 
	
	Show(dc);
}

void CChrgWin::Show(CDC &dc)
{
	int i,j,y1,y2;
	POINT p1,p2;
	double v,h,yl;
	char p[100];
	CRect rt,rt1,rt2;
	CTR_COLOR *cr;
	if(scf==NULL) return;
	rt=CRect(0,0,wx,wy);
	i=scf->ctrtype;
	if(i<0||i>5) return;
	SetWindowText(dgxs[i]);
	cr=(CTR_COLOR*)&scf->cr[i];
	mdc.FillBG(0xffffff);
	h=cr->value[0]-cr->value[4];
	if(h==0) return;
	yl=(rt.Height()-20)/h;
	y1=10;
	rt1.left=3;rt1.right=en[i];
	rt2.left=en[i]+4;rt2.right=wx;
	p1.x=en[i];p2.x=en[i]+4;
	for(j=1;j<5;j++){
		v=cr->value[j];
		if(v<cr->value[4]) v=cr->value[4];
		if(v>cr->value[0]) v=cr->value[0];
		v=v-cr->value[4];
		y2=rt.Height()-(int)(yl*v)-10;
		rt1.top=y1;
		rt1.bottom=y2+1;
		mdc.CRectc(rt1,cr->color[j-1],cr->color[j],1);
		p1.y=y1;p2.y=y1;
		mdc.CLine(p1,p2,0);
		p1.y=y2;p2.y=y2;
		mdc.CLine(p1,p2,0);
		rt2.top=y1-10;rt2.bottom=y1+10;
		if(j%2==1){
			if(i!=4) sprintf(p,"%2.2f% s",cr->value[j-1],cr->unit);
			else sprintf(p,"%2.2f% s",cr->value[j-1]*100,cr->unit);
			mdc.CTextOut(p,rt2,&lf,0,0,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		}
		y1=y2;
	}
	rt2.top=y1-10;rt2.bottom=y1+10;
	if(i!=4) sprintf(p,"%2.2f% s",cr->value[4],cr->unit);
	else sprintf(p,"%2.2f% s",cr->value[4]*100,cr->unit);
	mdc.CTextOut(p,rt2,&lf,0,0,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
	mdc.CDraw3DRect(rt,0,0xffffff);
	mdc.BitBlt(dc.m_hDC,rt);
}


void CChrgWin::ReDraw()
{
	CClientDC dc(this);
	Show(dc);

}


BOOL CChrgWin::Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd) 
{
	WNDCLASS wndcls;
	memset(&wndcls, 0,sizeof(WNDCLASS));   
    wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hCursor = NULL;
	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpszClassName ="popupwin";
	AfxRegisterClass(&wndcls);
	return CreateEx (WS_EX_TOPMOST|WS_EX_DLGMODALFRAME|WS_EX_TOOLWINDOW    , "popupwin","",dwStyle,rt.left,rt.top,rt.Width(),rt.Height(),pParentWnd->m_hWnd,NULL);
}

void CChrgWin::OnClose() 
{
	ShowWindow(SW_HIDE);
	//CWnd::OnClose();
}
