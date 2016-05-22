/*************************************************************************
FICHIER :	Eqp_18C.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _EQP_18C
#define _EQP_18C
/* **************************************************************************
NOM DU COMPOSANT : 		CEquip18C

ROLE DU COMPOSANT :		Classe Equipement de l'émetteur/récepteur UHF

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "Eqp18A.h"	

//const int	CDE_TEXTE_SEUL	=-1;		// pour Evoyer du texte
//const int	CDE_TEMPO_SEQ	=0;			// Temporisation dans les sequences

// Télésignalisation : EMR pour Emmetteur/Recepteur

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquip18C:public CEquip18A
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
/* **************************************************************************
METHODE :		CEquip18C()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquip18C(int idx);

/* **************************************************************************
METHODE :		~CEsuipRecHF()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CEquip18C();

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'écran de controle
***************************************************************************	*/
	virtual void Allocation();

/* **************************************************************************
METHODE :		ChangeFrequenceEm
TRAITEMENT:		Modifie la frquence d'emission et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeFrequenceEm(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		ChangeFrequenceRec
TRAITEMENT:		Modifie la ferquence de reception et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeFrequenceRec(int num_canal,int valeur,BOOL genere_TS);

};

#endif

