/* **************************************************************************
FICHIER :	Eqp_1241.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip1241
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\Eqp1241.h"
#include "Comm\p_1241.h"
#include "Dlg1241.h"

#include "Divers\Div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

const int	SEUIL_NIVEAU_HF 	= 25;

extern char glob_CONTEXT_RECHF[];
/* **************************************************************************
METHODE :		CEquip1241()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquip1241::CEquip1241(int idx):CEquip(idx)
{
	int 	i;
	
	l11 	= 	0;
	spin	=	0;

	for(i=0 ; i<100 ; i++)
	{
		carac_canal[i].mode_reception 	= 	0;
		carac_canal[i].attenuateur		=	0;
		carac_canal[i].filtre			=	0;
		carac_canal[i].cag 				=	0;
		carac_canal[i].squelch 			= 	0;
		carac_canal[i].sens_manip 		=	0;
		carac_canal[i].shift 			= 	0;
		carac_canal[i].frequence 		= 	10000; 	// 10 kHz
		carac_canal[i].bfo 				= 	1000; 	// 1 kHz
		carac_canal[i].gainHF 			= 	120;	//
		carac_canal[i].mesureur 		= 	55;
	}
	
	auto_mesureur 	= 	0;		// Variation automatique

	rejecteur 		= 	0;		// sans freq réjecteur
	freq_reject		=	1000;	// 1 kHz 


	cor_squelch		=   68;

	auto_centrage_F1	=	0;
	centrage_F1		=	055;

	canal 			= 	0;

	for (i=0; i<99 ; i++) veille[i]=0;
	for (i=0; i<3 ; i++) temps_maintien[i]=0;
	for (i=0; i<20 ; i++) frequence_balayage[i]=0;
	for (i=0; i<3 ; i++) vitesse_balayage[i]=0;

	test 			= 	0;
	info 			= 	0;		// Info non présence

	local 			= 1;		// Telecommande

}

/* **************************************************************************
METHODE :		~CEquip1241
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquip1241::~CEquip1241()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquip1241::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProtoRecHF(ligne.format,this);

	if(ihm == NULL) ihm = new CDlg1241;
	ihm->Associe(this);
	ihm->Create(F5_IDD_TRC1241_FF,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_RECHF);
}

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquip1241::Charge_Contexte(char *fichier)
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
	if(strcmp(ligne+4,"REC_1241_HF")!=0)
	if(iResult<0)
	{
		AjouterMessage("**** Erreur fichier non conforme à l'équipement",iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P01=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeModeRecep(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P02=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAttenuateur(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P03=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeFiltreFI(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P04=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeCag(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P05=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeSquelch(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P06=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeSensManip(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P07=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeShift(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P08=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeFrequence(0,atol(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P09=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeBfo(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P10=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAvecRejecteur(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P11=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeRejecteur(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P12=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeGainHF(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P13=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAutoMesureur(atoi(ligne+4));

	iResult = Extrait_ligne(contenu,"P14=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeMesureur(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P15=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeCorSquelch(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P16=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAutoCentrageF1(atoi(ligne+4));

	iResult = Extrait_ligne(contenu,"P17=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeCentrageF1(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P18=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeCanal(atoi(ligne+4),FALSE);
	
	iResult = Extrait_ligne(contenu,"P19=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeLocal(atoi(ligne+4),FALSE);

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
BOOL CEquip1241::Sauve_Contexte(char *fichier)
{
	int 	i,iResult;

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];

	strcpy(contenu,"// Contexte d'exploitation d'un récepteur HF\r\n");
	strcat(contenu,"// *****************************************\r\n");

	strcpy(ligne,"P00=REC_1241_HF\r\n");
	strcat(contenu,ligne);

	sprintf(ligne,"P01=%d\r\n",ModeRecep(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P02=%d\r\n",Attenuateur(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P03=%d\r\n",FiltreFI(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P04=%d\r\n",Cag(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P05=%d\r\n",Squelch(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P06=%d\r\n",SensManip(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P07=%d\r\n",Shift(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P08=%ld\r\n",Frequence(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P09=%d\r\n",Bfo(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P10=%d\r\n",AvecRejecteur());
	strcat(contenu,ligne);

	sprintf(ligne,"P11=%d\r\n",Rejecteur());
	strcat(contenu,ligne);

	sprintf(ligne,"P12=%d\r\n",GainHF(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P13=%d\r\n",AutoMesureur());
	strcat(contenu,ligne);

	sprintf(ligne,"P14=%d\r\n",Mesureur(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P15=%d\r\n",CorSquelch());
	strcat(contenu,ligne);

	sprintf(ligne,"P16=%d\r\n",CentrageF1());
	strcat(contenu,ligne);

	sprintf(ligne,"P17=%d\r\n",CentrageF1());
	strcat(contenu,ligne);

	sprintf(ligne,"P18=%d\r\n",0);
	strcat(contenu,ligne);
	
	sprintf(ligne,"P19=%d\r\n",Local());
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
BOOL CEquip1241::Power()
{
	BOOL	activite;
	CEquip::Power();

	activite = Actif();
	if(activite)
	{
//		proto->AjouterTS("Initialisation",CDE_TEXTE_SEUL);
		proto->AjouterTS(NULL,REC_1241_MODE_LOCAL);
		proto->AjouterTS(NULL,REC_1241_MODE_RECEP);
		proto->AjouterTS(NULL,REC_1241_OPTION_REC);
		proto->AjouterTS(NULL,REC_1241_FREQUENCE);
		proto->AjouterTS(NULL,REC_1241_MODE_RECEP);
		proto->AjouterTS(NULL,REC_1241_FILTRE_FI);
		proto->AjouterTS(NULL,REC_1241_ATTENUATEUR);
		proto->AjouterTS(NULL,REC_1241_CAG);
		proto->AjouterTS(NULL,REC_1241_REJECTEUR);
		proto->AjouterTS(NULL,REC_1241_SQUELCH);
		proto->AjouterTS(NULL,REC_1241_BFO);
		proto->AjouterTS(NULL,REC_1241_NIVEAU_HF);
		proto->AjouterTS(NULL,REC_1241_SEUIL_COR);
	}
	else
	{
//		proto->AjouterTS("Arret de l'équipement",CDE_TEXTE_SEUL);
	}
	return activite;

}

// Mode de reception *************
int CEquip1241::ModeRecep(int	num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].mode_reception;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip1241::ChangeModeRecep(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(valeur >=0 && valeur <=5)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].mode_reception = valeur;
			if(valeur>=2 && valeur <=4)		// A3J+/A3J-/A3B
				carac_canal[num_canal].filtre = carac_canal[num_canal].filtre/5 * 5;			// forcé à 0 ou 5

			if(valeur==1)					// A3
				carac_canal[num_canal].cag = carac_canal[num_canal].cag/2 * 2;			// forcé à 0 ou 2

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_1241_MODE_RECEP);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - carac_canal[num_canal].mode_reception; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Attenuateur *********************
int CEquip1241::Attenuateur(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].attenuateur;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeAttenuateur(int	num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(valeur >=0 && valeur <=2)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].attenuateur = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_1241_ATTENUATEUR);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - carac_canal[num_canal].attenuateur; // Ancienne valeur en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Filtres FI *******************
int CEquip1241::FiltreFI(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].filtre;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeFiltreFI(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;
	int		old_bp5;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur >=0 && valeur <=9)
	{
		old_bp5 = FiltreFI(num_canal) / 5;

		EnterCriticalSection(&crit);
			if(carac_canal[num_canal].mode_reception>=2 && 
						carac_canal[num_canal].mode_reception <=4)	// A3J+/A3J-/A3B
				valeur = valeur/5 * 5;					// forcé à 0 ou 5
			carac_canal[num_canal].filtre = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		iResult = valeur;

		if(genere_TS)
		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_1241_FILTRE_FI);
			if((valeur/5) != old_bp5) proto->AjouterTS(NULL,REC_1241_FREQUENCE);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - carac_canal[num_canal].filtre; // Ancienne valeur en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// CAG *********************
int CEquip1241::Cag(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].cag;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeCag(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur>=0 && valeur <= 3+L11())
	{
		EnterCriticalSection(&crit);
			if(carac_canal[num_canal].mode_reception==1)			// A3
				valeur = valeur/2 * 2;		// forcé à 0 ou 2
				carac_canal[num_canal].cag = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		iResult = valeur;

		if(genere_TS)
		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_1241_CAG);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - carac_canal[num_canal].cag; // Ancienne valeur en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Squelch *********************
int CEquip1241::Squelch(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].squelch;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeSquelch(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].squelch = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_1241_SQUELCH);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - carac_canal[num_canal].squelch; // Ancienne valeur en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}
// Sens de manipulation télégraphique *******************
int CEquip1241::SensManip(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].sens_manip;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeSensManip(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur>=0 && valeur <= 3)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].sens_manip = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_1241_SENS_MANIP);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - carac_canal[num_canal].sens_manip; // Ancienne valeur en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Shift ******************************************
int CEquip1241::Shift(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].shift;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeShift(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur>=0 && valeur <= 4)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].shift = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_1241_SHIFT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - carac_canal[num_canal].shift; // Ancienne valeur en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Frequence ******************************************
long CEquip1241::Frequence(int num_canal) const
{
	long		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].frequence;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

long CEquip1241::ChangeFrequence(int num_canal,long valeur,BOOL genere_TS)
{
	long	lResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur>=10000 && valeur <= 29999999)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].frequence = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_1241_FREQUENCE);
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

long CEquip1241::IncrementeFrequence(long valeur,BOOL genere_TS)
{
	EnterCriticalSection(&crit);
		if(carac_canal[0].frequence+valeur<10000) valeur = 10000;
		else
			if(carac_canal[0].frequence+valeur>29999999) valeur = 29999999;
			else valeur+=carac_canal[0].frequence;

		carac_canal[0].frequence = valeur;
		// Icrémentation de la variable d'évoution
		evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);

	if(genere_TS)
	{
			proto->AjouterTS(NULL,REC_1241_FREQUENCE);
	}
	return valeur;
}


// BFO ******************************************
int CEquip1241::Bfo(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].bfo;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

// *** Attention pour cette methode, le code erreur est -16000 + ancienne valeur BFO 
int CEquip1241::ChangeBfo(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur>=-7990 && valeur <= 7990)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].bfo = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_1241_BFO);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = -16000+carac_canal[num_canal].bfo;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}
// Rejecteur FI **********************************
int CEquip1241::AvecRejecteur() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = rejecteur;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeAvecRejecteur(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			rejecteur = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_1241_REJECTEUR);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = -rejecteur;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

int CEquip1241::Rejecteur() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = freq_reject;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

// *** Attention pour cette methode, le code erreur est -16000 + ancienne valeur reject 
int CEquip1241::ChangeRejecteur(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=-7990 && valeur <= 7990)
	{
		EnterCriticalSection(&crit);
			freq_reject = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_1241_REJECTEUR);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = -16000-freq_reject;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// GainHF ******************************************
int CEquip1241::GainHF(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].gainHF;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeGainHF(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur>=0 && valeur <= 255)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].gainHF = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_1241_NIVEAU_HF);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - carac_canal[num_canal].gainHF;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Mesureur de champs = Niveau HF reçu *********
int CEquip1241::AutoMesureur() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = auto_mesureur;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);


	return iResult;
}

int CEquip1241::ChangeAutoMesureur(int valeur)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			auto_mesureur = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

	}
	else iResult = -1;

	return iResult;
}

int CEquip1241::Mesureur(int num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].mesureur;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip1241::ChangeMesureur(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	if(valeur>=0 && valeur <= 108)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].mesureur = valeur;

			if(valeur > SEUIL_NIVEAU_HF)
			{
				if(!Info()) ChangeInfo(TRUE,TRUE);
			}
			else
				if(Info()) ChangeInfo(FALSE,TRUE);


			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

//		if(genere_TS)
//		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_1241_MESUREUR);
//		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - carac_canal[num_canal].mesureur;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// CorSquelch ******************************************
int CEquip1241::CorSquelch() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = cor_squelch;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeCorSquelch(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 108)
	{
		EnterCriticalSection(&crit);
			cor_squelch = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_1241_SEUIL_COR);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - cor_squelch;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Centrage F1 **************
int CEquip1241::AutoCentrageF1() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = auto_centrage_F1;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);


	return iResult;
}

int CEquip1241::ChangeAutoCentrageF1(int valeur)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			auto_centrage_F1 = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

	}
	else iResult = -1;

	return iResult;
}

int CEquip1241::CentrageF1() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = centrage_F1;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip1241::ChangeCentrageF1(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 077)
	{
		EnterCriticalSection(&crit);
			centrage_F1 = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

//		if(genere_TS)
//		{
			proto->AjouterTS(NULL,REC_1241_CENTRAGE_F1);
//		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = - centrage_F1;
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Positionnement de canal***************************************
int CEquip1241::Canal() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = canal;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeCanal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

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
			proto->AjouterTS(NULL,REC_1241_CANAL_POSI);
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
int CEquip1241::MemoriseCanal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=1 && valeur <= 99)
	{
		EnterCriticalSection(&crit);
			carac_canal[valeur]=carac_canal[0];

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			((CProtoRecHF*)proto)->ChangeCanalLecture(valeur);
			proto->AjouterTS(NULL,REC_1241_CANAL_LECT);
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
// Veille ***************************************
int CEquip1241::Veille(int pos) const
{
	int		iResult;

	if(pos<=1 || pos >= 99) return -1;		// hors limitte

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = veille[pos-1];
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

// Acces par TC uniquement
int CEquip1241::ChangeVeille(int pos,int valeur)
{
	int 	iResult = valeur;

	if(pos<=1 || pos >= 99) return ERR_NON_CONFORME;	// hors limitte

	if(valeur>=0 && valeur <= 99)
	{
		EnterCriticalSection(&crit);
			veille[pos-1] = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
	}
	else
		iResult = ERR_NON_CONFORME;
	return iResult;
}

// Temps de maintien ******************************************
int CEquip1241::TempsMaintien(int degre) const
{
	int		iResult;

	if(degre<0 || degre > 2) return ERR_NON_CONFORME;	// hors limitte

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = temps_maintien[degre];
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeTempsMaintien(int degre,int valeur)
{
	int 	iResult = valeur;

	if(degre<0 || degre > 2) return ERR_NON_CONFORME;	// hors limitte

	if(valeur>=1 && valeur <= 19)
	{
		EnterCriticalSection(&crit);
			temps_maintien[degre] = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

	}
	else
		iResult = ERR_NON_CONFORME;

	return iResult;
}

// Bande de frequence de balayage ***************************
long CEquip1241::FrequenceBalayage(int pos) const
{
	long		lResult;

	if(pos<=1 || pos >= 20) return -1;		// hors limitte

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		lResult = frequence_balayage[pos-1];
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return lResult;
}

// Acces par TC uniquement
long CEquip1241::ChangeFrequenceBalayage(int pos,long valeur)
{
	long 	lResult = valeur;

	if(pos<=1 || pos >= 99) return ERR_NON_CONFORME;	// hors limitte

	if((valeur>=10000 && valeur <= 29999999) || valeur == 0)
	{
		EnterCriticalSection(&crit);
			frequence_balayage[pos-1] = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
	}
	else
		return ERR_NON_CONFORME;

	return 0;
}

// Vitesse de balayage ******************************************
int CEquip1241::VitesseBalayage(int degre) const
{
	int		iResult;

	if(degre<0 || degre > 2) return ERR_NON_CONFORME;	// hors limitte

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = vitesse_balayage[degre];
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeVitesseBalayage(int degre,int valeur)
{
	int 	iResult = valeur;

	if(degre<0 || degre > 2) return ERR_NON_CONFORME;	// hors limitte

	if(valeur>=1 && valeur <= 19)
	{
		EnterCriticalSection(&crit);
			vitesse_balayage[degre] = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

	}
	else
		iResult = ERR_NON_CONFORME;

	return iResult;
}

// Test ******************************************
int CEquip1241::Test() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = test;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeTest(int valeur,BOOL genere_TS)
{
	int 	iResult = 0;

	if(valeur>=0) 	iResult = 0;
	if(valeur>=10)	iResult = 10;
	if(valeur>=20) 	iResult = 20;
	if(valeur>=25) 	iResult = 25;
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
	if(valeur>=75) 	iResult = 75;
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
		proto->AjouterTS(NULL,REC_1241_TEST);
	}

	return iResult;
}

// Presence infos ******************************************
int CEquip1241::Info() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = info;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeInfo(int valeur,BOOL genere_TS)
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
			proto->AjouterTS(NULL,REC_1241_INFO);
		}
	}

	return iResult;
}

// Local ******************************************
int CEquip1241::Local() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = local;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquip1241::ChangeLocal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			local = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_1241_MODE_LOCAL);

			if(valeur == 1)		// Mode telecommande
			{
				proto->AjouterTS(NULL,REC_1241_MODE_RECEP);
				proto->AjouterTS(NULL,REC_1241_OPTION_REC);
				proto->AjouterTS(NULL,REC_1241_FREQUENCE);
				proto->AjouterTS(NULL,REC_1241_MODE_RECEP);
				proto->AjouterTS(NULL,REC_1241_FILTRE_FI);
				proto->AjouterTS(NULL,REC_1241_ATTENUATEUR);
				proto->AjouterTS(NULL,REC_1241_CAG);
				proto->AjouterTS(NULL,REC_1241_REJECTEUR);
				proto->AjouterTS(NULL,REC_1241_SQUELCH);
				proto->AjouterTS(NULL,REC_1241_BFO);
				proto->AjouterTS(NULL,REC_1241_NIVEAU_HF);
				proto->AjouterTS(NULL,REC_1241_SEUIL_COR);
			}
		}
	}
	else iResult = ERR_NON_CONFORME;

	return iResult;
}

// mode L11
int CEquip1241::L11() const
{
	return 0;
}

// mode SPIN
int CEquip1241::Spin() const
{
	return 0;
}
int CEquip1241::ChangeSpin(int valeur,BOOL genere_TS)
{
	return 0;
}
