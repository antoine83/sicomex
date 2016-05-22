/* **********************************************************************
FICHIER :	DlgAffec.h		 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlgAffecte

ROLE DU COMPOSANT :		Affectation des liaisons/équipements

REFRENCES EXTERNES :
	CDlgAide			Gestion des écrans d'aide

REFRENCES INTERNES :
	CDlgSimu			Ecran d'accueil du simulateur
***********************************************************************	*/

/* **********************************************************************
DONNEES EXTERNES
	CParamSimu glob_paramsimu :	Paramétrage du simulateur
***********************************************************************	*/
#include "Equip\ParamSim.h"

class CDlgAffecte : public CDialog
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
public:
	//{{AFX_DATA(CDlgAffecte)
	enum { IDD = F0_IDD_LIAISON };
	CComboBox	m_type;
	CComboBox	m_port;
	CString	m_repere;
	//}}AFX_DATA

	int		index[NB_MAX_LIAISON];
	t_affecte	ligne[NB_MAX_LIAISON];

/* **********************************************************************
METHODE :		CDlgAffecte()
TRAITEMENT:		Construit la fenêtre d'affectation des liaisons/équipement
***********************************************************************	*/
public:
	CDlgAffecte(CWnd* pParent = NULL);   // standard constructor

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echange des données entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlgAffecte)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

/* **********************************************************************
METHODE :		OnHelp();
TRAITEMENT:		Affiche un écran d'aide

METHODE :		OnInitDialog()
TRAITEMENT:		Initialisation de la fenetre à partir des données de 
				CParamSimu

METHODE :		OnOK()
TRAITEMENT:		Prise en compte de la modification des données dans 
				CParamSimu



METHODE :		OnSelchangeIdcPort
TRAITEMENT:		Sur changement de sélection de la liaison, affiche les
				caractéristiques de la liaison

METHODE :		OnKillfocusIdcEditRepere
TRAITEMENT:		Sur modification du repere de l'affectation

METHODE :		OnSelchangeIdcEquip
TRAITEMENT:		Sur modification du type d'équipement de l'affectation

METHODE :		OnDcRadioD1
TRAITEMENT:		Sur sélection de 5 bit de données

METHODE :		OnDcRadioD2
TRAITEMENT:		Sur sélection de 6 bit de données

METHODE :		OnDcRadioD3
TRAITEMENT:		Sur sélection de 7 bit de données

METHODE :		OnDcRadioD4
TRAITEMENT:		Sur sélection de 8 bit de données

METHODE :		OnDcRadioV1
TRAITEMENT:		Sur sélection de 1200 bauds pour la vitesse de transmis.

METHODE :		OnDcRadioV2
TRAITEMENT:		Sur sélection de 2400 bauds pour la vitesse de transmis.

METHODE :		OnDcRadioV3
TRAITEMENT:		Sur sélection de 4800 bauds pour la vitesse de transmis.

METHODE :		OnDcRadioV4
TRAITEMENT:		Sur sélection de 9600 bauds pour la vitesse de transmis.

METHODE :		OnDcRadioV5
TRAITEMENT:		Sur sélection de 19200 bauds pour la vitesse de transmis.

METHODE :		OnDcRadioA1
TRAITEMENT:		Sur sélection de 1 bit d'arret

METHODE :		OnDcRadioA2
TRAITEMENT:		Sur sélection de 1,5 bit d'arret

METHODE :		OnDcRadioA3
TRAITEMENT:		Sur sélection de 2 bit d'arret

METHODE :		OnDcRadioP1
TRAITEMENT:		Sur sélection de sans parité

METHODE :		OnDcRadioP2
TRAITEMENT:		Sur sélection de parité paire

METHODE :		OnDcRadioP3
TRAITEMENT:		Sur sélection de parité impaire

METHODE :		afx_msg void OnIdcControle
TRAITEMENT:		Sur sélection/désélection de l'affichage l'écran de 
				controle
***********************************************************************	*/
	//{{AFX_MSG(CDlgAffecte)
	afx_msg void OnHelp();
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnSelchangeIdcPort();
	afx_msg void OnKillfocusIdcEditRepere();
	afx_msg void OnSelchangeIdcEquip();
	afx_msg void OnDcRadioD1();
	afx_msg void OnIdcRadioD2();
	afx_msg void OnIdcRadioD3();
	afx_msg void OnIdcRadioD4();
	afx_msg void OnIdcRadioV1();
	afx_msg void OnIdcRadioV2();
	afx_msg void OnIdcRadioV3();
	afx_msg void OnIdcRadioV4();
	afx_msg void OnIdcRadioV5();
	afx_msg void OnIdcRadioA1();
	afx_msg void OnIdcRadioA2();
	afx_msg void OnIdcRadioA3();
	afx_msg void OnIdcRadioP1();
	afx_msg void OnIdcRadioP2();
	afx_msg void OnIdcRadioP3();
	afx_msg void OnIdcControle();
	afx_msg void OnDestroy();
	afx_msg void OnIdcRadioV10();
	afx_msg void OnIdcRadioV11();
	afx_msg void OnIdcRadioV12();
	afx_msg void OnIdcRadioV6();
	afx_msg void OnIdcRadioV7();
	afx_msg void OnIdcRadioV8();
	afx_msg void OnIdcRadioV9();
	afx_msg void OnIdcRadioV18();
	afx_msg void OnIdcRadioV13();
	afx_msg void OnIdcRadioV14();
	afx_msg void OnIdcRadioV15();
	afx_msg void OnIdcRadioV16();
	afx_msg void OnIdcRadioV17();
	//}}AFX_MSG

/* **********************************************************************
METHODE :		DECLARE_MESSAGE_MAP()
TRAITEMENT:		Gestion des messages/événements de Windows
***********************************************************************	*/
	DECLARE_MESSAGE_MAP()

/* **********************************************************************
METHODE :		Format()
TRAITEMENT:		Affichage du format mémorisé de la liaison sélectionné
***********************************************************************	*/
	void Format(int	idx);

};
