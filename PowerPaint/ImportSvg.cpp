// ImportSvg.cpp: implementation of the CImportSvg class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "PowerPaint.h"
#include "ImportSvg.h"
#include "gdata.h"
#include "comobj.h"
#include "math.h"
#include "..\SvgImp\SvgImp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern gdata dbm;
extern comobj cobj;
extern const double PI;

DPOINT RotatePoint(DPOINT pt,double dAng,POINT* pOrg=NULL);
DPOINT SymPoint(DPOINT pt,BYTE byType,DRECT* pRect);

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CImportSvg::CImportSvg()
{
	gdx=0.0f;
	gdy=0.0f;
}

CImportSvg::~CImportSvg()
{

}

//读取SVG
BOOL CImportSvg::ReadSvg(const char* pSvgFile)
{
	SVG_PAGE* spage=NULL;
	if(SvgImport((char*)pSvgFile,"Open2000",&spage))
	{
		//初始化页面
		InitPage(spage,pSvgFile);
		//导入图元
		for(SVGELEGRPVTR::iterator i=spage->egrpVtr.begin();i!=spage->egrpVtr.end();++i)
		{
			ImportEGP(*i);
		}

		//导入图形
		for(int j=0;j<spage->laynum;j++)
		{
			ImportLayer(&(spage->layer[j]));
		}
	}
	ReleaseSvgPage(spage);
	return FALSE;
}

//初始化页面
BOOL CImportSvg::InitPage(SVG_PAGE* spage,const char* pName)
{
	int w=spage->width;
	int h=spage->height;
	w=w==0 ? 1024:w;
	h=h==0 ? 768:h;

	dbm.pagesum=1;
	dbm.curpage=0;
	dbm.cpage=&dbm.page[0];

	dbm.cpage->head.width=w;
	dbm.cpage->head.height=h;
	dbm.cpage->head.BgColor=spage->bgcolor;
	dbm.cpage->curlay=0;
	dbm.cpage->laysum=1;
	dbm.cpage->index=0;
	dbm.cpage->head.flag=0xcccc;
	dbm.cpage->head.type=1;
	dbm.cpage->head.width=w;
	dbm.cpage->head.height=h;
	dbm.cpage->head.laysum=1;
	dbm.cpage->head.imgID=-1;	
	dbm.cpage->head.showbyrt=0;
	dbm.cpage->head.BgColor=0;

	char* pNM=strrchr(pName,'\\');
	if(pNM!=NULL)
	{
		pNM++;
		strcpy(dbm.cpage->head.Name,pNM);
		pNM=strchr(dbm.cpage->head.Name,'.');
		if(pNM!=NULL)
			*pNM=0;
	}

	return TRUE;
}

//导入图元
BOOL CImportSvg::ImportEGP(SVG_ELEGRP *pEgp)
{
	if(pEgp==NULL)
		return FALSE;

	//申请一个号
	if(!cobj.AddAEmptyEGP(1)) return FALSE;

	CDRect rt1;
	int curnum=cobj.egpsum-1; //取当前号

	//先画第一个
	strcpy(cobj.segp[curnum].name1,pEgp->name);
	strcat(cobj.segp[curnum].name1,"_1");
	strcpy(cobj.segp[curnum].name2,pEgp->name);
	strcat(cobj.segp[curnum].name2,"_2");

	cobj.egp[curnum].id=pEgp->id;
	cobj.egp[curnum].type=pEgp->type;
	cobj.egp[curnum].subtype=pEgp->subtype;

	//读取图元
	for(SVGGRAPHVTR::iterator itr=pEgp->g1Vtr.begin();itr!=pEgp->g1Vtr.end();++itr)
	{
		//加入到图元组中
		cobj.AddAEGP(curnum,0,(*itr)->attr,(*itr)->graph);
		if(pEgp->g2Vtr.size()==0)
			cobj.AddAEGP(curnum,1,(*itr)->attr,(*itr)->graph);
	}

	//读取图元2
	for(itr=pEgp->g2Vtr.begin();itr!=pEgp->g2Vtr.end();++itr)
	{
		//加入到图元组中
		cobj.AddAEGP(curnum,1,(*itr)->attr,(*itr)->graph);
	}

	//重置图元矩形
	cobj.ResetAEgpRt(curnum,rt1);
	//分析图元端子
	AnalyseEgpSit(&cobj.egp[curnum]);
	return TRUE;
}

//导入图层
BOOL CImportSvg::ImportLayer(SVG_LAYER *pLayer)
{
	if(pLayer==NULL)
		return FALSE;

	for(SVGGRAPHVTR::iterator itr=pLayer->gVtr.begin();itr!=pLayer->gVtr.end();++itr)
	{
		SVG_GRAPH* pGraph=*itr;
		if(pGraph->attr.type==66 && (fabs(pGraph->fAngle)>0 || pGraph->sym==SYM_XAXIS || pGraph->sym==SYM_YAXIS))//需要旋转的组合图元
		{
			N_ELEGRPA* pgrpa=(N_ELEGRPA*)pGraph->graph;
			for(int i=0;i<cobj.egpsum;i++)
			{
				if(cobj.egp[i].id==pgrpa->egrpid)
				{
					char name1[64];
					strcpy(name1,cobj.segp[i].name1);
					char* pExt1=strchr(name1,'_');
					if(pExt1!=NULL)
					{
						if(pGraph->sym==SYM_XAXIS)
							sprintf(pExt1,"X_1");
						else if(pGraph->sym==SYM_YAXIS)
							sprintf(pExt1,"Y_1");
						else
							sprintf(pExt1,"R%d_1",(int)(abs(pGraph->fAngle*180/PI)));

						int newid=FindAEgp(name1);
						if(newid<0)//如没有，套用现有图元建立
						{
							if(!cobj.AddAEmptyEGP(1)) return -1;
							int curnum=cobj.egpsum-1; //取当前号
							strcpy(cobj.segp[curnum].name1,name1);			
							cobj.egp[curnum].type=cobj.egp[i].type;
							cobj.egp[curnum].subtype=cobj.egp[i].subtype;

							//对现有图元进行旋转
							if(pGraph->sym==SYM_XAXIS||pGraph->sym==SYM_YAXIS)
								SymmetryEgp(&cobj.egp[i],&cobj.egp[curnum],pGraph->sym);
							else
								RotateEgp(&cobj.egp[i],&cobj.egp[curnum],pGraph->fAngle);

							CDRect rt1;
							cobj.ResetAEgpRt(curnum,rt1);
							pgrpa->egrpid=cobj.egp[curnum].id;
						}
						else
						{
							pgrpa->egrpid=newid;
						}
					}

					dbm.AddAObject(pGraph->attr,pGraph->graph);
					break;
				}
			}
		}
		else
		{
			dbm.AddAObject(pGraph->attr,pGraph->graph);
		}
	}

	return TRUE;
}

void CImportSvg::AnalyseEgpSit(N_ELEGRP* pEgp)
{
	int i,j,type;
	CDRect  art;
	BASE0 *bs[3];
	//将所属置0
	for(i=0;i<pEgp->bsum1;i++){
	  pEgp->bs1[i].attr.belong=0;
	}
	for(i=0;i<pEgp->bsum2;i++){
	  pEgp->bs2[i].attr.belong=0;
	}
	for(i=0;i<pEgp->bsum1;i++){
		if(pEgp->bs1[i].attr.type==11){ //type=11为电气端子
			pEgp->bs1[i].ort.GetDRECT(pEgp->srt[pEgp->sitesum]);
			pEgp->bs1[i].attr.belong=pEgp->sitesum+1;
			pEgp->sitesum++;
		}
	  if(pEgp->sitesum>=3) break;
	}
	
	//如果不是变压器，就退出处理
	if(pEgp->type!=1||(pEgp->type==1&&
		pEgp->subtype!=7&&pEgp->subtype!=8))
	{
		for(i=0;i<pEgp->bsum1;i++){
			pEgp->bs1[i].attr.belong=1;
		}
		for(i=0;i<pEgp->bsum2;i++){
			pEgp->bs2[i].attr.belong=1;
		}
		return;
	}

	//查找相交圆
	int n=0;
	for(i=0;i<pEgp->sitesum;i++)
	{
		//先分析圆的
		for(j=0;j<pEgp->bsum1;j++)
		{
			type=pEgp->bs1[j].attr.type;
			if(type==3&&pEgp->bs1[j].attr.belong==0)
			{
				art.SetDRECT(pEgp->srt[i]);
				art&=pEgp->bs1[j].ort;
				if(!art.IsRectEmpty())
				{
					bs[n]=&pEgp->bs1[j];
					bs[n]->attr.belong=i+1;
					n++;
					break;
				}
			}
		}
	}
	for(i=n;i<pEgp->sitesum;i++)
	{
		//先分析圆弧的
		for(j=0;j<pEgp->bsum1;j++)
		{
			type=pEgp->bs1[j].attr.type;
		    if(type==6&&pEgp->bs1[j].attr.belong==0)
			{
				art.SetDRECT(pEgp->srt[i]);
				art&=pEgp->bs1[j].ort;
				if(!art.IsRectEmpty())
				{
					bs[n]=&pEgp->bs1[j];
					bs[n]->attr.belong=i+1;
					n++;
					break;
				}
			}
		}
	}

	CDRect rt1,rt2;
	CDPoint pt1,pt2;
	//开始计算着色图形
	for(i=0;i<pEgp->sitesum;i++)
	{
		rt1=bs[i]->ort;
		for(j=0;j<pEgp->bsum1;j++)
		{
			if(pEgp->bs1[j].attr.belong==0)
			{
				rt2=pEgp->bs1[j].ort;
				pt1=CDPoint(rt2.left,rt2.top);
				pt2=CDPoint(rt2.right,rt2.bottom);
				if(rt1.PtInRect(pt1)&&rt1.PtInRect(pt2)) pEgp->bs1[j].attr.belong=i+1;
			}
		}
	}
	for(i=0;i<pEgp->sitesum;i++)
	{
		rt1=bs[i]->ort;
		rt1.left--;rt1.top--;
		rt1.right++;
		rt1.bottom++;
		for(j=0;j<pEgp->bsum2;j++)
		{
			if(pEgp->bs2[j].attr.belong==0)
			{
				rt2=pEgp->bs2[j].ort;
				pt1=CDPoint(rt2.left,rt2.top);
				pt2=CDPoint(rt2.right,rt2.bottom);
				if(rt1.PtInRect(pt1)&&rt1.PtInRect(pt2)) pEgp->bs2[j].attr.belong=i+1;
			}
		}
	}
}

int CImportSvg::FindAEgp(char *name)
{
	for(int i=0;i<cobj.egpsum;i++)
	{
		if(strcmp(name,cobj.segp[i].name1)==0)
		{
			return i;
		}
	}
	return -1;
}

bool CImportSvg::RotateEgp(N_ELEGRP *pOrg, N_ELEGRP *pDir, double dAngle)
{
	BASE0* pBase1=NULL;
	POINT ptRotate;
	char obuf[16000];
	double angle=dAngle;
	
	ptRotate.x=(pOrg->rt1.left+pOrg->rt1.right)/2;
	ptRotate.y=(pOrg->rt1.top+pOrg->rt1.bottom)/2;
	if(pOrg->bsum1>0)
	{
		pBase1=(BASE0*)malloc(sizeof(BASE0)*pOrg->bsum1);
		//加入到图元组中
		for(int i=0;i<pOrg->bsum1;i++)
		{
			memset(obuf,0,16000);
			memcpy(obuf,pOrg->bs1[i].buf,pOrg->bs1[i].attr.size);
			RotaeEgpItem(pOrg->bs1[i].attr.type,obuf,angle,&ptRotate);
			pBase1[i].AddObject(pOrg->bs1[i].attr,obuf);
		}

		if(pDir->bs1!=NULL)
			free(pDir->bs1);
		pDir->bs1=pBase1;
		pDir->bsum1=pOrg->bsum1;
	}

	ptRotate.x=(pOrg->rt2.left+pOrg->rt2.right)/2;
	ptRotate.y=(pOrg->rt2.top+pOrg->rt2.bottom)/2;
	if(pOrg->bsum2>0)
	{
		pBase1=(BASE0*)malloc(sizeof(BASE0)*pOrg->bsum2);
		//加入到图元组中
		for(int i=0;i<pOrg->bsum2;i++)
		{
			memset(obuf,0,16000);
			memcpy(obuf,pOrg->bs2[i].buf,pOrg->bs2[i].attr.size);
			RotaeEgpItem(pOrg->bs2[i].attr.type,obuf,angle,&ptRotate);
			pBase1[i].AddObject(pOrg->bs2[i].attr,obuf);
		}
		if(pDir->bs2!=NULL)
			free(pDir->bs2);
		pDir->bs2=pBase1;
		pDir->bsum2=pOrg->bsum2;
		
	}
	return true;
}

bool CImportSvg::SymmetryEgp(N_ELEGRP *pOrg, N_ELEGRP *pDir, BYTE byType)
{
	BASE0* pBase1=NULL;
	char obuf[16000];
	if(pOrg->bsum1>0)
	{
		pBase1=(BASE0*)malloc(sizeof(BASE0)*pOrg->bsum1);
		//加入到图元组中
		for(int i=0;i<pOrg->bsum1;i++)
		{
			memset(obuf,0,16000);
			memcpy(obuf,pOrg->bs1[i].buf,pOrg->bs1[i].attr.size);
			SymEgpItem(pOrg->bs1[i].attr.type,obuf,byType,&pOrg->rt1);
			pBase1[i].AddObject(pOrg->bs1[i].attr,obuf);
		}

		if(pDir->bs1!=NULL)
			free(pDir->bs1);
		pDir->bs1=pBase1;
		pDir->bsum1=pOrg->bsum1;
	}

	if(pOrg->bsum2>0)
	{
		pBase1=(BASE0*)malloc(sizeof(BASE0)*pOrg->bsum2);
		//加入到图元组中
		for(int i=0;i<pOrg->bsum2;i++)
		{
			memset(obuf,0,16000);
			memcpy(obuf,pOrg->bs2[i].buf,pOrg->bs2[i].attr.size);
			SymEgpItem(pOrg->bs2[i].attr.type,obuf,byType,&pOrg->rt2);
			pBase1[i].AddObject(pOrg->bs2[i].attr,obuf);
		}
		if(pDir->bs2!=NULL)
			free(pDir->bs2);
		pDir->bs2=pBase1;
		pDir->bsum2=pOrg->bsum2;		
	}
	return true;
}

bool CImportSvg::SymEgpItem(WORD type,char* pBuff,BYTE byType,void* pRt)
{
	DRECT* pRectA=(DRECT*)pRt;
	switch(type)
	{
	case 1://多边形(N_DBX)
		{
			N_DBX* pDbx=(N_DBX*)pBuff;
			for(int j=0;j<pDbx->ptsum;j++)
			{
				pDbx->pt[j]=SymPoint(pDbx->pt[j],byType,pRectA);
			}
		}
		break;
	case 2://矩形(N_RECT)
		{
			N_RECT* pRect=(N_RECT*)pBuff;
			for(int j=0;j<4;j++)
			{
				pRect->pt[j]=SymPoint(pRect->pt[j],byType,pRectA);
			}
		}
		break;
	case 3://圆(N_CIRCLE)
		{
			N_CIRCLE* pCircle=(N_CIRCLE*)pBuff;
			for(int j=0;j<4;j++)
			{
				pCircle->pt[j]=SymPoint(pCircle->pt[j],byType,pRectA);
			}
		}
		break;
	case 6://弧(N_ARC)
		{
			N_ARC* pArc=(N_ARC*)pBuff;
			for(int j=0;j<4;j++)
				pArc->pt[j]=SymPoint(pArc->pt[j],byType,pRectA);

			short shAngle=pArc->start;
			if(byType==SYM_YAXIS)//SVG顺时针旋转，本系统逆旋
			{
				pArc->end=180-pArc->start;
				pArc->start=180-shAngle;
			}
			else if(byType==SYM_YAXIS)
			{
				pArc->end=360-pArc->start;
				pArc->start=360-shAngle;
			}
			pArc->start=pArc->start%360;pArc->end=pArc->end%360;
			
			if(pArc->start>pArc->end)
				pArc->start=pArc->start-360;
		}
		break;
	case 10://文本(N_TEXT)
		break;
	case 11://端子(N_ESITE)
		{
			N_ESITE* pSite=(N_ESITE*)pBuff;
			for(int j=0;j<4;j++)
			{
				pSite->pt[j]=SymPoint(pSite->pt[j],byType,pRectA);
			}
		}
		break;
	}
	return TRUE;
}

bool CImportSvg::RotaeEgpItem(WORD type,char* pBuff,double dAngle,POINT* pRotate)
{
	switch(type)
	{
	case 1://多边形(N_DBX)
		{
			N_DBX* pDbx=(N_DBX*)pBuff;
			for(int j=0;j<pDbx->ptsum;j++)
			{
				pDbx->pt[j]=RotatePoint(pDbx->pt[j],dAngle,pRotate);
			}
		}
		break;
	case 2://矩形(N_RECT)
		{
			N_RECT* pRect=(N_RECT*)pBuff;
			for(int j=0;j<4;j++)
			{
				pRect->pt[j]=RotatePoint(pRect->pt[j],dAngle,pRotate);
			}
		}
		break;
	case 3://圆(N_CIRCLE)
		{
			N_CIRCLE* pCircle=(N_CIRCLE*)pBuff;
			for(int j=0;j<4;j++)
			{
				pCircle->pt[j]=RotatePoint(pCircle->pt[j],dAngle,pRotate);
			}
		}
		break;
	case 6://弧(N_ARC)
		{
			N_ARC* pArc=(N_ARC*)pBuff;
			for(int j=0;j<4;j++)
				pArc->pt[j]=RotatePoint(pArc->pt[j],dAngle,pRotate);
			
			short shAngle=360-(short)(dAngle/PI*180);//SVG顺时针旋转，本系统逆旋
			
			pArc->start+=shAngle;pArc->end+=shAngle;
			pArc->start=pArc->start%360;pArc->end=pArc->end%360;
			
			if(pArc->start>pArc->end)
				pArc->start=pArc->start-360;
		}
		break;
	case 10://文本(N_TEXT)
		break;
	case 11://端子(N_ESITE)
		{
			N_ESITE* pSite=(N_ESITE*)pBuff;
			for(int j=0;j<4;j++)
			{
				pSite->pt[j]=RotatePoint(pSite->pt[j],dAngle,pRotate);
			}
		}
		break;
	}
	return TRUE;
}

DPOINT RotatePoint(DPOINT pt, double dAng,POINT* pOrg)
{
	DPOINT Temp=pt;
	if(pOrg!=NULL)
	{
		pt.x=pt.x-pOrg->x;
		pt.y=pt.y-pOrg->y;
	}

	Temp.x=pt.x*cos(dAng)-pt.y*sin(dAng);
	Temp.y=pt.x*sin(dAng)+pt.y*cos(dAng);

	if(pOrg!=NULL)
	{
		Temp.x=Temp.x+pOrg->x;
		Temp.y=Temp.y+pOrg->y;
	}

	return Temp;
}

DPOINT SymPoint(DPOINT pt,BYTE byType,DRECT* pRect)
{
	DPOINT Temp=pt;
	if(pRect!=NULL)
	{
		if(byType==SYM_YAXIS)
		{
			Temp.x=pRect->right-Temp.x;
		}
		else if(byType==SYM_XAXIS)
		{
			Temp.y=pRect->bottom-Temp.y;
		}
	}
	return Temp;
}