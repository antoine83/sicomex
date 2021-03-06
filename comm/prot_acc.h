/* **********************************************************************
FICHIER :	Prot_Acc.h				 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _CPROTOACCORD
#define _CPROTOACCORD

/* **********************************************************************
NOM DU COMPOSANT : 		CProtoAccord

ROLE DU COMPOSANT :		Classe de base de protocole de communication de
						l'emetteur HF

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***********************************************************************	*/
#include "..\comm\proto.h"

const int	TS_ACQUITE	=	0x30;
const int	TS_ORDRE	=	0x61;
const int	TS_REPETE	=	0x41;
const int	TS_ERREUR	=	0x3F;
const int	TS_SYSTEME	=	0x2A;

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CProtoAccord:public CProto
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
protected:
	int		num_ordre;
	int 	type_trame;
/* **************************************************************************
METHODE :		CProto()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CProtoAccord(t_format fmt,CEquip *eqp);

/* **************************************************************************
METHODE :		~CProto()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CProtoAccord();
/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
	int EnvoyerTS(char *message);

/* **************************************************************************
METHODE :		TraiteTC()
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquitement
***************************************************************************	*/
	virtual int TraiteTC(char *mes);

/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en r�ccup�rant les etats internes
				de l'equipement
***************************************************************************	*/
	virtual int TraiteTS(int type_cde,char *reponse);

/* **************************************************************************
METHODE :		RecevoirTC()
TRAITEMENT:		R�ceptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
	virtual int RecevoirTC(char *message,int nb_car);

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Attend un message d'acquitement du type de commande pr�cedement
				envoy� comme TS Maitre
***************************************************************************	*/
	virtual BOOL ValideAcquittement(int type_cde,char *message);

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		G�n�re les octets de controle du message
***************************************************************************	*/
	virtual char *ControleTrame(char *message,char *octet_controle);

/* **************************************************************************
METHODE :		ExtraitUtile()
TRAITEMENT:		Extrait la partie utile d'une trame de t�l�commande
***************************************************************************	*/
	virtual BOOL ExtraitUtile(char *buf,char *message,int *long_utile);
};
#endif
