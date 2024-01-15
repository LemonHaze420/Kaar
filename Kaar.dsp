# Microsoft Developer Studio Project File - Name="Kaar" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=Kaar - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Kaar.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Kaar.mak" CFG="Kaar - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Kaar - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "Kaar - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Kaar - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /Gi /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_KERNELVERSION_" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x40c /d "NDEBUG"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib \dev\crswincpp\crswincpp\relkernel\crswinker.lib /nologo /subsystem:windows /machine:I386 /nodefaultlib:"LIBCMTD.LIB LIBCD.LIB"

!ELSEIF  "$(CFG)" == "Kaar - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 1
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /Zi /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /YX /FD /c
# ADD CPP /nologo /MTd /W3 /Gm /Gi /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_DEBUGVERSION_" /D "_KERNELVERSION_" /YX /FD /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /o "NUL" /win32
# ADD BASE RSC /l 0x40c /d "_DEBUG"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ..\crswincpp\debkernel\crswinker.lib /nologo /subsystem:windows /debug /machine:I386 /nodefaultlib:"LIBCMT.LIB LIBC.LIB" /pdbtype:sept
# SUBTRACT LINK32 /incremental:no

!ENDIF 

# Begin Target

# Name "Kaar - Win32 Release"
# Name "Kaar - Win32 Debug"
# Begin Group "Tools"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\List.h
# End Source File
# Begin Source File

SOURCE=.\Ref.h
# End Source File
# End Group
# Begin Group "Game"

# PROP Default_Filter ""
# Begin Group "View"

# PROP Default_Filter ""
# Begin Group "CamView"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Cam.cpp
# End Source File
# Begin Source File

SOURCE=.\Cam.h
# End Source File
# Begin Source File

SOURCE=.\CamView.cpp
# End Source File
# Begin Source File

SOURCE=.\CamView.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\BlocItem.cpp
# End Source File
# Begin Source File

SOURCE=.\BlocItem.h
# End Source File
# Begin Source File

SOURCE=.\BlocView.cpp
# End Source File
# Begin Source File

SOURCE=.\BlocView.h
# End Source File
# Begin Source File

SOURCE=.\CellView.cpp
# End Source File
# Begin Source File

SOURCE=.\CellView.h
# End Source File
# Begin Source File

SOURCE=.\WorldView.cpp
# End Source File
# Begin Source File

SOURCE=.\WorldView.h
# End Source File
# Begin Source File

SOURCE=.\ZoneItem.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneItem.h
# End Source File
# Begin Source File

SOURCE=.\ZoneView.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneView.h
# End Source File
# End Group
# Begin Group "Univers"

# PROP Default_Filter ""
# Begin Group "World"

# PROP Default_Filter ""
# Begin Group "ZoneInst"

# PROP Default_Filter ""
# Begin Group "BlocInst"

# PROP Default_Filter ""
# Begin Group "Cell"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Cell.cpp
# End Source File
# Begin Source File

SOURCE=.\Cell.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\BlocInst.cpp
# End Source File
# Begin Source File

SOURCE=.\BlocInst.h
# End Source File
# End Group
# Begin Group "LandInst"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\LandInst.cpp
# End Source File
# Begin Source File

SOURCE=.\LandInst.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\ZoneInst.cpp
# End Source File
# Begin Source File

SOURCE=.\ZoneInst.h
# End Source File
# End Group
# Begin Group "Character"

# PROP Default_Filter ""
# Begin Group "ModelInst"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ModelInst.cpp
# End Source File
# Begin Source File

SOURCE=.\ModelInst.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Character.cpp
# End Source File
# Begin Source File

SOURCE=.\Character.h
# End Source File
# Begin Source File

SOURCE=.\CharPos.cpp
# End Source File
# Begin Source File

SOURCE=.\CharPos.h
# End Source File
# Begin Source File

SOURCE=.\IA.h
# End Source File
# Begin Source File

SOURCE=.\IAAnimal.cpp
# End Source File
# Begin Source File

SOURCE=.\IAAnimal.h
# End Source File
# Begin Source File

SOURCE=.\IABase.cpp
# End Source File
# Begin Source File

SOURCE=.\IABase.h
# End Source File
# Begin Source File

SOURCE=.\IAGarde.cpp
# End Source File
# Begin Source File

SOURCE=.\IAGarde.h
# End Source File
# Begin Source File

SOURCE=.\IAVolant.cpp
# End Source File
# Begin Source File

SOURCE=.\IAVolant.h
# End Source File
# Begin Source File

SOURCE=.\NPChar.cpp
# End Source File
# Begin Source File

SOURCE=.\NPChar.h
# End Source File
# Begin Source File

SOURCE=.\PChar.cpp
# End Source File
# Begin Source File

SOURCE=.\PChar.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\World.cpp
# End Source File
# Begin Source File

SOURCE=.\World.h
# End Source File
# Begin Source File

SOURCE=.\WorldPos.h
# End Source File
# End Group
# Begin Group "Group"

# PROP Default_Filter ""
# Begin Group "Bloc"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Bloc.cpp
# End Source File
# Begin Source File

SOURCE=.\Bloc.h
# End Source File
# End Group
# Begin Group "Land"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Land.cpp
# End Source File
# Begin Source File

SOURCE=.\Land.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Group.cpp
# End Source File
# Begin Source File

SOURCE=.\Group.h
# End Source File
# End Group
# Begin Group "Zone"

# PROP Default_Filter ""
# Begin Group "Set"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Set.cpp
# End Source File
# Begin Source File

SOURCE=.\Set.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Zone.cpp
# End Source File
# Begin Source File

SOURCE=.\Zone.h
# End Source File
# End Group
# Begin Group "Model"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\crehspsh.h
# End Source File
# Begin Source File

SOURCE=.\crsprha.cpp
# End Source File
# Begin Source File

SOURCE=.\crsprsha.h
# End Source File
# Begin Source File

SOURCE=.\Model.cpp
# End Source File
# Begin Source File

SOURCE=.\Model.h
# End Source File
# End Group
# Begin Group "Path"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Path.cpp
# End Source File
# Begin Source File

SOURCE=.\Path.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Univers.cpp
# End Source File
# Begin Source File

SOURCE=.\Univers.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Game.cpp
# End Source File
# Begin Source File

SOURCE=.\Game.h
# End Source File
# Begin Source File

SOURCE=.\Messager.cpp
# End Source File
# Begin Source File

SOURCE=.\Messager.h
# End Source File
# Begin Source File

SOURCE=.\Player.cpp
# End Source File
# Begin Source File

SOURCE=.\Player.h
# End Source File
# End Group
# Begin Group "System"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\crswincpp\CrsWin.rc
# End Source File
# Begin Source File

SOURCE=.\DrvMgr.cpp
# End Source File
# Begin Source File

SOURCE=.\DrvMgr.h
# End Source File
# Begin Source File

SOURCE=.\MyEvMgr.h
# End Source File
# Begin Source File

SOURCE=.\System.cpp
# End Source File
# Begin Source File

SOURCE=.\System.h
# End Source File
# End Group
# Begin Group "Screen"

# PROP Default_Filter ""
# Begin Group "Interface"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\IntChar.cpp
# End Source File
# Begin Source File

SOURCE=.\IntChar.h
# End Source File
# Begin Source File

SOURCE=.\Interface.cpp
# End Source File
# Begin Source File

SOURCE=.\Interface.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Cursor.cpp
# End Source File
# Begin Source File

SOURCE=.\Cursor.h
# End Source File
# Begin Source File

SOURCE=.\cursor.YH
# End Source File
# Begin Source File

SOURCE=.\Render.cpp
# End Source File
# Begin Source File

SOURCE=.\Render.h
# End Source File
# Begin Source File

SOURCE=.\Screen.cpp
# End Source File
# Begin Source File

SOURCE=.\Screen.h
# End Source File
# End Group
# Begin Group "Sound"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\crswincpp\inthea\snddrv.h
# End Source File
# Begin Source File

SOURCE=.\Sound.cpp
# End Source File
# Begin Source File

SOURCE=.\Sound.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\Kaar.cpp
# End Source File
# Begin Source File

SOURCE=.\Kaar.h
# End Source File
# Begin Source File

SOURCE=.\SFX.cpp
# End Source File
# Begin Source File

SOURCE=.\SFX.h
# End Source File
# Begin Source File

SOURCE=.\todo.txt
# End Source File
# Begin Source File

SOURCE=.\Datas\univers.txt
# End Source File
# End Target
# End Project
