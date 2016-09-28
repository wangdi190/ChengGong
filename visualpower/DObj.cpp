// DObj.cpp: implementation of the DObj class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "VisualPower.h"
#include "DObj.h"
#include "bclass.h"
#include "comobj.h"
#include "gdata.h"
#include "math.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif
extern comobj cobj;
extern char *wk[];
extern CPoint *mpt;//临时用的一个点缓冲区，最大1024个点
extern DPOINT *npt;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

DObj::DObj()
{
	buf=NULL;
	memset(&attr,0,sizeof(N_BASATTR));
	showdyn=0;
}

DObj::~DObj()
{
	FreeMem();
}
//显示多边形对象
void DObj::ShowDbx(CDIB&mdc, int dx, int dy,int high,int bgmode)
{
    DPOINT ptb[1024];
	int tpsum;
	N_DBX *dbx;
	dbx=(N_DBX*)buf;
	if(bgmode!=dbx->bgmode) return;
	tpsum=dbx->ptsum>1000 ? 1000:dbx->ptsum;
	PointActToScr(dbx->pt,ptb,tpsum,dbm->curzoom);
	mdc.CSetLineStyle(dbx->ltype);//);
	mdc.D3DrawPoly(ptb,tpsum,dbx->lcolor,dbx->bcolor1,dbx->fill,dbx->close,dx,dy,high);//dbx->close
	mdc.CSetLineStyle(0);	
}
   
 
//显示水库对象
void DObj::ShowReservoir(CDIB&mdc,int dx, int dy)
{
	int tpsum;        
	N_RESERVOIR *rev;
	rev=(N_RESERVOIR*)buf;
	tpsum=rev->ptsum>1000 ? 1000:rev->ptsum;
	PointActToScr(rev->pt,npt,tpsum,dbm->curzoom);
	mdc.D3DrawPoly(npt,tpsum,rev->color,rev->ncolor,1,1,dx,dy);
}
    

void DObj::ShowZone(CDIB&mdc,int dx, int dy)
{
	DWORD color;
	CDRect drt;
	CRect rt;
	DPOINT cpt;
	SIZE sz;
	LOGFONT lf;
	int tpsum;
	N_ZONE *zn;
	zn=(N_ZONE*)buf;
	color=dbm->GetDefColor(5,zn->dyval);
	tpsum=zn->ptsum>1000 ? 1000:zn->ptsum;
	PointActToScr(zn->pt,npt,tpsum,dbm->curzoom);
	mdc.D3DrawPoly(npt,tpsum,zn->lcolor,color,0,1,dx,dy);
	if(strlen(zn->zone_name)==0) return;
	drt=CreateNRt(zn->ptsum,zn->pt);
	cpt=drt.CenterPoint();
	lf=zn->lf;
	sz=GLDGetTextSize(mdc.m_hDC,&lf,zn->zone_name);
	drt.left=cpt.x-sz.cx/2;
	drt.right=cpt.x+sz.cx/2+2;
	drt.top=cpt.y-sz.cy/2;
	drt.bottom=cpt.y+sz.cy/2+2;
	drt.ActRtToScr(dbm->curzoom);
	drt.Offset(dx,dy);
	drt.GetRECT(rt);
	lf.lfHeight=(long)(lf.lfHeight*dbm->curzoom);
	lf.lfWidth=(long)(lf.lfWidth*dbm->curzoom);
	GLDDrawText(mdc.m_hDC,&rt,&lf,zn->zone_name,zn->fcolor,0,DT_LEFT);
}


//显示矩形对象
void DObj::ShowRect(CDIB&mdc, int dx, int dy,int high)
{
	int i;
	CPoint pta[4];
	DPOINT ptb[4];
	CDRect rt;
	N_RECT *nrt;
	nrt=(N_RECT*)buf;
	PointActToScr(nrt->pt,ptb,4,dbm->curzoom);
	mdc.DPtToScrPt(ptb,ptb,4,dx,dy,high);
	for(i=0;i<4;i++)
	{
		pta[i].x=(int)ptb[i].x;
		pta[i].y=(int)ptb[i].y;
	}
	mdc.CDrawPoly(ptb,4,nrt->lcolor,nrt->bcolor1,nrt->fill,1);//
	switch(nrt->type)
	{
	case 1: //凹矩形
		mdc.CDraw3dRectP(pta,0,0xffffff);
		break;
	case 2: //凸矩形
		mdc.CDraw3dRectP(pta,0xffffff,0);
		break;
	}
}

//显示圆对象
void DObj::ShowCircle(CDIB&mdc, int dx, int dy,int high)
{
	CDRect rt; 
	N_CIRCLE *ncr;
	ncr=(N_CIRCLE*)buf;
	rt=CreateDrawNRt(4,ncr->pt,dbm->curzoom);
	if(ncr->fill==1) mdc.D3Ellipsec(rt,ncr->lcolor,ncr->bcolor1,dx,dy,high);
	else mdc.D3Circle(rt,ncr->lcolor,dx,dy,high);
}


//显示半波
void DObj::ShowHSin(CDIB&mdc, int dx, int dy,int high)
{
	CDRect rt;
	N_HSIN *hsn;
	hsn=(N_HSIN *)buf; 
	rt=CreateDrawNRt(4,hsn->pt,dbm->curzoom);
	mdc.D3DrawHSin(rt,hsn->color,hsn->ltype,hsn->pirodic,dx,dy,high);
}

//显示正弦波
void DObj::ShowSin(CDIB&mdc, int dx, int dy,int high)
{
	CDRect rt; 
	N_SIN *sn;
	sn=(N_SIN *)buf;
	rt=CreateDrawNRt(4,sn->pt,dbm->curzoom);
	mdc.D3DrawSin(rt,sn->color,sn->ltype,sn->pirodic,dx,dy,sn->startdeg,high);     
}

//显示弧线
void DObj::ShowArc(CDIB&mdc, int dx, int dy,int high)
{
	CDRect rt;
	N_ARC *arc;
	arc=(N_ARC *)buf;
	rt=CreateDrawNRt(4,arc->pt,dbm->curzoom);
	mdc.D3DrawArc(rt,arc->color,arc->start,arc->end,dx,dy);
}

void DObj::ShowArrow(CDIB&mdc, int dx, int dy,int high)
{
	double w;
	N_ARROW *arw;
	arw=(N_ARROW *)buf;
	PointActToScr(arw->pt,npt,2,dbm->curzoom);
	w=4*dbm->curzoom;
	mdc.D3DrawArrow(npt[0],npt[1],arw->color,(int)w,dx,dy); 
}

//画玻璃层
void DObj::ShowGlass(CDIB&mdc,int dx,int dy)
{
	DPOINT dpt[4];
	POINT  pt[4];
	N_GLASS *gls;
	gls=(N_GLASS *)buf;
	PointActToScr(gls->pt,dpt,4,dbm->curzoom);
	mdc.DPtToScrPt(dpt,pt,4,dx,dy,0);
	mdc.CDrawPolyGlass(pt,4,gls->color,gls->ocolor,gls->outline,gls->depth); 
}

//显示坐标
void DObj::ShowCoordnate(CDIB&mdc, int dx, int dy)
{
	char p[100];
	DWORD c1;
	int i,xm,ym;
	double xl,yl,nx,ny,w,h,m,x,y,wd;
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
	c1=co->colorc;
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
	 for(i=1;i<xm+1;i++)
	 {
		x=i*xl;
		npt[0].x=rt.left+x;
		npt[0].y=rt.bottom;
		npt[1].x=rt.left+x;
		npt[1].y=rt.bottom+m;
		mdc.DPtToScrPt(npt,mpt,2,dx,dy);
		mdc.CLine(mpt[0],mpt[1],c1);
	    if(i>0){
			sprintf(p,"%d",(DWORD)(i*nx+co->xmin));
			size=GLDGetTextSize(mdc.m_hDC,&co->fontx,p);
			dpt[0].x=rt.left+x-size.cx/2;dpt[0].y=rt.bottom+m;
			dpt[1].x=rt.left+x+xl/2;dpt[1].y=rt.bottom+m;
			dpt[2].x=dpt[1].x;dpt[2].y=dpt[1].y+size.cy+4;
			dpt[3].x=npt[0].x;dpt[3].y=dpt[2].y;
			SDrawText(mdc.m_hDC,dpt,p,&tm.fontx,dx,dy,co->colort,DT_LEFT);
		}
	 };
	}
	m=5*dbm->curzoom/co->zm;
	if(co->yvshow==1)
	{
	 for(i=1;i<ym+1;i++)
	 {
		y=i*yl;
		npt[0].x=rt.left-m;
		npt[0].y=rt.bottom-y;
		npt[1].x=rt.left;
		npt[1].y=rt.bottom-y;
		mdc.DPtToScrPt(npt,mpt,2,dx,dy);
		mdc.CLine(mpt[0],mpt[1],c1);
		if(i>0){
		    sprintf(p,"%d",(DWORD)(i*ny+co->ymin));
			size=GLDGetTextSize(mdc.m_hDC,&co->fonty,p);
			dpt[0].x=drt.left+1;dpt[0].y=rt.bottom-y-size.cy/2;
			dpt[1].x=rt.left-m; dpt[1].y=dpt[0].y;
			dpt[2].x=dpt[1].x;dpt[2].y=dpt[1].y+size.cy+4;
			dpt[3].x=dpt[0].x;dpt[3].y=dpt[2].y;
			SDrawText(mdc.m_hDC,dpt,p,&tm.fonty,dx,dy,co->colort,DT_LEFT);
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
		mdc.DPtToScrPt(npt,mpt,2,dx,dy);
		mdc.CLine(mpt[0],mpt[1],co->colorw);
	 };
	}
	if(co->wydraw==1)
	{
	 for(i=1;i<ym+1;i++)
	 {
		y=i*yl;
		npt[0].x=rt.left;
		npt[0].y=rt.bottom-y;
		npt[1].x=rt.right;
		npt[1].y=rt.bottom-y;
		mdc.DPtToScrPt(npt,mpt,2,dx,dy);
		mdc.CLine(mpt[0],mpt[1],co->colorw);
	 };
	}
	wd=4*dbm->curzoom;
	npt[0].x=drt.left;
	npt[0].y=rt.bottom;
	npt[1].x=drt.right;
	npt[1].y=rt.bottom;
	mdc.D3DrawArrow(npt[0],npt[1],c1,(int)wd,dx,dy); 
	npt[0].x=rt.left;
	npt[0].y=drt.bottom;
	npt[1].x=rt.left;
	npt[1].y=drt.top;
	mdc.D3DrawArrow(npt[0],npt[1],c1,(int)wd,dx,dy); 
	npt[0].x=rt.left;npt[0].y=rt.top;
	npt[1].x=rt.right;npt[1].y=rt.top;
	npt[2].x=rt.right;npt[2].y=rt.bottom;
	mdc.DPtToScrPt(npt,mpt,3,dx,dy);
	mdc.CDrawDbx(mpt,3,c1);
}


//显示表格线
void DObj::ShowTable(CDIB&mdc, int dx, int dy)
{
	int i,ym,h,y,lw;
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
	for(i=1;i<ym+1;i++)
	{
		y=(int)(i*yl);
		npt[0].x=rt.left;
		npt[0].y=rt.bottom-y;
		npt[1].x=rt.right;
		npt[1].y=rt.bottom-y;
		mdc.DPtToScrPt(npt,mpt,2,dx,dy);
		mdc.CLine(mpt[0],mpt[1],ta->color);
	}	
	rt.right++;
	rt.bottom++;
	lw=(int)ta->width;
	if(ta->dbline==1) lw=lw*2;
	npt[0].x=rt.left;npt[0].y=rt.top;
	npt[1].x=rt.right;npt[1].y=rt.top;
	npt[2].x=rt.right;npt[2].y=rt.bottom;
	npt[3].x=rt.left;npt[3].y=rt.bottom;
	mdc.DPtToScrPt(npt,mpt,4,dx,dy);
	mdc.CDrawOutLine(mpt,4,ta->color);
}

//显示棒图
void DObj::ShowBar(CDIB&mdc, int dx, int dy)
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
		SIZE sz=GLDGetTextSize(mdc.m_hDC,&font,bar->dsrc.name);
		w1=rtTxt.Width()-sz.cx;
		h1=(rtTxt.Height()-sz.cy)/2;
		dpt[0].x=rtTxt.left+w1;dpt[0].y=rtTxt.top+h1;
		dpt[1].x=rtTxt.right;dpt[1].y=dpt[0].y;
		dpt[2].x=dpt[0].x;dpt[2].y=rt.bottom-h1;
		dpt[3].x=dpt[0].x;dpt[3].y=dpt[2].y;
		SDrawText(mdc.m_hDC,dpt,bar->dsrc.name,&font,dx,dy,RGB(255,255,255),DT_RIGHT);

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
	mdc.DPtToScrPt(npt,mpt,4,dx,dy);
	DrawPoly(mdc,mpt,4,bar->outline==1 ? 0:c1,c1,1,1);
	if(bar->outline==1)
	{
		DrtToDPt(rt,npt,0);
		mdc.DPtToScrPt(npt,mpt,4,dx,dy);
		DrawPoly(mdc,mpt,4,c1,c1,0,1);
	}
}


//显示仪表1
void DObj::ShowMeter1(CDIB&mdc,int dx, int dy)
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
	if(dbm->lookdown==1||dbm->curang!=0) return; //只在正常时显示
	PointActToScr(mtr->pt,npt,2,dbm->curzoom);
	for(i=0;i<2;i++)
	{
		npt[i].x+=(double)dx;
		npt[i].y+=(double)dy;
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
	//计算指针偏转角度
	axw=mtr->axw*mtr->zm*dbm->curzoom;
	pw=mtr->pw*mtr->zm*dbm->curzoom;

	val=mtr->curval;
	val=val<mtr->Vmin  ? mtr->Vmin:val;
	val=val>mtr->Vmax  ? mtr->Vmax:val;

	b=(val-mtr->Vmin)*xl;
	b=as-b;
	switch(mtr->pstyle)
	{
	case 0:
		ShowMPt1(mdc,spt[0],r3,b,axw,pw,mtr->pcr);
		break;
	case 1:
		ShowMPt2(mdc,spt[0],r3,b,axw,pw,mtr->pcr);
		break;
	case 2:
		ShowMPt3(mdc,spt[0],r3,b,axw,pw,mtr->pcr);	
		break;
	case 3:
		ShowMPt4(mdc,spt[0],r3,b,axw,pw,mtr->pcr);	
		break;
	case 4:
		ShowMPt5(mdc,spt[0],r3,b,axw,pw,mtr->pcr);
		break;
	}
}


//画2饼图
//c1大填充颜色 c2=小块填充颜色 c3=边缘颜色
void DObj::DrawPie(CDIB&mdc,CDRect &rt,DWORD c1,DWORD c2,DWORD c3,double pw,int dx,int dy)
{
	DPOINT  tp[74];
	DPOINT  cpt;
	int n,end;
	n=GetCircleAllPt(tp,rt);
	if(n!=72) return;
	memcpy(npt,tp,72*sizeof(DPOINT));
	mdc.DPtToScrPt(npt,mpt,n,dx,dy);
	DrawPoly(mdc,mpt,n,c3,c1,1,1);
	end=(int)(72*pw);
	if(end<0||end>72) return;
	if(end==0&&pw!=0) end=1;
	if(end!=72&&end!=0&&rt.Width()>3){
		cpt=rt.CenterPoint();
		tp[end].x=cpt.x;
		tp[end].y=cpt.y;
		tp[end+1]=tp[0];
		mdc.DPtToScrPt(tp,mpt,end+2,dx,dy);
		DrawPoly(mdc,mpt,end+2,c3,c2,1,1);
	}
}

//显示饼图
void DObj::ShowPie(CDIB&mdc, int dx, int dy)
{
	SIZE sz;
	char p[100];
	LOGFONT font;
	DPOINT tcpt[2];
	CDRect rt;
	//DWORD c1,c2;
	double a,b,w1,h1,vl[2];
	DWORD cr[2];
	DPOINT dpt[4];
	int w,len;
	N_PIE *pie;
	pie=(N_PIE*)buf;
	b=GetPercent(pie->pcur,pie->maxv);
	a=b>1 ? 1:b;
	cr[0]=pie->color[0];
	cr[1]=pie->color[1];
	rt=CreateDrawNRt(4,pie->pt,dbm->curzoom);
	if(a==1) cr[0]=cr[1];
	vl[0]=a;
	vl[1]=1-a;
	mdc.D3MPie(rt,cr,vl,tcpt,2,0xff,false,dx,dy,0);
	//显示百分饼图文字
	font=pie->lf;
	font.lfHeight=(int)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(int)(font.lfWidth*dbm->curzoom);
	sprintf(p,"%d%%",(int)(b*100));
	len=strlen(p);
	w=(int)((rt.Width())/4);
	sz=GLDGetTextSize(mdc.m_hDC,&font,p);
	w1=(rt.Width()-sz.cx)/2;
	h1=(rt.Height()-sz.cy)/2;
	dpt[0].x=rt.left+w1;dpt[0].y=rt.top+h1;
	dpt[1].x=rt.right-w1;dpt[1].y=dpt[0].y;
	dpt[2].x=dpt[0].x;dpt[2].y=rt.bottom-h1;
	dpt[3].x=dpt[0].x;dpt[3].y=dpt[2].y;
	SDrawText(mdc.m_hDC,dpt,p,&font,dx,dy,pie->fcolor,DT_LEFT);
}


//显示日期
void DObj::ShowDate(CDIB&mdc, int dx, int dy)
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
	mdc.DPtToScrPt(npt,mpt,4,dx,dy);
	c1=date->outcolor;
	if(date->tran==0)  DrawPoly(mdc,mpt,4,date->bcolor,date->bcolor,1,1);
	switch(date->outline)
	{
	case 1:	mdc.CDraw3dRectP(mpt,c1,c1);		break;
	case 2:	mdc.CDraw3dRectP(mpt,c1,0xffffff);  break;
	case 3: mdc.CDraw3dRectP(mpt,0xffffff,c1);	break;
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
	sz=GLDGetTextSize(mdc.m_hDC,&font,p);
	x=(rt.Width()-sz.cx)/2;
	y=(rt.Height()-sz.cy)/2;
	c1=date->fcolor;
	dpt[0].Offset(x,y);
	dpt[1].Offset(-x,y);
	dpt[2].Offset(-x,-y);
	dpt[3].Offset(x,-y);
	SDrawText(mdc.m_hDC,dpt,p,&font,dx,dy,c1,DT_LEFT);
}



//显示日期
void DObj::ShowTime(CDIB&mdc, int dx, int dy)
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
	mdc.DPtToScrPt(npt,mpt,4,dx,dy);
	GetDtStr(date->tm.GetHour(),hr);
	GetDtStr(date->tm.GetMinute(),min);
	GetDtStr(date->tm.GetSecond(),sec);
	if(date->tran==0) DrawPoly(mdc,mpt,4,date->bcolor,date->bcolor,1,1);
	c1=date->outcolor;
	switch(date->outline)
	{
	case 1:	mdc.CDraw3dRectP(mpt,c1,c1);		break;
	case 2:	mdc.CDraw3dRectP(mpt,c1,0xffffff);  break;
	case 3: mdc.CDraw3dRectP(mpt,0xffffff,c1);	break;
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
	sz=GLDGetTextSize(mdc.m_hDC,&font,p);
	x=(rt.Width()-sz.cx)/2;
	y=(rt.Height()-sz.cy)/2;
	rt.left++;
	rt.top++;
	rt.right-=3;
	rt.bottom-=3;
	c1=date->fcolor;
	dpt[0].Offset(x,y);
	dpt[1].Offset(-x,y);
	dpt[2].Offset(-x,-y);
	dpt[3].Offset(x,-y);
	SDrawText(mdc.m_hDC,dpt,p,&font,dx,dy,c1,DT_LEFT);
}

void DObj::ShowFlowLine(CDIB&mdc, int dx, int dy,int high)
{
	DWORD color;
	int v,tpsum,w,lstyle;
	N_FLOW *flw;
	flw=(N_FLOW*)buf;
	if(dbm->curopzt==3&&showdyn==1) return;
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
	lstyle=0;

	//switch(flw->vr.rp)
	switch(lstyle)
	{
	case 0: //正常状态
		w=flw->linewidth;
		w=w>4 ? 0:w;
		if(w==0) mdc.D3DrawPoly(npt,tpsum,color,0,0,0,dx,dy,high);
		else {
			mdc.DPtToScrPt(npt,mpt,tpsum,dx,dy,high);
			mdc.CDrawDbxW(mpt,tpsum,color,w-1);
		}
		break;
		return;
	case 1: case 2:
		lstyle=1;
		break;
	case 3:case 4:
		lstyle=2;
		break;
	}
	//检修显示
	mdc.CSetLineStyle(lstyle);
	mdc.D3DrawPoly(npt,tpsum,color,0,0,0,dx,dy);
	mdc.CSetLineStyle(0);
	//显示故障标牌,挂到线路的起始点
	DPOINT cpt;
//	if(dbm->lookdown==1||flw->vr.trb==0)  return;
	//PointActToScr(&);
	PointActToScr(&flw->stapt,npt,1,dbm->curzoom);
	cpt=npt[0];
	npt[0].x=cpt.x;npt[0].y=cpt.y;
	mdc.DPtToScrPt(npt,npt,1,dx,dy,high);
	//cobj.ShowSimg(mdc.m_hDC,(int)npt[0].x-16,(int)npt[0].y-16,3);
}
  
//显示滚动文本
void DObj::ShowScrText(CDIB &mdc, int dx, int dy)
{
	SIZE sz;
	HRGN hrgn;
	CRect rt,rt1;
	CDRect art;
	int w,h;
	DWORD align;
	N_SRLTEXT *a;
	LOGFONT font;
	a=(N_SRLTEXT*)buf;
	if(dbm->lookdown==1||dbm->curang!=0) return; //俯视和旋转不显示
	rt=CreateDrawRect(4,a->pt,dx,dy);
	rt1=rt;
	font=a->lf;
	w=rt.Width();
	h=rt.Height();
	font=a->lf;
	font.lfHeight=(long)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(long)(font.lfWidth*dbm->curzoom);
	if(a->direct==1||a->direct==3)
	{
	    sz=GLDGetTextSize(mdc.m_hDC,&font,a->text);
		a->wh=(WORD)(sz.cy*GetLineNum(a->text));
	}
	if(a->direct==2||a->direct==4)
	{
		sz=GLDGetTextSize(mdc.m_hDC,&font,a->text);
		a->wh=(WORD)(sz.cx);	     
	}
	switch(a->align)
	{
	  case 1:  align=DT_CENTER;break;
	  case 2:  align=DT_RIGHT; break;
	  default: align=DT_LEFT;
	}
	if(a->glass) mdc.CDrawGlass(rt,a->gcolor,a->fcolor,a->outline,a->depth);
	SaveDC(mdc.m_hDC);
	hrgn=CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
	SelectObject(mdc.m_hDC,hrgn);
	switch(a->direct)
	{
	  case 0:
		mdc.CTextOut(a->text,rt,&font,a->tcolor,a->tstyle,align);
		break;
	  case 3:
		  a->pos++;
		  if(a->pos>a->wh) a->pos=-h;
		  rt.top=rt.top-a->pos;
		  mdc.CTextOut(a->text,rt,&font,a->tcolor,a->tstyle,align);
		  break;
	  case 1:
		  a->pos--;
		  if(a->pos<=-h) a->pos=(WORD)a->wh;
		  rt.top=rt.top-a->pos;
		  mdc.CTextOut(a->text,rt,&font,a->tcolor,a->tstyle,align);
		  break;
	  case 4:
		  a->pos++;
		  if(a->pos>=a->wh) a->pos=-w;
		  rt.left=rt.left-a->pos;
		  mdc.CTextOut(a->text,rt,&font,a->tcolor,a->tstyle,align|DT_VCENTER|DT_SINGLELINE);
		  break;
	  case 2:
		  a->pos++;
		  if(a->pos>=w) a->pos=-a->wh;
		  rt.left=rt.left+a->pos;
		  mdc.CTextOut(a->text,rt,&font,a->tcolor,a->tstyle,align|DT_VCENTER|DT_SINGLELINE);
		  break;
	}
	RestoreDC(mdc.m_hDC,-1);
	DeleteObject(hrgn);
	if(a->outline==1) mdc.CDraw3DRect(rt1,a->fcolor,a->fcolor);
}

//显示潮流箭头
void DObj::ShowFlow(CDIB&mdc, int dx, int dy)
{
	DWORD color,c1,c2,c3;
	int v,tpsum,n1,n2,n3,pd,qd,id,w1,w2,w3;
	DPOINT tp[21];
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
		c3=0x7f7f7f;
	}else{
		v=flw->vl;
		v=v>20 ? 0:v;
		color=cobj.vcolor[v];
		c1=dbm->scf.syscolor[13];
		c2=dbm->scf.syscolor[14];
		c3=dbm->scf.syscolor[15];
	}
	     
	///////////////////////////////////////////////////////////////////
	if(flw->rf.pdir==0) pd=1;else pd=-1;
	if(flw->rf.qdir==0) qd=1;else qd=-1;
	if(flw->rf.idir==0) id=1;else id=-1;
	n1=flw->rf.pjs;
	n2=flw->rf.qjs;
	n3=flw->rf.ijs;
	w1=5-flw->pv;
	w2=5-flw->qv;
	w3=5-flw->iv;
	w1=w1>5 ? 5:w1;
	w2=w2>5 ? 5:w2;                 
	w3=w3>5 ? 5:w3;
	PointActToScr(flw->pt,tp,tpsum,dbm->curzoom);
	if(flw->vr.ele==0)  return;
	if(dbm->curopzt!=3) //正常潮流箭头显示
	{
		switch(dbm->scf.ftype){
		case 1: //只显有功
			if(flw->vr.value[0]!=0) mdc.D3DrawFlow(tp,tpsum,n1,pd,w1,96,color,c1,dx,dy);
			break;
		case 2: //只显无功 
			if(flw->vr.value[1]!=0) mdc.D3DrawFlow(tp,tpsum,n2,qd,w2,96,color,c2,dx,dy);
			break;
		case 3: //同时显示
			if(flw->vr.value[0]!=0) mdc.D3DrawFlow(tp,tpsum,n1,pd,w1,96,color,c1,dx,dy);
			if(flw->vr.value[1]!=0) mdc.D3DrawFlow(tp,tpsum,n2,qd,w2,96,color,c2,dx,dy);
			break;
		case 4: //显示电流潮流线
			if(flw->vr.value[7]!=0) mdc.D3DrawFlow(tp,tpsum,n3,id,w3,96,color,c3,dx,dy);
			break;
		}
	}
	if(dbm->curopzt==3&&flw->lowfbz==1) //低频震荡显示
	{
		PointActToScr(flw->pt,npt,tpsum,dbm->curzoom);
		mdc.DPtToScrPt(npt,mpt,tpsum,dx,dy);
 		DrawPoly(mdc.m_hDC,mpt,tpsum,0xf0ffff,0xf0ffff,0,0,16);
		mdc.D3FlowLowf(tp,tpsum,flw->fpt,flw->flen,0xff,dx,dy);
	}
	if(dbm->curopzt==3&&flw->lowfbz==0) //其它情况
	{
		mdc.D3DrawPoly(tp,tpsum,color,0,0,0,dx,dy);
	}
}


//显示连接线对象
void DObj::ShowConLine(CDIB&mdc, int dx, int dy)
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
	mdc.D3DrawPoly(npt,tpsum,color,0,0,0,dx,dy);
}





//根据记录号索引号显示图元组(正常显示专用)
void DObj::PreBusEGPEx(CDIB&mdc,int num,int index,int dx,int dy,int high)
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
		bs=dbm->egp[num].bs1;
		j=dbm->egp[num].bsum1;
		rt1.SetDRECT(dbm->egp[num].rt1);
		break;
	 case 1:
		bs=dbm->egp[num].bs2;
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
		bbs.ShowES(mdc,dx,dy,high);
		bbs.FreeMem();
	}
}

//显示母线
void DObj::ShowBus(CDIB&mdc, int dx, int dy,int high)
{
	int i,v,lstyle;
	DWORD color;
	CRect rt;
	CDRect art;
	N_BUS *bus;
	CDPoint cpt;
	bus=(N_BUS *)buf;
	if(bus->vr.ele==0) color=0x7f7f7f;
	else
	{
		v=bus->vl;
		v=v>20 ? 0:v;
		color=cobj.vcolor[v];
	}
	lstyle=0;
	switch(bus->vr.rp)
	{
	case 1: case 2:
		lstyle=1;
		break;
	case 3:case 4:
		lstyle=2;
		break;
	}
	mdc.CSetLineStyle(lstyle);
	switch(bus->type)
	{
	case 0:case 1:
		PointActToScr(bus->pt,npt,4,dbm->curzoom);
		mdc.DPtToScrPt(npt,npt,4,dx,dy,high);
		for(i=0;i<4;i++)
		{
			mpt[i].x=(int)npt[i].x;
			mpt[i].y=(int)npt[i].y;
		}
//		if(bus->vr.alarmband==1)	color=0xff;
		mdc.CDrawPoly(npt,4,color,color,1,1);
		if(bus->type==1) mdc.CDraw3dRectP(mpt,color);
		//显示告警灯
		if(dbm->lookdown==1)  break;
		art=CreateDrawNRt(4,bus->pt,dbm->curzoom);
		cpt=art.CenterPoint();
		npt[0].x=cpt.x;npt[0].y=cpt.y;
		mdc.DPtToScrPt(npt,npt,1,dx,dy,high);
		if(bus->vr.alarmhilo==1) cobj.ShowSimg(mdc.m_hDC,(int)npt[0].x-8,(int)npt[0].y-10,7);
		if(bus->vr.alarmhilo==2) cobj.ShowSimg(mdc.m_hDC,(int)npt[0].x-8,(int)npt[0].y-10,8);
		break;
	case 2: //圆形BUS
		art=CreateDrawNRt(4,bus->pt,dbm->curzoom);
		mdc.D3Ellipsec(art,0,color,dx,dy,high);
		if(dbm->lookdown==1)  break;
		art=CreateDrawNRt(4,bus->pt,dbm->curzoom);
		cpt=art.CenterPoint();
		npt[0].x=cpt.x;npt[0].y=cpt.y;
		mdc.DPtToScrPt(npt,npt,1,dx,dy,high);
		if(bus->vr.alarmhilo==1) cobj.ShowSimg(mdc.m_hDC,(int)npt[0].x-8,(int)npt[0].y-10,7);
		if(bus->vr.alarmhilo==2) cobj.ShowSimg(mdc.m_hDC,(int)npt[0].x-8,(int)npt[0].y-10,8);
		break;
	case 3:
		i=bus->eid;
		PreBusEGPEx(mdc,i,0,dx,dy,high);
		if(dbm->lookdown==1)  break;
		art=CreateDrawNRt(4,bus->pt,dbm->curzoom);
		cpt=art.CenterPoint();
		npt[0].x=cpt.x;npt[0].y=cpt.y;
		mdc.DPtToScrPt(npt,npt,1,dx,dy,high);
		if(bus->vr.alarmhilo==1) cobj.ShowSimg(mdc.m_hDC,(int)npt[0].x-8,(int)npt[0].y-10,7);
		if(bus->vr.alarmhilo==2) cobj.ShowSimg(mdc.m_hDC,(int)npt[0].x-8,(int)npt[0].y-10,8);
		break;
	}
	mdc.CSetLineStyle(0);
	//显示故障标牌
	//if(dbm->lookdown==1||bus->vr.trb==0)  return;
	art=CreateDrawNRt(4,bus->pt,dbm->curzoom);
	cpt=art.CenterPoint();
	npt[0].x=cpt.x;npt[0].y=cpt.y;
	mdc.DPtToScrPt(npt,npt,1,dx,dy,high);
	//cobj.ShowSimg(mdc.m_hDC,(int)npt[0].x-16,(int)npt[0].y-16,3);
	

	bool isshow=false;
	int pos=-1;
	if(bus->vr.alarmband >= 0) //wd
	{
		if (bus->vr.alarmband!=0)
			pos=5;
		//else if(bus->vr.alarmband==0)//不显示挂牌
		else
			pos=100;

		if(pos!=-1)
			isshow=true;
	}

	if(isshow==true)
	{
		PlateInfo plainfo;
		plainfo.m_devid = bus->did;
		plainfo.m_typemenu=EQUIP_TYPE_BUS;
		plainfo.m_subtype=bus->vr.alarmband;		//非图元没有子类型
		plainfo.m_platetype=pos;
		plainfo.m_center=CPoint((int)npt[0].x, (int)npt[0].y);
		plainfo.m_rgn = CreateRectRgn((int)npt[0].x-16, (int)npt[0].y-16, 
			(int)npt[0].x+16, (int)npt[0].y+16);
		
		dbm->AddPlate(plainfo);
	}
} 


//显示百分饼图
void DObj::ShowPctPie(CDIB&mdc,int dx,int dy)
{
	SIZE sz;
	char p[100];
	LOGFONT font;
	CDRect rt;
	DWORD c1,c2;
	double a,b,w1,h1;
	DPOINT dpt[6],cpt;
	int n,w,len;
	N_PCTPIE *pie;
	pie=(N_PCTPIE*)buf;
	b=GetPercent(pie->curval,pie->maxv);


	//如果需要显示短路符号，就显示
	if(pie->showdl==1&&dbm->scf.showrev==9) //必须是断路电流计算
	{
		rt=CreateDrawNRt(4,pie->pt,dbm->curzoom);
		cpt=rt.CenterPoint();
		GetFlashDot(dpt,cpt,dbm->curzoom);
		mdc.D3DrawPoly(dpt,6,0xff,0xff,1,1,dx,dy,0);
		return;
	}

	if(b<dbm->scf.vppe) return;
	a=b>1 ? 1:b;
	c1=pie->color2;
	c2=GetPctPieColor(pie->color1,a);
	rt=CreateDrawNRt(4,pie->pt,dbm->curzoom);
	n=GetPctPieCirclePt(npt,rt,a,dbm->scf.flowover);
	if(a==1) c1=c2;
	mdc.D3Draw2Pie(rt,c1,c2,c2,b,dx,dy);
	//显示百分饼图文字
	if(a>=0.8)
	{
		font=pie->lf;
		sprintf(p,"%d%%",(int)(b*100));
		len=strlen(p);
		w=(int)((rt.Width())/4);
		font.lfHeight=w*2;
		font.lfWidth=w;
		sz=GLDGetTextSize(mdc.m_hDC,&font,p);
		w1=(rt.Width()-sz.cx)/2;
		h1=(rt.Height()-sz.cy)/2;
		dpt[0].x=rt.left+w1;dpt[0].y=rt.top+h1;
		dpt[1].x=rt.right-w1;dpt[1].y=dpt[0].y;
		dpt[2].x=dpt[0].x;dpt[2].y=rt.bottom-h1;
		dpt[3].x=dpt[0].x;dpt[3].y=dpt[2].y;
		SDrawText(mdc.m_hDC,dpt,p,&font,dx,dy,pie->fcolor,DT_LEFT);
	} 


}

//显示发电机的出力及发电机的角度(CDIB)
void DObj::ShowGenPie(CDIB&mdc,CDRect art,float maxv,float curv,int deg,DWORD color,int dx,int dy)
{
	double r;
	double a,v,c;
	if(maxv<=0||curv<=0) return;
	v=curv>maxv ? maxv:curv;
	c=curv/maxv;
	c=c>1 ? 1:c;
    mdc.D3GenPie(art,c,0xff7f7f,dx,dy);
	npt[1]=art.CenterPoint();
	r=art.Width()/2.0f;
	a=deg*mpi/180;
	npt[0].x=npt[1].x+(int)(r*cos(a));
	npt[0].y=npt[1].y-(int)(r*sin(a));
	npt[2].x=art.right;npt[2].y=npt[1].y;
	mdc.DPtToScrPt(npt,npt,3,dx,dy);
	mdc.CDrawDbx(npt,3,color);
}

//根据记录号索引号显示图元组(正常显示专用)
void DObj::PreShowEGPEx(CDIB&mdc,int num,int index,int dx,int dy,int high)
{
	int type;
	N_CIRCLE *clr;
	DObj *bs,bbs;
	DPOINT *spt; 
	DWORD color; 
	CDRect  art; 
	N_ELEGRPA *el;
	int i,j,l,m,dele;
	double xl,yl,w1,w2,h1,h2;
	CDRect rt,rt1,rt2;
	el=(N_ELEGRPA*)buf;
	spt=el->pt;
	switch(index)
	{
	  case 0:
		bs=dbm->egp[num].bs1;
		j=dbm->egp[num].bsum1;
		rt1.SetDRECT(dbm->egp[num].rt1);
		break;
	  case 1:
		bs=dbm->egp[num].bs2;
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
	rt2.left=0;			rt2.top=0;
	rt2.right=rt.left;	rt2.bottom=rt.top;
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	dele=el->vr.ele; //返回设备带电状态
	bbs.dbm=dbm;
	for(i=0;i<j;i++)
	{
		type=bs[i].attr.type;
		if(el->type==1&&el->subtype==1&&type==5&&
			dbm->lookdown==0&&dbm->scf.gendyn==1) continue; //发电机的正弦线是否显示
		bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.MoveObject2(rt2,xl,yl);
		
		//((N_RECT*)bbs.buf).fill = 1;
	/*	if (type == 2)
		{
			N_RECT *p = (N_RECT*)bbs.buf;
			p->fill = index;
		}

		if (type == 1 && i == 3)
		{
			N_DBX *p = (N_DBX*)bbs.buf;
			p->close = 1;
		}*/
		

	//	bs[i].attr.type = 2;
		


		if(el->type==1){ //属于设备，需要动态着色
		  l=bs[i].attr.belong;
		  if(l>0){
			l--;
			l=l>2 ? 0:l;
			m=el->site[l].vl;
			m=m>24 ? 24:m;
			color=dele ? cobj.vcolor[m]:0x7f7f7f;
			if(el->subtype==2) 	
				bbs.SetColor(color);
			else 
				bbs.SetColor(color,1);
		  }
		  
		  if(el->subtype==1){ //发发电机动态处理
			if(type==3&&dbm->lookdown==0&&dbm->scf.gendyn==1){ //发电机动态显示
				clr=(N_CIRCLE*)bbs.buf;
				art=CreateDrawNRt(4,clr->pt,dbm->curzoom);
				bbs.ShowGenPie(mdc,art,el->vr.value[2],el->vr.value[0],(int)el->vr.value[4],color,dx,dy);
			}		
		  }
		}
		bbs.ShowES(mdc,dx,dy,high);
		bbs.FreeMem();
	 }
}


//根据记录号索引号显示图元组(发电机动态显示时)
void DObj::PreShowEGPExDy(CDIB&mdc,int num,int index,int dx,int dy,int high)
{
	N_SIN  *sn;
	DObj *bs,bbs;
	DPOINT *spt; 
	DWORD color; 
	CDRect  art; 
	N_ELEGRPA *el;
	int i,j,m,dele;
	double xl,yl,w1,w2,h1,h2;
	CDRect rt,rt1,rt2;
	el=(N_ELEGRPA*)buf;



	if(dbm->lookdown==1||dbm->scf.gendyn==0) return;
	if(el->type!=1||el->subtype!=1) return; //不是设备中的发电机，返回
	spt=el->pt;
	switch(index)
	{
	  case 0:
		bs=dbm->egp[num].bs1;
		j=dbm->egp[num].bsum1;
		rt1.SetDRECT(dbm->egp[num].rt1);
		break;
	  case 1:
		bs=dbm->egp[num].bs2;
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
	if(w2==0||h2==0)	return;
	rt2.left=0;			rt2.top=0;
	rt2.right=rt.left;	rt2.bottom=rt.top;
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	dele=el->vr.ele; //返回设备带电状态
	bbs.dbm=dbm;
	for(i=0;i<j;i++)
	{
		if(bs[i].attr.type==5) //是正弦波线
		{ 
			bbs.AddObject(bs[i].attr,bs[i].buf);
			bbs.MoveObject2(rt2,xl,yl);
			m=el->site[0].vl;
			m=m>24 ? 24:m;
			color=dele==1 ? cobj.vcolor[m]:0x7f7f7f;
			bbs.SetColor(color,1);
			sn=(N_SIN*)bbs.buf;
			sn->startdeg=el->dydeg;
			bbs.ShowES(mdc,dx,dy,high);
			bbs.FreeMem();
		}
	 }
}

void DObj::ShowEleGrp(CDIB&mdc, int dx, int dy,int high,int active)
{
	int i,eno,lstyle;
	N_ELEGRPA *ep;
	ep=(N_ELEGRPA*)buf;
	i=ep->egrpid;
	if(i<0) return;
	eno=ep->vr.sta;
	eno=eno==0 ? 0:1;
	lstyle=0;
	switch(ep->vr.rp)
	{
	case 1: case 2:
		lstyle=1;
		break;
	case 3:case 4:
		lstyle=2;
		break;
	}
	mdc.CSetLineStyle(lstyle);
	if(active==0) PreShowEGPEx(mdc,i,eno,dx,dy,high);
	else PreShowEGPExDy(mdc,i,eno,dx,dy,high);
	mdc.CSetLineStyle(0);
	//显示故障标牌
	CDRect art;
	CDPoint cpt;
//	if(dbm->lookdown==1||ep->vr.trb==0)  return;
	art=CreateDrawNRt(4,ep->pt,dbm->curzoom);
	cpt=art.CenterPoint();
	npt[0].x=cpt.x;npt[0].y=cpt.y;
	mdc.DPtToScrPt(npt,npt,1,dx,dy,high);
//	cobj.ShowSimg(mdc.m_hDC,(int)npt[0].x-16,(int)npt[0].y-16,3);


	bool isshow=false;
	int pos=-1;

	if (ep->vr.alarmband>=0)
	{
		if (ep->subtype==4 || ep->subtype==5)//电容和电抗
		{
			/*if(ep->vr.alarmband==1 || ep->vr.alarmband==2)//
				pos=5;
			else if(ep->vr.alarmband==4 || ep->vr.alarmband==8)//
				pos=3;
			else
				pos=100;*/
			if(ep->vr.alarmband != 0)
				pos=5;
			else
				pos=100;
		}
		else if (ep->subtype==8 || ep->subtype==7)//三绕组和二绕组
		{
			if(ep->vr.alarmband != 0)
				pos=3;
			else
				pos=100;
		}

		if (ep->type==2) //厂站
		{
			if(ep->vr.alarmband != 0)
				pos=4;
			else
				pos=100;
		}
		if(pos!=-1)
			isshow=true;
	}

	if(isshow==true)
	{
		PlateInfo plainfo;
		plainfo.m_devid = ep->did;
		plainfo.m_typemenu=0;
		plainfo.m_subtype=ep->subtype;

		if(plainfo.m_subtype==1)
			plainfo.m_typemenu=EQUIP_TYPE_GEN;
		else if(plainfo.m_subtype==2)
			plainfo.m_typemenu=EQUIP_TYPE_SWITCH;
		else if(plainfo.m_subtype==3)
			plainfo.m_typemenu=EQUIP_TYPE_LOAD;
		else if(plainfo.m_subtype==4)
			plainfo.m_typemenu=EQUIP_TYPE_SHUNT;
		else if(plainfo.m_subtype==5)
			plainfo.m_typemenu=EQUIP_TYPE_REACT;
		else if(plainfo.m_subtype==6)
			plainfo.m_typemenu=EQUIP_TYPE_GROUP;
		else if(plainfo.m_subtype==7)
			plainfo.m_typemenu=EQUIP_TYPE_BITRS;
		else if(plainfo.m_subtype==8)
			plainfo.m_typemenu=EQUIP_TYPE_TRITRS;
		else if(plainfo.m_subtype==33)
			plainfo.m_typemenu=EQUIP_TYPE_BUS;
		plainfo.m_platetype=pos;
		plainfo.m_center=CPoint((int)npt[0].x, (int)npt[0].y);
		plainfo.m_rgn = CreateRectRgn((int)npt[0].x-16, (int)npt[0].y-16, 
			(int)npt[0].x+16, (int)npt[0].y+16);
		dbm->AddPlate(plainfo);
	}

}

void DObj::ShowYb(CDIB&mdc, int dx, int dy)
{
	int i;
	N_ELEGRPYB *ep;
	if(dbm->lookdown==1||dbm->curang!=0) return; //只在正常时显示
	ep=(N_ELEGRPYB*)buf;
	i=ep->egrpid;
	if(i<0) return;
	PreShowEGPYB(mdc,i,dx,dy);
	ep->show=0;
}


//根据记录号索引号显示图元组(正常显示专用)
void DObj::PreShowEGPYB(CDIB&mdc,int num,int dx,int dy)
{
	DObj *bs,bbs;
	CDRect  art; 
	N_ELEGRPYB *yb;
	int i,j,k,n;
	double xl,yl,w1,w2,h1,h2;
	CDRect rt,rt1,rt2;
	yb=(N_ELEGRPYB*)buf;
	bs=dbm->egp[num].bs1;
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
	rt2.left=0;			rt2.top=0;
	rt2.right=rt.left;	rt2.bottom=rt.top;
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	//将当前值设定
	n=dbm->egp[num].sitesum;
	if(n>0&&n<=8)
	{
		for(i=0;i<n;i++)
		{
			k=dbm->egp[num].index[i];
			if(k>=0&&k<j)
			{
				bs[k].SetMeterVal(yb->curval[i]);
				bs[k].SetMeterMaxMin(yb->umr[i]);
			}
		}
	}
	//显示图形
	bbs.dbm=dbm;
	for(i=0;i<j;i++)
	{
		bbs.AddObject(bs[i].attr,bs[i].buf);
		bbs.MoveObject2(rt2,xl,yl);
		bbs.SetSObjZM(xl);
		bbs.ShowES(mdc,dx,dy,0);
		bbs.FreeMem();
	 }
}


//显示图片
void DObj::ShowImg(CDIB&mdc, int dx, int dy)
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
	SaveDC(mdc.m_hDC);
	PointActToScr(img->pt,npt,2,dbm->curzoom);
	dbm->msr->DPtToScrPt(npt,mpt,2,dx,dy);
	
	if(dbm->curang=0)
	{
		a=GetAngle(npt[0],npt[1]);
		a=-a*mpi/180;
		StartRatate(mdc.m_hDC,a,(float)mpt[0].x,(float)mpt[0].y);
		SetStretchBltMode(mdc.m_hDC,COLORONCOLOR);
		if(img->zoom==1) StretchBlt(mdc.m_hDC,0,0,rt.Width(),rt.Height(),dbm->mpic[i].dc.m_hDC,0,0,dbm->mpic[i].dc.nWidth,dbm->mpic[i].dc.nHeight,SRCCOPY);
		else dbm->mpic[i].dc.BitBlt(mdc.m_hDC,CRect(0,0,rt.Width(),rt.Height()),SRCCOPY);
		RestoreDC(mdc.m_hDC,-1);
		return;
	}
	rt.OffsetRect(dx,dy);
	if(img->zoom==1)
	{
	  SetStretchBltMode(mdc.m_hDC,COLORONCOLOR);
	  StretchBlt(mdc.m_hDC,rt.left,rt.top,rt.Width(),rt.Height(),dbm->mpic[i].dc.m_hDC,0,0,dbm->mpic[i].dc.nWidth,dbm->mpic[i].dc.nHeight,SRCCOPY);
	  return;
	};
	if(img->depth==0)	mdc.TranImgShadow(dbm->mpic[i].dc,rt,img->shadow);
	if(img->depth>0)	mdc.CopyImgPercent(dbm->mpic[i].dc,rt,img->depth);
	
}


void DObj::ShowSysPie(CDIB&mdc, int dx, int dy)
{
	int i;
	SIZE sz;
	double w1,h1;
	CDRect rt;
	char p[100];
	LOGFONT font;
	DPOINT dpt[4];
	DPOINT  tcpt[16];
	N_SYSPIE *pie;
	pie=(N_SYSPIE*)buf;
	rt=CreateDrawNRt(4,pie->pt,dbm->curzoom);
	mdc.D3MPie(rt,&pie->color[1],pie->vl,tcpt,pie->num,pie->color[0],false,dx,dy,0);
	//显示文字
	font=pie->lf;
	font.lfHeight=(int)(font.lfHeight*dbm->curzoom);
	font.lfWidth=(int)(font.lfWidth*dbm->curzoom);
	for(i=0;i<pie->num;i++)
	{
		sprintf(p,"%d%%",(int)(pie->vl[i]*100));
		sz=GLDGetTextSize(mdc.m_hDC,&font,p);
		w1=(sz.cx)/2;
		h1=(sz.cy)/2;
		dpt[0].x=tcpt[i].x-w1;dpt[0].y=tcpt[i].y-h1;
		dpt[1].x=tcpt[i].x+w1;dpt[1].y=tcpt[i].y-h1;
		dpt[2].x=tcpt[i].x+w1;dpt[2].y=tcpt[i].y+h1;
		dpt[3].x=tcpt[i].x-w1;dpt[3].y=tcpt[i].y+h1;
		SDrawText(mdc.m_hDC,dpt,p,&font,dx,dy,pie->fcolor,DT_LEFT);
	}
}  
       
//显示图形对象(HDC专门用于显示组合图元)
void DObj::ShowES(CDIB&mdc,int dx, int dy,int high)
{
	switch(attr.type)
	{
	case 1: ShowDbx(mdc,dx,dy,high,0);			break;
	case 2: ShowRect(mdc,dx,dy,high);			break;
	case 3: ShowCircle(mdc,dx,dy,high);			break;
	case 4: ShowHSin(mdc,dx,dy,high);			break;
	case 5: ShowSin(mdc,dx,dy,high);			break;
	case 6: ShowArc(mdc,dx,dy,high);			break;
	case 7: ShowArrow(mdc,dx,dy,high);			break;
	case 10:ShowText(mdc.m_hDC,dx,dy);			break;
	case 32:ShowMeter1(mdc,dx,dy);				break;
	case 33:ShowMeter2(mdc.m_hDC,dx,dy);		break;
	case 34:ShowMeter3(mdc.m_hDC,dx,dy);		break;
	case 35:ShowMeter4(mdc.m_hDC,dx,dy);		break;
	}
}

//显示到背景上的画面
void DObj::ShowS(CDIB&mdc,int dx,int dy,int high)
{
	
	switch(attr.type)
	{
	case 1: ShowDbx(mdc,dx,dy,high,0);			break;
	case 2: ShowRect(mdc,dx,dy,high);			break;
	case 3: ShowCircle(mdc,dx,dy,high);			break;
	case 4: ShowHSin(mdc,dx,dy,high);			break;
	case 5: ShowSin(mdc,dx,dy,high);			break;
	case 6: ShowArc(mdc,dx,dy,high);			break; 
	case 7: ShowArrow(mdc,dx,dy,high);			break;
	case 8:	ShowGlass(mdc,dx,dy);				break;
	case 10:ShowText(mdc.m_hDC,dx,dy);			break;
	case 13:ShowCoordnate(mdc,dx,dy);			break;
	case 14:ShowTable(mdc,dx,dy);				break;
	case 15:ShowImg(mdc,dx,dy);					break;
	case 64:ShowAnl(mdc.m_hDC,dx,dy,0);			break;
	case 66:ShowEleGrp(mdc,dx,dy,high);			break;
	case 68:ShowSysPie(mdc,dx,dy);				break;
	case 69:ShowBar(mdc,dx,dy);					break;
	case 70:ShowPie(mdc,dx,dy);					break;
	case 75:ShowPush(mdc.m_hDC,dx,dy);			break;
	case 77:ShowFlowLine(mdc,dx,dy,high);		break;
	case 78:ShowConLine(mdc,dx,dy);				break;
	case 79:ShowBus(mdc,dx,dy,high);			break;
	case 82:ShowPctPie(mdc,dx,dy);				break;
	case 83:ShowZone(mdc,dx,dy);				break;
	case 84:ShowMTText(mdc.m_hDC,dx,dy,0);		break;
	}
}   

//显示到背景上的画面
void DObj::ShowAct(CDIB&mdc,int dx,int dy)
{
	switch(attr.type)
	{
	case 65:ShowReservoir(mdc,dx,dy);		break;
	case 66:ShowEleGrp(mdc,dx,dy,0,1);		break;
	case 67:ShowYb(mdc,dx,dy);				break;
	case 71:ShowDate(mdc,dx,dy);			break;
	case 72:ShowTime(mdc,dx,dy);			break;
	case 73:ShowGifAnl(mdc.m_hDC,dx,dy);	break;
	case 74:ShowScrText(mdc,dx,dy);			break;
	case 75:ShowPush(mdc.m_hDC,dx,dy);		break;
	case 77:ShowFlow(mdc,dx,dy);			break;
	//case 83:ShowZone(mdc,dx,dy);			break;
	}
}   