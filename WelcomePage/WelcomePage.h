// WelcomePage.h : main header file for the WELCOMEPAGE DLL
//

#if !defined(AFX_WELCOMEPAGE_H__902C1DB7_B100_4FB2_BF59_CEEB08B11510__INCLUDED_)
#define AFX_WELCOMEPAGE_H__902C1DB7_B100_4FB2_BF59_CEEB08B11510__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CWelcomePageApp
// See WelcomePage.cpp for the implementation of this class
//

void* GetRealRecords(char *table,MEMTABLE** pMem,char *db);
//²éÑ¯¼ÇÂ¼
void* QueryRecord(char* pszTable, char* pszWhere,int &num,char* pszDB);
extern BOOL threadQuit;

class CWelcomePageApp : public CWinApp
{
public:
	CWelcomePageApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CWelcomePageApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CWelcomePageApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_WELCOMEPAGE_H__902C1DB7_B100_4FB2_BF59_CEEB08B11510__INCLUDED_)
