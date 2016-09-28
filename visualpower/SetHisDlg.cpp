// SetHisDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "SetHisDlg.h"
#include "gdata.h"
#include "middll.h"
#include "comobj.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern comobj  cobj;	//公共对象
/////////////////////////////////////////////////////////////////////////////
// SetHisDlg dialog


SetHisDlg::SetHisDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SetHisDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SetHisDlg)
	//}}AFX_DATA_INIT
}


void SetHisDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SetHisDlg)
	DDX_Control(pDX, IDC_TIME2, m_time2);
	DDX_Control(pDX, IDC_TIME1, m_time1);
	DDX_Control(pDX, IDC_DATE2, m_date2);
	DDX_Control(pDX, IDC_DATE1, m_date1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SetHisDlg, CDialog)
	//{{AFX_MSG_MAP(SetHisDlg)
	ON_BN_CLICKED(IDC_GETHISLIST, OnGethislist)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SetHisDlg message handlers

BOOL SetHisDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	dbm->hdbok=IniProvider();

	////////////////////////////////////
	dbm->hdbok=TRUE;
	/////////////////////////////////////
	if(dbm->hdbok==FALSE)
	{
		MessageBox("历史数据库初始化错误！","错误",MB_OK|MB_ICONSTOP);
		CDialog::OnCancel();
		return FALSE;
	}
	SetDlgItemInt(IDC_DMSUM,0);
	SetDlgItemInt(IDC_SPEED,5);
	EnableItem(IDOK,false);
	return TRUE;
}

//获取历史断面
void SetHisDlg::OnGethislist() 
{ 
	//int i;
	time_t t1,t2;
	CTime tm1,tm2,tmp;
	m_date1.GetTime(tm1);
	m_time1.GetTime(tm2);
	tmp=CTime(tm1.GetYear(),tm1.GetMonth(),tm1.GetDay(),tm2.GetHour(),tm2.GetMinute(),0);
	t1=tmp.GetTime();
	m_date2.GetTime(tm1);
	m_time2.GetTime(tm2);
	tmp=CTime(tm1.GetYear(),tm1.GetMonth(),tm1.GetDay(),tm2.GetHour(),tm2.GetMinute(),0);
	t2=tmp.GetTime();
	if(t2<t1)
	{
		MessageBox("结束时间必须小于开始时间，请重新输入！","错误",MB_OK|MB_ICONSTOP);
		return;
	}


	int i;
	tm1=CTime(1990,1,1,0,0,0);
	for(i=0;i<100;i++)
	{
		tm1+=CTimeSpan(0,0,0, 5);
		dbm->hlist[i]=tm1.GetTime();
	}
	dbm->hsum=100;


	dbm->hsum=GetSectionList(t1,t2,dbm->hlist,2048);
	SetDlgItemInt(IDC_DMSUM,dbm->hsum);
	//清除原注册
	ClearAllRegData();
	//注册本页面
	cobj.swin->RegistHisAllDev();
	BeginGettingData();
	

	EnableItem(IDOK,true);
}


void SetHisDlg::EnableItem(int id, bool enable)
{
	CWnd *wnd;
	wnd=GetDlgItem(id);
	if(wnd==NULL) return;
	wnd->EnableWindow(enable);
}

void SetHisDlg::OnCancel() 
{
	if(dbm->hdbok==TRUE) CloseProvider();
	dbm->hdbok=FALSE;
	CDialog::OnCancel();
}

void SetHisDlg::OnOK() 
{
	dbm->hspeed=GetDlgItemInt(IDC_SPEED);
	if(dbm->hspeed<0||dbm->hspeed>60)
	{
		MessageBox("回放速度必须介于0-60秒之间\n请重新输入！","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	
	CDialog::OnOK();
}
