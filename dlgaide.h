/* **********************************************************************
FICHIER :	DlgAide.h		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlgAide

ROLE DU COMPOSANT :		Affichage des écran d'aide

REFRENCES EXTERNES :
	CDlgAccueil			Ecran d'accueil du simulateur
	CDlgAffecte			Ecran d'affectation des Liaison/eqp
	CDlgConfig			Ecran de configuration
	CDlgEquip			Ecran de controle des equipement

REFRENCES INTERNES :
	Aucune
***********************************************************************	*/

/* **********************************************************************
DONNEES EXTERNES
	Aucune
***********************************************************************	*/
#include "divers\div_fic.h"

class CDlgAide : public CDialog
{
// Construction
public:
	CDlgAide(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgAide)
	enum { IDD = F0_IDD_ECRAN_HELP };
	CString	m_edit;
	//}}AFX_DATA

	char nom_ecran[80];
	char nom_fichier[80];
	char contenu[TAILLE_MAX_MESSAGE+1];
	
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgAide)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(CDlgAide)
	afx_msg void OnSize(UINT nType, int cx, int cy);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnQuitter();
	void OnSauver();

public:
	int Charge(char *fichier,char *nom);
};
