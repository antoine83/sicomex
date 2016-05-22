/* **************************************************************************
FICHIER :	DlgCV24Card.CPP		 		AUTEUR : FSA
DATE DE CREATION : 	08/01/07			DERNIERE MODIFICATION : 10/01/07
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgCV24Card
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "DLGCV24Card.h"
#include "equip\EqpCV24Card.h"
#include "DlgAide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char glob_HELP_CV24[];
/////////////////////////////////////////////////////////////////////////////
// CDLGCV24Card dialog


CDLGCV24Card::CDLGCV24Card(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDLGCV24Card::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGCV24Card)
	m_err_retard	= _T("");
	m_periode		= _T("");
	m_tempo			= _T("");
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void CDLGCV24Card::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGCV24Card)
	DDX_Control (pDX, IDC_CHECK_SYNCHRO,m_synchro);
	DDX_Control (pDX, IDC_CHECK_CYCLE,	m_cycle);
	DDX_Text	(pDX, IDC_RETARD,		m_err_retard);
	DDX_Text	(pDX, IDC_EDIT_CYCLE,	m_periode);
	DDX_Text	(pDX, IDC_EDIT_TEMPO,	m_tempo);
	DDX_Control	(pDX, IDC_MES_STATUT,	m_liste_message);
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGCV24Card, CDialog)
	//{{AFX_MSG_MAP(CDLGCV24Card)
	ON_BN_CLICKED(IDC_INPUT_0, OnInput0Clicked)
	ON_BN_CLICKED(IDC_INPUT_1, OnInput1Clicked)
	ON_BN_CLICKED(IDC_INPUT_2, OnInput2Clicked)
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
// CDLGCV24Card message handlers

BOOL CDLGCV24Card::OnInitDialog()
{
	char		buf[10];

	// Set the operating mode.
	((CEquipCV24Card *) equip)->setOperatingMode(COMMAND_MODE);

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
	m_liste_message.AddString("Erreur de parité en réception côté chiffreur");
	m_liste_message.AddString("Commande non existante");
	m_liste_message.AddString("Commande impossible dans ce mode");
	m_liste_message.AddString("Traitement immédiat de la commande impossible");
	m_liste_message.AddString("Carte en panne");
	m_liste_message.AddString("Erreur de format en réception côté CAD");
	m_liste_message.AddString("Erreur de parité en réception côté CAD");
	m_liste_message.AddString("Erreur de débordement en réception côté CAD");
	m_liste_message.AddString("Débordement FIFO en réception côté CAD");
	m_liste_message.AddString("Impossible de vider la FIFO en réception côté CAD");
	m_liste_message.AddString("Récepteur pas en busy condition côté CAD");
	m_liste_message.AddString("Débordement temporisation 106 chiffreur");
	m_liste_message.AddString("Débordement temporisation 107 chiffreur");
	m_liste_message.AddString("Erreur de format en réception côté chiffreur");
	m_liste_message.AddString("Erreur de débordement en réception côté chiffreur");
	m_liste_message.AddString("Aucune erreur");

	// Custom control
	// **************
	m_status.SubclassDlgItem(IDC_OUTPUT_STATUS,this);
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);
	m_inputLed[0].SubclassDlgItem(INPUT_0_INFO,this);
	m_inputLed[1].SubclassDlgItem(INPUT_1_INFO,this);
	m_inputLed[2].SubclassDlgItem(INPUT_2_INFO,this);
	m_inputStatus[0].SubclassDlgItem(IDC_INPUT_0,this);
	m_inputStatus[1].SubclassDlgItem(IDC_INPUT_1,this);
	m_inputStatus[2].SubclassDlgItem(IDC_INPUT_2,this);
	m_outputStatus[0].SubclassDlgItem(IDC_OUTPUT_0,this);
	m_outputStatus[1].SubclassDlgItem(IDC_OUTPUT_1,this);
	m_outputStatus[2].SubclassDlgItem(IDC_OUTPUT_2,this);
	m_outputStatus[3].SubclassDlgItem(IDC_OUTPUT_3,this);
	m_outputStatus[4].SubclassDlgItem(IDC_OUTPUT_4,this);
	m_outputStatus[5].SubclassDlgItem(IDC_OUTPUT_5,this);
	m_outputStatus[6].SubclassDlgItem(IDC_OUTPUT_6,this);
	m_outputStatus[7].SubclassDlgItem(IDC_OUTPUT_14,this);
	m_keyNumber.SubclassDlgItem(IDC_NUM_CLE,this);

	if (((CEquipCV24Card *) equip)->getType() == CV24_ANDVT) {
		// Set not visible the key fields.
		GetDlgItem(IDC_CV24_KEY_TITLE)->CloseWindow();
		m_keyNumber.CloseWindow();
	} else if (((CEquipCV24Card *) equip)->getType() == CV24_KY58) {
		GetDlgItem(IDC_CV24_OUTPUT_14)->CloseWindow();
		m_outputStatus[7].CloseWindow();
	}

	refresh();

	UpdateData(FALSE);

	return true;
}

void CDLGCV24Card::refresh() {
	// Set the default key number.
	if (((CEquipCV24Card *) equip)->getType() == CV24_KY58) {
		if ( ((CEquipCV24Card *) equip)->getKey() == -1) {
			m_keyNumber.SetWindowText("");
		} else {
			onKeyChange( ((CEquipCV24Card *) equip)->getKey() );
		}
	}
	// Set the status.
	m_status.Positionne_etat(((CEquipCV24Card *) equip)->getStatus());
	// Set the input values.
	int i;
	for(i=0; i<3 ; i++) {
		m_inputStatus[i].Positionne_etat(((CEquipCV24Card *) equip)->getInputValue(i));
		m_inputLed[i].Positionne_etat(((CEquipCV24Card *) equip)->getInputMaskValue(i));
	}
	// Set the outputs values.
	for(i=0; i<8 ; i++) {
		m_outputStatus[i].Positionne_etat(((CEquipCV24Card *) equip)->getOutputValue(i));
	}
}

// Comm erreur ********************************************
void CDLGCV24Card::OnComErreur()
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

void CDLGCV24Card::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_CV24,"Carte CV24");
	if(iResult >=  0) win.DoModal();
}

// OnTimer : Rafraichissement de l'écran de controle **************************
// ****************************************************************************
void CDLGCV24Card::OnTimer(UINT nIDEvent)
{
	//int			val;			//2009-1127
	//char		buf[10];			//2009-11-27

	UpdateData(TRUE);

	CDialog::OnTimer(nIDEvent);
	CDlgEquip::OnTimer();			// Rafraichissement des controles commun

	UpdateData(FALSE);
}

void CDLGCV24Card::OnEnvoiTrame()
{

	int		i, j, decalage;			//int		i,j,code_ascii, decalage;			//2009-11-27
	char 	buffer[TAILLE_PIPE_MESSAGE+1];
	char	commande[TAILLE_PIPE_MESSAGE+1];
	char	*pcResult;
	char    toto[2];

	CEdit	*m_trame	 = (CEdit*)GetDlgItem(IDC_TRAME);

	m_trame->GetLine(0,buffer,TAILLE_PIPE_MESSAGE);

	if(strlen(buffer)==0) return;	// Chaine vide

	// Controler la valeur.
	for(i=0; i< strlen(buffer); i++) {
		if ( buffer[i] != '0' && buffer[i] != '1' ) {
			return; // Chaine non binaire.
		}
	}

	// Transformation de la chaine binaire en un ASCII
	pcResult = buffer;
	strcpy(commande,"");
	i=0;
	j=-1;
	decalage = 7;
	toto[1] = '\0';
	while(i < strlen(buffer))
	{
		if (decalage==7) {
			j++;
		}
		toto[0] = buffer[i];
		commande[j] += atoi(toto) << decalage;
		i++;
		if (decalage==0) {
			decalage = 7;
		} else {
			decalage--;
		}
	}
	commande[j+1]='\0';

	equip->proto->TraiteTC(commande);
}

// Externals actions.

/**
 * Set the 'index' input value.
 */
void CDLGCV24Card::onInputValueChange(int index) {
	m_inputStatus[index].Positionne_etat(((CEquipCV24Card *) equip)->getInputValue(index));
}

/**
 * Set the 'index' output value.
 */
void CDLGCV24Card::onOutputValueChange(int index) {
	m_outputStatus[index].Positionne_etat(((CEquipCV24Card *) equip)->getOutputValue(index));
}

/**
 * Set the 'index' input mask value.
 */
void CDLGCV24Card::onInputMaskValueChange(int index) {
	m_inputLed[index].Positionne_etat(((CEquipCV24Card *) equip)->getInputMaskValue(index));
}

/**
 * Set the status.
 */
void CDLGCV24Card::onStatusChange() {
	m_status.Positionne_etat(((CEquipCV24Card *) equip)->getStatus());
}

void CDLGCV24Card::onKeyChange(int key) {
	if ( key < 0 || key > 7 ) {
		return;
	}
	char value[2] = "\0";
	sprintf(value,"%d",key);
	m_keyNumber.SetWindowText(value);
}

// Callbacks.

void CDLGCV24Card::OnInput0Clicked()
{
	((CEquipCV24Card *)equip)->setInput(0,!m_inputStatus[0].Retourne_etat());
}

void CDLGCV24Card::OnInput1Clicked()
{
	((CEquipCV24Card *)equip)->setInput(1,!m_inputStatus[1].Retourne_etat());
}

void CDLGCV24Card::OnInput2Clicked()
{
	((CEquipCV24Card *)equip)->setInput(2,!m_inputStatus[2].Retourne_etat());
}

