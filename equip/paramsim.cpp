/* **************************************************************************
FICHIER :	ParamSimu.CPP		 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CParamSimu
***************************************************************************	*/
#include <stdio.h>
#include "stdafx.h"

#include "Equip\ParamSim.h"
#include "Equip\EqpStd.h"
#include "Equip\Eqp1225.h"
#include "Equip\Eqp1241.h"
#include "Equip\Eqp18A.h"
#include "Equip\EqpAudi.h"
#include "Equip\EqpAcco.h"

#include "Equip\Eqp18C.h"
#include "Equip\Eqp1236.h"
#include "Equip\Eqp1236L.h"
#include "Equip\Eqp1236S.h"
#include "Equip\Eqp1237.h"
#include "Equip\Eqp1237L.h"
#include "Equip\Eqp1237S.h"
#include "Equip\Eqp1241.h"
#include "Equip\Eqp1241L.h"
#include "Equip\Eqp1241S.h"
#include "Equip\Eqp251.h"
// Header des multicoupleurs AAD_20x4 et AAD_20_8
#include "Equip\EqpAAD.h"
// Header des matrices de commutation SPIN et L11
#include "Equip\EqpMAT.h"
// Header des multicoupleurs CA150
#include "Equip\EqpCA150.h"
// Header des CV24 equipments.
#include "Equip\EqpCV24Card.h"
// Header des TOR equipments.
#include "Equip\EqpTORCard.h"
// Header pour les matrices de commutation.
#include "Equip\EqpMatCom.h"
// Header de l'interface de test
#include "Equip\EquipTest.h"
// Header temporaire a effacer
#include "Equip\EqpTemp.h"
// Header du modem 1752
#include "Equip\EquipM1752.h"
// Header du ED42
#include "Equip\EquipED42.h"


#include "DlgOutil.h"
#include "DlgAccue.h"

#include "Divers\div_fic.h"

extern	CDlgAccueil *glob_ihm;
extern	CSynchro	*glob_synchro;
extern	CDlgOutil	*boite;
extern 	CDlgOutil	*glob_barre;				// Boite d'outil

/* **********************************************************************
METHODE :		CParamSimu()
TRAITEMENT:		Cronstruit l'objet
***********************************************************************	*/
CParamSimu::CParamSimu()
{
	int		i;

	InitializeCriticalSection(&crit);

	// CHANGEMENT max_liaison = 18;
	// CHANGEMENT max_liaison = 19;
	// CHANGEMENT max_liaison = 20;
	// CHANGEMENT max_liaison = 22;
	// CHANGEMENT max_liaison = 23;
	// CHANGEMENT max_liaison = 24;
	// CHANGEMENT max_liaison = 25;
	max_liaison = 51;
	for(i=0;i<NB_MAX_LIAISON;i++)
	{
		table_affecte[i].affectable = TRUE;	
		table_affecte[i].type_eqp = EQP_NON_AFFECTE;	
		strcpy(table_affecte[i].repere,"");	
		table_affecte[i].format.num_port = i+1;
		table_affecte[i].format.vitesse = 9600;
		table_affecte[i].format.data = 7;
		table_affecte[i].format.stop = UN_STOP;
		table_affecte[i].format.parite = EVEN_PARITE;
		table_affecte[i].format.control_parite = TRUE;

		table_affecte[i].controle = TRUE;
		table_affecte[i].activite = FALSE;

		table_affecte[i].Eqp = NULL;
		table_affecte[i].icone = NULL;
	}

    taille_journaux = DEFAUT_TAILLE_JOURNAUX;

   	top_externe = FALSE;
    depart = 0;
    periode     = 60;
}

/* **********************************************************************
METHODE :		~CParamSimu()
TRAITEMENT:		Destructeur
***********************************************************************	*/
CParamSimu::~CParamSimu()
{
	DeleteCriticalSection(&crit);
}

/* **********************************************************************
METHODE :		MaxLiaison()
TRAITEMENT:		Reccupère le nombre de liaison
***********************************************************************	*/
int CParamSimu::MaxLiaison() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = max_liaison;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

/*************************************************************************
Modif_Nb_liaison : 	Contole la modification nombre de liaison retourne TRUE
					sur succés et FALSE pour une valeur incohérente
*************************************************************************/
BOOL CParamSimu::Modif_Nb_liaison(int nb_liaison)
{
	int		i;
	BOOL	bResult = FALSE;
	char	ligne[TAILLE_MAX_LIGNE+1];

	if(nb_liaison <= 0 && nb_liaison > NB_MAX_LIAISON) return FALSE;

	EnterCriticalSection(&crit);
		for(i= nb_liaison-1 ; i<max_liaison ; i++)
			if(table_affecte[i].Eqp != NULL)		// Equippement affecté
			{
				LeaveCriticalSection(&crit);

				sprintf(ligne,"Impossible de réduire à ce nombre de liaison : La liaison %d est affectée",i+1);
				glob_ihm->Ajout_message(ligne);

				return FALSE;
			}

				
		for(i=max_liaison; i<nb_liaison; i++)
		{
			table_affecte[i].affectable = TRUE;	
			table_affecte[i].type_eqp = EQP_NON_AFFECTE;	
			strcpy(table_affecte[i].repere,"");	
			table_affecte[i].format.num_port = i+1;
			table_affecte[i].format.vitesse = 9600;
			table_affecte[i].format.data = 7;
			table_affecte[i].format.stop = UN_STOP;
			table_affecte[i].format.parite = EVEN_PARITE;
			table_affecte[i].format.control_parite = TRUE;

			table_affecte[i].controle = TRUE;
			table_affecte[i].activite = FALSE;

			table_affecte[i].Eqp = NULL;
			table_affecte[i].icone = NULL;
		}

   		if(max_liaison != nb_liaison)
   		{
   			max_liaison = nb_liaison;
			bResult = TRUE;
		}
	LeaveCriticalSection(&crit);
	if(bResult)
	{
		sprintf(ligne,"Modification du nombre de liaison à %d",nb_liaison);
		glob_ihm->Ajout_message(ligne);
	}


	return bResult;
}

/* **********************************************************************
METHODE :		Affectable()
TRAITEMENT:		Réccupère l'etat d'affectablilté de la ieme liaison
***********************************************************************	*/
int CParamSimu::Affectable(int i) const
{
	int		iResult;
	if (i <0 || i>=NB_MAX_LIAISON) return FALSE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = table_affecte[i].affectable;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

/* **********************************************************************
METHODE :		Modif_Affecte()
TRAITEMENT:		Modifie l'affectabilité d'une liaison
***********************************************************************	*/
int CParamSimu::Modif_Affecte(int ligne,BOOL affecte)
{
	BOOL	bResult = FALSE;
	char	message[TAILLE_MAX_LIGNE+1];

	if (ligne <0 || ligne>=NB_MAX_LIAISON) return bResult;

	EnterCriticalSection(&crit);
		if(table_affecte[ligne].Eqp != NULL && !affecte)		// Equippement affecté
		{
			LeaveCriticalSection(&crit);
			sprintf(message,"Impossible de réserver cette liaison %d : Déjà affectée à un équipement",ligne+1);
			glob_ihm->Ajout_message(message);
			return FALSE;
		}

		if(table_affecte[ligne].affectable != affecte)
		{
			table_affecte[ligne].affectable = affecte;
			bResult = TRUE;
		}
	LeaveCriticalSection(&crit);
	if(bResult)
	{
		sprintf(message,"Affectabilite de la ligne %d : %s",ligne+1 , affecte ? "Oui":"Non");
		glob_ihm->Ajout_message(message);
	}

	return bResult;
}

/* **********************************************************************
METHODE :		MaxMessage()
TRAITEMENT:		Reccupère la taille des journaux
***********************************************************************	*/
int CParamSimu::MaxMessage() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = taille_journaux;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

/*************************************************************************
METHODE :		Modif_taille()
TRAITEMENT :	Modifie la taille des journaux
*************************************************************************/
BOOL CParamSimu::Modif_taille(int taille)
{
	BOOL	bResult = FALSE;
	char	message[TAILLE_MAX_LIGNE+1];

	EnterCriticalSection(&crit);
		if(taille > 0)
		{
	   		if(taille_journaux != taille)
			{
	   			taille_journaux = taille;
				bResult = TRUE;
			}
		}
	LeaveCriticalSection(&crit);
	if(bResult)
	{
		sprintf(message,"Taille des journaux limitée à  %d événements",taille);
		glob_ihm->Ajout_message(message);
	}

	return bResult;
}

/* **********************************************************************
METHODE :		Top_synchro()
TRAITEMENT:		Reccupère la caracteristique externe du top synchro
***********************************************************************	*/
void CParamSimu::Top_synchro(int *ext,int *dep,int *per) const
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		*ext = top_externe;
		*dep = depart;
		*per = periode;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

/* **********************************************************************
METHODE :		Change_top_synchro()
TRAITEMENT:		Change les caractéristique du Top Synchro
***********************************************************************	*/
BOOL CParamSimu::Change_top_synchro(int	ext,int dep,int per)
{
	BOOL	bResult = FALSE;
	char	message[TAILLE_MAX_LIGNE+1];

	EnterCriticalSection(&crit);
		if(top_externe != ext || depart != dep || periode != per)
		{
			top_externe = ext;
			depart = dep;
			periode = per;
			bResult = TRUE;
		}
	LeaveCriticalSection(&crit);

	if(bResult)
	{
		sprintf(message,"Nouveau paramétrage du top Synchro");
		glob_ihm->Ajout_message(message);
	}

	glob_synchro->Change_Top();		// previent la tache CSynchro

	return bResult;
}


/* **********************************************************************
METHODE :		Init_Environ()
TRAITEMENT:		Initialise un enviuronnement vierge
***********************************************************************	*/
BOOL CParamSimu::Init_Environ()
{
	int 	i;

	t_affecte affectation;

	Modif_Nb_liaison(18);

	Modif_taille(DEFAUT_TAILLE_JOURNAUX);

	Change_top_synchro(FALSE,0,60);

	for(i=0;i<NB_MAX_LIAISON;i++)
	{
		affectation.affectable = TRUE;	
		affectation.type_eqp = EQP_NON_AFFECTE;	
		strcpy(affectation.repere,"");	
		affectation.format.num_port = i+1;
		affectation.format.vitesse = 9600;
		affectation.format.data = 7;
		affectation.format.stop = UN_STOP;
		affectation.format.parite = EVEN_PARITE;
		affectation.format.control_parite = TRUE;

		affectation.controle = TRUE;
		affectation.activite = FALSE;

		affectation.Eqp = NULL;

		Modif_Equipement(i,affectation);
	}


	return TRUE;
}

/* **********************************************************************
METHODE :		Sauvegarder_Environ()
TRAITEMENT:		Sauvegarde l'environnement d'utilisation dans fichier
***********************************************************************	*/
BOOL CParamSimu::Sauvegarder_Environ(char *fichier)
{
	int 	iResult;
	int 	i,j,k;

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];

	t_affecte affectation;

	strcpy(contenu,"// Environnement du Simulateur\r\n");
	strcat(contenu,"// ***************************\r\n");
	
	strcpy(ligne,"P00=ENVIRONNEMENT\r\n");
	strcat(contenu,ligne);

	sprintf(ligne,"P01=%d\r\n",MaxLiaison());
	strcat(contenu,ligne);

	sprintf(ligne,"P02=%d\r\n",MaxMessage());
	strcat(contenu,ligne);

	Top_synchro(&i,&j,&k);
	sprintf(ligne,"P03=%d\r\n",i);
	strcat(contenu,ligne);

	sprintf(ligne,"P04=%d\r\n",j);
	strcat(contenu,ligne);

	sprintf(ligne,"P05=%d\r\n",k);
	strcat(contenu,ligne);

	for(i=0 ; i<NB_MAX_LIAISON ; i++)
	{
		Equipement(i,&affectation);
		
		sprintf(ligne,"P%2.2d=%1d%2.2d%-*s %2.2d%4.4d%1d%1d%1d%1d%1d\r\n",i+10,
					affectation.affectable,
					affectation.type_eqp,
					TAILLE_REPERE-1,affectation.repere,
					affectation.format.num_port,
					affectation.format.vitesse,
					affectation.format.data,
					affectation.format.stop,
					affectation.format.parite,
					affectation.format.control_parite,
					affectation.icone ? (affectation.icone)->Actif():0
					);
		strcat(contenu,ligne);
	}

	iResult = Stocker_fichier(fichier,contenu);
	if(iResult<0)
	{
		glob_ihm->Ajout_message("**** Erreur d'ouverture fichier d'environnement du simulateur");
		return FALSE;
	}
	sprintf(ligne,"Sauvegarde de l'environnement : %s",fichier);
	glob_ihm->Ajout_message(ligne);

	return TRUE;


}

/* **********************************************************************
METHODE :		Charger_Environ()
TRAITEMENT:		Charger le fichier d'environnement fichier
***********************************************************************	*/
BOOL CParamSimu::Charger_Environ(char *fichier)
{
	int 	iResult;
	int		i,j,k;
	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];
	char	cle[80];

	t_affecte affectation;

	iResult = Recup_fichier(fichier,contenu);
	if(iResult<0)
	{
		glob_ihm->Ajout_message("**** Erreur d'ouverture fichier contexte exploitation");
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P00=",ligne,TAILLE_MAX_LIGNE);
	if(strcmp(ligne+4,"ENVIRONNEMENT")!=0)
	if(iResult<0)
	{
			glob_ihm->Ajout_message("**** Erreur fichier non conforme à un environnement");
		return FALSE;
	}

	sprintf(ligne,"Chargement de l'environnement : %s",fichier);
	glob_ihm->Ajout_message(ligne);

	Init_Environ();
	iResult = Extrait_ligne(contenu,"P01=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	Modif_Nb_liaison(atoi(ligne+4));

	iResult = Extrait_ligne(contenu,"P02=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	Modif_taille(atoi(ligne+4));

	iResult = Extrait_ligne(contenu,"P03=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
	{
		i=atoi(ligne+4);
		iResult = Extrait_ligne(contenu,"P04=",ligne,TAILLE_MAX_LIGNE);
		if(iResult>=0)
		{
			j=atoi(ligne+4);
			iResult = Extrait_ligne(contenu,"P05=",ligne,TAILLE_MAX_LIGNE);
			if(iResult>=0)	k=atoi(ligne+4);
			{
				Change_top_synchro(i,j,k);
			}
		}
	}

	for(i=0 ; i<NB_MAX_LIAISON ; i++)
	{

		affectation.affectable = TRUE;	
		affectation.type_eqp = EQP_NON_AFFECTE;	
		strcpy(affectation.repere,"");	
		affectation.format.num_port = i+1;
		affectation.format.vitesse = 9600;
		affectation.format.data = 7;
		affectation.format.stop = UN_STOP;
		affectation.format.parite = EVEN_PARITE;
		affectation.format.control_parite = TRUE;

		affectation.controle = TRUE;
		affectation.activite = FALSE;

		affectation.Eqp = NULL;
		affectation.icone = NULL;
		
		sprintf(cle,"P%2.2d=",10+i);
		iResult = Extrait_ligne(contenu,cle,ligne,TAILLE_MAX_LIGNE);

		if(iResult>=0)
		{
			sprintf(cle,"%%1d%%2d%%%1dc%%2d%%4d%%1d%%1d%%1d%%1d%%1d\r\n",TAILLE_REPERE-1);
			sscanf(ligne+4,cle,
					&affectation.affectable,
					&affectation.type_eqp,
					affectation.repere,
					&affectation.format.num_port,
					&affectation.format.vitesse,
					&affectation.format.data,
					&affectation.format.stop,
					&affectation.format.parite,
					&affectation.format.control_parite,
					&affectation.controle
					);
			affectation.repere[TAILLE_REPERE-1]=0;
		}

		Modif_Affecte(i,affectation.affectable);
		Modif_Equipement(i,affectation);
	}


	return TRUE;
}

/* **********************************************************************
METHODE :		Equipement()
TRAITEMENT:		Charger les caracteristique d'une affectation
***********************************************************************	*/
void CParamSimu::Equipement(int	index,t_affecte *ligne) const
{
	if (index <0 || index>=NB_MAX_LIAISON)
		return;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		*ligne = table_affecte[index];
		if(table_affecte[index].Eqp != NULL)
		(*ligne).activite = table_affecte[index].Eqp->Actif();
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

/* **********************************************************************
METHODE :		Modif_Equipement()
TRAITEMENT:		Modifie l'affection d'une liaison/Equipement
***********************************************************************	*/
void CParamSimu::Modif_Equipement(int index,t_affecte liaison)
{
	char	message[TAILLE_MAX_LIGNE+1];
	if (index <0 || index>=NB_MAX_LIAISON) return;

	EnterCriticalSection(&crit);
		if(table_affecte[index].Eqp != NULL)		// Equippement affecté
		{
			if(table_affecte[index].Eqp->Actif())	// Pas de modif en activité
			{
				LeaveCriticalSection(&crit);
				return;
			}
		}

// modification autorisée
		// Le type d'equipement est conserve, modif du format et du repere
		if(table_affecte[index].type_eqp == liaison.type_eqp)
		{
			table_affecte[index] = liaison;
//			table_affecte[index].format = liaison.format;		
//			table_affecte[index].controle = liaison.controle;
			if(table_affecte[index].type_eqp != NULL)
			{
				table_affecte[index].Eqp->Afficher(liaison.controle);
				table_affecte[index].Eqp->FormatRepere();
				glob_barre->ChangeNomIcone(table_affecte[index].icone,
							table_affecte[index].repere,
							table_affecte[index].controle);
			}
		}
		else		// Nouvelle affectation
		{
			sprintf(message,"Affectation sur liaison %d : Equipement %d",index+1,liaison.type_eqp);
			glob_ihm->Ajout_message(message);

			// Désallocation du précedent equipement
			if (table_affecte[index].Eqp != NULL)
			{
				//delete(table_affecte[index].Eqp);
				table_affecte[index].Eqp->~CEquip();
				liaison.Eqp = NULL;
			// Suppression de l'icone
				glob_barre->Retire_icone(table_affecte[index].icone);
			}

			table_affecte[index] = liaison;
			switch(table_affecte[index].type_eqp)
			{
				case EQP_BOITE_ACCORD:
					table_affecte[index].Eqp = new CEquipAccord(index);
					break;
				case EQP_STANDARD_HF:
					table_affecte[index].Eqp = new CEquipStd(index);
					break;
				case EQP_AUDIO_TTY:
					table_affecte[index].Eqp = new CEquipAudio(index);
					break;

				case EQP_TRC1225M:
					table_affecte[index].Eqp = new CEquip1225(index);
					break;

				case EQP_TRBM18A:
					table_affecte[index].Eqp = new CEquip18A(index);
					break;
				case EQP_TRBM18C:
					table_affecte[index].Eqp = new CEquip18C(index);
					break;

				case EQP_TRC1241_FF:
					table_affecte[index].Eqp = new CEquip1241(index);
					break;
				case EQP_TRC1241_L11:
					table_affecte[index].Eqp = new CEquip1241L(index);
					break;
				case EQP_TRC1241_SPIN:
					table_affecte[index].Eqp = new CEquip1241S(index);
					break;

				case EQP_TRC1236_FF:
					table_affecte[index].Eqp = new CEquip1236(index);
					break;
				case EQP_TRC1236_L11:
					table_affecte[index].Eqp = new CEquip1236L(index);
					break;
				case EQP_TRC1236_SPIN:
					table_affecte[index].Eqp = new CEquip1236S(index);
					break;

				case EQP_TRC1237_FF:
					table_affecte[index].Eqp = new CEquip1237(index);
					break;
				case EQP_TRC1237_L11:
					table_affecte[index].Eqp = new CEquip1237L(index);
					break;
				case EQP_TRC1237_SPIN:
					table_affecte[index].Eqp = new CEquip1237S(index);
					break;
				case EQP_TRC251:
					table_affecte[index].Eqp = new CEquip251(index);
					break;
				case AAD_20_4:
					table_affecte[index].Eqp = new CEquipAAD(index, 4);
					break;
				case AAD_20_8:
					table_affecte[index].Eqp = new CEquipAAD(index, 8);
					break;
				case MATRICE_SPIN:
					table_affecte[index].Eqp = new CEqpMAT(index, SPIN);
					break;
				case MATRICE_L11:
					table_affecte[index].Eqp = new CEqpMAT(index, L11);
					break;
				case CA_150_MASTER:
					table_affecte[index].Eqp = new CEquipCA150(index, MASTER);
					break;
				case CA_150_SLAVE:
					table_affecte[index].Eqp = new CEquipCA150(index, SLAVE);
					break;
				case KY58:
					table_affecte[index].Eqp = new CEquipCV24Card(index, CV24_KY58);
					break;
				case ANDVT:
					table_affecte[index].Eqp = new CEquipCV24Card(index, CV24_ANDVT);
					break;
				case COMMUTATION_MATRIX:
					table_affecte[index].Eqp = new CEquipCommutationMatrix(index);
					break;
				case TOR_KY58:
					table_affecte[index].Eqp = new CEquipTORCard(index, TYPE_TOR_KY58);
					break;
				case TOR_ANDVT:
					table_affecte[index].Eqp = new CEquipTORCard(index, TYPE_TOR_ANDVT);
					break;
				case TOR_CARD:
					table_affecte[index].Eqp = new CEquipTORCard(index, TYPE_TOR_CARD);
					break;
				case MDM_TRC1752:
					table_affecte[index].Eqp = new CEquipM1752(index);
					break;
				case ED42:
					table_affecte[index].Eqp = new CEquipED42(index);
					break;
				case Test:
					table_affecte[index].Eqp = new CEquipTest(index);
					break;
				default:
					LeaveCriticalSection(&crit);
					return;
					break;
			}

			table_affecte[index].Eqp->Allocation();
		
			// Ajout d'un nouvel Icone
			if (table_affecte[index].type_eqp != NULL)
			{
				table_affecte[index].icone = glob_barre->Ajoute_icone(table_affecte[index].type_eqp,
					table_affecte[index].repere,
					table_affecte[index].controle,
					table_affecte[index].Eqp);
			}
		}
	LeaveCriticalSection(&crit);
}

/* **********************************************************************
METHODE :		Icone()
TRAITEMENT:		Renvoi l'icone associé à la idex_ieme position
***********************************************************************	*/
CIcone	 *CParamSimu::Icone(int index)
{
	CIcone	*element;

	if(index <0 || index>=NB_MAX_LIAISON) return NULL;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		element = table_affecte[index].icone;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
	return element;
}

