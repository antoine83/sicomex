/* **********************************************************************
FICHIER :	Sequence.h				 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _CSEQUENCE
#define _CSEQUENCE
/* **********************************************************************
NOM DU COMPOSANT : 		CSequence

ROLE DU COMPOSANT :		Classe Gestion des séquence d'envoi de message

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***********************************************************************	*/

#include "divers\Tache.h"
#include "divers\Table.h"
#include "Equip\Equip.h"

const int	ERR_AUCUN_ELEMENT	=-10;

const int	EVENT_THREAD	=0;		// Pilotage du thread
const int	EVENT_TIMER		=1;		// Evenement d'envoi de séquence
const int	EVENT_TOP		=2;		// Evenement d'envoi de séquence
/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquip;

class CSequence:public CTache
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
	CEquip		*eqp;
	HANDLE		event[3];			// Fin Thread / Envoi de la sequence

	CTable		sequence;			// Liste de message à envoyer
	int			duree_tempo;		// Valeur de la temposriation(<10s)

	BOOL		envoi_cyclique;		
	int			periode;			// Valeur du cycle : entre 10s et 5 mn
	BOOL		synchronise;		// Synchronisé avec le top synchro

	BOOL		en_cours;

/* **************************************************************************
METHODE :		CSequence()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CSequence(CEquip *pEqp);

/* **************************************************************************
METHODE :		~CSequence()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CSequence();

/* **************************************************************************
METHODE :		EnCours()
TRAITEMENT:		Retourne l'etat procedure en cours
***************************************************************************	*/
	BOOL  EnCours() const;

/* **************************************************************************
METHODE :		ChangeEnCours()
TRAITEMENT:		Bastule l'etat l'etat procedure en cours
***************************************************************************	*/
	void ChangeEnCours(BOOL etat);

/* **************************************************************************
METHODE :		DureeTempo()
TRAITEMENT:		Retourne la valeur de la durée de la temporisation
***************************************************************************	*/
	int  DureeTempo() const;

/* **************************************************************************
METHODE :		DureeTempo()
TRAITEMENT:		Fixe la durée de la temporisation
***************************************************************************	*/
	BOOL ChangeDureeTempo(int nb_milli);

/* **************************************************************************
METHODE :		EnvoiCyclique()
TRAITEMENT:		Retourne le type d'envoi :	unitaire ou cyclique
***************************************************************************	*/
	BOOL EnvoiCyclique() const;		
/* **************************************************************************
METHODE :		ChangeEnvoiCyclique()
TRAITEMENT:		Détermine l'envoi cyclique ou unitaire d'un séquence		
***************************************************************************	*/
	BOOL ChangeEnvoiCyclique(BOOL cycle);		

/* **************************************************************************
METHODE :		Periode()
TRAITEMENT:		retourne la valeur de la période en sec
***************************************************************************	*/
	int Periode() const;

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
	BOOL Synchronise() const;
/* **************************************************************************
METHODE :		ChangeSynchronise()
TRAITEMENT:		Détermine l'envoi d'une séquence est synchronisée sur le TOP
				du simulateur
***************************************************************************	*/
	BOOL ChangeSynchronise(BOOL sync);

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
TRAITEMENT:		retire le index ieme commande à la sequence
***************************************************************************	*/
	int RetirerSequence(int index);

/* **************************************************************************
METHODE :		Desactiver()
TRAITEMENT:		Termine le thread associé
***************************************************************************	*/
	virtual int Desactiver();

/* **************************************************************************
METHODE :		Traitement()
TRAITEMENT:		Traitement à effecter dans le thread
***************************************************************************	*/
	virtual DWORD WINAPI Traitement(void *param);
};
#endif
