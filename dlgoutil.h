/* **********************************************************************
FICHIER :	DlgOutil.h					AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _DLGOUTIL
#define _DLGOUTIL
/* **********************************************************************
NOM DU COMPOSANT:		CDlgOutil

ROLE DU COMPOSANT :		Classe CDlgOutil correspondant à la fenêtre d'outil
						qui Affiche ou Masque les écrans de contrôle des 
						Equipements

REFERENCES EXTERNES :
	CDlgAccord:			Ecran de controle de la boite d'accord
	CDlgAudio:			Ecran de controle du standard Audio
	CDlgEmetHF:			Ecran de controle de l'émetteur HF
	CDlgEmRecUHF:		Ecran de controle de l'émetteur/récepteur UHF
	CDlgRecepHF			Ecran de controle du recepteur HF
	CDlgStandHF:		Ecran de controle du standard Antenne HF
	COutil:				Barre d'outil

REFRENCES INTERNES :
	CDlgSimu			Ecran d'accueil du simulateur
***********************************************************************	*/

/* **********************************************************************
DONNEES EXTERNES
***********************************************************************	*/
#include "Custom\outil.h"
#include "Equip\paramsim.h"
#include "Custom\Icone.h"
		
class CDlgOutil : public CDialog
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
	CObArray ListeIcone;			// Liste de pointeur sur des CIcone

   	COutil   outil;					// ListBox / Barre d'outil
public:
	//{{AFX_DATA(CDlgOutil)
	enum { IDD = F0_IDD_BARRE_OUTIL };
	//}}AFX_DATA

/* **********************************************************************
METHODE :		CDlgOutil()
TRAITEMENT:		Constuit l'objet
***********************************************************************	*/
public:
	CDlgOutil(CWnd* pParent = NULL);   // standard constructor

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echande des donnes entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlgOutil)
	public:
	virtual BOOL DestroyWindow();
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

/* **********************************************************************
METHODE :		OnInitDialog()
TRAITEMENT:		Initialisation de la fenetre

METHODE :		OnSize()
TRAITEMENT:		sur redimentionnement de la fenetre, il faut redimentionner
				la listbox représentant la barre d'outil
***********************************************************************	*/
protected:
	//{{AFX_MSG(CDlgOutil)
	virtual BOOL OnInitDialog();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg void OnSelchangeBarre();
	//}}AFX_MSG

/* **********************************************************************
METHODE :		DECLARE_MESSAGE_MAP()
TRAITEMENT:		Gestion des messages/événements de Windows
***********************************************************************	*/
	DECLARE_MESSAGE_MAP()

/* **********************************************************************
METHODE :		Ajoute_icone()
TRAITEMENT:		Ajoute un icone dans la barre d'outil et retourne handle
***********************************************************************	*/
public:
	CIcone *Ajoute_icone(int typ,char *titre,BOOL etat,CEquip *lien);

/* **********************************************************************
METHODE :		ChangeNomcone(char *titre BOOL etat)
TRAITEMENT:		Ajoute un icone dans la barre d'outil et retourne handle
***********************************************************************	*/
	void ChangeNomIcone(CIcone *element,char *titre,BOOL etat);

/* **********************************************************************
METHODE :		Retire_icone()
TRAITEMENT:		Retire un icone de la barre d'outil
***********************************************************************	*/
	void Retire_icone(CIcone *element);

/* **********************************************************************
METHODE :		MasqueEcran
TRAITEMENT:		Masque l'ecran de controle lie à l'icone
***********************************************************************	*/
	void MasqueEcran(CIcone *element);
};
#endif
