/* **********************************************************************
FICHIER :	DlgAccor.h		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlgAccord

ROLE DU COMPOSANT :		Gestion de l'écran de contrôle de la boite 
						d'accrod antenne

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
DONNEES EXTERNES :		aucune
***********************************************************************	*/

class CDlgAccord : public CDlgEquip
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
protected:
	CInter			m_activite;		// Interrupteur M/A pour mise en route
	CInter			m_manuel;		// Interrupteur M/A pour mise en route
	CInter			m_no_xmit;

	CDiode			m_impedance;
	CDiode			m_ros;
	CDiode			m_tun;
	CDiode			m_tmp;

public:
	//{{AFX_DATA(CDlgAccord)
	enum { IDD = F2_IDD_ACCORD_ANTENNE };
	CComboBox	m_etat;
	CComboBox	m_accord;
	CComboBox	m_operation;
	CComboBox	m_selecte_alarme;
	CListBox	m_liste_message;
	CButton	m_synchro;
	CButton	m_cycle;
	CListBox	m_journal;
	CString	m_alarme;
	CString	m_capacite;
	CString	m_frequence;
	CString	m_inductance;
	CString	m_tos;
	CString	m_periode;
	CString	m_tempo;
	CString	m_err_retard;
	//}}AFX_DATA

/* **********************************************************************
METHODE :		CDlgAccord()
TRAITEMENT:		Constuit l'objet "écran de controle" de l'équipement
***********************************************************************	*/
public:
	CDlgAccord(CWnd* pParent = NULL);   // standard constructor
	virtual void GenerateurAuto();

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echande des donnes entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlgAccord)
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
	//{{AFX_MSG(CDlgAccord)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnComErreur();
	afx_msg void OnSelchangeSelecteAlarme();
	afx_msg void OnKillfocusAlarme();
	afx_msg void OnManuel();
	afx_msg void OnKillfocusFrequence();
	afx_msg void OnSelchangeOperation();
	afx_msg void OnNoXmit();
	afx_msg void OnSelchangeAccord();
	afx_msg void OnKillfocusCapacite();
	afx_msg void OnKillfocusInductance();
	afx_msg void OnKillfocusTos();
	afx_msg void OnAutoCapa();
	afx_msg void OnAutoInduc();
	afx_msg void OnAutoTos();
	afx_msg void OnSelchangeEtat();
	afx_msg void OnIndetermine();
	afx_msg void OnAccorde();
	afx_msg void OnLargeBande();
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

};
