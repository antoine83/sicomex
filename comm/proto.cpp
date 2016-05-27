/* **************************************************************************
FICHIER :	Propto.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CProto
***************************************************************************	*/

#include "stdafx.h"

#include "Comm\proto.h"
#include "divers\Div_tmp.h"
/* **************************************************************************
METHODE :		CProto()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProto::CProto(t_format	fmt,CEquip *peqp)
{
	//int iResult;			//2009-11-27

	format = fmt;
	eqp = peqp;

	event = CreateEvent(NULL,FALSE,FALSE,NULL);

	erreur_com.pas_debut = FALSE;
	erreur_com.pas_fin = FALSE;
	erreur_com.controle_parite = FALSE;

	erreur_com.retard = 5;

	erreur_com.cde_inconnue = FALSE;
	erreur_com.pas_de_reponse = FALSE;
}

/* **************************************************************************
METHODE :		~CProto()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProto::~CProto()
{
	int		iResult;
	BOOL	bResult;

	iResult = Desactiver();
	CloseHandle(event);

	if(Handle() != NULL)
	{
		bResult = TerminateThread(Handle(),0);
	}
}

/* **************************************************************************
METHODE :		InitialiseFormat()
TRAITEMENT:		Initialise le format de transmission
***************************************************************************	*/
void CProto::InitialiseFormat(t_format	fmt)
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		format = fmt;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

/* **************************************************************************
METHODE :		Desactiver()
TRAITEMENT:		Termine le thread associé
***************************************************************************	*/
int CProto::Desactiver()
{
	int		iResult;
	DWORD	dwResult;

	if(EtatTache() == THREAD_NON_CREE) return ERR_CTACHE;

	ChangeEtat(THREAD_NON_CREE);
	PulseEvent(event);

	Purge_message();
	dwResult = WaitForSingleObject(Handle(),1000);
	if(dwResult == WAIT_TIMEOUT)
	{
		TerminateThread(Handle(),0);
	}

	iResult = ligne.Fermeture();
	if (iResult<0) eqp->AjouterMessage("**** Erreur Fermeture",iResult);

	return 0;
}

/* **************************************************************************
METHODE :		AjouterTS()
TRAITEMENT:		Ajoute un message de télésignalisation à la liste de message
				à transférer
***************************************************************************	*/
int CProto::AjouterTS(char *mes,int type_cde)
{
	table_cde.Ajouter(mes,type_cde);
	SetEvent(event);
	return 0;
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProto::EnvoyerTS(char *message)
{
	int		iResult;
	int		len_mes = (int)strlen(message);
	int		nb_car_enveloppe;		// Nombre de caractère envlopant le message

	nb_car_enveloppe = 0;
	char	buf[TAILLE_BUFFER];
	char	octet_controle[2];

	if(len_mes + nb_car_enveloppe > TAILLE_BUFFER-1)
			 return ERR_TAILLE_BUFFER;

	sprintf(buf,"%s%s",message,ControleTrame(message,octet_controle));
	iResult = ligne.Ecrire(buf);
	if(iResult < 0) return ERREUR_EXTERNE*iResult;

	return iResult;			// nb caractere transmis
}

/* **************************************************************************
METHODE :		TraiteTC()
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquitement
***************************************************************************	*/
int CProto::TraiteTC(char *mes)
{
	char	reponse[TAILLE_PIPE_MESSAGE+1];

	if(!strcmp(mes,"")) return ERR_CDE_INCONNUE;

	if(!strcmp(mes,"")) return ERR_PAS_ACQUITTE;

	strcpy(reponse,"Ok Bill");
	
	EnvoyerTS(reponse);

	return 0;
}

/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
int CProto:: TraiteTS(int type_cde,char *reponse)
{
	if(type_cde <=0) return ERR_CDE_INCONNUE;	// Type commande inconue

	sprintf(reponse,"Commande n°%d",type_cde);
	return type_cde;
}

/* **************************************************************************
METHODE :		RecevoirTC()
TRAITEMENT:		Réceptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProto::RecevoirTC(char *message,int nb_car)
{
	char	buf[TAILLE_BUFFER+1];
	int		iResult;

	if(nb_car > TAILLE_BUFFER) return ERR_TAILLE_BUFFER;

	iResult = ligne.Lire(buf,nb_car);
	if(iResult < 0) return ERREUR_EXTERNE*iResult;

	if(!ExtraitUtile(buf,message,&iResult)) 
		return ERR_NON_CONFORME;			// Message non conforme

	return iResult;
}

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Attend un message d'acquitement du type de commande précedement
				envoyé comme TS Maitre
***************************************************************************	*/
BOOL CProto::ValideAcquittement(int type_cde,char *message)
{
	return TRUE;
}

/* **************************************************************************
METHODE :		Purge_message()
TRAITEMENT:		Purge de la table TS
***************************************************************************	*/
void CProto::Purge_message()
{
	char	mes[TAILLE_PIPE_MESSAGE+1];
	int		type_cde;
	
	while(table_cde.EstNonVide())
		table_cde.Retirer(mes,&type_cde);

}

/* **************************************************************************
METHODE :		Purge_Reception()
TRAITEMENT:		Purge le buffer de réception
***************************************************************************	*/
void CProto::Purge_Reception()
{
	ligne.Purge();
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
***************************************************************************	*/
char *CProto::ControleTrame(char *message,char *octet_controle)
{
	strcpy(octet_controle,"");
	return octet_controle;
}

/* **************************************************************************
METHODE :		ExtraitUtile()
TRAITEMENT:		Extrait la partie utile du message
***************************************************************************	*/
BOOL CProto::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	strcpy(message,buf);

	*long_utile = (int)strlen(message);
	return TRUE;
}

/* **************************************************************************
METHODE :		RetourneErreurCom()
TRAITEMENT:		Retourne les erreur de communication
***************************************************************************	*/
void CProto::RetourneErreurCom(t_ComErreur	*err) const
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		*err = erreur_com;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

/* **************************************************************************
METHODE :		ChangeErreurCom()
TRAITEMENT:		Modifie les erreurs de communication
***************************************************************************	*/
void CProto::ChangeErreurCom(t_ComErreur	err)
{
	EnterCriticalSection(&crit);
		erreur_com = err;
	LeaveCriticalSection(&crit);
}
/* **************************************************************************
METHODE :		Traitement()
TRAITEMENT:		Traitement à effecter dans le thread :
				- Gere les dialogues Esclave
				- Gere les dialogue maitre à partir de la liste de message
				  à transférer
***************************************************************************	*/
DWORD WINAPI CProto::Traitement(void *param)
{
	int		i,j,iResult,nb_message;
	DWORD	dwResult;

	char	mes[TAILLE_PIPE_MESSAGE+1];

	int		type_cde;
	char	tps[25];
	char	buf[3*TAILLE_PIPE_MESSAGE+25];	// Message dans journal

	time_t 	timeout,t;
	int		tab_ts_envoye[DIM_TS_ACQ];
	int		nb_ts_en_cours = 0;	// = type TS en cours, 0 si aucune

	t_ComErreur	err_com;					// erreurs de communication

	int		long_message;					// longuer message pour affichage hexa

	iResult = ligne.Ouverture(format.num_port,
				format.vitesse,format.data,
				format.stop,format.parite);
	if (iResult<0)
	{
		eqp->AjouterMessage("**** Erreur d'Ouverture port",iResult);
		Desactiver();
	}

	time(&timeout);
	while (EtatTache() != THREAD_NON_CREE)
	{
		// Récupération de la structure des erreur de communication
		RetourneErreurCom(&err_com);

		// Priorité aux envoi du simulateur
		dwResult = WaitForMultipleObjects(1,&event,FALSE,0);
		if(dwResult == WAIT_OBJECT_0 + 1)		// Timeout
		{
			Sleep(1000);
			continue;
		}

		if(dwResult == WAIT_TIMEOUT)			// Timeout
		{
// Test de reception de message

			iResult = RecevoirTC(mes,TAILLE_PIPE_MESSAGE);
			if (iResult<0)
			{
				if (iResult != ERREUR_TIMEOUT)
				{
					eqp->AjouterMessage("**** Erreur RecevoirTC",iResult);
					continue;
				}
			}
			else
			{
				sprintf(buf,"<-- %s - ",Renvoi_temps_milli(tps));
				if(!hexa)
					strcat(buf,mes);
				else
				{
					for(i=0 ; i<iResult ; i++)
					{
						sprintf(tps,"%2.2X ",mes[i]);
						strcat(buf,tps);
					}
				}
				eqp->AjouterMessage(buf,0);

				if(err_com.retard)
					Sleep(err_com.retard);

				if(erreur_com.cde_inconnue) strcpy(mes,"cde inconnue");

				if(erreur_com.pas_de_reponse)
				{
					iResult = ERR_PAS_ACQUITTE;
					eqp->AjouterMessage("**** Mal ou Pas d'acquitement",iResult);
					continue;
				}
				else iResult = TraiteTC(mes);

				if (iResult>=0)
				{
					sprintf(buf,"<-- %s - ",Renvoi_temps_milli(tps));
					if(!hexa)
						strcat(buf,mes);
					else
					{
						for(i=0 ; i<(int)strlen(mes) ; i++)
						{
							sprintf(tps,"%2.2X ",mes[i]);
							strcat(buf,tps);
						}
					}

					strcat(buf," acquitté");

					eqp->AjouterMessage(buf,0);

					continue;
				}
				else
				{
					if(nb_ts_en_cours==0) continue;

					// Le message recu est peut être un acquittement de la TS en cours
					for(i=0 ; i<nb_ts_en_cours ; i++)
					{
						if(!ValideAcquittement(tab_ts_envoye[i],mes) || tab_ts_envoye[i]<=0)
							continue;
						else
						{
							for(j=i ; j<nb_ts_en_cours ; j++)
							{
								tab_ts_envoye[j] = tab_ts_envoye[j+1];
							}
							nb_ts_en_cours --;
							break;
						}
					}
					continue;
				}
			}
		}

// Envoi d'un commande
		time(&t);
		if((timeout+TIMEOUT_ACQ_TS>t) || nb_ts_en_cours==0) 
		{
			// Dépilage de la table tournante
			nb_message=table_cde.EstNonVide();
			for (i = 0 ; i<nb_message ; i++)
			{
				if(!table_cde.Retirer(mes,&type_cde)) break;
				
				if(nb_ts_en_cours<DIM_TS_ACQ && type_cde>0)
				{
					tab_ts_envoye[nb_ts_en_cours] = type_cde; 
					nb_ts_en_cours++;
					time(&timeout);
				}


				if(type_cde == CDE_PURGE_PORT)
				{
					Purge_Reception();
					continue;
				}

				if(type_cde == CDE_TEMPO_SEQ)
				{
					Sleep(TEMPO_TRAVAIL);
					continue;
				}

				if(type_cde == CDE_TEMPO_DIV_10)
				{
					Sleep(TEMPO_TRAVAIL/10);
					continue;
				}

				if(type_cde == CDE_TEMPO_DIV_4)
				{
					Sleep(TEMPO_TRAVAIL/4);
					continue;
				}

				if(mes[0] == NULL)		// Reccupere les valeur
				{
					if(type_cde == CDE_TEXTE_SEUL) continue;
   	
					iResult = TraiteTS(type_cde,mes);
					if (iResult<0)
					{
						eqp->AjouterMessage("**** TS Impossible ou Inconnu",iResult);
						continue;
					}
					long_message = iResult;
				}
				else
					long_message = (int)strlen(mes);

				if(type_cde==CDE_HEXA)
				{
					sprintf(buf,"--> %s - Trame : ",Renvoi_temps_milli(tps));

					for(i=0 ; i<(int)strlen(mes) ; i++)
					{
						sprintf(tps,"%2.2X ",mes[i]);
						strcat(buf,tps);
					}

					eqp->AjouterMessage(buf,0);
					iResult = ligne.Ecrire(mes);
					if (iResult<0)
					{
						eqp->AjouterMessage("**** Erreur Ecrire HEXA",iResult);
						continue;
					}
				}
				else
				{
					sprintf(buf,"<-- %s - ",Renvoi_temps_milli(tps));
					if(!hexa)
						strcat(buf,mes);
					else
					{
						for(i=0 ; i<long_message ; i++)
						{
							sprintf(tps,"%2.2X ",mes[i]);
							strcat(buf,tps);
						}

					}

					eqp->AjouterMessage(buf,0);
		   	
			   		iResult = EnvoyerTS(mes);
					if (iResult<0)
					{
						eqp->AjouterMessage("**** Erreur EnvoyerTS",iResult);
						continue;
					}
				}
			}
		}
		else
		{
			while(nb_ts_en_cours)
			{
				nb_ts_en_cours--;
				type_cde = tab_ts_envoye[nb_ts_en_cours];

				if(!ValideAcquittement(type_cde,""))
				{
					eqp->AjouterMessage("**** Erreur Acquitement TS",type_cde);
					table_cde.Ajouter(NULL,type_cde);
				}
			}

		}
		continue;				// boucle attente evennement
	}								// Fin de boucle attente evennement
	return 0;
}
