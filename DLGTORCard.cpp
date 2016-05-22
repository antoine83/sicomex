/* **************************************************************************
FICHIER :	DlgTORCard.CPP		 		AUTEUR : FSA
DATE DE CREATION : 	08/01/07			DERNIERE MODIFICATION : 10/01/07
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgTORCard
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "DLGTORCard.h"
#include "DlgAide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char glob_HELP_TOR[];
/////////////////////////////////////////////////////////////////////////////
// CDLGTORCard dialog


CDLGTORCard::CDLGTORCard(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDLGTORCard::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGTORCard)
	m_err_retard	= _T("");
	m_periode		= _T("");
	m_tempo			= _T("");
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDLGTORCard::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGTORCard)
	DDX_Control (pDX, IDC_CHECK_SYNCHRO,m_synchro);
	DDX_Control (pDX, IDC_CHECK_CYCLE,	m_cycle);
	DDX_Text	(pDX, IDC_RETARD,		m_err_retard);
	DDX_Text	(pDX, IDC_EDIT_CYCLE,	m_periode);
	DDX_Text	(pDX, IDC_EDIT_TEMPO,	m_tempo);
	DDX_Control	(pDX, IDC_MES_STATUT,	m_liste_message);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGTORCard, CDialog)
	//{{AFX_MSG_MAP(CDLGTORCard)
	ON_BN_CLICKED(IDC_INPUT_0, OnInput0Clicked)
	ON_BN_CLICKED(IDC_INPUT_1, OnInput1Clicked)
	ON_BN_CLICKED(IDC_INPUT_2, OnInput2Clicked)
	ON_BN_CLICKED(IDC_INPUT_3, OnInput3Clicked)
	ON_BN_CLICKED(IDC_INPUT_4, OnInput4Clicked)
	ON_BN_CLICKED(IDC_INPUT_5, OnInput5Clicked)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CDE_INCONUE, OnComErreur)
	ON_BN_CLICKED(IDC_DEBUT_TRAME, OnComErreur)
	ON_BN_CLICKED(IDC_FIN_TRAME, OnComErreur)
	ON_EN_KILLFOCUS(IDC_RETARD, OnComErreur)
	ON_BN_CLICKED(IDC_PAS_REPONSE, OnComErreur)
	//}}AFX_MSG_MAP
	ON_WM_CLOSE()
	ON_WM_PAINT()

// Activation des tache de comm
	ON_COMMAND(IDC_ACTIVITE, OnActivite)

// Aide
// TODO - ON_COMMAND(ID__AIDE, OnAide)

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
	ON_BN_CLICKED	(IDC_AJOUT_MESSAGE,				OnAjoutMessage)
	ON_BN_CLICKED	(IDC_RETIRE_MESSAGE,			OnRetireMessage)
	ON_BN_CLICKED	(IDC_CHECK_CYCLE,				OnCheckCycle)
	ON_BN_CLICKED	(IDC_CHECK_SYNCHRO,				OnCheckSynchro)
	ON_EN_KILLFOCUS	(IDC_EDIT_CYCLE,				OnKillfocusEditCycle)
	ON_EN_KILLFOCUS	(IDC_EDIT_TEMPO,				OnKillfocusEditTempo)
	ON_BN_CLICKED	(IDC_ENVOI_STATUT,				OnEnvoiStatut)
	ON_BN_CLICKED	(IDC_ARRET_STATUT,				OnArretStatut)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDLGTORCard message handlers

BOOL CDLGTORCard::OnInitDialog()
{
	char		buf[10];

	// Call the super function.
	CDialog::OnInitDialog();

	//	Set the timer
	SetTimer(1,1000,NULL);

	// Initialize message part.
	GetDlgItem(IDC_ENVOI_STATUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARRET_STATUT)->EnableWindow(FALSE);
	sprintf(buf,"%d",equip->DureeTempo());
	m_tempo = buf;
	sprintf(buf,"%d",equip->Periode());
	m_periode = buf;
	m_cycle.SetCheck(equip->EnvoiCyclique());
	m_synchro.SetCheck(equip->Synchronise());

	// Set the ERROR messages.
	// TODO - m_liste_message.AddString("Erreur de parité en réception côté chiffreur");

	// Custom control
	// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);
	m_inputLed[0].SubclassDlgItem(INPUT_0_INFO,this);
	m_inputLed[1].SubclassDlgItem(INPUT_1_INFO,this);
	m_inputLed[2].SubclassDlgItem(INPUT_2_INFO,this);
	m_inputLed[3].SubclassDlgItem(INPUT_3_INFO,this);
	m_inputLed[4].SubclassDlgItem(INPUT_4_INFO,this);
	m_inputLed[5].SubclassDlgItem(INPUT_5_INFO,this);
	m_inputStatus[0].SubclassDlgItem(IDC_INPUT_0,this);
	m_inputStatus[1].SubclassDlgItem(IDC_INPUT_1,this);
	m_inputStatus[2].SubclassDlgItem(IDC_INPUT_2,this);
	m_inputStatus[3].SubclassDlgItem(IDC_INPUT_3,this);
	m_inputStatus[4].SubclassDlgItem(IDC_INPUT_4,this);
	m_inputStatus[5].SubclassDlgItem(IDC_INPUT_5,this);
	m_outputStatus[0].SubclassDlgItem(IDC_OUTPUT_0,this);
	m_outputStatus[1].SubclassDlgItem(IDC_OUTPUT_1,this);
	m_outputStatus[2].SubclassDlgItem(IDC_OUTPUT_2,this);
	m_outputStatus[3].SubclassDlgItem(IDC_OUTPUT_3,this);
	m_outputStatus[4].SubclassDlgItem(IDC_OUTPUT_4,this);
	m_outputStatus[5].SubclassDlgItem(IDC_OUTPUT_5,this);
	m_outputStatus[6].SubclassDlgItem(IDC_OUTPUT_6,this);
	m_outputStatus[7].SubclassDlgItem(IDC_OUTPUT_7,this);
	m_outputStatus[8].SubclassDlgItem(IDC_OUTPUT_8,this);
	m_outputStatus[9].SubclassDlgItem(IDC_OUTPUT_9,this);
	m_keyNumber.SubclassDlgItem(IDC_TOR_NUM_CLE,this);

	if (((CEquipTORCard *) equip)->getType() == TYPE_TOR_ANDVT) {
		// Set not visible the key fields.
		GetDlgItem(IDC_TOR_KEY_TITLE)->CloseWindow();
		m_keyNumber.CloseWindow();
	} else if (((CEquipTORCard *) equip)->getType() == TYPE_TOR_KY58) {
		GetDlgItem(IDC_TOR_OUTPUT_7)->CloseWindow();
		m_outputStatus[7].CloseWindow();
	}
	if (((CEquipTORCard *) equip)->getType() != TYPE_TOR_CARD) {
		GetDlgItem(IDC_TOR_OUTPUT_8)->CloseWindow();
		m_outputStatus[8].CloseWindow();
		GetDlgItem(IDC_TOR_OUTPUT_9)->CloseWindow();
		m_outputStatus[9].CloseWindow();
	}

	refresh();

	UpdateData(FALSE);

	return true;
}

void CDLGTORCard::refresh() {
	// Set the default key number.
	if (((CEquipTORCard *) equip)->getType() != TYPE_TOR_ANDVT) {
		if ( ((CEquipTORCard *) equip)->getKey() == -1) {
			m_keyNumber.SetWindowText("");
		} else {
			onKeyChange( ((CEquipTORCard *) equip)->getKey() );
		}
	}
	// Set the input values.
	int i;
	for(i=0; i<INPUT_COUNT ; i++) {
		m_inputStatus[i].Positionne_etat(((CEquipTORCard *) equip)->getInputValue(i));
		m_inputLed[i].Positionne_etat(((CEquipTORCard *) equip)->getInputMaskValue(i));
	}
	// Set the outputs values.
	for(i=0; i<OUTPUT_COUNT ; i++) {
		m_outputStatus[i].Positionne_etat(((CEquipTORCard *) equip)->getOutputValue(i));
	}
}

// Comm erreur ********************************************
void CDLGTORCard::OnComErreur()
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

/////////////////////////////////////////////////////////////////////////////
// CDlgCommutationMatrix message handlers

void CDLGTORCard::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_TOR,"Carte TOR");
	if(iResult >=  0) win.DoModal();
}

// OnTimer : Rafraichissement de l'écran de controle **************************
// ****************************************************************************
void CDLGTORCard::OnTimer(UINT nIDEvent)
{
	//int			val;			//2009-11-27
	//char		buf[10];			//2009-11-27

	UpdateData(TRUE);

	CDialog::OnTimer(nIDEvent);
	CDlgEquip::OnTimer();			// Rafraichissement des controles commun

	UpdateData(FALSE);
}

void CDLGTORCard::OnEnvoiTrame()
{

	char	commande[TAILLE_PIPE_MESSAGE+1];

	CEdit	*m_trame	 = (CEdit*)GetDlgItem(IDC_TRAME);

	// recuperer la commande.
	m_trame->GetLine(0,commande,TAILLE_PIPE_MESSAGE);

	if(strlen(commande)==0) return;	// Chaine vide

	equip->proto->TraiteTC(commande);
}

// Externals actions.

/**
 * Set the 'index' input value.
 */
void CDLGTORCard::onInputValueChange(int index) {
	m_inputStatus[index].Positionne_etat(((CEquipTORCard *) equip)->getInputValue(index));
}

/**
 * Set the 'index' output value.
 */
void CDLGTORCard::onOutputValueChange(int index) {
	m_outputStatus[index].Positionne_etat(((CEquipTORCard *) equip)->getOutputValue(index));
}

/**
 * Set the 'index' input mask value.
 */
void CDLGTORCard::onInputMaskValueChange(int index) {
	m_inputLed[index].Positionne_etat(((CEquipTORCard *) equip)->getInputMaskValue(index));
}

void CDLGTORCard::onKeyChange(int key) {
	if ( key < 0 || key > 7 ) {
		return;
	}
	char value[2] = "\0";
	sprintf(value,"%d",key);
	m_keyNumber.SetWindowText(value);
}

// Callbacks.

void CDLGTORCard::OnInput0Clicked()
{
	((CEquipTORCard *)equip)->setInput(0,!m_inputStatus[0].Retourne_etat());
}

void CDLGTORCard::OnInput1Clicked()
{
	((CEquipTORCard *)equip)->setInput(1,!m_inputStatus[1].Retourne_etat());
}

void CDLGTORCard::OnInput2Clicked()
{
	((CEquipTORCard *)equip)->setInput(2,!m_inputStatus[2].Retourne_etat());
}

void CDLGTORCard::OnInput3Clicked()
{
	((CEquipTORCard *)equip)->setInput(3,!m_inputStatus[3].Retourne_etat());
}

void CDLGTORCard::OnInput4Clicked()
{
	((CEquipTORCard *)equip)->setInput(4,!m_inputStatus[4].Retourne_etat());
}

void CDLGTORCard::OnInput5Clicked()
{
	((CEquipTORCard *)equip)->setInput(5,!m_inputStatus[5].Retourne_etat());
}

