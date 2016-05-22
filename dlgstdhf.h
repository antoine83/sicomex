/* **********************************************************************
FICHIER :	DlgStdHF.h		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlgStandHF

ROLE DU COMPOSANT :		Gestion de l'écran de contrôle du standard antenne
						HF

REFRENCES EXTERNES :
	CEquipStd :			Equipement Standard d'antenne
	CInter :			Interrupteur 2 positions M/A
	CDiode :			Indicateur 3 états Oui/Non/Alarme

REFRENCES INTERNES :
	CDlgSimu			Ecran d'accueil du simlulateur
	CDlgOutil			Boite d'outil du simulateur
***********************************************************************	*/

#include "Custom\Inter.h"
#include "Custom\Diode.h"
#include "DlgEquip.h"

/* **********************************************************************
DONNEES EXTERNES		aucune
***********************************************************************	*/

class CDlgStandHF : public CDlgEquip
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
	CInter	m_activite;
	CInter	m_incorrect;
	CInter	m_silence;

	CInter	m_xmit_1;
	CInter	m_mat_1;

	CInter	m_xmit_2;
	CInter	m_mat_2;

public:
	//{{AFX_DATA(CDlgStandHF)
	enum { IDD = F1_IDD_STANDARD_HF };
	CListBox	m_liste_message;
	CButton	m_synchro;
	CButton	m_cycle;
	CString	m_err_retard;
	CString	m_avarie;
	CString	m_periode;
	CString	m_tempo;
	//}}AFX_DATA

/* **********************************************************************
METHODE :		CDlgStandHF()
TRAITEMENT:		Constuit l'objet "écran de controle" de l'équipement
***********************************************************************	*/
public:
	CDlgStandHF(CWnd* pParent = NULL);   // standard constructor

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echange des données entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlgStandHF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

/* **********************************************************************
METHODE :		OnInitDialog()
TRAITEMENT:		Initialisation de la fenetre

METHODE :		OnActivite()
TRAITEMENT:		Mise en route de l'équipement

METHODE :		OnTimer()
TRAITEMENT:		Rafraichissement des contrôles en fonction des états de
				l'équipement
***********************************************************************	*/
protected:
	//{{AFX_MSG(CDlgStandHF)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAbsence();
	afx_msg void OnAccord();
	afx_msg void OnKillfocusAvarie();
	afx_msg void OnBaa1();
	afx_msg void OnBaa2();
	afx_msg void OnEm1();
	afx_msg void OnEm2();
	afx_msg void OnEtat();
	afx_msg void OnHissage();
	afx_msg void OnNoXmit();
	afx_msg void OnRec1();
	afx_msg void OnRec2();
	afx_msg void OnRlb();
	afx_msg void OnSilence();
	afx_msg void OnComErreur();
	afx_msg void OnDistance();
	afx_msg void OnLocal();
	afx_msg void OnMat1();
	afx_msg void OnMat2();
	afx_msg void OnTemp();
	afx_msg void OnXmit1();
	afx_msg void OnXmit2();
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
};
