// XmlParse.h: interface for the CXmlParse class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLPARSE_H__7C3530BC_6415_4981_BF09_AEE75878794A__INCLUDED_)
#define AFX_XMLPARSE_H__7C3530BC_6415_4981_BF09_AEE75878794A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlNode.h"

const int BRACKET_MAXLEN=2048;  //尖括号内容最大长度

class CXmlParse  
{
public:
	BOOL NodeParse(CXmlNode* pNodeParent);
	//解析XML字符串
	BOOL ParseXml(const char* pXmlStr,int len,const char* pRoot=NULL);
	//解析XML文件
	BOOL ParseXml(const char* pXmlFile,const char* pRoot=NULL);

	CXmlParse(XMLNODEVTR* pNodeVtr);
	virtual ~CXmlParse();
private:
	//取到到反括弧
	CXmlNode* GotoBracket(int &end);
	//到字符位置
	int GotoChar(const char end,char* pStr,int  max);
	//主解析函数
	BOOL MainParse(const char* pRoot=NULL);
	//取得一个字符
	int GetChar();

	XMLNODEVTR* m_pNodeVtr;

	char m_Buffer[BRACKET_MAXLEN];
	const char *m_pSrc; //源串
	char *m_pCur; //当前位置
	int m_iSrcLen; //源串长
	FILE* m_pf; //文件指针
};

#endif // !defined(AFX_XMLPARSE_H__7C3530BC_6415_4981_BF09_AEE75878794A__INCLUDED_)
