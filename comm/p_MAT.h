// p_MAT.h: interface for the CProto_MAT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P_MAT_H__33C4EF72_B9F8_4C6D_A290_AA02BE3C59E6__INCLUDED_)
#define AFX_P_MAT_H__33C4EF72_B9F8_4C6D_A290_AA02BE3C59E6__INCLUDED_

#include "..\comm\proto.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProto_MAT:public CProto
{
public:
	CProto_MAT(t_format fmt,CEquip *pEqp);
	virtual			~CProto_MAT();
	int				EnvoyerTS(char *message);
	virtual int		TraiteTC(char *mes);
	virtual int		TraiteTS(int type_cde,char *reponse);
	virtual int		RecevoirTC(char *message,int nb_car);
	virtual BOOL	ValideAcquittement(int type_cde,char *message);
	virtual char	*ControleTrame(char *message,char *octet_controle);
	virtual BOOL	ExtraitUtile(char *buf,char *message,int *long_utile);
};

#endif // !defined(AFX_P_MAT_H__33C4EF72_B9F8_4C6D_A290_AA02BE3C59E6__INCLUDED_)
