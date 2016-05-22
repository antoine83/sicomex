/* **********************************************************************
FICHIER :	Outil.h						AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _COUTIL
#define _COUTIL
/* **********************************************************************
NOM DU COMPOSANT:		COutil

ROLE DU COMPOSANT :		Classe dérivée d'un listbox permettant d'afficher
						un icone et un libelle sur chaque Ligne

REFERENCES EXTERNES :
	COutil:				Barre d'outil

REFRENCES INTERNES :
	CDlgOutil			Ecran d'accueil du simlulateur
***********************************************************************	*/

/* **********************************************************************
DONNEES EXTERNES
***********************************************************************	*/
class COutil : public CListBox
{
/* **********************************************************************
DONNEES INTERNE
***********************************************************************	*/
	HBITMAP	bmp_1;
	HBITMAP	bmp_2;
	HBITMAP	bmp_3;
	HBITMAP	bmp_4;
	HBITMAP	bmp_5;
	HBITMAP	bmp_6;
	HBITMAP	bmp_7;
	HBITMAP	bmp_8;
	HBITMAP	bmp_9;
	HBITMAP	bmp_10;
	HBITMAP	bmp_11;
	HBITMAP	bmp_12;
	HBITMAP	bmp_13;
	HBITMAP	bmp_14;
	HBITMAP	bmp_15;
	HBITMAP	bmp_16;
	HBITMAP	bmp_17;
	HBITMAP	bmp_18;
	HBITMAP	bmp_19;
	HBITMAP	bmp_20;
	HBITMAP	bmp_21;
	HBITMAP	bmp_22;
	HBITMAP	bmp_23;
	HBITMAP	bmp_24;
	HBITMAP	bmp_25;
	HBITMAP	bmp_26;
	HBITMAP	bmp_27;
	HBITMAP	bmp_28;
	HBITMAP	bmp_29;
	HBITMAP	bmp_30;
	HBITMAP	bmp_31;
	HBITMAP	bmp_32;

/* **********************************************************************
METHODE :		COutil()
TRAITEMENT:		Constructeur
***********************************************************************	*/
public:
	COutil();

/* **********************************************************************
METHODE :		~COutil()
TRAITEMENT:		Destructeur
***********************************************************************	*/
	virtual ~COutil();

/* **********************************************************************
METHODE :		DrawItem()
TRAITEMENT:		Redessine chacune des lignes de la listbox

METHODE :		MeasureItem()
TRAITEMENT:		définie la taille des ligne de la listbox
***********************************************************************	*/
	//{{AFX_VIRTUAL(COutil)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void MeasureItem(LPMEASUREITEMSTRUCT lpMeasureItemStruct);
	//}}AFX_VIRTUAL

	// Generated message map functions
protected:
	//{{AFX_MSG(COutil)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

/* *********************************************************************
METHODE :		DECLARE_MESSAGE_MAP()
TRAITEMENT:		Gestion des messages/événements de Windows
***********************************************************************	*/
	DECLARE_MESSAGE_MAP()

/* *********************************************************************
METHODE :		Profondeur()
TRAITEMENT:		Ajoute un relief sur la ligne
***********************************************************************	*/
	void Profondeur(RECT *rect,CDC *pDC,BOOL enfonce);
};

/////////////////////////////////////////////////////////////////////////////
#endif
