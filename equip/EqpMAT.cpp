// EqpMAT.cpp: implementation of the CEqpMAT class.
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

#include "Equip\EqpMAT.h"
#include "Comm\p_MAT.h"
#include "DLGmatSPIN.h"
#include "DLGmatL11.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_MAT_SPIN[];
extern char glob_CONTEXT_MAT_L11[];
extern char cour_CONTEXT_MAT_SPIN[];
extern char cour_CONTEXT_MAT_L11[];

const int SEPARE_TRAME	= 0x0D;	// Separateur de commande

/* **************************************************************************
METHODE :		CEqpMAT(int idx)
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEqpMAT::CEqpMAT(int idx, TypeMatrice type):CEquip(idx)
{
	TYPE_MATRICE = type;

	// Initialise le type de matrice SPIN
	if(TYPE_MATRICE == SPIN)
	{
		NB_PM = 4;
		NB_ER = 9;
	}
	// Initialise le type de matrice L11
	if(TYPE_MATRICE == L11)
	{
		NB_PM = 2;
		NB_ER = 14;
	}
	InitialiserMatrice();
}

/* **************************************************************************
METHODE :		~CEqpMAT
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEqpMAT::~CEqpMAT()
{
	free(MATRICE_COMMUT);
}

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEqpMAT::Allocation()
{
	t_affecte ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL)
		proto = new CProto_MAT(ligne.format,this);

	if(ihm == NULL)
	{
		if(TYPE_MATRICE == SPIN)
			ihm = new CDLGmatSPIN;
		if(TYPE_MATRICE == L11)
			ihm = new CDLGmatL11;
	}
	ihm->Associe(this);

	// Allocation protocole matrice SPIN
	if(TYPE_MATRICE == SPIN)
	{
		ihm->Create(IDD_SPIN,glob_ihm);
		ihm->SetWindowText(ligne.repere);
		Afficher(ligne.controle);
		Charge_Contexte(glob_CONTEXT_MAT_SPIN);
	}
	// Allocation protocole matrice L11
	if(TYPE_MATRICE == L11)
	{
		ihm->Create(IDD_L11,glob_ihm);
		ihm->SetWindowText(ligne.repere);
		Afficher(ligne.controle);
		Charge_Contexte(glob_CONTEXT_MAT_L11);
	}
}

/* **************************************************************************
METHODE :		Charge_Contexte(char *fichier)
TRAITEMENT:		Initialise l'equipement a partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEqpMAT::Charge_Contexte(char *fichier)
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
	if( (strcmp(ligne+4, "SPIN")!=0) || (strcmp(ligne+4, "L11")!=0))
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
		for(k=0; k<NB_ER; k++)
		{
			if( ligne[4+k] == '1')
				MATRICE_COMMUT[0][k] = true;
			else
				MATRICE_COMMUT[0][k] = false;
		}
	}

	// Ligne 2 de la matrice
	iResult = Extrait_ligne(contenu, "P02=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for(k=0; k<NB_ER; k++)
		{
			if( ligne[4+k] == '1')
				MATRICE_COMMUT[1][k] = true;
			else
				MATRICE_COMMUT[1][k] = false;
		}
	}

	// Lignes supplementaires pour la matrice SPIN
	if(TYPE_MATRICE == SPIN)
	{
		// Ligne 3 de la matrice
		iResult = Extrait_ligne(contenu, "P03=", ligne, TAILLE_MAX_LIGNE);
		if(iResult >= 0)
		{
			for(k=0; k<NB_ER; k++)
			{
				if( ligne[4+k] == '1')
					MATRICE_COMMUT[2][k] = true;
				else
					MATRICE_COMMUT[2][k] = false;
			}
		}

		// Ligne 4 de la matrice
		iResult = Extrait_ligne(contenu, "P04=", ligne, TAILLE_MAX_LIGNE);
		if(iResult >= 0)
		{
			for(k=0; k<NB_ER; k++)
			{
				if( ligne[4+k] == '1')
					MATRICE_COMMUT[3][k] = true;
				else
					MATRICE_COMMUT[3][k] = false;
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
BOOL CEqpMAT::Sauve_Contexte(char *fichier)
{
	int  i,iResult, j, k;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];

	// En tete fichier de la matrice SPIN
	if(TYPE_MATRICE == SPIN)
	{
		strcpy(contenu, "// Contexte d'exploitation d'une matrice SPIN\r\n");
		strcat(contenu, "// *********************************************\r\n");
		strcpy(ligne, "P00=SPIN\r\n");
		strcat(contenu, ligne);
	}

	// En tete fichier de la matrice L11
	if(TYPE_MATRICE == L11)
	{
		strcpy(contenu, "// Contexte d'exploitation d'une matrice L11\r\n");
		strcat(contenu, "// *********************************************\r\n");
		strcpy(ligne, "P00=L11\r\n");
		strcat(contenu, ligne);
	}

	// Lignes de la matrice
	for(j=0; j<NB_PM; j++)
	{
		sprintf(ligne, "P0%d=", j+1);
		strcat(contenu, ligne);
		for(k=0; k<NB_ER; k++)
		{
			if(MATRICE_COMMUT[j][k] == true)
				sprintf(ligne, "1");
			else
				sprintf(ligne, "0");
			strcat(contenu, ligne);
		}
		sprintf(ligne, "\r\n");
		strcat(contenu, ligne);
	}

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
BOOL CEqpMAT::Power()
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
bool CEqpMAT::Local() const
{
	bool bResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		bResult = local;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return bResult;
}

/* **************************************************************************
METHODE :		ChangeLocal(int valeur)
TRAITEMENT:		Change l'etat local de la face avant
***************************************************************************	*/
void CEqpMAT::ChangeLocal(bool b)
{
	EnterCriticalSection(&crit);
		local = b;
		evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		Initialiser()
TRAITEMENT:		Initialiser la matrice
***************************************************************************	*/
void CEqpMAT::InitialiserMatrice()
{
	int i, j;

	// Allocation de la memoire
	MATRICE_COMMUT = new bool * [NB_PM];
	MATRICE_COMMUT[0] = new bool[NB_PM*NB_ER];

	for(i=0; i<NB_PM;i++)
	{
        MATRICE_COMMUT[i] = &MATRICE_COMMUT[0][NB_ER*i];
	}

	// Initialisation matrice
	for(i=0; i<NB_PM; i++)
	{
		for(j=0; j<NB_ER; j++)
		{
			MATRICE_COMMUT[i][j] = false;
		}
	}
}

/* **************************************************************************
METHODE :		ResetMatrice()
TRAITEMENT:		Met la matrice dans son etat initial.
***************************************************************************	*/
void CEqpMAT::ResetMatrice()
{
	int i, j;

	// Initialisation matrice
	EnterCriticalSection(&crit);
		for(i=0; i<NB_PM; i++)
		{
			for(j=0; j<NB_ER; j++)
			{
				MATRICE_COMMUT[i][j] = false;
			}
		}
		evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);
}

/* **************************************************************************
METHODE :		ValiderMatrice()
TRAITEMENT:		Valide la matrice (superflux)
***************************************************************************	*/
BOOL CEqpMAT::ValiderMatrice()
{
	int  i, j;
	BOOL btemp;
	int  iE, iR, iER;

	// Validation de la matrice SPIN
	if(TYPE_MATRICE == SPIN)
	{
		for(i=0; i<NB_PM; i++)
		{
			btemp = FALSE;
			for(j=0; j<NB_ER; j++)
			{
				if(MATRICE_COMMUT[i][j] == true)
				{
					if(btemp == TRUE)
						return FALSE;
					else
						btemp = TRUE;
				}
			}
		}
	}

	// Validation de la matrice L11
	if(TYPE_MATRICE == L11)
	{
		for(i=0; i<NB_PM; i++)
		{
			iE  = 0;
			iR  = 0;
			iER = 0;
			for(j=0; j<=4; j++)
			{
				if(MATRICE_COMMUT[i][j] == true)
					iE ++;
			}
			for(j=6; j<=9; j++)
			{
				if(MATRICE_COMMUT[i][j] == true)
					iR ++;
			}
			for(j=9; j<=14; j++)
			{
				if(MATRICE_COMMUT[i][j] == true)
					iER ++;
			}
			// Si aucun E/R, presence probable d'un E et/ou d'un R
			if(iER == 0)
			{
				if(iE>1 || iR>1)
					return FALSE;
			}
			if(iER == 1)
			{
				if(iE != 0 || iR != 0)
					return FALSE;
			}
		}
	}

	return TRUE;
}

/* **************************************************************************
METHODE :		ChgtEtatMatrice(int idxPM, int idxER)
TRAITEMENT:		Connecte sur la matrice la connexion recue par TC
***************************************************************************	*/
void CEqpMAT::ChgtEtatMatrice(int idxPM, int idxER)
{
	int  i;

	if(idxPM>=NB_PM || idxER>=NB_ER)
	{
		proto->EnvoyerTS("KO");
		return ;
	}

	if(idxPM<0 || idxER<0)
	{
		proto->EnvoyerTS("KO");
		return ;
	}

	else
	{
		// Sur la matrice SPIN
		EnterCriticalSection(&crit);
			if(TYPE_MATRICE == SPIN)
			{
				// Verifie si le processeur P est libre
				for(i=0; i<NB_ER; i++)
				{
					if(MATRICE_COMMUT[idxPM][i] == true)
					{
						MATRICE_COMMUT[idxPM][i] = false;
						break;
					}
				}
				// Verifie si l'emetteur n'est pas deja connecte
				for(i=0; i<NB_PM; i++)
				{
					if(MATRICE_COMMUT[i][idxER] == true)
					{
						MATRICE_COMMUT[i][idxER] = false;
						break;
					}
				}
				// On commute ou on connecte
				MATRICE_COMMUT[idxPM][idxER] = true;
				proto->EnvoyerTS("OK");
			}
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		// Sur la matrice L11
		EnterCriticalSection(&crit);
			if(TYPE_MATRICE == L11 && idxPM<NB_PM && idxER <NB_ER)
			{
				switch (idxER)
				{
				// Commutation d'un emetteur
				case 0:
				case 1:
				case 2:
				case 3:
				case 4:
					for(i=0; i<=4; i++)
					{
						MATRICE_COMMUT[idxPM][i] = false;
					}
					for(i=10; i<=13; i++)
					{
						MATRICE_COMMUT[idxPM][i] = false;
					}
					if(MATRICE_COMMUT[1-idxPM][idxER])
						MATRICE_COMMUT[1-idxPM][idxER] = false;
					MATRICE_COMMUT[idxPM][idxER] = true;
					proto->EnvoyerTS("OK");
					break;
				// NU
				case 5:
					proto->EnvoyerTS("KO");
					break;
				// Commutation d'un Recepteur
				case 6:
				case 7:
				case 8:
				case 9:
					for(i=6; i<=9; i++)
					{
						MATRICE_COMMUT[idxPM][i] = false;
					}
					for(i=10; i<=13; i++)
					{
						MATRICE_COMMUT[idxPM][i] = false;
					}
					if(MATRICE_COMMUT[1-idxPM][idxER])
						MATRICE_COMMUT[1-idxPM][idxER] = false;
					MATRICE_COMMUT[idxPM][idxER] = true;
					proto->EnvoyerTS("OK");
					break;
				// Commutation d'un Emetteur/Recepteur
				case 10:
				case 11:
				case 12:
				case 13:
					for(i=0; i<NB_ER; i++)
					{
						MATRICE_COMMUT[idxPM][i] = false;
					}
					if(MATRICE_COMMUT[1-idxPM][idxER])
						MATRICE_COMMUT[1-idxPM][idxER] = false;
					MATRICE_COMMUT[idxPM][idxER] = true;
					proto->EnvoyerTS("OK");
					break;
				default:
					proto->EnvoyerTS("KO");
					break;
				}
			}
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
	}
}

/* **************************************************************************
METHODE :		DeconnexionMatrice(int idxPM, int idxER)
TRAITEMENT:		Deconnexion d'un E ou R ou E/R de la matrice
***************************************************************************	*/
void CEqpMAT::DeconnexionMatrice(int idxER)
{
	if(idxER<0 || idxER>NB_ER)
	{
		proto->EnvoyerTS("KO");
		return ;
	}
	if(TYPE_MATRICE == L11)
	{
		EnterCriticalSection(&crit);
		if(MATRICE_COMMUT[0][idxER] == true || MATRICE_COMMUT[1][idxER] == true)
		{
			MATRICE_COMMUT[0][idxER] = false;
			MATRICE_COMMUT[1][idxER] = false;
			proto->EnvoyerTS("OK");
		}
		else
		{
			proto->EnvoyerTS("KO");
		}
		evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
	}
	else if(TYPE_MATRICE == SPIN)
	{
		EnterCriticalSection(&crit);
		if(MATRICE_COMMUT[0][idxER] == true || MATRICE_COMMUT[1][idxER] == true ||
			MATRICE_COMMUT[2][idxER] == true || MATRICE_COMMUT[3][idxER] == true )
		{
			MATRICE_COMMUT[0][idxER] = false;
			MATRICE_COMMUT[1][idxER] = false;
			MATRICE_COMMUT[2][idxER] = false;
			MATRICE_COMMUT[3][idxER] = false;
			proto->EnvoyerTS("OK");
		}
		else
		{
			proto->EnvoyerTS("KO");
		}
		evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
	}
}

/* **************************************************************************
METHODE :		VerifConnexionMatrice(int idxPM, int idxER)
TRAITEMENT:		Verifie la connexion
***************************************************************************	*/
void CEqpMAT::VerifConnexionMatrice(int idxER)
{
	if(idxER<0 || idxER>NB_ER)
	{
		proto->EnvoyerTS("KO");
		return ;
	}
	if(TYPE_MATRICE == L11)
	{
		if(MATRICE_COMMUT[0][idxER] == true || MATRICE_COMMUT[1][idxER] == true)
		{
			proto->EnvoyerTS("KO");
		}
		else
		{
			proto->EnvoyerTS("OK");
		}
	}
	else if(TYPE_MATRICE == SPIN)
	{
		if(MATRICE_COMMUT[0][idxER] == true || MATRICE_COMMUT[1][idxER] == true ||
			MATRICE_COMMUT[2][idxER] == true || MATRICE_COMMUT[3][idxER] == true)
		{
			proto->EnvoyerTS("KO");
		}
		else
		{
			proto->EnvoyerTS("OK");
		}
	}
}

/* **************************************************************************
METHODE :		EtatMatrice()
TRAITEMENT:		Demande d'etat general de la matrice
***************************************************************************	*/
void CEqpMAT::EtatMatrice()
{
	int  i, j, k;
	char reponse[21];
	char buffer[6];
	bool temp, presence;

	sprintf(reponse, "ET");

	// Cas de la matrice SPIN
	if(TYPE_MATRICE == SPIN)
	{
		for(i=0; i<NB_PM; i++)
		{
			temp = false;
			for(j=0; j<NB_ER; j++)
			{
				if(MATRICE_COMMUT[i][j] == true)
				{
					sprintf(buffer, "000%d", j+1);
					strcat(reponse, buffer);
					temp = true;
				}
			}
			if(temp == false)
			{
				sprintf(buffer, "0000");
				strcat(reponse, buffer);
			}
		}
	}

	// Cas le la matrice L11
	if(TYPE_MATRICE == L11)
	{
		for(i=0; i<NB_PM; i++)
		{
			j = 0;
			temp = false;
			presence = false;
			while(j<NB_ER && MATRICE_COMMUT[i][j] != true)
			{
				j++;
			}
			switch (j)
			{
			// Cas d'un E de 0 a 4
			case 0:
			case 1:
			case 2:
			case 3:
			case 4:
				presence = true;
				k = j;
				do
				{
					k++;
					if(MATRICE_COMMUT[i][k] == true)
						temp = true;
				}
				while(k<10 && MATRICE_COMMUT[i][k] != true);
				if(temp == true)
				{
					if( (k+1) == 10)
						sprintf(buffer, "0%d%d", j+1, k+1);
					else
						sprintf(buffer, "0%d0%d", j+1, k+1);
					strcat(reponse, buffer);
				}
				else
				{
					sprintf(buffer, "0%d00", j+1);
					strcat(reponse, buffer);
				}
				break;
			// NU
			case 5:
				break;
			// Cas d'un R de 6 a 9
			case 6:
			case 7:
			case 8:
			case 9:
				presence = true;
				if(temp == false)
				{
					if( (j+1) == 10 )
						sprintf(buffer, "00%d", j+1);
					else
						sprintf(buffer, "000%d", j+1);
					strcat(reponse, buffer);
				}
				break;
			// Cas d'un E/R de 10 a 13
			case 10:
			case 11:
			case 12:
			case 13:
				presence = true;
				sprintf(buffer, "%d00", j+1);
				strcat(reponse, buffer);
			default:
				break;
			}
			if(!presence)
			{
				sprintf(buffer, "0000", j+1);
				strcat(reponse, buffer);
			}
		}
	}

	proto->EnvoyerTS(reponse);
}

/* **************************************************************************
METHODE :		PassageDistance()
TRAITEMENT:		Demande de passage à DISTANCE
***************************************************************************	*/
void CEqpMAT::PassageDistance()
{
	proto->EnvoyerTS("DIST");
}

/* **************************************************************************
METHODE :		VerrouillageFaceAvant()
TRAITEMENT:		Demande de verrouillage de la face avant
***************************************************************************	*/
void CEqpMAT::VerrouillageFaceAvant()
{
	//int iResult;					//2009-11-27

	// TODO : Verrouillage de la face avant
	/*EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = local;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);*/

	proto->EnvoyerTS("LOCK");
}

/* **************************************************************************
METHODE :		DeverrouillageFaceAvant()
TRAITEMENT:		Demande de deverrouillage de la face avant
***************************************************************************	*/
void CEqpMAT::DeverrouillageFaceAvant()
{
	proto->EnvoyerTS("ULOCK");
}

/* **************************************************************************
METHODE :		PassageErreur(int num)
TRAITEMENT:		Demande de passage d'une erreur
***************************************************************************	*/
void CEqpMAT::PassageErreur(int num)
{
	proto->AjouterTS(NULL, num);
}

/* **************************************************************************
METHODE :		EnregistrerMatrice()
TRAITEMENT:		Enregistre dans un fichier la matrice courante
***************************************************************************	*/
BOOL CEqpMAT::EnregistrerMatrice()
{
	int  i, iResult, j, k;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];
	char fichier[32];

	// En tete fichier de la matrice SPIN
	if(TYPE_MATRICE == SPIN)
	{
		strcpy(contenu, "// Matrice courante SPIN\r\n");
		strcat(contenu, "// *********************\r\n");
		strcpy(ligne, "P00=SPIN\r\n");
		strcat(contenu, ligne);
		sprintf(fichier, "%s%c", cour_CONTEXT_MAT_SPIN, '0');
	}

	// En tete fichier de la matrice L11
	if(TYPE_MATRICE == L11)
	{
		strcpy(contenu, "// Matrice courante L11\r\n");
		strcat(contenu, "// ********************\r\n");
		strcpy(ligne, "P00=L11\r\n");
		strcat(contenu, ligne);
		sprintf(fichier, "%s%c", cour_CONTEXT_MAT_L11, '0');
	}

	// Lignes de la matrice
	for(j=0; j<NB_PM; j++)
	{
		sprintf(ligne, "P0%d=", j+1);
		strcat(contenu, ligne);
		for(k=0; k<NB_ER; k++)
		{
			if(MATRICE_COMMUT[j][k] == true)
				sprintf(ligne, "1");
			else
				sprintf(ligne, "0");
			strcat(contenu, ligne);
		}
		sprintf(ligne, "\r\n");
		strcat(contenu, ligne);
	}

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
METHODE :		ChargerMatrice()
TRAITEMENT:		Rappel de la matrice enregistree dans un fichier
***************************************************************************	*/
BOOL CEqpMAT::ChargerMatrice()
{
	int  i,iResult, k;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];
	char cle[10];
	char fichier[32];

	if(TYPE_MATRICE == SPIN)
	{
		sprintf(fichier, "%s%c", cour_CONTEXT_MAT_SPIN, '0');
	}

	if(TYPE_MATRICE == L11)
	{
		sprintf(fichier, "%s%c", cour_CONTEXT_MAT_L11, '0');
	}

	iResult = Recup_fichier(fichier, contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation", iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu, "P00=", ligne, TAILLE_MAX_LIGNE);
	if( (strcmp(ligne+4, "SPIN")!=0) || (strcmp(ligne+4, "L11")!=0))
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
		for(k=0; k<NB_ER; k++)
		{
			if( ligne[4+k] == '1')
				MATRICE_COMMUT[0][k] = true;
			else
				MATRICE_COMMUT[0][k] = false;
		}
	}

	// Ligne 2 de la matrice
	iResult = Extrait_ligne(contenu, "P02=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for(k=0; k<NB_ER; k++)
		{
			if( ligne[4+k] == '1')
				MATRICE_COMMUT[1][k] = true;
			else
				MATRICE_COMMUT[1][k] = false;
		}
	}

	// Lignes supplementaires pour la matrice SPIN
	if(TYPE_MATRICE == SPIN)
	{
		// Ligne 3 de la matrice
		iResult = Extrait_ligne(contenu, "P03=", ligne, TAILLE_MAX_LIGNE);
		if(iResult >= 0)
		{
			for(k=0; k<NB_ER; k++)
			{
				if( ligne[4+k] == '1')
					MATRICE_COMMUT[2][k] = true;
				else
					MATRICE_COMMUT[2][k] = false;
			}
		}

		// Ligne 4 de la matrice
		iResult = Extrait_ligne(contenu, "P04=", ligne, TAILLE_MAX_LIGNE);
		if(iResult >= 0)
		{
			for(k=0; k<NB_ER; k++)
			{
				if( ligne[4+k] == '1')
					MATRICE_COMMUT[3][k] = true;
				else
					MATRICE_COMMUT[3][k] = false;
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
