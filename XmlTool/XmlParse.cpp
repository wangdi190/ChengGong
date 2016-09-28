// XmlParse.cpp: implementation of the CXmlParse class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "XmlParse.h"

const int BRACKET_EOF=-1;	//未找到尖括号结尾
const int BRACKET_BRACKET=1;   //尖括号结尾>
const int BRACKET_BACKLASH=2;  //反斜线尖括号结尾/>
const int BACKLASH_BRACKET=3;  //反斜线...尖括号结尾/...>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CXmlParse::CXmlParse(XMLNODEVTR* pNodeVtr)
{
	m_pNodeVtr=pNodeVtr;
	m_pSrc=NULL;
	m_pCur=NULL;
	m_iSrcLen=0;
	m_pf=NULL;
}

CXmlParse::~CXmlParse()
{

}

//解析XML字符串
BOOL CXmlParse::ParseXml(const char* pXmlStr,int len,const char* pRoot)
{
	m_pSrc=pXmlStr;
	m_pCur=(char*)m_pSrc;
	m_iSrcLen=len;

	return MainParse(pRoot);
}

BOOL CXmlParse::ParseXml(const char* pXmlFile,const char* pRoot)
{
	m_pf=fopen(pXmlFile,"r");
	if(m_pf==NULL)
		return FALSE;

	BOOL bResult=FALSE;
	bResult=MainParse(pRoot);
	fclose(m_pf);

	return bResult;
}

int CXmlParse::GetChar()
{
	if(m_pf!=NULL && m_pSrc==NULL)
	{
		return fgetc(m_pf);
	}
	else if(m_pf==NULL && m_pSrc!=NULL && m_iSrcLen>0)
	{
		if(m_pCur-m_pSrc<m_iSrcLen)
		{
			char cRet=*m_pCur;
			m_pCur++;
			return cRet;
		}
	}
	return EOF;
}

BOOL CXmlParse::MainParse(const char* pRoot)
{
	if(m_pNodeVtr==NULL)
		return FALSE;

	int c;
	int end;
	CXmlNode* pCurNode=NULL;
	while((c=GetChar())!=EOF)
	{
		if(c=='<')
		{
			pCurNode=GotoBracket(end);
			if(pCurNode!=NULL)
			{
				if(pRoot!=NULL)
				{
					if(pCurNode->IsKindof(pRoot))
					{
						m_pNodeVtr->push_back(pCurNode);
						return NodeParse(pCurNode);
					}
				}
				else
				{
					m_pNodeVtr->push_back(pCurNode);
					if(end==BRACKET_BRACKET)
						NodeParse(pCurNode);
				}
			}
		}
	}
	return TRUE;
}

int CXmlParse::GotoChar(const char end,char *pStr, int max)
{
	if(pStr==NULL || max==0)
		return 0;

	int ret=0;
	int c;
	while((c=GetChar())!=EOF)
	{
		if(ret==0 && (c==' '||c==10))//去掉前面的空格、换行
			continue;
		if(c==end)
		{
			if(ret<max-1)
				pStr[ret]=0;//添加字串结尾
			else
				pStr[max-1]=0;//留一位置添加添加字串结尾
			break;
		}
		else if(ret<max)
		{
			pStr[ret++]=c;
		}
	}
	if(c!=end)
		ret=0;
	return ret;
}

//取到到反括弧，end的意义：-1=EOF,1=找到>,2=找到/>
CXmlNode* CXmlParse::GotoBracket(int &end)
{
	int i=0;
	int c;
	CXmlNode* pNode=NULL;
	CXmlItem* pItem=NULL;
	while((c=GetChar())!=EOF)
	{
		if(i==0 && (c==' '||c=='\n'))//去掉前面的空格、换行
			continue;

		if(c=='>')
		{
			end=BRACKET_BRACKET;
			if(i>1 && m_Buffer[0]=='/')//......</XXXX>
				end=BACKLASH_BRACKET;
			else if(i>0 && m_Buffer[i-1]=='/')//.....<XXXX/>
			{
				m_Buffer[i-1]=0;
				end=BRACKET_BACKLASH;
			}
			else if(i>0 && (m_Buffer[i-1]=='?' || m_Buffer[i-1]==']'))//.....<?xml ...?><![CDATA[...]>
			{
				if(pNode!=NULL && (pNode->IsKindof("?xml")||pNode->IsKindof("![CDATA")))
					end=BRACKET_BACKLASH;
			}

			if(i<BRACKET_MAXLEN-1)
				m_Buffer[i]=0;//添加字串结尾
			else
				m_Buffer[BRACKET_MAXLEN-1]=0;//添加字串结尾
			break;
		}
		else
		{
			if(i<BRACKET_MAXLEN-1)//留一位置添加添加字串结尾
			{
				switch(c)
				{
				case ' ':
					{
						if(pNode==NULL && i>0)
						{
							if(m_Buffer[0]!='/')
							{
								m_Buffer[i]=0;
								//pNode=new CXmlNode(m_Buffer);
								pNode=CXmlNode::AllocNodeMem(m_Buffer);
								i=0;
							}
						}
						else
							m_Buffer[i++]=(char)c;
					}
					break;
				case '"':
					{
						if(pNode!=NULL && i>1 && m_Buffer[i-1]=='=')//找到" =" "
						{
							m_Buffer[i-1]=0;
							char* pItemNM=m_Buffer;
							char* pItemVal=&m_Buffer[i];
							if(GotoChar('"',&m_Buffer[i], BRACKET_MAXLEN-i)>0)
							{
								//pItem=new CXmlItem(pItemNM,pItemVal);
								pItem=CXmlItem::AllocItemMem(pItemNM,pItemVal);
								pNode->AddPropItem(pItem);
							}
							i=0;
						}
					}
					break;
				case '[':
					{
						if(pNode==NULL && i>=7 && strncmp(&m_Buffer[i-7],"![CDATA",7)==0)//<![CDATA[...]]>
						{
							m_Buffer[i]=0;
							//pNode=new CXmlNode(m_Buffer);
							pNode=CXmlNode::AllocNodeMem(m_Buffer);
							i=0;
							if(GotoChar(']',m_Buffer, BRACKET_MAXLEN)>0)
								pNode->SetNodeValue(m_Buffer);
							i=0;
						}
						else
							m_Buffer[i++]=(char)c;
					}
					break;
				default:
					m_Buffer[i++]=(char)c;
				}
			}
		}
	}
	if(c==EOF && end==0)
		end=BRACKET_EOF;

	if(i>0 && pNode==NULL && c!=EOF && BACKLASH_BRACKET!=end)
	{
		m_Buffer[i]=0;
		//pNode=new CXmlNode(m_Buffer);
		pNode=CXmlNode::AllocNodeMem(m_Buffer);
	}
	return pNode;
}

BOOL CXmlParse::NodeParse(CXmlNode *pNodeParent)
{
	int c;
	int end,i=0;
	CXmlNode* pCurNode=NULL;
	while((c=GetChar())!=EOF)
	{
		if(i==0 && (c==' '||c==10))//去掉前面的空格
			continue;

		if(c=='<')
		{
			if(i>0 && pCurNode==NULL)
			{
				m_Buffer[i]=0;
				pNodeParent->SetNodeValue(m_Buffer);
				i=0;
			}

			pCurNode=GotoBracket(end);
			if(pCurNode==NULL)
			{
				if(end==BACKLASH_BRACKET && pNodeParent->IsEndFlag(m_Buffer))
					return TRUE;
			}
			else
			{
				pNodeParent->AddSubNode(pCurNode);
				if(end==BRACKET_BRACKET)
				{
					if(!NodeParse(pCurNode))
						return FALSE;
				}
			}
		}
		else if(i<BRACKET_MAXLEN)
			m_Buffer[i++]=(char)c;

	}
	return TRUE;
}
