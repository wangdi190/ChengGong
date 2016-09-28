// Layer.h: interface for the CLayer class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LAYER_H__D789C3DE_748A_4E26_A7B5_D0B572DD05EA__INCLUDED_)
#define AFX_LAYER_H__D789C3DE_748A_4E26_A7B5_D0B572DD05EA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Graph.h"

class CLayer  
{
public:
	//返回图层名字
	const char* GetLayerName(){return m_szName;};
	//添加基本图形
	void AddFigure(CFigure figure){m_FigureVtr.push_back(figure);};
	//添加组合图形
	void AddGraph(CGraph* pg){m_GraphVtr.push_back(pg);};

	BOOL GetFirstGraph(){m_grpitr=m_GraphVtr.begin();if(m_grpitr!=m_GraphVtr.end()) return TRUE;return FALSE;};
	CGraph* GetNextGraph();
	BOOL GetFirstFigure(){m_figitr=m_FigureVtr.begin();if(m_figitr!=m_FigureVtr.end()) return TRUE;return FALSE;};
	CFigure* GetNextFigure();

	CLayer(const char* pName);
	virtual ~CLayer();
protected:
	GRAPHVTR m_GraphVtr;	//图元图形
	FIGUREVTR m_FigureVtr;	//基本图形组
private:
	GRAPHVTR::iterator m_grpitr;
	FIGUREVTR::iterator m_figitr;
	char m_szName[GNAME_MAX];
};

typedef std::vector<CLayer*> LAYERVTR;

#endif // !defined(AFX_LAYER_H__D789C3DE_748A_4E26_A7B5_D0B572DD05EA__INCLUDED_)
