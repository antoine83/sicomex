/* **********************************************************************
FICHIER :	AppelAle.h				 		AUTEUR : DGE
DATE DE CREATION : 	16/12/2009
VERSION :	1.0
***********************************************************************	*/
#ifndef _CAPPELALE
#define _CAPPELALE
/* **********************************************************************
NOM DU COMPOSANT : 		CAppelAle

ROLE DU COMPOSANT :		Classe Gestion des appels ale

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***********************************************************************	*/

#include "divers\Tache.h"
#include "Equip\EquipM1752.h"

#include <string>

using namespace std;

const int SCANNING_TIME = 1000;
const int CALLING_TIME = 2000;
const int RECEIVE_TIME = 1000;
const int SEND_TIME = 1000;
const int WAIT_TIME = 500;

const int IDLE = 0;
const int LISTENING = 1;
const int SCANNING = 2;
const int CALLING = 3;
const int RECEIVE_RESPONSE = 4;
const int SEND_ACKNOWNLEDGEMENT = 5;
const int LINKED_CALLING = 6;
const int LINKED_CALLED = 7;
const int RECEIVING_RESPONSE = 8;
const int RECEIVE_CALL = 9;
const int SEND_RESPONSE = 10;
const int RECEIVING_CALL = 11;
const int SOUNDING = 12;
const int SEND_AMD = 13;
const int RECEIVING_AMD = 14;

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CEquipM1752;

class CAppelAle:public CTache
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
	CEquipM1752		*eqp;
	string			channel;
	bool			appel;
	bool			appel_recu;
	bool			fin_appel;
	bool			amd_recu;
	bool			amd_envoye;
	bool			sound;
	int				automate;
	int				automate_prec;

/* **************************************************************************
METHODE :		Calling()
TRAITEMENT:		Verifie si le passage en calling est attendu et possible
***************************************************************************	*/
	bool Calling();
/* **************************************************************************
METHODE :		TestCalling()
TRAITEMENT:		Verifie les conditions pour que l'appel aboutisse
***************************************************************************	*/
	bool TestCalling(int canal);

/* **************************************************************************
METHODE :		TestCanalCalled()
TRAITEMENT:		Verifie que le canal sur lequel on recoit l'appel est bon
***************************************************************************	*/
	bool TestCanalCalled(int canal);

/* **************************************************************************
METHODE :		TestAdresseAppelee()
TRAITEMENT:		Verifie que l'adresse appelée est la notre
***************************************************************************	*/
	bool TestAdresseAppelee();

/* **************************************************************************
METHODE :		TestAdresseAppelante()
TRAITEMENT:		Verifie que l'adresse qui nous appelle est connue
***************************************************************************	*/
	bool TestAdresseAppelante();

/* **************************************************************************
METHODE :		SetReceptionValueOn()
TRAITEMENT:		Place la qualité et le level af receive aux valeurs de reception
***************************************************************************	*/
	void SetReceptionValueOn();

/* **************************************************************************
METHODE :		SetReceptionValueOff()
TRAITEMENT:		Place la qualité et le level af receive aux valeurs de veille
***************************************************************************	*/
	void SetReceptionValueOff();

/* **************************************************************************
METHODE :		LinkAction()
TRAITEMENT:		Test les actions possible pdt un link
***************************************************************************	*/
	void LinkAction();

public:
/* **************************************************************************
METHODE :		CAppelAle()
TRAITEMENT:		Constructeur
***************************************************************************	*/
	CAppelAle(CEquipM1752 *pEqp, string channel);

/* **************************************************************************
METHODE :		~CAppelAle()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CAppelAle();

/* **************************************************************************
METHODE :		Desactiver()
TRAITEMENT:		Termine le thread associé
***************************************************************************	*/
	virtual int Desactiver();

/* **************************************************************************
METHODE :		Traitement()
TRAITEMENT:		Traitement à effectuer dans le thread
***************************************************************************	*/
	virtual DWORD WINAPI Traitement(void *param);

/* **************************************************************************
METHODE :		LancerAppel()
TRAITEMENT:		Lance l'appel concerné
***************************************************************************	*/
	void LancerAppel();

/* **************************************************************************
METHODE :		CasserAppel()
TRAITEMENT:		Termine l'operation en cours pour retomber en idle
***************************************************************************	*/
	void CasserAppel();
/* **************************************************************************
METHODE :		RecevoirAppel()
TRAITEMENT:		Recoit un appel pdt la phase d'écoute
***************************************************************************	*/
	void RecevoirAppel();

/* **************************************************************************
METHODE :		RecevoirAmd()
TRAITEMENT:		Recoit un amd pdt le link
***************************************************************************	*/
	void RecevoirAmd();

/* **************************************************************************
METHODE :		EnvoyerAmd()
TRAITEMENT:		Envoi un amd pdt le link
***************************************************************************	*/
	void EnvoyerAmd();

/* **************************************************************************
METHODE :		Sounding()
TRAITEMENT:		Emettre un sounding
***************************************************************************	*/
	void Sounding();
};
#endif
