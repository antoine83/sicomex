/* ***********************************************************************
FICHIER :	p_ED42.h				 	AUTEUR : FDI
DATE DE CREATION : 	06/01/2016			DERNIERE MODIFICATION : 06/01/2016
VERSION :	1.0
*************************************************************************/
#ifndef _CPROTOED42
#define _CPROTOED42

/* **********************************************************************
NOM DU COMPOSANT : 		CProtoED42

ROLE DU COMPOSANT :		Classe de base de protocole de communication du
						Récepteur HF

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***********************************************************************	*/
#include "..\comm\proto.h"
#include "Equip\EquipED42.h"


#include <string>
#include <math.h>

enum MESSAGE_TYPE {
	ACV,
	ALM,
	CES,
	CIK,
	CV,
	CVBTA,
	CVBUD,
	CVDLA,
	CVLG,
	CVLR,
	CVTAG,
	CVUPD,
	DEFPS,
	ERR,
	INI,
	KEK,
	KEKDEL,
	OFL,
	OPS,
	PSS,
	PWCHG,
	PWCHK,
	REQDS,
	REQHD,
	REQHT,
	REQID,
	REQPS,
	REQUL,
	RES,
	RST,
	S,
	SETAD,
	SETDS,
	SETHD,
	SETID,
	SETPS,
	SETUL,
	SYS,
	TAK,
	VER,
	CMD_NA,
	NB_MESSAGE_TYPE
};


using namespace std;

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/
class CProtoED42:public CProto
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
	int	indice_veille;		// ieme Canal de veille en cours
	int indice_maintien;	// indice du temps de maintien en cours
	int	indice_frequence;	// ieme frequence des bandes
	int indice_vitesse;		// indice de la vitesse de blayage
	int	lecture_canal;

	char bufCmd[TAILLE_BUFFER];

	bool isRES;				//

protected:
	t_ComErreur	err;

/* **************************************************************************
METHODE :		CProto()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CProtoED42(t_format fmt,CEquip *pEqp);

/* **************************************************************************
METHODE :		~CProto()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CProtoED42();

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
	virtual int TraiteTC(char *mess);

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
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
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


	int CProtoED42::ExtractData(istringstream &data, string res[], int length, char sep = ';');

	//void CProtoED42:: sendAcq();
	void CProtoED42:: sendAcq(int val);
	void CProtoED42:: sendAuthorizationError();

	string CProtoED42:: getUneError(string tmp_cmd);
	int GestionHexa(const char* toBeTested);
	int DecimalToHexa(char* number);
	string HaxaToStringRCS(string reponse);
	string IntToHexaString(int reponse,int format = 2);
	string TagStatusCrypto(string confKey, int tmpOnlinePreset = -1, int tmpPresetType = OPE_NA);

	string KeyMemoryIndex(TMapKeyManagement confKey, int minPlage, int maxPlage);


protected:
	CEquipED42 * equip;
	int	extendedErrorCode;
	bool testTrameFirst(string trame, int sizeMin, int sizeMax, char usedSep, int *ret, bool option=false, int typeOption=0, bool isOnline=false);

	int CProtoED42:: A(string trame);
	int CProtoED42:: ACV(string trame);
	int CProtoED42:: ALM(string trame);
	int CProtoED42:: CES(string trame);
	int CProtoED42:: CIK(string trame);
	int CProtoED42:: CV(string trame);
	int CProtoED42:: CVBTA(string trame);
	int CProtoED42:: CVBUD(string trame);
	int CProtoED42:: CVDEL(string trame);
	int CProtoED42:: CVDLA(string trame);
	int CProtoED42:: CVLG(string trame);
	int CProtoED42:: CVLR(string trame);
	int CProtoED42:: CVTAG(string trame);
	int CProtoED42:: CVUPD(string trame);
	int CProtoED42:: DEFPS(string trame);
	int CProtoED42:: ERR(string trame);
	int CProtoED42:: INI(string trame);
	int CProtoED42:: KEK(string trame);
	int CProtoED42:: KEKDL(string trame);
	int CProtoED42:: N(string trame);
	int CProtoED42:: OFL(string trame);
	int CProtoED42:: ONL(string trame);
	int CProtoED42:: OPS(string trame);
	int CProtoED42:: PSS(string trame);
	int CProtoED42:: PWCHG(string trame);
	int CProtoED42:: PWCHK(string trame);
	int CProtoED42:: REQDS(string trame);
	int CProtoED42:: REQHD(string trame);
	int CProtoED42:: REQHT(string trame);
	int CProtoED42:: REQID(string trame);
	int CProtoED42:: REQPS(string trame);
	int CProtoED42:: REQUL(string trame);
	string CProtoED42:: RES();
	int CProtoED42:: RES(string trame);
	string CProtoED42:: RCS(string trame, bool outCmd = FALSE);
	int CProtoED42:: RST(string trame);
	int CProtoED42:: S(string trame);
	string CProtoED42:: S();
	int CProtoED42:: SETAD(string trame);
	int CProtoED42:: SETDS(string trame);
	int CProtoED42:: SETHD(string trame);
	int CProtoED42:: SETHT(string trame);
	int CProtoED42:: SETID(string trame);
	int	CProtoED42:: SETPS(string trame);
	int CProtoED42:: SETUL(string trame);
	int CProtoED42:: SYS(string trame);
	int CProtoED42:: TAK(string trame);
	int CProtoED42:: VER(string trame);

	void CProtoED42::buildTrameREQPS(TGeneralParameters presetEnCours,TDigitalDCE digitalDceEnCours,
								   TDigitalDTE digitalDteEnCours,TAnalogDCE analogDceEnCours,
								   TAnalogDTE analogDteEnCours);

};
#endif
