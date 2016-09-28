// egpwin.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "egpwin.h"
#include "egatrdlg.h"
#include "ptdefine.h"
#include "gdata.h"
#include "comobj.h"
#include "filev30.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern gdata dbm;
extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// egpwin

egpwin::egpwin()
{
	dy=0;
	selpic=0;
	m_curtype = 255;
	m_cursubtype = 255;
	fcolor=GetSysColor(COLOR_3DFACE);
	mdc.Create(1,1);
	menu.LoadMenu(IDR_ELEMENU);
}

egpwin::~egpwin()
{
	menu.DestroyMenu();
}


BEGIN_MESSAGE_MAP(egpwin, CWnd)
	//{{AFX_MSG_MAP(egpwin)
	ON_WM_SIZE()
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_COMMAND(IDC_OPENEGRP, OnOpenegrp)
	ON_WM_VSCROLL()
	ON_WM_LBUTTONDOWN()
	ON_COMMAND(IDC_SAVEEGRP, OnSaveegrp)
	ON_COMMAND(ID_SAVEAS, OnSaveas)
	ON_COMMAND(IDC_ADDEMPTY, OnAddempty)
	ON_COMMAND(IDC_PASTENORMAL, OnPastenormal)
	ON_COMMAND(IDC_PASTEALARM, OnPastealarm)
	ON_COMMAND(IDC_DELAEGRP, OnDelaegrp)
	ON_COMMAND(IDC_COPYTODESK, OnCopytodesk)
	ON_COMMAND(IDC_SETUP, OnSetup)
	ON_WM_RBUTTONDOWN()
	ON_WM_MOUSEWHEEL()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// egpwin message handlers

BOOL egpwin::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), NULL, NULL);
	return TRUE;
}

void egpwin::OnSize(UINT nType, int cx, int cy) 
{
	CWnd::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	if(wx>25&&wy>10) mdc.SizeChange(wx-20,wy);
	twin.MoveWindow(CRect(0,wy-21,wx,wy));
	bar.MoveWindow(CRect(wx-20,0,wx,wy-21));
	computpage();
	SetYScroll();
}

void egpwin::OnPaint() 
{
	CPaintDC dc(this); 
	ShowEPIC();
	mdc.BitBlt(dc.m_hDC,CRect(0,0,wx,wy-21));
}

int egpwin::OnCreate(LPCREATESTRUCT lpCreateStruct) 
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	twin.Create("","",WS_CHILD|WS_VISIBLE,CRect(0,0,1,1),this,100);
	bar.Create(WS_CHILD|WS_VISIBLE|SBS_VERT,CRect(0,0,1,1),this,101);
	AddAllStr();
	return 0;
}


//加入所有的串
void egpwin::AddAllStr()
{
	twin.AddSelStr("全部",0);
	twin.AddSelStr("开关",1);
	twin.AddSelStr("二绕变",2);
	twin.AddSelStr("三绕变",3);
	twin.AddSelStr("负荷",4);
	twin.AddSelStr("电容",5);
	twin.AddSelStr("接地",6);
	twin.AddSelStr("PT",7);
	twin.AddSelStr("电抗",8);
	twin.AddSelStr("发电机",9);
	twin.AddSelStr("静态无功",10);
	twin.AddSelStr("变流器",11);
	twin.AddSelStr("厂站",12);
	twin.AddSelStr("区域",13);
	twin.AddSelStr("仪表",14);
}

void egpwin::OnOpenegrp() 
{
	char title[64];
	char path[256];
	char filter[256];
	char fnm[256];
	strcpy(filter,"图形组文件(*.NDV)|*.ndv");
	strcpy(path,cobj.path[1].path);
	CFileDialog  fodlg(true,NULL,NULL,
		OFN_FILEMUSTEXIST|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	strcpy(title,"打开组合图元文件");
	fodlg.m_ofn.lpstrInitialDir=path;
	fodlg.m_ofn.lpstrTitle=title;
	if(fodlg.DoModal()==IDOK){
	  strcpy(fnm,fodlg.GetPathName());
	  LoadEGP(fnm);
	  ReDrawObj();
	  computpage();
	  SetYScroll();
	  fbz=1;
	  strcpy(filenm,fnm);
	};
}

//打开一个已有的组合图元文件
void egpwin::LoadEGP(char *filename)
{
	FileV30  fv3;
	N_BASATTR btr;		//基本属性
	char  buf[MAXSIZE]; //最大缓冲区10K
	FILE *fp;
	DWORD *dw;
	int i,j,k,m,n,size,bsize;
	char *pbuf;
	char *rbuf;
	char *lp;
	uncmpres upr;
	N_EGPHEAD head;
	N_EGPDATA *eda;
	fp=fopen(filename,"r+b");
	if(fp==NULL) return;
	fread(&head,sizeof(N_EGPHEAD),1,fp);
	if(head.flag!=0x20010215||head.picsum==0||head.psize<=0||
		(head.version>0x500)||head.size<=0)
	{
	  fclose(fp);
	  MessageBox("版本不对，无法读入","错误",MB_OK);
	  return;  //数据有问题，退出
	};
	size=head.psize;
	pbuf=new char[size+100];
	rbuf=new char[head.size+100];
	fread(pbuf,size,1,fp);
	fclose(fp);
	dw=(DWORD*)pbuf;
	upr.initdata();
	upr.DDeCode(pbuf+4,rbuf,size,dw[0]); //解压
	eda=(N_EGPDATA *)rbuf;
	lp=rbuf+head.picsum*sizeof(N_EGPDATA);
	for(i=0;i<head.picsum;i++){
		if(eda[i].start!=0x10891112) break;
		if(cobj.egpsum>=MAXEGRP)	 break;
		if(!cobj.AddAEmptyEGP(eda[i].sav.type)) break;
		n=cobj.egpsum-1;
		cobj.egp[n].type=eda[i].sav.type;
		cobj.egp[n].subtype=eda[i].sav.subtype;
		m=eda[i].sav.sitesum;
		if(cobj.egp[n].type==0){ //仪表
			cobj.egp[n].sitesum=m;
			for(k=0;k<6;k++) cobj.egp[n].index[k]=eda[i].sav.index[k];
		}else{				//非仪表
			m=m>3 ? 0:m;
			cobj.egp[n].sitesum=m;
			for(k=0;k<m;k++){
				cobj.egp[n].srt[k]=eda[i].sav.srt[k];
			}
		}
		cobj.egp[n].rt1=eda[i].sav.rt1;
		cobj.egp[n].rt2=eda[i].sav.rt2;
		strcpy(cobj.egp[n].name,eda[i].sav.name);
		for(j=0;j<eda[i].sav.bsum1;j++){
			memset(buf,0,MAXSIZE);
			switch(head.version)
			{
			case 0x200: //V2版本
				bsize=fv3.GetBsFromV2(lp,btr,buf);
				break;
			case 0x300: //V3版本
				bsize=fv3.GetBsFromV3(lp,btr,buf);
				break;
			case 0x400: //V4版本
				bsize=fv3.GetBsFromV4(lp,btr,buf);
				break;
			default: continue;
			}
			if(btr.size==0) continue;
			cobj.AddAEGP(n,0,btr,buf);
			lp+=bsize;
		};
		for(j=0;j<eda[i].sav.bsum2;j++){
			memset(buf,0,MAXSIZE);
			switch(head.version)
			{
			case 0x200: //V2版本
				bsize=fv3.GetBsFromV2(lp,btr,buf);
				break;
			case 0x300: //V3版本
				bsize=fv3.GetBsFromV3(lp,btr,buf);
				break;
			case 0x400: //V4版本
				bsize=fv3.GetBsFromV4(lp,btr,buf);
				break;
			default: continue;
			}
			if(btr.size==0) continue;
			cobj.AddAEGP(n,1,btr,buf);
			lp+=bsize;
		};
		//察看刚加的是否和以前的相同，如相同，则删除
		if(cobj.IsSameWhithOther(n)){
			cobj.FreeEgp(n,0);
			cobj.FreeEgp(n,1);
			memset(&cobj.egp[n],0,sizeof(N_ELEGRP));
			cobj.egpsum--;
		}
	};
	delete rbuf;
	delete pbuf;
	Invalidate();
}

void egpwin::ReDrawObj()
{
	CClientDC dc(this);
	ShowEPIC();
	mdc.BitBlt(dc.m_hDC,CRect(0,0,400,wy-21));
}

//计算页面数
void egpwin::computpage()
{
	int i;
	ComputMax();
	int sum=0;
	for(i=0;i<cobj.egpsum;i++)
	{
		switch(m_curtype)
		{
		case 255:
			cobj.typeidx[sum]=i;
			sum++;
			break;
		case 1:
			if(cobj.egp[i].type == m_curtype&&cobj.egp[i].subtype == m_cursubtype)
			{
				cobj.typeidx[sum]=i;
				sum++;
			}
			break;
		default:
			if((cobj.egp[i].type == m_curtype))
			{
				cobj.typeidx[sum]=i;
				sum++;
			}
		}
	
	}
	cobj.selsum=sum;
}

void egpwin::SetYScroll()
{
	int sp=cobj.selsum-1;
	sp=sp<0 ? 0:sp;
	if(sp>0){
		bar.EnableScrollBar(ESB_ENABLE_BOTH);
		bar.SetScrollRange(0,sp);
		bar.SetScrollPos(dy);
	}else{
		bar.EnableScrollBar(ESB_DISABLE_BOTH);
	};
}

//显示
void egpwin::ShowEPIC()
{
	CRect rt,rt1;
	int i,k,t,index=0;
	mdc.FillBG(0xffffff);
	for(i=0;i<maxy+1;i++){
		//显示第一幅
		k=dy+i;
		if(k>=cobj.selsum) break;
		rt.left=dx;
		rt.top=i*55+5;
		rt.right=rt.left+50;
		rt.bottom=rt.top+50;
		rt1=rt;
		rt1.left+=3;rt1.top+=3;
		rt1.right-=3;rt1.bottom-=3;
		t=cobj.typeidx[k];
		if(k==selpic){
			mdc.FillSolidRect(rt,0);
			mdc.CDraw3DRect(rt,0xffffff,0xffffff);
			dbm.PreShowEGP(mdc,t,rt1,0,0xffffff,1);
		}
		else  {
			mdc.FillSolidRect(rt,0xff0000);
			mdc.CDraw3DRect(rt,0,0);
			dbm.PreShowEGP(mdc,t,rt1,0,0,1);
		}
		//显示第二幅
		rt.left+=50;
		rt.right=rt.left+50;
		rt1=rt;
		rt1.left+=3;rt1.top+=3;
		rt1.right-=3;rt1.bottom-=3;
		if(k==selpic){
			mdc.FillSolidRect(rt,0);
			mdc.CDraw3DRect(rt,0xffffff,0xffffff);
			dbm.PreShowEGP(mdc,t,rt1,1,0xffffff,1);
		}
		else  {
			mdc.FillSolidRect(rt,0xff0000);
			mdc.CDraw3DRect(rt,0,0);
			dbm.PreShowEGP(mdc,t,rt1,1,0,1);
		}
	}
}
//计算最大值
void egpwin::ComputMax()
{
	dx=(wx-21-100)/2;  //X方向可显示的最大图元数
	maxy=(wy-21-5)/55; //Y方向可显示的最大图元数
	if(dx<=0) dx=0;
	if(maxy<=0) maxy=1;
}

void egpwin::ReOpenGrp()
{
	computpage();
	SetYScroll();
	ReDrawObj();
}

void egpwin::OnVScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar) 
{
	int sy,vy;
	sy=dy;
	switch(nSBCode){
	case SB_PAGEDOWN:
	case SB_LINEDOWN:
		sy=sy<cobj.selsum-1 ? sy+1:sy;	
		break;
	case SB_PAGEUP:
	case SB_LINEUP:
		sy=sy>0 ? sy-1:0;
		break;
	case SB_THUMBPOSITION:
	case SB_THUMBTRACK:
		sy=nPos;
		break;  
	};
	vy=sy-dy;
	if(vy!=0){
		dy=sy;
		bar.SetScrollPos(sy);
		ReDrawObj();
	};
	CWnd::OnVScroll(nSBCode, nPos, pScrollBar);
}

void egpwin::OnLButtonDown(UINT nFlags, CPoint point) 
{
	int k;
	k=point.y/55+dy;
	if(k<cobj.selsum){
		selpic=k;
		CClientDC dc(this);
		ShowEPIC();
		mdc.BitBlt(dc.m_hDC,CRect(0,0,400,wy-22));
	}
	SetFocus();
	CWnd::OnLButtonDown(nFlags, point);
}

LRESULT egpwin::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	if(message==WM_COMMAND&&wParam>=0&&wParam<16){ //选择命令
		NewTypeSel(wParam);
	}
	return CWnd::WindowProc(message, wParam, lParam);
}

void egpwin::NewTypeSel(int cmd)
{
	dy=0;
	switch(cmd){
	case 0:
		m_curtype = 255;
		m_cursubtype = 255;
		break;
	case 1:
		m_curtype = 1;
		m_cursubtype = 2;
		break;
	case 2:
		m_curtype = 1;
		m_cursubtype = 7;
		break;
	case 3:
		m_curtype = 1;
		m_cursubtype = 8;	
		break;
	case 4:
		m_curtype = 1;
		m_cursubtype = 3;
		break;
	case 5:
		m_curtype = 1;
		m_cursubtype = 4;
		break;
	case 6:
		m_curtype = 1;
		m_cursubtype = 6;
		break;
	case 7:
		m_curtype = 1;
		m_cursubtype = 0;
		break;
	case 8:
		m_curtype = 1;
		m_cursubtype = 5;
		break;
	case 9:
		m_curtype = 1;
		m_cursubtype = 1;
		break;
	case 10:
		m_curtype = 1;
		m_cursubtype =9;
		break;
	case 11:
		m_curtype = 1;
		m_cursubtype =10;
		break;
	case 12:
		m_curtype =  2;
		m_cursubtype = 255;
		break;
	case 13:
		m_curtype =  3;
		m_cursubtype = 255;
		break;
	case 14:
		m_curtype=0;
		m_cursubtype=0;
	}
	computpage();
	SetYScroll();
	ReDrawObj();
}

//保存为一个磁盘文件
void egpwin::SaveEGP(char *filename)
{
	FileV30 fv3;
	FILE*fp;
	int i,j,m,n,size;
	char *lp;
	char *wbuf;     //写入缓冲区
	char *pbuf;		//压缩后的缓冲区
	N_EGPHEAD head;
	N_EGPDATA *eda;
	n=cobj.egpsum;
	cmpress cps;
	//第一步:计算各图元的字节数
	size=n*sizeof(N_EGPDATA);
	for(i=0;i<n;i++){
	  size+=cobj.GetEleGrpSize(i,0);
	  size+=cobj.GetEleGrpSize(i,1);
	};
	//申请内存
	wbuf=new char[size+100];
	pbuf=new char[size+100];
	//填充数据
	eda=(N_EGPDATA *)wbuf;
	for(i=0;i<n;i++){
	  eda[i].sav=cobj.egp[i];
	  eda[i].start=0x10891112;
	  eda[i].size1=cobj.GetEleGrpSize(i,0);
	  eda[i].size2=cobj.GetEleGrpSize(i,1);
	 };
	lp=wbuf+n*sizeof(N_EGPDATA);
	
	for(i=0;i<n;i++){
		for(j=0;j<eda[i].sav.bsum1;j++){ //拷贝第一组数据
			m=fv3.CopyV5Data(cobj.egp[i].bs1[j],lp);
			lp+=m;
		};

		for(j=0;j<eda[i].sav.bsum2;j++){ //拷贝第一组数据
			m=fv3.CopyV5Data(cobj.egp[i].bs2[j],lp);
			lp+=m;
		};
	};
	//压缩数据
	cps.initdata();
	m=cps.EEnCode(wbuf,pbuf,size,size+100);
	//填充头
	head.flag=0x20010215;
	head.version=0x500;  //v5版 0x200为V2版
	head.picsum=n;
	head.press=1;
	head.size=size;		//压缩前字节数
	head.psize=m;		//压缩后字节数
	//写入磁盘文件
	fp=fopen(filename,"w+b");
	if(fp!=NULL){
		fwrite(&head,sizeof(N_EGPHEAD),1,fp); //写头
		fwrite(pbuf,m,1,fp);				//写入压缩数据
		fclose(fp);
	};
	delete wbuf;
	delete pbuf;
}


void egpwin::OnSaveegrp() 
{
	char filter[256];
	char fnm[256];
	char *lp;
	if(cobj.egpsum<=0){
		MessageBox("组合图元中没有图形");
		return;
	};
	if(fbz==1){
		SaveEGP(filenm);
		return;
	}
	strcpy(filter,"图形组文件(*.NDV)|*.ndv");
	CFileDialog  fodlg(false,NULL,NULL,
		OFN_CREATEPROMPT|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	if(fodlg.DoModal()==IDOK){
	  strcpy(fnm,fodlg.GetPathName());
	  lp=strchr(fnm,'.');
	  if(lp!=NULL) *lp=0;
	  strcat(fnm,".ndv");
	  SaveEGP(fnm);
	  fbz=1;
	  strcpy(filenm,fnm);
	};
}

void egpwin::OnSaveas() 
{
	char filter[256];
	char fnm[256];
	char *lp;
	if(cobj.egpsum<=0){
		MessageBox("组合图元中没有图形");
		return;
	};
	strcpy(filter,"图形组文件(*.ndv)|*.ndv");
	CFileDialog  fodlg(false,NULL,NULL,
		OFN_CREATEPROMPT|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,this);
	if(fodlg.DoModal()==IDOK){
	  strcpy(fnm,fodlg.GetPathName());
	  lp=strchr(fnm,'.');
	  if(lp!=NULL) *lp=0;
	  strcat(fnm,".ndv");
	  SaveEGP(fnm);
	  fbz=1;
	  strcpy(filenm,fnm);
	};
}

void egpwin::OnAddempty() 
{
	if(!cobj.AddAEmptyEGP(0)) return;
	if(m_curtype!=255) cobj.egp[cobj.egpsum-1].type = m_curtype;
	if(m_cursubtype!=255) cobj.egp[cobj.egpsum-1].subtype = m_cursubtype;
	computpage();
	selpic = cobj.selsum-1;
	if(cobj.selsum>maxy) dy=selpic-maxy+1;
	SetYScroll();
	ReDrawObj();
}

void egpwin::OnPastenormal() 
{
	int i,j;
	CDRect rt1,rtt;
	if(selpic>=cobj.selsum) return;
	j=cobj.typeidx[selpic];
	if(j>=cobj.egpsum)      return;



	//察看是否剪贴板里有
	dbm.GetEleFromClipboard(m_hWnd);
	////////////////////////////
	for(i=0;i<dbm.cpysum;i++)
	{
		if(!dbm.cpyobj[i].IsRotateObj())
		{
			MessageBox("欲作组合图元的图形组中包含了非基本图形对象！","错误");	
			return;
		};
	};
	//如果原来有对象，清除
	if(cobj.egp[j].bs1!=NULL){
	  if(MessageBox("是否替换原来的图形?","提示",MB_YESNO)==IDNO) return;	
	};
	cobj.FreeEgp(j,0);
	//查看有效的图元对象
	for(i=0;i<dbm.cpysum;i++){
	 cobj.AddAEGP(j,0,dbm.cpyobj[i].attr,dbm.cpyobj[i].buf); 
	};
	rt1.SetRectEmpty();
	for(i=0;i<cobj.egp[j].bsum1;i++){
		if(cobj.egp[j].bs1[i].attr.type==32) continue;
		rtt=cobj.egp[j].bs1[i].ort;
		if(rt1.IsRectEmpty()) rt1=rtt;
		else rt1|=rtt;
	  };
	rt1.GetDRECT(cobj.egp[j].rt1);
	ReDrawObj();
}

void egpwin::OnPastealarm() 
{
	CDRect rt1,rtt;
	int i,j;
	if(selpic>=cobj.selsum) return;
	j=cobj.typeidx[selpic];
	if(j>=cobj.egpsum) return;
	//察看是否剪贴板里有
	dbm.GetEleFromClipboard(m_hWnd);
	////////////////////////////////////////
	for(i=0;i<dbm.cpysum;i++)
	{
		if(!dbm.cpyobj[i].IsRotateObj())
		{
			MessageBox("欲作组合图元的图形组中包含了非基本图形对象！","错误");	
			return;
		};
	};
	if(cobj.egp[j].bs2!=NULL)
	{
	  if(MessageBox("是否替换原来的图形?","提示",MB_YESNO)==IDNO) return;	
	};
	//如果原来有对象，清除
	cobj.FreeEgp(j,1);
	//查看有效的图元对象
	for(i=0;i<dbm.cpysum;i++){
	 cobj.AddAEGP(j,1,dbm.cpyobj[i].attr,dbm.cpyobj[i].buf); 
	};
	rt1.SetRectEmpty();
	for(i=0;i<cobj.egp[j].bsum2;i++){
		rtt=cobj.egp[j].bs2[i].ort;
		if(rt1.IsRectEmpty()) rt1=rtt;
		else rt1|=rtt;
	  };
	rt1.GetDRECT(cobj.egp[j].rt2);
	ReDrawObj();
}

void egpwin::OnDelaegrp() 
{
	int i,j,k,id;
	if(selpic>=cobj.selsum||cobj.selsum<=0) return;
	//第一步：查看本图元是否在使用
	k=cobj.typeidx[selpic];
	id=cobj.egp[k].id;
	bool b=dbm.EgrpInUse(id);
	if(!b){ //删除组合图元
	  cobj.FreeEgp(k,0);
	  cobj.FreeEgp(k,1);
	  for(i=k;i<cobj.egpsum-1;i++){
		 cobj.egp[i]=cobj.egp[i+1];
	  };
	  i=cobj.egpsum-1;
	  memset(&cobj.egp[i],0,sizeof(N_ELEGRP));
	  cobj.egpsum-=1;
	}
	else  MessageBox("当前的组合图元正在使用，不能删除");	
	j=selpic;
	computpage();
	if(j>=cobj.selsum) j=0;
	selpic=j;
	ReDrawObj();
}

void egpwin::OnCopytodesk() 
{
	int k;
	if(cobj.selsum<=0||selpic>=cobj.selsum)
	{
		MessageBox("没有选择图形!");
		return;
	}
	k=cobj.typeidx[selpic];
	if(cobj.egp[k].bs1==NULL){
		MessageBox("选择的图形第一幅图为空!");
		return;
	};
	cobj.patternID=cobj.egp[k].id;
	if(cobj.egp[k].type==0) cobj.cvs->AddegpYb();
	else cobj.cvs->Addegpr(0);
	cobj.tlsw->ReFreshWin();
}

void egpwin::OnSetup() 
{
	int i,j;
	if(selpic>=cobj.selsum)  return;
	i=cobj.typeidx[selpic];
	if(i>cobj.egpsum) return;
	egatrdlg dlg(i);
	dlg.DoModal();
	j=selpic;
	computpage();
	if(j>=cobj.selsum) j=0;
	selpic=j;
	ReDrawObj();
}


void egpwin::OnRButtonDown(UINT nFlags, CPoint point) 
{
	CPoint pt;
	CMenu *mm;
	pt=point;
	ClientToScreen(&pt);
	mm=menu.GetSubMenu(0);
	mm->TrackPopupMenu(TPM_LEFTALIGN,pt.x,pt.y,this);
	CWnd::OnRButtonDown(nFlags, point);
}

BOOL egpwin::OnMouseWheel(UINT nFlags, short zDelta, CPoint pt) 
{
	int sy,vy,y;
	y=zDelta>0 ? 1:2;
	sy=dy;
	switch(y){
	case 2:
		sy=sy<cobj.selsum-1 ? sy+1:sy;	
		break;
	case 1:
		sy=sy>0 ? sy-1:0;
		break;
	};
	vy=sy-dy;
	if(vy!=0){
		dy=sy;
		bar.SetScrollPos(sy);
		ReDrawObj();
	};
	return CWnd::OnMouseWheel(nFlags, zDelta, pt);
}
