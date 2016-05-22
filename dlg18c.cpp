/* **************************************************************************
FICHIER :	Dlg18C.CPP		 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlg18C
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "Dlg18C.h"
#include "Equip\Eqp18C.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_EMR_18[];

CDlg18C::CDlg18C(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDlg18C::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg18C)
	m_err_retard = _T("");
	m_adresse = _T("");
	m_canal = _T("");
	m_cle_crypto = _T("");
	m_code_test = _T("");
	m_freq_em = _T("");
	m_freq_rec = _T("");
	m_gene_crypto = _T("");
	m_scan_deb = _T("");
	m_scan_fin = _T("");
	m_periode = _T("");
	m_tempo = _T("");
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDR_SICOMEX);
}

void CDlg18C::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg18C)
	DDX_Control(pDX, F7_RELAIS, m_relais);
	DDX_Control(pDX, F7_PAS_REC, m_pas_rec);
	DDX_Control(pDX, F7_PAS_EM, m_pas_em);
	DDX_Control(pDX, F7_ANTENNE, m_antenne);
	DDX_Control(pDX, F7_MODE, m_mode);
	DDX_Control(pDX, F7_NIVEAU, m_niveau);
	DDX_Control(pDX, IDC_MES_STATUT, m_liste_message);
	DDX_Control(pDX, IDC_CHECK_SYNCHRO, m_synchro);
	DDX_Control(pDX, IDC_CHECK_CYCLE, m_cycle);
	DDX_Text(pDX, IDC_RETARD, m_err_retard);
	DDX_Text(pDX, F7_ADRESSE, m_adresse);
	DDX_Text(pDX, F7_CANAL, m_canal);
	DDX_Text(pDX, F7_CLE_CRYPTO, m_cle_crypto);
	DDX_Text(pDX, F7_CODE_TEST, m_code_test);
	DDX_Text(pDX, F7_FREQ_EM, m_freq_em);
	DDX_Text(pDX, F7_FREQ_REC, m_freq_rec);
	DDX_Text(pDX, F7_GENE_CRYPTO, m_gene_crypto);
	DDX_Text(pDX, F7_SCAN_DEB, m_scan_deb);
	DDX_Text(pDX, F7_SCAN_FIN, m_scan_fin);
	DDX_Text(pDX, IDC_EDIT_CYCLE, m_periode);
	DDX_Text(pDX, IDC_EDIT_TEMPO, m_tempo);
	//}}AFX_DATA_MAP
}

BEGIN_MESSAGE_MAP(CDlg18C, CDialog)
	//{{AFX_MSG_MAP(CDlg18C)
	ON_WM_TIMER()
	ON_EN_KILLFOCUS(F7_FREQ_EM, OnKillfocusFreqEm)
	ON_EN_KILLFOCUS(F7_FREQ_REC, OnKillfocusFreqRec)
	ON_BN_CLICKED(IDC_PARITE, OnComErreur)
	ON_EN_KILLFOCUS(F7_CANAL, OnKillfocusCanal)
	ON_CBN_SELCHANGE(F7_NIVEAU, OnSelchangeNiveau)
	ON_CBN_SELCHANGE(F7_MODE, OnSelchangeMode)
	ON_BN_CLICKED(F7_NB, OnNb)
	ON_BN_CLICKED(F7_WB, OnWb)
	ON_EN_KILLFOCUS(F7_CLE_CRYPTO, OnKillfocusCleCrypto)
	ON_CBN_SELCHANGE(F7_ANTENNE, OnSelchangeAntenne)
	ON_BN_CLICKED(F7_SQUELCH, OnSquelch)
	ON_CBN_SELCHANGE(F7_PAS_EM, OnSelchangePasEm)
	ON_CBN_SELCHANGE(F7_PAS_REC, OnSelchangePasRec)
	ON_BN_CLICKED(F7_PROTECTION, OnProtection)
	ON_CBN_SELCHANGE(F7_RELAIS, OnSelchangeRelais)
	ON_BN_CLICKED(F7_REC_GARDE, OnRecGarde)
	ON_EN_KILLFOCUS(F7_SCAN_DEB, OnKillfocusScanDeb)
	ON_EN_KILLFOCUS(F7_SCAN_FIN, OnKillfocusScanFin)
	ON_EN_KILLFOCUS(F7_ADRESSE, OnKillfocusAdresse)
	ON_EN_KILLFOCUS(F7_GENE_CRYPTO, OnKillfocusGeneCrypto)
	ON_BN_CLICKED(F7_LOCAL, OnLocal)
	ON_BN_CLICKED(F7_HF, OnHf)
	ON_BN_CLICKED(F7_ROS, OnRos)
	ON_BN_CLICKED(F7_EMISSION, OnEmission)
	ON_BN_CLICKED(F7_SILENCE, OnSilence)
	ON_BN_CLICKED(F7_BF, OnBf)
	ON_BN_CLICKED(F7_SCAN, OnScan)
	ON_EN_KILLFOCUS(F7_CODE_TEST, OnKillfocusCodeTest)
	ON_BN_CLICKED(F7_MEMO_CANAL, OnMemoCanal)
	ON_BN_CLICKED(F7_PANNE_ACCORD, OnPanneAccord)
	ON_BN_CLICKED(F7_PANNE_EMR, OnPanneEmr)
	ON_BN_CLICKED(IDC_CDE_INCONUE, OnComErreur)
	ON_BN_CLICKED(IDC_DEBUT_TRAME, OnComErreur)
	ON_BN_CLICKED(IDC_FIN_TRAME, OnComErreur)
	ON_EN_KILLFOCUS(IDC_RETARD, OnComErreur)
	ON_BN_CLICKED(IDC_PAS_REPONSE, OnComErreur)
	ON_BN_CLICKED(F7_ACCORD_EN_COURS, OnAccordEnCours)
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
// CDlg18C message handlers

void CDlg18C::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_EMR_18,"Emetteur/récepteur HF");
	if(iResult >=  0) win.DoModal();
}

BOOL CDlg18C::OnInitDialog() 
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
	m_liste_message.AddString("Données d'exploitation");
	m_liste_message.AddString("Surveillance");
	m_liste_message.AddString("Surveillance & Status");

// Custom control
// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);	
	m_local.SubclassDlgItem(F7_LOCAL,this);	
	m_silence.SubclassDlgItem(F7_SILENCE,this);	
	m_scan.SubclassDlgItem(F7_SCAN,this);	
	m_hf.SubclassDlgItem(F7_HF,this);	
	m_ros.SubclassDlgItem(F7_ROS,this);	
	m_bf.SubclassDlgItem(F7_BF,this);	
	m_emission.SubclassDlgItem(F7_EMISSION,this);	

	m_accord_en_cours.SubclassDlgItem(F7_ACCORD_EN_COURS,this);	

	m_panne_emr.SubclassDlgItem(F7_PANNE_EMR,this);
	m_panne_accord.SubclassDlgItem(F7_PANNE_ACCORD,this);

	m_accord.SubclassDlgItem(F7_ACCORD,this);
	m_rec_garde.SubclassDlgItem(F7_REC_GARDE,this);
	
// Initialisation de la face avant
// *******************************
	m_niveau.AddString("nominal");
	m_niveau.AddString("-6 dB");
	m_niveau.AddString("-12 dB");
	m_niveau.AddString("-18 dB");
	m_niveau.AddString("-24 dB");

	m_mode.AddString("F3E");
	m_mode.AddString("F1D");
	m_mode.AddString("F2B");
	m_mode.AddString("F2D");
	m_mode.AddString("A2D");
	m_mode.AddString("A3E");
	m_mode.AddString("F1B");
	m_mode.AddString("A1D");
	m_mode.AddString("A2A");
	m_mode.AddString("A2B");
	m_mode.AddString("L4");
	m_mode.AddString("L11");
	m_mode.AddString("Mod. ext.");
	m_mode.AddString("ECCM");

	m_antenne.AddString("0:1/1/1");
	m_antenne.AddString("1:1/2/2");
	m_antenne.AddString("2:1/2/garde");
	m_antenne.AddString("3:1/1/garde");
	m_antenne.AddString("Réservé");
	m_antenne.AddString("Réservé");

	m_pas_em.AddString("0 kHz");
	m_pas_em.AddString("25 kHz");
	m_pas_em.AddString("50 kHz");
	m_pas_em.AddString("75 kHz");

	m_pas_rec.AddString("0 kHz");
	m_pas_rec.AddString("25 kHz");
	m_pas_rec.AddString("50 kHz");
	m_pas_rec.AddString("75 kHz");

	m_relais.AddString("0 / 0 / 0");
	m_relais.AddString("1 / 0 / 0");
	m_relais.AddString("0 / 1 / 0");
	m_relais.AddString("1 / 1 / 0");
	m_relais.AddString("0 / 0 / 1");
	m_relais.AddString("1 / 0 / 1");
	m_relais.AddString("0 / 1 / 1");
	m_relais.AddString("1 / 1 / 1");

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


// Modif des erreurs de communication
// **********************************
void CDlg18C::OnComErreur() 
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

// Verrouillage de la face avant
void CDlg18C::Verrouille(BOOL etat)
{
// Frequence Em
	GetDlgItem(F7_FREQ_EM)->EnableWindow(etat);

// Frequence Rec
	GetDlgItem(F7_FREQ_REC)->EnableWindow(etat);

// Canal
	GetDlgItem(F7_CANAL)->EnableWindow(etat);

// Niveau
	m_niveau.EnableWindow(etat);

// Mode
	m_mode.EnableWindow(etat);

// Bande
	GetDlgItem(F7_WB)->EnableWindow(etat);
	GetDlgItem(F7_NB)->EnableWindow(etat);

// Cle Crypto
	GetDlgItem(F7_CLE_CRYPTO)->EnableWindow(etat);

// Configuration antenne
	m_antenne.EnableWindow(etat);

// Squelch
	GetDlgItem(F7_SQUELCH)->EnableWindow(etat);

// Pas de 25 kHz
	m_pas_em.EnableWindow(etat);
	m_pas_rec.EnableWindow(etat);

// Protection Canal
	GetDlgItem(F7_PROTECTION)->EnableWindow(etat);

// Configuration des relais
	m_relais.EnableWindow(etat);

// Recepteur de garde
	m_rec_garde.EnableWindow(etat);

// Canal de debut de Scan
	GetDlgItem(F7_SCAN_DEB)->EnableWindow(etat);

// Canal de fin de Scan
	GetDlgItem(F7_SCAN_FIN)->EnableWindow(etat);

// Adresse
	GetDlgItem(F7_ADRESSE)->EnableWindow(etat);

// Cle Crypto generale
	GetDlgItem(F7_GENE_CRYPTO)->EnableWindow(etat);

// COde Test
	GetDlgItem(F7_CODE_TEST)->EnableWindow(etat);
}

// OnTimer : Rafraichissement de l'écran de controle **************************
// ****************************************************************************
void CDlg18C::OnTimer(UINT nIDEvent) 
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

	// Verrouille(!((CEquip18C*)equip)->Local());

// Frequence Em
	if(GetDlgItem(F7_FREQ_EM) != GetFocus())
	{
		sprintf(buf,"%d",100*((CEquip18C*)equip)->FrequenceEm(0));
		m_freq_em = buf;
	}

// Frequence Rec
	if(GetDlgItem(F7_FREQ_REC) != GetFocus())
	{
		sprintf(buf,"%d",100*((CEquip18C*)equip)->FrequenceRec(0));
		m_freq_rec = buf;
	}

// Canal
	if(GetDlgItem(F7_CANAL) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip18C*)equip)->Canal());
		m_canal = buf;
	}

// Accord Multicoupleur demandé
	val = !((CEquip18C*)equip)->AccordMulti(0);	// Inverse
	if(m_accord.Retourne_etat()!=val)
		m_accord.Positionne_etat(val);

// Niveau
	val = ((CEquip18C*)equip)->Niveau(0);
	m_niveau.SetCurSel(val);

// Mode
	val = ((CEquip18C*)equip)->Mode(0);
	m_mode.SetCurSel(val);

// Bande
	SendDlgItemMessage(F7_WB,BM_SETCHECK,0,0);
	SendDlgItemMessage(F7_NB,BM_SETCHECK,0,0);
	val = ((CEquip18C*)equip)->Bande(0);
	if(val)
		SendDlgItemMessage(F7_NB,BM_SETCHECK,1,0);
	else
		SendDlgItemMessage(F7_WB,BM_SETCHECK,1,0);

// Cle Crypto
	if(GetDlgItem(F7_CLE_CRYPTO) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip18C*)equip)->CleCrypto(0));
		m_cle_crypto = buf;
	}

// Antenne
	val = ((CEquip18C*)equip)->Antenne(0);
	m_antenne.SetCurSel(val);

// Squelch
	val = ((CEquip18C*)equip)->Squelch(0);
	SendDlgItemMessage(F7_SQUELCH,BM_SETCHECK,val,0);

// Pas de 25 kHz de EM
	val = ((CEquip18C*)equip)->PasEm(0);
	m_pas_em.SetCurSel(val);

// Pas de 25 kHz de REC
	val = ((CEquip18C*)equip)->PasRec(0);
	m_pas_rec.SetCurSel(val);

// Protection
	val = ((CEquip18C*)equip)->Protection(0);
	SendDlgItemMessage(F7_PROTECTION,BM_SETCHECK,val,0);

// Configuration des relais
	val = ((CEquip18C*)equip)->Relais();
	m_relais.SetCurSel(val);

// Recepteur de garde
	val = ((CEquip18C*)equip)->RecGarde();
	if(&m_rec_garde != GetFocus() && m_rec_garde.Retourne_etat()!=val)
		m_rec_garde.Positionne_etat(val);

// Canal de debut de scan
	if(GetDlgItem(F7_SCAN_DEB) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip18C*)equip)->ScanDebut());
		m_scan_deb = buf;
	}

// Canal de fin de scan
	if(GetDlgItem(F7_SCAN_FIN) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip18C*)equip)->ScanFin());
		m_scan_fin = buf;
	}

// Adresse
	if(GetDlgItem(F7_ADRESSE) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip18C*)equip)->Adresse());
		m_adresse = buf;
	}

// Cle Crypto generale
	if(GetDlgItem(F7_GENE_CRYPTO) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip18C*)equip)->GeneCrypto());
		m_gene_crypto = buf;
	}

// Local/Distance
	val = ((CEquip18C*)equip)->Local();
	if(&m_local != GetFocus() && m_local.Retourne_etat()!=val)
		m_local.Positionne_etat(val);

// Accord en cours
	val = ((CEquip18C*)equip)->Accord();
	if(&m_accord_en_cours != GetFocus() && m_accord_en_cours.Retourne_etat()!=val)
		m_accord_en_cours.Positionne_etat(val);

// Panne E/R
	val = ((CEquip18C*)equip)->PanneEmr();
	if(&m_panne_emr != GetFocus() && m_panne_emr.Retourne_etat()!=val)
		m_panne_emr.Positionne_etat(val);

// Panne Accord
	val = ((CEquip18C*)equip)->PanneAccord();
	if(&m_panne_accord != GetFocus() && m_panne_accord.Retourne_etat()!=val)
		m_panne_accord.Positionne_etat(val);

// HF recu
	val = ((CEquip18C*)equip)->HfRecu();
	if(&m_hf != GetFocus() && m_hf.Retourne_etat()!=val)
		m_hf.Positionne_etat(val);

// Ros
	val = ((CEquip18C*)equip)->Ros();
	if(&m_ros != GetFocus() && m_ros.Retourne_etat()!=val)
		m_ros.Positionne_etat(val);

// Emission
	val = ((CEquip18C*)equip)->Emission();
	if(&m_emission != GetFocus() && m_emission.Retourne_etat()!=val)
		m_emission.Positionne_etat(val);

// Silence
	val = ((CEquip18C*)equip)->Silence();
	if(&m_silence != GetFocus() && m_silence.Retourne_etat()!=val)
		m_silence.Positionne_etat(val);

// BF Chiffre
	val = ((CEquip18C*)equip)->Chiffre();
	if(&m_bf != GetFocus() && m_bf.Retourne_etat()!=val)
		m_bf.Positionne_etat(val);

// Scan
	val = ((CEquip18C*)equip)->Scan();
	if(&m_scan != GetFocus() && m_scan.Retourne_etat()!=val)
		m_scan.Positionne_etat(val);


// Code Test
	if(GetDlgItem(F7_CODE_TEST) != GetFocus())
	{
		sprintf(buf,"%d",((CEquip18C*)equip)->Test());
		m_code_test = buf;
	}

// Mise à jour de CEdit
// ********************
	UpdateData(FALSE);

}


void CDlg18C::OnKillfocusFreqEm() 
{
	int		iResult;

	UpdateData(TRUE);
	
	iResult = ((CEquip18C*)equip)->ChangeFrequenceEm(0,atoi(m_freq_em)/100,((CEquip18C*)equip)->Local() != 0);
	if(((CEquip18C*)equip)->Canal() < 95)
		iResult = ((CEquip18C*)equip)->ChangeFrequenceRec(0,atoi(m_freq_em)/100,FALSE);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie

}

void CDlg18C::OnKillfocusFreqRec() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip18C*)equip)->ChangeFrequenceRec(0,atoi(m_freq_rec)/100,((CEquip18C*)equip)->Local() != 0);
	if(((CEquip18C*)equip)->Canal() < 95)
		iResult = ((CEquip18C*)equip)->ChangeFrequenceEm(0,atoi(m_freq_rec)/100,FALSE);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnKillfocusCanal() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip18C*)equip)->ChangeCanal(atoi(m_canal),((CEquip18C*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnSelchangeNiveau() 
{
	int	iResult = ((CEquip18C*)equip)->ChangeNiveau(0,m_niveau.GetCurSel(),((CEquip18C*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnSelchangeMode() 
{
	int	iResult = ((CEquip18C*)equip)->ChangeMode(0,m_mode.GetCurSel(),((CEquip18C*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnNb() 
{
	int	iResult = ((CEquip18C*)equip)->ChangeBande(0,1,((CEquip18C*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnWb() 
{
	int	iResult = ((CEquip18C*)equip)->ChangeBande(0,0,((CEquip18C*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnKillfocusCleCrypto() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip18C*)equip)->ChangeCleCrypto(0,atoi(m_cle_crypto),((CEquip18C*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnSelchangeAntenne() 
{
	int	iResult = ((CEquip18C*)equip)->ChangeAntenne(0,m_antenne.GetCurSel(),((CEquip18C*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnSquelch() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F7_SQUELCH))->GetCheck();
	iResult = ((CEquip18C*)equip)->ChangeSquelch(0,val,((CEquip18C*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnSelchangePasEm() 
{
	int	iResult = ((CEquip18C*)equip)->ChangePasEm(0,m_pas_em.GetCurSel(),((CEquip18C*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnSelchangePasRec() 
{
	int	iResult = ((CEquip18C*)equip)->ChangePasRec(0,m_pas_rec.GetCurSel(),((CEquip18C*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnProtection() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F7_PROTECTION))->GetCheck();
	iResult = ((CEquip18C*)equip)->ChangeProtection(0,val,((CEquip18C*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnSelchangeRelais() 
{
	int	iResult = ((CEquip18C*)equip)->ChangeRelais(m_relais.GetCurSel(),((CEquip18C*)equip)->Local() != 0);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnRecGarde() 
{
	int	iResult = m_rec_garde.Inverse_etat();
 	((CEquip18C*)equip)->ChangeRecGarde(iResult,((CEquip18C*)equip)->Local() != 0);
}

void CDlg18C::OnKillfocusScanDeb() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip18C*)equip)->ChangeScanDebut(atoi(m_scan_deb),((CEquip18C*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnKillfocusScanFin() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip18C*)equip)->ChangeScanFin(atoi(m_scan_fin),((CEquip18C*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnKillfocusAdresse() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip18C*)equip)->ChangeAdresse(atoi(m_adresse),((CEquip18C*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnKillfocusGeneCrypto() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip18C*)equip)->ChangeGeneCrypto(atoi(m_gene_crypto),((CEquip18C*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnLocal() 
{
	int	iResult = m_local.Inverse_etat();
 	((CEquip18C*)equip)->ChangeLocal(iResult,TRUE);
}

void CDlg18C::OnHf() 
{
	int	iResult = m_hf.Inverse_etat();
 	((CEquip18C*)equip)->ChangeHfRecu(iResult,((CEquip18C*)equip)->Local() != 0);
}

void CDlg18C::OnRos() 
{
	int	iResult = m_ros.Inverse_etat();
 	((CEquip18C*)equip)->ChangeRos(iResult,((CEquip18C*)equip)->Local() != 0);
}

void CDlg18C::OnEmission() 
{
	int	iResult = m_emission.Inverse_etat();
 	((CEquip18C*)equip)->ChangeEmission(iResult,((CEquip18C*)equip)->Local() != 0);
}

void CDlg18C::OnSilence() 
{
	int	iResult = m_silence.Inverse_etat();
 	((CEquip18C*)equip)->ChangeSilence(iResult,((CEquip18C*)equip)->Local() != 0);
}

void CDlg18C::OnBf() 
{
	int	iResult = m_bf.Inverse_etat();
 	((CEquip18C*)equip)->ChangeChiffre(iResult,((CEquip18C*)equip)->Local() != 0);
}

void CDlg18C::OnScan() 
{
	int	iResult = m_scan.Inverse_etat();
 	((CEquip18C*)equip)->ChangeScan(iResult,((CEquip18C*)equip)->Local() != 0);
}

void CDlg18C::OnKillfocusCodeTest()
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquip18C*)equip)->ChangeTest(atoi(m_code_test),((CEquip18C*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnMemoCanal() 
{
	int		iResult;

	int		num_canal = ((CEquip18C*)equip)->Canal();

	iResult = ((CEquip18C*)equip)->MemoriseCanal(num_canal,((CEquip18C*)equip)->Local() != 0);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlg18C::OnPanneAccord() 
{
	int	iResult = m_panne_accord.Inverse_etat();
 	((CEquip18C*)equip)->ChangePanneAccord(iResult,TRUE);
}

void CDlg18C::OnPanneEmr() 
{
	int	iResult = m_panne_emr.Inverse_etat();
 	((CEquip18C*)equip)->ChangePanneEmr(iResult,TRUE);
}

void CDlg18C::OnAccordEnCours() 
{
	int	iResult = m_accord_en_cours.Inverse_etat();
 	((CEquip18C*)equip)->ChangeAccord(iResult,TRUE);
}
