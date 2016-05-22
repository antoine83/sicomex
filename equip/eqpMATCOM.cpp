/* **************************************************************************
FICHIER :	Eqp_1237.CPP		 			AUTEUR : FSA
DATE DE CREATION : 	26/02/07		DERNIERE MODIFICATION : 26/02/07
VERSION :	1.0
ROLE :		Implémentation de la classe CEquipCommutationMatrix
***************************************************************************	*/
#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\eqpMATCOM.h"
#include "Comm\p_MatCom.h"
#include "DlgCommutationMatrix.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

const int	SEUIL_NIVEAU_HF 	= 25;

const char * DEFAULT_INPUT_NAME_FORMAT = "E-%d\0";
const char * DEFAULT_OUTPUT_NAME_FORMAT = "S-%d\0";

extern char glob_CONTEXT_COMMUTATION_MATRIX[];
/* **************************************************************************
METHODE :		CEquipCommutationMatrix()
TRAITEMENT:		Constructeur 
***************************************************************************	*/
CEquipCommutationMatrix::CEquipCommutationMatrix(int idx):CEquip(idx)
{
	local = false;
	test = 0;
	result_test="OK";
	type = DATA_MATRIX;
	// Presets are automaticly initialized.
	// Set default receptacle names and connections.
	for(int eachReceptacle=0; eachReceptacle < RECEPTACLE_COUNT ; eachReceptacle++) {
		// Identifier.
		inputs[eachReceptacle].identifier = eachReceptacle + 1;
		outputs[eachReceptacle].identifier = eachReceptacle + 1;
		// Name.
		sprintf(inputs[eachReceptacle].name,DEFAULT_INPUT_NAME_FORMAT,inputs[eachReceptacle].identifier);
		sprintf(outputs[eachReceptacle].name,DEFAULT_OUTPUT_NAME_FORMAT,outputs[eachReceptacle].identifier);
		// Connections.
		emissionConnections[eachReceptacle] = 0;
		receptionConnections[eachReceptacle] = 0;
	}
}

/* **************************************************************************
METHODE :		~CEquipCommutationMatrix
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquipCommutationMatrix::~CEquipCommutationMatrix()
{
	// Nothing to do.
}

/* **************************************************************************
METHODE :		Protocole()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipCommutationMatrix::Allocation()
{
	t_affecte	ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL) proto = new CProtoCommutationMatrix(ligne.format,this);

	if(ihm == NULL) ihm = new CDlgCommutationMatrix;
	ihm->Associe(this);
	ihm->Create(IDD_COMMUTATION_MATRIX,glob_ihm);
	ihm->SetWindowText(ligne.repere);
	Afficher(ligne.controle);

	Charge_Contexte(glob_CONTEXT_COMMUTATION_MATRIX);

	ihm->RedrawWindow();
}

/* **************************************************************************
METHODE :		Charge_Contexte()
TRAITEMENT:		Initialise l'équipement à partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipCommutationMatrix::Charge_Contexte(char *fichier)
{
	int 	iResult;						//int 	i,iResult;		//2009-11-27

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];

	iResult = Recup_fichier(fichier,contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation",iResult);
		return FALSE;
	}

	// Read the equipment type.
	iResult = Extrait_ligne(contenu, "P00=", ligne, TAILLE_MAX_LIGNE);
	if (strcmp(ligne+4, "COMMUTATION_MATRIX")!=0) {
		if(iResult < 0) {
			AjouterMessage("**** Erreur fichier non conforme à l'équipement", iResult);
			return FALSE;
		}
	}

	// Get the input names.
	iResult = Extrait_ligne(contenu, "P01=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		char * count = ligne + 4;
		char * offset = 0;
		char * lineLength = strlen(ligne) + ligne;
		for (short eachUplink=0; eachUplink < RECEPTACLE_COUNT ; eachUplink++)  {
			offset = count;
			while( count < lineLength && count[0] != ',' ) {
				count++;
			}
			strncpy(inputs[eachUplink].name,offset,count - offset);
			inputs[eachUplink].name[count - offset] = '\0';
			count++;
		}
	}

	// Get the output names.
	iResult = Extrait_ligne(contenu, "P02=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		char * count = ligne + 4;
		char * offset = 0;
		char * lineLength = strlen(ligne) + ligne;
		for (short eachUplink=0; eachUplink < RECEPTACLE_COUNT ; eachUplink++)  {
			offset = count;
			while( count < lineLength && count[0] != ',' ) {
				count++;
			}
			strncpy(outputs[eachUplink].name,offset,count - offset);
			outputs[eachUplink].name[count - offset] = '\0';
			count++;
		}
	}
	
	// Get the current emission connections.
	iResult = Extrait_ligne(contenu, "P03=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		sscanf(ligne+4,"%d,%d,%d,%d,%d,%d,%d,%d",
			&(emissionConnections[0]), &(emissionConnections[1]), &(emissionConnections[2]),
			&(emissionConnections[3]), &(emissionConnections[4]), &(emissionConnections[5]),
			&(emissionConnections[6]), &(emissionConnections[7]));
	}

	// Get the current reception connections.
	iResult = Extrait_ligne(contenu, "P04=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		sscanf(ligne+4,"%d,%d,%d,%d,%d,%d,%d,%d",
			&(receptionConnections[0]), &(receptionConnections[1]), &(receptionConnections[2]),
			&(receptionConnections[3]), &(receptionConnections[4]), &(receptionConnections[5]),
			&(receptionConnections[6]), &(receptionConnections[7]));
	}

	// TODO - Read the presets.

	((CDlgCommutationMatrix *)ihm)->refresh();

	return TRUE;
}

/* **************************************************************************
METHODE :		Sauve_Contexte()
TRAITEMENT:		Sauveagrde le contexte d'exploitation d'un fichier
***************************************************************************	*/
BOOL CEquipCommutationMatrix::Sauve_Contexte(char *fichier)
{
	int 	iResult;						//int 	i,iResult;		//2009-11-27

	char	contenu[TAILLE_MAX_MESSAGE+1];
	char	ligne[TAILLE_MAX_LIGNE+1];

	strcpy(contenu,"// Contexte d'exploitation d'une matrice de commutation\r\n");
	strcat(contenu,"// ****************************************************\r\n");
	strcpy(ligne, "P00=COMMUTATION_MATRIX\r\n");
	strcat(contenu, ligne);

	// Save the inputs names.
	strcat(contenu,"// Noms des entrées.\r\n");
	sprintf(ligne, "P01=%s,%s,%s,%s,%s,%s,%s,%s\r\n",
		inputs[0].name, inputs[1].name, inputs[2].name, inputs[3].name,
		inputs[4].name, inputs[5].name, inputs[6].name, inputs[7].name);
	strcat(contenu,ligne);
	
	// Save the outputs names.
	strcat(contenu,"// Noms des sorties.\r\n");
	sprintf(ligne, "P02=%s,%s,%s,%s,%s,%s,%s,%s\r\n",
		outputs[0].name, outputs[1].name, outputs[2].name, outputs[3].name,
		outputs[4].name, outputs[5].name, outputs[6].name, outputs[7].name);
	strcat(contenu,ligne);

	// Save the emissions connections.
	strcat(contenu,"// Connections d'emission.\r\n");
	sprintf(ligne, "P03=%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d\r\n",
		emissionConnections[0], emissionConnections[1], emissionConnections[2], emissionConnections[3],
		emissionConnections[4], emissionConnections[5], emissionConnections[6], emissionConnections[7]);
	strcat(contenu,ligne);

	// Save the reception connections.
	strcat(contenu,"// Connections d'emission.\r\n");
	sprintf(ligne, "P04=%02d,%02d,%02d,%02d,%02d,%02d,%02d,%02d\r\n",
		receptionConnections[0], receptionConnections[1], receptionConnections[2], receptionConnections[3],
		receptionConnections[4], receptionConnections[5], receptionConnections[6], receptionConnections[7]);
	strcat(contenu,ligne);

	// TODO - Save the context.

	iResult = Stocker_fichier(fichier,contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation",iResult);
		return FALSE;
	}

	return TRUE;
}

/* **************************************************************************
METHODE :		Power
TRAITEMENT:		Mise en route de l'équipement
***************************************************************************	*/
BOOL CEquipCommutationMatrix::Power()
{
	//BOOL	activite;
	CEquip::Power();

	activite = Actif()!=0;

	if(activite)
	{
		//proto->AjouterTS("Initialisation",CDE_TEXTE_SEUL);
	}
	else
	{
		//proto->AjouterTS("Arret de l'équipement",CDE_TEXTE_SEUL);
	}

	return activite;
}

// ****** GETTERS ******
bool CEquipCommutationMatrix::isLocal()
{
	return local;
}

/** Is the equipment is in actif mode. */
bool CEquipCommutationMatrix::isActif()
{
	return activite;
}

/** Get the matrix type. */
MatrixTypeEnum CEquipCommutationMatrix::getType() {
	return type;
}

/** Get the 'id' input name. */
char * CEquipCommutationMatrix::getInputName(int id) {
	if ( (id < 1) || (id > RECEPTACLE_COUNT )) {
		return NULL;
	}
	return inputs[id - 1].name;
}

/** Get the 'id' output name. */
char * CEquipCommutationMatrix::getOutputName(int id) {
	if ( (id < 1) || (id > RECEPTACLE_COUNT )) {
		return NULL;
	}
	return outputs[id - 1].name;
}

/** Get the emission connection for uplink. */
int CEquipCommutationMatrix::getEmissionConnection(int uplink) {
	if ( (uplink < 1) || (uplink > RECEPTACLE_COUNT )) {
		return 0;
	}
	return emissionConnections[uplink - 1];
}

/** Get the emission connection for downlink for inputs*/
int CEquipCommutationMatrix::getEmissionConnectionInputs(int downlink) {
	if ( (downlink < 1) || (downlink > RECEPTACLE_COUNT )) {
		return -1;
	}
	else
	{
		for(int i=0;i<RECEPTACLE_COUNT;i++)
		{
			if(emissionConnections[i]==downlink)return i;
		}
	}
	return -1;
}

/** Get the reception connection for downlink for inputs*/
int CEquipCommutationMatrix::getReceptionConnectionInputs(int downlink) {
	if ( (downlink < 1) || (downlink > RECEPTACLE_COUNT )) {
		return -1;
	}
	else
	{
		for(int i=0;i<RECEPTACLE_COUNT;i++)
		{
			if(receptionConnections[i]==downlink)return i;
		}
	}
	return -1;
}

/** Get the reception connection for uplink. */
int CEquipCommutationMatrix::getReceptionConnection(int uplink) {
	if ( (uplink < 1) || (uplink > RECEPTACLE_COUNT )) {
		return 0;
	}
	return receptionConnections[uplink - 1];
}

// ****** SETTERS ******
void CEquipCommutationMatrix::setLocal(bool newLocal)
{
	if ( Actif() ) {
		local = newLocal;
	}
}

/** Set the matrix type. */
void CEquipCommutationMatrix::setType(MatrixTypeEnum newType) {
	type = newType;
}

/** Set the 'id' input name. */
bool CEquipCommutationMatrix::setInputName(int id, char *name) {
	if ( (id < 1) || (id > RECEPTACLE_COUNT )) {
		return false;
	}
	EnterCriticalSection(&crit);
	strcpy(inputs[id - 1].name,name);
	evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);
	return true;
}

/** Set the 'id' output name. */
bool CEquipCommutationMatrix::setOutputName(int id, char *name) {
	if ( (id < 1) || (id > RECEPTACLE_COUNT )) {
		return false;
	}
	EnterCriticalSection(&crit);
	strcpy(outputs[id - 1].name,name);
	evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);
	return true;
}

/** Set emission connection. */
bool CEquipCommutationMatrix::setEmissionConnection(int uplink, int downlink) {
	if ( (uplink < 1) || (uplink > RECEPTACLE_COUNT)
		|| (downlink < 1) || (downlink > RECEPTACLE_COUNT)) {
		return false;
	}
	/** test de la sortie */
	if(getEmissionConnectionInputs(downlink)!=-1) {
		disconnectEmission(getEmissionConnectionInputs(downlink)+1,downlink);
	}
	EnterCriticalSection(&crit);
	emissionConnections[uplink - 1] = downlink;
	evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);
	return true;
}

/** Set the reception connection. */
bool CEquipCommutationMatrix::setReceptionConnection(int uplink, int downlink) {
	if ( (uplink < 1) || (uplink > RECEPTACLE_COUNT)
		|| (downlink < 1) || (downlink > RECEPTACLE_COUNT)) {
		return false;
	}
	/** test de la sortie */
	if (getReceptionConnectionInputs(downlink)!=-1) {
		disconnectReception(getReceptionConnectionInputs(downlink)+1,downlink);
	}
	EnterCriticalSection(&crit);
	receptionConnections[uplink - 1] = downlink;
	evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);
	return true;
}

// ****** METHODS ******

/** Disconnect a pair. */
void CEquipCommutationMatrix::disconnectEmission(int uplink, int downlink) {
	EnterCriticalSection(&crit);
	emissionConnections[uplink - 1] = 0;
	evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);
}

/** Disconnect a pair. */
void CEquipCommutationMatrix::disconnectReception(int uplink, int downlink) {
	EnterCriticalSection(&crit);
	receptionConnections[uplink - 1] = 0;
	evolution = (evolution+1) % PLAGE_EVOLUTION;
	LeaveCriticalSection(&crit);
}

/** Reset the commutation matrix. */
void CEquipCommutationMatrix::reset() {
	AjouterMessage("Reset de la matrice.",0);
}

/** Tests the matrix. */
void CEquipCommutationMatrix::testMatrix() {
	AjouterMessage("Test de la matrice demande.",0);
}

/** Remote a preset. */
bool CEquipCommutationMatrix::removePreset(int id) {
	// If the identifier is invalid.
	if ( id < 1 || id > MAX_PRESET_COUNT ) {
		return false;
	}
	// Reinitialize the preset.
	presets[id - 1].reset();
	return true;
}

/** Restore a preset. */
bool CEquipCommutationMatrix::restorePreset(int id) {
	// If the identifier is invalid.
	if ( id < 1 || id > MAX_PRESET_COUNT || !presets[id - 1].isSetted() ) {
		return false;
	}
	// Restore the preset.
	for (short eachUplink = 0 ; eachUplink < RECEPTACLE_COUNT ; eachUplink++) {
		setEmissionConnection(eachUplink + 1, presets[id - 1].emissionConnections[eachUplink]);
		setReceptionConnection(eachUplink + 1, presets[id - 1].receptionConnections[eachUplink]);
	}
	return true;
}

/** Set the preset. */
bool CEquipCommutationMatrix::setPreset(int presetId, CommutationMatrixPreset preset) {
	// If the identifier is invalid.
	if ( presetId < 1 || presetId > MAX_PRESET_COUNT) {
		return false;
	}
	memcpy(&(presets[presetId - 1]),&preset, sizeof(preset));
	return true;
}

/** Commutation ihm Emission */

void CEquipCommutationMatrix::setConnectionEmission(int para1,int para2)
{
	setEmissionConnection(para1,para2);
}

/** Commutation ihm Reception */

void CEquipCommutationMatrix::setConnectionReception(int para1,int para2)
{
	setReceptionConnection(para1,para2);
}

void CEquipCommutationMatrix::ChangeEdit(CString result)
{
if(result=="OK")result_test="OK";
else result_test="KO";
}

/** Set chaine Edit*/
CString CEquipCommutationMatrix::GetEdit()
{
return result_test;
}

// ************************************************
// ******  CommutationMatrixPreset
// ************************************************

CommutationMatrixPreset::CommutationMatrixPreset() {
	reset();
}

CommutationMatrixPreset::~CommutationMatrixPreset() {
	// Do nothing.
}

// Get the setted value.
bool CommutationMatrixPreset::isSetted() {
	return setted;
}

// Set the setted value.
void CommutationMatrixPreset::setSetted(bool newSetted) {
	setted = newSetted;
}

// Reset the preset.
void CommutationMatrixPreset::reset() {
	setted = false;
	for(short eachUplink = 0 ; eachUplink < RECEPTACLE_COUNT ; eachUplink++) {
		emissionConnections[eachUplink] = 0;
		receptionConnections[eachUplink] = 0;
	}
}
