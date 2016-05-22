/* **************************************************************************
FICHIER :	Dlg1241.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlg1241L
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "Dlg1241L.h"
#include "Equip\Eqp1241L.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_R_1241[];

CDlg1241L::CDlg1241L(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDlg1241L::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg1241L)
	m_err_retard = _T("");
	m_bfo = _T("");
	m_canal = _T("");
	m_centrage = _T("");
	m_code_test = _T("");
	m_cor_squelch = _T("");
	m_freq_rejecteur = _T("");
	m_frequence = _T("");
	m_gain_hf = _T("");
	m_mesureur = _T("");
	m_periode = _T("");
	m_tempo = _T("");
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDI_REC_HF);
}


void CDlg1241L::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg1241L)
	DDX_Control(pDX, F4_SHIFT, m_shift);
	DDX_Control(pDX, IDC_PARITE, m_parite);
	DDX_Control(pDX, F4_INV_TG, m_sens_manip);
	DDX_Control(pDX, F4_CAG, m_cag);
	DDX_Control(pDX, IDC_MES_STATUT, m_liste_message);
	DDX_Control(pDX, IDC_CHECK_SYNCHRO, m_synchro);
	DDX_Control(pDX, IDC_CHECK_CYCLE, m_cycle);
	DDX_Control(pDX, IDC_MODE_RECEPTION, m_mode_reception);
	DDX_Text(pDX, IDC_RETARD, m_err_retard);
	DDX_Text(pDX, F4_BFO, m_bfo);
	DDX_Text(pDX, F4_CANAL, m_canal);
	DDX_Text(pDX, F4_CENTRAGE, m_centrage);
	DDX_Text(pDX, F4_CODE_TEST, m_code_test);
	DDX_Text(pDX, F4_COR_SQUELCH, m_cor_squelch);
	DDX_Text(pDX, F4_FREQ_REJECT, m_freq_rejecteur);
	DDX_Text(pDX, F4_FREQUENCE, m_frequence);
	DDX_Text(pDX, F4_GAIN_HF, m_gain_hf);
	DDX_Text(pDX, F4_MESUREUR, m_mesureur);
	DDX_Text(pDX, IDC_EDIT_CYCLE, m_periode);
	DDX_Text(pDX, IDC_EDIT_TEMPO, m_tempo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg1241L, CDialog)
	//{{AFX_MSG_MAP(CDlg1241L)
	ON_CBN_SELCHANGE(IDC_MODE_RECEPTION, OnSelchangeModeReception)
	ON_BN_CLICKED(F4_IDC_ATTENUATEUR_0, OnIdcAttenuateur0)
	ON_BN_CLICKED(F4_IDC_ATTENUATEUR_1, OnIdcAttenuateur1)
	ON_BN_CLICKED(F4_IDC_ATTENUATEUR_2, OnIdcAttenuateur2)
	ON_WM_TIMER()
	ON_BN_CLICKED(F4_BP1, OnBp1)
	ON_BN_CLICKED(F4_BP2, OnBp2)
	ON_BN_CLICKED(F4_BP3, OnBp3)
	ON_BN_CLICKED(F4_BP4, OnBp4)
	ON_BN_CLICKED(F4_BP5, OnBp5)
	ON_CBN_SELCHANGE(F4_CAG, OnSelchangeCag)
	ON_BN_CLICKED(F4_SQUELCH, OnSquelch)
	ON_CBN_SELCHANGE(F4_INV_TG, OnSelchangeInvTg)
	ON_BN_CLICKED(IDC_PARITE, OnComErreur)
	ON_CBN_SELCHANGE(F4_SHIFT, OnSelchangeShift)
	ON_EN_KILLFOCUS(F4_FREQUENCE, OnKillfocusFrequence)
	ON_EN_KILLFOCUS(F4_BFO, OnKillfocusBfo)
	ON_BN_CLICKED(F4_REJECTEUR, OnRejecteur)
	ON_EN_KILLFOCUS(F4_FREQ_REJECT, OnKillfocusFreqReject)
	ON_EN_KILLFOCUS(F4_GAIN_HF, OnKillfocusGainHf)
	ON_BN_CLICKED(F4_AUTO_MESUREUR, OnAutoMesureur)
	ON_EN_KILLFOCUS(F4_MESUREUR, OnKillfocusMesureur)
	ON_EN_KILLFOCUS(F4_COR_SQUELCH, OnKillfocusCorSquelch)
	ON_BN_CLICKED(F4_AUTO_CENTRAGE, OnAutoCentrage)
	ON_EN_KILLFOCUS(F4_CENTRAGE, OnKillfocusCentrage)
	ON_EN_KILLFOCUS(F4_CANAL, OnKillfocusCanal)
	ON_BN_CLICKED(F4_MEMO_CANAL, OnMemoCanal)
	ON_EN_KILLFOCUS(F4_CODE_TEST, OnKillfocusCodeTest)
	ON_BN_CLICKED(F4_MODE_LOC, OnModeLoc)
	ON_BN_CLICKED(F4_MODE_RMT, OnModeRmt)
	ON_BN_CLICKED(IDC_CDE_INCONUE, OnComErreur)
	ON_BN_CLICKED(IDC_DEBUT_TRAME, OnComErreur)
	ON_BN_CLICKED(IDC_FIN_TRAME, OnComErreur)
	ON_BN_CLICKED(IDC_PAS_REPONSE, OnComErreur)
	ON_EN_KILLFOCUS(IDC_RETARD, OnComErreur)
	//}}AFX_MSG_MAP

	ON_WM_CLOSE()
	ON_WM_PAINT()

// Activation des tache de comm
	ON_COMMAND(IDC_ACTIVITE, OnActivite)

// Aide
	ON_COMMAND(ID__AIDE, OnAide)

// Masquage de l'ecran de controle
	ON_COMMAND(ID_AFF_CONTROLE, OnClose)

// Contexte d'exploitation
	ON_COMMAND(ID_CONTEXTE_OUVRIR, OnOuvrir)
	ON_COMMAND(ID_CONTEXTE_SAUVER, OnSauver)

// Envoi de trame
	ON_BN_CLICKED(IDC_ENVOI_TRAME, OnEnvoiTrame)

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


void CDlg1241L::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_R_1241,"Récepteur HF");
	if(iResult >=  0) win.DoModal();
}

BOOL CDlg1241L::OnInitDialog() 
{
	t_ComErreur	err;
	char	buf[10];

	CDialog::OnInitDialog();
	
//	Armement du timer
	SetTimer(1,1000,NULL);	

// Gestion des erreurs de communication
// ************************************
	equip->RetourneComErreur(&err);

	sprintf(buf,"%d",err.retard);
	m_err_retard = buf;

	m_parite.SetCheck(err.controle_parite);

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
	m_liste_message.AddString("Mode réception");
	m_liste_message.AddString("Atténuateur HF");
	m_liste_message.AddString("Filtre FI");
	m_liste_message.AddString("CAG");
	m_liste_message.AddString("Squelch");				// cde 5
	m_liste_message.AddString("Sens manip. ...");
	m_liste_message.AddString("Shift");
	m_liste_message.AddString("Frequence accord");
	m_liste_message.AddString("Frequence BFO");
	m_liste_message.AddString("Freq. réject. FI");  // cde 10
	m_liste_message.AddString("Niveau Gain HF");
	m_liste_message.AddString("Mesureur champs");
	m_liste_message.AddString("Seuil COR/Squelch");	// cde 15
	m_liste_message.AddString("Centrage démod. F1");
	m_liste_message.AddString("Position canal");
	m_liste_message.AddString("Coordonnée canal");
	m_liste_message.AddString("Pos. Canal veille");
	m_liste_message.AddString("Coord. Canal veille");// cde 20
	m_liste_message.AddString("Temps de maintien");
	m_liste_message.AddString("Pos. freq. balayage");
	m_liste_message.AddString("Lect. freq. balayage");
	m_liste_message.AddString("Vitesse balayage");
	m_liste_message.AddString("Option récepteur");	// cde 25
	m_liste_message.AddString("Résultat du test");
	m_liste_message.AddString("Présence info");
	m_liste_message.AddString("Balayage");
	m_liste_message.AddString("Etat logique");
	m_liste_message.AddString("Passage en local");	  // cde 30


// Custom control
// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);	
	m_info.SubclassDlgItem(F4_INFO,this);
	
// Initialisation de la face avant
// *******************************
	m_mode_reception.AddString("A1");
	m_mode_reception.AddString("A3E");
	m_mode_reception.AddString("BLU sup");
	m_mode_reception.AddString("BLU inf");
	m_mode_reception.AddString("BLI");
	m_mode_reception.AddString("TG");

	m_cag.AddString("sans CAG");
	m_cag.AddString("Courte");
	m_cag.AddString("Moyenne");
	m_cag.AddString("Longue");
	m_cag.AddString("L11");

	m_sens_manip.AddString("Sens direct, V24 actif");
	m_sens_manip.AddString("Sens direct, V24 bloqué");
	m_sens_manip.AddString("Sens inverse, V24 actif");
	m_sens_manip.AddString("Sens inverse, V24 bloqué");

	m_shift.AddString("425 Hz");
	m_shift.AddString("200 Hz");
	m_shift.AddString("85 Hz");
	m_shift.AddString("42,5 Hz");
	m_shift.AddString("25 Hz");

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// GenrateurAuto():	Effectue les variation automatique de certains paramètres
void CDlg1241L::GenerateurAuto()
{
	srand( (unsigned)time( NULL ) );

	if(((CEquip1241L*)equip)->AutoMesureur())
		((CEquip1241L*)equip)->ChangeMesureur(0,rand()%109,FALSE);

	if(((CEquip1241L*)equip)->AutoCentrageF1())
		((CEquip1241L*)equip)->ChangeCentrageF1(rand()%077,FALSE);
}

// OnTimer : Rafraichissement de l'écran de controle **************************
// ****************************************************************************
void CDlg1241L::OnTimer(UINT nIDEvent) 
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

	// Verrouille(!((CEquip1241L*)equip)->Local());

// Mode Local
	SendDlgItemMessage(F4_MODE_LOC,BM_SETCHECK,0,0);
	SendDlgItemMessage(F4_MODE_RMT,BM_SETCHECK,0,0);
	val = ((CEquip1241L*)equip)->Local();
	if(val)
		SendDlgItemMessage(F4_MODE_RMT,BM_SETCHECK,1,0);
	else
		SendDlgItemMessage(F4_MODE_LOC,BM_SETCHECK,1,0);

// Mode reception
	val = ((CEquip1241L*)equip)->ModeRecep(0);
	m_mode_reception.SetCurSel(val);

// Attenuateur HF
	SendDlgItemMessage(F4_IDC_ATTENUATEUR_0,BM_SETCHECK,0,0);
	SendDlgItemMessage(F4_IDC_ATTENUATEUR_1,BM_SETCHECK,0,0);
	SendDlgItemMessage(F4_IDC_ATTENUATEUR_2,BM_SETCHECK,0,0);
	val = ((CEquip1241L*)equip)->Attenuateur(0);
	switch(val)
	{
		case 0:
			SendDlgItemMessage(F4_IDC_ATTENUATEUR_0,BM_SETCHECK,1,0);
			break;
		case 1:
			SendDlgItemMessage(F4_IDC_ATTENUATEUR_1,BM_SETCHECK,1,0);
			break;
		default:			// 2
			SendDlgItemMessage(F4_IDC_ATTENUATEUR_2,BM_SETCHECK,1,0);
			break;
	}

// Filtre FI
	val = ((CEquip1241L*)equip)->FiltreFI(0);
	if(val>4)
		SendDlgItemMessage(F4_BP5,BM_SETCHECK,1,0);
	else
		SendDlgItemMessage(F4_BP5,BM_SETCHECK,0,0);

	SendDlgItemMessage(F4_BP1,BM_SETCHECK,0,0);
	SendDlgItemMessage(F4_BP2,BM_SETCHECK,0,0);
	SendDlgItemMessage(F4_BP3,BM_SETCHECK,0,0);
	SendDlgItemMessage(F4_BP4,BM_SETCHECK,((CEquip1241L*)equip)->L11(),0);
	switch(val % 5)
	{
		case 1:
			SendDlgItemMessage(F4_BP1,BM_SETCHECK,1,0);
			break;
		case 2:
			SendDlgItemMessage(F4_BP2,BM_SETCHECK,1,0);
			break;
		case 3:
			SendDlgItemMessage(F4_BP3,BM_SETCHECK,1,0);
			break;
		case 4:
			SendDlgItemMessage(F4_BP4,BM_SETCHECK,1,0);
			break;
	}

// CAG
	val = ((CEquip1241L*)equip)->Cag(0);
	m_cag.SetCurSel(val);
	if(val==4)
		SendDlgItemMessage(F4_BP4,BM_SETCHECK,1,0);

// Squelch
	val = ((CEquip1241L*)equip)->Squelch(0);
	SendDlgItemMessage(F4_SQUELCH,BM_SETCHECK,val,0);

// Sens de manipulation télégraphique
	val = ((CEquip1241L*)equip)->SensManip(0);
	m_sens_manip.SetCurSel(val);

// Shift
	val = ((CEquip1241L*)equip)->Shift(0);
	m_shift.SetCurSel(val);

// Frequence
	if(GetDlgItem(F4_FREQUENCE) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1241L*)equip)->Frequence(0));
		m_frequence = buf;
	}

// Frequence BFO
	if(GetDlgItem(F4_BFO) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1241L*)equip)->Bfo(0));
		m_bfo = buf;
	}

// Avec Rejecteur
	val = ((CEquip1241L*)equip)->AvecRejecteur();
	SendDlgItemMessage(F4_REJECTEUR,BM_SETCHECK,val,0);
	((CEdit*)GetDlgItem(F4_FREQ_REJECT))->EnableWindow(val);

// Frequence Rejecteur
	if(GetDlgItem(F4_FREQ_REJECT) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1241L*)equip)->Rejecteur());
		m_freq_rejecteur = buf;
	}

// Gain HF
	if(GetDlgItem(F4_GAIN_HF) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1241L*)equip)->GainHF(0));
		m_gain_hf = buf;
	}

// Mesureur de champs
	if(GetDlgItem(F4_MESUREUR) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1241L*)equip)->Mesureur(0));
		m_mesureur = buf;
	}

	val = ((CEquip1241L*)equip)->AutoMesureur();
	SendDlgItemMessage(F4_AUTO_MESUREUR,BM_SETCHECK,val,0);

// Seuil Cor/Squelch
	if(GetDlgItem(F4_COR_SQUELCH) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1241L*)equip)->CorSquelch());
		m_cor_squelch = buf;
	}

// Centrage Démodulateur F1
	if(GetDlgItem(F4_CENTRAGE) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1241L*)equip)->CentrageF1());
		m_centrage = buf;
	}

	val = ((CEquip1241L*)equip)->AutoCentrageF1();
	SendDlgItemMessage(F4_AUTO_CENTRAGE,BM_SETCHECK,val,0);

// Canal
	if(GetDlgItem(F4_CANAL) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1241L*)equip)->Canal());
		m_canal = buf;
	}

// Code Test
	if(GetDlgItem(F4_CODE_TEST) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip1241L*)equip)->Test());
		m_code_test = buf;
	}

// Presence Infos
	val = ((CEquip1241L*)equip)->Info();
	if(m_info.Retourne_etat() != val)
		m_info.Positionne_etat(val);

// Mise à jour de CEdit
// ********************
	UpdateData(FALSE);
}

// Comm erreur ********************************************
void CDlg1241L::OnComErreur() 
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

void CDlg1241L::OnSelchangeModeReception() 
{
	int	iResult = ((CEquip1241L*)equip)->ChangeModeRecep(0,m_mode_reception.GetCurSel(),((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnIdcAttenuateur0() 
{
	int	iResult = ((CEquip1241L*)equip)->ChangeAttenuateur(0,0,((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnIdcAttenuateur1() 
{
	int	iResult = ((CEquip1241L*)equip)->ChangeAttenuateur(0,1,((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnIdcAttenuateur2() 
{
	int	iResult = ((CEquip1241L*)equip)->ChangeAttenuateur(0,2,((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}


void CDlg1241L::OnBp1() 
{
	int		val;

	if(((CButton*)GetDlgItem(F4_BP1))->GetCheck())
	{
		SendDlgItemMessage(F4_BP2,BM_SETCHECK,0,0);
		SendDlgItemMessage(F4_BP3,BM_SETCHECK,0,0);
		SendDlgItemMessage(F4_BP4,BM_SETCHECK,0,0);
	}

	val = (((CButton*)GetDlgItem(F4_BP1))->GetCheck())*1
				+ (((CButton*)GetDlgItem(F4_BP2))->GetCheck())*2
				+ (((CButton*)GetDlgItem(F4_BP3))->GetCheck())*3
				+ (((CButton*)GetDlgItem(F4_BP4))->GetCheck())*4
				+ (((CButton*)GetDlgItem(F4_BP5))->GetCheck())*5;

	int	iResult = ((CEquip1241L*)equip)->ChangeFiltreFI(0,val,((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnBp2() 
{
	int		val;

	if(((CButton*)GetDlgItem(F4_BP2))->GetCheck())
	{
		SendDlgItemMessage(F4_BP1,BM_SETCHECK,0,0);
		SendDlgItemMessage(F4_BP3,BM_SETCHECK,0,0);
		SendDlgItemMessage(F4_BP4,BM_SETCHECK,0,0);
	}

	val = (((CButton*)GetDlgItem(F4_BP1))->GetCheck())*1
				+ (((CButton*)GetDlgItem(F4_BP2))->GetCheck())*2
				+ (((CButton*)GetDlgItem(F4_BP3))->GetCheck())*3
				+ (((CButton*)GetDlgItem(F4_BP4))->GetCheck())*4
				+ (((CButton*)GetDlgItem(F4_BP5))->GetCheck())*5;

	int	iResult = ((CEquip1241L*)equip)->ChangeFiltreFI(0,val,((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnBp3() 
{
	int		val;

	if(((CButton*)GetDlgItem(F4_BP3))->GetCheck())
	{
		SendDlgItemMessage(F4_BP1,BM_SETCHECK,0,0);
		SendDlgItemMessage(F4_BP2,BM_SETCHECK,0,0);
		SendDlgItemMessage(F4_BP4,BM_SETCHECK,0,0);
	}

	val = (((CButton*)GetDlgItem(F4_BP1))->GetCheck())*1
				+ (((CButton*)GetDlgItem(F4_BP2))->GetCheck())*2
				+ (((CButton*)GetDlgItem(F4_BP3))->GetCheck())*3
				+ (((CButton*)GetDlgItem(F4_BP4))->GetCheck())*4
				+ (((CButton*)GetDlgItem(F4_BP5))->GetCheck())*5;

	int	iResult = ((CEquip1241L*)equip)->ChangeFiltreFI(0,val,((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnBp4() 
{
	int		val;

	if(((CButton*)GetDlgItem(F4_BP4))->GetCheck())
	{
		SendDlgItemMessage(F4_BP1,BM_SETCHECK,0,0);
		SendDlgItemMessage(F4_BP2,BM_SETCHECK,0,0);
		SendDlgItemMessage(F4_BP3,BM_SETCHECK,0,0);
	}

	val = (((CButton*)GetDlgItem(F4_BP1))->GetCheck())*1
				+ (((CButton*)GetDlgItem(F4_BP2))->GetCheck())*2
				+ (((CButton*)GetDlgItem(F4_BP3))->GetCheck())*3
				+ (((CButton*)GetDlgItem(F4_BP4))->GetCheck())*4
				+ (((CButton*)GetDlgItem(F4_BP5))->GetCheck())*5;

	int	iResult = ((CEquip1241L*)equip)->ChangeFiltreFI(0,val,((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnBp5() 
{
	int val = (((CButton*)GetDlgItem(F4_BP1))->GetCheck())*1
				+ (((CButton*)GetDlgItem(F4_BP2))->GetCheck())*2
				+ (((CButton*)GetDlgItem(F4_BP3))->GetCheck())*3
				+ (((CButton*)GetDlgItem(F4_BP4))->GetCheck())*4
				+ (((CButton*)GetDlgItem(F4_BP5))->GetCheck())*5;

	int	iResult = ((CEquip1241L*)equip)->ChangeFiltreFI(0,val,((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnSelchangeCag() 
{
	int	iResult = ((CEquip1241L*)equip)->ChangeCag(0,m_cag.GetCurSel(),((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnSquelch() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F4_SQUELCH))->GetCheck();
	iResult = ((CEquip1241L*)equip)->ChangeSquelch(0,val,((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnSelchangeInvTg() 
{
	
	int	iResult = ((CEquip1241L*)equip)->ChangeSensManip(0,m_sens_manip.GetCurSel(),((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}


void CDlg1241L::OnSelchangeShift() 
{
	int	iResult = ((CEquip1241L*)equip)->ChangeShift(0,m_shift.GetCurSel(),((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnKillfocusFrequence() 
{
	long	lResult;

	UpdateData(TRUE);
	lResult = ((CEquip1241L*)equip)->ChangeFrequence(0,atoi(m_frequence),((CEquip1241L*)equip)->Local() != 0);
	if(lResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnKillfocusBfo() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip1241L*)equip)->ChangeBfo(0,atoi(m_bfo),((CEquip1241L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnRejecteur() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F4_REJECTEUR))->GetCheck();
	iResult = ((CEquip1241L*)equip)->ChangeAvecRejecteur(val,((CEquip1241L*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnKillfocusFreqReject() 
{
	int		iResult;
	UpdateData(TRUE);
	iResult = ((CEquip1241L*)equip)->ChangeRejecteur(atoi(m_freq_rejecteur),((CEquip1241L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnKillfocusGainHf() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip1241L*)equip)->ChangeGainHF(0,atoi(m_gain_hf),((CEquip1241L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnAutoMesureur() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F4_AUTO_MESUREUR))->GetCheck();
	iResult = ((CEquip1241L*)equip)->ChangeAutoMesureur(val);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnKillfocusMesureur() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip1241L*)equip)->ChangeMesureur(0,atoi(m_mesureur),((CEquip1241L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnKillfocusCorSquelch() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip1241L*)equip)->ChangeCorSquelch(atoi(m_cor_squelch),((CEquip1241L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnAutoCentrage() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F4_AUTO_CENTRAGE))->GetCheck();
	iResult = ((CEquip1241L*)equip)->ChangeAutoCentrageF1(val);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnKillfocusCentrage() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip1241L*)equip)->ChangeCentrageF1(atoi(m_centrage),((CEquip1241L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnKillfocusCanal() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip1241L*)equip)->ChangeCanal(atoi(m_canal),((CEquip1241L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
	
}

void CDlg1241L::OnMemoCanal() 
{
	int		iResult;

	int		num_canal = ((CEquip1241L*)equip)->Canal();

	iResult = ((CEquip1241L*)equip)->MemoriseCanal(num_canal,((CEquip1241L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnKillfocusCodeTest() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip1241L*)equip)->ChangeTest(atoi(m_code_test),((CEquip1241L*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg1241L::OnModeLoc() 
{
	int	iResult = ((CEquip1241L*)equip)->ChangeLocal(0,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie

}

void CDlg1241L::OnModeRmt() 
{
	int	iResult = ((CEquip1241L*)equip)->ChangeLocal(1,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie

}

void CDlg1241L::Verrouille(BOOL etat)
{

// Mode reception
	m_mode_reception.EnableWindow(etat);

// Attenuateur HF
	GetDlgItem(F4_IDC_ATTENUATEUR_0)->EnableWindow(etat);
	GetDlgItem(F4_IDC_ATTENUATEUR_1)->EnableWindow(etat);
	GetDlgItem(F4_IDC_ATTENUATEUR_2)->EnableWindow(etat);

// Filtre FI
	GetDlgItem(F4_BP5)->EnableWindow(etat);
	GetDlgItem(F4_BP1)->EnableWindow(etat);
	GetDlgItem(F4_BP2)->EnableWindow(etat);
	GetDlgItem(F4_BP3)->EnableWindow(etat);
	GetDlgItem(F4_BP4)->EnableWindow(etat);

// CAG
	m_cag.EnableWindow(etat);

// Squelch
	GetDlgItem(F4_SQUELCH)->EnableWindow(etat);

// Sens de manipulation télégraphique
	m_sens_manip.EnableWindow(etat);

// Shift
	m_shift.EnableWindow(etat);

// Frequence
	GetDlgItem(F4_FREQUENCE)->EnableWindow(etat);

// Frequence BFO
	GetDlgItem(F4_BFO)->EnableWindow(etat);

// Avec Rejecteur
	GetDlgItem(F4_REJECTEUR)->EnableWindow(etat);

// Frequence Rejecteur
	GetDlgItem(F4_FREQ_REJECT)->EnableWindow(etat);

// Gain HF
	GetDlgItem(F4_GAIN_HF)->EnableWindow(etat);
 
 // Mesureur de champs
	GetDlgItem(F4_MESUREUR)->EnableWindow(etat);
	GetDlgItem(F4_AUTO_MESUREUR)->EnableWindow(etat);

// Seuil Cor/Squelch
	GetDlgItem(F4_COR_SQUELCH)->EnableWindow(etat);

// Centrage Démodulateur F1
	GetDlgItem(F4_CENTRAGE)->EnableWindow(etat);
	GetDlgItem(F4_AUTO_CENTRAGE)->EnableWindow(etat);

// Canal
	GetDlgItem(F4_CANAL)->EnableWindow(etat);

// Code Test
	GetDlgItem(F4_CODE_TEST)->EnableWindow(etat);

// Code Test
	GetDlgItem(F4_INFO)->EnableWindow(etat);
}

