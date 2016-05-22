/* **********************************************************************
FICHIER :	DlgAccue.H		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlgAccueil

ROLE DU COMPOSANT :		Gestion de l'écran d'accueil

REFERENCES EXTERNES :
	CParamSimu			Paramétrage du simulateur
	CDlgConfig			Fenêtre de configuration du simulateur
	CDlgAffecte			Fenêtre d'affectation des Liaisons/Equipements
	CDlgApropos			Fenêtre d'information sur le Simulateur
	CDlgAide			Gestion des écrans d'aide
	Div_fichier			Routines de gestion de fichier

REFERENCES INTERNES :
	CSim				Instance du simulateur
***********************************************************************	*/

/* *********************************************************************
DONNEES EXTERNES :		aucune
	CParamSimu	*glob_paramsimu			Paramétrage du simulateur
	CSynchro    *glob_synchro			Gestion du top synchro
********************************************************************** */

class CDlgAccueil : public CDialog
{
/* *********************************************************************
DONNEES INTERNES :
********************************************************************** */
protected:
	BOOL		outil_affiche;		// Etat d'affichage de la boite d'outil

	HICON 		m_hIcon;			// Icone attaché à la fenetre

// Dialog Data
	//{{AFX_DATA(CDlgAccueil)
	enum { IDD = F0_IDD_SIM_ACCUEIL };
	CListBox	m_journal;
	//}}AFX_DATA


/* *********************************************************************
METHODE : 	CDlgAccueil()
TRAITEMENT:	Construit l'objet ecran d'accueil
********************************************************************** */
public:
	CDlgAccueil(CWnd* pParent = NULL);	// standard constructor

protected:
/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echange des donnees entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlgAccueil)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

/* **********************************************************************
METHODE :		OnInitDialog()
TRAITEMENT:		Initialisation de la fenetre

METHODE :		OnPaint()
TRAITEMENT:		Redessine l'icone lorsque la fenetre est iconifié

METHODE :		OnSize()
TRAITEMENT:		Sur redimenssionnement de la fenêtre

METHODE :		OnClose()
TRAITEMENT:		Avant fermeture de la fenêtre et de l'application
***********************************************************************	*/
	//{{AFX_MSG(CDlgAccueil)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnClose();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG

/* **********************************************************************
METHODE :		DECLARE_MESSAGE_MAP()
TRAITEMENT:		Gestion des messages/événements de Windows
***********************************************************************	*/
	DECLARE_MESSAGE_MAP()

/* *********************************************************************
METHODE : 	OnApropos()
TRAITEMENT:	Ouverture de la fenêtre A propos en mode Modal
********************************************************************** */
	void OnApropos();

/* *********************************************************************
METHODE : 	OnAide()
TRAITEMENT:	Ouverture de la fenêtre d'aide
********************************************************************** */
	void OnAide();

/* *********************************************************************
METHODE : 	OnNouveau()
TRAITEMENT:	Réinitialisation de l'environnement
********************************************************************** */
	void OnNouveau();

/* *********************************************************************
METHODE : 	OnOuvrir()
TRAITEMENT:	Chargement d'un fichier d'environnement
********************************************************************** */
	void OnOuvrir();

/* *********************************************************************
METHODE : 	OnSauver()
TRAITEMENT:	Sauvegarde d'un fichier d'environnement
********************************************************************** */
	void OnSauver();

/* *********************************************************************
METHODE : 	Configure_liaison()
TRAITEMENT:	Ouverture de la fenêtre de configuration du simulateur en mode 
			modale
********************************************************************** */
	void Configure_liaison();

/* *********************************************************************
METHODE : 	Parametre_liaison()
TRAITEMENT:	Ouverture de la fenêtre d'affectation Liaison/Equipement en 
			mode Modal
********************************************************************** */
	void Parametre_liaison();
	
/* *********************************************************************
METHODE : 	Affiche_outil()
TRAITEMENT:	Affichage ou masquage de la boite d'outil
********************************************************************** */
	void Affiche_outil();

/* *********************************************************************
METHODE : 	Ajoute_message()
TRAITEMENT:	Ajoute un message dans la listeBox
********************************************************************** */
public:
	void Ajout_message(char *buf);

private:
/* *********************************************************************
METHODE : 	OnCouper()
TRAITEMENT:	Efface les ligne sélectionnée du journal
********************************************************************** */
	void OnCouper();

/* *********************************************************************
METHODE : 	OnCouperTout()
TRAITEMENT:	Efface Toutes les lignes du journal
********************************************************************** */
	void OnCouperTout();

/* *********************************************************************
METHODE : 	OnSauvegarde()
TRAITEMENT:	Enregistre le contenu du journal dans un fichier ASCII
********************************************************************** */
	void OnSauvegarde();

};
