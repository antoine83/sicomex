/* **********************************************************************
FICHIER :	Inter.h			 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _INTER
#define _INTER
/* **********************************************************************
NOM DU COMPOSANT : 		CInter

ROLE DU COMPOSANT :		Custom controle repésentant un interrupteur 2 position

REFRENCES EXTERNES :	Aucune

REFRENCES INTERNES :
	CDlgAccord:			Ecran de controle de la boite d'accord
	CDlgAudio:			Ecran de controle du standard Audio
	CDlgEmetHF:			Ecran de controle de l'emetteur HF
	CDlgEmRecUHF:		Ecran de controle de l'émetteur/récepteur UHF
	CDlgRecepHF			Ecran de controle du recepteur HF
	CDlgStandHF:		Ecran de controle du standard Antenne HF
***********************************************************************	*/

#define	LARG_BMP	40
#define	HAUT_BMP	40


/* **********************************************************************
DONNEES EXTERNES
***********************************************************************	*/

class CInter : public CButton
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
protected:
	BOOL	etat;
	HBITMAP	bmp_on,bmp_off;

/* **********************************************************************
METHODE :		CInter()
TRAITEMENT:		Constuit l'objet CDiode
***********************************************************************	*/
public:
	CInter();

/* **********************************************************************
METHODE :		DrawItem()
TRAITEMENT:		Affiche un bitmap en fonction de etat
***********************************************************************	*/
public:
	//{{AFX_VIRTUAL(CInter)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

/* **********************************************************************
METHODE :		~CInter()
TRAITEMENT:		Destructeur de l'objet
***********************************************************************	*/
public:
	virtual ~CInter();

/* **********************************************************************
METHODE :		Retourne_etat()
TRAITEMENT:		Retourne la valeur de etat
***********************************************************************	*/
	const BOOL	Retourne_etat();

/* **********************************************************************
METHODE :		Positionne_etat()
TRAITEMENT:		Force la valeur de etat
***********************************************************************	*/
	void		Positionne_etat(BOOL valeur);

/* **********************************************************************
METHODE :		Inverse_etat()
TRAITEMENT:		Inverse la valeur de etat
***********************************************************************	*/
	BOOL		Inverse_etat();

/* **********************************************************************
METHODE :		
TRAITEMENT:		
***********************************************************************	*/
protected:
	//{{AFX_MSG(CInter)
		// NOTE - the ClassWizard will add and remove member functions ICI
	//}}AFX_MSG

/* **********************************************************************
METHODE :		DECLARE_MESSAGE_MAP()
TRAITEMENT:		Gestion des messages/événements de Windows
***********************************************************************	*/
	DECLARE_MESSAGE_MAP()
};

#endif
