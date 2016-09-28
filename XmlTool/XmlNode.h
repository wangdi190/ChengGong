// XmlNode.h: interface for the CXmlNode class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_XMLNODE_H__2A565BD6_FD16_4E55_839B_0C17ECF59EF5__INCLUDED_)
#define AFX_XMLNODE_H__2A565BD6_FD16_4E55_839B_0C17ECF59EF5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "XmlTool.h"
#include "XmlItem.h"

class CXmlNode : public IXmlNode  
{
public:
	//是否结束标志
	BOOL IsEndFlag(char* pEnd);
	//取属性值
	virtual const char* GetPropValue(const char* pName);
	//按字符串取值
	virtual const char* GetValue();
	//通过标志返回子节点
	virtual IXmlNode* GetSubNodeByFlag(const char* pFlag,std::vector<IXmlNode*>* pSubVtr);
	//通过标志返回子节点值
	virtual const char* GetSubValueByFlag(const char* pFlag);
	//返回首个子节点位置
	virtual int GetFirstSubNode();
	//返回当前子节点和下一个子节点位置
	virtual IXmlNode* GetNextSubNode();
	//返回首个属性位置
	virtual int GetFirstProp();
	//返回当前属性
	virtual int GetNextProp(const char** pName,const char** pValue);
	//是否节点标志
	virtual int IsKindof(const char* pFlag){if(strcmp(pFlag,m_pszFlag)==0) return TRUE;else return FALSE;};
	//返回标志
	virtual const char* GetFlag(){return m_pszFlag;};

	//添加子节点
	BOOL AddSubNode(CXmlNode* pNode);
	//设置节点值
	BOOL SetNodeValue(char* pValue);
	//添加属性项目
	void AddPropItem(CXmlItem* pItem);
	//设置标志
	void SetNodeFlag(char* pFlag);

	//清除名字
	static void ClearNode();
	//分配节点内存
	static CXmlNode* AllocNodeMem(char* pFlag);

	CXmlNode();
	CXmlNode(char* pFlag);
	virtual ~CXmlNode();
protected:
	//通过名字取属性
	CXmlItem* GetPropByName(const char* pName);
	XMLITERATOR m_curitr;
	XMLITEMVTR::iterator m_propitr;

	const char* m_pszFlag;  //节点标志
	char* m_pszValue;  //节点值
	//char m_szValue[XMLVALUE_MAX];  //节点值
	XMLNODEVTR m_SubVtr;//子节点

	XMLITEMVTR m_propVtr;
private:
	static XMLNODEVTR m_MemNodeVtr;//内存节点
	static CMemoryName m_MemNM;
	static CXmlNode* m_pMemNode;
	static int m_memindex;
};

#endif // !defined(AFX_XMLNODE_H__2A565BD6_FD16_4E55_839B_0C17ECF59EF5__INCLUDED_)
