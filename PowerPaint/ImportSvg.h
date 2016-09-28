// ImportSvg.h: interface for the CImportSvg class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_IMPORTSVG_H__BC1E37A6_9FDE_44A3_9EA8_D5B87ABE771F__INCLUDED_)
#define AFX_IMPORTSVG_H__BC1E37A6_9FDE_44A3_9EA8_D5B87ABE771F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct SVG_PAGE;
struct SVG_LAYER;
struct SVG_ELEGRP;
struct N_ELEGRP;

class CImportSvg  
{
public:
	BOOL ReadSvg(const char* pSvgFile);

	CImportSvg();
	virtual ~CImportSvg();
private:
	float     gdx,gdy;	//偏移量
	
	void AnalyseEgpSit(N_ELEGRP* pEgp);
	bool RotateEgp(N_ELEGRP *pOrg, N_ELEGRP *pDir, double dAngle);
	bool SymmetryEgp(N_ELEGRP *pOrg, N_ELEGRP *pDir, BYTE byType);
	bool RotaeEgpItem(WORD type,char* pBuff,double dAngle,POINT* pRotate);
	bool SymEgpItem(WORD type,char* pBuff,BYTE byType,void* pRt);
	int FindAEgp(char *name);
protected:
	//初始化页面参数
	virtual BOOL InitPage(SVG_PAGE* spage,const char* pName);
	//导入图层
	BOOL ImportLayer(SVG_LAYER* pLayer);
	//导入图元
	BOOL ImportEGP(SVG_ELEGRP* pEgp);
};

#endif // !defined(AFX_IMPORTSVG_H__BC1E37A6_9FDE_44A3_9EA8_D5B87ABE771F__INCLUDED_)
