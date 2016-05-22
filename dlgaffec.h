/* **********************************************************************
FICHIER :	DlgAffec.h		 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlgAffecte

ROLE DU COMPOSANT :		Affectation des liaisons/�quipements

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
TRAITEMENT:		Construit la fen�tre d'affectation des liaisons/�quipement
***********************************************************************	*/
public:
	CDlgAffecte(CWnd* pParent = NULL);   // standard constructor

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echange des donn�es entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlgAffecte)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

/* **********************************************************************
METHODE :		OnHelp();
TRAITEMENT:		Affiche un �cran d'aide

METHODE :		OnInitDialog()
TRAITEMENT:		Initialisation de la fenetre � partir des donn�es de 
				CParamSimu

METHODE :		OnOK()
TRAITEMENT:		Prise en compte de la modification des donn�es dans 
				CParamSimu



METHODE :		OnSelchangeIdcPort
TRAITEMENT:		Sur changement de s�lection de la liaison, affiche les
				caract�ristiques de la liaison

METHODE :		OnKillfocusIdcEditRepere
TRAITEMENT:		Sur modification du repere de l'affectation

METHODE :		OnSelchangeIdcEquip
TRAITEMENT:		Sur modification du type d'�quipement de l'affectation

METHODE :		OnDcRadioD1
TRAITEMENT:		Sur s�lection de 5 bit de donn�es

METHODE :		OnDcRadioD2
TRAITEMENT:		Sur s�lection de 6 bit de donn�es

METHODE :		OnDcRadioD3
TRAITEMENT:		Sur s�lection de 7 bit de donn�es

METHODE :		OnDcRadioD4
TRAITEMENT:		Sur s�lection de 8 bit de donn�es

METHODE :		OnDcRadioV1
TRAITEMENT:		Sur s�lection de 1200 bauds pour la vitesse de transmis.

METHODE :		OnDcRadioV2
TRAITEMENT:		Sur s�lection de 2400 bauds pour la vitesse de transmis.

METHODE :		OnDcRadioV3
TRAITEMENT:		Sur s�lection de 4800 bauds pour la vitesse de transmis.

METHODE :		OnDcRadioV4
TRAITEMENT:		Sur s�lection de 9600 bauds pour la vitesse de transmis.

METHODE :		OnDcRadioV5
TRAITEMENT:		Sur s�lection de 19200 bauds pour la vitesse de transmis.

METHODE :		OnDcRadioA1
TRAITEMENT:		Sur s�lection de 1 bit d'arret

METHODE :		OnDcRadioA2
TRAITEMENT:		Sur s�lection de 1,5 bit d'arret

METHODE :		OnDcRadioA3
TRAITEMENT:		Sur s�lection de 2 bit d'arret

METHODE :		OnDcRadioP1
TRAITEMENT:		Sur s�lection de sans parit�

METHODE :		OnDcRadioP2
TRAITEMENT:		Sur s�lection de parit� paire

METHODE :		OnDcRadioP3
TRAITEMENT:		Sur s�lection de parit� impaire

METHODE :		afx_msg void OnIdcControle
TRAITEMENT:		Sur s�lection/d�s�lection de l'affichage l'�cran de 
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
TRAITEMENT:		Gestion des messages/�v�nements de Windows
***********************************************************************	*/
	DECLARE_MESSAGE_MAP()

/* **********************************************************************
METHODE :		Format()
TRAITEMENT:		Affichage du format m�moris� de la liaison s�lectionn�
***********************************************************************	*/
	void Format(int	idx);

};
