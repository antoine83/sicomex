// EqpTemp.cpp: implementation of the CEquipTemp class.
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

#include "Equip\EqpTemp.h"
#include "Comm\p_temp.h"
#include "DLGtemp.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_EMETHF[];

/* **************************************************************************
METHODE :		CEquipTemp(int idx)
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquipTemp::CEquipTemp(int idx):CEquip(idx)
{
	// TODO : integrer le constructeur
}

/* **************************************************************************
METHODE :		~CEquipTemp
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquipTemp::~CEquipTemp()
{
}

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipTemp::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);

	if(proto == NULL)
	{
		proto = new CProtoTemp(ligne.format,this);
	}
	if(ihm == NULL)
	{
		ihm = new CDLGtemp;
	}
	ihm->Associe(this);
	ihm->Create(IDD_TEMP,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_EMETHF);
}

/* **************************************************************************
METHODE :		Charge_Contexte(char *fichier)
TRAITEMENT:		Initialise l'equipement a partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipTemp::Charge_Contexte(char *fichier)
{
	int  i,iResult;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];
	char cle[10];

	iResult = Recup_fichier(fichier,contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation",iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P00=",ligne,TAILLE_MAX_LIGNE);
	if(strcmp(ligne+4,"EMET_HF")!=0)
	if(iResult<0)
	{
		AjouterMessage("**** Erreur fichier non conforme à l'équipement",iResult);
		return FALSE;
	}

	// TODO : integrer ici le format de charge du fichier defaut

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
BOOL CEquipTemp::Sauve_Contexte(char *fichier)
{
	int  i,iResult;

	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];

	strcpy(contenu,"// Contexte d'exploitation d'un émetteur HF\r\n");
	strcat(contenu,"// *****************************************\r\n");

	strcpy(ligne,"P00=EMET_HF\r\n");
	strcat(contenu,ligne);

	// TODO : integrer ici le format de sauvegarde du fichier defaut

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
BOOL CEquipTemp::Power()
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
METHODE :		Local()
TRAITEMENT:		Retourne l'etat local de la face avant
***************************************************************************	*/
int CEquipTemp::Local() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = local;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

/* **************************************************************************
METHODE :		ChangeLocal(int valeur,BOOL genere_TS)
TRAITEMENT:		Change l'etat local de la face avant
***************************************************************************	*/
int CEquipTemp::ChangeLocal(int valeur,BOOL genere_TS)
{
	int iResult = valeur;

	if(valeur>=0 && valeur <= 2)
	{
		EnterCriticalSection(&crit);
			local = valeur;
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			// TODO : integrer l'AjouterTS du mode local
			// Mode telecommande
			if(valeur ==1 )
			{
				// TODO : integrer l'AjouterTS du changement de mode local
			}
		}
	}
	else
	{
		iResult = ERR_NON_CONFORME;
	}

	return iResult;
}
