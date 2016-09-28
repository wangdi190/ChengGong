// PhraseXml.cpp: implementation of the PhraseXml class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "ChooseCase.h"
#include "PhraseXml.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

PhraseXml::PhraseXml()
{

}

PhraseXml::~PhraseXml()
{

}

std::wstring UT2WC(const char* buf)
{
	int len = MultiByteToWideChar(CP_UTF8, 0, buf, -1, NULL, 0);
	std::vector<wchar_t> unicode(len);
	MultiByteToWideChar(CP_UTF8, 0, buf, -1, &unicode[0], len);
	
	return std::wstring(&unicode[0]);
}

std::string WC2MB(const wchar_t* buf)
{
	int len = WideCharToMultiByte(CP_ACP, 0, buf, -1, NULL, 0, NULL, NULL);
	std::vector<char> utf8(len);
	WideCharToMultiByte(CP_ACP, 0, buf, -1, &utf8[0], len, NULL, NULL);
	
	return std::string(&utf8[0]);
}

std::string str;
const char* UT2MB(char* buf)
{
	if (buf == NULL)
		return NULL;
	
	std::wstring wstr = UT2WC(buf);
	if (wstr.c_str() == NULL)
		return NULL;
	
	str = WC2MB(wstr.c_str());
	if (str.c_str() == NULL)
		return NULL;
	else
		return str.data();
}

void PhraseXml::GetPropValueToInt(xmlNodePtr cur, char *Prop, int &nValue)
{
	xmlChar *value;
	value = xmlGetProp(cur, (const xmlChar*) Prop);
	nValue = atoi((char*)value);
	xmlFree(value);
}

void PhraseXml::GetPropValueToPtr(xmlNodePtr cur, char *Prop, char *pValue)
{
	xmlChar *value;
	value = xmlGetProp(cur, (const xmlChar*) Prop);
	strcpy(pValue, (char*)value);
	xmlFree(value);
}

void PhraseXml::GetContent(xmlNodePtr cur, char *pValue)
{
	xmlChar *value;
	value = xmlNodeGetContent(cur);
	strcpy(pValue, (char*)value);
	xmlFree(value);
}

void PhraseXml::Init(char *pPathXmlFile)
{
	xmlDocPtr doc;  //
	xmlNodePtr cur;  //
	
	doc = xmlParseFile(pPathXmlFile);
	if (doc == NULL )
	{
		fprintf(stderr,"xmlParseFile return is null.\n");
		return ;
	}
	
	cur = xmlDocGetRootElement(doc);
	if (cur == NULL)
	{
		fprintf(stderr,"xmlDocGetRootElement is null.\n");
		xmlFreeDoc(doc);
		return ;
	}

	ST_CaseInfo caseinfo;
	m_VecCaseInfo.clear();

	cur = cur->xmlChildrenNode;
	while (cur != NULL)
	{
		memset(&caseinfo, 0, sizeof(ST_CaseInfo));

		GetPropValueToPtr(cur, "Name", caseinfo.name);
		GetContent(cur, caseinfo.description);

		CString str;
		str.Format("%s\n%s", caseinfo.name, caseinfo.description);
		AfxMessageBox(str);

		m_VecCaseInfo.push_back(caseinfo);
		cur = cur->next;
	}
	xmlFreeDoc(doc);
}