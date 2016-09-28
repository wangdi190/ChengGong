// ChooseCase.h : main header file for the CHOOSECASE DLL
//

#if !defined(AFX_CHOOSECASE_H__6BA7DC7B_F870_4D64_B324_C3236C7D4B60__INCLUDED_)
#define AFX_CHOOSECASE_H__6BA7DC7B_F870_4D64_B324_C3236C7D4B60__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CChooseCaseApp
// See ChooseCase.cpp for the implementation of this class
//
void* GetRealRecords(char *table,MEMTABLE** pMem,char *db);
//²éÑ¯¼ÇÂ¼
void* QueryRecord(char* pszTable, char* pszWhere,int &num,char* pszDB);
BOOL UpdateRecord(char* pszTable, char* pszWhere,void* pRecVal,char* pszDB);

extern BOOL threadQuit;
class CChooseCaseApp : public CWinApp
{
public:
	CChooseCaseApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CChooseCaseApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CChooseCaseApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CHOOSECASE_H__6BA7DC7B_F870_4D64_B324_C3236C7D4B60__INCLUDED_)
