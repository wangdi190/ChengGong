// PhraseXml.h: interface for the PhraseXml class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PHRASEXML_H__4AA3D85B_9978_4359_A800_2A45691DBF7E__INCLUDED_)
#define AFX_PHRASEXML_H__4AA3D85B_9978_4359_A800_2A45691DBF7E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include <vector>
using namespace std;

#include <libxml/xmlmemory.h>
#include <libxml/parser.h>
#pragma comment(lib, "libxml2.lib")

struct  ST_CaseInfo
{
	char name[64];
	char description[1024];
};
typedef std::vector<ST_CaseInfo> VecCaseInfo;


class PhraseXml  
{
public:
	PhraseXml();
	virtual ~PhraseXml();
public:
	void GetPropValueToInt(xmlNodePtr cur, char *Prop, int &nValue);
	void GetPropValueToPtr(xmlNodePtr cur, char *Prop, char *pValue);
	void GetContent(xmlNodePtr cur, char *pValue);

	void Init(char *pPathXmlFile);

	VecCaseInfo m_VecCaseInfo;

};

#endif // !defined(AFX_PHRASEXML_H__4AA3D85B_9978_4359_A800_2A45691DBF7E__INCLUDED_)
