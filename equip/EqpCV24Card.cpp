// EqpCA150.cpp: implementation of the CEquipCV24Card class.
//
//////////////////////////////////////////////////////////////////////

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#include "stdafx.h"
#include <stdio.h>

#include "sicomex.h"
#include "DlgAccue.h"
#include "Equip\ParamSim.h"

#include "Equip\EqpCV24Card.h"
#include "comm\p_CV24Card.h"
#include "DLGCV24Card.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_CV24_KY58[];
extern char glob_CONTEXT_CV24_ANDVT[];

/* **************************************************************************
METHODE :		CEquipCV24Card(int idx, typeCV24Eqp type)
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquipCV24Card::CEquipCV24Card(int idx, TypeCV24Eqp atype):CEquip(idx)
{
	// The card status is active : Output can be used.
	status = true;
	key = 0;
	operatingMode = COMMAND_MODE;
	inputs = new BOOL[3];
	inputMask = new BOOL[3];
	outputs = new BOOL[8];
	type = atype;

	// initialize tables.
	int i;
	for(i=0;i<3;i++) {
		inputs[i] = false;
		inputMask[i] = true;
	}

	for(i=0;i<8;i++) {
		outputs[i] = false;
	}
}

/* **************************************************************************
METHODE :		~CEquipCV24Card
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquipCV24Card::~CEquipCV24Card()
{
	free(inputs);
	free(outputs);
	free(inputMask);
}

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipCV24Card::Allocation()
{
	t_affecte ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL)
	{
		proto = new CProtoCV24Card(ligne.format,this);
	}

	// Allocation protocole des CA150
	if(ihm == NULL)
	{
		ihm = new CDLGCV24Card;
		ihm->Associe(this);
		ihm->Create(IDD_CV24_CARD,glob_ihm);
		ihm->SetWindowText(ligne.repere);
		Afficher(ligne.controle);
		if(type == CV24_KY58)
		{
			Charge_Contexte(glob_CONTEXT_CV24_KY58);
		}
		if(type == CV24_ANDVT)
		{
			Charge_Contexte(glob_CONTEXT_CV24_ANDVT);
		}
	}
}

/* **************************************************************************
METHODE :		Charge_Contexte(char *fichier)
TRAITEMENT:		Initialise l'equipement a partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipCV24Card::Charge_Contexte(char *fichier)
{
	int  i, iResult;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];
	iResult = Recup_fichier(fichier, contenu);
	if(iResult<0)
	{
		AjouterMessage("**** Erreur d'ouverture fichier contexte exploitation", 0);
		return FALSE;
	}

	iResult = Extrait_ligne(contenu, "P00=", ligne, TAILLE_MAX_LIGNE);
	if( (strcmp(ligne+4, "CV24_KY58")!=0) || (strcmp(ligne+4, "CV24_ANDVT")!=0) )
	{
		if(iResult < 0)
		{
			AjouterMessage("**** Erreur fichier non conforme à l'équipement", iResult);
			return FALSE;
		}
	}

	// type
	if(strcmp(ligne+4, "CV24_KY58") == 0) {
		type = CV24_KY58;
	} else if(strcmp(ligne+4, "CV24_ANDVT") == 0) {
		type = CV24_ANDVT;
	}

	// Get the input values.
	iResult = Extrait_ligne(contenu, "P01=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for( i=0 ; i<3 ; i++ ) {
			if ( ligne[4+i] == '1' ) {
				inputs[i]=true;
			} else {
				inputs[i]=false;
			}
		}
	}

	// Get the input mask values.
	iResult = Extrait_ligne(contenu, "P02=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for( i=0 ; i<3 ; i++ ) {
			if ( ligne[4+i] == '1' ) {
				inputMask[i]=true;
			} else {
				inputMask[i]=false;
			}
		}
	}

	// Get the output values.
	iResult = Extrait_ligne(contenu, "P03=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for( i=0 ; i<8 ; i++ ) {
			if ( ligne[4+i] == '1' ) {
				outputs[i]=true;
			} else {
				outputs[i]=false;
			}
		}
	}

	((CDLGCV24Card *)ihm)->refresh();

	// Clé
	iResult = Extrait_ligne(contenu, "P04=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		key = atoi(ligne + 4);
	}

	// Status
	iResult = Extrait_ligne(contenu, "P05=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		if ( ligne[4] == '1' ) {
			status = true;
		} else {
			status = false;
		}
	}

	return TRUE;
}

/* **************************************************************************
METHODE :		Sauve_Contexte(char *fichier)
TRAITEMENT:		Sauveagrde le contexte d'exploitation d'un fichier
***************************************************************************	*/
BOOL CEquipCV24Card::Sauve_Contexte(char *fichier)
{
	int  i, iResult;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];

	// En tete fichier KY58
	if(type == CV24_KY58)
	{
		strcpy(contenu, "// Contexte d'exploitation d'une carte CV24\r\n");
		strcat(contenu, "// ************************************************\r\n");
		strcpy(ligne, "P00=CV24_KY58\r\n");
		strcat(contenu, ligne);
	} else { // ANDVT
		strcpy(contenu, "// Contexte d'exploitation d'une carte CC24\r\n");
		strcat(contenu, "// ************************************************\r\n");
		strcpy(ligne, "P00=CV24_ANDVT\r\n");
		strcat(contenu, ligne);
	}

	// Save the inputs values.
	strcat(contenu,"// Etats des entrées.\r\n");
	sprintf(ligne, "P01=%d%d%d\r\n", inputs[0], inputs[1], inputs[2]);
	strcat(contenu,ligne);

	// Save the mask status.
	strcat(contenu,"// Etats des masques des entrées.\r\n");
	sprintf(ligne, "P02=%d%d%d\r\n", inputMask[0], inputMask[1], inputMask[2]);
	strcat(contenu,ligne);

	// Save the outputs values.
	strcat(contenu,"// Etats des sorties.\r\nP03=");
	strcpy(ligne,"\0");
	for ( i=0 ; i<8 ; i++ ) {
		sprintf(ligne,"%s%d",ligne,outputs[i]);
	}
	strcat(contenu,ligne);
	strcat(contenu,"\r\n");

	// Valeur de la clé
	strcat(contenu,"// Valeur de la dernière clé transférée.\r\n");
	sprintf(ligne,"P04=%d\r\n",key);
	strcat(contenu,ligne);

	// Valeur du status
	strcat(contenu,"// Valeur du status.\r\n");
	sprintf(ligne,"P05=%d\r\n",status);
	strcat(contenu,ligne);

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
BOOL CEquipCV24Card::Power()
{
	BOOL	activite;
	CEquip::Power();

	activite = Actif();
	if(activite)
	{
		// TODO - Start equipment.
	}
	else
	{
		// TODO - Stop equipment.
	}
	return activite;
}

/**
 * Returns the output index.
 */
int CEquipCV24Card::getOutputIndex(int outputId) {
	if ( outputId == 14 ) {
		return 7;
	}
	if ( outputId >=0 && outputId < 7 ) {
		return outputId;
	}
	return -1;
}

// \\\\\\\\\\\\\\\\\\\ OPERATIONS \\\\\\\\\\\\\\\\\\\\

void CEquipCV24Card::clearKeys() {
	AjouterMessage("Demande d'effacement des clefs.",0);
	transferKey(0);
}

void CEquipCV24Card::transferKey() {
	char message[255];
	sprintf(message,"Demande de tranfert de la clé numero : %d",key);
	AjouterMessage(message,0);
}

void CEquipCV24Card::transferKey(int value) {
	if ( value < 0 || value > 7 ) {
		return;
	}
	key = value;
	((CDLGCV24Card *) ihm)->onKeyChange(key);
	transferKey();
}

// \\\\\\\\\\\\\\\\\\\ SETTERS \\\\\\\\\\\\\\\\\\\\\\\\

/**
 * Set the operating mode.
 */
void CEquipCV24Card::setOperatingMode(OperatingModeEnum mode) {
	if ( Actif() ) {
		operatingMode = mode;
	}
}

/**
 * Set the status value.
 */
void CEquipCV24Card::setStatus(BOOL newStatus) {
	if ( Actif() ) {
		status = newStatus;
		((CDLGCV24Card *) ihm)->onStatusChange();
	}
}

/**
 * Set the input mask value.
 * Genererate a change on IHM.
 */
void CEquipCV24Card::setInputMask(int inputId, BOOL value) {
	// The identifier must be 0 to 2.
	if ( inputId < 0 || inputId > 2 || !Actif() ) {
		return;
	}
	inputMask[inputId] = value;
	((CDLGCV24Card *)ihm)->onInputMaskValueChange(inputId);
}

/**
 * Set the 'id' input value.
 * Genererate a change on IHM.
 */
void CEquipCV24Card::setInput(int inputId, BOOL value) {
	// The identifier must be 0 to 2.
	if ( inputId < 0 || inputId > 2 || !Actif() ) {
		return;
	}
	inputs[inputId] = value;
	((CDLGCV24Card *)ihm)->onInputValueChange(inputId);
	if ( !inputMask[inputId] ) {
		proto->AjouterTS(NULL,TS_INT * 100 + inputId );
	}
}

/**
 * Set the 'id' output value.
 * Genererate a change on IHM.
 */
void CEquipCV24Card::setOutput(int id, BOOL value) {
	int outputIndex = getOutputIndex(id);
	if ( ( outputIndex < 0 ) || ( outputIndex > 7 ) || !Actif()) {
		return;
	}
	// The output cannot be sets.
	if ( !getStatus() ) {
		proto->AjouterTS(NULL,TS_ERROR * 100 + 11 );
	}
	outputs[outputIndex] = value;
	((CDLGCV24Card *)ihm)->onOutputValueChange(outputIndex);
}

// \\\\\\\\\\\\\\\\\\\\\ GETTERS \\\\\\\\\\\\\\\\\\\\\\

/**
 * Returns the equipment type. (KY58 or ANDVT).
 */
TypeCV24Eqp CEquipCV24Card::getType() {
	 return type;
}

/**
 * Returns the equipment status.
 */
BOOL	CEquipCV24Card::getStatus() {
	return status;
}

/**
 * Returns the 'inputId' input value.
 */
BOOL	CEquipCV24Card::getInputValue(int inputId) {
	if ( inputId < 0 ||inputId > 2 ) {
		return 1;
	}
	return inputs[inputId];
}

/**
 * Returns the 'outputId' output value.
 */
BOOL	CEquipCV24Card::getOutputValue(int outputIndex) {
	return outputs[outputIndex];
}

/**
 * Returns the 'inputId' input mask value.
 */
BOOL	CEquipCV24Card::getInputMaskValue(int inputIndex) {
	return inputMask[inputIndex];
}

/**
 * Returns the equipment current key.
 */
int		CEquipCV24Card::getKey() {
	return key;
}
