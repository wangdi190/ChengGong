// CMonitorError.h : main header file for the CMONITORERROR DLL
//

#if !defined(AFX_CMONITORERROR_H__B6AC016C_398E_4CA4_A74C_ECE1141EF10B__INCLUDED_)
#define AFX_CMONITORERROR_H__B6AC016C_398E_4CA4_A74C_ECE1141EF10B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/////////////////////////////////////////////////////////////////////////////
// CCMonitorErrorApp
// See CMonitorError.cpp for the implementation of this class
//
void* GetRealRecords(char *table,MEMTABLE** pMem,char *db);
//²éÑ¯¼ÇÂ¼
void* QueryRecord(char* pszTable, char* pszWhere,int &num,char* pszDB);
extern BOOL threadQuit;
class CCMonitorErrorApp : public CWinApp
{
public:
	CCMonitorErrorApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CCMonitorErrorApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CCMonitorErrorApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CMONITORERROR_H__B6AC016C_398E_4CA4_A74C_ECE1141EF10B__INCLUDED_)
