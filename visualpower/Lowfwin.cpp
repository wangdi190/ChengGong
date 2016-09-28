// Lowfwin.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "Lowfwin.h"
#include "middll.h"
#include "comobj.h"
#include "math.h"
#include "mmsystem.h"


extern comobj  cobj;		//公共对象
//////////////////////////////////////////////////////////////////////////////////////

Lowfwin::Lowfwin()
{
	mdc.Create(1,1);
	sfr=0;
	sval=0;
	name[0]=0;
	CFont cf;
	cf.CreateFont(14,7,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"Arial" );
	cf.GetLogFont(&lf);
	cf.DeleteObject();
	consum=0;		//配置总数
	curcon=0;		//当前配置
	showbl=1;
	fcolor=GetSysColor(COLOR_3DFACE);		//低频震荡数据
	vlen=0;			//低频震荡数据长度
	curfct=0;		//正常状态
	vpt=NULL;
	lbdown=0;
	nLine=0;		//线路数
	svrchk=0;
	islowf=0;
	sounding=0;
}

Lowfwin::~Lowfwin()
{
//	KillTimer(100);
//	KillTimer(101);
//	KillTimer(102);
//	KillTimer(103);
}



BEGIN_MESSAGE_MAP(Lowfwin, CWnd)
	//{{AFX_MSG_MAP(Lowfwin)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_LBUTTONUP()
	ON_WM_CREATE()
	ON_WM_TIMER()
	ON_COMMAND(1001,OnConnect)
	ON_COMMAND(RECDATA,OnRecData)
	ON_WM_HSCROLL()
	ON_WM_LBUTTONDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// Lowfwin message handlers

BOOL Lowfwin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

void Lowfwin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	if(wx>10&&wy>10) mdc.SizeChange(wx,wy);
	if(curfct==2) sld.MoveWindow(CRect(65,2,wx-22,18));
	else sld.MoveWindow(CRect(65,2,wx-2,18));
}

void Lowfwin::OnPaint() 
{
	CPaintDC dc(this);
	switch(curfct)
	{
	case 0:	
		DrawControll();
		break;
	case 2:
		Draw();
		break;
	}
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx,wy));
}

//画控制部分
void Lowfwin::DrawControll()
{
	CRect rt;
	LOGFONT ft;
	rt=CRect(0,0,wx,wy);
	mdc.FillBG(fcolor);
	GLDDraw3DRect(mdc.m_hDC,rt,0xffffff,0);
	rt=CRect(2,1,118,15);
	ft=lf;
	ft.lfHeight=16;
	ft.lfWidth=7;
	mdc.CTextOut("扫描调节:",rt,&ft,0,0);
}


//设置功能
void Lowfwin::SetFunct(int funct)
{
	int w,h;
	CRect rt,rt1;
	curfct=funct;
	GetParent()->GetClientRect(&rt);
	switch(curfct)
	{
	case 0: //将自己移动到右上角，仅保留滑动杆和关闭钮
		rt1.top=0;
		rt1.left=rt.right-214;
		rt1.bottom=20;
		rt1.right=rt.right+1;
		sld.ShowWindow(SW_SHOW);
		MoveWindow(rt1);
		break;
	case 1:
		w=rt.Width()/2;
		h=rt.Height()/2;
		rt1.left=w-260;
		rt1.right=w+260;
		rt1.top=h-20;
		rt1.bottom=h+20;
		sld.ShowWindow(SW_HIDE);
		MoveWindow(rt1);
		break;
	}
}


void Lowfwin::Draw()
{
	int i;
	LOGFONT ft;
	char p[100];
	DPOINT dp1,dp2;
	CPoint pt1,pt2;
	CRect rt;
	rt=CRect(0,0,wx,20);
	mdc.CRectc(rt,fcolor,fcolor,0);
	rt=CRect(2,20,wx-2,wy-2);
	mdc.CRectc(rt,0,0,0);

	rt=CRect(0,0,wx,wy);
	GLDDraw3DRect(mdc.m_hDC,rt,0xffffff,0xffffff);
	rt.left++;rt.top++;rt.right--;rt.bottom--;
	GLDDraw3DRect(mdc.m_hDC,rt,0xf0ffff,0xf0ffff);
	
	ft=lf;
	ft.lfHeight=16;
	ft.lfWidth=7;
	mdc.CTextOut("扫描调节:",rt,&ft,0,0);


	pt1.y=22;
	pt2.y=wy-3;
	for(i=1;i<11;i++)
	{
		pt1.x=2+i*30;
		pt2.x=pt1.x;
		mdc.CLine(pt1,pt2,0x4f00);
	}
	pt1.x=2;
	pt2.x=wx-3;
	for(i=1;i<4;i++)
	{
		pt1.y=22+i*30;
		pt2.y=pt1.y;
		mdc.CLine(pt1,pt2,0x4f00);
	}
	if(vlen==0) return;
	dp1.x=2;
	dp1.y=82+vpt[0]*8;
	
	//显示波形
	for(i=1;i<254;i++)
	{
		if(i>=vlen) break;
		dp2.x=2+i*2;
		dp2.y=82+vpt[i]*8;
		mdc.CDLine(dp1,dp2,0xff00);
		dp1=dp2;
	}

	//显示频率和幅度
	rt=CRect(15,22,wx-5,38);
	sprintf(p,"%2.4fHz  %2.2fMW",sfr,sval);
	GLDDrawText(mdc.m_hDC,&rt,&lf,p,0xff00,0);

	rt=CRect(15,wy-20,wx-15,wy-4);
	sprintf(p,"Powerline:%s",name);
	GLDDrawText(mdc.m_hDC,&rt,&lf,p,0xff00,0);
	//显示关闭钮
	rt=CRect(wx-21,2,wx-3,18);
	DrawFrameControl(mdc.m_hDC,&rt,DFC_CAPTION,DFCS_CAPTIONCLOSE|DFCS_MONO);
	rt=CRect(2,1,118,15);
}

//动态显示低频震荡
void Lowfwin::LowFShow()
{
	CClientDC dc(this);
	Draw();
	mdc.BitBltRect(dc.m_hDC,CRect(0,20,wx,wy),CRect(0,20,wx,wy));
}	

void Lowfwin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	lbdown=1;
	SetCapture();
	
	CWnd::OnLButtonDown(nFlags, point);
}

void Lowfwin::OnLButtonUp(UINT nFlags, CPoint point) 
{
	CRect rt=CRect(wx-16,4,wx-4,16);
	if(curfct==2&&rt.PtInRect(point)) SetFunct(0);
	lbdown=0;
	ReleaseCapture();
	CWnd::OnLButtonUp(nFlags, point);
}

//将字节的高低进行转换
DWORD Lowfwin::ChangeHL(DWORD param)
{
	BYTE a[4],c[4];
	DWORD *d;
	d=(DWORD*)a;
	d[0]=param;
	c[0]=a[3];
	c[1]=a[2];
	c[2]=a[1];
	c[3]=a[0];
	d=(DWORD*)c;
	return d[0];
}

int Lowfwin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	//创建网络窗口
	cliw.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,100);
	sld.Create(TBS_HORZ|WS_CHILD|WS_VISIBLE|TBS_NOTICKS   ,CRect(0,0,1,1),this,101);
	sld.SetRange(1,50);
	sld.SetPos(showbl);
	CreateConCfg();
	//读取PMU线路,申请缓冲区
	//InitLowfLine();

	//演示时钟
	SetTimer(102,1000,NULL);
	SetTimer(103,1000,NULL);//检查是否连接到服务器
	return 0;
}

//生成连接配置
void Lowfwin::CreateConCfg()
{
	int i,j,k,n;
	PSvrIpPort pip[2];
	n=rrd->ReadPmuSvrIpPort(pip); //读取服务器IP
	consum=n*cliw.nAdapter;
	if(consum==0) return;
	k=0;
	for(i=0;i<n;i++)
	{
		for(j=0;j<cliw.nAdapter;j++)
		{
			concfg[k].laddr=cliw.ad[j];
			concfg[k].saddr.S_un.S_addr=ChangeHL(pip[i].ip);
			concfg[k].port=pip[i].port;
			k++;
		}
	}
	curcon=0;
}


//启动低频震荡连接
void Lowfwin::StartLowf()
{
	
	if(consum==0) return;
	LoginSvr(); //首先连接一次
	SetTimer(100,5000,NULL);

}
//结束低频震荡
void Lowfwin::EndLowf()
{
	SetFunct(0);
	vlen=0;			//低频震荡数据长度
	if(cliw.connect_svr==1) cliw.slogout(); //脱机
	cliw.connect_svr=0;
	KillTimer(101);
	islowf=0;
}

void Lowfwin::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 100: //定时连接服务器
		LoginSvr();
		break;
	case 101: //自动发连接信息
		SendCheck();
		break;
	case 102: //演示自动数据
		//DemoLowFData();
		break;
	case 103: //自动检查服务器
		CheckCon();
		break;
	}
	CWnd::OnTimer(nIDEvent);
}

//连接服务器
void Lowfwin::LoginSvr()
{
	int rtn;
	for(int i=0;i<consum;i++)
	{
		char szAddr[24]={0};
		char* pAddr=inet_ntoa(concfg[i].saddr);
		strcpy(szAddr,pAddr);
		pAddr=strrchr(szAddr,'.');
		if(pAddr!=NULL)
		{
			*pAddr=0;
			pAddr=inet_ntoa(concfg[i].laddr);
			if(strstr(pAddr,szAddr)!=NULL)//同网段网卡
			{
				curcon=i;
				rtn=cliw.ReInitNet(concfg[curcon].laddr);
				cliw.Connect(concfg[curcon].saddr,concfg[curcon].port);
				return;
			}
		}
	}
	rtn=cliw.ReInitNet(concfg[curcon].laddr);
	cliw.Connect(concfg[curcon].saddr,concfg[curcon].port);
	curcon++;
	if(curcon>=consum) curcon=0;
}

//连接到服务器
void Lowfwin::OnConnect()
{
	KillTimer(100);
	SetTimer(101,1000,NULL); //启动连接监视
	SetFunct(0);			 //设置为连接状态
}


//发送验证信息 funct=32;
void Lowfwin::SendCheck()
{

	PHead head;
	if(cliw.connect_svr==0) return;
	head.flag=0xcc;
	head.funct=32;
	head.packsize=sizeof(PHead);
	cliw.senddata((char*)&head,sizeof(PHead));
}


void Lowfwin::OnRecData()
{
	DWORD n;
	PHead *sd;
	char *buf;
	buf=cliw.GetRecBuf(n);
	sd=(PHead*)buf;
	if(cliw.connect_svr==0) return;
	if(sd->flag!=0xcc) return;
	switch(sd->funct)
	{
	case 1: //接收数据
		RecFlowLowF(buf,n);
		break;
	case 2:  //接收确认信号
		svrchk=0;
		break;
	}

}

//确认连接情况
void Lowfwin::CheckCon()
{
	if(cliw.connect_svr==0)//如果没有联接直接启动连接
	{
		StartLowf();
		return;
	}
	svrchk++;
	//如果，已连接，确认连接是否超限
	if(svrchk>5)
	{
		cliw.slogout(); //直接脱机
		svrchk=0;
	}
}


void Lowfwin::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int i;
	i=sld.GetPos();
	if(i>=1&&i<=50)
	{
		showbl=i;
	}
	CWnd::OnHScroll(nSBCode, nPos, pScrollBar);
}


//初始化低频振荡缓冲区
void Lowfwin::InitLowfLine()
{
	int i,n;
	LowFLPam lfbuf[MAXLWF];
	nLine=0;
	n=rrd->ReadLowFLine(lfbuf,MAXLWF);
	if(n<=0) return;
	for(i=0;i<n;i++)
	{
		lwf[i].bsum=0;
		lwf[i].LineID=lfbuf[i].LineID;
		lwf[i].Type=lfbuf[i].Type;
		lwf[i].maxv=lfbuf[i].MaxV;
		lwf[i].pha=0;
		lwf[i].lastv=0;
		memset(lwf[i].data,0,sizeof(LFDATA)*8);
		nLine++;
	}
}

//察看是否是低频震荡线路
bool Lowfwin::IsLowFLine(int id,int type)
{
	int i;
	for(i=0;i<nLine;i++)
	{
		if(lwf[i].LineID==id&&type==lwf[i].Type) return true;
	}
	return false;
}



//接收低频震荡数据
void Lowfwin::RecFlowLowF(char *buf,DWORD len)
{
	int i,ozt;
	SENDLFDATA *sd;
	LFDATA *lfd;
	sd=(SENDLFDATA*)buf;
	ozt=islowf;
	if(len!=sd->packsize)
	{
		islowf=0;
		return;
	}
	lfd=sd->lfd;
	for(i=0;i<sd->nline;i++)
	{
		SetLowFData(lfd[i]);
	}
	islowf=1;
	//有数据到达，察看是否处于低频震荡状态，如果不是，切换到低频震荡
	if(ozt==0&&islowf==1) cobj.swin->TurnToLowF();
	if(sounding==0) //播放声音
	{
		sndPlaySound(cobj.lowfsnd,SND_ASYNC); 
		sounding=1;
	}
}

float pl=1;
float fd=1;
//自动产生演示数据
void Lowfwin::DemoLowFData()
{
	/*int i;
	LFDATA lfd;
	for(i=0;i<nLine;i++)
	{
		lfd.LineID=lwf[i].LineID;
		lfd.Type=lwf[i].Type;
		lfd.frq=pl;
		lfd.lfp=fd;
		SetLowFData(lfd);
	}
	pl+=1;
	fd+=1;
	if(pl>5) pl=1;
	if(fd>5) fd=1;*/

}

//设置一秒低频震荡数据
void Lowfwin::SetLowFData(LFDATA &lfd)
{
	LFData* pLFD=NULL;
	int i,j;
	float v;

	for(i=0;i<nLine;i++)
	{
		if(lfd.LineID==lwf[i].LineID && lfd.Type==lwf[i].Type)
		{
			pLFD=&lwf[i];
			break;
		}
	}

	/*char szMsg[128];
	sprintf(szMsg,"NU=%d,Type=%d,curopzt=%d",lfd.LineID,lfd.Type,cobj.dbm->curopzt);
	AfxMessageBox(szMsg);*/

	if(pLFD==NULL && nLine<MAXLWF)//新增记录
	{
		memset(&lwf[nLine],0,sizeof(LFData));
		lwf[nLine].LineID=lfd.LineID;
		lwf[nLine].Type=lfd.Type;
		pLFD=&lwf[nLine];
		nLine++;
	}

	if(pLFD!=NULL)//修改数据
	{
		cobj.swin->InitLowFData(&lfd);
		if(pLFD->bsum>=8) return;//缓冲区已满
		j=pLFD->bsum;
		pLFD->data[j].frq=lfd.frq;
		v=lfd.lfp;
		v=v<0 ? -v:v;
		pLFD->data[j].lfp=v;
		pLFD->data[j].LineID=lfd.LineID;
		pLFD->data[j].Type=lfd.Type;
		pLFD->bsum++;
	}
}

//返回一个缓冲区的数据
bool Lowfwin::GetABufData(LFSDATA &lfd,int id,int type)
{
	int i,j,k;
	double a,f,b,c,d,v,t,val;
	for(i=0;i<nLine;i++)
	{		
		if(lwf[i].LineID!=id) continue;
		if(lwf[i].Type!=type) continue;
		if(lwf[i].bsum==0) return false;
		lfd.frq=lwf[i].data[0].frq;
		lfd.lfp=lwf[i].data[0].lfp;
		if(curtype==type&&curid==id)
		{
			sfr=lwf[i].data[0].frq;
			sval=lwf[i].data[0].lfp;
		}
		t=lwf[i].data[0].lfp;
		val=lwf[i].data[0].lfp;
		val=val<0 ? -val:val;
		val=val>5 ? 5:val;
		d=(double)(val-lwf[i].lastv)/(double)120.00;
		f=lwf[i].data[0].frq;
		a=5*mpi*f/(120*showbl);
		c=lwf[i].pha;
		//生成数据
		for(j=0;j<120;j++)
		{
			v=val+j*d;
			lfd.lfd[j]=(float)(v*sin(j*a+c));
		}
		lwf[i].lastv=(float)val;
		for(j=0;j<lwf[i].bsum-1;j++) lwf[i].data[j]=lwf[i].data[j+1];
		b=120*a+c;
		k=(int)(b/dpi);
		c=b-k*dpi;
		lwf[i].pha=(float)c;
		lwf[i].bsum--;
		break;
	}
	return true;
}


