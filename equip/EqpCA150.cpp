// EqpCA150.cpp: implementation of the CEquipCA150 class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\EqpCA150.h"
#include "Comm\p_CA150.h"
#include "DLGCA150.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_CA150_MASTER[];
extern char glob_CONTEXT_CA150_SLAVE[];

/* **************************************************************************
METHODE :		CEquipCA150(int idx, TypeCA type)
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquipCA150::CEquipCA150(int idx, TypeCA type):CEquip(idx)
{
	TYPE				= type;
	InitialiserSH();
	TIMER				= true;
	DEFAUT				= false;
	MAUVAIS_ROS			= false;
	LOCAL				= false;
	PUISSANCE_INCIDENTE	= 0;
	PUISSANCE_REFLECHIE	= 0;
	if(type == MASTER)
	{
		COMBINE			= false;
		InitialiserCharge();
	}
	if(type == SLAVE)
	{
		InitialiserCharge();
	}
}

/* **************************************************************************
METHODE :		~CEquipCA150
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquipCA150::~CEquipCA150()
{
	free(CHARGE);
}

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipCA150::Allocation()
{
	t_affecte ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL)
	{
		proto = new CProtoCA150(ligne.format,this);
	}

	// Allocation protocole des CA150
	if(ihm == NULL)
	{
		ihm = new CDLGCA150;
		ihm->Associe(this);
		ihm->Create(IDD_CA_150,glob_ihm);
		ihm->SetWindowText(ligne.repere);
		Afficher(ligne.controle);
		if(TYPE == MASTER)
		{
			Charge_Contexte(glob_CONTEXT_CA150_MASTER);
		}
		if(TYPE == SLAVE)
		{
			Charge_Contexte(glob_CONTEXT_CA150_SLAVE);
		}
	}
}

/* **************************************************************************
METHODE :		Charge_Contexte(char *fichier)
TRAITEMENT:		Initialise l'equipement a partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipCA150::Charge_Contexte(char *fichier)
{
	int  i, iResult, k;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];
	char cle[10], cTemp[4];

	iResult = Recup_fichier(fichier, contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation", 0);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu, "P00=", ligne, TAILLE_MAX_LIGNE);
	if( (strcmp(ligne+4, "CA150 MASTER")!=0) || (strcmp(ligne+4, "CA150 SLAVE")!=0) )
	{
		if(iResult < 0)
		{
			AjouterMessage("**** Erreur fichier non conforme à l'équipement", iResult);
			return FALSE;
		}
	}

	// TYPE
	if(strcmp(ligne+4, "CA150 MASTER") == 0)
		TYPE = MASTER;

	if(strcmp(ligne+4, "CA150 SLAVE") == 0)
		TYPE = SLAVE;

	// TIMER
	iResult = Extrait_ligne(contenu, "P01=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		if( ligne[4] == '1')
			TIMER = true;
		else
			TIMER = false;
	}

	// SURCHAUFFE_HYBRIDE
	iResult = Extrait_ligne(contenu, "P02=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for(k=0; k<4; k++)
		{
			if( ligne[4+k] == '1')
				SURCHAUFFE_HYBRIDE[k] = true;
			else
				SURCHAUFFE_HYBRIDE[k] = false;
		}
	}

	// DEFAUT
	iResult = Extrait_ligne(contenu, "P03=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		if( ligne[4] == '1')
			DEFAUT = true;
		else
			DEFAUT = false;
	}

	// MAUVAIS_ROS
	iResult = Extrait_ligne(contenu, "P04=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		if( ligne[4] == '1')
			MAUVAIS_ROS = true;
		else
			MAUVAIS_ROS = false;
	}

	// LOCAL
	iResult = Extrait_ligne(contenu, "P05=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		if( ligne[4] == '1')
			LOCAL = true;
		else
			LOCAL = false;
	}

	// PUISSANCE_INCIDENTE
	iResult = Extrait_ligne(contenu, "P06=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		sprintf(cTemp, "%s", ligne+4);
		PUISSANCE_INCIDENTE = atoi(cTemp);
	}

	// PUISSANCE_REFLECHIE
	iResult = Extrait_ligne(contenu, "P07=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		sprintf(cTemp, "%s", ligne+4);
		PUISSANCE_REFLECHIE = atoi(cTemp);
	}

	// CHARGE HF1 a HF4
	iResult = Extrait_ligne(contenu, "P08=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for(k=0; k<4; k++)
		{
			if( ligne[4+k] == '1')
				CHARGE[k] = true;
			else
				CHARGE[k] = false;
		}
	}

	// Reste de la difference MASTER / SLAVE
	iResult = Extrait_ligne(contenu, "P09=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		if(TYPE == MASTER)
		{
			if( ligne[4] == '1')
				CHARGE[5] = true;
			else
				CHARGE[5] = false;
			if( ligne[4+1] == '1')
				COMBINE = true;
			else
				COMBINE = false;
		}
		if(TYPE == SLAVE)
		{
			if( ligne[4] == '1')
				CHARGE[5] = true;
			else
				CHARGE[5] = false;
			if( ligne[4+1] == '1')
				CHARGE[6] = true;
			else
				CHARGE[6] = false;
		}
	}

	while(RetirerSequence(0));
	i=50;
	while(i<100)
	{
		sprintf(cle,"P%2.2d=",i);
		iResult = Extrait_ligne(contenu,cle,ligne,TAILLE_MAX_LIGNE);
		if(iResult<0) break;

		AjouterSequence(atoi(ligne+4));
		i++;
	}

	return TRUE;
}

/* **************************************************************************
METHODE :		Sauve_Contexte(char *fichier)
TRAITEMENT:		Sauveagrde le contexte d'exploitation d'un fichier
***************************************************************************	*/
BOOL CEquipCA150::Sauve_Contexte(char *fichier)
{
	int  i, iResult;
	int  sh1, sh2, sh3, sh4;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];

	// En tete fichier de la matrice SPIN
	if(TYPE == MASTER)
	{
		strcpy(contenu, "// Contexte d'exploitation d'un multicoupleur CA150\r\n");
		strcat(contenu, "// ************************************************\r\n");
		strcpy(ligne, "P00=CA150 MASTER\r\n");
		strcat(contenu, ligne);
	}

	// En tete fichier de la matrice L11
	if(TYPE == SLAVE)
	{
		strcpy(contenu, "// Contexte d'exploitation d'un multicoupleur CA150\r\n");
		strcat(contenu, "// ************************************************\r\n");
		strcpy(ligne, "P00=CA150 SLAVE\r\n");
		strcat(contenu, ligne);
	}

	// TIMER
	if(TIMER)
	{
		sprintf(ligne, "P01=%d", 1);
		strcat(contenu, ligne);
	}
	else
	{
		sprintf(ligne, "P01=%d", 0);
		strcat(contenu, ligne);
	}
	sprintf(ligne, "\r\n");
	strcat(contenu, ligne);


	// SURCHAUFFE_HYBRIDE
	if(SURCHAUFFE_HYBRIDE[0])
		sh1 = 1;
	else
		sh1 = 0;
	if(SURCHAUFFE_HYBRIDE[1])
		sh2 = 1;
	else
		sh2 = 0;
	if(SURCHAUFFE_HYBRIDE[2])
		sh3 = 1;
	else
		sh3 = 0;
	if(SURCHAUFFE_HYBRIDE[3])
		sh4 = 1;
	else
		sh4 = 0;
	sprintf(ligne, "P02=%d%d%d%d", sh1, sh2, sh3, sh4);
	strcat(contenu, ligne);
	sprintf(ligne, "\r\n");
	strcat(contenu, ligne);

	// DEFAUT
	if(DEFAUT)
	{
		sprintf(ligne, "P03=%d", 1);
		strcat(contenu, ligne);
	}
	else
	{
		sprintf(ligne, "P03=%d", 0);
		strcat(contenu, ligne);
	}
	sprintf(ligne, "\r\n");
	strcat(contenu, ligne);

	// MAUVAIS_ROS
	if(MAUVAIS_ROS)
	{
		sprintf(ligne, "P04=%d", 1);
		strcat(contenu, ligne);
	}
	else
	{
		sprintf(ligne, "P04=%d", 0);
		strcat(contenu, ligne);
	}
	sprintf(ligne, "\r\n");
	strcat(contenu, ligne);

	// LOCAL
	if(LOCAL)
	{
		sprintf(ligne, "P05=%d", 1);
		strcat(contenu, ligne);
	}
	else
	{
		sprintf(ligne, "P05=%d", 0);
		strcat(contenu, ligne);
	}
	sprintf(ligne, "\r\n");
	strcat(contenu, ligne);

	// PUISSANCE_INCIDENTE
	sprintf(ligne, "P06=%d", PUISSANCE_INCIDENTE);
	strcat(contenu, ligne);
	sprintf(ligne, "\r\n");
	strcat(contenu, ligne);

	// PUISSANCE_REFLECHIE
	sprintf(ligne, "P07=%d", PUISSANCE_REFLECHIE);
	strcat(contenu, ligne);
	sprintf(ligne, "\r\n");
	strcat(contenu, ligne);

	// CHARGE HF1 a HF4
	if(CHARGE[1])
		sh1 = 1;
	else
		sh1 = 0;
	if(CHARGE[2])
		sh2 = 1;
	else
		sh2 = 0;
	if(CHARGE[3])
		sh3 = 1;
	else
		sh3 = 0;
	if(CHARGE[4])
		sh4 = 1;
	else
		sh4 = 0;
	sprintf(ligne, "P08=%d%d%d%d", sh1, sh2, sh3, sh4);
	strcat(contenu, ligne);
	sprintf(ligne, "\r\n");
	strcat(contenu, ligne);

	// Reste de la difference MASTER / SLAVE
	if(TYPE == MASTER)
	{
		if(CHARGE[5])
			sh1 = 1;
		else
			sh1 = 0;
		if(COMBINE)
			sh2 = 1;
		else
			sh2 = 0;
		sprintf(ligne, "P09=%d%d", sh1, sh2);
		strcat(contenu, ligne);
		sprintf(ligne, "\r\n");
		strcat(contenu, ligne);
	}
	if(TYPE == SLAVE)
	{
		if(CHARGE[5])
			sh1 = 1;
		else
			sh1 = 0;
		if(CHARGE[6])
			sh2 = 1;
		else
			sh2 = 0;
		sprintf(ligne, "P09=%d%d", sh1, sh2);
		strcat(contenu, ligne);
		sprintf(ligne, "\r\n");
		strcat(contenu, ligne);
	}

	i=50;
	while(i<100)
	{
		iResult = seq->LireSequence(i-50);
		if(iResult != ERR_AUCUN_ELEMENT)
		{
			sprintf(ligne,"P%2.2d=%d\r\n",i,iResult);
			strcat(contenu,ligne);
		}
		i++;
	}

	iResult = Stocker_fichier(fichier,contenu);
	free(ligne);
	free(contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation",iResult);
		return FALSE;
	}

	return TRUE;
}

/* **************************************************************************
METHODE :		Power()
TRAITEMENT:		Mise en route de l'équipement
***************************************************************************	*/
BOOL CEquipCA150::Power()
{
	BOOL    activite;
	CEquip::Power();

	activite = Actif();
	if(activite)
	{
		proto->AjouterTS(NULL, DEMANDE_ETAT);
	}
	else
	{
		// TODO : integrer ici le protocole d'arret de l'equipement
	}
	return activite;
}

/* **************************************************************************
METHODE :		InitialiserSH
TRAITEMENT:		Initialise le tableau de surchauffe hybride a false
***************************************************************************	*/
void CEquipCA150::InitialiserSH()
{
	int i;

	for(i=0; i<4; i++)
		SURCHAUFFE_HYBRIDE[i] = false;
}

/* **************************************************************************
METHODE :		InitialiserCharge(int taille)
TRAITEMENT:		Initialise les charges suivant le type de CA150
***************************************************************************	*/
void CEquipCA150::InitialiserCharge()
{
	int i, taille;

	if(TYPE == MASTER)
		taille = 6;
	else
		taille = 7;

	// Allocation de la memoire
	CHARGE = new bool[taille];

	// Initialisation des charges
	for(i=0; i<taille; i++)
		CHARGE[i] = false;
}

/* **************************************************************************
METHODE :		ChgtEtatSH(int idx, bool etat)
TRAITEMENT:		Change l'etat de la surchauffe hybride
***************************************************************************	*/
void CEquipCA150::ChgtEtatSH(int idx, bool etat)
{
	if(SURCHAUFFE_HYBRIDE[idx] == etat)
	{
		// TODO : retourner un message d'erreur : etat deja existant
	}
	else
	{
		SURCHAUFFE_HYBRIDE[idx] = etat;
	}
	EnterCriticalSection(&crit);
		evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		ChgtEtatCharge(int idx, bool etat)
TRAITEMENT:		Change l'etat de la charge
***************************************************************************	*/
void CEquipCA150::ChgtEtatCharge(int idx, bool etat)
{
	if(TYPE == MASTER)
	{
		EnterCriticalSection(&crit);
			CHARGE[1] = false;
			CHARGE[2] = false;
			CHARGE[3] = false;
			CHARGE[4] = false;
			CHARGE[5] = false;
			if(etat == false)
				CHARGE[0] = true;
			else
				CHARGE[idx] = etat;
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
	}

	if(TYPE == SLAVE)
	{
		EnterCriticalSection(&crit);
			CHARGE[1] = false;
			CHARGE[2] = false;
			CHARGE[3] = false;
			CHARGE[4] = false;
			CHARGE[5] = false;
			CHARGE[6] = false;
			if(etat == false)
				CHARGE[0] = true;
			else
				CHARGE[idx] = etat;
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
	}
}

/* **************************************************************************
METHODE :		DemandeEtat()
TRAITEMENT:		Demande l'etat general du multicoupleur
***************************************************************************	*/
void CEquipCA150::EnvoiEtatCyclique()
{
	proto->AjouterTS(NULL,DEMANDE_ETAT);
}

/* **************************************************************************
METHODE :		DemandeEtat()
TRAITEMENT:		Demande l'etat general du multicoupleur
***************************************************************************	*/
char* CEquipCA150::DemandeEtat()
{
	//int  i;							//2009-11-27
	char cMasque[2];
	char * reponse = (char *)malloc (sizeof (char) * 10);

	strcpy(reponse, "");

	// Octet 1
	cMasque[0] = 48; // 0x30
	if(!SURCHAUFFE_HYBRIDE[0]) cMasque[0] = cMasque[0] + 1;
	if(!SURCHAUFFE_HYBRIDE[1]) cMasque[0] = cMasque[0] + 2;
	if(!SURCHAUFFE_HYBRIDE[2]) cMasque[0] = cMasque[0] + 4;
	if(!SURCHAUFFE_HYBRIDE[3]) cMasque[0] = cMasque[0] + 8;
	//strcat(reponse, cMasque);
	reponse[0] = cMasque[0];

	// Octet 2
	cMasque[0] = 48; //0x30
	if(!CHARGE[1]) cMasque[0] = cMasque[0] + 1;
	if(!CHARGE[2]) cMasque[0] = cMasque[0] + 2;
	if(!CHARGE[3]) cMasque[0] = cMasque[0] + 4;
	if(!CHARGE[4]) cMasque[0] = cMasque[0] + 8;
	//strcat(reponse, cMasque);
	reponse[1] = cMasque[0];

	// Octet 3
	cMasque[0] = 54; //0x36
	if(TYPE == SLAVE)
	{
		if(!CHARGE[5]) cMasque[0] = cMasque[0] + 1;
		if(!CHARGE[6]) cMasque[0] = cMasque[0] + 8;
	}
	if(TYPE == MASTER)
	{
		cMasque[0] = cMasque[0] + 1;
		if(!CHARGE[5]) cMasque[0] = cMasque[0] + 8;
	}
	//strcat(reponse, cMasque);
	reponse[2] = cMasque[0];

	// Octet 4
	// cMasque[0] = 56; //0x38
	cMasque[0] = 48; //0x30
	if(!DEFAUT)			cMasque[0] = cMasque[0] + 1 ;
	if(!MAUVAIS_ROS)	cMasque[0] = cMasque[0] + 2;
	if(!LOCAL)			cMasque[0] = cMasque[0] + 4;
	//strcat(reponse, cMasque);
	reponse[3] = cMasque[0];

	// Octet 5
	cMasque[0] = 48; //0x30
	cMasque[0] = cMasque[0] + (PUISSANCE_INCIDENTE%16);
	reponse[4] = cMasque[0];

	// Octet 6
	cMasque[0] = 48; //0x30
	cMasque[0] = cMasque[0] + (PUISSANCE_INCIDENTE/16);
	reponse[5] = cMasque[0];

	// Octet 7
	cMasque[0] = 48; //0x30
	cMasque[0] = cMasque[0] + (PUISSANCE_REFLECHIE%16);
	reponse[6] = cMasque[0];

	// Octet 8
	cMasque[0] = 48; //0x30
	cMasque[0] = cMasque[0] + (PUISSANCE_REFLECHIE/16);
	reponse[7] = cMasque[0];

	// Octet 9
	cMasque[0] = 48; //0x30
	if(TYPE == MASTER)
	{
		if(!COMBINE) cMasque[0] = cMasque[0] + 8;
	}
	reponse[8] = cMasque[0];


	reponse[9] = 0;

	return reponse;
}

/* **************************************************************************
METHODE :		ChgtCombineMaster(bool etat)
TRAITEMENT:		Change l'etat du couplage MASTER/slave
***************************************************************************	*/
void CEquipCA150::ChgtCombineMaster(bool etat)
{
	if(TYPE == MASTER)
	{
		if(COMBINE == etat)
		{
			// TODO : envoyer un message d'erreur deja existant
		}
		else
		{
			EnterCriticalSection(&crit);
				COMBINE = etat;
				evolution = (evolution+1) % PLAGE_EVOLUTION;
			LeaveCriticalSection(&crit);
		}
	}
}
