# Microsoft Developer Studio Project File - Name="sicomex" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=sicomex - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "sicomex.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "sicomex.mak" CFG="sicomex - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "sicomex - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE "sicomex - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName "sicomex"
# PROP Scc_LocalPath "."
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "sicomex - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "WinDebug"
# PROP BASE Intermediate_Dir "WinDebug"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MD /W3 /GX /Zi /Od /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /Gz /MTd /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fr /Yu"stdafx.h" /FD /c
# ADD MTL /mktyplib203
# ADD BASE RSC /l 0x40c /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib /nologo /subsystem:windows /debug /machine:I386
# SUBTRACT LINK32 /pdb:none

!ELSEIF  "$(CFG)" == "sicomex - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "WinRel"
# PROP BASE Intermediate_Dir "WinRel"
# PROP Use_MFC 5
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_AFXDLL" /FR /Yu"stdafx.h" /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fr /Yu"stdafx.h" /FD /c
# ADD MTL /mktyplib203
# ADD BASE RSC /l 0x40c /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x40c /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /machine:I386
# SUBTRACT BASE LINK32 /pdb:none
# ADD LINK32 winmm.lib /nologo /subsystem:windows /machine:I386
# SUBTRACT LINK32 /pdb:none /debug

!ENDIF 

# Begin Target

# Name "sicomex - Win32 Debug"
# Name "sicomex - Win32 Release"
# Begin Group "Application"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\IDD_Mode_Operationnel.cpp
# End Source File
# Begin Source File

SOURCE=.\README.TXT
# End Source File
# Begin Source File

SOURCE=.\sicomex.CPP
# End Source File
# Begin Source File

SOURCE=.\sicomex.RC
# End Source File
# Begin Source File

SOURCE=.\STDAFX.CPP
# ADD BASE CPP /Yc"stdafx.h"
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Ihm"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Group "TRC1752"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\DlgTRC1752_MOD.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_ALE.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_ARQ.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_CONF.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_ENV.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_RDO.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_STST.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_OPS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ALE.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ALE_CALL.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ALE_LP.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ALE_SYS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ALE_TAB.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_CONF.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ENV.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF_ASS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF_BF.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF_LIAS.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF_PIL.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF_TC.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA_A1.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA_A2.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA_B1.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA_B2.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA_TST.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STST.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_TC.cpp
# End Source File
# End Group
# Begin Source File

SOURCE=.\DLG1236.CPP
# End Source File
# Begin Source File

SOURCE=.\dlg1236l.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg1236s.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg1237.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg1237l.cpp
# End Source File
# Begin Source File

SOURCE=.\dlg1237s.cpp
# End Source File
# Begin Source File

SOURCE=.\DLG1241.CPP
# End Source File
# Begin Source File

SOURCE=.\DLG1241L.CPP
# End Source File
# Begin Source File

SOURCE=.\dlg1241s.cpp
# End Source File
# Begin Source File

SOURCE=.\Dlg18C.CPP
# End Source File
# Begin Source File

SOURCE=.\dlg251.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGaad_20_4.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGaad_20_8.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGACCOR.CPP
# End Source File
# Begin Source File

SOURCE=.\dlgaccue.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGAFFEC.CPP
# End Source File
# Begin Source File

SOURCE=.\DLGAIDE.CPP
# End Source File
# Begin Source File

SOURCE=.\DLGAPROP.CPP
# End Source File
# Begin Source File

SOURCE=.\DLGAUDIO.CPP
# End Source File
# Begin Source File

SOURCE=.\DLGCA150.cpp
# End Source File
# Begin Source File

SOURCE=.\dlgCommutationMatrix.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGCONFI.CPP
# End Source File
# Begin Source File

SOURCE=.\DLGCV24Card.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42AnalogDCE.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42AnalogDTE.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42Bit.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42CikSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42DigitalDCE.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42DigitalDTE.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42ERR.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42ERRPANNE.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42GeneralParameter.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42Info.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42KeyDisplay.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42KeyManagement.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42KeyManagementTab.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42KeyTag.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42Pannes.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42Parametres.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42Password.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42Presets.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42PresetsTab.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42SecurityTab.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42StatusERR.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgED42Tab.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGEMHF.CPP
# End Source File
# Begin Source File

SOURCE=.\dlgemrec.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGEQUIP.CPP
# End Source File
# Begin Source File

SOURCE=.\DLGmatL11.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGmatSPIN.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgModeOperationnel.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGOUTIL.CPP
# End Source File
# Begin Source File

SOURCE=.\DLGSTDHF.CPP
# End Source File
# Begin Source File

SOURCE=.\DLGtemp.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGTest1.cpp
# End Source File
# Begin Source File

SOURCE=.\DLGTORCard.cpp
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752.cpp
# End Source File
# End Group
# Begin Group "Ihm Custom"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\CUSTOM\DIODE.CPP
# End Source File
# Begin Source File

SOURCE=.\CUSTOM\ICONE.CPP
# End Source File
# Begin Source File

SOURCE=.\CUSTOM\INTER.CPP
# End Source File
# Begin Source File

SOURCE=.\CUSTOM\OUTIL.CPP
# End Source File
# Begin Source File

SOURCE=.\XTabCtrl.cpp
# End Source File
# End Group
# Begin Group "Equipement"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\equip\AppelAle.cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1225.cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1236.CPP
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1236L.CPP
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1236S.CPP
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1237.CPP
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1237L.CPP
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1237S.CPP
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1241.Cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1241L.Cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1241S.Cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp18A.cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp18C.cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp251.Cpp
# End Source File
# Begin Source File

SOURCE=.\equip\EqpAAD.cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EqpAcco.CPP
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EqpAudi.CPP
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EqpCA150.cpp
# End Source File
# Begin Source File

SOURCE=.\equip\EqpCV24Card.cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EqpMAT.cpp
# End Source File
# Begin Source File

SOURCE=.\equip\eqpMATCOM.cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EqpStd.CPP
# End Source File
# Begin Source File

SOURCE=.\equip\EqpTemp.cpp
# End Source File
# Begin Source File

SOURCE=.\equip\EqpTORCard.cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EQUIP.CPP
# End Source File
# Begin Source File

SOURCE=.\equip\EquipED42.cpp
# End Source File
# Begin Source File

SOURCE=.\equip\EquipM1752.cpp
# End Source File
# Begin Source File

SOURCE=.\equip\EquipTest.cpp
# End Source File
# Begin Source File

SOURCE=.\EQUIP\PARAMSIM.CPP
# End Source File
# Begin Source File

SOURCE=.\EQUIP\SEQUENCE.CPP
# End Source File
# Begin Source File

SOURCE=.\EQUIP\SYNCHRO.CPP
# End Source File
# End Group
# Begin Group "Communication"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\COMM\p_1225.CPP
# End Source File
# Begin Source File

SOURCE=.\COMM\P_1236.CPP
# End Source File
# Begin Source File

SOURCE=.\COMM\P_1237.CPP
# End Source File
# Begin Source File

SOURCE=.\COMM\P_1241.CPP
# End Source File
# Begin Source File

SOURCE=.\COMM\P_18A.CPP
# End Source File
# Begin Source File

SOURCE=.\COMM\P_251.CPP
# End Source File
# Begin Source File

SOURCE=.\comm\p_AAD.cpp
# End Source File
# Begin Source File

SOURCE=.\COMM\p_CA150.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\p_CV24Card.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\p_ED42.cpp
# End Source File
# Begin Source File

SOURCE=.\COMM\p_MAT.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\p_MatCom.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\p_temp.cpp
# End Source File
# Begin Source File

SOURCE=.\COMM\p_Test.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\p_TORCard.cpp
# End Source File
# Begin Source File

SOURCE=.\comm\p_TRC1752.cpp
# End Source File
# Begin Source File

SOURCE=.\COMM\PORT.CPP
# End Source File
# Begin Source File

SOURCE=.\COMM\PROT_ACC.CPP
# End Source File
# Begin Source File

SOURCE=.\COMM\PROT_AUD.CPP
# End Source File
# Begin Source File

SOURCE=.\COMM\PROT_STD.CPP
# End Source File
# Begin Source File

SOURCE=.\COMM\PROTO.CPP
# End Source File
# End Group
# Begin Group "Divers"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;hpj;bat;for;f90"
# Begin Source File

SOURCE=.\DIVERS\DIV_FIC.CPP
# End Source File
# Begin Source File

SOURCE=.\DIVERS\DIV_TMP.CPP
# End Source File
# Begin Source File

SOURCE=.\MyEdit.cpp
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.cpp
# End Source File
# Begin Source File

SOURCE=.\DIVERS\TABLE.CPP
# End Source File
# Begin Source File

SOURCE=.\DIVERS\TACHE.CPP
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl;fi;fd"
# Begin Source File

SOURCE=.\equip\AppelAle.h
# End Source File
# Begin Source File

SOURCE=.\CUSTOM\DIODE.H
# End Source File
# Begin Source File

SOURCE=.\DIVERS\DIV_FIC.H
# End Source File
# Begin Source File

SOURCE=.\DIVERS\DIV_TMP.H
# End Source File
# Begin Source File

SOURCE=.\dlg1236.h
# End Source File
# Begin Source File

SOURCE=.\dlg1236l.h
# End Source File
# Begin Source File

SOURCE=.\dlg1236s.h
# End Source File
# Begin Source File

SOURCE=.\dlg1237.h
# End Source File
# Begin Source File

SOURCE=.\dlg1237l.h
# End Source File
# Begin Source File

SOURCE=.\dlg1237s.h
# End Source File
# Begin Source File

SOURCE=.\DLG1241.H
# End Source File
# Begin Source File

SOURCE=.\DLG1241L.H
# End Source File
# Begin Source File

SOURCE=.\dlg1241s.h
# End Source File
# Begin Source File

SOURCE=.\dlg18c.h
# End Source File
# Begin Source File

SOURCE=.\dlg251.h
# End Source File
# Begin Source File

SOURCE=.\DLGaad_20_4.h
# End Source File
# Begin Source File

SOURCE=.\DLGaad_20_8.h
# End Source File
# Begin Source File

SOURCE=.\DLGACCOR.H
# End Source File
# Begin Source File

SOURCE=.\dlgaccue.h
# End Source File
# Begin Source File

SOURCE=.\DLGAFFEC.H
# End Source File
# Begin Source File

SOURCE=.\DLGAIDE.H
# End Source File
# Begin Source File

SOURCE=.\DLGAPROP.H
# End Source File
# Begin Source File

SOURCE=.\DLGAUDIO.H
# End Source File
# Begin Source File

SOURCE=.\DLGCA150.h
# End Source File
# Begin Source File

SOURCE=.\dlgCommutationMatrix.h
# End Source File
# Begin Source File

SOURCE=.\DLGCONFI.H
# End Source File
# Begin Source File

SOURCE=.\DLGCV24Card.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42AnalogDCE.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42AnalogDTE.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42Bit.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42CikSystem.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42DigitalDCE.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42DigitalDTE.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42ERR.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42ERRPANNE.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42GeneralParameter.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42Info.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42KeyDisplay.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42KeyManagement.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42KeyManagementTab.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42KeyTag.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42Pannes.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42Parametres.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42Password.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42Presets.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42PresetsTab.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42SecurityTab.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42StatusERR.h
# End Source File
# Begin Source File

SOURCE=.\DlgED42Tab.h
# End Source File
# Begin Source File

SOURCE=.\DLGEMHF.H
# End Source File
# Begin Source File

SOURCE=.\dlgemrec.h
# End Source File
# Begin Source File

SOURCE=.\DLGEQUIP.H
# End Source File
# Begin Source File

SOURCE=.\DLGmatL11.h
# End Source File
# Begin Source File

SOURCE=.\DLGmatSPIN.h
# End Source File
# Begin Source File

SOURCE=.\DlgModeOperationnel.h
# End Source File
# Begin Source File

SOURCE=.\DLGOUTIL.H
# End Source File
# Begin Source File

SOURCE=.\DLGSTDHF.H
# End Source File
# Begin Source File

SOURCE=.\DLGtemp.h
# End Source File
# Begin Source File

SOURCE=.\DLGTest1.h
# End Source File
# Begin Source File

SOURCE=.\DLGTORCard.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_ALE.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_ARQ.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_CONF.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_ENV.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_RDO.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_CONF_STST.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_OPS.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ALE.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ALE_CALL.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ALE_LP.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ALE_SYS.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ALE_TAB.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_CONF.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_ENV.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF_ASS.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF_BF.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF_LIAS.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF_PIL.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_INTF_TC.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA_A1.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA_A2.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA_B1.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA_B2.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STA_TST.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_STST.h
# End Source File
# Begin Source File

SOURCE=.\DlgTRC1752_MOD_PROG_TC.h
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1225.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1236.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1236L.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1236S.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1237.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1237L.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1237S.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1241.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1241L.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp1241S.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp18A.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp18C.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\Eqp251.H
# End Source File
# Begin Source File

SOURCE=.\equip\EqpAAD.h
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EqpAcco.h
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EqpAudi.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EqpCA150.h
# End Source File
# Begin Source File

SOURCE=.\equip\EqpCV24Card.h
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EqpMAT.h
# End Source File
# Begin Source File

SOURCE=.\equip\eqpMATCOM.h
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EqpStd.H
# End Source File
# Begin Source File

SOURCE=.\equip\EqpTemp.h
# End Source File
# Begin Source File

SOURCE=.\equip\eqpTORCard.h
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EQUIP.H
# End Source File
# Begin Source File

SOURCE=.\equip\EquipED42.h
# End Source File
# Begin Source File

SOURCE=.\equip\EquipM1752.h
# End Source File
# Begin Source File

SOURCE=.\EQUIP\EquipTest.h
# End Source File
# Begin Source File

SOURCE=.\equip\EquipXT4410.h
# End Source File
# Begin Source File

SOURCE=.\GLOBAL.H
# End Source File
# Begin Source File

SOURCE=.\CUSTOM\ICONE.H
# End Source File
# Begin Source File

SOURCE=.\IDD_Mode_Operationnel.h
# End Source File
# Begin Source File

SOURCE=.\CUSTOM\INTER.H
# End Source File
# Begin Source File

SOURCE=.\MyEdit.h
# End Source File
# Begin Source File

SOURCE=.\MyListCtrl.h
# End Source File
# Begin Source File

SOURCE=.\CUSTOM\OUTIL.H
# End Source File
# Begin Source File

SOURCE=.\COMM\p_1225.H
# End Source File
# Begin Source File

SOURCE=.\COMM\P_1236.H
# End Source File
# Begin Source File

SOURCE=.\COMM\P_1237.H
# End Source File
# Begin Source File

SOURCE=.\COMM\P_1241.H
# End Source File
# Begin Source File

SOURCE=.\COMM\P_18A.H
# End Source File
# Begin Source File

SOURCE=.\COMM\P_251.H
# End Source File
# Begin Source File

SOURCE=.\comm\p_AAD.h
# End Source File
# Begin Source File

SOURCE=.\COMM\p_CA150.h
# End Source File
# Begin Source File

SOURCE=.\comm\p_CV24Card.h
# End Source File
# Begin Source File

SOURCE=.\comm\p_ED42.h
# End Source File
# Begin Source File

SOURCE=.\COMM\p_MAT.h
# End Source File
# Begin Source File

SOURCE=.\comm\p_MatCom.h
# End Source File
# Begin Source File

SOURCE=.\comm\p_temp.h
# End Source File
# Begin Source File

SOURCE=.\COMM\p_Test.h
# End Source File
# Begin Source File

SOURCE=.\comm\p_TORCard.h
# End Source File
# Begin Source File

SOURCE=.\comm\p_TRC1752.h
# End Source File
# Begin Source File

SOURCE=.\EQUIP\PARAMSIM.H
# End Source File
# Begin Source File

SOURCE=.\COMM\PORT.H
# End Source File
# Begin Source File

SOURCE=.\COMM\PROT_ACC.H
# End Source File
# Begin Source File

SOURCE=.\COMM\PROT_AUD.H
# End Source File
# Begin Source File

SOURCE=.\COMM\PROT_STD.H
# End Source File
# Begin Source File

SOURCE=.\COMM\PROTO.H
# End Source File
# Begin Source File

SOURCE=.\resource.h
# End Source File
# Begin Source File

SOURCE=.\EQUIP\SEQUENCE.H
# End Source File
# Begin Source File

SOURCE=.\sicomex.H
# End Source File
# Begin Source File

SOURCE=.\STDAFX.H
# End Source File
# Begin Source File

SOURCE=.\EQUIP\SYNCHRO.H
# End Source File
# Begin Source File

SOURCE=.\DIVERS\TABLE.H
# End Source File
# Begin Source File

SOURCE=.\DIVERS\TACHE.H
# End Source File
# Begin Source File

SOURCE=.\TYP_GLOB.H
# End Source File
# Begin Source File

SOURCE=.\XTabCtrl.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;cnt;rtf;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\AAD20_4.bmp
# End Source File
# Begin Source File

SOURCE=.\res\AAD20_8.bmp
# End Source File
# Begin Source File

SOURCE=.\res\andvt.bmp
# End Source File
# Begin Source File

SOURCE=.\res\atos.bmp
# End Source File
# Begin Source File

SOURCE=.\res\atoslogo_rgb.bmp
# End Source File
# Begin Source File

SOURCE=.\res\black.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ca_150.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cik_off.bmp
# End Source File
# Begin Source File

SOURCE=.\res\cik_on.bmp
# End Source File
# Begin Source File

SOURCE=.\res\ComMat.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\DIODE_ER.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\DIODE_OF.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\DIODE_ON.BMP
# End Source File
# Begin Source File

SOURCE=.\res\ED42.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\EM_HF.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\EQP_ACCO.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\EQP_AUDI.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\EQP_EMET.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\EQP_EMRE.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\EQP_RECE.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\EQP_STD_.BMP
# End Source File
# Begin Source File

SOURCE=.\res\icon1.ico
# End Source File
# Begin Source File

SOURCE=.\RES\INTER_OF.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\INTER_ON.BMP
# End Source File
# Begin Source File

SOURCE=.\RES\IOS.ICO
# End Source File
# Begin Source File

SOURCE=.\res\ky58.bmp
# End Source File
# Begin Source File

SOURCE=.\res\matl11.bmp
# End Source File
# Begin Source File

SOURCE=.\res\matspin.bmp
# End Source File
# Begin Source File

SOURCE=.\res\mdm_1752.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\REC_HF.ICO
# End Source File
# Begin Source File

SOURCE=.\res\red.bmp
# End Source File
# Begin Source File

SOURCE=.\RES\sicomex.ICO
# End Source File
# Begin Source File

SOURCE=.\RES\sicomex.RC2
# End Source File
# Begin Source File

SOURCE=.\res\tor.bmp
# End Source File
# Begin Source File

SOURCE=.\res\white.bmp
# End Source File
# End Group
# End Target
# End Project
