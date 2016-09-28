// MsAlmWin.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "MsAlmWin.h"
#include "comobj.h"
#include "mmsystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj cobj;
char *astr[]={"线路","发电","变压","断面","母线","ACE","TEGY"};
/////////////////////////////////////////////////////////////////////////////
// MsAlmWin

MsAlmWin::MsAlmWin()
{
	CFont cf;
	mdc.Create(1,1);
	color=GetSysColor(COLOR_3DFACE);
	cf.CreateFont(14,7,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"楷体");
	cf.GetLogFont(&lf1);
	cf.DeleteObject();
	memset(alm,0,sizeof(SYSALARM)*5);
	zt=0;
	zt2=0;
	cursor=0;
	dwnbz=0;
	sounding=0;
}

MsAlmWin::~MsAlmWin()
{
	KillTimer(100);
	KillTimer(101);
	KillTimer(102);
}


BEGIN_MESSAGE_MAP(MsAlmWin, CWnd)
	//{{AFX_MSG_MAP(MsAlmWin)
	ON_WM_CREATE()
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_LBUTTONDOWN()
	ON_WM_LBUTTONUP()
	ON_WM_MOUSEMOVE()
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(IDC_SHOWLST, OnShowlst)
	ON_COMMAND(IDC_PUSHPIC, OnPushpic)
	ON_WM_SETCURSOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// MsAlmWin message handlers

BOOL MsAlmWin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

int MsAlmWin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{

	int i;
	if (CWnd::OnCreate(lpCreateStruct) == -1)	return -1;
	rrd.SetCurDbf(0);
	for(i=0;i<5;i++)
	{
		gzw[i] = new GzTblDlg();
		gzw[i]->type=i;
		gzw[i]->Create(IDD_TABLEDLG);
		gzw[i]->ShowWindow(SW_HIDE);
		gzw[i]->SetMenu(&cobj.tmenu);	

		alsv.cfg[i].flash=1;
		alsv.cfg[i].pop=0;
		alsv.cfg[i].sound=0;
	}
	LoadAlmCfg();
	SetTimer(100,2000,NULL);
	SetTimer(101,500,NULL);
	SetTimer(102,1000,NULL);
	
	return 0;
}

void MsAlmWin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	
	wx=cx;
	wy=cy;
	mdc.SizeChange(wx,wy);
	
}

void MsAlmWin::OnPaint() 
{
	CPaintDC dc(this); 
	Show(dc);

}


BOOL MsAlmWin::Createtun(DWORD dwStyle,CRect rt,CWnd* pParentWnd) 
{
	WNDCLASS wndcls;
	memset(&wndcls, 0,sizeof(WNDCLASS));   
    wndcls.lpfnWndProc = ::DefWindowProc;
	wndcls.hInstance = AfxGetInstanceHandle();
	wndcls.hCursor = NULL;
	wndcls.style = CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW;
	wndcls.lpszClassName ="popupwin";
	AfxRegisterClass(&wndcls);
	return CreateEx (WS_EX_TOPMOST|WS_EX_DLGMODALFRAME, "popupwin","",dwStyle,rt.left,rt.top,rt.Width(),rt.Height(),pParentWnd->m_hWnd,NULL);
}


//装入告警参数配置
void MsAlmWin::LoadAlmCfg()
{
	FILE *fp;
	char fnm[256];
	cobj.SetToLocalFile("almpara.cfg",fnm);
	fp=fopen(fnm,"r+b");
	if(fp==NULL) return;
	fread(&alsv,sizeof(ALMSAVE),1,fp);
	fclose(fp);
}

void MsAlmWin::OnTimer(UINT nIDEvent) 
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
	CWnd::OnTimer(nIDEvent);
}


//读取数据
void MsAlmWin::ReadData()
{
	int i,n;
	SYSALARM tmp[5];
	memset(tmp,0,sizeof(SYSALARM)*5);
	if(!rrd.ReadSysAlarm(tmp,n)) return;
	//验证是否有列表,如果没有就表示这个信息是错误的，需要纠正
	for(i=0;i<5;i++)
	{
		if(gzw[i]->alsum==0)
		{
			tmp[i].Alarm=0;
			rrd.WriteSAlarm(i,0);
		}
	}
	if(memcmp(alm,tmp,sizeof(SYSALARM)*n)!=0)
	{
		memcpy(alm,tmp,sizeof(SYSALARM)*5);
	}
	DrawShow();
}



//闪动显示告警状态
void MsAlmWin::FlashShow()
{
	int i;
	CRect rt;
	CClientDC dc(this);
	rt.top=22;rt.bottom=38;
	for(i=0;i<5;i++)
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
			if(gzw[i]->alarm==0)	continue; //不闪烁显示
			if((alm[i].Alarm==1)&&zt==1) BitBlt(dc.m_hDC,i*46+14,2,18,18,cobj.amdc.m_hDC,18,0,SRCCOPY);
			else BitBlt(dc.m_hDC,i*46+14,2,18,18,cobj.amdc.m_hDC,0,0,SRCCOPY);
			break;
		}
	}
	zt=zt==0 ? 1:0;
}

//验证是否该推报警表
void MsAlmWin::CheckPushTbl()
{
	int i,pok;
	pok=0;

	for(i=0;i<5;i++)
	{
		if(alm[i].Alarm==1&&gzw[i]->alarm==1&&alsv.cfg[i].pop==1)
		{
			if(!gzw[i]->IsWindowVisible())
			{
				gzw[i]->showmode=0; //只显示告警的
				gzw[i]->ShowWindow(SW_SHOW);
				pok=1;
			}
		}
	}
	if(pok==1) RelayChild();
}

//显示低频震荡通信状态
void MsAlmWin::ShowLowFCom()
{
	int j;
	CClientDC dc(this);
	if(cobj.swin->lwin.cliw.connect_svr==1) j=9+zt2;
	else j=11;
	cobj.ShowSimg(dc.m_hDC,236,2,j);
	zt2=zt2==0 ? 1:0;
}

//播放预警声音
void MsAlmWin::PlayAlmSound()
{
	int i,play;
	play=0;
	for(i=0;i<5;i++)
	{
		if(alm[i].Alarm==1&&gzw[i]->alarm==1&&gzw[i]->sound==1&&alsv.cfg[i].sound==1)
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
	if(play==0&&sounding==1)
	{
		sndPlaySound(NULL,SND_LOOP|SND_ASYNC); 
		sounding=0;
	}
}

void MsAlmWin::DrawShow()
{
	CClientDC dc(this);
	Show(dc);
}

//排列子窗口
void MsAlmWin::RelayChild()
{
	int i,n,m,w,ws;
	n=0;
	for(i=0;i<5;i++)
	{
		if(gzw[i]->IsWindowVisible()) n++;
	}
	ws=GetSystemMetrics(SM_CXSCREEN);
	w=ws/n;
	if(w>300) w=300;
	m=0;
	for(i=0;i<5;i++)
	{
		if(gzw[i]->IsWindowVisible())
		{
			gzw[i]->MoveWindow(m,0,w,600);
			m+=w;
		}
	}
}

void MsAlmWin::Show(CDC &dc)
{
	int i,j;
	CRect rt;
	mdc.FillBG(0xf0ffff);
	mdc.CRectc(CRect(230,0,wx,wy),color,color,0);
	rt.top=22;rt.bottom=38;
	for(i=0;i<5;i++)
	{
		rt.left=i*46;
		rt.right=rt.left+46;
		if(alm[i].Alarm==0) BitBlt(mdc.m_hDC,i*46+14,2,18,18,cobj.amdc.m_hDC,0,0,SRCCOPY);
		else BitBlt(mdc.m_hDC,i*46+14,2,18,18,cobj.amdc.m_hDC,18,0,SRCCOPY);
		GLDDrawText(mdc.m_hDC,&rt,&lf1,astr[i],0,0,DT_CENTER|DT_SINGLELINE);
	}
	if(cobj.swin->lwin.cliw.connect_svr==1) j=9; 
	else j=11;
	cobj.ShowSimg(mdc.m_hDC,236,2,j);
	mdc.CDraw3DRect(CRect(0,0,wx-1,wy-1),0,0xffffff);
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx,wy));
}

void MsAlmWin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	oldpt=point;
	ClientToScreen(&oldpt);
	GetWindowRect(&oldrt);
	SetCapture();
	dwnbz=1;
	CWnd::OnLButtonDown(nFlags, point);
}

void MsAlmWin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	ReleaseCapture();
	dwnbz=0;
	
	CWnd::OnLButtonUp(nFlags, point);
}

void MsAlmWin::OnMouseMove(UINT nFlags, CPoint point) 
{
	cursor=GetCursor(point);
	if(dwnbz==1) MoveMyWin(point);
	CWnd::OnMouseMove(nFlags, point);
}

//返回光标
int  MsAlmWin::GetCursor(CPoint point)
{
	int i;
	if(point.x>340||point.y>26) return 0;
	i=point.x/46;
	if(i<0||i>6) return 0;
	return 1;
}

void MsAlmWin::MoveMyWin(CPoint point)
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

void MsAlmWin::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CMenu *mm;
	CPoint pt;
	cursel=point.x/46;
	if(cursel<0||cursel>4) return;
	pt=point;
	ClientToScreen(&pt);
	mm=cobj.amenu.GetSubMenu(0); //弹参数修改菜单
	if(cursel==5) mm->EnableMenuItem(IDC_PUSHPIC,1);
	else mm->EnableMenuItem(IDC_PUSHPIC,0);
	mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
	CWnd::OnRButtonDown(nFlags, point);
}

void MsAlmWin::OnShowlst() 
{
	gzw[cursel]->SetList();
	gzw[cursel]->ShowWindow(SW_SHOW);
	RelayChild();
}

void MsAlmWin::OnPushpic() 
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


BOOL MsAlmWin::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message) 
{
	if(nHitTest == HTCLIENT)
	 {
		switch(cursor)
		{
		case 1:  SetCursor(cobj.hcur[3]);	return TRUE;
		};
	}
	return CWnd::OnSetCursor(pWnd, nHitTest, message);
}
