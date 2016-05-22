/* **************************************************************************
FICHIER :	Tache.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Impl�mentation de la classe CTache
***************************************************************************	*/

#include "stdafx.h"
#include "Divers\Tache.h"

DWORD WINAPI XTraitement(LPVOID param);

/* **************************************************************************
METHODE :		CTache()
TRAITEMENT:		Cr�e l'objet CTache
***************************************************************************	*/
CTache::CTache()
{
		hdl					= NULL;
		id					= 0;
		etat_thread			= THREAD_NON_CREE;
		InitializeCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		~CTache()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CTache::~CTache()
{
	BOOL	bResult;
	int		iResult;

	iResult = Desactiver();
	if (hdl != NULL) bResult = TerminateThread(hdl,0);

	LeaveCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		Handle()
TRAITEMENT:		Retourne le Handle du thread du protocole
***************************************************************************	*/
HANDLE CTache::Handle() const
{
	HANDLE	h;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		h = hdl;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
	return h;
}

/* **************************************************************************
METHODE :		EtatTache()
TRAITEMENT:		Retourne l'�tat de la tache du protocole
***************************************************************************	*/
int CTache::EtatTache() const
{
	int iResult;
	
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = etat_thread;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

/* **************************************************************************
METHODE :		ChangeEtatProto()
TRAITEMENT:		Modifie l'�tat de la tache
***************************************************************************	*/
int CTache::ChangeEtat(int etat)
{
	EnterCriticalSection(&crit);
		etat_thread = etat;
	LeaveCriticalSection(&crit);

	return etat;
}

/* **************************************************************************
METHODE :		Activer()
TRAITEMENT:		Cr�er le thread � d�fini dans la m�thode traitement
				Renvoi 0 sur succ�s ou une const int n�gative sur echec
***************************************************************************	*/
int CTache::Activer()
{
	if(EtatTache() != THREAD_NON_CREE)
	{
		return ERR_CTACHE;
	}
	
	hdl = CreateThread(
		NULL,				// attributs de securit�
		0,
		XTraitement,
		(LPVOID)(this),
		0,					// le thread s'ex�cute imm�diatement
		&id);

	if(hdl == NULL)
	{
		return ERR_THREAD;
	}

	ChangeEtat(THREAD_ACTIVE);

	return 0;
}

/* **************************************************************************
METHODE :		Desactiver()
TRAITEMENT:		Termine le thread associ�
				Renvoi 0 sur succ�s ou une const int n�gative sur echec
***************************************************************************	*/
int CTache::Desactiver()
{
	DWORD	dwResult;
	if(EtatTache() == THREAD_NON_CREE) return ERR_CTACHE;

	ChangeEtat(THREAD_NON_CREE);

	dwResult = WaitForSingleObject(Handle(),2000);
	if(dwResult == WAIT_TIMEOUT)
	{
		TerminateThread(Handle(),0);
		Beep(840,100);
	}

	return 0;
}

/* **************************************************************************
METHODE :		Suspendre()
TRAITEMENT:		Suspend la thread associ�
				Renvoi 0 sur succ�s ou une const int n�gative sur echec
***************************************************************************	*/
int CTache::Suspendre()
{
	if(EtatTache() != THREAD_ACTIVE) return ERR_CTACHE;

	SuspendThread(hdl);
	ChangeEtat(THREAD_SUSPENDU);

	return 0;
}

/* **************************************************************************
METHODE :		Rependre()
TRAITEMENT:		Reprend le thread associ� pr�c�delment suspendu
				Renvoi 0 sur succ�s ou une const int n�gative sur echec
***************************************************************************	*/
int CTache::Rependre()
{
	if(EtatTache() != THREAD_SUSPENDU) return ERR_THREAD;

	ResumeThread(hdl);
	ChangeEtat(THREAD_ACTIVE);

	return 0;
}

/* **************************************************************************
METHODE :		Traitement()
TRAITEMENT:		Traitement � effecter dans le thread
***************************************************************************	*/
DWORD WINAPI CTache::Traitement(LPVOID param)
{
	while(((CTache*)param)->EtatTache() != THREAD_NON_CREE)
		Beep(440,1000);
	return 0;
}

DWORD WINAPI XTraitement(LPVOID param)
{
	CTache* prum = (CTache*) param;
	return prum->Traitement(param);
}
