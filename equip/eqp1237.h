/*************************************************************************
FICHIER :	Eqp_1237.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _CEQUIP_1237
#define _CEQUIP_1237
/* **************************************************************************
NOM DU COMPOSANT : 		CEquip1237

ROLE DU COMPOSANT :		Classe Equipement Emetteur HF

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "Equip.h"

//const int	CDE_TEXTE_SEUL	=-1;		// pour Evoyer du texte
//const int	CDE_TEMPO_SEQ	=0;			// Temporisation dans les sequences

// Télésignalisation : EME pour Emetteur
const int	EME_1237_MODE_TRAFIC	= 1;		// Mx
const int	EME_1237_COMPRESSEUR	= 2;		// Zx
const int	EME_1237_MODE_FONCT	= 3;		// Bx
const int	EME_1237_FREQUENCE	= 4;		// Fx
const int	EME_1237_NIVEAU		= 5;		// Hx
const int	EME_1237_CANAL_POSI	= 6;		// Px
const int	EME_1237_CANAL_LECT	= 7;		// Cx
const int	EME_1237_OPTION		= 8;		// OPxy
const int	EME_1237_TEST		= 9;		// TST
const int	EME_1237_ETAT_LOGI	= 10;		// XX
const int	EME_1237_MODE_LOCAL	= 11;		// LOC/RMT/DOUBLE
const int	EME_1237_DATA_OUT	= 12;		// Y
const int	EME_1237_INCIDENT	= 13;		// Jxy
const int	EME_1237_INFO		= 14;		// T
const int	EME_1237_COUPLAGE 	= 15;		// XX_

typedef struct
{
	int		mode_trafic;		// Entre 0 et 5
	long	frequence;			// de 40000 à 29999990 Hz
	int		fonction;			// 0 à 9
}	t_canal_1237;

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquip1237:public CEquip
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
protected:
	int		local;				// 0=LOC, 1=RMT; 2=DBL

	int		couplage;

	int		l11;
	int		spin;

	int		canal;
	t_canal_1237	carac_canal[100];

	int		compresseur;		// 0 ou 1

	int		incident;			// -1=permanent,sinon de 0 à 99

	int		auto_niveau;
	int		choix_niveau;		// de 0 à 7
	int		niveau;				// de 0 à 0xFF

	int		test;				// Resultat du test

	int		info;				// Présence info


/* **************************************************************************
METHODE :		CEquip1237()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquip1237(int idx);

/* **************************************************************************
METHODE :		~CEsuipEmHF()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CEquip1237();

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
METHODE :		Local
TRAITEMENT:		Retourne le mode local
***************************************************************************	*/
	int Local() const;
/* **************************************************************************
METHODE :		ChangeLocal
TRAITEMENT:		Modifie le mode de trafic et eventuellement génère une TS
***************************************************************************	*/
	int ChangeLocal(int mode,BOOL genere_TS);

/* **************************************************************************
METHODE :		ModeTrafic
TRAITEMENT:		Retourne le mode de trafic
***************************************************************************	*/
	int ModeTrafic(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeModeTrafic
TRAITEMENT:		Modifie le mode de trafic et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeModeTrafic(int num_canal,int mode,BOOL genere_TS);

/* **************************************************************************
METHODE :		Compresseur
TRAITEMENT:		Retourne l'état du compresseur
***************************************************************************	*/
	int Compresseur() const;
/* **************************************************************************
METHODE :		ChangeCompresseur
TRAITEMENT:		Modifie l'état du compresseur
***************************************************************************	*/
	int ChangeCompresseur(int mode,BOOL genere_TS);

/* **************************************************************************
METHODE :		Fonction
TRAITEMENT:		Retourne le mode de fonctionnement
***************************************************************************	*/
	int Fonction(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeFonction
TRAITEMENT:		Modifie le mode focntionnement
***************************************************************************	*/
	int ChangeFonction(int num_canal,int mode,BOOL genere_TS);

/* **************************************************************************
METHODE :		Incident
TRAITEMENT:		Retourne le code incident
***************************************************************************	*/
	int Incident() const;
/* **************************************************************************
METHODE :		ChangeIncident
TRAITEMENT:		Modifie le code incident
***************************************************************************	*/
	int ChangeIncident(int mode,BOOL genere_TS);

/* **************************************************************************
METHODE :		Frequence
TRAITEMENT:		Retourne la valeur de la frequence
***************************************************************************	*/
	long Frequence(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeFrequence
TRAITEMENT:		Modifie la frequence d'accord
***************************************************************************	*/
	long ChangeFrequence(int num_canal,long valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AutoNiveau
TRAITEMENT:		Retourne l'état de variation automatique du niveau analogique
***************************************************************************	*/
	int AutoNiveau() const;
/* **************************************************************************
METHODE :		ChangeAutoNiveau
TRAITEMENT:		Modifie l'état de variation automatique du Niveau
***************************************************************************	*/
	int ChangeAutoNiveau(int valeur);

/* **************************************************************************
METHODE :		Niveau
TRAITEMENT:		Retourne la valeur du niveau analogique
***************************************************************************	*/
	int Niveau() const;
/* **************************************************************************
METHODE :		ChangeNIveau
TRAITEMENT:		Modifie la valeur du niveau analogique
***************************************************************************	*/
	int ChangeNiveau(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		ChoixNiveau
TRAITEMENT:		Retourne le choix du niveau analogique à visualiser
***************************************************************************	*/
	int ChoixNiveau() const;
/* **************************************************************************
METHODE :		ChangeChoixNiveau
TRAITEMENT:		Modifie le choix du niveau analogique à visualiser
***************************************************************************	*/
	int ChangeChoixNiveau(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Canal
TRAITEMENT:		Retourne le N° de canal exploité
***************************************************************************	*/
	int Canal() const;
/* **************************************************************************
METHODE :		ChangeCanal
TRAITEMENT:		Se positionne sur un nouveau canal
***************************************************************************	*/
	int ChangeCanal(int valeur,BOOL genere_TS);
/* **************************************************************************
METHODE :		MemoriseCanal
TRAITEMENT:		Modification d'un canal
***************************************************************************	*/
	int MemoriseCanal(int valeur,BOOL genere_TS);

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
METHODE :		Info
TRAITEMENT:		Retourne la valeur du seuil de la fonction Cor/Squelch
***************************************************************************	*/
	int Info() const;
/* **************************************************************************
METHODE :		ChangeInfo
TRAITEMENT:		Modifie la valeur du seuil de la fonction Cor/Squelch
***************************************************************************	*/
	int ChangeInfo(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		L11
TRAITEMENT:		Retourne le mode L11
***************************************************************************	*/
	virtual int L11() const;

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

/* **************************************************************************
METHODE :		Couplage
TRAITEMENT:		Retourne l'état du couplage
***************************************************************************	*/
	virtual int Couplage() const;
/* **************************************************************************
METHODE :		ChangeCouplage
TRAITEMENT:		Modifie l'état du couplage
***************************************************************************	*/
	virtual int ChangeCouplage(int valeur,BOOL genere_TS);
};

#endif

