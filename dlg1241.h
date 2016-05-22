/* **********************************************************************
FICHIER :	Dlg1241.h		 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlg1241

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

class CDlg1241 : public CDlgEquip
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
	CInter		m_activite;
	CDiode		m_info;

public:
	//{{AFX_DATA(CDlg1241)
	enum { IDD = F5_IDD_TRC1241_FF };
	CComboBox	m_shift;
	CButton	m_parite;
	CComboBox	m_sens_manip;
	CComboBox	m_cag;
	CListBox	m_liste_message;
	CButton	m_synchro;
	CButton	m_cycle;
	CComboBox	m_mode_reception;
	CString	m_err_retard;
	CString	m_bfo;
	CString	m_canal;
	CString	m_centrage;
	CString	m_code_test;
	CString	m_cor_squelch;
	CString	m_freq_rejecteur;
	CString	m_frequence;
	CString	m_gain_hf;
	CString	m_mesureur;
	CString	m_periode;
	CString	m_tempo;
	//}}AFX_DATA

/* **********************************************************************
METHODE :		CDlg1241()
TRAITEMENT:		Constuit l'objet
***********************************************************************	*/
public:
	CDlg1241(CWnd* pParent = NULL);   // standard constructor
	virtual void GenerateurAuto();

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echande des donnes entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlg1241)
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
	//{{AFX_MSG(CDlg1241)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeModeReception();
	afx_msg void OnIdcAttenuateur0();
	afx_msg void OnIdcAttenuateur1();
	afx_msg void OnIdcAttenuateur2();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBp1();
	afx_msg void OnBp2();
	afx_msg void OnBp3();
	afx_msg void OnBp4();
	afx_msg void OnBp5();
	afx_msg void OnSelchangeCag();
	afx_msg void OnSquelch();
	afx_msg void OnSelchangeInvTg();
	afx_msg void OnComErreur();
	afx_msg void OnSelchangeShift();
	afx_msg void OnKillfocusFrequence();
	afx_msg void OnKillfocusBfo();
	afx_msg void OnRejecteur();
	afx_msg void OnKillfocusFreqReject();
	afx_msg void OnKillfocusGainHf();
	afx_msg void OnAutoMesureur();
	afx_msg void OnKillfocusMesureur();
	afx_msg void OnKillfocusCorSquelch();
	afx_msg void OnAutoCentrage();
	afx_msg void OnKillfocusCentrage();
	afx_msg void OnKillfocusCanal();
	afx_msg void OnMemoCanal();
	afx_msg void OnKillfocusCodeTest();
	afx_msg void OnModeLoc();
	afx_msg void OnModeRmt();
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
