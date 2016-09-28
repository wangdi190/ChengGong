// comobj.cpp: implementation of the comobj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "visualpower.h"
#include "comobj.h"
#include "middll.h"
#include <direct.h>
#include <io.h>
#include "dbapi.h"
#include "sethisdlg.h"
#include "prtmode.h"
#include "cfgshow.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


DWORD vcrd[]={0xff7080,0xff0080,0xaaebeb,0xffffff,0xc000c0,0xffff00,0x8000ff,
			  0xd0c0a8,0x80ff,0x70ffff,0x80ffeb,0x8080ff,0xff00,0x80ff80,
			  0x8a,0xf00000,0xf000,0x374b87,0x808080,0xc0c0c0,0x4040f0};
char  *vnm[]={"1100kV","750kV","500kV","330kV","220kV","110kV",
			  "66kV","38kV","35kV","22kV","20kV","18kV","15kV","14kV"
			  "10kV","6kV","3kV","1kV","0.38kV","0.22kV"};

char *keyw[]={"[DEFAULTPAGE]","[MENU]","[HOTKEY]","[AUTOTP]","[LOWF]","[ALARMSND]","[LOWFSND]"};
char *fkey[]={"F1","F2","F3","F4","F5","F6","F7","F8","F9"};

CPoint *mpt; //临时用的一个点缓冲区，最大1024个点
DPOINT *npt;
char   *buff;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

comobj::comobj()
{ 
	GetSysMemory();
	fwin=NULL; //框架窗口
	mwin=NULL; //主窗口
	hbar=NULL; //历史重演工具条
	sbar=NULL; //SCADA工具条
	vbar=NULL; //统计棒
	swin=NULL; //scada窗口
	tbar=NULL; //状态条地址
	nwin=NULL;
	InitParam();
	daoban=0;
	//初始化数据库
	////////////////必须初始化，否则系统不能读取实时库///////////////////////
	//dbok=InitMemDbf();
	dbok=LSI_InitNTDbi();
	if(dbok) LSI_CheckUser("sa","");
	CFont cf;
	cf.CreateFont(128,64,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"楷体" );
	cf.GetLogFont(&font1);
	cf.DeleteObject();

}

comobj::~comobj()
{
    int i;
	for(i=0;i<gpsum;i++)
	{
		if(gp[i].pm!=NULL) delete gp[i].pm;
		gp[i].menu.DestroyMenu();
	};
	if(hotsum>0) delete []hotkey;
	if(fbus!=NULL) delete []fbus;
	if(sysbuf!=NULL) delete sysbuf;
}


//分配系统常用内存
void comobj::GetSysMemory()
{
	int size;
	size=65536+sizeof(CPoint)*1024+sizeof(DPOINT)*1024+256;
	sysbuf=new char[size];
	buff=sysbuf;
	mpt=(CPoint *)(sysbuf+65536); //临时用的一个点缓冲区，最大1024个点
	npt=(DPOINT *)(sysbuf+65536+sizeof(CPoint)*1024);
	syssize=size;
}

//初始化参数
void comobj::InitParam()
{
	int i;
	char path[256];
	for(i=0;i<21;i++) vcolor[i]=vcrd[i];; //初始化颜色
	for(i=0;i<10;i++) hcur[i]=NULL;
	curnm[0]=0;	
	curpw[0]=0;	
	autotp=0;
	utype=3;//最低级用户
	////////////////////////////////
	for(i=0;i<10;i++)
	{
		gp[i].pm=NULL;
		gp[i].pmsum=0;
		strcpy(gp[i].popname,"未定义");
	}
	mpok=0;
	curgp=-1;
	strcpy(mainpage.filename,"");
	mainpage.index=0;
	strcpy(Lowfpage.filename,"");
	Lowfpage.index=0;
	GetCurrentDirectory(255,runpath);	//读入当前路径
	strcpy(startpath,runpath);			//当前目录保存
	strcat(runpath,"\\hmifile");		//构造界面文件目录
	strcpy(senfilepath,startpath);		//灵敏度文件目录
	strcat(senfilepath,"\\datfile");
	TestDir(senfilepath);
	//if(GetHmiPath(path)) strcpy(runpath,path);
	if(LSI_GetHmiPath(path)) strcpy(runpath,path);
	hotsum=0;
	fbus=NULL;			//已关联
	fsum=0;				//关联个数
}


void comobj::LoadImg()
{
	//simg.Create(IDB_BITMAP1,32,0,RGB(255,0,255));

	simg.Create(24,24,ILC_COLOR32|ILC_MASK, 10,2);
	CBitmap bm;
	bm.LoadBitmap(IDB_BITMAP1);
	simg.Add(&bm, RGB(255,0,255));
}

void comobj::ShowSimg(HDC hdc,int x,int y,int index, int width, int height)
{
	x-=width;
	y-=width;

	CDC dc;
	if(index<0||index>13) return;
	dc.Attach(hdc);
	//simg.Draw(&dc,index,CPoint(x,y),ILD_NORMAL);
	simg.DrawIndirect(&dc, index, CPoint(x, y), 
      CSize(width*2, width*2), CPoint(0, 0));
	dc.Detach();
}


void comobj::SetCurUser(char *user, char *pw,int ut)
{
	strcpy(curnm,user);
	strcpy(curpw,pw);
	utype=ut;
}


//设置电压颜色
void comobj::SetVLColor(char *vlname,DWORD color)
{
	int i;
	for(i=0;i<20;i++)
	{
		if(strcmp(vlname,vnm[i])==0)
		{
			vcolor[i]=color;
			break;
		}
	}
}

//读入预定义颜色
void comobj::ReadDefColor()
{
	int i;
	DEFCOLOR cr[25];
	int crsum=0;
	//if(ReadColorData==NULL) return;
	//ReadColorData(cr,crsum);
	swin->rrd.ReadColorData(cr,crsum);
	for(i=0;i<crsum;i++)
	{
		SetVLColor(cr[i].VLName,RGB(cr[i].R,cr[i].G,cr[i].B));
	}
}

//类型转换：用于读取设备参数
int comobj::TypeTran(int type, int subtype)
{
	if(type!=2) return -1;
	switch(subtype)
	{
	case 1: return 0; //发电机
	case 34:return 1; //交流线
	case 35:return 2; //直流线
	case 33:return 3; //母线
	case 3: return 4; //负荷
	case 7: return 5; //2绕组变压器
	case 8: return 6; //3绕组变压器
	case 4: return 7; //电容器
	case 5: return 8; //电抗器
	case 9: return 9; //SVC
	default:
		return -1;
	}
	return -1;
}

//加入一个菜单项
void comobj::AddMenuItem(char *nm, char *fnm, WORD index)
{
	int n;
	n=gp[curgp].pmsum;
	if(n==0)
	{
	  gp[curgp].pm=new I_MENU;
	};
	if(n>0)
	{
	  gp[curgp].pm=(I_MENU*)realloc(gp[curgp].pm,sizeof(I_MENU)*(n+1));
	};
	strcpy(gp[curgp].pm[n].itemname,nm);
	strcpy(gp[curgp].pm[n].filename,fnm);
	gp[curgp].pm[n].index=index;
	n++;
	gp[curgp].pmsum=n;
}
//读入初始化文件
void comobj::ReadIni_File()
{
	FILE *fp;
	char line[256];
	char fnm[288];
	//读入初始化文件
	strcpy(fnm,runpath);
	strcat(fnm,"\\");
	strcat(fnm,"pwhmi.ini");
	fp=fopen(fnm,"r+b");
	if(fp==NULL){
		MessageBox(0,"初始化文件pwhmi.ini不存在","错误",MB_OK);
		return;
	}
	//读入初始化文件
	for(;;){
		if(feof(fp)) break;
		if(!ReadLine(fp,line)) break;
		AnalyseLine(fp,line);
	}
	fclose(fp);
	if(mpok==0){
		strcpy(mainpage.filename,"default.pw0");
		mainpage.index=0;
		mpok=1;
	}
	MakeMenu();//生成系统菜单
}	
//读入一行
bool comobj::ReadLine(FILE *fp, char *buf)
{
	int i;
	char c;
	if(feof(fp)) return false;
	for(i=0;i<255;i++){
		c=(char)fgetc(fp);
		if(c==0xd||c==0xa){
		  fgetc(fp);
		  break;
		}else buf[i]=(char)c;
		if(feof(fp)) break;
	}
	buf[i]=0;
	return true;
}

//分析语法
void comobj::AnalyseLine(FILE *fp,char *line)
{
	int j;
	j=IsKeyw(line);
	switch(j){
	case 0:   //主页标题
		GetMainPage(fp);	
		break;
	case 1:   //菜单标题
		GetMenu(fp);
		break;
	case 2:   //读取热键定义
		ReadHotKey(fp);
		break;
	case 3:   //读取是否自动拓扑
		ReadAutotp(fp);
		break;
	case 4:	  //读取低频震荡界面
		GetLowfFile(fp);
		break;
	case 5:   //告警声音
		GetSndFile(fp);
		break;
	case 6:   //低频振荡声音
		GetLOWFSndFile(fp);
		break;
	}
}

int comobj::IsKeyw(char *buf)  //察看是否主键
{
	int i;
	for(i=0;i<7;i++){
	 if(strcmp(buf,keyw[i])==0) return i;
	}
	return -1;
}
//读入主页面
void comobj::GetMainPage(FILE *fp)
{
	char line[256];
	char s1[64];
	int  n,index;
	if(!ReadLine(fp,line)) return;
	n=sscanf(line,"%s %d\n",s1,&index);
	if(n==2&&mpok==0){
		strcpy(mainpage.filename,s1);
		mainpage.index=index;
		strcpy(mainpage.itemname,"主页面");
		mpok=1; //表示主页面读入成功
	}
}

//读入低频震荡页面
void comobj::GetLowfFile(FILE *fp)
{
	char line[256];
	char s1[64];
	int  n,index;
	if(!ReadLine(fp,line)) return;
	n=sscanf(line,"%s %d\n",s1,&index);
	if(n==2){
		strcpy(Lowfpage.filename,s1);
		Lowfpage.index=index;
	}
}

//读入声音文件
void comobj::GetSndFile(FILE *fp)
{
	char line[256];
	char s1[64];
	int  n;
	if(!ReadLine(fp,line)) return;
	n=sscanf(line,"%s\n",s1);
	if(n!=1) strcpy(s1,"default.wav");
	SetToLocalFile(s1, sndfile);
}

//读入声音文件
void comobj::GetLOWFSndFile(FILE *fp)
{
	char line[256];
	char s1[64];
	int  n;
	if(!ReadLine(fp,line)) return;
	n=sscanf(line,"%s\n",s1);
	if(n!=1) strcpy(s1,"default.wav");
	SetToLocalFile(s1, lowfsnd);
}

//读入菜单
void comobj::GetMenu(FILE *fp)
{
	char buf[256];
	char *p1;
	for(;;){  //读入最大10个菜单
		if(feof(fp)) break;
		if(!ReadLine(fp,buf)) break;
		p1=strchr(buf,'{');
		if(p1!=NULL){
		  *p1=0;
		  if(curgp<9)
		  {
			curgp++;
			strcpy(gp[curgp].popname,buf);
			//读取子项目
			ReadSubMenu(fp);
		  }
		}
		if(curgp>=9) break;  //达到10个菜单，退出
	}
	gpsum=curgp+1;
	ComputCMD();
}
//读入子菜单项
void comobj::ReadSubMenu(FILE *fp)
{
	char buf[256];
	char s1[64],s2[64];
	int  n,num;
	char *p1,*p2;
	for(;;){
		if(feof(fp)) break;
		if(!ReadLine(fp,buf)) break;
		p1=strchr(buf,'}');
		if(p1!=NULL) break;
		p2=GetMenuName(s1,buf);
		if(p2==NULL) continue;
		n=sscanf(p2,"%s %d\n",s2,&num);
		if(n!=2) continue;

		AddMenuItem(s1,s2,(WORD)num);
	}
}
//计算命令ID
void comobj::ComputCMD()
{
	int i,j,n;
	n=39000;
	for(i=0;i<gpsum;i++){
      gp[i].menu.CreatePopupMenu();
	  for(j=0;j<gp[i].pmsum;j++)
	  {
		  gp[i].pm[j].cmdid=n;
		  gp[i].menu.AppendMenu(MF_STRING,n,gp[i].pm[j].itemname);
		  n++;
		}
	}
}
//返回一个页面的文件名和序号
bool comobj::GetCMDPage(int id, char *fnm, int &num)
{
	int i,j;
	for(i=0;i<gpsum;i++){
		for(j=0;j<gp[i].pmsum;j++)
		{
			if(id==gp[i].pm[j].cmdid){
				strcpy(fnm,gp[i].pm[j].filename);
				num=gp[i].pm[j].index;
				return true;

			}
		}
	}
	return false;
}


//察看文件是否存在
bool comobj::IsFileExist(char *filename)
{
	CFileFind fnd;
	BOOL b=fnd.FindFile(filename);
	fnd.Close();
	return b!=0 ? true:false;
}

void comobj::SetToLocalFile(char *infile, char *outfile)
{
	char *p1;
	char fm[512];
	char name[256];
	strcpy(name,infile);
	
	p1=strrchr(name,'\\');
	if(p1!=NULL) p1++;
	else p1=name;
	sprintf(fm,"%s\\%s",runpath,p1);
	if(IsFileExist(fm)){
		strcpy(outfile,fm);
		return;
	  }
	sprintf(fm,"%s\\%s",startpath,p1);
	if(IsFileExist(fm)){
		strcpy(outfile,fm);
		return;
	  }
	if(IsFileExist(name)){
		strcpy(outfile,name);
		return;
	}
	strcpy(outfile,infile);
}


//增加一个热键
void comobj::AddHotKey(I_HOTKEY hk)
{
	int n;
	n=hotsum;
	if(n==0){
	  hotkey=new I_HOTKEY;
	};
	if(n>0){
	  hotkey=(I_HOTKEY*)realloc(hotkey,sizeof(I_HOTKEY)*(n+1));
	};
	hotkey[n]=hk;
	n++;
	hotsum=n;
}
//查找一个标准的F键
int comobj::FindKey(char *key)
{
	int i;
	for(i=0;i<9;i++){
		if(strcmp(key,fkey[i])==0) return i;
	}
	return -1;
}
//读入热键
void comobj::ReadHotKey(FILE *fp)
{
	I_HOTKEY hk;
	char line[256];
	char k1[64],k2[64];
	BYTE type,val;
	int  n,m=0;
	for(;;){
	   if(!ReadLine(fp,line)) return;
	   if(IsKeyw(line)>=0){  //如果是关键字，转其他分析
			AnalyseLine(fp,line);
			return;
		}
	  n=sscanf(line,"%s %s %d\n",k1,k2,&m);
	  if(n==3){ //能读入三个项
		  if(AnalyHotKey(k1,type,val)){
			hk.type=type;
			hk.kvalue=val;
			hk.index=m;
			strcpy(hk.filename,k2);
			AddHotKey(hk);
		  }
	  }
	}
}



//分析热键的码值及类型
bool comobj::AnalyHotKey(char *kstr, BYTE &type, BYTE &val)
{
	int i;
	//第一步：察看是否是F键
	i=FindKey(kstr);
	if(i>=0){ //是F键
      type=1;
	  val=(BYTE)(i+112);
	  return true;
	}
	if(strlen(kstr)>1) return false;        //多余一个字符
	type=0;
	val=BYTE(kstr[0]);
	return true;
}

//返回热键驱动的画面
bool comobj::GetHotPic(BYTE type, BYTE val, char *fnm, int &index)
{
	int i;
	for(i=0;i<hotsum;i++){
		if(type==hotkey[i].type&&val==hotkey[i].kvalue){
			strcpy(fnm,hotkey[i].filename);
			index=hotkey[i].index;
			return true;
		}
	}
	return false;
}

//读取是否自动拓扑标志
void comobj::ReadAutotp(FILE *fp)
{
	int n;
	char buf[256];
	char s1[256];
	if(feof(fp)) return;
	if(!ReadLine(fp,buf)) return; 
	n=sscanf(buf,"%s\n",s1);
	autotp=0;
	if(n==1){
		if(strcmp(s1,"ON")==0) autotp=1;
	}
}


//生成定义的菜单
void comobj::MakeMenu()
{
	int i;
	CMenu *mm;
	//准备菜单
	menu.LoadMenu(IDR_MAINFRAME);
	fmenu.LoadMenu(IDR_FMENU);
	for(i=0;i<gpsum;i++){
	   menu.InsertMenu( 1, MF_POPUP|MF_BYPOSITION,(UINT)gp[gpsum-i-1].menu.m_hMenu,
		   gp[gpsum-i-1].popname );
	}
	//组装右键菜单
	rmenu.CreatePopupMenu();
	mm=fmenu.GetSubMenu(0);
	rmenu.InsertMenu( 0, MF_BYPOSITION,1800,"主界面(&m)");

    for(i=0;i<gpsum;i++){
	   rmenu.AppendMenu(MF_POPUP,(UINT)gp[i].menu.m_hMenu,gp[i].popname);	
	   if(mm!=NULL) mm->AppendMenu(MF_POPUP,(UINT)gp[i].menu.m_hMenu,gp[i].popname);
	}
}

void comobj::TestDir(char *path)
{
	long hfind;
	struct _finddata_t ffblk;
	hfind=_findfirst(path, &ffblk);
	if(hfind==-1) _mkdir(path);
	if(hfind!=-1) _findclose(hfind);
}
//装入母线图形关联文件
void comobj::LoadBusRalate()
{
	char fnm[256];
	BFHEAD head;
	FILE  *fp;
	strcpy(fnm,runpath);
	strcat(fnm,"\\bsralate.cfg");
	fp=fopen(fnm,"r+b");
	if(fp==NULL) return;
	fread(&head,sizeof(BFHEAD),1,fp);
	if(head.flag!=0xd0||head.version!=0x10||head.sum==0)
	{
		fclose(fp);
		return;
	}
	if(fbus!=NULL) delete []fbus;
	fsum=head.sum;
	fbus=new BUSFILE[fsum];
	fread(fbus,sizeof(BUSFILE),fsum,fp);
	fclose(fp);
}
//返回BusID关联的图形
bool comobj::GetBusGrp(int id, char *grpname, int &pno)
{
	int i;
	for(i=0;i<fsum;i++)
	{
		if(id==fbus[i].id)
		{
			strcpy(grpname,fbus[i].grpfile);
			pno=fbus[i].index;
			return true;
		}
	}
	return false;
}


char *comobj::GetMenuName(char *nbuf, char *lbuf)
{
	char *lp1,*lp2;
	nbuf[0]=0;
	lp1=strchr(lbuf,'[');
	lp2=strrchr(lbuf,']');
	if(lp1==NULL||lp2==NULL) return NULL;
	*lp2=0;
	strcpy(nbuf,lp1+1);
	return lp2+1;
}


//按指定模式推出画面
void comobj::SetToNeedMode(int mode)
{
	switch(mode)
	{
	case 0://正常
		ResetFunct(0,1);
		break;
	case 1://电压等高线
		fwin->PostMessage(WM_COMMAND,IDC_DGXBUS,NULL);
		Showdgx();
		break;
	case 2://线路等高线
		fwin->PostMessage(WM_COMMAND,IDC_LINELOAD,NULL);
		Showdgx();
		break;
	case 3://发电机备用
		Genrev();
		break;
	case 4://无功备用IDC_GENREVQ
		Genrevq();	
		break;
	case 5://变压器备用
		Tranrev();	
		break;
	case 6://低频震荡
		ToLowf();
		break;
	case 7://断面潮流
		Dmflow();	
		break;
	case 8: //灵敏度计算
		Senopr();
		break;
	case 9: //历史数据库回放
		Starthis();
		break;
	case 10: //N-1故障分析
		N_1Operator(5,0);	
		break;
	case 11: //开关SOE回放
		StartSoe();
		break;
	case 12: //短路电流结果展示
		DlDlperator();
		break;
	case 13: //手动短路电流计算
		ManuDlperator();
		break;
	}
}

//打印当前页面
void comobj::PrintPage() 
{
	double oldcurzoom;			
	int    oldzw,oldzh;		
	int	   oldcurang;		
	int    oldlookdown;	
	BYTE pm;
	char p[100];
	double pdx,pdy;
	int i,j,mok,mx,my;
	int yl,w,h,kw,kh,dx,dy,ht,mh;
	DEVMODE *dev,devmode;
	double bl;
	CPrintDialog pdlg(true);
	if(pdlg.DoModal()==IDOK){
		dev=pdlg.GetDevMode();
		devmode=dev[0];
	}else return;

	PMODE lppm;
	prtmode pmdlg(&lppm);
	mok=pmdlg.DoModal();
	if(mok==IDCANCEL) return;
	if(lppm.mode<1) pm=1;else pm=0;

	
	HDC hdc=pdlg.CreatePrinterDC();
	if(hdc==NULL){
		MessageBox(0,"当前选择的打印机不存在\n请重新选择打印机后再式","错误",MB_OK|MB_ICONSTOP);	
		return;
	}
	kw=dbm->page.head.width;
	kh=dbm->page.head.height;
	yl=-devmode.dmPrintQuality;
	
	if(devmode.dmOrientation==1){ //确定方向:1为正常方向
		w=devmode.dmPaperWidth-100;
		h=devmode.dmPaperLength-100;
	}else{						  //横向打印
		h=devmode.dmPaperWidth-100;
		w=devmode.dmPaperLength-100;
	};
	//每页纸的象素大小
	//w=(int)(w*yl/255);
	//h=(int)(h*yl/255);
	w=(int)(w*yl);
	h=(int)(h*yl);

	oldcurzoom=dbm->curzoom;	
	oldzw=dbm->zw;
	oldzh=dbm->zh;			
	oldcurang=dbm->curang;			
	oldlookdown=dbm->lookdown;		

	dbm->lookdown=0;
	dbm->curang=0;
	bl=kw/(double)kh;
	ht=(int)(w/bl);
	//单张纸的特殊处理方式
	if(lppm.px==0){
	  if(ht<h){
			dx=0;
			dy=((h-ht)*kw/w)/2;
			h=ht;
		}else{	
			dy=0;
			dx=(int)(((w-h*bl)*kh/h)/2);
			w=(int)(h*bl);
		}
		dbm->curzoom=(double)w/(double)kw;
		swin->Set3DEnv();
		//////////////// 打 印 到 纸 上 ///////////////////
		StartDoc(hdc,NULL);
		SetMapMode(hdc,MM_ISOTROPIC);
		SetWindowExtEx(hdc,w,h,NULL);
		SetViewportExtEx(hdc,w,h,NULL);
		StartPage(hdc);
		swin->PrintPage(hdc,pm,dx,dy);
		EndPage(hdc);
		EndDoc(hdc);
		DeleteDC(hdc);
		///////////////////////////////////////////////////
	}
	//放大打印
	if(lppm.px>0){
		mx=lppm.px+1;  //x方向的纸张数
		mh=ht*mx;	   //需要的总高度
		my=mh/h;	   //计算纵向所需纸张数
		j=mh-my*h;
		if(j>0) my++;
		sprintf(p,"所需纸张数:%d张。\n还需打印吗? ",mx*my);
		mok=MessageBox(0,p,"打印最后确认",MB_YESNO);
		if(mok==IDNO) return;
		w=w*mx;
		pdx=(double)((double)w/(double)mx);
		pdy=(double)h;
		dbm->curzoom=(double)w/(double)kw;
		swin->Set3DEnv();
		for(i=0;i<my;i++){
			for(j=0;j<mx;j++){
				//////////////// 打 印 到 纸 上 ///////////////////
				dx=(int)(j*pdx);
				dy=(int)(i*pdy);
				StartDoc(hdc,NULL);
				SetMapMode(hdc,MM_ISOTROPIC);
				SetWindowExtEx(hdc,w,mh,NULL);
				SetViewportExtEx(hdc,w,mh,NULL);
				StartPage(hdc);
				swin->PrintPage(hdc,pm,-dx,-dy);
				EndPage(hdc);
				EndDoc(hdc);
				///////////////////////////////////////////////////
			}
		}
		DeleteDC(hdc);
	}
	dbm->curzoom=oldcurzoom;	
	dbm->zw=oldzw;
	dbm->zh=oldzh;			
	dbm->curang=oldcurang;			
	dbm->lookdown=oldlookdown;
	swin->Set3DEnv();
}

//正常大小
void comobj::Zoomnml() 
{
	dbm->curzoom=1;
	swin->ZoomChange();
	if(dbm->scf.showdgx==1) swin->sct.DrawDgxinMem(swin->msr,dbm->curzoom,swin->dx,swin->dy);
	swin->CreateAllrgn();
	swin->EndShow();
	swin->SetStatusZoom();
}

//保存为位图
void comobj::Savetobmp() 
{
	char filter[512];
	char fnm[512];
	char *lp;
	strcpy(filter,"Windows bmp文件(*.BMP)|*.bmp");
	CFileDialog  fodlg(false,NULL,NULL,
		OFN_CREATEPROMPT|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,0);
	if(fodlg.DoModal()==IDOK)
	{
	  strcpy(fnm,fodlg.GetPathName());
	  lp=strchr(fnm,'.');
	  if(lp!=NULL) *lp=0;
	  strcat(fnm,".bmp");
	  swin->DrawShow();
	  dbm->SaveToBmp(swin->m_hWnd,swin->wx,swin->wy,fnm);
	  MessageBox(0,"保存为BMP文件完成！","保存位图",MB_OK);
	 };
	
}

void comobj::Savetojpg() 
{
	char filter[512];
	char fnm[512];
	char *lp;
	strcpy(filter,"JPEG文件(*.jpg)|*.jpg");
	CFileDialog  fodlg(false,NULL,NULL,
		OFN_CREATEPROMPT|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,filter,0);
	if(fodlg.DoModal()==IDOK)
	{
	  strcpy(fnm,fodlg.GetPathName());
	  lp=strchr(fnm,'.');
	  if(lp!=NULL) *lp=0;
	  strcat(fnm,".jpg");
	  swin->DrawShow();
	  dbm->SaveToJpg(swin->m_hWnd,swin->wx,swin->wy,fnm);
	  MessageBox(0,"保存为JPG文件完成！","保存JPG",MB_OK);
	 }
}

void comobj::Zoomall() 
{
	swin->SetFirstPosition();
	if(dbm->scf.showdgx==1) swin->sct.DrawDgxinMem(swin->msr,dbm->curzoom,swin->dx,swin->dy);
	swin->EndShow();
	swin->SetStatusZoom();
}

void comobj::Senopr() 
{
	CloseHisPrc(); //如果处于历史态就关闭
	swin->CloseLowfWin();
	dbm->curopzt=dbm->curopzt==2 ? 0:2;
	dbm->lookdown=0;
	dbm->scf.showdgx=0;
	dbm->curang=0;
	swin->CursorChange(0);
	if(dbm->curopzt==2)
	{
		swin->SetCurFunction(FUN_SENOPR);
		dbm->scf.showrev=0;
		dbm->n1bz=-1;
		swin->dmsum=0;
	}else{
		dbm->scf.lmd=0;
		swin->SetCurFunction(swin->m_PreFun);
	}
	FunctChange();
}

void comobj::Bussen() 
{
	swin->CursorChange(8);
	dbm->lookdown=0;
	dbm->scf.lmd=0;
	dbm->curang=0;
	swin->Set3DEnv();
	if(dbm->scf.showdgx==1) swin->sct.DrawDgxinMem(swin->msr,dbm->curzoom,swin->dx,swin->dy);
	swin->CreateAllrgn();
	swin->EndShow();
}

void comobj::Linesen() 
{
	swin->CursorChange(7);
	dbm->lookdown=0;
	dbm->scf.lmd=0;
	dbm->curang=0;
	swin->Set3DEnv();
	if(dbm->scf.showdgx==1) swin->sct.DrawDgxinMem(swin->msr,dbm->curzoom,swin->dx,swin->dy);
	swin->CreateAllrgn();
	swin->EndShow();
}

//手动选择线路
void comobj::MdlSelLine() 
{
	swin->CursorChange(12);
	dbm->lookdown=0;
	dbm->scf.lmd=0;
	dbm->curang=0;
	swin->Set3DEnv();
	if(dbm->scf.showdgx==1) swin->sct.DrawDgxinMem(swin->msr,dbm->curzoom,swin->dx,swin->dy);
	swin->CreateAllrgn();
	swin->EndShow();
}

void comobj::Genrev() 
{
	swin->CloseLowfWin();
	dbm->curopzt=0;
	swin->dmsum=0;
	dbm->scf.showrev=1;
	dbm->scf.lmd=0;
	dbm->lookdown=1;
	dbm->scf.showdgx=0;
	swin->SetCurFunction(FUN_REVGEN);
	cwin->ShowWindow(SW_HIDE);
	swin->ToMyZm(1.15);
	FunctChange();
}

void comobj::Genrevq() 
{
	swin->CloseLowfWin();
	dbm->curopzt=0;
	swin->dmsum=0;
	dbm->scf.showrev=2;
	dbm->scf.lmd=0;
	dbm->lookdown=1;
	dbm->scf.showdgx=0;
	swin->SetCurFunction(FUN_REVGENQ);
	cwin->ShowWindow(SW_HIDE);
	swin->ToMyZm(1.15);
	FunctChange();
}

void comobj::Tranrev() 
{
	swin->CloseLowfWin();
	dbm->curopzt=0;
	swin->dmsum=0;
	dbm->scf.showrev=3;
	dbm->scf.lmd=0;
	dbm->lookdown=1;
	dbm->scf.showdgx=0;
	swin->SetCurFunction(FUN_REVTRANS);
	cwin->ShowWindow(SW_HIDE);
	swin->ToMyZm(1.15);
	FunctChange();
}

void comobj::Byqwd() 
{
	swin->CloseLowfWin();
	dbm->curopzt=0;
	dbm->scf.showrev=4; //变压器温度
	dbm->scf.lmd=0;
	dbm->lookdown=1;
	dbm->scf.showdgx=0;
	swin->SetCurFunction(FUN_TRANSTEMP);
	cwin->ShowWindow(SW_HIDE);
	swin->ToMyZm(1.15);
	FunctChange();
}

//菜单驱动的页面切换
void comobj::GoToCMDPage(int id)
{
	char p[256];
	char fnm[256],nm[64];
	HISHMI newhmi;
	int index;
	if(!GetCMDPage(id,nm,index)) return; //没有该ID的页面
	swin->GetCurHmi(newhmi);
	SetToLocalFile(nm,fnm);
	if(dbm->CheckFileIndex(fnm,index))
	{
		swin->CloseLowfWin();
		swin->enabletimer=0;
		swin->allupdate=0;
		swin->FreeMem();
		dbm->OpenPwFile(fnm,index);
		swin->InitMoveObj();
		dbm->AddOpenHmi(newhmi);
		return;
	}
	sprintf(p,"指定的画面不存在:%s %d\n请修改pwhmi.ini文件",fnm,index);
	MessageBox(0,p,"错误",MB_OK|MB_ICONERROR);
}

//根据键值推出画面
bool comobj::PutHotKeyPic(BYTE type, BYTE val)
{
	char fnm[256],nm[64];
	int  index;
	HISHMI newhmi;
	swin->GetCurHmi(newhmi);
	if(GetHotPic(type, val,nm,index))
	{
		SetToLocalFile(nm,fnm);
		if(dbm->CheckFileIndex(fnm,index))
		{
			swin->CloseLowfWin();
			swin->enabletimer=0;
			swin->allupdate=0;
			swin->FreeMem();
			dbm->OpenPwFile(fnm,index);
			swin->InitMoveObj();
			dbm->AddOpenHmi(newhmi);
			return true;
		}
		MessageBox(0,"热键指定的画面不存在，请修改pwhmi.ini文件","错误",MB_OK|MB_ICONERROR);
	}
	return false;
}

//重新打开文件
void comobj::ReOpenFile(char *filename)
{
	int oldpage;
	bool rtn;
	if(strcmp(filename,dbm->curfile)!=0) return; //不与当前界面文件相同
	if(!IsFileExist(filename))		return; //文件不存在 
	oldpage=dbm->curpage;
	swin->enabletimer=0;
	swin->allupdate=0;
	swin->FreeMem();
	rtn=dbm->OpenPwFile(filename,oldpage);
	if(!rtn) return;
	swin->InitMoveObj(NULL,0);
}

void comobj::Mainpage(bool first) 
{
	char fnm[256],nm[64];
	HISHMI newhmi;
	CloseHisPrc(); //如果处于历史态就关闭
	swin->CloseLowfWin();
	dbm->curopzt=0;
	dbm->n1bz=-1;
	dbm->scf.lmd=0;
	dbm->lookdown=0;
	if(!first) ReShowToolBar();
	swin->GetCurHmi(newhmi);
	strcpy(nm,mainpage.filename);
	SetToLocalFile(nm,fnm);
	if(dbm->CheckFileIndex(fnm,mainpage.index))
	{
		swin->FreeMem();
		dbm->OpenPwFile(fnm,mainpage.index);
		swin->InitMoveObj(NULL,0);
		if(!first) dbm->AddOpenHmi(newhmi);
		return;
	}
	MessageBox(0,"主画面和缺省页均不存在，请修改pwhmi.ini文件","错误",MB_OK|MB_ICONERROR);
}

void comobj::Newpage() 
{
	char fnm[256],nm[64];
	dbm->curopzt=0;
//	swin->dmsum=0;
	dbm->n1bz=-1;
	dbm->scf.lmd=0;
	dbm->lookdown=0;
	strcpy(nm,"newpage.pw0");
	SetToLocalFile(nm,fnm);
	if(dbm->CheckFileIndex(fnm,0))
	{
		swin->FreeMem();
		dbm->OpenPwFile(fnm,0);
		swin->InitMoveObj(NULL,0);
		return;
	}
	MessageBox(0,"newpage.pw0不存在","错误",MB_OK|MB_ICONERROR);
}

//配置属性
void comobj::Cfgattr() 
{
	int oldtype;
	float Pref,Qref;
	CCfgShow dlg;
	dlg.tmpcfg=dbm->scf;
	Pref=dbm->scf.Pref;
	Qref=dbm->scf.Qref;
	oldtype=dbm->scf.ctrtype;
	if(dlg.DoModal()==IDOK)
	{
		if(memcmp(&dbm->scf,&dlg.tmpcfg,sizeof(SHOWCFG))==0) return;
		dbm->scf=dlg.tmpcfg;
		dbm->scf.ctrtype=oldtype;
		dbm->SaveShowSet();
		swin->SetDgxParam();
		if(Pref!=dbm->scf.Pref||Qref!=dbm->scf.Qref) swin->FlwZoomChange();
		swin->ChangeDgxcfg();
		swin->CreateAllrgn();
		if(dbm->scf.showdgx==0) cwin->ShowWindow(SW_HIDE);
		else cwin->ReDraw();
	}
}

//上一个界面
void comobj::Lasthmi() 
{
	char fnm[256];
	HISHMI hmi,hmi1;
	if(dbm->GetALastHmi(hmi)==false) return;
	swin->GetCurHmi(hmi1);
	dbm->AddRtnHmi(hmi1);
	dbm->n1bz=-1;
	SetToLocalFile(hmi.filename,fnm);
	if(dbm->CheckFileIndex(fnm,hmi.picno))
	{
		swin->FileOpen(fnm,hmi.picno,&hmi,1);
	}
}

void comobj::Nexthmi() 
{
	char fnm[256];
	HISHMI hmi,hmi1;
	if(dbm->GetARtnHmi(hmi)==false) return;
	swin->GetCurHmi(hmi1);
	dbm->AddOpenHmi(hmi1);
	dbm->n1bz=-1;
	SetToLocalFile(hmi.filename,fnm);
	
	if(dbm->CheckFileIndex(fnm,hmi.picno))
	{
		swin->FileOpen(fnm,hmi.picno,&hmi,1);
		return;
	}
}

void comobj::HisSpdown() 
{
	swin->dbm.hspeed=swin->dbm.hspeed >1 ? swin->dbm.hspeed-1:0;
	hbar->SetSpeed(swin->dbm.hspeed);
}

void comobj::HisSpup() 
{
	swin->dbm.hspeed=swin->dbm.hspeed <59 ? swin->dbm.hspeed+1:0;
	hbar->SetSpeed(swin->dbm.hspeed);
}

void comobj::OnShowdgx() 
{
	dbm->scf.showdgx=dbm->scf.showdgx==1 ? 0:1;
	if(dbm->scf.showdgx==1)
	{
		dbm->curopzt=0;
		switch(dbm->scf.ctrtype)
		 {
		 case 0:
			 swin->SetCurFunction(FUN_DGXBUS);
			 break;
		 case 1:
			 swin->SetCurFunction(FUN_DGXBUSL);
			 break;
		 case 2:
			 swin->SetCurFunction(FUN_DGXBUSH);
			 break;
		 case 3:
			 swin->SetCurFunction(FUN_DGXLINE);
			 break;
		 case 4:
			 swin->SetCurFunction(FUN_DGXTRAS);
			 break;
		 default :
			 swin->SetCurFunction(FUN_BASE);
			 break;

		 }
	}
	else
	{
		if(swin->m_CurFun>FUN_BASE && swin->m_CurFun<FUN_DMFLOW)
			swin->SetCurFunction(FUN_BASE);
	}

	swin->ChangeDgxcfg();
	dbm->SaveShowSet();
	if(dbm->scf.showdgx==1)	cwin->ShowWindow(SW_SHOW);
	else cwin->ShowWindow(SW_HIDE);
}

void comobj::Showdgx() 
{
	dbm->scf.showdgx=1;
	dbm->curopzt=0;
	swin->ChangeDgxcfg();
	dbm->SaveShowSet();
	if(dbm->scf.showdgx==1)	cwin->ShowWindow(SW_SHOW);
	else cwin->ShowWindow(SW_HIDE);
}

//重新显示工具棒
void comobj::ReShowToolBar()
{
	CRect rect;	
	if(dbm->curopzt==1) dmbar->ShowWindow(SW_SHOW);
	else dmbar->ShowWindow(SW_HIDE);
	if(dbm->curopzt==2) sebar->ShowWindow(SW_SHOW);
	else sebar->ShowWindow(SW_HIDE);
	if(dbm->curopzt==4) fwin->m_hisbar.ShowWindow(SW_SHOW);
	else fwin->m_hisbar.ShowWindow(SW_HIDE);
	if(dbm->curopzt==5) fwin->m_soebar.ShowWindow(SW_SHOW);
	else fwin->m_soebar.ShowWindow(SW_HIDE);
	if(dbm->curopzt==6) fwin->m_mdlbar.ShowWindow(SW_SHOW);
	else fwin->m_mdlbar.ShowWindow(SW_HIDE);
	if(mwin->GetCurpageType()==0) fwin->m_funbar.ShowWindow(SW_SHOW);
	else fwin->m_funbar.ShowWindow(SW_HIDE);
	fwin->m_wndToolBar.GetWindowRect(&rect);
	rect.OffsetRect(1,0);
	fwin->DockControlBar(&fwin->m_funbar,(UINT)0,&rect);
	fwin->DockControlBar(&fwin->m_hisbar,(UINT)0,&rect);
	fwin->DockControlBar(&fwin->m_dmbar,(UINT)0,&rect);
	fwin->DockControlBar(&fwin->m_senbar,(UINT)0,&rect);
	fwin->DockControlBar(&fwin->m_soebar,(UINT)0,&rect);
	fwin->DockControlBar(&fwin->m_mdlbar,(UINT)0,&rect);
	fwin->RecalcLayout();
}

void comobj::SetNewCursor(int newcur)
{
	swin->cursor=newcur;
	swin->rcursor=newcur;
}

void comobj::FunctChange()
{
	swin->Set3DEnv();		//设置3D环境
	swin->Order3dPos();
	swin->CreateAllrgn();
	swin->EndShow();
	swin->cursor=0;
	nwin->PageChange();
	ReShowToolBar();
}

//N-1数据读取
void comobj::ReadN1GZ(int n1type)
{
	int i,j,num;
	float v1,v2;
	N1Data data[300],td;
	if(!swin->rrd.ReadN1Data(n1type,num,data,300)) return;
	//按绝对值大小排序
	for(i=0;i<num-1;i++)
	{
		v1=data[i].val;
		v1=v1<0 ? -v1:v1;
		for(j=i+1;j<num;j++)
		{
			v2=data[j].val;
			v2=v2<0 ? -v2:v2;
			if(v1>v2)
			{
				td=data[i];
				data[i]=data[j];
				data[j]=td;
			}
		}
	}
	//设置数据
	swin->SetN1Data(n1type,data,num);
}

//短路电流数据读取
void comobj::ReadShortCC()
{
	int i,num;
	DLDL  sc[256];	//最大缓冲256个
	//读取数据
	num=swin->rrd.ReadShtCC(sc,256);
	if(num==0) return;
	//设置数据
	for(i=0;i<num;i++)
	{
		swin->SetSwtSccData(sc[i]);
		swin->SetLineSccData(sc[i]);
	}
}


void comobj::N1FunSet(int n1type)
{
	switch(n1type)
	{
	case 0:
		swin->SetCurFunction(FUN_N1BUS);
		break;
	case 1:
		swin->SetCurFunction(FUN_N1BRA);
		break;
	case 2:
		swin->SetCurFunction(FUN_N1ALL);
		break;
	case 3:
		swin->SetCurFunction(FUN_N1BUSF);
		break;
	case 4:
		swin->SetCurFunction(FUN_N1BRAF);
		break;
	case 5:
		swin->SetCurFunction(FUN_N1ALLF);
		break;
	}
}

//N-1操作

void comobj::N_1Operator(int rev,int n1type) 
{
	ResetFunct(0,0);
	dbm->scf.showrev=rev; 
	dbm->n1bz=n1type;
	dbm->lookdown=1;
	N1FunSet(n1type);
	swin->CollectN1Device(); //收集设备参数
	//读取n-1结果
	ReadN1GZ(n1type);
	FunctChange();
}
//短路电流展示
void comobj::DlDlperator() 
{
	ResetFunct(0,0);
	dbm->scf.showrev=9; 
	dbm->lookdown=1;
	dbm->scf.showdgx=0;
	swin->CleaseDlFlash();
	//读取短路电流计算结果
	ReadShortCC();
	FunctChange();
}


//手动短路电流计算
void comobj::ManuDlperator() 
{
	/*ResetFunct();
	dbm->scf.showrev=9; 
	dbm->curopzt=6;
	dbm->lookdown=0;
	dbm->scf.showdgx=0;
	swin->CleaseDlFlash();
	//读取短路电流计算结果
	//ReadShortCC();
	FunctChange();*/
}

//复位功能,置为平面
void comobj::ResetFunct(int resetzoom,int issetfun) 
{
	CloseHisPrc(); //如果处于历史态就关闭
	swin->CloseLowfWin();
	swin->SetCurDbf(0);
	dbm->curopzt=0;
	swin->SetStatusBarMsg();
	if(resetzoom==1)
	{
		swin->SetFirstPosition();
		swin->ComputZCenter();
	}
	dbm->scf.showrev=0;
	dbm->n1bz=-1;
	dbm->scf.lmd=0;
	dbm->lookdown=0;
	dbm->scf.showdgx=0;
	cwin->ShowWindow(SW_HIDE);
	if(issetfun==1) swin->SetCurFunction(FUN_BASE);
	FunctChange();
}

//关闭历史
void comobj::CloseHisPrc()
{
	if(swin->dbm.hdbok==TRUE)
	{
		//关闭历史连接
		CloseProvider();
		swin->dbm.hisplay=0;
		dbm->dbzt=0;			//0=正常 1=浏览历史
		dbm->curopzt=0;
		swin->rrd.SetCurDbf(0);
		swin->SetStatusBarMsg();
		ReShowToolBar();
		swin->dbm.hdbok=FALSE;
	}
}


//低频震荡监视
void comobj::ToLowf() 
{
	char nm[256],fnm[256];
	ResetFunct(0,0);
	dbm->curopzt=3;
	//打开低频震荡监视画面
	strcpy(nm,Lowfpage.filename);
	SetToLocalFile(nm,fnm);
	if(dbm->CheckFileIndex(fnm,Lowfpage.index))
	{
		swin->FreeMem();
		dbm->OpenPwFile(fnm,mainpage.index);
		swin->InitMoveObj(NULL,0);
	}
	swin->SetCurFunction(FUN_LOWF);
	//////////////////////////////
	swin->InitLowFData();
	swin->CreateAllrgn();
	swin->EndShow();
	ReShowToolBar();
	swin->cursor=0;
}
//启动历史
void comobj::Starthis() 
{
	SetHisDlg dlg;
	dlg.dbm=dbm;
	if(dlg.DoModal()!=IDOK) return;
	swin->ResetAllData();
	swin->dbm.curtm=0;
	swin->SetCurDbf(1);
	dbm->curopzt=4;
	swin->EndShow();
	swin->SetStatusBarMsg();
	ReShowToolBar();
	swin->SetCurHisDTime();
	hbar->SetSpeed(swin->dbm.hspeed);
}

//启动SOE
void comobj::StartSoe() 
{
	swin->ResetAllData(1);
	swin->SetCurDbf(0);
	dbm->curopzt=5;
	dbm->scf.showrev=8;
	dbm->scf.showdgx=0;
	swin->SetCurFunction(FUN_SOE);
	SuspendThread(swin->hThread_rd);
	swin->EndShow();
	swin->SetStatusBarMsg();
	ReShowToolBar();
}

//进入断面潮流环境
void comobj::Dmflow() 
{
	swin->CloseLowfWin();
	dbm->curopzt=dbm->curopzt==1 ? 0:1;
	if(dbm->curopzt==1) swin->SetCurFunction(FUN_DMFLOW);
	else swin->SetCurFunction(swin->m_PreFun);
	dbm->scf.showrev=0;
	dbm->n1bz=-1;
	swin->CursorChange(0);
	dbm->lookdown=0;
	dbm->scf.showdgx=0;
	dbm->curang=0;
	swin->Set3DEnv();
	if(dbm->scf.showdgx==1)	swin->sct.DrawDgxinMem(swin->msr,dbm->curzoom,swin->dx,swin->dy);
	swin->EndShow();
	swin->CreateAllrgn();
	ReShowToolBar();
}

void comobj::Btnreturn() 
{
	switch(swin->m_PreFun)
	{
	case FUN_DGXBUS://母线等高线
		swin->SetCurFunction(FUN_DGXBUS);
		dbm->scf.ctrtype=0;
		mwin->ToolBarDgxSel();
		break;
	case FUN_DGXBUSL://母线等高线低
		swin->SetCurFunction(FUN_DGXBUSL);
		dbm->scf.ctrtype=1;
		mwin->ToolBarDgxSel();
		break;
	case FUN_DGXBUSH://母线等高线高
		swin->SetCurFunction(FUN_DGXBUSH);
		dbm->scf.ctrtype=2;
		mwin->ToolBarDgxSel();
		break;
	case FUN_DGXLINE://输电线等高线
		swin->SetCurFunction(FUN_DGXLINE);
		dbm->scf.ctrtype=5;
		mwin->ToolBarDgxSel();
		break;
	case FUN_DGXTRAS://变压器等高线
		swin->SetCurFunction(FUN_DGXTRAS);
		dbm->scf.ctrtype=4;
		mwin->ToolBarDgxSel();
		break;
	case FUN_DGXLOAD://负荷等高线
		
		break;
	case FUN_DMFLOW://断面潮流
		Dmflow();
		break;
	case FUN_SENOPR://灵敏度
		Senopr();
		break;
	case FUN_REVGEN://发电机备用
		Genrev();
		break;
	case FUN_REVGENQ://发电机无功备用
		Genrevq();
		break;
	case FUN_REVTRANS://变压器备用
		Tranrev();
		break;
	case FUN_TRANSTEMP://变压器温度
		Byqwd();
		break;
	case FUN_N1BUS://N1母线
		N_1Operator(5,0);
		break;
	case FUN_N1BRA://N1支路
		N_1Operator(6,1);
		break;
	case FUN_N1ALL://N1全部
		N_1Operator(7,2);
		break;
	case FUN_N1BUSF://预测N1母线
		N_1Operator(5,3);
		break;
	case FUN_N1BRAF://预测N1支路
		N_1Operator(6,4);
		break;
	case FUN_N1ALLF://预测N1全部
		N_1Operator(7,4);
		break;
	case FUN_N1EFT://N1影响
		N12eft3d();
		break;
	case FUN_ZONE://分区信息
		Zonebar();
		break;
	case FUN_SPIE://系统
		Syspiebar();
		break;
	default:
		ResetFunct(1,1);
		break;
	}
}

void comobj::N12eft3d() 
{
	swin->CloseLowfWin();
	swin->dmsum=0;
	dbm->scf.ctrtype=7;
	swin->SetCurFunction(FUN_N1EFT);
	dbm->scf.showrev=12; //N-1重载、过载设备
	dbm->scf.lmd=0;
	dbm->lookdown=1;
	//读取n-1影响结果
	swin->ReadN1EFT();
	FunctChange();
}



void comobj::SaveShowTrans()
{
	char fnm[288];
	strcpy(fnm,startpath);
	strcat(fnm,"\\showtrans.cfg");

	CString strTmp;
	CStdioFile f1;
	if( !f1.Open( fnm, CFile::modeCreate|CFile::modeWrite | CFile::typeText ))
		return;
	for(int i=0;i<shownum;i++)
	{
		strTmp.Format("%d %s\n",showtrans[i].devtype,showtrans[i].devname);
		f1.WriteString(strTmp);
	}
	f1.Close();
}


void comobj::Zonebar() 
{
	swin->CloseLowfWin();
	dbm->curopzt=0;
	swin->dmsum=0;
	dbm->scf.showrev=10;
	dbm->scf.lmd=0;
	dbm->lookdown=1;
	dbm->scf.showdgx=0;
	swin->SetCurFunction(FUN_ZONE);
	cwin->ShowWindow(SW_HIDE);
	swin->ToMyZm(1.15);
	FunctChange();
}

void comobj::Syspiebar() 
{
	swin->CloseLowfWin();
	dbm->curopzt=0;
	swin->dmsum=0;
	dbm->scf.showrev=11;
	dbm->scf.lmd=0;
	dbm->lookdown=1;
	dbm->scf.showdgx=0;
	swin->SetCurFunction(FUN_SPIE);
	cwin->ShowWindow(SW_HIDE);
	swin->ToMyZm(1.15);
	FunctChange();

	/*dbm->n1type=20;
	dbm->scf.lowf=0;
	dbm->dmflow=0;
	swin.dmsum=0;
	senopr=0;
	SetCurFunction(FUN_SPIE);
	dbm->scf.showrev=10; //区域
	dbm->scf.lmd=0;
	dbm->lookdown=1;
	swin.dwin.ShowWindow(SW_HIDE);
	FunctChange();*/
}