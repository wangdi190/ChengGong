// gdata.cpp: implementation of the gdata class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "gdata.h"
#include "DObj.h"
#include "comobj.h"
#include "middll.h"
#include "filev30.h"
#include "bclass.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern comobj  cobj;	//公共对象
extern double vl[];
extern DWORD  cr[];
extern char   *ut[];
extern int    qz[];
extern int    fl[];
extern DWORD scr[];




extern CPoint *mpt; //临时用的一个点缓冲区，最大1024个点
extern DPOINT *npt;

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

gdata::gdata()
{
    int i;
	InitParam();
	for(i=0;i<32;i++){
		strcpy(hishmi[i].filename,"");
		hishmi[i].picno=0;
	}
	memset(&scf,0,sizeof(SHOWCFG));  

	curopzt=0;		//操作初始状态

	curhmi=0;
	currtn=0;
	lookdown=0;
	dbzt=0;
	apdenable=0;

	hsum=0;			//历史断面数
	hspeed=5;		//历史回放速度
	hdbok=FALSE;	//
	curtm=0;		//当前时段
	hisplay=0;
	n1bz=-1;
	tylayer.objnum=0;
	filename[0]=0;
	soe=NULL;	//SOE数据
	soesum=0;	//SOE个数

	m_PlateNum=0;
}

gdata::~gdata()
{
	if(hdbok==TRUE) CloseProvider();
	hdbok=FALSE;
	FreeMem();
}



//初始化参数
void gdata::InitParam()
{
	int j;
	curpage=0;
	spicsum=0;
	mpicsum=0;
	egpsum=0;
	curfile[0]=0;
	clayer=&page.layer[0];
	/////////////////////页面初始化
	page.index=(BYTE)0;
	zh=768;
	zw=1024;
	page.head.BgColor=0;
	page.head.height=768;
	page.head.width=1024;
	page.head.imgID=-1;
	page.head.showbyrt=0;
	strcpy(page.head.Name,"");
	page.laysum=1;
	page.curlay=0;
	for(j=0;j<MAXLAYER;j++){
		sprintf(page.layer[j].name,"图层%d",j);
		page.layer[j].select=1;
		page.layer[j].show=1;
		page.layer[j].obj=NULL;
		page.layer[j].objnum=0;
	}
	/////////////////////////////////////////////
	memset(&spic,0,sizeof(N_SMALLPIC)*MAXSPIC);
	memset(&mpic,0,sizeof(N_MemPic)*100);
	memset(&egp,0,sizeof(N_ELEGRP)*MAXEGRP);
	cmsum=0; //当前控件菜单总数
}


//释放内存
void gdata::FreeMem()
{
	int i,j,k;
	//第一步释放公共部分内存
	//删除组合图元
	for(i=0;i<egpsum;i++){
		FreeEgp(i,0);
		FreeEgp(i,1);
	};
	//清除内存图形
	for(i=0;i<mpicsum;i++){
	  if(mpic[i].dc.m_hDC!=NULL)   DeleteDC(mpic[i].dc.m_hDC);
	  if(mpic[i].dc.hbitmap!=NULL) DeleteObject(mpic[i].dc.hbitmap);
	  mpic[i].dc.m_hDC=NULL;
	  mpic[i].dc.hbitmap=NULL;
	};
	for(i=0;i<spicsum;i++){
		spic[i].img.FreeMem();
	}
    spicsum=0;			//图片总数
    mpicsum=0;			//图片数,最大=100
    egpsum=0;			//当前的组合图元数
	//第二步:释放所有页面
	//删除对象
	for(j=0;j<page.laysum;j++)
	{
	  if(page.layer[j].objnum>0)
	  {
		    for(k=0;k<page.layer[j].objnum;k++)
			{
			 page.layer[j].obj[k].FreeMem();	
			};
			free(page.layer[j].obj);
		    page.layer[j].obj=NULL;
	  }
		 page.layer[j].objnum=0;
	};
	//释放投影层
	FreeMemTyLayer();
	filename[0]=0;
	//释放SOE
	if(soe!=NULL) delete soe;
	soe=NULL;
	soesum=0;

	//释放挂牌信息
	for(i=0; i<m_PlateNum; i++)
	{
		if(m_PlateInfo[i].m_rgn!=NULL) DeleteObject(m_PlateInfo[i].m_rgn);
		memset(&m_PlateInfo[i], 0, sizeof(PlateInfo));
	}
	m_PlateNum=0;
}

//释放投影层
void gdata::FreeMemTyLayer()
{
	int i;
	//删除对象
	for(i=0;i<tylayer.objnum;i++)
	{
		tylayer.obj[i].FreeMem();	
	};
	if(tylayer.objnum>0) free(tylayer.obj);
	tylayer.obj=NULL;
	tylayer.objnum=0;
}

//释放组合图元内存
void gdata::FreeEgp(int num, int index)
{
	DObj *bs;
	int i,j;
	switch(index){
	case 0:
		bs=egp[num].bs1;
		j=egp[num].bsum1;
		egp[num].bs1=NULL;
		egp[num].bsum1=0;;
		break;
	case 1:
		bs=egp[num].bs2;
		j=egp[num].bsum2;
		egp[num].bs2=NULL;
		egp[num].bsum2=0;
		break;
	default:return;
	};
	if(bs==NULL) return;
	for(i=0;i<j;i++){
		bs[i].FreeMem();
	};
	free(bs);
}

//返回一个内存图片记录号
int gdata::GetMPICRecno(int id)
{
	int i;
	for(i=0;i<mpicsum;i++){
	  if(mpic[i].id==id) return i;
	};
	return -1;
}

//返回一个小图记录号
int gdata::GetPICRecno(int id)
{
	int i;
	for(i=0;i<spicsum;i++){
	  if(spic[i].id==id) return i;
	};
	return -1;
}

//返回图元记录号
int gdata::GetEGPRecNo(int id)
{
	int i;
	for(i=0;i<egpsum;i++)
	{
	  if(egp[i].id==id) return i;
	}
	return -1;
}

//打开pw格式文件
//输入参数:	fname:文件名
//			pageno:页面号
bool gdata::OpenPwFile(char *fname,int pageno)
{
	N_APDINFO atmp;
	FILE *fp;
	char *buf1;
	int i,m,n;
	N_PWFHEAD *ph,head;
	fp=fopen(fname,"r+b");
	if(fp==NULL) return false;
	strcpy(filename,fname);
	//第一步:读入文件头:
	fread(&head,sizeof(N_PWFHEAD),1,fp);
	if(head.Version>3203)
	{
		fclose(fp);
		return false;
	};
	//察看pageno是否在其中，否则返回错误
	if(pageno<0||pageno>=head.pagesum) return false;
	////正式读取文件
	FreeMem(); //释放原有的图形数据
	InitParam();
	n=head.pagesum;
	if(n>MAXPAGE){
	 fclose(fp);
	 return false;
	};
	m=n*sizeof(N_OBJSAVE)+sizeof(N_PWFHEAD);
	buf1=new char[m+100];
	ph=(N_PWFHEAD*)buf1;
	fseek(fp,0,SEEK_SET);
	fread(buf1,m,1,fp);
	//第一步:读入小图标
	if(ph->spicsum>0)
	{
		fseek(fp,(long)ph->spic.offset,SEEK_SET);
		LoadSPic(fp);
	};
	//第二步:读入组合图元
	if(ph->egpsum>0)
	{
		fseek(fp,(long)ph->epic.offset,SEEK_SET);
		LoadEGP(fp,head.Version);
	};
	
	//第三步:读入内存图元
	if(ph->mpicsum>0)
	{
		fseek(fp,(long)ph->mpic.offset,SEEK_SET);
		LoadMemPic(fp);
	};

	//第四步：读入附加信息
	apdenable=0;
	if(ph->apdsum>0)
	{
	 fseek(fp,(long)ph->apdinfo.offset,SEEK_SET);
	 for(i=0;i<ph->apdsum;i++)
	 {	
		 if(feof(fp)) break;
	     fread(&atmp,sizeof(N_APDINFO),1,fp);
		 if(atmp.pageno==pageno)
		 {
			 apd=atmp;
			 apdenable=1;
			 break;
		 }
	 }
	}
	//第五步:读入页面图形及参数
	fseek(fp,(long)ph->page[pageno].offset,SEEK_SET);
	
	LoadPage(fp,head.Version);

	fclose(fp);
	delete buf1;
	strcpy(curfile,fname);
	curpage=pageno;
	clayer=&page.layer[0];
	selbz=0;
	return true;
}


//打开历史文件中的界面文件
//输入参数:	hisfile:文件名
//			hmifile:界面名字			
//			pageno:页面号
bool gdata::OpenHisPwFile(char *hisfile,char *hmifile,int pageno)
{
	HISHEAD   hd;
	FILEINFO  fi;
	FILE *fp;
	char *buf1;
	int i,m,n,okbz;
	N_PWFHEAD *ph,head;
	fp=fopen(hisfile,"r+b");
	if(fp==NULL) return false;
	//读入历史文件头
	fread(&hd,sizeof(HISHEAD),1,fp);
	okbz=0;
	for(i=0;i<hd.fnum;i++)
	{
		fread(&fi,sizeof(FILEINFO),1,fp);
		if(strcmp(fi.filename,hmifile)==0)
		{
			okbz=1;
			break;
		};
	}
	if(okbz==0)
	{
		fclose(fp);
		return false;
	}
	//第一步:读入文件头:
	fseek(fp,fi.offset,SEEK_SET);
	fread(&head,sizeof(N_PWFHEAD),1,fp);
	if(head.Version>3203)//!=3200&&head.Version!=3201)
	{
		fclose(fp);
		return false;
	};
	//察看pageno是否在其中，否则返回错误
	if(pageno<0||pageno>=head.pagesum) return false;
	////正式读取文件
	FreeMem(); //释放原有的图形数据
	InitParam();
	n=head.pagesum;
	if(n>MAXPAGE){
	 fclose(fp);
	 return false;
	};
	m=n*sizeof(N_OBJSAVE)+sizeof(N_PWFHEAD);
	buf1=new char[m+100];
	ph=(N_PWFHEAD*)buf1;
	fseek(fp,fi.offset,SEEK_SET);
	fread(buf1,m,1,fp);
	//第一步:读入小图标
	if(ph->spicsum>0){
	 fseek(fp,(long)ph->spic.offset+fi.offset,SEEK_SET);
	 LoadSPic(fp);
	};
	//第二步:读入组合图元
	if(ph->egpsum>0){
	 fseek(fp,(long)ph->epic.offset+fi.offset,SEEK_SET);
	 LoadEGP(fp,head.Version);
	};
	//第三步:读入内存图元
	if(ph->mpicsum>0){
	 fseek(fp,(long)ph->mpic.offset+fi.offset,SEEK_SET);
	 LoadMemPic(fp);
	};
	//第四步:读入页面图形及参数
	fseek(fp,(long)ph->page[pageno].offset+fi.offset,SEEK_SET);
	LoadPage(fp,head.Version);
	fclose(fp);
	delete buf1;
	clayer=&page.layer[0];
	selbz=0;
	return true;
}

//从界面文件中读入小图标
void gdata::LoadSPic(FILE *fp)
{
	int i,n;
	DWORD *dw;
	uncmpres upr;
	N_PHEAD ph;
	N_PDATA pd;
	char *btmp;
	char *dib;
	fread(&ph,sizeof(N_PHEAD),1,fp);
	if(ph.flag!=0xf9876761||ph.version>0x100)  return;
	n=0;
	for(i=0;i<ph.picsum;i++){
	  fread(&pd,sizeof(N_PDATA),1,fp);
	  if(pd.start!=0x10891111) break;
	  btmp=new char[pd.psize+100];
	  dib=new char[pd.size+100];
	  fread(btmp,pd.psize,1,fp);
	  dw=(DWORD*)btmp;
	  if(dw[0]==pd.size){//字节完全正确
		upr.initdata();
		upr.DDeCode(btmp+4,dib,pd.psize,dw[0]); //解压
		spic[i].img.Create(dib);
		if(pd.tranflag==1&&pd.bits<=8) spic[i].img.CreateRGN(pd.tranindex); 
		spic[i].id=pd.id;
		spic[i].tranmode=pd.tranmode;
		spic[i].trancolor=pd.trancolor;
		spic[i].inuse=pd.inuse;
	  };
	  delete btmp;	
	  delete dib;
	  n++;
	  if(n>=MAXSPIC) break;
	};
	spicsum=n;
}

//读入组合图元
void gdata::LoadEGP(FILE *fp,WORD ver)
{
	FileV30  fv3;
	N_BASATTR btr;		//基本属性
	char  buf[MAXSIZE]; //最大缓冲区10K
	DWORD *dw;
	int i,j,k,m,n,size,bsize;
	char *pbuf;
	char *rbuf;
	char *lp;
	uncmpres upr;
	N_EGPHEAD head;
	N_EGPDATA *eda;
	fread(&head,sizeof(N_EGPHEAD),1,fp);
	if(head.flag!=0x20010215||head.picsum==0||head.psize<=0||
		head.version!=0x100||head.size<=0){
	  fclose(fp);
	  return;  //数据有问题，退出
	};
	fv3.dbm=this;
	size=head.psize;
	pbuf=new char[size+100];
	rbuf=new char[head.size+100];
	fread(pbuf,size,1,fp);
	dw=(DWORD*)pbuf;
	if(dw[0]==head.size){//字节完全正确
		upr.initdata();
		upr.DDeCode(pbuf+4,rbuf,size,dw[0]); //解压
		eda=(N_EGPDATA *)rbuf;
		lp=rbuf+head.picsum*sizeof(N_EGPDATA);
		for(i=0;i<head.picsum;i++){
			if(eda[i].start!=0x10891112) break;
			if(egpsum>=MAXEGRP) break;
			if(!AddAEmptyEGP(eda[i].sav.type)) break;
			n=egpsum-1;
			egp[n].type=eda[i].sav.type;
			egp[n].subtype=eda[i].sav.subtype;
			m=eda[i].sav.sitesum;
			if(egp[n].type==0){ //仪表
				egp[n].sitesum=m;
				for(k=0;k<8;k++) egp[n].index[k]=eda[i].sav.index[k];
			}else{	    		//非仪表
				m=m>3 ? 0:m;
				egp[n].sitesum=m;
				for(k=0;k<m;k++) egp[n].srt[k]=eda[i].sav.srt[k];
			}
			egp[n].rt1=eda[i].sav.rt1;
			egp[n].rt2=eda[i].sav.rt2;
			egp[n].id=eda[i].sav.id;
			//egp[n].inuse=eda[i].sav.inuse;
			//strcpy(egp[n].name,eda[i].sav.name);
			for(j=0;j<eda[i].sav.bsum1;j++){
				memset(buf,0,MAXSIZE);
				switch(ver)
				{
				case 3200: //V2版本
					bsize=fv3.GetBsFromV2(lp,btr,buf);
					break;
				case 3201: //V3版本
					bsize=fv3.GetBsFromV3(lp,btr,buf);
					break;
				case 3202: //V4版本
					bsize=fv3.GetBsFromV4(lp,btr,buf);
					break;
				case 3203: //V5版本
					bsize=fv3.GetBsFromV5(lp,btr,buf);
					break;
				default: continue;
				}
				if(btr.size==0) continue;
				AddAEGP(n,0,btr,buf);
				lp+=bsize;
			};
			for(j=0;j<eda[i].sav.bsum2;j++)
			{
				memset(buf,0,MAXSIZE);
				switch(ver)
				{
				case 3200: //V2版本
					bsize=fv3.GetBsFromV2(lp,btr,buf);
					break;
				case 3201: //V3版本
					bsize=fv3.GetBsFromV3(lp,btr,buf);
					break;
				case 3202: //V4版本
					bsize=fv3.GetBsFromV4(lp,btr,buf);
					break;
				case 3203: //V5版本
					bsize=fv3.GetBsFromV5(lp,btr,buf);
					break;
				default: continue;
				}
				if(btr.size==0) continue;
				AddAEGP(n,1,btr,buf);
				lp+=bsize;
			};
		};
		}
	delete rbuf;
	delete pbuf;
}

//读入内存图片
void gdata::LoadMemPic(FILE *fp)
{
	int i,n;
	DWORD *dw;
	N_PHEAD  ph;
	N_MPicHD pd;
	char *btmp,*src;
	uncmpres upr;
	fread(&ph,sizeof(N_PHEAD),1,fp);
	if(ph.flag!=0xf9876762||ph.version!=0x100) return;
	n=0;
	for(i=0;i<ph.picsum;i++){
		if(n>=100) break;
		fread(&pd,sizeof(N_MPicHD),1,fp);
		mpic[i].dc.Create(pd.nWidth,pd.nHeight);
		mpic[i].id=pd.id;
		mpic[i].inuse=pd.inuse;
		mpic[i].trancolor=1;
		mpic[i].tranmode=0;
		src=new char[pd.psize+100];
		btmp=new char[pd.size+100];
		fread(src,1,pd.psize,fp);
		dw=(DWORD*)src;
		if(dw[0]==pd.size){ //字节完全正确
			upr.initdata();
			upr.DDeCode(src+4,btmp,pd.psize,dw[0]); //解压
			memcpy(mpic[i].dc.dib,btmp,pd.size);
		};
		delete btmp;
		delete src;
		n++;
		};
	mpicsum=n;
}

//读入各页面数据
bool gdata::LoadPage(FILE *fp,WORD ver)
{
	FileV30  fv3;
	N_BASATTR btr;		//基本属性
	char  buf[MAXSIZE]; //最大缓冲区10K
	int  i,j,m,sz,bsize,osum;
	DWORD *dw;
	char *lp;
	char *src;     //源缓冲区
	char *des;	   //目标缓冲区
	N_SUBPWF head;
	N_LAYERS ly;	//层控制结构
	uncmpres upr;
	fv3.dbm=this;
	fread(&head,sizeof(N_SUBPWF),1,fp);			//读页面控制
	if(head.flag!=0xcccc)		return false;	//错误的头
	if(head.laysum>MAXLAYER)    return false;	//层太多    
	page.head=head;
	for(i=0;i<head.laysum;i++)
	{
		fread(&ly,sizeof(N_LAYERS),1,fp);	//读入层控制
		if(ly.flag!=0xffff) return false;	//读层出错
		strcpy(page.layer[i].name,ly.name);
		clayer=&page.layer[i];			//设定当前层，便于添加对象
		page.curlay=i;
		m=ly.psize;
		sz=ly.size;
		if(ly.objnum>0&&m>0&&sz>0)
		{
		 //申请内存
		 src=new char[m+100];
		 des=new char[sz+100];
		 fread(src,m,1,fp);
		 //解压数据
		 dw=(DWORD*)src;
		 if(dw[0]==ly.size){ //字节完全正确,可以解压
			upr.initdata();
			upr.DDeCode(src+4,des,m,dw[0]); //解压
			lp=des;
			clayer->obj=NULL;
			clayer->objnum=0;
			osum=ly.objnum;
			for(j=0;j<osum;j++){
				memset(buf,0,MAXSIZE);
				switch(ver)
				{
				case 3200: //V2版本
					bsize=fv3.GetBsFromV2(lp,btr,buf);
					break;
				case 3201: //V3版本
					bsize=fv3.GetBsFromV3(lp,btr,buf);
					break;
				case 3202: //V4版本
					bsize=fv3.GetBsFromV4(lp,btr,buf);
					break;
				case 3203: //V5版本
					bsize=fv3.GetBsFromV5(lp,btr,buf);
					break;
				default: continue;
				}
				AddCurLayerAObject(btr,buf);
				lp+=bsize;
				if((DWORD)(lp-des)>ly.size)	break;
			}
		 }
		 delete src;
		 delete des;
		};
		CreatePctpie();
	}
	page.laysum=head.laysum;
	return true;
}

//添加一个空的组合图元
bool gdata::AddAEmptyEGP(int type)
{
	if(egpsum>=MAXEGRP){
	  MessageBox(0,"组合图元已满！","错误",MB_OK);
	  return false;
	};
	memset(&egp[egpsum],0,sizeof(N_ELEGRP));
	egp[egpsum].type=type;
	egpsum++;
	return true;
}

void gdata::AddAEGP(int num, int index, N_BASATTR &attr, void *obuf)
{
	int n;
	if(num>=egpsum) return;
	switch(index)
	{
	case 0:
		n=egp[num].bsum1;
		if(n==0)
		{
			egp[num].bs1=new DObj;
		};
		if(n>0){
			egp[num].bs1=(DObj*)realloc(egp[num].bs1,sizeof(DObj)*(n+1));
		};
		egp[num].bs1[n].AddObject(attr,obuf);
		egp[num].bs1[n].dbm=this;
		egp[num].bsum1++;
		break;
	case 1:
		n=egp[num].bsum2;
		if(n==0){
			egp[num].bs2=new DObj;
		};
		if(n>0){
			egp[num].bs2=(DObj*)realloc(egp[num].bs2,sizeof(DObj)*(n+1));
		};
		egp[num].bs2[n].AddObject(attr,obuf);
		egp[num].bs2[n].dbm=this;
		egp[num].bsum2++;
		break;
	}
	
}


//放大缩小 mode=0恢复原始尺寸 1=放大 2=缩小
bool gdata::ZoomPage(int mode)
{
	double zr,oldzr;
	double maxzm;
	oldzr=curzoom;
	maxzm=2;
	//先设定最大放大倍数
	switch(page.head.type)
	{
	case 0: maxzm=1;   break;
	case 1: maxzm=3;   break;
	case 2: maxzm=10;  break;
	default:
		return false;
	}
	//计算新的放大倍数
	switch(mode){
	case 0:	zr=1;		    break;
	case 1: 
		if(oldzr>=maxzm) return false;
		zr=oldzr*1.06;  
		break;
	case 2: 
		if(oldzr<0.1) return false;
		zr=oldzr/1.06;
		break;
	default:
		return false;
	};
	curzoom=zr;
	if(oldzr!=curzoom){
		zw=(int)(page.head.width*curzoom);
		zh=(int)(page.head.height*curzoom);
		return true;
	};
	return false;
}


//确认文件名和索引是否合法
bool gdata::CheckFileIndex(char *filenm, int index)
{
	FILE *fp;
	N_PWFHEAD head;
	fp=fopen(filenm,"r+b");
	if(fp==NULL) return false;
	//第一步:读入文件头:
	fread(&head,sizeof(N_PWFHEAD),1,fp);
	fclose(fp);
	if((head.Version>3203)||index<0||index>=head.pagesum) return false;
	return true;
}

//显示背景
void gdata::ShowBkgd(CDIB&mdc,CRect rt)
{
	if(page.head.imgID<0) mdc.FillBG(page.head.BgColor);
	else FillBgImg(mdc.m_hDC,rt,page.head.imgID);
	if(cobj.daoban==1) ShowDaoBan(mdc,rt);
}

//显示盗版字样
void gdata::ShowDaoBan(CDIB&mdc,CRect rt)
{
	int w,h;
	CRect rt1;
	w=rt.Width();
	h=rt.Height();
	rt1=CRect(0,0,w,h);
	GLDDrawText(mdc.m_hDC,&rt1,&cobj.font1,"盗版",0xff,0);
}

//用小图填充背景
void gdata::FillBgImg(HDC hdc,CRect rt,int k)
{
	CRect rt1;
	int i,j,l,x,y,xoff,yoff,nx,ny,imgw,imgh,izw,izh,yx,yy,w,h;
	l=GetPICRecno(k);
	if(l<0) return;
	imgw=spic[l].img.nWidth;
	imgh=spic[l].img.nHeight;
	izw=(int)(imgw*curzoom);
	izh=(int)(imgh*curzoom);
	if(imgw<=0||imgh<=0) return;
	yx=abs(rt.left)%izw;
	yy=abs(rt.top)%izh;

	xoff=rt.left>0 ? yx:izw-yx;
	yoff=rt.top>0  ? yy:izh-yy;
	nx=rt.Width()/izw+1; //X方向显示的个数
	ny=rt.Height()/izh+1;//y方向显示的个数

	w=nx*izw-xoff;
	h=ny*izh-yoff;
	if(w<rt.Width()) nx++;
	if(h<rt.Height()) ny++;
	for(i=0;i<nx;i++)
	{
		x=i*izw-xoff;
		for(j=0;j<ny;j++)
		{
			y=j*izh-yoff;
			StretchBlt(hdc,x,y,izw,izh,spic[l].img.m_hDC,0,0,imgw,imgh,SRCCOPY);
 		}
	}
}

//当鼠标按下时全部显示(非平滑显示)
void gdata::MSDownShow(CDIB &mdc,int dx,int dy,CRect rt)
{
	int i,j,m;
	CRect trt;
	CPoint cpt;
	CRect rt1,rt2;
	int sdx,sdy;
	DObj *bs;
	rt1=rt;
	rt1.OffsetRect(-dx,-dy);
	sdx=dx-rt.left;
	sdy=dy-rt.top;
	for(i=0;i<page.laysum;i++)
	{
		if(page.layer[i].show==0) continue;	
		m=page.layer[i].objnum;
		bs=page.layer[i].obj;
		for(j=0;j<m;j++)
		{
			if(!bs[j].ObjIsInRect(rt1)) continue;
			bs[j].Show(mdc.m_hDC,sdx,sdy);
			TRACE("%d\n", j);
		}
	}
}


//显示静态图形(如线条等)
void gdata::ShowStatic(CDIB &mdc,int dx,int dy,CRect rt)
{
	int i,j,m;
	CRect trt,rt1;
	CPoint cpt;
	int sdx,sdy;
	DObj *bs;
	rt1=rt;
	rt1.OffsetRect(-dx,-dy);
	sdx=dx-rt.left;
	sdy=dy-rt.top;
	for(i=0;i<page.laysum;i++)
	{
		if(page.layer[i].show==0) continue;	
		m=page.layer[i].objnum;
		bs=page.layer[i].obj;
		for(j=0;j<m;j++)
		{
			if(!bs[j].ObjIsInRect(rt1)) continue;
			bs[j].ShowS(mdc,sdx,sdy,0);
		}
	} 
}

//显示静态图形(如线条等)
void gdata::ShowBgDbx(CDIB &mdc,int dx,int dy,CRect rt,int high)
{
	int i,j,m;
	CRect trt,rt1;
	CPoint cpt;
	int sdx,sdy;
	DObj *bs;
	rt1=rt;
	rt1.OffsetRect(-dx,-dy);
	sdx=dx-rt.left;
	sdy=dy-rt.top;
	for(i=0;i<page.laysum;i++)
	{
		if(page.layer[i].show==0) continue;	
		m=page.layer[i].objnum;
		bs=page.layer[i].obj;
		for(j=0;j<m;j++)
		{
			if(bs[j].attr.type!=1) continue;
			if(!bs[j].ObjIsInRect(rt1)) continue;
			bs[j].ShowDbx(mdc,sdx,sdy,high,1);
		}
	} 
}

void gdata::ShowAct(CDIB &mdc,int dx,int dy,CRect rt)
{
	int i,j,m;
	int sdx,sdy;
	CRect rt1;
	rt1=rt;
	rt1.OffsetRect(-dx,-dy);
	DObj *bs;
	sdx=dx-rt.left;
	sdy=dy-rt.top;
	for(i=0;i<page.laysum;i++)
	{	
		if(page.layer[i].show==0) continue;
		m=page.layer[i].objnum;
		bs=page.layer[i].obj;
		for(j=0;j<m;j++){
			if(bs[j].showdyn==1)	bs[j].ShowAct(mdc,sdx,sdy);
		}
	}
}


void gdata::SignPaintObj(HRGN hrgn,int dx,int dy)
{
	int i,j,m;
	DObj *bs;
	OffsetRgn(hrgn,-dx,-dy);
	for(i=0;i<page.laysum;i++)
	{	
		if(page.layer[i].show==0) continue;
		m=page.layer[i].objnum;
		bs=page.layer[i].obj;
		for(j=0;j<m;j++){
			bs[j].showdyn=0;
			switch(bs[j].attr.type)
			{
			case 73: case 74:case 66:case 67: case 75: case 77: case 65: case 83: case 79:
				if(bs[j].ObjIsCutRgn(hrgn))
				{
				   bs[j].showdyn=1;	
				};
				break;
			case 71:case 72: 
				bs[j].showdyn=1;
				break;
			}
		 }
	}
	OffsetRgn(hrgn,dx,dy);
}


void gdata::PrintShow(HDC hdc, BYTE pm, int dx, int dy)
{
	int i,j,n;
	N_layer  *mlay;
	for(i=0;i<page.laysum;i++){
		n=page.layer[i].objnum;
		mlay=&page.layer[i];
		for(j=0;j<n;j++){
			mlay->obj[j].Print(hdc,pm,dx,dy);
		}
	}
}


void gdata::SaveToBmp(HWND hwnd,int width,int height,char *fname)
{
	FILE *fp;
	CDIB mdc;
	int w,h;
	double oldz;
    BITMAPFILEHEADER bfhdr;
	BITMAPINFOHEADER bi;
	fp=fopen(fname,"w+b");
	if(fp==NULL) return;
	//保存放大倍数
	oldz=curzoom;
	curzoom=1;
	w=width;
	h=height;
	mdc.Create(w,h);
	HDC hdc=GetDC(hwnd);
	BitBlt(mdc.m_hDC,0,0,w,h,hdc,0,0,SRCCOPY);
	ReleaseDC(hwnd,hdc);
	//////////////////////////
	bi.biSize=sizeof(BITMAPINFOHEADER);
    bi.biWidth=mdc.nWidth;
    bi.biHeight=mdc.nHeight; 
    bi.biPlanes=1;
    bi.biBitCount=24;
	bi.biCompression=BI_RGB; 
    bi.biXPelsPerMeter=0; 
    bi.biYPelsPerMeter=0; 
    bi.biClrUsed=0; 
    bi.biClrImportant=0; 
	bi.biSizeImage=mdc.nHeight*mdc.sPerline; 
    bfhdr.bfType = ('M' << 8) | 'B';
    bfhdr.bfReserved1 = 0;
    bfhdr.bfReserved2 = 0;
    bfhdr.bfOffBits = sizeof(BITMAPFILEHEADER) +
                       sizeof(BITMAPINFOHEADER);
    bfhdr.bfSize = (long)mdc.nHeight*mdc.sPerline+bfhdr.bfOffBits;
    fwrite((unsigned char*)&bfhdr,sizeof(BITMAPFILEHEADER),1,fp);
	fwrite((unsigned char*)&bi,sizeof(BITMAPINFOHEADER),1,fp);
	fwrite(mdc.dib,mdc.dibsize,1,fp);
	fclose(fp);
	//恢复放大倍数
	curzoom=oldz;
}

void gdata::SaveToJpg(HWND hwnd,int width,int height,char *fname)
{
	JpegFile  jpg;
	char *buf;
	int size,i,j,w,h;
	char *src,*des;
	CDIB mdc;
	SetCursor(LoadCursor(NULL, IDC_WAIT));
	//保存放大倍数
	w=width;
	h=height;
	mdc.Create(w,h);
	HDC hdc=GetDC(hwnd);
	BitBlt(mdc.m_hDC,0,0,w,h,hdc,0,0,SRCCOPY);
	ReleaseDC(hwnd,hdc);
 	size=h*w*3+100;
	buf=new char[size];
	for(i=0;i<h;i++){
		 src=(char*)mdc.dib+(h-i-1)*mdc.sPerline;
		 des=buf+i*w*3;
		 for(j=0;j<w;j++){
			des[j*3]=src[j*3+2];
			des[j*3+1]=src[j*3+1];
			des[j*3+2]=src[j*3];
		 };
		};
		jpg.RGBToJpegFile(fname,(BYTE*)buf,w,h,true,100);
		delete buf;
	SetCursor(LoadCursor(NULL, IDC_ARROW));
}

//保存显示设置
void gdata::SaveShowSet()
{
	FILE *fp;
	char name[256];
	strcpy(name,cobj.startpath);
	strcat(name,"\\showset.cfg");
	scf.ver=0x1001;
	fp=fopen(name,"w+b");
	if(fp!=NULL){
		fwrite(&scf,sizeof(SHOWCFG),1,fp);
		fclose(fp);
	}
}

//装入显示设置
void gdata::LoadShowSet()
{
	FILE *fp;
	char name[256];
	SetScfDefaultvalue();
	strcpy(name,cobj.startpath);
	strcat(name,"\\showset.cfg");
	fp=fopen(name,"r+b");
	if(fp==NULL) return;
	fread(&scf,sizeof(SHOWCFG),1,fp);
	fclose(fp);
	scf.showrev=0;
	n1bz=-1;
	scf.showdgx=0;
	//scf.lowf=0;
}


//添加一个打开的界面文件(界面返回用)
void gdata::AddOpenHmi(HISHMI &newhmi,char mode)
{
	int i;
	if(curhmi<32){
		hishmi[curhmi]=newhmi;
		hishmi[curhmi].mode=mode;
		curhmi++;
	}else{
		for(i=0;i<31;i++){
			hishmi[i]=hishmi[i+1];
		}
		hishmi[31]=newhmi;
		hishmi[31].mode=mode;
		curhmi=32;
	}
}

//添加返前进用界面文件(界面返回用)
void gdata::AddRtnHmi(HISHMI &newhmi)
{
	int i;
	if(currtn<32){
		rtnhmi[currtn]=newhmi;
		currtn++;
	}else{
		for(i=0;i<31;i++){
			rtnhmi[i]=rtnhmi[i+1];
		}
		rtnhmi[31]=newhmi;
		currtn=32;
	}
}

//返回返回的界面
bool gdata::GetARtnHmi(HISHMI &hmi)
{
	if(currtn<1) return false;
	currtn--;
	hmi=rtnhmi[currtn];
	return true;
}

//返回一个上次的界面
bool gdata::GetALastHmi(HISHMI &hmi)
{
	if(curhmi<1) return false;
	curhmi--;
	hmi=hishmi[curhmi];
	return true;
}

void gdata::GetMenuItem(HWND hwnd,HMENU hmenu)
{
	int i,s,count;
	MENUITEMINFO info,info1;
	memset(&info,0,sizeof(MENUITEMINFO));
	memset(&info1,0,sizeof(MENUITEMINFO));
	count=GetMenuItemCount(hmenu);
	for(i=0;i<count;i++){
		info.cbSize=sizeof(MENUITEMINFO);
		info.fMask=MIIM_TYPE|MIIM_ID|MIIM_SUBMENU;
		s=GetMenuItemInfo(hmenu,i,TRUE,&info); 
		if(s!=0){  //读成功
			if(info.wID!=0&&info.hSubMenu!=0){ //读到一个POP菜单
				GetMenuItem(hwnd,info.hSubMenu);
			}
			else if(info.wID!=0){
				if(cmsum<200){
				  ctlmenu[cmsum].hWnd=hwnd;         //对应的窗口
				  ctlmenu[cmsum].oldid=info.wID;		  //最大200个
				  ctlmenu[cmsum].newid=39300+cmsum; //新ID
				  info1.cbSize=sizeof(MENUITEMINFO);
				  info1.fMask=MIIM_ID;
				  info1.wID=ctlmenu[cmsum].newid;
				  SetMenuItemInfo(hmenu,info.wID,FALSE,&info1);
 				  cmsum++;					      //当前应用总数
				}
			}

		}

	}
}

//设置子窗口菜单
void gdata::SetChildMenu(HWND hwnd,HMENU hm)
{
	if(hm==NULL) return;
	popsum++;//弹出菜单个数
	GetMenuItem(hwnd,hm);
}
//返回应发的窗口和ID
bool gdata::GetChildSendMsg(int id_in, int &id_out, HWND &hwnd)
{
	int i;
	for(i=0;i<cmsum;i++){
		if(id_in==ctlmenu[i].newid){
			id_out=ctlmenu[i].oldid;
			hwnd=ctlmenu[i].hWnd;
			return true;
		}
	}
	return false;
}


//统计对象数量
void gdata::TJObjSum(int *objsum)
{
	int i,j,k,m;
	DObj  *bs;
	memset(objsum,0,100*4);
	for(i=0;i<page.laysum;i++){
		bs=(DObj*)page.layer[i].obj;
		m=page.layer[i].objnum;
		for(j=0;j<m;j++){
			k=bs[j].attr.type;
			if(k>84) continue;
			if(k==1) {if(bs[j].attr.ID<2) objsum[0]++;}
			objsum[k]++;
		}
	}
}

//查找一个发电机的组合图元中的园（每个发电机有一个唯一的圆）
bool gdata::FindAGenCircle(int id,CDRect &rt,CDRect zrt)
{
	DObj  *bs,bbs;
	N_CIRCLE *clr;
	CDRect rt1,rt2;
	int i,j,n;
	double xl,yl,w1,w2,h1,h2;
	j=id;
	if(j<0) return false;
	bs=egp[j].bs1;
	n=egp[j].bsum1;
	rt1.SetDRECT(egp[j].rt1);
	if(bs==NULL||n<=0)	return false;
	//计算宽高
	h1=zrt.Height();
	w1=zrt.Width();
	//原来的宽高
	w2=rt1.Width();
	h2=rt1.Height();
	if(w2==0||h2==0) return false;
	rt2.left=0;			rt2.top=0;
	rt2.right=zrt.left;	rt2.bottom=zrt.top;
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	bbs.dbm=this;
	for(i=0;i<n;i++){
		if(bs[i].attr.type==3)
		{
			bbs.AddObject(bs[i].attr,bs[i].buf);
			bbs.MoveObject2(rt2,xl,yl);
			clr=(N_CIRCLE*)bbs.buf;
			rt=CreateNRt(4,clr->pt);
			bbs.FreeMem();
			return true;
		}
	};
	return false;
}


//显示发电储备棒图(俯视)
void gdata::SHowRevBarP(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum)
{
	int i,h1,h2,h3;
	CDRect art,art1;
	CRect crt;
	CPoint cpt;           
	N_ELEGRPA *elg;

  	for(i=0;i<rvsum;i++){
		elg=r_rv[i].elg;
		if(elg->vr.value[2]<=0) continue;
		if(r_rv[i].subtype!=1||elg->genrev==0||elg->vr.value[2]<=scf.gen3dminp) continue; 
		art=CreateDrawNRt(4,elg->pt,curzoom);
		if(!FindAGenCircle(elg->egrpid,art1,art)) continue;	
		art1.GetRECT(crt);
		art1.left--;
		art1.right++;                  
		art1.top--;   
		art1.bottom++;
		h3=(int)(hbas+elg->vr.value[2]*scf.pqzoom); //最大值
		h1=(int)(h3*elg->vr.value[0]/elg->vr.value[2]);    //第一段
		h2=(int)(h3*elg->vr.value[3]/elg->vr.value[2]); //检修
		
		h2=h3-h2; //转换为实际高度
		h1=h1<0 ? 0:h1;
		h2=h2<0 ? 0:h2;                
		h3=h3<0 ? 0:h3;        
		if(h3==0) continue; //最大值为零
		if(h2>h3) h2=h3;                
		if(h1>h2) h1=h2;                              
		mdc.D3DrawBar2(art1,0,(double)h1,scf.syscolor[0],dx-rt.left,dy-rt.top );
		if(h3>h2) 
		{   
			mdc.D3DrawBar2(art1,(double)h1,(double)h2,scf.syscolor[1],dx-rt.left,dy-rt.top,1);
			mdc.D3DrawBar2j(art1,(double)h2,(double)h3,scf.syscolor[2],dx-rt.left,dy-rt.top,1);
		}else mdc.D3DrawBar2(art1,(double)h1,(double)h2,scf.syscolor[1],dx-rt.left,dy-rt.top,1);
		
	}
}   


//显示发电储备棒图(俯视)
void gdata::SHowRevBarPj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum)
{
	int i,h1,h2,h3;  
	CDRect art,art1;
	CRect crt;
	CPoint cpt;           
	N_ELEGRPA *elg;
  	for(i=0;i<rvsum;i++){
		elg=r_rv[i].elg;
		if(elg->vr.value[2]<=0) continue;
		if(r_rv[i].subtype!=1||elg->genrev==0||elg->vr.value[2]<=scf.gen3dminp)	  continue; 
		art=CreateDrawNRt(4,elg->pt,curzoom);
		if(!FindAGenCircle(elg->egrpid,art1,art)) continue;	
		art1.GetRECT(crt);
		art1.left--;
		art1.right++;                  
		art1.top--;   
		art1.bottom++;
		h3=(int)(hbas+elg->vr.value[2]*scf.pqzoom); //最大值
		h1=(int)(h3*elg->vr.value[0]/elg->vr.value[2]);    //第一段
		h2=(int)(h3*elg->vr.value[3]/elg->vr.value[2]); //检修
		h2=h3-h2; //转换为实际高度
		h1=h1<0 ? 0:h1;
		h2=h2<0 ? 0:h2;       
		h3=h3<0 ? 0:h3;        
		if(h3==0) continue; //最大值为零
		if(h2>h3) h2=h3;                
		if(h1>h2) h1=h2;                       
		mdc.D3DrawBar2j(art1,0,(double)h1,scf.syscolor[0],dx-rt.left,dy-rt.top);
		if(h3>h2)
		{
			mdc.D3DrawBar2j(art1,(double)h1,(double)h2,scf.syscolor[1],dx-rt.left,dy-rt.top);
			mdc.D3DrawBar2j(art1,(double)h2,(double)h3,scf.syscolor[2],dx-rt.left,dy-rt.top,1);
		}else mdc.D3DrawBar2j(art1,(double)h1,(double)h2,scf.syscolor[1],dx-rt.left,dy-rt.top,1);
	}
}  
//显示变压器备用棒图(俯视)
void gdata::SHowTranRevBarP(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum)
{
	DWORD c1,c2;
	int i;
	double a,w,h,h1,h2,maxp,p,overt;
	CDRect art,art1; 
	CDPoint cpt;        
	N_ELEGRPA *elg; 
	for(i=0;i<trsum;i++)
	{
		elg=r_tr[i].elg;
		if(elg->subtype==7)
		{
			maxp=elg->vr.value[1];
			p=elg->Ps;//vr.value[2];
			overt=elg->vr.value[3];
		}else{
			maxp=elg->vr.value[3];
			p=elg->Ps;//vr.value[4];
			overt=elg->vr.value[5];
		}
		if(maxp==0) continue;
		art=CreateDrawNRt(4,elg->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		h2=hbas+maxp*scf.tpzoom;
		h1=h2*elg->Ps/maxp;
		h1=h1<0 ? 0:h1;
		h2=h2<0 ? 0:h2;
		h1=h1>h2 ?  h2:h1;
		if(h2==0) continue;
		a=p/maxp;
		if(a<0.8)
		{
			c1=scf.syscolor[6];
			c2=scf.syscolor[7];
		}else{
			c1=scf.syscolor[8];
			c2=scf.syscolor[7];
		}
		mdc.D3DrawBar2(art1,0,h1,c1,dx-rt.left,dy-rt.top);
		mdc.D3DrawBar2(art1,h1,h2,c2,dx-rt.left,dy-rt.top,1);
	}
} 




//显示变压器备用棒图(俯视)
void gdata::SHowTranRevBarPj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum)
{
	DWORD c1,c2;
	int i;
	double w,h,h1,h2,maxp,p,overt;
	CDRect art,art1; 
	CDPoint cpt;        
	N_ELEGRPA *elg; 
	for(i=0;i<trsum;i++)
	{
		elg=r_tr[i].elg;
		if(elg->subtype==7)
		{
			maxp=elg->vr.value[1];
			p=elg->vr.value[2];
			overt=elg->vr.value[3];
		}else{
			maxp=elg->vr.value[3];
			p=elg->vr.value[4];
			overt=elg->vr.value[5];
		}
		if(maxp==0) continue;
		art=CreateDrawNRt(4,elg->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		h2=hbas+maxp*scf.tpzoom;
		h1=h2*elg->Ps/maxp;
		h1=h1<0 ? 0:h1;
		h2=h2<0 ? 0:h2;
		h1=h1>h2 ?  h2:h1;
		if(h2==0) continue;
		if(overt<=0)
		{
			c1=scf.syscolor[6];
			c2=scf.syscolor[7];
		}else{
			c1=scf.syscolor[8];
			c2=scf.syscolor[8];
		}
		mdc.D3DrawBar2j(art1,0,h1,c1,dx-rt.left,dy-rt.top);
		mdc.D3DrawBar2j(art1,h1,h2,c2,dx-rt.left,dy-rt.top,1);
	}
} 


//显示变压器温度棒图(俯视)
void gdata::SHowTranTBar(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum)
{
	int i;
	double w,h,h1,h2,tcur,tmax;
	CDRect art,art1; 
	CDPoint cpt;        
	N_ELEGRPA *elg; 
	for(i=0;i<trsum;i++)
	{
		elg=r_tr[i].elg;
		if(elg->subtype==7)
		{
			tcur=elg->vr.value[4];
			tmax=elg->vr.value[5];
		}else{
			tcur=elg->vr.value[6];
			tmax=elg->vr.value[7];
		}
		if(tcur<=0) continue;
		art=CreateDrawNRt(4,elg->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		h1=tcur*scf.tptzoom;
		h2=tmax*scf.tptzoom;
		h1=h1<0 ? 0:h1;
		h2=h2<0 ? 0:h2;
		h1=h1>h2 ?  h2:h1;
		if(h2==0) continue;
		if(h1<h2)
		{
			mdc.D3DrawBar2(art1,0,h1,scf.syscolor[10],dx-rt.left,dy-rt.top);
			mdc.D3DrawBar2(art1,h1,h2,scf.syscolor[11],dx-rt.left,dy-rt.top,1);
		}else{
			h1=h1*1.2;
			mdc.D3DrawBar2(art1,0,h1,scf.syscolor[12],dx-rt.left,dy-rt.top,1);
		}
	}
} 



//显示变压器温度棒图(俯视)
void gdata::SHowTranTBarj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_tr,int trsum)
{
	int i;
	double w,h,h1,h2,tcur,tmax;
	CDRect art,art1; 
	CDPoint cpt;        
	N_ELEGRPA *elg; 
	for(i=0;i<trsum;i++)
	{
		elg=r_tr[i].elg;
		if(elg->subtype==7)
		{
			tcur=elg->vr.value[4];
			tmax=elg->vr.value[5];
		}else{
			tcur=elg->vr.value[6];
			tmax=elg->vr.value[7];
		}
		if(tcur<=0) continue;
		art=CreateDrawNRt(4,elg->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		h1=tcur*scf.tptzoom;
		h2=tmax*scf.tptzoom;
		h1=h1<0 ? 0:h1;
		h2=h2<0 ? 0:h2;
		h1=h1>h2 ?  h2:h1;
		if(h2==0) continue;
		if(h1<h2)
		{
		mdc.D3DrawBar2j(art1,0,h1,scf.syscolor[10],dx-rt.left,dy-rt.top);
		mdc.D3DrawBar2j(art1,h1,h2,scf.syscolor[11],dx-rt.left,dy-rt.top,1);
		}else{
			h1=h1*1.2;
			mdc.D3DrawBar2j(art1,0,h1,scf.syscolor[12],dx-rt.left,dy-rt.top,1);
		}
	}
} 

//显示发电机及电容器无功储备棒图(俯视)
void gdata::SHowGenBarQ(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum)
{
	int i,h1,h2;
	double w,h;
	CDRect art,art1;
	CDPoint cpt;
	N_ELEGRPA *elg;
	if(scf.showrev!=2) return;
	DWORD crColor;
	for(i=0;i<rvsum;i++){
		elg=r_rv[i].elg;
		switch(elg->subtype){
		case 1: //发电机
			if(elg->vr.value[1]==0) continue;
			art=CreateDrawNRt(4,elg->pt,curzoom);
			if(!FindAGenCircle(elg->egrpid,art1,art)) continue;	
			art1.left--;art1.right++;art1.top--;art1.bottom++;
			//h1=(int)(hbas+elg->vr.value[1]*scf.pqzoom);
			crColor=scf.syscolor[3];
			if(elg->vr.value[1]<0)
				crColor=RGB(255,128,255);
			h1=(int)(elg->vr.value[1]*1.0);
			h1=h1<0 ? -h1:h1;
			if(h1==0) continue;
			mdc.D3DrawBar2(art1,0,(double)h1,crColor,dx-rt.left,dy-rt.top,1);
			break;
		case 4: //电容器
			art=CreateDrawNRt(4,elg->pt,curzoom);
			cpt=art.CenterPoint();
			w=art.Width();
			h=art.Height();
			w=w>h ? h:w;
			w=w/2;
			art1.left=cpt.x-w;
			art1.right=cpt.x+w;
			art1.top=cpt.y-w;
			art1.bottom=cpt.y+w;
			if(elg->vr.value[2]==0) continue;
			//h2=(int)(hbas+elg->vr.value[2]*scf.pqzoom);
			h2=(int)(elg->vr.value[2]*1.0);
			crColor=scf.syscolor[4];
			if(elg->vr.value[2]<0)
				crColor=RGB(255,128,255);
			h1=(int)(h2*elg->vr.value[0]/elg->vr.value[2]);
			h1=h1<0 ? 0:h1;
			h2=h2<0 ? 0:h2;
			h1=h1>h2 ?  h2:h1;
			if(h2==0) continue;
			mdc.D3DrawBar2(art1,0,(double)h1,crColor,dx-rt.left,dy-rt.top,0);
			mdc.D3DrawBar2(art1,(double)h1,(double)h2,scf.syscolor[5],dx-rt.left,dy-rt.top,1);
			break;
		}
	}
}

/*发电机出力棒
发电机备用棒
发电机检修棒
发电机无功棒
电容器无功棒
电容器容量棒
变压器负载棒
变压器容量棒
变压器越限棒
灵敏度棒图
变压器温度棒图
变压器极限温度棒图
变压器温度越限颜色*/
//显示发电机及电容器无功储备棒图(俯视)
void gdata::SHowGenBarQj(CDIB&mdc,CRect rt,int dx,int dy,RREV *r_rv,int rvsum)
{
	int i,h1,h2;
	double w,h;
	CDRect art,art1;
	CDPoint cpt;
	N_ELEGRPA *elg;
	if(scf.showrev!=2) return;
	DWORD crColor;
	for(i=0;i<rvsum;i++){
		elg=r_rv[i].elg;
		switch(elg->subtype){
		case 1: //发电机
			if(elg->vr.value[1]==0) continue;
			art=CreateDrawNRt(4,elg->pt,curzoom);
			if(!FindAGenCircle(elg->egrpid,art1,art)) continue;	
			art1.left--;art1.right++;art1.top--;art1.bottom++;
			h1=(int)(elg->vr.value[1]*1.0);
			//h1=(int)(hbas+elg->vr.value[1]*scf.pqzoom);
			h1=h1<0 ? -h1:h1;
			if(h1==0) continue;
			crColor=scf.syscolor[3];
			if(elg->vr.value[1]<0)
				crColor=RGB(255,128,255);
			mdc.D3DrawBar2j(art1,0,(double)h1,crColor,dx-rt.left,dy-rt.top,1);
			break;
		case 4: //电容器
			art=CreateDrawNRt(4,elg->pt,curzoom);
			cpt=art.CenterPoint();
			w=art.Width();
			h=art.Height();
			w=w>h ? h:w;
			w=w/2;
			art1.left=cpt.x-w;
			art1.right=cpt.x+w;
			art1.top=cpt.y-w;
			art1.bottom=cpt.y+w;
			if(elg->vr.value[2]==0) continue;
			//h2=(int)(hbas+elg->vr.value[2]*scf.pqzoom);
			h2=(int)(elg->vr.value[2]*1.0);
			h1=(int)(h2*elg->vr.value[0]/elg->vr.value[2]);
			h1=h1<0 ? 0:h1;
			h2=h2<0 ? 0:h2;
			h1=h1>h2 ?  h2:h1;
			if(h2==0) continue;
			mdc.D3DrawBar2j(art1,0,(double)h1,scf.syscolor[4],dx-rt.left,dy-rt.top,1);
			mdc.D3DrawBar2j(art1,(double)h1,(double)h2,scf.syscolor[5],dx-rt.left,dy-rt.top,1);
			break;
		}
	}
}
//显示灵敏度棒图(俯视)
void gdata::SHowSenBar(CDIB&mdc,CRect rt,int dx,int dy,RSEN *r_sen,int sesum)
{
	int i,j;
	double w,h1;
	DPOINT cnp;
	CDRect art1;
	if(scf.lmd==0) return;
	//先显示发电机的灵敏度
	for(i=0;i<sesum;i++){
		if(r_sen[i].senvalue==0) continue;
		art1=CreateDrawNRt(4,r_sen[i].elg->pt,curzoom);
		w=15*curzoom;
		j=r_sen[i].rtype;
		cnp=art1.CenterPoint();
		art1.left=cnp.x-w;
		art1.right=cnp.x+w;
		art1.top=cnp.y-w;
		art1.bottom=cnp.y+w;
		h1=r_sen[i].senvalue*scf.senzoom*curzoom+100.00;
		h1=h1<0 ? -h1:h1;
		if(r_sen[i].senvalue<0) mdc.D3DrawTaper(art1,h1,scf.sencolor[j],dx-rt.left,dy-rt.top);//这是倒锥形
		else mdc.D3DrawTaperu(art1,h1,scf.sencolor[j],dx-rt.left,dy-rt.top);//这是正锥形
	}
}



//显示灵敏度棒图(俯视)
void gdata::SHowSenBarj(CDIB&mdc,CRect rt,int dx,int dy,RSEN *r_sen,int sesum)
{
	int i,j;
	double w,h1;
	DPOINT cnp;
	CDRect art1;
	if(scf.lmd==0) return;
	//先显示发电机的灵敏度
	for(i=0;i<sesum;i++){ 
		if(r_sen[i].senvalue==0) continue;
		art1=CreateDrawNRt(4,r_sen[i].elg->pt,curzoom);
		j=r_sen[i].rtype;
		w=15*curzoom;
		cnp=art1.CenterPoint();
		art1.left=cnp.x-w;
		art1.right=cnp.x+w;
		art1.top=cnp.y-w;
		art1.bottom=cnp.y+w;
		h1=r_sen[i].senvalue*scf.senzoom*curzoom+100.00;
		h1=h1<0 ? -h1:h1;
		if(r_sen[i].senvalue<0) mdc.D3DrawTaperj(art1,h1,scf.sencolor[j],dx-rt.left,dy-rt.top);//这是倒锥形
		else mdc.D3DrawTaperuj(art1,h1,scf.sencolor[j],dx-rt.left,dy-rt.top);//这是正锥形
	}
}


//显示N-1BUS(俯视)
void gdata::SHowN1Bar(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum)
{
	int i;
	double w,h2;
	DPOINT cnp;
	CDRect art1;
	for(i=0;i<n1sum;i++)
	{ 
		if(r_n1[i].vn1==0) continue; 
		w=12;
		PointActToScr(&r_n1[i].opt,&cnp,1,curzoom);
		art1.left=cnp.x-w;
		art1.right=cnp.x+w;
		art1.top=cnp.y-w;
		art1.bottom=cnp.y+w;
		h2=30+r_n1[i].index*20;
		h2=h2<0 ? -h2:h2;
		mdc.D3DrawTaper(art1,h2,r_n1[i].vn1>0 ? scf.syscolor[16]:scf.syscolor[17],dx-rt.left,dy-rt.top);//这是锥形
	}
}

//显示N-1BUS(俯视)
void gdata::SHowN1Barj(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum)
{
	int i;
	double w,h2;
	DPOINT cnp;
	CDRect art1;
	for(i=0;i<n1sum;i++)
	{
		if(r_n1[i].vn1==0) continue;
		w=12;//*curzoom;
		PointActToScr(&r_n1[i].opt,&cnp,1,curzoom);
		art1.left=cnp.x-w;
		art1.right=cnp.x+w;
		art1.top=cnp.y-w;
		art1.bottom=cnp.y+w;
		h2=30+r_n1[i].index*20;//*curzoom;
		h2=h2<0 ? -h2:h2;
		mdc.D3DrawTaperj(art1,h2,r_n1[i].vn1>0 ? scf.syscolor[16]:scf.syscolor[17],dx-rt.left,dy-rt.top);//这是锥形
	}
}

//显示短路电流计算结果
void gdata::ShowSwtSccBar(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum)
{
	int i;
	double w,h2;
	DPOINT cnp;
	CDRect art1;
	if(scf.swtsum<=0) return;
	for(i=0;i<swsum;i++)
	{ 
		if(r_sw[i].dl.high==0) continue;
		w=12;
		PointActToScr(&r_sw[i].opt,&cnp,1,curzoom);
		art1.left=cnp.x-w;
		art1.right=cnp.x+w;
		art1.top=cnp.y-w;
		art1.bottom=cnp.y+w;
		h2=30+r_sw[i].dl.high*curzoom;
		h2=h2<0 ? -h2:h2;
		mdc.D3DrawTaper(art1,h2,scf.syscolor[20],dx-rt.left,dy-rt.top);//这是锥形
	}
}

void gdata::ShowSwtSccBarj(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum)
{
	int i;
	double w,h2;
	DPOINT cnp;
	CDRect art1;
	if(scf.swtsum<=0) return;
	for(i=0;i<swsum;i++)
	{ 
		if(r_sw[i].dl.high==0) continue;
		w=12;
		PointActToScr(&r_sw[i].opt,&cnp,1,curzoom);
		art1.left=cnp.x-w;
		art1.right=cnp.x+w;
		art1.top=cnp.y-w;
		art1.bottom=cnp.y+w;
		h2=30+r_sw[i].dl.high*curzoom;
		h2=h2<0 ? -h2:h2;
		mdc.D3DrawTaperj(art1,h2,scf.syscolor[20],dx-rt.left,dy-rt.top);//这是锥形
	}
}

//生成区域
void gdata::CreateSwtSccRgn(RSWT *r_sw,int swsum)
{
	int i;
	double w,h2;
	DPOINT cnp;
	CDRect art1;
	if(scf.swtsum<=0) return;
	for(i=0;i<swsum;i++)
	{
		if(r_sw[i].hrgn!=NULL) DeleteObject(r_sw[i].hrgn);
		r_sw[i].hrgn=NULL;

		if(r_sw[i].dl.high==0) continue;
		w=12;
		PointActToScr(&r_sw[i].opt,&cnp,1,curzoom);
		art1.left=cnp.x-w;
		art1.right=cnp.x+w;
		art1.top=cnp.y-w;
		art1.bottom=cnp.y+w;
		h2=30+r_sw[i].dl.high*curzoom;
		h2=h2<0 ? -h2:h2;
		r_sw[i].hrgn=msr->Get3dTaperRGN(art1,(int)h2); //这是锥形
	}
}

//显示开关动作顺序棒图(俯视)
void gdata::SHowSwtBar(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum)
{
	
	int i,j,m,n,sta;
	DWORD color;
	double h1,h2,hl;
	DPOINT  dpt[4];
	if(scf.swtsum<=0) return;
	n=30;
	for(i=0;i<swsum;i++)
	{
		if(r_sw[i].order==-1) continue;
		if(r_sw[i].soe[0].tm==0) continue;
		if(r_sw[i].soesum<1) continue;
		PointActToScr(r_sw[i].elg->pt,dpt,4,curzoom);
		h1=0;
		m=10-r_sw[i].order;
		h2=m*n;
		if(r_sw[i].order==0) h2+=90;
		hl=(double)h2/(double)r_sw[i].soesum;
		for(j=0;j<r_sw[i].soesum;j++)
		{
			h2=(int)(hl*(j+1));
			sta=r_sw[i].soe[j].sta;
			color=sta==0 ? scf.syscolor[18]:scf.syscolor[19];
			mdc.D3DrawRectBar(dpt,h1,h2,color,0xff0000,sta,dx-rt.left,dy-rt.top,1);
			h1=h2;
		}
	}
} 

//显示开关动作顺序棒图(俯视)
void gdata::SHowSwtBarj(CDIB&mdc,CRect rt,int dx,int dy,RSWT *r_sw,int swsum)
{
	int i,j,m,n,sta;
	DWORD color;
	double h1,h2,hl;
	DPOINT  dpt[4];
	if(scf.swtsum<=0) return;
	n=30;

	for(i=0;i<swsum;i++)
	{
		if(r_sw[i].order==-1) continue;
		if(r_sw[i].soe[0].tm==0) continue;
		if(r_sw[i].soesum<1) continue;
		PointActToScr(r_sw[i].elg->pt,dpt,4,curzoom);
		h1=0;
		m=10-r_sw[i].order;
		h2=m*n;
		if(r_sw[i].order==0) h2+=90;
		hl=(double)h2/(double)r_sw[i].soesum;
		for(j=0;j<r_sw[i].soesum;j++)
		{
			h2=(int)(hl*(j+1));
			sta=r_sw[i].soe[j].sta;
			color=sta==0 ? scf.syscolor[18]:scf.syscolor[19];
			mdc.D3DrawRectBarj(dpt,h1,h2,color,dx-rt.left,dy-rt.top,1);
			h1=h2;
		}
	}
} 

void gdata::CreateSwtRgn(RSWT *r_sw,int swsum)
{
	int i,n,h2;
	CDRect art;
	if(scf.swtsum<=0) return;
	n=30;
	for(i=0;i<swsum;i++)
	{	
		if(r_sw[i].hrgn!=NULL) DeleteObject(r_sw[i].hrgn);
		r_sw[i].hrgn=NULL;
		if(r_sw[i].soe[0].tm==0) continue;
		if(r_sw[i].order==-1) continue;
		if(r_sw[i].soesum<1) continue;
		art=CreateDrawNRt(4,r_sw[i].elg->pt,curzoom);
		h2=(10-r_sw[i].order)*n;
		if(r_sw[i].order==0) h2+=90;
		r_sw[i].hrgn=msr->Get3dRectBarRGN(art,h2);
	}
} 

//显示区域棒图(俯视)
void gdata::SHowZoneBar(CDIB&mdc,CRect rt,int dx,int dy,RPIE *r_pe,int pesum)
{
	int i;
	double w,h,h1,h2,tcur,tmax;
	CDRect art,art1; 
	CDPoint cpt;        
	N_PIE *pie; 
	for(i=0;i<pesum;i++)
	{
		pie=r_pe[i].pie;
		tcur=pie->pcur;
		tmax=pie->maxv;
		tcur=tcur<0 ? -tcur:tcur;
		if(tcur<=0) continue;
		art=CreateDrawNRt(4,pie->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		h1=tcur*znzoom;
		h2=tmax*znzoom;
		h1=h1<0 ? 0:h1;
		h2=h2<0 ? 0:h2;
		h1=h1>h2 ?  h2:h1;
		if(h2==0) continue;
		if(h1<h2)
		{
			mdc.D3DrawBar2(art1,0,h1,pie->color[1],dx-rt.left,dy-rt.top);
			mdc.D3DrawBar2(art1,h1,h2,pie->color[0],dx-rt.left,dy-rt.top,1);
		}else{
			h1=h1*1.2;
			mdc.D3DrawBar2(art1,0,h1,pie->color[0],dx-rt.left,dy-rt.top,1);
		}
	}
} 

//显示区域棒图(俯视)
void gdata::SHowZoneBarj(CDIB&mdc,CRect rt,int dx,int dy,RPIE *r_pe,int pesum)
{
	int i;
	double w,h,h1,h2,tcur,tmax;
	CDRect art,art1; 
	CDPoint cpt;        
	N_PIE *pie; 
	for(i=0;i<pesum;i++)
	{
		pie=r_pe[i].pie;
		tcur=pie->pcur;
		tmax=pie->maxv;
		if(tcur<=0) continue;
		art=CreateDrawNRt(4,pie->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		h1=tcur*znzoom;
		h2=tmax*znzoom;
		h1=h1<0 ? 0:h1;
		h2=h2<0 ? 0:h2;
		h1=h1>h2 ?  h2:h1;
		if(h2==0) continue;
		if(h1<h2)
		{
			mdc.D3DrawBar2j(art1,0,h1,pie->color[1],dx-rt.left,dy-rt.top);
			mdc.D3DrawBar2j(art1,h1,h2,pie->color[0],dx-rt.left,dy-rt.top,1);
		}else{
			h1=h1*1.2;
			mdc.D3DrawBar2j(art1,0,h1,pie->color[0],dx-rt.left,dy-rt.top,1);
		}
	}
} 

//生成变压器棒图区域(俯视)
void gdata::CreateZnRgn(RPIE  *r_pe,int pesum)
{
	int i;
	double w,h,h2,tcur,tmax;
	CDRect art,art1;
	DPOINT cpt;
	N_PIE *pie;
	for(i=0;i<pesum;i++){
		if(r_pe[i].hrgn!=NULL) DeleteObject(r_pe[i].hrgn);
		r_pe[i].hrgn=NULL;
		pie=r_pe[i].pie;
		tcur=pie->pcur;
		tmax=pie->maxv;
		art=CreateDrawNRt(4,pie->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2+2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		h2=tmax*znzoom;
		h2=h2<0 ? 0:h2;
		if(h2==0) continue;
		if(tcur>=tmax) h2=h2*1.2;
		r_pe[i].hrgn=msr->Get3dBarRGN(art1,(int)h2);
	}
}

//显示N-1BUS(俯视)
void gdata::CreateN1Rgn(N1BAR *r_n1,int n1sum)
{
	int i;
	double w,h2; 
	DPOINT cnp;
	CDRect art1;
	for(i=0;i<n1sum;i++)
	{
		if(r_n1[i].vn1==0) continue;
		w=12+2;
		PointActToScr(&r_n1[i].opt,&cnp,1,curzoom);
		art1.left=cnp.x-w;
		art1.right=cnp.x+w; 
		art1.top=cnp.y-w;   
		art1.bottom=cnp.y+w; 
		h2=30+r_n1[i].index*20;
		h2=h2<0 ? -h2:h2;
		r_n1[i].hrgn=msr->Get3dTaperRGN(art1,(int)h2); //这是锥形
	}
}

//显示系统发电负荷棒图(俯视)
void gdata::SHowSpieBar(CDIB&mdc,CRect rt,int dx,int dy,RSPIE *r_spe,int spesum)
{
	int i,j,n;
	double w,h,hg[5],v;
	CDRect art,art1; 
	CDPoint cpt;        
	N_SYSPIE *pie; 
	for(i=0;i<spesum;i++)
	{
		pie=r_spe[i].pie;
		n=pie->num;
		n=n>4 ? 4:n;
		art=CreateDrawNRt(4,pie->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		v=0;
		hg[0]=0;
		for(j=0;j<n;j++)
		{
			v+=pie->vl[j];
			hg[j+1]=500*v*curzoom;
		}
		for(j=0;j<n;j++)
		{
			mdc.D3DrawBar2(art1,hg[j],hg[j+1],pie->color[j+1],dx-rt.left,dy-rt.top);
		}
		mdc.D3DrawBar2(art1,hg[n-1],hg[n],pie->color[n],dx-rt.left,dy-rt.top,1);
	}
} 


//显示系统发电负荷棒图(俯视)
void gdata::SHowSpieBarj(CDIB&mdc,CRect rt,int dx,int dy,RSPIE *r_spe,int spesum)
{
	int i,j,n;
	double w,h,hg[5],v;
	CDRect art,art1; 
	CDPoint cpt;        
	N_SYSPIE *pie; 
	for(i=0;i<spesum;i++)
	{
		pie=r_spe[i].pie;
		n=pie->num;
		n=n>4 ? 4:n;
		art=CreateDrawNRt(4,pie->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		v=0;
		hg[0]=0;
		for(j=0;j<n;j++)
		{
			v+=pie->vl[j];
			hg[j+1]=500*v*curzoom;
		}
		for(j=0;j<n;j++)
		{
			mdc.D3DrawBar2j(art1,hg[j],hg[j+1],pie->color[j+1],dx-rt.left,dy-rt.top);
		}
		mdc.D3DrawBar2j(art1,hg[n-1],hg[n],pie->color[n],dx-rt.left,dy-rt.top,1);
	}
} 

void gdata::CreateSPieRgn(RSPIE  *r_spe,int spesum)
{
	int i,j,n;
	double w,h,hg[5],v;
	CDRect art,art1; 
	CDPoint cpt;        
	N_SYSPIE *pie; 
	for(i=0;i<spesum;i++)
	{
		pie=r_spe[i].pie;
		n=pie->num;
		n=n>4 ? 4:n;
		art=CreateDrawNRt(4,pie->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2+2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		v=0;
		hg[0]=0;
		for(j=0;j<n;j++)
		{
			v+=pie->vl[j];
			hg[j+1]=500*v*curzoom;
		}
		r_spe[i].hrgn=msr->Get3dBarRGN(art1,(int)hg[n]);
	}
}

//显示n-1影响设备
void gdata::SHowN1EftBar(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum)
{
	int i;
	//DWORD color;
	double w,h2;
	DPOINT cnp;
	CDRect art1;

	for(i=0;i<n1sum;i++)
	{ 
	
		if(r_n1[i].vn1==0) continue; 
		w=16;
		PointActToScr(&r_n1[i].opt,&cnp,1,curzoom);
		art1.left=cnp.x-w;
		art1.right=cnp.x+w;
		art1.top=cnp.y-w;
		art1.bottom=cnp.y+w;
		h2=r_n1[i].Hbar; 
		h2=h2<0 ? -h2:h2;
		
		if(r_n1[i].selbz==1)
		{
			mdc.D3DrawBar2(art1,0,h2,r_n1[i].color,dx-rt.left,dy-rt.top,1);
		}else
		{
			if(r_n1[i].vn1<0) 
				mdc.D3DrawTaper(art1,h2,r_n1[i].color,dx-rt.left,dy-rt.top);//这是倒锥形
			else 
				mdc.D3DrawTaperu(art1,h2,r_n1[i].color,dx-rt.left,dy-rt.top);//这是正锥形
		}
	}
}

//显示n-1影响设备
void gdata::SHowN1EftBarj(CDIB&mdc,CRect rt,int dx,int dy,N1BAR *r_n1,int n1sum)
{
	int i;
	//DWORD color;
	double w,h2;
	DPOINT cnp;
	CDRect art1;

	for(i=0;i<n1sum;i++)
	{ 
	
		if(r_n1[i].vn1==0) continue; 
		w=16;
		PointActToScr(&r_n1[i].opt,&cnp,1,curzoom);
		art1.left=cnp.x-w;
		art1.right=cnp.x+w;
		art1.top=cnp.y-w;
		art1.bottom=cnp.y+w;
		h2=r_n1[i].Hbar; 
		h2=h2<0 ? -h2:h2;
		
		if(r_n1[i].selbz==1)
		{
			mdc.D3DrawBar2j(art1,0,h2,r_n1[i].color,dx-rt.left,dy-rt.top,1);
		}else
		{
			if(r_n1[i].vn1<0) 
				mdc.D3DrawTaperj(art1,h2,r_n1[i].color,dx-rt.left,dy-rt.top);//这是倒锥形
			else 
				mdc.D3DrawTaperuj(art1,h2,r_n1[i].color,dx-rt.left,dy-rt.top);//这是正锥形
		}
	}
}

//显示N-1BUS(俯视)
void gdata::CreateN1EftRgn(N1BAR *r_n1,int n1sum)
{
	int i;
	double w,h2;
	DPOINT cnp;
	CDRect art1;
	for(i=0;i<n1sum;i++)
	{
		if(r_n1[i].hrgn!=NULL) DeleteObject(r_n1[i].hrgn);
		r_n1[i].hrgn=NULL;
		if(r_n1[i].vn1==0) continue;
		w=16+2;
		PointActToScr(&r_n1[i].opt,&cnp,1,curzoom);
		art1.left=cnp.x-w;
		art1.right=cnp.x+w;
		art1.top=cnp.y-w;
		art1.bottom=cnp.y+w;
		h2=r_n1[i].Hbar;
		h2=h2<0 ? -h2:h2;
		if(r_n1[i].selbz==1) r_n1[i].hrgn=msr->Get3dBarRGN(art1,(int)h2);
		else{
			if(r_n1[i].vn1<0) 
				r_n1[i].hrgn=msr->Get3dTaperRGN(art1,(int)h2);//这是倒锥形
			else 
				r_n1[i].hrgn=msr->Get3dTaperuRGN(art1,(int)h2); 
		}
	}
}

//生成发电储备棒图区域(俯视)
void gdata::CreateRevRgn(RREV  *r_rv,int rvsum)
{
	int i,h2;
	double w,h;
	CDRect art,art1;
	CRect crt;
	DPOINT cpt;
	N_ELEGRPA *elg;
	for(i=0;i<rvsum;i++){
		if(r_rv[i].hrgn!=NULL) DeleteObject(r_rv[i].hrgn);
		r_rv[i].hrgn=NULL;
		elg=r_rv[i].elg;
		switch(elg->subtype){
		case 1: //发电机
			art=CreateDrawNRt(4,elg->pt,curzoom);
			if(elg->vr.value[2]<=0) continue;
			if(elg->vr.value[2]<scf.gen3dminp&&scf.showrev==1) continue;
			if(!FindAGenCircle(elg->egrpid,art1,art)) continue;	
			art1.left-=2;
			art1.right+=2;
			art1.top-=2;
			art1.bottom+=2;
			if(scf.showrev==1) h2=(int)(hbas+elg->vr.value[2]*scf.pqzoom);
			//else h2=(int)(hbas+elg->vr.value[1]*scf.pqzoom);
			else h2=(int)(elg->vr.value[1]*1.0);
			h2=h2<0 ? -h2:h2;
			if(h2==0) continue;
			r_rv[i].hrgn=msr->Get3dBarRGN(art1,h2);
			break;
		case 4: //电容器
			art=CreateDrawNRt(4,elg->pt,curzoom);
			cpt=art.CenterPoint();
			w=art.Width();
			h=art.Height();
			w=w>h ? h:w;
			w=w/2;
			w+=2;
			art1.left=cpt.x-w;
			art1.right=cpt.x+w;
			art1.top=cpt.y-w;
			art1.bottom=cpt.y+w;
			//if(scf.showrev==2) h2=(int)(hbas+elg->vr.value[2]*scf.pqzoom);
			if(scf.showrev==2) h2=(int)(elg->vr.value[2]*1.0);
			else continue;
			h2=h2<0 ? -h2:h2;
			if(h2==0) continue;
			r_rv[i].hrgn=msr->Get3dBarRGN(art1,h2);
			break;
		}
	}
}

//生成变压器棒图区域(俯视)
void gdata::CreateTranRevRgn(RREV  *r_tr,int trsum)
{
	int i,h2;
	double w,h,maxp;
	CDRect art,art1;
	DPOINT cpt;
	N_ELEGRPA *elg;
	for(i=0;i<trsum;i++){
		if(r_tr[i].hrgn!=NULL) DeleteObject(r_tr[i].hrgn);
		r_tr[i].hrgn=NULL;
		elg=r_tr[i].elg;
		if(elg->subtype==7) maxp=elg->vr.value[1];
		else maxp=elg->vr.value[3];
		if(maxp==0) continue;
		art=CreateDrawNRt(4,elg->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2+2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		h2=(int)(hbas+maxp*scf.tpzoom);
		h2=h2<0 ? 0:h2;
		if(h2==0) continue;
		r_tr[i].hrgn=msr->Get3dBarRGN(art1,h2);
	}
}

//生成变压器棒图区域(俯视)
void gdata::CreateTranTRgn(RREV  *r_tr,int trsum)
{
	int i;
	double w,h,h2,tcur,tmax;
	CDRect art,art1;
	DPOINT cpt;
	N_ELEGRPA *elg;
	for(i=0;i<trsum;i++){
		if(r_tr[i].hrgn!=NULL) DeleteObject(r_tr[i].hrgn);
		r_tr[i].hrgn=NULL;
		elg=r_tr[i].elg;
		if(elg->subtype==7)
		{
			tcur=elg->vr.value[4];
			tmax=elg->vr.value[5];
		}else{
			tcur=elg->vr.value[6];
			tmax=elg->vr.value[7];
		}
		if(tcur<=0) continue;
		art=CreateDrawNRt(4,elg->pt,curzoom);
		cpt=art.CenterPoint();
		w=art.Width();
		h=art.Height();
		w=w>h ? h:w;
		w=w/2+2;
		art1.left=cpt.x-w;
		art1.right=cpt.x+w;
		art1.top=cpt.y-w;
		art1.bottom=cpt.y+w;
		h2=tmax*scf.tptzoom;
		h2=h2<0 ? 0:h2;
		if(h2==0) continue;
		if(tcur>=tmax) h2=h2*1.2;
		r_tr[i].hrgn=msr->Get3dBarRGN(art1,(int)h2);
	}
}
//生成灵敏度区域
void gdata::CreateSenRgn(RSEN  *r_sen,int sesum)
{
	int i,h1;
	double w;
	CDRect art,art1;
	DPOINT cnp;
	for(i=0;i<sesum;i++){
		if(r_sen[i].hrgn!=NULL) DeleteObject(r_sen[i].hrgn);
		r_sen[i].hrgn=NULL;
		if(r_sen[i].senvalue==0) continue;
		art1=CreateDrawNRt(4,r_sen[i].elg->pt,curzoom);
		w=15*curzoom+2;
		cnp=art1.CenterPoint();
		art1.left=cnp.x-w;
		art1.right=cnp.x+w;
		art1.top=cnp.y-w;
		art1.bottom=cnp.y+w;
		h1=(int)(r_sen[i].senvalue*scf.senzoom*curzoom)+100;
		h1=h1<0 ? -h1:h1;
		if(h1==0) continue;
		if(r_sen[i].senvalue<0) r_sen[i].hrgn=msr->Get3dTaperRGN(art1,h1);
		else r_sen[i].hrgn=msr->Get3dTaperuRGN(art1,h1);
	}
}


//生成潮流的区域
void gdata::CreateFlwRgn(RFLOW *r_fw,int fwsum)
{
	int i,j,ptsum;
	DPOINT dpt[21];
	POINT  *pt;
	double w;
	CRect rt;
	HRGN hrgn1,hrgn2;
	for(j=0;j<fwsum;j++)
	{
		if(r_fw[j].hrgn!=NULL) DeleteObject(r_fw[j].hrgn);
		r_fw[j].hrgn=NULL;
		r_fw[j].flw->hrgn=NULL;
		ptsum=r_fw[j].flw->ptsum;
		ptsum=ptsum>20 ? 20:ptsum;
		r_fw[j].ptsum=ptsum;
		PointActToScr(r_fw[j].flw->pt,dpt,ptsum,curzoom);
		pt=r_fw[j].pt;
		msr->DPtToScrPt(dpt,pt,ptsum,0,0);
		w=6;
		hrgn1=BCreateLineRGN1(CPoint(pt[0]),CPoint(pt[1]),w);
		for(i=1;i<ptsum-1;i++)
		{
			hrgn2=BCreateLineRGN1(CPoint(pt[i]),CPoint(pt[i+1]),w);
			if(hrgn2!=NULL)
			{
				CombineRgn(hrgn1,hrgn1,hrgn2,RGN_OR);
				DeleteObject(hrgn2);
			}
		}
		r_fw[j].hrgn=hrgn1;
		r_fw[j].flw->hrgn=hrgn1;
		GetRgnBox(hrgn1,&r_fw[j].rt);
 		rt=r_fw[j].rt;
		r_fw[j].ptsum=ptsum;
		for(i=0;i<ptsum;i++){
			pt[i].x=pt[i].x-rt.left+8;
			pt[i].y=pt[i].y-rt.top+8;
		}
	}
}

//生成水库的区域
void gdata::CreateResRgn(RRES  *r_rs,int  rssum)
{
	int i,ptsum;
	for(i=0;i<rssum;i++)
	{
		if(r_rs[i].hrgn!=NULL) DeleteObject(r_rs[i].hrgn);
		r_rs[i].hrgn=NULL;
		r_rs[i].res->hrgn=NULL;
		ptsum=r_rs[i].res->ptsum;
		PointActToScr(r_rs[i].res->pt,npt,ptsum,curzoom);
		msr->DPtToScrPt(npt,mpt,ptsum,0,0);
		r_rs[i].hrgn=CreatePolygonRgn(mpt,ptsum,ALTERNATE);
	}
}


void gdata::SetScfDefaultvalue()
{
	int i;
	for(i=0;i<6;i++){
		scf.cr[i].value[0]=(float)vl[i*5];
		scf.cr[i].value[1]=(float)vl[i*5+1];
		scf.cr[i].value[2]=(float)vl[i*5+2];
		scf.cr[i].value[3]=(float)vl[i*5+3];
		scf.cr[i].value[4]=(float)vl[i*5+4];
		scf.cr[i].color[0]=cr[i*5];
		scf.cr[i].color[1]=cr[i*5+1];
		scf.cr[i].color[2]=cr[i*5+2];
		scf.cr[i].color[3]=cr[i*5+3];
		scf.cr[i].color[4]=cr[i*5+4];
		strcpy(scf.cr[i].unit,ut[i]);
		scf.cr[i].vhow=(char)qz[i];
		scf.cr[i].emptyfill=(BYTE)fl[i];
	}
	for(i=0;i<10;i++) 	scf.syscolor[i]=scr[i];
	scf.pqzoom=1;
	scf.senzoom=1;
}
//计算PQ3D显示的立体放大倍数
void gdata::ComputePqZoom(RREV *r_rv, int rvsum,int wy)
{
	int i;
	double maxv=0,v;
	hbas=(float)(wy/4);
	for(i=0;i<rvsum;i++)
	{
		v=r_rv[i].elg->vr.value[2];
		if(maxv<v) maxv=v;
	}
	if(maxv!=0)
	{
		scf.pqzoom=(float)(wy/(maxv*5));
	}else scf.pqzoom=1;

}

void gdata::ComputeZnZoom(RPIE *r_pe, int pesum,int wy)
{
	int i;
	double maxv=0,v;
	hbas=(float)(wy/4);
	for(i=0;i<pesum;i++)
	{
		v=r_pe[i].pie->maxv;
		if(maxv<v) maxv=v;
	}
	if(maxv!=0)
	{
		znzoom=2*wy/(maxv*5);
	}else znzoom=1;

}

void gdata::ComputeTpzoom(RREV *r_tr, int trsum, int wy)
{
	int i;
	double maxv=0,v;
	hbas=(float)(wy/4);
	for(i=0;i<trsum;i++)
	{
		if(r_tr[i].elg->subtype==7) v=r_tr[i].elg->vr.value[1];
		else v=r_tr[i].elg->vr.value[3];
		if(maxv<v) maxv=v;
	}
	if(maxv!=0)
	{
		scf.tpzoom=(float)(wy/(maxv*5));
	}else scf.tpzoom=1;
}


void gdata::ComputeTptzoom(RREV *r_tr, int trsum, int wy)
{
	int i;
	double maxv=0,v;
	for(i=0;i<trsum;i++)
	{	
		if(r_tr[i].elg->subtype==7) v=r_tr[i].elg->vr.value[5];
		else v=r_tr[i].elg->vr.value[7];
		if(maxv<v) maxv=v;
	}
	if(maxv!=0)
	{
		scf.tptzoom=(float)(wy*2/(maxv*5));
	}else scf.tptzoom=1;
}

void gdata::ComputeSenzomm(RSEN *r_sen, int sesum, int wy)
{
	int i;
	double maxv=0,a;
	for(i=0;i<sesum;i++)
	{
		a=r_sen[i].senvalue;
		a=a<0 ? -a:a;
		if(maxv<a) maxv=a;
	}
	if(maxv!=0)
	{
		scf.senzoom=(float)(200/maxv);
	}else scf.senzoom=1;
}



//最后一幅画面是否是自动推出(mode=1)
bool gdata::LastHmiIsMode1()
{
	int i;
	if(curhmi<=1) return false;
	i=curhmi-1;
	if(hishmi[i].mode==1) return true;
	return false;
}

//显示断面棒图
void gdata::Showdms(CDIB &mdc, int dx,int dy,DMSECT *dm, int dmsum,CDRect *srt)
{
	double wd,hg;
	int i,j,n,h,h1,a;
	float Vmax,v1,v2;
	POINT pt[300],pt1;
	DPOINT pt2;
	CRect rt,rt1;

	if(curopzt!=1)	return;
	Vmax=0;
	switch(scf.ftype)
	{
	case 0:case 1:case 2:case 3:
		for(i=0;i<dmsum;i++) if(Vmax<dm[i].Pmax) Vmax=dm[i].Pmax;//找最大值
		break;
	case 4:
		for(i=0;i<dmsum;i++) if(Vmax<dm[i].Imax) Vmax=dm[i].Imax;//找最大值
		break;
	default:
		return;
	}
	if(Vmax==0)	return;
	
	wd=25*curzoom;
	hg=150*curzoom;
	for(i=0;i<dmsum;i++)
	{
		//先显示线路径
		n=0;
		for(j=0;j<dm[i].segsum;j++) n+=dm[i].dmsdot[j];
		PointActToScr(dm[i].pt,pt,n,curzoom);
		PtOffset(pt,n,dx,dy);
		//显示划线
		DrawDmLine(mdc,pt,dm[i].segsum,dm[i].dmsdot);

		
		switch(scf.ftype)
		{
		case 0:case 1:case 2:case 3:
			v1=dm[i].Pmax;
			v2=dm[i].Pcur;
			break;
		case 4:
			v1=dm[i].Imax;
			v2=dm[i].Icur;
			break;
		}
		v1=v1<0 ? -v1:v1;
		v2=v2<0 ? -v2:v2;
		if(v1==0){
			
			continue;
		}
		
		if(v2>v1) v2=v1;
		h1=(int)(hg*v1/Vmax);
		h=(int)(hg*v2/Vmax);
		a=h1;
		h1=h1/2;
		pt1=pt[n-1];
		rt.left=pt1.x;
		rt.top=pt1.y-h1;
		rt.right=(int)(pt1.x+wd);
		rt.bottom=pt1.y+h1;
		//设置选择矩形大小
		h1=(int)(h1/curzoom);
		pt2=dm[i].pt[n-1];
		srt[i].left=pt2.x;
		srt[i].top=pt2.y-h1;
		srt[i].right=pt2.x+wd/curzoom;
		srt[i].bottom=pt2.y+h1;
		////////////////////
		rt1=rt;
		rt1.top=rt1.bottom-h;
		rt.bottom=rt1.top;
		GLRectc(mdc.m_hDC,rt1,0x7f,0xff,4);
		GLRectc(mdc.m_hDC,rt,0x7f00,0x7fff7f,4);
	}
}

void gdata::GetSectFLwName(char *nm)
{
	char name[256],fnm[256],*lp,*lp1;
	strcpy(fnm,curfile);
	lp=strrchr(fnm,'\\');
	if(lp==NULL) lp=fnm;
	lp1=strrchr(lp,'.');
	if(lp1!=NULL) *lp1=0;
	sprintf(name,"%s_%d_%s.sfw",lp,curpage,cobj.curnm);
	strcpy(nm,cobj.runpath);
	strcat(nm,name);
}


//加入一个百分饼图
void gdata::AddPctPie(double x,double y,int id,int type,char *name)
{
	CDRect rt;
	N_BASATTR btr;		//基本属性
	N_PCTPIE pct;
	memset(&pct,0,sizeof(N_PCTPIE));
	rt.left=x-8;
	rt.top=y-8;
	rt.right=x+8;
	rt.bottom=y+8;
	rt.NormalizeRect();
	DRectTo4Dpt(&rt,pct.pt);
	pct.type=0;
	pct.did=id;
	pct.color1=0xff0000;
	pct.color2=0xffffff;
	pct.fcolor=0;
	pct.lf=cobj.font1;
	pct.maxv=100;
	pct.type=type;
	btr.size=sizeof(N_PCTPIE);
	btr.type=82;
	strcpy(pct.dev_name,name);
	AddCurLayerAObject(btr,&pct);
}

//添加一个对象
void gdata::AddCurLayerAObject(N_BASATTR &attr, void *obuf)
{
	int n;
	n=clayer->objnum;
	if(n==0){
	  clayer->obj=new DObj;
	};
	if(n>0){
	  clayer->obj=(DObj*)realloc(clayer->obj,sizeof(DObj)*(n+1));
	};
	clayer->obj[n].buf=NULL;
	clayer->obj[n].showdyn=0;
	clayer->obj[n].dbm=this;
	clayer->obj[n].AddObject(attr,obuf);
	clayer->objnum++;
}

//依据线路添加百分饼图
void gdata::CreatePctpie()
{
	double ptl[32];
	double x,y,len,dis,ys,angle;
	int i,j,k,n,m,lineid,oldsum,type;
	DPOINT *pt;
	N_FLOW  *fw;
	oldsum=clayer->objnum;
	for(i=0;i<clayer->objnum;i++)
	{
		if(clayer->obj[i].attr.type!=77) continue;
		fw=(N_FLOW*)clayer->obj[i].buf;
		lineid=fw->did;
		type=fw->type;
		pt=fw->pt;
		n=fw->ptsum;
		if(n<2||n>32) continue;
		len=0;
		for(j=0;j<n-1;j++)
		{
			ptl[j]=GetLength(pt[j],pt[j+1]);
			len+=ptl[j];
		}
		m=(int)(len/8); //计算可以有多少种位置
		m/=2;
		len/=2;
		if(m==0)
		{
			x=(pt[0].x+pt[1].x)/2.0;
			y=(pt[0].y+pt[1].y)/2.0;
		}else{
			for(j=0;j<=m;j++)
			{
				dis=len+j*8;
				k=GetLineSeg(ptl,ys,dis,n-1);
				angle=GetAngle(pt[k],pt[k+1]);
				x=pt[k].x+ys*cos(angle*mpi/180);
				y=pt[k].y-ys*sin(angle*mpi/180);
				if(PosIsOk(x,y,oldsum)) break;
				dis=len-j*8;
				k=GetLineSeg(ptl,ys,dis,n-1);
				angle=GetAngle(pt[k],pt[k+1]);
				x=pt[k].x+ys*cos(angle*mpi/180);
				y=pt[k].y-ys*sin(angle*mpi/180);
				if(PosIsOk(x,y,oldsum)) break;
			}
		}
		AddPctPie(x,y,lineid,type,fw->dev_name);
		fw->stapt.x = x;
		fw->stapt.y = y;
	}
}

//找到一个合适的位置添加PCTPIE图元
bool gdata::PosIsOk(double x,double y,int start)
{
	int i;
	DPOINT *pt;
	CDRect rt,rt1;
	rt.left=x-15;
	rt.top=y-15;
	rt.right=x+15;
	rt.bottom=y+15;
	for(i=start;i<clayer->objnum;i++)
	{
		if(clayer->obj[i].attr.type!=82) continue;
		pt=(DPOINT*)clayer->obj[i].buf;
		rt1=CreateDrawNRt(4,pt,1);
		rt1&=rt;
		if(!rt1.IsRectEmpty()) return false;
	}
	return true;
}

//返回一个值定义的颜色
//index=颜色号
//val=输入值
DWORD gdata::GetDefColor(int index,float val)
{
	short r1,g1,b1,r2,g2,b2,r,g,b;
	int i;
	double w,v;
	CTR_COLOR cr;
	cr=scf.cr[index];
	if(val>=cr.value[0]) return cr.color[0];
	if(val<=cr.value[4]) return cr.color[4];
	for(i=1;i<5;i++)
	{
		if(val>cr.value[i]) break;
	}
	if(i==5) return 0;
	r1=(WORD)(cr.color[i-1]&0xff);
	g1=(WORD)((cr.color[i-1]>>8)&0xff);
	b1=(WORD)((cr.color[i-1]>>16)&0xff);
	r2=(WORD)(cr.color[i]&0xff);
	g2=(WORD)((cr.color[i]>>8)&0xff);
	b2=(WORD)((cr.color[i]>>16)&0xff);
	w=cr.value[i-1]-cr.value[i];
	v=val-cr.value[i];
	if(w==0) return 0;
	r=(WORD)(r2+(r1-r2)*v/w);
	g=(WORD)(g2+(g1-g2)*v/w);
	b=(WORD)(b2+(b1-b2)*v/w);
	return RGB(r,g,b);
}

//返回所有的对象占用的矩形
void gdata::GetObjRect(CRect &rt)
{
	int i,j,m,f=0;
	CRect trt;
	DObj *bs;
	for(i=0;i<page.laysum;i++)
	{
		m=page.layer[i].objnum;
		bs=page.layer[i].obj;
		for(j=0;j<m;j++)
		{
			if(bs[j].attr.type<64) continue;
			bs[j].ort.GetRECT(trt);
			if(f==0){
				rt=trt;
				f=1;
			}
			else rt|=trt;

		}
	}
}


//添加一个对象
void gdata::AddTyAObject(N_BASATTR &attr, void *obuf)
{
	int n;
	n=tylayer.objnum;
	if(n==0){
	  tylayer.obj=new DObj;
	};
	if(n>0){
	  tylayer.obj=(DObj*)realloc(tylayer.obj,sizeof(DObj)*(n+1));
	};
	tylayer.obj[n].buf=NULL;
	tylayer.obj[n].showdyn=0;
	tylayer.obj[n].dbm=this;
	tylayer.obj[n].AddObject(attr,obuf);
	tylayer.objnum++;
}

//从对象中获取设备加到投影中
void gdata::GetDevObjToTy()
{
	int i,j,m,f=0;
	DObj *bs;
	//释放原有的投影层
	FreeMemTyLayer();
	for(i=0;i<page.laysum;i++)
	{
		m=page.layer[i].objnum;
		bs=page.layer[i].obj;
		for(j=0;j<m;j++)
		{
			switch(bs[j].attr.type)
			{
			case 66: case 77:case 78: case 79: case 1:case 2:case 3:case 4:case 5:case 6:case 7:
				AddTyAObject(bs[j].attr,bs[j].buf);
				break;
			}
		}
	}
}


//显示静态图形(如线条等)投影显示
void gdata::ShowTy(CDIB &mdc,int dx,int dy,CRect rt)
{
	int j,m;
	CRect trt,rt1;
	CPoint cpt;
	int sdx,sdy;
	DObj *bs;
	rt1=rt;
	rt1.OffsetRect(-dx,-dy);
	sdx=dx-rt.left;
	sdy=dy-rt.top; 
	m=tylayer.objnum;
	bs=tylayer.obj;   
	for(j=0;j<m;j++)  
	{ 
		if(!bs[j].ObjIsInRect(rt1)) continue;
		bs[j].ShowS(mdc,sdx,sdy,500);
	}
}  


//察看文件是否已打开
bool gdata::IsOpenedFile(char *newfile)
{
	if(strcmp(newfile,filename)==0) return true;
	return false;
}

void gdata::DeletePlate(long id, BYTE newValue)
{
	for(int i=0; i<this->m_PlateNum; i++)
	{
		if(m_PlateInfo[i].m_devid == id)
		{
			if(m_PlateInfo[i].m_rgn!=NULL && m_PlateInfo[i].m_subtype!=newValue)  
			{
				DeleteObject(m_PlateInfo[i].m_rgn);
				m_PlateInfo[i].m_subtype = newValue;
			}
			break;
		}
	}
}

void gdata::AddPlate(PlateInfo pltinfo)
{
	if(pltinfo.m_devid<=0||pltinfo.m_rgn==NULL)
		return;
	if(m_PlateNum>=MAXPLATE)
		return;
	bool isfind=false;
	for(int i=0; i<m_PlateNum; i++)
	{
		PlateInfo* ptmp = &m_PlateInfo[i];
		if(ptmp==NULL)
			continue;
		
		if(pltinfo.m_devid==ptmp->m_devid)//&&pltinfo.m_platetype==ptmp->m_platetype)
		{
			if(ptmp->m_rgn!=NULL)  DeleteObject(ptmp->m_rgn);
			memcpy(ptmp, &pltinfo, sizeof(PlateInfo));
			ptmp->m_rgn = pltinfo.m_rgn;
			//			ptmp->m_pdev=pltinfo.m_pdev;
			isfind=true;
			break;
		}
	}
	if(isfind==false)
	{
		if(m_PlateInfo[m_PlateNum].m_rgn!=NULL)  DeleteObject(m_PlateInfo[m_PlateNum].m_rgn);
		memcpy(&m_PlateInfo[m_PlateNum], &pltinfo, sizeof(PlateInfo));
		m_PlateInfo[m_PlateNum].m_rgn = pltinfo.m_rgn;
		//		m_PlateInfo[m_PlateNum].m_pdev=pltinfo.m_pdev;
		m_PlateNum++;
	}
}

//显示挂牌
void gdata::ShowPlatte(CDIB& mdc)
{
	for(int i=0; i<m_PlateNum; i++)
	{
		PlateInfo* ptmp = &m_PlateInfo[i];
		if(ptmp==NULL)
			continue;
		
		cobj.ShowSimg(mdc.m_hDC,ptmp->m_center.x,ptmp->m_center.y,ptmp->m_platetype, 12,12);
	}
}