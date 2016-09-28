// SvgBase.cpp: implementation of the CSvgBase class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SvgBase.h"
#include "math.h"

//SVG主键字
const char* svgkey[]={"?xml",		//index=0
						"svg",		//index=1
						"g",		//index=2
						"defs",		//index=3
						"symbol",	//index=4
						"use",		//index=5
						"metadata",	//index=6
						"desc",		//index=7
						"title",	//index=8
						"style",	//index=9
						"script",	//index=10
						"a"			//index=11
};

//公共图形交换标准(CGE)键值
const char* cgekey[]={"cge:PSR_Ref",				//index=0
						"cge:Meas_Ref",				//index=1
						"cge:CN_Ref",				//index=2
						"cge:PSR_Link",				//index=3
						"cge:Layer_Ref",			//index=4
						"cge:MeasValSource_Ref"		//index=5
};

//显示图形元素，注意该数组与GTYPE对应！！！
const char* graphkey[]={"line","polyline","path","ploygon","rect","circle","ellipse","text","image"};

//属性关键词
const char* atrkey[]={"id",				//index=0
						"attrib",		//index=1
						"fill",			//index=2
						"stroke",		//index=3
						"stroke-width",	//index=4
						"points",		//index=5
						"x",			//index=6
						"y",			//index=7
						"cx",			//index=8
						"cy",			//index=9
						"r",			//index=10
						"rx",			//index=11
						"ry",			//index=12
						"width",		//index=13
						"height",		//index=14
						"d",			//index=15
						"fill-opacity",	//index=16
						"font-family",	//index=17
						"font-size",	//index=18
						"writing-mode",	//index=19
						"text-anchor",	//index=20
						"font-style",	//index=21
						"xlink:href",	//index=22
						"class",		//index=23
						"style",		//index=24
						"viewBox"		//index=25
};		

//此处需与powerpaint的变量lst_vl对应
const char* cvlevel[]={
		"BV-1000KV",
		"BV-750KV",
		"kv500kV",//"BV-500KV",
		"BV-330KV",
		"kv220kV",//"BV-220KV",
		"kv110kV",//"BV-110KV",
		"kv66kV",//"BV-66KV",
		"BV-38KV",
		"kv35kV",//"BV-35KV",
		"BV-22KV",
		"BV-20KV",
		"BV-18KV",
		"BV-15KV",
		"BV-14KV",
		"kv10kV",//"BV-10KV",
		"BV-6KV",
		"BV-3KV",
		"kv-1",//"BV-1KV",
		"BV-380",
		"BV-220"};
const float fvlevel[]={1000.0f,750.0f,500.0f,330.0f,220.0f,110.0f,66.0f,38.0f,35.0f,22.0f,20.0f,18.0f,15.0f,14.0f,10.0f,6.0f,3.0f,1.0f,0.38f,0.22f};

#define IsNumber(c)	(c<='9' && c>='0')||(c=='-' || c=='.')
#define IsLetter(c)	(c<='Z' && c>='A')||(c<='z' && c>='a')

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CSvgBase::CSvgBase()
{
	m_pTranslator=NULL;
	m_byCode=0;
}

CSvgBase::~CSvgBase()
{
	m_CssStyleVtr.clear();
	for(FIGUREELEVTR::iterator epr=m_EleGrpVtr.begin();epr!=m_EleGrpVtr.end();++epr)
		delete *epr;
	m_EleGrpVtr.clear();

	for(FIGUREGRPVTR::iterator gpr=m_FigureGrpVtr.begin();gpr!=m_FigureGrpVtr.end();++gpr)
		delete *gpr;
	m_FigureGrpVtr.clear();

	for(LAYERVTR::iterator itr=m_LayerVtr.begin();itr!=m_LayerVtr.end();++itr)
		delete *itr;
	m_LayerVtr.clear();

	if(m_pTranslator!=NULL)
		delete m_pTranslator;
	m_pTranslator=NULL;
}

BOOL CSvgBase::MainParse(IXmlNode* pNode)
{
	if(pNode->IsKindof(svgkey[3]))//defs
	{
		if(pNode->GetFirstSubNode())
		{
			IXmlNode* pSymNode=NULL;
			while((pSymNode=pNode->GetNextSubNode())!=NULL)
			{
				if(pSymNode->IsKindof(svgkey[4]))//symbol
				{
					GetSymbol(pSymNode);
				}
				else if(pSymNode->IsKindof(svgkey[9]))//style
				{
					GetStyle(pSymNode);
				}
			}
		}
		PolyFigureGroup();//多态图元分析
	}
	else if(pNode->IsKindof(svgkey[2]))//g
	{
		TRACE("%s\n", pNode->GetPropValue("id"));
		GetLayer(pNode);
	}
	return TRUE;
}

BOOL CSvgBase::GetViewBox(const char *pView, CRect *pRect)
{
	int val[4]={0};
	if(strchr(pView,',')!=NULL)
		sscanf(pView,"(%d,%d,%d,%d)",&val[0],&val[1],&val[2],&val[3]);
	else
	{
		if(SplitStr<int>(pView,' ',val,4)!=4)
			return FALSE;
	}
	*pRect=CRect(val[0],val[1],val[0]+val[2],val[1]+val[3]);
	return TRUE;
}

//将utf->8码转换为ansi码
int CSvgBase::Utf8ToASCII(const unsigned char* pUtf,int len,char *pASCII,int maxbuf)
{
	unsigned short  str[256]={0};
	unsigned char a[3],b[2];
	int m,n;
	int s=0;
	for(int i=0;i<len;i++)
	{
		m=len-i;
		if(m>=3)
		{
			a[0]=(0xe0 & pUtf[i]);
			a[1]=(0x80 & pUtf[i+1]);
			a[2]=0x80 & pUtf[i+2];
			if(a[0]==0xe0 && a[1]==0x80 && a[2]==0x80) //汉字处理
			{
				b[0]=(pUtf[i]<<4)&0xf0;
				b[0]=b[0]|((pUtf[i+1]>>2)&0x0f);
				b[1]=(pUtf[i+1]<<6)&0xc0;
				b[1]=b[1]|(pUtf[i+2]&0x3f);
				str[s]=MAKEWORD(b[1],b[0]);
				s++;
				i+=2;
				continue;
			}
		}
		//直接处理非汉字字符
		str[s]=MAKEWORD(pUtf[i],0);
		s++;
	}
	n=WideCharToMultiByte(936,0,str,s,pASCII,maxbuf,NULL,NULL);
	if(n>=0) pASCII[n]=0;
	return n;
}

//返回图形变换矩阵
BOOL CSvgBase::GetTransform(const char* pTrans,int len,MATRIX* pMatrix)
{
	if(pTrans==NULL)
		return FALSE;

	int count=0;
	MATRIX matrix[5];
	char* pStart=(char*)pTrans;
	char* pEnd=strchr(pStart,')');

	float fVal[6];
	char buffer[128];
	int slen=0;
	while(pEnd!=NULL && (slen=pEnd-pStart)>0)
	{
		strncpy(buffer,pStart,slen);
		buffer[slen]=0;
		if((pStart=strstr(buffer,"matrix("))!=NULL)
		{
			pStart=pStart+7;
			if(strlen(pStart)>0)
			{
				if(SplitStr<float>(pStart,' ',fVal,6)==6)
				{
					matrix[count].fa=fVal[0];
					matrix[count].fb=fVal[1];
					matrix[count].fc=fVal[2];
					matrix[count].fd=fVal[3];
					matrix[count].fe=fVal[4];
					matrix[count].ff=fVal[5];
					count++;
				}
			}
		}
		else if((pStart=strstr(buffer,"rotate("))!=NULL)
		{
			pStart=pStart+7;
			if(strlen(pStart)>0)
			{
				if(SplitStr<float>(pStart,',',fVal,3)==3)
				{
					if(fabs(fVal[0])>0)
					{
						float fcos=cos(fVal[0]*PI/180);
						float fsin=sin(fVal[0]*PI/180);
						
						/////矩阵公式
						//cos          sin           0
						//-sin         cos           0
						//a-acos+bsin  b-asin-bcos  1 
						//////////////////////////////////
						
						matrix[count].fa=fcos;
						matrix[count].fb=fsin;
						matrix[count].fc=-fsin;
						matrix[count].fd=fcos;
						matrix[count].fe=fVal[1]*(1-fcos)+fVal[2]*fsin;
						matrix[count].ff=fVal[2]*(1-fcos)-fVal[1]*fsin;
						count++;
					}
				}
			}
		}
		else if((pStart=strstr(buffer,"scale("))!=NULL)
		{
			pStart=pStart+6;
			if(strlen(pStart)>0)
			{
				if(SplitStr<float>(pStart,',',fVal,2)==2)
				{
					if(fVal[0]!=1.0f || fVal[1]!=1.0)
					{
						matrix[count].fa=fVal[0];
						matrix[count].fd=fVal[1];
						count++;
					}
				}
			}
		}
		else if((pStart=strstr(buffer,"translate("))!=NULL)
		{
			pStart=pStart+10;
			if(strlen(pStart)>0)
			{
				if(SplitStr<float>(pStart,',',fVal,2)==2)
				{
					if(fVal[0]!=0.0f || fVal[1]!=0.0)
					{
					matrix[count].fa=1.0f;
					matrix[count].fd=1.0f;
					matrix[count].fe=fVal[0];
					matrix[count].ff=fVal[1];
					count++;
					}
				}
			}
		}

		pStart=pEnd;
		pStart++;
		pEnd=strchr(pStart,')');
	}
	if(count>0)
	{
		memcpy(pMatrix,&matrix[count-1],sizeof(MATRIX));
		for(int i=count-2;i>=0;i--)
		{
			MutiMatrix(pMatrix,&matrix[i]);
		}
		return TRUE;
	}

	return FALSE;
}

//返回线
BOOL CSvgBase::GetSvgLine(IXmlNode* pNode,G_LINE* pLine)
{
	const char* pName=NULL;
	const char* pValue=NULL;
	pLine->check=0;
	if(pNode!=NULL && pNode->GetFirstProp())
	{
		while(pNode->GetNextProp(&pName,&pValue))
		{
			if(strcmp(pName,"x1")==0)
			{
				pLine->sp.x=atol(pValue);
				pLine->check|=LEFT_SHIFT00;
			}
			else if(strcmp(pName,"y1")==0)
			{
				pLine->sp.y=atol(pValue);
				pLine->check|=LEFT_SHIFT01;
			}
			else if(strcmp(pName,"x2")==0)
			{
				pLine->ep.x=atol(pValue);
				pLine->check|=LEFT_SHIFT02;
			}
			else if(strcmp(pName,"y2")==0)
			{
				pLine->ep.y=atol(pValue);
				pLine->check|=LEFT_SHIFT03;
			}
			else if(strcmp(pName,"stroke-width")==0)
			{
				pLine->swidth=atof(pValue);
				pLine->check|=LEFT_SHIFT04;
			}
			else if(strcmp(pName,"stroke")==0)
			{
				pLine->lcolor=GetRGB(pValue);
				pLine->check|=LEFT_SHIFT05;
			}
			else if(strcmp(pName,"transform")==0)
			{
				if(GetTransform(pValue,strlen(pValue),&pLine->mx))
					pLine->check|=LEFT_SHIFT06;
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

//返回矩形
BOOL CSvgBase::GetSvgRect(IXmlNode* pNode,G_RECT* pRect)
{
	const char* pName=NULL;
	const char* pValue=NULL;
	pRect->check=0;
	if(pNode!=NULL && pNode->GetFirstProp())
	{
		while(pNode->GetNextProp(&pName,&pValue))
		{
			if(strcmp(pName,"x")==0)
			{
				pRect->lt.x=atof(pValue);
				pRect->check|=LEFT_SHIFT00;
			}
			else if(strcmp(pName,"y")==0)
			{
				pRect->lt.y=atof(pValue);
				pRect->check|=LEFT_SHIFT01;
			}
			else if(strcmp(pName,"height")==0)
			{
				pRect->height=atof(pValue);
				pRect->check|=LEFT_SHIFT02;
			}
			else if(strcmp(pName,"width")==0)
			{
				pRect->width=atof(pValue);
				pRect->check|=LEFT_SHIFT03;
			}
			else if(strcmp(pName,"stroke-width")==0)
			{
				pRect->swidth=atof(pValue);
				pRect->check|=LEFT_SHIFT04;
			}
			else if(strcmp(pName,"stroke")==0)
			{
				pRect->lcolor=GetRGB(pValue);
				pRect->check|=LEFT_SHIFT05;
			}
			else if(strcmp(pName,"fill")==0)
			{
				pRect->fcolor=GetRGB(pValue);
				pRect->check|=LEFT_SHIFT06;
			}
			else if(strcmp(pName,"transform")==0)
			{
				if(GetTransform(pValue,strlen(pValue),&pRect->mx))
					pRect->check|=LEFT_SHIFT07;
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

//返回折线
BOOL CSvgBase::GetSvgPolyl(IXmlNode* pNode,G_POLYLINE* pPolyline)
{
	const char* pName=NULL;
	const char* pValue=NULL;
	pPolyline->check=0;
	if(pNode!=NULL && pNode->GetFirstProp())
	{
		while(pNode->GetNextProp(&pName,&pValue))
		{
			if(strcmp(pName,"points")==0)
			{
				int val[6000];
				pPolyline->ptnum=(int)(SplitStr<int>(pValue,',',val,6000)/2);
				for(int i=0;i<pPolyline->ptnum;i++)
				{
					pPolyline->pt[i].x=val[2*i];
					pPolyline->pt[i].y=val[2*i+1];
				}
				pPolyline->check|=LEFT_SHIFT00;
				pPolyline->check|=LEFT_SHIFT01;
			}
			else if(strcmp(pName,"stroke-width")==0)
			{
				pPolyline->swidth=atof(pValue);
				pPolyline->check|=LEFT_SHIFT02;
			}
			else if(strcmp(pName,"stroke")==0)
			{
				pPolyline->lcolor=GetRGB(pValue);
				pPolyline->check|=LEFT_SHIFT03;
			}
			else if(strcmp(pName,"transform")==0)
			{
				if(GetTransform(pValue,strlen(pValue),&pPolyline->mx))
					pPolyline->check|=LEFT_SHIFT04;
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

//返回多边
BOOL CSvgBase::GetSvgPolyn(IXmlNode* pNode,G_POLYGON* pPolygon)
{
	const char* pName=NULL;
	const char* pValue=NULL;
	pPolygon->check=0;
	if(pNode!=NULL && pNode->GetFirstProp())
	{
		while(pNode->GetNextProp(&pName,&pValue))
		{
			if(strcmp(pName,"points")==0)
			{
				int val[6000];
				pPolygon->ptnum=(int)(SplitStr<int>(pValue,',',val,6000)/2);
				for(int i=0;i<pPolygon->ptnum;i++)
				{
					pPolygon->pt[i].x=val[2*i];
					pPolygon->pt[i].y=val[2*i+1];
				}
				pPolygon->check|=LEFT_SHIFT00;
				pPolygon->check|=LEFT_SHIFT01;
			}
			else if(strcmp(pName,"stroke-width")==0)
			{
				pPolygon->swidth=atof(pValue);
				pPolygon->check|=LEFT_SHIFT02;
			}
			else if(strcmp(pName,"stroke")==0)
			{
				pPolygon->lcolor=GetRGB(pValue);
				pPolygon->check|=LEFT_SHIFT03;
			}
			else if(strcmp(pName,"fill")==0)
			{
				pPolygon->fcolor=GetRGB(pValue);
				pPolygon->check|=LEFT_SHIFT04;
			}
			else if(strcmp(pName,"transform")==0)
			{
				if(GetTransform(pValue,strlen(pValue),&pPolygon->mx))
					pPolygon->check|=LEFT_SHIFT05;
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

//返回圆
BOOL CSvgBase::GetSvgCircle(IXmlNode* pNode,G_CIRCLE* pCircle)
{
	const char* pName=NULL;
	const char* pValue=NULL;
	pCircle->check=0;
	if(pNode!=NULL && pNode->GetFirstProp())
	{
		while(pNode->GetNextProp(&pName,&pValue))
		{
			if(strcmp(pName,"cx")==0)
			{
				pCircle->cp.x=atol(pValue);
				pCircle->check|=LEFT_SHIFT00;
			}
			else if(strcmp(pName,"cy")==0)
			{
				pCircle->cp.y=atol(pValue);
				pCircle->check|=LEFT_SHIFT01;
			}
			else if(strcmp(pName,"r")==0)
			{
				pCircle->r=atof(pValue);
				pCircle->check|=LEFT_SHIFT02;
			}
			else if(strcmp(pName,"stroke-width")==0)
			{
				pCircle->swidth=atof(pValue);
				pCircle->check|=LEFT_SHIFT03;
			}
			else if(strcmp(pName,"stroke")==0)
			{
				pCircle->lcolor=GetRGB(pValue);
				pCircle->check|=LEFT_SHIFT04;
			}
			else if(strcmp(pName,"fill")==0)
			{
				pCircle->fcolor=GetRGB(pValue);
				pCircle->check|=LEFT_SHIFT05;
			}
			else if(strcmp(pName,"transform")==0)
			{
				if(GetTransform(pValue,strlen(pValue),&pCircle->mx))
					pCircle->check|=LEFT_SHIFT06;
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

//返回椭圆
BOOL CSvgBase::GetSvgEllipse(IXmlNode* pNode,G_ELLIPSE* pEllips)
{
	const char* pName=NULL;
	const char* pValue=NULL;
	pEllips->check=0;
	if(pNode!=NULL && pNode->GetFirstProp())
	{
		while(pNode->GetNextProp(&pName,&pValue))
		{
			if(strcmp(pName,"cx")==0)
			{
				pEllips->cp.x=atol(pValue);
				pEllips->check|=LEFT_SHIFT00;
			}
			else if(strcmp(pName,"cy")==0)
			{
				pEllips->cp.y=atol(pValue);
				pEllips->check|=LEFT_SHIFT01;
			}
			else if(strcmp(pName,"rx")==0)
			{
				pEllips->rx=atof(pValue);
				pEllips->check|=LEFT_SHIFT02;
			}
			else if(strcmp(pName,"ry")==0)
			{
				pEllips->ry=atof(pValue);
				pEllips->check|=LEFT_SHIFT03;
			}
			else if(strcmp(pName,"stroke-width")==0)
			{
				pEllips->swidth=atof(pValue);
				pEllips->check|=LEFT_SHIFT04;
			}
			else if(strcmp(pName,"stroke")==0)
			{
				pEllips->lcolor=GetRGB(pValue);
				pEllips->check|=LEFT_SHIFT05;
			}
			else if(strcmp(pName,"fill")==0)
			{
				pEllips->fcolor=GetRGB(pValue);
				pEllips->check|=LEFT_SHIFT06;
			}
			else if(strcmp(pName,"transform")==0)
			{
				if(GetTransform(pValue,strlen(pValue),&pEllips->mx))
					pEllips->check|=LEFT_SHIFT07;
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

//返回文本
BOOL CSvgBase::GetSvgText(IXmlNode* pNode,G_TEXT* pText)
{
	const char* pName=NULL;
	const char* pValue=NULL;
	pText->check=0;
	if(pNode!=NULL && pNode->GetFirstProp())
	{
		while(pNode->GetNextProp(&pName,&pValue))
		{
			if(strcmp(pName,"x")==0)
			{
				pText->lt.x=atol(pValue);
				pText->check|=LEFT_SHIFT00;
			}
			else if(strcmp(pName,"y")==0)
			{
				pText->lt.y=atol(pValue);
				pText->check|=LEFT_SHIFT01;
			}
			else if(strcmp(pName,"font-family")==0)
			{
				if(strlen(pValue)>16)
					return FALSE;
				else
					strcpy(pText->lfFace,pValue);
				pText->check|=LEFT_SHIFT03;
			}
			else if(strcmp(pName,"font-size")==0)
			{
				pText->fsize=atoi(pValue);
				pText->check|=LEFT_SHIFT04;
			}
			else if(strcmp(pName,"stroke")==0)
			{
				pText->lcolor=GetRGB(pValue);
				pText->check|=LEFT_SHIFT05;
			}
			else if(strcmp(pName,"fill")==0)
			{
				pText->fcolor=GetRGB(pValue);
				pText->check|=LEFT_SHIFT06;
			}
			else if(strcmp(pName,"font-style")==0)
			{
				if(strcmp(pValue,"italic")==0)
					pText->italic=1;
				pText->check|=LEFT_SHIFT07;
			}
			else if(strcmp(pName,"text-decoration")==0)
			{
				if(strcmp(pValue,"underline")==0)
					pText->underline=1;
				pText->check|=LEFT_SHIFT08;
			}
			else if(strcmp(pName,"transform")==0)
			{
				if(GetTransform(pValue,strlen(pValue),&pText->mx))
				{
					pText->check|=LEFT_SHIFT09;
				}
			}
			else if(strcmp(pName,"writing-mode")==0)
			{
				if(strstr(pValue,"tb")!=NULL)
				{
					pText->wmode=1;
					pText->check|=LEFT_SHIFT10;
				}
			}
		}

		const char* pValue=pNode->GetValue();
		if(pValue!=NULL && strlen(pValue)>0)
		{
			if(m_byCode==1)//UFT码
				Utf8ToASCII((const unsigned char*)pValue,strlen(pValue),pText->szText,256);
			else
				strcpy(pText->szText,pValue);
			pText->check|=LEFT_SHIFT02;
		}

		return TRUE;
	}
	else
		return FALSE;
}

//返回图像
BOOL CSvgBase::GetSvgImage(IXmlNode* pNode,G_IMAGE* pImage)
{
	const char* pName=NULL;
	const char* pValue=NULL;
	pImage->check=0;
	if(pNode!=NULL && pNode->GetFirstProp())
	{
		while(pNode->GetNextProp(&pName,&pValue))
		{
			if(strcmp(pName,"x")==0)
			{
				pImage->lt.x=atol(pValue);
				pImage->check|=LEFT_SHIFT00;
			}
			else if(strcmp(pName,"y")==0)
			{
				pImage->lt.y=atol(pValue);
				pImage->check|=LEFT_SHIFT01;
			}
			else if(strcmp(pName,"height")==0)
			{
				pImage->height=atof(pValue);
				pImage->check|=LEFT_SHIFT02;
			}
			else if(strcmp(pName,"width")==0)
			{
				pImage->width=atof(pValue);
				pImage->check|=LEFT_SHIFT03;
			}
			else if(strcmp(pName,"xlink:href")==0)
			{
				if(strlen(pValue)>256)
					return FALSE;
				else if(m_byCode==1)//UTF8
					Utf8ToASCII((const unsigned char*)pValue,strlen(pValue),pImage->href,256);
				else
					strcpy(pImage->href,pValue);
				pImage->check|=LEFT_SHIFT04;
			}
			else if(strcmp(pName,"transform")==0)
			{
				if(GetTransform(pValue,strlen(pValue),&pImage->mx))
					pImage->check|=LEFT_SHIFT05;
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

//返回路径
BOOL CSvgBase::GetSvgPath(IXmlNode* pNode,G_PATH* pPath)
{
	const char* pName=NULL;
	const char* pValue=NULL;
	pPath->check=0;
	if(pNode!=NULL && pNode->GetFirstProp())
	{
		while(pNode->GetNextProp(&pName,&pValue))
		{
			if(strcmp(pName,"d")==0)
			{
				if(strlen(pValue)>256)
					return FALSE;
				else
					strcpy(pPath->szPath,pValue);
				pPath->check|=LEFT_SHIFT00;
			}
			else if(strcmp(pName,"class")==0)
			{
				if(strlen(pValue)>32)
					return FALSE;
				else
					strcpy(pPath->rclass,pValue);
				pPath->check|=LEFT_SHIFT01;
			}
			else if(strcmp(pName,"stroke-width")==0)
			{
				pPath->swidth=atof(pValue);
				pPath->check|=LEFT_SHIFT02;
			}
			else if(strcmp(pName,"stroke")==0)
			{
				pPath->lcolor=GetRGB(pValue);
				pPath->check|=LEFT_SHIFT03;
			}
			else if(strcmp(pName,"fill")==0)
			{
				pPath->fcolor=GetRGB(pValue);
				pPath->check|=LEFT_SHIFT04;
			}
			else if(strcmp(pName,"transform")==0)
			{
				if(GetTransform(pValue,strlen(pValue),&pPath->mx))
					pPath->check|=LEFT_SHIFT05;
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

DWORD CSvgBase::GetRGB(const char *pRGB)
{
	DWORD color=0;
	char *pSrc=strstr(pRGB,"rgb(");
	if(pSrc!=NULL)
	{
		int rgb[3]={0};
		char buff[32];
		strcpy(buff,pSrc+4);
		pSrc=strchr(buff,')');
		if(pSrc!=NULL)
			*pSrc=0;
		
		SplitStr<int>(buff,',',rgb,3);
		color=RGB(rgb[0],rgb[1],rgb[2]);
	}
	else
	{
		pSrc=strstr(pRGB,"grey");
		if(pSrc!=NULL)
			color=RGB(127,127,127);
	}
	return color;
}

//取得图元
BOOL CSvgBase::GetSymbol(IXmlNode *pNode)
{
	if(pNode!=NULL && pNode->GetFirstSubNode())
	{
		const char* pidnm=pNode->GetPropValue("id");
		if(pidnm==NULL)
			return FALSE;

		CFigureGroup* pGrp=new CFigureGroup(pidnm);
		IXmlNode* pGphNode=NULL;
		while((pGphNode=pNode->GetNextSubNode())!=NULL)
		{
			FIGUREVTR figVtr;
			if(GetFigure(pGphNode,&figVtr))
			{
				for(FIGUREVTR::iterator itr=figVtr.begin();itr!=figVtr.end();++itr)
					pGrp->AddFigure(*itr);
			}
		}

		//插入排序
		for(FIGUREGRPVTR::iterator itr=m_FigureGrpVtr.begin();itr!=m_FigureGrpVtr.end();++itr)
		{
			if((*itr)->CompareName(pidnm)>0)
			{
				m_FigureGrpVtr.insert(itr,pGrp);
				break;
			}
		}		
		if(itr==m_FigureGrpVtr.end())//空或最大添到后面
			m_FigureGrpVtr.push_back(pGrp);
	}
	return TRUE;
}

//返回图形
BOOL CSvgBase::GetFigure(IXmlNode* pNode,FIGUREVTR* pFigVtr)
{
	if(pNode==NULL || pFigVtr==NULL)
		return FALSE;

	if(pNode->IsKindof(graphkey[GTYPE_LINE]))//线
	{
		G_LINE graph;
		if(GetSvgLine(pNode,&graph))
		{
			CFigure fig(GTYPE_LINE,&graph,sizeof(G_LINE));
			pFigVtr->push_back(fig);
		}
	}
	else if(pNode->IsKindof(graphkey[GTYPE_POLYL]))//折线
	{
		G_POLYLINE graph;
		if(GetSvgPolyl(pNode,&graph))
		{
			CFigure fig(GTYPE_POLYL,&graph,sizeof(G_POLYLINE));
			pFigVtr->push_back(fig);
		}
	}
	else if(pNode->IsKindof(graphkey[GTYPE_PATH]))//路径
	{
		G_PATH graph;
		if(GetSvgPath(pNode,&graph))
		{
			CSS_STYLE* pCss=NULL;
			const char* pClass=pNode->GetPropValue("class");
			if(pClass!=NULL)
			{
				pCss=SearchCssStyle(pClass);
				graph.lcolor = pCss->lcolor;
			}

			GetPathFigure(&graph,pFigVtr);
		}
	}
	else if(pNode->IsKindof(graphkey[GTYPE_POLYG]))//多边形
	{
		G_POLYGON graph;
		if(GetSvgPolyn(pNode,&graph))
		{
			CFigure fig(GTYPE_POLYG,&graph,sizeof(G_POLYGON));
			pFigVtr->push_back(fig);
		}
	}
	else if(pNode->IsKindof(graphkey[GTYPE_RECT]))//矩形
	{
		G_RECT graph;
		if(GetSvgRect(pNode,&graph))
		{
			CFigure fig(GTYPE_RECT,&graph,sizeof(G_RECT));
			pFigVtr->push_back(fig);
		}
	}
	else if(pNode->IsKindof(graphkey[GTYPE_CIRCLE]))//圆
	{
		G_CIRCLE graph;
		if(GetSvgCircle(pNode,&graph))
		{
			CFigure fig(GTYPE_CIRCLE,&graph,sizeof(G_CIRCLE));
			pFigVtr->push_back(fig);
		}
	}
	else if(pNode->IsKindof(graphkey[GTYPE_ELLIPSE]))//椭圆
	{
		G_ELLIPSE graph;
		if(GetSvgEllipse(pNode,&graph))
		{
			CFigure fig(GTYPE_ELLIPSE,&graph,sizeof(G_ELLIPSE));
			pFigVtr->push_back(fig);
		}
	}
	else if(pNode->IsKindof(graphkey[GTYPE_TEXT]))//文本
	{
		G_TEXT graph;
		if(GetSvgText(pNode,&graph))
		{
			CFigure fig(GTYPE_TEXT,&graph,sizeof(G_TEXT));
			pFigVtr->push_back(fig);
		}
	}
	else if(pNode->IsKindof(graphkey[GTYPE_IMAGE]))//图像
	{
		G_IMAGE graph;
		if(GetSvgImage(pNode,&graph))
		{
			CFigure fig(GTYPE_IMAGE,&graph,sizeof(G_IMAGE));
			pFigVtr->push_back(fig);
		}
	}
	else if(pNode->IsKindof("use"))//调用其他图元，一般是端子
	{
		G_GUSE graph;
		if(GetSvgSymUse(pNode,&graph))
		{
			CFigure fig(GTYPE_GUSE,&graph,sizeof(G_GUSE));
			pFigVtr->push_back(fig);
		}
	}
	else if(pNode->IsKindof("a"))//超连接
	{
		char pValue[256]={0};
		const char* pHref=pNode->GetPropValue("xlink:href");
		if(pHref!=NULL)
		{
			strcpy(pValue,pHref);
			if(strlen(pHref)<256 && m_byCode==1)
				Utf8ToASCII((const unsigned char*)pValue,strlen(pValue),pValue,256);
		}

		if(pNode->GetFirstSubNode())
		{
			IXmlNode* pLink=pNode->GetNextSubNode();
			if(pLink!=NULL)
			{
				FIGUREVTR figVtr;
				if(GetFigure(pLink,&figVtr))
				{
					for(FIGUREVTR::iterator itr=figVtr.begin();itr!=figVtr.end();++itr)
					{
						if(strlen(pValue)>0)
							(*itr).SetHref(pValue);
						pFigVtr->push_back(*itr);
					}
				}
			}
		}		 
	}
	else
		return FALSE;
	return TRUE;
}

//处理电压等级
BOOL CSvgBase::GetStyle(IXmlNode *pNode)
{
	IXmlNode* pStyleNode=pNode->GetSubNodeByFlag("![CDATA",NULL);
	if(pStyleNode!=NULL)
	{
		int len=0;
		char buffer[256];
		const char* pStyle=pStyleNode->GetValue();
		const char* pStart=NULL;
		while(strlen(pStyle)>0)
		{
			char* pEnd=strchr(pStyle,'{');
			if(pEnd!=NULL)
			{
				len=pEnd-pStyle;
				strncpy(buffer,pStyle,len);
				buffer[len]=0;
				//清除空格
				while(buffer[len-1]==' ')
				{
					buffer[len-1]=0;
					len--;
				}
				pStart=buffer;
				pEnd++;

				CSS_STYLE style;
				if(strlen(pStyle)>0)
				{
					if((pStart=strchr(pStart,'.'))!=NULL)
						pStart++;

					style.descr=pStart;
					GetVolLevelByStyle(pStart,style.vVol);
					pStyle=pEnd;

					pEnd=strstr(pStyle,"stroke:");
					if(pEnd!=NULL)
					{
						pEnd+=7;
						pStyle=pEnd;
						pEnd=strchr(pStyle,';');
						if(pEnd!=NULL)
						{
							len=pEnd-pStyle;
							strncpy(buffer,pStyle,len);
							buffer[len]=0;

							style.lcolor=GetRGB(buffer);
							pEnd++;
							pStyle=pEnd;
						}
					}

					pEnd=strstr(pStyle,"fill:");
					if(pEnd!=NULL)
					{
						pEnd+=5;
						pStyle=pEnd;
						pEnd=strchr(pStyle,'}');
						if(pEnd!=NULL)
						{
							len=pEnd-pStyle;
							strncpy(buffer,pStyle,len);
							buffer[len]=0;

							style.fcolor=GetRGB(buffer);
							pEnd++;
							pStyle=pEnd;
						}
					}
					//插入排序
					for(CSSSTYLEVTR::iterator itr=m_CssStyleVtr.begin();itr!=m_CssStyleVtr.end();++itr)
					{
						if((*itr).descr.compare(style.descr)>0)
						{
							m_CssStyleVtr.insert(itr,style);
							break;
						}
					}					
					if(itr==m_CssStyleVtr.end())//空或最大添到后面
						m_CssStyleVtr.push_back(style);
				}
				else
					pStyle++;
			}
			else
				pStyle++;
		}

		return TRUE;
	}
	return FALSE;
}

BOOL CSvgBase::GetLayer(IXmlNode *pNode)
{
	if(pNode==NULL)
		return FALSE;

	const char* pLayerName=pNode->GetPropValue("id");
	char layername[64]={0};
	strcpy(layername,pLayerName);
	strupr(layername);
	if(strstr(layername,"LAYER")!=NULL)
	{
		CLayer* pLayer=new CLayer(pLayerName);
		m_LayerVtr.push_back(pLayer);
		if(pNode->GetFirstSubNode())
		{
			IXmlNode* pGphNode=NULL;
			while((pGphNode=pNode->GetNextSubNode())!=NULL)
			{
				if(pGphNode->IsKindof("g"))
				{
					const char* pid=pGphNode->GetPropValue("id");
					CGraph* pg=new CGraph(pid);
					GetGraph(pGphNode,pg);
					pLayer->AddGraph(pg);
				}
				else
				{
					FIGUREVTR figVtr;
					if(GetFigure(pGphNode,&figVtr))
					{
						for(FIGUREVTR::iterator itr=figVtr.begin();itr!=figVtr.end();++itr)
						{
							pLayer->AddFigure(*itr);
						}
					}
				}
			}
		}
	}
	return TRUE;
}

BOOL CSvgBase::GetGraph(IXmlNode *pNode,CGraph* pg)
{
	if(pg==NULL || pNode==NULL)
		return FALSE;

	//变换
	const char* pTrans=pNode->GetPropValue("transform");
	if(pTrans!=NULL)
	{
		MATRIX mx;
		if(GetTransform(pTrans,strlen(pTrans),&mx))
		{
			pg->SetFigureMatrix(&mx);
		}
	}
	//类
	const char* pVal=pNode->GetPropValue("class");
	if(pVal!=NULL)
	{
		CSS_STYLE* pClass=SearchCssStyle(pVal);
		pg->SetClass(pClass);
	}


	//子节点
	if(pNode->GetFirstSubNode())
	{
		IXmlNode* pSubNode=NULL;
		while((pSubNode=pNode->GetNextSubNode())!=NULL)
		{
			if(pSubNode->IsKindof("g"))//嵌套图
			{
				const char* pid=pSubNode->GetPropValue("id");
				CGraph* g=new CGraph(pid);
				GetGraph(pSubNode,g);
				pg->AddGraph(g);
			}
			else if(pSubNode->IsKindof("use"))//use
			{
				GetUse(pSubNode,pg);
			}
			else if(pSubNode->IsKindof("metadata"))//metadata
			{
				GetMetaData(pSubNode,pg);
				
			}
			else//一般图形
			{
				FIGUREVTR figVtr;
				if(GetFigure(pSubNode,&figVtr))
				{
					CSS_STYLE* pCss=NULL;
					const char* pClass=pSubNode->GetPropValue("class");
					if(pClass!=NULL)
					{
						pCss=SearchCssStyle(pClass);
						pg->SetClass(pCss);
					}

					for(FIGUREVTR::iterator itr=figVtr.begin();itr!=figVtr.end();++itr)
					{
						if(pCss!=NULL)
							(*itr).SetClass(pCss);

						pg->AddFigure(*itr);
					}
				}
			}
		}
	}
	return TRUE;
}

BOOL CSvgBase::GetMetaData(IXmlNode *pNode,CGraph* pg)
{
	if(pNode==NULL || pg==NULL)
		return FALSE;

	const char* pID=NULL;
	const char* pName=NULL;
	IXmlNode* pSubNode=pNode->GetSubNodeByFlag("cge:PSR_Ref",NULL);
	if(pSubNode!=NULL)
	{
		pID=pSubNode->GetPropValue("ObjectID");
		if(pID==NULL)
			pID=pSubNode->GetPropValue("ObjectId");
		pName=pSubNode->GetPropValue("ObjectName");

		char szName[256]={0};
		Utf8ToASCII((const unsigned char*)pName,strlen(pName),szName,256);

		if(pID!=NULL || pName!=NULL)
		{
			pg->SetPSRRef(pID,szName);
		}
	}

	pSubNode=pNode->GetSubNodeByFlag("cge:Meas_Ref",NULL);
	if(pSubNode!=NULL)
	{
		pID=pSubNode->GetPropValue("ObjectID");
		if(pID==NULL)
			pID=pSubNode->GetPropValue("ObjectId");
		pName=pSubNode->GetPropValue("ObjectName");
		if(pID!=NULL && pName!=NULL)
		{
			pg->SetMeasRef(pID,pName);
		}
	}
	return TRUE;
}

BOOL CSvgBase::GetUse(IXmlNode *pNode,CGraph* pg)
{
	if(pg==NULL || pNode==NULL)
		return FALSE;

	const char* pName=NULL;
	const char* pValue=NULL;
	if(pNode->GetFirstProp())
	{
		CRect rt;
		unsigned int check=0;
		int val[4]={0};
		while(pNode->GetNextProp(&pName,&pValue))
		{
			if(strcmp(pName,"x")==0)
			{
				val[0]=atoi(pValue);
				check|=LEFT_SHIFT00;
			}
			else if(strcmp(pName,"y")==0)
			{
				val[1]=atoi(pValue);
				check|=LEFT_SHIFT01;
			}
			else if(strcmp(pName,"width")==0)
			{
				val[2]=atoi(pValue);
				check|=LEFT_SHIFT02;
			}
			else if(strcmp(pName,"height")==0)
			{
				val[3]=atoi(pValue);
				check|=LEFT_SHIFT03;
			}
			else if(strcmp(pName,"transform")==0)
			{
				MATRIX mx;
				if(GetTransform(pValue,strlen(pValue),&mx))
				{
					mx.fe=mx.fe;
					mx.ff=mx.ff;
					pg->SetFigureMatrix(&mx);
					check|=LEFT_SHIFT04;
				}
			}
			else if(strcmp(pName,"class")==0)
			{
				CSS_STYLE* pClass=SearchCssStyle(pValue);
				pg->SetClass(pClass);
				check|=LEFT_SHIFT05;
			}
			else if(strcmp(pName,"xlink:href")==0)
			{
				pValue++;	
				CFigureGroup* pGroup=SearchFigureGroup(pValue);
				if(pGroup!=NULL)
				{
					pGroup->GetGroupRect(rt);
					pg->SetFigureGroup(pGroup);
					check|=LEFT_SHIFT06;
				}
			}
		}
		if(check & 0x0f==0x0f)
		{
			CRect rect(val[0],val[1],val[0]+val[2],val[1]+val[3]);
			pg->SetFigureRect(&rect);
		}
	}
	return TRUE;
}

//查找图元
CFigureGroup* CSvgBase::SearchFigureGroup(const char *pid)
{
	if(m_FigureGrpVtr.size()>0)
	{
		long lMin=0;
		long lMax=m_FigureGrpVtr.size()-1;
		while(lMin<=lMax)
		{
			long lHalf=(lMax+lMin)/2;
			if(lHalf>=0)
			{
				int cmp=m_FigureGrpVtr[lHalf]->CompareName(pid);
				if(cmp<0)
					lMin=lHalf+1;
				else if(cmp>0)
					lMax=lHalf-1;
				else
					return m_FigureGrpVtr[lHalf];
			}
			else
				break;
		}
	}
	return NULL;	
}

//查找class
CSS_STYLE* CSvgBase::SearchCssStyle(const char *pClass)
{
	if(m_CssStyleVtr.size()>0)
	{
		long lMin=0;
		long lMax=m_CssStyleVtr.size()-1;
		while(lMin<=lMax)
		{
			long lHalf=(lMax+lMin)/2;
			if(lHalf>=0)
			{
				int cmp=strcmp(m_CssStyleVtr[lHalf].descr.c_str(),pClass);
				if(cmp<0)
					lMin=lHalf+1;
				else if(cmp>0)
					lMax=lHalf-1;
				else
					return &m_CssStyleVtr[lHalf];
			}
			else
				break;
		}
	}
	return NULL;	
}

BOOL CSvgBase::GetSvgSymUse(IXmlNode *pNode, G_GUSE *pGUse)
{
	const char* pName=NULL;
	const char* pValue=NULL;
	pGUse->check=0;
	if(pNode!=NULL && pNode->GetFirstProp())
	{
		while(pNode->GetNextProp(&pName,&pValue))
		{
			if(strcmp(pName,"x")==0)
			{
				pGUse->lt.x=atol(pValue);
				pGUse->check|=LEFT_SHIFT00;
			}
			else if(strcmp(pName,"y")==0)
			{
				pGUse->lt.y=atol(pValue);
				pGUse->check|=LEFT_SHIFT01;
			}
			else if(strcmp(pName,"xlink:href")==0)
			{
				if(pValue[0]=='#')
					pValue++;
				pGUse->use=SearchFigureGroup(pValue);
				pGUse->check|=LEFT_SHIFT02;
			}
			else if(strcmp(pName,"transform")==0)
			{
				if(GetTransform(pValue,strlen(pValue),&pGUse->mx))
					pGUse->check|=LEFT_SHIFT03;
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

BOOL CSvgBase::GetVolLevelByStyle(const char *pStype,BYTE &volLevel)
{
	int count=sizeof(cvlevel)/sizeof(char*);
	for(int i=0;i<count;i++)
	{
		if(strstr(pStype,cvlevel[i])!=NULL)
		{
			volLevel=i;
			return TRUE;
		}
	}
	return FALSE;
}

//路径图形暂时处理成弧和折线
BOOL CSvgBase::GetPathFigure(G_PATH *path,FIGUREVTR* pFigVtr)
{
	PATHINFO info[32];
	int Count=GetPathInfo(path->szPath,info, 32);

	POINT ptStart,ptEnd;
	POINT dpt[64];
	int dpts=0;
	for(int i=0;i<Count;i++)
	{
		if(info[i].cmd=='M' && info[i].byCnt==2)
		{
			ptStart.x=(int)info[i].argv[0];
			ptStart.y=(int)info[i].argv[1];
		}
		else if(info[i].cmd=='Z')
		{
			if(dpts==0)
			{
				dpt[dpts].x=(int)ptStart.x;
				dpt[dpts++].y=(int)ptStart.y;
				dpt[dpts].x=(int)ptEnd.x;
				dpt[dpts++].y=(int)ptEnd.y;
			}
			else
			{
				dpt[dpts].x=(int)ptStart.x;
				dpt[dpts].y=(int)ptStart.y;
				if(dpts<64)
					dpts++;
			}
		}
		else if(info[i].cmd=='L' && info[i].byCnt==2)
		{
			if(dpts==0)
			{
				dpt[dpts].x=ptStart.x;
				dpt[dpts++].y=ptStart.y;
			}
			dpt[dpts].x=(int)info[i].argv[0];
			dpt[dpts].y=(int)info[i].argv[1];
			if(dpts<64)
				dpts++;
		}
		else if(info[i].cmd=='H' && info[i].byCnt==1)
		{
			if(dpts==0)
			{
				dpt[dpts].x=ptStart.x;
				dpt[dpts++].y=ptStart.y;
			}
			dpt[dpts].x=dpt[dpts-1].x+(int)info[i].argv[0];
			dpt[dpts].y=dpt[dpts-1].y;
			if(dpts<64)
				dpts++;
		}
		else if(info[i].cmd=='V' && info[i].byCnt==1)
		{
			if(dpts==0)
			{
				dpt[dpts].x=ptStart.x;
				dpt[dpts++].y=ptStart.y;
			}
			dpt[dpts].x=dpt[dpts-1].x;
			dpt[dpts].y=dpt[dpts-1].y+(int)info[i].argv[0];
			if(dpts<64)
				dpts++;
		}
		else if(info[i].cmd=='A' && info[i].byCnt==7)
		{
			G_ARC arc;
			arc.sp.x=ptStart.x;
			arc.sp.y=ptStart.y;
			arc.check|=LEFT_SHIFT00;
			arc.rx=(int)info[i].argv[0];
			arc.check|=LEFT_SHIFT01;
			arc.ry=(int)info[i].argv[1];
			arc.check|=LEFT_SHIFT02;
			arc.xaixsr=info[i].argv[2];
			arc.check|=LEFT_SHIFT03;
			arc.larc=(BYTE)info[i].argv[3];
			arc.check|=LEFT_SHIFT04;
			arc.sweep=(int)info[i].argv[4];
			arc.check|=LEFT_SHIFT05;
			arc.ep.x=ptEnd.x=info[i].argv[5];
			arc.ep.y=ptEnd.y=info[i].argv[6];
			arc.check|=LEFT_SHIFT06;
			arc.swidth=path->swidth;
			arc.check|=LEFT_SHIFT07;
			arc.lcolor=path->lcolor;
			arc.check|=LEFT_SHIFT08;
			arc.fcolor=path->fcolor;
			arc.check|=LEFT_SHIFT09;
			if(GetArcCenter(&arc.sp,&arc.ep,arc.rx,arc.ry, arc.larc,arc.sweep, arc.center))
				arc.check|=LEFT_SHIFT10;
			if((path->check & LEFT_SHIFT05)==LEFT_SHIFT05)
			{
				memcpy(&arc.mx,&path->mx,sizeof(MATRIX));
				arc.check|=LEFT_SHIFT11;
			}

			CFigure fig(GTYPE_ARC,&arc,sizeof(G_ARC));
			pFigVtr->push_back(fig);

			if(dpts>0)
			{
				G_POLYLINE poly;
				memcpy(poly.pt,dpt,sizeof(POINT)*dpts);
				poly.ptnum=dpts;
				poly.check|=LEFT_SHIFT00;
				poly.swidth=path->swidth;
				poly.check|=LEFT_SHIFT02;
				poly.lcolor=path->lcolor;
				poly.check|=LEFT_SHIFT03;
				if((path->check & LEFT_SHIFT05)==LEFT_SHIFT05)
				{
					memcpy(&poly.mx,&path->mx,sizeof(MATRIX));
					poly.check|=LEFT_SHIFT05;
				}

				CFigure fig2(GTYPE_POLYL,&poly,sizeof(G_POLYLINE));
				pFigVtr->push_back(fig2);

				ptStart=ptEnd;
				dpts=0;
			}
		}
	}
	if(dpts>1)//添加折线
	{
		G_POLYLINE poly;
		memcpy(poly.pt,dpt,sizeof(POINT)*dpts);
		poly.ptnum=dpts;
		poly.check|=LEFT_SHIFT00;
		poly.check|=LEFT_SHIFT01;
		poly.swidth=path->swidth;
		poly.check|=LEFT_SHIFT02;
		poly.lcolor=path->lcolor;
		poly.check|=LEFT_SHIFT03;
		if((path->check & LEFT_SHIFT05)==LEFT_SHIFT05)
		{
			memcpy(&poly.mx,&path->mx,sizeof(MATRIX));
			poly.check|=LEFT_SHIFT04;
		}
		
		CFigure fig2(GTYPE_POLYL,&poly,sizeof(G_POLYLINE));
		pFigVtr->push_back(fig2);
	}
	return TRUE;
}

int CSvgBase::GetPathInfo(const char* pPath,PATHINFO *pInfo, int max)
{
	char* lp=strstr(pPath,"d=");
	if(lp!=NULL)
		lp+=3;
	else
		lp=(char*)pPath;

	int iRet=0;
	char* pStart=NULL;
	while(1)
	{
		if(IsLetter(*lp))
		{
			pInfo[iRet].cmd=*lp;

			iRet++;
			if(iRet>=max)
				break;
			pStart=NULL;
		}
		else if(*lp==' '||*lp==',')
		{
			if(pStart!=NULL && iRet>0 && pInfo[iRet-1].byCnt<16)
			{
				pInfo[iRet-1].argv[pInfo[iRet-1].byCnt++]=(float)atof(pStart);
			}
			pStart=NULL;
		}
		else if(pStart==NULL && IsNumber(*lp))
		{
			pStart=lp;
		}

		lp++;
		if(lp==NULL|| strlen(lp)==0 || *lp=='"')
		{
			if(pStart!=NULL && iRet>0 && pInfo[iRet-1].byCnt<16)
				pInfo[iRet-1].argv[pInfo[iRet-1].byCnt++]=(float)atof(pStart);
			break;
		}
	}
	return iRet;
}

BOOL CSvgBase::PolyOneGroup(CFigureGroup* pGroup,FIGUREELE* pEle)
{
	if(pGroup==NULL)
		return FALSE;

	BOOL bReturn=FALSE;
	char szGName[64]={0};
//	char pText[64]={0};
	strcpy(szGName,pGroup->GetGroupName());

//	Utf8ToASCII((const unsigned char*)szGName,strlen(szGName),pText,64);

	char* pFlag=strchr(szGName,'_');
	if(pFlag!=NULL)
	{
		pFlag++; *pFlag=0;

		for(FIGUREGRPVTR::iterator itr=m_FigureGrpVtr.begin();itr!=m_FigureGrpVtr.end();++itr)
		{
			if((*itr)->m_pGroupParent!=NULL || pGroup==(*itr))
				continue;

			if(strstr((*itr)->GetGroupName(),szGName)!=NULL)
			{
				if((*itr)->GetFirstFigure())
				{
					CFigure *pFigure=NULL;
					while((pFigure=(*itr)->GetNextFigure())!=NULL)
					{
						pGroup->AddFigure(*pFigure);
					}
				}
				pEle->pGrp0=pGroup;
				pEle->pGrp1=pGroup;
				pGroup->m_pGroupParent=pEle;
				(*itr)->m_pGroupParent=pEle;
				bReturn=TRUE;
			}
		}
	}
	
	return bReturn;
}

BOOL CSvgBase::PolyOneGroup(CFigureGroup* pGroup,char* pFalse,char* pTrue,FIGUREELE* pEle)
{
	if(pGroup==NULL)
		return FALSE;

	const char* pGName=pGroup->GetGroupName();
	char* pOpen=strstr(pGName,pFalse);
	char* pClose=strstr(pGName,pTrue);

	CRect rt;
	char szGName[64]={0};
	if(pOpen!=NULL && pOpen!=pGName)
	{
		strncpy(szGName,pGName,pOpen-pGName);
		strcat(szGName,pTrue);
		for(FIGUREGRPVTR::iterator itr=m_FigureGrpVtr.begin();itr!=m_FigureGrpVtr.end();++itr)
		{
			if((*itr)->m_pGroupParent!=NULL || pGroup==(*itr))
				continue;
			if(strcmp((*itr)->GetGroupName(),szGName)==0)
			{
				pEle->pGrp0=pGroup;
				pEle->pGrp1=*itr;

				pGroup->m_pGroupParent=pEle;
				(*itr)->m_pGroupParent=pEle;
				if(pEle->pGrp1!=NULL && pEle->pGrp1->GetFirstFigure())
				{
					CFigure* pFigure=NULL;
					while((pFigure=pEle->pGrp1->GetNextFigure())!=NULL)
					{
						if(pFigure->IsKindOf()==GTYPE_RECT)
						{
							pFigure->SetFullColor(RGB(255,0,0));
						}
					}
				}
				return TRUE;
			}
		}
	}
	else if(pClose!=NULL && pClose!=pGName)
	{
		strncpy(szGName,pGName,pClose-pGName);
		strcat(szGName,pFalse);
		for(FIGUREGRPVTR::iterator itr=m_FigureGrpVtr.begin();itr!=m_FigureGrpVtr.end();++itr)
		{
			if((*itr)->m_pGroupParent!=NULL)
				continue;
			if(strcmp((*itr)->GetGroupName(),szGName)==0)
			{
				pEle->pGrp0=*itr;
				pEle->pGrp1=pGroup;
				pGroup->m_pGroupParent=pEle;
				(*itr)->m_pGroupParent=pEle;
				if(pEle->pGrp1!=NULL && pEle->pGrp1->GetFirstFigure())
				{
					CFigure* pFigure=NULL;
					while((pFigure=pEle->pGrp1->GetNextFigure())!=NULL)
					{
						if(pFigure->IsKindOf()==GTYPE_RECT)
						{
							pFigure->SetFullColor(RGB(255,0,0));
						}
					}
				}
				return TRUE;
			}
		}
	}
	return FALSE;
}

