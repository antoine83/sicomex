/* **********************************************************************
FICHIER :	Synchro.h			 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _CSYNCHRO
#define _CSYNCHRO

/* **********************************************************************
NOM DU COMPOSANT : 		CSynchro

ROLE DU COMPOSANT :		Gestion et Top synchro du simulateur

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***********************************************************************	*/
#include "divers\Tache.h"

const	int NB_MAX_PIPE = 10;

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/

class CSynchro:public CTache
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
	HANDLE		event;				// Action thread
	HANDLE		pipe[NB_MAX_PIPE];			

	BOOL		externe;			// Top externe
	int			depart;			    // heure de d�clenchement en nb s
	int			periode;

public:
	HANDLE		top;				// Top synchro

/* **************************************************************************
METHODE :		CSynchro()
TRAITEMENT:		Cr�e l'objet CSynchro
***************************************************************************	*/
public:
	CSynchro();

/* **************************************************************************
METHODE :		~CSynchro()
TRAITEMENT:		Supprime l'objet CSynchro
***************************************************************************	*/
	~CSynchro();

/* **************************************************************************
METHODE :		Change_Top()
TRAITEMENT:		Pr�vient le thread d'un modification des carcat�ristique du
				top synchro
***************************************************************************	*/
	void Change_Top();

/* **************************************************************************
METHODE :		Activer()
TRAITEMENT:		Active le thread g�n�rant le top synchro s'il est externe
***************************************************************************	*/
	virtual int Activer();

/* **************************************************************************
METHODE :		Desactiver()
TRAITEMENT:		Termine le thread associ�
***************************************************************************	*/
	virtual int Desactiver();

/* **************************************************************************
METHODE :		Traitement()
TRAITEMENT:		Traitement � effecter dans le thread
***************************************************************************	*/
	virtual DWORD WINAPI Traitement(void *param);
};
#endif
