# Microsoft Developer Studio Generated NMAKE File, Based on sicomex.dsp
!IF "$(CFG)" == ""
CFG=sicomex - Win32 Debug
!MESSAGE No configuration specified. Defaulting to sicomex - Win32 Debug.
!ENDIF 

!IF "$(CFG)" != "sicomex - Win32 Debug" && "$(CFG)" != "sicomex - Win32 Release"
!MESSAGE Invalid configuration "$(CFG)" specified.
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
!ERROR An invalid configuration is specified.
!ENDIF 

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE 
NULL=nul
!ENDIF 

!IF  "$(CFG)" == "sicomex - Win32 Debug"

OUTDIR=c:\Sicomex
INTDIR=c:\tmp\Sicomex
# Begin Custom Macros
OutDir=c:\Sicomex
# End Custom Macros

ALL : "$(OUTDIR)\sicomex.exe" "$(OUTDIR)\sicomex.bsc"


CLEAN :
	-@erase "$(INTDIR)\AppelAle.obj"
	-@erase "$(INTDIR)\AppelAle.sbr"
	-@erase "$(INTDIR)\DIODE.OBJ"
	-@erase "$(INTDIR)\DIODE.SBR"
	-@erase "$(INTDIR)\DIV_FIC.OBJ"
	-@erase "$(INTDIR)\DIV_FIC.SBR"
	-@erase "$(INTDIR)\DIV_TMP.OBJ"
	-@erase "$(INTDIR)\DIV_TMP.SBR"
	-@erase "$(INTDIR)\DLG1236.OBJ"
	-@erase "$(INTDIR)\DLG1236.SBR"
	-@erase "$(INTDIR)\dlg1236l.obj"
	-@erase "$(INTDIR)\dlg1236l.sbr"
	-@erase "$(INTDIR)\dlg1236s.obj"
	-@erase "$(INTDIR)\dlg1236s.sbr"
	-@erase "$(INTDIR)\dlg1237.obj"
	-@erase "$(INTDIR)\dlg1237.sbr"
	-@erase "$(INTDIR)\dlg1237l.obj"
	-@erase "$(INTDIR)\dlg1237l.sbr"
	-@erase "$(INTDIR)\dlg1237s.obj"
	-@erase "$(INTDIR)\dlg1237s.sbr"
	-@erase "$(INTDIR)\DLG1241.OBJ"
	-@erase "$(INTDIR)\DLG1241.SBR"
	-@erase "$(INTDIR)\DLG1241L.OBJ"
	-@erase "$(INTDIR)\DLG1241L.SBR"
	-@erase "$(INTDIR)\dlg1241s.obj"
	-@erase "$(INTDIR)\dlg1241s.sbr"
	-@erase "$(INTDIR)\Dlg18C.obj"
	-@erase "$(INTDIR)\Dlg18C.sbr"
	-@erase "$(INTDIR)\dlg251.obj"
	-@erase "$(INTDIR)\dlg251.sbr"
	-@erase "$(INTDIR)\DLGaad_20_4.obj"
	-@erase "$(INTDIR)\DLGaad_20_4.sbr"
	-@erase "$(INTDIR)\DLGaad_20_8.obj"
	-@erase "$(INTDIR)\DLGaad_20_8.sbr"
	-@erase "$(INTDIR)\DLGACCOR.OBJ"
	-@erase "$(INTDIR)\DLGACCOR.SBR"
	-@erase "$(INTDIR)\dlgaccue.obj"
	-@erase "$(INTDIR)\dlgaccue.sbr"
	-@erase "$(INTDIR)\DLGAFFEC.OBJ"
	-@erase "$(INTDIR)\DLGAFFEC.SBR"
	-@erase "$(INTDIR)\DLGAIDE.OBJ"
	-@erase "$(INTDIR)\DLGAIDE.SBR"
	-@erase "$(INTDIR)\DLGAPROP.OBJ"
	-@erase "$(INTDIR)\DLGAPROP.SBR"
	-@erase "$(INTDIR)\DLGAUDIO.OBJ"
	-@erase "$(INTDIR)\DLGAUDIO.SBR"
	-@erase "$(INTDIR)\DLGCA150.obj"
	-@erase "$(INTDIR)\DLGCA150.sbr"
	-@erase "$(INTDIR)\dlgCommutationMatrix.obj"
	-@erase "$(INTDIR)\dlgCommutationMatrix.sbr"
	-@erase "$(INTDIR)\DLGCONFI.OBJ"
	-@erase "$(INTDIR)\DLGCONFI.SBR"
	-@erase "$(INTDIR)\DLGCV24Card.obj"
	-@erase "$(INTDIR)\DLGCV24Card.sbr"
	-@erase "$(INTDIR)\DlgED42.obj"
	-@erase "$(INTDIR)\DlgED42.sbr"
	-@erase "$(INTDIR)\DLGEMHF.OBJ"
	-@erase "$(INTDIR)\DLGEMHF.SBR"
	-@erase "$(INTDIR)\dlgemrec.obj"
	-@erase "$(INTDIR)\dlgemrec.sbr"
	-@erase "$(INTDIR)\DLGEQUIP.OBJ"
	-@erase "$(INTDIR)\DLGEQUIP.SBR"
	-@erase "$(INTDIR)\DLGmatL11.obj"
	-@erase "$(INTDIR)\DLGmatL11.sbr"
	-@erase "$(INTDIR)\DLGmatSPIN.obj"
	-@erase "$(INTDIR)\DLGmatSPIN.sbr"
	-@erase "$(INTDIR)\DlgModeOperationnel.obj"
	-@erase "$(INTDIR)\DlgModeOperationnel.sbr"
	-@erase "$(INTDIR)\DLGOUTIL.OBJ"
	-@erase "$(INTDIR)\DLGOUTIL.SBR"
	-@erase "$(INTDIR)\DLGSTDHF.OBJ"
	-@erase "$(INTDIR)\DLGSTDHF.SBR"
	-@erase "$(INTDIR)\DLGtemp.obj"
	-@erase "$(INTDIR)\DLGtemp.sbr"
	-@erase "$(INTDIR)\DLGTest1.obj"
	-@erase "$(INTDIR)\DLGTest1.sbr"
	-@erase "$(INTDIR)\DLGTORCard.obj"
	-@erase "$(INTDIR)\DLGTORCard.sbr"
	-@erase "$(INTDIR)\DlgTRC1752.obj"
	-@erase "$(INTDIR)\DlgTRC1752.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ALE.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ALE.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ARQ.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ARQ.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_CONF.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_CONF.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ENV.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ENV.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_RDO.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_RDO.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_STST.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_STST.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_OPS.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_OPS.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_CALL.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_CALL.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_LP.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_LP.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_SYS.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_SYS.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_TAB.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_TAB.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_CONF.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_CONF.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ENV.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ENV.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_ASS.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_ASS.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_BF.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_BF.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_LIAS.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_LIAS.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_PIL.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_PIL.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_TC.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_TC.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A1.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A1.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A2.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A2.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B1.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B1.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B2.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B2.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_TST.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_TST.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STST.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STST.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_TC.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_TC.sbr"
	-@erase "$(INTDIR)\Eqp1225.obj"
	-@erase "$(INTDIR)\Eqp1225.sbr"
	-@erase "$(INTDIR)\Eqp1236.obj"
	-@erase "$(INTDIR)\Eqp1236.sbr"
	-@erase "$(INTDIR)\Eqp1236L.obj"
	-@erase "$(INTDIR)\Eqp1236L.sbr"
	-@erase "$(INTDIR)\Eqp1236S.obj"
	-@erase "$(INTDIR)\Eqp1236S.sbr"
	-@erase "$(INTDIR)\Eqp1237.obj"
	-@erase "$(INTDIR)\Eqp1237.sbr"
	-@erase "$(INTDIR)\Eqp1237L.obj"
	-@erase "$(INTDIR)\Eqp1237L.sbr"
	-@erase "$(INTDIR)\Eqp1237S.obj"
	-@erase "$(INTDIR)\Eqp1237S.sbr"
	-@erase "$(INTDIR)\Eqp1241.obj"
	-@erase "$(INTDIR)\Eqp1241.sbr"
	-@erase "$(INTDIR)\Eqp1241L.obj"
	-@erase "$(INTDIR)\Eqp1241L.sbr"
	-@erase "$(INTDIR)\Eqp1241S.obj"
	-@erase "$(INTDIR)\Eqp1241S.sbr"
	-@erase "$(INTDIR)\Eqp18A.obj"
	-@erase "$(INTDIR)\Eqp18A.sbr"
	-@erase "$(INTDIR)\Eqp18C.obj"
	-@erase "$(INTDIR)\Eqp18C.sbr"
	-@erase "$(INTDIR)\Eqp251.obj"
	-@erase "$(INTDIR)\Eqp251.sbr"
	-@erase "$(INTDIR)\EqpAAD.obj"
	-@erase "$(INTDIR)\EqpAAD.sbr"
	-@erase "$(INTDIR)\EqpAcco.obj"
	-@erase "$(INTDIR)\EqpAcco.sbr"
	-@erase "$(INTDIR)\EqpAudi.obj"
	-@erase "$(INTDIR)\EqpAudi.sbr"
	-@erase "$(INTDIR)\EqpCA150.obj"
	-@erase "$(INTDIR)\EqpCA150.sbr"
	-@erase "$(INTDIR)\EqpCV24Card.obj"
	-@erase "$(INTDIR)\EqpCV24Card.sbr"
	-@erase "$(INTDIR)\EqpMAT.obj"
	-@erase "$(INTDIR)\EqpMAT.sbr"
	-@erase "$(INTDIR)\eqpMATCOM.obj"
	-@erase "$(INTDIR)\eqpMATCOM.sbr"
	-@erase "$(INTDIR)\EqpStd.obj"
	-@erase "$(INTDIR)\EqpStd.sbr"
	-@erase "$(INTDIR)\EqpTemp.obj"
	-@erase "$(INTDIR)\EqpTemp.sbr"
	-@erase "$(INTDIR)\EqpTORCard.obj"
	-@erase "$(INTDIR)\EqpTORCard.sbr"
	-@erase "$(INTDIR)\EQUIP.OBJ"
	-@erase "$(INTDIR)\EQUIP.SBR"
	-@erase "$(INTDIR)\EquipED42.obj"
	-@erase "$(INTDIR)\EquipED42.sbr"
	-@erase "$(INTDIR)\EquipM1752.obj"
	-@erase "$(INTDIR)\EquipM1752.sbr"
	-@erase "$(INTDIR)\EquipTest.obj"
	-@erase "$(INTDIR)\EquipTest.sbr"
	-@erase "$(INTDIR)\ICONE.OBJ"
	-@erase "$(INTDIR)\ICONE.SBR"
	-@erase "$(INTDIR)\IDD_Mode_Operationnel.obj"
	-@erase "$(INTDIR)\IDD_Mode_Operationnel.sbr"
	-@erase "$(INTDIR)\INTER.OBJ"
	-@erase "$(INTDIR)\INTER.SBR"
	-@erase "$(INTDIR)\MyEdit.obj"
	-@erase "$(INTDIR)\MyEdit.sbr"
	-@erase "$(INTDIR)\OUTIL.OBJ"
	-@erase "$(INTDIR)\OUTIL.SBR"
	-@erase "$(INTDIR)\p_1225.obj"
	-@erase "$(INTDIR)\p_1225.sbr"
	-@erase "$(INTDIR)\P_1236.OBJ"
	-@erase "$(INTDIR)\P_1236.SBR"
	-@erase "$(INTDIR)\P_1237.OBJ"
	-@erase "$(INTDIR)\P_1237.SBR"
	-@erase "$(INTDIR)\P_1241.OBJ"
	-@erase "$(INTDIR)\P_1241.SBR"
	-@erase "$(INTDIR)\P_18A.OBJ"
	-@erase "$(INTDIR)\P_18A.SBR"
	-@erase "$(INTDIR)\P_251.OBJ"
	-@erase "$(INTDIR)\P_251.SBR"
	-@erase "$(INTDIR)\p_AAD.obj"
	-@erase "$(INTDIR)\p_AAD.sbr"
	-@erase "$(INTDIR)\p_CA150.obj"
	-@erase "$(INTDIR)\p_CA150.sbr"
	-@erase "$(INTDIR)\p_CV24Card.obj"
	-@erase "$(INTDIR)\p_CV24Card.sbr"
	-@erase "$(INTDIR)\p_ED42.obj"
	-@erase "$(INTDIR)\p_ED42.sbr"
	-@erase "$(INTDIR)\p_MAT.obj"
	-@erase "$(INTDIR)\p_MAT.sbr"
	-@erase "$(INTDIR)\p_MatCom.obj"
	-@erase "$(INTDIR)\p_MatCom.sbr"
	-@erase "$(INTDIR)\p_temp.obj"
	-@erase "$(INTDIR)\p_temp.sbr"
	-@erase "$(INTDIR)\p_Test.obj"
	-@erase "$(INTDIR)\p_Test.sbr"
	-@erase "$(INTDIR)\p_TORCard.obj"
	-@erase "$(INTDIR)\p_TORCard.sbr"
	-@erase "$(INTDIR)\p_TRC1752.obj"
	-@erase "$(INTDIR)\p_TRC1752.sbr"
	-@erase "$(INTDIR)\PARAMSIM.OBJ"
	-@erase "$(INTDIR)\PARAMSIM.SBR"
	-@erase "$(INTDIR)\PORT.OBJ"
	-@erase "$(INTDIR)\PORT.SBR"
	-@erase "$(INTDIR)\PROT_ACC.OBJ"
	-@erase "$(INTDIR)\PROT_ACC.SBR"
	-@erase "$(INTDIR)\PROT_AUD.OBJ"
	-@erase "$(INTDIR)\PROT_AUD.SBR"
	-@erase "$(INTDIR)\PROT_STD.OBJ"
	-@erase "$(INTDIR)\PROT_STD.SBR"
	-@erase "$(INTDIR)\PROTO.OBJ"
	-@erase "$(INTDIR)\PROTO.SBR"
	-@erase "$(INTDIR)\SEQUENCE.OBJ"
	-@erase "$(INTDIR)\SEQUENCE.SBR"
	-@erase "$(INTDIR)\sicomex.obj"
	-@erase "$(INTDIR)\sicomex.pch"
	-@erase "$(INTDIR)\sicomex.res"
	-@erase "$(INTDIR)\sicomex.sbr"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\STDAFX.SBR"
	-@erase "$(INTDIR)\SYNCHRO.OBJ"
	-@erase "$(INTDIR)\SYNCHRO.SBR"
	-@erase "$(INTDIR)\TABLE.OBJ"
	-@erase "$(INTDIR)\TABLE.SBR"
	-@erase "$(INTDIR)\TACHE.OBJ"
	-@erase "$(INTDIR)\TACHE.SBR"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\vc60.pdb"
	-@erase "$(INTDIR)\XTabCtrl.obj"
	-@erase "$(INTDIR)\XTabCtrl.sbr"
	-@erase "$(OUTDIR)\sicomex.bsc"
	-@erase "$(OUTDIR)\sicomex.exe"
	-@erase "$(OUTDIR)\sicomex.ilk"
	-@erase "$(OUTDIR)\sicomex.pdb"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /Gz /MTd /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\sicomex.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/mktyplib203 
RSC=rc.exe
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\sicomex.res" /d "_DEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sicomex.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DlgModeOperationnel.sbr" \
	"$(INTDIR)\IDD_Mode_Operationnel.sbr" \
	"$(INTDIR)\MyEdit.sbr" \
	"$(INTDIR)\sicomex.sbr" \
	"$(INTDIR)\STDAFX.SBR" \
	"$(INTDIR)\DlgTRC1752_MOD.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ALE.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ARQ.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_CONF.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ENV.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_RDO.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_STST.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_OPS.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_CALL.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_LP.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_SYS.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_TAB.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_CONF.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ENV.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_ASS.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_BF.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_LIAS.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_PIL.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_TC.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A1.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A2.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B1.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B2.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_TST.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STST.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_TC.sbr" \
	"$(INTDIR)\DLG1236.SBR" \
	"$(INTDIR)\dlg1236l.sbr" \
	"$(INTDIR)\dlg1236s.sbr" \
	"$(INTDIR)\dlg1237.sbr" \
	"$(INTDIR)\dlg1237l.sbr" \
	"$(INTDIR)\dlg1237s.sbr" \
	"$(INTDIR)\DLG1241.SBR" \
	"$(INTDIR)\DLG1241L.SBR" \
	"$(INTDIR)\dlg1241s.sbr" \
	"$(INTDIR)\Dlg18C.sbr" \
	"$(INTDIR)\dlg251.sbr" \
	"$(INTDIR)\DLGaad_20_4.sbr" \
	"$(INTDIR)\DLGaad_20_8.sbr" \
	"$(INTDIR)\DLGACCOR.SBR" \
	"$(INTDIR)\dlgaccue.sbr" \
	"$(INTDIR)\DLGAFFEC.SBR" \
	"$(INTDIR)\DLGAIDE.SBR" \
	"$(INTDIR)\DLGAPROP.SBR" \
	"$(INTDIR)\DLGAUDIO.SBR" \
	"$(INTDIR)\DLGCA150.sbr" \
	"$(INTDIR)\dlgCommutationMatrix.sbr" \
	"$(INTDIR)\DLGCONFI.SBR" \
	"$(INTDIR)\DLGCV24Card.sbr" \
	"$(INTDIR)\DlgED42.sbr" \
	"$(INTDIR)\DLGEMHF.SBR" \
	"$(INTDIR)\dlgemrec.sbr" \
	"$(INTDIR)\DLGEQUIP.SBR" \
	"$(INTDIR)\DLGmatL11.sbr" \
	"$(INTDIR)\DLGmatSPIN.sbr" \
	"$(INTDIR)\DLGOUTIL.SBR" \
	"$(INTDIR)\DLGSTDHF.SBR" \
	"$(INTDIR)\DLGtemp.sbr" \
	"$(INTDIR)\DLGTest1.sbr" \
	"$(INTDIR)\DLGTORCard.sbr" \
	"$(INTDIR)\DlgTRC1752.sbr" \
	"$(INTDIR)\DIODE.SBR" \
	"$(INTDIR)\ICONE.SBR" \
	"$(INTDIR)\INTER.SBR" \
	"$(INTDIR)\OUTIL.SBR" \
	"$(INTDIR)\XTabCtrl.sbr" \
	"$(INTDIR)\AppelAle.sbr" \
	"$(INTDIR)\Eqp1225.sbr" \
	"$(INTDIR)\Eqp1236.sbr" \
	"$(INTDIR)\Eqp1236L.sbr" \
	"$(INTDIR)\Eqp1236S.sbr" \
	"$(INTDIR)\Eqp1237.sbr" \
	"$(INTDIR)\Eqp1237L.sbr" \
	"$(INTDIR)\Eqp1237S.sbr" \
	"$(INTDIR)\Eqp1241.sbr" \
	"$(INTDIR)\Eqp1241L.sbr" \
	"$(INTDIR)\Eqp1241S.sbr" \
	"$(INTDIR)\Eqp18A.sbr" \
	"$(INTDIR)\Eqp18C.sbr" \
	"$(INTDIR)\Eqp251.sbr" \
	"$(INTDIR)\EqpAAD.sbr" \
	"$(INTDIR)\EqpAcco.sbr" \
	"$(INTDIR)\EqpAudi.sbr" \
	"$(INTDIR)\EqpCA150.sbr" \
	"$(INTDIR)\EqpCV24Card.sbr" \
	"$(INTDIR)\EqpMAT.sbr" \
	"$(INTDIR)\eqpMATCOM.sbr" \
	"$(INTDIR)\EqpStd.sbr" \
	"$(INTDIR)\EqpTemp.sbr" \
	"$(INTDIR)\EqpTORCard.sbr" \
	"$(INTDIR)\EQUIP.SBR" \
	"$(INTDIR)\EquipED42.sbr" \
	"$(INTDIR)\EquipM1752.sbr" \
	"$(INTDIR)\EquipTest.sbr" \
	"$(INTDIR)\PARAMSIM.SBR" \
	"$(INTDIR)\SEQUENCE.SBR" \
	"$(INTDIR)\SYNCHRO.SBR" \
	"$(INTDIR)\p_1225.sbr" \
	"$(INTDIR)\P_1236.SBR" \
	"$(INTDIR)\P_1237.SBR" \
	"$(INTDIR)\P_1241.SBR" \
	"$(INTDIR)\P_18A.SBR" \
	"$(INTDIR)\P_251.SBR" \
	"$(INTDIR)\p_AAD.sbr" \
	"$(INTDIR)\p_CA150.sbr" \
	"$(INTDIR)\p_CV24Card.sbr" \
	"$(INTDIR)\p_ED42.sbr" \
	"$(INTDIR)\p_MAT.sbr" \
	"$(INTDIR)\p_MatCom.sbr" \
	"$(INTDIR)\p_temp.sbr" \
	"$(INTDIR)\p_Test.sbr" \
	"$(INTDIR)\p_TORCard.sbr" \
	"$(INTDIR)\p_TRC1752.sbr" \
	"$(INTDIR)\PORT.SBR" \
	"$(INTDIR)\PROT_ACC.SBR" \
	"$(INTDIR)\PROT_AUD.SBR" \
	"$(INTDIR)\PROT_STD.SBR" \
	"$(INTDIR)\PROTO.SBR" \
	"$(INTDIR)\DIV_FIC.SBR" \
	"$(INTDIR)\DIV_TMP.SBR" \
	"$(INTDIR)\TABLE.SBR" \
	"$(INTDIR)\TACHE.SBR"

"$(OUTDIR)\sicomex.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:yes /pdb:"$(OUTDIR)\sicomex.pdb" /debug /machine:I386 /out:"$(OUTDIR)\sicomex.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DlgModeOperationnel.obj" \
	"$(INTDIR)\IDD_Mode_Operationnel.obj" \
	"$(INTDIR)\MyEdit.obj" \
	"$(INTDIR)\sicomex.obj" \
	"$(INTDIR)\STDAFX.OBJ" \
	"$(INTDIR)\DlgTRC1752_MOD.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ALE.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ARQ.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_CONF.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ENV.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_RDO.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_STST.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_OPS.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_CALL.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_LP.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_SYS.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_TAB.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_CONF.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ENV.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_ASS.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_BF.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_LIAS.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_PIL.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_TC.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A1.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A2.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B1.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B2.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_TST.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STST.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_TC.obj" \
	"$(INTDIR)\DLG1236.OBJ" \
	"$(INTDIR)\dlg1236l.obj" \
	"$(INTDIR)\dlg1236s.obj" \
	"$(INTDIR)\dlg1237.obj" \
	"$(INTDIR)\dlg1237l.obj" \
	"$(INTDIR)\dlg1237s.obj" \
	"$(INTDIR)\DLG1241.OBJ" \
	"$(INTDIR)\DLG1241L.OBJ" \
	"$(INTDIR)\dlg1241s.obj" \
	"$(INTDIR)\Dlg18C.obj" \
	"$(INTDIR)\dlg251.obj" \
	"$(INTDIR)\DLGaad_20_4.obj" \
	"$(INTDIR)\DLGaad_20_8.obj" \
	"$(INTDIR)\DLGACCOR.OBJ" \
	"$(INTDIR)\dlgaccue.obj" \
	"$(INTDIR)\DLGAFFEC.OBJ" \
	"$(INTDIR)\DLGAIDE.OBJ" \
	"$(INTDIR)\DLGAPROP.OBJ" \
	"$(INTDIR)\DLGAUDIO.OBJ" \
	"$(INTDIR)\DLGCA150.obj" \
	"$(INTDIR)\dlgCommutationMatrix.obj" \
	"$(INTDIR)\DLGCONFI.OBJ" \
	"$(INTDIR)\DLGCV24Card.obj" \
	"$(INTDIR)\DlgED42.obj" \
	"$(INTDIR)\DLGEMHF.OBJ" \
	"$(INTDIR)\dlgemrec.obj" \
	"$(INTDIR)\DLGEQUIP.OBJ" \
	"$(INTDIR)\DLGmatL11.obj" \
	"$(INTDIR)\DLGmatSPIN.obj" \
	"$(INTDIR)\DLGOUTIL.OBJ" \
	"$(INTDIR)\DLGSTDHF.OBJ" \
	"$(INTDIR)\DLGtemp.obj" \
	"$(INTDIR)\DLGTest1.obj" \
	"$(INTDIR)\DLGTORCard.obj" \
	"$(INTDIR)\DlgTRC1752.obj" \
	"$(INTDIR)\DIODE.OBJ" \
	"$(INTDIR)\ICONE.OBJ" \
	"$(INTDIR)\INTER.OBJ" \
	"$(INTDIR)\OUTIL.OBJ" \
	"$(INTDIR)\XTabCtrl.obj" \
	"$(INTDIR)\AppelAle.obj" \
	"$(INTDIR)\Eqp1225.obj" \
	"$(INTDIR)\Eqp1236.obj" \
	"$(INTDIR)\Eqp1236L.obj" \
	"$(INTDIR)\Eqp1236S.obj" \
	"$(INTDIR)\Eqp1237.obj" \
	"$(INTDIR)\Eqp1237L.obj" \
	"$(INTDIR)\Eqp1237S.obj" \
	"$(INTDIR)\Eqp1241.obj" \
	"$(INTDIR)\Eqp1241L.obj" \
	"$(INTDIR)\Eqp1241S.obj" \
	"$(INTDIR)\Eqp18A.obj" \
	"$(INTDIR)\Eqp18C.obj" \
	"$(INTDIR)\Eqp251.obj" \
	"$(INTDIR)\EqpAAD.obj" \
	"$(INTDIR)\EqpAcco.obj" \
	"$(INTDIR)\EqpAudi.obj" \
	"$(INTDIR)\EqpCA150.obj" \
	"$(INTDIR)\EqpCV24Card.obj" \
	"$(INTDIR)\EqpMAT.obj" \
	"$(INTDIR)\eqpMATCOM.obj" \
	"$(INTDIR)\EqpStd.obj" \
	"$(INTDIR)\EqpTemp.obj" \
	"$(INTDIR)\EqpTORCard.obj" \
	"$(INTDIR)\EQUIP.OBJ" \
	"$(INTDIR)\EquipED42.obj" \
	"$(INTDIR)\EquipM1752.obj" \
	"$(INTDIR)\EquipTest.obj" \
	"$(INTDIR)\PARAMSIM.OBJ" \
	"$(INTDIR)\SEQUENCE.OBJ" \
	"$(INTDIR)\SYNCHRO.OBJ" \
	"$(INTDIR)\p_1225.obj" \
	"$(INTDIR)\P_1236.OBJ" \
	"$(INTDIR)\P_1237.OBJ" \
	"$(INTDIR)\P_1241.OBJ" \
	"$(INTDIR)\P_18A.OBJ" \
	"$(INTDIR)\P_251.OBJ" \
	"$(INTDIR)\p_AAD.obj" \
	"$(INTDIR)\p_CA150.obj" \
	"$(INTDIR)\p_CV24Card.obj" \
	"$(INTDIR)\p_ED42.obj" \
	"$(INTDIR)\p_MAT.obj" \
	"$(INTDIR)\p_MatCom.obj" \
	"$(INTDIR)\p_temp.obj" \
	"$(INTDIR)\p_Test.obj" \
	"$(INTDIR)\p_TORCard.obj" \
	"$(INTDIR)\p_TRC1752.obj" \
	"$(INTDIR)\PORT.OBJ" \
	"$(INTDIR)\PROT_ACC.OBJ" \
	"$(INTDIR)\PROT_AUD.OBJ" \
	"$(INTDIR)\PROT_STD.OBJ" \
	"$(INTDIR)\PROTO.OBJ" \
	"$(INTDIR)\DIV_FIC.OBJ" \
	"$(INTDIR)\DIV_TMP.OBJ" \
	"$(INTDIR)\TABLE.OBJ" \
	"$(INTDIR)\TACHE.OBJ" \
	"$(INTDIR)\sicomex.res"

"$(OUTDIR)\sicomex.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ELSEIF  "$(CFG)" == "sicomex - Win32 Release"

OUTDIR=c:\Sicomex
INTDIR=c:\tmp\Sicomex
# Begin Custom Macros
OutDir=c:\Sicomex
# End Custom Macros

ALL : "$(OUTDIR)\sicomex.exe" "$(OUTDIR)\sicomex.bsc"


CLEAN :
	-@erase "$(INTDIR)\AppelAle.obj"
	-@erase "$(INTDIR)\AppelAle.sbr"
	-@erase "$(INTDIR)\DIODE.OBJ"
	-@erase "$(INTDIR)\DIODE.SBR"
	-@erase "$(INTDIR)\DIV_FIC.OBJ"
	-@erase "$(INTDIR)\DIV_FIC.SBR"
	-@erase "$(INTDIR)\DIV_TMP.OBJ"
	-@erase "$(INTDIR)\DIV_TMP.SBR"
	-@erase "$(INTDIR)\DLG1236.OBJ"
	-@erase "$(INTDIR)\DLG1236.SBR"
	-@erase "$(INTDIR)\dlg1236l.obj"
	-@erase "$(INTDIR)\dlg1236l.sbr"
	-@erase "$(INTDIR)\dlg1236s.obj"
	-@erase "$(INTDIR)\dlg1236s.sbr"
	-@erase "$(INTDIR)\dlg1237.obj"
	-@erase "$(INTDIR)\dlg1237.sbr"
	-@erase "$(INTDIR)\dlg1237l.obj"
	-@erase "$(INTDIR)\dlg1237l.sbr"
	-@erase "$(INTDIR)\dlg1237s.obj"
	-@erase "$(INTDIR)\dlg1237s.sbr"
	-@erase "$(INTDIR)\DLG1241.OBJ"
	-@erase "$(INTDIR)\DLG1241.SBR"
	-@erase "$(INTDIR)\DLG1241L.OBJ"
	-@erase "$(INTDIR)\DLG1241L.SBR"
	-@erase "$(INTDIR)\dlg1241s.obj"
	-@erase "$(INTDIR)\dlg1241s.sbr"
	-@erase "$(INTDIR)\Dlg18C.obj"
	-@erase "$(INTDIR)\Dlg18C.sbr"
	-@erase "$(INTDIR)\dlg251.obj"
	-@erase "$(INTDIR)\dlg251.sbr"
	-@erase "$(INTDIR)\DLGaad_20_4.obj"
	-@erase "$(INTDIR)\DLGaad_20_4.sbr"
	-@erase "$(INTDIR)\DLGaad_20_8.obj"
	-@erase "$(INTDIR)\DLGaad_20_8.sbr"
	-@erase "$(INTDIR)\DLGACCOR.OBJ"
	-@erase "$(INTDIR)\DLGACCOR.SBR"
	-@erase "$(INTDIR)\dlgaccue.obj"
	-@erase "$(INTDIR)\dlgaccue.sbr"
	-@erase "$(INTDIR)\DLGAFFEC.OBJ"
	-@erase "$(INTDIR)\DLGAFFEC.SBR"
	-@erase "$(INTDIR)\DLGAIDE.OBJ"
	-@erase "$(INTDIR)\DLGAIDE.SBR"
	-@erase "$(INTDIR)\DLGAPROP.OBJ"
	-@erase "$(INTDIR)\DLGAPROP.SBR"
	-@erase "$(INTDIR)\DLGAUDIO.OBJ"
	-@erase "$(INTDIR)\DLGAUDIO.SBR"
	-@erase "$(INTDIR)\DLGCA150.obj"
	-@erase "$(INTDIR)\DLGCA150.sbr"
	-@erase "$(INTDIR)\dlgCommutationMatrix.obj"
	-@erase "$(INTDIR)\dlgCommutationMatrix.sbr"
	-@erase "$(INTDIR)\DLGCONFI.OBJ"
	-@erase "$(INTDIR)\DLGCONFI.SBR"
	-@erase "$(INTDIR)\DLGCV24Card.obj"
	-@erase "$(INTDIR)\DLGCV24Card.sbr"
	-@erase "$(INTDIR)\DlgED42.obj"
	-@erase "$(INTDIR)\DlgED42.sbr"
	-@erase "$(INTDIR)\DLGEMHF.OBJ"
	-@erase "$(INTDIR)\DLGEMHF.SBR"
	-@erase "$(INTDIR)\dlgemrec.obj"
	-@erase "$(INTDIR)\dlgemrec.sbr"
	-@erase "$(INTDIR)\DLGEQUIP.OBJ"
	-@erase "$(INTDIR)\DLGEQUIP.SBR"
	-@erase "$(INTDIR)\DLGmatL11.obj"
	-@erase "$(INTDIR)\DLGmatL11.sbr"
	-@erase "$(INTDIR)\DLGmatSPIN.obj"
	-@erase "$(INTDIR)\DLGmatSPIN.sbr"
	-@erase "$(INTDIR)\DlgModeOperationnel.obj"
	-@erase "$(INTDIR)\DlgModeOperationnel.sbr"
	-@erase "$(INTDIR)\DLGOUTIL.OBJ"
	-@erase "$(INTDIR)\DLGOUTIL.SBR"
	-@erase "$(INTDIR)\DLGSTDHF.OBJ"
	-@erase "$(INTDIR)\DLGSTDHF.SBR"
	-@erase "$(INTDIR)\DLGtemp.obj"
	-@erase "$(INTDIR)\DLGtemp.sbr"
	-@erase "$(INTDIR)\DLGTest1.obj"
	-@erase "$(INTDIR)\DLGTest1.sbr"
	-@erase "$(INTDIR)\DLGTORCard.obj"
	-@erase "$(INTDIR)\DLGTORCard.sbr"
	-@erase "$(INTDIR)\DlgTRC1752.obj"
	-@erase "$(INTDIR)\DlgTRC1752.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ALE.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ALE.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ARQ.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ARQ.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_CONF.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_CONF.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ENV.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_ENV.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_RDO.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_RDO.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_STST.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_CONF_STST.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_OPS.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_OPS.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_CALL.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_CALL.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_LP.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_LP.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_SYS.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_SYS.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_TAB.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_TAB.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_CONF.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_CONF.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ENV.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_ENV.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_ASS.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_ASS.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_BF.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_BF.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_LIAS.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_LIAS.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_PIL.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_PIL.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_TC.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_TC.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A1.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A1.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A2.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A2.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B1.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B1.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B2.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B2.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_TST.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STA_TST.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STST.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_STST.sbr"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_TC.obj"
	-@erase "$(INTDIR)\DlgTRC1752_MOD_PROG_TC.sbr"
	-@erase "$(INTDIR)\Eqp1225.obj"
	-@erase "$(INTDIR)\Eqp1225.sbr"
	-@erase "$(INTDIR)\Eqp1236.obj"
	-@erase "$(INTDIR)\Eqp1236.sbr"
	-@erase "$(INTDIR)\Eqp1236L.obj"
	-@erase "$(INTDIR)\Eqp1236L.sbr"
	-@erase "$(INTDIR)\Eqp1236S.obj"
	-@erase "$(INTDIR)\Eqp1236S.sbr"
	-@erase "$(INTDIR)\Eqp1237.obj"
	-@erase "$(INTDIR)\Eqp1237.sbr"
	-@erase "$(INTDIR)\Eqp1237L.obj"
	-@erase "$(INTDIR)\Eqp1237L.sbr"
	-@erase "$(INTDIR)\Eqp1237S.obj"
	-@erase "$(INTDIR)\Eqp1237S.sbr"
	-@erase "$(INTDIR)\Eqp1241.obj"
	-@erase "$(INTDIR)\Eqp1241.sbr"
	-@erase "$(INTDIR)\Eqp1241L.obj"
	-@erase "$(INTDIR)\Eqp1241L.sbr"
	-@erase "$(INTDIR)\Eqp1241S.obj"
	-@erase "$(INTDIR)\Eqp1241S.sbr"
	-@erase "$(INTDIR)\Eqp18A.obj"
	-@erase "$(INTDIR)\Eqp18A.sbr"
	-@erase "$(INTDIR)\Eqp18C.obj"
	-@erase "$(INTDIR)\Eqp18C.sbr"
	-@erase "$(INTDIR)\Eqp251.obj"
	-@erase "$(INTDIR)\Eqp251.sbr"
	-@erase "$(INTDIR)\EqpAAD.obj"
	-@erase "$(INTDIR)\EqpAAD.sbr"
	-@erase "$(INTDIR)\EqpAcco.obj"
	-@erase "$(INTDIR)\EqpAcco.sbr"
	-@erase "$(INTDIR)\EqpAudi.obj"
	-@erase "$(INTDIR)\EqpAudi.sbr"
	-@erase "$(INTDIR)\EqpCA150.obj"
	-@erase "$(INTDIR)\EqpCA150.sbr"
	-@erase "$(INTDIR)\EqpCV24Card.obj"
	-@erase "$(INTDIR)\EqpCV24Card.sbr"
	-@erase "$(INTDIR)\EqpMAT.obj"
	-@erase "$(INTDIR)\EqpMAT.sbr"
	-@erase "$(INTDIR)\eqpMATCOM.obj"
	-@erase "$(INTDIR)\eqpMATCOM.sbr"
	-@erase "$(INTDIR)\EqpStd.obj"
	-@erase "$(INTDIR)\EqpStd.sbr"
	-@erase "$(INTDIR)\EqpTemp.obj"
	-@erase "$(INTDIR)\EqpTemp.sbr"
	-@erase "$(INTDIR)\EqpTORCard.obj"
	-@erase "$(INTDIR)\EqpTORCard.sbr"
	-@erase "$(INTDIR)\EQUIP.OBJ"
	-@erase "$(INTDIR)\EQUIP.SBR"
	-@erase "$(INTDIR)\EquipED42.obj"
	-@erase "$(INTDIR)\EquipED42.sbr"
	-@erase "$(INTDIR)\EquipM1752.obj"
	-@erase "$(INTDIR)\EquipM1752.sbr"
	-@erase "$(INTDIR)\EquipTest.obj"
	-@erase "$(INTDIR)\EquipTest.sbr"
	-@erase "$(INTDIR)\ICONE.OBJ"
	-@erase "$(INTDIR)\ICONE.SBR"
	-@erase "$(INTDIR)\IDD_Mode_Operationnel.obj"
	-@erase "$(INTDIR)\IDD_Mode_Operationnel.sbr"
	-@erase "$(INTDIR)\INTER.OBJ"
	-@erase "$(INTDIR)\INTER.SBR"
	-@erase "$(INTDIR)\MyEdit.obj"
	-@erase "$(INTDIR)\MyEdit.sbr"
	-@erase "$(INTDIR)\OUTIL.OBJ"
	-@erase "$(INTDIR)\OUTIL.SBR"
	-@erase "$(INTDIR)\p_1225.obj"
	-@erase "$(INTDIR)\p_1225.sbr"
	-@erase "$(INTDIR)\P_1236.OBJ"
	-@erase "$(INTDIR)\P_1236.SBR"
	-@erase "$(INTDIR)\P_1237.OBJ"
	-@erase "$(INTDIR)\P_1237.SBR"
	-@erase "$(INTDIR)\P_1241.OBJ"
	-@erase "$(INTDIR)\P_1241.SBR"
	-@erase "$(INTDIR)\P_18A.OBJ"
	-@erase "$(INTDIR)\P_18A.SBR"
	-@erase "$(INTDIR)\P_251.OBJ"
	-@erase "$(INTDIR)\P_251.SBR"
	-@erase "$(INTDIR)\p_AAD.obj"
	-@erase "$(INTDIR)\p_AAD.sbr"
	-@erase "$(INTDIR)\p_CA150.obj"
	-@erase "$(INTDIR)\p_CA150.sbr"
	-@erase "$(INTDIR)\p_CV24Card.obj"
	-@erase "$(INTDIR)\p_CV24Card.sbr"
	-@erase "$(INTDIR)\p_ED42.obj"
	-@erase "$(INTDIR)\p_ED42.sbr"
	-@erase "$(INTDIR)\p_MAT.obj"
	-@erase "$(INTDIR)\p_MAT.sbr"
	-@erase "$(INTDIR)\p_MatCom.obj"
	-@erase "$(INTDIR)\p_MatCom.sbr"
	-@erase "$(INTDIR)\p_temp.obj"
	-@erase "$(INTDIR)\p_temp.sbr"
	-@erase "$(INTDIR)\p_Test.obj"
	-@erase "$(INTDIR)\p_Test.sbr"
	-@erase "$(INTDIR)\p_TORCard.obj"
	-@erase "$(INTDIR)\p_TORCard.sbr"
	-@erase "$(INTDIR)\p_TRC1752.obj"
	-@erase "$(INTDIR)\p_TRC1752.sbr"
	-@erase "$(INTDIR)\PARAMSIM.OBJ"
	-@erase "$(INTDIR)\PARAMSIM.SBR"
	-@erase "$(INTDIR)\PORT.OBJ"
	-@erase "$(INTDIR)\PORT.SBR"
	-@erase "$(INTDIR)\PROT_ACC.OBJ"
	-@erase "$(INTDIR)\PROT_ACC.SBR"
	-@erase "$(INTDIR)\PROT_AUD.OBJ"
	-@erase "$(INTDIR)\PROT_AUD.SBR"
	-@erase "$(INTDIR)\PROT_STD.OBJ"
	-@erase "$(INTDIR)\PROT_STD.SBR"
	-@erase "$(INTDIR)\PROTO.OBJ"
	-@erase "$(INTDIR)\PROTO.SBR"
	-@erase "$(INTDIR)\SEQUENCE.OBJ"
	-@erase "$(INTDIR)\SEQUENCE.SBR"
	-@erase "$(INTDIR)\sicomex.obj"
	-@erase "$(INTDIR)\sicomex.pch"
	-@erase "$(INTDIR)\sicomex.res"
	-@erase "$(INTDIR)\sicomex.sbr"
	-@erase "$(INTDIR)\STDAFX.OBJ"
	-@erase "$(INTDIR)\STDAFX.SBR"
	-@erase "$(INTDIR)\SYNCHRO.OBJ"
	-@erase "$(INTDIR)\SYNCHRO.SBR"
	-@erase "$(INTDIR)\TABLE.OBJ"
	-@erase "$(INTDIR)\TABLE.SBR"
	-@erase "$(INTDIR)\TACHE.OBJ"
	-@erase "$(INTDIR)\TACHE.SBR"
	-@erase "$(INTDIR)\vc60.idb"
	-@erase "$(INTDIR)\XTabCtrl.obj"
	-@erase "$(INTDIR)\XTabCtrl.sbr"
	-@erase "$(OUTDIR)\sicomex.bsc"
	-@erase "$(OUTDIR)\sicomex.exe"

"$(OUTDIR)" :
    if not exist "$(OUTDIR)/$(NULL)" mkdir "$(OUTDIR)"

"$(INTDIR)" :
    if not exist "$(INTDIR)/$(NULL)" mkdir "$(INTDIR)"

CPP=cl.exe
CPP_PROJ=/nologo /MT /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\sicomex.pch" /Yu"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

.c{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.obj::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.c{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cpp{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

.cxx{$(INTDIR)}.sbr::
   $(CPP) @<<
   $(CPP_PROJ) $< 
<<

MTL=midl.exe
MTL_PROJ=/mktyplib203 
RSC=rc.exe
RSC_PROJ=/l 0x40c /fo"$(INTDIR)\sicomex.res" /d "NDEBUG" 
BSC32=bscmake.exe
BSC32_FLAGS=/nologo /o"$(OUTDIR)\sicomex.bsc" 
BSC32_SBRS= \
	"$(INTDIR)\DlgModeOperationnel.sbr" \
	"$(INTDIR)\IDD_Mode_Operationnel.sbr" \
	"$(INTDIR)\MyEdit.sbr" \
	"$(INTDIR)\sicomex.sbr" \
	"$(INTDIR)\STDAFX.SBR" \
	"$(INTDIR)\DlgTRC1752_MOD.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ALE.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ARQ.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_CONF.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ENV.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_RDO.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_STST.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_OPS.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_CALL.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_LP.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_SYS.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_TAB.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_CONF.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ENV.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_ASS.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_BF.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_LIAS.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_PIL.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_TC.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A1.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A2.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B1.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B2.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_TST.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STST.sbr" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_TC.sbr" \
	"$(INTDIR)\DLG1236.SBR" \
	"$(INTDIR)\dlg1236l.sbr" \
	"$(INTDIR)\dlg1236s.sbr" \
	"$(INTDIR)\dlg1237.sbr" \
	"$(INTDIR)\dlg1237l.sbr" \
	"$(INTDIR)\dlg1237s.sbr" \
	"$(INTDIR)\DLG1241.SBR" \
	"$(INTDIR)\DLG1241L.SBR" \
	"$(INTDIR)\dlg1241s.sbr" \
	"$(INTDIR)\Dlg18C.sbr" \
	"$(INTDIR)\dlg251.sbr" \
	"$(INTDIR)\DLGaad_20_4.sbr" \
	"$(INTDIR)\DLGaad_20_8.sbr" \
	"$(INTDIR)\DLGACCOR.SBR" \
	"$(INTDIR)\dlgaccue.sbr" \
	"$(INTDIR)\DLGAFFEC.SBR" \
	"$(INTDIR)\DLGAIDE.SBR" \
	"$(INTDIR)\DLGAPROP.SBR" \
	"$(INTDIR)\DLGAUDIO.SBR" \
	"$(INTDIR)\DLGCA150.sbr" \
	"$(INTDIR)\dlgCommutationMatrix.sbr" \
	"$(INTDIR)\DLGCONFI.SBR" \
	"$(INTDIR)\DLGCV24Card.sbr" \
	"$(INTDIR)\DlgED42.sbr" \
	"$(INTDIR)\DLGEMHF.SBR" \
	"$(INTDIR)\dlgemrec.sbr" \
	"$(INTDIR)\DLGEQUIP.SBR" \
	"$(INTDIR)\DLGmatL11.sbr" \
	"$(INTDIR)\DLGmatSPIN.sbr" \
	"$(INTDIR)\DLGOUTIL.SBR" \
	"$(INTDIR)\DLGSTDHF.SBR" \
	"$(INTDIR)\DLGtemp.sbr" \
	"$(INTDIR)\DLGTest1.sbr" \
	"$(INTDIR)\DLGTORCard.sbr" \
	"$(INTDIR)\DlgTRC1752.sbr" \
	"$(INTDIR)\DIODE.SBR" \
	"$(INTDIR)\ICONE.SBR" \
	"$(INTDIR)\INTER.SBR" \
	"$(INTDIR)\OUTIL.SBR" \
	"$(INTDIR)\XTabCtrl.sbr" \
	"$(INTDIR)\AppelAle.sbr" \
	"$(INTDIR)\Eqp1225.sbr" \
	"$(INTDIR)\Eqp1236.sbr" \
	"$(INTDIR)\Eqp1236L.sbr" \
	"$(INTDIR)\Eqp1236S.sbr" \
	"$(INTDIR)\Eqp1237.sbr" \
	"$(INTDIR)\Eqp1237L.sbr" \
	"$(INTDIR)\Eqp1237S.sbr" \
	"$(INTDIR)\Eqp1241.sbr" \
	"$(INTDIR)\Eqp1241L.sbr" \
	"$(INTDIR)\Eqp1241S.sbr" \
	"$(INTDIR)\Eqp18A.sbr" \
	"$(INTDIR)\Eqp18C.sbr" \
	"$(INTDIR)\Eqp251.sbr" \
	"$(INTDIR)\EqpAAD.sbr" \
	"$(INTDIR)\EqpAcco.sbr" \
	"$(INTDIR)\EqpAudi.sbr" \
	"$(INTDIR)\EqpCA150.sbr" \
	"$(INTDIR)\EqpCV24Card.sbr" \
	"$(INTDIR)\EqpMAT.sbr" \
	"$(INTDIR)\eqpMATCOM.sbr" \
	"$(INTDIR)\EqpStd.sbr" \
	"$(INTDIR)\EqpTemp.sbr" \
	"$(INTDIR)\EqpTORCard.sbr" \
	"$(INTDIR)\EQUIP.SBR" \
	"$(INTDIR)\EquipED42.sbr" \
	"$(INTDIR)\EquipM1752.sbr" \
	"$(INTDIR)\EquipTest.sbr" \
	"$(INTDIR)\PARAMSIM.SBR" \
	"$(INTDIR)\SEQUENCE.SBR" \
	"$(INTDIR)\SYNCHRO.SBR" \
	"$(INTDIR)\p_1225.sbr" \
	"$(INTDIR)\P_1236.SBR" \
	"$(INTDIR)\P_1237.SBR" \
	"$(INTDIR)\P_1241.SBR" \
	"$(INTDIR)\P_18A.SBR" \
	"$(INTDIR)\P_251.SBR" \
	"$(INTDIR)\p_AAD.sbr" \
	"$(INTDIR)\p_CA150.sbr" \
	"$(INTDIR)\p_CV24Card.sbr" \
	"$(INTDIR)\p_ED42.sbr" \
	"$(INTDIR)\p_MAT.sbr" \
	"$(INTDIR)\p_MatCom.sbr" \
	"$(INTDIR)\p_temp.sbr" \
	"$(INTDIR)\p_Test.sbr" \
	"$(INTDIR)\p_TORCard.sbr" \
	"$(INTDIR)\p_TRC1752.sbr" \
	"$(INTDIR)\PORT.SBR" \
	"$(INTDIR)\PROT_ACC.SBR" \
	"$(INTDIR)\PROT_AUD.SBR" \
	"$(INTDIR)\PROT_STD.SBR" \
	"$(INTDIR)\PROTO.SBR" \
	"$(INTDIR)\DIV_FIC.SBR" \
	"$(INTDIR)\DIV_TMP.SBR" \
	"$(INTDIR)\TABLE.SBR" \
	"$(INTDIR)\TACHE.SBR"

"$(OUTDIR)\sicomex.bsc" : "$(OUTDIR)" $(BSC32_SBRS)
    $(BSC32) @<<
  $(BSC32_FLAGS) $(BSC32_SBRS)
<<

LINK32=link.exe
LINK32_FLAGS=winmm.lib /nologo /subsystem:windows /incremental:no /pdb:"$(OUTDIR)\sicomex.pdb" /machine:I386 /out:"$(OUTDIR)\sicomex.exe" 
LINK32_OBJS= \
	"$(INTDIR)\DlgModeOperationnel.obj" \
	"$(INTDIR)\IDD_Mode_Operationnel.obj" \
	"$(INTDIR)\MyEdit.obj" \
	"$(INTDIR)\sicomex.obj" \
	"$(INTDIR)\STDAFX.OBJ" \
	"$(INTDIR)\DlgTRC1752_MOD.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ALE.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ARQ.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_CONF.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_ENV.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_RDO.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_CONF_STST.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_OPS.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_CALL.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_LP.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_SYS.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_TAB.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_CONF.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_ENV.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_ASS.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_BF.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_LIAS.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_PIL.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_TC.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A1.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A2.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B1.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B2.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_TST.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_STST.obj" \
	"$(INTDIR)\DlgTRC1752_MOD_PROG_TC.obj" \
	"$(INTDIR)\DLG1236.OBJ" \
	"$(INTDIR)\dlg1236l.obj" \
	"$(INTDIR)\dlg1236s.obj" \
	"$(INTDIR)\dlg1237.obj" \
	"$(INTDIR)\dlg1237l.obj" \
	"$(INTDIR)\dlg1237s.obj" \
	"$(INTDIR)\DLG1241.OBJ" \
	"$(INTDIR)\DLG1241L.OBJ" \
	"$(INTDIR)\dlg1241s.obj" \
	"$(INTDIR)\Dlg18C.obj" \
	"$(INTDIR)\dlg251.obj" \
	"$(INTDIR)\DLGaad_20_4.obj" \
	"$(INTDIR)\DLGaad_20_8.obj" \
	"$(INTDIR)\DLGACCOR.OBJ" \
	"$(INTDIR)\dlgaccue.obj" \
	"$(INTDIR)\DLGAFFEC.OBJ" \
	"$(INTDIR)\DLGAIDE.OBJ" \
	"$(INTDIR)\DLGAPROP.OBJ" \
	"$(INTDIR)\DLGAUDIO.OBJ" \
	"$(INTDIR)\DLGCA150.obj" \
	"$(INTDIR)\dlgCommutationMatrix.obj" \
	"$(INTDIR)\DLGCONFI.OBJ" \
	"$(INTDIR)\DLGCV24Card.obj" \
	"$(INTDIR)\DlgED42.obj" \
	"$(INTDIR)\DLGEMHF.OBJ" \
	"$(INTDIR)\dlgemrec.obj" \
	"$(INTDIR)\DLGEQUIP.OBJ" \
	"$(INTDIR)\DLGmatL11.obj" \
	"$(INTDIR)\DLGmatSPIN.obj" \
	"$(INTDIR)\DLGOUTIL.OBJ" \
	"$(INTDIR)\DLGSTDHF.OBJ" \
	"$(INTDIR)\DLGtemp.obj" \
	"$(INTDIR)\DLGTest1.obj" \
	"$(INTDIR)\DLGTORCard.obj" \
	"$(INTDIR)\DlgTRC1752.obj" \
	"$(INTDIR)\DIODE.OBJ" \
	"$(INTDIR)\ICONE.OBJ" \
	"$(INTDIR)\INTER.OBJ" \
	"$(INTDIR)\OUTIL.OBJ" \
	"$(INTDIR)\XTabCtrl.obj" \
	"$(INTDIR)\AppelAle.obj" \
	"$(INTDIR)\Eqp1225.obj" \
	"$(INTDIR)\Eqp1236.obj" \
	"$(INTDIR)\Eqp1236L.obj" \
	"$(INTDIR)\Eqp1236S.obj" \
	"$(INTDIR)\Eqp1237.obj" \
	"$(INTDIR)\Eqp1237L.obj" \
	"$(INTDIR)\Eqp1237S.obj" \
	"$(INTDIR)\Eqp1241.obj" \
	"$(INTDIR)\Eqp1241L.obj" \
	"$(INTDIR)\Eqp1241S.obj" \
	"$(INTDIR)\Eqp18A.obj" \
	"$(INTDIR)\Eqp18C.obj" \
	"$(INTDIR)\Eqp251.obj" \
	"$(INTDIR)\EqpAAD.obj" \
	"$(INTDIR)\EqpAcco.obj" \
	"$(INTDIR)\EqpAudi.obj" \
	"$(INTDIR)\EqpCA150.obj" \
	"$(INTDIR)\EqpCV24Card.obj" \
	"$(INTDIR)\EqpMAT.obj" \
	"$(INTDIR)\eqpMATCOM.obj" \
	"$(INTDIR)\EqpStd.obj" \
	"$(INTDIR)\EqpTemp.obj" \
	"$(INTDIR)\EqpTORCard.obj" \
	"$(INTDIR)\EQUIP.OBJ" \
	"$(INTDIR)\EquipED42.obj" \
	"$(INTDIR)\EquipM1752.obj" \
	"$(INTDIR)\EquipTest.obj" \
	"$(INTDIR)\PARAMSIM.OBJ" \
	"$(INTDIR)\SEQUENCE.OBJ" \
	"$(INTDIR)\SYNCHRO.OBJ" \
	"$(INTDIR)\p_1225.obj" \
	"$(INTDIR)\P_1236.OBJ" \
	"$(INTDIR)\P_1237.OBJ" \
	"$(INTDIR)\P_1241.OBJ" \
	"$(INTDIR)\P_18A.OBJ" \
	"$(INTDIR)\P_251.OBJ" \
	"$(INTDIR)\p_AAD.obj" \
	"$(INTDIR)\p_CA150.obj" \
	"$(INTDIR)\p_CV24Card.obj" \
	"$(INTDIR)\p_ED42.obj" \
	"$(INTDIR)\p_MAT.obj" \
	"$(INTDIR)\p_MatCom.obj" \
	"$(INTDIR)\p_temp.obj" \
	"$(INTDIR)\p_Test.obj" \
	"$(INTDIR)\p_TORCard.obj" \
	"$(INTDIR)\p_TRC1752.obj" \
	"$(INTDIR)\PORT.OBJ" \
	"$(INTDIR)\PROT_ACC.OBJ" \
	"$(INTDIR)\PROT_AUD.OBJ" \
	"$(INTDIR)\PROT_STD.OBJ" \
	"$(INTDIR)\PROTO.OBJ" \
	"$(INTDIR)\DIV_FIC.OBJ" \
	"$(INTDIR)\DIV_TMP.OBJ" \
	"$(INTDIR)\TABLE.OBJ" \
	"$(INTDIR)\TACHE.OBJ" \
	"$(INTDIR)\sicomex.res"

"$(OUTDIR)\sicomex.exe" : "$(OUTDIR)" $(DEF_FILE) $(LINK32_OBJS)
    $(LINK32) @<<
  $(LINK32_FLAGS) $(LINK32_OBJS)
<<

!ENDIF 


!IF "$(NO_EXTERNAL_DEPS)" != "1"
!IF EXISTS("sicomex.dep")
!INCLUDE "sicomex.dep"
!ELSE 
!MESSAGE Warning: cannot find "sicomex.dep"
!ENDIF 
!ENDIF 


!IF "$(CFG)" == "sicomex - Win32 Debug" || "$(CFG)" == "sicomex - Win32 Release"
SOURCE=.\DlgModeOperationnel.cpp

"$(INTDIR)\DlgModeOperationnel.obj"	"$(INTDIR)\DlgModeOperationnel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\IDD_Mode_Operationnel.cpp

"$(INTDIR)\IDD_Mode_Operationnel.obj"	"$(INTDIR)\IDD_Mode_Operationnel.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\MyEdit.cpp

"$(INTDIR)\MyEdit.obj"	"$(INTDIR)\MyEdit.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\sicomex.CPP

"$(INTDIR)\sicomex.obj"	"$(INTDIR)\sicomex.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\sicomex.RC

"$(INTDIR)\sicomex.res" : $(SOURCE) "$(INTDIR)"
	$(RSC) $(RSC_PROJ) $(SOURCE)


SOURCE=.\STDAFX.CPP

!IF  "$(CFG)" == "sicomex - Win32 Debug"

CPP_SWITCHES=/nologo /Gz /MTd /Gm /GX /ZI /Od /I "." /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\sicomex.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\STDAFX.OBJ"	"$(INTDIR)\STDAFX.SBR"	"$(INTDIR)\sicomex.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ELSEIF  "$(CFG)" == "sicomex - Win32 Release"

CPP_SWITCHES=/nologo /MT /W3 /GX /O2 /I "." /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /Fr"$(INTDIR)\\" /Fp"$(INTDIR)\sicomex.pch" /Yc"stdafx.h" /Fo"$(INTDIR)\\" /Fd"$(INTDIR)\\" /FD /c 

"$(INTDIR)\STDAFX.OBJ"	"$(INTDIR)\STDAFX.SBR"	"$(INTDIR)\sicomex.pch" : $(SOURCE) "$(INTDIR)"
	$(CPP) @<<
  $(CPP_SWITCHES) $(SOURCE)
<<


!ENDIF 

SOURCE=.\DlgTRC1752_MOD.cpp

"$(INTDIR)\DlgTRC1752_MOD.obj"	"$(INTDIR)\DlgTRC1752_MOD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_CONF.cpp

"$(INTDIR)\DlgTRC1752_MOD_CONF.obj"	"$(INTDIR)\DlgTRC1752_MOD_CONF.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_CONF_ALE.cpp

"$(INTDIR)\DlgTRC1752_MOD_CONF_ALE.obj"	"$(INTDIR)\DlgTRC1752_MOD_CONF_ALE.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_CONF_ARQ.cpp

"$(INTDIR)\DlgTRC1752_MOD_CONF_ARQ.obj"	"$(INTDIR)\DlgTRC1752_MOD_CONF_ARQ.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_CONF_CONF.cpp

"$(INTDIR)\DlgTRC1752_MOD_CONF_CONF.obj"	"$(INTDIR)\DlgTRC1752_MOD_CONF_CONF.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_CONF_ENV.cpp

"$(INTDIR)\DlgTRC1752_MOD_CONF_ENV.obj"	"$(INTDIR)\DlgTRC1752_MOD_CONF_ENV.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_CONF_RDO.cpp

"$(INTDIR)\DlgTRC1752_MOD_CONF_RDO.obj"	"$(INTDIR)\DlgTRC1752_MOD_CONF_RDO.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_CONF_STST.cpp

"$(INTDIR)\DlgTRC1752_MOD_CONF_STST.obj"	"$(INTDIR)\DlgTRC1752_MOD_CONF_STST.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_OPS.cpp

"$(INTDIR)\DlgTRC1752_MOD_OPS.obj"	"$(INTDIR)\DlgTRC1752_MOD_OPS.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_ALE.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_ALE_CALL.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_CALL.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_CALL.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_ALE_LP.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_LP.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_LP.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_ALE_SYS.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_SYS.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_SYS.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_ALE_TAB.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_TAB.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_ALE_TAB.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_CONF.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_CONF.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_CONF.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_ENV.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_ENV.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_ENV.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_INTF.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_INTF_ASS.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_ASS.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_ASS.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_INTF_BF.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_BF.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_BF.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_INTF_LIAS.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_LIAS.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_LIAS.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_INTF_PIL.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_PIL.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_PIL.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_INTF_TC.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_TC.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_INTF_TC.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_STA.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_STA.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_STA_A1.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A1.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_STA_A2.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A2.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_A2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_STA_B1.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B1.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_STA_B2.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B2.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_B2.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_STA_TST.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_TST.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_STA_TST.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_STST.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_STST.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_STST.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752_MOD_PROG_TC.cpp

"$(INTDIR)\DlgTRC1752_MOD_PROG_TC.obj"	"$(INTDIR)\DlgTRC1752_MOD_PROG_TC.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLG1236.CPP

"$(INTDIR)\DLG1236.OBJ"	"$(INTDIR)\DLG1236.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\dlg1236l.cpp

"$(INTDIR)\dlg1236l.obj"	"$(INTDIR)\dlg1236l.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\dlg1236s.cpp

"$(INTDIR)\dlg1236s.obj"	"$(INTDIR)\dlg1236s.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\dlg1237.cpp

"$(INTDIR)\dlg1237.obj"	"$(INTDIR)\dlg1237.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\dlg1237l.cpp

"$(INTDIR)\dlg1237l.obj"	"$(INTDIR)\dlg1237l.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\dlg1237s.cpp

"$(INTDIR)\dlg1237s.obj"	"$(INTDIR)\dlg1237s.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLG1241.CPP

"$(INTDIR)\DLG1241.OBJ"	"$(INTDIR)\DLG1241.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLG1241L.CPP

"$(INTDIR)\DLG1241L.OBJ"	"$(INTDIR)\DLG1241L.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\dlg1241s.cpp

"$(INTDIR)\dlg1241s.obj"	"$(INTDIR)\dlg1241s.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\Dlg18C.CPP

"$(INTDIR)\Dlg18C.obj"	"$(INTDIR)\Dlg18C.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\dlg251.cpp

"$(INTDIR)\dlg251.obj"	"$(INTDIR)\dlg251.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGaad_20_4.cpp

"$(INTDIR)\DLGaad_20_4.obj"	"$(INTDIR)\DLGaad_20_4.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGaad_20_8.cpp

"$(INTDIR)\DLGaad_20_8.obj"	"$(INTDIR)\DLGaad_20_8.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGACCOR.CPP

"$(INTDIR)\DLGACCOR.OBJ"	"$(INTDIR)\DLGACCOR.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\dlgaccue.cpp

"$(INTDIR)\dlgaccue.obj"	"$(INTDIR)\dlgaccue.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGAFFEC.CPP

"$(INTDIR)\DLGAFFEC.OBJ"	"$(INTDIR)\DLGAFFEC.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGAIDE.CPP

"$(INTDIR)\DLGAIDE.OBJ"	"$(INTDIR)\DLGAIDE.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGAPROP.CPP

"$(INTDIR)\DLGAPROP.OBJ"	"$(INTDIR)\DLGAPROP.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGAUDIO.CPP

"$(INTDIR)\DLGAUDIO.OBJ"	"$(INTDIR)\DLGAUDIO.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGCA150.cpp

"$(INTDIR)\DLGCA150.obj"	"$(INTDIR)\DLGCA150.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\dlgCommutationMatrix.cpp

"$(INTDIR)\dlgCommutationMatrix.obj"	"$(INTDIR)\dlgCommutationMatrix.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGCONFI.CPP

"$(INTDIR)\DLGCONFI.OBJ"	"$(INTDIR)\DLGCONFI.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGCV24Card.cpp

"$(INTDIR)\DLGCV24Card.obj"	"$(INTDIR)\DLGCV24Card.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgED42.cpp

"$(INTDIR)\DlgED42.obj"	"$(INTDIR)\DlgED42.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGEMHF.CPP

"$(INTDIR)\DLGEMHF.OBJ"	"$(INTDIR)\DLGEMHF.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\dlgemrec.cpp

"$(INTDIR)\dlgemrec.obj"	"$(INTDIR)\dlgemrec.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGEQUIP.CPP

"$(INTDIR)\DLGEQUIP.OBJ"	"$(INTDIR)\DLGEQUIP.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGmatL11.cpp

"$(INTDIR)\DLGmatL11.obj"	"$(INTDIR)\DLGmatL11.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGmatSPIN.cpp

"$(INTDIR)\DLGmatSPIN.obj"	"$(INTDIR)\DLGmatSPIN.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGOUTIL.CPP

"$(INTDIR)\DLGOUTIL.OBJ"	"$(INTDIR)\DLGOUTIL.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGSTDHF.CPP

"$(INTDIR)\DLGSTDHF.OBJ"	"$(INTDIR)\DLGSTDHF.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGtemp.cpp

"$(INTDIR)\DLGtemp.obj"	"$(INTDIR)\DLGtemp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGTest1.cpp

"$(INTDIR)\DLGTest1.obj"	"$(INTDIR)\DLGTest1.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DLGTORCard.cpp

"$(INTDIR)\DLGTORCard.obj"	"$(INTDIR)\DLGTORCard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\DlgTRC1752.cpp

"$(INTDIR)\DlgTRC1752.obj"	"$(INTDIR)\DlgTRC1752.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\CUSTOM\DIODE.CPP

"$(INTDIR)\DIODE.OBJ"	"$(INTDIR)\DIODE.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CUSTOM\ICONE.CPP

"$(INTDIR)\ICONE.OBJ"	"$(INTDIR)\ICONE.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CUSTOM\INTER.CPP

"$(INTDIR)\INTER.OBJ"	"$(INTDIR)\INTER.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\CUSTOM\OUTIL.CPP

"$(INTDIR)\OUTIL.OBJ"	"$(INTDIR)\OUTIL.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\XTabCtrl.cpp

"$(INTDIR)\XTabCtrl.obj"	"$(INTDIR)\XTabCtrl.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"


SOURCE=.\equip\AppelAle.cpp

"$(INTDIR)\AppelAle.obj"	"$(INTDIR)\AppelAle.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp1225.cpp

"$(INTDIR)\Eqp1225.obj"	"$(INTDIR)\Eqp1225.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp1236.CPP

"$(INTDIR)\Eqp1236.obj"	"$(INTDIR)\Eqp1236.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp1236L.CPP

"$(INTDIR)\Eqp1236L.obj"	"$(INTDIR)\Eqp1236L.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp1236S.CPP

"$(INTDIR)\Eqp1236S.obj"	"$(INTDIR)\Eqp1236S.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp1237.CPP

"$(INTDIR)\Eqp1237.obj"	"$(INTDIR)\Eqp1237.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp1237L.CPP

"$(INTDIR)\Eqp1237L.obj"	"$(INTDIR)\Eqp1237L.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp1237S.CPP

"$(INTDIR)\Eqp1237S.obj"	"$(INTDIR)\Eqp1237S.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp1241.Cpp

"$(INTDIR)\Eqp1241.obj"	"$(INTDIR)\Eqp1241.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp1241L.Cpp

"$(INTDIR)\Eqp1241L.obj"	"$(INTDIR)\Eqp1241L.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp1241S.Cpp

"$(INTDIR)\Eqp1241S.obj"	"$(INTDIR)\Eqp1241S.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp18A.cpp

"$(INTDIR)\Eqp18A.obj"	"$(INTDIR)\Eqp18A.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp18C.cpp

"$(INTDIR)\Eqp18C.obj"	"$(INTDIR)\Eqp18C.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\Eqp251.Cpp

"$(INTDIR)\Eqp251.obj"	"$(INTDIR)\Eqp251.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\equip\EqpAAD.cpp

"$(INTDIR)\EqpAAD.obj"	"$(INTDIR)\EqpAAD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\EqpAcco.CPP

"$(INTDIR)\EqpAcco.obj"	"$(INTDIR)\EqpAcco.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\EqpAudi.CPP

"$(INTDIR)\EqpAudi.obj"	"$(INTDIR)\EqpAudi.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\EqpCA150.cpp

"$(INTDIR)\EqpCA150.obj"	"$(INTDIR)\EqpCA150.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\equip\EqpCV24Card.cpp

"$(INTDIR)\EqpCV24Card.obj"	"$(INTDIR)\EqpCV24Card.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\EqpMAT.cpp

"$(INTDIR)\EqpMAT.obj"	"$(INTDIR)\EqpMAT.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\equip\eqpMATCOM.cpp

"$(INTDIR)\eqpMATCOM.obj"	"$(INTDIR)\eqpMATCOM.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\EqpStd.CPP

"$(INTDIR)\EqpStd.obj"	"$(INTDIR)\EqpStd.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\equip\EqpTemp.cpp

"$(INTDIR)\EqpTemp.obj"	"$(INTDIR)\EqpTemp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\equip\EqpTORCard.cpp

"$(INTDIR)\EqpTORCard.obj"	"$(INTDIR)\EqpTORCard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\EQUIP.CPP

"$(INTDIR)\EQUIP.OBJ"	"$(INTDIR)\EQUIP.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\equip\EquipED42.cpp

"$(INTDIR)\EquipED42.obj"	"$(INTDIR)\EquipED42.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\equip\EquipM1752.cpp

"$(INTDIR)\EquipM1752.obj"	"$(INTDIR)\EquipM1752.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\equip\EquipTest.cpp

"$(INTDIR)\EquipTest.obj"	"$(INTDIR)\EquipTest.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\PARAMSIM.CPP

"$(INTDIR)\PARAMSIM.OBJ"	"$(INTDIR)\PARAMSIM.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\SEQUENCE.CPP

"$(INTDIR)\SEQUENCE.OBJ"	"$(INTDIR)\SEQUENCE.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\EQUIP\SYNCHRO.CPP

"$(INTDIR)\SYNCHRO.OBJ"	"$(INTDIR)\SYNCHRO.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\p_1225.CPP

"$(INTDIR)\p_1225.obj"	"$(INTDIR)\p_1225.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\P_1236.CPP

"$(INTDIR)\P_1236.OBJ"	"$(INTDIR)\P_1236.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\P_1237.CPP

"$(INTDIR)\P_1237.OBJ"	"$(INTDIR)\P_1237.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\P_1241.CPP

"$(INTDIR)\P_1241.OBJ"	"$(INTDIR)\P_1241.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\P_18A.CPP

"$(INTDIR)\P_18A.OBJ"	"$(INTDIR)\P_18A.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\P_251.CPP

"$(INTDIR)\P_251.OBJ"	"$(INTDIR)\P_251.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\comm\p_AAD.cpp

"$(INTDIR)\p_AAD.obj"	"$(INTDIR)\p_AAD.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\p_CA150.cpp

"$(INTDIR)\p_CA150.obj"	"$(INTDIR)\p_CA150.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\comm\p_CV24Card.cpp

"$(INTDIR)\p_CV24Card.obj"	"$(INTDIR)\p_CV24Card.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\comm\p_ED42.cpp

"$(INTDIR)\p_ED42.obj"	"$(INTDIR)\p_ED42.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\p_MAT.cpp

"$(INTDIR)\p_MAT.obj"	"$(INTDIR)\p_MAT.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\comm\p_MatCom.cpp

"$(INTDIR)\p_MatCom.obj"	"$(INTDIR)\p_MatCom.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\comm\p_temp.cpp

"$(INTDIR)\p_temp.obj"	"$(INTDIR)\p_temp.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\p_Test.cpp

"$(INTDIR)\p_Test.obj"	"$(INTDIR)\p_Test.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\comm\p_TORCard.cpp

"$(INTDIR)\p_TORCard.obj"	"$(INTDIR)\p_TORCard.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\comm\p_TRC1752.cpp

"$(INTDIR)\p_TRC1752.obj"	"$(INTDIR)\p_TRC1752.sbr" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\PORT.CPP

"$(INTDIR)\PORT.OBJ"	"$(INTDIR)\PORT.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\PROT_ACC.CPP

"$(INTDIR)\PROT_ACC.OBJ"	"$(INTDIR)\PROT_ACC.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\PROT_AUD.CPP

"$(INTDIR)\PROT_AUD.OBJ"	"$(INTDIR)\PROT_AUD.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\PROT_STD.CPP

"$(INTDIR)\PROT_STD.OBJ"	"$(INTDIR)\PROT_STD.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\COMM\PROTO.CPP

"$(INTDIR)\PROTO.OBJ"	"$(INTDIR)\PROTO.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\DIVERS\DIV_FIC.CPP

"$(INTDIR)\DIV_FIC.OBJ"	"$(INTDIR)\DIV_FIC.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\DIVERS\DIV_TMP.CPP

"$(INTDIR)\DIV_TMP.OBJ"	"$(INTDIR)\DIV_TMP.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\DIVERS\TABLE.CPP

"$(INTDIR)\TABLE.OBJ"	"$(INTDIR)\TABLE.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)


SOURCE=.\DIVERS\TACHE.CPP

"$(INTDIR)\TACHE.OBJ"	"$(INTDIR)\TACHE.SBR" : $(SOURCE) "$(INTDIR)" "$(INTDIR)\sicomex.pch"
	$(CPP) $(CPP_PROJ) $(SOURCE)



!ENDIF 

