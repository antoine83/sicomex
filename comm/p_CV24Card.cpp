// p_CA150.cpp: implementation of the CProtoCV24Card class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Comm\p_CV24Card.h"
#include "Equip\EqpCV24Card.h"
#include "divers\div_tmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int 	DEBUT_TRAME = 0xD;	// Caractere de debut de trame
const int 	FIN_TRAME 	= 0xA;	// Caractere de fin de trame

/* **************************************************************************
METHODE :		CProtoCV24Card()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProtoCV24Card::CProtoCV24Card(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;
	// TODO : integrer ici le constructeur
}

/* **************************************************************************
METHODE :		~CProtoCV24Card()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProtoCV24Card::~CProtoCV24Card()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProtoCV24Card::EnvoyerTS(char *message, int nbChar)
{
	int  iResult;
	// Nombre de caractere envelopant le message
	char *buf = new char[nbChar];

	if(nbChar > TAILLE_BUFFER)
	{
		return ERR_TAILLE_BUFFER;
	}

	memcpy(buf,message,nbChar);

	iResult = ligne.Ecrire(buf, nbChar);
	if(iResult < 0) return ERREUR_EXTERNE+iResult;

	// nb d'octet transmis
	return iResult;
}

/**
 * Send the response for the RC 'mes'.
 * Set the MSB null.
 */
void CProtoCV24Card::sendResponse(char *mes) {
	mes[0] &= 127;
	EnvoyerTS(mes, 1);
}

/* **************************************************************************
METHODE :		TraiteTC(char *mes)
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquittement
***************************************************************************	*/
int CProtoCV24Card::TraiteTC(char *mes)
{
	if ( mes[0] == 0 ) {
		return ERR_CDE_INCONNUE;
	}

	BOOL isValid = true;

	// Get the message type.
	// The MSB is 1.
	if ( mes[0] >> 7 ) {
		// Get the command id.
		char identifier = ( ( mes[0] >> 5 ) & 3 );
		switch (identifier) {
			case 0:
				{
					// Set the output value.
					BOOL value = ( ( mes[0] >> 4 ) & 1 );
					char outputId = ( mes[0] & 15 );
					((CEquipCV24Card *) eqp)->setOutput(outputId, value);
					// Send the acknowledgement RS.
					sendResponse(mes);
				}
				break;
			case 1:
				{
					// Get the input identifier.
					char inputId = ( mes[0] & 31 );
					// Create the acknowlegement remote signalling.
					char response [TAILLE_BUFFER + 1];
					response[0] = ( mes[0] & 127);
					if ( inputId == 15 ) {
						if ( ((CEquipCV24Card *) eqp)->getType() == CV24_ANDVT ) {
							response[1] = 141;
						} else {
							response[1] = 143;
						}
					} else {
						if ( ((CEquipCV24Card *) eqp)->getInputValue(inputId) ) {
							response[1] = 255;
						} else {
							response[1] = 0;
						}
					}
					EnvoyerTS(response, 2);
				}
				break;
			case 2:
				{
					// Set the input value.
					BOOL value = ( ( mes[0] >> 4 ) & 1 );
					char inputId = ( mes[0] & 15 );
					((CEquipCV24Card *) eqp)->setInputMask(inputId, value);
					// Send the acknowledgement RS.
					mes[0] &= 127;
					mes[1] = (value) ? 255 : 0;
					EnvoyerTS(mes,2);
				}
				break;
			case 3:
				{
					BOOL reset = ( (mes[0] >> 3) & 1 );
					if ( reset) {
						// Do nothing yet.
						return ERR_CDE_INCONNUE;
					} else {
						BOOL request = ( ( mes[0] >> 4 ) & 1 );
						char keyId = ( mes[0] & 7 );
						if (request) {
							// Send the acknowledgement RS.
							mes[0] = ( mes[0] & 127);
							mes[1] = ((CEquipCV24Card *) eqp)->getKey();
							EnvoyerTS(mes,2);
						} else {
							((CEquipCV24Card *) eqp)->transferKey(keyId);
							// Send the acknowledgement RS.
							sendResponse(mes);
						}
					}
				}
				break;
			default:
				isValid = false;
		}
	// The 3 MSB are 010.
	} else if ( (mes[0] & 224) == 64) {
		// Get the command id.
		char identifier = ( mes[0] & 31 );
		switch(identifier) {
			case 0:
				((CEquipCV24Card *) eqp)->setStatus(true);
				// Send the acknowledgement RS.
				sendResponse(mes);
				break;
			case 1:
				((CEquipCV24Card *) eqp)->setStatus(false);
				// Send the acknowledgement RS.
				sendResponse(mes);
				break;
			case 4:
				((CEquipCV24Card *) eqp)->setOperatingMode(COMMAND_MODE);
				// Send the acknowledgement RS.
				sendResponse(mes);
				break;
			case 5:
				((CEquipCV24Card *) eqp)->setOperatingMode(TRANSFER_MODE);
				// Send the acknowledgement RS.
				sendResponse(mes);
				break;
			case 6:
				((CEquipCV24Card *) eqp)->clearKeys();
				// Send the acknowledgement RS.
				sendResponse(mes);
				break;
			case 7:
				((CEquipCV24Card *) eqp)->transferKey();
				// Send the acknowledgement RS.
				sendResponse(mes);
				break;
			case 15:
				// Send the acknowledgement RS.
				sendResponse(mes);
				break;
			default:
				isValid = false;
		}
	// The 2 MSB are 00.
	} else if ( (mes[0] & 192) == 0 ) {
		// Get the command id.
		char identifier = ( ( mes[0] >> 4 ) & 3 );
		char nbChar = (mes[0] & 15);
		switch(identifier) {
			case 0:
				{
					// Set all outputs values.
					int id;
					// Get 14 value.
					char value = ( ( mes[1] >> 6) & 1 );
					((CEquipCV24Card *) eqp)->setOutput(14, value);
					for (id = 7; id > -1 ; id--) {
						value = ( ( mes[2] >> (id) ) & 1 );
						((CEquipCV24Card *) eqp)->setOutput(id, value);
					}
					// Create the acknowlegement remote signalling.
					char response [TAILLE_BUFFER + 1];
					response[0] = 0;
					response[1] = 1;
					response[2] = 2;
					EnvoyerTS(response, 3);
				}
				break;
			case 1:
				// Read all inputs.
				{
					int id = 7;
					// The 15 entry is not used here.
					mes[1] = 255;
					mes[2] = 0;
					// Set the other values.
					for( ; id >= 0 ; id--) {
						mes[2] += ( ((CEquipCV24Card *) eqp)->getInputValue(id) << id );
					}
					EnvoyerTS(mes,3);
				}
				break;
			case 2:
				// Set all inputs mask.
				{
					int id;
					// Get 15 value.
					char value = ( ( mes[1] >> 7) & 1 );
					((CEquipCV24Card *) eqp)->setInputMask(15, value);
					for (id = 7; id > -1 ; id--) {
						value = ( ( mes[2] >> (id) ) & 1 );
						((CEquipCV24Card *) eqp)->setInputMask(id, value);
					}
					// Create the acknowlegement remote signalling.
					EnvoyerTS(mes, 3);
				}
				break;
			default:
				isValid = false;
		}
	} else {
		isValid = false;
	}

	if ( ! isValid ) {
		AjouterTS(NULL,TS_ERROR * 100 + 1);
		return ERR_CDE_INCONNUE;
	}

	return 1;
}

/* **************************************************************************
METHODE :		TraiteTS(int type_cde,char *reponse)
TRAITEMENT:		Formate une TS en fonction en recuperant les etats internes
				de l'equipement
***************************************************************************	*/
int CProtoCV24Card:: TraiteTS(int type_cde,char *reponse)
{
	int		iResult = 1;

	strcpy(reponse,"");
	switch(type_cde/100) {

		case TS_INT:
			{
				// The message is 1000xxxx
				char result = ( 1 << 7 ) + ( type_cde % 100 );
				reponse[0] = result;
				reponse[1] = 0;
			}
			break;

		case TS_ERROR:
			{
				// The message is 1100xxxx
				char result = ( 3 << 6 ) + ( type_cde % 100 ) ;
				reponse[0] = result;
				reponse[1] = 0;
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
int CProtoCV24Card::RecevoirTC(char *message,int nb_car)
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
BOOL CProtoCV24Card::ValideAcquittement(int type_cde,char *buf)
{
	return TRUE;
}

/* **************************************************************************
METHODE :		ExtraitUtile()
TRAITEMENT:		Extrait la partie utile du message
***************************************************************************	*/
BOOL CProtoCV24Card::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	memcpy(message,buf, *long_utile);
	return TRUE;
}
