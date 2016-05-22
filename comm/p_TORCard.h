// p_CA150.h: interface for the CProtoCA150 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P_TOR_CARD_H__1187430F_1A80_42E8_B962_8B67F26C1A31__INCLUDED_)
#define AFX_P_TOR_CARD_H__1187430F_1A80_42E8_B962_8B67F26C1A31__INCLUDED_

#include "..\comm\proto.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

typedef enum TorProtocolErrors_ {
	INVALID_IDENTIFIER = 1,
	INVALID_OUTPUT,
	INVALID_OUTPUT_VALUE,
	INVALID_INPUT,
	INVALID_INPUT_MASK,
	INVALID_KEY,
	KEY_ERASING_FAILURE,
	INVALID_COMMAND_FORMAT
} TorProtocolErrors;

class CProtoTORCard:public CProto
{
public:
	CProtoTORCard(t_format fmt,CEquip *pEqp);
	virtual			~CProtoTORCard();
	int				EnvoyerTS(char *message);
	virtual int		TraiteTC(char *mes);
	virtual int		TraiteTS(int type_cde,char *reponse);
	virtual int		RecevoirTC(char *message,int nb_car);
	virtual BOOL	ValideAcquittement(int type_cde,char *message);
	virtual BOOL	ExtraitUtile(char *buf,char *message,int *long_utile);

private:
	// Encoder le status passe en parametre.
	char *			encodeStatus(BOOL value);
	// Retourne le decodage du status passe en parametre.
	BOOL			decodeStatus(char * value);
	// Tester si le parametre value est un status.
	BOOL			isValidStatus(char *value);
};

#endif // !defined(AFX_P_TOR_CARD_H__1187430F_1A80_42E8_B962_8B67F26C1A31__INCLUDED_)
