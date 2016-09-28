// ConfigTrans.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "ConfigTrans.h"
#include "comobj.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConfigTrans dialog
extern comobj  cobj;	//公共对象



CConfigTrans::CConfigTrans(CWnd* pParent /*=NULL*/)
	: CDialog(CConfigTrans::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConfigTrans)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	m_shownum=0;
}


void CConfigTrans::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConfigTrans)
	DDX_Control(pDX, IDC_LIST_SHOW, m_lstShow);
	DDX_Control(pDX, IDC_LIST_HIDE, m_lstHide);
	DDX_Radio(pDX, IDC_RADIO_TYPE, m_iType);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConfigTrans, CDialog)
	//{{AFX_MSG_MAP(CConfigTrans)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnButtonDel)
	ON_BN_CLICKED(IDC_RADIO_TYPE, OnRadioType)
	ON_BN_CLICKED(IDC_RADIO_TYPE2, OnRadioType2)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConfigTrans message handlers

BOOL CConfigTrans::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadTrans();
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CConfigTrans::OnButtonAdd() 
{
	int iCount=m_lstShow.GetCount();
	for(int i=iCount-1;i>=0;i--)
	{
		if(m_lstShow.GetSel(i)>0)
		{
			SHOW_EQU* pEqu=(SHOW_EQU*)m_lstShow.GetItemDataPtr(i);
			pEqu->bshow=0;
			m_lstShow.DeleteString(i);
			
			int iSel=m_lstHide.AddString(pEqu->devname);
			m_lstHide.SetItemDataPtr(iSel,pEqu);
		}
	}
}

void CConfigTrans::OnButtonDel() 
{
	int iCount=m_lstHide.GetCount();
	for(int i=iCount-1;i>=0;i--)
	{
		if(m_lstHide.GetSel(i)>0)
		{
			SHOW_EQU* pEqu=(SHOW_EQU*)m_lstHide.GetItemDataPtr(i);
			pEqu->bshow=1;
			m_lstHide.DeleteString(i);

			int iSel=m_lstShow.AddString(pEqu->devname);
			m_lstShow.SetItemDataPtr(iSel,pEqu);
		}
	}
}

void CConfigTrans::OnRadioType() 
{
	UpdateData();
	LoadTrans();
}

void CConfigTrans::OnRadioType2() 
{
	UpdateData();
	LoadTrans();	
}

void CConfigTrans::OnOK() 
{
	cobj.shownum=0;
	memset(cobj.showtrans,0,sizeof(SHOW_EQU)*400);
	for(int i=0;i<m_shownum;i++)
	{
		if(m_show[i].bshow==0)
		{
			memcpy(&cobj.showtrans[cobj.shownum++],&m_show[i],sizeof(SHOW_EQU));
		}
	}
	cobj.SaveShowTrans();
	CDialog::OnOK();
}


void CConfigTrans::LoadTrans()
{
	m_lstShow.ResetContent();
	m_lstHide.ResetContent();

	int index=0;
	memset(m_show,0,sizeof(SHOW_EQU)*400);
	m_shownum=rrd->ReadAllTfmData(m_show,400);
	for(int i=0;i<m_shownum;i++)
	{
		m_show[i].bshow=1;
		for(int j=0;j<cobj.shownum;j++)
		{
			if(strcmp(cobj.showtrans[j].devname,m_show[i].devname)==0 && cobj.showtrans[j].devtype==m_show[i].devtype)
			{
				m_show[i].bshow=0;
			}
		}

		if(m_iType==0)
		{
			if(strchr(m_show[i].devname,'.')==NULL)
				continue;
		}
		else
		{
			if(strchr(m_show[i].devname,'.')!=NULL)
				continue;
		}

		if(m_show[i].bshow==1)
		{
			index=m_lstShow.AddString(m_show[i].devname);
			m_lstShow.SetItemDataPtr(index,&m_show[i]);
		}
		else
		{
			index=m_lstHide.AddString(m_show[i].devname);
			m_lstHide.SetItemDataPtr(index,&m_show[i]);
		}
	}
}