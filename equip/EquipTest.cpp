// EquipTest.cpp: implementation of the CEquipTest class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include <stdio.h>
#include "stdafx.h"
#include "sicomex.h"
#include "Equip\ParamSim.h"
#include "EquipTest.h"
#include "Comm\p_Test.h"

#include "DlgAccue.h"
#include "DLGTest1.h"

#include "Divers\div_fic.h"

extern CParamSimu* glob_paramsimu;
extern CDlgAccueil* glob_ihm;
extern char glob_CONTEXT_MAT_SPIN[];
extern char glob_CONTEXT_MAT_L11[];

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CEquipTest::CEquipTest(int idx):CEquip(idx)
{

}

CEquipTest::~CEquipTest()
{

}

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipTest::Charge_Contexte(char *fichier)
{
	return TRUE;
}

/* **************************************************************************
METHODE :		Sauve_Contexte()
TRAITEMENT:		Sauveagrde le contexte d'exploitation d'un fichier
***************************************************************************	*/
BOOL CEquipTest::Sauve_Contexte(char *fichier)
{
	return TRUE;
}

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipTest::Allocation()
{
	t_affecte ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL)
	{
		proto = new CProto_Test(ligne.format,this);
	}

	if(ihm == NULL)
	{
		ihm = new CDLGTest;
	}

	ihm->Associe(this);

	ihm->Create(IDD_TEST,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);
}

/* **************************************************************************
METHODE :		Power
TRAITEMENT:		Mise en route de l'équipement
***************************************************************************	*/
BOOL CEquipTest::Power()
{
	BOOL activite;
	CEquip::Power();

	activite = Actif();
	if(activite)
	{
		proto->AjouterTS("",CDE_TEXTE_SEUL);
	}

	return activite;
}

void CEquipTest::EnvoiMessage(char *mes)
{
	proto->EnvoyerTS(mes);
}

/* **************************************************************************
METHODE :		Power
TRAITEMENT:		Mise en route de l'équipement
***************************************************************************	*/
void CEquipTest::MAJMessage()
{
	ihm->GenerateurAuto();
}
