/*************************************************************************
FICHIER :	EquipM1752.h				 AUTEUR : PhB
DATE DE CREATION : 						 DERNIERE MODIFICATION : 24/01/11
VERSION :	1.0
ROLE :		Implémentation de la classe CProtoTRC1752
***************************************************************************	*/

#if !defined(AFX_EQUIPM1752_H__C0073A2F_AFAA_4C30_9020_DC3AE7B14513__INCLUDED_)
#define AFX_EQUIPM1752_H__C0073A2F_AFAA_4C30_9020_DC3AE7B14513__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equip.h"
#include <windows.h>
#include "Equip\AppelAle.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

#define NB_TESTS 31 
#define NB_CHANNELS 4 // A1..B2
#define NB_ALE_PARAMETERS 2 // A1/B1
#define NB_CHANNELS_CONFIGURATIONS 31 // CA..CZ/MC1..MC4
#define NB_INTERFACES_CONFIGURATIONS 10 // CI0..CI9
#define NB_DATA_LINK_IDS 5 // D1,D2,D5,D6,INT
#define NB_AUX_INTERFACES_CONFIGURATIONS 4 //IA3..IA6
#define NB_AF_CHANNELS_CONFIGURATIONS 4 // BF1..BF4
#define NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS 5 // TC1..TC4+TC

// Taille des tables
#define NB_LT_KEY 31
#define NB_SAD 20
#define NB_STA 100
#define NB_NET 20
#define NB_NET_ADDRESS 51
#define NB_SST 10
#define NB_RCH 100
#define NB_LIST_CHANNEL 101

#define NB_ERREURS 309

#define DEFAULT_INT_VALUE -8000
#define DEFAULT_STRING_VALUE ""

#define TPS_TEST 5000
#define TPS_TEST_INIT 20000	//15000

//#define NB_MAX_PARAMS 100 // nombre max de params dispos sur une ligne

const string TESTS[NB_TESTS] = {
	"TIROIR",
	"EEPROM",
	"IntA1",
	"IntA2",
	"IntB1",
	"IntB2",
	"A1",
	"A2",
	"B1",
	"B2",
	"TC",
	"TC1",
	"TC2",
	"TC3",
	"TC4",
	"D1",
	"D2",
	"D3",
	"D4",
	"D5",
	"D6",
	"D7",
	"D8",
	"IA3",
	"IA4",
	"IA5",
	"IA6",
	"103-104",
	"105-106",
	"107-108",
	"113-114"
};

const string CHANNELS[NB_CHANNELS] = {
	"A1",
	"A2",
	"B1",
	"B2"
};

const string ALE_PARAMETERS[NB_ALE_PARAMETERS] = {
	"A1",
	"B1"
};

const string CHANNELS_CONFIGURATION[NB_CHANNELS_CONFIGURATIONS] = {
	"CA",
	"CB",
	"CC",
	"CD",
	"CE",
	"CF",
	"CG",
	"CH",	
	"CI",
	"CJ",
	"CK",	
	"CL",
	"CM",
	"CN",	
	"CO",
	"CP",
	"CQ",
	"CR",
	"CS",
	"CT",
	"CU",
	"CV",
	"CW",
	"CX",
	"CY",
	"CZ",
	"A1",
	"A2",
	"B1",
	"B2"
};

const string INTERFACES_CONFIGURATION[NB_INTERFACES_CONFIGURATIONS] = {
	"CI0",
	"CI1",
	"CI2",
	"CI3",
	"CI4",
	"CI5",
	"CI6",
	"CI7",
	"CI8",
	"CI9"
};

const string DATA_LINK_IDS[NB_DATA_LINK_IDS] = {
	"D1",
	"D2",
	"D5",
	"D6",
	"INT"
};


const string AUX_INTERFACES_CONFIGURATIONS[NB_AUX_INTERFACES_CONFIGURATIONS] = {
	"IA3",
	"IA4",
	"IA5",
	"IA6"
};

const string AF_CHANNELS_CONFIGURATIONS[NB_AF_CHANNELS_CONFIGURATIONS] = {
	"BF1",
	"BF2",
	"BF3",
	"BF4"
};

const string LOCAL_REMOTE_INTERFACES_CONFIGURATIONS[NB_LOCAL_REMOTE_INTERFACES_CONFIGURATIONS] = {
	"TC1",
	"TC2",
	"TC3",
	"TC4",
	"TC"
};

/* Definition types struct */
typedef struct
{ // DVM
	string waveform;						// 4285...
	string diversity;						// AVEC/SANS
	string direction;						// TX,RX,HD,FD
	int af_transmission_baudrate;			// 1200, 2400.../ 0 = auto
	string af_transmission_codingtype;		// SANS, CODE, PHONIE
	string af_transmission_interleaving;	// SANS, COURT, LONG
	int transmission_carrier_frequency; 
	int transmission_space_frequency;
	int transmission_mark_frequency;
	int af_reception_baudrate;				// 1200, 2400 .../ 0 = auto
	string af_reception_codingtype;			// SANS, CODE, PHONIE
	string af_reception_interleaving;		// SANS, COURT, LONG
	int reception_carrier_frequency;
	int reception_space_frequency;
	int reception_mark_frequency;
	int slave_baudrate;						// 1200, 2400 .../ 0 = auto
	string slave_codingtype;				// SANS, CODE, PHONIE
	string slave_interleaving;				// SANS, COURT, LONG
	int slave_carrier_frequency;
	string slave_direction;					// RX / FD
	string use_data;						// AVEC / SANS

} TChannelConfiguration;

typedef struct
{// DID
	string type;						// SYNCHRONE / ASYNCHRONE
	string electrical_characteristics;	// V10, V11...
	int transmission_baudrate;			// 0 = AUTO
	int reception_baudrate;				// 0 = AUTO
	string direction;					// ENTRANTE/SORTANTE/SANS
	string validity_time;				// 01H/24H
	string binary_integrity;			// PETITE/GRANDE
	string polarity;					// NORMALE/INVERSEE
	string handshake;					// DPE/ENTETE/OFF
	int character_length;				// 5...8
	string parity;						// PAIR/IMPAIR/SANS
	int number_stop_bits;				// 1/2
	string data_flow_control;			// XON/PAE

} TInterfaceConfiguration;

typedef struct
{
	string associated_configuration_id; // CI0..CI9
	string test_progress;				// INTERNE,EXTERNE ou vide
} TDataLink;

typedef struct
{// DIA
	string electrical_characteristics;	// V28, V11...
	int baudrate; 
	int character_length;				// 7 / 8
	string character_parity;			// PAIR,IMPAIR,SANS
	int number_stop_bits;				// 1/2
	int radio_address;					// 000...999
	string equipment_type;				// NORAD...
	string test_progress;				// INTERNE,EXTERNE ou vide
} TAuxInterfaceConfiguration;

typedef struct
{// DTC
	string electrical_characteristics;	// V28, V11...
	int baudrate;
	int characters_length;				// 7 / 8
	string characters_parity;			// PAIR,IMPAIR,SANS
	int number_stop_bits;				// 1/2
} TLocalRemoteInterfaceConfiguration;

typedef struct
{// DBF
	int input_level;				// 00/18
	int output_level;				// -30/+10
	string interface_type;			// SYMETRIQUE/ASYMETRIQUE
	string ptt_type;				// TTL/COL_OUV/COL_OUV_M
	int ptt_tempo;					// 0000...9999
	string mute_characteristics;	// TTL/COL_OUV/COL_OUV_M
	int mute_delay;					// 0000...5000
	int radio_delay;				// 0000...9999
} TAFChannelConfiguration;

typedef struct
{
	string state;						// ACTIVE / INACTIVE
	string status_local_remote_control; // LOCAL / MAIN

	string associated_af_configuration; // CA..CZ/MC
	string data_link_id;				// D1..D6/INT
	string type;						// -,S,C
	int index_scanset_channel;			// 00..99
	string link_management_type;		// LMANU,LAUTO

	int quality_value;				// 00..31
	int af_level_received;			// -30..+10
	int offset_af_output_level;		// -30..+10
	int af_level_received_slave;	// -30..+10
	int dopple_offset;				// -200..+200
	int signal_noise_ratio;			// -30..99

	string direction_transmission;			// EMISSION/RECEPTION
	int offset_carrier_frequency;			// -200..+200
	int offset_mark_frequency;				// -200..+200
	int offset_space_frequency;				// -200..+200

	bool master_diversity;			// voie maitre en diversité
	string test_progress;			// 1800HZ,BOUCLE_BF ou vide
	bool reserve;					// TRUE si reserve en ale

	bool emission_encours;			// True si émission demandée
	string emission_status;			// INACTIF/DEBUT/EN_COURS/FIN
	string reception_status;		// INACTIF/DEBUT/EN_COURS/FIN
	
	bool emissionMessage;			// TRUE si demande d'émission d'un message en ALE

} TChannel;

typedef struct
{
	string capabilities;
	string number;
	string release;
	string day;
	string month;
	string year;

	string date_and_time;		// jj/mm/aa.hhHmm.ss
	int time_accuracy;			// 00000...60000
	string date_origin;			// GPS/MRC/DEM
	string last_date_and_time;	// jj/mm/aa.hhHmm.ss
	int time_lag;				// -60000...+60000
} TBoard;

struct TRch {
	int channel;		// 000..999
	int tx_freq;		// 01500000..30000000
	int rx_freq;		// 01500000..30000000
	string mode_tx;		// USB/LSB/ISB
	string mode_rx;		// USB/LSB/ISB
	int bfo;			// -7990..+7990
	int filter;			// 000..009
	int agc;			// 0..3
	int squelch;		// -128..+063
	int pwr;			// -50..0
	string ed;			// ON/OFF
	int sound_interv;	// 0000..1439
	int self_add;		// 00..19

	TRch()
	{
		channel = DEFAULT_INT_VALUE;
		tx_freq = DEFAULT_INT_VALUE;
		rx_freq = DEFAULT_INT_VALUE;
		mode_tx = DEFAULT_STRING_VALUE;
		mode_rx = DEFAULT_STRING_VALUE;
		bfo		= DEFAULT_INT_VALUE;
		filter	= DEFAULT_INT_VALUE;
		agc		= DEFAULT_INT_VALUE;
		squelch = DEFAULT_INT_VALUE;
		pwr		= DEFAULT_INT_VALUE;
		ed		= DEFAULT_STRING_VALUE;
		sound_interv	= 0;
		self_add		= DEFAULT_INT_VALUE;
	}
};

struct TSad {
	string self_address;	// 1..15 car
	int net_address;		// 00..19
	int slot;				// 01..50
	bool valid_channels[NB_LIST_CHANNEL]; // 0..399 car (ALL <=> 100)

	TSad()
	{
		self_address	= DEFAULT_STRING_VALUE;
		net_address		= DEFAULT_INT_VALUE;
		slot			= DEFAULT_INT_VALUE;
		for(int i=0; i<NB_LIST_CHANNEL; i++)
			valid_channels[i]=FALSE;
	}
};

struct TNet {
	string net_address;				// 1..15 car
	int net_member[NB_NET_ADDRESS]; // 00..99 tableau commence a 1 fini a 50

	TNet()
	{
		net_address = DEFAULT_STRING_VALUE;
		for(int i=0; i<NB_NET_ADDRESS; i++)
			net_member[i] = DEFAULT_INT_VALUE;
	}
};

struct TSta {
	string address_ale; // 1..15 car
	string address_arq; // 1..7 car
	int twr;			// 00131..99999
	bool valid_channels[NB_LIST_CHANNEL]; // 0..399 car (ALL <=> 100)

	TSta()
	{
		address_ale = DEFAULT_STRING_VALUE;
		address_arq = DEFAULT_STRING_VALUE;
		twr = 2000;
		for(int i=0; i<NB_LIST_CHANNEL; i++)
			valid_channels[i]=FALSE;
	}
} ;

struct TSst {
	bool scan_set_channel[NB_LIST_CHANNEL]; // 0..399 car

	TSst() 
	{
		for (int i=0; i<NB_LIST_CHANNEL; i++)
			scan_set_channel[i] = FALSE;
	}
};

struct TTableLT {
	string name;					// 000,J05...
	bool key[NB_LT_KEY];			// 0..30

	TTableLT() 
	{
		name = DEFAULT_STRING_VALUE;
		for (int i=0; i<NB_LT_KEY; i++)
			key[i] = FALSE;
	}
};

struct TTable {
	TSad sad[NB_SAD];
	TRch rch[NB_RCH];
	TNet net[NB_NET];
	TSta sta[NB_STA];
	TSst sst[NB_SST];
	TTableLT lt0;
	TTableLT lt1;
	bool sad_present;
	bool rch_present;
	bool net_present;
	bool sta_present;
	bool sst_present;

	TTable () 
	{
		sad_present = FALSE;
		rch_present = FALSE;
		net_present = FALSE;
		sta_present = FALSE;
		sst_present = FALSE;
	}
};

typedef struct
{ // DSP
	string automatic_sounding;			// ON/OFF
	int aging_percentage;				// 000...100
	string aging_time;					// 00.0...08.0
	string multiservice;				// ON/OFF
	string automatic_reconfiguration;	// ON/OFF
	int service_activation;				// 01...10
	string allcall_message;				// ON/OFF
	string wildcard_message;			// ON/OFF
	string anycall_message;				// ON/OFF
	string respond;						// ON/OFF
	int scanrate;						// 2/5
	int twa_automatic;					// 000...999
	int twa_manual;						// 000...999
	int twt;							// 0000...0099
	int tunetime_local;					// 0000...9999
	int tunetime_other;					// 0000...9999
	string ptt_gestion;					// WIRE/SERIAL
	int sound_length;					// 001...100 000=---=auto
	int retries_channel;				// 0...9
	int retries_scanfield;				// 0...9
	int long_sound_limit;				// 00...99

  // DCP
	string cms_choice;					// CHA/BST/LMF
	string ale_termination_frame;		// TIS/TAS
	int index_channel_table;			// 00...99
	int lowest_usable_frequency;		// 015000000...29999999
	int upper_usable_frequency;			// 015000000...29999999
	string call_type;					// STD/ANY/SAN.../SAL
	int index_selfaddress;				// 00...19
	string quick_identification;		// ON/OFF
	string quality_analysis;			// ON/OFF
	string station_network_group;		// S/N/G
	int called_address;					// 00...99
	string called_address_string;		// ??
	vector<int> index_station_table_group; // ??
	string agc;
	int call_length;	// 000...999
	string amd_message; // 90 chars
	
  // DLP
	int link_protection_level; // 0/1/2

  // AKT
	string key_management;	// FIX/24H
	//string lt0_table_name; // 000,J05...
	int key_position;		// 00...30 / -1 == vide

	//string lt1_table_name; // 000,J05...

  // STL
	string ale_status;				// SCA,LIS...
	int index_channel_in_scanset;	// 00..99

	bool appel_en_cours;

	int sounding_index; // 0 à 99

	bool est_appele;	// indique si on a été appelé ou on a appelé

} TAleParameter;

struct TModemDistant {
	bool marche;
	vector<string> selfaddress;
	int current_selfaddress;
	vector<string> LP;
	int current_LP;
	vector<string> LT0;
	int current_LT0;
	vector<string> Key;
	int current_Key;
	vector<string> stations;
	int current_station;
	vector<string> reseaux;
	int current_reseau;
	string type_appel; // ALL/NET/STA
	string type_ale; // S/C
	bool channel[10];
	string amd_chat;
	string amd_chat_recu;

	TModemDistant ()
	{
		marche = true;
		selfaddress.push_back("1TD614");
		selfaddress.push_back("1PD614");
		selfaddress.push_back("BAT003");
		selfaddress.push_back("BAT103");
		selfaddress.push_back("1TX920");
		current_selfaddress = 0;
		
		LP.push_back("0");
		LP.push_back("1");
		LP.push_back("2");
		current_LP = 1;
		
		LT0.push_back("K05");
		current_LT0 = 0;

		Key.push_back("01");
		Key.push_back("02");
		current_Key = 0;

		stations.push_back("1TD615");
		stations.push_back("1PD615");
		stations.push_back("1TF710");
		stations.push_back("1PF710");
		stations.push_back("1TF711");
		stations.push_back("1PF711");
		stations.push_back("BAT001");
		stations.push_back("BAT002");
		stations.push_back("BAT101");
		stations.push_back("BAT102");
		stations.push_back("1TX901");
		current_station = 0;

		reseaux.push_back("RES1");
		reseaux.push_back("RES2");
		reseaux.push_back("RES3");
		current_reseau = 0;

		type_appel	= "STA";
		type_ale	= "S";
		for(int i=0; i<10; i++) channel[i] = FALSE;
		amd_chat = "";
		amd_chat_recu = "";
	}
};

struct TPCArq {
	string fonction;			// TRANS/NO ALE/ALE/NO PIL
	string etat;
	string modulation;			// 4285 / MIL110A
	string adaptabilite;		// AVEC/SANS
	string debit;				// 150,300,600,1200,2400
	string codage;				// COURT/LONG
	
	vector<string> adresses_locales;
	vector<string> adresses_destinataires;
	int current_adresse_locale;
	int current_adresse_destinataire;
	bool active;
	bool etabli;
	bool sachem;				// la voie sachem est à false (fermée) par défaut
	bool arqdebrec;

	TPCArq () 
	{
		fonction		= "TRANS";
		etat			= "INACTIF";
		modulation		= "4285";
		adaptabilite	= "AVEC";
		debit			= "0300";
		codage			= "COURT";

		adresses_locales.push_back("1TD615");
		//adresses_locales.push_back("1TD614");
		adresses_destinataires.push_back("1TF710");
		adresses_destinataires.push_back("1TF711");
		adresses_destinataires.push_back("1TD614");

		current_adresse_locale			= 0;
		current_adresse_destinataire	= 1;
		active = FALSE;
		etabli = FALSE;

		// FDI - Voie SACHEM
		sachem = FALSE;
		// FDI - 201202
		arqdebrec = FALSE;
	}
};

typedef struct
{
	string code;
	string erreur;

} TErreur;

typedef map<string, TChannelConfiguration> TMapChannelConfiguration;
typedef map<string, TInterfaceConfiguration> TMapInterfaceConfiguration;
typedef map<string, TAuxInterfaceConfiguration> TMapAuxInterfaceConfiguration;
typedef map<string, TLocalRemoteInterfaceConfiguration> TMapLocalRemoteInterfaceConfiguration;
typedef map<string, TAFChannelConfiguration> TMapAFChannelConfiguration;
typedef map<string, TChannel> TMapChannel;
typedef map<string, TDataLink> TMapDataLink;
typedef map<string, TAleParameter> TMapAleParameter;
typedef map<string, TTable> TMapTable;
typedef map<string, TPCArq> TMapPcArq;

typedef map<string, bool> TMapTest;

class CAppelAle;

int ExtractData(istringstream &data, string res[], int length, char sep = ';');
string IntToString(int value, int size, bool sign = FALSE);

class CEquipM1752:public CEquip  
{
private: 
	unsigned short crc_ccitt(unsigned char data, unsigned short crc);

protected:
//Thread appel
	CAppelAle * appel_A;
	CAppelAle * appel_B;

// Donnees internes
	TMapChannelConfiguration channels_configurations;								// CA..CZ/A1..B2
	TMapInterfaceConfiguration interfaces_configurations;							// CI0..CI9
	TMapDataLink data_links;														// D1..INT
	TMapAuxInterfaceConfiguration aux_interfaces_configurations;					// IA3..IA6
	TMapLocalRemoteInterfaceConfiguration local_remote_interfaces_configurations;	// TC1..TC4+TC
	TMapAFChannelConfiguration af_channels_configurations;							// BF1..BF4

    TMapChannel channels;			// A1..B2

	TMapAleParameter ale_parameter; // A1/B1

	TMapTable table;			// listing des tables chargées A1/B1
	TMapTable table_stored1;	// listing des tables en memoire 1 A1/B1
	TMapTable table_stored2;	// listing des tables en memoire 2 A1/B1

	TMapPcArq pc_arq;		// A1/B1

	bool mode;				// false=local / true=distant

	string clock_pilot;		// INTERNE / EXTERNE
	bool PilExt;			//true=Autosisé sinon interdit

	// FDI - ZTS
	bool ZtsPft;			// false = ZTS non généré sur PFT

	// FDI - Bug FFT_1302
	bool Fft1302;			// false le modem fonctionne normalement

	// FDI - MIL110
	bool RecMil;

	string inr;				// AVEC/SANS
	int inr_rate;			// 1..100 (unité = 100ms)

	string gic;				// 0000
	string origine_heure;	// DEM/MRC/GPS

	// configuration modem distant en ale
	TModemDistant distant;

	// conf interne
	string manufacturer;
	string identity;
	TBoard board_management;
	TBoard board_1;
	TBoard board_2;
	bool quadrivoie;		// 4 voies ou 2 voies

	// Configuration emetteur/recepteur
	bool emetteur_marche;
	bool emetteur_panne_majeure;
	bool emetteur_panne_tc;
	bool recepteur_marche;
	bool recepteur_panne_majeure;
	bool recepteur_panne_tc;
	// TODO
	bool emetteur_emission;

	// Configuration des résultats de tests et pannes
	TMapTest test_map;

	// bidouille interne
	bool modif;				// Champ permettant de savoir si des modifs sont en cours
	int voie_select;		// indice de la voie selectionnée dans la vue ops
	string test_progress;	// TIROIR,CARTE_A,CARTE_B ou vide
	bool equip_en_test;		// valeur globale indiquant si un test se déroule

	int panne;				// panne global du modem nécessitant un redémarrage

	CString Name_Slave;		//nom du modem esclave en diversité

	bool equip_test_carte;	//test de carte A ou B 
	
public:
	TErreur erreurs[NB_ERREURS];

	CEquipM1752(int idx);

	virtual ~CEquipM1752();
	
	void	Allocation();

	BOOL Power();

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

	void DesactiveVoie(string voie);

	void CreerAppel(string voie);
	void LancerAppel(string voie);
	void LancerReceptionAppel(string voie);
	void CasserAppel(string voie);
	void FinAppel(string voie);
	void EnvoyerAmd(string voie);
	void RecevoirAmd(string voie);
	void Sound(string voie);

	int LancerTestVoie(const string voie, const string test);
	int ArreterTestVoie(const string voie);

	int Activer(string voie);
	int Desactiver(string voie);
	int DefinitionArq(const string voie, const string fct_arq, 
						const string modulation, const int adr_loc, const int adr_dist);
	int ModificationArq(const string voie, const string debit, const string entrelacement);

	void SetAppel(const string voie, const bool val);
	bool IsAppel(const string voie);

	int EffacementUrgence();
	int SelectionMemoire(const string channel, const string num);
	int EffacementMemoire(const string channel, const string num);
	int EcritureMemoire(const string channel, const string num);

	void RazIntegrite();

	void SendINR();
	void SendINT(const string id);
	void SendTSP(const string id);

	void SendPAO(const string channel, const string direction);

	void SendLKL(const string channel, const string erreur);

	bool ValidChannelId(const string id);
	bool ValidChannelVersion(const string id);
	string GetAfChannelFromModemChannel(const string channel);
	string GetModemChannelFromAfChannel(const string af_channel);

	bool ValidDataLinkId(const string id);
	bool ValidDataLinkVersion(const string id);
	bool IsDataLinkUsed(const string id);
	string GetChannelFromDataLink(const string data);
	string GetChannelAssociated(const string id);

	string GetDataLinkAssociatedConfiguration(const string id);
	void SetDataLinkAssociatedConfiguration(const string id, const string value);
	bool ValidDataLinkAssociatedConfiguration(const string value);
	string GetDataLinkTest(const string id);
	string GetDataLinkFromChannel(const string data);

	bool IsChannelFree(const string id);
	bool IsChannelAleReserved(const string id);

	string GetChannelState(const string id);
	string GetChannelStateIhm(const string id);
	void SetChannelState(const string id, const string state);
	bool ValidChannelState(const string state);

	string GetChannelLocalRemoteControl(const string id);
	void SetChannelLocalRemoteControl(const string id, const string value);
	bool ValidChannelLocalRemoteControl(const string value);

	string GetChannelAssociatedAfConfiguration(const string id);
	string GetChannelAssociatedAfConfigurationConverted(const string id);
	void SetChannelAssociatedAfConfiguration(const string id, const string value);
	void SetChannelAssociatedAfConfigurationModified(const string id);
	bool ValidChannelAssociatedAfConfiguration(const string value);

	string GetChannelDataLinkId(const string id);
	void SetChannelDataLinkId(const string id, const string value);
	bool ValidChannelDataLinkId(const string value);

	string GetChannelType(const string id);
	void SetChannelType(const string id, const string value);
	bool ValidChannelType(const string value);

	int GetChannelIndexScansetChannel(const string id);
	void SetChannelIndexScansetChannel(const string id, const int value);
	bool ValidChannelIndexScansetChannel(const int value);

	string GetChannelLinkManagementType(const string id);
	void SetChannelLinkManagementType(const string id, const string value);
	bool ValidChannelLinkManagementType(const string value);
	string GetChannelLinkManagementTypeIhm(const string id);
	void SetChannelLinkManagementTypeIhm(const string id, const string value);

	int GetChannelQualityValue(const string id);
	void SetChannelQualityValue(const string id, const int value);
	int GetChannelAfLevelReceived(const string id);
	void SetChannelAfLevelReceived(const string id, const int value);
	int GetChannelAfLevelOutput(const string id);
	void SetChannelAfLevelOutput(const string id, const int value);
	int GetChannelAfLevelReceivedSlave(const string id);
	void SetChannelAfLevelReceivedSlave(const string id, const int value);
	int GetChannelDopplerOffset(const string id);
	void SetChannelDopplerOffset(const string id, const int value);
	int GetChannelSignalNoiseRation(const string id);
	void SetChannelSignalNoiseRation(const string id, const int value);

	void SetChannelDirectionTransmission(const string id, const string value);
	string GetChannelDirectionTransmission(const string id);
	bool ValidChannelDirectionTransmission(const string value);

	void SetChannelOffsetCarrierFrequency(const string id, const int value);
	int GetChannelOffsetCarrierFrequency(const string id);
	bool ValidChannelOffsetCarrierFrequency(const string value);

	void SetChannelOffsetMarkFrequency(const string id, const int value);
	int GetChannelOffsetMarkFrequency(const string id);

	void SetChannelOffsetSpaceFrequency(const string id, const int value);
	int GetChannelOffsetSpaceFrequency(const string id);

	bool GetChannelMasterDiversity(const string id);
	void SetChannelMasterDiversity(const string id, const bool value);

	string GetChannelTest(const string id);
	void SetChannelTest(const string id, const string test);
	bool ValidChannelTest(const string test);

	bool IsChannelReserve(const string id);
	void SetChannelReserve(const string id, const bool val);

	string GetChannelReceptionStatus(const string id);
	void SetChannelReceptionStatus(const string id, const int val, int dir = 1);
	void SetChannelReceptionStatus(const string id, const string status);

	bool GetChannelEmissionEncours(const string id);
	void SetChannelEmissionEncours(const string id, bool status);

	string GetChannelEmissionStatus(const string id);
	void SetChannelEmissionStatus(const string id, const string status);

	TChannelConfiguration GetChannelConfiguration(const string id);
	void SetChannelConfiguration(const string id, const TChannelConfiguration conf);
	bool ValidChannelConfiguration(const string id);
	bool ValidChannelConfigurationVersion(const string id);
	bool ValidChannelConfigurationWaveform(const string waveform);
	bool ValidChannelConfigurationDiversity(const string &waveform, string &value);
	bool ValidChannelConfigurationDirection(const string &waveform, const string &diversity, string &direction);
	int ValidChannelConfigurationAfParameters(const string &waveform, string &baudrate, string &coding, 
								 string &interleaving, const bool reception = FALSE);
	bool ValidChannelConfigurationCarrierFrequency(const string &waveform, string &value);
	int ValidChannelConfigurationFrequency(const string &waveform, string &space, string &mark);
	bool ValidChannelConfigurationSlaveDirection(const string &waveform, string &direction);
	bool ValidChannelConfigurationUseData(const string &waveform, string &use);

	TAuxInterfaceConfiguration GetAuxInterfaceConfiguration(const string id);
	void SetAuxInterfaceConfiguration(const string id, const TAuxInterfaceConfiguration value);
	bool ValidAuxInterfaceConfiguration(const string id);
	bool ValidAuxInterfaceConfigurationVersion(const string id);
	string GetChannelFromAuxInterfaceConfiguration(const string aux_interface);
	bool ValidAuxInterfaceConfigurationElectricalCharacteristic(const string characteristic);
	bool ValidAuxInterfaceConfigurationBaudrate(const string baudrate);
	bool ValidAuxInterfaceConfigurationCharacterLength(const string length);
	bool ValidAuxInterfaceConfigurationCharacterParity(const string parity);
	bool ValidAuxInterfaceConfigurationNumberStopBit(const string number);
	bool ValidAuxInterfaceConfigurationRadioAddress(const string address);
	bool ValidAuxInterfaceConfigurationEquipmentType(const string id, const string type);

	TInterfaceConfiguration GetInterfaceConfiguration(const string id);
	void SetInterfaceConfiguration(const string id, const TInterfaceConfiguration conf);
	bool ValidInterfaceConfiguration(const string id);
	bool IsInterfaceConfigurationUsed(const string value);
	bool ValidInterfaceConfigurationType(const string type);
	bool ValidInterfaceConfigurationElectricalCharacteristic(const string type, const string carac);
	bool ValidInterfaceConfigurationBaudrate(const string type, const string direction, const string baudrate);
	bool ValidInterfaceConfigurationClockDirection(const string type, const string direction);
	bool ValidInterfaceConfigurationValidityTime(const string time);
	bool ValidInterfaceConfigurationBinaryIntegrity(const string integrity);
	bool ValidInterfaceConfigurationPolarity(const string polarity);
	bool ValidInterfaceConfigurationHandShake(const string handshake);
	bool ValidInterfaceConfigurationCharacterLength(const string type, const string length);
	bool ValidInterfaceConfigurationParity(const string type, const string parity);
	bool ValidInterfaceConfigurationNumberStopBits(const string type, const string number);
	bool ValidInterfaceConfigurationDataFlowControl(const string data_flow);

	TLocalRemoteInterfaceConfiguration GetLocalRemoteInterfaceConfiguration(const string id);
	string GetLocalRemoteInterfaceConfigurationFromChannel(const string id);
	void SetLocalRemoteInterfaceConfiguration(const string id, const TLocalRemoteInterfaceConfiguration value);
	bool ValidLocalRemoteInterfaceConfiguration(const string id);
	bool ValidLocalRemoteInterfaceConfigurationVersion(const string id);
	bool ValidLocalRemoteInterfaceConfigurationElectricalCharacteristic(const string characteristic);
	bool ValidLocalRemoteInterfaceConfigurationBaudrate(const string baudrate);
	bool ValidLocalRemoteInterfaceConfigurationCharacterLength(const string length);
	bool ValidLocalRemoteInterfaceConfigurationCharacterParity(const string parity);
	bool ValidLocalRemoteInterfaceConfigurationNumberStopBits(const string number);

	TAFChannelConfiguration GetAfChannelConfiguration(const string id);
	void SetAfChannelConfiguration(const string id, const TAFChannelConfiguration value);
	void SetAfChannelOutputLevel(const string id, const int value);
	bool ValidAfChannelConfiguration(const string id);
	bool ValidAfChannelConfigurationVersion(const string id);
	bool ValidAfChannelConfigurationInputLevel(const string level);
	bool ValidAfChannelConfigurationOutputLevel(const string level);
	bool ValidAfChannelConfigurationInterfaceType(const string type);
	bool ValidAfChannelConfigurationPttType(const string ptt);
	bool ValidAfChannelConfigurationPttTempo(const string tempo);
	bool ValidAfChannelConfigurationMuteSignal(const string mute);
	bool ValidAfChannelConfigurationMuteDelay(const string delay);
	bool ValidAfChannelConfigurationRadioDelay(const string delay);


	TAleParameter GetAleParameter(const string id);
	void SetAleParameter(const string id, const TAleParameter conf);
	int GetAleTwa(const string id);
	void SetAleChannelInScanset(const string id, const int index);
	int GetAleChannelInScanset(const string id);
	void SetAleStatus(const string id, const string state);
	string GetAleStatus(const string id);
	bool IsLink(const string id);
	bool ValidAleParameter(const string id);
	bool ValidAleParameterVersion(const string id);
	int GetAleLinkProtectionLevel(const string id);
	string GetAleKeyManagement(const string id);
	string GetAleSilence(const string id);
	int GetAleKeyPosition(const string id);
	void SetAleKeyPosition(const string id, int pos);
	int GetAleSoundIndex(const string id);
    void SetAleEstAppele(const string id, bool value);
    bool GetAleEstAppele(const string id);
	void ResetAleSoundIndex(const string id);
	int NextSound(const string id);

	bool ValidAleParameterOnOff(const string value);
	bool ValidAleParameterAgingPercentage(const string value);
	bool ValidAleParameterAgingTime(const string value);
	bool ValidAleParameterServiceActivation(const string value);
	bool ValidAleParameterScanRate(const string value);
	bool ValidAleParameterTwa(const string value);
	bool ValidAleParameterTwt(const string value);
	bool ValidAleParameterTuneTime(const string value);
	bool ValidAleParameterPttGestion(const string value);
	bool ValidAleParameterSoundLength(const string value);
	bool ValidAleParameterRetries(const string value);
	bool ValidAleParameterLongSoundLimit(const string value);

	bool ValidAleParameterCmsChoice(const string value);
	bool ValidAleParameterAleTerminationFrame(const string value);
	bool ValidAleParameterIndexChannelTable(const string value);
	bool ValidAleParameterUsableFrequency(const string value);
	bool ValidAleParameterCallType(const string value);
	bool ValidAleParameterIndexSelfAddress(const string value);
	bool ValidAleParameterStationNetworkGroup(const string value);
	bool ValidAleParameterCalledAddress(const string value);
	bool ValidAleParameterCalledAddressString(const string value);
	bool ValidAleParameterIndexStationTableGroup(const string value);
	bool ValidAleParameterAgc(const string value);
	bool ValidAleParameterCallLength(const string value);
	bool ValidAleParameterAmdMessage(const string value);

	bool ValidAleParameterLinkProtectionLevel(const string value);

	bool ValidAleParameterKeyPosition(const string value);
	bool ValidAleParameterKeyManagement(const string value);
	
	string GetTableLtName(const string id, const string table_name);
	bool ValidTableLT(const string id);
	bool ValidTableName(const string value);
	bool ValidTableType(const string value);
	bool ValidTableCRC(const string value);
	unsigned short CalculateCRC(const string data);
	TTableLT GetTableLT(const string id, const string table);
	void SetTableLT(const string id, const string table, const TTableLT value);
	void ActiveLT1(const string id);
	bool ValidTableAddress(const string value);
	bool ValidTableKey(const string value);
	bool ValidTableLt0(const string value);
	bool ExtractTableChannels(const string value, bool list[], bool all_autorized = TRUE);

	void AddRch(const string id, const int index, const TRch value);
	int ExtractTableRch(const string data[], TRch &rch);
	bool IsRchPresent(const string id, const int index);
	bool IsRchPresent(const string id);
	bool GetRch(const string id, const int index, TRch &value);
	int GetRchSoundDelay(const string id, const int index);
	void AddSad(const string id, const int index, const TSad value);
	int ExtractTableSad(const string data [], TSad &sad);
	bool IsSadPresent(const string id);
	bool GetSad(const string id, const int index, TSad &value);
	int GetSad(const string id, const string adr);
	void AddSta(const string id, const int index, const TSta value);
	int ExtractTableSta(const string data [], TSta &sta);
	bool IsStaPresent(const string id);
	bool GetSta(const string id, const int index, TSta &value);
	int GetSta(const string id, const string adr);
	void AddNet(const string id, const int index, const TNet value);
	int ExtractTableNet(const string data [], TNet &net);
	bool IsNetPresent(const string id, const int index);
	bool IsNetPresent(const string id);
	bool GetNet(const string id, const int index, TNet &value);
	int GetNet(const string id, const string adr);
	void AddSst(const string id, const int index, const TSst value);
	int ExtractTableSst(const string data [], TSst &sst);
	bool IsSstPresent(const string id, int index);
	bool IsSstPresent(const string id);
	bool GetSst(const string id, const int index, TSst &value);

	void WriteTable(const string id, const string position);
	void ReadTable(const string id, const string position);

	void DeleteSad(const string id);
	void DeleteRch(const string id);
	void DeleteNet(const string id);
	void DeleteSta(const string id);
	void DeleteSst(const string id);
	void DeleteLt0(const string id);
	void DeleteLt1(const string id);

	void DeleteTableStored(const string id, const string id_number);

	bool ValidTableSad(const string id);
	bool ValidTableSta(const string id);
	bool ValidTableNet(const string id);
	bool ValidTableSst(const string id);

	bool GetMode();
	void SetMode(const bool mode, bool signaling = FALSE);

	void SetGic(const string value);
	string GetGic(); 
	void SetOrigineHeure(const string value);
	string GetOrigineHeure();

	void SetModemDistant(const TModemDistant value);
	TModemDistant GetModemDistant();

	void SetPcArq(const string id, const TPCArq arq);
	TPCArq GetPcArq(const string id);

	string GetManufacturer();
	void SetManufacturer(const string manufacturer);

	string GetIdentity();
	void SetIdentity(const string identity);

	TBoard GetBoardManagement();
	void SetBoardManagement(const TBoard board);

	TBoard GetBoard1();
	void SetBoard1(const TBoard board);

	TBoard GetBoard2();
	void SetBoard2(const TBoard board);

	bool IsEmetteurMarche();
	void SetEmetteurMarche(const bool value);

	bool IsEmetteurPanneMajeure();
	void SetEmetteurPanneMajeure(const bool value);

	bool IsEmetteurPanneTC();
	void SetEmetteurPanneTC(const bool value);

	bool IsEmetteurEmission();
	void SetEmetteurEmission(const bool value);

	bool IsRecepteurMarche();
	void SetRecepteurMarche(const bool value);

	bool IsRecepteurPanneMajeure();
	void SetRecepteurPanneMajeure(const bool value);

	bool IsRecepteurPanneTC();
	void SetRecepteurPanneTC(const bool value);

	string GetClockPilot();
	void SetClockPilot(const string clock);
	bool ValidClockPilot(const string clock);

	string GetInr();
	void SetInr(const string inr);
	bool ValidInr(const string inr);

	int GetInrRate();
	void SetInrRate(const int rate);
	bool ValidInrRate(const int rate);

	bool ValidDateAndTime(const string datetime);
	bool ValidTimeAccuracy(const string accuracy);

	bool GetTest(const string id);
	void SetTest(const string id, const bool value);

	void GetIdentityString(string &ligne1, string &ligne2);
	void GetTestStringChannel(string &ligne1, string &ligne2);
	bool GetTestStringTC(string &ligne1, string &ligne2);
	bool GetTestStringIA(string &ligne1, string &ligne2, string &ligne3, string &ligne4);
	bool GetTestStringDX(string &ligne1, string &ligne2, string &ligne3, string &ligne4);
	bool GetTestStringEEPROM(string &ligne1, string &ligne2);

	bool GetQuadrivoie();
	void SetQuadrivoie(const bool value);

	bool IsModif();
	void SetModif(const bool modif);

	int GetVoieSelect();
	void SetVoieSelect(const int indice);

	bool IsEnTest();
	void StartTest();
	void StopTest();

	string GetTestProgress();
	void SetTestProgress(const string test);
	bool ValidTestProgress(const string test);
	bool ValidTestProgressVersion(const string test);

	void ReinitModem();

	void VueOps(const string voie);

	void VueTst(const int voie);

	void VueAutotest(const string type_erreur);

	void SetAutotestMessage(string *l1 = NULL, string *l2 = NULL, string *l3 = NULL, string *l4 = NULL);

	//
	void AffichageTestCartes(const string nomvoie);

	//******************
	//Gestion Pilote
	//******************
	bool GetPilExt();
	void SetPilExt(const bool etat);

	//******************
	//Gestion ZTS - PFT
	//******************
	bool GetZtsPft();
	void SetZtsPft(const bool etat);

	//**********************
	//Gestion FFT_1302 - PFT
	//**********************
	bool GetFft1302();
	void SetFft1302(const bool etat);

	//**********************
	//Gestion RecMil
	//**********************
	bool GetRecMil();
	void SetRecMil(const bool etat);

	//*****************************
	// Gestion de l'émission On/Off
	//*****************************
	void EmissionOff(const string id);
	void EmissionOn(const string id);

	void SetEmissionMsg(const string id, const bool value);
	bool GetEmissionMsg(const string id);

	//***************************
	// Test Activation d'une voie
	//***************************
	CString TestActivation(const string voie);

	//******************
	// Gestion Réception
	//******************
	void SetReceptionOn(const string voie);
	void SetReceptionOff(const string voie);
	void SetReceptionUp(const string voie);
	void SetReceptionDown(const string voie);

	//********************************
	// Nom de l'esclave ( diversité )
	//********************************

	void SetNameSlave(CString);
	CString GetNameSlave();

	//*****************
	// Test Carte A / B
	//*****************

	void SetTestCarte(bool);
	bool GetTestCarte();

	//*****************
	// FDI - 201202
	//*****************
	void SendRadEmiRnr(const string id);

	//*****************
	// FDI - 201509
	//*****************
	bool IsStatus(const string l_cntx);

};

#endif // !defined(AFX_EQUIPM1752_H__C0073A2F_AFAA_4C30_9020_DC3AE7B14513__INCLUDED_)

