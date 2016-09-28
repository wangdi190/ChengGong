// XmlItem.cpp: implementation of the CXmlItem class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmlItem.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CMemoryName CXmlItem::m_MemNM;
std::vector<CXmlItem*> CXmlItem::m_MemItemVtr;
CXmlItem* CXmlItem::m_pMemItem=NULL;
int CXmlItem::m_memindex=0;

CXmlItem::CXmlItem(char* pszItem,char* pszVal)
{
	m_pszName=m_MemNM.GetNamePointer(pszItem);
	int count=strlen(pszVal);
	if(count>0)
	{
		m_pValue=new char[count+1];
		strcpy(m_pValue,pszVal);
	}
	/*if(count>=XMLVALUE_MAX)
	{
		strncpy(m_szValue,pszVal,XMLVALUE_MAX-1);  //数据项值
		m_szValue[XMLVALUE_MAX-1]=0;
	}
	else
		strcpy(m_szValue,pszVal);  //数据项值*/
}

CXmlItem::CXmlItem()
{
	m_pszName=NULL;
	m_pValue=NULL;
	//memset(m_szValue,0,XMLVALUE_MAX);
}

CXmlItem::~CXmlItem()
{
	if(m_pValue!=NULL)
		delete []m_pValue;
	m_pValue=NULL;
}

BOOL CXmlItem::ValIsNumber()
{
	/*for(int i=0;i<strlen(m_szValue);i++)
	{
		if(!IsNumber(m_szValue[i]))
			return FALSE;
	}*/
	return TRUE;
}

//清除名字
void CXmlItem::ClearItem()
{
	m_pMemItem=NULL;
	m_memindex=0;
	for(XMLITEMVTR::iterator j=m_MemItemVtr.begin();j!=m_MemItemVtr.end();++j)
		delete [](*j);
	m_MemItemVtr.clear();

	m_MemNM.ResetName();
};

CXmlItem* CXmlItem::AllocItemMem(char* pszItem,char* pszVal)
{
	if(m_memindex==0)
	{
		m_pMemItem=new CXmlItem[64];
		m_MemItemVtr.push_back(m_pMemItem);
	}
	
	CXmlItem* pItem=NULL;
	if(strlen(pszItem)>0)
	{
		pItem=&m_pMemItem[m_memindex++];
		pItem->SetItem(pszItem,pszVal);
	}
	if(m_memindex>=64)
		m_memindex=0;
	return pItem;
}


void CXmlItem::SetItem(char* pszItem,char* pszVal)
{
	m_pszName=m_MemNM.GetNamePointer(pszItem);
	int count=strlen(pszVal);
	if(count>0)
	{
		m_pValue=new char[count+1];
		strcpy(m_pValue,pszVal);
	}
	/*if(count>=XMLVALUE_MAX)
	{
		strncpy(m_szValue,pszVal,XMLVALUE_MAX-1);  //数据项值
		m_szValue[XMLVALUE_MAX-1]=0;
	}
	else
		strcpy(m_szValue,pszVal);  //数据项值*/
}
