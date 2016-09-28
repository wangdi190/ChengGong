#if !defined(AFX_EDITCTL_H)
#define AFX_EDITCTL_H



#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

//CJH 1999年11月设计
#include "lib.h"

class editctl : public CEdit
{
public:
	editctl();
public:

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(editctl)
	//}}AFX_VIRTUAL

// Implementation
public:
	void SetDataLink(char dtype,char *bf,BYTE maxl,WORD recno,BYTE xsd);
	virtual ~editctl();

	// Generated message map functions
protected:
	//{{AFX_MSG(editctl)
	afx_msg void OnChange();
	virtual LRESULT WindowProc(UINT message, WPARAM wParam, LPARAM lParam);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	int IsNorTime(int year,int mon,int day,int hour,int min,int sec);
	void  GetEditString();
	char  type;            //0=float 1=str 2=char 3=short 4=int 5=BYTE 6=WORD 7=DWORD
	char  *addr;           //数据交换缓冲区地址
	BYTE  strmax;          //字符串长度
	char  buf[260];        //缓冲区最大256字节
	WORD  rec;             //数据变化时需要返回的记录号
	BYTE  xs;
};

#endif 