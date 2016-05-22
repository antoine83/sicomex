// EqpAAD.h: interface for the CEquipAAD class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_EQPAAD_H__514B1256_7DE3_4A47_9A75_9F17C0947D83__INCLUDED_)
#define AFX_EQPAAD_H__514B1256_7DE3_4A47_9A75_9F17C0947D83__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Equip.h"

// Telesignalisation
const int NB_VOIES = 20;

typedef enum
{
	ABSENT0 = 0, CORRECT0 = 1, ALIM_HS0 = 2, SURCHAUFFE0 = 3
} EtatAntenne;

typedef enum
{
	ABSENT1 = 0, CORRECT1 = 1, DEFAUT1 = 2
} EtatAmpli;

class CEquipAAD:public CEquip
{
private:
	// TODO : integrer les variables et methodes privees
	int local;
public:
	CEquipAAD(int idx, int dim);
	virtual			~CEquipAAD();
	virtual void	Allocation();
	virtual BOOL	Charge_Contexte(char *fichier);
	virtual BOOL	Sauve_Contexte(char *fichier);
	BOOL			Power();
	void			Initialiser();
	BOOL			ValiderMatrice();
	void			InitialiserMatrice();
	void			ResetMatrice();
	bool			ChgtEtatMatrice(int idxAntenne, int idxVoie);
	void			InitialiserAntenne();
	void			ChgtEtatAntenne(int no_antenne, int statut);
	void			InitialiserPreampli();
	void			ChgtEtatPreampli(int no_preampli, int statut);
	void			InitialiserAmpli();
	void			ChgtEtatAmpli(int no_ampli, int statut);
	void			EtatMateriel();
	void			EtatMatrice();

	bool		**MATRICE_20_4;
	EtatAntenne	*TAB_ANTENNE;
	EtatAmpli	*TAB_PREAMPLI;
	EtatAmpli	*TAB_AMPLI;
	int			NB_ANTENNES;
	int			NB_AMPLIS;
	int			NB_PREAMPLIS;
};

#endif // !defined(AFX_EQPAAD_H__514B1256_7DE3_4A47_9A75_9F17C0947D83__INCLUDED_)
