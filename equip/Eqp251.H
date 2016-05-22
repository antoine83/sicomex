/*************************************************************************
FICHIER :	Eqp_251.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _EQP_251
#define _EQP_251
/* **************************************************************************
NOM DU COMPOSANT : 		CEquip251

ROLE DU COMPOSANT :		Classe Equipement du récepteur HF

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "Equip.h"

const int	REC_251_NB_VOIE			= 4;
const int	REC_251_SEUIL_VITESSE	= 8; 	// Seuil vitesse de recherche en fct
											// des valeur du peigne

//const int	CDE_TEXTE_SEUL	=-1;		// pour Evoyer du texte
//const int	CDE_TEMPO_SEQ	=0;			// Temporisation dans les sequences

// Télésignalisation : REC pour recepteur HF
const int	REC_251_INIT			= 1;		// initialisation en mode console
const int	REC_251_ENQ				= 2;		// MES 5
const int	REC_251_ACK				= 3;		// MES 6
const int	REC_251_BEL				= 4;		// MES 7

const int	REC_251_CONFIG_OP		= 5;		// MES 60 : config operationnelle
const int	REC_251_POLARITE		= 6;		// MES 61
const int	REC_251_FREQUENCE		= 7;		// MES 63
const int	REC_251_FREQ_BFO		= 8;		// MES 64
const int	REC_251_TRAFIC			= 9;		// MES 65
const int	REC_251_ATTENUATION		= 10;		// MES 66
const int	REC_251_LIMITTEUR		= 11;		// MES 67
const int	REC_251_MODE_INTERFACE	= 12;		// MES 68
const int	REC_251_ENTREE_CANAL	= 13;		// MES 70
const int	REC_251_POLARITE_CANAL	= 14;		// MES 71
const int	REC_251_SORTIE_CANAL	= 15;		// MES 72
const int	REC_251_FREQUENCE_CANAL	= 16;		// MES 73
const int	REC_251_FREQ_BFO_CANAL	= 17;		// MES 74
const int	REC_251_ATTENUATION_CANAL	= 18;	// MES 76
const int	REC_251_LIMITEUR_CANAL	= 19;		// MES 77
const int	REC_251_MODUL_INTERF_CANAL	= 20;	// MES 78
const int	REC_251_STOCKAGE_CANAL	= 21;		// MES 80
const int	REC_251_ETAT_TEST		= 22;		// MES 81,82,83
const int	REC_251_CAG				= 23;		// MES 110
const int	REC_251_SYNCHRONISATION_BIT	= 24;		// MES 111
const int	REC_251_SYNCHRONISATION_TRAME1	= 25;		// MES 111
const int	REC_251_SYNCHRONISATION_TRAME2	= 26;		// MES 111
const int	REC_251_SYNCHRONISATION_TRAME3	= 27;		// MES 111
const int	REC_251_SYNCHRONISATION_TRAME4	= 28;		// MES 111
const int	REC_251_QUALITE_BIT		= 29;		// MES 112
const int	REC_251_NOTE_FIBO1		= 30;		// MES 113
const int	REC_251_NOTE_FIBO2		= 31;		// MES 113
const int	REC_251_NOTE_FIBO3		= 32;		// MES 113
const int	REC_251_NOTE_FIBO4		= 33;		// MES 113
const int	REC_251_NUM_PEIGNE		= 34;		// MES 114
const int	REC_251_DEFAUT			= 35;		// MES 115
const int	REC_251_MODE_LOCAL		= 36;	// MES 116/117 

typedef struct
{	
	int 	frequence;			// entre 10000 et 99999 Hz
	int		bfo;				// entre 0 et 7990 Hz
	int 	attenuation;		// entre 0, 1 ou 2
	int 	cag;				// 0 ou 1
	int		limiteur;			// 0 ou 1

	int		mode_reception;		// 0 à 9
	int		voie_active[REC_251_NB_VOIE];
	int		interfaces[REC_251_NB_VOIE];			
	int		polarite[REC_251_NB_VOIE];
}	t_canal_251;

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquip251:public CEquip
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
protected:
	int		phase_init;
	time_t	duree_ini;

	int		telecommande;		// Liaison telecommande ou console
	int		trafic;
	int		local;

	int		canal;				// 0 à 99, 0= canal d'exploitation
	t_canal_251	carac_canal[100+1];

	int		etat_test;		// 0,1 ou 2
	int		auto_alarme;	// <=> arret alarme 0,1
	int		defaut_0;		// defaut general
	int		defaut_1;		// Def carte demodulateur
	int		defaut_2;		// Def carte Stanag
	int		defaut_3;		// Def carte Interface

	int		q_bit_mini;		// 0 à 127
	int		auto_mini;

	int		q_bit_maxi;		// 0 à 127
	int		auto_maxi;
	
	int		etat_synchro;				// 0 , 1 ou 2
	int		fibo[REC_251_NB_VOIE];		// 0 à 100
	int		auto_fibo;
	int		peigne;	// 0 à 15
	int		auto_peigne;
	int		vitesse_recherche; // 0 ou 1
	int		synchro_trame[REC_251_NB_VOIE];		// 0 à 100


/* **************************************************************************
METHODE :		CEquip251()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquip251(int idx);

/* **************************************************************************
METHODE :		~CEsuipRecHF()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CEquip251();

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
METHODE :		FinPhaseInit
TRAITEMENT:		Indique la fin de la phase d'ini
***************************************************************************	*/
	int FinPhaseInit();

/* **************************************************************************
METHODE :		Telecommande
TRAITEMENT:		Retourne l'état du mode liaison Telecommande ou console
***************************************************************************	*/
	int Telecommande() const;
/* **************************************************************************
METHODE :		ChangeTelecommande
TRAITEMENT:		Modifie l'état du mode liaison Telecommande ou console et 
				eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeTelecommande(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Trafic
TRAITEMENT:		Retourne l'état du mode Trafic
***************************************************************************	*/
	int Trafic() const;
/* **************************************************************************
METHODE :		ChangeTrafic
TRAITEMENT:		Modifie l'état du mode Trafic et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeTrafic(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Local
TRAITEMENT:		Retourne l'état du mode Loac/distance
***************************************************************************	*/
	int Local() const;
/* **************************************************************************
METHODE :		ChangeLocal
TRAITEMENT:		Modifie l'état du mode Local et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeLocal(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Canal
TRAITEMENT:		Retourne le Canal operationel
***************************************************************************	*/
	int Canal() const;
/* **************************************************************************
METHODE :		ChangeCanal
TRAITEMENT:		Modifie le canal operationel et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeCanal(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		MemoriseCanal
TRAITEMENT:		Mémorise les donnees operationnelle dans canal et 
				eventuellement génère une TS
***************************************************************************	*/
	int MemoriseCanal(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		ModeRecep
TRAITEMENT:		Retourne le mode de réception
***************************************************************************	*/
	int ModeRecep(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeModeRecep
TRAITEMENT:		Modifie le mode de réception et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeModeRecep(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Frequence
TRAITEMENT:		Retourne la frequence d'antenne
***************************************************************************	*/
	int Frequence(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeFrequence
TRAITEMENT:		Modifie la frequence d'antenne et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeFrequence(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Bfo
TRAITEMENT:		Retourne la frequence Bfo
***************************************************************************	*/
	int Bfo(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeBfo
TRAITEMENT:		Modifie la frequence Bfo et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeBfo(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Attenuation
TRAITEMENT:		Retourne l'attenuation
***************************************************************************	*/
	int Attenuation(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeAttenuation
TRAITEMENT:		Modifie l'attenuation et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeAttenuation(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Cag
TRAITEMENT:		Retourne l'etat du Cag
***************************************************************************	*/
	int Cag(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeCag
TRAITEMENT:		Modifie l'etat du Cag et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeCag(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Limiteur
TRAITEMENT:		Retourne l'etat du Limiteur
***************************************************************************	*/
	int Limiteur(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeLimiteur
TRAITEMENT:		Modifie l'etat du Limiteur et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeLimiteur(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		VoieActive
TRAITEMENT:		Retourne l'etat des voies
***************************************************************************	*/
	int VoieActive(int	num_canal,int *etat) const;

/* **************************************************************************
METHODE :		Interface
TRAITEMENT:		Retourne les interfaces des voies
***************************************************************************	*/
	int Interface(int	num_canal,int *valeur) const;

/* **************************************************************************
METHODE :		ChangeInterface
TRAITEMENT:		Modifie les interfaces et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeInterface(int	num_canal,int *valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Polarite
TRAITEMENT:		Retourne la polarite des voies
***************************************************************************	*/
	int Polarite(int	num_canal,int *valeur) const;

/* **************************************************************************
METHODE :		ChangePolarite
TRAITEMENT:		Modifie la polarite et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangePolarite(int	num_canal,int *valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		EtatTest
TRAITEMENT:		Retourne l'etat du test
***************************************************************************	*/
	int EtatTest() const;
/* **************************************************************************
METHODE :		ChangeEtatTest
TRAITEMENT:		Modifie l'etat du test et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeEtatTest(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AutoAlarme
TRAITEMENT:		Retourne l'etat du AutoAlarme
***************************************************************************	*/
	int AutoAlarme() const;
/* **************************************************************************
METHODE :		ChangeAutoAlarme
TRAITEMENT:		Modifie l'etat du AutoAlarme et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeAutoAlarme(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Defaut
TRAITEMENT:		Retourne la valeur du defaut general
***************************************************************************	*/
	int Defaut() const;
/* **************************************************************************
METHODE :		ChangeDefaut
TRAITEMENT:		Modifie la valeur du defaut general et eventuellement génère 
				une TS
***************************************************************************	*/
	virtual int ChangeDefaut(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		DefautCarte1
TRAITEMENT:		Retourne la valeur du defaut carte 1
***************************************************************************	*/
	int DefautCarte1() const;
/* **************************************************************************
METHODE :		ChangeDefautCarte1
TRAITEMENT:		Modifie la valeur du defaut carte1 et eventuellement génère 
				une TS
***************************************************************************	*/
	virtual int ChangeDefautCarte1(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		DefautCarte2
TRAITEMENT:		Retourne la valeur du defaut carte 1
***************************************************************************	*/
	int DefautCarte2() const;
/* **************************************************************************
METHODE :		ChangeDefautCarte2
TRAITEMENT:		Modifie la valeur du defaut carte1 et eventuellement génère 
				une TS
***************************************************************************	*/
	virtual int ChangeDefautCarte2(int valeur,BOOL genere_TS);
/* **************************************************************************
METHODE :		DefautCarte3
TRAITEMENT:		Retourne la valeur du defaut carte 1
***************************************************************************	*/
	int DefautCarte3() const;
/* **************************************************************************
METHODE :		ChangeDefautCarte3
TRAITEMENT:		Modifie la valeur du defaut carte1 et eventuellement génère 
				une TS
***************************************************************************	*/
	virtual int ChangeDefautCarte3(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		QBitMini
TRAITEMENT:		Retourne la qualite de bit mini
***************************************************************************	*/
	int QBitMini() const;
/* **************************************************************************
METHODE :		ChangeQBitMini
TRAITEMENT:		Modifie la qualite de bit mini et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeQBitMini(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AutoMini
TRAITEMENT:		Retourne l'etat de auto Qbit mini
***************************************************************************	*/
	int AutoMini() const;
/* **************************************************************************
METHODE :		ChangeAutoMini
TRAITEMENT:		Modifie l'etat du AutoQBit mini et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeAutoMini(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		QBitMaxi
TRAITEMENT:		Retourne la qualite de bit maxi
***************************************************************************	*/
	int QBitMaxi() const;
/* **************************************************************************
METHODE :		ChangeQBitMaxi
TRAITEMENT:		Modifie la qualite de bit maxi et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeQBitMaxi(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AutoMaxi
TRAITEMENT:		Retourne l'etat de auto Qbit maxi
***************************************************************************	*/
	int AutoMaxi() const;
/* **************************************************************************
METHODE :		ChangeAutoMaxi
TRAITEMENT:		Modifie l'etat du AutoQBit maxi et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeAutoMaxi(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		EtatSynchro
TRAITEMENT:		Retourne l' Etat de la Synchro
***************************************************************************	*/
	int EtatSynchro() const;
/* **************************************************************************
METHODE :		ChangeEtatSynchro
TRAITEMENT:		Modifie l'EtatSynchro et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeEtatSynchro(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Fibo
TRAITEMENT:		Retourne les note de fibo des voies
***************************************************************************	*/
	int Fibo(int *valeur) const;

/* **************************************************************************
METHODE :		ChangeFibo
TRAITEMENT:		Modifie les notes de fibo et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeFibo(int *valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AutoFibo
TRAITEMENT:		Retourne l'etat de auto FIBO
***************************************************************************	*/
	int AutoFibo() const;
/* **************************************************************************
METHODE :		ChangeAutoFibo
TRAITEMENT:		Modifie l'etat du Auto FIBO et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeAutoFibo(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Peigne
TRAITEMENT:		Retourne les n° de Peigne des voies
***************************************************************************	*/
	int Peigne() const;

/* **************************************************************************
METHODE :		ChangePeigne
TRAITEMENT:		Modifie les n° de Peigne et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangePeigne(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AutoPeigne
TRAITEMENT:		Retourne l'etat de auto Peigne
***************************************************************************	*/
	int AutoPeigne() const;
/* **************************************************************************
METHODE :		ChangeAutoPeigne
TRAITEMENT:		Modifie l'etat du Auto Peigne et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeAutoPeigne(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Vitesse
TRAITEMENT:		Retourne les vitesse de recherche synchro
***************************************************************************	*/
	int Vitesse() const;

/* **************************************************************************
METHODE :		SynchroTrame
TRAITEMENT:		Retourne les etat de synchro trame des voies
***************************************************************************	*/
	int SynchroTrame(int *valeur) const;

/* **************************************************************************
METHODE :		ChangeSynchroTrame
TRAITEMENT:		Modifie les les etat de synchro trame et eventuellement 
				génère une TS
***************************************************************************	*/
	virtual int ChangeSynchroTrame(int *valeur,BOOL genere_TS);
};
#endif

