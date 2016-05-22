/* **************************************************************************
FICHIER :	Prot_Acc.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CProtoAccord
***************************************************************************	*/

#include "stdafx.h"

#include "Comm\Prot_Acc.h"
#include "Equip\EqpAcco.h"
#include "divers\div_tmp.h"

const int 	DEBUT_TRAME = 0x0A;
const int 	FIN_TRAME 	= 0x0D;
const int 	SEPARATEUR 	= 0x20;

/* **************************************************************************
METHODE :		CProtoAccord()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProtoAccord::CProtoAccord(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;

	num_ordre = 0;
	type_trame = TS_ACQUITE;
}

/* **************************************************************************
METHODE :		~CProtoAccord()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProtoAccord::~CProtoAccord()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProtoAccord::EnvoyerTS(char *message)
{
	int		len_mes,iResult;
	int		nb_car_enveloppe;		// Nombre de caractère envlopant le message

	char	buf[TAILLE_BUFFER+1];
	char	octet_controle[2];

	len_mes = (int)strlen(message);	// Taille du message à envoyer
	nb_car_enveloppe = 1 + 1 + 1 + 1; 	// Debut Trame + n° ordre + CheckSum + Fin Trame 
												// n  PC par tranche de 8 car
	if(len_mes+nb_car_enveloppe > TAILLE_BUFFER)
		 return ERR_TAILLE_BUFFER;
	

	buf[0] = DEBUT_TRAME;
	if(!((CEquipAccord*)eqp)->Manuel())		// Mode Auto
	{
		buf[1] = type_trame + num_ordre;
		num_ordre = (num_ordre + 1) % 10;
		strcpy(buf+2,message);
	}
	else
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
int CProtoAccord::TraiteTC(char *mes)
{
	int		iResult = 0;
	int		i, j;
	int		pos,valeur;
	char	reponse[TAILLE_PIPE_MESSAGE+1];
	char	buf[80];

	char	*pcResult;

	strcpy(reponse,"");

	if( (pos =!((CEquipAccord*)eqp)->Manuel()))		// Mode auto
		if(mes[0]<0x61 || mes[0]>0x61+9)
			 iResult = ERR_CDE_INCONNUE;

	if(pos>0) num_ordre = mes[0]-0x61;

	if(strncmp(mes+pos,"ALM",3)==0)
	{
		valeur = atoi(mes+pos+3);

		iResult = ((CEquipAccord*)eqp)->Alarme(valeur);
		if(iResult >= 0)				// Modification acceptée
		{
			type_trame = TS_ACQUITE;
			sprintf(reponse,"> ALM%2.2d %1d Information complementaire",valeur,iResult);
		}
		else
		{
			type_trame = TS_ACQUITE;
			strcpy(reponse,"? SYNTAX");
		}
		EnvoyerTS(reponse);
	}

	if(strncmp(mes+pos,"ACK",3)==0)
	{
		if(strstr(mes+pos+3,"ROS")!=0)
			iResult = ((CEquipAccord*)eqp)->ChangeAlarme(ALARME_ROS,0,FALSE);
		if(strstr(mes+pos+3,"TUN")!=0)
			iResult = ((CEquipAccord*)eqp)->ChangeAlarme(ALARME_TUN,0,FALSE);
		if(iResult>=0)
		{
			sprintf(reponse,"> ACK ROS=%1d TUN=%1d TMP=%1d",
					((CEquipAccord*)eqp)->Alarme(ALARME_ROS),
					((CEquipAccord*)eqp)->Alarme(ALARME_TUN),
					((CEquipAccord*)eqp)->Alarme(ALARME_TMP));

			type_trame = TS_ACQUITE;
		}
		else
		{
			type_trame = TS_ACQUITE;
			strcpy(reponse,"? SYNTAX");
		}
		EnvoyerTS(reponse);
	}

	if(strncmp(mes+pos,"CFG",3)==0)
	{
		if(strstr(mes+pos+3,"TF")!=0)
			iResult = ((CEquipAccord*)eqp)->ChangeMode(0,FALSE);
		if(strstr(mes+pos+3,"RX")!=0)
			iResult = ((CEquipAccord*)eqp)->ChangeMode(1,FALSE);
		if((int)strlen(mes+pos+3)==0)		// Demande de lecture
			iResult = ((CEquipAccord*)eqp)->Mode();
		if(iResult>=0)
		{
			switch (iResult)
			{
				case 0:
					strcpy(reponse,"> CFG TF");
					break;
				case 1:
					strcpy(reponse,"> CFG RX");
					break;
				default:
					strcpy(reponse,"> CFG ?");
					break;
			}
			type_trame = TS_ACQUITE;
		}
		else
		{
			type_trame = TS_ACQUITE;
			strcpy(reponse,"? SYNTAX");
		}
		EnvoyerTS(reponse);
	}

	if(strncmp(mes+pos,"STS",3)==0)
	{
		strcpy(reponse,"> STS CFG=");

		iResult = ((CEquipAccord*)eqp)->Mode();
		switch (iResult)
		{
			case 0:
				strcat(reponse,"TF");
				break;
			case 1:
				strcat(reponse,"RX");
				break;
			default:
				strcat(reponse,"?");
				break;
		}

		iResult = ((CEquipAccord*)eqp)->Frequence();
		sprintf(buf," F=%2.2d.%3.3d",iResult/1000,iResult%1000);
		strcat(reponse,buf);

		iResult = ((CEquipAccord*)eqp)->Operation();
		switch(iResult)
		{
			case OP_IDLE:
				strcpy(buf," OP=IDLE");
				break;
			case OP_TUNING:
				strcpy(buf," OP=TUNING");
				break;
			case OP_SELFTEST:
				strcpy(buf," OP=M_SELFTEST");
				break;
			case OP_AUTOTUNING:
				strcpy(buf," OP=M_AUTOTUNING");
				break;
			default:
				strcpy(buf," OP=M_MAINTENANCE");				
				break;
		}
		strcat(reponse,buf);

		iResult = ((CEquipAccord*)eqp)->NoXmit();
		sprintf(buf," NOXMIT=%1d",iResult);
		strcat(reponse,buf);

		iResult = ((CEquipAccord*)eqp)->Accord();
		if(iResult<=2)
			sprintf(buf," TUNED=%1d",iResult);
		else
			strcpy(buf," TUNED=?");
		strcat(reponse,buf);

		iResult = ((CEquipAccord*)eqp)->Inductance();
		sprintf(buf," L=%3.3d",iResult);
		strcat(reponse,buf);

		iResult = ((CEquipAccord*)eqp)->Capacite();
		sprintf(buf," C=%3.3d",iResult);
		strcat(reponse,buf);

		iResult = ((CEquipAccord*)eqp)->Alarme(ALARME_ROS);
		sprintf(buf," SROS=%1d",iResult);
		strcat(reponse,buf);

		iResult = ((CEquipAccord*)eqp)->Alarme(ALARME_TUN);
		sprintf(buf," STUN=%1d",iResult);
		strcat(reponse,buf);

		iResult = ((CEquipAccord*)eqp)->Alarme(ALARME_TMP);
		sprintf(buf," STMP=%1d",iResult);
		strcat(reponse,buf);

		type_trame = TS_ACQUITE;
		EnvoyerTS(reponse);
	}

	if(strncmp(mes+pos,"SWR",3)==0)
	{
		iResult = ((CEquipAccord*)eqp)->Tos();
		sprintf(reponse,"> SWR %1d.%1d",iResult/10,iResult%10);

		if(!((CEquipAccord*)eqp)->AutoTos())
		{
			strcat(reponse," !");

			if((((CEquipAccord*)eqp)->Accord()) == 2) // Accord Fin
				strcat(reponse," #");
		}
		type_trame = TS_ACQUITE;
		EnvoyerTS(reponse);
	}

	if(strncmp(mes+pos,"TUN",3)==0)
	{
		if((pcResult = strstr(mes+pos+3,"HALT"))!=0)
		{
			iResult = ((CEquipAccord*)eqp)->ChangeAccord(0,FALSE);
		}
		else
		{
			if((pcResult = strstr(mes+pos+3,"START"))!=0)
			{
				strcpy(reponse,"> TUN ");

				iResult = ((CEquipAccord*)eqp)->Etat();
				switch(iResult)
				{
					case 0:
						strcat(reponse,"U");
						break;
					case 1:
						strcat(reponse,"E10");
						break;
					case 2:
						strcat(reponse,"R3");
						break;
					case 3:
						strcat(reponse,"S");
						break;
					case 4:
						strcat(reponse,"P");
						break;
					case 5:
						strcat(reponse,"F");
						break;
					case 6:
						strcat(reponse,"X");
						break;
					case 7:
						strcat(reponse,"Y");
						break;
				}

				sprintf(buf," %2.2d.%3.3d %1d.%1d",
					((CEquipAccord*)eqp)->Frequence()/1000,
					((CEquipAccord*)eqp)->Frequence()%1000,
					((CEquipAccord*)eqp)->Tos() / 10,
					((CEquipAccord*)eqp)->Tos() % 10);
		
				strcat(reponse,buf);

				type_trame = TS_ACQUITE;
				EnvoyerTS(reponse);

				sscanf(pcResult+5,"%2d.%3d",&i,&j);
				valeur = i*1000 + j;
				iResult = ((CEquipAccord*)eqp)->ChangeFrequence(valeur,FALSE);

				Sleep(TEMPO_TRAVAIL);

				iResult = ((CEquipAccord*)eqp)->ChangeAccord(2,FALSE);
			}

			if((pcResult = strstr(mes+pos+3,"PRESET"))!=0)
			{

				sscanf(pcResult+6,"%2d.%3d",&i,&j);
				valeur = i*1000 + j;
				iResult = ((CEquipAccord*)eqp)->ChangeFrequence(valeur,FALSE);

				Sleep(TEMPO_TRAVAIL);
			}
		}

	// TS de finde test
		strcpy(reponse,"> TUN ");

		iResult = ((CEquipAccord*)eqp)->Etat();
		switch(iResult)
		{
				case 0:
					strcat(reponse,"U");
					break;
				case 1:
					strcat(reponse,"E10");
					break;
				case 2:
					strcat(reponse,"R3");
					break;
				case 3:
					strcat(reponse,"S");
					break;
				case 4:
					strcat(reponse,"P");
					break;
				case 5:
					strcat(reponse,"F");
					break;
				case 6:
					strcat(reponse,"X");
					break;
				case 7:
					strcat(reponse,"Y");
					break;
		}

		sprintf(buf," %2.2d.%3.3d %1d.%1d",
			((CEquipAccord*)eqp)->Frequence()/1000,
			((CEquipAccord*)eqp)->Frequence()%1000,
			((CEquipAccord*)eqp)->Tos() / 10,
			((CEquipAccord*)eqp)->Tos() % 10);
	
		strcat(reponse,buf);

		type_trame = TS_ACQUITE;
		EnvoyerTS(reponse);
	}

	if(strncmp(mes+pos,"ECH",3)==0)
	{
		valeur = atoi(mes+pos+3);
		iResult = ((CEquipAccord*)eqp)->ChangeEcho(valeur,FALSE);
		if(iResult >= 0)				// Modification acceptée
		{
			type_trame = TS_ACQUITE;
			sprintf(reponse,"> ECH %1d",valeur);
		}
		else
		{
			type_trame = TS_ACQUITE;
			strcpy(reponse,"? SYNTAX");
		}
		EnvoyerTS(reponse);
	}

	if(strncmp(mes+pos,"IDP",3)==0)
	{
		sscanf(mes+pos+3,"%1d%s",&valeur,reponse);

		strcpy(reponse,"> IDP ");
		iResult = ((CEquipAccord*)eqp)->Chaine(valeur,reponse+6);

		if(valeur && (int)strlen(reponse))
		{
				iResult = ((CEquipAccord*)eqp)->ChangeChaine(valeur,reponse,FALSE);
				strcpy(reponse,"> IDP");
		}
		if(iResult<0)
		{
			strcpy(reponse,"? SYNTAX");
		}
		type_trame = TS_ACQUITE;
		EnvoyerTS(reponse);
	}
	if(strncmp(mes+pos,"MCL",3)==0)
	{
		valeur = atoi(mes+pos+3);
		iResult = ((CEquipAccord*)eqp)->ChangeInductance(valeur,FALSE);
		if(iResult>=0)
		{
			((CEquipAccord*)eqp)->ChangeAutoInduc(0,FALSE);
			strcpy(reponse,"> MCL");
			type_trame = TS_ACQUITE;
			EnvoyerTS(reponse);
		}
		else
		{
			strcpy(reponse,"? SYNTAX");
			type_trame = TS_ACQUITE;
			EnvoyerTS(reponse);
		}
	}

	if(strncmp(mes+pos,"MCP",3)==0)
	{
		valeur = atoi(mes+pos+3);
		iResult = ((CEquipAccord*)eqp)->ChangeCapacite(valeur,FALSE);
		if(iResult>=0)
		{
			((CEquipAccord*)eqp)->ChangeAutoCapa(0,FALSE);
			strcpy(reponse,"> MCP");
			type_trame = TS_ACQUITE;
			EnvoyerTS(reponse);

		}
		else
		{
			strcpy(reponse,"? SYNTAX");
			type_trame = TS_ACQUITE;
			EnvoyerTS(reponse);
		}
	}

	if(strncmp(mes+pos,"PRE",3)==0)
	{
		iResult = sscanf(mes+pos+3,"%s %d %d",buf,&i,&j);

		strcpy(reponse,"> PRE ");
		if(	(strstr(buf,"HALT")!=0 ||
			strstr(buf,"ABORT")!=0 ||
			strstr(buf,"XFERU")!=0 ||
			strstr(buf,"XFERS")!=0 ||
			strstr(buf,"RST")!=0) && iResult == 1 )
		{
		}
		else
		{
			if(	strstr(buf,"START")!=0 && iResult >=1)
			{	
				iResult = ((CEquipAccord*)eqp)->ChangeAccord(2,FALSE);
			}
			else
			{
				iResult = -1;
			}
		}

		if(iResult >=0)
		{
			iResult = ((CEquipAccord*)eqp)->Etat();
			switch(iResult)
			{
				case 0:
					strcat(reponse,"U");
					break;
				case 1:
					strcat(reponse,"E0");
					break;
				case 2:
					strcat(reponse,"R2:4");
					break;
				case 3:
					strcat(reponse,"A");
					break;
				case 4:
					strcat(reponse,"H3:4");
					break;
				case 5:
					strcat(reponse,"F");
					break;
			}
			type_trame = TS_ACQUITE;
		}
		else
		{
			type_trame = TS_ACQUITE;
			strcpy(reponse,"? SYNTAX");
		}

		EnvoyerTS(reponse);
	}

	if(strncmp(mes+pos,"TST",3)==0)
	{
		Sleep(TEMPO_TRAVAIL);

		sprintf(reponse,"> TST GL=%1d RL=%3.3X RC=%2.2X RM=%1d AN=%1d SP=%1d CPU=%1d",
			((CEquipAccord*)eqp)->Alarme(ALARME_ALIM) || ((CEquipAccord*)eqp)->Alarme(ALARME_CPU),			// Défaut d'état général
			0,			// Pas de défaut de relais L
			0,			// Pas de défaut de relais C
			0,			// Pas de défaut du relais RM 
			0,			// Pas de défaut du systeme de mesure
			((CEquipAccord*)eqp)->Alarme(ALARME_ALIM),
			((CEquipAccord*)eqp)->Alarme(ALARME_CPU)	);
		type_trame = TS_ACQUITE;
		EnvoyerTS(reponse);
	}

	return iResult;
}

/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
int CProtoAccord:: TraiteTS(int type_cde,char *reponse)
{
	int		num,iResult;

	strcpy(reponse,"");
	switch(type_cde)
	{
		case ACD_ALARME:
			num = ((CEquipAccord*)eqp)->SelecteAlarme();

			iResult = ((CEquipAccord*)eqp)->Alarme(num);
			sprintf(reponse,"ALM%2.2d %1d Information complémentaire",num,iResult);
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
int CProtoAccord::RecevoirTC(char *message,int nb_car)
{
	char	buf[TAILLE_BUFFER+1];
	int		i,iResult;
	int		ec = ((CEquipAccord*)eqp)->Echo();

	if(nb_car > TAILLE_BUFFER) return ERR_TAILLE_BUFFER;

	i=0;
	while(i<nb_car)
	{
		iResult = ligne.Lire(buf+i,1);
		if(iResult < 0) return ERREUR_EXTERNE+iResult;
		if(iResult == 0) return ERREUR_TIMEOUT;

		if(ec) ligne.EcritCar(buf[i]);

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
BOOL CProtoAccord::ValideAcquittement(int type_cde,char *buf)
{
	int		iResult = NULL;
	BOOL	bResult;

	if(!erreur_com.controle_parite)	return TRUE;

	bResult = TRUE;
/*	switch(type_cde)
	{
		case CDE_MODE_RECEP:
			if(strcmp(buf,"m") != 0)	bResult = FALSE;
			break;
		default:
			break;
	}
*/

	return bResult;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
char* CProtoAccord::ControleTrame(char *message,char *octet_controle)
{
	int		i,len_mes;
	int		pc;

	if(((CEquipAccord*)eqp)->Manuel())
	{
		strcpy(octet_controle,"");
		return octet_controle;
	}

	strcpy(octet_controle,"F");
	if(erreur_com.controle_parite) 	return octet_controle;

	len_mes = (int)strlen(message);

	pc = 0;
	i=0;
	while(i<len_mes)
	{	
		pc = (pc + message[i]) % 256;
		i++;
	}
		
	if(pc < 32) pc += 32;

	sprintf(octet_controle,"%c",pc);
	return octet_controle;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
BOOL CProtoAccord::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	char 	octet_controle[2];
	int		len_mes;
	int		avec_checksum = !((CEquipAccord*)eqp)->Manuel();

	len_mes = (int)strlen(buf);		
	if(buf[0] != DEBUT_TRAME && buf[len_mes -1] != FIN_TRAME)
		return FALSE;

	strcpy(message,"");
	strncat(message,buf+1,len_mes -2 			// sans debut et fin de trame
	 			-avec_checksum);			 	// et sans checkSum

	*long_utile = (int)strlen(message);

  	if(avec_checksum)
	{
  		ControleTrame(message+1,octet_controle);
		if(!erreur_com.controle_parite)	
			if(buf[1+(int)strlen(message)]!=octet_controle[0]) return FALSE;
	}

	return TRUE;
}

