// FirstDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ChooseCase.h"
#include "FirstDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// FirstDlg dialog


FirstDlg::FirstDlg(CWnd* pParent /*=NULL*/)
	: CDialog(FirstDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(FirstDlg)
	//}}AFX_DATA_INIT
}


void FirstDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(FirstDlg)
	DDX_Control(pDX, IDC_LIST_CASE, m_listcase);
	DDX_Control(pDX, IDC_EDIT_DESCRIPTION, m_edit_description);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(FirstDlg, CDialog)
	//{{AFX_MSG_MAP(FirstDlg)
	ON_NOTIFY(NM_RCLICK, IDC_LIST_CASE, OnRclickListCase)
	ON_NOTIFY(NM_CLICK, IDC_LIST_CASE, OnClickListCase)
	ON_COMMAND(ID_DELETE_CASE, OnDeleteCase)
	ON_COMMAND(ID_MODIFY_CASE, OnModifyCase)
	ON_COMMAND(ID_ADD_CASE, OnAddCase)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnButton2)
	ON_BN_CLICKED(IDC_BUTTON3, OnButton3)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// FirstDlg message handlers

BOOL FirstDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
//	m_xml.Init(".//ChooseCase.xml");

	//设置字体属性
	/*CFont font;
	font.CreateFont(16,0,0,0,FW_DONTCARE,FALSE,FALSE,0,1,
		OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DEFAULT_QUALITY,
		DEFAULT_PITCH|FF_SWISS,"宋体");
	UpdateData(FALSE);
	
	m_listcase.SetFont(&font);//设置控件中字体大小
	m_edit_description.SetFont(&font);*/


	char path[MAX_PATH]={0};

	GetModuleFileName(NULL, path, MAX_PATH);
	char *pTemp = strstr(path, "VisualPower");
	if (pTemp !=NULL)
	{
		memset(pTemp, 0, strlen(pTemp)+1);
	}

	m_szPath.Format("%s", path);

//	AfxMessageBox(m_szPath);

	Init();
	EnumCaseFolder();
	CheckRuntype();
	
	


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void FirstDlg::Init()
{
	//初始化界面
	RECT rect;
//	m_listcase.SetItemHeight(30);
	m_listcase.GetClientRect(&rect);
	
	m_listcase.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_listcase.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB|LVS_EX_TWOCLICKACTIVATE);
	m_listcase.InsertColumn(0, "案例名称", LVCFMT_LEFT, rect.right-rect.left);

}

void FirstDlg::EnumCaseFolder()
{
	m_listcase.DeleteAllItems();
	CFileFind finder;
	BOOL bHave = finder.FindFile(m_szPath+"case\\*.*");//"case\\*.*");
	if (bHave == FALSE)
	{
		AfxMessageBox("没有找到存案列的文件夹！！！");
		return ;
	}
	
	while(bHave)
	{
		bHave = finder.FindNextFile();
		if (finder.IsDots())
			continue;
		else if (finder.IsDirectory())
		{
			//m_list.InsertItem(0, time.Format("%m-%d %H:%M:%S"), bWarn);//插入行
			m_listcase.InsertItem(0, finder.GetFileName());
		}
	}
}

void FirstDlg::CheckRuntype()
{
	int m_recn=-2;
	CString szTmp, szDesPath;
	szTmp = "TABLE(common.RunType),WHERE(Nu=0)";
	common_RunType *pRec = (common_RunType*)QueryRecord("RunType",szTmp.GetBuffer(0),m_recn,"common");
	if(pRec != NULL && m_recn>0)
	{
		m_szSelectedName.Format("%s", pRec[0].Name);
		SetDlgItemText(IDC_STATIC_NAME, "当前选择案例： "+m_szSelectedName);
		
		CFile file;
		szDesPath.Format("%scase\\%s\\description.txt", m_szPath, m_szSelectedName);
		BOOL bRet = file.Open(szDesPath, CFile::modeReadWrite);
		if (bRet == FALSE)
		{
			AfxMessageBox("没有找到该案例的描述文件");
			return;
		}
		char buf[1024]={0};
		file.Read(buf, 1024);
		file.Close();
		
		m_szSelectedDescription.Format("%s", buf);
		SetDlgItemText(IDC_EDIT_DESCRIPTION, m_szSelectedDescription);
		
		szTmp.Format("%s", pRec[0].Info);
		SetDlgItemText(IDC_EDIT_INFO, szTmp);
		
		for(int i=0; i<m_listcase.GetItemCount(); i++)
		{
			if(m_listcase.GetItemText(i, 0) == m_szSelectedName)
			{
				m_listcase.EnsureVisible(i,  FALSE);
				m_listcase.SetItemState(i,  LVIS_SELECTED,  LVIS_SELECTED );  
				m_listcase.SetFocus();  
				break;
			}
		}
	}
}

void FirstDlg::OnRclickListCase(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	POSITION pos = m_listcase.GetFirstSelectedItemPosition();
	if(pos)
	{
		while(pos)
		{
			m_nSelectedItem = m_listcase.GetNextSelectedItem(pos);
			
			CPoint   point;
			::GetCursorPos(&point);
			
			CMenu menu;
			menu.LoadMenu(IDR_MENU_CASE);
			CMenu*   pPopup   =   menu.GetSubMenu(0);
			
			pPopup->TrackPopupMenu(TPM_LEFTALIGN|TPM_LEFTBUTTON, point.x, point.y, this);
		}
	}
	*pResult = 0;
}

void FirstDlg::OnClickListCase(NMHDR* pNMHDR, LRESULT* pResult)
{
	POSITION pos = m_listcase.GetFirstSelectedItemPosition();
	if(pos)
	{
		while (pos)
		{
			m_szSelectedName = "";
			m_szSelectedDescription = "";

			GetDlgItem(IDC_EDIT_DESCRIPTION)->SetWindowText("");
			int nItem = m_listcase.GetNextSelectedItem(pos);
			CString szDesPath;
			
			m_szSelectedName = m_listcase.GetItemText(nItem, 0);
			CFile file;
			szDesPath.Format("%scase\\%s\\description.txt", m_szPath, m_szSelectedName);
			BOOL bRet = file.Open(szDesPath, CFile::modeReadWrite);
			if (bRet == FALSE)
			{
				AfxMessageBox("没有找到该案例的描述文件");
				*pResult = 0;
				return;
			}
			
			char buf[1024]={0};
			file.Read(buf, 1024);
			file.Close();
			
			
			m_szSelectedDescription.Format("%s", buf);
			GetDlgItem(IDC_EDIT_DESCRIPTION)->SetWindowText(m_szSelectedDescription);

			SetDlgItemText(IDC_STATIC_NAME, "当前选择案例： "+m_szSelectedName);
			SetDlgItemText(IDC_EDIT_INFO, "");
		}
	}
	*pResult = 0;
}

void FirstDlg::OnDeleteCase()
{
	if(MessageBox("确认要删除吗？", "提示", MB_OKCANCEL) == IDOK)
	{
		m_listcase.DeleteItem(m_nSelectedItem);

		CString szTmp;
		szTmp.Format("%scase\\%s",m_szPath, m_szSelectedName);
		DeleteDirectory(szTmp.GetBuffer(0));
	}
}

void FirstDlg::OnModifyCase() 
{
	CString szName, szDescription;
	szName = m_listcase.GetItemText(m_nSelectedItem, 0);

	m_bAdd = false;
	CaseDlg dlg(this);
	dlg.m_szPath = m_szPath;
	dlg.DoModal();
}

void FirstDlg::OnAddCase() 
{
	// TODO: Add your command handler code here
	
	m_bAdd = true;
	CaseDlg dlg(this);
	dlg.m_szPath = m_szPath;
	dlg.DoModal();
}

BOOL FirstDlg::DeleteDirectory(char* psDirName)   
{   
    CFileFind tempFind;   
    char sTempFileFind[ _MAX_PATH ] = { 0 };   
    sprintf(sTempFileFind,"%s//*.*",psDirName);   
    BOOL IsFinded = tempFind.FindFile(sTempFileFind);   
    while (IsFinded)   
    {   
        IsFinded = tempFind.FindNextFile();   
        if (!tempFind.IsDots())  
        {   
            char sFoundFileName[ _MAX_PATH ] = { 0 };   
            strcpy(sFoundFileName,tempFind.GetFileName().GetBuffer(200));   
            if (tempFind.IsDirectory())   
            {   
                char sTempDir[ _MAX_PATH ] = { 0 };   
                sprintf(sTempDir,"%s//%s",psDirName,sFoundFileName);   
                DeleteDirectory(sTempDir);   
            }   
            else   
            {   
                char sTempFileName[ _MAX_PATH ] = { 0 };  
                sprintf(sTempFileName,"%s//%s",psDirName,sFoundFileName);   
                DeleteFile(sTempFileName);   
            }   
        }   
    }   
    tempFind.Close();   
    if(!RemoveDirectory(psDirName))   
    {   
        return FALSE;   
    }   
    return TRUE;   
} 

void FirstDlg::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	// TODO: Add your message handler code here
	CRect rect;
	this->GetClientRect(rect);

	m_capbitmap.LoadBitmap(IDB_BACK_BMP);

	CDC m_memdc;
	m_memdc.CreateCompatibleDC(&dc);
	CBitmap   *pOldBit=m_memdc.SelectObject(&m_capbitmap);   	

	dc.BitBlt(0, 0, rect.Width(), rect.Height(), &m_memdc, 0,0,SRCCOPY);
	m_memdc.SelectObject(pOldBit);
	m_memdc.DeleteDC();
	// Do not call CDialog::OnPaint() for painting messages
}

void FirstDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
	if (m_szSelectedName == "")
	{
		AfxMessageBox("请选择案例！！！");
		return;
	}
	CString szTmp;
	int recn;
	int nGen=0, nLine=0, nBus=0, nTfm=0, nShunt=0, nLoad=0;

	visualpw_Gen *pRec_Gen = (visualpw_Gen*)QueryRecord("Gen",NULL,recn,"visualpw");
	if(pRec_Gen !=NULL)
	{
		for (int i=0; i<recn; i++)
		{
			if(pRec_Gen[i].ele !=0 &&pRec_Gen[i].sta!=0)
				nGen++;
		}
	}

	visualpw_Bus *pRec_Bus = (visualpw_Bus*)QueryRecord("Bus",NULL,recn,"visualpw");
	if(pRec_Bus !=NULL)
	{
		for (int i=0; i<recn; i++)
		{
			if(pRec_Bus[i].ele !=0 &&pRec_Bus[i].sta!=0)
				nBus++;
		}
	}

	visualpw_Shunt *pRec_Shunt = (visualpw_Shunt*)QueryRecord("Shunt",NULL,recn,"visualpw");
	if(pRec_Shunt !=NULL)
	{
		for (int i=0; i<recn; i++)
		{
			if(pRec_Shunt[i].ele !=0 &&pRec_Shunt[i].sta!=0)
				nShunt++;
		}
	}

	visualpw_Load *pRec_Load = (visualpw_Load*)QueryRecord("Load",NULL,recn,"visualpw");
	if(pRec_Load !=NULL)
	{
		for (int i=0; i<recn; i++)
		{
			if(pRec_Load[i].ele !=0 &&pRec_Load[i].sta!=0)
				nLoad++;
		}
	}

	visualpw_Tfm1 *pRec_Tfm1 = (visualpw_Tfm1*)QueryRecord("Tfm1",NULL,recn,"visualpw");
	if(pRec_Tfm1 !=NULL)
	{
		for (int i=0; i<recn; i++)
		{
			if(pRec_Tfm1[i].ele !=0 &&pRec_Tfm1[i].sta!=0)
				nTfm++;
		}
	}

	visualpw_Tfm2 *pRec_Tfm2 = (visualpw_Tfm2*)QueryRecord("Tfm2",NULL,recn,"visualpw");
	if(pRec_Tfm2 !=NULL)
	{
		for (int i=0; i<recn; i++)
		{
			if(pRec_Tfm2[i].ele !=0 &&pRec_Tfm2[i].sta!=0)
				nTfm++;
		}
	}

	visualpw_Line *pRec_Line = (visualpw_Line*)QueryRecord("Line",NULL,recn,"visualpw");
	if(pRec_Line !=NULL)
	{
		for (int i=0; i<recn; i++)
		{
			if(pRec_Line[i].ele !=0 &&pRec_Line[i].sta!=0)
			{
				if (pRec_Line[i].EquiSta==2)
					nGen++;
				else if(pRec_Line[i].EquiSta==1)
					nLoad++;
				else
					nLine++;
			}
		}
	}

	
	szTmp.Format("案例名称:  %s  \r\n\r\n案例描述:\r\n%s\r\n\r\n电机数(%d台),线路数(%d条),母线数(%d条),变压器数(%d台),电容数(%d个),负荷数(%d个)", 
		m_szSelectedName,m_szSelectedDescription, nGen, nLine, nBus, nTfm, nShunt, nLoad);
	SetDlgItemText(IDC_EDIT_INFO, szTmp);
}

#define WM_MY_MESSAGE (WM_USER+100) 

void FirstDlg::OnButton2() 
{

	common_RunType rec;
	memset(&rec, 0, sizeof(rec));
	rec.Nu=0;
	strcpy(rec.Name, m_szSelectedName);

	CString szInfo;
	GetDlgItemText(IDC_EDIT_INFO, szInfo);
	memcpy(rec.Info, szInfo, szInfo.GetLength()+1);
	rec.TestTime = CTime::GetCurrentTime();
	LSI_AppendRec("common.RunType", &rec);

	CWnd *pWnd = CWnd::FindWindow(NULL,"可视化仿真评估系统");  
	if(pWnd != NULL)
	{
		pWnd->PostMessage(WM_MY_MESSAGE, 0, 0);
	}
}

#define WM_MAP_MESSAGE (WM_USER+101) 
void FirstDlg::OnButton3() 
{
	CWnd *pWnd = CWnd::FindWindow(NULL,"可视化仿真评估系统");  
	if(pWnd != NULL)
	{
		pWnd->PostMessage(WM_MAP_MESSAGE, 0, 0);
	}
		
}
