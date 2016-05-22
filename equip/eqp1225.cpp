/* **************************************************************************
FICHIER :	Eqp1225.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip1225
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\Eqp1225.h"
#include "Comm\p_1225.h"
#include "DlgEmHF.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

const int	SEUIL_NIVEAU_HF 	= 25;

extern char glob_CONTEXT_EMETHF[];
/* **************************************************************************
METHODE :		CEquip1225()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquip1225::CEquip1225(int idx):CEquip(idx)
{
	int		i;
	local 		= 1;		// Mode télécommande

	canal 		= 0;
	for(i=0 ; i<100 ; i++)
	{
		carac_canal[i].mode_trafic = 0;   		// CW
		carac_canal[i].frequence 	= 1000000;	// 1MHz
		carac_canal[i].fonction 	= 2;		// Puissance normale
	}

	compresseur = 0;		// Pas de comresseur

	incident 	= 0;		// Pas d'incident

	auto_niveau = 0;		
	niveau 		= 15;
	choix_niveau = 3;		// RF Exiteur

	test 		= 0;

	info 		= 0;		// Pas de presence d'info
}

/* **************************************************************************
METHODE :		~CEquip1225
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquip1225::~CEquip1225()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquip1225::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProto1225(ligne.format,this);

	if(ihm == NULL) ihm = new CDlgEmetHF;
	ihm->Associe(this);
	ihm->Create(F3_IDD_TRC1225M,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_EMETHF);
}

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquip1225::Charge_Contexte(char *fichier)
{
	int 	i,iResult;

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
	if(strcmp(ligne+4,"EMET_HF")!=0)
	if(iResult<0)
	{
		AjouterMessage("**** Erreur fichier non conforme à l'équipement",iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P01=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeLocal(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P02=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeModeTrafic(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P03=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeCompresseur(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P04=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeFonction(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P05=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeIncident(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P06=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeFrequence(0,atol(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P07=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAutoNiveau(atoi(ligne+4));

	iResult = Extrait_ligne(contenu,"P08=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeNiveau(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P09=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeChoixNiveau(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P10=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeCanal(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P11=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeTest(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P12=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeInfo(atoi(ligne+4),FALSE);

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
BOOL CEquip1225::Sauve_Contexte(char *fichier)
{
	int 	i,iResult;

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];

	strcpy(contenu,"// Contexte d'exploitation d'un émetteur HF\r\n");
	strcat(contenu,"// *****************************************\r\n");

	strcpy(ligne,"P00=EMET_HF\r\n");
	strcat(contenu,ligne);

	sprintf(ligne,"P01=%d\r\n",Local());
	strcat(contenu,ligne);

	sprintf(ligne,"P02=%d\r\n",ModeTrafic(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P03=%d\r\n",Compresseur());
	strcat(contenu,ligne);

	sprintf(ligne,"P04=%d\r\n",Fonction(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P05=%d\r\n",Incident());
	strcat(contenu,ligne);

	sprintf(ligne,"P06=%ld\r\n",Frequence(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P07=%d\r\n",AutoNiveau());
	strcat(contenu,ligne);

	sprintf(ligne,"P08=%d\r\n",Niveau());
	strcat(contenu,ligne);

	sprintf(ligne,"P09=%d\r\n",ChoixNiveau());
	strcat(contenu,ligne);

	sprintf(ligne,"P10=%d\r\n",0);
	strcat(contenu,ligne);

	sprintf(ligne,"P11=%d\r\n",Test());
	strcat(contenu,ligne);

	sprintf(ligne,"P12=%d\r\n",Info());
	strcat(contenu,ligne);

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
BOOL CEquip1225::Power()
{
	BOOL	activite;
	CEquip::Power();

	activite = Actif();
	if(activite)
	{
		//proto->AjouterTS("Initialisation",CDE_TEXTE_SEUL);
		proto->AjouterTS(NULL,EME_MODE_LOCAL);
		proto->AjouterTS(NULL,EME_OPTION);
		proto->AjouterTS(NULL,EME_FREQUENCE);
		proto->AjouterTS(NULL,EME_MODE_FONCT);
		proto->AjouterTS(NULL,EME_COMPRESSEUR);
		proto->AjouterTS(NULL,EME_MODE_TRAFIC);
		proto->AjouterTS(NULL,EME_CANAL_POSI);
		proto->AjouterTS(NULL,EME_ETAT_LOGI);
		proto->AjouterTS(NULL,EME_INFO);
	}
	else
	{
//		proto->AjouterTS("Arret de l'équipement",CDE_TEXTE_SEUL);
	}
	return activite;
}

// Local ******************************************
int CEquip1225::Local() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = local;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1225::ChangeLocal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 2)
	{
		EnterCriticalSection(&crit);
			local = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,EME_MODE_LOCAL);

			if(valeur ==1 )		// Mode telecommande
			{
				proto->AjouterTS(NULL,EME_OPTION);
				proto->AjouterTS(NULL,EME_FREQUENCE);
				proto->AjouterTS(NULL,EME_MODE_FONCT);
				proto->AjouterTS(NULL,EME_COMPRESSEUR);
				proto->AjouterTS(NULL,EME_MODE_TRAFIC);
				proto->AjouterTS(NULL,EME_CANAL_POSI);
				proto->AjouterTS(NULL,EME_ETAT_LOGI);
				proto->AjouterTS(NULL,EME_INFO);
			}
		}
	}
	else iResult = ERR_NON_CONFORME;

	return iResult;
}

// Mode de trafic *********************************************
int CEquip1225::ModeTrafic(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].mode_trafic;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip1225::ChangeModeTrafic(int num_canal,int valeur,BOOL genere_TS)
{
	int		iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=5)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].mode_trafic = valeur;

			switch(valeur)
			{
				case 0:
					compresseur = 0;
					break;
				case 1:
					compresseur = 1;
					break;
				case 2:
					compresseur = 1;
					break;
				case 3:
					compresseur = 1;
					break;
				case 4:
					compresseur = 1;
					break;
				case 5:
					compresseur = 0;
					break;
			}

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto1225*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EME_MODE_TRAFIC);
			proto->AjouterTS(NULL,EME_COMPRESSEUR);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - carac_canal[num_canal].mode_trafic; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}
// Compresseur *********************************************
int CEquip1225::Compresseur() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = compresseur;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip1225::ChangeCompresseur(int valeur,BOOL genere_TS)
{
	int		iResult = valeur;
	if(valeur >=0 && valeur <=1)
	{

		EnterCriticalSection(&crit);
			if((carac_canal[Canal()].mode_trafic%5) == 0)
			{
					iResult = 0;
			}

			compresseur = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EME_COMPRESSEUR);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - compresseur; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}
	return iResult;
}

// Mode de fonctionnement *********************************************
int CEquip1225::Fonction(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].fonction;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1225::ChangeFonction(int num_canal,int valeur,BOOL genere_TS)
{
	char	buf[80];

	int		iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=9)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].fonction = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto1225*)proto)->ChangeCanalLecture(num_canal);
			proto->TraiteTS(EME_MODE_FONCT,buf);
			buf[2]='?';
			proto->AjouterTS(buf,EME_MODE_FONCT);
			proto->AjouterTS(NULL,CDE_TEMPO_SEQ);

			if(Incident())
			{
				buf[2]='=';
				proto->AjouterTS(buf,EME_MODE_FONCT);
			}
			else proto->AjouterTS(NULL,EME_MODE_FONCT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - carac_canal[num_canal].fonction; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}
	return iResult;
}
// Incident *********************************************
int CEquip1225::Incident() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = incident;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1225::ChangeIncident(int valeur,BOOL genere_TS)
{
	int		iResult = valeur;

	if(valeur >=-1 && valeur <=999)
	{
		EnterCriticalSection(&crit);
			incident = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EME_INCIDENT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - incident; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}
	return iResult;
}
// Frequence ******************************************
long CEquip1225::Frequence(int num_canal) const
{
	long		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].frequence;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

long CEquip1225::ChangeFrequence(int num_canal,long valeur,BOOL genere_TS)
{
	char		buf[80];
	long	lResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur>=400000 && valeur <= 29999990)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].frequence = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			((CProto1225*)proto)->ChangeCanalLecture(num_canal);
			proto->TraiteTS(EME_FREQUENCE,buf);

			buf[(int)strlen(buf)-1] = '<';
			proto->AjouterTS(buf,EME_FREQUENCE);
			proto->AjouterTS(NULL,CDE_TEMPO_SEQ);

			buf[(int)strlen(buf)-1] = '?';
			proto->AjouterTS(buf,EME_FREQUENCE);
			proto->AjouterTS(NULL,CDE_TEMPO_SEQ);

			if(Incident())
			{
				buf[(int)strlen(buf)-1] = '=';
				proto->AjouterTS(buf,EME_FREQUENCE);
			}
			else
			{
				buf[(int)strlen(buf)-1] = '>';
				proto->AjouterTS(buf,EME_FREQUENCE);
			}
		}



	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			lResult = - carac_canal[num_canal].frequence; // Ancienne valeur en code erreur
		LeaveCriticalSection(&crit);
	}

	return lResult;
}

// Niveau *********************************************
int CEquip1225::AutoNiveau() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = auto_niveau;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1225::ChangeAutoNiveau(int valeur)
{
	int		iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			auto_niveau = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
	}
	else iResult = -1;

	return iResult;
}

int CEquip1225::Niveau() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = niveau;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1225::ChangeNiveau(int valeur,BOOL genere_TS)
{
	int		iResult = valeur;

	if(valeur >=0 && valeur <=0xFF)
	{
		EnterCriticalSection(&crit);
			niveau = iResult;

			if(valeur > SEUIL_NIVEAU_HF)
			{
				if(!Info()) ChangeInfo(TRUE,TRUE);
			}
			else
				if(Info()) ChangeInfo(FALSE,TRUE);

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EME_NIVEAU);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - niveau; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}
	return iResult;
}

int CEquip1225::ChoixNiveau() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = choix_niveau;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1225::ChangeChoixNiveau(int valeur,BOOL genere_TS)
{
	int		iResult = valeur;

	if(valeur >=0 && valeur <=7)
	{
		EnterCriticalSection(&crit);
			choix_niveau = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
//			proto->AjouterTS(NULL,EME_NIVEAU);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - choix_niveau; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}
	return iResult;
}

// Positionnement de canal***************************************
int CEquip1225::Canal() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = canal;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1225::ChangeCanal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;
	char	buf[80];

	if(valeur>=0 && valeur <= 99)
	{
		EnterCriticalSection(&crit);
			canal = valeur;
			carac_canal[0] = carac_canal[valeur];

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->TraiteTS(EME_CANAL_POSI,buf);

			buf[(int)strlen(buf)-1] = '<';
			proto->AjouterTS(buf,EME_CANAL_POSI);
			proto->AjouterTS(NULL,CDE_TEMPO_SEQ);

			buf[(int)strlen(buf)-1] = '?';
			proto->AjouterTS(buf,EME_CANAL_POSI);
			proto->AjouterTS(NULL,CDE_TEMPO_SEQ);

			if(Incident())
			{
				buf[(int)strlen(buf)-1] = '=';
				proto->AjouterTS(buf,EME_CANAL_POSI);
			}
			else
			{
				buf[(int)strlen(buf)-1] = '>';
				proto->AjouterTS(buf,EME_CANAL_POSI);
			}
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = -canal;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}
int CEquip1225::MemoriseCanal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=1 && valeur <= 99)
	{
		EnterCriticalSection(&crit);
			carac_canal[valeur] = carac_canal[0];
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto1225*)proto)->ChangeCanalLecture(valeur);
			proto->AjouterTS(NULL,EME_CANAL_LECT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = -canal;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Test ******************************************
int CEquip1225::Test() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = test;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1225::ChangeTest(int valeur,BOOL genere_TS)
{
	int 	iResult = 0;

	if(valeur>=0) 	iResult = 0;
	if(valeur>=29) 	iResult = 29;
	if(valeur>=30) 	iResult = 30;
	if(valeur>=35) 	iResult = 35;
	if(valeur>=40) 	iResult = 40;
	if(valeur>=50) 	iResult = 50;
	if(valeur>=55) 	iResult = 55;
	if(valeur>=62) 	iResult = 62;
	if(valeur>=64) 	iResult = 64;
	if(valeur>=66) 	iResult = 66;
	if(valeur>=70) 	iResult = 70;
	if(valeur>=71) 	iResult = 71;
	if(valeur>=72) 	iResult = 72;
	if(valeur>=73) 	iResult = 73;
	if(valeur>=74) 	iResult = 74;
	if(valeur>=76) 	iResult = 76;
	if(valeur>=80) 	iResult = 80;
	if(valeur>=81) 	iResult = 81;
	if(valeur>=84) 	iResult = 84;
	if(valeur>=85) 	iResult = 85;
	if(valeur>=86) 	iResult = 86;
	if(valeur>=87) 	iResult = 87;
	if(valeur>=91) 	iResult = 91;
	if(valeur>=92) 	iResult = 92;
	if(valeur>=93) 	iResult = 93;
	if(valeur>=94) 	iResult = 94;
	if(valeur>=95) 	iResult = 95;
	if(valeur>=96) 	iResult = 96;
	if(valeur>=97) 	iResult = 97;

	EnterCriticalSection(&crit);
		test = iResult;

		// Icrémentation de la variable d'évoution
		evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);

	if(genere_TS)
	{
		proto->AjouterTS(NULL,EME_TEST);
	}

	return iResult;
}

// Presence infos ******************************************
int CEquip1225::Info() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = info;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1225::ChangeInfo(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			info = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,EME_INFO);
		}
	}

	return iResult;
}
