/* **************************************************************************
FICHIER :	p_TRC1752.h		 		AUTEUR : DGE
DATE DE CREATION : 	05/10/09			DERNIERE MODIFICATION : 05/10/09
VERSION :	1.0
ROLE :		Définition de la classe CProtoTRC1752
***************************************************************************	*/
#ifndef _CPROTO_TRC1752
#define _CPROTO_TRC1752

/* **********************************************************************
NOM DU COMPOSANT : 		CProtoTRC1752

ROLE DU COMPOSANT :		Classe de base de protocole de communication du
						modem TRC1752

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***********************************************************************	*/
#include "..\comm\proto.h"
#include "Equip\EquipM1752.h"

#include <string>
using namespace std;

// Les nombres de paramètres sont augmentés de 1 pour commencer les tableaux à 1.
// Nombre de parametres des TC
#define NB_PARAM_DLT 5
#define NB_PARAM_DLQ 3
#define NB_PARAM_WRT 3
#define NB_PARAM_SEL 3
#define NB_PARAM_ART 4
#define NB_PARAM_CLT 3
#define NB_PARAM_CLS 3
#define NB_PARAM_MAG 3
#define NB_PARAM_LNL 2
#define NB_PARAM_UNL 2
#define NB_PARAM_CHT 4
#define NB_PARAM_SOU 2
#define NB_PARAM_POL 3
// Nombre de parametres des fichiers
#define NB_PARAM_LT_FILE 4
#define NB_PARAM_RCH_FILE 15
#define NB_PARAM_SAD_FILE 6
#define NB_PARAM_STA_FILE 6
#define NB_PARAM_NET_FILE 53
#define NB_PARAM_SST_FILE 3

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CProtoTRC1752:public CProto
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/

protected:

/* **************************************************************************
METHODE :		CProto()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CProtoTRC1752(t_format fmt,CEquip *pEqp);

/* **************************************************************************
METHODE :		~CProto()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CProtoTRC1752();

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

	int CProtoTRC1752::ExtractData(istringstream &data, string res[], int length, char sep = ';');

	CEquipM1752 * equip;

	void CProtoTRC1752::SendNAC(string * cmd, int pos);

	void CProtoTRC1752::SendNAC(string * cmd, string * param);

	void CProtoTRC1752::SendACK(string * cmd, string * param);

	void CProtoTRC1752::SendSignaling(string cmd, string * param = NULL);

	int CProtoTRC1752::CEV(istringstream &trame);
	int CProtoTRC1752::IDE(istringstream &trame);
	int CProtoTRC1752::CPI(istringstream &trame);
	int CProtoTRC1752::CTO(istringstream &trame);
	int CProtoTRC1752::CAV(istringstream &trame);
	int CProtoTRC1752::CAD(istringstream &trame);
	int CProtoTRC1752::DIS(istringstream &trame);
	int CProtoTRC1752::PIL(istringstream &trame);
	int CProtoTRC1752::LOC(istringstream &trame);
	int CProtoTRC1752::TOK(istringstream &trame);
	void CProtoTRC1752::SignalSTO(const string channel);
	int CProtoTRC1752::AID(istringstream &trame);
	int CProtoTRC1752::AVM(istringstream &trame);
	int CProtoTRC1752::LID(istringstream &trame);
	int CProtoTRC1752::CVM(istringstream &trame);
	int CProtoTRC1752::CTC(istringstream &trame);
	int CProtoTRC1752::CBF(istringstream &trame);
	int CProtoTRC1752::CID(istringstream &trame);
	int CProtoTRC1752::CDT(istringstream &trame);
	int CProtoTRC1752::CSP(istringstream &trame);
	int CProtoTRC1752::CCP(istringstream &trame);
	int CProtoTRC1752::CLP(istringstream &trame);
	int CProtoTRC1752::CKT(istringstream &trame);
	int CProtoTRC1752::CTN(istringstream &trame);
	int CProtoTRC1752::DVM(istringstream &trame);
	int CProtoTRC1752::DID(istringstream &trame);
	int CProtoTRC1752::DIA(istringstream &trame);
	int CProtoTRC1752::DTC(istringstream &trame);
	int CProtoTRC1752::DBF(istringstream &trame);
	int CProtoTRC1752::DDT(istringstream &trame);
	int CProtoTRC1752::BFE(istringstream &trame, bool acq = TRUE);
	int CProtoTRC1752::AUT(istringstream &trame);
	void CProtoTRC1752::SignalAUT();
	int CProtoTRC1752::TES(istringstream &trame, bool acq = TRUE);
	int CProtoTRC1752::STE(istringstream &trame, bool acq = TRUE);
	int CProtoTRC1752::TLS(istringstream &trame);
	int CProtoTRC1752::ACT(istringstream &trame, bool acq = TRUE);
	int CProtoTRC1752::DAC(istringstream &trame, bool acq = TRUE);
	int CProtoTRC1752::ZTS(istringstream &trame);
	void CProtoTRC1752::SignalINR();
	void CProtoTRC1752::SignalPAO(const string channel, const string direction);
	int CProtoTRC1752::MDV(istringstream &trame, bool acq = TRUE);
	int CProtoTRC1752::POR(istringstream &trame, bool acq = TRUE);
	int CProtoTRC1752::RES(istringstream &trame, bool acq = TRUE);
	void CProtoTRC1752::SignalINC(string *error, const string *board=NULL, string *task = NULL, string *debug = NULL);
	int CProtoTRC1752::DSP(istringstream &trame);
	int CProtoTRC1752::DCP(istringstream &trame);
	int CProtoTRC1752::DLP(istringstream &trame);
	int CProtoTRC1752::AKT(istringstream &trame);
	int CProtoTRC1752::DLT(istringstream &trame);
	int CProtoTRC1752::DLQ(istringstream &trame);
	int CProtoTRC1752::WRT(istringstream &trame, bool acq = TRUE);
	int CProtoTRC1752::SEL(istringstream &trame, bool acq = TRUE);
	int CProtoTRC1752::ART(istringstream &trame);
	int CProtoTRC1752::CLT(istringstream &trame);
	int CProtoTRC1752::CLS(istringstream &trame, bool acq = TRUE);
	int CProtoTRC1752::EUA(bool acq = TRUE);
	int CProtoTRC1752::MAG(istringstream &trame);
	void CProtoTRC1752::SignalSTL(const string channel);
	void CProtoTRC1752::SignalRAD(const string aux_port, const string error, bool force = FALSE);
	int CProtoTRC1752::LNL(istringstream &trame);
	int CProtoTRC1752::UNL(istringstream &trame);
	int CProtoTRC1752::CHT(istringstream &trame);
	void CProtoTRC1752::SignalINT(const string voie);
	int CProtoTRC1752::SOU(istringstream &trame);
	void CProtoTRC1752::SignalTBF(const string channel);
	void CProtoTRC1752::SignalETA(const string direction, const string channel);
	void CProtoTRC1752::SignalTSP(const string channel);
	void CProtoTRC1752::SignalLKL(const string voie, const string erreur);
	int CProtoTRC1752::POL(istringstream &trame);
	int testIdxCleLp (const char *s, const char *accept);


};

#endif
