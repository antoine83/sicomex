/* **************************************************************************
FICHIER :	Sequence.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CSequence
***************************************************************************	*/

#include "stdafx.h"

#include "Equip\Sequence.h"
#include "divers\Div_tmp.h"

extern	char glob_TOP[];
/* **************************************************************************
METHODE :		CSequence()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CSequence::CSequence(CEquip *pEqp)
{
	eqp = pEqp;

	event[EVENT_THREAD] = CreateEvent(NULL,FALSE,FALSE,NULL);
	event[EVENT_TIMER] = CreateEvent(NULL,FALSE,FALSE,NULL);
	event[EVENT_TOP] = OpenEvent(SYNCHRONIZE,FALSE,glob_TOP);	

	duree_tempo = 2000;
	envoi_cyclique = FALSE;		
	periode = 10;
	synchronise = TRUE;

	en_cours = FALSE;

}

/* **************************************************************************
METHODE :		~CSequence()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CSequence::~CSequence()
{
	int		iResult;
	BOOL	bResult;

	iResult = Desactiver();
	CloseHandle(event[EVENT_THREAD]);

	if (Handle() != NULL) bResult = TerminateThread(Handle(),0);
}

/* **************************************************************************
METHODE :		EnCours()
TRAITEMENT:		Retourne l'etat procedure en cours
***************************************************************************	*/
BOOL  CSequence::EnCours() const
{
	BOOL		bResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		bResult = en_cours;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
		
	return bResult;
}

/* **************************************************************************
METHODE :		ChangeEnCours()
TRAITEMENT:		Bascule l'etat de procedure en cours
***************************************************************************	*/
void CSequence::ChangeEnCours(BOOL etat)
{
	BOOL	bResult;
	EnterCriticalSection(&crit);
		en_cours = etat;

		if(etat)
		{
			if(!Synchronise())
				bResult = SetEvent(event[EVENT_TIMER]);
		}

	LeaveCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		DureeTempo()
TRAITEMENT:		Retourne la valeur de la durée de la temporisation
***************************************************************************	*/
int  CSequence::DureeTempo() const
{
	int		iResult;
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = duree_tempo;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
		
	return iResult;
}

/* **************************************************************************
METHODE :		ChangeDureeTempo()
TRAITEMENT:		Fixe la durée de la temporisation
***************************************************************************	*/
BOOL CSequence::ChangeDureeTempo(int nb_milli)
{
	if(EnCours()) return FALSE;
	if(nb_milli<0 || nb_milli>10000) return FALSE;

	EnterCriticalSection(&crit);
		duree_tempo = nb_milli;
	LeaveCriticalSection(&crit);

	return TRUE;
}

/* **************************************************************************
METHODE :		EnvoiCyclique()
TRAITEMENT:		Retourne le type d'envoi :	unitaire ou cyclique
***************************************************************************	*/
BOOL CSequence::EnvoiCyclique() const
{
	BOOL		bResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		bResult = envoi_cyclique;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
		
	return bResult;
}			
/* **************************************************************************
METHODE :		ChangeEnvoiCyclique()
TRAITEMENT:		Détermine l'envoi cyclique ou unitaire d'un séquence		
***************************************************************************	*/
BOOL CSequence::ChangeEnvoiCyclique(BOOL cycle)
{
	if(EnCours()) return FALSE;

	EnterCriticalSection(&crit);
		envoi_cyclique = cycle;
	LeaveCriticalSection(&crit);
	return TRUE;
}		

/* **************************************************************************
METHODE :		Periode()
TRAITEMENT:		retourne la valeur de la période en sec
***************************************************************************	*/
int CSequence::Periode() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = periode;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

/* **************************************************************************
METHODE :		ChangePeriode()
TRAITEMENT:		Détermine la valeur de la période en sec pour les séquences
				non synchronisées
***************************************************************************	*/
BOOL CSequence::ChangePeriode(int per)
{
	if(EnCours()) return FALSE;

	if(per<1 || per >300) return FALSE;

	EnterCriticalSection(&crit);
		periode = per;
	LeaveCriticalSection(&crit);

	return TRUE;
}

/* **************************************************************************
METHODE :		Synchronise()
TRAITEMENT:		retourne si l'envoi d'une séquence est synchronisée avec le
				TOP	du simulateur
***************************************************************************	*/
BOOL CSequence::Synchronise() const
{
	BOOL		bResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		bResult = synchronise;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
		
	return bResult;
}

/* **************************************************************************
METHODE :		ChangeSynchronise()
TRAITEMENT:		Détermine l'envoi d'une séquence est synchronisée sur le TOP
				du simulateur
***************************************************************************	*/
BOOL CSequence::ChangeSynchronise(BOOL sync)
{
	if(EnCours()) return FALSE;

	EnterCriticalSection(&crit);
		synchronise = sync;
	LeaveCriticalSection(&crit);

	SetEvent(event[EVENT_TIMER]);		// Re positionne le Wait event

	return TRUE;

}

/* **************************************************************************
METHODE :		AjouterSequence()
TRAITEMENT:		Ajoute une commande à la sequence
***************************************************************************	*/
int CSequence::AjouterSequence(int type_cde)
{
	return sequence.Ajouter(NULL,type_cde);
}
/* **************************************************************************
METHODE :		LireSequence()
TRAITEMENT:		Lire la commande à la index ieme position dans la sequence
***************************************************************************	*/
int CSequence::LireSequence(int index)
{
	int	type_cde;
	char mes[TAILLE_PIPE_MESSAGE];

	if(sequence.Lire(index,mes,&type_cde))	return  type_cde;

	return ERR_AUCUN_ELEMENT;
}

/* **************************************************************************
METHODE :		RetirerSequence()
TRAITEMENT:		retire le index ieme commande à la sequence
***************************************************************************	*/
int CSequence::RetirerSequence(int index)
{
	return	sequence.Supprime(index);
}

/* **************************************************************************
METHODE :		Desactiver()
TRAITEMENT:		Termine le thread associé
***************************************************************************	*/
int CSequence::Desactiver()
{
	DWORD	dwResult;

	if(EtatTache() == THREAD_NON_CREE) return ERR_CTACHE;

	ChangeEtat(THREAD_NON_CREE);
	PulseEvent(event[EVENT_THREAD]);
	PulseEvent(event[EVENT_THREAD]);
	PulseEvent(event[EVENT_THREAD]);

	dwResult = WaitForSingleObject(Handle(),1000);
	if(dwResult == WAIT_TIMEOUT)
	{
		TerminateThread(Handle(),0);
	}

	return 0;
}

/* **************************************************************************
METHODE :		Traitement()
TRAITEMENT:		Traitement à effecter dans le thread
***************************************************************************	*/
DWORD WINAPI CSequence::Traitement(void *param)
{
	int		iResult;
	DWORD	dwResult;

	int		type_commande;
	char	message[TAILLE_PIPE_MESSAGE];
    char    temps[25];
    char    buf[80];

	int		offset = 0;			// Pour recallage du temps
	int		tempo;

	offset = Nb_milli(temps);
	while (EtatTache() != THREAD_NON_CREE)
	{

		if(Synchronise())
			dwResult = WaitForMultipleObjects(3,event,FALSE,INFINITE);
		else
		{
			tempo = Periode()*1000 - (Nb_milli(temps)+60000-offset)%60000;
			dwResult = WaitForMultipleObjects(2,event,FALSE,tempo);
			if(Synchronise()) continue;

		}

		if(dwResult == WAIT_OBJECT_0)				// EVENT_THREAD
		{
			ChangeEtat(THREAD_NON_CREE);
			break;
		}

		offset = Nb_milli(temps);
		if(!EnCours()) continue;

// Envoi de la sequence

        sprintf(buf,"%s - Envoi d'une séquence",
              temps);

		eqp->AjouterMessage(buf,0);
		tempo = DureeTempo();

		iResult = sequence.EstNonVide();
		for(int i = 0; i<iResult ; i++)
		{
			sequence.Lire(i,message,&type_commande);
			if(type_commande == CDE_TEMPO_SEQ) Sleep(tempo);
			else
				eqp->EnvoyerMessage(NULL,type_commande);
		}

// Invalidation de l'envoi de la sequence
 		if(!EnvoiCyclique()) ChangeEnCours(FALSE);

	}								// Fin de boucle attente evennement
	return 0;
}
