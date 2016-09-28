; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=3
Class1=CCMonitorErrorApp
LastClass=CModiDlg
NewFileInclude2=#include "CMonitorError.h"
ResourceCount=2
NewFileInclude1=#include "stdafx.h"
Class2=CErrorShowDlg
LastTemplate=CDialog
Resource1=IDD_ERRORSHOWDLG_DIALOG
Class3=CModiDlg
Resource2=IDD_DIALOG_MODI

[CLS:CCMonitorErrorApp]
Type=0
HeaderFile=CMonitorError.h
ImplementationFile=CMonitorError.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CCMonitorErrorApp

[DLG:IDD_ERRORSHOWDLG_DIALOG]
Type=1
Class=CErrorShowDlg
ControlCount=2
Control1=IDC_LIST,SysListView32,1350631425
Control2=IDC_STATIC_TIP,static,1342308352

[CLS:CErrorShowDlg]
Type=0
HeaderFile=ErrorShowDlg.h
ImplementationFile=ErrorShowDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CErrorShowDlg
VirtualFilter=dWC

[DLG:IDD_DIALOG_MODI]
Type=1
Class=CModiDlg
ControlCount=14
Control1=IDC_LIST_Tfm,SysListView32,1350631425
Control2=IDC_LIST,SysListView32,1350631425
Control3=IDC_EDIT_MODI,edit,1350631552
Control4=IDC_BTN_MODI,button,1342242816
Control5=IDC_STATIC_MODI,static,1342308352
Control6=IDC_STATIC_MODI2,static,1342308352
Control7=IDC_RADIO_RL,button,1342308361
Control8=IDC_RADIO_SYS,button,1342177289
Control9=IDC_LIST_SYS,SysListView32,1350631425
Control10=IDC_STATIC,button,1342177287
Control11=IDC_STATIC,button,1342177287
Control12=IDC_EDIT_SYS,edit,1350631552
Control13=IDC_STATIC_MODI3,static,1342308352
Control14=IDC_BTN_SYSDATA,button,1342242816

[CLS:CModiDlg]
Type=0
HeaderFile=ModiDlg.h
ImplementationFile=ModiDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST_SYS
VirtualFilter=dWC

