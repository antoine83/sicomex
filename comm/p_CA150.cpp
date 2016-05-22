// p_CA150.cpp: implementation of the CProtoCA150 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Comm\p_CA150.h"
#include "Equip\EqpCA150.h"
#include "divers\div_tmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int 	DEBUT_TRAME = 0xD;	// Caractere de debut de trame
const int 	FIN_TRAME 	= 0xA;	// Caractere de fin de trame

/* **************************************************************************
METHODE :		CProtoCA150()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProtoCA150::CProtoCA150(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;
	// TODO : integrer ici le constructeur
}

/* **************************************************************************
METHODE :		~CProtoCA150()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProtoCA150::~CProtoCA150()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProtoCA150::EnvoyerTS(char *message)
{
	int  len_mes,iResult;
	// Nombre de caractere envelopant le message
	int  nb_car_enveloppe;
	char buf[TAILLE_BUFFER+1];
	char octet_controle[8];

	// Taille du message � envoyer
	len_mes = (int)strlen(message);
	// Debut Trame + Fin Trame et  n  PC par tranche de 8 car
	nb_car_enveloppe = 1 + 1 + len_mes/9 + 1;

	if(len_mes+nb_car_enveloppe > TAILLE_BUFFER)
	{
		return ERR_TAILLE_BUFFER;
	}

	buf[0] = DEBUT_TRAME;
	strcpy(buf+1,message);
	strcat(buf,ControleTrame(message,octet_controle));
	iResult = (int)strlen(buf);
	buf[iResult] = FIN_TRAME;
	// Force la fin de chaine
	buf[iResult+1]=0;

	if(erreur_com.pas_debut)
	{
		buf[0]=0x20;
	}
	if(erreur_com.pas_fin)
	{
		buf[iResult]=0;
	}

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
int CProtoCA150::TraiteTC(char *mes)
{
	((CEquipCA150 *)eqp)->ChgtEtatCharge(1, false);
	// Octet 1
	switch (mes[0])
	{
	case '8':
		((CEquipCA150 *)eqp)->ChgtEtatCharge(4, true);
		break;
	case '4':
		((CEquipCA150 *)eqp)->ChgtEtatCharge(3, true);
		break;
	case '2':
		((CEquipCA150 *)eqp)->ChgtEtatCharge(2, true);
		break;
	case '1':
		((CEquipCA150 *)eqp)->ChgtEtatCharge(1, true);
		break;
	case '0':
		break;
	default:
		// TODO : erreur de trame
		return ERR_CDE_INCONNUE;
		break;
	}

	// Octet 2
	switch (mes[1])
	{
	case '8':
		if(((CEquipCA150 *)eqp)->TYPE == SLAVE)
			((CEquipCA150 *)eqp)->ChgtEtatCharge(6, true);
		if(((CEquipCA150 *)eqp)->TYPE == MASTER)
			((CEquipCA150 *)eqp)->ChgtEtatCharge(5, true);
		break;
	case '1':
		if(((CEquipCA150 *)eqp)->TYPE == SLAVE)
			((CEquipCA150 *)eqp)->ChgtEtatCharge(5, true);
		break;
	case '0':
		break;
	default:
		// TODO : erreur de trame
		return ERR_CDE_INCONNUE;
		break;
	}

	// Octet 3
	switch (mes[2])
	{
	case '8':
		if(((CEquipCA150 *)eqp)->TYPE == MASTER)
			((CEquipCA150 *)eqp)->ChgtCombineMaster(true);
		break;
	case '0':
		if(((CEquipCA150 *)eqp)->TYPE == MASTER)
			((CEquipCA150 *)eqp)->ChgtCombineMaster(false);
		break;
	default:
		// TODO : erreur de trame
		return ERR_CDE_INCONNUE;
		break;
	}

	return 1;
}

/* **************************************************************************
METHODE :		TraiteTS(int type_cde,char *reponse)
TRAITEMENT:		Formate une TS en fonction en recuperant les etats internes
				de l'equipement
***************************************************************************	*/
int CProtoCA150:: TraiteTS(int type_cde,char *reponse)
{
	int iResult;
	char * result = NULL;

	strcpy(reponse, "");
	switch (type_cde)
	{
	case DEMANDE_ETAT:
		result = ((CEquipCA150 *)eqp)->DemandeEtat();
		strcpy(reponse, result);
		free(result);
		iResult = 1;
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
int CProtoCA150::RecevoirTC(char *message,int nb_car)
{
	char buf[TAILLE_BUFFER+1];
	int	 i,iResult;

	if(nb_car > TAILLE_BUFFER)
	{
		return ERR_TAILLE_BUFFER;
	}

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
		if(buf[i]==DEBUT_TRAME && i!=0)
		{
			buf[0] = DEBUT_TRAME;
			i=0;
		}
		if(buf[i]==FIN_TRAME) break;

		i++;
	}

	// Message non conforme
	if(!ExtraitUtile(buf,message,&iResult))
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
BOOL CProtoCA150::ValideAcquittement(int type_cde,char *buf)
{
	return TRUE;
}

/* **************************************************************************
METHODE :		ControleTrame(char *message,char *octet_controle)
TRAITEMENT:		Genere les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
char* CProtoCA150::ControleTrame(char *message,char *octet_controle)
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
		// caract pr�cedent = debut de tranche
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
BOOL CProtoCA150::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	char octet_controle[8];
	int	 len_mes,nb_tranche;

	len_mes = (int)strlen(buf);

	if(buf[0] != DEBUT_TRAME && buf[len_mes -1] != FIN_TRAME)
	{
		return FALSE;
	}

	// 1 tranche = 8 caract�re utile + 1 PC sans oublier d'oter les
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
