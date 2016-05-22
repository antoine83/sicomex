/*************************************************************************
FICHIER :	Equip.h					 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _CEQUIP
#define _CEQUIP
/* **************************************************************************
NOM DU COMPOSANT : 		CEquip

ROLE DU COMPOSANT :		Classe de base d'un equipement du STR

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "DlgEquip.h"
#include "Divers\table.h"
#include "comm\proto.h"
#include "Equip\Sequence.h"
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/

class CProto;
class CSequence;
class CDlgEquip;

const int	PLAGE_EVOLUTION	=128;		// Plage tournante de l'évoution

const int	CDE_PURGE_PORT	=-5;		// mini temporisation / 10
const int	CDE_TEMPO_DIV_10=-4;		//
const int	CDE_TEMPO_DIV_4	=-3;		// mini temporisation
const int	CDE_HEXA		=-2;		// pour le message tel quel
const int	CDE_TEXTE_SEUL	=-1;		// pour envoyer du texte
const int	CDE_TEMPO_SEQ	=0;			// Temporisation dans les sequences

class CEquip
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/

public:
	CProto		*proto;				// Objet protocole
protected:
	CDlgEquip	*ihm;				// Objet Ecran de controle
	CSequence	*seq;				// Objet sequence de mess à envoyer
	//CTache		*tache;
	int			index;				// index dans la table glob_paramsimu;

	BOOL		power;				// Idication de mise en route

	int			evolution;			// Incrémenté après chaque modif de
									// param interne (optimise le rafraich.)

	CRITICAL_SECTION	crit;		// Section critique

/* **************************************************************************
METHODE :		CEquip()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquip(int	idx);

/* **************************************************************************
METHODE :		~CEquip()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	virtual ~CEquip();

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication
***************************************************************************	*/
	virtual void Allocation();

/* **************************************************************************
METHODE :		FormatRepere
TRAITEMENT:		Modifie le format de transmission et le repere de l'equipement
***************************************************************************	*/
	virtual void FormatRepere();
/* **************************************************************************
METHODE :		Index
TRAITEMENT:		Retourne la position de l'equipement dans la rable CParamSimu
***************************************************************************	*/
	int Index() const;

/* **************************************************************************
METHODE :		Evolution
TRAITEMENT:		Retourne la valeur d'évolution des paramètres interne de 
				l'équipement. Cette valeur est incrémenté à chaque modification
				d'un des paramètres interne de l'équipement
***************************************************************************	*/
	int Evolution() const;

/* **************************************************************************
METHODE :		RetourneErreurCom()
TRAITEMENT:		Retourne les erreur de communication
***************************************************************************	*/
	virtual void RetourneComErreur(t_ComErreur	*err);

/* **************************************************************************
METHODE :		ChangeErreurCom()
TRAITEMENT:		Modifie les erreurs de communication
***************************************************************************	*/
	virtual void ChangeComErreur(t_ComErreur err);

/* **************************************************************************
METHODE :		EnCours()
TRAITEMENT:		Retourne l'etat procedure en cours
***************************************************************************	*/
	BOOL  EnCours();

/* **************************************************************************
METHODE :		ChangeEnCours()
TRAITEMENT:		Bastule l'etat l'etat procedure en cours
***************************************************************************	*/
	void  ChangeEnCours(BOOL etat);
/* **************************************************************************
METHODE :		DureeTempo()
TRAITEMENT:		Retourne la valeur de la durée de la temporisation
***************************************************************************	*/
	int  DureeTempo();

/* **************************************************************************
METHODE :		DureeTempo()
TRAITEMENT:		Fixe la durée de la temporisation
***************************************************************************	*/
	BOOL ChangeDureeTempo(int nb_milli);

/* **************************************************************************
METHODE :		EnvoiCyclique()
TRAITEMENT:		Retourne le type d'envoi :	unitaire ou cyclique
***************************************************************************	*/
	BOOL EnvoiCyclique();		
/* **************************************************************************
METHODE :		ChangeEnvoiCyclique()
TRAITEMENT:		Détermine l'envoi cyclique ou unitaire d'un séquence		
***************************************************************************	*/
	void ChangeEnvoiCyclique(BOOL cycle);		

/* **************************************************************************
METHODE :		Periode()
TRAITEMENT:		retourne la valeur de la période en sec
***************************************************************************	*/
	int Periode();

/* **************************************************************************
METHODE :		Periode()
TRAITEMENT:		Détermine la valeur de la période en sec pour les séquences
				non synchronisées
***************************************************************************	*/
	BOOL ChangePeriode(int per);

/* **************************************************************************
METHODE :		Synchronise()
TRAITEMENT:		retourne si l'envoi d'une séquence est synchronisée avec le
				TOP	du simulateur
***************************************************************************	*/
	BOOL Synchronise();
/* **************************************************************************
METHODE :		ChangeSynchronise()
TRAITEMENT:		Détermine l'envoi d'une séquence est synchronisée sur le TOP
				du simulateur
***************************************************************************	*/
	void ChangeSynchronise(BOOL sync);

/* **************************************************************************
METHODE :		AjouterSequence()
TRAITEMENT:		Ajoute une commande à la sequence
***************************************************************************	*/
	int AjouterSequence(int type_cde);

/* **************************************************************************
METHODE :		LireSequence()
TRAITEMENT:		Lire la commande à la index ieme position dans la sequence
***************************************************************************	*/
	int LireSequence(int index);

/* **************************************************************************
METHODE :		RetirerSequence()
TRAITEMENT:		Retire une commande à la sequence
***************************************************************************	*/
	int RetirerSequence(int index);

/* **************************************************************************
METHODE :		EnvoyerMessage()
TRAITEMENT:		Envoi un message par le protocole de l'equipement
***************************************************************************	*/
	virtual void EnvoyerMessage(char *mes,int type_cde);

/* **************************************************************************
METHODE :		Afficher()
TRAITEMENT:		Affiche ou masque l'écran de controle
***************************************************************************	*/
	void Afficher(BOOL	etat);

/* **************************************************************************
METHODE :		Verrouiller()
TRAITEMENT:		Verrouille ou deverrouille l'écran de controle
***************************************************************************	*/
	void Verrouiller(BOOL	etat);

/* **************************************************************************
METHODE :		AjouterMessage()
TRAITEMENT:		Ajoute un message sur le journal des evenement de l'equipement
***************************************************************************	*/
	void AjouterMessage(char *mes,int code_erreur);

/* **************************************************************************
METHODE :		Actif()
TRAITEMENT:		Retourne l'etat d'activite de l'équipement
***************************************************************************	*/
	BOOL Actif();

/* **************************************************************************
METHODE :		Power()
TRAITEMENT:		Mise en route de l'équipement->activation du thread de CProto
***************************************************************************	*/
public:
	virtual BOOL Power();

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
	virtual BOOL Charge_Contexte(char *fichier);
/* **************************************************************************
METHODE :		Sauve_Contexte()
TRAITEMENT:		Sauveagrde le contexte d'exploitation d'un fichier
***************************************************************************	*/
	virtual BOOL Sauve_Contexte(char *fichier);

};

#endif

