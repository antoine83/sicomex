/* **************************************************************************
FICHIER :	Eqp1237S.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip1237S
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\Eqp1237S.h"
#include "Comm\p_1237.h"
#include "Dlg1237S.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_EMETHF[];
/* **************************************************************************
METHODE :		CEquip1237S()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquip1237S::CEquip1237S(int idx):CEquip1237L(idx)
{

}

/* **************************************************************************
METHODE :		~CEquip1237S
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquip1237S::~CEquip1237S()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquip1237S::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProto1237(ligne.format,this);

	if(ihm == NULL) ihm = new CDlg1237S;
	ihm->Associe(this);
	ihm->Create(F8_IDD_TRC1237_SPIN,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_EMETHF);
}

// mode SPIN
int CEquip1237S::Spin() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = spin;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip1237S::ChangeSpin(int valeur,BOOL genere_TS)
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
			proto->AjouterTS(NULL,EME_1237_MODE_LOCAL);
			proto->AjouterTS(NULL,EME_1237_OPTION);
			proto->AjouterTS(NULL,EME_1237_FREQUENCE);
			proto->AjouterTS(NULL,EME_1237_MODE_FONCT);
			proto->AjouterTS(NULL,EME_1237_COMPRESSEUR);
			proto->AjouterTS(NULL,EME_1237_MODE_TRAFIC);
			proto->AjouterTS(NULL,EME_1237_CANAL_POSI);
			proto->AjouterTS(NULL,EME_1237_ETAT_LOGI);
			proto->AjouterTS(NULL,EME_1237_INFO);
		}
	}

	return iResult;
}
