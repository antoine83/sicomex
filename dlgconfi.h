/* **********************************************************************
FICHIER :	DlgConfi.h			 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlgConfig

ROLE DU COMPOSANT :		Gestion de l'�cran de configuration du simulateur

REFRENCES EXTERNES :
	CDlgAide			Gestion des �crans d'aide

REFRENCES INTERNES :
	CDlgSimu			Ecran d'accueil du simulateur
***********************************************************************	*/

/* **********************************************************************
DONNEES EXTERNES
	CParamSimu glob_paramsimu :	Param�trage du simulateur
***********************************************************************	*/
#include "Equip\ParamSim.h"

class CDlgConfig : public CDialog
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
public:
	//{{AFX_DATA(CDlgConfig)
	enum { IDD = F0_IDD_CONFIGURATION };
	CButton	m_top_externe;
	CButton	m_affectable;
	CListBox	m_liste_liaison;
	UINT	m_num_port;
	UINT	m_nb_liaison;
	UINT	m_taille;
	UINT	m_periode;
	CString	m_depart;
	//}}AFX_DATA

// Etat temporaire jusqu'a validation
	UINT	nb_liaison;					// Etat en cours de modification
	BOOL	affecte[NB_MAX_LIAISON];	// affectable

	UINT	taille;						// Taille des journaux

	BOOL	top_externe;
	int		depart;
	int		periode;

/* **********************************************************************
METHODE :		CDlgConfig()
TRAITEMENT:		Constuit l'objet fenetre de configuration
***********************************************************************	*/
public:
	CDlgConfig(CWnd* pParent = NULL);   // standard constructor

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echange des donn�es entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlgConfig)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

/* **********************************************************************
METHODE :		OnInitDialog()
TRAITEMENT:		Initialisation de la fenetre � partir des donn�es de 
				CParamSimu

METHODE :		KillfocusIdcNbLiaison()
TRAITEMENT:		Sur modification du nombre de liaison, cette methode
				effectue un rafraichissement de la liste des liaisons

METHODE :		OnOK()
TRAITEMENT:		Prose en compte de la modification des donn�es dans 
				CParamSimu

METHODE :		OnSelchangeIdcListeLiaison()
TRAITEMENT:		Affichage de l'�tat de l'affectabilit� de la liaison
				s�lectionn�e dans la liste
	
METHODE :		OnIdcAffectable();
TRAITEMENT:		Modification de l'affectabilit� de la liaison s�lectionn�e

METHODE :		OnKillfocusIdcTailleJournaux();
TRAITEMENT:		Sur modification de la taille des journaux

METHODE :		OnIdcTopExterne();
TRAITEMENT:		Sur s�lection/d�s�lection du Top externe

METHODE :		OnKillfocusIdcTopDepart();
TRAITEMENT:		Sur modification de l'heure de d�part du Top synchro

METHODE :		OnKillfocusIdcTopPeriode();
TRAITEMENT:		Sur modification de la p�riode du top synchro

METHODE :		OnHelp();
TRAITEMENT:		Affiche un �cran d'aide
***********************************************************************	*/
protected:
	//{{AFX_MSG(CDlgConfig)
	virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusIdcNbLiaison();
	virtual void OnOK();
	afx_msg void OnSelchangeIdcListeLiaison();
	afx_msg void OnIdcAffectable();
	afx_msg void OnKillfocusIdcTailleJournaux();
	afx_msg void OnIdcTopExterne();
	afx_msg void OnKillfocusIdcTopDepart();
	afx_msg void OnKillfocusIdcTopPeriode();
	afx_msg void OnHelp();
	afx_msg void OnDblclkIdcListeLiaison();
	afx_msg void OnDestroy();
	//}}AFX_MSG

/* **********************************************************************
METHODE :		DECLARE_MESSAGE_MAP()
TRAITEMENT:		Gestion des messages/�v�nements de Windows
***********************************************************************	*/
	DECLARE_MESSAGE_MAP()

/* **********************************************************************
METHODE :		Rafraichir_liste()
TRAITEMENT:		Rafraichit la liste des liaisons
***********************************************************************	*/
private:
void Rafraichir_liste(); 
};
