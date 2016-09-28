// BinarySearch.cpp: implementation of the CBinarySearch class.
//
//////////////////////////////////////////////////////////////////////
#include "stdafx.h"
#include "BinarySearch.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CBinarySearch::CBinarySearch()
{
	m_SortType=SORT_UN;
	m_iIndex=1;
}

CBinarySearch::~CBinarySearch()
{
	ResetSearch();
}

//返回记录
void* CBinarySearch::Search(const char* pName)
{
	if(m_SortType!=SORT_NM)
	{
		std::sort(m_MapVtr.begin(),m_MapVtr.end(),CmpSearchByName);
		m_SortType=SORT_NM;
	}

	if(m_MapVtr.size()>0)
	{
		long lMin=0;
		long lMax=m_MapVtr.size()-1;
		while(lMin<=lMax)
		{
			long lHalf=(lMax+lMin)/2;
			if(lHalf>=0)
			{
				int iCompare=CmpMapByName(m_MapVtr[lHalf],pName);
				if(iCompare<0)
					lMin=lHalf+1;
				else if(iCompare>0)
					lMax=lHalf-1;
				else
				{
					return m_MapVtr[lHalf]->pRec;
				}
			}
			else
				break;
		}
	}
	return NULL;
}

//返回记录和记录号
void* CBinarySearch::Search(int NU)
{
	if(m_SortType!=SORT_ID)
	{
		std::sort(m_MapVtr.begin(),m_MapVtr.end(),CmpSearchByNU);
		m_SortType=SORT_ID;
	}

	if(m_MapVtr.size()>0)
	{
		long lMin=0;
		long lMax=m_MapVtr.size()-1;
		while(lMin<=lMax)
		{
			long lHalf=(lMax+lMin)/2;
			if(lHalf>=0)
			{
				if(m_MapVtr[lHalf]->NU<NU)
					lMin=lHalf+1;
				else if(m_MapVtr[lHalf]->NU>NU)
					lMax=lHalf-1;
				else
				{
					return m_MapVtr[lHalf]->pRec;
				}
			}
			else
				break;
		}
	}
	return NULL;
}

//添加影射
void CBinarySearch::AddMap(int NU,char* pName,void* pMap,int idx)
{
	BINARYMAP* pSearch=new BINARYMAP;
	pSearch->NU=NU;
	strcpy(pSearch->szName,pName);
	pSearch->idx=idx;
	pSearch->pRec=pMap;
	if(pMap==NULL)
		pSearch->pRec=pSearch;
	m_MapVtr.push_back(pSearch);
}

//自编号添加影射
BINARYMAP* CBinarySearch::AddMap(char* pName,void* pMap,int idx)
{
	BINARYMAP* pSearch=new BINARYMAP;
	pSearch->NU=m_iIndex++;
	strcpy(pSearch->szName,pName);
	pSearch->idx=idx;
	pSearch->pRec=pMap;
	if(pMap==NULL)
		pSearch->pRec=pSearch;
	m_MapVtr.push_back(pSearch);

	return pSearch;
}

//重置查找
void CBinarySearch::ResetSearch()
{
	m_iIndex=1;
	m_SortType=SORT_UN;

	for(BMAPVTR::iterator itr=m_MapVtr.begin();itr!=m_MapVtr.end();itr++)
		delete (*itr);
	m_MapVtr.clear();
}

int CBinarySearch::CmpSearchByName(BINARYMAP* pOne,BINARYMAP* pTwo)
{
	if(strcmp(pOne->szName,pTwo->szName)<0)
		return TRUE;
	else
		return FALSE;
}

int CBinarySearch::CmpSearchByNU(BINARYMAP* pOne,BINARYMAP* pTwo)
{
	if(pOne->NU<pTwo->NU)
		return TRUE;
	else
		return FALSE;
}

int CBinarySearch::CmpMapByName(BINARYMAP* pMap,const char* pName)
{
	int iRet=strcmp(pMap->szName,pName);
	if(iRet<0)
		return -1;
	else if(iRet==0)
		return 0;
	else
		return 1;
}

int CBinarySearch::CmpMapByIndex(BINARYMAP* pOne,int NU)
{
	if(pOne->NU<NU)
		return -1;
	else if(pOne->NU==NU)
		return 0;
	else
		return 1;
}

