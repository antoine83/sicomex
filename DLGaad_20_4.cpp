// DLGaad_20_4.cpp: implementation of the CDLGaad_20_4 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sicomex.h"
#include "DLGaad_20_4.h"
#include "Equip\EqpAAD.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_AAD_20_4[];

/* **************************************************************************
METHODE :		CDLGaad_20_4()
TRAITEMENT:		Construction
***************************************************************************	*/
CDLGaad_20_4::CDLGaad_20_4(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDLGaad_20_4::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGaad_20_4)
	m_err_retard	= _T("");
	m_periode		= _T("");
	m_tempo			= _T("");
	//}}AFX_DATA_INIT

	bmp_BLACK = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BLACK));
	bmp_WHITE = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_WHITE));
	m_hIcon = AfxGetApp()->LoadIcon(IDB_AAD_20_4);
}

/* **************************************************************************
METHODE :		DoDataExchange(CDataExchange* pDX)
TRAITEMENT:		Procedures d'echange
***************************************************************************	*/
void CDLGaad_20_4::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGaad_20_4)
	DDX_Control (pDX, IDC_MES_STATUT,			m_liste_message);
	DDX_Control (pDX, IDC_CHECK_SYNCHRO,		m_synchro);
	DDX_Control (pDX, IDC_CHECK_CYCLE,			m_cycle);
	DDX_Text	(pDX, IDC_RETARD,				m_err_retard);
	DDX_Text	(pDX, IDC_EDIT_CYCLE,			m_periode);
	DDX_Text	(pDX, IDC_EDIT_TEMPO,			m_tempo);
	
	DDX_Control	(pDX, IDC_20_4_EtatAntenne1,	EtatAntenne_20_4[0]);
	DDX_Control	(pDX, IDC_20_4_EtatAntenne2,	EtatAntenne_20_4[1]);
	DDX_Control	(pDX, IDC_20_4_EtatAntenne3,	EtatAntenne_20_4[2]);
	DDX_Control	(pDX, IDC_20_4_EtatAntenne4,	EtatAntenne_20_4[3]);

	DDX_Control	(pDX, IDC_20_4_EtatPreampli1,	EtatPreampli_20_4[0]);
	DDX_Control	(pDX, IDC_20_4_EtatPreampli2,	EtatPreampli_20_4[1]);
	DDX_Control	(pDX, IDC_20_4_EtatPreampli3,	EtatPreampli_20_4[2]);
	DDX_Control	(pDX, IDC_20_4_EtatPreampli4,	EtatPreampli_20_4[3]);

	DDX_Control	(pDX, IDC_20_4_EtatAmpli1,		EtatAmpli_20_4[0]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli2,		EtatAmpli_20_4[1]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli3,		EtatAmpli_20_4[2]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli4,		EtatAmpli_20_4[3]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli5,		EtatAmpli_20_4[4]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli6,		EtatAmpli_20_4[5]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli7,		EtatAmpli_20_4[6]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli8,		EtatAmpli_20_4[7]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli9,		EtatAmpli_20_4[8]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli10,		EtatAmpli_20_4[9]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli11,		EtatAmpli_20_4[10]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli12,		EtatAmpli_20_4[11]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli13,		EtatAmpli_20_4[12]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli14,		EtatAmpli_20_4[13]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli15,		EtatAmpli_20_4[14]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli16,		EtatAmpli_20_4[15]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli17,		EtatAmpli_20_4[16]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli18,		EtatAmpli_20_4[17]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli19,		EtatAmpli_20_4[18]);
	DDX_Control	(pDX, IDC_20_4_EtatAmpli20,		EtatAmpli_20_4[19]);
	
	DDX_Control	(pDX, IDC_20_4_1x1,				m_20_4[0][0]);
	DDX_Control	(pDX, IDC_20_4_1x2,				m_20_4[0][1]);
	DDX_Control	(pDX, IDC_20_4_1x3,				m_20_4[0][2]);
	DDX_Control	(pDX, IDC_20_4_1x4,				m_20_4[0][3]);
	DDX_Control	(pDX, IDC_20_4_1x5,				m_20_4[0][4]);
	DDX_Control	(pDX, IDC_20_4_1x6,				m_20_4[0][5]);
	DDX_Control	(pDX, IDC_20_4_1x7,				m_20_4[0][6]);
	DDX_Control	(pDX, IDC_20_4_1x8,				m_20_4[0][7]);
	DDX_Control	(pDX, IDC_20_4_1x9,				m_20_4[0][8]);
	DDX_Control	(pDX, IDC_20_4_1x10,			m_20_4[0][9]);
	DDX_Control	(pDX, IDC_20_4_1x11,			m_20_4[0][10]);
	DDX_Control	(pDX, IDC_20_4_1x12,			m_20_4[0][11]);
	DDX_Control	(pDX, IDC_20_4_1x13,			m_20_4[0][12]);
	DDX_Control	(pDX, IDC_20_4_1x14,			m_20_4[0][13]);
	DDX_Control	(pDX, IDC_20_4_1x15,			m_20_4[0][14]);
	DDX_Control	(pDX, IDC_20_4_1x16,			m_20_4[0][15]);
	DDX_Control	(pDX, IDC_20_4_1x17,			m_20_4[0][16]);
	DDX_Control	(pDX, IDC_20_4_1x18,			m_20_4[0][17]);
	DDX_Control	(pDX, IDC_20_4_1x19,			m_20_4[0][18]);
	DDX_Control	(pDX, IDC_20_4_1x20,			m_20_4[0][19]);

	DDX_Control	(pDX, IDC_20_4_2x1,				m_20_4[1][0]);
	DDX_Control	(pDX, IDC_20_4_2x2,				m_20_4[1][1]);
	DDX_Control	(pDX, IDC_20_4_2x3,				m_20_4[1][2]);
	DDX_Control	(pDX, IDC_20_4_2x4,				m_20_4[1][3]);
	DDX_Control	(pDX, IDC_20_4_2x5,				m_20_4[1][4]);
	DDX_Control	(pDX, IDC_20_4_2x6,				m_20_4[1][5]);
	DDX_Control	(pDX, IDC_20_4_2x7,				m_20_4[1][6]);
	DDX_Control	(pDX, IDC_20_4_2x8,				m_20_4[1][7]);
	DDX_Control	(pDX, IDC_20_4_2x9,				m_20_4[1][8]);
	DDX_Control	(pDX, IDC_20_4_2x10,			m_20_4[1][9]);
	DDX_Control	(pDX, IDC_20_4_2x11,			m_20_4[1][10]);
	DDX_Control	(pDX, IDC_20_4_2x12,			m_20_4[1][11]);
	DDX_Control	(pDX, IDC_20_4_2x13,			m_20_4[1][12]);
	DDX_Control	(pDX, IDC_20_4_2x14,			m_20_4[1][13]);
	DDX_Control	(pDX, IDC_20_4_2x15,			m_20_4[1][14]);
	DDX_Control	(pDX, IDC_20_4_2x16,			m_20_4[1][15]);
	DDX_Control	(pDX, IDC_20_4_2x17,			m_20_4[1][16]);
	DDX_Control	(pDX, IDC_20_4_2x18,			m_20_4[1][17]);
	DDX_Control	(pDX, IDC_20_4_2x19,			m_20_4[1][18]);
	DDX_Control	(pDX, IDC_20_4_2x20,			m_20_4[1][19]);

	DDX_Control	(pDX, IDC_20_4_3x1,				m_20_4[2][0]);
	DDX_Control	(pDX, IDC_20_4_3x2,				m_20_4[2][1]);
	DDX_Control	(pDX, IDC_20_4_3x3,				m_20_4[2][2]);
	DDX_Control	(pDX, IDC_20_4_3x4,				m_20_4[2][3]);
	DDX_Control	(pDX, IDC_20_4_3x5,				m_20_4[2][4]);
	DDX_Control	(pDX, IDC_20_4_3x6,				m_20_4[2][5]);
	DDX_Control	(pDX, IDC_20_4_3x7,				m_20_4[2][6]);
	DDX_Control	(pDX, IDC_20_4_3x8,				m_20_4[2][7]);
	DDX_Control	(pDX, IDC_20_4_3x9,				m_20_4[2][8]);
	DDX_Control	(pDX, IDC_20_4_3x10,			m_20_4[2][9]);
	DDX_Control	(pDX, IDC_20_4_3x11,			m_20_4[2][10]);
	DDX_Control	(pDX, IDC_20_4_3x12,			m_20_4[2][11]);
	DDX_Control	(pDX, IDC_20_4_3x13,			m_20_4[2][12]);
	DDX_Control	(pDX, IDC_20_4_3x14,			m_20_4[2][13]);
	DDX_Control	(pDX, IDC_20_4_3x15,			m_20_4[2][14]);
	DDX_Control	(pDX, IDC_20_4_3x16,			m_20_4[2][15]);
	DDX_Control	(pDX, IDC_20_4_3x17,			m_20_4[2][16]);
	DDX_Control	(pDX, IDC_20_4_3x18,			m_20_4[2][17]);
	DDX_Control	(pDX, IDC_20_4_3x19,			m_20_4[2][18]);
	DDX_Control	(pDX, IDC_20_4_3x20,			m_20_4[2][19]);

	DDX_Control	(pDX, IDC_20_4_4x1,				m_20_4[3][0]);
	DDX_Control	(pDX, IDC_20_4_4x2,				m_20_4[3][1]);
	DDX_Control	(pDX, IDC_20_4_4x3,				m_20_4[3][2]);
	DDX_Control	(pDX, IDC_20_4_4x4,				m_20_4[3][3]);
	DDX_Control	(pDX, IDC_20_4_4x5,				m_20_4[3][4]);
	DDX_Control	(pDX, IDC_20_4_4x6,				m_20_4[3][5]);
	DDX_Control	(pDX, IDC_20_4_4x7,				m_20_4[3][6]);
	DDX_Control	(pDX, IDC_20_4_4x8,				m_20_4[3][7]);
	DDX_Control	(pDX, IDC_20_4_4x9,				m_20_4[3][8]);
	DDX_Control	(pDX, IDC_20_4_4x10,			m_20_4[3][9]);
	DDX_Control	(pDX, IDC_20_4_4x11,			m_20_4[3][10]);
	DDX_Control	(pDX, IDC_20_4_4x12,			m_20_4[3][11]);
	DDX_Control	(pDX, IDC_20_4_4x13,			m_20_4[3][12]);
	DDX_Control	(pDX, IDC_20_4_4x14,			m_20_4[3][13]);
	DDX_Control	(pDX, IDC_20_4_4x15,			m_20_4[3][14]);
	DDX_Control	(pDX, IDC_20_4_4x16,			m_20_4[3][15]);
	DDX_Control	(pDX, IDC_20_4_4x17,			m_20_4[3][16]);
	DDX_Control	(pDX, IDC_20_4_4x18,			m_20_4[3][17]);
	DDX_Control	(pDX, IDC_20_4_4x19,			m_20_4[3][18]);
	DDX_Control	(pDX, IDC_20_4_4x20,			m_20_4[3][19]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGaad_20_4, CDialog)
	//{{AFX_MSG_MAP(CDLGaad_20_4)
	ON_WM_TIMER()

	ON_BN_CLICKED	(IDC_CDE_INCONUE,	OnComErreur)
	ON_BN_CLICKED	(IDC_DEBUT_TRAME,	OnComErreur)
	ON_BN_CLICKED	(IDC_FIN_TRAME,		OnComErreur)
	ON_EN_KILLFOCUS	(IDC_RETARD,		OnComErreur)
	ON_BN_CLICKED	(IDC_PAS_REPONSE,	OnComErreur)
	
	ON_BN_CLICKED	(IDC_20_4_Valider, OnButtonValider)
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
void CDLGaad_20_4::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_AAD_20_4,"Matrice AAD 20x4");
	if(iResult >=  0)
	{
		win.DoModal();
	}
}

/* **************************************************************************
METHODE :		OnInitDialog() 
TRAITEMENT:		Initialisation de la boite de dialogue
***************************************************************************	*/
BOOL CDLGaad_20_4::OnInitDialog() 
{
	t_ComErreur	err;
	char		buf[10];
	int			i;

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
	for(i=0; i< ((CEquipAAD*)equip)->NB_ANTENNES; i++)
	{
		EtatAntenne_20_4[i].AddString("Absent");
		EtatAntenne_20_4[i].AddString("Correct");
		EtatAntenne_20_4[i].AddString("AlimHS");
		EtatAntenne_20_4[i].AddString("Surchauffe");
		switch (((CEquipAAD*)equip)->TAB_ANTENNE[i])
		{
		case ABSENT0:
			EtatAntenne_20_4[i].SetCurSel(0);
			break;
		case CORRECT0:
			EtatAntenne_20_4[i].SetCurSel(1);
			break;
		case ALIM_HS0:
			EtatAntenne_20_4[i].SetCurSel(2);
			break;
		case SURCHAUFFE0:
			EtatAntenne_20_4[i].SetCurSel(3);
			break;
		default:
			break;
		}
	}

	for(i=0; i<((CEquipAAD*)equip)->NB_PREAMPLIS; i++)
	{
		EtatPreampli_20_4[i].AddString("Absent");
		EtatPreampli_20_4[i].AddString("Correct");
		EtatPreampli_20_4[i].AddString("Defaut");
		switch (((CEquipAAD*)equip)->TAB_PREAMPLI[i])
		{
		case ABSENT1:
			EtatPreampli_20_4[i].SetCurSel(0);
			break;
		case CORRECT1:
			EtatPreampli_20_4[i].SetCurSel(1);
			break;
		case DEFAUT1:
			EtatPreampli_20_4[i].SetCurSel(2);
			break;
		default:
			break;
		}
	}

	for(i=0; i< ((CEquipAAD*)equip)->NB_AMPLIS; i++)
	{
		EtatAmpli_20_4[i].AddString("Absent");
		EtatAmpli_20_4[i].AddString("Correct");
		EtatAmpli_20_4[i].AddString("Defaut");
		switch (((CEquipAAD*)equip)->TAB_AMPLI[i])
		{
		case ABSENT1:
			EtatAmpli_20_4[i].SetCurSel(0);
			break;
		case CORRECT1:
			EtatAmpli_20_4[i].SetCurSel(1);
			break;
		case DEFAUT1:
			EtatAmpli_20_4[i].SetCurSel(2);
			break;
		default:
			break;
		}
	}

	UpdateData(FALSE);

	return TRUE;
}


/* **************************************************************************
METHODE :		GenerateurAuto()
TRAITEMENT:		Effectue les variations automatiques de certains composants
***************************************************************************	*/
void CDLGaad_20_4::GenerateurAuto()
{
	// Aucune variation automatique sur cet equipement
}

/* **************************************************************************
METHODE :		OnTimer(UINT nIDEvent) 
TRAITEMENT:		Rafraichissement de l'ecran de controle
***************************************************************************	*/
void CDLGaad_20_4::OnTimer(UINT nIDEvent) 
{
	int	 val, i, j;
	//char buf[10];		2009-11-27

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

	for(i=0; i<((CEquipAAD*)equip)->NB_ANTENNES; i++)
	{
		for(j=0; j<NB_VOIES; j++)
		{
			if(((CEquipAAD*)equip)->MATRICE_20_4[i][j] == true)
				m_20_4[i][j].SetBitmap(bmp_BLACK);
			else
				m_20_4[i][j].SetBitmap(bmp_WHITE);
		}
	}

	UpdateData(FALSE);
}

/* **************************************************************************
METHODE :		OnComErreur()
TRAITEMENT:		
***************************************************************************	*/
void CDLGaad_20_4::OnComErreur() 
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
void CDLGaad_20_4::Verrouille(BOOL etat)
{
	// Pas de verouillage sur cet equipement
}

/* **************************************************************************
METHODE :		OnButtonValider()
TRAITEMENT:		Evenement bouton Valider
***************************************************************************	*/
void CDLGaad_20_4::OnButtonValider()
{
	int i, temp;
	
	for(i=0; i< ((CEquipAAD*)equip)->NB_ANTENNES ; i++)
	{
		temp = EtatAntenne_20_4[i].GetCurSel();
		switch (temp)
		{
			// ABSENT0
		case 0:
			((CEquipAAD*)equip)->ChgtEtatAntenne(i, 0);
			break;
		// CORRECT0
		case 1:
			((CEquipAAD*)equip)->ChgtEtatAntenne(i, 1);
			break;
		// ALIM_HS0
		case 2:
			((CEquipAAD*)equip)->ChgtEtatAntenne(i, 2);
			break;
		// SURCHAUFFE0
		case 3:
			((CEquipAAD*)equip)->ChgtEtatAntenne(i, 3);
			break;
		default:
			break;
		}
	}

	for(i=0; i< ((CEquipAAD*)equip)->NB_PREAMPLIS; i++)
	{
		temp = EtatPreampli_20_4[i].GetCurSel();
		switch (temp)
		{
		// ABSENT1
		case 0:
			((CEquipAAD*)equip)->ChgtEtatPreampli(i, 0);
			break;
		// CORRECT1
		case 1:
			((CEquipAAD*)equip)->ChgtEtatPreampli(i, 1);
			break;
		// DEFAUT1
		case 2:
			((CEquipAAD*)equip)->ChgtEtatPreampli(i, 2);
			break;
		default:
			break;
		}
	}

	for(i=0; i< ((CEquipAAD*)equip)->NB_AMPLIS ; i++)
	{
		temp = EtatAmpli_20_4[i].GetCurSel();
		switch (temp)
		{
		// ABSENT1
		case 0:
			((CEquipAAD*)equip)->ChgtEtatAmpli(i, 0);
			break;
		// CORRECT1
		case 1:
			((CEquipAAD*)equip)->ChgtEtatAmpli(i, 1);
			break;
		// DEFAUT1
		case 2:
			((CEquipAAD*)equip)->ChgtEtatAmpli(i, 2);
			break;
		default:
			break;
		}
	}
}