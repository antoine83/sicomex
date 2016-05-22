// EqpAAD.cpp: implementation of the CEquipAAD class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "stdafx.h"
#include <stdio.h>
#include <string.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\EqpAAD.h"
#include "Comm\p_AAD.h"
#include "DLGaad_20_4.h"
#include "DLGaad_20_8.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_AAD_20_4[];
extern char glob_CONTEXT_AAD_20_8[];

const int 	CR			= 0xD;	// Debut de trame
const int 	FIN_TRAME 	= 0x1A;	// Fin de trame

/* **************************************************************************
METHODE :		CEquipAAD(int idx, int dim)
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquipAAD::CEquipAAD(int idx, int dim):CEquip(idx)
{
	MATRICE_20_4[dim][NB_VOIES];
	TAB_ANTENNE[dim];
	TAB_PREAMPLI[dim];
	NB_ANTENNES  = dim;
	NB_PREAMPLIS = dim;
	// Initialise le type de matrice AAD 20x4
	if(dim == 4)
		NB_AMPLIS = 20;
	// Initialise le type de matrice AAD 20x8
	if(dim == 8)
		NB_AMPLIS	= 40;
	Initialiser();
}

/* **************************************************************************
METHODE :		~CEquipTemp
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquipAAD::~CEquipAAD()
{
}

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipAAD::Allocation()
{
	t_affecte ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL)
	{
		proto = new CProtoAAD(ligne.format,this);
	}

	// Allocation protocole matrice AAD 20x4
	if(NB_ANTENNES == 4)
	{
		if(ihm == NULL)
		{
			ihm = new CDLGaad_20_4;
			ihm->Associe(this);
			ihm->Create(IDD_AAD_20_4,glob_ihm);
			ihm->SetWindowText(ligne.repere);
			Afficher(ligne.controle);
			Charge_Contexte(glob_CONTEXT_AAD_20_4);
		}
	}
	// Allocation protocole matrice AAD 20x8
	if(NB_ANTENNES == 8)
	{
		if(ihm == NULL)
		{
			ihm = new CDLGaad_20_8;
			ihm->Associe(this);
			ihm->Create(IDD_AAD_20_8,glob_ihm);
			ihm->SetWindowText(ligne.repere);
			Afficher(ligne.controle);
			Charge_Contexte(glob_CONTEXT_AAD_20_8);
		}
	}
}

/* **************************************************************************
METHODE :		Charge_Contexte(char *fichier)
TRAITEMENT:		Initialise l'equipement a partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipAAD::Charge_Contexte(char *fichier)
{
	int  i,iResult, k;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];
	char cle[10];

	iResult = Recup_fichier(fichier, contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation", iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu, "P00=", ligne, TAILLE_MAX_LIGNE);
	if(strcmp(ligne+4, "AAD_20_4")!=0)
	{
		if(iResult < 0)
		{
			AjouterMessage("**** Erreur fichier non conforme à l'équipement", iResult);
			return FALSE;
		}
	}

	// Ligne 1 de la matrice
	iResult = Extrait_ligne(contenu, "P01=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for(k=0; k<NB_VOIES; k++)
		{
			if( ligne[4+k] == '1')
			{
				MATRICE_20_4[0][k] = true;
			}
			else
			{
				MATRICE_20_4[0][k] = false;
			}
		}
	}

	// Ligne 2 de la matrice
	iResult = Extrait_ligne(contenu, "P02=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for(k=0; k<NB_VOIES; k++)
		{
			if( ligne[4+k] == '1')
			{
				MATRICE_20_4[1][k] = true;
			}
			else
			{
				MATRICE_20_4[1][k] = false;
			}
		}
	}

	// Ligne 3 de la matrice
	iResult = Extrait_ligne(contenu, "P03=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for(k=0; k<NB_VOIES; k++)
		{
			if( ligne[4+k] == '1')
			{
				MATRICE_20_4[2][k] = true;
			}
			else
			{
				MATRICE_20_4[2][k] = false;
			}
		}
	}

	// Ligne 4 de la matrice
	iResult = Extrait_ligne(contenu, "P04=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for(k=0; k<NB_VOIES; k++)
		{
			if( ligne[4+k] == '1')
			{
				MATRICE_20_4[3][k] = true;
			}
			else
			{
				MATRICE_20_4[3][k] = false;
			}
		}
	}

	// Lignes supplementaires pour la matrice AAD 20x8
	if(NB_ANTENNES == 8)
	{
		// ligne 5 de la matrice
		iResult = Extrait_ligne(contenu, "P05=", ligne, TAILLE_MAX_LIGNE);
		if(iResult >= 0)
		{
			for(k=0; k<NB_VOIES; k++)
			{
				if( ligne[4+k] == '1')
				{
					MATRICE_20_4[4][k] = true;
				}
				else
				{
					MATRICE_20_4[4][k] = false;
				}
			}
		}

		// Ligne 6 de la matrice
		iResult = Extrait_ligne(contenu, "P06=", ligne, TAILLE_MAX_LIGNE);
		if(iResult >= 0)
		{
			for(k=0; k<NB_VOIES; k++)
			{
				if( ligne[4+k] == '1')
				{
					MATRICE_20_4[5][k] = true;
				}
				else
				{
					MATRICE_20_4[5][k] = false;
				}
			}
		}

		// Ligne 7 de la matrice
		iResult = Extrait_ligne(contenu, "P07=", ligne, TAILLE_MAX_LIGNE);
		if(iResult >= 0)
		{
			for(k=0; k<NB_VOIES; k++)
			{
				if( ligne[4+k] == '1')
				{
					MATRICE_20_4[6][k] = true;
				}
				else
				{
					MATRICE_20_4[6][k] = false;
				}
			}
		}

		// Ligne 8 de la matrice
		iResult = Extrait_ligne(contenu, "P08=", ligne, TAILLE_MAX_LIGNE);
		if(iResult >= 0)
		{
			for(k=0; k<NB_VOIES; k++)
			{
				if( ligne[4+k] == '1')
				{
					MATRICE_20_4[7][k] = true;
				}
				else
				{
					MATRICE_20_4[7][k] = false;
				}
			}
		}
	}

	// Tableau des antennes
	if(NB_ANTENNES == 4)
	{
		iResult = Extrait_ligne(contenu, "P05=", ligne, TAILLE_MAX_LIGNE);
	}
	if(NB_ANTENNES == 8)
	{
		iResult = Extrait_ligne(contenu, "P09=", ligne, TAILLE_MAX_LIGNE);
	}
	if(iResult >= 0)
	{
		for(k=0; k<NB_ANTENNES; k++)
		{
			switch (ligne[4+k])
			{
			case '0':
				TAB_ANTENNE[k] = ABSENT0;
				break;
			case '1':
				TAB_ANTENNE[k] = CORRECT0;
				break;
			case '2':
				TAB_ANTENNE[k] = ALIM_HS0;
				break;
			case '3':
				TAB_ANTENNE[k] = SURCHAUFFE0;
				break;
			default:
				break;
			}
		}
	}

	// Tableau des preamplis
	if(NB_ANTENNES == 4)
	{
		iResult = Extrait_ligne(contenu, "P06=", ligne, TAILLE_MAX_LIGNE);
	}
	if(NB_ANTENNES == 8)
	{
		iResult = Extrait_ligne(contenu, "P11=", ligne, TAILLE_MAX_LIGNE);
	}
	if(iResult >= 0)
	{
		for(k=0; k<NB_PREAMPLIS; k++)
		{
			switch (ligne[4+k])
			{
			case '0':
				TAB_PREAMPLI[k] = ABSENT1;
				break;
			case '1':
				TAB_PREAMPLI[k] = CORRECT1;
				break;
			case '2':
				TAB_PREAMPLI[k] = DEFAUT1;
				break;
			default:
				break;
			}
		}
	}

	// Tableau des amplis
	if(NB_ANTENNES == 4)
	{
		iResult = Extrait_ligne(contenu, "P07=", ligne, TAILLE_MAX_LIGNE);
	}
	if(NB_ANTENNES == 8)
	{
		iResult = Extrait_ligne(contenu, "P11=", ligne, TAILLE_MAX_LIGNE);
	}
	if(iResult >= 0)
	{
		for(k=0; k<NB_AMPLIS; k++)
		{
			switch (ligne[4+k])
			{
			case '0':
				TAB_AMPLI[k] = ABSENT1;
				break;
			case '1':
				TAB_AMPLI[k] = CORRECT1;
				break;
			case '2':
				TAB_AMPLI[k] = DEFAUT1;
				break;
			default:
				break;
			}
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
BOOL CEquipAAD::Sauve_Contexte(char *fichier)
{
	int  i, iResult, j, k;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];

	// En tete fichier de la matrice AAD 20x4
	if(NB_ANTENNES == 4)
	{
		strcpy(contenu, "// Contexte d'exploitation d'une matrice ADD20x4\r\n");
		strcat(contenu, "// *********************************************\r\n");
		strcpy(ligne, "P00=AAD_20_4\r\n");
		strcat(contenu, ligne);
	}

	// En tete fichier de la matrice AAD 20x8
	if(NB_ANTENNES == 8)
	{
		strcpy(contenu, "// Contexte d'exploitation d'une matrice ADD20x8\r\n");
		strcat(contenu, "// *********************************************\r\n");
		strcpy(ligne, "P00=AAD_20_8\r\n");
		strcat(contenu, ligne);
	}

	// Lignes de la matrice
	for(j=0; j<NB_ANTENNES; j++)
	{
		sprintf(ligne, "P0%d=", j+1);
		strcat(contenu, ligne);
		for(k=0; k<NB_VOIES; k++)
		{
			if(MATRICE_20_4[j][k] == true)
			{
				sprintf(ligne, "1");
			}
			else
			{
				sprintf(ligne, "0");
			}
			strcat(contenu, ligne);
		}
		sprintf(ligne, "\r\n");
		strcat(contenu, ligne);
	}


	// Tableau des antennes
	if(NB_ANTENNES == 4)
	{
		sprintf(ligne, "P05=");
	}
	if(NB_ANTENNES == 8)
	{
		sprintf(ligne, "P09=");
	}
	strcat(contenu, ligne);
	for(j=0; j<NB_ANTENNES; j++)
	{
		sprintf(ligne,"%d", TAB_ANTENNE[j]);
		strcat(contenu, ligne);
	}
	sprintf(ligne, "\r\n");
	strcat(contenu, ligne);

	// Tableau des preamplis
	if(NB_ANTENNES == 4)
	{
		sprintf(ligne, "P06=");
	}
	if(NB_ANTENNES == 8)
	{
		sprintf(ligne, "P10=");
	}
	strcat(contenu, ligne);
	for(j=0; j<NB_PREAMPLIS; j++)
	{
		sprintf(ligne,"%d", TAB_PREAMPLI[j]);
		strcat(contenu, ligne);
	}
	sprintf(ligne, "\r\n");
	strcat(contenu, ligne);

	// Tableau des amplis
	if(NB_ANTENNES == 4)
	{
		sprintf(ligne, "P07=");
	}
	if(NB_ANTENNES == 8)
	{
		sprintf(ligne, "P11=");
	}
	strcat(contenu, ligne);
	for(j=0; j<NB_AMPLIS; j++)
	{
		sprintf(ligne,"%d", TAB_AMPLI[j]);
		strcat(contenu, ligne);
	}
	sprintf(ligne, "\r\n");
	strcat(contenu, ligne);

	iResult = Stocker_fichier(fichier, contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation", iResult);
		return FALSE;
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
BOOL CEquipAAD::Power()
{
	BOOL    activite;
	CEquip::Power();

	activite = Actif();
	if(activite)
	{
		// TODO : integrer ici le protocole de mise en route de l'equipement
	}
	else
	{
		// TODO : integrer ici le protocole d'arret de l'equipement
	}
	return activite;
}

/* **************************************************************************
METHODE :		Initialiser()
TRAITEMENT:		Initialiser l'environnement
***************************************************************************	*/
void CEquipAAD::Initialiser()
{
	InitialiserMatrice();
	InitialiserAntenne();
	InitialiserPreampli();
	InitialiserAmpli();
}

/* **************************************************************************
METHODE :		Initialiser()
TRAITEMENT:		Initialiser la matrice
***************************************************************************	*/
void CEquipAAD::InitialiserMatrice()
{
	int i, j;

	// Allocation de la memoire
	MATRICE_20_4 = new bool * [NB_ANTENNES];
	MATRICE_20_4[0] = new bool[NB_ANTENNES*NB_VOIES];

	for(i=0; i<NB_ANTENNES;i++)
	{
        MATRICE_20_4[i] = &MATRICE_20_4[0][NB_VOIES*i];
	}

	// Initialisation matrice
	for(j=0; j<NB_VOIES; j++)
	{
		MATRICE_20_4[0][j] = true;
	}

	for(i=1; i<NB_ANTENNES; i++)
	{
		for(j=0; j<NB_VOIES; j++)
		{
			MATRICE_20_4[i][j] = false;
		}
	}
}

/* **************************************************************************
METHODE :		Initialiser()
TRAITEMENT:		Initialiser la matrice
***************************************************************************	*/
void CEquipAAD::ResetMatrice()
{
	int i, j;

	// Initialisation matrice
	EnterCriticalSection(&crit);
		for(j=0; j<NB_VOIES; j++)
		{
			MATRICE_20_4[0][j] = true;
		}

		for(i=1; i<NB_ANTENNES; i++)
		{
			for(j=0; j<NB_VOIES; j++)
			{
				MATRICE_20_4[i][j] = false;
			}
		}
		evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		ValiderMatrice()
TRAITEMENT:		Valide la matrice
***************************************************************************	*/
BOOL CEquipAAD::ValiderMatrice()
{
	int	 i, j;
	bool btemp;

	for(i=0; i<NB_VOIES; i++)
	{
		btemp = 0;
		for(j=0; j<NB_ANTENNES; j++)
		{
			if(MATRICE_20_4[j][i] == true)
			{
				if(btemp == true)
				{
					return FALSE;
				}
				else
				{
					btemp = true;
				}
			}
		}
	}

	return TRUE;
}

/* **************************************************************************
METHODE :		ChgtEtatMatrice(int idxAntenne, int idxVoie)
TRAITEMENT:		Connecte sur la matrice la connexion recue par TC
***************************************************************************	*/
bool CEquipAAD::ChgtEtatMatrice(int idxAntenne, int idxVoie)
{
	if(idxAntenne>=NB_ANTENNES)
		return false;
	if(idxVoie>=NB_VOIES)
		return false;
	for(int i=0; i<NB_ANTENNES; i++)
	{
		if(MATRICE_20_4[i][idxVoie] == true)
		{
			EnterCriticalSection(&crit);
				MATRICE_20_4[i][idxVoie] = false;
				MATRICE_20_4[idxAntenne][idxVoie] = true;
				evolution = (evolution+1) % PLAGE_EVOLUTION;
			LeaveCriticalSection(&crit);
			break;
		}
	}
	return true;
}

/* **************************************************************************
METHODE :		InitialiserAntenne()
TRAITEMENT:		Initialise l'etat des antennes a CORRECT0
***************************************************************************	*/
void CEquipAAD::InitialiserAntenne()
{
	// Allocation de la memoire
	TAB_ANTENNE = new EtatAntenne[NB_ANTENNES];

	// Initialisation du tableau d'antennes
	for(int i=0; i<NB_ANTENNES; i++)
	{
		TAB_ANTENNE[i] = CORRECT0;
	}
}

/* **************************************************************************
METHODE :		ChgtEtatAntenne(int no_antenne, int statut)
TRAITEMENT:		Change l'etat d'une antenne
***************************************************************************	*/
void CEquipAAD::ChgtEtatAntenne(int no_antenne, int statut)
{
	EnterCriticalSection(&crit);
		switch (statut)
		{
		case 0:
			TAB_ANTENNE[no_antenne] = ABSENT0;
			break;
		case 1:
			TAB_ANTENNE[no_antenne] = CORRECT0;
			break;
		case 2:
			TAB_ANTENNE[no_antenne] = ALIM_HS0;
			break;
		case 3:
			TAB_ANTENNE[no_antenne] = SURCHAUFFE0;
			break;
		default:
			break;
		}
	LeaveCriticalSection(&crit);
}


/* **************************************************************************
METHODE :		InitialiserPreampli()
TRAITEMENT:		Initialise l'etat des preamplis a CORRECT1
***************************************************************************	*/
void CEquipAAD::InitialiserPreampli()
{
	// Allocation de la memoire
	TAB_PREAMPLI = new EtatAmpli[NB_PREAMPLIS];

	// Initialisation du tableau d'antennes
	for(int i=0; i<NB_PREAMPLIS; i++)
	{
		TAB_PREAMPLI[i] = CORRECT1;
	}
}

/* **************************************************************************
METHODE :		ChgtEtatPreampli(int no_preampli, int statut)
TRAITEMENT:		Change l'etat d'un preampli
***************************************************************************	*/
void CEquipAAD::ChgtEtatPreampli(int no_preampli, int statut)
{
	EnterCriticalSection(&crit);
		switch (statut)
		{
		case 0:
			TAB_PREAMPLI[no_preampli] = ABSENT1;
			break;
		case 1:
			TAB_PREAMPLI[no_preampli] = CORRECT1;
			break;
		case 2:
			TAB_PREAMPLI[no_preampli] = DEFAUT1;
			break;
		default:
			// TODO : Erreur de trame TC
			break;
		}
	LeaveCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		InitialiserAmpli()
TRAITEMENT:		Initialise l'etat des amplis a CORRECT1
***************************************************************************	*/
void CEquipAAD::InitialiserAmpli()
{
	// Allocation de la memoire
	TAB_AMPLI = new EtatAmpli[NB_AMPLIS];

	// Initialisation du tableau d'amplificateurs
	for(int i=0; i<NB_AMPLIS; i++)
	{
		TAB_AMPLI[i] = CORRECT1;
	}
}

/* **************************************************************************
METHODE :		ChgtEtatAmpli(int no_ampli, int statut)
TRAITEMENT:		Change l'etat d'un ampli
***************************************************************************	*/
void CEquipAAD::ChgtEtatAmpli(int no_ampli, int statut)
{
	EnterCriticalSection(&crit);
		switch (statut)
		{
		case 0:
			TAB_AMPLI[no_ampli] = ABSENT1;
			break;
		case 1:
			TAB_AMPLI[no_ampli] = CORRECT1;
			break;
		case 2:
			TAB_AMPLI[no_ampli] = DEFAUT1;
			break;
		default:
			// TODO : Erreur de trame TC
			break;
		}
	LeaveCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		EtatMateriel()
TRAITEMENT:		Interroge l'etat general du materiel
***************************************************************************	*/
void CEquipAAD::EtatMateriel()
{
	int  i, iResult;
	char reponse[400];
	char buffer[20];

	//EnterCriticalSection(&crit);
	memset(reponse, 0, sizeof(reponse));

	// Etat general des antennes
	for(i=0; i<NB_ANTENNES; i++)
	{
		sprintf(buffer, "A%d,Z%d%c", (i+1), TAB_ANTENNE[i], CR);
		strcat(reponse, buffer);
	}

	// Etat general des preamplis
	for(i=0; i<NB_PREAMPLIS; i++)
	{
		sprintf(buffer, "V%d,Z%d%c", (i+1), TAB_PREAMPLI[i], CR);
		strcat(reponse, buffer);
	}

	// Etat general des amplis
	for(i=0; i<=NB_AMPLIS-1; i++)
	{
		sprintf(buffer, "K%d,Z%d%c", (i+1), TAB_AMPLI[i], CR);
		strcat(reponse, buffer);
	}

	iResult = proto->EnvoyerTS(reponse);

	if(iResult < 0)
	{
		EnterCriticalSection(&crit);
		printf("Toto\n");
		LeaveCriticalSection(&crit);
	}
	//LeaveCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		EtatMatrice()
TRAITEMENT:		Interroge l'etat general de la matrice
***************************************************************************	*/
void CEquipAAD::EtatMatrice()
{
	int  i, j;
	char reponse[150];
	char buffer[10];

	strcpy(reponse,"");
	strcpy(buffer, "");

	// Etat general de la matrice
	for(i=0; i<NB_VOIES; i++)
	{
		for(j=0; j<NB_ANTENNES; j++)
		{
			if(MATRICE_20_4[j][i] == true)
			{
				sprintf(buffer, "A%d,E%d%c", (j+1), (i+1), CR);
				strcat(reponse, buffer);
			}
		}
	}
	proto->EnvoyerTS(reponse);
}
