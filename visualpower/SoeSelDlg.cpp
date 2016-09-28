// SoeSelDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "SoeSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// SoeSelDlg dialog


SoeSelDlg::SoeSelDlg(CWnd* pParent /*=NULL*/)
	: CDialog(SoeSelDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(SoeSelDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	soe=0; //soe内容
	soesum=0;	 //soe个数
}


void SoeSelDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(SoeSelDlg)
	DDX_Control(pDX, IDC_TIME2, m_time2);
	DDX_Control(pDX, IDC_TIME1, m_time1);
	DDX_Control(pDX, IDC_DATE2, m_date2);
	DDX_Control(pDX, IDC_DATE1, m_date1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(SoeSelDlg, CDialog)
	//{{AFX_MSG_MAP(SoeSelDlg)
	ON_BN_CLICKED(IDC_GETSELSOE, OnGetselsoe)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// SoeSelDlg message handlers

BOOL SoeSelDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	EnableItem(IDOK,false);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void SoeSelDlg::OnGetselsoe() 
{
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

	AutoCreateData();
	SetDlgItemInt(IDC_NUM,soesum);
	
	if(t2<t1)
	{
		MessageBox("结束时间必须小于开始时间，请重新输入！","错误",MB_OK|MB_ICONSTOP);
		return;
	}
	
	EnableItem(IDOK,true);
}


void SoeSelDlg::EnableItem(int id, bool enable)
{
	CWnd *wnd;
	wnd=GetDlgItem(id);
	if(wnd==NULL) return;
	wnd->EnableWindow(enable);
}

//自动生成数据100点数据
void SoeSelDlg::AutoCreateData()
{	
	int i,s,a,b;
	CTime tm1,tm2;
	if(soe!=NULL) delete soe;
	soe=new NSOES[100]; 
	soesum=100;
	tm1=CTime(2008,9,13,3,21,22);
	//CClientDC dc(0);
	//char p[100];
	s=0;
	b=0;
	for(i=0;i<100;i++)
	{
		a=1+rand()%19;
		b=b+1200;
		s=b/1000;
		tm2=tm1+CTimeSpan(0,0,0,s);
		//sprintf(p,"i=%d,a=%d  b=%d s=%d",i,a,b%1000,s);
		//dc.TextOut(10,10+i*20,p);
		soe[i].swtid=a;
		soe[i].sta=rand()%2;
		soe[i].tm=tm2;
		soe[i].ms=b%1000;
	}
}
