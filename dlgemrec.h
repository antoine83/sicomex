/* **********************************************************************
FICHIER :	DlgEmRec.h		 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlgEmRecUHF

ROLE DU COMPOSANT :		Gestion de l'écran de contrôle de l'émetteur/
						récepteur HF

REFRENCES EXTERNES :
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

class CDlgEmRecUHF : public CDlgEquip
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
protected:
	CInter		m_activite;
	CInter		m_local;
	CInter		m_silence;
	CInter		m_scan;
	CInter		m_hf;
	CInter		m_ros;
	CInter		m_bf;
	CInter		m_emission;

	CInter		m_accord_en_cours;

	CDiode		m_accord;
	CInter		m_rec_garde;

	CInter		m_panne_emr;
	CInter		m_panne_accord;

public:
	//{{AFX_DATA(CDlgEmRecUHF)
	enum { IDD = F6_IDD_TRBM18A };
	CComboBox	m_relais;
	CComboBox	m_pas_rec;
	CComboBox	m_pas_em;
	CComboBox	m_antenne;
	CComboBox	m_mode;
	CComboBox	m_niveau;
	CListBox	m_liste_message;
	CButton	m_synchro;
	CButton	m_cycle;
	CString	m_err_retard;
	CString	m_adresse;
	CString	m_canal;
	CString	m_cle_crypto;
	CString	m_code_test;
	CString	m_freq_em;
	CString	m_freq_rec;
	CString	m_gene_crypto;
	CString	m_scan_deb;
	CString	m_scan_fin;
	CString	m_periode;
	CString	m_tempo;
	//}}AFX_DATA
/* **********************************************************************
METHODE :		CDlgAccord()
TRAITEMENT:		Constuit l'objet
***********************************************************************	*/
public:
	CDlgEmRecUHF(CWnd* pParent = NULL);   // standard constructor

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echande des donnes entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlgEmRecUHF)
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
	//{{AFX_MSG(CDlgEmRecUHF)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKillfocusFreqEm();
	afx_msg void OnKillfocusFreqRec();
	afx_msg void OnComErreur();
	afx_msg void OnKillfocusCanal();
	afx_msg void OnSelchangeNiveau();
	afx_msg void OnSelchangeMode();
	afx_msg void OnNb();
	afx_msg void OnWb();
	afx_msg void OnKillfocusCleCrypto();
	afx_msg void OnSelchangeAntenne();
	afx_msg void OnSquelch();
	afx_msg void OnSelchangePasEm();
	afx_msg void OnSelchangePasRec();
	afx_msg void OnProtection();
	afx_msg void OnSelchangeRelais();
	afx_msg void OnRecGarde();
	afx_msg void OnKillfocusScanDeb();
	afx_msg void OnKillfocusScanFin();
	afx_msg void OnKillfocusAdresse();
	afx_msg void OnKillfocusGeneCrypto();
	afx_msg void OnLocal();
	afx_msg void OnHf();
	afx_msg void OnRos();
	afx_msg void OnEmission();
	afx_msg void OnSilence();
	afx_msg void OnBf();
	afx_msg void OnScan();
	afx_msg void OnKillfocusCodeTest();
	afx_msg void OnMemoCanal();
	afx_msg void OnPanneAccord();
	afx_msg void OnPanneEmr();
	afx_msg void OnAccordEnCours();
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
METHODE : 	Verrouille()
TRAITEMENT:	Verrouille la face avant
********************************************************************** */
	void Verrouille(BOOL etat);

};
