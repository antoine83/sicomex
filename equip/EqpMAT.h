// EqpMAT.h: interface for the EqpMAT class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQPMAT_H__BE3FC12D_7AA1_42CB_92F1_8A64C41A392C__INCLUDED_)
#define AFX_EQPMAT_H__BE3FC12D_7AA1_42CB_92F1_8A64C41A392C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equip.h"

// Telesignalisation
const int DEFAUT_AUCUN					=  0;
const int DEFAUT_ALIMENTATION			=  1;
const int DEFAUT_CONFIGURATION_CHASSIS	=  2;
const int DEFAUT_RAM_UC					=  3;
const int DEFAUT_PROM_UC				=  4;
const int DEFAUT_BUS_INTERNE_UC			=  5;
const int DEFAUT_BUS_LENT				=  6;
const int DEFAUT_FORMAT_MESSAGE			=  7;
const int DEFAUT_SEQUENCE				=  8;
const int DEFAUT_CARTE_RELAIS_1			=  9;
const int DEFAUT_CARTE_RELAIS_2			= 10;
const int DEFAUT_CARTE_RELAIS_3			= 11;
const int DEFAUT_CARTE_RELAIS_4			= 12;
const int DEFAUT_CARTE_RELAIS_5			= 13;
const int DEFAUT_CARTE_RELAIS_6			= 14;
const int DEFAUT_CARTE_RELAIS_7			= 15;
const int DEFAUT_CARTE_RELAIS_8			= 16;
const int DEFAUT_CARTE_RELAIS_9			= 17;
const int DEFAUT_CARTE_RELAIS_10		= 18;
const int DEFAUT_CARTE_RELAIS_11		= 19;
const int DEFAUT_CARTE_RELAIS_12		= 20;
const int DEFAUT_ATTENUATEUR_1			= 21;
const int DEFAUT_ATTENUATEUR_2			= 22;
const int DEFAUT_ATTENUATEUR_3			= 23;
const int DEFAUT_ATTENUATEUR_4			= 24;
const int DEFAUT_PROGRAMMATION			= 25;
const int DEFAUT_SANS					= 26;

typedef enum
{
	SPIN, L11
} TypeMatrice;

class CEqpMAT:public CEquip
{
private:
	bool local;
public:
	CEqpMAT	(int idx, TypeMatrice type);
	virtual	~CEqpMAT();
	void	Allocation();
	BOOL	Charge_Contexte(char *fichier);
	BOOL	Sauve_Contexte(char *fichier);
	BOOL	Power();
	bool	Local() const;
	void	ChangeLocal(bool b);
	void	InitialiserMatrice();
	void	ResetMatrice();
	BOOL	ValiderMatrice();
	void	ChgtEtatMatrice(int idxPM, int idxER);
	void	DeconnexionMatrice(int idxER);
	void	VerifConnexionMatrice(int idxER);
	void	EtatMatrice();
	void	PassageDistance();
	void	VerrouillageFaceAvant();
	void	DeverrouillageFaceAvant();
	void	PassageErreur(int num);
	BOOL	EnregistrerMatrice();
	BOOL	ChargerMatrice();

	TypeMatrice	TYPE_MATRICE;
	bool		**MATRICE_COMMUT;
	int			NB_PM;
	int			NB_ER;
};

#endif // !defined(AFX_EQPMAT_H__BE3FC12D_7AA1_42CB_92F1_8A64C41A392C__INCLUDED_)
