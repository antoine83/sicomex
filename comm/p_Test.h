// p_Test.h: interface for the CProto_Test class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_P_TEST_H__70D864EC_98FB_4E54_B634_8CF863BC563B__INCLUDED_)
#define AFX_P_TEST_H__70D864EC_98FB_4E54_B634_8CF863BC563B__INCLUDED_

#include "..\comm\proto.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CProto_Test:public CProto 
{
public:
	CProto_Test(t_format fmt,CEquip *pEqp);
	virtual ~CProto_Test();
	int		EnvoyerTS(char *message);
	int		TraiteTC(char *mes);
	int		TraiteTS(int type_cde,char *reponse);
	int		RecevoirTC(char *message,int nb_car);
};

#endif // !defined(AFX_P_TEST_H__70D864EC_98FB_4E54_B634_8CF863BC563B__INCLUDED_)
