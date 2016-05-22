/*************************************************************************
FICHIER :	Eqp_1236.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _EQP_1237_L11
#define _EQP_1237_L11
/* **************************************************************************
NOM DU COMPOSANT : 		CEquip1237L

ROLE DU COMPOSANT :		Classe Equipement Emetteur HF 1237 L11

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "Eqp1237.h"

//const int	CDE_TEXTE_SEUL	=-1;		// pour Evoyer du texte
//const int	CDE_TEMPO_SEQ	=0;			// Temporisation dans les sequences

// Télésignalisation : EME pour Emetteur
// const int	EME_1236_INFO		= 14;		// T


/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquip1237L:public CEquip1237
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
/* **************************************************************************
METHODE :		CEquip1237L()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquip1237L(int idx);

/* **************************************************************************
METHODE :		~CEquip1237L()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CEquip1237L();

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'écran de controle
***************************************************************************	*/
	virtual void Allocation();

/* **************************************************************************
METHODE :		ChangeModeTrafic
TRAITEMENT:		Modifie le mode de trafic et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeModeTrafic(int num_canal,int mode,BOOL genere_TS);

/* **************************************************************************
METHODE :		L11
TRAITEMENT:		Retourne le mode L11
***************************************************************************	*/
	virtual int L11() const;
};

#endif

