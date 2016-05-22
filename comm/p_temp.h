// p_temp.h: interface for the CProtoTemp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P_TEMP_H__0A8FA1DF_5796_4180_97EA_586B230053FF__INCLUDED_)
#define AFX_P_TEMP_H__0A8FA1DF_5796_4180_97EA_586B230053FF__INCLUDED_

#include "..\comm\proto.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProtoTemp:public CProto
{
public:
	CProtoTemp(t_format fmt,CEquip *pEqp);
	virtual			~CProtoTemp();
	int				EnvoyerTS(char *message);
	virtual int		TraiteTC(char *mes);
	virtual int		TraiteTS(int type_cde,char *reponse);
	virtual int		RecevoirTC(char *message,int nb_car);
	virtual BOOL	ValideAcquittement(int type_cde,char *message);
	virtual char	*ControleTrame(char *message,char *octet_controle);
	virtual BOOL	ExtraitUtile(char *buf,char *message,int *long_utile);
};

#endif // !defined(AFX_P_TEMP_H__0A8FA1DF_5796_4180_97EA_586B230053FF__INCLUDED_)
