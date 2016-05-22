/* **************************************************************************
FICHIER :	Equip.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip
***************************************************************************	*/

#include "stdafx.h"
#include <stdio.h>

#include "Equip\ParamSim.h"		// struct et prototype des fonct Stations
#include "Equip\Equip.h"		// struct et prototype des fonct Stations

extern	CParamSimu	*glob_paramsimu;
/* **************************************************************************
METHODE :		CEquip()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquip::CEquip(int	idx)
{
	InitializeCriticalSection(&crit);
	index = idx;
	power = FALSE;
	proto = NULL;
	ihm = NULL;
	seq = new CSequence(this);
	evolution = 0;

// Initialisation de CSequence
	seq->ChangeDureeTempo(2000);		// Fixe la durée de la tempo à 2 s
	seq->ChangeEnvoiCyclique(FALSE);		
	seq->ChangePeriode(60);
	seq->ChangeSynchronise(FALSE);		// non Synchronisé avec le top synchro

}

/* **************************************************************************
METHODE :		~CEquip()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquip::~CEquip()
{
	if(proto != NULL) delete proto;
	if(seq != NULL) delete seq;
	if(ihm != NULL) delete ihm;
	DeleteCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication
***************************************************************************	*/
void CEquip::Allocation()
{
	t_affecte	affecte;
	glob_paramsimu->Equipement(index,&affecte);
	if(proto == NULL) proto = new CProto(affecte.format,this);
}

/* **************************************************************************
METHODE :		FormatRepere
TRAITEMENT:		Modifie le format de transmission et le repere de l'equipement
***************************************************************************	*/
void CEquip::FormatRepere()
{
	t_affecte	affecte;

	glob_paramsimu->Equipement(index,&affecte);
	if(proto != NULL) proto->InitialiseFormat(affecte.format);

	if(ihm != NULL)
	{
		ihm->SetWindowText(affecte.repere);
		Afficher(affecte.controle);
	}

}
/* **************************************************************************
METHODE :		Index
TRAITEMENT:		Retourne la position de l'equipement dans la rable CParamSimu
***************************************************************************	*/
int CEquip::Index() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = index;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

/* **************************************************************************
METHODE :		Evolution
TRAITEMENT:		Retourne la valeur d'évolution des paramètres interne de 
				l'équipement. Cette valeur est incrémenté à chaque modification
				d'un des paramètres interne de l'équipement
***************************************************************************	*/
int CEquip::Evolution() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = evolution;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

/* **************************************************************************
METHODE :		RetourneErreurCom()
TRAITEMENT:		Retourne les erreur de communication
***************************************************************************	*/
void CEquip::RetourneComErreur(t_ComErreur	*err)
{
	proto->RetourneErreurCom(err);
}

/* **************************************************************************
METHODE :		ChangeErreurCom()
TRAITEMENT:		Modifie les erreurs de communication
***************************************************************************	*/
void CEquip::ChangeComErreur(t_ComErreur err)
{
	proto->ChangeErreurCom(err);
}

/* **************************************************************************
METHODE :		EnCours()
TRAITEMENT:		Retourne l'etat procedure en cours
***************************************************************************	*/
BOOL  CEquip::EnCours()
{
	return seq->EnCours();
}

/* **************************************************************************
METHODE :		ChangeEnCours()
TRAITEMENT:		Bastule l'etat l'etat procedure en cours
***************************************************************************	*/
void CEquip::ChangeEnCours(BOOL etat)
{
		seq->ChangeEnCours(etat);
}

/* **************************************************************************
METHODE :		DureeTempo()
TRAITEMENT:		Retourne la valeur de la durée de la temporisation
***************************************************************************	*/
int  CEquip::DureeTempo()
{
	return seq->DureeTempo();
}

/* **************************************************************************
METHODE :		DureeTempo()
TRAITEMENT:		Fixe la durée de la temporisation
***************************************************************************	*/
BOOL CEquip::ChangeDureeTempo(int nb_milli)
{
	return seq->ChangeDureeTempo(nb_milli);
}
/* **************************************************************************
METHODE :		EnvoiCyclique()
TRAITEMENT:		Retourne le type d'envoi :	unitaire ou cyclique
***************************************************************************	*/
BOOL CEquip::EnvoiCyclique()		
{
	return seq->EnvoiCyclique();
}
/* **************************************************************************
METHODE :		ChangeEnvoiCyclique()
TRAITEMENT:		Détermine l'envoi cyclique ou unitaire d'un séquence		
***************************************************************************	*/
void CEquip::ChangeEnvoiCyclique(BOOL cycle)
{
	seq->ChangeEnvoiCyclique(cycle);
}

/* **************************************************************************
METHODE :		Periode()
TRAITEMENT:		retourne la valeur de la période en sec
***************************************************************************	*/
int CEquip::Periode()
{
	return seq->Periode();
}

/* **************************************************************************
METHODE :		Periode()
TRAITEMENT:		Détermine la valeur de la période en sec pour les séquences
				non synchronisées
***************************************************************************	*/
BOOL CEquip::ChangePeriode(int per)
{
	return seq->ChangePeriode(per);
}

/* **************************************************************************
METHODE :		Synchronise()
TRAITEMENT:		retourne si l'envoi d'une séquence est synchronisée avec le
				TOP	du simulateur
***************************************************************************	*/
BOOL CEquip::Synchronise()
{
	return seq->Synchronise();
}
/* **************************************************************************
METHODE :		ChangeSynchronise()
TRAITEMENT:		Détermine l'envoi d'une séquence est synchronisée sur le TOP
				du simulateur
***************************************************************************	*/
void CEquip::ChangeSynchronise(BOOL sync)
{
	seq->ChangeSynchronise(sync);
}

/* **************************************************************************
METHODE :		AjouterSequence()
TRAITEMENT:		Ajoute une commande à la sequence
***************************************************************************	*/
int CEquip::AjouterSequence(int type_cde)
{
	return seq->AjouterSequence(type_cde);
}

/* **************************************************************************
METHODE :		LireSequence()
TRAITEMENT:		Lire la commande à la index ieme position dans la sequence
***************************************************************************	*/
int CEquip::LireSequence(int index)
{
	return seq->LireSequence(index);
}

/* **************************************************************************
METHODE :		RetirerSequence()
TRAITEMENT:		Retire une commande à la sequence
***************************************************************************	*/
int CEquip::RetirerSequence(int index)
{
	return seq->RetirerSequence(index);
}

/* **************************************************************************
METHODE :		EnvoyerMessage()
TRAITEMENT:		Envoi un message par le protocole de l'equipement
***************************************************************************	*/
void CEquip::EnvoyerMessage(char *mes,int type_cde)
{
	if(Actif())
		proto->AjouterTS(mes,type_cde);
}

/* **************************************************************************
METHODE :		Afficher()
TRAITEMENT:		Affiche ou masque l'écran de controle
***************************************************************************	*/
void CEquip::Afficher(BOOL	etat)
{
 	EnterCriticalSection(&crit);
		if(etat)
		{
			ihm->ShowWindow(SW_RESTORE);
			ihm->ShowWindow(SW_SHOW);
		}
		else		ihm->ShowWindow(SW_HIDE);
	LeaveCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		Verrouiller()
TRAITEMENT:		Verrouille ou deverrouille l'écran de controle
***************************************************************************	*/
void CEquip::Verrouiller(BOOL	etat)
{
 	EnterCriticalSection(&crit);
		ihm->EnableWindow(etat);
	LeaveCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		AjouterMessage()
TRAITEMENT:		Ajoute un message sur le journal des evenement de l'equipement
***************************************************************************	*/
void CEquip::AjouterMessage(char *mes,int code_erreur)
{
	ihm->AjoutJournal(mes,code_erreur);
}

/* **************************************************************************
METHODE :		Actif()
TRAITEMENT:		Retourne l'etat d'activite de l'équipement
***************************************************************************	*/
BOOL CEquip::Actif()
{
	BOOL	bResult;
 	
 	EnterCriticalSection(&crit);
 		bResult =  power;
	LeaveCriticalSection(&crit);

	return bResult;
}

/* **************************************************************************
METHODE :		Power()
TRAITEMENT:		Mise en route de l'équipement->activation du thread de CProto
***************************************************************************	*/
BOOL CEquip::Power()
{
	EnterCriticalSection(&crit);
		power = !power;
		if(power)
		{
			seq->Activer();
			proto->Purge_message();
			proto->Activer();
		}
		else
		{
			seq->Desactiver();
			proto->Desactiver();
		}
	LeaveCriticalSection(&crit);

	return power;
}

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquip::Charge_Contexte(char *fichier)
{
	return TRUE;
}

/* **************************************************************************
METHODE :		Sauve_Contexte()
TRAITEMENT:		Sauveagrde le contexte d'exploitation d'un fichier
***************************************************************************	*/
BOOL CEquip::Sauve_Contexte(char *fichier)
{
	return TRUE;
}
