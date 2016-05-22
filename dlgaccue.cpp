/* **************************************************************************
FICHIER :	DlgAccue.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgAccueil
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"

#include "DlgAccue.h"
#include "DlgAprop.h"		// Boite de dialogue d'information sur le logiciel
#include "DlgConfi.h"		// Fenêtre de configuration
#include "DlgAffec.h"		// Fenêtre d'affectation des Liaisons/Equipements
#include "DlgAide.h"		// Fenêtre d'affectation des Liaisons/Equipements

#include "divers\div_fic.h"		// Fenêtre d'affectation des Liaisons/Equipements
#include "global.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern	CParamSimu 	*glob_paramsimu;
extern char glob_HELP_ACCUEIL[];
const int	TAILLE_MESSAGE=81;

CDlgAccueil::CDlgAccueil(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAccueil::IDD, pParent)
{

	//{{AFX_DATA_INIT(CDlgAccueil)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	// Note that LoadIcon does not require a subsequent DestroyIcon in Win32
	m_hIcon = AfxGetApp()->LoadIcon(IDI_SICOMEX);

	glob_paramsimu = new CParamSimu;
	glob_synchro = new CSynchro;
	glob_barre = new CDlgOutil;

	GetCurrentDirectory(80, glob_CHEMIN);
	GetCurrentDirectory(80, glob_REPERTOIRE);
	

}

void CDlgAccueil::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAccueil)
	DDX_Control(pDX, IDC_JOURNAL, m_journal);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlgAccueil, CDialog)
	//{{AFX_MSG_MAP(CDlgAccueil)
	ON_WM_PAINT()
	ON_WM_SIZE()
	ON_WM_CLOSE()
	ON_WM_TIMER()
	//}}AFX_MSG_MAP

	ON_COMMAND(ID__APROPOS, OnApropos)
	ON_COMMAND(ID__AIDE, OnAide)
 	ON_COMMAND(ID_ENV_QUITTER, OnClose)

	ON_COMMAND(ID_ENV_NOUVEAU, OnNouveau)
	ON_COMMAND(ID_ENV_OUVRIR, OnOuvrir)
	ON_COMMAND(ID_ENV_SAUVER, OnSauver)

	ON_COMMAND(ID_PARA_CONFIGURATION, Configure_liaison)
	ON_COMMAND(ID_PARA_LIAISON, Parametre_liaison)

	ON_COMMAND(ID_JOURNAL_COUPER, OnCouper)
	ON_COMMAND(ID_JOURNAL_COUPERTOUT, OnCouperTout)
	ON_COMMAND(ID_JOURNAL_ENREGISTRERSOUS, OnSauvegarde)

	ON_COMMAND(ID_AFF_OUTIL, Affiche_outil)
//	ON_COMMAND(ID_AFF_MOSAIQUE, Mosaique)
//	ON_COMMAND(ID_AFF_CASCADE, Casacade)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgAccueil message handlers

void CDlgAccueil::OnApropos() 
{
	CDlgApropos W0;
	W0.DoModal();	
}

void CDlgAccueil::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_ACCUEIL,"Ecran d'accueil du Simulateur");
	if(iResult >=  0) win.DoModal();
}

void CDlgAccueil::OnNouveau()
{
	glob_paramsimu->Init_Environ();
}

void CDlgAccueil::OnOuvrir()
{
	int		iResult;
	char	fichier[80]="";
	CFileDialog win(TRUE,"env",fichier,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		,"Environnement (*.env)|*.env|Fichier ASCII (*.txt)|*.txt|Tous les Fichiers (*.*)|*.*||"
 		,this);

	win.m_ofn.Flags &= ~OFN_SHOWHELP;
	win.m_ofn.Flags &= ~524288;		//OFN_EXPLORER;

	iResult = win.DoModal();
	if(iResult != IDOK) return;

	strcpy(fichier,win.GetPathName()); 

	BeginWaitCursor( );
	glob_paramsimu->Charger_Environ(fichier);
	EndWaitCursor( );
}

void CDlgAccueil::OnSauver()
{
	int		iResult;
	char	fichier[80]="";
	CFileDialog win(FALSE,"env",fichier,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		,"Environnement (*.env)|*.env|Fichier ASCII (*.txt)|*.txt|Tous les Fichiers (*.*)|*.*||"
 		,this);
	 	 
	win.m_ofn.Flags &= ~OFN_SHOWHELP;
	win.m_ofn.Flags &= ~524288;		//OFN_EXPLORER;

	iResult = win.DoModal();
	if(iResult != IDOK) return;

	strcpy(fichier,win.GetPathName()); 

	glob_paramsimu->Sauvegarder_Environ(fichier);
}

BOOL CDlgAccueil::OnInitDialog() 
{
	RECT	rect;

	CDialog::OnInitDialog();

//	Armement du timer
	SetTimer(1,1000,NULL);	

	glob_barre->Create(F0_IDD_BARRE_OUTIL,this);
	outil_affiche = TRUE;

	glob_barre->GetWindowRect(&rect);
	MoveWindow(rect.right,0,GetSystemMetrics(SM_CXSCREEN) - rect.right,
				 rect.bottom,FALSE); 

	PostMessage(WM_SIZE);		// Redimensionnement du journal

// Initialisation des variables globales
    glob_ihm = this;
    glob_synchro->Change_Top();

	
	return TRUE;  // return TRUE unless you set the focus to a control	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAccueil::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if (IsIconic())
	{
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}


void CDlgAccueil::Configure_liaison() 
{
	CDlgConfig	win;
	win.DoModal();
}
void CDlgAccueil::Parametre_liaison() 
{
	CDlgAffecte	win;
	win.DoModal();
}

void CDlgAccueil::Affiche_outil()
{
	if(outil_affiche)
	{
		glob_barre->ShowWindow(SW_HIDE);
		GetMenu()->CheckMenuItem(ID_AFF_OUTIL,MF_UNCHECKED);
	}
	else
	{
		glob_barre->ShowWindow(SW_SHOW);
		GetMenu()->CheckMenuItem(ID_AFF_OUTIL,MF_CHECKED);
		PostMessage(WM_SIZE);
	}
	outil_affiche = !outil_affiche;
}

void CDlgAccueil::OnSize(UINT nType, int cx, int cy) 
{
	RECT	dim;

	CDialog::OnSize(nType, cx, cy);

	GetClientRect(&dim);
	if(m_journal.m_hWnd != NULL)
		m_journal.MoveWindow(&dim,TRUE);

}

void CDlgAccueil::Ajout_message(char *buf)
{
	int			i,iResult;
	int			nb_max_message = glob_paramsimu->MaxMessage();

	if(strlen(buf)>TAILLE_MESSAGE-1)
		buf[TAILLE_MESSAGE-1]=0;			// Force limite la taille des messsage
	
	iResult = m_journal.GetCount();
	for(i=nb_max_message ; i<=iResult ; i++)
		m_journal.DeleteString(0);

	iResult = m_journal.AddString(buf);
	m_journal.SetCaretIndex(iResult,FALSE);	// Se place sur le message ajouter
}

void CDlgAccueil::OnCouper()
{
	int		i;
	int		taille = m_journal.GetCount();

	for(i=taille-1 ; i>=0 ; i--)
	{
		if(m_journal.GetSel(i))
			m_journal.DeleteString(i);
	}
}

void CDlgAccueil::OnCouperTout()
{
	int		i;
	int		taille = m_journal.GetCount();

	for(i=taille-1 ; i>=0 ; i--)
	{
		m_journal.DeleteString(i);
	}
}

void CDlgAccueil::OnSauvegarde()
{
	int		i,iResult;
	int		taille;
	char	parametre[TAILLE_MESSAGE-1];
	char	*message;

	char	fichier[80]="";

	CFileDialog win(TRUE,"env",fichier,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		,"Journal (*.jou)|*.jou|Fichier ASCII (*.txt)|*.txt||"
 		,this);
	
	win.m_ofn.Flags &= ~OFN_SHOWHELP;
	win.m_ofn.Flags &= ~524288;		//OFN_EXPLORER;

	iResult = win.DoModal();
	if(iResult != IDOK) return;

	strcpy(fichier,win.GetPathName()); 

	taille = m_journal.GetCount();
	message = (char*) malloc(taille*(TAILLE_MESSAGE));
	if(message==NULL) return;

	strcpy(message,"");
	for(i=0 ; i<taille ; i++)
	{
		m_journal.GetText(i,parametre);
		strcat(message,parametre);
		strcat(message,"\r\n");
	}

	i = Stocker_fichier(fichier,message);
   	if(message!= NULL) free(message);

	i = Stocker_fichier(fichier,message);
}


void CDlgAccueil::OnClose() 
{
	if (glob_paramsimu != NULL) 
	{
		delete glob_paramsimu;
		glob_paramsimu = NULL;
	}
	/*
	if (glob_synchro != NULL) 
	{
		delete glob_synchro;
		glob_synchro = NULL;
	}
	
	if (glob_barre != NULL) 
	{
		delete	glob_barre;				// Boite d'outil
		glob_barre = NULL;
	}
	*/
	DestroyWindow();
}

void CDlgAccueil::OnTimer(UINT nIDEvent) 
{
	int			i;
	t_affecte	ligne;
	int			nb_liaison = glob_paramsimu->MaxLiaison();
	BOOL		un_eqp_actif = FALSE;

	for(i=0 ; i<nb_liaison ; i++)
	{
		glob_paramsimu->Equipement(i,&ligne);
		if(ligne.activite) un_eqp_actif = TRUE;
	}
	
	if(un_eqp_actif)
	{
		glob_ihm->GetMenu()->EnableMenuItem(ID_ENV_NOUVEAU,MF_DISABLED | MF_GRAYED);
		glob_ihm->GetMenu()->EnableMenuItem(ID_ENV_OUVRIR,MF_DISABLED | MF_GRAYED);
		glob_ihm->GetMenu()->EnableMenuItem(ID_ENV_SAUVER,MF_DISABLED | MF_GRAYED);
	}
	else
	{
		glob_ihm->GetMenu()->EnableMenuItem(ID_ENV_NOUVEAU,MF_ENABLED);
		glob_ihm->GetMenu()->EnableMenuItem(ID_ENV_OUVRIR,MF_ENABLED);
		glob_ihm->GetMenu()->EnableMenuItem(ID_ENV_SAUVER,MF_ENABLED);
	}

	CDialog::OnTimer(nIDEvent);
}
