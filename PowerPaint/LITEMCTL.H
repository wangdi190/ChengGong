#if !defined(AFX_LITEMCTL_H__)
#define AFX_LITEMCTL_H__

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// litemctl.h : header file
//
#include "lib.h"
/////////////////////////////////////////////////////////////////////////////
// litemctl window

class litemctl : public CComboBox
{
// Construction
public:
	litemctl();

// Attributes
public:

// Operations
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(litemctl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetDataLink(BYTE type1,char *buff,WORD recno);
	virtual ~litemctl();

	// Generated message map functions
protected:
	//{{AFX_MSG(litemctl)
	afx_msg void OnSelchange();
	LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam) ;
	//}}AFX_MSG
	int GetEditValue();
	DECLARE_MESSAGE_MAP()
	char  type;            //0=float 1=str 2=char 3=short 4=int 5=BYTE 6=WORD 7=DWORD
	char  *addr;           //数据交换缓冲区地址
	WORD  rec;
};

#endif 