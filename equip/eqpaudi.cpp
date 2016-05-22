/* **************************************************************************
FICHIER :	Eqp_Audi.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquipAudio
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\EqpAudi.h"
#include "Comm\prot_Aud.h"
#include "DlgAudio.h"

#include "Divers\div_fic.h"
#include <string.h>

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_AUDIO[];
/* **************************************************************************
METHODE :		CEquipAudio()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquipAudio::CEquipAudio(int idx):CEquip(idx)
{
	int		i,j;

	for(i=0 ; i<MAX_CARTE ; i++)
		for(j=0 ; j<MAX_RELAIS ; j++)
			relais[i][j]=0;

	test 		= 0;
	lock 		= 0;
}

/* **************************************************************************
METHODE :		~CEquipAudio
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquipAudio::~CEquipAudio()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipAudio::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProtoAudio(ligne.format,this);

	if(ihm == NULL) ihm = new CDlgAudio;
	ihm->Associe(this);
	ihm->Create(F4_IDD_STANDARD_AUDIO,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_AUDIO);
}

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipAudio::Charge_Contexte(char *fichier)
{
	int 	iResult;
	int		i,j;

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];
	char	cle[10];

	iResult = Recup_fichier(fichier,contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation",iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P00=",ligne,TAILLE_MAX_LIGNE);
	if(strcmp(ligne+4,"AUDIO")!=0)
	if(iResult<0)
	{
		AjouterMessage("**** Erreur fichier non conforme à l'équipement",iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P01=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeTest(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P02=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeLock(atoi(ligne+4),FALSE);

	for(i=0 ; i<MAX_CARTE ; i++)
		for(j=0 ; j<MAX_RELAIS ; j++)
		{
			sprintf(cle,"P%2.2d,%2.2d=",i,j);
			iResult = Extrait_ligne(contenu,cle,ligne,TAILLE_MAX_LIGNE);
			if(iResult>=0)	ChangeEtatRelais(i,j,atoi(ligne+7),FALSE);
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
METHODE :		Sauve_Contexte()
TRAITEMENT:		Sauveagrde le contexte d'exploitation d'un fichier
***************************************************************************	*/
BOOL CEquipAudio::Sauve_Contexte(char *fichier)
{
	int 	iResult;
	int		i,j;

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];

	strcpy(contenu,"// Contexte d'exploitation du standard audio\r\n");
	strcat(contenu,"// *****************************************\r\n");

	strcpy(ligne,"P00=AUDIO\r\n");
	strcat(contenu,ligne);

	sprintf(ligne,"P01=%d\r\n",Test());
	strcat(contenu,ligne);

	sprintf(ligne,"P02=%d\r\n",Lock());
	strcat(contenu,ligne);

	for(i=0 ; i<MAX_CARTE ; i++)
		for(j=0 ; j<MAX_RELAIS ; j++)
		{
			sprintf(ligne,"P%2.2d,%2.2d=%d\r\n",i,j,EtatRelais(i,j));
			strcat(contenu,ligne);
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
METHODE :		Power
TRAITEMENT:		Mise en route de l'équipement
***************************************************************************	*/
BOOL CEquipAudio::Power()
{
	BOOL	activite;
	CEquip::Power();

	activite = Actif();
	if(activite)
	{
//		proto->AjouterTS("Initialisation",CDE_TEXTE_SEUL);
	}
	else
	{
//		proto->AjouterTS("Arret de l'équipement",CDE_TEXTE_SEUL);
	}
	return activite;

}
// Test ******************************************
int CEquipAudio::Test() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = test;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAudio::ChangeTest(int valeur,BOOL genere_TS)
{
	int 	iResult = 0;

	if(valeur>=0) 		iResult = 0;
	if(valeur>=4100)	iResult = 4100;
	if(valeur>=4200) 	iResult = 4200;
	if(valeur>=4300) 	iResult = 4300;
	if(valeur>=4401) 	iResult = 4401;
	if(valeur>=5100) 	iResult = 5100;
	if(valeur>=5200) 	iResult = 5200;
	if(valeur>=5500) 	iResult = valeur;
	if(valeur>=5600) 	iResult = 5600;
	if(valeur>=6000) 	iResult = 6000;
	if(valeur>=6100) 	iResult = 6100;

	EnterCriticalSection(&crit);
		test = iResult;
		// Icrémentation de la variable d'évoution
		evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);
	if(genere_TS)
	{
		proto->AjouterTS(NULL,AUD_RESET);
	}

	return iResult;
}
// Lock ******************************************
int CEquipAudio::Lock() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = lock;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAudio::ChangeLock(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 9999)
	{
		EnterCriticalSection(&crit);
			lock = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

	}
	else
	{
		EnterCriticalSection(&crit);
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		iResult = ERR_NON_CONFORME;
	}
	return iResult;
}

// Relais ******************************************
int CEquipAudio::EtatRelais(int x, int y) const
{
	int		iResult;

	if(x<0 || x>=MAX_CARTE || y<0 || y>=MAX_RELAIS) return 	ERR_NON_CONFORME;
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = relais[x][y];
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAudio::ChangeEtatRelais(int x, int y, int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(x<0 || x>=MAX_CARTE || y<0 || y>=MAX_RELAIS) return 	ERR_NON_CONFORME;
	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			relais[x][y] = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

	}
	else
	{
		EnterCriticalSection(&crit);
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		iResult = ERR_NON_CONFORME;
	}

	return iResult;
}
