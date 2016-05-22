// DLGTest1.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DLGTest1.h"
#include "Equip\EquipTest.h"
#include "DlgAide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_MAT_L11[];

//////////////////////////////////////////////////////////////////////
// Construction
//////////////////////////////////////////////////////////////////////
CDLGTest::CDLGTest(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDLGTest::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGmatL11)
	m_err_retard = _T("");
	m_periode = _T("");
	m_tempo = _T("");
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDB_MATL11);
}


void CDLGTest::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGTest)
	DDX_Control(pDX, IDC_TEST_DEBUT_CR, m_debut_CR);
	DDX_Control(pDX, IDC_TEST_DEBUT_LF, m_debut_LF);
	DDX_Control(pDX, IDC_TEST_DEBUT_SUB, m_debut_SUB);
	DDX_Control(pDX, IDC_TEST_FIN_CR, m_fin_CR);
	DDX_Control(pDX, IDC_TEST_FIN_LF, m_fin_LF);
	DDX_Control(pDX, IDC_TEST_FIN_SUB, m_fin_SUB);

	DDX_Control(pDX, IDC_TEST_ENVOITS, m_envoyer);
	DDX_Control(pDX, IDC_TEST_BENVOITS, m_benvoyer);
	DDX_Control(pDX, IDC_TEST_RECEPTION, m_recevoir);
	DDX_Control(pDX, IDC_TEST_BRECEPTION, m_brecevoir);

	DDX_Control(pDX, IDC_CHECK_CYCLE, m_cycle);
	DDX_Control(pDX, IDC_CHECK_SYNCHRO, m_synchro);
	DDX_Control(pDX, IDC_MES_STATUT, m_liste_message);
	DDX_Control(pDX, IDC_ENVOI_STATUT, m_statut_envoi);
	DDX_Control(pDX, IDC_ARRET_STATUT, m_statut_arret);
	DDX_Control(pDX, IDC_AJOUT_MESSAGE, m_ajout_msg);
	DDX_Control(pDX, IDC_RETIRE_MESSAGE, m_retire_msg);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGTest, CDialog)
	//{{AFX_MSG_MAP(CDLGTest)
	ON_BN_CLICKED(IDC_TEST_DEBUT_CR, OnDebutCR)
	ON_BN_CLICKED(IDC_TEST_DEBUT_LF, OnDebutLF)
	ON_BN_CLICKED(IDC_TEST_DEBUT_SUB, OnDebutSUB)
	ON_BN_CLICKED(IDC_TEST_FIN_CR, OnFinCR)
	ON_BN_CLICKED(IDC_TEST_FIN_LF, OnFinLF)
	ON_BN_CLICKED(IDC_TEST_FIN_SUB, OnFinSUB)
	//}}AFX_MSG_MAP

	ON_BN_CLICKED(IDC_TEST_BENVOITS, OnBEnvoi)
	ON_BN_CLICKED(IDC_TEST_BRECEPTION, OnBReception)

	ON_WM_CLOSE()
	ON_WM_PAINT()

	// Activation des tache de comm
	ON_COMMAND(IDC_ACTIVITE, OnActivite)

	// Aide
	ON_COMMAND(ID__AIDE, OnAide)

	// Masquage de l'ecran de controle
	ON_COMMAND(ID_AFF_CONTROLE, OnClose)

	// Envoi de trame
	ON_BN_CLICKED(IDC_ENVOI_TRAME, OnEnvoiTrame)

	// Contexte d'exploitation
	ON_COMMAND(ID_CONTEXTE_OUVRIR, OnOuvrir)
	ON_COMMAND(ID_CONTEXTE_SAUVER, OnSauver)

	// journal
	ON_COMMAND(ID_JOURNAL_COUPER, OnCouper)
	ON_COMMAND(ID_JOURNAL_COUPERTOUT, OnCouperTout)
	ON_COMMAND(ID_JOURNAL_ENREGISTRERSOUS, OnSauvegarde)
	ON_BN_CLICKED(IDC_PRECEDENT, OnPrecedent)
	ON_BN_CLICKED(IDC_SUIVANT, OnSuivant)
	ON_LBN_DBLCLK(IDC_JOURNAL, OnDblclkJournal)

	// Sequence de message : fonction definies dans la classe de base
	ON_BN_CLICKED(IDC_AJOUT_MESSAGE, OnAjoutMessage)
	ON_BN_CLICKED(IDC_RETIRE_MESSAGE, OnRetireMessage)
	ON_BN_CLICKED(IDC_CHECK_CYCLE, OnCheckCycle)
	ON_BN_CLICKED(IDC_CHECK_SYNCHRO, OnCheckSynchro)

	ON_EN_KILLFOCUS(IDC_EDIT_CYCLE, OnKillfocusEditCycle)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMPO, OnKillfocusEditTempo)
	ON_BN_CLICKED(IDC_ENVOI_STATUT, OnEnvoiStatut)
	ON_BN_CLICKED(IDC_ARRET_STATUT, OnArretStatut)

END_MESSAGE_MAP()

/* **************************************************************************
METHODE :		OnAide()
TRAITEMENT:		Fenetre d'aide pour la matrice AAD 20x4
***************************************************************************	*/
void CDLGTest::OnAide()
{

}

/* **************************************************************************
METHODE :		Verrouille(BOOL etat)
TRAITEMENT:		Fenetre d'aide pour la matrice AAD 20x4
***************************************************************************	*/
void CDLGTest::Verrouille(BOOL etat)
{

}

/* **************************************************************************
METHODE :		OnInitDialog()
TRAITEMENT:		Initialise la boite de dialogue
***************************************************************************	*/
BOOL CDLGTest::OnInitDialog()
{
	t_ComErreur	err;
	char buf[10];

	CDialog::OnInitDialog();

	// Armement du timer
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

	// Custom control
	// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);

	((CEquipTest *)equip)->DebutCR  = false;
	((CEquipTest *)equip)->DebutLF  = false;
	((CEquipTest *)equip)->DebutSUB = false;
	((CEquipTest *)equip)->FinCR    = false;
	((CEquipTest *)equip)->FinLF    = false;
	((CEquipTest *)equip)->FinSUB   = false;
	m_debut_CR.SetCheck(0);
	m_debut_LF.SetCheck(0);
	m_debut_SUB.SetCheck(0);
	m_fin_CR.SetCheck(0);
	m_fin_LF.SetCheck(0);
	m_fin_SUB.SetCheck(0);

	UpdateData(FALSE);

	return TRUE;
}

/* **************************************************************************
METHODE :		OnComErreur()
TRAITEMENT:		Initialise la boite de dialogue
***************************************************************************	*/
void CDLGTest::OnComErreur()
{
	t_ComErreur	err;

	CButton		*m_debut = (CButton*)GetDlgItem(IDC_DEBUT_TRAME);
	CButton		*m_fin = (CButton*)GetDlgItem(IDC_FIN_TRAME);
	CButton		*m_parite = (CButton*)GetDlgItem(IDC_PARITE);
	CButton		*m_inconnue = (CButton*)GetDlgItem(IDC_CDE_INCONUE);
	CButton		*m_reponse = (CButton*)GetDlgItem(IDC_PAS_REPONSE);

	err.pas_debut		= m_debut->GetCheck();
	err.pas_fin			= m_fin->GetCheck();
	err.controle_parite	= m_parite->GetCheck();
	err.cde_inconnue	= m_inconnue->GetCheck();
	err.pas_de_reponse	= m_reponse->GetCheck();

	UpdateData(TRUE);
	err.retard = atoi(m_err_retard);

	equip->ChangeComErreur(err);
}

/* **************************************************************************
METHODE :		GenerateurAuto()
TRAITEMENT:		Effectue les variation automatique de certains paramètres
***************************************************************************	*/
void CDLGTest::GenerateurAuto()
{
	OnReception();
}

/* **************************************************************************
METHODE :		OnTimer(UINT nIDEvent)
TRAITEMENT:		Rafraichissement de l'écran de controle
***************************************************************************	*/
void CDLGTest::OnTimer(UINT nIDEvent)
{
	int			val;

	UpdateData(TRUE);

	CDialog::OnTimer(nIDEvent);
	CDlgEquip::OnTimer();

	val = equip->Evolution();
	if (val==evolution) return;
	evolution = val;

	UpdateData(FALSE);
}

void CDLGTest::OnBEnvoi()
{
	char buffer[TAILLE_PIPE_MESSAGE+1];

	CEdit *m_temp = (CEdit*)GetDlgItem(IDC_TEST_ENVOITS);

	m_temp->GetLine(0,buffer,TAILLE_PIPE_MESSAGE);
	((CEquipTest *)equip)->EnvoiMessage(buffer);
}

void CDLGTest::OnReception()
{
	m_recevoir.AddString( ((CEquipTest *)equip)->MESSAGE );
}

void CDLGTest::OnBReception()
{
	m_recevoir.ResetContent();
}

/* **************************************************************************
METHODE :		OnDebutCR()
TRAITEMENT:
***************************************************************************	*/
void CDLGTest::OnDebutCR()
{
	if(m_debut_CR.GetCheck())
	{
		((CEquipTest *)equip)->DebutCR = true;
	}
	else
	{
		((CEquipTest *)equip)->DebutCR = false;
	}
}

/* **************************************************************************
METHODE :		OnDebutLF()
TRAITEMENT:
***************************************************************************	*/
void CDLGTest::OnDebutLF()
{
	if(m_debut_LF.GetCheck())
	{
		((CEquipTest *)equip)->DebutLF = true;
	}
	else
	{
		((CEquipTest *)equip)->DebutLF = false;
	}
}

/* **************************************************************************
METHODE :		OnDebutSUB()
TRAITEMENT:
***************************************************************************	*/
void CDLGTest::OnDebutSUB()
{
	if(m_debut_SUB.GetCheck())
	{
		((CEquipTest *)equip)->DebutSUB = true;
	}
	else
	{
		((CEquipTest *)equip)->DebutSUB = false;
	}
}

/* **************************************************************************
METHODE :		OnFinCR()
TRAITEMENT:
***************************************************************************	*/
void CDLGTest::OnFinCR()
{
	if(m_fin_CR.GetCheck())
	{
		((CEquipTest *)equip)->FinCR = true;
	}
	else
	{
		((CEquipTest *)equip)->FinCR = false;
	}
}

/* **************************************************************************
METHODE :		OnFinLF()
TRAITEMENT:
***************************************************************************	*/
void CDLGTest::OnFinLF()
{
	if(m_fin_LF.GetCheck())
	{
		((CEquipTest *)equip)->FinLF = true;
	}
	else
	{
		((CEquipTest *)equip)->FinLF = false;
	}
}

/* **************************************************************************
METHODE :		OnFinSUB()
TRAITEMENT:
***************************************************************************	*/
void CDLGTest::OnFinSUB()
{
	if(m_fin_SUB.GetCheck())
	{
		((CEquipTest *)equip)->FinSUB = true;
	}
	else
	{
		((CEquipTest *)equip)->FinSUB = false;
	}
}
