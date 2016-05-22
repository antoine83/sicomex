/* **********************************************************************
FICHIER :	Diode.h			 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _DIODE
#define _DIODE
/* **********************************************************************
NOM DU COMPOSANT : 		CDiode

ROLE DU COMPOSANT :		Custom controle repésentant une diode à 3 états

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

#define ETAT_ON		1
#define ETAT_OFF	0
#define ETAT_ERR	-1


/* **********************************************************************
DONNEES EXTERNES
***********************************************************************	*/

class CDiode : public CButton
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
protected:
	int		etat;
	HBITMAP	bmp_on,bmp_off,bmp_err;

/* **********************************************************************
METHODE :		CDiode()
TRAITEMENT:		Constuit l'objet CDiode
***********************************************************************	*/
public:
	CDiode();

/* **********************************************************************
METHODE :		DrawItem()
TRAITEMENT:		Affiche un bitmap en fonction de etat
***********************************************************************	*/
	//{{AFX_VIRTUAL(Cdiode)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	//}}AFX_VIRTUAL

/* **********************************************************************
METHODE :		~CDiode()
TRAITEMENT:		Destructeur de l'objet
***********************************************************************	*/
public:
	virtual ~CDiode();

/* **********************************************************************
METHODE :		Retourne_etat()
TRAITEMENT:		Retourne la valeur de etat
***********************************************************************	*/
	const BOOL	Retourne_etat();

/* **********************************************************************
METHODE :		Positionne_etat()
TRAITEMENT:		Modifie la valeur de etat
***********************************************************************	*/
	void		Positionne_etat(int valeur);

/* **********************************************************************
METHODE :		
TRAITEMENT:		
***********************************************************************	*/
protected:
	//{{AFX_MSG(Cdiode)
	//}}AFX_MSG

/* **********************************************************************
METHODE :		DECLARE_MESSAGE_MAP()
TRAITEMENT:		Gestion des messages/événements de Windows
***********************************************************************	*/
	DECLARE_MESSAGE_MAP()
};

#endif
