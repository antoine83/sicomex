/* **********************************************************************
FICHIER :	DlgEquip.h		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _CDLGEQUIP
#define _CDLGEQUIP
/* **********************************************************************
NOM DU COMPOSANT : 		CDlgEquip

ROLE DU COMPOSANT :		Classe de base des écrans de contrôle des 
						équipements et affichage du journal d'évennement

REFRENCES EXTERNES :	
	Div_fichier			Routine de gestion de fichiers
	CEquip				Classe de base des Equipements

REFRENCES INTERNES :
	CDlgAffecte			Affectation des liaisons/équipements
	CDlgOutil			Gestion de la barre d'outil
	CProto				Classe de base des protocole de communication
						(Ajoute un message d'événement au journal)
***********************************************************************	*/

#include "resource.h"
#include "Equip\Equip.h"

/* **********************************************************************
DONNEES EXTERNES
	CParamSimu *glob_paramsimu		Paramétrage du simulateur
***********************************************************************	*/
class CEquip;

class CDlgEquip : public CDialog
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
protected:
	CEquip		*equip;
	CListBox	*journal;
 	UINT 		timer;
	int			position_courante;	// dans la recherche des mot cle

	HICON 		m_hIcon;			// Icone attaché à la fenetre

	int			evolution;
public:
//	enum { IDD = 0 };


// Dialog Data
	//{{AFX_DATA(CDlgEquip)
	enum { IDD = F0_IDD_ECRAN_CONTROLE };
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgEquip)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

/* **********************************************************************
METHODE : 	OnClose()
TRAITEMENT:	interprete une demande de fermeture de fenêtre comme
			masquage de la fenetre

METHODE :		OnTimer()
TRAITEMENT:		Rafraichissement des controle en fonction des etats 
				interne de l'equipement
***********************************************************************	*/
	// Generated message map functions
	//{{AFX_MSG(CDlgEquip)
	afx_msg void OnClose();
	virtual BOOL OnInitDialog();
	afx_msg void OnAjoutMessage();
	afx_msg void OnCheckCycle();
	afx_msg void OnCheckSynchro();
	afx_msg void OnKillfocusEditCycle();
	afx_msg void OnKillfocusEditTempo();
	afx_msg void OnEnvoiStatut();
	afx_msg void OnArretStatut();
	afx_msg void OnRetireMessage();
	afx_msg void OnPrecedent();
	afx_msg void OnSuivant();
	afx_msg void OnDblclkJournal();
	afx_msg void OnPaint();
	afx_msg void OnEnvoiTrame();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

/* **********************************************************************
METHODE :		CDlgEquip()
TRAITEMENT:		Constuit l'objet "écran de controle" de l'équipement
***********************************************************************	*/
public:
	CDlgEquip(UINT nID, CWnd* pParentWnd = NULL);   // standard constructor
	virtual void GenerateurAuto();

/* **********************************************************************
METHODE :		Associe()
TRAITEMENT:		Associe un équipement à l'écran de controle
***********************************************************************	*/
	void Associe(CEquip	*eqp);

/* *********************************************************************
METHODE : 	OnOuvrir()
TRAITEMENT:	Charge un contexte d'exploitation
********************************************************************** */
	void OnOuvrir();

/* *********************************************************************
METHODE : 	OnSauver()
TRAITEMENT:	sauve un contexte d'exploitation
********************************************************************** */
	void OnSauver();

/* **********************************************************************
METHODE :		AjoutJournal()
TRAITEMENT:		Ajoute un message au journal
***********************************************************************	*/
	void AjoutJournal(char *mes,int code_erreur);

protected:
/* *********************************************************************
METHODE : 	OnCouper()
TRAITEMENT:	Efface les lignes sélectionnées du journal
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

/* *********************************************************************
METHODE : 	JouerSon()
TRAITEMENT:	Jouer un son
********************************************************************** */
	void JouerSon(LPCTSTR lpszSound);

/* *********************************************************************
METHODE : 	OnTimer()
TRAITEMENT:	Effectue les rafraichissements des controles commun à
			tous les equipement (CSequence)
********************************************************************** */
	void OnTimer();

/* *********************************************************************
METHODE : 	OnActivite()
TRAITEMENT:	Active les taches de communication et d'en voi de seq message
********************************************************************** */
	void OnActivite();

/* *********************************************************************
METHODE : 	GenerateurAuto()
TRAITEMENT:	Gestion des variations automatique de certains paramètres
********************************************************************** */
	//virtual void GenerateurAuto();

/* *********************************************************************
METHODE : 	OnTc()
TRAITEMENT:	Passage en LOCAL sur le TRC1752
********************************************************************** */
	void OnTc();

};
#endif
