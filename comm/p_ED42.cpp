/* **************************************************************************
FICHIER :	p_ED42.CPP		 			AUTEUR : FDI
DATE DE CREATION : 	06/01/2016			DERNIERE MODIFICATION : 06/01/2016
VERSION :	1.0
ROLE :		Implémentation de la classe CProtoED42
***************************************************************************	*/

#include "stdafx.h"
#include "stdlib.h"

#include "Comm\p_ED42.h"
#include "Equip\EquipED42.h"
#include "divers\div_tmp.h"

#include <sstream>
#include <iostream>
#include <string.h> 
#include <stdio.h>
#include <stdlib.h>
#include <iomanip>

#include <stdexcept>
#include <algorithm>
#include "Divers\Logger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;
using namespace CPlusPlusLogging;
// using namespace System::Text::RegularExpressions;
// using namespace System;


extern Logger pLogger;

const char 	DEBUT_TRAME = '>';
const char 	FIN_TRAME 	= '<';


int cptSuccessfullCmd;
int cptNbrCmd;
istringstream cmd;
string pwd = "12345";

int typeCmd = 0;


/* **************************************************************************
METHODE :		CProtoRecHF()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProtoED42::CProtoED42(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;
	equip = (CEquipED42*)pEqp;

	isRES = FALSE;
}

/* **************************************************************************
METHODE :		~CProtoRecHF()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProtoED42::~CProtoED42()
{
	pLogger.LOG_TRACE("Dans CProtoED42:: Destructeur");
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProtoED42::EnvoyerTS(char *message)
{
	OutputDebugString("Dans : CProtoED42::EnvoyerTS(char *message)!\n");
	pLogger.LOG_TRACE("Dans : CProtoED42::EnvoyerTS(char *message)!");


	int		len_mes,iResult;

	char	buf[TAILLE_BUFFER+1];

	len_mes = (int)strlen(message);	// Taille du message à envoyer

	if (!equip->getErrorCR())
		buf[0] = DEBUT_TRAME;

	strcpy(buf+1,message);
	iResult = (int)strlen(buf);

	if(!equip->getErrorLF())
		buf[iResult] = FIN_TRAME;

	buf[iResult+1]=0;				// Force la fin de chaine

	OutputDebugString("Dans : CProtoED42::EnvoyerTS(char *message) et ligne.Ecrire(buf) !\n");
	pLogger.LOG_TRACE("Dans : CProtoED42::EnvoyerTS(char *message) et ligne.Ecrire(buf) !");

	iResult = ligne.Ecrire(buf);
	if(iResult < 0) return ERREUR_EXTERNE+iResult;

	OutputDebugString("Dans : CProtoED42::EnvoyerTS(char *message) et ligne.Ecrire(buf) pas de ERREUR_EXTERNE+iResult!\n");
	pLogger.LOG_TRACE("Dans : CProtoED42::EnvoyerTS(char *message) et ligne.Ecrire(buf) pas de ERREUR_EXTERNE+iResult!");

	return iResult;  // nb d'octet transmis
}

/* **************************************************************************
METHODE :		TraiteTC()
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquitement
***************************************************************************	*/
int CProtoED42::TraiteTC(char *mess)
{

	OutputDebugString("Dans : CProtoED42::TraiteTC(char *mess) !\n");
	pLogger.LOG_TRACE("Dans : CProtoED42::TraiteTC(char *mess)");

	ostringstream sss1;
    sss1 << endl;
    sss1 << "\t" << "mess: " << mess << endl;
	pLogger.LOG_TRACE(sss1.str());

	if (equip->getRemoteMode() == LF_DIG || !equip->GetMarcheEd42())
		return ERR_NO_REMOTE_MODE;

	//ExtraitValeurs(mes);
	string trame;
	string strMaj;

	string message		= mess;
	int len_mes			= (int)strlen(mess);

	TVectorError errorEncours = equip->getErrors();

	//On efface l'erreur en l'enplacement RES
	errorEncours[COMMAND_RES] = " ";
	equip->setErrors(errorEncours);

	if (len_mes == 0)
		return ERR_CDE_INCONNUE;

	int checker			= SUCCESS;
	cptSuccessfullCmd	= 0;
	cptNbrCmd			= 0;

	strcpy(bufCmd,"");


	strMaj = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	int pos			= 0;
	int endOfCmd	= 0;
	int endOfParams = 0;

	//while(endOfParams != -1 && checker == SUCCESS)
	while(endOfParams != -1)
	{
		//if(	checker == SUCCESS)
		if(	checker != 255)
		{
			int param	= 0;
			int lenMsg	= 0;

			//***************************
			// Vérification du RCS
			//***************************
			size_t found = message.find("RCS");

			if (found!=std::string::npos)
			{
				pLogger.LOG_TRACE("Dans : CProtoED42::TraiteTC(char *mess) et if (found!=std::string::npos)");

				lenMsg = message.length();
				string rcsMsg = message.substr (lenMsg-2,2);
				string rcsMsgTmp = RCS(message.substr (0,lenMsg-6), TRUE);

				if(rcsMsg != rcsMsgTmp)
					equip->setStatusErrorTable(SYNTAX_RCS, TRUE);

			}
			//****************************

			endOfCmd = message.find_first_not_of(strMaj, pos);
			cmd.str(message.substr(pos, endOfCmd-pos));
			endOfParams = message.find_first_of(strMaj, endOfCmd);
			string parameters;
			//Vérifie si les paramètres ne sont pas vide
			if(endOfCmd == -1)
				parameters = "";
			else
				parameters = message.substr(endOfCmd, endOfParams - endOfCmd);

			trame	= parameters;
			pos		= endOfParams;


			if (equip->IsEnTest()== true)  // L'equipement n'execute pas de commande lorsqu'il est en test
				return ERR_CDE_INCONNUE;

		/*	if(!(equip->getRemoteStatus()))
				return ERR_NON_CONFORME;*/

			if (cmd.str() != "A" && cmd.str() != "RCS" && cmd.str() != "N")
			{
				pLogger.LOG_TRACE("Dans : CProtoED42::TraiteTC(char *mess) et cptNbrCmd++ !");
				cptNbrCmd++;
			}

			if(cmd.str() == "A")						// Permet de définir à quel appareil le message va être envoyé
				checker = A(trame);

			else if(cmd.str() == "ACV")					// Requête de la clé active	TODO pour  && !equip->GetStatusNl()
				checker = ACV(trame);

			else if(cmd.str() == "ALM")					// Buffer de l'alarme
				checker = ALM(trame);

			else if(cmd.str() == "CES")												// Etat da la machine de cryptage  TODO pour  && !equip->GetStatusNl()
				checker = CES(trame);

			else if(cmd.str() == "CIK")					// requête du statut du CIK
				checker = CIK(trame);

			else if(cmd.str() == "CV")					// Requête d'une clé
				checker = CV(trame);

			else if(cmd.str() == "CVBTA")				// tag bilateral d'une clé
				checker = CVBTA(trame);

			else if(cmd.str() == "CVBUD")				// update bilateral d'une clé
				checker = CVBUD(trame);

			else if(cmd.str() == "CVDEL")				// supprime une clé
				checker = CVDEL(trame);

			else if(cmd.str() == "CVDLA")				// supprime toutes les clés
				checker = CVDLA(trame);

			else if(cmd.str() == "CVLG")				// update la vue sur les clés
				checker = CVLG(trame);

			else if(cmd.str() == "CVLR")				// requête d'une vue sur les clés
				checker = CVLR(trame);

			else if(cmd.str() == "CVTAG")				// tag une clé
				checker = CVTAG(trame);

			else if(cmd.str() == "CVUPD")				// update une clé
				checker = CVUPD(trame);

			else if(cmd.str() == "DEFPS")				//requête des paramètres par défaut
				checker = DEFPS(trame);

			else if(cmd.str() == "ERR")					// accès au buffer d'erreur
				checker = ERR(trame);

			else if(cmd.str() == "INI")					//permet d'initialiser une connection et vérifie la version du protocole
				checker = INI(trame);

			else if(cmd.str() == "KEK")					// requête d'une KEK
				checker = KEK(trame);

			else if(cmd.str() == "KEKDL")				// supprime une KEK
				checker = KEKDL(trame);

			else if(cmd.str() == "N")					// Déclenche le compteur de message	 TODO pour  && !equip->GetStatusNl()
				checker = N(trame);

			else if(cmd.str() == "OFL")					// Passer en mode OFFLINE
				checker = OFL(trame);

			else if(cmd.str() == "ONL")					// Passer en mode ONLINE
				checker = ONL(trame);

			else if(cmd.str() == "OPS")					// Retourne le preset qui est online
				checker = OPS(trame);

			else if(cmd.str() == "PSS")					// Requête d'un changement d'état de preset
				checker = PSS(trame);

			else if(cmd.str() == "PWCHG")											// changer le mot de passe
				checker = PWCHG(trame);

			else if(cmd.str() == "PWCHK")				// vérifie le password
				checker = PWCHK(trame);

			else if(cmd.str() == "REQDS")				// Renvoie la DSInterface en cours
				checker = REQDS(trame);

			else if(cmd.str() == "REQHD")				// Renvoie la HDLC Adress
				checker = REQHD(trame);

			else if(cmd.str() == "REQHT")				// Renvoie le temps avant autolock
				checker = REQHT(trame);

			else if(cmd.str() == "REQID")				// Renvoie l'ID de la station
				checker = REQID(trame);

			else if(cmd.str() == "REQPS")				// Renvoie les parametres du preset en cours
				checker = REQPS(trame);

			else if(cmd.str() == "REQUL")				// Renvoie le nombre maximum de mise à jour
				checker = REQUL(trame);

			else if(cmd.str() == "RES")				// Demande de RES 
				checker = RES(trame);

			else if(cmd.str() == "RCS")											// Résultat du checksum
				checker = TRUE; //Vérifie juste que la commande est connue

			else if(cmd.str() == "RST")											// Reset de l'appareil
				checker = RST(trame);

			else if(cmd.str() == "S")											// Renvoie le statut du message TODO : 156
				checker = S(trame);

			else if(cmd.str() == "SETAD")				// Permet de définir l'adresse de l'appareil
				checker = SETAD(trame);

			else if(cmd.str() == "SETDS")				// Permet de définir la DS interface en cours
				checker = SETDS(trame);

			else if(cmd.str() == "SETHD")				// Permet de définir la HDLC Adress
				checker = SETHD(trame);

			else if(cmd.str() == "SETHT")				// Permet de définir Le temps avant verrouillage
				checker = SETHT(trame);

			else if(cmd.str() == "SETID")				// Permet de définir L'ID de la station
				checker = SETID(trame);

			else if(cmd.str() == "SETPS")				// Permet de définir le preset actif
				checker = SETPS(trame);

			else if(cmd.str() == "SETUL")				// Permet de définir le nombre maximum de mise à jour pouvant être effectuées
				checker = SETUL(trame);

			else if(cmd.str() == "SYS")											// Requête du statut du système	 TODO pour  && !equip->GetStatusNl())
				checker = SYS(trame);

			else if(cmd.str() == "TAK")											// Passe en mode Remote
				checker = TAK(trame);

			else if(cmd.str() == "VER")				// Renvoie la version de l'appareil
				checker = VER(trame);

			else 										// TODO : else if(!equip->GetStatusNl()) ou  if(cmd.str() == "VER")
			{
				pLogger.LOG_TRACE("Dans : CProtoED42::TraiteTC(char *mess) et //Commande inconnue !");
				ostringstream sss1;
				sss1 << endl;
				sss1 << "\t" << "Dans : CProtoED42::TraiteTC(char *mess) et //Commande inconnue !" << endl;
				sss1 << "\t" << "cmd.str(): " << cmd.str() << endl;
				pLogger.LOG_DEBUG(sss1);
				//Commande inconnue
				equip->setStatusErrorTable(UNKNOWN_COMMAND, TRUE); 
				//On envoi un RES car on ne construit pas de reponce spécifique à la commande
				isRES = TRUE;

				checker = UNKNOWN_COMMAND;
			}
		}


		//**************************
		//  checker == SUCCESS
		//**************************
		if((checker == SUCCESS &&
			cmd.str() != "A" &&
			cmd.str() != "N" &&
			cmd.str() != "RCS") ||
			checker == NOT_REMOTE_MODE ||
			checker == CONFLICT)
		{
			OutputDebugString("Dans : CProtoED42::TraiteTC(char *mess) et cptSuccessfullCmd++ !\n");
			pLogger.LOG_TRACE("Dans : CProtoED42::TraiteTC(char *mess) et cptSuccessfullCmd++ !");

			cptSuccessfullCmd++;
		}


		// **************************************************
		// Mise en place du nr de la Commande étant en erreur
		//***************************************************
		if((checker != SUCCESS &&
			cmd.str() != "A" &&
			cmd.str() != "N" &&
			cmd.str() != "RCS") &&
			checker != NOT_REMOTE_MODE &&
			checker != CONFLICT)
		{
			OutputDebugString("Dans : CProtoED42::TraiteTC(char *mess) et SetnrCommandInError !\n");
			pLogger.LOG_TRACE("Dans : CProtoED42::TraiteTC(char *mess) et SetnrCommandInError !");

			equip->SetnrCommandInError(cptNbrCmd);
		}

	}

	ostringstream sss;
    sss << endl;
    sss << "\t" << "Dans : CProtoED42:: avant sendAcq(typeCmd)" << endl;
    sss << "\t" << "cptSuccessfullCmd: " << cptSuccessfullCmd << endl;
	sss << "\t" << "cptNbrCmd: " << cptNbrCmd << endl;
    pLogger.LOG_DEBUG(sss);
	pLogger.LOG_TRACE(sss.str());



	//**************************
	//  Réponse à la commande
	//**************************
	sendAcq(typeCmd);

	OutputDebugString("Fin CProtoED42::TraiteTC(char *mess) !\n");
	pLogger.LOG_TRACE("Fin CProtoED42::TraiteTC(char *mess) !");

	return SUCCESS;

}

/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
int CProtoED42:: TraiteTS(int type_REC,char *reponse)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: TraiteTS(int type_REC,char *reponse)");

	int	iResult = 0;

	return iResult;
}

/* **************************************************************************
METHODE :		RecevoirTC()
TRAITEMENT:		Réceptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProtoED42::RecevoirTC(char *message,int nb_car)
{
	pLogger.LOG_TRACE("Dans CProtoED42::RecevoirTC(char *message,int nb_car)");

	char	buf[TAILLE_BUFFER+1];
	int		index,iResult;

	size_t lenMsg = strlen(message);

	ostringstream sss;
    sss << endl;
    sss << "\t" << "Avant debut traitement" << endl;
    sss << "\t" << "message: " << message << endl;
	sss << "\t" << "lenMsg:  " << lenMsg << endl;
	sss << "\t" << "nb_car:  " << nb_car << endl << endl;
    pLogger.LOG_DEBUG(sss);

	if(nb_car > TAILLE_BUFFER) return ERR_TAILLE_BUFFER;			// TODO ?? nb_car = tjrs 512 et ERR_TAILLE_BUFFER = tjrs 512

	index=0;
	while(index<nb_car)
	{
		iResult = ligne.Lire(buf+index,1);
		//********************************
		ostringstream ss1;
		ss1 << endl;
		ss1 << "\t" << "Dans le while(index<nb_car)" << endl;
		ss1 << "\t" << "index:   " << index << endl;
		ss1 << "\t" << "nb_car:  " << nb_car << endl << endl;
		pLogger.LOG_DEBUG(ss1);
		//********************************
		if(iResult < 0) return ERREUR_EXTERNE+iResult;
		if(iResult == 0) return ERREUR_TIMEOUT;
		if(buf[index]==DEBUT_TRAME && index!=0)
		{
			buf[0] = DEBUT_TRAME;
			index=0;
		}

		if(buf[index]==FIN_TRAME) break;

		index++;
	}

	if(!ExtraitUtile(buf,message,&iResult))
		return ERR_NON_CONFORME;			// Message non conforme

	ostringstream ss2;
    ss2 << endl;
    ss2 << "\t" << "Apres traitement" << endl;
	ss2 << "\t" << "buf:	 " << buf << endl;
    ss2 << "\t" << "iResult: " << iResult << endl;
	ss2 << "\t" << "index:   " << index << endl << endl;
    pLogger.LOG_DEBUG(ss2);

	return iResult;
}

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Attend un message d'acquitement du type de commande précedement
				envoyé comme TS Maitre
***************************************************************************	*/
BOOL CProtoED42::ValideAcquittement(int type_cde,char *buf)
{
	pLogger.LOG_TRACE("Dans CProtoED42::ValideAcquittement(int type_cde,char *buf)");

	int		iResult = NULL;
	BOOL	bResult;

	bResult = TRUE;

	return bResult;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
char* CProtoED42::ControleTrame(char *message,char *octet_controle)
{
	pLogger.LOG_TRACE("Dans CProtoED42::ControleTrame(char *message,char *octet_controle)");
	//int		i,len_mes;
	//char	pc;

	strcpy(octet_controle,"");

	return octet_controle;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
BOOL CProtoED42::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	pLogger.LOG_TRACE("Dans CProtoED42::ExtraitUtile");

	int		len_mes;

	len_mes = (int)strlen(buf);
	if(buf[0] != DEBUT_TRAME && buf[len_mes -1] != FIN_TRAME) // vérifie la présence des "><" du protocole
		return FALSE;

	*long_utile = len_mes - 2;
	strcpy(message,"");
	strncat(message,buf+1,*long_utile);     // on retire les "><" et notre TC est contenue dans message


	return TRUE;
}

/* **************************************************************************
METHODE :		CanalLecture()
TRAITEMENT:		Retourne le n° de canal pour utiliser lors de l'envoi des TS
***************************************************************************	*/
int CProtoED42::CanalLecture()
{
	pLogger.LOG_TRACE("Dans CProtoED42::CanalLecture()");

	int	valeur;

	EnterCriticalSection(&crit);
		valeur = lecture_canal;
	LeaveCriticalSection(&crit);

	return valeur;
}

/* **************************************************************************
METHODE :		ChangeCanalLecture()
TRAITEMENT:		Force un n° de canal pour utiliser lors de l'envoi des TS
***************************************************************************	*/
BOOL CProtoED42::ChangeCanalLecture(int	valeur)
{

	return TRUE;
}



int CProtoED42::ExtractData(istringstream &data, string res[], int length, char sep)
{
	pLogger.LOG_TRACE("Dans CProtoED42::ExtractData");

	for(int param_number = 1; param_number<length; param_number++)
		if(!getline(data, res[param_number], sep) && param_number != length-1)
		{
			return param_number;
		}

	string tmp;

	if(getline(data, tmp, sep)) return length+1;

	return 0;
}

//********************************************************************
void CProtoED42::sendAuthorizationError()
{
	pLogger.LOG_TRACE("Dans CProtoED42::sendAuthorizationError()");

	stringstream out;
	if((equip->getRemoteAdress()) <10)
	{
		out <<"a0"<<(equip->getRemoteAdress())<<"S#00"<<"RES1," << "107" << "," << cptSuccessfullCmd;
	}
	else
	{
		out <<"a"<<(equip->getRemoteAdress())<<"S#00"<<"RES1," << "107" << "," << cptSuccessfullCmd;
	}


	string reponse;

	reponse= out.str();

	EnvoyerTS((char*)LPCTSTR(CString(reponse.c_str())));
}

//********************************
//
//********************************
void CProtoED42:: sendAcq(int val)
{
	//TODO : Ne pas repondre lorsqu'on demande RST

	OutputDebugString("Dans : CProtoED42:: sendAcq(int val)!\n");
	pLogger.LOG_TRACE("Dans CProtoED42:: sendAcq(int val)");

	if(equip->getPasDeReponse())
		return;

	if (equip->GetResetEd42())
		return;

	stringstream out;
	string reponse = "";
	string reponseRcs = "";

	// Message Number page 158 TODO
	if(equip->getRepetition())
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: sendAcq(int val) et if(equip->getRepetition())");

		reponse.append(equip->getLastMessage());
		EnvoyerTS((char*)LPCTSTR(CString(reponse.c_str())));

		equip->setRepetition(FALSE);

		return;

	}

	// Contruction du message S
	string msgS = "S#" + S();

	//Construction de la réponce aXXN
	if ( bufCmd[0] != 'a')
		return;

	out << bufCmd[0] << bufCmd[1] << bufCmd[2];

	//Vérification de la présence du N
	if(bufCmd[3] == 'N')
	{
		out << bufCmd[3];

		if (bufCmd[4] != '0')
		{
			out << bufCmd[4];
			out << bufCmd[5];
		}
		else
		{
			if (bufCmd[5] != '0')
				out << bufCmd[5];
		}

		out << bufCmd[6] << msgS << bufCmd+7;
	}
	else
	{
		out << msgS << bufCmd+3;
	}

	pLogger.LOG_TRACE(out.str());

	//Recherche si envoi d'un RES
	if(isRES)
		out << RES();

	pLogger.LOG_TRACE("Dans CProtoED42:: sendAcq(int val) et retour de if(isRES)");
	pLogger.LOG_TRACE(out.str());

	//Mise à jour du flag isRES
	isRES = FALSE;

	// Reset du compteur de nrCommandInError
	equip->SetnrCommandInError(0);

	//*****************
	//Ajout du checksum
	//*****************
	//if (val != 0)
	//{

	reponse			= out.str();

	reponseRcs		= RCS(reponse);

	reponse.append(reponseRcs);

	//--------------------------------------------------------------
	// Attention 
	// Quand on détecte une erreur, il ne faut pas mémoriser le dernier numéro de la trame
	// car si on recoit la nouvelle trame qui ne contient plus d'erreur. Il faut pouvoir lui envoyer 
	// une nouvelle réponce et non la précédent qui a remonté une erreur.
	if(msgS.compare("S#00") != 0)
	{
		equip->setRepetition(FALSE);
		equip->setLastNumber(equip->getLastNumber()-1);
	}else
		equip->setLastMessage(reponse);

	OutputDebugString("Dans : CProtoED42:: sendAcq(int val) et EnvoyerTS!\n");
	pLogger.LOG_TRACE("Dans CProtoED42:: sendAcq(int val) et EnvoyerTS");
	ostringstream sss;
    sss << endl;
    sss << "\t" << "EnvoyerTS" << endl;
    sss << "\t" << "reponse: " << reponse << endl;
    pLogger.LOG_DEBUG(sss);
	pLogger.LOG_TRACE(sss.str());

	// Reset du Busy
	equip->SetStatusBusy(0);

	EnvoyerTS((char*)LPCTSTR(CString(reponse.c_str())));

	//}
	//*************************
	// Mise à jour Status Error
	//*************************
	//equip->setStatusErrorTable(SYNTAX_RCS, FALSE);
	//*************************

}

/* ***********************************************************************************
METHODE :		A()
TRAITEMENT:		Permet de définir à quel appareil le message va être envoyé (page 155)
*********************************************************************************** */
int CProtoED42:: A(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: A(string trame)");

 	if(atoi(trame.c_str()) == equip->getRemoteAdress())
	{
		char remoteAdr[2]="";

		if(equip->getRemoteAdress() < 10)
		{
			strcat(bufCmd, "a0");
		}
		else
		{
			strcat(bufCmd, "a");
		}

		itoa(equip->getRemoteAdress(), remoteAdr, 10);

		strcat(bufCmd, remoteAdr);
		//typeCmd = 1;

		return SUCCESS;
	}
	else
	{
		/*
		//Sachant que la remote address n'est pas bon, on devrait pas repondre (A VERIFIER)
		//Parametre invalide
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		//Pour l'erreur
		equip->setErrorTable(START_ERROR, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);
		*/

		return ERR_NON_CONFORME;
	}

	pLogger.LOG_TRACE("Fin CProtoED42:: A(string trame)");

}

/* **************************************************************************
METHODE :		ACV()
TRAITEMENT:		Requête de la clé active (page 175)
***************************************************************************	*/
int CProtoED42:: ACV(string trame)
{
	OutputDebugString("Dans : CProtoED42:: ACV(string trame) !\n");
	pLogger.LOG_TRACE("Dans CProtoED42:: ACV(string trame)");

	/*
	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() == 3 || equip->GetStatusS20() == 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0)
	{
		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}
	*/

	int ret = SUCCESS;
	int tmpMemIdx;

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return WRONG_PASSWORD;
	}

	if (testTrameFirst(trame, 0, 1, '?', &ret))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	/*
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return ERR_NON_CONFORME;
	}

	//La taille du message est trop grande ou vide
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if (trame[0] == '?')
	{
	*/

	OutputDebugString("Dans : CProtoED42:: ACV(string trame) et début!\n");

	if (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0)
	{
		OutputDebugString("Dans : CProtoED42:: ACV(string trame) et if (equip->GetStatusBusy() == 1) !\n");
		pLogger.LOG_TRACE("Dans : CProtoED42:: ACV(string trame) et if (equip->GetStatusBusy() == 1)");
		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}
		

	//Récupéreration de la valeur en binaire avant de la transformer en hexadécimal.
	stringstream timeDate;
	char buffer[3] = {0};
	char bufferIdx[3] = {0};

	tmpMemIdx = equip->GetActivatedKey();

	if (tmpMemIdx == DEFAULT_INVALID_VALUE_ED42)
	{
		strcat(bufCmd, "ACV255,#ff,#ff,255,255,0000,000000");
		//equip->SetKeyList(0);				// Param 25 : Flag : key listpage page 163	TODO
		equip->SetActiveKeyState(0);		// Param 29 : Flag : Active KEY state page 163 
		return SUCCESS;
	}

		itoa(tmpMemIdx,bufferIdx,10);
		TKeyManagement confKey = equip->GetKeyManagement(bufferIdx);


		// First 1..3
		strcat(bufCmd, "ACV");

		//Index mémoire de la clé
		// Param 4..6
		if(equip->GetOnlinePreset() == DEFAULT_INVALID_VALUE_ED42 || equip->GetOnlinePreset() > 16)
			itoa(DEFAULT_INVALID_VALUE_ED42,buffer,10);
		else
			itoa(tmpMemIdx, buffer,10);
		strcat(bufCmd, buffer);

		// Param 7..8
		//TAG Status (Data crypto)
		strcat(bufCmd, ",#");

		//Boucle sur les 8 presets de DATA crypto
		//Preset7 à preset0.
		// Param 9..10
		if(equip->GetOnlinePreset() == DEFAULT_INVALID_VALUE_ED42 || equip->GetOnlinePreset() > 16)
			strcat(bufCmd, "ff");
		else
			strcat(bufCmd, TagStatusCrypto(confKey.tag, equip->GetOnlinePreset(), 'D').c_str());

		// Param 11..12
		//TAG Status (Voice crypto)
		strcat(bufCmd, ",#");

		//Boucle sur les 8 presets de VOICE crypto
		//Preset15 à preset8.
		// Param 13..14
		if(equip->GetOnlinePreset() == DEFAULT_INVALID_VALUE_ED42 || equip->GetOnlinePreset() > 16)
			strcat(bufCmd, "ff");
		else
			strcat(bufCmd, TagStatusCrypto(confKey.tag, equip->GetOnlinePreset(), 'V').c_str());

		// Param 15
		strcat(bufCmd, ",");

		//Active status // TODO pour  4:Master
		// Param 16..18
		//Attention si on a un enum avec les valeurs 4 à 6 et 255 à l'intérieur.
		if(equip->GetOnlinePreset() == DEFAULT_INVALID_VALUE_ED42 || equip->GetOnlinePreset() > 16)
			itoa(DEFAULT_INVALID_VALUE_ED42,buffer,10);
		else
			if (equip->GetOperatingMode() == DATA_CRYPRO )
				itoa(6,buffer,10);
			else if (equip->GetOperatingMode() == VOICE_CRYPRO )
				itoa(5,buffer,10);
			else if (equip->GetOperatingMode() == OPE_MASTER )
				itoa(4,buffer,10);
		strcat(bufCmd, buffer);

		// Param 19
		strcat(bufCmd, ",");

		//Compteur de mise à jour
		// Param 20..22
		if(equip->GetOnlinePreset() == DEFAULT_INVALID_VALUE_ED42 || equip->GetOnlinePreset() > 16)
		{
			itoa(DEFAULT_INVALID_VALUE_ED42,buffer,10);
		}
		else
		{
			itoa(confKey.updateCount,buffer,10);
		}

		strcat(bufCmd, buffer);

		// Param 23
		strcat(bufCmd, ",");

		//Mise à zéro de elementBin
		//timeDate.str("");

		// Time
		// Param 24..27
		//Mise en place du format "XX"
		timeDate << setfill('0') << setw(2);
		//Pour les minutes
		//Attention si les minutes sont sauvegardées [00,10,20,30,40,50]
		itoa(confKey.minutes,buffer,10);
		timeDate << buffer;
		strcat(bufCmd, timeDate.str().c_str());

		//Mise à zéro de timeDate
		timeDate.str("");
		//Mise en place du format "XX"
		timeDate << setfill('0') << setw(2);

		//Pour les heures
		itoa(confKey.hours,buffer,10);
		timeDate << buffer;
		strcat(bufCmd, timeDate.str().c_str());

		// Param 28
		strcat(bufCmd, ",");

		//Mise à zéro de timeDate
		timeDate.str("");
		//Mise en place du format "XX"
		timeDate << setfill('0') << setw(2);

		// Param 29..34
		//Pour le jour
		itoa(confKey.days,buffer,10);
		timeDate << buffer;
		strcat(bufCmd, timeDate.str().c_str());

		//Mise à zéro de timeDate
		timeDate.str("");
		//Mise en place du format "XX"
		timeDate << setfill('0') << setw(2);

		//Pour le mois
		itoa(confKey.months,buffer,10);
		timeDate << buffer;
		strcat(bufCmd, timeDate.str().c_str());

		//Mise à zéro de timeDate
		timeDate.str("");
		//Mise en place du format "XX"
		timeDate << setfill('0') << setw(2);

		//Pour l'année
		itoa(confKey.years,buffer,10);
		timeDate << buffer;
		strcat(bufCmd, timeDate.str().c_str());

		equip->SetKeyList(0);				// Param 25 : Flag : key listpage page 163
		equip->SetActiveKeyState(0);		// Param 29 : Flag : Active KEY state page 163

		OutputDebugString("Fin : CProtoED42:: ACV(string trame) !\n");
		pLogger.LOG_TRACE("Fin CProtoED42:: ACV(string trame)");

		return SUCCESS;
}

/* **************************************************************************
METHODE :		ALM()
TRAITEMENT:		Buffer de l'alarme (page 169)
***************************************************************************	*/
int CProtoED42:: ALM(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: ALM(string trame)");

	char buffer[3] = "";
	bool alarmFind = FALSE;
	int i = 0;
	int ret = NOT_ERROR;

	if (testTrameFirst(trame, 0, 1, '?', &ret))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	strcat(bufCmd, "ALM");

	//Recherche de la première alarme - Alarm Message page 170
	TAlarm alarm;
	TVectorAlarm alarmList = equip->getAlarms();

	for(i=0;i<alarmList.size();i++)
	{
		alarm = equip->DecodeAlarm(alarmList[i]);
		if(alarm.used)
		{
			alarmFind = TRUE;
			break;
		}
	}

	if(alarmFind)
	{
		itoa(alarm.alarmType,buffer,10);		// Alarm Message page 170
		strcat(bufCmd, buffer);

		strcat(bufCmd, ",");

		itoa(alarm.alarmNumber,buffer,10);		// Alarm Message page 170
		strcat(bufCmd, buffer);

		// ------------------------------------------------------------------------------------
		// ATTENTION
		// Lors de la demande de cette commande, mettre à jour le flag alarm (SetAlarm) à FALSE
		// uniquement si il n'y a plus d'alarme dans le vector.
		// Suppression de l'alarme dans le vector.
		// ------------------------------------------------------------------------------------

		//Mise à zero de l'alarme
		//Position du flag de l'alarme
		equip->SetAlarm(0);							//equip->SetAlarm(FALSE);
	}
	else
		strcat(bufCmd, "0,0");

	pLogger.LOG_TRACE("Fin CProtoED42:: ALM(string trame)");
	
	return SUCCESS;
}

/* **************************************************************************
METHODE :		CES()
TRAITEMENT:		Etat da la machine de cryptage (page 165)
***************************************************************************	*/
int CProtoED42:: CES(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: CES(string trame)");

	int ret = SUCCESS;

	int tmpS20 = equip->GetStatusS20();

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	//if((equip->GetStatusS20() == 3 || equip->GetStatusS20() == 2)  && !equip->GetStatusNl())
	if((tmpS20 >= 2)  && !equip->GetStatusNl())
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;

		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(tmpS20 != 0  && !equip->GetStatusNl())
	{
		equip->setStatusErrorTable(CONFLICT, TRUE);
		//Force le RES
		isRES = TRUE;

		return CONFLICT;
	}
	

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);

		return ERR_NON_CONFORME;
	}

	if (testTrameFirst(trame, 0, 1, '?', &ret))
	{
		equip->setStatusErrorTable(ret, TRUE);

		return ERR_NON_CONFORME;
	}

	//if(trame[0] == '?')
	//{

		strcat(bufCmd, "CES#");

		strcat(bufCmd, IntToHexaString(equip->GetKeStatus()).c_str());
		strcat(bufCmd, ",#");
		strcat(bufCmd, IntToHexaString(equip->getSecureMode()).c_str());

		//Mise à jour du flag KEState utilisé par le SYS
		equip->SetKEState(0);			// Param 28

		pLogger.LOG_TRACE("Fin CProtoED42:: CES(string trame)");

		return SUCCESS;

}

/* **************************************************************************
METHODE :		CIK()
TRAITEMENT:		requête du statut du CIK (page 183)
***************************************************************************	*/
int CProtoED42:: CIK(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: CIK(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 )
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	int ret = NOT_ERROR;

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);

		return ERR_NON_CONFORME;
	}
	
	if (testTrameFirst(trame, 0, 1, '?', &ret))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	if (equip->GetKeStatus() == CIK_NOT_PLUGED)
		return CIK_NOT_PLUGED;

	char buffer[3] = {0};

	strcat(bufCmd, "CIK#");

	//CIK Status
	strcat(bufCmd, IntToHexaString(equip->GetStatusCik(),2).c_str());

	strcat(bufCmd, ",");

	//User number
	itoa(equip->GetUserCik(),buffer,10);
	strcat(bufCmd, buffer); 

	strcat(bufCmd, ",#");

	//Compteur d'activité sur la programmation du CIK
	strcat(bufCmd, IntToHexaString(equip->GetCounterCik(),2).c_str());
	
	pLogger.LOG_TRACE("Fin CProtoED42:: CIK(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		CV()
TRAITEMENT:		Requête d'une clé (page 173)
***************************************************************************	*/
int CProtoED42:: CV(string trame)
{
	//OutputDebugString("Dans : CProtoED42:: CV(string trame)!\n");
	pLogger.LOG_TRACE("Dans CProtoED42:: CV(string trame)");

	int tmpS20 = equip->GetStatusS20();

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	//if(equip->GetStatusS20() == 3 || equip->GetStatusS20() == 2)
	if(tmpS20 == 3)
	{
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		//Force le RES
		isRES = TRUE;
		return WRONG_COMMAND;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(tmpS20 != 0 )
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: CV(string trame) et if(tmpS20 != 0 || equip->GetStatusBusy() == 1");
		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	int ret = SUCCESS;

		if(!(equip->getAuthentified()))
		{
			//Pour l'erreur
			equip->setErrorTable(WRONG_PASSWORD, TRUE);
			return ERR_NON_CONFORME;
		}

		if (testTrameFirst(trame, 0, 3, '?', &ret, true, 1))
		{
			equip->setStatusErrorTable(ret, TRUE);
			return ERR_NON_CONFORME;
		}

		//Récupéreration de la valeur en binaire avant de la transformer en hexadécimal.
		stringstream timeDate;
		char buffer[3]		= {0};
		char bufferIdx[3]	= {0};
		const int Invalid	= 255;

		string tmpMemIdx = trame.substr(0, trame.length()-1);

		//On vérifie que la variable location est bien entre 1 et 96
		if(atoi(tmpMemIdx.c_str()) < 1 || atoi(tmpMemIdx.c_str()) > 96)
		{
			//Parametre invalide
			equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

			return ERR_NON_CONFORME;
		}

		TKeyManagement confKey = equip->GetKeyManagement(tmpMemIdx);

		// First 1..2
		strcat(bufCmd, "CV");

		//Index mémoire de la clé
		// Param 3..5
		itoa(confKey.variableLocation, buffer,10);
		strcat(bufCmd, buffer);

		// Param 6..7
		//TAG Status (Data crypto)
		strcat(bufCmd, ",#");
		//Boucle sur les 8 presets de DATA crypto
		//Preset7 à preset0.
		// Param 8..9
		strcat(bufCmd, TagStatusCrypto(confKey.tag, confKey.variableLocation, 'D').c_str());

		// Param 10..11
		//TAG Status (Voice crypto)
		strcat(bufCmd, ",#");

		//Boucle sur les 8 presets de VOICE crypto
		//Preset15 à preset8.
		// Param 12..13
		strcat(bufCmd, TagStatusCrypto(confKey.tag, confKey.variableLocation, 'V').c_str());

		// Param 14
		strcat(bufCmd, ",");

		//Active status // TODO pour  4:Master
		// Param 15..17
		//Attention si on a un enum avec les valeurs 4 à 6 et 255 à l'intérieur.
		if (equip->GetActivatedKey() == confKey.variableLocation)
		{
			switch(equip->GetOperatingMode()){
				case DATA_CRYPRO:
					itoa(6,buffer,10);
					break;
				case VOICE_CRYPRO:
					itoa(5,buffer,10);
					break;
				case OPE_MASTER:
					itoa(4,buffer,10);
					break;
				default:
					itoa(DEFAULT_INVALID_VALUE_ED42,buffer,10);
					break;
			}
		}else
		{
			itoa(DEFAULT_INVALID_VALUE_ED42, buffer,10);
		}
		strcat(bufCmd, buffer);

		// Param 18
		strcat(bufCmd, ",");

		//Compteur de mise à jour
		// Param 19..21
		itoa(confKey.updateCount,buffer,10);
		strcat(bufCmd, buffer);

		// Param 22
		strcat(bufCmd, ",");

		//Mise à zéro de elementBin
		//timeDate.str("");

		// Time
		// Param 23..26
		//Mise en place du format "XX"
		timeDate << setfill('0') << setw(2);
		//Pour les minutes
		//Attention si les minutes sont sauvegardées [00,10,20,30,40,50]
		itoa(confKey.minutes,buffer,10);
		timeDate << buffer;
		strcat(bufCmd, timeDate.str().c_str());

		//Mise à zéro de timeDate
		timeDate.str("");
		//Mise en place du format "XX"
		timeDate << setfill('0') << setw(2);

		//Pour les heures
		itoa(confKey.hours,buffer,10);
		timeDate << buffer;
		strcat(bufCmd, timeDate.str().c_str());

		// Param 27
		strcat(bufCmd, ",");

		//Mise à zéro de timeDate
		timeDate.str("");
		//Mise en place du format "XX"
		timeDate << setfill('0') << setw(2);


		// Param 28..33
		//Pour le jour
		itoa(confKey.days,buffer,10);
		timeDate << buffer;
		strcat(bufCmd, timeDate.str().c_str());

		//Mise à zéro de timeDate
		timeDate.str("");
		//Mise en place du format "XX"
		timeDate << setfill('0') << setw(2);

		//Pour le mois
		itoa(confKey.months,buffer,10);
		timeDate << buffer;
		strcat(bufCmd, timeDate.str().c_str());

		//Mise à zéro de timeDate
		timeDate.str("");
		//Mise en place du format "XX"
		timeDate << setfill('0') << setw(2);

		//Pour l'année
		itoa(confKey.years,buffer,10);
		timeDate << buffer;
		strcat(bufCmd, timeDate.str().c_str());

		//strcat(bufCmd, timeDate.str().c_str());

		pLogger.LOG_TRACE("Fin CProtoED42:: CV(string trame)");

		return SUCCESS;
}

/* **************************************************************************
METHODE :		CVBTA()
TRAITEMENT:		tag bilateral d'une clé (page 178)
***************************************************************************	*/
int CProtoED42:: CVBTA(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: CVBTA(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 )
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	int ret = NOT_ERROR;
	size_t found;

	//Envoi d'un RES
	isRES = TRUE;


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return ERR_NON_CONFORME;
	}

	if (testTrameFirst(trame, 0, 4, '?', &ret, false, 10))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	if (equip->GetKeStatus() == CIK_NOT_PLUGED)
		return CIK_NOT_PLUGED;

	string tmpMemIdx = trame.substr(0, trame.length()-2);

	// ************************************************************************
	//On vérifie que la variable location est bien entre 1 et 96
	// ************************************************************************
	if(atoi(tmpMemIdx.c_str()) < 1 || atoi(tmpMemIdx.c_str()) > 96)
	{
		//Pour l'erreur
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	// ************************************************************************
	// Vérification si la variable location demande a été chargé par un LOAD CV
	// La variable location n'est pas chargé si updateCount = 255
	// ************************************************************************
	TKeyManagement keyManagement = equip->GetKeyManagement(tmpMemIdx.c_str());
	if(keyManagement.updateCount == 255)	

	{
		//Pour l'erreur
		equip->setErrorTable(VARIABLE_NOT_DEFINED, TRUE);

		return ERR_NON_CONFORME;
	}

	// ************************************************************************
	// Vérification si la variable 'autosync' est valide.
	// ************************************************************************
	found=trame.find(',');
	tmpMemIdx = trame.substr(found+1, trame.length()-1);

	if(atoi(tmpMemIdx.c_str()) < 0 || atoi(tmpMemIdx.c_str()) > 1)
	{
		//Pour l'erreur
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	pLogger.LOG_TRACE("Fin CProtoED42:: CVBTA(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		CVBUD()
TRAITEMENT:		update bilateral d'une clé (page 178)
***************************************************************************	*/
int CProtoED42:: CVBUD(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: CVBUD(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 )
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;
	int ret = NOT_ERROR;
	char buffer[3];


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return ERR_NON_CONFORME;
	}

	if (testTrameFirst(trame, 0, 1, '0', &ret, true, 2))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	if(equip->GetOperatingStatus() == OFFLINE)
	{
		//Precondition "ONLINE" mode Compact User Guide page 55
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return WRONG_COMMAND;
	}

	if (equip->GetKeStatus() == CIK_NOT_PLUGED)
		return CIK_NOT_PLUGED;

	
	if (equip->GetTransmissionMode() != DIGITAL && equip->GetOperatingMode() != DATA_CRYPRO )
	{
		//Precondition mode Compact User Guide page 55
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return WRONG_COMMAND;
	}

	if (equip->GetOperatingMode() != OPE_MASTER)
	{
		//Precondition "OPE_MASTER" mode Compact User Guide page 55
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return WRONG_COMMAND;
	}

	itoa(equip->GetActivatedKey(),buffer,10);

	TKeyManagement keyManagement = equip->GetKeyManagement(buffer);

	//MessageBox("BILATERAL UPDATE OK !","Information",MB_ICONINFORMATION);
	keyManagement.updateCount	= keyManagement.updateCount+1;
	//Sauvegarde 
	equip->SetKeyManagement(buffer,keyManagement);
	//Set du flag : Key List
	equip->SetKeyList(1);
		
	pLogger.LOG_TRACE("Fin CProtoED42:: CVBUD(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		CVDEL()
TRAITEMENT:		supprime une clé (page 176)
***************************************************************************	*/
int CProtoED42:: CVDEL(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: CVDEL(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 )
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;
	int ret = NOT_ERROR;

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return ERR_NON_CONFORME;
	}

	if (testTrameFirst(trame, 0, 2, '0', &ret, false, 3, true))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	if (equip->GetKeStatus() == CIK_NOT_PLUGED)
		return CIK_NOT_PLUGED;

	
	int param = atoi(trame.c_str());

	//On vérifie que la variable location est entre 1 et 96
	if(param < 1 || param > 96)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	TKeyManagement keyManagement = equip->GetKeyManagement(trame);

	// Vérification si la variable location demande a été chargé par un LOAD CV
	if (equip->GetCvChargement(&keyManagement))
	{
		equip->setErrorTable(VARIABLE_NOT_DEFINED, TRUE);
		return ERR_NON_CONFORME;
	}

	//On ne doit pas supprimer une clé avec un tag
	if(keyManagement.tag.compare("--------") == 0)
	{
		keyManagement.days			= 00;
		keyManagement.months		= 00;
		keyManagement.years			= 00;
		keyManagement.hours			= 00;
		keyManagement.minutes		= 00;
		keyManagement.updateCount	= 255;

		//Sauvegarde 
		equip->SetKeyManagement(trame,keyManagement);
		equip->setModifVue(true);
	}
	else
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	pLogger.LOG_TRACE("Fin CProtoED42:: CVDEL(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		CVDLA()
TRAITEMENT:		supprime toutes les clés (page 177)
***************************************************************************	*/
int CProtoED42:: CVDLA(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: CVDLA(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 )
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;
	int ret = NOT_ERROR;


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}


	if (testTrameFirst(trame, 0, 1, '0', &ret, true, 2, true))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	if (equip->GetKeStatus() == CIK_NOT_PLUGED)
		return CIK_NOT_PLUGED;

	char buffer[3] = {0};
	TKeyManagement keyManagement;

	for(int i=1;i<97;i++)
	{
		itoa(i,buffer,10);
		keyManagement = equip->GetKeyManagement(buffer);

		keyManagement.days			= 00;
		keyManagement.months		= 00;
		keyManagement.years			= 00;
		keyManagement.hours			= 00;
		keyManagement.minutes		= 00;
		keyManagement.updateCount	= 255;
		keyManagement.tag			= "--------";
	
		//Sauvegarde 
		equip->SetKeyManagement(buffer,keyManagement);

	}

	// Param 30 Flag key memory
	equip->SetKeyMemory(0);

	pLogger.LOG_TRACE("Fin CProtoED42:: CVDLA(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		CVLG()
TRAITEMENT:		update la vue sur les clés (page 179)
***************************************************************************	*/
int CProtoED42:: CVLG(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: CVLG(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 )
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;
	int ret = NOT_ERROR;


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return ERR_NON_CONFORME;
	}

	/*
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		//Pour l'erreur
		equip->setErrorTable(FORMAT_ERROR, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		//Pour l'erreur
		equip->setErrorTable(FORMAT_ERROR, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}
	*/

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	if (testTrameFirst(trame, 0, 1, '0', &ret, true, 2))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	// Param 30 Flag key memory
	equip->SetKeyMemory(0);

	pLogger.LOG_TRACE("Fin CProtoED42:: CVLG(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		CVLR()
TRAITEMENT:		requête d'une vue sur les clés (page 179)
***************************************************************************	*/
 int CProtoED42:: CVLR(string trame)
{
	 pLogger.LOG_TRACE("Dans CProtoED42:: CVLR(string trame)");

	 int tmpS20 = equip->GetStatusS20();

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	//if(equip->GetStatusS20() == 3 || equip->GetStatusS20() == 2)
	if(tmpS20 >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(tmpS20 != 0)
	{
		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	int ret = SUCCESS;

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return ERR_NON_CONFORME;
	}

	if (testTrameFirst(trame, 0, 1, '?', &ret))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}


	//strcat(bufCmd, "CVLR#03,#02000000,#00000001"); // [1,2],[58],65
	//strcat(bufCmd, "CVLR#00000003,#40010100,#40000001"); // [1,2],[41,49,63],65,95
	//strcat(bufCmd, "CVLR#00000003,#40010100,#20000001"); // [1,2],[41,49,63],65,94
	//strcat(bufCmd, "CVLR#00000003,#40010100,#00010001"); // [1,2],[41,49,63],65,81
	//strcat(bufCmd, "CVLR#00000003,#40010100,#00008001"); // [1,2],[41,49,63],65,80
	//strcat(bufCmd, "CVLR#20000003,#40010100,#00008001"); // [1,2,30],[41,49,63],65,80
	//strcat(bufCmd, "CVLR#00004003,#40010100,#00008001"); // [1,2,15],[41,49,63],65,80
	//strcat(bufCmd, "CVLR#40000003,#40010100,#00008001"); // [1,2,31],[41,49,63],65,80
	//strcat(bufCmd, "CVLR#80000003,#40010100,#00008001"); // [1,2,32],[41,49,63],65,80
	//strcat(bufCmd, "CVLR#00000003,#80000000,#00000000"); // [1,2,32],[41,49,63],65,80
	//strcat(bufCmd, "CVLR#00000003,#00200000,#00000400"); // [1,2],[54],75
	//equip->SetKeyList(0);
	//return SUCCESS;

	TMapKeyManagement confKey = equip->GetMapKeyManagement();

	// First 1..4
	strcat(bufCmd, "CVLR");

	// Param 5
	strcat(bufCmd, "#");

	// Param 6..13
	// Key memory inde 0..31
	//strcat(bufCmd, elementHex.c_str());
	strcat(bufCmd, KeyMemoryIndex(confKey, 17, 32).c_str());
	strcat(bufCmd, KeyMemoryIndex(confKey, 1, 16).c_str());


	// Param 14..15
	strcat(bufCmd, ",#");

	// Param 6..23
	// Key memory inde 32..63
	strcat(bufCmd, KeyMemoryIndex(confKey, 49, 64).c_str());
	strcat(bufCmd, KeyMemoryIndex(confKey, 33, 48).c_str());


	// Param 24..55
	strcat(bufCmd, ",#");

	// Param 26..33
	// Key memory inde 64..95
	strcat(bufCmd, KeyMemoryIndex(confKey, 81, 96).c_str());
	strcat(bufCmd, KeyMemoryIndex(confKey, 65, 80).c_str());


	equip->SetKeyList(0);	// Param 25 : Flag : key listpage 163
	//ret = SUCCESS;

	pLogger.LOG_TRACE("Fin CProtoED42:: CVLR(string trame)");

	return ret;
}

/* **************************************************************************
METHODE :		CVTAG()
TRAITEMENT:		tag une clé (page 176)
***************************************************************************	*/
int CProtoED42:: CVTAG(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: CVTAG(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		pLogger.LOG_TRACE("Dans CProtoED42:: CVTAG(string trame) CONFLICT.");
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;
	int ret = NOT_ERROR;

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return ERR_NON_CONFORME;
	}

	if (equip->GetKeStatus() == CIK_NOT_PLUGED)
		return CIK_NOT_PLUGED;

	if (testTrameFirst(trame, 0, 5, '?', &ret, false, 5, false))			//if (testTrameFirst(trame, 0, 5, '?', &ret, false, 5, true))
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: CVTAG(string trame) ERR_NON_CONFORME.");
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		pLogger.LOG_TRACE("Dans CProtoED42:: CVTAG(string trame) ERR_NO_REMOTE_MODE.");
		return ERR_NO_REMOTE_MODE;
	}

	pLogger.LOG_TRACE("Dans CProtoED42:: CVTAG(string trame) debut traitement.");


	TKeyManagement keyManagement;

	string variableLocation = "";
	int presetNumber = 0;
	char buffer[3] = {0};

	int debut = 0;
	int fin = trame.find_first_of(",",debut);

	variableLocation = trame.substr(debut,fin);

	int param = atoi(variableLocation.c_str());

	if(param < 1 || param > 96)
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: CVTAG(string trame) et if(param < 1 || param > 96)");

		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return INVALID_PARAMETER;
	}

	// param : 2 Preset number
	presetNumber = atoi(trame.substr(fin+1,trame.size()).c_str());

	if(presetNumber < 0 || presetNumber > 15
		|| (presetNumber == 0 && trame.substr(fin+1,trame.size()).compare("0") != 0))
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: CVTAG(string trame) et presetNumber NOk)");

		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return INVALID_PARAMETER;
	}

	keyManagement = equip->GetKeyManagement(variableLocation);

	// ************************************************************************
	// Vérification si la variable location demande a été chargé par un LOAD CV
	// ************************************************************************
	if (equip->GetCvChargement(&keyManagement))
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: CVTAG(string trame) et if (equip->GetCvChargement(&keyManagement)))");

		equip->setErrorTable(VARIABLE_NOT_DEFINED, TRUE);
		equip->SetError(TRUE);
		
		return VARIABLE_NOT_DEFINED;
	}

	//Mise à jour, il faut retirer le nouveau preset dans les autres variables locations.
	for(int cpt=1;cpt<97;cpt++)
	{
		//Il ne faut pas effacer le tag à modifier. 
		if(param != cpt)
		{
			itoa(cpt,buffer,10);
			keyManagement = equip->GetKeyManagement(buffer);
			keyManagement.tag[presetNumber%8] = '-';
			equip->SetKeyManagement(buffer,keyManagement);
		}
	}
	
	keyManagement = equip->GetKeyManagement(variableLocation);

	//Tag sur un preset DATA
	pLogger.LOG_TRACE("Dans CProtoED42:: CVTAG(string trame) et Tag sur un preset DATA");
	if(presetNumber < 8)
	{
		if(keyManagement.tag[presetNumber] == 'V')
			keyManagement.tag[presetNumber] = 'B';
		else
			keyManagement.tag[presetNumber] = 'D';
	}
	//Tag sur un preset VOICE
	else
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: CVTAG(string trame) et Tag sur un preset VOICE");
		if(keyManagement.tag[presetNumber%8] == 'D')
			keyManagement.tag[presetNumber%8] = 'B';
		else
			keyManagement.tag[presetNumber%8] = 'V';
	}	
	
	//Sauvegarde 
	equip->SetKeyManagement(variableLocation, keyManagement);
	
	pLogger.LOG_TRACE("Fin CProtoED42:: CVTAG(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		CVUPD()
TRAITEMENT:		update une clé (page 177)
***************************************************************************	*/
int CProtoED42:: CVUPD(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: CVUPD(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if (equip->GetOperatingStatus() == ONLINE)
	{
		//Parametre invalide
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return WRONG_COMMAND;
	}
	
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 2 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if (equip->GetKeStatus() == CIK_NOT_PLUGED)
		return CIK_NOT_PLUGED;

	int param = atoi(trame.c_str());

	if(param < 1 || param > 96)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	if(equip->GetOperatingStatus() == ONLINE)
	{
		//Precondition "OFFLINE" mode Compact User Guide page 55
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return WRONG_COMMAND;
	}


	TKeyManagement keyManagement = equip->GetKeyManagement(trame);

	// Vérification si la variable location demande a été chargé par un LOAD CV
	// La variable location n'est pas chargé si updateCount = 255
	if(keyManagement.updateCount == 255)
	{
		//Parametre invalide
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		//Pour l'erreur
		equip->setErrorTable(VARIABLE_NOT_DEFINED, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	//On ne peut pas mettre à jour un variable si elle a dépassé l'update limit
	if(equip->GetUpdateLimit() <= keyManagement.updateCount)
	{
		//Pour l'erreur
		equip->setErrorTable(UPDATE_LIMIT_EXCEEDED, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	keyManagement.updateCount++;

	//Sauvegarde 
	equip->SetKeyManagement(trame,keyManagement);

	equip->setModifVue(TRUE);

	pLogger.LOG_TRACE("Fin CProtoED42:: CVUPD(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		DEFPS()
TRAITEMENT:		requête des paramètres par défaut (page 189)
***************************************************************************	*/
int CProtoED42:: DEFPS(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: DEFPS(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 2 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame[trame.size()-1] != '?')
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	//cmd.clear();

	//Récupération du preset demandé
	string preset = trame.substr(0,trame.size()-1);

	if(preset[0] < '0' || preset[0] > '3')
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	strcat(bufCmd, "DEFPS");

	// param : 1 Preset index
	strcat(bufCmd, preset.c_str());


	TGeneralParameters presetEnCours	= equip->GetDefaultGeneralParameters(preset);
	TDigitalDCE digitalDceEnCours		= equip->GetDefaultDigitalDCEParameters(preset);
	TDigitalDTE digitalDteEnCours		= equip->GetDefaultDigitalDTEParameters(preset);
	TAnalogDCE analogDceEnCours			= equip->GetDefaultAnalogDCEParameters(preset);
	TAnalogDTE analogDteEnCours			= equip->GetDefaultAnalogDTEParameters(preset);

	//Construction de la suite de la trame qui est identique au REQPS
	buildTrameREQPS(presetEnCours,digitalDceEnCours,digitalDteEnCours,analogDceEnCours,analogDteEnCours);

	pLogger.LOG_TRACE("Fin CProtoED42:: DEFPS(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		ERR()
TRAITEMENT:		accès au buffer d'erreur (page 169)
***************************************************************************	*/
int CProtoED42:: ERR(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: ERR(string trame)");
	// TODO : traitement d'une seule erreur !! ??

	if(equip->GetStatusS20() == 3)
	{
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		//Force le RES
		isRES = TRUE;
		return WRONG_COMMAND;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0)
	{
		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("?") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	char buffer[4] = "";
	bool errorFind = FALSE;
	int i = 0;

	strcat(bufCmd, "ERR");

	//Recherche de la première erreur
	TError error;
	TVectorError errorList = equip->getErrors();

	//On effectue une recherche de 1 .. max
	//L'indice 0 est pour la commande RES
	for(i=1;i<errorList.size();i++)
	{
		error = equip->DecodeError(errorList[i]);
		if(error.used)
		{
			errorFind = TRUE;
			break;
		}
	}

	if(errorFind)
	{
		itoa(error.errorNumbers,buffer,10);
		strcat(bufCmd, buffer);

		strcat(bufCmd, ",");

		itoa(error.extendedCodes,buffer,10);
		strcat(bufCmd, buffer);

		// ------------------------------------------------------------------------------------
		// ATTENTION
		// Lors de la demande de cette commande, mettre à jour le flag error (SetError) à FALSE
		// uniquement si il n'y a plus d'erreur dans le vector.
		// Supression de l'erreur dans le vector.
		// ------------------------------------------------------------------------------------

		//Mise à zero de l'erreur
/*		equip->setErrorTable(i,FALSE);
		errorList = equip->getErrors();
		
		//Recherche d'une nouvelle erreur à partir de la dernier erreur.
		errorFind = FALSE;
		for(i=i;i<errorList.size();i++)
		{
			error = equip->DecodeError(errorList[i]);
			if(error.used)
			{
				errorFind = TRUE;
				break;
			}
		}
		
		if(!errorFind)
		{
			//Position du flag de l'erreur
			equip->SetError(FALSE);
		}*/

		//Position du flag de l'erreur
		equip->SetError(FALSE);
	}
	else
		strcat(bufCmd, "0,0");

	pLogger.LOG_TRACE("Fin CProtoED42:: ERR(string trame)");
	
	return SUCCESS;
}

/* **************************************************************************
METHODE :		INI()
TRAITEMENT:		permet d'initialiser une connection et vérifie la version
				du protocole (page 155 et page 160)
***************************************************************************	*/
int CProtoED42:: INI(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: INI(string trame)");

	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("?") != 0 || trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	//Modification S#20 (sequence conflict)
	equip->SetStatusS20(2);
	/*
	if(equip->GetStatusS20() == 3)
	{
		equip->SetStatusS20(2);
	}
	*/

	char buffer[3] = "";


	strcat(bufCmd, "INI");
	itoa(equip->getProtocolNumber(), buffer, 10);
	strcat(bufCmd, buffer);

	strcat(bufCmd, ",#");
	strcat(bufCmd, IntToHexaString(equip->GetKeStatus()).c_str());

	equip->setAuthentified(FALSE);
	equip->SetKeyList(1);								// Param 25 : Flag : key list
	equip->SetKEState(1);								// Param 28 : Flag : KE state

	pLogger.LOG_TRACE("Fin CProtoED42:: INI(string trame)");
	
	return SUCCESS;
}

/* **************************************************************************
METHODE :		KEK()
TRAITEMENT:		requête d'une KEK (page 181)
***************************************************************************	*/
int CProtoED42:: KEK(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: KEK(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: KEK(string trame) et if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");
		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("?") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	TKeyManagement confKey = equip->GetKeyManagement("0");

	char buffer[4] = {0};

	strcat(bufCmd, "KEK");
	itoa(confKey.kekLoaded, buffer, 10);
	strcat(bufCmd, buffer);
	strcat(bufCmd, ",#FF");
	strcat(bufCmd, ",#00");
	strcat(bufCmd, ",255");
	itoa(confKey.updateCount, buffer, 10);
	strcat(bufCmd, ",");
	strcat(bufCmd, buffer);
	strcat(bufCmd, ",");

	//Time
	itoa(confKey.minutes, buffer, 10);
	if(confKey.minutes < 10)
		strcat(bufCmd, "0");
	strcat(bufCmd, buffer);
	itoa(confKey.hours, buffer, 10);
	if(confKey.hours < 10)
		strcat(bufCmd, "0");
	strcat(bufCmd, buffer);
	strcat(bufCmd, ",");

	//Date
	itoa(confKey.days, buffer, 10);
	if(confKey.days < 10)
		strcat(bufCmd, "0");
	strcat(bufCmd, buffer);
	itoa(confKey.months, buffer, 10);
	if(confKey.months < 10)
		strcat(bufCmd, "0");
	strcat(bufCmd, buffer);
	itoa(confKey.years, buffer, 10);
	if(confKey.years < 10)
		strcat(bufCmd, "0");
	strcat(bufCmd, buffer);

	pLogger.LOG_TRACE("Fin CProtoED42:: KEK(string trame)");
	
	return SUCCESS;
}

/* **************************************************************************
METHODE :		KEKDL()
TRAITEMENT:		supprime une KEK (page 182)
***************************************************************************	*/
int CProtoED42:: KEKDL(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: KEKDL(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if (equip->GetOperatingStatus() == ONLINE)
	{
		//Parametre invalide
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return WRONG_COMMAND;
	}
	
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("0") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	if (equip->GetKeStatus() == CIK_NOT_PLUGED)
		return CIK_NOT_PLUGED;


	TKeyManagement keyManagement = equip->GetKeyManagement("0");

	keyManagement.kekLoaded		= 255;
	keyManagement.days			= 00;
	keyManagement.months		= 00;
	keyManagement.years			= 00;
	keyManagement.hours			= 0;
	keyManagement.minutes		= 0;
	keyManagement.updateCount	= 255;
	keyManagement.tag			= "--------";
	
	//Sauvegarde 
	equip->SetKeyManagement("0",keyManagement);

	pLogger.LOG_TRACE("Fin CProtoED42:: KEKDL(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		N()
TRAITEMENT:		Déclenche le compteur de message (page158)
***************************************************************************	*/
int CProtoED42:: N(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: N(string trame)");

	//La fonction atoi remonte un 0 si le string n'est pas un integer.
	if(atoi(trame.c_str()) < 0 || atoi(trame.c_str()) > 999 
		|| (atoi(trame.c_str()) == 0 && trame.compare("0") != 0)) 
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	// Simulation errorMessageNumber
	if(equip->getErrorMSG())
	{
		strcat(bufCmd, "N001");
		return SUCCESS;
	}
	// Vérificatioin sur la suite de la numerotation
	if (atoi(trame.c_str()) == equip->getLastNumber())
	{
		equip->setRepetition(TRUE);
		return SUCCESS;
	}

	equip->setLastNumber(atoi(trame.c_str()));

	if(atoi(trame.c_str()) < 10)
		{
			strcat(bufCmd, "N00");
		}
	else if (atoi(trame.c_str()) < 100)
		{
			strcat(bufCmd, "N0");
		}
	else
	{
		strcat(bufCmd, "N");
	}

    strcat(bufCmd, trame.c_str());

	pLogger.LOG_TRACE("Fin CProtoED42:: N(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		OFL()
TRAITEMENT:		Passer en mode OFFLINE (page 171)
***************************************************************************	*/
int CProtoED42:: OFL(string trame)
{
	OutputDebugString("Dans : OFL(string trame)!\n");
	pLogger.LOG_TRACE("Dans CProtoED42:: OFL(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;
	int ret = NOT_ERROR;

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return ERR_NON_CONFORME;
	}

	if (testTrameFirst(trame, 0, 1, '0', &ret))
	{
		pLogger.LOG_TRACE("Fin CProtoED42:: OFL(string trame) et return ERR_NON_CONFORME");

		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	if (equip->GetKeStatus() == CIK_NOT_PLUGED)
		return CIK_NOT_PLUGED;

	if (equip->GetOperatingStatus() == OFFLINE)
		return ERR_NON_CONFORME;

	equip->SetStatusBusy(1);

	// Mise à jour des flag's
	equip->SetOnlinePresetStatus(1);					// Param 21 : Flag : Online preset
	equip->SetActiveKeyState(1);						// Param 29 : Flag : Active KEY state
	equip->SetKeyList(1);								// Param 25 : Flag : key list
	equip->SetOperatingStatus(OFFLINE);
	equip->SetOnlinePreset(DEFAULT_INVALID_VALUE_ED42);
	equip->SetActivatedKey(DEFAULT_INVALID_VALUE_ED42);
	equip->SetStatusTx(0);
	equip->SetStatusRx(0);

	pLogger.LOG_TRACE("Fin CProtoED42:: OFL(string trame) et return SUCCESS");
	
	return SUCCESS;
}

/* **************************************************************************
METHODE :		ONL()
TRAITEMENT:		Passer en mode ONLINE (page 148/171)
***************************************************************************	*/
int CProtoED42:: ONL(string trame)
{
    //>A01N178S?ONL8RCS#43<

	//OutputDebugString("Dans : CProtoED42:: ONL(string trame) !\n");
	pLogger.LOG_TRACE("Dans CProtoED42:: ONL(string trame)");
	pLogger.LOG_TRACE(trame);

	int tmpS20 = equip->GetStatusS20();

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	//if(equip->GetStatusS20() >= 2)
	if(tmpS20 >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(tmpS20 != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(tmpS20 != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;
	int ret = SUCCESS;

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return ERR_NON_CONFORME;
	}

	if (testTrameFirst(trame, 0, 2, '?', &ret, false, 6, true))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: ONL(string trame) et if(equip->GetRemoteTC() == LOCAL_TC)");
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return NOT_REMOTE_MODE;
	}

	//La fonction atoi remonte un 0 si le string n'est pas un integer.
	if(atoi(trame.c_str()) < 0 || atoi(trame.c_str()) > 31 
		|| (atoi(trame.c_str()) == 0 && trame.compare("0") != 0)) 
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: ONL(string trame) et return ERR_NON_CONFORME");

		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}
		
	if (equip->GetKeStatus() == CIK_NOT_PLUGED)
		return CIK_NOT_PLUGED;


	//**********************************
	// Test pour le CV a utiliser
	//**********************************

	// TODO vérification si pour un VC ou DC le préset est taggée

	// Activation
	equip->activationPreset(trame.c_str());

	int tmpMemIdx = equip->GetMemoryIndexOfKey(equip->GetOnlinePreset(),equip->GetOperatingMode());

	if (equip->GetOperatingMode() == 0 || equip->GetOperatingMode() == 1)
	{
		//Mise à jour du flag KEState utilisé par le SYS
		equip->SetKeyList(1);						// Param 25 : Flag : key list
		equip->SetKEState(1);						// Param 28 : Flag : KE state
		equip->SetActiveKeyState(1);				// Param 29 : Flag : Active KEY state

	}

	if (tmpMemIdx == DEFAULT_INVALID_VALUE_ED42 && (equip->GetOperatingMode() == 0 || equip->GetOperatingMode() == 1)) //TODO
	{
		pLogger.LOG_TRACE("Dans : CProtoED42:: ONL(string trame) et if (tmpMemIdx == DEFAULT_INVALID_VALUE_ED42....");
		equip->setErrorTable(VARIABLE_NOT_DEFINED, TRUE);
		return ERR_NON_CONFORME; 
	}

	equip->SetStatusBusy(1);

	equip->SetOnlinePreset(atoi(trame.c_str()));
	equip->SetOnlinePresetStatus(1);						// Param 21 : Flag : Online preset
	equip->SetActivatedKey(tmpMemIdx);						// pour ACV
	equip->SetOperatingStatus(ONLINE);
	equip->setED42Lock(false);

	pLogger.LOG_TRACE("Fin CProtoED42:: ONL(string trame) et return SUCCESS;");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		OPS()
TRAITEMENT:		Retourne le preset qui est online (page 172)
***************************************************************************	*/
int CProtoED42:: OPS(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: OPS(string trame)");

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("?") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	char buffer[4] = {0};

	strcat(bufCmd, "OPS");
	itoa(equip->GetOnlinePreset(),buffer,10);
	strcat(bufCmd, buffer);
	equip->SetOnlinePresetStatus(0);			// Param 21 : Flag : Online preset

	pLogger.LOG_TRACE("Fin CProtoED42:: OPS(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		PSS()
TRAITEMENT:		Requête d'un changement d'état de preset (page 190)
***************************************************************************	*/
int CProtoED42:: PSS(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: PSS(string trame)");

	if(!(equip->getRemoteStatus()))
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);

		return ERR_NO_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0)
	{
		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;

		return ERR_NON_CONFORME;
	}

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("?") == 0)
	{
		strcat(bufCmd, "PSS#");
		strcat(bufCmd, IntToHexaString(equip->GetPresetList(),8).c_str());
	}
	else
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	pLogger.LOG_TRACE("Fin CProtoED42:: PSS(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		PWCHG()
TRAITEMENT:		changer le mot de passe (page 182)
***************************************************************************	*/
int CProtoED42:: PWCHG(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: PWCHG(string trame)");

	/*
	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)				// TODO 
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}
	*/

	//Envoi d'un RES
	isRES = TRUE;

	
	if (equip->GetOperatingStatus() == ONLINE)
	{
		//Parametre invalide
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return WRONG_COMMAND;
	}

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 19 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame[0] != '#')
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	if (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0)
	{
		pLogger.LOG_TRACE("Dans equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	int endOfPassword = trame.find_first_of(",", 0);

	string newPassword = "";
	string password = "";
	char buffer[3] = {0};
	string codeN	= "";
	string codeN1	= "";
	string passwordN = "";
	long pwdRecup = 0;
	long pwdCalcul = 0;
	int cpt =0;

	string defaultPassword = trame.substr(0,endOfPassword);

	for(cpt = 1; cpt < defaultPassword.size() ; cpt++)
	{
		//Vérification que le defaultPassword contient uniquement un hexadécimal
		if(!((defaultPassword[cpt] >= '0' && defaultPassword[cpt] <= '9')
			|| (defaultPassword[cpt] >= 'A' && defaultPassword[cpt] <= 'F')
			|| (defaultPassword[cpt] >= 'a' && defaultPassword[cpt] <= 'f')))
		{
			equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

			return ERR_NON_CONFORME;
		}
	}

	//-------------------------------------
	//Verification du password du zeroized
	//-------------------------------------

	//Récupération du password clair
	password = equip->GetDefPassWord();

	//Remplacement du caractère # par 5 pour le décodage
	defaultPassword = defaultPassword.replace(0, 1, "5");

	for(cpt=0;cpt<password.length();cpt++)
	{
		codeN = defaultPassword.substr(cpt,1);
		codeN1 = defaultPassword.substr(cpt+1,1);
		passwordN = password.substr(cpt,1);

		pwdCalcul = strtol(passwordN.c_str(),NULL,16);
		pwdRecup = strtol(codeN.c_str(),NULL,16)^strtol(codeN1.c_str(),NULL,16);

		//Vérification de PWi
		//le password est code avec des chiffres compris entre 0..9 (page 135) 
		if(!(pwdCalcul == pwdRecup 
			&& (pwdRecup >= 0 && pwdRecup <=9)
			&& (pwdCalcul >= 0 && pwdCalcul <=9)))
		{
			//Si le password n'est pas correcte, il ne faut pas être en distant. //TODO
			//equip->setRemoteStatus(FALSE);
			//equip->setAuthentified(FALSE);

			equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
			//Pour l'erreur
			equip->setErrorTable(WRONG_DLD_PASSWORD_USER, TRUE);
			//Position du flag de l'erreur
			equip->SetError(TRUE);

			return WRONG_USER_PASSWORD;
		}
	}

	//--------------------------------
	//Verification du nouveau password
	//--------------------------------

	trame = trame.replace(0, endOfPassword, "");

	//Vérification du séparateur
	if(trame[0] != ',')
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	//Suppression de la virgule
	trame = trame.replace(0, 1, "");

	if(trame[0] != '#')
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	for(cpt = 1; cpt < trame.size() ; cpt++)
	{
		//Vérification que la trame contient uniquement un hexadécimal
		if(!((trame[cpt] >= '0' && trame[cpt] <= '9')
			|| (trame[cpt] >= 'A' && trame[cpt] <= 'F')
			|| (trame[cpt] >= 'a' && trame[cpt] <= 'f')))
		{
			equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

			return ERR_NON_CONFORME;
		}
	}

	//Remplacement du caractère # par 5 pour le décodage
	trame = trame.replace(0, 1, "5");

	for(cpt=0;cpt<trame.length()-1;cpt++)
	{
		codeN = trame.substr(cpt,1);
		codeN1 = trame.substr(cpt+1,1);

		pwdRecup = strtol(codeN.c_str(),NULL,16)^strtol(codeN1.c_str(),NULL,16);

		//le password est code avec des chiffres compris entre 0..9 (page 135) 
		if(pwdRecup >= 0 && pwdRecup <=9)
		{
			itoa(pwdRecup,buffer,10);
			newPassword.append(buffer);
		}
	}

	equip->setAuthentified(TRUE);
	equip->SetUserPassWord(newPassword);
	equip->SetZeroizeStatus(false);
	//************************************
	equip->ChangeNl(0);
	equip->SetResetEd42(false);
	equip->SetOperatingStatus(ZEROIZE_ALARM_TC);

	if(equip->GetStatusS20() == 1)
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: PWCHG(string trame) et if(equip->GetStatusS20() == 1)");

		equip->SetStatusS20(0);

	}

	if (equip->GetResetEd42Tc())
	{
		pLogger.LOG_TRACE("Fin CProtoED42:: PWCHG(string trame) et if (equip->GetResetEd42Tc())");

		equip->SetResetEd42(FALSE);
		equip->SetZeroizeStatus(FALSE);
		equip->SetResetEd42Tc(FALSE);
		equip->ChangeNl(0);
		equip->SetStatusS20(0);
		equip->SetOperatingStatus(ZEROIZE_ALARM_TC);
	}

	pLogger.LOG_TRACE("Fin CProtoED42:: PWCHG(string trame)");

	return SUCCESS;
}

/* ******************************************************************************************
METHODE :		PWCHK()
TRAITEMENT:		vérifie le password (Doc EL4.2 - Software interface control p 135 / page 183)
*******************************************************************************************	*/
int CProtoED42:: PWCHK(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: PWCHK(string trame)");

	int tmpS20 = equip->GetStatusS20();

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	//if(equip->GetStatusS20() >= 2)
	if(tmpS20 >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	string codeN	= "";
	string codeN1	= "";
	string password	= "";
	string passwordN= "";
	long pwdCalcul = 0;
	long pwdRecup = 0;

	//Envoi d'un RES
	isRES = TRUE;
	
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() != 9 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	//Recherche du caractère #
	if(trame[0] != '#')
	{
		//Mot de passe invalid si pas de présence du caractère #
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	for(int cpt = 1; cpt < trame.size() ; cpt++)
	{
		//Vérification que la trame contient uniquement un hexadécimal
		if(!((trame[cpt] >= '0' && trame[cpt] <= '9')
			|| (trame[cpt] >= 'A' && trame[cpt] <= 'F')
			|| (trame[cpt] >= 'a' && trame[cpt] <= 'f')))
		{
			equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
			return ERR_NON_CONFORME;
		}
	}
	
	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	if (equip->GetStatusBusy() == 1)
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	if(equip->GetZeroizeStatus())								// TODO
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		//Pour l'erreur
		equip->setErrorTable(WRONG_DLD_PASSWORD_USER, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);
		equip->setAuthentified(FALSE);

		return WRONG_USER_PASSWORD;
	}

	//Remplacement du caractère # par 5 pour le décodage
	trame = trame.replace(0, 1, "5");

	//Récupération du password clair
	password = equip->GetUserPassWord();

	for(int i=0;i<password.length();i++)
	{
		codeN = trame.substr(i,1);
		codeN1 = trame.substr(i+1,1);
		passwordN = password.substr(i,1);

		pwdCalcul = strtol(passwordN.c_str(),NULL,16);
		pwdRecup = strtol(codeN.c_str(),NULL,16)^strtol(codeN1.c_str(),NULL,16);

		//Vérification de PWi
		//le password est code avec des chiffres compris entre 0..9 (page 135) 
		if(!(pwdCalcul == pwdRecup 
			&& (pwdRecup >= 0 && pwdRecup <=9)
			&& (pwdCalcul >= 0 && pwdCalcul <=9)))
		{
			//Si le password n'est pas correcte, il ne faut pas être en distant.
			equip->setRemoteStatus(FALSE);
			equip->SetRemoteTC(LOCAL_TC);
			equip->setAuthentified(FALSE);

			//Pour l'erreur
			equip->setErrorTable(PASSWORD_CHECK, TRUE);
			//Position du flag de l'erreur
			equip->SetError(TRUE);

			return WRONG_USER_PASSWORD;
		}
	}

	//Vérification si on est en présence d'une erreur S#20 (sequence conflict)
	if(tmpS20 == 1)
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: PWCHK(string trame) et if(tmpS20 == 1)");

		equip->SetStatusS20(0);
	}

	equip->setAuthentified(TRUE);
	//typeCmd = 2;

	pLogger.LOG_TRACE("Fin CProtoED42:: PWCHK(string trame)");


	return SUCCESS;
}

/* **************************************************************************
METHODE :		REQDS()
TRAITEMENT:		Renvoie la DSInterface en cours (page 180)
***************************************************************************	*/
int CProtoED42:: REQDS(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: REQDS(string trame)");

	int tmpS20 = equip->GetStatusS20();

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	//if(equip->GetStatusS20() >= 2)
	if(tmpS20 >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(tmpS20 != 0)
	{
		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("?") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	strcat(bufCmd, "REQDS");

	stringstream out;
	out << equip->GetInterfaceKeyDownload();

	strcat(bufCmd, out.str().c_str());

	pLogger.LOG_TRACE("Fin CProtoED42:: REQDS(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		REQHD()
TRAITEMENT:		Renvoie la HDLC Adress (page 191)
***************************************************************************	*/
int CProtoED42:: REQHD(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: REQHD(string trame)");

	int tmpS20 = equip->GetStatusS20();

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	//if(equip->GetStatusS20() >= 2)
	if(tmpS20 >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(tmpS20 != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(tmpS20 != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("?") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	strcat(bufCmd, "REQHD");

	char HdlcAddress[4] = {0};

	itoa(equip->getHDLCAddress(), HdlcAddress, 10);
	strcat(bufCmd, HdlcAddress);

	pLogger.LOG_TRACE("Fin CProtoED42:: REQHD(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		REQHT()
TRAITEMENT:		Renvoie le temps avant autolock (page 192)
***************************************************************************	*/
int CProtoED42:: REQHT(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: REQHT(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	int ret;

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return ERR_NON_CONFORME;
	}

	if (testTrameFirst(trame, 0, 1, '?', &ret))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	strcat(bufCmd, "REQHT");

	stringstream out;
	out << equip->GetPasswordHoldTime();

	strcat(bufCmd, out.str().c_str());

	pLogger.LOG_TRACE("Fin CProtoED42:: REQHT(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		REQID()
TRAITEMENT:		Renvoie l'ID de la station (page 191)
***************************************************************************	*/
int CProtoED42:: REQID(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: REQID(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("?") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	strcat(bufCmd, "REQID");

	stringstream out;
	out << equip->GetDeviceID();

	strcat(bufCmd, out.str().c_str());

	pLogger.LOG_TRACE("Fin CProtoED42:: REQID(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		REQPS()
TRAITEMENT:		Renvoie les parametres du preset en cours (page186)
***************************************************************************	*/
int CProtoED42:: REQPS(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: REQPS(string trame)");

	int tmpS20 = equip->GetStatusS20();

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	//if(equip->GetStatusS20() >= 2)
	if(tmpS20 >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(tmpS20 != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(tmpS20 != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);
		return ERR_NON_CONFORME;
	}
	
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 3 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame[trame.size()-1] != '?')
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}
	

	pLogger.LOG_TRACE("Dans CProtoED42:: REQPS(string trame) et traitement");

	cmd.clear();

	//Récupération du preset demandé
	string preset = "";

	cmd.str(trame);
	// param : 1 Preset index
	getline(cmd, preset, '?');

	int tmp_val = atoi(preset.c_str());
	
	//Vérification de la valeur du preset index
	if(tmp_val < 0 || tmp_val > 31
		|| (tmp_val == 0 && preset.compare("0") != 0))
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	strcat(bufCmd, "REQPS");

	strcat(bufCmd, preset.c_str());

	TGeneralParameters presetEnCours	= equip->GetGeneralParameters(preset);
	TDigitalDCE digitalDceEnCours		= equip->GetDigitalDCEParameters(preset);
	TDigitalDTE digitalDteEnCours		= equip->GetDigitalDTEParameters(preset);
	TAnalogDCE analogDceEnCours			= equip->GetAnalogDCEParameters(preset);
	TAnalogDTE analogDteEnCours			= equip->GetAnalogDTEParameters(preset);

	//Construction de la suite de la trame REQPS
	buildTrameREQPS(presetEnCours,digitalDceEnCours,digitalDteEnCours,analogDceEnCours,analogDteEnCours);

	//Modification
	equip->SetPresetList(preset,'S');				// Param 20 : Flag : Preset list

	pLogger.LOG_TRACE("Fin CProtoED42:: REQPS(string trame)");
	
	return SUCCESS;
}

/* **************************************************************************
METHODE :		REQUL()
TRAITEMENT:		Renvoie le nombre maximum de mise à jour (page 190)
***************************************************************************	*/
int CProtoED42:: REQUL(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: REQUL(string trame)");

	int tmpS20 = equip->GetStatusS20();

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	//if(equip->GetStatusS20() >= 2)
	if(tmpS20 >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(tmpS20 != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(tmpS20 != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("?") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	strcat(bufCmd,"REQUL");

	stringstream out;
	out << equip->GetUpdateLimit();

	strcat(bufCmd, out.str().c_str());

	pLogger.LOG_TRACE("Fin CProtoED42:: REQUL(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		RES()
TRAITEMENT:		Résultat d'une opération (page 166)
***************************************************************************	*/
string CProtoED42:: RES()
{
	pLogger.LOG_TRACE("Dans CProtoED42:: RES()");

/*
	if(!(equip->getAuthentified()))
	{
		sendAuthorizationError();
		return "";;
	}
*/

	char tmpcmd[5];
	string reponse;

	reponse = getUneError("RES");
	reponse.append(",");

	if (reponse[3] == '0')
		itoa(cptSuccessfullCmd, tmpcmd, 10);
	else
		itoa(equip->GetnrCommandInError(), tmpcmd, 10);

	reponse.append(tmpcmd);

	pLogger.LOG_TRACE("Fin CProtoED42:: RES()");

	return reponse;
}

/* **************************************************************************
METHODE :		RES()
TRAITEMENT:		Résultat d'une opération (page 166)
***************************************************************************	*/
int CProtoED42:: RES(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: RES(string trame)");

		//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() == 3)
	{
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		//Force le RES
		isRES = TRUE;
		return WRONG_COMMAND;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0)
	{
		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 || trame.size() == 0)
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("?") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	strcat(bufCmd,getUneError("RES").c_str());

	//Le dernier paramètre doit être 0 (page 168)
	strcat(bufCmd,",0");

	pLogger.LOG_TRACE("Fin CProtoED42:: RES(string trame)");

	return SUCCESS;
}
/* **************************************************************************
METHODE :		RCS()
TRAITEMENT:		Retourne un Checksum (page 159)
***************************************************************************	*/
string CProtoED42:: RCS(string reponse, bool outCmd)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: RCS(string reponse, bool outCmd)");

	stringstream out;

	//Calcul du checksum (page 159)
	int checksum = 0x00;

	for(int i=0; i<reponse.length();i++)
	{
		checksum = checksum+reponse[i];
	}

	//Convertion du résultat en hexadécimal
	stringstream out2;
	out2 << hex <<checksum;
	string res = out2.str();

	//Récupération des deux derniers chiffres
	res = res.substr(res.length()-2,2);

	if (outCmd)
		return res;

	out << "RCS#"<<res;

	pLogger.LOG_TRACE("Fin CProtoED42:: RCS(string reponse, bool outCmd)");

	return out.str();
}

/* **************************************************************************
METHODE :		RST()
TRAITEMENT:		Reset de l'appareil (page 172)
***************************************************************************	*/
int CProtoED42:: RST(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: RST(string trame)");

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("0") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	equip->SetResetEd42(true);

	if (equip->GetStatusNl())
		equip->SetResetEd42Tc(true);

	pLogger.LOG_TRACE("Fin CProtoED42:: RST(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		S()
TRAITEMENT:		Renvoie le statut du message (page 156)
***************************************************************************	*/
int CProtoED42:: S(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: S(string trame)");

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return INVALID_PARAMETER;
	}

	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return MAX_MSG_LENGTH;
	}

	if(trame.compare("?") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return INVALID_PARAMETER;
	}

	pLogger.LOG_TRACE("Fin CProtoED42:: S(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		S()
TRAITEMENT:		Renvoie le statut du message (page 156)
***************************************************************************	*/
string CProtoED42::S()
{
	pLogger.LOG_TRACE("Dans CProtoED42::S()");

	double resultat = 0;
	string res;

	//if (equip->getStatusErrorRCS())
	//	return res = IntToHexaString(2);

	TStatusError error;
	TVectorStatusError errorList = equip->getStatusErrors();


	for (int i=0; i<errorList.size(); i++)
	{
		pLogger.LOG_TRACE("Dans CProtoED42::S() et for (int i=0; i<errorList.size(); i++)");

		error = equip->DecodeStatusError(errorList[i]);

		if (error.used) 
		{
			pLogger.LOG_TRACE("Dans CProtoED42::S() et for (int i=0; i<errorList.size(); i++) et if (error.used)");

			resultat = resultat + pow (2.0, i);
			
			// Attention   A VERIFIER
			//Vérification du nombre de fois à émettre l'erreur
			if(error.nbRepeat == 0)
			{
				// Lorsqu'on construit le S, il faut enlever l'erreur status du vector
				//equip->setStatusErrorTable(i,FALSE);
				error.used = FALSE;
			}else
				error.nbRepeat--;
							
			errorList[i] = equip->EncodeStatusError(error);
		}
	}

	equip->setStatusErrors(errorList);

	res = IntToHexaString((int)resultat);

	pLogger.LOG_TRACE("Fin CProtoED42::S()");

	return res;
}

/* **************************************************************************
METHODE :		SETAD()
TRAITEMENT:		Permet de définir l'adresse de l'appareil (page 192)
***************************************************************************	*/
int CProtoED42:: SETAD(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: SETAD(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if (equip->GetOperatingStatus() == ONLINE)
	{
		//Parametre invalide
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return WRONG_COMMAND;
	}
	
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 2 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	int param;

	const char * c = trame.c_str();

	param = atoi(c);

	if(param < MIN_REMOTE_ADDRESS || param > MAX_REMOTE_ADDRESS)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	equip->setRemoteAdress(param);

	pLogger.LOG_TRACE("Fin CProtoED42:: SETAD(string trame)");

	return SUCCESS;	
}

/* **************************************************************************
METHODE :		SETDS()
TRAITEMENT:		Permet de définir la DS interface en cours (page 180)
***************************************************************************	*/
int CProtoED42:: SETDS(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: SETDS(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0)
	{
		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;

	if(!(equip->getRemoteStatus()))
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);

		return ERR_NO_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0)
	{
		equip->setStatusErrorTable(CONFLICT, TRUE);

		return ERR_NON_CONFORME;
	}

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}
	
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	int param;

	const char * c = trame.c_str();

	param = atoi(c);

	if(param < 1 || param > 2)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	equip->SetInterfaceKeyDownload(param);

	pLogger.LOG_TRACE("Fin CProtoED42:: SETDS(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		SETHD()
TRAITEMENT:		Permet de définir la HDLC Adress (page 191)
***************************************************************************	*/
int CProtoED42:: SETHD(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: SETHD(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if (equip->GetOperatingStatus() == ONLINE)
	{
		//Parametre invalide
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return WRONG_COMMAND;
	}
	
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 3 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	int param;

	const char * c = trame.c_str();

	param = atoi(c);

	if(param < MIN_HDLC_ADDRESS || param > MAX_HDLC_ADDRESS)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	equip->setHDLCAddress(param);

	pLogger.LOG_TRACE("Fin CProtoED42:: SETHD(string trame)");

 	return SUCCESS;
}

/* **************************************************************************
METHODE :		SETHT()
TRAITEMENT:		Permet de définir Le temps avant verrouillage (page 192)
***************************************************************************	*/
int CProtoED42:: SETHT(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: SETHT(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;
	int ret = NOT_ERROR;


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return ERR_NON_CONFORME;
	}
	
	if (testTrameFirst(trame, 0, 2, '0', &ret, false, 4, true))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	int param;

	const char * c = trame.c_str();

	param = atoi(c);

	if(param < 0 || param > 60
		|| (param == 0 && trame.compare("0") != 0))
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	equip->SetPasswordHoldTime(param);

	pLogger.LOG_TRACE("Fin CProtoED42:: SETHT(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		SETID()
TRAITEMENT:		Permet de définir L'ID de la station (page 191)
***************************************************************************	*/
int CProtoED42:: SETID(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: SETID(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

		//Envoi d'un RES
	isRES = TRUE;


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if (equip->GetOperatingStatus() == ONLINE)
	{
		//Parametre invalide
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return WRONG_COMMAND;
	}
	
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 6 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	int param;

	const char * c = trame.c_str();

	param = atoi(c);

	if(param < MIN_STATION_ID || param > MAX_STATION_ID
		|| (param == 0 && trame.compare("0") != 0))
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	equip->SetDeviceID(param);

	pLogger.LOG_TRACE("Fin CProtoED42:: SETID(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		SETPS()
TRAITEMENT:		Permet de définir le preset actif (page 186)
***************************************************************************	*/
int CProtoED42:: SETPS(string trame)
{
	//OutputDebugString("Dans : CProtoED42:: SETPS(string trame)!\n");
	pLogger.LOG_TRACE("Dans CProtoED42:: SETPS(string trame)");

	int tmpS20 = equip->GetStatusS20();

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	//if(equip->GetStatusS20() == 3 || equip->GetStatusS20() == 2)
	if(tmpS20 >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(tmpS20 != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(tmpS20 != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	int tmp_val;
	int cpt = 0;
	int ret = NOT_ERROR;

	//Envoi d'un RES
	isRES = TRUE;


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		return ERR_NON_CONFORME;
	}

	OutputDebugString("Dans : CProtoED42:: SETPS(string trame) et début traitement!\n");
	
	if (testTrameFirst(trame, 0, 129, '?', &ret, false, 6, true))
	{
		equip->setStatusErrorTable(ret, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	equip->SetStatusBusy(1);


	//********************
	// Début du traitement
	//********************
	OutputDebugString("Dans : CProtoED42:: SETPS(string trame) et // Début du traitement!\n");
	cmd.clear();

	string commande = "";
	string tmp_Preset = "";
	int tmp_NumPreset;
	//int prCourant;

	cmd.str(trame);

	// param : 1 Preset index
	getline(cmd, commande, ',');
	tmp_Preset = commande;
	tmp_NumPreset = atoi(commande.c_str());		// ID du preset DE LA COMMANDE
	//prCourant = tmp_NumPreset%8;				// si ID = 16 prCourant = 0 !!??

	//Vérification de la valeur du preset index
	if(tmp_NumPreset < 0 || tmp_NumPreset > 31
		|| (tmp_NumPreset == 0 && commande.compare("0") != 0))
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}

	//*
	TGeneralParameters presetEnCours	= equip->GetGeneralParameters(tmp_Preset);
	TDigitalDCE digitalDceEnCours		= equip->GetDigitalDCEParameters(tmp_Preset);
	TDigitalDTE digitalDteEnCours		= equip->GetDigitalDTEParameters(tmp_Preset);
	TAnalogDCE analogDceEnCours			= equip->GetAnalogDCEParameters(tmp_Preset);
	TAnalogDTE analogDteEnCours			= equip->GetAnalogDTEParameters(tmp_Preset);
	//**
	presetEnCours.preset = tmp_NumPreset;

	// param : 2 Preset type
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());	// Type de preset
	
	//Vérification de la valeur du preset type
	if(tmp_val < 0 || tmp_val > 3
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	presetEnCours.operation_mode = tmp_val;
	//equip->SetOperatingMode(tmp_val);		//TODO

	// param : 3 transmissionMode
	getline(cmd, commande, ',');
	tmp_val  = atoi(commande.c_str());
	
	//Vérification de la valeur du transmission mode
	if(tmp_val < 0 || tmp_val > 8
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	presetEnCours.transmission_mode = tmp_val;
	//equip->SetTransmissionMode(tmp_val);		//TODO

	//(cmd.str()).substr(0,2);
	// param : 4 transmissionProc
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());
	
	//Vérification de la valeur du transmission Procedure
	if(tmp_val < 0 || tmp_val > 7
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);

		return ERR_NON_CONFORME;
	}

	presetEnCours.transmission_procedure = tmp_val;
	//equip->SetTransmissionProcedure(tmp_val);		//TODO

	//(cmd.str()).substr(0,2);
	// param : 5 trafficMode
	getline(cmd, commande, ',');
	tmp_val  = atoi(commande.c_str());
	
	//Vérification de la valeur du traffic mode
	if(tmp_val < 0 || tmp_val > 18
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	presetEnCours.trafic_mode = tmp_val;
	//equip->SetTraficMode(tmp_val);			//TODO

	//(cmd.str()).substr(0,3);
	// param : 6 reserved
	getline(cmd, commande, ',');

	//Vérification de la valeur reserved
	/*
	if(commande.compare("255") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}
	*/
	//(cmd.str()).substr(0,2);
	// param : 7 syncMode
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());
	
	//Vérification de la valeur du sync mode
	if(tmp_val < 0 || tmp_val > 2
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	presetEnCours.synchronisation_mode = tmp_val;

	//(cmd.str()).substr(0,2);
	getline(cmd, commande, ',');
	//(cmd.str()).substr(0,2);
	getline(cmd, commande, ',');

	//(cmd.str()).substr(0,2);
	// param : 10 parity
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());
	
	//Vérification de la valeur du parity
	if(tmp_val < 0 || tmp_val > 2
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	presetEnCours.parity = tmp_val;

	//(cmd.str()).substr(0,2);
	// param : 11 numberOfStopBits
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());
	
	//Vérification de la valeur du number of stop bits
	if(tmp_val < 0 || tmp_val > 1
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	presetEnCours.nb_of_stop_bite = tmp_val;

	//(cmd.str()).substr(0,2);
	// param : 12 outputSelect
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());
	
	//Vérification de la valeur du output select
	if(tmp_val < 0 || tmp_val > 1
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	presetEnCours.output_selection = tmp_val;

	//(cmd.str()).substr(0,2);
	// param : 13 antispoof
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());
	
	//Vérification de la valeur du antispoof
	if(tmp_val < 0 || tmp_val > 1
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	presetEnCours.antispoof = (tmp_val == 1);

	//(cmd.str()).substr(0,2);
	// param : 14 dataRate
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());
	
	//Vérification de la valeur du data rate
	if(tmp_val < 0 || tmp_val > 16
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	presetEnCours.data_rate = tmp_val;

	//(cmd.str()).substr(0,3);
	// param : 15 FEC
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());
	
	//Vérification de la valeur du FEC
	if(tmp_val < 0 || tmp_val > 1
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	presetEnCours.fec = (tmp_val == 1);

	//(cmd.str()).substr(0,2);
	// param : 16 LeadTime
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());
	
	//Vérification de la valeur du leadTime
	if(tmp_val < 1 || tmp_val > 20)
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	presetEnCours.lead_time = tmp_val;

	//(cmd.str()).substr(0,3);
	// param : 17 Interface selection
	getline(cmd, commande, ',');

	if(commande[0] != '#')
	{
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return ERR_NON_CONFORME;
	}
	else
	{
		commande=commande.replace(0, 1, "");

		//Vérification de la valeur de l'interface selection
		for(cpt = 0 ; cpt < commande.size() ; cpt++)
		{
			//Vérification que la trame contient uniquement un hexadécimal
			if(!((commande[cpt] >= '0' && commande[cpt] <= '9')
				|| (commande[cpt] >= 'A' && commande[cpt] <= 'F')
				|| (commande[cpt] >= 'a' && commande[cpt] <= 'f')))
			{
				equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
				return ERR_NON_CONFORME;
			}
		}

		int tmp_dteAnalogInterf		= (strtol(commande.c_str(),NULL,16) & 0x01);
		int tmp_dteDigitalInterface = (strtol(commande.c_str(),NULL,16) & 0x02)/2;
		int tmp_dceAnalogInterf		= (strtol(commande.c_str(),NULL,16) & 0x04)/4;
		int tmp_dceDigitalInterface = (strtol(commande.c_str(),NULL,16) & 0x08)/8;

		presetEnCours.dteAnalogInterf					= (tmp_dteAnalogInterf == 1);
		analogDteEnCours.activateAnalogDteInterface		= (tmp_dteAnalogInterf == 1);
		presetEnCours.dteDigitalInterface				= (tmp_dteDigitalInterface == 1);
		digitalDteEnCours.activateDigitalDteInterface	= (tmp_dteDigitalInterface == 1);
		presetEnCours.dceAnalogInterf					= (tmp_dceAnalogInterf == 1);
		analogDceEnCours.activateAnalogDceInterface		= (tmp_dceAnalogInterf == 1);
		presetEnCours.dceDigitalInterface				= (tmp_dceDigitalInterface == 1);
		digitalDceEnCours.activateDigitalDceInterface	= (tmp_dceDigitalInterface == 1);
	}

	//(cmd.str()).substr(0,5);
	// param : 18 DCE outputlevel
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());
    
	//Vérification de la valeur de DCE output level
	if(tmp_val < 0 || tmp_val > 2
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	digitalDceEnCours.outputLevel = tmp_val;

	//(cmd.str()).substr(0,2);
	// param : 19 DCE Digital polarity
	getline(cmd, commande, ',');

	if(commande[0] != '#')
	{
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return ERR_NON_CONFORME;
	}
	else
	{
		commande=commande.replace(0, 1, "");

		//Vérification de la valeur de DCE Digital polarity
		for(cpt = 0 ; cpt < commande.size() ; cpt++)
		{
			//Vérification que la trame contient uniquement un hexadécimal
			if(!((commande[cpt] >= '0' && commande[cpt] <= '9')
				|| (commande[cpt] >= 'A' && commande[cpt] <= 'F')
				|| (commande[cpt] >= 'a' && commande[cpt] <= 'f')))
			{
				equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
				return ERR_NON_CONFORME;
			}
		}

		int tmp_dce_dig_interf_llr = (strtol(commande.c_str(),NULL,16) & 0x01);
		int tmp_dce_dig_interf_rng = (strtol(commande.c_str(),NULL,16) & 0x02)/2;
		int tmp_dce_dig_interf_rck = (strtol(commande.c_str(),NULL,16) & 0x04)/4;
		int tmp_dce_dig_interf_xck = (strtol(commande.c_str(),NULL,16) & 0x08)/8;
		int tmp_dce_dig_interf_dcd = (strtol(commande.c_str(),NULL,16) & 0x10)/16;
		int tmp_dce_dig_interf_dsr = (strtol(commande.c_str(),NULL,16) & 0x20)/32;
		int tmp_dce_dig_interf_cts = (strtol(commande.c_str(),NULL,16) & 0x40)/64;
		int tmp_dce_dig_interf_rxd = (strtol(commande.c_str(),NULL,16) & 0x80)/128;
		int tmp_dce_dig_interf_ltl = (strtol(commande.c_str(),NULL,16) & 0x100)/256;
		int tmp_dce_dig_interf_rtl = (strtol(commande.c_str(),NULL,16) & 0x200)/512;
		int tmp_dce_dig_interf_tck = (strtol(commande.c_str(),NULL,16) & 0x400)/1024;
		int tmp_dce_dig_interf_dtr = (strtol(commande.c_str(),NULL,16) & 0x800)/2048;
		int tmp_dce_dig_interf_rts = (strtol(commande.c_str(),NULL,16) & 0x1000)/4096;
		int tmp_dce_dig_interf_txd = (strtol(commande.c_str(),NULL,16) & 0x2000)/8192;

		digitalDceEnCours.polarityInputSignalLLR = tmp_dce_dig_interf_llr == 1;
		digitalDceEnCours.polarityInputSignalRNG = tmp_dce_dig_interf_rng == 1;
		digitalDceEnCours.polarityInputSignalRCK = tmp_dce_dig_interf_rck == 1;
		digitalDceEnCours.polarityInputSignalXCK = tmp_dce_dig_interf_xck == 1;
		digitalDceEnCours.polarityInputSignalDCD = tmp_dce_dig_interf_dcd == 1;
		digitalDceEnCours.polarityInputSignalDSR = tmp_dce_dig_interf_dsr == 1;
		digitalDceEnCours.polarityInputSignalCTS = tmp_dce_dig_interf_cts == 1;
		digitalDceEnCours.polarityInputSignalRXD = tmp_dce_dig_interf_rxd == 1;
		digitalDceEnCours.polarityOutputSignalLTL = tmp_dce_dig_interf_ltl == 1;
		digitalDceEnCours.polarityOutputSignalRTL = tmp_dce_dig_interf_rtl == 1;
		digitalDceEnCours.polarityOutputSignalTCK = tmp_dce_dig_interf_tck == 1;
		digitalDceEnCours.polarityOutputSignalDTR = tmp_dce_dig_interf_dtr == 1;
		digitalDceEnCours.polarityOutputSignalRTS = tmp_dce_dig_interf_rts == 1;
		digitalDceEnCours.polarityOutputSignalTXD = tmp_dce_dig_interf_txd == 1;
	}

	// param : 20 DTE Digital
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str());
	
	//Vérification de la valeur de DTE Digital
	if(tmp_val < 0 || tmp_val > 2
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	digitalDteEnCours.outputLevel = tmp_val;

	// param : 21 DTE Digital polarity
	getline(cmd, commande, ',');

	if(commande[0] != '#')
	{
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return ERR_NON_CONFORME;
	}
	else
	{
		commande=commande.replace(0, 1, "");

		//Vérification de la valeur de DTE Digital polarity
		for(cpt = 0 ; cpt < commande.size() ; cpt++)
		{
			//Vérification que la trame contient uniquement un hexadécimal
			if(!((commande[cpt] >= '0' && commande[cpt] <= '9')
				|| (commande[cpt] >= 'A' && commande[cpt] <= 'F')
				|| (commande[cpt] >= 'a' && commande[cpt] <= 'f')))
			{
				equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
				return ERR_NON_CONFORME;
			}
		}

		int tmp_dte_dig_interf_ltl = (strtol(commande.c_str(),NULL,16) & 0x01);
		int tmp_dte_dig_interf_rtl = (strtol(commande.c_str(),NULL,16) & 0x02)/2;
		int tmp_dte_dig_interf_dtr = (strtol(commande.c_str(),NULL,16) & 0x04)/4;
		int tmp_dte_dig_interf_rts = (strtol(commande.c_str(),NULL,16) & 0x08)/8;
		int tmp_dte_dig_interf_txd = (strtol(commande.c_str(),NULL,16) & 0x10)/16;
		int tmp_dte_dig_interf_dcd = (strtol(commande.c_str(),NULL,16) & 0x20)/32;
		int tmp_dte_dig_interf_llr = (strtol(commande.c_str(),NULL,16) & 0x40)/64;
		int tmp_dte_dig_interf_rng = (strtol(commande.c_str(),NULL,16) & 0x80)/128;
		int tmp_dte_dig_interf_xck = (strtol(commande.c_str(),NULL,16) & 0x100)/256;
		int tmp_dte_dig_interf_rck = (strtol(commande.c_str(),NULL,16) & 0x200)/512;
		int tmp_dte_dig_interf_dsr = (strtol(commande.c_str(),NULL,16) & 0x400)/1024;
		int tmp_dte_dig_interf_cts = (strtol(commande.c_str(),NULL,16) & 0x800)/2048;
		int tmp_dte_dig_interf_rxd = (strtol(commande.c_str(),NULL,16) & 0x1000)/4096;

		digitalDteEnCours.polarityOutputSignalLLR = tmp_dte_dig_interf_llr == 1;
		digitalDteEnCours.polarityOutputSignalRNG = tmp_dte_dig_interf_rng == 1;
		digitalDteEnCours.polarityOutputSignalRCK = tmp_dte_dig_interf_rck == 1;
		digitalDteEnCours.polarityOutputSignalXCK = tmp_dte_dig_interf_xck == 1;
		digitalDteEnCours.polarityOutputSignalDCD = tmp_dte_dig_interf_dcd == 1;
		digitalDteEnCours.polarityOutputSignalDSR = tmp_dte_dig_interf_dsr == 1;
		digitalDteEnCours.polarityOutputSignalCTS = tmp_dte_dig_interf_cts == 1;
		digitalDteEnCours.polarityOutputSignalRXD = tmp_dte_dig_interf_rxd == 1;
		digitalDteEnCours.polarityInputSignalLTL = tmp_dte_dig_interf_ltl == 1;
		digitalDteEnCours.polarityInputSignalRTL = tmp_dte_dig_interf_rtl == 1;
		digitalDteEnCours.polarityInputSignalDTR = tmp_dte_dig_interf_dtr == 1;
		digitalDteEnCours.polarityInputSignalRTS = tmp_dte_dig_interf_rts == 1;
		digitalDteEnCours.polarityInputSignalTXD = tmp_dte_dig_interf_txd == 1;
	}

	// param : 22 DCE Analog polarity
	getline(cmd, commande, ',');

	if(commande[0] != '#')
	{
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return ERR_NON_CONFORME;
	}
	else
	{
		commande=commande.replace(0, 1, "");

		//Vérification de la valeur de DCE Analog polarity
		for(cpt = 0 ; cpt < commande.size() ; cpt++)
		{
			//Vérification que la trame contient uniquement un hexadécimal
			if(!((commande[cpt] >= '0' && commande[cpt] <= '9')
				|| (commande[cpt] >= 'A' && commande[cpt] <= 'F')
				|| (commande[cpt] >= 'a' && commande[cpt] <= 'f')))
			{
				equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
				return ERR_NON_CONFORME;
			}
		}

		int tmp_dceAnaIntrfSqgPolar  = (strtol(commande.c_str(),NULL,16) & 0x01);
		int tmp_dceAnaIntrfSqmPolar  = (strtol(commande.c_str(),NULL,16) & 0x02)/2;
		int tmp_dceAnaIntrfPttPolar  = (strtol(commande.c_str(),NULL,16) & 0x04)/4;
		int tmp_dceAnaIntrfNbwbPolar = (strtol(commande.c_str(),NULL,16) & 0x08)/8;
		int tmp_dceAnaIntrfBbdpPolar = (strtol(commande.c_str(),NULL,16) & 0x10)/16;
		int tmp_dceAnaIntrfDpttPolar = (strtol(commande.c_str(),NULL,16) & 0x20)/32;

		analogDceEnCours.polaritySQG = tmp_dceAnaIntrfSqgPolar == 1;
		analogDceEnCours.polaritySQM = tmp_dceAnaIntrfSqmPolar == 1;
		analogDceEnCours.polarityPTT = tmp_dceAnaIntrfPttPolar == 1;
		analogDceEnCours.polarityNBWB = tmp_dceAnaIntrfNbwbPolar == 1;
		analogDceEnCours.polarityBBDP = tmp_dceAnaIntrfBbdpPolar == 1;
		analogDceEnCours.polarityDPTT = tmp_dceAnaIntrfDpttPolar == 1;

	}

	// param : 23 DCE Analog configuration
	getline(cmd, commande, ',');

	if(commande[0] != '#')
	{
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return ERR_NON_CONFORME;
	}
	else
	{
		commande=commande.replace(0, 1, "");

		//Vérification de la valeur de DCE Analog configuration
		for(cpt = 0 ; cpt < commande.size() ; cpt++)
		{
			//Vérification que la trame contient uniquement un hexadécimal
			if(!((commande[cpt] >= '0' && commande[cpt] <= '9')
				|| (commande[cpt] >= 'A' && commande[cpt] <= 'F')
				|| (commande[cpt] >= 'a' && commande[cpt] <= 'f')))
			{
				equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
				return ERR_NON_CONFORME;
			}
		}

		int tmp_dceAnaIntrfDpttConfig = ((strtol(commande.c_str(),NULL,16) & 0x000000ff));
		int tmp_dceAnaIntrfSqmConfig  = (((strtol(commande.c_str(),NULL,16) & 0x0000ff00)/256));
		int tmp_dceAnaIntrfSqgConfig  = (((strtol(commande.c_str(),NULL,16) & 0x00ff0000)/65536));
		int tmp_dceAnaIntrfSqlConfig  = (((strtol(commande.c_str(),NULL,16) & 0xff000000)/16777216));

		analogDceEnCours.confTypeDPTT		= tmp_dceAnaIntrfDpttConfig;
		analogDceEnCours.confTypeSQM		= tmp_dceAnaIntrfSqmConfig;
		analogDceEnCours.confTypeSQG		= tmp_dceAnaIntrfSqgConfig;
		analogDceEnCours.confTypeSQUELCH	= tmp_dceAnaIntrfSqlConfig;
	}

	// param : 24 RXNB Level
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str()) - 50;
    
	//Vérification de la valeur de RXNB Level
	if(tmp_val < -40 || tmp_val > 20
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDceEnCours.levelRXNB = tmp_val;

	// param : 25 TXNB Level
	getline(cmd, commande, ',');
	tmp_val  = atoi(commande.c_str()) -50;
    
	//Vérification de la valeur de TXNB Level
	if(tmp_val < -47 || tmp_val > 13
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDceEnCours.levelTXNB = tmp_val;

	// param : 26 RXWB Level
	getline(cmd, commande, ',');
	tmp_val  = atoi(commande.c_str()) - 50;
    
	//Vérification de la valeur de RXWB Level
	if(tmp_val < -40 || tmp_val > 20
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDceEnCours.levelRXWB = tmp_val;

	// param : 27 TXWB Level
	getline(cmd, commande, ',');
	tmp_val  = atoi(commande.c_str()) - 50;
    
	//Vérification de la valeur de TXWB Level
	if(tmp_val < -47 || tmp_val > 13
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDceEnCours.levelTXWB = tmp_val;

	// param : 28 DTE analog polarity
	getline(cmd, commande, ',');

	if(commande[0] != '#')
	{
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return ERR_NON_CONFORME;
	}
	else
	{
		commande=commande.replace(0, 1, "");

		//Vérification de la valeur de DTE analog polarity
		for(cpt = 0 ; cpt < commande.size() ; cpt++)
		{
			//Vérification que la trame contient uniquement un hexadécimal
			if(!((commande[cpt] >= '0' && commande[cpt] <= '9')
				|| (commande[cpt] >= 'A' && commande[cpt] <= 'F')
				|| (commande[cpt] >= 'a' && commande[cpt] <= 'f')))
			{
				equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
				return ERR_NON_CONFORME;
			}
		}

		int tmp_microphoneSupply	= (strtol(commande.c_str(),NULL,16) & 0x04)/4;
		int tmp_Monitoring			= (strtol(commande.c_str(),NULL,16) & 0x08)/8;

		analogDteEnCours.activateMonitoring = (tmp_Monitoring == 1);
		analogDteEnCours.microSupply        = (tmp_microphoneSupply == 1);
	}

	// param : 29 DTE analog configuration
	getline(cmd, commande, ',');

	if(commande[0] != '#')
	{
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return ERR_NON_CONFORME;
	}
	else
	{
		commande=commande.replace(0, 1, "");

		//Vérification de la valeur de DTE analog configuration
		for(cpt = 0 ; cpt < commande.size() ; cpt++)
		{
			//Vérification que la trame contient uniquement un hexadécimal
			if(!((commande[cpt] >= '0' && commande[cpt] <= '9')
				|| (commande[cpt] >= 'A' && commande[cpt] <= 'F')
				|| (commande[cpt] >= 'a' && commande[cpt] <= 'f')))
			{
				equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
				return ERR_NON_CONFORME;
			}
		}

		int tmp_microphoneType		  = ((strtol(commande.c_str(),NULL,16) & 0x0000ff));
		int tmp_dteAnaIntPttlocConfig = (((strtol(commande.c_str(),NULL,16) & 0x00ff00)/256));
		int tmp_dteAnaIntPttctrConfig = (((strtol(commande.c_str(),NULL,16) & 0xff0000)/65536));

		analogDteEnCours.microType		= tmp_microphoneType ;
		analogDteEnCours.confTypePTT42	= tmp_dteAnaIntPttlocConfig;
		analogDteEnCours.confTypePTTCTR	= tmp_dteAnaIntPttctrConfig;

	}

	// param : 30 Internal RI
	getline(cmd, commande, ',');
	tmp_val	= atoi(commande.c_str());
    
	//Vérification de la valeur de Internal RI
	if(tmp_val < 0 || tmp_val > 1
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.microRi = tmp_val;

	// param : 31 Micro supply voltage
	getline(cmd, commande, ',');
	tmp_val	= atoi(commande.c_str());
    
	//Vérification de la valeur de Micro supply voltage
	if(tmp_val < 0 || tmp_val > 15
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.voltageSupply = tmp_val;

	// param : 32 Micro level
	getline(cmd, commande, ',');
	tmp_val	= atoi(commande.c_str()) - 50;
    
	//Vérification de la valeur de Micro level
	if(tmp_val < -47 || tmp_val > 13
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.microLevel = tmp_val;

	// param : 33 Phone level
	getline(cmd, commande, ',');
	tmp_val	= atoi(commande.c_str()) - 50;
    
	//Vérification de la valeur de Phone level
	if(tmp_val < -47 || tmp_val > 13
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.phoneLevel = tmp_val;

	// param : 34 TXCTR level
	getline(cmd, commande, ',');
	tmp_val	= atoi(commande.c_str()) - 50;
    
	//Vérification de la valeur de TXCTR level
	if(tmp_val < -47 || tmp_val > 13
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.txctrLevel = tmp_val;

	// param : 35 RXCTR level
	getline(cmd, commande, ',');
	tmp_val	= atoi(commande.c_str()) - 50;
    
	//Vérification de la valeur de RXCTR level
	if(tmp_val < -47 || tmp_val > 13
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.rxctrLevel = tmp_val;

	// param : 36 TX Plain level
	getline(cmd, commande, ',');
	tmp_val	= atoi(commande.c_str()) - 50;
    
	//Vérification de la valeur de TX Plain level
	if(tmp_val < -40 || tmp_val > 20
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.txbypassLevel = tmp_val;

	// param : 37 Bypass level
	getline(cmd, commande, ',');
	tmp_val	= atoi(commande.c_str()) - 50;
    
	//Vérification de la valeur de Bypass level
	if(tmp_val < -40 || tmp_val > 20
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.rxbypassLevel = tmp_val;

	// param : 38 Monitor level
	getline(cmd, commande, ',');
	tmp_val = atoi(commande.c_str()) - 50;
    
	//Vérification de la valeur de Monitor level
	if(tmp_val < -40 || tmp_val > 20
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.monitorLevel = tmp_val;

	// param : 39 Sidetone adaption
	getline(cmd, commande, ',');
	tmp_val	= atoi(commande.c_str()) - 50;
    
	//Vérification de la valeur de Sidetone adaptation
	if(tmp_val < -40 || tmp_val > 20
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.sidetoneLevel = tmp_val;

	// param : 40 Alarme adaption
	getline(cmd, commande, ',');
	tmp_val	= atoi(commande.c_str()) - 50;    

	//Vérification de la valeur de Alarme adaption
	if(tmp_val < -40 || tmp_val > 20
		|| (tmp_val == 0 && commande.compare("50") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.alarmeLevel = tmp_val;

	// param : 41 Audio selection
	getline(cmd, commande, ',');
	tmp_val	= atoi(commande.c_str());
    
	//Vérification de la valeur de Audio selection
	if(tmp_val < 0 || tmp_val > 1
		|| (tmp_val == 0 && commande.compare("0") != 0))
	{
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		return ERR_NON_CONFORME;
	}

	analogDteEnCours.activateLocalAudioInterface	= (tmp_val == 1);
	analogDteEnCours.activateCentralAudioInterface	= (tmp_val == 0);

    // Mise à jour des structures
	equip->SetGeneralParameters(tmp_Preset, presetEnCours);
	equip->SetAnalogDCEParameters(tmp_Preset,analogDceEnCours);
	equip->SetAnalogDTEParameters(tmp_Preset,analogDteEnCours);
	equip->SetDigitalDCEParameters(tmp_Preset,digitalDceEnCours);
	equip->SetDigitalDTEParameters(tmp_Preset,digitalDteEnCours);

	//Donnee reçu mise à jour de la vue
	equip->setReceptionDonnee(TRUE);
	equip->SetPresetList(tmp_Preset, 'A');			// Param 20 : Flag : Preset list

	ostringstream sss;
    sss << endl;
    sss << "\t" << "Traitement de SETPS" << endl;
    sss << "\t" << "tmp_Preset: " << tmp_Preset << endl << endl;
    pLogger.LOG_DEBUG(sss);

	pLogger.LOG_TRACE("Fin CProtoED42:: SETPS(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		SETUL()
TRAITEMENT:		Permet de définir le nombre maximum de mise à jour pouvant
				être effectuées (page 190)
***************************************************************************	*/
int CProtoED42:: SETUL(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: SETUL(string trame)");

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if(equip->GetStatusS20() >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(equip->GetStatusS20() != 0 || (equip->GetStatusBusy() == 1 && equip->GetDureeBusy() != 0))
	{
		pLogger.LOG_TRACE("Dans if(equip->GetStatusS20() != 0 || equip->GetStatusBusy() == 1");

		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	//Envoi d'un RES
	isRES = TRUE;


	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}

	if (equip->GetOperatingStatus() == ONLINE)
	{
		//Parametre invalide
		equip->setStatusErrorTable(WRONG_COMMAND, TRUE);
		return WRONG_COMMAND;
	}
	
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 2 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(equip->GetRemoteTC() == LOCAL_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}

	int param;
	const std::string& tmp = trame;
    const char* cstr = tmp.c_str();
	param = GestionHexa(cstr);

	if(param < MIN_UPDATE_LIMIT || param > MAX_UPDATE_LIMIT)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		//Pour l'erreur
		equip->setErrorTable(CONFIGURATION_ERROR, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}
	
	equip->SetUpdateLimit(param);

	pLogger.LOG_TRACE("Fin CProtoED42:: SETUL(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		SYS()
TRAITEMENT:		Requête du statut du système (page 161)
***************************************************************************	*/
int CProtoED42:: SYS(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: SYS(string trame)");

	int tmpS20 = equip->GetStatusS20();
	
	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	if((tmpS20 >= 2) && !equip->GetStatusNl())		// TODO pour le  && !equip->GetStatusNl()
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;

		return NOT_REMOTE_MODE;
	}


	//Cas d'une erreur CONFLICT (S#20)
	if(tmpS20 != 0 && !equip->GetStatusNl())										// TODO pour le  && !equip->GetStatusNl()
	{
		equip->setStatusErrorTable(CONFLICT, TRUE);
		//Force le RES
		isRES = TRUE;

		return CONFLICT;
	}
	

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);

		return ERR_NON_CONFORME;
	}


	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;
	}

	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);

		return ERR_NON_CONFORME;
	}

	if(trame.compare("?") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;		
	}

	// Fabrication de la réponse:

	// Res : >a01N93S#00SYS#40000200RCS#fa<
	//                      --------
	//                         |
	//                         |
	//                         V

	// HEXA : 40000200
	// BIN  : 0|0|0|0|0|0|0|0| x|0|0|0|0|xx|0|xxxx|0010|xxx|00000
	// POS  : 31             |23|                              0
	// HEXA : 40000201
	// BIN  : 0|1|0|0|0|0|0|0| x|0|0|0|0|xx|0|xxxx|0010|xxx|00001
	// POS  : 31             |23|                              0
	// HEXA : 62200200
	// BIN  : 0|1|1|0|0|0|1|0| x|0|1|0|0|xx|0|xxxx|0010|xxx|00000
	// POS  : 31             |23|                              0

	//Récupérer de la valeur en binaire avant de la transformer en hexadécimal.
	stringstream elementBin;
	stringstream elementHex;

	//typeCmd = 3;
	strcat(bufCmd, "SYS#");


	//Les valeurs 31 est non utilisées.
	elementBin << "0";

	//Pour Key memory 30
	elementBin << equip->GetKeyMemory();

	//Pour key state 29
	elementBin << equip->GetActiveKeyState();

	//--------Recherche de l'élément 28---------
	//Pour KE state 28
	elementBin << equip->GetKEState();

	//Pour error 27
	elementBin << equip->GetError();

	//Pour alarm 26
	elementBin << equip->GetAlarm();

	//Pour key list l'élément 25
	if (equip->GetKeyList() == 1)
		elementBin << "1";
		else
		elementBin << "0";

	//--------Recherche de l'élément 24---------
	//Pour system configuration
	elementBin << equip->GetSystemConfiguration();

	//La valeur 23 est non utilisée.
	elementBin << "0";

	//Pour busy 22
	elementBin << equip->GetStatusBusy();

	//Pour Online preset 21
	elementBin << equip->GetOnlinePresetStatus();

	//Pour Preset List 20
	if (equip->GetPresetList()!=0)
		elementBin << "1";
	else
		elementBin << "0";


	//Pour Data transfert Device Active 19
	elementBin << equip->GetDataTransfertDevice();

	//Les valeurs 17 et 18 non utilisées.
	elementBin << "00";

	//--------Recherche de l'élément 4---------
	//Pour Active control mode 16
	elementBin <<  equip->GetRemoteTC();

	//Les valeurs 12 à 15 non utilisées.
	elementBin << "0000";

	//Les valeurs 11 et 10 sont toujours à 0 d'apres la doc.
	elementBin << "00";

	//Pour le StateCIK 8 - 9
	switch(equip->GetStateCik())
	{
		case NO_CIK_STATE:
			elementBin << "00";
			break;
		case UNKNOWN_CIK_STATE:
			elementBin << "01";
			break;
		case VALID_CIK_STATE:
			elementBin << "10";
			break;
		case WAITING_CIK_STATE:
			elementBin << "11";
			break;
		default:
			elementBin << "00";
			break;
	}

	////--------Recherche de l'élément 5 à 7 Unused---------
	elementBin << "000";

	//Pour StatusCall - élément 4
	elementBin << equip->GetStatusCall();

	//Pour StatusSync - élément 3
	elementBin << equip->GetStatusSync();

	//Pour StatusRx - élément 2
	elementBin << equip->GetStatusRx();

	//Pour StatusTx - élément 1
	elementBin << equip->GetStatusTx();

	//Pour OperatingStatus - élément 0
	if(equip->GetOperatingStatus() == ONLINE)
		elementBin << "1";
		else
		elementBin << "0";

	//Mise en place du format de la réponse en hexadécimal "XXXXXXXX"
	elementHex << setfill('0') << setw(8);

	elementHex << hex << strtol(elementBin.str().c_str(),NULL,2);

	strcat(bufCmd, elementHex.str().c_str());

	ostringstream sss;
    sss << endl;
    sss << "\t" << "Traitement de SYS" << endl;
	sss << "\t" << "bufCmd:  " << bufCmd << endl << endl;
    pLogger.LOG_DEBUG(sss);

	pLogger.LOG_TRACE("Fin CProtoED42:: SYS(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		TAK()
TRAITEMENT:		Passe en mode Remote (page 168)
***************************************************************************	*/
int CProtoED42:: TAK(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: TAK(string trame)");

	//Envoi d'un RES
	isRES = TRUE;

	/* TODO puisque l'équipement répond un RES0,0,1 pour un TAK0
	if(equip->GetRemoteTC() == REMOTE_TC)
	{
		//Parametre invalide
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		return ERR_NO_REMOTE_MODE;
	}
	*/

	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}

	if(trame.compare("0") != 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return ERR_NON_CONFORME;		
	}
	
	//Vérification si on est en présence d'une erreur S#20 (sequence conflict)
	if(equip->GetStatusS20() == 2)
	{
		pLogger.LOG_TRACE("Dans CProtoED42:: TAK(string trame) et if(equip->GetStatusS20() == 2)");

		equip->SetStatusS20(1);
	}

	equip->setRemoteStatus(TRUE);
	//equip->setRemoteMode(REMOTE);
	equip->SetRemoteTC(REMOTE_TC);

	pLogger.LOG_TRACE("Fin CProtoED42:: TAK(string trame)");

	return SUCCESS;
}

/* **************************************************************************
METHODE :		VER()
TRAITEMENT:		Renvoie la version de l'appareil (page 185)
***************************************************************************	*/
int CProtoED42:: VER(string trame)
{
	pLogger.LOG_TRACE("Dans CProtoED42:: VER(string trame)");

	int tmpS20 = equip->GetStatusS20();

	//Vérification si on est en présence d'une erreur S#10 (NOT_REMOTE_MODE)
	//if(equip->GetStatusS20() == 3 || equip->GetStatusS20() == 2)
	if(tmpS20 >= 2)
	{
		equip->setStatusErrorTable(NOT_REMOTE_MODE, TRUE);
		//Force le RES
		isRES = TRUE;
		return NOT_REMOTE_MODE;
	}

	//Cas d'une erreur CONFLICT (S#20)
	if(tmpS20 != 0)
	{
		equip->setStatusErrorTable(CONFLICT, TRUE);
		
		//Force le RES
		isRES = TRUE;
		return CONFLICT;
	}

	if(!(equip->getAuthentified()))
	{
		//Pour l'erreur
		equip->setErrorTable(WRONG_PASSWORD, TRUE);
		//Position du flag de l'erreur
		equip->SetError(TRUE);

		return ERR_NON_CONFORME;
	}
	
	if(trame.size() == 0)
	{
		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);
		return ERR_NON_CONFORME;
	}


	//La taille du message est trop grande ou vide.
	if(trame.size() > 1 )
	{
		equip->setStatusErrorTable(MAX_MSG_LENGTH, TRUE);
		return ERR_NON_CONFORME;
	}
	
	//string versionNumber="VER401120813,401120812,027120711,027140711,048120813,601261011";
	if(trame.compare("?") == 0)
	{
		//strcat(bufCmd, "VER401120813,401120812,027120711,027140711,048120813,601261011");
		
		strcat(bufCmd, "VER");

		//Version et date du signal processing red
		strcat(bufCmd, equip->GetVersionRed().c_str());
		strcat(bufCmd, ",");

		//Version et date du signal processing black
		strcat(bufCmd, equip->GetVersionBlack().c_str());
		strcat(bufCmd, ",");

		//Version et date du PLD red
		strcat(bufCmd, equip->GetVersionPldRed().c_str());
		strcat(bufCmd, ",");

		//Version et date du PLD black
		strcat(bufCmd, equip->GetVersionPldBlack().c_str());
		strcat(bufCmd, ",");

		//Version et date de operator device
		strcat(bufCmd, equip->GetVersionOpeDevice().c_str());
		strcat(bufCmd, ",");

		//Version et date de MIL-Bus
		strcat(bufCmd, equip->GetVersionMilBus().c_str());

		pLogger.LOG_TRACE("Fin CProtoED42:: VER(string trame) et return SUCCESS;");

		return SUCCESS;
	}
	else
	{
		pLogger.LOG_TRACE("Fin CProtoED42:: VER(string trame) et return INVALID_PARAMETER;");

		equip->setStatusErrorTable(INVALID_PARAMETER, TRUE);

		return INVALID_PARAMETER;
	}

	pLogger.LOG_TRACE("Fin CProtoED42:: VER(string trame)");
}

/* **************************************************************************
METHODE :		getUneError()
TRAITEMENT:		Renvoie l'erreur la dernière erreur stocké dans (COMMAND_RES)
***************************************************************************	*/
string CProtoED42::getUneError(string tmp_cmd)
{
	pLogger.LOG_TRACE("Dans CProtoED42::getUneError(string tmp_cmd)");
	pLogger.LOG_TRACE(tmp_cmd);

	char buffer[3] = "";
	bool errorFind = FALSE;
	char bufErr[TAILLE_BUFFER] = "";

	strcat(bufErr, tmp_cmd.c_str());

	//Recherche de la première erreur
	TError error;
	TVectorError errorEncours = equip->getErrors();

	/*for(int i=0;i<errorEncours.size();i++)
	{
		error = equip->DecodeError(errorEncours[i]);
		if(error.used)
		{
			errorFind = TRUE;
			break;
		}
	}

	if(errorFind)
	{
		itoa(error.errorNumbers,buffer,10);
		strcat(bufErr, buffer);

		strcat(bufErr, ",");

		itoa(error.extendedCodes,buffer,10);
		strcat(bufErr, buffer);
	}
	else
		strcat(bufErr, "0,0");*/

	if(errorEncours[COMMAND_RES].compare(" ") != 0)
	{
		pLogger.LOG_TRACE("Dans CProtoED42::getUneError(string tmp_cmd) et if(errorEncours[COMMAND_RES].compare(' ') != 0)");

		error = equip->DecodeError(errorEncours[COMMAND_RES]);

		ostringstream sss;
		sss << endl;
		sss << "\t" << "TError error" << endl;
		sss << "\t" << "error.errorNumbers:  " << error.errorNumbers << endl;
		sss << "\t" << "error.extendedCodes:  " << error.extendedCodes << endl;
		pLogger.LOG_DEBUG(sss);

		itoa(error.errorNumbers,buffer,10);
		strcat(bufErr, buffer);

		strcat(bufErr, ",");
		itoa(error.extendedCodes,buffer,10);
		strcat(bufErr, buffer);

		//On efface l'erreur en l'enplacement RES
		pLogger.LOG_TRACE("Dans CProtoED42::On efface l'erreur en l'enplacement RES");
		errorEncours[COMMAND_RES] = " ";
		equip->setErrors(errorEncours);
	}
	else
	{
		strcat(bufErr, "0,0");
	}

	pLogger.LOG_TRACE(bufErr);
	pLogger.LOG_TRACE("Fin CProtoED42::getUneError(string tmp_cmd)");

    return bufErr;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int CProtoED42::GestionHexa(const char* toBeTested)
{
	pLogger.LOG_TRACE("Dans CProtoED42::GestionHexa");

	int iResult;

	if(toBeTested[0] == '#')
	{
		iResult = strtol(toBeTested+1, NULL, 16);
	}
	else
	{
		iResult = atoi(toBeTested);
	}

	return iResult;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
int CProtoED42::DecimalToHexa(char* number)
{
	pLogger.LOG_TRACE("CProtoED42::DecimalToHexa(char* number)");

	int iResult = strtol(number, NULL, 16);

	return iResult;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
string CProtoED42::HaxaToStringRCS(string reponse)
{
	pLogger.LOG_TRACE("Dans CProtoED42::HaxaToStringRCS(string reponse)");

    int checksum = 0x00;

    for(int i=0; i<reponse.length();i++)
    {
        checksum = checksum+reponse[i];
    }
		//Convertion du résultat en hexadécimal
		stringstream out2;
		out2 << hex <<checksum;
		string res = out2.str();

    return res;
}

/** \brief : Convertion d'un résultat en hexadécimal
 *
 * \param
 * \param
 * \return
 *
 */
string CProtoED42::IntToHexaString(int reponse, int format)
{
	pLogger.LOG_TRACE("Dans CProtoED42::IntToHexaString(int reponse, int format)");

	ostringstream sss;
    sss << endl;
    sss << "\t" << "reponse: " << reponse << endl;
	sss << "\t" << "format: " << format << endl;
    pLogger.LOG_DEBUG(sss);

    stringstream elementHex;

    //Mise en place du format de la réponse en hexadécimal "XXXXXXXX"
	elementHex << setfill('0') << setw(format);

    elementHex << hex <<reponse;

    string res = elementHex.str();

	pLogger.LOG_TRACE("Fin CProtoED42::IntToHexaString(int reponse, int format)");
	pLogger.LOG_TRACE(res);

    return res;
}

/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
string CProtoED42::TagStatusCrypto(string confKey, int tmpOnlinePreset, int tmpPresetType)
{
	pLogger.LOG_TRACE("Dans CProtoED42::TagStatusCrypto");

	stringstream elementBin;
	stringstream elementHex;

    //Mise à zéro de elementBin
    elementBin.str("");

	for (int ii = 7; ii>=0; ii--)
	{
		if (confKey[ii] == tmpPresetType || confKey[ii] == 'B')
			elementBin << "1";
		else
			elementBin << "0";
	}
    //Mise à zéro de elementHex
    elementHex.str("");
	//Mise en place du format de la réponse en hexadécimal "XX"
	elementHex << setfill('0') << setw(2);
	elementHex << hex << strtol(elementBin.str().c_str(),NULL,2);

	return elementHex.str();

}
/** \brief
 *
 * \param
 * \param
 * \return
 *
 */
string CProtoED42::KeyMemoryIndex(TMapKeyManagement confKey, int minPlage, int maxPlage)
{
	pLogger.LOG_TRACE("Dans CProtoED42::KeyMemoryIndex");

	ostringstream sss;
    sss << endl;
    sss << "\t" << "Traitement de KeyMemoryIndex" << endl;
    sss << "\t" << "minPlage: " << minPlage << endl;
	sss << "\t" << "maxPlage: " << maxPlage << endl << endl;
    pLogger.LOG_DEBUG(sss);

	char buffer[3] = {0};
	stringstream elementBin;
	stringstream elementHex;

	//Mise à zéro de elementBin
    elementBin.str("");
    //Mise en place du format "XX"
    elementBin << setfill('0') << setw(32);

	for (int ii = maxPlage; ii>=minPlage; ii--)
	{
		itoa(ii,buffer,10);
		if (confKey[buffer].updateCount != 255)
			elementBin << "1";
		else
			elementBin << "0";
	}

	//if(minPlage == 1)
		//elementBin << "0";

    //Mise à zéro de elementHex
    elementHex.str("");
	//Mise en place du format de la réponse en hexadécimal "XX"
	elementHex << setfill('0') << setw(4);
	elementHex << hex << strtol(elementBin.str().c_str(),NULL,2);

	pLogger.LOG_TRACE("Fin CProtoED42::KeyMemoryIndex");

	return elementHex.str();
}

//***************************************************************
// Construction du REQPSx
//***************************************************************
void CProtoED42::buildTrameREQPS(TGeneralParameters presetEnCours,
								 TDigitalDCE digitalDceEnCours,
								 TDigitalDTE digitalDteEnCours,
								 TAnalogDCE analogDceEnCours,
								 TAnalogDTE analogDteEnCours)
{
	pLogger.LOG_TRACE("Dans CProtoED42::buildTrameREQPS");

	//Récupération du preset demandé
	char buffer[10]="";
	string result="";
	stringstream elementBin;

	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 2 Preset type
	itoa(presetEnCours.operation_mode,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 3 transmissionMode
	itoa(presetEnCours.transmission_mode,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 4 transmissionProc
	itoa(presetEnCours.transmission_procedure,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 5 trafficMode
	itoa(presetEnCours.trafic_mode,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 6 reserved
	strcat(bufCmd, "0");
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 7 syncMode
	itoa(presetEnCours.synchronisation_mode,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 8 unknown
	strcat(bufCmd, "0");
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 9 unknown
	strcat(bufCmd, "0");
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 10 parity
	itoa(presetEnCours.parity,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 11 numberOfStopBits
	itoa(presetEnCours.nb_of_stop_bite,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 12 outputSelect
	itoa(presetEnCours.output_selection,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 13 antispoof
	itoa(presetEnCours.antispoof,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 14 dataRate
	itoa(presetEnCours.data_rate,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 15 FEC
	itoa(presetEnCours.fec,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 16 LeadTime
	itoa(presetEnCours.lead_time,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 17 Interface selection
	strcat(bufCmd,"#");

	elementBin << presetEnCours.dceDigitalInterface;
	elementBin << presetEnCours.dceAnalogInterf;
	elementBin << presetEnCours.dteDigitalInterface;
	elementBin << presetEnCours.dteAnalogInterf;

	//Mise en place du format de la réponse en hexadécimal "XX"
	strcat(bufCmd, IntToHexaString(strtol(elementBin.str().c_str(),NULL,2),2).c_str());
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 18 DCE outputlevel
	itoa(digitalDceEnCours.outputLevel,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 19 DCE Digital polarity
	strcat(bufCmd,"#");

	//Mise à zéro de elementBin
	elementBin.str("");

	elementBin << digitalDceEnCours.polarityOutputSignalTXD;
	elementBin << digitalDceEnCours.polarityOutputSignalRTS;
	elementBin << digitalDceEnCours.polarityOutputSignalDTR;
	elementBin << digitalDceEnCours.polarityOutputSignalTCK;
	elementBin << digitalDceEnCours.polarityOutputSignalRTL;
	elementBin << digitalDceEnCours.polarityOutputSignalLTL;
	elementBin << digitalDceEnCours.polarityInputSignalRXD;
	elementBin << digitalDceEnCours.polarityInputSignalCTS;
	elementBin << digitalDceEnCours.polarityInputSignalDSR;
	elementBin << digitalDceEnCours.polarityInputSignalDCD;
	elementBin << digitalDceEnCours.polarityInputSignalXCK;
	elementBin << digitalDceEnCours.polarityInputSignalRCK;
	elementBin << digitalDceEnCours.polarityInputSignalRNG;
	elementBin << digitalDceEnCours.polarityInputSignalLLR;

	//Mise en place du format de la réponse en hexadécimal "XXXX"
	strcat(bufCmd, IntToHexaString(strtol(elementBin.str().c_str(),NULL,2),4).c_str());
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 20 DTE Digital
	itoa(digitalDteEnCours.outputLevel,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 21 DTE Digital polarity
	strcat(bufCmd,"#");

	//Mise à zéro de elementBin
	elementBin.str("");

	elementBin << digitalDteEnCours.polarityInputSignalTXD;
	elementBin << digitalDteEnCours.polarityInputSignalRTS;
	elementBin << digitalDteEnCours.polarityInputSignalDTR;
	elementBin << digitalDteEnCours.polarityInputSignalRTL;
	elementBin << digitalDteEnCours.polarityInputSignalLTL;
	elementBin << digitalDteEnCours.polarityOutputSignalRXD;
	elementBin << digitalDteEnCours.polarityOutputSignalCTS;
	elementBin << digitalDteEnCours.polarityOutputSignalDSR;
	elementBin << digitalDteEnCours.polarityOutputSignalDCD;
	elementBin << digitalDteEnCours.polarityOutputSignalXCK;
	elementBin << digitalDteEnCours.polarityOutputSignalRCK;
	elementBin << digitalDteEnCours.polarityOutputSignalRNG;
	elementBin << digitalDteEnCours.polarityOutputSignalLLR;

	//Mise en place du format de la réponse en hexadécimal "XXXX"
	strcat(bufCmd, IntToHexaString(strtol(elementBin.str().c_str(),NULL,2),4).c_str());
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 22 DCE Analog polarity
	strcat(bufCmd,"#");

	//Mise à zéro de elementBin
	elementBin.str("");

	elementBin << analogDceEnCours.polarityDPTT;
	elementBin << analogDceEnCours.polarityBBDP;
	elementBin << analogDceEnCours.polarityNBWB;
	elementBin << analogDceEnCours.polarityPTT;
	elementBin << analogDceEnCours.polaritySQM;
	elementBin << analogDceEnCours.polaritySQG;

	//Mise en place du format de la réponse en hexadécimal "XX"
	strcat(bufCmd, IntToHexaString(strtol(elementBin.str().c_str(),NULL,2),2).c_str());
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 23 DCE Analog configuration
	strcat(bufCmd,"#");

	//Mise à zéro de result
	result="";

	itoa(analogDceEnCours.confTypeSQUELCH,buffer,10);
	result.append(buffer);
	itoa(analogDceEnCours.confTypeSQG,buffer,10);
	result.append(buffer);
	itoa(analogDceEnCours.confTypeSQM,buffer,10);
	result.append(buffer);
	itoa(analogDceEnCours.confTypeDPTT,buffer,10);
	result.append(buffer);

	//Mise en place du format de la réponse en hexadécimal "XXXXXXXX"
	strcat(bufCmd, IntToHexaString(strtol(result.c_str(),NULL,10),8).c_str());
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 24 RXNB Level
	itoa(analogDceEnCours.levelRXNB+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 25 TXNB Level
	itoa(analogDceEnCours.levelTXNB+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 26 RXWB Level
	itoa(analogDceEnCours.levelRXWB+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 27 TXWB Level
	itoa(analogDceEnCours.levelTXWB+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 28 DTE analog polarity
	strcat(bufCmd,"#");

	//Mise à zéro de elementBin
	elementBin.str("");

	elementBin << analogDteEnCours.microSupply;
	elementBin << analogDteEnCours.activateMonitoring;
	elementBin << "00";

	//Mise en place du format de la réponse en hexadécimal "XX"
	strcat(bufCmd, IntToHexaString(strtol(elementBin.str().c_str(),NULL,2),2).c_str());
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 29 DTE analog configuration
	strcat(bufCmd,"#");

	//Mise à zéro de result
	result="";

	itoa(analogDteEnCours.confTypePTTCTR,buffer,10);
	result.append(buffer);
	itoa(analogDteEnCours.confTypePTT42,buffer,10);
	result.append(buffer);
	itoa(analogDteEnCours.microType,buffer,10);
	result.append(buffer);

	//Mise en place du format de la réponse en hexadécimal "XXXXXX"
	strcat(bufCmd, IntToHexaString(strtol(result.c_str(),NULL,10),6).c_str());
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 30 Internal RI
	itoa(analogDteEnCours.microRi,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 31 Micro supply voltage
	itoa(analogDteEnCours.voltageSupply,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 32 Micro level
	itoa(analogDteEnCours.microLevel+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 33 Phone level
	itoa(analogDteEnCours.phoneLevel+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 34 TXCTR level
	itoa(analogDteEnCours.rxctrLevel+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 35 RXCTR level
	itoa(analogDteEnCours.rxctrLevel+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 36 TX Plain level
	itoa(analogDteEnCours.txbypassLevel+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 37 Bypass level
	itoa(analogDteEnCours.rxbypassLevel+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 38 Monitor level
	itoa(analogDteEnCours.monitorLevel+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 39 Sidetone adaption
	itoa(analogDteEnCours.sidetoneLevel+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 40 Alarme adaption
	itoa(analogDteEnCours.alarmeLevel+50,buffer,10);
	strcat(bufCmd, buffer);
	//Mise en place du séparateur
	strcat(bufCmd,",");

	// param : 41 Audio selection
	itoa(analogDteEnCours.activateLocalAudioInterface,buffer,10);
	strcat(bufCmd, buffer);

	pLogger.LOG_TRACE("Fin CProtoED42::buildTrameREQPS");
}

//***************************************************************************************************
// Return false si pas de problème sinon return true si un problème avec le nr de l'error dans le ret
//***************************************************************************************************
bool CProtoED42::testTrameFirst(string trame, int sizeMin, int sizeMax, char usedSep, int *ret, bool option, int typeOption, bool isOnline)
{
	pLogger.LOG_TRACE("Dans CProtoED42::testTrameFirst");

	if (isOnline && equip->GetOperatingStatus() == ONLINE)
	{
		pLogger.LOG_TRACE("Dans CProtoED42::testTrameFirst et if (isOnline && equip->GetOperatingStatus() == ONLINE)");

		*ret =  WRONG_COMMAND;
		return true;
	}

	if (option)
	{
		switch(typeOption)
		{
		case 0:
			break;
		case 1:				// Pour le test sur une commande CV
			if(trame[trame.length()-1] != usedSep)
			{
				*ret = WRONG_COMMAND;
				return true;
			}
		break;
		case 2:				// Pour le test sur une commande CVBUD/CVDLA
			if(trame[0] != usedSep)
			{
				*ret = INVALID_PARAMETER;
				return true;
			}
		break;
		}
	}else{
		if(trame.size() == sizeMin)
		{
			*ret = WRONG_COMMAND;
			return true;
		}

		//La taille du message est trop grande ou vide
		if(trame.size() > sizeMax )
		{
			if (typeOption != 3)				// Test pour CVDEL
				*ret = MAX_MSG_LENGTH;
			else
				*ret = INVALID_PARAMETER;
			return true;
		}
	}

	// typeOption : 4 pour SETHT
	// typeOption : 5 pour CVTAG
	// typeOption : 6 pour ONL
	// typeOption : 6 pour SETPS

	if (trame[0] != usedSep && typeOption != 10 && typeOption != 3 && typeOption != 4 && typeOption != 5 && typeOption != 6 && typeOption != 1)
	{
		pLogger.LOG_TRACE("Dans CProtoED42::testTrameFirst et if (trame[0] != usedSep &&.....");

		*ret = WRONG_COMMAND;
		return true;
	}

	pLogger.LOG_TRACE("Dans CProtoED42::testTrameFirst et return false; donc error=false");

	return false;
}

