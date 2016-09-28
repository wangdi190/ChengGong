// FindIDTODevInfo.h : main header file for the FINDIDTODEVINFO DLL
//

#if !defined(AFX_FINDIDTODEVINFO_H__3E1B16BD_2AEA_4FCD_8145_FE47E711CD3C__INCLUDED_)
#define AFX_FINDIDTODEVINFO_H__3E1B16BD_2AEA_4FCD_8145_FE47E711CD3C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols
#include "BinarySearch.h"

/////////////////////////////////////////////////////////////////////////////
// CFindIDTODevInfoApp
// See FindIDTODevInfo.cpp for the implementation of this class
//

class CFindIDTODevInfoApp : public CWinApp
{
public:
	void* SearchByID(char* pid,int &type);
	CFindIDTODevInfoApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CFindIDTODevInfoApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CFindIDTODevInfoApp)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	bool IniSearch();

	CBinarySearch m_MeasSearch;
	CBinarySearch m_RelSearch;

	common_UnEquMeas* m_pUnEquMeas;
	common_Relation* m_pRelation;
	int m_UnEquMeas;
	int m_Relations;	
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_FINDIDTODEVINFO_H__3E1B16BD_2AEA_4FCD_8145_FE47E711CD3C__INCLUDED_)
