// FacDialog.cpp : implementation file
//

#include "stdafx.h"
#include "CMonitorError.h"
#include "FacDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CFacDialog dialog


CFacDialog::CFacDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CFacDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CFacDialog)
	m_zone = _T("");
	m_group = _T("");
	//}}AFX_DATA_INIT
	m_pstation=NULL;
	m_stationnum=0;
}

CFacDialog::~CFacDialog()
{
	if(m_pstation==NULL)
		delete []m_pstation;
}

void CFacDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CFacDialog)
	DDX_Control(pDX, IDC_LIST_STATION, m_faclist);
	DDX_Control(pDX, IDC_COMBO_ZONE, m_ComZone);
	DDX_Control(pDX, IDC_COMBO_GROUP, m_ComGroup);
	DDX_Text(pDX, IDC_EDIT_CONTROL, m_zone);
	DDX_Text(pDX, IDC_EDIT_GROUP, m_group);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CFacDialog, CDialog)
	//{{AFX_MSG_MAP(CFacDialog)
	ON_NOTIFY(NM_CLICK, IDC_LIST_STATION, OnClickListStation)
	ON_EN_CHANGE(IDC_EDIT_CONTROL, OnChangeEditControl)
	ON_EN_CHANGE(IDC_EDIT_GROUP, OnChangeEditGroup)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, OnButtonChange)
	ON_CBN_SELCHANGE(IDC_COMBO_GROUP, OnSelchangeComboGroup)
	ON_CBN_SELCHANGE(IDC_COMBO_ZONE, OnSelchangeComboZone)
	ON_BN_CLICKED(ID_REFLESH, OnReflesh)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CFacDialog message handlers

void CFacDialog::OnOK() 
{
	// TODO: Add extra validation here
	
	DWORD idi;
	if(!LSI_GetTableID("visualpw","Station",idi))
		return;

	//保存定义
	for(int i=0; i<m_stationnum; i++)
	{
		visualpw_Station* psta=m_pstation+i;
		if(psta==NULL)
			continue;

		MEMTABLE* pMem=NULL;
		visualpw_Station* pRecord = (visualpw_Station*)GetRealRecords("Station", &pMem, "visualpw");
		if (pRecord != NULL)
		{
			for (int n=0; n<pMem->userec; n++)
			{
				visualpw_Station* pstation=pRecord+n;
				if(pstation==NULL)
					continue;
				if(pstation->NU!=psta->NU)
					continue;

				LSI_PutColVal(idi, n, "ControlArea", &psta->ControlArea);
				LSI_PutColVal(idi, n, "Subjection", &psta->Subjection);
				break;
			}
		}
		
	}

	LoadStationInfo();
	//CDialog::OnOK();
}

BOOL CFacDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// TODO: Add extra initialization here
	m_ComGroup.AddString("-");
	m_ComGroup.AddString("格盟国际");
	m_ComGroup.AddString("国电集团");
	m_ComGroup.AddString("国网能源");
	m_ComGroup.AddString("华电集团");
	m_ComGroup.AddString("华能集团");
	m_ComGroup.AddString("京能控股");
	m_ComGroup.AddString("山西国际");
	m_ComGroup.AddString("中电投集团");

	LoadZoneInfo();

	m_faclist.SetExtendedStyle(LVS_EX_FULLROWSELECT|LVS_EX_CHECKBOXES|LVS_EX_GRIDLINES);
	LoadStationInfo();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CFacDialog::OnClickListStation(NMHDR* pNMHDR, LRESULT* pResult) 
{
	// TODO: Add your control notification handler code here
	LPNMLISTVIEW lp = (LPNMLISTVIEW)pNMHDR;

	*pResult = 0;

	if(lp->iItem<0)
		return;

	for(int i=0; i<m_faclist.GetItemCount(); i++)
	{
		m_faclist.SetCheck(i, FALSE);
	}

	m_faclist.SetCheck(lp->iItem, TRUE);

	m_zone=m_faclist.GetItemText(lp->iItem, 2);
	if(m_zone.GetLength()<=0)
		m_zone="-";
	m_group=m_faclist.GetItemText(lp->iItem, 3);
	if(m_group.GetLength()<=0)
		m_group="-";

	UpdateData(FALSE);
	m_ComZone.SetCurSel(0);
	m_ComGroup.SetCurSel(0);
}

void CFacDialog::LoadZoneInfo()
{
	m_ComZone.AddString("-");

	MEMTABLE* pMem=NULL;
	visualpw_Zone* pRecord = (visualpw_Zone*)GetRealRecords("Zone", &pMem, "visualpw");
	if (pRecord != NULL)
	{
		for (int i=0; i<pMem->userec; i++)
		{
			visualpw_Zone* pzone = pRecord+i;
			if(pzone==NULL)
				break;
			if(pzone->progen_generat<=0)
				continue;

			m_ComZone.AddString(pzone->Name);
		}
	}
}

void CFacDialog::LoadStationInfo()
{
	if(m_faclist.GetHeaderCtrl()->GetItemCount()<=0)
	{
		m_faclist.InsertColumn(0, "站号", LVCFMT_LEFT, 80);
		m_faclist.InsertColumn(1, "站名", LVCFMT_LEFT, 150);
		m_faclist.InsertColumn(2, "调度关系", LVCFMT_LEFT, 150);
		m_faclist.InsertColumn(3, "所属发电集团", LVCFMT_LEFT, 150);
	}
	else
	{
		m_faclist.DeleteAllItems();
	}

	if(m_pstation==NULL)
		delete []m_pstation;
	m_pstation=NULL;
	m_stationnum=0;

	CString sztext;
	int nrow=0;
	MEMTABLE* pMem=NULL;
	visualpw_Station* pRecord = (visualpw_Station*)GetRealRecords("Station", &pMem, "visualpw");
	if (pRecord != NULL)
	{
		if(pMem->userec>0)
		{
			m_stationnum=pMem->userec;
			m_pstation = new visualpw_Station[pMem->userec];
			memcpy(m_pstation, pRecord, sizeof(visualpw_Station)*m_stationnum);
		}

		for (int i=0; i<m_stationnum; i++)
		{
			visualpw_Station* pstation=m_pstation+i;
			if(pstation==NULL)
				break;
			if(pstation->Type!=STATION_W&&pstation->Type!=STATION_H&&pstation->Type!=STATION_F&&pstation->Type!=STATION_PH)
				continue;
			
			sztext.Format("%d", pstation->NU);
			m_faclist.InsertItem(nrow, sztext);

			m_faclist.SetItemText(nrow, 1, pstation->Name);
			m_faclist.SetItemText(nrow, 2, pstation->ControlArea);
			m_faclist.SetItemText(nrow, 3, pstation->Subjection);
			nrow++;
		}
	}

	m_zone="";
	m_group="";
	UpdateData(FALSE);
	m_ComZone.SetCurSel(0);
	m_ComGroup.SetCurSel(0);
}

void CFacDialog::OnChangeEditControl() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

}

void CFacDialog::OnChangeEditGroup() 
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.
	
	// TODO: Add your control notification handler code here

	
}

void CFacDialog::OnButtonChange() 
{
	// TODO: Add your control notification handler code here
	UpdateData(TRUE);
	if(m_zone=="-")
		m_zone="";
	if(m_group=="-")
		m_group="";

	int nu=0;
	int index=-1;
	for(int i=0; i<m_faclist.GetItemCount(); i++)
	{
		if(m_faclist.GetCheck(i)==FALSE)
			continue;

		nu = atoi(m_faclist.GetItemText(i,0));
		index=i;
		break;
	}
	if(nu==0)
		return;

	visualpw_Station* psel=NULL;
	for(i=0; i<m_stationnum; i++)
	{
		visualpw_Station* psta = m_pstation+i;
		if(psta==NULL)
			continue;
		if(psta->NU!=nu)
			continue;

		psel=psta;
		psta->ControlArea[0]=0;
		strcat(psta->ControlArea, m_zone);
		psta->Subjection[0]=0;
		strcat(psta->Subjection, m_group);
		break;
	}

	if(psel==NULL)
		return;

	m_faclist.SetItemText(index, 2, m_zone);
	m_faclist.SetItemText(index, 3, m_group);
//	LoadStationInfo();
}

void CFacDialog::OnSelchangeComboGroup() 
{
	// TODO: Add your control notification handler code here
	m_ComGroup.GetWindowText(m_group);
	UpdateData(FALSE);	
}

void CFacDialog::OnSelchangeComboZone() 
{
	// TODO: Add your control notification handler code here
	m_ComZone.GetWindowText(m_zone);
	UpdateData(FALSE);	
}

void CFacDialog::OnReflesh() 
{
	// TODO: Add your control notification handler code here
	this->LoadStationInfo();
}
