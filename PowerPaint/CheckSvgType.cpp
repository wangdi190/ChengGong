// CheckSvgType.cpp: implementation of the CCheckSvgType class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerPaint.h"
#include "CheckSvgType.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCheckSvgType::CCheckSvgType()
{
	lbuf=NULL;			//行缓冲区
	lbmax=0;
	fp=NULL;
	type=0;
}

CCheckSvgType::~CCheckSvgType()
{
	if(fp!=NULL) fclose(fp);
	if(lbuf!=NULL) free(lbuf);
}

int CCheckSvgType::GetSvgType(char *svgfilename)
{
	fp=fopen(svgfilename,"r+b");
	if(fp==NULL) return -1;
	CheckType();
	fclose(fp);
	fp=NULL;
	return type;
}

int CCheckSvgType::ReadALine()
{
	int c;
	int s1=0;
	//第一次缓冲区申请
	if(lbmax<100) 
	{
		lbuf=new char[128];
		lbmax=128;
		if(lbuf==NULL) return -2;
	}
	//寻找行首字符"<"，过滤掉中间的无用字符
	for(;;)
	{
		if(feof(fp)) return -1;
		c=fgetc(fp);
		if(c!='<') continue;
		lbuf[s1]=c;
		s1=1;
		break;
	}
	//读取后续内容
	for(;;)
	{
		if(s1>=(lbmax-2))
		{
			lbmax=lbmax+128;
			lbuf=(char*)realloc(lbuf,lbmax);
			if(lbuf==NULL) return -2;
		};
		if(feof(fp)) return  -1;
		c=fgetc(fp);
		if(c==0xd||c==0xa||c==9) continue;
		lbuf[s1]=c;
		s1++;
		if(c=='>')	break;
	}
	lbuf[s1]=0;
	return s1;
}


void CCheckSvgType::CheckType()
{
	int i,m;
	for(i=0;i<30;i++)
	{
		m=ReadALine(); //读一个标准行
		if(m<0) break;
		if(strcmp(lbuf,"<!--Visual system By SICUAN UNIVERSITY  PowerGroup-->")==0)
		{
			type=1;
			break;
		}
	}
}