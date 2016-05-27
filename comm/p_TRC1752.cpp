/* **************************************************************************
FICHIER :	p_TRC1752.cpp	 			AUTEUR : DGE
DATE DE CREATION : 	05/10/09			DERNIERE MODIFICATION : 
VERSION :	1.0
ROLE :		Implémentation de la classe CProtoTRC1752
***************************************************************************	*/

#include "stdafx.h"

#include "Comm\p_TRC1752.h"
#include "Equip\EquipM1752.h"
#include "divers\div_tmp.h"


#include <sstream>

const int 	DEBUT_TRAME = 0xD;
const int 	FIN_TRAME 	= 0xA;

const int   NB_CAR_CMD = 3;

/* **************************************************************************
METHODE :		CProtoTRC1752()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProtoTRC1752::CProtoTRC1752(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;

	equip = (CEquipM1752*)pEqp;
}

/* **************************************************************************
METHODE :		~CProtoTRC1752()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProtoTRC1752::~CProtoTRC1752()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProtoTRC1752::EnvoyerTS(char *message)
{
	int		len_mes,iResult;
	int		nb_car_enveloppe;		// Nombre de caractère envlopant le message

	char	buf[TAILLE_BUFFER+1];
	//char	octet_controle[8];
	
	if(equip->GetTest("TC")!=true)
	{
	len_mes = (int)strlen(message);	// Taille du message à envoyer
	nb_car_enveloppe = 1 + 1; 	// Debut Trame + Fin Trame
												// n  PC par tranche de 8 car
	if(len_mes+nb_car_enveloppe > TAILLE_BUFFER)
		 return ERR_TAILLE_BUFFER;
	
	buf[0] = DEBUT_TRAME;
	strcpy(buf+1,message);
	iResult = (int)strlen(buf);
	buf[iResult] = FIN_TRAME;
	buf[iResult+1]=0;				// Force la fin de chaine
	
	iResult = ligne.Ecrire(buf);
	if(iResult < 0) return ERREUR_EXTERNE+iResult;

	return iResult;  // nb d'octet transmis
	}
	else return 0;
}

/* **************************************************************************
METHODE :		RecevoirTC()
TRAITEMENT:		Réceptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProtoTRC1752::RecevoirTC(char *message,int nb_car)
{
	char	buf[TAILLE_BUFFER+1];
	int		i,iResult;

	if(nb_car > TAILLE_BUFFER) return ERR_TAILLE_BUFFER;

	i=0;
	while(i<nb_car)
	{
		iResult = ligne.Lire(buf+i,1);
		if(iResult < 0) return ERREUR_EXTERNE+iResult;
		if(iResult == 0) return ERREUR_TIMEOUT;
		if(buf[i]==DEBUT_TRAME && i!=0)
		{
			buf[0] = DEBUT_TRAME;
			i=0;
		}
		if(buf[i]==FIN_TRAME) break;

		i++;
	}

	if(!ExtraitUtile(buf,message,&iResult)) 
		return ERR_NON_CONFORME;			// Message non conforme

	return iResult;
}

/* **************************************************************************
METHODE :		TraiteTC()
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquitement
***************************************************************************	*/
int CProtoTRC1752::TraiteTC(char *mes)
{
	istringstream trame (mes);

	string cmd = "";

	getline(trame, cmd, ';');

	// Si le modem est bloqué ou si le modem a une panne TC, il ne répond pas ou en test // FDI
	if (equip->Panne() >= 0 || equip->GetTest("TC")==true || equip->IsEnTest()==true) 
		return ERR_CDE_INCONNUE;

	// Liste des commandes attendues

	/* ************************** consultation ****************** */

	// ancienne methode

	if (cmd == "CEV")
		return CEV(trame);

	if (cmd == "IDE")
		return IDE(trame);

	if (cmd == "LID")
		return LID(trame);

	if (cmd == "CPI")
		return CPI(trame);

	if (cmd == "CTO")
		return CTO(trame);

	if (cmd == "CAV")
		return CAV(trame);

	if (cmd == "CAD")
		return CAD(trame);

	if (cmd == "CVM")
		return CVM(trame);

	if (cmd == "CTC")
		return CTC(trame);

	if (cmd == "CBF")
		return CBF(trame);

	if (cmd == "CID")
		return CID(trame);

	if (cmd == "CDT")
		return CDT(trame);

	if (cmd == "CSP")
		return CSP(trame);

	if (cmd == "CCP")
		return CCP(trame);

	if (cmd == "CLP")
		return CLP(trame);

	if (cmd == "CKT")
		return CKT(trame);

	if (cmd == "CTN")
		return CTN(trame);
	
	if (cmd == "EUA")
		return EUA();

	// nouvelle methode

	/* **************** modification possible en local *********** */

	if (cmd == "DIS")
		return DIS(trame);

	/* **************** modification ****************************** */

	if (cmd == "AUT")
		return AUT(trame);
	
	// Pour modifier quelque chose il faut etre en distant
	if (equip->GetMode() == false) return ERR_NON_CONFORME;

	// ancienne methode

	if(cmd == "PIL")
		return PIL(trame);

	if (cmd == "LOC")
		return LOC(trame);

	if (cmd == "TOK")
		return TOK(trame);

	if (cmd == "AID")
		return AID(trame);

	if (cmd == "AVM")
		return AVM(trame);

	// nouvelle methode

	if (cmd == "DVM")
		return DVM(trame);

	if (cmd == "DID")
		return DID(trame);

	if (cmd == "DIA")
		return DIA(trame);

	if (cmd == "DTC")
		return DTC(trame);

	if (cmd == "DBF")
		return DBF(trame);

	if (cmd == "DDT")
		return DDT(trame);

	if (cmd == "BFE")
		return BFE(trame);

	if (cmd == "TES")
		return TES(trame);

	if (cmd == "STE")
		return STE(trame);

	if (cmd == "TLS")
		return TLS(trame);

	if (cmd == "ACT")
		return ACT(trame);

	if (cmd == "DAC")
		return DAC(trame);

	if (cmd == "ZTS")
		return ZTS(trame);

	if (cmd == "MDV")
		return MDV(trame);

	if (cmd == "POR")
		return POR(trame);

	if (cmd == "RES")
		return RES(trame);

	if (cmd == "DSP")
		return DSP(trame);

	if (cmd == "DCP")
		return DCP(trame);

	if (cmd == "DLP")
		return DLP(trame);

	if (cmd == "AKT")
		return AKT(trame);

	if (cmd == "DLT")
		return DLT(trame);

	if (cmd == "WRT")
		return WRT(trame);

	if (cmd == "SEL")
		return SEL(trame);

	if (cmd == "ART")
		return ART(trame);

	if (cmd == "CLT")
		return CLT(trame);

	if (cmd == "CLS")
		return CLS(trame);

	if (cmd == "LNL")
		return LNL(trame);

	if (cmd == "UNL")
		return UNL(trame);

	if (cmd == "CHT")
		return CHT(trame);

	if (cmd == "MAG")
		return MAG(trame);

	if (cmd == "SOU")
		return SOU(trame);

	if (cmd == "POL")
		return POL(trame);


    // Commande inconnue
	EnvoyerTS("NAC;SYNTAXE");

	return ERR_CDE_INCONNUE;
}

void CProtoTRC1752::SendNAC(string * cmd, int pos)
{
	stringstream out;

	out << "NAC;" << *cmd << ";" << pos ;

	string reponse = out.str();

	EnvoyerTS((char*)LPCTSTR(CString(reponse.c_str())));
}

void CProtoTRC1752::SendNAC(string * cmd, string * param)
{
	string reponse;

	if (*param != "")
	{
		stringstream out;

		out << "NAC;" << *cmd << ";" << *param; 

		reponse = out.str();
	} else 
		reponse = "NAC;" + *cmd;

	EnvoyerTS((char*)LPCTSTR(CString(reponse.c_str())));
}

void CProtoTRC1752::SendACK(string * cmd, string * param)
{
	string reponse;

	if (*param != "")
	{
		stringstream out;

		out << "ACK;" << *cmd << ";" << *param; 

		reponse = out.str();
	} else 
		reponse = "ACK;" + *cmd;

	EnvoyerTS((char*)LPCTSTR(CString(reponse.c_str())));
}

void CProtoTRC1752::SendSignaling(string cmd, string * param)
{
	string reponse;

	if (param != NULL)
	{
		stringstream out;

		out << cmd << ";" << *param; 

		reponse = out.str();
	} else
		reponse = cmd;

	EnvoyerTS((char*)LPCTSTR(CString(reponse.c_str())));
}

/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
int CProtoTRC1752::TraiteTS(int type_cde,char *reponse)
{
	strcpy(reponse, "");
	string rep;

	if (type_cde > 0 && type_cde <= 49)
	{
		// incident voie
		rep = "INCIDENT MODEM ";
	} else if (type_cde > 49 && type_cde <= 155)	//201 - 155 - FFT_1165
	{
		// incident carte
		rep = "INCIDENT MODEM ";
	} else if (type_cde > 155 && type_cde <= NB_ERREURS)	//201 - 155 - FFT_1165
	{
		// panne modem
		rep = "PANNE MODEM ";

		equip->SetPanne(type_cde);
	} else return ERR_CDE_INCONNUE;

	rep += equip->erreurs[type_cde].code;

	// Pour les erreurs 42 à 49 la voie est indiquée dans le INC
	// Si l'erreur concerne la voie x et que la voie selectionnée dans la vue ops ne correspond
	// pas à la voie x de la carte rien ne se passe
	if (type_cde >= 42 && type_cde <= 49)
	{
		int voie = equip->GetVoieSelect();

		switch(type_cde)
		{
		case 42:
		case 46:
			if (voie != 0 && voie != 2) return ERR_CDE_INCONNUE;
			break;
		default:
			if (voie != 1 && voie != 3) return ERR_CDE_INCONNUE;
			break;
		}

		
		SignalINC(&(equip->erreurs[type_cde].code), &(CHANNELS[voie]), &(equip->erreurs[type_cde].erreur), NULL);
	} else
		SignalINC(&(equip->erreurs[type_cde].code), NULL, &(equip->erreurs[type_cde].erreur), NULL);

	equip->VueAutotest(rep);

	strcpy(reponse, rep.c_str());

	return 1;
}

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Retourne toujours TRUE (pas d'acquittement attendu)
***************************************************************************	*/
BOOL CProtoTRC1752::ValideAcquittement(int type_cde,char *buf)
{
	return TRUE;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génére un octet de controle.
***************************************************************************	*/
char* CProtoTRC1752::ControleTrame(char *message,char *octet_controle)
{
	// Pas de controle
	return "";
}

/* **************************************************************************
METHODE :		ExtraitUtile()
TRAITEMENT:		Extrait la partie utile d'une trame de télécommande
***************************************************************************	*/
BOOL CProtoTRC1752::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	//char 	octet_controle[8];
	int		len_mes;	//int		len_mes,nb_tranche;

	len_mes = (int)strlen(buf);		
	if(buf[0] != DEBUT_TRAME && buf[len_mes -1] != FIN_TRAME)
		return FALSE;

	*long_utile = len_mes - 2;
	strcpy(message,"");
	strncat(message,buf+1,*long_utile);

	return TRUE;
}



int CProtoTRC1752::ExtractData(istringstream &data, string res[], int length, char sep)
{
	for(int param_number = 1; param_number<length; param_number++)
		if(!getline(data, res[param_number], sep) && param_number != length-1)
		{
			return param_number;
		}

	string tmp;

	if(getline(data, tmp, sep)) return length+1;

	return 0;
}

int CProtoTRC1752::CEV(istringstream & trame) 
{
	string cmd = "CEV";
	string reponse = "";
	int param_number = 1;


	string id;
	if(!getline(trame, id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelId(id) == FALSE)
	{
		reponse = id + ";ID";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que la voie est possible dans la version courante
	if (equip->ValidChannelVersion(id) == FALSE)
	{
		reponse = id + ";VERSION";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	reponse = id + ";" + equip->GetChannelState(id);

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::IDE(istringstream & trame) 
{
	string cmd = "IDE";
	string reponse = "";

	reponse += equip->GetManufacturer() + ";";
	reponse += equip->GetIdentity() + ";";

	TBoard board;

	board = equip->GetBoardManagement();
	reponse += board.capabilities + ";" + board.number + ";" + board.release + ";" + board.day + ";" + board.month + ";" + board.year + ";";

	board = equip->GetBoard1();
	reponse += board.capabilities + ";" + board.number + ";" + board.release + ";" + board.day + ";" + board.month + ";" + board.year + ";";

	board = equip->GetBoard2();
	reponse += board.capabilities + ";" + board.number + ";" + board.release + ";" + board.day + ";" + board.month + ";" + board.year;

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::CPI(istringstream & trame) 
{
	string cmd = "CPI";
	string reponse = "";

	reponse = equip->GetClockPilot();

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::CTO(istringstream & trame) 
{
	string cmd = "CTO";
	string reponse = "";
	int param_number = 1;

	string id;
	if(!getline(trame, id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelId(id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que la voie est possible dans la version courante
	if (equip->ValidChannelVersion(id) == FALSE)
	{
		reponse = id + ";VERSION";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	reponse = id + ";" + equip->GetChannelLocalRemoteControl(id);

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::CAV(istringstream & trame) 
{
	string cmd = "CAV";
	string reponse = "";
	int param_number = 1;

	string id;
	if(!getline(trame, id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelId(id) == FALSE)
	{
		reponse = id + ";ID";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que la voie est possible dans la version courante
	if (equip->ValidChannelVersion(id) == FALSE)
	{
		reponse = id + ";VERSION";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// FFT_1188
	char index[3] = "";			// char index[2] = "";
	memset(index, '\0', 3);
	//

	// Si on est en non ale on laisse cette valeur vide
	if (equip->GetChannelType(id) != "-")
		sprintf (index, "%.2i", equip->GetChannelIndexScansetChannel(id));


	reponse = id + ";" + equip->GetChannelAssociatedAfConfigurationConverted(id) + ";" + equip->GetChannelDataLinkId(id) + ";"
		+ equip->GetChannelType(id) + ";" + index + ";;;" + equip->GetChannelLinkManagementType(id);

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::CAD(istringstream & trame) 
{
	string cmd = "CAD";
	string reponse = "";
	int param_number = 1;

	string id;
	if(!getline(trame, id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidDataLinkId(id) == FALSE)
	{
		SendNAC(&cmd, param_number);

		return ERR_NON_CONFORME;
	}

	// Verifie que le data link est possible dans la version courante
	if (equip->ValidDataLinkVersion(id) == FALSE)
	{
		reponse = id + ";VERSION";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	reponse = id + ";" + equip->GetDataLinkAssociatedConfiguration(id);

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::DIS(istringstream & trame) 
{
	string cmd = "DIS";
	string reponse = "";

	if(equip->IsEnTest() == TRUE)
	{
		SendNAC(&cmd,&reponse);
		return ERR_NON_CONFORME;
	}

	equip->SetMode(TRUE);

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::PIL(istringstream & trame) 
{
	string cmd = "PIL";
	string reponse = "";
	int param_number = 1;

	string value;
	if(!getline(trame, value, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie la valeur
	if(equip->ValidClockPilot(value) == FALSE )
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Test si external clock present
	if(equip->GetPilExt() == FALSE)
	{
		SendNAC(&cmd, &value);
		return ERR_NON_CONFORME;
	}


	equip->SetClockPilot(value);

	reponse = value;

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::LOC(istringstream & trame) 
{
	string cmd = "LOC";
	string reponse = "";

	if(equip->IsEnTest() == TRUE)
	{
		SendNAC(&cmd,&reponse);
		return ERR_NON_CONFORME;
	}

	equip->SetMode(FALSE);

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::TOK(istringstream & trame) 
{
	string cmd = "TOK";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string id;
	if(!getline(trame, id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelId(id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que la voie est possible dans la version courante
	if (equip->ValidChannelVersion(id) == FALSE)
	{
		reponse = id + ";VERSION";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Parametre 2
	string value;
	param_number++;
	if(!getline(trame, value, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie la valeur
	if(equip->ValidChannelLocalRemoteControl(value) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	bool sto = false;
	if (equip->GetChannelLocalRemoteControl(id) != value)
		sto = true;

	equip->SetChannelLocalRemoteControl(id, value);

	reponse = id;

	SendACK(&cmd, &reponse);

	// Le TOK doit provoquer l'envoi d'un STO en cas de changement
	if (sto == true)
		SignalSTO(id);

	return 0;
}

void CProtoTRC1752::SignalSTO(const string channel)
{
	string reponse = channel + ";" + equip->GetChannelLocalRemoteControl(channel);

	SendSignaling("STO", &reponse);
}

int CProtoTRC1752::AID(istringstream & trame) 
{
	string cmd = "AID";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string id;
	if(!getline(trame, id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidDataLinkId(id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que le data link est possible dans la version courante
	if (equip->ValidDataLinkVersion(id) == FALSE)
	{
		reponse = id + ";VERSION";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que la voie associée au data link n'est pas active
	if (equip->IsDataLinkUsed(id) == TRUE)
	{
		reponse = id + ";USED";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Parametre 2
	string configuration_id;
	param_number++;
	if(!getline(trame, configuration_id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie la valeur
	if(equip->ValidDataLinkAssociatedConfiguration(configuration_id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	equip->SetDataLinkAssociatedConfiguration(id, configuration_id);

	reponse = id;

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::AVM(istringstream & trame) 
{
	string cmd = "AVM";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string channel_id;
	if(!getline(trame, channel_id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelId(channel_id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que le channel est possible dans la version courante
	if (equip->ValidChannelVersion(channel_id) == FALSE)
	{
		reponse = channel_id + ";VERSION";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que le channel n'est pas actif
	if (equip->GetChannelState(channel_id) != "INACTIVE")
	{
		reponse = channel_id + ";USED";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Parametre 2
	string configuration_id;
	param_number++;
	if(!getline(trame, configuration_id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie la valeur
	if(equip->ValidChannelAssociatedAfConfiguration(configuration_id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Parametre 3
	string data_id;
	param_number++;
	if(!getline(trame, data_id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie la valeur
	if(equip->ValidChannelDataLinkId(data_id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que le data id est possible dans la version courante
	if(equip->ValidDataLinkVersion(data_id) == FALSE)
	{
		reponse = channel_id + ";VERSION";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que le data id n'est pas utilisé dans une autre voie
	if(equip->IsDataLinkUsed(data_id) == TRUE)
	{
		reponse = channel_id + ";USED";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Parametre 4
	string type;
	param_number++;
	if(!getline(trame, type, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie la valeur
	if(equip->ValidChannelType(type) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Parametre 5
	string canal_string;
	int canal = 0;
	param_number++;
	if(!getline(trame, canal_string, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Si on est en no ale on ignore
	if(type != "-")
	{
		// Conversion en int
		canal = atoi(canal_string.c_str());

		// Verifie la valeur
		if(equip->ValidChannelIndexScansetChannel(canal) == FALSE)
		{
			SendNAC(&cmd, param_number);
			return ERR_NON_CONFORME;
		}
	}

	// Parametre 6
	string not_use;
	param_number++;
	if(!getline(trame, not_use, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Parametre 7
	param_number++;
	if(!getline(trame, not_use, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Parametre 8
	string link_type;
	param_number++;
	if(!getline(trame, link_type, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie la valeur
	if(equip->ValidChannelLinkManagementType(link_type) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// On enregistre toutes les valeurs
	equip->SetChannelAssociatedAfConfiguration(channel_id, configuration_id);
	equip->SetChannelDataLinkId(channel_id, data_id);
	equip->SetChannelType(channel_id, type);
	if (type != "-")
		equip->SetChannelIndexScansetChannel(channel_id, canal);
	equip->SetChannelLinkManagementType(channel_id, link_type);

	reponse = channel_id;

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::LID(istringstream & trame) 
{
	string cmd = "LID";
	string reponse = "";

	int nb_iter = 4;
	TBoard board1 = equip->GetBoard1();;
	TBoard board2 = equip->GetBoard2();;

	if(equip->GetQuadrivoie() == FALSE) nb_iter = 2;

	for(int i = 0; i<nb_iter; i++)
	{
		reponse = equip->GetManufacturer() + ";";
		reponse += equip->GetIdentity() + ";";

		reponse += CHANNELS[i] + ";";

		if (i<2)
			reponse += board1.capabilities + ";" + board1.number + ";" + board1.release + ";" + board1.day + ";" + board1.month + ";" + board1.year;
		else
			reponse += board2.capabilities + ";" + board2.number + ";" + board2.release + ";" + board2.day + ";" + board2.month + ";" + board2.year;

		SendACK(&cmd, &reponse);
	}

	return 0;
}

int CProtoTRC1752::CVM(istringstream & trame) 
{
	string cmd = "CVM";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string channel_conf;
	if(!getline(trame, channel_conf, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelConfiguration(channel_conf) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que le channel est possible dans la version courante
	if ((channel_conf == "B1" || channel_conf == "B2") && (equip->ValidChannelVersion(channel_conf) == FALSE))
	{
		reponse = channel_conf + ";VERSION";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Si on demande la configuration d'une des voies, on renvoi le contenu de la conf associé à la voie

	if (channel_conf == "A1" || channel_conf == "A2" || channel_conf == "B1" || channel_conf == "B2")
	{
		string channel_associe = equip->GetChannelAssociatedAfConfiguration(channel_conf);

		// Si le channel associé est MC on a rien à faire 
		//if (channel_associe != "MC") channel_conf = channel_associe;
	}

	TChannelConfiguration conf = equip->GetChannelConfiguration(channel_conf);

	// TODO
	if (conf.waveform == "FSKP" || conf.waveform == "FSKV")
		reponse = channel_conf + ";" + "BFSK" + ";" + conf.diversity + ";" + conf.direction + ";";
	else
		reponse = channel_conf + ";" + conf.waveform + ";" + conf.diversity + ";" + conf.direction + ";";

	if (conf.af_transmission_baudrate == 0)
		reponse += "AUTO";
	else reponse += IntToString(conf.af_transmission_baudrate, 4);
		
	reponse += ";" + conf.af_transmission_codingtype + ";"
		+ conf.af_transmission_interleaving + ";";

	if (conf.waveform == "4529")
		reponse += IntToString(conf.transmission_carrier_frequency, 4);

	reponse += ";";

	// TODO
	if (conf.waveform == "BFSK" || conf.waveform == "FSKP" || conf.waveform == "FSKV")
		reponse += IntToString(conf.transmission_space_frequency, 4);

	reponse += ";";

	// TODO
	if (conf.waveform == "BFSK" || conf.waveform == "FSKP" || conf.waveform == "FSKV")
		reponse += IntToString(conf.transmission_mark_frequency, 4);

	reponse += ";";

	if (conf.af_reception_baudrate == 0)
		reponse += "AUTO";
	else reponse += IntToString(conf.af_reception_baudrate, 4);

	reponse += ";" + conf.af_reception_codingtype + ";" + conf.af_reception_interleaving + ";";

	if (conf.waveform == "4529")
		reponse += IntToString(conf.reception_carrier_frequency, 4);

	reponse += ";";

	// TODO
	if (conf.waveform == "BFSK" || conf.waveform == "FSKP" || conf.waveform == "FSKV")
		reponse += IntToString(conf.reception_space_frequency, 4);

	reponse += ";";

	// TODO
	if (conf.waveform == "BFSK" || conf.waveform == "FSKP" || conf.waveform == "FSKV")
		reponse += IntToString(conf.reception_mark_frequency, 4);

	reponse += ";";

	if (conf.diversity == "AVEC")
	{
		reponse += IntToString(conf.slave_baudrate, 4) + ";" + conf.slave_codingtype + ";" 
		+ conf.slave_interleaving + ";";

		if (conf.waveform == "4529")
			reponse += IntToString(conf.slave_carrier_frequency, 4);

		reponse += ";" + conf.slave_direction + ";" + conf.use_data;
	}
	else reponse += ";;;;;";

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::CTC(istringstream &trame)
{
	string cmd = "CTC";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string aux_interface_id;
	if(!getline(trame, aux_interface_id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidAuxInterfaceConfiguration(aux_interface_id) == FALSE
		&& equip->ValidLocalRemoteInterfaceConfiguration(aux_interface_id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que le channel est possible dans la version courante
	if (((aux_interface_id == "IA5" || aux_interface_id == "IA6") && (equip->ValidAuxInterfaceConfigurationVersion(aux_interface_id) == FALSE))
		|| ((aux_interface_id == "TC3" || aux_interface_id == "TC4") && (equip->ValidLocalRemoteInterfaceConfigurationVersion(aux_interface_id) == FALSE)))
	{
		reponse = aux_interface_id + ";VERSION";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	reponse = aux_interface_id + ";";

	if (equip->ValidAuxInterfaceConfiguration(aux_interface_id) == TRUE)
	{
		TAuxInterfaceConfiguration value = equip->GetAuxInterfaceConfiguration(aux_interface_id);

		reponse += value.electrical_characteristics + ";" + IntToString(value.baudrate, 5) + ";" + IntToString(value.character_length,1) + ";" + value.character_parity
			+ ";" + IntToString(value.number_stop_bits,1) + ";" + IntToString(value.radio_address, 3) + ";" + value.equipment_type;
	} else {
		TLocalRemoteInterfaceConfiguration value = equip->GetLocalRemoteInterfaceConfiguration(aux_interface_id);

		reponse += value.electrical_characteristics + ";" + IntToString(value.baudrate, 5) + ";" + IntToString(value.characters_length,1) + ";" + value.characters_parity
			+ ";" + IntToString(value.number_stop_bits, 1) + ";;NORAD";
	}

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::CBF(istringstream &trame)
{
	string cmd = "CBF";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string af_channel_conf;
	if(!getline(trame, af_channel_conf, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidAfChannelConfiguration(af_channel_conf) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que le channel est possible dans la version courante
	if (equip->ValidAfChannelConfigurationVersion(af_channel_conf) == FALSE)
	{
		reponse = af_channel_conf + ";VERSION";

		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	TAFChannelConfiguration value = equip->GetAfChannelConfiguration(af_channel_conf);

	reponse = af_channel_conf + ";" + IntToString(value.input_level, 2) + ";" + IntToString(value.output_level, 2, TRUE) + ";"
		+ value.interface_type + ";" + value.ptt_type + ";" + IntToString(value.ptt_tempo, 4) + ";" + value.mute_characteristics + ";"
		+ IntToString(value.mute_delay, 4) + ";" + IntToString(value.radio_delay, 4);

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::CID(istringstream &trame)
{
	string cmd = "CID";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string data_link_configuration;
	if(!getline(trame, data_link_configuration, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidInterfaceConfiguration(data_link_configuration) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	TInterfaceConfiguration value = equip->GetInterfaceConfiguration(data_link_configuration);

	reponse = data_link_configuration + ";" + value.type + ";" + value.electrical_characteristics + ";";

	if (value.transmission_baudrate == 0) reponse += "AUTO";
	else reponse += IntToString(value.transmission_baudrate, 5);

	reponse += ";";

	if (value.reception_baudrate == 0) reponse += "AUTO";
	else reponse += IntToString(value.reception_baudrate, 5);

	reponse += ";";
	
	if (value.type == "SYNCHRONE")
		reponse += value.direction; 
	
	reponse += ";" + value.validity_time + ";" + value.binary_integrity + ";" + value.polarity + ";"
		+ value.handshake + ";" ;
		
	if (value.type == "ASYNCHRONE") 
		reponse += IntToString(value.character_length, 1) + ";" + value.parity + ";" + IntToString(value.number_stop_bits, 1);
	else reponse += ";;";
		
	reponse += ";" + value.data_flow_control;

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::CDT(istringstream &trame)
{
	string cmd = "CDT";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string channel_id;
	if(!getline(trame, channel_id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelId(channel_id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que l'id est different de A2 et B2
	if (channel_id == "A2" || channel_id == "B2")
	{
		reponse = ";ID";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que l'id est possible dans la version courante
	if (equip->ValidChannelVersion(channel_id) == FALSE)
	{
		reponse = channel_id + ";VERSION";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que le channel demandé n'est pas en panne
	if ( (channel_id == "A1" && equip->GetTest("A1")) 
		|| (channel_id == "B1" && equip->GetTest("B1")) )
	{
		reponse = channel_id + ";PANNE";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	TBoard value;

	char heure[9];  
	char date[9];
	GetTimeFormat (LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT , NULL, "HH'H'mm'.'ss", (LPTSTR) heure, 9); 
	GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,NULL,"dd'/'MM'/'yy", date, 9);

	string date_heure = date;
	date_heure += ".";
	date_heure += heure;

	if (channel_id == "A1")
	{
		value = equip->GetBoard1();
		value.date_and_time = date_heure;
		equip->SetBoard1(value);
	}
	else 
	{
		value = equip->GetBoard2();
		value.date_and_time = date_heure;
		equip->SetBoard2(value);
	}

	reponse = channel_id + ";" + value.date_and_time + ";" + IntToString(value.time_accuracy, 5) + ";" + value.date_origin + ";"
		+ value.last_date_and_time + ";" + IntToString(value.time_lag, 5, TRUE);

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::CSP(istringstream &trame)
{
	string cmd = "CSP";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string channel_id;
	if(!getline(trame, channel_id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelId(channel_id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que l'id est different de A2 et B2
	if (equip->ValidAleParameter(channel_id) == FALSE)
	{
		reponse = ";ID";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que l'id est possible dans la version courante
	if (equip->ValidAleParameterVersion(channel_id) == FALSE)
	{
		reponse = channel_id + ";VERSION";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	TAleParameter params = equip->GetAleParameter(channel_id);

	reponse = channel_id + ";;;;;;;;" + params.automatic_sounding + ";" + IntToString(params.aging_percentage, 3) + ";" 
		+ params.aging_time + ";" + params.multiservice + ";" + params.automatic_reconfiguration + ";" + IntToString(params.service_activation, 2)
		+ ";" + params.allcall_message + ";" + params.wildcard_message + ";" + params.anycall_message + ";" + params.respond + ";" 
		+ IntToString(params.scanrate, 1) + ";" + IntToString(params.twa_automatic, 3) + ";" + IntToString(params.twa_manual, 3) + ";"
		+ IntToString(params.twt, 4) + ";" + IntToString(params.tunetime_local, 4) + ";" + IntToString(params.tunetime_other, 4) + ";"
		+ params.ptt_gestion + ";";

	if (params.sound_length == 0) reponse += "---";
	else reponse += IntToString(params.sound_length, 3);

	reponse += ";" + IntToString(params.retries_channel, 1) + ";" + IntToString(params.retries_scanfield, 1) + ";" + IntToString(params.long_sound_limit, 2);

	SendACK(&cmd, &reponse);
	
	return 0;
}

int CProtoTRC1752::CCP(istringstream &trame)
{
	string cmd = "CCP";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string channel_id;
	if(!getline(trame, channel_id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelId(channel_id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que l'id est different de A2 et B2
	if (equip->ValidAleParameter(channel_id) == FALSE)
	{
		reponse = ";ID";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que l'id est possible dans la version courante
	if (equip->ValidAleParameterVersion(channel_id) == FALSE)
	{
		reponse = channel_id + ";VERSION";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	TAleParameter params = equip->GetAleParameter(channel_id);

	reponse = channel_id + ";;;" + params.cms_choice + ";" + params.ale_termination_frame + ";" + IntToString(params.index_channel_table, 2)
		+ ";";

	if (params.cms_choice == "LMF") reponse += IntToString(params.lowest_usable_frequency, 8) + ";" + IntToString(params.upper_usable_frequency, 8);
	else reponse += ";";

	// FFT_1189
	/*
	reponse += ";" + params.call_type + ";" + IntToString(params.index_selfaddress, 2) + ";" + params.quick_identification + ";" 
		+ params.quality_analysis + ";" + ";"; //params.station_network_group + ";";
		*/

	reponse += ";" + params.call_type + ";" + IntToString(params.index_selfaddress, 2) + ";" + params.quick_identification + ";" 
		+ params.quality_analysis + ";" + params.station_network_group + ";";						// parametre : 13

	// FFT_1189
	//if (params.call_type == "STD" || params.call_type == "NET") reponse += IntToString(equip->GetChannelIndexScansetChannel(channel_id), 2);

	reponse += IntToString(params.called_address, 2) + ";" + params.called_address_string + ";";	//station_network_group
	
	for(int i = 0; i<params.index_station_table_group.size(); i++)
		if (i == params.index_station_table_group.size()-1) reponse += IntToString(params.index_station_table_group[i],2);
		else reponse += IntToString(params.index_station_table_group[i],2) + "/";

			
	reponse += ";" + params.agc + ";" + IntToString(params.call_length,3) + ";" +  params.amd_message;

	SendACK(&cmd, & reponse);

	return 0;
}

int CProtoTRC1752::CLP(istringstream &trame)
{
	string cmd = "CLP";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string channel_id;
	if(!getline(trame, channel_id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelId(channel_id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que l'id est different de A2 et B2
	if (equip->ValidAleParameter(channel_id) == FALSE)
	{
		reponse = ";ID";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que l'id est possible dans la version courante
	if (equip->ValidAleParameterVersion(channel_id) == FALSE)
	{
		reponse = channel_id + ";VERSION";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	reponse = channel_id + ";" + IntToString(equip->GetAleLinkProtectionLevel(channel_id), 1);

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::CKT(istringstream &trame)
{
	string cmd = "CKT";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string channel_id;
	if(!getline(trame, channel_id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelId(channel_id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que l'id est different de A2 et B2
	if (equip->ValidAleParameter(channel_id) == FALSE)
	{
		reponse = ";ID";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que l'id est possible dans la version courante
	if (equip->ValidAleParameterVersion(channel_id) == FALSE)
	{
		reponse = channel_id + ";VERSION";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie qu'il y a une table dans lt0
	if (equip->GetTableLtName(channel_id, "LT0") == "")
	{
		reponse = channel_id + ";TABLE";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie qu'il y a une clée active
	if (equip->GetAleKeyPosition(channel_id) == -1)
	{
		reponse = channel_id + ";NOKEY";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	reponse = channel_id + ";" + equip->GetAleKeyManagement(channel_id) + ";" + equip->GetTableLtName(channel_id, "LT0") + ";"
		+ IntToString(equip->GetAleKeyPosition(channel_id), 2);

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::CTN(istringstream &trame)
{
	string cmd = "CTN";
	string reponse = "";
	int param_number = 1;

	// Parametre 1
	string channel_id;
	if(!getline(trame, channel_id, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidChannelId(channel_id) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Parametre 2
	string table;
	param_number++;
	if(!getline(trame, table, ';'))
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie l'id
	if (equip->ValidTableLT(table) == FALSE)
	{
		SendNAC(&cmd, param_number);
		return ERR_NON_CONFORME;
	}

	/*****************************************/

	// Verifie que l'id est différent de A2 et B2
	if (equip->ValidAleParameter(channel_id) == FALSE)
	{
		reponse = ";" + table + ";ID";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que l'id est possible dans la version courante
	if (equip->ValidAleParameterVersion(channel_id) == FALSE)
	{
		reponse = channel_id + ";" + table + ";VERSION";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que la table demandée existe
	if (equip->GetTableLtName(channel_id, table) == "")
	{
		reponse = channel_id + ";" + table + ";TABLE";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	reponse = channel_id + ";" + table + ";" + equip->GetTableLtName(channel_id, table);

	SendACK(&cmd, &reponse);

	return 0;
}

int CProtoTRC1752::DVM(istringstream &trame) //TODO, un parametre non attendu DOIT etre vide
{
	int param_number;

	// Les paramètres commencent à 1 et finissent à 22
	string params[23];

	// La commande
	params[0] = "DVM";

	int result; // utilisé en interne

// Chargement des paramètres
	for(param_number = 1; param_number<23; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 22)
		{
			
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie remote controle configuration
	if (equip->ValidChannelConfiguration(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}


	// FFT_1390
	if (params[1] == "MC")
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}


	// Verifie la version de remote controle configuration
	if (equip->ValidChannelConfigurationVersion(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie si le channel est utilisé
	if (equip->GetChannelState(params[1]) == "ACTIVE")
	{
		string reponse = params[1] + ";USED";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	// Verifie waveform
	if (equip->ValidChannelConfigurationWaveform(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

// Parametre 3
	// Verifie diversity
	if (equip->ValidChannelConfigurationDiversity(params[2], params[3]) == FALSE)
	{
		SendNAC(&params[0], 3);
		return ERR_NON_CONFORME;
	}

// Parametre 4
	// Verifie direction
	if (equip->ValidChannelConfigurationDirection(params[2], params[3], params[4]) == FALSE)
	{
		SendNAC(&params[0], 4);
		return ERR_NON_CONFORME;
	}	

// Les parametres 5,6,7,8,9,10 ne sont pas utilisés en RX
	if (params[4] != "RX")
	{
	// Parametre 5,6,7
	 
		// Verifie groupe transmision
		result = equip->ValidChannelConfigurationAfParameters(params[2], params[5], params[6], params[7]);
		if (result != 0)
		{
			SendNAC(&params[0], result+4);
			return ERR_NON_CONFORME;
		}

	// Parametre 8
		if(equip->ValidChannelConfigurationCarrierFrequency(params[2], params[8]) == FALSE)
		{
			SendNAC(&params[0], 8);
			return ERR_NON_CONFORME;
		}
	// Parametre 9 et 10
		result = equip->ValidChannelConfigurationFrequency(params[2], params[9], params[10]);
		if (result != 0)
		{
			SendNAC(&params[0], result+8);
			return ERR_NON_CONFORME;
		}
	}
	else
	{
		// On vide ces parametres
		for(param_number = 5; param_number<11; param_number++)
			params[param_number] = "";
	}

// Les parametres 11,12,13,14,15,16 ne sont pas utilisés en TX
	if (params[4] != "TX")
	{
	// Parametre 11,12,13

		// Verifie groupe reception
		result = equip->ValidChannelConfigurationAfParameters(params[2], params[11], params[12], params[13], TRUE);
		if (result != 0)
		{
			SendNAC(&params[0], result+10);
			return ERR_NON_CONFORME;
		}

		// En HD les parametres emission et reception doivent etre les memes
		// Sauf en MIL110 ou la reception est tjs à auto dans ce cas
		if (params[4] == "HD" && params[2] != "MIL110")
		{
			if (params[5] != params[11]) 
			{
				SendNAC(&params[0], 11);
				return ERR_NON_CONFORME;
			}
			if (params[6] != params[12])
			{
				SendNAC(&params[0], 12);
				return ERR_NON_CONFORME;
			}				
			if (params[7] != params[13])
			{
				SendNAC(&params[0], 13);
				return ERR_NON_CONFORME;
			}
		}

	// Parametre 14
		if(equip->ValidChannelConfigurationCarrierFrequency(params[2], params[14]) == FALSE)
		{
			SendNAC(&params[0], 14);
			return ERR_NON_CONFORME;
		}
	// Parametre 15 et 16
		result = equip->ValidChannelConfigurationFrequency(params[2], params[15], params[16]);
		if (result != 0)
		{
			SendNAC(&params[0], result+14);
			return ERR_NON_CONFORME;
		}
	}
	else
	{
		// On vide ces parametres
		for(param_number = 11; param_number<17; param_number++)
			params[param_number] = "";
	}

// Les parametres 17,18,19,20,21,22 qu'en diversité
	if(params[3] == "AVEC")
	{
		// Parametre 21
		if (equip->ValidChannelConfigurationSlaveDirection(params[2], params[21]) == FALSE)
		{
			SendNAC(&params[0], 21);
			return ERR_NON_CONFORME;
		}

	// Les parametres 17,18,19,20 ne sont pas utilisés en RX slave
		if (params[21] != "RX")
		{
		// Parametre 17,18,19

			// Verifie groupe slave
			result = equip->ValidChannelConfigurationAfParameters(params[2], params[17], params[18], params[19]);
			if (result != 0)
			{
				SendNAC(&params[0], result+16);
				return ERR_NON_CONFORME;
			}

		// Parametre 20
			if(equip->ValidChannelConfigurationCarrierFrequency(params[2], params[20]) == FALSE)
			{
				SendNAC(&params[0], 20);
				return ERR_NON_CONFORME;
			}
		}
		else
		{
			// On vide ces parametres
			for(param_number = 17; param_number<21; param_number++)
				params[param_number] = "";
		}

		// Parametre 22
		if (equip->ValidChannelConfigurationUseData(params[2], params[22]) == FALSE)
		{
			SendNAC(&params[0], 22);
			return ERR_NON_CONFORME;
		}
	}
	else
	{
		// On vide ces parametres
		for(param_number = 17; param_number<23; param_number++)
			params[param_number] = "";
	}

	// On arrive ici donc le DVM est valide !
	// On peut le sauver et envoyer le ACK
	
	// On change les parametres nouveaux
	TChannelConfiguration conf_courante = equip->GetChannelConfiguration(params[1]);
	
	conf_courante.waveform = params[2];

	if (params[3] != "") conf_courante.diversity = params[3];
	if (params[4] != "") conf_courante.direction = params[4];
	if (params[5] != "") conf_courante.af_transmission_baudrate = atoi(params[5].c_str());
	if (params[6] != "") conf_courante.af_transmission_codingtype = params[6];
	if (params[7] != "") conf_courante.af_transmission_interleaving = params[7];
	if (params[8] != "") conf_courante.transmission_carrier_frequency = atoi(params[8].c_str());
	if (params[9] != "") conf_courante.transmission_space_frequency = atoi(params[9].c_str());
	if (params[10] != "") conf_courante.transmission_mark_frequency = atoi(params[10].c_str());

	if (params[11] != "") 
	{
		if (params[11] == "AUTO")
			conf_courante.af_reception_baudrate = 0;
		else
			conf_courante.af_reception_baudrate = atoi(params[11].c_str());
	}

	if (params[12] != "") conf_courante.af_reception_codingtype = params[12];
	if (params[13] != "") conf_courante.af_reception_interleaving = params[13];
	if (params[14] != "") conf_courante.reception_carrier_frequency = atoi(params[14].c_str());
	if (params[15] != "") conf_courante.reception_space_frequency = atoi(params[15].c_str());
	if (params[16] != "") conf_courante.reception_mark_frequency = atoi(params[16].c_str());
	if (params[17] != "") conf_courante.slave_baudrate = atoi(params[17].c_str());
	if (params[18] != "") conf_courante.slave_codingtype = params[18];
	if (params[19] != "") conf_courante.slave_interleaving = params[19];
	if (params[20] != "") conf_courante.slave_carrier_frequency = atoi(params[20].c_str());
	if (params[21] != "") conf_courante.slave_direction = params[21];
	if (params[22] != "") conf_courante.use_data = params[22];

	equip->SetChannelConfiguration(params[1], conf_courante);

	SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::DID(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 14
	string params[15];

	// La commande
	params[0] = "DID";

	//int result; // utilisé en interne

// Chargement des paramètres
	for(int param_number = 1; param_number<15; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 14)
		{
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie interface conguration
	if (equip->ValidInterfaceConfiguration(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie si le data link est utilisé
	// Si le CI est associé à un data link (DX) et que ce data link correspond à une voie active
	if (equip->IsInterfaceConfigurationUsed(params[1]) == TRUE)
	{
		string reponse = params[1] + ";USED";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	// Verifie interface type
	if (equip->ValidInterfaceConfigurationType(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

// Parametre 3
	// Verifie electrical characteristic
	if (equip->ValidInterfaceConfigurationElectricalCharacteristic(params[2], params[3]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

// Parametre 4 et 5
	//TODO si les baudrate sont en autos il faudra les remplir à l'ACT à partir des valeurs du channel af associé
	if (equip->ValidInterfaceConfigurationBaudrate(params[2], params[6], params[4]) == FALSE)
	{
		SendNAC(&params[0], 4);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidInterfaceConfigurationBaudrate(params[2], params[6], params[5]) == FALSE)
	{
		SendNAC(&params[0], 5);
		return ERR_NON_CONFORME;
	}

// Parametre 6
	if (equip->ValidInterfaceConfigurationClockDirection(params[2], params[6]) == FALSE)
	{
		SendNAC(&params[0], 6);
		return ERR_NON_CONFORME;
	}

// Parametre 7, 8
	if (equip->ValidInterfaceConfigurationValidityTime(params[7]) == FALSE)
	{
		SendNAC(&params[0], 7);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidInterfaceConfigurationBinaryIntegrity(params[8]) == FALSE)
	{
		SendNAC(&params[0], 8);
		return ERR_NON_CONFORME;
	}

// Parametre 9,10
	if (equip->ValidInterfaceConfigurationPolarity(params[9]) == FALSE)
	{
		SendNAC(&params[0], 9);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidInterfaceConfigurationHandShake(params[10]) == FALSE)
	{
		SendNAC(&params[0], 10);
		return ERR_NON_CONFORME;
	}

// Parametre 11,12,13
	if (equip->ValidInterfaceConfigurationCharacterLength(params[2], params[11]) == FALSE)
	{
		SendNAC(&params[0], 11);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidInterfaceConfigurationParity(params[2], params[12]) == FALSE)
	{
		SendNAC(&params[0], 12);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidInterfaceConfigurationNumberStopBits(params[2], params[13]) == FALSE)
	{
		SendNAC(&params[0], 13);
		return ERR_NON_CONFORME;
	}

// Parametre 14
	if (equip->ValidInterfaceConfigurationDataFlowControl(params[14]) == FALSE)
	{
		SendNAC(&params[0], 14);
		return ERR_NON_CONFORME;
	}

// On change les parametres nouveaux
	TInterfaceConfiguration conf_courante = equip->GetInterfaceConfiguration(params[1]);
	
	conf_courante.type = params[2];
	conf_courante.electrical_characteristics = params[3];

	if (params[4] == "AUTO")
		conf_courante.transmission_baudrate = 0;
	else
		conf_courante.transmission_baudrate = atoi(params[4].c_str());

	if (params[5] == "AUTO")
		conf_courante.reception_baudrate = 0;
	else
		conf_courante.reception_baudrate = atoi(params[5].c_str());

	if (params[6] != "") conf_courante.direction = params[6];

	conf_courante.validity_time = params[7];
	conf_courante.binary_integrity = params[8];
	conf_courante.polarity = params[9];
	conf_courante.handshake = params[10];

	if (params[11] != "") conf_courante.character_length = atoi(params[11].c_str());
	if (params[12] != "") conf_courante.parity = params[12];
	if (params[13] != "") conf_courante.number_stop_bits = atoi(params[13].c_str());

	conf_courante.data_flow_control = params[14];

	equip->SetInterfaceConfiguration(params[1], conf_courante);

	SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::DIA(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 8
	string params[9];

	// La commande
	params[0] = "DIA";

	string reponse = ""; // utilisé en interne


// Chargement des paramètres
	for(int param_number = 1; param_number<9; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 8)
		{
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie aux interface configuration
	if (equip->ValidAuxInterfaceConfiguration(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAuxInterfaceConfigurationVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie si le data link est utilisé
	// Si le CI est associé à un data link (DX) et que ce data link correspond à une voie active
	if (equip->IsChannelFree(equip->GetChannelFromAuxInterfaceConfiguration(params[1])) == FALSE)
	{
		string reponse = params[1] + ";USED";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}


	// Verifie si l'interface est en panne PANNE
	if (equip->GetTest(params[1]) == TRUE)
	{
		string reponse = params[1] + ";PANNE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (equip->ValidAuxInterfaceConfigurationElectricalCharacteristic(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

// Parametre 3
	if (equip->ValidAuxInterfaceConfigurationBaudrate(params[3]) == FALSE)
	{
		SendNAC(&params[0], 3);
		return ERR_NON_CONFORME;
	}

// Parametre 4
	if (equip->ValidAuxInterfaceConfigurationCharacterLength(params[4]) == FALSE)
	{
		SendNAC(&params[0], 4);
		return ERR_NON_CONFORME;
	}

// Parametre 5
	if (equip->ValidAuxInterfaceConfigurationCharacterParity(params[5]) == FALSE)
	{
		SendNAC(&params[0], 5);
		return ERR_NON_CONFORME;
	}

// Parametre 6
	if (equip->ValidAuxInterfaceConfigurationNumberStopBit(params[6]) == FALSE)
	{
		SendNAC(&params[0], 6);
		return ERR_NON_CONFORME;
	}

// Parametre 7
	if (equip->ValidAuxInterfaceConfigurationRadioAddress(params[7]) == FALSE)
	{
		reponse = params[1] + ";ERR_AD_RAD";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 8
	if (equip->ValidAuxInterfaceConfigurationEquipmentType(params[1], params[8]) == FALSE)
	{
		reponse = params[1] + ";OTHER";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	TAuxInterfaceConfiguration aux_intf_conf = equip->GetAuxInterfaceConfiguration(params[1]);

	aux_intf_conf.electrical_characteristics = params[2];
	aux_intf_conf.baudrate = atoi(params[3].c_str());
	aux_intf_conf.character_length = atoi(params[4].c_str());
	aux_intf_conf.character_parity = params[5];
	aux_intf_conf.number_stop_bits = atoi(params[6].c_str());
	aux_intf_conf.radio_address = atoi(params[7].c_str());
	aux_intf_conf.equipment_type = params[8];

	equip->SetAuxInterfaceConfiguration(params[1], aux_intf_conf);

	SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::DTC(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 6
	string params[7];

	// La commande
	params[0] = "DTC";

	string reponse = ""; // utilisé en interne


// Chargement des paramètres
	for(int param_number = 1; param_number<7; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 6)
		{
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie local remote controle configuration
	if (equip->ValidLocalRemoteInterfaceConfiguration(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidLocalRemoteInterfaceConfigurationVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie si l'interface est en panne PANNE
	if (equip->GetTest(params[1]) == TRUE)
	{
		string reponse = params[1] + ";PANNE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (equip->ValidLocalRemoteInterfaceConfigurationElectricalCharacteristic(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

// Parametre 3
	if (equip->ValidLocalRemoteInterfaceConfigurationBaudrate(params[3]) == FALSE)
	{
		SendNAC(&params[0], 3);
		return ERR_NON_CONFORME;
	}

// Parametre 4
	if (equip->ValidLocalRemoteInterfaceConfigurationCharacterLength(params[4]) == FALSE)
	{
		SendNAC(&params[0], 4);
		return ERR_NON_CONFORME;
	}

// Parametre 5
	if (equip->ValidLocalRemoteInterfaceConfigurationCharacterParity(params[5]) == FALSE)
	{
		SendNAC(&params[0], 5);
		return ERR_NON_CONFORME;
	}

// Parametre 6
	if (equip->ValidLocalRemoteInterfaceConfigurationNumberStopBits(params[6]) == FALSE)
	{
		SendNAC(&params[0], 6);
		return ERR_NON_CONFORME;
	}

	TLocalRemoteInterfaceConfiguration local_remote_intf_conf = equip->GetLocalRemoteInterfaceConfiguration(params[1]);

	local_remote_intf_conf.electrical_characteristics = params[2];
	local_remote_intf_conf.baudrate = atoi(params[3].c_str());
	local_remote_intf_conf.characters_length = atoi(params[4].c_str());
	local_remote_intf_conf.characters_parity = params[5];
	local_remote_intf_conf.number_stop_bits = atoi(params[6].c_str());

	equip->SetLocalRemoteInterfaceConfiguration(params[1], local_remote_intf_conf);

	SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::DBF(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 9
	string params[10];

	// La commande
	params[0] = "DBF";

	string reponse = ""; // utilisé en interne


// Chargement des paramètres
	for(int param_number = 1; param_number<10; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 9)
		{
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie af channel configuration
	if (equip->ValidAfChannelConfiguration(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAfChannelConfigurationVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie si le data link est utilisé USED
	if (equip->IsChannelFree(equip->GetModemChannelFromAfChannel(params[1])) == FALSE)
	{
		string reponse = params[1] + ";USED";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie si l'interface est en panne PANNE
	if (equip->GetTest(params[1]) == TRUE)
	{
		string reponse = params[1] + ";PANNE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (equip->ValidAfChannelConfigurationInputLevel(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

// Parametre 3
	if (equip->ValidAfChannelConfigurationOutputLevel(params[3]) == FALSE)
	{
		SendNAC(&params[0], 3);
		return ERR_NON_CONFORME;
	}

// Parametre 4
	if (equip->ValidAfChannelConfigurationInterfaceType(params[4]) == FALSE)
	{
		SendNAC(&params[0], 4);
		return ERR_NON_CONFORME;
	}

// Parametre 5
	if (equip->ValidAfChannelConfigurationPttType(params[5]) == FALSE)
	{
		SendNAC(&params[0], 5);
		return ERR_NON_CONFORME;
	}

// Parametre 6
	if (equip->ValidAfChannelConfigurationPttTempo(params[6]) == FALSE)
	{
		SendNAC(&params[0], 6);
		return ERR_NON_CONFORME;
	}

// Parametre 7
	if (equip->ValidAfChannelConfigurationMuteSignal(params[7]) == FALSE)
	{
		SendNAC(&params[0], 7);
		return ERR_NON_CONFORME;
	}

// Parametre 8
	if (equip->ValidAfChannelConfigurationMuteDelay(params[8]) == FALSE)
	{
		SendNAC(&params[0], 8);
		return ERR_NON_CONFORME;
	}

// Parametre 9
	if (equip->ValidAfChannelConfigurationRadioDelay(params[9]) == FALSE)
	{
		SendNAC(&params[0], 9);
		return ERR_NON_CONFORME;
	}

	TAFChannelConfiguration af_channel_conf = equip->GetAfChannelConfiguration(params[1]);

	af_channel_conf.input_level = atoi(params[2].c_str());
	af_channel_conf.output_level = atoi(params[3].c_str());
	af_channel_conf.interface_type = params[4];
	af_channel_conf.ptt_type = params[5];
	af_channel_conf.ptt_tempo = atoi(params[6].c_str());
	af_channel_conf.mute_characteristics = params[7];
	af_channel_conf.mute_delay = atoi(params[8].c_str());
	af_channel_conf.radio_delay = atoi(params[9].c_str());

	equip->SetAfChannelConfiguration(params[1], af_channel_conf);

	SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::DDT(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[3];

	// La commande
	params[0] = "DDT";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	for(int param_number = 1; param_number<3; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 2)
		{
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

	// Test panne des 2 boards
	if (equip->GetTest("A1") == TRUE && equip->GetTest("A2") == TRUE)
	{
		if (equip->GetQuadrivoie() == FALSE)
		{
			reponse = "PANNE";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		} else
			if (equip->GetTest("B1") == TRUE && equip->GetTest("B2") == TRUE)
			{
				reponse = "PANNE";
				SendNAC(&params[0], &reponse);
				return ERR_NON_CONFORME;
			}
	}

// Parametre 1
	if (equip->ValidDateAndTime(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (equip->ValidTimeAccuracy(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	char heure[9];  
	char date[9];
	GetTimeFormat (LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT , NULL, "HH'H'mm'.'ss", (LPTSTR) heure, 9); 
	GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,NULL,"dd'/'MM'/'yy", date, 9);

	string date_heure = date;
	date_heure += ".";
	date_heure += heure;

	TBoard board = equip->GetBoard1();

	board.date_and_time = date_heure;
	board.last_date_and_time = date_heure;

	equip->SetBoard1(board);

	board = equip->GetBoard2();

	board.date_and_time = date_heure;
	board.last_date_and_time = date_heure;

	equip->SetBoard2(board);

	SendACK(&params[0], &reponse);

	reponse = "A1;" + params[2] + ";" + equip->GetBoard1().date_origin + ";" + params[1] + ";+30000";
	SendSignaling("DTU", &reponse);

	if (equip->GetQuadrivoie() == TRUE)
	{
		reponse = "B1;" + params[2] + ";" + equip->GetBoard2().date_origin + ";" + params[1] + ";-10000";
		SendSignaling("DTU", &reponse);
	}

	return 0;
}

int CProtoTRC1752::BFE(istringstream &trame, bool acq)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[3];

	// La commande
	params[0] = "BFE";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	for(int param_number = 1; param_number<3; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 2)
		{
			if (acq) SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	if (equip->ValidChannelId(params[1]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidChannelVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que le modem channel est actif
	if (equip->GetChannelState(params[1]) != "ACTIVE")
	{
		reponse = params[1] + ";INACTIVE";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}
	

	// Verifie que le modem channel n'est pas en reception seulement
	if (equip->GetChannelConfiguration(params[1]).direction == "RX")
	{
		reponse = params[1] + ";ERREUR_CONF";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Si A2 ou B2 verifie que le channel n'est pas en ALE
	if (equip->IsChannelAleReserved(params[1]) == TRUE)
	{
		reponse = params[1] + ";USED";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (equip->ValidAfChannelConfigurationOutputLevel(params[2]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	string af_id = equip->GetAfChannelFromModemChannel(params[1]);

	TAFChannelConfiguration af_channel = equip->GetAfChannelConfiguration(af_id);

	af_channel.output_level = atoi(params[2].c_str());

	equip->SetAfChannelConfiguration(af_id, af_channel);

	if (acq) SendACK(&params[0], &params[1]);

	reponse = params[1] + ";" + params[2];

	SendSignaling("TBF", &reponse);

	return 0;
}

int CProtoTRC1752::AUT(istringstream &trame)
{
	// La commande
	string cmd = "AUT";

	string test = "";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	if(!getline(trame, test, ';'))
	{
		SendNAC(&cmd, 1);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	if (equip->ValidTestProgress(test) == FALSE)
	{
		SendNAC(&cmd, 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidTestProgressVersion(test) == FALSE)
	{
		reponse = test + ";VERSION";
		SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que la voie n'est pas active sinon on casse les services
	if(test == "CARTE_A" || test == "TIROIR")
	{
		if (equip->GetChannelState("A1") == "ACTIVE")
			equip->DesactiveVoie("A1");
		if (equip->GetChannelState("A2") == "ACTIVE")
			equip->DesactiveVoie("A2");
	}

	if (test == "CARTE_B"  || test == "TIROIR")
	{
		if (equip->GetChannelState("B1") == "ACTIVE")
			equip->DesactiveVoie("B1");
		if (equip->GetChannelState("B2") == "ACTIVE")
			equip->DesactiveVoie("B2");
	}

	equip->SetTestProgress(test);

	SendACK(&cmd, &test);

	reponse = test + ";EN_COURS";

	SendSignaling("AUT", &reponse);

	return 0;
}

void CProtoTRC1752::SignalAUT()
{
	string reponse = "";
	string result = "OK";

	string test = equip->GetTestProgress();

	if (test == "TIROIR" || test == "CARTE_A")
		if (equip->GetTest("A1") == TRUE)
		{
			reponse += "A1";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("A1", TRUE);
		}

	reponse += ";";

	if (test == "TIROIR" || test == "CARTE_A")
		if (equip->GetTest("A2") == TRUE)
		{
			reponse += "A2";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("A2", TRUE);
		}

	reponse += ";";

	if (equip->GetQuadrivoie() == TRUE)
	{
	if (test == "TIROIR" || test == "CARTE_B")
		if (equip->GetTest("B1") == TRUE)
		{
			reponse += "B1";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("B1", TRUE);
		}
	}

	reponse += ";";

	if (equip->GetQuadrivoie() == TRUE)
	{
	if (test == "TIROIR" || test == "CARTE_B")
		if (equip->GetTest("B2") == TRUE)
		{
			reponse += "B2";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("B2", TRUE);
		}
	}

	reponse += ";";

	if (test == "TIROIR")
		if (equip->GetTest("TC") == TRUE)
		{
			reponse += "TC";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("TC", TRUE);
		}

	reponse += ";";

	if (test == "TIROIR" || test == "CARTE_A")
		if (equip->GetTest("D1") == TRUE)
		{
			reponse += "D1";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("D1", TRUE);
		}

	reponse += ";";

	if (test == "TIROIR" || test == "CARTE_A")
		if (equip->GetTest("D2") == TRUE)
		{
			reponse += "D2";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("D2", TRUE);
		}

	reponse += ";";

	if (test == "TIROIR")
		if (equip->GetTest("D3") == TRUE)
		{
			reponse += "D3";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("D3", TRUE);
		}

	reponse += ";";

	if (test == "TIROIR")
		if (equip->GetTest("D4") == TRUE)
		{
			reponse += "D4";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("D4", TRUE);
		}

	reponse += ";";

	if (test == "TIROIR" || test == "CARTE_B")
		if (equip->GetTest("D5") == TRUE)
		{
			reponse += "D5";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("D5", TRUE);
		}

	reponse += ";";

	if (test == "TIROIR" || test == "CARTE_B")
		if (equip->GetTest("D6") == TRUE)
		{
			reponse += "D6";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("D6", TRUE);
		}

	reponse += ";";

	if (test == "TIROIR")
		if (equip->GetTest("D7") == TRUE)
		{
			reponse += "D7";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("D7", TRUE);
		}

	reponse += ";";

	if (test == "TIROIR")
		if (equip->GetTest("D8") == TRUE)
		{
			reponse += "D8";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("D8", TRUE);
		}

	reponse += ";";

	if (test == "TIROIR" || test == "CARTE_A")
		if (equip->GetTest("IA3") == TRUE)
		{
			reponse += "IA3";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("IA3", TRUE);
		}

	reponse += ";";

	if (test == "TIROIR" || test == "CARTE_A")
		if (equip->GetTest("IA4") == TRUE)
		{
			reponse += "IA4";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("IA4", TRUE);
		}

	reponse += ";";

	if (equip->GetQuadrivoie() == TRUE)
	{
	if (test == "TIROIR" || test == "CARTE_B")
		if (equip->GetTest("IA5") == TRUE)
		{
			reponse += "IA5";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("IA5", TRUE);
		}
	}

	reponse += ";";

	if (equip->GetQuadrivoie() == TRUE)
	{
	if (test == "TIROIR" || test == "CARTE_B")
		if (equip->GetTest("IA6") == TRUE)
		{
			reponse += "IA6";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("IA6", TRUE);
		}
	}

	reponse += ";";

	if (test == "TIROIR")
		if (equip->GetTest("EEPROM") == TRUE)
		{
			reponse += "PANNE_EEPROM";
			result = "NOK";
			// FFT ADEL_97569
			equip->SetTest("EEPROM", TRUE);
		}

	reponse += ";;";

	reponse.insert(0, test + ";" + result + ";");

	SendSignaling("AUT", &reponse);
}

int CProtoTRC1752::TES(istringstream &trame, bool acq)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[3];

	// La commande
	params[0] = "TES";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	for(int param_number = 1; param_number<3; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 2)
		{
			if (acq) SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidChannelId(params[1]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidChannelVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que le channel est ok
	if (equip->GetTest(params[1]) == TRUE)
	{
		reponse = params[1] + ";PANNE";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Une seule voie peut etre en test
	for (int i=0; i<NB_CHANNELS; i++)
		if (equip->GetChannelTest(CHANNELS[i]) != DEFAULT_STRING_VALUE)
		{
			reponse = params[1] + ";OTHER";
			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

	// Si la voie etait active on casse tout
	equip->DesactiveVoie(params[1]);

// Parametre 2
	// Verifie que le test est ok
	if (equip->ValidChannelTest(params[2]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	equip->SetChannelTest(params[1], params[2]);

	if (acq) SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::STE(istringstream &trame, bool acq)
{
	// La commande
	string cmd = "STE";

	string id = "";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	if(!getline(trame, id, ';'))
	{
		if (acq) SendNAC(&cmd, 1);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidChannelId(id) == FALSE)
	{
		if (acq) SendNAC(&cmd, 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidChannelVersion(id) == FALSE)
	{
		reponse = id + ";VERSION";
		if (acq) SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que le channel est ok
	if (equip->GetTest(id) == TRUE)
	{
		reponse = id + ";PANNE";
		if (acq) SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que le channel est en test
	if (equip->GetChannelTest(id) != "1800HZ" && equip->GetChannelTest(id) != "BOUCLE_BF")
	{
		reponse = id + ";OTHER";
		if (acq) SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	equip->SetChannelTest(id, "");

	if (acq) SendACK(&cmd, &id);

	//SendSignaling("TDA", &id);

	return 0;
}

int CProtoTRC1752::TLS(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[3];

	// La commande
	params[0] = "TLS";

	string reponse = ""; // utilisé en interne
	bool result;

	// Chargement des paramètres
	for(int param_number = 1; param_number<3; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 2)
		{
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie le link id
	if ((equip->ValidDataLinkId(params[1]) == FALSE) && (equip->ValidAuxInterfaceConfiguration(params[1]) == FALSE)
		&& params[1] != "D3" && params[1] != "D4" && params[1] != "D7" && params[1] != "D8")
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Suivant le link id
	if (params[1][0] == 'D')
	{
		// Verifie la version
		if (equip->ValidDataLinkVersion(params[1]) == FALSE)
		{
			reponse = params[1] + ";VERSION";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		// Verifie que le channel est ok
		if (equip->GetTest(equip->GetChannelFromDataLink(params[1])) == TRUE)
		{
			reponse = params[1] + ";PANNE";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		// Verifie que le modem channel n'est pas actif
		if (equip->GetChannelState(equip->GetChannelFromDataLink(params[1])) == "ACTIVE")
		{
			reponse = params[1] + ";USED";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		result = equip->GetTest(params[1]);
	} 
	else
	{
		// Verifie la version
		if (equip->ValidAuxInterfaceConfigurationVersion(params[1]) == FALSE)
		{
			reponse = params[1] + ";VERSION";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		// Verifie que le channel est ok
		if (equip->GetTest(equip->GetChannelFromAuxInterfaceConfiguration(params[1])) == TRUE)
		{
			reponse = params[1] + ";PANNE";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		// Verifie que le modem channel n'est pas actif
		if (equip->GetChannelState(equip->GetChannelFromAuxInterfaceConfiguration(params[1])) == "ACTIVE")
		{
			reponse = params[1] + ";USED";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}
		
		result = equip->GetTest(params[1]);
	} 

// Parametre 2
	if (params[2] != "INTERNE" && params[2] != "EXTERNE")
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	if (result == TRUE)
	{
		reponse = params[1] + ";NOK;";

		string error[4] = {"103-104","105-106","107-108","113-114"};

		for(int i = 0; i<4; i++)
		{
			if (equip->GetTest(error[i]) == TRUE) reponse += error[i];
			reponse += ";";
		}

		reponse.erase(reponse.length()-1, 1);
	} else
		reponse = params[1] + ";OK;;;;";

	SendACK(&params[0], &reponse);

	return 0;
}

int CProtoTRC1752::ACT(istringstream &trame, bool acq)
{
	int param_number;

	// Les paramètres commencent à 1 et finissent à 8
	string params[9];
	bool surac = FALSE;

	// La commande
	params[0] = "ACT";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	for(param_number = 1; param_number<9; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 8)
		{
			if (acq) SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie l'id channel
	if (equip->ValidChannelId(params[1]) == FALSE)
	{
		if (acq) SendNAC(&params[0], param_number);
		return ERR_NON_CONFORME;
	}

	// Verifie que le channel est possible dans la version courante
	if (equip->ValidChannelVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que le channel est en etat
	if (equip->GetTest(params[1]) == TRUE)
	{
		reponse = params[1] + ";PANNE;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	// doit etre MC si piloté par le pc arq

	// Verifie interface configuration
	if (equip->ValidChannelConfiguration(params[2]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	// FFT_1390
	//string toto = equip->GetChannelLocalRemoteControl(params[1]);
	if (params[2] == "MC" && equip->GetChannelLocalRemoteControl(params[1]) != "LOCAL")
	{
		if (acq) SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	// Récupération de la conf du channel
	TChannelConfiguration channel_conf;
	
	if (params[2] == "MC")
		channel_conf = equip->GetChannelConfiguration(params[1]);
	else
		channel_conf = equip->GetChannelConfiguration(params[2]);

// Parametre 3
	// Verifie que le data link est valide
	if (equip->ValidChannelDataLinkId(params[3]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 3);
		return ERR_NON_CONFORME;
	}

	// Le data link doit correspondre à la voie
	if ((params[3] == "D1" && params[1] != "A1")
	||  (params[3] == "D2" && params[1] != "A2")
	||  (params[3] == "D5" && params[1] != "B1")
	||  (params[3] == "D6" && params[1] != "B2"))
	{
		reponse = params[1] + ";ASSOCIATION_INCORRECTE;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Récupération de la conf de l'interface associée
	string interface_id = equip->GetDataLinkAssociatedConfiguration(params[3]);
	TInterfaceConfiguration interface_conf = equip->GetInterfaceConfiguration(interface_id);


// Parametre 4
	// Verifie que le type est valide
	if (equip->ValidChannelType(params[4]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 4);
		return ERR_NON_CONFORME;
	}

// Parametre 5
	// Inutile si en non ale
	if (params[4] != "-") 
	{
		// Verifie l'index
		if (equip->ValidChannelIndexScansetChannel(atoi(params[5].c_str())) == FALSE)
		{
			if (acq) SendNAC(&params[0], 5);
			return ERR_NON_CONFORME;
		}

	}

// Parametre 8
	if (equip->ValidChannelLinkManagementType(params[8]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 8);
		return ERR_NON_CONFORME;
	}


// Erreurs

	// En ALE seul A1 et B1 sont utilisables
	if (params[4] != "-" && params[1] != "A1" && params[1] != "B1")
	{
		reponse = params[1] + ";ASSOCIATION_INCORRECTE;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// En ALE, la deuxieme voie doit etre libre (T2-54)
	// Mais si elle ne l'est pas il faut vérifier que la premiere n'est active elle aussi.
	// On se retrouve dans un cas de suractivation
	if (params[4] != "-")
	{
		if ((params[1] == "A1" && equip->GetChannelState("A1") == "ACTIVE" && equip->IsLink("A1"))
			|| (params[1] == "B1" && equip->GetChannelState("B1") == "ACTIVE" && equip->IsLink("B1")))
				surac = TRUE;

		if (   (params[1] == "A1" && equip->GetChannelState("A1") != "ACTIVE" && equip->IsChannelFree("A2") == FALSE)
			|| (params[1] == "B1" && equip->GetChannelState("B1") != "ACTIVE" && equip->IsChannelFree("B2") == FALSE) )
		{
			reponse = params[1] + ";USED;";

			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}
	}

	//***********************************************************************
	// MAE - page 82/124 - Interface TD
	// Correction pour V3.0.1
	if (params[4] == "-" )
	{
		if ( params[1] == "A1"
			&& ( ( equip->GetChannelState("A2") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A1")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A2")))
			|| ( equip->GetChannelState("B1") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A1")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B1")))
			|| ( equip->GetChannelState("B2") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A1")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B2")))
			))
		{
			reponse = params[1] + ";USED;";

			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		if ( params[1] == "A2"
			&& ( ( equip->GetChannelState("A1") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A2")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A1")))
			|| ( equip->GetChannelState("B1") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A2")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B1")))
			|| ( equip->GetChannelState("B2") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A2")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B2")))
			))
		{
			reponse = params[1] + ";USED;";

			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		if ( params[1] == "B1"
			&& ( ( equip->GetChannelState("A1") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B1")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A1")))
			|| ( equip->GetChannelState("A2") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B1")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A2")))
			|| ( equip->GetChannelState("B2") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B1")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B2")))
			))
		{
			reponse = params[1] + ";USED;";

			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		if ( params[1] == "B2"
			&& ( ( equip->GetChannelState("A1") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B2")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A1")))
			|| ( equip->GetChannelState("A2") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B2")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("A2")))
			|| ( equip->GetChannelState("B1") == "ACTIVE"
			&& equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B2")) == equip->GetDataLinkAssociatedConfiguration(equip->GetChannelDataLinkId("B1")))
			))
		{
			reponse = params[1] + ";USED;";

			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

	}
	
	//*************************************************************************

	// En diversite, la deuxieme voie doit etre libre (T2-54)
	if (channel_conf.diversity == "AVEC")
	{
		if (   (params[1] == "A1" && equip->IsChannelFree("A2") == FALSE)
			|| (params[1] == "A2" && equip->IsChannelFree("A1") == FALSE)
			|| (params[1] == "B1" && equip->IsChannelFree("B2") == FALSE)
			|| (params[1] == "B2" && equip->IsChannelFree("B1") == FALSE) )
		{
			reponse = params[1] + ";USED;";

			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

	}

	// En 4285, 4529 et mil110 la conf du datalink doit etre differente de asynchrone inversee (T2-54)
	if (channel_conf.waveform == "4285" || channel_conf.waveform == "4529" || channel_conf.waveform == "MIL110")
	{
		if (interface_conf.polarity == "INVERSEE" && interface_conf.type == "ASYNCHRONE")
		{
			reponse = params[1] + ";ASSOCIATION_INCORRECTE;";

			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}
	}

	// En ale la conf de la forme d'onde doit etre differente de repos (T2-54)
	if (channel_conf.waveform == "REPOS" && params[4] != "-")
	{
		reponse = params[1] + ";ASSOCIATION_INCORRECTE;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Pas de scanset ou channel en BFSK (T2-55)
	if (channel_conf.waveform == "BFSK" && (params[4] == "S" || params[4] == "C"))
	{
		reponse = params[1] + ";ASSOCIATION_INCORRECTE;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Pas de scanset ou channel en 4529 (T2-55)
	if (channel_conf.waveform == "4529" && (params[4] == "S" || params[4] == "C"))
	{
		reponse = params[1] + ";ASSOCIATION_INCORRECTE;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Pas de scanset ou channel en diversite (T2-55)
	if (channel_conf.diversity == "AVEC" && (params[4] == "S" || params[4] == "C"))
	{
		reponse = params[1] + ";ASSOCIATION_INCORRECTE;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Pas de lauto avec une conf d'interface dont le handshake est à off (T2-55)
	if (interface_conf.handshake == "OFF" && params[8] == "LAUTO") 
	{
		reponse = params[1] + ";ASSOCIATION_INCORRECTE;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Si le channel est en HD, on force le passage en DPE (82)
	if (channel_conf.direction == "HD")
	{
		interface_conf.handshake = "DPE";
		reponse = params[1] + ";ACTIVATION_DPE";
		if (acq) SendSignaling("COA", &reponse);
	}

	// Si on est en sans DPE et pas en emission seule (T2-55)
	if (interface_conf.handshake == "OFF" && channel_conf.direction != "TX")
	{
		reponse = params[1] + ";OTHER;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Si le data link est INT (test PN511) le channel doit etre en TX (82) et sans ale (T2-54)
	if (params[3] == "INT" && (channel_conf.direction != "TX" || params[4] != "-"))
	{
		reponse = params[1] + ";USED;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Vérification cohérences débits

	// Si la liaison est synchrone, les debits doivent être les mêmes, sinon le débit du channel est prioritaire (81)
	if (interface_conf.type == "SYNCHRONE")
	{
		if (interface_conf.transmission_baudrate != channel_conf.af_transmission_baudrate)
		{
			interface_conf.transmission_baudrate = channel_conf.af_transmission_baudrate;
			reponse = params[1] + ";L_SYNCHRONE";
			if (acq) SendSignaling("COA", &reponse);
		}
		if (interface_conf.reception_baudrate != channel_conf.af_reception_baudrate)
		{
			interface_conf.reception_baudrate = channel_conf.af_reception_baudrate;
			reponse = params[1] + ";L_SYNCHRONE";
			if (acq) SendSignaling("COA", &reponse);
		}
	}

	//Si la liaison est asynchrone
	if (interface_conf.type == "ASYNCHRONE")
	{
		// si le débit interface est < au debit channel, le debit channel est abaissé (81)
		// sauf si le débit de l'interface est 50,100,200,800 (en bfsk il n'y a que 800 interdit) (T2-55)
		if (interface_conf.transmission_baudrate < channel_conf.af_transmission_baudrate)
		{
			if ( ((interface_conf.transmission_baudrate == 50
					|| interface_conf.transmission_baudrate == 100
					|| interface_conf.transmission_baudrate == 200) 
						&& channel_conf.waveform != "BFSK")
				|| interface_conf.transmission_baudrate == 800)
			{
				reponse = params[1] + ";DEBIT_LS_A_CORRIGER;";

				if (acq) SendNAC(&params[0], &reponse);
				return ERR_NON_CONFORME;
			}
			else
			{
				channel_conf.af_transmission_baudrate = interface_conf.transmission_baudrate;
				reponse = params[1] + ";BAISSE_DEB_RADIO";
				if (acq) SendSignaling("COA", &reponse);
			}
		}

		if (interface_conf.reception_baudrate < channel_conf.af_reception_baudrate)
		{
			if ( ((interface_conf.reception_baudrate == 50
					|| interface_conf.reception_baudrate == 100
					|| interface_conf.reception_baudrate == 200) 
						&& channel_conf.waveform != "BFSK")
				|| interface_conf.reception_baudrate == 800)
			{
				reponse = params[1] + ";DEBIT_LS_A_CORRIGER;";

				if (acq) SendNAC(&params[0], &reponse);
				return ERR_NON_CONFORME;
			}
			else
			{
				channel_conf.af_reception_baudrate = interface_conf.reception_baudrate;
				reponse = params[1] + ";BAISSE_DEB_RADIO";
				if (acq) SendSignaling("COA", &reponse);
			}
		}

		// si le débit interface est > au débit channel il y a PAE (82)
		if (interface_conf.transmission_baudrate > channel_conf.af_transmission_baudrate)
		{
			reponse = params[1] + ";ACTIVATION_CTL_FLUX";
			if (acq) SendSignaling("COA", &reponse);
		}
		if (interface_conf.reception_baudrate > channel_conf.af_reception_baudrate)
		{
			reponse = params[1] + ";ACTIVATION_CTL_FLUX";
			if (acq) SendSignaling("COA", &reponse);
		}
	}

	// Coherence des tables en ALE
	if(params[4] != "-")
	{
		// On verifie la presence de la table SAD, STA, RCH
		if (equip->IsRchPresent(params[1]) == FALSE)
		{
			reponse = params[1] + ";RCH;";

			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		if (equip->IsSadPresent(params[1]) == FALSE)
		{
			reponse = params[1] + ";SAD;";

			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		} else if (equip->ValidTableSad(params[1]) == FALSE)
		{
			reponse = params[1] + ";SAD;";

			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		if (equip->IsStaPresent(params[1]) == FALSE)
		{
			reponse = params[1] + ";STA;";

			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		} else if (equip->ValidTableSta(params[1]) == FALSE)
		{
			reponse = params[1] + ";STA;";

			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}
		
	
		// Si on est en NET on verifie la presence de la table NET
		if (equip->GetAleParameter(params[1]).call_type == "NET")
		{
			if (equip->IsNetPresent(params[1]) == FALSE)
			{
				reponse = params[1] + ";NET;";

				if (acq) SendNAC(&params[0], &reponse);
				return ERR_NON_CONFORME;
			} else if (equip->ValidTableNet(params[1]) == FALSE)
			{
				reponse = params[1] + ";NET;";

				if (acq) SendNAC(&params[0], &reponse);
				return ERR_NON_CONFORME;
			}
		}

		// Si on est en scanset, vérifier le scanset
		if (params[4] == "S")
		{
			
			// On verifie la presence de la table SST
			if (equip->IsSstPresent(params[1]) == FALSE)
			{
				reponse = params[1] + ";SST;";

				if (acq) SendNAC(&params[0], &reponse);
				return ERR_NON_CONFORME;
			} else if (equip->ValidTableSst(params[1]) == FALSE)
			{
				reponse = params[1] + ";SST;";

				if (acq) SendNAC(&params[0], &reponse);
				return ERR_NON_CONFORME;
			}
			
			// On verifie la presence de l'index dans la table SST
			if (equip->IsSstPresent(params[1], atoi(params[5].c_str())) == FALSE)
			{
				reponse = params[1] + ";OTHER;" + params[5];

				if (acq) SendNAC(&params[0], &reponse);
				return ERR_NON_CONFORME;
			}

		}
		// Si on est en channel, vérifier el canal
		else
		{
			// On verifie la presence de l'index dans RCH
			if (equip->IsRchPresent(params[1], atoi(params[5].c_str())) == FALSE)
			{
				reponse = params[1] + ";OTHER;" + params[5];

				if (acq) SendNAC(&params[0], &reponse);
				return ERR_NON_CONFORME;
			}
		}
	}

	// Si on est en ale on verifie la presence du recepteur
	if (params[4] != "-")
	{
		if (equip->IsRecepteurMarche() == FALSE || equip->IsRecepteurPanneTC() == TRUE)
		{
			if (params[1] == "A1")
				if (acq) SignalRAD("IA4", "RNR", TRUE);
			else if (params[1] == "B1")
				   if (acq) SignalRAD("IA6", "RNR", TRUE);
			
			reponse = reponse = params[1] + ";OTHER;";
			if (acq) SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}
	}

	// Si on est en ale et sur le channel esclave on refuse
	if (equip->IsChannelReserve(params[1]) == TRUE)
	{
		reponse = params[1] + ";USED;";

		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}


	// En diversite on recopie la conf du channel ds l'esclave

	// On refait l'association
	equip->SetChannelAssociatedAfConfiguration(params[1], params[2]);
	equip->SetChannelDataLinkId(params[1], params[3]);
	equip->SetChannelType(params[1], params[4]);
	if (params[4] != "-")
		equip->SetChannelIndexScansetChannel(params[1], atoi(params[5].c_str()));
	equip->SetChannelLinkManagementType(params[1], params[8]);

	// On reconfigure le channel et l'interface au cas ou il y ait eu retouche
	if (params[2] == "MC")
		equip->SetChannelConfiguration(params[1], channel_conf);
	else
		equip->SetChannelConfiguration(params[2], channel_conf);

	equip->SetInterfaceConfiguration(interface_id, interface_conf);

	// En ale/diversité, on configure la voie associée/esclave
	if (params[4] != "-" || channel_conf.diversity == "AVEC")
	{
		equip->SetChannelAssociatedAfConfiguration(equip->GetChannelAssociated(params[1]), params[2]);
		equip->SetChannelType(equip->GetChannelAssociated(params[1]), params[4]);
		if (params[4] != "-")
			equip->SetChannelIndexScansetChannel(equip->GetChannelAssociated(params[1]), atoi(params[5].c_str()));
		equip->SetChannelLinkManagementType(equip->GetChannelAssociated(params[1]), params[8]);
		equip->SetChannelReserve(equip->GetChannelAssociated(params[1]), TRUE);
	}

	if (acq) SendACK(&params[0], &params[1]);

	// On passe a active
	equip->SetChannelState(params[1], "ACTIVE");

	// FDI - 201202
	// On supprime la panne des TC des équipement radio
	equip->SetEmetteurPanneTC(FALSE);
	equip->SetRecepteurPanneTC(FALSE);

	// On supprime la panne majeur des équipement radio
	equip->SetEmetteurPanneMajeure(FALSE);
	equip->SetRecepteurPanneMajeure(FALSE);
	// FDI

	// On passe l'autre voie aussi a active en ale/diversité
	if (params[4] != "-")
		equip->SetChannelState(equip->GetChannelAssociated(params[1]), "ACTIVE");
	else if (channel_conf.diversity == "AVEC")
	{
		equip->SetChannelState(equip->GetChannelAssociated(params[1]), "ACTIVE");
		equip->SetChannelMasterDiversity(params[1], TRUE);
		equip->SetChannelMasterDiversity(equip->GetChannelAssociated(params[1]), FALSE);
	}

	reponse = params[1] + ";" + params[2] + ";" + params[3] + ";" + params[4] + ";" + params[5] + ";"
		+ params[6] + ";" + params[7] + ";" + params[8];

	if (acq) SendSignaling("TAC", &reponse);

	// En ale le status change en fonction du mode ale
	// Fait dans le thread
	

	if (params[4] != "-" && !surac )		//if (params[4] != "-" && !surac)
	{
		equip->CreerAppel(params[1]);
	}

	return 0;
}

int CProtoTRC1752::DAC(istringstream &trame, bool acq)
{
	// La commande
	string cmd = "DAC";

	string id = "";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	if(!getline(trame, id, ';'))
	{
		if (acq) SendNAC(&cmd, 1);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidChannelId(id) == FALSE)
	{
		if (acq) SendNAC(&cmd, 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidChannelVersion(id) == FALSE)
	{
		reponse = id + ";VERSION";
		if (acq) SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// On remplace par le test sur le reserve
	if (equip->IsChannelReserve(id) == TRUE)
	{
		if (acq) SendNAC(&cmd, &id);
		return ERR_NON_CONFORME;
	}

	if (acq) SendACK(&cmd, &id);

	equip->DesactiveVoie(id);

	// FDI - 201202
	// On supprime la panne des TC des équipement radio
	equip->SetEmetteurPanneTC(FALSE);
	equip->SetRecepteurPanneTC(FALSE);

	// On supprime la panne majeur des équipement radio
	equip->SetEmetteurPanneMajeure(FALSE);
	equip->SetRecepteurPanneMajeure(FALSE);
	// FDI

	return 0;
}

int CProtoTRC1752::ZTS(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[3];

	// La commande
	params[0] = "ZTS";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	for(int param_number = 1; param_number<3; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 2)
		{
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	if (equip->ValidInr(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (equip->ValidInrRate(atoi(params[2].c_str())) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	equip->SetInr(params[1]);
	equip->SetInrRate(atoi(params[2].c_str()));

	SendACK(&params[0], &reponse);

	return 0;
}

void CProtoTRC1752::SignalINR()
{
	// FDI - ZTS
	if (equip->GetZtsPft() == false)
		return;

	string reponse = "";
	TChannelConfiguration conf;

	// On envoi ce signal pour les voies qui sont actives
	for(int i=0; i<NB_CHANNELS; i++)
		if (equip->GetChannelState(CHANNELS[i]) == "ACTIVE")
		{
			conf = equip->GetChannelConfiguration(equip->GetChannelAssociatedAfConfiguration(CHANNELS[i]));
			if (conf.direction == "TX") continue;

			// En 4285, 4529, MIL110 ou BFSK
			if (conf.waveform != "4285" && conf.waveform != "4529" && conf.waveform != "MIL110" && conf.waveform != "BFSK")
				continue;

			reponse = CHANNELS[i] + ";";

			if (conf.waveform != "BKSK")
				reponse += IntToString(equip->GetChannelQualityValue(CHANNELS[i]), 2);

			reponse += ";" + IntToString(equip->GetChannelAfLevelReceived(CHANNELS[i]), 2, TRUE) + ";"
				+ IntToString(equip->GetChannelDopplerOffset(CHANNELS[i]), 3, TRUE) + ";";

			if (conf.waveform != "BKSK")
			{
				string temp = IntToString(equip->GetChannelSignalNoiseRation(CHANNELS[i]), 2, TRUE);

				// Pas de signe + ...
				if (temp[0] == '+')
					reponse += temp.substr(1, temp.length());
				else
					reponse += temp;
			}

			SendSignaling("INR", &reponse);
		}

}

void CProtoTRC1752::SignalPAO(const string channel, const string direction)
{
	string reponse = "";

	// Récupération du nom de la configuration associée à la voie (channel)
	//string value = equip->GetChannelAssociatedAfConfiguration(channel);
	
	// Conversion
	//int nrConf = static_cast<int>(value[1]) - 65;

	// Récupération des paramètres de la configuration
	TChannelConfiguration conf = equip->GetChannelConfiguration(channel);
	//TChannelConfiguration conf = equip->GetChannelConfiguration(CHANNELS_CONFIGURATION[nrConf]);

	//string direction = equip->GetChannelDirectionTransmission(channel);

	// FDI - 2012
	TPCArq arq = equip->GetPcArq(channel);

	reponse = channel + ";" + direction + ";";


	if (direction == "EMISSION")
		reponse += IntToString(conf.af_transmission_baudrate, 4) + ";" + conf.af_transmission_codingtype + ";" + conf.af_transmission_interleaving;

	/*
	if (direction == "RECEPTION" && equip->GetChannelAfLevelReceived(channel) >= -10)
		reponse += IntToString(conf.af_reception_baudrate, 4) + ";" + conf.af_reception_codingtype + ";" + conf.af_reception_interleaving;
		*/

	/*
	if (direction == "EMISSION")
		reponse += IntToString(conf.af_transmission_baudrate, 4) + ";" + conf.af_transmission_codingtype + ";" + conf.af_transmission_interleaving;
	else if (conf.waveform != "MIL110" && arq.arqdebrec != TRUE)
			reponse += IntToString(conf.af_reception_baudrate, 4) + ";" + conf.af_reception_codingtype + ";" + conf.af_reception_interleaving;
		else if(arq.arqdebrec != TRUE)
			reponse += IntToString(1200, 4) + ";" + conf.af_reception_codingtype + ";" + conf.af_reception_interleaving;
	*/

	
	// FDI - RecMil
	if (direction == "RECEPTION" && equip->GetRecMil() && equip->GetChannelAfLevelReceived(channel) >= -10)
	{
		reponse += IntToString(1200, 4) + ";" + conf.af_reception_codingtype + ";LONG";
	}
	else
	{
		reponse += IntToString(conf.af_reception_baudrate, 4) + ";" + conf.af_reception_codingtype + ";" + conf.af_reception_interleaving;
	}

	/*	
	if (arq.arqdebrec != TRUE) 
		SendSignaling("PAO", &reponse);

	// FDI - 2012
	if (arq.arqdebrec == TRUE && equip->GetChannelAfLevelReceived(channel) >= -10 && direction == "RECEPTION")
	{
		//conf = equip->GetChannelConfiguration(channel);
		reponse = "";
		reponse = channel + ";" + direction + ";";
		reponse += IntToString(conf.af_transmission_baudrate, 4) + ";" + conf.af_transmission_codingtype + ";" + conf.af_transmission_interleaving;
		SendSignaling("PAO", &reponse);
	}
	*/

	
	SendSignaling("PAO", &reponse);
}

int CProtoTRC1752::MDV(istringstream &trame, bool acq)
{
	// Les paramètres commencent à 1 et finissent à 5
	string params[6];

	// La commande
	params[0] = "MDV";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	for(int param_number = 1; param_number<6; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 5)
		{
			if (acq) SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidChannelId(params[1]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidChannelVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (equip->ValidChannelDirectionTransmission(params[2]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}	
	
// Parametre 3/4/5
	string coding = params[4];
	string interleaving = params[5];
	TChannelConfiguration conf = equip->GetChannelConfiguration(params[1]);

	if (params[2] == "EMISSION") 
	{
		if (params[4] == "") coding = conf.af_transmission_codingtype;
		if (params[5] == "") interleaving = conf.af_transmission_interleaving;
	} else
	{
		if (params[4] == "") coding = conf.af_reception_codingtype;
		if (params[5] == "") interleaving = conf.af_reception_interleaving;
	}


	int result = equip->ValidChannelConfigurationAfParameters(conf.waveform, params[3], coding, interleaving, params[2] == "EMISSION" ? FALSE : TRUE);
		
	switch (result)
	{
	case 0: 
		break;
	case 1: 
		reponse = params[0] + ";DATA_RATE_ERROR";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	case 2:
		reponse = params[0] + ";CODING_ERROR";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	case 3:
		reponse = params[0] + ";INTERLEAVING_ERROR";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	default:
		break;
	}

// Verification suppl
	// Le channel doit etre actif et pas en diversité
	if (equip->GetChannelState(params[1]) != "ACTIVE" || conf.diversity == "AVEC")
	{
		reponse = params[0] + ";STATE_ERROR";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Pas possible en EMISSION si channel configuré en RX (idem pour la RECEPTION + TX)
	if (   (params[2] == "EMISSION" && conf.direction == "RX")
		|| (params[2] == "RECEPTION" && conf.direction == "TX"))
	{
		reponse = params[0] + ";STATE_ERROR";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Pas possible si en SYNCHRONE et 
	TInterfaceConfiguration iconf = equip->GetInterfaceConfiguration(equip->GetChannelAssociatedAfConfiguration(params[1]));
	if (iconf.type == "SYNCHRONE" && iconf.direction != "SORTANTE")
	{
		reponse = params[0] + ";STATE_ERROR";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Sauve les valeurs
	if (params[2] == "EMISSION")
	{
		conf.af_transmission_baudrate = atoi(params[3].c_str());
		conf.af_transmission_codingtype = coding;
		conf.af_transmission_interleaving = interleaving;
	} else
	{
		conf.af_reception_baudrate = atoi(params[3].c_str());
		conf.af_reception_codingtype = coding;
		conf.af_reception_interleaving = interleaving;
	}

	equip->SetChannelConfiguration(params[1], conf);
	
	if (acq) SendACK(&params[0], &params[1]);

	// Envoi du signal PAO
	SignalPAO(params[1], params[2]);

	return 0;
}

int CProtoTRC1752::POR(istringstream &trame, bool acq)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[3];

	// La commande
	params[0] = "POR";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	for(int param_number = 1; param_number<3; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 2)
		{
			if (acq) SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidChannelId(params[1]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidChannelVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (equip->ValidChannelOffsetCarrierFrequency(params[2]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}	

// Verif suppl
	// La voie doit etre active
	if (equip->GetChannelState(params[1]) != "ACTIVE")
	{
		reponse = params[1] + ";INACTIVE";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	TChannelConfiguration conf = equip->GetChannelConfiguration(equip->GetChannelAssociatedAfConfiguration(params[1]));

	// Le channel ne doit pas etre en TX et doit etre en BFSK
	if (conf.direction == "TX" || conf.waveform != "BFSK")
	{
		reponse = params[1] + ";ERREUR_CONF";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// En ALE on ne doit pas faire la commande sur A2 ou B2
	if (equip->IsChannelAleReserved(params[1]) == TRUE)
	{
		reponse = params[1] + ";USED";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// TODO Erreur STATE si pdt la phase d'appel en ALE on recoit la commande, non traité

	//equip->SetChannelOffsetCarrierFrequency(params[1], atoi(params[2].c_str()));

	// FDI - GetChannelOffsetCarrierFrequency(const string id)
	// TODO vérification de des bornes

	equip->SetChannelOffsetCarrierFrequency(params[1], equip->GetChannelOffsetCarrierFrequency(params[1]) + atoi(params[2].c_str()));



	if (acq) SendACK(&params[0], &params[1]);

	//reponse = params[1] + ";" + params[2];

	// FDI
	reponse = params[1] + ";" + IntToString(equip->GetChannelOffsetCarrierFrequency(params[1]), 3, TRUE);

	SendSignaling("TPO", &reponse);


	return 0;
}

int CProtoTRC1752::RES(istringstream &trame, bool acq)
{
	// La commande
	string cmd = "RES";

	string id = "";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	if(!getline(trame, id, ';'))
	{
		if (acq) SendNAC(&cmd, 1);
		return ERR_NON_CONFORME;
	}

	// Verifie le channel id
	if (equip->ValidChannelId(id) == FALSE)
	{
		if (acq) SendNAC(&cmd, 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidChannelVersion(id) == FALSE)
	{
		reponse = id + ";VERSION";
		if (acq) SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// En ALE on ne doit pas faire la commande sur A2 ou B2
	if (equip->IsChannelAleReserved(id) == TRUE)
	{
		reponse = id + ";USED";
		if (acq) SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	TChannelConfiguration conf = equip->GetChannelConfiguration(equip->GetChannelAssociatedAfConfiguration(id));

	// Le channel ne doit pas etre en RX
	if (conf.direction == "RX")
	{
		reponse = id + ";ERREUR_CONF";
		if (acq) SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	// TODO Le channel ne doit pas etre idle et doit emettre
	if (equip->GetChannelEmissionStatus(id) != "EN_COURS")
	{
		reponse = id + ";INACTIVE";
		if (acq) SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	string status = equip->GetAleStatus(id);
	// Impossible ds certains états (calling phase en ale, asynchronous, transparent)
	if ((equip->GetChannelType(id) != "-" 
		&& status != "LKD" && status != "LKG" && status != "SCA" && status != "LIS" && status != "SAM" && status != "RAM")
		|| (equip->GetInterfaceConfiguration(id).type == "ASYNCHRONE") 
		|| (conf.waveform == "TRANSPARENT"))
	{
		reponse = id + ";STATE";
		if (acq) SendNAC(&cmd, &reponse);
		return ERR_NON_CONFORME;
	}

	if (acq) SendACK(&cmd, &id);

	if (equip->GetTest("Int" + id) == TRUE)
	{
		// On retire la panne sur la voie
		equip->SetTest("Int" + id, FALSE);
		SendSignaling("TRE", &id);
	}

	return 0;
}

void CProtoTRC1752::SignalINC(string *error, const string *board, string *task, string *debug)
{
	string reponse = "";

	if (board != NULL) reponse += *board;

	reponse += ";" + *error + ";";

	if (task != NULL) reponse += *task;

	reponse += ";";

	if (debug != NULL) reponse += *debug;

	SendSignaling("INC", &reponse);
}

int CProtoTRC1752::DSP(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 29
	string params[30];

	// La commande
	params[0] = "DSP";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	for(int param_number = 1; param_number<30; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 29)
		{
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que la carte n'est pas en panne
	if (equip->GetTest(params[1]) == TRUE)
	{
		reponse = params[1] + ";PANNE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que la carte n'est pas utilisée
	if (equip->IsChannelFree(params[1]) == FALSE || equip->IsChannelAleReserved(params[1]) == TRUE)
	{
		reponse = params[1] + ";USED";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Validation des paramètres
	if (equip->ValidAleParameterOnOff(params[9]) == FALSE)
	{
		SendNAC(&params[0], 9);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterAgingPercentage(params[10]) == FALSE)
	{
		SendNAC(&params[0], 10);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterAgingTime(params[11]) == FALSE)
	{
		SendNAC(&params[0], 11);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterOnOff(params[12]) == FALSE)
	{
		SendNAC(&params[0], 12);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterOnOff(params[13]) == FALSE)
	{
		SendNAC(&params[0], 13);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterServiceActivation(params[14]) == FALSE)
	{
		SendNAC(&params[0], 14);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterOnOff(params[15]) == FALSE)
	{
		SendNAC(&params[0], 15);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterOnOff(params[16]) == FALSE)
	{
		SendNAC(&params[0], 16);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterOnOff(params[17]) == FALSE)
	{
		SendNAC(&params[0], 17);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterOnOff(params[18]) == FALSE)
	{
		SendNAC(&params[0], 18);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterScanRate(params[19]) == FALSE)
	{
		SendNAC(&params[0], 19);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterTwa(params[20]) == FALSE)
	{
		SendNAC(&params[0], 20);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterTwa(params[21]) == FALSE)
	{
		SendNAC(&params[0], 21);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterTwt(params[22]) == FALSE)
	{
		SendNAC(&params[0], 22);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterTuneTime(params[23]) == FALSE)
	{
		SendNAC(&params[0], 23);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterTuneTime(params[24]) == FALSE)
	{
		SendNAC(&params[0], 24);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterPttGestion(params[25]) == FALSE)
	{
		SendNAC(&params[0], 25);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterSoundLength(params[26]) == FALSE)
	{
		SendNAC(&params[0], 26);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterRetries(params[27]) == FALSE)
	{
		SendNAC(&params[0], 27);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterRetries(params[28]) == FALSE)
	{
		SendNAC(&params[0], 28);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterLongSoundLimit(params[29]) == FALSE)
	{
		SendNAC(&params[0], 29);
		return ERR_NON_CONFORME;
	}

	TAleParameter conf = equip->GetAleParameter(params[1]);

	conf.automatic_sounding = params[9]; // ON/OFF
	conf.aging_percentage = atoi(params[10].c_str()); // 000...100

	if (equip->GetFft1302() == false)
	{
		conf.aging_time = params[11]; // 00.0...08.0
	}
	else if(params[11] == "08.0" && equip->GetFft1302() == true)
	{
		conf.aging_time = "04.0";
	}
	else
	{
		conf.aging_time = params[11]; // 00.0...08.0
	}


	conf.multiservice = params[12]; // ON/OFF
	conf.automatic_reconfiguration = params[13]; // ON/OFF
	conf.service_activation = atoi(params[14].c_str()); // 01...10
	conf.allcall_message = params[15]; // ON/OFF
	conf.wildcard_message = params[16]; // ON/OFF
	conf.anycall_message  = params[17]; // ON/OFF
	conf.respond = params[18]; // ON/OFF
	conf.scanrate = atoi(params[19].c_str()); // 2/5
	conf.twa_automatic = atoi(params[20].c_str()); // 000...999
	conf.twa_manual = atoi(params[21].c_str()); // 000...999
	conf.twt = atoi(params[22].c_str()); // 0000...0099
	conf.tunetime_local = atoi(params[23].c_str()); // 0000...9999
	conf.tunetime_other = atoi(params[24].c_str()); // 0000...9999
	conf.ptt_gestion = params[25]; // WIRE/SERIAL
	if (params[26] == "---") 
		conf.sound_length = 0; // 001...100 000=---=auto
	else
		conf.sound_length = atoi(params[26].c_str()); // 001...100 000=---=auto
	conf.retries_channel = atoi(params[27].c_str()); // 0...9
	conf.retries_scanfield = atoi(params[28].c_str()); // 0...9
	conf.long_sound_limit = atoi(params[29].c_str()); // 00...99

	equip->SetAleParameter(params[1], conf);

	SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::DCP(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 19
	string params[20];

	// La commande
	params[0] = "DCP";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	for(int param_number = 1; param_number<20; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 19)
		{
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 4
	if (equip->ValidAleParameterCmsChoice(params[4]) == FALSE)
	{
		SendNAC(&params[0], 4);
		return ERR_NON_CONFORME;
	}

// Parametre 5
	if (equip->ValidAleParameterAleTerminationFrame(params[5]) == FALSE)
	{
		SendNAC(&params[0], 5);
		return ERR_NON_CONFORME;
	}

// Parametre 6
	if (params[4] == "CHA")
		if (equip->ValidAleParameterIndexChannelTable(params[6]) == FALSE)
		{
			SendNAC(&params[0], 6);
			return ERR_NON_CONFORME;
		}

// Parametre 7
	if (params[7] != "")
	{
		if (equip->ValidAleParameterUsableFrequency(params[7]) == FALSE)
		{
			SendNAC(&params[0], 7);
			return ERR_NON_CONFORME;
		}
	}

// Parametre 8
	if (params[8] != "")
	{
		if (equip->ValidAleParameterUsableFrequency(params[8]) == FALSE)
		{
			SendNAC(&params[0], 8);
			return ERR_NON_CONFORME;
		}
	}

// Parametre 9
	if (equip->ValidAleParameterCallType(params[9]) == FALSE)
	{
		SendNAC(&params[0], 9);
		return ERR_NON_CONFORME;
	}

	
// Parametre 10
	if (equip->ValidAleParameterIndexSelfAddress(params[10]) == FALSE)
	{
		SendNAC(&params[0], 10);
		return ERR_NON_CONFORME;
	}

// Parametre 11
	if (equip->ValidAleParameterOnOff(params[11]) == FALSE)
	{
		SendNAC(&params[0], 11);
		return ERR_NON_CONFORME;
	}

// Parametre 12
	if (equip->ValidAleParameterOnOff(params[12]) == FALSE)
	{
		SendNAC(&params[0], 12);
		return ERR_NON_CONFORME;
	}

// Parametre 13
	if (params[13] != "")
	{
		if (equip->ValidAleParameterStationNetworkGroup(params[13]) == FALSE)
		{
			SendNAC(&params[0], 13);
			return ERR_NON_CONFORME;
		}
	}

// Parametre 14
	if (params[9] == "STD" || params[9] == "NET")
		if (equip->ValidAleParameterCalledAddress(params[14]) == FALSE)
		{
			SendNAC(&params[0], 14);
			return ERR_NON_CONFORME;
		}

// Parametre 15
	if (params[15] != "")
	{
		if (equip->ValidAleParameterCalledAddressString(params[15]) == FALSE)
		{
			SendNAC(&params[0], 15);
			return ERR_NON_CONFORME;
		}
	}

// Parametre 16
	if (params[16] != "")
	{
		if (equip->ValidAleParameterIndexStationTableGroup(params[16]) == FALSE)
		{
			SendNAC(&params[0], 16);
			return ERR_NON_CONFORME;
		}
	}

// Parametre 17
	if (equip->ValidAleParameterAgc(params[17]) == FALSE)
	{
		SendNAC(&params[0], 17);
		return ERR_NON_CONFORME;
	}

// Parametre 18
	if (equip->ValidAleParameterCallLength(params[18]) == FALSE)
	{
		SendNAC(&params[0], 18);
		return ERR_NON_CONFORME;
	}

// Parametre 19
	if (params[19] != "")
	{
		if (equip->ValidAleParameterAmdMessage(params[19]) == FALSE)
		{
			SendNAC(&params[0], 19);
			return ERR_NON_CONFORME;
		}
	}

	// On sauve
	TAleParameter conf = equip->GetAleParameter(params[1]);

	conf.cms_choice = params[4]; // CHA/BST/LMF
	conf.ale_termination_frame = params[5]; // TIS/TAS
	if (params[4] == "CHA") conf.index_channel_table = atoi(params[6].c_str()); // 00...99
		else conf.index_channel_table = 0;
	if (params[7] != "") conf.lowest_usable_frequency = atoi(params[7].c_str()); // 015000000...29999999
	if (params[8] != "") conf.upper_usable_frequency = atoi(params[8].c_str()); // 015000000...29999999
	conf.call_type = params[9]; // STD/ANY/SAN.../SAL
	conf.index_selfaddress = atoi(params[10].c_str()); // 00...19
	conf.quick_identification = params[11]; // ON/OFF
	conf.quality_analysis = params[12]; // ON/OFF
	if (params[13] != "") conf.station_network_group = params[13]; // S/N/G
	if (params[9] == "STD" || params[9] == "NET") conf.called_address = atoi(params[14].c_str()); // 00...99
		else conf.called_address = 0;
	if (params[15] != "") conf.called_address_string = params[15]; // ??
	if (params[16] != "") 
	{
		istringstream convert (params[16].c_str());
		string val = "";
		int vali;

		while(getline(convert, val, '/'))
		{
			vali = atoi(val.c_str());
			conf.index_station_table_group.push_back(vali);
		}
	}

	conf.agc = params[17];
	conf.call_length = atoi(params[18].c_str()); // 000...999
	if (params[19] != "") conf.amd_message = params[19]; // 90 chars

	equip->SetAleParameter(params[1], conf);

	SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::DLP(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[3];

	// La commande
	params[0] = "DLP";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	for(int param_number = 1; param_number<3; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 2)
		{
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	//TODO tester l'etat de l'ale erreur STATE pdt un link exchange ou linked

// Parametre 2
	// Vérifie le link
	if (equip->ValidAleParameterLinkProtectionLevel(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	TAleParameter conf = equip->GetAleParameter(params[1]);

	conf.link_protection_level = atoi(params[2].c_str());

	equip->SetAleParameter(params[1], conf);

	SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::AKT(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 4
	string params[5];

	// La commande
	params[0] = "AKT";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres
	for(int param_number = 1; param_number<5; param_number++)
		if(!getline(trame, params[param_number], ';') && param_number != 4)
		{
			SendNAC(&params[0], param_number);
			return ERR_NON_CONFORME;
		}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie si la board n'est pas active
	if (equip->IsChannelFree(params[1]) == FALSE)
	{
		reponse = params[1] + ";USED";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Verifier parametres
	if (equip->ValidAleParameterKeyManagement(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidTableName(params[3]) == FALSE)
	{
		SendNAC(&params[0], 3);
		return ERR_NON_CONFORME;
	}

	if (equip->ValidAleParameterKeyPosition(params[4]) == FALSE)
	{
		SendNAC(&params[0], 4);
		return ERR_NON_CONFORME;
	}

	TTableLT current_table;
	string current_conf_location = "LT0";

	// Verifie si la table existe
	if (equip->GetTableLtName(params[1], "LT0") == params[3])
	{
		current_table = equip->GetTableLT(params[1], "LT0");
	} else if (equip->GetTableLtName(params[1], "LT1") == params[3])
	{
		current_table = equip->GetTableLT(params[1], "LT1");
		current_conf_location = "LT1";
	}
	else
	{
		reponse = params[1] + ";TABLE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	int key_position = atoi(params[4].c_str());

	// Verifie la presence de la cle dans table
	if (current_table.key[key_position] == FALSE)
	{
		reponse = params[1] + ";NOKEY";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie que les clés de la table sont contigues en mode automatique (T3-P28)
	if (params[2] == "24H")
	{
		bool stop = FALSE;
		for(int i = key_position; i<NB_LT_KEY; i++)
		{
			if (current_table.key[i] == FALSE) stop = TRUE;
			else if (stop == TRUE)
			{
				reponse = params[1] + ";TABLE";
				SendNAC(&params[0], &reponse);
				return ERR_NON_CONFORME;
			}
		}
	}
	
	// Remplir la struct (echange de table lt0 / lt1)
	if (current_conf_location == "LT1")
		equip->ActiveLT1(params[1]);

	TAleParameter conf = equip->GetAleParameter(params[1]);

	conf.key_management = params[2];
	conf.key_position = key_position;

	equip->SetAleParameter(params[1], conf);

	SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::DLT(istringstream &trame)
{
	// Liste des char valide pour l'index cle LP
	char cset[] = "1234567890";

	// Les paramètres commencent à 1 et finissent à 4
	string params[NB_PARAM_DLT];

	// La commande
	params[0] = "DLT";

	string reponse = ""; // utilisé en interne

	// Chargement des paramètres

	int resultat = ExtractData(trame, params, NB_PARAM_DLT);

	if (resultat != 0)
	{
		SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";" + params[2] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie la carte est libre
	if (equip->IsChannelFree(params[1]) == FALSE)
	{
		reponse = params[1] + ";" + params[2] + ";USED";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	// Verifie type de table
	if (equip->ValidTableType(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

// Parametre 3+4
	// Check CRC
	if (equip->ValidTableCRC(params[4]) == FALSE)
	{
		SendNAC(&params[0], 4);
		return ERR_NON_CONFORME;
	}

	if (equip->CalculateCRC(params[3]) != atoi(params[4].c_str()))
	{
		reponse = params[1] + ";" + params[2] + ";BAD_CRC";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Extraction de la liste de données
	istringstream data (params[3].c_str());

//LTx	
	if (params[2] == "LT0" || params[2] == "LT1")
	{
		// la table ne doit pas etre active
		if (params[2] == "LT0" && equip->GetAleKeyPosition(params[1]) != DEFAULT_INT_VALUE)
		{
			reponse = params[1] + ";" + params[2] + ";TABLE";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		string res[NB_PARAM_LT_FILE];

		resultat = ExtractData(data, res, NB_PARAM_LT_FILE, ',');

		if (resultat != 0)
		{
			SendNAC(&params[0], resultat);
			return ERR_NON_CONFORME;
		}

		// GIC
		if(res[1] != equip->GetGic())
		{
			reponse = params[1] + ";" + params[2] + ";GIC";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		// Datas
		if (res[2] == "")
		{
			reponse = params[1] + ";" + params[2] + ";FIRST_L_EMPTY";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		string table_name, key_index;
		table_name = res[2].substr(0,3);
		key_index = res[2].substr(3,2);

		if (res[2].length() != 32 || equip->ValidTableName(table_name) == FALSE 
			|| equip->ValidAleParameterKeyPosition(key_index) == FALSE || strspn (res[2].substr(3,2).c_str(), cset) != 2)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		if (   (params[2] == "LT0" && table_name == equip->GetTableLtName(params[1], "LT1"))
			|| (params[2] == "LT1" && table_name == equip->GetTableLtName(params[1], "LT0")) )
		{
			reponse = params[1] + ";" + params[2] + ";TABLE_NAME";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		// vector init
		if (res[3].length() != 32)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		// Saving
		TTableLT conf = equip->GetTableLT(params[1], params[2]);

		conf.name = table_name;
		conf.key[atoi(key_index.c_str())] = TRUE;

		equip->SetTableLT(params[1], params[2], conf);

	} 
//RCH
	else if (params[2] == "RCH")
	{
		string res[NB_PARAM_RCH_FILE];

		resultat = ExtractData(data, res, NB_PARAM_RCH_FILE, ',');

		if (resultat != 0)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		// On transforme cette liste de paramètres en TRch
		TRch rch;
		resultat = equip->ExtractTableRch(res, rch);

		if (resultat == -1)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		// On insère ces nouvelles valeurs
		equip->AddRch(params[1], resultat, rch);

		// On reset le compteur de sounding
		equip->ResetAleSoundIndex(params[1]);
	}
//SAD
	else if (params[2] == "SAD")
	{
		string res[NB_PARAM_SAD_FILE];

		resultat = ExtractData(data, res, NB_PARAM_SAD_FILE, ',');

		if (resultat != 0)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		// On transforme cette liste de paramètres en TSad
		TSad sad;
		resultat = equip->ExtractTableSad(res, sad);

		if (resultat == -1)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		// On insère ces nouvelles valeurs
		equip->AddSad(params[1], resultat, sad);
	}
//STA
	else if (params[2] == "STA")
	{
		string res[NB_PARAM_STA_FILE];

		resultat = ExtractData(data, res, NB_PARAM_STA_FILE, ',');

		if (resultat != 0)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		// On transforme cette liste de paramètres en TSta
		TSta sta;
		resultat = equip->ExtractTableSta(res, sta);

		if (resultat == -1)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		// On insère ces nouvelles valeurs
		equip->AddSta(params[1], resultat, sta);
	}
//NET
	else if (params[2] == "NET")
	{
		string res[NB_PARAM_NET_FILE];

		resultat = ExtractData(data, res, NB_PARAM_NET_FILE, ',');

		if (resultat != 0)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		// On transforme cette liste de paramètres en TNet
		TNet net;
		resultat = equip->ExtractTableNet(res, net);

		if (resultat == -1)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		// On insère ces nouvelles valeurs
		equip->AddNet(params[1], resultat, net);
	}
//SST
	else if (params[2] == "SST")
	{
		string res[NB_PARAM_SST_FILE];

		resultat = ExtractData(data, res, NB_PARAM_SST_FILE, ',');

		if (resultat != 0)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		// On transforme cette liste de paramètres en TSst
		TSst sst;
		resultat = equip->ExtractTableSst(res, sst);

		if (resultat == -1)
		{
			SendNAC(&params[0], 3);
			return ERR_NON_CONFORME;
		}

		// On insère ces nouvelles valeurs
		equip->AddSst(params[1], resultat, sst);
	}

	reponse = params[1] + ";" + params[2];
	SendACK(&params[0], &reponse);

	return 0;
}

int CProtoTRC1752::DLQ(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 4
	string params[NB_PARAM_DLQ];

	// La commande
	params[0] = "DLQ";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_DLQ);

	if (resultat != 0)
	{
		SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie la carte est libre
	if (equip->IsChannelFree(params[1]) == FALSE)
	{
		reponse = params[1] + ";USED";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::WRT(istringstream &trame, bool acq)
{
	// Les paramètres commencent à 1 et finissent à 4
	string params[NB_PARAM_WRT];

	// La commande
	params[0] = "WRT";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_WRT);

	if (resultat != 0)
	{
		if (acq) SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie la carte est libre
	if (equip->IsChannelFree(params[1]) == FALSE)
	{
		reponse = params[1] + ";USED";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (params[2] == "1" || params[2] == "2")
	{
		equip->WriteTable(params[1], params[2]);
	}
	else // on doit accepter la valeur 2
	{
		if (acq) SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	// FFT_1190 - Le 16/06/2010
	reponse = params[1] + ";" + params[2];

	if (acq) SendACK(&params[0], &reponse);

	return 0;
}

int CProtoTRC1752::SEL(istringstream &trame, bool acq)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[NB_PARAM_SEL];

	// La commande
	params[0] = "SEL";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_SEL);

	if (resultat != 0)
	{
		if (acq) SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie la carte est libre
	if (equip->IsChannelFree(params[1]) == FALSE)
	{
		reponse = params[1] + ";USED";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (params[2] == "1" || params[2] == "2")
	{
		equip->ReadTable(params[1], params[2]);
	}
	else // on doit accepter la valeur 2
	{
		if (acq) SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	if (acq) SendACK(&params[0], &params[1]);

	return 0;
}

int CProtoTRC1752::ART(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[NB_PARAM_ART];

	// La commande
	params[0] = "ART";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_ART);

	if (resultat != 0)
	{
		SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie la carte est libre
	if (equip->IsChannelFree(params[1]) == FALSE)
	{
		reponse = params[1] + ";STATE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (params[2] != "SAD" && params[2] != "RCH" && params[2] != "NET" && params[2] != "STA" && params[2] != "SST")
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

// Parametre 3
	int val = atoi(params[3].c_str());
	if (params[3].length() != 2 || val <0 || val>99)
	{
		SendNAC(&params[0], 3);
		return ERR_NON_CONFORME;
	}

	if (params[2] == "SAD")
	{
		if (equip->IsSadPresent(params[1]) == FALSE)
		{
			reponse = params[1] + ";TABLE";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		reponse = params[1] + ";" + params[2] + ";";

		TSad sad;
		if (equip->GetSad(params[1], val, sad) == FALSE)
			reponse += "T_END;00000";
		else
		{
			string data = params[3] + "," + sad.self_address + "," + IntToString(sad.net_address, 2)
				+ "," + IntToString(sad.slot, 2) + ",";

			bool une_entree = FALSE;

			for(int i = 0; i<NB_LIST_CHANNEL-1; i++)
			{
				if (sad.valid_channels[i] == TRUE)
				{
					data += IntToString(i, 2) + "/";
					une_entree = TRUE;
				}
			}

			if (sad.valid_channels[NB_LIST_CHANNEL-1] == TRUE)
				data += "ALL";
			else
				if (une_entree == TRUE) data.erase(data.length()-1, 1);

			reponse += data + ";" + IntToString(equip->CalculateCRC(data), 5);
		}
	}
	else if (params[2] == "RCH")
	{
		if (equip->IsRchPresent(params[1]) == FALSE)
		{
			reponse = params[1] + ";TABLE";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		reponse = params[1] + ";" + params[2] + ";";

		TRch rch;
		if (equip->GetRch(params[1], val, rch) == FALSE)
			reponse += "T_END;00000";
		else
		{
			string data = params[3] + "," + IntToString(rch.channel, 3) + "," + IntToString(rch.tx_freq, 8) + "," 
				+ IntToString(rch.rx_freq, 8) + "," + rch.mode_tx + "," + rch.mode_rx + ",";
			
			string bfo = IntToString(rch.bfo, 4, TRUE);

			// Pas de + sur 0 dans le bfo
			if (rch.bfo == 0) bfo.erase(0,1);

			data += bfo + "," + IntToString(rch.filter, 3) + "," + IntToString(rch.agc, 1) + "," + IntToString(rch.squelch, 3, TRUE)
				+ "," + IntToString(rch.pwr, 2, TRUE) + "," + rch.ed + "," + IntToString(rch.sound_interv, 4) + ","
				+ IntToString(rch.self_add, 2);

			reponse += data + ";" + IntToString(equip->CalculateCRC(data), 5);
		}
	}
	else if (params[2] == "NET")
	{
		if (equip->IsNetPresent(params[1]) == FALSE)
		{
			reponse = params[1] + ";TABLE";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		reponse = params[1] + ";" + params[2] + ";";

		TNet net;
		if (equip->GetNet(params[1], val, net) == FALSE)
			reponse += "T_END;00000";
		else
		{
			string data = params[3] + "," + net.net_address + ",";

			for(int i = 1; i<NB_NET_ADDRESS; i++)
				data += IntToString(net.net_member[i], 2) + ",";

			data.erase(data.length()-1, 1);

			reponse += data + ";" + IntToString(equip->CalculateCRC(data), 5);
		}
	}
	else if (params[2] == "STA")
	{
		if (equip->IsStaPresent(params[1]) == FALSE)
		{
			reponse = params[1] + ";TABLE";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		reponse = params[1] + ";" + params[2] + ";";

		TSta sta;
		if (equip->GetSta(params[1], val, sta) == FALSE)
			reponse += "T_END;00000";
		else
		{
			string data = params[3] + "," + sta.address_ale + "," + sta.address_arq + "," + IntToString(sta.twr, 5) ;

			bool une_entree = FALSE;

			for(int i = 0; i<NB_LIST_CHANNEL-1; i++)
			{
				if (sta.valid_channels[i] == TRUE)
				{
					data += IntToString(i, 2) + "/";
					une_entree = TRUE;
				}
			}

			if (sta.valid_channels[NB_LIST_CHANNEL-1] == TRUE)
				data += "ALL";
			else
				if (une_entree == TRUE) data.erase(data.length()-1, 1);

			reponse += data + ";" + IntToString(equip->CalculateCRC(data), 5);
		}
	}
	else if (params[2] == "SST")
	{
		if (equip->IsSstPresent(params[1]) == FALSE)
		{
			reponse = params[1] + ";TABLE";
			SendNAC(&params[0], &reponse);
			return ERR_NON_CONFORME;
		}

		reponse = params[1] + ";" + params[2] + ";";

		TSst sst;
		if (equip->GetSst(params[1], val, sst) == FALSE)
			reponse += "T_END;00000";
		else
		{
			string data = params[3] + ",";

			for(int i = 0; i<NB_LIST_CHANNEL-1; i++)
				if (sst.scan_set_channel[i] == TRUE)
					data += IntToString(i, 2) + "/";

			data.erase(data.length()-1, 1);

			reponse += data + ";" + IntToString(equip->CalculateCRC(data), 5);
		}
	}

	SendACK(&params[0], &reponse);

	return 0;
}

int CProtoTRC1752::CLT(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[NB_PARAM_CLT];

	// La commande
	params[0] = "CLT";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_CLT);

	if (resultat != 0)
	{
		SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie la carte est libre
	if (equip->IsChannelFree(params[1]) == FALSE)
	{
		reponse = params[1] + ";USED";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2

	if (params[2] == "SAD")
	{
		equip->DeleteSad(params[1]);
	}
	else if (params[2] == "RCH")
	{
		equip->DeleteRch(params[1]);
	}
	else if (params[2] == "NET")
	{
		equip->DeleteNet(params[1]);
	}
	else if (params[2] == "STA")
	{
		equip->DeleteSta(params[1]);
	}
	else if (params[2] == "SST")
	{
		equip->DeleteSst(params[1]);
	}
	else if (params[2] == "LT0")
	{
		equip->DeleteLt0(params[1]);
		equip->SetAleKeyPosition(params[1], DEFAULT_INT_VALUE);
	}
	else if (params[2] == "LT1")
	{
		equip->DeleteLt1(params[1]);
	}
	else if (params[2] == "ALL")
	{
		equip->DeleteSad(params[1]);
		equip->DeleteRch(params[1]);
		equip->DeleteNet(params[1]);
		equip->DeleteSta(params[1]);
		equip->DeleteSst(params[1]);
		equip->DeleteLt0(params[1]);
		equip->DeleteLt1(params[1]);
		equip->SetAleKeyPosition(params[1], DEFAULT_INT_VALUE);
	}
	else if (params[2] != "LQA")
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	reponse = params[1] + ";" + params[2];

	SendACK(&params[0], &reponse);

	return 0;
}

int CProtoTRC1752::CLS(istringstream &trame, bool acq)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[NB_PARAM_CLS];

	// La commande
	params[0] = "CLS";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_CLS);

	if (resultat != 0)
	{
		if (acq) SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		if (acq) SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie la carte est libre
	if (equip->IsChannelFree(params[1]) == FALSE)
	{
		reponse = params[1] + ";USED";
		if (acq) SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (params[2] == "1" || params[2] == "2")
	{
		equip->DeleteTableStored(params[1], params[2]);
	}
	else 
	{
		if (acq) SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}

	reponse = params[1] + ";" + params[2];
	if (acq) SendACK(&params[0], &reponse);

	return 0;
}

int CProtoTRC1752::EUA(bool acq)
{
	string cmd = "EUA";
	
	string reponse = ""; // utilisé en interne

	if (acq) SendACK(&cmd, &reponse);

	// Effacement A1
	reponse = "A1";

	equip->DeleteSad(reponse);
	equip->DeleteRch(reponse);
	equip->DeleteNet(reponse);
	equip->DeleteSta(reponse);
	equip->DeleteSst(reponse);
	equip->DeleteLt0(reponse);
	equip->DeleteLt1(reponse);

	equip->DeleteTableStored(reponse, "1");
	equip->DeleteTableStored(reponse, "2");
	equip->SetAleKeyPosition(reponse, DEFAULT_INT_VALUE);

	// Envoi du signal de confirmation
	reponse += ";OK";
	if (acq) SendSignaling("CEU", &reponse);

	// Si bi-voie
	if (equip->GetQuadrivoie() == TRUE)
	{
		// Effacement B1
		reponse = "B1";

		equip->DeleteSad(reponse);
		equip->DeleteRch(reponse);
		equip->DeleteNet(reponse);
		equip->DeleteSta(reponse);
		equip->DeleteSst(reponse);
		equip->DeleteLt0(reponse);
		equip->DeleteLt1(reponse);

		equip->DeleteTableStored(reponse, "1");
		equip->DeleteTableStored(reponse, "2");
		equip->SetAleKeyPosition(reponse, DEFAULT_INT_VALUE);

		// Envoi du signal de confirmation
		reponse += ";OK";
		if (acq) SendSignaling("CEU", &reponse);
	}

	// Durée de l'éffacement du modem
	Sleep(7000);
	// Lancer un test du modem
	equip->SetTestProgress("TIROIR");

	reponse = ";TIROIR;EN_COURS";
	SendSignaling("AUT", &reponse);

	return 0;
}

void CProtoTRC1752::SignalSTL(const string channel)
{
	string reponse = "";
	int val;

	const TAleParameter ale_parameter = equip->GetAleParameter(channel);
	const TModemDistant modem = equip->GetModemDistant();

	// parametre 1 et 2
	reponse = channel + ";" + ale_parameter.ale_status + ";";

	// parametre 3
	if (ale_parameter.ale_status == "SOU")
	{
		reponse += IntToString(equip->GetAleSoundIndex(channel), 2);
	}
	else if (ale_parameter.ale_status != "SCA" && ale_parameter.ale_status != "ERR"
		&& ale_parameter.ale_status != "NKY" && ale_parameter.ale_status != "TME")
	{
		if (equip->GetChannelType(channel) == "C")
		{
			reponse += IntToString(equip->GetChannelIndexScansetChannel(channel), 2);
		}
		else if (equip->GetChannelType(channel) == "S")
		{
			reponse += IntToString(equip->GetAleChannelInScanset(channel), 2);
		}
	}

	reponse += ";";

	// parametre 4
	if (ale_parameter.ale_status == "SCA")
		reponse += IntToString(equip->GetChannelIndexScansetChannel(channel), 2);

	reponse += ";";

	// parametre 5
	if (ale_parameter.ale_status == "CAL" || ale_parameter.ale_status == "RCA" || 
		ale_parameter.ale_status == "SRE" || ale_parameter.ale_status == "RRE" || 
		ale_parameter.ale_status == "SAK" || ale_parameter.ale_status == "LKD" || 
		ale_parameter.ale_status == "LKG" || ale_parameter.ale_status == "SAM" || 
		ale_parameter.ale_status == "RAM")
	{
		reponse += ale_parameter.call_type[0];
	}

	reponse += ";";

	// parametre 6
	if (ale_parameter.ale_status == "CAL" || //ale_parameter.ale_status == "SAM" || 
		ale_parameter.ale_status == "LKG" || //ale_parameter.ale_status == "RAM" ||
		ale_parameter.ale_status == "SAK" )
	{
		// cas (1)
		if(ale_parameter.call_type == "STD" || ale_parameter.call_type == "NET")
		{
			reponse += IntToString(ale_parameter.called_address, 2);
		}
		 else
		{
			reponse += "--";
		}
	} else if (ale_parameter.ale_status == "SAM")
	{
		// Pour le SAM l'adresse est différente suivant qui appelle
		if (equip->GetAleEstAppele(channel) == FALSE)
		{
			// cas (3)
			reponse += IntToString(ale_parameter.called_address, 2);
		}
		else
		{
			val = equip->GetSta(channel, modem.selfaddress[modem.current_selfaddress]);
			if (val != DEFAULT_INT_VALUE) reponse += IntToString(val, 2);
		}
	} else if (ale_parameter.ale_status == "RRE" || ale_parameter.ale_status == "RAM")
	{
		// cas (2)
		reponse += IntToString(ale_parameter.index_selfaddress, 2);
	} else if (ale_parameter.ale_status == "RCA")
	{
		// cas (5)
		if(modem.type_appel == "STA")
		{
			val = equip->GetSad(channel, modem.stations[modem.current_station]);
			if (val != DEFAULT_INT_VALUE) reponse += IntToString(val, 2);
		} else if (modem.type_appel == "NET")
		{
			val = equip->GetNet(channel, modem.reseaux[modem.current_reseau]);
			if (val != DEFAULT_INT_VALUE) reponse += IntToString(val, 2);
		} else reponse += "--";

	} else if (ale_parameter.ale_status == "SRE")
	{
		val = equip->GetSta(channel, modem.selfaddress[modem.current_selfaddress]);
		if (val != DEFAULT_INT_VALUE) reponse += IntToString(val, 2);
	} else if (ale_parameter.ale_status == "LKD")
	{
		if (modem.type_appel == "STA")
		{
			val = equip->GetSad(channel, modem.stations[modem.current_station]);
			if (val != DEFAULT_INT_VALUE) reponse += IntToString(val, 2);
		} else if (modem.type_appel == "NET")
		{
			val = equip->GetNet(channel, modem.reseaux[modem.current_reseau]);
			if (val != DEFAULT_INT_VALUE) reponse += IntToString(val, 2);
		} else reponse += "--";
	}

	reponse += ";";

	// parametre 7
	if (ale_parameter.ale_status == "CAL" || ale_parameter.ale_status == "SRE" || 
		ale_parameter.ale_status == "SAK" || ale_parameter.ale_status == "LKG" || 
		ale_parameter.ale_status == "SAM" || ale_parameter.ale_status == "SOU" || 
		ale_parameter.ale_status == "POL" || ale_parameter.ale_status == "RPO")
	{
		// cas (2)
		reponse += IntToString(ale_parameter.index_selfaddress, 2);
	} else if (ale_parameter.ale_status == "RRE" || 
		ale_parameter.ale_status == "RSO" || ale_parameter.ale_status == "RPO")
	{
		// cas (3)
		reponse += IntToString(ale_parameter.called_address, 2);
	} else if (ale_parameter.ale_status == "RAM")
	{
		// Pour le RAM l'adresse est différente suivant qui appelle
		if (equip->GetAleEstAppele(channel) == FALSE)
		{
			// cas (3)
			reponse += IntToString(ale_parameter.called_address, 2);
		}
		else
		{
			val = equip->GetSta(channel, modem.selfaddress[modem.current_selfaddress]);
			if (val != DEFAULT_INT_VALUE) reponse += IntToString(val, 2);
		}
	} else if (ale_parameter.ale_status == "RCA" || ale_parameter.ale_status == "LKD")
	{
		val = equip->GetSta(channel, modem.selfaddress[modem.current_selfaddress]);
		if (val != DEFAULT_INT_VALUE) reponse += IntToString(val, 2);
	}
	
	reponse += ";";

	// parametre 8
	reponse += ";";

	// parametre 9
	if (ale_parameter.ale_status == "SAK" )
	{
		// cas (9)
		reponse += ale_parameter.amd_message;
	} else if (	ale_parameter.ale_status == "LKD" || ale_parameter.ale_status == "RAM")
	{
		reponse += modem.amd_chat;
	} else if (ale_parameter.ale_status == "SAM")
	{
		reponse += modem.amd_chat_recu;
	}

	reponse += ";";

	// parametre 10 à 15
	reponse += ";;;;;";

	SendSignaling("STL", &reponse);
}

void CProtoTRC1752::SignalRAD(const string aux_port, const string error, bool force)
{
	string reponse = "";

	// En ale actif on renvoi l'etat radio
	if (aux_port == "IA3" || aux_port == "IA4")
	{
		if ((equip->GetChannelState("A1") == "ACTIVE" && equip->GetChannelType("A1") != "-") || force) 
		{
			reponse = aux_port + ";" + error + ";40";
			SendSignaling("RAD", &reponse);
			return;
		}
	}

	if (aux_port == "IA5" || aux_port == "IA6")
	{
		if ((equip->GetChannelState("B1") == "ACTIVE" && equip->GetChannelType("B1") != "-") || force) 
		{
			reponse = aux_port + ";" + error + ";40";
			SendSignaling("RAD", &reponse);
		}
	}
	
}

int CProtoTRC1752::LNL(istringstream &trame)
{
		// Les paramètres commencent à 1 et finissent à 2
	string params[NB_PARAM_LNL];

	// La commande
	params[0] = "LNL";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_LNL);

	if (resultat != 0)
	{
		SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	if (equip->GetChannelType(params[1]) == "-" || (equip->GetAleStatus(params[1]) != "SCA" && equip->GetAleStatus(params[1]) != "LIS"))
	{
		reponse = params[1] + ";STATE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	if (equip->GetChannelLinkManagementType(params[1]) != "LMANU")
	{
		reponse = params[1] + ";OTHER";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	SendACK(&params[0], &params[1]);

	equip->LancerAppel(params[1]);

	return 0;
}

int CProtoTRC1752::UNL(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[NB_PARAM_UNL];

	// La commande
	params[0] = "UNL";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_UNL);

	if (resultat != 0)
	{
		SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	if (equip->GetChannelType(params[1]) == "-" || equip->IsLink(params[1]) == FALSE )
	{
		reponse = params[1] + ";STATE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	if (equip->GetChannelLinkManagementType(params[1]) != "LMANU")
	{
		reponse = params[1] + ";OTHER";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	SendACK(&params[0], &params[1]);

	equip->CasserAppel(params[1]);

	return 0;
}

int CProtoTRC1752::CHT(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[NB_PARAM_CHT];

	// La commande
	params[0] = "CHT";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_CHT);

	if (resultat != 0)
	{
		SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie l'etat ale et le niveau lp et pas en réception
	if (equip->IsLink(params[1]) == FALSE
		|| equip->GetAleParameter(params[1]).link_protection_level != 0 || equip->GetChannelReceptionStatus(params[1]) != "INACTIF")
	{
		reponse = params[1] + ";STATE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (equip->ValidAleParameterAmdMessage(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}	

// Parametre 3
	if (equip->ValidAleParameterOnOff(params[3]) == FALSE)
	{
		SendNAC(&params[0], 3);
		return ERR_NON_CONFORME;
	}	

	SendACK(&params[0], &params[1]);

	TModemDistant modem = equip->GetModemDistant();
	modem.amd_chat_recu = params[2];
	equip->SetModemDistant(modem);

	// Declenchement automate
	equip->EnvoyerAmd(params[1]);

	return 0;
}

int CProtoTRC1752::MAG(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[NB_PARAM_MAG];

	// La commande
	params[0] = "MAG";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_MAG);

	if (resultat != 0)
	{
		SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie l'etat ale
	if (equip->IsLink(params[1]) == FALSE)
	{
		reponse = params[1] + ";STATE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (equip->ValidAleParameterAgc(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}	

	TAleParameter ale_parameter = equip->GetAleParameter(params[1]);

	ale_parameter.agc = params[2];

	equip->SetAleParameter(params[1], ale_parameter);

	SendACK(&params[0], &params[1]);

	return 0;
}

void CProtoTRC1752::SignalINT(const string voie)
{
	if (equip->GetTest("Int" + voie) == TRUE
		&& equip->GetChannelAfLevelReceived(voie) >= -10 
		&& equip->GetChannelConfiguration(equip->GetChannelAssociatedAfConfiguration(voie)).waveform != "TRANSPARENT"
		&& equip->GetInterfaceConfiguration(voie).type != "ASYNCHRONE")
	{
			string reponse = voie + ";RECEPTION_PLEIN";
			SendSignaling("INT", &reponse);
	}
}

int CProtoTRC1752::SOU(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 2
	string params[NB_PARAM_SOU];

	// La commande
	params[0] = "SOU";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_SOU);

	if (resultat != 0)
	{
		SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	if (equip->GetChannelType(params[1]) != "C" || equip->GetAleStatus(params[1]) != "LIS")
	{
		reponse = params[1] + ";STATE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Utilise le self address du rch
	TRch rch;
	equip->GetRch(params[1], equip->GetChannelIndexScansetChannel(params[1]), rch);
	if (rch.self_add == DEFAULT_INT_VALUE)
	{
		reponse = params[1] + ";OTHER";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	TAleParameter ale = equip->GetAleParameter(params[1]);
	int index_courant = ale.sounding_index;
	ale.sounding_index = equip->GetChannelIndexScansetChannel(params[1]);
	equip->SetAleParameter(params[1], ale);

	equip->SetAleStatus(params[1], "SOU");

	ale.sounding_index = index_courant;
	equip->SetAleParameter(params[1], ale);

	SendACK(&params[0], &params[1]);

	equip->SetAleStatus(params[1], "LIS");

	return 0;
}

void CProtoTRC1752::SignalTBF(const string voie)
{
	if (equip->GetChannelState(voie) != "ACTIVE" || equip->GetChannelConfiguration(equip->GetChannelAssociatedAfConfiguration(voie)).direction == "RX") return;

	string reponse = voie + ";" + IntToString(equip->GetAfChannelConfiguration(equip->GetAfChannelFromModemChannel(voie)).output_level + equip->GetChannelAfLevelOutput(voie), 2, TRUE);

	SendSignaling("TBF", &reponse);
}

void CProtoTRC1752::SignalETA(const string direction, const string channel)
{
	if (equip->GetChannelState(channel) != "ACTIVE") return;

	string reponse = channel + ";" + direction + ";";

	if (direction == "EMISSION")
		reponse += equip->GetChannelEmissionStatus(channel);
	else
		reponse += equip->GetChannelReceptionStatus(channel);

	reponse += ";";

	SendSignaling("ETA", &reponse);
}

void CProtoTRC1752::SignalTSP(const string channel)
{
	if (equip->GetChannelState(channel) != "ACTIVE") return;

	TChannelConfiguration conf = equip->GetChannelConfiguration(channel);

	string reponse = channel + ";" 
		+ conf.waveform + ";" + conf.diversity + ";" + conf.direction + ";" + IntToString(conf.af_transmission_baudrate, 4) + ";"
		+ conf.af_transmission_codingtype + ";" + conf.af_transmission_interleaving + ";" 
		+ IntToString(conf.af_reception_baudrate, 4) + ";" + conf.af_reception_codingtype + ";" 
		+ conf.af_reception_interleaving + ";";

	if (equip->GetChannelType(channel) != "-" && equip->ValidAleParameter(channel))
	{
		TAleParameter ale = equip->GetAleParameter(channel);
		reponse += ale.cms_choice + ";";
		
		if (equip->GetChannelType(channel) == "C") 
		{
			reponse += IntToString(equip->GetChannelIndexScansetChannel(channel), 2);
		}
		else
		{
			TSst sst;
			int sst_parcours = 0;

			if (!equip->GetSst(channel, equip->GetChannelIndexScansetChannel(channel), sst)) return;

			while (sst.scan_set_channel[sst_parcours] != TRUE) 
					sst_parcours++;

			reponse += IntToString(sst_parcours, 2);
		}

		reponse += ";" + ale.call_type + ";" + IntToString(ale.index_selfaddress, 2) + ";";

		if (ale.call_type == "STD" || ale.call_type == "NET") 
			reponse += IntToString(ale.called_address, 2);

		reponse += ";;" + ale.respond + ";" + IntToString(ale.scanrate, 1);
	} else
		reponse += ";;;;;;;"; 


	SendSignaling("TSP", &reponse);
}

void CProtoTRC1752::SignalLKL(const string voie, const string erreur)
{
	string reponse = voie + ";" + erreur;

	SendSignaling("LKL", &reponse);
}

int CProtoTRC1752::POL(istringstream &trame)
{
	// Les paramètres commencent à 1 et finissent à 3
	string params[NB_PARAM_POL];

	// La commande
	params[0] = "POL";

	string reponse = ""; // utilisé en interne

	int resultat = ExtractData(trame, params, NB_PARAM_POL);

	if (resultat != 0)
	{
		SendNAC(&params[0], resultat);
		return ERR_NON_CONFORME;
	}

// Parametre 1
	// Verifie le channel id
	if (equip->ValidAleParameter(params[1]) == FALSE)
	{
		SendNAC(&params[0], 1);
		return ERR_NON_CONFORME;
	}

	// Verifie la version
	if (equip->ValidAleParameterVersion(params[1]) == FALSE)
	{
		reponse = params[1] + ";VERSION";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	// Verifie l'etat ale 
	if (equip->IsLink(params[1]) == FALSE)
	{
		reponse = params[1] + ";STATE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 2
	if (equip->ValidAleParameterCalledAddress(params[2]) == FALSE)
	{
		SendNAC(&params[0], 2);
		return ERR_NON_CONFORME;
	}	

	// Verifie l'index
	TSta sta;
	if (equip->GetSta(params[1], atoi(params[2].c_str()), sta) == FALSE)
	{
		reponse = params[1] + ";TABLE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

// Parametre 3
	if (equip->ValidAleParameterIndexSelfAddress(params[3]) == FALSE)
	{
		SendNAC(&params[0], 3);
		return ERR_NON_CONFORME;
	}	

	// Verifie l'index
	TSad sad;
	if (equip->GetSad(params[1], atoi(params[3].c_str()), sad) == FALSE)
	{
		reponse = params[1] + ";TABLE";
		SendNAC(&params[0], &reponse);
		return ERR_NON_CONFORME;
	}

	SendACK(&params[0], &params[1]);

	return 0;
}

// Test de la validité de l'index de la clé LP en chargement
int CProtoTRC1752::testIdxCleLp (const char *s, const char *accept)
{
	return strspn (s, accept);
}
