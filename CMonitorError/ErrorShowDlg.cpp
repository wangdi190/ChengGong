// ErrorShowDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CMonitorError.h"
#include "ErrorShowDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CErrorShowDlg dialog


CErrorShowDlg::CErrorShowDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CErrorShowDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CErrorShowDlg)
	m_szinfo = _T("");
	//}}AFX_DATA_INIT
	m_NU = 0;
}


void CErrorShowDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CErrorShowDlg)
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Text(pDX, IDC_STATIC_TIP, m_szinfo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CErrorShowDlg, CDialog)
	//{{AFX_MSG_MAP(CErrorShowDlg)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CErrorShowDlg message handlers

DWORD WINAPI _RefreshThread(LPVOID lp);

BOOL CErrorShowDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB|LVS_EX_TWOCLICKACTIVATE);
	m_list.InsertColumn(0, "程序名称", LVCFMT_CENTER, 320);

	//加载信息
	int recn;
	common_InterfaceAppSt* pRecord=(common_InterfaceAppSt*)QueryRecord("InterfaceAppSt",NULL,recn,"common");
	if(pRecord!=NULL && recn>0)
	{
		for (int n=0; n<recn; n++)
		{
			m_list.InsertItem(n, pRecord[n].Name);
			m_list.SetItemData(n, pRecord[n].ID);
		}
	}

	threadQuit = TRUE;
	HANDLE hThread = CreateThread(NULL, 0, _RefreshThread,this , 0, NULL);
	CloseHandle(hThread);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

DWORD WINAPI _RefreshThread(LPVOID lp)
{
	CErrorShowDlg *pDlg = (CErrorShowDlg*)lp;
	CString str;
	while(threadQuit)
	{
		//加载信息
		char chWhere[10];
		sprintf(chWhere,"ID=%d",pDlg->m_NU);
		int recn;
		common_InterfaceAppSt* pRecord=(common_InterfaceAppSt*)QueryRecord("InterfaceAppSt",chWhere,recn,"common");
		if(pRecord!=NULL && recn>0)
		{
			if (recn == 1)
			{
				str.Format("用途：%s\n\n最后更新时间：%s\n\n情况：%s", 
					pRecord->NameExe, pRecord->AppRunTime.Format("%Y-%m-%d %H:%M:%S"), pRecord->AppInfomation);
				SetDlgItemText(pDlg->m_hWnd, IDC_STATIC_TIP, str);
			}
		}
		Sleep(1000);
	}
	return 0;
}

void CErrorShowDlg::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMLISTVIEW lp = (LPNMLISTVIEW)pNMHDR;
	
	*pResult = 0;
	
	if(lp->iItem==-1)
		return;
	
	DWORD nu = m_list.GetItemData(lp->iItem);
	if(nu<=0)
		return;

	m_NU = nu;
	*pResult = 0;
}
