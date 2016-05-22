/* **************************************************************************
FICHIER :	DlgAudio.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgAudi
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "DlgAudio.h"
#include "Equip\EqpAudi.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_HELP_AUDIO[];

CDlgAudio::CDlgAudio(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDlgAudio::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAudio)
	m_err_retard = _T("");
	m_test = _T("");
	m_periode = _T("");
	m_tempo = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAudio::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAudio)
	DDX_Control(pDX, IDC_MES_STATUT, m_liste_message);
	DDX_Control(pDX, IDC_CHECK_SYNCHRO, m_synchro);
	DDX_Control(pDX, IDC_CHECK_CYCLE, m_cycle);
	DDX_Text(pDX, IDC_RETARD, m_err_retard);
	DDX_Text(pDX, F6_TEST, m_test);
	DDX_Text(pDX, IDC_EDIT_CYCLE, m_periode);
	DDX_Text(pDX, IDC_EDIT_TEMPO, m_tempo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAudio, CDialog)
	//{{AFX_MSG_MAP(CDlgAudio)
	ON_WM_TIMER()
	ON_EN_KILLFOCUS(F6_TEST, OnKillfocusTest)
	ON_BN_CLICKED(F6_RELAIS_03_01, OnRelais0301)
	ON_BN_CLICKED(F6_RELAIS_03_02, OnRelais0302)
	ON_BN_CLICKED(F6_RELAIS_03_03, OnRelais0303)
	ON_BN_CLICKED(F6_RELAIS_03_04, OnRelais0304)
	ON_BN_CLICKED(F6_RELAIS_03_05, OnRelais0305)
	ON_BN_CLICKED(F6_RELAIS_03_06, OnRelais0306)
	ON_BN_CLICKED(F6_RELAIS_03_07, OnRelais0307)
	ON_BN_CLICKED(F6_RELAIS_03_08, OnRelais0308)
	ON_BN_CLICKED(F6_RELAIS_03_09, OnRelais0309)
	ON_BN_CLICKED(F6_RELAIS_03_10, OnRelais0310)
	ON_BN_CLICKED(F6_RELAIS_03_11, OnRelais0311)
	ON_BN_CLICKED(F6_RELAIS_03_12, OnRelais0312)
	ON_BN_CLICKED(F6_RELAIS_03_13, OnRelais0313)
	ON_BN_CLICKED(F6_RELAIS_03_14, OnRelais0314)
	ON_BN_CLICKED(F6_RELAIS_03_15, OnRelais0315)
	ON_BN_CLICKED(F6_RELAIS_03_16, OnRelais0316)
	ON_BN_CLICKED(F6_RELAIS_03_17, OnRelais0317)
	ON_BN_CLICKED(F6_RELAIS_03_18, OnRelais0318)
	ON_BN_CLICKED(F6_RELAIS_03_19, OnRelais0319)
	ON_BN_CLICKED(F6_RELAIS_03_20, OnRelais0320)
	ON_BN_CLICKED(IDC_DEBUT_TRAME, OnComErreur)
	ON_BN_CLICKED(F6_CHIFFRE1_RX, OnChiffre1Rx)
	ON_BN_CLICKED(F6_CHIFFRE1_TX, OnChiffre1Tx)
	ON_BN_CLICKED(F6_CHIFFRE2_RX, OnChiffre2Rx)
	ON_BN_CLICKED(F6_CHIFFRE2_TX, OnChiffre2Tx)
	ON_BN_CLICKED(F6_CLAIRE1_RX, OnClaire1Rx)
	ON_BN_CLICKED(F6_CLAIRE1_TX, OnClaire1Tx)
	ON_BN_CLICKED(F6_CLAIRE2_RX, OnClaire2Rx)
	ON_BN_CLICKED(F6_CLAIRE2_TX, OnClaire2Tx)
	ON_BN_CLICKED(F6_MAGNETO1_RX, OnMagneto1Rx)
	ON_BN_CLICKED(F6_MAGNETO1_TX, OnMagneto1Tx)
	ON_BN_CLICKED(F6_MAGNETO2_RX, OnMagneto2Rx)
	ON_BN_CLICKED(F6_MAGNETO2_TX, OnMagneto2Tx)
	ON_BN_CLICKED(F6_RELAIS_09_01, OnRelais0901)
	ON_BN_CLICKED(F6_RELAIS_09_02, OnRelais0902)
	ON_BN_CLICKED(F6_RELAIS_09_03, OnRelais0903)
	ON_BN_CLICKED(F6_RELAIS_09_04, OnRelais0904)
	ON_BN_CLICKED(F6_RELAIS_09_05, OnRelais0905)
	ON_BN_CLICKED(F6_RELAIS_09_06, OnRelais0906)
	ON_BN_CLICKED(F6_RELAIS_09_07, OnRelais0907)
	ON_BN_CLICKED(F6_RELAIS_09_08, OnRelais0908)
	ON_BN_CLICKED(F6_RELAIS_09_09, OnRelais0909)
	ON_BN_CLICKED(F6_RELAIS_09_10, OnRelais0910)
	ON_BN_CLICKED(F6_RELAIS_09_11, OnRelais0911)
	ON_BN_CLICKED(F6_RELAIS_09_12, OnRelais0912)
	ON_BN_CLICKED(F6_RELAIS_09_13, OnRelais0913)
	ON_BN_CLICKED(F6_RELAIS_09_14, OnRelais0914)
	ON_BN_CLICKED(F6_RELAIS_09_15, OnRelais0915)
	ON_BN_CLICKED(F6_RELAIS_09_16, OnRelais0916)
	ON_BN_CLICKED(F6_RELAIS_09_17, OnRelais0917)
	ON_BN_CLICKED(F6_RELAIS_09_18, OnRelais0918)
	ON_BN_CLICKED(F6_RELAIS_09_19, OnRelais0919)
	ON_BN_CLICKED(F6_RELAIS_09_20, OnRelais0920)
	ON_BN_CLICKED(F6_RELAIS_11_01, OnRelais1101)
	ON_BN_CLICKED(F6_RELAIS_11_02, OnRelais1102)
	ON_BN_CLICKED(F6_RELAIS_11_03, OnRelais1103)
	ON_BN_CLICKED(F6_RELAIS_11_04, OnRelais1104)
	ON_BN_CLICKED(F6_RELAIS_11_05, OnRelais1105)
	ON_BN_CLICKED(F6_RELAIS_11_06, OnRelais1106)
	ON_BN_CLICKED(F6_RELAIS_11_07, OnRelais1107)
	ON_BN_CLICKED(F6_RELAIS_11_08, OnRelais1108)
	ON_BN_CLICKED(F6_RELAIS_11_09, OnRelais1109)
	ON_BN_CLICKED(F6_RELAIS_11_10, OnRelais1110)
	ON_BN_CLICKED(F6_RELAIS_11_11, OnRelais1111)
	ON_BN_CLICKED(F6_RELAIS_11_12, OnRelais1112)
	ON_BN_CLICKED(F6_RELAIS_11_13, OnRelais1113)
	ON_BN_CLICKED(F6_RELAIS_11_14, OnRelais1114)
	ON_BN_CLICKED(F6_RELAIS_11_15, OnRelais1115)
	ON_BN_CLICKED(F6_RELAIS_11_16, OnRelais1116)
	ON_BN_CLICKED(F6_RELAIS_11_17, OnRelais1117)
	ON_BN_CLICKED(F6_RELAIS_11_18, OnRelais1118)
	ON_BN_CLICKED(F6_RELAIS_11_19, OnRelais1119)
	ON_BN_CLICKED(F6_RELAIS_11_20, OnRelais1120)
	ON_BN_CLICKED(F6_RELAIS_13_01, OnRelais1301)
	ON_BN_CLICKED(F6_RELAIS_13_02, OnRelais1302)
	ON_BN_CLICKED(F6_RELAIS_13_03, OnRelais1303)
	ON_BN_CLICKED(F6_RELAIS_13_04, OnRelais1304)
	ON_BN_CLICKED(F6_RELAIS_13_05, OnRelais1305)
	ON_BN_CLICKED(F6_RELAIS_13_06, OnRelais1306)
	ON_BN_CLICKED(F6_RELAIS_13_07, OnRelais1307)
	ON_BN_CLICKED(F6_RELAIS_13_08, OnRelais1308)
	ON_BN_CLICKED(F6_RELAIS_13_09, OnRelais1309)
	ON_BN_CLICKED(F6_RELAIS_13_10, OnRelais1310)
	ON_BN_CLICKED(F6_RELAIS_13_11, OnRelais1311)
	ON_BN_CLICKED(F6_RELAIS_13_12, OnRelais1312)
	ON_BN_CLICKED(F6_RELAIS_13_13, OnRelais1313)
	ON_BN_CLICKED(F6_RELAIS_13_14, OnRelais1314)
	ON_BN_CLICKED(F6_RELAIS_13_15, OnRelais1315)
	ON_EN_KILLFOCUS(IDC_RETARD, OnComErreur)
	ON_BN_CLICKED(IDC_PAS_REPONSE, OnComErreur)
	ON_BN_CLICKED(IDC_FIN_TRAME, OnComErreur)
	ON_BN_CLICKED(IDC_CDE_INCONUE, OnComErreur)
	//}}AFX_MSG_MAP

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

void CDlgAudio::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_AUDIO,"Standard Audio/TTY");
	if(iResult >=  0) win.DoModal();
}

/////////////////////////////////////////////////////////////////////////////
// CDlgAudio message handlers

BOOL CDlgAudio::OnInitDialog() 
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
	m_liste_message.AddString("Temporisation");
	m_liste_message.AddString("Test interne");


// Custom control
// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);	

// Initialisation de la face avant
// *******************************
	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// OnTimer : Rafraichissement de l'écran de controle **************************
// ****************************************************************************
void CDlgAudio::OnTimer(UINT nIDEvent) 
{
	int		val;
	char	buf[10];

	UpdateData(TRUE);

	CDialog::OnTimer(nIDEvent);
	CDlgEquip::OnTimer();			// Rafraichissement des controles commun

// Test de changement dans la face avant
	val = equip->Evolution();
	if (val==evolution) return;		// Rafraichissement inutile
	evolution = val;

	Verrouille(!((CEquipAudio*)equip)->Lock());
		
// Code Test
	if(GetDlgItem(F6_TEST) != GetFocus())
	{
		sprintf(buf,"%d",((CEquipAudio*)equip)->Test());
		m_test = buf;
	}

// Etat relais
	// PPL1
		val = ((CEquipAudio*)equip)->EtatRelais(3,11);
		SendDlgItemMessage(F6_RELAIS_03_11,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,16);
		SendDlgItemMessage(F6_RELAIS_03_16,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,1);
		SendDlgItemMessage(F6_RELAIS_03_01,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,6);
		SendDlgItemMessage(F6_RELAIS_03_06,BM_SETCHECK,val,0);

	// PPL2
		val = ((CEquipAudio*)equip)->EtatRelais(3,12);
		SendDlgItemMessage(F6_RELAIS_03_12,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,17);
		SendDlgItemMessage(F6_RELAIS_03_17,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,2);
		SendDlgItemMessage(F6_RELAIS_03_02,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,7);
		SendDlgItemMessage(F6_RELAIS_03_07,BM_SETCHECK,val,0);

	// PPL3
		val = ((CEquipAudio*)equip)->EtatRelais(3,13);
		SendDlgItemMessage(F6_RELAIS_03_13,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,18);
		SendDlgItemMessage(F6_RELAIS_03_18,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,3);
		SendDlgItemMessage(F6_RELAIS_03_03,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,8);
		SendDlgItemMessage(F6_RELAIS_03_08,BM_SETCHECK,val,0);

	// TTY1
		val = ((CEquipAudio*)equip)->EtatRelais(3,14);
		SendDlgItemMessage(F6_RELAIS_03_14,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,19);
		SendDlgItemMessage(F6_RELAIS_03_19,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,4);
		SendDlgItemMessage(F6_RELAIS_03_04,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,9);
		SendDlgItemMessage(F6_RELAIS_03_09,BM_SETCHECK,val,0);

	// TTY2
		val = ((CEquipAudio*)equip)->EtatRelais(3,15);
		SendDlgItemMessage(F6_RELAIS_03_15,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,20);
		SendDlgItemMessage(F6_RELAIS_03_20,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,5);
		SendDlgItemMessage(F6_RELAIS_03_05,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(3,10);
		SendDlgItemMessage(F6_RELAIS_03_10,BM_SETCHECK,val,0);

	// HF1
		val = ((CEquipAudio*)equip)->EtatRelais(11,1);
		SendDlgItemMessage(F6_RELAIS_11_01,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,2);
		SendDlgItemMessage(F6_RELAIS_11_02,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,11);
		SendDlgItemMessage(F6_RELAIS_11_11,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,12);
		SendDlgItemMessage(F6_RELAIS_11_12,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,1);
		SendDlgItemMessage(F6_RELAIS_09_01,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,2);
		SendDlgItemMessage(F6_RELAIS_09_02,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,11);
		SendDlgItemMessage(F6_RELAIS_09_11,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,12);
		SendDlgItemMessage(F6_RELAIS_09_12,BM_SETCHECK,val,0);

	// HF2
		val = ((CEquipAudio*)equip)->EtatRelais(11,3);
		SendDlgItemMessage(F6_RELAIS_11_03,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,4);
		SendDlgItemMessage(F6_RELAIS_11_04,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,13);
		SendDlgItemMessage(F6_RELAIS_11_13,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,14);
		SendDlgItemMessage(F6_RELAIS_11_14,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,3);
		SendDlgItemMessage(F6_RELAIS_09_03,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,4);
		SendDlgItemMessage(F6_RELAIS_09_04,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,13);
		SendDlgItemMessage(F6_RELAIS_09_13,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,14);
		SendDlgItemMessage(F6_RELAIS_09_14,BM_SETCHECK,val,0);

	// HF3
		val = ((CEquipAudio*)equip)->EtatRelais(11,5);
		SendDlgItemMessage(F6_RELAIS_11_05,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,6);
		SendDlgItemMessage(F6_RELAIS_11_06,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,15);
		SendDlgItemMessage(F6_RELAIS_11_15,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,16);
		SendDlgItemMessage(F6_RELAIS_11_16,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,5);
		SendDlgItemMessage(F6_RELAIS_09_05,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,6);
		SendDlgItemMessage(F6_RELAIS_09_06,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,15);
		SendDlgItemMessage(F6_RELAIS_09_15,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,16);
		SendDlgItemMessage(F6_RELAIS_09_16,BM_SETCHECK,val,0);

	// UHF1
		val = ((CEquipAudio*)equip)->EtatRelais(11,7);
		SendDlgItemMessage(F6_RELAIS_11_07,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,8);
		SendDlgItemMessage(F6_RELAIS_11_08,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,17);
		SendDlgItemMessage(F6_RELAIS_11_17,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,18);
		SendDlgItemMessage(F6_RELAIS_11_18,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,7);
		SendDlgItemMessage(F6_RELAIS_09_07,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,8);
		SendDlgItemMessage(F6_RELAIS_09_08,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,17);
		SendDlgItemMessage(F6_RELAIS_09_17,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,18);
		SendDlgItemMessage(F6_RELAIS_09_18,BM_SETCHECK,val,0);

	// UHF2
		val = ((CEquipAudio*)equip)->EtatRelais(11,9);
		SendDlgItemMessage(F6_RELAIS_11_09,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,10);
		SendDlgItemMessage(F6_RELAIS_11_10,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,19);
		SendDlgItemMessage(F6_RELAIS_11_19,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(11,20);
		SendDlgItemMessage(F6_RELAIS_11_20,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,9);
		SendDlgItemMessage(F6_RELAIS_09_09,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,10);
		SendDlgItemMessage(F6_RELAIS_09_10,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,19);
		SendDlgItemMessage(F6_RELAIS_09_19,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(9,20);
		SendDlgItemMessage(F6_RELAIS_09_20,BM_SETCHECK,val,0);

	// HF1 - Alternat
		val = ((CEquipAudio*)equip)->EtatRelais(13,5);
		SendDlgItemMessage(F6_RELAIS_13_05,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(13,10);
		SendDlgItemMessage(F6_RELAIS_13_10,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(13,15);
		SendDlgItemMessage(F6_RELAIS_13_15,BM_SETCHECK,val,0);

	// HF2 - Alternat
		val = ((CEquipAudio*)equip)->EtatRelais(13,4);
		SendDlgItemMessage(F6_RELAIS_13_04,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(13,9);
		SendDlgItemMessage(F6_RELAIS_13_09,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(13,14);
		SendDlgItemMessage(F6_RELAIS_13_14,BM_SETCHECK,val,0);

	// HF3 - Alternat
		val = ((CEquipAudio*)equip)->EtatRelais(13,3);
		SendDlgItemMessage(F6_RELAIS_13_03,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(13,8);
		SendDlgItemMessage(F6_RELAIS_13_08,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(13,13);
		SendDlgItemMessage(F6_RELAIS_13_13,BM_SETCHECK,val,0);

	// UHF1 - Alternat
		val = ((CEquipAudio*)equip)->EtatRelais(13,2);
		SendDlgItemMessage(F6_RELAIS_13_02,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(13,7);
		SendDlgItemMessage(F6_RELAIS_13_07,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(13,12);
		SendDlgItemMessage(F6_RELAIS_13_12,BM_SETCHECK,val,0);

	// UHF2 - Alternat
		val = ((CEquipAudio*)equip)->EtatRelais(13,1);
		SendDlgItemMessage(F6_RELAIS_13_01,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(13,6);
		SendDlgItemMessage(F6_RELAIS_13_06,BM_SETCHECK,val,0);

		val = ((CEquipAudio*)equip)->EtatRelais(13,11);
		SendDlgItemMessage(F6_RELAIS_13_11,BM_SETCHECK,val,0);

	// Chiffre 1
		val = 	((CEquipAudio*)equip)->EtatRelais(5,2) &&
		 		((CEquipAudio*)equip)->EtatRelais(5,7);
		SendDlgItemMessage(F6_CHIFFRE1_TX,BM_SETCHECK,val,0);

		val = 	((CEquipAudio*)equip)->EtatRelais(5,12) &&
		 		((CEquipAudio*)equip)->EtatRelais(5,17);
		SendDlgItemMessage(F6_CHIFFRE1_RX,BM_SETCHECK,val,0);

	// Chiffre 2
		val = 	((CEquipAudio*)equip)->EtatRelais(7,2) &&
		 		((CEquipAudio*)equip)->EtatRelais(7,7);
		SendDlgItemMessage(F6_CHIFFRE2_TX,BM_SETCHECK,val,0);

		val = 	((CEquipAudio*)equip)->EtatRelais(7,12) &&
		 		((CEquipAudio*)equip)->EtatRelais(7,17);
		SendDlgItemMessage(F6_CHIFFRE2_RX,BM_SETCHECK,val,0);

	// Claire 1
		val = 	((CEquipAudio*)equip)->EtatRelais(5,1) &&
		 		((CEquipAudio*)equip)->EtatRelais(5,6);
		SendDlgItemMessage(F6_CLAIRE1_TX,BM_SETCHECK,val,0);

		val = 	((CEquipAudio*)equip)->EtatRelais(5,11) &&
		 		((CEquipAudio*)equip)->EtatRelais(5,16);
		SendDlgItemMessage(F6_CLAIRE1_RX,BM_SETCHECK,val,0);

	// Claire 2
		val = 	((CEquipAudio*)equip)->EtatRelais(7,1) &&
		 		((CEquipAudio*)equip)->EtatRelais(7,6);
		SendDlgItemMessage(F6_CLAIRE2_TX,BM_SETCHECK,val,0);

		val = 	((CEquipAudio*)equip)->EtatRelais(7,11) &&
		 		((CEquipAudio*)equip)->EtatRelais(7,16);
		SendDlgItemMessage(F6_CLAIRE2_RX,BM_SETCHECK,val,0);

	// Magneto 1
		val = 	((CEquipAudio*)equip)->EtatRelais(5,8) ||
		 		((CEquipAudio*)equip)->EtatRelais(5,9);
		SendDlgItemMessage(F6_MAGNETO1_TX,BM_SETCHECK,val,0);

		val = 	((CEquipAudio*)equip)->EtatRelais(5,18) ||
		 		((CEquipAudio*)equip)->EtatRelais(5,19);
		SendDlgItemMessage(F6_MAGNETO1_RX,BM_SETCHECK,val,0);

	// Magneto 2
		val = 	((CEquipAudio*)equip)->EtatRelais(7,8) ||
		 		((CEquipAudio*)equip)->EtatRelais(7,9);
		SendDlgItemMessage(F6_MAGNETO2_TX,BM_SETCHECK,val,0);

		val = 	((CEquipAudio*)equip)->EtatRelais(7,18) ||
		 		((CEquipAudio*)equip)->EtatRelais(7,19);
		SendDlgItemMessage(F6_MAGNETO2_RX,BM_SETCHECK,val,0);

// Mise à jour de CEdit
// ********************
	UpdateData(FALSE);
}
void CDlgAudio::Verrouille(BOOL etat)
{

// test
	GetDlgItem(F6_TEST)->EnableWindow(etat);

// PPL1
	GetDlgItem(F6_RELAIS_03_11)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_16)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_01)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_06)->EnableWindow(etat);

// PPL2
	GetDlgItem(F6_RELAIS_03_12)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_17)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_02)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_07)->EnableWindow(etat);

// PPL3
	GetDlgItem(F6_RELAIS_03_13)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_18)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_03)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_08)->EnableWindow(etat);

// TTY1
	GetDlgItem(F6_RELAIS_03_14)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_19)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_04)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_09)->EnableWindow(etat);

// TTY2
	GetDlgItem(F6_RELAIS_03_15)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_20)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_05)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_03_10)->EnableWindow(etat);

// HF1
	GetDlgItem(F6_RELAIS_11_01)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_02)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_11)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_12)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_01)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_02)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_11)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_12)->EnableWindow(etat);

// HF2
	GetDlgItem(F6_RELAIS_11_03)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_04)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_13)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_14)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_03)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_04)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_13)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_14)->EnableWindow(etat);

// HF3
	GetDlgItem(F6_RELAIS_11_05)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_06)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_15)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_16)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_05)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_06)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_15)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_16)->EnableWindow(etat);

// UHF1
	GetDlgItem(F6_RELAIS_11_07)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_08)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_17)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_18)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_07)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_08)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_17)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_18)->EnableWindow(etat);

// UHF2
	GetDlgItem(F6_RELAIS_11_09)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_10)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_19)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_11_20)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_09)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_10)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_19)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_09_20)->EnableWindow(etat);

// HF1 - Alternat
	GetDlgItem(F6_RELAIS_13_05)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_13_10)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_13_15)->EnableWindow(etat);

// HF2 - Alternat
	GetDlgItem(F6_RELAIS_13_04)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_13_09)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_13_14)->EnableWindow(etat);

// HF3 - Alternat
	GetDlgItem(F6_RELAIS_13_03)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_13_08)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_13_13)->EnableWindow(etat);

// UHF1 - Alternat
	GetDlgItem(F6_RELAIS_13_02)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_13_07)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_13_12)->EnableWindow(etat);

// UHF2 - Alternat
	GetDlgItem(F6_RELAIS_13_01)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_13_06)->EnableWindow(etat);
	GetDlgItem(F6_RELAIS_13_11)->EnableWindow(etat);

// Chiffre
	GetDlgItem(F6_CHIFFRE1_TX)->EnableWindow(etat);
	GetDlgItem(F6_CHIFFRE1_RX)->EnableWindow(etat);
	GetDlgItem(F6_CHIFFRE2_TX)->EnableWindow(etat);
	GetDlgItem(F6_CHIFFRE2_RX)->EnableWindow(etat);

// Claire
	GetDlgItem(F6_CLAIRE1_TX)->EnableWindow(etat);
	GetDlgItem(F6_CLAIRE1_RX)->EnableWindow(etat);
	GetDlgItem(F6_CLAIRE2_TX)->EnableWindow(etat);
	GetDlgItem(F6_CLAIRE2_RX)->EnableWindow(etat);

// Magneto
	GetDlgItem(F6_MAGNETO1_TX)->EnableWindow(etat);
	GetDlgItem(F6_MAGNETO1_RX)->EnableWindow(etat);
	GetDlgItem(F6_MAGNETO2_TX)->EnableWindow(etat);
	GetDlgItem(F6_MAGNETO2_RX)->EnableWindow(etat);
}


void CDlgAudio::OnKillfocusTest() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquipAudio*)equip)->ChangeTest(atoi(m_test),TRUE);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0301() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,1);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,1,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0302() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,2);
	int	iResult =((CEquipAudio*)equip)->ChangeEtatRelais(3,2,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0303() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,3);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,3,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0304() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,4);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,4,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0305() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,5);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,5,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0306() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,6);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,6,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0307() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,7);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,7,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0308() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,8);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,8,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0309() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,9);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,9,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0310() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,10);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,10,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0311() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,11);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,11,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0312() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,12);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,12,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0313() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,13);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,13,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0314() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,14);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,14,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0315() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,15);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,15,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0316() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,16);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,16,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0317() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,17);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,17,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0318() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,18);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,18,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0319() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,19);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,19,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0320() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(3,20);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(3,20,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnComErreur() 
{
	t_ComErreur	err;
	
	CButton		*m_debut = (CButton*)GetDlgItem(IDC_DEBUT_TRAME);
	CButton		*m_fin = (CButton*)GetDlgItem(IDC_FIN_TRAME);
//	CButton		*m_parite = (CButton*)GetDlgItem(IDC_PARITE);
	CButton		*m_inconnue = (CButton*)GetDlgItem(IDC_CDE_INCONUE);
	CButton		*m_reponse = (CButton*)GetDlgItem(IDC_PAS_REPONSE);

	err.pas_debut		= m_debut->GetCheck();
	err.pas_fin			= m_fin->GetCheck();
	err.controle_parite	= 0;
	err.cde_inconnue	= m_inconnue->GetCheck();
	err.pas_de_reponse	= m_reponse->GetCheck();

	UpdateData(TRUE);
	err.retard = atoi(m_err_retard);

	equip->ChangeComErreur(err);
}

void CDlgAudio::OnChiffre1Rx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(5,12);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(5,12,i,TRUE);

	i = !((CEquipAudio*)equip)->EtatRelais(5,17);
	((CEquipAudio*)equip)->ChangeEtatRelais(5,17,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnChiffre1Tx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(5,2);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(5,2,i,TRUE);
	
	i = !((CEquipAudio*)equip)->EtatRelais(5,7);
	((CEquipAudio*)equip)->ChangeEtatRelais(5,7,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnChiffre2Rx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(7,12);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(7,12,i,TRUE);
	
	i = !((CEquipAudio*)equip)->EtatRelais(7,17);
	((CEquipAudio*)equip)->ChangeEtatRelais(7,17,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnChiffre2Tx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(7,2);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(7,2,i,TRUE);
	
	i = !((CEquipAudio*)equip)->EtatRelais(7,7);
	((CEquipAudio*)equip)->ChangeEtatRelais(7,7,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnClaire1Rx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(5,11);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(5,11,i,TRUE);
	
	i = !((CEquipAudio*)equip)->EtatRelais(5,16);
	((CEquipAudio*)equip)->ChangeEtatRelais(5,16,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnClaire1Tx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(5,1);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(5,1,i,TRUE);
	
	i = !((CEquipAudio*)equip)->EtatRelais(5,6);
	((CEquipAudio*)equip)->ChangeEtatRelais(5,6,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnClaire2Rx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(7,11);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(7,11,i,TRUE);
	
	i = !((CEquipAudio*)equip)->EtatRelais(7,16);
	((CEquipAudio*)equip)->ChangeEtatRelais(7,16,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnClaire2Tx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(7,1);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(7,1,i,TRUE);
	
	i = !((CEquipAudio*)equip)->EtatRelais(7,6);
	((CEquipAudio*)equip)->ChangeEtatRelais(7,6,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnMagneto1Rx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(5,18);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(5,18,i,TRUE);
	
	i = !((CEquipAudio*)equip)->EtatRelais(5,19);
	((CEquipAudio*)equip)->ChangeEtatRelais(5,19,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnMagneto1Tx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(5,8);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(5,8,i,TRUE);
	
	i = !((CEquipAudio*)equip)->EtatRelais(5,9);
	((CEquipAudio*)equip)->ChangeEtatRelais(5,9,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnMagneto2Rx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(7,18);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(7,18,i,TRUE);
	
	i = !((CEquipAudio*)equip)->EtatRelais(7,19);
	((CEquipAudio*)equip)->ChangeEtatRelais(7,19,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnMagneto2Tx() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(7,8);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(7,8,i,TRUE);
	
	i = !((CEquipAudio*)equip)->EtatRelais(7,9);
	((CEquipAudio*)equip)->ChangeEtatRelais(7,9,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0901() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,1);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,1,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0902() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,2);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,2,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0903() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,3);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,3,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0904() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,4);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,4,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0905() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,5);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,5,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0906() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,6);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,6,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0907() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,7);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,7,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0908() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,8);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,8,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0909() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,9);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,9,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0910() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,10);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,10,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0911() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,11);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,11,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0912() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,12);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,12,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0913() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,13);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,13,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0914() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,14);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,14,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0915() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,15);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,15,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0916() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,16);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,16,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0917() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,17);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,17,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0918() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,18);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,18,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0919() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,19);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,19,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais0920() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(9,20);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(9,20,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1101() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,1);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,1,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1102() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,2);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,2,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1103() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,3);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,3,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1104() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,4);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,4,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1105() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,5);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,5,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1106() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,6);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,6,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1107() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,7);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,7,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1108() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,8);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,8,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1109() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,9);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,9,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1110() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,10);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,10,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1111() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,11);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,11,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1112() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,12);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,12,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1113() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,13);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,13,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1114() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,14);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,14,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1115() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,15);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,15,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1116() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,16);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,16,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1117() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,17);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,17,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1118() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,18);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,18,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1119() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,19);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,19,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1120() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(11,20);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(11,20,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1301() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,1);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,1,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1302() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,2);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,2,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1303() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,3);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,3,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1304() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,4);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,4,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1305() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,5);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,5,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1306() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,6);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,6,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1307() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,7);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,7,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1308() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,8);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,8,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1309() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,9);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,9,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1310() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,10);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,10,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1311() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,11);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,11,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1312() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,12);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,12,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1313() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,13);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,13,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1314() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,14);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,14,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}

void CDlgAudio::OnRelais1315() 
{
	int	i = !((CEquipAudio*)equip)->EtatRelais(13,15);
	int	iResult = ((CEquipAudio*)equip)->ChangeEtatRelais(13,15,i,TRUE);
	if(iResult<0) return;	// L'ancienne valeur sera rafraichie
}
