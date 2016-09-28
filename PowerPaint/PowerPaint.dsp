# Microsoft Developer Studio Project File - Name="PowerPaint" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=PowerPaint - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "PowerPaint.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "PowerPaint.mak" CFG="PowerPaint - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "PowerPaint - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "PowerPaint - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "PowerPaint - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\"
# PROP Intermediate_Dir "..\tmppowerpaint"
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
# ADD LINK32 SvgImp.lib jhsyslibl.lib seldev.lib readdata.lib NT_DEVICE.lib jpeglib2.lib AVCProperty.lib cimread.lib FindIDTODevInfo.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"libc.lib" /nodefaultlib:"libcmt.lib" /nodefaultlib:"libcd.lib" /nodefaultlib:"libcmtd.lib" /nodefaultlib:"msvcrtd.lib" /out:"E:\wangdi\四川电压无功\bin_avc\VisualPaint.exe" /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none /nodefaultlib

!ELSEIF  "$(CFG)" == "PowerPaint - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_AFXDLL" /D "_MBCS" /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 SvgImp.lib jhsyslibl.lib seldev.lib readdata.lib NT_DEVICE.lib jpeglib2.lib AVCProperty.lib cimread.lib FindIDTODevInfo.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"libcmt.lib" /nodefaultlib:"libc.lib" /out:"E:\wangdi\四川电压无功\bin_avc\VisualPaint.exe" /pdbtype:sept /libpath:"..\lib"
# SUBTRACT LINK32 /nodefaultlib

!ENDIF 

# Begin Target

# Name "PowerPaint - Win32 Release"
# Name "PowerPaint - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\Base0.cpp
# End Source File
# Begin Source File

SOURCE=.\bclass.cpp
# End Source File
# Begin Source File

SOURCE=.\BFCfgDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\canvas.cpp
# End Source File
# Begin Source File

SOURCE=.\CfgCRDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CfgMeter.cpp
# End Source File
# Begin Source File

SOURCE=.\CfgZmDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\CheckSvgType.cpp
# End Source File
# Begin Source File

SOURCE=.\CloseWin.cpp
# End Source File
# Begin Source File

SOURCE=.\COMOBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\EDITCTL.CPP
# End Source File
# Begin Source File

SOURCE=.\EDITOBJ.CPP
# End Source File
# Begin Source File

SOURCE=.\egatrdlg.cpp
# End Source File
# Begin Source File

SOURCE=.\egpwin.cpp
# End Source File
# Begin Source File

SOURCE=.\FileV30.cpp
# End Source File
# Begin Source File

SOURCE=.\gdata.cpp
# End Source File
# Begin Source File

SOURCE=.\GetIdDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\GetNMDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\guiddlg.cpp
# End Source File
# Begin Source File

SOURCE=.\imgopen.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ImportSvg.cpp
# End Source File
# Begin Source File

SOURCE=.\keyword.cpp
# End Source File
# Begin Source File

SOURCE=.\layerwin.cpp
# End Source File
# Begin Source File

SOURCE=.\LITEMCTL.CPP
# End Source File
# Begin Source File

SOURCE=.\MainFrm.cpp
# End Source File
# Begin Source File

SOURCE=.\MainWin.cpp
# End Source File
# Begin Source File

SOURCE=.\NaviWin.cpp
# End Source File
# Begin Source File

SOURCE=.\OBJWIN.CPP
# End Source File
# Begin Source File

SOURCE=.\OpenPw0.cpp
# End Source File
# Begin Source File

SOURCE=.\pagectl.cpp
# End Source File
# Begin Source File

SOURCE=.\PatrDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\PowerPaint.cpp
# End Source File
# Begin Source File

SOURCE=.\PowerPaint.rc
# End Source File
# Begin Source File

SOURCE=.\PrtMode.cpp
# End Source File
# Begin Source File

SOURCE=.\ScrTDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelEDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelVLev.cpp
# End Source File
# Begin Source File

SOURCE=.\shockwaveflash.cpp
# End Source File
# Begin Source File

SOURCE=.\spiwin.cpp
# End Source File
# Begin Source File

SOURCE=.\SPLITASS.CPP
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\StrField.cpp
# End Source File
# Begin Source File

SOURCE=.\SvgOut.cpp
# End Source File
# Begin Source File

SOURCE=.\TestWin.cpp
# End Source File
# Begin Source File

SOURCE=.\TextDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\textstr.cpp
# End Source File
# Begin Source File

SOURCE=.\tlswin.cpp
# End Source File
# Begin Source File

SOURCE=.\TypeWin.cpp
# End Source File
# Begin Source File

SOURCE=.\undoop.cpp
# End Source File
# Begin Source File

SOURCE=.\workwin.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\Base0.h
# End Source File
# Begin Source File

SOURCE=.\bclass.h
# End Source File
# Begin Source File

SOURCE=.\BFCfgDlg.h
# End Source File
# Begin Source File

SOURCE=.\canvas.h
# End Source File
# Begin Source File

SOURCE=.\CfgCRDlg.h
# End Source File
# Begin Source File

SOURCE=.\CfgMeter.h
# End Source File
# Begin Source File

SOURCE=.\CfgZmDlg.h
# End Source File
# Begin Source File

SOURCE=.\CheckSvgType.h
# End Source File
# Begin Source File

SOURCE=.\CloseWin.h
# End Source File
# Begin Source File

SOURCE=.\COMOBJ.H
# End Source File
# Begin Source File

SOURCE=.\defv30.h
# End Source File
# Begin Source File

SOURCE=.\EDITCTL.H
# End Source File
# Begin Source File

SOURCE=.\EDITOBJ.H
# End Source File
# Begin Source File

SOURCE=.\egatrdlg.h
# End Source File
# Begin Source File

SOURCE=.\egpwin.h
# End Source File
# Begin Source File

SOURCE=.\FileV30.h
# End Source File
# Begin Source File

SOURCE=.\gdata.h
# End Source File
# Begin Source File

SOURCE=.\GetIdDlg.h
# End Source File
# Begin Source File

SOURCE=.\GetNMDlg.h
# End Source File
# Begin Source File

SOURCE=.\guiddlg.h
# End Source File
# Begin Source File

SOURCE=.\imgopen.h
# End Source File
# Begin Source File

SOURCE=.\ImportDlg.h
# End Source File
# Begin Source File

SOURCE=.\ImportSvg.h
# End Source File
# Begin Source File

SOURCE=..\include\jhsyslibL.h
# End Source File
# Begin Source File

SOURCE=.\layerwin.h
# End Source File
# Begin Source File

SOURCE=.\LITEMCTL.H
# End Source File
# Begin Source File

SOURCE=.\MainFrm.h
# End Source File
# Begin Source File

SOURCE=.\MainWin.h
# End Source File
# Begin Source File

SOURCE=.\middll.h
# End Source File
# Begin Source File

SOURCE=.\NaviWin.h
# End Source File
# Begin Source File

SOURCE=.\OBJWIN.H
# End Source File
# Begin Source File

SOURCE=.\OpenPw0.h
# End Source File
# Begin Source File

SOURCE=.\pagectl.h
# End Source File
# Begin Source File

SOURCE=.\PatrDlg.h
# End Source File
# Begin Source File

SOURCE=.\PowerPaint.h
# End Source File
# Begin Source File

SOURCE=.\PrtMode.h
# End Source File
# Begin Source File

SOURCE=.\ptdefine.H
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\ScrTDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelEDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelVLev.h
# End Source File
# Begin Source File

SOURCE=.\shockwaveflash.h
# End Source File
# Begin Source File

SOURCE=.\spiwin.h
# End Source File
# Begin Source File

SOURCE=.\SPLITASS.H
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\StrField.h
# End Source File
# Begin Source File

SOURCE=.\SvgOut.h
# End Source File
# Begin Source File

SOURCE=.\TestWin.h
# End Source File
# Begin Source File

SOURCE=.\TextDlg.h
# End Source File
# Begin Source File

SOURCE=.\tlswin.h
# End Source File
# Begin Source File

SOURCE=.\TypeWin.h
# End Source File
# Begin Source File

SOURCE=.\undoop.h
# End Source File
# Begin Source File

SOURCE=.\workwin.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\ARW07LT.ICO
# End Source File
# Begin Source File

SOURCE=.\res\ARW07RT.ICO
# End Source File
# Begin Source File

SOURCE=.\res\basetl.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00001.bmp
# End Source File
# Begin Source File

SOURCE=.\res\bmp00002.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cd.bmp
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR1.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR10.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR11.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR12.CUR
# End Source File
# Begin Source File

SOURCE=.\res\cursor13.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR14.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR15.cur
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR16.cur
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR17.cur
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

SOURCE=.\res\CURSOR5.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR6.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR7.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR8.CUR
# End Source File
# Begin Source File

SOURCE=.\res\CURSOR9.CUR
# End Source File
# Begin Source File

SOURCE=.\res\gs.ICO
# End Source File
# Begin Source File

SOURCE=.\res\ICLBuild.ico
# End Source File
# Begin Source File

SOURCE=.\res\OTHBMP.BMP
# End Source File
# Begin Source File

SOURCE=.\res\PowerPaint.ico
# End Source File
# Begin Source File

SOURCE=.\res\PowerPaint.rc2
# End Source File
# Begin Source File

SOURCE=.\res\print.bmp
# End Source File
# Begin Source File

SOURCE=.\res\pt.bmp
# End Source File
# Begin Source File

SOURCE=.\res\TBITMAP.BMP
# End Source File
# Begin Source File

SOURCE=.\res\Toolbar.bmp
# End Source File
# Begin Source File

SOURCE=.\res\toolbar1.bmp
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
