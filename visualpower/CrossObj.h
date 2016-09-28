// CrossObj.h: interface for the CCrossObj class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CROSSOBJ_H__404083ED_C5B6_4B9C_BB0B_25BC322CBE92__INCLUDED_)
#define AFX_CROSSOBJ_H__404083ED_C5B6_4B9C_BB0B_25BC322CBE92__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "pwptdef.h"
#include "gdata.h"

class CCrossObj  
{
public:
	bool GetCrossLine(DMSECT&dm);
	CCrossObj();
	virtual ~CCrossObj();
	RFLOW *r_fw;	//潮流线
	int fwsum;		//个数
	POINT *pt;		//截面点
	int   segsum;
	int   *dmdot;
	gdata *dbm;		//数据库指针
};

#endif // !defined(AFX_CROSSOBJ_H__404083ED_C5B6_4B9C_BB0B_25BC322CBE92__INCLUDED_)
