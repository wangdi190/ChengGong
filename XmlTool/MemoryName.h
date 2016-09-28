// MemoryName.h: interface for the CMemoryName class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MEMORYNAME_H__1B04A952_8BFD_4D23_96DA_AF23405A5C05__INCLUDED_)
#define AFX_MEMORYNAME_H__1B04A952_8BFD_4D23_96DA_AF23405A5C05__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//using namespace std;
#include <vector>
#include <string>

typedef std::vector<std::string>  STRVTR;//字串向量

class CMemoryName  
{
public:
	//清除名字数组
	void ResetName(){m_strVtr.clear();};
	//反回名字指针
	const char* GetNamePointer(char* pName);

	CMemoryName();
	virtual ~CMemoryName();
private:
	//字符串向量
	STRVTR m_strVtr;
	//按名字比较
	static BOOL CompareByName(char* pOne,char* pTwo);

	const char* BinarySearch(char* pName);
};
 
#endif // !defined(AFX_MEMORYNAME_H__1B04A952_8BFD_4D23_96DA_AF23405A5C05__INCLUDED_)
