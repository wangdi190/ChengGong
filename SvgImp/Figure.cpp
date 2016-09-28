// Figure.cpp: implementation of the CFigure class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Figure.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CFigure::CFigure(GTYPE type,void* pFigure,int size)
{
	memcpy(m_pGraph,pFigure,size);

	m_type=type;
	m_size=size;
}

CFigure::~CFigure()
{
	if(m_pGraph!=NULL)
		delete []m_pGraph;
	m_pGraph=NULL;
	m_size=0;
}

