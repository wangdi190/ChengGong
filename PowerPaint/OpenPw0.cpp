// OpenPw0.cpp : implementation file
//

#include "stdafx.h"
#include "Powerpaint.h"
#include "OpenPw0.h"
#include "ptdefine.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


BOOL GetPw0ile(char *filename,char *path,int &pageno,HWND hWndParent)
{
 	 char title[46],filter[64];
	 strcpy(filter,"PowerPaint界面文件(*.pw0)|*.pw0|");
	 OpenPw0  fodlg(true,NULL,NULL,OFN_ENABLEHOOK|OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT|OFN_EXPLORER|OFN_ENABLETEMPLATE,
		 filter,CWnd::FromHandle(hWndParent));
	 strcpy(title,"打开PowerPaint(pw0)界面文件");
	 fodlg.m_ofn.lpstrTitle=title;
	 fodlg.m_ofn.lpstrInitialDir=path;
	 if(fodlg.DoModal()==IDOK){
		strcpy(filename,fodlg.GetPathName()); 
		pageno=fodlg.curpage;
		return true;
	 };
	 return false;
};


//////////////////////////////////////////////////////////////////////////////////////////////
// OpenPw0
IMPLEMENT_DYNAMIC(OpenPw0, CFileDialog)

OpenPw0::OpenPw0(BOOL bOpenFileDialog, LPCTSTR lpszDefExt, LPCTSTR lpszFileName,
		DWORD dwFlags, LPCTSTR lpszFilter, CWnd* pParentWnd) :
		CFileDialog(bOpenFileDialog, lpszDefExt, lpszFileName, dwFlags, lpszFilter, pParentWnd)
{
	m_ofn.hInstance = AfxGetInstanceHandle();
    m_ofn.lpTemplateName = MAKEINTRESOURCE(IDD_OPENPW0); 
	curpage=0;
}



void OpenPw0::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(OpenPw0)
	DDX_Control(pDX, IDC_PAGE, m_page);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(OpenPw0, CFileDialog)
	//{{AFX_MSG_MAP(OpenPw0)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		ON_CBN_SELCHANGE(IDC_PAGE, OnSelchangePage)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


LRESULT OpenPw0::WindowProc(UINT message, WPARAM wParam, LPARAM lParam) 
{
	LPNMHDR pnmh;
	char filename[1024];
	pnmh = (LPNMHDR) lParam;
	if(message==WM_NOTIFY){
		if (pnmh->code == CDN_SELCHANGE){
			::SendMessage(::GetParent(m_hWnd),CDM_GETFILEPATH ,1024,(LPARAM)filename);      
			GetFilePage(filename);
		}
	}
	return CFileDialog::WindowProc(message, wParam, lParam);
}

void OpenPw0::OnSelchangePage() 
{
	curpage=m_page.GetCurSel();
	SetDlgItemInt(IDC_PNO,curpage);
}

void OpenPw0::GetFilePage(char *filename)
{
	int i,m,n;
	N_PWFHEAD *ph,head;
	N_SUBPWF hd;
	char *buf1;
	FILE *fp;
	m_page.ResetContent();
	//打开文件
	fp=fopen(filename,"r+b");
	if(fp==NULL) return;
	fread(&head,sizeof(N_PWFHEAD),1,fp);
	if(head.Version>3203)//!=3200&&head.Version!=3201&&head.Version!=0x3202){ //验证版本
	{
		fclose(fp);
		return;
	};
	n=head.pagesum;
	m=n*sizeof(N_OBJSAVE)+sizeof(N_PWFHEAD);
	buf1=new char[m+100];
	ph=(N_PWFHEAD*)buf1;
	fseek(fp,0,SEEK_SET);
	fread(buf1,m,1,fp);
	for(i=0;i<n;i++)
	{
		fseek(fp,(long)ph->page[i].offset,SEEK_SET);
		fread(&hd,sizeof(N_SUBPWF),1,fp);
		if(hd.flag!=0xcccc)	continue;	//错误的
		m_page.AddString(hd.Name);
	};
	fclose(fp);
	delete buf1;
	m_page.SetCurSel(0);
	curpage=0;
	SetDlgItemInt(IDC_PNO,curpage);
}



