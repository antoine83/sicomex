// EqpTOR.h: interface for the CEquipTORCard class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQPTORCARD_H__2539B4C7_4B39_45C5_B2DD_A29BCA2143E9__INCLUDED_)
#define AFX_EQPTORCARD_H__2539B4C7_4B39_45C5_B2DD_A29BCA2143E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equip.h"

const int OUTPUT_COUNT = 10;
const int INPUT_COUNT = 6;

const int TS_TOR_ISC = 1;

typedef enum
{
	TYPE_TOR_KY58 = 0,
	TYPE_TOR_ANDVT = 1,
	TYPE_TOR_CARD = 2
} TypeTOREqp;

class CEquipTORCard:public CEquip
{
public:
	CEquipTORCard(int idx, TypeTOREqp type);
	virtual ~CEquipTORCard();
	void	Allocation();
	BOOL	Charge_Contexte(char *fichier);
	BOOL	Sauve_Contexte(char *fichier);
	BOOL	Power();

	// Operations.
	void	clearKeys();

	// Setters.
	void    setCardStatus(BOOL value);
	void	setInputMask(int id,BOOL value);
	void	setInput(int id,BOOL value);
	void	setOutput(int id,BOOL value);
	BOOL	setKey(int keyId);

	// Getters.
	TypeTOREqp getType();
	BOOL	getCardStatus();
	BOOL	getInputValue(int inputId);
	BOOL	getOutputValue(int outputId);
	BOOL	getInputMaskValue(int inputId);
	int		getKey();

private:
	TypeTOREqp type;
	BOOL*	inputs;
	BOOL*	outputs;
	BOOL*	inputMask;
	short	key;

};

#endif // !defined(AFX_EQPTORCARD_H__2539B4C7_4B39_45C5_B2DD_A29BCA2143E9__INCLUDED_)
