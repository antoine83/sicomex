/* **************************************************************************
FICHIER :	P_1237.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CProto1237
***************************************************************************	*/

#include "stdafx.h"

#include "Comm\p_1237.h"
#include "Equip\Eqp1237.h"
#include "divers\div_tmp.h"

const int 	DEBUT_TRAME = 0xD;
const int 	FIN_TRAME 	= 0xA;

/* **************************************************************************
METHODE :		CProto1237()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProto1237::CProto1237(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;
	lecture_canal = 0;
}

/* **************************************************************************
METHODE :		~CProto1237()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProto1237::~CProto1237()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProto1237::EnvoyerTS(char *message)
{
	int		len_mes,iResult;
	int		nb_car_enveloppe;		// Nombre de caractère envlopant le message

	char	buf[TAILLE_BUFFER+1];
	char	octet_controle[8];

	len_mes = (int)strlen(message);	// Taille du message à envoyer
	nb_car_enveloppe = 1 + 1 + len_mes/9 + 1; 	// Debut Trame + Fin Trame
												// n  PC par tranche de 8 car
	if(len_mes+nb_car_enveloppe > TAILLE_BUFFER)
		 return ERR_TAILLE_BUFFER;
	
	buf[0] = DEBUT_TRAME;
	strcpy(buf+1,message);
	strcat(buf,ControleTrame(message,octet_controle));
	iResult = (int)strlen(buf);
	buf[iResult] = FIN_TRAME;
	buf[iResult+1]=0;				// Force la fin de chaine

	if(erreur_com.pas_debut) buf[0]=0x20;
	if(erreur_com.pas_fin) buf[iResult]=0;
	
	iResult = ligne.Ecrire(buf);
	if(iResult < 0) return ERREUR_EXTERNE+iResult;

	return iResult;  // nb d'octet transmis
}
/* **************************************************************************
METHODE :		TraiteTC()
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquitement
***************************************************************************	*/
int CProto1237::TraiteTC(char *mes)
{
	int		iResult = 0;
	int		cResult = 0;
	int		valeur;
	long	long_valeur;
	long	lResult = 0;
	char	reponse[TAILLE_PIPE_MESSAGE+1];

	strcpy(reponse,"");

	iResult = ((CEquip1237*)eqp)->Spin();
	if(iResult)	return ERR_PAS_ACQUITTE;

	if(strcmp(mes,"RMS")==0)		// Passage en commande
	{
		iResult = ((CEquip1237*)eqp)->ChangeSpin(1,FALSE);
		
//		strcpy(reponse,"rms");
//		EnvoyerTS(reponse);
		return 0;
	}

	if(strcmp(mes,"LOC")==0)		// Passage en Local
	{
		iResult = ((CEquip1237*)eqp)->ChangeLocal(0,FALSE);
		strcpy(reponse,"loc");
		EnvoyerTS(reponse);
		return 0;
	}

	if(mes[0]=='D')						// Mode double telecommende
	{
		valeur = atoi(mes+1);
		iResult = ((CEquip1237*)eqp)->ChangeLocal(2,FALSE);

		if(iResult >= 0)				// Modification acceptée
		{
			strcpy(reponse,mes);
			reponse[0]='d';
			EnvoyerTS(reponse);
		}
		return 0;
	}

	if(strcmp(mes,"RMT")==0)		// Passage en commande
	{
		iResult = ((CEquip1237*)eqp)->ChangeLocal(1,FALSE);
		
		strcpy(reponse,"rmt");
		EnvoyerTS(reponse);

		AjouterTS(NULL,EME_1237_OPTION);
		AjouterTS(NULL,EME_1237_FREQUENCE);
		AjouterTS(NULL,EME_1237_MODE_FONCT);
		AjouterTS(NULL,EME_1237_COMPRESSEUR);
		AjouterTS(NULL,EME_1237_MODE_TRAFIC);
		AjouterTS(NULL,EME_1237_CANAL_POSI);
		AjouterTS(NULL,EME_1237_INFO);
		return 0;
	}
	else
		if(((CEquip1237*)eqp)->Local() == 0) return ERR_PAS_ACQUITTE;

	switch(mes[0])
	{
		case 'M':		// Modes de trafic
			valeur = atoi(mes+1);
			iResult = ((CEquip1237*)eqp)->ChangeModeTrafic(0,valeur,FALSE);
			sprintf(reponse,"m%d",abs(iResult));
			EnvoyerTS(reponse);

			cResult = ((CEquip1237*)eqp)->ChangeCanal(0,TRUE);
			//ChangeCanalLecture(0);
			ChangeCanalLecture(cResult);

			if(iResult >= 0)				// Modification acceptée
			{
				AjouterTS(NULL,EME_1237_COMPRESSEUR);
			}

			break;

		case 'Z':
			valeur = atoi(mes+1);
			iResult = ((CEquip1237*)eqp)->ChangeCompresseur(valeur-1,FALSE);
			sprintf(reponse,"z%d",abs(iResult)+1);
			EnvoyerTS(reponse);

			if(iResult >= 0)				// Modification acceptée
			{
			}

			break;

		case 'B':
			valeur = atoi(mes+1);
			if(valeur<0 || valeur>9) return ERR_PAS_ACQUITTE;
			sprintf(reponse,"b%d?",valeur);
			EnvoyerTS(reponse);

			cResult = ((CEquip1237*)eqp)->ChangeCanal(0,TRUE);
			//ChangeCanalLecture(0);
			ChangeCanalLecture(cResult);

			AjouterTS(NULL,CDE_TEMPO_DIV_4);

			iResult = ((CEquip1237*)eqp)->ChangeFonction(0,valeur,FALSE);
			if(iResult>=0 && !((CEquip1237*)eqp)->Incident())		// Modification acceptée
				AjouterTS(NULL,EME_1237_MODE_FONCT);
			else
			{
				sprintf(reponse,"B%d=",valeur);
				AjouterTS(reponse,EME_1237_MODE_FONCT);
			}
			break;

		case 'F':
			long_valeur = atol(mes+1) * Puissance(10,8-(int)strlen(mes+1));

			lResult = ((CEquip1237*)eqp)->ChangeFrequence(0,long_valeur,FALSE);
  
			if(lResult >= 0)				// Modification acceptée Autre TS
			{
				cResult = ((CEquip1237*)eqp)->ChangeCanal(0,TRUE);
				//ChangeCanalLecture(0);
				ChangeCanalLecture(cResult);

				TraiteTS(EME_1237_FREQUENCE,reponse);
				reponse[0]='f';
				reponse[(int)strlen(reponse)-1] = '<';
				EnvoyerTS(reponse);

				AjouterTS(NULL,CDE_TEMPO_DIV_4);

				reponse[0]='F';
				reponse[(int)strlen(reponse)-1] = '?';
				AjouterTS(reponse,EME_1237_FREQUENCE);

				AjouterTS(NULL,CDE_TEMPO_DIV_4);

				if(((CEquip1237*)eqp)->Incident())
				{
					reponse[(int)strlen(reponse)-1] = '=';
					AjouterTS(reponse,EME_1237_FREQUENCE);
				}
				else
				{
					reponse[(int)strlen(reponse)-1] = '>';
					AjouterTS(reponse,EME_1237_FREQUENCE);
				}
			}
			else iResult = ERR_PAS_ACQUITTE;
			break;

		case 'H':
			valeur = atoi(mes+1);
			iResult = ((CEquip1237*)eqp)->ChangeChoixNiveau(valeur,FALSE);
			/* Correction du 30/01/2008 */
			if(iResult >= 0)				// Modification acceptée
			{
				sprintf(reponse,"h%d",abs(iResult));
				EnvoyerTS(reponse);

				AjouterTS(NULL,EME_1237_NIVEAU);
			}
			if(iResult == 0)
			{
				((CEquip1237*)eqp)->ChangeAutoNiveau(0);
			}
			break;

		case 'P':
			if(mes[1] == '#' || mes[1] == '=')
			{
				TraiteTS(EME_1237_CANAL_POSI,reponse);
				reponse[0]='p';
				reponse[(int)strlen(reponse)-1] = '>';
				EnvoyerTS(reponse);
			}
			else
			{
				valeur = atoi(mes+1);
				iResult = ((CEquip1237*)eqp)->ChangeCanal(valeur,FALSE);
				if(iResult >= 0)				// Modification acceptée Autre TS
				{
					ChangeCanalLecture(iResult);

					TraiteTS(EME_1237_CANAL_POSI,reponse);
					reponse[0]='p';
					reponse[(int)strlen(reponse)-1] = '<';
					EnvoyerTS(reponse);

					AjouterTS(NULL,CDE_TEMPO_DIV_4);

					reponse[0]='P';
					reponse[(int)strlen(reponse)-1] = '?';
					AjouterTS(reponse,EME_1237_CANAL_POSI);

					AjouterTS(NULL,CDE_TEMPO_DIV_4);

					if(((CEquip1237*)eqp)->Incident())
					{
						reponse[(int)strlen(reponse)-1] = '=';
						AjouterTS(reponse,EME_1237_CANAL_POSI);
					}
					else
					{
						reponse[(int)strlen(reponse)-1] = '>';
						AjouterTS(reponse,EME_1237_CANAL_POSI);
					}
				}
			}
			AjouterTS(NULL,EME_1237_NIVEAU);
			break;

		case 'C':
			iResult = 0;
			strncpy(reponse,mes+1,2);reponse[2]=0;
			valeur = atoi(reponse);
			if(valeur<1 || valeur >99) return ERR_CDE_INCONNUE;

			ChangeCanalLecture(valeur);

			if((int)strlen(mes+1)>5)		// canal,M,E,B : Modif canal
			{
				strcpy(reponse,mes+3);
				// Mode de fonctionnement
				valeur = atoi(reponse+(int)strlen(reponse)-1);
				iResult = ((CEquip1237*)eqp)->ChangeFonction(CanalLecture(),valeur,FALSE);
				reponse[(int)strlen(reponse)-1] = 0;
							
				// (E)
				reponse[(int)strlen(reponse)-1] = 0;

				// Mode de trafic
				valeur = atoi(reponse+(int)strlen(reponse)-1);
				iResult = ((CEquip1237*)eqp)->ChangeModeTrafic(CanalLecture(),valeur,FALSE);
				reponse[(int)strlen(reponse)-1] = 0;
	
				// frequence
				long_valeur = atol(reponse) * Puissance(10,8-(int)strlen(reponse));
				lResult = ((CEquip1237*)eqp)->ChangeFrequence(CanalLecture(),long_valeur,FALSE);
			}

			if(iResult >= 0)				// Modification acceptée Autre TS
			{
				TraiteTS(EME_1237_CANAL_LECT,reponse);
				reponse[0]='c';
				EnvoyerTS(reponse);
			}
			break;

		case 'T':					   // demande de test
			iResult = strcmp(mes,"TST");
			if(iResult == 0)				// Commande correcte
			{
				strcpy(reponse,"tst");
				EnvoyerTS(reponse);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);

				AjouterTS(NULL,EME_1237_TEST);
				AjouterTS(NULL,EME_1237_NIVEAU);
			}
			break;

		case 'X':		// Etat logique
			if((int)strlen(mes)!=3)
			{
				iResult = ERR_PAS_ACQUITTE;
				break;
			}
			strcpy(reponse,mes);
			reponse[0]='x';
			reponse[1]='x';
			EnvoyerTS(reponse);

			if(strcmp(mes,"XX[")==0)
			{
				if(((CEquip1237*)eqp)->Couplage()==0)
					((CEquip1237*)eqp)->ChangeCouplage(1,FALSE);
			}
			if(strcmp(mes,"XX_")==0)
			{
				if(((CEquip1237*)eqp)->Couplage()!=0)
					((CEquip1237*)eqp)->ChangeCouplage(0,FALSE);
			}

			iResult = 0;
			break;

		case 'Y':		// Data out
			if((int)strlen(mes)!=1)
			{
				iResult = ERR_PAS_ACQUITTE;
				break;
			}
			TraiteTS(EME_1237_CANAL_POSI,reponse);
			reponse[0]='y';
			EnvoyerTS(reponse);

			iResult = 0;

			break;

		default:
//			iResult = ERR_PAS_ACQUITTE;
			iResult = ERR_CDE_INCONNUE;
			break;
	}

	return iResult;
}

/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
int CProto1237:: TraiteTS(int type_cde,char *reponse)
{
	int		iResult;
	long	lResult;

	char	buf[80];

	iResult = ((CEquip1237*)eqp)->Spin();
	if(iResult)	return ERR_CDE_INCONNUE;

	strcpy(reponse,"");
	switch(type_cde)
	{
		case EME_1237_MODE_LOCAL:
			iResult = ((CEquip1237*)eqp)->Local();
			switch(iResult)
			{
				case 1:
					strcpy(reponse,"RMT");
					break;
				case 2:
					strcpy(reponse,"DCL");
					break;
				default:
					strcpy(reponse,"LOC");
					break;
			}
			break;

		case EME_1237_MODE_TRAFIC:
			iResult = ((CEquip1237*)eqp)->ModeTrafic(CanalLecture());
			sprintf(reponse,"M%d",iResult);
			break;

		case EME_1237_COMPRESSEUR:
			iResult = ((CEquip1237*)eqp)->Compresseur();
			sprintf(reponse,"Z%d",iResult+1);
			break;

		case EME_1237_MODE_FONCT:
			iResult = ((CEquip1237*)eqp)->Fonction(CanalLecture());
			sprintf(reponse,"B%d>",iResult);
			break;

		case EME_1237_INCIDENT:
			iResult = ((CEquip1237*)eqp)->Incident();
			if(iResult == -1)
			{
				strcpy(reponse,"J=");
				iResult = 0;
			}
			else
				sprintf(reponse,"J%2.2d",iResult);

			break;

		case EME_1237_FREQUENCE:
			lResult = ((CEquip1237*)eqp)->Frequence(CanalLecture());
			sprintf(reponse,"F%7.7ld",lResult/10);

			// Purge des 0 de fin de message
			while(reponse[(int)strlen(reponse)-1] == '0') 
				reponse[(int)strlen(reponse)-1]=0;

			strcat(reponse,">");
			break;

		case EME_1237_NIVEAU:
			iResult = ((CEquip1237*)eqp)->ChoixNiveau();
			switch(iResult)
			{
				case 1:
				case 2:
				case 3:
				case 4:
				/* Correction 30/01/2008 */
				case 5:
				case 6:
				case 7:
					iResult = ((CEquip1237*)eqp)->Niveau();
					sprintf(reponse,"H%C%C",abs(iResult)/16 + 0x30,(abs(iResult)%16) + 0x30);
					break;
				
				default:
					//iResult = ERR_PAS_ACQUITTE;
					break;
			}
			break;

		case EME_1237_CANAL_POSI:
			iResult = ((CEquip1237*)eqp)->Canal();
			sprintf(reponse,"P%2.2d",iResult);

			TraiteTS(EME_1237_FREQUENCE,buf);
			buf[(int)strlen(buf)-1]=0; // Pas de caractere de positionnement
			strcat(reponse,buf+1); 


			TraiteTS(EME_1237_MODE_TRAFIC,buf);
			strcat(reponse,buf+1);

			// Caractère réservé
			strcat(reponse,"0");

			TraiteTS(EME_1237_MODE_FONCT,buf);
			buf[(int)strlen(buf)-1]=0; // Pas de caractere de positionnement
			strcat(reponse,buf+1);

			// Caractère réservé
			strcat(reponse,">");
			break;

		case EME_1237_CANAL_LECT:
			sprintf(reponse,"C%2.2d",CanalLecture());

			TraiteTS(EME_1237_FREQUENCE,buf);
			buf[(int)strlen(buf)-1]=0; // Pas de caractere de positionnement
			strcat(reponse,buf+1); 


			TraiteTS(EME_1237_MODE_TRAFIC,buf);
			strcat(reponse,buf+1);

			// Caractère réservé
			strcat(reponse,"0");

			TraiteTS(EME_1237_MODE_FONCT,buf);
			buf[(int)strlen(buf)-1]=0; // Pas de caractere de positionnement
			strcat(reponse,buf+1);

			break;

		case EME_1237_OPTION:
			/*sprintf(reponse,"OP78",iResult); Correction 03/01/2008*/
			sprintf(reponse,"OP7%?",iResult);
			break;

		case EME_1237_TEST:
			iResult = ((CEquip1237*)eqp)->Test();
			sprintf(reponse,"TST%2.2d",iResult);
			break;

		case EME_1237_ETAT_LOGI:
			strcpy(reponse,"XX_");
			break;

		case EME_1237_DATA_OUT:
			TraiteTS(EME_1237_CANAL_POSI,reponse);
			reponse[0]='Y';
//			reponse[(int)strlen(reponse)-1] = 0; // F.P est inhibé
			break;

		case EME_1237_INFO:
			iResult = 1 && (((CEquip1237*)eqp)->Info());
			sprintf(reponse,"T%d",!iResult);
			break;

		default:
			iResult = ERR_CDE_INCONNUE;
			break;
	}

	return iResult;
}

/* **************************************************************************
METHODE :		RecevoirTC()
TRAITEMENT:		Réceptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProto1237::RecevoirTC(char *message,int nb_car)
{
	char	buf[TAILLE_BUFFER+1];
	int		i,iResult;

	if(nb_car > TAILLE_BUFFER) return ERR_TAILLE_BUFFER;

	i=0;
	while(i<nb_car)
	{
		iResult = ligne.Lire(buf+i,1);
		if(iResult < 0) return ERREUR_EXTERNE+iResult;
		if(iResult == 0) return ERREUR_TIMEOUT;
		if(buf[i]==DEBUT_TRAME && i!=0)
		{
			buf[0] = DEBUT_TRAME;
			i=0;
		}
		if(buf[i]==FIN_TRAME) break;

		i++;
	}

	if(!ExtraitUtile(buf,message,&iResult)) 
		return ERR_NON_CONFORME;			// Message non conforme

	return iResult;
}

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Attend un message d'acquitement du type de commande précedement
				envoyé comme TS Maitre
***************************************************************************	*/
BOOL CProto1237::ValideAcquittement(int type_cde,char *buf)
{
	int		iResult = NULL;
	BOOL	bResult;

	if(!erreur_com.controle_parite)	return TRUE;

	bResult = TRUE;
	switch(type_cde)
	{
		case EME_1237_MODE_LOCAL:
			if(strstr(" loc rmt d ",buf) ==0 )	bResult = FALSE;
			break;

		case EME_1237_MODE_TRAFIC:
			if(strcmp(buf,"m") != 0)	bResult = FALSE;
			break;

		case EME_1237_COMPRESSEUR:
			if(strcmp(buf,"z") != 0)	bResult = FALSE;
			break;

		case EME_1237_MODE_FONCT:
			if(strcmp(buf,"b") != 0)	bResult = FALSE;
			break;

		case EME_1237_INCIDENT:
			if(strcmp(buf,"j") != 0)	bResult = FALSE;
			break;

		case EME_1237_FREQUENCE:
			if(strcmp(buf,"f") != 0)	bResult = FALSE;
			break;

		case EME_1237_NIVEAU:
			if(strcmp(buf,"h") != 0)	bResult = FALSE;
			break;

		case EME_1237_CANAL_POSI:
			if(strcmp(buf,"p") != 0)	bResult = FALSE;
			break;

		case EME_1237_CANAL_LECT:
			if(strcmp(buf,"c") != 0)	bResult = FALSE;
			break;

		case EME_1237_OPTION:
			if(strcmp(buf,"op") != 0)	bResult = FALSE;
			break;

		case EME_1237_TEST:
			if(strcmp(buf,"tst") != 0)	bResult = FALSE;
			break;

		case EME_1237_DATA_OUT:
			if(strcmp(buf,"y") != 0)	bResult = FALSE;
			break;

		case EME_1237_INFO:
			if(strcmp(buf,"t") != 0)	bResult = FALSE;
			break;

		default:
			break;
	}

	return bResult;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
char* CProto1237::ControleTrame(char *message,char *octet_controle)
{
	int		i,len_mes;
	char	pc;

	strcpy(octet_controle,"");

	if(!erreur_com.controle_parite) 	return octet_controle;

	len_mes = (int)strlen(message);

	pc = 0;
	i=len_mes-1;
	while(i>=0)
	{	
		pc = pc ^ message[i];
		
		if((i) % 8 == 0)	// caract précedent = debut de tranche
		{
			if(pc < 64) pc += 64;
			strncat(octet_controle,&pc,1);
			pc = 0;
		}
		i--;
	}
	return octet_controle;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
BOOL CProto1237::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	char 	octet_controle[8];
	int		len_mes,nb_tranche;

	len_mes = (int)strlen(buf);		
	if(buf[0] != DEBUT_TRAME && buf[len_mes -1] != FIN_TRAME)
		return FALSE;

// 1 tranche = 8 caractère utile + 1 PC sans oublier d'oter les
// caracteres de debut et de fin de trame
	if(erreur_com.controle_parite)
		nb_tranche = (len_mes-2)/9 + !((len_mes-2)%9 == 0);
	else
		nb_tranche = 0;		// Aucun caractere de parite

	*long_utile = len_mes - 2 - nb_tranche;
	strcpy(message,"");
	strncat(message,buf+1,*long_utile);

	ControleTrame(message,octet_controle);
	if(strncmp(octet_controle,buf+1+(len_mes - 2 - nb_tranche),nb_tranche))
		return FALSE;

	return TRUE;
}

/* **************************************************************************
METHODE :		CanalLecture()
TRAITEMENT:		Retourne le n° de canal pour utiliser lors de l'envoi des TS
***************************************************************************	*/
int CProto1237::CanalLecture()
{
	int	valeur;
	
	EnterCriticalSection(&crit);
		valeur = lecture_canal;
	LeaveCriticalSection(&crit);

	return valeur;
}

/* **************************************************************************
METHODE :		ChangeCanalLecture()
TRAITEMENT:		Force un n° de canal pour utiliser lors de l'envoi des TS
***************************************************************************	*/
BOOL CProto1237::ChangeCanalLecture(int	valeur)
{
	if(valeur<0 || valeur > 99) return FALSE;
	
	EnterCriticalSection(&crit);
		lecture_canal = valeur;
	LeaveCriticalSection(&crit);

	return TRUE;
}
