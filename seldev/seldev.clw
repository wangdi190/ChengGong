; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
ClassCount=28
Class1=CSeldevApp
LastClass=SelAnlDlg
NewFileInclude2=#include "seldev.h"
ResourceCount=10
NewFileInclude1=#include "stdafx.h"
Class2=SelAnlDlg
LastTemplate=CDialog
Resource1=IDD_SELDEV
Class3=SglVDlg
Resource2=IDD_ALMLSTDLG
Class4=StaDlg
Resource3=IDD_SELRESVR
Class5=SZoneDlg
Resource4=IDD_SELPIE
Class6=SelDVDlg
Resource5=IDD_SVALDLG
Class7=CZoneDlg
Class8=StationDlg
Class9=EditDev
Class10=EditBus
Class11=EditGen
Class12=EditSwitch
Class13=EditLoad
Class14=EditShunt
Class15=EditSreact
Class16=EditGround
Class17=EditTran1
Class18=EditTran2
Class19=EditStavc
Class20=EditConver
Class21=EditACLine
Class22=EditDCLine
Class23=CSelPie
Class24=SelDbDlg
Resource6=IDD_SELZONE
Class25=SelRevDlg
Resource7=IDD_SELSTA
Class26=DefdmDlg
Resource8=IDD_DEFSECTDLG
Class27=AlmDlg
Resource9=IDD_SELANLDEV
Class28=YbSelDlg
Resource10=IDD_YBSELDLG

[CLS:CSeldevApp]
Type=0
HeaderFile=seldev.h
ImplementationFile=seldev.cpp
Filter=N
LastObject=CSeldevApp
BaseClass=CWinApp
VirtualFilter=AC

[DLG:IDD_SELANLDEV]
Type=1
Class=SelAnlDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DEV,combobox,1344339970
Control5=IDC_LDEV,listbox,1352728833
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_XS,combobox,1344339970
Control9=IDC_PYJS,edit,1350631568
Control10=IDC_STATIC,static,1342308352

[CLS:SelAnlDlg]
Type=0
HeaderFile=SelAnlDlg.h
ImplementationFile=SelAnlDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=SelAnlDlg

[DLG:IDD_SVALDLG]
Type=1
Class=SglVDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DEV,combobox,1344339970
Control5=IDC_LDEV,listbox,1352728833
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_XS,combobox,1344339969

[CLS:SglVDlg]
Type=0
HeaderFile=SglVDlg.h
ImplementationFile=SglVDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DEV

[DLG:IDD_SELSTA]
Type=1
Class=StaDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DEV,combobox,1344339970
Control5=IDC_LDEV,listbox,1352728833
Control6=IDC_STATIC,static,1342308352

[CLS:StaDlg]
Type=0
HeaderFile=StaDlg.h
ImplementationFile=StaDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DEV

[DLG:IDD_SELZONE]
Type=1
Class=SZoneDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_NAME,listbox,1352728833
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO1,combobox,1344339970

[CLS:SZoneDlg]
Type=0
HeaderFile=SZoneDlg.h
ImplementationFile=SZoneDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_COMBO1

[DLG:IDD_SELDEV]
Type=1
Class=SelDVDlg
ControlCount=14
Control1=IDC_PYJS,edit,1350631568
Control2=IDC_LIST2,listbox,1352728833
Control3=IDC_LIST1,SysListView32,1350631437
Control4=IDOK,button,1342242817
Control5=IDCANCEL,button,1342242816
Control6=IDC_DTYPE,static,1342308352
Control7=IDC_STATIC,static,1342308352
Control8=IDC_STATIC,static,1342308352
Control9=IDC_NU,edit,1342244992
Control10=IDC_NAME,edit,1342244992
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_SHOWALL,button,1342242816
Control14=IDC_STATIC,static,1342308352

[CLS:SelDVDlg]
Type=0
HeaderFile=SelDVDlg.h
ImplementationFile=SelDVDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_LIST1
VirtualFilter=dWC

[CLS:CZoneDlg]
Type=0
HeaderFile=ZoneDlg.h
ImplementationFile=ZoneDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_LIST1

[CLS:StationDlg]
Type=0
HeaderFile=StationDlg.h
ImplementationFile=StationDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_CREATE

[CLS:EditDev]
Type=0
HeaderFile=EditDev.h
ImplementationFile=EditDev.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=EditDev

[CLS:EditBus]
Type=0
HeaderFile=EditBus.h
ImplementationFile=EditBus.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=EditBus

[CLS:EditGen]
Type=0
HeaderFile=EditGen.h
ImplementationFile=EditGen.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=EditGen

[CLS:EditSwitch]
Type=0
HeaderFile=EditSwitch.h
ImplementationFile=EditSwitch.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=EditSwitch

[CLS:EditLoad]
Type=0
HeaderFile=EditLoad.h
ImplementationFile=EditLoad.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=EditLoad

[CLS:EditShunt]
Type=0
HeaderFile=EditShunt.h
ImplementationFile=EditShunt.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:EditSreact]
Type=0
HeaderFile=EditSreact.h
ImplementationFile=EditSreact.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=EditSreact

[CLS:EditGround]
Type=0
HeaderFile=EditGround.h
ImplementationFile=EditGround.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=EditGround

[CLS:EditTran1]
Type=0
HeaderFile=EditTran1.h
ImplementationFile=EditTran1.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=EditTran1

[CLS:EditTran2]
Type=0
HeaderFile=EditTran2.h
ImplementationFile=EditTran2.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=EditTran2

[CLS:EditStavc]
Type=0
HeaderFile=EditStavc.h
ImplementationFile=EditStavc.cpp
BaseClass=CDialog
Filter=D
LastObject=EditStavc
VirtualFilter=dWC

[CLS:EditConver]
Type=0
HeaderFile=EditConver.h
ImplementationFile=EditConver.cpp
BaseClass=CDialog
Filter=D
LastObject=EditConver
VirtualFilter=dWC

[CLS:EditACLine]
Type=0
HeaderFile=EditACLine.h
ImplementationFile=EditACLine.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[CLS:EditDCLine]
Type=0
HeaderFile=EditDCLine.h
ImplementationFile=EditDCLine.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=EditDCLine

[DLG:IDD_SELPIE]
Type=1
Class=CSelPie
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_COMBO1,combobox,1344339970
Control5=IDC_LIST1,listbox,1352728833
Control6=IDC_STATIC,static,1342308352

[CLS:CSelPie]
Type=0
HeaderFile=SelPie.h
ImplementationFile=SelPie.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[CLS:SelDbDlg]
Type=0
HeaderFile=SelDbDlg.h
ImplementationFile=SelDbDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

[DLG:IDD_SELRESVR]
Type=1
Class=SelRevDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728833

[CLS:SelRevDlg]
Type=0
HeaderFile=SelRevDlg.h
ImplementationFile=SelRevDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[DLG:IDD_DEFSECTDLG]
Type=1
Class=DefdmDlg
ControlCount=30
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DMNAME,edit,1350631552
Control5=IDC_DEFINED,listbox,1352728833
Control6=IDC_ADDDM,button,1342242816
Control7=IDC_STATIC,static,1342308352
Control8=IDC_RL,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_PAR,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_DELETEDM,button,1342242816
Control15=IDC_STATIC,static,1342308352
Control16=IDC_LINEID,listbox,1352728833
Control17=IDC_DELETELINE,button,1342242816
Control18=IDC_STATIC,button,1342177287
Control19=IDC_MODIDM,button,1342242816
Control20=IDC_LINE,listbox,1352728833
Control21=IDC_STATIC,static,1342308352
Control22=IDC_STATIC,static,1342308352
Control23=IDC_ACDC,combobox,1344339970
Control24=IDC_STATIC,static,1342308352
Control25=IDC_ADDYS,button,1342242816
Control26=IDC_SUBYS,button,1342242816
Control27=IDC_STATIC,static,1342308352
Control28=IDC_PYJS,edit,1350631552
Control29=IDC_MSG,edit,1350631552
Control30=IDC_STATIC,static,1342308352

[CLS:DefdmDlg]
Type=0
HeaderFile=DefdmDlg.h
ImplementationFile=DefdmDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=DefdmDlg
VirtualFilter=dWC

[DLG:IDD_ALMLSTDLG]
Type=1
Class=AlmDlg
ControlCount=1
Control1=IDC_LIST1,SysListView32,1350631425

[CLS:AlmDlg]
Type=0
HeaderFile=AlmDlg.h
ImplementationFile=AlmDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AlmDlg

[DLG:IDD_YBSELDLG]
Type=1
Class=YbSelDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_YBSEL,combobox,1344339970
Control5=IDC_DEVLST,listbox,1352728833
Control6=IDC_STATIC,static,1342308352
Control7=IDC_SELFLD,combobox,1344339970

[CLS:YbSelDlg]
Type=0
HeaderFile=YbSelDlg.h
ImplementationFile=YbSelDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_DEVLST

