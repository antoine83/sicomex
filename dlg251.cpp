/* **************************************************************************
FICHIER :	Dlg251.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlg251
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "Dlg251.h"
#include "Equip\Eqp251.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_R_251[];

CDlg251::CDlg251(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDlg251::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg251)
	m_err_retard = _T("");
	m_periode = _T("");
	m_tempo = _T("");
	m_canal = _T("");
	m_frequence = _T("");
	m_bfo = _T("");
	m_fibo_v1 = _T("");
	m_fibo_v2 = _T("");
	m_fibo_v3 = _T("");
	m_fibo_v4 = _T("");
	m_defaut = _T("");
	m_qbit_mini = _T("");
	m_qbit_maxi = _T("");
	m_peigne = _T("");
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDI_REC_HF);
}


void CDlg251::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg251)
	DDX_Control(pDX, F9_SYNCHRO_TRAME_V4, m_synchro_v4);
	DDX_Control(pDX, F9_SYNCHRO_TRAME_V3, m_synchro_v3);
	DDX_Control(pDX, F9_SYNCHRO_TRAME_V2, m_synchro_v2);
	DDX_Control(pDX, F9_SYNCHRO_TRAME_V1, m_synchro_v1);
	DDX_Control(pDX, F9_ETAT_SYNCHRO, m_etat_synchro);
	DDX_Control(pDX, F9_MODULATION, m_modulation);
	DDX_Control(pDX, IDC_PARITE, m_parite);
	DDX_Control(pDX, IDC_MES_STATUT, m_liste_message);
	DDX_Control(pDX, IDC_CHECK_SYNCHRO, m_synchro);
	DDX_Control(pDX, IDC_CHECK_CYCLE, m_cycle);
	DDX_Text(pDX, IDC_RETARD, m_err_retard);
	DDX_Text(pDX, IDC_EDIT_CYCLE, m_periode);
	DDX_Text(pDX, IDC_EDIT_TEMPO, m_tempo);
	DDX_Text(pDX, F9_CANAL, m_canal);
	DDX_Text(pDX, F9_FREQUENCE, m_frequence);
	DDX_Text(pDX, F9_FREQ_BFO, m_bfo);
	DDX_Text(pDX, F9_FIBO_V1, m_fibo_v1);
	DDX_Text(pDX, F9_FIBO_V2, m_fibo_v2);
	DDX_Text(pDX, F9_FIBO_V3, m_fibo_v3);
	DDX_Text(pDX, F9_FIBO_V4, m_fibo_v4);
	DDX_Text(pDX, F9_TEST_RESULT, m_defaut);
	DDX_Text(pDX, F9_QB_MINI, m_qbit_mini);
	DDX_Text(pDX, F9_QB_MAXI, m_qbit_maxi);
	DDX_Text(pDX, F9_PEIGNE, m_peigne);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg251, CDialog)
	//{{AFX_MSG_MAP(CDlg251)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_PARITE, OnComErreur)
	ON_BN_CLICKED(F9_TRAFFIC, OnTraffic)
	ON_BN_CLICKED(F9_LOCAL, OnLocal)
	ON_EN_KILLFOCUS(F9_CANAL, OnKillfocusCanal)
	ON_EN_KILLFOCUS(F9_FREQUENCE, OnKillfocusFrequence)
	ON_CBN_SELCHANGE(F9_MODULATION, OnSelchangeModulation)
	ON_EN_KILLFOCUS(F9_FREQ_BFO, OnKillfocusFreqBfo)
	ON_BN_CLICKED(F9_A1, OnA1)
	ON_BN_CLICKED(F9_A2, OnA2)
	ON_BN_CLICKED(F9_A3, OnA3)
	ON_BN_CLICKED(F9_CAG, OnCag)
	ON_BN_CLICKED(F9_LIMITTEUR, OnLimitteur)
	ON_BN_CLICKED(F9_INTERFACE_V1, OnInterface)
	ON_BN_CLICKED(F9_INVERSION_V1, OnInversion)
	ON_BN_CLICKED(F9_TEST_1, OnTest1)
	ON_BN_CLICKED(F9_TEST_2, OnTest2)
	ON_BN_CLICKED(F9_TEST_3, OnTest3)
	ON_BN_CLICKED(F9_ARRET_ALARME, OnArretAlarme)
	ON_EN_KILLFOCUS(F9_TEST_RESULT, OnKillfocusTestResult)
	ON_BN_CLICKED(F9_DEFAUT_CARTE1, OnDefautCarte1)
	ON_BN_CLICKED(F9_DEFAUT_CARTE2, OnDefautCarte2)
	ON_BN_CLICKED(F9_DEFAUT_CARTE3, OnDefautCarte3)
	ON_BN_CLICKED(F9_AUTO_QB_MAXI, OnAutoQbMaxi)
	ON_BN_CLICKED(F9_AUTO_QB_MINI, OnAutoQbMini)
	ON_EN_KILLFOCUS(F9_QB_MAXI, OnKillfocusQbMaxi)
	ON_EN_KILLFOCUS(F9_QB_MINI, OnKillfocusQbMini)
	ON_CBN_SELCHANGE(F9_ETAT_SYNCHRO, OnSelchangeEtatSynchro)
	ON_EN_KILLFOCUS(F9_FIBO_V1, OnKillfocusFibo)
	ON_BN_CLICKED(F9_AUTO_FIBO, OnAutoFibo)
	ON_BN_CLICKED(F9_AUTO_PEIGNE, OnAutoPeigne)
	ON_CBN_SELCHANGE(F9_SYNCHRO_TRAME_V1, OnSelchangeSynchroTrame)
	ON_BN_CLICKED(F9_MEMO_CANAL, OnMemoCanal)
	ON_BN_CLICKED(IDC_CDE_INCONUE, OnComErreur)
	ON_BN_CLICKED(IDC_DEBUT_TRAME, OnComErreur)
	ON_BN_CLICKED(IDC_FIN_TRAME, OnComErreur)
	ON_BN_CLICKED(IDC_PAS_REPONSE, OnComErreur)
	ON_EN_KILLFOCUS(IDC_RETARD, OnComErreur)
	ON_BN_CLICKED(F9_INVERSION_V2, OnInversion)
	ON_BN_CLICKED(F9_INVERSION_V3, OnInversion)
	ON_BN_CLICKED(F9_INVERSION_V4, OnInversion)
	ON_BN_CLICKED(F9_INTERFACE_V2, OnInterface)
	ON_BN_CLICKED(F9_INTERFACE_V3, OnInterface)
	ON_BN_CLICKED(F9_INTERFACE_V4, OnInterface)
	ON_EN_KILLFOCUS(F9_FIBO_V2, OnKillfocusFibo)
	ON_EN_KILLFOCUS(F9_FIBO_V3, OnKillfocusFibo)
	ON_EN_KILLFOCUS(F9_FIBO_V4, OnKillfocusFibo)
	ON_CBN_SELCHANGE(F9_SYNCHRO_TRAME_V2, OnSelchangeSynchroTrame)
	ON_CBN_SELCHANGE(F9_SYNCHRO_TRAME_V3, OnSelchangeSynchroTrame)
	ON_CBN_SELCHANGE(F9_SYNCHRO_TRAME_V4, OnSelchangeSynchroTrame)
	ON_EN_KILLFOCUS(F9_PEIGNE, OnKillfocusPeigne)
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


void CDlg251::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_R_251,"Récepteur VHF");
	if(iResult >=  0) win.DoModal();
}

BOOL CDlg251::OnInitDialog() 
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
	m_liste_message.AddString("Init en console");
	m_liste_message.AddString("ENQ");
	m_liste_message.AddString("ACK");
	m_liste_message.AddString("BEL");
	m_liste_message.AddString("Config. op.");// cde 5
	m_liste_message.AddString("Polarité");
	m_liste_message.AddString("Fréquence");
	m_liste_message.AddString("Frequence BFO");
	m_liste_message.AddString("Traffic");
	m_liste_message.AddString("Attenuation"); // cde 10
	m_liste_message.AddString("Limitteur");
	m_liste_message.AddString("Interface V/J");
	m_liste_message.AddString("Entrée fct Canal");
	m_liste_message.AddString("Polarité Canal");
	m_liste_message.AddString("Sortie fct Canal");	// cde 15
	m_liste_message.AddString("Frequence Canal");
	m_liste_message.AddString("Freq BFO Canal");
	m_liste_message.AddString("Attenuation Canal");
	m_liste_message.AddString("Limitteur Canal");
	m_liste_message.AddString("Mod./Interf. Canal");// cde 20
	m_liste_message.AddString("Stockage Canal");
	m_liste_message.AddString("Etat du test");
	m_liste_message.AddString("Cag");	// cde 25
	m_liste_message.AddString("Synchro. bit");
	m_liste_message.AddString("Synchro.trame V1");
	m_liste_message.AddString("Synchro.trame V2");
	m_liste_message.AddString("Synchro.trame V3");
	m_liste_message.AddString("Synchro.trame V4");
	m_liste_message.AddString("Qualité de bit");
	m_liste_message.AddString("Note FIBO V1");
	m_liste_message.AddString("Note FIBO V2");
	m_liste_message.AddString("Note FIBO V3");
	m_liste_message.AddString("Note FIBO V4");
	m_liste_message.AddString("Numero de peigne");
	m_liste_message.AddString("Valeur des défauts");  // cde 30
	m_liste_message.AddString("Local/distance");

// Custom control
// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);	
	m_trafic.SubclassDlgItem(F9_TRAFFIC,this);
	m_local.SubclassDlgItem(F9_LOCAL,this);
	m_mode_console.SubclassDlgItem(F9_CONSOLE,this);

	m_vitesse.SubclassDlgItem(F9_VIT_RECHERCHE,this);

// Initialisation de la face avant
// *******************************
	m_modulation.AddString("EXT");
	m_modulation.AddString("A1");
	m_modulation.AddString("F1 ind 1");
	m_modulation.AddString("F1 ind 1,7");
	m_modulation.AddString("CPFSK");
	m_modulation.AddString("MSK1");
	m_modulation.AddString("MSK2");
	m_modulation.AddString("MSK4");

	m_modulation.AddString("PTG mode protégé");
	m_modulation.AddString("F1 ind 1,13");

	m_etat_synchro.AddString("Acquise");
	m_etat_synchro.AddString("Confirmation");
	m_etat_synchro.AddString("Recherche");

	m_synchro_v1.AddString("HORS trafic");
	m_synchro_v1.AddString("LO cal");
	m_synchro_v1.AddString("ACT ualisation");
	m_synchro_v1.AddString("RCV (Rec. conv.)");
	m_synchro_v1.AddString("Jason");
	m_synchro_v1.AddString("FIL ler");
	m_synchro_v1.AddString("SYN chronisation");

	m_synchro_v2.AddString("HORS trafic");
	m_synchro_v2.AddString("LO cal");
	m_synchro_v2.AddString("ACT ualisation");
	m_synchro_v2.AddString("RCV (Rec. conv.)");
	m_synchro_v2.AddString("Jason");
	m_synchro_v2.AddString("FIL ler");
	m_synchro_v2.AddString("SYN chronisation");

	m_synchro_v3.AddString("HORS trafic");
	m_synchro_v3.AddString("LO cal");
	m_synchro_v3.AddString("ACT ualisation");
	m_synchro_v3.AddString("RCV (Rec. conv.)");
	m_synchro_v3.AddString("Jason");
	m_synchro_v3.AddString("FIL ler");
	m_synchro_v3.AddString("SYN chronisation");

	m_synchro_v4.AddString("HORS trafic");
	m_synchro_v4.AddString("LO cal");
	m_synchro_v4.AddString("ACT ualisation");
	m_synchro_v4.AddString("RCV (Rec. conv.)");
	m_synchro_v4.AddString("Jason");
	m_synchro_v4.AddString("FIL ler");
	m_synchro_v4.AddString("SYN chronisation");

	GetDlgItem(F9_INTERFACE_V1)->EnableWindow(0);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// GenrateurAuto():	Effectue les variation automatique de certains paramètres
void CDlg251::GenerateurAuto()
{
	if(!((CEquip251*)equip)->Trafic()) return;

	int val[REC_251_NB_VOIE];

	srand( (unsigned)time( NULL ) );

	if(((CEquip251*)equip)->AutoAlarme())
			((CEquip251*)equip)->ChangeDefaut(((CEquip251*)equip)->Defaut(),TRUE);

	if(((CEquip251*)equip)->AutoMini())
		((CEquip251*)equip)->ChangeQBitMini(rand()%128,TRUE);

	if(((CEquip251*)equip)->AutoMaxi())
		((CEquip251*)equip)->ChangeQBitMaxi(rand()%128,TRUE);

	if(((CEquip251*)equip)->AutoFibo())
	{
		val[0] = rand()%101;
		val[1] = rand()%101;
		val[2] = rand()%101;
		val[3] = rand()%101;
		((CEquip251*)equip)->ChangeFibo(val,TRUE);
	}

	if(((CEquip251*)equip)->AutoPeigne())
		((CEquip251*)equip)->ChangePeigne(rand()%16,TRUE);

}

// OnTimer : Rafraichissement de l'écran de controle **************************
// ****************************************************************************
void CDlg251::OnTimer(UINT nIDEvent) 
{
	int		val;
	char	buf[10];
	int		etat_voie[REC_251_NB_VOIE];
	int		valeur_voie[REC_251_NB_VOIE];

	UpdateData(TRUE);

	CDialog::OnTimer(nIDEvent);
	CDlgEquip::OnTimer();			// Rafraichissement des controles commun

// Test de changement dans la face avant
	val = equip->Evolution();
	if (val==evolution) return;		// Rafraichissement inutile
	evolution = val;

	// Verrouille(!((CEquip251*)equip)->Local());

	((CEquip251*)equip)->VoieActive(0,etat_voie);

	// Interface
		GetDlgItem(F9_INTERFACE_V2)->EnableWindow(etat_voie[1]);
		GetDlgItem(F9_INTERFACE_V3)->EnableWindow(etat_voie[2]);
		GetDlgItem(F9_INTERFACE_V4)->EnableWindow(etat_voie[3]);

	// Inversion
		GetDlgItem(F9_INVERSION_V1)->EnableWindow(etat_voie[0]);
		GetDlgItem(F9_INVERSION_V2)->EnableWindow(etat_voie[1]);
		GetDlgItem(F9_INVERSION_V3)->EnableWindow(etat_voie[2]);
		GetDlgItem(F9_INVERSION_V4)->EnableWindow(etat_voie[3]);

	// Synchro trame
		GetDlgItem(F9_SYNCHRO_TRAME_V1)->EnableWindow(etat_voie[0]);
		GetDlgItem(F9_SYNCHRO_TRAME_V2)->EnableWindow(etat_voie[1]);
		GetDlgItem(F9_SYNCHRO_TRAME_V3)->EnableWindow(etat_voie[2]);
		GetDlgItem(F9_SYNCHRO_TRAME_V4)->EnableWindow(etat_voie[3]);

	// Note Fibo
		GetDlgItem(F9_FIBO_V1)->EnableWindow(etat_voie[0]);
		GetDlgItem(F9_FIBO_V2)->EnableWindow(etat_voie[1]);
		GetDlgItem(F9_FIBO_V3)->EnableWindow(etat_voie[2]);
		GetDlgItem(F9_FIBO_V4)->EnableWindow(etat_voie[3]);
	
// Liaison telecommande
	val = ((CEquip251*)equip)->Telecommande();
	if(&m_mode_console != GetFocus() && m_mode_console.Retourne_etat()!=val)
		m_mode_console.Positionne_etat(val);

// Mode trafic
	val = ((CEquip251*)equip)->Trafic();
	if(&m_trafic != GetFocus() && m_trafic.Retourne_etat()!=val)
		m_trafic.Positionne_etat(val);

// Local/distance
	val = ((CEquip251*)equip)->Local();
	if(&m_local != GetFocus() && m_local.Retourne_etat()!=val)
		m_local.Positionne_etat(val);

// Canal
	if(GetDlgItem(F9_CANAL) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip251*)equip)->Canal());
		m_canal = buf;
	}

// Mode de reception
//	if(&m_modulation != GetFocus())
//	{
		val = ((CEquip251*)equip)->ModeRecep(0);
		m_modulation.SetCurSel(val);
//	}

// Frequence
	if(GetDlgItem(F9_FREQUENCE) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip251*)equip)->Frequence(0));
		m_frequence = buf;
	}

// Frequence BFO
	if(GetDlgItem(F9_FREQ_BFO) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip251*)equip)->Bfo(0));
		m_bfo = buf;
	}

// Attenuation
	SendDlgItemMessage(F9_A1,BM_SETCHECK,0,0);
	SendDlgItemMessage(F9_A2,BM_SETCHECK,0,0);
	SendDlgItemMessage(F9_A3,BM_SETCHECK,0,0);
	val = ((CEquip251*)equip)->Attenuation(0);
	switch(val)
	{
		case 1:
			SendDlgItemMessage(F9_A2,BM_SETCHECK,1,0);
			break;
		case 2:
			SendDlgItemMessage(F9_A3,BM_SETCHECK,1,0);
			break;
		default:
			SendDlgItemMessage(F9_A1,BM_SETCHECK,1,0);
			break;
	}

// Cag
	val = ((CEquip251*)equip)->Cag(0);
	SendDlgItemMessage(F9_CAG,BM_SETCHECK,val,0);

// Limiteur
	val = ((CEquip251*)equip)->Limiteur(0);
	SendDlgItemMessage(F9_LIMITTEUR,BM_SETCHECK,val,0);

// Interface
	((CEquip251*)equip)->Interface(0,valeur_voie);
	SendDlgItemMessage(F9_INTERFACE_V1,BM_SETCHECK,valeur_voie[0],0);
	SendDlgItemMessage(F9_INTERFACE_V2,BM_SETCHECK,valeur_voie[1],0);
	SendDlgItemMessage(F9_INTERFACE_V3,BM_SETCHECK,valeur_voie[2],0);
	SendDlgItemMessage(F9_INTERFACE_V4,BM_SETCHECK,valeur_voie[3],0);

// Interface
	((CEquip251*)equip)->Polarite(0,valeur_voie);
	SendDlgItemMessage(F9_INVERSION_V1,BM_SETCHECK,valeur_voie[0],0);
	SendDlgItemMessage(F9_INVERSION_V2,BM_SETCHECK,valeur_voie[1],0);
	SendDlgItemMessage(F9_INVERSION_V3,BM_SETCHECK,valeur_voie[2],0);
	SendDlgItemMessage(F9_INVERSION_V4,BM_SETCHECK,valeur_voie[3],0);

// Etat test
	SendDlgItemMessage(F9_TEST_1,BM_SETCHECK,0,0);
	SendDlgItemMessage(F9_TEST_2,BM_SETCHECK,0,0);
	SendDlgItemMessage(F9_TEST_3,BM_SETCHECK,0,0);
	val = ((CEquip251*)equip)->EtatTest();
	switch(val)
	{
		case 1:
			SendDlgItemMessage(F9_TEST_2,BM_SETCHECK,1,0);
			break;
		case 2:
			SendDlgItemMessage(F9_TEST_3,BM_SETCHECK,1,0);
			break;
		default:
			SendDlgItemMessage(F9_TEST_1,BM_SETCHECK,1,0);
			break;
	}

// Arret Alarme
	val = ((CEquip251*)equip)->AutoAlarme();
	SendDlgItemMessage(F9_ARRET_ALARME,BM_SETCHECK,val,0);

// Defaut general
	if(GetDlgItem(F9_TEST_RESULT) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip251*)equip)->Defaut());
		m_defaut = buf;
	}

// Defaut Carte 1
	val = ((CEquip251*)equip)->DefautCarte1();
	SendDlgItemMessage(F9_DEFAUT_CARTE1,BM_SETCHECK,val,0);

// Defaut Carte 2
	val = ((CEquip251*)equip)->DefautCarte2();
	SendDlgItemMessage(F9_DEFAUT_CARTE2,BM_SETCHECK,val,0);

// Defaut Carte 3
	val = ((CEquip251*)equip)->DefautCarte3();
	SendDlgItemMessage(F9_DEFAUT_CARTE3,BM_SETCHECK,val,0);

// QBit mini
	if(GetDlgItem(F9_QB_MINI) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip251*)equip)->QBitMini());
		m_qbit_mini = buf;
	}

// Auo mini
	val = ((CEquip251*)equip)->AutoMini();
	SendDlgItemMessage(F9_AUTO_QB_MINI,BM_SETCHECK,val,0);

// QBit maxi
	if(GetDlgItem(F9_QB_MAXI) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip251*)equip)->QBitMaxi());
		m_qbit_maxi = buf;
	}

// Auo maxi
	val = ((CEquip251*)equip)->AutoMaxi();
	SendDlgItemMessage(F9_AUTO_QB_MAXI,BM_SETCHECK,val,0);

// Etat Synchro
	val = ((CEquip251*)equip)->EtatSynchro();
	m_etat_synchro.SetCurSel(val);

// Note Fibo
	((CEquip251*)equip)->Fibo(valeur_voie);
	if(GetDlgItem(F9_FIBO_V1) != GetFocus())
	{
		sprintf(buf,"%d",valeur_voie[0]);
		m_fibo_v1 = buf;
	}
	if(GetDlgItem(F9_FIBO_V2) != GetFocus())
	{
		sprintf(buf,"%d",valeur_voie[1]);
		m_fibo_v2 = buf;
	}
	if(GetDlgItem(F9_FIBO_V3) != GetFocus())
	{
		sprintf(buf,"%d",valeur_voie[2]);
		m_fibo_v3 = buf;
	}
	if(GetDlgItem(F9_FIBO_V4) != GetFocus())
	{
		sprintf(buf,"%d",valeur_voie[3]);
		m_fibo_v4 = buf;
	}

// Auto FIBO
	val = ((CEquip251*)equip)->AutoFibo();
	SendDlgItemMessage(F9_AUTO_FIBO,BM_SETCHECK,val,0);

// Note Peigne
	;
	if(GetDlgItem(F9_PEIGNE) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip251*)equip)->Peigne());
		m_peigne = buf;
	}

// Auto Peigne
	val = ((CEquip251*)equip)->AutoPeigne();
	SendDlgItemMessage(F9_AUTO_PEIGNE,BM_SETCHECK,val,0);


// Vitesse de recherche synchro
	((CEquip251*)equip)->Vitesse();
	m_vitesse.Positionne_etat(((CEquip251*)equip)->Vitesse());

// Etat Synchro
	((CEquip251*)equip)->SynchroTrame(valeur_voie);
	m_synchro_v1.SetCurSel(valeur_voie[0]);
	m_synchro_v2.SetCurSel(valeur_voie[1]);
	m_synchro_v3.SetCurSel(valeur_voie[2]);
	m_synchro_v4.SetCurSel(valeur_voie[3]);

// Mise à jour de CEdit
// ********************
	UpdateData(FALSE);
}

// Comm erreur ********************************************
void CDlg251::OnComErreur() 
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

void CDlg251::Verrouille(BOOL etat)
{

// Mode reception
//	m_mode_reception.EnableWindow(etat);

// Attenuateur HF
//	GetDlgItem(F4_IDC_ATTENUATEUR_0)->EnableWindow(etat);
}

void CDlg251::OnTraffic() 
{
	int	iResult = m_trafic.Inverse_etat();
 	((CEquip251*)equip)->ChangeTrafic(iResult,TRUE);
}

void CDlg251::OnLocal() 
{
	int	iResult = m_local.Inverse_etat();
 	((CEquip251*)equip)->ChangeLocal(iResult,TRUE);
}

void CDlg251::OnKillfocusCanal() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip251*)equip)->ChangeCanal(atoi(m_canal),TRUE);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnKillfocusFrequence() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip251*)equip)->ChangeFrequence(0,atoi(m_frequence),TRUE);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnSelchangeModulation() 
{
	int	iResult = ((CEquip251*)equip)->ChangeModeRecep(0,m_modulation.GetCurSel(),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}


void CDlg251::OnKillfocusFreqBfo() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip251*)equip)->ChangeBfo(0,atoi(m_bfo),TRUE);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnA1() 
{
	int	iResult = ((CEquip251*)equip)->ChangeAttenuation(0,0,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnA2() 
{
	int	iResult = ((CEquip251*)equip)->ChangeAttenuation(0,1,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnA3() 
{
	int	iResult = ((CEquip251*)equip)->ChangeAttenuation(0,2,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnCag() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F9_CAG))->GetCheck();
	iResult = ((CEquip251*)equip)->ChangeCag(0,val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnLimitteur() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F9_LIMITTEUR))->GetCheck();
	iResult = ((CEquip251*)equip)->ChangeLimiteur(0,val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnInterface() 
{
	int		iResult;

	int		val[REC_251_NB_VOIE];
	
	val[0] =((CButton*)GetDlgItem(F9_INTERFACE_V1))->GetCheck();
	val[1] =((CButton*)GetDlgItem(F9_INTERFACE_V2))->GetCheck();
	val[2] =((CButton*)GetDlgItem(F9_INTERFACE_V3))->GetCheck();
	val[3] =((CButton*)GetDlgItem(F9_INTERFACE_V4))->GetCheck();

	iResult = ((CEquip251*)equip)->ChangeInterface(0,val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnInversion() 
{
	int		iResult;

	int		val[REC_251_NB_VOIE];
	
	UpdateData(TRUE);
	val[0] =((CButton*)GetDlgItem(F9_INVERSION_V1))->GetCheck();
	val[1] =((CButton*)GetDlgItem(F9_INVERSION_V2))->GetCheck();
	val[2] =((CButton*)GetDlgItem(F9_INVERSION_V3))->GetCheck();
	val[3] =((CButton*)GetDlgItem(F9_INVERSION_V4))->GetCheck();

	iResult = ((CEquip251*)equip)->ChangePolarite(0,val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnTest1() 
{
	int	iResult = ((CEquip251*)equip)->ChangeEtatTest(0,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnTest2() 
{
	int	iResult = ((CEquip251*)equip)->ChangeEtatTest(1,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnTest3() 
{
	int	iResult = ((CEquip251*)equip)->ChangeEtatTest(2,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnArretAlarme() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F9_ARRET_ALARME))->GetCheck();
	iResult = ((CEquip251*)equip)->ChangeAutoAlarme(val,FALSE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnKillfocusTestResult() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip251*)equip)->ChangeDefaut(atoi(m_defaut),TRUE);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnDefautCarte1() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F9_DEFAUT_CARTE1))->GetCheck();
	iResult = ((CEquip251*)equip)->ChangeDefautCarte1(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnDefautCarte2() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F9_DEFAUT_CARTE2))->GetCheck();
	iResult = ((CEquip251*)equip)->ChangeDefautCarte2(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnDefautCarte3() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F9_DEFAUT_CARTE3))->GetCheck();
	iResult = ((CEquip251*)equip)->ChangeDefautCarte3(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnAutoQbMaxi() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F9_AUTO_QB_MAXI))->GetCheck();
	iResult = ((CEquip251*)equip)->ChangeAutoMaxi(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnAutoQbMini() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F9_AUTO_QB_MINI))->GetCheck();
	iResult = ((CEquip251*)equip)->ChangeAutoMini(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnKillfocusQbMaxi() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip251*)equip)->ChangeQBitMaxi(atoi(m_qbit_maxi),TRUE);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnKillfocusQbMini() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip251*)equip)->ChangeQBitMini(atoi(m_qbit_mini),TRUE);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnSelchangeEtatSynchro() 
{
	int	iResult = ((CEquip251*)equip)->ChangeEtatSynchro(m_etat_synchro.GetCurSel(),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnKillfocusFibo() 
{
	int		iResult;

	int		val[REC_251_NB_VOIE];
	
	UpdateData(TRUE);
	val[0] = atoi(m_fibo_v1);
	val[1] = atoi(m_fibo_v2);
	val[2] = atoi(m_fibo_v3);
	val[3] = atoi(m_fibo_v4);

	iResult = ((CEquip251*)equip)->ChangeFibo(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnAutoFibo() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F9_AUTO_FIBO))->GetCheck();
	iResult = ((CEquip251*)equip)->ChangeAutoFibo(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnKillfocusPeigne() 
{
	int		iResult;

	
	UpdateData(TRUE);

	iResult = ((CEquip251*)equip)->ChangePeigne(atoi(m_peigne),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnAutoPeigne() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F9_AUTO_PEIGNE))->GetCheck();
	iResult = ((CEquip251*)equip)->ChangeAutoPeigne(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnSelchangeSynchroTrame() 
{
	int		iResult;

	int		val[REC_251_NB_VOIE];

	val[0] = m_synchro_v1.GetCurSel();
	val[1] = m_synchro_v2.GetCurSel();
	val[2] = m_synchro_v3.GetCurSel();
	val[3] = m_synchro_v4.GetCurSel();

	iResult = ((CEquip251*)equip)->ChangeSynchroTrame(val,TRUE);

	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg251::OnMemoCanal() 
{
	int		iResult;

	int		num_canal = ((CEquip251*)equip)->Canal();

	iResult = ((CEquip251*)equip)->MemoriseCanal(num_canal,TRUE);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}
