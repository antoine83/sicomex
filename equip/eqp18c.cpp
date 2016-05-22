/* **************************************************************************
FICHIER :	Eqp_18C.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip18C
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\Eqp18C.h"
#include "Comm\p_18A.h"

#include "Dlg18C.h"

#include "..\Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_EMREC[];
/* **************************************************************************
METHODE :		CEquip18C()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquip18C::CEquip18C(int idx):CEquip18A(idx)
{
}

/* **************************************************************************
METHODE :		~CEquip18C
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquip18C::~CEquip18C()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquip18C::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProto18A(ligne.format,this);

	if(ihm == NULL) ihm = new CDlg18C;
	ihm->Associe(this);
	ihm->Create(F6_IDD_TRBM18C,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_EMREC);
}

// Frequence d'emmission
int CEquip18C::ChangeFrequenceEm(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;
	char	reponse[TAILLE_PIPE_MESSAGE+1];

	EnterCriticalSection(&crit);
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(num_canal==0 && Canal()!=0 && !genere_TS) return ERR_CDE_INCONNUE;
	// genere_TS est vrai sur modification par IHM

	if((valeur >=2250 && valeur <=3999) || (valeur >=1000 && valeur <=1559))
	{
		if(valeur >=1000 && valeur <=1559) 	// Mode VHF
		{
			if((Relais()%2)!=1 ) 
				return ERR_NON_CONFORME;
		}

	 	if(FrequenceEm(num_canal) != valeur)
		{
			ChangeAccordMulti(num_canal,1,FALSE);	// Accord non demandé == 1

			if(!Silence() && genere_TS)		// Pas silence et par face avant
			{
				ChangeAccord(1,FALSE);
				ChangeAccordMulti(0,1,FALSE);	// Accord non demandé == 1
				ChangeEmission(1,FALSE);
				
				proto->TraiteTS(EMR_STATUS,reponse);
				proto->EnvoyerTS(reponse);

				proto->AjouterTS(NULL,CDE_TEMPO_SEQ);

				ChangeAccord(0,FALSE);
				ChangeEmission(0,FALSE);
				
				proto->AjouterTS(NULL,EMR_STATUS);
			}			

		}

		EnterCriticalSection(&crit);
			carac_canal[num_canal].frequence_Em = valeur;

			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
		iResult = ERR_NON_CONFORME;

	return iResult;
}

// Frequence de reception
int CEquip18C::ChangeFrequenceRec(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	EnterCriticalSection(&crit);
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(num_canal==0 && Canal()!=0 && !genere_TS) return ERR_CDE_INCONNUE;
	// genere_TS est vrai sur modification par IHM

	if((valeur >=2250 && valeur <=3999) || (valeur >=1000 && valeur <=1559))
	{
		if(valeur >=1000 && valeur <=1559) 	// Mode VHF
		{
			if((Relais()%2)!=1 ) 
				return ERR_NON_CONFORME;
		}

		EnterCriticalSection(&crit);
			carac_canal[num_canal].frequence_Rec = valeur;

			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
		iResult = ERR_NON_CONFORME;

	return iResult;
}
