/* **************************************************************************
FICHIER :	DlgAprop.CPP		 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgApropos
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "DlgAprop.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CDlgApropos::CDlgApropos() : CDialog(CDlgApropos::IDD)
{
	//{{AFX_DATA_INIT(CDlgApropos)
	//}}AFX_DATA_INIT
}

void CDlgApropos::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgApropos)
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgApropos, CDialog)
	//{{AFX_MSG_MAP(CDlgApropos)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgApropos message handlers

BOOL CDlgApropos::OnInitDialog()
{
	CDialog::OnInitDialog();
	CenterWindow();
	
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}
