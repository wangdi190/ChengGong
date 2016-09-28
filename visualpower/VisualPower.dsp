# Microsoft Developer Studio Project File - Name="VisualPower" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=VisualPower - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "VisualPower.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "VisualPower.mak" CFG="VisualPower - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "VisualPower - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "VisualPower - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "VisualPower - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\"
# PROP Intermediate_Dir "..\tmpvisualpower"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 jhsyslibl.lib jpeglib2.lib cuserapi.lib ws2_32.lib dbapi.lib winmm.lib EarthClient.lib VisHisSOE.lib DynMonitorCli.lib scswitch.lib HisProvider.lib BJ_SCFileDLL.lib SecImport.lib EstDemo.lib psapi.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrtd.lib" /out:"E:\wangdi\四川电压无功\bin_avc\VisualPower.exe" /libpath:"..\lib"
# SUBTRACT LINK32 /nodefaultlib

!ELSEIF  "$(CFG)" == "VisualPower - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\visualsys"
# PROP Intermediate_Dir "..\tmp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /MTd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 jhsyslibl.lib jpeglib2.lib cuserapi.lib ws2_32.lib dbapi.lib winmm.lib EarthClient.lib VisHisSOE.lib DynMonitorCli.lib scswitch.lib HisProvider.lib BJ_SCFileDLL.lib SecImport.lib EstDemo.lib psapi.lib /nologo /subsystem:windows /debug /machine:I386 /out:"E:\wangdi\四川电压无功\bin_avc\VisualPower.exe" /pdbtype:sept /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none

!ENDIF 

# Begin Target

# Name "VisualPower - Win32 Release"
# Name "VisualPower - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\bclass.cpp
# End Source File
# Begin Source File

SOURCE=.\BObj.cpp
# End Source File
# Begin Source File

SOURCE=.\CfgAlmDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CfgShow.cpp
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\ChrgWin.cpp
# End Source File
# Begin Source File

SOURCE=.\Clisock.cpp
# End Source File
# Begin Source File

SOURCE=.\COMOBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\ConfigTrans.cpp
# End Source File
# Begin Source File

SOURCE=.\CrossObj.cpp
# End Source File
# Begin Source File

SOURCE=.\dbedit.cpp
# End Source File
# Begin Source File

SOURCE=.\DmJsDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DObj.cpp
# End Source File
# Begin Source File

SOURCE=.\FileV30.cpp
# End Source File
# Begin Source File

SOURCE=.\FunToolBar.cpp
# End Source File
# Begin Source File

SOURCE=.\gdata.cpp
# End Source File
# Begin Source File

SOURCE=.\GzTblDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\HisToolbar.cpp
# End Source File
# Begin Source File

SOURCE=.\LayerDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\Lowfwin.cpp
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainWin.cpp
# End Source File
# Begin Source File

SOURCE=.\MenuWin.cpp
# End Source File
# Begin Source File

SOURCE=.\MsAlmWin.cpp
# End Source File
# Begin Source File

SOURCE=.\MyTips.cpp
# End Source File
# Begin Source File

SOURCE=.\NavWin.cpp
# End Source File
# Begin Source File

SOURCE=.\NetTpy.cpp
# End Source File
# Begin Source File

SOURCE=.\OpenPw0.cpp
# End Source File
# Begin Source File

SOURCE=.\pagectl.cpp
# End Source File
# Begin Source File

SOURCE=.\Processe.cpp
# End Source File
# Begin Source File

SOURCE=.\prtmode.cpp
# End Source File
# Begin Source File

SOURCE=.\ReadRltD.cpp
# End Source File
# Begin Source File

SOURCE=.\ScadaWin.cpp
# End Source File
# Begin Source File

SOURCE=.\ScadaWin1.cpp
# End Source File
# Begin Source File

SOURCE=.\SenDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SetHisDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\shockwaveflash.cpp
# End Source File
# Begin Source File

SOURCE=.\SoePlayBar.cpp
# End Source File
# Begin Source File

SOURCE=.\SoeSelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StFlwDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\textstr.cpp
# End Source File
# Begin Source File

SOURCE=.\ViewDev.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPower.cpp
# End Source File
# Begin Source File

SOURCE=.\VisualPower.rc
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\bclass.h
# End Source File
# Begin Source File

SOURCE=.\CfgAlmDlg.h
# End Source File
# Begin Source File

SOURCE=.\CfgShow.h
# End Source File
# Begin Source File

SOURCE=.\ChildFrm.h
# End Source File
# Begin Source File

SOURCE=.\ChrgWin.h
# End Source File
# Begin Source File

SOURCE=.\Clisock.h
# End Source File
# Begin Source File

SOURCE=.\COMOBJ.H
# End Source File
# Begin Source File

SOURCE=.\ConfigTrans.h
# End Source File
# Begin Source File

SOURCE=.\CrossObj.h
# End Source File
# Begin Source File

SOURCE=..\include\dbapi.h
# End Source File
# Begin Source File

SOURCE=.\dbedit.h
# End Source File
# Begin Source File

SOURCE=.\defv30.h
# End Source File
# Begin Source File

SOURCE=.\DmJsDlg.h
# End Source File
# Begin Source File

SOURCE=.\DObj.h
# End Source File
# Begin Source File

SOURCE=.\FileV30.h
# End Source File
# Begin Source File

SOURCE=.\FunToolBar.h
# End Source File
# Begin Source File

SOURCE=.\gdata.h
# End Source File
# Begin Source File

SOURCE=.\GzTblDlg.h
# End Source File
# Begin Source File

SOURCE=.\HisToolbar.h
# End Source File
# Begin Source File

SOURCE=..\include\jhsyslibL.h
# End Source File
# Begin Source File

SOURCE=.\LayerDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\LIB.H
# End Source File
# Begin Source File

SOURCE=.\LoginDlg.h
# End Source File
# Begin Source File

SOURCE=.\Lowfwin.h
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainWin.h
# End Source File
# Begin Source File

SOURCE=.\MenuWin.h
# End Source File
# Begin Source File

SOURCE=.\middll.h
# End Source File
# Begin Source File

SOURCE=.\MsAlmWin.h
# End Source File
# Begin Source File

SOURCE=.\MyTips.h
# End Source File
# Begin Source File

SOURCE=.\NavWin.h
# End Source File
# Begin Source File

SOURCE=.\NetTpy.h
# End Source File
# Begin Source File

SOURCE=.\OpenPw0.h
# End Source File
# Begin Source File

SOURCE=.\pagectl.h
# End Source File
# Begin Source File

SOURCE=.\Processe.h
# End Source File
# Begin Source File

SOURCE=.\prtmode.h
# End Source File
# Begin Source File

SOURCE=.\PWPTDEF.H
# End Source File
# Begin Source File

SOURCE=.\ReadRltD.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScadaWin.h
# End Source File
# Begin Source File

SOURCE=.\SenDlg.h
# End Source File
# Begin Source File

SOURCE=.\SetHisDlg.h
# End Source File
# Begin Source File

SOURCE=.\shockwaveflash.h
# End Source File
# Begin Source File

SOURCE=.\SoePlayBar.h
# End Source File
# Begin Source File

SOURCE=.\SoeSelDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StFlwDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\USERAPI.H
# End Source File
# Begin Source File

SOURCE=.\ViewDev.h
# End Source File
# Begin Source File

SOURCE=.\VisualPower.h
# End Source File
# Begin Source File

SOURCE=.\webbrowser2.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\alarm.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bitmap3.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00003.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00004.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00005.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00006.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00007.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR1.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR10.cur
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR11.cur
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR2.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR3.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR4.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR5.cur
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR6.cur
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR7.cur
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR8.cur
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR9.cur
# End Source File
# Begin Source File

SOURCE=.\res\gs.ICO
# End Source File
# Begin Source File

SOURCE=.\res\icon3.ico
# End Source File
# Begin Source File

SOURCE=.\res\NUMBIG.bmp
# End Source File
# Begin Source File

SOURCE=.\res\OTHBMP.BMP
# End Source File
# Begin Source File

SOURCE=.\res\QuickVie.ico
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# Begin Source File

SOURCE=.\res\VisualPower.ico
# End Source File
# Begin Source File

SOURCE=.\res\VisualPower.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
# Section VisualPower : {D30C1661-CDAF-11D0-8A3E-00C04FC9E26E}
# 	2:5:Class:CWebBrowser2
# 	2:10:HeaderFile:webbrowser2.h
# 	2:8:ImplFile:webbrowser2.cpp
# End Section
# Section VisualPower : {8856F961-340A-11D0-A96B-00C04FD705A2}
# 	2:21:DefaultSinkHeaderFile:webbrowser2.h
# 	2:16:DefaultSinkClass:CWebBrowser2
# End Section
