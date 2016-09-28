// BASE0.cpp: implementation of the BASE0 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "BASE0.h"
#include "comobj.h"
#include "gdata.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern comobj cobj;
extern gdata dbm;
extern CImageList  othimg;

char *wk[]={"日","一","二","三","四","五","六"};

CPoint mpt[3024]; //临时用的一个点缓冲区，最大2024个点
DPOINT npt[3024];
extern int testflag;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

BASE0::BASE0()
{
	buf=NULL;
	bakbuf=NULL;
}

BASE0::~BASE0()
{
	FreeMem();
}

void BASE0::FreeMem()
{
	N_SELFCTL *sft;
	if(attr.type==76&&buf!=NULL){  //如果是自助控件
	  	sft=(N_SELFCTL*)buf;
		if(sft->hinst!=NULL) FreeLibrary(sft->hinst);
	};
	if(buf!=NULL)	 delete buf;
	if(bakbuf!=NULL) delete bakbuf;
	buf=NULL;
	bakbuf=NULL;
}



void BASE0::AddObject(N_BASATTR &atr, void *obuf,int mode)
{
	/*
	mode=0时正常加载自助控件
	mode=1时不加载自助控件,为对象拷贝到缓充区用
	*/
	
	questdot=0;
	attr=atr;
	buf=NULL;
	bakbuf=NULL;
	sel=0;
	if(attr.size>0){
	  buf=new char[attr.size];
	  memcpy(buf,obuf,attr.size);
	};
		
	//如果是自助控件，特殊处理
	if(attr.type==76&&mode==0) InitSelfCtl();
	//计算矩形
	CreateSelRect();
}

//产生选择矩形
void BASE0::CreateSelRect()
{
	double r;
	DPOINT *pt;
	N_METER1 *mtr;
	int  fill,close;
	int  ptsum;
	switch(attr.type)
	{
	case 32:
		mtr=(N_METER1*)buf;
		r=GetLength(mtr->pt[0],mtr->pt[1]);
		ort.left=mtr->pt[0].x-r;ort.right=mtr->pt[0].x+r;
		ort.top=mtr->pt[0].y-r;	ort.bottom=mtr->pt[0].y+r;
		break;
	default:
		pt=GetObjectPt(ptsum,fill,close,0);
		ort=CreateNRt(ptsum,pt);
		ort.NormalizeRect();
		if(ort.left==ort.right){
			ort.left=(double)(ort.left-5);
			ort.right=(double)(ort.right+5);
		}
		if(ort.top==ort.bottom)
		{
			ort.top=(double)(ort.top-5);
			ort.bottom=(double)(ort.bottom+5);
		}
	}
	
}
//产生旧的(选中前)矩形
CDRect BASE0::CreateOldRect()
{
	double r;
	DPOINT *pt;
	int fill,close;
	N_METER1 *mtr;
	int    ptsum;
	CDRect  mrt;
	switch(attr.type)
	{
	case 32:
		mtr=(N_METER1*)bakbuf;
		r=GetLength(mtr->pt[0],mtr->pt[1]);
		mrt.left=mtr->pt[0].x-r;mrt.right=mtr->pt[0].x+r;
		mrt.top=mtr->pt[0].y-r;	mrt.bottom=mtr->pt[0].y+r;
		break;
	default:
		pt=GetObjectPt(ptsum,fill,close,1);
		mrt=CreateNRt(ptsum,pt);		
		mrt.NormalizeRect();
		if(mrt.left==mrt.right){
			mrt.left=(double)(mrt.left-5);
			mrt.right=(double)(mrt.right+5);
		}
		if(mrt.top==mrt.bottom){
			mrt.top=(double)(mrt.top-5);
			mrt.bottom=(double)(mrt.bottom+5);
		}
	}
	return mrt;
}

//显示多边形对象
void BASE0::ShowDbx(HDC hdc,int dx, int dy,int pm)
{
	DWORD c1;
	int tpsum;
	CDRect rt;
	N_DBX *dbx;
	dbx=(N_DBX*)buf;
	tpsum=dbx->ptsum;
	tpsum=dbx->ptsum>3000 ? 3000:dbx->ptsum;
	PointActToScr(dbx->pt,mpt,tpsum,dx,dy,cobj.curzoom);
	c1=pm==0 ? dbx->lcolor:0;
	DrawPoly(hdc,mpt,tpsum,c1,dbx->bcolor1,dbx->fill,dbx->close,(BYTE)cobj.curzoom);
}


//显示多边形对象
void BASE0::ShowDbx(CDIB&mdc,int dx, int dy)
{
	int i,tpsum; 
	POINT  tpt[1000];
	N_DBX *dbx;
	dbx=(N_DBX*)buf;
	tpsum=dbx->ptsum>1000 ? 1000:dbx->ptsum;
	PointActToScr(dbx->pt,npt,tpsum,dx,dy,cobj.curzoom);
	mdc.CSetLineStyle(dbx->ltype);
	if(dbx->close==0){
		for(i=0;i<tpsum;i++)
		{
			tpt[i].x=(int)npt[i].x;
			tpt[i].y=(int)npt[i].y;

		}
		mdc.CDrawDbxW(tpt,tpsum,dbx->lcolor,(int)dbx->width); 
	}
	else mdc.CDrawPoly(npt,tpsum,dbx->lcolor,dbx->bcolor1,dbx->fill,dbx->close);
	mdc.CSetLineStyle(0);
}

//显示矩形对象
void BASE0::ShowRect(HDC hdc,int dx, int dy,int pm)
{
	CRect rt;
	N_RECT *nrt;
	nrt=(N_RECT*)buf;
	PointActToScr(nrt->pt,mpt,4,dx,dy,cobj.curzoom);
	rt=CreateDrawRect(4,nrt->pt,dx,dy);
	if(nrt->fill==1) GLRectc(hdc,rt,nrt->bcolor1,nrt->bcolor1,5);
	switch(nrt->type)
	{
	case 0:
		GLDDraw3DRect(hdc,rt,nrt->lcolor,nrt->lcolor);
		break;
	case 1: 
		GLDDraw3DRect(hdc,rt,0,0xffffff);
		break;
	case 2:
		GLDDraw3DRect(hdc,rt,0xffffff,0);
		break;
	}
}

//显示园形对象
void BASE0::ShowCircle(HDC hdc,int dx, int dy,int pm)
{
	CDRect rt;
	CRect crt;
	N_CIRCLE *ncr;
	ncr=(N_CIRCLE*)buf;
	rt=CreateDrawNRt(4,ncr->pt,cobj.curzoom);
	rt.Offset(dx,dy);
	rt.GetRECT(crt);
	
	if(ncr->fill==1) GLEllipsec(hdc,crt,ncr->bcolor1,ncr->bcolor1,1);
	GLCircle(hdc,crt,1,ncr->lcolor);
}


//显示园形对象
void BASE0::ShowCircle(CDIB&mdc,int dx, int dy)
{
	CDRect rt; 
	N_CIRCLE *ncr;
	ncr=(N_CIRCLE*)buf;
	rt=CreateDrawNRt(4,ncr->pt,cobj.curzoom);
	rt.Offset(dx,dy);
	if(ncr->fill==1) mdc.CEllipsec(rt,ncr->bcolor1);
	mdc.CCircle(rt,ncr->lcolor);
}



//显示半波
void BASE0::ShowHSin(HDC hdc, int dx, int dy,int pm)
{
	DWORD c1;
	int n,c;
	CDRect art;
	CRect crt;
	N_HSIN *hsn;
	hsn=(N_HSIN *)buf;
	art=CreateDrawNRt(4,hsn->pt,cobj.curzoom);
	c=hsn->pirodic;
	c=c>30 ? 30:c;
	n=GetHSinPoint(art,npt,c,hsn->ltype);
	PointOffset(npt,mpt,n,dx,dy);
	c1=pm==0 ? hsn->color:0;
	GLDrawDbx(hdc,n,mpt,(int)cobj.curzoom,c1);
}


//显示半波
void BASE0::ShowHSin(CDIB&mdc, int dx, int dy)
{
	CDRect rt;
	RECT rt1;
	N_HSIN *hsn;
	hsn=(N_HSIN *)buf; 
	rt=CreateDrawNRt(4,hsn->pt,cobj.curzoom);
	rt.Offset(dx,dy);
	rt.GetRECT(rt1);
	mdc.CDrawHSin(rt1,hsn->color,hsn->ltype,hsn->pirodic,0);
}

void BASE0::ShowSin(HDC hdc, int dx, int dy,int pm)
{
	DWORD c1;
	int n,c;
	CDRect art;
	CRect crt;
	N_SIN *sn;
	sn=(N_SIN *)buf;
	art=CreateDrawNRt(4,sn->pt,cobj.curzoom);
	c=sn->pirodic;
	c=c>30 ? 30:c;
	n=GetSinPoint(art,npt,sn->pirodic,sn->ltype,sn->startdeg);
	PointOffset(npt,mpt,n,dx,dy);
	if(pm==0) c1=sn->color;else c1=0;
	GLDrawDbx(hdc,n,mpt,(int)cobj.curzoom,c1);
}


void BASE0::ShowSin(CDIB&mdc, int dx, int dy)
{
	CDRect rt; 
	RECT rt1;
	N_SIN *sn;
	sn=(N_SIN *)buf;
	rt=CreateDrawNRt(4,sn->pt,cobj.curzoom);
	rt.Offset(dx,dy);
	rt.GetRECT(rt1);
	mdc.CDrawSin(rt1,sn->color,sn->ltype,sn->pirodic,sn->startdeg);
}

//显示弧线(打印用)
void BASE0::ShowArc(HDC hdc, int dx, int dy,int pm)
{
	CDRect rt;
	CRect crt;
	N_ARC *arc; 
	arc=(N_ARC *)buf;
	rt=CreateDrawNRt(4,arc->pt,cobj.curzoom);
	rt.GetRECT(crt); 
	crt.OffsetRect(dx,dy);
	GLDrawArc(hdc,crt,arc->color,arc->start,arc->end,1);
}


//显示弧线
void BASE0::ShowArc(CDIB&mdc, int dx, int dy)
{
	RECT rt1;
	CDRect rt;
	N_ARC *arc;
	arc=(N_ARC *)buf;
	rt=CreateDrawNRt(4,arc->pt,cobj.curzoom);
	rt.Offset(dx,dy);
	rt.GetRECT(rt1);
	mdc.CDrawArc(rt1,arc->color,arc->start,arc->end);
}

void BASE0::DrawArrow(HDC hdc,DPOINT *pts,DWORD color)
{
	int n;
	double w;
	DPOINT pt1[3];
	pt1[0]=pts[0];
	pt1[1]=pts[1];
	PointOffset(pts,mpt,2,0,0);
	GLLine(hdc,mpt[0].x,mpt[0].y,mpt[1].x,mpt[1].y,color);
	w=4*cobj.curzoom;
	n=GetDirPoint(pt1[0],pt1[1],npt,(int)w);
	PointOffset(npt,mpt,n,0,0);
	GLPolygonc(hdc,mpt,4,color,color,0);
}

void BASE0::ShowArrow(HDC hdc, int dx, int dy,int pm)
{
	N_ARROW *arw;
	arw=(N_ARROW *)buf;
	PointActToScr(arw->pt,npt,2,dx,dy,cobj.curzoom);
	DrawArrow(hdc,npt,arw->color);
}



void BASE0::ShowArrow(CDIB&mdc, int dx, int dy)
{
	double w;
	N_ARROW *arw;
	arw=(N_ARROW *)buf;
	PointActToScr(arw->pt,npt,2,dx,dy,cobj.curzoom);
	w=4*cobj.curzoom;
	mdc.CDrawArrow(npt[0],npt[1],arw->color,(int)w); 
}


//显示半波
void BASE0::ShowGlass(CDIB&mdc, int dx, int dy)
{
	CRect rt;
	N_GLASS *gl;
	gl=(N_GLASS *)buf;
	rt=CreateDrawRect(4,gl->pt,dx,dy);
	mdc.CDrawGlass(rt,gl->color,gl->ocolor,gl->outline,gl->depth);
}


//显示CBAR
void BASE0::ShowText(HDC hdc, int dx, int dy,int pm)
{
	double angle,w;
	DWORD c1;
	CRect rt;
	LOGFONT font;
	N_TEXT *text;
	int len,h;
	text=(N_TEXT *)buf;
	rt=CreateDrawRect(4,text->pt,dx,dy);
	font=text->font;
	angle=GetAngle(text->pt[3],text->pt[2]);//计算角度
	angle*=10;
	font.lfEscapement=(long)angle;
	if(pm==0) c1=text->color;else c1=0;
	if(text->autofill==0){
	  font.lfHeight=(long)(font.lfHeight*cobj.curzoom*text->zm);
	  font.lfWidth=(long)(font.lfWidth*cobj.curzoom*text->zm);
	  GLDDrawText(hdc,&rt,&font,text->text,c1,text->style,DT_LEFT|DT_WORDBREAK);
	}else{
		len=strlen(text->text);
		if(len<=0) return;
		w=GetLength(text->pt[0],text->pt[1])*cobj.curzoom;
		h=(int)(GetLength(text->pt[0],text->pt[3])*cobj.curzoom);
		font.lfHeight=h;
	    font.lfWidth=(long)w/len;
		GLDDrawText(hdc,&rt,&font,text->text,c1,text->style,DT_LEFT);
	}
}

//显示CBAR
void BASE0::ShowMTText(HDC hdc, int dx, int dy,int pm)
{
	double angle;
	char  tx[256];
	DWORD c1;
	CRect rt;
	LOGFONT font;
	N_MTTEXT *text;
	int len;
	text=(N_MTTEXT *)buf;
	rt=CreateDrawRect(4,text->pt,dx,dy);
	font=text->lf;
	angle=GetAngle(text->pt[3],text->pt[2]);//计算角度
	angle*=10;
	font.lfEscapement=(long)angle;
	if(pm==0) c1=text->fcolor;else c1=0;
	GetSubTxt(text->text,tx);
	len=strlen(tx);
	if(len<=0) return;
	font.lfHeight=(long)(font.lfHeight*cobj.curzoom);
	font.lfWidth=(long)(font.lfWidth*cobj.curzoom);
	GLDDrawText(hdc,&rt,&font,tx,c1,0,DT_LEFT);
}


void BASE0::GetSubTxt(char *obuf,char *nbuf)
{
	int n;
	char *lp;
	lp=strstr(obuf,"===");
	if(lp!=NULL)
	{
		n=lp-obuf;
		n=n>255 ? 255:n;
		strncpy(nbuf,obuf,n);
		nbuf[n]=0;
		return;
	}
	strcpy(nbuf,obuf);
}

//显示电气端子(打印用)
void BASE0::ShowESite(HDC hdc, int dx, int dy,int pm)
{
	int w,h,m,k;
	DWORD c1;
	double n;
	CRect rt;
	CDPoint apt;
	CPoint cpt;
	N_ESITE *es;
	es=(N_ESITE *)buf;
	rt=CreateDrawRect(4,es->pt,dx,dy);
	apt.x=(double)((double)(es->pt[0].x+es->pt[1].x+es->pt[2].x+es->pt[3].x)/(double)4);
	apt.y=(double)((double)(es->pt[0].y+es->pt[1].y+es->pt[2].y+es->pt[3].y)/(double)4);
	apt.ActPtToScr(cobj.curzoom);
	apt.Offset(dx,dy);
	apt.GetPOINT(cpt);
	w=rt.Width();
	h=rt.Height();
	n=w>h ? h:w;
	m=(int)n;
	k=m%2;
	m/=2;
	rt.left=(int)(apt.x-m);
	rt.right=(int)(apt.x+m+k);
	rt.top=(int)(apt.y-m);
	rt.bottom=(int)(apt.y+m+k);
	if(pm==0) c1=es->color;else c1=0;
	switch(es->solder){
	case 0:
		GLCircle(hdc,rt,1,c1);
		break;
	case 1:
		GLEllipsec(hdc,rt,c1,c1,0);
		break;
	};
}


//显示电气端子
void BASE0::ShowESite(CDIB&mdc, int dx, int dy)
{
	int w,h,m,k;
	DWORD c1;
	double n;
	CRect rt;
	CDPoint apt;
	CPoint cpt;
	N_ESITE *es;
	es=(N_ESITE *)buf;
	rt=CreateDrawRect(4,es->pt,dx,dy);
	apt.x=(double)((double)(es->pt[0].x+es->pt[1].x+es->pt[2].x+es->pt[3].x)/(double)4);
	apt.y=(double)((double)(es->pt[0].y+es->pt[1].y+es->pt[2].y+es->pt[3].y)/(double)4);
	apt.ActPtToScr(cobj.curzoom);
	apt.Offset(dx,dy);
	apt.GetPOINT(cpt);
	w=rt.Width(); 
	h=rt.Height();
	n=w>h ? h:w;
	m=(int)n;
	k=m%2;
	m/=2;
	rt.left=(int)(apt.x-m);
	rt.right=(int)(apt.x+m+k);
	rt.top=(int)(apt.y-m);
	rt.bottom=(int)(apt.y+m+k);
	c1=es->color;
	switch(es->solder){
	case 0:
		mdc.CCircle(rt,c1);
		break;
	case 1:
		mdc.CEllipsec(rt,c1);
		break;
	};
}


//显示母板
void BASE0::ShowEgpMb(HDC hdc, int dx, int dy,int pm)
{
	DWORD c1;
	CRect rt;
	N_EGPMB *em;
	em=(N_EGPMB *)buf;
	if(em->mode==0) return;
	rt=CreateDrawRect(4,em->pt,dx,dy);
	if(pm==0) c1=em->color;else c1=0;
	GLRect(hdc,rt.left,rt.top,rt.right,rt.bottom,1,c1);
}

//显示坐标
void BASE0::ShowCoordnate(HDC hdc, int dx, int dy,int pm)
{
	double w;
	CRect rt;
	N_COORDINATE *co,tm;
	co=(N_COORDINATE *)buf;
	rt=CreateDrawRect(4,co->pt,dx,dy);
	if(co->xmax<co->xmin){
		co->xmax=100;
		co->xmin=0;
	}
	if(co->ymax<co->ymin){
		co->ymax=100;
		co->ymin=0;
	}
	tm=co[0];
	tm.width1=(int)(tm.width1*cobj.curzoom);
	tm.width2=(int)(tm.width2*cobj.curzoom);
	tm.fontx.lfHeight=(long)(tm.fontx.lfHeight*cobj.curzoom/tm.zm);
	tm.fontx.lfWidth=(long)(tm.fontx.lfWidth*cobj.curzoom/tm.zm);
	tm.fonty.lfHeight=(long)(tm.fonty.lfHeight*cobj.curzoom/tm.zm);
	tm.fonty.lfWidth=(long)(tm.fonty.lfWidth*cobj.curzoom/tm.zm);
	w=tm.width1;
	tm.width1=w>255 ? 255:w; 
	w=tm.width2;
	tm.width2=w>255 ? 255:w; 
	DrawCoordinate(hdc,rt,1,tm,pm);
}

//显示表格线
void BASE0::ShowTable(HDC hdc, int dx, int dy,int pm)
{
	double w;
	CRect rt;
	N_TABLE *ta,tm;
	ta=(N_TABLE *)buf;
	tm=ta[0];
	rt=CreateDrawRect(4,ta->pt,dx,dy);
	w=(double)(tm.width*cobj.curzoom);
	w=w>255 ? 255:w;
	tm.width=(BYTE)w;
	DrawTable(hdc,rt,tm,pm);
}


//显示图片
void BASE0::ShowImg(CDIB&mdc, int dx, int dy)
{
	int i;
	CRect rt;
	N_IMG *img;
	img=(N_IMG*)buf;
	rt=CreateDrawRect(4,img->pt,dx,dy);
	i=cobj.GetMPICRecno(img->imgID);
	if(i==-1) return;
	if(img->zoom==1)
	{
	  SetStretchBltMode(mdc.m_hDC,COLORONCOLOR);
	  StretchBlt(mdc.m_hDC,rt.left,rt.top,rt.Width(),rt.Height(),cobj.mpic[i].dc.m_hDC,0,0,cobj.mpic[i].dc.nWidth,cobj.mpic[i].dc.nHeight,SRCCOPY);
	  return;
	};
	if(img->depth==0)	mdc.TranImgShadow(cobj.mpic[i].dc,rt,img->shadow);
	if(img->depth>0)	mdc.CopyImgPercent(cobj.mpic[i].dc,rt,img->depth);
}

void BASE0::ShowImg(HDC hdc, int dx, int dy)
{
	int i;
	CRect rt;
	N_IMG *img;
	img=(N_IMG*)buf;
	rt=CreateDrawRect(4,img->pt,dx,dy);
	i=cobj.GetMPICRecno(img->imgID);
	if(i==-1) return;
	if(img->zoom==1){
		SetStretchBltMode(hdc,COLORONCOLOR);
		StretchBlt(hdc,rt.left,rt.top,rt.Width(),rt.Height(),cobj.mpic[i].dc.m_hDC,
			0,0,cobj.mpic[i].dc.nWidth,cobj.mpic[i].dc.nHeight,SRCCOPY);
  	}else cobj.mpic[i].dc.BitBlt(hdc,rt,SRCCOPY);
}

//显示仪表1
void BASE0::ShowMeter1(HDC hdc,int dx, int dy)
{
	int i,j,n,dot,fw,axw,pw,nbz;
	char p[100];
	LOGFONT lf;
	double angle,r,as,ae,a,b,ax,bx,r1,r2,r3,r4,nx,ag,bg,val,xl,v,a1,a2,v1,v2,vmax,vmin;
	DPOINT cpt,spt[2];
	CPoint pt1,pt2;
	CRect rt;
	N_METER1 *mtr;
	mtr=(N_METER1*)buf;
	PointActToScr(mtr->pt,npt,2,dx,dy,cobj.curzoom);
	spt[0]=npt[0];
	spt[1]=npt[1];
	cpt=npt[0];
	angle=GetAngle(npt[0],npt[1]);
	r=GetLength(npt[0],npt[1]);
	a=mtr->angle;
	a=a>180 ? 180:a;
	a=a<10 ? 10:a;
	if(a>175) nbz=1;else nbz=0;
	mtr->angle=(BYTE)a;
	as=angle+a;
	ae=angle-a;
	lf=mtr->font;
	lf.lfHeight=(long)(lf.lfHeight*cobj.curzoom*mtr->zm);
	lf.lfWidth=(long)(lf.lfWidth*cobj.curzoom*mtr->zm);
	fw=lf.lfHeight>0 ? lf.lfHeight:-lf.lfHeight;
	b=mtr->slen*cobj.curzoom*mtr->zm;
	switch(mtr->shownum)
	{
	case 1:
		r=r-fw;
		r4=r-fw/4;;
		break;
	case 2:
		r4=r-b-fw;
		break;
	}
	if(mtr->shownum==1)	r=r-fw;
	//画刻度  
	r1=r;
	r2=r-b/2;  
	r3=r-b;
	mtr->scale=mtr->scale<2 ? 2:mtr->scale;
	ax=(double)(2*a)/(double)(mtr->scale);
	bx=(double)ax/(double)(mtr->scales);
	v=mtr->Vmax-mtr->Vmin;
	if(v==0){
		mtr->Vmax=100;
		mtr->Vmin=0;
		v=100;
	}
 	xl=a*2/v;
	mtr->alarm=mtr->alarm>2 ? 2:mtr->alarm;
	vmax=mtr->Vmax;
	vmin=mtr->Vmin;
	for(i=0;i<mtr->alarm;i++) //画告警刻度背景
	{
		v1=mtr->val[i*2];
		v2=mtr->val[i*2+1];
		if(v1>vmax) continue;
		if(v1<vmin) v1=vmin;
		if(v2<vmin) continue;
		if(v2>vmax) v2=vmax;
		if(v2<v1) continue;
		a1=as-xl*(v1-mtr->Vmin); 
		a2=as-xl*(v2-mtr->Vmin);
		GLDrawArcBand(hdc,cpt,r3,r2,a1,a2,mtr->cr[i]);
	}
	if(mtr->showarc==1)
	{
		rt.left=(int)(cpt.x-r3);rt.right=(int)(cpt.x+r3+1);
		rt.top=(int)(cpt.y-r3);rt.bottom=(int)(cpt.y+r3+1);
		GLDrawArc(hdc,rt,mtr->scr,ae,as,1);
	}
	dot=mtr->numdot;
	dot=dot>7 ? 7:dot;
 	n=mtr->scale;
	nx=(mtr->Vmax-mtr->Vmin)/(mtr->scale);
	for(i=0;i<=n;i++)
	{
		ag=ae+i*ax;
		pt1=GetRPt(cpt,ag,r1);
		pt2=GetRPt(cpt,ag,r3);
		if(mtr->stype==0) GLLine(hdc,pt1.x,pt1.y,pt2.x,pt2.y,mtr->scr);
		else ShowKd1(hdc,pt1,pt2,mtr->scr);
		if(i<n)
		{
			for(j=1;j<=mtr->scales;j++)
			{
				bg=ag+bx*j;
				pt1=GetRPt(cpt,bg,r2);
				pt2=GetRPt(cpt,bg,r3);
				GLLine(hdc,pt1.x,pt1.y,pt2.x,pt2.y,mtr->scr);
			}
		}
		//显示数字
		if(mtr->shownum!=0)
		{
			if(nbz==1&&i==n) continue;
			pt1=GetRPt(cpt,ag,r4);
			rt.left=(int)(pt1.x-fw*2);
			rt.right=(int)(pt1.x+fw*2);
			rt.top=(int)(pt1.y-lf.lfHeight/2);
			rt.bottom=(int)(pt1.y+lf.lfHeight/2);
			val=nx*(n-i)+mtr->Vmin;
			GetDoubleStr(val,p,dot);
			GLDDrawText(hdc,&rt,&lf,p,mtr->scr,0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);

		}
	}
	//显示指针
	axw=(int)(mtr->axw*cobj.curzoom*mtr->zm);
	pw=(int)(mtr->pw*cobj.curzoom*mtr->zm);
	switch(mtr->pstyle)
	{
	case 0:
		ShowMPt1(hdc,spt[0],r3,angle,axw,pw,mtr->pcr);
		break;
	case 1:
		ShowMPt2(hdc,spt[0],r3,angle,axw,pw,mtr->pcr);
		break;
	case 2:
		ShowMPt3(hdc,spt[0],r3,angle,axw,pw,mtr->pcr);	
		break;
	case 3:
		ShowMPt4(hdc,spt[0],r3,angle,axw,pw,mtr->pcr);	
		break;
	case 4:
		ShowMPt5(hdc,spt[0],r3,angle,axw,pw,mtr->pcr);
		break;
	}
}

//显示仪表1
void BASE0::ShowMeter1(CDIB&mdc,int dx, int dy) 
{
	int i,j,n,dot,fw,nbz;
	char p[100];
	LOGFONT lf;
	double angle,r,as,ae,a,b,ax,bx,r1,r2,r3,r4,nx,ag,bg,val,xl,v,a1,a2,axw,pw,v1,v2,vmax,vmin;
	DPOINT cpt,spt[2];
	DPOINT pt1,pt2;
	CRect rt;
	N_METER1 *mtr;
	mtr=(N_METER1*)buf;
	PointActToScr(mtr->pt,npt,2,dx,dy,cobj.curzoom);
	spt[0]=npt[0];
	spt[1]=npt[1];
	cpt=npt[0];
	angle=GetAngle(npt[0],npt[1]);
	r=GetLength(npt[0],npt[1]);
	a=mtr->angle;
	a=a>180 ? 180:a;
	a=a<10 ? 10:a;
	if(a>175) nbz=1;else nbz=0;
	mtr->angle=(BYTE)a;
	as=angle+a;
	ae=angle-a;
	lf=mtr->font;
	lf.lfHeight=(long)(lf.lfHeight*cobj.curzoom*mtr->zm);
	lf.lfWidth=(long)(lf.lfWidth*cobj.curzoom*mtr->zm);
	fw=lf.lfHeight>0 ? lf.lfHeight:-lf.lfHeight;
	b=mtr->slen*cobj.curzoom*mtr->zm;
	switch(mtr->shownum)
	{
	case 1:
		r=r-fw;
		r4=r-fw/4;
		break;
	case 2:
		r4=r-b-fw;
		break;
	}
	if(mtr->shownum==1)	r=r-fw;
	//画刻度  
	r1=r;
	r2=r-b/2;  
	r3=r-b;
	mtr->scale=mtr->scale<2 ? 2:mtr->scale;
	ax=(double)(2*a)/(double)(mtr->scale);
	bx=(double)ax/(double)(mtr->scales);
	v=mtr->Vmax-mtr->Vmin;
	if(v==0){
		mtr->Vmax=100;
		mtr->Vmin=0;
		v=100;
	}
 	xl=a*2/v;
	mtr->alarm=mtr->alarm>2 ? 2:mtr->alarm;
	vmax=mtr->Vmax;
	vmin=mtr->Vmin;
	for(i=0;i<mtr->alarm;i++) //画告警刻度背景
	{
		v1=mtr->val[i*2];
		v2=mtr->val[i*2+1];
		if(v1>vmax) continue;
		if(v1<vmin) v1=vmin;
		if(v2<vmin) continue;
		if(v2>vmax) v2=vmax;
		if(v2<v1) continue;
		a1=as-xl*(v1-mtr->Vmin); 
		a2=as-xl*(v2-mtr->Vmin);
		mdc.GLDrawArcBand(cpt,r3,r2,a1,a2,mtr->cr[i]);
	}
	if(mtr->showarc==1)
	{
		rt.left=(int)(cpt.x-r3);rt.right=(int)(cpt.x+r3+1);
		rt.top=(int)(cpt.y-r3);rt.bottom=(int)(cpt.y+r3+1);
		mdc.CDrawArc(rt,mtr->scr,ae,as);
	}
	dot=mtr->numdot;
	dot=dot>7 ? 7:dot;
 	n=mtr->scale;
	nx=(mtr->Vmax-mtr->Vmin)/(mtr->scale);
	for(i=0;i<=n;i++)
	{
		ag=ae+i*ax;
		pt1=GetRDPt(cpt,ag,r1);
		pt2=GetRDPt(cpt,ag,r3);
		if(mtr->stype==0) mdc.CDLine(pt1,pt2,mtr->scr);
		else ShowKd1(mdc,pt1,pt2,mtr->scr);
		if(i<n)
		{
			for(j=1;j<=mtr->scales;j++)
			{
				bg=ag+bx*j;
				pt1=GetRDPt(cpt,bg,r2);
				pt2=GetRDPt(cpt,bg,r3);
				mdc.CDLine(pt1,pt2,mtr->scr);
			}
		}
		//显示数字
		if(mtr->shownum!=0)
		{
			if(nbz==1&&i==n) continue;
			pt1=GetRDPt(cpt,ag,r4);
			rt.left=(int)(pt1.x-fw*2);
			rt.right=(int)(pt1.x+fw*2);
			rt.top=(int)(pt1.y-lf.lfHeight);
			rt.bottom=(int)(pt1.y+lf.lfHeight);
			val=nx*(n-i)+mtr->Vmin;
			GetDoubleStr(val,p,dot);
			GLDDrawText(mdc.m_hDC,&rt,&lf,p,mtr->scr,0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
	}
	//显示指针
	axw=mtr->axw*cobj.curzoom*mtr->zm;
	pw=mtr->pw*cobj.curzoom*mtr->zm;
	switch(mtr->pstyle)
	{
	case 0:
		ShowMPt1(mdc,spt[0],r3,angle,axw,pw,mtr->pcr);
		break;
	case 1:
		ShowMPt2(mdc,spt[0],r3,angle,axw,pw,mtr->pcr);
		break;
	case 2:
		ShowMPt3(mdc,spt[0],r3,angle,axw,pw,mtr->pcr);	
		break;
	case 3:
		ShowMPt4(mdc,spt[0],r3,angle,axw,pw,mtr->pcr);	
		break;
	case 4:
		ShowMPt5(mdc,spt[0],r3,angle,axw,pw,mtr->pcr);
		break;
	}
}

//显示meter2
void BASE0::ShowMeter2(HDC hdc, int dx, int dy)
{
	char p[100];
	CRect rt,rt1;
	LOGFONT lf;
	CPoint pt1,pt2,pt3;
	N_METER2 *mtr;
	int i,j,n,h,w,x1,x2,h1,h2,h3,h4;
	double a,xl,vl,bx,bl,val,v1,v2,vmax,vmin;
	mtr=(N_METER2 *)buf;
	mtr->numdot=mtr->numdot>7 ? 7:mtr->numdot;
	rt=CreateDrawRect(4,mtr->pt,dx,dy);
	a=mtr->Vmax-mtr->Vmin;
	if(a<=0) return;
	h=rt.Height();
	switch(mtr->shownum)
	{
	case 0: //没有数字
		w=rt.Width()-1;
		x1=rt.left;
		h2=rt.top;
		h3=rt.top+h/2;
		h4=rt.bottom;
		break;
	case 1: //数字在上
		w=rt.Width()-h-1;
		x1=rt.left+h/2;
		h1=rt.top;
		h2=rt.top+h/2;
		h3=rt.top+h*3/4;
		h4=rt.bottom;
		break;
	case 2: //数字再下
		w=rt.Width()-h-1;
		x1=rt.left+h/2;
		h1=rt.bottom;
		h2=rt.bottom-h/2;
		h3=rt.bottom-h*2/3;
		h4=rt.top;
		break;
	}
	if(w==0) return;
	mtr->scale=mtr->scale<2 ? 2:mtr->scale;
	n=mtr->scale;
	xl=(double)w/(double)n;
	vl=(double)a/(double)n;
	bl=(double)w/a;
	

	lf=cobj.font;
	strcpy(lf.lfFaceName,"Airal");
	lf.lfHeight=(int)(h/2);
	lf.lfWidth=lf.lfHeight/2;

	if(mtr->scales>0) bx=xl/mtr->scales;
	//画告警刻度背景
	mtr->alarm=mtr->alarm>2 ? 2:mtr->alarm;
	vmax=mtr->Vmax;
	vmin=mtr->Vmin;
	for(i=0;i<mtr->alarm;i++)
	{
		v1=mtr->val[i*2];
		v2=mtr->val[i*2+1];
		if(v1>vmax) continue;
		if(v1<vmin) v1=vmin;
		if(v2<vmin) continue;
		if(v2>vmax) v2=vmax;
		if(v2<v1) continue;
		pt1.x=x1+(int)(bl*(v1-mtr->Vmin));
		pt2.x=x1+(int)(bl*(v2-mtr->Vmin));
		pt1.y=h3;
		pt2.y=h4;
		GLRectc(hdc,CRect(pt1,pt2),mtr->cr[i],mtr->cr[i],0);
	}
	//画刻度
	pt1.y=rt.top+h1;
	pt2.y=rt.bottom;
	pt3.y=rt.top+h2;
	if(mtr->showbl==1) GLLine(hdc,x1,h4,x1+w+1,h4,mtr->scr);
	for(i=0;i<=n;i++)
	{
		pt1.x=(int)(x1+i*xl);
		pt2.x=pt1.x;
		GLLine(hdc,pt1.x,h4,pt2.x,h2,mtr->scr);
		if(i<n)
		{
			for(j=1;j<mtr->scales;j++)
			{
			x2=pt1.x+(int)(j*bx);
			GLLine(hdc,x2,h4,x2,h3,mtr->scr);
			}
		}
		//显示数字
		if(mtr->shownum>0)
		{
			rt1.left=pt1.x-(int)(xl/2); rt1.right=pt1.x+(int)(xl/2);
			rt1.top=h1;
			rt1.bottom=h2;
			val=mtr->Vmin+i*vl;
			GetDoubleStr(val,p,mtr->numdot);
			GLDDrawText(hdc,&rt1,&lf,p,mtr->scr,0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
	}
	//画指针
	x2=x1+w/2;
	GLRectc(hdc,CRect(x2-1,h2,x2+2,h4),mtr->pcr,mtr->pcr,0);
}

//垂直刻度表
void BASE0::ShowMeter3(HDC hdc, int dx, int dy)
{
	char p[100];
	CRect rt,rt1;
	LOGFONT lf;
	CPoint pt1,pt2,pt3;
	N_METER3 *mtr;
	int i,j,n,h,w,y1,y2,w1,w2,w3,w4,fh;
	double a,yl,vl,bx,bl,val,v1,v2,vmax,vmin;
	mtr=(N_METER3 *)buf;
	mtr->numdot=mtr->numdot>7 ? 7:mtr->numdot;
	rt=CreateDrawRect(4,mtr->pt,dx,dy);
	a=mtr->Vmax-mtr->Vmin;
	if(a<=0) return;
	w=rt.Width();
	switch(mtr->shownum)
	{
	case 0: //没有数字
		h=rt.Height()-1;
		y1=rt.top;
		w2=rt.left;
		w3=rt.left+w/2;
		w4=rt.right;
		break;
	case 1: //数字在左
		h=rt.Height()-20;
		y1=rt.top+10;
		w1=rt.left;
		w2=rt.left+w*3/4;
		w3=rt.left+w*7/8;
		w4=rt.right;
		break;
	case 2: //数字在右
		h=rt.Height()-20;
		y1=rt.top+10;
		w1=rt.right;
		w2=rt.right-w*3/4;
		w3=rt.right-w*7/8;
		w4=rt.left;
		break;
	}
	if(w==0) return;
	mtr->scale=mtr->scale<2 ? 2:mtr->scale;
	n=mtr->scale;
	yl=(double)h/(double)n;
	vl=(double)a/(double)n;
	bl=(double)h/a;
	
	lf=cobj.font;
	strcpy(lf.lfFaceName,"Airal");
	lf.lfWidth=(w*3/20);
	fh=lf.lfWidth*2;
	fh=fh>(int)yl ? (int)yl:fh;
	lf.lfHeight=fh;

	if(mtr->scales>0) bx=yl/mtr->scales;
	//画告警刻度背景
	mtr->alarm=mtr->alarm>2 ? 2:mtr->alarm;
	vmax=mtr->Vmax;
	vmin=mtr->Vmin;
	for(i=0;i<mtr->alarm;i++)
	{
		v1=mtr->val[i*2];
		v2=mtr->val[i*2+1];
		if(v1>vmax) continue;
		if(v1<vmin) v1=vmin;
		if(v2<vmin) continue;
		if(v2>vmax) v2=vmax;
		if(v2<v1) continue;
		pt1.y=y1+(int)(bl*(v1-mtr->Vmin));
		pt2.y=y1+(int)(bl*(v2-mtr->Vmin));
		pt1.x=w3;
		pt2.x=w4;
		GLRectc(hdc,CRect(pt1,pt2),mtr->cr[i],mtr->cr[i],0);
	}
	//画刻度
	if(mtr->showbl==1) GLLine(hdc,w4,y1,w4,y1+h+1,mtr->scr);
	for(i=0;i<=n;i++)
	{
		pt1.y=(int)(y1+i*yl);
		GLLine(hdc,w4,pt1.y,w2,pt1.y,mtr->scr);
		if(i<n)
		{
			for(j=1;j<mtr->scales;j++)
			{
			y2=pt1.y+(int)(j*bx);
			GLLine(hdc,w4,y2,w3,y2,mtr->scr);
			}
		}
		//显示数字
		if(mtr->shownum>0)
		{
			rt1.left=w1; rt1.right=w2;
			rt1.top=pt1.y-fh/2;
			rt1.bottom=pt1.y+fh/2;
			rt1.NormalizeRect();
			val=mtr->Vmin+i*vl;
			GetDoubleStr(val,p,mtr->numdot);
			if(mtr->shownum==1) GLDDrawText(hdc,&rt1,&lf,p,mtr->scr,0,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
			else GLDDrawText(hdc,&rt1,&lf,p,mtr->scr,0,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
		}
	}
	//画指针
	y2=y1+h/2;
	GLRectc(hdc,CRect(w2,y2-1,w4,y2+2),mtr->pcr,mtr->pcr,0);
}

//显示数码仪表
void BASE0::ShowMeter4(HDC hdc, int dx, int dy)
{
	char p[100];
	DWORD color;
	CRect rt,rt1;
	LOGFONT lf;
	int i,n,m,x1,x2;
	double xl;
	N_METER4 *mtr;
	mtr=(N_METER4 *)buf;
	rt=CreateDrawRect(4,mtr->pt,dx,dy);
	mtr->num=mtr->num>10 ? 10:mtr->num;
	mtr->num=mtr->num<1 ? 1:mtr->num;
	mtr->numdot=mtr->numdot>4 ? 4:mtr->numdot;
	if(mtr->numdot>=mtr->num) mtr->numdot=0;
	xl=(double)rt.Width()/(double)mtr->num;
	lf=cobj.font;
	strcpy(lf.lfFaceName,"Airal");
	lf.lfWidth=(int)(xl*0.5);
	lf.lfHeight=(int)(rt.Height()*0.8);
	GLDDraw3DRect(hdc,rt,mtr->bcr,mtr->bcr);
	n=mtr->numdot;
	m=mtr->num-n;
	x1=rt.left;
	rt1.top=rt.top;
	rt1.bottom=rt.bottom;
	for(i=1;i<=mtr->num;i++)
	{
		x2=rt.left+(int)(i*xl);
		if(i!=mtr->num) GLLine(hdc,x2,rt.top,x2,rt.bottom,mtr->bcr);
		rt1.left=x1;
		rt1.right=x2;
		sprintf(p,"%d",i);
		color=i>m ? mtr->ncr[1]:mtr->ncr[0];
		GLDDrawText(hdc,&rt1,&lf,p,color,0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		x1=x2;
	}
}
//显示路径
void BASE0::ShowPath(HDC hdc,int dx, int dy,int pm)
{
	DWORD color;
	HPEN pen,oldpen;
	int i,tpsum;
	POINT *tp;
	CDRect rt;
	N_PATH *pth;
	pth=(N_PATH*)buf;
	tpsum=pth->ptsum;
	tp=new POINT[tpsum+1];
	for(i=0;i<tpsum;i++)
	 {
		tp[i].x=(int)(pth->pt[i].x*cobj.curzoom+dx);
		tp[i].y=(int)(pth->pt[i].y*cobj.curzoom+dy);
	 };
	if(pm==0) color=pth->color;else color=0;
	pen=CreatePen(PS_DOT,1,color);
	oldpen=(HPEN)::SelectObject(hdc,pen);
	SetBkMode(hdc,TRANSPARENT);
	Polyline(hdc,tp,tpsum);
	SelectObject(hdc,oldpen);
	SetBkMode(hdc,OPAQUE);
	DeleteObject(pen);
	delete tp;
}

//显示模擬量
void BASE0::ShowAnl(HDC hdc, int dx, int dy,int pm)
{
	CRect rt;
	LOGFONT font;
	N_ANL *anl;
	anl=(N_ANL *)buf;
	rt=CreateDrawRect(4,anl->pt,dx,dy);
	font=anl->lf;
	font.lfHeight=(int)(font.lfHeight*cobj.curzoom);
	font.lfWidth=(int)(font.lfWidth*cobj.curzoom);
	font.lfEscapement=anl->direction==0 ? 0:900;
	ShowAnalog(hdc,rt,&font,anl,pm);
}

//显示模擬量
void BASE0::ShowAnl(CDIB&mdc, int dx, int dy)
{
	CRect rt;
	LOGFONT font;
	N_ANL *anl;
	anl=(N_ANL *)buf;
	rt=CreateDrawRect(4,anl->pt,dx,dy);
	font=anl->lf;
	font.lfHeight=(int)(font.lfHeight*cobj.curzoom);
	font.lfWidth=(int)(font.lfWidth*cobj.curzoom);
	font.lfEscapement=anl->direction==0 ? 0:900;
	ShowAnalog(mdc.m_hDC,rt,&font,anl,0);

	//标志显示
	bool s=false;
	if(cobj.nocdev){
		if(anl->did<0) s=true;
	}
	if(s){  //显示标志矩形
		mdc.CDrawGlass(rt,0xff,0,1,100);
	}

}

//显示系统饼图
void BASE0::ShowSysPie(HDC hdc, int dx, int dy)
{
	int num;
	double vp[4];
	CRect rt;
	CRect rt1;
	N_SYSPIE *pie;
	pie=(N_SYSPIE*)buf;
	rt=CreateDrawRect(4,pie->pt,dx,dy);
	if(pie->type==0)
	{
		vp[0]=0.3;
		vp[1]=0.25;
		vp[2]=0.45;
		num=3;

	}else{
		vp[0]=0.3;
		vp[1]=0.7;
		num=2;
	}
	DrawMPie(hdc,rt,pie->color,vp,num,pie->lf,pie->fcolor,dx,dy);
}

//显示棒图
void BASE0::ShowBar(HDC hdc, int dx, int dy)
{
	CRect rt;
	N_BAR *bar;
	bar=(N_BAR *)buf;
	rt=CreateDrawRect(4,bar->pt,dx,dy);
	DrawBar(hdc,rt,bar[0]);
}

//显示饼图
void BASE0::ShowPie(HDC hdc, int dx, int dy)
{
	char p[100];
	LOGFONT font;
	CDRect rt;
	CRect rt1;
	DWORD c1,c2;
	double a,b;
	//int n;
	N_PIE *pie;
	pie=(N_PIE*)buf;
	b=0.9;
	a=b>1 ? 1:b;
	c1=pie->color[0];
	c2=pie->color[1];
	rt=CreateDrawNRt(4,pie->pt,cobj.curzoom);
	//n=GetPctPieCirclePt(npt,rt,a,0);
	if(a==1) c1=c2;
	DrawPie(hdc,rt,c2,c1,c1,b,dx,dy);
	//DrawPie(hdc,rt,0xff,0xffffff,0x0,b,dx,dy);
	//显示百分饼图文字
	font=pie->lf;
	font.lfHeight=(long)(font.lfHeight*cobj.curzoom);
	 font.lfWidth=(long)(font.lfWidth*cobj.curzoom);
	sprintf(p,"%d%%",(int)(a*100));
	rt.GetRECT(rt1);
	rt1.OffsetRect(dx,dy);
	GLDDrawText(hdc,&rt1,&font,p,pie->fcolor,0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

//显示日期
void BASE0::ShowDate(HDC hdc, int dx, int dy,int pm)
{
	int i;
	CRect rt;
	DWORD c1;
	LOGFONT font;
	char p[100],mn[10],da[10];
	N_DATE *date;
	date=(N_DATE *)buf;
	rt=CreateDrawRect(4,date->pt,dx,dy);
	GetDtStr(date->tm.GetMonth(),mn);
	GetDtStr(date->tm.GetDay(),da);
	if(pm==0) c1=date->outcolor;else c1=0;
	if(date->tran==0) GLRectc(hdc,rt,date->bcolor,date->bcolor,0);
	switch(date->outline){
	case 1:	GLDDraw3DRect(hdc,rt,c1,c1); break;
	case 2:	GLDDraw3DRect(hdc,rt,c1,0xffffff);  break;
	case 3: GLDDraw3DRect(hdc,rt,0xffffff,c1);	break;
	};
	switch(date->fmt){
	case 1:	sprintf(p,"%s/%s/%d",mn,da,date->tm.GetYear());  break;
	case 2:	sprintf(p,"%d年%s月%s日",date->tm.GetYear(),mn,da);break;
	case 3: 
		i=date->tm.GetDayOfWeek();
		i=i-1;
		i=i<0 ? 0:i;
		i=i>6 ? 6:i;
		sprintf(p,"星期%s",wk[i]); 
		break;
	  default:
		sprintf(p,"%d-%s-%s",date->tm.GetYear(),mn,da);
	};
	font=date->font;
	font.lfHeight=(int)(font.lfHeight*cobj.curzoom);
	font.lfWidth=(int)(font.lfWidth*cobj.curzoom);
	rt.left++;
	rt.top++;
	rt.right-=3;
	rt.bottom-=3;
	if(pm==0) c1=date->fcolor;else c1=0;
	GLDDrawText(hdc,&rt,&font,p,c1,date->style,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

//显示日期
void BASE0::ShowTime(HDC hdc, int dx, int dy,int pm)
{
	CRect rt;
	DWORD c1;
	LOGFONT font;
	char p[100],hr[10],min[10],sec[10];
	N_TIME *date;
	date=(N_TIME *)buf;
	rt=CreateDrawRect(4,date->pt,dx,dy);
	GetDtStr(date->tm.GetHour(),hr);
	GetDtStr(date->tm.GetMinute(),min);
	GetDtStr(date->tm.GetSecond(),sec);
	if(date->tran==0) GLRectc(hdc,rt,date->bcolor,date->bcolor,0);
	if(pm==0) c1=date->outcolor;else c1=0;
	switch(date->outline){
	case 1:	GLDDraw3DRect(hdc,rt,c1,c1); break;
	case 2:	GLDDraw3DRect(hdc,rt,c1,0xffffff);  break;
	case 3: GLDDraw3DRect(hdc,rt,0xffffff,c1);	break;
	};
	switch(date->fmt){
	case 1:sprintf(p,"%s:%s",hr,min);			break;
	case 2:sprintf(p,"%s时%s分%s秒",hr,min,sec);break;
	case 3:sprintf(p,"%s点%s分%s秒",hr,min,sec);break;
	case 4:strcpy(p,"02分02秒");				break;	
	default:
		sprintf(p,"%s:%s:%s",hr,min,sec);
	};
	font=date->font;
	font.lfHeight=(int)(font.lfHeight*cobj.curzoom);
	font.lfWidth=(int)(font.lfWidth*cobj.curzoom);
	rt.left++;
	rt.top++;
	rt.right-=3;
	rt.bottom-=3;
	if(pm==0) c1=date->fcolor;else c1=0;
	GLDDrawText(hdc,&rt,&font,p,c1,date->style,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
}

//显示动画
void BASE0::ShowGifAnl(HDC hdc, int dx, int dy)
{
	CRect rt;
	N_GIFAML *ga;
	ga=(N_GIFAML *)buf;
	rt=CreateDrawRect(4,ga->pt,dx,dy);
	if(ga->rec>=MAXGIF) return;
	if(cobj.gal[ga->rec].dc.m_hDC!=NULL) 
		cobj.gal[ga->rec].dc.Show(hdc,rt.left,rt.top,rt.Width(),rt.Height());
	else GLDDraw3DRect(hdc,rt,0xc0c0c0,0xc0c0c0); 
}

//显示滚动文本
void BASE0::ShowScrText(CDIB &mdc, int dx, int dy)
{
	CDRect art;
	CRect rt,rt1;
	LOGFONT font;
	N_SRLTEXT *lp;
	lp=(N_SRLTEXT *)buf;
	rt=CreateDrawRect(4,lp->pt,dx,dy);
	font=lp->lf;
	font.lfHeight=(int)(font.lfHeight*cobj.curzoom);
	font.lfWidth=(int)(font.lfWidth*cobj.curzoom);
	DWORD align=DT_LEFT;
	if(lp->align==1) align=DT_CENTER;
	if(lp->align==2) align=DT_RIGHT;
	if(lp->glass==1) mdc.CDrawGlass(rt,lp->gcolor,lp->fcolor,0,lp->depth);
	rt1=rt;
	rt.left+=5;
	rt.top+=5;
	rt.right-=5;
	rt.bottom-=5;
	mdc.CTextOut(lp->text,rt,&lp->lf,lp->tcolor,lp->tstyle,align);
	if(lp->outline==1) mdc.CDraw3DRect(rt1,lp->fcolor,lp->fcolor);
}

//显示滚动文本
void BASE0::ShowScrText(HDC hdc, int dx, int dy,int pm)
{
	CDRect art;
	DWORD c1;
	CRect rt;
	LOGFONT font;
	N_SRLTEXT *lp;
	lp=(N_SRLTEXT *)buf;
	rt=CreateDrawRect(4,lp->pt,dx,dy);
	font=lp->lf;
	font.lfHeight=(int)(font.lfHeight*cobj.curzoom);
	font.lfWidth=(int)(font.lfWidth*cobj.curzoom);
	DWORD align=DT_LEFT;
	if(lp->align==1) align=DT_CENTER;
	if(lp->align==2) align=DT_RIGHT;
	rt.left+=5;
	rt.top+=5;
	rt.right-=5;
	rt.bottom-=5;
	if(pm==0) c1=lp->tcolor;else c1=0;
	GLDDrawText(hdc,&rt,&font,lp->text,c1,lp->tstyle,lp->align);
}


//显示滚动文本
void BASE0::ShowPush(CDIB&mdc, int dx, int dy)
{
	CRect rt;
	int type;
	LOGFONT font;
	N_PUSH *lp;
	lp=(N_PUSH *)buf;
	rt=CreateDrawRect(4,lp->pt,dx,dy);
	font=lp->lf;
	font.lfHeight=(int)(font.lfHeight*cobj.curzoom);
	font.lfWidth=(int)(font.lfWidth*cobj.curzoom);
	type=lp->style;
    switch(type){
	case 0:
		BDrawButton(mdc.m_hDC,rt,lp->title,&font,lp->down,1);
	  break;
	case 1:
	  if(lp->edit==1) mdc.CDraw3DRect(rt,0xc0c0c0,0xc0c0c0);
	  break;
	case 2:
	  if(lp->down==1||lp->edit==1){
	   mdc.CDrawGlass(rt,0xff0000,0,0,30);
	   mdc.CDraw3DRect(rt,0,0xffffff);
		}
	  break;
	case 3:
	  if(lp->down==1||lp->edit==1){
	   mdc.CDrawGlass(rt,0xff,0,0,30);
	   mdc.CDraw3DRect(rt,0xffffff,0);
		}
	 break;
	case 4:
		if(lp->down==0){
	     mdc.CTextOut(lp->title,rt,&font,lp->color1,lp->fstyle,DT_CENTER|DT_VCENTER|DT_SINGLELINE) ;
		}else{
		 mdc.CTextOut(lp->title,rt,&font,lp->color2,lp->fstyle,DT_CENTER|DT_VCENTER|DT_SINGLELINE) ;
		}
	  break;
	};
		
}

//显示按钮
void BASE0::ShowPush(HDC hdc, int dx, int dy)
{
	CRect rt;
	int type;
	LOGFONT font;
	N_PUSH *lp;
	lp=(N_PUSH *)buf;
	rt=CreateDrawRect(4,lp->pt,dx,dy);
	font=lp->lf;
	font.lfHeight=(int)(font.lfHeight*cobj.curzoom);
	font.lfWidth=(int)(font.lfWidth*cobj.curzoom);
	type=lp->style;
    switch(type){
	case 0:
		BDrawButton(hdc,rt,lp->title,&font,lp->down,1);
	  break;
	case 1:
	  if(lp->edit==1) GLDDraw3DRect(hdc,rt,0xc0c0c0,0xc0c0c0,1);
	  break;
	case 2:
	  if(lp->down==1||lp->edit==1)  GLDDraw3DRect(hdc,rt,0,0xffffff);
	   break;
	case 3:
	  if(lp->down==1||lp->edit==1) GLDDraw3DRect(hdc,rt,0xffffff,0);
	  break;
	case 4:
		if(lp->down==0){
		 GLDDrawText(hdc,&rt,&font,lp->title,lp->color1,lp->fstyle,
			 DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	    }else{
		 GLDDrawText(hdc,&rt,&font,lp->title,lp->color2,lp->fstyle,
			 DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}
	  break;
	};
}



//显示编辑态的自助控件
void BASE0::ShowSlfCtl(HDC hdc, int dx, int dy)
{
	CRect rt;
	N_SELFCTL *sft;
	sft=(N_SELFCTL *)buf;
	if(testflag==1) return;;
	rt=CreateDrawRect(4,sft->pt,dx,dy);
	if(sft->hinst!=NULL){
	 if(sft->DfDrawDemo!=NULL) sft->DfDrawDemo(hdc,rt,sft->style,sft->lkbuf);
	}else
	{
	  GLRectc(hdc,rt,0xffffff,0xffffff,0);
	  GLDDraw3DRect(hdc,rt,0,0);
	  rt.left+=3;
	  rt.top+=3;
	  rt.right-=3;
	  rt.bottom-=3;
	  GLDDraw3DRect(hdc,rt,0,0);
	  rt.left+=10;
	  rt.top+=10;
	  GLDDrawText(hdc,&rt,&cobj.sysfont,"该自助控制无效",0,0);
	 };
}
//显示水库对象
void BASE0::ShowReservoir(HDC hdc,int dx, int dy,int pm)
{
	DWORD c1;
	int tpsum;
	N_RESERVOIR *rev;
	rev=(N_RESERVOIR*)buf;
	tpsum=rev->ptsum;
	tpsum=rev->ptsum>1000 ? 1000:rev->ptsum;
	PointActToScr(rev->pt,mpt,tpsum,dx,dy,cobj.curzoom);
	c1=pm==0 ? rev->lcolor:0;
	DrawPoly(hdc,mpt,tpsum,c1,rev->ncolor,1,1,1);
}


//显示水库对象
void BASE0::ShowReservoir(CDIB&mdc,int dx, int dy)
{
	int tpsum;        
	N_RESERVOIR *rev;
	rev=(N_RESERVOIR*)buf;
	tpsum=rev->ptsum>1000 ? 1000:rev->ptsum;
	PointActToScr(rev->pt,npt,tpsum,dx,dy,cobj.curzoom);
	mdc.CDrawPoly(npt,tpsum,rev->color,rev->ncolor,1,1);
}


//显示连接线对象
void BASE0::ShowConLine(HDC hdc,int dx, int dy,int pm)
{
	DWORD color;
	int i,v,tpsum;
	double w;
	POINT *tp;
	CDRect rt;
	CRect rt1;
	N_CONLINE *cnl;
	cnl=(N_CONLINE*)buf;
	tpsum=cnl->ptsum;
	tp=new POINT[tpsum+1];
	for(i=0;i<tpsum;i++)
	 {
		tp[i].x=(int)((double)(cnl->pt[i].x*cobj.curzoom))+dx;
		tp[i].y=(int)((double)(cnl->pt[i].y*cobj.curzoom))+dy;
	 };
	if(cnl->autozoom==1) w=(double)(cnl->width*cobj.curzoom);
	else w=cnl->width;
	w=w>255 ? 255:w;
	w=w<1 ? 1:w;
	v=cnl->vl;
	v=v>20 ? 0:v;
	if(cnl->conobj==0) color=0x7f7f7f;else color=cobj.vcolor[v];
	if(pm!=0) color=0;
	GLDrawDbx(hdc,tpsum,tp,(BYTE)w,color);
	if(cnl->solder1==1&&cobj.showsite==1){
		rt.left=tp[0].x-2*w;rt.right=tp[0].x+2*w+1;
		rt.top=tp[0].y-2*w;rt.bottom=tp[0].y+2*w;
		rt.GetRECT(rt1);
		GLEllipsec(hdc,rt1,color,color,0);
		}
	if(cnl->solder2==1&&cobj.showsite==1){
		rt.left=tp[tpsum-1].x-2*w;rt.right=tp[tpsum-1].x+2*w+1;
		rt.top=tp[tpsum-1].y-2*w;rt.bottom=tp[tpsum-1].y+2*w;
		rt.GetRECT(rt1);
		GLEllipsec(hdc,rt1,color,color,0);
		}
	delete tp;
}

//显示连接线对象
void BASE0::ShowConLine(CDIB&mdc,int dx, int dy)
{
	DWORD color;
	int i,v,tpsum;
	double w;
	POINT *tp;
	CDRect rt;
	CRect rt1;
	N_CONLINE *cnl;
	cnl=(N_CONLINE*)buf;
	tpsum=cnl->ptsum;
	tp=new POINT[tpsum+1];
	for(i=0;i<tpsum;i++)
	 {
		tp[i].x=(int)((double)(cnl->pt[i].x*cobj.curzoom))+dx;
		tp[i].y=(int)((double)(cnl->pt[i].y*cobj.curzoom))+dy;
	 };
	if(cnl->autozoom==1) w=(double)(cnl->width*cobj.curzoom);
	else w=cnl->width;
	w=w>255 ? 255:w;
	w=w<1 ? 1:w;
	v=cnl->vl;
	v=v>20 ? 0:v;
	if(cnl->conobj==0) color=0x7f7f7f;else color=cobj.vcolor[v];
	mdc.CDrawDbx(tp,tpsum,color);
	if(cnl->solder1==1&&cobj.showsite==1){
		rt.left=tp[0].x-2*w;rt.right=tp[0].x+2*w+1;
		rt.top=tp[0].y-2*w;rt.bottom=tp[0].y+2*w;
		rt.GetRECT(rt1);
		mdc.CEllipsec(rt1,color);
		}
	if(cnl->solder2==1&&cobj.showsite==1){
		rt.left=tp[tpsum-1].x-2*w;rt.right=tp[tpsum-1].x+2*w+1;
		rt.top=tp[tpsum-1].y-2*w;rt.bottom=tp[tpsum-1].y+2*w;
		rt.GetRECT(rt1);
		mdc.CEllipsec(rt1,color);
		}
	delete tp;
}



void BASE0::ShowFlow(HDC hdc,int dx, int dy,int pm)
{
	DWORD color,c1,c2;
	int i,v,tpsum;
	POINT *tp;
	CDRect rt;
	CRect rt1;
	N_FLOW *flw;
	flw=(N_FLOW*)buf;
	tpsum=flw->ptsum;
	tp=new POINT[tpsum+1];
	for(i=0;i<tpsum;i++)
	 {
		tp[i].x=(int)((double)(flw->pt[i].x*cobj.curzoom))+dx;
		tp[i].y=(int)((double)(flw->pt[i].y*cobj.curzoom))+dy;
	 };
	v=flw->vl;
	v=v>20 ? 0:v;
	if(pm==0){
		color=cobj.vcolor[v];
		c1=flw->color1;
		c2=flw->color2;
	}else{
		color=0;
		c1=0;
		c2=0;
	}
	GLDrawDbx(hdc,tpsum,tp,1,color);
	delete tp;
}

void BASE0::ShowFlow(CDIB&mdc,int dx, int dy)
{
	DWORD color;
	int i,v,tpsum;
	POINT *tp;
	CDRect rt;
	CRect rt1;
	N_FLOW *flw;
	flw=(N_FLOW*)buf;
	tpsum=flw->ptsum;
	tp=new POINT[tpsum+1];
	for(i=0;i<tpsum;i++)
	 {
		tp[i].x=(int)((double)(flw->pt[i].x*cobj.curzoom))+dx;
		tp[i].y=(int)((double)(flw->pt[i].y*cobj.curzoom))+dy;
	 };
	v=flw->vl;
	v=v>20 ? 0:v;
	color=cobj.vcolor[v];

	if(flw->linewidth==0) mdc.CDrawDbx(tp,tpsum,color); 
	else mdc.CDrawDbxW(tp,tpsum,color,flw->linewidth-1); 
	//显示标志
	bool s=false;
	if(cobj.nocdev){
		if(flw->did<0) s=true;
	}
	if(s){  //显示标志矩形
		mdc.CDrawDbx(tp,tpsum,0xff00);
	}
	delete tp;
}

void BASE0::ShowZone(HDC hdc,int dx, int dy,int pm)
{
	CDRect drt;
	CRect rt;
	DPOINT cpt;
	SIZE sz;
	LOGFONT lf;
	DWORD color;
	int tpsum;
	N_ZONE *zn;
	zn=(N_ZONE*)buf;
	tpsum=zn->ptsum;
	tpsum=zn->ptsum>1000 ? 1000:zn->ptsum;
	PointActToScr(zn->pt,mpt,tpsum,dx,dy,cobj.curzoom);
	color=pm==0 ? zn->lcolor:0;
	DrawPoly(hdc,mpt,tpsum,color,0xf0ffff,0,1,1);
	if(strlen(zn->zone_name)==0) return;
	drt=CreateNRt(zn->ptsum,zn->pt);
	cpt=drt.CenterPoint();
	lf=zn->lf;
	sz=GLDGetTextSize(hdc,&lf,zn->zone_name);
	drt.left=cpt.x-sz.cx/2;
	drt.right=cpt.x+sz.cx/2+2;
	drt.top=cpt.y-sz.cy/2;
	drt.bottom=cpt.y+sz.cy/2+2;
	drt.ActRtToScr(cobj.curzoom);
	drt.Offset(dx,dy);
	drt.GetRECT(rt);
	lf.lfHeight=(long)(lf.lfHeight*cobj.curzoom);
	lf.lfWidth=(long)(lf.lfWidth*cobj.curzoom);
	GLDDrawText(hdc,&rt,&lf,zn->zone_name,zn->fcolor,0,DT_LEFT);
}

void BASE0::ShowZone(CDIB&mdc,int dx, int dy)
{
	CDRect drt;
	CRect rt;
	DPOINT cpt;
	SIZE sz;
	LOGFONT lf;
	int tpsum;
	N_ZONE *zn;
	zn=(N_ZONE*)buf;
	tpsum=zn->ptsum>1000 ? 1000:zn->ptsum;
	PointActToScr(zn->pt,npt,tpsum,dx,dy,cobj.curzoom);
	mdc.CDrawPoly(npt,tpsum,zn->lcolor,0xf0ffff,0,1);
	if(strlen(zn->zone_name)==0) return;
	drt=CreateNRt(zn->ptsum,zn->pt);
	cpt=drt.CenterPoint();
	lf=zn->lf;
	sz=GLDGetTextSize(mdc.m_hDC,&lf,zn->zone_name);
	drt.left=cpt.x-sz.cx/2;
	drt.right=cpt.x+sz.cx/2+2;
	drt.top=cpt.y-sz.cy/2;
	drt.bottom=cpt.y+sz.cy/2+2;
	drt.ActRtToScr(cobj.curzoom);
	drt.Offset(dx,dy);
	drt.GetRECT(rt);
	lf.lfHeight=(long)(lf.lfHeight*cobj.curzoom);
	lf.lfWidth=(long)(lf.lfWidth*cobj.curzoom);
	GLDDrawText(mdc.m_hDC,&rt,&lf,zn->zone_name,zn->fcolor,0,DT_LEFT);
}


//显示棒图
void BASE0::ShowBus(HDC hdc, int dx, int dy,int pm)
{
	int i,v;
	int r,g,b,r1,g1,b1,r2,g2,b2;
	DWORD color,c1,c2;
	CRect rt;
	N_BUS *bus;
	bus=(N_BUS *)buf;
	rt=CreateDrawRect(4,bus->pt,dx,dy);
	v=bus->vl;
	v=v>20 ? 0:v;
	color=cobj.vcolor[v];

	if(pm!=0) color=0;
	rt.NormalizeRect();
	if(rt.Width()<2||rt.Height()<2){
		GLRectc(hdc,rt,color,color,0);
		return;
		 }
	switch(bus->type){
	 case 0:
		 GLRectc(hdc,rt,color,color,0);
		 break;	
	 case 1:		 
		 GLRectc(hdc,rt,color,color,4);
		 r=GetRValue(color);
		 g=GetGValue(color);
		 b=GetBValue(color);
		 r1=r+96;
		 b1=b+96;
		 g1=g+96;
		 r1=r1>255 ? 255:r1;
		 g1=g1>255 ? 255:g1;
		 b1=b1>255 ? 255:b1;
		 r2=r1/3;
		 g2=g1/3;
		 b2=b1/3;
		 c1=RGB(r1,g1,b1);
		 c2=RGB(r2,g2,b2);
		 GLDDraw3DRect(hdc,rt,c1,c2);
		 break;
	 case 2:
		 GLEllipsec(hdc,rt,color,color,0);
		 GLCircle(hdc,rt,1,0);
		 break;
	 case 3:
		 i=cobj.GetEGPRecNo(bus->eid);
		 PreBusEGPEx(hdc,i,0,dx,dy,pm);
		 break;
	};
}


//显示棒图
void BASE0::ShowBus(CDIB&mdc, int dx, int dy)
{
	int i,v;
	int r,g,b,r1,g1,b1,r2,g2,b2;
	DWORD color,c1,c2;
	CRect rt;
	N_BUS *bus;
	bus=(N_BUS *)buf;
	rt=CreateDrawRect(4,bus->pt,dx,dy);
	v=bus->vl;
	v=v>20 ? 0:v;
	color=cobj.vcolor[v];
	rt.NormalizeRect();
	if(rt.Width()<2||rt.Height()<2){
		GLRectc(mdc.m_hDC,rt,color,color,0);
		return;
		 }
	switch(bus->type){
	 case 0:
		 GLRectc(mdc.m_hDC,rt,color,color,0);
		 break;	
	 case 1:		 
		 GLRectc(mdc.m_hDC,rt,color,color,5);
		 r=GetRValue(color);
		 g=GetGValue(color);
		 b=GetBValue(color);
		 r1=r+96;
		 b1=b+96;
		 g1=g+96;
		 r1=r1>255 ? 255:r1;
		 g1=g1>255 ? 255:g1;
		 b1=b1>255 ? 255:b1;
		 r2=r/3;
		 g2=g/3;
		 b2=b/3;
		 c1=RGB(r1,g1,b1);
		 c2=RGB(r2,g2,b2);
		 GLDDraw3DRect(mdc.m_hDC,rt,c1,c2);
		 break;
	 case 2:
		 mdc.CEllipsec(rt,color);
		 mdc.CCircle(rt,0);
		 break;
	 case 3:
		 i=cobj.GetEGPRecNo(bus->eid);
		 PreBusEGPEx(mdc,i,0,dx,dy);
		 break;
	};
	//显示标志
	bool s=false;
	if(cobj.nocdev){
		if(bus->did<0) s=true;
	}
	if(s){  //显示标志矩形
		mdc.CDrawGlass(rt,0xff,0,1,100);
	}
}


//显示FLASH对象
void BASE0::ShowFlash(HDC hdc, int dx, int dy,int pm)
{
	char p[100];	
	CRect rt,r;
	N_FLASH *fsh;
	fsh=(N_FLASH *)buf;
	rt=CreateDrawRect(4,fsh->pt,dx,dy);
	rt.NormalizeRect();
	GLRectc(hdc,rt,0xffffff,0xffffff,0);
	sprintf(p,"Flash对象:%s",fsh->fname);
	r=rt;
	r.left+=3;
	r.top+=3;
	r.right-=3;
	r.bottom-=3;
	GLDDrawText(hdc,&r,&cobj.sysfont,p,0,0,DT_LEFT);
	GLDDraw3DRect(hdc,rt,0xffc0c0,0xffc0c0,1);
}

//显示小图标
void BASE0::ShowSpic(CDIB &mdc,int dx, int dy)
{
	int i,w,h,w1,h1;
	N_SPIC *pic;
	CRect rt;
	pic=(N_SPIC*)buf;
	i=cobj.GetPICRecno(pic->picID);
	if(i<0) return;
	rt=CreateDrawRect(4,pic->pt,dx,dy);
	w=cobj.spic[i].img.nWidth;
	h=cobj.spic[i].img.nHeight;
	
	if(pic->zoom==0){
		w1=rt.Width();
		h1=rt.Height();
		cobj.spic[i].img.Show(mdc.m_hDC,rt.left,rt.top,w>w1 ? w1:w,h>h1 ? h1:h);
	}else{
		CMemDC dc;
		dc.Create(w,h);
		dc.FillBG(1);
		cobj.spic[i].img.Show(dc.m_hDC,0,0);
		mdc.StrechImg(dc,rt,0);
 	}
}

//显示小图标
void BASE0::ShowSpic(HDC hdc,int dx, int dy)
{
	int i,w,h,w1,h1;
	N_SPIC *pic;
	CRect rt;
	pic=(N_SPIC*)buf;
	i=cobj.GetPICRecno(pic->picID);
	if(i<0) return;
	rt=CreateDrawRect(4,pic->pt,dx,dy);
	w=cobj.spic[i].img.nWidth;
	h=cobj.spic[i].img.nHeight;
	w1=rt.Width();
	h1=rt.Height();
	cobj.spic[i].img.Show(hdc,rt.left,rt.top,w>w1 ? w1:w,h>h1 ? h1:h);
}

//画2饼图
//c1大填充颜色 c2=小块填充颜色 c3=边缘颜色
void BASE0::DrawPie(HDC hdc,CDRect &rt,DWORD c1,DWORD c2,DWORD c3,double pw,int dx,int dy)
{
	DPOINT  tp[74];
	DPOINT  cpt;
	int i,n,end;
	n=GetCircleAllPt(tp,rt);
	if(n!=72) return;
	memcpy(npt,tp,72*sizeof(DPOINT));
	for(i=0;i<n;i++)
	{
		mpt[i].x=(int)npt[i].x+dx;
		mpt[i].y=(int)npt[i].y+dy;
	}
	DrawPoly(hdc,mpt,n,c3,c1,1,1);
	end=(int)(72*pw);
	if(end<0||end>72) return;
	if(end==0&&pw!=0) end=1;
	if(end!=72&&end!=0&&rt.Width()>3)
	{
		cpt=rt.CenterPoint();
		tp[end].x=cpt.x;
		tp[end].y=cpt.y;
		tp[end+1]=tp[0];
		//DPtToScrPt(tp,mpt,end+2,dx,dy);
		for(i=0;i<end+2;i++)
		{
			mpt[i].x=(int)tp[i].x+dx;
			mpt[i].y=(int)tp[i].y+dy;
		}
		DrawPoly(hdc,mpt,end+2,c3,c2,1,1);
	}
}


void BASE0::DrawMPie(HDC hdc,CRect &rt,DWORD *cr,double *vp,int num,LOGFONT &lf,DWORD fcolor,int dx,int dy)
{
	char p[100];
	CDRect drt;
	CRect rt1;
	LOGFONT font;
	double v;
	CPoint   ipt[74],cpt;
	DPOINT  tp[74];
	int    pt[24];
	int i,j,n,m;
	drt.SetCRect(rt);
	n=GetCircleAllPt(tp,drt);
	if(n!=72) return;
	tp[72]=tp[0];
	for(i=0;i<73;i++)
	{
		mpt[i].x=(int)tp[i].x;
		mpt[i].y=(int)tp[i].y;

	}
	//DrawPoly(hdc,mpt,72,cr[0],cr[num],1,1);
	pt[0]=0;
	v=0;
	for(i=0;i<num;i++)
	{
		v+=vp[i];
		pt[i+1]=(int)(72*v);
		if(pt[i+1]>=72) pt[i+1]=72;
	}
	pt[num+1]=0;
	//画小饼图
	font=lf;
	font.lfHeight=(long)(font.lfHeight*cobj.curzoom);
	font.lfWidth=(long)(font.lfWidth*cobj.curzoom);
	cpt=rt.CenterPoint();
	for(i=0;i<num;i++)
	{
		ipt[0]=cpt;
		m=pt[i+1]-pt[i];
		n=pt[i];
		for(j=0;j<m+1;j++)
		{
			ipt[j+1]=mpt[n+j];
		}
		DrawPoly(hdc,ipt,m+2,cr[0],cr[i+1],1,1);

		//显示百分饼图文字		
		sprintf(p,"%d%%",(int)(vp[i]*100));
		rt1=CreateNRt(m+2,ipt);
		GLDDrawText(hdc,&rt1,&font,p,fcolor,0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
	}
	
}

void BASE0::ShowActObj(HDC hdc,int dx, int dy)
{
	int i,w,h;
	N_ACTOBJ *act;
	CRect rt;
	act=(N_ACTOBJ*)buf;
	rt=CreateDrawRect(4,act->pt,dx,dy);
	i=cobj.GetPICRecno(act->gid);
	if(i<0){
		CDC dc;
	    dc.Attach(hdc);
	    othimg.Draw(&dc,12,CPoint(rt.left,rt.top),ILD_NORMAL);
	    dc.Detach();
		return;
	}
	w=cobj.spic[i].img.nWidth;
	h=cobj.spic[i].img.nHeight;
	w=w>(rt.right-rt.left) ? rt.right-rt.left:w;
	h=h>(rt.bottom-rt.top) ? rt.bottom-rt.top:h;
	cobj.spic[i].img.Show(hdc,rt.left,rt.top,w,h);
}

void BASE0::ShowEleGrp(HDC hdc, int dx, int dy,int pm)
{
	int i,eno;
	N_ELEGRPA *ep;
	ep=(N_ELEGRPA*)buf;
	i=cobj.GetEGPRecNo(ep->egrpid);
	if(i<0) return;
	if(ep->rval[0].enable==1)  eno =ep->rval[0].zt;
	else  eno=ep->showno;	
	eno=eno==0 ? 0:1;
	PreShowEGPEx(hdc,i,eno,dx,dy,pm);
}

void BASE0::ShowEleGrp(CDIB&mdc, int dx, int dy)
{
	int i,eno;
	N_ELEGRPA *ep;
	ep=(N_ELEGRPA*)buf;
	i=cobj.GetEGPRecNo(ep->egrpid);
	if(i<0) return;
	if(ep->rval[0].enable==1)  eno =ep->rval[0].zt;
	else  eno=ep->showno;	
	eno=eno==0 ? 0:1;
	PreShowEGPEx(mdc,i,eno,dx,dy);
}


void BASE0::ShowYb(HDC hdc, int dx, int dy)
{
	int i;
	N_ELEGRPYB *ep;
	ep=(N_ELEGRPYB*)buf;
	i=cobj.GetEGPRecNo(ep->egrpid);
	if(i<0) return;
	PreShowEGPYB(hdc,i,dx,dy);
}

void BASE0::ShowYb(CDIB&mdc, int dx, int dy)
{
	int i;
	N_ELEGRPYB *ep;
	ep=(N_ELEGRPYB*)buf;
	i=cobj.GetEGPRecNo(ep->egrpid);
	if(i<0) return;
	PreShowEGPYB(mdc,i,dx,dy);
}

//根据记录号索引号显示图元组(打印用)
void BASE0::PreShowEGPYB(HDC hdc,int num,int dx,int dy)
{
	BASE0 *bs,bbs;
	N_ELEGRPYB *yb;
	int i,j;
	double xl,yl,w1,w2,h1,h2;
	CDRect rt,rt1,rt2;
	yb=(N_ELEGRPYB*)buf;
	bs=cobj.egp[num].bs1;
	j=cobj.egp[num].bsum1;
	rt1.SetDRECT(cobj.egp[num].rt1);
	if(bs==NULL||j<=0)	return;
	//计算宽高
	rt=CreateNRt(4,yb->pt);
	h1=rt.Height();
	w1=rt.Width();
	//原来的宽高
	w2=rt1.Width();
	h2=rt1.Height();
	if(w2==0||h2==0) return;
	rt2.left=0;		rt2.top=0;
	rt2.right=rt.left;	rt2.bottom=rt.top;
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	for(i=0;i<j;i++){
		if(bs[i].attr.type==12) continue;
		bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.SetSelected();
		bbs.MoveObject2(rt2,xl,yl);
		bbs.SetSObjZM(xl);
		bbs.ShowE(hdc,dx,dy,0);
		bbs.FreeMem();
	}
}

void BASE0::PreShowEGPYB(CDIB&mdc,int num,int dx,int dy)
{
	BASE0 *bs,bbs;
	N_ELEGRPYB *yb;
	int i,j;
	double xl,yl,w1,w2,h1,h2;
	CDRect rt,rt1,rt2;
	yb=(N_ELEGRPYB*)buf;
	bs=cobj.egp[num].bs1;
	j=cobj.egp[num].bsum1;
	rt1.SetDRECT(cobj.egp[num].rt1);
	if(bs==NULL||j<=0)	return;
	//计算宽高
	rt=CreateNRt(4,yb->pt);
	h1=rt.Height();
	w1=rt.Width();
	//原来的宽高
	w2=rt1.Width();
	h2=rt1.Height();
	if(w2==0||h2==0) return;
	rt2.left=0;			rt2.top=0;
	rt2.right=rt.left;	rt2.bottom=rt.top;
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	for(i=0;i<j;i++)
	{
		if(bs[i].attr.type==12) continue;
	   	bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.SetSelected();
		bbs.MoveObject2(rt2,xl,yl);
		bbs.SetSObjZM(xl);
		bbs.ShowE(mdc,dx,dy);
		bbs.FreeMem();
	};
}

//根据记录号索引号显示图元组(打印用)
void BASE0::PreShowEGPEx(HDC hdc,int num,int index,int dx,int dy,int pm)
{
	int type;
	BASE0 *bs,bbs;
	DPOINT *spt;
	DWORD color;
	N_ELEGRPA *el;
	N_ESITE *es;
	int i,j,l,k;
	CRect drt;
	double xl,yl,w1,w2,h1,h2,bl;
	CDRect rt,rt1,rt2;
	el=(N_ELEGRPA*)buf;
	spt=el->pt;
	drt=CreateDrawRect(4,el->pt,0,0);
	
	el->type=cobj.egp[num].type;
	el->subtype=cobj.egp[num].subtype;
	el->sitesum=cobj.egp[num].sitesum;
	switch(index){
	 case 0:
		bs=cobj.egp[num].bs1;
		j=cobj.egp[num].bsum1;
		rt1.SetDRECT(cobj.egp[num].rt1);
		break;
	 case 1:
		bs=cobj.egp[num].bs2;
		j=cobj.egp[num].bsum2;
		rt1.SetDRECT(cobj.egp[num].rt2);
		break;
	 default:return;
	};
	if(bs==NULL||j<=0)	return;
	//计算宽高
	
	rt=CreateNRt(4,el->pt);

	
	h1=rt.Height();
	w1=rt.Width();
	//原来的宽高
	w2=rt1.Width();
	h2=rt1.Height();
	if(w2==0||h2==0) return;
	rt2.left=0;		rt2.top=0;
	rt2.right=rt.left;	rt2.bottom=rt.top;
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	bl=xl>yl ? yl:xl;
	bl=(double)(1/bl);
	k=-1;
	for(i=0;i<j;i++){
	  type=bs[i].attr.type;
	  if(type!=12){ //母板不显示
	   	bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.SetSelected();
		bbs.MoveObject2(rt2,xl,yl);
		if(bl!=0) bbs.SetLineWidth(bl);
		if(el->type==1){
		  l=bs[i].attr.belong;
		  if(l>0){
			l--;
			l=l>2 ? 0:l;
			bbs.SetColor(cobj.vcolor[el->site[l].vl]);
		  }
		if(type==11&&cobj.showsite==1){ //对端子的特殊处理
			  k++;
			  if(k<3){
		       if((el->subtype==7||el->subtype==8)) l=el->site[k].vl;
		       else l=el->site[0].vl;
		       l=l>20 ? 0:l;	
			   color=cobj.vcolor[l];
			   es=(N_ESITE*)bbs.buf;
			   if(el->site[k].id>=0)  es->solder=1;else es->solder=0;
			   es->color=color;
			  }
		  }
		}
		if(type!=11||(type==11&&cobj.showsite==1)) bbs.ShowE(hdc,dx,dy,pm);
		bbs.FreeMem();
	  }
	}
	//标志显示
	bool s=false;
	if(cobj.nocondev){
		for(i=0;i<el->sitesum;i++){
			if(el->site[i].id<0){
				s=true;
				break;
			}
		}
	}
	if(cobj.nocdev){
		if(el->did<0) s=true;
	}
	if(s){  //显示标志矩形
		drt.OffsetRect(dx,dy);
		drt.right++;
		drt.bottom++;
		GLDDraw3DRect(hdc,drt,0xffc0c0,0xffc0c0,1);
	}
}

//根据记录号索引号显示图元组(正常显示专用)
void BASE0::PreShowEGPEx(CDIB&mdc,int num,int index,int dx,int dy)
{
	int type;
	BASE0 *bs,bbs;
	DPOINT *spt;
	DWORD color;
	N_ELEGRPA *el;
	N_ESITE *es;
	int i,j,l,k;
	CRect drt;
	double xl,yl,w1,w2,h1,h2,bl;
	CDRect rt,rt1,rt2;
	el=(N_ELEGRPA*)buf;
	spt=el->pt;
	drt=CreateDrawRect(4,el->pt,0,0);
	el->type=cobj.egp[num].type;
	el->subtype=cobj.egp[num].subtype;
	el->sitesum=cobj.egp[num].sitesum;
	switch(index){
	 case 0:
		bs=cobj.egp[num].bs1;
		j=cobj.egp[num].bsum1;
		rt1.SetDRECT(cobj.egp[num].rt1);
		break;
	 case 1:
		bs=cobj.egp[num].bs2;
		j=cobj.egp[num].bsum2;
		rt1.SetDRECT(cobj.egp[num].rt2);
		break;
	 default:return;
	};
	if(bs==NULL||j<=0)	return;
	//计算宽高
	rt=CreateNRt(4,el->pt);
	h1=rt.Height();
	w1=rt.Width();
	//原来的宽高
	w2=rt1.Width();
	h2=rt1.Height();
	if(w2==0||h2==0) return;
	rt2.left=0;		rt2.top=0;
	rt2.right=rt.left;	rt2.bottom=rt.top;
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	bl=xl>yl ? yl:xl;
	bl=(double)(1/bl);
	k=-1;
	for(i=0;i<j;i++){
	  type=bs[i].attr.type;
	  if(type!=12){ //母板不显示
	   	bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.SetSelected();
		bbs.MoveObject2(rt2,xl,yl);
		if(bl!=0) bbs.SetLineWidth(bl);
		if(el->type==1){
		  l=bs[i].attr.belong;
		  if(l>0){
			l--;
			l=l>2 ? 0:l;
			bbs.SetColor(cobj.vcolor[el->site[l].vl]);
		  }
		 if(type==11&&cobj.showsite==1){ //对端子的特殊处理
			  k++;
			  if(k<3){
		       if((el->subtype==7||el->subtype==8)) l=el->site[k].vl;
		       else l=el->site[0].vl;
		       l=l>20 ? 0:l;	
			   color=cobj.vcolor[l];
			   es=(N_ESITE*)bbs.buf;
			   if(el->site[k].id>=0)  es->solder=1;else es->solder=0;
			   es->color=color;
			  }
		  }
		}
		if(type!=11||(type==11&&cobj.showsite==1)) bbs.ShowE(mdc,dx,dy);
		bbs.FreeMem();
	  }
	};
	//标志显示
	bool s=false;
	if(cobj.nocondev){
		for(i=0;i<el->sitesum;i++){
			if(el->site[i].id<0){
				s=true;
				break;
			}
		}
	}
	if(cobj.nocdev){
		if(el->did<0) s=true;
	}
	if(s){  //显示标志矩形
		drt.OffsetRect(dx,dy);
		drt.right++;
		drt.bottom++;
		mdc.CDrawGlass(drt,0xff,0,0,100);
	}
}



//根据记录号索引号显示图元组(打印用)
void BASE0::PreBusEGPEx(HDC hdc,int num,int index,int dx,int dy,int pm)
{
	int type;
	BASE0 *bs,bbs;
	N_BUS *bus;
	int i,j,k;
	double xl,yl,w1,w2,h1,h2,bl;
	CDRect rt,rt1,rt2;
	bus=(N_BUS*)buf;
	switch(index){
	 case 0:
		bs=cobj.egp[num].bs1;
		j=cobj.egp[num].bsum1;
		rt1.SetDRECT(cobj.egp[num].rt1);
		break;
	 case 1:
		bs=cobj.egp[num].bs2;
		j=cobj.egp[num].bsum2;
		rt1.SetDRECT(cobj.egp[num].rt2);
		break;
	 default:return;
	};
	if(bs==NULL||j<=0)	return;
	//计算宽高
	rt=CreateNRt(4,bus->pt);
	h1=rt.Height();
	w1=rt.Width();
	//原来的宽高
	w2=rt1.Width();
	h2=rt1.Height();
	if(w2==0||h2==0) return;
	rt2.left=0;		rt2.top=0;
	rt2.right=rt.left;	rt2.bottom=rt.top;
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	bl=xl>yl ? yl:xl;
	bl=(double)(1/bl);
	k=-1;
	for(i=0;i<j;i++){
	  type=bs[i].attr.type;
	  if(type!=12&&type!=11){ //母板不显示
	   	bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.SetSelected();
		bbs.MoveObject2(rt2,xl,yl);
		if(bl!=0) bbs.SetLineWidth(bl);
		bbs.SetColor(cobj.vcolor[bus->vl]);
		bbs.ShowE(hdc,dx,dy,pm);
		bbs.FreeMem();
	  }
	}
}

//根据记录号索引号显示图元组(正常显示专用)
void BASE0::PreBusEGPEx(CDIB&mdc,int num,int index,int dx,int dy)
{
	int type;
	BASE0 *bs,bbs;
	N_BUS *bus;
	int i,j,k;
	CRect drt;
	double xl,yl,w1,w2,h1,h2,bl;
	CDRect rt,rt1,rt2;
	bus=(N_BUS*)buf;
	switch(index){
	 case 0:
		bs=cobj.egp[num].bs1;
		j=cobj.egp[num].bsum1;
		rt1.SetDRECT(cobj.egp[num].rt1);
		break;
	 case 1:
		bs=cobj.egp[num].bs2;
		j=cobj.egp[num].bsum2;
		rt1.SetDRECT(cobj.egp[num].rt2);
		break;
	 default:return;
	};
	if(bs==NULL||j<=0)	return;
	//计算宽高
	rt=CreateNRt(4,bus->pt);
	h1=rt.Height();
	w1=rt.Width();
	//原来的宽高
	w2=rt1.Width();
	h2=rt1.Height();
	if(w2==0||h2==0) return;
	rt2.left=0;		rt2.top=0;
	rt2.right=rt.left;	rt2.bottom=rt.top;
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	bl=xl>yl ? yl:xl;
	bl=(double)(1/bl);
	k=-1;
	for(i=0;i<j;i++){
	  type=bs[i].attr.type;
	  if(type!=12&&type!=11){ //母板不显示
	   	bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.SetSelected();
		bbs.MoveObject2(rt2,xl,yl);
		if(bl!=0) bbs.SetLineWidth(bl);
		bbs.SetColor(cobj.vcolor[bus->vl]);
		bbs.ShowE(mdc,dx,dy);
		bbs.FreeMem();
	  }
	}
}
//显示图形对象
void BASE0::Show(CDIB &mdc,int dx, int dy)
{
	switch(attr.type){    
	case 1: ShowDbx(mdc,dx,dy);			break;
	case 2: ShowRect(mdc.m_hDC,dx,dy);	break;
	case 3: ShowCircle(mdc,dx,dy);		break;
	case 4: ShowHSin(mdc,dx,dy);		break;
	case 5: ShowSin(mdc,dx,dy);			break;
	case 6: ShowArc(mdc.m_hDC,dx,dy);			break;
	case 7: ShowArrow(mdc,dx,dy);		break;
	case 8: ShowGlass(mdc,dx,dy);		break;
	case 10:ShowText(mdc.m_hDC,dx,dy);	break;
	case 11:ShowESite(mdc,dx,dy);		break;
	case 12:ShowEgpMb(mdc.m_hDC,dx,dy);	break;
	case 13:ShowCoordnate(mdc.m_hDC,dx,dy);	break;
	case 14:ShowTable(mdc.m_hDC,dx,dy);	break;
	case 15:ShowImg(mdc,dx,dy);			break;
	case 16:ShowPath(mdc.m_hDC,dx,dy);	break;
	case 17:ShowSpic(mdc,dx,dy);		break;
	case 32:ShowMeter1(mdc,dx,dy);		break;
	case 33:ShowMeter2(mdc.m_hDC,dx,dy);break;
	case 34:ShowMeter3(mdc.m_hDC,dx,dy);break;
	case 35:ShowMeter4(mdc.m_hDC,dx,dy);break;
	case 64:ShowAnl(mdc,dx,dy);			break;
	case 65:ShowReservoir(mdc,dx,dy);	break;
	case 66:ShowEleGrp(mdc,dx,dy);		break;
	case 67:ShowYb(mdc,dx,dy);			break;
	case 68:ShowSysPie(mdc.m_hDC,dx,dy);break;
	case 69:ShowBar(mdc.m_hDC,dx,dy);	break;
	case 70:ShowPie(mdc.m_hDC,dx,dy);	break;
	case 71:ShowDate(mdc.m_hDC,dx,dy);	break;
	case 72:ShowTime(mdc.m_hDC,dx,dy);	break;
	case 73:ShowGifAnl(mdc.m_hDC,dx,dy);break;
	case 74:ShowScrText(mdc,dx,dy);		break;
	case 75:ShowPush(mdc,dx,dy);		break;
	case 76:ShowSlfCtl(mdc.m_hDC,dx,dy);break;
	case 77:ShowFlow(mdc,dx,dy);		break;
	case 78:ShowConLine(mdc,dx,dy);		break;
	case 79:ShowBus(mdc,dx,dy);			break;
	case 80:ShowActObj(mdc.m_hDC,dx,dy);break;
	case 81:ShowFlash(mdc.m_hDC,dx,dy); break;
	case 83:ShowZone(mdc,dx,dy);		break;
	case 84:ShowMTText(mdc.m_hDC,dx,dy);break;
	};
}

//显示图形对象(打印用)
void BASE0::ShowE(HDC hdc,int dx, int dy,int pm)
{
	switch(attr.type)
	{
	case 1: ShowDbx(hdc,dx,dy,pm);		break;
	case 2: ShowRect(hdc,dx,dy,pm);		break;
	case 3: ShowCircle(hdc,dx,dy,pm);	break;
	case 4: ShowHSin(hdc,dx,dy,pm);		break;
	case 5: ShowSin(hdc,dx,dy,pm);		break;
	case 6: ShowArc(hdc,dx,dy,pm);		break;
	case 7: ShowArrow(hdc,dx,dy,pm);	break;
	case 10:ShowText(hdc,dx,dy,pm);		break;
	case 11:ShowESite(hdc,dx,dy,pm);	break;
	case 12:ShowEgpMb(hdc,dx,dy,pm);	break;
	case 32:ShowMeter1(hdc,dx,dy);		break;
	case 33:ShowMeter2(hdc,dx,dy);		break;
	case 34:ShowMeter3(hdc,dx,dy);		break;
	case 35:ShowMeter4(hdc,dx,dy);		break;
	};
}
  

//显示图形对象
void BASE0::ShowE(CDIB&mdc,int dx, int dy)
{
	switch(attr.type){
	case 1: ShowDbx(mdc,dx,dy);				break;
	case 2: ShowRect(mdc.m_hDC,dx,dy,0);	break;
	case 3: ShowCircle(mdc,dx,dy);			break;
	case 4: ShowHSin(mdc,dx,dy);			break;
	case 5: ShowSin(mdc,dx,dy);				break;
	case 6: ShowArc(mdc,dx,dy);				break;
	case 7:	ShowArrow(mdc,dx,dy);			break;
	case 10:ShowText(mdc.m_hDC,dx,dy,0);	break;
	case 11:ShowESite(mdc,dx,dy);			break;
	case 12:ShowEgpMb(mdc.m_hDC,dx,dy,0);	break;
	case 32:ShowMeter1(mdc,dx,dy);			break;
	case 33:ShowMeter2(mdc.m_hDC,dx,dy);	break;
	case 34:ShowMeter3(mdc.m_hDC,dx,dy);	break;
	case 35:ShowMeter4(mdc.m_hDC,dx,dy);	break;
	};
}

//显示图形对象
void BASE0::Print(HDC hdc,int pm,int dx, int dy)
{
	switch(attr.type){
	case 1: ShowDbx(hdc,dx,dy,pm);		break;
	case 2: ShowRect(hdc,dx,dy,pm);		break;
	case 3: ShowCircle(hdc,dx,dy,pm);	break;
	case 4: ShowHSin(hdc,dx,dy,pm);		break;
	case 5: ShowSin(hdc,dx,dy,pm);		break;
	case 6: ShowArc(hdc,dx,dy,pm);		break;
	case 7: ShowArrow(hdc,dx,dy,pm);	break;
	case 10:ShowText(hdc,dx,dy,pm);		break;
	case 11:ShowESite(hdc,dx,dy,pm);	break;
	case 12:ShowEgpMb(hdc,dx,dy,pm);	break;
	case 13:ShowCoordnate(hdc,dx,dy,pm);break;
	case 14:ShowTable(hdc,dx,dy,pm);	break;
	case 15:ShowImg(hdc,dx,dy);			break;
	case 16:ShowPath(hdc,dx,dy,pm);		break;
	case 17:ShowSpic(hdc,dx,dy);		break;
	case 64:ShowAnl(hdc,dx,dy,pm);		break;
	case 65:ShowReservoir(hdc,dx,dy,pm);break;
	case 66:ShowEleGrp(hdc,dx,dy,pm);	break;
	case 67:ShowYb(hdc,dx,dy);			break;
	case 68:ShowSysPie(hdc,dx,dy);		break;
	case 69:ShowBar(hdc,dx,dy);			break;
	case 70:ShowPie(hdc,dx,dy);			break;
	case 71:ShowDate(hdc,dx,dy,pm);		break;
	case 72:ShowTime(hdc,dx,dy,pm);		break;
	case 73:ShowGifAnl(hdc,dx,dy);		break;
	case 74:ShowScrText(hdc,dx,dy,pm);	break;
	case 75:ShowPush(hdc,dx,dy);		break;
	case 76:ShowSlfCtl(hdc,dx,dy);		break;
	case 77:ShowFlow(hdc,dx,dy,pm);		break;
	case 78:ShowConLine(hdc,dx,dy,pm);	break;
	case 79:ShowBus(hdc,dx,dy,pm);		break;
	case 80:ShowActObj(hdc,dx,dy);		break;
	case 81:ShowFlash(hdc,dx,dy);		break;
	case 83:ShowZone(hdc,dx,dy,pm);		break;
	case 84:ShowMTText(hdc,dx,dy,pm);	break;
	};
}

void BASE0::ShowBasGrp(CDIB &mdc,int dx, int dy)
{
	switch(attr.type){
	case 1: ShowDbx(mdc.m_hDC,dx,dy);	break;
	case 2: ShowRect(mdc.m_hDC,dx,dy);	break;
	case 3: ShowCircle(mdc,dx,dy);		break;
	case 4: ShowHSin(mdc,dx,dy);		break;
	case 5: ShowSin(mdc,dx,dy);			break;
	case 6: ShowArc(mdc,dx,dy);			break;
	case 7: ShowArrow(mdc,dx,dy);		break;
	case 8: ShowGlass(mdc,dx,dy);		break;
	case 10:ShowText(mdc.m_hDC,dx,dy);	break;
	case 11:ShowESite(mdc,dx,dy);		break;
	case 12:ShowEgpMb(mdc.m_hDC,dx,dy);	break;
	case 13:ShowCoordnate(mdc.m_hDC,dx,dy);	break;
	case 14:ShowTable(mdc.m_hDC,dx,dy);	break;
	case 15:ShowImg(mdc,dx,dy);			break;
	case 17:ShowSpic(mdc,dx,dy);		break;
	};
}

//显示活动对象
void BASE0::ShowActGrp(CDIB &mdc,int dx, int dy,int mode)
{
	N_FLOW *flw;
	switch(attr.type)
	{
	case 64:ShowAnl(mdc,dx,dy);			break;
	case 66:ShowEleGrp(mdc,dx,dy);		break;
	case 68:ShowSysPie(mdc.m_hDC,dx,dy);break;
	case 69:ShowBar(mdc.m_hDC,dx,dy);	break;
	case 70:ShowPie(mdc.m_hDC,dx,dy);	break;
	case 71:ShowDate(mdc.m_hDC,dx,dy);	break;
	case 72:ShowTime(mdc.m_hDC,dx,dy);	break;
	case 75:ShowPush(mdc,dx,dy);		break;
	case 76:ShowSlfCtl(mdc.m_hDC,dx,dy);break;
	case 77:
		flw=(N_FLOW *)buf;
		if(flw->style==0||mode==1) 	ShowFlow(mdc,dx,dy);	
		break;
	case 78:ShowConLine(mdc,dx,dy);		break;
	case 79:ShowBus(mdc,dx,dy);			break;
	case 81:ShowFlash(mdc.m_hDC,dx,dy);	break;
	//case 83:ShowZone(mdc,dx,dy);		break;
	};
}

//删除选择
void BASE0::ClearSel()
{
	if(bakbuf!=NULL) delete bakbuf;
	sel=0;
	bakbuf=NULL;
}

//查看点是否在图形中
bool BASE0::PtInObject(CPoint point)
{
	HRGN hrgn;
	CDRect rt;
	bool b=false;
	//判断是否是不选择的对象
	switch(attr.type)
	{
	case 1: case 2:case 3: case 4: case 5: case 6: case 7: 
	case 8: case  9: case 16: case 17: case 65: case 66: case 77:case 78:case 83:
		hrgn=CreateRGN();
		
		if(hrgn==NULL)	return false;
		if(PtInRegion(hrgn,point.x,point.y)) b=true;
		DeleteObject(hrgn);
		return b;
	default:
		rt=ort;
		rt.ActRtToScr(cobj.curzoom);
	    if(rt.PtInRect(point)) return true;
	};
	return false;
}

//偏移dx,dy
void BASE0::Offset(double dx, double dy)
{
	int i,ptsum,fill,close;
	DPOINT *pt;
	pt=GetObjectPt(ptsum,fill,close,0);
	if(pt!=NULL){
		for(i=0;i<ptsum;i++){
			pt[i].x=(double)(pt[i].x+dx);
			pt[i].y=(double)(pt[i].y+dy);
		}
	}
	CreateSelRect();
}

//设置为选择
void BASE0::SetSelected(int selindex)
{
	ClearSel();
	sel=selindex;
	if(attr.size>0)
	{
		if(bakbuf==NULL) bakbuf=new char[attr.size];
		if(bakbuf!=NULL) memcpy(bakbuf,buf,attr.size);
	};
};

HRGN BASE0::CreateRGN()
{
	double r;
	int fill,close;
	DPOINT *pt;
	CDRect art;
	N_METER1 *mtr;
	CRect rt;
	int ptsum;
//	N_DBX *dbx;
//	HRGN rgn;
	switch(attr.type)
	{
	/*case 1:
		dbx=(N_DBX*)buf;
		pt=GetObjectPt(ptsum,fill,close,0);
		rgn=CreateNRGN(ptsum,pt,fill,close,cobj.curzoom);
		return rgn;
	case 3:
		pt=GetObjectPt(ptsum,fill,close,0);
		return CreateNRGN(ptsum,pt,1,1,cobj.curzoom);*/
	case 32:
		mtr=(N_METER1*)buf;
		r=GetLength(mtr->pt[0],mtr->pt[1]);
		art.left=mtr->pt[0].x-r;art.right=mtr->pt[0].x+r;
		art.top=mtr->pt[0].y-r;art.bottom=mtr->pt[0].y+r;
		art.ActRtToScr(cobj.curzoom);
		art.GetRECT(rt);
		return CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
    default:
		pt=GetObjectPt(ptsum,fill,close,0);
		return CreateNRGN(ptsum,pt,fill,close,cobj.curzoom);
	};
	return NULL;
}

//返回对象的坐标 mode=0 返回正常点 =1返回Bak点
DPOINT *BASE0::GetObjectPt(int &ptsum,int &fill,int &close,int mode)
{
	N_FLOW  *flw;
	N_PATH  *pth;
	N_ARROW *arw;
	N_DBX  *dbx;
	N_RECT *nrt;
	N_CIRCLE *ncr;
	N_HSIN   *hsn;
	N_CONLINE *cnl;
	N_METER1  *mtr;
	N_RESERVOIR *rev;
	N_ZONE     *zon;
	DPOINT *tpt=NULL;
	ptsum=0;
	switch(attr.type){
	case 1:
		if(mode==0) dbx=(N_DBX*)buf;
		else dbx=(N_DBX*)bakbuf;
		if(dbx!=NULL){
		  ptsum=dbx->ptsum;
		  tpt=dbx->pt;
		  fill=dbx->fill;
		  close=dbx->close;
		}
		break;
	case 2:
		if(mode==0) nrt=(N_RECT*)buf;
		else nrt=(N_RECT*)bakbuf;
		if(nrt!=NULL){
		  ptsum=4;
		  tpt=nrt->pt;
		}
		fill=nrt->fill;
		close=1;
		break;
	case 3:
		if(mode==0) ncr=(N_CIRCLE*)buf;
		else ncr=(N_CIRCLE*)bakbuf;
		if(ncr!=NULL){
		  ptsum=4;
		  tpt=ncr->pt;
		}
		fill=ncr->fill;
		close=ncr->type;
		break;
	case 7:
		if(mode==0) arw=(N_ARROW*)buf;
		else arw=(N_ARROW*)bakbuf;
		if(arw!=NULL){
		  ptsum=2;
		  tpt=arw->pt;
		}
		fill=0;	close=0;
		break;
	case 32:
		if(mode==0) mtr=(N_METER1*)buf;
		else mtr=(N_METER1*)bakbuf;
		if(mtr!=NULL){
		  ptsum=2;
		  tpt=mtr->pt;
		}
		fill=0;	close=0;
		break;
	case 16:
		if(mode==0) pth=(N_PATH*)buf;
		else pth=(N_PATH*)bakbuf;
		if(pth!=NULL){
		  ptsum=pth->ptsum;
		  tpt=pth->pt;
		}
		fill=0;	close=0;
		break;
	case 65:
		if(mode==0) rev=(N_RESERVOIR*)buf;
		else rev=(N_RESERVOIR*)bakbuf;
		if(rev!=NULL){
		  ptsum=rev->ptsum;
		  tpt=rev->pt;
		}
		fill=1;	close=0;
		break;
	case 78:
		if(mode==0) cnl=(N_CONLINE*)buf;
		else cnl=(N_CONLINE*)bakbuf;
		if(cnl!=NULL){
		  ptsum=cnl->ptsum;
		  tpt=cnl->pt;
		}
		fill=0;	close=0;
		break;
	case 77:
		if(mode==0) flw=(N_FLOW*)buf;
		else flw=(N_FLOW*)bakbuf;
		if(flw!=NULL){
		  ptsum=flw->ptsum;
		  tpt=flw->pt;
		}
		fill=0;	close=0;
		break;
	case 83:
		if(mode==0) zon=(N_ZONE*)buf;
		else zon=(N_ZONE*)bakbuf;
		if(zon!=NULL){
		  ptsum=zon->ptsum;
		  tpt=zon->pt;
		}
		fill=1;	close=0;
		break;
	default:
		if(mode==0) hsn=(N_HSIN*)buf;
		else hsn=(N_HSIN*)bakbuf;
		if(hsn!=NULL){
		  ptsum=4;
		  tpt=hsn->pt;
		}
		fill=1;	close=1;
	}
	return tpt;
}


//简单移动对象
void BASE0::MoveObject1(double mx,double my,int opno)
{
	CDRect rt;
	double w1,h1;
	DPOINT *pt1,*pt2;
	int ptsum,i,k,fill,close;
	if(sel==0) return;
	pt1=GetObjectPt(ptsum,fill,close,0);
	pt2=GetObjectPt(ptsum,fill,close,1);
	if(ptsum==0||pt1==NULL||pt2==NULL) return;
	if(opno==0){  //平移
		for(i=0;i<ptsum;i++)
		{
		 pt1[i].x=(double)(pt2[i].x+mx);
		 pt1[i].y=(double)(pt2[i].y+my);
		}
		CreateSelRect();
		return;
	}
	switch(attr.type){
	case 1:case 7: case 16:case 77: case 78: case 32:case 65: case 83:
		k=opno-1;
		if(k<0||k>=ptsum) return;
		pt1[k].x=(double)(pt2[k].x+mx);
		pt1[k].y=(double)(pt2[k].y+my);
		ChangeOtherDot(pt1,ptsum,k); //改变线条的连接
		break;
	case 67: //对于仪表，要求放缩比例一样
		rt=CreateNRt(4,pt2);
		w1=rt.Width();
		h1=rt.Height();
		MoveObjRect(rt,mx,my,opno);
		//约束比例
		HoldWH(rt,w1,h1,opno);
		GetptFromDRECT(rt,pt1);
		break;
	default:  //其它情况（矩形）define in bclass 
		rt=CreateNRt(4,pt2);
		MoveObjRect(rt,mx,my,opno);
		GetptFromDRECT(rt,pt1);
	}
	CreateSelRect();
}
//移动时考虑其他点的移动
void BASE0::ChangeOtherDot(DPOINT *pt,int ptsum,int k)
{
	int ks;
	double qx,qy;
	ks=GetKeyState(VK_LSHIFT);
	if(ks>=0) return;
	if(k>0)//操作前面一点
	{
		qx=pt[k].x-pt[k-1].x;
		qy=pt[k].y-pt[k-1].y;
		qx=qx<0 ? -qx:qx;
		qy=qy<0 ? -qy:qy;
		if(qx>=qy)
		{
			pt[k-1].y=pt[k].y;
		}else{
			pt[k-1].x=pt[k].x;
		}
	}
	if(k<ptsum-1) //操作后面一点
	{
		qx=pt[k].x-pt[k+1].x;
		qy=pt[k].y-pt[k+1].y;
		qx=qx<0 ? -qx:qx;
		qy=qy<0 ? -qy:qy;
		if(qx>=qy)
		{
			pt[k+1].y=pt[k].y;
		}else{
			pt[k+1].x=pt[k].x;
		}
	}
}

//按比例移动一个对象
void BASE0::MoveObject2(CDRect prt, double xl, double yl)
{
	double vl,xl1,yl1;
	DPOINT *pt1,*pt2;
	int ptsum,i,fill,close;
	if(sel==0) return;
	pt1=GetObjectPt(ptsum,fill,close,0);
	pt2=GetObjectPt(ptsum,fill,close,1);
	if(ptsum==0||pt1==NULL||pt2==NULL) return;
	if(attr.type==67){
		vl=xl>yl ? yl:xl;
		xl1=vl;
		yl1=vl;
	}else{
		xl1=xl;
		yl1=yl;
	}
	for(i=0;i<ptsum;i++){
		pt1[i].x=(double)(prt.right+(double)(pt2[i].x-prt.left)*xl1);
		pt1[i].y=(double)(prt.bottom+(double)(pt2[i].y-prt.top)*yl1);
	  }
	CreateSelRect();
}

//设置特殊对象的放大倍数，主要针对组合图元的仪表部件
void BASE0::SetSObjZM(double zm)
{
	N_METER1 *mtr;
	N_TEXT    *txt;
	switch(attr.type)
	{
	case 32:
		mtr=(N_METER1*)buf;
		mtr->zm=zm;
		break;
	case 10:
		txt=(N_TEXT*)buf;
		txt->zm=zm;
		break;
	}
}


//结束移动(将数据拷贝到备份区,该对象还处于选择状态)
void BASE0::EndMOveObject()
{
	if(attr.size>0)	memcpy(bakbuf,buf,attr.size);
	CreateSelRect();
}

//查看对象是否完全在矩形中
bool BASE0::RtInRect(CDRect rect)
{
	N_METER1 *mtr;
	CDPoint p1,p2;
	p1=CDPoint(ort.left,ort.top);
	p2=CDPoint(ort.right,ort.bottom);
	if(attr.type==32)
	{
		mtr=(N_METER1*)buf;
		if(rect.PtInRect(mtr->pt[1])) return true;
		else return false;
	}
	if(rect.PtInRect(p1)&&rect.PtInRect(p2)) return true;
	return false;
}

//返回活动对象的类型
bool BASE0::GetDevType(BYTE &type, BYTE &subtype,BYTE &vl,char *dev_name,int &jlh)
{
	N_FLOW  *fl;
	N_ELEGRPA *el;
	N_BUS    *bus;
	subtype=255;
	jlh=-1;
	switch(attr.type)
	{
	case 77:
		fl=(N_FLOW*)buf;
		type=2;
		if(fl->type==0) subtype=34;else subtype=35;
		strcpy(dev_name,fl->dev_name);
		jlh=fl->did;
		vl=fl->vl; //取第一端子电压
		return true;
	case 66:
		el=(N_ELEGRPA*)buf;
		strcpy(dev_name,el->dev_name);
		jlh=el->did;
		vl=el->site[0].vl; //取第一端子电压
		switch(el->type){
		case 0: type=1;return true;
		case 1: type=2;subtype=el->subtype;return true;
		case 2: type=3;return true;
		case 3: type=4;return true;
		case 4: type=0;return true;
		default:return false;
		}
	case 79:
		bus=(N_BUS*)buf;
		type=2;	subtype=33;
		strcpy(dev_name,bus->dev_name);
		jlh=bus->did;
		vl=bus->vl;
		return true;
	}
	return false;
}

//返回活动对象的类型
bool BASE0::GetAnlDevType(char *name,BYTE &type)
{
	N_ANL  *anl;
	if(attr.type!=64) return false;
	anl=(N_ANL*)buf;
	type=anl->dtype;
	strcpy(name,anl->dev_name);
	return true;
}


//画出坐标
void  BASE0::DrawCoordinate(HDC hdc,CRect drt,int mode,N_COORDINATE &co,int pm){

	char p[100];
	DWORD c1;
	int i,xm,ym,w,h,x,y,m;
	double xl,yl,nx,ny;
	CRect rt,rt1;
	rt=drt;
	if(pm==0) c1=co.colorc;else c1=0;
	if(mode==0){
	 rt.left+=40;
	 rt.bottom-=24;
	 rt.right-=20;
	 rt.top+=20;
	}else{
	 rt.left=(int)(rt.left+40*cobj.curzoom/co.zm);
	 rt.bottom=(int)(rt.bottom-24*cobj.curzoom/co.zm);
	 rt.right=(int)(rt.right-20*cobj.curzoom/co.zm);
	 rt.top=(int)(rt.top+20*cobj.curzoom/co.zm);	
	}
	w=rt.right-rt.left;
	h=rt.bottom-rt.top;
	xm=co.xdot<2 ? 2:co.xdot;
	ym=co.ydot<2 ? 2:co.ydot;
	xl=(double)(w/(double)xm);
	yl=(double)(h/(double)ym);
	nx=(double)((co.xmax-co.xmin)/(double)xm);
	ny=(double)((co.ymax-co.ymin)/(double)ym);

	m=(int)(5*cobj.curzoom/co.zm);
	if(co.xvshow==1){
	 for(i=0;i<xm+1;i++){
       x=(int)(i*xl);
	   GLDrawLine(hdc,rt.left+x,rt.bottom,rt.left+x,rt.bottom+m,1,c1);
	   if(i>0){
		rt1.left=(int)(rt.left+x-xl/2);
		rt1.right=(int)(rt.left+x+xl/2);
		rt1.top=rt.bottom+m;
		rt1.bottom=drt.bottom;
		sprintf(p,"%d",(DWORD)(i*nx+co.xmin));
		GLDDrawText(hdc,&rt1,&co.fontx,p,co.colort,0,DT_CENTER);
	   }
	 };
	}
	m=(int)(5*cobj.curzoom/co.zm);
	if(co.yvshow==1){
	 for(i=0;i<ym+1;i++){
		y=(int)(i*yl);
		GLDrawLine(hdc,rt.left-m,rt.bottom-y,rt.left,rt.bottom-y,1,c1);
		if(i>0){
		 rt1.left=drt.left+1;
		 rt1.right=rt.left-m;
		 rt1.top=(int)(rt.bottom-y-yl/2);
		 rt1.bottom=(int)(rt.bottom-y+yl/2);
		 sprintf(p,"%d",(DWORD)(i*ny+co.ymin));
		 GLDDrawText(hdc,&rt1,&co.fonty,p,co.colort,0,DT_RIGHT|DT_VCENTER|DT_SINGLELINE);
		}
	 };	
	}
	if(co.wxdraw==1){
	 for(i=0;i<xm+1;i++){
       x=(int)(i*xl);
	   GLDrawLine(hdc,rt.left+x,rt.bottom,rt.left+x,rt.top,1,co.colorw);
	 };
	}
	if(co.wydraw==1){
	 for(i=0;i<ym+1;i++){
		y=(int)(i*yl);
		GLDrawLine(hdc,rt.left,rt.bottom-y,rt.right,rt.bottom-y,1,co.colorw);
	 };
	}
	
	BDrawDIRSingle(hdc,CPoint(drt.left,rt.bottom),CPoint(drt.right,rt.bottom),
		c1,(BYTE)(4*cobj.curzoom));
	BDrawDIRSingle(hdc,CPoint(rt.left,drt.bottom),CPoint(rt.left,drt.top),
		c1,(BYTE)(4*cobj.curzoom)); 
	rt.right++;
	rt.bottom++;
	GLDDraw3DRect(hdc,rt,c1,c1);

};

//画出表格
void  BASE0::DrawTable(HDC hdc,CRect drt,N_TABLE &ta,int pm)
{
	int i,ym,h,y,lw;
	DWORD c1;
	double yl;
	CRect rt,rt1;
	rt=drt;
	rt.left+=5;
	rt.bottom-=5;
	rt.right-=5;
	rt.top+=5;
	h=rt.bottom-rt.top;
	ym=ta.line<2 ? 2:ta.line;
	yl=(double)(h/(double)ym);
	if(pm==0) c1=ta.color;else c1=0;
	for(i=0;i<ym+1;i++){
		y=(int)(i*yl);
		GLDrawLine(hdc,rt.left,rt.bottom-y,rt.right,rt.bottom-y,(BYTE)ta.width,c1);
	};	
	rt.right++;
	rt.bottom++;
	lw=(int)ta.width;
	if(ta.dbline==1) lw=lw*2;
	GLDDraw3DRect(hdc,rt,c1,ta.color,lw);
};




void  BASE0::DrawBar(HDC hdc,CRect  drt,N_BAR &bar)
{
	if(bar.dsrc.xsmode>0)
	{
		CRect rtTxt=drt;
		int w=drt.Width()/3;
		rtTxt.right=rtTxt.left+w;

		if(strlen(bar.dsrc.name)>0)
		{
			LOGFONT font=cobj.font;
			font.lfHeight=(int)(rtTxt.Height());
			font.lfWidth=(int)(rtTxt.Height()/2);
			SIZE sz=GLDGetTextSize(hdc,&font,bar.dsrc.name);
			if(rtTxt.Width()<sz.cx)
				rtTxt.left=rtTxt.right-sz.cx;

			GLDDrawText(hdc,&rtTxt,&font,bar.dsrc.name,RGB(255,255,255),0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		}

		drt.left=drt.left+w;
	}

	switch(bar.xy){
	case 0:
		GLRectc(hdc,drt,bar.ncolor,0xffffff,5);
		if(bar.outline==1)	GLRect(hdc,drt.left,drt.top,drt.right,drt.bottom,1,0xc0c0c0);
		break;
	case 1:
		GLRectc(hdc,drt,bar.ncolor,0xffffff,4);
		if(bar.outline==1)
		GLRect(hdc,drt.left,drt.top,drt.right,drt.bottom,1,0);
		break;
	};
};

//初始化自助空件
void BASE0::InitSelfCtl()
{
	CFileFind fd;
	char name[256];
	char tmppath[256];
	char p[256],*p1;
	N_SELFCTL *sft;
	sft=(N_SELFCTL*)buf;
	if(sft->hinst!=NULL) FreeLibrary(sft->hinst);
	sft->hinst=NULL;
	sft->DfClose=NULL;
	sft->DfDrawDemo=NULL;
	sft->DfGetVer=NULL;
	sft->DfInit=NULL;
	sft->DfAbout=NULL;
	sft->DfSetParam=NULL;
	sft->DfPrint=NULL;
	sft->hwnd=NULL;
	cobj.SetToLocalFile(sft->dllname,name);
	GetCurrentDirectory(256,tmppath);
	strcpy(p,name);
 	p1=strrchr(p,'\\');
	if(p1!=NULL){
		*p1=0;
		SetCurrentDirectory(p);  //先设置到该动态连接库所在目录
	}
	sft->hinst=LoadLibrary(name);
	if(sft->hinst!=NULL){
	  (FARPROC&)sft->DfGetVer=GetProcAddress(sft->hinst,"DfGetVer");
	  (FARPROC&)sft->DfDrawDemo=GetProcAddress(sft->hinst,"DfDrawDemo");
	  (FARPROC&)sft->DfInit=GetProcAddress(sft->hinst,"DfInit");
	  (FARPROC&)sft->DfClose=GetProcAddress(sft->hinst,"DfClose");
	  (FARPROC&)sft->DfAbout=GetProcAddress(sft->hinst,"DfAbout");
	  (FARPROC&)sft->DfSetParam=GetProcAddress(sft->hinst,"DfSetParam");
	  (FARPROC&)sft->DfPrint=GetProcAddress(sft->hinst,"DfPrint");
		 };
	if(sft->hinst==NULL){
		sprintf(p,"找不到%s或文件运行有问题!",name);	
		MessageBox(0,p,"错误",MB_OK);
	};
	if(sft->hinst!=NULL&&(sft->DfGetVer==NULL||
		  sft->DfDrawDemo==NULL||sft->DfInit==NULL||
		  sft->DfClose==NULL)){
		  FreeLibrary(sft->hinst);
		  sft->hinst=NULL;
		  sft->DfGetVer=0;
		  sft->DfDrawDemo=NULL;
		  sft->DfInit=NULL;
		  sft->DfClose=NULL;
		  sft->DfAbout=NULL;
		  sft->DfSetParam=NULL;
		  sft->DfPrint=NULL;
		  MessageBox(0,"添加的DLL不支持自助协议.","错误",MB_OK);
		 };
	SetCurrentDirectory(tmppath);	//恢复为原来的目录
}

//生成可画的屏幕矩形
CRect BASE0::CreateDrawRect(int ptsum,DPOINT *pt,int dx,int dy)
{
	CRect rt;
	CDRect art;
	art=CreateNRt(ptsum,pt);
	art.ActRtToScr(cobj.curzoom);
	art.GetRECT(rt);
	rt.OffsetRect(dx,dy);
	return rt;
}


//将矩形整直
void BASE0::StraightObj()
{
	int i,ptsum,fill,close;
	double w,h;
	DPOINT *p1,*p2;
	p1=GetObjectPt(ptsum,fill,close,0);
	p2=GetObjectPt(ptsum,fill,close,1);
	if(p1==NULL||p2==NULL) return;		//无对象
	if(close==0){	//多点线的处理
		for(i=1;i<ptsum;i++){
			w=(double)(p1[i].x-p1[i-1].x);
			h=(double)(p1[i].y-p1[i-1].y);
			w=w<0 ? -w:w;
			h=h<0 ? -h:h;
			if(w>h)  p1[i].y=p1[i-1].y;
			else p1[i].x=p1[i-1].x;	
			p2[i]=p1[i];
		};
		return;
	}
	//矩形的处理
	p1[0].x=ort.left;p1[0].y=ort.top;
	p1[1].x=ort.right;p1[1].y=ort.top;
	p1[2].x=ort.right;p1[2].y=ort.bottom;
	p1[3].x=ort.left;p1[3].y=ort.bottom;
	for(i=0;i<ptsum;i++) p2[i]=p1[i];
	CreateSelRect();
}


//将矩形整直
void BASE0::SqrtObj()
{
	int i,ptsum,fill,close;
	double w,h;
	DPOINT *p1,*p2;
	p1=GetObjectPt(ptsum,fill,close,0);
	p2=GetObjectPt(ptsum,fill,close,1);
	if(p1==NULL||p2==NULL||ptsum!=4) return;		//无对象
	//矩形的处理
	ort.NormalizeRect();
	w=ort.Width();
	h=ort.Height();
	w=w>h ? w:h;
	p1[0].x=ort.left;p1[0].y=ort.top;
	p1[1].x=ort.left+w;p1[1].y=ort.top;
	p1[2].x=ort.left+w;p1[2].y=ort.top+w;
	p1[3].x=ort.left;p1[3].y=ort.top+w;
	for(i=0;i<ptsum;i++) p2[i]=p1[i];
	CreateSelRect();
}

bool BASE0::IsRotateObj()
{
	if(attr.type>63) return false;
	return true;
}

bool BASE0::IsDeviceObj()
{
	switch(attr.type){
	 case 66: case 77:  case 78: case 79:
     return true;
	}
	return false;
}

//设置对象的颜色
void BASE0::SetColor(DWORD color)
{
	N_DBX  *db;
	N_RECT *rt;
	N_HSIN *hn;
	N_SIN  *sn;
	N_ARROW *aw;
	N_TEXT  *tx;
	N_ARC   *ar;
	N_ESITE *si;
	N_METER1 *mt1;
	N_METER2 *mt2;
	N_METER3 *mt3;
	N_METER4 *mt4;
	switch(attr.type){
	case 1: 
		db=(N_DBX*)buf;
		db->lcolor=color;
		break;
	case 2: case 3:
		rt=(N_RECT *)buf;
		rt->lcolor=color;
		break;
	case 4:
		hn=(N_HSIN*)buf;
		hn->color=color;  
		break;
	case 5: 
		sn=(N_SIN*)buf;
		sn->color=color;  
		break;
	case 6:
		ar=(N_ARC*)buf;
		ar->color=color;
		break;
	case 7:
		aw=(N_ARROW*)buf;
		aw->color=color;
		break;
	case 10:
		tx=(N_TEXT*)buf;
		tx->color=color;
		break;
	case 11:
		si=(N_ESITE*)buf;
		si->color=color;
		break;
	case 32:
		mt1=(N_METER1*)buf;
		mt1->cr[0]=color;
		mt1->cr[1]=color;
		mt1->pcr=color;
		mt1->scr=color;
		break;
	case 33:
		mt2=(N_METER2*)buf;
		mt2->cr[0]=color;
		mt2->cr[1]=color;
		mt2->pcr=color;
		mt2->scr=color;
		break;
	case 34:
		mt3=(N_METER3*)buf;
		mt3->cr[0]=color;
		mt3->cr[1]=color;
		mt3->pcr=color;
		mt3->scr=color;
		break;
	case 35:
		mt4=(N_METER4*)buf;
		mt4->bcr=color;
		mt4->ncr[0]=color;
		mt4->ncr[1]=color;
		break;
	};
}

//设置对象的宽度
void BASE0::SetLineWidth(double bl)
{
	N_DBX  *db;
	N_RECT *rt;
	N_HSIN *hn;
	N_ARROW *aw;
	N_ARC   *ar;
	switch(attr.type){
	case 1: 
		db=(N_DBX*)buf;
		db->width/=bl;
		break;
	case 2: case 3:
		rt=(N_RECT *)buf;
		rt->width/=bl;
		break;
	case 4:
		hn=(N_HSIN*)buf;
		hn->width/=bl;
		break;
	case 6:
		ar=(N_ARC*)buf;
		ar->width/=bl;
		break;
	case 7:
		aw=(N_ARROW*)buf;
		aw->width/=bl;
		break;
	};
}

//空置对象参数(不删除对象)
void BASE0::SetEmpty()
{
	buf=NULL;
	bakbuf=NULL;
}


/*void BASE0::SetDadaSource(char *ds_name, int jlh)
{
	N_ANL   *al;
	N_FLOW  *fl;
	N_ELEGRPA *el;
	N_GIFAML *gf;
	N_BUS    *bus;
	switch(attr.type)
	{
	case 64:
		al=(N_ANL*)buf;
		strcpy(al->dev_name,ds_name);
		al->did=jlh;
		break;
	case 77:
		fl=(N_FLOW*)buf;
		strcpy(fl->dev_name,ds_name);
		fl->did=jlh;
		break;
	case 66:
		el=(N_ELEGRPA*)buf;
//		strcpy(el->ds_name,ds_name);
//		el->jlh=jlh;
		break;
	case 73:
		//"状态量","设备","站","局"};
		gf=(N_GIFAML*)buf;
		strcpy(gf->dsrc.name,ds_name);
		gf->dsrc.did=jlh;
		break;
	case 79:
		bus=(N_BUS*)buf;
		//strcpy(bus->ds_name,ds_name);
		//bus->jlh=jlh;
		break;
	}
}*/

void BASE0::SetDevSource(char *dev_name, int djlh)
{
	N_FLOW  *fl;
	N_ELEGRPA *el;
	N_BUS    *bus;
	N_RESERVOIR *rev;
	N_ZONE    *zon;
	switch(attr.type)
	{
	case 77:
		fl=(N_FLOW*)buf;
		strcpy(fl->dev_name,dev_name);
		fl->did=djlh;
		break;
	case 65:
		rev=(N_RESERVOIR*)buf;
		strcpy(rev->dev_name,dev_name);
		rev->did=djlh;
		break;
		break;
	case 66:
		el=(N_ELEGRPA*)buf;
		strcpy(el->dev_name,dev_name);
		el->did=djlh;
		break;
	case 79:
		bus=(N_BUS*)buf;
		strcpy(bus->dev_name,dev_name);
		bus->did=djlh;
		break;
	case 83:
		zon=(N_ZONE*)buf;
		strcpy(zon->zone_name,dev_name);
		zon->did=djlh;
		break;
	}
}

void BASE0::SetDevName_VL(char *dev_name, int vl1,int vl2,int vl3)
{
	N_FLOW  *fl;
	N_ELEGRPA *el;
	N_BUS    *bus;
	N_ANL    *anl;
	switch(attr.type)
	{
	case 77:
		fl=(N_FLOW*)buf;
		strcpy(fl->dev_name,dev_name);
		fl->vl=vl1;
		break;
	case 66:
		el=(N_ELEGRPA*)buf;
		strcpy(el->dev_name,dev_name);
		if(vl1!=-1) el->site[0].vl=vl1;
		if(vl2!=-1) el->site[1].vl=vl2;
		if(vl3!=-1) el->site[2].vl=vl3;
		break;
	case 79:
		bus=(N_BUS*)buf;
		strcpy(bus->dev_name,dev_name);
		bus->vl=vl1;
		break;
	case 64:
		anl=(N_ANL*)buf;
		strcpy(anl->dev_name,dev_name);
		break;
	}
}


void BASE0::SetAnlIdType(int id,int type)
{
	N_ANL *anl;
	if(attr.type!=64) return;
	anl=(N_ANL*)buf;
	anl->did=id;
	anl->dtype=type;
}

void BASE0::ReSetValue(N_BASATTR &atr, void *obuf)
{
	N_SELFCTL *sft;
	//处理原来的内容
	if(attr.type==76&&buf!=NULL){    //如果是自助控件
	  	sft=(N_SELFCTL*)buf;
		if(sft->hinst!=NULL) FreeLibrary(sft->hinst);
		sft->hinst=NULL;
		sft->DfGetVer=0;
		sft->DfDrawDemo=NULL;
		sft->DfInit=NULL;
		sft->DfClose=NULL;
		sft->DfAbout=NULL;
		sft->DfSetParam=NULL;
	};
	if(sel==1&&bakbuf!=NULL) delete bakbuf; 
	////////////////////////////
	attr=atr;
	buf=NULL;
	bakbuf=NULL;
	if(attr.size>0){
	  buf=new char[attr.size];
	  memcpy(buf,obuf,attr.size);
	  if(sel==1) SetSelected();
	};
	//如果是自助控件，特殊处理
	if(attr.type==76) InitSelfCtl();
	//计算矩形
	CreateSelRect();
}

//设置模拟量值
bool BASE0::SetAnlVal(R_ANL &v)
//返回值 true=可以立即画 false=不需要画
{
	bool b=false;
	N_ANL *al;
	N_BAR   *ba;
	N_FLOW  *fl;
	switch(attr.type)
	{
	case 64:
		al=(N_ANL*)buf;
		if(memcmp(&v,&al->rval,sizeof(R_ANL))){
			b=true;
			memcpy(&al->rval,&v,sizeof(R_ANL));
		}
		break;
	case 69:
		ba=(N_BAR*)buf;
		if(memcmp(&v,&ba->rval,sizeof(R_ANL))){
			b=true;
			memcpy(&ba->rval,&v,sizeof(R_ANL));
		}
		break;
	case 77:
		fl=(N_FLOW*)buf;
		//memcpy(&fl->rval,&v,sizeof(R_ANL));
		break;
	}
	return b;
}

//设置状态量值
bool BASE0::SetStaVal(R_STA &v)
//返回值 true=可以立即画 false=不需要画
{
	bool b=false;
	N_ELEGRPA *el;
	N_GIFAML *gf;
	switch(attr.type)
	{
	case 66:
		el=(N_ELEGRPA*)buf;
		if(memcmp(&v,&el->rval,sizeof(R_STA))){
			b=true;
			el->rval[0]=v;
			el->rval[1]=v;
			el->rval[2]=v;
		}
		break;
	case 73:
		gf=(N_GIFAML*)buf;
		if(memcmp(&v,&gf->rval,sizeof(R_STA))){
			b=false;
			memcpy(&gf->rval,&v,sizeof(R_STA));
		}
		break;
	}
	return b;
}


void BASE0::SetVLevel(BYTE vl)
{
	N_ELEGRPA *ele;
	N_FLOW    *fw;
	N_CONLINE *cn;
	N_BUS     *bs;
	int i;
	switch(attr.type){
		case 66:
			ele=(N_ELEGRPA*)buf;
			for(i=0;i<ele->sitesum;i++){
				ele->site[i].vl=vl;
				}
			break;
		case 77:
			fw=(N_FLOW*)buf;
			fw->vl=vl;
			break;
		case 78:
			cn=(N_CONLINE*)buf;
			cn->vl=vl;
			break;
		case 79:
			bs=(N_BUS*)buf;
			bs->vl=vl;
			break;
	}

}

void BASE0::SetFont(LOGFONT &font)
{
	N_TEXT *txt;
	N_ANL  *anl;
	N_DATE *dat;
	N_TIME *tim;
	N_SRLTEXT *sct;
	N_PUSH *ph;
	switch(attr.type){
		case 10:
			txt=(N_TEXT*)buf;
			txt->font=font;
			break;
		case 64:
			anl=(N_ANL*)buf;
			anl->lf=font;
			break;
		case 71:
			dat=(N_DATE*)buf;
			dat->font=font;
			break;
		case 72:
			tim=(N_TIME*)buf;
			tim->font=font;
			break;
		case 74:
			sct=(N_SRLTEXT*)buf;
			sct->lf=font;
			break;
		case 75:
			ph=(N_PUSH*)buf;
			ph->lf=font;
			break;
	}

}


CDRect BASE0::GetObjRect()
{
	DPOINT *pt;
	int  fill,close;
	int  ptsum;
	CDRect art;
	pt=GetObjectPt(ptsum,fill,close,0);
	art=CreateNRt(ptsum,pt);
	art.NormalizeRect();
	return art;
}
//模拟量显示的调整矩形
void BASE0::OffsetRt(CRect &rt,int wh, int direct, int qh)
{
	switch(qh){
	case 0://上下或左右
		switch(direct){
		case 0:
			rt.top+=wh;
			if(rt.top>rt.bottom) rt.top=rt.bottom;
			break;
		case 1:
			rt.left+=wh;
			if(rt.left>rt.right) rt.left=rt.right;
			break;
		}
		break;
	case 1://前后
		switch(direct){
		case 0:
			rt.left+=wh;
			if(rt.left>rt.right) rt.left=rt.right;
			break;
		case 1:
			rt.bottom-=wh;
			if(rt.bottom<rt.top) rt.bottom=rt.top;
			break;
		}
		break;
	}
}


//察看是否相同
bool BASE0::IsSame(BASE0 &base)
{
	if(base.attr.type!=attr.type) return false;
	if(base.attr.size!=attr.size) return false;
	if(attr.size!=0){
		if(memcmp(base.buf,buf,attr.size)!=0) return false; 
	}
	return true;
}


//返回活动对象的类型
void BASE0::SetDevName(char *dev_name,int type,int subtype)
{
	N_FLOW  *fl;
	N_ELEGRPA *el;
	N_BUS    *bus;
	switch(attr.type)
	{
	case 77:
		fl=(N_FLOW*)buf;
		strcpy(fl->dev_name,dev_name);
		break;
	case 66:
		el=(N_ELEGRPA*)buf;
		strcpy(el->dev_name,dev_name);
		if(type>=0) el->type=type;
		if(subtype>=0) el->subtype=subtype;
		break;
	case 79:
		bus=(N_BUS*)buf;
		strcpy(bus->dev_name,dev_name);
		break;
	}
}
