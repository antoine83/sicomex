/*************************************************************************
FICHIER :	Eqp_Audi.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _CEQUIPAUDIO
#define _CEQUIPAUDIO
/* **************************************************************************
NOM DU COMPOSANT : 		CEquipAudio

ROLE DU COMPOSANT :		Classe Equipement Emetteur HF

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "Equip\Equip.h"	

//const int	CDE_TEXTE_SEUL	=-1;		// pour Evoyer du texte
//const int	CDE_TEMPO_SEQ	=0;			// Temporisation dans les sequences

// Télésignalisation : AUD pour Audio
const int	AUD_RESET	= 1;		// RESET

const int	MAX_CARTE	= 14;
const int	MAX_RELAIS	= 21;

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquipAudio:public CEquip
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
	int		relais[MAX_CARTE][MAX_RELAIS];
	int		test;		// Code de test interne
	int		lock;		// Code de test interne

/* **************************************************************************
METHODE :		CEquipAudio()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquipAudio(int idx);

/* **************************************************************************
METHODE :		~CEsuipEmHF()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CEquipAudio();

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'écran de controle
***************************************************************************	*/
	virtual void Allocation();

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

/* **************************************************************************
METHODE :		Power
TRAITEMENT:		Mise en route de l'équipement
***************************************************************************	*/
	BOOL Power();

/* **************************************************************************
METHODE :		Test
TRAITEMENT:		Retourne le code du Test
***************************************************************************	*/
	int Test() const;
/* **************************************************************************
METHODE :		ChangeTest
TRAITEMENT:		Modifie le code test
***************************************************************************	*/
	int ChangeTest(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Lock
TRAITEMENT:		Retourne la cle du clock, 0 non locké
***************************************************************************	*/
	int Lock() const;
/* **************************************************************************
METHODE :		ChangeLock
TRAITEMENT:		Modifie l'etat du Lock
***************************************************************************	*/
	int ChangeLock(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		EtatRelais
TRAITEMENT:		Retourne l'état du relais
***************************************************************************	*/
	int EtatRelais(int x,int y) const;
/* **************************************************************************
METHODE :		ChangeEtatRelais
TRAITEMENT:		Modifie l'etat d'un relais
***************************************************************************	*/
	int ChangeEtatRelais(int x, int y, int valeur, BOOL genere_TS);
};

#endif

