/* **************************************************************************
FICHIER :	Sicomex.cpp		 				AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 03/07/12
VERSION :	3.0
ROLE :		Implémentation de la classe CSicomex
***************************************************************************	*/
#include "stdafx.h"
#include "Sicomex.h"
#include "DlgAccue.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

#include <stdio.h>
#include <tchar.h>


BEGIN_MESSAGE_MAP(CSicomexApp, CWinApp)
	//{{AFX_MSG_MAP(CSicomexApp)
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CSicomexApp construction

CSicomexApp::CSicomexApp()
{
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CSicomexApp object

CSicomexApp theApp;

/////////////////////////////////////////////////////////////////////////////
// CSicomexApp initialization

BOOL CSicomexApp::InitInstance()
{
	// Standard initialization
	// If you are not using these features and wish to reduce the size
	//  of your final executable, you should remove from the following
	//  the specific initialization routines you do not need.

	Enable3dControls();
	LoadStdProfileSettings();  // Load standard INI file options (including MRU)

	
	CDlgAccueil dlg;
	m_pMainWnd = &dlg;
	int nResponse = dlg.DoModal();
	if (nResponse == IDOK)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with OK
	}
	else if (nResponse == IDCANCEL)
	{
		// TODO: Place code here to handle when the dialog is
		//  dismissed with Cancel
	}


	// Since the dialog has been closed, return FALSE so that we exit the
	//  application, rather than start the application's message pump.

	return FALSE;
}

void CSicomexApp::WinHelp(DWORD dwData, UINT nCmd) 
{
	// TODO: Add your specialized code here and/or call the base class
	
	// 	CWinApp::WinHelp(dwData, nCmd);
}
