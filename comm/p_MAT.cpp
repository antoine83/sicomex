// p_MAT.cpp: implementation of the CProto_MAT class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Comm\p_MAT.h"
#include "Equip\EqpMAT.h"
#include "divers\div_tmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int SEPARE_TRAME	= 0x0D;	// Separateur de commande
const int FIN_TRAME		= 0x0A;	// Fin de transmission

/* **************************************************************************
METHODE :		CProto_MAT()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProto_MAT::CProto_MAT(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;
}

/* **************************************************************************
METHODE :		~CProto_MAT()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProto_MAT::~CProto_MAT()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProto_MAT::EnvoyerTS(char *message)
{
	int  len_mes,iResult;
	char buf[TAILLE_BUFFER+1];
	//char octet_controle[8];					//2009-11-27

	// Taille du message à envoyer
	len_mes = (int)strlen(message);
	if(len_mes > TAILLE_BUFFER)
	{
		return ERR_TAILLE_BUFFER;
	}

	sprintf(buf, "%s%c%c", message, SEPARE_TRAME, FIN_TRAME);

	iResult = ligne.Ecrire(buf);
	if(iResult < 0) return ERREUR_EXTERNE+iResult;

	// nb d'octet transmis
	return iResult;
}
/* **************************************************************************
METHODE :		TraiteTC(char *mes)
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquittement
***************************************************************************	*/
int CProto_MAT::TraiteTC(char *mes)
{
	int	 iResult = 0;
	int	 xx, yy;				//int	 valeur, i, j, xx, yy;	//2009-11-27
	//long long_valeur;						//2009-11-27
	long lResult = 0;
	char reponse[TAILLE_PIPE_MESSAGE+1];
	char cTemp[10];

	strcpy(reponse,"");

	// Demande d'enregistrement de la matrice
	if(strcmp(mes, "REC")==0)
	{
		((CEqpMAT*)eqp)->EnregistrerMatrice();
		EnvoyerTS("OK");
	}

	// Demande d'ouverture d'une matrice precedente
	if(strcmp(mes, "STO")==0)
	{
		((CEqpMAT*)eqp)->ChargerMatrice();
		EnvoyerTS("OK");
	}

	// Demande de connexion de l'entree xx sur la sortie yy
	if(mes[4] == 'C')
	{
		if( (isdigit(mes[0])) && (isdigit(mes[1])) && (isdigit(mes[2])) && (isdigit(mes[3])) )
		{
			sprintf(cTemp, "%c%c", mes[0], mes[1]);
			xx = atoi(cTemp);
			sprintf(cTemp, "%c%c", mes[2], mes[3]);
			yy = atoi(cTemp);
			((CEqpMAT*)eqp)->ChgtEtatMatrice(yy-1, xx-1);
			return 0;
		}
	}

	// Demande de deconnexion de l'entree xx sur la sortie yy
	if(mes[4] == 'D')
	{
		if( (isdigit(mes[0])) && (isdigit(mes[1])) && (isdigit(mes[2])) && (isdigit(mes[3])) )
		{
			sprintf(cTemp, "%c%c", mes[0], mes[1]);
			xx = atoi(cTemp);
			((CEqpMAT*)eqp)->DeconnexionMatrice(xx-1);
			return 0;
		}
	}

	// Demande de verification de l'entree xx sur la sortie yy
	if(mes[4] == 'V')
	{
		if( (isdigit(mes[0])) && (isdigit(mes[1])) && (isdigit(mes[2])) && (isdigit(mes[3])) )
		{
			sprintf(cTemp, "%c%c", mes[0], mes[1]);
			xx = atoi(cTemp);
			((CEqpMAT*)eqp)->VerifConnexionMatrice(xx-1);
			return 0;
		}
	}

	// Mise a zero de la matrice en retirant toutes les connexions
	if(strcmp(mes,"CLEAR")==0)
	{
		((CEqpMAT*)eqp)->ResetMatrice();
		EnvoyerTS("OK");
		return 0;
	}

	// Envoi l'etat general de la matrice
	if(strcmp(mes,"DUMPA")==0)
	{
		((CEqpMAT*)eqp)->EtatMatrice();
		EnvoyerTS("OK");
		return 0;
	}

	// Verrouille la face avant
	if(strcmp(mes,"LOCKF")==0)
	{
		// TODO : Trouver la fonction du verrouillage
		((CEqpMAT*)eqp)->ChangeLocal(false);
		EnvoyerTS("OK");
		return 0;
	}

	// Deverouille la face avant
	if(strcmp(mes,"ULOCK")==0)
	{
		// TODO : Trouver la fonction du deverrouillage
		((CEqpMAT*)eqp)->ChangeLocal(true);
		EnvoyerTS("OK");
		return 0;
	}

	// Passage en mode distant
	if(strcmp(mes,"MDIST")==0)
	{
		((CEqpMAT*)eqp)->ChangeLocal(false);
		EnvoyerTS("OK");
		return 0;
	}

	EnvoyerTS("KO");
	return ERR_CDE_INCONNUE;
}

/* **************************************************************************
METHODE :		TraiteTS(int type_cde,char *reponse)
TRAITEMENT:		Formate une TS en fonction en recuperant les etats internes
				de l'equipement
***************************************************************************	*/
int CProto_MAT:: TraiteTS(int type_cde,char *reponse)
{
	strcpy(reponse, "");

	// Distinction des messages des matrice SPIN et L11
	if( ((CEqpMAT*)eqp)->TYPE_MATRICE == L11 )
	{
		if(type_cde>15)
		{
			type_cde = type_cde + 5;
		}
	}
	if( ((CEqpMAT*)eqp)->TYPE_MATRICE == SPIN && type_cde == 21 )
		type_cde = 25;
	switch(type_cde)
	{
	case DEFAUT_ALIMENTATION:
		sprintf(reponse, "E000%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CONFIGURATION_CHASSIS:
		sprintf(reponse, "E000%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_RAM_UC:
		sprintf(reponse, "E000%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_PROM_UC:
		sprintf(reponse, "E000%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_BUS_INTERNE_UC:
		sprintf(reponse, "E000%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_BUS_LENT:
		sprintf(reponse, "E000%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_FORMAT_MESSAGE:
		sprintf(reponse, "E000%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_SEQUENCE:
		sprintf(reponse, "E000%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CARTE_RELAIS_1:
		sprintf(reponse, "E000%d%c", type_cde, SEPARE_TRAME);
		break;
	// On retire 1 octet pour les dizaines
	case DEFAUT_CARTE_RELAIS_2:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CARTE_RELAIS_3:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CARTE_RELAIS_4:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CARTE_RELAIS_5:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CARTE_RELAIS_6:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CARTE_RELAIS_7:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CARTE_RELAIS_8:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CARTE_RELAIS_9:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CARTE_RELAIS_10:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CARTE_RELAIS_11:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_CARTE_RELAIS_12:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_ATTENUATEUR_1:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_ATTENUATEUR_2:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_ATTENUATEUR_3:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_ATTENUATEUR_4:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	case DEFAUT_PROGRAMMATION:
		sprintf(reponse, "E00%d%c", type_cde, SEPARE_TRAME);
		break;
	default:
		return ERR_CDE_INCONNUE;
		break;
	}

	return 1;
}

/* **************************************************************************
METHODE :		RecevoirTC(char *message,int nb_car)
TRAITEMENT:		Receptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProto_MAT::RecevoirTC(char *message,int nb_car)
{
	char buf[TAILLE_BUFFER+1];
	int	 i,iResult;

	if(nb_car > TAILLE_BUFFER)
	{
		return ERR_TAILLE_BUFFER;
	}

	strcpy(message, "");
	i=0;
	while(i<nb_car)
	{
		iResult = ligne.Lire(buf+i,1);
		if(iResult < 0)
		{
			return ERREUR_EXTERNE+iResult;
		}
		if(iResult == 0)
		{
			return ERREUR_TIMEOUT;
		}
		if(buf[i]==SEPARE_TRAME)
		{
			continue;
		}
		if(buf[i]==FIN_TRAME) break;
		sprintf(message, "%s%c", message, buf[i]);
		i++;
	}
	return iResult;
}

/* **************************************************************************
METHODE :		ValideAcquittement(int type_cde,char *buf)
TRAITEMENT:		Attend un message d'acquittement du type de commande precedement
				envoye comme TS Maitre
***************************************************************************	*/
BOOL CProto_MAT::ValideAcquittement(int type_cde,char *buf)
{
	BOOL bResult = TRUE;;

	// TODO : integrer le protocole d'acquittement

	return bResult;
}

/* **************************************************************************
METHODE :		ControleTrame(char *message,char *octet_controle)
TRAITEMENT:		Genere les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
char* CProto_MAT::ControleTrame(char *message,char *octet_controle)
{
	int	 i,len_mes;
	char pc;

	strcpy(octet_controle,"");

	if(!erreur_com.controle_parite)
	{
		return octet_controle;
	}

	len_mes = (int)strlen(message);

	pc = 0;
	i=len_mes-1;
	while(i>=0)
	{
		pc = pc ^ message[i];
		// caract précedent = debut de tranche
		if((i) % 8 == 0)
		{
			if(pc < 64)
			{
				pc += 64;
			}
			strncat(octet_controle,&pc,1);
			pc = 0;
		}
		i--;
	}
	return octet_controle;
}

/* **************************************************************************
METHODE :		ExtraitUtile(char *buf,char *message,int *long_utile)
TRAITEMENT:		Extrait les octets utiles
***************************************************************************	*/
BOOL CProto_MAT::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	char octet_controle[8];
	int	 len_mes,nb_tranche;

	len_mes = (int)strlen(buf);

	if(buf[len_mes -2] != SEPARE_TRAME && buf[len_mes -1] != FIN_TRAME)
	{
		return FALSE;
	}

	// 1 tranche = 8 caractère utile + 1 PC sans oublier d'oter les
	// caracteres de debut et de fin de trame
	if(erreur_com.controle_parite)
	{
		nb_tranche = (len_mes-2)/9 + !((len_mes-2)%9 == 0);
	}
	// Aucun caractere de parite
	else
	{
		nb_tranche = 0;
	}

	*long_utile = len_mes - 2 - nb_tranche;
	strcpy(message,"");
	strncat(message,buf+1,*long_utile);

	ControleTrame(message,octet_controle);
	if(strncmp(octet_controle,buf+1+(len_mes - 2 - nb_tranche),nb_tranche))
	{
		return FALSE;
	}

	return TRUE;
}
