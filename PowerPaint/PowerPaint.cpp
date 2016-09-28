// PowerPaint.cpp : Defines the class behaviors for the application.
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "comobj.h"
#include "gdata.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
extern gdata dbm;
extern comobj cobj;
/////////////////////////////////////////////////////////////////////////////
// CPowerPaintApp

BEGIN_MESSAGE_MAP(CPowerPaintApp, CWinApp)
	//{{AFX_MSG_MAP(CPowerPaintApp)
	ON_COMMAND(ID_APP_ABOUT, OnAppAbout)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CPowerPaintApp construction

CPowerPaintApp::CPowerPaintApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

CPowerPaintApp::~CPowerPaintApp()
{
	FreeResource();
}
/////////////////////////////////////////////////////////////////////////////
// The one and only CPowerPaintApp object

CPowerPaintApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CPowerPaintApp initialization

BOOL CPowerPaintApp::InitInstance()
{
	AfxEnableControlContainer();

	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

#ifdef _AFXDLL
	Enable3dControls();			// Call this when using MFC in a shared DLL
#else
	Enable3dControlsStatic();	// Call this when linking to MFC statically
#endif

	// Change the registry key under which our settings are stored.
	// TODO: You should modify this string to be something appropriate
	// such as the name of your company or organization.
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));
	LoadResource();

	// To create the main window, this code creates a new frame window
	// object and then sets it as the application's main window object.

	CMainFrame* pFrame = new CMainFrame;
	m_pMainWnd = pFrame;

	// create and load the frame with its resources

	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);
	pFrame->SetIcon(LoadIcon(IDR_MAINFRAME),true);
	pFrame->ShowWindow(SW_SHOWMAXIMIZED);
	pFrame->UpdateWindow();

	return TRUE;
}

/////////////////////////////////////////////////////////////////////////////
// CPowerPaintApp message handlers

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


HBRUSH CAboutDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
{
	if (nCtlColor != CTLCOLOR_EDIT && nCtlColor != CTLCOLOR_SCROLLBAR){
   		pDC->SetBkMode(TRANSPARENT);
     	HBRUSH B = CreateSolidBrush(0xffffff);
     	return (HBRUSH)B;
  	}
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	return hbr;
}


// App command to run the dialog
void CPowerPaintApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CPowerPaintApp message handlers

//装入需要的资源
void CPowerPaintApp::LoadResource()
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
	cobj.hcur[11]=LoadCursor(IDC_CURSOR12);
	cobj.hcur[12]=LoadCursor(IDC_CURSOR13);
	cobj.hcur[13]=LoadCursor(IDC_CURSOR14);
	cobj.hcur[14]=LoadCursor(IDC_CURSOR15);
	cobj.hcur[15]=LoadCursor(IDC_CURSOR16);
	cobj.hcur[16]=LoadCursor(IDC_CURSOR17);


}

//程序退出时释放装入的资源
void CPowerPaintApp::FreeResource()
{
	int i;
	for(i=0;i<17;i++) DestroyCursor(cobj.hcur[i]);
	cobj.menu1.DestroyMenu();
}

