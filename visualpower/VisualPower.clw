; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CMainFrame
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "VisualPower.h"
LastPage=0

ClassCount=35
Class1=CVisualPowerApp
Class3=CMainFrame
Class4=CAboutDlg

ResourceCount=36
Resource1=IDB_BITMAP1
Resource2=IDD_ALARMDLG
Resource6=IDD_COLORDLG
Resource7=IDR_LOWFBAR
Class2=CMainWin
Resource8=IDD_ABOUTBOX
Resource9=IDD_LOGIN
Resource10=IDR_AMENU
Resource11=IDR_DMBAR
Resource12=IDD_LAYERDLG
Resource3=IDD_DISPATTR
Resource4=IDR_MAINFRAME
Resource5=IDR_MDLBAR
Class5=HisToolbar
Class6=ScadaBar
Class7=LoginDlg
Class8=ScadaWin
Class9=CSysVBar
Class10=NavgDlg
Class11=DgxCrDlg
Class12=MyTips
Class13=CLayerDlg
Class14=CCfgShow
Class15=StFlwDlg
Class16=prtmode
Class17=SenDlg
Class18=CViewDev
Resource13=IDR_FLOWMENU
Resource14=IDD_PRTDLG
Class19=OpenPw0
Resource15=IDR_SENBAR
Class20=Lowfwin
Resource16=IDR_TABLEMENU
Resource17=IDR_FUNBAR
Resource18=IDD_CFGHIS
Resource19=IDR_RMENU
Resource20=IDD_SENDLG
Class21=SetHisDlg
Resource21=IDD_SECTFLOW
Resource22=IDD_DMDLG
Resource23=IDR_SWSOEBAR
Resource24=IDR_PLATEMENU
Class22=MenuWin
Resource25=IDR_CTLBAR
Class23=DmJsDlg
Class24=GzTblDlg
Resource26=IDD_GDDLG
Resource27=IDR_HISBAR
Class25=CCfgAlmDlg
Class26=MsAlmWin
Resource28=IDD_SOEDLG
Class27=pagectl
Class28=CChildFrm
Class29=CNavWin
Class30=CChrgWin
Resource29=IDD_OPENPW0
Resource30=IDR_FMENU
Class31=SoeSelDlg
Class32=SoePlayBar
Resource31=IDD_VIEWDEV
Class33=YbGdDlg
Resource32=IDD_PRECFGDLG
Resource33=IDD_NVGDLG
Class34=FunToolBar
Resource34=IDR_DGXMENU
Class35=CConfigTrans
Resource35=IDD_TABLEDLG
Resource36=IDD_DIALOG_CFGTRA

[CLS:CVisualPowerApp]
Type=0
HeaderFile=VisualPower.h
ImplementationFile=VisualPower.cpp
Filter=N

[CLS:CMainWin]
Type=0
HeaderFile=MainWin.h
ImplementationFile=MainWin.cpp
Filter=W
LastObject=AFX_ID_PREVIEW_NEXT
BaseClass=CWnd 
VirtualFilter=WC

[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
BaseClass=CFrameWnd
VirtualFilter=fWC
LastObject=CMainFrame




[CLS:CAboutDlg]
Type=0
HeaderFile=VisualPower.cpp
ImplementationFile=VisualPower.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=6
Control1=IDC_STATIC,static,1342177294
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_OPEN
Command2=ID_FILE_PRINT
Command3=IDC_SAVETOBMP
Command4=IDC_SAVETOJPG
Command5=IDC_RELOGIN
Command6=ID_APP_EXIT
Command7=IDC_CTLLAYER
Command8=IDC_CFGTRANS
Command9=IDC_BASFLOW
Command10=IDC_SHOWDGX
Command11=IDC_DMFLOW
Command12=IDC_GENREV
Command13=IDC_GENREVQ
Command14=IDC_TRANREV
Command15=IDC_BYQWD
Command16=IDC_PREDMJS
Command17=ID_TOOL_PAINT
Command18=ID_TOOL_DBM
Command19=ID_TOOL_CASEMG
Command20=ID_TOOL_EST
Command21=ID_TOOL_HISTORY
Command22=ID_TOOL_SECT
Command23=ID_TOOL_SE
Command24=ID_TOOL_EM
Command25=IDC_NEWWINDOW
Command26=IDC_MAINPAGE
Command27=IDC_NAVIGATION
Command28=IDC_SHOWCRMAP
Command29=IDC_SHOWSYS
Command30=ID_VIEW_TOOLBAR
Command31=ID_VIEW_STATUS_BAR
Command32=IDC_SV_AUTO
Command33=IDC_SVWIN
Command34=IDC_FULLSCR
Command35=IDC_OPENMENUWIN
Command36=IDC_DELCHILD
Command37=ID_CHANGE
Command38=ID_APP_ABOUT
CommandCount=38

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_EDIT_COPY
Command2=ID_EDIT_PASTE
Command3=ID_EDIT_UNDO
Command4=ID_EDIT_CUT
Command5=ID_NOFULLSCR
Command6=ID_EDIT_COPY
Command7=ID_EDIT_PASTE
Command8=ID_EDIT_CUT
Command9=ID_EDIT_UNDO
CommandCount=9

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_PRINT
Command2=ID_FILE_OPEN
Command3=ID_NORMAL
Command4=ID_MOVEPIC
Command5=ID_PARTZOOM
Command6=ID_ZOOMIO
Command7=ID_ZOOMNML
Command8=ID_ZOOMALL
Command9=ID_LASTHMI
Command10=IDC_NEXTHMI
Command11=IDC_SHOWDGX
Command12=ID_DGXSELCB
Command13=IDC_CFGATTR
Command14=IDC_FLOW
Command15=ID_ROTATE
Command16=ID_NORMALNS
Command17=IDC_OPENMENUWIN
Command18=ID_CHANGE
Command19=IDC_SHOWPLATE
CommandCount=19

[TB:IDR_HISBAR]
Type=1
Class=CMainWin
Command1=ID_SHOWTEXT
Command2=IDC_SPDOWN
Command3=ID_SPSHOW
Command4=IDC_SPUP
Command5=ID_GOTOTOP
Command6=ID_FASTREV
Command7=ID_PLAY
Command8=ID_FASTFW
Command9=ID_PAUSE
Command10=ID_SHOWTIME
CommandCount=10

[DLG:IDD_COLORDLG]
Type=1
Class=DgxCrDlg
ControlCount=0

[DLG:IDD_DISPATTR]
Type=1
Class=CCfgShow
ControlCount=58
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_GENDT,button,1342242819
Control4=IDC_FLOWPIE,button,1342242819
Control5=IDC_DGXTYPE,combobox,1344339970
Control6=IDC_TRANDGX,button,1342242819
Control7=IDC_ONELINE,button,1342242819
Control8=IDC_STATIC,static,1342308352
Control9=IDC_SMOOTH,edit,1350639744
Control10=IDC_CPU,button,1342242819
Control11=IDC_STATIC,button,1342177287
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_V1,edit,1350631552
Control18=IDC_V2,edit,1350631552
Control19=IDC_V3,edit,1350631552
Control20=IDC_V4,edit,1350631552
Control21=IDC_V5,edit,1350631552
Control22=IDC_C1,static,1342177287
Control23=IDC_C2,static,1342177287
Control24=IDC_C3,static,1342177287
Control25=IDC_C4,static,1342177287
Control26=IDC_C5,static,1342177287
Control27=IDC_CC1,button,1342242816
Control28=IDC_CC2,button,1342242816
Control29=IDC_CC3,button,1342242816
Control30=IDC_CC4,button,1342242816
Control31=IDC_CC5,button,1342242816
Control32=IDC_DEMOCOLOR,static,1342177287
Control33=IDC_DEFAULTCOLOR,button,1342242816
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,button,1342177287
Control37=IDC_CNAME,combobox,1344339970
Control38=IDC_SYSCOLOR,static,1342177287
Control39=IDC_MODISC,button,1342242816
Control40=IDC_ARROWP,edit,1350631552
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_ARROWQ,edit,1350631552
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342308352
Control46=IDC_VPPE,edit,1350631552
Control47=IDC_STATIC,static,1342308352
Control48=IDC_STATIC,static,1342308352
Control49=IDC_ARROWI,edit,1350631552
Control50=IDC_STATIC,static,1342308352
Control51=IDC_STATIC,static,1342308352
Control52=IDC_STATIC,static,1342308352
Control53=IDC_SENCTYPE,combobox,1344339970
Control54=IDC_SENCOLOR,static,1342177287
Control55=IDC_MODISC2,button,1342242816
Control56=IDC_STATIC,static,1342308352
Control57=IDC_GEN3DMINP,edit,1350631552
Control58=IDC_STATIC,static,1342308352

[DLG:IDD_LAYERDLG]
Type=1
Class=CLayerDlg
ControlCount=3
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,SysListView32,1350664965

[DLG:IDD_LOGIN]
Type=1
Class=LoginDlg
ControlCount=8
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177283
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_PASSWORD,edit,1350631584
Control7=IDC_USERNAME,combobox,1344340226
Control8=IDC_SAVEUSRPW,button,1342242819

[DLG:IDD_NVGDLG]
Type=1
Class=NavgDlg
ControlCount=0

[DLG:IDD_PRTDLG]
Type=1
Class=prtmode
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342177283
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_COMBO1,combobox,1344339970
Control7=IDC_COMBO2,combobox,1344339970

[DLG:IDD_SECTFLOW]
Type=1
Class=StFlwDlg
ControlCount=18
Control1=IDC_NAME,edit,1350631552
Control2=IDC_ADD,button,1342242816
Control3=IDC_LIST1,listbox,1352728833
Control4=IDC_SECT2,static,1342308352
Control5=IDC_SECT1,static,1342308352
Control6=IDC_SECT3,button,1342177287
Control7=IDC_STATIC,static,1342308352
Control8=IDC_DELETE,button,1342242816
Control9=IDOK,button,1342242816
Control10=IDCANCEL,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_MAXP,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_MAXP1,edit,1350631552
Control18=IDC_MODIP,button,1342242816

[DLG:IDD_SENDLG]
Type=1
Class=SenDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_SENTYPE,static,1342308352
Control4=IDC_DEV,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_PROGRESS1,msctls_progress32,1350565888

[DLG:IDD_VIEWDEV]
Type=1
Class=CViewDev
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_LIST1,SysListView32,1350664193

[MNU:IDR_RMENU]
Type=1
Class=ScadaWin
Command1=IDC_VIEWDEV
Command2=IDC_SVOPT
Command3=IDC_N12EFT
Command4=IDC_N12EFT3D
Command5=IDC_GENMSG
Command6=IDC_TRANMSG
CommandCount=6

[CLS:HisToolbar]
Type=0
HeaderFile=HisToolbar.h
ImplementationFile=HisToolbar.cpp
BaseClass=CToolBar
Filter=W
LastObject=AFX_ID_PREVIEW_NEXT

[CLS:ScadaBar]
Type=0
HeaderFile=ScadaBar.h
ImplementationFile=ScadaBar.cpp
BaseClass=CToolBar
Filter=W
LastObject=ScadaBar

[CLS:LoginDlg]
Type=0
HeaderFile=LoginDlg.h
ImplementationFile=LoginDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_USERNAME

[CLS:ScadaWin]
Type=0
HeaderFile=ScadaWin.h
ImplementationFile=ScadaWin.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=IDC_LOWZOOM

[CLS:CSysVBar]
Type=0
HeaderFile=SysVBar.h
ImplementationFile=SysVBar.cpp
BaseClass=CWnd
Filter=W
LastObject=AFX_ID_PREVIEW_NEXT
VirtualFilter=WC

[CLS:NavgDlg]
Type=0
HeaderFile=NavgDlg.h
ImplementationFile=NavgDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=NavgDlg
VirtualFilter=dWC

[CLS:DgxCrDlg]
Type=0
HeaderFile=DgxCrDlg.h
ImplementationFile=DgxCrDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=DgxCrDlg
VirtualFilter=dWC

[CLS:MyTips]
Type=0
HeaderFile=MyTips.h
ImplementationFile=MyTips.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=MyTips

[CLS:CLayerDlg]
Type=0
HeaderFile=LayerDlg.h
ImplementationFile=LayerDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CLayerDlg
VirtualFilter=dWC

[CLS:CCfgShow]
Type=0
HeaderFile=CfgShow.h
ImplementationFile=CfgShow.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_MODISC

[CLS:StFlwDlg]
Type=0
HeaderFile=StFlwDlg.h
ImplementationFile=StFlwDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_MODIP

[CLS:prtmode]
Type=0
HeaderFile=prtmode.h
ImplementationFile=prtmode.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=ID_APP_ABOUT

[CLS:SenDlg]
Type=0
HeaderFile=SenDlg.h
ImplementationFile=SenDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=SenDlg

[CLS:CViewDev]
Type=0
HeaderFile=ViewDev.h
ImplementationFile=ViewDev.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=CViewDev

[DLG:IDD_OPENPW0]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342308352
Control2=IDC_PAGE,combobox,1344339970
Control3=IDC_STATIC,static,1342308352
Control4=IDC_PNO,edit,1342244992

[CLS:OpenPw0]
Type=0
HeaderFile=OpenPw0.h
ImplementationFile=OpenPw0.cpp
BaseClass=CFileDialog
Filter=D
LastObject=OpenPw0

[MNU:IDR_FMENU]
Type=1
Class=?
Command1=ID_NOFULLSCR
Command2=ID_NORMAL
Command3=ID_ROTATE
Command4=ID_ZOOMIO
Command5=ID_MOVEPIC
Command6=IDC_SHOWDGX
Command7=IDC_BASFLOW
Command8=IDC_GENREV
Command9=IDC_GENREVQ
Command10=IDC_TRANREV
Command11=IDC_BYQWD
Command12=IDC_MAINPAGE
CommandCount=12

[CLS:Lowfwin]
Type=0
HeaderFile=Lowfwin.h
ImplementationFile=Lowfwin.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=AFX_ID_PREVIEW_NEXT

[TB:IDR_DMBAR]
Type=1
Class=?
Command1=IDC_SECTFLW
Command2=IDC_SECTDF
Command3=IDC_SHOWSTF
CommandCount=3

[TB:IDR_SENBAR]
Type=1
Class=?
Command1=IDC_LINESEN
Command2=IDC_BUSSEN
CommandCount=2

[TB:IDR_LOWFBAR]
Type=1
Class=?
Command1=IDC_CTLFRE
Command2=AFX_ID_PREVIEW_NEXT
CommandCount=2

[MNU:IDR_DGXMENU]
Type=1
Class=?
Command1=IDC_DGXBUS
Command2=IDC_DGXBUSHI
Command3=IDC_DGXBUSLO
Command4=IDC_LINELOAD
Command5=IDC_TRANLOAD
CommandCount=5

[MNU:IDR_FLOWMENU]
Type=1
Class=?
Command1=IDC_NOFLOW
Command2=IDC_FLOWP
Command3=IDC_FLOWQ
Command4=IDC_FLOWPQ
CommandCount=4

[DLG:IDD_CFGHIS]
Type=1
Class=SetHisDlg
ControlCount=17
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_DATE1,SysDateTimePick32,1342242852
Control5=IDC_STATIC,static,1342308352
Control6=IDC_DATE2,SysDateTimePick32,1342242852
Control7=IDC_TIME1,SysDateTimePick32,1342242857
Control8=IDC_TIME2,SysDateTimePick32,1342242857
Control9=IDC_STATIC,button,1342177287
Control10=IDC_GETHISLIST,button,1342242816
Control11=IDC_STATIC,static,1342308352
Control12=IDC_DMSUM,edit,1350641792
Control13=IDC_STATIC,static,1342308352
Control14=IDC_SPEED,edit,1350631552
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,button,1342177287

[CLS:SetHisDlg]
Type=0
HeaderFile=SetHisDlg.h
ImplementationFile=SetHisDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AFX_ID_PREVIEW_NEXT

[MNU:IDR_AMENU]
Type=1
Class=?
Command1=IDC_SHOWLST
Command2=IDC_PUSHPIC
CommandCount=2

[TB:IDB_BITMAP1]
Type=1
Class=?
Command1=ID_BUTTON32882
Command2=ID_BUTTON32883
Command3=ID_BUTTON32884
Command4=ID_BUTTON32885
Command5=ID_BUTTON32886
Command6=ID_BUTTON32887
Command7=ID_BUTTON32888
Command8=ID_BUTTON32889
Command9=ID_BUTTON32890
Command10=ID_BUTTON32891
Command11=ID_BUTTON32892
Command12=ID_BUTTON32893
Command13=ID_BUTTON32894
Command14=ID_BUTTON32895
CommandCount=14

[DLG:IDD_ALARMDLG]
Type=1
Class=?
ControlCount=0

[DLG:IDD_DMDLG]
Type=1
Class=DmJsDlg
ControlCount=0

[CLS:DmJsDlg]
Type=0
HeaderFile=DmJsDlg.h
ImplementationFile=DmJsDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=AFX_ID_PREVIEW_NEXT

[DLG:IDD_TABLEDLG]
Type=1
Class=GzTblDlg
ControlCount=2
Control1=IDC_LIST1,SysListView32,1350631429
Control2=IDC_SOUND,button,1342242819

[CLS:GzTblDlg]
Type=0
HeaderFile=GzTblDlg.h
ImplementationFile=GzTblDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=GzTblDlg

[MNU:IDR_TABLEMENU]
Type=1
Class=?
Command1=IDC_CHECKALL
Command2=IDC_UNCHECKALL
Command3=IDC_RELOAD
Command4=IDC_SHOWALL
Command5=IDC_SHOWALM
CommandCount=5

[DLG:IDD_PRECFGDLG]
Type=1
Class=CCfgAlmDlg
ControlCount=26
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_LIST1,listbox,1352728833
Control4=IDC_SOUND,button,1342242819
Control5=IDC_POP,button,1342242819
Control6=IDC_FLASH,button,1342242819
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,button,1342177287
Control9=IDC_STATIC,static,1342308352
Control10=IDC_GEN,edit,1350631552
Control11=IDC_STATIC,static,1342308352
Control12=IDC_STATIC,static,1342308352
Control13=IDC_LINE,edit,1350631552
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_DCLINE,edit,1350631552
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_TFM1,edit,1350631552
Control20=IDC_STATIC,static,1342308352
Control21=IDC_STATIC,static,1342308352
Control22=IDC_TFM2,edit,1350631552
Control23=IDC_STATIC,static,1342308352
Control24=IDC_STATIC,static,1342308352
Control25=IDC_DM,edit,1350631552
Control26=IDC_STATIC,static,1342308352

[CLS:CCfgAlmDlg]
Type=0
HeaderFile=CfgAlmDlg.h
ImplementationFile=CfgAlmDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_SVOPT

[CLS:MsAlmWin]
Type=0
HeaderFile=MsAlmWin.h
ImplementationFile=MsAlmWin.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=MsAlmWin

[CLS:MenuWin]
Type=0
HeaderFile=MenuWin.h
ImplementationFile=MenuWin.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=MenuWin

[TB:IDR_CTLBAR]
Type=1
Class=?
Command1=ID_PAGEUP
Command2=ID_LEFT
Command3=ID_RIGHT
Command4=ID_PAGEDOWN
Command5=IDC_DELCHILD
CommandCount=5

[CLS:pagectl]
Type=0
HeaderFile=pagectl.h
ImplementationFile=pagectl.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=IDC_DELCHILD

[CLS:CChildFrm]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CChildFrm

[CLS:CNavWin]
Type=0
HeaderFile=NavWin.h
ImplementationFile=NavWin.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CNavWin

[CLS:CChrgWin]
Type=0
HeaderFile=ChrgWin.h
ImplementationFile=ChrgWin.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC
LastObject=CChrgWin

[TB:IDR_SWSOEBAR]
Type=1
Class=?
Command1=IDC_GETNEWSOE
Command2=ID_SOEGOTOTOP
Command3=IDC_PLAYSOE
Command4=IDC_PAUSESOE
Command5=IDC_SOEMSG
CommandCount=5

[DLG:IDD_SOEDLG]
Type=1
Class=SoeSelDlg
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_DATE1,SysDateTimePick32,1342242853
Control6=IDC_TIME1,SysDateTimePick32,1342242857
Control7=IDC_DATE2,SysDateTimePick32,1342242853
Control8=IDC_TIME2,SysDateTimePick32,1342242857
Control9=IDC_GETSELSOE,button,1342242816
Control10=IDC_STATIC,static,1342308352
Control11=IDC_NUM,edit,1350641792

[CLS:SoeSelDlg]
Type=0
HeaderFile=SoeSelDlg.h
ImplementationFile=SoeSelDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_GETSELSOE

[CLS:SoePlayBar]
Type=0
HeaderFile=SoePlayBar.h
ImplementationFile=SoePlayBar.cpp
BaseClass=CToolBarCtrl
Filter=W
VirtualFilter=YWC
LastObject=SoePlayBar

[DLG:IDD_GDDLG]
Type=1
Class=YbGdDlg
ControlCount=0

[CLS:YbGdDlg]
Type=0
HeaderFile=YbGdDlg.h
ImplementationFile=YbGdDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=YbGdDlg

[TB:IDR_MDLBAR]
Type=1
Class=?
Command1=IDC_MSELLINE
CommandCount=1

[TB:IDR_FUNBAR]
Type=1
Class=?
Command1=ID_BTNRETURN
Command2=ID_SHOWFUNCTION
CommandCount=2

[CLS:FunToolBar]
Type=0
HeaderFile=FunToolBar.h
ImplementationFile=FunToolBar.cpp
BaseClass=CToolBar
Filter=W
LastObject=FunToolBar

[DLG:IDD_DIALOG_CFGTRA]
Type=1
Class=CConfigTrans
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_RADIO_TYPE,button,1342177289
Control4=IDC_RADIO_TYPE2,button,1342177289
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_STATIC,button,1342177287
Control8=IDC_LIST_HIDE,listbox,1352728835
Control9=IDC_LIST_SHOW,listbox,1352728835
Control10=IDC_BUTTON_DEL,button,1342242816
Control11=IDC_BUTTON_ADD,button,1342242816

[CLS:CConfigTrans]
Type=0
HeaderFile=ConfigTrans.h
ImplementationFile=ConfigTrans.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDOK

[MNU:IDR_PLATEMENU]
Type=1
Class=?
Command1=IDC_NO_PLATE
Command2=IDC_SHOWJX_PLATE
CommandCount=2

