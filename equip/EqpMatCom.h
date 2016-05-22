/*************************************************************************
FICHIER :	EqpMATCOM.h				 	AUTEUR : FSA
DATE DE CREATION : 	26/02/07			DERNIERE MODIFICATION : 26/02/07
VERSION :	1.0
*************************************************************************/
#ifndef _CEQUIP_COMMUTATION_MATRIX
#define _CEQUIP_COMMUTATION_MATRIX
/* **************************************************************************
NOM DU COMPOSANT : 		CEquip1237

ROLE DU COMPOSANT :		Classe Equipement Matrice Commutation

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

#include "Equip.h"
#include <string>

using namespace std;

const int MAX_NAME_COUNT = 11;
const int RECEPTACLE_COUNT = 8;
const int MAX_PRESET_COUNT = 10;

// Télésignalisation : EME pour Emetteur
const int	COM_MAT_MODE_TRAFIC	= 1;

/**
 * The receptacle type.
 */
typedef struct _Receptacle
{
	int		identifier;				  // Entre 1 et 8
	char	name[MAX_NAME_COUNT + 1]; // de 40000 à 29999990 Hz
} Receptacle;

/**
 * The matrix type enumeration.
 */
typedef enum _MatrixTypeEnum {
	DATA_MATRIX  = 0,
	RADIO_MATRIX = 1
} MatrixTypeEnum;

/**
 * The preset type.
 */
class CommutationMatrixPreset {
	private:
		bool setted;

	public:
		// The connections table.
		short emissionConnections[RECEPTACLE_COUNT];
		short receptionConnections[RECEPTACLE_COUNT];

		// *** Contructors & Desctructors. ***

		// Contructs a new commutation matrix preset.
		CommutationMatrixPreset();

		// Destruct the preset.
		~CommutationMatrixPreset();

		// *** Getters ***

		// Get the setted value.
		bool isSetted();

		// *** Setters ***

		// Set the setted value.
		void setSetted(bool newSetted);

		// *** Others functions. ***

		// Reset the preset.
		void reset();
};

/**
 * This class represent a commutation matrix.
 */
class CEquipCommutationMatrix:public CEquip
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
protected:
	/** Is actif. */
	bool		activite;
	/** Is local. */
	bool		local;
	/** The tests result. */
	int		test;
	/** chaine test */
	CString result_test;
	/** The matrix type. */
	MatrixTypeEnum type;
	/** The preset table. */
	CommutationMatrixPreset presets[MAX_PRESET_COUNT];

	// The receptacles tables.
	Receptacle inputs[RECEPTACLE_COUNT];
	Receptacle outputs[RECEPTACLE_COUNT];

	// The connections table.
	short emissionConnections[RECEPTACLE_COUNT];
	short receptionConnections[RECEPTACLE_COUNT];


/* **************************************************************************
METHODE :		CEquipCommutationMatrix()
TRAITEMENT:		Constructeur
***************************************************************************	*/
public:
	CEquipCommutationMatrix(int idx);

/* **************************************************************************
METHODE :		~CEquipCommutationMatrix()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CEquipCommutationMatrix();

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'écran de controle
***************************************************************************	*/
	virtual void Allocation();

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

/* **************************************************************************
METHODE :		Power
TRAITEMENT:		Mise en route de l'équipement
***************************************************************************	*/
	BOOL Power();

	// ********** GETTERS ***********

	/** Get the matrix type. */
	MatrixTypeEnum getType();

	/** Get the 'id' input name. */
	char * getInputName(int id);

	/** Get the 'id' output name. */
	char * getOutputName(int id);

	/** Get the emission connection for uplink. */
	int getEmissionConnection(int uplink);
	
	/** Get the emission connection for downlink for inputs*/
	int getEmissionConnectionInputs(int downlink);

	/** Get the reception connection for uplink. */
	int getReceptionConnection(int uplink);

	/** Get the reception connection for downlink for inputs*/
	int getReceptionConnectionInputs(int downlink);

	/** Is the equipment is in local mode. */
	bool isLocal();

	/** Is the equipment is in actif mode. */
	bool isActif();

	// ********** SETTERS ***********

	/** Set the local mode. */
	void setLocal(bool newLocal);

	/** Set the matrix type. */
	void setType(MatrixTypeEnum newType);

	/** Set the 'id' input name. */
	bool setInputName(int id, char *name);

	/** Set the 'id' output name. */
	bool setOutputName(int id, char *name);

	/** Set emission connection. */
	bool setEmissionConnection(int uplink, int downlink);

	/** Set the reception connection. */
	bool setReceptionConnection(int uplink, int downlink);

	/** Set the preset. */
	bool setPreset(int presetId, CommutationMatrixPreset preset);

	// *********** METHODS *************

	/** Disconnect a pair. */
	void disconnectEmission(int uplink, int downlink);

	/** Disconnect a pair. */
	void disconnectReception(int uplink, int downlink);

	/** Reset the commutation matrix. */
	void reset();

	/** Tests the matrix. */
	void testMatrix();

	/** Remote a preset. */
	bool removePreset(int id);

	/** Restore a preset. */
	bool restorePreset(int id);

	/** Commutation ihm Emission */
	void setConnectionEmission(int para1,int para2);

	/** Commutation ihm reception */
	void setConnectionReception(int para1,int para2);

	/** change the edit */
	void ChangeEdit(CString result);

	/** Set chaine Edit*/
	CString GetEdit();
};

#endif

