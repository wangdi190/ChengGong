// comobj.cpp: implementation of the comobj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "comobj.h"
#include "base0.h"
#include "ptdefine.h"
#include "middll.h"
#include "filev30.h"
#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern comobj  cobj;


DWORD vcrd[]={0xff7080,0xff0080,0xaaebeb,0xffffff,0x800080,0xffff00,0x8000ff,
			  0xd0c0a8,0x80ff,0x70ffff,0x80ffeb,0x8080ff,0xff00,0x80ff80,
			  0x8a,0xf00000,0xf000,0x374b87,0x808080,0xc0c0c0,0x4040f0};

extern char *lst_vl[];
char  *rgntype[]={"政府","学校","宾馆","写字楼","公司","工厂","道路",
				 "边界","车站","居民区","饭店","排灌站","村庄","饲养基地",
				 "广场","街道","交通岗亭","绿地、草坪","旅游风景区","森林","田野","沙漠",
				 "其他"};
//取得字体样本///////////////////////////////////////////////////////
int CALLBACK EnumFontsProcs( LPLOGFONT lplf, LPTEXTMETRIC lptm,
		DWORD dwType,LPARAM lpData)
{
   if(cobj.fzs>=100) return 0;
   if(!cobj.IsInfont(lplf->lfFaceName)&&dwType==TRUETYPE_FONTTYPE){
    strcpy(cobj.fontlist[cobj.fzs].FaceName,lplf->lfFaceName);
    cobj.fzs++;
	}
    return 1;
};

FONTENUMPROC lpe;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

comobj::comobj()
{
	int i;
	CFont cf;
	fzs=0;
	cursor=0;
	outcolor=0xffffff;	
	bcolor1=0xff;
	bcolor2=0xff;
	tcolor=0xffffff;
	ncolor=0xff00;
	acolor=0xff;
	linewd=1;
	shadow=0;
	fill=0;
	fillmode=1;
	outline=0;
	tmode=0;
	edobj=0;
	close=0;
	vl=4;
	selsum=0;
	mcline=0;

	test=0;		
    curzoom=1;
	gwide=32;	
	gstyle=1;	
	gcolor=0x7f7f7f;
	gshow=1;
   
	ebcolor=0xa0a0a0;

	cf.CreateFont(-16,0,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"宋体" );
	cf.GetLogFont(&font);
	cf.DeleteObject();
	GetFontName();
	InitParam();
	//字体
	CFont cfnt;
	cfnt.CreateFont(16,8,0,0,400,0,0,0,1,OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH,"宋体" );
	cfnt.GetLogFont(&sysfont);
	cfnt.DeleteObject();
	for(i=0;i<21;i++) vcolor[i]=vcrd[i]; //初始化颜色
	InitPath();

	nocondev=0;
	nocdev=0;
	showsite=1;

	clptype=RegisterClipboardFormat("CJH_PW0");
}

comobj::~comobj()
{
	FreeMem();
}


bool comobj::IsInfont(char *name){ //查看字体名字是否存在
	int i;
	for(i=0;i<fzs;i++){
	 if(strcmp(name,fontlist[i].FaceName)==0) return true;
	};
	return false;
};


void comobj::GetFontName() //返回字体名字
{	
	HDC hdc=::GetDC(0);
	lpe=(FONTENUMPROC)MakeProcInstance((FARPROC)EnumFontsProcs,AfxGetInstanceHandle( ));
	EnumFonts(hdc,NULL,lpe,(LPARAM)NULL);
 	FreeProcInstance((FARPROC)lpe);
	ReleaseDC(0,hdc);
}

int comobj::GetFontIndex(char *facename)
{
	int i;
	for(i=0;i<fzs;i++){
	 if(strcmp(facename,fontlist[i].FaceName)==0) return i;
	};
	return 0;
}

//返回一个内存图片记录号
int comobj::GetMPICRecno(int id)
{
	int i;
	for(i=0;i<mpicsum;i++){
	  if(mpic[i].id==id) return i;
	};
	return -1;
}

//加减内存图片使用次数
void comobj::MpicAddSubUse(int id,int time)
{
	int i,j;
	j=GetMPICRecno(id);
	if(j<0) return;
	mpic[j].inuse=mpic[j].inuse+time;
	//删除该幅画面
	if(mpic[j].inuse<=0){  //当没有使用时,删除图形
		mpic[j].dc.~CMemDC();
		mpic[j].dc.dib=0;
		mpic[j].dc.hbitmap=0;
		for(i=j;i<mpicsum-1;i++){
		 mpic[i]=mpic[i+1];
		 mpic[i+1].dc.dib=0;
		 mpic[i+1].dc.hbitmap=0;
		 };
		mpicsum--;
	};
}
//返回一个小图记录号
int comobj::GetPICRecno(int id)
{
	int i;
	for(i=0;i<spicsum;i++){
	  if(spic[i].id==id) return i;
	};
	return -1;
}
//加减小图标使用次数
void comobj::SpicAddSubUse(int id,int time)
{
	int i=GetPICRecno(id);
	if(i<0) return;
	spic[i].inuse+=time;
}

//初始化参数
void comobj::InitParam()
{
	int i;
	memset(&egp,0,sizeof(N_ELEGRP)*MAXEGRP);
	for(i=0;i<MAXGIF;i++){
		gal[i].used=0;
		strcpy(gal[i].fnm,"");
	};
	patternID=-1;		//样板ID号,初始为-1;
    spicsum=0;			//图片总数
    mpicsum=0;			//图片数,最大=100
    egpsum=0;			//当前的组合图元数
	curzoom=1;			//当前的放大系数
}
//释放内存
void comobj::FreeMem()
{
	int i;
	//删除组合图元
	for(i=0;i<egpsum;i++){
		FreeEgp(i,0);
		FreeEgp(i,1);
	};
	memset(&egp,0,sizeof(N_ELEGRP)*MAXEGRP);
	//清除GIF动画内存
	for(i=0;i<MAXGIF;i++){
		if(gal[i].used>0){
			gal[i].dc.FreeMem();
			gal[i].used=0;
			strcpy(gal[i].fnm,"");
		}
	 };
	//清除内存图形
	for(i=0;i<mpicsum;i++){
	  if(mpic[i].dc.m_hDC!=NULL)   DeleteDC(mpic[i].dc.m_hDC);
	  if(mpic[i].dc.hbitmap!=NULL) DeleteObject(mpic[i].dc.hbitmap);
	  mpic[i].dc.m_hDC=NULL;
	  mpic[i].dc.hbitmap=NULL;
	  mpic[i].inuse=0;
	};
	//清除内存小图标
	for(i=0;i<spicsum;i++){
		spic[i].img.FreeMem();
	}
	patternID=-1;		//样板ID号,初始为-1;
    spicsum=0;			//图片总数
    mpicsum=0;			//图片数,最大=100
    egpsum=0;			//当前的组合图元数
	selsum=0;

	//标注显示标志
	nocondev=0;
	nocdev=0;
	showsite=1;
}
//释放图形内存
void comobj::FreeEgp(int num, int index)
{
	BASE0 *bs;
	int i,j;
	switch(index){
	case 0:
		bs=egp[num].bs1;
		j=egp[num].bsum1;
		egp[num].bs1=NULL;;
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

//返回一个未用的小图ID(目的是添加新的小图标)
int comobj::GetANoUsePICID()
{
	int i;
	for(i=0;i<spicsum+1;i++){
	  if(GetPICRecno(i)<0) return i;	//返回空ID
	};
	return -1; //未找到
}

//保存小图
int comobj::SaveSpic(FILE *fp)
{
	int i,sum;
	BITMAPINFO *bi;
	N_PHEAD ph;
	N_PDATA pd;
	int hsize,size,ks,sz;
	char *btmp,*src;
	cmpress cps;
	ph.flag=0xf9876761;
	ph.version=0x100;
	ph.picsum=spicsum;
	fwrite(&ph,sizeof(N_PHEAD),1,fp);
	sum=sizeof(N_PHEAD);
	pd.start=0x10891111;
	pd.press=1;
	for(i=0;i<spicsum;i++){
		bi=(BITMAPINFO*)spic[i].img.bnf;
		pd.bits=(BYTE)bi->bmiHeader.biBitCount;
		hsize=colornums(pd.bits)*sizeof(RGBQUAD)+sizeof(BITMAPINFOHEADER);
		pd.sPerline=spic[i].img.sPerline;
		pd.tranflag=spic[i].img.tranflag;
		pd.tranindex=spic[i].img.colorindex;
		pd.nWidth=spic[i].img.nWidth;
		pd.nHeight=spic[i].img.nHeight;
		pd.tranmode=spic[i].tranmode;
		pd.trancolor=spic[i].trancolor;
		pd.id=spic[i].id;
		pd.inuse=spic[i].inuse;
		size=pd.sPerline*pd.nHeight;
		pd.size=size+hsize;
		src=new char[pd.size+1000];
		memcpy(src,spic[i].img.bnf,hsize);
		memcpy(src+hsize,spic[i].img.dib,size);
		ks=pd.size;
	    btmp=new char[ks+10000];
		cps.initdata();
	    sz=cps.EEnCode(src,btmp,ks,ks+100);
		pd.psize=sz;
		fwrite(&pd,sizeof(N_PDATA),1,fp);
		sum+=sizeof(N_PDATA);
		fwrite(btmp,1,sz,fp);
		sum+=sz;
		delete btmp;
		delete src;
		};
	return sum; //返回保存的字节数
}

int comobj::colornums(int bits) //返回颜色数
{
	switch(bits)
    {
        case 1: return 2;
        case 4: return 16;
        case 8: return 256;
        default: return 0;
    }
}

//保存内存图形文件
int comobj::SaveMPic(FILE *fp)
{
	int i,sum;
	N_PHEAD  ph;
	N_MPicHD pd;
	int size,ks,sz;
	char *btmp,*src;
	cmpress cps;
	ph.flag=0xf9876762;
	ph.version=0x100;
	ph.picsum=mpicsum;
	fwrite(&ph,sizeof(N_PHEAD),1,fp);
	sum=sizeof(N_PHEAD);
	pd.start=0x10891112;
	for(i=0;i<mpicsum;i++){
		pd.bits=(BYTE)24;
		pd.sPerline=mpic[i].dc.sPerline;
		pd.nWidth=mpic[i].dc.nWidth;
		pd.nHeight=mpic[i].dc.nHeight;
		pd.id=mpic[i].id;
		pd.inuse=mpic[i].inuse;
		size=pd.sPerline*pd.nHeight;
		pd.size=size;
		src=new char[pd.size+100];
		memcpy(src,mpic[i].dc.dib,size);
		ks=pd.size;
	    btmp=new char[ks+100];
		cps.initdata();
	    sz=cps.EEnCode(src,btmp,ks,ks+100);
		pd.psize=sz;
		fwrite(&pd,sizeof(N_MPicHD),1,fp);
		sum+=sizeof(N_MPicHD);
		fwrite(btmp,1,sz,fp);
		sum+=sz;
		delete btmp;
		delete src;
		};
	return sum; //返回保存的字节数
}


//保存组合图元
int comobj::SaveEGrp(FILE *fp)
{
	FileV30 fv3;
	cmpress cps;
	int  i,j,m,n,size;
	char *lp;
	char *wbuf;     //写入缓冲区
	char *pbuf;		//压缩后的缓冲区
	N_EGPHEAD head;
	N_EGPDATA *eda;
	n=egpsum;
	//第一步:计算各图元的字节数
	size=0;
	for(i=0;i<n;i++){
	  size+=GetEleGrpSize(i,0);
	  size+=GetEleGrpSize(i,1);
	};
	size=size+n*sizeof(N_EGPDATA);
	//申请内存
	wbuf=new char[size+100];
	pbuf=new char[size+1000];
	//填充数据
	eda=(N_EGPDATA *)wbuf;
	for(i=0;i<n;i++){
	  eda[i].sav=egp[i];
	  eda[i].start=0x10891112;
	  eda[i].size1=GetEleGrpSize(i,0);
	  eda[i].size2=GetEleGrpSize(i,1);
	};
	lp=wbuf+n*sizeof(N_EGPDATA);
	for(i=0;i<n;i++){
		for(j=0;j<eda[i].sav.bsum1;j++){ //拷贝第一组数据
			m=fv3.CopyV5Data(egp[i].bs1[j],lp);
			lp+=m;
		};

		for(j=0;j<eda[i].sav.bsum2;j++){ //拷贝第一组数据
			m=fv3.CopyV5Data(egp[i].bs2[j],lp);
			lp+=m;
		};
	};
	//压缩数据
	cps.initdata();
	m=cps.EEnCode(wbuf,pbuf,size,size+100);

	
	//填充头
	head.flag=0x20010215;
	head.version=0x100;
	head.picsum=n;
	head.press=1;
	head.size=size;		//压缩前字节数
	head.psize=m;		//压缩后字节数
	//写入磁盘文件
	fwrite(&head,sizeof(N_EGPHEAD),1,fp); //写头
	
	fwrite(pbuf,m,1,fp);				//写入压缩数据
	delete wbuf;
	delete pbuf;
	return sizeof(N_EGPHEAD)+m;
}

//返回组合图元总字节数
int comobj::GetEleGrpSize(int num,int index) //num=记录号 index=图号0,1
{
	FileV30 fv3;
	int i,bssum;
	int size=0;
	BASE0 *bs;
	if(num>egpsum) return 0;
	switch(index){
	case 0: 
		bs=egp[num].bs1;
		bssum=egp[num].bsum1;
		break;
	case 1:
		bs=egp[num].bs2;
		bssum=egp[num].bsum2;
		break;
	default:
		return 0;
	};
	if(bs==NULL) return 0;
	for(i=0;i<bssum;i++) size+=fv3.GetV5Size(bs[i]);
	return size;
}

//从界面文件中读入小图标
void comobj::LoadSPic(FILE *fp)
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
	};
	spicsum=n;
}
//读入组合图元
void comobj::LoadEGP(FILE *fp,WORD ver)
{
	DWORD *dw;
	FileV30  fv3;
	N_BASATTR btr;		//基本属性
	char  buf[MAXSIZE]; //最大缓冲区10K
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
				for(k=0;k<16;k++) egp[n].index[k]=eda[i].sav.index[k];
			}else{	    		//非仪表
				m=m>3 ? 0:m;
				egp[n].sitesum=m;
				for(k=0;k<m;k++) egp[n].srt[k]=eda[i].sav.srt[k];
			}
			egp[n].rt1=eda[i].sav.rt1;
			egp[n].rt2=eda[i].sav.rt2;
			egp[n].id=eda[i].sav.id;
			egp[n].inuse=eda[i].sav.inuse;
			strcpy(egp[n].name,eda[i].sav.name);
			for(j=0;j<eda[i].sav.bsum1;j++)
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
void comobj::LoadMemPic(FILE *fp)
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

//添加一个空的组合图元
bool comobj::AddAEmptyEGP(int type)
{
	if(egpsum>=MAXEGRP){
	  MessageBox(0,"组合图元已满！","错误",MB_OK);
	  return false;
	};
	memset(&egp[egpsum],0,sizeof(N_ELEGRP));
	egp[egpsum].type=type;
	switch(type){
	case 0:
		strcpy(egp[egpsum].name,"新状态量");
		break;
	case 1:
		strcpy(egp[egpsum].name,"新设备量");
		break;
	case 2:
		strcpy(egp[egpsum].name,"新厂站量");
		break;
	case 3:
		strcpy(egp[egpsum].name,"新局");
		break;
	};
	egp[egpsum].id=GetANoUseEGPID(); //给予唯一的ID

	egp[egpsum].subtype=0;
	egpsum++;
	return true;
}
void comobj::AddAEGP(int num, int index, N_BASATTR &attr, void *obuf)
{
	int n;
	if(num>=egpsum) return;
	switch(index){
	case 0:
		n=egp[num].bsum1;
		if(n==0)egp[num].bs1=new BASE0;
		if(n>0)  egp[num].bs1=(BASE0*)realloc(egp[num].bs1,sizeof(BASE0)*(n+1));
		egp[num].bs1[n].AddObject(attr,obuf);
		
		egp[num].bsum1++;
		break;
	case 1:
		n=egp[num].bsum2;
		if(n==0) egp[num].bs2=new BASE0;
		if(n>0)  egp[num].bs2=(BASE0*)realloc(egp[num].bs2,sizeof(BASE0)*(n+1));
		egp[num].bs2[n].AddObject(attr,obuf);
		egp[num].bsum2++;
		break;
	}
}

//返回一个未用的图元ID(目的是添加新的图元)
int comobj::GetANoUseEGPID()
{
	int i;
	for(i=0;i<egpsum+1;i++){
	  if(GetEGPRecNo(i)<0) return i;	//返回空ID
	};
	return -1; //未找到
}

//返回图元记录号
int comobj::GetEGPRecNo(int id)
{
	int i;
	for(i=0;i<egpsum;i++){
	  if(egp[i].id==id) return i;
	}
	return -1;
}

//往缓冲区内加一图片
void comobj::AddMpic(char *filename, int id)
{
	int j=mpicsum;
	mpic[j].dc.ReadImageFile(filename);
	mpic[j].id=id;
	mpic[j].inuse=1;
	mpic[j].trancolor=1;
	mpic[j].tranmode=0;
	mpicsum++;
}

//返回未用的GAL位置
int comobj::GetNoUseGal()
{
	int i;
	for(i=0;i<MAXGIF;i++) if(gal[i].used==0) return i;
	return -1; //没有空位置
}

//打开一个GIF动画文件
void comobj::OpenGifAnl(int i,char *filename)
{
	char fnm[512];
	if(i>=MAXGIF) return;
	SetToLocalFile(filename,fnm);
	gal[i].dc.ReadImage(fnm);
	strcpy(gal[i].fnm,filename);
	gal[i].used=1;
}

//-一个GIF动画的使用次数
void comobj::DelAGifAnl(int i)
{
	if(i>=MAXGIF) return ;
	gal[i].used--;
	if(gal[i].used<=0){
		gal[i].dc.FreeMem();
		gal[i].fnm[0]=0;
	};
}

//+一个GIF动画的使用次数
void comobj::AddGifAnlUse(int i)
{
	if(i>=MAXGIF) return ;
	gal[i].used++;
}

//返回正在使用GIF的动画的记录号
int comobj::GetGifAnlRec(char *filename)
{
	int i;
	for(i=0;i<MAXGIF;i++){
	 if(gal[i].used>0&&strcmp(gal[i].fnm,filename)==0) return i;
	};
	return -1;
};
//返回一个未用的内存图片ID(目的是添加新的)
int comobj::GetANoUseMPICID()
{
	int i;
	for(i=0;i<mpicsum+1;i++){
	  if(GetMPICRecno(i)<0) return i;	//返回空ID
	};
	return -1; //未找到
}

//////////////////////////////////////////////////////////////////////
//初始化文件路径
void comobj::InitPath()
{
	int i;
	char tmppath[256]; //程序的路径
	GetCurrentDirectory(255,tmppath); //读入当前路径
	for(i=0;i<2;i++)	strcpy(path[i].path,tmppath);
	strcat(path[1].path,"\\hmifile");
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
	int i;
	char *p1;
	char fm[512];
	char name[256];
	strcpy(name,infile);
	if(IsFileExist(name)){
		strcpy(outfile,name);
		return;
	}
	p1=strrchr(name,'\\');
	if(p1!=NULL) p1++;
	else p1=name;
	for(i=0;i<2;i++){
	  sprintf(fm,"%s\\%s",path[i].path,p1);
	  if(IsFileExist(fm)){
		strcpy(outfile,fm);
		return;
	  }
	}
	strcpy(outfile,infile);
}



//返回电压名索引号
void comobj::SetVLColor(char *vlname,DWORD color)
{
	int i;
	for(i=0;i<20;i++){
		if(strcmp(vlname,lst_vl[i])==0){
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
	if(ReadColorData==NULL) return;
	ReadColorData(cr,crsum);
	for(i=0;i<crsum;i++){
		SetVLColor(cr[i].VLName,RGB(cr[i].R,cr[i].G,cr[i].B));
	}
}

bool comobj::SetColor(char *vname, BYTE r, BYTE g, BYTE b)
{
	if(SetColorData==NULL){
		MessageBox(0,"readdata.dll不存在或版本不正确！","错误",MB_OK|MB_ICONSTOP);	
		return false;
	}
	return SetColorData(vname,r,g,b);
}


//察看第index个和其他是否相同
bool comobj::IsSameWhithOther(int index)
{
	int i,j;
	bool r1,r2;
	N_ELEGRP *el;
	if(index>=egpsum) return false;
	el=(N_ELEGRP*)&egp[index];
	for(i=0;i<egpsum;i++){
		if(i==index||el->type!=egp[i].type||el->subtype!=egp[i].subtype) continue;
		//先察看第一组图元
		if(el->bsum1!=egp[i].bsum1) continue;
		r1=true;
		for(j=0;j<el->bsum1;j++){
			r1&=egp[i].bs1[j].IsSame(el->bs1[j]);
			if(!r1) break;
		}
		if(!r1) continue;
		//再察看第二组图元
		if(el->bsum2!=egp[i].bsum2) continue;
		r2=true;
		for(j=0;j<el->bsum2;j++){
			r2&=egp[i].bs2[j].IsSame(el->bs2[j]);
			if(!r2) break;
		}
		if(r2) return true;
	}
	return false;
}

//删除一个MPIC
void comobj::DelAMpic(int j)
{
	int i;
	if(j>=mpicsum) return;
	mpic[j].dc.~CMemDC();
	mpic[j].dc.dib=0;
	mpic[j].dc.hbitmap=0;
	for(i=j;i<mpicsum-1;i++){
	 mpic[i]=mpic[i+1];
	 mpic[i+1].dc.dib=0;
	 mpic[i+1].dc.hbitmap=0;
	 };
	mpicsum--;
}



//重置组合图元矩形大小
void comobj::ResetEgpRt()
{
	int i,j,n1,n2;
	CDRect rt;
	BASE0 *bs1,*bs2;
	for(i=0;i<egpsum;i++)
	{
		n1=egp[i].bsum1;
		n2=egp[i].bsum2;
		bs1=egp[i].bs1;
		bs2=egp[i].bs2;
		rt.SetRectEmpty();
		for(j=0;j<n1;j++)
		{
			rt|=bs1[j].ort;
		}
		egp[i].rt1=rt;
		rt.SetRectEmpty();
		for(j=0;j<n2;j++)
		{
			rt|=bs2[j].ort;
		}
		egp[i].rt2=rt;
	}
}

//重置组合图元矩形大小
void comobj::ResetAEgpRt(int i,CDRect &rtr)
{
	int j,n1,n2;
	double dx,dy;
	CDRect rt,rt1;
	BASE0 *bs1,*bs2;
	n1=egp[i].bsum1;
	n2=egp[i].bsum2;
	bs1=egp[i].bs1;
	bs2=egp[i].bs2;
	if(n1>0)
	{
		rt=bs1[0].GetObjRect();
		
		for(j=1;j<n1;j++)
		{
			rt1=bs1[j].GetObjRect();
			
			rt|=rt1;
		}
		segp[i].rt1=rt;
		rtr=rt;
		dx=-rt.left;
		dy=-rt.top;
		for(j=0;j<n1;j++)
		{
			bs1[j].Offset(dx,dy);
		}
		rt.Offset(dx,dy);
		egp[i].rt1=rt;

	}
	if(n2>0)
	{
		rt=bs2[0].GetObjRect();
		for(j=1;j<n2;j++)
		{
			rt|=bs2[j].GetObjRect();
		}
		segp[i].rt2=rt;
		dx=-rt.left;
		dy=-rt.top;
		for(j=0;j<n2;j++)
		{
			bs2[j].Offset(dx,dy);
		}
		rt.Offset(dx,dy);
		egp[i].rt2=rt;
	}
}