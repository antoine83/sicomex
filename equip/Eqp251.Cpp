/* **************************************************************************
FICHIER :	Eqp_251.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip251
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\Eqp251.h"
#include "Comm\p_251.h"
#include "Dlg251.h"

#include "Divers\Div_fic.h"

const int	TEMPO_INIT_T1 			= 4;		// en,tre 2 et 6s
const int	TEMPO_INIT_T2 			= 14;		

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_REC_251[];


/* **************************************************************************
METHODE :		CEquip251()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquip251::CEquip251(int idx):CEquip(idx)
{
	int 	i,j;
	
	phase_init = 1;
	time(&duree_ini);

	telecommande = 0;			// Mode console
	trafic = 0;			// hors trafic
	local = 1;					// distance

	canal = 0;				// 0 à 99, 0= canal d'exploitation

	for(i=0 ; i<100 ; i++)
	{
		carac_canal[i].frequence = 10000;			// 10000 Hz
		carac_canal[i].bfo = 0;
		carac_canal[i].attenuation = 0;
		carac_canal[i].cag = 0;
		carac_canal[i].limiteur = 0;

		carac_canal[i].mode_reception = 7; // MSK 4
		
		for(j=0 ; j<REC_251_NB_VOIE ; j++)
		{
			carac_canal[i].voie_active[j] = 1; 	// toutes active en MSK4
			carac_canal[i].interfaces[j] = 1;	// Valor
			carac_canal[i].polarite[j] = 0;
		}

	}
	
	etat_test = 0;			// Fin de test
	auto_alarme = 0;			// 0,1
	defaut_0 = 0;
	defaut_1 = 0;
	defaut_2 = 0;
	defaut_3 = 0;

	q_bit_mini = 0;		// 0 à 127
	auto_mini = 0;
	q_bit_maxi = 0;		// 0 à 127
	auto_maxi = 0;
	
	etat_synchro = 0;				// synchro acquise

	auto_fibo = 0;
	auto_peigne = 0;
	peigne = 0;
	vitesse_recherche = 0; // Vitesse lente
	for(i=0 ; i<REC_251_NB_VOIE ; i++)
	{
		fibo[i] = 0;		// 0 à 100
		synchro_trame[i] = 6;		// Synchronisation
	}
	
}

/* **************************************************************************
METHODE :		~CEquip251
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquip251::~CEquip251()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquip251::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProto251(ligne.format,this);

	if(ihm == NULL) ihm = new CDlg251;
	ihm->Associe(this);
	ihm->Create(F9_IDD_TRC251,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_REC_251);
}

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquip251::Charge_Contexte(char *fichier)
{
	int 	i,iResult;

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];
	char	cle[10];

	int		tab_val[REC_251_NB_VOIE];

	iResult = Recup_fichier(fichier,contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation",iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P00=",ligne,TAILLE_MAX_LIGNE);
	if(strcmp(ligne+4,"REC_251_HF")!=0)
	if(iResult<0)
	{
		AjouterMessage("**** Erreur fichier non conforme à l'équipement",iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P01=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeTelecommande(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P02=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeTrafic(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P03=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeLocal(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P04=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeCanal(atoi(ligne+4),FALSE);
	
	iResult = Extrait_ligne(contenu,"P05=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeFrequence(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P06=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeBfo(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P07=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAttenuation(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P08=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeCag(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P09=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeLimiteur(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P10=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeModeRecep(0,atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P11=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
	{
		sscanf(ligne+4,"%d %d %d %d",&tab_val[0],&tab_val[1],&tab_val[2],&tab_val[3]);
		ChangeInterface(0,tab_val,FALSE);
	}

	iResult = Extrait_ligne(contenu,"P12=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
	{
		sscanf(ligne+4,"%d %d %d %d",&tab_val[0],&tab_val[1],&tab_val[2],&tab_val[3]);
		ChangePolarite(0,tab_val,FALSE);
	}

	iResult = Extrait_ligne(contenu,"P13=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeEtatTest(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P14=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAutoAlarme(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P15=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeDefaut(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P16=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeDefautCarte1(atoi(ligne+4),FALSE);
	
	iResult = Extrait_ligne(contenu,"P17=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeDefautCarte2(atoi(ligne+4),FALSE);
	
	iResult = Extrait_ligne(contenu,"P18=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeDefautCarte3(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P19=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeQBitMini(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P20=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAutoMini(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P21=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeQBitMaxi(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P22=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAutoMaxi(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P23=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeEtatSynchro(atoi(ligne+4),FALSE);
	
	iResult = Extrait_ligne(contenu,"P24=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
	{
		sscanf(ligne+4,"%d %d %d %d",&tab_val[0],&tab_val[1],&tab_val[2],&tab_val[3]);
		ChangeFibo(tab_val,FALSE);
	}

	iResult = Extrait_ligne(contenu,"P25=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAutoFibo(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P26=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangePeigne(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P27=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAutoPeigne(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P28=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
	{
		sscanf(ligne+4,"%d %d %d %d",&tab_val[0],&tab_val[1],&tab_val[2],&tab_val[3]);
		ChangeSynchroTrame(tab_val,FALSE);
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
BOOL CEquip251::Sauve_Contexte(char *fichier)
{
	int 	i,iResult;
	int		tab_val[REC_251_NB_VOIE];

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];

	strcpy(contenu,"// Contexte d'exploitation d'un récepteur HF\r\n");
	strcat(contenu,"// *****************************************\r\n");

	strcpy(ligne,"P00=REC_251_HF\r\n");
	strcat(contenu,ligne);

	sprintf(ligne,"P01=%d\r\n",0);		// Force le mode console
	strcat(contenu,ligne);
	
	sprintf(ligne,"P02=%d\r\n",Trafic());
	strcat(contenu,ligne);

	sprintf(ligne,"P03=%d\r\n",Local());
	strcat(contenu,ligne);

	sprintf(ligne,"P04=%d\r\n",Canal());
	strcat(contenu,ligne);

	sprintf(ligne,"P05=%d\r\n",Frequence(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P06=%d\r\n",Bfo(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P07=%d\r\n",Attenuation(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P08=%d\r\n",Cag(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P09=%d\r\n",Limiteur(0));
	strcat(contenu,ligne);

	sprintf(ligne,"P10=%d\r\n",ModeRecep(0));
	strcat(contenu,ligne);

	Interface(0,tab_val);
	sprintf(ligne,"P11=%d %d %d %d\r\n",tab_val[0],tab_val[1],tab_val[2],tab_val[3]);
	strcat(contenu,ligne);

	Polarite(0,tab_val);
	sprintf(ligne,"P12=%d %d %d %d\r\n",tab_val[0],tab_val[1],tab_val[2],tab_val[3]);
	strcat(contenu,ligne);

	sprintf(ligne,"P13=%d\r\n",EtatTest());
	strcat(contenu,ligne);

	sprintf(ligne,"P14=%d\r\n",AutoAlarme());
	strcat(contenu,ligne);

	sprintf(ligne,"P15=%d\r\n",Defaut());
	strcat(contenu,ligne);

	sprintf(ligne,"P16=%d\r\n",DefautCarte1());
	strcat(contenu,ligne);
	sprintf(ligne,"P17=%d\r\n",DefautCarte2());
	strcat(contenu,ligne);
	sprintf(ligne,"P18=%d\r\n",DefautCarte3());
	strcat(contenu,ligne);

	sprintf(ligne,"P19=%d\r\n",QBitMini());
	strcat(contenu,ligne);
	sprintf(ligne,"P20=%d\r\n",AutoMini());
	strcat(contenu,ligne);

	sprintf(ligne,"P21=%d\r\n",QBitMaxi());
	strcat(contenu,ligne);
	sprintf(ligne,"P22=%d\r\n",AutoMaxi());
	strcat(contenu,ligne);
	
	sprintf(ligne,"P23=%d\r\n",EtatSynchro());
	strcat(contenu,ligne);

	Fibo(tab_val);
	sprintf(ligne,"P24=%d %d %d %d\r\n",tab_val[0],tab_val[1],tab_val[2],tab_val[3]);
	strcat(contenu,ligne);

	sprintf(ligne,"P25=%d\r\n",AutoFibo());
	strcat(contenu,ligne);

	sprintf(ligne,"P26=%d\r\n",Peigne());
	strcat(contenu,ligne);

	sprintf(ligne,"P27=%d\r\n",AutoPeigne());
	strcat(contenu,ligne);

	SynchroTrame(tab_val);
	sprintf(ligne,"P28=%d %d %d %d\r\n",tab_val[0],tab_val[1],tab_val[2],tab_val[3]);
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
BOOL CEquip251::Power()
{
	int		i;
	BOOL	activite;
	char	buf[80];

	CEquip::Power();

	activite = Actif();
	if(activite)
	{
		EnterCriticalSection(&crit);
			phase_init = 1;
			time(&duree_ini);

			telecommande = 0;			// Mode console

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		srand( (unsigned)time( NULL ) );

		for(i=0 ; i<30 ; i++)	// Attention table limitte à 100 cde
		{
			sprintf(buf,"[H[%d;%d] %3.3d",rand()%24,rand()%40,rand()%999);
			proto->AjouterTS(buf,CDE_TEXTE_SEUL);
			proto->AjouterTS(buf,CDE_TEMPO_DIV_10);
		}
		proto->AjouterTS(NULL,CDE_PURGE_PORT);
		proto->AjouterTS(NULL,REC_251_ENQ);
	}
	else
	{
//		proto->AjouterTS("Arret de l'équipement",CDE_TEXTE_SEUL);
	}
	return activite;

}

//	FinPhaseInit *************************
int CEquip251::FinPhaseInit()
{
	time_t	t;
	if((time(&t) < duree_ini + TEMPO_INIT_T1) && phase_init) 
		return FALSE;
	if(phase_init)
	{
		phase_init = FALSE;
	}

	return TRUE;
	
}

// Type liaison telecommande *************
int CEquip251::Telecommande() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = telecommande;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeTelecommande(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			telecommande = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_MODE_LOCAL);
			proto->AjouterTS(NULL,REC_251_CONFIG_OP);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Hors ou en Trafic *************
int CEquip251::Trafic() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = trafic;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeTrafic(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;
	int		tab_voie[REC_251_NB_VOIE];

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			trafic = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_TRAFIC);

			VoieActive(0,tab_voie);

			proto->AjouterTS(NULL,REC_251_SYNCHRONISATION_BIT);

			if(tab_voie[0])
				proto->AjouterTS(NULL,REC_251_SYNCHRONISATION_TRAME1);
			if(tab_voie[1])
				proto->AjouterTS(NULL,REC_251_SYNCHRONISATION_TRAME2);
			if(tab_voie[2])
				proto->AjouterTS(NULL,REC_251_SYNCHRONISATION_TRAME3);
			if(tab_voie[3])
				proto->AjouterTS(NULL,REC_251_SYNCHRONISATION_TRAME4);

			proto->AjouterTS(NULL,REC_251_QUALITE_BIT);

			if(tab_voie[0])
				proto->AjouterTS(NULL,REC_251_NOTE_FIBO1);
			if(tab_voie[1])
				proto->AjouterTS(NULL,REC_251_NOTE_FIBO2);
			if(tab_voie[2])
				proto->AjouterTS(NULL,REC_251_NOTE_FIBO3);
			if(tab_voie[3])
				proto->AjouterTS(NULL,REC_251_NOTE_FIBO4);

			proto->AjouterTS(NULL,REC_251_NUM_PEIGNE);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Local/distance *************
int CEquip251::Local() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = local;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeLocal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			local = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_MODE_LOCAL);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Canal *************
int CEquip251::Canal() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = canal;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeCanal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=100)
	{
		EnterCriticalSection(&crit);
			canal = valeur;
			carac_canal[0] = carac_canal[valeur];

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_ENTREE_CANAL);
			proto->AjouterTS(NULL,REC_251_FREQUENCE_CANAL);
			proto->AjouterTS(NULL,REC_251_FREQ_BFO_CANAL);
			proto->AjouterTS(NULL,REC_251_LIMITEUR_CANAL);
			proto->AjouterTS(NULL,REC_251_CAG);
			proto->AjouterTS(NULL,REC_251_ATTENUATION_CANAL);
			proto->AjouterTS(NULL,REC_251_MODUL_INTERF_CANAL);
			proto->AjouterTS(NULL,REC_251_POLARITE_CANAL);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}
int CEquip251::MemoriseCanal(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=1 && valeur <= 100)
	{
		EnterCriticalSection(&crit);
			carac_canal[valeur] = carac_canal[0];
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto251*)proto)->ChangeCanalLecture(valeur);
			proto->AjouterTS(NULL,REC_251_STOCKAGE_CANAL);
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


// Mode de reception *************
int CEquip251::ModeRecep(int	num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].mode_reception;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeModeRecep(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(valeur >=0 && valeur <=9)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].mode_reception = valeur;
			if(valeur==7)		// MSK4
			{
				carac_canal[num_canal].voie_active[0] = 1;
				carac_canal[num_canal].voie_active[1] = 1;
				carac_canal[num_canal].voie_active[2] = 1;
				carac_canal[num_canal].voie_active[3] = 1;
			}

			if(valeur==6)		// MSK2
			{
				carac_canal[num_canal].voie_active[0] = 1;
				carac_canal[num_canal].voie_active[1] = 1;
				carac_canal[num_canal].voie_active[2] = 0;
				carac_canal[num_canal].voie_active[3] = 0;
			}

			if((valeur>=2 && valeur<=5) || valeur==9)	// MSK1 | F1 | CPFSK
			{
				carac_canal[num_canal].voie_active[0] = 0;
				carac_canal[num_canal].voie_active[1] = 0;
				carac_canal[num_canal].voie_active[2] = 0;
				carac_canal[num_canal].voie_active[3] = 1;
			}

			if(valeur<2 || valeur==8 )		// A1 ou Ext
			{
				carac_canal[num_canal].voie_active[0] = 0;
				carac_canal[num_canal].voie_active[1] = 0;
				carac_canal[num_canal].voie_active[2] = 0;
				carac_canal[num_canal].voie_active[3] = 0;
			}

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto251*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_251_LIMITTEUR);
			proto->AjouterTS(NULL,REC_251_MODE_INTERFACE);
			proto->AjouterTS(NULL,REC_251_POLARITE);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Frequence antenne *************
int CEquip251::Frequence(int	num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].frequence;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeFrequence(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(valeur >=10000 && valeur <=99999)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].frequence = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto251*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_251_FREQUENCE);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Frequence Bfo *************
int CEquip251::Bfo(int	num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].bfo;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeBfo(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(valeur >=0 && valeur <=7990)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].bfo = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto251*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_251_FREQ_BFO);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Attenuation *************
int CEquip251::Attenuation(int	num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].attenuation;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeAttenuation(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(valeur >=0 && valeur <=2)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].attenuation = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto251*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_251_ATTENUATION);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Cag *************
int CEquip251::Cag(int	num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].cag;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeCag(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].cag = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
//			((CProto251*)proto)->ChangeCanalLecture(num_canal);
//			proto->AjouterTS(NULL,REC_251_CAG);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Limiteur *************
int CEquip251::Limiteur(int	num_canal) const
{
	int		iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = carac_canal[num_canal].limiteur;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeLimiteur(int num_canal,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			carac_canal[num_canal].limiteur = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto251*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_251_LIMITTEUR);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Activite des voies  *************
int CEquip251::VoieActive(int	num_canal,int *etat) const
{
	int		i,iResult = NULL;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		for(i=0 ; i<REC_251_NB_VOIE ; i++)
		{
			etat[i] = carac_canal[num_canal].voie_active[i];
		}
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

// Valor/jason  *************
int CEquip251::Interface(int	num_canal,int *etat) const
{
	int		i,iResult = NULL;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		for(i=0 ; i<REC_251_NB_VOIE ; i++)
		{
			etat[i] = carac_canal[num_canal].interfaces[i];
		}
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeInterface(int num_canal,int *valeur,BOOL genere_TS)
{
	int 	i,iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(valeur[0] >=0 && valeur[0] <=1 && valeur[1] >=0 && valeur[1] <=1
		&& valeur[2] >=0 && valeur[2] <=1 && valeur[3] >=0 && valeur[3] <=1)
	{
		EnterCriticalSection(&crit);
			for(i=1 ; i<REC_251_NB_VOIE ; i++)
			{
				carac_canal[num_canal].interfaces[i] = valeur[i];
			}

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto251*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_251_MODE_INTERFACE);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Polarite *************
int CEquip251::Polarite(int	num_canal,int *etat) const
{
	int		i,iResult = NULL;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		for(i=0 ; i<REC_251_NB_VOIE ; i++)
		{
			etat[i] = carac_canal[num_canal].polarite[i];
		}
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangePolarite(int num_canal,int *valeur,BOOL genere_TS)
{
	int 	i,iResult;

	if(num_canal<0 || num_canal>99) return ERR_CDE_INCONNUE;
	if(valeur[0] >=0 && valeur[0] <=1 && valeur[1] >=0 && valeur[1] <=1
		&& valeur[2] >=0 && valeur[2] <=1 && valeur[3] >=0 && valeur[3] <=1)
	{
		EnterCriticalSection(&crit);
			for(i=0 ; i<REC_251_NB_VOIE ; i++)
			{
				carac_canal[num_canal].polarite[i] = valeur[i];
			}

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			((CProto251*)proto)->ChangeCanalLecture(num_canal);
			proto->AjouterTS(NULL,REC_251_POLARITE);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Etat du Test *************
int CEquip251::EtatTest() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = etat_test;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeEtatTest(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=2)
	{
		EnterCriticalSection(&crit);
			etat_test = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_ETAT_TEST);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Auto alarme *************
int CEquip251::AutoAlarme() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = auto_alarme;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeAutoAlarme(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			auto_alarme = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_DEFAUT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Defaut *************
int CEquip251::Defaut() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = defaut_0;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeDefaut(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=99)
	{
		EnterCriticalSection(&crit);
			defaut_0 = valeur;
			if(valeur) auto_alarme=1;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_DEFAUT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// DefautCarte1 *************
int CEquip251::DefautCarte1() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = defaut_1;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeDefautCarte1(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			defaut_1 = valeur;
			if(valeur) auto_alarme=1;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_DEFAUT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// DefautCarte2 *************
int CEquip251::DefautCarte2() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = defaut_2;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeDefautCarte2(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			defaut_2 = valeur;
			if(valeur) auto_alarme=1;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_DEFAUT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// DefautCarte3 *************
int CEquip251::DefautCarte3() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = defaut_3;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeDefautCarte3(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			defaut_3 = valeur;
			if(valeur) auto_alarme=1;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_DEFAUT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Qualite de bit mini *************
int CEquip251::QBitMini() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = q_bit_mini;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeQBitMini(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=127)
	{
		EnterCriticalSection(&crit);
			q_bit_mini = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_QUALITE_BIT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Auto mini *************
int CEquip251::AutoMini() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = auto_mini;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeAutoMini(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			auto_mini = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
//			proto->AjouterTS(NULL,REC_251_DEFAUT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Qualite de bit maxi *************
int CEquip251::QBitMaxi() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = q_bit_maxi;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeQBitMaxi(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=127)
	{
		EnterCriticalSection(&crit);
			q_bit_maxi = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_QUALITE_BIT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Auto maxi *************
int CEquip251::AutoMaxi() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = auto_maxi;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeAutoMaxi(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			auto_maxi = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
//			proto->AjouterTS(NULL,REC_251_DEFAUT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Etat synchro *************
int CEquip251::EtatSynchro() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = etat_synchro;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeEtatSynchro(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=2)
	{
		EnterCriticalSection(&crit);
			etat_synchro = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_SYNCHRONISATION_BIT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Note FIBO *************
int CEquip251::Fibo(int *etat) const
{
	int		i,iResult = NULL;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		for(i=0 ; i<REC_251_NB_VOIE ; i++)
		{
			etat[i] = fibo[i];
		}
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeFibo(int *valeur,BOOL genere_TS)
{
	int 	i,iResult;
	int		tab_voie[REC_251_NB_VOIE];

	if(valeur[0] >=0 && valeur[0] <=100 && valeur[1] >=0 && valeur[1] <=100
		&& valeur[2] >=0 && valeur[2] <=100 && valeur[3] >=0 && valeur[3] <=100)
	{
		EnterCriticalSection(&crit);
			for(i=0 ; i<REC_251_NB_VOIE ; i++)
			{
				fibo[i] = valeur[i];
			}

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		VoieActive(0,tab_voie);
		if(genere_TS)
		{
			if(tab_voie[0])
				proto->AjouterTS(NULL,REC_251_NOTE_FIBO1);
			if(tab_voie[1])
				proto->AjouterTS(NULL,REC_251_NOTE_FIBO2);
			if(tab_voie[2])
				proto->AjouterTS(NULL,REC_251_NOTE_FIBO3);
			if(tab_voie[3])
				proto->AjouterTS(NULL,REC_251_NOTE_FIBO4);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Auto fibo *************
int CEquip251::AutoFibo() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = auto_fibo;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeAutoFibo(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			auto_fibo = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
//			proto->AjouterTS(NULL,REC_251_DEFAUT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// N° Peigne *************
int CEquip251::Peigne() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
			iResult = peigne;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangePeigne(int valeur,BOOL genere_TS)
{
	int 	iResult;

	if(valeur >=0 && valeur <=15)
	{
		EnterCriticalSection(&crit);
			peigne = valeur;
			vitesse_recherche = (valeur>REC_251_SEUIL_VITESSE);

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,REC_251_NUM_PEIGNE);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Auto fibo *************
int CEquip251::AutoPeigne() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = auto_peigne;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeAutoPeigne(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			auto_peigne = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
//			proto->AjouterTS(NULL,REC_251_DEFAUT);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; 
		LeaveCriticalSection(&crit);
	}

	return iResult;
}

// Vitesse de recherche synchro *************
int CEquip251::Vitesse() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
			iResult = vitesse_recherche;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

// Synchro trame *************
int CEquip251::SynchroTrame(int *etat) const
{
	int		i,iResult = NULL;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		for(i=0 ; i<REC_251_NB_VOIE ; i++)
		{
			etat[i] = synchro_trame[i];
		}
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquip251::ChangeSynchroTrame(int *valeur,BOOL genere_TS)
{
	int 	i,iResult;
	int		tab_voie[REC_251_NB_VOIE];


	if(valeur[0] >=0 && valeur[0] <=6 && valeur[1] >=0 && valeur[1] <=6
		&& valeur[2] >=0 && valeur[2] <=6 && valeur[3] >=0 && valeur[3] <=6)
	{
		EnterCriticalSection(&crit);
			for(i=0 ; i<REC_251_NB_VOIE ; i++)
			{
				synchro_trame[i] = valeur[i];
			}

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

		VoieActive(0,tab_voie);

		if(genere_TS)
		{
			if(tab_voie[0])
				proto->AjouterTS(NULL,REC_251_SYNCHRONISATION_TRAME1);
			if(tab_voie[1])
				proto->AjouterTS(NULL,REC_251_SYNCHRONISATION_TRAME2);
			if(tab_voie[2])
				proto->AjouterTS(NULL,REC_251_SYNCHRONISATION_TRAME3);
			if(tab_voie[3])
				proto->AjouterTS(NULL,REC_251_SYNCHRONISATION_TRAME4);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
			iResult = ERR_CDE_INCONNUE; // Ancien mode en code erreur
		LeaveCriticalSection(&crit);
	}

	return iResult;
}
