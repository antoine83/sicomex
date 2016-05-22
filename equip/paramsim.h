/*************************************************************************
FICHIER :	ParamSimu.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _CPARAMSIMU
#define _CPARAMSIMU
/* ***********************************************************************
NOM DU COMPOSANT : 		CParamSimu

ROLE DU COMPOSANT :		Gestion des paramètres d'environnement du 
						simulateur

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	
	CDlgConfig			Fenêtre de configuration du simulateur
	CDlgAffecte			Fenêtre d'affectation des Liaisons/Equipements
***********************************************************************	*/
#include "Equip\Synchro.h"
#include "typ_glob.h"
#include "Equip\equip.h"
#include "Custom\Icone.h"
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

const int  NB_MAX_LIAISON = 51;		 	// Taille des repères
const int  TAILLE_REPERE = 20+2;		// Taille des repères

const int  EQP_NON_AFFECTE 		=0;
const int  EQP_BOITE_ACCORD 	=1;
const int  EQP_STANDARD_HF	 	=2;
const int  EQP_AUDIO_TTY	 	=3;
const int  EQP_TRC1225M			=4;

const int  EQP_TRBM18A	 		=5;
const int  EQP_TRBM18C			=6;

const int  EQP_TRC1241_FF 		=7;
const int  EQP_TRC1241_L11	 	=8;
const int  EQP_TRC1241_SPIN	 	=9;

const int  EQP_TRC1236_FF	 	=10;
const int  EQP_TRC1236_L11	 	=11;
const int  EQP_TRC1236_SPIN	 	=12;

const int  EQP_TRC1237_FF	 	=13;
const int  EQP_TRC1237_L11	 	=14;
const int  EQP_TRC1237_SPIN	 	=15;

const int  EQP_TRC251	 		=16;

const int  AAD_20_4				=17;
const int  AAD_20_8				=18;

const int  MATRICE_SPIN			=19;
const int  MATRICE_L11			=20;

const int  CA_150_MASTER		=21;
const int  CA_150_SLAVE			=22;

// CV24 card equipments.
const int  KY58					=23;
const int  ANDVT				=24;

const int  COMMUTATION_MATRIX   =25;

// TOR card equipments.
const int  TOR_KY58				=26;
const int  TOR_ANDVT			=27;
const int  TOR_CARD			    =28;

//Modem
const int MDM_TRC1752			=29;

// ED42
const int  ED42					=30;

// TEST
const int  Test					=31;


// TEST1
const int  Test1				=32;


const int  DEFAUT_TAILLE_JOURNAUX = 1000;

/* **********************************************************************
DONNEES EXTERNES :
	CSynchro				Gestion du top de synchronisation
***********************************************************************	*/

/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
class CIcone;

typedef struct				
{
	BOOL		affectable;
	int			type_eqp;				// Type équipement
	char		repere[TAILLE_REPERE];	// repère de la liaison
	t_format	format;					
	CEquip		*Eqp;					// Equipement
	BOOL		controle;
	BOOL		activite;				//
	CIcone		*icone;

} t_affecte;							// affectations Liaison/équipement

/*
struct t_affecte				
{
	BOOL		affectable;
	int			type_eqp;				// Type équipement
	char		repere[TAILLE_REPERE];	// repère de la liaison
	t_format	format;					
	CEquip		*Eqp;					// Equipement
	BOOL		controle;
	BOOL		activite;				//
	CIcone		*icone;

	t_affecte()
	{
		affectable = TRUE;
	}

} ;							// affectations Liaison/équipement
*/
class CParamSimu
{
private:
	int			max_liaison;					// Nombre maxi
	t_affecte	table_affecte[NB_MAX_LIAISON];	// Table d'affectation

	int			taille_journaux;				// Taille des journaux

	BOOL        top_externe;					// Top externe OUI/NON
	int         depart;		        // Heure de déclenchement (en s)
    int         periode;		   // Période

	CRITICAL_SECTION	crit;		// Section critique


/* **********************************************************************
METHODE :		CParamSimu()
TRAITEMENT:		Cronstruit l'objet
***********************************************************************	*/
public:
	CParamSimu();

/* **********************************************************************
METHODE :		~CParamSimu()
TRAITEMENT:		Destructeur
***********************************************************************	*/
	~CParamSimu();

/* **********************************************************************
METHODE :		MaxLiaison()
TRAITEMENT:		Recupère le nombre de liaisons
***********************************************************************	*/
	int MaxLiaison() const;

/* **********************************************************************
METHODE :		Modif_Nb_liaison()
TRAITEMENT:		Controle la modification du nombre de liaisons série
***********************************************************************	*/
	BOOL	Modif_Nb_liaison(int nb_liaison);

/* **********************************************************************
METHODE :		Affectable()
TRAITEMENT:		Récupère l'etat d'affectablilté de la ieme liaison
***********************************************************************	*/
int CParamSimu::Affectable(int i) const;

/* **********************************************************************
METHODE :		Modif_affectable()
TRAITEMENT:		Controle la modification de la declaration d'une liaison
***********************************************************************	*/
	BOOL	Modif_affectable(int num,BOOL affectable);

/* **********************************************************************
METHODE :		Affecte()
TRAITEMENT:		Affecte un équipement sur une liaison
***********************************************************************	*/
	BOOL	Affecte(int num,t_affecte affectation);

/* **********************************************************************
METHODE :		Modif_Affecte()
TRAITEMENT:		Modifie l'affectabilité d'une liaison
***********************************************************************	*/
	int Modif_Affecte(int ligne,BOOL affecte);


/* **********************************************************************
METHODE :		Change_Taille()
TRAITEMENT:		Change le nombre de messages des journaux
***********************************************************************	*/
	BOOL	Change_Taille(int taille);

/* **********************************************************************
METHODE :		MaxMessage()
TRAITEMENT:		Recupère la taille des journaux
***********************************************************************	*/
    int     MaxMessage() const;

/*************************************************************************
METHODE :		Modif_taille()
TRAITEMENT :	Modifie la taille des journaux
*************************************************************************/
	BOOL 	Modif_taille(int taille);

/* **********************************************************************
METHODE :		Top_externe()
TRAITEMENT:		Recupère la caracteristique externe du top synchro
***********************************************************************	*/
	void 	Top_synchro(int	*ext,int *dep,int *per) const;

/* **********************************************************************
METHODE :		Change_top_synchro()
TRAITEMENT:		Change les caractéristiques du Top Synchro
***********************************************************************	*/
	BOOL	Change_top_synchro(int	ext,int dep,int per);

/* **********************************************************************
METHODE :		Init_Environ()
TRAITEMENT:		Initialise un environnement
***********************************************************************	*/
	BOOL	Init_Environ();

/* **********************************************************************
METHODE :		Sauvegarder_Environ()
TRAITEMENT:		Sauvegarde l'environnement d'utilisation dans fichier
***********************************************************************	*/
	BOOL	Sauvegarder_Environ(char *fichier);

/* **********************************************************************
METHODE :		Charger_Environ()
TRAITEMENT:		Charger le fichier d'environnement (fichier)
***********************************************************************	*/
	BOOL	Charger_Environ(char *fichier);

/* **********************************************************************
METHODE :		Equipement()
TRAITEMENT:		Charger les caracteristiques d'une affectation
***********************************************************************	*/
	void	Equipement(int	index,t_affecte *ligne) const;

/* **********************************************************************
METHODE :		Modif_Equipement()
TRAITEMENT:		Modifie l'affection d'une liaison/Equipement
***********************************************************************	*/
	void Modif_Equipement(int index,t_affecte liaison);

/* **********************************************************************
METHODE :		Icone()
TRAITEMENT:		Renvoi l'icone associé à la idex_ieme position
***********************************************************************	*/
	CIcone	*Icone(int index);
};

#endif
