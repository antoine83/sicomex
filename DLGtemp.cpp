// DLGtemp.cpp: implementation of the CDLGtemp class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sicomex.h"
#include "DLGtemp.h"
#include "Equip\EqpTemp.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_E_1225[];

/* **************************************************************************
METHODE :		CDLGtemp()
TRAITEMENT:		Construction
***************************************************************************	*/
CDLGtemp::CDLGtemp(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDLGtemp::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGtemp)
	m_err_retard	= _T("");
	m_periode		= _T("");
	m_tempo			= _T("");
	// TODO : integrer ici les objets CString
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDI_EM_HF);
}

/* **************************************************************************
METHODE :		DoDataExchange(CDataExchange* pDX)
TRAITEMENT:		Procedures d'echange
***************************************************************************	*/
void CDLGtemp::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGtemp)
	DDX_Control (pDX, IDC_MES_STATUT,	m_liste_message);
	DDX_Control (pDX, IDC_CHECK_SYNCHRO,m_synchro);
	DDX_Control (pDX, IDC_CHECK_CYCLE,	m_cycle);
	DDX_Text	(pDX, IDC_RETARD,		m_err_retard);
	DDX_Text	(pDX, IDC_EDIT_CYCLE,	m_periode);
	DDX_Text	(pDX, IDC_EDIT_TEMPO,	m_tempo);
	// TODO : integrer les variables d'echange
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGtemp, CDialog)
	//{{AFX_MSG_MAP(CDLGtemp)
	ON_WM_TIMER()

	ON_BN_CLICKED	(IDC_CDE_INCONUE,	OnComErreur)
	ON_BN_CLICKED	(IDC_DEBUT_TRAME,	OnComErreur)
	ON_BN_CLICKED	(IDC_FIN_TRAME,		OnComErreur)
	ON_EN_KILLFOCUS	(IDC_RETARD,		OnComErreur)
	ON_BN_CLICKED	(IDC_PAS_REPONSE,	OnComErreur)
	// TODO : integrer les evenements lies a l'interface
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
void CDLGtemp::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_E_1225,"Emetteur HF");
	if(iResult >=  0)
	{
		win.DoModal();
	}
}

/* **************************************************************************
METHODE :		OnInitDialog() 
TRAITEMENT:		Initialisation de la boite de dialogue
***************************************************************************	*/
BOOL CDLGtemp::OnInitDialog() 
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

	// Custom control
	// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);

	
	// Initialisation de la face avant
	// *******************************

	UpdateData(FALSE);

	return TRUE;
}


/* **************************************************************************
METHODE :		GenerateurAuto()
TRAITEMENT:		Effectue les variations automatiques de certains composants
***************************************************************************	*/
void CDLGtemp::GenerateurAuto()
{
	// TODO : integrer ici le variations cyclique des composants
	Beep(220, 10);
}

/* **************************************************************************
METHODE :		OnTimer(UINT nIDEvent) 
TRAITEMENT:		Rafraichissement de l'ecran de controle
***************************************************************************	*/
void CDLGtemp::OnTimer(UINT nIDEvent) 
{
	int	 val;
	//char buf[10];				//2009-11-27

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

	// TODO : Integrer le code de rafraichissement de l'ecran de controle

	UpdateData(FALSE);
}

/* **************************************************************************
METHODE :		OnComErreur()
TRAITEMENT:		
***************************************************************************	*/
void CDLGtemp::OnComErreur() 
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
void CDLGtemp::Verrouille(BOOL etat)
{

	// TODO : integrer le code de verrouillage
}
