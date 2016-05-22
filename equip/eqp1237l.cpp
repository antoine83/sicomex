/* **************************************************************************
FICHIER :	Eqp1237L.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip1237
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\Eqp1237L.h"
#include "Comm\p_1237.h"
#include "Dlg1237L.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_EMETHF[];
/* **************************************************************************
METHODE :		CEquip1237L()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquip1237L::CEquip1237L(int idx):CEquip1237(idx)
{

}

/* **************************************************************************
METHODE :		~CEquip1237L
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquip1237L::~CEquip1237L()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquip1237L::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProto1237(ligne.format,this);

	if(ihm == NULL) ihm = new CDlg1237L;
	ihm->Associe(this);
	ihm->Create(F8_IDD_TRC1237_L11,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_EMETHF);
}

// Mode de trafic
int CEquip1237L::ChangeModeTrafic(int num_canal,int valeur,BOOL genere_TS)
{
	int		iResult;

	iResult = CEquip1237::ChangeModeTrafic(num_canal,valeur,genere_TS);

	if(iResult>=0)
	{
		EnterCriticalSection(&crit);
			l11 = (iResult == 2) || (iResult == 3) || (iResult == 4);

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
	}
	return iResult;
}

// mode L11
int CEquip1237L::L11() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = l11;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
