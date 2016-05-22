/* **********************************************************************
FICHIER :	p_MatCom.h				 		AUTEUR : FSA
DATE DE CREATION : 	26/02/07			DERNIERE MODIFICATION : 26/02/07
VERSION :	1.0
***********************************************************************	*/
#ifndef _CPROT_COMMUTATION_MATRIX
#define _CPROT_COMMUTATION_MATRIX

/* **********************************************************************
NOM DU COMPOSANT : 		CProto1237

ROLE DU COMPOSANT :		Classe de base de protocole de communication de
						la matrice de commutation

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***********************************************************************	*/
#include "..\comm\proto.h"
/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CProtoCommutationMatrix:public CProto
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
protected:

/* **************************************************************************
METHODE :		CProtoCommutationMatrix()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CProtoCommutationMatrix(t_format fmt,CEquip *pEqp);

/* **************************************************************************
METHODE :		~CProtoCommutationMatrix()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CProtoCommutationMatrix();

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
TRAITEMENT:		Attend un message d'acquitement du type de commande précedement
				envoyé comme TS Maitre
***************************************************************************	*/
	virtual BOOL ValideAcquittement(int type_cde,char *message);

/* **************************************************************************
METHODE :		ExtraitUtile()
TRAITEMENT:		Extrait la partie utile d'une trame de télécommande
***************************************************************************	*/
	virtual BOOL ExtraitUtile(char *buf,char *message,int *long_utile);

	bool testSeparator(char *here);

};
#endif
