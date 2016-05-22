/* **********************************************************************
FICHIER :	Icone.h					AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _CICONE
#define _CICONE
/* **********************************************************************
NOM DU COMPOSANT:		CIcone

ROLE DU COMPOSANT :		Classe CIcone correspondant � la fen�tre d'outil
						qui Affiche ou Masque les �cran de contr�le des 
						Equipement

REFERENCES EXTERNES :
	CEquip:				Equipement associ� � l'icone
	COutil:				Barre d'outil

REFRENCES INTERNES :
	CDlgSimu			Ecran d'accueil du simlulateur
***********************************************************************	*/

/* **********************************************************************
DONNEES EXTERNES
***********************************************************************	*/
#include "Custom\outil.h"
#include "Equip\paramsim.h"

class CIcone : public CObject
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
private:
	int			type_eqp;			// Type �quipement
	char		lib[40];			// Libell� de l'icone
	BOOL		actif;				// Ecran de controle affich�
	CEquip		*Eqp;				// Equipement associ�

public:
/* **********************************************************************
METHODE :		CIcone()
TRAITEMENT:		Constructeur
***********************************************************************	*/
	CIcone(int typ,char *titre,BOOL etat,CEquip *lien);

/* **********************************************************************
METHODE :		~CIcone()
TRAITEMENT:		Destructeur
***********************************************************************	*/
	~CIcone();

/* **********************************************************************
METHODE :		Equip()
TRAITEMENT:		Retourne le type d'�quipement
***********************************************************************	*/
	int	Equip() const;

/* **********************************************************************
METHODE :		Libel()
TRAITEMENT:		Renvoi le libelle de l'icone
***********************************************************************	*/
	char*	Libel() const;

/* **********************************************************************
METHODE :		ChangeLibel()
TRAITEMENT:		Modifie le libell� associ� � l'icone
***********************************************************************	*/
	void ChangeLibel(char *titre);

/* **********************************************************************
METHODE :		Actif()
TRAITEMENT:		Retourne l'�tat de l'icone S�lectionne OUI/NON
***********************************************************************	*/
  	BOOL Actif() const;

/* **********************************************************************
METHODE :		Active()
TRAITEMENT:		S�lection/D�selectionne l'icone
***********************************************************************	*/
  	void Active(BOOL etat);

};
		
#endif
