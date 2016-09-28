// aseDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChooseCase.h"
#include "aseDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CaseDlg dialog

#include "FirstDlg.h"
FirstDlg *pMainDlg;


CaseDlg::CaseDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CaseDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CaseDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	pMainDlg = (FirstDlg*)pParent;
	//pParent->m_s
}


void CaseDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CaseDlg)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CaseDlg, CDialog)
	//{{AFX_MSG_MAP(CaseDlg)
	ON_BN_CLICKED(IDC_BTN_SAVE, OnBtnSave)
	ON_BN_CLICKED(IDC_BTN_QUIT, OnBtnQuit)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CaseDlg message handlers

void CaseDlg::InitData(CString szName, CString szDescription)
{
	SetDlgItemText(IDC_EDIT_NAME, szName);
	SetDlgItemText(IDC_EDIT_DESCRIPTION, szDescription);
}

BOOL CaseDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	
	CString szTitle;

	if(pMainDlg->m_bAdd == false)
	{
		SetDlgItemText(IDC_EDIT_NAME, pMainDlg->m_szSelectedName);
		SetDlgItemText(IDC_EDIT_DESCRIPTION, pMainDlg->m_szSelectedDescription);

		SetDlgItemText(IDC_BTN_SAVE, "修改");

		szTitle.Format("编辑案列 “%s”", pMainDlg->m_szSelectedName);
		SetWindowText(szTitle);
	}
	else
	{
		SetDlgItemText(IDC_BTN_SAVE,"添加");
		szTitle.Format("添加案列");
		SetWindowText(szTitle);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

#include <io.h>

void CaseDlg::OnBtnSave() 
{
	// TODO: Add your control notification handler code here
	

	if (pMainDlg->m_bAdd == false)  //
	{
		CString strName;
		GetDlgItemText(IDC_EDIT_NAME, strName);
		GetDlgItemText(IDC_EDIT_DESCRIPTION, pMainDlg->m_szSelectedDescription);
		
		if (pMainDlg->m_szSelectedName != strName)
		{
			if(rename(m_szPath+"case\\"+pMainDlg->m_szSelectedName, m_szPath+"case\\"+strName) != 0)
			{
				AfxMessageBox("修改失败！！！修改文件夹失败");
				return;
			}
		}

		CFile file;
		CString szDesPath;
		szDesPath.Format("%scase\\%s\\description.txt",m_szPath, strName);
		BOOL bRet = file.Open(szDesPath, CFile::modeReadWrite|CFile::modeCreate);
		if (bRet == FALSE)
		{
			AfxMessageBox("修改失败!!!\n打开"+strName+"\\description.txt文件失败");
			return;
		}
		file.Write(pMainDlg->m_szSelectedDescription, pMainDlg->m_szSelectedDescription.GetLength());
		file.Close();
		AfxMessageBox("修改成功！！！");
		OnOK();
	}
	else
	{
		GetDlgItemText(IDC_EDIT_NAME, pMainDlg->m_szSelectedName);
		GetDlgItemText(IDC_EDIT_DESCRIPTION, pMainDlg->m_szSelectedDescription);
		CFileFind find;
		BOOL bRet = find.FindFile(m_szPath+"case\\"+pMainDlg->m_szSelectedName);
		if(bRet)
		{
			AfxMessageBox("新增失败！！！\n已经存在名为\""+pMainDlg->m_szSelectedName+"\"的案列");
			return;
		}
		
		bRet = CreateDirectory(m_szPath+"case\\"+pMainDlg->m_szSelectedName, NULL);
		if(!bRet)
		{
			AfxMessageBox("新增失败！！！\n创建案列文件夹失败");
			return;
		}
		
		CFile file;
		file.Open(m_szPath+"case\\"+pMainDlg->m_szSelectedName+"\\description.txt", CFile::modeCreate | CFile::modeWrite);
		file.Write(pMainDlg->m_szSelectedDescription, pMainDlg->m_szSelectedDescription.GetLength());
		file.Close();
		AfxMessageBox("新增成功！！！");
		pMainDlg->m_listcase.InsertItem(pMainDlg->m_listcase.GetItemCount(), pMainDlg->m_szSelectedName);
		
		OnOK();

	}

}

void CaseDlg::OnBtnQuit() 
{
	// TODO: Add your control notification handler code here
	OnOK();
}

