// SecImport.h: interface for the SecImport.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SECIMPORT_H__3E24519A_DF0D_4490_9C26_19714D45CCC5__INCLUDED_)
#define AFX_SECIMPORT_H__3E24519A_DF0D_4490_9C26_19714D45CCC5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#pragma warning(disable: 4786) 

#include <vector>
#include <string>
using namespace std;

//取得断面名字
int __stdcall GetSectionList(const char* pSecFile,vector<string> &secVtr);
//导入断面信息
int __stdcall ImportSection(const void* pImport,long tStart);
//断面数据映射到库对象(bySect=0:SCADA断面，bySect=1:状态估计断面，bySect=2:评估断面)
int __stdcall MapSectionToObj(const void* pDB,unsigned char bySect);

#endif // !defined(AFX_SECIMPORT_H__3E24519A_DF0D_4490_9C26_19714D45CCC5__INCLUDED_)
