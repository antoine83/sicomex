/* **************************************************************************
FICHIER :	Tache.h				 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***************************************************************************	*/
#ifndef _CTACHE
#define _CTACHE
#include <windows.h>
#include <stdio.h>

/* **************************************************************************
NOM DU COMPOSANT : 		CTache

ROLE DU COMPOSANT :		Gestion et controle de base d'un thread

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

const int THREAD_NON_CREE	=0;
const int THREAD_ACTIVE		=1;
const int THREAD_SUSPENDU	=2;
const int ERR_THREAD		=-1;
const int ERR_CTACHE		=-2;

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CTache
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
	HANDLE 		hdl;
	DWORD 		id;
	int			etat_thread;

protected:
	CRITICAL_SECTION	crit;		// Section critique

public:
	CTache();
	~CTache();

	HANDLE	Handle() const;
	int		EtatTache() const;
	int		ChangeEtat(int etat);
	int		Activer();
	virtual int Desactiver();
	int		Suspendre();
	int		Rependre();
	virtual DWORD WINAPI Traitement(LPVOID param);

};

#endif
