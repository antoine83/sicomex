/*************************************************************************
FICHIER :	Eqp_Acco.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _CEQUIPACCORD
#define _CEQUIPACCORD
/* **************************************************************************
NOM DU COMPOSANT : 		CEquipAccord

ROLE DU COMPOSANT :		Classe Equipement Emetteur HF

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "..\Equip\Equip.h"	

const int 	ALARME_ROS  	= 20;
const int 	ALARME_TMP  	= 21;
const int 	ALARME_ALIM 	= 23;
const int 	ALARME_TUN  	= 24;				// A voir
const int 	ALARME_CPU  	= 31;				// A voir

const int 	OP_IDLE  		= 0;
const int 	OP_TUNING  		= 1;
const int 	OP_SELFTEST		= 2;
const int 	OP_AUTOTUNING  	= 3;

const int	TAILLE_CHAINE	= 20;

//const int	CDE_TEXTE_SEUL	=-1;		// pour Evoyer du texte
//const int	CDE_TEMPO_SEQ	=0;			// Temporisation dans les sequences

// Télésignalisation : ACD pour Accord
const int	ACD_ALARME	= 1;		// ALM
/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquipAccord:public CEquip
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
	int		echo;
	int		manuel;

	int		selecte_alarme;
	int		alarme[100];

	int		mode;		// Mode de fonctionnement

	int		frequence;

	int		operation;

	int		no_xmit;

	int		accord;

	int		auto_induc;
	int		inductance;

	int		auto_capa;
	int		capacite;

	int		auto_tos;
	int		tos;

	int		etat;	// etat de l'operation TUN

	char	chaine[5][TAILLE_CHAINE+1];

/* **************************************************************************
METHODE :		CEquipAccord()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquipAccord(int idx);

/* **************************************************************************
METHODE :		~CEsuipEmHF()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CEquipAccord();

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
METHODE :		Manuel
TRAITEMENT:		Retourne l'état du mode manuel
***************************************************************************	*/
	int Manuel() const;
/* **************************************************************************
METHODE :		ChangeManuel
TRAITEMENT:		Modifie l'état du mode manuel
***************************************************************************	*/
	int ChangeManuel(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Echo
TRAITEMENT:		Retourne l'état de l'echo
***************************************************************************	*/
	int Echo() const;
/* **************************************************************************
METHODE :		ChangeEcho
TRAITEMENT:		Modifie l'état de l'echo
***************************************************************************	*/
	int ChangeEcho(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		SelecteAlarme
TRAITEMENT:		Retourne la Selection de l'alarme
***************************************************************************	*/
	int SelecteAlarme() const;
/* **************************************************************************
METHODE :		ChangeSelecteAlarme
TRAITEMENT:		Modifie la selection de l'alarme
***************************************************************************	*/
	int ChangeSelecteAlarme(int valeur,BOOL genere_TS);
/* **************************************************************************
METHODE :		Alarme
TRAITEMENT:		Retourne le code alarme
***************************************************************************	*/
	int Alarme(int num) const;
/* **************************************************************************
METHODE :		ChangeAlarme
TRAITEMENT:		Modifie le Code alarme
***************************************************************************	*/
	int ChangeAlarme(int num,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Mode
TRAITEMENT:		Retourne le mode de fonctionnement TF ou RX
***************************************************************************	*/
	int Mode() const;
/* **************************************************************************
METHODE :		ChangeMode
TRAITEMENT:		Modifie le mode de fonctionnement
***************************************************************************	*/
	int ChangeMode(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Frequence
TRAITEMENT:		Retourne la valeur de la frequence
***************************************************************************	*/
	int Frequence() const;
/* **************************************************************************
METHODE :		ChangeFrequence
TRAITEMENT:		Modifie la frequence
***************************************************************************	*/
	int ChangeFrequence(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Operation
TRAITEMENT:		Retourne l'operation en cours
***************************************************************************	*/
	int Operation() const;
/* **************************************************************************
METHODE :		ChangeOperation
TRAITEMENT:		Modifie l'operation en cours
***************************************************************************	*/
	int ChangeOperation(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		NoXmit
TRAITEMENT:		Retourne l'état de NO XMIT
***************************************************************************	*/
	int NoXmit() const;
/* **************************************************************************
METHODE :		ChangeNoXmit
TRAITEMENT:		Modifie l'état NO XMIT
***************************************************************************	*/
	int ChangeNoXmit(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Accord
TRAITEMENT:		Retourne le type d'accord
***************************************************************************	*/
	int Accord() const;
/* **************************************************************************
METHODE :		ChangeAccord
TRAITEMENT:		Modifie le type d'accord
***************************************************************************	*/
	int ChangeAccord(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AutoInduc
TRAITEMENT:		Retourne l'état d'auto induction
***************************************************************************	*/
	int AutoInduc() const;
/* **************************************************************************
METHODE :		ChangeAutoInduc
TRAITEMENT:		Modifie l'état d'auto induction
***************************************************************************	*/
	int ChangeAutoInduc(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Inductance
TRAITEMENT:		Retourne la valeur de la banque d'inductance
***************************************************************************	*/
	int Inductance() const;
/* **************************************************************************
METHODE :		ChangeInductance
TRAITEMENT:		Modifie la valeur de la banque d'inductance
***************************************************************************	*/
	int ChangeInductance(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AutoCapa
TRAITEMENT:		Retourne l'état d'auto capacite
***************************************************************************	*/
	int AutoCapa() const;
/* **************************************************************************
METHODE :		ChangeAutoCapa
TRAITEMENT:		Modifie l'état d'auto capacite
***************************************************************************	*/
	int ChangeAutoCapa(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Capacite
TRAITEMENT:		Retourne la valeur de la banque de capacite
***************************************************************************	*/
	int Capacite() const;
/* **************************************************************************
METHODE :		ChangeCapacite
TRAITEMENT:		Modifie la valeur de la banque de capacite
***************************************************************************	*/
	int ChangeCapacite(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AutoTos
TRAITEMENT:		Retourne l'état d'auto TOS
***************************************************************************	*/
	int AutoTos() const;
/* **************************************************************************
METHODE :		ChangeAutoTos
TRAITEMENT:		Modifie l'état d'auto TOS
***************************************************************************	*/
	int ChangeAutoTos(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Tos
TRAITEMENT:		Retourne le TOS
***************************************************************************	*/
	int Tos() const;
/* **************************************************************************
METHODE :		ChangeTos
TRAITEMENT:		Modifie la valeur du TOS
***************************************************************************	*/
	int ChangeTos(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Etat
TRAITEMENT:		Retourne l'etat
***************************************************************************	*/
	int Etat() const;
/* **************************************************************************
METHODE :		ChangeEtat
TRAITEMENT:		Modifie l'etat
***************************************************************************	*/
	int ChangeEtat(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Chaine
TRAITEMENT:		Retourne la chaine
***************************************************************************	*/
	int Chaine(int index, char *reponse) const;
/* **************************************************************************
METHODE :		ChangeChaine
TRAITEMENT:		Modifie le contenu de la chaine'etat
***************************************************************************	*/
	int ChangeChaine(int index,char *message,BOOL genere_TS);

};

#endif

