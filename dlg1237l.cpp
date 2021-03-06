/* **************************************************************************
FICHIER :	Dlg1237.CPP		 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Impl�mentation de la classe CDlg1237L
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "Dlg1237L.h"
#include "Equip\Eqp1237L.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_E_1237[];

CDlg1237L::CDlg1237L(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDlg1237L::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg1237L)
	m_frequence = _T("");
	m_err_retard = _T("");
	m_canal = _T("");
	m_code_incident = _T("");
	m_test = _T("");
	m_niveau = _T("");
	m_periode = _T("");
	m_tempo = _T("");
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDI_EM_HF);
}


void CDlg1237L::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg1237L)
	DDX_Control(pDX, F3_CHOIX_NIVEAU, m_choix_niveau);
	DDX_Control(pDX, F3_MODE_FONCT, m_fonctionnement);
	DDX_Control(pDX, F3_MODE_TRAFIC, m_trafic);
	DDX_Control(pDX, IDC_MES_STATUT, m_liste_message);
	DDX_Control(pDX, IDC_CHECK_SYNCHRO, m_synchro);
	DDX_Control(pDX, IDC_CHECK_CYCLE, m_cycle);
	DDX_Text(pDX, F3_FREQUENCE, m_frequence);
	DDX_Text(pDX, IDC_RETARD, m_err_retard);
	DDX_Text(pDX, F3_CANAL, m_canal);
	DDX_Text(pDX, F3_CODE_INCIDENT, m_code_incident);
	DDX_Text(pDX, F3_CODE_TEST, m_test);
	DDX_Text(pDX, F3_NIVEAU, m_niveau);
	DDX_Text(pDX, IDC_EDIT_CYCLE, m_periode);
	DDX_Text(pDX, IDC_EDIT_TEMPO, m_tempo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg1237L, CDialog)
	//{{AFX_MSG_MAP(CDlg1237L)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(F3_MODE_TRAFIC, OnSelchangeModeTrafic)
	ON_BN_CLICKED(F3_MODE_DBL, OnModeDbl)
	ON_BN_CLICKED(F3_MODE_LOC, OnModeLoc)
	ON_BN_CLICKED(F3_MODE_RMT, OnModeRmt)
	ON_BN_CLICKED(IDC_PARITE, OnComErreur)
	ON_BN_CLICKED(F3_COMPRESSEUR, OnCompresseur)
	ON_CBN_SELCHANGE(F3_MODE_FONCT, OnSelchangeModeFonct)
	ON_EN_KILLFOCUS(F3_CODE_INCIDENT, OnKillfocusCodeIncident)
	ON_EN_KILLFOCUS(F3_FREQUENCE, OnKillfocusFrequence)
	ON_BN_CLICKED(F3_AUTO, OnAuto)
	ON_EN_KILLFOCUS(F3_NIVEAU, OnKillfocusNiveau)
	ON_CBN_SELCHANGE(F3_CHOIX_NIVEAU, OnSelchangeChoixNiveau)
	ON_EN_KILLFOCUS(F3_CANAL, OnKillfocusCanal)
	ON_BN_CLICKED(F3_MEMO_CANAL, OnMemoCanal)
	ON_EN_KILLFOCUS(F3_CODE_TEST, OnKillfocusCodeTest)
	ON_BN_CLICKED(F3_INFO, OnInfo)
	ON_BN_CLICKED(F8_COUPLAGE_ESCLAVE, OnCouplageEsclave)
	ON_BN_CLICKED(F8_COUPLAGE_MAITRE, OnCouplageMaitre)
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


/////////////////////////////////////////////////////////////////////////////
// CDlg1237L message handlers

void CDlg1237L::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_E_1237,"Emetteur HF");
	if(iResult >=  0) win.DoModal();
}

BOOL CDlg1237L::OnInitDialog() 
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
	m_liste_message.AddString("Mode de trafic");
	m_liste_message.AddString("Compresseur");
	m_liste_message.AddString("Mode Fonct.");
	m_liste_message.AddString("Frequence");
	m_liste_message.AddString("Niveaux analog.");
	m_liste_message.AddString("Position canal");
	m_liste_message.AddString("Lecture de canal");
	m_liste_message.AddString("Option emetteur");
	m_liste_message.AddString("Test interne");
	m_liste_message.AddString("Etat logique");
	m_liste_message.AddString("Mode local");
	m_liste_message.AddString("Data out");
	m_liste_message.AddString("incident");
	m_liste_message.AddString("Pr�sence info");

// Custom control
// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);	
	m_incident.SubclassDlgItem(F3_INCIDENT,this);
	m_info.SubclassDlgItem(F3_INFO,this);

	
// Initialisation de la face avant
// *******************************
	m_trafic.AddString("A1");
	m_trafic.AddString("A3");
	m_trafic.AddString("BLU sup");
	m_trafic.AddString("BLU inf");
	m_trafic.AddString("BLI");
	m_trafic.AddString("TG");

	m_fonctionnement.AddString("Veille");
	m_fonctionnement.AddString("PR");
	m_fonctionnement.AddString("PN");
	m_fonctionnement.AddString("PN (-3 dB)");
	m_fonctionnement.AddString("PN (-6 dB)");
	m_fonctionnement.AddString("PN (-9 dB)");
	m_fonctionnement.AddString("PN (-12 dB)");
	m_fonctionnement.AddString("PN (-15 dB)");
	m_fonctionnement.AddString("PN (-18 dB)");
	m_fonctionnement.AddString("PN (-21 dB)");

	m_choix_niveau.AddString("Aucune demande");
	m_choix_niveau.AddString("niveau FI 1");
	m_choix_niveau.AddString("taux de Compression");
	m_choix_niveau.AddString("RF Exciteur");
	m_choix_niveau.AddString("Valeur du ROS");
	m_choix_niveau.AddString("Niveau HF �metteur");
	m_choix_niveau.AddString("Voie A");
	m_choix_niveau.AddString("Voie B");

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// GenrateurAuto():	Effectue les variation automatique de certains param�tres
void CDlg1237L::GenerateurAuto()
{
	srand( (unsigned)time( NULL ) );

	if(((CEquip1237L*)equip)->AutoNiveau())
		((CEquip1237L*)equip)->ChangeNiveau(rand()%0xFF,FALSE);
}
// OnTimer : Rafraichissement de l'�cran de controle **************************
// ****************************************************************************
void CDlg1237L::OnTimer(UINT nIDEvent) 
{
	int			val;
	char		buf[10];

	UpdateData(TRUE);

	CDialog::OnTimer(nIDEvent);
	CDlgEquip::OnTimer();			// Rafraichissement des controles commun

// Test de changement dans la face avant
	val = equip->Evolution();
	if (val==evolution) return;		// Rafraichissement inutile
	evolution = val;

// Verrouille((((CEquip1237L*)equip)->Local())!=1);

// Couplage
	SendDlgItemMessage(F8_COUPLAGE_MAITRE,BM_SETCHECK,0,0);
	SendDlgItemMessage(F8_COUPLAGE_ESCLAVE,BM_SETCHECK,0,0);
	val = ((CEquip1237*)equip)->Couplage();
	switch(val)
	{
		case 0:
			SendDlgItemMessage(F8_COUPLAGE_MAITRE,BM_SETCHECK,1,0);
			break;
		case 1:
			SendDlgItemMessage(F8_COUPLAGE_ESCLAVE,BM_SETCHECK,1,0);
			break;
	}

// Mode Local
	SendDlgItemMessage(F3_MODE_LOC,BM_SETCHECK,0,0);
	SendDlgItemMessage(F3_MODE_RMT,BM_SETCHECK,0,0);
	SendDlgItemMessage(F3_MODE_DBL,BM_SETCHECK,0,0);
	val = ((CEquip1237L*)equip)->Local();
	switch(val)
	{
		case 1:
			SendDlgItemMessage(F3_MODE_RMT,BM_SETCHECK,1,0);
			break;
		case 2:
			SendDlgItemMessage(F3_MODE_DBL,BM_SETCHECK,1,0);
			break;
		default:
			SendDlgItemMessage(F3_MODE_LOC,BM_SETCHECK,1,0);
			break;
	}

// Mode Trafic
	val = ((CEquip1237L*)equip)->ModeTrafic(0);
	m_trafic.SetCurSel(val);

// Compresseur
	val = ((CEquip1237L*)equip)->Compresseur();
	SendDlgItemMessage(F3_COMPRESSEUR,BM_SETCHECK,val,0);

// Mode de fonctionnement
	val = ((CEquip1237L*)equip)->Fonction(0);
	m_fonctionnement.SetCurSel(val);

// Incident
	val = ((CEquip1237L*)equip)->Incident();
	if(m_incident.Retourne_etat() != (val!=0))
		m_incident.Positionne_etat(val!=0);

	if(GetDlgItem(F3_CODE_INCIDENT) != GetFocus())
	{
		sprintf(buf,"%d",val);
		m_code_incident = buf;
	}

// Frequence
	if(GetDlgItem(F3_FREQUENCE) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1237L*)equip)->Frequence(0));
		m_frequence = buf;
	}

// Niveau analogique
	val = ((CEquip1237L*)equip)->AutoNiveau();
	SendDlgItemMessage(F3_AUTO,BM_SETCHECK,val,0);

	if(GetDlgItem(F3_NIVEAU) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1237L*)equip)->Niveau());
		m_niveau = buf;
	}

	val = ((CEquip1237L*)equip)->ChoixNiveau();
	m_choix_niveau.SetCurSel(val);

// Canal
	if(GetDlgItem(F3_CANAL) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1237L*)equip)->Canal());
		m_canal = buf;
	}

// Test
	if(GetDlgItem(F3_CODE_TEST) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1237L*)equip)->Test());
		m_test = buf;
	}

// Presence Info
		m_info.Positionne_etat(((CEquip1237L*)equip)->Info());

// Mise � jour de CEdit
// ********************
	UpdateData(FALSE);

}

// Comm erreur ********************************************
void CDlg1237L::OnComErreur() 
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

// Action par la face avant *****************************************************
// ******************************************************************************
void CDlg1237L::Verrouille(BOOL etat)
{

// Mode trafic
	m_trafic.EnableWindow(etat);

// Compresseur
	GetDlgItem(F3_COMPRESSEUR)->EnableWindow(etat);

// Mode de fonctionnement
	GetDlgItem(F3_MODE_FONCT)->EnableWindow(etat);

// Code incident
	GetDlgItem(F3_CODE_INCIDENT)->EnableWindow(etat);

// Frequence
	GetDlgItem(F3_FREQUENCE)->EnableWindow(etat);

// Niveau analogique
	GetDlgItem(F3_NIVEAU)->EnableWindow(etat);
	GetDlgItem(F3_AUTO)->EnableWindow(etat);

// Niveau analogique
	GetDlgItem(F3_CANAL)->EnableWindow(etat);
	GetDlgItem(F3_MEMO_CANAL)->EnableWindow(etat);

// Code Test
	GetDlgItem(F3_CODE_TEST)->EnableWindow(etat);

}

void CDlg1237L::OnSelchangeModeTrafic() 
{
	int	iResult = ((CEquip1237L*)equip)->ChangeModeTrafic(0,m_trafic.GetCurSel(),((CEquip1237L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnModeDbl() 
{
	int	iResult = ((CEquip1237L*)equip)->ChangeLocal(2,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnModeLoc() 
{
	int	iResult = ((CEquip1237L*)equip)->ChangeLocal(0,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnModeRmt() 
{
	int	iResult = ((CEquip1237L*)equip)->ChangeLocal(1,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}


void CDlg1237L::OnCompresseur() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F3_COMPRESSEUR))->GetCheck();
	iResult = ((CEquip1237L*)equip)->ChangeCompresseur(val,((CEquip1237L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnSelchangeModeFonct() 
{
	int	iResult = ((CEquip1237L*)equip)->ChangeFonction(0,m_fonctionnement.GetCurSel(),((CEquip1237L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnKillfocusCodeIncident() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip1237L*)equip)->ChangeIncident(atoi(m_code_incident),((CEquip1237L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnKillfocusFrequence() 
{
	long	lResult;

	UpdateData(TRUE);
	lResult = ((CEquip1237L*)equip)->ChangeFrequence(0,atoi(m_frequence),((CEquip1237L*)equip)->Local() != 0);
	if(lResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnAuto() 
{
	int		iResult;

	/* Correction du 30/01/2008 */
	if(m_choix_niveau.GetCurSel() != 0)
	{
		int		val=((CButton*)GetDlgItem(F3_AUTO))->GetCheck();
		iResult = ((CEquip1237L*)equip)->ChangeAutoNiveau(val);
		if(iResult<0);	// L'ancienne valeur sera rafraichie
	}
	else
	{
		SendDlgItemMessage(F3_AUTO,BST_UNCHECKED,0,0);
		((CEquip1237L*)equip)->ChangeAutoNiveau(0);
	}
}

void CDlg1237L::OnKillfocusNiveau() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip1237L*)equip)->ChangeNiveau(atoi(m_niveau),((CEquip1237L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnSelchangeChoixNiveau() 
{
	int	iResult = ((CEquip1237L*)equip)->ChangeChoixNiveau(m_choix_niveau.GetCurSel(),((CEquip1237L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
	/* Correction du 30/01/2008 */
	if(iResult == 0)
	{
		SendDlgItemMessage(F3_AUTO,BST_UNCHECKED,0,0);
		((CEquip1237L*)equip)->ChangeAutoNiveau(0);
	}
}

void CDlg1237L::OnKillfocusCanal() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip1237L*)equip)->ChangeCanal(atoi(m_canal),((CEquip1237L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnMemoCanal() 
{
	int		iResult;

	int		num_canal = ((CEquip1237L*)equip)->Canal();

	iResult = ((CEquip1237L*)equip)->MemoriseCanal(num_canal,((CEquip1237L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnKillfocusCodeTest() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip1237L*)equip)->ChangeTest(atoi(m_test),((CEquip1237L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnInfo() 
{
	int	iResult = m_info.Inverse_etat();
 	((CEquip1237*)equip)->ChangeInfo(iResult,TRUE);
}


void CDlg1237L::OnCouplageEsclave() 
{
	int	iResult = ((CEquip1237*)equip)->ChangeCouplage(1,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1237L::OnCouplageMaitre() 
{
	int	iResult = ((CEquip1237*)equip)->ChangeCouplage(0,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}
