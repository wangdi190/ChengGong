// ChooseCase.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "ChooseCase.h"
#include "MainFrame.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CChooseCaseApp

BEGIN_MESSAGE_MAP(CChooseCaseApp, CWinApp)
	//{{AFX_MSG_MAP(CChooseCaseApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CChooseCaseApp construction

CChooseCaseApp::CChooseCaseApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CChooseCaseApp object

CChooseCaseApp theApp;
BOOL threadQuit;


BOOL CChooseCaseApp::InitInstance() 
{
	// TODO: Add your specialized code here and/or call the base class
	SetDialogBkColor(RGB(241,254,253));
	return CWinApp::InitInstance();
}

//返回版本号F1
int WINAPI DfGetVer()
{
	return 2009;
}

//编辑态显示的图形F2
void WINAPI DfDrawDemo(HDC hdc,RECT rt,DWORD style,char *buf)
{
	CDC dc;
	dc.Attach(hdc);
	dc.DrawEdge(&rt,EDGE_ETCHED,BF_RECT);
	dc.TextOut(rt.right/2, rt.bottom/2, "选择案列程序2015");
	dc.Detach();
}

//初始化F3
void* WINAPI DfInit(HWND hWndParent,HWND &hw,RECT rt,int nID,DWORD style,char *buf)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	CMainFrame* pFram=new CMainFrame();
	if(pFram != NULL)
	{
		if(!pFram->Create(NULL, "", WS_CHILD|WS_BORDER|WS_VISIBLE,rt,
			CWnd::FromHandle(hWndParent), nID))
		{
			return NULL;
		}
		CWnd* pWnd=CWnd::FromHandle(hWndParent);
		CFont* pFont=pWnd->GetFont();
		pFram->SetFont(pFont);
		
		hw=pFram->GetSafeHwnd();
		pFram->ShowWindow(SW_SHOW);
	}
	
	return pFram;
}

//关闭退出F4
void WINAPI DfClose(void *rc)
{
	//	ReleaseAreaStatDB();
	threadQuit = FALSE;
	Sleep(1000);
	CMainFrame* pFram=(CMainFrame*)rc;
	if(pFram!=NULL)
		delete pFram;
	pFram=NULL;
}

//关于F5
void WINAPI DfAbout()
{
	MessageBox(0,"这是一个用于运行方式参数管理自助控件\n遵守自助控件2.01版模型","关于编辑态",MB_OK);
}

//参数配置F6
void WINAPI DfSetParam(DWORD &style,char *buf)
{
	//AFX_MANAGE_STATE(AfxGetStaticModuleState());
}

//装入菜单F7
HMENU WINAPI DfLoadMenu()
{
	return NULL;
}


void* GetRealRecords(char *table,MEMTABLE** pMem,char *db)
{
	DWORD idi;
	if(!LSI_GetTableID(db,table,idi)) return NULL;
	(*pMem)=(MEMTABLE *)LSI_GetTableAdd(LOWORD(idi));
	if((*pMem)==NULL)
	{
		return NULL;
	}
//	recn=(*pMem)->userec;
//	if(recn==0)
//		return NULL;
	
	return (*pMem)->data;
}

//查询记录
void* QueryRecord(char* pszTable, char* pszWhere,int &num,char* pszDB)
{
	if(pszDB==NULL || pszTable==NULL)
		return FALSE;
	
	num=0;
	void* pReturn=NULL;
	if(pszWhere!=NULL)
	{
		//char chSql[256];	
		//sprintf(chSql,"TABLE(%s.%s),WHERE(%s)",pszDB,pszTable,pszWhere);
		
		//TABLE(数据库名.表名)，WHERE(域名=XXX)
		int error;
		char* pRec=(char*)LSI_QueryRecord(pszWhere,num,error,TRUE);
		pReturn=(void*)(pRec+num*2*sizeof(char));
	}
	else
	{
		DWORD idi;
		MEMTABLE *mtb;
		if(!LSI_GetTableID(pszDB,pszTable,idi)) return 0;
		int addr=LOWORD(idi);
		mtb=(MEMTABLE *)LSI_GetTableAdd(addr);
		if(mtb!=NULL)
		{
			num=mtb->userec;
			pReturn=mtb->data;
		}
	}
	return pReturn;
}

//修改记录
BOOL UpdateRecord(char* pszTable, char* pszWhere,void* pRecVal,char* pszDB)
{
	if(pszDB==NULL || pszTable==NULL || pRecVal==NULL)
		return FALSE;
	
	//	char chSql[256];	
	//	sprintf(chSql,"TABLE(%s.%s),WHERE(%s)",pszDB,pszTable,pszWhere);
	
	int recno=LSI_GetFirstRecno(pszWhere);
	if(recno>=0)//修改
	{
		char chUpdate[256];	
		sprintf(chUpdate,"%s.%s",pszDB,pszTable);
		LSI_UpdateARecord(chUpdate, pRecVal, recno);
		//	DWORD dwtid=0;
		//	if(LSI_GetTableIDExt(chUpdate,dwtid))
		//		LSI_SetChanged(dwtid,recno);
		return TRUE;
	}
	return FALSE;
}