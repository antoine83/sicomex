// EquipM1752.cpp: implementation of the CEquipM1752 class.
//
//////////////////////////////////////////////////////////////////////


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "stdafx.h"
#include "sicomex.h"
#include "Equip\ParamSim.h"
#include "Equip\EquipM1752.h"

#include "Comm\p_TRC1752.h"

#include "DlgAccue.h"
#include "DlgTRC1752.h"

#include "Divers\Div_fic.h"

#include <sstream>
#include <fstream>

extern CParamSimu* glob_paramsimu;
extern CDlgAccueil* glob_ihm;

//////////////////////////////////////////////////////////////////////
// Utilitaires
//////////////////////////////////////////////////////////////////////

int ExtractData(istringstream &data, string res[], int length, char sep)
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

string IntToString(int value, int size, bool sign)
{
	stringstream out;
	string result = "";

	// Si la valeur est indéfinie, on renvoi un string vide
	if (value == DEFAULT_INT_VALUE) return result;

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

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

/* **************************************************************************
METHODE :		CEquipM1752()
TRAITEMENT:		Constructeur, initialise les structures
***************************************************************************	*/
CEquipM1752::CEquipM1752(int idx):CEquip(idx)
{
	int i;

	char heure[9];
	char date[9];
	GetTimeFormat (LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT , NULL, "HH'H'mm'.'ss", (LPTSTR) heure, 9);
	GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,NULL,"dd'/'MM'/'yy", date, 9);

	appel_A = NULL;
	appel_B = NULL;

	string date_heure = date;
	date_heure += ".";
	date_heure += heure;

	modif = FALSE;
	test_progress = "";
	equip_en_test = FALSE;

	gic = "0000";
	origine_heure = "GPS";

	// Modem data
	manufacturer = "THOMSON";
	identity = "TRC 1752";
	board_management.capabilities = "TT";
	board_management.number = "T";
	board_management.release = "2";
	board_management.day = "01";
	board_management.month = "01";
	board_management.year = "70";

	board_1.capabilities = "AA";
	board_1.number = "A";
	board_1.release = "0";
	board_1.day = "01";
	board_1.month = "01";
	board_1.year = "70";
	board_1.date_and_time = date_heure;
	board_1.time_accuracy = 0;
	board_1.date_origin = "DEM";
	board_1.last_date_and_time = date_heure;
	board_1.time_lag = 0;

	board_2.capabilities = "BB";
	board_2.number = "B";
	board_2.release = "1";
	board_2.day = "01";
	board_2.month = "01";
	board_2.year = "70";
	board_2.date_and_time = date_heure;
	board_2.time_accuracy = 0;
	board_2.date_origin = "DEM";
	board_2.last_date_and_time = date_heure;
	board_2.time_lag = 0;

	quadrivoie = true;

	emetteur_marche			= true;
	emetteur_panne_majeure	= false;
	emetteur_panne_tc		= false;
	emetteur_emission		= false;

	recepteur_marche		= true;
	recepteur_panne_majeure = false;
	recepteur_panne_tc		= false;

	mode = false;			//En LOCAL par défaut.

	clock_pilot = "INTERNE";
	PilExt = true;				//Autorisation d'utiliser le pilote en externe

	// FDI - ZTS
	ZtsPft = false;

	// FFT - 1302
	Fft1302 = false;

	// RecMil
	RecMil = false;

	inr = "SANS";
	inr_rate = 10;

	panne = DEFAULT_INT_VALUE;

	//mise à false de la variable test carte	//CC
	equip_test_carte=false;

	for(int i=0; i<NB_TESTS; i++) {
		test_map[TESTS[i]] = FALSE;
	}

	for(i=0; i<NB_CHANNELS; i++) {
		channels[CHANNELS[i]].state = "INACTIVE";
		channels[CHANNELS[i]].status_local_remote_control = "MAIN";		//LOCAL

		channels[CHANNELS[i]].associated_af_configuration = "MC";		//CA

		if (CHANNELS[i] == "A1") channels[CHANNELS[i]].data_link_id = "D1";
		if (CHANNELS[i] == "A2") channels[CHANNELS[i]].data_link_id = "D2";
		if (CHANNELS[i] == "B1") channels[CHANNELS[i]].data_link_id = "D5";
		if (CHANNELS[i] == "B2") channels[CHANNELS[i]].data_link_id = "D6";

		channels[CHANNELS[i]].type = "-";
		channels[CHANNELS[i]].index_scanset_channel = 0;
		channels[CHANNELS[i]].link_management_type = "LAUTO";

		channels[CHANNELS[i]].quality_value = 31;
		channels[CHANNELS[i]].af_level_received = -30;
		channels[CHANNELS[i]].offset_af_output_level = 0;
		channels[CHANNELS[i]].af_level_received_slave = -30;
		channels[CHANNELS[i]].dopple_offset = 0;
		channels[CHANNELS[i]].signal_noise_ratio = 0;

		channels[CHANNELS[i]].direction_transmission = "RECEPTION";
		channels[CHANNELS[i]].offset_carrier_frequency = 0;
		channels[CHANNELS[i]].offset_mark_frequency = 0;
		channels[CHANNELS[i]].offset_space_frequency = 0;

		channels[CHANNELS[i]].master_diversity = FALSE;
		channels[CHANNELS[i]].test_progress = "";
		channels[CHANNELS[i]].reserve = FALSE;

		channels[CHANNELS[i]].emission_encours = FALSE;
		channels[CHANNELS[i]].emission_status = "INACTIF";
		channels[CHANNELS[i]].reception_status = "VEILLE";
		channels[CHANNELS[i]].emissionMessage = FALSE;
	}

	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++) {
		channels_configurations[CHANNELS_CONFIGURATION[i]].waveform = "REPOS";			//4285
		channels_configurations[CHANNELS_CONFIGURATION[i]].diversity = "SANS";
		channels_configurations[CHANNELS_CONFIGURATION[i]].direction = "HD";
		channels_configurations[CHANNELS_CONFIGURATION[i]].af_transmission_baudrate = 2400;
		channels_configurations[CHANNELS_CONFIGURATION[i]].af_transmission_codingtype = "CODE";
		channels_configurations[CHANNELS_CONFIGURATION[i]].af_transmission_interleaving = "LONG";
		channels_configurations[CHANNELS_CONFIGURATION[i]].transmission_carrier_frequency = 2000;
		channels_configurations[CHANNELS_CONFIGURATION[i]].transmission_space_frequency = 2425;
		channels_configurations[CHANNELS_CONFIGURATION[i]].transmission_mark_frequency = 1575;
		channels_configurations[CHANNELS_CONFIGURATION[i]].af_reception_baudrate = 2400;
		channels_configurations[CHANNELS_CONFIGURATION[i]].af_reception_codingtype = "CODE";
		channels_configurations[CHANNELS_CONFIGURATION[i]].af_reception_interleaving = "LONG";
		channels_configurations[CHANNELS_CONFIGURATION[i]].reception_carrier_frequency = 2000;
		channels_configurations[CHANNELS_CONFIGURATION[i]].reception_space_frequency = 2425;
		channels_configurations[CHANNELS_CONFIGURATION[i]].reception_mark_frequency = 1575;
		channels_configurations[CHANNELS_CONFIGURATION[i]].slave_baudrate = 2400;
		channels_configurations[CHANNELS_CONFIGURATION[i]].slave_codingtype = "CODE";
		channels_configurations[CHANNELS_CONFIGURATION[i]].slave_interleaving = "LONG";
		channels_configurations[CHANNELS_CONFIGURATION[i]].slave_carrier_frequency = 2000;
		channels_configurations[CHANNELS_CONFIGURATION[i]].slave_direction = "FD";
		channels_configurations[CHANNELS_CONFIGURATION[i]].use_data = "SANS";
	}

	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++) {
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].type = "SYNCHRONE";
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].electrical_characteristics = "V28";
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].transmission_baudrate = 2400;
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].reception_baudrate = 2400;
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].direction = "SORTANTE";
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].validity_time = "24H";
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].binary_integrity = "GRANDE";
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].polarity = "NORMALE";
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].handshake = "DPE";
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].character_length = 5;
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].parity = "SANS";
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].number_stop_bits = 1;
		interfaces_configurations[INTERFACES_CONFIGURATION[i]].data_flow_control = "PAE";
	}

	for(i=0; i<NB_AUX_INTERFACES_CONFIGURATIONS; i++) {
		aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].electrical_characteristics = "V28";
		aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].baudrate = 4800;
		aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].character_length = 7;
		aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].character_parity = "PAIR";
		aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].number_stop_bits = 1;
		aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].radio_address = 0;
		aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].equipment_type = "NORAD";
		aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].test_progress = "";

	}

	for(i=0; i<NB_DATA_LINK_IDS; i++) {
		data_links[DATA_LINK_IDS[i]].associated_configuration_id = "CI0";
		data_links[DATA_LINK_IDS[i]].test_progress = "";
	}

	for(i=0; i<NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS; i++) {
		local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].electrical_characteristics = "V28";
		local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].baudrate = 9600;
		local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].characters_length = 8;
		local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].characters_parity = "SANS";
		local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].number_stop_bits = 1;
	}

	for(i=0; i<NB_AF_CHANNELS_CONFIGURATIONS; i++) {
		af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].input_level = 0;
		af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].output_level = 0;
		af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].interface_type = "SYMETRIQUE";
		af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].ptt_type = "COL_OUV_M";
		af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].ptt_tempo = 300;
		af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].mute_characteristics = "COL_OUV_M";
		af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].mute_delay = 300;
		af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].radio_delay = 300;
	}

	for(i=0; i<NB_ALE_PARAMETERS; i++) {
		ale_parameter[ALE_PARAMETERS[i]].automatic_sounding = "OFF";
		ale_parameter[ALE_PARAMETERS[i]].aging_percentage = 5;
		ale_parameter[ALE_PARAMETERS[i]].aging_time = "04.0";
		ale_parameter[ALE_PARAMETERS[i]].multiservice = "OFF";
		ale_parameter[ALE_PARAMETERS[i]].automatic_reconfiguration = "OFF";
		ale_parameter[ALE_PARAMETERS[i]].service_activation = 3;
		ale_parameter[ALE_PARAMETERS[i]].allcall_message = "ON";
		ale_parameter[ALE_PARAMETERS[i]].wildcard_message = "OFF";
		ale_parameter[ALE_PARAMETERS[i]].anycall_message = "OFF";
		ale_parameter[ALE_PARAMETERS[i]].respond = "OFF";
		ale_parameter[ALE_PARAMETERS[i]].scanrate = 2;
		ale_parameter[ALE_PARAMETERS[i]].twa_automatic = 120;
		ale_parameter[ALE_PARAMETERS[i]].twa_manual = 999;
		ale_parameter[ALE_PARAMETERS[i]].twt = 3;
		ale_parameter[ALE_PARAMETERS[i]].tunetime_local = 200;
		ale_parameter[ALE_PARAMETERS[i]].tunetime_other = 300;
		ale_parameter[ALE_PARAMETERS[i]].ptt_gestion = "WIRE";
		ale_parameter[ALE_PARAMETERS[i]].sound_length = 0;
		ale_parameter[ALE_PARAMETERS[i]].retries_channel = 0;
		ale_parameter[ALE_PARAMETERS[i]].retries_scanfield = 1;
		ale_parameter[ALE_PARAMETERS[i]].long_sound_limit = 99;

		ale_parameter[ALE_PARAMETERS[i]].cms_choice = "BST";
		ale_parameter[ALE_PARAMETERS[i]].ale_termination_frame = "TIS";
		ale_parameter[ALE_PARAMETERS[i]].index_channel_table = 0;
		ale_parameter[ALE_PARAMETERS[i]].lowest_usable_frequency = 2000000;
		ale_parameter[ALE_PARAMETERS[i]].upper_usable_frequency = 2000000;
		ale_parameter[ALE_PARAMETERS[i]].call_type = "STD";
		ale_parameter[ALE_PARAMETERS[i]].index_selfaddress = 0;
		ale_parameter[ALE_PARAMETERS[i]].quick_identification = "OFF";
		ale_parameter[ALE_PARAMETERS[i]].quality_analysis = "ON";
		ale_parameter[ALE_PARAMETERS[i]].station_network_group = "S";
		ale_parameter[ALE_PARAMETERS[i]].called_address = 0;
		ale_parameter[ALE_PARAMETERS[i]].called_address_string = "0";
		ale_parameter[ALE_PARAMETERS[i]].agc = "FAST";
		ale_parameter[ALE_PARAMETERS[i]].call_length = 0;
		ale_parameter[ALE_PARAMETERS[i]].amd_message = "";

		ale_parameter[ALE_PARAMETERS[i]].link_protection_level = 1;
		ale_parameter[ALE_PARAMETERS[i]].key_management = "24H";
		ale_parameter[ALE_PARAMETERS[i]].key_position = DEFAULT_INT_VALUE;

		ale_parameter[ALE_PARAMETERS[i]].ale_status = DEFAULT_STRING_VALUE;
		ale_parameter[ALE_PARAMETERS[i]].index_channel_in_scanset = 0;

		ale_parameter[ALE_PARAMETERS[i]].appel_en_cours = FALSE;

		ale_parameter[ALE_PARAMETERS[i]].sounding_index = -1;

		ale_parameter[ALE_PARAMETERS[i]].est_appele = false;
	}

	// Remplissage de la liste d'erreur
	// commence à 1

	i = 1;
	// incident voie
	erreurs[i].code = "0000";
	erreurs[i].erreur = "A_E_INC";//AUTRE_ERR_INCIDENT

	i++;
	erreurs[i].code = "0001";
	erreurs[i].erreur = "E_ADD_ERR";//ERR_ADDRESS_ERROR

	i++;
	erreurs[i].code = "0002";
	erreurs[i].erreur = "E_ALL_BLO";//ERR_ALLOC_BLOC

	i++;
	erreurs[i].code = "0003";
	erreurs[i].erreur = "E_BUS_ERR";//ERR_BUS_ERROR

	i++;
	erreurs[i].code = "0004";
	erreurs[i].erreur = "E_F_IN_TS";//ERR_CHOIX_FILE_INTERFACE_TS

	i++;
	erreurs[i].code = "0005";
	erreurs[i].erreur = "E_RAMDP_T";//ERR_COMPREHENSION_RAMDP_T

	i++;
	erreurs[i].code = "0006";
	erreurs[i].erreur = "E_CONF_BF";//ERR_CONFIG_BF

	i++;
	erreurs[i].code = "0007";
	erreurs[i].erreur = "E_CONF_PO";//ERR_CONFIG_PORT

	i++;
	erreurs[i].code = "0008";
	erreurs[i].erreur = "E_CRE_TCH";//ERR_CREATION_TACHE

	i++;
	erreurs[i].code = "0009";
	erreurs[i].erreur = "ERR_DEBUG";//ERR_DEBUG

	i++;
	erreurs[i].code = "000A";
	erreurs[i].erreur = "E_DES_BL";//ERR_DESTRUCTION_BLOC

	i++;
	erreurs[i].code = "000B";
	erreurs[i].erreur = "E_DES_TCH";//ERR_DESTRUCTION_TACHE

	i++;
	erreurs[i].code = "000C";
	erreurs[i].erreur = "E_E_RDPTS";//ERR_ECRITURE_RAMDP_TS

	i++;
	erreurs[i].code = "000D";
	erreurs[i].erreur = "E_F_MODE";//ERR_FERMETURE_MODE

	i++;
	erreurs[i].code = "000E";
	erreurs[i].erreur = "E_F_PH";//ERR_FERMETURE_PH

	i++;
	erreurs[i].code = "000F";
	erreurs[i].erreur = "E_IL_INS";//ERR_ILLEGAL_INSTRUCTION

	i++;
	erreurs[i].code = "0010";
	erreurs[i].erreur = "E_M_ERR";//ERR_MESSAGE_ERRONE

	i++;
	erreurs[i].code = "0011";
	erreurs[i].erreur = "E_MG_TS_IN";//ERR_MSG_TS_INCONNU

	i++;
	erreurs[i].code = "0012";
	erreurs[i].erreur = "E_O_MODE";//ERR_OUVERTURE_MODE

	i++;
	erreurs[i].code = "0013";
	erreurs[i].erreur = "E_O_PH";//ERR_OUVERTURE_PH

	i++;
	erreurs[i].code = "0017";
	erreurs[i].erreur = "E_C_LO_TS";//ERR_CHARGER_LOGICIEL_TS

	i++;
	erreurs[i].code = "0018";
	erreurs[i].erreur = "ERR_TRAP";//ERR_TRAP

	i++;
	erreurs[i].code = "0019";
	erreurs[i].erreur = "E_ZERO_DIV";//ERR_ZERO_DIVISION

	i++;
	erreurs[i].code = "001A";
	erreurs[i].erreur = "E_ACK_TS";//ERR_ACK_TS

	i++;
	erreurs[i].code = "001B";
	erreurs[i].erreur = "E_CR_TS";//ERR_CR_TS

	i++;
	erreurs[i].code = "001C";
	erreurs[i].erreur = "E_ACCE_MCX";//ERR_ACCES_MCX

	i++;
	erreurs[i].code = "001D";
	erreurs[i].erreur = "E_SC_P_EBL";//ERR_SC_POST_ENVOIBLOC

	i++;
	erreurs[i].code = "001E";
	erreurs[i].erreur = "E_NB_MG_E";//ERR_NB_MSG_EMISSION

	i++;
	erreurs[i].code = "001F";
	erreurs[i].erreur = "E_I_GE_LRC";//ERR_INIT_GES_LRC

	i++;
	erreurs[i].code = "0020";
	erreurs[i].erreur = "E_PTTXSC34";//ERR_SC_PEND_TASK_TX_SCC_3_4

	i++;
	erreurs[i].code = "0021";
	erreurs[i].erreur = "E_ED_NDISP";//ERR_BLOC_ED_NON_DISPO

	i++;
	erreurs[i].code = "0022";
	erreurs[i].erreur = "E_TRXTXOFF";//ERR_BUFTACHERX_PLEIN_DISTANTXOFF

	i++;
	erreurs[i].code = "0023";
	erreurs[i].erreur = "E_SC_P_MGR";//ERR_SC_POST_MSG_RECU

	i++;
	erreurs[i].code = "0024";
	erreurs[i].erreur = "E_PMG_H_TC";//ERR_POST_MSG_HDLTC_TC

	i++;
	erreurs[i].code = "0025";
	erreurs[i].erreur = "E_R_PORT";//ERR_RECEVOIR_PORT

	i++;
	erreurs[i].code = "0026";
	erreurs[i].erreur = "E_E_M_ISA";//ERR_ENVOI_MESSAGE_ISA

	i++;
	erreurs[i].code = "0027";
	erreurs[i].erreur = "E_MG_LRCTG";//ERR_MSG_LRC_TROP_GROS

	i++;
	erreurs[i].code = "0028";
	erreurs[i].erreur = "E_V_INAT";//ERR_VALEUR_INATTENDUE

	i++;
	erreurs[i].code = "0029";
	erreurs[i].erreur = "E_R_TS";//ERR_REVEILLER_TS

	i++;
	erreurs[i].code = "002A";
	erreurs[i].erreur = "E_TCRTS_V1";//ERR_TEMPO_CR_TS_VOIE1

	i++;
	erreurs[i].code = "002B";
	erreurs[i].erreur = "E_TCRTS_V2";//ERR_TEMPO_CR_TS_VOIE2

	i++;
	erreurs[i].code = "002C";
	erreurs[i].erreur = "E_TCTSBFV2";//ERR_TEMPO_CR_TS_BF_VOIE2

	i++;
	erreurs[i].code = "002D";
	erreurs[i].erreur = "E_TCTSGTV2";//ERR_TEMPO_CR_TS_GT_VOIE2

	i++;
	erreurs[i].code = "002E";
	erreurs[i].erreur = "E_TACKTSV1";//ERR_TEMPO_ACK_TS_VOIE1

	i++;
	erreurs[i].code = "002F";
	erreurs[i].erreur = "E_TACKTSV2";//ERR_TEMPO_ACK_TS_VOIE2

	i++;
	erreurs[i].code = "0030";
	erreurs[i].erreur = "E_TAKTBFV2";//ERR_TEMPO_ACK_TS_BF_VOIE2

	i++;
	erreurs[i].code = "0031";
	erreurs[i].erreur = "E_TAKTGTV2";//ERR_TEMPO_ACK_TS_GT_VOIE2

	i++;
	erreurs[i].code = "0032";
	erreurs[i].erreur = "E_AR_TEMPO";//ERR_ARMER_TEMPO

	i++;
	erreurs[i].code = "0033";
	erreurs[i].erreur = "E_AN_TEMPO";//ERR_ANNULER_TEMPO

	// incident carte
	i++;
	erreurs[i].code = "1000";
	erreurs[i].erreur = "ERR_ALLOC";//ERR_ALLOC

	i++;
	erreurs[i].code = "1001";
	erreurs[i].erreur = "E_DESALLOC";//ERR_DESALLOC

	i++;
	erreurs[i].code = "1100";
	erreurs[i].erreur = "E_TYPE_PSK";//ERR_TYPE_PSK

	i++;
	erreurs[i].code = "1101";
	erreurs[i].erreur = "E_DEBI_MIL";//ERR_DEBIT_MIL

	i++;
	erreurs[i].code = "1102";
	erreurs[i].erreur = "E_ENTL_MIL";//ERR_ENTREL_MIL

	i++;
	erreurs[i].code = "1103";
	erreurs[i].erreur = "E_NB_REPET";//ERR_NB_REPETITIONS;

	i++;
	erreurs[i].code = "1104";
	erreurs[i].erreur = "E_F_ONDE";//ERR_FORME_ONDE

	i++;
	erreurs[i].code = "1105";
	erreurs[i].erreur = "E_NB_DATA";//ERR_NB_DATA

	i++;
	erreurs[i].code = "1106";
	erreurs[i].erreur = "E_SERVICE";//ERR_SERVICE

	i++;
	erreurs[i].code = "1107";
	erreurs[i].erreur = "E_IND_TABL";//ERR_IND_TABLE

	i++;
	erreurs[i].code = "1108";
	erreurs[i].erreur = "E_T_C_CONV";//ERR_TYPE_CODAGE_CONV

	i++;
	erreurs[i].code = "1109";
	erreurs[i].erreur = "E_T_REPET";//ERR_TYPE_REPETITION

	i++;
	erreurs[i].code = "110A";
	erreurs[i].erreur = "E_COMPACTA";//ERR_COMPACTAGE

	i++;
	erreurs[i].code = "110B";
	erreurs[i].erreur = "E_DECOMPAC";//ERR_DECOMPACTAGE

	i++;
	erreurs[i].code = "110C";
	erreurs[i].erreur = "E_T_ENTREL";//ERR_TYPE_ENTREL

	i++;
	erreurs[i].code = "110D";
	erreurs[i].erreur = "E_ENTRELAC";//ERR_ENTRELACEMENT

	i++;
	erreurs[i].code = "110E";
	erreurs[i].erreur = "E_DESENTRE";//ERR_DESENTRELACEMENT

	i++;
	erreurs[i].code = "110F";
	erreurs[i].erreur = "E_E_ENTREL";//ERR_ETAT_ENTRELACEUR

	i++;
	erreurs[i].code = "1110";
	erreurs[i].erreur = "E_O_EMIS";//ERR_ORIGINE_EMISSION

	i++;
	erreurs[i].code = "1111";
	erreurs[i].erreur = "E_I_EMIS";//ERR_IND_EMISSION

	i++;
	erreurs[i].code = "1112";
	erreurs[i].erreur = "E_I_RECEP";//ERR_IND_RECEPTION

	i++;
	erreurs[i].code = "1113";
	erreurs[i].erreur = "E_I_F_DATA";//ERR_IND_FIN_DATA

	i++;
	erreurs[i].code = "1114";
	erreurs[i].erreur = "E_MPSYNCHR";//ERR_MODE_PRISE_SYNCHRO

	i++;
	erreurs[i].code = "1115";
	erreurs[i].erreur = "E_T_INTERF";//ERR_TYPE_INTERFACE

	i++;
	erreurs[i].code = "1116";
	erreurs[i].erreur = "E_STATUS";//ERR_STATUS

	i++;
	erreurs[i].code = "1117";
	erreurs[i].erreur = "E_NB_TRAME";//ERR_NOMBRE_TRAMES

	i++;
	erreurs[i].code = "1210";
	erreurs[i].erreur = "E_MAJ_E_Z";//ERR_MAJ_ECR_ZONE

	i++;
	erreurs[i].code = "120F";
	erreurs[i].erreur = "E_LIB_TOUT";//ERR_LIBERER_TIMEOUT

	i++;
	erreurs[i].code = "1200";
	erreurs[i].erreur = "E_POST_EVT";//ERR_POSTER_EVT

	i++;
	erreurs[i].code = "1201";
	erreurs[i].erreur = "E_POS_E_IT";//ERR_POSTER_EVT_IT

	i++;
	erreurs[i].code = "1202";
	erreurs[i].erreur = "E_POS_E_IN";//ERR_POSTER_EVT_INATTENDU

	i++;
	erreurs[i].code = "1203";
	erreurs[i].erreur = "E_POSIT_IN";//ERR_POSTER_IT_INATTENDU

	i++;
	erreurs[i].code = "1204";
	erreurs[i].erreur = "E_POS_EVTR";//ERR_POSTER_EVTR

	i++;
	erreurs[i].code = "1205";
	erreurs[i].erreur = "E_A_DELAI";//ERR_ATTENDRE_DELAI

	i++;
	erreurs[i].code = "1206";
	erreurs[i].erreur = "E_A_EVT";//ERR_ATTENDRE_EVT

	i++;
	erreurs[i].code = "1207";
	erreurs[i].erreur = "E_A_TOUT";//ERR_ATTENDRE_TIMEOUT

	i++;
	erreurs[i].code = "1208";
	erreurs[i].erreur = "E_A_TOUT";//ERR_ACTIVITE_TIMEOUT

	i++;
	erreurs[i].code = "1209";
	erreurs[i].erreur = "E_L_Z_EVT";//ERR_LIRE_ZONE_EVT

	i++;
	erreurs[i].code = "120A";
	erreurs[i].erreur = "E_E_Z_EVT";//ERR_ECRIRE_ZONE_EVT

	i++;
	erreurs[i].code = "120B";
	erreurs[i].erreur = "E_INIT_Z";//ERR_INITIALISER_ZONE

	i++;
	erreurs[i].code = "120C";
	erreurs[i].erreur = "E_RAZ_Z";//ERR_RAZ_ZONE

	i++;
	erreurs[i].code = "120D";
	erreurs[i].erreur = "E_MJ_LEC_Z";//ERR_MAJ_LEC_ZONE

	i++;
	erreurs[i].code = "120E";
	erreurs[i].erreur = "E_MJ_ECR_Z";//ERR_MAJ_ECR_ZONE

	i++;
	erreurs[i].code = "120F";
	erreurs[i].erreur = "E_L_TOUT";//ERR_LIBERER_TIMEOUT

	i++;
	erreurs[i].code = "1210";
	erreurs[i].erreur = "E_L_EVT";//ERR_LIBERER_EVT

	i++;
	erreurs[i].code = "1211";
	erreurs[i].erreur = "E_POEVT_EC";//ERR_POSTER_EVT_ECRASER

	i++;
	erreurs[i].code = "1300";
	erreurs[i].erreur = "E_CONF_MOD";//ERR_CONFIGURER_MODE

	i++;
	erreurs[i].code = "1301";
	erreurs[i].erreur = "E_INIT_MOD";//ERR_INITIALISER_MODE

	i++;
	erreurs[i].code = "1302";
	erreurs[i].erreur = "E_ORD_MOD";//ERR_ORDONNER_MODE

	i++;
	erreurs[i].code = "1303";
	erreurs[i].erreur = "E_SIGN_BAS";//ERR_SIGNATURE_BASE

	i++;
	erreurs[i].code = "1304";
	erreurs[i].erreur = "E_SIGN_MOD";//ERR_SIGNATURE_MODE

	i++;
	erreurs[i].code = "1311";
	erreurs[i].erreur = "E_GES_TEST";//ERR_GESTION_TEST

	i++;
	erreurs[i].code = "1312";
	erreurs[i].erreur = "E_GE_T_SR";//ERR_GESTION_TEST_SR

	i++;
	erreurs[i].code = "1400";
	erreurs[i].erreur = "E_EAKRDP";//ERR_ECRIRE_ACK_RAMDP

	i++;
	erreurs[i].code = "1401";
	erreurs[i].erreur = "E_ENAKRDP";//ERR_ECRIRE_NACK_RAMDP

	i++;
	erreurs[i].code = "1402";
	erreurs[i].erreur = "E_E_CR_RDP";//ERR_ECRIRE_CR_RAMDP

	i++;
	erreurs[i].code = "1403";
	erreurs[i].erreur = "E_E_INDRDP";//ERR_ECRIRE_IND_RAMDP

	i++;
	erreurs[i].code = "1404";
	erreurs[i].erreur = "E_EDEMDRDP";//ERR_ECRIRE_DEM_DATA_RAMDP

	i++;
	erreurs[i].code = "1405";
	erreurs[i].erreur = "E_EDOUTRDP";//ERR_ECRIRE_DATA_OUT_RAMDP

	i++;
	erreurs[i].code = "1406";
	erreurs[i].erreur = "E_IT_RAMDP";//ERR_IT_RAMDP

	i++;
	erreurs[i].code = "1407";
	erreurs[i].erreur = "E_A_RDP_L";//ERR_ATTENDRE_RAMDP_LIBRE

	i++;
	erreurs[i].code = "1408";
	erreurs[i].erreur = "E_D_RDP";//ERR_DIALOGUE_RAMDP

	i++;
	erreurs[i].code = "1409";
	erreurs[i].erreur = "E_L_D_RDP";//ERR_LIRE_DATA_RAMDP

	i++;
	erreurs[i].code = "140A";
	erreurs[i].erreur = "E_TOUTDRDP";//ERR_TIMEOUT_DATA_RAMDP

	i++;
	erreurs[i].code = "140B";
	erreurs[i].erreur = "E_ID_DRPD";//ERR_ID_DIALOGUE_RAMPD

	i++;
	erreurs[i].code = "140C";
	erreurs[i].erreur = "E_ID_D_RDP";//ERR_ID_DATA_RAMDP

	i++;
	erreurs[i].code = "1420";
	erreurs[i].erreur = "E_L_AK_DSP";//ERR_LIRE_ACK_DSP

	i++;
	erreurs[i].code = "1421";
	erreurs[i].erreur = "E_E_AK_DSP";//ERR_ECRIRE_ACK_DSP

	i++;
	erreurs[i].code = "1422";
	erreurs[i].erreur = "E_LNAK_DSP";//ERR_LIRE_NACK_DSP

	i++;
	erreurs[i].code = "1423";
	erreurs[i].erreur = "E_ENAK_DSP";//ERR_ECRIRE_NACK_DSP

	i++;
	erreurs[i].code = "1424";
	erreurs[i].erreur = "E_L_CR_DSP";//ERR_LIRE_CR_DSP

	i++;
	erreurs[i].code = "1425";
	erreurs[i].erreur = "E_E_CR_DSP";//ERR_ECRIRE_CR_DSP

	i++;
	erreurs[i].code = "1426";
	erreurs[i].erreur = "E_LIND_DSP";//ERR_LIRE_IND_DSP

	i++;
	erreurs[i].code = "1427";
	erreurs[i].erreur = "E_EIND_DSP";//ERR_ECRIRE_IND_DSP

	i++;
	erreurs[i].code = "1428";
	erreurs[i].erreur = "E_E_RQ_DSP";//ERR_ECRIRE_RQ_DSP

	i++;
	erreurs[i].code = "1429";
	erreurs[i].erreur = "E_EDEMDDSP";//ERR_ECRIRE_DEM_DATA_DSP

	i++;
	erreurs[i].code = "142A";
	erreurs[i].erreur = "E_E_D_DSP";//ERR_ECRIRE_DATA_DSP

	i++;
	erreurs[i].code = "142B";
	erreurs[i].erreur = "E_EDMA_DSP";//ERR_ECRIRE_DMA_DSP

	i++;
	erreurs[i].code = "142C";
	erreurs[i].erreur = "E_A_DSP_L";//ERR_ATTENTE_DSP_LIBRE

	i++;
	erreurs[i].code = "142D";
	erreurs[i].erreur = "E_A_DMA_L";//ERR_ATTENTE_DMA_LIBRE

	i++;
	erreurs[i].code = "142E";
	erreurs[i].erreur = "E_A_R_DSP";//ERR_ATTENTE_REPONSE_DSP

	i++;
	erreurs[i].code = "142F";
	erreurs[i].erreur = "E_ITDMADSP";//ERR_IT_DMA_DSP

	i++;
	erreurs[i].code = "1430";
	erreurs[i].erreur = "E_IT_DSP";//ERR_IT_DSP

	i++;
	erreurs[i].code = "1431";
	erreurs[i].erreur = "E_ID_D_DSP";//ERR_ID_DIALOGUE_DSP

	i++;
	erreurs[i].code = "1432";
	erreurs[i].erreur = "E_IDDATDSP";//ERR_ID_DAT_DSP

	i++;
	erreurs[i].code = "1440";
	erreurs[i].erreur = "E_IT_E";//ERR_IT_EMISSION

	i++;
	erreurs[i].code = "1441";
	erreurs[i].erreur = "E_T_R_E";//ER_TEMPS_REEL_EMISSION

	i++;
	erreurs[i].code = "1442";
	erreurs[i].erreur = "E_IT_R";//ERR_IT_RECEPTION

	i++;
	erreurs[i].code = "1500";
	erreurs[i].erreur = "E_T_C_CONV";//ERR_TACHE_CODAGE_CONVOLUTIF

	i++;
	erreurs[i].code = "1501";
	erreurs[i].erreur = "E_T_D_CONV";//ERR_TACHE_DECODAGE_CONVOLUTIF

	i++;
	erreurs[i].code = "1502";
	erreurs[i].erreur = "E_T_E_B";//ERR_TACHE_ENTRELACEMENT_BLOC

	i++;
	erreurs[i].code = "1503";
	erreurs[i].erreur = "E_T_D_B";//ERR_TACHE_DESENTRELACEMENT_BLOC

	i++;
	erreurs[i].code = "1504";
	erreurs[i].erreur = "E_T_E_CONV";//ERR_TACHE_ENTRELACEMENT_CONVOLUTIF

	i++;
	erreurs[i].code = "1505";
	erreurs[i].erreur = "E_T_D_CONV";//ERR_TACHE_DESENTRELACEMENT_CONVOLUTIF

	i++;
	erreurs[i].code = "1506";
	erreurs[i].erreur = "E_T_MOD";//ERR_TACHE_MODULATION

	i++;
	erreurs[i].code = "1507";
	erreurs[i].erreur = "E_T_DEMO";//ERR_TACHE_DEMODULATION

	i++;
	erreurs[i].code = "1508";
	erreurs[i].erreur = "E_T_P_TRAI";//ERR_TACHE_POST_TRAITEMENT

	i++;
	erreurs[i].code = "1509";
	erreurs[i].erreur = "E_T_PRE_T";//ERR_TACHE_PRE_TRAITEMENT

	i++;
	erreurs[i].code = "150A";
	erreurs[i].erreur = "E_T_Q";//ERR_TACHE_QUANTIFICATION

	i++;
	erreurs[i].code = "150B";
	erreurs[i].erreur = "E_T_S";//ERR_TACHE_SYNCHRONISATION

	i++;
	erreurs[i].code = "150C";
	erreurs[i].erreur = "E_T_A_VOC";//ERR_TACHE_ANALYSE_VOC

	i++;
	erreurs[i].code = "150D";
	erreurs[i].erreur = "E_T_S_VOC";//ERR_TACHE_SYNTHESE_VOC

	i++;
	erreurs[i].code = "150E";
	erreurs[i].erreur = "E_TCFEC_PH";//ERR_TACHE_CODAGE_FEC_PHONIE

	i++;
	erreurs[i].code = "150F";
	erreurs[i].erreur = "E_TDFEC_PH";//ERR_TACHE_DECODAGE_FEC_PHONIE

	i++;
	erreurs[i].code = "1510";
	erreurs[i].erreur = "E_T_S_PH";//ERR_TACHE_SYNCHRO_PHONIE

	i++;
	erreurs[i].code = "1600";
	erreurs[i].erreur = "E_DEP_PIL";//ERR_DEPASSEMENT_PILE

	// panne modem
	i++;
	erreurs[i].code = "0901";
	erreurs[i].erreur = "I_E_VL_DI";//ID_ERREUR_VAL_DISPLAY

	i++;
	erreurs[i].code = "0902";
	erreurs[i].erreur = "I_VL_SLOC";//ID_ERREUR_VAL_STATLOC

	i++;
	erreurs[i].code = "0903";
	erreurs[i].erreur = "I_VL_SDIS";//ID_ERREUR_VAL_STATDIS

	i++;
	erreurs[i].code = "0904";
	erreurs[i].erreur = "I_M_DHM";//ID_ERREUR_MENU_DHM

	i++;
	erreurs[i].code = "0905";
	erreurs[i].erreur = "I_A_DHM";//ID_ERREUR_AUTO_DHM

	i++;
	erreurs[i].code = "0906";
	erreurs[i].erreur = "I_INIT_DHM";//ID_ERREUR_INIT_DHM

	i++;
	erreurs[i].code = "090A";
	erreurs[i].erreur = "I_GET_DATA";//ID_ERREUR_GET_DATA

	i++;
	erreurs[i].code = "090B";
	erreurs[i].erreur = "I_UPD_DATA";//ID_ERREUR_UPD_DATA

	i++;
	erreurs[i].code = "090C";
	erreurs[i].erreur = "I_MODE";//ID_ERREUR_MODE

	i++;
	erreurs[i].code = "090D";
	erreurs[i].erreur = "I_LINK";//ID_ERREUR_LINK

	i++;
	erreurs[i].code = "090E";
	erreurs[i].erreur = "I_RTS";//ID_ERREUR_RTS

	i++;
	erreurs[i].code = "090F";
	erreurs[i].erreur = "I_DEBIT";//ID_ERREUR_DEBIT

	i++;
	erreurs[i].code = "0910";
	erreurs[i].erreur = "I_ENTREL";//ID_ERREUR_ENTREL

	i++;
	erreurs[i].code = "0911";
	erreurs[i].erreur = "I_SSP";//ID_ERREUR_SSP

	i++;
	erreurs[i].code = "0912";
	erreurs[i].erreur = "I_SHIFT";//ID_ERREUR_SHIFT

	i++;
	erreurs[i].code = "0913";
	erreurs[i].erreur = "I_SPACE";//ID_ERREUR_SPACE

	i++;
	erreurs[i].code = "0914";
	erreurs[i].erreur = "I_MARK";//ID_ERREUR_MARK

	i++;
	erreurs[i].code = "0915";
	erreurs[i].erreur = "I_DPE";//ID_ERREUR_DPE

	i++;
	erreurs[i].code = "0916";
	erreurs[i].erreur = "I_VITESSE";//ID_ERREUR_VITESSE

	i++;
	erreurs[i].code = "0917";
	erreurs[i].erreur = "I_NB_BITS";//ID_ERREUR_NB_BITS

	i++;
	erreurs[i].code = "0918";
	erreurs[i].erreur = "I_NB_STOP";//ID_ERREUR_NB_STOP

	i++;
	erreurs[i].code = "0919";
	erreurs[i].erreur = "I_PARITE";//ID_ERREUR_PARITE

	i++;
	erreurs[i].code = "091A";
	erreurs[i].erreur = "I_CK_GEN";//ID_ERREUR_CK_GEN

	i++;
	erreurs[i].code = "091B";
	erreurs[i].erreur = "I_STAB";//ID_ERREUR_STAB

	i++;
	erreurs[i].code = "091C";
	erreurs[i].erreur = "I_INIT_TC";//ID_ERREUR_INIT_TC

	i++;
	erreurs[i].code = "091E";
	erreurs[i].erreur = "I_ACTIV";//ID_ERREUR_ACTIV

	i++;
	erreurs[i].code = "091F";
	erreurs[i].erreur = "I_CR_RECU";//ID_ERREUR_CR_RECU

	i++;
	erreurs[i].code = "0920";
	erreurs[i].erreur = "I_DESACTIV";//ID_ERREUR_DESACTIV

	i++;
	erreurs[i].code = "0921";
	erreurs[i].erreur = "I_AJUS_FSK";//ID_ERREUR_AJUST_FSK

	i++;
	erreurs[i].code = "0922";
	erreurs[i].erreur = "I_T_DECL";//ID_ERREUR_TEST_DECL

	i++;
	erreurs[i].code = "0923";
	erreurs[i].erreur = "I_TRAI_REQ";//ID_ERREUR_TRAIT_REQ

	i++;
	erreurs[i].code = "0924";
	erreurs[i].erreur = "I_CRDE4285";//ID_ERREUR_CR_DEB_EMI_4285

	i++;
	erreurs[i].code = "0925";
	erreurs[i].erreur = "I_CRFE4285";//ID_ERREUR_CR_FIN_EMI_4285

	i++;
	erreurs[i].code = "0926";
	erreurs[i].erreur = "I_CRDR4285";//ID_ERREUR_CR_DEB_REC_4285

	i++;
	erreurs[i].code = "0927";
	erreurs[i].erreur = "I_CRFR4285";//ID_ERREUR_CR_FIN_REC_4285

	i++;
	erreurs[i].code = "0928";
	erreurs[i].erreur = "I_CRDE_FSK";//ID_ERREUR_CR_DEB_EMI_FSK

	i++;
	erreurs[i].code = "0929";
	erreurs[i].erreur = "I_CRFE_FSK";//ID_ERREUR_CR_FIN_EMI_FSK

	i++;
	erreurs[i].code = "092A";
	erreurs[i].erreur = "I_CRDR_FSK";//ID_ERREUR_CR_DEB_REC_FSK

	i++;
	erreurs[i].code = "092B";
	erreurs[i].erreur = "I_CRFR_FSK";//ID_ERREUR_CR_FIN_REC_FSK

	i++;
	erreurs[i].code = "092C";
	erreurs[i].erreur = "I_CR_ARRET";//ID_ERREUR_CR_ARRET

	i++;
	erreurs[i].code = "092D";
	erreurs[i].erreur = "I_CRD_TEST";//ID_ERREUR_CR_DEB_TEST

	i++;
	erreurs[i].code = "092E";
	erreurs[i].erreur = "I_CR_PARAM";//ID_ERREUR_CR_PARAM

	i++;
	erreurs[i].code = "092F";
	erreurs[i].erreur = "I_CR_INIT";//ID_ERREUR_CR_INIT

	i++;
	erreurs[i].code = "0930";
	erreurs[i].erreur = "I_CR_TEST";//ID_ERREUR_CR_TEST

	i++;
	erreurs[i].code = "0931";
	erreurs[i].erreur = "I_CR_REQ_I";//ID_ERREUR_CR_REQ_INCONNUE

	i++;
	erreurs[i].code = "0932";
	erreurs[i].erreur = "I_CR_I";//ID_ERREUR_CR_INCONNU

	i++;
	erreurs[i].code = "0933";
	erreurs[i].erreur = "I_TABREQ_F";//ID_ERREUR_TAB_REQ_FULL

	i++;
	erreurs[i].code = "0934";
	erreurs[i].erreur = "I_V_MDM";//ID_ERREUR_VERSION_MDM

	i++;
	erreurs[i].code = "0935";
	erreurs[i].erreur = "I_ATES_MDM";//ID_ERREUR_AUTOTEST_MDM

	i++;
	erreurs[i].code = "0936";
	erreurs[i].erreur = "I_FALT_STG";//ID_ERREUR_FIN_ALT_STANAG

	i++;
	erreurs[i].code = "0937";
	erreurs[i].erreur = "I_FALT_FSK";//ID_ERREUR_FIN_ALT_FSK

	i++;
	erreurs[i].code = "0938";
	erreurs[i].erreur = "I_I_PARAM";//ID_ERREUR_INIT_PARAM

	i++;
	erreurs[i].code = "0939";
	erreurs[i].erreur = "I_T_RADIO";//ID_ERREUR_TEMPO_RADIO

	i++;
	erreurs[i].code = "093A";
	erreurs[i].erreur = "I_INV_BIT";//ID_ERREUR_INV_BIT

	i++;
	erreurs[i].code = "093B";
	erreurs[i].erreur = "I_CR_R_TEST";//ID_ERREUR_CR_RESULTAT_TEST

	i++;
	erreurs[i].code = "0950";
	erreurs[i].erreur = "I_IT_N_TRA";//ID_ERREUR_IT_NON_TRAITE

	i++;
	erreurs[i].code = "0951";
	erreurs[i].erreur = "I_BUS_E";//ID_ERREUR_BUS_ERROR

	i++;
	erreurs[i].code = "0952";
	erreurs[i].erreur = "I_ADD_E";//ID_ERREUR_ADDRESS_ERROR

	i++;
	erreurs[i].code = "0953";
	erreurs[i].erreur = "I_ILLEGAL";//ID_ERREUR_ILLEGAL

	i++;
	erreurs[i].code = "0954";
	erreurs[i].erreur = "I_TRAP";//ID_ERREUR_TRAP

	i++;
	erreurs[i].code = "0955";
	erreurs[i].erreur = "I_WD";//ID_ERREUR_WD

	i++;
	erreurs[i].code = "0964";
	erreurs[i].erreur = "I_BTTX_P";//ID_ERREUR_BUFTACHETX_PLEIN

	i++;
	erreurs[i].code = "0965";
	erreurs[i].erreur = "I_BTX_P";//ID_ERREUR_BUFTX_PLEIN

	i++;
	erreurs[i].code = "0966";
	erreurs[i].erreur = "I_CCARN_TX";//ID_ERREUR_CTRLCAR_NON_TX

	i++;
	erreurs[i].code = "0967";
	erreurs[i].erreur = "I_E_N_PREV";//ID_ERREUR_EFFAC_NON_PREVU

	i++;
	erreurs[i].code = "0968";
	erreurs[i].erreur = "I_T_N_PREV";//ID_ERREUR_TIRAIT_NON_PREVU

	i++;
	erreurs[i].code = "0969";
	erreurs[i].erreur = "I_ITRX_BND";//ID_ERREUR_ITRX_BUFNONDISPO

	i++;
	erreurs[i].code = "096A";
	erreurs[i].erreur = "I_ITRXOVPF";//ID_ERREUR_ITRX_OV_PAR_FRA

	i++;
	erreurs[i].code = "096B";
	erreurs[i].erreur = "I_IT_BUSY";//ID_ERREUR_IT_BUSY

	i++;
	erreurs[i].code = "096C";
	erreurs[i].erreur = "I_CMDEINRE";//ID_ERREUR_CMDE_INCO_RECO

	i++;
	erreurs[i].code = "096D";
	erreurs[i].erreur = "I_BADIRXBD";//ID_ERREUR_BAD_INDICE_RXBD

	i++;
	erreurs[i].code = "096E";
	erreurs[i].erreur = "I_LXOFDXOF";//ID_ERREUR_LOCXOFF_DISXOFF

	i++;
	erreurs[i].code = "096F";
	erreurs[i].erreur = "I_BTRXPDON";//ID_ERREUR_BUFTACHERX_PLEIN_DISTANTXON

	i++;
	erreurs[i].code = "0970";
	erreurs[i].erreur = "I_BTRXPDOF";//ID_ERREUR_BUFTACHERX_PLEIN_DISTANTXOFF

	i++;
	erreurs[i].code = "0971";
	erreurs[i].erreur = "I_CCAR_IN";//ID_ERREUR_CTRLCAR_INCONNU

	i++;
	erreurs[i].code = "0972";
	erreurs[i].erreur = "I_ITTXIDLE";//ID_ERREUR_ITTX_TXIDLE

	i++;
	erreurs[i].code = "0973";
	erreurs[i].erreur = "I_P_V";//ID_ERROR_PANNE_VOIES

	i++;
	erreurs[i].code = "0974";
	erreurs[i].erreur = "I_PSMBALNV";//ID_ERREUR_PSMBAL_NON_VIDE

	i++;
	erreurs[i].code = "0A00";
	erreurs[i].erreur = "I_ACQ_SDHM";//ID_ERREUR_ACQ_SEQ_DHM

	i++;
	erreurs[i].code = "0A01";
	erreurs[i].erreur = "I_MGMDMHDL";//ID_ERREUR_MSG_MDM_HDLMDM

	i++;
	erreurs[i].code = "0A02";
	erreurs[i].erreur = "I_MGMDMSEQ";//ID_ERREUR_MSG_MDM_SEQ

	i++;
	erreurs[i].code = "0A03";
	erreurs[i].erreur = "I_MGMDMDHM";//ID_ERREUR_MSG_MDM_DHM

	i++;
	erreurs[i].code = "0A04";
	erreurs[i].erreur = "I_MGMDMTC";//ID_ERREUR_MSG_MDM_TC

	i++;
	erreurs[i].code = "0A05";
	erreurs[i].erreur = "I_CRSTMDM";//ID_ERREUR_CR_STATUS_MDM

	i++;
	erreurs[i].code = "0A06";
	erreurs[i].erreur = "I_CMDMDMS";//ID_ERREUR_CMDE_MDM_SEQ

	i++;
	erreurs[i].code = "0A07";
	erreurs[i].erreur = "I_CMHDLMD";//ID_ERREUR_CMDE_MDM_HDLMDM

	i++;
	erreurs[i].code = "0A08";
	erreurs[i].erreur = "I_ATCCMD";//ID_ERREUR_AUTO_TC_CMD

	i++;
	erreurs[i].code = "0A09";
	erreurs[i].erreur = "I_ACQ_STC";//ID_ERREUR_ACQ_SEQ_TC

	i++;
	erreurs[i].code = "0A0A";
	erreurs[i].erreur = "I_MGTSIGTC";//ID_ERREUR_MSG_TELESIG_TC

	i++;
	erreurs[i].code = "0A0B";
	erreurs[i].erreur = "I_MGTSGDHM";//ID_ERREUR_MSG_TELESIG_DHM

	i++;
	erreurs[i].code = "0A0C";
	erreurs[i].erreur = "I_PMGHDLTC";//ID_ERREUR_POST_MSG_HDLTC_TC

	i++;
	erreurs[i].code = "0A0D";
	erreurs[i].erreur = "I_NB_MG_E";//ID_ERREUR_NB_MSG_EMISSION

	i++;
	erreurs[i].code = "0A0E";
	erreurs[i].erreur = "I_NB_MG_T";//ID_ERREUR_NB_MSG_TEMPS

	i++;
	erreurs[i].code = "0A0F";
	erreurs[i].erreur = "I_SEACKCMD";//ID_ERREUR_SEQ_ACK_CMD

	i++;
	erreurs[i].code = "0A10";
	erreurs[i].erreur = "I_SCMDEOPE";//ID_ERREUR_SEQ_CMDE_OPERATEUR

	i++;
	erreurs[i].code = "0A11";
	erreurs[i].erreur = "I_STSG_SYS";//ID_ERREUR_SEQ_TELESIG_SYST

	i++;
	erreurs[i].code = "0A12";
	erreurs[i].erreur = "I_P_MGSMDM";//ID_ERREUR_POST_MSG_SEQ_MDM

	i++;
	erreurs[i].code = "0A13";
	erreurs[i].erreur = "I_S_A_ACQ";//ID_ERREUR_SEQ_ATTEND_ACQ

	i++;
	erreurs[i].code = "0A14";
	erreurs[i].erreur = "I_SMCMDEMD";//ID_ERREUR_SEQ_MEMO_CMDE_MDM

	i++;
	erreurs[i].code = "0A15";
	erreurs[i].erreur = "I_SCMDEEC";//ID_ERREUR_SEQ_CMDE_EN_COURS

	i++;
	erreurs[i].code = "0A64";
	erreurs[i].erreur = "I_SC_P_ENB";//ID_ERREUR_SC_POST_ENVOIBLOC

	i++;
	erreurs[i].code = "0A65";
	erreurs[i].erreur = "I_SC_PMG_R";//ID_ERREUR_SC_POST_MSG_RECU

	i++;
	erreurs[i].code = "0A66";
	erreurs[i].erreur = "I_SCPCMDST";//ID_ERREUR_SC_POST_CMDE_TC_STOPTEST

	i++;
	erreurs[i].code = "0A67";
	erreurs[i].erreur = "I_SCPTCI";//ID_ERREUR_SC_POST_TC_INIT

	i++;
	erreurs[i].code = "0A68";
	erreurs[i].erreur = "I_SCPCMDEL";//ID_ERREUR_SC_POST_CMDE_TC_LANGUE

	i++;
	erreurs[i].code = "0A69";
	erreurs[i].erreur = "I_SCPCMDEE";//ID_ERREUR_SC_POST_CMDE_TC_EXPLOIT

	i++;
	erreurs[i].code = "0A60A";
	erreurs[i].erreur = "I_SCPCMDEC";//ID_ERREUR_SC_POST_CMDE_TC_CONF

	i++;
	erreurs[i].code = "0A6B";
	erreurs[i].erreur = "I_SCPCMDES";//ID_ERREUR_SC_POST_CMDE_TC_SETUP

	i++;
	erreurs[i].code = "0A6C";
	erreurs[i].erreur = "I_SCPCMDEI";//ID_ERREUR_SC_POST_CMDE_TC_INIT

	i++;
	erreurs[i].code = "0A6D";
	erreurs[i].erreur = "I_SCPCMACT";//ID_ERREUR_SC_POST_CMDE_TC_ACT

	i++;
	erreurs[i].code = "0A6E";
	erreurs[i].erreur = "I_SPCMDACT";//ID_ERREUR_SC_POST_CMDE_TC_DISACT

	i++;
	erreurs[i].code = "0A6F";
	erreurs[i].erreur = "I_SCPCMDET";//ID_ERREUR_SC_POST_CMDE_TC_TEST

	i++;
	erreurs[i].code = "0A70";
	erreurs[i].erreur = "I_SCPCMFTU";//ID_ERREUR_SC_POST_CMDE_TC_FTUNE

	i++;
	erreurs[i].code = "0A71";
	erreurs[i].erreur = "I_SCPCMFOR";//ID_ERREUR_SC_POST_CMDE_TC_FORMAT

	i++;
	erreurs[i].code = "0A72";
	erreurs[i].erreur = "I_SCPMDMI";//ID_ERREUR_SC_POST_MDM_INIT

	i++;
	erreurs[i].code = "0A73";
	erreurs[i].erreur = "I_SCPAMDMS";//ID_ERREUR_SC_POST_ACQ_MDM_SEQ

	i++;
	erreurs[i].code = "0A74";
	erreurs[i].erreur = "I_SCPSA";//ID_ERREUR_SC_POST_SEQ_ANOMALIE

	i++;
	erreurs[i].code = "0A75";
	erreurs[i].erreur = "I_SCTS_M_D";//ID_ERREUR_SC_POST_TS_MDM_DHM

	i++;
	erreurs[i].code = "0A76";
	erreurs[i].erreur = "I_SCPTSMTC";//ID_ERREUR_SC_POST_TS_MDM_TC

	i++;
	erreurs[i].code = "0A77";
	erreurs[i].erreur = "I_SCPDI";//ID_ERREUR_SC_POST_DHM_INIT

	i++;
	erreurs[i].code = "0A78";
	erreurs[i].erreur = "I_SCPCMDST";//ID_ERREUR_SC_POST_CMDE_DHM_STOPTEST

	i++;
	erreurs[i].code = "0A79";
	erreurs[i].erreur = "I_SCPCMDDE";//ID_ERREUR_SC_POST_CMDE_DHM_EXPLOIT

	i++;
	erreurs[i].code = "0A7A";
	erreurs[i].erreur = "I_SCPCMDFT";//ID_ERREUR_SC_POST_CMDE_DHM_FTUNE

	i++;
	erreurs[i].code = "0A7B";
	erreurs[i].erreur = "I_SCPCMDDL";//ID_ERREUR_SC_POST_CMDE_DHM_LANGUE

	i++;
	erreurs[i].code = "0A7C";
	erreurs[i].erreur = "I_SCPCMDDR";//ID_ERREUR_SC_POST_CMDE_DHM_REMOTE

	i++;
	erreurs[i].code = "0A7D";
	erreurs[i].erreur = "I_SCPCMDDC";//ID_ERREUR_SC_POST_CMDE_DHM_CONF

	i++;
	erreurs[i].code = "0A7E";
	erreurs[i].erreur = "I_SCPCMDDS";//ID_ERREUR_SC_POST_CMDE_DHM_SETUP

	i++;
	erreurs[i].code = "0A7F";
	erreurs[i].erreur = "I_SCPCMDAT";//ID_ERREUR_SC_POST_CMDE_DHM_AUTOTEST

	i++;
	erreurs[i].code = "0A80";
	erreurs[i].erreur = "I_SCPCDACT";//ID_ERREUR_SC_POST_CMDE_DHM_ACT

	i++;
	erreurs[i].code = "0A81";
	erreurs[i].erreur = "I_SCPCDDAT";//ID_ERREUR_SC_POST_CMDE_DHM_DISACT

	i++;
	erreurs[i].code = "0A82";
	erreurs[i].erreur = "I_SCPCDT";//ID_ERREUR_SC_POST_CMDE_DHM_TEST

	i++;
	erreurs[i].code = "0A83";
	erreurs[i].erreur = "I_SCPACQSO";//ID_ERREUR_SC_POST_ACQ_SEQ_OPER

	i++;
	erreurs[i].code = "0A84";
	erreurs[i].erreur = "I_SCPSI";//ID_ERREUR_SC_POST_SEQ_INIT

	i++;
	erreurs[i].code = "0A85";
	erreurs[i].erreur = "I_SCPCSM";//ID_ERREUR_SC_POST_CMDE_SEQ_MDM

	i++;
	erreurs[i].code = "0A86";
	erreurs[i].erreur = "I_SCPTI";//ID_ERREUR_SC_POST_TEMPS_INIT

	i++;
	erreurs[i].code = "0A87";
	erreurs[i].erreur = "I_SC_PTOUT";//ID_ERREUR_SC_POST_TIMEOUT

	i++;
	erreurs[i].code = "0A88";
	erreurs[i].erreur = "I_SCPTSSO";//ID_ERREUR_SC_POST_TS_SEQ_OPER

	i++;
	erreurs[i].code = "0A89";
	erreurs[i].erreur = "I_SCPDRCRS";//ID_ERREUR_SC_POST_DRV_CRY_SEQ

	i++;
	erreurs[i].code = "0A8A";
	erreurs[i].erreur = "I_SCPDRCRI";//ID_ERREUR_SC_POST_DRV_CRY_INIT

	i++;
	erreurs[i].code = "0A8B";
	erreurs[i].erreur = "I_SCPHDRCR";//ID_ERREUR_SC_POST_HDLCRY_CRY

	i++;
	erreurs[i].code = "0A8C";
	erreurs[i].erreur = "I_SCPTTXS1";//ID_ERREUR_SC_PEND_TASK_TX_SCC1

	i++;
	erreurs[i].code = "0A8D";
	erreurs[i].erreur = "I_IN_M";//ID_ERREUR_INCIDENT_MODEM

	i++;
	erreurs[i].code = "0A8E";
	erreurs[i].erreur = "I_A_ACQ";//ID_ERREUR_ATT_ACQ

	i++;
	erreurs[i].code = "0A8F";
	erreurs[i].erreur = "I_M_ACQ";//ID_ERREUR_MAUVAIS_ACQ

	i++;
	erreurs[i].code = "0A90";
	erreurs[i].erreur = "C_E_C_M1_I";//C_ERR_CARTE_MODEM1_INEXISTANTE

	i++;
	erreurs[i].code = "0A91";
	erreurs[i].erreur = "C_E_C_M2_I";//C_ERR_CARTE_MODEM2_INEXISTANTE

	i++;
	erreurs[i].code = "0A92";
	erreurs[i].erreur = "C_E_P_NV_I";//C_ERR_PARAM_NUM_VOIE_INVALIDE

	i++;
	erreurs[i].code = "0A93";
	erreurs[i].erreur = "C_E_U_CONF";//C_ERR_UPDATE_CONFIG

	i++;
	erreurs[i].code = "0A94";
	erreurs[i].erreur = "C_E_V_N_D";//C_ERR_VOIE_NON_DESACTIVEE

	i++;
	erreurs[i].code = "0A95";
	erreurs[i].erreur = "ID_ECIPTI";//ID_ERR_CLASSE_INCONNUE_PDT_INIT

	i++;
	erreurs[i].code = "0A96";
	erreurs[i].erreur = "ID_EAQRPI";//ID_ERR_ACQ_RECU_PDT_INIT

	i++;
	erreurs[i].code = "0A97";
	erreurs[i].erreur = "C_ECMDBADP";//C_ERR_CMD_BAD_PARAM

	i++;
	erreurs[i].code = "942E";
	erreurs[i].erreur = "CHARC_GT";//C_ERR_CHARC_GT

}

/* **************************************************************************
METHODE :		~CEquipM1752()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquipM1752::~CEquipM1752()
{

}

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipM1752::Allocation()
{
	t_affecte ligne;

	glob_paramsimu->Equipement(index,&ligne);

	if(proto == NULL)
	{
		proto = new CProtoTRC1752(ligne.format,this);
	}

	if(ihm == NULL)
	{
		ihm = new CDlgTRC1752;
    }

	ihm->Associe(this);

	ihm->Create(F10_IDD_TRC1752,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

}

/* **************************************************************************
METHODE :		Power()
TRAITEMENT:		Mise en route de l'equipement
***************************************************************************	*/
BOOL CEquipM1752::Power()
{
	BOOL etat = CEquip::Power();

	if (etat == TRUE)
	{
		// Lancement des tests
		SetPanne(DEFAULT_INT_VALUE);
		SetTestProgress("TIROIR");

		//***************************

	} else
	{
		// Effacement des tables
		// init modem
		ReinitModem();
	}

	return etat;
}

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipM1752::Charge_Contexte(char *fichier)
{
	int 	i,j;

	AfxGetApp()->DoWaitCursor(1);

	ifstream file(fichier);

	istringstream stream_tmp, stream_tmp2;
	string tmp, ligne;

	getline( file, ligne );
	getline( file, ligne );

	getline( file, ligne );
	if (ligne.substr(0, 5) == "P000=") {
		{
			if (ligne.erase(0, 5) != "MODEM_TRC1752")
			{
				AjouterMessage("**** Erreur fichier non conforme à l'équipement",-1);
				return FALSE;
			}
		}
	}

	EnterCriticalSection((CRITICAL_SECTION*)&crit);

	//mode
	getline(file, ligne);
	if (ligne.substr(0, 5) == "P001=")
		mode = IsStatus(ligne);

		//mode = atoi((ligne.erase(0,5)).c_str());

	//clock_pilot
	getline(file, ligne); if (ligne.substr(0, 5) == "P002=")
		clock_pilot = ligne.erase(0,5);

	//PilExt
	getline(file, ligne);
	if (ligne.substr(0, 5) == "P003=")
		PilExt = IsStatus(ligne);

		//PilExt = atoi((ligne.erase(0,5)).c_str());

	//inr
	getline(file, ligne); if (ligne.substr(0, 5) == "P004=")
		inr = ligne.erase(0,5);

	//inr_rate
	getline(file, ligne); if (ligne.substr(0, 5) == "P005=")
		inr_rate = atoi((ligne.erase(0,5)).c_str());

	//gic
	getline(file, ligne); if (ligne.substr(0, 5) == "P006=")
		gic = ligne.erase(0,5);

	//origine_heure
	getline(file, ligne); if (ligne.substr(0, 5) == "P007=")
		origine_heure = ligne.erase(0,5);

//distant

	//marche
	getline(file, ligne);
	if (ligne.substr(0, 5) == "P008=")
		distant.marche = IsStatus(ligne);

		//distant.marche = atoi((ligne.erase(0,5)).c_str());

	//distant selfaddress
	getline(file, ligne); if (ligne.substr(0, 5) == "P009=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		distant.selfaddress.clear();

		while ( getline( stream_tmp, tmp, ';' ) )
			distant.selfaddress.push_back(tmp);
	}

	//distant current_selfaddress
	getline(file, ligne); if (ligne.substr(0, 5) == "P010=")
		distant.current_selfaddress = atoi((ligne.erase(0,5)).c_str());

	//distant stations
	getline(file, ligne); if (ligne.substr(0, 5) == "P011=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		distant.stations.clear();

		while ( getline( stream_tmp, tmp, ';' ) )
			distant.stations.push_back(tmp);
	}

	//distant current_station
	getline(file, ligne); if (ligne.substr(0, 5) == "P012=")
		distant.current_station = atoi((ligne.erase(0,5)).c_str());

	//distant reseaux
	getline(file, ligne); if (ligne.substr(0, 5) == "P013=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		distant.reseaux.clear();

		while ( getline( stream_tmp, tmp, ';' ) )
			distant.reseaux.push_back(tmp);
	}

	//distant current_reseau
	getline(file, ligne); if (ligne.substr(0, 5) == "P014=")
		distant.current_reseau = atoi((ligne.erase(0,5)).c_str());

	//distant type_appel
	getline(file, ligne); if (ligne.substr(0, 5) == "P015=")
		distant.type_appel = ligne.erase(0,5);

	//distant type_ale
	getline(file, ligne); if (ligne.substr(0, 5) == "P016=")
		distant.type_ale = ligne.erase(0,5);

	//distant channel
	getline(file, ligne); if (ligne.substr(0, 5) == "P017=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<10)
		{
			distant.channel[i] = atoi(tmp.c_str())!=0;
			i++;
		}
	}

	//distant amd_chat
	getline(file, ligne); if (ligne.substr(0, 5) == "P018=")
		distant.amd_chat = ligne.erase(0,5);

	//distant amd_chat_recu
	getline(file, ligne); if (ligne.substr(0, 5) == "P019=")
		distant.amd_chat_recu = ligne.erase(0,5);

	//manufacturer
	getline(file, ligne); if (ligne.substr(0, 5) == "P020=")
		manufacturer = ligne.erase(0,5);

	//identity
	getline(file, ligne); if (ligne.substr(0, 5) == "P021=")
		identity = ligne.erase(0,5);

	//board_management capabilities
	getline(file, ligne); if (ligne.substr(0, 5) == "P022=")
		board_management.capabilities = ligne.erase(0,5);

	//board_management number
	getline(file, ligne); if (ligne.substr(0, 5) == "P023=")
		board_management.number = ligne.erase(0,5);

	//board_management release
	getline(file, ligne); if (ligne.substr(0, 5) == "P024=")
		board_management.release = ligne.erase(0,5);

	//board_management day
	getline(file, ligne); if (ligne.substr(0, 5) == "P025=")
		board_management.day = ligne.erase(0,5);

	//board_management month
	getline(file, ligne); if (ligne.substr(0, 5) == "P026=")
		board_management.month = ligne.erase(0,5);

	//board_management year
	getline(file, ligne); if (ligne.substr(0, 5) == "P027=")
		board_management.year = ligne.erase(0,5);

	//board_management date_and_time
	getline(file, ligne); if (ligne.substr(0, 5) == "P028=")
		board_management.date_and_time = ligne.erase(0,5);

	//board_management time_accuracy
	getline(file, ligne); if (ligne.substr(0, 5) == "P029=")
		board_management.time_accuracy = atoi((ligne.erase(0,5)).c_str());

	//board_management date_origin
	getline(file, ligne); if (ligne.substr(0, 5) == "P030=")
		board_management.date_origin = ligne.erase(0,5);

	//board_management last_date_and_time
	getline(file, ligne); if (ligne.substr(0, 5) == "P031=")
		board_management.last_date_and_time = ligne.erase(0,5);

	//board_management time_lag
	getline(file, ligne); if (ligne.substr(0, 5) == "P032=")
		board_management.time_lag = atoi((ligne.erase(0,5)).c_str());

	//board_1 capabilities
	getline(file, ligne); if (ligne.substr(0, 5) == "P033=")
		board_1.capabilities = ligne.erase(0,5);

	//board_1 number
	getline(file, ligne); if (ligne.substr(0, 5) == "P034=")
		board_1.number = ligne.erase(0,5);

	//board_1 release
	getline(file, ligne); if (ligne.substr(0, 5) == "P035=")
		board_1.release = ligne.erase(0,5);

	//board_1 day
	getline(file, ligne); if (ligne.substr(0, 5) == "P036=")
		board_1.day = ligne.erase(0,5);

	//board_1 month
	getline(file, ligne); if (ligne.substr(0, 5) == "P037=")
		board_1.month = ligne.erase(0,5);

	//board_1 year
	getline(file, ligne); if (ligne.substr(0, 5) == "P038=")
		board_1.year = ligne.erase(0,5);

	//board_1 date_and_time
	getline(file, ligne); if (ligne.substr(0, 5) == "P039=")
		board_1.date_and_time = ligne.erase(0,5);

	//board_1 time_accuracy
	getline(file, ligne); if (ligne.substr(0, 5) == "P040=")
		board_1.time_accuracy = atoi((ligne.erase(0,5)).c_str());

	//board_1 date_origin
	getline(file, ligne); if (ligne.substr(0, 5) == "P041=")
		board_1.date_origin = ligne.erase(0,5);

	//board_1 last_date_and_time
	getline(file, ligne); if (ligne.substr(0, 5) == "P042=")
		board_1.last_date_and_time = ligne.erase(0,5);

	//board_1 time_lag
	getline(file, ligne); if (ligne.substr(0, 5) == "P043=")
		board_1.time_lag = atoi((ligne.erase(0,5)).c_str());

	//board_2 capabilities
	getline(file, ligne); if (ligne.substr(0, 5) == "P044=")
		board_2.capabilities = ligne.erase(0,5);

	//board_2 number
	getline(file, ligne); if (ligne.substr(0, 5) == "P045=")
		board_2.number = ligne.erase(0,5);

	//board_2 release
	getline(file, ligne); if (ligne.substr(0, 5) == "P046=")
		board_2.release = ligne.erase(0,5);

	//board_2 day
	getline(file, ligne); if (ligne.substr(0, 5) == "P047=")
		board_2.day = ligne.erase(0,5);

	//board_2 month
	getline(file, ligne); if (ligne.substr(0, 5) == "P048=")
		board_2.month = ligne.erase(0,5);

	//board_2 year
	getline(file, ligne); if (ligne.substr(0, 5) == "P049=")
		board_2.year = ligne.erase(0,5);

	//board_2 date_and_time
	getline(file, ligne); if (ligne.substr(0, 5) == "P050=")
		board_2.date_and_time = ligne.erase(0,5);

	//board_2 time_accuracy
	getline(file, ligne); if (ligne.substr(0, 5) == "P051=")
		board_2.time_accuracy = atoi((ligne.erase(0,5)).c_str());

	//board_2 date_origin
	getline(file, ligne); if (ligne.substr(0, 5) == "P052=")
		board_2.date_origin = ligne.erase(0,5);

	//board_2 last_date_and_time
	getline(file, ligne); if (ligne.substr(0, 5) == "P053=")
		board_2.last_date_and_time = ligne.erase(0,5);

	//board_2 time_lag
	getline(file, ligne); if (ligne.substr(0, 5) == "P054=")
		board_2.time_lag = atoi((ligne.erase(0,5)).c_str());

	//quadrivoie
	getline(file, ligne);
	if (ligne.substr(0, 5) == "P055=")
		quadrivoie = IsStatus(ligne);

		//quadrivoie = atoi((ligne.erase(0,5)).c_str());

	//emetteur_marche
	getline(file, ligne);
	if (ligne.substr(0, 5) == "P056=")
		emetteur_marche = IsStatus(ligne);

		//emetteur_marche = atoi((ligne.erase(0,5)).c_str());

	//emetteur_panne_majeure
	getline(file, ligne);
	if (ligne.substr(0, 5) == "P057=")
		emetteur_panne_majeure = IsStatus(ligne);

		//emetteur_panne_majeure = atoi((ligne.erase(0,5)).c_str());

	//emetteur_panne_tc
	getline(file, ligne);
	if (ligne.substr(0, 5) == "P058=")
		emetteur_panne_majeure = IsStatus(ligne);

		//emetteur_panne_tc = atoi((ligne.erase(0,5)).c_str());

	//recepteur_marche
	getline(file, ligne);
	if (ligne.substr(0, 5) == "P059=")
		recepteur_marche = IsStatus(ligne);

		//recepteur_marche = atoi((ligne.erase(0,5)).c_str());

	//recepteur_panne_majeure
	getline(file, ligne);
	if (ligne.substr(0, 5) == "P060=")
		recepteur_panne_majeure = IsStatus(ligne);

		//recepteur_panne_majeure = atoi((ligne.erase(0,5)).c_str());

	//recepteur_panne_tc
	getline(file, ligne);
	if (ligne.substr(0, 5) == "P061=")
		recepteur_panne_tc = IsStatus(ligne);

		//recepteur_panne_tc = atoi((ligne.erase(0,5)).c_str());

	//emetteur_emission
	getline(file, ligne);
	if (ligne.substr(0, 5) == "P062=")
		emetteur_emission = IsStatus(ligne);

		//emetteur_emission = atoi((ligne.erase(0,5)).c_str());

	//test_map
	getline(file, ligne); if (ligne.substr(0, 5) == "P063=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_TESTS)
		{
			test_map[TESTS[i]] = atoi(tmp.c_str())!=0;
			i++;
		}
	}

//channels_configurations
	// waveform
	getline(file, ligne); if (ligne.substr(0, 5) == "P064=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].waveform = tmp.c_str();
			i++;
		}
	}

	// diversity
	getline(file, ligne); if (ligne.substr(0, 5) == "P065=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].diversity = tmp.c_str();
			i++;
		}
	}

	// direction
	getline(file, ligne); if (ligne.substr(0, 5) == "P066=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].direction = tmp.c_str();
			i++;
		}
	}

	// af_transmission_baudrate
	getline(file, ligne); if (ligne.substr(0, 5) == "P067=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].af_transmission_baudrate = atoi(tmp.c_str());
			i++;
		}
	}

	// af_transmission_codingtype
	getline(file, ligne); if (ligne.substr(0, 5) == "P068=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].af_transmission_codingtype = tmp.c_str();
			i++;
		}
	}

	// af_transmission_interleaving
	getline(file, ligne); if (ligne.substr(0, 5) == "P069=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].af_transmission_interleaving = tmp.c_str();
			i++;
		}
	}

	// transmission_carrier_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P070=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].transmission_carrier_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// transmission_space_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P071=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].transmission_space_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// transmission_mark_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P072=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].transmission_mark_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// af_reception_baudrate
	getline(file, ligne); if (ligne.substr(0, 5) == "P073=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].af_reception_baudrate = atoi(tmp.c_str());
			i++;
		}
	}

	// af_reception_codingtype
	getline(file, ligne); if (ligne.substr(0, 5) == "P074=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].af_reception_codingtype = tmp.c_str();
			i++;
		}
	}

	// af_reception_interleaving
	getline(file, ligne); if (ligne.substr(0, 5) == "P075=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].af_reception_interleaving = tmp.c_str();
			i++;
		}
	}

	// reception_carrier_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P076=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].reception_carrier_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// reception_space_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P077=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].reception_space_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// reception_mark_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P078=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].reception_mark_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// slave_baudrate
	getline(file, ligne); if (ligne.substr(0, 5) == "P079=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].slave_baudrate = atoi(tmp.c_str());
			i++;
		}
	}

	// slave_codingtype
	getline(file, ligne); if (ligne.substr(0, 5) == "P080=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].slave_codingtype = tmp.c_str();
			i++;
		}
	}

	// slave_interleaving
	getline(file, ligne); if (ligne.substr(0, 5) == "P081=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].slave_interleaving = tmp.c_str();
			i++;
		}
	}

	// slave_carrier_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P082=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].slave_carrier_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// slave_direction
	getline(file, ligne); if (ligne.substr(0, 5) == "P083=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].slave_direction = tmp.c_str();
			i++;
		}
	}

	// use_data
	getline(file, ligne); if (ligne.substr(0, 5) == "P084=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS_CONFIGURATIONS)
		{
			channels_configurations[CHANNELS_CONFIGURATION[i]].use_data = tmp.c_str();
			i++;
		}
	}

//interfaces_configurations

	// type
	getline(file, ligne); if (ligne.substr(0, 5) == "P085=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].type = tmp.c_str();
			i++;
		}
	}

	// electrical_characteristics
	getline(file, ligne); if (ligne.substr(0, 5) == "P086=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].electrical_characteristics = tmp.c_str();
			i++;
		}
	}

	// transmission_baudrate
	getline(file, ligne); if (ligne.substr(0, 5) == "P087=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].transmission_baudrate = atoi(tmp.c_str());
			i++;
		}
	}

	// reception_baudrate
	getline(file, ligne); if (ligne.substr(0, 5) == "P088=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].reception_baudrate = atoi(tmp.c_str());
			i++;
		}
	}

	// direction
	getline(file, ligne); if (ligne.substr(0, 5) == "P089=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].direction = tmp.c_str();
			i++;
		}
	}

	// validity_time
	getline(file, ligne); if (ligne.substr(0, 5) == "P090=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].validity_time = tmp.c_str();
			i++;
		}
	}

	// binary_integrity
	getline(file, ligne); if (ligne.substr(0, 5) == "P091=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].binary_integrity = tmp.c_str();
			i++;
		}
	}

	// polarity
	getline(file, ligne); if (ligne.substr(0, 5) == "P092=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].polarity = tmp.c_str();
			i++;
		}
	}

	// handshake
	getline(file, ligne); if (ligne.substr(0, 5) == "P093=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].handshake = tmp.c_str();
			i++;
		}
	}

	// character_length
	getline(file, ligne); if (ligne.substr(0, 5) == "P094=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].character_length = atoi(tmp.c_str());
			i++;
		}
	}

	// parity
	getline(file, ligne); if (ligne.substr(0, 5) == "P095=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].parity = tmp.c_str();
			i++;
		}
	}

	// number_stop_bits
	getline(file, ligne); if (ligne.substr(0, 5) == "P096=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].number_stop_bits = atoi(tmp.c_str());
			i++;
		}
	}

	// data_flow_control
	getline(file, ligne); if (ligne.substr(0, 5) == "P097=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_INTERFACES_CONFIGURATIONS)
		{
			interfaces_configurations[INTERFACES_CONFIGURATION[i]].data_flow_control = tmp.c_str();
			i++;
		}
	}

//data_links

	// associated_configuration_id
	getline(file, ligne); if (ligne.substr(0, 5) == "P098=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_DATA_LINK_IDS)
		{
			data_links[DATA_LINK_IDS[i]].associated_configuration_id = tmp.c_str();
			i++;
		}
	}

//aux_interfaces_configurations

	// electrical_characteristics
	getline(file, ligne); if (ligne.substr(0, 5) == "P099=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AUX_INTERFACES_CONFIGURATIONS)
		{
			aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].electrical_characteristics = tmp.c_str();
			i++;
		}
	}

	// baudrate
	getline(file, ligne); if (ligne.substr(0, 5) == "P100=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AUX_INTERFACES_CONFIGURATIONS)
		{
			aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].baudrate = atoi(tmp.c_str());
			i++;
		}
	}

	// character_length
	getline(file, ligne); if (ligne.substr(0, 5) == "P101=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AUX_INTERFACES_CONFIGURATIONS)
		{
			aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].character_length = atoi(tmp.c_str());
			i++;
		}
	}

	// character_parity
	getline(file, ligne); if (ligne.substr(0, 5) == "P102=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AUX_INTERFACES_CONFIGURATIONS)
		{
			aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].character_parity = tmp.c_str();
			i++;
		}
	}

	// number_stop_bits
	getline(file, ligne); if (ligne.substr(0, 5) == "P103=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AUX_INTERFACES_CONFIGURATIONS)
		{
			aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].number_stop_bits = atoi(tmp.c_str());
			i++;
		}
	}

	// radio_address
	getline(file, ligne); if (ligne.substr(0, 5) == "P104=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AUX_INTERFACES_CONFIGURATIONS)
		{
			aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].radio_address = atoi(tmp.c_str());
			i++;
		}
	}

	// equipment_type
	getline(file, ligne); if (ligne.substr(0, 5) == "P105=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AUX_INTERFACES_CONFIGURATIONS)
		{
			aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].equipment_type = tmp.c_str();
			i++;
		}
	}

//local_remote_interfaces_configurations

	// electrical_characteristics
	getline(file, ligne); if (ligne.substr(0, 5) == "P106=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS)
		{
			local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].electrical_characteristics = tmp.c_str();
			i++;
		}
	}

	// baudrate
	getline(file, ligne); if (ligne.substr(0, 5) == "P107=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS)
		{
			local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].baudrate = atoi(tmp.c_str());
			i++;
		}
	}

	// characters_length
	getline(file, ligne); if (ligne.substr(0, 5) == "P108=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS)
		{
			local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].characters_length = atoi(tmp.c_str());
			i++;
		}
	}

	// characters_parity
	getline(file, ligne); if (ligne.substr(0, 5) == "P109=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS)
		{
			local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].characters_parity = tmp.c_str();
			i++;
		}
	}

	// number_stop_bits
	getline(file, ligne); if (ligne.substr(0, 5) == "P110=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS)
		{
			local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].number_stop_bits = atoi(tmp.c_str());
			i++;
		}
	}

//af_channels_configurations

	// input_level
	getline(file, ligne); if (ligne.substr(0, 5) == "P111=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AF_CHANNELS_CONFIGURATIONS)
		{
			af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].input_level = atoi(tmp.c_str());
			i++;
		}
	}

	// output_level
	getline(file, ligne); if (ligne.substr(0, 5) == "P112=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AF_CHANNELS_CONFIGURATIONS)
		{
			af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].output_level = atoi(tmp.c_str());
			i++;
		}
	}

	// interface_type
	getline(file, ligne); if (ligne.substr(0, 5) == "P113=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AF_CHANNELS_CONFIGURATIONS)
		{
			af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].interface_type = tmp.c_str();
			i++;
		}
	}

	// ptt_type
	getline(file, ligne); if (ligne.substr(0, 5) == "P114=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AF_CHANNELS_CONFIGURATIONS)
		{
			af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].ptt_type = tmp.c_str();
			i++;
		}
	}

	// ptt_tempo
	getline(file, ligne); if (ligne.substr(0, 5) == "P115=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AF_CHANNELS_CONFIGURATIONS)
		{
			af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].ptt_tempo = atoi(tmp.c_str());
			i++;
		}
	}

	// mute_characteristics
	getline(file, ligne); if (ligne.substr(0, 5) == "P116=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AF_CHANNELS_CONFIGURATIONS)
		{
			af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].mute_characteristics = tmp.c_str();
			i++;
		}
	}

	// mute_delay
	getline(file, ligne); if (ligne.substr(0, 5) == "P117=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AF_CHANNELS_CONFIGURATIONS)
		{
			af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].mute_delay = atoi(tmp.c_str());
			i++;
		}
	}

	// radio_delay
	getline(file, ligne); if (ligne.substr(0, 5) == "P118=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_AF_CHANNELS_CONFIGURATIONS)
		{
			af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].radio_delay = atoi(tmp.c_str());
			i++;
		}
	}

//channels

	// status_local_remote_control
	getline(file, ligne); if (ligne.substr(0, 5) == "P119=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].status_local_remote_control = tmp.c_str();
			i++;
		}
	}

	// associated_af_configuration
	getline(file, ligne); if (ligne.substr(0, 5) == "P120=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].associated_af_configuration = tmp.c_str();
			i++;
		}
	}

	// data_link_id
	getline(file, ligne); if (ligne.substr(0, 5) == "P121=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].data_link_id = tmp.c_str();
			i++;
		}
	}

	// type
	getline(file, ligne); if (ligne.substr(0, 5) == "P122=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].type = tmp.c_str();
			i++;
		}
	}

	// index_scanset_channel
	getline(file, ligne); if (ligne.substr(0, 5) == "P123=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].index_scanset_channel = atoi(tmp.c_str());
			i++;
		}
	}

	// link_management_type
	getline(file, ligne); if (ligne.substr(0, 5) == "P124=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].link_management_type = tmp.c_str();
			i++;
		}
	}

	// quality_value
	getline(file, ligne); if (ligne.substr(0, 5) == "P125=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].quality_value = atoi(tmp.c_str());
			i++;
		}
	}

	// af_level_received
	getline(file, ligne); if (ligne.substr(0, 5) == "P126=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].af_level_received = atoi(tmp.c_str());
			i++;
		}
	}

	// offset_af_output_level
	getline(file, ligne); if (ligne.substr(0, 5) == "P127=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].offset_af_output_level = atoi(tmp.c_str());
			i++;
		}
	}

	// af_level_received_slave
	getline(file, ligne); if (ligne.substr(0, 5) == "P128=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].af_level_received_slave = atoi(tmp.c_str());
			i++;
		}
	}

	// dopple_offset
	getline(file, ligne); if (ligne.substr(0, 5) == "P129=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].dopple_offset = atoi(tmp.c_str());
			i++;
		}
	}

	// signal_noise_ratio
	getline(file, ligne); if (ligne.substr(0, 5) == "P130=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].signal_noise_ratio = atoi(tmp.c_str());
			i++;
		}
	}

	// direction_transmission
	getline(file, ligne); if (ligne.substr(0, 5) == "P131=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].direction_transmission = tmp.c_str();
			i++;
		}
	}

	// offset_carrier_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P132=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].offset_carrier_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// offset_mark_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P133=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].offset_mark_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// offset_space_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P134=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].offset_space_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// master_diversity
	getline(file, ligne); if (ligne.substr(0, 5) == "P135=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_CHANNELS)
		{
			channels[CHANNELS[i]].master_diversity = atoi(tmp.c_str())!=0;
			i++;
		}
	}

//ale_parameter

	// automatic_sounding
	getline(file, ligne); if (ligne.substr(0, 5) == "P136=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].automatic_sounding = tmp.c_str();
			i++;
		}
	}

	// aging_percentage
	getline(file, ligne); if (ligne.substr(0, 5) == "P137=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].aging_percentage = atoi(tmp.c_str());
			i++;
		}
	}

	// aging_time
	getline(file, ligne); if (ligne.substr(0, 5) == "P138=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].aging_time = tmp.c_str();
			i++;
		}
	}

	// multiservice
	getline(file, ligne); if (ligne.substr(0, 5) == "P139=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].multiservice = tmp.c_str();
			i++;
		}
	}

	// automatic_reconfiguration
	getline(file, ligne); if (ligne.substr(0, 5) == "P140=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].automatic_reconfiguration = tmp.c_str();
			i++;
		}
	}

	// service_activation
	getline(file, ligne); if (ligne.substr(0, 5) == "P141=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].service_activation = atoi(tmp.c_str());
			i++;
		}
	}

	// allcall_message
	getline(file, ligne); if (ligne.substr(0, 5) == "P142=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].allcall_message = tmp.c_str();
			i++;
		}
	}

	// wildcard_message
	getline(file, ligne); if (ligne.substr(0, 5) == "P143=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].wildcard_message = tmp.c_str();
			i++;
		}
	}

	// anycall_message
	getline(file, ligne); if (ligne.substr(0, 5) == "P144=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].anycall_message = tmp.c_str();
			i++;
		}
	}

	// respond
	getline(file, ligne); if (ligne.substr(0, 5) == "P145=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].respond = tmp.c_str();
			i++;
		}
	}

	// scanrate
	getline(file, ligne); if (ligne.substr(0, 5) == "P146=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].scanrate = atoi(tmp.c_str());
			i++;
		}
	}

	// twa_automatic
	getline(file, ligne); if (ligne.substr(0, 5) == "P147=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].twa_automatic = atoi(tmp.c_str());
			i++;
		}
	}

	// twa_manual
	getline(file, ligne); if (ligne.substr(0, 5) == "P148=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].twa_manual = atoi(tmp.c_str());
			i++;
		}
	}

	// twt
	getline(file, ligne); if (ligne.substr(0, 5) == "P149=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].twt = atoi(tmp.c_str());
			i++;
		}
	}

	// tunetime_local
	getline(file, ligne); if (ligne.substr(0, 5) == "P150=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].tunetime_local = atoi(tmp.c_str());
			i++;
		}
	}

	// tunetime_other
	getline(file, ligne); if (ligne.substr(0, 5) == "P151=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].tunetime_other = atoi(tmp.c_str());
			i++;
		}
	}

	// ptt_gestion
	getline(file, ligne); if (ligne.substr(0, 5) == "P152=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].ptt_gestion = tmp.c_str();
			i++;
		}
	}

	// sound_length
	getline(file, ligne); if (ligne.substr(0, 5) == "P153=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].sound_length = atoi(tmp.c_str());
			i++;
		}
	}

	// retries_channel
	getline(file, ligne); if (ligne.substr(0, 5) == "P154=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].retries_channel = atoi(tmp.c_str());
			i++;
		}
	}

	// retries_scanfield
	getline(file, ligne); if (ligne.substr(0, 5) == "P155=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].retries_scanfield = atoi(tmp.c_str());
			i++;
		}
	}

	// long_sound_limit
	getline(file, ligne); if (ligne.substr(0, 5) == "P156=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].long_sound_limit = atoi(tmp.c_str());
			i++;
		}
	}

	// cms_choice
	getline(file, ligne); if (ligne.substr(0, 5) == "P157=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].cms_choice = tmp.c_str();
			i++;
		}
	}

	// ale_termination_frame
	getline(file, ligne); if (ligne.substr(0, 5) == "P158=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].ale_termination_frame = tmp.c_str();
			i++;
		}
	}

	// index_channel_table
	getline(file, ligne); if (ligne.substr(0, 5) == "P159=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].index_channel_table = atoi(tmp.c_str());
			i++;
		}
	}

	// lowest_usable_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P160=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].lowest_usable_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// upper_usable_frequency
	getline(file, ligne); if (ligne.substr(0, 5) == "P161=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].upper_usable_frequency = atoi(tmp.c_str());
			i++;
		}
	}

	// call_type
	getline(file, ligne); if (ligne.substr(0, 5) == "P162=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].call_type = tmp.c_str();
			i++;
		}
	}

	// index_selfaddress
	getline(file, ligne); if (ligne.substr(0, 5) == "P163=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].index_selfaddress = atoi(tmp.c_str());
			i++;
		}
	}

	// quick_identification
	getline(file, ligne); if (ligne.substr(0, 5) == "P164=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].quick_identification = tmp.c_str();
			i++;
		}
	}

	// quality_analysis
	getline(file, ligne); if (ligne.substr(0, 5) == "P165=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].quality_analysis = tmp.c_str();
			i++;
		}
	}

	// station_network_group
	getline(file, ligne); if (ligne.substr(0, 5) == "P166=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].station_network_group = tmp.c_str();
			i++;
		}
	}

	// called_address
	getline(file, ligne); if (ligne.substr(0, 5) == "P167=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].called_address = atoi(tmp.c_str());
			i++;
		}
	}

	// called_address_string
	getline(file, ligne); if (ligne.substr(0, 5) == "P168=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].called_address_string = tmp.c_str();
			i++;
		}
	}


	// index_station_table_group
	getline(file, ligne); if (ligne.substr(0, 5) == "P169=") {

	}

	// agc
	getline(file, ligne); if (ligne.substr(0, 5) == "P170=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].agc = tmp.c_str();
			i++;
		}
	}

	// call_length
	getline(file, ligne); if (ligne.substr(0, 5) == "P171=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].call_length = atoi(tmp.c_str());
			i++;
		}
	}

	// amd_message
	getline(file, ligne); if (ligne.substr(0, 5) == "P172=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].amd_message = tmp.c_str();
			i++;
		}
	}

	// link_protection_level
	getline(file, ligne); if (ligne.substr(0, 5) == "P173=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].link_protection_level = atoi(tmp.c_str());
			i++;
		}
	}

	// key_management
	getline(file, ligne); if (ligne.substr(0, 5) == "P174=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].key_management = tmp.c_str();
			i++;
		}
	}

	// key_position
	getline(file, ligne); if (ligne.substr(0, 5) == "P175=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			ale_parameter[ALE_PARAMETERS[i]].key_position = atoi(tmp.c_str());
			i++;
		}
	}

//table_stored1

	// sad self_address
	getline(file, ligne); if (ligne.substr(0, 5) == "P176=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored1["A1"].sad[i].self_address = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P177=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored1["B1"].sad[i].self_address = tmp.c_str();
			i++;
		}
	}

	// sad net_address
	getline(file, ligne); if (ligne.substr(0, 5) == "P178=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored1["A1"].sad[i].net_address = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P179=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored1["B1"].sad[i].net_address = atoi(tmp.c_str());
			i++;
		}
	}

	// sad slot
	getline(file, ligne); if (ligne.substr(0, 5) == "P180=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored1["A1"].sad[i].slot = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P181=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored1["B1"].sad[i].slot = atoi(tmp.c_str());
			i++;
		}
	}

	// sad valid_channels
	getline(file, ligne); if (ligne.substr(0, 5) == "P182=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored1["A1"].sad[i].valid_channels[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P183=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored1["B1"].sad[i].valid_channels[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	// rch channel
	getline(file, ligne); if (ligne.substr(0, 5) == "P184=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].channel = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P185=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].channel = atoi(tmp.c_str());
			i++;
		}
	}

	// rch tx_freq
	getline(file, ligne); if (ligne.substr(0, 5) == "P186=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].tx_freq = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P187=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].tx_freq = atoi(tmp.c_str());
			i++;
		}
	}

	// rch rx_freq
	getline(file, ligne); if (ligne.substr(0, 5) == "P188=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].rx_freq = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P189=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].rx_freq = atoi(tmp.c_str());
			i++;
		}
	}

	// rch mode_tx
	getline(file, ligne); if (ligne.substr(0, 5) == "P190=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].mode_tx = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P191=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].mode_tx = tmp.c_str();
			i++;
		}
	}

	// rch mode_rx
	getline(file, ligne); if (ligne.substr(0, 5) == "P192=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].mode_rx = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P193=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].mode_tx = tmp.c_str();
			i++;
		}
	}

	// rch bfo
	getline(file, ligne); if (ligne.substr(0, 5) == "P194=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].bfo = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P195=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].bfo = atoi(tmp.c_str());
			i++;
		}
	}

	// rch filter
	getline(file, ligne); if (ligne.substr(0, 5) == "P196=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].filter = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P197=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].filter = atoi(tmp.c_str());
			i++;
		}
	}

	// rch agc
	getline(file, ligne); if (ligne.substr(0, 5) == "P198=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].agc = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P199=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].agc = atoi(tmp.c_str());
			i++;
		}
	}

	// rch squelch
	getline(file, ligne); if (ligne.substr(0, 5) == "P200=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].squelch = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P201=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].squelch = atoi(tmp.c_str());
			i++;
		}
	}

	// rch pwr
	getline(file, ligne); if (ligne.substr(0, 5) == "P202=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].pwr = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P203=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].pwr = atoi(tmp.c_str());
			i++;
		}
	}

	// rch ed
	getline(file, ligne); if (ligne.substr(0, 5) == "P204=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].ed = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P205=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].ed = tmp.c_str();
			i++;
		}
	}

	// rch sound_interv
	getline(file, ligne); if (ligne.substr(0, 5) == "P206=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].sound_interv = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P207=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].sound_interv = atoi(tmp.c_str());
			i++;
		}
	}

	// rch self_add
	getline(file, ligne); if (ligne.substr(0, 5) == "P208=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["A1"].rch[i].self_add = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P209=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored1["B1"].rch[i].self_add = atoi(tmp.c_str());
			i++;
		}
	}

	// net net_address
	getline(file, ligne); if (ligne.substr(0, 5) == "P210=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_NET)
		{
			table_stored1["A1"].net[i].net_address = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P211=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_NET)
		{
			table_stored1["B1"].net[i].net_address = tmp.c_str();
			i++;
		}
	}

	// net net_member
	getline(file, ligne); if (ligne.substr(0, 5) == "P212=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_NET)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_NET_ADDRESS)
			{
				table_stored1["A1"].net[i].net_member[j] = atoi(tmp.c_str());
				j++;
			}
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P213=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_NET)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_NET_ADDRESS)
			{
				table_stored1["B1"].net[i].net_member[j] = atoi(tmp.c_str());
				j++;
			}
			i++;
		}
	}

	// sta address_ale
	getline(file, ligne); if (ligne.substr(0, 5) == "P214=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored1["A1"].sta[i].address_ale = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P215=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored1["B1"].sta[i].address_ale = tmp.c_str();
			i++;
		}
	}

	// sta address_arq
	getline(file, ligne); if (ligne.substr(0, 5) == "P216=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored1["A1"].sta[i].address_arq = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P217=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored1["B1"].sta[i].address_arq = tmp.c_str();
			i++;
		}
	}

	// sta twr
	getline(file, ligne); if (ligne.substr(0, 5) == "P218=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored1["A1"].sta[i].twr = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P219=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored1["B1"].sta[i].twr = atoi(tmp.c_str());
			i++;
		}
	}

	// sta valid_channels
	getline(file, ligne); if (ligne.substr(0, 5) == "P220=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored1["A1"].sta[i].valid_channels[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P221=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored1["B1"].sta[i].valid_channels[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	// sst scan_set_channel
	getline(file, ligne); if (ligne.substr(0, 5) == "P222=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SST)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored1["A1"].sst[i].scan_set_channel[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P223=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SST)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored1["B1"].sst[i].scan_set_channel[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	// lt0 name
	getline(file, ligne); if (ligne.substr(0, 5) == "P224=") {

		stream_tmp.str(ligne.erase(0,5));

		// FDI 11/11/2010
		//stream_tmp.clear();

		//table_stored1["A1"].lt0.name = tmp.c_str();
		table_stored1["A1"].lt0.name = ligne.c_str();
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P225=") {

		stream_tmp.str(ligne.erase(0,5));
		// FDI 11/11/2010
		//stream_tmp.clear();


		//table_stored1["B1"].lt0.name = tmp.c_str();
		table_stored1["B1"].lt0.name = ligne.c_str();
	}

	// lt0 key
	getline(file, ligne); if (ligne.substr(0, 5) == "P226=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LT_KEY)
		{
			table_stored1["A1"].lt0.key[i] = atoi(tmp.c_str())!=0;
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P227=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LT_KEY)
		{
			table_stored1["B1"].lt0.key[i] = atoi(tmp.c_str())!=0;
			i++;
		}
	}

	// lt1 name
	getline(file, ligne); if (ligne.substr(0, 5) == "P228=") {

		stream_tmp.str(ligne.erase(0,5));
		// FDI 11/11/2010
		//stream_tmp.clear();


		//table_stored1["A1"].lt1.name = tmp.c_str();
		table_stored1["A1"].lt1.name = ligne.c_str();
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P229=") {

		stream_tmp.str(ligne.erase(0,5));
		// FDI 11/11/2010
		//stream_tmp.clear();


		//table_stored1["B1"].lt1.name = tmp.c_str();
		table_stored1["B1"].lt1.name = ligne.c_str();
	}

	// lt1 key
	getline(file, ligne); if (ligne.substr(0, 5) == "P230=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LT_KEY)
		{
			table_stored1["A1"].lt1.key[i] = atoi(tmp.c_str())!=0;
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P231=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LT_KEY)
		{
			table_stored1["B1"].lt1.key[i] = atoi(tmp.c_str())!=0;
			i++;
		}
	}

	// ***_present
	getline(file, ligne); if (ligne.substr(0, 5) == "P232=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		getline( stream_tmp, tmp, ';' );
		table_stored1["A1"].sad_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored1["A1"].rch_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored1["A1"].net_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored1["A1"].sta_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored1["A1"].sst_present = atoi(tmp.c_str())!=0;
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P233=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		getline( stream_tmp, tmp, ';' );
		table_stored1["B1"].sad_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored1["B1"].rch_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored1["B1"].net_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored1["B1"].sta_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored1["B1"].sst_present = atoi(tmp.c_str())!=0;
	}

//table_stored2

	// sad self_address
	getline(file, ligne); if (ligne.substr(0, 5) == "P234=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored2["A1"].sad[i].self_address = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P235=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored2["B1"].sad[i].self_address = tmp.c_str();
			i++;
		}
	}

	// sad net_address
	getline(file, ligne); if (ligne.substr(0, 5) == "P236=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored2["A1"].sad[i].net_address = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P237=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored2["B1"].sad[i].net_address = atoi(tmp.c_str());
			i++;
		}
	}

	// sad slot
	getline(file, ligne); if (ligne.substr(0, 5) == "P238=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored2["A1"].sad[i].slot = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P239=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			table_stored2["B1"].sad[i].slot = atoi(tmp.c_str());
			i++;
		}
	}

	// sad valid_channels
	getline(file, ligne); if (ligne.substr(0, 5) == "P240=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored2["A1"].sad[i].valid_channels[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P241=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SAD)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored2["B1"].sad[i].valid_channels[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	// rch channel
	getline(file, ligne); if (ligne.substr(0, 5) == "P242=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].channel = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P243=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].channel = atoi(tmp.c_str());
			i++;
		}
	}

	// rch tx_freq
	getline(file, ligne); if (ligne.substr(0, 5) == "P244=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].tx_freq = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P245=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].tx_freq = atoi(tmp.c_str());
			i++;
		}
	}

	// rch rx_freq
	getline(file, ligne); if (ligne.substr(0, 5) == "P246=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].rx_freq = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P247=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].rx_freq = atoi(tmp.c_str());
			i++;
		}
	}

	// rch mode_tx
	getline(file, ligne); if (ligne.substr(0, 5) == "P248=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].mode_tx = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P249=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].mode_tx = tmp.c_str();
			i++;
		}
	}

	// rch rx_freq
	getline(file, ligne); if (ligne.substr(0, 5) == "P250=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].mode_rx = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P251=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].mode_tx = tmp.c_str();
			i++;
		}
	}

	// rch bfo
	getline(file, ligne); if (ligne.substr(0, 5) == "P252=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].bfo = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P253=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].bfo = atoi(tmp.c_str());
			i++;
		}
	}

	// rch filter
	getline(file, ligne); if (ligne.substr(0, 5) == "P254=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].filter = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P255=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].filter = atoi(tmp.c_str());
			i++;
		}
	}

	// rch agc
	getline(file, ligne); if (ligne.substr(0, 5) == "P256=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].agc = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P257=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].agc = atoi(tmp.c_str());
			i++;
		}
	}

	// rch squelch
	getline(file, ligne); if (ligne.substr(0, 5) == "P258=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].squelch = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P259=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].squelch = atoi(tmp.c_str());
			i++;
		}
	}

	// rch pwr
	getline(file, ligne); if (ligne.substr(0, 5) == "P260=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].pwr = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P261=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].pwr = atoi(tmp.c_str());
			i++;
		}
	}

	// rch ed
	getline(file, ligne); if (ligne.substr(0, 5) == "P262=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].ed = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P263=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].ed = tmp.c_str();
			i++;
		}
	}

	// rch sound_interv
	getline(file, ligne); if (ligne.substr(0, 5) == "P264=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].sound_interv = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P265=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].sound_interv = atoi(tmp.c_str());
			i++;
		}
	}

	// rch self_add
	getline(file, ligne); if (ligne.substr(0, 5) == "P266=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["A1"].rch[i].self_add = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P267=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_RCH)
		{
			table_stored2["B1"].rch[i].self_add = atoi(tmp.c_str());
			i++;
		}
	}

	// net net_address
	getline(file, ligne); if (ligne.substr(0, 5) == "P268=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_NET)
		{
			table_stored2["A1"].net[i].net_address = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P269=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_NET)
		{
			table_stored2["B1"].net[i].net_address = tmp.c_str();
			i++;
		}
	}

	// net net_member
	getline(file, ligne); if (ligne.substr(0, 5) == "P270=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_NET)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_NET_ADDRESS)
			{
				table_stored2["A1"].net[i].net_member[j] = atoi(tmp.c_str());
				j++;
			}
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P271=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_NET)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_NET_ADDRESS)
			{
				table_stored2["B1"].net[i].net_member[j] = atoi(tmp.c_str());
				j++;
			}
			i++;
		}
	}

	// sta address_ale
	getline(file, ligne); if (ligne.substr(0, 5) == "P272=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored2["A1"].sta[i].address_ale = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P273=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored2["B1"].sta[i].address_ale = tmp.c_str();
			i++;
		}
	}

	// sta address_arq
	getline(file, ligne); if (ligne.substr(0, 5) == "P274=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored2["A1"].sta[i].address_arq = tmp.c_str();
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P275=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored2["B1"].sta[i].address_arq = tmp.c_str();
			i++;
		}
	}

	// sta twr
	getline(file, ligne); if (ligne.substr(0, 5) == "P276=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored2["A1"].sta[i].twr = atoi(tmp.c_str());
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P277=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			table_stored2["B1"].sta[i].twr = atoi(tmp.c_str());
			i++;
		}
	}

	// sta valid_channels
	getline(file, ligne); if (ligne.substr(0, 5) == "P278=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored2["A1"].sta[i].valid_channels[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P279=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_STA)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored2["B1"].sta[i].valid_channels[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	// sst scan_set_channel
	getline(file, ligne); if (ligne.substr(0, 5) == "P280=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SST)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored2["A1"].sst[i].scan_set_channel[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P281=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_SST)
		{
			j = 0;
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while ( getline (stream_tmp2, tmp, '/' ) && j<NB_LIST_CHANNEL)
			{
				table_stored2["B1"].sst[i].scan_set_channel[j] = atoi(tmp.c_str())!=0;
				j++;
			}
			i++;
		}
	}

	// lt0 name
	getline(file, ligne); if (ligne.substr(0, 5) == "P282=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		table_stored2["A1"].lt0.name = tmp.c_str();
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P283=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		table_stored2["B1"].lt0.name = tmp.c_str();
	}

	// lt0 key
	getline(file, ligne); if (ligne.substr(0, 5) == "P284=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LT_KEY)
		{
			table_stored2["A1"].lt0.key[i] = atoi(tmp.c_str())!=0;
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P285=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LT_KEY)
		{
			table_stored2["B1"].lt0.key[i] = atoi(tmp.c_str())!=0;
			i++;
		}
	}

	// lt1 name
	getline(file, ligne); if (ligne.substr(0, 5) == "P286=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		table_stored2["A1"].lt1.name = tmp.c_str();
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P287=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		table_stored2["B1"].lt1.name = tmp.c_str();
	}

	// lt1 key
	getline(file, ligne); if (ligne.substr(0, 5) == "P288=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LT_KEY)
		{
			table_stored2["A1"].lt1.key[i] = atoi(tmp.c_str())!=0;
			i++;
		}
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P289=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_LT_KEY)
		{
			table_stored2["B1"].lt1.key[i] = atoi(tmp.c_str())!=0;
			i++;
		}
	}

	// ***_present
	getline(file, ligne); if (ligne.substr(0, 5) == "P290=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		getline( stream_tmp, tmp, ';' );
		table_stored2["A1"].sad_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored2["A1"].rch_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored2["A1"].net_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored2["A1"].sta_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored2["A1"].sst_present = atoi(tmp.c_str())!=0;
	}

	getline(file, ligne); if (ligne.substr(0, 5) == "P291=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		getline( stream_tmp, tmp, ';' );
		table_stored2["B1"].sad_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored2["B1"].rch_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored2["B1"].net_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored2["B1"].sta_present = atoi(tmp.c_str())!=0;
		getline( stream_tmp, tmp, ';' );
		table_stored2["B1"].sst_present = atoi(tmp.c_str())!=0;
	}

//pc_arq

	// fonction
	getline(file, ligne); if (ligne.substr(0, 5) == "P292=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			pc_arq[ALE_PARAMETERS[i]].fonction = tmp.c_str();
			i++;
		}
	}

	// etat
	getline(file, ligne); if (ligne.substr(0, 5) == "P293=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			pc_arq[ALE_PARAMETERS[i]].etat = tmp.c_str();
			i++;
		}
	}

	// modulation
	getline(file, ligne); if (ligne.substr(0, 5) == "P294=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			pc_arq[ALE_PARAMETERS[i]].modulation = tmp.c_str();
			i++;
		}
	}

	// adaptabilite
	getline(file, ligne); if (ligne.substr(0, 5) == "P295=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			pc_arq[ALE_PARAMETERS[i]].adaptabilite = tmp.c_str();
			i++;
		}
	}

	// debit
	getline(file, ligne); if (ligne.substr(0, 5) == "P296=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			pc_arq[ALE_PARAMETERS[i]].debit = tmp.c_str();
			i++;
		}
	}

	// codage
	getline(file, ligne); if (ligne.substr(0, 5) == "P297=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			pc_arq[ALE_PARAMETERS[i]].codage = tmp.c_str();
			i++;
		}
	}

	// adresses_locales
	getline(file, ligne); if (ligne.substr(0, 5) == "P298=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			j = 0;
			pc_arq[ALE_PARAMETERS[i]].adresses_locales.clear();
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while (getline (stream_tmp2, tmp, '/' ))
			{
				pc_arq[ALE_PARAMETERS[i]].adresses_locales.push_back(tmp.c_str());
			}
			i++;
		}
	}

	// adresses_destinataires
	getline(file, ligne); if (ligne.substr(0, 5) == "P299=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			j = 0;
			pc_arq[ALE_PARAMETERS[i]].adresses_destinataires.clear();
			stream_tmp2.str(tmp);
			stream_tmp2.clear();
			while (getline (stream_tmp2, tmp, '/' ))
			{
				pc_arq[ALE_PARAMETERS[i]].adresses_destinataires.push_back(tmp.c_str());
			}
			i++;
		}
	}

	// current_adresse_locale
	getline(file, ligne); if (ligne.substr(0, 5) == "P300=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			pc_arq[ALE_PARAMETERS[i]].current_adresse_locale = atoi(tmp.c_str());
			i++;
		}
	}

	// current_adresse_destinataire
	getline(file, ligne); if (ligne.substr(0, 5) == "P301=") {

		stream_tmp.str(ligne.erase(0,5));
		stream_tmp.clear();

		i = 0;
		while ( getline( stream_tmp, tmp, ';' ) && i<NB_ALE_PARAMETERS)
		{
			pc_arq[ALE_PARAMETERS[i]].current_adresse_destinataire = atoi(tmp.c_str());
			i++;
		}
	}

	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	AfxGetApp()->DoWaitCursor(-1);

	file.close();

	return TRUE;
}

/* **************************************************************************
METHODE :		Sauve_Contexte()
TRAITEMENT:		Sauveagrde le contexte d'exploitation d'un fichier
***************************************************************************	*/
BOOL CEquipM1752::Sauve_Contexte(char *fichier)
{
	int 	i,j;
	char	ligne[TAILLE_MAX_MESSAGE*2];

	ofstream file(fichier);

	string tmp;

	AfxGetApp()->DoWaitCursor(1);

	file << "// Contexte d'exploitation d'un modem TRC1752" << endl;
	file << "// ******************************************" << endl;

	strcpy(ligne,"P000=MODEM_TRC1752");
	file << ligne << endl;

	sprintf(ligne,"P001=%d",mode);
	file << ligne << endl;

	sprintf(ligne,"P002=%s",clock_pilot.c_str());
	file << ligne << endl;

	sprintf(ligne,"P003=%d",PilExt);
	file << ligne << endl;

	sprintf(ligne,"P004=%s",inr.c_str());
	file << ligne << endl;

	sprintf(ligne,"P005=%d",inr_rate);
	file << ligne << endl;

	sprintf(ligne,"P006=%s",gic.c_str());
	file << ligne << endl;

	sprintf(ligne,"P007=%s",origine_heure.c_str());
	file << ligne << endl;

//distant

	sprintf(ligne,"P008=%d",distant.marche);
	file << ligne << endl;

	tmp = "";
	for(i=0; i<distant.selfaddress.size(); i++)
		tmp += distant.selfaddress[i] + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);


	sprintf(ligne,"P009=%s",tmp.c_str());
	file << ligne << endl;

	sprintf(ligne,"P010=%d",distant.current_selfaddress);
	file << ligne << endl;

	tmp = "";
	for(i=0; i<distant.stations.size(); i++)
		tmp += distant.stations[i] + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P011=%s",tmp.c_str());
	file << ligne << endl;

	sprintf(ligne,"P012=%d",distant.current_station);
	file << ligne << endl;

	tmp = "";
	for(i=0; i<distant.reseaux.size(); i++)
		tmp += distant.reseaux[i] + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P013=%s",tmp.c_str());
	file << ligne << endl;

	sprintf(ligne,"P014=%d",distant.current_reseau);
	file << ligne << endl;

	sprintf(ligne,"P015=%s",distant.type_appel.c_str());
	file << ligne << endl;

	sprintf(ligne,"P016=%s",distant.type_ale.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<10; i++)
		tmp += IntToString(distant.channel[i],0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P017=%s",tmp.c_str());
	file << ligne << endl;

	sprintf(ligne,"P018=%s",distant.amd_chat.c_str());
	file << ligne << endl;

	sprintf(ligne,"P019=%s",distant.amd_chat_recu.c_str());
	file << ligne << endl;

	sprintf(ligne,"P020=%s",manufacturer.c_str());
	file << ligne << endl;

	sprintf(ligne,"P021=%s",identity.c_str());
	file << ligne << endl;

	sprintf(ligne,"P022=%s",board_management.capabilities.c_str());
	file << ligne << endl;

	sprintf(ligne,"P023=%s",board_management.number.c_str());
	file << ligne << endl;

	sprintf(ligne,"P024=%s",board_management.release.c_str());
	file << ligne << endl;

	sprintf(ligne,"P025=%s",board_management.day.c_str());
	file << ligne << endl;

	sprintf(ligne,"P026=%s",board_management.month.c_str());
	file << ligne << endl;

	sprintf(ligne,"P027=%s",board_management.year.c_str());
	file << ligne << endl;

	sprintf(ligne,"P028=%s",board_management.date_and_time.c_str());
	file << ligne << endl;

	sprintf(ligne,"P029=%d",board_management.time_accuracy);
	file << ligne << endl;

	sprintf(ligne,"P030=%s",board_management.date_origin.c_str());
	file << ligne << endl;

	sprintf(ligne,"P031=%s",board_management.last_date_and_time.c_str());
	file << ligne << endl;

	sprintf(ligne,"P032=%d",board_management.time_lag);
	file << ligne << endl;

	sprintf(ligne,"P033=%s",board_1.capabilities.c_str());
	file << ligne << endl;

	sprintf(ligne,"P034=%s",board_1.number.c_str());
	file << ligne << endl;

	sprintf(ligne,"P035=%s",board_1.release.c_str());
	file << ligne << endl;

	sprintf(ligne,"P036=%s",board_1.day.c_str());
	file << ligne << endl;

	sprintf(ligne,"P037=%s",board_1.month.c_str());
	file << ligne << endl;

	sprintf(ligne,"P038=%s",board_1.year.c_str());
	file << ligne << endl;

	sprintf(ligne,"P039=%s",board_1.date_and_time.c_str());
	file << ligne << endl;

	sprintf(ligne,"P040=%d",board_1.time_accuracy);
	file << ligne << endl;

	sprintf(ligne,"P041=%s",board_1.date_origin.c_str());
	file << ligne << endl;

	sprintf(ligne,"P042=%s",board_1.last_date_and_time.c_str());
	file << ligne << endl;

	sprintf(ligne,"P043=%d",board_1.time_lag);
	file << ligne << endl;

	sprintf(ligne,"P044=%s",board_2.capabilities.c_str());
	file << ligne << endl;

	sprintf(ligne,"P045=%s",board_2.number.c_str());
	file << ligne << endl;

	sprintf(ligne,"P046=%s",board_2.release.c_str());
	file << ligne << endl;

	sprintf(ligne,"P047=%s",board_2.day.c_str());
	file << ligne << endl;

	sprintf(ligne,"P048=%s",board_2.month.c_str());
	file << ligne << endl;

	sprintf(ligne,"P049=%s",board_2.year.c_str());
	file << ligne << endl;

	sprintf(ligne,"P050=%s",board_2.date_and_time.c_str());
	file << ligne << endl;

	sprintf(ligne,"P051=%d",board_2.time_accuracy);
	file << ligne << endl;

	sprintf(ligne,"P052=%s",board_2.date_origin.c_str());
	file << ligne << endl;

	sprintf(ligne,"P053=%s",board_2.last_date_and_time.c_str());
	file << ligne << endl;

	sprintf(ligne,"P054=%d",board_2.time_lag);
	file << ligne << endl;

	sprintf(ligne,"P055=%d",quadrivoie);
	file << ligne << endl;

	sprintf(ligne,"P056=%d",emetteur_marche);
	file << ligne << endl;

	sprintf(ligne,"P057=%d",emetteur_panne_majeure);
	file << ligne << endl;

	sprintf(ligne,"P058=%d",emetteur_panne_tc);
	file << ligne << endl;

	sprintf(ligne,"P059=%d",recepteur_marche);
	file << ligne << endl;

	sprintf(ligne,"P060=%d",recepteur_panne_majeure);
	file << ligne << endl;

	sprintf(ligne,"P061=%d",recepteur_panne_tc);
	file << ligne << endl;

	sprintf(ligne,"P062=%d",emetteur_emission);
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_TESTS; i++)
		tmp += IntToString(test_map[TESTS[i]],0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P063=%s",tmp.c_str());
	file << ligne << endl;

//channels_configurations

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += channels_configurations[CHANNELS_CONFIGURATION[i]].waveform + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P064=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += channels_configurations[CHANNELS_CONFIGURATION[i]].diversity + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P065=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += channels_configurations[CHANNELS_CONFIGURATION[i]].direction + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P066=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(channels_configurations[CHANNELS_CONFIGURATION[i]].af_transmission_baudrate,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P067=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += channels_configurations[CHANNELS_CONFIGURATION[i]].af_transmission_codingtype + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P068=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += channels_configurations[CHANNELS_CONFIGURATION[i]].af_transmission_interleaving + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P069=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(channels_configurations[CHANNELS_CONFIGURATION[i]].transmission_carrier_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P070=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(channels_configurations[CHANNELS_CONFIGURATION[i]].transmission_space_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P071=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(channels_configurations[CHANNELS_CONFIGURATION[i]].transmission_mark_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P072=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(channels_configurations[CHANNELS_CONFIGURATION[i]].af_reception_baudrate,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P073=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += channels_configurations[CHANNELS_CONFIGURATION[i]].af_reception_codingtype + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P074=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += channels_configurations[CHANNELS_CONFIGURATION[i]].af_reception_interleaving + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P075=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(channels_configurations[CHANNELS_CONFIGURATION[i]].reception_carrier_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P076=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(channels_configurations[CHANNELS_CONFIGURATION[i]].reception_space_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P077=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(channels_configurations[CHANNELS_CONFIGURATION[i]].reception_mark_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P078=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(channels_configurations[CHANNELS_CONFIGURATION[i]].slave_baudrate,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P079=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += channels_configurations[CHANNELS_CONFIGURATION[i]].slave_codingtype + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P080=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += channels_configurations[CHANNELS_CONFIGURATION[i]].slave_interleaving + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P081=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(channels_configurations[CHANNELS_CONFIGURATION[i]].slave_carrier_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P082=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += channels_configurations[CHANNELS_CONFIGURATION[i]].slave_direction + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P083=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS_CONFIGURATIONS; i++)
		tmp += channels_configurations[CHANNELS_CONFIGURATION[i]].use_data + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P084=%s",tmp.c_str());
	file << ligne << endl;

//interfaces_configurations

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += interfaces_configurations[INTERFACES_CONFIGURATION[i]].type + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P085=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += interfaces_configurations[INTERFACES_CONFIGURATION[i]].electrical_characteristics + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P086=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += IntToString(interfaces_configurations[INTERFACES_CONFIGURATION[i]].transmission_baudrate,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P087=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += IntToString(interfaces_configurations[INTERFACES_CONFIGURATION[i]].reception_baudrate,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P088=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += interfaces_configurations[INTERFACES_CONFIGURATION[i]].direction + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P089=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += interfaces_configurations[INTERFACES_CONFIGURATION[i]].validity_time + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P090=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += interfaces_configurations[INTERFACES_CONFIGURATION[i]].binary_integrity + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P091=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += interfaces_configurations[INTERFACES_CONFIGURATION[i]].polarity + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P092=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += interfaces_configurations[INTERFACES_CONFIGURATION[i]].handshake + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P093=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += IntToString(interfaces_configurations[INTERFACES_CONFIGURATION[i]].character_length,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P094=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += interfaces_configurations[INTERFACES_CONFIGURATION[i]].parity + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P095=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += IntToString(interfaces_configurations[INTERFACES_CONFIGURATION[i]].number_stop_bits,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P096=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_INTERFACES_CONFIGURATIONS; i++)
		tmp += interfaces_configurations[INTERFACES_CONFIGURATION[i]].data_flow_control + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P097=%s",tmp.c_str());
	file << ligne << endl;

//data_links

	tmp = "";
	for(i=0; i<NB_DATA_LINK_IDS; i++)
		tmp += data_links[DATA_LINK_IDS[i]].associated_configuration_id + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P098=%s",tmp.c_str());
	file << ligne << endl;

//aux_interfaces_configurations

	tmp = "";
	for(i=0; i<NB_AUX_INTERFACES_CONFIGURATIONS; i++)
		tmp += aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].electrical_characteristics + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P099=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AUX_INTERFACES_CONFIGURATIONS; i++)
		tmp += IntToString(aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].baudrate,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P100=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AUX_INTERFACES_CONFIGURATIONS; i++)
		tmp += IntToString(aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].character_length,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P101=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AUX_INTERFACES_CONFIGURATIONS; i++)
		tmp += aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].character_parity + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P102=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AUX_INTERFACES_CONFIGURATIONS; i++)
		tmp += IntToString(aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].number_stop_bits,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P103=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AUX_INTERFACES_CONFIGURATIONS; i++)
		tmp += IntToString(aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].radio_address,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P104=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AUX_INTERFACES_CONFIGURATIONS; i++)
		tmp += aux_interfaces_configurations[AUX_INTERFACES_CONFIGURATIONS[i]].equipment_type + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P105=%s",tmp.c_str());
	file << ligne << endl;

//local_remote_interfaces_configurations

	tmp = "";
	for(i=0; i<NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS; i++)
		tmp += local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].electrical_characteristics + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P106=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS; i++)
		tmp += IntToString(local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].baudrate,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P107=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS; i++)
		tmp += IntToString(local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].characters_length,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P108=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS; i++)
		tmp += local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].characters_parity + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P109=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS; i++)
		tmp += IntToString(local_remote_interfaces_configurations[LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[i]].number_stop_bits,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P110=%s",tmp.c_str());
	file << ligne << endl;

//af_channels_configurations

	tmp = "";
	for(i=0; i<NB_AF_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].input_level,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P111=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AF_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].output_level,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P112=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AF_CHANNELS_CONFIGURATIONS; i++)
		tmp += af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].interface_type + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P113=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AF_CHANNELS_CONFIGURATIONS; i++)
		tmp += af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].ptt_type + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P114=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AF_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].ptt_tempo,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P115=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AF_CHANNELS_CONFIGURATIONS; i++)
		tmp += af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].mute_characteristics + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P116=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AF_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].mute_delay,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P117=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_AF_CHANNELS_CONFIGURATIONS; i++)
		tmp += IntToString(af_channels_configurations[AF_CHANNELS_CONFIGURATIONS[i]].radio_delay,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P118=%s",tmp.c_str());
	file << ligne << endl;

//channels

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += channels[CHANNELS[i]].status_local_remote_control + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P119=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += channels[CHANNELS[i]].associated_af_configuration + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P120=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += channels[CHANNELS[i]].data_link_id + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P121=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += channels[CHANNELS[i]].type + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P122=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += IntToString(channels[CHANNELS[i]].index_scanset_channel,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P123=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += channels[CHANNELS[i]].link_management_type + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P124=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += IntToString(channels[CHANNELS[i]].quality_value,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P125=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += IntToString(channels[CHANNELS[i]].af_level_received,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P126=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += IntToString(channels[CHANNELS[i]].offset_af_output_level,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P127=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += IntToString(channels[CHANNELS[i]].af_level_received_slave,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P128=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += IntToString(channels[CHANNELS[i]].dopple_offset,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P129=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += IntToString(channels[CHANNELS[i]].signal_noise_ratio,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P130=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += channels[CHANNELS[i]].direction_transmission + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P131=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += IntToString(channels[CHANNELS[i]].offset_carrier_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P132=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += IntToString(channels[CHANNELS[i]].offset_mark_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P133=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += IntToString(channels[CHANNELS[i]].offset_space_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P134=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_CHANNELS; i++)
		tmp += IntToString(channels[CHANNELS[i]].master_diversity,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P135=%s",tmp.c_str());
	file << ligne << endl;

//ale_parameter

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].automatic_sounding + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P136=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].aging_percentage,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P137=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].aging_time + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P138=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].multiservice + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P139=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].automatic_reconfiguration + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P140=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].service_activation,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P141=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].allcall_message + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P142=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].wildcard_message + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P143=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].anycall_message + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P144=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].respond + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P145=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].scanrate,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P146=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].twa_automatic,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P147=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].twa_manual,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P148=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].twt,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P149=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].tunetime_local,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P150=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].tunetime_other,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P151=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].ptt_gestion + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P152=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].sound_length + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P153=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].retries_channel,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P154=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].retries_scanfield,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P155=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].long_sound_limit,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P156=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].cms_choice + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P157=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].ale_termination_frame + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P158=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].index_channel_table,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P159=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].lowest_usable_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P160=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].upper_usable_frequency,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P161=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].call_type + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P162=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].index_selfaddress,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P163=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].quick_identification + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P164=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].quality_analysis + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P165=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].station_network_group + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P166=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].called_address,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P167=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].called_address_string + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P168=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";


	sprintf(ligne,"P169=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].agc + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P170=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].call_length,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P171=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].amd_message + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P172=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].link_protection_level,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P173=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += ale_parameter[ALE_PARAMETERS[i]].key_management + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P174=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(ale_parameter[ALE_PARAMETERS[i]].key_position,0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P175=%s",tmp.c_str());
	file << ligne << endl;

//table_stored1

	// sad self_address
	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += table_stored1["A1"].sad[i].self_address + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P176=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += table_stored1["B1"].sad[i].self_address + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P177=%s",tmp.c_str());
	file << ligne << endl;

	// sad net_address
	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += IntToString(table_stored1["A1"].sad[i].net_address, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P178=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += IntToString(table_stored1["B1"].sad[i].net_address, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P179=%s",tmp.c_str());
	file << ligne << endl;

	// sad slot
	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += IntToString(table_stored1["A1"].sad[i].slot, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P180=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += IntToString(table_stored1["B1"].sad[i].slot, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P181=%s",tmp.c_str());
	file << ligne << endl;

	// sad valid_channels
	tmp = "";
	for(i=0; i<NB_SAD; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored1["A1"].sad[i].valid_channels[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P182=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_SAD; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored1["B1"].sad[i].valid_channels[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P183=%s",tmp.c_str());
	file << ligne << endl;

	// rch channel

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["A1"].rch[i].channel, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P184=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["B1"].rch[i].channel, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P185=%s",tmp.c_str());
	file << ligne << endl;

	// rch tx_freq

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["A1"].rch[i].tx_freq, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P186=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["B1"].rch[i].tx_freq, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P187=%s",tmp.c_str());
	file << ligne << endl;

	// rch rx_freq

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["A1"].rch[i].rx_freq, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P188=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["B1"].rch[i].rx_freq, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P189=%s",tmp.c_str());
	file << ligne << endl;

	// rch mode_tx

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored1["A1"].rch[i].mode_tx + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P190=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored1["B1"].rch[i].mode_tx + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P191=%s",tmp.c_str());
	file << ligne << endl;

	// rch mode_rx

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored1["A1"].rch[i].mode_rx + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P192=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored1["B1"].rch[i].mode_rx + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P193=%s",tmp.c_str());
	file << ligne << endl;

	// rch bfo

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["A1"].rch[i].bfo, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P194=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["B1"].rch[i].bfo, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P195=%s",tmp.c_str());
	file << ligne << endl;

	// rch filter

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["A1"].rch[i].filter, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P196=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["B1"].rch[i].filter, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P197=%s",tmp.c_str());
	file << ligne << endl;

	// rch agc

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["A1"].rch[i].agc, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P198=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["B1"].rch[i].agc, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P199=%s",tmp.c_str());
	file << ligne << endl;

	// rch squelch

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["A1"].rch[i].squelch, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P200=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["B1"].rch[i].squelch, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P201=%s",tmp.c_str());
	file << ligne << endl;

	// rch pwr

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["A1"].rch[i].pwr, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P202=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["B1"].rch[i].pwr, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P203=%s",tmp.c_str());
	file << ligne << endl;

	// rch ed

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored1["A1"].rch[i].ed + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P204=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored1["B1"].rch[i].ed + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P205=%s",tmp.c_str());
	file << ligne << endl;

	// rch sound_interv

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["A1"].rch[i].sound_interv, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P206=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["B1"].rch[i].sound_interv, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P207=%s",tmp.c_str());
	file << ligne << endl;

	// rch self_add

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["A1"].rch[i].self_add, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P208=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored1["B1"].rch[i].self_add, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P209=%s",tmp.c_str());
	file << ligne << endl;

	// net net_address

	tmp = "";
	for(i=0; i<NB_NET; i++)
		tmp += table_stored1["A1"].net[i].net_address + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P210=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_NET; i++)
		tmp += table_stored1["B1"].net[i].net_address + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P211=%s",tmp.c_str());
	file << ligne << endl;

	// net net_member

	tmp = "";
	for(i=0; i<NB_NET; i++)
	{
		for(j=0; j<NB_NET_ADDRESS; j++)
			tmp += IntToString(table_stored1["A1"].net[i].net_member[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P212=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_NET; i++)
	{
		for(j=0; j<NB_NET_ADDRESS; j++)
			tmp += IntToString(table_stored1["B1"].net[i].net_member[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P213=%s",tmp.c_str());
	file << ligne << endl;

	// sta address_ale

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += table_stored1["A1"].sta[i].address_ale + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P214=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += table_stored1["B1"].sta[i].address_ale + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P215=%s",tmp.c_str());
	file << ligne << endl;

	// sta address_arq

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += table_stored1["A1"].sta[i].address_arq + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P216=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += table_stored1["B1"].sta[i].address_arq + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P217=%s",tmp.c_str());
	file << ligne << endl;

	// sta twr

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += IntToString(table_stored1["A1"].sta[i].twr, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P218=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += IntToString(table_stored1["B1"].sta[i].twr, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P219=%s",tmp.c_str());
	file << ligne << endl;

	// sta valid_channels

	tmp = "";
	for(i=0; i<NB_STA; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored1["A1"].sta[i].valid_channels[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P220=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_STA; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored1["B1"].sta[i].valid_channels[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P221=%s",tmp.c_str());
	file << ligne << endl;

	// sst scan_set_channel

	tmp = "";
	for(i=0; i<NB_SST; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored1["A1"].sst[i].scan_set_channel[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P222=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_SST; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored1["B1"].sst[i].scan_set_channel[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P223=%s",tmp.c_str());
	file << ligne << endl;

	// lt0 name

	tmp = "";
	tmp += table_stored1["A1"].lt0.name ;

	sprintf(ligne,"P224=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	tmp += table_stored1["B1"].lt0.name ;

	sprintf(ligne,"P225=%s",tmp.c_str());
	file << ligne << endl;

	// lt0 key

	tmp = "";
	for(i=0; i<NB_LT_KEY; i++)
		tmp += IntToString(table_stored1["A1"].lt0.key[i], 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P226=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_LT_KEY; i++)
		tmp += IntToString(table_stored1["B1"].lt0.key[i], 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P227=%s",tmp.c_str());
	file << ligne << endl;

	// lt1 name

	tmp = "";
	tmp += table_stored1["A1"].lt1.name ;

	sprintf(ligne,"P228=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	tmp += table_stored1["B1"].lt1.name ;

	sprintf(ligne,"P229=%s",tmp.c_str());
	file << ligne << endl;

	// lt1 key

	tmp = "";
	for(i=0; i<NB_LT_KEY; i++)
		tmp += IntToString(table_stored1["A1"].lt1.key[i], 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P230=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_LT_KEY; i++)
		tmp += IntToString(table_stored1["B1"].lt1.key[i], 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P231=%s",tmp.c_str());
	file << ligne << endl;

	// ***_present

	tmp = "";
	tmp += IntToString(table_stored1["A1"].sad_present, 0) + ";"
		+ IntToString(table_stored1["A1"].rch_present, 0) + ";"
		+ IntToString(table_stored1["A1"].net_present, 0) + ";"
		+ IntToString(table_stored1["A1"].sta_present, 0) + ";"
		+ IntToString(table_stored1["A1"].sst_present, 0);

	sprintf(ligne,"P232=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	tmp += IntToString(table_stored1["B1"].sad_present, 0) + ";"
		+ IntToString(table_stored1["B1"].rch_present, 0) + ";"
		+ IntToString(table_stored1["B1"].net_present, 0) + ";"
		+ IntToString(table_stored1["B1"].sta_present, 0) + ";"
		+ IntToString(table_stored1["B1"].sst_present, 0);

	sprintf(ligne,"P233=%s",tmp.c_str());
	file << ligne << endl;

//table_stored2

	// sad self_address
	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += table_stored2["A1"].sad[i].self_address + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P234=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += table_stored2["B1"].sad[i].self_address + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P235=%s",tmp.c_str());
	file << ligne << endl;

	// sad net_address
	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += IntToString(table_stored2["A1"].sad[i].net_address, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P236=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += IntToString(table_stored2["B1"].sad[i].net_address, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P237=%s",tmp.c_str());
	file << ligne << endl;

	// sad slot
	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += IntToString(table_stored2["A1"].sad[i].slot, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P238=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_SAD; i++)
		tmp += IntToString(table_stored2["B1"].sad[i].slot, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P239=%s",tmp.c_str());
	file << ligne << endl;

	// sad valid_channels
	tmp = "";
	for(i=0; i<NB_SAD; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored2["A1"].sad[i].valid_channels[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P240=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_SAD; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored2["B1"].sad[i].valid_channels[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P241=%s",tmp.c_str());
	file << ligne << endl;

	// rch channel

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["A1"].rch[i].channel, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P242=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["B1"].rch[i].channel, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P243=%s",tmp.c_str());
	file << ligne << endl;

	// rch tx_freq

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["A1"].rch[i].tx_freq, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P244=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["B1"].rch[i].tx_freq, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P245=%s",tmp.c_str());
	file << ligne << endl;

	// rch rx_freq

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["A1"].rch[i].rx_freq, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P246=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["B1"].rch[i].rx_freq, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P247=%s",tmp.c_str());
	file << ligne << endl;

	// rch mode_tx

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored2["A1"].rch[i].mode_tx + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P248=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored2["B1"].rch[i].mode_tx + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P249=%s",tmp.c_str());
	file << ligne << endl;

	// rch mode_rx

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored2["A1"].rch[i].mode_rx + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P250=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored2["B1"].rch[i].mode_rx + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P251=%s",tmp.c_str());
	file << ligne << endl;

	// rch bfo

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["A1"].rch[i].bfo, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P252=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["B1"].rch[i].bfo, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P253=%s",tmp.c_str());
	file << ligne << endl;

	// rch filter

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["A1"].rch[i].filter, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P254=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["B1"].rch[i].filter, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P255=%s",tmp.c_str());
	file << ligne << endl;

	// rch agc

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["A1"].rch[i].agc, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P256=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["B1"].rch[i].agc, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P257=%s",tmp.c_str());
	file << ligne << endl;

	// rch squelch

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["A1"].rch[i].squelch, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P258=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["B1"].rch[i].squelch, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P259=%s",tmp.c_str());
	file << ligne << endl;

	// rch pwr

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["A1"].rch[i].pwr, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P260=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["B1"].rch[i].pwr, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P261=%s",tmp.c_str());
	file << ligne << endl;

	// rch ed

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored2["A1"].rch[i].ed + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P262=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += table_stored2["B1"].rch[i].ed + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P263=%s",tmp.c_str());
	file << ligne << endl;

	// rch sound_interv

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["A1"].rch[i].sound_interv, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P264=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["B1"].rch[i].sound_interv, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P265=%s",tmp.c_str());
	file << ligne << endl;

	// rch self_add

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["A1"].rch[i].self_add, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P266=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_RCH; i++)
		tmp += IntToString(table_stored2["B1"].rch[i].self_add, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P267=%s",tmp.c_str());
	file << ligne << endl;

	// net net_address

	tmp = "";
	for(i=0; i<NB_NET; i++)
		tmp += table_stored2["A1"].net[i].net_address + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P268=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_NET; i++)
		tmp += table_stored2["B1"].net[i].net_address + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P269=%s",tmp.c_str());
	file << ligne << endl;

	// net net_member

	tmp = "";
	for(i=0; i<NB_NET; i++)
	{
		for(j=0; j<NB_NET_ADDRESS; j++)
			tmp += IntToString(table_stored2["A1"].net[i].net_member[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P270=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_NET; i++)
	{
		for(j=0; j<NB_NET_ADDRESS; j++)
			tmp += IntToString(table_stored2["B1"].net[i].net_member[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P271=%s",tmp.c_str());
	file << ligne << endl;

	// sta address_ale

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += table_stored2["A1"].sta[i].address_ale + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P272=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += table_stored2["B1"].sta[i].address_ale + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P273=%s",tmp.c_str());
	file << ligne << endl;

	// sta address_arq

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += table_stored2["A1"].sta[i].address_arq + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P274=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += table_stored2["B1"].sta[i].address_arq + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P275=%s",tmp.c_str());
	file << ligne << endl;

	// sta twr

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += IntToString(table_stored2["A1"].sta[i].twr, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P276=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_STA; i++)
		tmp += IntToString(table_stored2["B1"].sta[i].twr, 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P277=%s",tmp.c_str());
	file << ligne << endl;

	// sta valid_channels

	tmp = "";
	for(i=0; i<NB_STA; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored2["A1"].sta[i].valid_channels[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P278=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_STA; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored2["B1"].sta[i].valid_channels[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P279=%s",tmp.c_str());
	file << ligne << endl;

	// sst scan_set_channel

	tmp = "";
	for(i=0; i<NB_SST; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored2["A1"].sst[i].scan_set_channel[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P280=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_SST; i++)
	{
		for(j=0; j<NB_LIST_CHANNEL; j++)
			tmp += IntToString(table_stored2["B1"].sst[i].scan_set_channel[j], 0,TRUE) + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P281=%s",tmp.c_str());
	file << ligne << endl;

	// lt0 name

	tmp = "";
	tmp += table_stored2["A1"].lt0.name ;

	sprintf(ligne,"P282=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	tmp += table_stored2["B1"].lt0.name ;

	sprintf(ligne,"P283=%s",tmp.c_str());
	file << ligne << endl;

	// lt0 key

	tmp = "";
	for(i=0; i<NB_LT_KEY; i++)
		tmp += IntToString(table_stored2["A1"].lt0.key[i], 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P284=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_LT_KEY; i++)
		tmp += IntToString(table_stored2["B1"].lt0.key[i], 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P285=%s",tmp.c_str());
	file << ligne << endl;

	// lt1 name

	tmp = "";
	tmp += table_stored2["A1"].lt1.name ;

	sprintf(ligne,"P286=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	tmp += table_stored2["B1"].lt1.name ;

	sprintf(ligne,"P287=%s",tmp.c_str());
	file << ligne << endl;

	// lt1 key

	tmp = "";
	for(i=0; i<NB_LT_KEY; i++)
		tmp += IntToString(table_stored2["A1"].lt1.key[i], 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P288=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_LT_KEY; i++)
		tmp += IntToString(table_stored2["B1"].lt1.key[i], 0,TRUE) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P289=%s",tmp.c_str());
	file << ligne << endl;

	// ***_present

	tmp = "";
	tmp += IntToString(table_stored2["A1"].sad_present, 0) + ";"
		+ IntToString(table_stored2["A1"].rch_present, 0) + ";"
		+ IntToString(table_stored2["A1"].net_present, 0) + ";"
		+ IntToString(table_stored2["A1"].sta_present, 0) + ";"
		+ IntToString(table_stored2["A1"].sst_present, 0);

	sprintf(ligne,"P290=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	tmp += IntToString(table_stored2["B1"].sad_present, 0) + ";"
		+ IntToString(table_stored2["B1"].rch_present, 0) + ";"
		+ IntToString(table_stored2["B1"].net_present, 0) + ";"
		+ IntToString(table_stored2["B1"].sta_present, 0) + ";"
		+ IntToString(table_stored2["B1"].sst_present, 0);

	sprintf(ligne,"P291=%s",tmp.c_str());
	file << ligne << endl;

//pc_arq

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += pc_arq[ALE_PARAMETERS[i]].fonction + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P292=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += pc_arq[ALE_PARAMETERS[i]].etat + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P293=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += pc_arq[ALE_PARAMETERS[i]].modulation + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P294=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += pc_arq[ALE_PARAMETERS[i]].adaptabilite + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P295=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += pc_arq[ALE_PARAMETERS[i]].debit + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P296=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += pc_arq[ALE_PARAMETERS[i]].codage + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P297=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
	{
		for(j=0; j<pc_arq[ALE_PARAMETERS[i]].adresses_locales.size(); j++)
			tmp += pc_arq[ALE_PARAMETERS[i]].adresses_locales[j] + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P298=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
	{
		for(j=0; j<pc_arq[ALE_PARAMETERS[i]].adresses_destinataires.size(); j++)
			tmp += pc_arq[ALE_PARAMETERS[i]].adresses_destinataires[j] + "/";

		tmp.erase(tmp.length()-1, 1);
		tmp += ";";
	}

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P299=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(pc_arq[ALE_PARAMETERS[i]].current_adresse_locale, 0) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P300=%s",tmp.c_str());
	file << ligne << endl;

	tmp = "";
	for(i=0; i<NB_ALE_PARAMETERS; i++)
		tmp += IntToString(pc_arq[ALE_PARAMETERS[i]].current_adresse_destinataire, 0) + ";";

	if(i>0)
		tmp.erase(tmp.length()-1, 1);

	sprintf(ligne,"P301=%s",tmp.c_str());
	file << ligne << endl;

	AfxGetApp()->DoWaitCursor(-1);

	file.close();

	return TRUE;
}


/* **************************************************************************
METHODE :		Panne()
TRAITEMENT:		Retourne le numéro de la panne complète du modem,
				DEFAULT_INT_VALUE si aucune panne
***************************************************************************	*/
int CEquipM1752::Panne()
{
	return panne;
}

/* **************************************************************************
METHODE :		SetPanne()
TRAITEMENT:		Change la valeur de la panne
***************************************************************************	*/
void CEquipM1752::SetPanne(const int val)
{
	panne = val;
}

/* **************************************************************************
METHODE :		DesactiveVoie()
TRAITEMENT:		Desactive la voie passée en paramètre et la voie associée si
				en ALE.
				Envoi un signal TDA
***************************************************************************	*/
void CEquipM1752::DesactiveVoie(string voie)
{
	// Si le channel était deja INACTIVE on envoi pas le signal
	if (GetChannelState(voie) != "INACTIVE" && GetChannelState(voie) != "HS")
	{
		//((CDlgTRC1752*)ihm)->AffichageAct(voie);		// V3.0.1

		SetChannelState(voie, "INACTIVE");

		// FDI
		SetChannelAfLevelReceived(voie, -30);
		SetChannelOffsetCarrierFrequency(voie, 0);
		SetChannelReceptionStatus(voie, "VEILLE");

		((CProtoTRC1752*)proto)->SendSignaling("TDA", &voie);

	}

	// En ale/diversité on desactive les deux voies
	if (GetChannelType(voie) != "-" || GetChannelConfiguration(GetChannelAssociatedAfConfiguration(voie)).diversity == "AVEC")
	{
		if (GetChannelState(voie) != "HS")
			SetChannelState(GetChannelAssociated(voie), "INACTIVE");

		SetChannelReserve(GetChannelAssociated(voie), FALSE);
	}

	// Si un thread d'appel existe on le detruit
	FinAppel(voie);
}


/* **************************************************************************
METHODE :		CreerAppel()
TRAITEMENT:		Cree l'appel ALE pour la voie passée en paramètre
***************************************************************************	*/
void CEquipM1752::CreerAppel(string voie)
{
	if (voie == "A1")
	{
		if (appel_A != NULL) FinAppel(voie);
		NextSound("A1");
		appel_A = new CAppelAle(this, "A1");
	}
	else
	{
		if (appel_B != NULL) FinAppel(voie);
		NextSound("B1");
		appel_B = new CAppelAle(this, "B1");
	}
}

/* **************************************************************************
METHODE :		LancerAppel()
TRAITEMENT:		Lance l'appel ALE pour la voie passée en paramètre
***************************************************************************	*/
void CEquipM1752::LancerAppel(string voie)
{
	if (voie == "A1" && appel_A != NULL)
	{
		appel_A->LancerAppel();
	}

	if (voie == "B1" && appel_B != NULL)
	{
		appel_B->LancerAppel();
	}
}

/* **************************************************************************
METHODE :		LancerReceptionAppel()
TRAITEMENT:		Lance la procedure de reception d'un appel ALE pour la voie passée en paramètre
***************************************************************************	*/
void CEquipM1752::LancerReceptionAppel(string voie)
{
	if (voie == "A1" && appel_A != NULL)
	{
		appel_A->RecevoirAppel();
	}

	if (voie == "B1" && appel_B != NULL)
	{
		appel_B->RecevoirAppel();
	}
}

/* **************************************************************************
METHODE :		CasserAppel()
TRAITEMENT:		Casse l'appel ALE pour la voie passée en paramètre
***************************************************************************	*/
void CEquipM1752::CasserAppel(string voie)
{
	if (voie == "A1" && appel_A != NULL)
	{
		appel_A->CasserAppel();
	}

	if (voie == "B1" && appel_B != NULL)
	{
		appel_B->CasserAppel();
	}
}

/* **************************************************************************
METHODE :		FinAppel()
TRAITEMENT:		Arrete l'appel ale
***************************************************************************	*/
void CEquipM1752::FinAppel(string voie)
{
	if (voie == "A1" && appel_A != NULL)
	{
		appel_A->~CAppelAle();
		appel_A = NULL;
	}
	else if(voie == "B1" && appel_B != NULL)
	{
		appel_B->~CAppelAle();
		appel_B = NULL;
	}
}

/* **************************************************************************
METHODE :		RecevoirAmd()
TRAITEMENT:		Recoit un amd
***************************************************************************	*/
void CEquipM1752::RecevoirAmd(string voie)
{
	if (voie == "A1" && appel_A != NULL)
	{
		appel_A->RecevoirAmd();
	}
	else if(voie == "B1" && appel_B != NULL)
	{
		appel_B->RecevoirAmd();
	}
}

/* **************************************************************************
METHODE :		EnvoyerAmd()
TRAITEMENT:		Envoi un amd
***************************************************************************	*/
void CEquipM1752::EnvoyerAmd(string voie)
{
	if (voie == "A1" && appel_A != NULL)
	{
		appel_A->EnvoyerAmd();
	}
	else if(voie == "B1" && appel_B != NULL)
	{
		appel_B->EnvoyerAmd();
	}
}

/* **************************************************************************
METHODE :		Sound()
TRAITEMENT:		Envoi un sounding
***************************************************************************	*/
void CEquipM1752::Sound(string voie)
{
	if (voie == "A1" && appel_A != NULL)
	{
		appel_A->Sounding();
	}
	else if(voie == "B1" && appel_B != NULL)
	{
		appel_B->Sounding();
	}
}

/* **************************************************************************
METHODE :		LancerTestVoie()
TRAITEMENT:		Lance un test sur la voie
***************************************************************************	*/
int CEquipM1752::LancerTestVoie(const string voie, const string test)
{
	string trame = voie + ";" + test;

	istringstream stream (trame);

	return ((CProtoTRC1752*)proto)->TES(stream, FALSE);
}

/* **************************************************************************
METHODE :		ArreterTestVoie()
TRAITEMENT:		Arrete un test sur la voie
***************************************************************************	*/
int CEquipM1752::ArreterTestVoie(const string voie)
{
	string trame = voie;

	istringstream stream (trame);

	return ((CProtoTRC1752*)proto)->STE(stream, FALSE);
}

/* **************************************************************************
METHODE :		Activer()
TRAITEMENT:		Active la voie
***************************************************************************	*/
int CEquipM1752::Activer(string voie)
{
	// Fabrication trame activation
	string trame = voie + ";" + GetChannelAssociatedAfConfigurationConverted(voie) + ";"
		+ GetChannelDataLinkId(voie) + ";" + GetChannelType(voie) + ";";

	if (GetChannelType(voie) != "-")
		trame += IntToString(GetChannelIndexScansetChannel(voie),2);

	trame += ";;;" + GetChannelLinkManagementType(voie);

	istringstream stream (trame);

	return ((CProtoTRC1752*)proto)->ACT(stream, FALSE);
}

/* **************************************************************************
METHODE :		Desactiver()
TRAITEMENT:		Desactive la voie
***************************************************************************	*/
int CEquipM1752::Desactiver(string voie)
{
	// Initialisation des Offset's
	SetChannelOffsetMarkFrequency(voie, 0);
	SetChannelOffsetSpaceFrequency(voie, 0);
	SetChannelOffsetCarrierFrequency(voie, 0);
	SetChannelAfLevelOutput(voie, 0);

	// Fabrication trame desactivation
	istringstream stream (voie);

	return ((CProtoTRC1752*)proto)->DAC(stream, FALSE);
}

/* **************************************************************************
METHODE :		DefinitionArq()
TRAITEMENT:		Compilation du DCP, ART, DVM du pc arq
***************************************************************************	*/
int CEquipM1752::DefinitionArq(const string voie, const string fct_arq,
							   const string modulation, const int adr_loc, const int adr_dist)
{
	if (fct_arq == "NO ALE" || fct_arq == "NO ARQ" || fct_arq == "ALE")
	{
		// DVM
		TChannelConfiguration conf = GetChannelConfiguration(GetChannelAssociatedAfConfiguration(voie));

		conf.waveform = modulation;
		conf.diversity = "SANS";
		conf.direction = "HD";

		conf.af_reception_baudrate  = 300;
		conf.af_reception_codingtype = "CODE";
		conf.af_reception_interleaving = "COURT";

		conf.af_transmission_baudrate  = 300;
		conf.af_transmission_codingtype = "CODE";
		conf.af_transmission_interleaving = "COURT";

		SetChannelConfiguration(voie, conf);
		SetChannelAssociatedAfConfiguration(voie, voie);

		if (fct_arq == "ALE")
		{
			// ART
			// Recherche sad
			int sad = GetSad(voie, GetPcArq(voie).adresses_locales[adr_loc]);
			if (DEFAULT_INT_VALUE == sad) return -1;

			// Recherche sta
			int sta = GetSta(voie, GetPcArq(voie).adresses_destinataires[adr_dist]);
			if (DEFAULT_INT_VALUE == sta) return -2;

			// DCP
			TAleParameter ale = GetAleParameter(voie);

			ale.index_selfaddress = sad;
			ale.called_address = sta;

			SetAleParameter(voie, ale);
		}

	}

	return 0;
}

/* **************************************************************************
METHODE :		ModificationArq()
TRAITEMENT:		MDV du pc arq
***************************************************************************	*/
int CEquipM1752::ModificationArq(const string voie, const string debit, const string entrelacement)
{
	// On fabrique la trame du MDV
	// Rq: Le PC ARQ fonctionne en HD et CODE dans notre cas

	string cmd = voie + ";EMISSION;" + debit + ";" + "CODE;" + entrelacement;
	istringstream trame (cmd.c_str());

	int result = ((CProtoTRC1752*)proto)->MDV(trame, FALSE);

	// Modification V3.0.1
	TChannelConfiguration conf_courante;
	conf_courante = GetChannelConfiguration(voie);

	if (conf_courante.waveform == "MIL110")
		return result;

	trame.clear();
	cmd = voie + ";RECEPTION;" + debit + ";" + "CODE;" + entrelacement;
	trame.str(cmd.c_str());

	result += ((CProtoTRC1752*)proto)->MDV(trame, FALSE);

	return result;
}

/* **************************************************************************
METHODE :		SetAppel()
TRAITEMENT:		Changer le statut de l'appel
***************************************************************************	*/
void CEquipM1752::SetAppel(const string voie, const bool val)
{
	ale_parameter[voie].appel_en_cours = val;
}

/* **************************************************************************
METHODE :		IsAppel()
TRAITEMENT:		Indique si un appel est en cours
***************************************************************************	*/
bool CEquipM1752::IsAppel(const string voie)
{
	return ale_parameter[voie].appel_en_cours;
}


/* **************************************************************************
METHODE :		EffacementUrgence()
TRAITEMENT:		Efface toutes les tables du modem
***************************************************************************	*/
int CEquipM1752::EffacementUrgence()
{
	return ((CProtoTRC1752*)proto)->EUA(FALSE);
}

/* **************************************************************************
METHODE :		SelectionMemoire()
TRAITEMENT:		Selectionne une memoire sur la voie, retourne 0 en cas de reussite
***************************************************************************	*/
int CEquipM1752::SelectionMemoire(const string channel, const string num)
{
	string cmd = channel + ";" + num;
	istringstream trame (cmd.c_str());

	return ((CProtoTRC1752*)proto)->SEL(trame, FALSE);
}

/* **************************************************************************
METHODE :		EffacementMemoire()
TRAITEMENT:		Efface les tables du channel sur l'indice choisi, retourne 0
				en cas de reussite
***************************************************************************	*/
int CEquipM1752::EffacementMemoire(const string channel, const string num)
{
	string cmd = channel + ";" + num;
	istringstream trame (cmd.c_str());

	return ((CProtoTRC1752*)proto)->CLS(trame, FALSE);
}

/* **************************************************************************
METHODE :		EcritureMemoire()
TRAITEMENT:		Ecrit les tables du channel dans l'emplacement memoire choisi,
				retourne 0 en cas de réussite
***************************************************************************	*/
int CEquipM1752::EcritureMemoire(const string channel, const string num)
{
	string cmd = channel + ";" + num;
	istringstream trame (cmd.c_str());

	return ((CProtoTRC1752*)proto)->WRT(trame, FALSE);
}

/* **************************************************************************
METHODE :		RazIntegrite()
TRAITEMENT:		Enleve les defauts d'integrités sur les voies
***************************************************************************	*/
void CEquipM1752::RazIntegrite()
{
	// Peu importe le nombre de carte presentes
	istringstream trame;

	for(int i=0; i<NB_CHANNELS; i++)
	{
		trame.str(CHANNELS[i].c_str());
		((CProtoTRC1752*)proto)->RES(trame, FALSE);
		trame.clear();
	}
}

/* **************************************************************************
METHODE :		SendINR()
TRAITEMENT:		Envoi un INR
***************************************************************************	*/
void CEquipM1752::SendINR()
{
	((CProtoTRC1752*)proto)->SignalINR();
}

/* **************************************************************************
METHODE :		SendINT()
TRAITEMENT:		Envoi un INT
***************************************************************************	*/
void CEquipM1752::SendINT(const string id)
{
	((CProtoTRC1752*)proto)->SignalINT(id);
}


/* **************************************************************************
METHODE :		SendTSP()
TRAITEMENT:		Envoi un TSP
***************************************************************************	*/
void CEquipM1752::SendTSP(const string id)
{
	((CProtoTRC1752*)proto)->SignalTSP(id);
}

/* **************************************************************************
METHODE :		SendPAO()
TRAITEMENT:		Envoi un PAO
***************************************************************************	*/
void CEquipM1752::SendPAO(const string channel, const string direction)
{
	((CProtoTRC1752*)proto)->SignalPAO(channel, direction);
}

/* **************************************************************************
METHODE :		SendLKL()
TRAITEMENT:		Envoi un LKL
***************************************************************************	*/
void CEquipM1752::SendLKL(const string channel, const string erreur)
{
	((CProtoTRC1752*)proto)->SignalLKL(channel, erreur);
}

/* **************************************************************************
				GETTERS / SETTERS
***************************************************************************	*/

/* **************************************************************************
METHODE :		ValidChannelId()
TRAITEMENT:		Indique si le channel passé en paramètre est valide
***************************************************************************	*/
bool CEquipM1752::ValidChannelId(const string id)
{
	if (channels.find(id) == channels.end()) return FALSE;

	return TRUE;
}

/* **************************************************************************
METHODE :		ValidChannelVersion()
TRAITEMENT:		Indique si le channel passé en paramètre existe dans la conf
				actuelle du modem
***************************************************************************	*/
bool CEquipM1752::ValidChannelVersion(const string id)
{
	if (id == "B1" || id == "B2")
		if (quadrivoie == false) return FALSE;

	return TRUE;
}

/* **************************************************************************
METHODE :		GetAfChannelFromModemChannel()
TRAITEMENT:		Retourne la voie BF associé au channel passé en paramètre
***************************************************************************	*/
string CEquipM1752::GetAfChannelFromModemChannel(const string channel)
{
	if (channel == "A1") return "BF1";
	if (channel == "A2") return "BF2";
	if (channel == "B1") return "BF3";

	return "BF4";
}

/* **************************************************************************
METHODE :		GetModemChannelFromAfChannel()
TRAITEMENT:		Retourne la voie modem associé à la voie BF passée en param
***************************************************************************	*/
string CEquipM1752::GetModemChannelFromAfChannel(const string af_channel)
{
	if (af_channel == "BF1") return "A1";
	if (af_channel == "BF2") return "A2";
	if (af_channel == "BF3") return "B1";

	return "B2";
}

/* **************************************************************************
METHODE :		ValidDataLinkId()
TRAITEMENT:		Indique si le data link passé en paramètre est valide
***************************************************************************	*/
bool CEquipM1752::ValidDataLinkId(const string id)
{
	if (data_links.find(id) == data_links.end()) return FALSE;

	return TRUE;
}

/* **************************************************************************
METHODE :		ValidDataLinkVersion()
TRAITEMENT:		Indique si le data link passé en param existe dans la conf
				actuelle du modem
***************************************************************************	*/
bool CEquipM1752::ValidDataLinkVersion(const string id)
{
	if (id == "D5" || id == "D6" || id == "D7" || id == "D8")
		if (quadrivoie == false) return FALSE;

	return TRUE;
}

/* **************************************************************************
METHODE :		IsDataLinkUsed()
TRAITEMENT:		Indique si le data link passé en param est associé à une voie
				modem active
***************************************************************************	*/
bool CEquipM1752::IsDataLinkUsed(const string id)
{
	bool res = FALSE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	for(int i = 0; i<NB_CHANNELS; i++)
	{
		if((channels[CHANNELS[i]].data_link_id == id)
			&& ((channels[CHANNELS[i]].state == "ACTIVE") || (channels[CHANNELS[i]].test_progress != DEFAULT_STRING_VALUE)))
				res = TRUE;
	}
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return res;
}

/* **************************************************************************
METHODE :		GetChannelFromDataLink()
TRAITEMENT:		Retourne le channel associé au data link passé en param
***************************************************************************	*/
string CEquipM1752::GetChannelFromDataLink(const string data)
{
	if (data == "D1") return "A1";
	if (data == "D2") return "A2";
	if (data == "D5") return "B1";
	if (data == "D6") return "B2";

	return DEFAULT_STRING_VALUE;
}

/* **************************************************************************
METHODE :		GetChannelAssociated()
TRAITEMENT:		Retourne la voie modem associé à la voie passé en paramètre
				(Utile dans le cas ALE)
***************************************************************************	*/
string CEquipM1752::GetChannelAssociated(const string id)
{
	if (id == "A1") return "A2";
	if (id == "A2") return "A1";
	if (id == "B1") return "B2";
	return "B1";
}

/************* Data link structure ************************/

/* **************************************************************************
METHODE :		GetDataLinkAssociatedConfiguration()
TRAITEMENT:		Retourne le nom de la configuration de l'interface associée
				au data link passé en paramètre
***************************************************************************	*/
string CEquipM1752::GetDataLinkAssociatedConfiguration(const string id)
{
	return data_links[id].associated_configuration_id;
}

/* **************************************************************************
METHODE :		SetDataLinkAssociatedConfiguration()
TRAITEMENT:		Change le nom de la configuraiton interface associée au
				data link indiqué
***************************************************************************	*/
void CEquipM1752::SetDataLinkAssociatedConfiguration(const string id, const string value)
{
	data_links[id].associated_configuration_id = value;
}

/* **************************************************************************
METHODE :		ValidDataLinkAssociatedConfiguration()
TRAITEMENT:		Retourne TRUE si le data link passé en paramètre est valide
***************************************************************************	*/
bool CEquipM1752::ValidDataLinkAssociatedConfiguration(const string value)
{
	if (interfaces_configurations.find(value) == interfaces_configurations.end()) return FALSE;

	return TRUE;
}

string CEquipM1752::GetDataLinkTest(const string id)
{
	return data_links[id].test_progress;
}

/* **************************************************************************
METHODE :		GetDataLinkFromChannel()
TRAITEMENT:		Retourne le Data Link correspondant au channel
***************************************************************************	*/
string CEquipM1752::GetDataLinkFromChannel(const string data)
{
	if (data == "A1") return "D1";
	if (data == "A2") return "D2";
	if (data == "B1") return "D5";
	if (data == "B2") return "D6";

	return DEFAULT_STRING_VALUE;
}

/************* Channel structure **************************/

bool CEquipM1752::IsChannelFree(const string id)
{
	if (channels[id].state == "ACTIVE") return FALSE;
	if (channels[id].test_progress != DEFAULT_STRING_VALUE) return FALSE;

	return TRUE;
}

bool CEquipM1752::IsChannelAleReserved(const string id)
{
	if (id != "A2" && id != "B2") return FALSE;

	if (id == "A2" && channels["A1"].state == "ACTIVE" && channels["A1"].type != "-") return TRUE;
	if (id == "B2" && channels["B1"].state == "ACTIVE" && channels["B1"].type != "-") return TRUE;

	return FALSE;
}

// ChannelState

string CEquipM1752::GetChannelState(const string id)
{
	return channels[id].state;
}

string CEquipM1752::GetChannelStateIhm(const string id)
{
	string value;

	if (channels[id].state == "ACTIVE") value = "A";
	else value = "I";

	return value;
}

void CEquipM1752::SetChannelState(const string id, const string state)
{
	channels[id].state = state;
}

bool CEquipM1752::ValidChannelState(const string state)
{
	if (state != "ACTIVE" && state != "INACTIVE" && state != "HS") return FALSE;

	return TRUE;
}

// ChannelLocalRemoteControl

string CEquipM1752::GetChannelLocalRemoteControl(const string id)
{
	return channels[id].status_local_remote_control;
}

void CEquipM1752::SetChannelLocalRemoteControl(const string id, const string value)
{
	channels[id].status_local_remote_control = value;
}

bool CEquipM1752::ValidChannelLocalRemoteControl(const string value)
{
	if (value != "LOCAL" && value != "MAIN") return FALSE;

	return TRUE;
}

/* **************************************************************************
METHODE :		GetChannelAssociatedAfConfiguration()
TRAITEMENT:		Retourne le nom de la conf af associé
***************************************************************************	*/
string CEquipM1752::GetChannelAssociatedAfConfiguration(const string id)
{
	return channels[id].associated_af_configuration;
}

/* **************************************************************************
METHODE :		GetChannelAssociatedAfConfigurationConverted()
TRAITEMENT:		Retourne le nom de la conf af associé et MC si manual
***************************************************************************	*/
string CEquipM1752::GetChannelAssociatedAfConfigurationConverted(const string id)
{
	string value = GetChannelAssociatedAfConfiguration(id);

	// Cas de la valeur MC
	if (value == "A1" || value == "A2" || value == "B1" || value == "B2")
		value = "MC";

	return value;
}

void CEquipM1752::SetChannelAssociatedAfConfiguration(const string id, const string value)
{
	string convert_value = value;

	// Cas de la valeur MC
	if (value == "MC")
	{
		convert_value = id;
	}

	channels[id].associated_af_configuration = convert_value;
}

/* **************************************************************************
METHODE :		SetChannelAssociatedAfConfigurationModified()
TRAITEMENT:		Recopie la conf en cours du channel dans le manual de la voie
***************************************************************************	*/
void CEquipM1752::SetChannelAssociatedAfConfigurationModified(const string id)
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);

	if (channels[id].associated_af_configuration == "MC")
		channels_configurations[id] = channels_configurations[id];
	else
		channels_configurations[id] = channels_configurations[channels[id].associated_af_configuration];

		channels[id].associated_af_configuration = id;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

bool CEquipM1752::ValidChannelAssociatedAfConfiguration(const string value)
{
	if ((channels_configurations.find(value) == channels_configurations.end())
		&& value != "MC") return FALSE;

	return TRUE;
}

// ChannelDataLinkId

string CEquipM1752::GetChannelDataLinkId(const string id)
{
	return channels[id].data_link_id;
}

void CEquipM1752::SetChannelDataLinkId(const string id, const string value)
{
	channels[id].data_link_id = value;
}

bool CEquipM1752::ValidChannelDataLinkId(const string value)
{
	if (value != "D1" && value != "D2" && value != "D5" && value != "D6" && value != "INT") return FALSE;

	return TRUE;
}

// ChannelType

string CEquipM1752::GetChannelType(const string id)
{
	return channels[id].type;
}

void CEquipM1752::SetChannelType(const string id, const string value)
{
	channels[id].type = value;
}

bool CEquipM1752::ValidChannelType(const string value)
{
	if (value != "-" && value != "S" && value != "C") return FALSE;

	return TRUE;
}

// ChannelIndexScansetChannel

int CEquipM1752::GetChannelIndexScansetChannel(const string id)
{
	return channels[id].index_scanset_channel;
}

void CEquipM1752::SetChannelIndexScansetChannel(const string id, const int value)
{
	channels[id].index_scanset_channel = value;
}

bool CEquipM1752::ValidChannelIndexScansetChannel(const int value)
{
	if (value >= 0 && value <= 99) return TRUE;

	return FALSE;
}

// ChannelLinkManagementType

string CEquipM1752::GetChannelLinkManagementType(const string id)
{
	return channels[id].link_management_type;
}

void CEquipM1752::SetChannelLinkManagementType(const string id, const string value)
{
	channels[id].link_management_type = value;
}

bool CEquipM1752::ValidChannelLinkManagementType(const string value)
{
	if (value != "-" && value != "LMANU" && value != "LAUTO") return FALSE;

	return TRUE;
}

string CEquipM1752::GetChannelLinkManagementTypeIhm(const string id)
{
	string value;

	// Conversion vers le format ihm
	if (channels[id].link_management_type == "LMANU") value = "M";
	else value = "A";

	return value;
}

void CEquipM1752::SetChannelLinkManagementTypeIhm(const string id, const string value)
{
	// Conversion vers le format ihm
	string convert = "LAUTO";
	if (value == "M") convert = "LMANU";

	channels[id].link_management_type = convert;
}

bool CEquipM1752::GetChannelMasterDiversity(const string id)
{
	return channels[id].master_diversity;
}

void CEquipM1752::SetChannelMasterDiversity(const string id, const bool value)
{
	channels[id].master_diversity = value;
}

string CEquipM1752::GetChannelTest(const string id)
{
	return channels[id].test_progress;
}

void CEquipM1752::SetChannelTest(const string id, const string test)
{
	channels[id].test_progress = test;
}

bool CEquipM1752::ValidChannelTest(const string test)
{
	if (test == "1800HZ" || test == "BOUCLE_BF") return TRUE;

	return FALSE;
}

/* **************************************************************************
METHODE :		IsChannelReserve()
TRAITEMENT:		Indique si le channel est reservé en ale
***************************************************************************	*/
bool CEquipM1752::IsChannelReserve(const string id)
{
	return channels[id].reserve;
}

/* **************************************************************************
METHODE :		SetChannelReserve()
TRAITEMENT:		Change la valeur de reservation du channel
***************************************************************************	*/
void CEquipM1752::SetChannelReserve(const string id, bool val)
{
	channels[id].reserve = val;
}

/******************** Channel configuration ********************/

TChannelConfiguration CEquipM1752::GetChannelConfiguration(const string id)
{
	return channels_configurations[id];
}

void CEquipM1752::SetChannelConfiguration(const string id, const TChannelConfiguration conf)
{
	channels_configurations[id] = conf;
}

bool CEquipM1752::ValidChannelConfiguration(const string id)
{
	if (channels_configurations.find(id) == channels_configurations.end()) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidChannelConfigurationVersion(const string id)
{
	if (id == "B1" || id == "B2") return FALSE;

	return TRUE;
}

// Vérification des waveform autorisée
bool CEquipM1752::ValidChannelConfigurationWaveform(const string waveform)
{
	if (waveform == "4285" || waveform == "4529" || waveform == "BFSK"
		|| waveform == "MIL110" || waveform == "TRANSP" || waveform == "REPOS")
		return TRUE;

	return FALSE;
}

// Vérification de la diversity autorisée en fonction de la waveform
bool CEquipM1752::ValidChannelConfigurationDiversity(const string &waveform, string &value)
{
	if (waveform == "4285" || waveform == "4529")
	{
		if (value != "AVEC" && value != "SANS") return FALSE;
	}
	else value = "";

	return TRUE;
}

// Vérification de la direction en fonction de la waveform
bool CEquipM1752::ValidChannelConfigurationDirection(const string &waveform, const string &diversity, string &direction)
{
	if (waveform == "4285" || waveform == "4529")
	{
		if (diversity == "SANS")
		{
			if (direction != "TX" && direction != "RX" && direction != "HD" && direction != "FD") return FALSE;
		}
		else
		{
			if (direction != "RX" && direction != "HD" && direction != "FD") return FALSE;
		}
	}
	else if (waveform == "BFSK" || waveform == "MIL110")
	{
		if (direction != "TX" && direction != "RX" && direction != "HD" && direction != "FD") return FALSE;
	}
	else direction = "";

	return TRUE;
}

// Vérification af parameters en fonction de la waveform
int CEquipM1752::ValidChannelConfigurationAfParameters(const string &waveform, string &baudrate, string &coding,
								 string &interleaving, const bool reception)
{
	int error_baudrate = 1;
	int error_coding = 2;
	int error_interleaving = 3;
	int no_error = 0;

	if (waveform == "4285")
	{
		if (baudrate == "0075" || baudrate == "0150" || baudrate == "0300" || baudrate == "0600")
		{
			if (coding != "CODE") return error_coding;
			if (interleaving != "SANS" && interleaving != "COURT" && interleaving != "LONG") return error_interleaving;
		}
		else if (baudrate == "1200")
		{
			if (coding != "CODE" && coding != "SANS") return error_coding;
			if (interleaving != "SANS" && interleaving != "COURT" && interleaving != "LONG") return error_interleaving;
		}
		else if (baudrate == "2400")
		{
			if (coding == "CODE")
			{
				if (interleaving != "COURT" && interleaving != "LONG") return error_interleaving;
			}
			else if (coding == "SANS")
			{
				if (interleaving != "SANS" && interleaving != "COURT" && interleaving != "LONG") return error_interleaving;
			}
			else return error_coding;
		}
		else if (baudrate == "3600")
		{
			if (coding != "SANS") return error_coding;
			if (interleaving != "SANS") return error_interleaving;
		}
		else return error_baudrate;

		return no_error;
	}
	else if (waveform == "4529")
	{
		if (baudrate == "0075" || baudrate == "0150" || baudrate == "0300")
		{
			if (coding != "CODE") return error_coding;
			if (interleaving != "SANS" && interleaving != "COURT" && interleaving != "LONG") return error_interleaving;
		}
		else if (baudrate == "0600")
		{
			if (coding != "CODE" && coding != "SANS") return error_coding;
			if (interleaving != "SANS" && interleaving != "COURT" && interleaving != "LONG") return error_interleaving;
		}
		else if (baudrate == "1200")
		{
			if (coding == "SANS")
			{
				if (interleaving != "COURT" && interleaving != "LONG") return error_interleaving;
			}
			else if (coding == "CODE")
			{
				if (interleaving != "SANS" && interleaving != "COURT" && interleaving != "LONG") return error_interleaving;
			}
			else return error_coding;
		}
		else if (baudrate == "1800")
		{
			if (coding != "SANS") return error_coding;
			if (interleaving != "SANS") return error_interleaving;
		}
		else return error_baudrate;

		return no_error;
	}
	else if (waveform == "BFSK")
	{
		if (baudrate != "0050" && baudrate != "0075" && baudrate != "0100" && baudrate != "0150" && baudrate != "0200"
			&& baudrate != "0300" && baudrate != "0600" && baudrate != "1200") return error_baudrate;

		// On vide les parametres non utilisés
		coding = "";
		interleaving = "";

		return no_error;
	}
	else if (waveform == "MIL110")
	{
		if (reception == FALSE)
		{
			if (baudrate == "0075" || baudrate == "0150" || baudrate == "0300" || baudrate == "0600" || baudrate == "1200")
			{
				if (coding != "CODE") return error_coding;
				if (interleaving != "SANS" && interleaving != "COURT" && interleaving != "LONG") return error_interleaving;
			}
			else if (baudrate == "2400")
			{
				if (coding == "CODE")
				{
					if (interleaving != "SANS" && interleaving != "COURT" && interleaving != "LONG") return error_interleaving;
				}
				else if (coding == "PHONIE")
				{
					if (interleaving != "SANS" && interleaving != "COURT") return error_interleaving;
				}
				else return error_coding;
			}
			else if (baudrate == "4800")
			{
				if (coding != "SANS") return error_coding;
				if (interleaving != "SANS") return error_interleaving;
			}
			else return error_baudrate;

			return no_error;
		}
		else
		{
			if (baudrate != "AUTO") return error_baudrate;
			if (interleaving != "SANS" && interleaving != "COURT") return error_interleaving;

			// On vide le parametre coding non utilisé
			coding = "";

			return no_error;
		}
	}
	else // On vide tout, ça sert à rien
	{
		baudrate = "";
		coding = "";
		interleaving = "";
	}

	return no_error;
}

bool CEquipM1752::ValidChannelConfigurationCarrierFrequency(const string &waveform, string &value)
{
	if (waveform == "4529")
	{
		// La frequence doit faire 4 caractères
		if(value.length() != 4) return FALSE;

		// Elle doit se finir par 00
		if(value.substr(2,2) != "00") return FALSE;

		int convert = atoi(value.c_str());

		// Elle doit etre comprise en 900 et 2400
		if(convert<900 || convert>2400) return FALSE;
	}
	else // On vide ce champs dénué d'interet
		value = "";

	return TRUE;
}

int CEquipM1752::ValidChannelConfigurationFrequency(const string &waveform, string &space, string &mark)
{
	int error_space = 1;
	int error_mark = 2;
	int no_error = 0;

	if (waveform == "BFSK")
	{
		// Les frequences doivent faire 4 caractères
		if(space.length() != 4) return error_space;
		if(mark.length() != 4) return error_mark;

		// Elles doivent être comprises entre 300 et 3300
		int convert_haute = atoi(space.c_str());
		if(convert_haute<300 || convert_haute>3300) return error_space;

		int convert_basse = atoi(mark.c_str());
		if(convert_basse<300 || convert_basse>3300) return error_mark;

		// La frequence haute doit etre superieur a la basse
		if (convert_haute <= convert_basse) return error_space;
	}
	else // On vide ces champs
	{
		space = "";
		mark = "";
	}

	return no_error;
}

bool CEquipM1752::ValidChannelConfigurationSlaveDirection(const string &waveform, string &direction)
{
	if (waveform == "4285" || waveform == "4529")
	{
		if (direction != "RX" && direction != "FD") return FALSE;
	}
	else
		direction = "";

	return TRUE;
}

bool CEquipM1752::ValidChannelConfigurationUseData(const string &waveform, string &use)
{
	if (waveform == "4285" || waveform == "4529")
	{
		if (use != "AVEC" && use != "SANS") return FALSE;
	}
	else
		use = "";

	return TRUE;
}

int CEquipM1752::GetChannelQualityValue(const string id)
{
	return channels[id].quality_value;
}

void CEquipM1752::SetChannelQualityValue(const string id, const int value)
{
	channels[id].quality_value = value;
}

int CEquipM1752::GetChannelAfLevelReceived(const string id)
{
	return channels[id].af_level_received;
}

void CEquipM1752::SetChannelAfLevelReceived(const string id, const int value)
{
	channels[id].af_level_received = value;
}

int CEquipM1752::GetChannelAfLevelReceivedSlave(const string id)
{
	return channels[id].af_level_received_slave;
}

void CEquipM1752::SetChannelAfLevelReceivedSlave(const string id, const int value)
{
	channels[id].af_level_received_slave = value;
}

int CEquipM1752::GetChannelAfLevelOutput(const string id)
{
	return channels[id].offset_af_output_level;
}

void CEquipM1752::SetChannelAfLevelOutput(const string id, const int value)
{
	channels[id].offset_af_output_level = value;

	// Signal TBF
	((CProtoTRC1752*)proto)->SignalTBF(id);
}

int CEquipM1752::GetChannelDopplerOffset(const string id)
{
	return channels[id].dopple_offset;
}

void CEquipM1752::SetChannelDopplerOffset(const string id, const int value)
{
	channels[id].dopple_offset = value;
}

int CEquipM1752::GetChannelSignalNoiseRation(const string id)
{
	return channels[id].signal_noise_ratio;
}

void CEquipM1752::SetChannelDirectionTransmission(const string id, const string value)
{
	channels[id].direction_transmission = value;
}

string CEquipM1752::GetChannelDirectionTransmission(const string id)
{
	return channels[id].direction_transmission;
}

bool CEquipM1752::ValidChannelDirectionTransmission(const string value)
{
	if (value == "EMISSION" || value == "RECEPTION") return TRUE;

	return FALSE;
}

void CEquipM1752::SetChannelOffsetCarrierFrequency(const string id, const int value)
{
	channels[id].offset_carrier_frequency = value;
}

int CEquipM1752::GetChannelOffsetCarrierFrequency(const string id)
{
	return channels[id].offset_carrier_frequency;
}

bool CEquipM1752::ValidChannelOffsetCarrierFrequency(const string value)
{
	int convert = atoi(value.c_str());

	if (value.length() != 4 || convert < -200 || convert > 200) return FALSE;

	return TRUE;
}

void CEquipM1752::SetChannelOffsetMarkFrequency(const string id, const int value)
{
	channels[id].offset_mark_frequency = value;
}

int CEquipM1752::GetChannelOffsetMarkFrequency(const string id)
{
	return channels[id].offset_mark_frequency;
}

void CEquipM1752::SetChannelOffsetSpaceFrequency(const string id, const int value)
{
	channels[id].offset_space_frequency = value;
}

int CEquipM1752::GetChannelOffsetSpaceFrequency(const string id)
{
	return channels[id].offset_space_frequency;
}

void CEquipM1752::SetChannelSignalNoiseRation(const string id, const int value)
{
	channels[id].signal_noise_ratio = value;
}

/* **************************************************************************
METHODE :		GetChannelReceptionStatus()
TRAITEMENT:		Retourne le status de reception
***************************************************************************	*/
string CEquipM1752::GetChannelReceptionStatus(const string id)
{
	return channels[id].reception_status;
}

/* **************************************************************************
METHODE :		SetChannelReceptionStatus()
TRAITEMENT:		Change le status de reception en fct de la puissance en entrée
***************************************************************************	*/
void CEquipM1752::SetChannelReceptionStatus(const string id, const int val, int dir)
{
	bool change = false;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	string etat = channels[id].reception_status;

	//*****************************************************
	// Pas de réception : m_EtatReception = _T("VEILLE");
	if ( val >= -30 &&  val < -20 ) etat = "INACTIF";

	// Début de la réception : m_EtatReception = _T("DEBUT");
	if ( val >= -20 &&  val < -10) etat = "DEBUT";

	// Réception en cours : m_EtatReception = _T("EN_COURS");
	if ( val >= -10 &&  val <= 10) etat = "EN_COURS";

	// Fin de la réception : m_EtatReception = _T("FIN");
	if ( val < -10 && val >= -20 &&  dir < 0) etat = "FIN";
	//******************************************************

	if (etat != channels[id].reception_status) change = true;

	channels[id].reception_status = etat;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	if (change)
	{
		// Signal ETA
		((CProtoTRC1752*)proto)->SignalETA("RECEPTION", id);
	}
}

/* **************************************************************************
METHODE :		SetChannelReceptionStatus()
TRAITEMENT:		Change le status de reception
***************************************************************************	*/
void CEquipM1752::SetChannelReceptionStatus(const string id, const string status)
{
	channels[id].reception_status = status;
}

/* **************************************************************************
METHODE :		GetChannelEmissionStatus()
TRAITEMENT:		Retourne le status d'emission
***************************************************************************	*/
string CEquipM1752::GetChannelEmissionStatus(const string id)
{
	return channels[id].emission_status;
}

/* **************************************************************************
METHODE :		SetChannelEmissionStatus()
TRAITEMENT:		Change le status d'emission
***************************************************************************	*/
void CEquipM1752::SetChannelEmissionStatus(const string id, const string status)
{
	bool change = false;

	if (channels[id].emission_status != status) change = true;

	channels[id].emission_status = status;

	// Signal TBF
	if (change)
		((CProtoTRC1752*)proto)->SignalTBF(id);

}

/* **************************************************************************
METHODE :		GetChannelEmissionEncours()
TRAITEMENT:		Emission encours ?
***************************************************************************	*/
bool CEquipM1752::GetChannelEmissionEncours(const string id)
{
	return channels[id].emission_encours;
}

/* **************************************************************************
METHODE :		SetChannelEmissionEncours()
TRAITEMENT:		Mise en/hors emission
***************************************************************************	*/
void CEquipM1752::SetChannelEmissionEncours(const string id, bool status)
{
	bool change = false;

	if (channels[id].emission_encours != status) change = true;

	channels[id].emission_encours = status;

	// Signal ETA
	if (change)
	{
		if (status == FALSE)
			SetChannelEmissionStatus(id,"INACTIF");
		else
			SetChannelEmissionStatus(id,"EN_COURS");

		((CProtoTRC1752*)proto)->SignalETA("EMISSION", id);
	}
}

/******************** Aux Interface configuration ********************/

TInterfaceConfiguration CEquipM1752::GetInterfaceConfiguration(const string id)
{
	return interfaces_configurations[id];
}

void CEquipM1752::SetInterfaceConfiguration(const string id, const TInterfaceConfiguration conf)
{
	interfaces_configurations[id] = conf;
}

bool CEquipM1752::ValidInterfaceConfiguration(const string id)
{
	if (interfaces_configurations.find(id) == interfaces_configurations.end()) return FALSE;

	return TRUE;
}

bool CEquipM1752::IsInterfaceConfigurationUsed(const string value)
{
	for (int i = 0; i<NB_DATA_LINK_IDS-1; i++)
	{
		if (GetDataLinkAssociatedConfiguration(DATA_LINK_IDS[i]) == value)
			if (IsDataLinkUsed(DATA_LINK_IDS[i]) == TRUE) return TRUE;
	}

	return FALSE;
}


bool CEquipM1752::ValidInterfaceConfigurationType(const string type)
{
	if (type != "SYNCHRONE" && type != "ASYNCHRONE") return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidInterfaceConfigurationElectricalCharacteristic(const string type, const string carac)
{
	if (carac == "V10" || carac == "V11" || carac == "V11_DA" || carac == "V28" || carac == "EIA530"
		|| carac == "EIA530_DA")
		return TRUE;

	if (type == "SYNCHRONE")
	{
		if (carac == "V11_HA" || carac == "EIA530_HA" ) return TRUE;
	}

	return FALSE;
}

bool CEquipM1752::ValidInterfaceConfigurationBaudrate(const string type, const string direction, const string baudrate)
{
	if (baudrate == "00050" || baudrate == "00075" || baudrate == "00100" || baudrate == "00150"
		|| baudrate == "00200" || baudrate == "00300" || baudrate == "00600" || baudrate == "00800"
		|| baudrate == "01200" || baudrate == "01800" || baudrate == "02400" || baudrate == "AUTO")
		return TRUE;

	if (type == "SYNCHRONE" && direction == "SANS") return FALSE;

	if (baudrate != "03600" && baudrate != "04800" && baudrate != "07200" && baudrate != "09600"
		&& baudrate != "19200")
		return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidInterfaceConfigurationClockDirection(const string type, const string direction)
{
	if (type == "ASYNCHRONE" && direction != "") return FALSE;

	if (type == "SYNCHRONE")
	{
		if (direction != "ENTRANTE" && direction != "SORTANTE" && direction != "SANS")
			return FALSE;
	}

	return TRUE;
}

bool CEquipM1752::ValidInterfaceConfigurationValidityTime(const string time)
{
	if (time != "01H" && time != "24H") return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidInterfaceConfigurationBinaryIntegrity(const string integrity)
{
	if (integrity != "PETITE" && integrity != "GRANDE") return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidInterfaceConfigurationPolarity(const string polarity)
{
	if (polarity != "NORMALE" && polarity != "INVERSEE") return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidInterfaceConfigurationHandShake(const string handshake)
{
	if (handshake != "DPE" && handshake != "ENTETE" && handshake != "OFF") return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidInterfaceConfigurationCharacterLength(const string type, const string length)
{
	if (type == "SYNCHRONE" && length == "") return TRUE;

	if (type == "ASYNCHRONE")
	{
		if (length == "5" || length == "6" || length == "7" || length == "8") return TRUE;
	}

	return FALSE;
}

bool CEquipM1752::ValidInterfaceConfigurationParity(const string type, const string parity)
{
	if (type == "SYNCHRONE" && parity == "") return TRUE;

	if (type == "ASYNCHRONE")
	{
		if (parity == "PAIR" || parity == "IMPAIR" || parity == "SANS") return TRUE;
	}

	return FALSE;
}

bool CEquipM1752::ValidInterfaceConfigurationNumberStopBits(const string type, const string number)
{
	if (type == "SYNCHRONE" && number == "") return TRUE;

	if (type == "ASYNCHRONE")
	{
		if (number == "1" || number == "2") return TRUE;
	}

	return FALSE;
}

bool CEquipM1752::ValidInterfaceConfigurationDataFlowControl(const string data_flow)
{
	if (data_flow == "XON" || data_flow == "PAE") return TRUE;

	return FALSE;
}

/******************** Aux Interface configuration ********************/

TAuxInterfaceConfiguration CEquipM1752::GetAuxInterfaceConfiguration(const string id)
{
	return aux_interfaces_configurations[id];
}

void CEquipM1752::SetAuxInterfaceConfiguration(const string id, const TAuxInterfaceConfiguration value)
{
	aux_interfaces_configurations[id] = value;
}

bool CEquipM1752::ValidAuxInterfaceConfiguration(const string id)
{
	if (aux_interfaces_configurations.find(id) == aux_interfaces_configurations.end()) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAuxInterfaceConfigurationVersion(const string id)
{
	if (id == "IA5" || id == "IA6")
	{
		if (quadrivoie == false) return FALSE;
	}

	return TRUE;
}

string CEquipM1752::GetChannelFromAuxInterfaceConfiguration(const string aux_interface)
{
	if (aux_interface == "IA3") return "A1";
	if (aux_interface == "IA4") return "A2";
	if (aux_interface == "IA5") return "B1";

	return "B2";
}

bool CEquipM1752::ValidAuxInterfaceConfigurationElectricalCharacteristic(const string characteristic)
{
	if (characteristic == "EIA485" || characteristic == "V28" || characteristic == "V11"
		|| characteristic == "V11_DA" || characteristic == "EIA485_DA")
			return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAuxInterfaceConfigurationBaudrate(const string baudrate)
{
	if (baudrate == "00300" || baudrate == "00600" || baudrate == "01200" || baudrate == "02400"
		|| baudrate == "04800" || baudrate == "09600" || baudrate == "19200")
			return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAuxInterfaceConfigurationCharacterLength(const string length)
{
	if (length == "7" || length == "8") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAuxInterfaceConfigurationCharacterParity(const string parity)
{
	if (parity == "PAIR" || parity == "IMPAIR" || parity == "SANS") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAuxInterfaceConfigurationNumberStopBit(const string number)
{
	if (number == "1" || number == "2") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAuxInterfaceConfigurationRadioAddress(const string address)
{
	if (address.length() != 3) return FALSE;

	int val = atoi(address.c_str());

	if (val<0 || val>999) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAuxInterfaceConfigurationEquipmentType(const string id, const string type)
{
	if (type == "NORAD"
		|| type == "TMR6211" || type == "TMR6200" || type == "TMR6209" || type == "TMR5200" || type == "TMR5201"
		|| type == "XK2100" || type == "XK2500") return TRUE;

	if (id == "IA3" || id == "IA5")
	{
		// only transmitter
		if (type == "TRC1242" || type == "TRC1232" || type == "TRC1236" || type == "TRC1237" || type == "TRC1352"
			|| type == "TRC1332" || type == "TRC109" || type == "TRC110" || type == "TMR6300" || type == "TMR6309"
			|| type == "TMR6305" || type == "TMR5300" || type == "TMR5309")
				return TRUE;
	}
	else
	{
		// only receiver
		if (type == "TRC1241" || type == "TRC241" || type == "TMR6100" || type == "TMR5100")
			return TRUE;
	}

	return FALSE;
}

/************** LocalRemote Interface configuration ****************/

TLocalRemoteInterfaceConfiguration CEquipM1752::GetLocalRemoteInterfaceConfiguration(const string id)
{
	return local_remote_interfaces_configurations[id];
}

void CEquipM1752::SetLocalRemoteInterfaceConfiguration(const string id, const TLocalRemoteInterfaceConfiguration value)
{
	local_remote_interfaces_configurations[id] = value;
}

string CEquipM1752::GetLocalRemoteInterfaceConfigurationFromChannel(const string id)
{
	if (id == "A1") return "TC1";
	if (id == "A2") return "TC2";
	if (id == "B1") return "TC3";
	if (id == "B2") return "TC4";

	return DEFAULT_STRING_VALUE;
}

bool CEquipM1752::ValidLocalRemoteInterfaceConfiguration(const string id)
{
	if (local_remote_interfaces_configurations.find(id) == local_remote_interfaces_configurations.end()) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidLocalRemoteInterfaceConfigurationVersion(const string id)
{
	if (id == "TC3" || id == "TC4")
	{
		if (quadrivoie == false) return FALSE;
	}

	return TRUE;
}

bool CEquipM1752::ValidLocalRemoteInterfaceConfigurationElectricalCharacteristic(const string characteristic)
{
	if (characteristic == "V28" || characteristic == "V11" || characteristic == "V11_DA") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidLocalRemoteInterfaceConfigurationBaudrate(const string baudrate)
{
	if (baudrate == "00300" || baudrate == "00600" || baudrate == "01200" || baudrate == "02400"
		|| baudrate == "04800" || baudrate == "09600" || baudrate == "19200") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidLocalRemoteInterfaceConfigurationCharacterLength(const string length)
{
	if (length == "7" || length == "8") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidLocalRemoteInterfaceConfigurationCharacterParity(const string parity)
{
	if (parity == "PAIR" || parity == "IMPAIR" || parity == "SANS") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidLocalRemoteInterfaceConfigurationNumberStopBits(const string number)
{
	if (number == "1" || number == "2") return TRUE;

	return FALSE;
}

/************** AF Channel configuration ****************/

TAFChannelConfiguration CEquipM1752::GetAfChannelConfiguration(const string id)
{
	return af_channels_configurations[id];
}

void CEquipM1752::SetAfChannelConfiguration(const string id, const TAFChannelConfiguration value)
{
	af_channels_configurations[id] = value;
}

void CEquipM1752::SetAfChannelOutputLevel(const string id, const int value)
{
	af_channels_configurations[id].output_level = value;
}

bool CEquipM1752::ValidAfChannelConfiguration(const string id)
{
	if (af_channels_configurations.find(id) == af_channels_configurations.end()) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAfChannelConfigurationVersion(const string id)
{
	if (id == "BF3" || id == "BF4")
	{
		if (quadrivoie == false) return FALSE;
	}

	return TRUE;
}

bool CEquipM1752::ValidAfChannelConfigurationInputLevel(const string level)
{
	if (level == "00" || level == "18") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAfChannelConfigurationOutputLevel(const string level)
{
	if (level[0] != '-' && level[0] != '+') return FALSE;

	if (level.length() != 3) return FALSE;

	int val = atoi(level.c_str());

	if (val<-30 || val>10) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAfChannelConfigurationInterfaceType(const string type)
{
	if (type == "SYMETRIQUE" || type == "ASYMETRIQUE") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAfChannelConfigurationPttType(const string ptt)
{
	if (ptt == "TTL" || ptt == "COL_OUV" || ptt == "COL_OUV_M") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAfChannelConfigurationPttTempo(const string tempo)
{
	if (tempo.length() != 4) return FALSE;

	int val = atoi(tempo.c_str());

	if (val<0 || val>9999) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAfChannelConfigurationMuteSignal(const string mute)
{
	if (mute == "TTL" || mute == "COL_OUV" || mute == "COL_OUV_M") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAfChannelConfigurationMuteDelay(const string delay)
{
	if (delay.length() != 4) return FALSE;

	int val = atoi(delay.c_str());

	if (val<0 || val>5000) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAfChannelConfigurationRadioDelay(const string delay)
{
	if (delay.length() != 4) return FALSE;

	int val = atoi(delay.c_str());

	if (val<0 || val>9999) return FALSE;

	return TRUE;
}

/************** Ale Parameter configuration ****************/

TAleParameter CEquipM1752::GetAleParameter(const string id)
{
	return ale_parameter[id];
}

void CEquipM1752::SetAleParameter(const string id, const TAleParameter conf)
{
	ale_parameter[id] = conf;
}

/* **************************************************************************
METHODE :		GetAleTwa()
TRAITEMENT:		Renvoi le twa courant
***************************************************************************	*/
int CEquipM1752::GetAleTwa(const string id)
{
	if (channels[id].link_management_type == "LAUTO")
		return ale_parameter[id].twa_automatic;

	return ale_parameter[id].twa_manual;
}

/* **************************************************************************
METHODE :		SetAleStatus()
TRAITEMENT:		Change le status de la liaison ale
***************************************************************************	*/
void CEquipM1752::SetAleStatus(const string id, const string state)
{
	ale_parameter[id].ale_status = state;

	// On envoi un STL
	((CProtoTRC1752*)proto)->SignalSTL(id);
}

/* **************************************************************************
METHODE :		GetAleStatus()
TRAITEMENT:		Retourne le status de la liaison ale
***************************************************************************	*/
string CEquipM1752::GetAleStatus(const string id)
{
	return ale_parameter[id].ale_status;
}

/* **************************************************************************
METHODE :		IsLink()
TRAITEMENT:		Indique si le canal est dans un etat linké
***************************************************************************	*/
bool CEquipM1752::IsLink(const string id)
{
	string val = ale_parameter[id].ale_status;

	if (val == "LKD" || val == "LKG" || val == "SAM" || val == "RAM")
		return TRUE;

	return FALSE;
}

/* **************************************************************************
METHODE :		SetAleChannelInScanset()
TRAITEMENT:		Change le channel en cours dans le scanset
***************************************************************************	*/
void CEquipM1752::SetAleChannelInScanset(const string id, const int index)
{
	ale_parameter[id].index_channel_in_scanset = index;
}

/* **************************************************************************
METHODE :		GetAleChannelInScanset()
TRAITEMENT:		Retourne le channel en cours dans le scanset
***************************************************************************	*/
int CEquipM1752::GetAleChannelInScanset(const string id)
{
	return ale_parameter[id].index_channel_in_scanset;
}

int CEquipM1752::GetAleLinkProtectionLevel(const string id)
{
	return ale_parameter[id].link_protection_level;
}

string CEquipM1752::GetAleKeyManagement(const string id)
{
	return ale_parameter[id].key_management;
}

int CEquipM1752::GetAleKeyPosition(const string id)
{
	return ale_parameter[id].key_position;
}

void CEquipM1752::SetAleKeyPosition(const string id, int pos)
{
	ale_parameter[id].key_position = pos;
}

/* **************************************************************************
METHODE :		GetAleSoundIndex()
TRAITEMENT:		Retourne le channel en cours de sounding
***************************************************************************	*/
int CEquipM1752::GetAleSoundIndex(const string id)
{
	return ale_parameter[id].sounding_index ;
}

/* **************************************************************************
METHODE :		GetAleSilence()
TRAITEMENT:		Retourne l'etat du silence
***************************************************************************	*/
string CEquipM1752::GetAleSilence(const string id)
{
	return ale_parameter[id].respond ;
}

/* **************************************************************************
METHODE :		ResetAleSoundIndex()
TRAITEMENT:		Remet le sound index à -1
***************************************************************************	*/
void CEquipM1752::ResetAleSoundIndex(const string id)
{
	ale_parameter[id].sounding_index = -1 ;
}

/* **************************************************************************
METHODE :		SetAleEstAppele()
TRAITEMENT:		Change la valeur indiquant qui appelle
***************************************************************************	*/
void CEquipM1752::SetAleEstAppele(const string id, bool value)
{
	ale_parameter[id].est_appele = value;
}

/* **************************************************************************
METHODE :		GetAleEstAppele()
TRAITEMENT:		Indique qui appelle
***************************************************************************	*/
bool CEquipM1752::GetAleEstAppele(const string id)
{
	return ale_parameter[id].est_appele ;
}

/* **************************************************************************
METHODE :		NextSound()
TRAITEMENT:		Recherche le prochain index à sounder
				Positionne l'index dans la structure
				Retourne le délai à attendre en secondes
***************************************************************************	*/
int CEquipM1752::NextSound(const string id)
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		int index = ((ale_parameter[id].sounding_index+1)%(NB_RCH-1));
		//int index = index_deb;
		int incr = 0;
		TRch rch;
	while (incr != NB_RCH) // Pour eviter de boucler sans fin
	{
		incr++;
		if (!GetRch(id, index, rch))
			// Fin atteinte
			index = 0;

		if (rch.ed == "ON") // trouvé
		{
			ale_parameter[id].sounding_index = index;
			LeaveCriticalSection((CRITICAL_SECTION*)&crit);
			return rch.sound_interv;
		}

		index = (index+1)%(NB_RCH-1);
	}

	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
	return DEFAULT_INT_VALUE;
}

bool CEquipM1752::ValidAleParameter(const string id)
{
	if (id == "A1" || id == "B1") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAleParameterVersion(const string id)
{
	if (id == "B1")
	{
		if (quadrivoie == false) return FALSE;
	}

	return TRUE;
}

bool CEquipM1752::ValidAleParameterOnOff(const string value)
{
	if (value == "ON" || value == "OFF") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAleParameterAgingPercentage(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 3 || val<0 || val>100) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterAgingTime(const string value)
{
	int val = atoi(value.substr(0,2).c_str());

	if (value.length() != 4 || value.substr(2,2) != ".0" || val<0 || val>8)  return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterServiceActivation(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 2 || val<0 || val>10) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterScanRate(const string value)
{
	if (value == "2" || value == "5") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAleParameterTwa(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 3 || val<0 || val>999) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterTwt(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 4 || val<0 || val>99) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterTuneTime(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 4 || val<0 || val>9999) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterPttGestion(const string value)
{
	if (value == "WIRE" || value == "SERIAL") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAleParameterSoundLength(const string value)
{
	if (value == "---") return TRUE;

	int val = atoi(value.c_str());

	if (value.length() != 3 || val<0 || val>100) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterRetries(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 1 || val<0 || val>9) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterLongSoundLimit(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 2 || val<0 || val>99) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterCmsChoice(const string value)
{
	if (value == "CHA" || value == "BST" || value == "LMF") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAleParameterAleTerminationFrame(const string value)
{
	if (value == "TIS" || value == "TAS") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAleParameterIndexChannelTable(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 2 || val<0 || val>99) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterUsableFrequency(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 8 || val<1500000 || val>30000000) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterCallType(const string value)
{
	if (value == "STD" || value == "ANY" || value == "SAN" || value == "NUL"
		|| value == "SEL" || value == "WIL" || value == "NET" || value == "ALL"
		|| value == "GRP" || value == "SAL") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAleParameterIndexSelfAddress(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 2 || val<0 || val>19) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterStationNetworkGroup(const string value)
{
	if (value == "S" || value == "G" || value == "N") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAleParameterCalledAddress(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 2 || val<0 || val>99) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterCalledAddressString(const string value)
{
	if (value.length() != 3) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterIndexStationTableGroup(const string value)
{
	istringstream trame (value.c_str());
	string val = "";
	int vali;

	while(getline(trame, val, '/'))
	{
		vali = atoi(val.c_str());

		if (val.length() != 2 || vali<0 || vali>99) return FALSE;
	}

	return TRUE;
}

bool CEquipM1752::ValidAleParameterAgc(const string value)
{
	if (value == "OFF" || value == "SLOW" || value == "MEDIUM" || value == "FAST" || value == "NOMGT")
		return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAleParameterCallLength(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 3 || val<0 || val>999) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterAmdMessage(const string value)
{
	if (value.length() > 90) return FALSE;

	if (-1 == value.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789 !#$%&'()*+,./:<>=?[]-_")) return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAleParameterLinkProtectionLevel(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 1 || val<0 || val>2) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidAleParameterKeyManagement(const string value)
{
	if (value == "FIX" || value == "24H") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidAleParameterKeyPosition(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 2 || val<0 || val>30) return FALSE;

	return TRUE;
}



/******************** structure table ********************/

string CEquipM1752::GetTableLtName(const string id, const string table_name)
{
	if (table_name == "LT0") return table[id].lt0.name;

	return table[id].lt1.name;

}

bool CEquipM1752::ValidTableLT(const string id)
{
	if (id == "LT0" || id == "LT1") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidTableName(const string value)
{
	if (value.length() != 3) return FALSE;

	if (-1 == value.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")) return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidTableType(const string value)
{
	if (value == "SAD" || value == "RCH" || value == "NET" || value == "STA" || value == "SST"
		|| value == "LT0" || value == "LT1") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidTableCRC(const string value)
{
	int val = atoi(value.c_str());

	if (value.length() != 5 || val<0 || val>65535) return FALSE;

	return TRUE;
}

unsigned short CEquipM1752::CalculateCRC(const string data)
{
	int size = data.length();
	unsigned short crc = 0;

	for (int i=0; i<size; i++)
		crc = crc_ccitt(data[i], crc);


	return crc;
}

unsigned short CEquipM1752::crc_ccitt(unsigned char data, unsigned short crc)
{
	unsigned char i, bit;

	for (i = 0x80;i;i>>=1)
	{
		bit = ((( crc & 0x8000) ? 1 : 0) ^ ((data & i) ? 1 : 0));
		crc <<= 1;
		if (bit) crc ^= 0x1021;
	}
	return crc;
}

TTableLT CEquipM1752::GetTableLT(const string id, const string table)
{
	if(table == "LT0")
		return this->table[id].lt0;

	return this->table[id].lt1;
}

void CEquipM1752::SetTableLT(const string id, const string table, const TTableLT value)
{
	if (table == "LT0")
		this->table[id].lt0 = value;
	else
		this->table[id].lt1 = value;
}

void CEquipM1752::ActiveLT1(const string id)
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		// Copie LT1 dans LT0
		this->table[id].lt0 = this->table[id].lt1;

		// Efface LT1
		this->table[id].lt1.name = "";
		for (int j=0; j<NB_LT_KEY; j++)
			table[id].lt1.key[j] = FALSE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

bool CEquipM1752::ValidTableAddress(const string value)
{
	if (value.length() < 1 || value.length() > 15) return FALSE;

	if (-1 == value.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")) return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidTableKey(const string value)
{
	if (value.length() < 2 || value.length() >= 3) return FALSE;

	if (-1 == value.find_first_not_of("0123456789"))
	{
		if(atoi(value.c_str())>1 && atoi(value.c_str())<=31)return TRUE;
	}

	return FALSE;
}

bool CEquipM1752::ValidTableLt0(const string value)
{
	if (value.length() < 1 || value.length() > 3) return FALSE;

	if (-1 == value.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789")) return TRUE;

	return FALSE;
}

bool CEquipM1752::ExtractTableChannels(const string value, bool list[], bool all_autorized)
{
	istringstream data (value.c_str());
	string tmp;
	int convert;

	while (getline(data, tmp, '/'))
	{
		if (tmp == "ALL")
		{
			if (all_autorized == FALSE)  return FALSE;
			if (!getline(data, tmp, '/'))
				// c'etait bien le dernier
				list[NB_LIST_CHANNEL-1] = TRUE;
			else
				// ou pas
				return FALSE;
			break;
		}

		convert = atoi(tmp.c_str());

		if (tmp.length() != 2 || convert<0 || convert>99 || list[convert] == TRUE) return FALSE;
		list[convert] = TRUE;
	}

	if (value[value.length()-1] == '/') return FALSE;

	return TRUE;

}

void CEquipM1752::AddRch(const string id, const int index, const TRch value)
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		table[id].rch[index] = value;
		table[id].rch_present = TRUE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

int CEquipM1752::ExtractTableRch(const string data[], TRch &rch)
{
	int res;
	int val;

	res = atoi(data[1].c_str());
	if (data[1].length() != 2 || res<0 || res>99) return -1;

	val = atoi(data[2].c_str());
	if (data[2].length() != 3 || val<0 || val>999) return -1;
	rch.channel = val;

	// freq
	if (data[3] != "")
	{
		val = atoi(data[3].c_str());
		if (data[3].length() != 8 || val<1500000 || val>30000000) return -1;
		rch.tx_freq = val;
	}

	if (data[4] != "")
	{
		val = atoi(data[4].c_str());
		if (data[4].length() != 8 || val<1500000 || val>30000000) return -1;
		rch.rx_freq = val;
	}

	// mode
	if (data[5] != "" && data[5] != "USB" && data[5] != "LSB" && data[5] != "ISB") return -1;
	rch.mode_tx = data[5];
	if (data[6] != "" && data[6] != "USB" && data[6] != "LSB" && data[6] != "ISB") return -1;
	rch.mode_rx = data[6];

	// bfo
	if (data[7] != "")
	{
		val = atoi(data[7].c_str());
		if (data[7].length() != 6 || val<-7990 || val>7990 || (val != 0 && data[7][0] != '-' && data[7][0] != '+'))
			return -1;
		rch.bfo = val;
	}

	// filter
	if (data[8] != "")
	{
		val = atoi(data[8].c_str());
		if (data[8].length() != 3 || val<0 || val>9)
			return -1;
		rch.filter = val;
	}

	// agc
	if (data[9] != "")
	{
		val = atoi(data[9].c_str());
		if (data[9].length() != 1 || val<0 || val>3)
			return -1;
		rch.agc = val;
	}

	// squelch
	if (data[10] != "")
	{
		val = atoi(data[10].c_str());
		if (data[10].length() != 4 || val<-128 || val>63 || (data[10][0] != '-' && data[10][0] != '+'))
			return -1;
		rch.squelch = val;
	}

	// pwr
	if (data[11] != "")
	{
		val = atoi(data[11].c_str());
		if (data[11].length() != 3 || val<-50 || val>0)
			return -1;
		rch.pwr = val;
	}

	// ed
	if (data[12] != "ON" && data[12] != "OFF") return -1;
	rch.ed = data[12];

	// sound interv
	if (data[13] != "")
	{
		val = atoi(data[13].c_str());
		if (data[13].length() != 4 || val<0 || val>1439)
			return -1;
		rch.sound_interv = val;

	}

	// self add
	if (data[14] != "")
	{
		val = atoi(data[14].c_str());
		if (data[14].length() != 2 || val<0 || val>19)
			return -1;
		rch.self_add = val;
	}

	if ((data[13] == "" && data[14] != "") || (data[13] != "" && data[14] == "")) return -1;

	return res;
}

bool CEquipM1752::IsRchPresent(const string id, const int index)
{
	bool value = FALSE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		if (index == 100) value = TRUE;
		else
			if (table[id].rch[index].channel != DEFAULT_INT_VALUE) value = TRUE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return value;
}

bool CEquipM1752::IsRchPresent(const string id)
{
	return table[id].rch_present;
}

/**************************************************************
  * GetRch ()
  * renvoi le rch de la voie "id" à la position "index"
  * retourne FALSE si la ligne n'est pas trouvée
  *          TRUE et le rch en paramètre sinon
**/
bool CEquipM1752::GetRch(const string id, const int index, TRch &value)
{
	if (index < 0 || index > NB_RCH || &value == NULL) return FALSE;

	value = table[id].rch[index];

	if (value.channel == DEFAULT_INT_VALUE) return FALSE;

	return TRUE;
}

/* **************************************************************************
METHODE :		GetRchSoundDelay()
TRAITEMENT:		Renvoi le delai pour l'index rch de la voie
***************************************************************************	*/
int CEquipM1752::GetRchSoundDelay(const string id, const int index)
{
	if (index < 0 || index > NB_RCH) return FALSE;

	return table[id].rch[index].sound_interv;
}

void CEquipM1752::AddSad(const string id, const int index, const TSad value)
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		table[id].sad[index] = value;
		table[id].sad_present = TRUE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

int CEquipM1752::ExtractTableSad(const string data [], TSad &sad)
{
	int val;
	int res;

	res = atoi(data[1].c_str());
	if (data[1].length() != 2 || res<0 || res>19) return -1;

	if (ValidTableAddress(data[2]) == FALSE) return -1;
	sad.self_address = data[2];

	if (data[3] != "")
	{
		val = atoi(data[3].c_str());
		if (data[3].length() != 2 || val<0 || val>19) return -1;
		sad.net_address = val;
	}

	if (data[4] != "")
	{
		val = atoi(data[4].c_str());
		if (data[4].length() != 2 || val<1 || val>50) return -1;
		sad.slot = val;
	} else if (data[3] != "") return -1;

	if (data[5] != "" && ExtractTableChannels(data[5], sad.valid_channels) == FALSE) return -1;

	return res;
}

bool CEquipM1752::IsSadPresent(const string id)
{
	return table[id].sad_present;
}

/**************************************************************
  * GetSad ()
  * renvoi le sad de la voie "id" à la position "index"
  * retourne FALSE si la ligne n'est pas trouvée
  *          TRUE et le sad en paramètre sinon
**/
bool CEquipM1752::GetSad(const string id, const int index, TSad &value)
{
	if (index < 0 || index > NB_SAD || &value == NULL) return FALSE;

	value = table[id].sad[index];

	if (value.self_address == DEFAULT_STRING_VALUE) return FALSE;

	return TRUE;
}

/**************************************************************
  * GetSad ()
  * renvoi l'index du sad de la voie "id" ayant pour valeur adr
  * retourne DEFAULT_INT_VALUE si la ligne n'est pas trouvée
**/
int CEquipM1752::GetSad(const string id, const string adr)
{
	int val = 0;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);

		while(val != NB_SAD)
		{
			if (table[id].sad[val].self_address == adr) break;
			val++;
		}

	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	if (val == NB_SAD) val = DEFAULT_INT_VALUE;

	return val;
}

void CEquipM1752::AddSta(const string id, const int index, const TSta value)
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		table[id].sta[index] = value;
		table[id].sta_present = TRUE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

int CEquipM1752::ExtractTableSta(const string data [], TSta &sta)
{
	int res, val;

	res = atoi(data[1].c_str());
	if (data[1].length() != 2 || res<0 || res>99) return -1;

	if (ValidTableAddress(data[2]) == FALSE) return -1;
	sta.address_ale = data[2];

	if (data[3] != "")
	{
		if (ValidTableAddress(data[3]) == FALSE) return -1;
		sta.address_arq = data[3];
	}

	if (data[4] != "")
	{
		val = atoi(data[4].c_str());
		if (data[4].length() != 5 || val<131 || val>99999) return -1;
		sta.twr = val;
	}

	if (data[5] != "" && ExtractTableChannels(data[5], sta.valid_channels) == FALSE) return -1;

	return res;
}

bool CEquipM1752::IsStaPresent(const string id)
{
	return table[id].sta_present;
}

/**************************************************************
  * GetSta ()
  * renvoi le sta de la voie "id" à la position "index"
  * retourne FALSE si la ligne n'est pas trouvée
  *          TRUE et le sta en paramètre sinon
**/
bool CEquipM1752::GetSta(const string id, const int index, TSta &value)
{
	if (index < 0 || index > NB_STA || &value == NULL) return FALSE;

	value = table[id].sta[index];

	if (value.address_ale == DEFAULT_STRING_VALUE) return FALSE;

	return TRUE;
}

/**************************************************************
  * GetSta ()
  * renvoi l'index du sta de la voie "id" ayant pour valeur adr
  * retourne DEFAULT_INT_VALUE si la ligne n'est pas trouvée
**/
int CEquipM1752::GetSta(const string id, const string adr)
{
	int val = 0;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);

		while(val != NB_STA)
		{
			if (table[id].sta[val].address_ale == adr) break;
			val++;
		}

	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	if (val == NB_STA) val = DEFAULT_INT_VALUE;

	return val;
}

void CEquipM1752::AddNet(const string id, const int index, const TNet value)
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		table[id].net[index] = value;
		table[id].net_present = TRUE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

int CEquipM1752::ExtractTableNet(const string data [], TNet &net)
{
	int res, val;

	res = atoi(data[1].c_str());
	if (data[1].length() != 2 || res<0 || res>19) return -1;

	if (ValidTableAddress(data[2]) == FALSE) return -1;
	net.net_address = data[2];

	for(int i=3; i<NB_PARAM_NET_FILE; i++)
		if (data[i] != "")
		{
			val = atoi(data[i].c_str());
			if (data[i].length() != 2 || val<0 || val>99) return -1;
			net.net_member[i-2] = val;
		}

	return res;
}

bool CEquipM1752::IsNetPresent(const string id, const int index)
{
	if (table[id].net[index].net_address != DEFAULT_STRING_VALUE) return TRUE;

	return FALSE;
}

bool CEquipM1752::IsNetPresent(const string id)
{
	return table[id].net_present;
}

/**************************************************************
  * GetNet ()
  * renvoi le net de la voie "id" à la position "index"
  * retourne FALSE si la ligne n'est pas trouvée
  *          TRUE et le net en paramètre sinon
**/
bool CEquipM1752::GetNet(const string id, const int index, TNet &value)
{
	if (index < 0 || index > NB_NET || &value == NULL) return FALSE;

	value = table[id].net[index];

	if (value.net_address == DEFAULT_STRING_VALUE) return FALSE;

	return TRUE;
}

/**************************************************************
  * GetNet ()
  * renvoi l'index du net de la voie "id" ayant pour valeur adr
  * retourne DEFAULT_INT_VALUE si la ligne n'est pas trouvée
**/
int CEquipM1752::GetNet(const string id, const string adr)
{
	int val = 0;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);

		while(val != NB_NET)
		{
			if (table[id].net[val].net_address == adr) break;
			val++;
		}

	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	if (val == NB_NET) val = DEFAULT_INT_VALUE;

	return val;
}

void CEquipM1752::AddSst(const string id, const int index, const TSst value)
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		table[id].sst[index] = value;
		table[id].sst_present = TRUE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

int CEquipM1752::ExtractTableSst(const string data [], TSst &sst)
{
	int res;

	res = atoi(data[1].c_str());
	if (data[1].length() != 1 || res<0 || res>9) return -1;

	if (ExtractTableChannels(data[2], sst.scan_set_channel, FALSE) == FALSE) return -1;

	return res;
}

bool CEquipM1752::IsSstPresent(const string id, int index)
{
	bool value = FALSE;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		for (int i=0; i<NB_LIST_CHANNEL; i++)
			if (table[id].sst[index].scan_set_channel[i] == TRUE)
			{
				value = TRUE;
				break;
			}
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return value;
}

bool CEquipM1752::IsSstPresent(const string id)
{
	return table[id].sst_present;
}

/**************************************************************
  * GetSst ()
  * renvoi le sst de la voie "id" à la position "index"
  * retourne FALSE si la ligne n'est pas trouvée
  *          TRUE et le sst en paramètre sinon
**/
bool CEquipM1752::GetSst(const string id, const int index, TSst &value)
{
	if (index < 0 || index > NB_SST || &value == NULL) return FALSE;

	if (IsSstPresent(id,index) == FALSE) return FALSE;

	value = table[id].sst[index];

	return TRUE;
}

void CEquipM1752::WriteTable(const string id, const string position)
{
	if (position == "1")
		table_stored1[id] = table[id];

	table_stored2[id] = table[id];
}

void CEquipM1752::ReadTable(const string id, const string position)
{
	if (position == "1")
		table[id] = table_stored1[id];

	// FDI - 11/11/2010
	if (position == "2")
		table[id] = table_stored2[id];
}

void CEquipM1752::DeleteSad(const string id)
{
	TSad sad;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	for (int i=0; i<NB_SAD; i++)
		table[id].sad[i] = sad;
	table[id].sad_present = FALSE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

void CEquipM1752::DeleteRch(const string id)
{
	TRch rch;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	for (int i=0; i<NB_RCH; i++)
		table[id].rch[i] = rch;
	table[id].rch_present = FALSE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

void CEquipM1752::DeleteNet(const string id)
{
	TNet net;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	for (int i=0; i<NB_NET; i++)
		table[id].net[i] = net;
	table[id].net_present = FALSE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

void CEquipM1752::DeleteSta(const string id)
{
	TSta sta;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	for (int i=0; i<NB_STA; i++)
		table[id].sta[i] = sta;
	table[id].sta_present = FALSE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

void CEquipM1752::DeleteSst(const string id)
{
	TSst sst;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	for (int i=0; i<NB_SST; i++)
		table[id].sst[i] = sst;
	table[id].sst_present = FALSE;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

void CEquipM1752::DeleteLt0(const string id)
{
	TTableLT lt;
	table[id].lt0 = lt;
}

void CEquipM1752::DeleteLt1(const string id)
{
	TTableLT lt;
	table[id].lt1 = lt;
}

void CEquipM1752::DeleteTableStored(const string id, const string id_number)
{
	TTable table;
	if (id_number == "1")
		table_stored1[id] = table;

	table_stored2[id] = table;
}

bool CEquipM1752::ValidTableSad(const string id)
{
	int j;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	TTable *table_courante = &(table[id]);
	// Pour toutes les entrées de la table sad
	for (int i=0; i<NB_SAD; i++)
	{
		// S'il y a une net address on vérifie son existance
		if ((*table_courante).sad[i].net_address != DEFAULT_INT_VALUE)
		{
			if ((*table_courante).net[(*table_courante).sad[i].net_address].net_address == DEFAULT_STRING_VALUE)
			{
				LeaveCriticalSection((CRITICAL_SECTION*)&crit);
				return FALSE;
			}
		}

		// On vérifie que la liste de valid channel contient des entrées de RCH
		for (j=0; j<NB_LIST_CHANNEL; j++)
		{
			if ((*table_courante).sad[i].valid_channels[j] == TRUE)
			{
				if (j != 100 && (*table_courante).rch[j].channel == DEFAULT_INT_VALUE)
				{
					LeaveCriticalSection((CRITICAL_SECTION*)&crit);
					return FALSE;
				}
			}
		}
	}
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return TRUE;
}

bool CEquipM1752::ValidTableSta(const string id)
{
	int j;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	TTable *table_courante = &(table[id]);
	// Pour toutes les entrées de la table sta
	for (int i=0; i<NB_STA; i++)
	{
		// On vérifie que la liste de valid channel contient des entrées de STA
		for (j=0; j<NB_LIST_CHANNEL; j++)
		{
			if ((*table_courante).sta[i].valid_channels[j] == TRUE)
			{
				if (j != 100 && (*table_courante).rch[j].channel == DEFAULT_INT_VALUE)
				{
					LeaveCriticalSection((CRITICAL_SECTION*)&crit);
					return FALSE;
				}
			}
		}
	}
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return TRUE;
}

bool CEquipM1752::ValidTableNet(const string id)
{
	int j;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	TTable *table_courante = &(table[id]);
	// Pour toutes les entrées de la table net
	for (int i=0; i<NB_NET; i++)
	{
		// On vérifie que la liste de valid channel contient des entrées de NET
		for (j=0; j<NB_NET_ADDRESS; j++)
		{
			if ((*table_courante).net[i].net_member[j] != DEFAULT_INT_VALUE)
			{
				//if (j != 100 && (*table_courante).rch[(*table_courante).net[i].net_member[j]].channel == DEFAULT_INT_VALUE)
				// FDI - 20120208
				if (j != 100 && (*table_courante).sta[(*table_courante).net[i].net_member[j]].address_ale == DEFAULT_STRING_VALUE)
				{
					LeaveCriticalSection((CRITICAL_SECTION*)&crit);
					return FALSE;
				}
			}
		}
	}
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return TRUE;
}

bool CEquipM1752::ValidTableSst(const string id)
{
	int j;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	TTable *table_courante = &(table[id]);
	// Pour toutes les entrées de la table sst
	for (int i=0; i<NB_SST; i++)
	{
		// On vérifie que la liste de valid channel contient des entrées de SST
		for (j=0; j<NB_LIST_CHANNEL; j++)
		{
			if ((*table_courante).sst[i].scan_set_channel[j] == TRUE)
			{
				if (j != 100 && (*table_courante).rch[j].channel == DEFAULT_INT_VALUE)
				{
					LeaveCriticalSection((CRITICAL_SECTION*)&crit);
					return FALSE;
				}
			}
		}
	}
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return TRUE;
}


/******************** structure principale ********************/

/* **************************************************************************
METHODE :		GetMode()
TRAITEMENT:		Retourne le mode
***************************************************************************	*/
bool CEquipM1752::GetMode()
{
	return this->mode;
}

/* **************************************************************************
METHODE :		SetMode()
TRAITEMENT:		Change le mode
***************************************************************************	*/
void CEquipM1752::SetMode(const bool mode, bool signaling)
{
	this->mode = mode;

	if (signaling == true) ((CProtoTRC1752*)proto)->SendSignaling("ULO");
}

/* **************************************************************************
METHODE :		GetGic()
TRAITEMENT:		Retourne le gic du modem
***************************************************************************	*/
string CEquipM1752::GetGic()
{
	return this->gic;
}

/* **************************************************************************
METHODE :		SetGic()
TRAITEMENT:		Changer le gic du modem
***************************************************************************	*/
void CEquipM1752::SetGic(const string value)
{
	this->gic = value;
}

/* **************************************************************************
METHODE :		GetOrigineHeure()
TRAITEMENT:		Retourne l'origine de l'heure du modem
***************************************************************************	*/
string CEquipM1752::GetOrigineHeure()
{
	return this->origine_heure;
}

/* **************************************************************************
METHODE :		SetOrigineHeure()
TRAITEMENT:		Change l'origine de l'heure du modem
***************************************************************************	*/
void CEquipM1752::SetOrigineHeure(const string value)
{
	this->origine_heure = value;
}

/* **************************************************************************
METHODE :		GetModemDistant()
TRAITEMENT:		Retourne les parametres du modem distant
***************************************************************************	*/
TModemDistant CEquipM1752::GetModemDistant()
{
	return this->distant;
}

/* **************************************************************************
METHODE :		SetModemDistant()
TRAITEMENT:		Change les parametres du modem distant
***************************************************************************	*/
void CEquipM1752::SetModemDistant(const TModemDistant value)
{
	this->distant = value;
}

/* **************************************************************************
METHODE :		SetPcArq()
TRAITEMENT:		Change les parametres du pc arq
***************************************************************************	*/
void CEquipM1752::SetPcArq(const string id, const TPCArq arq)
{
	this->pc_arq[id] = arq;
}

/* **************************************************************************
METHODE :		GetPcArq()
TRAITEMENT:		Retourne les parametres du pc arq
***************************************************************************	*/
TPCArq CEquipM1752::GetPcArq(const string id)
{
	return this->pc_arq[id];
}

string CEquipM1752::GetManufacturer()
{
	return this->manufacturer;
}

void CEquipM1752::SetManufacturer(const string manufacturer)
{
	this->manufacturer = manufacturer;
}

string CEquipM1752::GetIdentity()
{
	return this->identity;
}

void CEquipM1752::SetIdentity(const string identity)
{
	this->identity = identity;
}

TBoard CEquipM1752::GetBoardManagement()
{
	return this->board_management;
}

void CEquipM1752::SetBoardManagement(const TBoard board)
{
	this->board_management = board;
}

TBoard CEquipM1752::GetBoard1()
{
	return this->board_1;
}

void CEquipM1752::SetBoard1(const TBoard board)
{
	this->board_1 = board;
}

TBoard CEquipM1752::GetBoard2()
{
	return this->board_2;
}

void CEquipM1752::SetBoard2(const TBoard board)
{
	this->board_2 = board;
}

bool CEquipM1752::GetQuadrivoie()
{
	return this->quadrivoie;
}

void CEquipM1752::SetQuadrivoie(const bool value)
{
	this->quadrivoie = value;
}

/* **************************************************************************
METHODE :		IsEmetteurMarche()
TRAITEMENT:		Indique si l'emetteur est en marche
***************************************************************************	*/
bool CEquipM1752::IsEmetteurMarche()
{
	return this->emetteur_marche;
}

/* **************************************************************************
METHODE :		SetEmetteurMarche()
TRAITEMENT:		Change la valeur de emetteur_marche
***************************************************************************	*/
void CEquipM1752::SetEmetteurMarche(const bool value)
{
	this->emetteur_marche = value;

	if (value == FALSE)
	{
		((CProtoTRC1752*)proto)->SignalRAD("IA3","RNR");
		((CProtoTRC1752*)proto)->SignalRAD("IA5","RNR");
	}
}

/* **************************************************************************
METHODE :		IsEmetteurPanneMajeure()
TRAITEMENT:		Indique si l'emetteur est en panne majeure
***************************************************************************	*/
bool CEquipM1752::IsEmetteurPanneMajeure()
{
	return this->emetteur_panne_majeure;
}

/* **************************************************************************
METHODE :		SetEmetteurPanneMajeure()
TRAITEMENT:		Change la valeur de panne majeure
***************************************************************************	*/
void CEquipM1752::SetEmetteurPanneMajeure(const bool value)
{
	this->emetteur_panne_majeure = value;

	if (value == TRUE)
	{
		((CProtoTRC1752*)proto)->SignalRAD("IA3","RRE");
		((CProtoTRC1752*)proto)->SignalRAD("IA5","RRE");
	}
}

/* **************************************************************************
METHODE :		IsEmetteurPanneTC()
TRAITEMENT:		Indique si l'emetteur est en panne tc
***************************************************************************	*/
bool CEquipM1752::IsEmetteurPanneTC()
{
	return this->emetteur_panne_tc;
}


/* **************************************************************************
METHODE :		SetEmetteurPanneTC()
TRAITEMENT:		Change la valeur de panne tc
***************************************************************************	*/
void CEquipM1752::SetEmetteurPanneTC(const bool value)
{
	this->emetteur_panne_tc = value;

	return;

	if (value == TRUE)
	{
		((CProtoTRC1752*)proto)->SignalRAD("IA3","RNR");
		((CProtoTRC1752*)proto)->SignalRAD("IA5","RNR");
	}
}

/* **************************************************************************
METHODE :		IsEmetteurEmission()
TRAITEMENT:		Indique si l'emetteur est en émission
***************************************************************************	*/
bool CEquipM1752::IsEmetteurEmission()
{
	return this->emetteur_emission;
}

/* **************************************************************************
METHODE :		SetEmetteurEmission()
TRAITEMENT:		Change la valeur de l'émission
***************************************************************************	*/
void CEquipM1752::SetEmetteurEmission(const bool value)
{
	this->emetteur_emission = value;
}

/* **************************************************************************
METHODE :		IsRecepteurMarche()
TRAITEMENT:		Indique si le recepteur est en marche
***************************************************************************	*/
bool CEquipM1752::IsRecepteurMarche()
{
	return this->recepteur_marche;
}

/* **************************************************************************
METHODE :		SetRecepteurMarche()
TRAITEMENT:		Change la valeur de marche du recepteur
***************************************************************************	*/
void CEquipM1752::SetRecepteurMarche(const bool value)
{
	this->recepteur_marche = value;

	if (value == FALSE)
	{
		((CProtoTRC1752*)proto)->SignalRAD("IA4","RNR");
		((CProtoTRC1752*)proto)->SignalRAD("IA6","RNR");
	}
}

/* **************************************************************************
METHODE :		IsRecepteurPanneMajeure()
TRAITEMENT:		Indique si le recepteur est en panne majeure
***************************************************************************	*/
bool CEquipM1752::IsRecepteurPanneMajeure()
{
	return this->recepteur_panne_majeure;
}

/* **************************************************************************
METHODE :		SetRecepteurPanneMajeure()
TRAITEMENT:		Change la valeur de panne majeure du recepteur
***************************************************************************	*/
void CEquipM1752::SetRecepteurPanneMajeure(const bool value)
{
	this->recepteur_panne_majeure = value;

	if (value == TRUE)
	{
		((CProtoTRC1752*)proto)->SignalRAD("IA4","RRE");
		((CProtoTRC1752*)proto)->SignalRAD("IA6","RRE");
	}
}

/* **************************************************************************
METHODE :		IsRecepteurPanneTC()
TRAITEMENT:		Indique si le recepteur est en panne tc
***************************************************************************	*/
bool CEquipM1752::IsRecepteurPanneTC()
{
	return this->recepteur_panne_tc;
}

/* **************************************************************************
METHODE :		SetRecepteurPanneTC()
TRAITEMENT:		Change la valeur de panne tc du recepteur
***************************************************************************	*/
void CEquipM1752::SetRecepteurPanneTC(const bool value)
{
	this->recepteur_panne_tc = value;

	if (value == TRUE)
	{
		((CProtoTRC1752*)proto)->SignalRAD("IA4","RNR");
		((CProtoTRC1752*)proto)->SignalRAD("IA6","RNR");
	}
}

string CEquipM1752::GetClockPilot()
{
	return this->clock_pilot;
}

void CEquipM1752::SetClockPilot(const string clock)
{
	this->clock_pilot = clock;
}

bool CEquipM1752::ValidClockPilot(const string clock)
{
	if (clock != "INTERNE" && clock != "EXTERNE") return FALSE;

	return TRUE;
}

string CEquipM1752::GetInr()
{
	return this->inr;
}

void CEquipM1752::SetInr(const string inr)
{
	this->inr = inr;
}

bool CEquipM1752::ValidInr(const string inr)
{
	if (inr == "AVEC" || inr == "SANS") return TRUE;

	return FALSE;
}

int CEquipM1752::GetInrRate()
{
	return this->inr_rate;
}

void CEquipM1752::SetInrRate(const int rate)
{
	this->inr_rate = rate;
}

bool CEquipM1752::ValidInrRate(const int rate)
{
	if (rate < 0 || rate > 100) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidDateAndTime(const string datetime)
{
	if (datetime.length() != 17) return FALSE;

	// séparateurs
	if (datetime[2] != '/' || datetime[5] != '/' || datetime[8] != '.' || datetime[11] != 'H' || datetime[14] != '.')
		return FALSE;

	int val = atoi(datetime.substr(0,2).c_str());

	if (val<1 || val>31) return FALSE;

	val = atoi(datetime.substr(3,2).c_str());

	if (val<1 || val>12) return FALSE;

	val = atoi(datetime.substr(6,2).c_str());

	if (val<4 || val>99) return FALSE;

	val = atoi(datetime.substr(9,2).c_str());

	if (val<0 || val>23) return FALSE;

	val = atoi(datetime.substr(12,2).c_str());

	if (val<0 || val>59) return FALSE;

	val = atoi(datetime.substr(15,2).c_str());

	if (val<0 || val>59) return FALSE;

	return TRUE;
}

bool CEquipM1752::ValidTimeAccuracy(const string accuracy)
{
	if (accuracy.length() != 5) return FALSE;

	int val = atoi(accuracy.c_str());

	if (val<0 || val>60000) return FALSE;

	return TRUE;
}

bool CEquipM1752::GetTest(const string id)
{
	return this->test_map[id];
}

void CEquipM1752::SetTest(const string id, const bool value)
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);

		this->test_map[id] = value;

		if (id == "A1" || id == "A2" || id == "B1" || id == "B2")
		{
			if (value == TRUE)
				SetChannelState(id, "HS");
			else
				SetChannelState(id, "INACTIVE");
		} else if (id == "TIROIR")
		{
			if (value == TRUE)
			{
				SetChannelState("A1", "HS");
				SetChannelState("A2", "HS");
				SetChannelState("B1", "HS");
				SetChannelState("B2", "HS");
			}
			else
			{
				if (this->test_map["A1"] == FALSE) SetChannelState("A1", "INACTIVE");
				if (this->test_map["A2"] == FALSE) SetChannelState("A2", "INACTIVE");
				if (this->test_map["B1"] == FALSE) SetChannelState("B1", "INACTIVE");
				if (this->test_map["B2"] == FALSE) SetChannelState("B2", "INACTIVE");
			}
		}

	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

/* **************************************************************************
METHODE :		GetIdentityString()
TRAITEMENT:		Retourne les lignes d'affichage de l'identité du modem
***************************************************************************	*/
void CEquipM1752::GetIdentityString(string &ligne1, string &ligne2)
{
	TBoard board = GetBoard1();
	ligne1 = "A : " + board.capabilities + " " + board.number + "." + board.release + "   ";
	ligne2 = "  " + board.day + board.month + board.year + "     ";

	if (GetQuadrivoie())
	{
		board = GetBoard2();
		ligne1 += "B : " + board.capabilities + " " + board.number + "." + board.release + "   ";
		ligne2 += "  " + board.day + board.month + board.year + "     ";
	}

	board = GetBoardManagement();
	ligne1 += "T : " + board.capabilities + " " + board.number + "." + board.release;
	ligne2 += "  " + board.day + board.month + board.year;
}

/* **************************************************************************
METHODE :		GetTestStringChannel()
TRAITEMENT:		Retourne TRUE si pas d'erreur et FALSE si une erreur est detectée
				sur le modem
                Rempli les lignes d'affichage pour le modem
***************************************************************************	*/
void CEquipM1752::GetTestStringChannel(string &ligne1, string &ligne2)
{
	ligne2 = "";
	int nb_channels = NB_CHANNELS;
	bool test = TRUE;

	if (!GetQuadrivoie()) nb_channels = NB_CHANNELS/2;

	for (int i=0; i<nb_channels; i++)
	{
		ligne2 += CHANNELS[i];
		if (GetTest(CHANNELS[i]))
		{
			ligne2 += " NOK ";
			test = FALSE;
		}
		else
			ligne2 += " OK  ";
	}

	if (test)
		ligne1 = "AUTOTEST TIROIR OK";
	else
		ligne1 = "AUTOTEST TIROIR NOK";
}

/* **************************************************************************
METHODE :		GetTestStringTC()
TRAITEMENT:		Retourne TRUE si pas d'erreur et FALSE cas contraire
                Rempli les lignes d'affichage pour le modem
***************************************************************************	*/
bool CEquipM1752::GetTestStringTC(string &ligne1, string &ligne2)
{
	if (!GetTest("TC") && !GetTest("TC1")
		&& !GetTest("TC2") && !GetTest("TC3")
		&& !GetTest("TC3")) return TRUE;

	ligne1 = "LIAISON DE TELECOMMANDE";
	ligne2 = "EN PANNE";

	return FALSE;
}

/* **************************************************************************
METHODE :		GetTestStringIA()
TRAITEMENT:		Retourne TRUE si pas d'erreur et FALSE cas contraire
                Rempli les lignes d'affichage pour le modem
***************************************************************************	*/
bool CEquipM1752::GetTestStringIA(string &ligne1, string &ligne2, string &ligne3, string &ligne4)
{
	ligne3 = "";
	ligne4 = "";

	int nb_channels = NB_CHANNELS;
	bool test = TRUE;

	if (!GetQuadrivoie()) nb_channels = NB_CHANNELS/2;

	for (int i=0; i<nb_channels; i++)
	{
		if (i<2)
		{
			ligne3 += AUX_INTERFACES_CONFIGURATIONS[i] + ":";
			if (GetTest(AUX_INTERFACES_CONFIGURATIONS[i]))
			{
				ligne3 += " NOK";
				test = FALSE;
			}
			else
				ligne3 += " OK ";

			ligne3 += "  ";
		} else
		{
			ligne4 += AUX_INTERFACES_CONFIGURATIONS[i] + ":";
			if (GetTest(AUX_INTERFACES_CONFIGURATIONS[i]))
			{
				ligne4 += " NOK";
				test = FALSE;
			}
			else
				ligne4 += " OK ";

			ligne4 += "  ";
		}

	}

	ligne1 = "LIAISON TELECOMMANDE";
	ligne2 = "RADIO EN PANNE";

	return test;
}

/* **************************************************************************
METHODE :		GetTestStringDX()
TRAITEMENT:		Retourne TRUE si pas d'erreur et FALSE cas contraire
                Rempli les lignes d'affichage pour le modem
***************************************************************************	*/
bool CEquipM1752::GetTestStringDX(string &ligne1, string &ligne2, string &ligne3, string &ligne4)
{
	bool test = TRUE;

	ligne1 = "LIAISON DE DONNEES";
	ligne2 = "EN PANNE";
	ligne3 = "";
	ligne4 = "";

	string dx;

	for (int i=1; i<5; i++)
	{
		dx = "D" + IntToString(i,1);
		ligne3 += dx;

		if (GetTest(dx))
		{
			ligne3 += " NOK  ";
			test = FALSE;
		}
		else
			ligne3 += " OK   ";

	}

	if (GetQuadrivoie())
		for (int i=5; i<9; i++)
		{
			dx = "D" + IntToString(i,1);
			ligne4 += dx;

			if (GetTest(dx))
			{
				ligne4 += " NOK  ";
				test = FALSE;
			}
			else
				ligne4 += " OK   ";
		}

	return test;
}

/* **************************************************************************
METHODE :		GetTestStringEEPROM()
TRAITEMENT:		Retourne TRUE si pas d'erreur et FALSE cas contraire
                Rempli les lignes d'affichage pour le modem
***************************************************************************	*/
bool CEquipM1752::GetTestStringEEPROM(string &ligne1, string &ligne2)
{
	if (!GetTest("EEPROM"))
		return TRUE;

	ligne1 = "SAUVEGARDE CONFIGURATION";
	ligne2 = "EN PANNE";

	return FALSE;
}

bool CEquipM1752::IsModif()
{
	return this->modif;
}

void CEquipM1752::SetModif(const bool modif)
{
	this->modif = modif;
}

/* **************************************************************************
METHODE :		GetVoieSelect()
TRAITEMENT:		Retourne l'indice de la voie selectionnée dans la vue ops
***************************************************************************	*/
int CEquipM1752::GetVoieSelect()
{
	return this->voie_select;
}

/* **************************************************************************
METHODE :		SetVoieSelect()
TRAITEMENT:		Change l'indice de la voie selectionnée dans la vue ops
***************************************************************************	*/
void CEquipM1752::SetVoieSelect(const int indice)
{
	this->voie_select = indice;
}

bool CEquipM1752::IsEnTest()
{
	return this->equip_en_test;
}

void CEquipM1752::StartTest()
{
	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		// Suivant la voie testé on passe ou pas l'eqp complet en test
		if (this->test_progress == "TIROIR")
			this->equip_en_test = TRUE;

		// Stopper les appels en cours
		if (this->test_progress == "CARTE_A" || this->test_progress == "TIROIR")
			FinAppel("A1");
		if (this->test_progress == "CARTE_B" || this->test_progress == "TIROIR")
			FinAppel("B1");
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);
}

void CEquipM1752::StopTest()
{
	((CProtoTRC1752*)proto)->SignalAUT();

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		this->equip_en_test = FALSE;
		this->test_progress = "";
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	// TODO A la fin d'un autotest passage en mode local ?????
	//ReinitModem();
}

string CEquipM1752::GetTestProgress()
{
	return this->test_progress;
}

void CEquipM1752::SetTestProgress(const string test)
{
	this->test_progress = test;
}

bool CEquipM1752::ValidTestProgress(const string test)
{
	if (test == "TIROIR" || test == "CARTE_A" || test == "CARTE_B") return TRUE;

	return FALSE;
}

bool CEquipM1752::ValidTestProgressVersion(const string test)
{
	if (test == "CARTE_B")
	{
		if (quadrivoie == false) return FALSE;
	}

	return TRUE;
}

void CEquipM1752::ReinitModem()
{
	int i;

	FinAppel("A1");
	FinAppel("B1");
	SetMode(FALSE, FALSE);				//RAZ de la case à cocher "Distante"
	// TODO on arrete les voies etc...
	for (int i=0; i<NB_CHANNELS; i++)
	{
		SetChannelState(CHANNELS[i], "INACTIVE");
		SetChannelTest(CHANNELS[i], DEFAULT_STRING_VALUE);
		SetChannelReserve(CHANNELS[i], FALSE);
		SetChannelEmissionEncours(CHANNELS[i], FALSE);
		SetChannelEmissionStatus(CHANNELS[i], "INACTIF");
		SetChannelReceptionStatus(CHANNELS[i], "INACTIF");
	}

	for (i=0; i<NB_ALE_PARAMETERS; i++)
	{
		TAleParameter ale = GetAleParameter(ALE_PARAMETERS[i]);
		ale.ale_status = DEFAULT_STRING_VALUE;
		ale.index_channel_in_scanset = 0;
		ale.sounding_index = 0;
		SetAleParameter(ALE_PARAMETERS[i], ale);

		// Recharge les tables de la mémoire 1 de chaque voie
		SelectionMemoire(ALE_PARAMETERS[i], "1");
	}


}

//******************
//Gestion Pilote
//******************
bool CEquipM1752::GetPilExt()
{
	return this->PilExt;
}

void CEquipM1752::SetPilExt(const bool etat)
{
	this->PilExt = etat;

}

//******************
//Gestion ZTS
//******************
bool CEquipM1752::GetZtsPft()
{
	return this->ZtsPft;
}

void CEquipM1752::SetZtsPft(const bool etat)
{
	this->ZtsPft = etat;

}

//******************
//Gestion FFT1302
//******************
bool CEquipM1752::GetFft1302()
{
	return this->Fft1302;
}

void CEquipM1752::SetFft1302(const bool etat)
{
	this->Fft1302 = etat;

}



// Test Activation Voie
CString CEquipM1752::TestActivation(const string voie)
{
	CString res;
	res.Empty();

	string dataLink		= GetChannelDataLinkId(voie);						//Interface Data : D1, D2....
	string dataLinkAss	= GetDataLinkAssociatedConfiguration(dataLink);		//Configuration Interface : CI0, CI1...
	string dataConfAss	= GetChannelAssociatedAfConfiguration(voie);		//Configuration Radio : CA, CB.....


	TInterfaceConfiguration conf_courante_data	= GetInterfaceConfiguration(dataLinkAss);
	TChannelConfiguration conf_courante_radio	= GetChannelConfiguration(dataConfAss);

	// MAE - page 81/124 - SYNCHRONE
	if (conf_courante_data.type == "SYNCHRONE" && conf_courante_radio.waveform != "TRANSP")
	{
		// Emission
		if (conf_courante_data.transmission_baudrate != 0)	//AUTO
			if (conf_courante_data.transmission_baudrate != conf_courante_radio.af_transmission_baudrate)
				res = "LIAISON SERIE SYNCHRONE CORRECTION DU DEBIT";

		// Réception
		if (conf_courante_data.reception_baudrate != 0)		//AUTO
			if (conf_courante_data.reception_baudrate != conf_courante_radio.af_reception_baudrate)
				res = "LIAISON SERIE SYNCHRONE CORRECTION DU DEBIT";
	}

	// MAE - page 81/124 - ASYNCHRONE
	if (conf_courante_data.type == "ASYNCHRONE")
	{
		// MAE - page 81/124
		if (conf_courante_data.reception_baudrate < conf_courante_radio.af_reception_baudrate)
		{
			if ( ((conf_courante_data.transmission_baudrate == 50
					|| conf_courante_data.transmission_baudrate == 100
					|| conf_courante_data.transmission_baudrate == 200)
						&& (conf_courante_radio.waveform != "BFSK" || conf_courante_radio.waveform != "FSKV" || conf_courante_radio.waveform != "FSKP"))
				|| conf_courante_data.transmission_baudrate == 800)
					res = "INCOHERENCE DEBIT DEBIT L.SERIE A CORRIGER";
				else
					res = "INCOHERENCE DEBIT BAISSE DU DEBIT RADIO";
		}

		// MAE - page 82/124
		if (conf_courante_data.transmission_baudrate > conf_courante_radio.af_transmission_baudrate)
		{
			res = "INCOHERENCE DEBIT ACTIVATION CTRL DE FLUX";
		}
		if (conf_courante_data.reception_baudrate > conf_courante_radio.af_reception_baudrate)
		{
			res = "INCOHERENCE DEBIT ACTIVATION CTRL DE FLUX";
		}
	}

	// MAE - page 82/124 - DPE
	if (conf_courante_radio.direction == "HD" && conf_courante_data.handshake != "DPE")
	{
		res = "INCOHERENCE DPE ACTIVATION GESTION DPE";
		conf_courante_data.handshake = "ON";
		SetInterfaceConfiguration(dataLinkAss, conf_courante_data);

	}

	// MAE - page 82/124 - Interface TD
	if (GetChannelType(voie) == "-" )
	{
		if ( ( voie == "A1" || voie == "B1" || voie == "B2") && ( GetChannelState("A2") == "ACTIVE" && dataLinkAss == GetDataLinkAssociatedConfiguration(GetChannelDataLinkId("A2"))))
			res = "INCOHERENCE L. SERIE UTILISEZ UNE AUTRE L.S.";

		if ( ( voie == "A2" || voie == "B1" || voie == "B2") && ( GetChannelState("A1") == "ACTIVE" && dataLinkAss == GetDataLinkAssociatedConfiguration(GetChannelDataLinkId("A1"))))
			res = "INCOHERENCE L. SERIE UTILISEZ UNE AUTRE L.S.";

		if ( ( voie == "B1" || voie == "A1" || voie == "A2") && ( GetChannelState("B2") == "ACTIVE" && dataLinkAss == GetDataLinkAssociatedConfiguration(GetChannelDataLinkId("B2"))))
			res = "INCOHERENCE L. SERIE UTILISEZ UNE AUTRE L.S.";

		if ( ( voie == "B2" || voie == "A1" || voie == "A2") && ( GetChannelState("B1") == "ACTIVE" && dataLinkAss == GetDataLinkAssociatedConfiguration(GetChannelDataLinkId("B1"))))
			res = "INCOHERENCE L. SERIE UTILISEZ UNE AUTRE L.S.";
	}


	if (GetChannelType(voie) != "-" )
	{
		if (   (voie == "A1" && GetChannelState("A1") != "ACTIVE" && IsChannelFree("A2") == FALSE)
			|| (voie == "B1" && GetChannelState("B1") != "ACTIVE" && IsChannelFree("B2") == FALSE) )
		{
			res = "INCOHERENCE L. SERIE UTILISEZ UNE AUTRE L.S.";
		}
	}

	// MAE - page 82/124 - En diversite, la deuxieme voie doit etre libre (T2-54)
	if (conf_courante_radio.diversity == "AVEC")
	{
		if (   (voie == "A1" && IsChannelFree("A2") == FALSE)
			|| (voie == "A2" && IsChannelFree("A1") == FALSE)
			|| (voie == "B1" && IsChannelFree("B2") == FALSE)
			|| (voie == "B2" && IsChannelFree("B1") == FALSE) )
		{
			res = "INCOHERENCE L. SERIE UTILISEZ UNE AUTRE L.S.";
		}
	}

	// MAE - page 83/124 - Coherence des tables en ALE
	if(GetChannelType(voie) != "-")
	{
		// On verifie la presence de la table RCH
		if (IsRchPresent(voie) == FALSE)
		{
			res = "PROBLEME AVEC LA TABLE ALE : RCH";
		}
	}

	return res;
}

void CEquipM1752::VueOps(const string voie)
{
	if (GetChannelState(voie) == "ACTIVE")
		((CDlgTRC1752*)ihm)->AffichageOps();
}

void CEquipM1752::VueTst(const int voie)
{
	((CDlgTRC1752*)ihm)->AffichageTst(voie);
}

void CEquipM1752::VueAutotest(const string type_erreur)
{
	((CDlgTRC1752*)ihm)->AffichageAutotest(type_erreur);
}

void CEquipM1752::SetAutotestMessage(string *l1, string *l2, string *l3, string *l4)
{
	((CDlgTRC1752*)ihm)->AffichageAutotest(l1,l2,l3,l4);
}

//
void CEquipM1752::AffichageTestCartes(const string nomvoie)
{
	((CDlgTRC1752*)ihm)->AffichageTestCarte(nomvoie);
}

//**************************
// Gestion de l'émission Off
//**************************
void CEquipM1752::EmissionOff(const string id)
{
	SetChannelEmissionEncours(id, FALSE);
}

//*************************
// Gestion de l'émission On
//*************************
void CEquipM1752::EmissionOn(const string id)
{
	SetChannelEmissionEncours(id, TRUE);
}

//*************************************************
// Emission d'un message en ALE une fois LKD ou LKG
//*************************************************
void CEquipM1752::SetEmissionMsg(const string id, const bool value)
{
	channels[id].emissionMessage = value;
}

bool CEquipM1752::GetEmissionMsg(const string id)
{
	return channels[id].emissionMessage;
}

//*************
// Réception Up
//*************
void CEquipM1752::SetReceptionUp(const string voie)
{
	for (int i = GetChannelAfLevelReceived(voie); i<=-1; i++)
	{
		SetChannelAfLevelReceived(voie, i);
		SetChannelReceptionStatus(voie, i);
	}

	SetChannelQualityValue(voie, 31);
}

//***************
// Réception Down
//***************
void CEquipM1752::SetReceptionDown(const string voie)
{
	for (int i = GetChannelAfLevelReceived(voie); i>=-30; i--)
	{
		SetChannelAfLevelReceived(voie, i);
		SetChannelReceptionStatus(voie, i, -1);
	}

	SetChannelQualityValue(voie, 0);
}

void CEquipM1752::SetReceptionOn(const string voie)
{
	SetChannelAfLevelReceived(voie, -30);
	SetChannelReceptionStatus(voie, -30);
	SetChannelQualityValue(voie, 31);
}
void CEquipM1752::SetReceptionOff(const string voie)
{
	SetChannelAfLevelReceived(voie, -30);
	SetChannelReceptionStatus(voie, -30);
	SetChannelQualityValue(voie, 0);
}

//********************************
// Nom de l'esclave ( diversité )
//********************************

void CEquipM1752::SetNameSlave(CString str)
{
Name_Slave=str;
}

CString CEquipM1752::GetNameSlave()
{
return Name_Slave;
}


//*****************
// Test Carte A / B
//*****************

void CEquipM1752::SetTestCarte(bool val)
{
	equip_test_carte=val;
}

bool CEquipM1752::GetTestCarte()
{
	return equip_test_carte;
}

//*****************
// FDI - 201202
//*****************
void CEquipM1752::SendRadEmiRnr(const string id)
{
	if (id == "A1")
		((CProtoTRC1752*)proto)->SignalRAD("IA3","RNR");

	if (id == "B1")
		((CProtoTRC1752*)proto)->SignalRAD("IA5","RNR");

}

//*****************
// FDI - RecMil
//*****************

bool CEquipM1752::GetRecMil()
{
	return RecMil;
}

void CEquipM1752::SetRecMil(const bool etat)
{
	RecMil = etat;
}


//*****************
// FDI - 201509
//*****************
bool CEquipM1752::IsStatus(const string l_cntx)
{
		if (l_cntx.substr(5, 1) == "0")
			return FALSE;
		else
			return TRUE;
}
