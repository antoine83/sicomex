// EqpTORCard.cpp: implementation of the CEquipTORCard class.
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

#include "Equip\EqpTORCard.h"
#include "comm\p_TORCard.h"
#include "DLGTORCard.h"

#include "Divers\div_fic.h"

extern	CParamSimu	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

extern char glob_CONTEXT_TOR_KY58[];
extern char glob_CONTEXT_TOR_ANDVT[];
extern char glob_CONTEXT_TOR_CARD[];

/* **************************************************************************
METHODE :		CEquipTORCard(int idx, typeTOREqp type)
TRAITEMENT:		Constructeur
***************************************************************************	*/
CEquipTORCard::CEquipTORCard(int idx, TypeTOREqp atype):CEquip(idx)
{
	key = 0;
	inputs = new BOOL[INPUT_COUNT];
	inputMask = new BOOL[INPUT_COUNT];
	outputs = new BOOL[OUTPUT_COUNT];
	type = atype;

	// initialize tables.
	int i;
	for(i=0;i<INPUT_COUNT;i++) {
		inputs[i] = false;
		inputMask[i] = false;
	}

	for(i=0;i<OUTPUT_COUNT;i++) {
		outputs[i] = false;
	}
}

/* **************************************************************************
METHODE :		~CEquipTORCard
TRAITEMENT:		Destructeur
***************************************************************************	*/
CEquipTORCard::~CEquipTORCard()
{
	free(inputs);
	free(outputs);
	free(inputMask);
}

/* **************************************************************************
METHODE :		Allocation()
TRAITEMENT:		Alloue le protocole de communication et l'ecran de controle
***************************************************************************	*/
void CEquipTORCard::Allocation()
{
	t_affecte ligne;

	glob_paramsimu->Equipement(index,&ligne);
	if(proto == NULL)
	{
		proto = new CProtoTORCard(ligne.format,this);
	}

	// Allocation protocole des CA150
	if(ihm == NULL)
	{
		ihm = new CDLGTORCard;
		ihm->Associe(this);
		ihm->Create(IDD_TOR_CARD,glob_ihm);
		ihm->SetWindowText(ligne.repere);
		Afficher(ligne.controle);
		if(type == TYPE_TOR_KY58)
		{
			Charge_Contexte(glob_CONTEXT_TOR_KY58);
		} else if(type == TYPE_TOR_ANDVT)
		{
			Charge_Contexte(glob_CONTEXT_TOR_ANDVT);
		} else if (type == TYPE_TOR_CARD) {
			Charge_Contexte(glob_CONTEXT_TOR_CARD);
		}
	}
}

/* **************************************************************************
METHODE :		Charge_Contexte(char *fichier)
TRAITEMENT:		Initialise l'equipement a partir d'un fichier contenant un
				contexte d'exploitation
***************************************************************************	*/
BOOL CEquipTORCard::Charge_Contexte(char *fichier)
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
	if( (strcmp(ligne+4, "TOR_KY58") !=0) ||
		(strcmp(ligne+4, "TOR_ANDVT")!=0) ||
		(strcmp(ligne+4, "TOR_CARD") !=0) )
	{
		if(iResult < 0)
		{
			AjouterMessage("**** Erreur fichier non conforme à l'équipement", iResult);
			return FALSE;
		}
	}

	// type
	if(strcmp(ligne+4, "TOR_KY58") == 0) {
		type = TYPE_TOR_KY58;
	} else if(strcmp(ligne+4, "TOR_ANDVT") == 0) {
		type = TYPE_TOR_ANDVT;
	} else if (strcmp(ligne+4, "TOR_CARD") == 0) {
		type = TYPE_TOR_CARD;
	}

	// Get the input values.
	iResult = Extrait_ligne(contenu, "P01=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		for( i=0 ; i < INPUT_COUNT ; i++ ) {
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
		for( i=0 ; i < INPUT_COUNT ; i++ ) {
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
		for( i=0 ; i < OUTPUT_COUNT ; i++ ) {
			if ( ligne[4+i] == '1' ) {
				outputs[i]=true;
			} else {
				outputs[i]=false;
			}
		}
	}

	((CDLGTORCard *)ihm)->refresh();

	// Clé
	iResult = Extrait_ligne(contenu, "P04=", ligne, TAILLE_MAX_LIGNE);
	if(iResult >= 0)
	{
		key = atoi(ligne + 4);
	}

	return TRUE;
}

/* **************************************************************************
METHODE :		Sauve_Contexte(char *fichier)
TRAITEMENT:		Sauveagrde le contexte d'exploitation d'un fichier
***************************************************************************	*/
BOOL CEquipTORCard::Sauve_Contexte(char *fichier)
{
	int  i, iResult;
	char contenu[TAILLE_MAX_MESSAGE+1];
	char ligne[TAILLE_MAX_LIGNE+1];

	// En tete fichier KY58
	if(type == TYPE_TOR_KY58)
	{
		strcpy(contenu, "// Contexte d'exploitation d'une carte TOR\r\n");
		strcat(contenu, "// ************************************************\r\n");
		strcpy(ligne, "P00=TOR_KY58\r\n");
		strcat(contenu, ligne);
	} else if (type == TYPE_TOR_ANDVT) { // ANDVT
		strcpy(contenu, "// Contexte d'exploitation d'une carte TOR\r\n");
		strcat(contenu, "// ************************************************\r\n");
		strcpy(ligne, "P00=TOR_ANDVT\r\n");
		strcat(contenu, ligne);
	} else if (type == TYPE_TOR_CARD) { // TOR CARD.
		strcpy(contenu, "// Contexte d'exploitation d'une carte TOR\r\n");
		strcat(contenu, "// ************************************************\r\n");
		strcpy(ligne, "P00=TOR_CARD\r\n");
		strcat(contenu, ligne);
	}

	// Save the inputs values.
	strcat(contenu,"// Etats des entrées.\r\nP01=");
	strcpy(ligne,"\0");
	for( i=0 ; i < INPUT_COUNT ; i++) {
		sprintf(ligne, "%s%d", ligne, inputs[i]);
	}
	strcat(contenu,ligne);
	strcat(contenu,"\r\n");

	// Save the mask status.
	strcat(contenu,"// Etats des masques des entrées.\r\nP02=");
	strcpy(ligne,"\0");
	for( i=0 ; i < INPUT_COUNT ; i++) {
		sprintf(ligne, "%s%d", ligne, inputMask[i]);
	}
	strcat(contenu,ligne);
	strcat(contenu,"\r\n");

	// Save the outputs values.
	strcat(contenu,"// Etats des sorties.\r\nP03=");
	strcpy(ligne,"\0");
	for ( i=0 ; i < OUTPUT_COUNT ; i++ ) {
		sprintf(ligne,"%s%d",ligne,outputs[i]);
	}
	strcat(contenu,ligne);
	strcat(contenu,"\r\n");

	// Valeur de la clé
	strcat(contenu,"// Valeur de la dernière clé transférée.\r\n");
	sprintf(ligne,"P04=%d\r\n",key);
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
BOOL CEquipTORCard::Power()
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

// \\\\\\\\\\\\\\\\\\\ OPERATIONS \\\\\\\\\\\\\\\\\\\\

void CEquipTORCard::clearKeys() {
	key = 0;
	((CDLGTORCard *) ihm)->onKeyChange(key);
}


// \\\\\\\\\\\\\\\\\\\ SETTERS \\\\\\\\\\\\\\\\\\\\\\\\

/**
 * Set the input mask value.
 * Genererate a change on IHM.
 */
void CEquipTORCard::setInputMask(int inputIndex, BOOL value) {
	// The identifier must be valid.
	if ( inputIndex < 0 || inputIndex >= INPUT_COUNT || !Actif() ) {
		return;
	}
	inputMask[inputIndex] = value;
	((CDLGTORCard *)ihm)->onInputMaskValueChange(inputIndex);
}

/**
 * Set the 'id' input value.
 * Genererate a change on IHM.
 */
void CEquipTORCard::setInput(int inputIndex, BOOL value) {
	// The identifier must be valid.
	if ( inputIndex < 0 || inputIndex >= INPUT_COUNT || !Actif() ) {
		return;
	}
	inputs[inputIndex] = value;
	((CDLGTORCard *)ihm)->onInputValueChange(inputIndex);
	if ( inputMask[inputIndex] ) {
		proto->AjouterTS(NULL,TS_TOR_ISC * 100 + inputIndex);
	}
}

/**
 * Set the 'id' output value.
 * Genererate a change on IHM.
 */
void CEquipTORCard::setOutput(int outputIndex, BOOL value) {
	// The identifier must be valid.
	if ( ( outputIndex < 0 ) || ( outputIndex >= OUTPUT_COUNT ) || !Actif()) {
		return;
	}
	outputs[outputIndex] = value;
	((CDLGTORCard *)ihm)->onOutputValueChange(outputIndex);
}

/**
 * Sets the key.
 */
BOOL CEquipTORCard::setKey(int value) {
	if ( value < 0 || value > 7 ) {
		return FALSE;
	}
	key = value;
	((CDLGTORCard *) ihm)->onKeyChange(key);
	return TRUE;
}

// \\\\\\\\\\\\\\\\\\\\\ GETTERS \\\\\\\\\\\\\\\\\\\\\\

/**
 * Returns the equipment type. (KY58 or ANDVT).
 */
TypeTOREqp CEquipTORCard::getType() {
	 return type;
}

/**
 * Returns the 'inputIndex' input value.
 */
BOOL	CEquipTORCard::getInputValue(int inputIndex) {
	if ( inputIndex < 0 ||inputIndex >= INPUT_COUNT ) {
		return 1;
	}
	return inputs[inputIndex];
}

/**
 * Returns the 'outputIndex' output value.
 */
BOOL	CEquipTORCard::getOutputValue(int outputIndex) {
	return outputs[outputIndex];
}

/**
 * Returns the 'inputIndex' input mask value.
 */
BOOL	CEquipTORCard::getInputMaskValue(int inputIndex) {
	return inputMask[inputIndex];
}

/**
 * Returns the equipment current key.
 */
int		CEquipTORCard::getKey() {
	return key;
}
