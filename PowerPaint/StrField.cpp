// StrField.cpp: implementation of the StrField class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerPaint.h"
#include "StrField.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

StrField::StrField()
{
	fldsum=0;
}

StrField::~StrField()
{

}

//设置一个新串，并返回域个数
int StrField::SetNewStr(char *str)
{
	char *lp;
	fldsum=1;
	lpt[0]=str; //第一个为起始点
	lp=str;
	for(;;)
	{
		if(*lp==0) break;
		if(*lp==',')
		{
			*lp=0;
			lp++;
			lpt[fldsum]=lp;
			fldsum++;
			continue;
		}
		lp++;
	}
	return fldsum;
}
