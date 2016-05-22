/* **********************************************************************
FICHIER :	DlgAccor.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgAccord
***********************************************************************	*/
#include "stdafx.h"
#include "sicomex.h"

#include "divers\div_tmp.h"
#include "DlgAccor.h"
#include "Equip\EqpAcco.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_ACCORD[];

CDlgAccord::CDlgAccord(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDlgAccord::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAccord)
	m_alarme = _T("");
	m_capacite = _T("");
	m_frequence = _T("");
	m_inductance = _T("");
	m_tos = _T("");
	m_periode = _T("");
	m_tempo = _T("");
	m_err_retard = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAccord::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAccord)
	DDX_Control(pDX, F2_ETAT, m_etat);
	DDX_Control(pDX, F2_ACCORD, m_accord);
	DDX_Control(pDX, F2_OPERATION, m_operation);
	DDX_Control(pDX, F2_SELECTE_ALARME, m_selecte_alarme);
	DDX_Control(pDX, IDC_MES_STATUT, m_liste_message);
	DDX_Control(pDX, IDC_CHECK_SYNCHRO, m_synchro);
	DDX_Control(pDX, IDC_CHECK_CYCLE, m_cycle);
	DDX_Control(pDX, IDC_JOURNAL, m_journal);
	DDX_Text(pDX, F2_ALARME, m_alarme);
	DDX_Text(pDX, F2_CAPACITE, m_capacite);
	DDX_Text(pDX, F2_FREQUENCE, m_frequence);
	DDX_Text(pDX, F2_INDUCTANCE, m_inductance);
	DDX_Text(pDX, F2_TOS, m_tos);
	DDX_Text(pDX, IDC_EDIT_CYCLE, m_periode);
	DDX_Text(pDX, IDC_EDIT_TEMPO, m_tempo);
	DDX_Text(pDX, IDC_RETARD, m_err_retard);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAccord, CDialog)
	//{{AFX_MSG_MAP(CDlgAccord)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CDE_INCONUE, OnComErreur)
	ON_CBN_SELCHANGE(F2_SELECTE_ALARME, OnSelchangeSelecteAlarme)
	ON_EN_KILLFOCUS(F2_ALARME, OnKillfocusAlarme)
	ON_BN_CLICKED(F2_MANUEL, OnManuel)
	ON_EN_KILLFOCUS(F2_FREQUENCE, OnKillfocusFrequence)
	ON_CBN_SELCHANGE(F2_OPERATION, OnSelchangeOperation)
	ON_BN_CLICKED(F2_NO_XMIT, OnNoXmit)
	ON_CBN_SELCHANGE(F2_ACCORD, OnSelchangeAccord)
	ON_EN_KILLFOCUS(F2_CAPACITE, OnKillfocusCapacite)
	ON_EN_KILLFOCUS(F2_INDUCTANCE, OnKillfocusInductance)
	ON_EN_KILLFOCUS(F2_TOS, OnKillfocusTos)
	ON_BN_CLICKED(F2_AUTO_CAPA, OnAutoCapa)
	ON_BN_CLICKED(F2_AUTO_INDUC, OnAutoInduc)
	ON_BN_CLICKED(F2_AUTO_TOS, OnAutoTos)
	ON_CBN_SELCHANGE(F2_ETAT, OnSelchangeEtat)
	ON_BN_CLICKED(F2_INDETERMINE, OnIndetermine)
	ON_BN_CLICKED(F2_ACCORDE, OnAccorde)
	ON_BN_CLICKED(F2_LARGE_BANDE, OnLargeBande)
	ON_BN_CLICKED(IDC_DEBUT_TRAME, OnComErreur)
	ON_BN_CLICKED(IDC_FIN_TRAME, OnComErreur)
	ON_BN_CLICKED(IDC_PARITE, OnComErreur)
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


void CDlgAccord::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_ACCORD,"Boite d'accord antenne");
	if(iResult >=  0) win.DoModal();
}

BOOL CDlgAccord::OnInitDialog() 
{
	t_ComErreur	err;
	int		i;
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
	m_liste_message.AddString("Etat Alarme");
	
// Custom control
// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);	
	m_manuel.SubclassDlgItem(F2_MANUEL,this);	

	m_no_xmit.SubclassDlgItem(F2_NO_XMIT,this);	

	m_ros.SubclassDlgItem(F2_ROS,this);
	m_tun.SubclassDlgItem(F2_TUN,this);
	m_tmp.SubclassDlgItem(F2_TEMP,this);
	m_impedance.SubclassDlgItem(F2_IMPEDANCE,this);
	
 // Initialisation de la face avant
// *******************************
	m_operation.AddString("IDLE");
	m_operation.AddString("TUNING");
	m_operation.AddString("M_SELFTEST");
	m_operation.AddString("M_AUTOTUNING");

	m_accord.AddString("Pas accordée");
	m_accord.AddString("Accord préréglage");
	m_accord.AddString("Accord fin");
	m_accord.AddString("Accord inconnue");

	m_etat.AddString("U");
	m_etat.AddString("E10");
	m_etat.AddString("R3");
	m_etat.AddString("S");
	m_etat.AddString("P");
	m_etat.AddString("F");
	m_etat.AddString("X");
	m_etat.AddString("Y");

	for(i=0 ; i<100 ; i++)
	{
		sprintf(buf,"%2.2d",i);
		m_selecte_alarme.AddString(buf);
	}

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}



// GenrateurAuto():	Effectue les variation automatique de certains paramètres
void CDlgAccord::GenerateurAuto()
{
	srand( (unsigned)time( NULL ) );

	if(((CEquipAccord*)equip)->AutoCapa())
		((CEquipAccord*)equip)->ChangeCapacite(rand()%256,FALSE);

	if(((CEquipAccord*)equip)->AutoInduc())
		((CEquipAccord*)equip)->ChangeInductance(rand()%512,FALSE);

	if(((CEquipAccord*)equip)->AutoTos())
		((CEquipAccord*)equip)->ChangeTos(10+(rand()%81),FALSE);

}

void CDlgAccord::OnTimer(UINT nIDEvent) 
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

// Mode Manuel
	val = ((CEquipAccord*)equip)->Manuel();
	if(m_manuel.Retourne_etat() != val)
		m_manuel.Positionne_etat(val);

// Code Alarme
	val = ((CEquipAccord*)equip)->SelecteAlarme();
	m_selecte_alarme.SetCurSel(val);

	if(GetDlgItem(F2_SELECTE_ALARME) != GetFocus())
	{
		sprintf(buf,"%d",((CEquipAccord*)equip)->Alarme(m_selecte_alarme.GetCurSel()));
		m_alarme = buf;
	}

// Ros
	val = ((CEquipAccord*)equip)->Alarme(ALARME_ROS);
	if(m_ros.Retourne_etat() != val)
		m_ros.Positionne_etat(val);

// Tun
	val = ((CEquipAccord*)equip)->Alarme(ALARME_TUN);
	if(m_tun.Retourne_etat() != val)
		m_tun.Positionne_etat(val);

// Temp
	val = ((CEquipAccord*)equip)->Alarme(ALARME_TMP);
	if(m_tmp.Retourne_etat() != val)
		m_tmp.Positionne_etat(val);

// Mode de fonctionnement
	SendDlgItemMessage(F2_INDETERMINE,BM_SETCHECK,0,0);
	SendDlgItemMessage(F2_ACCORDE,BM_SETCHECK,0,0);
	SendDlgItemMessage(F2_LARGE_BANDE,BM_SETCHECK,0,0);
	val = ((CEquipAccord*)equip)->Mode();
	switch(val)
	{
		case 0:
			SendDlgItemMessage(F2_ACCORDE,BM_SETCHECK,1,0);
			break;
		case 1:
			SendDlgItemMessage(F2_LARGE_BANDE,BM_SETCHECK,1,0);
			break;
		default:
			SendDlgItemMessage(F2_INDETERMINE,BM_SETCHECK,1,0);
			break;
	}

// Frequence
	if(GetDlgItem(F2_FREQUENCE) != GetFocus())
	{
		sprintf(buf,"%d",((CEquipAccord*)equip)->Frequence());
		m_frequence = buf;
	}

// Operation
	val = ((CEquipAccord*)equip)->Operation();
	m_operation.SetCurSel(val);

// NoXmit
	val = ((CEquipAccord*)equip)->NoXmit();
	if(m_no_xmit.Retourne_etat() != val)
		m_no_xmit.Positionne_etat(val);

// Accord
	val = ((CEquipAccord*)equip)->Accord();
	m_accord.SetCurSel(val);

// Capacite
	if(GetDlgItem(F2_CAPACITE) != GetFocus())
	{
		sprintf(buf,"%d",((CEquipAccord*)equip)->Capacite());
		m_capacite = buf;
	}

// Inductance
	if(GetDlgItem(F2_INDUCTANCE) != GetFocus())
	{
		sprintf(buf,"%d",((CEquipAccord*)equip)->Inductance());
		m_inductance = buf;
	}

// Tos
	if(GetDlgItem(F2_TOS) != GetFocus())
	{
		sprintf(buf,"%d",((CEquipAccord*)equip)->Tos());
		m_tos = buf;
	}

// Auto Capa
	val = ((CEquipAccord*)equip)->AutoCapa();
	SendDlgItemMessage(F2_AUTO_CAPA,BM_SETCHECK,val,0);

// Auto Inductance
	val = ((CEquipAccord*)equip)->AutoInduc();
	SendDlgItemMessage(F2_AUTO_INDUC,BM_SETCHECK,val,0);

// Auto Tos
	val = ((CEquipAccord*)equip)->AutoTos();
	SendDlgItemMessage(F2_AUTO_TOS,BM_SETCHECK,val,0);

// Etat de commande TUN
	val = ((CEquipAccord*)equip)->Etat();
	m_etat.SetCurSel(val);

	UpdateData(FALSE);
}

void CDlgAccord::OnComErreur() 
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

void CDlgAccord::OnSelchangeSelecteAlarme() 
{
	char	buf[8];
	int	iResult = ((CEquipAccord*)equip)->ChangeSelecteAlarme(m_selecte_alarme.GetCurSel(),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie

	sprintf(buf,"%d",((CEquipAccord*)equip)->Alarme(iResult));
	m_alarme = buf;
	UpdateData(FALSE);
}

void CDlgAccord::OnKillfocusAlarme() 
{
	int	iResult = m_selecte_alarme.GetCurSel();

	UpdateData(TRUE);

	((CEquipAccord*)equip)->ChangeAlarme(iResult,atoi(m_alarme),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnManuel() 
{
	int	iResult = m_manuel.Inverse_etat();
 	((CEquipAccord*)equip)->ChangeManuel(iResult,TRUE);
}

void CDlgAccord::OnKillfocusFrequence() 
{
	UpdateData(TRUE);

	int iResult = ((CEquipAccord*)equip)->ChangeFrequence(atoi(m_frequence),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnSelchangeOperation() 
{
	int	iResult = ((CEquipAccord*)equip)->ChangeOperation(m_operation.GetCurSel(),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnNoXmit() 
{
	int	iResult = m_no_xmit.Inverse_etat();
 	((CEquipAccord*)equip)->ChangeNoXmit(iResult,TRUE);
}

void CDlgAccord::OnSelchangeAccord() 
{
	int	iResult = ((CEquipAccord*)equip)->ChangeAccord(m_accord.GetCurSel(),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnKillfocusCapacite() 
{
	UpdateData(TRUE);

	int iResult = ((CEquipAccord*)equip)->ChangeCapacite(atoi(m_capacite),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnKillfocusInductance() 
{
	UpdateData(TRUE);

	int iResult = ((CEquipAccord*)equip)->ChangeInductance(atoi(m_inductance),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnKillfocusTos() 
{
	UpdateData(TRUE);

	int iResult = ((CEquipAccord*)equip)->ChangeTos(atoi(m_tos),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnAutoCapa() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F2_AUTO_CAPA))->GetCheck();
	iResult = ((CEquipAccord*)equip)->ChangeAutoCapa(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnAutoInduc() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F2_AUTO_INDUC))->GetCheck();
	iResult = ((CEquipAccord*)equip)->ChangeAutoInduc(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnAutoTos() 
{
	int		iResult;

	int		val=((CButton*)GetDlgItem(F2_AUTO_TOS))->GetCheck();
	iResult = ((CEquipAccord*)equip)->ChangeAutoTos(val,TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnSelchangeEtat() 
{
	int	iResult = ((CEquipAccord*)equip)->ChangeEtat(m_etat.GetCurSel(),TRUE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnIndetermine() 
{
	int	iResult = ((CEquipAccord*)equip)->ChangeMode(2,FALSE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnAccorde() 
{
	int	iResult = ((CEquipAccord*)equip)->ChangeMode(0,FALSE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}

void CDlgAccord::OnLargeBande() 
{
	int	iResult = ((CEquipAccord*)equip)->ChangeMode(1,FALSE);
	if(iResult<0);	// L'ancienne valeur sera rafraichie
}
