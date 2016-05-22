// DLGmatSPIN.cpp: implementation of the CDLGmatSPIN class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sicomex.h"
#include "DLGmatSPIN.h"
#include "Equip\EqpMAT.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_MAT_SPIN[];

/* **************************************************************************
METHODE :		CDLGmatSPIN()
TRAITEMENT:		Construction
***************************************************************************	*/
CDLGmatSPIN::CDLGmatSPIN(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDLGmatSPIN::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGmatSPIN)
	m_err_retard	= _T("");
	m_periode		= _T("");
	m_tempo			= _T("");
	m_distant		= _T("");
	// TODO : integrer ici les objets CString
	//}}AFX_DATA_INIT

	bmp_BLACK = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BLACK));
	bmp_WHITE = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_WHITE));
	m_hIcon = AfxGetApp()->LoadIcon(IDB_MATSPIN);
}

/* **************************************************************************
METHODE :		DoDataExchange(CDataExchange* pDX)
TRAITEMENT:		Procedures d'echange
***************************************************************************	*/
void CDLGmatSPIN::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGmatSPIN)
	DDX_Control (pDX, IDC_MES_STATUT,		m_liste_message);
	DDX_Control (pDX, IDC_CHECK_SYNCHRO,	m_synchro);
	DDX_Control (pDX, IDC_CHECK_CYCLE,		m_cycle);
	DDX_Text	(pDX, IDC_RETARD,			m_err_retard);
	DDX_Text	(pDX, IDC_EDIT_CYCLE,		m_periode);
	DDX_Text	(pDX, IDC_EDIT_TEMPO,		m_tempo);

	DDX_Control	(pDX, IDC_SPIN_LOCAL,		m_local);
	DDX_Control	(pDX, IDC_SPIN_DUMP,		m_dump);
	DDX_Control	(pDX, IDC_SPIN_ERREUR,		m_erreur);
	DDX_Text	(pDX, IDC_SPIN_DISTANT,		m_distant);
	DDX_Control	(pDX, IDC_SPIN_1x1,			m_spin[0][0]);
	DDX_Control	(pDX, IDC_SPIN_1x2,			m_spin[0][1]);
	DDX_Control	(pDX, IDC_SPIN_1x3,			m_spin[0][2]);
	DDX_Control	(pDX, IDC_SPIN_1x4,			m_spin[0][3]);
	DDX_Control	(pDX, IDC_SPIN_1x5,			m_spin[0][4]);
	DDX_Control	(pDX, IDC_SPIN_1x6,			m_spin[0][5]);
	DDX_Control	(pDX, IDC_SPIN_1x7,			m_spin[0][6]);
	DDX_Control	(pDX, IDC_SPIN_1x8,			m_spin[0][7]);
	DDX_Control	(pDX, IDC_SPIN_1x9,			m_spin[0][8]);

	DDX_Control	(pDX, IDC_SPIN_2x1,			m_spin[1][0]);
	DDX_Control	(pDX, IDC_SPIN_2x2,			m_spin[1][1]);
	DDX_Control	(pDX, IDC_SPIN_2x3,			m_spin[1][2]);
	DDX_Control	(pDX, IDC_SPIN_2x4,			m_spin[1][3]);
	DDX_Control	(pDX, IDC_SPIN_2x5,			m_spin[1][4]);
	DDX_Control	(pDX, IDC_SPIN_2x6,			m_spin[1][5]);
	DDX_Control	(pDX, IDC_SPIN_2x7,			m_spin[1][6]);
	DDX_Control	(pDX, IDC_SPIN_2x8,			m_spin[1][7]);
	DDX_Control	(pDX, IDC_SPIN_2x9,			m_spin[1][8]);
	
	DDX_Control	(pDX, IDC_SPIN_3x1,			m_spin[2][0]);
	DDX_Control	(pDX, IDC_SPIN_3x2,			m_spin[2][1]);
	DDX_Control	(pDX, IDC_SPIN_3x3,			m_spin[2][2]);
	DDX_Control	(pDX, IDC_SPIN_3x4,			m_spin[2][3]);
	DDX_Control	(pDX, IDC_SPIN_3x5,			m_spin[2][4]);
	DDX_Control	(pDX, IDC_SPIN_3x6,			m_spin[2][5]);
	DDX_Control	(pDX, IDC_SPIN_3x7,			m_spin[2][6]);
	DDX_Control	(pDX, IDC_SPIN_3x8,			m_spin[2][7]);
	DDX_Control	(pDX, IDC_SPIN_3x9,			m_spin[2][8]);

	DDX_Control	(pDX, IDC_SPIN_4x1,			m_spin[3][0]);
	DDX_Control	(pDX, IDC_SPIN_4x2,			m_spin[3][1]);
	DDX_Control	(pDX, IDC_SPIN_4x3,			m_spin[3][2]);
	DDX_Control	(pDX, IDC_SPIN_4x4,			m_spin[3][3]);
	DDX_Control	(pDX, IDC_SPIN_4x5,			m_spin[3][4]);
	DDX_Control	(pDX, IDC_SPIN_4x6,			m_spin[3][5]);
	DDX_Control	(pDX, IDC_SPIN_4x7,			m_spin[3][6]);
	DDX_Control	(pDX, IDC_SPIN_4x8,			m_spin[3][7]);
	DDX_Control	(pDX, IDC_SPIN_4x9,			m_spin[3][8]);
	// TODO : integrer les variables d'echange
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGmatSPIN, CDialog)
	//{{AFX_MSG_MAP(CDLGmatSPIN)
	ON_WM_TIMER()

	ON_BN_CLICKED	(IDC_CDE_INCONUE,	OnComErreur)
	ON_BN_CLICKED	(IDC_DEBUT_TRAME,	OnComErreur)
	ON_BN_CLICKED	(IDC_FIN_TRAME,		OnComErreur)
	ON_EN_KILLFOCUS	(IDC_RETARD,		OnComErreur)
	ON_BN_CLICKED	(IDC_PAS_REPONSE,	OnComErreur)

	ON_BN_CLICKED	(IDC_SPIN_LOCAL,	OnLocal)
	ON_BN_CLICKED	(IDC_SPIN_DUMP,		OnDump)
	ON_CBN_SELCHANGE(IDC_SPIN_ERREUR,	OnErreur)
	//}}AFX_MSG_MAP

	ON_WM_CLOSE()
	ON_WM_PAINT()

	// Activation des tache de comm
	ON_COMMAND		(IDC_ACTIVITE,					OnActivite)
	// Aide
	ON_COMMAND		(ID__AIDE,						OnAide)
	// Masquage de l'ecran de controle
	ON_COMMAND		(ID_AFF_CONTROLE,				OnClose)
	// Envoi de trame
	ON_BN_CLICKED	(IDC_ENVOI_TRAME,				OnEnvoiTrame)
	// Contexte d'exploitation
	ON_COMMAND		(ID_CONTEXTE_OUVRIR,			OnOuvrir)
	ON_COMMAND		(ID_CONTEXTE_SAUVER,			OnSauver)
	// journal
	ON_COMMAND		(ID_JOURNAL_COUPER,				OnCouper)
	ON_COMMAND		(ID_JOURNAL_COUPERTOUT,			OnCouperTout)
	ON_COMMAND		(ID_JOURNAL_ENREGISTRERSOUS,	OnSauvegarde)
	ON_BN_CLICKED	(IDC_PRECEDENT,					OnPrecedent)
	ON_BN_CLICKED	(IDC_SUIVANT,					OnSuivant)
	ON_LBN_DBLCLK	(IDC_JOURNAL,					OnDblclkJournal)
	// Sequence de message : fonction definies dans la classe de base
	ON_BN_CLICKED	(IDC_AJOUT_MESSAGE,				OnAjoutMessage)
	ON_BN_CLICKED	(IDC_RETIRE_MESSAGE,			OnRetireMessage)
	ON_BN_CLICKED	(IDC_CHECK_CYCLE,				OnCheckCycle)
	ON_BN_CLICKED	(IDC_CHECK_SYNCHRO,				OnCheckSynchro)
	ON_EN_KILLFOCUS	(IDC_EDIT_CYCLE,				OnKillfocusEditCycle)
	ON_EN_KILLFOCUS	(IDC_EDIT_TEMPO,				OnKillfocusEditTempo)
	ON_BN_CLICKED	(IDC_ENVOI_STATUT,				OnEnvoiStatut)
	ON_BN_CLICKED	(IDC_ARRET_STATUT,				OnArretStatut)

END_MESSAGE_MAP()


/* **************************************************************************
METHODE :		OnAide()
TRAITEMENT:		Boite de dialogue d'aide
***************************************************************************	*/
void CDLGmatSPIN::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_MAT_SPIN,"Matrice SPIN");
	if(iResult >=  0)
	{
		win.DoModal();
	}
}

/* **************************************************************************
METHODE :		OnInitDialog() 
TRAITEMENT:		Initialisation de la boite de dialogue
***************************************************************************	*/
BOOL CDLGmatSPIN::OnInitDialog() 
{
	t_ComErreur	err;
	char		buf[10];

	CDialog::OnInitDialog();

	//	Armement du timer
	SetTimer(1,1000,NULL);	
	
	// Gestion des erreurs de communication
	// ************************************
	equip->RetourneComErreur(&err);
	sprintf(buf,"%d",err.retard);
	m_err_retard = buf;

	// Envoi de sequence de message
	// ****************************
	GetDlgItem(IDC_ENVOI_STATUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARRET_STATUT)->EnableWindow(FALSE);
	sprintf(buf,"%d",equip->DureeTempo());
	m_tempo = buf;
	sprintf(buf,"%d",equip->Periode());
	m_periode = buf;
	m_cycle.SetCheck(equip->EnvoiCyclique());
	m_synchro.SetCheck(equip->Synchronise());

	// Liste des commandes de sequence
	// *******************************
	m_liste_message.AddString("Aucun");
	m_liste_message.AddString("Defaut alimentation");
	m_liste_message.AddString("Defaut configuration chassis");
	m_liste_message.AddString("Defaut RAM/UC");
	m_liste_message.AddString("Defaut PROM/UC");
	m_liste_message.AddString("Defaut bus interne/UC");
	m_liste_message.AddString("Defaut bus lent");
	m_liste_message.AddString("Defaut format message");
	m_liste_message.AddString("Defaut sequence");
	m_liste_message.AddString("Defaut carte relais 1");
	m_liste_message.AddString("Defaut carte relais 2");
	m_liste_message.AddString("Defaut carte relais 3");
	m_liste_message.AddString("Defaut carte relais 4");
	m_liste_message.AddString("Defaut carte relais 5");
	m_liste_message.AddString("Defaut carte relais 6");
	m_liste_message.AddString("Defaut carte relais 7");
	m_liste_message.AddString("Defaut carte relais 8");
	m_liste_message.AddString("Defaut carte relais 9");
	m_liste_message.AddString("Defaut carte relais 10");
	m_liste_message.AddString("Defaut carte relais 11");
	m_liste_message.AddString("Defaut carte relais 12");
	m_liste_message.AddString("Defaut programmation");
	m_liste_message.AddString("Aucun defaut");

	// Custom control
	// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);

	
	// Initialisation de la face avant
	// *******************************
	m_erreur.AddString("Aucun");
	m_erreur.AddString("Defaut alimentation");
	m_erreur.AddString("Defaut configuration chassis");
	m_erreur.AddString("Defaut RAM/UC");
	m_erreur.AddString("Defaut PROM/UC");
	m_erreur.AddString("Defaut bus interne/UC");
	m_erreur.AddString("Defaut bus lent");
	m_erreur.AddString("Defaut format message");
	m_erreur.AddString("Defaut sequence");
	m_erreur.AddString("Defaut carte relais 1");
	m_erreur.AddString("Defaut carte relais 2");
	m_erreur.AddString("Defaut carte relais 3");
	m_erreur.AddString("Defaut carte relais 4");
	m_erreur.AddString("Defaut carte relais 5");
	m_erreur.AddString("Defaut carte relais 6");
	m_erreur.AddString("Defaut carte relais 7");
	m_erreur.AddString("Defaut carte relais 8");
	m_erreur.AddString("Defaut carte relais 9");
	m_erreur.AddString("Defaut carte relais 10");
	m_erreur.AddString("Defaut carte relais 11");
	m_erreur.AddString("Defaut carte relais 12");
	m_erreur.AddString("Defaut programmation");
	m_erreur.AddString("Aucun defaut");
	m_erreur.SetCurSel(0);

	m_distant = _T("Mode distant");

	UpdateData(FALSE);

	return TRUE;
}


/* **************************************************************************
METHODE :		GenerateurAuto()
TRAITEMENT:		Effectue les variations automatiques de certains composants
***************************************************************************	*/
void CDLGmatSPIN::GenerateurAuto()
{
	// Aucune variation automatique sur cet equipement
}

/* **************************************************************************
METHODE :		OnTimer(UINT nIDEvent) 
TRAITEMENT:		Rafraichissement de l'ecran de controle
***************************************************************************	*/
void CDLGmatSPIN::OnTimer(UINT nIDEvent) 
{
	int	 val, i, j;
	//char buf[10];					//2009-11-27

	UpdateData(TRUE);

	CDialog::OnTimer(nIDEvent);
	// Rafraichissement des controles commun
	CDlgEquip::OnTimer();

	// Test de changement dans la face avant
	val = equip->Evolution();
	// Rafraichissement inutile
	if(val==evolution)
	{
		return;
	}
	evolution = val;

	for(i=0; i< ((CEqpMAT *)equip)->NB_PM ; i++)
	{
		for(j=0; j< ((CEqpMAT *)equip)->NB_ER ; j++)
		{
			if( ((CEqpMAT *)equip)->MATRICE_COMMUT[i][j] == true)
				m_spin[i][j].SetBitmap(bmp_BLACK);
			else
				m_spin[i][j].SetBitmap(bmp_WHITE);
		}
	}

	if( ((CEqpMAT *)equip)->Local() )
	{
		Verrouille(TRUE);
		m_distant = _T("Mode local");
	}
	else
	{
		Verrouille(FALSE);
		m_distant = _T("Mode distant");
	}

	UpdateData(FALSE);
}

/* **************************************************************************
METHODE :		OnComErreur()
TRAITEMENT:		
***************************************************************************	*/
void CDLGmatSPIN::OnComErreur() 
{
	t_ComErreur	err;
	
	CButton	*m_debut	= (CButton*)GetDlgItem(IDC_DEBUT_TRAME);
	CButton	*m_fin		= (CButton*)GetDlgItem(IDC_FIN_TRAME);
	CButton	*m_parite	= (CButton*)GetDlgItem(IDC_PARITE);
	CButton	*m_inconnue	= (CButton*)GetDlgItem(IDC_CDE_INCONUE);
	CButton	*m_reponse	= (CButton*)GetDlgItem(IDC_PAS_REPONSE);

	err.pas_debut		= m_debut->GetCheck();
	err.pas_fin			= m_fin->GetCheck();
	err.controle_parite	= m_parite->GetCheck();
	err.cde_inconnue	= m_inconnue->GetCheck();
	err.pas_de_reponse	= m_reponse->GetCheck();

	UpdateData(TRUE);
	err.retard = atoi(m_err_retard);
	equip->ChangeComErreur(err);
}

// Action par la face avant *****************************************************
// ******************************************************************************

/* **************************************************************************
METHODE :		Verrouille(BOOL etat)
TRAITEMENT:		Verrouillage de la face avant
***************************************************************************	*/
void CDLGmatSPIN::Verrouille(BOOL etat)
{
// Button valider
	m_local.EnableWindow(etat);
	// Button DUMP
	m_dump.EnableWindow(etat);
	// Button LOCAL
	m_erreur.EnableWindow(etat);
}

/* **************************************************************************
METHODE :		OnLocal()
TRAITEMENT:		Msie en mode local
***************************************************************************	*/
void CDLGmatSPIN::OnLocal()
{

}

/* **************************************************************************
METHODE :		OnDump()
TRAITEMENT:		Demande spontannee d'envoi d'etat de la matrice
***************************************************************************	*/
void CDLGmatSPIN::OnDump()
{
	((CEqpMAT *)equip)->EtatMatrice();
}

/* **************************************************************************
METHODE :		OnErreur()
TRAITEMENT:		Demande spontannee d'envoi d'erreur
***************************************************************************	*/
void CDLGmatSPIN::OnErreur()
{
	((CEqpMAT *)equip)->PassageErreur(m_erreur.GetCurSel());
}
