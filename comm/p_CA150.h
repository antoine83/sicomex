// p_CA150.h: interface for the CProtoCA150 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P_CA150_H__1187430F_1A80_42E8_B962_8B67F26C1A31__INCLUDED_)
#define AFX_P_CA150_H__1187430F_1A80_42E8_B962_8B67F26C1A31__INCLUDED_

#include "..\comm\proto.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProtoCA150:public CProto
{
public:
	CProtoCA150(t_format fmt,CEquip *pEqp);
	virtual			~CProtoCA150();
	int				EnvoyerTS(char *message);
	virtual int		TraiteTC(char *mes);
	virtual int		TraiteTS(int type_cde,char *reponse);
	virtual int		RecevoirTC(char *message,int nb_car);
	virtual BOOL	ValideAcquittement(int type_cde,char *message);
	virtual char	*ControleTrame(char *message,char *octet_controle);
	virtual BOOL	ExtraitUtile(char *buf,char *message,int *long_utile);
};

#endif // !defined(AFX_P_CA150_H__1187430F_1A80_42E8_B962_8B67F26C1A31__INCLUDED_)
