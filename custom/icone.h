/* **********************************************************************
FICHIER :	Icone.h					AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _CICONE
#define _CICONE
/* **********************************************************************
NOM DU COMPOSANT:		CIcone

ROLE DU COMPOSANT :		Classe CIcone correspondant à la fenêtre d'outil
						qui Affiche ou Masque les écran de contrôle des 
						Equipement

REFERENCES EXTERNES :
	CEquip:				Equipement associé à l'icone
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
	int			type_eqp;			// Type équipement
	char		lib[40];			// Libellé de l'icone
	BOOL		actif;				// Ecran de controle affiché
	CEquip		*Eqp;				// Equipement associé

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
TRAITEMENT:		Retourne le type d'équipement
***********************************************************************	*/
	int	Equip() const;

/* **********************************************************************
METHODE :		Libel()
TRAITEMENT:		Renvoi le libelle de l'icone
***********************************************************************	*/
	char*	Libel() const;

/* **********************************************************************
METHODE :		ChangeLibel()
TRAITEMENT:		Modifie le libellé associé à l'icone
***********************************************************************	*/
	void ChangeLibel(char *titre);

/* **********************************************************************
METHODE :		Actif()
TRAITEMENT:		Retourne l'état de l'icone Sélectionne OUI/NON
***********************************************************************	*/
  	BOOL Actif() const;

/* **********************************************************************
METHODE :		Active()
TRAITEMENT:		Sélection/Déselectionne l'icone
***********************************************************************	*/
  	void Active(BOOL etat);

};
		
#endif
