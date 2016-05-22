/* **************************************************************************
FICHIER :	Prot_Aud.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CProtoAudio
***************************************************************************	*/

#include "stdafx.h"

#include "Comm\Prot_Aud.h"
#include "Equip\EqpAudi.h"
#include "divers\div_tmp.h"

const int 	CR 	= 0xD;
const int 	LF 	= 0xA;

/* **************************************************************************
METHODE :		CProtoAudio()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProtoAudio::CProtoAudio(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;
}

/* **************************************************************************
METHODE :		~CProtoAudio()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProtoAudio::~CProtoAudio()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProtoAudio::EnvoyerTS(char *message)
{
	int		len_mes,iResult;
	int		nb_car_enveloppe;		// Nombre de caractère envlopant le message

	char	buf[TAILLE_BUFFER+1];

	len_mes = (int)strlen(message);	// Taille du message à envoyer
	nb_car_enveloppe = 1 + 1; 		// CR+LF
												
	if(len_mes+nb_car_enveloppe > TAILLE_BUFFER)
		 return ERR_TAILLE_BUFFER;
	
	sprintf(buf,"%s%c%c",message,
		erreur_com.pas_debut ? 0 : CR,
		erreur_com.pas_fin ? 0 : LF);
	
	iResult = ligne.Ecrire(buf);
	if(iResult < 0) return ERREUR_EXTERNE+iResult;

	return iResult;  // nb d'octet transmis
}
/* **************************************************************************
METHODE :		TraiteTC()
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquitement
***************************************************************************	*/
int CProtoAudio::TraiteTC(char *mes)
{
	int		iResult = ERR_CDE_INCONNUE;
	int		x,y,valeur;
	char	reponse[TAILLE_PIPE_MESSAGE+1];

	strcpy(reponse,"");

	if(strstr(mes,"STO") != 0)
	{
		valeur = atoi(mes+3);
		iResult = 0;
		if(valeur<1 || valeur>99)	iResult = ERR_PAS_ACQUITTE;

		if(iResult >=0)
		{
			strcpy(reponse,"OK");
		}
		else
			strcpy(reponse,"E5100");
		EnvoyerTS(reponse);
	}

	if(strstr(mes,"REC") != 0)
	{
		valeur = atoi(mes+3);
		iResult = 0;
		if(valeur<1 || valeur >99)	iResult = ERR_PAS_ACQUITTE;

		if(iResult >=0)
		{
			strcpy(reponse,"OK");
		}
		else
			strcpy(reponse,"E5100");

		EnvoyerTS(reponse);
	}

	if(strcmp(mes,"RESET")==0)
	{
		iResult = ((CEquipAudio*)eqp)->Test();
		if(iResult>0)
		{
			AjouterTS(NULL,CDE_TEMPO_SEQ);
			AjouterTS(NULL,CDE_TEMPO_SEQ);
			AjouterTS(NULL,AUD_RESET);
		}
	}

	if(strcmp(mes,"CLEAR")==0)
	{
		for(x=0 ; x<MAX_CARTE ; x++)
			for(y=0 ; y<MAX_RELAIS ; y++)
				iResult = ((CEquipAudio*)eqp)->ChangeEtatRelais(x,y,0,FALSE);

		strcpy(reponse,"OK");
		EnvoyerTS(reponse);
	}

	switch(mes[0])
	{

		case 'L':
			valeur = atoi(mes+1);
			iResult = ((CEquipAudio*)eqp)->ChangeLock(valeur,FALSE);
			if(iResult<0) break;

			strcpy(reponse,"OK");
			EnvoyerTS(reponse);
 
			break;

		case 'U':
			if(strcmp(mes,"ULOCK")!=0)
			{
				iResult =  ERR_CDE_INCONNUE;
				break;
			}

			iResult = ((CEquipAudio*)eqp)->ChangeLock(0,FALSE);
			if(iResult<0) break;

			strcpy(reponse,"OK");
			EnvoyerTS(reponse);
 
			break;

		case 'X':
			x = atoi(mes+1);
			y =  atoi(mes+6);
			if(strstr(mes,"MS") != 0)
			{
				iResult = ((CEquipAudio*)eqp)->ChangeEtatRelais(x,y,1,FALSE);
				if(iResult >=0)
				{
					strcpy(reponse,"OK");
				}
				else
					strcpy(reponse,"E5100");
				EnvoyerTS(reponse);
			}
			if(strstr(mes,"MR") != 0)
			{
				iResult = ((CEquipAudio*)eqp)->ChangeEtatRelais(x,y,0,FALSE);
				if(iResult >=0)
				{
					strcpy(reponse,"OK");
				}
				else
					strcpy(reponse,"E5100");
				EnvoyerTS(reponse);
			}

			if(strstr(mes,"MV") != 0)
			{
				iResult = ((CEquipAudio*)eqp)->EtatRelais(x,y);
				if(iResult>=0)
				{
					if(iResult)
						strcpy(reponse,"Y");
					else
						strcpy(reponse,"N");
				}
				else
					strcpy(reponse,"E5100");

				EnvoyerTS(reponse);
			}
 
			break;

 		default:
			if(iResult<0)  		// n'est pas passer dans les if avant 
			{					// le switch
				iResult = ERR_CDE_INCONNUE;
			}
			break;
	}

	return iResult;
}

/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
int CProtoAudio:: TraiteTS(int type_cde,char *reponse)
{
	int		iResult;

	strcpy(reponse,"");
	switch(type_cde)
	{
		case AUD_RESET:
			iResult = ((CEquipAudio*)eqp)->Test();
			sprintf(reponse,"E%4.4d",iResult);
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
int CProtoAudio::RecevoirTC(char *message,int nb_car)
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
		if(buf[i]==LF) break;

		i++;
	}

	if(!ExtraitUtile(buf,message,&iResult)) 
		return ERR_NON_CONFORME;			// Message non conforme

	return iResult;
}

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Retourne toujours TRUE car n'attend pas d'acquitement
***************************************************************************	*/
BOOL CProtoAudio::ValideAcquittement(int type_cde,char *buf)
{
	return TRUE;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Retournes une chaine vide car aucun caratère de controle
				n'est demandé
***************************************************************************	*/
char* CProtoAudio::ControleTrame(char *message,char *octet_controle)
{
	strcpy(octet_controle,"");
	return octet_controle;
}

/* **************************************************************************
METHODE :		ExtraitUtile()
TRAITEMENT:		Extrait la partie utile d'une trame de télécommande
***************************************************************************	*/
BOOL CProtoAudio::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	char	*pcResult;
	char	fin_message[3];

	strcpy(message,"");
	sprintf(fin_message,"%c%c",CR,LF);

	pcResult = strstr(buf,fin_message);
	if(pcResult == NULL) return FALSE;

	*pcResult =0 ;		// force une fin de chaine
	strcpy(message,buf);

	*long_utile = (int)strlen(message);

	return TRUE;
}
