/* **************************************************************************
FICHIER :	Eqp1236S.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip1236S
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\Eqp1236S.h"
#include "Comm\p_1236.h"
#include "Dlg1236S.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_EMETHF[];
/* **************************************************************************
METHODE :		CEquip1236S()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquip1236S::CEquip1236S(int idx):CEquip1236L(idx)
{

}

/* **************************************************************************
METHODE :		~CEquip1236S
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquip1236S::~CEquip1236S()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquip1236S::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProto1236(ligne.format,this);

	if(ihm == NULL) ihm = new CDlg1236S;
	ihm->Associe(this);
	ihm->Create(F7_IDD_TRC1236_SPIN,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_EMETHF);
}

// mode SPIN
int CEquip1236S::Spin() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = spin;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip1236S::ChangeSpin(int valeur,BOOL genere_TS)
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
			proto->AjouterTS(NULL,EME_1236_MODE_LOCAL);
			proto->AjouterTS(NULL,EME_1236_OPTION);
			proto->AjouterTS(NULL,EME_1236_FREQUENCE);
			proto->AjouterTS(NULL,EME_1236_MODE_FONCT);
			proto->AjouterTS(NULL,EME_1236_COMPRESSEUR);
			proto->AjouterTS(NULL,EME_1236_MODE_TRAFIC);
			proto->AjouterTS(NULL,EME_1236_CANAL_POSI);
			proto->AjouterTS(NULL,EME_1236_ETAT_LOGI);
			proto->AjouterTS(NULL,EME_1236_INFO);
		}
	}

	return iResult;
}
