/*************************************************************************
FICHIER :	Eqp18A.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _CEQUIP_18A
#define _CEQUIP_18A
/* **************************************************************************
NOM DU COMPOSANT : 		CEquip18A

ROLE DU COMPOSANT :		Classe Equipement de l'émetteur/récepteur UHF

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "..\Equip\Equip.h"	

//const int	CDE_TEXTE_SEUL	=-1;		// pour Evoyer du texte
//const int	CDE_TEMPO_SEQ	=0;			// Temporisation dans les sequences

// Télésignalisation : EMR pour Emmetteur/Recepteur
const int	EMR_EXPLOITATION	= 1;		// 0-D
const int	EMR_SURVEILLANCE	= 2;		// E
const int	EMR_STATUS			= 3;		// E

typedef struct
{
	int		frequence_Em;		// en 100 kHz : 100-155,9 MHz, 225-399,9 MHz
	int		niveau;				// 0 à 4
	int		accord_multi;		// 0=Accord demande, 1=non demandé depuis modif frquence
	int		mode;				// 0 à 9, 0xB, 0xC
	int		bande;				// 0 ou 1 WB/NB
	int		cle_crypto;			// 0 à 7
	int		antenne;			// 0 à 3
	int		squelch;			// 0 ou 1
	int		frequence_Rec;		// en 100 kHz : 100-155,9 MHz, 225-399,9 MHz
	int		pas_Em;				// 0 à 3
	int		pas_Rec;			// 0 à 3
	int		protection;			// 0 ou 1
}	t_canal_emr;
/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquip18A:public CEquip
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
protected:
	// Données d'exploitation
	int		numero;				// n° E/R = 12 d'apres essai
 	int		canal;				// -1:SCAN, 0 à 99
	t_canal_emr carac_canal[100];

	int		relais;				// 0 à 7
	int		rec_garde;			// TC :0 ou 1 ; TS : 0 à 3
 	int		scan_debut;			//  0 à 99, 00 pas de scan
 	int		scan_fin;			//  0 à 99, 00 pas de scan
	int		adresse;			// 0 à FF : par defaut FF
	int		reserve;			// 0 à 2;
	int		gene_crypto;		// 0 à 6

	// Surveillance/Status
	int		local;				// 0 ou 1
	int		panne_emr;
	int		panne_accord;

	int		HF_recu;			// 0 ou 1
	int		ros;				// 0 ou 1
	int		emission;			// 0 ou 1
	int		silence;			// 0 ou 1

	int		chiffre;			// 0 ou 1
	int		test_en_cours;		// 0 ou 1
	int		scan;				// 0 ou 1
	int		accord;				// 0 ou 1

	int		status_evol;		// 0 à F

	// Instruction
	int		code_test;
/* **************************************************************************
METHODE :		CEquip18A()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquip18A(int idx);

/* **************************************************************************
METHODE :		~CEsuipRecHF()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CEquip18A();

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
METHODE :		Evolution
TRAITEMENT:		Retourne la variable d'evolution
***************************************************************************	*/
	int StatusEvolution() const;
/* **************************************************************************
METHODE :		ChangeEvolution
TRAITEMENT:		Modifie la variable d'evolution
***************************************************************************	*/
	int ChangeStatusEvolution(int valeur);

/* **************************************************************************
METHODE :		Numero
TRAITEMENT:		Retourne le numero de l'E/R
***************************************************************************	*/
	int Numero() const;
/* **************************************************************************
METHODE :		ChangeNumero
TRAITEMENT:		Modifie le numero d'E/R
***************************************************************************	*/
	int ChangeNumero(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		FrequenceEm
TRAITEMENT:		Retourne la frequence d'emission
***************************************************************************	*/
	int FrequenceEm(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeFrequenceEm
TRAITEMENT:		Modifie la frquence d'emission et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeFrequenceEm(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Canal
TRAITEMENT:		Retourne le numero du canal préréglé
***************************************************************************	*/
	int Canal() const;
/* **************************************************************************
METHODE :		ChangeCanal
TRAITEMENT:		Modifie le n° de canal préréglé
***************************************************************************	*/
	int ChangeCanal(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Niveau
TRAITEMENT:		Retourne la valeur du niveau
***************************************************************************	*/
	int Niveau(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeNiveau
TRAITEMENT:		Modifie la valeur du niveau HF
***************************************************************************	*/
	int ChangeNiveau(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		AccordMulti
TRAITEMENT:		Retourne l'etat de l'accord multicoupleur
***************************************************************************	*/
	int AccordMulti(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeAccordMulti
TRAITEMENT:		Modifie ll'etat de l'accord multicoupleur
***************************************************************************	*/
	int ChangeAccordMulti(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Mode
TRAITEMENT:		Retourne le type de modualtion
***************************************************************************	*/
	int Mode(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeMode
TRAITEMENT:		Modifie le type de modulation
***************************************************************************	*/
	int ChangeMode(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Bande
TRAITEMENT:		Retourne la valeur de la bande
***************************************************************************	*/
	int Bande(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeBande
TRAITEMENT:		Modifie la valeur de la bande
***************************************************************************	*/
	int ChangeBande(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		CleCrypto
TRAITEMENT:		Retourne la valeur de la cle Crypto
***************************************************************************	*/
	int CleCrypto(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeCleCrypto
TRAITEMENT:		Modifie la valeur de la cle Crypto
***************************************************************************	*/
	int ChangeCleCrypto(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Antenne
TRAITEMENT:		Retourne la configuration antenne
***************************************************************************	*/
	int Antenne(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeAntenne
TRAITEMENT:		Modifie la configuration antenne
***************************************************************************	*/
	int ChangeAntenne(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Squelch
TRAITEMENT:		Retourne l'etat du squelch
***************************************************************************	*/
	int Squelch(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeSquelch
TRAITEMENT:		Modifie l'état du scquelch
***************************************************************************	*/
	int ChangeSquelch(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		FrequenceRec
TRAITEMENT:		Retourne la frequence de reception
***************************************************************************	*/
	int FrequenceRec(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeFrequenceRec
TRAITEMENT:		Modifie la ferquence de reception et eventuellement génère une TS
***************************************************************************	*/
	virtual int ChangeFrequenceRec(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		PasEm
TRAITEMENT:		Retourne la valeur du pas de 25 kHz de l'emetteur
***************************************************************************	*/
	int PasEm(int num_canal) const;
/* **************************************************************************
METHODE :		ChangePasEm
TRAITEMENT:		Modifie la valeur du pas de 25 kHz de l'emetteur
***************************************************************************	*/
	int ChangePasEm(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		PasRec
TRAITEMENT:		Retourne la valeur du pas de 25 kHz du recepteur
***************************************************************************	*/
	int PasRec(int num_canal) const;
/* **************************************************************************
METHODE :		ChangePasRec
TRAITEMENT:		Modifie la valeur du pas de 25 kHz du recepteur
***************************************************************************	*/
	int ChangePasRec(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Protection
TRAITEMENT:		Retourne l'état de la protection canal
***************************************************************************	*/
	int Protection(int num_canal) const;
/* **************************************************************************
METHODE :		ChangeProtection
TRAITEMENT:		Modifie l'état de la protection canal
***************************************************************************	*/
	int ChangeProtection(int num_canal,int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Relais
TRAITEMENT:		Retourne la valeur des relais
***************************************************************************	*/
	int Relais() const;
/* **************************************************************************
METHODE :		ChangeRelais
TRAITEMENT:		Modifie la valeur des relais
***************************************************************************	*/
	int ChangeRelais(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		RecGarde
TRAITEMENT:		Retourne l'etat du recepteur de garde
***************************************************************************	*/
	int RecGarde() const;
/* **************************************************************************
METHODE :		ChangeRecGarde
TRAITEMENT:		Modifie l'etat du recepteur de garde
***************************************************************************	*/
	int ChangeRecGarde(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		ScanDebut
TRAITEMENT:		Retourne le canal de debut de scan
***************************************************************************	*/
	int ScanDebut() const;
/* **************************************************************************
METHODE :		ChangeScanDebut
TRAITEMENT:		Modifie le canal de debut de scan
***************************************************************************	*/
	int ChangeScanDebut(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		ScanFin
TRAITEMENT:		Retourne le canal de Fin de scan
***************************************************************************	*/
	int ScanFin() const;
/* **************************************************************************
METHODE :		ChangeScanFin
TRAITEMENT:		Modifie le canal de Fin de scan
***************************************************************************	*/
	int ChangeScanFin(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Adresse
TRAITEMENT:		Retourne l'adresse de reservation par gestion radio centralisée
***************************************************************************	*/
	int Adresse() const;
/* **************************************************************************
METHODE :		ChangeAdresse
TRAITEMENT:		Modifie l'adresse de reservation par gestion radio centralisée
***************************************************************************	*/
	int ChangeAdresse(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Reserve
TRAITEMENT:		Retourne le type de réservation
***************************************************************************	*/
	int Reserve() const;
/* **************************************************************************
METHODE :		ChangeReserve
TRAITEMENT:		Modifie le type de réservation
***************************************************************************	*/
	int ChangeReserve(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		GeneCrypto
TRAITEMENT:		Retourne la clé crypto générale
***************************************************************************	*/
	int GeneCrypto() const;
/* **************************************************************************
METHODE :		ChangeGeneCrypto
TRAITEMENT:		Modifie  la clé crypto générale
***************************************************************************	*/
	int ChangeGeneCrypto(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		StatusEvol
TRAITEMENT:		Retourne la valeur de la variable d'évolution
***************************************************************************	*/
	int StatusEvol() const;

/* **************************************************************************
METHODE :		Local
TRAITEMENT:		Retourne l'état Local distance
***************************************************************************	*/
	int Local() const;
/* **************************************************************************
METHODE :		ChangeLocal
TRAITEMENT:		Modifie  l'état local distance
***************************************************************************	*/
	int ChangeLocal(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		PanneEmr
TRAITEMENT:		Retourne l'état de panne de l'EMR
***************************************************************************	*/
	int PanneEmr() const;
/* **************************************************************************
METHODE :		ChangePanneEmr
TRAITEMENT:		Modifie  l'état de panne de l'EMR
***************************************************************************	*/
	int ChangePanneEmr(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		PanneAccord
TRAITEMENT:		Retourne l'état de panne de l'Accord
***************************************************************************	*/
	int PanneAccord() const;
/* **************************************************************************
METHODE :		ChangePanneAccord
TRAITEMENT:		Modifie  l'état de panne de l'Accord
***************************************************************************	*/
	int ChangePanneAccord(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		HfRecu
TRAITEMENT:		Retourne l'état de réception de HF
***************************************************************************	*/
	int HfRecu() const;
/* **************************************************************************
METHODE :		ChangePanneMulti
TRAITEMENT:		Modifie l'état de réception de HF
***************************************************************************	*/
	int ChangeHfRecu(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Ros
TRAITEMENT:		Retourne l'état du ROS
***************************************************************************	*/
	int Ros() const;
/* **************************************************************************
METHODE :		ChangeRos
TRAITEMENT:		Modifie l'état du ROS
***************************************************************************	*/
	int ChangeRos(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Emission
TRAITEMENT:		Retourne l'état de emission en cours
***************************************************************************	*/
	int Emission() const;
/* **************************************************************************
METHODE :		ChangeEmission
TRAITEMENT:		Modifie l'état Emission
***************************************************************************	*/
	int ChangeEmission(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Silence
TRAITEMENT:		Retourne l'état Silence Radio
***************************************************************************	*/
	int Silence() const;
/* **************************************************************************
METHODE :		ChangeSilence
TRAITEMENT:		Modifie l'état Silence Radio
***************************************************************************	*/
	int ChangeSilence(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Chiffre
TRAITEMENT:		Retourne l'état presence de BF chiffre
***************************************************************************	*/
	int Chiffre() const;
/* **************************************************************************
METHODE :		ChangeChiffre
TRAITEMENT:		Modifie l'état presence de BF chiffre
***************************************************************************	*/
	int ChangeChiffre(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		TestEnCours
TRAITEMENT:		Retourne l'état Test en cours
***************************************************************************	*/
	int TestEnCours() const;
/* **************************************************************************
METHODE :		ChangeTestEnCours
TRAITEMENT:		Modifie l'état Test en cours
***************************************************************************	*/
	int ChangeTestEnCours(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Scan
TRAITEMENT:		Retourne l'état Scan en cours
***************************************************************************	*/
	int Scan() const;
/* **************************************************************************
METHODE :		ChangeScan
TRAITEMENT:		Modifie l'état Scan en cours
***************************************************************************	*/
	int ChangeScan(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Accord
TRAITEMENT:		Retourne l'état Accord multicoupleur en cours
***************************************************************************	*/
	int Accord() const;
/* **************************************************************************
METHODE :		ChangeAccord
TRAITEMENT:		Modifie l'état Accord multicoupleur en cours
***************************************************************************	*/
	int ChangeAccord(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		Test
TRAITEMENT:		Retourne la valeur du code Test
***************************************************************************	*/
	int Test() const;
/* **************************************************************************
METHODE :		ChangeTest
TRAITEMENT:		Modifie la valeur du code test
***************************************************************************	*/
	int ChangeTest(int valeur,BOOL genere_TS);

/* **************************************************************************
METHODE :		MemoriseCanal
TRAITEMENT:		Modification d'un canal
***************************************************************************	*/
	int MemoriseCanal(int valeur,BOOL genere_TS);

};

#endif

