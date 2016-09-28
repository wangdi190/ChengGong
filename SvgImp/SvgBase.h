// SvgBase.h: interface for the CSvgBase class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SVGBASE_H__E94CD3EC_1E8E_416B_A9D5_DF3074DCF9E0__INCLUDED_)
#define AFX_SVGBASE_H__E94CD3EC_1E8E_416B_A9D5_DF3074DCF9E0__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "..\XmlTool\XmlTool.h"
#include "Translator.h"

struct SVG_PAGE;
struct PATHINFO	//路径信息
{
	PATHINFO(){memset(this,0,sizeof(PATHINFO));};
	char cmd;//路径命令
	BYTE byCnt;//参数数量
	float argv[16];//参数值
};

class CSvgBase  
{
public:
	//解析SVG文件
	virtual BOOL SvgParse(char* pFile,SVG_PAGE* page)=0;

	CSvgBase();
	virtual ~CSvgBase();

protected:
	//主解析过程
	virtual BOOL MainParse(IXmlNode* pNode);

	//****解码函数*****//
	//返回编码类型
	unsigned char GetCodeStyle(const char* pStyle){if(strcmp(pStyle,"UTF-8")==0) return 1;else return 0;};
	//返回视图框
	virtual BOOL GetViewBox(const char* pView,CRect* pRect);
	//取得图元
	virtual BOOL GetSymbol(IXmlNode* pNode);
	//电压定义
	virtual BOOL GetStyle(IXmlNode* pNode);
	//返回图层
	virtual BOOL GetLayer(IXmlNode* pNode);
	//返回嵌套图
	virtual BOOL GetGraph(IXmlNode *pNode,CGraph* pg);
	//返回图形
	virtual BOOL GetFigure(IXmlNode* pNode,FIGUREVTR* pFigVtr);
	//返回use标识信息
	virtual BOOL GetUse(IXmlNode* pNode,CGraph* pg);
	//返回metadata标识信息
	virtual BOOL GetMetaData(IXmlNode* pNode,CGraph* pg);

	//****解码基本图形元素*****//
	//返回线
	virtual BOOL GetSvgLine(IXmlNode* pNode,G_LINE* pLine);
	//返回矩形
	virtual BOOL GetSvgRect(IXmlNode* pNode,G_RECT* pRect);
	//返回折线
	virtual BOOL GetSvgPolyl(IXmlNode* pNode,G_POLYLINE* pPolyline);
	//返回多边
	virtual BOOL GetSvgPolyn(IXmlNode* pNode,G_POLYGON* pPolygon);
	//返回圆
	virtual BOOL GetSvgCircle(IXmlNode* pNode,G_CIRCLE* pCircle);
	//返回椭圆
	virtual BOOL GetSvgEllipse(IXmlNode* pNode,G_ELLIPSE* pEllips);
	//返回文本
	virtual BOOL GetSvgText(IXmlNode* pNode,G_TEXT* pText);
	//返回图像
	virtual BOOL GetSvgImage(IXmlNode* pNode,G_IMAGE* pImage);
	//返回路径
	virtual BOOL GetSvgPath(IXmlNode* pNode,G_PATH* pPath);
	//返回基本图形引用
	virtual BOOL GetSvgSymUse(IXmlNode* pNode,G_GUSE* pGUse);

	//返回图形变换矩阵
	BOOL GetTransform(const char* pTrans,int len,MATRIX* pMatrix);
	//返回路径图形
	BOOL GetPathFigure(G_PATH *path,FIGUREVTR* pFigVtr);

	//****辅助函数*****//
	//UTF转ASCII
	int Utf8ToASCII(const unsigned char* pUtf,int len,char *pASCII,int maxbuf);
	//查找class
	CSS_STYLE* SearchCssStyle(const char* pClass);
	//查找图元
	CFigureGroup* SearchFigureGroup(const char* pid);
	//图形组,多状态组成图元
	BOOL PolyOneGroup(CFigureGroup* pGroup,char* pFalse,char* pTrue,FIGUREELE* pEle);
	//图形组,多构建组成图元
	BOOL PolyOneGroup(CFigureGroup* pGroup,FIGUREELE* pEle);


	//视图矩形
	CRect m_viewBox;
	//编码方式0=ASCII,1=UTF8
	unsigned char m_byCode;
	//图元
	FIGUREELEVTR m_EleGrpVtr;
	//图元组
	FIGUREGRPVTR m_FigureGrpVtr;
	//类型定义表
	CSSSTYLEVTR m_CssStyleVtr;
	//图层表
	LAYERVTR m_LayerVtr;
	//转换器
	CTranslator* m_pTranslator;
private:
	//取得路径信息
	int GetPathInfo(const char* pPath,PATHINFO *pInfo, int max);
	//转换图形
	virtual BOOL Translate(SVG_PAGE* page)=0;
	//多态图元分析
	virtual BOOL PolyFigureGroup()=0;
	//根据类型取得电压等级
	virtual BOOL GetVolLevelByStyle(const char* pStype,BYTE &volLevel);
	//返回RGB颜色
	DWORD GetRGB(const char* pRGB);
};

template<class T> int SplitStr(const char* pScr,char split,T* pRet,int count)
{
	int i=0;
	const char* pStart=pScr;
	char buffer[256];
	while(strlen(pStart)>0 && i<count)
	{
		char* pEnd=NULL;
		int len=strlen(pStart);		
		for(int j=0;j<len;j++)
		{
			if(pStart[j]==split || pStart[j]==' ')//默认空格是分割符
			{
				pEnd=(char*)&pStart[j];
				break;
			}
		}

		len=pEnd-pStart;
		if(pEnd!=NULL && len<256 && len>0)
		{
			strncpy(buffer,pStart,len);
			buffer[len]=0;
			pRet[i++]=(T)atof(buffer);
			pEnd++;
			pStart=pEnd;
		}
		else
		{
			pRet[i++]=(T)atof(pStart);
			break;
		}
	}
	return i;
}

#endif // !defined(AFX_SVGBASE_H__E94CD3EC_1E8E_416B_A9D5_DF3074DCF9E0__INCLUDED_)
