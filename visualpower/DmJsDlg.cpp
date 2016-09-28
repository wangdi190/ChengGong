// DmJsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "VisualPower.h"
#include "DmJsDlg.h"
#include <vector>
#include <algorithm>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DmJsDlg dialog


DmJsDlg::DmJsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DmJsDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DmJsDlg)
	//}}AFX_DATA_INIT
	num=0;
}

DmJsDlg::~DmJsDlg()
{
//	KillTimer(100);
}
void DmJsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DmJsDlg)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DmJsDlg, CDialog)
	//{{AFX_MSG_MAP(DmJsDlg)
	ON_WM_SIZE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DmJsDlg message handlers

BOOL DmJsDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();
	dbwin.Create("","",WS_CHILD|WS_VISIBLE|WS_HSCROLL|WS_VSCROLL,CRect(0,0,300,300),this,100);
	SetTimer(100,5000,NULL);
	return TRUE;  
}

void DmJsDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	wx=cx;
	wy=cy;
	dbwin.MoveWindow(0,0,wx,wy);
	
}

void DmJsDlg::OnTimer(UINT nIDEvent) 
{
	switch(nIDEvent)
	{
	case 100:
		TimeRead();
		break;
	}
	CDialog::OnTimer(nIDEvent);
}



void DmJsDlg::TimeRead()
{
	int i;
	double a;
	int oldnum=num;
	if(!rrd->ReadPreAlarm(pdf,num,256)) return;

	std::vector<common_PreDefSF*> sfvtr;
	for(i=0;i<num;i++)
		sfvtr.push_back(&pdf[i]);
	std::sort(sfvtr.begin(),sfvtr.end(),CmpRateForSort);

	i=0;
	for(std::vector<common_PreDefSF*>::iterator itr=sfvtr.begin();itr!=sfvtr.end();++itr)
	{
		pdm[i].ID=(*itr)->ID;
		strcpy(pdm[i].Name,(*itr)->Name);
		pdm[i].Par=(float)((*itr)->CurPar*100);
		pdm[i].curval=(*itr)->curval;
		pdm[i].Vmax=(*itr)->Vmax;
		pdm[i].Vmin=(*itr)->Pcur;
		strcpy(pdm[i].msg,(*itr)->msg);
		if(pdm[i].Vmax!=0 && pdm[i].curval>0)
		{
			a=pdm[i].curval*100.00/pdm[i].Vmax;
		}
		else if(pdm[i].curval<0 && (*itr)->Pcur<0)
			a=pdm[i].curval*100.00/(*itr)->Pcur;
		else a=0;
		a=a<0 ? -a:a;
		pdm[i].fz=(float)a;
		if(a>=100)
		{
			strcpy(pdm[i].gjstr,"越限");
			pdm[i].color=0xff;
		}else {
			strcpy(pdm[i].gjstr,"正常");
			pdm[i].color=0;
		}
		i++;
	}
	if(oldnum!=num) SetAllList();
	else Invalidate();
}


//设置全部的列表
void DmJsDlg::SetAllList()
{
	dbwin.reset();  //复位数据库 
	dbwin.SetInitPara((char*)&pdm,sizeof(PRESMDATA),256,num);
	dbwin.AddItemType("断面编号(ID)",EDIT_INT,4,0,-1,-1,0,8);
	dbwin.AddItemType("断面名称",EDIT_STR,45,0,-1,-1,0,20);
	dbwin.AddItemType("断面上限",EDIT_FLOAT,4,0,-1,-1,2,8);
	dbwin.AddItemType("断面下限",EDIT_FLOAT,4,0,-1,-1,2,8);
	dbwin.AddItemType("当前断面潮流",EDIT_FLOAT,4,0,-1,-1,2,12);
	dbwin.AddItemType("告警限值%",EDIT_FLOAT,4,0,-1,-1,2,9);
	dbwin.AddItemType("当前负载率%",EDIT_FLOAT,4,0,-1,-1,2,9);
	dbwin.AddItemType("过载情况",EDIT_STR,16,0,-1,-1,0,9);
	dbwin.AddItemType("备注信息",EDIT_STR,45,0,-1,-1,0,25);
	dbwin.Invalidate();
}
