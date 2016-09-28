# Microsoft Developer Studio Project File - Name="seldev" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=seldev - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "seldev.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "seldev.mak" CFG="seldev - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "seldev - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "seldev - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "seldev - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "..\"
# PROP Intermediate_Dir "..\tmp"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /Zp1 /MD /W3 /GX /O2 /I "..\include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "_WINDLL" /D "_AFXDLL" /FR /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 dbapi.lib /nologo /subsystem:windows /dll /machine:I386 /out:"F:\广东无功\bin\seldev.dll" /implib:"..\lib\seldev.lib" /libpath:"..\lib"
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "seldev - Win32 Debug"

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
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /Zp1 /MDd /W3 /Gm /GX /ZI /Od /I "..\include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_USRDLL" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 dbapi.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"E:\wangdi\四川电压无功\bin_avc\seldev.dll" /pdbtype:sept /libpath:"..\lib"

!ENDIF 

# Begin Target

# Name "seldev - Win32 Release"
# Name "seldev - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AlmDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DefdmDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\DevGet.cpp
# End Source File
# Begin Source File

SOURCE=.\PySel.cpp
# End Source File
# Begin Source File

SOURCE=.\SelAnlDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\seldev.cpp
# End Source File
# Begin Source File

SOURCE=.\seldev.def
# End Source File
# Begin Source File

SOURCE=.\seldev.rc
# End Source File
# Begin Source File

SOURCE=.\SelDVDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SelPie.cpp
# End Source File
# Begin Source File

SOURCE=.\SelRevDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\SglVDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StaDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StationDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# Begin Source File

SOURCE=.\SZoneDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\YbSelDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneDlg.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AlmDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\dbapi.h
# End Source File
# Begin Source File

SOURCE=.\DefdmDlg.h
# End Source File
# Begin Source File

SOURCE=.\mstruct.h
# End Source File
# Begin Source File

SOURCE=.\PySel.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SelAnlDlg.h
# End Source File
# Begin Source File

SOURCE=.\seldev.h
# End Source File
# Begin Source File

SOURCE=.\SelDVDlg.h
# End Source File
# Begin Source File

SOURCE=.\SelPie.h
# End Source File
# Begin Source File

SOURCE=.\SelRevDlg.h
# End Source File
# Begin Source File

SOURCE=.\SglVDlg.h
# End Source File
# Begin Source File

SOURCE=.\StaDlg.h
# End Source File
# Begin Source File

SOURCE=.\StationDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# Begin Source File

SOURCE=.\SZoneDlg.h
# End Source File
# Begin Source File

SOURCE=..\include\USERAPI.H
# End Source File
# Begin Source File

SOURCE=..\include\visualdb.h
# End Source File
# Begin Source File

SOURCE=.\YbSelDlg.h
# End Source File
# Begin Source File

SOURCE=.\ZoneDlg.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\0096.ICO
# End Source File
# Begin Source File

SOURCE=.\res\door.ICO
# End Source File
# Begin Source File

SOURCE=.\res\Edit.ico
# End Source File
# Begin Source File

SOURCE=.\res\seldev.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
