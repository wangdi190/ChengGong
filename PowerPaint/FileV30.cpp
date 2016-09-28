// FileV30.cpp: implementation of the FileV30 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FileV30.h"
#include "base0.h"
#include "bclass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FileV30::FileV30()
{
	
}

FileV30::~FileV30()
{
	
}

//返回版本5保存所需字节数
int FileV30::GetV5Size(BASE0 &bs,int mode)
{
	int m,n;
	N_RESERVOIR *rv;
	N_DBX *dbx;
	N_TEXT *txt;
	N_PATH *path;
	N_SRLTEXT *stxt;
	N_FLOW *flw;
	N_CONLINE *con;
	N_ZONE    *zon;
	if(mode==0) m=sizeof(N5_BASATTR);
	else m=0;
	switch(bs.attr.type)
	{
	case 1: //多边形
		dbx=(N_DBX*)bs.buf;
		n=dbx->ptsum;
		m=m+sizeof(N5_DBX)+n*sizeof(DPOINT);
		break;
	case 2: case 3://矩形，园
		m=m+sizeof(N5_RECT);
		break;
	case 4: //正弦半波形
		m=m+sizeof(N5_HSIN);
		break;
	case 5: //正弦波形
		m=m+sizeof(N5_SIN);
		break;
	case 6: //园弧
		m=m+sizeof(N5_ARC);
		break;
	case 7: //方向箭头
		m=m+sizeof(N5_ARROW);
		break;
	case 8: //玻璃层
		m=m+sizeof(N5_GLASS);
		break;
	case 10://文本
		txt=(N_TEXT*)bs.buf;
		n=strlen(txt->text);
		m=m+sizeof(N5_TEXT)+n+4;
		break;
	case 11://电气端子
		m=m+sizeof(N5_ESITE);
		break;
	case 12://组合图元母板
		m=m+sizeof(N5_EGPMB);
		break;
	case 13: //坐标
		m=m+sizeof(N5_COORDINATE);
		break;
	case 14://表格线
		m=m+sizeof(N5_TABLE);
		break;
	case 15://静态图形
		m=m+sizeof(N5_IMG);
		break;
	case 16://路径
		path=(N_PATH*)bs.buf;
		n=path->ptsum;
		m=m+sizeof(N5_PATH)+n*sizeof(DPOINT);
		break;
	case 17://静态小图标
		m=m+sizeof(N5_SPIC);
		break;
	case 32:
		m=m+sizeof(N5_METER1);
		break;
	case 33:
		m=m+sizeof(N5_METER2);
		break;
	case 34:
		m=m+sizeof(N5_METER3);
		break;
	case 35:
		m=m+sizeof(N5_METER4);
		break;
	case 64://模拟量显示结构
		m=m+sizeof(N5_ANL);
		break;
	case 65://水库
		rv=(N_RESERVOIR*)bs.buf;
		m=m+sizeof(N5_RESERVOIR)+rv->ptsum*sizeof(DPOINT);
		break;
	case 66://组合图元显示结构
		m=m+sizeof(N5_ELEGRPA);
		break;
	case 67://组合仪表结构
		m=m+sizeof(N5_ELEGRPYB);
		break;
	case 68:
		m=m+sizeof(N5_SYSPIE);
		break;
	case 69://棒图
		m=m+sizeof(N5_BAR);
		break;
	case 70://饼图结构数据
		m=m+sizeof(N5_PIE);
		break;
	case 71:case 72://日期格式,时间格式
		m=m+sizeof(N5_DATE);
		break;
	case 73://动画图形
		m=m+sizeof(N5_GIFAML);
		break;
	case 74://滚动文本
		stxt=(N_SRLTEXT*)bs.buf;
		n=strlen(stxt->text);
		m=m+sizeof(N5_SRLTEXT)+n;
		break;
	case 75://按钮格式
		m=m+sizeof(N5_PUSH);
		break;
	case 76://自助控件
		m=m+sizeof(N5_SELFCTL);
		break;
	case 77://潮流线
		flw=(N_FLOW*)bs.buf;
		n=flw->ptsum;
		m=m+sizeof(N5_FLOW)+n*sizeof(DPOINT);
		break;
	case 78://连接线
		con=(N_CONLINE*)bs.buf;
		n=con->ptsum;
		m=m+sizeof(N5_CONLINE)+n*sizeof(DPOINT);
		break;
	case 79://母线
		m=m+sizeof(N5_BUS);
		break;
	case 80://小型活动对象
		m=m+sizeof(N5_ACTOBJ);
		break;
	case 81://FLASH对象
		m=m+sizeof(N5_FLASH);
		break;
	case 82://百分比饼图
		m=m+sizeof(N5_PCTPIE);
		break;
	case 83:
		zon=(N_ZONE*)bs.buf;
		m=m+sizeof(N5_ZONE)+zon->ptsum*sizeof(DPOINT);
		break;
	case 84:
		m=m+sizeof(N5_MTTEXT);
		break;
	}
	return m;
}

//将格式转换为V3，并存在相应的内存中
int FileV30::CopyV5Data(BASE0 &bs, char *lp)
{
	int m;
	char *lp1;
	N5_BASATTR *a5;
	lp1=lp;
	a5=(N5_BASATTR*)lp1;
	a5->belong=bs.attr.belong;
	a5->ID=(WORD)bs.attr.ID;
	m=GetV5Size(bs,1);
	a5->size=(WORD)m;
	a5->type=(BYTE)bs.attr.type;
	lp1+=sizeof(N5_BASATTR);
	//转换数据到V3版
	ConvertDataToV5(bs.buf,lp1,bs.attr.type);
	//////////////////
	return m+sizeof(N5_BASATTR);
}

//转换数据到V5版
void FileV30::ConvertDataToV5(void *data, void *lp, int type)
{
	switch(type)
	{
	case 1: //多边形
		DbxToV5(data,lp);
		break;
	case 2: case 3://矩形，园
		RectToV5(data,lp);
		break;
	case 4: //正弦半波形
		HsinToV5(data,lp);
		break;
	case 5: //正弦波形
		SinToV5(data,lp);
		break;
	case 6: //园弧
		ArcToV5(data,lp);
		break;
	case 7: //方向箭头
		ArrowToV5(data,lp);
		break;
	case 8: //玻璃层
		GlassToV5(data,lp);
		break;
	case 10://文本
		TextToV5(data,lp);
		break;
	case 11://电气端子
		SiteToV5(data,lp);
		break;
	case 12://组合图元母板
		MBoardToV5(data,lp);
		break;
	case 13: //坐标
		CoordToV5(data,lp);
		break;
	case 14://表格线
		TableToV5(data,lp);
		break;
	case 15://静态图形
		SpicToV5(data,lp);
		break;
	case 16://路径
		PathToV5(data,lp);
		break;
	case 17://静态小图标
		PicToV5(data,lp);
		break;
	case 32:
		Meter1ToV5(data,lp);
		break;
	case 33:
		Meter2ToV5(data,lp);
		break;
	case 34:
		Meter3ToV5(data,lp);
		break;
	case 35:
		Meter4ToV5(data,lp);
		break;
	case 64://模拟量显示结构
		AnlToV5(data,lp);
		break;
	case 65://水库
		ReservoirToV5(data,lp);
		break;
	case 66://组合图元显示结构
		ElegToV5(data, lp);
		break;
	case 67:
		YBToV5(data,lp);
		break;
	case 68:
		SysPieToV5(data,lp);
		break;
	case 69://棒图
		BarToV5(data,lp);
		break;
	case 70://饼图结构数据
		PieToV5(data,lp);
		break;
	case 71:case 72://日期格式,时间格式
		DateToV5(data,lp);
		break;
	case 73://动画图形
		GifToV5(data,lp);
		break;
	case 74://滚动文本
		ScrtxtToV5(data,lp);
		break;
	case 75://按钮格式
		PushToV5(data,lp);
		break;
	case 76://自助控件
		SelfToV5(data,lp);
		break;
	case 77://潮流线
		FlowToV5(data, lp);
		break;
	case 78://连接线
		ConlToV5(data,lp);
		break;
	case 79://母线
		BusToV5(data,lp);
		break;
	case 80://小型活动对象
		ActToV5(data,lp);
		break;
	case 81://FLASH对象
		FlashToV5(data, lp);
		break;
	case 82://百分比饼图
		PctToV5(data, lp);
		break;
	case 83://区域
		ZoneToV5(data,lp);
		break;
	case 84://多行文本
		MttextToV5(data,lp);
		break;
	}
}

void FileV30::DbxToV5(void *data, void *lp)
{
	int i;
	N_DBX   *d1;
	N5_DBX  *d2;
	d1=(N_DBX*)data;
	d2=(N5_DBX*)lp;
	d2->bgmode=d1->bgmode;
	d2->close=d1->close;
	d2->bcolor1=d1->bcolor1;
	d2->fill=d1->fill;
	d2->fillmode=d1->fillmode;
	d2->lcolor=d1->lcolor;
	d2->ltype=d1->ltype;
	d2->ptsum=d1->ptsum;
	d2->bgmode=d1->bgmode;
	for(i=0;i<d2->ptsum;i++) d2->pt[i]=d1->pt[i];
}

void FileV30::RectToV5(void *data, void *lp)
{
	N_RECT  *r1;
	N5_RECT *r2;
	r1=(N_RECT*)data;
	r2=(N5_RECT*)lp;
	r2->bcolor1=r1->bcolor1;
	r2->fill=r1->fill;
	r2->fillmode=r1->fillmode;
	r2->lcolor=r1->lcolor;
	r2->type=r1->type;
	r2->rt=CreateNRt(4,r1->pt);
}

void FileV30::HsinToV5(void *data, void *lp)
{
	N_HSIN  *h1;
	N5_HSIN *h2;
	h1=(N_HSIN*)data;
	h2=(N5_HSIN*)lp;
	h2->color=h1->color;
	h2->hv=h1->ltype;
	h2->pirodic=h1->pirodic;
	h2->rt=CreateNRt(4,h1->pt);
}

void FileV30::SinToV5(void *data, void *lp)
{
	N_SIN *s1;
	N5_SIN *s2;
	s1=(N_SIN*)data;
	s2=(N5_SIN*)lp;
	s2->color=s1->color;
	s2->hv=s1->ltype;
	s2->pirodic=s1->pirodic;
	s2->startdeg=s1->startdeg;
	s2->rt=CreateNRt(4,s1->pt);
}

void FileV30::ArcToV5(void *data, void *lp)
{
	N_ARC  *a1;
	N5_ARC *a2;
	a1=(N_ARC*)data;
	a2=(N5_ARC*)lp;
	a2->color=a1->color;
	a2->end=a1->end;
	a2->start=a1->start;
	a2->rt=CreateNRt(4,a1->pt);
}

void FileV30::ArrowToV5(void *data, void *lp)
{
	N_ARROW *a1;
	N5_ARROW *a2;
	a1=(N_ARROW*)data;
	a2=(N5_ARROW*)lp;
	a2->color=a1->color;
	memcpy(a2->pt,a1->pt,2*sizeof(DPOINT));
}

void FileV30::GlassToV5(void *data, void *lp)
{
	N_GLASS *g1;
	N5_GLASS *g2;
	g1=(N_GLASS*)data;
	g2=(N5_GLASS*)lp;
	g2->color=g1->color;
	g2->depth=g1->depth;
	g2->lcolor=g1->ocolor;
	g2->outline=g1->outline;
	g2->rt=CreateNRt(4,g1->pt);
}

void FileV30::TextToV5(void *data, void *lp)
{
	N_TEXT *t1;
	N5_TEXT *t2;
	t1=(N_TEXT*)data;
	t2=(N5_TEXT*)lp;
	t2->color=t1->color;
	t2->font=t1->font;
	t2->style=t1->style;
	t2->zm=1;
	t2->angle=0;
	t2->autofit=t1->autofill;
	strcpy(t2->text,t1->text);
	t2->rt=CreateNRt(4,t1->pt);
}

void FileV30::SiteToV5(void *data, void *lp)
{
	N_ESITE *e1;
	N5_ESITE *e2;
	e1=(N_ESITE*)data;
	e2=(N5_ESITE*)lp;
	e2->color=e1->color;
	e2->solder=e1->solder;
	e2->rt=CreateNRt(4,e1->pt);
}

void FileV30::MBoardToV5(void *data, void *lp)
{
	N_EGPMB *m1;
	N5_EGPMB *m2;
	m1=(N_EGPMB*)data;
	m2=(N5_EGPMB*)lp;
	m2->color=m1->color;
	m2->mode=m1->mode;
	m2->rt=CreateNRt(4,m1->pt);
}

void FileV30::CoordToV5(void *data, void *lp)
{
	N_COORDINATE *c1;
	N5_COORDINATE *c2;
	c1=(N_COORDINATE*)data;
	c2=(N5_COORDINATE*)lp;
	c2->colorc=c1->colorc;
	c2->colort=c1->colort;
	c2->colorw=c1->colorw;
	c2->fontx=c1->fontx;
	c2->fonty=c1->fonty;
	c2->wxdraw=c1->wxdraw;
	c2->wydraw=c1->wydraw;
	c2->xdot=c1->xdot;
	c2->xmax=c1->xmax;
	c2->xmin=c1->xmin;
	c2->xvshow=c1->xvshow;
	c2->ydot=c1->ydot;
	c2->ymax=c1->ymax;
	c2->ymin=c1->ymin;
	c2->yvshow=c1->yvshow;
	c2->rt=CreateNRt(4,c1->pt);
}

void FileV30::TableToV5(void *data, void *lp)
{
	N_TABLE  *t1;
	N5_TABLE *t2;
	t1=(N_TABLE*)data;
	t2=(N5_TABLE*)lp;
	t2->color=t1->color;
	t2->dbline=t1->dbline;
	t2->line=t1->line;
	t2->width=t1->width;
	t2->rt=CreateNRt(4,t1->pt);
}

void FileV30::SpicToV5(void *data, void *lp)
{
	N_IMG  *m1;
	N5_IMG *m2;
	m1=(N_IMG*)data;
	m2=(N5_IMG*)lp;
	m2->depth=m1->depth;
	m2->imgID=m1->imgID;
	m2->shadow=m1->shadow;
	m2->zoom=m1->zoom;
	m2->rt=CreateNRt(4,m1->pt);
}

void FileV30::Meter1ToV5(void *data, void *lp)
{
	int i;
	N5_METER1 *m2;
	N_METER1  *m1;
	m2=(N5_METER1*)lp;
	m1=(N_METER1*)data;
	for(i=0;i<2;i++)  m2->pt[i]=m1->pt[i];
	m2->font=m1->font;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showarc=m1->showarc;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;	
	m2->slen=m1->slen;
	m2->angle=m1->angle;		
	m2->pstyle=m1->pstyle;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;
	m2->axw=m1->axw;
	m2->pw=m1->pw;
	m2->stype=m1->stype;
	m2->lstype=m1->lstype;
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];	
}

void FileV30::Meter2ToV5(void *data, void *lp)
{
	int i;
	N5_METER2 *m2;
	N_METER2  *m1;
	m2=(N5_METER2*)lp;
	m1=(N_METER2*)data;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showbl=m1->showbl;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;		
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];	
	m2->rt=CreateNRt(4,m1->pt);
}



void FileV30::Meter3ToV5(void *data, void *lp)
{
	int i;
	N5_METER3 *m2;
	N_METER3  *m1;
	m2=(N5_METER3*)lp;
	m1=(N_METER3*)data;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showbl=m1->showbl;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;		
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];	
	m2->rt=CreateNRt(4,m1->pt);	
}

void FileV30::Meter4ToV5(void *data, void *lp)
{
	int i;
	N5_METER4 *m2;
	N_METER4  *m1;
	m2=(N5_METER4*)lp;
	m1=(N_METER4*)data;
	m2->num=m1->num;			
	m2->numdot=m1->numdot;			
	m2->bcr=m1->bcr;			
	for(i=0;i<2;i++) m2->ncr[i]=m1->ncr[i];
	m2->rt=CreateNRt(4,m1->pt);	
}

void FileV30::PathToV5(void *data, void *lp)
{
	N_PATH  *p1;
	N5_PATH *p2;
	p1=(N_PATH*)data;
	p2=(N5_PATH*)lp;
	p2->ID=p1->ID;
	p2->ptsum=p1->ptsum;
	memcpy(p2->pt,p1->pt,p1->ptsum*sizeof(DPOINT));
}

void FileV30::PicToV5(void *data, void *lp)
{
	N_SPIC *s1;
	N5_SPIC *s2;
	s1=(N_SPIC*)data;
	s2=(N5_SPIC*)lp;
	s2->picID=s1->picID;
	s2->zoom=s1->zoom;
	s2->rt=CreateNRt(4,s1->pt);
}

void FileV30::AnlToV5(void *data, void *lp)
{
	N_ANL *a1;
	N5_ANL *a2;
	a1=(N_ANL*)data;
	a2=(N5_ANL*)lp;
	a2->acolor=a1->acolor;
	a2->angle=a1->direction==0 ? 0:900;
	strcpy(a2->dev_name,a1->dev_name);
	a2->did=a1->did;
	a2->dtype=a1->dtype;
	a2->lf=a1->lf;
	a2->ncolor=a1->ncolor;
	a2->style=a1->style;
	a2->xs=a1->xs;
	a2->xsmode=a1->xsmode;
	a2->rt=CreateNRt(4,a1->pt);
}

void FileV30::ReservoirToV5(void *data, void *lp)
{
	int i;
	N_RESERVOIR *a1;
	N5_RESERVOIR *a2;
	a1=(N_RESERVOIR*)data;
	a2=(N5_RESERVOIR*)lp;
	a2->color=a1->color;
	strcpy(a2->dev_name,a1->dev_name);
	a2->did=a1->did;
	a2->hcolor=a1->hcolor;
	a2->lcolor=a1->lcolor;
	a2->ncolor=a1->ncolor;
	a2->ptsum=a1->ptsum;
	for(i=0;i<a2->ptsum;i++)
	{
		a2->pt[i]=a1->pt[i];
	}
	
}

void FileV30::ElegToV5(void *data, void *lp)
{
	N_ELEGRPA *e1;
	N5_ELEGRPA *e2;
	e1=(N_ELEGRPA*)data;
	e2=(N5_ELEGRPA*)lp;
	strcpy(e2->dev_name,e1->dev_name);
	e2->did=e1->did;
	e2->egrpid=e1->egrpid;
	e2->genrev=e1->genrev;
	e2->runshow=e1->runshow;
	e2->showno=e1->showno;
	e2->sitesum=e1->sitesum;
	e2->type=e1->type;
	e2->subtype=e1->subtype;
	e2->rt=CreateNRt(4,e1->pt);
	memcpy(e2->site,e1->site,3*sizeof(D_SITE));
}


void FileV30::YBToV5(void *data, void *lp)
{
	int i,j;
	N_ELEGRPYB *e1;
	N5_ELEGRPYB *e2;
	e1=(N_ELEGRPYB*)data;
	e2=(N5_ELEGRPYB*)lp;
	e2->egrpid=e1->egrpid;
	e2->dbsum=e1->dbsum;
	for(i=0;i<8;i++){
		strcpy(e2->dbs[i].name,e1->dbs[i].name);
		e2->dbs[i].did=e1->dbs[i].did;
		e2->dbs[i].dtype=e1->dbs[i].dtype;
		e2->dbs[i].xsmode=e1->dbs[i].xsmode;
		e2->pam[i].ptype=e1->pam[i].ptype;
		e2->pam[i].vmin=e1->pam[i].vmin;
		e2->pam[i].vmax=e1->pam[i].vmax;
		e2->pam[i].alarm=e1->pam[i].alarm;
		for(j=0;j<4;j++) e2->pam[i].val[j]=e1->pam[i].val[j];
		for(j=0;j<2;j++) e2->pam[i].color[j]=e1->pam[i].color[j];
	}
	e2->rt=CreateNRt(4,e1->pt);
}

void FileV30::SysPieToV5(void *data, void *lp)
{
	N_SYSPIE *p1;
	N5_SYSPIE *p2;
	p1=(N_SYSPIE*)data;
	p2=(N5_SYSPIE*)lp;
	p2->lf=p1->lf;
	p2->ID=p1->ID;
	memcpy(p2->color,p1->color,24);
	p2->fcolor=p1->fcolor;
	p2->type=p1->type;
	p2->rt=CreateNRt(4,p1->pt);
}

void FileV30::BarToV5(void *data, void *lp)
{
	N_BAR *b1;
	N5_BAR *b2;
	b1=(N_BAR*)data;
	b2=(N5_BAR*)lp;
	b2->acolor=b1->acolor;
	b2->aval=b1->aval;

//	b2->dsrc=b1->dsrc;
	strcpy(b2->dsrc.name,b1->dsrc.name);
	b2->dsrc.did=b1->dsrc.did;
	b2->dsrc.dtype=b1->dsrc.dtype;
	b2->dsrc.xsmode=b1->dsrc.xsmode;

	b2->max=b1->max;
	b2->min=b1->min;
	b2->ncolor=b1->ncolor;
	b2->outline=b1->outline;
	b2->style=b1->style;
	b2->xy=b1->xy;
	b2->rt=CreateNRt(4,b1->pt);
}

void FileV30::PieToV5(void *data, void *lp)
{
	N_PIE *p1;
	N5_PIE *p2;
	p1=(N_PIE*)data;
	p2=(N5_PIE*)lp;
	p2->lf=p1->lf;
	memcpy(p2->color,p1->color,12);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	p2->type=p1->type;
	strcpy(p2->name,p1->name);
	p2->rt=CreateNRt(4,p1->pt);
	/*N_PIE *p1;
	N5_PIE *p2;
	p1=(N_PIE*)data;
	p2=(N5_PIE*)lp;
	p2->angle=p1->angle;
	memcpy(p2->color,p1->color,32);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	strcpy(p2->name,p1->name);
	p2->outline=p1->outline;
	memcpy(p2->pd,p1->pd,8*sizeof(NPIEDAT));
	p2->shad=p1->shad;
	p2->style=p1->style;
	p2->sum=p1->sum;
	p2->rt=CreateNRt(4,p1->pt);*/
}

void FileV30::DateToV5(void *data, void *lp)
{
	N_DATE *d1;
	N5_DATE *d2;
	d1=(N_DATE*)data;
	d2=(N5_DATE*)lp;
	d2->bcolor=d1->bcolor;
	d2->fcolor=d1->fcolor;
	d2->fmt=d1->fmt;
	d2->font=d1->font;
	d2->outcolor=d1->outcolor;
	d2->shadow=d1->shadow;
	d2->tran=(unsigned)d1->tran;
	d2->zm=1;
	d2->outline=d1->outline;
	d2->rt=CreateNRt(4,d1->pt);
}

void FileV30::GifToV5(void *data, void *lp)
{
	N_GIFAML *g1;
	N5_GIFAML *g2;
	g1=(N_GIFAML*)data;
	g2=(N5_GIFAML*)lp;
	//g2->dsrc=g1->dsrc;

	strcpy(g2->dsrc.name,g1->dsrc.name);
	g2->dsrc.did=g1->dsrc.did;
	g2->dsrc.dtype=g1->dsrc.dtype;
	g2->dsrc.xsmode=g1->dsrc.xsmode;

	strcpy(g2->fname,g1->fname);
	g2->rec=g1->rec;
	g2->rt=CreateNRt(4,g1->pt);
}

void FileV30::ScrtxtToV5(void *data, void *lp)
{
	N_SRLTEXT *s1;
	N5_SRLTEXT *s2;
	s1=(N_SRLTEXT*)data;
	s2=(N5_SRLTEXT*)lp;
	s2->align=s1->align;
	s2->depth=s1->depth;
	s2->direct=s1->direct;
	s2->fcolor=s1->fcolor;
	s2->gcolor=s1->gcolor;
	s2->glass=s1->glass;
	s2->lf=s1->lf;
	s2->outline=s1->outline;
	s2->tcolor=s1->tcolor;
	s2->zm=1;
	strcpy(s2->text,s1->text);
	s2->rt=CreateNRt(4,s1->pt);
}

void FileV30::PushToV5(void *data, void *lp)
{
	N_PUSH *p1;
	N5_PUSH *p2;
	p1=(N_PUSH*)data;
	p2=(N5_PUSH*)lp;
	p2->autlin=p1->autlin;
	p2->cmdnum=p1->cmdnum;
	p2->cmdtype=p1->cmdtype;
	p2->color1=p1->color1;
	p2->color2=p1->color2;
	strcpy(p2->command,p1->command);
	p2->lf=p1->lf;
	p2->selfid=p1->selfid;
	p2->shadow=p1->shadow;
	p2->spicid=p1->spicid;
	p2->style=p1->style;
	strcpy(p2->title,p1->title);
	p2->zm=1;
	p2->tosta=p1->tosta;
	p2->rt=CreateNRt(4,p1->pt);
}

void FileV30::SelfToV5(void *data, void *lp)
{
	N_SELFCTL *s1;
	N5_SELFCTL *s2;
	s1=(N_SELFCTL*)data;
	s2=(N5_SELFCTL*)lp;
	s2->abottom=s1->abottom;
	s2->aleft=s1->aleft;
	s2->aright=s1->aright;
	s2->atop=s1->atop;
	strcpy(s2->dllname,s1->dllname);
	s2->id=s1->id;
	memcpy(s2->lkbuf,s1->lkbuf,255);
	s2->mode=s1->mode;
	s2->style=s1->style;
	s2->rt=CreateNRt(4,s1->pt);
}

void FileV30::FlowToV5(void *data, void *lp)
{
	N_FLOW *f1;
	N5_FLOW *f2;
	f1=(N_FLOW*)data;
	f2=(N5_FLOW*)lp;
	f2->color1=f1->color1;
	f2->color2=f1->color2;
	strcpy(f2->dev_name,f1->dev_name);
	f2->did=f1->did;
	f2->direct=f1->direct;
	f2->ptsum=f1->ptsum;
	memcpy(f2->site,f1->site,2*sizeof(D_SITEB));
	f2->style=f1->style;
	f2->type=f1->type;
	f2->vl=f1->vl;
	f2->linewidth=f1->linewidth;
	memcpy(f2->pt,f1->pt,f1->ptsum*sizeof(DPOINT));
}

void FileV30::ConlToV5(void *data, void *lp)
{
	N_CONLINE *c1;
	N5_CONLINE *c2;
	c1=(N_CONLINE*)data;
	c2=(N5_CONLINE*)lp;
	c2->conobj=c1->conobj;
	memcpy(c2->lobj,c1->lobj,2*sizeof(LOGOBJ));
	c2->ptsum=c1->ptsum;
	c2->solder1=c1->solder1;
	c2->solder2=c1->solder2;
	c2->vl=c1->vl;
	memcpy(c2->pt,c1->pt,c2->ptsum*sizeof(DPOINT));
}

void FileV30::BusToV5(void *data, void *lp)
{
	N_BUS *b1;
	N5_BUS *b2;
	b1=(N_BUS*)data;
	b2=(N5_BUS*)lp;
	strcpy(b2->dev_name,b1->dev_name);
	b2->did=b1->did;
	b2->eid=b1->eid;
	b2->type=b1->type;
	b2->valarm=b1->valarm;
	b2->vl=b1->vl;
	b2->rt=CreateNRt(4,b1->pt);
}

void FileV30::ActToV5(void *data, void *lp)
{
	N_ACTOBJ  *a1;
	N5_ACTOBJ *a2;
	a1=(N_ACTOBJ*)data;
	a2=(N5_ACTOBJ*)lp;
	//a2->dsrc=a1->dsrc;
	strcpy(a2->dsrc.name,a1->dsrc.name);
	a2->dsrc.did=a1->dsrc.did;
	a2->dsrc.dtype=a1->dsrc.dtype;
	a2->dsrc.xsmode=a1->dsrc.xsmode;

	a2->gid=a1->gid;
	a2->pathid=a1->pathid;
	a2->runmode=a1->runmode;
	a2->skip=a1->skip;
	a2->speed=a1->speed;
	a2->rt=CreateNRt(4,a1->pt);
}

void FileV30::FlashToV5(void *data, void *lp)
{
	N_FLASH  *f1;
	N5_FLASH *f2;
	f1=(N_FLASH*)data;
	f2=(N5_FLASH*)lp;
	f2->align_buttom=f1->align_buttom;
	f2->align_left=f1->align_left;
	f2->align_right=f1->align_right;
	f2->align_top=f1->align_top;
	strcpy(f2->fname,f1->fname);
	f2->playmode=f1->playmode;
	f2->rt=CreateNRt(4,f1->pt);
}

void FileV30::PctToV5(void *data, void *lp)
{
	N_PCTPIE *p1;
	N5_PCTPIE *p2;
	p1=(N_PCTPIE*)data;
	p2=(N5_PCTPIE*)lp;
	p2->color1=p1->color1;
	p2->color2=p1->color2;
	strcpy(p2->dev_name,p1->dev_name);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	p2->lf=p1->lf;
	p2->maxv=p1->maxv;
	p2->type=p1->type;
	p2->zm=1;
	p2->rt=CreateNRt(4,p1->pt);
}

void FileV30::ZoneToV5(void *data, void *lp)
{
	int i;
	N_ZONE *p1;
	N5_ZONE *p2;
	p1=(N_ZONE*)data;
	p2=(N5_ZONE*)lp;
	p2->lcolor=p1->lcolor;
	strcpy(p2->zone_name,p1->zone_name);
	p2->lf=p1->lf;
	p2->fcolor=p1->fcolor;
	p2->did=p1->did;
	p2->ptsum=p1->ptsum;
	for(i=0;i<p2->ptsum;i++) p2->pt[i]=p1->pt[i];

}

void FileV30::MttextToV5(void *data, void *lp)
{
	N_MTTEXT *p1;
	N5_MTTEXT *p2;
	p1=(N_MTTEXT*)data;
	p2=(N5_MTTEXT*)lp;
	p2->fcolor=p1->fcolor;
	strcpy(p2->name,p1->name);
	p2->lf=p1->lf;
	p2->did=p1->did;
	p2->type=p1->type;
	strcpy(p2->text,p1->text);
	p2->rt=CreateNRt(4,p1->pt);
}

//将V2版本的内容转换到基本类中
int FileV30::GetBsFromV2(void *lp1, N_BASATTR &btr, void *lp2)
{
	char *lp;
	lp=(char*)lp1;
	N2_BASATTR *ar2;
	ar2=(N2_BASATTR*)lp1;
	btr.belong=ar2->belong;
	btr.ID=ar2->ID;
	btr.type=ar2->type;
	lp+=sizeof(N2_BASATTR);
	btr.size=0;
	//按每种类型转换
	switch(ar2->type)
	{
	case 1: //多边形
		btr.size=V2DbxToBs(lp,lp2);
		break;
	case 2: case 3://矩形，园
		btr.size=V2RectToBs(lp,lp2);
		break;
	case 4: //正弦半波形
		btr.size=V2HsinToBs(lp,lp2);
		break;
	case 5: //正弦波形
		btr.size=FileV30::V2SinToBs(lp,lp2);
		break;
	case 6: //园弧
		btr.size=V2ArcToBs(lp,lp2);
		break;
	case 7: //方向箭头
		btr.size=V2ArrowToBs(lp,lp2);
		break;
	case 8: //玻璃层
		btr.size=V2GlassToBs(lp,lp2);
		break;
	case 10://文本
		btr.size=V2TextToBs(lp,lp2);
		break;
	case 11://电气端子
		btr.size=V2SiteToBs(lp,lp2);
		break;
	case 12://组合图元母板
		btr.size=V2MBoardToBs(lp,lp2);
		break;
	case 13: //坐标
		btr.size=V2CoordToBs(lp,lp2);
		break;
	case 14://表格线
		btr.size=V2TableToBs(lp,lp2);
		break;
	case 15://静态图形
		btr.size=V2SpicToBs(lp,lp2);
		break;
	case 16://路径
		btr.size=V2PathToBs(lp,lp2);
		break;
	case 17://静态小图标
		btr.size=V2PicToBs(lp,lp2);
		break;
	case 64://模拟量显示结构
		btr.size=V2AnlToBs(lp,lp2);
		break;
	case 66://组合图元显示结构
		btr.size=V2ElegToBs(lp,lp2);
		break;
	case 69://棒图
		btr.size=V2BarToBs(lp,lp2);
		break;
	case 70://饼图结构数据
		btr.size=V2PieToBs(lp,lp2);
		break;
	case 71:case 72://日期格式,时间格式
		btr.size=V2DateToBs(lp,lp2);
		break;
	case 73://动画图形
		btr.size=V2GifToBs(lp,lp2);
		break;
	case 74://滚动文本
		btr.size=V2ScrtxtToBs(lp,lp2);
		break;
	case 75://按钮格式
		btr.size=V2PushToBs(lp,lp2);
		break;
	case 76://自助控件
		btr.size=V2SelfToBs(lp,lp2);
		break;
	case 77://潮流线
		btr.size=V2FlowToBs(lp,lp2);
		break;
	case 78://连接线
		btr.size=V2ConlToBs(lp,lp2);
		break;
	case 79://母线
		btr.size=V2BusToBs(lp,lp2);
		break;
	case 80://小型活动对象
		btr.size=V2ActToBs(lp,lp2);
		break;
	case 81://FLASH对象
		btr.size=V2FlashToBs(lp,lp2);
		break;
	case 82://百分比饼图
		btr.size=V2PctToBs(lp,lp2);
		break;
	}
	return sizeof(N2_BASATTR)+ar2->size; //返回已使用字节数
}

int FileV30::V2DbxToBs(void *lp, void *lp2)
{
	int s;
	N2_DBX *d1;
	N_DBX  *d2;
	d1=(N2_DBX*)lp;
	d2=(N_DBX*)lp2;
	d2->bcolor1=d1->bcolor1;
	d2->fill=d1->fill;
	d2->close=d1->close;
	d2->fillmode=d1->fillmode;
	d2->lcolor=d1->lcolor;
	d2->ltype=d1->ltype;
	d2->ptsum=d1->ptsum;
	d2->bgmode=0;
	memcpy(d2->pt,d1->pt,d1->ptsum*sizeof(DPOINT));
	s=sizeof(N_DBX)+d1->ptsum*sizeof(DPOINT);
	return s;
}

int FileV30::V2RectToBs(void *lp, void *lp2)
{
	N2_RECT  *r1;
	N_RECT   *r2;
	r1=(N2_RECT*)lp;
	r2=(N_RECT*)lp2;
	r2->bcolor1=r1->bcolor1;
	r2->fill=r1->fill;
	r2->fillmode=r1->fillmode;
	r2->lcolor=r1->lcolor;
	r2->type=r1->type;
	memcpy(r2->pt,r1->pt,4*sizeof(DPOINT));
	return sizeof(N_RECT);
}

int FileV30::V2HsinToBs(void *lp, void *lp2)
{
	N2_HSIN  *h1;
	N_HSIN   *h2;
	h1=(N2_HSIN*)lp;
	h2=(N_HSIN*)lp2;
	h2->color=h1->color;
	h2->ltype=h1->ltype;
	h2->pirodic=h1->pirodic;
	memcpy(h2->pt,h1->pt,4*sizeof(DPOINT));
	return sizeof(N_HSIN);
}

int FileV30::V2SinToBs(void *lp, void *lp2)
{
	N2_SIN *s1;
	N_SIN *s2;
	s1=(N2_SIN*)lp;
	s2=(N_SIN*)lp2;
	s2->color=s1->color;
	s2->ltype=s1->ltype;
	s2->pirodic=s1->pirodic;
	s2->startdeg=s1->startdeg;
	memcpy(s2->pt,s1->pt,4*sizeof(DPOINT));
	return sizeof(N_SIN);
}

int FileV30::V2ArcToBs(void *lp, void *lp2)
{
	N2_ARC  *a1;
	N_ARC   *a2;
	a1=(N2_ARC*)lp;
	a2=(N_ARC*)lp2;
	a2->color=a1->color;
	a2->end=a1->end;
	a2->start=a1->start;
	memcpy(a2->pt,a1->pt,4*sizeof(DPOINT));
	return sizeof(N_ARC);
}

int FileV30::V2ArrowToBs(void *lp, void *lp2)
{
	N2_ARROW *a1;
	N_ARROW *a2;
	a1=(N2_ARROW*)lp;
	a2=(N_ARROW*)lp2;
	a2->color=a1->color;
	memcpy(a2->pt,a1->pt,2*sizeof(DPOINT));
	return sizeof(N_ARROW);
}

int FileV30::V2GlassToBs(void *lp, void *lp2)
{
	N2_GLASS *g1;
	N_GLASS *g2;
	g1=(N2_GLASS*)lp;
	g2=(N_GLASS*)lp2;
	g2->color=g1->color;
	g2->depth=g1->depth;
	g2->ocolor=g1->ocolor;
	g2->outline=g1->outline;
	memcpy(g2->pt,g1->pt,4*sizeof(DPOINT));
	return sizeof(N_GLASS);
}

int FileV30::V2TextToBs(void *lp, void *lp2)
{
	N2_TEXT *t1;
	N_TEXT *t2;
	t1=(N2_TEXT*)lp;
	t2=(N_TEXT*)lp2;
	t2->color=t1->color;
	t2->font=t1->font;
	t2->style=t1->style;
	if(t1->zm!=1&&t1->zm!=0){
		t2->font.lfHeight=(int)(t1->font.lfHeight/t1->zm);
		t2->font.lfWidth=(int)(t1->font.lfWidth/t1->zm);
	}
	t2->zm=1;
	t2->autofill=t1->autofill;
	strcpy(t2->text,t1->text);
	memcpy(t2->pt,t1->pt,4*sizeof(DPOINT));
	return sizeof(N_TEXT);
}

int FileV30::V2SiteToBs(void *lp, void *lp2)
{
	N2_ESITE *e1;
	N_ESITE *e2;
	e1=(N2_ESITE*)lp;
	e2=(N_ESITE*)lp2;
	e2->color=e1->color;
	e2->solder=e1->solder;
	memcpy(e2->pt,e1->pt,4*sizeof(DPOINT));
	return sizeof(N_ESITE);
}

int FileV30::V2MBoardToBs(void *lp, void *lp2)
{
	N2_EGPMB *m1;
	N_EGPMB *m2;
	m1=(N2_EGPMB*)lp;
	m2=(N_EGPMB*)lp2;
	m2->color=m1->color;
	m2->mode=m1->mode;
	memcpy(m2->pt,m1->pt,4*sizeof(DPOINT));
	return sizeof(N_EGPMB);
}

int FileV30::V2CoordToBs(void *lp, void *lp2)
{
	N2_COORDINATE *c1;
	N_COORDINATE *c2;
	c1=(N2_COORDINATE*)lp;
	c2=(N_COORDINATE*)lp2;
	c2->colorc=c1->colorc;
	c2->colort=c1->colort;
	c2->colorw=c1->colorw;
	c2->fontx=c1->fontx;
	c2->fonty=c1->fonty;
	c2->wxdraw=c1->wxdraw;
	c2->wydraw=c1->wydraw;
	c2->xdot=c1->xdot;
	c2->xmax=c1->xmax;
	c2->xmin=c1->xmin;
	c2->xvshow=c1->xvshow;
	c2->ydot=c1->ydot;
	c2->ymax=c1->ymax;
	c2->ymin=c1->ymin;
	c2->yvshow=c1->yvshow;
	if(c1->zm!=1&&c1->zm!=0){
		c2->fontx.lfHeight=(int)(c1->fontx.lfHeight/c1->zm);
		c2->fontx.lfWidth=(int)(c1->fontx.lfWidth/c1->zm);
		c2->fonty.lfHeight=(int)(c1->fonty.lfHeight/c1->zm);
		c2->fonty.lfWidth=(int)(c1->fonty.lfWidth/c1->zm);
	}
	c2->zm=1;
	memcpy(c2->pt,c1->pt,4*sizeof(DPOINT));
	return sizeof(N_COORDINATE);
}

int FileV30::V2TableToBs(void *lp, void *lp2)
{
	N2_TABLE  *t1;
	N_TABLE *t2;
	t1=(N2_TABLE*)lp;
	t2=(N_TABLE*)lp2;
	t2->color=t1->color;
	t2->dbline=t1->dbline;
	t2->line=t1->line;
	t2->width=t1->width;
	memcpy(t2->pt,t1->pt,4*sizeof(DPOINT));
	return sizeof(N_TABLE);
}

int FileV30::V2SpicToBs(void *lp, void *lp2)
{
	N2_IMG  *m1;
	N_IMG *m2;
	m1=(N2_IMG*)lp;
	m2=(N_IMG*)lp2;
	m2->depth=m1->depth;
	m2->imgID=m1->imgID;
	m2->shadow=m1->shadow;
	m2->zoom=m1->zoom;
	memcpy(m2->pt,m1->pt,4*sizeof(DPOINT));
	return sizeof(N_IMG);
}

int FileV30::V2PathToBs(void *lp, void *lp2)
{
	N2_PATH  *p1;
	N_PATH *p2;
	p1=(N2_PATH*)lp;
	p2=(N_PATH*)lp2;
	p2->ID=p1->ID;
	p2->ptsum=p1->ptsum;
	memcpy(p2->pt,p1->pt,p1->ptsum*sizeof(DPOINT));
	return sizeof(N_PATH)+p1->ptsum*sizeof(DPOINT);
}

int FileV30::V2PicToBs(void *lp, void *lp2)
{
	N2_SPIC *s1;
	N_SPIC *s2;
	s1=(N2_SPIC*)lp;
	s2=(N_SPIC*)lp2;
	s2->picID=s1->picID;
	s2->zoom=s1->zoom;
	memcpy(s2->pt,s1->pt,4*sizeof(DPOINT));
	return sizeof(N_SPIC);
}

int FileV30::V2AnlToBs(void *lp, void *lp2)
{
	N2_ANL *a1;
	N_ANL *a2;
	a1=(N2_ANL*)lp;
	a2=(N_ANL*)lp2;
	a2->acolor=a1->acolor;
	a2->direction=a1->direction;
	strcpy(a2->dev_name,a1->dev_name);
	a2->did=a1->did;
	a2->dtype=a1->dtype;
	a2->lf=a1->lf;
	a2->ncolor=a1->ncolor;
	a2->style=a1->style;
	a2->xs=a1->xs;
	a2->xsmode=a1->xsmode;
	if(a1->zm!=1&&a1->zm!=0){
		a2->lf.lfHeight=(int)(a1->lf.lfHeight/a1->zm);
		a2->lf.lfWidth=(int)(a1->lf.lfWidth/a1->zm);
	}
	a2->zm=1;
	memcpy(a2->pt,a1->pt,4*sizeof(DPOINT));
	return sizeof(N_ANL);
}

int FileV30::V2ElegToBs(void *lp, void *lp2)
{
	N2_ELEGRPA *e1;
	N_ELEGRPA *e2;
	e1=(N2_ELEGRPA*)lp;
	e2=(N_ELEGRPA*)lp2;
	strcpy(e2->dev_name,e1->dev_name);
	e2->did=e1->did;
	e2->egrpid=e1->egrpid;
	e2->genrev=e1->genrev;
	e2->runshow=e1->runshow;
	e2->showno=e1->showno;
	e2->sitesum=e1->sitesum;
	e2->subtype=e1->subtype;
	e2->type=e1->type;
	memcpy(e2->pt,e1->pt,4*sizeof(DPOINT));
	memcpy(e2->site,e1->site,3*sizeof(D_SITE));
	return sizeof(N_ELEGRPA);
}

int FileV30::V2BarToBs(void *lp, void *lp2)
{
	N2_BAR *b1;
	N_BAR *b2;
	b1=(N2_BAR*)lp;
	b2=(N_BAR*)lp2;
	b2->acolor=b1->acolor;
	b2->aval=b1->aval;
	//b2->dsrc=b1->dsrc;
	strcpy(b2->dsrc.name,b1->dsrc.name);			 //设备名字
	b2->dsrc.did=b1->dsrc.did;				 //设备ID
	b2->dsrc.dtype=b1->dsrc.dtype;			 //设备类型
	b2->dsrc.xsmode=b1->dsrc.xsmode;			 //值索引


	b2->max=b1->max;
	b2->min=b1->min;
	b2->ncolor=b1->ncolor;
	b2->outline=b1->outline;
	b2->style=b1->style;
	b2->xy=b1->xy;
	memcpy(b2->pt,b1->pt,4*sizeof(DPOINT));
	return sizeof(N_BAR);
}

int FileV30::V2PieToBs(void *lp, void *lp2)
{
	N2_PIE *p1;
	N_PIE *p2;
	p1=(N2_PIE*)lp;
	p2=(N_PIE*)lp2;
	memcpy(p2->color,p1->color,32);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	strcpy(p2->name,p1->name);
	memcpy(p2->pt,p1->pt,4*sizeof(DPOINT));
	return sizeof(N_PIE);
}

int FileV30::V2DateToBs(void *lp, void *lp2)
{
	N2_DATE *d1;
	N_DATE *d2;
	d1=(N2_DATE*)lp;
	d2=(N_DATE*)lp2;
	d2->bcolor=d1->bcolor;
	d2->fcolor=d1->fcolor;
	d2->fmt=d1->fmt;
	d2->font=d1->font;
	d2->outcolor=d1->outcolor;
	d2->shadow=d1->shadow;
	d2->tran=d1->tran;
	if(d1->zm!=1&&d1->zm!=0){
		d2->font.lfHeight=(int)(d1->font.lfHeight/d1->zm);
		d2->font.lfWidth=(int)(d1->font.lfWidth/d1->zm);
	}
	d2->zm=1;
	d2->outline=d1->outline;
	memcpy(d2->pt,d1->pt,4*sizeof(DPOINT));
	return sizeof(N_DATE);
}

int FileV30::V2GifToBs(void *lp, void *lp2)
{
	N2_GIFAML *g1;
	N_GIFAML *g2;
	g1=(N2_GIFAML*)lp;
	g2=(N_GIFAML*)lp2;
	//g2->dsrc=g1->dsrc;
	strcpy(g2->dsrc.name,g1->dsrc.name);			 //设备名字
	g2->dsrc.did=g1->dsrc.did;				 //设备ID
	g2->dsrc.dtype=g1->dsrc.dtype;			 //设备类型
	g2->dsrc.xsmode=g1->dsrc.xsmode;			 //值索引
	strcpy(g2->fname,g1->fname);
	g2->rec=g1->rec;
	g2->type=g1->type;
	memcpy(g2->pt,g1->pt,4*sizeof(DPOINT));
	return sizeof(N_GIFAML);
}

int FileV30::V2ScrtxtToBs(void *lp, void *lp2)
{
	N2_SRLTEXT *s1;
	N_SRLTEXT *s2;
	s1=(N2_SRLTEXT*)lp;
	s2=(N_SRLTEXT*)lp2;
	s2->align=s1->align;
	s2->depth=s1->depth;
	s2->direct=s1->direct;
	s2->fcolor=s1->fcolor;
	s2->gcolor=s1->gcolor;
	s2->glass=s1->glass;
	s2->lf=s1->lf;
	s2->outline=s1->outline;
	s2->tcolor=s1->tcolor;
	if(s1->zm!=1&&s1->zm!=0){
		s2->lf.lfHeight=(int)(s1->lf.lfHeight/s1->zm);
		s2->lf.lfWidth=(int)(s1->lf.lfWidth/s1->zm);
	}
	s2->zm=1;
	strcpy(s2->text,s1->text);
	memcpy(s2->pt,s1->pt,4*sizeof(DPOINT));
	return sizeof(N_SRLTEXT);
}

int FileV30::V2PushToBs(void *lp, void *lp2)
{
	N2_PUSH *p1;
	N_PUSH *p2;
	p1=(N2_PUSH*)lp;
	p2=(N_PUSH*)lp2;
	p2->autlin=p1->autlin;
	p2->cmdnum=p1->cmdnum;
	p2->cmdtype=p1->cmdtype;
	p2->color1=p1->color1;
	p2->color2=p1->color2;
	strcpy(p2->command,p1->command);
	p2->lf=p1->lf;
	p2->selfid=p1->selfid;
	p2->shadow=p1->shadow;
	p2->spicid=p1->spicid;
	p2->style=p1->style;
	strcpy(p2->title,p1->title);
	if(p1->zm!=1&&p1->zm!=0){
		p2->lf.lfHeight=(int)(p1->lf.lfHeight/p1->zm);
		p2->lf.lfWidth=(int)(p1->lf.lfWidth/p1->zm);
	}
	p2->zm=1;
	memcpy(p2->pt,p1->pt,4*sizeof(DPOINT));
	return sizeof(N_PUSH);
}

int FileV30::V2SelfToBs(void *lp, void *lp2)
{
	N2_SELFCTL *s1;
	N_SELFCTL *s2;
	s1=(N2_SELFCTL*)lp;
	s2=(N_SELFCTL*)lp2;
	s2->abottom=s1->abottom;
	s2->aleft=s1->aleft;
	s2->aright=s1->aright;
	s2->atop=s1->atop;
	strcpy(s2->dllname,s1->dllname);
	s2->id=s1->id;
	memcpy(s2->lkbuf,s1->lkbuf,255);
	s2->mode=s1->mode;
	s2->style=s1->style;
	memcpy(s2->pt,s1->pt,4*sizeof(DPOINT));
	return sizeof(N_SELFCTL);
}

int FileV30::V2FlowToBs(void *lp, void *lp2)
{
	N2_FLOW *f1;
	N_FLOW *f2;
	f1=(N2_FLOW*)lp;
	f2=(N_FLOW*)lp2;
	f2->color1=f1->color1;
	f2->color2=f1->color2;
	strcpy(f2->dev_name,f1->dev_name);
	f2->did=f1->did;
	f2->direct=f1->direct;
	f2->ptsum=f1->ptsum;
	memcpy(f2->site,f1->site,2*sizeof(D_SITEB));
	f2->style=f1->style;
	f2->type=f1->type;
	f2->vl=f1->vl;
	f2->linewidth=0;
	memcpy(f2->pt,f1->pt,f1->ptsum*sizeof(DPOINT));
	return sizeof(N_FLOW)+f1->ptsum*sizeof(DPOINT);
}

int FileV30::V2ConlToBs(void *lp, void *lp2)
{
	N2_CONLINE *c1;
	N_CONLINE *c2;
	c1=(N2_CONLINE*)lp;
	c2=(N_CONLINE*)lp2;
	c2->conobj=c1->conobj;
	memcpy(c2->lobj,c1->lobj,2*sizeof(LOGOBJ));
	c2->ptsum=c1->ptsum;
	c2->solder1=c1->solder1;
	c2->solder2=c1->solder2;
	c2->vl=c1->vl;
	memcpy(c2->pt,c1->pt,c2->ptsum*sizeof(DPOINT));
	return sizeof(N_CONLINE)+c2->ptsum*sizeof(DPOINT);
}

int FileV30::V2BusToBs(void *lp, void *lp2)
{
	N2_BUS *b1;
	N_BUS *b2;
	b1=(N2_BUS*)lp;
	b2=(N_BUS*)lp2;
	strcpy(b2->dev_name,b1->dev_name);
	b2->did=b1->did;
	b2->eid=b1->eid;
	b2->type=b1->type;
	b2->valarm=b1->valarm;
	b2->vl=b1->vl;
	memcpy(b2->pt,b1->pt,4*sizeof(DPOINT));
	return sizeof(N_BUS);
}

int FileV30::V2ActToBs(void *lp, void *lp2)
{
	N2_ACTOBJ  *a1;
	N_ACTOBJ *a2;
	a1=(N2_ACTOBJ*)lp;
	a2=(N_ACTOBJ*)lp2;
	//a2->dsrc=a1->dsrc;
	strcpy(a2->dsrc.name,a1->dsrc.name);			 //设备名字
	a2->dsrc.did=a1->dsrc.did;				 //设备ID
	a2->dsrc.dtype=a1->dsrc.dtype;			 //设备类型
	a2->dsrc.xsmode=a1->dsrc.xsmode;			 //值索引

	a2->gid=a1->gid;
	a2->pathid=a1->pathid;
	a2->runmode=a1->runmode;
	a2->skip=a1->skip;
	a2->speed=a1->speed;
	memcpy(a2->pt,a1->pt,4*sizeof(DPOINT));
	return sizeof(N_ACTOBJ);
}

int FileV30::V2FlashToBs(void *lp, void *lp2)
{
	N2_FLASH  *f1;
	N_FLASH *f2;
	f1=(N2_FLASH*)lp;
	f2=(N_FLASH*)lp2;
	f2->align_buttom=f1->align_buttom;
	f2->align_left=f1->align_left;
	f2->align_right=f1->align_right;
	f2->align_top=f1->align_top;
	strcpy(f2->fname,f1->fname);
	f2->playmode=f1->playmode;
	memcpy(f2->pt,f1->pt,4*sizeof(DPOINT));
	return sizeof(N_FLASH);
}

int FileV30::V2PctToBs(void *lp, void *lp2)
{
	N2_PCTPIE *p1;
	N_PCTPIE *p2;
	p1=(N2_PCTPIE*)lp;
	p2=(N_PCTPIE*)lp2;
	p2->color1=p1->color1;
	p2->color2=p1->color2;
	strcpy(p2->dev_name,p1->dev_name);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	p2->lf=p1->lf;
	p2->maxv=p1->maxv;
	p2->type=p1->type;
	if(p1->zm!=1&&p1->zm!=0)
	{
		p2->lf.lfHeight=(int)(p1->lf.lfHeight/p1->zm);
		p2->lf.lfWidth=(int)(p1->lf.lfWidth/p1->zm);
	}
	p2->zm=1;
	memcpy(p2->pt,p1->pt,4*sizeof(DPOINT));
	return sizeof(N_PCTPIE);
}


//将V4版本的内容转换到基本类中
int FileV30::GetBsFromV4(void *lp1, N_BASATTR &btr, void *lp2)
{
	char *lp;
	lp=(char*)lp1;
	N4_BASATTR *ar2;
	ar2=(N4_BASATTR*)lp1;
	btr.belong=ar2->belong;
	btr.ID=ar2->ID;
	btr.type=ar2->type;
	btr.size=0;
	lp+=sizeof(N4_BASATTR);
	//按每种类型转换
	switch(ar2->type)
	{
	case 1: //多边形
		btr.size=V4DbxToBs(lp,lp2);
		break;
	case 2: case 3://矩形，园
		btr.size=V4RectToBs(lp,lp2);
		break;
	case 4: //正弦半波形
		btr.size=V4HsinToBs(lp,lp2);
		break;
	case 5: //正弦波形
		btr.size=V4SinToBs(lp,lp2);
		break;
	case 6: //园弧
		btr.size=V4ArcToBs(lp,lp2);
		break;
	case 7: //方向箭头
		btr.size=V4ArrowToBs(lp,lp2);
		break;
	case 8: //玻璃层
		btr.size=V4GlassToBs(lp,lp2);
		break;
	case 10://文本
		btr.size=V4TextToBs(lp,lp2);
		break;
	case 11://电气端子
		btr.size=V4SiteToBs(lp,lp2);
		break;
	case 12://组合图元母板
		btr.size=V4MBoardToBs(lp,lp2);
		break;
	case 13: //坐标
		btr.size=V4CoordToBs(lp,lp2);
		break;
	case 14://表格线
		btr.size=V4TableToBs(lp,lp2);
		break;
	case 15://静态图形
		btr.size=V4SpicToBs(lp,lp2);
		break;
	case 16://路径
		btr.size=V4PathToBs(lp,lp2);
		break;
	case 17://静态小图标
		btr.size=V4PicToBs(lp,lp2);
		break;
	case 32://仪表1
		btr.size=V4Meter1ToBs(lp,lp2);
		break;
	case 33://仪表2
		btr.size=V4Meter2ToBs(lp,lp2);
		break;
	case 34://仪表3
		btr.size=V4Meter3ToBs(lp,lp2);
		break;
	case 35://仪表4
		btr.size=V4Meter4ToBs(lp,lp2);
		break;
	case 64://模拟量显示结构
		btr.size=V4AnlToBs(lp,lp2);
		break;
	case 65://水库
		btr.size=V4ReservoirToBs(lp, lp2);
		break;
	case 66://组合图元显示结构
		btr.size=V4ElegToBs(lp,lp2);
		break;
	case 67:
		btr.size=V4YBToBs(lp,lp2);
		break;
	case 68:
		btr.size=V4SysPieToBs(lp,lp2);
		break;
	case 69://棒图
		btr.size=V4BarToBs(lp,lp2);
		break;
	case 70://饼图结构数据
		btr.size=V4PieToBs(lp,lp2);
		break;
	case 71:case 72://日期格式,时间格式
		btr.size=V4DateToBs(lp,lp2);
		break;
	case 73://动画图形
		btr.size=V4GifToBs(lp,lp2);
		break;
	case 74://滚动文本
		btr.size=V4ScrtxtToBs(lp,lp2);
		break;
	case 75://按钮格式
		btr.size=V4PushToBs(lp,lp2);
		break;
	case 76://自助控件
		btr.size=V4SelfToBs(lp,lp2);
		break;
	case 77://潮流线
		btr.size=V4FlowToBs(lp,lp2);
		break;
	case 78://连接线
		btr.size=V4ConlToBs(lp,lp2);
		break;
	case 79://母线
		btr.size=V4BusToBs(lp,lp2);
		break;
	case 80://小型活动对象
		btr.size=V4ActToBs(lp,lp2);
		break;
	case 81://FLASH对象
		btr.size=V4FlashToBs(lp,lp2);
		break;
	case 83://区域
		btr.size=V4ZoneToBs(lp,lp2);
		break;
	case 84:
		btr.size=V4WtrToBs(lp,lp2);		
		btr.type=85;					//天气
		break;
	}
	return sizeof(N4_BASATTR)+ar2->size; //返回已使用字节数
}

 

int FileV30::V4DbxToBs(void *lp, void *lp2)
{
	int s;
	N4_DBX *d1;
	N_DBX  *d2;
	d1=(N4_DBX*)lp;
	d2=(N_DBX*)lp2;
	d2->bcolor1=d1->bcolor1;
	d2->fill=d1->fill;
	d2->fillmode=d1->fillmode;
	d2->lcolor=d1->lcolor;
	d2->ltype=d1->ltype;
	d2->ptsum=d1->ptsum;
	d2->bgmode=d1->bgmode;
	if(d1->fill==1) d2->close=1;
	else d2->close=0;
	memcpy(d2->pt,d1->pt,d1->ptsum*sizeof(DPOINT));
	s=sizeof(N_DBX)+d1->ptsum*sizeof(DPOINT);
	return s;
}

int FileV30::V4RectToBs(void *lp, void *lp2)
{
	N4_RECT  *r1;
	N_RECT   *r2;
	r1=(N4_RECT*)lp;
	r2=(N_RECT*)lp2;
	r2->bcolor1=r1->bcolor1;
	r2->fill=r1->fill;
	r2->fillmode=r1->fillmode;
	r2->lcolor=r1->lcolor;
	r2->type=r1->type;
	GetptFromDRECT(r1->rt,r2->pt);
	return sizeof(N_RECT);
}

int FileV30::V4HsinToBs(void *lp, void *lp2)
{
	N4_HSIN  *h1;
	N_HSIN   *h2;
	h1=(N4_HSIN*)lp;
	h2=(N_HSIN*)lp2;
	h2->color=h1->color;
	h2->ltype=h1->hv;
	h2->pirodic=h1->pirodic;
	GetptFromDRECT(h1->rt,h2->pt);
	return sizeof(N_HSIN);
}

int FileV30::V4SinToBs(void *lp, void *lp2)
{
	N4_SIN *s1;
	N_SIN *s2;
	s1=(N4_SIN*)lp;
	s2=(N_SIN*)lp2;
	s2->color=s1->color;
	s2->ltype=s1->hv;
	s2->pirodic=s1->pirodic;
	s2->startdeg=s1->startdeg;
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SIN);
}

int FileV30::V4ArcToBs(void *lp, void *lp2)
{
	N4_ARC  *a1;
	N_ARC   *a2;
	a1=(N4_ARC*)lp;
	a2=(N_ARC*)lp2;
	a2->color=a1->color;
	a2->end=a1->end;
	a2->start=a1->start;
	GetptFromDRECT(a1->rt,a2->pt);
	return sizeof(N_ARC);
}

int FileV30::V4ArrowToBs(void *lp, void *lp2)
{
	N4_ARROW *a1;
	N_ARROW *a2;
	a1=(N4_ARROW*)lp;
	a2=(N_ARROW*)lp2;
	a2->color=a1->color;
	memcpy(a2->pt,a1->pt,2*sizeof(DPOINT));
	return sizeof(N_ARROW);
}

int FileV30::V4GlassToBs(void *lp, void *lp2)
{
	N4_GLASS *g1;
	N_GLASS *g2;
	g1=(N4_GLASS*)lp;
	g2=(N_GLASS*)lp2;
	g2->color=g1->color;
	g2->depth=g1->depth;
	g2->ocolor=g1->lcolor;
	g2->outline=g1->outline;
	GetptFromDRECT(g1->rt,g2->pt);
	return sizeof(N_GLASS);
}

int FileV30::V4TextToBs(void *lp, void *lp2)
{
	N4_TEXT *t1;
	N_TEXT *t2;
	t1=(N4_TEXT*)lp;
	t2=(N_TEXT*)lp2;
	t2->color=t1->color;
	t2->font=t1->font;
	t2->style=t1->style;
	t2->autofill=t1->autofit;
	if(t1->zm!=1&&t1->zm!=0){
		t2->font.lfHeight=(int)(t1->font.lfHeight/t1->zm);
		t2->font.lfWidth=(int)(t1->font.lfWidth/t1->zm);
	}
	t2->zm=1;
	strcpy(t2->text,t1->text);
	GetptFromDRECT(t1->rt,t2->pt);
	return sizeof(N_TEXT);
}

int FileV30::V4SiteToBs(void *lp, void *lp2)
{
	N4_ESITE *e1;
	N_ESITE *e2;
	e1=(N4_ESITE*)lp;
	e2=(N_ESITE*)lp2;
	e2->color=e1->color;
	e2->solder=e1->solder;
	GetptFromDRECT(e1->rt,e2->pt);
	return sizeof(N_ESITE);
}

int FileV30::V4MBoardToBs(void *lp, void *lp2)
{
	N4_EGPMB *m1;
	N_EGPMB *m2;
	m1=(N4_EGPMB*)lp;
	m2=(N_EGPMB*)lp2;
	m2->color=m1->color;
	m2->mode=m1->mode;
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_EGPMB);
}

int FileV30::V4CoordToBs(void *lp, void *lp2)
{
	N4_COORDINATE *c1;
	N_COORDINATE *c2;
	c1=(N4_COORDINATE*)lp;
	c2=(N_COORDINATE*)lp2;
	c2->colorc=c1->colorc;
	c2->colort=c1->colort;
	c2->colorw=c1->colorw;
	c2->fontx=c1->fontx;
	c2->fonty=c1->fonty;
	c2->wxdraw=c1->wxdraw;
	c2->wydraw=c1->wydraw;
	c2->xdot=c1->xdot;
	c2->xmax=c1->xmax;
	c2->xmin=c1->xmin;
	c2->xvshow=c1->xvshow;
	c2->ydot=c1->ydot;
	c2->ymax=c1->ymax;
	c2->ymin=c1->ymin;
	c2->yvshow=c1->yvshow;
	if(c1->zm!=1&&c1->zm!=0){
		c2->fontx.lfHeight=(int)(c1->fontx.lfHeight/c1->zm);
		c2->fontx.lfWidth=(int)(c1->fontx.lfWidth/c1->zm);
		c2->fonty.lfHeight=(int)(c1->fonty.lfHeight/c1->zm);
		c2->fonty.lfWidth=(int)(c1->fonty.lfWidth/c1->zm);
	}
	c2->zm=1;
	GetptFromDRECT(c1->rt,c2->pt);
	return sizeof(N_COORDINATE);
}

int FileV30::V4TableToBs(void *lp, void *lp2)
{
	N4_TABLE  *t1;
	N_TABLE *t2;
	t1=(N4_TABLE*)lp;
	t2=(N_TABLE*)lp2;
	t2->color=t1->color;
	t2->dbline=t1->dbline;
	t2->line=t1->line;
	t2->width=t1->width;
	GetptFromDRECT(t1->rt,t2->pt);
	return sizeof(N_TABLE);
}

int FileV30::V4SpicToBs(void *lp, void *lp2)
{
	N4_IMG  *m1;
	N_IMG *m2;
	m1=(N4_IMG*)lp;
	m2=(N_IMG*)lp2;
	m2->depth=m1->depth;
	m2->imgID=m1->imgID;
	m2->shadow=m1->shadow;
	m2->zoom=m1->zoom;
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_IMG);
}

int FileV30::V4PathToBs(void *lp, void *lp2)
{
	N4_PATH  *p1;
	N_PATH *p2;
	p1=(N4_PATH*)lp;
	p2=(N_PATH*)lp2;
	p2->ID=p1->ID;
	p2->ptsum=p1->ptsum;
	memcpy(p2->pt,p1->pt,p1->ptsum*sizeof(DPOINT));
	return sizeof(N_PATH)+p1->ptsum*sizeof(DPOINT);
}

int FileV30::V4PicToBs(void *lp, void *lp2)
{
	N4_SPIC *s1;
	N_SPIC *s2;
	s1=(N4_SPIC*)lp;
	s2=(N_SPIC*)lp2;
	s2->picID=s1->picID;
	s2->zoom=s1->zoom;
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SPIC);
}

int FileV30::V4Meter1ToBs(void *lp, void *lp2)
{
	int i;
	N4_METER1 *m1;
	N_METER1  *m2;
	m1=(N4_METER1*)lp;
	m2=(N_METER1*)lp2;
	for(i=0;i<2;i++)  m2->pt[i]=m1->pt[i];
	m2->font=m1->font;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showarc=m1->showarc;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;
	m2->slen=m1->slen;
	m2->angle=m1->angle;		
	m2->pstyle=m1->pstyle;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;
	m2->axw=m1->axw;
	m2->pw=m1->pw;
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];
	m2->zm=1;
	return sizeof(N_METER1);
}


int FileV30::V4Meter2ToBs(void *lp, void *lp2)
{
	int i;
	N4_METER2 *m1;
	N_METER2  *m2;
	m1=(N4_METER2*)lp;
	m2=(N_METER2*)lp2;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showbl=m1->showbl;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;		
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_METER2);
}

int FileV30::V4Meter3ToBs(void *lp, void *lp2)
{
	int i;
	N4_METER3 *m1;
	N_METER3  *m2;
	m1=(N4_METER3*)lp;
	m2=(N_METER3*)lp2;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showbl=m1->showbl;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;		
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_METER3);
}

int FileV30::V4Meter4ToBs(void *lp, void *lp2)
{
	int i;
	N4_METER4 *m1;
	N_METER4  *m2;
	m1=(N4_METER4*)lp;
	m2=(N_METER4*)lp2;
	m2->num=m1->num;
	m2->numdot=m1->numdot;
	m2->bcr=m1->bcr;
	for(i=0;i<2;i++) m2->ncr[i]=m1->ncr[i];
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_METER3);
}

int FileV30::V4SelfToBs(void *lp, void *lp2)
{
	N4_SELFCTL *s1;
	N_SELFCTL *s2;
	s1=(N4_SELFCTL*)lp;
	s2=(N_SELFCTL*)lp2;
	s2->abottom=s1->abottom;
	s2->aleft=s1->aleft;
	s2->aright=s1->aright;
	s2->atop=s1->atop;
	strcpy(s2->dllname,s1->dllname);
	s2->id=s1->id;
	memcpy(s2->lkbuf,s1->lkbuf,255);
	s2->mode=s1->mode;
	s2->style=s1->style;
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SELFCTL);
}


int FileV30::V4PieToBs(void *lp, void *lp2)
{
	N4_PIE *p1;
	N_PIE *p2;
	p1=(N4_PIE*)lp;
	p2=(N_PIE*)lp2;
	p2->lf=p1->lf;
	memcpy(p2->color,p1->color,12);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	p2->type=p1->type;
	strcpy(p2->name,p1->name);
	GetptFromDRECT(p1->rt,p2->pt);
	return sizeof(N_PIE);
}

int FileV30::V4SysPieToBs(void *lp, void *lp2)
{
	N4_SYSPIE *p1;
	N_SYSPIE *p2;
	p1=(N4_SYSPIE*)lp;
	p2=(N_SYSPIE*)lp2;
	p2->lf=p1->lf;
	p2->ID=p1->ID;
	memcpy(p2->color,p1->color,24);
	p2->fcolor=p1->fcolor;
	p2->type=p1->type;
	GetptFromDRECT(p1->rt,p2->pt);
	return sizeof(N_SYSPIE);
}

int FileV30::V4DateToBs(void *lp, void *lp2)
{
	N4_DATE *d1;
	N_DATE *d2;
	d1=(N4_DATE*)lp;
	d2=(N_DATE*)lp2;
	d2->bcolor=d1->bcolor;
	d2->fcolor=d1->fcolor;
	d2->fmt=d1->fmt;
	d2->font=d1->font;
	d2->outcolor=d1->outcolor;
	d2->shadow=d1->shadow;
	d2->tran=d1->tran;
	if(d1->zm!=1&&d1->zm!=0){
		d2->font.lfHeight=(int)(d1->font.lfHeight/d1->zm);
		d2->font.lfWidth=(int)(d1->font.lfWidth/d1->zm);
	}
	d2->zm=1;
	d2->outline=d1->outline;
	GetptFromDRECT(d1->rt,d2->pt);
	return sizeof(N_DATE);
}

int FileV30::V4ScrtxtToBs(void *lp, void *lp2)
{
	N4_SRLTEXT *s1;
	N_SRLTEXT *s2;
	s1=(N4_SRLTEXT*)lp;
	s2=(N_SRLTEXT*)lp2;
	s2->align=s1->align;
	s2->depth=s1->depth;
	s2->direct=s1->direct;
	s2->fcolor=s1->fcolor;
	s2->gcolor=s1->gcolor;
	s2->glass=s1->glass;
	s2->lf=s1->lf;
	s2->outline=s1->outline;
	s2->tcolor=s1->tcolor;
	if(s1->zm!=1&&s1->zm!=0){
		s2->lf.lfHeight=(int)(s1->lf.lfHeight/s1->zm);
		s2->lf.lfWidth=(int)(s1->lf.lfWidth/s1->zm);
	}
	s2->zm=1;
	strcpy(s2->text,s1->text);
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SRLTEXT);
}

int FileV30::V4BarToBs(void *lp, void *lp2)
{
	N4_BAR *b1;
	N_BAR *b2;
	b1=(N4_BAR*)lp;
	b2=(N_BAR*)lp2;
	b2->acolor=b1->acolor;
	b2->aval=b1->aval;
	b2->dsrc.did=b1->dsrc.did;
	b2->dsrc.dtype=b1->dsrc.dtype;
	b2->dsrc.xsmode=b1->dsrc.xsmode;
	strcpy(b2->dsrc.name,b1->dsrc.name);
	b2->max=b1->max;
	b2->min=b1->min;
	b2->ncolor=b1->ncolor;
	b2->outline=b1->outline;
	b2->style=b1->style;
	b2->xy=b1->xy;
	GetptFromDRECT(b1->rt,b2->pt);
	return sizeof(N_BAR);
}


int FileV30::V4WtrToBs(void *lp, void *lp2)
{
	N4_WEATHER *p1;
	N_WEATHER *p2;
	p1=(N4_WEATHER*)lp;
	p2=(N_WEATHER*)lp2;
	strcpy(p2->name,p1->name);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	p2->lf=p1->lf;
	GetptFromDRECT(p1->rt,p2->pt);
	return sizeof(N_WEATHER);
}

int FileV30::V4ZoneToBs(void *lp, void *lp2)
{
	N4_ZONE *f1;
	N_ZONE *f2;
	f1=(N4_ZONE*)lp;
	f2=(N_ZONE*)lp2;
	f2->lcolor=f1->lcolor;
	strcpy(f2->zone_name,f1->zone_name);
	f2->lf=f1->lf;
	f2->fcolor=f1->fcolor;
	f2->did=f1->did;
	f2->ptsum=f1->ptsum;
	memcpy(f2->pt,f1->pt,f1->ptsum*sizeof(DPOINT));
	return sizeof(N_ZONE)+f1->ptsum*sizeof(DPOINT);
}

int FileV30::V4ActToBs(void *lp, void *lp2)
{
	N4_ACTOBJ  *a1;
	N_ACTOBJ *a2;
	a1=(N4_ACTOBJ*)lp;
	a2=(N_ACTOBJ*)lp2;
	a2->dsrc.did=a1->dsrc.did;
	a2->dsrc.dtype=a1->dsrc.dtype;
	a2->dsrc.xsmode=a1->dsrc.xsmode;
	strcpy(a2->dsrc.name,a1->dsrc.name);
	a2->gid=a1->gid;
	a2->pathid=a1->pathid;
	a2->runmode=a1->runmode;
	a2->skip=a1->skip;
	a2->speed=a1->speed;
	GetptFromDRECT(a1->rt,a2->pt);
	return sizeof(N_ACTOBJ);
}

int FileV30::V4BusToBs(void *lp, void *lp2)
{
	N4_BUS *b1;
	N_BUS *b2;
	b1=(N4_BUS*)lp;
	b2=(N_BUS*)lp2;
	strcpy(b2->dev_name,b1->dev_name);
	b2->did=b1->did;
	b2->eid=b1->eid;
	b2->type=b1->type;
	b2->valarm=b1->valarm;
	b2->vl=b1->vl;
	GetptFromDRECT(b1->rt,b2->pt);
	return sizeof(N_BUS);
}

int FileV30::V4FlowToBs(void *lp, void *lp2)
{
	N4_FLOW *f1;
	N_FLOW *f2;
	f1=(N4_FLOW*)lp;
	f2=(N_FLOW*)lp2;
	f2->color1=f1->color1;
	f2->color2=f1->color2;
	strcpy(f2->dev_name,f1->dev_name);
	f2->did=f1->did;
	f2->direct=f1->direct;
	f2->ptsum=f1->ptsum;
	memcpy(f2->site,f1->site,2*sizeof(D_SITEB));
	f2->style=f1->style;
	f2->type=f1->type;
	f2->vl=f1->vl;
	memcpy(f2->pt,f1->pt,f1->ptsum*sizeof(DPOINT));
	return sizeof(N_FLOW)+f1->ptsum*sizeof(DPOINT);
}

int FileV30::V4PushToBs(void *lp, void *lp2)
{
	N4_PUSH *p1;
	N_PUSH *p2;
	p1=(N4_PUSH*)lp;
	p2=(N_PUSH*)lp2;
	p2->autlin=p1->autlin;
	p2->cmdnum=p1->cmdnum;
	p2->cmdtype=p1->cmdtype;
	p2->color1=p1->color1;
	p2->color2=p1->color2;
	strcpy(p2->command,p1->command);
	p2->lf=p1->lf;
	p2->selfid=p1->selfid;
	p2->shadow=p1->shadow;
	p2->spicid=p1->spicid;
	p2->style=p1->style;
	p2->tosta=p1->tosta;
	strcpy(p2->title,p1->title);
	if(p1->zm!=1&&p1->zm!=0){
		p2->lf.lfHeight=(int)(p1->lf.lfHeight/p1->zm);
		p2->lf.lfWidth=(int)(p1->lf.lfWidth/p1->zm);
	}
	p2->zm=1;
	GetptFromDRECT(p1->rt,p2->pt);
	return sizeof(N_PUSH);
}

int FileV30::V4GifToBs(void *lp, void *lp2)
{
	N4_GIFAML *g1;
	N_GIFAML *g2;
	g1=(N4_GIFAML*)lp;
	g2=(N_GIFAML*)lp2;
	g2->dsrc.did=g1->dsrc.did;
	g2->dsrc.dtype=g1->dsrc.dtype;
	g2->dsrc.xsmode=g1->dsrc.xsmode;
	strcpy(g2->dsrc.name,g1->dsrc.name);
	strcpy(g2->fname,g1->fname);
	g2->rec=g1->rec;
	g2->type=g1->type;
	GetptFromDRECT(g1->rt,g2->pt);
	return sizeof(N_GIFAML);
}

int FileV30::V4YBToBs(void *lp, void *lp2)
{
	int i;
	N4_ELEGRPYB *e1;
	N_ELEGRPYB *e2;
	e1=(N4_ELEGRPYB*)lp;
	e2=(N_ELEGRPYB*)lp2;
	e2->egrpid=e1->egrpid;
	e2->dbsum=e1->dbsum;
	for(i=0;i<8;i++){
		e2->dbs[i].did=e1->dbs[i].did;
		e2->dbs[i].dtype=e1->dbs[i].dtype;
		e2->dbs[i].xsmode=e1->dbs[i].xsmode;
		strcpy(e2->dbs[i].name,e1->dbs[i].name);
		//e2->umr[i]=e1->umr[i];
	}
	GetptFromDRECT(e1->rt,e2->pt);
	return sizeof(N_ELEGRPYB);
}

int FileV30::V4AnlToBs(void *lp, void *lp2)
{
	N4_ANL *a1;
	N_ANL *a2;
	a1=(N4_ANL*)lp;
	a2=(N_ANL*)lp2;
	a2->acolor=a1->acolor;
	a2->direction=a1->angle==0 ? 0:1;
	strcpy(a2->dev_name,a1->dev_name);
	a2->did=a1->did;
	a2->dtype=a1->dtype;
	a2->lf=a1->lf;
	a2->ncolor=a1->ncolor;
	a2->style=a1->style;
	a2->xs=a1->xs;
	a2->xsmode=a1->xsmode;
	if(a1->zm!=1&&a1->zm!=0){
		a2->lf.lfHeight=(int)(a1->lf.lfHeight/a1->zm);
		a2->lf.lfWidth=(int)(a1->lf.lfWidth/a1->zm);
	}
	a2->zm=1;
	GetptFromDRECT(a1->rt,a2->pt);
	return sizeof(N_ANL);
}

int FileV30::V4ReservoirToBs(void *lp, void *lp2)
{
	int i,size;
	N4_RESERVOIR *a1;
	N_RESERVOIR  *a2;
	a1=(N4_RESERVOIR*)lp;
	a2=(N_RESERVOIR *)lp2;
	a2->color=a1->color;
	strcpy(a2->dev_name,a1->dev_name);
	a2->did=a1->did;
	a2->hcolor=a1->hcolor;
	a2->lcolor=a1->lcolor;
	a2->ncolor=a1->ncolor;
	a2->ptsum=a1->ptsum;
	size=sizeof(N_RESERVOIR)+a2->ptsum*sizeof(DPOINT);
	for(i=0;i<a2->ptsum;i++)	a2->pt[i]=a1->pt[i];
	return size;
}

int FileV30::V4ElegToBs(void *lp, void *lp2)
{
	N4_ELEGRPA *e1;
	N_ELEGRPA *e2;
	e1=(N4_ELEGRPA*)lp;
	e2=(N_ELEGRPA*)lp2;
	strcpy(e2->dev_name,e1->dev_name);
	e2->did=e1->did;
	e2->egrpid=e1->egrpid;
	e2->genrev=e1->genrev;
	e2->runshow=e1->runshow;
	e2->showno=e1->showno;
	e2->sitesum=e1->sitesum;
	e2->type=e1->type;
	e2->subtype=e1->subtype;
	GetptFromDRECT(e1->rt,e2->pt);
	memcpy(e2->site,e1->site,3*sizeof(D_SITE));
	return sizeof(N_ELEGRPA);
}

int FileV30::V4ConlToBs(void *lp, void *lp2)
{
	N4_CONLINE *c1;
	N_CONLINE *c2;
	c1=(N4_CONLINE*)lp;
	c2=(N_CONLINE*)lp2;
	c2->conobj=c1->conobj;
	memcpy(c2->lobj,c1->lobj,2*sizeof(LOGOBJ));
	c2->ptsum=c1->ptsum;
	c2->solder1=c1->solder1;
	c2->solder2=c1->solder2;
	c2->vl=c1->vl;
	memcpy(c2->pt,c1->pt,c2->ptsum*sizeof(DPOINT));
	return sizeof(N_CONLINE)+c2->ptsum*sizeof(DPOINT);
}
int FileV30::V4FlashToBs(void *lp, void *lp2)
{
	N4_FLASH  *f1;
	N_FLASH *f2;
	f1=(N4_FLASH*)lp;
	f2=(N_FLASH*)lp2;
	f2->align_buttom=f1->align_buttom;
	f2->align_left=f1->align_left;
	f2->align_right=f1->align_right;
	f2->align_top=f1->align_top;
	strcpy(f2->fname,f1->fname);
	f2->playmode=f1->playmode;
	GetptFromDRECT(f1->rt,f2->pt);
	return sizeof(N_FLASH);
}

//将V3版本的内容转换到基本类中
int FileV30::GetBsFromV3(void *lp1, N_BASATTR &btr, void *lp2)
{
	char *lp;
	lp=(char*)lp1;
	N3_BASATTR *ar2;
	ar2=(N3_BASATTR*)lp1;
	btr.belong=ar2->belong;
	btr.ID=ar2->ID;
	btr.type=ar2->type;
	btr.size=0;
	lp+=sizeof(N3_BASATTR);
	//按每种类型转换
	switch(ar2->type)
	{
	case 1: //多边形
		btr.size=V3DbxToBs(lp,lp2);
		break;
	case 2: case 3://矩形，园
		btr.size=V3RectToBs(lp,lp2);
		break;
	case 4: //正弦半波形
		btr.size=V3HsinToBs(lp,lp2);
		break;
	case 5: //正弦波形
		btr.size=V3SinToBs(lp,lp2);
		break;
	case 6: //园弧
		btr.size=V3ArcToBs(lp,lp2);
		break;
	case 7: //方向箭头
		btr.size=V3ArrowToBs(lp,lp2);
		break;
	case 8: //玻璃层
		btr.size=V3GlassToBs(lp,lp2);
		break;
	case 10://文本
		btr.size=V3TextToBs(lp,lp2);
		break;
	case 11://电气端子
		btr.size=V3SiteToBs(lp,lp2);
		break;
	case 12://组合图元母板
		btr.size=V3MBoardToBs(lp,lp2);
		break;
	case 13: //坐标
		btr.size=V3CoordToBs(lp,lp2);
		break;
	case 14://表格线
		btr.size=V3TableToBs(lp,lp2);
		break;
	case 15://静态图形
		btr.size=V3SpicToBs(lp,lp2);
		break;
	case 16://路径
		btr.size=V3PathToBs(lp,lp2);
		break;
	case 17://静态小图标
		btr.size=V3PicToBs(lp,lp2);
		break;
	case 32://仪表1
		btr.size=V3Meter1ToBs(lp,lp2);
		break;
	case 33://仪表2
		btr.size=V3Meter2ToBs(lp,lp2);
		break;
	case 34://仪表3
		btr.size=V3Meter3ToBs(lp,lp2);
		break;
	case 35://仪表4
		btr.size=V3Meter4ToBs(lp,lp2);
		break;
	case 64://模拟量显示结构
		btr.size=V3AnlToBs(lp,lp2);
		break;
	case 65://水库
		btr.size=V3ReservoirToBs(lp, lp2);
		break;
	case 66://组合图元显示结构
		btr.size=V3ElegToBs(lp,lp2);
		break;
	case 67:
		btr.size=V3YBToBs(lp,lp2);
		break;
	case 69://棒图
		btr.size=V3BarToBs(lp,lp2);
		break;
	case 70://饼图结构数据
		btr.size=V3PieToBs(lp,lp2);
		break;
	case 71:case 72://日期格式,时间格式
		btr.size=V3DateToBs(lp,lp2);
		break;
	case 73://动画图形
		btr.size=V3GifToBs(lp,lp2);
		break;
	case 74://滚动文本
		btr.size=V3ScrtxtToBs(lp,lp2);
		break;
	case 75://按钮格式
		btr.size=V3PushToBs(lp,lp2);
		break;
	case 76://自助控件
		btr.size=V3SelfToBs(lp,lp2);
		break;
	case 77://潮流线
		btr.size=V3FlowToBs(lp,lp2);
		break;
	case 78://连接线
		btr.size=V3ConlToBs(lp,lp2);
		break;
	case 79://母线
		btr.size=V3BusToBs(lp,lp2);
		break;
	case 80://小型活动对象
		btr.size=V3ActToBs(lp,lp2);
		break;
	case 81://FLASH对象
		btr.size=V3FlashToBs(lp,lp2);
		break;
	case 82://百分比饼图
		btr.size=V3PctToBs(lp,lp2);
		break;
	case 83://区域
		btr.size=V3ZoneToBs(lp,lp2);
		break;
	case 84://多行
		btr.size=V3MttextToBs(lp,lp2);
		break;
	}
	return sizeof(N3_BASATTR)+ar2->size; //返回已使用字节数
}

int FileV30::V3DbxToBs(void *lp, void *lp2)
{
	int s;
	N3_DBX *d1;
	N_DBX  *d2;
	d1=(N3_DBX*)lp;
	d2=(N_DBX*)lp2;
	d2->close=d1->close;
	d2->bcolor1=d1->bcolor1;
	d2->fill=d1->fill;
	d2->fillmode=d1->fillmode;
	d2->lcolor=d1->lcolor;
	d2->ltype=d1->ltype;
	d2->ptsum=d1->ptsum;
	d2->bgmode=d1->bgmode;
	memcpy(d2->pt,d1->pt,d1->ptsum*sizeof(DPOINT));
	s=sizeof(N_DBX)+d1->ptsum*sizeof(DPOINT);
	return s;
}

int FileV30::V3RectToBs(void *lp, void *lp2)
{
	N3_RECT  *r1;
	N_RECT   *r2;
	r1=(N3_RECT*)lp;
	r2=(N_RECT*)lp2;
	r2->bcolor1=r1->bcolor1;
	r2->fill=r1->fill;
	r2->fillmode=r1->fillmode;
	r2->lcolor=r1->lcolor;
	r2->type=r1->type;
	GetptFromDRECT(r1->rt,r2->pt);
	return sizeof(N_RECT);
}

int FileV30::V3HsinToBs(void *lp, void *lp2)
{
	N3_HSIN  *h1;
	N_HSIN   *h2;
	h1=(N3_HSIN*)lp;
	h2=(N_HSIN*)lp2;
	h2->color=h1->color;
	h2->ltype=h1->hv;
	h2->pirodic=h1->pirodic;
	GetptFromDRECT(h1->rt,h2->pt);
	return sizeof(N_HSIN);
}

int FileV30::V3SinToBs(void *lp, void *lp2)
{
	N3_SIN *s1;
	N_SIN *s2;
	s1=(N3_SIN*)lp;
	s2=(N_SIN*)lp2;
	s2->color=s1->color;
	s2->ltype=s1->hv;
	s2->pirodic=s1->pirodic;
	s2->startdeg=s1->startdeg;
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SIN);
}

int FileV30::V3ArcToBs(void *lp, void *lp2)
{
	N3_ARC  *a1;
	N_ARC   *a2;
	a1=(N3_ARC*)lp;
	a2=(N_ARC*)lp2;
	a2->color=a1->color;
	a2->end=a1->end;
	a2->start=a1->start;
	GetptFromDRECT(a1->rt,a2->pt);
	return sizeof(N_ARC);
}

int FileV30::V3ArrowToBs(void *lp, void *lp2)
{
	N3_ARROW *a1;
	N_ARROW *a2;
	a1=(N3_ARROW*)lp;
	a2=(N_ARROW*)lp2;
	a2->color=a1->color;
	memcpy(a2->pt,a1->pt,2*sizeof(DPOINT));
	return sizeof(N_ARROW);
}

int FileV30::V3GlassToBs(void *lp, void *lp2)
{
	N3_GLASS *g1;
	N_GLASS *g2;
	g1=(N3_GLASS*)lp;
	g2=(N_GLASS*)lp2;
	g2->color=g1->color;
	g2->depth=g1->depth;
	g2->ocolor=g1->lcolor;
	g2->outline=g1->outline;
	GetptFromDRECT(g1->rt,g2->pt);
	return sizeof(N_GLASS);
}

int FileV30::V3TextToBs(void *lp, void *lp2)
{
	N3_TEXT *t1;
	N_TEXT *t2;
	t1=(N3_TEXT*)lp;
	t2=(N_TEXT*)lp2;
	t2->color=t1->color;
	t2->font=t1->font;
	t2->style=t1->style;
	t2->autofill=t1->autofit;
	if(t1->zm!=1&&t1->zm!=0)
	{
		t2->font.lfHeight=(int)(t1->font.lfHeight/t1->zm);
		t2->font.lfWidth=(int)(t1->font.lfWidth/t1->zm);
	}
	t2->zm=1;
	strcpy(t2->text,t1->text);
	GetptFromDRECT(t1->rt,t2->pt);
	return sizeof(N_TEXT);
}

int FileV30::V3SiteToBs(void *lp, void *lp2)
{
	N3_ESITE *e1;
	N_ESITE *e2;
	e1=(N3_ESITE*)lp;
	e2=(N_ESITE*)lp2;
	e2->color=e1->color;
	e2->solder=e1->solder;
	GetptFromDRECT(e1->rt,e2->pt);
	return sizeof(N_ESITE);
}

int FileV30::V3MBoardToBs(void *lp, void *lp2)
{
	N3_EGPMB *m1;
	N_EGPMB *m2;
	m1=(N3_EGPMB*)lp;
	m2=(N_EGPMB*)lp2;
	m2->color=m1->color;
	m2->mode=m1->mode;
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_EGPMB);
}

int FileV30::V3CoordToBs(void *lp, void *lp2)
{
	N3_COORDINATE *c1;
	N_COORDINATE *c2;
	c1=(N3_COORDINATE*)lp;
	c2=(N_COORDINATE*)lp2;
	c2->colorc=c1->colorc;
	c2->colort=c1->colort;
	c2->colorw=c1->colorw;
	c2->fontx=c1->fontx;
	c2->fonty=c1->fonty;
	c2->wxdraw=c1->wxdraw;
	c2->wydraw=c1->wydraw;
	c2->xdot=c1->xdot;
	c2->xmax=c1->xmax;
	c2->xmin=c1->xmin;
	c2->xvshow=c1->xvshow;
	c2->ydot=c1->ydot;
	c2->ymax=c1->ymax;
	c2->ymin=c1->ymin;
	c2->yvshow=c1->yvshow;
	if(c1->zm!=1&&c1->zm!=0){
		c2->fontx.lfHeight=(int)(c1->fontx.lfHeight/c1->zm);
		c2->fontx.lfWidth=(int)(c1->fontx.lfWidth/c1->zm);
		c2->fonty.lfHeight=(int)(c1->fonty.lfHeight/c1->zm);
		c2->fonty.lfWidth=(int)(c1->fonty.lfWidth/c1->zm);
	}
	c2->zm=1;
	GetptFromDRECT(c1->rt,c2->pt);
	return sizeof(N_COORDINATE);
}

int FileV30::V3TableToBs(void *lp, void *lp2)
{
	N3_TABLE  *t1;
	N_TABLE *t2;
	t1=(N3_TABLE*)lp;
	t2=(N_TABLE*)lp2;
	t2->color=t1->color;
	t2->dbline=t1->dbline;
	t2->line=t1->line;
	t2->width=t1->width;
	GetptFromDRECT(t1->rt,t2->pt);
	return sizeof(N_TABLE);
}

int FileV30::V3SpicToBs(void *lp, void *lp2)
{
	N3_IMG  *m1;
	N_IMG *m2;
	m1=(N3_IMG*)lp;
	m2=(N_IMG*)lp2;
	m2->depth=m1->depth;
	m2->imgID=m1->imgID;
	m2->shadow=m1->shadow;
	m2->zoom=m1->zoom;
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_IMG);
}

int FileV30::V3PathToBs(void *lp, void *lp2)
{
	N3_PATH  *p1;
	N_PATH *p2;
	p1=(N3_PATH*)lp;
	p2=(N_PATH*)lp2;
	p2->ID=p1->ID;
	p2->ptsum=p1->ptsum;
	memcpy(p2->pt,p1->pt,p1->ptsum*sizeof(DPOINT));
	return sizeof(N_PATH)+p1->ptsum*sizeof(DPOINT);
}

int FileV30::V3PicToBs(void *lp, void *lp2)
{
	N3_SPIC *s1;
	N_SPIC *s2;
	s1=(N3_SPIC*)lp;
	s2=(N_SPIC*)lp2;
	s2->picID=s1->picID;
	s2->zoom=s1->zoom;
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SPIC);
}

int FileV30::V3Meter1ToBs(void *lp, void *lp2)
{
	int i;
	N3_METER1 *m1;
	N_METER1  *m2;
	m1=(N3_METER1*)lp;
	m2=(N_METER1*)lp2;
	for(i=0;i<2;i++)  m2->pt[i]=m1->pt[i];
	m2->font=m1->font;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showarc=m1->showarc;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;
	m2->slen=m1->slen;
	m2->angle=m1->angle;		
	m2->pstyle=m1->pstyle;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;
	m2->axw=m1->axw;
	m2->pw=m1->pw;
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];
	m2->zm=1;
	m2->stype=m1->stype;
	m2->lstype=m1->lstype;
	return sizeof(N_METER1);
}


int FileV30::V3Meter2ToBs(void *lp, void *lp2)
{
	int i;
	N3_METER2 *m1;
	N_METER2  *m2;
	m1=(N3_METER2*)lp;
	m2=(N_METER2*)lp2;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showbl=m1->showbl;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;		
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_METER2);
}

int FileV30::V3Meter3ToBs(void *lp, void *lp2)
{
	int i;
	N3_METER3 *m1;
	N_METER3  *m2;
	m1=(N3_METER3*)lp;
	m2=(N_METER3*)lp2;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showbl=m1->showbl;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;		
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_METER3);
}

int FileV30::V3Meter4ToBs(void *lp, void *lp2)
{
	int i;
	N3_METER4 *m1;
	N_METER4  *m2;
	m1=(N3_METER4*)lp;
	m2=(N_METER4*)lp2;
	m2->num=m1->num;
	m2->numdot=m1->numdot;
	m2->bcr=m1->bcr;
	for(i=0;i<2;i++) m2->ncr[i]=m1->ncr[i];
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_METER3);
}

int FileV30::V3AnlToBs(void *lp, void *lp2)
{
	N3_ANL *a1;
	N_ANL *a2;
	a1=(N3_ANL*)lp;
	a2=(N_ANL*)lp2;
	a2->acolor=a1->acolor;
	a2->direction=a1->angle==0 ? 0:1;
	strcpy(a2->dev_name,a1->dev_name);
	a2->did=a1->did;
	a2->dtype=a1->dtype;
	a2->lf=a1->lf;
	a2->ncolor=a1->ncolor;
	a2->style=a1->style;
	a2->xs=a1->xs;
	a2->xsmode=a1->xsmode;
	if(a1->zm!=1&&a1->zm!=0){
		a2->lf.lfHeight=(int)(a1->lf.lfHeight/a1->zm);
		a2->lf.lfWidth=(int)(a1->lf.lfWidth/a1->zm);
	}
	a2->zm=1;
	GetptFromDRECT(a1->rt,a2->pt);
	return sizeof(N_ANL);
}

int FileV30::V3ReservoirToBs(void *lp, void *lp2)
{
	int i,size;
	N3_RESERVOIR *a1;
	N_RESERVOIR  *a2;
	a1=(N3_RESERVOIR*)lp;
	a2=(N_RESERVOIR *)lp2;
	a2->color=a1->color;
	strcpy(a2->dev_name,a1->dev_name);
	a2->did=a1->did;
	a2->hcolor=a1->hcolor;
	a2->lcolor=a1->lcolor;
	a2->ncolor=a1->ncolor;
	a2->ptsum=a1->ptsum;
	size=sizeof(N_RESERVOIR)+a2->ptsum*sizeof(DPOINT);
	for(i=0;i<a2->ptsum;i++)	a2->pt[i]=a1->pt[i];
	return size;
}

int FileV30::V3ElegToBs(void *lp, void *lp2)
{
	N3_ELEGRPA *e1;
	N_ELEGRPA *e2;
	e1=(N3_ELEGRPA*)lp;
	e2=(N_ELEGRPA*)lp2;
	strcpy(e2->dev_name,e1->dev_name);
	e2->did=e1->did;
	e2->egrpid=e1->egrpid;
	e2->genrev=e1->genrev;
	e2->runshow=e1->runshow;
	e2->showno=e1->showno;
	e2->sitesum=e1->sitesum;
	e2->type=e1->type;
	e2->subtype=e1->subtype;
	GetptFromDRECT(e1->rt,e2->pt);
	memcpy(e2->site,e1->site,3*sizeof(D_SITE));
	return sizeof(N_ELEGRPA);
}


int FileV30::V3YBToBs(void *lp, void *lp2)
{
	int i,j;
	N3_ELEGRPYB *e1;
	N_ELEGRPYB *e2;
	e1=(N3_ELEGRPYB*)lp;
	e2=(N_ELEGRPYB*)lp2;
	e2->egrpid=e1->egrpid;
	e2->dbsum=e1->dbsum;
	for(i=0;i<8;i++){
		//e2->dbs[i]=e1->dbs[i];
		//e2->pam[i]=e1->pam[i];
		strcpy(e2->dbs[i].name,e1->dbs[i].name);
		e2->dbs[i].did=e1->dbs[i].did;
		e2->dbs[i].dtype=e1->dbs[i].dtype;
		e2->dbs[i].xsmode=e1->dbs[i].xsmode;

		e2->pam[i].ptype=e1->pam[i].ptype;
		e2->pam[i].vmin=e1->pam[i].vmin;
		e2->pam[i].vmax=e1->pam[i].vmax;
		e2->pam[i].alarm=e1->pam[i].alarm;
		for(j=0;j<4;j++) e2->pam[i].val[j]=e1->pam[i].val[j];
		for(j=0;j<2;j++) e2->pam[i].color[j]=e1->pam[i].color[j];
	}
	GetptFromDRECT(e1->rt,e2->pt);
	return sizeof(N_ELEGRPYB);
}

int FileV30::V3BarToBs(void *lp, void *lp2)
{
	N3_BAR *b1;
	N_BAR *b2;
	b1=(N3_BAR*)lp;
	b2=(N_BAR*)lp2;
	b2->acolor=b1->acolor;
	b2->aval=b1->aval;
	//b2->dsrc=b1->dsrc;
	strcpy(b2->dsrc.name,b1->dsrc.name);
	b2->dsrc.did=b1->dsrc.did;
	b2->dsrc.dtype=b1->dsrc.dtype;
	b2->dsrc.xsmode=b1->dsrc.xsmode;

	b2->max=b1->max;
	b2->min=b1->min;
	b2->ncolor=b1->ncolor;
	b2->outline=b1->outline;
	b2->style=b1->style;
	b2->xy=b1->xy;
	GetptFromDRECT(b1->rt,b2->pt);
	return sizeof(N_BAR);
}

int FileV30::V3PieToBs(void *lp, void *lp2)
{
	N3_PIE *p1;
	N_PIE *p2;
	p1=(N3_PIE*)lp;
	p2=(N_PIE*)lp2;
	memcpy(p2->color,p1->color,32);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	strcpy(p2->name,p1->name);
	GetptFromDRECT(p1->rt,p2->pt);
	return sizeof(N_PIE);
}

int FileV30::V3DateToBs(void *lp, void *lp2)
{
	N3_DATE *d1;
	N_DATE *d2;
	d1=(N3_DATE*)lp;
	d2=(N_DATE*)lp2;
	d2->bcolor=d1->bcolor;
	d2->fcolor=d1->fcolor;
	d2->fmt=d1->fmt;
	d2->font=d1->font;
	d2->outcolor=d1->outcolor;
	d2->shadow=d1->shadow;
	d2->tran=d1->tran;
	if(d1->zm!=1&&d1->zm!=0){
		d2->font.lfHeight=(int)(d1->font.lfHeight/d1->zm);
		d2->font.lfWidth=(int)(d1->font.lfWidth/d1->zm);
	}
	d2->zm=1;
	d2->outline=d1->outline;
	GetptFromDRECT(d1->rt,d2->pt);
	return sizeof(N_DATE);
}

int FileV30::V3GifToBs(void *lp, void *lp2)
{
	N3_GIFAML *g1;
	N_GIFAML *g2;
	g1=(N3_GIFAML*)lp;
	g2=(N_GIFAML*)lp2;
	//g2->dsrc=g1->dsrc;

	strcpy(g2->dsrc.name,g1->dsrc.name);
	g2->dsrc.did=g1->dsrc.did;
	g2->dsrc.dtype=g1->dsrc.dtype;
	g2->dsrc.xsmode=g1->dsrc.xsmode;

	strcpy(g2->fname,g1->fname);
	g2->rec=g1->rec;
	g2->type=g1->type;
	GetptFromDRECT(g1->rt,g2->pt);
	return sizeof(N_GIFAML);
}

int FileV30::V3ScrtxtToBs(void *lp, void *lp2)
{
	N3_SRLTEXT *s1;
	N_SRLTEXT *s2;
	s1=(N3_SRLTEXT*)lp;
	s2=(N_SRLTEXT*)lp2;
	s2->align=s1->align;
	s2->depth=s1->depth;
	s2->direct=s1->direct;
	s2->fcolor=s1->fcolor;
	s2->gcolor=s1->gcolor;
	s2->glass=s1->glass;
	s2->lf=s1->lf;
	s2->outline=s1->outline;
	s2->tcolor=s1->tcolor;
	if(s1->zm!=1&&s1->zm!=0){
		s2->lf.lfHeight=(int)(s1->lf.lfHeight/s1->zm);
		s2->lf.lfWidth=(int)(s1->lf.lfWidth/s1->zm);
	}
	s2->zm=1;
	strcpy(s2->text,s1->text);
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SRLTEXT);
}

int FileV30::V3PushToBs(void *lp, void *lp2)
{
	N3_PUSH *p1;
	N_PUSH *p2;
	p1=(N3_PUSH*)lp;
	p2=(N_PUSH*)lp2;
	p2->autlin=p1->autlin;
	p2->cmdnum=p1->cmdnum;
	p2->cmdtype=p1->cmdtype;
	p2->color1=p1->color1;
	p2->color2=p1->color2;
	strcpy(p2->command,p1->command);
	p2->lf=p1->lf;
	p2->selfid=p1->selfid;
	p2->shadow=p1->shadow;
	p2->spicid=p1->spicid;
	p2->style=p1->style;
	strcpy(p2->title,p1->title);
	if(p1->zm!=1&&p1->zm!=0){
		p2->lf.lfHeight=(int)(p1->lf.lfHeight/p1->zm);
		p2->lf.lfWidth=(int)(p1->lf.lfWidth/p1->zm);
	}
	p2->zm=1;
	p2->tosta=p1->tosta;
	GetptFromDRECT(p1->rt,p2->pt);
	return sizeof(N_PUSH);
}

int FileV30::V3SelfToBs(void *lp, void *lp2)
{
	N3_SELFCTL *s1;
	N_SELFCTL *s2;
	s1=(N3_SELFCTL*)lp;
	s2=(N_SELFCTL*)lp2;
	s2->abottom=s1->abottom;
	s2->aleft=s1->aleft;
	s2->aright=s1->aright;
	s2->atop=s1->atop;
	strcpy(s2->dllname,s1->dllname);
	s2->id=s1->id;
	memcpy(s2->lkbuf,s1->lkbuf,255);
	s2->mode=s1->mode;
	s2->style=s1->style;
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SELFCTL);
}

int FileV30::V3FlowToBs(void *lp, void *lp2)
{
	N3_FLOW *f1;
	N_FLOW *f2;
	f1=(N3_FLOW*)lp;
	f2=(N_FLOW*)lp2;
	f2->color1=f1->color1;
	f2->color2=f1->color2;
	strcpy(f2->dev_name,f1->dev_name);
	f2->did=f1->did;
	f2->direct=f1->direct;
	f2->ptsum=f1->ptsum;
	memcpy(f2->site,f1->site,2*sizeof(D_SITEB));
	f2->style=f1->style;
	f2->type=f1->type;
	f2->vl=f1->vl;
	f2->linewidth=f1->linewidth>4 ? 0:f1->linewidth;
	memcpy(f2->pt,f1->pt,f1->ptsum*sizeof(DPOINT));
	return sizeof(N_FLOW)+f1->ptsum*sizeof(DPOINT);
}

int FileV30::V3ZoneToBs(void *lp, void *lp2)
{
	N3_ZONE *f1;
	N_ZONE *f2;
	f1=(N3_ZONE*)lp;
	f2=(N_ZONE*)lp2;
	f2->lcolor=f1->lcolor;
	strcpy(f2->zone_name,f1->zone_name);
	f2->lf=f1->lf;
	f2->fcolor=f1->fcolor;
	f2->did=f1->did;
	f2->ptsum=f1->ptsum;
	memcpy(f2->pt,f1->pt,f1->ptsum*sizeof(DPOINT));
	return sizeof(N_ZONE)+f1->ptsum*sizeof(DPOINT);
}

int FileV30::V3MttextToBs(void *lp, void *lp2)
{
	N3_MTTEXT *f1;
	N_MTTEXT *f2;
	f1=(N3_MTTEXT*)lp;
	f2=(N_MTTEXT*)lp2;
	f2->fcolor=f1->fcolor;
	strcpy(f2->name,f1->name);
	f2->lf=f1->lf;
	f2->did=f1->did;
	f2->type=f1->type;
	strcpy(f2->text,f1->text);
	GetptFromDRECT(f1->rt,f2->pt);
	return sizeof(N_MTTEXT);
}

int FileV30::V3ConlToBs(void *lp, void *lp2)
{
	N3_CONLINE *c1;
	N_CONLINE *c2;
	c1=(N3_CONLINE*)lp;
	c2=(N_CONLINE*)lp2;
	c2->conobj=c1->conobj;
	memcpy(c2->lobj,c1->lobj,2*sizeof(LOGOBJ));
	c2->ptsum=c1->ptsum;
	c2->solder1=c1->solder1;
	c2->solder2=c1->solder2;
	c2->vl=c1->vl;
	memcpy(c2->pt,c1->pt,c2->ptsum*sizeof(DPOINT));
	return sizeof(N_CONLINE)+c2->ptsum*sizeof(DPOINT);
}

int FileV30::V3BusToBs(void *lp, void *lp2)
{
	N3_BUS *b1;
	N_BUS *b2;
	b1=(N3_BUS*)lp;
	b2=(N_BUS*)lp2;
	strcpy(b2->dev_name,b1->dev_name);
	b2->did=b1->did;
	b2->eid=b1->eid;
	b2->type=b1->type;
	b2->valarm=b1->valarm;
	b2->vl=b1->vl;
	GetptFromDRECT(b1->rt,b2->pt);
	return sizeof(N_BUS);
}

int FileV30::V3ActToBs(void *lp, void *lp2)
{
	N3_ACTOBJ  *a1;
	N_ACTOBJ *a2;
	a1=(N3_ACTOBJ*)lp;
	a2=(N_ACTOBJ*)lp2;
	//a2->dsrc=a1->dsrc;
	strcpy(a2->dsrc.name,a1->dsrc.name);
	a2->dsrc.did=a1->dsrc.did;
	a2->dsrc.dtype=a1->dsrc.dtype;
	a2->dsrc.xsmode=a1->dsrc.xsmode;

	a2->gid=a1->gid;
	a2->pathid=a1->pathid;
	a2->runmode=a1->runmode;
	a2->skip=a1->skip;
	a2->speed=a1->speed;
	GetptFromDRECT(a1->rt,a2->pt);
	return sizeof(N_ACTOBJ);
}

int FileV30::V3FlashToBs(void *lp, void *lp2)
{
	N3_FLASH  *f1;
	N_FLASH *f2;
	f1=(N3_FLASH*)lp;
	f2=(N_FLASH*)lp2;
	f2->align_buttom=f1->align_buttom;
	f2->align_left=f1->align_left;
	f2->align_right=f1->align_right;
	f2->align_top=f1->align_top;
	strcpy(f2->fname,f1->fname);
	f2->playmode=f1->playmode;
	GetptFromDRECT(f1->rt,f2->pt);
	return sizeof(N_FLASH);
}

int FileV30::V3PctToBs(void *lp, void *lp2)
{
	N3_PCTPIE *p1;
	N_PCTPIE *p2;
	p1=(N3_PCTPIE*)lp;
	p2=(N_PCTPIE*)lp2;
	p2->color1=p1->color1;
	p2->color2=p1->color2;
	strcpy(p2->dev_name,p1->dev_name);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	p2->lf=p1->lf;
	p2->maxv=p1->maxv;
	p2->type=p1->type;
	p2->zm=1;
	GetptFromDRECT(p1->rt,p2->pt);
	return sizeof(N_PCTPIE);
}


//将V5版本的内容转换到基本类中
int FileV30::GetBsFromV5(void *lp1, N_BASATTR &btr, void *lp2)
{
	char *lp;
	lp=(char*)lp1;
	N5_BASATTR *ar2;
	ar2=(N5_BASATTR*)lp1;
	btr.belong=ar2->belong;
	btr.ID=ar2->ID;
	btr.type=ar2->type;
	btr.size=0;
	lp+=sizeof(N5_BASATTR);
	//按每种类型转换
	switch(ar2->type)
	{
	case 1: //多边形
		btr.size=V5DbxToBs(lp,lp2);
		break;
	case 2: case 3://矩形，园
		btr.size=V5RectToBs(lp,lp2);
		break;
	case 4: //正弦半波形
		btr.size=V5HsinToBs(lp,lp2);
		break;
	case 5: //正弦波形
		btr.size=V5SinToBs(lp,lp2);
		break;
	case 6: //园弧
		btr.size=V5ArcToBs(lp,lp2);
		break;
	case 7: //方向箭头
		btr.size=V5ArrowToBs(lp,lp2);
		break;
	case 8: //玻璃层
		btr.size=V5GlassToBs(lp,lp2);
		break;
	case 10://文本
		btr.size=V5TextToBs(lp,lp2);
		break;
	case 11://电气端子
		btr.size=V5SiteToBs(lp,lp2);
		break;
	case 12://组合图元母板
		btr.size=V5MBoardToBs(lp,lp2);
		break;
	case 13: //坐标
		btr.size=V5CoordToBs(lp,lp2);
		break;
	case 14://表格线
		btr.size=V5TableToBs(lp,lp2);
		break;
	case 15://静态图形
		btr.size=V5SpicToBs(lp,lp2);
		break;
	case 16://路径
		btr.size=V5PathToBs(lp,lp2);
		break;
	case 17://静态小图标
		btr.size=V5PicToBs(lp,lp2);
		break;
	case 32://仪表1
		btr.size=V5Meter1ToBs(lp,lp2);
		break;
	case 33://仪表2
		btr.size=V5Meter2ToBs(lp,lp2);
		break;
	case 34://仪表3
		btr.size=V5Meter3ToBs(lp,lp2);
		break;
	case 35://仪表4
		btr.size=V5Meter4ToBs(lp,lp2);
		break;
	case 64://模拟量显示结构
		btr.size=V5AnlToBs(lp,lp2);
		break;
	case 65://水库
		btr.size=V5ReservoirToBs(lp, lp2);
		break;
	case 66://组合图元显示结构
		btr.size=V5ElegToBs(lp,lp2);
		break;
	case 67:
		btr.size=V5YBToBs(lp,lp2);
		break;
	case 68:
		btr.size=V5SysPieToBs(lp,lp2);
		break;
	case 69://棒图
		btr.size=V5BarToBs(lp,lp2);
		break;
	case 70://饼图结构数据
		btr.size=V5PieToBs(lp,lp2);
		break;
	case 71:case 72://日期格式,时间格式
		btr.size=V5DateToBs(lp,lp2);
		break;
	case 73://动画图形
		btr.size=V5GifToBs(lp,lp2);
		break;
	case 74://滚动文本
		btr.size=V5ScrtxtToBs(lp,lp2);
		break;
	case 75://按钮格式
		btr.size=V5PushToBs(lp,lp2);
		break;
	case 76://自助控件
		btr.size=V5SelfToBs(lp,lp2);
		break;
	case 77://潮流线
		btr.size=V5FlowToBs(lp,lp2);
		break;
	case 78://连接线
		btr.size=V5ConlToBs(lp,lp2);
		break;
	case 79://母线
		btr.size=V5BusToBs(lp,lp2);
		break;
	case 80://小型活动对象
		btr.size=V5ActToBs(lp,lp2);
		break;
	case 81://FLASH对象
		btr.size=V5FlashToBs(lp,lp2);
		break;
	case 82://百分比饼图
		btr.size=V5PctToBs(lp,lp2);
		break;
	case 83://区域
		btr.size=V5ZoneToBs(lp,lp2);
		break;
	case 84://多行
		btr.size=V5MttextToBs(lp,lp2);
		break;
	}
	return sizeof(N5_BASATTR)+ar2->size; //返回已使用字节数
}

int FileV30::V5DbxToBs(void *lp, void *lp2)
{
	int s;
	N5_DBX *d1;
	N_DBX  *d2;
	d1=(N5_DBX*)lp;
	d2=(N_DBX*)lp2;
	d2->close=d1->close;
	d2->bcolor1=d1->bcolor1;
	d2->fill=d1->fill;
	d2->fillmode=d1->fillmode;
	d2->lcolor=d1->lcolor;
	d2->ltype=d1->ltype;
	d2->ptsum=d1->ptsum;
	d2->bgmode=d1->bgmode;
	memcpy(d2->pt,d1->pt,d1->ptsum*sizeof(DPOINT));
	s=sizeof(N_DBX)+d1->ptsum*sizeof(DPOINT);
	return s;
}

int FileV30::V5RectToBs(void *lp, void *lp2)
{
	N5_RECT  *r1;
	N_RECT   *r2;
	r1=(N5_RECT*)lp;
	r2=(N_RECT*)lp2;
	r2->bcolor1=r1->bcolor1;
	r2->fill=r1->fill;
	r2->fillmode=r1->fillmode;
	r2->lcolor=r1->lcolor;
	r2->type=r1->type;
	GetptFromDRECT(r1->rt,r2->pt);
	return sizeof(N_RECT);
}

int FileV30::V5HsinToBs(void *lp, void *lp2)
{
	N5_HSIN  *h1;
	N_HSIN   *h2;
	h1=(N5_HSIN*)lp;
	h2=(N_HSIN*)lp2;
	h2->color=h1->color;
	h2->ltype=h1->hv;
	h2->pirodic=h1->pirodic;
	GetptFromDRECT(h1->rt,h2->pt);
	return sizeof(N_HSIN);
}

int FileV30::V5SinToBs(void *lp, void *lp2)
{
	N5_SIN *s1;
	N_SIN *s2;
	s1=(N5_SIN*)lp;
	s2=(N_SIN*)lp2;
	s2->color=s1->color;
	s2->ltype=s1->hv;
	s2->pirodic=s1->pirodic;
	s2->startdeg=s1->startdeg;
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SIN);
}

int FileV30::V5ArcToBs(void *lp, void *lp2)
{
	N5_ARC  *a1;
	N_ARC   *a2;
	a1=(N5_ARC*)lp;
	a2=(N_ARC*)lp2;
	a2->color=a1->color;
	a2->end=a1->end;
	a2->start=a1->start;
	GetptFromDRECT(a1->rt,a2->pt);
	return sizeof(N_ARC);
}

int FileV30::V5ArrowToBs(void *lp, void *lp2)
{
	N5_ARROW *a1;
	N_ARROW *a2;
	a1=(N5_ARROW*)lp;
	a2=(N_ARROW*)lp2;
	a2->color=a1->color;
	memcpy(a2->pt,a1->pt,2*sizeof(DPOINT));
	return sizeof(N_ARROW);
}

int FileV30::V5GlassToBs(void *lp, void *lp2)
{
	N5_GLASS *g1;
	N_GLASS *g2;
	g1=(N5_GLASS*)lp;
	g2=(N_GLASS*)lp2;
	g2->color=g1->color;
	g2->depth=g1->depth;
	g2->ocolor=g1->lcolor;
	g2->outline=g1->outline;
	GetptFromDRECT(g1->rt,g2->pt);
	return sizeof(N_GLASS);
}

int FileV30::V5TextToBs(void *lp, void *lp2)
{
	N5_TEXT *t1;
	N_TEXT *t2;
	t1=(N5_TEXT*)lp;
	t2=(N_TEXT*)lp2;
	t2->color=t1->color;
	t2->font=t1->font;
	t2->style=t1->style;
	t2->autofill=t1->autofit;
	if(t1->zm!=1&&t1->zm!=0)
	{
		t2->font.lfHeight=(int)(t1->font.lfHeight/t1->zm);
		t2->font.lfWidth=(int)(t1->font.lfWidth/t1->zm);
	}
	t2->zm=1;
	strcpy(t2->text,t1->text);
	GetptFromDRECT(t1->rt,t2->pt);
	return sizeof(N_TEXT);
}

int FileV30::V5SiteToBs(void *lp, void *lp2)
{
	N5_ESITE *e1;
	N_ESITE *e2;
	e1=(N5_ESITE*)lp;
	e2=(N_ESITE*)lp2;
	e2->color=e1->color;
	e2->solder=e1->solder;
	GetptFromDRECT(e1->rt,e2->pt);
	return sizeof(N_ESITE);
}

int FileV30::V5MBoardToBs(void *lp, void *lp2)
{
	N5_EGPMB *m1;
	N_EGPMB *m2;
	m1=(N5_EGPMB*)lp;
	m2=(N_EGPMB*)lp2;
	m2->color=m1->color;
	m2->mode=m1->mode;
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_EGPMB);
}

int FileV30::V5CoordToBs(void *lp, void *lp2)
{
	N5_COORDINATE *c1;
	N_COORDINATE *c2;
	c1=(N5_COORDINATE*)lp;
	c2=(N_COORDINATE*)lp2;
	c2->colorc=c1->colorc;
	c2->colort=c1->colort;
	c2->colorw=c1->colorw;
	c2->fontx=c1->fontx;
	c2->fonty=c1->fonty;
	c2->wxdraw=c1->wxdraw;
	c2->wydraw=c1->wydraw;
	c2->xdot=c1->xdot;
	c2->xmax=c1->xmax;
	c2->xmin=c1->xmin;
	c2->xvshow=c1->xvshow;
	c2->ydot=c1->ydot;
	c2->ymax=c1->ymax;
	c2->ymin=c1->ymin;
	c2->yvshow=c1->yvshow;
	c2->fontx=c1->fontx;
	c2->fonty=c1->fonty;
	c2->zm=1;
	GetptFromDRECT(c1->rt,c2->pt);
	return sizeof(N_COORDINATE);
}

int FileV30::V5TableToBs(void *lp, void *lp2)
{
	N5_TABLE  *t1;
	N_TABLE *t2;
	t1=(N5_TABLE*)lp;
	t2=(N_TABLE*)lp2;
	t2->color=t1->color;
	t2->dbline=t1->dbline;
	t2->line=t1->line;
	t2->width=t1->width;
	GetptFromDRECT(t1->rt,t2->pt);
	return sizeof(N_TABLE);
}

int FileV30::V5SpicToBs(void *lp, void *lp2)
{
	N5_IMG  *m1;
	N_IMG *m2;
	m1=(N5_IMG*)lp;
	m2=(N_IMG*)lp2;
	m2->depth=m1->depth;
	m2->imgID=m1->imgID;
	m2->shadow=m1->shadow;
	m2->zoom=m1->zoom;
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_IMG);
}

int FileV30::V5PathToBs(void *lp, void *lp2)
{
	N5_PATH  *p1;
	N_PATH *p2;
	p1=(N5_PATH*)lp;
	p2=(N_PATH*)lp2;
	p2->ID=p1->ID;
	p2->ptsum=p1->ptsum;
	memcpy(p2->pt,p1->pt,p1->ptsum*sizeof(DPOINT));
	return sizeof(N_PATH)+p1->ptsum*sizeof(DPOINT);
}

int FileV30::V5PicToBs(void *lp, void *lp2)
{
	N5_SPIC *s1;
	N_SPIC *s2;
	s1=(N5_SPIC*)lp;
	s2=(N_SPIC*)lp2;
	s2->picID=s1->picID;
	s2->zoom=s1->zoom;
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SPIC);
}

int FileV30::V5Meter1ToBs(void *lp, void *lp2)
{
	int i;
	N5_METER1 *m1;
	N_METER1  *m2;
	m1=(N5_METER1*)lp;
	m2=(N_METER1*)lp2;
	for(i=0;i<2;i++)  m2->pt[i]=m1->pt[i];
	m2->font=m1->font;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showarc=m1->showarc;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;
	m2->slen=m1->slen;
	m2->angle=m1->angle;		
	m2->pstyle=m1->pstyle;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;
	m2->axw=m1->axw;
	m2->pw=m1->pw;
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];
	m2->zm=1;
	m2->stype=m1->stype;
	m2->lstype=m1->lstype;
	return sizeof(N_METER1);
}


int FileV30::V5Meter2ToBs(void *lp, void *lp2)
{
	int i;
	N5_METER2 *m1;
	N_METER2  *m2;
	m1=(N5_METER2*)lp;
	m2=(N_METER2*)lp2;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showbl=m1->showbl;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;		
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_METER2);
}

int FileV30::V5Meter3ToBs(void *lp, void *lp2)
{
	int i;
	N5_METER3 *m1;
	N_METER3  *m2;
	m1=(N5_METER3*)lp;
	m2=(N_METER3*)lp2;
	m2->Vmin=m1->Vmin;			
	m2->Vmax=m1->Vmax;			
	m2->showbl=m1->showbl;		
	m2->shownum=m1->shownum;		
	m2->numdot=m1->numdot;			
	m2->rev=m1->rev;			
	m2->scale=m1->scale;		
	m2->scales=m1->scales;		
	m2->pcr=m1->pcr;			
	m2->scr=m1->scr;			
	m2->alarm=m1->alarm;		
	for(i=0;i<4;i++) m2->val[i]=m1->val[i];	
	for(i=0;i<2;i++) m2->cr[i]=m1->cr[i];
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_METER3);
}

int FileV30::V5Meter4ToBs(void *lp, void *lp2)
{
	int i;
	N5_METER4 *m1;
	N_METER4  *m2;
	m1=(N5_METER4*)lp;
	m2=(N_METER4*)lp2;
	m2->num=m1->num;
	m2->numdot=m1->numdot;
	m2->bcr=m1->bcr;
	for(i=0;i<2;i++) m2->ncr[i]=m1->ncr[i];
	GetptFromDRECT(m1->rt,m2->pt);
	return sizeof(N_METER3);
}

int FileV30::V5AnlToBs(void *lp, void *lp2)
{
	N5_ANL *a1;
	N_ANL *a2;
	a1=(N5_ANL*)lp;
	a2=(N_ANL*)lp2;
	a2->acolor=a1->acolor;
	a2->direction=a1->angle==0 ? 0:1;
	strcpy(a2->dev_name,a1->dev_name);
	a2->did=a1->did;
	a2->dtype=a1->dtype;
	a2->lf=a1->lf;
	a2->ncolor=a1->ncolor;
	a2->style=a1->style;
	a2->xs=a1->xs;
	a2->xsmode=a1->xsmode;
	a2->lf=a1->lf;
	a2->zm=1;
	GetptFromDRECT(a1->rt,a2->pt);
	return sizeof(N_ANL);
}

int FileV30::V5ReservoirToBs(void *lp, void *lp2)
{
	int i,size;
	N5_RESERVOIR *a1;
	N_RESERVOIR  *a2;
	a1=(N5_RESERVOIR*)lp;
	a2=(N_RESERVOIR *)lp2;
	a2->color=a1->color;
	strcpy(a2->dev_name,a1->dev_name);
	a2->did=a1->did;
	a2->hcolor=a1->hcolor;
	a2->lcolor=a1->lcolor;
	a2->ncolor=a1->ncolor;
	a2->ptsum=a1->ptsum;
	size=sizeof(N_RESERVOIR)+a2->ptsum*sizeof(DPOINT);
	for(i=0;i<a2->ptsum;i++)	a2->pt[i]=a1->pt[i];
	return size;
}

int FileV30::V5ElegToBs(void *lp, void *lp2)
{
	N5_ELEGRPA *e1;
	N_ELEGRPA *e2;
	e1=(N5_ELEGRPA*)lp;
	e2=(N_ELEGRPA*)lp2;
	strcpy(e2->dev_name,e1->dev_name);
	e2->did=e1->did;
	e2->egrpid=e1->egrpid;
	e2->genrev=e1->genrev;
	e2->runshow=e1->runshow;
	e2->showno=e1->showno;
	e2->sitesum=e1->sitesum;
	e2->type=e1->type;
	e2->subtype=e1->subtype;
	GetptFromDRECT(e1->rt,e2->pt);
	memcpy(e2->site,e1->site,3*sizeof(D_SITE));
	return sizeof(N_ELEGRPA);
}


int FileV30::V5YBToBs(void *lp, void *lp2)
{
	int i,j;
	N5_ELEGRPYB *e1;
	N_ELEGRPYB *e2;
	e1=(N5_ELEGRPYB*)lp;
	e2=(N_ELEGRPYB*)lp2;
	e2->egrpid=e1->egrpid;
	e2->dbsum=e1->dbsum;
	for(i=0;i<8;i++){
		//e2->dbs[i]=e1->dbs[i];
		//e2->pam[i]=e1->pam[i];
		strcpy(e2->dbs[i].name,e1->dbs[i].name);
		e2->dbs[i].did=e1->dbs[i].did;
		e2->dbs[i].dtype=e1->dbs[i].dtype;
		e2->dbs[i].xsmode=e1->dbs[i].xsmode;

		e2->pam[i].ptype=e1->pam[i].ptype;
		e2->pam[i].vmin=e1->pam[i].vmin;
		e2->pam[i].vmax=e1->pam[i].vmax;
		e2->pam[i].alarm=e1->pam[i].alarm;
		for(j=0;j<4;j++) e2->pam[i].val[j]=e1->pam[i].val[j];
		for(j=0;j<2;j++) e2->pam[i].color[j]=e1->pam[i].color[j];
	}
	GetptFromDRECT(e1->rt,e2->pt);
	return sizeof(N_ELEGRPYB);
}

int FileV30::V5BarToBs(void *lp, void *lp2)
{
	N5_BAR *b1;
	N_BAR *b2;
	b1=(N5_BAR*)lp;
	b2=(N_BAR*)lp2;
	b2->acolor=b1->acolor;
	b2->aval=b1->aval;
	//b2->dsrc=b1->dsrc;
	strcpy(b2->dsrc.name,b1->dsrc.name);
	b2->dsrc.did=b1->dsrc.did;
	b2->dsrc.dtype=b1->dsrc.dtype;
	b2->dsrc.xsmode=b1->dsrc.xsmode;

	b2->max=b1->max;
	b2->min=b1->min;
	b2->ncolor=b1->ncolor;
	b2->outline=b1->outline;
	b2->style=b1->style;
	b2->xy=b1->xy;
	GetptFromDRECT(b1->rt,b2->pt);
	return sizeof(N_BAR);
}

int FileV30::V5SysPieToBs(void *lp, void *lp2)
{
	N5_SYSPIE *p1;
	N_SYSPIE *p2;
	p1=(N5_SYSPIE*)lp;
	p2=(N_SYSPIE*)lp2;
	p2->lf=p1->lf;
	p2->ID=p1->ID;
	memcpy(p2->color,p1->color,24);
	p2->fcolor=p1->fcolor;
	p2->type=p1->type;
	GetptFromDRECT(p1->rt,p2->pt);
	return sizeof(N_SYSPIE);
}

int FileV30::V5PieToBs(void *lp, void *lp2)
{
	/*N5_PIE *p1;
	N_PIE *p2;
	p1=(N5_PIE*)lp;
	p2=(N_PIE*)lp2;
	p2->angle=p1->angle;
	memcpy(p2->color,p1->color,32);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	strcpy(p2->name,p1->name);
	p2->outline=p1->outline;
	memcpy(p2->pd,p1->pd,8*sizeof(NPIEDAT));
	p2->shad=p1->shad;
	p2->style=p1->style;
	p2->sum=p1->sum;
	GetptFromDRECT(p1->rt,p2->pt);*/
	N5_PIE *p1;
	N_PIE *p2;
	p1=(N5_PIE*)lp;
	p2=(N_PIE*)lp2;
	p2->lf=p1->lf;
	memcpy(p2->color,p1->color,12);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	p2->type=p1->type;
	strcpy(p2->name,p1->name);
	GetptFromDRECT(p1->rt,p2->pt);
	return sizeof(N_PIE);
	return sizeof(N_PIE);
}

int FileV30::V5DateToBs(void *lp, void *lp2)
{
	N5_DATE *d1;
	N_DATE *d2;
	d1=(N5_DATE*)lp;
	d2=(N_DATE*)lp2;
	d2->bcolor=d1->bcolor;
	d2->fcolor=d1->fcolor;
	d2->fmt=d1->fmt;
	d2->font=d1->font;
	d2->outcolor=d1->outcolor;
	d2->shadow=d1->shadow;
	d2->tran=d1->tran;
	if(d1->zm!=1&&d1->zm!=0){
		d2->font.lfHeight=(int)(d1->font.lfHeight/d1->zm);
		d2->font.lfWidth=(int)(d1->font.lfWidth/d1->zm);
	}
	d2->zm=1;
	d2->outline=d1->outline;
	GetptFromDRECT(d1->rt,d2->pt);
	return sizeof(N_DATE);
}

int FileV30::V5GifToBs(void *lp, void *lp2)
{
	N5_GIFAML *g1;
	N_GIFAML *g2;
	g1=(N5_GIFAML*)lp;
	g2=(N_GIFAML*)lp2;
	//g2->dsrc=g1->dsrc;

	strcpy(g2->dsrc.name,g1->dsrc.name);
	g2->dsrc.did=g1->dsrc.did;
	g2->dsrc.dtype=g1->dsrc.dtype;
	g2->dsrc.xsmode=g1->dsrc.xsmode;
	strcpy(g2->fname,g1->fname);
	g2->rec=g1->rec;
//	g2->type=g1->type;
	GetptFromDRECT(g1->rt,g2->pt);
	return sizeof(N_GIFAML);
}

int FileV30::V5ScrtxtToBs(void *lp, void *lp2)
{
	N5_SRLTEXT *s1;
	N_SRLTEXT *s2;
	s1=(N5_SRLTEXT*)lp;
	s2=(N_SRLTEXT*)lp2;
	s2->align=s1->align;
	s2->depth=s1->depth;
	s2->direct=s1->direct;
	s2->fcolor=s1->fcolor;
	s2->gcolor=s1->gcolor;
	s2->glass=s1->glass;
	s2->lf=s1->lf;
	s2->outline=s1->outline;
	s2->tcolor=s1->tcolor;
	if(s1->zm!=1&&s1->zm!=0){
		s2->lf.lfHeight=(int)(s1->lf.lfHeight/s1->zm);
		s2->lf.lfWidth=(int)(s1->lf.lfWidth/s1->zm);
	}
	s2->zm=1;
	strcpy(s2->text,s1->text);
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SRLTEXT);
}

int FileV30::V5PushToBs(void *lp, void *lp2)
{
	N5_PUSH *p1;
	N_PUSH *p2;
	p1=(N5_PUSH*)lp;
	p2=(N_PUSH*)lp2;
	p2->autlin=p1->autlin;
	p2->cmdnum=p1->cmdnum;
	p2->cmdtype=p1->cmdtype;
	p2->color1=p1->color1;
	p2->color2=p1->color2;
	strcpy(p2->command,p1->command);
	p2->lf=p1->lf;
	p2->selfid=p1->selfid;
	p2->shadow=p1->shadow;
	p2->spicid=p1->spicid;
	p2->style=p1->style;
	strcpy(p2->title,p1->title);
	if(p1->zm!=1&&p1->zm!=0){
		p2->lf.lfHeight=(int)(p1->lf.lfHeight/p1->zm);
		p2->lf.lfWidth=(int)(p1->lf.lfWidth/p1->zm);
	}
	p2->zm=1;
	p2->tosta=p1->tosta;
	GetptFromDRECT(p1->rt,p2->pt);
	return sizeof(N_PUSH);
}

int FileV30::V5SelfToBs(void *lp, void *lp2)
{
	N5_SELFCTL *s1;
	N_SELFCTL *s2;
	s1=(N5_SELFCTL*)lp;
	s2=(N_SELFCTL*)lp2;
	s2->abottom=s1->abottom;
	s2->aleft=s1->aleft;
	s2->aright=s1->aright;
	s2->atop=s1->atop;
	strcpy(s2->dllname,s1->dllname);
	s2->id=s1->id;
	memcpy(s2->lkbuf,s1->lkbuf,255);
	s2->mode=s1->mode;
	s2->style=s1->style;
	GetptFromDRECT(s1->rt,s2->pt);
	return sizeof(N_SELFCTL);
}

int FileV30::V5FlowToBs(void *lp, void *lp2)
{
	N5_FLOW *f1;
	N_FLOW *f2;
	f1=(N5_FLOW*)lp;
	f2=(N_FLOW*)lp2;
	f2->color1=f1->color1;
	f2->color2=f1->color2;
	strcpy(f2->dev_name,f1->dev_name);
	f2->did=f1->did;
	f2->direct=f1->direct;
	f2->ptsum=f1->ptsum;
	memcpy(f2->site,f1->site,2*sizeof(D_SITEB));
	f2->style=f1->style;
	f2->type=f1->type;
	f2->vl=f1->vl;
	f2->linewidth=f1->linewidth>4 ? 0:f1->linewidth;
	memcpy(f2->pt,f1->pt,f1->ptsum*sizeof(DPOINT));
	return sizeof(N_FLOW)+f1->ptsum*sizeof(DPOINT);
}

int FileV30::V5ZoneToBs(void *lp, void *lp2)
{
	N5_ZONE *f1;
	N_ZONE *f2;
	f1=(N5_ZONE*)lp;
	f2=(N_ZONE*)lp2;
	f2->lcolor=f1->lcolor;
	strcpy(f2->zone_name,f1->zone_name);
	f2->lf=f1->lf;
	f2->fcolor=f1->fcolor;
	f2->did=f1->did;
	f2->ptsum=f1->ptsum;
	memcpy(f2->pt,f1->pt,f1->ptsum*sizeof(DPOINT));
	return sizeof(N_ZONE)+f1->ptsum*sizeof(DPOINT);
}

int FileV30::V5MttextToBs(void *lp, void *lp2)
{
	N5_MTTEXT *f1;
	N_MTTEXT *f2;
	f1=(N5_MTTEXT*)lp;
	f2=(N_MTTEXT*)lp2;
	f2->fcolor=f1->fcolor;
	strcpy(f2->name,f1->name);
	f2->lf=f1->lf;
	f2->did=f1->did;
	f2->type=f1->type;
	strcpy(f2->text,f1->text);
	GetptFromDRECT(f1->rt,f2->pt);
	return sizeof(N_MTTEXT);
}

int FileV30::V5ConlToBs(void *lp, void *lp2)
{
	N5_CONLINE *c1;
	N_CONLINE *c2;
	c1=(N5_CONLINE*)lp;
	c2=(N_CONLINE*)lp2;
	c2->conobj=c1->conobj;
	memcpy(c2->lobj,c1->lobj,2*sizeof(LOGOBJ));
	c2->ptsum=c1->ptsum;
	c2->solder1=c1->solder1;
	c2->solder2=c1->solder2;
	c2->vl=c1->vl;
	memcpy(c2->pt,c1->pt,c2->ptsum*sizeof(DPOINT));
	return sizeof(N_CONLINE)+c2->ptsum*sizeof(DPOINT);
}

int FileV30::V5BusToBs(void *lp, void *lp2)
{
	N5_BUS *b1;
	N_BUS *b2;
	b1=(N5_BUS*)lp;
	b2=(N_BUS*)lp2;
	strcpy(b2->dev_name,b1->dev_name);
	b2->did=b1->did;
	b2->eid=b1->eid;
	b2->type=b1->type;
	b2->valarm=b1->valarm;
	b2->vl=b1->vl;
	GetptFromDRECT(b1->rt,b2->pt);
	return sizeof(N_BUS);
}

int FileV30::V5ActToBs(void *lp, void *lp2)
{
	N5_ACTOBJ  *a1;
	N_ACTOBJ *a2;
	a1=(N5_ACTOBJ*)lp;
	a2=(N_ACTOBJ*)lp2;
	//a2->dsrc=a1->dsrc;
	strcpy(a2->dsrc.name,a1->dsrc.name);
	a2->dsrc.did=a1->dsrc.did;
	a2->dsrc.dtype=a1->dsrc.dtype;
	a2->dsrc.xsmode=a1->dsrc.xsmode;

	a2->gid=a1->gid;
	a2->pathid=a1->pathid;
	a2->runmode=a1->runmode;
	a2->skip=a1->skip;
	a2->speed=a1->speed;
	GetptFromDRECT(a1->rt,a2->pt);
	return sizeof(N_ACTOBJ);
}

int FileV30::V5FlashToBs(void *lp, void *lp2)
{
	N5_FLASH  *f1;
	N_FLASH *f2;
	f1=(N5_FLASH*)lp;
	f2=(N_FLASH*)lp2;
	f2->align_buttom=f1->align_buttom;
	f2->align_left=f1->align_left;
	f2->align_right=f1->align_right;
	f2->align_top=f1->align_top;
	strcpy(f2->fname,f1->fname);
	f2->playmode=f1->playmode;
	GetptFromDRECT(f1->rt,f2->pt);
	return sizeof(N_FLASH);
}

int FileV30::V5PctToBs(void *lp, void *lp2)
{
	N5_PCTPIE *p1;
	N_PCTPIE *p2;
	p1=(N5_PCTPIE*)lp;
	p2=(N_PCTPIE*)lp2;
	p2->color1=p1->color1;
	p2->color2=p1->color2;
	strcpy(p2->dev_name,p1->dev_name);
	p2->did=p1->did;
	p2->fcolor=p1->fcolor;
	p2->lf=p1->lf;
	p2->maxv=p1->maxv;
	p2->type=p1->type;
	p2->zm=1;
	GetptFromDRECT(p1->rt,p2->pt);
	return sizeof(N_PCTPIE);
}