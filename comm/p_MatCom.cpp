/* **************************************************************************
FICHIER :	p_MatCom.CPP		 			AUTEUR : FSA
DATE DE CREATION : 	26/02/07			DERNIERE MODIFICATION : 26/02/07
VERSION :	1.0
ROLE :		Implémentation de la classe CProtoCommutationMatrix
***************************************************************************	*/

#include "stdafx.h"

#include "Comm\p_MatCom.h"
#include "Equip\EqpMatCom.h"
#include "divers\div_tmp.h"

const char 	DEBUT_TRAME = '#';
const int 	FIN_TRAME 	= 0xD;

const char SEPARATOR = ';';
const char * REMOTE_COMMAND_HEADER = "#>";

/* **************************************************************************
METHODE :		CProtoCommutationMatrix()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProtoCommutationMatrix::CProtoCommutationMatrix(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;
}

/* **************************************************************************
METHODE :		~CProtoCommutationMatrix()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProtoCommutationMatrix::~CProtoCommutationMatrix()
{
	// Do nothing.
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProtoCommutationMatrix::EnvoyerTS(char *message)
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
int CProtoCommutationMatrix::TraiteTC(char *mes)
{
	int		iResult = 0;
	char	reponse[TAILLE_PIPE_MESSAGE+1];

	memset(reponse, '\0', TAILLE_PIPE_MESSAGE+1);

	// If the equipment in local mode. do nothing.
	if ( ((CEquipCommutationMatrix *) eqp)->isLocal() ) {
		return ERR_PAS_ACQUITTE;
	}

	// Set the response header.
	strcpy(reponse,"<");

	switch(mes[0]) {
	// Configure input remote command.
	case 'N':
		if ( (strlen(mes) < 6) ||(mes[1]!=SEPARATOR) ) {
			strcat(reponse,"n;KO");
		} else {
			int identifier = 0;
			char name[MAX_NAME_COUNT + 1] = "\0";
			sscanf(mes + 5, "%2d;%11s", &identifier, &name);
			if (mes[2] == 'E' ) {
				((CEquipCommutationMatrix *) eqp)->setInputName(identifier, name);
				strcat(reponse,"n;OK");
			} else if (mes[2] == 'S') {
				((CEquipCommutationMatrix *) eqp)->setOutputName(identifier, name);
				strcat(reponse,"n;OK");
			} else {
				strcat(reponse,"n;KO");
			}
		}
		break;
	case 'A':
		// Unused yet.
		break;
	// Data type remote command.
	case 'T':
		if ( (mes[1]!=SEPARATOR) || (mes[7]!='6') ) {
			strcat(reponse,"t;KO");
		} else {
			if (strncmp( mes + 2, "DATA", 4) == 0) {
				((CEquipCommutationMatrix *) eqp)->setType(DATA_MATRIX);
				strcat(reponse,"t;OK");
			} else if (strncmp(mes+2, "DATA", 4) == 0) {
				((CEquipCommutationMatrix *) eqp)->setType(RADIO_MATRIX);
				strcat(reponse,"t;OK");
			} else {
				strcat(reponse,"t;KO");
			}
		}
		break;
	// Connection remote command.
	case 'C':
		if ( (strlen(mes)!=8) ||(mes[1]!=SEPARATOR)) {
			strcat(reponse,"c;KO");
		} else {

			CEquipCommutationMatrix * pMatrix = ((CEquipCommutationMatrix *) eqp);
		
			int outputId = 0;
			int inputId = 0;
			char direction = 'U';

			sscanf(mes + 2, "%2d;%1c%2d", &inputId, &direction, &outputId);

			 if (direction == 'R' && pMatrix->setReceptionConnection(inputId, outputId)) {
				strcat(reponse,"c;OK");
			} else if ((direction == 'E') && pMatrix->setEmissionConnection(inputId, outputId)) {
				strcat(reponse,"c;OK");
			} else {
				strcat(reponse,"c;KO");
			}
		}
		break;
	// Disconnection remote command.
	case 'D':
		// Control the validity
		if ( (strlen(mes)!=8) || (mes[1]!=SEPARATOR) ) {
			strcat(reponse,"d;KO");
		} else {
			int inputId = 0, outputId = 0;
			char direction = 'U';
			// Get the values.
			sscanf(mes + 2, "%2d;%1c%2d", &inputId, &direction, &outputId);
			// call methods.
			if (direction == 'E') {
				if(((CEquipCommutationMatrix *) eqp)->getEmissionConnection(inputId)==outputId)
				{
					((CEquipCommutationMatrix *) eqp)->disconnectEmission(inputId, outputId);
					strcat(reponse,"d;OK");
				}
				else
				{
					strcat(reponse,"d;KO");
				}
			} else if ( direction == 'R' ) {
				if(((CEquipCommutationMatrix *) eqp)->getReceptionConnection(inputId)==outputId)
				{
					((CEquipCommutationMatrix *) eqp)->disconnectReception(inputId, outputId);
					strcat(reponse,"d;OK");
				}
				else
				{
					strcat(reponse,"d;KO");
				}
			} else {
				strcat(reponse,"d;KO");
			}
		}
		break;
	case 'P':
		// Control the frame.
		if ( (((strlen(mes) - 4) % 12) != 0)
			|| (mes[1] != SEPARATOR) ) {
			strcat(reponse,"p;KO");
		} else {
			bool hasError = false;
			char * pointer = mes + 2;
			char * lastOffset = mes + strlen(mes);
			int presetId = 0;
			CommutationMatrixPreset preset;

			preset.setSetted(true);
			sscanf(pointer, "%2d", &presetId );

			pointer += 2;
			// Read each uplink.
			while (pointer < lastOffset) {
				int uplinkId = 0;
				if ( !testSeparator(pointer) ) {
					hasError = true;
					break;
				}
				pointer++;
				if ( (*pointer) != 'C') {
					hasError = true;
					break;
				}
				pointer++;
				sscanf(pointer, "%2d", &uplinkId );
				pointer+=2;
				if ( !testSeparator(pointer) ) {
					hasError = true;
					break;
				}
				pointer++;
				if ( (*pointer) != 'E') {
					hasError = true;
					break;
				}
				pointer++;
				sscanf(pointer, "%2d", &(preset.emissionConnections[uplinkId - 1]) );
				pointer+=2;
				if ( !testSeparator(pointer) ) {
					hasError = true;
					break;
				}
				pointer++;
				if ( (*pointer) != 'R') {
					hasError = true;
					break;
				}
				pointer++;
				sscanf(pointer, "%2d", &(preset.receptionConnections[uplinkId - 1]) );
				pointer+=2;
			}
			if ( (hasError)
				|| !((CEquipCommutationMatrix *) eqp)->setPreset(presetId,preset) ) {
				strcat(reponse,"p;KO");
			} else {
				strcat(reponse,"p;OK");
			}
		}
		break;
	case 'R':
		// Control the frame.
		if ( (strlen(mes)!=4) || (mes[1]!=SEPARATOR) ) {
			strcat(reponse,"r;KO");
		} else {
			short id = 0;
			sscanf(mes + 2, "%2d", &id );
			// Remove the preset.
			if ( ((CEquipCommutationMatrix *) eqp)->restorePreset(id) ) {
				strcat(reponse,"r;OK");
			} else {
				strcat(reponse,"r;KO");
			}
		}
		break;
	case 'K':
		// Control the frame.
		if ( (strlen(mes)!=4) || (mes[1]!=SEPARATOR) ) {
			strcat(reponse,"k;KO");
		} else {
			short id = 0;
			sscanf(mes + 2, "%2d", &id );
			// Remove the preset.
			if ( ((CEquipCommutationMatrix *) eqp)->removePreset(id) ) {
				strcat(reponse,"k;OK");
			} else {
				strcat(reponse,"k;KO");
			}
		}
		break;
	// The read current connections remote command.
	case 'V':
		if (strlen(mes)!=1) {
			strcat(reponse,"v;KO");
		} else {
			for(short eachUplink = 0 ; eachUplink < RECEPTACLE_COUNT ; eachUplink ++ )  {
				// Emission connection.
				strcpy(reponse,"<v;0");
				sprintf(reponse,"%s%1d",reponse,eachUplink + 1);
				strcat(reponse,"E");
				int downlink = ((CEquipCommutationMatrix *) eqp)->getEmissionConnection(eachUplink + 1);
				if ( downlink > 0) {
					// No connection.
					sprintf(reponse,"%s;0%d",reponse,downlink);
				}
				EnvoyerTS(reponse);
				// Emission connection.
				strcpy(reponse,"<v;0");
				sprintf(reponse,"%s%1d",reponse,eachUplink + 1);
				strcat(reponse,"R");
				downlink = ((CEquipCommutationMatrix *) eqp)->getReceptionConnection(eachUplink + 1);
				if ( downlink > 0) {
					// No connection.
					sprintf(reponse,"%s;0%d",reponse,downlink);
				}
				EnvoyerTS(reponse);
			}
			return ERR_PAS_ACQUITTE;
		}
		break;
	// The command remote command.
	case 'M':
		{
			char command[5] = "NONE";
			sscanf(mes + 2, "%4s", command);
			if ( strcmp(command,"INIT") == 0 ) {
				((CEquipCommutationMatrix *) eqp)->reset();
				return ERR_PAS_ACQUITTE;
			} else if ( strcmp(command, "TCPL") == 0 ) {
				((CEquipCommutationMatrix *) eqp)->testMatrix();
				strcat(reponse,"m;"+((CEquipCommutationMatrix *) eqp)->GetEdit());
			} else {
				strcat(reponse,"m;KO");
			}
		}
		break;
	default:
		return ERR_CDE_INCONNUE;
	}

	// Send the TS.
	EnvoyerTS(reponse);

	return iResult;
}

bool CProtoCommutationMatrix::testSeparator(char *here) {
	if ( here[0] == SEPARATOR) {
		return true;
	}
	return false;
}

/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
int CProtoCommutationMatrix:: TraiteTS(int type_cde,char *reponse)
{
	int		iResult = 0;
	// Do nothing.
	return iResult;
}

/* **************************************************************************
METHODE :		RecevoirTC()
TRAITEMENT:		Réceptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProtoCommutationMatrix::RecevoirTC(char *message,int nb_car)
{
	char	buf[TAILLE_BUFFER+1];
	int		i,iResult;

	if(nb_car > TAILLE_BUFFER) return ERR_TAILLE_BUFFER;

	// Read on the port.
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

	// Get the remote command message.
	if(!ExtraitUtile(buf,message,&iResult)) 
		return ERR_NON_CONFORME;

	return iResult;
}

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Attend un message d'acquitement du type de commande précedement
				envoyé comme TS Maitre
***************************************************************************	*/
BOOL CProtoCommutationMatrix::ValideAcquittement(int type_cde,char *buf)
{
	BOOL bResult = TRUE;
	
	// Do nothing.

	return bResult;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
BOOL CProtoCommutationMatrix::ExtraitUtile(char *buf,char *message,int *long_utile) {
	int headerLength = strlen(REMOTE_COMMAND_HEADER);
	int bufferLength = strlen(buf);
	if (bufferLength < headerLength) {
		return false;
	}
	if (strncmp(buf,REMOTE_COMMAND_HEADER,headerLength) != 0) {
		return false;
	}
	strcpy(message, "");
	strncat(message, buf+headerLength, bufferLength - headerLength - 1);
	(*long_utile) = bufferLength - headerLength - 1;
	return true;
}

