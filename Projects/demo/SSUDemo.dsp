# Microsoft Developer Studio Project File - Name="SSUDemo" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=SSUDemo - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "SSUDemo.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "SSUDemo.mak" CFG="SSUDemo - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "SSUDemo - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "SSUDemo - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "SSUDemo - Win32 Release"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "../Release"
# PROP Intermediate_Dir "../tmp/Release/demo"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# ADD LINK32 ../release/SSUApi.lib /nologo /subsystem:windows /machine:I386

!ELSEIF  "$(CFG)" == "SSUDemo - Win32 Debug"

# PROP BASE Use_MFC 5
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "../Debug"
# PROP Intermediate_Dir "../tmp/Debug/demo"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /FR /Yu"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 ../Debug/SSUApi.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "SSUDemo - Win32 Release"
# Name "SSUDemo - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\MsgBoxOk.cpp
# End Source File
# Begin Source File

SOURCE=.\MsgBoxOkCancel.cpp
# End Source File
# Begin Source File

SOURCE=.\PageConfig.cpp
# End Source File
# Begin Source File

SOURCE=.\PageNetAddrRS485.cpp
# End Source File
# Begin Source File

SOURCE=.\PageNetAddrTCPIP.cpp
# End Source File
# Begin Source File

SOURCE=.\PageNodeExplore.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTagAccess.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTagAccessEx.cpp
# End Source File
# Begin Source File

SOURCE=.\PageTagInventory.cpp
# End Source File
# Begin Source File

SOURCE=.\PaneNodeRS485.cpp
# End Source File
# Begin Source File

SOURCE=.\PaneNodeTCPIP.cpp
# End Source File
# Begin Source File

SOURCE=.\SSUDemo.cpp
# End Source File
# Begin Source File

SOURCE=.\SSUDemo.rc
# End Source File
# Begin Source File

SOURCE=.\SSUDemoDlg.cpp
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\MsgBoxOk.h
# End Source File
# Begin Source File

SOURCE=.\MsgBoxOkCancel.h
# End Source File
# Begin Source File

SOURCE=.\PageConfig.h
# End Source File
# Begin Source File

SOURCE=.\PageNetAddrRS485.h
# End Source File
# Begin Source File

SOURCE=.\PageNetAddrTCPIP.h
# End Source File
# Begin Source File

SOURCE=.\PageNodeExplore.h
# End Source File
# Begin Source File

SOURCE=.\PageTagAccess.h
# End Source File
# Begin Source File

SOURCE=.\PageTagAccessEx.h
# End Source File
# Begin Source File

SOURCE=.\PageTagInventory.h
# End Source File
# Begin Source File

SOURCE=.\PaneNodeRS485.h
# End Source File
# Begin Source File

SOURCE=.\PaneNodeTCPIP.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\SSUDemo.h
# End Source File
# Begin Source File

SOURCE=.\SSUDemoDlg.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\SSUDemo.ico
# End Source File
# Begin Source File

SOURCE=.\res\SSUDemo.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
