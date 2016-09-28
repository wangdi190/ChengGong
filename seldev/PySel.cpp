// PySel.cpp: implementation of the PySel class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "seldev.h"
#include "PySel.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif




int areacode[] = {45217,45253,45761,46318,46826,47010,47297,47614,48119,48119,49062,49324,49896,
				  50371,50614,50622,50906,51387,51446,52218,52698,52698,52698,52980,53689,54481,
				  55290};
//拼音选择的类
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PySel::PySel()
{

}

PySel::~PySel()
{

}

//是否符合本串
bool PySel::IsThisPy(char *inchar,char *str)
{
	int i,n,m;
	int a,c;
	MYHZ   zf[10],zf1[10];
	strlwr(inchar);
	m=GetWORD(zf,str);
	n=GetWORD(zf1,inchar);
	n=n>m ? m:n;
	for(i=0;i<n;i++)
	{
		switch(zf1[i].type)
		{
		case 0: //字母或拼音
			a=zf1[i].hz;
			c=zf[i].type==0 ? zf[i].hz:GetIndex(zf[i].hz);
			if(c!=a) return false;
			break;
		case 1: //汉字
			if(zf[i].type!=1) return false;
			if(zf[i].hz!=zf1[i].hz) return false;
			break;
		}
	}
	return true;
}

//返回汉字或字符
int PySel::GetWORD(MYHZ *zf,char *str1)
{
	int n,i=0;
	BYTE  *str=(BYTE*)str1;
	char buf[10];
	buf[1]=0;
	n=0;

	for(;;)
	{
		if(n>=10)			return n;
		if(str[i]==0)		return n;
		
		if(isprint(str[i])) //如果是a-z字母
		{
			zf[n].type=0;
			buf[0]=str[i];
			if(isprint(str[i])) strlwr(buf);
			zf[n].hz=buf[0];
			i++;
		
		}else   //是汉字或其他字符
		{
			if(str[i]&0x80==0)		return n;
			if(str[i+1]==0)			return n;
			if(str[i+1]&0x80==0)	return n;
			zf[n].type=1;
			zf[n].hz=(WORD)MAKEWORD(str[i+1],str[i]);
			i=i+2;
		}
		n++;
	}
	return 0;
}


int PySel::GetIndex(int v)
{
	int i;
	for(i=0;i<26;i++)
	{
		if(v>=areacode[i]&&v<areacode[i+1]) return i+'a';
	}
	return 25+'a'; //都不是，认为是Z字符
}