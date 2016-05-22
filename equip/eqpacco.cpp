/* **************************************************************************
FICHIER :	Eqp_Acco.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CEquipAccord
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\EqpAcco.h"
#include "Comm\prot_Acc.h"
#include "DlgAccor.h"
#include "Divers\div_fic.h"
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm; 

extern char glob_CONTEXT_ACCORD[];
/* **************************************************************************
METHODE :		CEquipAccord()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquipAccord::CEquipAccord(int idx):CEquip(idx)
{	
	int		i;
	echo 		= 0;		// pas d'echo
	manuel 		= 0;		// Mode auto
	no_xmit		= 0;		// Pas d'interdiction d'emettre

	selecte_alarme = 0;
	for(i=0 ; i<100 ; i++)
		alarme[i] = 0;

	mode 		= 2; 		// etat indetermine

	frequence 	= 0;

	operation 	= OP_IDLE;

	accord		= 3;		// Type d'accord inconnu

	auto_induc	= 0;
	inductance 	= 999;		// Inconnue

	auto_capa	= 0;
	capacite 	= 999;		// Inconnue

	auto_tos	= 0;
	tos			= 0;

	etat		= 0;

	strcpy(chaine[0],"01552665601224554545");
	strcpy(chaine[1],"                    ");
	strcpy(chaine[2],"                    ");
	strcpy(chaine[3],"                    ");
	strcpy(chaine[4],"                    ");

}

/* **************************************************************************
METHODE :		~CEquipAccord
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquipAccord::~CEquipAccord()
{
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipAccord::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProtoAccord(ligne.format,this);

	if(ihm == NULL) ihm = new CDlgAccord;
	ihm->Associe(this);
	ihm->Create(F2_IDD_ACCORD_ANTENNE,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_ACCORD);
}

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipAccord::Charge_Contexte(char *fichier)
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
	if(strcmp(ligne+4,"ACCORD")!=0)
	if(iResult<0)
	{
		AjouterMessage("**** Erreur fichier non conforme à l'équipement",iResult);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P01=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeEcho(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P02=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeManuel(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P03=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeNoXmit(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P04=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeSelecteAlarme(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P05=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeMode(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P06=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeFrequence(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P07=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeOperation(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P08=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAccord(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P09=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAutoInduc(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P10=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeInductance(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P11=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAutoCapa(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P12=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeCapacite(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P13=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeAutoTos(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P14=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeTos(atoi(ligne+4),FALSE);

	iResult = Extrait_ligne(contenu,"P15=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeEtat(atoi(ligne+4),FALSE);

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
BOOL CEquipAccord::Sauve_Contexte(char *fichier)
{
	int 	i,iResult;

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];

	strcpy(contenu,"// Contexte d'exploitation de la boîte d'accord antenne\r\n");
	strcat(contenu,"// ****************************************************\r\n");

	strcpy(ligne,"P00=ACCORD\r\n");
	strcat(contenu,ligne);

	sprintf(ligne,"P01=%d\r\n",Echo());
	strcat(contenu,ligne);

	sprintf(ligne,"P02=%d\r\n",Manuel());
	strcat(contenu,ligne);

	sprintf(ligne,"P03=%d\r\n",NoXmit());
	strcat(contenu,ligne);

	sprintf(ligne,"P04=%d\r\n",SelecteAlarme());
	strcat(contenu,ligne);

	sprintf(ligne,"P05=%d\r\n",Mode());
	strcat(contenu,ligne);

	sprintf(ligne,"P06=%d\r\n",Frequence());
	strcat(contenu,ligne);

	sprintf(ligne,"P07=%d\r\n",Operation());
	strcat(contenu,ligne);

	sprintf(ligne,"P08=%d\r\n",Accord());
	strcat(contenu,ligne);

	sprintf(ligne,"P09=%d\r\n",AutoInduc());
	strcat(contenu,ligne);

	sprintf(ligne,"P10=%d\r\n",Inductance());
	strcat(contenu,ligne);

	sprintf(ligne,"P11=%d\r\n",AutoCapa());
	strcat(contenu,ligne);

	sprintf(ligne,"P12=%d\r\n",Capacite());
	strcat(contenu,ligne);

	sprintf(ligne,"P13=%d\r\n",AutoTos());
	strcat(contenu,ligne);

	sprintf(ligne,"P14=%d\r\n",Tos());
	strcat(contenu,ligne);

	sprintf(ligne,"P15=%d\r\n",Etat());
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
BOOL CEquipAccord::Power()
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

// Mode Manuel ******************************************
int CEquipAccord::Manuel() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = manuel;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeManuel(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			manuel = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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

// Echo ******************************************
int CEquipAccord::Echo() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = echo;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeEcho(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			echo = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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


// Alarme ******************************************
int CEquipAccord::SelecteAlarme() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = selecte_alarme;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
int CEquipAccord::ChangeSelecteAlarme(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 99)
	{
		EnterCriticalSection(&crit);
			selecte_alarme = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
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

int CEquipAccord::Alarme(int num) const
{
	int		iResult;

	if(num<0 || num >99) return ERR_NON_CONFORME;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = alarme[num];
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeAlarme(int num,int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(num<0 || num >99) return ERR_NON_CONFORME;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			alarme[num] = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
		if(genere_TS)
		{
			proto->AjouterTS(NULL,ACD_ALARME);
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

// Mode de fonctionnement
int CEquipAccord::Mode() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = mode;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeMode(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 2)
	{
		EnterCriticalSection(&crit);
			mode = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
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

// Frequence
int CEquipAccord::Frequence() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = frequence;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeFrequence(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 99999)
	{
		EnterCriticalSection(&crit);
			frequence = iResult;
			tos = 0;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);
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

// Operation
int CEquipAccord::Operation() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = operation;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeOperation(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= OP_AUTOTUNING)
	{
		EnterCriticalSection(&crit);
			operation = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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

// No Xmit
int CEquipAccord::NoXmit() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = no_xmit;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeNoXmit(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			no_xmit = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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

// Type d'accord
int CEquipAccord::Accord() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = accord;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeAccord(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 3)
	{
		EnterCriticalSection(&crit);
			accord = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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

// Baque d'inductance
int CEquipAccord::AutoInduc() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = auto_induc;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeAutoInduc(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			auto_induc = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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
int CEquipAccord::Inductance() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = inductance;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeInductance(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if((valeur>=0 && valeur <= 511) || valeur == 999)
	{
		ChangeSelecteAlarme(ALARME_TUN,FALSE);
		ChangeAlarme(ALARME_TUN,1,TRUE);

		EnterCriticalSection(&crit);
			inductance = iResult;
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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

// Baque de capacite
int CEquipAccord::AutoCapa() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = auto_capa;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeAutoCapa(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			auto_capa = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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
int CEquipAccord::Capacite() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = capacite;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeCapacite(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if((valeur>=0 && valeur <= 255) || valeur == 999)
	{
		ChangeSelecteAlarme(ALARME_TUN,FALSE);
		ChangeAlarme(ALARME_TUN,1,TRUE);

		EnterCriticalSection(&crit);
			capacite = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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

// Tos
int CEquipAccord::AutoTos() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = auto_tos;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeAutoTos(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			auto_tos = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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

int CEquipAccord::Tos() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = tos;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeTos(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if((valeur>=10 && valeur <= 99) || valeur == 0)
	{
		EnterCriticalSection(&crit);
			tos = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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

// Etat de l'operation TUN
int CEquipAccord::Etat() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = etat;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeEtat(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 7)
	{
		EnterCriticalSection(&crit);
			etat = iResult;

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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

// Chaine
int CEquipAccord::Chaine(int index,char *reponse) const
{
	int		iResult = 0;

	if(index<0 || index>4) return ERR_NON_CONFORME;
	EnterCriticalSection((CRITICAL_SECTION*)&crit);

		strcpy(reponse,chaine[index]);

	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipAccord::ChangeChaine(int index, char* message,BOOL genere_TS)
{
	int 	iResult = 0;

	if(index>=0 && index<=4 && (int)strlen(message)<=TAILLE_CHAINE) 
	{
		EnterCriticalSection(&crit);
			strcpy(chaine[index],message);

			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
		LeaveCriticalSection(&crit);

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

