// SvgOut.cpp: implementation of the SvgOut class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerPaint.h"
#include "SvgOut.h"
#include "math.h"
#include "comobj.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//转换为SVG中文对照表,总共19种
char *fontnm[]={"宋体","SimSun","黑体","Simhei","仿宋_GB2312","FangSong",
 "楷体_GB2312","KaiTi","幼圆","YouYuan","华文宋体","STSong",
 "华文中宋","STZhongsong","华文楷体","STKaiti","华文仿宋","STFangsong",
 "华文细黑","STXihei","华文隶书","STLiti","华文行楷","STXingkai",
 "华文新魏","STXinwei","华文琥珀","STHupo","华文彩云","STCaiyun",
 "方正姚体简体","FZYaoTi","方正舒体简体","FZShuTi","新宋体","NSimSun","隶书","LiSu",
 "楷体_GB2312","KaiTi"};   

extern char *wk[];
extern comobj  cobj;
extern char *lst_vl[];
//输出SVG格式的界面文件
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

SvgOut::SvgOut()
{
	fp=NULL;
	cpage=NULL;
}

SvgOut::~SvgOut()
{
	if(fp!=NULL) fclose(fp);
}

//打开一个文件用于写SVG格式的图形
bool SvgOut::OpenWFile(char *filename)
{
	fp=fopen(filename,"w+t");
	if(fp==NULL) return false;
	return true;
}

//关闭已打开的文件
void SvgOut::CloseFile()
{
	fprintf(fp,"%s\n","</svg>");
	if(fp!=NULL) fclose(fp);
	fp=NULL;
}

//写入SVG文件头
void SvgOut::WriteSvgHead()
{
	int n;
	char atrstr[256];
	BYTE title[256];

	BYTE flag[4];
	flag[0]=0xef;
	flag[1]=0xbb;
	flag[2]=0xbf;
	fwrite(flag,3,1,fp);
	fprintf(fp,"%s\n","<?xml version=\"1.0\" encoding=\"utf-8\"?>");
	fprintf(fp,"%s\n","<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.0//EN\" ");
	fprintf(fp,"%s\n","\"http://www.w3.org/TR/2001/REC-SVG-20010904/DTD/svg10.dtd\">");
	fprintf(fp,"%s\n","<!--Visual system By SICUAN UNIVERSITY  PowerGroup-->");
	fprintf(fp,"%s\n","<!--PowerSystem Graphics version=\"1.0\"-->");
	sprintf(atrstr,"attrib=\"%d\"",cpage->head.type);


	fprintf(fp,"<svg width=\"%d\" height=\"%d\" %s xmlns=\"http://www.w3.org/2000/svg\">\n",cpage->head.width,cpage->head.height,atrstr);
	
	n=ANSIToUtf8(cpage->head.Name,title,256);
	fprintf(fp,"\t<title>");
	fwrite(title,n,1,fp);	
	fprintf(fp,"</title>\n",cpage->head.Name);

	fprintf(fp,"\t<rect id=\"background\" x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\"",0,0,cpage->head.width,cpage->head.height);
	GStyleOut(1,cpage->head.BgColor,cpage->head.BgColor,1,0);
	fprintf(fp,"/>\n");
}


//将图形写入SVG文件
void SvgOut::DrawOnSvgFile()
{
	int i,j;
	N_LAYER  *lay;
	for(i=0;i<cpage->laysum;i++)
	{
		lay=&cpage->layer[i];
		for(j=0;j<lay->objnum;j++)
		{
			DrawObj(lay->obj[j]);
		}
	}
}


//画对象
void SvgOut::DrawObj(BASE0&bs)
{
	switch(bs.attr.type)
	{
	case 1: ShowDbx(bs);	break;
	case 2: ShowRect(bs);	break;
	case 3: ShowCircle(bs);	break;
	case 4: ShowHSin(bs);	break;
	case 5: ShowSin(bs);	break;
	case 6: ShowArc(bs);	break;
	case 7: ShowArrow(bs);	break;
	case 8: ShowGlass(bs);	break;
	case 10:ShowText(bs);	break;
	case 11:ShowEsite(bs);	break;
	case 12:ShowEgpMb(bs);	break;
	case 13:ShowCoordnate(bs);break;
	case 14:ShowTable(bs);  break;
	case 64:ShowAnalog(bs); break;
	case 66:ShowEleGrp(bs);	break;
	case 69:ShowBar(bs);	break;
	case 70:ShowPie(bs);	break;
	case 71:ShowDate(bs);	break;
	case 72:ShowTime(bs);	break;
	case 77:ShowFlow(bs);	break;
	case 78:ShowConline(bs);break;
	case 79:ShowBus(bs);	break;
	case 82:ShowPctPie(bs);	break;
	}
}


//组装组合图元
void SvgOut::DrawEleGrp(BASE0&bs,int gp)
{
	switch(bs.attr.type)
	{
	case 1: ShowDbx(bs,gp);		break;
	case 2: ShowRect(bs,gp);	break;
	case 3: ShowCircle(bs,gp);	break;
	case 4: ShowHSin(bs,gp);	break;
	case 5: ShowSin(bs,gp);		break;
	case 6: ShowArc(bs,gp);		break;
	case 7: ShowArrow(bs,gp);	break;
	case 8: ShowGlass(bs,gp);	break;
	case 10:ShowText(bs,gp);	break;
	case 11:ShowEsite(bs,1);	break;
	case 12:ShowEgpMb(bs,1);	break;
	}
}


//组装变压器
void SvgOut::EgpTran(BASE0 *bs,int id,int index,int sum)
{
	int i;
	int  sn[3],ss;
	sn[0]=0;
	sn[1]=0;
	sn[2]=0;
	ss=0;
	for(i=0;i<sum;i++)
	{
		if(bs[i].attr.belong>3) bs[i].attr.belong=0;
		switch(bs[i].attr.belong)
		{
		case 0:
			ss++;
			break;
		case 1:
			sn[0]++;
			break;
		case 2:
			sn[1]++;
			break;
		case 3:
			sn[2]++;
			break;
		}
	}
	//第一步:将未圈入的对象
	if(ss>0)
	{
		fprintf(fp,"\t<g id=\"egp_%d_%d_0\" >\n",id,index);
		for(i=0;i<sum;i++) 
		{
			if(bs[i].attr.belong==0) DrawEleGrp(bs[i],0);
		}
		fprintf(fp,"\t</g>\n");
	}
	//将第一圈的写入
	if(sn[0]>0)
	{
		fprintf(fp,"\t<g id=\"egp_%d_%d_1\" >\n",id,index);
		for(i=0;i<sum;i++) 
		{
			if(bs[i].attr.belong==1) DrawEleGrp(bs[i]);
		}
		fprintf(fp,"\t</g>\n");
	}

	if(sn[1]>0)
	{
		fprintf(fp,"\t<g id=\"egp_%d_%d_2\" >\n",id,index);
		for(i=0;i<sum;i++) 
		{
			if(bs[i].attr.belong==2) DrawEleGrp(bs[i]);
		}
		fprintf(fp,"\t</g>\n");
	}

	if(sn[2]>0)
	{
		fprintf(fp,"\t<g id=\"egp_%d_%d_3\" >\n",id,index);
		for(i=0;i<sum;i++) 
		{
			if(bs[i].attr.belong==3) DrawEleGrp(bs[i]);
		}
		fprintf(fp,"\t</g>\n");
	}
}



//定义组合图元
void SvgOut::DefineEleGrp()
{
	int i,j;
	char msg[256];
	if(egpsum<=0) return;
	fprintf(fp,"<defs>\n");
	///用/g定义组合图元////////////////////////////////////
	for(i=0;i<egpsum;i++)
	{
		//先输出0号图元
		sprintf(msg,"id=\"egp_%d_0\" type=\"%d\" subtype=\"%d\" site=\"%d\"",egp[i].id,egp[i].type,egp[i].subtype,egp[i].sitesum);
		fprintf(fp,"<g %s >\n",msg);
		if(egp[i].type==1&&(egp[i].subtype==7||egp[i].subtype==8)) //是变压器
		{
			EgpTran(egp[i].bs1,egp[i].id,0,egp[i].bsum1);
		}else{
			for(j=0;j<egp[i].bsum1;j++)
			{	
				DrawEleGrp(egp[i].bs1[j]);
			}
		}
		fprintf(fp,"</g>\n");
		//再输出1号图元
		sprintf(msg,"id=\"egp_%d_1\" type=\"%d\" subtype=\"%d\" site=\"%d\"",egp[i].id,egp[i].type,egp[i].subtype,egp[i].sitesum);
		fprintf(fp,"<g %s >\n",msg);
		if(egp[i].type==1&&(egp[i].subtype==7||egp[i].subtype==8)) //是变压器
		{
			EgpTran(egp[i].bs2,egp[i].id,1,egp[i].bsum2);
		}else{
			for(j=0;j<egp[i].bsum2;j++)
			{
				DrawEleGrp(egp[i].bs2[j]);
			}
		}
		fprintf(fp,"</g>\n");
	}
	//////////////////////////////////////////////////////
	fprintf(fp,"</defs>\n");
}



//填充语句输出
void SvgOut::GStyleOut(int fill,DWORD fcolor,DWORD lcolor,float lwidth,int gp)
{
	if(gp==0)
	{
		if(fill==0) fprintf(fp,"%s"," fill=\"none\" ");
		else fprintf(fp," fill=\"#%02x%02x%02x\" ",GetRValue(fcolor),GetGValue(fcolor),GetBValue(fcolor));
		fprintf(fp,"stroke=\"#%02x%02x%02x\" ",GetRValue(lcolor),GetGValue(lcolor),GetBValue(lcolor));
	}else
	{
		if(fill==0) fprintf(fp,"%s"," fill=\"none\" ");
		else fprintf(fp," fill=\"#%02x%02x%02x\" ",GetRValue(fcolor),GetGValue(fcolor),GetBValue(fcolor));
	}
	fprintf(fp," stroke-width=\"%2.2f\" ",lwidth);
}

//返回颜色串
void SvgOut::GetColorStr(char *str,DWORD color)
{
	sprintf(str,"#%02x%02x%02x",GetRValue(color),GetGValue(color),GetBValue(color));
}
//显示多边形
void SvgOut::ShowDbx(BASE0 &bs,int gp)
{
	int i,tpsum;
	float wd;
	CDRect rt;
	N_DBX *dbx;
	dbx=(N_DBX*)bs.buf;
	tpsum=dbx->ptsum;
	fprintf(fp,"%s","\t<polyline id=\"polyline\" points=\"");
	for(i=0;i<dbx->ptsum;i++)
	{
		fprintf(fp,"%2.2f,%2.2f ",dbx->pt[i].x,dbx->pt[i].y);
		if(i==(dbx->ptsum-1)){
			if(dbx->fill==1) fprintf(fp,"%2.2f,%2.2f ",dbx->pt[0].x,dbx->pt[0].y);
			fprintf(fp,"\"");
		}
		if(i>5&&(i%5==0)) fprintf(fp,"\n\t");
	}
	wd=(float)(dbx->width*2);
	wd=wd==0 ? 1:wd;

	fprintf(fp,"\n\t");
	GStyleOut(dbx->fill,dbx->bcolor1,dbx->lcolor,wd,gp);
	fprintf(fp,"/>\n");
}

//显示矩形
void SvgOut::ShowRect(BASE0 &bs,int gp)
{
	CDRect drt;
	N_RECT *rt1;
	rt1=(N_RECT*)bs.buf;
	drt=CreateNRt(4,rt1->pt);
	fprintf(fp,"\t<rect id=\"rect\" x=\"%2.2f\" y=\"%2.2f\" width=\"%2.2f\" height=\"%2.2f\"",drt.left,drt.top,drt.Width(),drt.Height());
	GStyleOut(rt1->fill,rt1->bcolor1,rt1->lcolor,1,gp);
	fprintf(fp,"/>\n");
}



//显示园
void SvgOut::ShowCircle(BASE0 &bs,int gp)
{
	DPOINT cpt;
	CDRect drt;
	double rx,ry;
	N_CIRCLE *cl;
	cl=(N_CIRCLE*)bs.buf;
	drt=CreateNRt(4,cl->pt);
	rx=drt.Width()/2;
	ry=drt.Height()/2;
	cpt=drt.CenterPoint();
	fprintf(fp,"\t<ellipse id=\"circle\" cx=\"%2.2f\" cy=\"%2.2f\" rx=\"%2.2f\" ry=\"%2.2f\" ",cpt.x,cpt.y,rx,ry);
	GStyleOut(cl->fill,cl->bcolor1,cl->lcolor,1,gp);
	fprintf(fp,"/>\n");
}

//显示半波形
void SvgOut::ShowHSin(BASE0 &bs,int gp)
{
	char cstr[16];
	char atrstr[256];
	int i,j,zq,zq1;
	CDRect drt;
	double xl,yl,x1,x2,x3,y1,y2,y3;
	N_HSIN *hs;
	hs=(N_HSIN*)bs.buf;
	drt=CreateNRt(4,hs->pt);
	zq=hs->pirodic;
	zq=zq<1 ? 1:zq;
	zq1=zq*2;
	zq=zq*4+1;
	GetColorStr(cstr,hs->color);
	sprintf(atrstr,"attrib=\"%2.2f,%2.2f,%2.2f,%2.2f,%s,%d,%d\"",drt.left,drt.top,drt.right,drt.bottom,cstr,hs->ltype,hs->pirodic);
	fprintf(fp,"\t<path id=\"hsin\" %s d=\"",atrstr);
	switch(hs->ltype)
	{
	case 0://水平方向
		xl=drt.Width()/(zq-1);
		y1=drt.bottom;
		y2=drt.top-drt.Height();
		for(i=0;i<zq1;i++)
		{	
			j=i*2;
			x1=drt.left+xl*j;
			x2=drt.left+xl*(j+1);
			x3=drt.left+xl*(j+2);
			fprintf(fp,"M%2.2f,%2.2f Q%2.2f,%2.2f %2.2f,%2.2f ",x1,y1,x2,y2,x3,y1);
		}
		fprintf(fp,"\"\n\t");
		break;
	case 1://垂直方向
		yl=drt.Height()/(zq-1);
		x1=drt.left;
		x2=drt.right+drt.Width();
		for(i=0;i<zq1;i++)
		{	
			j=i*2;
			y1=drt.top+yl*j;
			y2=drt.top+yl*(j+1);
			y3=drt.top+yl*(j+2);
			fprintf(fp,"M%2.2f,%2.2f Q%2.2f,%2.2f %2.2f,%2.2f ",x1,y1,x2,y2,x1,y3);
		}
		fprintf(fp,"\"\n\t");
		break;
	}
	GStyleOut(0,hs->bcolor,hs->color,1,gp);
	fprintf(fp,"/>\n");
}

//显示正弦波形
void SvgOut::ShowSin(BASE0 &bs,int gp)
{
	char cstr[16];
	char atrstr[256];
	int i,j,zq,zq1;
	CDRect drt;
	DPOINT cpt;
	double xl,yl,x1,x2,x3,x4,y1,y2,y3,y4;
	N_SIN *hs;
	hs=(N_SIN*)bs.buf;
	drt=CreateNRt(4,hs->pt);
	zq=hs->pirodic;
	zq=zq<1 ? 1:zq;
	zq1=zq;
	zq=zq*4+1;
	cpt=drt.CenterPoint();
	GetColorStr(cstr,hs->color);
	sprintf(atrstr,"attrib=\"%2.2f,%2.2f,%2.2f,%2.2f,%s,%d,%d\"",drt.left,drt.top,drt.right,drt.bottom,cstr,hs->ltype,hs->pirodic);
	fprintf(fp,"\t<path id=\"sin\" %s d=\"",atrstr);
	switch(hs->ltype)
	{
	case 0://水平方向
		xl=drt.Width()/(zq-1);
		y2=cpt.y-drt.Height();
		y1=cpt.y;
		for(i=0;i<zq1;i++)
		{	
			j=i*4;
			x1=drt.left+xl*j;
			x2=drt.left+xl*(j+1);
			x3=drt.left+xl*(j+2);
			x4=drt.left+xl*(j+4);
			fprintf(fp,"M%2.2f,%2.2f Q%2.2f,%2.2f %2.2f,%2.2f T%2.2f,%2.2f ",x1,y1,x2,y2,x3,y1,x4,y1);
		}
		fprintf(fp,"\"\n\t");
		break;
	case 1://垂直方向
		yl=drt.Height()/(zq-1);
		x2=cpt.x+drt.Width();
		x1=cpt.x;
		for(i=0;i<zq1;i++)
		{	
			j=i*4;
			y1=drt.top+yl*j;
			y2=drt.top+yl*(j+1);
			y3=drt.top+yl*(j+2);
			y4=drt.top+yl*(j+4);
			fprintf(fp,"M%2.2f,%2.2f Q%2.2f,%2.2f %2.2f,%2.2f T%2.2f,%2.2f ",x1,y1,x2,y2,x1,y3,x1,y4);
		}
		fprintf(fp,"\"\n\t");
		break;
	}
	GStyleOut(0,hs->color,hs->color,1,gp);
	fprintf(fp,"/>\n");
}


//显示园弧
void SvgOut::ShowArc(BASE0 &bs,int gp)
{
	char cstr[16];
	char atrstr[256];
	DPOINT cpt,pt1,pt2;
	CDRect drt;
	double rx,ry,xl,a;
	N_ARC *arc;
	arc=(N_ARC*)bs.buf;
	drt=CreateNRt(4,arc->pt);
	rx=drt.Width()/2;
	ry=drt.Height()/2;
	cpt=drt.CenterPoint();
	if(rx==0||ry==0) return;
	xl=rx/ry;
	a=arc->start*mpi/180;
	pt1.x=cpt.x+xl*ry*cos(a);
	pt1.y=cpt.y-ry*sin(a);
	a=arc->end*mpi/180;
	pt2.x=cpt.x+xl*ry*cos(a);
	pt2.y=cpt.y-ry*sin(a);
	GetColorStr(cstr,arc->color);
	sprintf(atrstr,"attrib=\"%2.2f,%2.2f,%2.2f,%2.2f,%s,%d,%d\"",drt.left,drt.top,drt.right,drt.bottom,cstr,arc->start,arc->end);
	fprintf(fp,"\t<path id=\"arc\" %s d=\"M%2.2f,%2.2f A%2.2f,%2.2f 0 0,0 %2.2f,%2.2f\" ",atrstr,pt1.x,pt1.y,rx,ry,pt2.x,pt2.y);
    GStyleOut(0,arc->color,arc->color,1,gp);
	fprintf(fp,"/>\n");
}

//显示箭头
void SvgOut::ShowArrow(BASE0 &bs,int gp)
{
	char cstr[16];
	char atrstr[256];
	int n;
	DPOINT pt[2],pt1[4];
	N_ARROW *arw;
	arw=(N_ARROW*)bs.buf;
	PointActToScr(arw->pt,pt,2,0,0,1);
	n=GetDirPoint(pt[0],pt[1],pt1,4);
	GetColorStr(cstr,arw->color);
	sprintf(atrstr,"attrib=\"%2.2f,%2.2f,%2.2f,%2.2f,%s\"",pt[0].x,pt[0].y,pt[1].x,pt[1].y,cstr);

	fprintf(fp,"\t<g id=\"arrow\" %s>\n",atrstr);
	fprintf(fp,"\t\t<line x1=\"%2.2f\" y1=\"%2.2f\" x2=\"%2.2f\" y2=\"%2.2f\" ",pt[0].x,pt[0].y,pt[1].x,pt[1].y);
    GStyleOut(0,arw->color,arw->color,1,gp);
	fprintf(fp,"/>\n");
	fprintf(fp,"\t\t<polyline points=\"%2.2f,%2.2f %2.2f,%2.2f %2.2f,%2.2f  %2.2f,%2.2f\" ",pt1[0].x,pt1[0].y,pt1[1].x,pt1[1].y,pt1[2].x,pt1[2].y,pt1[3].x,pt1[3].y);
	GStyleOut(1,arw->color,arw->color,1,gp);
	fprintf(fp,"/>\n");
	fprintf(fp,"\t</g>\n");
}

//显示玻璃层
void SvgOut::ShowGlass(BASE0 &bs,int gp)
{
	CDRect drt;
	N_GLASS *gls;
	gls=(N_GLASS*)bs.buf;
	drt=CreateNRt(4,gls->pt);
	fprintf(fp,"\t<rect id=\"glass\" x=\"%2.2f\" y=\"%2.2f\" width=\"%2.2f\" height=\"%2.2f\"",drt.left,drt.top,drt.Width(),drt.Height());
	fprintf(fp," fill-opacity=\"%2.2f\" ",(double)gls->depth/(double)255);
	GStyleOut(1,gls->color,gls->ocolor,1,gp);
	fprintf(fp,"/>\n");
}


//转换为SVG可识别的汉字名
void SvgOut::ChangeFontFaceName(char *oldname,char *newname)
{
	int i,j;
	j=-1;
	for(i=0;i<20;i++)
	{
		if(strcmp(fontnm[i*2],oldname)==0)
		{
			j=i;
			break;
		}
	}
	if(j==-1){
		strcpy(newname,oldname);
		return;
	}
	strcpy(newname,fontnm[j*2+1]);
}

/*
E4 BD A0　　　　　　　　11100100 10111101 10100000

这是“你”字的UTF-8编码

4F 60　　　　　　　　　　01001111 01100000

这是“你”的Unicode编码

 

按照UTF-8的编码规则，分解如下：xxxx0100 xx111101 xx100000

把除了x之外的数字拼接在一起，就变成“你”的Unicode编码了。

注意UTF-8的最前面３个1，表示整个UTF-8串是由３个字节构成的。

经过UTF-8编码之后，再也不会出现敏感字符了，因为最高位始终为1。

 

以下是Unicode和UTF-8之间的转换关系表：

U-00000000 - U-0000007F: 0xxxxxxx

U-00000080 - U-000007FF: 110xxxxx 10xxxxxx

U-00000800 - U-0000FFFF: 1110xxxx 10xxxxxx 10xxxxxx

U-00010000 - U-001FFFFF: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx

U-00200000 - U-03FFFFFF: 111110xx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx

U-04000000 - U-7FFFFFFF: 1111110x 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx 10xxxxxx

 */



//将ANSI码转换为SVG可识别的UTF-8码
int SvgOut::ANSIToUtf8(char  *ostr,BYTE *nstr,int maxbuf)
{
	unsigned short  str[256];
	BYTE a1,a2,a3,b1,b2,b3,bh,bl,c;
	int i,s,n;
	s=0;
	n=MultiByteToWideChar(936,0,ostr,-1,str,256)-1;
	for(i=0;i<n;i++)
	{
		a1=0xe0;
		a2=0x80;
		a3=0x80;
		bl=LOBYTE(str[i]);
		bh=HIBYTE(str[i]);
		if(bh==0) //高位为零
		{
			nstr[s]=bl;
			s++;
			if(s>(maxbuf-1)) break;
			continue;
		}
		b1=(bh>>4)&0xf;
		b1|=a1;
		b2=(bh<<2)&0x3c;
		c=(bl>>6)&0x3;
		b2|=c;
		b2|=a2;
		b3=bl&0x3f;
		b3|=a3;
		nstr[s]=b1;
		nstr[s+1]=b2;
		nstr[s+2]=b3;
		s+=3;
		if(s>(maxbuf-4)) break;
	}
	return s;
}



//显示文本(只有两种方式，垂直和水平显示)
void SvgOut::ShowText(BASE0 &bs,int gp)
{
	LOGFONT font;
	int sz,n;
	BYTE utf[256]; //转换为UTF-8的缓冲区
	char  facenm[256];
	CDRect drt;
	N_TEXT *txt;
	txt=(N_TEXT*)bs.buf;
	drt=CreateNRt(4,txt->pt);
	font=txt->font;
	font.lfHeight=(long)(font.lfHeight/txt->zm);
	font.lfWidth=(long)(font.lfWidth/txt->zm);
	sz=font.lfHeight;
	sz=sz<0 ? -sz:sz;
	n=ANSIToUtf8(txt->text,utf,256);
	if(n<=0) return;
	ChangeFontFaceName(font.lfFaceName,facenm);
	if(drt.Height()>drt.Width()){
		fprintf(fp,"\t<text x=\"%2.2f\" y=\"%2.2f\" font-family=\"%s\" font-size=\"%d\"",drt.left+sz/2,drt.top,facenm,sz);
		fprintf(fp," %s ","writing-mode=\"tb-rl\"");
	}else{
		fprintf(fp,"\t<text x=\"%2.2f\" y=\"%2.2f\" font-family=\"%s\" font-size=\"%d\"",drt.left,drt.top+sz,facenm,sz);
	}
	if(font.lfItalic==1) fprintf(fp," %s ","font-style=\"italic\"");
	if(font.lfUnderline==1) fprintf(fp," %s ","text-decoration=\"underline\"");
	fprintf(fp," fill=\"#%02x%02x%02x\" ",GetRValue(txt->color),GetGValue(txt->color),GetBValue(txt->color));
	fprintf(fp,">\n\t");
	fwrite(utf,n,1,fp);
	fprintf(fp,"\n\t</text>\n");
}

//显示电气端子
void SvgOut::ShowEsite(BASE0 &bs,int gp)
{
	DPOINT cpt;
	CDRect drt;
	double r,rx,ry;
	N_ESITE *es;
	es=(N_ESITE*)bs.buf;
	drt=CreateNRt(4,es->pt);
	rx=drt.Width()/2;
	ry=drt.Height()/2;
	r=rx<ry ? rx:ry;
	cpt=drt.CenterPoint();
	fprintf(fp,"\t<esite id=\"esite\" cx=\"%2.2f\" cy=\"%2.2f\" r=\"%2.2f\" ",cpt.x,cpt.y,r);
	GStyleOut(es->solder,es->color,es->color,1,gp);
	fprintf(fp,"/>\n");
}

//显示母板
void SvgOut::ShowEgpMb(BASE0 &bs,int gp)
{
	CDRect drt;
	N_EGPMB *mb;
	mb=(N_EGPMB*)bs.buf;
	drt=CreateNRt(4,mb->pt);
	fprintf(fp,"\t<egpmb id=\"EgpMb\" x=\"%2.2f\" y=\"%2.2f\" width=\"%2.2f\" height=\"%2.2f\"",drt.left,drt.top,drt.Width(),drt.Height());
	GStyleOut(0,mb->color,mb->color,1,gp);
	fprintf(fp,"/>\n");
}


//显示潮流线
void SvgOut::ShowFlow(BASE0 &bs)
{
	BYTE dname[64];
	char c1[16],c2[16];
	char atrstr[256];
	int wd;
	DWORD color;
	int i,n,v,tpsum;
	N_FLOW *flw;
	flw=(N_FLOW*)bs.buf;
	tpsum=flw->ptsum;
	v=flw->vl;
	v=v>20 ? 0:v;
	color=cobj.vcolor[v];
	GetColorStr(c1,flw->color1);
	GetColorStr(c2,flw->color2);
	n=ANSIToUtf8(flw->dev_name,dname,64);
	dname[n]=0;
	wd=flw->linewidth*2;
	wd=wd==0 ? 1:wd;
	sprintf(atrstr,"attrib=\"%d,%s,%s,%d,%d,%d,%s,%s,%d\"",flw->did,dname,lst_vl[v],flw->type,flw->style,flw->direct,c1,c2,wd);
	fprintf(fp,"\t<polyline id=\"line\" %s points=\"",atrstr);
	for(i=0;i<flw->ptsum;i++)
	{
		fprintf(fp,"%2.0f,%2.0f ",flw->pt[i].x,flw->pt[i].y);
		if(i==(flw->ptsum-1)){
			fprintf(fp,"\"");
		}
		if(i>5&&(i%5==0)) fprintf(fp,"\n\t");
	}
	fprintf(fp,"\n\t");
	GStyleOut(0,0,color,1,0);
	fprintf(fp,"/>\n");
}


//显示母线
void SvgOut::ShowBus(BASE0 &bs)
{
	BYTE dname[64];
	char atrstr[256];
	int n,v;
	int r,g,b,r1,g1,b1,r2,g2,b2;
	double w,h,ra;
	DWORD color;
	CDRect drt;
	DPOINT cpt;
	N_BUS *bus;
	bus=(N_BUS*)bs.buf;
	v=bus->vl;
	v=v>20 ? 0:v;
	color=cobj.vcolor[v];
	drt=CreateNRt(4,bus->pt);
	cpt=drt.CenterPoint();
	w=drt.Width()/2;
	h=drt.Height()/2;
	ra=w>h ? h:w;
	n=ANSIToUtf8(bus->dev_name,dname,64);
	dname[n]=0;
	sprintf(atrstr,"attrib=\"%d,%s,%s,%d,%d,%2.2f,%2.2f,%2.2f,%2.2f\"",bus->did,dname,lst_vl[v],bus->type,bus->eid,
		drt.left,drt.top,drt.right,drt.bottom);


	fprintf(fp,"\t<g id=\"bus\" %s >\n",atrstr);
	switch(bus->type)
	{
	case 0:
		fprintf(fp,"\t\t<rect x=\"%2.2f\" y=\"%2.2f\" width=\"%2.2f\" height=\"%2.2f\"",drt.left,drt.top,drt.Width(),drt.Height());
		GStyleOut(1,color,color,1,0);
		fprintf(fp,"/>\n");
		break;
	case 1://正常母线
		fprintf(fp,"\t\t<rect x=\"%2.2f\" y=\"%2.2f\" width=\"%2.2f\" height=\"%2.2f\"",drt.left,drt.top,drt.Width(),drt.Height());
		GStyleOut(1,color,color,1,0);
		fprintf(fp,"/>\n");
		//显示3d矩形
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
		fprintf(fp,"\t\t<line x1=\"%2.2f\" y1=\"%2.2f\" x2=\"%2.2f\" y2=\"%2.2f\" stroke=\"#%02x%02x%02x\" stroke-width=\"1\" />\n",
			drt.left,drt.bottom,drt.left,drt.top,r1,g1,b1);
		fprintf(fp,"\t\t<line x1=\"%2.2f\" y1=\"%2.2f\" x2=\"%2.2f\" y2=\"%2.2f\" stroke=\"#%02x%02x%02x\" stroke-width=\"1\" />\n",
			drt.left,drt.top,drt.right,drt.top,r1,g1,b1);
		fprintf(fp,"\t\t<line x1=\"%2.2f\" y1=\"%2.2f\" x2=\"%2.2f\" y2=\"%2.2f\" stroke=\"#%02x%02x%02x\" stroke-width=\"1\" />\n",
			drt.right,drt.top,drt.right,drt.bottom,r2,g2,b2);
		fprintf(fp,"\t\t<line x1=\"%2.2f\" y1=\"%2.2f\" x2=\"%2.2f\" y2=\"%2.2f\" stroke=\"#%02x%02x%02x\" stroke-width=\"1\" />\n",
			drt.right,drt.bottom,drt.left,drt.bottom,r2,g2,b2);
		break;
	case 2: //圆形母线
		fprintf(fp,"\t\t<circle cx=\"%2.2f\" cy=\"%2.2f\" r=\"%2.2f\"",cpt.x,cpt.y,ra);
		GStyleOut(1,color,0,1,0);
		fprintf(fp,"/>\n");
		break;
	case 3: //组合图元母线
		ShowEleBus(bs);
		break;
	}
	fprintf(fp,"\t</g>\n");
}

//显示连接线
void SvgOut::ShowConline(BASE0 &bs)
{
	DWORD color;
	int i,v,tpsum;
	N_CONLINE *con;
	con=(N_CONLINE*)bs.buf;
	tpsum=con->ptsum;
	v=con->vl;
	v=v>20 ? 0:v;
	color=cobj.vcolor[v];
	fprintf(fp,"\t<polyline id=\"conline\" attrib=\"%s,%d,%d\"  points=\"",lst_vl[v],con->solder1,con->solder2);
	for(i=0;i<con->ptsum;i++)
	{
		fprintf(fp,"%2.2f,%2.2f ",con->pt[i].x,con->pt[i].y);
		if(i==(con->ptsum-1)){
			fprintf(fp,"\"");
		}
		if(i>5&&(i%5==0)) fprintf(fp,"\n\t");
	}
	fprintf(fp,"\n\t");
	GStyleOut(0,0,color,1,0);
	fprintf(fp,"/>\n");
}

//显示组合图元
void SvgOut::ShowEleGrp(BASE0 &bs)
{
	BYTE dname[64];
	char atrstr[256];
	char msg[256],cstr[32];
	DWORD color;
	double xl,yl,w1,w2,h1,h2;
	int i,j,l,n;
	BYTE v1,v2,v3;
	CDRect rt,rt1,rt2;
	N_ELEGRPA *ep;
	ep=(N_ELEGRPA*)bs.buf;
	i=cobj.GetEGPRecNo(ep->egrpid);
	if(i<0) return;
	rt1.SetDRECT(egp[i].rt1);
	rt=CreateNRt(4,ep->pt);
	h1=rt.Height();
	w1=rt.Width();
	//原来的宽高
	w2=rt1.Width();
	h2=rt1.Height();
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	v1=ep->site[0].vl; v1=v1>20 ? 20:v1;
	v2=ep->site[1].vl; v2=v2>20 ? 20:v2;
	v3=ep->site[2].vl; v3=v3>20 ? 20:v3;
	n=ANSIToUtf8(ep->dev_name,dname,64);
	dname[n]=0;
	sprintf(atrstr,"attrib=\"%d,%s,%2.2f,%2.2f,%2.2f,%2.2f,%d,%d,%d,%d,%d,%s,%s,%s\"",
		ep->did,dname,rt.left,rt.top,rt.right,rt.bottom,
		ep->type,ep->subtype,ep->egrpid,ep->sitesum,ep->showno,lst_vl[v1],lst_vl[v2],lst_vl[v3]);

	if(ep->type==1&&(ep->subtype==7||ep->subtype==8)) //是变压器时特殊处理
	{
		fprintf(fp,"\t<g id=\"elegrp\" %s>\n",atrstr);
		for(j=0;j<ep->sitesum;j++)
		{
			l=ep->site[j].vl;
			l=l>20 ? 0:l;	
			color=cobj.vcolor[l];
			sprintf(cstr,"\"#%02x%02x%02x\"",GetRValue(color),GetGValue(color),GetBValue(color));
			sprintf(msg,"<use xlink:href=\"#egp_%d_0_%d\" transform=\"translate(%2.2f,%2.2f) scale(%2.2f,%2.2f)\"",ep->egrpid,j+1,rt.left,rt.top,xl,yl);
			fprintf(fp,"\t\t%s stroke=%s/>",msg,cstr);
			fprintf(fp,"\n");
		}
		fprintf(fp,"\t</g>\n");
	}else{
		l=ep->site[0].vl;
		l=l>20 ? 0:l;	
		color=cobj.vcolor[l];
		sprintf(cstr,"\"#%02x%02x%02x\"",GetRValue(color),GetGValue(color),GetBValue(color));
		sprintf(msg,"<use id=\"elegrp\" %s xlink:href=\"#egp_%d_0\" transform=\"translate(%2.2f,%2.2f) scale(%2.2f,%2.2f)\"",atrstr,ep->egrpid,rt.left,rt.top,xl,yl);
		fprintf(fp,"\t%s stroke=%s/>",msg,cstr);
		fprintf(fp,"\n");
	}
}


//显示组合图元的母线
void SvgOut::ShowEleBus(BASE0 &bs)
{
	char msg[256],cstr[32];
	DWORD color;
	double xl,yl,w1,w2,h1,h2;
	int i,l;
	CDRect rt,rt1,rt2;
	N_BUS *bus;
	bus=(N_BUS*)bs.buf;
	i=cobj.GetEGPRecNo(bus->eid);
	if(i<0) return;
	rt1.SetDRECT(egp[i].rt1);
	rt=CreateNRt(4,bus->pt);
	h1=rt.Height();
	w1=rt.Width();
	//原来的宽高
	w2=rt1.Width();
	h2=rt1.Height();
	xl=(double)(w1/w2);
	yl=(double)(h1/h2);
	l=bus->vl;
	l=l>20 ? 0:l;	
	color=cobj.vcolor[l];
	sprintf(cstr,"\"#%02x%02x%02x\"",GetRValue(color),GetGValue(color),GetBValue(color));
	sprintf(msg,"<use xlink:href=\"#egp_%d_0\" transform=\"translate(%2.2f,%2.2f) scale(%2.2f,%2.2f)\"",bus->eid,rt.left,rt.top,xl,yl);
	fprintf(fp,"\t%s stroke=%s/>",msg,cstr);
	fprintf(fp,"\n");
}


//显示一个数字
void SvgOut::ShowDigit(char *text,float val,char *pre,char *unit,char xs)
{
	char p1[64];
	strcpy(text,pre);
	GetDoubleStr(val,p1,xs);
	strcat(text,p1);
	strcat(text,unit);
}

void SvgOut::ShowDigitPQ(char *text,float vp,float vq,char xs)
{
	char p[64],p1[64];
	GetDoubleStr(vp,p,xs);
	strcpy(text,p);
	if(vq>=0) strcpy(p,"+j");
	else strcpy(p,"-j");
	GetDoubleStr(vq,p1,xs);
	strcat(p,p1);
	strcat(text,p);
}

//显示模拟量
void SvgOut::ShowAnalog(BASE0 &bs)
{
	BYTE dname[64];
	char c1[16],c2[16];
	char atrstr[256];
	int i,sz,n,m;
	BYTE utf[256]; //转换为UTF-8的缓冲区
	char  facenm[256];
	char  text[256];
	CDRect drt;
	N_ANL *anl;
	LOGFONT font;
	anl=(N_ANL *)bs.buf;
	drt=CreateNRt(4,anl->pt);
	font=anl->lf;
	font.lfHeight=(int)(font.lfHeight/anl->zm);
	font.lfWidth=(int)(font.lfWidth/anl->zm);
	switch(anl->dtype)
	{
	case 0:case 4: //"发电机","交流线路","负荷"
		switch(anl->xsmode){
		case 0:
			ShowDigitPQ(text,anl->rval[0].curval,anl->rval[1].curval,anl->xs);
		    break;
		case 1:
			ShowDigit(text,anl->rval[0].curval,"","MW",anl->xs);
			break;
		case 2:
			ShowDigit(text,anl->rval[1].curval,"","Mvar",anl->xs);
			break;
		}
		break;
	case 1:
		ShowDigitPQ(text,anl->rval[0].curval,anl->rval[1].curval,anl->xs);
		break;
	case 2: //直流线路
		ShowDigit(text,anl->rval[0].curval,"","MW",anl->xs);
		break;
	case 3: //节点
		switch(anl->xsmode){
		case 0: // 显示电压等级
			ShowDigit(text,anl->rval[0].curval,"等级:","kV",anl->xs);
			break;
		case 1:
			ShowDigit(text,anl->rval[1].curval,"","pu",anl->xs);
			break;
		case 2:
			ShowDigit(text,(float)113.11,"","",anl->xs);
			break;
		case 3:
			ShowDigit(text,anl->rval[2].curval,"","deg",anl->xs);
			break;
		}
		break;
	case 5:  //变压器
		ShowDigit(text,anl->rval[0].curval,"","",anl->xs);
		break;
	case 6: //三绕组变压器
		sprintf(text,"%2.0f",anl->rval[0].curval);
		break;
	case 7:   case 8: //电容器，电抗器投入组数
		switch(anl->xsmode){
		case 0:
			ShowDigit(text,anl->rval[0].curval,"","",anl->xs);
			break;
		case 1:
			ShowDigit(text,anl->rval[1].curval,"","",0);
			break;
		}
		break;
	case 9:  //显示SVC
		ShowDigit(text,anl->rval[0].curval,"","Mvar",anl->xs);
		break;
	case 10:
		i=anl->xsmode;
		i=i>3 ? 3:i;
		if(i<3) ShowDigit(text,anl->rval[i].curval,"","MW",anl->xs);
		else ShowDigit(text,anl->rval[i].curval,"","$/hr",anl->xs);
		break;
	case 11:
		i=anl->xsmode;
		switch(i){
		case 0:case 2:case 3:case 4:
			ShowDigit(text,anl->rval[0].curval,"","MW",anl->xs);
			break;
		case 1:case 5:
			ShowDigit(text,anl->rval[0].curval,"","MVar",anl->xs);
			break;
		}
		break;
	case 14:  //设备量测
	case 15:  //非设备量测
		ShowDigit(text,anl->rval[0].curval,"","",anl->xs);
		break;
	}

	sz=font.lfHeight;
	sz=sz<0 ? -sz:sz;
	n=ANSIToUtf8(text,utf,256);
	if(n<=0) return;
	ChangeFontFaceName(font.lfFaceName,facenm);
	m=ANSIToUtf8(anl->dev_name,dname,64);
	dname[m]=0;
	GetColorStr(c1,anl->ncolor);
	GetColorStr(c2,anl->acolor);
	sprintf(atrstr,"attrib=\"%d,%s,%d,%d,%d,%d,%s,%s,%2.2f,%2.2f,%2.2f,%2.2f\"",anl->did,dname,anl->xs,anl->direction,anl->dtype,anl->xsmode,c1,c2,drt.left,drt.top,drt.right,drt.bottom);
	if(anl->direction==1){
		fprintf(fp,"\t<text id=\"analog\" %s x=\"%2.2f\" y=\"%2.2f\" font-family=\"%s\" font-size=\"%d\"",atrstr,drt.left+sz/2,drt.top,facenm,sz);
		fprintf(fp," %s ","writing-mode=\"tb-rl\"");
	}else{
		fprintf(fp,"\t<text id=\"analog\" %s x=\"%2.2f\" y=\"%2.2f\" font-family=\"%s\" font-size=\"%d\"",atrstr,drt.left,drt.top+sz,facenm,sz);
	}
	fprintf(fp," fill=\"#%02x%02x%02x\" ",GetRValue(anl->ncolor),GetGValue(anl->ncolor),GetBValue(anl->ncolor));
	fprintf(fp,">\n\t");
	fwrite(utf,n,1,fp);
	fprintf(fp,"\n\t</text>\n");
}


//显示榜图
void SvgOut::ShowBar(BASE0 &bs)
{
	int m;
	BYTE dname[64];
	char cr1[16],cr2[16];
	char atrstr[256];
	DWORD c1;
	CDRect drt;
	N_BAR *bar;
	bar=(N_BAR *)bs.buf;
	drt=CreateNRt(4,bar->pt);
	m=ANSIToUtf8(bar->dsrc.name,dname,64);
	dname[m]=0;
	GetColorStr(cr1,bar->ncolor);
	GetColorStr(cr2,bar->acolor);
	sprintf(atrstr,"attrib=\"%d,%s,%d,%d,%2.2f,%2.2f,%2.2f,%d,%d,%s,%s\"",bar->dsrc.did,dname,bar->xy,bar->outline,
		bar->max,bar->min,bar->aval,bar->dsrc.dtype,bar->dsrc.xsmode,cr1,cr2);
	fprintf(fp,"\t<rect id=\"bar\" %s x=\"%2.2f\" y=\"%2.2f\" width=\"%2.2f\" height=\"%2.2f\"",atrstr,drt.left,drt.top,drt.Width(),drt.Height());
	c1=bar->outline==0 ? 0xffffff:0;
	GStyleOut(1,bar->ncolor,c1,1,0);
	fprintf(fp,"/>\n");
}

//显示百分饼图
void SvgOut::ShowPctPie(BASE0 &bs)
{
	int m;
	BYTE dname[64];
	char cr1[16],cr2[16],cr3[16];
	char atrstr[256];
	DPOINT cpt;
	double rx,ry,r;
	CDRect drt;
	N_PCTPIE *pie;
	pie=(N_PCTPIE*)bs.buf;
	drt=CreateNRt(4,pie->pt);
	cpt=drt.CenterPoint();
	rx=drt.Width()/2;
	ry=drt.Height()/2;
	r=rx<ry ? rx:ry;
	m=ANSIToUtf8(pie->dev_name,dname,64);
	dname[m]=0;
	GetColorStr(cr1,pie->color1);
	GetColorStr(cr2,pie->color2);
	GetColorStr(cr3,pie->fcolor);
	sprintf(atrstr,"attrib=\"%d,%s,%2.2f,%2.2f,%2.2f,%d,%s,%s,%s\"",pie->did,dname,cpt.x,cpt.y,r,pie->type,cr1,cr2,cr3);
	fprintf(fp,"\t<g id=\"pctpie\" %s >\n",atrstr);
	fprintf(fp,"\t\t<circle cx=\"%2.2f\" cy=\"%2.2f\" r=\"%2.2f\" ",cpt.x,cpt.y,r);
	GStyleOut(1,pie->color2,pie->color1,1,0);
	fprintf(fp,"/>\n");
	fprintf(fp,"\t\t<path d=\"M%2.2f,%2.2f h%2.2f a%2.2f,%2.2f 0 0,0 %2.2f,%2.2f z\"",cpt.x,cpt.y,r,r,r,-r,-r);
    GStyleOut(1,pie->color1,pie->color1,1,0);
	fprintf(fp,"/>\n");
	fprintf(fp,"\t</g>\n");
}

//显示表格线
void SvgOut::ShowTable(BASE0 &bs)
{
	char atrstr[256];
	char c1[32];
	char cstr[32];
	int i,ym,y;
	double w,h,yl,lw;
	CDRect drt;
	N_TABLE *ta;
	ta=(N_TABLE *)bs.buf;
	drt=CreateNRt(4,ta->pt);
	w=(double)(ta->width);
	w=w>255 ? 255:w;
	ym=ta->line<2 ? 2:ta->line;
	h=drt.Height();
	yl=(double)(h/(double)ym);
	sprintf(cstr,"\"#%02x%02x%02x\"",GetRValue(ta->color),GetGValue(ta->color),GetBValue(ta->color));
	GetColorStr(c1,ta->color);
	sprintf(atrstr,"attrib=\"%2.2f,%2.2f,%2.2f,%2.2f,%d,%d,%2.2f,%s\"",drt.left,drt.top,drt.right,drt.bottom,
		ta->line,ta->dbline,ta->width,c1);

	fprintf(fp,"\t<g id=\"table\" %s fill=\"none\" stroke=%s stroke-width=\"%2.2f\">\n",atrstr,cstr,w);
	for(i=0;i<ym+1;i++){
		y=(int)(i*yl);
		fprintf(fp,"\t\t<line x1=\"%2.2f\" y1=\"%2.2f\" x2=\"%2.2f\" y2=\"%2.2f\" />\n",drt.left,drt.bottom-y,drt.right,drt.bottom-y);
	};	
	lw=ta->width;
	if(ta->dbline==1) lw=lw*2;
	fprintf(fp,"\t\t<rect x=\"%2.2f\" y=\"%2.2f\" width=\"%2.2f\" height=\"%2.2f\" stroke-width=\"%2.2f\"  />\n",drt.left,drt.top,drt.Width(),drt.Height(),lw);
    fprintf(fp,"\t</g>\n");

}


//画出坐标
void  SvgOut::DrawCoordinate(CRect drt,N_COORDINATE &co)
{
	char p[100];
	DWORD c1;
	char cstr1[32],cstr2[32];
	char facenm[256];
	int i,xm,ym,w,h,x,y,m,n,fh;
	double xl,yl,nx,ny;
	CRect rt,rt1;
	rt=drt;
	c1=co.colorc;
	rt.left=(int)(rt.left+40/co.zm);
	rt.bottom=(int)(rt.bottom-24/co.zm);
	rt.right=(int)(rt.right-20/co.zm);
	rt.top=(int)(rt.top+20/co.zm);	
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
		sprintf(cstr1,"\"#%02x%02x%02x\"",GetRValue(c1),GetGValue(c1),GetBValue(c1));
		sprintf(cstr2,"\"#%02x%02x%02x\"",GetRValue(co.colort),GetGValue(co.colort),GetBValue(co.colort));
		ChangeFontFaceName(co.fontx.lfFaceName,facenm);
		fprintf(fp,"\t\t<g id=\"xvshow_line\" stroke=%s stroke-width=\"1\" >\n",cstr1);
		for(i=0;i<xm+1;i++){
			x=(int)(i*xl);
			fprintf(fp,"\t\t\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" />\n",rt.left+x,rt.bottom,rt.left+x,rt.bottom+m);
	    };
		fprintf(fp,"\t\t</g>\n");
		///////
		fh=co.fontx.lfHeight;
		fh=fh<0 ? -fh:fh;
		fprintf(fp,"\t\t<g id=\"xvshow_text\" fill=%s font-family=\"%s\" font-size=\"%d\" text-anchor=\"middle\" >\n",cstr2,facenm,fh);
		for(i=1;i<xm+1;i++){
			x=(int)(i*xl);
			sprintf(p,"%d",(DWORD)(i*nx+co.xmin));
			fprintf(fp,"\t\t\t<text x=\"%d\" y=\"%d\"> %s  </text>\n",rt.left+x,drt.bottom,p);
		}
		fprintf(fp,"\t\t</g>\n");
	}
	m=(int)(5*cobj.curzoom/co.zm);
	if(co.yvshow==1){
		sprintf(cstr1,"\"#%02x%02x%02x\"",GetRValue(c1),GetGValue(c1),GetBValue(c1));
		sprintf(cstr2,"\"#%02x%02x%02x\"",GetRValue(co.colort),GetGValue(co.colort),GetBValue(co.colort));
		ChangeFontFaceName(co.fonty.lfFaceName,facenm);
		fprintf(fp,"\t\t<g id=\"yvshow_line\" stroke=%s stroke-width=\"1\" >\n",cstr1);
		for(i=0;i<ym+1;i++){
			y=(int)(i*yl);
			fprintf(fp,"\t\t\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" />\n",rt.left-m,rt.bottom-y,rt.left,rt.bottom-y);
		};
		fprintf(fp,"\t\t</g>\n");
		///////////////////////////////
		fh=co.fontx.lfHeight;
		fh=fh<0 ? -fh:fh;
		fprintf(fp,"\t\t<g id=\"xvshow_text\" fill=%s font-family=\"%s\" font-size=\"%d\" text-anchor=\"end\">\n",cstr2,facenm,fh);
		for(i=1;i<ym+1;i++){
			y=(int)(i*yl);
			sprintf(p,"%d",(DWORD)(i*ny+co.ymin));
			fprintf(fp,"\t\t\t<text x=\"%d\" y=\"%d\"> %s  </text>\n",rt.left-m,rt.bottom-y+fh/2-1,p);
		}	
		fprintf(fp,"\t\t</g>\n");
	}


	if(co.wxdraw==1){
		sprintf(cstr1,"\"#%02x%02x%02x\"",GetRValue(co.colorw),GetGValue(co.colorw),GetBValue(co.colorw));
		fprintf(fp,"\t\t<g id=\"wxdraw_line\" stroke=%s stroke-width=\"1\" >\n",cstr1);
		for(i=0;i<xm+1;i++){
			x=(int)(i*xl);
			fprintf(fp,"\t\t\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" />\n",rt.left+x,rt.bottom,rt.left+x,rt.top);
		};
		fprintf(fp,"\t\t</g>\n");
	}

	if(co.wydraw==1){
		sprintf(cstr1,"\"#%02x%02x%02x\"",GetRValue(co.colorw),GetGValue(co.colorw),GetBValue(co.colorw));
		fprintf(fp,"\t\t<g id=\"wxdraw_line\" stroke=%s stroke-width=\"1\" >\n",cstr1);
		for(i=0;i<ym+1;i++){
			y=(int)(i*yl);
			fprintf(fp,"\t\t\t<line x1=\"%d\" y1=\"%d\" x2=\"%d\" y2=\"%d\" />\n",rt.left,rt.bottom-y,rt.right,rt.bottom-y);
		};
		fprintf(fp,"\t\t</g>\n");
	}
	
	DPOINT pt[2],pt1[4];
	
	sprintf(cstr1,"\"#%02x%02x%02x\"",GetRValue(c1),GetGValue(c1),GetBValue(c1));
	
	fprintf(fp,"\t\t<g id=\"cdtarrow\" fill=%s stroke=%s stroke-width=\"1\">\n",cstr1,cstr1);
	pt[0].x=drt.left;pt[0].y=rt.bottom;
	pt[1].x=drt.right;pt[1].y=rt.bottom;
	n=GetDirPoint(pt[0],pt[1],pt1,4);
	fprintf(fp,"\t\t\t<line x1=\"%2.2f\" y1=\"%2.2f\" x2=\"%2.2f\" y2=\"%2.2f\" />\n",pt[0].x,pt[0].y,pt[1].x,pt[1].y);
	fprintf(fp,"\t\t\t<polyline points=\"%2.2f,%2.2f %2.2f,%2.2f %2.2f,%2.2f  %2.2f,%2.2f\" />\n",pt1[0].x,pt1[0].y,pt1[1].x,pt1[1].y,pt1[2].x,pt1[2].y,pt1[3].x,pt1[3].y);
	pt[0].x=rt.left;pt[0].y=drt.bottom;
	pt[1].x=rt.left;pt[1].y=drt.top;
	n=GetDirPoint(pt[0],pt[1],pt1,4);
	fprintf(fp,"\t\t\t<line x1=\"%2.2f\" y1=\"%2.2f\" x2=\"%2.2f\" y2=\"%2.2f\" />\n",pt[0].x,pt[0].y,pt[1].x,pt[1].y);
	fprintf(fp,"\t\t\t<polyline points=\"%2.2f,%2.2f %2.2f,%2.2f %2.2f,%2.2f  %2.2f,%2.2f\" />\n",pt1[0].x,pt1[0].y,pt1[1].x,pt1[1].y,pt1[2].x,pt1[2].y,pt1[3].x,pt1[3].y);
	fprintf(fp,"\t\t</g>\n");
};

//显示坐标
void SvgOut::ShowCoordnate(BASE0 &bs)
{
	char cr1[16],cr2[16],cr3[32];
	char atrstr[256];
	double w;
	CDRect rt;
	CRect rt1;
	N_COORDINATE *co,tm;
	co=(N_COORDINATE *)bs.buf;
	rt=CreateNRt(4,co->pt);
	rt.GetRECT(rt1);
	if(co->xmax<co->xmin){
		co->xmax=100;
		co->xmin=0;
	}
	if(co->ymax<co->ymin){
		co->ymax=100;
		co->ymin=0;
	}
	tm=co[0];
	tm.width1=(int)(tm.width1);
	tm.width2=(int)(tm.width2);
	tm.fontx.lfHeight=(long)(tm.fontx.lfHeight/tm.zm);
	tm.fontx.lfWidth=(long)(tm.fontx.lfWidth/tm.zm);
	tm.fonty.lfHeight=(long)(tm.fonty.lfHeight/tm.zm);
	tm.fonty.lfWidth=(long)(tm.fonty.lfWidth/tm.zm);
	w=tm.width1;
	tm.width1=w>255 ? 255:w; 
	w=tm.width2;
	tm.width2=w>255 ? 255:w; 
	GetColorStr(cr1,co->colorc);
	GetColorStr(cr2,co->colorw);
	GetColorStr(cr3,co->colort);
	sprintf(atrstr,"attrib=\"%d,%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d\"",rt1.left,rt1.top,rt1.right,rt1.bottom,co->xmin,co->xmax,
		co->ymin,co->ymax,cr1,cr2,cr3,co->xdot,co->ydot,co->wxdraw,co->wydraw,co->xvshow,co->yvshow,tm.fontx.lfHeight,tm.fontx.lfWidth,
		tm.fonty.lfHeight,tm.fonty.lfWidth);
	fprintf(fp,"\t<g id=\"coordinate\" %s fill=\"none\" >\n",atrstr);
	DrawCoordinate(rt1,tm);
	fprintf(fp,"\t</g>\n");
}


//显示饼图
void SvgOut::ShowPie(BASE0 &bs)
{
	BYTE dname[64];
	char atrstr[256];
	
	BYTE utf[256]; //转换为UTF-8的缓冲区
	CRect crt;
	DPOINT cpt;
	CDRect r,rt,rt1,rt2;
	int i,n,m;
	double v1,v2,v3,w,h,pw,a;
	N_PIE *pie;
	char p[100];
	pie=(N_PIE *)bs.buf;
	rt=CreateDrawNRt(4,pie->pt,1);
	rt1=rt;
	rt1.bottom=rt1.top+60;
	rt2=rt;
	rt2.top=rt1.bottom;
	v1=100;
	v2=25;
	v3=v2/v1;
	m=ANSIToUtf8(pie->name,dname,64);
	dname[m]=0;
	sprintf(atrstr,"attrib=\"%d,%s,%2.2f,%2.2f,%2.2f,%2.2f\"",pie->did,dname,rt.left,rt.top,rt.right,rt.bottom);

	fprintf(fp,"\t<g id=\"syspie\" %s >\n",atrstr);
	//显示方块图
	for(i=0;i<2;i++)
	{
		r.left=rt1.left+4;
		r.top=rt1.top+i*20+2;
		r.bottom=r.top+15;
		r.right=r.left+15;
		r.GetRECT(crt);
		fprintf(fp,"\t\t<rect x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\"",crt.left,crt.top,crt.Width(),crt.Height());
		GStyleOut(1,pie->color[i],0,1,0);
		fprintf(fp,"/>\n");

		r.left=r.right+4;
		r.right=rt1.right-3;
		if(i==0) sprintf(p,"区域有功出力:%2.0fMW",v1);
		else sprintf(p,"区域有功损耗:%2.0fMW",v2);
		r.GetRECT(crt);
		fprintf(fp,"\t\t<text x=\"%d\" y=\"%d\" font-family=\"SimSum\" font-size=\"16\"",crt.left,crt.top+16);
		n=ANSIToUtf8(p,utf,256);
		fprintf(fp," fill=\"#%02x%02x%02x\" ",GetRValue(pie->color[i]),GetGValue(pie->color[i]),GetBValue(pie->color[i]));
		fprintf(fp,">\n\t\t");
		fwrite(utf,n,1,fp);
		fprintf(fp,"\n\t\t</text>\n");
	}
	r=rt1;
	r.top=r.bottom-20;
	r.left+=22;
	sprintf(p,"损耗所占比例:%2.2f％",v3*100);
	r.GetRECT(crt);
	fprintf(fp,"\t\t<text x=\"%d\" y=\"%d\" font-family=\"SimSum\" font-size=\"16\"",crt.left,crt.top+16);
	n=ANSIToUtf8(p,utf,256);
	fprintf(fp," fill=\"#%02x%02x%02x\" ",GetRValue(pie->color[1]),GetGValue(pie->color[1]),GetBValue(pie->color[1]));
	fprintf(fp,">\n\t\t");
	fwrite(utf,n,1,fp);
	fprintf(fp,"\n\t\t</text>\n");
	//绘制饼图用RT2矩形绘制
	if(v1==0) return;
	pw=v2/v1;
	w=rt2.Width();
	h=rt2.Height();
	if(w>h)
	{
		a=(w-h)/2;
		rt2.left+=a;
		rt2.right-=a;
	}else{
		a=(h-w)/2;
		rt2.top+=a;
		rt2.bottom-=a;
	}
	pw=pw<0 ? 0:pw;
	pw=pw>1 ? 1:pw;

	cpt=rt2.CenterPoint();
	w=rt2.Width()/2;
	h=rt2.Height()/2;
	a=w<h ? w:h;
	fprintf(fp,"\t\t<circle cx=\"%2.2f\" cy=\"%2.2f\" r=\"%2.2f\" ",cpt.x,cpt.y,a);
	GStyleOut(1,pie->color[0],0,1,0);
	fprintf(fp,"/>\n");
	fprintf(fp,"\t\t<path d=\"M%2.2f,%2.2f h%2.2f a%2.2f,%2.2f 0 0,0 %2.2f,%2.2f z\"",cpt.x,cpt.y,a,a,a,-a,-a);
    GStyleOut(1,pie->color[1],0,1,0);
	fprintf(fp,"/>\n");
	fprintf(fp,"\t</g>\n");
}


//显示日期
void SvgOut::ShowDate(BASE0&bs)
{
	char cr1[16],cr2[16],cr3[32];
	char atrstr[256];
	int i,n,fh;
	CRect rt;
	CDRect drt;
	POINT cpt;
	DWORD c1;
	char facenm[64];
	BYTE utf[256]; //转换为UTF-8的缓冲区
	char p[100],mn[10],da[10];
	N_DATE *date;
	date=(N_DATE *)bs.buf;
	drt=CreateNRt(4,date->pt);
	drt.GetRECT(rt);
	GetDtStr(date->tm.GetMonth(),mn);
	GetDtStr(date->tm.GetDay(),da);
	c1=date->outcolor;
	GetColorStr(cr1,date->bcolor);
	GetColorStr(cr2,date->outcolor);
	GetColorStr(cr3,date->fcolor);
	fh=(int)(date->font.lfHeight/date->zm);
	ChangeFontFaceName(date->font.lfFaceName,facenm);
	fh=fh<0 ? -fh:fh;
	sprintf(atrstr,"attrib=\"%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%d,%d\"",rt.left,rt.top,rt.right,rt.bottom,
		date->fmt,date->outline,date->tran,cr1,cr2,cr3,facenm,fh,fh/2);

	fprintf(fp,"\t<g id=\"date\" %s >\n",atrstr);
	if(date->tran==0){
		fprintf(fp,"\t\t<rect id=\"rect\" x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\"",rt.left,rt.top,rt.Width(),rt.Height());
		GStyleOut(1,date->bcolor,c1,1,0);
		fprintf(fp,"/>\n");		
	}
	if(date->outline>0)
	{
		fprintf(fp,"\t\t<rect id=\"rect\" x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\"",rt.left,rt.top,rt.Width(),rt.Height());
		GStyleOut(0,date->bcolor,c1,1,0);
		fprintf(fp,"/>\n");	
	}
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
	
	rt.left++;
	rt.top++;
	rt.right-=3;
	rt.bottom-=3;
	c1=date->fcolor;
	
	cpt=rt.CenterPoint();
	fprintf(fp,"\t\t<text x=\"%d\" y=\"%d\" font-family=\"%s\" font-size=\"%d\" text-anchor=\"middle\"",cpt.x,cpt.y+fh/2,facenm,fh);
	n=ANSIToUtf8(p,utf,256);
	fprintf(fp," fill=\"#%02x%02x%02x\" ",GetRValue(c1),GetGValue(c1),GetBValue(c1));
	fprintf(fp,">\n\t\t");
	fwrite(utf,n,1,fp);
	fprintf(fp,"\n\t\t</text>\n");
	fprintf(fp,"\t</g>\n");
}

//显示日期
void SvgOut::ShowTime(BASE0&bs)
{
	char cr1[16],cr2[16],cr3[32];
	char atrstr[256];
	int n,fh;
	CRect rt;
	CDRect drt;
	POINT cpt;
	DWORD c1;
	char facenm[64];
	BYTE utf[256]; //转换为UTF-8的缓冲区
	char p[100],hr[10],min[10],sec[10];
	N_TIME *date;
	date=(N_TIME *)bs.buf;
	drt=CreateNRt(4,date->pt);
	drt.GetRECT(rt);
	GetDtStr(date->tm.GetHour(),hr);
	GetDtStr(date->tm.GetMinute(),min);
	GetDtStr(date->tm.GetSecond(),sec);
	c1=date->outcolor;

	GetColorStr(cr1,date->bcolor);
	GetColorStr(cr2,date->outcolor);
	GetColorStr(cr3,date->fcolor);
	fh=(int)(date->font.lfHeight*cobj.curzoom/date->zm);
	ChangeFontFaceName(date->font.lfFaceName,facenm);
	fh=fh<0 ? -fh:fh;
	sprintf(atrstr,"attrib=\"%d,%d,%d,%d,%d,%d,%d,%s,%s,%s,%s,%d,%d\"",rt.left,rt.top,rt.right,rt.bottom,
		date->fmt,date->outline,date->tran,cr1,cr2,cr3,facenm,fh,fh/2);

	fprintf(fp,"\t<g id=\"time\" %s >\n",atrstr);

	if(date->tran==0){
		fprintf(fp,"\t\t<rect id=\"rect\" x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\"",rt.left,rt.top,rt.Width(),rt.Height());
		GStyleOut(1,date->bcolor,c1,1,0);
		fprintf(fp,"/>\n");	
	}
	if(date->outline>0)
	{
		fprintf(fp,"\t\t<rect id=\"rect\" x=\"%d\" y=\"%d\" width=\"%d\" height=\"%d\"",rt.left,rt.top,rt.Width(),rt.Height());
		GStyleOut(0,date->bcolor,c1,1,0);
		fprintf(fp,"/>\n");	
	}
	switch(date->fmt){
	case 1:sprintf(p,"%s:%s",hr,min);			break;
	case 2:sprintf(p,"%s时%s分%s秒",hr,min,sec);break;
	case 3:sprintf(p,"%s点%s分%s秒",hr,min,sec);break;
	case 4:strcpy(p,"02分02秒");				break;	
	default:
		sprintf(p,"%s:%s:%s",hr,min,sec);
	};
	
	rt.left++;
	rt.top++;
	rt.right-=3;
	rt.bottom-=3;
	c1=date->fcolor;
	
	cpt=rt.CenterPoint();
	fprintf(fp,"\t\t<text x=\"%d\" y=\"%d\" font-family=\"%s\" font-size=\"%d\" text-anchor=\"middle\"",cpt.x,cpt.y+fh/2,facenm,fh);
	n=ANSIToUtf8(p,utf,256);
	fprintf(fp," fill=\"#%02x%02x%02x\" ",GetRValue(c1),GetGValue(c1),GetBValue(c1));
	fprintf(fp,">\n\t\t");
	fwrite(utf,n,1,fp);
	fprintf(fp,"\n\t\t</text>\n");
	fprintf(fp,"\t</g>\n");
}
