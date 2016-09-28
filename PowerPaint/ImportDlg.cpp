// ImportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "PowerPaint.h"
#include "ImportDlg.h"
#include "gdata.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern gdata dbm;
UINT SvgImportThread( LPVOID pParam );

/////////////////////////////////////////////////////////////////////////////
// CImportDlg dialog


CImportDlg::CImportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CImportDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CImportDlg)
	m_strScr = _T("");
	m_strDir = _T("");
	m_bCheckAll = TRUE;
	//}}AFX_DATA_INIT
}


void CImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CImportDlg)
	DDX_Control(pDX, IDC_LIST_SVG, m_lsCtrl);
	DDX_Text(pDX, IDC_SRCPATH, m_strScr);
	DDX_Text(pDX, IDC_DIRPATH, m_strDir);
	DDX_Check(pDX, IDC_CHECK_ALL, m_bCheckAll);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CImportDlg, CDialog)
	//{{AFX_MSG_MAP(CImportDlg)
	ON_BN_CLICKED(IDC_CHECK_ALL, OnCheckAll)
	ON_BN_CLICKED(IDC_BTNSCR, OnBtnscr)
	ON_BN_CLICKED(IDC_BTNDIR, OnBtndir)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SVG, OnClickListSvg)
	ON_EN_CHANGE(IDC_SRCPATH, OnChangeSrcpath)
	ON_EN_CHANGE(IDC_DIRPATH, OnChangeDirpath)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CImportDlg message handlers

BOOL CImportDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	CWnd* pWnd=GetDlgItem(IDC_CHECK_ALL);
	pWnd->EnableWindow(FALSE);

	m_lsCtrl.SetExtendedStyle(LVS_EX_CHECKBOXES|LVS_EX_FULLROWSELECT|LVS_SINGLESEL/*|LVS_EX_GRIDLINES*/);

	CRect rt;
	m_lsCtrl.GetClientRect(&rt);
	m_lsCtrl.InsertColumn(0,"文件名",LVCFMT_LEFT,(int)(rt.Width()*0.6));
	m_lsCtrl.InsertColumn(1,"状  态",LVCFMT_LEFT,(int)(rt.Width()*0.35));

	char szPath[255];
	if(GetModuleFileName(NULL,szPath,255)>0)
	{
		char* pSplit=strrchr(szPath,'\\');
		if(pSplit!=NULL)
		{
			pSplit++;
			strcpy(pSplit,"hmifile\\");
			m_strDir=szPath;
			UpdateData(FALSE);
		}
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CImportDlg::OnOK() 
{
	AfxBeginThread(SvgImportThread,this);
}

void CImportDlg::OnCheckAll() 
{
	UpdateData();

	int index=m_lsCtrl.GetNextItem(-1,LVNI_ALL);
	while(index>=0)
	{
		if(m_bCheckAll)
			m_lsCtrl.SetCheck(index);
		else
			m_lsCtrl.SetCheck(index,FALSE);
		m_lsCtrl.SetItemText(index,1,"○");				
		index=m_lsCtrl.GetNextItem(index,LVNI_ALL);
	}	
}

void CImportDlg::OnBtnscr() 
{
	if(OpenDir(this, m_strScr, "", "选择SVG源文件夹"))
	{
		if(m_strScr[m_strScr.GetLength()-1]!='\\')
			m_strScr+="\\";

		if(LoadDirSvg("*.svg"))
		{
			CWnd* pWnd=GetDlgItem(IDC_CHECK_ALL);
			pWnd->EnableWindow();
		}
		UpdateData(FALSE);
	}
}

void CImportDlg::OnBtndir() 
{
	char szPath[255]={0};
	if(GetModuleFileName(NULL,szPath,255)>0)
	{
		char* pSplit=strrchr(szPath,'\\');
		if(pSplit!=NULL)
		{
			pSplit++;
			*pSplit=0;
			strcpy(pSplit,"hmifile\\");
			if(OpenDir(this, m_strDir,"", "选择转换保存文件夹"))
			{
				if(m_strDir[m_strDir.GetLength()-1]!='\\')
					m_strDir+="\\";
				UpdateData(FALSE);
			}
		}
	}
}

BOOL OpenDir(CWnd* parent, CString& strPath,char * strRootFolder,LPCTSTR cDlgName)
{
	char   path[MAX_PATH];   
	BROWSEINFO    bi;   
	if(strRootFolder==NULL)   
		bi.pidlRoot=NULL;   
	else
	{   
		LPITEMIDLIST     pIdl    =    NULL;   
		IShellFolder*    pDesktopFolder;   
		char             szPath[MAX_PATH];   
		OLECHAR          olePath[MAX_PATH];   
		ULONG            chEaten;   
		ULONG            dwAttributes;   
		strcpy(szPath, (LPCTSTR)strRootFolder);   
		if(SUCCEEDED(SHGetDesktopFolder(&pDesktopFolder)))   
		{   
			MultiByteToWideChar(CP_ACP,    MB_PRECOMPOSED,    szPath,    -1,    olePath,    MAX_PATH);   
			pDesktopFolder->ParseDisplayName(NULL,    NULL,    olePath,    &chEaten,    &pIdl,    &dwAttributes);   
			pDesktopFolder->Release();   
		}   
		bi.pidlRoot=pIdl;   
	} 
	bi.hwndOwner=parent->GetSafeHwnd();     
	bi.pszDisplayName=path;   
	bi.lpszTitle=cDlgName;   
	bi.ulFlags=0;   
	bi.lpfn=NULL;   
	bi.lParam=NULL;   
	bi.iImage=NULL;   
	path[0]='\0';   
	if(SHGetPathFromIDList(SHBrowseForFolder(&bi),path))
	{
		strPath.Format("%s",path);
		return true;
	}
	else
		return false;
}


BOOL CImportDlg::LoadDirSvg(char *pExt)
{
	m_lsCtrl.DeleteAllItems();
	CString strPath=m_strScr+pExt;

	CFileFind fFind;
	CString strName;
	if(fFind.FindFile(strPath))
	{
		int index;
		while(fFind.FindNextFile())
		{
			strName=fFind.GetFileName();
			if(!strName.IsEmpty())
			{
				index=m_lsCtrl.InsertItem(0,(LPCSTR)strName);
				m_lsCtrl.SetItemText(index,1,"○");				

				if(m_bCheckAll)
					m_lsCtrl.SetCheck(index);
				else
					m_lsCtrl.SetCheck(index,FALSE);
			}
		}
	}
	return TRUE;
}

void CImportDlg::OnClickListSvg(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_LISTVIEW* pNMListView = (NM_LISTVIEW*)pNMHDR;
	
	if(pNMListView->iItem >=0)
	{
		m_lsCtrl.SetItemText(pNMListView->iItem,1,"○");				
	}	
	
	*pResult = 0;
}

void CImportDlg::OnChangeSrcpath() 
{
	UpdateData();
	if(m_strScr[m_strScr.GetLength()-1]!='\\')
		m_strScr+="\\";

	if(LoadDirSvg("*.svg"))
	{
		CWnd* pWnd=GetDlgItem(IDC_CHECK_ALL);
		pWnd->EnableWindow();
	}
}

void CImportDlg::OnChangeDirpath() 
{
	UpdateData();
	if(m_strDir[m_strDir.GetLength()-1]!='\\')
		m_strDir+="\\";
}

UINT SvgImportThread( LPVOID pParam )
{
	CImportDlg* pImport=(CImportDlg*)pParam;
	CWnd* pOK=pImport->GetDlgItem(IDOK);
	pOK->EnableWindow(FALSE);
	CWnd* pCancel=pImport->GetDlgItem(IDCANCEL);
	pCancel->EnableWindow(FALSE);

	CString strLoad,strSave;
	int index=pImport->m_lsCtrl.GetNextItem(-1,LVNI_ALL);
	while(index>=0)
	{
		if(pImport->m_lsCtrl.GetCheck(index))//被选中
		{	
			strLoad=strSave=pImport->m_lsCtrl.GetItemText(index,0);
			strLoad=pImport->m_strScr+strLoad;
			strSave=pImport->m_strDir+strSave;
			strSave.Replace(".svg",".pw0");

			pImport->m_lsCtrl.SetItemText(index,1,"...");
			if(dbm.LoadSvgAndSave((LPCSTR)strLoad,(LPCSTR)strSave))
				pImport->m_lsCtrl.SetItemText(index,1,"√");
			else
				pImport->m_lsCtrl.SetItemText(index,1,"×");
			Sleep(1);
		}
		index=pImport->m_lsCtrl.GetNextItem(index,LVNI_ALL);
	}	
	pOK->EnableWindow();
	pCancel->EnableWindow();
	return 0;
}

