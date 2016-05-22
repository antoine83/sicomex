/*************************************************************************
FICHIER :	Eqp_Std.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _CEQUIPSTD
#define _CEQUIPSTD
/* **************************************************************************
NOM DU COMPOSANT : 		CEquipStd

ROLE DU COMPOSANT :		Classe Equipement Standard HF

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "..\Equip\Equip.h"	

//const int	CDE_TEXTE_SEUL	=-1;		// pour Evoyer du texte
//const int	CDE_TEMPO_SEQ	=0;			// Temporisation dans les sequences

// Télésignalisation : STD pour Standard
const int	STD_TEST			= 1;		// Auto test
const int	STD_COMMUTATION		= 2;		// Commutation
const int	STD_SILENCE			= 3;		// Silence Radio
const int	STD_AVARIE_REL		= 4;		// Avarie relais
const int	STD_AVARIE_TENSION 	= 5;
const int	STD_AVARIE_HISSAGE 	= 6;
const int	STD_AVARIE_NOXMIT 	= 7;

const int	STD_AVARIE_TEMP 	= 8;

const int	STD_LOCAL 			= 9;
const int	STD_XMIT_1 			= 10;
const int	STD_XMIT_2 			= 11;
const int	STD_MAT_1		 	= 12;
const int	STD_MAT_2		 	= 13;


/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquipStd:public CEquip
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
	int		etat_incorrect;		// etat incorrect :0 ou 1	

	int		baa;			// 1 ou 2	
	int		emet;			// 1 ou 2	
	int		recep;			// 1 ou 2	

	int		silence_radio;	// 0 ou 1

	int		accorde;		// 0 ou 1	

	int		avarie;			// 1 à 7
	int		absence_tension;// 0 ou 1
	int		non_hissage;	// 0 ou 1
	int		no_xmit;		// 0 ou 1

	int		local;		// 0= local ; 1 = distant
	int		xmit_1;		// 0 ou 1
	int		xmit_2;		// 0 ou 1
	int		mat_1;		// 0 ou 1
	int		mat_2;		// 0 ou 1
	int		temperature;		// 0 ou 1

/* **************************************************************************
METHODE :		CEquipStd()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquipStd(int idx);

/* **************************************************************************
METHODE :		~CEsuipStd()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CEquipStd();

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
METHODE :		EtatIncorrect
TRAITEMENT:		Retourne si l'état est incorrect
***************************************************************************	*/
	int EtatIncorrect() const;
/* **************************************************************************
METHODE :		ChangeEtatIncorrect
TRAITEMENT:		Modifie l'etat incorrect de l'equipement
***************************************************************************	*/
	int ChangeEtatIncorrect(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Baa
TRAITEMENT:		Retourne la BAA sélectionnée
***************************************************************************	*/
	int Baa() const;
/* **************************************************************************
METHODE :		ChangeBaa
TRAITEMENT:		Modifie la sélection de la BAA
***************************************************************************	*/
	int ChangeBaa(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Emet
TRAITEMENT:		Retourne le numero d'emetteur sélectionné
***************************************************************************	*/
	int Emet() const;
/* **************************************************************************
METHODE :		ChangeEmet
TRAITEMENT:		Modifie la sélection de l'emetteur
***************************************************************************	*/
	int ChangeEmet(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Recep
TRAITEMENT:		Retourne le numero de récepteur sélectionné
***************************************************************************	*/
	int Recep() const;
/* **************************************************************************
METHODE :		ChangeRecep
TRAITEMENT:		Modifie la sélection du récepteur
***************************************************************************	*/
	int ChangeRecep(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Silence
TRAITEMENT:		Retourne l'état du silence radio
***************************************************************************	*/
	int SilenceRadio() const;
/* **************************************************************************
METHODE :		ChangeSilence
TRAITEMENT:		Modifie l'état de silence radio
***************************************************************************	*/
	int ChangeSilenceRadio(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Accorde
TRAITEMENT:		Retourne l'état de la réception accordé ou RLB
***************************************************************************	*/
	int Accorde() const;
/* **************************************************************************
METHODE :		ChangeAccorde
TRAITEMENT:		Modifie l'état de réception accordée
***************************************************************************	*/
	int ChangeAccorde(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Avarie
TRAITEMENT:		Retourne le code+1 d'avarie
***************************************************************************	*/
	int Avarie() const;
/* **************************************************************************
METHODE :		ChangeAvarie
TRAITEMENT:		Modifie le code d'avarie
***************************************************************************	*/
	int ChangeAvarie(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Absence
TRAITEMENT:		Retourne l'état du défaut absence tension
***************************************************************************	*/
	int AbsenceTension() const;
/* **************************************************************************
METHODE :		ChangeAbsence
TRAITEMENT:		Modifie l'état du défaut absence tension
***************************************************************************	*/
	int ChangeAbsenceTension(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		NonHissage
TRAITEMENT:		Retourne l'état du défaut "Mat non hissé"
***************************************************************************	*/
	int NonHissage() const;
/* **************************************************************************
METHODE :		ChangeNonHissage
TRAITEMENT:		Modifie l'état du défaut "Mat non hissé"
***************************************************************************	*/
	int ChangeNonHissage(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		NoXmit
TRAITEMENT:		Retourne l'état du défaut "no xmit"
***************************************************************************	*/
	int NoXmit() const;
/* **************************************************************************
METHODE :		ChangeNoXmit
TRAITEMENT:		Modifie l'état du défaut "no xmit"
***************************************************************************	*/
	int ChangeNoXmit(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Local
TRAITEMENT:		Retourne l'état loc/dis du standard
***************************************************************************	*/
	int Local() const;
/* **************************************************************************
METHODE :		ChangeLocal
TRAITEMENT:		Modifie l'état du loc/dis deu standard
***************************************************************************	*/
	int ChangeLocal(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Xmit_1
TRAITEMENT:		Retourne l'état xmit_1 du standard
***************************************************************************	*/
	int Xmit_1() const;
/* **************************************************************************
METHODE :		ChangeXmit_1
TRAITEMENT:		Modifie l'état du xmit_1 du standard
***************************************************************************	*/
	int ChangeXmit_1(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Xmit_2
TRAITEMENT:		Retourne l'état xmit_2 du standard
***************************************************************************	*/
	int Xmit_2() const;
/* **************************************************************************
METHODE :		ChangeXmit_2
TRAITEMENT:		Modifie l'état du xmit_2 du standard
***************************************************************************	*/
	int ChangeXmit_2(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Mat_1
TRAITEMENT:		Retourne l'état du mat 1 du standard
***************************************************************************	*/
	int Mat_1() const;
/* **************************************************************************
METHODE :		ChangeMat_1
TRAITEMENT:		Modifie l'état du mat 1 du standard
***************************************************************************	*/
	int ChangeMat_1(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Mat_2
TRAITEMENT:		Retourne l'état du mat 2 du standard
***************************************************************************	*/
	int Mat_2() const;
/* **************************************************************************
METHODE :		ChangeMat_2
TRAITEMENT:		Modifie l'état du mat 2 du standard
***************************************************************************	*/
	int ChangeMat_2(int valeur, BOOL genere_TS);

/* **************************************************************************
METHODE :		Temperature
TRAITEMENT:		Retourne l'état du defaut de temperatue du standard
***************************************************************************	*/
	int Temperature() const;
/* **************************************************************************
METHODE :		ChangeTemperature
TRAITEMENT:		Modifie l'état du defaut temperature du standard
***************************************************************************	*/
	int ChangeTemperature(int valeur, BOOL genere_TS);

};

#endif

