/* **************************************************************************
FICHIER :	Eqp1241S.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip1241S
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\Eqp1241S.h"
#include "Comm\p_1241.h"
#include "Dlg1241S.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_RECHF[];
/* **************************************************************************
METHODE :		CEquip1241S()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquip1241S::CEquip1241S(int idx):CEquip1241L(idx)
{

}

/* **************************************************************************
METHODE :		~CEquip1241S
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquip1241S::~CEquip1241S()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquip1241S::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProtoRecHF(ligne.format,this);

	if(ihm == NULL) ihm = new CDlg1241S;
	ihm->Associe(this);
	ihm->Create(F5_IDD_TRC1241_SPIN,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_RECHF);
}

// mode SPIN
int CEquip1241S::Spin() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = spin;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip1241S::ChangeSpin(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			spin = valeur;
			if(valeur==0)
			{
				local = 1;  // Mode RMT
			}

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS && valeur==0)
		{
			proto->AjouterTS(NULL,REC_1241_MODE_LOCAL);
			proto->AjouterTS(NULL,REC_1241_MODE_RECEP);
			proto->AjouterTS(NULL,REC_1241_OPTION_REC);
			proto->AjouterTS(NULL,REC_1241_FREQUENCE);
			proto->AjouterTS(NULL,REC_1241_MODE_RECEP);
			proto->AjouterTS(NULL,REC_1241_FILTRE_FI);
			proto->AjouterTS(NULL,REC_1241_ATTENUATEUR);
			proto->AjouterTS(NULL,REC_1241_CAG);
			proto->AjouterTS(NULL,REC_1241_REJECTEUR);
			proto->AjouterTS(NULL,REC_1241_SQUELCH);
			proto->AjouterTS(NULL,REC_1241_BFO);
			proto->AjouterTS(NULL,REC_1241_NIVEAU_HF);
			proto->AjouterTS(NULL,REC_1241_SEUIL_COR);
			proto->AjouterTS(NULL,REC_1241_CANAL_POSI);
		}
	}

	return iResult;
}
