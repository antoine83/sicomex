/*************************************************************************
FICHIER :	EquipED42.h				AUTEUR : FDI
DATE DE CREATION : 05/01/2016 		DERNIERE MODIFICATION : 05/01/2016
VERSION :	1.0
ROLE :		Implémentation de la classe CEquipED42
***************************************************************************	*/

#if !defined(AFX_EQUIPED42_H__1CB55772_1888_4E2F_BE5F_7BD123A0B81F__INCLUDED_)
#define AFX_EQUIPED42_H__1CB55772_1888_4E2F_BE5F_7BD123A0B81F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "Equip.h"
#include <windows.h>

#include <string.h> 
#include <stdio.h>
#include <stdlib.h>

#include <map>
#include <string>
#include <vector>
#include <sstream>

#include "Divers\Logger.h"

using namespace std;
using namespace CPlusPlusLogging;

#define NB_BOOT_UP_BIT 6
#define NB_MANUALLY_UP_BIT 5
#define NB_STATUS 31
//#define NB_OPERATING_STATUS 5

#define NB_OP_PRAMS 4 // DataCrypto, DataPlain, VoiceCrypto, VoicePlain
#define NB_PRESETS_CONFIGURATIONS 33

#define DEFAULT_INT_VALUE_ED42		-1
#define DEFAULT_STRING_VALUE_ED42	""
#define DEFAULT_INVALID_VALUE_ED42  255

// Definition des durées
#define DUREETIMER	500
#ifdef _DEBUG
#define DUREE1S	500
#else
#define DUREE1S	1000
#endif
#define DUREE2S		DUREE1S*2
#define DUREE3S		DUREE1S*3
#define DUREE4S		DUREE1S*4
#define DUREE5S		DUREE1S*5
#define DUREE10S	DUREE1S*10
#define DUREE10R	DUREE1S*10
#define DUREE20S	DUREE1S*20
#define DUREE30S	DUREE1S*30
#define DUREE1MN	DUREE1S*60
#define DUREEBUSY	150

// Mot de passe
#define MDPMIN	5
#define MDMMAX  8

// Adresses
#define ADDRESS_MIN 1
#define ADDRESS_MAX 99


enum OPERATION_MODES {
	DATA_CRYPRO,
	VOICE_CRYPRO,
	DATA_PLAIN,
	VOICE_PLAIN,
	OPE_MASTER,
	OPE_NA,
	NB_OPERATION_MODE
};

const string OPERATION_MODES[NB_OPERATION_MODE] = {
	"DATA",
	"VOICE",
	"DATA",
	"VOICE",
	"MASTER",
	"-"
};

enum TRANSMISSION_MODES {
	LOS,
	HF,
	DIGITAL,
	VUHFANA,
	VUHFDIG,
	LOSHFPL,
	VUHFPL,
	LFDIGI,
	DIG5BIT,
	TRXM_NA,
	NB_TRANSMISSION_MODES
};

const string TRANSMISSION_MODES[NB_TRANSMISSION_MODES] = {
	"LOS",
	"HF",
	"DIGITAL",
	"VUHFANA (VHF/UHF)",
	"VUHFDIG (VHF/UHF digital)",
	"LOSHFPL (LOS/HF plain)",
	"VUHFPL (VHF/UHF plain)",
	"LFDIGI (LF digital)",
	"DIG5BIT (digital 5 bit)",
	"-"
};

const string TRANSMISSION_MODES_SHORT[NB_TRANSMISSION_MODES] = {
	"LOS",
	"HF",
	"DIGITAL",
	"VUHFANA",
	"VUHFDIG",
	"LOSHFPL",
	"VUHFPL",
	"LFDIGI",
	"DIG5BIT"
};

//Tableur de string pour le combo transmission mode en fonction l'Operation mode
//Pour DATA CRYPTO
const string TRANSMISSION_MODES_DATA_CRYPTO[4] = {
	"LOS",
	"HF",
	"DIGITAL",
	"DIG5BIT"
};

//Pour DATA PLAIN
const string TRANSMISSION_MODES_DATA_PLAIN[2] = {
	"DIGITAL",
	"DIG5BIT"
};

//Pour VOICE CRYPTO
const string TRANSMISSION_MODES_VOICE_CRYPTO[6] = {
	"LOS",
	"HF",
	"DIGITAL",
	"VUHFANA",
	"VUHFDIG",
	"LFDIGI"
};

//Pour VOICE PLAIN
const string TRANSMISSION_MODES_VOICE_PLAIN[2] = {
	"LOSHFPL",
	"VUHFPL"
};

enum TRANSMISSION_PROCEDURES {
	V24,
	V25BIS,
	X21,
	HFNETV,
	HFPTP,
	V24HA,
	BASEBAND,
	DIPHASE,
	TRXP_NA,
	NB_TRANSMISSION_PROCEDURES
};

const string TRANSMISSION_PROCEDURES[NB_TRANSMISSION_PROCEDURES] = {
	"V.24",
	"V.25BIS",
	"X.21",
	"HF NETV (HF net voice)",
	"HFPTP (HF point to point)",
	"V 24 HA (Hayes)",
	"BASEBAND",
	"DIPHASE",
	"-"
};

const string TRANSMISSION_PROCEDURES_SHORT[NB_TRANSMISSION_PROCEDURES] = {
	"V.24",
	"V.25BIS",
	"X.21",
	"HF NETV",
	"HFPTP",
	"V 24 HA",
	"BASEBAND",
	"DIPHASE"
};

//Tableau de string pour le combo transmission procedure en fonction :
//Pour	* Operation mode :		DATA CRYPTO
//		* Transmission mode :	DIGITAL
const string TRANSMISSION_PROCEDURES_DATA_CRYPTO_DIGITAL[4] = {
	"V.24",
	"V.25BIS",
	"X.21",
	"V 24 HA"
};

//Pour	* Operation mode :		DATA PLAIN et VOICE CRYPTO
//		* Transmission mode :	DIGITAL
const string TRANSMISSION_PROCEDURES_DATA_P_AND_VOICE_C_DIGITAL[1] = {
	"V.24"
};

//Pour	* Operation mode :		VOICE CRYPTO
//		* Transmission mode :	HF
const string TRANSMISSION_PROCEDURES_VOICE_CRYPTO_HF[2] = {
	"HF NETV",
	"HFPTP"
};

//Pour	* Operation mode :		VOICE CRYPTO
//		* Transmission mode :	VUHFANA et VUHFDIG
const string TRANSMISSION_PROCEDURES_VOICE_CRYPTO_VUHF[2] = {
	"BASEBAND",
	"DIPHASE"
};

enum TRAFFIC_MODES {
	DX,
	DXD,
	DXI,
	HDX,
	HAS,
	BAS,
	AAS,
	HEB,
	BEB,
	AEB,
	EPH,
	SPH,
	NATOIN,
	NATOINA,
	NATOENA,
	NATOEN,
	DLINE_M,
	DLINE_S,
	NATOOP2,
	TXM_NA,
	NB_TRAFFIC_MODES
};

const string TRAFFIC_MODES[NB_TRAFFIC_MODES] = {
	"DX",
	"DXD",
	"DXI",
	"HDX",
	"HAS",
	"BAS",
	"AAS",
	"HEB",
	"BEB",
	"AEB",
	"EPH",
	"SPH",
	"NATOIN",
	"NATOINA",
	"NATOENA",
	"NATOEN",
	"DLINE-M",
	"DLINE-S",
	"NATOOP2",
	"-"
};

//Tableau de string pour le combo traffic mode en fonction :
//Pour	* Operation mode :		DATA CRYPTO
//		* Transmission mode :	DIGITAL
//		* Transmission proc :	V.24
const string TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_V24[9] = {
	"DX",
	"DXD",
	"DXI",
	"HDX",
	"NATOIN",
	"NATOINA",
	"NATOENA",
	"NATOEN",
	"NATOOP2"
};

//Pour	* Operation mode :		DATA CRYPTO
//		* Transmission mode :	DIGITAL
//		* Transmission proc :	V.25.BIS
const string TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_V25BIS[6] = {
	"HAS",
	"BAS",
	"AAS",
	"HEB",
	"BEB",
	"AEB"
};

//Pour	* Operation mode :		DATA CRYPTO
//		* Transmission mode :	DIGITAL
//		* Transmission proc :	X.21
const string TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_X21[6] = {
	"HAS",
	"BAS",
	"HEB",
	"BEB",
	"DLINE-M",
	"DLINE-S"
};

//Pour	* Operation mode :		DATA CRYPTO
//		* Transmission mode :	DIGITAL
//		* Transmission proc :	V.24HA
const string TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_V24HA[1] = {
	"DXD"
};

//Pour	* Operation mode :		VOICE CRYPTO
//		* Transmission mode :	DIGITAL
//		* Transmission proc :	V.24
const string TRAFFIC_MODES_VOICE_CRYPTO_DIGITAL[1] = {
	"HDX"
};

//Pour	* Operation mode :		VOICE CRYPTO
//		* Transmission mode :	VUHFANA et VUHFDIG
//		* Transmission proc :	BASEBAND et DIPHASE
const string TRAFFIC_MODES_VOICE_CRYPTO_VUHF[2] = {
	"EPH",
	"SPH"
};

enum SYNC_MODES {
	SYN_SYN,
	ASY_SYN,
	ASY_ASY,
	NB_SYNC_MODES
};

const string SYNC_MODES[NB_SYNC_MODES] = {
	"SYN_SYN (sync-sync)",
	"ASY_SYN (async-sync)",
	"ASY_ASY (async-async)"
};

const string SYNC_MODES_SHORT[NB_SYNC_MODES] = {
	"SYN_SYN",
	"ASY_SYN",
	"ASY_ASY"
};

enum CLOCK_MODES {
	DCE,
	SELF,
	NB_CLOCK_MODES
};

const string CLOCK_MODES[NB_CLOCK_MODES] = {
	"DCE",
	"SELF"
};

enum NUMBERS_OF_DATA_BITS {
	BITS_5,
	BITS_7,
	BITS_8,
	NB_NUMBERS_OF_DATA_BITS
};

const string NUMBERS_OF_DATA_BITS[NB_NUMBERS_OF_DATA_BITS] = {
	"5 data bits",
	"7 data bits",
	"8 data bits"
};

const string NUMBERS_OF_DATA_BITS_SHORT[NB_NUMBERS_OF_DATA_BITS] = {
	"5",
	"7",
	"8"
};

enum PARITY_MODE {
	NONE,
	ODD,
	EVEN,
	NB_PARITY_MODE
};

const string PARITY_MODE[NB_PARITY_MODE] = {
	"NONE",
	"ODD",
	"EVEN"
};

enum NUMBERS_OF_STOP_BITS {
	BITS_1,
	BITS_2,
	NB_NUMBERS_OF_STOP_BITS
};

const string NUMBERS_OF_STOP_BITS[NB_NUMBERS_OF_STOP_BITS] = {
	"1 stop bits",
	"2 stop bits"
};

const string NUMBERS_OF_STOP_BITS_SHORT[NB_NUMBERS_OF_STOP_BITS] = {
	"1",
	"2"
};

enum OUTPUT_SELECT {
	TXWBV11,
	TXD,
	NB_OUTPUT_SELECT
};

const string OUTPUT_SELECT[NB_OUTPUT_SELECT] = {
	"TXWBV11",
	"TXD"
};

enum DATA_RATE {
	KB0_2,
	KB0_3,
	KB0_6,
	KB1_2,
	KB2_4,
	KB4_8,
	KB9_6,
	KB16_0,
	KB19_2,
	KB32_0,
	KB38_4,
	KB48_0,
	KB57_6,
	KB64_0,
	KB115_2,
	KB128_0,
	KB256_0,
	NB_DATA_RATE
};

const string DATA_RATE[NB_DATA_RATE] = {
	"0.2 kbits/s",
	"0.3 kbits/s",
	"0.6 kbits/s",
	"1.2 kbits/s",
	"2.4 kbits/s",
	"4.8 kbits/s",
	"9.6 kbits/s",
	"16.0 kbits/s",
	"19.2 kbits/s",
	"32.0 kbits/s",
	"38.4 kbits/s",
	"48.0 kbits/s",
	"57.6 kbits/s",
	"64.0 kbits/s",
	"115.2 kbits/s",
	"128.0 kbits/s",
	"256.0 kbits/s"
};

const string DATA_RATE_SHORT[NB_DATA_RATE] = {
	"0.2",
	"0.3",
	"0.6",
	"1.2",
	"2.4",
	"4.8",
	"9.6",
	"16.0",
	"19.2",
	"32.0",
	"38.4",
	"48.0",
	"57.6",
	"64.0",
	"115.2",
	"128.0",
	"256.0"
};

//Tableau de string pour le combo data rate avec avec 14 éléments possibles
const string DATA_RATE_ITEMS_14[14] = {
	"0.2",
	"0.3",
	"0.6",
	"1.2",
	"2.4",
	"4.8",
	"9.6",
	"16.0",
	"19.2",
	"32.0",
	"48.0",
	"64.0",
	"128.0",
	"256.0"
};

//Tableau de string pour le combo data rate avec avec 10 éléments possibles
const string DATA_RATE_ITEMS_10[10] = {
	"0.3",
	"0.6",
	"1.2",
	"2.4",
	"4.8",
	"9.6",
	"19.2",
	"38.4",
	"57.6",
	"115.2"
};

//Tableau de string pour le combo data rate avec avec 9 éléments possibles
const string DATA_RATE_ITEMS_9[9] = {
	"0.2",
	"0.3",
	"0.6",
	"1.2",
	"2.4",
	"4.8",
	"9.6",
	"16.0",
	"19.2"
};

//Tableau de string pour le combo data rate avec avec 7 éléments possibles
const string DATA_RATE_ITEMS_7[7] = {
	"0.2",
	"0.3",
	"0.6",
	"1.2",
	"2.4",
	"4.8",
	"9.6"
};

//Tableau de string pour le combo data rate avec avec 6 éléments possibles
const string DATA_RATE_ITEMS_6[6] = {
	"0.3",
	"0.6",
	"1.2",
	"2.4",
	"4.8",
	"9.6"
};

//Tableau de string pour le combo data rate avec avec 4 éléments possibles
const string DATA_RATE_ITEMS_4[4] = {
	"0.3",
	"0.6",
	"1.2",
	"2.4",
};

//Tableau de string pour le combo data rate avec avec 2 éléments possibles
const string DATA_RATE_ITEMS_2[2] = {
	"1.2",
	"2.4",
};

enum OUTPUT_LEVEL_DIGITAL_INTERFACE {
	V10,
	V11,
	V28,
	NB_OUTPUT_LEVEL_DIGITAL_INTERFACE
};

const string OUTPUT_LEVEL_DIGITAL_INTERFACE[NB_OUTPUT_LEVEL_DIGITAL_INTERFACE] = {
	"V.10",
	"V.11",
	"V.28"
};

enum CONFIGURATION_TYPES {
	TYPE_A,
	TYPE_B,
	TYPE_C,
	TYPE_D,
	TYPE_E,
	TYPE_F,
	TYPE_G,
	TYPE_H,
	TYPE_I,
	TYPE_K,
	TYPE_L,
	NB_CONFIGURATION_TYPES
};

const string CONFIGURATION_TYPES[NB_CONFIGURATION_TYPES] = {
	"configuration type A",
	"configuration type B",
	"configuration type C",
	"configuration type D",
	"configuration type E",
	"configuration type F",
	"configuration type G",
	"configuration type H",
	"configuration type I",
	"configuration type K",
	"configuration type L"
};

enum INTERNAL_RESISTOR {
	OHM150,
	OHM600,
	NB_INTERNAL_RESISTOR
};

const string INTERNAL_RESISTOR[NB_INTERNAL_RESISTOR] = {
	"150 Ohm",
	"600 Ohm"
};

enum MICRO_SUPPLY_VOLTAGE {
	V3_7,
	V5_0,
	V6_4,
	V7_8,
	V9_1,
	V10_5,
	V11_8,
	V13_2,
	V14_5,
	V15_9,
	V17_2,
	V20_0 = 12,
	V21_0,
	V24_0 = 15,
	NB_MICRO_SUPPLY_VOLTAGE
};

const string MICRO_SUPPLY_VOLTAGE[NB_MICRO_SUPPLY_VOLTAGE] = {
	"3.7V",
	"5.0V",
	"6.4V",
	"7.8V",
	"9.1V",
	"10.5V",
	"11.8V",
	"13.2V",
	"14.5V",
	"15.9V",
	"17.2V",
	"20.0V",
	"21.3V",
	"24.0V"
};

enum AUDIO_SELECTION {
	CENTRALAUDIO,
	LOCALAUDIO,
	NB_AUDIO_SELECTION
};

const string AUDIO_SELECTION[NB_AUDIO_SELECTION] = {
	"Central Audio",
	"Local Audio"
};

enum BOOT_UP_PANNE {
	RAM,
	FLASH,
	MODULES,
	ENCRYPT_UP,
	DECRYPT,
	INTB2,
	OK,
	NOK,
	NB_BOOT_UP_PANNE
};

const string BOOT_UP_BIT[NB_BOOT_UP_PANNE] = {
	"RAM",
	"FLASH",
	"MODULES",
	"ENCRYPT",
	"DECRYPT",
	"IntB2",
	"OK",
	"NOK"
};

const string MANUALLY_UP_BIT[NB_MANUALLY_UP_BIT] = {
	"BATTERY",
	"CONTROL_UNIT",
	"PLUGS",
	"DS101",
	"HEADSET"
};

enum LANGUAGES_SELECTION {
	GERMAIN,
	ENGLICH,
	NB_LANGUAGE_SELECTION
};

const string LANGUAGES_SELECTION[NB_LANGUAGE_SELECTION] = {
	"GERMAIN",
	"ENGLICH"
};

enum OPERATING_STATUS {
	TRAIT,						// 0
	TRAIT_G,
	TRAIT_D,
	CARTIRET,
	MA,
	SUCCESSFUL,
	INCORRECT,
	REMOTE_ONLINE,				// REMOTE_ONLINE, LOCAL_ONLINE+TAK0=REMOTE_ONLINE
	REMOTE_MODE,				// REMOTE_MODE, par un TAK0
	REMOTE,						// LOCAL_ONLINE,
	LF_DIG,						// 10
	ACTIV_LOCAL_CTRL,
	ACTIV_LOCAL_CTRL_1,
	ACTIV_LOCAL_CTRL_2,
	LOCAL,
	ED42_INITIALISATION,
	POWER_ON_BIT,
	POWER_ON_BIT_ERROR,
	ENTER_ZEROIZE_PW,
	DEF_PW,
	ENTER_USER_PW,				// 20
	USER_PW_VERIFICATION,
	VERIFICATION_ERROR,
	PLEASE_WAIT,
	LANGUAGE_SELECTION,
	OFFLINE,
	ONLINE,
	CARS,
	CARVIDE,
	ZEROIZE_ALARM,
	ZEROIZE_ALARM_C,			// 30
	ZEROIZE_ALARM_S,
	ZEROIZE_ALARM_TC,
	RESTART_WITH_RESET,
	MAIN_MENU,
	EMI_TEST,
	KEY_MANAGEMENT,
	PARAMETRIZATION,
	ACTIVATE_OPMODE,
	ED42_LOCK,
	ED42_UNLOCK,
	LOCAL_CONTROL,				// 41
	STOP_ONLINE_MODE,
	BIT,
	LOAD_CV,
	DELETE_VARIABLE,
	DISPLAY_VARIABLE,
	TAG_VARIABLE,
	UPDATE_VARIABLE,
	DELETE_CV,
	DELETE_ALL_CV,
	DISPLAY_CV,					// 51
	DISPLAY_KEK,
	CV_DATA_CRYPTO,
	CV_VOICE_CRYPTO,
	UPDATE_CV,
	BILATERAL_UPDATE,
	USER_PW,
	NB_OPERATING_STATUS
};

const string OPERATING_STATUS[NB_OPERATING_STATUS] = {
	"####################",		// 0
	"##########          ",
	"          ##########",
	"-",
	"Marche Arret",
	"SUCCESSFUL!!",
	"INCORRECT!",
	".      R        R",		// REMOTE_ONLINE, LOCAL_ONLINE+TAK0=REMOTE_ONLINE
	".      R (REMOTE)",		// REMOTE_MODE, par un TAK0
	".               R",		// REMOTE : LOCAL_ONLINE,
	"LF DIG",					// 10
	"ACTIV. LOCAL CTRL",
	"ACTIV. LOCAL CTRL",
	"ACTIV. LOCAL CTRL",
	"LOCAL",
	"ED4-2 INITIALISATION",
	"POWER ON BIT",
	"POWER ON BIT ERROR!",
	"ENTER ZEROIZE PW",
	"DEF PW:",
	"ENTER USER PW",			// 20
	"USER PW VERIFICATION",
	"VERIFICATION ERROR!",
	"PLEASE WAIT",
	"LANGUAGE SELECTION",
	"STATUS OFFLINE",
	"     ",
	"S",
	"",
	"ZEROIZE ALARM",
	"",							// 30
	"",
	"",
	"RESTART WITH RESET",
	"MAIN MENU",
	"EMI TEST SUPPORT",
	"KEY MANAGEMENT",
	"PARAMETRIZATION",
	"ACTIVATE OPMODE",
	"ED42 LOCK",
	"ED42 UNLOCK",
	"LOCAL CONTROL",			// 41
	"STOP ONLINE MODE",
	"BIT",						
	"LOAD CV",
	"DELETE VARIABLE",
	"DISPLAY VARIABLE",
	"TAG VARIABLE",
	"UPDATE VARIABLE",
	"DELETE CV",
	"DELETE ALL CV",
	"DISPLAY CV",				// 51
	"DISPLAY KEK",
	"CV DATA CRYPTO",			
	"CV VOICE CRYPTO",
	"UPDATE CV",
	"BILATERAL UPDATE",
	"USER PW"
};

/* ****************************************************************/


const string PRESET_CONFIGURATION[NB_PRESETS_CONFIGURATIONS] = {
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"10",
	"11",
	"12",
	"13",
	"14",
	"15",
	"16",
	"17",
	"18",
	"19",
	"20",
	"21",
	"22",
	"23",
	"24",
	"25",
	"26",
	"27",
	"28",
	"29",
	"30",
	"31",
	"-"
};


typedef struct
{
	int		HDLCAdress;
	int		IDStation;
	int		PwdLockTime;
	int		UpdateLimit;
	int		LeadTime;
	int		DSInterface;
	bool	RemoteStatus;
	int		AlarmtoneLevel;
	int		MonitorLevel;
	int		PhoneLevel;
	int		MicrophoneLevel;
	int		DimLevel;
}TParametres;

typedef struct
{
	bool CikPlugged;
	bool ErreurRAM;
	bool ErreurMemoireFlash;
	bool ErreurSofts;
	bool ErreurAlimentation;
	bool ErreurCryptage;
	bool ErreurBatterie;
	bool ErreurProcesseur;
	bool ErreurBoutonFW;
	bool ErreurBoutonST;
	bool ErreurDS101;
	bool ErreurCasqueEcoute;
	bool ErreurAlimInterne;
}TConfigExt;

typedef struct
{
	int		errorNumbers;
	int		extendedCodes;
	string	meaning;
	bool	used;
	int		nrCmdErr;
}TError;

typedef struct
{
	int		alarmType;
	int		alarmNumber;
	string	meaning;
	bool	used;

}TAlarm;

typedef struct
{
	int		errorNumbers;
	string	meaning;
	bool	used;
	int		nbRepeat;
	int		nrCmdErr;
}TStatusError;

typedef struct
{
	string	meaning;
	bool	used;

}TPowerBitError;

typedef struct
{
	string	meaning;
	bool	used;
	bool	result; //Résultat de l'erreur (success = FALSE, error = TRUE)

}TManuallyBitError;

enum STATUS_ERROR {
	PARITY_FRAMING,
	SYNTAX_RCS,
	MAX_MSG_LENGTH,
	UNKNOWN_COMMAND,
	NOT_REMOTE_MODE,
	CONFLICT,
	WRONG_COMMAND,
	INVALID_PARAMETER,
	NOT_ERROR,
	NB_STATUS_ERROR
};

const string STATUS_ERROR[NB_STATUS_ERROR] = {
	"PARITY FRAMING",
	"SYNTAX or RCS",
	"MAX MSG LENGTH",
	"UNKNOWN COMMAND",
	"NOT REMOTE MODE",
	"CONFLICT",
	"WRONG COMMAND",
	"INVALID PARAMETER",
	"NO ERROR"
};

enum ERROR_NUMBER_CODES {
	COMMAND_RES, //emplacement de la dernière erreur reçu (utiliser dans le RES)
	ERROR_CODES,
	F101_INTERFACE,
	F101_TIMEOUT,
	F101_ERROR_ACTION,
	NO_VARIABLE_AVAILABLE,
	WRONG_PASSWORD,
	F101_ERROR_VARIABLE,
	F101_ERROR_KEK,
	CONFIGURATION_ERROR,
	START_ERROR,
	ERROR_SOFTWARE,
	VARIABLE_NOT_DEFINED,
	UPDATE_LIMIT_EXCEEDED,
	BILATERAL_UPDATE_ERROR,
	BILATERAL_TAG_ERROR,
	WRONG_DLD_PASSWORD_USER,
	FORMAT_ERROR,
	ERROR_CONNECTING_CIK,
	VARIABLE_MANAGEMENT,
	MISSING_CIK,
	WRONG_CONDITION_CIK,
	TIMEOUT_CIK_INIT,
	ERROR_CRYPTOMODUL,
	PASSWORD_CHECK,
	NB_ERROR
};

enum ALARM_NUMBER_CODES {
	ZSS_MAMANG_CRC,
	ZSS_UNEX_SKM_STATE_STARTUP,
	KE_UNEX_SKM_STATE_INDISPOSED,
	ZSS_FLASH_MAGIC_ERROR,
	ZSS_FLASH_ERROR,
	ZSS_UNEX_SKM_STATE_IDLE,
	ZSS_ERROR_INTERFACEBIT,
	CE_SKM_TIMEOUT_AOUT,
	CE_PWDTEST_ERROR,
	CE_VAR_STAT_ERROR,
	CE_UNEX_SKM_STATE_AOUT,
	CE_UNEX_SKM_STATE_POWERON,
	CE_UNEX_SKM_STATE_INITCIK2_IDLE,
	CE_UNEX_SKM_STATE_DELCIKUSER_IDLE,
	CE_CIK_SYSTEM_ERROR,
	CE_ACTIV_ERROR_CRYSETUP,
	CE_ACTIV_ERROR_CRYSETUP2,
	CE_PREP_ERROR_COMSETUP,
	CE_UNEX_ONLINE_MODE,
	CE_START_ERROR_ONLINE,
	CE_STARTRX_ERROR_ONLINE,
	CE_STARTTX_ERROR_ONLINE,
	CRYPTOALARM_NOTL,
	CRYPTOALARM_TAMPER,
	CRYPTOALARM_GLOBAL,
	NB_ALARM
};

enum POWER_ON_BIT_ERROR {
	POWER_ON_BIT_RAM_TEST,
	POWER_ON_BIT_FLASH_MEMORY_TEST,
	POWER_ON_BIT_INTEGRITY_SOFTWARE,
	POWER_ON_BIT_CHECKING_SUPPLY_VOLTAGE,
	POWER_ON_BIT_EN_DECRYPTION_SIGNAL,
	NB_ERROR_POWER_ON_BIT
};

enum BIT_MANUALLY_ERROR {
	BIT_MANUALLY_BATTERY_TEST,
	BIT_MANUALLY_BIT_CONTROL_UNIT,
	BIT_MANUALLY_BIT_TEST_PLUGS,
	BIT_MANUALLY_BIT_DS101_TEST,
	BIT_MANUALLY_BIT_HEADSET,
	NB_ERROR_BIT_MANUALLY
};

typedef struct{
	int preset;			// 0..31
	int operation_mode;
	int transmission_mode;
	int transmission_procedure;
	int trafic_mode;
	int application_type;
	int output_selection;
	int synchronisation_mode;
	int clock_mode;
	int nb_of_data_bite;
	int parity;
	int nb_of_stop_bite;
	int lead_time;
	bool fec;
	bool antispoof;
	int data_rate;
	bool dteAnalogInterf;
	bool dteDigitalInterface;
	bool dceAnalogInterf;
	bool dceDigitalInterface;
}TGeneralParameters;

typedef struct  {
	int preset;			// 0..31
	bool activateDigitalDceInterface;
	int outputLevel;
	bool polarityOutputSignalTXD;
	bool polarityOutputSignalRTS;
	bool polarityOutputSignalDTR;
	bool polarityOutputSignalTCK;
	bool polarityOutputSignalRTL;
	bool polarityOutputSignalLTL;
	bool polarityInputSignalRXD;
	bool polarityInputSignalCTS;
	bool polarityInputSignalDSR;
	bool polarityInputSignalDCD;
	bool polarityInputSignalXCK;
	bool polarityInputSignalRCK;
	bool polarityInputSignalRNG;
	bool polarityInputSignalLLR;
}TDigitalDCE;

typedef struct  {
	int preset;			// 0..31
	bool activateAnalogDceInterface;
	bool polaritySQG;
	bool polaritySQM;
	bool polarityDPTT;
	bool polarityPTT;
	bool polarityBBDP;
	bool polarityNBWB;
	int confTypeSQG;
	int confTypeSQM;
	int confTypeDPTT;
	int confTypeSQUELCH;
	int levelTXNB;
	int levelRXNB;
	int levelTXWB;
	int levelRXWB;
}TAnalogDCE;

typedef struct  {
	int preset;			// 0..31
	bool activateDigitalDteInterface;
	int outputLevel;
	bool polarityInputSignalTXD;
	bool polarityInputSignalRTS;
	bool polarityInputSignalDTR;
	bool polarityInputSignalRTL;
	bool polarityInputSignalLTL;
	bool polarityOutputSignalRXD;
	bool polarityOutputSignalCTS;
	bool polarityOutputSignalDSR;
	bool polarityOutputSignalDCD;
	bool polarityOutputSignalXCK;
	bool polarityOutputSignalRCK;
	bool polarityOutputSignalRNG;
	bool polarityOutputSignalLLR;
}TDigitalDTE;

typedef struct  {
	int preset;			// 0..31
	bool activateAnalogDteInterface;
	bool activateLocalAudioInterface;
	int confTypePTT42;
	int microLevel;
	int phoneLevel;
	int microRi;
	bool microSupply;
	int microType;
	int voltageSupply;
	bool activateCentralAudioInterface;
	int confTypePTTCTR;
	int txctrLevel;
	int rxctrLevel;
	bool activateMonitoring;
	int monitorLevel;
	int sidetoneLevel;
	int alarmeLevel;
	int txbypassLevel;
	int rxbypassLevel;
}TAnalogDTE;


enum CIK_STATE {				// Param 8..11 de SYS
	NO_CIK_STATE,
	UNKNOWN_CIK_STATE,
	VALID_CIK_STATE,
	WAITING_CIK_STATE,
	NB_CIK_STATE
};

enum CIK_STATUS {				// CIK : page 183 - Table 47
	NO_CIK_STATUS,
	INVALID_DATA_STATUS,
	UNKNOWN_CIK_STATUS,
	OBSOLETE_CIK_STATUS,
	INVALID_USER_STATUS,
	NEW_CIK_STATUS,
	INVALID_COPY_CIK_STATUS,
	DAMAGED_CIK_STATUS,
	VALID_CIK_NOT_UPDATED_STATUS,
	VALID_CIK_STATUS,
	NB_CIK_STATUS
};

enum DS_INTERFACE {
	DS101 = 1,
	DS102,
	NB_DS_INTERFACE
};

enum CIK_USER {
	NO_CIK_USER,
	CIK_USER_1,
	CIK_USER_2,
	CIK_USER_1_ET_2,
	NB_CIK_USER
};

const string CIK_USER[NB_CIK_USER] = {
	"NO CIK",
	"CIK 1",
	"CIK 2",
	"CIK 1 et 2"
};

// *******************************************
// Key management
typedef struct{
	int kekLoaded;
	int variableLocation;			// 0..96 (0 -> pour KEK)
	int updateCount;
	int days;
	int months;
	int years;
	int hours;
	int minutes;
	string tag;
}TKeyManagement;

//***************************
// CES : Crypto Engine Status - CE_STATE
enum KE_STATUS {
	ADU0,
	ADU1,
	TAMPER,
	ALARM,
	NO_SECURE_SYSTEM,
	ADU5,
	ADU6,
	ADU7,
	ZEROIZED,
	ADU9,
	ADU10,
	NO_CIK_SET_UP,
	ADU12,
	ADU13,
	CIK_NOT_PLUGED,
	ADU15,
	ADU16,
	ADU17,
	KE_IDLE,
	NB_KE_STATE
};

enum SECURE_MODE {
	NOT_DEFINED,
	LOCK_MODE,
	CIK_MODE,
	NB_SECURE_MODE
};

enum REMOTE_MODE {
	REMOTE_TC,
	LOCAL_TC,
	REMOTE_TC_A,
	MODE_NA,
	NB_REMOTE_MODE
};
/**************************


//***************************
/* Definition types struct */
//***************************
struct TStatus {
	bool marche;
	bool RstEquip;
	bool RstEquipTc;
	bool RemoteStatus;					// True = remote; False = local..
	int RemoteMode;						// REMOTE ou LF DIG si LF DIG pas de TC/TS possible
	int RemoteTc;						// REMOTE = 0, LOCAL = 1. Ainsi que pour param 16 dans SYS. Gestion par TAK0 et CTRL_LOCAL
	int RemoteAdress;
	int HDLCAddress;
	bool Authentified;
	string DefPassWord;
	string UserPassWord;
	int Language;
	bool ED42Lock;
	int operatingStatus;
	//string transmitStatus;
	//string receiveStatus;
	int cikState;					//CIK utilisé pour le SYS parm : 8 à 11
	int cikStatus;					//CIK utilisé pour le CIK Page 183/184 tableau 47
	int cikUser;
	int cikCounter;					//Compteur d'activités sur la programmation du CIK
	int KEState;					// Pour le SYS param : 28 (0 = KE state in unchanged, 1 = KE state has been changed).
	int KEStatus;					// Pour le CES (page 165) par le tableau 39 page 160 (TAMPER, ALARM.....).
	bool nlStatus;
	bool zeroizeStatus;
	bool egStatus;
	//int activePreset;
	int operatingMode;
	int transmissionMode;
	int transmissionProcedure;
	int traficMode;
	//int dateRate;
	//string memoryLocation;
	//string name;
	//string tageState;
	//string updateState;
	int updateLimit;
	int dataTransfertDevice;
	int passwordHoldTime;
	//string activationState;
	int deviceID;
	int interfaceKeyDownload;
	int presetList;
	int onlinePreset;
	int onlinePresetStatus;
	int systemConfiguration;
	int keyList;
	int alarm;
	int error;
	int activeKeyState;
	int activatedKey;
	int keyMemory;
	int statusCall;
	int statusSync;
	int statusRx;
	int statusTx;
	int statusBusy;
	int dureeBussy;
	string versionRed;
	string versionBlack;
	string versionPldRed;
	string versionPldBlack;
	string versionOperDevice;
	string versionMilBus;
	BOOL actionClavier;
	int secureMode;
	//bool errorRCS;
	//bool errorMSG;
	int protocolVersion;
	int CyclicalStatusRequest;
	BOOL fullSimu;

	int statusS20;	//Variable qui permet de vérifier si on a initialisé l'équipement lors 
					//d'un réponse avec S#20 (il y a exécution ou non exécution des commandes)
	int zeroizePassWord;
	int nrCommandInError;

	TStatus()
	{
		marche = false;
		RstEquip = false;
		RstEquipTc = false;
		RemoteStatus = false;
		RemoteMode = REMOTE;
		RemoteTc = LOCAL_TC; 
		RemoteAdress = 1;
		HDLCAddress = 127;
		Authentified = false;
		DefPassWord = DEFAULT_STRING_VALUE_ED42;
		UserPassWord = DEFAULT_STRING_VALUE_ED42;
		Language = 0;
		ED42Lock = FALSE;
		operatingStatus = MA;
		//transmitStatus	= DEFAULT_STRING_VALUE_ED42;
		//receiveStatus	= DEFAULT_STRING_VALUE_ED42;
		cikState = NO_CIK_STATE;
		cikStatus = NO_CIK_STATUS;
		cikUser = NO_CIK_USER;
		cikCounter = 0;
		KEState = 0;
		KEStatus = CIK_NOT_PLUGED;
		nlStatus = false;
		egStatus = false;
		zeroizeStatus = false;
		//activePreset = DEFAULT_INT_VALUE_ED42;
		operatingMode = OPE_NA;
		transmissionMode = DEFAULT_INT_VALUE_ED42;
		transmissionProcedure = DEFAULT_INT_VALUE_ED42;
		traficMode = DEFAULT_INT_VALUE_ED42;
		//dateRate = DEFAULT_INT_VALUE_ED42;
		//memoryLocation= DEFAULT_STRING_VALUE_ED42;
		//name= DEFAULT_STRING_VALUE_ED42;
		//tageState= DEFAULT_STRING_VALUE_ED42;
		//updateState= DEFAULT_STRING_VALUE_ED42;
		updateLimit = 0;
		dataTransfertDevice = 0;
		passwordHoldTime = 0;
		//activationState= DEFAULT_STRING_VALUE_ED42;
		deviceID= DEFAULT_INT_VALUE_ED42;
		interfaceKeyDownload = DS102;
		presetList = 0;
		onlinePreset = DEFAULT_INVALID_VALUE_ED42;
		onlinePresetStatus = 0;			// 0 si pas de changement;
		systemConfiguration =0;
		keyList = 0;
		alarm = 0;
		error = 0;
		
		activeKeyState = 0;
		activatedKey = DEFAULT_INVALID_VALUE_ED42;
		keyMemory = 0;

		statusCall = 0;
		statusSync = 0;
		statusRx = 0;
		statusTx = 0;
		statusBusy = 0;
		dureeBussy = 0;
		versionRed= DEFAULT_STRING_VALUE_ED42;
		versionBlack= DEFAULT_STRING_VALUE_ED42;
		versionPldRed= DEFAULT_STRING_VALUE_ED42;
		versionPldBlack= DEFAULT_STRING_VALUE_ED42;
		versionOperDevice= DEFAULT_STRING_VALUE_ED42;
		versionMilBus= DEFAULT_STRING_VALUE_ED42;
		actionClavier = false;
		
		secureMode = NOT_DEFINED;
		//errorRCS = FALSE;
		//errorMSG = FALSE;
		protocolVersion		= 4;
		CyclicalStatusRequest = DUREE1MN*5;
		fullSimu = TRUE;
		statusS20			= 3;
		zeroizePassWord		= 2;
		nrCommandInError	= 0;
	}

};

typedef map<string, TGeneralParameters> TMapGeneralParameters;
typedef map<string, TDigitalDCE> TMapDigitalDCE;
typedef map<string, TDigitalDTE> TMapDigitalDTE;
typedef map<string, TAnalogDCE> TMapAnalogDCE;
typedef map<string, TAnalogDTE> TMapAnalogDTE;

int ExtractDataEd42(istringstream &data, string res[], int length, char sep = ';');
string IntToStringEd42(int value, int size, bool sign = FALSE);

typedef vector<string> TVectorError;
typedef vector<string> TVectorAlarm;
typedef vector<string> TVectorStatusError;

typedef vector<string> TVectorPowerBit;
typedef vector<string> TVectorBitManually;

typedef map<string, TKeyManagement> TMapKeyManagement;

class CEquipED42:public CEquip
{

protected:
	CPort		ligne;
	int		panne;				// panne global de l'équipement nécessitant un redémarrage
	int		incident;			// -1=permanent,sinon de 0 à 99
	string	test_progress;
	int		local;				// 0=LOC, 1=RMT;
	int		cik;				// Présence CIK
	int		nl;				// Présence NL
	int		eg;				// Présence EG

	//************************************
	int niveauTrace;

	//*****************************************************
	int NumPreset;
	TConfigExt configExt;
	bool Authentified;
	int	DimLevel;
	int RemoteAdress;
	int indx;
	int indexId;
	int idx;

	bool equip_en_test;		// valeur globale indiquant si un test se déroule

	//*******************************************************
	// configuration equipement
	TStatus statusED42;
    TMapKeyManagement key_management;

	TMapGeneralParameters	general_parameters;
	TMapDigitalDCE			digitalDce_parameters;
	TMapDigitalDTE			digitalDte_parameters;
	TMapAnalogDCE			analogDce_parameters;
	TMapAnalogDTE			analogDte_parameters;

	//Default preset
	TMapGeneralParameters	default_general_parameters;
	TMapDigitalDCE			default_digitalDce_parameters;
	TMapDigitalDTE			default_digitalDte_parameters;
	TMapAnalogDCE			default_analogDce_parameters;
	TMapAnalogDTE			default_analogDte_parameters;

	//Liste des erreurs
	TVectorError errorTab;

	//Liste des alarmes
	TVectorAlarm alarmTab;

	//Liste des status erreurs
	TVectorStatusError statusErrorTab;

	//Liste des erreurs pour power on bit.
	TVectorPowerBit powerBit;

	//Liste des erreurs pour bit manually.
	TVectorBitManually bitManually;

	bool modifErreurPanne; //vérifie si une valeur des fenêtres est modifiée.

	bool modifVue; //vérifie si une valeur des différents onglets ont été modifiées.

	bool receptionDonnee; //Vérifie si on doit mettre à jour une vue apres réception d'une donnée.

	string chaineClavier;

	// Traitement message number page 158
	int lastNumber;
	string lastMessage;
	bool repetition;
	bool errorMSG;
	bool errorLF;
	bool errorCR;
	bool pasDeReponse;

	//Vérification si les presets ont été taggés
	int presetTagV;
	int presetTagD;

public:
	Logger* pLogger;



/* **************************************************************************
METHODE :		CEquipED42()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquipED42(int idx);

/* **************************************************************************
METHODE :		~CEquipED42()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	virtual ~CEquipED42();

	/* **************************************************************************
	METHODE :		Allocation()
	TRAITEMENT:		Alloue le protocole de communication et l'écran de controle
	***************************************************************************	*/
	void	Allocation();

	/* **************************************************************************
	METHODE :		IsEnTest()
	TRAITEMENT:
	***************************************************************************	*/
	bool IsEnTest();

	/* **************************************************************************
	METHODE :		Power
	TRAITEMENT:		Mise en route de l'équipement
	***************************************************************************	*/
	BOOL Power();

	/* **************************************************************************
	METHODE :		PowerOnBit
	TRAITEMENT:		Mise en route de l'équipement
	***************************************************************************	*/
	int PowerOnBit();

	/* **************************************************************************
	METHODE :		Charge_Contexte()
	TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
					contexte d'exploitation
	***************************************************************************	*/
	virtual BOOL Charge_Contexte(char *fichier);

	/* **************************************************************************
	METHODE :		Sauve_Contexte()
	TRAITEMENT:		Sauveagrde le contexte d'exploitation d'un fichier
	***************************************************************************	*/
	virtual BOOL Sauve_Contexte(char *fichier);

	int Panne();
	void SetPanne(const int val);
	string GetTestProgress();
	void SetTestProgress(const string test);
	bool ValidTestProgress(const string test);
	void ReinitED42();

	/* **************************************************************************
	METHODE :		InfoCIK
	TRAITEMENT:		Retourne la valeur de CIK
	***************************************************************************	*/
	int InfoCik() const;
	/* **************************************************************************
	METHODE :		ChangeCik
	TRAITEMENT:		Modifie la valeur de CIK
	***************************************************************************	*/
	int ChangeCik(int valeur, BOOL genere_TS=FALSE);

    // ********************************
	// Gestion CIK - KE
	int GetStateCik();
	void SetStateCik(int val);

	int GetStatusCik();
	void SetStatusCik(int val);

    int GetKEState();
	void SetKEState(int val);

    void SetKeStatus(const int valeur);
	int  GetKeStatus();

	int GetUserCik();
	void SetUserCik(int val);

	int GetCounterCik();
	void SetCounterCik(int val);
	// ********************************

	/* **************************************************************************
	METHODE :		InfoNL
	TRAITEMENT:		Retourne la valeur de NL
	***************************************************************************	*/
	int InfoNl() const;
	/* **************************************************************************
	METHODE :		ChangeNL
	TRAITEMENT:		Modifie la valeur de NL
	***************************************************************************	*/
	int ChangeNl(int valeur, BOOL genere_TS=FALSE);

	/* **************************************************************************
	METHODE :		InfoEG
	TRAITEMENT:		Retourne la valeur de EG
	***************************************************************************	*/
	int InfoEg() const;
	/* **************************************************************************
	METHODE :		ChangeEG
	TRAITEMENT:		Modifie la valeur de NL
	***************************************************************************	*/
	int ChangeEg(int valeur, BOOL genere_TS=FALSE);

	//**************************************************************************

	void activationPreset(string preset);

	void SetEquipement(const TStatus value);
	TStatus GetEquipement();

	BOOL GetMarcheEd42();
	void SetMarcheEd42(bool val);

	BOOL GetResetEd42();
	void SetResetEd42(bool val);

	BOOL GetResetEd42Tc();
	void SetResetEd42Tc(bool val);

	BOOL GetStatusNl();
	void SetStatusNl(bool val);

	BOOL GetZeroizeStatus();
	void SetZeroizeStatus(bool val);

	BOOL GetStatusEg();
	void SetStatusEg(bool val);

	int ChangeDefPassWord(string valeur, BOOL genere_TS=FALSE);
	string GetDefPassWord();
	void SetDefPassWord(string val);

	int ChangeUserPassWord(string valeur, BOOL genere_TS=FALSE);
	string GetUserPassWord();
	void SetUserPassWord(string val);

	int ChangeLanguage(int valeur=0, BOOL genere_TS=FALSE);
	int GetLanguage();
	void SetLanguage(int val);

	int ChangeUpdateLimit(int valeur=1, BOOL genere_TS=FALSE);
	int GetUpdateLimit();
	void SetUpdateLimit(int val);

	int ChangePasswordHoldTime(int valeur=0, BOOL genere_TS=FALSE);
	int GetPasswordHoldTime();
	void SetPasswordHoldTime(int val);

	int ChangeDeviceID(int valeur=0, BOOL genere_TS=FALSE);
	int GetDeviceID();
	void SetDeviceID(int val);
	void SetDeviceID(CString val);

	int ChangeInterfaceKeyDownload(int valeur=1, BOOL genere_TS=FALSE);
	int GetInterfaceKeyDownload();
	void SetInterfaceKeyDownload(int val);
	void SetInterfaceKeyDownload(CString val);

	int GetOperatingStatus();
	void SetOperatingStatus(int val);

	int GetOperatingMode();
	void SetOperatingMode(int val);

	//int GetActivePreset();
	//void SetActivePreset(int val);

	int GetTransmissionMode();
	void SetTransmissionMode(int val);

	int GetTransmissionProcedure();
	void SetTransmissionProcedure(int val);

	int GetTraficMode();
	void SetTraficMode(int val);

	int GetPresetList();
	void SetPresetList(string preset,char operation);

	int GetOnlinePreset();
	void SetOnlinePreset(int val);

	int GetOnlinePresetStatus();
	void SetOnlinePresetStatus(int val);

	int GetSystemConfiguration();
	void SetSystemConfiguration(int val);

	int GetKeyList();
	void SetKeyList(int val);

	int GetAlarm();
	void SetAlarm(int val);

	int GetError();
	void SetError(int val);

	int GetActiveKeyState();
	void SetActiveKeyState(int val);

	int GetActivatedKey();
	void SetActivatedKey(int val);

	int GetKeyMemory();
	void SetKeyMemory(int val);

	int GetDataTransfertDevice();
	void SetDataTransfertDevice(int val);

	int GetStatusCall();
	void SetStatusCall(int val);

	int GetStatusSync();
	void SetStatusSync(int val);

	int GetStatusRx();
	void SetStatusRx(int val);

	int GetStatusTx();
	void SetStatusTx(int val);

	int GetStatusBusy();
	void SetStatusBusy(int val);

	int GetDureeBusy();
	void SetDureeBusy(int val);

	string GetVersionRed();
	void SetVersionRed(string val);

	string GetVersionBlack();
	void SetVersionBlack(string val);

	string GetVersionPldRed();
	void SetVersionPldRed(string val);

	string GetVersionPldBlack();
	void SetVersionPldBlack(string val);

	string GetVersionOpeDevice();
	void SetVersionOpeDevice(string val);

	string GetVersionMilBus();
	void SetVersionMilBus(string val);

	BOOL GetClavier();
	void SetClavier(bool val);

	void setED42Lock(const bool valeur);
	BOOL getED42Lock();

	//**************************************************************

	BOOL ValidPreset(const int id);

	string GetChaineClavier();
	void SetChaineClavier(string val);


	//**************************************************************

	void    CEquipED42:: setRemoteAdress(const int valeur);
	void	CEquipED42:: setRemoteAdress(CString val);
	int     CEquipED42:: getRemoteAdress();

	void    CEquipED42:: setRemoteStatus(const bool valeur);
	bool    CEquipED42:: getRemoteStatus();

	void    CEquipED42:: setRemoteMode(const int valeur);
	void    CEquipED42:: setRemoteMode(CString val);
	int     CEquipED42:: getRemoteMode();

	void    CEquipED42:: SetRemoteTC(const int valeur);
	int     CEquipED42:: GetRemoteTC();

	void    CEquipED42:: setHDLCAddress(CString val);
	void    CEquipED42:: setHDLCAddress(const int valeur);
	int     CEquipED42:: getHDLCAddress();

	void    CEquipED42:: setAuthentified(const bool valeur);
	BOOL    CEquipED42:: getAuthentified();

	TError	CEquipED42:: DecodeError(string val);
	string	CEquipED42:: EncodeError(TError val);

	void	CEquipED42:: setErrors(TVectorError val);
	TVectorError CEquipED42::getErrors();

	TStatusError	CEquipED42:: DecodeStatusError(string val);
	string	CEquipED42:: EncodeStatusError(TStatusError val);

	void	CEquipED42:: setStatusErrors(TVectorStatusError val);
	TVectorStatusError CEquipED42::getStatusErrors();

	void	CEquipED42:: setModifErreurPanne(bool val);
	bool	CEquipED42:: getModifErreurPanne();

	void	CEquipED42:: setModifVue(bool val);
	bool	CEquipED42:: getModifVue();

	void	CEquipED42:: setReceptionDonnee(bool val);
	bool	CEquipED42:: getReceptionDonnee();

	TAlarm	CEquipED42:: DecodeAlarm(string val);
	string	CEquipED42:: EncodeAlarm(TAlarm val);

	void	CEquipED42:: setAlarms(TVectorAlarm val);
	TVectorAlarm CEquipED42::getAlarms();

	TGeneralParameters GetGeneralParameters(const string id);
	void SetGeneralParameters(const string id, const TGeneralParameters conf);

	TDigitalDCE GetDigitalDCEParameters(const string id);
	void SetDigitalDCEParameters(const string id, const TDigitalDCE conf);

	TDigitalDTE GetDigitalDTEParameters(const string id);
	void SetDigitalDTEParameters(const string id, const TDigitalDTE conf);

	TAnalogDCE GetAnalogDCEParameters(const string id);
	void SetAnalogDCEParameters(const string id, const TAnalogDCE conf);

	TAnalogDTE GetAnalogDTEParameters(const string id);
	void SetAnalogDTEParameters(const string id, const TAnalogDTE conf);

	TGeneralParameters GetDefaultGeneralParameters(const string id);

	TDigitalDCE GetDefaultDigitalDCEParameters(const string id);

	TDigitalDTE GetDefaultDigitalDTEParameters(const string id);

	TAnalogDCE GetDefaultAnalogDCEParameters(const string id);

	TAnalogDTE GetDefaultAnalogDTEParameters(const string id);

	void    CEquipED42:: setSecureMode(const int valeur);
	int    CEquipED42:: getSecureMode();

	void setStatusErrorTable(int errorNumber, bool val);
	BOOL getStatusErrorTable(int errorNumber);

	/*void setStatusErrorRCS(bool val);
	BOOL getStatusErrorRCS();*/

	void setStatusErrorMSG(bool val);
	BOOL getStatusErrorMSG();

	// Traitement message number page 158
	void setLastNumber(const int valeur);
	int getLastNumber();

	void setLastMessage(string valeur);
	string getLastMessage();

	void setRepetition(bool valeur);
	BOOL getRepetition();


	void setErrorMSG(bool valeur);
	BOOL getErrorMSG();

	void setErrorLF(bool valeur);
	BOOL getErrorLF();

	void setErrorCR(bool valeur);
	BOOL getErrorCR();

	void setPasDeReponse(bool valeur);
	BOOL getPasDeReponse();

	void setProtocolNumber(int valeur);
	int getProtocolNumber();

	TKeyManagement GetKeyManagement(const string id);
	void SetKeyManagement(const string id, const TKeyManagement conf);

	int GetMemoryIndexOfKey(int tmpActivePreset = DEFAULT_INT_VALUE_ED42, int tmpPresetType = OPE_NA);

	bool GetCvChargement(TKeyManagement *keyManagement);

	TMapKeyManagement GetMapKeyManagement();

	string verifyTag(string tag);
	string verifyTagV(string tag);
	string verifyTagD(string tag);

	void setErrorTable(int errorValue, bool val);
	BOOL getErrorTable(int errorValue);

	void setAlarmTable(int alarmValue, bool val);
	BOOL getAlarmTable(int alarmValue);

	TPowerBitError	CEquipED42:: DecodePowerBit(string val);
	string		CEquipED42:: EncodePowerBit(TPowerBitError val);

	TManuallyBitError	CEquipED42:: DecodeManuallyBit(string val);
	string		CEquipED42:: EncodeManuallyBit(TManuallyBitError val);

	//Pour les erreurs power on bit
	void		CEquipED42:: setPowerBitTable(int errorValue, bool val);
	BOOL		CEquipED42:: getPowerBitTable(int errorValue);

	//Pour les erreurs bit manually
	void		CEquipED42:: setBitManuallyTable(int errorValue, bool val);
	BOOL		CEquipED42:: getBitManuallyTable(int errorValue);
	void		CEquipED42:: setBitManuallyResultTable(int errorValue, bool val);
	BOOL		CEquipED42:: getBitManuallyResultTable(int errorValue);

	//Raz des différentes tables
	void		CEquipED42:: RAZTable();

	//Pour erreur de CONFLICT (S#20)
	int CEquipED42::GetStatusS20();
	void CEquipED42::SetStatusS20(int val);

	// Pour CyclicalStatusRequest
	int GetCyclicalStatusRequest();
	void SetCyclicalStatusRequest(int val);

	// Pour FullSimu
	BOOL GetFullSimu();
	void SetFullSimu(bool val);

	// RAZ table CV et KEK
	void RazTableCle(bool cle_kek = FALSE);

	void SetZeroizePassWord(int val);
	int GetZeroizePassWord();

	void SetnrCommandInError(int val);
	int GetnrCommandInError();

};

#endif // !defined(AFX_EQUIPED42_H__1CB55772_1888_4E2F_BE5F_7BD123A0B81F__INCLUDED_)
