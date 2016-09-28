// StrField.h: interface for the StrField class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_STRFIELD_H__0013C460_34FD_4B67_BF6C_5EA63AE5A716__INCLUDED_)
#define AFX_STRFIELD_H__0013C460_34FD_4B67_BF6C_5EA63AE5A716__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class StrField  
{
public:
	int SetNewStr(char *str);
	StrField();
	virtual ~StrField();
	char *lpt[256];
	int fldsum;
};

#endif // !defined(AFX_STRFIELD_H__0013C460_34FD_4B67_BF6C_5EA63AE5A716__INCLUDED_)
