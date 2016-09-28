// ModiDlg.cpp : implementation file
//

#include "stdafx.h"
#include "CMonitorError.h"
#include "ModiDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CModiDlg dialog

CString strTemp;
int CNCODE[] = {45217,45253,45761,46318,46826,47010,47297,47614,48119,48119,49062,49324,49896,
				50371,50614,50622,50906,51387,51446,52218,52698,52698,52698,52980,53689,54481,
				55290};
char LETTER[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};


CModiDlg::CModiDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CModiDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CModiDlg)
	//}}AFX_DATA_INIT
}


void CModiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CModiDlg)
	DDX_Control(pDX, IDC_LIST_SYS, m_list_sys);
	DDX_Control(pDX, IDC_LIST, m_list);
	DDX_Control(pDX, IDC_LIST_Tfm, m_list_tfm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CModiDlg, CDialog)
	//{{AFX_MSG_MAP(CModiDlg)
	ON_BN_CLICKED(IDC_BUTTON1, OnButton1)
	ON_NOTIFY(NM_CLICK, IDC_LIST, OnClickList)
	ON_NOTIFY(NM_CLICK, IDC_LIST_Tfm, OnClickLISTTfm)
	ON_BN_CLICKED(IDC_BTN_MODI, OnBtnModi)
	ON_BN_CLICKED(IDC_RADIO_RL, OnRadioRl)
	ON_BN_CLICKED(IDC_RADIO_SYS, OnRadioSys)
//	ON_BN_CLICKED(IDC_BTN_SYS, OnBtnSys)
	ON_NOTIFY(NM_CLICK, IDC_LIST_SYS, OnClickListSys)
	ON_BN_CLICKED(IDC_BTN_SYSDATA, OnBtnSysdata)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CModiDlg message handlers

void CModiDlg::OnButton1() 
{
	// TODO: Add your control notification handler code here
//	ListStation();
}


void CModiDlg::ListStation()
{
	int nRow;

	MEMTABLE* pMem=NULL;
	visualpw_Station* pRecord = (visualpw_Station*)GetRealRecords("Station", &pMem, "visualpw");
	if (pRecord != NULL)
	{
		for (int i=pMem->userec; i>0; i--)
		{
			nRow = m_list.InsertItem(0, pRecord[i-1].Name);//插入行
			strTemp.Format("%d", pRecord[i-1].NU);
			m_list.SetItemText(nRow, 1, strTemp);//设置数据
		}
	}
}

void CModiDlg::ListSys()
{
	int nRow;
	
	MEMTABLE* pMem=NULL;
	visualpw_SystemData* pRecord = (visualpw_SystemData*)GetRealRecords("SystemData", &pMem, "visualpw");
	if (pRecord != NULL)
	{
		for (int i=0; i<pMem->userec; i++)
		{
			nRow = m_list_sys.InsertItem(0, pRecord[i-1].Name);//插入行
			strTemp.Format("%d", i);
			m_list_sys.SetItemText(nRow, 1, strTemp);//设置数据
			strTemp.Format("%d", pMem->id);
			m_list_sys.SetItemText(nRow, 2, strTemp);//设置数据
		}
	}
}

BOOL CModiDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	m_list.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_list.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB|LVS_EX_TWOCLICKACTIVATE);
	m_list.InsertColumn(0, "名称", LVCFMT_LEFT, 246);
	m_list.InsertColumn(1, "NU", LVCFMT_LEFT, 0);

	m_list_tfm.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_list_tfm.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB|LVS_EX_TWOCLICKACTIVATE);
	m_list_tfm.InsertColumn(0, "名称", LVCFMT_LEFT, 246);
	m_list_tfm.InsertColumn(1, "位置", LVCFMT_LEFT, 0);
	m_list_tfm.InsertColumn(2, "表号", LVCFMT_LEFT, 0);

	m_list_sys.ModifyStyle(LVS_TYPEMASK, LVS_REPORT);
	m_list_sys.SetExtendedStyle(LVS_EX_GRIDLINES|LVS_EX_FULLROWSELECT|LVS_EX_FLATSB|LVS_EX_TWOCLICKACTIVATE);
	m_list_sys.InsertColumn(0, "名称", LVCFMT_LEFT, 246);
	m_list_sys.InsertColumn(1, "位置", LVCFMT_LEFT, 0);
	m_list_sys.InsertColumn(2, "表号", LVCFMT_LEFT, 0);

	OnRadioRl();
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CModiDlg::OnClickList(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;

	if(pNMListView->iItem!=-1)
	{
		m_list_tfm.DeleteAllItems();
		char ch[20] = {0};
		m_list.GetItemText(pNMListView->iItem, 1, ch, 20);
		DWORD staNU = atoi(ch);
		MEMTABLE* pMem=NULL;
		visualpw_Tfm1* pRecord1 = (visualpw_Tfm1*)GetRealRecords("Tfm1", &pMem, "visualpw");
		for(int i=0; i<pMem->userec; i++)
		{
			if(staNU == pRecord1[i].Station)
			{
				int nRow = m_list_tfm.InsertItem(0, pRecord1[i].Name);//插入行
				strTemp.Format("%d", i);
				m_list_tfm.SetItemText(nRow, 1, strTemp);//设置数据
				strTemp.Format("%d", pMem->id);
				m_list_tfm.SetItemText(nRow, 2, strTemp);//设置数据
			}
		}

		visualpw_Tfm2* pRecord2 = (visualpw_Tfm2*)GetRealRecords("Tfm2", &pMem, "visualpw");
		for(i=0; i<pMem->userec; i++)
		{
			if(staNU == pRecord2[i].Station)
			{
				int nRow = m_list_tfm.InsertItem(0, pRecord2[i].Name);//插入行
				strTemp.Format("%d", i);
				m_list_tfm.SetItemText(nRow, 1, strTemp);//设置数据
				strTemp.Format("%d", pMem->id);
				m_list_tfm.SetItemText(nRow, 2, strTemp);//设置数据
			}
		}

	}
	*pResult = 0;
}

void CModiDlg::OnClickLISTTfm(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	//int nPos, iTable;
	m_iTable = 0;
	m_nPos = 0;
	if(pNMListView->iItem!=-1)
	{
		char ch[64] = {0};
		m_list_tfm.GetItemText(pNMListView->iItem, 0, ch, 64);
		strTemp.Format("%s", ch);
		SetDlgItemText(IDC_STATIC_MODI, strTemp);
		m_list_tfm.GetItemText(pNMListView->iItem, 1, ch, 64);
		m_nPos = atoi(ch);
		m_list_tfm.GetItemText(pNMListView->iItem, 2, ch, 64);
		m_iTable = atoi(ch);
		LSI_GetColVal(m_iTable, m_nPos, "Pmax", &m_fPmax);
		strTemp.Format("%f", m_fPmax);
		SetDlgItemText(IDC_EDIT_MODI, strTemp);
	}
	*pResult = 0;
}

void CModiDlg::OnBtnModi() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDlgItemText(IDC_EDIT_MODI, strTemp);
	if (m_iTable == -1 || m_nPos == -1)
	{
		AfxMessageBox("青选择修改项目");
		return;
	}
	if (strTemp.IsEmpty()!=TRUE && fabs((m_fPmax-atof(strTemp.GetBuffer(0))))>0.01)
	{
		m_fPmax = atof(strTemp.GetBuffer(0));
		LSI_PutColVal(m_iTable, m_nPos, "Pmax", &m_fPmax);
		strTemp.Format("%d, %d, %f", m_iTable, m_nPos, m_fValue);
		AfxMessageBox(strTemp);
		AfxMessageBox("修改成功");
	}
	else
		AfxMessageBox("修改失败");
}



void CModiDlg::OnRadioRl() 
{
	// TODO: Add your control notification handler code here
	m_iTable = -1;
	m_nPos = -1;
	m_list.DeleteAllItems();
	m_list_tfm.DeleteAllItems();
	m_list_sys.DeleteAllItems();
	GetDlgItem(IDC_EDIT_MODI)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_MODI)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_SYS)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_SYSDATA)->EnableWindow(FALSE);
	ListStation();
}

void CModiDlg::OnRadioSys() 
{
	// TODO: Add your control notification handler code here
	m_iTable = -1;
	m_nPos = -1;
	m_list.DeleteAllItems();
	m_list_tfm.DeleteAllItems();
	m_list_sys.DeleteAllItems();
	GetDlgItem(IDC_EDIT_MODI)->EnableWindow(FALSE);
	GetDlgItem(IDC_BTN_MODI)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_SYS)->EnableWindow(TRUE);
	GetDlgItem(IDC_BTN_SYSDATA)->EnableWindow(TRUE);
	ListSys();
}

void CModiDlg::OnBtnSys() 
{
	// TODO: Add your control notification handler code here
	/*AfxMessageBox("1");
	UpdateData();
	GetDlgItemText(IDC_EDIT_SYS, strTemp);
	AfxMessageBox(strTemp);
	if (strTemp.IsEmpty())
		return;
	AfxMessageBox(strTemp);
	
	if (fabs((m_fValue-atof(strTemp.GetBuffer(0))))>0.01)
	{
		m_fValue = atof(strTemp.GetBuffer(0));
		LSI_PutColVal(m_iTable, m_nPos, "Value", &m_fValue);
		strTemp.Format("%d, %d, %f", m_iTable, m_nPos, m_fValue);
		AfxMessageBox(strTemp);
	}*/
}

void CModiDlg::OnClickListSys(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	NM_LISTVIEW* pNMListView=(NM_LISTVIEW*)pNMHDR;
	//int nPos, iTable;
	
	m_iTable = 0;
	m_nPos = 0;
	if(pNMListView->iItem!=-1)
	{
		char ch[64] = {0};
		m_list_sys.GetItemText(pNMListView->iItem, 1, ch, 64);
		m_nPos = atoi(ch);
		m_list_sys.GetItemText(pNMListView->iItem, 2, ch, 64);
		m_iTable = atoi(ch);
		LSI_GetColVal(m_iTable, m_nPos, "Value", &m_fValue);
		strTemp.Format("%f", m_fValue);
		SetDlgItemText(IDC_EDIT_SYS, strTemp);

	//	strTemp.Format("%d, %d, %f", m_iTable, m_nPos, m_fValue);
	//	AfxMessageBox(strTemp);
	}
	*pResult = 0;
}

void CModiDlg::OnBtnSysdata() 
{
	// TODO: Add your control notification handler code here
	UpdateData();
	GetDlgItemText(IDC_EDIT_SYS, strTemp);
	if (m_iTable == -1 || m_nPos == -1)
	{
		AfxMessageBox("青选择修改项目");
		return;
	}
	if (strTemp.IsEmpty()!=TRUE && fabs((m_fValue-atof(strTemp.GetBuffer(0))))>0.01)
	{
		m_fValue = atof(strTemp.GetBuffer(0));
		LSI_PutColVal(m_iTable, m_nPos, "Value", &m_fValue);
		AfxMessageBox("修改成功");
	}
	else
		AfxMessageBox("修改失败");
}
