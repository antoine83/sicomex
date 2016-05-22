/* **************************************************************************
FICHIER :	Eqp18A.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip18A
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\Eqp18A.h"
#include "Comm\p_18A.h"

#include "DlgEmRec.h"

#include "..\Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_EMREC[];
/* **************************************************************************
METHODE :		CEquip18A()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquip18A::CEquip18A(int idx):CEquip(idx)
{
	int			i;
	numero 			= 0x12;

	canal 			= 0;		// Pas de canal
	for(i=0 ; i<100 ; i++)
	{
		carac_canal[i].frequence_Em 	= 2500;		// 250 MHz
		carac_canal[i].niveau			= 2;		// -12 dB
		carac_canal[i].accord_multi		= 1;		// accord non demandé
		carac_canal[i].mode				= 0;		// F3E
		carac_canal[i].bande			= 0;		// WB
		carac_canal[i].cle_crypto		= 6;		
		carac_canal[i].antenne			= 0;
		carac_canal[i].squelch			= 0;
		carac_canal[i].frequence_Rec 	= 2500;		// 250 MHz
		carac_canal[i].pas_Em			= 2;		// 50 kHz
		carac_canal[i].pas_Rec			= 2;		// 50 kHz
		carac_canal[i].protection 		= 0;		// Pas de protection canal
	}
	relais			= 2;
	rec_garde		= 0;		// Arret + ancien à l'arret
	scan_debut		= 0;
	scan_fin		= 0;
	adresse			= 0xFF;		// Non reservé
	gene_crypto		= 0;
	status_evol		= 0;

	local			= 1;		// Distance

	panne_emr		= 0;
	panne_accord	= 0;

	HF_recu			= 0;
	ros				= 0;
	emission		= 0;
	silence			= 0;

	chiffre			= 0;
	test_en_cours	= 0;
	scan 			= 0;
	accord		 	= 0;
	
	code_test 		= 0;
}

/* **************************************************************************
METHODE :		~CEquip18A
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquip18A::~CEquip18A()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquip18A::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProto18A(ligne.format,this);

	if(ihm == NULL) ihm = new CDlgEmRecUHF;
	ihm->Associe(this);
	ihm->Create(F6_IDD_TRBM18A,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_EMREC);
}

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquip18A::Charge_Contexte(char *fichier)
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
	if(strcmp(ligne+4,"EMET_REC")!=0)
	if(iResult<0)
	{
		AjouterMessage("**** Erreur fichier non conforme à l'équipement",iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P01=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeNumero(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P02=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeFrequenceEm(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P03=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeCanal(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P04=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeNiveau(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P05=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAccordMulti(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P06=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeMode(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P07=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeBande(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P08=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeCleCrypto(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P09=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAdresse(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P10=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeSquelch(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P11=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeFrequenceRec(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P12=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangePasEm(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P13=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangePasRec(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P14=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeProtection(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P15=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeRelais(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P16=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeRecGarde(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P17=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeScanDebut(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P18=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeScanFin(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P19=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAdresse(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P20=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeGeneCrypto(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P21=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeLocal(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P22=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeHfRecu(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P23=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeRos(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P24=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeEmission(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P25=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeSilence(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P26=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeChiffre(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P27=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeTestEnCours(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P28=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeScan(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P29=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAccord(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P30=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeTest(atoi(ligne+4),FALSE);

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
BOOL CEquip18A::Sauve_Contexte(char *fichier)
{
	int 	i,iResult;

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];

	strcpy(contenu,"// Contexte d'exploitation d'un émetteur/récepteur UHF\r\n");
	strcat(contenu,"// ***************************************************\r\n");

	strcpy(ligne,"P00=EMET_REC\r\n");
	strcat(contenu,ligne);

	sprintf(ligne,"P01=%d\r\n",Numero());
	strcat(contenu,ligne);

	sprintf(ligne,"P02=%d\r\n",FrequenceEm(0));
	strcat(contenu,ligne);
 
	sprintf(ligne,"P03=%d\r\n",0);
	strcat(contenu,ligne);

	sprintf(ligne,"P04=%d\r\n",Niveau(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P05=%d\r\n",AccordMulti(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P06=%d\r\n",Mode(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P07=%d\r\n",Bande(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P08=%d\r\n",CleCrypto(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P09=%d\r\n",Antenne(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P10=%d\r\n",Squelch(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P11=%d\r\n",FrequenceRec(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P12=%d\r\n",PasEm(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P13=%d\r\n",PasRec(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P14=%d\r\n",Protection(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P15=%d\r\n",Relais());
	strcat(contenu,ligne);

	sprintf(ligne,"P16=%d\r\n",RecGarde());
	strcat(contenu,ligne);

	sprintf(ligne,"P17=%d\r\n",ScanDebut());
	strcat(contenu,ligne);

	sprintf(ligne,"P18=%d\r\n",ScanFin());
	strcat(contenu,ligne);

	sprintf(ligne,"P19=%d\r\n",Adresse());
	strcat(contenu,ligne);

	sprintf(ligne,"P20=%d\r\n",GeneCrypto());
	strcat(contenu,ligne);

	sprintf(ligne,"P21=%d\r\n",Local());
	strcat(contenu,ligne);

	sprintf(ligne,"P22=%d\r\n",HfRecu());
	strcat(contenu,ligne);

	sprintf(ligne,"P23=%d\r\n",Ros());
	strcat(contenu,ligne);

	sprintf(ligne,"P24=%d\r\n",Emission());
	strcat(contenu,ligne);

	sprintf(ligne,"P25=%d\r\n",Silence());
	strcat(contenu,ligne);

	sprintf(ligne,"P26=%d\r\n",Chiffre());
	strcat(contenu,ligne);

	sprintf(ligne,"P27=%d\r\n",TestEnCours());
	strcat(contenu,ligne);

	sprintf(ligne,"P28=%d\r\n",Scan());
	strcat(contenu,ligne);

	sprintf(ligne,"P29=%d\r\n",Accord());
	strcat(contenu,ligne);

	sprintf(ligne,"P30=%d\r\n",Test());
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
BOOL CEquip18A::Power()
{
	BOOL	activite;
	CEquip::Power();

	activite = Actif();
	if(activite)
	{
//		proto->AjouterTS("Initialisation",CDE_TEXTE_SEUL);
		proto->AjouterTS(NULL,EMR_STATUS);
		proto->AjouterTS(NULL,EMR_EXPLOITATION);

	}
	else
	{
//		proto->AjouterTS("Arret de l'équipement",CDE_TEXTE_SEUL);
	}
	return activite;

}

// Variable d'evolution *************
int CEquip18A::StatusEvolution() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = status_evol;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeStatusEvolution(int valeur)
{
	int 	iResult = valeur;

	if(valeur >= 0 && valeur <= 0xF)
	{
		EnterCriticalSection(&crit);
			status_evol = valeur;
		LeaveCriticalSection(&crit);
	}
	return iResult;
}

// Numero d'E/R *************
int CEquip18A::Numero() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = numero;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeNumero(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >= 1 && valeur < 0xFF)
	{
		EnterCriticalSection(&crit);
			numero = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Frequence d'emission *************
int CEquip18A::FrequenceEm(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].frequence_Em;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeFrequenceEm(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;
	char	reponse[TAILLE_PIPE_MESSAGE+1];


	EnterCriticalSection(&crit);
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(num_canal==0 && Canal()!=0 && !genere_TS) return ERR_CDE_INCONNUE;
	// genere_TS est vrai sur modification par IHM

	if(valeur >=2250 && valeur <=3999)
	{
 		if(FrequenceEm(num_canal) != valeur)
		{
			ChangeAccordMulti(num_canal,1,FALSE);	// Accord non demandé == 1

			if(!Silence() && genere_TS)		// Pas silence et par face avant
			{
				ChangeAccord(1,FALSE);
				ChangeAccordMulti(0,1,FALSE);	// Accord non demandé == 1
				ChangeEmission(1,FALSE);
				
				proto->TraiteTS(EMR_STATUS,reponse);
				proto->EnvoyerTS(reponse);

				proto->AjouterTS(NULL,CDE_TEMPO_SEQ);

				ChangeAccord(0,FALSE);
				ChangeEmission(0,FALSE);
				
				proto->AjouterTS(NULL,EMR_STATUS);
			}			

		}

		EnterCriticalSection(&crit);
			carac_canal[num_canal].frequence_Em = valeur;

			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);



		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
		iResult = ERR_NON_CONFORME;

	return iResult;
}

// Canal *************
int CEquip18A::Canal() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = canal;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeCanal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 99)
	{
		EnterCriticalSection(&crit);
			canal = valeur;
			if(valeur<95)
				carac_canal[valeur].frequence_Em = carac_canal[valeur].frequence_Rec;

			carac_canal[0] = carac_canal[valeur];
			if(valeur == 0) scan = 0;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
			proto->AjouterTS(NULL,EMR_STATUS);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}
	return iResult;
}
// Niveau *************
int CEquip18A::Niveau(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].niveau;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip18A::ChangeNiveau(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=4)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].niveau = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}
// Acoord Multicoupleur *************
int CEquip18A::AccordMulti(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].accord_multi;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip18A::ChangeAccordMulti(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=4)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].accord_multi = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Type de modulation *************
int CEquip18A::Mode(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].mode;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip18A::ChangeMode(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(num_canal==0 && Canal()!=0 && !genere_TS) return ERR_CDE_INCONNUE;
	// genere_TS est vrai sur modification par IHM

	if((valeur >=0 && valeur <=9) || valeur==0xB || valeur==0xC)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].mode = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Bande *************
int CEquip18A::Bande(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].bande;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip18A::ChangeBande(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].bande = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Cle crypto *************
int CEquip18A::CleCrypto(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].cle_crypto;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeCleCrypto(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=7)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].cle_crypto = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}
// Configuration Antenne *************
int CEquip18A::Antenne(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].antenne;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip18A::ChangeAntenne(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=5)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].antenne = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Squelch *************
int CEquip18A::Squelch(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].squelch;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip18A::ChangeSquelch(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].squelch = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Frequence de reception *************
int CEquip18A::FrequenceRec(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].frequence_Rec;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeFrequenceRec(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	EnterCriticalSection(&crit);
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(num_canal==0 && Canal()!=0 && !genere_TS) return ERR_CDE_INCONNUE;
	// genere_TS est vrai sur modification par IHM

	if(valeur >=2250 && valeur <=3999)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].frequence_Rec = valeur;

			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
		iResult = ERR_NON_CONFORME;

	return iResult;
}

// Pas de 25 kHz de l'émetteur *************
int CEquip18A::PasEm(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].pas_Em;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangePasEm(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=3)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].pas_Em = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Pas de 25 kHz du récepteur *************
int CEquip18A::PasRec(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].pas_Rec;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangePasRec(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=3)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].pas_Rec= valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Protection du canal *************
int CEquip18A::Protection(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].protection;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeProtection(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].protection= valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Relais Externes *************
int CEquip18A::Relais() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = relais;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeRelais(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=7)
	{
		EnterCriticalSection(&crit);
			relais= valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Recepteur de garde *************
int CEquip18A::RecGarde() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = rec_garde;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeRecGarde(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			rec_garde &= 0x2;
			rec_garde += valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Canal de de but de scan *************
int CEquip18A::ScanDebut() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = scan_debut;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeScanDebut(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=99)
	{
		EnterCriticalSection(&crit);
			scan_debut = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Canal de fin de scan *************
int CEquip18A::ScanFin() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = scan_fin;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeScanFin(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=99)
	{
		EnterCriticalSection(&crit);
			scan_fin = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Adresse de reservation *************
int CEquip18A::Adresse() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = adresse;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeAdresse(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=0xFF)
	{
		EnterCriticalSection(&crit);
			adresse = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Type de reservation *************
int CEquip18A::Reserve() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = reserve;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeReserve(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=2)
	{
		EnterCriticalSection(&crit);
			if(reserve == valeur)
			{
				LeaveCriticalSection(&crit);
				return ERR_PAS_ACQUITTE;
			}
			reserve = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Clé crypto générale *************
int CEquip18A::GeneCrypto() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = gene_crypto;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeGeneCrypto(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=6)
	{
		EnterCriticalSection(&crit);
			gene_crypto = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Variable d'evolution du satus *************
int CEquip18A::StatusEvol() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = status_evol;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

// Local / Distance *************
int CEquip18A::Local() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = local;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeLocal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			local = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_STATUS);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Panne EMR *************
int CEquip18A::PanneEmr() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = panne_emr;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangePanneEmr(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			panne_emr = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_STATUS);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Panne Accord *************
int CEquip18A::PanneAccord() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = panne_accord;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangePanneAccord(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			panne_accord = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_STATUS);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Reception de HF *************
int CEquip18A::HfRecu() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = HF_recu;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeHfRecu(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			HF_recu = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_STATUS);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// ROS *************
int CEquip18A::Ros() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = ros;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeRos(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			ros = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_STATUS);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Emission *************
int CEquip18A::Emission() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = emission;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeEmission(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			emission = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_STATUS);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Silence *************
int CEquip18A::Silence() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = silence;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeSilence(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			silence = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_STATUS);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Presence de BF chiffre *************
int CEquip18A::Chiffre() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = chiffre;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeChiffre(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			chiffre = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_STATUS);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Test en cours *************
int CEquip18A::TestEnCours() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = test_en_cours;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeTestEnCours(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			test_en_cours = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_STATUS);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Scan en cours *************
int CEquip18A::Scan() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = scan;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeScan(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			scan = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_STATUS);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Accord en cours *************
int CEquip18A::Accord() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = accord;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeAccord(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			accord = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_STATUS);
		}
		ChangeAccordMulti(0,0,genere_TS);		// Accord demandé == 0
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Resultat du test *************
int CEquip18A::Test() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = code_test;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip18A::ChangeTest(int valeur,BOOL genere_TS)
{
	int 	iResult = 0;

	if(valeur >=0 && valeur <= 15*1000 + 2*100 + 52*1)
	{
		EnterCriticalSection(&crit);
			code_test = valeur;
			// Icrémentation de la variable d'évoution IHM
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			status_evol = (status_evol+1) % (0xF+1);
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

int CEquip18A::MemoriseCanal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=1 && valeur <= 99)
	{
		EnterCriticalSection(&crit);
			carac_canal[valeur] = carac_canal[0];
			if(valeur<95)
				carac_canal[valeur].frequence_Em = carac_canal[valeur].frequence_Rec;

			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto18A*)proto)->ChangeCanalLecture(valeur);
			proto->AjouterTS(NULL,EMR_EXPLOITATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_NON_CONFORME;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}
