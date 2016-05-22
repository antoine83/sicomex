/* **************************************************************************
FICHIER :	EquipED42.CPP		 		AUTEUR : FDI
DATE DE CREATION : 	06/01/2016			DERNIERE MODIFICATION : 11/01/2016
VERSION :	1.0
ROLE :		Implémentation de la classe CEquipED42
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\EquipED42.h"
#include "DlgED42.h"
#include "DlgED42Tab.h"
#include "Comm\p_ED42.h"

#include "Divers\Div_fic.h"

#include <sstream>
#include <fstream>
#include <iomanip>


using namespace std;

extern CParamSimu* glob_paramsimu;
extern CDlgAccueil* glob_ihm;

extern char glob_CONTEXT_ED42[];

//////////////////////////////////////////////////////////////////////
// Utilitaires
//////////////////////////////////////////////////////////////////////
int ExtractDataEd42(istringstream &data, string res[], int length, char sep)
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

string IntToStringEd42(int value, int size, bool sign)
{
	stringstream out;
	string result = "";

	// Si la valeur est indéfinie, on renvoi un string vide
	if (value == DEFAULT_INT_VALUE_ED42) return result;

	out << value;

	result = out.str();

	if (value < 0) result.erase(0,1);

	for(int current_size = result.size(); current_size<size; current_size++)
		result.insert(0,"0");

	if (sign == TRUE)
	{
		if (value < 0) result.insert(0,"-");
		else result.insert(0,"+");
	}

	return result;
}

template<typename T>
bool ConvertCString( const CString & Str, T & Dest )
{																																	  _
    // créer un flux à partir de la chaîne donnée
    std::istringstream iss( static_cast<const char *>( Str) );
    // tenter la conversion vers Dest
    return iss >> Dest != 0;
}

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
/* **************************************************************************
METHODE :		CEquipED42()
TRAITEMENT:		Constructeur, initialise les structures
***************************************************************************	*/
CEquipED42::CEquipED42(int idx):CEquip(idx)
{
	int i;

	char heure[9];
	char date[9];
	GetTimeFormat (LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT , NULL, "HH'H'mm'.'ss", (LPTSTR) heure, 9);
	GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,NULL,"dd'/'MM'/'yy", date, 9);

	string date_heure = date;
	date_heure += ".";
	date_heure += heure;

	test_progress	= "";
	panne			= 0;				// panne global de l'équipement nécessitant un redémarrage
	incident		= 0;			// -1=permanent,sinon de 0 à 99
	local			= 0;				// 0=LOC, 1=RMT;
	cik				= 0;				// Présence CIK : 0 pas de CIK
	nl				= 0;
	eg				= 0;

	lastNumber		= 0;
	lastMessage		= "";
	repetition		= FALSE;
	errorMSG		= FALSE;
	errorLF			= FALSE;
	errorCR			= FALSE;
	pasDeReponse	= FALSE;

	//Initialisation de la liste des erreurs
	//Format : Used;Error Number;Extented Code;Meaning
	errorTab.push_back(" "); //utiliser pour le RES
	errorTab.push_back("0;1;1;error codes of cryptomodul");
	errorTab.push_back("0;1;100;F101 interface not activated");
	errorTab.push_back("0;1;101;F101 timeout from SKM");
	errorTab.push_back("0;1;103;F101 error - give header action");
	errorTab.push_back("0;1;106;no variable available");
	errorTab.push_back("0;1;107;wrong password type");
	errorTab.push_back("0;1;108;F101 error - store variable");
	errorTab.push_back("0;1;109;F101 error - store KEK");
	errorTab.push_back("0;1;111;configuration error");
	errorTab.push_back("0;1;112;start error");
	errorTab.push_back("0;1;114;error in software");
	errorTab.push_back("0;1;116;selected variable not defined");
	errorTab.push_back("0;1;119;update limit exceeded");
	errorTab.push_back("0;1;122;bilateral update global error");
	errorTab.push_back("0;1;123;bilateral tag global error");
	errorTab.push_back("0;1;125;wrong dld password from user");
	errorTab.push_back("0;1;126;format error");
	errorTab.push_back("0;1;127;error while connecting CIK");
	errorTab.push_back("0;2;0;variable management");
	errorTab.push_back("0;3;207;missing CIK");
	errorTab.push_back("0;3;1;wrong condition CIK");
	errorTab.push_back("0;3;2;timeout while CIK-init");
	errorTab.push_back("0;3;3;error from cryptomodul");
	errorTab.push_back("0;4;1;password check");

	//Initialisation de la liste des alarmes
	//Format : Used;Alarm type;Alamr number;Meaning
	alarmTab.push_back("0;1;13;ZSS_MANAG_CRC");
	alarmTab.push_back("0;1;12;ZSS_UNEX_SKM_STATE_STARUP");
	alarmTab.push_back("0;1;40;KE_UNEX_SKM_STATE_INDISPOSED");
	alarmTab.push_back("0;1;14;ZSS_FLASH_MAGIC_ERROR");
	alarmTab.push_back("0;1;10;ZSS_FLASH_ERROR");
	alarmTab.push_back("0;1;11;ZSS_UNEX_SKM_STATE_IDLE");
	alarmTab.push_back("0;1;15;ZSS_ERROR_INTERFACEBIT");
	alarmTab.push_back("0;1;31;CE_SKM_TIMEOUT_AOUT");
	alarmTab.push_back("0;1;33;CE_PWDTEST_ERROR");
	alarmTab.push_back("0;1;35;CE_VAR_STAT_ERROR");
	alarmTab.push_back("0;1;36;CE_UNEX_SKM_STATE_AOUT");
	alarmTab.push_back("0;1;38;CE_UNEX_SKM_STATE_POWERON");
	alarmTab.push_back("0;1;23;CE_UNEX_SKM_STATE_INITCIK2_IDLE");
	alarmTab.push_back("0;1;24;CE_UNEX_SKM_STATE_DELCIKUSER_IDLE");
	alarmTab.push_back("0;1;37;CE_CIK_SYSTEM_ERROR");
	alarmTab.push_back("0;1;25;CE_ACTIV_ERROR_CRYSETUP");
	alarmTab.push_back("0;1;26;CE_ACTIV_ERROR_CRYSETUP2");
	alarmTab.push_back("0;1;27;CE_PREP_ERROR_COMSETUP");
	alarmTab.push_back("0;1;39;CE_UNEX_ONLINE_MODE");
	alarmTab.push_back("0;1;29;CE_START_ERROR_ONLINE");
	alarmTab.push_back("0;1;50;CE_STARTRX_ERROR_ONLINE");
	alarmTab.push_back("0;1;51;CE_STARTTX_ERROR_ONLINE");
	alarmTab.push_back("0;2;3;CRYPTOALARM_NOTL");
	alarmTab.push_back("0;2;2;CRYPTOALARM_TAMPER");
	alarmTab.push_back("0;2;1;CRYPTOALARM_GLOBAL");

	//Initialisation de la liste des status error
	//Format : Used; error number; Meaning; nnRepeat (nombre de repetition)
	for (int ii=0; ii<NB_STATUS_ERROR; ii++)
		statusErrorTab.push_back("0;ii;STATUS_ERROR[ii];0");
	/*
	statusErrorTab.push_back("0;PARITY_FRAMING;PARITY FRAMING;0");
	statusErrorTab.push_back("0;SYNTAX_RCS;SYNTAX or RCS;0");
	statusErrorTab.push_back("0;MAX_MSG_LENGTH;MAX MSG LENGTH;0");
	statusErrorTab.push_back("0;UNKNOWN_COMMAND;UNKNOWN COMMAND;0");
	statusErrorTab.push_back("0;NOT_REMOTE_MODE;NOT REMOTE MODE;0");
	statusErrorTab.push_back("0;CONFLICT;CONFLICT;0");
	statusErrorTab.push_back("0;WRONG_COMMAND;WRONG COMMAND;0");
	statusErrorTab.push_back("0;INVALID_PARAMETER;INVALID PARAMETER;0");
	statusErrorTab.push_back("0;NOT_ERROR;NO ERROR;0");
	*/

	//Initialisation de la liste des power on bit
	//Format : Used; Meaning
	powerBit.push_back("0;RAM TEST");
	powerBit.push_back("0;FALSH MEMORY TEST");
	powerBit.push_back("0;INTEGRITY CHECK OF LOADED SOFTWARE MODULES");
	powerBit.push_back("0;CHECKING THE SUPPLY VOLTAGE");
	powerBit.push_back("0;TEST OF ENCRYPTION AND DECRYPTION SIGNAL PATHS");

	//Initialisation de la liste des bit manually
	//Format : Used; Result; Meaning
	bitManually.push_back("0;0;BATTERY TEST");
	bitManually.push_back("0;0;BIT FOR CONTROL UNIT");
	bitManually.push_back("0;0;BIT WITHOUT TEST PLUGS");
	bitManually.push_back("0;0;BIT FOR DS-101 TEST");
	bitManually.push_back("0;0;BIT FOR HEADSET");

	//*********************************************************************************************************
	//Initialisation des défauts general parameters
	//DATA CRYPTO
	default_general_parameters["0"].preset = 0;
	default_general_parameters["0"].operation_mode = DATA_CRYPRO;
	default_general_parameters["0"].transmission_mode = DIGITAL;
	default_general_parameters["0"].transmission_procedure = V24;
	default_general_parameters["0"].trafic_mode = DXD;
	default_general_parameters["0"].application_type = DEFAULT_INT_VALUE_ED42;
	default_general_parameters["0"].output_selection = TXWBV11;
	default_general_parameters["0"].synchronisation_mode = SYN_SYN;
	default_general_parameters["0"].clock_mode = SELF;
	default_general_parameters["0"].nb_of_data_bite = BITS_8;
	default_general_parameters["0"].parity = NONE;
	default_general_parameters["0"].nb_of_stop_bite = BITS_1;
	default_general_parameters["0"].lead_time = 1;
	default_general_parameters["0"].fec = FALSE;
	default_general_parameters["0"].antispoof = FALSE;
	default_general_parameters["0"].data_rate = KB64_0;
	default_general_parameters["0"].dteAnalogInterf = FALSE;
	default_general_parameters["0"].dteDigitalInterface = TRUE;
	default_general_parameters["0"].dceAnalogInterf = FALSE;
	default_general_parameters["0"].dceDigitalInterface = TRUE;

	//VOICE CRYPTO
	default_general_parameters["1"].preset = 1;
	default_general_parameters["1"].operation_mode = VOICE_CRYPRO;
	default_general_parameters["1"].transmission_mode = HF;
	default_general_parameters["1"].transmission_procedure = HFNETV;
	default_general_parameters["1"].trafic_mode = DX;
	default_general_parameters["1"].application_type = DEFAULT_INT_VALUE_ED42;
	default_general_parameters["1"].output_selection = TXWBV11;
	default_general_parameters["1"].synchronisation_mode = SYN_SYN;
	default_general_parameters["1"].clock_mode = DCE;
	default_general_parameters["1"].nb_of_data_bite = BITS_7;
	default_general_parameters["1"].parity = NONE;
	default_general_parameters["1"].nb_of_stop_bite = BITS_1;
	default_general_parameters["1"].lead_time = 15;
	default_general_parameters["1"].fec = FALSE;
	default_general_parameters["1"].antispoof = FALSE;
	default_general_parameters["1"].data_rate = KB2_4;
	default_general_parameters["1"].dteAnalogInterf = TRUE;
	default_general_parameters["1"].dteDigitalInterface = FALSE;
	default_general_parameters["1"].dceAnalogInterf = TRUE;
	default_general_parameters["1"].dceDigitalInterface = FALSE;

	//DATA PLAIN
	default_general_parameters["2"].preset = 2;
	default_general_parameters["2"].operation_mode = DATA_PLAIN;
	default_general_parameters["2"].transmission_mode = DIGITAL;
	default_general_parameters["2"].transmission_procedure = V24;
	default_general_parameters["2"].trafic_mode = SPH;
	default_general_parameters["2"].application_type = DEFAULT_INT_VALUE_ED42;
	default_general_parameters["2"].output_selection = TXWBV11;
	default_general_parameters["2"].synchronisation_mode = SYN_SYN;
	default_general_parameters["2"].clock_mode = SELF;
	default_general_parameters["2"].nb_of_data_bite = BITS_7;
	default_general_parameters["2"].parity = NONE;
	default_general_parameters["2"].nb_of_stop_bite = BITS_2;
	default_general_parameters["2"].lead_time = 15;
	default_general_parameters["2"].fec = FALSE;
	default_general_parameters["2"].antispoof = FALSE;
	default_general_parameters["2"].data_rate = KB64_0;
	default_general_parameters["2"].dteAnalogInterf = FALSE;
	default_general_parameters["2"].dteDigitalInterface = TRUE;
	default_general_parameters["2"].dceAnalogInterf = FALSE;
	default_general_parameters["2"].dceDigitalInterface = TRUE;

	//VOICE PLAIN
	default_general_parameters["3"].preset = 3;
	default_general_parameters["3"].operation_mode = VOICE_PLAIN;
	default_general_parameters["3"].transmission_mode = LOSHFPL;
	default_general_parameters["3"].transmission_procedure = BASEBAND;
	default_general_parameters["3"].trafic_mode = SPH;
	default_general_parameters["3"].application_type = DEFAULT_INT_VALUE_ED42;
	default_general_parameters["3"].output_selection = TXWBV11;
	default_general_parameters["3"].synchronisation_mode = SYN_SYN;
	default_general_parameters["3"].clock_mode = DCE;
	default_general_parameters["3"].nb_of_data_bite = BITS_7;
	default_general_parameters["3"].parity = NONE;
	default_general_parameters["3"].nb_of_stop_bite = BITS_1;
	default_general_parameters["3"].lead_time = 15;
	default_general_parameters["3"].fec = FALSE;
	default_general_parameters["3"].antispoof = FALSE;
	default_general_parameters["3"].data_rate = KB2_4;
	default_general_parameters["3"].dteAnalogInterf = TRUE;
	default_general_parameters["3"].dteDigitalInterface = FALSE;
	default_general_parameters["3"].dceAnalogInterf = TRUE;
	default_general_parameters["3"].dceDigitalInterface = FALSE;

	for(int i=0; i<8; i++) {
		general_parameters[PRESET_CONFIGURATION[i]] = default_general_parameters["0"];
		general_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=8; i<16; i++) {
		general_parameters[PRESET_CONFIGURATION[i]] = default_general_parameters["1"];
		general_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=16; i<24; i++) {
		general_parameters[PRESET_CONFIGURATION[i]] = default_general_parameters["2"];
		general_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=24; i<32; i++) {
		general_parameters[PRESET_CONFIGURATION[i]] = default_general_parameters["3"];
		general_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	//***********************************************************************************
	//Initialisation des défauts digital DCE parameters
	//DATA CRYPTO
	default_digitalDce_parameters["0"].preset = 0;
	default_digitalDce_parameters["0"].activateDigitalDceInterface = FALSE;
	default_digitalDce_parameters["0"].outputLevel = V10;
	default_digitalDce_parameters["0"].polarityOutputSignalTXD = FALSE;
	default_digitalDce_parameters["0"].polarityOutputSignalRTS = FALSE;
	default_digitalDce_parameters["0"].polarityOutputSignalDTR = FALSE;
	default_digitalDce_parameters["0"].polarityOutputSignalTCK = FALSE;
	default_digitalDce_parameters["0"].polarityOutputSignalRTL = FALSE;
	default_digitalDce_parameters["0"].polarityOutputSignalLTL = FALSE;
	default_digitalDce_parameters["0"].polarityInputSignalRXD = FALSE;
	default_digitalDce_parameters["0"].polarityInputSignalCTS = FALSE;
	default_digitalDce_parameters["0"].polarityInputSignalDSR = FALSE;
	default_digitalDce_parameters["0"].polarityInputSignalDCD = FALSE;
	default_digitalDce_parameters["0"].polarityInputSignalXCK = FALSE;
	default_digitalDce_parameters["0"].polarityInputSignalRCK = FALSE;
	default_digitalDce_parameters["0"].polarityInputSignalRNG = FALSE;
	default_digitalDce_parameters["0"].polarityInputSignalLLR = FALSE;

	//VOICE CRYPTO
	default_digitalDce_parameters["1"].preset = 1;
	default_digitalDce_parameters["1"].activateDigitalDceInterface = FALSE;
	default_digitalDce_parameters["1"].outputLevel = V10;
	default_digitalDce_parameters["1"].polarityOutputSignalTXD = FALSE;
	default_digitalDce_parameters["1"].polarityOutputSignalRTS = FALSE;
	default_digitalDce_parameters["1"].polarityOutputSignalDTR = FALSE;
	default_digitalDce_parameters["1"].polarityOutputSignalTCK = FALSE;
	default_digitalDce_parameters["1"].polarityOutputSignalRTL = FALSE;
	default_digitalDce_parameters["1"].polarityOutputSignalLTL = FALSE;
	default_digitalDce_parameters["1"].polarityInputSignalRXD = FALSE;
	default_digitalDce_parameters["1"].polarityInputSignalCTS = FALSE;
	default_digitalDce_parameters["1"].polarityInputSignalDSR = FALSE;
	default_digitalDce_parameters["1"].polarityInputSignalDCD = FALSE;
	default_digitalDce_parameters["1"].polarityInputSignalXCK = FALSE;
	default_digitalDce_parameters["1"].polarityInputSignalRCK = FALSE;
	default_digitalDce_parameters["1"].polarityInputSignalRNG = FALSE;
	default_digitalDce_parameters["1"].polarityInputSignalLLR = FALSE;

	//DATA PLAIN
	default_digitalDce_parameters["2"].preset = 2;
	default_digitalDce_parameters["2"].activateDigitalDceInterface = FALSE;
	default_digitalDce_parameters["2"].outputLevel = V10;
	default_digitalDce_parameters["2"].polarityOutputSignalTXD = FALSE;
	default_digitalDce_parameters["2"].polarityOutputSignalRTS = FALSE;
	default_digitalDce_parameters["2"].polarityOutputSignalDTR = FALSE;
	default_digitalDce_parameters["2"].polarityOutputSignalTCK = FALSE;
	default_digitalDce_parameters["2"].polarityOutputSignalRTL = FALSE;
	default_digitalDce_parameters["2"].polarityOutputSignalLTL = FALSE;
	default_digitalDce_parameters["2"].polarityInputSignalRXD = FALSE;
	default_digitalDce_parameters["2"].polarityInputSignalCTS = FALSE;
	default_digitalDce_parameters["2"].polarityInputSignalDSR = FALSE;
	default_digitalDce_parameters["2"].polarityInputSignalDCD = FALSE;
	default_digitalDce_parameters["2"].polarityInputSignalXCK = FALSE;
	default_digitalDce_parameters["2"].polarityInputSignalRCK = FALSE;
	default_digitalDce_parameters["2"].polarityInputSignalRNG = FALSE;
	default_digitalDce_parameters["2"].polarityInputSignalLLR = FALSE;

	//VOICE PLAIN
	default_digitalDce_parameters["3"].preset = 3;
	default_digitalDce_parameters["3"].activateDigitalDceInterface = FALSE;
	default_digitalDce_parameters["3"].outputLevel = V10;
	default_digitalDce_parameters["3"].polarityOutputSignalTXD = FALSE;
	default_digitalDce_parameters["3"].polarityOutputSignalRTS = FALSE;
	default_digitalDce_parameters["3"].polarityOutputSignalDTR = FALSE;
	default_digitalDce_parameters["3"].polarityOutputSignalTCK = FALSE;
	default_digitalDce_parameters["3"].polarityOutputSignalRTL = FALSE;
	default_digitalDce_parameters["3"].polarityOutputSignalLTL = FALSE;
	default_digitalDce_parameters["3"].polarityInputSignalRXD = FALSE;
	default_digitalDce_parameters["3"].polarityInputSignalCTS = FALSE;
	default_digitalDce_parameters["3"].polarityInputSignalDSR = FALSE;
	default_digitalDce_parameters["3"].polarityInputSignalDCD = FALSE;
	default_digitalDce_parameters["3"].polarityInputSignalXCK = FALSE;
	default_digitalDce_parameters["3"].polarityInputSignalRCK = FALSE;
	default_digitalDce_parameters["3"].polarityInputSignalRNG = FALSE;
	default_digitalDce_parameters["3"].polarityInputSignalLLR = FALSE;

	for(i=0; i<8; i++) {
		digitalDce_parameters[PRESET_CONFIGURATION[i]] = default_digitalDce_parameters["0"];
		digitalDce_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=8; i<16; i++) {
		digitalDce_parameters[PRESET_CONFIGURATION[i]] = default_digitalDce_parameters["1"];
		digitalDce_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=16; i<24; i++) {
		digitalDce_parameters[PRESET_CONFIGURATION[i]] = default_digitalDce_parameters["2"];
		digitalDce_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=24; i<32; i++) {
		digitalDce_parameters[PRESET_CONFIGURATION[i]] = default_digitalDce_parameters["3"];
		digitalDce_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

		//***********************************************************************************
	//Initialisation des défauts analog DCE parameters
	//DATA CRYPTO
	default_analogDce_parameters["0"].preset = 0;
	default_analogDce_parameters["0"].activateAnalogDceInterface = FALSE;
	default_analogDce_parameters["0"].polaritySQG = FALSE;
	default_analogDce_parameters["0"].polaritySQM = FALSE;
	default_analogDce_parameters["0"].polarityDPTT = FALSE;
	default_analogDce_parameters["0"].polarityPTT = FALSE;
	default_analogDce_parameters["0"].polarityBBDP = FALSE;
	default_analogDce_parameters["0"].polarityNBWB = FALSE;
	default_analogDce_parameters["0"].confTypeSQG = TYPE_A;
	default_analogDce_parameters["0"].confTypeSQM = TYPE_A;
	default_analogDce_parameters["0"].confTypeDPTT = TYPE_A;
	default_analogDce_parameters["0"].confTypeSQUELCH = TYPE_A;
	default_analogDce_parameters["0"].levelTXNB = 0;
	default_analogDce_parameters["0"].levelRXNB = 0;
	default_analogDce_parameters["0"].levelTXWB = 0;
	default_analogDce_parameters["0"].levelRXWB = 0;

	//VOICE CRYPTO
	default_analogDce_parameters["1"].preset = 1;
	default_analogDce_parameters["1"].activateAnalogDceInterface = FALSE;
	default_analogDce_parameters["1"].polaritySQG = FALSE;
	default_analogDce_parameters["1"].polaritySQM = FALSE;
	default_analogDce_parameters["1"].polarityDPTT = FALSE;
	default_analogDce_parameters["1"].polarityPTT = FALSE;
	default_analogDce_parameters["1"].polarityBBDP = FALSE;
	default_analogDce_parameters["1"].polarityNBWB = FALSE;
	default_analogDce_parameters["1"].confTypeSQG = TYPE_A;
	default_analogDce_parameters["1"].confTypeSQM = TYPE_A;
	default_analogDce_parameters["1"].confTypeDPTT = TYPE_A;
	default_analogDce_parameters["1"].confTypeSQUELCH = TYPE_A;
	default_analogDce_parameters["1"].levelTXNB = 0;
	default_analogDce_parameters["1"].levelRXNB = 0;
	default_analogDce_parameters["1"].levelTXWB = 0;
	default_analogDce_parameters["1"].levelRXWB = 0;

	//DATA PLAIN
	default_analogDce_parameters["2"].preset = 2;
	default_analogDce_parameters["2"].activateAnalogDceInterface = FALSE;
	default_analogDce_parameters["2"].polaritySQG = FALSE;
	default_analogDce_parameters["2"].polaritySQM = FALSE;
	default_analogDce_parameters["2"].polarityDPTT = FALSE;
	default_analogDce_parameters["2"].polarityPTT = FALSE;
	default_analogDce_parameters["2"].polarityBBDP = FALSE;
	default_analogDce_parameters["2"].polarityNBWB = FALSE;
	default_analogDce_parameters["2"].confTypeSQG = TYPE_A;
	default_analogDce_parameters["2"].confTypeSQM = TYPE_A;
	default_analogDce_parameters["2"].confTypeDPTT = TYPE_A;
	default_analogDce_parameters["2"].confTypeSQUELCH = TYPE_A;
	default_analogDce_parameters["2"].levelTXNB = 0;
	default_analogDce_parameters["2"].levelRXNB = 0;
	default_analogDce_parameters["2"].levelTXWB = 0;
	default_analogDce_parameters["2"].levelRXWB = 0;

	//VOICE PLAIN
	default_analogDce_parameters["3"].preset = 3;
	default_analogDce_parameters["3"].activateAnalogDceInterface = FALSE;
	default_analogDce_parameters["3"].polaritySQG = FALSE;
	default_analogDce_parameters["3"].polaritySQM = FALSE;
	default_analogDce_parameters["3"].polarityDPTT = FALSE;
	default_analogDce_parameters["3"].polarityPTT = FALSE;
	default_analogDce_parameters["3"].polarityBBDP = FALSE;
	default_analogDce_parameters["3"].polarityNBWB = FALSE;
	default_analogDce_parameters["3"].confTypeSQG = TYPE_A;
	default_analogDce_parameters["3"].confTypeSQM = TYPE_A;
	default_analogDce_parameters["3"].confTypeDPTT = TYPE_A;
	default_analogDce_parameters["3"].confTypeSQUELCH = TYPE_A;
	default_analogDce_parameters["3"].levelTXNB = 0;
	default_analogDce_parameters["3"].levelRXNB = 0;
	default_analogDce_parameters["3"].levelTXWB = 0;
	default_analogDce_parameters["3"].levelRXWB = 0;

	for(i=0; i<8; i++) {
		analogDce_parameters[PRESET_CONFIGURATION[i]] = default_analogDce_parameters["0"];
		analogDce_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=8; i<16; i++) {
		analogDce_parameters[PRESET_CONFIGURATION[i]] = default_analogDce_parameters["1"];
		analogDce_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=16; i<24; i++) {
		analogDce_parameters[PRESET_CONFIGURATION[i]] = default_analogDce_parameters["2"];
		analogDce_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=24; i<32; i++) {
		analogDce_parameters[PRESET_CONFIGURATION[i]] = default_analogDce_parameters["3"];
		analogDce_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

		//***********************************************************************************
	//Initialisation des défauts digital DTE parameters
	//DATA CRYPTO
	default_digitalDte_parameters["0"].preset = 0;
	default_digitalDte_parameters["0"].activateDigitalDteInterface = FALSE;
	default_digitalDte_parameters["0"].outputLevel = V10;
	default_digitalDte_parameters["0"].polarityInputSignalTXD = FALSE;
	default_digitalDte_parameters["0"].polarityInputSignalRTS = FALSE;
	default_digitalDte_parameters["0"].polarityInputSignalDTR = FALSE;
	default_digitalDte_parameters["0"].polarityInputSignalRTL = FALSE;
	default_digitalDte_parameters["0"].polarityInputSignalLTL = FALSE;
	default_digitalDte_parameters["0"].polarityOutputSignalRXD = FALSE;
	default_digitalDte_parameters["0"].polarityOutputSignalCTS = FALSE;
	default_digitalDte_parameters["0"].polarityOutputSignalDSR = FALSE;
	default_digitalDte_parameters["0"].polarityOutputSignalDCD = FALSE;
	default_digitalDte_parameters["0"].polarityOutputSignalXCK = FALSE;
	default_digitalDte_parameters["0"].polarityOutputSignalRCK = FALSE;
	default_digitalDte_parameters["0"].polarityOutputSignalRNG = FALSE;
	default_digitalDte_parameters["0"].polarityOutputSignalLLR = FALSE;

	//VOICE CRYPTO
	default_digitalDte_parameters["1"].preset = 1;
	default_digitalDte_parameters["1"].activateDigitalDteInterface = FALSE;
	default_digitalDte_parameters["1"].outputLevel = V10;
	default_digitalDte_parameters["1"].polarityInputSignalTXD = FALSE;
	default_digitalDte_parameters["1"].polarityInputSignalRTS = FALSE;
	default_digitalDte_parameters["1"].polarityInputSignalDTR = FALSE;
	default_digitalDte_parameters["1"].polarityInputSignalRTL = FALSE;
	default_digitalDte_parameters["1"].polarityInputSignalLTL = FALSE;
	default_digitalDte_parameters["1"].polarityOutputSignalRXD = FALSE;
	default_digitalDte_parameters["1"].polarityOutputSignalCTS = FALSE;
	default_digitalDte_parameters["1"].polarityOutputSignalDSR = FALSE;
	default_digitalDte_parameters["1"].polarityOutputSignalDCD = FALSE;
	default_digitalDte_parameters["1"].polarityOutputSignalXCK = FALSE;
	default_digitalDte_parameters["1"].polarityOutputSignalRCK = FALSE;
	default_digitalDte_parameters["1"].polarityOutputSignalRNG = FALSE;
	default_digitalDte_parameters["1"].polarityOutputSignalLLR = FALSE;

	//DATA PLAIN
	default_digitalDte_parameters["2"].preset = 2;
	default_digitalDte_parameters["2"].activateDigitalDteInterface = FALSE;
	default_digitalDte_parameters["2"].outputLevel = V10;
	default_digitalDte_parameters["2"].polarityInputSignalTXD = FALSE;
	default_digitalDte_parameters["2"].polarityInputSignalRTS = FALSE;
	default_digitalDte_parameters["2"].polarityInputSignalDTR = FALSE;
	default_digitalDte_parameters["2"].polarityInputSignalRTL = FALSE;
	default_digitalDte_parameters["2"].polarityInputSignalLTL = FALSE;
	default_digitalDte_parameters["2"].polarityOutputSignalRXD = FALSE;
	default_digitalDte_parameters["2"].polarityOutputSignalCTS = FALSE;
	default_digitalDte_parameters["2"].polarityOutputSignalDSR = FALSE;
	default_digitalDte_parameters["2"].polarityOutputSignalDCD = FALSE;
	default_digitalDte_parameters["2"].polarityOutputSignalXCK = FALSE;
	default_digitalDte_parameters["2"].polarityOutputSignalRCK = FALSE;
	default_digitalDte_parameters["2"].polarityOutputSignalRNG = FALSE;
	default_digitalDte_parameters["2"].polarityOutputSignalLLR = FALSE;

	//VOICE PLAIN
	default_digitalDte_parameters["3"].preset = 3;
	default_digitalDte_parameters["3"].activateDigitalDteInterface = FALSE;
	default_digitalDte_parameters["3"].outputLevel = V10;
	default_digitalDte_parameters["3"].polarityInputSignalTXD = FALSE;
	default_digitalDte_parameters["3"].polarityInputSignalRTS = FALSE;
	default_digitalDte_parameters["3"].polarityInputSignalDTR = FALSE;
	default_digitalDte_parameters["3"].polarityInputSignalRTL = FALSE;
	default_digitalDte_parameters["3"].polarityInputSignalLTL = FALSE;
	default_digitalDte_parameters["3"].polarityOutputSignalRXD = FALSE;
	default_digitalDte_parameters["3"].polarityOutputSignalCTS = FALSE;
	default_digitalDte_parameters["3"].polarityOutputSignalDSR = FALSE;
	default_digitalDte_parameters["3"].polarityOutputSignalDCD = FALSE;
	default_digitalDte_parameters["3"].polarityOutputSignalXCK = FALSE;
	default_digitalDte_parameters["3"].polarityOutputSignalRCK = FALSE;
	default_digitalDte_parameters["3"].polarityOutputSignalRNG = FALSE;
	default_digitalDte_parameters["3"].polarityOutputSignalLLR = FALSE;

	for(i=0; i<8; i++) {
		digitalDte_parameters[PRESET_CONFIGURATION[i]] = default_digitalDte_parameters["0"];
		digitalDte_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=8; i<16; i++) {
		digitalDte_parameters[PRESET_CONFIGURATION[i]] = default_digitalDte_parameters["1"];
		digitalDte_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=16; i<24; i++) {
		digitalDte_parameters[PRESET_CONFIGURATION[i]] = default_digitalDte_parameters["2"];
		digitalDte_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=24; i<32; i++) {
		digitalDte_parameters[PRESET_CONFIGURATION[i]] = default_digitalDte_parameters["3"];
		digitalDte_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	//***********************************************************************************
	//Initialisation des défauts analog DTE parameters
	//DATA CRYPTO
	default_analogDte_parameters["0"].preset = 0;
	default_analogDte_parameters["0"].activateAnalogDteInterface = FALSE;
	default_analogDte_parameters["0"].activateLocalAudioInterface = FALSE;
	default_analogDte_parameters["0"].confTypePTT42 = TYPE_A;
	default_analogDte_parameters["0"].microLevel = V3_7;
	default_analogDte_parameters["0"].phoneLevel = 0;
	default_analogDte_parameters["0"].microRi = OHM150;
	default_analogDte_parameters["0"].microSupply = FALSE;
	default_analogDte_parameters["0"].microType = TYPE_A;
	default_analogDte_parameters["0"].voltageSupply = V3_7;
	default_analogDte_parameters["0"].activateCentralAudioInterface = FALSE;
	default_analogDte_parameters["0"].confTypePTTCTR = TYPE_A;
	default_analogDte_parameters["0"].txctrLevel = 0;
	default_analogDte_parameters["0"].rxctrLevel = 0;
	default_analogDte_parameters["0"].activateMonitoring = FALSE;
	default_analogDte_parameters["0"].monitorLevel = 0;
	default_analogDte_parameters["0"].sidetoneLevel = 0;
	default_analogDte_parameters["0"].alarmeLevel = 0;
	default_analogDte_parameters["0"].txbypassLevel = 0;
	default_analogDte_parameters["0"].rxbypassLevel = 0;

	//VOICE CRYPTO
	default_analogDte_parameters["1"].preset = 1;
	default_analogDte_parameters["1"].activateAnalogDteInterface = FALSE;
	default_analogDte_parameters["1"].activateLocalAudioInterface = FALSE;
	default_analogDte_parameters["1"].confTypePTT42 = TYPE_A;
	default_analogDte_parameters["1"].microLevel = V3_7;
	default_analogDte_parameters["1"].phoneLevel = 0;
	default_analogDte_parameters["1"].microRi = OHM150;
	default_analogDte_parameters["1"].microSupply = FALSE;
	default_analogDte_parameters["1"].microType = TYPE_A;
	default_analogDte_parameters["1"].voltageSupply = V3_7;
	default_analogDte_parameters["1"].activateCentralAudioInterface = FALSE;
	default_analogDte_parameters["1"].confTypePTTCTR = TYPE_A;
	default_analogDte_parameters["1"].txctrLevel = 0;
	default_analogDte_parameters["1"].rxctrLevel = 0;
	default_analogDte_parameters["1"].activateMonitoring = FALSE;
	default_analogDte_parameters["1"].monitorLevel = 0;
	default_analogDte_parameters["1"].sidetoneLevel = 0;
	default_analogDte_parameters["1"].alarmeLevel = 0;
	default_analogDte_parameters["1"].txbypassLevel = 0;
	default_analogDte_parameters["1"].rxbypassLevel = 0;

	//DATA PLAIN
	default_analogDte_parameters["2"].preset = 2;
	default_analogDte_parameters["2"].activateAnalogDteInterface = FALSE;
	default_analogDte_parameters["2"].activateLocalAudioInterface = FALSE;
	default_analogDte_parameters["2"].confTypePTT42 = TYPE_A;
	default_analogDte_parameters["2"].microLevel = V3_7;
	default_analogDte_parameters["2"].phoneLevel = 0;
	default_analogDte_parameters["2"].microRi = OHM150;
	default_analogDte_parameters["2"].microSupply = FALSE;
	default_analogDte_parameters["2"].microType = TYPE_A;
	default_analogDte_parameters["2"].voltageSupply = V3_7;
	default_analogDte_parameters["2"].activateCentralAudioInterface = FALSE;
	default_analogDte_parameters["2"].confTypePTTCTR = TYPE_A;
	default_analogDte_parameters["2"].txctrLevel = 0;
	default_analogDte_parameters["2"].rxctrLevel = 0;
	default_analogDte_parameters["2"].activateMonitoring = FALSE;
	default_analogDte_parameters["2"].monitorLevel = 0;
	default_analogDte_parameters["2"].sidetoneLevel = 0;
	default_analogDte_parameters["2"].alarmeLevel = 0;
	default_analogDte_parameters["2"].txbypassLevel = 0;
	default_analogDte_parameters["2"].rxbypassLevel = 0;

	//VOICE PLAIN
	default_analogDte_parameters["3"].preset = 3;
	default_analogDte_parameters["3"].activateAnalogDteInterface = FALSE;
	default_analogDte_parameters["3"].activateLocalAudioInterface = FALSE;
	default_analogDte_parameters["3"].confTypePTT42 = TYPE_A;
	default_analogDte_parameters["3"].microLevel = V3_7;
	default_analogDte_parameters["3"].phoneLevel = 0;
	default_analogDte_parameters["3"].microRi = OHM150;
	default_analogDte_parameters["3"].microSupply = FALSE;
	default_analogDte_parameters["3"].microType = TYPE_A;
	default_analogDte_parameters["3"].voltageSupply = V3_7;
	default_analogDte_parameters["3"].activateCentralAudioInterface = FALSE;
	default_analogDte_parameters["3"].confTypePTTCTR = TYPE_A;
	default_analogDte_parameters["3"].txctrLevel = 0;
	default_analogDte_parameters["3"].rxctrLevel = 0;
	default_analogDte_parameters["3"].activateMonitoring = FALSE;
	default_analogDte_parameters["3"].monitorLevel = 0;
	default_analogDte_parameters["3"].sidetoneLevel = 0;
	default_analogDte_parameters["3"].alarmeLevel = 0;
	default_analogDte_parameters["3"].txbypassLevel = 0;
	default_analogDte_parameters["3"].rxbypassLevel = 0;

	for(i=0; i<8; i++) {
		analogDte_parameters[PRESET_CONFIGURATION[i]] = default_analogDte_parameters["0"];
		analogDte_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=8; i<16; i++) {
		analogDte_parameters[PRESET_CONFIGURATION[i]] = default_analogDte_parameters["1"];
		analogDte_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=16; i<24; i++) {
		analogDte_parameters[PRESET_CONFIGURATION[i]] = default_analogDte_parameters["2"];
		analogDte_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	for(i=24; i<32; i++) {
		analogDte_parameters[PRESET_CONFIGURATION[i]] = default_analogDte_parameters["3"];
		analogDte_parameters[PRESET_CONFIGURATION[i]].preset = i;
	}

	//***********************************************************************************
	// KeyManagement
	char buffer[3] ="";
	for(i=0; i<97; i++) {
		itoa(i,buffer,10);
		key_management[buffer].kekLoaded = 255;
		key_management[buffer].variableLocation = i;
		/*
		if (i == 0)
			key_management[buffer].updateCount= 255;
		else
			key_management[buffer].updateCount= 0;
		*/
		key_management[buffer].updateCount	= 255;
		key_management[buffer].days			= 00;
		key_management[buffer].months		= 00;
		key_management[buffer].years		= 00;
		key_management[buffer].hours		= 00;
		key_management[buffer].minutes		= 00;
		key_management[buffer].tag = "--------";
	}

	modifErreurPanne	= FALSE;

	modifVue			= FALSE;

	//Vérification des tag lors du chargement du context
	presetTagV = 0;
	presetTagD = 0;
}

/* **************************************************************************
METHODE :		~CEquipM1752()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquipED42::~CEquipED42()
{
}

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipED42::Allocation()
{
	t_affecte ligne;

	glob_paramsimu->Equipement(index,&ligne);

	if(proto == NULL)
	{
		proto = new CProtoED42(ligne.format,this);
	}

	if(ihm == NULL)
	{
		ihm = new CDlgED42;
	}
	
	ihm->Associe(this);
	ihm->Create(F12_IDD_ED42,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_ED42);
    

}

/* **************************************************************************
METHODE :		IsEnTest()
TRAITEMENT:
***************************************************************************	*/
bool CEquipED42::IsEnTest()
{
	return equip_en_test;
}

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipED42::Charge_Contexte(char *fichier)
{
	// TODO vérification de la validité des saisies.

	int  i = 0,
	iResult = 0,
	k = 0;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];

	char bufKey[10] = {0};
	char bufKey0[10] = {0};
	char buffer[255] = {0};

	//Vérification des tag lors du chargement du context
	presetTagV = 0;
	presetTagD = 0;

	iResult = Recup_fichier(fichier, contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation", 0);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu,"P000=",ligne,TAILLE_MAX_LIGNE);
	if(strcmp(ligne+5,"ED_42")!=0)
	{
		AjouterMessage("**** Erreur fichier non conforme à l'équipement",iResult);
		return FALSE;
	}

	// Traitement de CIK pour CIK_STATE
	iResult = Extrait_ligne(contenu,"P001=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
		ChangeCik(atoi(ligne+5),FALSE);

		//if(atoi(ligne+5) == 0)
			//ChangeCik(NO_CIK,FALSE);

	// Traitement de NL
	iResult = Extrait_ligne(contenu,"P002=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeNl(atoi(ligne+5),FALSE);

	// Traitement de EG
	iResult = Extrait_ligne(contenu,"P003=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeEg(atoi(ligne+5),FALSE);

	// Traitement de Default password
	iResult = Extrait_ligne(contenu,"P004=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeDefPassWord(ligne+5,FALSE);

	// Traitement de User password
	iResult = Extrait_ligne(contenu,"P005=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeUserPassWord(ligne+5,FALSE);

	// Traitement de Language
	iResult = Extrait_ligne(contenu,"P006=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeLanguage(atoi(ligne+5),FALSE);

	// Traitement de Update Limit
	iResult = Extrait_ligne(contenu,"P007=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeUpdateLimit(atoi(ligne+5),FALSE);

	// Traitement de Password Hold Time
	iResult = Extrait_ligne(contenu,"P008=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangePasswordHoldTime(atoi(ligne+5),FALSE);

	// Traitement de Device ID
	iResult = Extrait_ligne(contenu,"P009=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	ChangeDeviceID(atoi(ligne+5),FALSE);

	// Traitement de Interfce Key Download
	iResult = Extrait_ligne(contenu,"P010=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
		if(atoi(ligne+5) >= 1)
			SetInterfaceKeyDownload(atoi(ligne+5));
		else
			SetInterfaceKeyDownload(1);

	// Traitement de CE State - KEStatus
	iResult = Extrait_ligne(contenu,"P011=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
		SetKeStatus(atoi(ligne+5));

	// NU
	iResult = Extrait_ligne(contenu,"P012=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)


	// NU
	iResult = Extrait_ligne(contenu,"P013=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)


	// Traitement de VersionRed
	iResult = Extrait_ligne(contenu,"P014=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	SetVersionRed(ligne+5);

	// Traitement de VersionBlack
	iResult = Extrait_ligne(contenu,"P015=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	SetVersionBlack(ligne+5);

	// Traitement de VersionPldRed
	iResult = Extrait_ligne(contenu,"P016=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	SetVersionPldRed(ligne+5);

	// Traitement de VersionPldBlack
	iResult = Extrait_ligne(contenu,"P017=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	SetVersionPldBlack(ligne+5);

	// Traitement de VersionOpeDevice
	iResult = Extrait_ligne(contenu,"P018=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	SetVersionOpeDevice(ligne+5);

	// Traitement de VersionMilBus
	iResult = Extrait_ligne(contenu,"P019=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)	SetVersionMilBus(ligne+5);

	// Traitement de Remote Adress
	iResult = Extrait_ligne(contenu,"P020=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
		if(atoi(ligne+5) >= ADDRESS_MIN && atoi(ligne+5) <= ADDRESS_MAX)
			setRemoteAdress(atoi(ligne+5));
		else
			setRemoteAdress(1);

	// Traitement de Protocol Version
	iResult = Extrait_ligne(contenu,"P021=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
		setProtocolNumber(atoi(ligne+5));

	// Traitement de CIK status page 183
	iResult = Extrait_ligne(contenu,"P022=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
		SetStatusCik(atoi(ligne+5));

	// Traitement de CIK user page 183
	iResult = Extrait_ligne(contenu,"P023=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
	{
		SetUserCik(atoi(ligne+5));

		if (atoi(ligne+5) == CIK_USER_1 || atoi(ligne+5) == CIK_USER_2 || atoi(ligne+5) == CIK_USER_1_ET_2 )
			setSecureMode(CIK_MODE);
		else
			setSecureMode(NOT_DEFINED);
	}

	// Traitement de CounterCIK page 183
	iResult = Extrait_ligne(contenu,"P024=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
		SetCounterCik(atoi(ligne+5));

	// Traitement REMOTE/LF_DIG
	iResult = Extrait_ligne(contenu,"P025=",ligne,TAILLE_MAX_LIGNE);
	if(iResult>=0)
		if (atoi(ligne+5) != 9 && atoi(ligne+5) !=10)
			setRemoteMode(REMOTE);
		else
			setRemoteMode(atoi(ligne+5));

	// Key Management
	strcat(bufKey, "P10..");

	for (int ii = 0; ii<97; ii++)
	{
		if (ii < 10 )
		{
			itoa(ii,buffer,10);
			bufKey[3] = buffer[0];
			bufKey[4] = '0';
			itoa(ii,bufKey0,10);
		}
		else
		{
			itoa(ii,buffer,10);
			bufKey[2] = buffer[0];
			bufKey[3] = buffer[1];
			bufKey[4] = '0';
			itoa(ii,bufKey0,10);
		}


		// ****************
		// Gestion des clés
		//*****************
		iResult = Extrait_ligne(contenu, bufKey,ligne,TAILLE_MAX_LIGNE);
		if(iResult>=0)
		{
			TKeyManagement confKey = GetKeyManagement(bufKey0);

			confKey.kekLoaded = atoi(ligne+6);

				int iii = 1;
				itoa(iii,buffer,10);
				bufKey[4] = buffer[0];

				iResult = Extrait_ligne(contenu,bufKey,ligne,TAILLE_MAX_LIGNE);
				if(iResult>=0)
					confKey.variableLocation = atoi(ligne+6);

				iii++;
				itoa(iii,buffer,10);
				bufKey[4] = buffer[0];

				iResult = Extrait_ligne(contenu,bufKey,ligne,TAILLE_MAX_LIGNE);
				if(iResult>=0)
				{
					confKey.updateCount = atoi(ligne+6);

					if ( atoi(ligne+6) != 255)
						SetKeyMemory(1);
				}

				iii++;
				itoa(iii,buffer,10);
				bufKey[4] = buffer[0];

				iResult = Extrait_ligne(contenu,bufKey,ligne,TAILLE_MAX_LIGNE);
				if(iResult>=0)
					confKey.days = atoi(ligne+6);

				iii++;
				itoa(iii,buffer,10);
				bufKey[4] = buffer[0];

				iResult = Extrait_ligne(contenu,bufKey,ligne,TAILLE_MAX_LIGNE);
				if(iResult>=0)
					confKey.months = atoi(ligne+6);

				iii++;
				itoa(iii,buffer,10);
				bufKey[4] = buffer[0];

				iResult = Extrait_ligne(contenu,bufKey,ligne,TAILLE_MAX_LIGNE);
				if(iResult>=0)
					confKey.years = atoi(ligne+6);

				iii++;
				itoa(iii,buffer,10);
				bufKey[4] = buffer[0];

				iResult = Extrait_ligne(contenu,bufKey,ligne,TAILLE_MAX_LIGNE);
				if(iResult>=0)
					confKey.hours = atoi(ligne+6);

				iii++;
				itoa(iii,buffer,10);
				bufKey[4] = buffer[0];

				iResult = Extrait_ligne(contenu,bufKey,ligne,TAILLE_MAX_LIGNE);
				if(iResult>=0)
					confKey.minutes = atoi(ligne+6);

				iii++;
				itoa(iii,buffer,10);
				bufKey[4] = buffer[0];

				iResult = Extrait_ligne(contenu,bufKey,ligne,TAILLE_MAX_LIGNE);
				if(iResult>=0)
					confKey.tag = verifyTag(ligne+6);


			SetKeyManagement(bufKey0, confKey);
			SetKeyList(1);

			if (ii == 0)
				SetKEState(1);						// Param 28 : Flag : KE state
		}

	}

	return TRUE;
}

/* **************************************************************************
METHODE :		Sauve_Contexte()
TRAITEMENT:		Sauveagrde le contexte d'exploitation d'un fichier
***************************************************************************	*/
BOOL CEquipED42::Sauve_Contexte(char *fichier)
{
	char ligne[TAILLE_MAX_MESSAGE*2];

	char buffer[10]		= {0};
	char bufKey[10]		= {0};
	char bufKey0[10]	= {0};
	char bufKey1[10]	= {0};

	ofstream file(fichier);

	string tmp;

	AfxGetApp()->DoWaitCursor(1);

	file << "// Contexte d'exploitation d'un ED42" << endl;
	file << "// *********************************" << endl;

	strcpy(ligne,"P000=ED_42");
	file << ligne << endl;

	sprintf(ligne,"P001=%d", GetStateCik());
	file << ligne << endl;

	sprintf(ligne,"P002=%d", GetStatusNl());
	file << ligne << endl;

	sprintf(ligne,"P003=%d", GetStatusEg());
	file << ligne << endl;

	sprintf(ligne,"P004=%s", (char*)GetDefPassWord().c_str());
	file << ligne << endl;

	sprintf(ligne,"P005=%s", (char*)GetUserPassWord().c_str());
	file << ligne << endl;

	sprintf(ligne,"P006=%d", GetLanguage());
	file << ligne << endl;

	sprintf(ligne,"P007=%d", GetUpdateLimit());
	file << ligne << endl;

	sprintf(ligne,"P008=%d", GetPasswordHoldTime());
	file << ligne << endl;

	sprintf(ligne,"P009=%d", GetDeviceID());
	file << ligne << endl;

	sprintf(ligne,"P010=%d", GetInterfaceKeyDownload());
	file << ligne << endl;

	sprintf(ligne,"P011=%d", GetKeStatus());
	file << ligne << endl;

	sprintf(ligne,"P012=%s", "NU");
	file << ligne << endl;

	sprintf(ligne,"P013=%s", "NU");
	file << ligne << endl;

	sprintf(ligne,"P014=%s", (char*)GetVersionRed().c_str());
	file << ligne << endl;

	sprintf(ligne,"P015=%s", (char*)GetVersionBlack().c_str());
	file << ligne << endl;

	sprintf(ligne,"P016=%s", (char*)GetVersionPldRed().c_str());
	file << ligne << endl;

	sprintf(ligne,"P017=%s", (char*)GetVersionPldBlack().c_str());
	file << ligne << endl;

	sprintf(ligne,"P018=%s", (char*)GetVersionOpeDevice().c_str());
	file << ligne << endl;

	sprintf(ligne,"P019=%s", (char*)GetVersionMilBus().c_str());
	file << ligne << endl;

	sprintf(ligne,"P020=%d", getRemoteAdress());
	file << ligne << endl;

	sprintf(ligne,"P021=%d", getProtocolNumber());
	file << ligne << endl;

	sprintf(ligne,"P022=%d", GetStatusCik());
	file << ligne << endl;

	sprintf(ligne,"P023=%d", GetUserCik());
	file << ligne << endl;

	sprintf(ligne,"P024=%d", GetCounterCik());
	file << ligne << endl;

	sprintf(ligne,"P025=%d", getRemoteMode());
	file << ligne << endl;


	//***************
	// Key Management
	//***************
	strcat(bufKey,  "P10..");
	strcat(bufKey1, "P10..");

	for (int ii = 0; ii<97; ii++)
	{
		if (ii < 10 )
		{
			itoa(ii,buffer,10);
			bufKey[3] = buffer[0];
			bufKey[4] = '0';
			itoa(ii,bufKey0,10);
		}
		else
		{
			itoa(ii,buffer,10);
			bufKey[2] = buffer[0];
			bufKey[3] = buffer[1];
			bufKey[4] = '0';
			itoa(ii,bufKey0,10);
		}
			bufKey1[2] = bufKey[2];
			bufKey1[3] = bufKey[3];
			bufKey1[4] = bufKey[4];
			bufKey1[5] = '=';
			bufKey1[6] = '%';
			bufKey1[7] = 'd';


			TKeyManagement confKey = GetKeyManagement(bufKey0);

				sprintf(ligne, bufKey1, confKey.kekLoaded);
				file << ligne << endl;

				int iii = 1;
				itoa(iii,buffer,10);
				bufKey[4]	= buffer[0];
				bufKey1[4]	= buffer[0];

				sprintf(ligne, bufKey1, confKey.variableLocation);
				file << ligne << endl;

				iii++;
				itoa(iii,buffer,10);
				bufKey[4]	= buffer[0];
				bufKey1[4]	= buffer[0];

				sprintf(ligne, bufKey1, confKey.updateCount);
				file << ligne << endl;

				iii++;
				itoa(iii,buffer,10);
				bufKey[4]	= buffer[0];
				bufKey1[4]	= buffer[0];

				sprintf(ligne, bufKey1, confKey.days);
				file << ligne << endl;

				iii++;
				itoa(iii,buffer,10);
				bufKey[4]	= buffer[0];
				bufKey1[4]	= buffer[0];

				sprintf(ligne, bufKey1, confKey.months);
				file << ligne << endl;

				iii++;
				itoa(iii,buffer,10);
				bufKey[4]	= buffer[0];
				bufKey1[4]	= buffer[0];

				sprintf(ligne, bufKey1, confKey.years);
				file << ligne << endl;

				iii++;
				itoa(iii,buffer,10);
				bufKey[4]	= buffer[0];
				bufKey1[4]	= buffer[0];

				sprintf(ligne, bufKey1, confKey.hours);
				file << ligne << endl;

				iii++;
				itoa(iii,buffer,10);
				bufKey[4]	= buffer[0];
				bufKey1[4]	= buffer[0];

				sprintf(ligne, bufKey1, confKey.minutes);
				file << ligne << endl;

				iii++;
				itoa(iii,buffer,10);
				bufKey[4]	= buffer[0];
				bufKey1[4]	= buffer[0];
				bufKey1[7] = 's';

				sprintf(ligne, bufKey1, (char *)confKey.tag.c_str());
				file << ligne << endl;

	}
	//********************************************************************


	AfxGetApp()->DoWaitCursor(-1);

	file.close();

		return TRUE;
}

/* **************************************************************************
METHODE :		Power()
TRAITEMENT:		Mise en route de l'equipement
***************************************************************************	*/
BOOL CEquipED42::Power()
{
	BOOL	activite;
	CEquip::Power();

	activite = Actif();
	if (activite)
	{
		// Lancement des tests
		SetPanne(DEFAULT_INT_VALUE_ED42);
		//SetMarcheEd42(activite);
	} else
	{
		ReinitED42();
	}

	return activite;

}

/* **************************************************************************
METHODE :		PowerOnBit()
TRAITEMENT:		Mise en route de l'equipement
***************************************************************************	*/
int CEquipED42::PowerOnBit()
{
	int panne = 0;

	return panne;
}

/* **************************************************************************
METHODE :		Panne()
TRAITEMENT:		Retourne le numéro de la panne complète du modem,
				DEFAULT_INT_VALUE si aucune panne
***************************************************************************	*/
int CEquipED42::Panne()
{
	return panne;
}

/* **************************************************************************
METHODE :		SetPanne()
TRAITEMENT:		Change la valeur de la panne
***************************************************************************	*/
void CEquipED42::SetPanne(const int val)
{
	panne = val;
}

string CEquipED42::GetTestProgress()
{
	return this->test_progress;
}

void CEquipED42::SetTestProgress(const string test)
{
	//this->test_progress = test;
}

bool CEquipED42::ValidTestProgress(const string test)
{
	return FALSE;
}


// Presence CIK ******************************************
int CEquipED42::InfoCik() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = cik;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipED42::ChangeCik(int valeur, BOOL genere_TS)
{
	if(valeur>=NO_CIK_STATE && valeur <= WAITING_CIK_STATE)
	{
		EnterCriticalSection(&crit);
		cik = 0;
		if(valeur == VALID_CIK_STATE || valeur == WAITING_CIK_STATE)
			cik = 1;
		evolution = (evolution+1) % PLAGE_EVOLUTION;
		SetStateCik(valeur);
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,0);
		}
	}
	return valeur;
}

// ******************************************
// Infos CES - Crypto Engine State page 160
// ******************************************

// NL******************************************
int CEquipED42::InfoNl() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = nl;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}
/** \Action sur le bouton NL (zeroized).
 *
 * \param
 * \param
 * \return
 *
 */
int CEquipED42::ChangeNl(int valeur, BOOL genere_TS)
{
	int iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			nl = valeur;
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			SetStatusNl(valeur != 0);
			if(valeur == 1)
			{
				SetKeStatus(ZEROIZED);
				SetZeroizeStatus(TRUE);
			}
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,0);
		}
	}

	return iResult;
}

// EG******************************************
int CEquipED42::InfoEg() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		iResult = eg;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

int CEquipED42::ChangeEg(int valeur,BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			eg = valeur;
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			SetStatusEg(valeur != 0);
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,0);
		}
	}

	return iResult;
}

void CEquipED42::ReinitED42()
{
	SetMarcheEd42(false);
}

/* **************************************************************************
METHODE :		SetEquipement()
TRAITEMENT:		Change les parametres de l'équipement
***************************************************************************	*/
void CEquipED42::SetEquipement(const TStatus value)
{
	this->statusED42 = value;
}

/* **************************************************************************
METHODE :		GetEquipement()
TRAITEMENT:		Retourne les parametres de l'équipement
*************************************************************************** */
TStatus CEquipED42::GetEquipement()
{
	return this->statusED42;
}

/* **************************************************************************
METHODE :		GetStateCik()
TRAITEMENT:		Retourne le state de CIK
*************************************************************************** */
int CEquipED42::GetStateCik()
{
	return this->statusED42.cikState;
}

/* **************************************************************************
METHODE :		SetStateCik()
TRAITEMENT:		Set le state de CIK
*************************************************************************** */
void CEquipED42::SetStateCik(int val)
{
	this->statusED42.cikState = val;
}

/* **************************************************************************
METHODE :		GetStatusCik()
TRAITEMENT:		Retourne le status de CIK
*************************************************************************** */
int CEquipED42::GetStatusCik()
{
	return this->statusED42.cikStatus;
}

/* **************************************************************************
METHODE :		SetStatusCik()
TRAITEMENT:		Set le status de CIK
*************************************************************************** */
void CEquipED42::SetStatusCik(int val)
{
	this->statusED42.cikStatus = val;
}

/* **************************************************************************
METHODE :		GetUserCik()
TRAITEMENT:		Retourne le user de CIK
*************************************************************************** */
int CEquipED42::GetUserCik()
{
	return this->statusED42.cikUser;
}

/* **************************************************************************
METHODE :		SetUserCik()
TRAITEMENT:		Set le user de CIK
*************************************************************************** */
void CEquipED42::SetUserCik(int val)
{
	this->statusED42.cikUser = val;
}

/* **************************************************************************
METHODE :		GetCounterCik()
TRAITEMENT:		Retourne le compter de CIK
*************************************************************************** */
int CEquipED42::GetCounterCik()
{
	return this->statusED42.cikCounter;
}

/* **************************************************************************
METHODE :		SetCounterCik()
TRAITEMENT:		Set le compter de CIK
*************************************************************************** */
void CEquipED42::SetCounterCik(int val)
{
	this->statusED42.cikCounter = val;
}

/* **************************************************************************
METHODE :		GetStatusNl()
TRAITEMENT:		Retourne le status de NL
*************************************************************************** */
BOOL CEquipED42::GetStatusNl()
{
	return this->statusED42.nlStatus;
}

/* **************************************************************************
METHODE :		SetStatusNl()
TRAITEMENT:		Set le status de NL
*************************************************************************** */
void CEquipED42::SetStatusNl(bool val)
{
	this->statusED42.nlStatus = val;
}

/* **************************************************************************
METHODE :		GetZeroizeStatus()
TRAITEMENT:		Retourne le status de Zeroize
*************************************************************************** */
BOOL CEquipED42::GetZeroizeStatus()
{
	return this->statusED42.zeroizeStatus;
}

/* **************************************************************************
METHODE :		SetZeroizeStatus()
TRAITEMENT:		Set le status de Zeroize
*************************************************************************** */
void CEquipED42::SetZeroizeStatus(bool val)
{
	this->statusED42.zeroizeStatus = val;
}

/* **************************************************************************
METHODE :		GetStatusEg()
TRAITEMENT:		Retourne le status de EG
*************************************************************************** */
BOOL CEquipED42::GetStatusEg()
{
	return this->statusED42.egStatus;
}

/* **************************************************************************
METHODE :		SetStatusEg()
TRAITEMENT:		Set le status de EG
*************************************************************************** */
void CEquipED42::SetStatusEg(bool val)
{
	this->statusED42.egStatus = val;
}

/* **************************************************************************
METHODE :		SetMarcheEd42()
TRAITEMENT:		Set le status de marche
*************************************************************************** */
void CEquipED42::SetMarcheEd42(bool val)
{
	this->statusED42.marche = val;
}

/* **************************************************************************
METHODE :		GetMarcheEd42()
TRAITEMENT:		Retourne le status de NL
*************************************************************************** */
BOOL CEquipED42::GetMarcheEd42()
{
	return this->statusED42.marche;
}

/* **************************************************************************
METHODE :		SetResetEd42()
TRAITEMENT:		Set le status de marche
*************************************************************************** */
void CEquipED42::SetResetEd42(bool val)
{
	this->statusED42.RstEquip = val;
}

/* **************************************************************************
METHODE :		GetResetEd42()
TRAITEMENT:		Retourne le status de NL
*************************************************************************** */
BOOL CEquipED42::GetResetEd42()
{
	return this->statusED42.RstEquip;
}
//******************************************************************************

void CEquipED42::setRemoteAdress(const int valeur)
{
	this->statusED42.RemoteAdress = valeur;
}

void CEquipED42::setRemoteAdress(CString val)
{
	statusED42.RemoteAdress = atoi(val);
}

int CEquipED42::getRemoteAdress()
{
	return this->statusED42.RemoteAdress;
}

void CEquipED42::setRemoteStatus(const bool valeur)
{
	EnterCriticalSection(&crit);
		this->statusED42.RemoteStatus = valeur;
	LeaveCriticalSection(&crit);
}

bool CEquipED42::getRemoteStatus()
{
	return this->statusED42.RemoteStatus;
}

void CEquipED42::setRemoteMode(const int valeur)
{
	EnterCriticalSection(&crit);
		this->statusED42.RemoteMode = valeur;
	LeaveCriticalSection(&crit);
}

void  CEquipED42::setRemoteMode(CString val)
{
	this->statusED42.RemoteMode = atoi(val);
}

int CEquipED42::getRemoteMode()
{
	return this->statusED42.RemoteMode;
}

void    CEquipED42:: SetRemoteTC(const int valeur)
{
	this->statusED42.RemoteTc = valeur;
}
int     CEquipED42:: GetRemoteTC()
{
	return this->statusED42.RemoteTc;
}

void CEquipED42::setHDLCAddress(const int valeur)
{
	this->statusED42.HDLCAddress = valeur;
}

void  CEquipED42:: setHDLCAddress(CString val)
{
	this->statusED42.HDLCAddress = atoi(val);
}



int CEquipED42::getHDLCAddress()
{
	return this->statusED42.HDLCAddress;
}

int CEquipED42::ChangeDefPassWord(string valeur, BOOL genere_TS)
{
	int 	iResult = SUCCESS;

	if(valeur.length()<MDPMIN && valeur.length()>MDMMAX)
	{
		iResult = WRONG_USER_PASSWORD;
	}else
	{
		EnterCriticalSection(&crit);
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			SetDefPassWord(valeur);
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,0);
		}
	}

	return iResult;
}

string CEquipED42::GetDefPassWord()
{
	return this->statusED42.DefPassWord;
}

void CEquipED42::SetDefPassWord(string val)
{
	this->statusED42.DefPassWord = val;
}

int CEquipED42::ChangeUserPassWord(string valeur, BOOL genere_TS)
{
	int 	iResult = SUCCESS;

	if(valeur.length()<5 && valeur.length()>8)
	{
		iResult = WRONG_USER_PASSWORD;
		}else
		{
			EnterCriticalSection(&crit);
				// Icrémentation de la variable d'évoution
				evolution = (evolution+1) % PLAGE_EVOLUTION;
				SetUserPassWord(valeur);
			LeaveCriticalSection(&crit);

			if(genere_TS)
			{
				proto->AjouterTS(NULL,0);
			}
	}

	return iResult;
}

string CEquipED42::GetUserPassWord()
{
	return this->statusED42.UserPassWord;
}

void CEquipED42::SetUserPassWord(string val)
{
	this->statusED42.UserPassWord = val;
}

int CEquipED42::ChangeLanguage(int valeur, BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 1)
	{
		EnterCriticalSection(&crit);
			eg = valeur;
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			SetLanguage(valeur);
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,0);
		}
	}

	return iResult;
}

//******************************
// Update Limit §3.7.8.5
//******************************
int CEquipED42::ChangeUpdateLimit(int valeur, BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=1 && valeur <= 99)
	{
		EnterCriticalSection(&crit);
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			SetUpdateLimit(valeur);
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,0);
		}
	}

	return iResult;
}

//******************************
// Update Limit §3.7.8.9
//******************************
int CEquipED42::ChangePasswordHoldTime(int valeur, BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 99)
	{
		EnterCriticalSection(&crit);
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			SetPasswordHoldTime(valeur);
			if (valeur == 0)
				setED42Lock(FALSE);
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,0);
		}
	}

	return iResult;
}

//******************************
// Update Limit §3.7.8.7
//******************************
int CEquipED42::ChangeDeviceID(int valeur, BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=0 && valeur <= 999999)
	{
		EnterCriticalSection(&crit);
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			SetDeviceID(valeur);
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,0);
		}
	}

	return iResult;
}

//******************************
// Update Limit §3.7.5.10
//******************************
int CEquipED42::ChangeInterfaceKeyDownload(int valeur, BOOL genere_TS)
{
	int 	iResult = valeur;

	if(valeur>=1 && valeur <= 2)
	{
		EnterCriticalSection(&crit);
			// Icrémentation de la variable d'évoution
			evolution = (evolution+1) % PLAGE_EVOLUTION;
			SetInterfaceKeyDownload(valeur);
		LeaveCriticalSection(&crit);

		if(genere_TS)
		{
			proto->AjouterTS(NULL,0);
		}
	}

	return iResult;
}

int CEquipED42::GetLanguage()
{
	return this->statusED42.Language;
}

void CEquipED42::SetLanguage(int val)
{
	this->statusED42.Language = val;
}

/*
void CEquipED42::SetClavier(const bool valeur)
{
	this->statusED42.clavier = valeur;
}

BOOL CEquipED42::GetClavier()
{
	return this->statusED42.clavier;
}
*/
//*****************
// Authentification
//*****************
void CEquipED42:: setAuthentified(const bool valeur)
{
	this->statusED42.Authentified = valeur;
}

BOOL CEquipED42::getAuthentified()
{
	return this->statusED42.Authentified;
}

//******************************
// SETID, REQID §3.7.8.7
//******************************
int CEquipED42::GetDeviceID()
{
	return this->statusED42.deviceID;
}


void CEquipED42::SetDeviceID(int val)
{
	this->statusED42.deviceID = val;
}

void CEquipED42::SetDeviceID(CString val)
{
	statusED42.deviceID = atoi(val);
}

//******************************
// SETUL, REQUL §3.7.8.5
//******************************
int CEquipED42::GetUpdateLimit()
{
	return this->statusED42.updateLimit;
}


void CEquipED42::SetUpdateLimit(int val)
{
	this->statusED42.updateLimit = val;
}

//******************************
// SETHT, REQHT §3.7.8.9
//******************************
int CEquipED42::GetPasswordHoldTime()
{
	return this->statusED42.passwordHoldTime;
}

void CEquipED42::SetPasswordHoldTime(int val)
{
	this->statusED42.passwordHoldTime = val;
}

//******************************
// SETDS, REQDS §3.7.5.10
//******************************
int CEquipED42::GetInterfaceKeyDownload()
{
	return this->statusED42.interfaceKeyDownload;
}


void CEquipED42::SetInterfaceKeyDownload(int val)
{
	this->statusED42.interfaceKeyDownload = val;
}

void CEquipED42::SetInterfaceKeyDownload(CString val)
{
	statusED42.interfaceKeyDownload = atoi(val);
}
/* **************************************************************************
METHODE :		GetOperatingStatus()
TRAITEMENT:		Retourne le status de operating
*************************************************************************** */
int CEquipED42::GetOperatingStatus()
{
	return this->statusED42.operatingStatus;
}

/* **************************************************************************
METHODE :		SetOperatingStatus()
TRAITEMENT:		Set le status de operating
*************************************************************************** */
void CEquipED42::SetOperatingStatus(int val)
{
	this->statusED42.operatingStatus = val;
}

/* **************************************************************************
METHODE :		GetOperatingMode()
TRAITEMENT:		Retourne le OperatingMode
*************************************************************************** */
int CEquipED42::GetOperatingMode()
{
	return this->statusED42.operatingMode;
}

/* **************************************************************************
METHODE :		SetOperatingMode()
TRAITEMENT:		Set le OperatingMode
*************************************************************************** */
void CEquipED42::SetOperatingMode(int val)
{
	this->statusED42.operatingMode = val;
}

/* **************************************************************************
METHODE :		GetTransmissionMode()
TRAITEMENT:		Retourne le TransmissionMode
*************************************************************************** */
int CEquipED42::GetTransmissionMode()
{
	return this->statusED42.transmissionMode;
}

/* **************************************************************************
METHODE :		SetTransmissionMode()
TRAITEMENT:		Set le TransmissionMode
*************************************************************************** */
void CEquipED42::SetTransmissionMode(int val)
{
	this->statusED42.transmissionMode = val;
}

/* **************************************************************************
METHODE :		GetTransmissionProcedure()
TRAITEMENT:		Retourne le TransmissionProcedure
*************************************************************************** */
int CEquipED42::GetTransmissionProcedure()
{
	return this->statusED42.transmissionProcedure;
}

/* **************************************************************************
METHODE :		SetTransmissionProcedure()
TRAITEMENT:		Set le TransmissionMode
*************************************************************************** */
void CEquipED42::SetTransmissionProcedure(int val)
{
	this->statusED42.transmissionProcedure = val;
}

/* **************************************************************************
METHODE :		GetTraficMode()
TRAITEMENT:		Retourne le TraficMode
*************************************************************************** */
int CEquipED42::GetTraficMode()
{
	return this->statusED42.traficMode;
}

/* **************************************************************************
METHODE :		SetTraficMode()
TRAITEMENT:		Set le TraficMode
*************************************************************************** */
void CEquipED42::SetTraficMode(int val)
{
	this->statusED42.traficMode = val;
}

/* **************************************************************************
METHODE :		GetDataTransfertDevice()
TRAITEMENT:		Retourne le data transfert device
*************************************************************************** */
int CEquipED42::GetDataTransfertDevice()
{
	return this->statusED42.dataTransfertDevice;
}

/* **************************************************************************
METHODE :		SetDataTransfertDevice()
TRAITEMENT:		Set le data transfert device
*************************************************************************** */
void CEquipED42::SetDataTransfertDevice(int val)
{
	this->statusED42.dataTransfertDevice = val;
}

/* **************************************************************************
METHODE :		GetPresetList()
TRAITEMENT:		Retourne le preset list
*************************************************************************** */
int CEquipED42::GetPresetList()
{
	return this->statusED42.presetList;
}

/* **************************************************************************
METHODE :		SetPresetList()
TRAITEMENT:		Set le preset list
*************************************************************************** */
void CEquipED42::SetPresetList(string preset,char operation)
{
	/*
	La valeur de presetList est la valeur décimal des valeurs définies 
	dans la commande PSS (page 190)
	
	Exemple le preset 8 est modifié
	Presets
	31|30|29|28|27|26|25|24|23|22|21|20|19|18|17|16|15|14|13|12|11|10|09|08|07|06|05|04|03|02|01|00
	 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 0| 1| 0| 0| 0| 0| 0| 0| 0| 0

    #         0|          0|          0|          0|          0|          1|          0|          0
	
	On sauvegarde la valeur en décimal dans presetList 256
	*/
	char allPresets[33] = {0};
	int indicePreset = atoi(preset.c_str());

	if (indicePreset == 255)
	{
		this->statusED42.presetList = 0;
	}else
	{
		//Récupération de la valeur presetList dans un string en binaire 
		itoa(this->statusED42.presetList,allPresets,2);

		//Mise en place du format de la valeur binaire (32 bits)
		stringstream elementBin;
		elementBin << setfill('0') << setw(32) ;
		elementBin << allPresets;
		string result = elementBin.str();
		switch(operation)
		{
		case 'A': //Ajout d'un preset qui a été modifié
			if(result[31 - indicePreset]=='0')
			{
				this->statusED42.presetList += pow (2.0, indicePreset);
			}
			break;

		case 'S': //Suppression d'un preset qui a été modifié
			if(result[31 - indicePreset]=='1')
			{
				this->statusED42.presetList -= pow (2.0, indicePreset);
			}
			break;
		default:
			this->statusED42.presetList = 0;
			break;
		}
	}
}

/* **************************************************************************
METHODE :		GetOnlinePreset()
TRAITEMENT:		Retourne le online preset
*************************************************************************** */
int CEquipED42::GetOnlinePreset()
{
	return this->statusED42.onlinePreset;
}

/* **************************************************************************
METHODE :		SetOnlinePresetStatus()
TRAITEMENT:		Set le online preset status
*************************************************************************** */
void CEquipED42::SetOnlinePresetStatus(int val)
{
	this->statusED42.onlinePresetStatus = val;
}

/* **************************************************************************
METHODE :		GetOnlinePresetStatus()
TRAITEMENT:		Retourne le online preset status
*************************************************************************** */
int CEquipED42::GetOnlinePresetStatus()
{
	return this->statusED42.onlinePresetStatus;
}

/* **************************************************************************
METHODE :		SetOnlinePreset()
TRAITEMENT:		Set le online preset
*************************************************************************** */
void CEquipED42::SetOnlinePreset(int val)
{
	this->statusED42.onlinePreset = val;
}

/* **************************************************************************
METHODE :		GetSystemConfiguration()
TRAITEMENT:		Retourne la valeur du system configuration
*************************************************************************** */
int CEquipED42::GetSystemConfiguration()
{
	return this->statusED42.systemConfiguration;
}

/* **************************************************************************
METHODE :		SetSystemConfiguration()
TRAITEMENT:		Set la valeur du system configuration
*************************************************************************** */
void CEquipED42::SetSystemConfiguration(int val)
{
	this->statusED42.systemConfiguration = val;
}

/* **************************************************************************
METHODE :		GetKeyList()
TRAITEMENT:		Retourne la valeur du key list
*************************************************************************** */
int CEquipED42::GetKeyList()
{
	return this->statusED42.keyList;
}

/* **************************************************************************
METHODE :		SetKeyList()
TRAITEMENT:		Set la valeur du key list
*************************************************************************** */
void CEquipED42::SetKeyList(int val)
{
	this->statusED42.keyList = val;
}

/* **************************************************************************
METHODE :		GetAlarm()
TRAITEMENT:		Retourne la valeur d'alarme
*************************************************************************** */
int CEquipED42::GetAlarm()
{
	return this->statusED42.alarm;
}

/* **************************************************************************
METHODE :		SetAlarm()
TRAITEMENT:		Set la valeur d'alarme
*************************************************************************** */
void CEquipED42::SetAlarm(int val)
{
	this->statusED42.alarm = val;
}

/* **************************************************************************
METHODE :		GetError()
TRAITEMENT:		Retourne la valeur d'erreur
*************************************************************************** */
int CEquipED42::GetError()
{
	return this->statusED42.error;
}

/* **************************************************************************
METHODE :		SetError()
TRAITEMENT:		Set la valeur d'erreur
*************************************************************************** */
void CEquipED42::SetError(int val)
{
	this->statusED42.error = val;
}

/* **************************************************************************
METHODE :		GetKEState()
TRAITEMENT:		Retourne la valeur de KE state
*************************************************************************** */
int CEquipED42::GetKEState()
{
	return this->statusED42.KEState;
}

/* **************************************************************************
METHODE :		SetKEState()
TRAITEMENT:		Set la valeur de KE state
*************************************************************************** */
void CEquipED42::SetKEState(int val)
{
	this->statusED42.KEState = val;
}

/* **************************************************************************
METHODE :		GetActiveKeyState()
TRAITEMENT:		Retourne la valeur de active key state
*************************************************************************** */
int CEquipED42::GetActiveKeyState()
{
	return this->statusED42.activeKeyState;
}

/* **************************************************************************
METHODE :		SetActiveKeyState()
TRAITEMENT:		Set la valeur de active key state
*************************************************************************** */
void CEquipED42::SetActiveKeyState(int val)
{
	this->statusED42.activeKeyState = val;
}

/* **************************************************************************
METHODE :		SetActivatedKey()
TRAITEMENT:		Set la valeur de active key
*************************************************************************** */
void CEquipED42::SetActivatedKey(int val)
{
	this->statusED42.activatedKey = val;
}

/* **************************************************************************
METHODE :		GetActivatedKey()
TRAITEMENT:		Retourne la valeur de active key
*************************************************************************** */
int CEquipED42::GetActivatedKey()
{
	return this->statusED42.activatedKey;
}

/* **************************************************************************
METHODE :		GetKeyMemory()
TRAITEMENT:		Retourne la valeur de key memory
*************************************************************************** */
int CEquipED42::GetKeyMemory()
{
	return this->statusED42.keyMemory;
}

/* **************************************************************************
METHODE :		SetKeyMemory()
TRAITEMENT:		Set la valeur de key memory
*************************************************************************** */
void CEquipED42::SetKeyMemory(int val)
{
	this->statusED42.keyMemory = val;
}

/* **************************************************************************
METHODE :		GetStatusCall()
TRAITEMENT:		Retourne la valeur de call
*************************************************************************** */
int CEquipED42::GetStatusCall()
{
	return this->statusED42.statusCall;
}

/* **************************************************************************
METHODE :		SetStatusCall()
TRAITEMENT:		Set la valeur de call
*************************************************************************** */
void CEquipED42::SetStatusCall(int val)
{
	this->statusED42.statusCall = val;
}

/* **************************************************************************
METHODE :		GetStatusSync()
TRAITEMENT:		Retourne la valeur de sync
*************************************************************************** */
int CEquipED42::GetStatusSync()
{
	return this->statusED42.statusSync;
}

/* **************************************************************************
METHODE :		SetStatusSync()
TRAITEMENT:		Set la valeur de sync
*************************************************************************** */
void CEquipED42::SetStatusSync(int val)
{
	this->statusED42.statusSync = val;
}

/* **************************************************************************
METHODE :		GetStatusRx()
TRAITEMENT:		Retourne la valeur de rx
*************************************************************************** */
int CEquipED42::GetStatusRx()
{
	return this->statusED42.statusRx;
}

/* **************************************************************************
METHODE :		SetStatusRx()
TRAITEMENT:		Set la valeur de rx
*************************************************************************** */
void CEquipED42::SetStatusRx(int val)
{
	this->statusED42.statusRx = val;
}

/* **************************************************************************
METHODE :		GetStatusTx()
TRAITEMENT:		Retourne la valeur de tx
*************************************************************************** */
int CEquipED42::GetStatusTx()
{
	return this->statusED42.statusTx;
}

/* **************************************************************************
METHODE :		SetStatusTx()
TRAITEMENT:		Set la valeur de tx
*************************************************************************** */
void CEquipED42::SetStatusTx(int val)
{

	this->statusED42.statusTx = val;

	if (GetOperatingStatus() == OFFLINE )
		return;


	// Precondition Compact User Guide page 55
	if (val == 1 && (GetTransmissionMode() == DIGITAL || 
					 GetOperatingMode() == DATA_CRYPRO ) &&
					( (GetTransmissionProcedure() == V24 && 
					  (GetTraficMode() == DX || 
					   GetTraficMode() == DXD)) ||
					 GetTransmissionProcedure() == V25BIS ||
					 GetTransmissionProcedure() == X21))
	{
		SetOperatingMode(OPE_MASTER);
	}
	else {

		if (GetOnlinePreset() >=0 && GetOnlinePreset() < 8 )
			SetOperatingMode(DATA_CRYPRO);

		if (GetOnlinePreset() >=8 && GetOnlinePreset() < 16 )
			SetOperatingMode(VOICE_CRYPRO);

		if (GetOnlinePreset() >=16 && GetOnlinePreset() < 24 )
			SetOperatingMode(DATA_PLAIN);

		if (GetOnlinePreset() >=24 && GetOnlinePreset() < 32 )
			SetOperatingMode(VOICE_PLAIN);
	}
}

/* **************************************************************************
METHODE :		GetStatusBusy()
TRAITEMENT:		Retourne la valeur de busy
*************************************************************************** */
int CEquipED42::GetStatusBusy()
{
	return this->statusED42.statusBusy;
}

/* **************************************************************************
METHODE :		SetStatusBusy()
TRAITEMENT:		Set la valeur de busy
*************************************************************************** */
void CEquipED42::SetStatusBusy(int val)
{
	this->statusED42.statusBusy = val;
}

/* **************************************************************************
METHODE :		GetVersionRed()
TRAITEMENT:		Retourne la valeur de VersionRed
*************************************************************************** */
string CEquipED42::GetVersionRed()
{
	return this->statusED42.versionRed;
}

/* **************************************************************************
METHODE :		SetVersionRed()
TRAITEMENT:		Set la valeur de VersionRed
*************************************************************************** */
void CEquipED42::SetVersionRed(string val)
{
	this->statusED42.versionRed = val;
}

/* **************************************************************************
METHODE :		GetVersionBlack()
TRAITEMENT:		Retourne la valeur de VersionBlack
*************************************************************************** */
string CEquipED42::GetVersionBlack()
{
	return this->statusED42.versionBlack;
}

/* **************************************************************************
METHODE :		SetVersionBlack()
TRAITEMENT:		Set la valeur de VersionBlack
*************************************************************************** */
void CEquipED42::SetVersionBlack(string val)
{
	this->statusED42.versionBlack = val;
}

/* **************************************************************************
METHODE :		GetVersionPldRed()
TRAITEMENT:		Retourne la valeur de VersionPldRed
*************************************************************************** */
string CEquipED42::GetVersionPldRed()
{
	return this->statusED42.versionPldRed;
}

/* **************************************************************************
METHODE :		SetVersionPldRed()
TRAITEMENT:		Set la valeur de VersionPldRed
*************************************************************************** */
void CEquipED42::SetVersionPldRed(string val)
{
	this->statusED42.versionPldRed = val;
}

/* **************************************************************************
METHODE :		GetVersionPldBlack()
TRAITEMENT:		Retourne la valeur de VersionPldBlack
*************************************************************************** */
string CEquipED42::GetVersionPldBlack()
{
	return this->statusED42.versionPldBlack;
}

/* **************************************************************************
METHODE :		SetVersionPldBlack()
TRAITEMENT:		Set la valeur de VersionPldBlack
*************************************************************************** */
void CEquipED42::SetVersionPldBlack(string val)
{
	this->statusED42.versionPldBlack = val;
}

/* **************************************************************************
METHODE :		GetVersionOpeDevice()
TRAITEMENT:		Retourne la valeur de VersionOpeDevice
*************************************************************************** */
string CEquipED42::GetVersionOpeDevice()
{
	return this->statusED42.versionOperDevice;
}

/* **************************************************************************
METHODE :		SetVersionOpeDevice()
TRAITEMENT:		Set la valeur de VersionOpeDevice
*************************************************************************** */
void CEquipED42::SetVersionOpeDevice(string val)
{
	this->statusED42.versionOperDevice = val;
}


/* **************************************************************************
METHODE :		GetVersionMilBus()
TRAITEMENT:		Retourne la valeur de VersionMilBus
*************************************************************************** */
string CEquipED42::GetVersionMilBus()
{
	return this->statusED42.versionMilBus;
}

/* **************************************************************************
METHODE :		SetVersionMilBus()
TRAITEMENT:		Set la valeur de VersionMilBus
*************************************************************************** */
void CEquipED42::SetVersionMilBus(string val)
{
	this->statusED42.versionMilBus = val;
}

/* **************************************************************************
METHODE :		SetClavier()
TRAITEMENT:		Action sur une touche
***************************************************************************	*/
void CEquipED42::SetClavier(const bool valeur)
{
	this->statusED42.actionClavier = valeur;
}

/* **************************************************************************
METHODE :		GetClavier()
TRAITEMENT:		Action sur une touche ?
***************************************************************************	*/
BOOL CEquipED42::GetClavier()
{
	return this->statusED42.actionClavier;
}


/* **************************************************************************
METHODE :		setED42Lock()
TRAITEMENT:		Set la valeur de ED42Lock
*************************************************************************** */
void CEquipED42::setED42Lock(const bool valeur)
{
	this->statusED42.ED42Lock = valeur;
}

/* **************************************************************************
METHODE :		getED42Lock()
TRAITEMENT:		Retourne la valeur de ED42Lock
*************************************************************************** */
BOOL CEquipED42::getED42Lock()
{
	return this->statusED42.ED42Lock;
}

/* ***************************************************************************/

BOOL CEquipED42::ValidPreset(const int id)
{
	bool ret = FALSE;

	/*TPreset *preset_courante = &(presets_configurations[id]);

	if ((*preset_courante).analogdce[id].activateAnalogDceInterface != DEFAULT_INT_VALUE_ED42)
		{

		}
*/
	return ret;
}

/* **************************************************************************
METHODE :		GetChaineClavier()
TRAITEMENT:		Retourne la valeur de la touche
*************************************************************************** */
string CEquipED42::GetChaineClavier()
{
	return this->chaineClavier;
}
/* **************************************************************************
METHODE :		SetChaineClavier()
TRAITEMENT:		Set la valeur de la touche
*************************************************************************** */
void CEquipED42::SetChaineClavier(string val)
{
	this->chaineClavier = val;
}

/* **************************************************************************
METHODE :		DecodeError()
TRAITEMENT:		Decode une chaine de caractère en TError.
*************************************************************************** */
TError	CEquipED42::DecodeError(string val)
{
	string res="";
	int cpt =0;
	TError resultat;

	//Récupère l'indice du séparateur.
	string::size_type pos;

	//Recupère l'indice de début de chaine à traiter
	string::size_type debut = val.find_first_not_of(";");

	while(debut != string::npos)
	{
		//Recherche de la position du séparateur
		pos = val.find_first_of(";",debut);

		//Récupère la chaine à traiter
		res = val.substr(debut,pos-debut);

		switch (cpt)
			{
			case 0:
				resultat.used = (atoi(res.c_str())==1);
				cpt++;
				break;

			case 1:
				resultat.errorNumbers = atoi(res.c_str());
				cpt++;
				break;

			case 2:
				resultat.extendedCodes = atoi(res.c_str());
				cpt++;
				break;

			case 3:
				resultat.meaning=res;
				cpt++;
				break;
			}

		//Recherche du prochain indice de début de chaine
		debut = val.find_first_not_of(";",pos);
	}
	return resultat;
}

/* **************************************************************************
METHODE :		DecodeStatusError()
TRAITEMENT:		Decode une chaine de caractère en TError.
*************************************************************************** */
TStatusError	CEquipED42::DecodeStatusError(string val)
{
	string res="";
	int cpt = 0;
	TStatusError resultat;

	//Récupère l'indice du séparateur.
	string::size_type pos;

	//Recupère l'indice de début de chaine à traiter
	string::size_type debut = val.find_first_not_of(";");

	while(debut != string::npos)
	{
		//Recherche de la position du séparateur
		pos = val.find_first_of(";",debut);

		//Récupère la chaine à traiter
		res = val.substr(debut,pos-debut);

		switch (cpt)
			{
			case 0:
				resultat.used = (atoi(res.c_str())==1);
				cpt++;
				break;

			case 1:
				resultat.errorNumbers = atoi(res.c_str());
				cpt++;
				break;

			case 2:
				resultat.meaning=res;
				cpt++;
				break;
			case 3:
				resultat.nbRepeat = atoi(res.c_str());
				break;
			}

		//Recherche du prochain indice de début de chaine
		debut = val.find_first_not_of(";",pos);
	}

	return resultat;
}

/* **************************************************************************
METHODE :		EncodeError()
TRAITEMENT:		Encode TError en une chaine de caractère.
*************************************************************************** */
string	CEquipED42::EncodeError(TError val)
{
	stringstream resultat;

	resultat << val.used << ";" << val.errorNumbers << ";" << val.extendedCodes << ";" << val.meaning;

	return resultat.str();
}

/* **************************************************************************
METHODE :		EncodeStatusError()
TRAITEMENT:		Encode TStatusError en une chaine de caractère.
*************************************************************************** */
string	CEquipED42::EncodeStatusError(TStatusError val)
{
	stringstream resultat;

	resultat << val.used << ";" << val.errorNumbers << ";"  << val.meaning << ";" << val.nbRepeat;

	return resultat.str();
}

/* **************************************************************************
METHODE :		setErrors()
TRAITEMENT:		Sauvegarde le tableau des erreurs.
*************************************************************************** */

void CEquipED42::setErrors(TVectorError val)
{
	errorTab = val;
}

/* **************************************************************************
METHODE :		setStatusErrors()
TRAITEMENT:		Sauvegarde le tableau des erreurs.
*************************************************************************** */

void CEquipED42::setStatusErrors(TVectorStatusError val)
{
	statusErrorTab = val;
}
/* **************************************************************************
METHODE :		getErrors()
TRAITEMENT:		Retourne le tableau des erreurs.
*************************************************************************** */

TVectorError CEquipED42::getErrors()
{
	return errorTab;
}

/* **************************************************************************
METHODE :		getStatusErrors()
TRAITEMENT:		Retourne le tableau des status erreurs.
*************************************************************************** */

TVectorStatusError CEquipED42::getStatusErrors()
{
	return statusErrorTab;
}
/* **************************************************************************
METHODE :		setModifErreurPanne()
TRAITEMENT:		Sauvegarde si un élément d'une fenêtre a été modifié
*************************************************************************** */

void	CEquipED42::setModifErreurPanne(bool val)
{
	modifErreurPanne = val;
}

/* **************************************************************************
METHODE :		getModifErreurPanne()
TRAITEMENT:		Retourne si un élément d'une fenêtre a été modifié
*************************************************************************** */

bool	CEquipED42::getModifErreurPanne()
{
	return modifErreurPanne;
}

/* **************************************************************************
METHODE :		setModifVue()
TRAITEMENT:		Sauvegarde si un élément des différents onglets
*************************************************************************** */

void	CEquipED42::setModifVue(bool val)
{
	modifVue = val;
}

/* **************************************************************************
METHODE :		getModifVue()
TRAITEMENT:		Retourne si un élément des différents onglets a été modifiées
*************************************************************************** */

bool	CEquipED42::getModifVue()
{
	return modifVue;
}

/* **************************************************************************
METHODE :		setReceptionDonnee()
TRAITEMENT:		Sauvegarde si une donnee reçu doit mettre à jour la vue
*************************************************************************** */

void	CEquipED42::setReceptionDonnee(bool val)
{
	receptionDonnee = val;
}

/* **************************************************************************
METHODE :		getReceptionDonnee()
TRAITEMENT:		Retourne si une donnee reçu doit mettre à jour la vue
*************************************************************************** */

bool	CEquipED42::getReceptionDonnee()
{
	return receptionDonnee;
}

/* **************************************************************************
METHODE :		DecodeAlarm()
TRAITEMENT:		Decode une chaine de caractère en TAlarm.
*************************************************************************** */
TAlarm	CEquipED42::DecodeAlarm(string val)
{
	string res="";
	int cpt =0;
	TAlarm resultat;

	//Récupère l'indice du séparateur.
	string::size_type pos;

	//Recupère l'indice de début de chaine à traiter
	string::size_type debut = val.find_first_not_of(";");

	while(debut != string::npos)
	{
		//Recherche de la position du séparateur
		pos = val.find_first_of(";",debut);

		//Récupère la chaine à traiter
		res = val.substr(debut,pos-debut);

		switch (cpt)
			{
			case 0:
				resultat.used = (atoi(res.c_str())==1);
				cpt++;
				break;

			case 1:
				resultat.alarmType = atoi(res.c_str());
				cpt++;
				break;

			case 2:
				resultat.alarmNumber = atoi(res.c_str());
				cpt++;
				break;

			case 3:
				resultat.meaning=res;
				cpt++;
				break;
			}

		//Recherche du prochain indice de début de chaine
		debut = val.find_first_not_of(";",pos);
	}
	return resultat;
}

/* **************************************************************************
METHODE :		EncodeAlarm()
TRAITEMENT:		Encode TAlarm en une chaine de caractère.
*************************************************************************** */
string	CEquipED42::EncodeAlarm(TAlarm val)
{
	stringstream resultat;

	resultat << val.used << ";" << val.alarmType << ";" << val.alarmNumber << ";" << val.meaning;

	return resultat.str();
}

/* **************************************************************************
METHODE :		setAlarms()
TRAITEMENT:		Sauvegarde le tableau des alarmes.
*************************************************************************** */

void	CEquipED42::setAlarms(TVectorAlarm val)
{
	alarmTab = val;
}

/* **************************************************************************
METHODE :		getAlarms()
TRAITEMENT:		Retourne le tableau des alarmes.
*************************************************************************** */

TVectorAlarm	CEquipED42::getAlarms()
{
	return alarmTab;
}


/******************** Channel configuration ********************/
/* **************************************************************************
METHODE :		GetGeneralParameters()
TRAITEMENT:		Retourne le tableau de GeneralParameters
*************************************************************************** */
TGeneralParameters CEquipED42::GetGeneralParameters(const string id)
{
	return general_parameters[id];
}
/* **************************************************************************
METHODE :		SetGeneralParameters()
TRAITEMENT:		Set le tableau de GeneralParameters
*************************************************************************** */
void CEquipED42::SetGeneralParameters(const string id, const TGeneralParameters conf)
{
	general_parameters[id] = conf;

	SetPresetList(id,'A');
}

/* **************************************************************************
METHODE :		GetDigitalDCEParameters()
TRAITEMENT:		Retourne le tableau de DigitalDCEParameters
*************************************************************************** */
TDigitalDCE CEquipED42::GetDigitalDCEParameters(const string id)
{
	return digitalDce_parameters[id];
}
/* **************************************************************************
METHODE :		SetDigitalDCEParameters()
TRAITEMENT:		Set le tableau de DigitalDCEParameters
*************************************************************************** */
void CEquipED42::SetDigitalDCEParameters(const string id, const TDigitalDCE conf)
{
	digitalDce_parameters[id] = conf;

	SetPresetList(id,'A');
}

/* **************************************************************************
METHODE :		GetDigitalDCEParameters()
TRAITEMENT:		Retourne le tableau de DigitalDCEParameters
*************************************************************************** */
TDigitalDTE CEquipED42::GetDigitalDTEParameters(const string id)
{
	return digitalDte_parameters[id];
}
/* **************************************************************************
METHODE :		SetDigitalDTEParameters()
TRAITEMENT:		Set le tableau de DigitalDCEParameters
*************************************************************************** */
void CEquipED42::SetDigitalDTEParameters(const string id, const TDigitalDTE conf)
{
	digitalDte_parameters[id] = conf;

	SetPresetList(id,'A');
}

/* **************************************************************************
METHODE :		GetAnalogDCEParameters()
TRAITEMENT:		Retourne le tableau de AnalogDCEParameters()
*************************************************************************** */
TAnalogDCE CEquipED42::GetAnalogDCEParameters(const string id)
{
	return analogDce_parameters[id];
}
/* **************************************************************************
METHODE :		SetAnalogDCEParameters()
TRAITEMENT:		Set le tableau de AnalogDCEParameters
*************************************************************************** */
void CEquipED42::SetAnalogDCEParameters(const string id, const TAnalogDCE conf)
{
	analogDce_parameters[id] = conf;

	SetPresetList(id,'A');
}

/* **************************************************************************
METHODE :		GetAnalogDTEParameters()
TRAITEMENT:		Retourne le tableau de AnalogDTEParameters
*************************************************************************** */
TAnalogDTE CEquipED42::GetAnalogDTEParameters(const string id)
{
	return analogDte_parameters[id];
}
/* **************************************************************************
METHODE :		SetAnalogDTEParameters()
TRAITEMENT:		Set le tableau de AnalogDTEParameters
*************************************************************************** */
void CEquipED42::SetAnalogDTEParameters(const string id, const TAnalogDTE conf)
{
	analogDte_parameters[id] = conf;

	SetPresetList(id,'A');
}

/* **************************************************************************
METHODE :		GetDefaultGeneralParameters()
TRAITEMENT:		Retourne le tableau de defaultGeneralParameters
*************************************************************************** */
TGeneralParameters CEquipED42::GetDefaultGeneralParameters(const string id)
{
	return default_general_parameters[id];
}

/* **************************************************************************
METHODE :		GetDefaultDigitalDCEParameters()
TRAITEMENT:		Retourne le tableau de defaultDigitalDCEParameters
*************************************************************************** */
TDigitalDCE CEquipED42::GetDefaultDigitalDCEParameters(const string id)
{
	return default_digitalDce_parameters[id];
}

/* **************************************************************************
METHODE :		GetDefaultDigitalDTEParameters()
TRAITEMENT:		Retourne le tableau de defaultDigitalDCEParameters
*************************************************************************** */
TDigitalDTE CEquipED42::GetDefaultDigitalDTEParameters(const string id)
{
	return default_digitalDte_parameters[id];
}

/* **************************************************************************
METHODE :		GetDefaultAnalogDCEParameters()
TRAITEMENT:		Retourne le tableau de defaultAnalogDCEParameters()
*************************************************************************** */
TAnalogDCE CEquipED42::GetDefaultAnalogDCEParameters(const string id)
{
	return default_analogDce_parameters[id];
}

/* **************************************************************************
METHODE :		GetDefaultAnalogDTEParameters()
TRAITEMENT:		Retourne le tableau de defaultAnalogDTEParameters
*************************************************************************** */
TAnalogDTE CEquipED42::GetDefaultAnalogDTEParameters(const string id)
{
	return default_analogDte_parameters[id];
}

/* **************************************************************************
METHODE :		setSecureMode()
TRAITEMENT:		Set le SecureMode
*************************************************************************** */
void    CEquipED42:: setSecureMode(const int valeur)
{
	this->statusED42.secureMode = valeur;
}

/* **************************************************************************
METHODE :		getSecureMode()
TRAITEMENT:		Retourne le SecureMode
*************************************************************************** */
int    CEquipED42:: getSecureMode()
{
	return this->statusED42.secureMode;
}

/* **************************************************************************
METHODE :		SetKeStatus()
TRAITEMENT:		Set le KeStatus
*************************************************************************** */
void    CEquipED42:: SetKeStatus(const int valeur)
{
		this->statusED42.KEStatus = valeur;
}

/* **************************************************************************
METHODE :		GetKeStatus()
TRAITEMENT:		Retourne le KeStatus
*************************************************************************** */
int    CEquipED42:: GetKeStatus()
{
	return this->statusED42.KEStatus;
}

/* **************************************************************************
METHODE :		setStatusError()
TRAITEMENT:		Set la table StatusError
*************************************************************************** */
void CEquipED42::setStatusErrorTable(int errorNumber, bool val)
{
	TStatusError error;
	TVectorStatusError errorList = getStatusErrors();

	// Mise à jour de la variable used
	error = DecodeStatusError(errorList[errorNumber]);
	error.used = val;

	// Si l'erreur est FALSE, on force la variable nbRepeat à 0
	if(!val)
		error.nbRepeat = 0;

	errorList[errorNumber] = EncodeStatusError(error);
	setStatusErrors(errorList);

}

/* **************************************************************************
METHODE :		getStatusErrorTable()
TRAITEMENT:		Retourne l'état de l'errorNumber
*************************************************************************** */
BOOL CEquipED42::getStatusErrorTable(int errorNumber)
{
	TStatusError error;
	TVectorStatusError errorList = getStatusErrors();


	error = DecodeStatusError(errorList[errorNumber]);

	return error.used;
}

/* **************************************************************************
METHODE :		setStatusErrorRCS()
TRAITEMENT:		Set errorRCS, erreur permanent.
*************************************************************************** */
/*void CEquipED42::setStatusErrorRCS(bool valeur)
{
	this->statusED42.errorRCS = valeur;
}*/

/* **************************************************************************
METHODE :		getStatusErrorRCS()
TRAITEMENT:		Retourne l'état errorRCS
*************************************************************************** */
/*BOOL CEquipED42::getStatusErrorRCS()
{
	return this->statusED42.errorRCS;
}*/

/*
***************************************************************************
METHODE :		setStatusErrorMSG()
TRAITEMENT:		Set errorMSG, erreur permanent.
***************************************************************************
void CEquipED42::setStatusErrorMSG(bool valeur)
{
	this->statusED42.errorMSG = valeur;
}

**************************************************************************
METHODE :		getStatusErrorMSG()
TRAITEMENT:		Retourne l'état errorMSG
***************************************************************************
BOOL CEquipED42::getStatusErrorMSG()
{
	return this->statusED42.errorMSG;
}

*/
//**********************************************
void CEquipED42::setLastNumber(const int valeur)
{
	lastNumber = valeur;
}
int CEquipED42::getLastNumber()
{
	return lastNumber;
}

void CEquipED42::setLastMessage(string valeur)
{
	lastMessage = valeur;
}
string CEquipED42::getLastMessage()
{
	return lastMessage;
}

void CEquipED42::setRepetition(bool valeur)
{
	repetition = valeur;
}
BOOL CEquipED42::getRepetition()
{
	return repetition;
}

void CEquipED42::setErrorMSG(bool valeur)
{
	errorMSG = valeur;
}
BOOL CEquipED42::getErrorMSG()
{
	return errorMSG;
}

void CEquipED42::setErrorLF(bool valeur)
{
	errorLF = valeur;
}
BOOL CEquipED42::getErrorLF()
{
	return errorLF;
}

void CEquipED42::setErrorCR(bool valeur)
{
	errorCR = valeur;
}
BOOL CEquipED42::getErrorCR()
{
	return errorCR;
}

void CEquipED42::setPasDeReponse(bool valeur)
{
	pasDeReponse = valeur;
}
BOOL CEquipED42::getPasDeReponse()
{
	return pasDeReponse;
}

/* **************************************************************************
METHODE :		setProtocolNumber()
TRAITEMENT:		Set la version du protocol.
*************************************************************************** */
void CEquipED42::setProtocolNumber(int valeur)
{
	this->statusED42.protocolVersion = valeur;
}
/* **************************************************************************
METHODE :		getProtocolNumber()
TRAITEMENT:		Retourne la version du protocol.
**************************************************************					************* */
int CEquipED42::getProtocolNumber()
{
	return this->statusED42.protocolVersion;
}

/* **************************************************************************
METHODE :		GetKeyManagement()

TRAITEMENT:		Retourne le tableau de KeyManagement
*************************************************************************** */
TKeyManagement CEquipED42::GetKeyManagement(const string id)
{
	return key_management[id];
}
/* **************************************************************************
METHODE :		SetKeyManagement()
TRAITEMENT:		Set le tableau de KeyManagement
*************************************************************************** */
void CEquipED42::SetKeyManagement(const string id, const TKeyManagement conf)
{
	key_management[id] = conf;
}

/* **************************************************************************
METHODE :		GetCvChargement()
TRAITEMENT:		Verification du chargement du CV
*************************************************************************** */

bool CEquipED42::GetCvChargement(TKeyManagement *keyManagement)
{
	return (keyManagement->updateCount == 255);
}


/* **************************************************************************
METHODE :		GetMemoryIndexOfKey()
TRAITEMENT:		Get le Memory index of the actived key
*************************************************************************** */
int CEquipED42::GetMemoryIndexOfKey(int tmpActivePreset, int tmpPresetType)
{
	int ret = DEFAULT_INVALID_VALUE_ED42;

	if (tmpActivePreset == DEFAULT_INT_VALUE_ED42)
		return ret;

	char buffer[10] = {0};
	//char bufKey[10];
	std::string str = "--------";
	char tmpTagBufKey = 'X';
	int tmpBufKey;

	if (tmpPresetType == DATA_CRYPRO){
		tmpBufKey = tmpActivePreset ;
		tmpTagBufKey = 'D' ;

	}else if (tmpPresetType == VOICE_CRYPRO){

		tmpBufKey = tmpActivePreset - 8;
		tmpTagBufKey = 'V';
	}

	for (int i = 1; i<97; i++)
	{
		itoa(i,buffer,10);

		TKeyManagement confKey = GetKeyManagement(buffer);

		str = confKey.tag;

		for (int ii = 0; ii<8; ii++)
		{
			if ((str[ii] == tmpTagBufKey || str[ii] == 'B') && ii == tmpBufKey)
				return confKey.variableLocation;
		}
	}

	return ret;
}

TMapKeyManagement CEquipED42::GetMapKeyManagement()
{
	return key_management;
}

string CEquipED42::verifyTag(string tag)
{
	string tagV = "00000000";
	string tagD = "00000000";
	int cpt = 0;

	//Convertion en binaire
	for(cpt=0;cpt<tag.size();cpt++)
	{
		if(tag[cpt] == 'V' || tag[cpt] == 'B')
			tagV[cpt] = '1';
		if(tag[cpt] == 'D' || tag[cpt] == 'B')
			tagD[cpt] = '1';
	}

	tagV = verifyTagV(tagV);
	tagD = verifyTagD(tagD);

	//Conversion en V, D ou B.
	for(cpt=0;cpt<tag.size();cpt++)
	{
		if(tagV[cpt] == '1' && tagD[cpt] == '1')
			tag[cpt] = 'B';
		else if(tagV[cpt] == '1')
			tag[cpt] = 'V';
		else if(tagD[cpt] == '1')
			tag[cpt] = 'D';
		else
			tag[cpt] = '-';
	}
	return tag;
}

string CEquipED42::verifyTagV(string tag)
{
	char result[9]={0};
	stringstream elementBin;
	int tempTag = strtol(tag.c_str(),NULL,2);

	tempTag = (tempTag & presetTagV) ^ tempTag;

	itoa(tempTag,result,2);

	elementBin << setfill('0') << setw(8);
	elementBin << result;

	//Modification de la savegarde du preset tag.
	presetTagV = presetTagV | tempTag;

	return elementBin.str();
}

string CEquipED42::verifyTagD(string tag)
{
	char result[9]={0};
	stringstream elementBin;
	int tempTag = strtol(tag.c_str(),NULL,2);

	tempTag = (tempTag & presetTagD) ^ tempTag;

	itoa(tempTag,result,2);

	elementBin << setfill('0') << setw(8);
	elementBin << result;

	//Modification de la savegarde du preset tag.
	presetTagD = presetTagD | tempTag;

	return elementBin.str();
}

/* **************************************************************************
METHODE :		setErrorTable()
TRAITEMENT:		Set la table Error
*************************************************************************** */
void CEquipED42::setErrorTable(int errorValue, bool val)
{
	TError errorTmp;

	//Pour la commande RES
	errorTab[COMMAND_RES] = errorTab[errorValue];

	//Suppression du flag used pour toutes les erreurs
	for(int i =1;i < NB_ERROR ; i++)
	{
		errorTmp = DecodeError(errorTab[i]);
		errorTmp.used = 0;
	}

	errorTmp = DecodeError(errorTab[errorValue]);
	errorTmp.used = val;

	errorTab[errorValue] = EncodeError(errorTmp);

}

/* **************************************************************************
METHODE :		getErrorTable()
TRAITEMENT:		Retourne l'état de l'error
*************************************************************************** */
BOOL CEquipED42::getErrorTable(int errorValue)
{
	TError errorTmp;

	errorTmp = DecodeError(errorTab[errorValue]);

	return errorTmp.used;
}

/* **************************************************************************
METHODE :		setAlarmTable()
TRAITEMENT:		Set la table Alarm
*************************************************************************** */
void CEquipED42::setAlarmTable(int alarmValue, bool val)
{
	TAlarm alarmTmp;

	//Suppression du flag used pour toutes les alarmes
	for(int i =0;i < NB_ALARM ; i++)
	{
		alarmTmp = DecodeAlarm(alarmTab[i]);
		alarmTmp.used = 0;
	}

	alarmTmp = DecodeAlarm(alarmTab[alarmValue]);
	alarmTmp.used = val;

	alarmTab[alarmValue] = EncodeAlarm(alarmTmp);

}

/* **************************************************************************
METHODE :		getAlarmTable()
TRAITEMENT:		Retourne l'état de l'Alarm
*************************************************************************** */
BOOL CEquipED42::getAlarmTable(int alarmValue)
{
	TAlarm alarmTmp;

	alarmTmp = DecodeAlarm(alarmTab[alarmValue]);

	return alarmTmp.used;
}

/* **************************************************************************
METHODE :		DecodePowerBit()
TRAITEMENT:		Decode une chaine de caractère en TPowerBitError.
*************************************************************************** */
TPowerBitError	CEquipED42::DecodePowerBit(string val)
{
	string res="";
	int cpt = 0;
	TPowerBitError resultat;

	//Récupère l'indice du séparateur.
	string::size_type pos;

	//Recupère l'indice de début de chaine à traiter
	string::size_type debut = val.find_first_not_of(";");

	while(debut != string::npos)
	{
		//Recherche de la position du séparateur
		pos = val.find_first_of(";",debut);

		//Récupère la chaine à traiter
		res = val.substr(debut,pos-debut);

		switch (cpt)
			{
			case 0:
				resultat.used = (atoi(res.c_str())==1);
				cpt++;
				break;

			case 1:
				resultat.meaning=res;
				cpt++;
				break;
			}

		//Recherche du prochain indice de début de chaine
		debut = val.find_first_not_of(";",pos);
	}

	return resultat;
}

/* **************************************************************************
METHODE :		EncodePowerBit()
TRAITEMENT:		Encode TPowerBitError en une chaine de caractère.
*************************************************************************** */
string	CEquipED42::EncodePowerBit(TPowerBitError val)
{
	stringstream resultat;

	resultat << val.used  << ";"  << val.meaning;

	return resultat.str();
}

/* **************************************************************************
METHODE :		DecodeManuallyBit()
TRAITEMENT:		Decode une chaine de caractère en TManuallyBitError.
*************************************************************************** */
TManuallyBitError	CEquipED42::DecodeManuallyBit(string val)
{
	string res="";
	int cpt = 0;
	TManuallyBitError resultat;

	//Récupère l'indice du séparateur.
	string::size_type pos;

	//Recupère l'indice de début de chaine à traiter
	string::size_type debut = val.find_first_not_of(";");

	while(debut != string::npos)
	{
		//Recherche de la position du séparateur
		pos = val.find_first_of(";",debut);

		//Récupère la chaine à traiter
		res = val.substr(debut,pos-debut);

		switch (cpt)
			{
			case 0:
				resultat.used = (atoi(res.c_str())==1);
				cpt++;
				break;

			case 1:
				resultat.result=(atoi(res.c_str())==1);
				cpt++;
				break;

			case 2:
				resultat.meaning=res;
				cpt++;
				break;
			}

		//Recherche du prochain indice de début de chaine
		debut = val.find_first_not_of(";",pos);
	}

	return resultat;
}

/* **************************************************************************
METHODE :		EncodeManuallyBit()
TRAITEMENT:		Encode TManuallyBitError en une chaine de caractère.
*************************************************************************** */
string	CEquipED42::EncodeManuallyBit(TManuallyBitError val)
{
	stringstream resultat;

	resultat << val.used  << ";" << val.result << ";" << val.meaning;

	return resultat.str();
}

/* **************************************************************************
METHODE :		setPowerBitTable()
TRAITEMENT:		Set la table power on bit
*************************************************************************** */
void CEquipED42::setPowerBitTable(int errorValue, bool val)
{
	TPowerBitError bitPowerErrorTmp;

	bitPowerErrorTmp = DecodePowerBit(powerBit[errorValue]);
	bitPowerErrorTmp.used = val;

	powerBit[errorValue] = EncodePowerBit(bitPowerErrorTmp);

}

/* **************************************************************************
METHODE :		getPowerBitTable()
TRAITEMENT:		Retourne l'état du power on bit
*************************************************************************** */
BOOL CEquipED42::getPowerBitTable(int errorValue)
{
	TPowerBitError bitPowerErrorTmp;

	bitPowerErrorTmp = DecodePowerBit(powerBit[errorValue]);

	return bitPowerErrorTmp.used;
}

/* **************************************************************************
METHODE :		setBitManuallyTable()
TRAITEMENT:		Set la table bit manually
*************************************************************************** */
void CEquipED42::setBitManuallyTable(int errorValue, bool val)
{
	TManuallyBitError bitManuallyErrorTmp;

	bitManuallyErrorTmp = DecodeManuallyBit(bitManually[errorValue]);
	bitManuallyErrorTmp.used = val;

	bitManually[errorValue] = EncodeManuallyBit(bitManuallyErrorTmp);

}

/* **************************************************************************
METHODE :		getBitManuallyTable()
TRAITEMENT:		Retourne l'état du bit manually
*************************************************************************** */
BOOL CEquipED42::getBitManuallyTable(int errorValue)
{
	TManuallyBitError bitManuallyErrorTmp;

	bitManuallyErrorTmp = DecodeManuallyBit(bitManually[errorValue]);

	return bitManuallyErrorTmp.used;
}

/* **************************************************************************
METHODE :		setBitManuallyResultTable()
TRAITEMENT:		Set le resultat de table bit manually
*************************************************************************** */
void CEquipED42::setBitManuallyResultTable(int errorValue, bool val)
{
	TManuallyBitError bitManuallyErrorTmp;

	bitManuallyErrorTmp = DecodeManuallyBit(bitManually[errorValue]);
	bitManuallyErrorTmp.result = val;

	bitManually[errorValue] = EncodeManuallyBit(bitManuallyErrorTmp);

}

/* **************************************************************************
METHODE :		getBitManuallyResultTable()
TRAITEMENT:		Retourne le resultat du bit manually
*************************************************************************** */
BOOL CEquipED42::getBitManuallyResultTable(int errorValue)
{
	TManuallyBitError bitManuallyErrorTmp;

	bitManuallyErrorTmp = DecodeManuallyBit(bitManually[errorValue]);

	return bitManuallyErrorTmp.result;
}

/* **************************************************************************
METHODE :		RAZTable()
TRAITEMENT:		Efface toutes les tables
*************************************************************************** */
void		CEquipED42::RAZTable()
{
	int cpt =0;

	//Pour errorTab
	for(cpt=0;cpt<NB_ERROR;cpt++)
	{
		setErrorTable(cpt,FALSE);
	}

	//Pour alarmTab
	for(cpt=0;cpt<NB_ALARM;cpt++)
	{
		setAlarmTable(cpt,FALSE);
	}

	//Pour statusErrorTab
	for(cpt=0;cpt<NB_STATUS_ERROR;cpt++)
	{
		setStatusErrorTable(cpt,FALSE);
	}

	//Pour powerBit
	for(cpt=0;cpt<NB_ERROR_POWER_ON_BIT;cpt++)
	{
		setPowerBitTable(cpt,FALSE);
	}

	//Pour powerBit
	for(cpt=0;cpt<NB_ERROR_BIT_MANUALLY;cpt++)
	{
		setBitManuallyTable(cpt,FALSE);
	}
}

/* **************************************************************************
METHODE :		GetStatusS20()
TRAITEMENT:		Retourne le status du S20
*************************************************************************** */
int CEquipED42::GetStatusS20()
{
	return this->statusED42.statusS20;
}

/* **************************************************************************
METHODE :		SetStatusS20()
TRAITEMENT:		Set le status du S20
*************************************************************************** */
void CEquipED42::SetStatusS20(int val)
{
	this->statusED42.statusS20 = val;
}

/* **************************************************************************
METHODE :		GetCyclicalStatusRequest()
TRAITEMENT:		Retourne le CyclicalStatusRequest
*************************************************************************** */
int CEquipED42::GetCyclicalStatusRequest()
{
	return this->statusED42.CyclicalStatusRequest;
}

/* **************************************************************************
METHODE :		SetCyclicalStatusRequest()
TRAITEMENT:		Set le status du S20
*************************************************************************** */
void CEquipED42::SetCyclicalStatusRequest(int val)
{
	this->statusED42.CyclicalStatusRequest = val;
}

/* **************************************************************************
METHODE :		activationPreset()
TRAITEMENT:		Activation du preset ONLpreset
*************************************************************************** */

void CEquipED42::activationPreset(string preset)
{

	TGeneralParameters presetEnCours = GetGeneralParameters(preset);

	SetOnlinePreset(presetEnCours.preset);
	SetOperatingMode(presetEnCours.operation_mode);
	SetTransmissionMode(presetEnCours.transmission_mode);
	SetTransmissionProcedure(presetEnCours.transmission_procedure);
	SetTraficMode(presetEnCours.trafic_mode);

}


/* **************************************************************************
METHODE :		GetFullSimu()
TRAITEMENT:		
*************************************************************************** */
BOOL CEquipED42::GetFullSimu()
{
	return this->statusED42.fullSimu;
}
/* **************************************************************************
METHODE :		SetFullSimu()
TRAITEMENT:		
*************************************************************************** */
void CEquipED42::SetFullSimu(bool val)
{
	this->statusED42.fullSimu = val;
}

/* **************************************************************************
METHODE :		RazTableCle()
TRAITEMENT:		Si cle_kek = TRUE efface la cle KEK également
*************************************************************************** */

void CEquipED42::RazTableCle(bool cle_kek)
{
	TKeyManagement keyManagement;

	char buffer[3] ={0};
	int i = 1;

	if (cle_kek)
		i = 0;

	for(i;i<97;i++)
		{
			itoa(i,buffer,10);
			keyManagement = GetKeyManagement(buffer);
			if (cle_kek)
				keyManagement.kekLoaded	= 255;
			keyManagement.days			= 00;
			keyManagement.months		= 00;
			keyManagement.years			= 00;
			keyManagement.hours			= 00;
			keyManagement.minutes		= 00;
			keyManagement.updateCount	= 255;				//0; 255 : pas de clé - page 173
			keyManagement.tag			= "--------";
	
			//Sauvegarde 
			SetKeyManagement(buffer,keyManagement);

		}

		// Param 30 Flag key memory
		SetKeyMemory(0);
}