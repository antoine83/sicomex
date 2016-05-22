/* **********************************************************************
FICHIER :	Sicomex.h		 				AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT:		CSicomex

ROLE DU COMPOSANT :		Classe CSicomex (CWinApp du Sicomexulateur)

REFERENCES EXTERNES :
	CDlgSicomexu:			Ecran d'accueil

REFERENCES INTERNES :	Aucune
***********************************************************************	*/

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// main symbols

/* **********************************************************************
DONNEES EXTERNES :	Aucune
***********************************************************************	*/

class CSicomexApp : public CWinApp
{
/* **********************************************************************
DONNEES INTERNES :	Aucune
***********************************************************************	*/

/* **********************************************************************
METHODE : 		CSicomexApp()
TRAITEMENTS :	Creer une instance de l'application "Sicomexulateur"
***********************************************************************	*/
public:
	CSicomexApp();

/* *********************************************************************
METHODE : 		InitInstance()
TRAITEMENTS :	Initialisation de l'application Sicomexulateur
				Ouvre la fenêtre d'écran d'accueil en mode Modal
***********************************************************************	*/
	//{{AFX_VIRTUAL(CSicomexApp)
	public:
	virtual BOOL InitInstance();
	virtual void WinHelp(DWORD dwData, UINT nCmd = HELP_CONTEXT);
	//}}AFX_VIRTUAL

	//{{AFX_MSG(CSicomexApp)
	//}}AFX_MSG

/* **********************************************************************
METHODE :		DECLARE_MESSAGE_MAP()
TRAITEMENT:		Gestion des messages/évennements Windows
***********************************************************************	*/
	DECLARE_MESSAGE_MAP()
};
