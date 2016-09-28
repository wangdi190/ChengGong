// SAlmDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "SAlmDlg.h"
#include "comobj.h"
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj cobj;
extern char *astr[];
//char *astr[]={"Line","Gen","Tfm","Sect","Bus"};


/////////////////////////////////////////////////////////////////////////////
// CSAlmDlg dialog


CSAlmDlg::CSAlmDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CSAlmDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CSAlmDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	CFont cf;
	mdc.Create(1,1);
	color=GetSysColor(COLOR_3DFACE);
	cf.CreateFont(14,7,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"华文细黑");
	cf.GetLogFont(&lf1);
	cf.DeleteObject();
	memset(alm,0,sizeof(SYSALARM)*5);
	zt=0;
	zt2=0;
	cursor=0;
	dwnbz=0;
	sounding=0;

}

CSAlmDlg::~CSAlmDlg()
{
	KillTimer(100);
	KillTimer(101);
	KillTimer(102);
}

void CSAlmDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSAlmDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CSAlmDlg, CDialog)
	//{{AFX_MSG_MAP(CSAlmDlg)
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDC_SHOWLST, OnShowlst)
	ON_COMMAND(IDC_PUSHPIC, OnPushpic)
	ON_WM_SIZE()
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_WM_LBUTTONUP()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSAlmDlg message handlers

BOOL CSAlmDlg::OnInitDialog() 
{
	int i;
	CDialog::OnInitDialog();
	rrd.SetCurDbf(0);
	for(i=0;i<6;i++)
	{
		gzw[i].type=i;
		gzw[i].Create(IDD_TABLEDLG,this);
		gzw[i].ShowWindow(SW_HIDE);
		gzw[i].SetMenu(&cobj.tmenu);
		alsv.cfg[i].flash=1;
		alsv.cfg[i].pop=1;
		alsv.cfg[i].sound=1;
	}
	LoadAlmCfg();
	SetTimer(100,2000,NULL);
	SetTimer(101,500,NULL);
	SetTimer(102,1000,NULL);
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CSAlmDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	mdc.SizeChange(wx,wy);
}


void CSAlmDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	Show(dc);
}

void CSAlmDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 100:
		ReadData();
		break;
	case 101:
		FlashShow();
		CheckPushTbl();
		break;
	case 102: //显示低频震荡连接和播放声音检查
		ShowLowFCom();
		PlayAlmSound();
		break;
	}
	CDialog::OnTimer(nIDEvent);
}




//读取数据
void CSAlmDlg::ReadData()
{
	int i,n;
	SYSALARM tmp[6];
	memset(tmp,0,sizeof(SYSALARM)*6);
	if(!rrd.ReadSysAlarm(tmp,n)) return;
	//验证是否有列表,如果没有就表示这个信息是错误的，需要纠正
	for(i=0;i<6;i++)
	{
		if(gzw[i].alsum==0){
			tmp[i].Alarm=0;
			rrd.WriteSAlarm(i,0);
		}
	}
	if(memcmp(alm,tmp,sizeof(SYSALARM)*n)!=0)
	{
		memcpy(alm,tmp,sizeof(SYSALARM)*6);
		
	}
	DrawShow();
}

//显示告警列表
void CSAlmDlg::OnShowlst() 
{
	gzw[cursel].SetList();
	gzw[cursel].ShowWindow(SW_SHOW);
	RelayChild();
}
//推画面
void CSAlmDlg::OnPushpic() 
{
	bool rtn;
	char fnm[256],p[256];
	cobj.SetToLocalFile(alm[cursel].picname,fnm);
	if(!cobj.IsFileExist(fnm)){
		sprintf(p,"画面:%s不存在！",fnm);
		MessageBox(p,"错误",MB_OK|MB_ICONSTOP);
		return; //文件不存在 
	}
	cobj.swin->enabletimer=0;
	cobj.swin->FreeMem();
	rtn=cobj.swin->dbm.OpenPwFile(fnm,alm[cursel].picno);
	if(!rtn) return;
	cobj.swin->ShowWindow(SW_HIDE);
	cobj.swin->InitMoveObj(NULL,0);
	//根据类型决定是否显示功能
	switch(cursel)
	{
	case 0:
		cobj.fwin->SendMessage(WM_COMMAND,IDC_LINELOAD,NULL);
		cobj.Showdgx();
		break;
	case 1:
		cobj.mwin->SendMessage(WM_COMMAND,IDC_GENREV,NULL);
		break;
	case 2:
		cobj.mwin->SendMessage(WM_COMMAND,IDC_TRANREV,NULL);
		break;
	case 3:
		cobj.fwin->SendMessage(WM_COMMAND,IDC_LINELOAD,NULL);
		cobj.Showdgx() ;
		break;
	case 4:
		cobj.fwin->SendMessage(WM_COMMAND,IDC_DGXBUS,NULL);
		cobj.Showdgx();
		break;
	}
	cobj.swin->ShowWindow(SW_SHOW);
}


void CSAlmDlg::DrawShow()
{
	CClientDC dc(this);
	Show(dc);
}

void CSAlmDlg::Show(CDC &dc)
{
	int i,j;
	CRect rt;
	mdc.FillBG(0xf0ffff);
	mdc.CRectc(CRect(271,0,wx,wy),color,color,0);
	rt.top=22;rt.bottom=38;
	for(i=0;i<6;i++)
	{
		rt.left=i*46;
		rt.right=rt.left+46;
		if(alm[i].Alarm==0) BitBlt(mdc.m_hDC,i*46+14,2,18,18,cobj.amdc.m_hDC,0,0,SRCCOPY);
		else BitBlt(mdc.m_hDC,i*46+14,2,18,18,cobj.amdc.m_hDC,18,0,SRCCOPY);
		GLDDrawText(mdc.m_hDC,&rt,&lf1,astr[i],0,0,DT_CENTER|DT_SINGLELINE);
	}
	if(cobj.lwin->cliw.connect_svr==1) j=9;
	else j=11;
	cobj.ShowSimg(mdc.m_hDC,274,2,j);
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx,wy));
}

//闪动显示告警状态
void CSAlmDlg::FlashShow()
{
	int i;
	CRect rt;
	CClientDC dc(this);
	rt.top=22;rt.bottom=38;
	for(i=0;i<6;i++)
	{
		rt.left=i*46;
		rt.right=rt.left+46;
		//闪烁显示
		switch(alsv.cfg[i].flash)
		{
		case 0:  //正常显示
			if(alm[i].Alarm==1) BitBlt(dc.m_hDC,i*46+14,2,18,18,cobj.amdc.m_hDC,18,0,SRCCOPY);
			else BitBlt(dc.m_hDC,i*46+14,2,18,18,cobj.amdc.m_hDC,0,0,SRCCOPY);
			break;
		case 1:  //闪烁显示
			if(gzw[i].alarm==0)	continue; //不闪烁显示
			if((alm[i].Alarm==1)&&zt==1) BitBlt(dc.m_hDC,i*46+14,2,18,18,cobj.amdc.m_hDC,18,0,SRCCOPY);
			else BitBlt(dc.m_hDC,i*46+14,2,18,18,cobj.amdc.m_hDC,0,0,SRCCOPY);
			break;
		}
	}
	zt=zt==0 ? 1:0;
}

//显示低频震荡通信状态
void CSAlmDlg::ShowLowFCom()
{
	int j;
	CClientDC dc(this);
	if(cobj.lwin->cliw.connect_svr==1) j=9+zt2;
	else j=11;
	cobj.ShowSimg(dc.m_hDC,274,2,j);
	zt2=zt2==0 ? 1:0;
}

BOOL CSAlmDlg::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(nHitTest == HTCLIENT)
	 {
		switch(cursor)
		{
		case 1:  SetCursor(cobj.hcur[3]);	return TRUE;
		};
	}
	
	return CDialog::OnSetCursor(pWnd, nHitTest, message);
}

//返回光标
int  CSAlmDlg::GetCursor(CPoint point)
{
	int i;
	if(point.x>296||point.y>26) return 0;
	i=point.x/46;
	if(i<0||i>5) return 0;
	//if(alm[i].Alarm==0) return 0;
	return 1;
}

void CSAlmDlg::OnMouseMove(UINT nFlags, CPoint point) 
{
	cursor=GetCursor(point);
	if(dwnbz==1) MoveMyWin(point);
	CDialog::OnMouseMove(nFlags, point);
}


void CSAlmDlg::MoveMyWin(CPoint point)
{
	int dx,dy;
	CPoint pt;
	CRect rt;
	pt=point;
	ClientToScreen(&pt);
	dx=pt.x-oldpt.x;
	dy=pt.y-oldpt.y;
	rt=oldrt;
	rt.OffsetRect(dx,dy);
	MoveWindow(&rt);
}

void CSAlmDlg::OnLButtonDown(UINT nFlags, CPoint point) 
{

	oldpt=point;
	ClientToScreen(&oldpt);
	GetWindowRect(&oldrt);
	SetCapture();
	dwnbz=1;
	CDialog::OnLButtonDown(nFlags, point);
}

void CSAlmDlg::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu *mm;
	CPoint pt;
	cursel=point.x/46;
	if(cursel<0||cursel>5) return;
	//if(alm[cursel].Alarm==0) return;
	pt=point;
	ClientToScreen(&pt);
	mm=cobj.amenu.GetSubMenu(0); //弹参数修改菜单
	if(cursel==5) mm->EnableMenuItem(IDC_PUSHPIC,1);
	else mm->EnableMenuItem(IDC_PUSHPIC,0);
	mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
	CDialog::OnRButtonDown(nFlags, point);
}

void CSAlmDlg::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	dwnbz=0;
	CDialog::OnLButtonUp(nFlags, point);
}

//排列子窗口
void CSAlmDlg::RelayChild()
{
	int i,n,m,w,ws;
	n=0;
	for(i=0;i<6;i++)
	{
		if(gzw[i].IsWindowVisible()) n++;
	}
	ws=GetSystemMetrics(SM_CXSCREEN);
	w=ws/n;
	if(w>300) w=300;
	m=0;
	for(i=0;i<6;i++)
	{
		if(gzw[i].IsWindowVisible())
		{
			gzw[i].MoveWindow(m,0,w,600);
			m+=w;
		}
	}
}

//播放预警声音
void CSAlmDlg::PlayAlmSound()
{
	int i,play;
	play=0;
	for(i=0;i<6;i++)
	{
		if(alm[i].Alarm==1&&gzw[i].alarm==1&&gzw[i].sound==1&&alsv.cfg[i].sound==1)
		{
			play=1;
			break;
		}
	}
	if(play==1)
	{
		if(sounding==1) return;
	   	sndPlaySound(cobj.sndfile,SND_LOOP|SND_ASYNC); 
		sounding=1;
	}
	if(play==0&&sounding==1){
		sndPlaySound(NULL,SND_LOOP|SND_ASYNC); 
		sounding=0;
	}
}
//验证是否该推报警表
void CSAlmDlg::CheckPushTbl()
{
	int i,pok;
	pok=0;

	for(i=0;i<6;i++)
	{
		if(alm[i].Alarm==1&&gzw[i].alarm==1&&alsv.cfg[i].pop==1)
		{
			if(!gzw[i].IsWindowVisible())
			{
				gzw[i].showmode=0; //只显示告警的
				gzw[i].ShowWindow(SW_SHOW);
				pok=1;
			}
		}
		/*if(alm[i].Alarm==0&&gzw[i].alarm==0)
		{
			if(gzw[i].IsWindowVisible())
			{
				gzw[i].ShowWindow(SW_HIDE);
			}
		}*/
	}
	if(pok==1) RelayChild();
}

//装入告警参数配置
void CSAlmDlg::LoadAlmCfg()
{
	FILE *fp;
	char fnm[256];
	cobj.SetToLocalFile("almpara.cfg",fnm);
	fp=fopen(fnm,"r+b");
	if(fp==NULL) return;
	fread(&alsv,sizeof(ALMSAVE),1,fp);
	fclose(fp);
}
