/* **********************************************************************
FICHIER :	DlgAprop.h		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlgApropos

ROLE DU COMPOSANT :		Gestion de la fenêtre d'information sur le 
						Simulateur

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :
	CDlgSimu			Ecran d'accueil du simulateur
***********************************************************************	*/

/* **********************************************************************
DONNEES EXTERNES
***********************************************************************	*/

class CDlgApropos : public CDialog
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
public:
	//{{AFX_DATA(CDlgApropos)
	enum { IDD = F0_IDD_ABOUTBOX };
	//}}AFX_DATA

/* **********************************************************************
METHODE :		CDlgApropos()
TRAITEMENT:		Construit la fenetre d'information
***********************************************************************	*/
public:
	CDlgApropos();

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echange des données entre controle et 
				dialogBox
***********************************************************************	*/
protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

/* **********************************************************************
METHODE :		OnInitDialog()
TRAITEMENT:		Initialisation de la fenetre
***********************************************************************	*/
	//{{AFX_MSG(CDlgApropos)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	
	
/* **********************************************************************
METHODE :		DECLARE_MESSAGE_MAP()
TRAITEMENT:		Gestion des messages/événements de Windows
***********************************************************************	*/
DECLARE_MESSAGE_MAP()
};
