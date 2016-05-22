// EquipTest.h: interface for the CEquipTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQUIPTEST_H__1C77653A_3C90_425B_8045_3EFBE4610C6A__INCLUDED_)
#define AFX_EQUIPTEST_H__1C77653A_3C90_425B_8045_3EFBE4610C6A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CEquipTest:public CEquip
{
public:
	CEquipTest(int idx);
	virtual ~CEquipTest();
	BOOL	Charge_Contexte(char *fichier);
	BOOL	Sauve_Contexte(char *fichier);
	void	Allocation();
	BOOL	Power();
	void	AfficheMessage(char *mes);
	void	EnvoiMessage(char *mes);
	void	MAJMessage();


	char *	MESSAGE;
	bool	DebutCR;
	bool	DebutLF;
	bool	DebutSUB;
	bool	FinCR;
	bool	FinLF;
	bool	FinSUB;
};

#endif // !defined(AFX_EQUIPTEST_H__1C77653A_3C90_425B_8045_3EFBE4610C6A__INCLUDED_)
