// bclass.cpp: implementation of the APoint class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "bclass.h"
#include "math.h"
#include "jhsyslibl.h"
#include "gdata.h"
#include "dobj.h"
#include "middll.h"
#include "comobj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern comobj cobj;
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
//模拟量显示的调整矩形


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

CRect CreateCRt(int ptsum,POINT *pt)
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


//用于选择线段交叉而生成区域
HRGN SCreateLineRGN(POINT *pt,int ptsum)
{
	int i,k;
	HRGN h1,h2;
	if(ptsum<2) return NULL;
	for(i=0;i<ptsum-1;i++)
	{
		h1=BCreateLineRGN1(pt[i],pt[i+1],2);
		if(h1!=NULL) break;
	}
	k=i+1;	
	for(i=k;i<ptsum-1;i++){
		h2=BCreateLineRGN1(pt[i],pt[i+1],2);
		CombineRgn(h1,h1,h2,RGN_OR);
		DeleteObject(h2);
	}
	return h1;
}


float GetSingleVal(READDEV&data,int xsmode)
{
	int i=-1;
	switch(data.dtype)
	{
	case 0:  //发电机
		switch(xsmode)
		{
		case 0:case 1:
			i=xsmode;
			break;
		case 2:
			i=4;
			break;
		};
		break;
	case 1:  //交流线路
		i=xsmode;
		break;
	case 2:  //直流线路
		switch(xsmode){
		case 0://始端
			i=0;
			break;
		case 1://末端
			i=2;
			break;
		}
		break;
	case 3:  //母线
		switch(xsmode)
		{
		case 0:
			i=7;
			break;
		case 1:case 2:
			i=xsmode;
			break;
		}
		break;
	case 4:  //负荷
		i=xsmode;
		break;
	case 5:  //二绕变
		switch(xsmode)
		{
		case 0: i=0;break;
		case 1: i=2;break;
		}
		break;
	case 6: //三绕变
		switch(xsmode)
		{
		case 0:case 1:case 2: i=xsmode;break;
		case 3: i=4;break;
		}
		break;
	case 7://电容器
	case 8://电抗器
	case 9://SVC
		i=0;
		break;
	case 10://区域
		i=xsmode;
		break;
	case 11://系统
		switch(xsmode)
		{
		case 0:case 1: i=xsmode+1; break;
		case 2:case 3: i=xsmode+21;break;
		}
		break;
	case 13:  //断面
		i=xsmode;
		break;
	}
	if(i>=0&&i<16)	return data.value[i];
	return 0;
}


 
//将一系列的点由原始点转换为实际屏幕点
void PointActToScr(DPOINT *inpt,DPOINT *outpt,int ptsum,double curzoom)
{
	int i;
	for(i=0;i<ptsum;i++)
	{
		outpt[i].x=inpt[i].x*curzoom;
		outpt[i].y=inpt[i].y*curzoom;
	};
}

//将一系列的点由原始点转换为实际屏幕点
void PointActToScr(DPOINT *inpt,POINT *outpt,int ptsum,double curzoom)
{
	int i;
	for(i=0;i<ptsum;i++)
	{
		outpt[i].x=(int)(inpt[i].x*curzoom);
		outpt[i].y=(int)(inpt[i].y*curzoom);
	};
}



void DrawPoly(HDC hdc,CPoint *pt,int ptsum,DWORD lcolor,DWORD fcolor,int fill,int close,int w)
{
	int n;
	if(ptsum<2) return;
	switch(fill){
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

//返回百分比(双精度)
double GetPercent(double curval,double maxv)
{
	double a,b;
	if(maxv<=0) return 0;	
	a=curval/maxv;
	b=a<0 ? -a:a;
	return b;
}

//返回百分饼图颜色
DWORD GetPctPieColor(DWORD color,double pct)
{
	double gl,c;
	BYTE g;
	if(pct<0.8) return color;
	gl=(double)(-127)/0.2;
	c=pct-0.8;
	g=(BYTE)(127+gl*c);
	return RGB(255,g,0);
}
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


//返回一个视野中的半圆
void GetHalfCircle(int &s,DPOINT *inpt,DPOINT *outpt)
{
	int i,j,lp,dp;
	lp=0;
	//寻找最左边点
	for(i=0;i<72;i++)	if(inpt[i].x<inpt[lp].x) lp=i;
	for(i=0;i<36;i++)
	{
		j=i+lp;
		if(j>=72) j-=72;
		outpt[i]=inpt[j];
	}
	//找到最底下点
	dp=0;
	for(i=0;i<36;i++)	if(outpt[i].y>outpt[dp].y) dp=i;	
	s=dp;
}





void GetHalfCircle(DPOINT *inpt,DPOINT *npt)
{
	int i,j,lp;
	lp=0;
	for(i=0;i<73;i++)	if(inpt[i].x<inpt[lp].x) lp=i;
	for(i=0;i<36;i++)
	{
		j=i+lp;
		if(j>=73) j-=73;
		npt[i]=inpt[j];
	}
}




//设置启动旋转
//angle=角度
//cx,cy为旋转中心点
void StartRatate(HDC hdc,double angle,float cx,float cy)
{
	XFORM xf;
	double a,b;
	a=cos(angle);
	b=sin(angle);
	xf.eM11=(float)a;
	xf.eM12=(float)b;
	xf.eM21=(float)-b;
	xf.eM22=(float)a; 
	xf.eDx=cx;
	xf.eDy=cy;
	SetGraphicsMode(hdc, GM_ADVANCED);
	SetWorldTransform(hdc,&xf);
	SetBkMode(hdc,TRANSPARENT);
}

//设置倾斜:相当于和StartRatate相乘
//angle=角度
void SetIncline(HDC hdc,double angle)
{
	XFORM xf;
	xf.eM11=1;
	xf.eM12=0;
	xf.eM21=(float)tan(angle);
	xf.eM22=1;
	xf.eDx=0;
	xf.eDy=0;
	ModifyWorldTransform(hdc,&xf,MWT_LEFTMULTIPLY);
}


//返回一个棒从底部到顶部的区域
/*HRGN Get3dTaperRGN(CDRect rt,int h1)
{
	HRGN rgn1,rgn2;
	int i,j,n,r,l;
	DPOINT p1[74],p2,p3[74];
	POINT  p4[74];
	rt.left--;
	rt.top--;
	rt.right++; 
	rt.bottom++;
	n=GetCircleAllPt(p1,rt);
	if(n==0) return NULL;
	p2=rt.CenterPoint();
	//先计算两个园的位置
	DPtToScrPt(p1,p1,n,0,0,h1);
	DPtToScrPt(&p2,&p2,1,0,0,0);
	GetLeftRight(p1,n,r,l,p2);
	j=0;
	if(r>l){
		for(i=l;i<=r;i++)
		{
			p3[j]=p1[i];
			j++;
		}
	}else{
		for(i=l;i<n;i++)
		{
			p3[j]=p1[i];
			j++;
		}
		for(i=0;i<=r;i++)
		{
			p3[j]=p1[i];
			j++;
		}
	}
	p3[j]=p2;
	j++;

	for(i=0;i<j;i++)
	{
		p4[i].x=(int)p3[i].x+1;
		p4[i].y=(int)p3[i].y+1;
	}
	rgn1=CreatePolygonRgn(p4,j,ALTERNATE);
	for(i=0;i<n;i++)
	{
		p4[i].x=(int)p1[i].x+1;
		p4[i].y=(int)p1[i].y+1;
	}
	rgn2=CreatePolygonRgn(p4,n,ALTERNATE);
	CombineRgn(rgn1,rgn1,rgn2,RGN_OR);
	DeleteObject(rgn2); 
	rgn2=CreatePolygonRgn(p4,4,ALTERNATE);
	CombineRgn(rgn1,rgn1,rgn2,RGN_OR);
	DeleteObject(rgn2);
	return rgn1;
}
*/
//返回一个棒从底部到顶部的区域
/*HRGN Get3dTaperuRGN(CDRect rt,int h1)
{
	HRGN rgn1,rgn2;
	int i,j,n,r,l;
	DPOINT p1[74],p2,p3[74];
	POINT  p4[74];
	rt.left--;
	rt.top--;
	rt.right++; 
	rt.bottom++;
	n=GetCircleAllPt(p1,rt);
	if(n==0) return NULL;
	p2=rt.CenterPoint();
	//先计算两个园的位置
	DPtToScrPt(p1,p1,n,0,0,0);
	DPtToScrPt(&p2,&p2,1,0,0,h1);
	GetLeftRight(p1,n,l,r,p2);
	j=0;
	if(r>l){
		for(i=l;i<=r;i++)
		{
			p3[j]=p1[i];
			j++;
		}
	}else{
		for(i=l;i<n;i++)
		{
			p3[j]=p1[i];
			j++;
		}
		for(i=0;i<=r;i++)
		{
			p3[j]=p1[i];
			j++;
		}
	}
	p3[j]=p2;
	j++;

	for(i=0;i<j;i++)
	{
		p4[i].x=(int)p3[i].x+1;
		p4[i].y=(int)p3[i].y+1;
	}
	rgn1=CreatePolygonRgn(p4,j,ALTERNATE);
	for(i=0;i<n;i++)
	{
		p4[i].x=(int)p1[i].x+1;
		p4[i].y=(int)p1[i].y+1;
	}
	rgn2=CreatePolygonRgn(p4,n,ALTERNATE);
	CombineRgn(rgn1,rgn1,rgn2,RGN_OR);
	DeleteObject(rgn2); 
	rgn2=CreatePolygonRgn(p4,4,ALTERNATE);
	CombineRgn(rgn1,rgn1,rgn2,RGN_OR);
	DeleteObject(rgn2);
	return rgn1;
}
*/
//返回一个棒从底部到顶部的区域
/*HRGN Get3dBarRGN(CDRect rt,int h1)
{
	HRGN rgn1,rgn2;
	double a,xd,yd;
	int i,n,r,l;
	DPOINT p1[74],p2[74];
	POINT  p3[74],p4[9];
	rt.left--;
	rt.top--;
	rt.right++;
	rt.bottom++;
	n=GetCircleAllPt(p1,rt);
	if(n==0) return NULL;
	memcpy(p2,p1,sizeof(DPOINT)*n);
	//先计算两个园的位置
	DPtToScrPt(p1,p1,n,0,0,0);
	DPtToScrPt(p2,p2,n,0,0,h1);

	//计算斜度
	xd=p1[0].x-p2[0].x;
	yd=p1[0].y-p2[0].y;
	if(yd==0) a=0;
	else a=xd/yd;

	GetLeftRight(p1,n,r,l,a);
	for(i=0;i<n;i++)
	{
		p3[i].x=(int)p1[i].x+1;
		p3[i].y=(int)p1[i].y+1;
	}
	p4[0]=p3[l];
	p4[1]=p3[r];
	rgn1=CreatePolygonRgn(p3,n,ALTERNATE);
	for(i=0;i<n;i++)
	{
		p3[i].x=(int)p2[i].x+1;
		p3[i].y=(int)p2[i].y+1;
	}
	p4[2]=p3[r];
	p4[3]=p3[l]; 
	rgn2=CreatePolygonRgn(p3,n,ALTERNATE);
	CombineRgn(rgn1,rgn1,rgn2,RGN_OR);
	DeleteObject(rgn2); 
	rgn2=CreatePolygonRgn(p4,4,ALTERNATE);
	CombineRgn(rgn1,rgn1,rgn2,RGN_OR);
	DeleteObject(rgn2);
	return rgn1;
}
*/
void PtOffset(POINT *pt,int n,int dx,int dy)
{
	int i;
	for(i=0;i<n;i++)
	{
		pt[i].x+=dx;
		pt[i].y+=dy;
	}
}

void PtOffset(DPOINT *in,POINT *out,int n,int dx,int dy)
{
	int i;
	for(i=0;i<n;i++)
	{
		out[i].x=(int)in[i].x+dx;
		out[i].y=(int)in[i].y+dy;
	}
}

//专门用于传输线
HRGN BCreateLineRGN1(POINT ps, POINT pe,double width)
{
	double len,xl,yl,w,h,a,b;
	int w1;
	DPOINT  p1,p2;
	DPOINT  lpt[2];
	POINT   pi[5];
	CRect   rt;
	w=pe.x-ps.x;
	h=pe.y-ps.y;
	w1=(int)width;
	if(w==0){ //垂直的情况
		if(ps.y<pe.y){
			rt.left=ps.x-w1;
			rt.top=ps.y-w1*2;
			rt.right=ps.x+w1+1;
			rt.bottom=pe.y+w1*2;
			return CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
		}else{
			rt.left=pe.x-w1;
			rt.top=pe.y-w1*2;
			rt.right=pe.x+w1+1;
			rt.bottom=ps.y+w1*2;
			return CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
		}
	}
	if(h==0){  //水平的情况
		if(ps.x<pe.x){
			rt.left=ps.x-w1*2;
			rt.top=ps.y-w1;
			rt.right=pe.x+w1*2;
			rt.bottom=ps.y+w1+1;
			return CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
		}else{
			rt.left=pe.x-w1*2;
			rt.top=pe.y-w1;
			rt.right=ps.x+w1*2;
			rt.bottom=pe.y+w1+1;
			return CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
		}
	}
	//以下为斜线的情况
	len=sqrt(w*w+h*h);
	if(len==0) return NULL;
	a=asin(h/len); //计算角度
	xl=w/len;
	yl=h/len;
	w=width+1;
	b=width*3;
	if(pe.x>=ps.x){
		p1.x=w*sin(a);  p1.y=-w*cos(a);
		p2.x=-w*sin(a); p2.y=w*cos(a);
	}else{
		p1.x=w*sin(a);  p1.y=w*cos(a);
		p2.x=-w*sin(a); p2.y=-w*cos(a);
	};
	lpt[0].x=ps.x+xl*(-b);lpt[0].y=ps.y+yl*(-b);
	lpt[1].x=ps.x+xl*(len+b);lpt[1].y=ps.y+yl*(len+b);

	pi[0].x=(int)(lpt[0].x+p1.x);pi[0].y=(int)(lpt[0].y+p1.y);
	pi[1].x=(int)(lpt[0].x+p2.x);pi[1].y=(int)(lpt[0].y+p2.y);
	pi[2].x=(int)(lpt[1].x+p2.x);pi[2].y=(int)(lpt[1].y+p2.y);
	pi[3].x=(int)(lpt[1].x+p1.x);pi[3].y=(int)(lpt[1].y+p1.y);
	pi[4]=pi[0];
	return CreatePolygonRgn(pi,5,WINDING);
}


//返回一个多段线的长度
int GetLineLength(DPOINT *pt,int n)
{
	int i;
	double w;
	w=0;
	for(i=0;i<n-1;i++) w=w+GetLength(pt[i],pt[i+1]);
	return (int)w+1;
}

void BRotateObj(DPOINT  cpt,DPOINT &inpt,DPOINT &outpt,double angle)
{
	double r,x1,y1,dx,dy,a;
	dx=cpt.x-inpt.x;
	dy=cpt.y-inpt.y;
	r=sqrt((double)(dx*dx+dy*dy));
	a=(double)(180*asin(dy/r)/3.1425926);
	if(dx>0&&dy>0) a=(double)(180-a);
	if(dx>0&&dy<0) a=(double)(-180-a);
	if(a<0) a=(double)(360+a);
	a=(double)(a+angle);
	x1=(double)(r*cos(a*3.1415926/180));
	y1=(double)(r*sin(a*3.1415926/180));
	outpt.x=(double)(cpt.x+x1);
	outpt.y=(double)(cpt.y-y1);
}
void BRotateObj(DPOINT  cpt,DPOINT &inpt,POINT &outpt,double angle)
{
	double r,x1,y1,dx,dy,a;
	dx=cpt.x-inpt.x;
	dy=cpt.y-inpt.y;
	r=sqrt((double)(dx*dx+dy*dy));
	a=(double)(180*asin(dy/r)/3.1425926);
	if(dx>0&&dy>0) a=(double)(180-a);
	if(dx>0&&dy<0) a=(double)(-180-a);
	if(a<0) a=(double)(360+a);
	a=(double)(a+angle);
	x1=(double)(r*cos(a*3.1415926/180));
	y1=(double)(r*sin(a*3.1415926/180));
	outpt.x=(int)(cpt.x+x1);
	outpt.y=(int)(cpt.y-y1);
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
	//GLPolygonc(hdc,pt,3,color,color,0);
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
	a=r/2;
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
	mdc.CCircle(rt,color);
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
	dis=GetLength(pt1,pt2)/2;
	rt.left=pt.x-dis;rt.right=pt.x+dis+1;
	rt.top=pt.y-dis;rt.bottom=pt.y+dis+1;
	GLEllipsec(hdc,rt,color,color,0);
}

void ComputActRect(RACTOBJ  &r_at)
{
	int w,h;
	if(r_at.pt==NULL||r_at.ptsum==0) return;
	DPOINT pt=GetPosition(r_at.pt,r_at.ptsum,r_at.minv,r_at.maxv,r_at.curval);
	r_at.oldrt=r_at.currt;
	w=r_at.picw/2;
	h=r_at.pich/2;
	r_at.currt=CDRect(pt.x-w,pt.y-h,pt.x+w,pt.y+h);
}


HRGN DY_GetActObjRgn(HRGN oldhrgn,RACTOBJ  *r_at,int atsum,int dx,int dy,double curzoom)
{
	bool b;
	int i;
	CRect rt;
	CDRect art;
	double n,q;
	HRGN hrgn1,hrgn2;
	hrgn1=oldhrgn;
	//看活动对象
	for(i=0;i<atsum;i++)
	{
		b=false;
		if(r_at[i].act->runmode==0)
		{
		  r_at[i].js++;
		  if(r_at[i].js>=r_at[i].act->speed)
		  {
		  	r_at[i].js=0;
			n=r_at[i].act->skip;
			n=n==0 ? 1:n;
			q=r_at[i].curval+n;
			if(q>r_at[i].maxv) q=r_at[i].minv;
			r_at[i].curval=q;
			b=true;
			ComputActRect(r_at[i]);
		  }
		}
		if(b)//如果有变化，就刷新
		{  
			art=r_at[i].oldrt;
			art.ActRtToScr(curzoom);
			art.Offset(dx,dy);
			art.GetRECT(rt);
			rt.left-=5;
			rt.top-=5;
			rt.bottom+=5;
			rt.right+=5;
			if(hrgn1==NULL) hrgn1=CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
			else
			{
					hrgn2=CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
					CombineRgn(hrgn1,hrgn1,hrgn2,RGN_OR);
					DeleteObject(hrgn2);
			}
		    art=r_at[i].currt;
			art.ActRtToScr(curzoom);
			art.Offset(dx,dy);
			art.GetRECT(rt);
			hrgn2=CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
			CombineRgn(hrgn1,hrgn1,hrgn2,RGN_OR);
			DeleteObject(hrgn2);
		}
	}
	return hrgn1;	
}


HRGN DY_GetScrtxtRgn(HRGN oldhrgn,RSCRTXT  *r_sc,int scsum,CRect srt,int dx,int dy,double curzoom)
{
	int i;
	CRect rt;
	CDRect art;
	HRGN hrgn1,hrgn2;
	hrgn1=oldhrgn;
	for(i=0;i<scsum;i++)
	  {
		if(r_sc[i].stx->direct>0)
		{
		 art=r_sc[i].rt;
		 art.ActRtToScr(curzoom);
		 art.Offset(dx,dy);
		 art.GetRECT(rt);
		 rt&=srt;
		 if(!rt.IsRectEmpty())
		 {
			 if(hrgn1==NULL) hrgn1=CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
			 else
			 {
					hrgn2=CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
					CombineRgn(hrgn1,hrgn1,hrgn2,RGN_OR);
					DeleteObject(hrgn2);
			 }
		 }
		}
	  }
	return hrgn1;
}


HRGN DY_GetYBRgn(HRGN oldhrgn,RMETER   *r_yb,int ybsum,CRect srt,int dx,int dy,double curzoom)
{
	int i;
	CRect rt;
	CDRect art;
	HRGN hrgn1,hrgn2;
	hrgn1=oldhrgn;
	for(i=0;i<ybsum;i++)
	{
		art=r_yb[i].rt;
		art.ActRtToScr(curzoom);
		art.Offset(dx,dy);
		art.GetRECT(rt);
		rt&=srt;
		if(!rt.IsRectEmpty())
		{
			 if(hrgn1==NULL) hrgn1=CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
			 else
			 {
					hrgn2=CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
					CombineRgn(hrgn1,hrgn1,hrgn2,RGN_OR);
					DeleteObject(hrgn2);
			 }
		}
	}
	return hrgn1;
}

HRGN DY_GetGifAmlRgn(HRGN oldhrgn,RAML  *r_am,int  amsum,CRect srt,int dx,int dy,double curzoom)
{
	int i;
	CRect rt;
	CDRect art;
	HRGN hrgn1,hrgn2;
	hrgn1=oldhrgn;
	for(i=0;i<amsum;i++)
	{
		art=r_am[i].rt;
		art.ActRtToScr(curzoom);
		art.Offset(dx,dy);
		art.GetRECT(rt);
		rt&=srt;
		if(!rt.IsRectEmpty())
		{
			if(hrgn1==NULL) hrgn1=CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
			else
			{
				hrgn2=CreateRectRgn(rt.left,rt.top,rt.right,rt.bottom);
				CombineRgn(hrgn1,hrgn1,hrgn2,RGN_OR);
				DeleteObject(hrgn2);
			}
		}
	 }
	return hrgn1;
}


HRGN DY_GetGenRgn(CDIB &mdc,HRGN oldhrgn,RREV  *r_rv,int rvsum,CRect srt,int dx,int dy,int gendyn,double curzoom)
{
	int i;
	CRect rt;
	DPOINT dpt[4];
	POINT  ipt[4];
	CDRect art;
	N_ELEGRPA *elg;
	HRGN hrgn1,hrgn2;
	hrgn1=oldhrgn;
	if(gendyn!=1) return hrgn1;
	rt=srt;
	rt.OffsetRect(-dx,-dy);
	for(i=0;i<rvsum;i++)
	{
		elg=(N_ELEGRPA *)r_rv[i].elg;
		if(elg->subtype!=1) continue;
		if(r_rv[i].bs->ObjIsInRect(rt))
		{
			PointActToScr(elg->pt,dpt,4,curzoom);
			mdc.DPtToScrPt(dpt,ipt,4,dx,dy);
			if(hrgn1==NULL) hrgn1=CreatePolygonRgn(ipt,4,ALTERNATE);
			else
			{
				hrgn2=CreatePolygonRgn(ipt,4,ALTERNATE);
				CombineRgn(hrgn1,hrgn1,hrgn2,RGN_OR);
				DeleteObject(hrgn2);
			}
		}
	}
	return hrgn1;
}


//潮流线动态移动箭头
void ComputFlowJs(RFLOW *r_fw,int fwsum,int showtype)
{
	int i;
	N_FLOW *flw;
	for(i=0;i<fwsum;i++)
	{
		flw=r_fw[i].flw;
		if(flw->vr.ele==0) continue;
		r_fw[i].ptime++;
		r_fw[i].qtime++;
		r_fw[i].itime++;
		//先察看有功
		if((showtype==1||showtype==3)&&r_fw[i].ptime>=flw->pv)
		{
			r_fw[i].ptime=0;
			if(flw->rf.pdir==0)
			{
				flw->rf.pjs+=1;
				if(flw->rf.pjs>=96)	flw->rf.pjs=0;
			}else{
				flw->rf.pjs-=1;
				if(flw->rf.pjs<=0)	flw->rf.pjs=95;
			}
		}
		if((showtype==2||showtype==3)&&r_fw[i].qtime>=flw->qv)
		{
			r_fw[i].qtime=0;
			if(flw->rf.qdir==0)
			{
				flw->rf.qjs+=1;
				if(flw->rf.qjs>96)  flw->rf.qjs=0;
			}else{
				flw->rf.qjs-=1;
				if(flw->rf.qjs<=0)  flw->rf.qjs=95;
			}
		}
		if((showtype==4)&&r_fw[i].itime>=flw->iv)
		{
			r_fw[i].itime=0;
			if(flw->rf.idir==0)
			{
				flw->rf.ijs+=1;
				if(flw->rf.ijs>96)  flw->rf.ijs=0;
			}else{
				flw->rf.ijs-=1;
				if(flw->rf.ijs<=0)  flw->rf.ijs=95;
			}
		}
	}
}
//发电机动态
void ComputGenJs(RREV  *r_rv,int rvsum)
{
	int i;
	N_ELEGRPA *elg;
	for(i=0;i<rvsum;i++)
	{
		if(r_rv[i].elg->type!=1) continue;
		elg=(N_ELEGRPA *)r_rv[i].elg;
		if(elg->vr.value[0]!=0)
		{
			elg->dydeg-=30;
			if(elg->dydeg<0) elg->dydeg=360+elg->dydeg;
		}
	}
}


void ComputGifAmlJs(RAML *r_am,int  amsum)
{
	int i,j;
	CGIFAnm *gfm;
	for(i=0;i<amsum;i++)
	{
		gfm=&r_am[i].gfaml;
		if(r_am[i].zt==0){
			gfm->curfrm=0;
			continue;
		}

		j=gfm->curfrm;
		gfm->frm[j].count-=5;
		if(gfm->frm[j].count<0)//显示动画
		{  
			gfm->last=j;
			gfm->curfrm++;
			if(gfm->curfrm>=gfm->frmsum) gfm->curfrm=0;
			gfm->frm[j].count=gfm->frm[j].delay;
		}
	}
}

void DRectTo4Dpt(DRECT *rt,DPOINT *pt)
{
	CDRect drt;
	drt.SetDRECT(rt[0]);
	if(drt.Width()<3)
	{
		drt.left-=5;
		drt.right+=5;
	};
	if(drt.Height()<3)
	{
		drt.top-=5;
		drt.bottom+=5;
	}
	pt[0].x=drt.left;pt[0].y=drt.top;
	pt[1].x=drt.right;pt[1].y=drt.top;
	pt[2].x=drt.right;pt[2].y=drt.bottom;
	pt[3].x=drt.left;pt[3].y=drt.bottom;
}

//计算在哪一段
int GetLineSeg(double *slen,double &ys,double dis,int n)
{
	int i;
	double l1,l2;
	l1=0;
	l2=0;
	for(i=0;i<n;i++)
	{
		l1+=slen[i];
		if(dis<l1){
			ys=dis-l2;
			return i;
		}
		l2+=slen[i];
	}
	ys=dis;
	return 0;
}

//计算n-1显示比例
void ComputeN1Zoom(N1BAR *r_n1, int n1sum,double &zm,int wy)
{
	int i;
	double maxv=0,a;
	for(i=0;i<n1sum;i++)
	{
		a=r_n1[i].vn1;
		a=a<0 ? -a:a;
		if(maxv<a) maxv=a;
	}
	if(maxv!=0)
	{
		zm=300/maxv;
	}else zm=1;
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//注册历史-潮流线
void His_RegistFlow(RFLOW *flw,int flwsum)
{
	int i,n;
	DWORD *id;
	if(flwsum<=0) return;
	id=new DWORD[flwsum];
	//先注册交流
	n=0;
	for(i=0;i<flwsum;i++)
	{
		if(flw[i].flw->type==0)
		{
			if(IsThisId(id,n,flw[i].flw->did)) continue;
			id[n]=flw[i].flw->did;
			n++;
		}
	}


	if(n>0) RegPlayData(id,n,7);
	//注册直流
	n=0;
	for(i=0;i<flwsum;i++)
	{
		if(flw[i].flw->type==1)
		{
			if(IsThisId(id,n,flw[i].flw->did)) continue;
			id[n]=flw[i].flw->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,9);

	delete id;
}
//注册母线
void His_RegistBus(RBUS *bs,int bsum)
{
	int i,n;
	DWORD *id;
	if(bsum<=0) return;
	id=new DWORD[bsum];
	n=0;
	//先注册交流
	for(i=0;i<bsum;i++)
	{
		if(IsThisId(id,n,bs[i].bus->did)) continue;
		id[n]=bs[i].bus->did;
		n++;
	}
	RegPlayData(id,n,6);
	delete id;
}
//注册状态量中的设备
void His_RegistDev(RSTA *st,int stsum)
{
	int i,n;
	DWORD *id;
	if(stsum<=0) return;
	id=new DWORD[stsum];
	//先注册pt
	n=0;
	for(i=0;i<stsum;i++)
	{
		if(st[i].elg->type==1&&st[i].elg->subtype==0)
		{
			if(IsThisId(id,n,st[i].elg->did)) continue;
			id[n]=st[i].elg->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,17);
	//注册发电机
	n=0;
	for(i=0;i<stsum;i++)
	{
		if(st[i].elg->type==1&&st[i].elg->subtype==1)
		{
			if(IsThisId(id,n,st[i].elg->did)) continue;
			id[n]=st[i].elg->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,0);
	//注册开关，刀闸
	n=0;
	for(i=0;i<stsum;i++)
	{
		if(st[i].elg->type==1&&st[i].elg->subtype==2)
		{
			if(IsThisId(id,n,st[i].elg->did)) continue;
			id[n]=st[i].elg->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,8);
	//注册负荷
	n=0;
	for(i=0;i<stsum;i++)
	{
		if(st[i].elg->type==1&&st[i].elg->subtype==3)
		{
			if(IsThisId(id,n,st[i].elg->did)) continue;
			id[n]=st[i].elg->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,1);
	//注册电容
	n=0;
	for(i=0;i<stsum;i++)
	{
		if(st[i].elg->type==1&&st[i].elg->subtype==4)
		{
			if(IsThisId(id,n,st[i].elg->did)) continue;
			id[n]=st[i].elg->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,2);
	//注册电抗
	n=0;
	for(i=0;i<stsum;i++)
	{
		if(st[i].elg->type==1&&st[i].elg->subtype==5)
		{
			if(IsThisId(id,n,st[i].elg->did)) continue;
			id[n]=st[i].elg->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,3);
	//注册接地
	n=0;
	for(i=0;i<stsum;i++)
	{
		if(st[i].elg->type==1&&st[i].elg->subtype==6)
		{
			if(IsThisId(id,n,st[i].elg->did)) continue;
			id[n]=st[i].elg->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,10);
	//注册两绕变
	n=0;
	for(i=0;i<stsum;i++)
	{
		if(st[i].elg->type==1&&st[i].elg->subtype==7)
		{
			if(IsThisId(id,n,st[i].elg->did)) continue;
			id[n]=st[i].elg->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,4);
	//注册三绕变
	n=0;
	for(i=0;i<stsum;i++)
	{
		if(st[i].elg->type==1&&st[i].elg->subtype==8)
		{
			if(IsThisId(id,n,st[i].elg->did)) continue;
			id[n]=st[i].elg->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,5);
	//注册SVC
	n=0;
	for(i=0;i<stsum;i++)
	{
		if(st[i].elg->type==1&&st[i].elg->subtype==9)
		{
			if(IsThisId(id,n,st[i].elg->did)) continue;
			id[n]=st[i].elg->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,13);
	//注册CVT
	n=0;
	for(i=0;i<stsum;i++)
	{
		if(st[i].elg->type==1&&st[i].elg->subtype==10)
		{
			if(IsThisId(id,n,st[i].elg->did)) continue;
			id[n]=st[i].elg->did;
			n++;
		}
	}
	if(n>0) RegPlayData(id,n,18);
	delete id;
}

bool IsThisId(DWORD *ida,int maxn,DWORD idb)
{
	int i;
	for(i=0;i<maxn;i++)
	{
		if(ida[i]==idb) return true;
	}
	return false;
}

//显示断面中间划线
void ShowDmDraw(HDC hdc,POINT *pt,int segsum,int *sdot)
{
	int i,n;
	n=0;
	for(i=0;i<segsum;i++)
	{
		GLDrawDbx(hdc,sdot[i],&pt[n],1,0xff);
		n+=sdot[i];
	}
}


//显示断面线
void DrawDmLine(CDIB&mdc,POINT *pt,int segsum,int *sdot)
{
	int i,n;
	n=0;
	for(i=0;i<segsum;i++)
	{
		mdc.CDrawDbx(&pt[n],sdot[i],0xff);
		n+=sdot[i];
		if(segsum>1&&i<segsum-1)
		{
			mdc.CSetLineStyle(1);
			mdc.CLine(pt[n],pt[n-1],0xff);
			mdc.CSetLineStyle(0);
		}
	}
}


//清除自符串中的回车键
void ClrStrEnter(char *str)
{
	int i,len;	
	len=strlen(str);
	for(i=0;i<len;i++){
	  if(str[i]==0xd||str[i]==0xa) str[i]=' '; 
	};
}

//返回自助控件的参数
void GetSflRunParam(SUBW_PARAM&pad,RSELFCTL&pas)
{
	pad.bottom=pas.stl->abottom;
	pad.left=pas.stl->aleft;
	pad.mode=pas.stl->mode;
	pad.right=pas.stl->aright;
	pad.top=pas.stl->atop;
	pad.rts=pas.rt;
	pas.rt.GetRECT(pad.rt);
	pas.rt.GetRECT(pad.rtw);
	pad.hwnd=pas.stl->hwnd;
}


/**************************************************************
执行功能模块
mstring的格式：库  函数名  int参数 串参数
函数标准：void funct(int param1,char *str)
funct必须是打开一个对话框或者立即执行完毕的函数
     不能为POPUP窗口
***************************************************************/
void RunFunctModule(char *mstring)
{
	char filename[256];
	char dllname[45]; //动态连接库名
	char fnm[45];	  //函数名	
	char pstr[45];	  //串参数
	int  pint;		  //int参数
	void (WINAPI*mfunct)(int param,char *str);    //模块函数
	pint=0;
	pstr[0]=0;
	dllname[0]=0;
	sscanf(mstring,"%s %s %d %s",dllname,fnm,&pint,pstr);
	if(strlen(dllname)<4)
	{
		MessageBox(0,"模块名错误！","错误",MB_ICONERROR|MB_OK);
		return;
	}
	cobj.SetToLocalFile(dllname,filename);

	HINSTANCE hinst=LoadLibrary(filename);
	if(hinst!=NULL){
	  (FARPROC&)mfunct=GetProcAddress(hinst,fnm);
	  if(mfunct!=NULL) mfunct(pint,pstr);
	   else MessageBox(0,"指定的函数不存在！","错误",MB_ICONERROR|MB_OK);
	  FreeLibrary(hinst);
	}else{
		MessageBox(0,"指定的模块不存在！","错误",MB_ICONERROR|MB_OK);
	}
}

void GetSoeStr(char *str,NSOES *soe,int   soesum,int order,char *name)		//当前SOE个数
{
	int i,ms,sta;
	CTime tm;
	char p[100];
	sprintf(str,"名称：%s/n动作情况：动作排序第%d个",name,order+1);
	for(i=0;i<soesum;i++)
	{
		if(i>3) break;
		tm=soe[i].tm;
		ms=soe[i].ms;
		sta=soe[i].sta;
		strcat(str,"\n");
		sprintf(p,"%02d:%02d:%02d %03d  %s",tm.GetHour(),tm.GetMinute(),tm.GetSecond(),ms,sta==0 ? "开":"合");
		strcat(str,p);
	}
}

//构造一个闪电多边形(6点结果)
void GetFlashDot(DPOINT *dpt,DPOINT cpt,double zoom)
{
	double wd,hd;
	wd=8*zoom;
	hd=25*zoom;
	dpt[0].x=cpt.x+wd+wd/2;		dpt[0].y=cpt.y-hd;
	dpt[1].x=cpt.x+wd/2.0;		dpt[1].y=cpt.y-hd/8.0;
	dpt[2].x=cpt.x-wd;			dpt[2].y=cpt.y-hd/8.0;
	dpt[3].x=cpt.x-wd-wd/2;		dpt[3].y=cpt.y+hd;
	dpt[4].x=cpt.x-wd/2;		dpt[4].y=cpt.y+hd/8.0;
	dpt[5].x=cpt.x+wd;			dpt[5].y=cpt.y+hd/8.0;
}


//计算相交线路
void ComputeSelBra(int &id,int &linetype,RFLOW *r_fw,int fwsum,POINT *pt,int ptsum,double czm)
{
	int i,j,n,rtn;
	CRect rt;
	POINT pt1[20],ptt;
	HRGN hrgn1,hrgn2;
	CDPoint apt;
	id=-1;
	hrgn1=SCreateLineRGN(pt,ptsum);
	hrgn2=NULL;
	for(i=0;i<fwsum;i++)
	{
		n=r_fw[i].ptsum;
		n=n>20 ? 20:n;
		for(j=0;j<n;j++)
		{
			pt1[j].x=(int)((double)(r_fw[i].flw->pt[j].x*czm));
			pt1[j].y=(int)((double)(r_fw[i].flw->pt[j].y*czm));
		}
		if(hrgn2!=NULL) DeleteObject(hrgn2);
		hrgn2=SCreateLineRGN(pt1,n);
		rtn=CombineRgn(hrgn2,hrgn1,hrgn2,RGN_AND);
		if(rtn!=NULLREGION){
			id=r_fw[i].flw->did;
			linetype=r_fw[i].flw->type;
			GetRgnBox(hrgn2,&rt);
			ptt=rt.CenterPoint();
			apt.x=(double)ptt.x;
			apt.y=(double)ptt.y;
			apt.ScrPtToAct(czm);
			break;
		}
	}
	if(hrgn1!=NULL) DeleteObject(hrgn1);	
	if(hrgn2!=NULL) DeleteObject(hrgn2);
}


int GetLstSource(char *str,int *ofset,int maxl)
{
	int n;
	char *lp1,*lp2;
	lp1=str;
	ofset[0]=0;
	n=0;
	for(;;)
	{
		if(n>=maxl) break;
		lp2=strstr(lp1,"===");
		if(lp2!=NULL){
			n++;
			lp2[0]=0;
			lp2+=3;
			lp1=lp2;
			ofset[n]=lp2-str;
		}else break;
	}
	return n;
}

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