// PowerPaint.h : main header file for the POWERPAINT application
//

#if !defined(AFX_POWERPAINT_H__94BCE0BE_B3A1_4B8F_B09B_AA7FC333584A__INCLUDED_)
#define AFX_POWERPAINT_H__94BCE0BE_B3A1_4B8F_B09B_AA7FC333584A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CPowerPaintApp:
// See PowerPaint.cpp for the implementation of this class
//

class CPowerPaintApp : public CWinApp
{
public:
	CPowerPaintApp();
	~CPowerPaintApp();
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CPowerPaintApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation

public:
	//{{AFX_MSG(CPowerPaintApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void LoadResource();
	void FreeResource();
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_POWERPAINT_H__94BCE0BE_B3A1_4B8F_B09B_AA7FC333584A__INCLUDED_)
