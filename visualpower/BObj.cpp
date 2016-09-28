// BObj.cpp: implementation of the BObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisualPower.h"
#include "DObj.h"
#include "bclass.h"
#include "comobj.h"
#include "gdata.h"
#include "math.h"
#include <afx.h>

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
extern comobj cobj;
extern CPoint *mpt; //临时用的一个点缓冲区，最大1024个点
extern DPOINT *npt;

extern char *wk[];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//返回字符串的行数
int DObj::GetLineNum(char *str)
{
	int i,len,n;	
	n=1;
	len=strlen(str);
	for(i=0;i<len;i++)
	{
		if(str[i]==0xd) n++; 
	};
	return n;
}

//添加一个对象
void DObj::AddObject(N_BASATTR &atr, void *obuf)
{
	attr=atr;
	buf=NULL;
	if(attr.size>0)
	{
	  buf=new char[attr.size];
	  memcpy(buf,obuf,attr.size);
	}
	//计算矩形
	CreateSelRect();
}

//返回对象的坐标 mode=0 返回正常点 =1返回Bak点
DPOINT *DObj::GetObjectPt(int &ptsum)
{
	N_FLOW  *flw;
	N_PATH  *pth;
	N_ARROW *arw;
	N_DBX  *dbx;
	N_METER1  *mtr;
	N_RECT *nrt;
	N_CONLINE *cnl;
	DPOINT *tpt=NULL;
	ptsum=0;
	switch(attr.type)
	{
	case 1:
		dbx=(N_DBX*)buf;
		ptsum=dbx->ptsum;
		tpt=dbx->pt;
		break;
	case 7:
		arw=(N_ARROW*)buf;
		ptsum=2;
		tpt=arw->pt;
		break;
	case 16:
		pth=(N_PATH*)buf;
		ptsum=pth->ptsum;
		tpt=pth->pt;
		break;
	case 32:
		mtr=(N_METER1*)buf;
		ptsum=2;
		tpt=mtr->pt;
		break;
	case 78:
		cnl=(N_CONLINE*)buf;
		ptsum=cnl->ptsum;
		tpt=cnl->pt;
		break;
	case 77:
		flw=(N_FLOW*)buf;
		ptsum=flw->ptsum;
		tpt=flw->pt;
		break;
	default:
		nrt=(N_RECT*)buf;
		ptsum=4;
		tpt=nrt->pt;
	}
	return tpt;
}


//产生选择矩形
void DObj::CreateSelRect()
{
	DPOINT *pt;
	int  ptsum;
	pt=GetObjectPt(ptsum);
	ort=CreateNRt(ptsum,pt);
}

void DObj::FreeMem()
{
	if(buf!=NULL) delete buf;
	buf=NULL;
}

//设置发电机模拟量值
bool DObj::SetDevAnl(READDEV &ran,int kh)
{
	float p,q;
	N_ELEGRPA *elg;
	elg=(N_ELEGRPA *)buf;
	if(elg->type!=1) return false;
	if(memcmp(&ran,&elg->vr,sizeof(READDEV))==0) return false;
	memcpy(&elg->vr,&ran,sizeof(READDEV));
	switch(elg->subtype)
	{
	case 7:  //2饶变
		p=elg->vr.value[2];
		q=elg->vr.value[6];
		elg->Ps=(float)sqrt(p*p+q*q);
		break;
	case 8:   //三绕组变压器
		p=elg->vr.value[4];
		q=elg->vr.value[8];
		elg->Ps=(float)sqrt(p*p+q*q);
		break;
	}
	return true;
}


//设置模拟量值(用于模拟量显示)
bool DObj::SetAnlVal(READDEV &ran)
//返回值 true=可以立即画 false=不需要画
{
	N_ANL *al;
	al=(N_ANL*)buf;
	if(attr.type!=64) return false; //如果不是模拟量直接退出
	if(memcmp(&ran,&al->vr,sizeof(READDEV))==0) return false;
	memcpy(&al->vr,&ran,sizeof(READDEV));
	return true;
}

//初始化自助空件
void DObj::InitSelfCtl()
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
	sft->DfLoadMenu=NULL;
	sft->hwnd=NULL;
	sft->hmenu=NULL;
	cobj.SetToLocalFile(sft->dllname,name);
	GetCurrentDirectory(256,tmppath);
	strcpy(p,name);
 	p1=strrchr(p,'\\');
	if(p1!=NULL)
	{
		*p1=0;
		SetCurrentDirectory(p);  //先设置到该动态连接库所在目录
	}
	sft->hinst=LoadLibrary(name);
	if(sft->hinst!=NULL)
	{
	  (FARPROC&)sft->DfGetVer=GetProcAddress(sft->hinst,"DfGetVer");
	  (FARPROC&)sft->DfDrawDemo=GetProcAddress(sft->hinst,"DfDrawDemo");
	  (FARPROC&)sft->DfInit=GetProcAddress(sft->hinst,"DfInit");
	  (FARPROC&)sft->DfClose=GetProcAddress(sft->hinst,"DfClose");
	  (FARPROC&)sft->DfAbout=GetProcAddress(sft->hinst,"DfAbout");
	  (FARPROC&)sft->DfSetParam=GetProcAddress(sft->hinst,"DfSetParam");
	  (FARPROC&)sft->DfPrint=GetProcAddress(sft->hinst,"DfPrint");
	  (FARPROC&)sft->DfLoadMenu=GetProcAddress(sft->hinst,"DfLoadMenu");
		 };
	if(sft->hinst==NULL)
	{
		sprintf(p,"找不到%s或文件运行有问题!",name);	
		MessageBox(0,p,"错误",MB_OK);
	};
	if(sft->hinst!=NULL&&(sft->DfGetVer==NULL||
		  sft->DfDrawDemo==NULL||sft->DfInit==NULL||
		  sft->DfClose==NULL))
	{
		  FreeLibrary(sft->hinst);
		  sft->hinst=NULL;
		  sft->DfGetVer=0;
		  sft->DfDrawDemo=NULL;
		  sft->DfInit=NULL;
		  sft->DfClose=NULL;
		  sft->DfAbout=NULL;
		  sft->DfSetParam=NULL;
		  sft->DfPrint=NULL;
		  sft->DfLoadMenu=NULL;
		  MessageBox(0,"添加的DLL不支持自助协议.","错误",MB_OK);
	}
	SetCurrentDirectory(tmppath);	//恢复为原来的目录
	if(sft->DfLoadMenu!=NULL) sft->hmenu=sft->DfLoadMenu();
}

//返回活动对象的类型
bool DObj::GetType(BYTE &type, BYTE &subtype,char *ds_name,int &jlh)
{
	N_ANL   *al;
	N_FLOW  *fl;
	N_ELEGRPA *el;
	N_GIFAML *gf;
	N_BUS    *bus;
	N_PIE    *pe;
	N_RESERVOIR *res;
	subtype=255;
	jlh=-1;
	switch(attr.type)
	{
	case 64:
		al=(N_ANL*)buf;
		type=0;
		strcpy(ds_name,al->dev_name);
		jlh=al->vr.did;
		return true;
	case 65:
		res=(N_RESERVOIR *)buf;
		type=6;
		subtype=0;
		strcpy(ds_name,res->dev_name);
		jlh=res->did;
		return true;
	case 68:
		type=15;
		return true;
	case 69:
		type=14;        //棒图对象
		return true;
	case 70:
		pe=(N_PIE*)buf;
		type=13;		//饼图对象
		strcpy(ds_name,pe->name);
		jlh=pe->did;
		return true;
	case 77:
		fl=(N_FLOW*)buf;
		type=2;
		if(fl->type==0) subtype=34;else subtype=35;
		strcpy(ds_name,fl->dev_name);
		jlh=fl->did;
		return true;
	case 66:
		el=(N_ELEGRPA*)buf;
		strcpy(ds_name,el->dev_name);
		jlh=el->did;
		switch(el->type){
		case 0: type=1;return true;
		case 1: type=2;subtype=el->subtype;return true;
		case 2: type=3;subtype=100;return true;
		case 3: type=4;return true;
		case 4: type=0;return true;
		default:return false;
		}
	case 73:
		gf=(N_GIFAML*)buf;
		strcpy(ds_name,gf->dsrc.name);
		jlh=gf->dsrc.did;
		switch(gf->type){
		case 0: type=1;return true;
		case 1: type=2;subtype=2;return true;
		case 2: type=3;return true;
		case 3: type=4;return true;
		default:return false;
		}
	case 79:
		bus=(N_BUS*)buf;
		type=2;	subtype=33;
		strcpy(ds_name,bus->dev_name);
		jlh=bus->did;
		return true;
	}
	return false;
}


//显示多边形对象
void DObj::ShowDbx(HDC hdc,int dx, int dy)
{
	int tpsum;
	N_DBX *dbx;
	dbx=(N_DBX*)buf;
	tpsum=dbx->ptsum>1000 ? 1000:dbx->ptsum;
	PointActToScr(dbx->pt,npt,tpsum,dbm->curzoom);
	dbm->msr->DPtToScrPt(npt,mpt,tpsum,dx,dy);
 	DrawPoly(hdc,mpt,tpsum,dbx->lcolor,dbx->bcolor1,dbx->fill,dbx->close);
}


//显示水库对象
void DObj::ShowReservoir(HDC hdc,int dx, int dy,int pm)
{
	DWORD c1;
	int tpsum;
	N_RESERVOIR *rev;
	rev=(N_RESERVOIR*)buf;
	tpsum=rev->ptsum;
	tpsum=rev->ptsum>1000 ? 1000:rev->ptsum;
	PointActToScr(rev->pt,npt,tpsum,dbm->curzoom);
	c1=pm==0 ? rev->lcolor:0;
	dbm->msr->DPtToScrPt(npt,mpt,tpsum,dx,dy);
	DrawPoly(hdc,mpt,tpsum,c1,rev->ncolor,1,1,1);
}

void DObj::ShowZone(HDC hdc,int dx, int dy,int pm)
{
	CDRect drt;
	CRect rt;
	DPOINT cpt;
	SIZE sz;
	LOGFONT lf;
	DWORD color,color1;
	int tpsum;
	N_ZONE *zn;
	zn=(N_ZONE*)buf;
	tpsum=zn->ptsum;
	tpsum=zn->ptsum>1000 ? 1000:zn->ptsum;
	PointActToScr(zn->pt,npt,tpsum,dbm->curzoom);
	dbm->msr->DPtToScrPt(npt,mpt,tpsum,dx,dy);
	color=pm==0 ? zn->lcolor:0;
	color1=dbm->GetDefColor(5,zn->dyval);
	DrawPoly(hdc,mpt,tpsum,color,color1,0,1,1);
	if(strlen(zn->zone_name)==0) return;
	drt=CreateNRt(zn->ptsum,zn->pt);
	cpt=drt.CenterPoint();
	lf=zn->lf;
	sz=GLDGetTextSize(hdc,&lf,zn->zone_name);
	drt.left=cpt.x-sz.cx/2;
	drt.right=cpt.x+sz.cx/2+2;
	drt.top=cpt.y-sz.cy/2;
	drt.bottom=cpt.y+sz.cy/2+2;
	drt.ActRtToScr(dbm->curzoom);
	drt.Offset(dx,dy);
	drt.GetRECT(rt);
	lf.lfHeight=(long)(lf.lfHeight*dbm->curzoom);
	lf.lfWidth=(long)(lf.lfWidth*dbm->curzoom);
	GLDDrawText(hdc,&rt,&lf,zn->zone_name,zn->fcolor,0,DT_LEFT);
}


void DObj::ShowDbxP(HDC hdc,int dx, int dy,int pm)
{
	DWORD c1;
	int tpsum;
	N_DBX *dbx;
	dbx=(N_DBX*)buf;
	tpsum=dbx->ptsum>1000 ? 1000:dbx->ptsum;
	PointActToScr(dbx->pt,npt,tpsum,dbm->curzoom);
	PtOffset(npt,mpt,tpsum,dx,dy);
	c1=pm==0 ? dbx->lcolor:0;
 	DrawPoly(hdc,mpt,tpsum,c1,dbx->bcolor1,dbx->fill,dbx->close,(int)dbm->curzoom);
}

//显示矩形对象
void DObj::ShowRect(HDC hdc,int dx, int dy)
{
	CDRect rt;
	N_RECT *nrt;
	nrt=(N_RECT*)buf;
	PointActToScr(nrt->pt,npt,4,dbm->curzoom);
	dbm->msr->DPtToScrPt(npt,mpt,4,dx,dy);
	DrawPoly(hdc,mpt,4,nrt->lcolor,nrt->bcolor1,nrt->fill,1);
	switch(nrt->type)
	{
	case 1: //凹矩形
		Draw3dRect(hdc,mpt,0,0xffffff);
		break;
	case 2: //凸矩形
		Draw3dRect(hdc,mpt,0xffffff,0);
		break;
	}
}

//显示矩形对象
void DObj::ShowRectP(HDC hdc,int dx, int dy,int pm)
{
	DWORD c1;
	CDRect rt;
	N_RECT *nrt;
	nrt=(N_RECT*)buf;
	PointActToScr(nrt->pt,npt,4,dbm->curzoom);
	PtOffset(npt,mpt,4,dx,dy);
	c1=pm==0 ? nrt->lcolor:0;
	if(nrt->fill==1) DrawPoly(hdc,mpt,4,c1,nrt->bcolor1,1,1);
	switch(nrt->type)
	{
	case 1: //凹矩形
		Draw3dRect(hdc,mpt,0,0xffffff);
		break;
	case 2: //凸矩形
		Draw3dRect(hdc,mpt,0xffffff,0);
		break;
	}
}

//显示圆对象
void DObj::ShowCircle(HDC hdc,int dx, int dy)
{
	int n;
	CDRect rt;
	CRect crt;
	N_CIRCLE *ncr;
	ncr=(N_CIRCLE*)buf;
	rt=CreateDrawNRt(4,ncr->pt,dbm->curzoom);
	n=GetCircleAllPt(npt,rt);
	dbm->msr->DPtToScrPt(npt,mpt,n,dx,dy);
	if(n<4) return;
	DrawPoly(hdc,mpt,n,ncr->lcolor,ncr->bcolor1,ncr->fill,1);
}

//显示圆对象(打印用)
void DObj::ShowCircleP(HDC hdc,int dx, int dy,int pm)
{
	DWORD c1,c2;
	CDRect rt;
	CRect crt;
	N_CIRCLE *ncr;
	ncr=(N_CIRCLE*)buf;
	rt=CreateDrawNRt(4,ncr->pt,dbm->curzoom);
	rt.Offset(dx,dy);
	rt.GetRECT(crt);
	c1=pm==1 ? 0:ncr->lcolor;
	c2=pm==1 ? 0xffffff:ncr->bcolor1;
	if(ncr->fill==1) GLEllipsec(hdc,crt,c2,c2,0);
	GLCircle(hdc,crt,(int)dbm->curzoom,c1);
}



//显示半波
void DObj::ShowHSin(HDC hdc, int dx, int dy)
{
	int n;
	CDRect art;
	CRect crt;
	N_HSIN *hsn;
	hsn=(N_HSIN *)buf;
	art=CreateDrawNRt(4,hsn->pt,dbm->curzoom);
	n=GetHSinPoint(art,npt,hsn->pirodic,hsn->ltype);
	dbm->msr->DPtToScrPt(npt,mpt,n,dx,dy);
	GLDrawDbx(hdc,n,mpt,1,hsn->color);
}

//显示半波
void DObj::ShowHSinP(HDC hdc, int dx, int dy,int pm)
{
	DWORD c1;
	int n,c;
	CDRect art;
	CRect crt;
	N_HSIN *hsn;
	hsn=(N_HSIN *)buf;
	art=CreateDrawNRt(4,hsn->pt,dbm->curzoom);
	c=hsn->pirodic;
	c=c>30 ? 30:c; //不允许大于30个周期
	n=GetHSinPoint(art,npt,c,hsn->ltype);
	PtOffset(npt,mpt,n,dx,dy);
	c1=pm==0 ? hsn->color:0;
	GLDrawDbx(hdc,n,mpt,(int)dbm->curzoom,c1);
}

void DObj::ShowSin(HDC hdc, int dx, int dy)
{
	int n;
	CDRect art;
	CRect crt;
	N_SIN *sn;
	sn=(N_SIN *)buf;
	art=CreateDrawNRt(4,sn->pt,dbm->curzoom);
	n=GetSinPoint(art,npt,sn->pirodic,sn->ltype,sn->startdeg);
	dbm->msr->DPtToScrPt(npt,mpt,n,dx,dy);
	GLDrawDbx(hdc,n,mpt,1,sn->color);
	
}

void DObj::ShowSinP(HDC hdc, int dx, int dy,int pm)
{
	int w;
	DWORD c1;
	int n;
	CDRect art;
	CRect crt;
	N_SIN *sn;
	sn=(N_SIN *)buf;
	art=CreateDrawNRt(4,sn->pt,dbm->curzoom);
	n=GetSinPoint(art,npt,sn->pirodic,sn->ltype,sn->startdeg);
	PtOffset(npt,mpt,n,dx,dy);
	c1=pm==0 ? sn->color:0;
	w=(int)dbm->curzoom;
	GLDrawDbx(hdc,n,mpt,(int)dbm->curzoom,c1);
}

//显示弧线
void DObj::ShowArc(HDC hdc, int dx, int dy)
{
	int n,start,end;
	CDRect rt;
	CRect crt;
	N_ARC *arc;
	arc=(N_ARC *)buf;
	rt=CreateDrawNRt(4,arc->pt,dbm->curzoom);
	n=GetCircleAllPt(npt,rt);
	if(n<4) return;
	dbm->msr->DPtToScrPt(npt,mpt,n,dx,dy);
	start=(arc->start%360)/5;
	end=(arc->end%360)/5;
	if(end<start) return;
	n=end-start;
	DrawPoly(hdc,&mpt[start],n,arc->color,0,0,0);
}


//显示弧线
void DObj::ShowArcP(HDC hdc, int dx, int dy,int pm)
{
	int n,start,end;
	DWORD c1;
	CDRect rt;
	CRect crt;
	N_ARC *arc;
	arc=(N_ARC *)buf;
	rt=CreateDrawNRt(4,arc->pt,dbm->curzoom);
	n=GetCircleAllPt(npt,rt);
	if(n<4) return;
	dbm->msr->DPtToScrPt(npt,mpt,n,dx,dy);
	start=(arc->start%360)/5;
	end=(arc->end%360)/5;
	if(end<start) return;
	n=end-start;
	c1=pm==0 ? arc->color:0;
	DrawPoly(hdc,&mpt[start],n,c1,0,0,0,(int)dbm->curzoom);
}



void DObj::DrawArrow(HDC hdc,DPOINT *pts,DWORD color,int dx, int dy)
{
	int n;
	double w;
	DPOINT pt1[3];
	pt1[0]=pts[0];
	pt1[1]=pts[1];
	dbm->msr->DPtToScrPt(npt,mpt,2,dx,dy);
	GLLine(hdc,mpt[0].x,mpt[0].y,mpt[1].x,mpt[1].y,color);
	w=4*dbm->curzoom;
	n=GetDirPoint(pt1[0],pt1[1],npt,(int)w);
	dbm->msr->DPtToScrPt(npt,mpt,n,dx,dy);
	GLPolygonc(hdc,mpt,4,color,color,0);
}


void DObj::DrawArrowP(HDC hdc,DPOINT *pts,DWORD color,int dx, int dy)
{
	int n;
	double w;
	DPOINT pt1[3];
	pt1[0]=pts[0];
	pt1[1]=pts[1];
	PtOffset(npt,mpt,2,dx,dy);
	GLLine(hdc,mpt[0].x,mpt[0].y,mpt[1].x,mpt[1].y,color,(int)dbm->curzoom);
	w=4*dbm->curzoom;
	n=GetDirPoint(pt1[0],pt1[1],npt,(int)w);
	PtOffset(npt,mpt,n,dx,dy);
	GLPolygonc(hdc,mpt,4,color,color,0);
}
void DObj::ShowArrow(HDC hdc, int dx, int dy)
{
	N_ARROW *arw;
	arw=(N_ARROW *)buf;
	PointActToScr(arw->pt,npt,2,dbm->curzoom);
	DrawArrow(hdc,npt,arw->color,dx,dy);
}

void DObj::ShowArrowP(HDC hdc, int dx, int dy,int pm)
{
	DWORD c1;
	N_ARROW *arw;
	arw=(N_ARROW *)buf;
	PointActToScr(arw->pt,npt,2,dbm->curzoom);
	if(pm==0) c1=arw->color;else c1=0;
	DrawArrowP(hdc,npt,c1,dx,dy);
}
//参数
//x,y起点坐标
//angle1旋转角度
//用于正常和旋转时的显示，不支持俯视显示
void DObj::ShowTextEx(HDC hdc,LOGFONT *lf,char *str,float x,float y,int w,int h,double angle,DWORD color,DWORD nfmt)
{
	CRect rt;
	double a;
	LOGFONT font=lf[0];
	font.lfEscapement=0;
	a=-angle*mpi/180; 
	SaveDC(hdc);
	StartRatate(hdc,a,x,y);
	rt=CRect(0,0,w,h);
	//TextOut(hdc,10,10,str,strlen(str));   
	GLDDrawText(hdc,&rt,&font,str,color,0,nfmt);
	RestoreDC(hdc,-1);
}


//显示文本
//主要处理是否按WORD换行或回车换行处理
void DObj::SDrawText(HDC hdc,DPOINT *pt,char *text,LOGFONT *ft,int dx,int dy,DWORD color,int nfmt)
{
	int w,h;
	double angle;

	switch(dbm->lookdown)	
	{
	case 0://正常和旋转
		dbm->msr->DPtToScrPt(pt,npt,4,dx,dy);
		w=(int)GetLength(npt[0],npt[1]);
		h=(int)GetLength(npt[0],npt[3]);
		angle=GetAngle(npt[0],npt[1]);
		ShowTextEx(hdc,ft,text,(float)npt[0].x,(float)npt[0].y,w,h,angle,color,nfmt);
		return;
	case 1://俯视
		MDrawText(hdc,pt,text,ft,dx,dy,color,nfmt);
		break;
	}
}


//参数
void DObj::ShowTextXT(HDC hdc,LOGFONT *ft,char *str,DPOINT *pt,DWORD color,int dx,int dy)
{
	int f,n;
	double angle,a,b,w1,w2,w3,h1,h2,a1,a2,a3,a4,a5,a6;
	LOGFONT lf1;
	HFONT hf,oldhf;
	n=strlen(str);
	//if(n!=1) return;
	w1=GetLength(pt[0],pt[1]);
	h1=GetLength(pt[1],pt[2]);
	if(w1<5||h1<5) return;
	dbm->msr->DPtToScrPt(pt,npt,4,dx,dy);
	angle=GetAngle(npt[0],npt[1]);
	a5=angle-90;
	a1=a5-GetAngle(npt[1],npt[2]);
	a2=a5-GetAngle(npt[0],npt[3]);
	a3=a1<0 ? -a1:a1;
	a4=a2<0 ? -a2:a2;
	a6=a3>a4 ? a1:a2;
	//计算新的宽和高
	w2=GetLength(npt[0],npt[1]);
	h2=GetLength(npt[1],npt[2]);
	w3=GetLength(npt[2],npt[3]);
	w2=w2>w3 ? w3:w2;
	lf1=ft[0];
	f=lf1.lfHeight;
	if(f<0){
		lf1.lfHeight=(long)(lf1.lfHeight*h2/h1);
		if(lf1.lfHeight==0) return;
	}else
	{
		lf1.lfHeight=(long)(lf1.lfHeight*h2/h1);
		lf1.lfWidth=(long)(lf1.lfWidth*w2/w1);
		if(lf1.lfHeight<3||lf1.lfWidth<3) return;
	}

	lf1.lfEscapement=0;


	hf=CreateFontIndirect(&lf1);
	SaveDC(hdc);
	oldhf=(HFONT)::SelectObject(hdc,hf);
	SetTextColor(hdc,color);
	a=-angle*mpi/180;
	StartRatate(hdc,a,(float)npt[0].x,(float)npt[0].y);
	if(a6!=0)
	{
		b=-a6*mpi/180;
		SetIncline(hdc,b);
	}
	TextOut(hdc,0,0,str,n);
	hf=(HFONT)::SelectObject(hdc,oldhf);
	RestoreDC(hdc,-1);
	DeleteObject(hf);
}

//将矩形转换为实际的可绘制的4点
void DObj::RtToDrawDpt(CRect &rt,DPOINT *pt,DPOINT *opt,int dr)
{
	switch(dr)
	{
	case 0: //水平点
		pt[0].x=opt->x+rt.left;	pt[0].y=opt->y+rt.top;
		pt[1].x=opt->x+rt.right;pt[1].y=pt[0].y;
		pt[2].x=pt[1].x;		pt[2].y=opt->y+rt.bottom;
		pt[3].x=pt[0].x;		pt[3].y=pt[2].y;
		break;
	case 1: //垂直点
		pt[0].x=opt->x+rt.top; pt[0].y=opt->y-rt.left;
		pt[1].x=pt[0].x;		pt[1].y=opt->y-rt.right;
		pt[2].x=opt->x+rt.bottom; pt[2].y=pt[1].y;
		pt[3].x=pt[2].x; pt[3]. y=pt[0].y;
		break;
	}
}
//返回一个显示单位的长度
int DObj::GetAWordW(char *str,int *pos,int f,int len)
{
	int i,m,n;
	m=len-f;
	if(m<=0) return 0;
	if(str[f]==0x20) return 1;			//是空格 
	if(pos[f]==pos[f+1]&&m>1) return 2;	//是汉字
	n=0;
	for(i=f;i<len;i++)
	{
		m=len-i;
		if(str[i]==0x20) return n;    //是空格 
		if(pos[i]==pos[i+1]&&m>1) return n;//是汉字
		n++;
	}
	return n;
}
//按一定的宽度返回一行
int DObj::GetALine(int start,char *str,int *pos,int w,int max)
{
	int i,k,left,s,m,n;
	s=start;
	if(s>=max)  return 0; //表示已没有
	left=s==0 ? 0:pos[s-1];
	k=0;
	i=s;
	for(;;)
	{
		if(i>=max) return k;
		n=GetAWordW(str,pos,i,max); //返回一个显示单位宽度
		if(n==0) return k;
		m=pos[s+k+n-1]-left; //得到将要显示的宽度
		if(m>w&&k==0) return n;//返回当前串
		if(m>w&&k!=0) return k;//返回前一个宽度
		k=k+n;
		i+=n;
	}
	return 0;
}

//本函数仅用于文本的俯视显示
void DObj::MDrawText(HDC hdc,DPOINT *pt,char *text,LOGFONT *ft,int dx,int dy,DWORD color,DWORD nfmt)
{
	CRect rt;
	char str[12];
	int x,y,w,h,wk,i,fit,pos[128],m,n,dr,end,len,maxline,left; //最大128字符
	SIZE sz;
	HFONT hf,oldhf;
	DPOINT dpt[4];
	hf=CreateFontIndirect(ft);
	n=strlen(text);
	n=n>128 ? 128:n;
	wk=(nfmt&DT_WORDBREAK)==0 ? 0:1;
	dr=pt[0].x!=pt[1].x ? 0:1; //取方向0=水平 1=垂直
	if(dr==0){
		w=(int)(pt[1].x-pt[0].x);
		h=(int)(pt[3].y-pt[0].y);
	}else{
		h=(int)(pt[1].x-pt[0].x);
		w=(int)(pt[3].y-pt[0].y);
	}
	oldhf=(HFONT)SelectObject(hdc,hf);
	if(!GetTextExtentExPoint(hdc,text,n,26000,&fit,pos,&sz)) return;
	SelectObject(hdc,oldhf);
	DeleteObject(hf);
	switch(wk)
	{
	case 0:  //无需按WORD自动排列,单行方式,超出矩形框后即剪裁掉
		n=0;
		rt=CRect(0,0,w,sz.cy);
		for(i=0;i<fit;i++)
		{
			m=0;
			rt.left=n;
			rt.right=pos[i];
			if(rt.right>w) break; //显示字符超出矩形
			
			RtToDrawDpt(rt,dpt,pt,dr);
			n=pos[i];
			str[m]=text[i];
			m++;
			if(i<(fit-1)&&pos[i]==pos[i+1]){
				i++;
				str[m]=text[i];
				m++;
			}
			str[m]=0;
			if(str[0]==0x20) continue;
			ShowTextXT(hdc,ft,str,dpt,color,dx,dy);
		}
		break;
	case 1://按WORD进行排列
		maxline=h/sz.cy;
		x=0;y=0;
		for(;;)
		{
			//首先取一行
			len=GetALine(x,text,pos,w,fit);
			if(len==0) return;
			rt=CRect(0,y*sz.cy,w,y*sz.cy+sz.cy);
			end=x+len;
			n=0;
			left=x==0 ? 0:pos[x-1];
			for(i=x;i<end;i++)
			{
				m=0;
				rt.left=n;
				rt.right=pos[i]-left;
				if(rt.right>w) break; //显示字符超出矩形
				RtToDrawDpt(rt,dpt,pt,dr);
				n=pos[i]-left;
				str[m]=text[i];
				m++;
				if(i<(fit-1)&&pos[i]==pos[i+1]){
					i++;
					str[m]=text[i];
					m++;
				}
				str[m]=0;
				if(str[0]==0x20) continue;
				ShowTextXT(hdc,ft,str,dpt,color,dx,dy);
			}
			x=end;
			y++;
			if((y+1)*sz.cy>h) return;
		}
		break;
	}
}



//显示文本
void DObj::ShowText(HDC hdc, int dx, int dy)
{
	double ha,w;
	LOGFONT lf;
	CRect rt;
	DPOINT opt[4];
	int len,h;
	N_TEXT *text;
	text=(N_TEXT *)buf;
	memcpy(&lf,&text->font,sizeof(LOGFONT));
	PointActToScr(text->pt,opt,4,dbm->curzoom);
	if(text->autofill==0){ //非自动充满
		ha=lf.lfHeight;
		if(ha<0)
		{ 
			ha=-ha;
			lf.lfHeight=(long)(ha*dbm->curzoom*text->zm);
			ha=ha/2;
			lf.lfWidth=(long)(ha*dbm->curzoom*text->zm);
		}else{
		    lf.lfHeight=(long)(lf.lfHeight*dbm->curzoom*text->zm);
		    lf.lfWidth=(long)(lf.lfWidth*dbm->curzoom*text->zm);
		}
	}else{
		len=strlen(text->text);
		if(len<=0) return;
		w=GetLength(opt[0],opt[1]);
		h=(int)GetLength(opt[0],opt[3]);
		lf.lfHeight=h;
		lf.lfWidth=(long)w/len;
	}
	SDrawText(hdc,opt,text->text,&lf,dx,dy,text->color,DT_LEFT|DT_WORDBREAK);
}

//显示文本
void DObj::ShowTextP(HDC hdc, int dx, int dy,int pm)
{
	double ha;
	LOGFONT lf;
	DWORD c1; 
	CDRect drt;
	CRect rt;
	N_TEXT *text;
	text=(N_TEXT *)buf;
	lf=text->font;
	drt=CreateDrawNRt(4,text->pt,dbm->curzoom);
	drt.Offset(dx,dy);
	drt.GetRECT(rt);
	if(text->autofill==0){ //非自动充满
		ha=lf.lfHeight;
		if(ha<0)
		{
			ha=-ha;
			lf.lfHeight=(long)(ha*dbm->curzoom);
			ha=ha/2;
			lf.lfWidth=(long)(ha*dbm->curzoom);
		}else{
		    lf.lfHeight=(long)(lf.lfHeight*dbm->curzoom);
		    lf.lfWidth=(long)(lf.lfWidth*dbm->curzoom);
		}
	}else{
		lf.lfHeight=(long)(lf.lfHeight*dbm->curzoom);
		lf.lfWidth=(long)(lf.lfWidth*dbm->curzoom);
	}
	
	c1=pm==1 ? 0:text->color;
	GLDDrawText(hdc,&rt,&lf,text->text,c1,0,DT_LEFT|DT_WORDBREAK);
}

//显示坐标
void DObj::ShowCoordnate(HDC hdc, int dx, int dy,int pm)
{
	char p[100];
	DWORD c1;
	int i,xm,ym;
	double xl,yl,nx,ny,w,h,m,x,y;
	DPOINT dpt[4];
	CDRect rt;
	SIZE size;
	CDRect drt;
	N_COORDINATE *co,tm;
	co=(N_COORDINATE *)buf;
	drt=CreateDrawNRt(4,co->pt,dbm->curzoom);
	if(co->xmax<co->xmin)
	{
		co->xmax=100;
		co->xmin=0;
	}
	if(co->ymax<co->ymin)
	{
		co->ymax=100;
		co->ymin=0;
	}
	tm=co[0];
	tm.fontx.lfHeight=(long)(tm.fontx.lfHeight*dbm->curzoom/tm.zm);
	tm.fontx.lfWidth=(long)(tm.fontx.lfWidth*dbm->curzoom/tm.zm);
	tm.fonty.lfHeight=(long)(tm.fonty.lfHeight*dbm->curzoom/tm.zm);
	tm.fonty.lfWidth=(long)(tm.fonty.lfWidth*dbm->curzoom/tm.zm);
	
	
	rt=drt;
	if(pm==0) c1=co->colorc;else c1=0;
	rt.left=rt.left+40*dbm->curzoom/co->zm;
	rt.bottom=rt.bottom-24*dbm->curzoom/co->zm;
	rt.right=rt.right-20*dbm->curzoom/co->zm;
	rt.top=rt.top+20*dbm->curzoom/co->zm;	
	
	w=rt.right-rt.left;
	h=rt.bottom-rt.top;
	xm=co->xdot<2 ? 2:co->xdot;
	ym=co->ydot<2 ? 2:co->ydot;
	xl=(double)(w/(double)xm);
	yl=(double)(h/(double)ym);
	nx=(double)((co->xmax-co->xmin)/(double)xm);
	ny=(double)((co->ymax-co->ymin)/(double)ym);

	m=5*dbm->curzoom/co->zm;
	if(co->xvshow==1)
	{
	 for(i=0;i<xm+1;i++)
	 {
		x=i*xl;
		npt[0].x=rt.left+x;
		npt[0].y=rt.bottom;
		npt[1].x=rt.left+x;
		npt[1].y=rt.bottom+m;
		dbm->msr->DPtToScrPt(npt,mpt,2,dx,dy);
		GLDrawLine(hdc,mpt[0].x,mpt[0].y,mpt[1].x,mpt[1].y,1,c1);
	    if(i>0){
			sprintf(p,"%d",(DWORD)(i*nx+co->xmin));
			size=GLDGetTextSize(hdc,&co->fontx,p);
			dpt[0].x=rt.left+x-size.cx/2;dpt[0].y=rt.bottom+m;
			dpt[1].x=rt.left+x+xl/2;dpt[1].y=rt.bottom+m;
			dpt[2].x=dpt[1].x;dpt[2].y=dpt[1].y+size.cy+4;
			dpt[3].x=dpt[0].x;dpt[3].y=dpt[2].y;
			SDrawText(hdc,dpt,p,&tm.fontx,dx,dy,co->colort,DT_LEFT);
		}
	 };
	}
	m=5*dbm->curzoom/co->zm;
	if(co->yvshow==1)
	{
	 for(i=0;i<ym+1;i++)
	 {
		y=i*yl;
		npt[0].x=rt.left-m;
		npt[0].y=rt.bottom-y;
		npt[1].x=rt.left;
		npt[1].y=rt.bottom-y;
		dbm->msr->DPtToScrPt(npt,mpt,2,dx,dy);
		GLDrawLine(hdc,mpt[0].x,mpt[0].y,mpt[1].x,mpt[1].y,1,c1);
		if(i>0){
			
		    sprintf(p,"%d",(DWORD)(i*ny+co->ymin));
			size=GLDGetTextSize(hdc,&co->fonty,p);
			dpt[0].x=drt.left+1;dpt[0].y=rt.bottom-y-size.cy/2;
			dpt[1].x=rt.left-m; dpt[1].y=dpt[0].y;
			dpt[2].x=dpt[1].x;dpt[2].y=dpt[1].y+size.cy+4;
			dpt[3].x=dpt[0].x;dpt[3].y=dpt[2].y;
			SDrawText(hdc,dpt,p,&tm.fonty,dx,dy,co->colort,DT_LEFT);
		}
	 };	
	}
	if(co->wxdraw==1)
	{
	 for(i=0;i<xm+1;i++)
	 {
        x=i*xl;
	    npt[0].x=rt.left+x;
		npt[0].y=rt.bottom;
		npt[1].x=rt.left+x;
		npt[1].y=rt.top;
		dbm->msr->DPtToScrPt(npt,mpt,2,dx,dy);
		GLDrawLine(hdc,mpt[0].x,mpt[0].y,mpt[1].x,mpt[1].y,1,co->colorw);
	 };
	}
	if(co->wydraw==1)
	{
	 for(i=0;i<ym+1;i++)
	 {
		y=i*yl;
		npt[0].x=rt.left;
		npt[0].y=rt.bottom-y;
		npt[1].x=rt.right;
		npt[1].y=rt.bottom-y;
		dbm->msr->DPtToScrPt(npt,mpt,2,dx,dy);
		GLDrawLine(hdc,mpt[0].x,mpt[0].y,mpt[1].x,mpt[1].y,1,co->colorw);
	 };
	}
	npt[0].x=drt.left;
	npt[0].y=rt.bottom;
	npt[1].x=drt.right;
	npt[1].y=rt.bottom;
	DrawArrow(hdc,npt,c1,dx,dy);
	npt[0].x=rt.left;
	npt[0].y=drt.bottom;
	npt[1].x=rt.left;
	npt[1].y=drt.top;
	DrawArrow(hdc,npt,c1,dx,dy);
	npt[0].x=rt.left;npt[0].y=rt.top;
	npt[1].x=rt.right;npt[1].y=rt.top;
	npt[2].x=rt.right;npt[2].y=rt.bottom;
	dbm->msr->DPtToScrPt(npt,mpt,3,dx,dy);
	DrawPoly(hdc,mpt,3,c1,0,0,0);
}

//显示表格线
void DObj::ShowTable(HDC hdc, int dx, int dy,int pm)
{
	int i,ym,h,y,lw;
	DWORD c1;
	double yl;
	CRect rt;
	CDRect drt;
	N_TABLE *ta;
	ta=(N_TABLE *)buf;
	drt=CreateDrawNRt(4,ta->pt,dbm->curzoom);
	

	drt.GetRECT(rt);
	rt.left+=5;
	rt.bottom-=5;
	rt.right-=5;
	rt.top+=5;
	h=rt.bottom-rt.top;
	ym=ta->line<2 ? 2:ta->line;
	yl=(double)(h/(double)ym);
	if(pm==0) c1=ta->color;else c1=0;
	for(i=1;i<ym+1;i++)
	{
		y=(int)(i*yl);
		npt[0].x=rt.left;
		npt[0].y=rt.bottom-y;
		npt[1].x=rt.right;
		npt[1].y=rt.bottom-y;
		dbm->msr->DPtToScrPt(npt,mpt,2,dx,dy);
		GLDrawLine(hdc,mpt[0].x,mpt[0].y,mpt[1].x,mpt[1].y,(BYTE)ta->width,c1);
	}	
	rt.right++;
	rt.bottom++;
	lw=(int)ta->width;
	if(ta->dbline==1) lw=lw*2;
	npt[0].x=rt.left;npt[0].y=rt.top;
	npt[1].x=rt.right;npt[1].y=rt.top;
	npt[2].x=rt.right;npt[2].y=rt.bottom;
	npt[3].x=rt.left;npt[3].y=rt.bottom;
	dbm->msr->DPtToScrPt(npt,mpt,4,dx,dy);
	DrawPoly(hdc,mpt,4,c1,0,0,1);
}



void DObj::ShowImg(HDC hdc, int dx, int dy)
{
	int i;
	double a;
	CDRect drt;
	CRect rt;
	N_IMG *img;
	img=(N_IMG*)buf;
	if(dbm->lookdown==1) return; //只在正常时显示
	drt=CreateDrawNRt(4,img->pt,dbm->curzoom);
	drt.GetRECT(rt);
	i=dbm->GetMPICRecno(img->imgID);
	if(i==-1) return;
	SaveDC(hdc);
	PointActToScr(img->pt,npt,2,dbm->curzoom);
	dbm->msr->DPtToScrPt(npt,mpt,2,dx,dy);
	a=GetAngle(npt[0],npt[1]);
	a=-a*mpi/180;
	StartRatate(hdc,a,(float)mpt[0].x,(float)mpt[0].y);
	SetStretchBltMode(hdc,COLORONCOLOR);
	if(img->zoom==1) StretchBlt(hdc,0,0,rt.Width(),rt.Height(),dbm->mpic[i].dc.m_hDC,0,0,dbm->mpic[i].dc.nWidth,dbm->mpic[i].dc.nHeight,SRCCOPY);
	else dbm->mpic[i].dc.BitBlt(hdc,CRect(0,0,rt.Width(),rt.Height()),SRCCOPY);
	RestoreDC(hdc,-1);
}


//显示仪表1
void DObj::ShowMeter1(HDC hdc,int dx, int dy)
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
	if(dbm->lookdown==1||dbm->curang!=0) return; //只在正常时显示
	PointActToScr(mtr->pt,npt,2,dbm->curzoom);
	for(i=0;i<2;i++)
	{
		npt[i].x+=dx;
		npt[i].y+=dy;
	}
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
	lf.lfHeight=(long)(lf.lfHeight*dbm->curzoom*mtr->zm);
	lf.lfWidth=(long)(lf.lfWidth*dbm->curzoom*mtr->zm);
	fw=lf.lfHeight>0 ? lf.lfHeight:-lf.lfHeight;
	b=mtr->slen*dbm->curzoom*mtr->zm;
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
	if(v==0)
	{
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
	axw=(int)(mtr->axw*mtr->zm*dbm->curzoom);
	pw=(int)(mtr->pw*mtr->zm*dbm->curzoom);
	val=mtr->curval;
	val=val<mtr->Vmin  ? mtr->Vmin:val;
	val=val>mtr->Vmax  ? mtr->Vmax:val;
	b=(val-mtr->Vmin)*xl;
	b=as-b;
	switch(mtr->pstyle)
	{
	case 0:
		ShowMPt1(hdc,spt[0],r3,b,axw,pw,mtr->pcr);
		break;
	case 1:
		ShowMPt2(hdc,spt[0],r3,b,axw,pw,mtr->pcr);
		break;
	case 2:
		ShowMPt3(hdc,spt[0],r3,b,axw,pw,mtr->pcr);	
		break;
	case 3:
		ShowMPt4(hdc,spt[0],r3,b,axw,pw,mtr->pcr);	
		break;
	case 4:
		ShowMPt5(hdc,spt[0],r3,b,axw,pw,mtr->pcr);
	}
}

//显示meter2
void DObj::ShowMeter2(HDC hdc, int dx, int dy)
{
	char p[100];
	CRect rt,rt1;
	LOGFONT lf;
	CPoint pt1,pt2,pt3;
	N_METER2 *mtr;
	int i,j,n,h,w,x1,x2,h1,h2,h3,h4;
	double a,xl,vl,bx,bl,val,v1,v2,vmax,vmin;
	if(dbm->lookdown==1||dbm->curang!=0) return; //只在正常时显示
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
	
	lf=cobj.font1;
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
	val=mtr->curval;
	val=val<mtr->Vmin  ? mtr->Vmin:val;
	val=val>mtr->Vmax  ? mtr->Vmax:val;
	x2=(int)(x1+bl*(val-mtr->Vmin));
	GLRectc(hdc,CRect(x2-1,h2,x2+2,h4),mtr->pcr,mtr->pcr,0);
}

//垂直刻度表
void DObj::ShowMeter3(HDC hdc, int dx, int dy)
{
	char p[100];
	CRect rt,rt1;
	LOGFONT lf;
	CPoint pt1,pt2,pt3;
	N_METER3 *mtr;
	int i,j,n,h,w,y1,y2,w1,w2,w3,w4,fh;
	double a,yl,vl,bx,bl,val,v1,v2,vmax,vmin;
	if(dbm->lookdown==1||dbm->curang!=0) return; //只在正常时显示
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
	
	lf=cobj.font1;
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
	val=mtr->curval;
	val=val<mtr->Vmin  ? mtr->Vmin:val;
	val=val>mtr->Vmax  ? mtr->Vmax:val;
	y2=(int)(y1+bl*(val-mtr->Vmin));
	GLRectc(hdc,CRect(w2,y2-1,w4,y2+2),mtr->pcr,mtr->pcr,0);
}

//显示数码仪表
void DObj::ShowMeter4(HDC hdc, int dx, int dy)
{
	char p[256],p1[10];
	DWORD color;
	CRect rt,rt1;
	LOGFONT lf;
	int i,j,x1,x2,sn,bz;
	double xl;
	N_METER4 *mtr;
	if(dbm->lookdown==1||dbm->curang!=0) return; //只在正常时显示
	mtr=(N_METER4 *)buf;
	rt=CreateDrawRect(4,mtr->pt,dx,dy);
	mtr->num=mtr->num>10 ? 10:mtr->num;
	mtr->num=mtr->num<1 ? 1:mtr->num;
	mtr->numdot=mtr->numdot>4 ? 4:mtr->numdot;
	if(mtr->numdot>=mtr->num) mtr->numdot=0;
	xl=(double)rt.Width()/(double)mtr->num;
	lf=cobj.font1;
	strcpy(lf.lfFaceName,"Airal");
	lf.lfWidth=(int)(xl*0.5);
	lf.lfHeight=(int)(rt.Height()*0.8);
	GLDDraw3DRect(hdc,rt,mtr->bcr,mtr->bcr);
	x1=rt.left;
	rt1.top=rt.top;
	rt1.bottom=rt.bottom;
	GetDoubleStr(mtr->curval,p,mtr->numdot);
	sn=strlen(p);
	j=sn-1;
	p1[1]=0;
	bz=mtr->numdot>0 ? 0:1;
	for(i=mtr->num;i>0;i--)
	{
		x1=rt.left+(int)((i-1)*xl);
		x2=rt.left+(int)(i*xl);
		if(i!=mtr->num) GLLine(hdc,x2,rt.top,x2,rt.bottom,mtr->bcr);
		rt1.left=x1;
		rt1.right=x2;
		if(j<0) p1[0]='0';
		else p1[0]=p[j];
		if(p1[0]=='.')
		{
			j--;
			p1[0]=p[j];
			bz=1;
		}
		color=bz==0 ? mtr->ncr[1]:mtr->ncr[0];
		GLDDrawText(hdc,&rt1,&lf,p1,color,0,DT_CENTER|DT_VCENTER|DT_SINGLELINE);
		j--;
	}
}

//将矩形转化为可显示的多边形
//dr为文字显示方向 0=正常 1=水平
void DObj::DrtToDPt(DRECT &rt,DPOINT *pt,int dr)
{
	switch(dr)
	{
	case 0:
		pt[0].x=rt.left;pt[0].y=rt.top;
		pt[1].x=rt.right;pt[1].y=rt.top;
		pt[2].x=rt.right;pt[2].y=rt.bottom;
		pt[3].x=rt.left;pt[3].y=rt.bottom;
		break;
	case 1:
		pt[0].x=rt.left;pt[0].y=rt.bottom;
		pt[1].x=rt.left;pt[1].y=rt.top;
		pt[2].x=rt.right;pt[2].y=rt.top;
		pt[3].x=rt.right;pt[3].y=rt.bottom;
		break;
	}
}

//模拟量显示的调整矩形
void DObj::OffsetRt(DRECT &rt,int wh, int direct, int qh)
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

void DObj::ShowDigitPQ(HDC hdc,DRECT &rt,LOGFONT *lf,float vp,float vq,char xs,
					   DWORD color1,DWORD color2,BYTE direction,int dx,int dy)
{
	SIZE sz;
	DPOINT dpt[4];
	char p[100],p1[100];
	GetDoubleStr(vp,p,xs);
	DrtToDPt(rt,dpt,direction);
	SDrawText(hdc,dpt,p,lf,dx,dy,color1,DT_LEFT);
	sz=GLDGetTextSize(hdc,lf,p);
	if(vq>=0) strcpy(p,"+j");
	else strcpy(p,"-j");
	GetDoubleStr(vq<0 ? -vq:vq,p1,xs);
	strcat(p,p1);
	OffsetRt(rt,sz.cx,direction,1);
	DrtToDPt(rt,dpt,direction);
	SDrawText(hdc,dpt,p,lf,dx,dy,color2,DT_LEFT);
}

//显示一个数字
void DObj::ShowDigit(HDC hdc,DRECT &rt,LOGFONT *lf,float val,char *pre,char *unit,char xs,
					 DWORD color,BYTE direction,int dx,int dy)
{
	DPOINT dpt[4];
	char p[100],p1[100];
	p[0]=0;
	if(pre!=NULL) strcpy(p,pre);
	GetDoubleStr(val,p1,xs);
	strcat(p,p1);
	if(unit!=NULL) strcat(p,unit);
	DrtToDPt(rt,dpt,direction);
	SDrawText(hdc,dpt,p,lf,dx,dy,color,DT_LEFT);
}
//显示模拟量（太复杂，单独剔除编写,需要多处调用)
void DObj::ShowAnalog(HDC hdc,DRECT &rt,N_ANL *anl,int dx,int dy,int pm)
{
	int i;
	double v;
	SIZE sz;
	LOGFONT font;
	DWORD color1;
	font=anl->lf;
	font.lfHeight=(int)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(int)(font.lfWidth*dbm->curzoom);
	font.lfEscapement=anl->direction==0 ? 0:900;
	
	if(pm!=0) 	color1=0;
	else color1=anl->vr.alarmhilo==0 ? anl->ncolor:anl->acolor;
	
	switch(anl->vr.dtype)
	{
	case 0:case 4: //"发电机","负荷"
		switch(anl->xsmode){
		case 0:
			ShowDigitPQ(hdc,rt,&font,anl->vr.value[0],anl->vr.value[1],anl->xs,
				color1,color1,anl->direction,dx,dy);
		    break;
		case 1:
			ShowDigit(hdc,rt,&font,anl->vr.value[0],NULL,"",anl->xs,color1,anl->direction,dx,dy);
			break;
		case 2:
			ShowDigit(hdc,rt,&font,anl->vr.value[1],NULL,"",anl->xs,color1,anl->direction,dx,dy);
			break;
		}
		break;
	case 1: //交流线路
		switch(anl->xsmode)
		{
		case 0:
			ShowDigitPQ(hdc,rt,&font,anl->vr.value[0],anl->vr.value[1],anl->xs,
				color1,color1,anl->direction,dx,dy);
			break;
		case 1:
			ShowDigitPQ(hdc,rt,&font,anl->vr.value[2],anl->vr.value[3],anl->xs,
				color1,color1,anl->direction,dx,dy);
			break;
		case 2:
			ShowDigit(hdc,rt,&font,anl->vr.value[7],NULL,"A",anl->xs,color1,anl->direction,dx,dy);
			break;
		case 3:
			ShowDigit(hdc,rt,&font,anl->vr.value[0],NULL,"",anl->xs,color1,anl->direction,dx,dy);
			break;
		case 4:
			ShowDigit(hdc,rt,&font,anl->vr.value[1],NULL,"",anl->xs,color1,anl->direction,dx,dy);
			break;
		case 5:
			ShowDigit(hdc,rt,&font,anl->vr.value[2],NULL,"",anl->xs,color1,anl->direction,dx,dy);
			break;
		case 6:
			ShowDigit(hdc,rt,&font,anl->vr.value[3],NULL,"",anl->xs,color1,anl->direction,dx,dy);
			break;
		}
		break;
	case 2: //直流线路
		switch(anl->xsmode)
		{
		case 0:	case 1:
			ShowDigit(hdc,rt,&font,anl->vr.value[0],NULL,"MW",anl->xs,color1,anl->direction,dx,dy);
			break;
		case 2:
			ShowDigit(hdc,rt,&font,anl->vr.value[7],NULL,"A",anl->xs,color1,anl->direction,dx,dy);
			break;
		}
		break;
	case 3: //节点
		switch(anl->xsmode){
		case 0: // 显示电压等级
			color1=pm!=0 ? 0:anl->ncolor;
			ShowDigit(hdc,rt,&font,anl->vr.value[0],"等级:","kV",anl->xs,color1,anl->direction,dx,dy);
			break;
		case 1:
			ShowDigit(hdc,rt,&font,anl->vr.value[1],"","pu",anl->xs,color1,anl->direction,dx,dy);
			break;
		case 2:
			//ShowDigit(hdc,rt,&font,anl->vr.value[7],"","",anl->xs,color1,anl->direction,dx,dy);
			ShowDigit(hdc,rt,&font,anl->vr.value[7],"","",anl->xs,RGB(0,255,255),anl->direction,dx,dy);
			break;
		case 3:
			ShowDigit(hdc,rt,&font,anl->vr.value[2],"","deg",anl->xs,color1,anl->direction,dx,dy);
			break;
		}
		break;
	case 5:  //变压器
		switch(anl->xsmode){
		case 0: 
		ShowDigit(hdc,rt,&font,anl->vr.value[0],NULL,NULL,anl->xs,color1,anl->direction,dx,dy);
		break;
		case 1:
			ShowDigit(hdc,rt,&font,anl->vr.value[2],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 2:
			ShowDigit(hdc,rt,&font,anl->vr.value[6],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 3:
			ShowDigit(hdc,rt,&font,anl->vr.value[9],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 4:
			ShowDigit(hdc,rt,&font,anl->vr.value[7],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 5:
			ShowDigit(hdc,rt,&font,anl->vr.value[8],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 6:
			ShowDigit(hdc,rt,&font,anl->vr.value[10],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		}
		break;
	case 6: //三绕组变压器
		switch(anl->xsmode){
		case 0:
			{
		sz=GLDGetTextSize(hdc,&font,"M");
		ShowDigit(hdc,rt,&font,anl->vr.value[0],"",NULL,0,color1,anl->direction,dx,dy);
		/*OffsetRt(rt,sz.cy,anl->direction,0);
		ShowDigit(hdc,rt,&font,anl->vr.value[1],"中:",NULL,0,color1,anl->direction,dx,dy);
		OffsetRt(rt,sz.cy,anl->direction,0);
		ShowDigit(hdc,rt,&font,anl->vr.value[2],"低:",NULL,0,color1,anl->direction,dx,dy);*/
			}
			break;
		case 1:
			ShowDigit(hdc,rt,&font,anl->vr.value[4],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 2:
			ShowDigit(hdc,rt,&font,anl->vr.value[8],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 3:
			ShowDigit(hdc,rt,&font,anl->vr.value[13],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 4:
			ShowDigit(hdc,rt,&font,anl->vr.value[11],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 5:
			ShowDigit(hdc,rt,&font,anl->vr.value[12],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 6:
			ShowDigit(hdc,rt,&font,anl->vr.value[14],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 7:
			ShowDigit(hdc,rt,&font,anl->vr.value[9],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 8:
			ShowDigit(hdc,rt,&font,anl->vr.value[10],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		case 9:
			ShowDigit(hdc,rt,&font,anl->vr.value[15],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
		}
		break;
	case 7:   case 8: //电容器，电抗器投入组数
		switch(anl->xsmode){
		case 0:
			ShowDigit(hdc,rt,&font,anl->vr.value[0],NULL,NULL,anl->xs,color1,anl->direction,dx,dy);
			break;
		case 1:
			if(anl->vr.value[1]!=0){
				v=anl->vr.value[0]/anl->vr.value[1];
				ShowDigit(hdc,rt,&font,(float)v,NULL,NULL,0,color1,anl->direction,dx,dy);
			}
			break;
		}
		break;
	case 9:  //显示SVC
		ShowDigit(hdc,rt,&font,anl->vr.value[0],NULL,"Mvar",anl->xs,color1,anl->direction,dx,dy);
		break;
	case 10: //区域
		color1=pm!=0 ? 0:anl->ncolor;
		ShowDigit(hdc,rt,&font,anl->vr.value[0],NULL,"",anl->xs,color1,anl->direction,dx,dy);
		break;
	case 11:  //系统
		color1=pm!=0 ? 0:anl->ncolor;
		i=anl->xsmode;
		switch(i){
		case 0:case 1:case 3:case 4:
			ShowDigit(hdc,rt,&font,anl->vr.value[i],NULL,"MW",anl->xs,color1,anl->direction,dx,dy);
			break;
		case 2:case 5:
			ShowDigit(hdc,rt,&font,anl->vr.value[i],NULL,"MVar",anl->xs,color1,anl->direction,dx,dy);
			break;
		}
		break;
	case 13:
		{
			color1=pm!=0 ? 0:anl->ncolor;
			switch(anl->xsmode)
			{
			case 0:
				ShowDigit(hdc,rt,&font,anl->vr.value[0],"","",anl->xs,color1,anl->direction,dx,dy);
				break;
			case 1:
				ShowDigit(hdc,rt,&font,anl->vr.value[2],"","",anl->xs,color1,anl->direction,dx,dy);
				break;
			case 2:
				ShowDigit(hdc,rt,&font,anl->vr.value[3],"","",anl->xs,color1,anl->direction,dx,dy);
				break;
			}
		}
		break;
	case 12:
	case 14:
	case 15:
		color1=pm!=0 ? 0:anl->ncolor;
		ShowDigit(hdc,rt,&font,anl->vr.value[0],"","",anl->xs,color1,anl->direction,dx,dy);
		break;
	}
}

//显示模擬量
void DObj::ShowAnl(HDC hdc, int dx, int dy,int pm)
{
	CDRect drt;
	N_ANL *anl;
	anl=(N_ANL *)buf;
	drt=CreateDrawNRt(4,anl->pt,dbm->curzoom);
	ShowAnalog(hdc,drt,anl,dx,dy,pm);
}

//显示MTTEXT
void DObj::ShowMTText(HDC hdc, int dx, int dy,int pm)
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
	GetSubTxt(text->text,tx,text->offset,text->lstsum,text->sta);
	//sprintf(tx,"%d %d ",text->sta,text->lstsum);

	len=strlen(tx);
	if(len<=0) return;
	font.lfHeight=(long)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(long)(font.lfWidth*dbm->curzoom);
	GLDDrawText(hdc,&rt,&font,tx,c1,0,DT_LEFT);
}


void DObj::GetSubTxt(char *obuf,char *Outbuf,int *offset,int maxlst,int index)
{
	char *lp;
	if(index>maxlst||index<0)
	{
		sprintf(Outbuf,"Error (%d)",index);
		return;
	}
	lp=obuf+offset[index];
	strcpy(Outbuf,lp);
}


//显示棒图
void DObj::ShowBar(HDC hdc, int dx, int dy)
{
	DRECT rt1;
	int x1,x2,y1,y2;
	double w,h,vs,vc,kl;
	DWORD c1;
	CDRect rt;
	N_BAR *bar;
	bar=(N_BAR *)buf;
	rt=CreateDrawNRt(4,bar->pt,dbm->curzoom);
	if(bar->dsrc.xsmode>0)//动态排序断面
	{
		CDRect rtTxt=rt;
		w=rt.Width()/3;
		rtTxt.right=rtTxt.left+w;

		//显示动态排序断面名字
		double w1,h1;
		LOGFONT font;
		DPOINT dpt[4];
		font=cobj.font1;
		font.lfHeight=(int)(rt.Height());
		font.lfWidth=(int)(rt.Height()/2);
		SIZE sz=GLDGetTextSize(hdc,&font,bar->dsrc.name);
		w1=rtTxt.Width()-sz.cx;
		h1=(rtTxt.Height()-sz.cy)/2;
		dpt[0].x=rtTxt.left+w1;dpt[0].y=rtTxt.top+h1;
		dpt[1].x=rtTxt.right;dpt[1].y=dpt[0].y;
		dpt[2].x=dpt[0].x;dpt[2].y=rt.bottom-h1;
		dpt[3].x=dpt[0].x;dpt[3].y=dpt[2].y;
		SDrawText(hdc,dpt,bar->dsrc.name,&font,dx,dy,RGB(255,255,255),DT_RIGHT);
		rt.left=rt.left+w+1;
	}
	h=rt.bottom-rt.top;
	w=rt.right-rt.left;
	vs=(double)(bar->max-bar->min);
	if(vs<=0) return;
	vc=bar->rval.curval;
	
	vc=vc>bar->max ? bar->max:vc;
	vc=vc<bar->min ? bar->min:vc;
	//c1=vc>bar->aval ? bar->acolor:bar->ncolor;
	if(vc==bar->max || vc==bar->min)
		c1=bar->acolor;
	else
		c1=bar->ncolor;

	switch(bar->xy)
	{
	case 0:  //水平方向
		{
			kl=(double)(w/vs);
			x1=(int)(bar->aval*kl);	
			x2=(int)((vc-bar->min)*kl);

			if(bar->style==1)
			{
				rt1=rt;
				if(bar->rval.curval>=0)
				{
					if(bar->max*bar->min<0)
						x2=(int)(vc*(0.5*w/bar->max));
					else
						x2=(int)(vc*kl*0.5);
					rt1.left=rt.CenterPoint().x;
					rt1.right=rt.CenterPoint().x+x2;
				}
				else
				{
					if(bar->max*bar->min<0)
						x2=(int)(vc*(0.5*w/fabs(bar->min)));
					else
						x2=(int)(vc*kl*0.5);
					rt1.left=rt.CenterPoint().x+x2;
					rt1.right=rt.CenterPoint().x;
				}
			}
			else if(bar->style==2)
			{
				rt1=rt;
				rt1.left=rt.right-x2;
			}
			else
			{
				rt1=rt;
				rt1.right=rt.left+x2;
			}
		}
		break;
	case 1: //垂直方向
		{
			kl=(double)(h/vs);
			y1=(int)(bar->aval*kl);	
			y2=(int)((vc-bar->min)*kl);

			if(bar->style==1)
			{
				rt1=rt;
				if(bar->rval.curval>=0)
				{
					if(bar->max*bar->min<0)
						y2=(int)(vc*(0.5*h/bar->max));
					else
						y2=(int)(vc*kl*0.5);
					rt1.top=rt.CenterPoint().y-y2;
					rt1.bottom=rt.CenterPoint().y;
				}
				else
				{
					if(bar->max*bar->min<0)
						y2=(int)(vc*(0.5*h/fabs(bar->min)));
					else
						y2=(int)(vc*kl*0.5);
					rt1.top=rt.CenterPoint().y;
					rt1.bottom=rt.CenterPoint().y-y2;
				}
			}
			else if(bar->style==2)
			{
				rt1=rt;
				rt1.bottom=rt.top+y2;
			}
			else
			{
				rt1=rt;
				rt1.top=rt.bottom-y2;
			}
		}
		break;
	default:return;
	};
	
	DrtToDPt(rt1,npt,0);
	dbm->msr->DPtToScrPt(npt,mpt,4,dx,dy);
	DrawPoly(hdc,mpt,4,bar->outline==1 ? 0:c1,c1,1,1);
	if(bar->outline==1)
	{
		DrtToDPt(rt,npt,0);
		dbm->msr->DPtToScrPt(npt,mpt,4,dx,dy);
		DrawPoly(hdc,mpt,4,c1,c1,0,1);
	}
}



//画2饼图
//c1大填充颜色 c2=小块填充颜色 c3=边缘颜色
void DObj::DrawPie(HDC hdc,CDRect &rt,DWORD c1,DWORD c2,DWORD c3,double pw,int dx,int dy)
{
	DPOINT  tp[74];
	DPOINT  cpt;
	int n,end;
	n=GetCircleAllPt(tp,rt);
	if(n!=72) return;
	memcpy(npt,tp,72*sizeof(DPOINT));
	dbm->msr->DPtToScrPt(npt,mpt,n,dx,dy);
	DrawPoly(hdc,mpt,n,c3,c1,1,1);
	end=(int)(72*pw);
	if(end<0||end>72) return;
	if(end==0&&pw!=0) end=1;
	if(end!=72&&end!=0&&rt.Width()>3){
		cpt=rt.CenterPoint();
		tp[end].x=cpt.x;
		tp[end].y=cpt.y;
		tp[end+1]=tp[0];
		dbm->msr->DPtToScrPt(tp,mpt,end+2,dx,dy);
		DrawPoly(hdc,mpt,end+2,c3,c2,1,1);
	}
}

//画2饼图(打印用)
//c1大填充颜色 c2=小块填充颜色 c3=边缘颜色
void DObj::DrawPieP(HDC hdc,CRect &rt,DWORD c1,DWORD c2,DWORD c3,double pw,int pm)
{
	double w,h,a;
	int x1,y1,x2,y2;
	CPoint pt;
	HBRUSH hb1,hb2,oldb;
	HPEN hp,oldp;
	DWORD cr1,cr2,cr3;
	if(pm==1){
		cr1=0xffffff;
		cr2=0;
		cr3=0;
	}else{
		cr1=c1;
		cr2=c2;
		cr3=c3;
	}
	hb1=CreateSolidBrush(cr1);
	hb2=CreateSolidBrush(cr2);
	hp=CreatePen(PS_SOLID,(int)dbm->curzoom,cr3);
	oldb=(HBRUSH)SelectObject(hdc,hb1);
	oldp=(HPEN)SelectObject(hdc,hp);
	Ellipse(hdc,rt.left,rt.top,rt.right,rt.bottom);
	if(pw!=0)
	{
		a=pw>=0 ? pw:-pw;
		a=mpi*2*a;
		pt=rt.CenterPoint();
		w=(double)rt.Width()/2.0;
		h=(double)rt.Height()/2.0;
		x2=pt.x+(int)(w*cos(a));
		y2=pt.y-(int)(h*sin(a));
		x1=pt.x+(int)w;
		y1=pt.y;
		SelectObject(hdc,hb2);
		Pie(hdc,rt.left,rt.top,rt.right,rt.bottom,x1,y1,x2,y2);
	}
	SelectObject(hdc,oldp);
	SelectObject(hdc,oldb);
	DeleteObject(hb1);
	DeleteObject(hb2);
	DeleteObject(hp);
}


//显示饼图
void DObj::ShowPie(HDC hdc, int dx, int dy)
{
	SIZE sz;
	char p[100];
	LOGFONT font;
	CDRect rt;
	DWORD c1,c2;
	double a,b,w1,h1;
	DPOINT dpt[4];
	int w,len;
	N_PIE *pie;
	pie=(N_PIE*)buf;
	b=GetPercent(pie->pcur,pie->maxv);
	a=b>1 ? 1:b;
	c1=pie->color[0];
	c2=pie->color[1];
	rt=CreateDrawNRt(4,pie->pt,dbm->curzoom);
	if(a==1) c1=c2;
	DrawPie(hdc,rt,c1,c2,c2,b,dx,dy);
	//显示百分饼图文字
	font=pie->lf;
	font.lfHeight=(int)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(int)(font.lfWidth*dbm->curzoom);
	sprintf(p,"%d%%",(int)(b*100));
	len=strlen(p);
	w=(int)((rt.Width())/4);
	sz=GLDGetTextSize(hdc,&font,p);
	w1=(rt.Width()-sz.cx)/2;
	h1=(rt.Height()-sz.cy)/2;
	dpt[0].x=rt.left+w1;dpt[0].y=rt.top+h1;
	dpt[1].x=rt.right-w1;dpt[1].y=dpt[0].y;
	dpt[2].x=dpt[0].x;dpt[2].y=rt.bottom-h1;
	dpt[3].x=dpt[0].x;dpt[3].y=dpt[2].y;
	SDrawText(hdc,dpt,p,&font,dx,dy,pie->fcolor,DT_LEFT);
}

void DObj::ShowSysPie(HDC hdc, int dx, int dy)
{
	CDRect rt;
	N_SYSPIE *pie;
	pie=(N_SYSPIE*)buf;
	rt=CreateDrawNRt(4,pie->pt,dbm->curzoom);
	DrawMPie(hdc,rt,pie->color,pie->vl,pie->num,pie->lf,pie->fcolor,dx,dy);
}

void DObj::DrawMPie(HDC hdc,CDRect &rt,DWORD *cr,double *vp,int num,LOGFONT &lf,DWORD fcolor,int dx,int dy)
{
	SIZE sz;
	DPOINT dpt[4];
	char p[100];
	CDRect drt;
	CRect rt1,trt[8];
	LOGFONT font;
	double v;
	double w1,h1;
	CPoint   ipt[74],spt[74],cpt;
	DPOINT  tp[74],cpt1;
	int    pt[24];
	int i,j,n,m;
	n=GetCircleAllPt(tp,rt);
	if(n!=72) return;
	dbm->msr->DPtToScrPt(tp,ipt,n,dx,dy);
	ipt[72]=ipt[0];
	DrawPoly(hdc,ipt,n,cr[0],cr[0],1,1);
	v=0;
	for(i=0;i<num;i++) v+=vp[i];
	if(v==0) return;
	pt[0]=0;
	v=0;
	for(i=0;i<num;i++)
	{
		v+=vp[i];
		pt[i+1]=(int)(72*v);
		if(pt[i+1]>=72) pt[i+1]=72;
	}
	pt[num]=72;
	pt[num+1]=0;
	//画小饼图
	font=lf;
	font.lfHeight=(long)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(long)(font.lfWidth*dbm->curzoom);
	cpt1=rt.CenterPoint();
	dbm->msr->DPtToScrPt(&cpt1,&cpt,1,dx,dy);
	for(i=0;i<num;i++)
	{
		spt[0]=cpt;
		m=pt[i+1]-pt[i];
		n=pt[i];
		for(j=0;j<m+1;j++)
		{
			spt[j+1]=ipt[n+j];
			
		}
		DrawPoly(hdc,spt,m+2,cr[0],cr[i+1],1,1);
		trt[i]=CreateNRt(m+2,spt);
		
	}
	if(dbm->lookdown==1) return;

	//显示文字
	n=GetCircleAllPt(tp,rt);
	tp[72]=tp[0];
	cpt1=rt.CenterPoint();
	font=lf;
	font.lfHeight=(int)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(int)(font.lfWidth*dbm->curzoom);
	for(i=0;i<num;i++)
	{
		spt[0].x=(int)cpt1.x;
		spt[0].y=(int)cpt1.y;
		m=pt[i+1]-pt[i];
		n=pt[i];
		for(j=0;j<m+1;j++)
		{
			spt[j+1].x=(int)tp[n+j].x;
			spt[j+1].y=(int)tp[n+j].y;
		}
		rt1=CreateNRt(m+2,spt);
		cpt=rt1.CenterPoint();
		sprintf(p,"%2.0f%%",vp[i]*100);
		sz=GLDGetTextSize(hdc,&font,p);
		w1=(sz.cx)/2+3;
		h1=(sz.cy)/2;
		dpt[0].x=cpt.x-w1;dpt[0].y=cpt.y-h1;
		dpt[1].x=cpt.x+w1;dpt[1].y=cpt.y-h1;
		dpt[2].x=cpt.x+w1;dpt[2].y=cpt.y+h1;
		dpt[3].x=cpt.x-w1;dpt[3].y=cpt.y+h1;
		SDrawText(hdc,dpt,p,&font,dx,dy,fcolor,DT_LEFT);
	}	
}

//显示日期
void DObj::ShowDate(HDC hdc, int dx, int dy,int pm)
{
	int i;
	double x,y;
	SIZE sz;
	CDRect rt;
	DWORD  c1;
	CDPoint dpt[4];
	LOGFONT font;
	char p[100],mn[10],da[10];
	N_DATE *date;
	date=(N_DATE *)buf;
	PointActToScr(date->pt,dpt,4,dbm->curzoom);
	memcpy(npt,dpt,4*sizeof(DPOINT));
	dbm->msr->DPtToScrPt(npt,mpt,4,dx,dy);
	if(pm==0) c1=date->outcolor;else c1=0;
	if(date->tran==0) NPolygonc(hdc,mpt,4,date->bcolor,date->bcolor);
	switch(date->outline)
	{
	case 1:	Draw3dRect(hdc,mpt,c1,c1);		break;
	case 2:	Draw3dRect(hdc,mpt,c1,0xffffff);  break;
	case 3: Draw3dRect(hdc,mpt,0xffffff,c1);	break;
	};
	rt=CreateDrawNRt(4,date->pt,dbm->curzoom);
	GetDtStr(date->tm.GetMonth(),mn);
	GetDtStr(date->tm.GetDay(),da);
	switch(date->fmt)
	{
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
	font.lfHeight=(int)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(int)(font.lfWidth*dbm->curzoom);
	sz=GLDGetTextSize(hdc,&font,p);
	x=(rt.Width()-sz.cx)/2;
	y=(rt.Height()-sz.cy)/2;
	if(pm==0) c1=date->fcolor;else c1=0;
	dpt[0].Offset(x,y);
	dpt[1].Offset(-x,y);
	dpt[2].Offset(-x,-y);
	dpt[3].Offset(x,-y);
	SDrawText(hdc,dpt,p,&font,dx,dy,c1,DT_LEFT);
}


//显示日期
void DObj::ShowTime(HDC hdc, int dx, int dy,int pm)
{
	double x,y;
	SIZE sz;
	CDRect rt;
	DWORD  c1;
	CDPoint dpt[4];
	LOGFONT font;
	char p[100],hr[10],min[10],sec[10];
	N_TIME *date;
	date=(N_TIME *)buf;
	PointActToScr(date->pt,dpt,4,dbm->curzoom);
	memcpy(npt,dpt,4*sizeof(DPOINT));
	dbm->msr->DPtToScrPt(npt,mpt,4,dx,dy);
	GetDtStr(date->tm.GetHour(),hr);
	GetDtStr(date->tm.GetMinute(),min);
	GetDtStr(date->tm.GetSecond(),sec);
	if(date->tran==0) NPolygonc(hdc,mpt,4,date->bcolor,date->bcolor);
	if(pm==0) c1=date->outcolor;else c1=0;
	switch(date->outline)
	{
	case 1:	Draw3dRect(hdc,mpt,c1,c1);			break;
	case 2:	Draw3dRect(hdc,mpt,c1,0xffffff);	break;
	case 3: Draw3dRect(hdc,mpt,0xffffff,c1);	break;
	};
	switch(date->fmt)
	{
	case 1:sprintf(p,"%s:%s",hr,min);			break;
	case 2:sprintf(p,"%s时%s分%s秒",hr,min,sec);break;
	case 3:sprintf(p,"%s点%s分%s秒",hr,min,sec);break;
	case 4:strcpy(p,"02分02秒");				break;	
	default:
		sprintf(p,"%s:%s:%s",hr,min,sec);
	};
	rt=CreateDrawNRt(4,date->pt,dbm->curzoom);
	font=date->font;
	font.lfHeight=(int)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(int)(font.lfWidth*dbm->curzoom);
	sz=GLDGetTextSize(hdc,&font,p);
	x=(rt.Width()-sz.cx)/2;
	y=(rt.Height()-sz.cy)/2;
	rt.left++;
	rt.top++;
	rt.right-=3;
	rt.bottom-=3;
	if(pm==0) c1=date->fcolor;else c1=0;
	dpt[0].Offset(x,y);
	dpt[1].Offset(-x,y);
	dpt[2].Offset(-x,-y);
	dpt[3].Offset(x,-y);
	SDrawText(hdc,dpt,p,&font,dx,dy,c1,DT_LEFT);
}

//生成可画的屏幕矩形
CRect DObj::CreateDrawRect(int ptsum,DPOINT *pt,int dx,int dy)
{
	CRect rt;
	CDRect art;
	art=CreateNRt(ptsum,pt);
	art.ActRtToScr(dbm->curzoom);
	art.GetRECT(rt);
	rt.OffsetRect(dx,dy);
	return rt;
}

void DObj::ShowGifAnl(HDC hdc, int dx, int dy)
{
	CRect rt;
	N_GIFAML *ga;
	ga=(N_GIFAML *)buf;
	if(dbm->curang!=0||dbm->lookdown==1) return;
	rt=CreateDrawRect(4,ga->pt,dx,dy);
	if(ga->gfm!=NULL)
	{
		BitBlt(ga->gfm->m_hDC,0,0,rt.Width(),rt.Height(),hdc,rt.left,rt.top,SRCCOPY);
		ga->gfm->ShowSel(hdc,ga->gfm->curfrm,rt.left,rt.top,rt.Width(),rt.Height());
	}
}

//显示滚动文本
void DObj::ShowScrText(HDC hdc, int dx, int dy,int pm)
{
	CDRect art;
	DWORD c1;
	CRect rt;
	LOGFONT font;
	N_SRLTEXT *lp;
	lp=(N_SRLTEXT *)buf;
	if(dbm->lookdown==1||dbm->curang!=0) return;
	rt=CreateDrawRect(4,lp->pt,dx,dy);
	font=lp->lf;
	font.lfHeight=(int)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(int)(font.lfWidth*dbm->curzoom);
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

//显示按钮
void DObj::ShowPush(HDC hdc, int dx, int dy)
{
	CRect rt;
	int type;
	LOGFONT font;
	N_PUSH *lp;
	lp=(N_PUSH *)buf;
	if(dbm->lookdown==1||dbm->curang!=0) return;
	rt=CreateDrawRect(4,lp->pt,dx,dy);
	font=lp->lf;
	font.lfHeight=(int)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(int)(font.lfWidth*dbm->curzoom);
	type=lp->style;
    switch(type)
	{
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
	}
}

void DObj::ShowFlowLine(HDC hdc,int dx, int dy)
{
	DWORD color;
	int v,tpsum;
	N_FLOW *flw;
	flw=(N_FLOW*)buf;
	tpsum=flw->ptsum>20 ? 20:flw->ptsum;
	/////////设定颜色///////////////
	if(flw->vr.ele==0) color=0x7f7f7f;
	else
	{
		v=flw->vl;
		v=v>20 ? 0:v;
		color=cobj.vcolor[v];
	}
	///////////////////////////////////////////////////////////////////
	PointActToScr(flw->pt,npt,tpsum,dbm->curzoom);
	dbm->msr->DPtToScrPt(npt,mpt,tpsum,dx,dy);
 	GLDrawDbx(hdc,tpsum,mpt,1,color);	
}

void DObj::ShowFlowLineP(HDC hdc,int dx, int dy,int pm)
{
	DWORD color;
	int v,tpsum;
	N_FLOW *flw;
	flw=(N_FLOW*)buf;
	tpsum=flw->ptsum>20 ? 20:flw->ptsum;
	/////////设定颜色///////////////
	if(flw->vr.ele==0) color=0x7f7f7f;
	else
	{
		v=flw->vl;
		v=v>20 ? 0:v;
		color=cobj.vcolor[v];
	}
	if(pm==1) color=0;
	///////////////////////////////////////////////////////////////////
	PointActToScr(flw->pt,npt,tpsum,dbm->curzoom);
	PtOffset(npt,mpt,tpsum,dx,dy);
	GLDrawDbx(hdc,tpsum,mpt,(int)dbm->curzoom,color);
}


//画潮流线(箭头方式)
void DObj::DrawFlow(HDC hdc,POINT *pt,int ptsum,int start,int arrow,int size,
					int dis,DWORD color1,DWORD color2,int dx,int dy)
{
	int i,j,m,n,s;
	double len,xl,yl,w,h,x,y,a;
	DPOINT  p1,p2;
	DPOINT  lpt[4];
	POINT   pi[4];
	HBRUSH hb,oldhb;
	HPEN   hp,oldhp;
	if(size==0) return;
	hb=CreateSolidBrush(color2);
	hp=CreatePen(PS_SOLID,1,color1);
	oldhb=(HBRUSH)SelectObject(hdc,hb);
	oldhp=(HPEN)SelectObject(hdc,hp);
	s=start;
	for(i=0;i<ptsum-1;i++){
		w=pt[i+1].x-pt[i].x;
		h=pt[i+1].y-pt[i].y;
		len=sqrt(w*w+h*h);
		if(len==0) continue;
		a=asin(h/len); //计算角度
		n=(int)len;
		xl=w/len;
		yl=h/len;
		if(pt[i+1].x>=pt[i].x){
			p1.x=size*sin(a); p1.y=-size*cos(a);
			p2.x=-size*sin(a);p2.y=size*cos(a);
		}else{
			p1.x=size*sin(a);p1.y=size*cos(a);
			p2.x=-size*sin(a); p2.y=-size*cos(a);
		};
	    for(j=s;j<n;j=j+dis){
		  m=j-arrow*size;
          x=pt[i].x+xl*m;
		  y=pt[i].y+yl*m;
		  lpt[0].x=x+p1.x;lpt[0].y=y+p1.y;
		  lpt[1].x=x+p2.x;lpt[1].y=y+p2.y;
		  m=j+arrow*size;
		  lpt[2].x=pt[i].x+xl*m;lpt[2].y=pt[i].y+yl*m;
		  lpt[3]=lpt[0];
		  dbm->msr->DPtToScrPt(lpt,pi,4,dx,dy);
		  Polygon(hdc,pi,4);
		  Polyline(hdc,pi,4); 
		}
		s=j-n;
	}
	SelectObject(hdc,oldhb);
	SelectObject(hdc,oldhp);   
	DeleteObject(hb);
	DeleteObject(hp);
}


//显示潮流箭头
void DObj::ShowFlow(HDC hdc,int dx, int dy)
{
	DWORD color,c1,c2;
	int v,tpsum,n1,n2,pd,qd,w1,w2,w3;
	POINT tp[21];
	CDRect rt;
	CRect rt1;
	N_FLOW *flw;
	flw=(N_FLOW*)buf;
	tpsum=flw->ptsum>20 ? 20:flw->ptsum;
	
	/////////设定颜色///////////////
	if(flw->vr.ele==0)
	{
		color=0x7f7f7f;
		c1=0x7f7f7f;
		c2=0x7f7f7f;
	}else{
		v=flw->vl;
		v=v>20 ? 0:v;
		color=cobj.vcolor[v];
		c1=dbm->scf.syscolor[13];
		c2=dbm->scf.syscolor[14];
	}
	
	///////////////////////////////////////////////////////////////////
	if(flw->rf.pdir==0) pd=1;else pd=-1;
	if(flw->rf.qdir==0) qd=1;else qd=-1;
	n1=flw->rf.pjs;
	n2=flw->rf.qjs;
	w1=5-flw->pv;
	w2=5-flw->qv;
	w1=w1>5 ? 5:w1;
	w2=w2>5 ? 5:w2;
	w3=128;
	PointActToScr(flw->pt,tp,tpsum,dbm->curzoom);
	if(flw->vr.ele==0)  return;
	switch(dbm->scf.ftype){
	case 1: //只显有功
		if(flw->vr.value[0]!=0) DrawFlow(hdc,tp,tpsum,n1,pd,w1,w3,color,c1,dx,dy);
		break;
	case 2: //只显无功
		if(flw->vr.value[1]!=0) DrawFlow(hdc,tp,tpsum,n2,qd,w2,w3,color,c2,dx,dy);
		break;
	case 3: //同时显示
		if(flw->vr.value[0]!=0) DrawFlow(hdc,tp,tpsum,n1,pd,w1,w3,color,c1,dx,dy);
		if(flw->vr.value[1]!=0) DrawFlow(hdc,tp,tpsum,n2,qd,w2,w3,color,c2,dx,dy);
		break;
	}
}


//根据记录号索引号显示图元组(正常显示专用)
void DObj::PreBusEGPEx(HDC hdc,int num,int index,int dx,int dy)
{
	int type;
	DObj  *bs,bbs;
	DPOINT *spt;
	DWORD color;
	CDRect  art;
	N_BUS *bus;
	int i,j,k,m;
	BYTE dele;
	double xl,yl,w1,w2,h1,h2;
	CDRect rt,rt1,rt2;
	bus=(N_BUS*)buf;
	spt=bus->pt;
	switch(index)
	{
	 case 0:
		bs=(DObj*)dbm->egp[num].bs1;
		j=dbm->egp[num].bsum1;
		rt1.SetDRECT(dbm->egp[num].rt1);
		break;
	 case 1:
		bs=(DObj*)dbm->egp[num].bs2;
		j=dbm->egp[num].bsum2;
		rt1.SetDRECT(dbm->egp[num].rt2);
		break;
	 default:return;
	}
	
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
	k=-1;
	dele=bus->vr.ele; //返回设备带电状态
	m=bus->vl;
	m=m>24 ? 24:m;
	color=dele==1 ? cobj.vcolor[m]:0x7f7f7f;
	bbs.dbm=dbm;
	for(i=0;i<j;i++)
	{
		type=bs[i].attr.type;
		bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.MoveObject2(rt2,xl,yl);
		bbs.SetColor(color,1);
		bbs.ShowE(hdc,dx,dy);
		bbs.FreeMem();
	}
}


//根据记录号索引号显示图元组(正常显示专用)
void DObj::PreBusEGPExP(HDC hdc,int num,int index,int dx,int dy,int pm)
{
	int type;
	DObj  *bs,bbs;
	DPOINT *spt;
	DWORD color;
	CDRect  art;
	N_BUS *bus;
	int i,j,k,m;
	BYTE dele;
	double xl,yl,w1,w2,h1,h2;
	CDRect rt,rt1,rt2;
	bus=(N_BUS*)buf;
	spt=bus->pt;
	switch(index)
	{
	 case 0:
		bs=(DObj*)dbm->egp[num].bs1;
		j=dbm->egp[num].bsum1;
		rt1.SetDRECT(dbm->egp[num].rt1);
		break;
	 case 1:
		bs=(DObj*)dbm->egp[num].bs2;
		j=dbm->egp[num].bsum2;
		rt1.SetDRECT(dbm->egp[num].rt2);
		break;
	 default:return;
	}
	
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
	k=-1;
	dele=bus->vr.ele; //返回设备带电状态
	m=bus->vl;
	m=m>24 ? 24:m;
	color=dele ? cobj.vcolor[m]:0x7f7f7f;
	bbs.dbm=dbm;
	for(i=0;i<j;i++)
	{
		type=bs[i].attr.type;
		bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.MoveObject2(rt2,xl,yl);
		bbs.SetColor(color,1);
		bbs.ShowEP(hdc,dx,dy,pm);
		bbs.FreeMem();
	}
}


//显示母线
void DObj::ShowBus(HDC hdc, int dx, int dy)
{
	double a;
	int i,v,n,x,y;
	DWORD color;
	CRect rt;
	CDRect art;
	N_BUS *bus;
	bus=(N_BUS *)buf;
	if(bus->vr.ele==0) color=0x7f7f7f;
	else
	{
		v=bus->vl;
		v=v>20 ? 0:v;
		color=cobj.vcolor[v];
	}
	switch(bus->type)
	{
	case 0:case 1:
		PointActToScr(bus->pt,npt,4,dbm->curzoom);
		dbm->msr->DPtToScrPt(npt,mpt,4,dx,dy);
		GLPolygonc(hdc,mpt,4,color,color,0);
		if(bus->type==1) Draw3dRectP(hdc,mpt,color);
		
		break;
	case 2: //圆形BUS
		switch(dbm->lookdown){
		case 0: //正常显示
			rt=CreateDrawRect(4,bus->pt,dx,dy);
			PointActToScr(bus->pt,npt,2,dbm->curzoom);
			dbm->msr->DPtToScrPt(npt,mpt,2,dx,dy);
			a=GetAngle(mpt[0],mpt[1]);
			a=-a*mpi/180;
			SaveDC(hdc);
			StartRatate(hdc,a,(float)mpt[0].x,(float)mpt[0].y);
			x=rt.left;
			y=rt.top;
			rt.OffsetRect(-x,-y);
			GLEllipsec(hdc,rt,color,color,0);
			GLEllipse(hdc,rt.left,rt.top,rt.right,rt.bottom,0);
			RestoreDC(hdc,-1);
			break;
		case 1: //俯视
			art=CreateDrawNRt(4,bus->pt,dbm->curzoom);
			n=GetCircleAllPt(npt,art);
			dbm->msr->DPtToScrPt(npt,mpt,n,dx,dy);
			DrawPoly(hdc,mpt,n,0,color,1,1);
			break;
		}
		break;
	case 3:
		i=bus->eid;
		PreBusEGPEx(hdc,i,0,dx,dy);
		break;
	}
}

//显示母线
void DObj::ShowBusP(HDC hdc, int dx, int dy,int pm)
{
	int i,v;
	DWORD color;
	CRect rt;
	CDRect art;
	N_BUS *bus;
	bus=(N_BUS *)buf;
	if(bus->vr.ele==0) color=0x7f7f7f;
	else
	{
		v=bus->vl;
		v=v>20 ? 0:v;
		color=cobj.vcolor[v];
	}
	if(pm!=0) color=0;
	art=CreateDrawNRt(4,bus->pt,dbm->curzoom);
	art.Offset(dx,dy);
	art.GetRECT(rt);
	switch(bus->type)
	{
	case 0:case 1:
		GLRectc(hdc,rt,color,color,0);
		break;
	case 2: //圆形BUS
		GLEllipsec(hdc,rt,0xffffff,0xffffff,0);
		GLEllipse(hdc,rt.left,rt.top,rt.right,rt.bottom,color);
		break;
	case 3:
		i=bus->eid;
		PreBusEGPExP(hdc,i,0,dx,dy,pm);
		break;
	}
}

//显示连接线对象
void DObj::ShowConLine(HDC hdc,int dx, int dy)
{
	DWORD color;
	int v,tpsum;
	CDRect rt;
	CRect rt1;
	N_CONLINE *cnl;
	cnl=(N_CONLINE*)buf;
	tpsum=cnl->ptsum;
	if(cnl->el==0||cnl->conobj==0) color=0x7f7f7f;
	else 
	{
		v=cnl->vl;
		v=v>20 ? 0:v;
		color=cobj.vcolor[v];
	}
	PointActToScr(cnl->pt,npt,tpsum,dbm->curzoom);
	dbm->msr->DPtToScrPt(npt,mpt,tpsum,dx,dy);
 	GLDrawDbx(hdc,tpsum,mpt,1,color);
}

void DObj::ShowConLineP(HDC hdc,int dx, int dy,int pm)
{
	DWORD color;
	int v,tpsum;
	CDRect rt;
	CRect rt1;
	N_CONLINE *cnl;
	cnl=(N_CONLINE*)buf;
	tpsum=cnl->ptsum;
	if(cnl->el==0||cnl->conobj==0) color=0x7f7f7f;
	else 
	{
		v=cnl->vl;
		v=v>20 ? 0:v;
		color=cobj.vcolor[v];
	}
	if(pm!=0) color=0;
	PointActToScr(cnl->pt,npt,tpsum,dbm->curzoom);
	PtOffset(npt,mpt,tpsum,dx,dy);
	GLDrawDbx(hdc,tpsum,mpt,(int)dbm->curzoom,color);
}

//显示百分饼图
void DObj::ShowPctPieP(HDC hdc, int dx, int dy,int pm)
{
	SIZE sz;
	char p[100];
	LOGFONT font;
	CDRect rt;
	CRect crt;
	DWORD c1,c2;
	double a,b,w1,h1;
	DPOINT dpt[4];
	int w,len;
	N_PCTPIE *pie;
	pie=(N_PCTPIE*)buf;
	b=GetPercent(pie->curval,pie->maxv);
	if(b<dbm->scf.vppe) return;
	a=b>1 ? 1:b;
	c1=pie->color2;
	c2=GetPctPieColor(pie->color1,a);
	rt=CreateDrawNRt(4,pie->pt,dbm->curzoom);
	rt.Offset(dx,dy);
	rt.GetRECT(crt);
	if(a==1) c1=c2;
	DrawPieP(hdc,crt,c1,c2,c2,b,pm);
	//显示百分饼图文字
	if(a>=0.8)
	{
		SaveDC(hdc);
		SetROP2(hdc,R2_XORPEN);
		rt.Offset(-dx,-dy);
		font=pie->lf;
		sprintf(p,"%d%%",(int)(b*100));
		len=strlen(p);
		w=(int)((rt.Width())/4);
		font.lfHeight=w*2;
		font.lfWidth=w;
		sz=GLDGetTextSize(hdc,&font,p);
		w1=(rt.Width()-sz.cx)/2;
		h1=(rt.Height()-sz.cy)/2;
		dpt[0].x=rt.left+w1;dpt[0].y=rt.top+h1;
		dpt[1].x=rt.right-w1;dpt[1].y=dpt[0].y;
		dpt[2].x=dpt[0].x;dpt[2].y=rt.bottom-h1;
		dpt[3].x=dpt[0].x;dpt[3].y=dpt[2].y;
		SDrawText(hdc,dpt,p,&font,dx,dy,pie->fcolor,DT_LEFT);
		RestoreDC(hdc,-1);
	}
}


//显示百分饼图
void DObj::ShowPctPie(HDC hdc, int dx, int dy)
{
	SIZE sz;
	char p[100];
	LOGFONT font;
	CDRect rt;
	DWORD c1,c2;
	double a,b,w1,h1;
	DPOINT dpt[4];
	int n,w,len;
	N_PCTPIE *pie;
	pie=(N_PCTPIE*)buf;
	b=GetPercent(pie->curval,pie->maxv);
	if(b<dbm->scf.vppe) return;
	a=b>1 ? 1:b;
	c1=pie->color2;
	c2=GetPctPieColor(pie->color1,a);
	rt=CreateDrawNRt(4,pie->pt,dbm->curzoom);
	n=GetPctPieCirclePt(npt,rt,a,dbm->scf.flowover);
	if(a==1) c1=c2;
	DrawPie(hdc,rt,c1,c2,c2,b,dx,dy);
	//显示百分饼图文字
	if(a>=0.8)
	{
		font=pie->lf;
		sprintf(p,"%d%%",(int)(b*100));
		len=strlen(p);
		w=(int)((rt.Width())/4);
		font.lfHeight=w*2;
		font.lfWidth=w;
		sz=GLDGetTextSize(hdc,&font,p);
		w1=(rt.Width()-sz.cx)/2;
		h1=(rt.Height()-sz.cy)/2;
		dpt[0].x=rt.left+w1;dpt[0].y=rt.top+h1;
		dpt[1].x=rt.right-w1;dpt[1].y=dpt[0].y;
		dpt[2].x=dpt[0].x;dpt[2].y=rt.bottom-h1;
		dpt[3].x=dpt[0].x;dpt[3].y=dpt[2].y;
		SDrawText(hdc,dpt,p,&font,dx,dy,pie->fcolor,DT_LEFT);
	}
}




//显示组合图元
void DObj::ShowEleGrp(HDC hdc, int dx, int dy)
{
	int i,eno;
	N_ELEGRPA *ep;
	ep=(N_ELEGRPA*)buf;
	i=ep->egrpid;
	if(i<0) return;
	eno=ep->vr.sta;
	eno=eno==0 ? 0:1;
	PreShowEGPEx(hdc,i,eno,dx,dy);
}

void DObj::ShowYb(HDC hdc, int dx, int dy)
{
	int i;
	N_ELEGRPYB *ep;
	if(dbm->lookdown==1||dbm->curang!=0) return; //只在正常时显示
	ep=(N_ELEGRPYB*)buf;
	i=ep->egrpid;
	if(i<0) return;
	PreShowEGPYB(hdc,i,dx,dy);
}

//显示组合图元
void DObj::ShowEleGrpP(HDC hdc, int dx, int dy,int pm)
{
	int i,eno;
	N_ELEGRPA *ep;
	ep=(N_ELEGRPA*)buf;
	i=ep->egrpid;
	if(i<0) return;
	eno=ep->vr.sta;
	eno=eno==0 ? 0:1;
	PreShowEGPExP(hdc,i,eno,dx,dy,pm);
}

//设置对象的颜色
void DObj::SetColor(DWORD color,int bgmode)
{
	N_DBX  *db;
	N_RECT *rt;
	N_HSIN *hn;
	N_SIN  *sn;
	N_ARROW *aw;
	N_CBAR  *cb;
	N_TEXT  *tx;
	N_ARC   *ar;
	N_ESITE *si;
	switch(attr.type)
	{
	case 1: 
		db=(N_DBX*)buf;
		db->lcolor=color;
		if(bgmode==0)
		{
			db->bcolor1=color;
			db->bcolor2=color;
		}
		break;
	case 2: case 3:
		rt=(N_RECT *)buf;
		rt->lcolor=color;
		if(bgmode==0)
		{
			rt->bcolor1=color;
		}
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
	case 9: 
		cb=(N_CBAR*)buf;
		cb->color=color;
		break;
	case 10:
		tx=(N_TEXT*)buf;
		tx->color=color;
		break;
	case 11:
		si=(N_ESITE*)buf;
		si->color=color;
		break;
	}
}

//按比例移动一个对象
void DObj::MoveObject2(CDRect prt, double xl, double yl)
{
	DPOINT *pt;
	int ptsum,i;
	pt=GetObjectPt(ptsum);
	if(ptsum==0||pt==NULL) return;
	for(i=0;i<ptsum;i++)
	{
		pt[i].x=(double)(prt.right+(pt[i].x-prt.left)*xl);
		pt[i].y=(double)(prt.bottom+(pt[i].y-prt.top)*yl);
	}
}


//根据记录号索引号显示图元组(打印用)
void DObj::PreShowEGPYB(HDC hdc,int num,int dx,int dy)
{
	DObj  *bs,bbs;
	CDRect  art;
	N_ELEGRPYB *yb;
	int i,j,k,n;
	double xl,yl,w1,w2,h1,h2;
	CDRect rt,rt1,rt2;
	yb=(N_ELEGRPYB*)buf;
	bs=(DObj*)dbm->egp[num].bs1;
	j=dbm->egp[num].bsum1;
	rt1.SetDRECT(dbm->egp[num].rt1);
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

	n=dbm->egp[num].sitesum;
	if(n>0&&n<=8){
		for(i=0;i<n;i++)
		{
			k=dbm->egp[num].index[i];
			if(k>=0&&k<j)
			{
				bs[k].SetMeterVal(yb->curval[i]);
			}

		}
	}
	bbs.dbm=dbm;
	for(i=0;i<j;i++)
	{
		bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.MoveObject2(rt2,xl,yl);
		bbs.SetSObjZM(xl);
		bbs.ShowE(hdc,dx,dy);
		bbs.FreeMem();
	}
}

//根据记录号索引号显示图元组(正常显示专用)
void DObj::PreShowEGPEx(HDC hdc,int num,int index,int dx,int dy)
{
	int type;
	N_SIN  *sn;
	DObj  *bs,bbs;
	DPOINT *spt;
	DWORD color;
	CDRect  art;
	N_ELEGRPA *el;
	int i,j,l,k,m,dele;
	double xl,yl,w1,w2,h1,h2;
	CDRect rt,rt1,rt2;
	el=(N_ELEGRPA*)buf;
	spt=el->pt;
	switch(index)
	{
	 case 0:
		bs=(DObj*)dbm->egp[num].bs1;
		j=dbm->egp[num].bsum1;
		rt1.SetDRECT(dbm->egp[num].rt1);
		break;
	 case 1:
		bs=(DObj*)dbm->egp[num].bs2;
		j=dbm->egp[num].bsum2;
		rt1.SetDRECT(dbm->egp[num].rt2);
		break;
	 default:return;
	}
	
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
	k=-1;
	dele=el->vr.ele; //返回设备带电状态
	bbs.dbm=dbm;
	for(i=0;i<j;i++)
	{
		type=bs[i].attr.type;
		bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.MoveObject2(rt2,xl,yl);
		if(el->type==1){ //属于设备，需要动态着色
		  l=bs[i].attr.belong;
		  if(l>0)
		  {
			l--;
			l=l>2 ? 0:l;
			m=el->site[l].vl;
			m=m>24 ? 24:m;
			color=dele==1 ? cobj.vcolor[m]:0x7f7f7f;
			if(el->subtype==2) bbs.SetColor(color);
			else bbs.SetColor(color,1);
		  }
		  if(el->subtype==1){ //发发电机动态处理
			if(type==5){ //发电机动态显示
				sn=(N_SIN*)bbs.buf;
				sn->startdeg=el->dydeg;
			}
		  }
		}
		bbs.ShowE(hdc,dx,dy);
		bbs.FreeMem();
	}
}


//根据记录号索引号显示图元组(正常显示专用)
void DObj::PreShowEGPExP(HDC hdc,int num,int index,int dx,int dy,int pm)
{
	int type;
	N_SIN  *sn;
	DObj  *bs,bbs;
	DPOINT *spt;
	DWORD color;
	CDRect  art;
	N_ELEGRPA *el;
	int i,j,l,k,m,dele;
	double xl,yl,w1,w2,h1,h2;
	CDRect rt,rt1,rt2;
	el=(N_ELEGRPA*)buf;
	spt=el->pt;
	switch(index)
	{
	 case 0:
		bs=(DObj*)dbm->egp[num].bs1;
		j=dbm->egp[num].bsum1;
		rt1.SetDRECT(dbm->egp[num].rt1);
		break;
	 case 1:
		bs=(DObj*)dbm->egp[num].bs2;
		j=dbm->egp[num].bsum2;
		rt1.SetDRECT(dbm->egp[num].rt2);
		break;
	 default:return;
	}
	
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
	k=-1;
	dele=el->vr.ele; //返回设备带电状态
	bbs.dbm=dbm;
	for(i=0;i<j;i++)
	{
		type=bs[i].attr.type;
		bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.MoveObject2(rt2,xl,yl);
		if(el->type==1){ //属于设备，需要动态着色
		  l=bs[i].attr.belong;
		  if(l>0)
		  {
			l--;
			l=l>2 ? 0:l;
			m=el->site[l].vl;
			m=m>24 ? 24:m;
			color=dele ? cobj.vcolor[m]:0x7f7f7f;
			if(el->subtype==2) bbs.SetColor(color);
			else bbs.SetColor(color,1);
		  }
		  if(el->subtype==1){ //发发电机动态处理
			if(type==5){ //发电机动态显示
				sn=(N_SIN*)bbs.buf;
				sn->startdeg=el->dydeg;
			}
		  }
		}
		bbs.ShowEP(hdc,dx,dy,pm);
		bbs.FreeMem();
	}
}



//显示图形对象(HDC专门用于显示组合图元)
void DObj::ShowE(HDC hdc,int dx, int dy)
{
	switch(attr.type)
	{
	case 1: ShowDbx(hdc,dx,dy);		break;
	case 2: ShowRect(hdc,dx,dy);	break;
	case 3: ShowCircle(hdc,dx,dy);	break;
	case 4: ShowHSin(hdc,dx,dy);	break;
	case 5: ShowSin(hdc,dx,dy);		break;
	case 6: ShowArc(hdc,dx,dy);		break;
	case 7: ShowArrow(hdc,dx,dy);	break;
	case 10:ShowText(hdc,dx,dy);	break;
	case 32:ShowMeter1(hdc,dx,dy);	break;
	case 33:ShowMeter2(hdc,dx,dy);	break;
	case 34:ShowMeter3(hdc,dx,dy);	break;
	case 35:ShowMeter4(hdc,dx,dy);	break;
	}
}

//显示图形对象(HDC专门用于显示组合图元)
void DObj::ShowEP(HDC hdc,int dx, int dy,int pm)
{
	switch(attr.type)
	{
	case 1: ShowDbxP(hdc,dx,dy,pm);		break;
	case 2: ShowRectP(hdc,dx,dy,pm);	break;
	case 3: ShowCircleP(hdc,dx,dy,pm);	break;
	case 4: ShowHSinP(hdc,dx,dy,pm);	break;
	case 5: ShowSinP(hdc,dx,dy,pm);		break;
	case 6: ShowArcP(hdc,dx,dy,pm);		break;
	case 7: ShowArrowP(hdc,dx,dy,pm);	break;
	case 10:ShowTextP(hdc,dx,dy,pm);	break;
	}
}


//显示
void DObj::Show(HDC hdc,int dx,int dy)
{
	switch(attr.type)
	{
	case 1: ShowDbx(hdc,dx,dy);			break;
	case 2: ShowRect(hdc,dx,dy);		break;
	case 3: ShowCircle(hdc,dx,dy);		break;
	case 4: ShowHSin(hdc,dx,dy);		break;
	case 5: ShowSin(hdc,dx,dy);			break;
	case 6: ShowArc(hdc,dx,dy);			break;
	case 7: ShowArrow(hdc,dx,dy);		break;
	//case 10:ShowText(hdc,dx,dy);		break;
	case 13:ShowCoordnate(hdc,dx,dy,0);	break;
	case 14:ShowTable(hdc,dx,dy,0);		break;
	case 15:ShowImg(hdc,dx,dy);			break;
	case 32:ShowMeter1(hdc,dx,dy);		break;
	case 33:ShowMeter2(hdc,dx,dy);		break;
	case 34:ShowMeter3(hdc,dx,dy);		break;
	case 35:ShowMeter4(hdc,dx,dy);		break;
	case 65:ShowReservoir(hdc,dx,dy,0);	break;
	case 66:ShowEleGrp(hdc,dx,dy);		break;
	case 67:ShowYb(hdc,dx,dy);			break;
	case 68:ShowSysPie(hdc,dx,dy);		break;
	case 69:ShowBar(hdc,dx,dy);			break;
	case 70:ShowPie(hdc,dx,dy);			break;
	case 71:ShowDate(hdc,dx,dy,0);		break;
	case 72:ShowTime(hdc,dx,dy,0);		break;
	case 73:ShowGifAnl(hdc,dx,dy);		break;
	case 74:ShowScrText(hdc,dx,dy,0);	break;
	case 75:ShowPush(hdc,dx,dy);		break;
	case 77:ShowFlowLine(hdc,dx,dy);	break;
	case 78:ShowConLine(hdc,dx,dy);		break;
	case 79:ShowBus(hdc,dx,dy);			break;
	case 82:ShowPctPie(hdc,dx,dy);		break;
	case 83:ShowZone(hdc,dx,dy,0);		break;
	case 84:ShowMTText(hdc,dx,dy,0);break;
	}
}

//打印显示在纸上
void DObj::Print(HDC hdc,int pm,int dx,int dy)
{
	switch(attr.type)
	{
	case 1: ShowDbxP(hdc,dx,dy,pm);		break;
	case 2: ShowRectP(hdc,dx,dy,pm);	break;
	case 3: ShowCircleP(hdc,dx,dy,pm);	break;
	case 4: ShowHSinP(hdc,dx,dy,pm);	break;
	case 5: ShowSinP(hdc,dx,dy,pm);		break;
	case 6: ShowArcP(hdc,dx,dy,pm);		break;
	case 7: ShowArrowP(hdc,dx,dy,pm);	break;
	case 10:ShowTextP(hdc,dx,dy,pm);	break;
	case 13:ShowCoordnate(hdc,dx,dy,pm);break;
	case 14:ShowTable(hdc,dx,dy,pm);	break;
	case 15:ShowImg(hdc,dx,dy);			break;
	case 64:ShowAnl(hdc,dx,dy,pm);		break;
	case 65:ShowReservoir(hdc,dx,dy,pm);break;
	case 66:ShowEleGrpP(hdc,dx,dy,pm);	break;
	case 68:ShowSysPie(hdc,dx,dy);		break;
	case 69:ShowBar(hdc,dx,dy);			break;
	case 70:ShowPie(hdc,dx,dy);			break;
	case 71:ShowDate(hdc,dx,dy,pm);		break;
	case 72:ShowTime(hdc,dx,dy,pm);		break;
	case 73:ShowGifAnl(hdc,dx,dy);		break;
	case 74:ShowScrText(hdc,dx,dy,pm);	break;
	case 75:ShowPush(hdc,dx,dy);		break;
	case 77:ShowFlowLineP(hdc,dx,dy,pm);break;
	case 78:ShowConLineP(hdc,dx,dy,pm);	break;
	case 79:ShowBusP(hdc,dx,dy,pm);		break;
	case 82:ShowPctPieP(hdc,dx,dy,pm);	break;
	case 83:ShowZone(hdc,dx,dy,pm);		break;
	case 84:ShowMTText(hdc,dx,dy,pm);   break;
	}
}

//对象是否在显示的矩形中
bool DObj::ObjIsInRect(CRect &rt)
{
	CRect rt1;
	DPOINT *pt,dpt[4];
	POINT  ipt[4];
	pt=(DPOINT*)buf;
	PointActToScr(pt,dpt,4,dbm->curzoom);
	dbm->msr->DPtToScrPt(dpt,ipt,4,0,0);
	rt1=CreateCRt(4,ipt);
	rt1&=rt;
	if(rt1.IsRectEmpty()) return false;
	return true;
}

//对象是否在显示的矩形中
bool DObj::ObjIsCutRgn(HRGN hrgn)
{
	int a;
	N_FLOW *fw;
	HRGN rgn;
	CRect rt1;
	DPOINT *pt,dpt[4];
	POINT  ipt[4];
	switch(attr.type)
	{
	case 77:
		rgn=CreateRectRgn(0,0,1,1);
		fw=(N_FLOW*)buf;
		CombineRgn(rgn,fw->hrgn,fw->hrgn,RGN_COPY);
		break;
	default:
		pt=(DPOINT*)buf;
		PointActToScr(pt,dpt,4,dbm->curzoom);
		dbm->msr->DPtToScrPt(dpt,ipt,4,0,0);
		rt1=CreateCRt(4,ipt);
		rgn=CreatePolygonRgn(ipt,4,ALTERNATE);
		break;
	}
	if(rgn==NULL) return false;
	a=CombineRgn(rgn,rgn,hrgn,RGN_AND);
	if(rgn!=NULL) DeleteObject(rgn);
	if(a==NULLREGION||a==ERROR) return false;
	return true;
}


//点是否在对象的矩形中
bool DObj::PtIsInObj(POINT &pta)
{
	bool rtn;
	HRGN hrgn;
	CRect rt1;
	DPOINT *pt,dpt[4];
	POINT  ipt[4];
	pt=(DPOINT*)buf;
	PointActToScr(pt,dpt,4,dbm->curzoom);
	dbm->msr->DPtToScrPt(dpt,ipt,4,0,0);
	hrgn=CreatePolygonRgn(ipt,4,ALTERNATE);
	if(hrgn!=NULL)
	{
		rtn=PtInRegion(hrgn,pta.x,pta.y)==TRUE ? true:false;
		DeleteObject(hrgn);
		return rtn;
	}
	return false;
}




//设置仪表值
void DObj::SetMeterVal(float val)
{
	N_METER1 *mt1;
	N_METER2 *mt2;
	N_METER3 *mt3;
	N_METER4 *mt4;
	switch(attr.type)
	{
	case 32:
		mt1=(N_METER1 *)buf;
		mt1->curval=val;
		break;
	case 33:
		mt2=(N_METER2 *)buf;
		mt2->curval=val;
		break;
	case 34:
		mt3=(N_METER3 *)buf;
		mt3->curval=val;
		break;
	case 35:
		mt4=(N_METER4 *)buf;
		mt4->curval=val;
		break;
	}
}

//设置仪表最大最小值
void DObj::SetMeterMaxMin(MTRRANGE &mtr)
{
	N_METER1 *mt1;
	N_METER2 *mt2;
	N_METER3 *mt3;
	switch(attr.type)
	{
	case 32:
		mt1=(N_METER1 *)buf;
		mt1->Vmin=mtr.vmin;
		mt1->Vmax=mtr.vmax;
		mt1->val[0]=mtr.val[0];
		mt1->val[1]=mtr.val[1];
		mt1->val[2]=mtr.val[2];
		mt1->val[3]=mtr.val[3];
		mt1->alarm=mtr.alarm;
		break;
	case 33:
		mt2=(N_METER2 *)buf;
		mt2->Vmin=mtr.vmin;
		mt2->Vmax=mtr.vmax;
		mt2->val[0]=mtr.val[0];
		mt2->val[1]=mtr.val[1];
		mt2->val[2]=mtr.val[2];
		mt2->val[3]=mtr.val[3];
		mt2->alarm=mtr.alarm;
		break;
	case 34:
		mt3=(N_METER3 *)buf;
		mt3->Vmin=mtr.vmin;
		mt3->Vmax=mtr.vmax;
		break;
	}
}

//设置特殊对象的放大倍数，主要针对组合图元的仪表部件
void DObj::SetSObjZM(double zm)
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
