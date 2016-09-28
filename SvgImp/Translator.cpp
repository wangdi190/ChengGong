// Translator.cpp: implementation of the CTranslator class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Translator.h"
#include "math.h"
#include "SvgImp.h"
#include "publicpw.h"

//转换为SVG中文对照表,总共19种
char *fontnm[]={"宋体","SimSun","黑体","Simhei","仿宋_GB2312","FangSong",
 "楷体_GB2312","KaiTi","幼圆","YouYuan","华文宋体","STSong",
 "华文中宋","STZhongsong","华文楷体","STKaiti","华文仿宋","STFangsong",
 "华文细黑","STXihei","华文隶书","STLiti","华文行楷","STXingkai",
 "华文新魏","STXinwei","华文琥珀","STHupo","华文彩云","STCaiyun",
 "方正姚体简体","FZYaoTi","方正舒体简体","FZShuTi","新宋体","NSimSun","隶书","LiSu",
 "楷体_GB2312","KaiTi"};   

extern const double PI;

//转换量测ID为设备名和序号
char* WINAPI ExchangeIDName(char* pid,int &type,DWORD &iNU,int &mtype,int &mpos);
//转换设备ID为设备名和序号
char* WINAPI IDtoNuName(char* ID,int Type,DWORD &iNU);
char* WINAPI NUtoName(DWORD NU,int Type,DWORD &iNU);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTranslator::CTranslator(SVG_PAGE* page)
{
	m_page=page;
	memset(m_page,0,sizeof(SVG_PAGE));

	m_pCurLayer=NULL;
	m_lgid=0;
	memset(&m_vbMatrix,0,sizeof(MATRIX));
	m_vbMatrix.fa=1.0;
	m_vbMatrix.fd=1.0;
}

CTranslator::~CTranslator()
{

}

//图层头
BOOL CTranslator::LayerHead(CLayer *pLayer,CRect *pVBox)
{
	if(pLayer->GetFirstFigure())
	{
		CFigure* pFigure=NULL;
		while((pFigure=pLayer->GetNextFigure())!=NULL)
		{
			if(pFigure->IsKindOf()==GTYPE_RECT)
			{
				G_RECT grt;
				if(pFigure->GetFigure(&grt,sizeof(G_RECT)))
				{
					m_vbMatrix.fe=-pVBox->left;
					m_vbMatrix.ff=-pVBox->top;

					m_page->dx=0;
					m_page->dy=0;
					m_page->width=grt.width;//pVBox->Width();
					m_page->height=grt.height;//pVBox->Height();

					m_page->bgcolor=grt.fcolor;
					m_page->laynum=1;
					m_pCurLayer=&m_page->layer[0];//处理成一个图层
					strcpy(m_pCurLayer->szName,"Open2000");
					return TRUE;
				}
			}
		}
	}
	return FALSE;
}

//通用图元图形图层
BOOL CTranslator::LayerEleGeneric(CLayer *pLayer,unsigned char etype)
{
	return LayerEleGrp(pLayer,etype,&m_vbMatrix);
}

//一般图形图层
BOOL CTranslator::LayerGeneric(CLayer *pLayer)
{
	if(pLayer==NULL)
		return FALSE;

	BOOL bReturn=FALSE;
	if(pLayer->GetFirstGraph())
	{
		CGraph* pGraph=NULL;
		while((pGraph=pLayer->GetNextGraph())!=NULL)
			bReturn|=CGraphToGraph(pGraph, &m_pCurLayer->gVtr,&m_vbMatrix);
	}
	if(pLayer->GetFirstFigure())
	{
		SVG_GRAPH* graph=NULL;
		CFigure *pFigure=NULL;
		while((pFigure=pLayer->GetNextFigure())!=NULL)
		{
			graph=FigureToGraph(pFigure,&m_vbMatrix);
			if(graph!=NULL)
			{
				m_pCurLayer->gVtr.push_back(graph);
				bReturn=TRUE;
			}
		}
	}
	return bReturn;
}

//按钮图层
BOOL CTranslator::LayerButton(CLayer *pLayer)
{
	if(pLayer==NULL)
		return FALSE;
	
	BOOL bReturn=FALSE;
	if(pLayer->GetFirstGraph())
	{
		CGraph* pGraph=NULL;
		while((pGraph=pLayer->GetNextGraph())!=NULL)
		{
			if(pGraph->GetFirstFigure())
			{
				CFigure *pFigure=NULL;
				while((pFigure=pGraph->GetNextFigure())!=NULL)
				{
					SVG_GRAPH* graph=FigureToButton(pFigure,&m_vbMatrix);
					if(graph!=NULL)
					{
						m_pCurLayer->gVtr.push_back(graph);
						bReturn=TRUE;
					}
				}
			}
		}
	}
	return bReturn;
}

//文本图层
BOOL CTranslator::LayerText(CLayer *pLayer)
{
	return LayerGeneric(pLayer);
}

//量测图层
BOOL CTranslator::LayerMeasure(CLayer *pLayer)
{
	if(pLayer==NULL)
		return FALSE;
	
	BOOL bReturn=FALSE;
	if(pLayer->GetFirstGraph())
	{
		CGraph* pGraph=NULL;
		while((pGraph=pLayer->GetNextGraph())!=NULL)
		{
			SVG_GRAPH* graph=FigureToAnalog(pGraph,&m_vbMatrix);
			if(graph!=NULL)
			{
				m_pCurLayer->gVtr.push_back(graph);
				bReturn=TRUE;
			}
		}
	}
	return bReturn;
}

//发电机图层
BOOL CTranslator::LayerGenerator(CLayer *pLayer)
{
	return LayerEleGrp(pLayer,EGP_GEN,&m_vbMatrix);
}

//母线图层
BOOL CTranslator::LayerBus(CLayer *pLayer)
{
	if(pLayer==NULL)
		return FALSE;
	
	BOOL bReturn=FALSE;
	if(pLayer->GetFirstGraph())
	{
		CGraph* pGraph=NULL;
		while((pGraph=pLayer->GetNextGraph())!=NULL)
		{
		//	CGraphToGraph(pGraph, &m_pCurLayer->gVtr,&m_vbMatrix);
		//	continue;

			SVG_GRAPH* graph=FigureToBus(pGraph,&m_vbMatrix);//
		//	SVG_GRAPH* graph=FigureToGraph(pGraph,&m_vbMatrix);//
			if(graph!=NULL)
			{
				m_pCurLayer->gVtr.push_back(graph);
				bReturn=TRUE;
			}
		}
	}
	return bReturn;

	/*
	if(pLayer==NULL)
		return FALSE;
	
	BOOL bReturn=FALSE;
	if(pLayer->GetFirstGraph())
	{
		CGraph* pGraph=NULL;
		while((pGraph=pLayer->GetNextGraph())!=NULL)
			bReturn|=CGraphToGraph(pGraph, &m_pCurLayer->gVtr,&m_vbMatrix);
	}
	if(pLayer->GetFirstFigure())
	{
		SVG_GRAPH* graph=NULL;
		CFigure *pFigure=NULL;
		while((pFigure=pLayer->GetNextFigure())!=NULL)
		{
			graph=FigureToGraph(pFigure,&m_vbMatrix);
			if(graph!=NULL)
			{
				m_pCurLayer->gVtr.push_back(graph);
				bReturn=TRUE;
			}
		}
	}
		return bReturn;*/
}

/*
//一般图形图层
BOOL CTranslator::LayerGeneric(CLayer *pLayer)
{
if(pLayer==NULL)
return FALSE;

  BOOL bReturn=FALSE;
  if(pLayer->GetFirstGraph())
  {
		CGraph* pGraph=NULL;
		while((pGraph=pLayer->GetNextGraph())!=NULL)
		bReturn|=CGraphToGraph(pGraph, &m_pCurLayer->gVtr,&m_vbMatrix);
		}
		if(pLayer->GetFirstFigure())
		{
		SVG_GRAPH* graph=NULL;
		CFigure *pFigure=NULL;
		while((pFigure=pLayer->GetNextFigure())!=NULL)
		{
		graph=FigureToGraph(pFigure,&m_vbMatrix);
		if(graph!=NULL)
		{
		m_pCurLayer->gVtr.push_back(graph);
		bReturn=TRUE;
		}
		}
		}
		return bReturn;
}
*/

//两绕组变压器器图层
BOOL CTranslator::LayerTransformer2(CLayer *pLayer)
{
	if(pLayer==NULL)
		return FALSE;
	
	BOOL bReturn=FALSE;
	if(pLayer->GetFirstGraph())
	{
		CGraph* pGraph2=NULL;
		while((pGraph2=pLayer->GetNextGraph())!=NULL)
		{
			if(pGraph2->GetFirstGraph())
			{
				CGraph* pGraph=NULL;
				if((pGraph=pGraph2->GetNextGraph())!=NULL)
				{
					SVG_GRAPH* pSGraph=GetEleGraph(pGraph, EGP_TF2,&m_vbMatrix);
					if(pSGraph!=NULL)
					{
						N_ELEGRPA* egp=(N_ELEGRPA*)pSGraph->graph;
						const METADATA* pMeta=pGraph2->GetPSRRef();
						if(pMeta!=NULL)
						{
							egp->did=atoi(pGraph2->GetPSRRef()->szID);

							DWORD dwID;
							char* pName=NUtoName(egp->did,EGP_TF2,dwID);
							if(pName!=NULL)
								strcpy(egp->dev_name,pName);
						}
						m_pCurLayer->gVtr.push_back(pSGraph);
					}
				}
				bReturn=TRUE;
			}
		}
	}
	return bReturn;
}

//三绕组变压器器图层
BOOL CTranslator::LayerTransformer3(CLayer *pLayer)
{
	if(pLayer==NULL)
		return FALSE;
	
	BOOL bReturn=FALSE;
	if(pLayer->GetFirstGraph())
	{
		CGraph* pGraph2=NULL;
		while((pGraph2=pLayer->GetNextGraph())!=NULL)
		{
			if(pGraph2->GetFirstGraph())
			{
				CGraph* pGraph=NULL;
				if((pGraph=pGraph2->GetNextGraph())!=NULL)
				{
					SVG_GRAPH* pSGraph=GetEleGraph(pGraph, EGP_TF3,&m_vbMatrix);
					if(pSGraph!=NULL)
					{
						
						N_ELEGRPA* egp=(N_ELEGRPA*)pSGraph->graph;

						const METADATA* pMeta=pGraph2->GetPSRRef();
						if(pMeta!=NULL)
						{
							egp->did=atoi(pGraph2->GetPSRRef()->szID);

							DWORD dwID;
							char* pName=NUtoName(egp->did,EGP_TF3,dwID);
							if(pName!=NULL)
								strcpy(egp->dev_name,pName);
						}
						m_pCurLayer->gVtr.push_back(pSGraph);
					}
				}
				bReturn=TRUE;
			}
		}
	}
	return bReturn;
}

//断路器图层
BOOL CTranslator::LayerBreaker(CLayer *pLayer)
{
	return LayerEleGrp(pLayer,EGP_SWT,&m_vbMatrix);
}

//连接线图层
BOOL CTranslator::LayerConnectLine(CLayer *pLayer)
{
	if(pLayer->GetFirstGraph())
	{
		const MATRIX * pMtrix1,*pMtrix2;
		CGraph* pGraph=NULL;
		while((pGraph=pLayer->GetNextGraph())!=NULL)
		{
			N_CONLINE *pConnect=NULL;
			SVG_GRAPH* pSGraph=NULL;
			if(pGraph->GetFirstGraph())
			{
				CGraph* pGraph2=pGraph->GetNextGraph();
				if(pGraph2!=NULL && pGraph2->GetFirstFigure())
				{
					pMtrix1=pGraph->GetMatrix();
					pMtrix2=pGraph2->GetMatrix();

					MATRIX mx;
					memcpy(&mx,&m_vbMatrix,sizeof(MATRIX));
					
					if(pMtrix2!=NULL)
						MutiMatrix(&mx,pMtrix2);
					if(pMtrix1!=NULL)
						MutiMatrix(&mx,pMtrix1);
					pSGraph=FigureToConnect(pGraph2->GetNextFigure(),&mx);

					pConnect=(N_CONLINE*)pSGraph->graph;
					pConnect->conobj=1;
					pConnect->el=1;
					
					const CSS_STYLE* pCss=pGraph2->GetClass();
					if(pCss!=NULL)
						pConnect->vl=pCss->vVol;
				}
			}
			if(pSGraph!=NULL)
				m_pCurLayer->gVtr.push_back(pSGraph);
		}
		return TRUE;
	}
	else
		return FALSE;
}

//刀闸图层
BOOL CTranslator::LayerDisconnector(CLayer *pLayer)
{
	return LayerEleGrp(pLayer,EGP_SWT,&m_vbMatrix);
}

BOOL CTranslator::LayerGroundDisconnector(CLayer *pLayer)
{
	return LayerEleGrp(pLayer,EGP_ERH,&m_vbMatrix);
}

//输电线图层
BOOL CTranslator::LayerPowerLine(CLayer *pLayer)
{

	if(pLayer->GetFirstGraph())
	{
		const MATRIX * pMtrix1,*pMtrix2;
		CGraph* pGraph=NULL;
		while((pGraph=pLayer->GetNextGraph())!=NULL)
		{
			N_FLOW *pFlow=NULL;
			SVG_GRAPH* pSGraph=NULL;
			//if(pGraph->GetFirstGraph())
			//{
			//	CGraph* pGraph2=pGraph->GetNextGraph();
				CGraph* pGraph2 = pGraph;
				if(pGraph2!=NULL && pGraph2->GetFirstFigure())
				{
					pMtrix1=pGraph->GetMatrix();
					pMtrix2=pGraph2->GetMatrix();

					MATRIX mx;
					memcpy(&mx,&m_vbMatrix,sizeof(MATRIX));
					if(pMtrix2!=NULL)
						MutiMatrix(&mx,pMtrix2);
					if(pMtrix1!=NULL)
						MutiMatrix(&mx,pMtrix1);
					pSGraph=FigureToFlow(pGraph2->GetNextFigure(),&mx);

					pFlow=(N_FLOW*)pSGraph->graph;
					pFlow->rf.pjs=15;

					const CSS_STYLE* pCss=pGraph2->GetClass();
					if(pCss!=NULL)
					{
						pFlow->vl=pCss->vVol;
						for(int i=0;i<2;i++)
							pFlow->site[i].id=-1;
					}
				//}
			}
			if(pSGraph!=NULL)
			{
				const METADATA* pMeta=pGraph->GetPSRRef();
				if(pMeta!=NULL)
				{
					char *pID=NULL, *pName=NULL;// szName[256]={0};

					pID = strstr(pMeta->szID, "LN=");
					
					if(pID!=NULL)
						pFlow->did=atol(pID+3);

					if(strlen(pMeta->szName)>0)
					{
						//Utf8ToASCII((const unsigned char*)pMeta->szName,strlen(pMeta->szName),szName,256);
						
						pName = strstr(pMeta->szName, ".");
						if(pName==NULL)
							pName = strstr(pMeta->szName, "_");
						
						if(pName != NULL)
							strcpy(pFlow->dev_name,pName+1);
					}
				}

				m_pCurLayer->gVtr.push_back(pSGraph);
			}
		}
		return TRUE;
	}
	else
		return FALSE;
}

//负荷图层
BOOL CTranslator::LayerLoad(CLayer *pLayer)
{
	return FALSE;
}

//电抗图层
BOOL CTranslator::LayerReactor(CLayer *pLayer)
{
	return LayerEleGrp(pLayer,EGP_RTR,&m_vbMatrix);
}

//补偿图层
BOOL CTranslator::LayerCompensator(CLayer *pLayer)
{
	return LayerEleGrp(pLayer,EGP_SHT,&m_vbMatrix);
}

//动态点图层
BOOL CTranslator::LayerDynmic(CLayer *pLayer)
{
	return LayerEleGrp(pLayer,EGP_PT,&m_vbMatrix);
}

//转换图元
BOOL CTranslator::TranslateSymbol(FIGUREELEVTR* pEleGrpVtr)
{
	if(pEleGrpVtr==NULL)
		return FALSE;

	for(FIGUREELEVTR::iterator gpr=pEleGrpVtr->begin();gpr!=pEleGrpVtr->end();++gpr)
	{
		FIGUREELE* pFigEle=*gpr;

		SVG_ELEGRP* pgrp=new SVG_ELEGRP;
		memset(pgrp,0,sizeof(SVG_ELEGRP));

		//处理一个图元
		BOOL bResult=FALSE;
		if(pFigEle->pGrp0!=NULL)
			bResult=TranslateSymGrp(pFigEle->pGrp0,&pgrp->g1Vtr);
		if(pFigEle->pGrp1!=NULL)
			TranslateSymGrp(pFigEle->pGrp1,&pgrp->g2Vtr);

		if(bResult)
		{
			pgrp->id=m_page->egrpVtr.size();
			pgrp->type=1;
			sprintf(pgrp->name,"%d",pgrp->id);
			pFigEle->pEleGrp=pgrp;
			//TRACE("%d,%x\n",pgrp->id,pgrp);
			m_page->egrpVtr.push_back(pgrp);
		}
		else
			delete pgrp;
	}
	return TRUE;
}

//取得图元图层的图形
SVG_GRAPH* CTranslator::GetEleGraph(CGraph *pGraph, unsigned char etype,MATRIX* pVbMatrix)
{
	SVG_GRAPH* pSGraph=new SVG_GRAPH;
	memset(pSGraph,0,sizeof(SVG_GRAPH));
	pSGraph->attr.type=N_ELEGRPA_TYPE;
	pSGraph->attr.belong=0;
	pSGraph->attr.size=sizeof(N_ELEGRPA);
	pSGraph->attr.ID=GetGraphID();
	pSGraph->graph=new char[pSGraph->attr.size];
	
	const char* pName=pGraph->GetName();
	N_ELEGRPA* egp=(N_ELEGRPA*)pSGraph->graph;
	memset(egp,0,sizeof(N_ELEGRPA));
	strcpy(egp->dev_name,pName);
	egp->type=1;
	egp->subtype=etype;
	const CFigureGroup* pGroup=pGraph->GetFigureGroup();

	CRect rt;
	if(pGroup!=NULL && pGroup->m_pGroupParent!=NULL)
	{
		FIGUREELE* pFigEle=(FIGUREELE*)pGroup->m_pGroupParent;
		if(pFigEle->pGrp0==pGroup)
			egp->showno=0;
		else
			egp->showno=1;

		pFigEle->pGrp0->GetGroupRect(rt);
		if(pFigEle->pEleGrp!=NULL)
		{
			SVG_ELEGRP* pEleGrp=(SVG_ELEGRP*)pFigEle->pEleGrp;
			egp->egrpid=pEleGrp->id;
			if(etype!=pEleGrp->subtype)
				pEleGrp->subtype=etype;
		}
	}
	else
	{
		delete []pSGraph->graph;
		delete pSGraph;
		return NULL;
	}

	//取得位置
	const CRect* pRect=pGraph->GetRect();
	const MATRIX* pMatrix=pGraph->GetMatrix();
	DPOINT ptLT,ptRB;
	if(pRect==NULL)
		pRect=&rt;
	ptLT.x=pRect->left;
	ptLT.y=pRect->top;
	ptRB.x=pRect->right;
	ptRB.y=pRect->bottom;

	MATRIX mx;
	if(pMatrix!=NULL)
	{
		memcpy(&mx,pMatrix,sizeof(MATRIX));
		SetEleMatrixTfm(pSGraph,&mx);
	}
	if(pVbMatrix!=NULL)
		MutiMatrix(&mx,pVbMatrix);

	ptLT=PointMatrix(ptLT,&mx);
	ptRB=PointMatrix(ptRB,&mx);
	rt=CRect(ptLT.x,ptLT.y,ptRB.x,ptRB.y);
	rt.NormalizeRect();

	egp->pt[0].x=rt.left;
	egp->pt[0].y=rt.top;
	egp->pt[1].x=rt.right;
	egp->pt[1].y=rt.top;
	egp->pt[2].x=rt.right;
	egp->pt[2].y=rt.bottom;
	egp->pt[3].x=rt.left;
	egp->pt[3].y=rt.bottom;

		
	const CSS_STYLE* pClass=pGraph->GetClass();
	if(pClass!=NULL)
	{
		egp->site[0].vl=(int)pClass->vVol;
		egp->site[1].vl=(int)pClass->vVol;
	}
	
	const METADATA* pMeta=pGraph->GetPSRRef();
	if(pMeta!=NULL)
	{
		egp->did=atoi(pMeta->szID);
	//	strcpy(egp->dev_name,pMeta->szName);

		DWORD dwID;
		char* pName=NUtoName(egp->did,etype,dwID);
		if(pName!=NULL)
			strcpy(egp->dev_name,pName);
	}
	
	return pSGraph;
}

//SVG简单图形到PW0简单图形
SVG_GRAPH* CTranslator::FigureToGraph(CFigure *pFigure,MATRIX* pMtx)
{
	SVG_GRAPH* graph=NULL;
	if(pFigure==NULL)
		return graph;

	MATRIX mx;
	BOOL bMatrix=FALSE;
	GTYPE gtype=pFigure->IsKindOf();
	switch(gtype)
	{
	case GTYPE_LINE://SVG线
		{
			G_LINE g;
			N_DBX* pPW0=NULL;
			if(pFigure->GetFigure(&g,sizeof(G_LINE)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_DBX_TYPE;
				graph->attr.size=sizeof(N_DBX)+2*sizeof(DPOINT);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_DBX*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->pt[0].x=g.sp.x;
				pPW0->pt[0].y=g.sp.y;
				pPW0->pt[1].x=g.ep.x;
				pPW0->pt[1].y=g.ep.y;
				pPW0->ptsum=2;
				if((g.check & LEFT_SHIFT06)==LEFT_SHIFT06)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(int i=0;i<pPW0->ptsum;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}

				pPW0->lcolor=g.lcolor;
				pPW0->bcolor1=pPW0->bcolor2=g.lcolor;
				pPW0->width=g.swidth<1?1:g.swidth;				
			}
		}
		break;
	case GTYPE_POLYL://polyline折线
		{
			G_POLYLINE g;
			N_DBX* pPW0=NULL;
			if(pFigure->GetFigure(&g,sizeof(G_POLYLINE)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_DBX_TYPE;
				graph->attr.size=sizeof(N_DBX)+g.ptnum*sizeof(DPOINT);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_DBX*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->ptsum=g.ptnum;
				for(int i=0;i<pPW0->ptsum;i++)
				{
					pPW0->pt[i].x=g.pt[i].x;
					pPW0->pt[i].y=g.pt[i].y;
				}
				if((g.check & LEFT_SHIFT04)==LEFT_SHIFT04)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(i=0;i<pPW0->ptsum;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}
				pPW0->lcolor=g.lcolor;
				pPW0->bcolor1=pPW0->bcolor2=g.lcolor;
				pPW0->width=g.swidth<1?1:g.swidth;				
			}
		}
		break;
	case GTYPE_POLYG://polygon多边形
		{
			G_POLYGON g;
			N_DBX* pPW0=NULL;
			if(pFigure->GetFigure(&g,sizeof(G_POLYGON)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_DBX_TYPE;
				graph->attr.size=sizeof(N_DBX)+g.ptnum*sizeof(DPOINT);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_DBX*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->ptsum=g.ptnum;
				for(int i=0;i<pPW0->ptsum;i++)
				{
					pPW0->pt[i].x=g.pt[i].x;
					pPW0->pt[i].y=g.pt[i].y;
				}
				if((g.check & LEFT_SHIFT05)==LEFT_SHIFT05)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(i=0;i<pPW0->ptsum;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}
				pPW0->close=1;
				pPW0->lcolor=g.lcolor;
				pPW0->bcolor1=pPW0->bcolor2=g.fcolor;
				pPW0->width=g.swidth<1?1:g.swidth;				
			}
		}
		break;
	case GTYPE_RECT://rect矩形
		{
			G_RECT g;
			N_RECT* pPW0=NULL;
			if(pFigure->GetFigure(&g,sizeof(G_RECT)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_RECT_TYPE;
				graph->attr.size=sizeof(N_RECT);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_RECT*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->pt[0].x=g.lt.x;
				pPW0->pt[0].y=g.lt.y;
				pPW0->pt[1].x=g.lt.x+g.width;
				pPW0->pt[1].y=g.lt.y;
				pPW0->pt[2].x=g.lt.x+g.width;
				pPW0->pt[2].y=g.lt.y+g.height;
				pPW0->pt[3].x=g.lt.x;
				pPW0->pt[3].y=g.lt.y+g.height;
				if((g.check & LEFT_SHIFT07)==LEFT_SHIFT07)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(int i=0;i<4;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}
				pPW0->lcolor=g.lcolor;
				pPW0->fill=g.full;
				pPW0->bcolor1=pPW0->bcolor2=g.fcolor;
				pPW0->width=g.swidth<1?1:g.swidth;				
			}
		}
		break;
	case GTYPE_CIRCLE://circle圆
		{
			G_CIRCLE g;
			N_CIRCLE* pPW0=NULL;
			if(pFigure->GetFigure(&g,sizeof(G_CIRCLE)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_CIRCLE_TYPE;
				graph->attr.size=sizeof(N_RECT);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_CIRCLE*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->pt[0].x=g.cp.x-g.r;
				pPW0->pt[0].y=g.cp.y-g.r;
				pPW0->pt[1].x=g.cp.x+g.r;
				pPW0->pt[1].y=g.cp.y-g.r;
				pPW0->pt[2].x=g.cp.x+g.r;
				pPW0->pt[2].y=g.cp.y+g.r;
				pPW0->pt[3].x=g.cp.x-g.r;
				pPW0->pt[3].y=g.cp.y+g.r;
				if((g.check & LEFT_SHIFT06)==LEFT_SHIFT06)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(int i=0;i<4;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}
				pPW0->lcolor=g.lcolor;
				pPW0->bcolor1=pPW0->bcolor2=g.fcolor;
				pPW0->width=g.swidth<1?1:g.swidth;				
			}
		}
		break;
	case GTYPE_ELLIPSE://ellipse椭圆
		{
			G_ELLIPSE g;
			N_CIRCLE* pPW0=NULL;
			if(pFigure->GetFigure(&g,sizeof(G_ELLIPSE)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_CIRCLE_TYPE;
				graph->attr.size=sizeof(N_RECT);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_CIRCLE*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->pt[0].x=g.cp.x-g.rx;
				pPW0->pt[0].y=g.cp.y-g.ry;
				pPW0->pt[1].x=g.cp.x+g.rx;
				pPW0->pt[1].y=g.cp.y-g.ry;
				pPW0->pt[2].x=g.cp.x+g.rx;
				pPW0->pt[2].y=g.cp.y+g.ry;
				pPW0->pt[3].x=g.cp.x-g.rx;
				pPW0->pt[3].y=g.cp.y+g.ry;
				if((g.check & LEFT_SHIFT07)==LEFT_SHIFT07)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(int i=0;i<4;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}
				pPW0->lcolor=g.lcolor;
				pPW0->bcolor1=pPW0->bcolor2=g.fcolor;
				pPW0->width=g.swidth<1?1:g.swidth;				
			}
		}
		break;
	case GTYPE_TEXT://text文本
		{
			G_TEXT g;
			N_TEXT* pPW0=NULL;
			if(pFigure->GetFigure(&g,sizeof(G_TEXT)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_TEXT_TYPE;
				graph->attr.size=sizeof(N_TEXT);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_TEXT*)graph->graph;
				memset(pPW0,0,graph->attr.size);

				memset(&pPW0->font,0,sizeof(LOGFONT));
				pPW0->font.lfWeight=FW_NORMAL;
				pPW0->font.lfHeight=(int)(g.fsize);
				pPW0->font.lfWidth=(int)(g.fsize*0.5);
				pPW0->font.lfItalic=g.italic;
				pPW0->font.lfUnderline=g.underline;
				pPW0->font.lfCharSet=DEFAULT_CHARSET;
				pPW0->font.lfOutPrecision=OUT_DEFAULT_PRECIS;
				pPW0->font.lfClipPrecision=CLIP_DEFAULT_PRECIS;
				pPW0->font.lfQuality=DEFAULT_QUALITY;
				pPW0->font.lfPitchAndFamily=DEFAULT_PITCH;
				ChangeFontFaceName(g.lfFace,pPW0->font.lfFaceName);
				
				if(g.wmode==1)
				{
					pPW0->pt[0].x=g.lt.x;
					pPW0->pt[0].y=g.lt.y-g.fsize;
					pPW0->pt[1].x=g.lt.x+g.fsize;
					pPW0->pt[1].y=g.lt.y-g.fsize;
					pPW0->pt[2].x=g.lt.x+g.fsize;
					pPW0->pt[2].y=g.lt.y+strlen(g.szText)*g.fsize*0.5;
					pPW0->pt[3].x=g.lt.x;
					pPW0->pt[3].y=g.lt.y+strlen(g.szText)*g.fsize*0.5;
				}
				else
				{
					pPW0->pt[0].x=g.lt.x;
					pPW0->pt[0].y=g.lt.y-g.fsize;
					pPW0->pt[1].x=g.lt.x+strlen(g.szText)*g.fsize*0.5;
					pPW0->pt[1].y=g.lt.y-g.fsize;
					pPW0->pt[2].x=g.lt.x+strlen(g.szText)*g.fsize*0.5;
					pPW0->pt[2].y=g.lt.y;
					pPW0->pt[3].x=g.lt.x;
					pPW0->pt[3].y=g.lt.y;
				}
				pPW0->zm=1.0;
				strcpy(pPW0->text,g.szText);
				pPW0->autofill=0;
				pPW0->color=g.fcolor;
				pPW0->style=0;
				if((g.check & LEFT_SHIFT09)==LEFT_SHIFT09)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(int i=0;i<4;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}
			}
		}
		break;
	case GTYPE_ARC://幅角
		{
			G_ARC g;
			N_ARC* pPW0=NULL;
			if(pFigure->GetFigure(&g,sizeof(G_ARC)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_ARC_TYPE;
				graph->attr.size=sizeof(N_ARC);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_ARC*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->pt[0].x=g.center.x-g.rx;
				pPW0->pt[0].y=g.center.y-g.ry;
				pPW0->pt[1].x=g.center.x+g.rx;
				pPW0->pt[1].y=g.center.y-g.ry;
				pPW0->pt[2].x=g.center.x+g.rx;
				pPW0->pt[2].y=g.center.y+g.ry;
				pPW0->pt[3].x=g.center.x-g.rx;
				pPW0->pt[3].y=g.center.y+g.ry;
				POINT ptStart=g.sp;
				POINT ptEnd=g.ep;
				if((g.check & LEFT_SHIFT11)==LEFT_SHIFT11)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(int i=0;i<4;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
					ptStart=PointMatrix(ptStart,&mx);
					ptEnd=PointMatrix(ptEnd,&mx);
				}
				pPW0->color=g.lcolor;
				pPW0->autozoom=0;
				pPW0->width=g.swidth<1?1:g.swidth;

				ptStart.x=ptStart.x-g.center.x;
				ptStart.y=ptStart.y-g.center.y;
				ptEnd.x=ptEnd.x-g.center.x;
				ptEnd.y=ptEnd.y-g.center.y;
				
				double dAngS,dAngE;
				//本系统总是逆画弧，顺逆转换
				if(g.sweep==1)
				{
					dAngE=atan2(ptStart.y,ptStart.x)/PI*180;
					dAngS=atan2(ptEnd.y,ptEnd.x)/PI*180;
				}
				else
				{
					dAngS=atan2(ptStart.y,ptStart.x)/PI*180;
					dAngE=atan2(ptEnd.y,ptEnd.x)/PI*180;
				}			
				dAngE=-dAngE;dAngS=-dAngS;//本地坐标Y轴在上，转换
				
				pPW0->start=(short)((int)dAngS);
				pPW0->end=(short)((int)dAngE);
			}
		}
		break;
	/*case GTYPE_IMAGE://image图像
		{
			G_IMAGE g;
			if(pFigure->GetFigure(&g,sizeof(G_IMAGE)))
			{
				;
			}
		}
		break;*/
	}

	return graph;
}

//SVG基本图转化为可视化潮流线
SVG_GRAPH* CTranslator::FigureToFlow(CFigure* pFigure,MATRIX* pMtx)
{
	SVG_GRAPH* graph=NULL;
	if(pFigure==NULL)
		return graph;

	MATRIX mx;
	BOOL bMatrix=FALSE;
	GTYPE gtype=pFigure->IsKindOf();
	N_FLOW* pPW0=NULL;
	switch(gtype)
	{
	case GTYPE_LINE://SVG线
		{
			G_LINE g;
			if(pFigure->GetFigure(&g,sizeof(G_LINE)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_FLOW_TYPE;
				graph->attr.size=sizeof(N_FLOW)+2*sizeof(DPOINT);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_FLOW*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->pt[0].x=g.sp.x;
				pPW0->pt[0].y=g.sp.y;
				pPW0->pt[1].x=g.ep.x;
				pPW0->pt[1].y=g.ep.y;
				pPW0->ptsum=2;
				pPW0->linewidth=g.swidth;
				pPW0->color2=pPW0->color1=g.lcolor;
				if((g.check & LEFT_SHIFT06)==LEFT_SHIFT06)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx==NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(int i=0;i<pPW0->ptsum;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}
			}
		}
		break;
	case GTYPE_POLYL://polyline折线
		{
			G_POLYLINE g;
			if(pFigure->GetFigure(&g,sizeof(G_POLYLINE)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_FLOW_TYPE;
				graph->attr.size=sizeof(N_FLOW)+g.ptnum*sizeof(DPOINT);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_FLOW*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->ptsum=g.ptnum;
				pPW0->linewidth=g.swidth;
				pPW0->color2=pPW0->color1=g.lcolor;
				for(int i=0;i<pPW0->ptsum;i++)
				{
					pPW0->pt[i].x=g.pt[i].x;
					pPW0->pt[i].y=g.pt[i].y;
				}
				if((g.check & LEFT_SHIFT04)==LEFT_SHIFT04)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(i=0;i<pPW0->ptsum;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}
			}
		}
		break;
	}

	return graph;
}


//转换图元
BOOL CTranslator::TranslateSymGrp(CFigureGroup *pGroup, void* pSvgVtr)
{
	BOOL bReturn=FALSE;
	SVGGRAPHVTR* pgrp=(SVGGRAPHVTR*)pSvgVtr;
	if(pGroup==NULL || pgrp==NULL)
		return bReturn;
	if(pGroup->GetFirstFigure())
	{
		CFigure *pFigure=NULL;
		while((pFigure=pGroup->GetNextFigure())!=NULL)
		{
			SVG_GRAPH* pGraph=NULL;
			if(pFigure->IsKindOf()==GTYPE_GUSE)//调用其他图元
			{
				G_GUSE g;
				if(pFigure->GetFigure(&g,sizeof(G_GUSE)))
				{
					CFigureGroup* pGrp=(CFigureGroup*)g.use;
					if(pGrp!=NULL && pGrp->GetFirstFigure())
					{
						CFigure *pFig=NULL;
						while((pFig=pGroup->GetNextFigure())!=NULL)
						{
							pGraph=FigureToGraph(pFig,NULL);
							if(pGraph!=NULL)
							{
								//是否需要处理成N_ESITE_TYPE ???
								pgrp->push_back(pGraph);
								bReturn=TRUE;
							}
						}
					}
				}
			}
			else//普通图形
			{
				pGraph=FigureToGraph(pFigure,NULL);
				if(pGraph!=NULL)
				{
					pgrp->push_back(pGraph);
					bReturn=TRUE;
				}
			}
		}
	}
	return bReturn;
}

//图元图形层转换
BOOL CTranslator::LayerEleGrp(CLayer *pLayer,unsigned char etype,MATRIX* pVbMatrix)
{
	if(pLayer->GetFirstGraph())
	{
		CGraph* pGraph=NULL;
		while((pGraph=pLayer->GetNextGraph())!=NULL)
		{
			SVG_GRAPH* pSGraph=GetEleGraph(pGraph, etype,pVbMatrix);
			
			if(pSGraph!=NULL)
				m_pCurLayer->gVtr.push_back(pSGraph);
		}
		return TRUE;
	}
	else
		return FALSE;
}

//SVG基本图形转化为可视化连接线
SVG_GRAPH* CTranslator::FigureToConnect(CFigure *pFigure,MATRIX* pMtx)
{
	SVG_GRAPH* graph=NULL;
	if(pFigure==NULL)
		return graph;

	MATRIX mx;
	BOOL bMatrix=FALSE;
	GTYPE gtype=pFigure->IsKindOf();
	N_CONLINE* pPW0=NULL;
	switch(gtype)
	{
	case GTYPE_LINE://SVG线
		{
			G_LINE g;
			if(pFigure->GetFigure(&g,sizeof(G_LINE)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_CONLINE_TYPE;
				graph->attr.size=sizeof(N_CONLINE)+2*sizeof(DPOINT);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_CONLINE*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->pt[0].x=g.sp.x;
				pPW0->pt[0].y=g.sp.y;
				pPW0->pt[1].x=g.ep.x;
				pPW0->pt[1].y=g.ep.y;
				pPW0->ptsum=2;
				pPW0->width=g.swidth;
				if((g.check & LEFT_SHIFT06)==LEFT_SHIFT06)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(int i=0;i<pPW0->ptsum;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}
			}
		}
		break;
	case GTYPE_POLYL://polyline折线
		{
			G_POLYLINE g;
			if(pFigure->GetFigure(&g,sizeof(G_POLYLINE)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_CONLINE_TYPE;
				graph->attr.size=sizeof(N_CONLINE)+g.ptnum*sizeof(DPOINT);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_CONLINE*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->ptsum=g.ptnum;
				pPW0->width=g.swidth;
				for(int i=0;i<pPW0->ptsum;i++)
				{
					pPW0->pt[i].x=g.pt[i].x;
					pPW0->pt[i].y=g.pt[i].y;
				}
				if((g.check & LEFT_SHIFT04)==LEFT_SHIFT04)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(i=0;i<pPW0->ptsum;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}
			}
		}
		break;
	}

	return graph;
}

//SVG基本图形组转化为可视化基本图形
BOOL CTranslator::CGraphToGraph(CGraph *pGraph, void* pSvgVtr,MATRIX* pMtx)
{
	BOOL bMatrix=FALSE;
	SVGGRAPHVTR* pGrpVtr=(SVGGRAPHVTR*)pSvgVtr;
	if(pGraph==NULL || pSvgVtr==NULL)
		return FALSE;

	const MATRIX* pMtrix=pGraph->GetMatrix();
	MATRIX mx;
	if(pMtrix!=NULL)
	{
		memcpy(&mx,pMtrix,sizeof(MATRIX));
		if(pMtx!=NULL)
			MutiMatrix(&mx,pMtx);
		bMatrix=TRUE;
	}
	if(bMatrix || pMtx!=NULL)
	{
		if(!bMatrix && pMtx!=NULL)
		{
			memcpy(&mx,pMtx,sizeof(MATRIX));
			bMatrix=TRUE;
		}
	}
	
	BOOL bReturn=FALSE;
	if(pGraph->GetFirstGraph())
	{
		CGraph* pGrp=NULL;
		while((pGrp=pGraph->GetNextGraph())!=NULL)
		{
			if(bMatrix)
				bReturn|=CGraphToGraph(pGrp,pSvgVtr,&mx);
			else
				bReturn|=CGraphToGraph(pGrp,pSvgVtr,NULL);
		}
	}
	
	SVG_GRAPH* graph=NULL;
	if(pGraph->GetFirstFigure())
	{
		CFigure *pFigure=NULL;
		while((pFigure=pGraph->GetNextFigure())!=NULL)
		{
			if(bMatrix)
				graph=FigureToGraph(pFigure,&mx);
			else
				graph=FigureToGraph(pFigure,NULL);
			if(graph!=NULL)
			{
				pGrpVtr->push_back(graph);
				bReturn=TRUE;
			}
		}
	}

	if(pGraph->GetFigureGroup()!=NULL)
	{
		graph=GetEleGraph(pGraph, 0,pMtx);
		if(graph!=NULL)
		{
			pGrpVtr->push_back(graph);
			bReturn=TRUE;
		}
	}

	return bReturn;
}

//SVG基本图形组转化为可视化按钮
SVG_GRAPH* CTranslator::FigureToButton(CFigure *pFigure, MATRIX *pMtx)
{
	SVG_GRAPH* graph=NULL;
	if(pFigure==NULL)
		return graph;

	MATRIX mx;
	BOOL bMatrix=FALSE;
	GTYPE gtype=pFigure->IsKindOf();
	N_PUSH* pPW0=NULL;
	switch(gtype)
	{
	case GTYPE_RECT:
		{
			G_RECT g;
			if(pFigure->GetFigure(&g,sizeof(G_RECT)))
			{
				if(g.check&LEFT_SHIFT05==LEFT_SHIFT05)
				{
					graph=FigureToGraph(pFigure,pMtx);
					if(graph!=NULL)
						m_pCurLayer->gVtr.push_back(graph);
				}

				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_PUSH_TYPE;
				graph->attr.size=sizeof(N_PUSH);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_PUSH*)graph->graph;
				memset(pPW0,0,graph->attr.size);
				pPW0->id=graph->attr.ID;
				pPW0->cmdtype=1;
				pPW0->style=1;//0=普通按钮
				pPW0->zm=1;
				pPW0->spicid=-1;

				pPW0->pt[0].x=g.lt.x;
				pPW0->pt[0].y=g.lt.y;
				pPW0->pt[1].x=g.lt.x+g.width;
				pPW0->pt[1].y=g.lt.y;
				pPW0->pt[2].x=g.lt.x+g.width;
				pPW0->pt[2].y=g.lt.y+g.height;
				pPW0->pt[3].x=g.lt.x;
				pPW0->pt[3].y=g.lt.y+g.height;
				if((g.check & LEFT_SHIFT07)==LEFT_SHIFT07)//矩阵有效
				{
					memcpy(&mx,&g.mx,sizeof(MATRIX));
					if(pMtx!=NULL)
						MutiMatrix(&mx,pMtx);
					bMatrix=TRUE;
				}
				if(bMatrix || pMtx!=NULL)
				{
					if(!bMatrix && pMtx!=NULL)
						memcpy(&mx,pMtx,sizeof(MATRIX));
					for(int i=0;i<4;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx);
				}

				char buff[256]={0};
				char* pStart=(char*)pFigure->GetHref();
				if(pStart!=NULL)
				{
					pStart=strchr(pStart,'\'');
					pStart++;
					strcpy(buff,pStart);
					if((pStart=strchr(buff,'.'))!=NULL)
					{
						pStart++;
						strcpy(pStart,"pw0");
						sprintf(pPW0->command,"%s 0",buff);
					}
				}
			}
		}
		break;
	}
	return graph;
}

void CTranslator::ChangeFontFaceName(char *oldname, char *newname)
{
	if(oldname==NULL || newname==NULL)
		return;

	int j=-1;
	for(int i=0;i<20;i++)
	{
		if(strcmp(fontnm[i*2+1],oldname)==0)
		{
			j=i;
			break;
		}
	}
	if(j==-1)
	{
		strcpy(newname,oldname);
		return;
	}
	strcpy(newname,fontnm[j*2]);
}

SVG_GRAPH* CTranslator::FigureToAnalog(CGraph *pGraph, MATRIX *pMtx)
{
	SVG_GRAPH* graph=NULL;
	if(pGraph==NULL)
		return graph;

	BOOL bMatrix=FALSE;
	const MATRIX* pMtrix=pGraph->GetMatrix();
	MATRIX mx;
	if(pMtrix!=NULL)
	{
		memcpy(&mx,pMtrix,sizeof(MATRIX));
		if(pMtx!=NULL)
			MutiMatrix(&mx,pMtx);
		bMatrix=TRUE;
	}
	if(bMatrix || pMtx!=NULL)
	{
		if(!bMatrix && pMtx!=NULL)
		{
			memcpy(&mx,pMtx,sizeof(MATRIX));
			bMatrix=TRUE;
		}
	}

	if(pGraph->GetFirstFigure())
	{
		CFigure *pFigure=NULL;
		while((pFigure=pGraph->GetNextFigure())!=NULL)
		{
			if(GTYPE_TEXT!=pFigure->IsKindOf())
				continue;

			G_TEXT g;
			N_ANL* pPW0=NULL;
			MATRIX mx2;
			if(pFigure->GetFigure(&g,sizeof(G_TEXT)))
			{
				graph=new SVG_GRAPH;
				memset(graph,0,sizeof(SVG_GRAPH));
				graph->attr.type=N_ANL_TYPE;
				graph->attr.size=sizeof(N_ANL);
				graph->attr.ID=GetGraphID();

				graph->graph=new char[graph->attr.size];
				pPW0=(N_ANL*)graph->graph;
				memset(pPW0,0,graph->attr.size);

				memset(&pPW0->lf,0,sizeof(LOGFONT));
				pPW0->lf.lfWeight=FW_NORMAL;
				pPW0->lf.lfHeight=(int)(g.fsize);
				pPW0->lf.lfWidth=(int)(g.fsize*0.5);
				pPW0->lf.lfItalic=g.italic;
				pPW0->lf.lfUnderline=g.underline;
				pPW0->lf.lfCharSet=DEFAULT_CHARSET;
				pPW0->lf.lfOutPrecision=OUT_DEFAULT_PRECIS;
				pPW0->lf.lfClipPrecision=CLIP_DEFAULT_PRECIS;
				pPW0->lf.lfQuality=DEFAULT_QUALITY;
				pPW0->lf.lfPitchAndFamily=DEFAULT_PITCH;
				ChangeFontFaceName(g.lfFace,pPW0->lf.lfFaceName);

				pPW0->pt[0].x=g.lt.x;
				pPW0->pt[0].y=g.lt.y-g.fsize;
				pPW0->pt[1].x=g.lt.x+strlen(g.szText)*g.fsize*0.5;
				pPW0->pt[1].y=g.lt.y-g.fsize;
				pPW0->pt[2].x=g.lt.x+strlen(g.szText)*g.fsize*0.5;
				pPW0->pt[2].y=g.lt.y;
				pPW0->pt[3].x=g.lt.x;
				pPW0->pt[3].y=g.lt.y;
				if((g.check & LEFT_SHIFT09)==LEFT_SHIFT09)//矩阵有效
				{

					memcpy(&mx2,&g.mx,sizeof(MATRIX));
					if(bMatrix)
						MutiMatrix(&mx2,&mx);
					bMatrix=TRUE;
				}
				else if(bMatrix)
						memcpy(&mx2,&mx,sizeof(MATRIX));
				if(bMatrix)
				{
					for(int i=0;i<4;i++)
						pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx2);
				}

				pPW0->zm=1.0;
				pPW0->acolor=RGB(255,0,0);
				pPW0->ncolor=g.fcolor;
				pPW0->xs=2;
				pPW0->style=0;

				//const METADATA* pMeta=pGraph->GetMeasRef();
				const char* pMeta=pGraph->GetName();
				if(pMeta!=NULL)
				{
					const char* pName=GetAnalogAtr(pMeta,pPW0->did,pPW0->dtype,pPW0->xsmode);
					if(pName!=NULL && strlen(pName)>0)
						strcpy(pPW0->dev_name,pName);
				}
			}
		}
	}
	return graph;
}

const char* CTranslator::GetAnalogAtr(const char *objectid, long &id, BYTE &type, BYTE &mode)
{
	DWORD devNU=0;
	int devType,mType,mpos;
	const char* pName=ExchangeIDName((char*)objectid,devType,devNU,mType,mpos);
	if(pName==NULL)
		return NULL;
	id=devNU;

	//0=发电机 1=交流线路 2=直流线路 3=母线 4=负荷  5=2绕组变压器 6=3绕组变压器 7=电容器 8=电抗器 9=SVC 15=非设备量测
	type=0;
	mode=0;
	switch(devType)
	{
	case 32: //母线
		type=3;
		switch(mType)
		{
		  case MEASURE_TYPE_V:  
		  case MEASURE_TYPE_Vab:  
		  case MEASURE_TYPE_Vbc:
		  case MEASURE_TYPE_Vca:  
			  mode=2;
			  break;
		}
		break;
	case 33: //交流线路
		type=1;
		switch(mType)
		{
		case MEASURE_TYPE_P:
			{
				if(mpos==2)
					mode=5;
				else
					mode=3;
			}
			break;
		case MEASURE_TYPE_Q:
			{
				if(mpos==2)
					mode=6;
				else
					mode=4;
			}
			break;
		}
		break;
	case 7: //变压器
		type=6;
		switch(mType)
		{
		  case MEASURE_TYPE_Pos:  mode=0;
			  break;
		  case MEASURE_TYPE_P:
			  {
				  if(mpos==2)
					mode=4;
				  else
					mode=1;
			  }
			  break;
		  case MEASURE_TYPE_Q:
			  {
				  if(mpos==2)
					mode=5;
				  else
					mode=2;
			  }
			  break;
		  case MEASURE_TYPE_I:
			  {
				  if(mpos==2)
					mode=6;
				  else
					mode=3;
			  }
			  break;
		}
		break;
	case 8: //变压器
		type=6;
		switch(mType)
		{
		  case MEASURE_TYPE_Pos:  mode=0;
			  break;
		  case MEASURE_TYPE_P:
			  {
				  if(mpos==2)
					mode=4;
				  else if(mpos==3)
					mode=7;
				  else
					mode=1;
			  }
			  break;
		  case MEASURE_TYPE_Q:
			  {
				  if(mpos==2)
					mode=5;
				  else if(mpos==3)
					mode=8;
				  else
					mode=2;
			  }
			  break;
		  case MEASURE_TYPE_I:
			  {
				  if(mpos==2)
					mode=6;
				  else if(mpos==3)
					mode=9;
				  else
					mode=3;
			  }
			  break;
		}
		break;
	case 1: //发电机
		type=0;
		switch(mType)
		{
		  case MEASURE_TYPE_P:  mode=1;
			  break;
		  case MEASURE_TYPE_Q:  mode=2;
			  break;
		}
		break;
	case 3: //负荷
		type=4;
		switch(mType)
		{
		  case MEASURE_TYPE_P:  mode=1;
			  break;
		  case MEASURE_TYPE_Q:  mode=2;
			  break;
		}
		break;
	case 5: //电抗
		type=8;
		mode=0;
		break;
	case 19:
		{
			type=14;//设备量测
			mode=0;
		}
		break;
	case 20:
		{
			type=15;//非设备量测
			mode=0;
		}
		break;
	default:
		return NULL;
	}

	return pName;
}

//SVG基本图形组转化为母线
SVG_GRAPH* CTranslator::FigureToBus(CGraph *pGraph, MATRIX *pMtx)
{
	SVG_GRAPH* graph=NULL;
	if(pGraph==NULL)
		return graph;

	BOOL bMatrix=FALSE;
	const MATRIX* pMtrix=pGraph->GetMatrix();
	MATRIX mx;
	if(pMtrix!=NULL)
	{
		memcpy(&mx,pMtrix,sizeof(MATRIX));
		if(pMtx!=NULL)
			MutiMatrix(&mx,pMtx);
		bMatrix=TRUE;
	}
	if(bMatrix || pMtx!=NULL)
	{
		if(!bMatrix && pMtx!=NULL)
		{
			memcpy(&mx,pMtx,sizeof(MATRIX));
			bMatrix=TRUE;
		}
	}

//	if(pGraph->GetFirstGraph())
//	{
//		CGraph *pGraph2=pGraph->GetNextGraph();
//		if(pGraph2!=NULL)
		CGraph *pGraph2 = pGraph;
		if(pGraph2!=NULL)
		{
			if(pGraph2->GetFirstFigure())
			{
				CFigure *pFigure=NULL;
				while((pFigure=pGraph2->GetNextFigure())!=NULL)
				{
					G_POLYLINE g;
					N_BUS* pPW0=NULL;
					MATRIX mx2;
					if(pFigure->GetFigure(&g,sizeof(G_POLYLINE)))
					{
						graph=new SVG_GRAPH;
						memset(graph,0,sizeof(SVG_GRAPH));
						graph->attr.type=N_BUS_TYPE;
						graph->attr.size=sizeof(N_BUS);
						graph->attr.ID=GetGraphID();
						
						graph->graph=new char[graph->attr.size];
						pPW0=(N_BUS*)graph->graph;
						memset(pPW0,0,graph->attr.size);
						
						if(g.pt[0].y==g.pt[1].y)//水平
						{
							pPW0->pt[0].x=g.pt[0].x;
							pPW0->pt[0].y=g.pt[0].y-g.swidth;
							pPW0->pt[1].x=g.pt[1].x;
							pPW0->pt[1].y=g.pt[0].y-g.swidth;
							pPW0->pt[2].x=g.pt[1].x;
							pPW0->pt[2].y=g.pt[1].y+g.swidth;
							pPW0->pt[3].x=g.pt[0].x;
							pPW0->pt[3].y=g.pt[1].y+g.swidth;
						}
						else
						{
							pPW0->pt[0].x=g.pt[0].x-g.swidth;
							pPW0->pt[0].y=g.pt[0].y;
							pPW0->pt[1].x=g.pt[1].x+g.swidth;
							pPW0->pt[1].y=g.pt[0].y;
							pPW0->pt[2].x=g.pt[1].x+g.swidth;
							pPW0->pt[2].y=g.pt[1].y;
							pPW0->pt[3].x=g.pt[0].x-g.swidth;
							pPW0->pt[3].y=g.pt[1].y;
						}
						
						if((g.check & LEFT_SHIFT09)==LEFT_SHIFT09)//矩阵有效
						{
							
							memcpy(&mx2,&g.mx,sizeof(MATRIX));
							if(bMatrix)
								MutiMatrix(&mx2,&mx);
							bMatrix=TRUE;
						}
						else if(bMatrix)
							memcpy(&mx2,&mx,sizeof(MATRIX));
						if(bMatrix)
						{
							for(int i=0;i<4;i++)
								pPW0->pt[i]=PointMatrix(pPW0->pt[i],&mx2);
						}
						
						const CSS_STYLE* pCss=pGraph2->GetClass();//Figure/Graph?
						if(pCss!=NULL)
							pPW0->vl=pCss->vVol;
						
						const METADATA* pMeta=pGraph->GetPSRRef();
						if(pMeta!=NULL && strlen(pMeta->szID)>0)
						{
							pPW0->did=atoi(pMeta->szID);

							//strcpy(pPW0->dev_name,pMeta->szName);

							DWORD dwID;
							char* pName=NUtoName(pPW0->did,32,dwID);
							if(pName!=NULL)
							{
								strcpy(pPW0->dev_name,pName);
							}
						}
					}
				}
			}
		//}
	}
	return graph;
}

void CTranslator::SetEleMatrixTfm(SVG_GRAPH *pGraph, MATRIX *pMatrix)
{

	MATRIX mx;
	memcpy(&mx,pMatrix,sizeof(MATRIX));
	float fSx=sqrt(pMatrix->fa*pMatrix->fa+pMatrix->fb*pMatrix->fb);
	if(fSx>0)
	{
		mx.fa=pMatrix->fa/fSx;
		mx.fb=pMatrix->fb/fSx;
	}
	float fSy=sqrt(pMatrix->fc*pMatrix->fc+pMatrix->fd*pMatrix->fd);
	if(fSy>0)
	{
		mx.fc=pMatrix->fc/fSy;
		mx.fd=pMatrix->fd/fSy;
	}

	if(mx.fb==0.0f && mx.fc==0.0f && mx.fa==-1.0f && mx.fd==1.0f)
		pGraph->sym=SYM_YAXIS;
	else if(mx.fb==0.0f && mx.fc==0.0f && mx.fa==1.0f && mx.fd==-1.0f)
		pGraph->sym=SYM_XAXIS;
	else if(mx.fb==0.0f && mx.fc==0.0f && mx.fa==-1.0f && mx.fd==-1.0f)
		pGraph->sym=SYM_ORIG;
	else if(mx.fb==1.0f && mx.fc==1.0f && mx.fa==0.0f && mx.fd==0.0f)
		pGraph->sym=SYM_YXPOS;
	else if(mx.fb==-1.0f && mx.fc==-1.0f && mx.fa==0.0f && mx.fd==0.0f)
		pGraph->sym=SYM_YXNEG;

 	pGraph->fAngle=GetAngFromMatrix(pMatrix);
}
