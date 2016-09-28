// VisualPower.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "VisualPower.h"
#include "comobj.h"
#include "logindlg.h"
#include "MainFrm.h"
#include "middll.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
comobj  cobj;		//公共对象
CMainFrame* pFrame;
/////////////////////////////////////////////////////////////////////////////
// CVisualPowerApp

BEGIN_MESSAGE_MAP(CVisualPowerApp, CWinApp)
	//{{AFX_MSG_MAP(CVisualPowerApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CVisualPowerApp construction

CVisualPowerApp::CVisualPowerApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}


CVisualPowerApp::~CVisualPowerApp()
{
	FreeResource();
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CVisualPowerApp object

CVisualPowerApp theApp;
bool bShowProcessData;
/////////////////////////////////////////////////////////////////////////////
// CVisualPowerApp initialization

BOOL CVisualPowerApp::InitInstance()
{
	bShowProcessData = false;
	AfxEnableControlContainer();
#ifdef _AFXDLL
	Enable3dControls();		
#else
	Enable3dControlsStatic();
#endif
	AfxEnableControlContainer();
	LoginDlg log;
	if(log.DoModal()!=IDOK)	return false;
	CheckVersion();
	cobj.ReadIni_File();  //读入初始化文件
	cobj.LoadBusRalate(); //读入母线关联关系
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	pFrame = new CMainFrame;
	m_pMainWnd = pFrame;
	//装入资源
	LoadResource();
	//调入主页
	pFrame->LoadFrame(IDR_MAINFRAME,WS_OVERLAPPEDWINDOW|FWS_ADDTOTITLE,NULL,NULL);
	pFrame->SetIcon(LoadIcon(IDR_MAINFRAME),true);
	pFrame->SetMenu(&cobj.menu);
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();
	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CVisualPowerApp message handlers





/////////////////////////////////////////////////////////////////////////////
// CAboutDlg dialog used for App About

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
		// No message handlers
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAboutDlg)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
	ON_WM_CTLCOLOR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

// App command to run the dialog
void CVisualPowerApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_SCROLLBAR) {
   		pDC->SetBkMode(TRANSPARENT);
     	HBRUSH B = CreateSolidBrush(0xffffff); 
     	return (HBRUSH)B;
  	} 
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}

/////////////////////////////////////////////////////////////////////////////
// CVisualPowerApp message handlers
void CVisualPowerApp::LoadResource()
{
	cobj.hcur[0]=LoadCursor(IDC_CURSOR1);
	cobj.hcur[1]=LoadCursor(IDC_CURSOR2);
	cobj.hcur[2]=LoadCursor(IDC_CURSOR3);
	cobj.hcur[3]=LoadCursor(IDC_CURSOR4);
	cobj.hcur[4]=LoadCursor(IDC_CURSOR5);
	cobj.hcur[5]=LoadCursor(IDC_CURSOR6);
	cobj.hcur[6]=LoadCursor(IDC_CURSOR7);
	cobj.hcur[7]=LoadCursor(IDC_CURSOR8);
	cobj.hcur[8]=LoadCursor(IDC_CURSOR9);
	cobj.hcur[9]=LoadCursor(IDC_CURSOR10);
	cobj.hcur[10]=LoadCursor(IDC_CURSOR11);
	cobj.pmenu.LoadMenu(IDR_RMENU);
	cobj.dmenu.LoadMenu(IDR_DGXMENU);
	cobj.fwmenu.LoadMenu(IDR_FLOWMENU);
	cobj.platemenu.LoadMenu(IDR_PLATEMENU);
	cobj.amenu.LoadMenu(IDR_AMENU);
	cobj.tmenu.LoadMenu(IDR_TABLEMENU);
	//装入资源
	cobj.LoadImg();


	//装载告警图形
	CBitmap bmp;
	CBitmap *bm;
	CDC mdc;
	bmp.LoadBitmap(IDB_BITMAP5);
	mdc.CreateCompatibleDC(0);
	bm=mdc.SelectObject(&bmp);
	cobj.amdc.Create(36,18);
	BitBlt(cobj.amdc.m_hDC,0,0,36,18,mdc.m_hDC,0,0,SRCCOPY);
	mdc.SelectObject(bm);
	mdc.DeleteDC();
	bmp.DeleteObject();
}

void CVisualPowerApp::FreeResource()
{
	int i;
	for(i=0;i<11;i++) if(cobj.hcur[i]!=NULL) DestroyCursor(cobj.hcur[i]);
	cobj.pmenu.DestroyMenu();
	cobj.rmenu.DestroyMenu();
	cobj.menu.DestroyMenu();
	cobj.dmenu.DestroyMenu();
	cobj.fwmenu.DestroyMenu();
	cobj.platemenu.DestroyMenu();
	cobj.amenu.DestroyMenu();
	cobj.tmenu.DestroyMenu();
}


//验证盗版(或被二进制修改)
//使用方法：在资源文件中修改串AFX_IDS_IDLEMESSAGE的字符串，指定用户单位名及版权进告
//编译后用下面的对话框重新显示a和b的值，将值填入比较判断，屏蔽对话框，重新编译即可
void CVisualPowerApp::CheckVersion()
{
	char a,b;
	int i,n;
	char p[256];
	CString str;
	str.LoadString(AFX_IDS_IDLEMESSAGE);
	strcpy(p,str);
	a=0;b=0;
	n=strlen(p);
	for(i=0;i<n;i++)
	{
		a+=p[i];
		b^=p[i];
	}
	if(a!=-98||b!=46)
	{
		cobj.daoban=1;
		MessageBox(0,"该软件为二进制修改的盗版软件!\n请使用正版软件!\n盗版软件将丧失部分功能或出现不正常的死机！","盗版提示",MB_ICONSTOP);
	}else cobj.daoban=0;	
	/*sprintf(p,"a=%d  b=%d",a,b);
	MessageBox(0,p,"as",MB_OK);*/
}

