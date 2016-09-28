// bclass.cpp: implementation of the APoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bclass.h"
#include "math.h"
#include "middll.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CPoint mpt[1024]; //临时用的一个点缓冲区，最大1024个点
extern DPOINT npt[1024];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//模拟量显示的调整矩形
void OffsetRt(CRect &rt,int wh, int direct, int qh)
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

//显示一个数字
void ShowDigit(HDC hdc,CRect &rt,LOGFONT *lf,float val,char *pre,char *unit,char xs,DWORD color,BYTE style)
{
	char p[64],p1[64];
	strcpy(p,pre);
	GetDoubleStr(val,p1,xs);
	strcat(p,p1);
	strcat(p,unit);
	GLDDrawText(hdc,rt,lf,p,color,style,DT_LEFT);
}

void ShowDigitPQ(HDC hdc,CRect &rt,LOGFONT *lf,float vp,float vq,char xs,DWORD color1,DWORD color2,BYTE style,BYTE direction)
{
	SIZE sz;
	char p[64],p1[64];
	GetDoubleStr(vp,p,xs);
	GLDDrawText(hdc,rt,lf,p,color1,style,DT_LEFT);
	sz=GLDGetTextSize(hdc,lf,p);
	if(vq>=0) strcpy(p,"+j");
	else strcpy(p,"-j");
	GetDoubleStr(vq,p1,xs);
	strcat(p,p1);
	OffsetRt(rt,sz.cx,direction,1);
	GLDDrawText(hdc,rt,lf,p,color2,style,DT_LEFT);
}

//显示模拟量（太复杂，单独剔除编写,需要多处调用)
void ShowAnalog(HDC hdc,CRect &rt,LOGFONT *lf,N_ANL *anl,int pm)
{
	int i;
	SIZE sz;
	char p[64],p1[64];
	DWORD color1,color2;
	color1=anl->rval[0].alarm==0 ? anl->ncolor:anl->acolor;
	if(pm!=0) color1=0;
	color2=anl->rval[1].alarm==0 ? anl->ncolor:anl->acolor;
	if(pm!=0) color2=0;
	switch(anl->dtype)
	{
	case 0:case 4: //"发电机","交流线路","负荷"
		{
			switch(anl->xsmode){
			case 0:
				ShowDigitPQ(hdc,rt,lf,anl->rval[0].curval,anl->rval[1].curval,anl->xs,
					color1,color2,anl->style,anl->direction);
				break;
			case 1:
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 2:
				ShowDigit(hdc,rt,lf,anl->rval[1].curval,"","",anl->xs,color2,anl->style);
				break;
			}
		}
		break;
	case 1: //交流线
		{
			switch(anl->xsmode)
			{
			case 0:case 1:
				ShowDigitPQ(hdc,rt,lf,anl->rval[0].curval,anl->rval[1].curval,anl->xs,
					color1,color2,anl->style,anl->direction);
				break;
			case 2:
				ShowDigit(hdc,rt,lf,anl->rval[1].curval,"","",anl->xs,color2,anl->style);
				break;
			case 3:
				ShowDigit(hdc,rt,lf,anl->rval[1].curval,"","",anl->xs,color2,anl->style);
				break;
			case 4:
				ShowDigit(hdc,rt,lf,anl->rval[1].curval,"","",anl->xs,color2,anl->style);
				break;
			case 5:
				ShowDigit(hdc,rt,lf,anl->rval[1].curval,"","",anl->xs,color2,anl->style);
				break;
			case 6:
				ShowDigit(hdc,rt,lf,anl->rval[1].curval,"","",anl->xs,color2,anl->style);
				break;
			}
		}
		break;
	case 2: //直流线路
		{
			switch(anl->xsmode)
			{
			case 0:case 1:
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 2:
				ShowDigit(hdc,rt,lf,anl->rval[1].curval,"","",anl->xs,color2,anl->style);
				break;
			}
		}
		break;
	case 3: //节点
		{
			switch(anl->xsmode)
			{
			case 0: // 显示电压等级
				color1=pm!=0 ? 0:anl->ncolor;
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"等级:","kV",anl->xs,color1,anl->style);
				break;
			case 1:
				ShowDigit(hdc,rt,lf,anl->rval[1].curval,"","pu",anl->xs,color2,anl->style);
				break;
			case 2:
				ShowDigit(hdc,rt,lf,(float)113.11,"","",anl->xs,color2,anl->style);
				break;
			case 3:
				ShowDigit(hdc,rt,lf,anl->rval[2].curval,"","deg",anl->xs,color2,anl->style);
				break;
			}
		}
		break;
	case 5:  //变压器
		{
			switch(anl->xsmode)
			{
			case 0: // 显示档位
				{
					if(pm!=0) color1=0; else color1=anl->ncolor;
					ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				}
				break;
			case 1: // 高端有功
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 2: // 高端无功
				ShowDigit(hdc,rt,lf,anl->rval[1].curval,"","",anl->xs,color1,anl->style);
				break;
			case 3: // 高端电流
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 4: // 低端有功
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 5: // 低端无功
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 6: // 低端电流
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			}
		}
		break;
	case 6: //三绕组变压器
		{
			switch(anl->xsmode)
			{
			case 0: // 显示档位
				{
					sz=GLDGetTextSize(hdc,lf,"M");
					if(pm!=0) color1=0; else color1=anl->ncolor;
					GetDoubleStr(anl->rval[0].curval,p1,0);
					sprintf(p,"%s",p1);
					GLDDrawText(hdc,&rt,lf,p,color1,anl->style,DT_LEFT);

					/*GetDoubleStr(anl->rval[1].curval,p1,0);
					sprintf(p,"中:%s",p1);
					OffsetRt(rt,sz.cy,anl->direction,0);
					GLDDrawText(hdc,&rt,lf,p,color1,anl->style,DT_LEFT);
					GetDoubleStr(anl->rval[2].curval,p1,0);
					sprintf(p,"低:%s",p1);
					OffsetRt(rt,sz.cy,anl->direction,0);
					GLDDrawText(hdc,&rt,lf,p,color1,anl->style,DT_LEFT);*/
				}
				break;
			case 1: // 高端有功
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 2: // 高端无功
				ShowDigit(hdc,rt,lf,anl->rval[1].curval,"","",anl->xs,color1,anl->style);
				break;
			case 3: // 高端电流
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","A",anl->xs,color1,anl->style);
				break;
			case 4: // 低端有功
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 5: // 低端无功
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 6: // 低端电流
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 7: //中端有功
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 8: // 中端无功
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 9: // 中端电流
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			}
		}
		break;
	case 7:   
	case 8: //电容器，电抗器投入组数
		{
			switch(anl->xsmode)
			{
			case 0:
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
				break;
			case 1:
				ShowDigit(hdc,rt,lf,anl->rval[1].curval,"","",0,color1,anl->style);
				break;
			}
		}
		break;
	case 9:  //显示SVC
		{
		color1=pm!=0 ? 0:anl->ncolor;
		ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","Mvar",anl->xs,color1,anl->style);
		}
		break;
	case 10:
		{
		color1=pm!=0 ? 0:anl->ncolor;
		i=anl->xsmode;
		i=i>3 ? 3:i;
		if(i<3) ShowDigit(hdc,rt,lf,anl->rval[i].curval,"","",anl->xs,color1,anl->style);
		else ShowDigit(hdc,rt,lf,anl->rval[i].curval,"","",anl->xs,color1,anl->style);
		}
		break;
	case 11:
		{
			color1=pm!=0 ? 0:anl->ncolor;
			i=anl->xsmode;
			switch(i)
			{
			case 0:case 2:case 3:case 4:
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","MW",anl->xs,color1,anl->style);
				break;
			case 1:case 5:
				ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","MVar",anl->xs,color1,anl->style);
				break;
			}
		}
		break;
	case 12:
	case 13:
	case 14:
	case 15:
		{
			color1=pm!=0 ? 0:anl->ncolor;
			ShowDigit(hdc,rt,lf,anl->rval[0].curval,"","",anl->xs,color1,anl->style);
		}
		break;
	}
}
//////////////////////////////////////////////////////////////////////
void  GetptFromDRECT(DRECT&rt,DPOINT *pt)
{
	pt[0].x=rt.left; pt[0].y=rt.top;
	pt[1].x=rt.right;pt[1].y=rt.top;
	pt[2].x=rt.right;pt[2].y=rt.bottom;
	pt[3].x=rt.left;pt[3].y=rt.bottom;
}
//////////////////////////////////////////////////////////////////////
CDRect CreateNRt(int ptsum,DPOINT *pt)
{
	int i;
	CDRect rt;
	rt.left=pt[0].x;
	rt.top=pt[0].y;
	rt.right=pt[0].x;
	rt.bottom=pt[0].y;
	for(i=1;i<ptsum;i++){
		if(pt[i].x<rt.left) rt.left=pt[i].x;
		if(pt[i].x>rt.right) rt.right=pt[i].x;
		if(pt[i].y<rt.top) rt.top=pt[i].y;
		if(pt[i].y>rt.bottom) rt.bottom=pt[i].y;
	}
	return rt;
};

//////////////////////////////////////////////////////////////////////
CRect CreateNRt(int ptsum,POINT *pt)
{
	int i;
	CRect rt;
	rt.left=pt[0].x;
	rt.top=pt[0].y;
	rt.right=pt[0].x;
	rt.bottom=pt[0].y;
	for(i=1;i<ptsum;i++){
		if(pt[i].x<rt.left) rt.left=pt[i].x;
		if(pt[i].x>rt.right) rt.right=pt[i].x;
		if(pt[i].y<rt.top) rt.top=pt[i].y;
		if(pt[i].y>rt.bottom) rt.bottom=pt[i].y;
	}
	return rt;
};

HRGN CreateNRGN(int ptsum,DPOINT *pt,int type,int close,double zoom)
{
	HRGN hrgn=NULL;
	CDPoint ap;
	int i;
	for(i=0;i<ptsum;i++)
	{
		ap.x=(double)(pt[i].x*zoom);
		ap.y=(double)(pt[i].y*zoom);
		ap.GetPOINT(mpt[i]);
	}
	mpt[ptsum]=mpt[0];
	
	switch(type)
	{
	case 0:
		if(close==0) hrgn=CreatePolyRgn(ptsum,mpt);
		else hrgn=CreatePolyRgn(ptsum+1,mpt);
		break;
	case 1:
		hrgn=CreatePolygonRgn(mpt,ptsum,ALTERNATE);
		break;
	}
	if(hrgn==NULL)
	{
		hrgn=CreatePolygonRgn(mpt,ptsum,ALTERNATE);
	}
	return hrgn;
}


void GetCircleDOT(DPOINT *pt,CRect rt,double zm)
{
	int i;
	double xl,yl;
	CDRect rt1;
	for(i=0;i<36;i++){
		pt[i].y=(double)(100+100*sin(i*20*PI/360));
		pt[i].x=(double)(100+100*cos(i*20*PI/360));
	}
	rt1.SetCRect(rt);
	rt1.ScrRtToAct(zm);
	xl=(double)(rt1.Width()/200);
	yl=(double)(rt1.Height()/200);
	for(i=0;i<36;i++){
		pt[i].y=(double)(pt[i].y*yl+rt.top/zm);
		pt[i].x=(double)(pt[i].x*xl+rt.left/zm);
	}
}

//返回两点间的距离(未取平方根)
int GetDistance(CPoint p1, CPoint p2)
{
	int a,b;
	a=p2.x-p1.x;
	b=p2.y-p1.y;
	return a*a+b*b;
}

void BRotateObj(DPOINT  cpt,DPOINT &inpt,DPOINT &outpt,double angle)
{
	double r,x1,y1,dx,dy,a;
	dx=cpt.x-inpt.x;
	dy=cpt.y-inpt.y;
	r=sqrt((double)(dx*dx+dy*dy));
	a=(double)(180*asin(dy/r)/PI);
	if(dx>0&&dy>0) a=(double)(180-a);
	if(dx>0&&dy<0) a=(double)(-180-a);
	if(a<0) a=(double)(360+a);
	a=(double)(a+angle);
	x1=(double)(r*cos(a*PI/180));
	y1=(double)(r*sin(a*PI/180));
	outpt.x=(double)(cpt.x+x1);
	outpt.y=(double)(cpt.y-y1);
}

void BRotateObj(DPOINT  cpt,DPOINT &inpt,POINT &outpt,double angle)
{
	double r,x1,y1,dx,dy,a;
	dx=cpt.x-inpt.x;
	dy=cpt.y-inpt.y;
	r=sqrt((double)(dx*dx+dy*dy));
	a=(double)(180*asin(dy/r)/PI);
	if(dx>0&&dy>0) a=(double)(180-a);
	if(dx>0&&dy<0) a=(double)(-180-a);
	if(a<0) a=(double)(360+a);
	a=(double)(a+angle);
	x1=(double)(r*cos(a*PI/180));
	y1=(double)(r*sin(a*PI/180));
	outpt.x=(int)(cpt.x+x1);
	outpt.y=(int)(cpt.y-y1);
}


void MoveObjRect(CDRect &rt,double mx,double my,int opno)
{
	switch(opno)
	{
	case 1:
		rt.left+=mx;
		rt.top+=my;
		break;
	case 2:
		rt.right+=mx;
		rt.top+=my;
		break;
	case 3:
		rt.right+=mx;
		rt.bottom+=my;
		break;
	case 4:
		rt.left+=mx;
		rt.bottom+=my;
		break;
	}
	rt.NormalizeRect();
}


void HoldWH(CDRect &rt,double w,double h,int opno)
{
	double w1,h1,xl;
	if(w==0||h==0) return;
	xl=h/w;
	w1=rt.Width();
	h1=rt.Height();
	h1=w1*xl;
	switch(opno)
	{
	case 1:
		rt.left=rt.right-w1;
		rt.top=rt.bottom-h1;
		break;
	case 2:
		rt.right=rt.left+w1;
		rt.top=rt.bottom-h1;
		break;
	case 3:
		rt.right=rt.left+w1;
		rt.bottom=rt.top+h1;
		break;
	case 4:
		rt.left=rt.right-w1;
		rt.bottom=rt.top+h1;
		break;
	}
}


//计算一个矩形的72个点
int GetCirclePoint(DPOINT *pt,CDRect &art)
{
	int i;
	DPOINT cpt;
	double a,r,xl,w,h,c;
	w=art.Width();
	h=art.Height();
	if(h==0) return 0;
	r=h/2.0;
	xl=w/h;
	cpt=art.CenterPoint();
	c=PI/180;
	for(i=0;i<72;i++){
		a=(double)(5*i*c);
		pt[71-i].x=cpt.x+xl*r*cos(a);
		pt[71-i].y=cpt.y+r*sin(a);
	}
	a=(double)(5*72*c);
	pt[0].x=cpt.x+xl*r*cos(a);
	pt[0].y=cpt.y+r*sin(a);
	return 72;
}


//计算角度
/*double GetAngle(DPOINT p1,DPOINT p2)
{
	double x1,y1,r,j;
	x1=(double)(p1.x-p2.x);
	y1=(double)(p1.y-p2.y);
	r=sqrt((double)(x1*x1+y1*y1));
	j=(double)(180*asin(y1/r)/PI);
	if(x1>0&&y1>0) j=(double)(180-j);
	if(x1>0&&y1<0) j=(double)(-180-j);
	if(j<0) j=(double)(360+j);
	return j;
}*/

//计算一个矩形的36个点
bool GetHSinPoint(DPOINT *pt,DPOINT *spt,int np,int ptsum)
{
	int i,j,n;
	DPOINT cpt,cpt2,cp[4];
	double a,r,xl,nl,x,y,w,h,a1,a2,angle;
	for(i=0;i<4;i++) cp[i]=spt[i];
	w=GetLength(cp[0],cp[3]);
	h=GetLength(cp[2],cp[3]);
	a2=GetAngle(cp[3],cp[0]);
	a1=GetAngle(cp[3],cp[2]);
	a2=(double)(a2-a1-90);
	if(h==0) return false;
	r=(double)(h/2);
	xl=(double)(w/h);
	n=0;
	nl=(double)(h/np);
	nl=(double)(nl/18);
	for(i=0;i<=np;i++){
	 for(j=0;j<18;j++){
		 if(n>=ptsum) break;
		 a=(double)(10*j);
		 x=(double)(nl*n);
		 y=(double)(-w+w*sin(a*PI/180));
		 pt[n].x=x;
		 pt[n].y=y;
		 cpt.x=x;
		 cpt.y=0;
		 BRotateObj(cpt,pt[n],pt[n],a2);
		 pt[n].x=(double)(pt[n].x+cp[3].x);
		 pt[n].y=(double)(pt[n].y+cp[3].y);
		 n++;
	 }
	}

	cpt.x=(double)((cp[3].x+cp[0].x)/2);
	cpt.y=(double)((cp[3].y+cp[0].y)/2);
	cpt2.x=(double)((cp[1].x+cp[2].x)/2);
	cpt2.y=(double)((cp[1].y+cp[2].y)/2);
	angle=GetAngle(cp[3],cp[2]);
	for(i=0;i<ptsum;i++){
	  BRotateObj(cp[3],pt[i],pt[i],angle);
	}
	return true;
}

//计算一个矩形的36个点
bool GetSinPoint(DPOINT *pt,DPOINT *spt,int np,int ptsum)
{
	int i,j,n;
	DPOINT cpt,cpt2,cp[4];
	double a,r,xl,nl,x,y,w,h,w1,a1,a2,angle;
	for(i=0;i<4;i++) cp[i]=spt[i];
	w=GetLength(cp[0],cp[3]);
	h=GetLength(cp[2],cp[3]);
	a2=GetAngle(cp[3],cp[0]);
	a1=GetAngle(cp[3],cp[2]);
	a2=(double)(a2-a1-90);
	if(h==0) return false;
	r=(double)(h/2);
	xl=(double)(w/h);
	n=0;
	nl=(double)(h/np);
	nl=(double)(nl/18);
	w1=(double)(w/2);
	for(i=0;i<=np;i++){
	 for(j=0;j<18;j++){
		 if(n>=ptsum) break;
		 a=(double)(20*j);
		 x=(double)(nl*n);
		 y=(double)(-w1+w1*sin(a*PI/180));
		 pt[n].x=x;
		 pt[n].y=y;
		 cpt.x=x;
		 cpt.y=0;
		 BRotateObj(cpt,pt[n],pt[n],a2);
		 pt[n].x=(double)(pt[n].x+cp[3].x);
		 pt[n].y=(double)(pt[n].y+cp[3].y);
		 n++;
	 }
	}

	cpt.x=(double)((cp[3].x+cp[0].x)/2);
	cpt.y=(double)((cp[3].y+cp[0].y)/2);
	cpt2.x=(double)((cp[1].x+cp[2].x)/2);
	cpt2.y=(double)((cp[1].y+cp[2].y)/2);
	angle=GetAngle(cp[3],cp[2]);
	for(i=0;i<ptsum;i++){
	  BRotateObj(cp[3],pt[i],pt[i],angle);
	}
	return true;
}

DWORD ltype[]={PS_SOLID,PS_DASH,PS_DOT,PS_DASHDOT,PS_DASHDOTDOT};
DWORD lep[]={PS_ENDCAP_ROUND,PS_ENDCAP_SQUARE,PS_ENDCAP_FLAT};

void BDrawDbx(HDC hdc,int num,POINT *pt,BYTE width,DWORD color,
			  DWORD colorb,BYTE type,BYTE lmode,BYTE endcap){
	int i,j,w;
	HPEN oldpen,pen1,pen2;
	LOGBRUSH  lp;
	lp.lbColor=color;
	lp.lbHatch=0;
	i=type>4 ? 0:type;
	j=endcap>2 ? 0:endcap;
	lp.lbStyle=PS_SOLID;
	
	if(lmode==0||width<3){
		pen2=ExtCreatePen(ltype[i]|PS_GEOMETRIC|lep[j]|PS_JOIN_ROUND,width,&lp,0,NULL);
		oldpen=(HPEN)SelectObject(hdc,pen2);
		Polyline(hdc,pt,num); 
		SelectObject(hdc,oldpen);
		DeleteObject(pen2);
		return;
	}
	if(lmode==1){
		pen1=ExtCreatePen(PS_GEOMETRIC|PS_SOLID|lep[j]|PS_JOIN_ROUND,width,&lp,0,NULL);
		oldpen=(HPEN)SelectObject(hdc,pen1);
		Polyline(hdc,pt,num); 
		w=width-2;
		lp.lbColor=colorb;
		pen2=ExtCreatePen(PS_GEOMETRIC|ltype[i]|lep[j],w,&lp,0,NULL);
		SelectObject(hdc,pen2);
		Polyline(hdc,pt,num); 
		SelectObject(hdc,oldpen);
		DeleteObject(pen1);
		DeleteObject(pen2);
	}
};


DPOINT  GetPosition(DPOINT *pt,int npt,double min,double max,double value)
{
	DPOINT rpt,p1,p2;
	int i,n;
	double  m,pl,d,ps,pos[201],k;
	/*********特殊情况*************/
	if(min>=max) pt[0];
	if(value<min) return pt[0];
	if(value>max) return pt[npt-1];
	/*******************************************/
	n=npt>200 ? 200:npt;
	m=max-min;
	pl=(value-min)/m;  //计算位置比
	d=0;
	pos[0]=0;
	for(i=0;i<n-1;i++){  //计算距离
		d=(double)(d+GetLength(pt[i],pt[i+1]));
		pos[i+1]=d;
	}
	ps=d*pl;
	for(i=0;i<n;i++){  //查找落点
		if(ps>=pos[i]&&ps<=pos[i+1]) break;	
	}
	p1=pt[i];
	p2=pt[i+1];
	d=pos[i+1]-pos[i];
	k=ps-pos[i];
	pl=k/d;
	rpt.x=(int)(p1.x+pl*(p2.x-p1.x));
	rpt.y=(int)(p1.y+pl*(p2.y-p1.y));
	return rpt;
}



//画任意单线箭头
void BDrawDIRSingle(HDC hdc,POINT ps,POINT pe,DWORD color,int width)
{ 
	double len,xl,yl,w,h,a,b;
	DPOINT  p1,p2,p0;
	POINT   pi[4];
	w=pe.x-ps.x;
	h=pe.y-ps.y;
	len=sqrt(w*w+h*h);
	if(len==0) return;
	a=asin(h/len); //计算角度
	xl=w/len;
	yl=h/len;
	b=width*2;
	b=len-b;
	GLLine(hdc,ps.x,ps.y,pe.x,pe.y,color,1);
	if(b<0) return ;
	if(pe.x>=ps.x){
		p1.x=width*sin(a);  p1.y=-width*cos(a);
		p2.x=-width*sin(a); p2.y=width*cos(a);
	}else{
		p1.x=width*sin(a);  p1.y=width*cos(a);
		p2.x=-width*sin(a); p2.y=-width*cos(a);
	};
	p0.x=ps.x+xl*b;p0.y=ps.y+yl*b;
	pi[0].x=(int)(p0.x+p1.x);pi[0].y=(int)(p0.y+p1.y);
	pi[1].x=(int)(p0.x+p2.x);pi[1].y=(int)(p0.y+p2.y);
	pi[2]=pe;
	pi[3]=pi[0];
	GLPolygonc(hdc,pi,4,color,color,0);
};

//画任意单线箭头
void BDrawDIRSingle(CDIB&mdc,POINT ps,POINT pe,DWORD color,int width)
{ 
	/*double len,xl,yl,w,h,a,b;
	DPOINT  p1,p2,p0;
	POINT   pi[4];
	w=pe.x-ps.x;
	h=pe.y-ps.y;
	len=sqrt(w*w+h*h);
	if(len==0) return;
	a=asin(h/len); //计算角度
	xl=w/len;
	yl=h/len;
	b=width*2;
	b=len-b;
	mdc.CLine(ps,pe,color,1);
	if(b<0) return ;
	if(pe.x>=ps.x){
		p1.x=width*sin(a);  p1.y=-width*cos(a);
		p2.x=-width*sin(a); p2.y=width*cos(a);
	}else{
		p1.x=width*sin(a);  p1.y=width*cos(a);
		p2.x=-width*sin(a); p2.y=-width*cos(a);
	};
	p0.x=ps.x+xl*b;p0.y=ps.y+yl*b;
	pi[0].x=(int)(p0.x+p1.x);pi[0].y=(int)(p0.y+p1.y);
	pi[1].x=(int)(p0.x+p2.x);pi[1].y=(int)(p0.y+p2.y);
	pi[2]=pe;
	pi[3]=pi[0];
	FillDbx(mdc.m_hDC,pi,4,color);
	mdc.CDrawDbx(pi,4,1,color);*/
};



//画潮流线(箭头方式)
void DrawFlow(CDIB&mdc,POINT *pt,int ptsum,int start,int arrow,int size,int dis,DWORD color1,DWORD color2)
{
	int i,j,k,m,n,s;
	double len,xl,yl,w,h,x,y,a;
	DPOINT  p1,p2;
	DPOINT  lpt[4];
	POINT   pi[4];
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
          x=pt[i].x+xl*(j);
		  y=pt[i].y+yl*(j);
		  lpt[0].x=x+p1.x;lpt[0].y=y+p1.y;
		  lpt[1].x=x+p2.x;lpt[1].y=y+p2.y;
		  m=j+arrow*2*size;
		  lpt[2].x=pt[i].x+xl*m;lpt[2].y=pt[i].y+yl*m;
		  lpt[3]=lpt[0];
		  for(k=0;k<4;k++){
			  pi[k].x=(int)lpt[k].x;
			  pi[k].y=(int)lpt[k].y;
		  }
		  FillDbx(mdc.m_hDC,pi,4,color2);
		  mdc.CDrawDbx(pi,4,color1);
		}
		s=j-n;
	}
}



//画潮流线(箭头方式)
void DrawFlow(HDC hdc,POINT *pt,int ptsum,int start,int arrow,int size,int dis,DWORD color1,DWORD color2)
{
	int i,j,k,m,n,s;
	double len,xl,yl,w,h,x,y,a;
	DPOINT  p1,p2;
	DPOINT  lpt[4];
	POINT   pi[4];
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
          x=pt[i].x+xl*(j);
		  y=pt[i].y+yl*(j);
		  lpt[0].x=x+p1.x;lpt[0].y=y+p1.y;
		  lpt[1].x=x+p2.x;lpt[1].y=y+p2.y;
		  m=j+arrow*2*size;
		  lpt[2].x=pt[i].x+xl*m;lpt[2].y=pt[i].y+yl*m;
		  lpt[3]=lpt[0];
		  for(k=0;k<4;k++){
			  pi[k].x=(int)lpt[k].x;
			  pi[k].y=(int)lpt[k].y;
		  }
		  GLPolygonc(hdc,pi,4,color2,color2,0);
		  GLDrawDbx(hdc,4,pi,1,color1);
		}
		s=j-n;
	}
}


void FillDbx(HDC hdc,POINT *pt,int ptsum,int color)
{
	HRGN hgn;
	HBRUSH hb;
	hgn=CreatePolygonRgn(pt,ptsum,ALTERNATE);
	hb=CreateSolidBrush(color);
	FillRgn(hdc,hgn,hb);
	DeleteObject(hgn);
	DeleteObject(hb);
}

///////////////////////0605////////////////////////////////
//将一系列的点由原始点转换为实际屏幕点
void PointActToScr(DPOINT *inpt,DPOINT *outpt,int ptsum,int dx,int dy,double zoom)
{
	int i;
	for(i=0;i<ptsum;i++)
	{
		outpt[i].x=inpt[i].x*zoom+(double)dx;
		outpt[i].y=inpt[i].y*zoom+(double)dy;
	};
}

void PointActToScr(DPOINT *inpt,POINT *outpt,int ptsum,int dx,int dy,double zoom)
{
	int i;
	for(i=0;i<ptsum;i++)
	{
		outpt[i].x=(int)(inpt[i].x*zoom)+dx;
		outpt[i].y=(int)(inpt[i].y*zoom)+dy;
	};
}

//点偏移
void PointOffset(DPOINT *in,POINT *out,int n,int dx,int dy)
{
	int i;
	for(i=0;i<n;i++)
	{
		out[i].x=(int)in[i].x+dx;
		out[i].y=(int)in[i].y+dy;
	};
}
//点偏移
void PointOffset(DPOINT *in,DPOINT *out,int n,int dx,int dy)
{
	int i;
	for(i=0;i<n;i++)
	{
		out[i].x=in[i].x+dx;
		out[i].y=in[i].y+dy;
	};
}


void DrawPoly(HDC hdc,CPoint *pt,int ptsum,DWORD lcolor,DWORD fcolor,int fill,int close,int w)
{
	int n;
	if(ptsum<2) return;
	switch(fill)
	{
	case 0:
		if(close==1){
			n=ptsum+1;
			pt[ptsum]=pt[0];
		}else n=ptsum;
		GLDrawDbx(hdc,n,pt,w,lcolor);
		break;
	case 1:
	    NPolygonc(hdc,pt,ptsum,fcolor,lcolor);
		break;
	}
}


void DrawPoly(CDIB&mdc,CPoint *pt,int ptsum,DWORD lcolor,DWORD fcolor,int fill,int close)
{
	int n;
	HRGN hgn;
	HBRUSH hb;
	switch(fill){
	case 0:
		if(close==1){
			n=ptsum+1;
			pt[ptsum]=pt[0];
		}else n=ptsum;
		mdc.CDrawDbx(pt,n,lcolor);
		break;
	case 1:
	    hgn=CreatePolygonRgn(pt,ptsum,ALTERNATE);
		hb=CreateSolidBrush(fcolor);
		FillRgn(mdc.m_hDC,hgn,hb);
		DeleteObject(hgn);
		DeleteObject(hb);
		mdc.CDrawOutLine(pt,ptsum,lcolor);
		break;
	}
}


//绘制按钮
void BDrawButton(HDC hdc,CRect rt,char *text,LOGFONT *lf,int downup,int enable)
{
	CRect rt1;
	rt1=rt;
	//当无效按钮需要画时
	if(enable==0){
		DrawFrameControl(hdc,&rt1,DFC_BUTTON,DFCS_BUTTONPUSH|DFCS_MONO);
		GLDDrawText(hdc,&rt1,lf,text,0xffffff,0,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		rt1.OffsetRect(1,1);
		GLDDrawText(hdc,&rt1,lf,text,0x7f7f7f,0,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		return;
	}
	switch(downup){
	case 0:
		DrawFrameControl(hdc,&rt1,DFC_BUTTON,DFCS_BUTTONPUSH);
		GLDDrawText(hdc,&rt1,lf,text,0,0,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		break;
	case 1:
		DrawFrameControl(hdc,&rt1,DFC_BUTTON,DFCS_BUTTONPUSH|DFCS_PUSHED);
		rt1.OffsetRect(-1,-1);
		GLDDrawText(hdc,&rt1,lf,text,0,0,DT_VCENTER|DT_CENTER|DT_SINGLELINE);
		break;
	}
};


//返回百分饼图园上所有点(基于双精度）
int GetPctPieCirclePt(DPOINT *pt,CDRect &art,double pct,int flowover)
{
	double w,s,a;
	DPOINT cpt;
	a=pct>1 ? 1:pct;
	if(flowover==1&&pct>=0.8){
		cpt=art.CenterPoint();
		w=art.Width()/2;
		w=w<15 ? 15:w;
		s=w+(a-0.8)*50;
		art.left=cpt.x-s;
		art.top=cpt.y-s;
		art.right=cpt.x+s;
		art.bottom=cpt.y+s;
	}
	return GetCircleAllPt(pt,art);
}


/////////以下函数用于显示仪表指针//////////////
//类型1：箭头型
void ShowMPt1(HDC hdc,DPOINT cpt,double r,double angle,int axw,int pw,DWORD color)
{
	int i;
	CRect rt;
	double a;
	DPOINT dpt[10];
	POINT  pt[10];
	//构造点
	a=r*0.7;
	dpt[0].x=cpt.x+a;dpt[0].y=cpt.y-pw;
	dpt[1].x=cpt.x+a;dpt[1].y=cpt.y+pw;
	dpt[2].x=cpt.x+r;dpt[2].y=cpt.y;
	for(i=0;i<3;i++) BRotateObj(cpt,dpt[i],pt[i],angle);
	GLPolygonc(hdc,pt,3,color,color,0);
	pt[0].x=(int)cpt.x;pt[0].y=(int)cpt.y;
	dpt[1]=cpt;
	dpt[1].x+=a;
	BRotateObj(cpt,dpt[1],pt[1],angle);
	GLLine(hdc,pt[0].x,pt[0].y,pt[1].x,pt[1].y,color,1);
	
	rt.left=(int)(cpt.x-axw);rt.right=(int)(cpt.x+axw+1);
	rt.top=(int)(cpt.y-axw);rt.bottom=(int)(cpt.y+axw+1);
	GLEllipsec(hdc,rt,color,color,0);
}


void ShowMPt1(CDIB&mdc,DPOINT cpt,double r,double angle,double axw,double pw,DWORD color)
{
	int i;
	DRECT rt;
	double a;
	DPOINT dpt[10];
	DPOINT  pt[10];
	//构造点
	a=r*0.7;
	dpt[0].x=cpt.x+a;dpt[0].y=cpt.y-pw;
	dpt[1].x=cpt.x+a;dpt[1].y=cpt.y+pw;
	dpt[2].x=cpt.x+r;dpt[2].y=cpt.y;
	for(i=0;i<3;i++) BRotateObj(cpt,dpt[i],pt[i],angle);
	mdc.CDrawPoly(pt,3,color,color,1,1);
	pt[0].x=cpt.x;pt[0].y=cpt.y;
	dpt[1]=cpt;
	dpt[1].x+=a;
	BRotateObj(cpt,dpt[1],pt[1],angle);
	mdc.CDLine(pt[0],pt[1],color);
	rt.left=cpt.x-axw;rt.right=cpt.x+axw+1;
	rt.top=cpt.y-axw;rt.bottom=cpt.y+axw+1;
	mdc.CEllipsec(rt,color);
	mdc.CCircle(rt,color);
}

//类型2：箭头型
void ShowMPt2(HDC hdc,DPOINT cpt,double r,double angle,int axw,int pw,DWORD color)
{
	int i;
	CRect rt;
	DPOINT dpt[10];
	POINT  pt[10];
	//构造点
	dpt[0].x=cpt.x;dpt[0].y=cpt.y-pw;
	dpt[1].x=cpt.x;dpt[1].y=cpt.y+pw;
	dpt[2].x=cpt.x+r;dpt[2].y=cpt.y;
	for(i=0;i<3;i++) BRotateObj(cpt,dpt[i],pt[i],angle);
	GLPolygonc(hdc,pt,3,color,color,0);
	rt.left=(int)(cpt.x-axw);rt.right=(int)(cpt.x+axw+1);
	rt.top=(int)(cpt.y-axw);rt.bottom=(int)(cpt.y+axw+1);
	GLEllipsec(hdc,rt,color,color,0);
}

void ShowMPt2(CDIB&mdc,DPOINT cpt,double r,double angle,double axw,double pw,DWORD color)
{
	int i;
	DRECT rt;
	DPOINT dpt[10];
	DPOINT  pt[10];
	//构造点
	dpt[0].x=cpt.x;dpt[0].y=cpt.y-pw;
	dpt[1].x=cpt.x;dpt[1].y=cpt.y+pw;
	dpt[2].x=cpt.x+r;dpt[2].y=cpt.y;
	for(i=0;i<3;i++) BRotateObj(cpt,dpt[i],pt[i],angle);
	mdc.CDrawPoly(pt,3,color,color,1,1);
	rt.left=cpt.x-axw;rt.right=cpt.x+axw+1;
	rt.top=cpt.y-axw;rt.bottom=cpt.y+axw+1;
	mdc.CEllipsec(rt,color);
	mdc.CCircle(rt,color);
}

//类型3：大指针型
void ShowMPt3(HDC hdc,DPOINT cpt,double r,double angle,int axw,int pw,DWORD color)
{
	int i;
	double a;
	CRect rt;
	DPOINT dpt[10];
	POINT  pt[10];
	a=r/2;
	//构造点
	pt[0].x=(int)cpt.x;pt[0].y=(int)cpt.y;
	dpt[1].x=cpt.x+a;dpt[1].y=cpt.y-pw;
	dpt[2].x=cpt.x+r;dpt[2].y=cpt.y;
	dpt[3].x=cpt.x+a;dpt[3].y=cpt.y+pw;
	for(i=1;i<4;i++) BRotateObj(cpt,dpt[i],pt[i],angle);
	GLPolygonc(hdc,pt,4,color,color,0);
	rt.left=(int)(cpt.x-axw);rt.right=(int)(cpt.x+axw+1);
	rt.top=(int)(cpt.y-axw);rt.bottom=(int)(cpt.y+axw+1);
	GLEllipsec(hdc,rt,color,color,0);
}

void ShowMPt3(CDIB&mdc,DPOINT cpt,double r,double angle,double axw,double pw,DWORD color)
{
	int i;
	double a;
	DRECT rt;
	DPOINT dpt[10];
	DPOINT  pt[10];
	a=r/2;
	//构造点
	pt[0].x=(int)cpt.x;pt[0].y=(int)cpt.y;
	dpt[1].x=cpt.x+a;dpt[1].y=cpt.y-pw;
	dpt[2].x=cpt.x+r;dpt[2].y=cpt.y;
	dpt[3].x=cpt.x+a;dpt[3].y=cpt.y+pw;
	for(i=1;i<4;i++) BRotateObj(cpt,dpt[i],pt[i],angle);
	mdc.CDrawPoly(pt,4,color,color,1,1);
	rt.left=cpt.x-axw;rt.right=cpt.x+axw+1;
	rt.top=cpt.y-axw;rt.bottom=cpt.y+axw+1;
	mdc.CEllipsec(rt,color);
	mdc.CCircle(rt,color);
}

//类型3：半长短针型
void ShowMPt4(HDC hdc,DPOINT cpt,double r,double angle,int axw,int pw,DWORD color)
{
	int i;
	double a;
	CRect rt;
	DPOINT dpt[10];
	POINT  pt[10];
	a=r/2;
	//构造点
	dpt[0].x=cpt.x+a;dpt[0].y=cpt.y-pw;
	dpt[1].x=cpt.x+r;dpt[1].y=cpt.y;
	dpt[2].x=cpt.x+a;dpt[2].y=cpt.y+pw;
	for(i=0;i<3;i++) BRotateObj(cpt,dpt[i],pt[i],angle);
	GLPolygonc(hdc,pt,3,color,color,0);
}

void ShowMPt4(CDIB&mdc,DPOINT cpt,double r,double angle,double axw,double pw,DWORD color)
{
	int i;
	double a;
	CRect rt;
	DPOINT dpt[10];
	DPOINT  pt[10];
	a=r*2/3;
	//构造点
	dpt[0].x=cpt.x+a;dpt[0].y=cpt.y-pw;
	dpt[1].x=cpt.x+r;dpt[1].y=cpt.y;
	dpt[2].x=cpt.x+a;dpt[2].y=cpt.y+pw;
	for(i=0;i<3;i++) BRotateObj(cpt,dpt[i],pt[i],angle);
	mdc.CDrawPoly(pt,3,color,color,1,1);
}

void ShowMPt5(CDIB&mdc,DPOINT cpt,double r,double angle,double axw,double pw,DWORD color)
{
	double a;
	DRECT rt;
	DPOINT dpt;
	DPOINT  pt;
	a=r*4.0/5.0;
	//构造点
	dpt.x=cpt.x+a;dpt.y=cpt.y;
	BRotateObj(cpt,dpt,pt,angle);
	rt.left=pt.x-axw;rt.right=pt.x+axw+1;
	rt.top=pt.y-axw;rt.bottom=pt.y+axw+1;
	mdc.CEllipsec(rt,color);
}

void ShowMPt5(HDC hdc,DPOINT cpt,double r,double angle,int axw,int pw,DWORD color)
{
	double a;
	CRect rt;
	DPOINT dpt;
	DPOINT  pt;
	a=r*4.0/5.0;
	//构造点
	dpt.x=cpt.x+a;dpt.y=cpt.y;
	BRotateObj(cpt,dpt,pt,angle);
	rt.left=(int)(pt.x-axw);rt.right=(int)(pt.x+axw+1);
	rt.top=(int)(pt.y-axw);rt.bottom=(int)(pt.y+axw+1);
	GLEllipsec(hdc,rt,color,color,0);
}

//刻度显示
void ShowKd1(CDIB&mdc,DPOINT pt1,DPOINT pt2,DWORD color)
{
	DPOINT pt;
	CRect rt;
	double dis;
	pt.x=(pt1.x+pt2.x)/2.0;
	pt.y=(pt1.y+pt2.y)/2.0;
	dis=GetLength(pt1,pt2)/2;
	rt.left=(int)(pt.x-dis);rt.right=(int)(pt.x+dis+1);
	rt.top=(int)(pt.y-dis);rt.bottom=(int)(pt.y+dis+1);
	mdc.CEllipsec(rt,color);
}

//刻度显示
void ShowKd1(HDC hdc,POINT pt1,POINT pt2,DWORD color)
{
	POINT pt;
	CRect rt;
	int dis;
	pt.x=(pt1.x+pt2.x)/2;
	pt.y=(pt1.y+pt2.y)/2;
	dis=GetDistance(pt1,pt2)/2;
	rt.left=pt.x-dis;rt.right=pt.x+dis+1;
	rt.top=pt.y-dis;rt.bottom=pt.y+dis+1;
	GLEllipsec(hdc,rt,color,color,0);
}



//移动时考虑其他点的移动
void ChangeMoveDot(DPOINT *pt,int ptsum,int k,int kxy)
{
	int ks;
	ks=GetKeyState(VK_LSHIFT);
	if(ks>=0) return;
	switch(kxy)
	{
	case 0: //水平
		if(k>0)//操作前面一点
		{
			pt[k-1].y=pt[k].y;
		}
		if(k<ptsum-1) //操作后面一点
		{
			pt[k+1].y=pt[k].y;
		}
		break;
	case 1://垂直
		if(k>0)//操作前面一点
		{
			pt[k-1].x=pt[k].x;
		}
		if(k<ptsum-1) //操作后面一点
		{
			pt[k+1].x=pt[k].x;
		}
		break;
	}
}

///////////////////////////////////以下用于SVG名字转化//////////////////////////////////////
//CIM-〉SVG名字转换

bool SVGNameToCim(char *oldname,char *newname,int type,int &vl1,int &vl2,int &vl3)
{
	switch(type)
	{
	case 33:
		return CimBusName(oldname,newname,vl1);
	case 2:
		return CimSwitch(oldname,newname,vl1);
	case 34:case 35:
		return CimAcLine(oldname,newname,vl1);
	case 1:
		return CimGenerator(oldname,newname,vl1);
	case 7:case 8:
		return Cimtransformer(oldname,newname);
	case 4:case 5:
		return CimConpensator(oldname,newname);
	}
	return false;
}

bool SVGAnlNameToCim(char *oldname,char *newname,int type)
{
	int vl1;
	switch(type)
	{
	case 3:
		return CimBusName(oldname,newname,vl1);
	case 1:case 2:
		return CimAcLine(oldname,newname,vl1);
	case 0:
		return CimGenerator(oldname,newname,vl1);
	case 5:case 6:
		return Cimtransformer(oldname,newname);
	case 4:
		return CimLoadName(oldname,newname);
	case 7:case 8:
		return CimConpensator(oldname,newname);
	}
	return false;
}

extern char *DEVTYPEKEY[];
extern int DEVNUM[];
//获取信号设备类型
int GetMsgType(char *msgname)
{
	int i;
	for(i=0;i<7;i++)
	{
		if(strstr(msgname,DEVTYPEKEY[i])!=NULL) return DEVNUM[i];
	}
	return -1;
}

extern char *DEVXSTYPE[];
//获取信号显示类型
int GetXsType(char *xsname)
{
	int i,j;
	j=-1;
	for(i=0;i<6;i++)
	{
		if(strstr(xsname,DEVXSTYPE[i])!=NULL)
		{
			return i;
		}
	}
	return -1;
}

//将SVG的量点类型转换为本系统
int SvgAnlTypeToXs(int type,int xstype)
{
	int j=0;
	switch(type)
	{
	case 0:  //发电机
		switch(xstype)
		{
		case 0:case 2: //有功
			j=1;
			break;
		case 1:case 3: //无功
			j=2;
			break;
		}
		break;
	case 1:  //线路
		switch(xstype)
		{
		case 0:case 2: //有功
			j=3;
			break;
		case 1:case 3: //无功
			j=4;
			break;
		}
		break;	
	case 3:  //母线
		switch(xstype)
		{
		case 4:case 5: //电压
			j=2;
			break;
		}
		break;	
	case 4:  //负荷
		switch(xstype)
		{
		case 0:case 2: //有功
			j=1;
			break;
		case 1:case 3: //无功
			j=2;
			break;
		}
		break;	
	case 6:  //变压器
		j=0;
		break;	
	case 7:  //电容器，电抗器
		j=0;
		break;
	}
	return j;
}