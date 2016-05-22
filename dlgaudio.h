/* **********************************************************************
FICHIER :	DlgAudio.h		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlgAudio

ROLE DU COMPOSANT :		Gestion de l'écran de contrôle du standard 
						AUDIO/TTY

REFRENCES EXTERNES :
	CInter :			Interrupteur 2 positions M/A
	CDiode :			Indicateur 3 états Oui/Non/Alarme

REFRENCES INTERNES :
	CDlgSimu			Ecran d'accueil du simulateur
	CDlgOutil			Boite d'outil du simulateur
***********************************************************************	*/

/* **********************************************************************
DONNEES EXTERNES
***********************************************************************	*/
#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

class CDlgAudio : public CDlgEquip
{
/* **********************************************************************
DONNEES EXTERNES
*********************************************************************** */
protected:
	CInter	m_activite;

	//{{AFX_DATA(CDlgAudio)
	enum { IDD = F4_IDD_STANDARD_AUDIO };
	CListBox	m_liste_message;
	CButton	m_synchro;
	CButton	m_cycle;
	CString	m_err_retard;
	CString	m_test;
	CString	m_periode;
	CString	m_tempo;
	//}}AFX_DATA

/* **********************************************************************
METHODE :		CDlgAudio()
TRAITEMENT:		Constuit l'objet "écran de controle" de l'équipement
***********************************************************************	*/
public:
	CDlgAudio(CWnd* pParent = NULL);   // standard constructor

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echande des donnes entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlgAudio)
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
	//{{AFX_MSG(CDlgAudio)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnKillfocusTest();
	afx_msg void OnRelais0301();
	afx_msg void OnRelais0302();
	afx_msg void OnRelais0303();
	afx_msg void OnRelais0304();
	afx_msg void OnRelais0305();
	afx_msg void OnRelais0306();
	afx_msg void OnRelais0307();
	afx_msg void OnRelais0308();
	afx_msg void OnRelais0309();
	afx_msg void OnRelais0310();
	afx_msg void OnRelais0311();
	afx_msg void OnRelais0312();
	afx_msg void OnRelais0313();
	afx_msg void OnRelais0314();
	afx_msg void OnRelais0315();
	afx_msg void OnRelais0316();
	afx_msg void OnRelais0317();
	afx_msg void OnRelais0318();
	afx_msg void OnRelais0319();
	afx_msg void OnRelais0320();
	afx_msg void OnComErreur();
	afx_msg void OnChiffre1Rx();
	afx_msg void OnChiffre1Tx();
	afx_msg void OnChiffre2Rx();
	afx_msg void OnChiffre2Tx();
	afx_msg void OnClaire1Rx();
	afx_msg void OnClaire1Tx();
	afx_msg void OnClaire2Rx();
	afx_msg void OnClaire2Tx();
	afx_msg void OnMagneto1Rx();
	afx_msg void OnMagneto1Tx();
	afx_msg void OnMagneto2Rx();
	afx_msg void OnMagneto2Tx();
	afx_msg void OnRelais0901();
	afx_msg void OnRelais0902();
	afx_msg void OnRelais0903();
	afx_msg void OnRelais0904();
	afx_msg void OnRelais0905();
	afx_msg void OnRelais0906();
	afx_msg void OnRelais0907();
	afx_msg void OnRelais0908();
	afx_msg void OnRelais0909();
	afx_msg void OnRelais0910();
	afx_msg void OnRelais0911();
	afx_msg void OnRelais0912();
	afx_msg void OnRelais0913();
	afx_msg void OnRelais0914();
	afx_msg void OnRelais0915();
	afx_msg void OnRelais0916();
	afx_msg void OnRelais0917();
	afx_msg void OnRelais0918();
	afx_msg void OnRelais0919();
	afx_msg void OnRelais0920();
	afx_msg void OnRelais1101();
	afx_msg void OnRelais1102();
	afx_msg void OnRelais1103();
	afx_msg void OnRelais1104();
	afx_msg void OnRelais1105();
	afx_msg void OnRelais1106();
	afx_msg void OnRelais1107();
	afx_msg void OnRelais1108();
	afx_msg void OnRelais1109();
	afx_msg void OnRelais1110();
	afx_msg void OnRelais1111();
	afx_msg void OnRelais1112();
	afx_msg void OnRelais1113();
	afx_msg void OnRelais1114();
	afx_msg void OnRelais1115();
	afx_msg void OnRelais1116();
	afx_msg void OnRelais1117();
	afx_msg void OnRelais1118();
	afx_msg void OnRelais1119();
	afx_msg void OnRelais1120();
	afx_msg void OnRelais1301();
	afx_msg void OnRelais1302();
	afx_msg void OnRelais1303();
	afx_msg void OnRelais1304();
	afx_msg void OnRelais1305();
	afx_msg void OnRelais1306();
	afx_msg void OnRelais1307();
	afx_msg void OnRelais1308();
	afx_msg void OnRelais1309();
	afx_msg void OnRelais1310();
	afx_msg void OnRelais1311();
	afx_msg void OnRelais1312();
	afx_msg void OnRelais1313();
	afx_msg void OnRelais1314();
	afx_msg void OnRelais1315();
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
