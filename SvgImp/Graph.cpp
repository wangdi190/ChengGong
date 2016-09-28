// Graph.cpp: implementation of the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Graph.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CGraph::CGraph(const char* pName)
{
	m_pGroup=NULL;
	m_pPSRRef=NULL;
	m_pMeasRef=NULL;
	m_pMatrix=NULL;
	m_pRect=NULL;
	m_pClass=NULL;
	m_grpitr=NULL;
	m_figitr=NULL;

	if(pName!=NULL && strlen(pName)>0)
		strcpy(m_szName,pName);
	else
		memset(m_szName,0,GNAME_MAX);
}

CGraph::~CGraph()
{
	m_FigureVtr.clear();

/*	if(m_pPSRRef!=NULL)
		delete m_pPSRRef;
	m_pPSRRef=NULL;

	if(m_pMeasRef!=NULL)/// wd
		delete m_pMeasRef;
	m_pMeasRef=NULL;*/

	if(m_pMatrix!=NULL)
		delete m_pMatrix;
	m_pMatrix=NULL;

	if(m_pRect!=NULL)
		delete m_pRect;
	m_pRect=NULL;

	for(GRAPHVTR::iterator itr=m_GraphVtr.begin();itr!=m_GraphVtr.end();++itr)
		delete *itr;
	m_GraphVtr.clear();
}

//设置变换矩阵
void CGraph::SetFigureMatrix(MATRIX* pMatrix)
{
	if(pMatrix!=NULL)
	{
		if(m_pMatrix==NULL)
			m_pMatrix=new MATRIX;
		memcpy(m_pMatrix,pMatrix,sizeof(MATRIX));
	}
}

//设置图元位置
void CGraph::SetFigureRect(CRect* pRect)
{
	if(pRect!=NULL)
	{
		if(m_pRect==NULL)
			m_pRect=new CRect;
		memcpy(m_pRect,pRect,sizeof(CRect));
	}
}

//设置关联设备信息
void CGraph::SetPSRRef(const char* pID,const char* pName)
{
	if(m_pPSRRef==NULL)
		m_pPSRRef=new METADATA;
	if(pID!=NULL && strlen(pID)>0)
		strcpy(m_pPSRRef->szID,pID);
	if(pName!=NULL && strlen(pName)>0)
		strcpy(m_pPSRRef->szName,pName);
}

//设置关联量测信息
void CGraph::SetMeasRef(const char* pID,const char* pName)
{
	if(m_pMeasRef==NULL)
		m_pMeasRef=new METADATA;
	strcpy(m_pMeasRef->szID,pID);
	strcpy(m_pMeasRef->szName,pName);
}

CGraph* CGraph::GetNextGraph()
{
	CGraph* pGraph=NULL;
	if(m_grpitr!=NULL && m_grpitr!=m_GraphVtr.end())
	{
		pGraph=*m_grpitr;
		m_grpitr++;
	}
	return pGraph;
}

CFigure* CGraph::GetNextFigure()
{
	CFigure* pFigure=NULL;
	if(m_figitr!=NULL && m_figitr!=m_FigureVtr.end())
	{
		pFigure=(CFigure*)&(*m_figitr);
		m_figitr++;
	}
	return pFigure;
}
