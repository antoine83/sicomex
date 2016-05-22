/* **********************************************************************
FICHIER :	DlgAide.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgAide
***********************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "dlgaide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern 	char glob_CHEMIN[];

/////////////////////////////////////////////////////////////////////////////
// CDlgAide dialog


CDlgAide::CDlgAide(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAide::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAide)
	m_edit = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAide::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAide)
	DDX_Text(pDX, IDC_EDIT, m_edit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAide, CDialog)
	//{{AFX_MSG_MAP(CDlgAide)
	ON_WM_SIZE()
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FICHIER_QUITTER, OnQuitter)
	ON_COMMAND(ID_FICHIER_SAUVER, OnSauver)

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgAide message handlers

void CDlgAide::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	CWnd	*controle;
	
	RECT	dim;

	CDialog::OnSize(nType, cx, cy);

	GetClientRect(&dim);

	controle = GetDlgItem(IDC_EDIT);

//	if(controle->m_hWnd != NULL)
	if(controle != NULL)
		controle->MoveWindow(&dim,TRUE);
}

void CDlgAide::OnQuitter() 
{
	EndDialog(IDCANCEL);
}

int CDlgAide::Charge(char *fichier,char *nom)
{
	int		iResult;

	sprintf(nom_ecran,"Aide - %s",nom);

	strcpy(nom_fichier,fichier);

	iResult = Recup_fichier(fichier,contenu);
	if(iResult<=0) 
	{
		strcpy(contenu,"");
//		return iResult;
	}

	return 0;
}

void CDlgAide::OnSauver()
{
	int		iResult;

	UpdateData(TRUE);

	strcpy(contenu,m_edit);
	
	iResult = Stocker_fichier(nom_fichier,contenu);
//	if(iResult<0) return iResult;

	return;
}


BOOL CDlgAide::OnInitDialog() 
{
	CDialog::OnInitDialog();

	SetWindowText(nom_ecran);

	GetMenu()->EnableMenuItem(ID_FICHIER_SAUVER, MF_DISABLED | MF_GRAYED);
	
	PostMessage(WM_SIZE);

	m_edit = contenu;
	UpdateData(FALSE);

//	((CEdit*)GetDlgItem(IDC_EDIT))->SetSel(0,0,TRUE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}
