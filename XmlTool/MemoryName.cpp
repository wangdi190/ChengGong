// MemoryName.cpp: implementation of the CMemoryName class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "MemoryName.h"
#include <malloc.h>
#include <algorithm>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CMemoryName::CMemoryName()
{
}

CMemoryName::~CMemoryName()
{
	m_strVtr.clear();
}

//反回名字指针
const char* CMemoryName::GetNamePointer(char* pName)
{
	const char* pReturn=BinarySearch(pName);
	if(pReturn==NULL && strlen(pName)>0)
	{
		for(STRVTR::iterator itr=m_strVtr.begin();itr!=m_strVtr.end();++itr)
		{
			if((*itr).compare(pName)>0)
			{
				m_strVtr.insert(itr,std::string(pName));
				break;
			}
		}

		if(itr==m_strVtr.end() || m_strVtr.size()==0)
			m_strVtr.push_back(std::string(pName));
		pReturn=BinarySearch(pName);
	}
	return pReturn;
}

const char* CMemoryName::BinarySearch(char *pName)
{
	if(m_strVtr.size()>0)
	{
		long lMin=0;
		long lMax=m_strVtr.size()-1;
		while(lMin<=lMax)
		{
			long lHalf=(lMax+lMin)/2;
			if(lHalf>=0)
			{
				int cmp=m_strVtr[lHalf].compare(pName);
				if(cmp<0)
					lMin=lHalf+1;
				else if(cmp>0)
					lMax=lHalf-1;
				else
				{
					return m_strVtr[lHalf].c_str();
				}
			}
			else
				break;
		}
	}
	return NULL;
}

BOOL CMemoryName::CompareByName(char *pOne, char *pTwo)
{
	if(strcmp(pOne,pTwo)<0)
		return TRUE;
	else
		return FALSE;
}

