// SvgDF8003.cpp: implementation of the CSvgDF8003 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "SvgDF8003.h"
#include "SvgImp.h"

extern const char* svgkey[];
extern const char* cgekey[];
extern const char* graphkey[];
extern const char* atrkey[];
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////


CSvgDF8003::CSvgDF8003()
{

}

CSvgDF8003::~CSvgDF8003()
{

}

BOOL CSvgDF8003::SvgParse(char *pFile,SVG_PAGE* page)
{
	if(pFile==NULL)
		return FALSE;

	BOOL bResult=TRUE;
	XMLNODEVTR *ndvtr=NULL;
	if(XMLAPI_Parse(pFile,&ndvtr))
	{
		const char* pVal=NULL;
		IXmlNode* pNode=NULL;
		for(XMLITERATOR itr=ndvtr->begin();itr!=ndvtr->end();++itr)
		{
			pNode=(*itr);
			if(pNode->IsKindof(svgkey[0]))//?xml
			{
				pVal=pNode->GetPropValue("encoding");
				m_byCode=GetCodeStyle(pVal);
			}
			else if(pNode->IsKindof(svgkey[1]))//SVG
			{
				pVal=pNode->GetPropValue("viewBox");
				if(!GetViewBox(pVal,&m_viewBox))
				{
					bResult=FALSE;
					break;
				}

				if(pNode->GetFirstSubNode())
				{
					IXmlNode* pSubNode=NULL;
					while((pSubNode=pNode->GetNextSubNode())!=NULL)
					{
						if(!MainParse(pSubNode))
						{
							bResult=FALSE;
							break;
						}
					}
				}
			}
		}
		XMLAPI_Release(ndvtr);
	}

	if(bResult)//转换
	{
		bResult=Translate(page);
	}
	return bResult;
}

//转换图形
BOOL CSvgDF8003::Translate(SVG_PAGE* page)
{
	if(m_pTranslator!=NULL)
		delete m_pTranslator;
	m_pTranslator=new CTranslator(page);

	//转换图元
	m_pTranslator->TranslateSymbol(&m_EleGrpVtr);
	for(LAYERVTR::iterator itr=m_LayerVtr.begin();itr!=m_LayerVtr.end();++itr)
	{
		const char* pName=(*itr)->GetLayerName();
		if(pName==NULL || strlen(pName)==0)
			continue;

		CLayer* pLayer=(*itr);
		//Head_Layer...........头层
		if(strcmp(pName,"Head_Layer")==0)
			m_pTranslator->LayerHead(pLayer,&m_viewBox);
		//DynamicPoint_Layer...动态点图层
		else if(strcmp(pName,"DynamicPoint_Layer")==0)
			m_pTranslator->LayerDynmic(*itr);
		//Compensator_Layer....电容器层
		else if(strcmp(pName,"Compensator_Layer")==0)
			m_pTranslator->LayerCompensator(*itr);
		//Reactor_Layer........电抗器层
		else if(strcmp(pName,"Reactor_Layer")==0)
			m_pTranslator->LayerReactor(*itr);
		//Load_Layer............负荷图层
		else if(strcmp(pName,"Load_Layer")==0)
			m_pTranslator->LayerLoad(*itr);
		//PowerLine_Layer......输电线图层
		else if(strcmp(pName,"PowerLine_Layer")==0 ||
			strcmp(pName, "ACLineSegment_Layer")==0)
			m_pTranslator->LayerPowerLine(*itr);
		//Switch_Layer.........开关图层
		else if(strcmp(pName,"Switch_Layer")==0 || 
			strcmp(pName, "Disconnector_Layer") == 0 )//
			m_pTranslator->LayerDisconnector(*itr);
	//	else if(strcmp(pName, "GroundDisconnector_Layer") == 0)
	//		m_pTranslator->LayerGroundDisconnector(*itr);
		//ConnectLine_Layer....连接线图层
		else if(strcmp(pName,"ConnectLine_Layer")==0)
			m_pTranslator->LayerConnectLine(*itr);
		//Breaker_Layer........断路器图层
		else if(strcmp(pName,"Breaker_Layer")==0 || strcmp(pName,"DollyBreaker_Layer")==0)
			m_pTranslator->LayerBreaker(*itr);
		//Transformer_Layer变压器图层
		else if(strcmp(pName,"Transformer_Layer")==0 ||
			strcmp(pName, "Transformer3_Layer") == 0)
			m_pTranslator->LayerTransformer3(*itr);
		//Transformer_Layer变压器图层
		else if(strcmp(pName,"Transformer2_Layer")==0)
			m_pTranslator->LayerTransformer2(*itr);
		//Bus_Layer............母线图层
		else if(strcmp(pName,"Bus_Layer")==0 || strcmp(pName,"BusSection_Layer")==0 )
			m_pTranslator->LayerBus(*itr);
		//Generator_Layer......发电机图层
		else if(strcmp(pName,"Generator_Layer")==0)
			m_pTranslator->LayerGenerator(*itr);
		//TermMeasure_Layer....量测图层
		else if(strcmp(pName,"TermMeasure_Layer")==0 || strcmp(pName,"ScadaRealValue_Layer")==0)
			m_pTranslator->LayerMeasure(*itr);
		//Text_Layer...........文本图层
		else if(strcmp(pName,"Text_Layer")==0)
			m_pTranslator->LayerText(*itr);
		//MotifButton_Layer....按钮图层
		else if(strcmp(pName,"MotifButton_Layer")==0)
			m_pTranslator->LayerButton(*itr);
		//Group_Layer..........
		else if(strcmp(pName,"Earth_Layer")==0 || 
			strcmp(pName, "GroundDisconnector_Layer") == 0 || strcmp(pName, "GroundDisconnector_ZXD_Layer")==0)
			m_pTranslator->LayerEleGeneric(*itr,EGP_ERH);
		//Rectangle_Layer......矩形图层
		//Image_Layer..........图像层
		else
			m_pTranslator->LayerGeneric(*itr);
	}
	
	return TRUE;
}

//多态图元分析
BOOL CSvgDF8003::PolyFigureGroup()
{
	const char* pGName=NULL;
	FIGUREGRPVTR::iterator itr;

//	char pText[256];

	for(itr=m_FigureGrpVtr.begin();itr!=m_FigureGrpVtr.end();++itr)
	{
		if((*itr)->m_pGroupParent!=NULL)
			continue;

		FIGUREELE* pFigEle=new FIGUREELE;
		pGName=(*itr)->GetGroupName();

//		Utf8ToASCII((const unsigned char*)pGName,strlen(pGName),pText,256);

		if(strstr(pGName,"Transformer")!=NULL)
		{
			//多子图元标识一个图元的部分，主要是变压器
			if(PolyOneGroup(*itr,pFigEle))
			{
				m_EleGrpVtr.push_back(pFigEle);
				continue;
			}
		}

		//多图元标识一个图元的不同状态
		if(PolyOneGroup(*itr,"_0","_1",pFigEle))
			m_EleGrpVtr.push_back(pFigEle);
		else if(PolyOneGroup(*itr,"_0_0","_0_1",pFigEle))
			m_EleGrpVtr.push_back(pFigEle);
		else if(PolyOneGroup(*itr,"_1_0","_1_1",pFigEle))
			m_EleGrpVtr.push_back(pFigEle);
		else
		{
			pFigEle->pGrp0=(*itr);
			(*itr)->m_pGroupParent=pFigEle;
			m_EleGrpVtr.push_back(pFigEle);
		}
	}
	

	return TRUE;
}