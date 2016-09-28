// MemdbClass.cpp: implementation of the CMemdbClass class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemdbClass.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif


//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemdbClass::CMemdbClass()
{
	m_memdata = NULL;	//内存库返回数据指针地址,处理时将该地址变换为实际设备类型使用
	m_memtable = NULL;	//当前设备内存表基本结构
	m_datatnum = 0;		//当前表的数据数量
}

CMemdbClass::~CMemdbClass()
{

}

bool CMemdbClass::GetMemdata(LPCSTR pmemtype,LPCSTR ptablename)
{
	if((pmemtype==NULL)||(strlen(pmemtype)<=0))
		return false;
	if((ptablename==NULL)||(strlen(ptablename)<=0))
		return false;
	
	m_memdata =(char*)GetMemTable((char*)pmemtype,(char*)ptablename,&m_memtable);
	if(m_memdata==NULL)
		return false;
	m_datatnum = m_memtable->userec;
	
	return true;
}

void* GetMemTable(char *pDB, char *table, MEMTABLE **pTable)
{
	DWORD idi;
	if(!LSI_GetTableID(pDB,table,idi))
		return NULL;

	int tabno=LOWORD(idi);
	*pTable=(MEMTABLE *)LSI_GetTableAdd(tabno);
	if((*pTable)==NULL) return NULL;
	if((*pTable)->userec<0) return NULL;
	return (*pTable)->data;
}

