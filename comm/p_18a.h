/* **********************************************************************
FICHIER :	P_18A.h				 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _CPROTO_18A
#define _CPROTO_18A

/* **********************************************************************
NOM DU COMPOSANT : 		CProto18A

ROLE DU COMPOSANT :		Classe de base de protocole de communication de
						l'emetteur HF

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***********************************************************************	*/
#include "..\comm\proto.h"
/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CProto18A:public CProto
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
	int	lecture_canal;
	int	type_test;

protected:

/* **************************************************************************
METHODE :		CProto()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CProto18A(t_format fmt,CEquip *pEqp);

/* **************************************************************************
METHODE :		~CProto()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CProto18A();

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
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
	virtual int TraiteTS(int type_cde,char *reponse);

/* **************************************************************************
METHODE :		RecevoirTC()
TRAITEMENT:		Réceptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
	virtual int RecevoirTC(char *message,int nb_car);

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Retourne toujours TRUE (pas d'acquittement attendu)
***************************************************************************	*/
	virtual BOOL ValideAcquittement(int type_cde,char *message);

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génére un octet de controle.
***************************************************************************	*/
	virtual char *ControleTrame(char *message,char *octet_controle);

/* **************************************************************************
METHODE :		ExtraitUtile()
TRAITEMENT:		Extrait la partie utile d'une trame de télécommande
***************************************************************************	*/
	virtual BOOL ExtraitUtile(char *buf,char *message,int *long_utile);
/* **************************************************************************
METHODE :		CanalLecture()
TRAITEMENT:		Retourne le n° de canal pour utiliser lors de l'envoi des TS
***************************************************************************	*/
	int CanalLecture();

/* **************************************************************************
METHODE :		ChangeCanalLecture()
TRAITEMENT:		Force un n° de canal pour utiliser lors de l'envoi des TS
***************************************************************************	*/
	BOOL ChangeCanalLecture(int	valeur);

};
#endif
