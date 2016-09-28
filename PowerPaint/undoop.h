// undoop.h: interface for the undoop class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_UNDOOP_H__851DE31B_5C2C_4795_94E8_C78FBFCC65C7__INCLUDED_)
#define AFX_UNDOOP_H__851DE31B_5C2C_4795_94E8_C78FBFCC65C7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "gdata.h"


class undoop  
{
public:
	void UnDOAStep();
	void AddAUndoOp(N_BASATTR &attr, void *obuf,BYTE type);
	void AddAUndoOp(BYTE type);
	void FreeMem();
	undoop();
	virtual ~undoop();
	UNDOSTEP ustp[MAXUNDO];	//可以MAXUNDO步
	int curstep;			//当前步骤
private:
	void FreeAMem(int i);
	void AddUndoObj(BASE0&bs,int i);

};

#endif // !defined(AFX_UNDOOP_H__851DE31B_5C2C_4795_94E8_C78FBFCC65C7__INCLUDED_)
