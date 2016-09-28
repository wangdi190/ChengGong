// BinarySearch.h: interface for the CBinarySearch class.
//描述：二分法按名字或数字查找
//作者：张强 zhqi_ang@yeah.net
//日期：2009.7.1
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_BINARYSEARCH_H__AC5E78E4_6923_4D8A_870F_870D0F5458B9__INCLUDED_)
#define AFX_BINARYSEARCH_H__AC5E78E4_6923_4D8A_870F_870D0F5458B9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "stdio.h"
#include <afx.h>

#include <vector>
#include <algorithm>

struct BINARYMAP
{
	BINARYMAP(){memset(this,0,sizeof(BINARYMAP));};
	int NU;		//序号
	char szName[32];//名称
	void* pRec;//记录
	int idx;
};
typedef std::vector<BINARYMAP*> BMAPVTR;

enum SORTTYPE
{
	SORT_UN=0, //未排序
	SORT_NM=1, //按名字排序
	SORT_ID=2  //按ID排序
};

class CBinarySearch  
{
public:
	//重置查找
	void ResetSearch();
	//添加影射对象
	BINARYMAP* AddMap(char* pName,void* pMap,int idx=0);
	//添加影射对象
	void AddMap(int NU,char* pName,void* pMap,int idx=0);
	//按名字查找返回记录
	void* Search(const char* pName);
	//按序号返回记录
	void* Search(int NU);

	CBinarySearch();
	virtual ~CBinarySearch();
private:
	//比较两个map的名字，排序用
	static int CmpSearchByName(BINARYMAP* pOne,BINARYMAP* pTwo);
	//比较两个map的序号，排序用
	static int CmpSearchByNU(BINARYMAP* pOne,BINARYMAP* pTwo);
	//按名字比较，查找用
	static int CmpMapByName(BINARYMAP* pMap,const char* pName);
	//按序号比较大小，查找用
	static int CmpMapByIndex(BINARYMAP* pOne,int NU);

	BMAPVTR m_MapVtr;
	int m_iIndex;
	//排序类型
	SORTTYPE m_SortType;
};

#endif // !defined(AFX_BINARYSEARCH_H__AC5E78E4_6923_4D8A_870F_870D0F5458B9__INCLUDED_)
