/* **************************************************************************
FICHIER :	DlgStdHF.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgStandHF
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "DlgStdHF.h"
#include "Equip\EqpStd.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_STANDHF[];

CDlgStandHF::CDlgStandHF(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDlgStandHF::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgStandHF)
	m_err_retard = _T("");
	m_avarie = _T("");
	m_periode = _T("");
	m_tempo = _T("");
	//}}AFX_DATA_INIT
}


void CDlgStandHF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgStandHF)
	DDX_Control(pDX, IDC_MES_STATUT, m_liste_message);
	DDX_Control(pDX, IDC_CHECK_SYNCHRO, m_synchro);
	DDX_Control(pDX, IDC_CHECK_CYCLE, m_cycle);
	DDX_Text(pDX, IDC_RETARD, m_err_retard);
	DDX_Text(pDX, F5_AVARIE, m_avarie);
	DDX_Text(pDX, IDC_EDIT_CYCLE, m_periode);
	DDX_Text(pDX, IDC_EDIT_TEMPO, m_tempo);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgStandHF, CDialog)
	//{{AFX_MSG_MAP(CDlgStandHF)
	ON_WM_TIMER()
	ON_BN_CLICKED(F5_ABSENCE, OnAbsence)
	ON_BN_CLICKED(F5_ACCORD, OnAccord)
	ON_EN_KILLFOCUS(F5_AVARIE, OnKillfocusAvarie)
	ON_BN_CLICKED(F5_BAA1, OnBaa1)
	ON_BN_CLICKED(F5_BAA2, OnBaa2)
	ON_BN_CLICKED(F5_EM1, OnEm1)
	ON_BN_CLICKED(F5_EM2, OnEm2)
	ON_BN_CLICKED(F5_ETAT, OnEtat)
	ON_BN_CLICKED(F5_HISSAGE, OnHissage)
	ON_BN_CLICKED(F5_NO_XMIT, OnNoXmit)
	ON_BN_CLICKED(F5_REC1, OnRec1)
	ON_BN_CLICKED(F5_REC2, OnRec2)
	ON_BN_CLICKED(F5_RLB, OnRlb)
	ON_BN_CLICKED(F5_SILENCE, OnSilence)
	ON_BN_CLICKED(IDC_CDE_INCONUE, OnComErreur)
	ON_BN_CLICKED(IDC_DEBUT_TRAME, OnComErreur)
	ON_EN_KILLFOCUS(IDC_RETARD, OnComErreur)
	ON_BN_CLICKED(IDC_PAS_REPONSE, OnComErreur)
	ON_BN_CLICKED(F5_DISTANCE, OnDistance)
	ON_BN_CLICKED(F5_LOCAL, OnLocal)
	ON_BN_CLICKED(F5_MAT_1, OnMat1)
	ON_BN_CLICKED(F5_MAT_2, OnMat2)
	ON_BN_CLICKED(F5_TEMP, OnTemp)
	ON_BN_CLICKED(F5_XMIT_1, OnXmit1)
	ON_BN_CLICKED(F5_XMIT_2, OnXmit2)
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
// CDlgStandHF message handlers

void CDlgStandHF::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_STANDHF,"Standard Antenne HF");
	if(iResult >=  0) win.DoModal();
}

BOOL CDlgStandHF::OnInitDialog() 
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
	m_liste_message.AddString("Auto test");
	m_liste_message.AddString("Commutation");
	m_liste_message.AddString("Silence radio");
	m_liste_message.AddString("Avaries relais");
	m_liste_message.AddString("Absence +28 V");
	m_liste_message.AddString("Mât non hissé");
	m_liste_message.AddString("No Xmit");
	m_liste_message.AddString("Defaut temperature");
	m_liste_message.AddString("Local/distant");
	m_liste_message.AddString("Xmit antenne 1");
	m_liste_message.AddString("Xmit antenne 2");
	m_liste_message.AddString("Mat hissé antenne 1");
	m_liste_message.AddString("Mat hissé antenne 2");


// Custom control
// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);	
	m_incorrect.SubclassDlgItem(F5_ETAT,this);	
	m_silence.SubclassDlgItem(F5_SILENCE,this);	

	m_xmit_1.SubclassDlgItem(F5_XMIT_1,this);	
	m_mat_1.SubclassDlgItem(F5_MAT_1,this);	

	m_xmit_2.SubclassDlgItem(F5_XMIT_2,this);	
	m_mat_2.SubclassDlgItem(F5_MAT_2,this);	

// Initialisation de la face avant
// *******************************

	UpdateData(FALSE);
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgStandHF::OnTimer(UINT nIDEvent) 
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

// Etat incorrect du systeme
	val = ((CEquipStd*)equip)->EtatIncorrect();
	if(m_incorrect.Retourne_etat() != val)
		m_incorrect.Positionne_etat(val);

// SilenceRadio
	val = ((CEquipStd*)equip)->SilenceRadio();
	if(m_silence.Retourne_etat() != val)
		m_silence.Positionne_etat(val);


// Selcetion BAA
	SendDlgItemMessage(F5_BAA1,BM_SETCHECK,0,0);
	SendDlgItemMessage(F5_BAA2,BM_SETCHECK,0,0);
	val = ((CEquipStd*)equip)->Baa();
	if(val==1)
		SendDlgItemMessage(F5_BAA1,BM_SETCHECK,1,0);
	else
		SendDlgItemMessage(F5_BAA2,BM_SETCHECK,1,0);

// Selcetion Emet
	SendDlgItemMessage(F5_EM1,BM_SETCHECK,0,0);
	SendDlgItemMessage(F5_EM2,BM_SETCHECK,0,0);
	val = ((CEquipStd*)equip)->Emet();
	if(val==1)
		SendDlgItemMessage(F5_EM1,BM_SETCHECK,1,0);
	else
		SendDlgItemMessage(F5_EM2,BM_SETCHECK,1,0);

// Selection Recep
	SendDlgItemMessage(F5_REC1,BM_SETCHECK,0,0);
	SendDlgItemMessage(F5_REC2,BM_SETCHECK,0,0);
	val = ((CEquipStd*)equip)->Recep();
	if(val==1)
		SendDlgItemMessage(F5_REC1,BM_SETCHECK,1,0);
	else
		SendDlgItemMessage(F5_REC2,BM_SETCHECK,1,0);

// Reception accordée
	SendDlgItemMessage(F5_ACCORD,BM_SETCHECK,0,0);
	SendDlgItemMessage(F5_RLB,BM_SETCHECK,0,0);
	val = ((CEquipStd*)equip)->Accorde();
	if(val)
		SendDlgItemMessage(F5_ACCORD,BM_SETCHECK,1,0);
	else
		SendDlgItemMessage(F5_RLB,BM_SETCHECK,1,0);

// Avarie
	if(GetDlgItem(F5_AVARIE) != GetFocus())
	{
		sprintf(buf,"%d",((CEquipStd*)equip)->Avarie());
		m_avarie = buf;
	}

// Absence Tension
	val = ((CEquipStd*)equip)->AbsenceTension();
	SendDlgItemMessage(F5_ABSENCE,BM_SETCHECK,val,0);

// Mat non hisse
	val = ((CEquipStd*)equip)->NonHissage();
	SendDlgItemMessage(F5_HISSAGE,BM_SETCHECK,val,0);

// No Xmit
	val = ((CEquipStd*)equip)->NoXmit();
	SendDlgItemMessage(F5_NO_XMIT,BM_SETCHECK,val,0);

// Local distance
	SendDlgItemMessage(F5_LOCAL,BM_SETCHECK,0,0);
	SendDlgItemMessage(F5_DISTANCE,BM_SETCHECK,0,0);
	val = ((CEquipStd*)equip)->Local();
	if(val==1)
		SendDlgItemMessage(F5_DISTANCE,BM_SETCHECK,1,0);
	else
		SendDlgItemMessage(F5_LOCAL,BM_SETCHECK,1,0);

// Etat Xmit 1
	val = ((CEquipStd*)equip)->Xmit_1();
	if(m_xmit_1.Retourne_etat() != val)
		m_xmit_1.Positionne_etat(val);

// Etat Xmit 2
	val = ((CEquipStd*)equip)->Xmit_2();
	if(m_xmit_2.Retourne_etat() != val)
		m_xmit_2.Positionne_etat(val);

// Etat mat 1
	val = ((CEquipStd*)equip)->Mat_1();
	if(m_mat_1.Retourne_etat() != val)
		m_mat_1.Positionne_etat(val);

// Etat Xmit 2
	val = ((CEquipStd*)equip)->Mat_2();
	if(m_mat_2.Retourne_etat() != val)
		m_mat_2.Positionne_etat(val);

// Defaut temperature
	val = ((CEquipStd*)equip)->Temperature();
	SendDlgItemMessage(F5_TEMP,BM_SETCHECK,val,0);

// Mise à jour de CEdit
// ********************
	UpdateData(FALSE);
}

void CDlgStandHF::OnAbsence() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F5_ABSENCE))->GetCheck();
	iResult = ((CEquipStd*)equip)->ChangeAbsenceTension(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnAccord() 
{
	int	iResult = ((CEquipStd*)equip)->ChangeAccorde(1,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnRlb() 
{
	int	iResult = ((CEquipStd*)equip)->ChangeAccorde(0,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnKillfocusAvarie() 
{
	int		iResult;

	UpdateData(TRUE);
	iResult = ((CEquipStd*)equip)->ChangeAvarie(atoi(m_avarie),TRUE);
//	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnBaa1() 
{
	int	iResult = ((CEquipStd*)equip)->ChangeBaa(1,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnBaa2() 
{
	int	iResult = ((CEquipStd*)equip)->ChangeBaa(2,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnEm1() 
{
	int	iResult = ((CEquipStd*)equip)->ChangeEmet(1,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnEm2() 
{
	int	iResult = ((CEquipStd*)equip)->ChangeEmet(2,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnEtat() 
{
	int	iResult = m_incorrect.Inverse_etat();
 	((CEquipStd*)equip)->ChangeEtatIncorrect(iResult,TRUE);
}

void CDlgStandHF::OnHissage() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F5_HISSAGE))->GetCheck();
	iResult = ((CEquipStd*)equip)->ChangeNonHissage(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnNoXmit() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F5_NO_XMIT))->GetCheck();
	iResult = ((CEquipStd*)equip)->ChangeNoXmit(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnRec1() 
{
	int	iResult = ((CEquipStd*)equip)->ChangeRecep(1,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnRec2() 
{
	int	iResult = ((CEquipStd*)equip)->ChangeRecep(2,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnSilence() 
{
	int	iResult = m_silence.Inverse_etat();
 	((CEquipStd*)equip)->ChangeSilenceRadio(iResult,TRUE);
}

void CDlgStandHF::OnComErreur() 
{
	t_ComErreur	err;
	
	CButton		*m_debut = (CButton*)GetDlgItem(IDC_DEBUT_TRAME);
//	CButton		*m_fin = (CButton*)GetDlgItem(IDC_FIN_TRAME);
//	CButton		*m_parite = (CButton*)GetDlgItem(IDC_PARITE);
	CButton		*m_inconnue = (CButton*)GetDlgItem(IDC_CDE_INCONUE);
	CButton		*m_reponse = (CButton*)GetDlgItem(IDC_PAS_REPONSE);

	err.pas_debut		= m_debut->GetCheck();
	err.pas_fin			= 0;
	err.controle_parite	= 0;
	err.cde_inconnue	= m_inconnue->GetCheck();
	err.pas_de_reponse	= m_reponse->GetCheck();

	UpdateData(TRUE);
	err.retard = atoi(m_err_retard);

	equip->ChangeComErreur(err);
}

void CDlgStandHF::OnDistance() 
{
	int	iResult = ((CEquipStd*)equip)->ChangeLocal(1,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnLocal() 
{
	int	iResult = ((CEquipStd*)equip)->ChangeLocal(0,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnMat1() 
{
	int	iResult = m_mat_1.Inverse_etat();
 	((CEquipStd*)equip)->ChangeMat_1(iResult,TRUE);
}

void CDlgStandHF::OnMat2() 
{
	int	iResult = m_mat_2.Inverse_etat();
 	((CEquipStd*)equip)->ChangeMat_2(iResult,TRUE);
}

void CDlgStandHF::OnTemp() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F5_TEMP))->GetCheck();
	iResult = ((CEquipStd*)equip)->ChangeTemperature(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgStandHF::OnXmit1() 
{
	int	iResult = m_xmit_1.Inverse_etat();
 	((CEquipStd*)equip)->ChangeXmit_1(iResult,TRUE);
}

void CDlgStandHF::OnXmit2() 
{
	int	iResult = m_xmit_2.Inverse_etat();
 	((CEquipStd*)equip)->ChangeXmit_2(iResult,TRUE);
}
