// EqpCA150.h: interface for the CEquipCV24Card class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQPCV24CARD_H__2539B4C7_4B39_45C5_B2DD_A29BCA2143E9__INCLUDED_)
#define AFX_EQPCV24CARD_H__2539B4C7_4B39_45C5_B2DD_A29BCA2143E9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equip.h"

// Les télésignalisations.
const int TS_ERROR = 0;
const int TS_ACK   = 1;
const int TS_INT   = 2;

// Erreurs :
typedef enum _errors {
	ERROR_CV24_INVALID_COMMAND    = 1,
	ERROR_CV24_IMPOSSIBLE_COMMAND = 2,
	ERROR_CV24_CANNOT_REALISE_COMMAND = 3,
	ERROR_CV24_CARD_HS            = 4,
	ERROR_CV24_CAD_FRAMING_ERROR  = 5,
	ERROR_CV24_CAD_PARITY_ERROR   = 6,
	ERROR_CV24_CAD_OVERRUN_ERROR  = 7,
	ERROR_CV24_FIFO_OVERRUN       = 8,
	ERROR_CV24_CANNOT_CLEAR_FIFO  = 9,
	ERROR_CV24_RX_NOT_BUSY        = 10,
	ERROR_CV24_TEMPO_106_OVERFLOW = 11,
	ERROR_CV24_TEMPO_107_OVERFLOW = 12,
	ERROR_CV24_CIPHER_FRAMING_ERROR = 13,
	ERROR_CV24_CIPHER_PARITY_ERROR  =  0,
	ERROR_CV24_CIPHER_OVERRUN_ERROR = 14,
	ERROR_CV24_NONE				  = 15
} ErrorEnum;

typedef enum _operatingMode
{
	TRANSFER_MODE = 0,
	COMMAND_MODE  = 1
} OperatingModeEnum;

typedef enum
{
	CV24_KY58 = 0,
	CV24_ANDVT = 1
} TypeCV24Eqp;

class CEquipCV24Card:public CEquip
{
public:
	CEquipCV24Card(int idx, TypeCV24Eqp type);
	virtual ~CEquipCV24Card();
	void	Allocation();
	BOOL	Charge_Contexte(char *fichier);
	BOOL	Sauve_Contexte(char *fichier);
	BOOL	Power();

	// Operations.
	void	clearKeys();
	void	transferKey();
	void	transferKey(int keyId);

	// Setters.
	void	setStatus(BOOL newStatus);
	void	setInputMask(int id,BOOL value);
	void	setInput(int id,BOOL value);
	void	setOutput(int id,BOOL value);
	void	setOperatingMode(OperatingModeEnum mode);

	// Getters.
	TypeCV24Eqp getType();
	BOOL	getStatus();
	BOOL	getInputValue(int inputId);
	BOOL	getOutputValue(int outputId);
	BOOL	getInputMaskValue(int inputId);
	int		getKey();

private:
	TypeCV24Eqp type;
	BOOL	status;
	OperatingModeEnum operatingMode;
	BOOL*	inputs;
	BOOL*	outputs;
	BOOL*	inputMask;
	short	key;
	int	getOutputIndex(int outputId);

};

#endif // !defined(AFX_EQPCV24CARD_H__2539B4C7_4B39_45C5_B2DD_A29BCA2143E9__INCLUDED_)
