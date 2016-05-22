/*************************************************************************
FICHIER :	Eqp_1236.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _EQP_1236_SPIN
#define _EQP_1236_SPIN
/* **************************************************************************
NOM DU COMPOSANT : 		CEquip1236S

ROLE DU COMPOSANT :		Classe Equipement Emetteur HF 1236 SPIN

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "Eqp1236L.h"

//const int	CDE_TEXTE_SEUL	=-1;		// pour Evoyer du texte
//const int	CDE_TEMPO_SEQ	=0;			// Temporisation dans les sequences

// Télésignalisation : EME pour Emetteur
// const int	EME_1236_INFO		= 14;		// T


/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquip1236S:public CEquip1236L
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
/* **************************************************************************
METHODE :		CEquip1236S()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquip1236S(int idx);

/* **************************************************************************
METHODE :		~CEquip1236S()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CEquip1236S();

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'écran de controle
***************************************************************************	*/
	virtual void Allocation();

/* **************************************************************************
METHODE :		Spin
TRAITEMENT:		Retourne le mode SPIN
***************************************************************************	*/
	virtual int Spin() const;
/* **************************************************************************
METHODE :		ChangeSpin
TRAITEMENT:		Modifie le mode Spin
***************************************************************************	*/
	virtual int ChangeSpin(int valeur,BOOL genere_TS);
};

#endif

