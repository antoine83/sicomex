/* **********************************************************************
FICHIER :	Dlg251.h		 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlg251

ROLE DU COMPOSANT :		Gestion de l'écran de contrôle du récepteur HF

REFRENCES EXTERNES :
	CInter :			Interrupteur 2 positions M/A
	CDiode :			Indicateur 3 états Oui/Non/Alarme

REFRENCES INTERNES :
	CDlgSimu			Ecran d'accueil du simlulateur
	CDlgOutil			Boite d'outil du simulateur
***********************************************************************	*/

#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

/* **********************************************************************
DONNEES EXTERNES
***********************************************************************	*/

class CDlg251 : public CDlgEquip
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
	CInter		m_activite;
	CInter		m_trafic;
	CInter		m_local;
	CDiode		m_mode_console;

	CDiode		m_vitesse;

public:
	//{{AFX_DATA(CDlg251)
	enum { IDD = F9_IDD_TRC251 };
	CComboBox	m_synchro_v4;
	CComboBox	m_synchro_v3;
	CComboBox	m_synchro_v2;
	CComboBox	m_synchro_v1;
	CComboBox	m_etat_synchro;
	CComboBox	m_modulation;
	CButton	m_parite;
	CListBox	m_liste_message;
	CButton	m_synchro;
	CButton	m_cycle;
	CString	m_err_retard;
	CString	m_periode;
	CString	m_tempo;
	CString	m_canal;
	CString	m_frequence;
	CString	m_bfo;
	CString	m_fibo_v1;
	CString	m_fibo_v2;
	CString	m_fibo_v3;
	CString	m_fibo_v4;
	CString	m_defaut;
	CString	m_qbit_mini;
	CString	m_qbit_maxi;
	CString	m_peigne;
	//}}AFX_DATA

/* **********************************************************************
METHODE :		CDlg251()
TRAITEMENT:		Constuit l'objet
***********************************************************************	*/
public:
	CDlg251(CWnd* pParent = NULL);   // standard constructor
	virtual void GenerateurAuto();

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echande des donnes entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlg251)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

/* **********************************************************************
METHODE :		OnInitDialog()
TRAITEMENT:		Initialisation de la fenetre

METHODE :		OnTimer()
TRAITEMENT:		Raffraichissement des contrôle en fonction des états de
				l'équipement
***********************************************************************	*/
protected:
	//{{AFX_MSG(CDlg251)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnComErreur();
	afx_msg void OnTraffic();
	afx_msg void OnLocal();
	afx_msg void OnKillfocusCanal();
	afx_msg void OnKillfocusFrequence();
	afx_msg void OnSelchangeModulation();
	afx_msg void OnKillfocusFreqBfo();
	afx_msg void OnA1();
	afx_msg void OnA2();
	afx_msg void OnA3();
	afx_msg void OnCag();
	afx_msg void OnLimitteur();
	afx_msg void OnInterface();
	afx_msg void OnInversion();
	afx_msg void OnTest1();
	afx_msg void OnTest2();
	afx_msg void OnTest3();
	afx_msg void OnArretAlarme();
	afx_msg void OnKillfocusTestResult();
	afx_msg void OnDefautCarte1();
	afx_msg void OnDefautCarte2();
	afx_msg void OnDefautCarte3();
	afx_msg void OnAutoQbMaxi();
	afx_msg void OnAutoQbMini();
	afx_msg void OnKillfocusQbMaxi();
	afx_msg void OnKillfocusQbMini();
	afx_msg void OnSelchangeEtatSynchro();
	afx_msg void OnKillfocusFibo();
	afx_msg void OnAutoFibo();
	afx_msg void OnKillfocusPeigne();
	afx_msg void OnAutoPeigne();
	afx_msg void OnSelchangeSynchroTrame();
	afx_msg void OnMemoCanal();
	//}}AFX_MSG

/* *********************************************************************
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

/* *********************************************************************
METHODE : 	Verrouille()
TRAITEMENT:	Verrouille la face avant
********************************************************************** */
	void Verrouille(BOOL etat);
};
