// VisualPower.h : main header file for the VISUALPOWER application
//

#if !defined(AFX_VISUALPOWER_H__B3772E9E_D6D2_419A_8B34_8BE20CC18396__INCLUDED_)
#define AFX_VISUALPOWER_H__B3772E9E_D6D2_419A_8B34_8BE20CC18396__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CVisualPowerApp:
// See VisualPower.cpp for the implementation of this class
//

class CVisualPowerApp : public CWinApp
{
public:
	CVisualPowerApp();
	~CVisualPowerApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CVisualPowerApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CVisualPowerApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CheckVersion();
	void LoadResource();
	void FreeResource();
};

extern bool bShowProcessData;

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_VISUALPOWER_H__B3772E9E_D6D2_419A_8B34_8BE20CC18396__INCLUDED_)
