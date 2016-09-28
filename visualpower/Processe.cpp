// Processe.cpp: implementation of the Processe class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Processe.h"
#include "psapi.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProcesse::CProcesse()
{

}

CProcesse::~CProcesse()
{

}

//查找进程的主窗口
HWND CProcesse::FindProcHwnd(const char* pProcName)
{
	HWNDPID hpid;
	if(FindProcessID(pProcName,hpid.dwID))
	{
		EnumWindows(EnumCurWindowsProc,(LPARAM)&hpid);
		if(hpid.hWnd!=NULL)
			return hpid.hWnd;
	}
	return NULL;
}

//查找进程DI
BOOL CProcesse::FindProcessID(const char* pProcName,DWORD &dwID)
{
	DWORD dwSize;
	DWORD dwPID[1024];
	if(EnumProcesses(dwPID,1024,&dwSize))
	{
		DWORD dwDesired=PROCESS_QUERY_INFORMATION | PROCESS_VM_READ;
		for(DWORD i=0;i<dwSize;i++)
		{
			if(dwPID[i]==0)
				continue;
			
			HANDLE hProc=OpenProcess(dwDesired,FALSE,dwPID[i]);
			if(hProc!=NULL)
			{
				DWORD dwMode=0;
				HMODULE hMod=NULL;
				if(EnumProcessModules(hProc,&hMod,1,&dwMode))
				{
					if(dwMode>0)
					{
						char szModule[128]={0};
						if(GetModuleBaseName(hProc,hMod,szModule,128)>0)
						{
							if(strcmp(szModule,pProcName)==0)
							{
								CloseHandle(hMod);
								dwID=dwPID[i];
								return TRUE;
							}
						}
						CloseHandle(hMod);
					}
				}
				CloseHandle(hProc);
			}
		}
	}
	return FALSE;
}

//运行进程
BOOL CProcesse::RunProcess(const char* pWndName,WORD show)
{
	HWND hWnd=::FindWindow(NULL,pWndName);
	if(hWnd==NULL)
	{
		char szCommand[256]={0};
		if(!GetModuleFileName(NULL,szCommand,256))
			return FALSE;
		
		char* pEnd=strrchr(szCommand,'\\');
		if(pEnd!=NULL)
		{
			pEnd++;
			strcpy(pEnd,pWndName);
			
			PROCESS_INFORMATION li;
			STARTUPINFO  st;
			
			memset(&li,0,sizeof(PROCESS_INFORMATION));
			memset(&st,0,sizeof(STARTUPINFO));
			st.cb=sizeof(STARTUPINFO);
			st.wShowWindow=show;//SW_SHOWMAXIMIZED,SW_SHOWNORMAL;
			st.dwFlags=STARTF_USESHOWWINDOW;
			
			return CreateProcess(NULL,szCommand,NULL,NULL,FALSE,0,NULL,NULL,&st,&li);
		}		
	}
	return FALSE;
}

//枚举窗口处理进程
BOOL CALLBACK EnumCurWindowsProc(HWND hwnd,LPARAM lParam)
{
	HWNDPID* phid=(HWNDPID*)lParam;
	if(hwnd!=NULL)
	{
		HWND phwnd=GetParent(hwnd);
		if(GetWindowLong(hwnd,GWL_STYLE) & WS_VISIBLE)
		{
			DWORD dwID;
			GetWindowThreadProcessId(hwnd,&dwID);
			if(dwID==phid->dwID)//找到，通知枚举结束
			{
				phid->hWnd=hwnd;
				return FALSE;
			}
		}
	}
	return TRUE;
}
