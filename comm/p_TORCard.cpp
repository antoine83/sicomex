// p_TORCard.cpp: implementation of the CProtoTORCard class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Comm\p_TORCard.h"
#include "Equip\EqpTORCard.h"
#include "divers\div_tmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int 	DEBUT_TRAME = 0x01;	// Caractere de debut de trame
const int 	FIN_TRAME 	= 0x04;	// Caractere de fin de trame
const int   IDENTIFIER_SIZE = 3; // Nombre de caractères pour une trame.
const char *SEPARATOR = ";"; // Le separateur de parametres.

/* **************************************************************************
METHODE :		CProtoTORCard()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProtoTORCard::CProtoTORCard(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;
}

/* **************************************************************************
METHODE :		~CProtoTORCard()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProtoTORCard::~CProtoTORCard()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProtoTORCard::EnvoyerTS(char *message)
{
	int  iResult, nbChar = strlen(message);
	// Nombre de caractere envelopant le message
	char *buf = new char[nbChar + 2];

	if(nbChar > TAILLE_BUFFER - 2)
	{
		return ERR_TAILLE_BUFFER;
	}

	memcpy(buf + 1,message,nbChar);
	buf[0] = DEBUT_TRAME;
	buf[nbChar + 1] = FIN_TRAME;

	iResult = ligne.Ecrire(buf, nbChar + 2);
	if(iResult < 0) return ERREUR_EXTERNE+iResult;

	// nb d'octet transmis
	return iResult;
}

/* **************************************************************************
METHODE :		encodeStatus(BOOL value)
TRAITEMENT:		Retourne ON si la valeur est egale a TRUE, OFF sinon.
***************************************************************************	*/
char * CProtoTORCard::encodeStatus(BOOL value)
{
    if (value) {
        return "ON";
    }
    return "OFF";
}

/* **************************************************************************
METHODE :		decodeStatus(char *value)
TRAITEMENT:		Retourne TRUE si la valeur est egale a ON, FALSE sinon.
***************************************************************************	*/
BOOL CProtoTORCard::decodeStatus(char * value)
{
    if (strcmp(value, "ON")==0) {
        return TRUE;
    }
    return FALSE;
}

/* **************************************************************************
METHODE :		isValidStatus(char *value)
TRAITEMENT:		Retourne TRUE si la value est egale a ON ou OFF
***************************************************************************	*/
BOOL CProtoTORCard::isValidStatus(char *value)
{
	if ((strcmp(value, "ON") == 0)
		|| (strcmp(value, "OFF") == 0)) {
		return TRUE;
	}
	return FALSE;
}

/* **************************************************************************
METHODE :		TraiteTC(char *mes)
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquittement
***************************************************************************	*/
int CProtoTORCard::TraiteTC(char *mes)
{
	// Tester pas de contenu.
	if ( mes[0] == 0 ) {
		return ERR_CDE_INCONNUE;
	}

	// Index pour parcourir les tableaux.
	short index = 0;
	int returnCode = 0;
	int commandLength = strlen(mes);
	char *tmpMessage = NULL;
	char *temp = NULL;

	// Variables pour les acquittements negatifs
	BOOL isValid = true;
	char * relatedCommandId;
	int  errorCause = -1;

	// Tester la taille minimum d'une commande.
	if (commandLength < IDENTIFIER_SIZE) {
		return ERR_CDE_INCONNUE;
	}

	// Creer ma reponse.
	char reponse [TAILLE_BUFFER + 1];

	// Placer la commande dans le buffer temporaire.
	tmpMessage = (char *)malloc(sizeof(char) * (commandLength + 1));
	strcpy(tmpMessage, mes);

	// Identifiant de la commande.
	relatedCommandId = strtok(tmpMessage, SEPARATOR);
	if (relatedCommandId == NULL
			|| strlen(relatedCommandId) != IDENTIFIER_SIZE) {
		// Commande invalide.
		isValid = false;
		// Cause de l'erreur.
		errorCause = INVALID_IDENTIFIER;
	} else if(strcmp(relatedCommandId,"GCS")==0) {
	    // *** GetCardStatus.
		if (commandLength == IDENTIFIER_SIZE) {
			strcpy(reponse,"gcs");
		} else {
		    // Commande invalide.
		    isValid = false;
			// Cause de l'erreur.
			errorCause = INVALID_COMMAND_FORMAT;
		}
	} else if(strcmp(relatedCommandId,"GAO")==0) {
	    // *** GetAllOutput.
		if (commandLength == IDENTIFIER_SIZE) {
			strcpy(reponse,"gao");
			// Recuperer toutes les sorties.
			for(index = 0; index < OUTPUT_COUNT ; index++) {
			   strcat(reponse, SEPARATOR);
			   strcat(reponse, encodeStatus(((CEquipTORCard *)eqp)->getOutputValue(index)));
			}
		} else {
		    // Commande invalide.
		    isValid = false;
			// Cause de l'erreur.
			errorCause = INVALID_COMMAND_FORMAT;
		}
	} else if(strcmp(relatedCommandId,"GSO")==0) {
	    // *** GetSingleOutput.
		temp = strtok(NULL, SEPARATOR);
		if (temp == NULL) {
			// Commande invalide.
			isValid = false;
			// Cause de l'erreur.
			errorCause = INVALID_COMMAND_FORMAT;
        } else {
           int output = atoi(temp);
           if (output < 0 || output >= OUTPUT_COUNT) {
			// Commande invalide.
			isValid = false;
			// Cause de l'erreur.
			errorCause = INVALID_OUTPUT;
           } else {
              // Id de la reponse.
		      strcpy(reponse,"gso");
		      // Separateur.
	          strcat(reponse, SEPARATOR);
			  // Recuperer et encoder le numero de sortie.
			  strcat(reponse, temp);
		      // Separateur.
	          strcat(reponse, SEPARATOR);
	          // Recuperer et encoder la sortie.
	          strcat(reponse, encodeStatus(((CEquipTORCard *)eqp)->getOutputValue(output)));
		   }
        }
	} else if(strcmp(relatedCommandId,"SAO")==0) {
	    // SetAllOutput.
		for (index = 0 ; index < OUTPUT_COUNT; index ++) {
			temp = strtok(NULL, SEPARATOR);
			if (temp == NULL) {
				// Commande invalide.
				isValid = false;
				// Cause de l'erreur
				errorCause = INVALID_OUTPUT;
				break;
			} else {
				if (isValidStatus(temp)) {
					((CEquipTORCard *)eqp)->setOutput(index, decodeStatus(temp));
				} else {
					// Commande invalide.
					isValid = false;
					// Cause de l'erreur.
					errorCause = INVALID_OUTPUT_VALUE;
					break;
				}
			}
		}
		// Si la commande est valide.
		if (isValid) {
			strcpy(reponse, "sao");
			strcat(reponse, mes + IDENTIFIER_SIZE);
		}
	} else if(strcmp(relatedCommandId,"SSO")==0) {
	    // SetSingleOutput.
		int output = atoi(strtok(NULL, SEPARATOR));
		if (output < 0 || output >= OUTPUT_COUNT) {
			isValid = false;
			errorCause = INVALID_OUTPUT;
		} else {
			temp = strtok(NULL, SEPARATOR);
			if (isValidStatus(temp)) {
				((CEquipTORCard *)eqp)->setOutput(output, decodeStatus(temp));
				strcpy(reponse, "sso");
				strcat(reponse, SEPARATOR);
				sprintf(reponse, "%s%d%s%s", reponse, output, SEPARATOR, temp);
			} else {
				// Commande invalide.
				isValid = false;
				// Cause de l'erreur.
				errorCause = INVALID_OUTPUT_VALUE;
			}
		}
	} else if(strcmp(relatedCommandId,"GAI")==0) {
	    // GetAllInput.
		if (commandLength == IDENTIFIER_SIZE) {
			strcpy(reponse,"gai");
			// Recuperer toutes les sorties.
			for(index = 0; index < INPUT_COUNT ; index++) {
				strcat(reponse, SEPARATOR);
				strcat(reponse, encodeStatus(((CEquipTORCard *)eqp)->getInputValue(index)));
			}
		} else {
		    // Commande invalide.
		    isValid = false;
			// Cause de l'erreur.
			errorCause = INVALID_COMMAND_FORMAT;
		}
	} else if(strcmp(relatedCommandId,"GSI")==0) {
	    // GetSingleInput.
		temp = strtok(NULL, SEPARATOR);
		if (temp == NULL) {
			// Commande invalide.
			isValid = false;
			// Cause de l'erreur.
			errorCause = INVALID_COMMAND_FORMAT;
        } else {
           int input = atoi(temp);
           if (input < 0 || input >= INPUT_COUNT) {
			// Commande invalide.
			isValid = false;
			// Cause de l'erreur.
			errorCause = INVALID_INPUT;
           } else {
              // Id de la reponse.
		      strcpy(reponse,"gsi");
		      // Separateur.
	          strcat(reponse, SEPARATOR);
			  // Recuperer et encoder le numero de sortie.
			  strcat(reponse, temp);
		      // Separateur.
	          strcat(reponse, SEPARATOR);
	          // Recuperer et encoder l'entree.
	          strcat(reponse, encodeStatus(((CEquipTORCard *)eqp)->getInputValue(input)));
		   }
        }
	} else if(strcmp(relatedCommandId,"SIM")==0) {
	    // SetInputMask.
		for (index = 0 ; index < INPUT_COUNT; index ++) {
			temp = strtok(NULL, SEPARATOR);
			if (temp == NULL) {
				// Commande invalide.
				isValid = false;
				// Cause de l'erreur
				errorCause = INVALID_INPUT_MASK;
				break;
			} else {
				if (isValidStatus(temp)) {
					((CEquipTORCard *)eqp)->setInputMask(index, decodeStatus(temp));
				} else {
					// Commande invalide.
					isValid = false;
					// Cause de l'erreur.
					errorCause = INVALID_INPUT_MASK;
					break;
				}
			}
		}
		if (isValid) {
			strcpy(reponse, "sim");
			strcat(reponse, mes + IDENTIFIER_SIZE);
		}
	} else if(strcmp(relatedCommandId,"ERK")==0) {
	    // ERasingKey.
		if (commandLength == IDENTIFIER_SIZE) {
			// Effaccement des cles.
			((CEquipTORCard *)eqp)->clearKeys();
			// Encoder la reponse.
			strcpy(reponse, "erk");
		} else {
		    // Commande invalide.
		    isValid = false;
			// Cause de l'erreur.
			errorCause = INVALID_COMMAND_FORMAT;
		}
	} else if(strcmp(relatedCommandId,"GLK")==0) {
	    // GetLastKey.
		// Encoder la reponse.
		strcpy(reponse,"glk");
		strcat(reponse, SEPARATOR);
		// Ajouter la derniere cle.
		sprintf(reponse,"%s%d", reponse, ((CEquipTORCard *)eqp)->getKey());
	} else if(strcmp(relatedCommandId,"SLK")==0) {
	    // SetLastKey.
		// Recuperer le prochain parametre.
		temp = strtok(NULL, SEPARATOR);
        if (temp == NULL) {
		    // Commande invalide.
		    isValid = false;
			// Cause de l'erreur.
			errorCause = INVALID_COMMAND_FORMAT;
        } else {
			short key = atoi(temp);
			if (((CEquipTORCard *)eqp)->setKey(key)) {
				sprintf(reponse, "slk%s%d", SEPARATOR, key);
			} else {
				// Commande invalide.
				isValid = false;
				// Cause de l'erreur.
				errorCause = INVALID_KEY;
			}
		}
	} else {
		// Commande invalide.
		isValid = false;
		// Cause de la commande invalide.
		errorCause = INVALID_IDENTIFIER;
	}

	if ( ! isValid ) {
		// Creer l'acquittement négatif.
		sprintf(reponse, "nak%s%s%s%d", SEPARATOR, relatedCommandId, SEPARATOR, errorCause);
		// Retourner valeur commande inconnue.
		returnCode = ERR_CDE_INCONNUE;
	}

	// Envoyer la reponse
	EnvoyerTS(reponse);
	// Liberation du buffer temporaire.
	free(tmpMessage);

	return returnCode;
}

/* **************************************************************************
METHODE :		TraiteTS(int type_cde,char *reponse)
TRAITEMENT:		Formate une TS en fonction en recuperant les etats internes
				de l'equipement
***************************************************************************	*/
int CProtoTORCard:: TraiteTS(int type_cde,char *reponse)
{
	int		iResult = 1;

	strcpy(reponse,"");
	switch(type_cde/100) {

		case TS_TOR_ISC:
			{
				int input = type_cde % 100;
				strcpy(reponse, "ISC");
				strcat(reponse, SEPARATOR);
				// Recuperer et encoder l'entree.
				sprintf(reponse, "%s%d%s%s", reponse, input, SEPARATOR, encodeStatus(((CEquipTORCard *)eqp)->getInputValue(input)));
			}
			break;

		default:
			iResult = ERR_CDE_INCONNUE;
			break;
	}

	return iResult;
}

/* **************************************************************************
METHODE :		RecevoirTC(char *message,int nb_car)
TRAITEMENT:		Receptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProtoTORCard::RecevoirTC(char *message,int nb_car)
{
	char buf[TAILLE_BUFFER+1];
	int	 i,iResult;

	if(nb_car > TAILLE_BUFFER)
	{
		return ERR_TAILLE_BUFFER;
	}

	// Clear the last message.
	char zero = 0;
	memcpy(message,&zero, TAILLE_BUFFER + 1);

	i=0;
	while(i<nb_car)
	{
		iResult = ligne.Lire(buf+i,1);
		if(iResult < 0)
		{
			return ERREUR_EXTERNE+iResult;
		}
		// If the timeout is reached. exit.
		if(iResult == 0)
		{
			break;
		}

		i++;
	}

	// If there is no characters return.
	if ( i == 0 ) {
		return ERREUR_TIMEOUT;
	}

	// Message non conforme
	if(!ExtraitUtile(buf,message,&i))
	{
		return ERR_NON_CONFORME;
	}

	return iResult;
}

/* **************************************************************************
METHODE :		ValideAcquittement(int type_cde,char *buf)
TRAITEMENT:		Attend un message d'acquittement du type de commande precedement
				envoye comme TS Maitre
***************************************************************************	*/
BOOL CProtoTORCard::ValideAcquittement(int type_cde,char *buf)
{
	return TRUE;
}

/* **************************************************************************
METHODE :		ExtraitUtile(char *buf,char *message,int *long_utile)
TRAITEMENT:		Extrait les octets utiles
***************************************************************************	*/
BOOL CProtoTORCard::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	int	 len_mes;			//int	 len_mes,nb_tranche;		//2009-11-27

	len_mes = (int)strlen(buf);

	// Verifier le buffer.
	if(buf[0] != DEBUT_TRAME && buf[len_mes -1] != FIN_TRAME)
	{
		return FALSE;
	}

	// Calcul de la taille utile du message.
	*long_utile = len_mes - 2;
	strcpy(message,"");
	strncat(message,buf+1,*long_utile);

	return TRUE;
}
