/* **************************************************************************
FICHIER :	Eqp_std.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquip_std
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\EqpStd.h"
#include "Comm\prot_Std.h"
#include "DlgStdHF.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_STANDHF[];
/* **************************************************************************
METHODE :		CEquipStd()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquipStd::CEquipStd(int idx):CEquip(idx)
{
	etat_incorrect	= 0;	// correct

	baa 			= 1;
	emet			= 1;
	recep			= 1;
	silence_radio 	= 0;	// pas de silence radio

	accorde			= 0;	// RLB	

	avarie 			= 0;	// pas d'avarie
	absence_tension	= 0;	// pas de défaut
	non_hissage		= 0;	// Hissage normal
	no_xmit			= 0;	// pas d'interdiction d'émettre

	local			 = 1;	// Local
	xmit_1			 = 1;	// emission
	xmit_2			 = 0;	// noxmit
	mat_1			 = 1;	// hissé
	mat_2			 = 0;	// non hissé
	temperature		 = 0;	//pas de défaut

}

/* **************************************************************************
METHODE :		~CEquipStd
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquipStd::~CEquipStd()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipStd::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProtoStd(ligne.format,this);

	if(ihm == NULL) ihm = new CDlgStandHF;
	ihm->Associe(this);
	ihm->Create(F1_IDD_STANDARD_HF,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_STANDHF);
}
/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipStd::Charge_Contexte(char *fichier)
{
	int 	i,iResult;
	char	cle[10];

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];


	iResult = Recup_fichier(fichier,contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation",iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P00=",ligne,TAILLE_MAX_LIGNE);
	if(strcmp(ligne+4,"STANDARD")!=0)
	if(iResult<0)
	{
		AjouterMessage("**** Erreur fichier non conforme à l'équipement",iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P01=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeEtatIncorrect(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P02=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeBaa(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P03=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeEmet(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P04=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeRecep(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P05=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeSilenceRadio(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P06=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAccorde(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P07=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAvarie(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P08=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAbsenceTension(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P09=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeNonHissage(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P10=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeNoXmit(atoi(ligne+4),FALSE);

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
BOOL CEquipStd::Sauve_Contexte(char *fichier)
{
	int 	i,iResult;

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];

	strcpy(contenu,"// Contexte d'exploitation d'un standard HF\r\n");
	strcat(contenu,"// ****************************************\r\n");

	strcpy(ligne,"P00=STANDARD\r\n");
	strcat(contenu,ligne);

	sprintf(ligne,"P01=%d\r\n",EtatIncorrect());
	strcat(contenu,ligne);

	sprintf(ligne,"P02=%d\r\n",Baa());
	strcat(contenu,ligne);

	sprintf(ligne,"P03=%d\r\n",Emet());
	strcat(contenu,ligne);

	sprintf(ligne,"P04=%d\r\n",Recep());
	strcat(contenu,ligne);

	sprintf(ligne,"P05=%d\r\n",SilenceRadio());
	strcat(contenu,ligne);

	sprintf(ligne,"P06=%d\r\n",Accorde());
	strcat(contenu,ligne);

	sprintf(ligne,"P07=%d\r\n",Avarie());
	strcat(contenu,ligne);

	sprintf(ligne,"P08=%d\r\n",AbsenceTension());
	strcat(contenu,ligne);

	sprintf(ligne,"P09=%d\r\n",NonHissage());
	strcat(contenu,ligne);

	sprintf(ligne,"P10=%d\r\n",NoXmit());
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
BOOL CEquipStd::Power()
{
	BOOL	activite;
	CEquip::Power();

	activite = Actif();
	if(activite)
	{
//		proto->AjouterTS("Initialisation",CDE_TEXTE_SEUL);
		proto->AjouterTS(NULL,STD_TEST);
		proto->AjouterTS(NULL,STD_LOCAL);
		proto->AjouterTS(NULL,STD_COMMUTATION);
		proto->AjouterTS(NULL,STD_XMIT_1);
		proto->AjouterTS(NULL,STD_XMIT_2);
		proto->AjouterTS(NULL,STD_MAT_1);
		proto->AjouterTS(NULL,STD_MAT_2);
		proto->AjouterTS(NULL,STD_SILENCE);
	}
	else
	{
//		proto->AjouterTS("Arret de l'équipement",CDE_TEXTE_SEUL);
	}
	return activite;
}

// Etat incorrect ******************************************
int CEquipStd::EtatIncorrect() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = etat_incorrect;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipStd::ChangeEtatIncorrect(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			etat_incorrect = iResult;

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

// Selection BAA ******************************************
int CEquipStd::Baa() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = baa;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipStd::ChangeBaa(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=1 && valeur <= 2)
	{
		EnterCriticalSection(&crit);
			baa = iResult;

			if(baa==1)
			{
				if(!(xmit_1 && mat_1))
					no_xmit=1;
				else
					no_xmit=0;
			}
			else
			{
				if(!(xmit_2 && mat_2))
					no_xmit=1;
				else
					no_xmit=0;
			}

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

// Selection Emetteur ******************************************
int CEquipStd::Emet() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = emet;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeEmet(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=1 && valeur <= 2)
	{
		EnterCriticalSection(&crit);
			emet = iResult;

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

// Selection Recepteur ******************************************
int CEquipStd::Recep() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = recep;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeRecep(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=1 && valeur <= 2)
	{
		EnterCriticalSection(&crit);
			recep = iResult;

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

// Silence Radio ******************************************
int CEquipStd::SilenceRadio() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = silence_radio;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeSilenceRadio(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			silence_radio = iResult;

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

// Reception accordée ******************************************
int CEquipStd::Accorde() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = accorde;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeAccorde(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			accorde = iResult;

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

// Avarie ******************************************
int CEquipStd::Avarie() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = avarie;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeAvarie(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur<=7)
	{
		EnterCriticalSection(&crit);
			avarie = iResult;

			if(avarie || absence_tension || non_hissage 
				|| no_xmit || temperature) etat_incorrect = 1;
			else etat_incorrect = 0;

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

// Absence 28 V ******************************************
int CEquipStd::AbsenceTension() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = absence_tension;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeAbsenceTension(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur<=1)
	{
		EnterCriticalSection(&crit);
			absence_tension = iResult;

			if(avarie || absence_tension || non_hissage 
				|| no_xmit || temperature) etat_incorrect = 1;
			else etat_incorrect = 0;

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

// Non Hissage du mat ******************************************
int CEquipStd::NonHissage() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = non_hissage;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeNonHissage(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur<=1)
	{
		EnterCriticalSection(&crit);
			non_hissage = iResult;

			if(avarie || absence_tension || non_hissage 
				|| no_xmit || temperature) etat_incorrect = 1;
			else etat_incorrect = 0;

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

// No Xmit ******************************************
int CEquipStd::NoXmit() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = no_xmit;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeNoXmit(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur<=1)
	{
		EnterCriticalSection(&crit);
			no_xmit = iResult;

			if(avarie || absence_tension || non_hissage 
				|| no_xmit || temperature) etat_incorrect = 1;
			else etat_incorrect = 0;

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

// Local/distant ******************************************
int CEquipStd::Local() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = local;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeLocal(int valeur, BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			local = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		iResult = valeur;

		if(genere_TS)
		{
			proto->AjouterTS(NULL,STD_LOCAL);
		}
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
		LeaveCriticalSection(&crit);

		iResult = ERR_NON_CONFORME;
	}

	return iResult;
}

// Emmission 1 ******************************************
int CEquipStd::Xmit_1() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = xmit_1;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeXmit_1(int valeur, BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			xmit_1 = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		iResult = valeur;
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
		LeaveCriticalSection(&crit);

		iResult = ERR_NON_CONFORME;
	}

	return iResult;
}

// Emmission 2 ******************************************
int CEquipStd::Xmit_2() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = xmit_2;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeXmit_2(int valeur, BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			xmit_2 = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		iResult = valeur;
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
		LeaveCriticalSection(&crit);

		iResult = ERR_NON_CONFORME;
	}

	return iResult;
}

// Hissage du mat 1 ******************************************
int CEquipStd::Mat_1() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = mat_1;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeMat_1(int valeur, BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			mat_1 = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		iResult = valeur;
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
		LeaveCriticalSection(&crit);

		iResult = ERR_NON_CONFORME;
	}
	return iResult;
}

// Hissage du mat 2 ******************************************
int CEquipStd::Mat_2() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = mat_2;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeMat_2(int valeur, BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			mat_2 = valeur;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		iResult = valeur;
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
		LeaveCriticalSection(&crit);

		iResult = ERR_NON_CONFORME;
	}
	return iResult;
}

// Defaut temperature ******************************************
int CEquipStd::Temperature() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = temperature;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipStd::ChangeTemperature(int valeur, BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur >=0 && valeur <=1)
	{
		EnterCriticalSection(&crit);
			temperature = valeur;

			if(avarie || absence_tension || non_hissage 
				|| no_xmit || temperature) etat_incorrect = 1;
			else etat_incorrect = 0;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		iResult = valeur;
	}
	else
	{
		EnterCriticalSection(&crit);
			evolution = (evolution+1) % PLAGE_EVOLUTION; // Force à rafraichir
		LeaveCriticalSection(&crit);

		iResult = ERR_NON_CONFORME;
	}
	return iResult;
}
