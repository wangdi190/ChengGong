// Processe.h: interface for the Processe class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PROCESSE_H__203D4FF2_1F73_480B_8DD9_9619C4B1B8D3__INCLUDED_)
#define AFX_PROCESSE_H__203D4FF2_1F73_480B_8DD9_9619C4B1B8D3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct HWNDPID    //窗口句柄和它的进程ID
{
	HWNDPID(){memset(this,0,sizeof(HWNDPID));};
	HWND hWnd;
	DWORD dwID;
};

class CProcesse  
{
public:
	//查找进程的主窗口
	static HWND FindProcHwnd(const char* pProcName);
	//运行进程
	static BOOL RunProcess(const char* pWndName,WORD show=SW_SHOWNORMAL);
	//打开进程窗口
	static BOOL FindProcessID(const char* pProcName,DWORD &dwID); 
	
	CProcesse();
	virtual ~CProcesse();
	
};

//枚举窗口处理进程
BOOL CALLBACK EnumCurWindowsProc(HWND hwnd,LPARAM lParam);

#endif // !defined(AFX_PROCESSE_H__203D4FF2_1F73_480B_8DD9_9619C4B1B8D3__INCLUDED_)
