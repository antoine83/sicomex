// EqpTemp.h: interface for the CEquipTemp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQPTEMP_H__9AD81833_3FCC_4E08_A5B0_E4030E816AB6__INCLUDED_)
#define AFX_EQPTEMP_H__9AD81833_3FCC_4E08_A5B0_E4030E816AB6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equip.h"

// Telesignalisation

class CEquipTemp:public CEquip
{
private:
	int local;
public:
	CEquipTemp(int idx);
	virtual			~CEquipTemp();
	virtual void	Allocation();
	virtual BOOL	Charge_Contexte(char *fichier);
	virtual BOOL	Sauve_Contexte(char *fichier);
	BOOL			Power();
	int				Local() const;
	int				ChangeLocal(int mode,BOOL genere_TS);
};

#endif // !defined(AFX_EQPTEMP_H__9AD81833_3FCC_4E08_A5B0_E4030E816AB6__INCLUDED_)
