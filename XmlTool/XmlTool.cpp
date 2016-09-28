// XmlTool.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "XmlParse.h"

//解析XML文件
XMLTOOL_API BOOL XMLAPI_Parse(const char* pXmlFile,XMLNODEVTR** pNodeVtr,const char* pRoot)
{
	*pNodeVtr=new XMLNODEVTR;
	CXmlParse parse(*pNodeVtr);
	return parse.ParseXml(pXmlFile,pRoot);
}

//解析XML字符串
XMLTOOL_API BOOL XMLAPI_Parse(const char* pXmlFile,int len,XMLNODEVTR** pNodeVtr,const char* pRoot)
{
	*pNodeVtr=new XMLNODEVTR;
	CXmlParse parse(*pNodeVtr);
	return parse.ParseXml(pXmlFile,len,pRoot);
}

//释放名字
XMLTOOL_API void XMLAPI_Release(XMLNODEVTR* pNodeVtr)
{
	CXmlItem::ClearItem();
	CXmlNode::ClearNode();
	if(pNodeVtr!=NULL)
	{
		/*for(XMLITERATOR itr=pNodeVtr->begin();itr!=pNodeVtr->end();++itr)
			delete (*itr);*/
		pNodeVtr->clear();
	}
	delete pNodeVtr;
}
