// MemdbClass.h: interface for the CMemdbClass class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMDBCLASS_H__BBB0FCA4_1FB0_4330_9FA9_424637B16ADC__INCLUDED_)
#define AFX_MEMDBCLASS_H__BBB0FCA4_1FB0_4330_9FA9_424637B16ADC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMemdbClass  
{
public:
	CMemdbClass();
	virtual ~CMemdbClass();

	bool GetMemdata(LPCSTR pmemtype,LPCSTR ptablename);		//取内存表数据
public:
	char* m_memdata;		//内存库返回数据指针地址,处理时将该地址变换为实际设备类型使用
	MEMTABLE* m_memtable;	//当前设备内存表基本结构
	int m_datatnum;			//当前表的数据数量

private:

};

void* GetMemTable(char* pDB,char* table,MEMTABLE**  pTable);

#endif // !defined(AFX_MEMDBCLASS_H__BBB0FCA4_1FB0_4330_9FA9_424637B16ADC__INCLUDED_)
