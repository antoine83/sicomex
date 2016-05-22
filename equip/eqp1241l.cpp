/* **************************************************************************
FICHIER :	Eqp1241L.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip1241L
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\Eqp1241L.h"
#include "Comm\p_1241.h"
#include "Dlg1241L.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_RECHF[];
/* **************************************************************************
METHODE :		CEquip1236S()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquip1241L::CEquip1241L(int idx):CEquip1241(idx)
{

}

/* **************************************************************************
METHODE :		~CEquip1241L
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquip1241L::~CEquip1241L()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquip1241L::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProtoRecHF(ligne.format,this);

	if(ihm == NULL) ihm = new CDlg1241L;
	ihm->Associe(this);
	ihm->Create(F5_IDD_TRC1241_L11,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_RECHF);
}

int CEquip1241L::ChangeModeRecep(int num_canal,int valeur,BOOL genere_TS)
{
	int		iResult;

	iResult = CEquip1241::ChangeModeRecep(num_canal,valeur,genere_TS);

	if(iResult>=0)
	{
		EnterCriticalSection(&crit);
			l11 = (iResult == 2) || (iResult == 3) || (iResult == 4);

			if(!l11 && 	carac_canal[num_canal].cag == 4) 
				carac_canal[num_canal].cag = 0;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
	}
	return iResult;
}

// mode L11
int CEquip1241L::L11() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = l11;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
