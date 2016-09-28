// Graph.h: interface for the CGraph class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_GRAPH_H__F067000F_2C1E_4C0C_909A_642E513A6AE3__INCLUDED_)
#define AFX_GRAPH_H__F067000F_2C1E_4C0C_909A_642E513A6AE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
#include "Figure.h"

typedef struct METADATA
{
	METADATA(){memset(this,0,sizeof(METADATA));};

	char szID[GNAME_MAX];
	char szName[GNAME_MAX];
}METADATA;

class CGraph  
{
public:
	//添加嵌套图形
	void AddGraph(CGraph* pg){m_GraphVtr.push_back(pg);};
	//设置关联设备信息
	void SetPSRRef(const char* pID,const char* pName);
	//设置关联量测信息
	void SetMeasRef(const char* pID,const char* pName);
	//设置图元
	void SetFigureGroup(CFigureGroup* pGroup){m_pGroup=pGroup;};
	//设置类
	void SetClass(CSS_STYLE* pClass){m_pClass=pClass;};
	//设置变换矩阵
	void SetFigureMatrix(MATRIX* pMatrix);
	//设置图元位置
	void SetFigureRect(CRect* pRect);
	//添加基本图形
	void AddFigure(CFigure figure){m_FigureVtr.push_back(figure);};

	const METADATA* GetPSRRef(){return m_pPSRRef;};
	const METADATA* GetMeasRef(){return m_pMeasRef;};
	const char* GetName(){return m_szName;};
	const MATRIX* GetMatrix(){return m_pMatrix;};
	const CRect* GetRect(){return m_pRect;};
	const CFigureGroup* GetFigureGroup(){return m_pGroup;};
	const CSS_STYLE* GetClass(){return m_pClass;};

	BOOL GetFirstFigure()
	{
		m_figitr=m_FigureVtr.begin();
		if(m_figitr!=m_FigureVtr.end()) 
			return TRUE;
		return FALSE;
	};
	CFigure* GetNextFigure();

	BOOL GetFirstGraph()
	{
		m_grpitr=m_GraphVtr.begin();
		if(m_grpitr!=m_GraphVtr.end()) 
			return TRUE;
		return FALSE;
	};
	CGraph* GetNextGraph();

	CGraph(const char* pName);
	virtual ~CGraph();
private:
	METADATA* m_pPSRRef;
	METADATA* m_pMeasRef;

	char m_szName[GNAME_MAX];

	MATRIX* m_pMatrix;	//变换矩阵
	CRect* m_pRect;		//图形位置，图元图形才有
	CFigureGroup* m_pGroup; //图元图形
	CSS_STYLE* m_pClass;

	std::vector<CGraph*> m_GraphVtr;//嵌套图形
	std::vector<CGraph*>::iterator m_grpitr;
	FIGUREVTR m_FigureVtr;	//基本图形组
	FIGUREVTR::iterator m_figitr;
};
typedef std::vector<CGraph*> GRAPHVTR;

#endif // !defined(AFX_GRAPH_H__F067000F_2C1E_4C0C_909A_642E513A6AE3__INCLUDED_)
