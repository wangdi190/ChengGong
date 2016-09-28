// Layer.cpp: implementation of the CLayer class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Layer.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CLayer::CLayer(const char* pName)
{
	if(pName!=NULL && strlen(pName)>0)
		strcpy(m_szName,pName);
	else
		memset(m_szName,0,GNAME_MAX);
	m_grpitr=NULL;
	m_figitr=NULL;
}

CLayer::~CLayer()
{
	for(GRAPHVTR::iterator itr=m_GraphVtr.begin();itr!=m_GraphVtr.end();++itr)
		delete *itr;
	m_GraphVtr.clear();
	m_FigureVtr.clear();
}


CGraph* CLayer::GetNextGraph()
{
	CGraph* pGraph=NULL;
	if(m_grpitr!=NULL && m_grpitr!=m_GraphVtr.end())
	{
		pGraph=*m_grpitr;
		m_grpitr++;
	}
	return pGraph;
}

CFigure* CLayer::GetNextFigure()
{
	CFigure* pFigure=NULL;
	if(m_figitr!=NULL && m_figitr!=m_FigureVtr.end())
	{
		pFigure=(CFigure*)&(*m_figitr);
		m_figitr++;
	}
	return pFigure;
}
