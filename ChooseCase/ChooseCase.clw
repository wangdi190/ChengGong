; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=4
Class1=CChooseCaseApp
LastClass=FirstDlg
NewFileInclude2=#include "ChooseCase.h"
ResourceCount=3
NewFileInclude1=#include "stdafx.h"
Class2=FirstDlg
LastTemplate=CListCtrl
Resource1=IDD_FIRST_DIALOG
Resource2=IDD_CASE_DIALOG
Class3=CaseDlg
Class4=CMyListCtrl
Resource3=IDR_MENU_CASE

[CLS:CChooseCaseApp]
Type=0
HeaderFile=ChooseCase.h
ImplementationFile=ChooseCase.cpp
Filter=N
BaseClass=CWinApp
VirtualFilter=AC
LastObject=CChooseCaseApp

[DLG:IDD_FIRST_DIALOG]
Type=1
Class=FirstDlg
ControlCount=8
Control1=IDC_LIST_CASE,SysListView32,1350631429
Control2=IDC_EDIT_DESCRIPTION,edit,1353779396
Control3=IDC_STATIC,button,1342177287
Control4=IDC_BUTTON1,button,1342242816
Control5=IDC_STATIC_NAME,static,1342308352
Control6=IDC_BUTTON2,button,1342242816
Control7=IDC_BUTTON3,button,1342242816
Control8=IDC_EDIT_INFO,edit,1352730820

[CLS:FirstDlg]
Type=0
HeaderFile=FirstDlg.h
ImplementationFile=FirstDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=FirstDlg
VirtualFilter=dWC

[MNU:IDR_MENU_CASE]
Type=1
Class=?
Command1=ID_MODIFY_CASE
Command2=ID_ADD_CASE
Command3=ID_DELETE_CASE
CommandCount=3

[DLG:IDD_CASE_DIALOG]
Type=1
Class=CaseDlg
ControlCount=6
Control1=IDC_EDIT_NAME,edit,1350631552
Control2=IDC_EDIT_DESCRIPTION,edit,1350631492
Control3=IDC_BTN_SAVE,button,1342242816
Control4=IDC_BTN_QUIT,button,1342242816
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[CLS:CaseDlg]
Type=0
HeaderFile=aseDlg.h
ImplementationFile=aseDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CaseDlg
VirtualFilter=dWC

[CLS:CMyListCtrl]
Type=0
HeaderFile=MyListCtrl.h
ImplementationFile=MyListCtrl.cpp
BaseClass=CListCtrl
Filter=W
VirtualFilter=FWC
LastObject=CMyListCtrl

