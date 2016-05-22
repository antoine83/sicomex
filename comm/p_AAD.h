// p_AAD.h: interface for the CProtoAAD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P_AAD_H__C56C8C4B_C9FF_4C71_8826_A1B1D89E5178__INCLUDED_)
#define AFX_P_AAD_H__C56C8C4B_C9FF_4C71_8826_A1B1D89E5178__INCLUDED_

#include "..\comm\proto.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProtoAAD:public CProto
{
public:
	CProtoAAD(t_format fmt,CEquip *pEqp);
	virtual			~CProtoAAD();
	int				EnvoyerTS(char *message);
	virtual int		TraiteTC(char *mes);
	virtual int		TraiteTS(int type_cde,char *reponse);
	virtual int		RecevoirTC(char *message,int nb_car);
	virtual BOOL	ValideAcquittement(int type_cde,char *message);
	virtual char	*ControleTrame(char *message,char *octet_controle);
	virtual BOOL	ExtraitUtile(char *buf,char *message,int *long_utile);
};

#endif // !defined(AFX_P_AAD_H__C56C8C4B_C9FF_4C71_8826_A1B1D89E5178__INCLUDED_)
