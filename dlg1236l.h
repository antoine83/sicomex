/* **********************************************************************
FICHIER :	Dlg1236L.h		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlg1236LL

ROLE DU COMPOSANT :		Gestion de l'écran de contrôle de l'émetteur HF

REFRENCES EXTERNES :
	CEquipEmHF :		Equipement Emetteur HF 12 36 mode L11
	CInter :			Interrupteur 2 positions M/A
	CDiode :			Indicateur 3 états Oui/Non/Alarme

REFRENCES INTERNES :
	CDlgSimu			Ecran d'accueil du simulateur
	CDlgOutil			Boite d'outil du simulateur
***********************************************************************	*/

#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

/* **********************************************************************
DONNEES EXTERNES
***********************************************************************	*/

class CDlg1236L : public CDlgEquip
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
protected:
	CInter		m_activite;
	CDiode		m_incident;
	CInter		m_info;

public:
	//{{AFX_DATA(CDlg1236L)
	enum { IDD = F7_IDD_TRC1236_L11 };
	CComboBox	m_choix_niveau;
	CComboBox	m_fonctionnement;
	CComboBox	m_trafic;
	CListBox	m_liste_message;
	CButton	m_synchro;
	CButton	m_cycle;
	CString	m_frequence;
	CString	m_err_retard;
	CString	m_canal;
	CString	m_code_incident;
	CString	m_test;
	CString	m_niveau;
	CString	m_periode;
	CString	m_tempo;
	//}}AFX_DATA

/* **********************************************************************
METHODE :		CDlg1236L()
TRAITEMENT:		Constuit l'objet "écran de controle" de l'équipement
***********************************************************************	*/
public:
	CDlg1236L(CWnd* pParent = NULL);   // standard constructor
	virtual void GenerateurAuto();

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echande des donnes entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlg1236L)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

/* **********************************************************************
METHODE :		OnInitDialog()
TRAITEMENT:		Initialisation de la fenetre

METHODE :		OnTimer()
TRAITEMENT:		Rafraichissement des contrôles en fonction des états de
				l'équipement
***********************************************************************	*/
protected:
	//{{AFX_MSG(CDlg1236L)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeModeTrafic();
	afx_msg void OnModeDbl();
	afx_msg void OnModeLoc();
	afx_msg void OnModeRmt();
	afx_msg void OnComErreur();
	afx_msg void OnCompresseur();
	afx_msg void OnSelchangeModeFonct();
	afx_msg void OnKillfocusCodeIncident();
	afx_msg void OnKillfocusFrequence();
	afx_msg void OnAuto();
	afx_msg void OnKillfocusNiveau();
	afx_msg void OnSelchangeChoixNiveau();
	afx_msg void OnKillfocusCanal();
	afx_msg void OnMemoCanal();
	afx_msg void OnKillfocusCodeTest();
	afx_msg void OnInfo();
	//}}AFX_MSG

/* **********************************************************************
METHODE :		DECLARE_MESSAGE_MAP()
TRAITEMENT:		Gestion des messages/événements de Windows
***********************************************************************	*/
	DECLARE_MESSAGE_MAP()

/* **********************************************************************
METHODE :		OnAide()
TRAITEMENT:		Affiche un ecran d'aide sur l'utilisation de l'ecran de
				controle
***********************************************************************	*/
private:
	void OnAide();

/* *********************************************************************
METHODE : 	GenrateurAuto()
TRAITEMENT:	Effectue les variation automatique de certains paramètres
********************************************************************** */
	//virtual void GenerateurAuto();

/* **********************************************************************
METHODE :		Cerrouille()
TRAITEMENT:		Verrouillagde de la face avant pour mode local
***********************************************************************	*/
void Verrouille(BOOL etat);
};
