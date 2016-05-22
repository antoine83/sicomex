// p_Test.cpp: implementation of the CProto_Test class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sicomex.h"
#include "p_Test.h"
#include "Equip\EquipTest.h"
#include "divers\div_tmp.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int _CR  = 0x0D;	// Caractere CR
const int _LF  = 0x0A;	// Caractere LF
const int _SUB = 0x1A;	// Caractere SUB

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CProto_Test::CProto_Test(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{

}

CProto_Test::~CProto_Test()
{

}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProto_Test::EnvoyerTS(char *message)
{
	int  len_mes,iResult;
	char buf[TAILLE_BUFFER+1], cTemp1[20], cTemp2[20];

	len_mes = (int)strlen(message);

	if(len_mes > TAILLE_BUFFER)
	{
		return ERR_TAILLE_BUFFER;
	}

	strcpy(cTemp1, "");
	strcpy(cTemp2, "");
	if( ((CEquipTest *)eqp)->DebutCR )
	{
		sprintf(cTemp1, "%c", 13);
		strcat(cTemp2, cTemp1);
	}
	if( ((CEquipTest *)eqp)->DebutLF )
	{
		sprintf(cTemp1, "%c", 10);
		strcat(cTemp2, cTemp1);
	}
	if( ((CEquipTest *)eqp)->DebutSUB )
	{
		sprintf(cTemp1, "%c", 26);
		strcat(cTemp2, cTemp1);
	}

	sprintf(buf, "%s%s", cTemp2, message);

	strcpy(cTemp1, "");
	strcpy(cTemp2, "");
	if( ((CEquipTest *)eqp)->FinCR )
	{
		sprintf(cTemp1, "%c", 13);
		strcat(cTemp2, cTemp1);
	}
	if( ((CEquipTest *)eqp)->FinLF )
	{
		sprintf(cTemp1, "%c", 10);
		strcat(cTemp2, cTemp1);
	}
	if( ((CEquipTest *)eqp)->FinSUB )
	{
		sprintf(cTemp1, "%c", 26);
		strcat(cTemp2, cTemp1);
	}

	strcat(buf, cTemp2);

	iResult = (int)strlen(buf);

	iResult = ligne.Ecrire(buf);
	if(iResult < 0) return ERREUR_EXTERNE+iResult;

	return iResult;
}

/* **************************************************************************
METHODE :		TraiteTC()
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquitement
***************************************************************************	*/
int CProto_Test::TraiteTC(char *mes)
{
	((CEquipTest*)eqp)->MESSAGE = mes;
	((CEquipTest*)eqp)->MAJMessage();
	return 1;
}

/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
int CProto_Test::TraiteTS(int type_cde,char *reponse)
{
	return 1;
}

/* **************************************************************************
METHODE :		RecevoirTC()
TRAITEMENT:		Réceptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProto_Test::RecevoirTC(char *message,int nb_car)
{
	/*char buf[TAILLE_BUFFER+1];
	int  i,iResult;

	if(nb_car > TAILLE_BUFFER)
	{
		return ERR_TAILLE_BUFFER;
	}

	iResult = ligne.Lire(buf, nb_car);

	if(iResult < 0)
		return ERREUR_EXTERNE+iResult;

	if(iResult == 0)
		return ERREUR_TIMEOUT;

	strcpy(message, buf);
	TraiteTC(buf);

	return iResult;*/
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
		/*if(buf[i]==DEBUT_TRAME && i!=0)
		{
			buf[0] = DEBUT_TRAME;
			i=0;
		}*/
		if(buf[i]==_LF || _SUB) break;

		i++;
	}

	// Message non conforme
	if(!ExtraitUtile(buf,message,&iResult))
	{
		return ERR_NON_CONFORME;
	}

	return iResult;
}
