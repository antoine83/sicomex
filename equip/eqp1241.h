/*************************************************************************
FICHIER :	Eqp_1241.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _EQP_1241
#define _EQP_1241
/* **************************************************************************
NOM DU COMPOSANT : 		CEquip1241

ROLE DU COMPOSANT :		Classe Equipement du récepteur HF

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "Equip.h"

//const int	CDE_TEXTE_SEUL	=-1;		// pour Evoyer du texte
//const int	CDE_TEMPO_SEQ	=0;			// Temporisation dans les sequences

// Télésignalisation : REC pour recepteur HF
const int	REC_1241_MODE_RECEP	= 1;		// Mx
const int	REC_1241_ATTENUATEUR	= 2;		// Ax
const int	REC_1241_FILTRE_FI	= 3;		// Kx
const int	REC_1241_CAG			= 4;		// Gx
const int	REC_1241_SQUELCH		= 5;		// Qx
const int	REC_1241_SENS_MANIP	= 6;		// Nx
const int	REC_1241_SHIFT		= 7;		// Ex
const int	REC_1241_FREQUENCE	= 8;		// Fxxxxxxxx
const int	REC_1241_BFO			= 9;		// B±xxx
const int	REC_1241_REJECTEUR	= 10;		// R±xxx
const int	REC_1241_NIVEAU_HF	= 11;		// Hxy
const int	REC_1241_MESUREUR	= 12;		// Vxy
const int	REC_1241_SEUIL_COR	= 13;		// Uxy
const int	REC_1241_CENTRAGE_F1	= 14;		// Lxy
const int	REC_1241_CANAL_POSI	= 15;		// Pxy
const int	REC_1241_CANAL_LECT	= 16;		// Cxy ...
const int	REC_1241_VEILLE_POSI	= 17;		// W0xy
const int	REC_1241_VEILLE_LECT	= 18;		// W1yx ...
const int	REC_1241_TEMPS_MAINT	= 19;		// W8vxy
const int	REC_1241_BALAY_POSI	= 20;		// W3xyfffffff
const int	REC_1241_BALAY_LECT	= 21;		// W4xyfffffff
const int	REC_1241_VITESSE_BAL	= 22;		// W9v
const int	REC_1241_OPTION_REC	= 23;		// OPxyz
const int	REC_1241_TEST		= 24;		// TSTxy
const int	REC_1241_INFO		= 25;		// Tx
const int	REC_1241_BALAYAGE	= 26;		// Zxywz
const int	REC_1241_ETAT_LOGI	= 27;		// XXy
const int	REC_1241_MODE_LOCAL	= 28;		// LOC

typedef struct
{	
	int 	mode_reception;		// entre 0 et 5
	int		filtre;				// entre 0 et 9
	int 	attenuateur;		// entre 1 et 2
	int 	cag;				// 0,1,2,3,4 pour #,>,=,<
	int		squelch;			// 0 ou 1

	long	frequence;			// de 00010000 à 29999999 Hz
	int		bfo;				// de -7990 Hz à 7990 Hz

	int		sens_manip;			// 0,1,2,3
	int		shift;				// de 0 à 4

	int		gainHF;				// valeur du gain HF : 0 à 255
	int		mesureur;			// valeur du gain HF : 0 à 108
}	t_canal_1241;

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquip1241:public CEquip
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
protected:
	int		l11;
	int		spin;

	int		canal;				// 0 à 99, 0= canal d'exploitation
	t_canal_1241	carac_canal[100];

	int		auto_mesureur;		// variation automatique

	int		rejecteur;			// sans ou avec rejecteur
	int		freq_reject;		// freq reject[-3990,3990] kHz;


	int		cor_squelch;		// Seuil de la fonction COR/Squelch :0 à 108

	int		auto_centrage_F1;	// variation automatique
	int		centrage_F1;		// 0 à 077	(en octal)

	int		veille[99];			// canal de veille 0 à 98

	int		temps_maintien[3];	// Temps de maintien

	long	frequence_balayage[20];	// Bande de frequence de balayage

	int		vitesse_balayage[3];// vitesse de balayage

	int		test;				// code test

	int		info;				// Présence info

	int		local;
/* **************************************************************************
METHODE :		CEquip1241()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquip1241(int idx);

/* **************************************************************************
METHODE :		~CEsuipRecHF()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CEquip1241();

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
METHODE :		ModeRecep
TRAITEMENT:		Retourne le mode de réception
***************************************************************************	*/
	int Attenuateur(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeModeRecep
TRAITEMENT:		Modifie le mode de réception et eventuellement génère une TS
***************************************************************************	*/
	int ChangeAttenuateur(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		FiltreFI
TRAITEMENT:		Retourne le Filtre FI selectionnee
***************************************************************************	*/
	int FiltreFI(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeFiltreFI
TRAITEMENT:		Modifie la sélection des filtres FI et eventuellement génère
				une TS
***************************************************************************	*/
	int ChangeFiltreFI(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Cag
TRAITEMENT:		Retourne le Cag
***************************************************************************	*/
	int Cag(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeCag
TRAITEMENT:		Modifie le Cag et eventuellement génère	une TS
***************************************************************************	*/
	int ChangeCag(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Squelch
TRAITEMENT:		Retourne l'etat du squelch
***************************************************************************	*/
	int Squelch(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeSquelch
TRAITEMENT:		Modifie l'etat du squelch et eventuellement génère une TS
***************************************************************************	*/
	int ChangeSquelch(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		SensManip
TRAITEMENT:		Retourne la valeur du sens de manipulation télégraphique
***************************************************************************	*/
	int SensManip(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeSensManip
TRAITEMENT:		Modifie le sens de manipulation télégraphique
***************************************************************************	*/
	int ChangeSensManip(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Shift
TRAITEMENT:		Retourne la valeur du shift
***************************************************************************	*/
	int Shift(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeShift
TRAITEMENT:		Modifie le Shift
***************************************************************************	*/
	int ChangeShift(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Frequence
TRAITEMENT:		Retourne la valeur de la frequence
***************************************************************************	*/
	long Frequence(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeFrequence
TRAITEMENT:		Modifie la frequence d'accord
***************************************************************************	*/
	long ChangeFrequence(int	num_canal,long valeur,BOOL genere_TS);
/* **************************************************************************
METHODE :		IncrementeFrequence
TRAITEMENT:		Modifie la frequence d'accord par un increment
***************************************************************************	*/
	long IncrementeFrequence(long valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Bfo
TRAITEMENT:		Retourne la valeur de la frequence BFO
***************************************************************************	*/
	int Bfo(int	num_canal) const;
/* **************************************************************************
METHODE :		ChangeBfo
TRAITEMENT:		Modifie la frequence BFO
***************************************************************************	*/
	int ChangeBfo(int	num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AvecRejecteur
TRAITEMENT:		Retourne le fonctionnenent avec rejecteur
***************************************************************************	*/
	int AvecRejecteur() const;
/* **************************************************************************
METHODE :		ChangeAvecRejecteur
TRAITEMENT:		Modifie le fonctionnement avec rejecteur FI
***************************************************************************	*/
	int ChangeAvecRejecteur(int valeur,BOOL genere_TS);
/* **************************************************************************
METHODE :		Rejecteur
TRAITEMENT:		Retourne la valeur de la frequence du Rejecteur FI
***************************************************************************	*/
	int Rejecteur() const;

/* **************************************************************************
METHODE :		ChangeRejecteur
TRAITEMENT:		Modifie la frequence du rejecteur FI
***************************************************************************	*/
	int ChangeRejecteur(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		GainHF
TRAITEMENT:		Retourne la valeur du gain HF
***************************************************************************	*/
	int GainHF(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeGainHF
TRAITEMENT:		Modifie la valeur du gain HF
***************************************************************************	*/
	int ChangeGainHF(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AutoMesureur
TRAITEMENT:		Retourne l'état de variation automatique du Mesureur
***************************************************************************	*/
	int AutoMesureur() const;
/* **************************************************************************
METHODE :		ChangeAutoMesureur
TRAITEMENT:		Modifie l'état de variation automatique du Mesureur
***************************************************************************	*/
	int ChangeAutoMesureur(int valeur);
/* **************************************************************************
METHODE :		Mesureur
TRAITEMENT:		Retourne la valeur du gain HF recu
***************************************************************************	*/
	int Mesureur(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeMesureur
TRAITEMENT:		Modifie la valeur du gain HF recu
***************************************************************************	*/
	int ChangeMesureur(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		CorSquelch
TRAITEMENT:		Retourne la valeur du seuil de la fonction Cor/Squelch
***************************************************************************	*/
	int CorSquelch() const;
/* **************************************************************************
METHODE :		ChangeCorSquelch
TRAITEMENT:		Modifie la valeur du seuil de la fonction Cor/Squelch
***************************************************************************	*/
	int ChangeCorSquelch(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AutoCentrageF1
TRAITEMENT:		Retourne l'état de variation automatique du centrage F1
***************************************************************************	*/
	int AutoCentrageF1() const;
/* **************************************************************************
METHODE :		ChangeAutoMesureur
TRAITEMENT:		Modifie l'état de variation automatique du Centrage F1
***************************************************************************	*/
	int ChangeAutoCentrageF1(int valeur);
/* **************************************************************************
METHODE :		CentrageF1
TRAITEMENT:		Retourne la valeur du Centrage F1
***************************************************************************	*/
	int CentrageF1() const;
/* **************************************************************************
METHODE :		ChangeCentrageF1
TRAITEMENT:		Modifie la valeur du Centrage F1
***************************************************************************	*/
	int ChangeCentrageF1(int valeur,BOOL genere_TS);

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
METHODE :		Veille
TRAITEMENT:		Retourne le N° de canal associé au pos ieme canal de veille
***************************************************************************	*/
	int Veille(int pos) const;
/* **************************************************************************
METHODE :		ChangeVeille
TRAITEMENT:		Se positionne sur un nouveau canal
***************************************************************************	*/
	int ChangeVeille(int pos,int valeur);

/* **************************************************************************
METHODE :		TempsMaintien
TRAITEMENT:		Retourne la valeur du temps de maintien	(TC uniquement)
***************************************************************************	*/
	int TempsMaintien(int degre) const;
/* **************************************************************************
METHODE :		ChangeTempsMaintien
TRAITEMENT:		Modifie la valeur du temps de maintien (TC uniquement)
***************************************************************************	*/
	int ChangeTempsMaintien(int degre, int valeur);

/* **************************************************************************
METHODE :		FrequenceBalayage
TRAITEMENT:		Retourne la fréquence associée au pos ieme position de bande
***************************************************************************	*/
	long FrequenceBalayage(int pos) const;
/* **************************************************************************
METHODE :		ChangeFrequenceBalayage
TRAITEMENT:		Associe une frequence à une position de bande
***************************************************************************	*/
	long ChangeFrequenceBalayage(int pos,long valeur);

/* **************************************************************************
METHODE :		VitesseBalayage
TRAITEMENT:		Retourne la vitesse de balayage	(TC uniquement)
***************************************************************************	*/
	int VitesseBalayage(int degre) const;
/* **************************************************************************
METHODE :		ChangeVitesseBalayage
TRAITEMENT:		Modifie la vitesse de balayage (TC uniquement)
***************************************************************************	*/
	int ChangeVitesseBalayage(int degre, int valeur);

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
METHODE :		Local
TRAITEMENT:		Retourne le mode Local
***************************************************************************	*/
	int Local() const;
/* **************************************************************************
METHODE :		ChangeLocal
TRAITEMENT:		Modifie le mode local/telecommande
***************************************************************************	*/
	int ChangeLocal(int valeur,BOOL genere_TS);

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
};
#endif

