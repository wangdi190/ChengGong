// Translator.h: interface for the CTranslator class.
//说明：本类主要为DF8003配套，对应CSvgDF8003，其他需要继承改写
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TRANSLATOR_H__E8FD25FE_8BFD_40BA_B1F0_9525E370401D__INCLUDED_)
#define AFX_TRANSLATOR_H__E8FD25FE_8BFD_40BA_B1F0_9525E370401D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Layer.h"

struct SVG_PAGE;
struct SVG_LAYER;
struct SVG_GRAPH;
struct SVG_ELEGRP;


class CTranslator  
{
public:
	//转化图元
	virtual BOOL TranslateSymbol(FIGUREELEVTR* pEleGrpVtr);
	//动态点图层
	virtual BOOL LayerDynmic(CLayer *pLayer);
	//动态点图层
	virtual BOOL LayerCompensator(CLayer *pLayer);
	//电抗图层
	virtual BOOL LayerReactor(CLayer *pLayer);
	//负荷图层
	virtual BOOL LayerLoad(CLayer *pLayer);
	//电力线图层
	virtual BOOL LayerPowerLine(CLayer *pLayer);
	//刀闸图层
	virtual BOOL LayerDisconnector(CLayer *pLayer);

	virtual BOOL LayerGroundDisconnector(CLayer *pLayer);
	//连接线图层
	virtual BOOL LayerConnectLine(CLayer* pLayer);
	//开关图层
	virtual BOOL LayerBreaker(CLayer *pLayer);
	//两绕组变压器图层
	virtual BOOL LayerTransformer2(CLayer *pLayer);
	//三绕组变压器图层
	virtual BOOL LayerTransformer3(CLayer *pLayer);
	//母线图层
	virtual BOOL LayerBus(CLayer *pLayer);
	//发电机图层
	virtual BOOL LayerGenerator(CLayer *pLayer);
	//量测图层
	virtual BOOL LayerMeasure(CLayer *pLayer);
	//文本图层
	virtual BOOL LayerText(CLayer *pLayer);
	//按钮图层
	virtual BOOL LayerButton(CLayer *pLayer);
	//头图层
	virtual BOOL LayerHead(CLayer *pLayer,CRect *pVBox);
	//一般图层
	virtual BOOL LayerGeneric(CLayer* pLayer);
	//通用图元图形图层
	virtual BOOL LayerEleGeneric(CLayer *pLayer,unsigned char etype);

	CTranslator(SVG_PAGE* page);
	virtual ~CTranslator();
protected:
	void SetEleMatrixTfm(SVG_GRAPH* pGraph,MATRIX* pMatrix);
	//图元图层
	virtual BOOL LayerEleGrp(CLayer* pLayer,unsigned char etype,MATRIX* pVbMatrix);
	//转换一个图元
	virtual BOOL TranslateSymGrp(CFigureGroup *pGroup,void* pSvgVtr);
	//返回组合图元
	SVG_GRAPH* GetEleGraph(CGraph* pGraph,unsigned char etype,MATRIX* pVbMatrix);
	//图元编号
	unsigned long GetGraphID(){return ++m_lgid;};

	//SVG基本图转化为可视化基本图形
	virtual SVG_GRAPH* FigureToGraph(CFigure* pFigure,MATRIX* pMtx);
	//SVG基本图转化为可视化潮流线
	virtual SVG_GRAPH* FigureToFlow(CFigure* pFigure,MATRIX* pMtx);
	//SVG基本图形转化为可视化连接线
	virtual SVG_GRAPH* FigureToConnect(CFigure* pFigure,MATRIX* pMtx);
	//SVG基本图形组转化为可视化基本图形
	virtual BOOL CGraphToGraph(CGraph *pGraph, void* pSvgVtr,MATRIX* pMtx);
	//SVG基本图形组转化为可视化按钮
	virtual SVG_GRAPH* FigureToButton(CFigure* pFigure,MATRIX* pMtx);
	//SVG基本图形组转化为模拟量
	virtual SVG_GRAPH* FigureToAnalog(CGraph *pGraph, MATRIX *pMtx);
	//SVG基本图形组转化为母线
	virtual SVG_GRAPH* FigureToBus(CGraph *pGraph, MATRIX *pMtx);

	//转换为系统可识别的汉字库名
	void ChangeFontFaceName(char *oldname,char *newname);
	//取得模拟量属性
	const char* GetAnalogAtr(const char *objectid,long &id,BYTE &type,BYTE &mode);

	//输出的图形页
	SVG_PAGE* m_page;
	SVG_LAYER* m_pCurLayer;
private:
	unsigned long m_lgid;//图形ID
	MATRIX m_vbMatrix;
};

#endif // !defined(AFX_TRANSLATOR_H__E8FD25FE_8BFD_40BA_B1F0_9525E370401D__INCLUDED_)
