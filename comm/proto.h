/* **********************************************************************
FICHIER :	proto.h				 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _CPROTO
#define _CPROTO
/* **********************************************************************
NOM DU COMPOSANT : 		CProto

ROLE DU COMPOSANT :		Classe de base de protocole de communication

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***********************************************************************	*/

#include "typ_glob.h"
#include "divers\Tache.h"
#include "divers\Table.h"
#include "Port.h"
#include "Equip\Equip.h"

const int	TEMPO_TRAVAIL 		=2000;  // Durée d'une commande = 5s
const int	TAILLE_BUFFER		=512;	// Taille du buffer d'émission
const int	TIMEOUT_ACQ_TS		=5;		// TImeout d'acquitement TS = 5s
const int	DIM_TS_ACQ			=20;	// Taille du buffer d'émission

const int	SUCCESS					=0;
const int	MIN_STATION_ID			=1;
const int	MAX_STATION_ID			=999999;
const int	MIN_REMOTE_ADDRESS		=1;
const int	MAX_REMOTE_ADDRESS		=99;
const int	MAX_HDLC_ADDRESS		=254;
const int	MIN_HDLC_ADDRESS		=1;
const int	MIN_UPDATE_LIMIT		=1;
const int	MAX_UPDATE_LIMIT		=99;
const int	DS_INTERFACE_101		=101;
const int	DS_INTERFACE_102		=102;
const int	MIN_PASSWORD_LOCK_TIME	=0;
const int	MAX_PASSWORD_LOCK_TIME	=60;
const int   WRONG_PASSWORD_TYPE     =107;
const int   WRONG_USER_PASSWORD     =125;





const int	ERR_TAILLE_BUFFER	=-1;	// Message trop long
const int	ERREUR_TIMEOUT		=-2;	// TimeOut depasse
const int	ERR_NON_CONFORME	=-3;	// Message non conforme
const int	ERR_CDE_INCONNUE	=-4;	// Telecommande inconue
const int	ERR_PAS_ACQUITTE	=-5;
	// Pas d'acquitement

const int   ERR_NO_REMOTE_MODE  = -6;    // Besoin du mode remote pour cette commande
const int	ERREUR_EXTERNE		=-10;	// Erreur d'une procedure externe

//FDI
const int	ERREUR_FDI			=-17;
const int	IN_BUSY				=-18;

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquip;

class CProto:public CTache
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
protected:
	t_format	format;
	CPort		ligne;

	CEquip		*eqp;

	t_ComErreur	erreur_com;				// Gestion des erreurs de communication

	HANDLE		event;					// Dialogue maitre / Fin Thread

	CTable		table_cde;				// Liste de commande à envoyer

	BOOL		hexa;					// conversion des messages en Hexa

/* **************************************************************************
METHODE :		CProto()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CProto(t_format	fmt,CEquip *pEqp);

/* **************************************************************************
METHODE :		~CProto()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	virtual ~CProto();

/* **************************************************************************
METHODE :		Desactiver()
TRAITEMENT:		Termine le thread associé
***************************************************************************	*/
	virtual int Desactiver();

/* **************************************************************************
METHODE :		InitialiseFormat()
TRAITEMENT:		Initialise le format de transmission
***************************************************************************	*/
	virtual void InitialiseFormat(t_format	fmt);

/* **************************************************************************
METHODE :		AjouterTS()
TRAITEMENT:		Ajoute un message de télésignalisation à la liste de message
				à transférer
***************************************************************************	*/
	virtual int AjouterTS(char *mes,int type_cde);

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
	virtual int EnvoyerTS(char *message);

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
	virtual BOOL ValideAcquittement(int type_cde,char *buf);


/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
***************************************************************************	*/
	virtual char *ControleTrame(char *message,char *octet_controle);

/* **************************************************************************
METHODE :		Purge_message()
TRAITEMENT:		Purge de la table TS
***************************************************************************	*/
	void Purge_message();

/* **************************************************************************
METHODE :		Purge_Reception()
TRAITEMENT:		Purge le buffer de réception
***************************************************************************	*/
	void Purge_Reception();

/* **************************************************************************
METHODE :		ExtraitUtile()
TRAITEMENT:		Extrait la partie utile du message
***************************************************************************	*/
	virtual BOOL ExtraitUtile(char *buf,char *message,int *long_utile);

/* **************************************************************************
METHODE :		RetourneErreurCom()
TRAITEMENT:		Retourne les erreur de communication
***************************************************************************	*/
	virtual void RetourneErreurCom(t_ComErreur	*err) const;

/* **************************************************************************
METHODE :		ChangeErreurCom()
TRAITEMENT:		Modifie les erreurs de communication
***************************************************************************	*/
	virtual void ChangeErreurCom(t_ComErreur err);

/* **************************************************************************
METHODE :		Traitement()
TRAITEMENT:		Traitement à effecter dans le thread :
				- Gere les dialogues Esclave
				- Gere les dialogue maitre à partir de la liste de message
				  à transférer
***************************************************************************	*/
	virtual DWORD WINAPI Traitement(void *param);
};
#endif
