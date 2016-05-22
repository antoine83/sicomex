// p_CA150.h: interface for the CProtoCA150 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P_CA150_H__1187430F_1A80_42E8_B962_8B67F26C1A31__INCLUDED_)
#define AFX_P_CA150_H__1187430F_1A80_42E8_B962_8B67F26C1A31__INCLUDED_

#include "..\comm\proto.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProtoCV24Card:public CProto
{
public:
	CProtoCV24Card(t_format fmt,CEquip *pEqp);
	virtual			~CProtoCV24Card();
	int				EnvoyerTS(char *message, int nbChar);
	virtual int		TraiteTC(char *mes);
	virtual int		TraiteTS(int type_cde,char *reponse);
	virtual int		RecevoirTC(char *message,int nb_car);
	virtual BOOL	ValideAcquittement(int type_cde,char *message);
	void sendResponse(char *mes);
	virtual BOOL ExtraitUtile(char *buf,char *message,int *long_utile);
};

#endif // !defined(AFX_P_CA150_H__1187430F_1A80_42E8_B962_8B67F26C1A31__INCLUDED_)
