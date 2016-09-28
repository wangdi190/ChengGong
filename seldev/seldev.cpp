// seldev.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include "seldev.h"
#include "mstruct.h"
#include "selanldlg.h"
#include "sglvDlg.h"
#include "stadlg.h"
#include "szonedlg.h"
#include "SelDVDlg.h"
#include "ZoneDlg.h"
#include "stationdlg.h"
#include "SelPie.h"
#include "selrevdlg.h"
#include "defdmdlg.h"
#include "almdlg.h"
#include "YbSelDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


bool GetDevNameByID(SELECTDEV&dev);
bool GetDevIDByName(SELECTDEV&dev);

/////////////////////////////////////////////////////////////////////////////
//				本程序用于选择设备数据源
//				编程：陈金海 2004.10.18
//
/////////////////////////////////////////////////////////////////////////////
// CSeldevApp

BEGIN_MESSAGE_MAP(CSeldevApp, CWinApp)
	//{{AFX_MSG_MAP(CSeldevApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSeldevApp construction

CSeldevApp::CSeldevApp()
{
	
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSeldevApp object


CSeldevApp theApp;

//选择一个用于模拟量显示的设备及其显示的数据
//输入输出参数

bool WINAPI SelAnlSHow(SELDATA_DEV &indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //本行必须
	SelAnlDlg dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}

//选择一个单值数据源SELSINGLE_DEV;
bool WINAPI SelSingleAnl(SELSINGLE_DEV&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //本行必须
	SglVDlg dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}

//选择一个单值数据源SELSINGLE_DEV;
bool WINAPI SelDevSta(SELSINGLE_DEV&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //本行必须
	StaDlg dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}


//选择一个饼图数据;
bool WINAPI SelPie(SELECTPIE&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //本行必须
	CSelPie dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}

//选择一个区域用于网损显示;
bool WINAPI SelZone(SELDATA_DEV&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //本行必须
	SZoneDlg dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}
//关联一个设备
bool WINAPI  Select_device(SELECTDEV&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //本行必须
	SelDVDlg dlg;
	dlg.sd=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.sd;
		return true;
	}
	return false;
}

//选择一个水库;
bool WINAPI SelReservoir(SELRESERVOIR&indata)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //本行必须
	SelRevDlg dlg;
	dlg.ad=indata;
	if(dlg.DoModal()==IDOK){
		indata=dlg.ad;
		return true;
	};
	return false;
}



//配置断面;
bool WINAPI CfgSect()
{
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //本行必须
	DefdmDlg dlg;
	if(dlg.DoModal()==IDOK){
		return true;
	};
	return false;
}

//显示告警信息
void WINAPI ShowAlarm(int type)
{
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //本行必须
	AlmDlg dlg;
	dlg.type=type;
	dlg.DoModal();
}


//显示仪表信息
bool WINAPI SelYbDbs(SINGLEDBS&meter)
{
	
	AFX_MANAGE_STATE(AfxGetStaticModuleState()); //本行必须
	YbSelDlg dlg;
	dlg.tmp=meter;
	if(dlg.DoModal()==IDOK){
		meter=dlg.tmp;
		return true;
	}
	return false;
}


//关联一个设备
bool WINAPI  GetNameByID(SELECTDEV&dev)
{
	return GetDevNameByID(dev);
}

//关联一个设备
bool WINAPI  GetIDByName(SELECTDEV&dev)
{
	return GetDevIDByName(dev);
}

BOOL CSeldevApp::InitInstance() 
{
	
	::CoInitialize(NULL); 
	return CWinApp::InitInstance();
}

int CSeldevApp::ExitInstance() 
{
	
	::CoUninitialize();
	return CWinApp::ExitInstance();
}


