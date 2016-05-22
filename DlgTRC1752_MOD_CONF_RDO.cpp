// DlgTRC1752_MOD_CONF_RDO.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_CONF_RDO.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_RDO dialog


CDlgTRC1752_MOD_CONF_RDO::CDlgTRC1752_MOD_CONF_RDO(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_CONF_RDO::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_CONF_RDO)
	m_MarcheRecepteur = TRUE;
	m_MarcheEmetteur = TRUE;
	m_PanneTcE = FALSE;
	m_PanneTcR = FALSE;
	m_PanneMajeureE = FALSE;
	m_PanneMajeureR = FALSE;
	m_NiveauBfReception = -30;
	m_NiveauQualite = 31;
	m_NiveauBfReceptionEsclave = -30;
	m_Doppler = 0;
	m_EmetteurEmission = FALSE;
	m_recMil = FALSE;
	//}}AFX_DATA_INIT

	this->eqp = equip;
	inr_run = FALSE;
}


void CDlgTRC1752_MOD_CONF_RDO::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_CONF_RDO)
	DDX_Control(pDX, IDC_REC_MIL, m_RecMil);
	DDX_Control(pDX, IDC_BUTTON_ALE_MSG, m_Alt_Msg);
	DDX_Control(pDX, IDC_NIVEAU_QUALITE, c_NiveauQualite);
	DDX_Control(pDX, IDC_NIV_BF_REC_S, c_NiveauBfReceptionEsclave);
	DDX_Control(pDX, IDC_DOPPLER, c_Doppler);
	DDX_Control(pDX, IDC_NIV_BF_REC, c_NiveauBfReception);
	DDX_Control(pDX, IDC_COMBO_ALE_VOIE, c_Ale_Voie);
	DDX_Control(pDX, IDC_CONF_VOIE_MAITRE, c_VoieMaitre);
	DDX_Control(pDX, IDC_CONF_VOIE_ESCLAVE, c_VoieEsclave);
	DDX_Control(pDX, IDC_DOPPLER_SPIN, s_Doppler);
	DDX_Control(pDX, IDC_NIV_BF_REC_S_SPIN, s_NiveauBfReceptionEsclave);
	DDX_Control(pDX, IDC_NIVEUA_QUALITE_SPIN, s_NiveauQualite);
	DDX_Control(pDX, IDC_NIV_BF_REC_SPIN, s_NiveauBfReception);
	DDX_Check(pDX, IDC_AM_R, m_MarcheRecepteur);
	DDX_Check(pDX, IDC_AM_E, m_MarcheEmetteur);
	DDX_Check(pDX, IDC_PANNE_TC_E, m_PanneTcE);
	DDX_Check(pDX, IDC_PANNE_TC_R, m_PanneTcR);
	DDX_Check(pDX, IDC_PANNE_MAJ_E, m_PanneMajeureE);
	DDX_Check(pDX, IDC_PANNE_MAJ_R, m_PanneMajeureR);
	DDX_Text(pDX, IDC_NIV_BF_REC, m_NiveauBfReception);
	DDX_Text(pDX, IDC_NIVEAU_QUALITE, m_NiveauQualite);
	DDX_Text(pDX, IDC_NIV_BF_REC_S, m_NiveauBfReceptionEsclave);
	DDX_Text(pDX, IDC_DOPPLER, m_Doppler);
	DDX_Check(pDX, IDC_EMETEUR_EMI, m_EmetteurEmission);
	DDX_Check(pDX, IDC_REC_MIL, m_recMil);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_CONF_RDO, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_CONF_RDO)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_AM_E, OnAmE)
	ON_BN_CLICKED(IDC_AM_R, OnAmR)
	ON_NOTIFY(UDN_DELTAPOS, IDC_NIV_BF_REC_SPIN, OnDeltaposNivBfRecSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_NIVEUA_QUALITE_SPIN, OnDeltaposNiveuaQualiteSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_DOPPLER_SPIN, OnDeltaposDopplerSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_NIV_BF_REC_S_SPIN, OnDeltaposNivBfRecSSpin)
	ON_CBN_SELCHANGE(IDC_CONF_VOIE_MAITRE, OnSelchangeConfVoieMaitre)
	ON_CBN_SELCHANGE(IDC_CONF_VOIE_ESCLAVE, OnSelchangeConfVoieEsclave)
	ON_BN_CLICKED(IDC_PANNE_MAJ_E, OnPanneMajE)
	ON_BN_CLICKED(IDC_PANNE_TC_E, OnPanneTcE)
	ON_BN_CLICKED(IDC_PANNE_MAJ_R, OnPanneMajR)
	ON_BN_CLICKED(IDC_PANNE_TC_R, OnPanneTcR)
	ON_EN_KILLFOCUS(IDC_NIV_BF_REC, OnKillfocusNivBfRec)
	ON_EN_KILLFOCUS(IDC_NIV_BF_REC_S, OnKillfocusNivBfRecS)
	ON_EN_KILLFOCUS(IDC_NIVEAU_QUALITE, OnKillfocusNiveauQualite)
	ON_EN_KILLFOCUS(IDC_DOPPLER, OnKillfocusDoppler)
	ON_BN_CLICKED(IDC_BUTTON_ALE_MSG, OnButtonAleMsg)
	ON_BN_CLICKED(IDC_EMETEUR_EMI, OnEmeteurEmi)
	ON_EN_SETFOCUS(IDC_NIV_BF_REC, OnSetfocusNivBfRec)
	ON_EN_SETFOCUS(IDC_NIVEAU_QUALITE, OnSetfocusNiveauQualite)
	ON_EN_SETFOCUS(IDC_DOPPLER, OnSetfocusDoppler)
	ON_EN_SETFOCUS(IDC_NIV_BF_REC_S, OnSetfocusNivBfRecS)
	ON_CBN_EDITCHANGE(IDC_COMBO_ALE_VOIE, OnEditchangeComboAleVoie)
	ON_CBN_SELCHANGE(IDC_COMBO_ALE_VOIE, OnSelchangeComboAleVoie)
	ON_BN_CLICKED(IDC_REC_MIL, OnRecMil)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_RDO message handlers

BOOL CDlgTRC1752_MOD_CONF_RDO::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetTimer(1,2000,NULL);

	// Initialisation Voie
	c_VoieMaitre.SetCurSel(0);
	c_VoieEsclave.SetCurSel(0);
	c_Ale_Voie.SetCurSel(0);

	pBtnMarcheEmi = (CButton*) GetDlgItem(IDC_AM_E);
	pBtnMarcheRec = (CButton*) GetDlgItem(IDC_AM_R);
	pBtnPanneTcEmi = (CButton*) GetDlgItem(IDC_PANNE_TC_E);
	pBtnPanneMjEmi = (CButton*) GetDlgItem(IDC_PANNE_MAJ_E);
	pBtnPanneTcRec = (CButton*) GetDlgItem(IDC_PANNE_TC_R);
	pBtnPanneMjRec = (CButton*) GetDlgItem(IDC_PANNE_MAJ_R);

	//Changement du sens de variation des Spin

	//Initialisations pour Niveau BF réception
	s_NiveauBfReception.SetRange(NIV_BF_MIN, NIV_BF_MAX);

	//Initialisation Niveau de Qualité
	s_NiveauQualite.SetRange(NIV_QUAL_MIN, NIV_QUAL_MAX);
	m_NiveauQualite = NIV_QUAL_MAX;

	//Initialisations pour Niveau BF réception de la voie Réception
	s_NiveauBfReceptionEsclave.SetRange(NIV_BF_MIN, NIV_BF_MAX);

	//Initialisations l'écart Döppler
	s_Doppler.SetRange(NIV_DOPPLER_MIN, NIV_DOPPLER_MAX);

	LoadData();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTRC1752_MOD_CONF_RDO::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	CString VoieAppel;

	c_Ale_Voie.GetLBText(c_Ale_Voie.GetCurSel(), VoieAppel);

	if (eqp->GetChannelType((LPCTSTR)VoieAppel) != "-")
	{
		GetDlgItem(IDC_BUTTON_ALE_MSG)->ShowWindow(TRUE);
	}
	else
		if (eqp->GetChannelType((LPCTSTR)VoieAppel) == "-")
			GetDlgItem(IDC_BUTTON_ALE_MSG)->ShowWindow(FALSE);


	switch (nIDEvent)
	{
	case 1: // Gestion INR
		if (inr_run == TRUE && eqp->GetInrRate() != inr_rate)
		{
			// Changement de rythme
			inr_rate = eqp->GetInrRate();
			KillTimer(2);
			SetTimer(2,inr_rate*100,NULL);
		}

		if (eqp->GetInr() == "AVEC")
		{
			if (inr_run == FALSE)
			{
				// Lancement
				inr_rate = eqp->GetInrRate();
				inr_run = TRUE;
				SetTimer(2,inr_rate*100,NULL);
			}
		}
		else
		{
			if (inr_run == TRUE)
			{
				// Arret
				KillTimer(2);
				inr_run = FALSE;
			}
		}

		if (eqp->IsModif()) return;

		LoadData();

		break;
	case 2: // Envoi INR
		eqp->SendINR();
		break;
	case 3:
		FinEmissionMsg();
		break;
	default:
		break;
	}

}


/* **************************************************************************
METHODE :		LoadData()
TRAITEMENT:		Charge les données de la vue
***************************************************************************	*/
void CDlgTRC1752_MOD_CONF_RDO::LoadData()
{

	UpdateData(TRUE);

	m_MarcheRecepteur = eqp->IsRecepteurMarche();
	m_MarcheEmetteur = eqp->IsEmetteurMarche();
	m_PanneMajeureE = eqp->IsEmetteurPanneMajeure();
	m_PanneMajeureR = eqp->IsRecepteurPanneMajeure();
	m_PanneTcE = eqp->IsEmetteurPanneTC();
	m_PanneTcR = eqp->IsRecepteurPanneTC();

	AfficheParams(eqp->Actif()!=0);

	// FDI
	OnSelchangeComboAleVoie();

	OnSelchangeConfVoieMaitre();
	OnSelchangeConfVoieEsclave();

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_RDO::OnAmE()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_CONF_RDO::OnAmR()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_CONF_RDO::OnDeltaposNiveuaQualiteSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;

	//Le Niveau Qualité peut prendre les valeurs : 0  à 31.
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_NiveauQualite += 1;
		else       m_NiveauQualite -= 1;


	if ( m_NiveauQualite > NIV_QUAL_MAX )
	{
		AfxMessageBox("Le Niveau Qualité peut prendre les valeurs : 0 à 31");
		m_NiveauQualite = NIV_QUAL_MAX;
	}

	if ( m_NiveauQualite < NIV_QUAL_MIN)
	{
		AfxMessageBox("Le Niveau Qualité peut prendre les valeurs : 0 à 31");
		m_NiveauQualite = NIV_QUAL_MIN;
	}

	// Voie Maitre
	c_VoieMaitre.GetLBText(c_VoieMaitre.GetCurSel(), str);

	// Niveau Qualité
	eqp->SetChannelQualityValue((char *)LPCTSTR(str), m_NiveauQualite);

	UpdateData(FALSE);

	eqp->SetModif(true);

	*pResult = 0;
}

//*****************************
// Mémorisation des paramètres.
//*****************************
void CDlgTRC1752_MOD_CONF_RDO::Valide()
{
	CString str;

	UpdateData(TRUE);

	// Voie Maitre
	c_VoieMaitre.GetLBText(c_VoieMaitre.GetCurSel(), str);

	// Niveau BF
	eqp->SetChannelAfLevelReceived((char *)LPCTSTR(str), m_NiveauBfReception);

	// Niveau Qualité
	eqp->SetChannelQualityValue((char *)LPCTSTR(str), m_NiveauQualite);

	// Doppler
	eqp->SetChannelDopplerOffset((char *)LPCTSTR(str), m_Doppler);

	// Equipements Radio
	if (pBtnMarcheEmi->GetCheck())
		eqp->SetEmetteurMarche(TRUE);
	else
		eqp->SetEmetteurMarche(FALSE);

	if (pBtnMarcheRec->GetCheck())
		eqp->SetRecepteurMarche(TRUE);
	else
		eqp->SetRecepteurMarche(FALSE);

	if (pBtnPanneMjEmi->GetCheck())
		eqp->SetEmetteurPanneMajeure(TRUE);
	else
		eqp->SetEmetteurPanneMajeure(FALSE);

	if (pBtnPanneTcEmi->GetCheck())
		eqp->SetEmetteurPanneTC(TRUE);
	else
		eqp->SetEmetteurPanneTC(FALSE);

	if (pBtnPanneMjRec->GetCheck())
		eqp->SetRecepteurPanneMajeure(TRUE);
	else
		eqp->SetRecepteurPanneMajeure(FALSE);

	if (pBtnPanneTcRec->GetCheck())
		eqp->SetRecepteurPanneTC(TRUE);
	else
		eqp->SetRecepteurPanneTC(FALSE);

	eqp->SetModif(false);

}

void CDlgTRC1752_MOD_CONF_RDO::OnDeltaposDopplerSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_Doppler += 1;
		else       m_Doppler -= 1;


	if ( m_Doppler > NIV_DOPPLER_MAX )
	{
		AfxMessageBox("Le Niveau Doopler peut prendre les valeurs : -250 à 250");
		m_Doppler = NIV_DOPPLER_MAX;
	}

	if ( m_Doppler < NIV_DOPPLER_MIN)
	{
		AfxMessageBox("Le Niveau Doopler peut prendre les valeurs : -250 à 250");
		m_Doppler = NIV_DOPPLER_MIN;
	}

	// Voie Maitre
	c_VoieMaitre.GetLBText(c_VoieMaitre.GetCurSel(), str);

	// Doppler
	eqp->SetChannelDopplerOffset((char *)LPCTSTR(str), m_Doppler);

	UpdateData(FALSE);

	eqp->SetModif(true);

	*pResult = 0;
}

// Niveau BF Esclave
void CDlgTRC1752_MOD_CONF_RDO::OnDeltaposNivBfRecSSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	//Le Niveau BF d’une interface BF peut prendre les valeurs : -30 dBm à +10 dBm

	if (pNMUpDown->iDelta > 0)  m_NiveauBfReceptionEsclave += 1;
		else       m_NiveauBfReceptionEsclave -= 1;


	if ( m_NiveauBfReceptionEsclave > NIV_BF_MAX )
	{
		AfxMessageBox("Le Niveau BF d’une interface BF peut prendre les valeurs : -30 dBm à +10 dBm");
		m_NiveauBfReceptionEsclave = NIV_BF_MAX;
	}

	if ( m_NiveauBfReceptionEsclave < NIV_BF_MIN)
	{
		AfxMessageBox("Le Niveau BF d’une interface BF peut prendre les valeurs : -30 dBm à +10 dBm");
		m_NiveauBfReceptionEsclave = NIV_BF_MIN;
	}

	// Voie Esclave
	c_VoieEsclave.GetLBText(c_VoieEsclave.GetCurSel(), str);

	// Niveau BF
	eqp->SetChannelAfLevelReceivedSlave((char *)LPCTSTR(str), m_NiveauBfReceptionEsclave);

	//récupération le nom de l'esclave  //DI_SLAVE
	eqp->SetNameSlave(str);

	UpdateData(FALSE);

	eqp->SetModif(true);

	*pResult = 0;
}

// Niveau BF Maitre
void CDlgTRC1752_MOD_CONF_RDO::OnDeltaposNivBfRecSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;

	//Le Niveau BF d’une interface BF peut prendre les valeurs : -30 dBm à +10 dBm
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_NiveauBfReception += 1;
		else       m_NiveauBfReception -= 1;


	if ( m_NiveauBfReception > NIV_BF_MAX )
	{
		AfxMessageBox("Le Niveau BF d’une interface BF peut prendre les valeurs : -30 dBm à +10 dBm");
		m_NiveauBfReception = NIV_BF_MAX;
	}

	if ( m_NiveauBfReception < NIV_BF_MIN)
	{
		AfxMessageBox("Le Niveau BF d’une interface BF peut prendre les valeurs : -30 dBm à +10 dBm");
		m_NiveauBfReception = NIV_BF_MIN;
	}

	// Voie Maitre
	c_VoieMaitre.GetLBText(c_VoieMaitre.GetCurSel(), str);

	// Niveau BF
	eqp->SetChannelAfLevelReceived((char *)LPCTSTR(str), m_NiveauBfReception);

	eqp->SetChannelReceptionStatus((char *)LPCTSTR(str), m_NiveauBfReception, pNMUpDown->iDelta);

	UpdateData(FALSE);

	eqp->SetModif(true);

	*pResult = 0;
}

//************************************************************
// Affichage des paramètres, BF, Qualité et Doppler, des Voies
//************************************************************
void CDlgTRC1752_MOD_CONF_RDO::OnSelchangeConfVoieMaitre()
{
	CString str;

	string channelEncours;
	TChannelConfiguration confEnCours;

	// Voie Maitre
	c_VoieMaitre.GetLBText(c_VoieMaitre.GetCurSel(), str);

	m_NiveauBfReception = eqp->GetChannelAfLevelReceived((char *)LPCTSTR(str));
	m_NiveauQualite		= eqp->GetChannelQualityValue((char *)LPCTSTR(str));
	m_Doppler			= eqp->GetChannelDopplerOffset((char *)LPCTSTR(str));

	eqp->SetRecMil(false);

	// Lecture du canal associé à la voie
	channelEncours = eqp->GetChannelAssociatedAfConfiguration((char *)LPCTSTR(str));
	// Lecture de la configuration de la voie
	confEnCours = eqp->GetChannelConfiguration(channelEncours);
	// Si le waveform est MIL110 on affiche la case à cochée
	if (confEnCours.waveform == "MIL110" )
		m_RecMil.EnableWindow(true);
	else
		m_RecMil.EnableWindow(false);


	// Voie Esclave
	c_VoieEsclave.GetLBText(c_VoieEsclave.GetCurSel(), str);
	m_NiveauBfReceptionEsclave = eqp->GetChannelAfLevelReceivedSlave((char *)LPCTSTR(str));

	UpdateData(FALSE);

}

void CDlgTRC1752_MOD_CONF_RDO::OnSelchangeConfVoieEsclave()
{
	CString str;

	//Voie Esclave
	c_VoieEsclave.GetLBText(c_VoieEsclave.GetCurSel(), str);

	//récupération le nom de l'esclave  //DI_SLAVE
	eqp->SetNameSlave(str);

	m_NiveauBfReceptionEsclave = eqp->GetChannelAfLevelReceivedSlave((char *)LPCTSTR(str));

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_RDO::OnPanneMajE()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_CONF_RDO::OnPanneTcE()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_CONF_RDO::OnPanneMajR()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_CONF_RDO::OnPanneTcR()
{
	eqp->SetModif(true);
}

//**************************************************
// Gestion de m_NiveauBfReception sur focus
//**************************************************
void CDlgTRC1752_MOD_CONF_RDO::OnKillfocusNivBfRec()
{
	// FFT ADEL_97206
	/*
	if (eqp->Actif() == FALSE ) return;

	CString str, VoieEnCours;

	// Voie Maitre
	c_VoieMaitre.GetLBText(c_VoieMaitre.GetCurSel(), VoieEnCours);

	GetDlgItem(IDC_NIV_BF_REC)->GetWindowText(str);

	m_NiveauBfReception = atoi((char*)LPCTSTR(str));

	// Test sur le m_NiveauBfReception
	if ( m_NiveauBfReception > NIV_BF_MAX )
	{
		AfxMessageBox("Le Niveau BF d’une interface BF peut prendre les valeurs : -30 dBm à +10 dBm");
		m_NiveauBfReception = NIV_BF_MAX;
	}

	if ( m_NiveauBfReception < NIV_BF_MIN)
	{
		AfxMessageBox("Le Niveau BF d’une interface BF peut prendre les valeurs : -30 dBm à +10 dBm");
		m_NiveauBfReception = NIV_BF_MIN;
	}

	eqp->SetChannelAfLevelReceived((char *)LPCTSTR(VoieEnCours), m_NiveauBfReception);

	UpdateData(FALSE);

	eqp->SetModif(true);
	*/
}

//**************************************************
// Gestion de m_NiveauBfReceptionEsclave sur focus
//**************************************************
void CDlgTRC1752_MOD_CONF_RDO::OnKillfocusNivBfRecS()
{
	// FFT ADEL_97206

	/*
	if (eqp->Actif() == FALSE ) return;

	CString str, VoieEnCours;

	// Voie Esclave
	c_VoieEsclave.GetLBText(c_VoieEsclave.GetCurSel(), VoieEnCours);

	GetDlgItem(IDC_NIV_BF_REC_S)->GetWindowText(str);

	m_NiveauBfReceptionEsclave = atoi((char*)LPCTSTR(str));

	if ( m_NiveauBfReceptionEsclave > NIV_BF_MAX )
	{
		AfxMessageBox("Le Niveau BF d’une interface BF peut prendre les valeurs : -30 dBm à +10 dBm");
		m_NiveauBfReceptionEsclave = NIV_BF_MAX;
	}

	if ( m_NiveauBfReceptionEsclave < NIV_BF_MIN)
	{
		AfxMessageBox("Le Niveau BF d’une interface BF peut prendre les valeurs : -30 dBm à +10 dBm");
		m_NiveauBfReceptionEsclave = NIV_BF_MIN;
	}

	// Niveau BF
	eqp->SetChannelAfLevelReceivedSlave((char *)LPCTSTR(VoieEnCours), m_NiveauBfReceptionEsclave);

	//récupération le nom de l'esclave  //DI_SLAVE
	eqp->SetNameSlave(VoieEnCours);


	UpdateData(FALSE);

	eqp->SetModif(true);
	*/
}

//**************************************************
// Gestion de m_NiveauQualite sur focus
//**************************************************
void CDlgTRC1752_MOD_CONF_RDO::OnKillfocusNiveauQualite()
{
	if (eqp->Actif() == FALSE ) return;

	CString str, VoieEnCours;

	// Voie Maitre
	c_VoieMaitre.GetLBText(c_VoieMaitre.GetCurSel(), VoieEnCours);

	GetDlgItem(IDC_NIVEAU_QUALITE)->GetWindowText(str);

	m_NiveauQualite = atoi((char*)LPCTSTR(str));

	// Test sur le m_NiveauQualite
	if ( m_NiveauQualite > NIV_QUAL_MAX )
	{
		AfxMessageBox("Le Niveau Qualité peut prendre les valeurs : 0 à 31");
		m_NiveauQualite = NIV_QUAL_MAX;
	}

	if ( m_NiveauQualite < NIV_QUAL_MIN)
	{
		AfxMessageBox("Le Niveau Qualité peut prendre les valeurs : 0 à 31");
		m_NiveauQualite = NIV_QUAL_MIN;
	}


	// Niveau Qualité
	eqp->SetChannelQualityValue((char *)LPCTSTR(VoieEnCours), m_NiveauQualite);


	UpdateData(FALSE);

	eqp->SetModif(true);
}

//**************************************************
// Gestion de m_Doppler sur focus
//**************************************************
void CDlgTRC1752_MOD_CONF_RDO::OnKillfocusDoppler()
{
		if (eqp->Actif() == FALSE ) return;

	CString str, VoieEnCours;

	// Voie Maitre
	c_VoieMaitre.GetLBText(c_VoieMaitre.GetCurSel(), VoieEnCours);

	GetDlgItem(IDC_DOPPLER)->GetWindowText(str);

	m_Doppler = atoi((char*)LPCTSTR(str));

	// Test sur le m_Doppler
	if ( m_Doppler > NIV_DOPPLER_MAX )
	{
		AfxMessageBox("Le Niveau Doopler peut prendre les valeurs : -250 à 250");
		m_Doppler = NIV_DOPPLER_MAX;
	}

	if ( m_Doppler < NIV_DOPPLER_MIN)
	{
		AfxMessageBox("Le Niveau Doopler peut prendre les valeurs : -250 à 250");
		m_Doppler = NIV_DOPPLER_MIN;
	}

	// Doppler
	eqp->SetChannelDopplerOffset((char *)LPCTSTR(VoieEnCours), m_Doppler);

	UpdateData(FALSE);

	eqp->SetModif(true);
}

//***********************************************
// Demande d'émission d'un message en ALE - LAUTO
//***********************************************
void CDlgTRC1752_MOD_CONF_RDO::OnButtonAleMsg()
{
	CString VoieAppel;

	c_Ale_Voie.GetLBText(c_Ale_Voie.GetCurSel(), VoieAppel);

	// FDI -201202
	if (eqp->IsEmetteurPanneTC())
	{
		eqp->SendRadEmiRnr((char *)LPCTSTR(VoieAppel));
		return;
	}
	//


	if (eqp->GetChannelReceptionStatus((char *)LPCTSTR(VoieAppel)) == "INACTIF" && (eqp->GetAleStatus((char *)LPCTSTR(VoieAppel)) == "LKD" || eqp->GetAleStatus((char *)LPCTSTR(VoieAppel)) == "LKG"))
	{
		eqp->EmissionOn((char *)LPCTSTR(VoieAppel));
		eqp->SetEmissionMsg((char *)LPCTSTR(VoieAppel), TRUE);
		timerMsg = SetTimer(3,5000,NULL);
		return;
	}

	eqp->LancerAppel((LPCTSTR)VoieAppel);
}

//****************************
// Mise en Emission de la voie
//****************************
void CDlgTRC1752_MOD_CONF_RDO::OnEmeteurEmi()
{
	CString VoieEncours;

	c_Ale_Voie.GetLBText(c_Ale_Voie.GetCurSel(), VoieEncours);

	if (m_EmetteurEmission == 1)
	{
		eqp->EmissionOff((char *)LPCTSTR(VoieEncours));
		eqp->SetReceptionOn((char *)LPCTSTR(VoieEncours));
	}
	else
	{
		eqp->SetReceptionDown((char *)LPCTSTR(VoieEncours));
		eqp->EmissionOn((char *)LPCTSTR(VoieEncours));
		if (eqp->GetChannelType((char *)LPCTSTR(VoieEncours)) != "-")
			if (eqp->GetAleStatus((char *)LPCTSTR(VoieEncours)) == "LKD" || eqp->GetAleStatus((char *)LPCTSTR(VoieEncours)) == "LKG")
				timerMsg = SetTimer(3,5000,NULL);
	}

	// FDI - 23/09/2010
	LoadData();

}

void CDlgTRC1752_MOD_CONF_RDO::OnSetfocusNivBfRec()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_NIV_BF_REC)->PostMessage(EM_SETSEL,0,-1);
}

void CDlgTRC1752_MOD_CONF_RDO::OnSetfocusNiveauQualite()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_NIVEAU_QUALITE)->PostMessage(EM_SETSEL,0,-1);
}

void CDlgTRC1752_MOD_CONF_RDO::OnSetfocusDoppler()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_DOPPLER)->PostMessage(EM_SETSEL,0,-1);
}

void CDlgTRC1752_MOD_CONF_RDO::OnSetfocusNivBfRecS()
{
	// TODO: Add your control notification handler code here
	GetDlgItem(IDC_NIV_BF_REC_S)->PostMessage(EM_SETSEL,0,-1);
}

void CDlgTRC1752_MOD_CONF_RDO::OnEditchangeComboAleVoie() {}

void CDlgTRC1752_MOD_CONF_RDO::OnSelchangeComboAleVoie()
{
	CString VoieEncours;

	//FDI
	string VoieAss;

	c_Ale_Voie.GetLBText(c_Ale_Voie.GetCurSel(), VoieEncours);

	// FDI
	VoieAss = eqp->GetChannelAssociatedAfConfiguration((char *)LPCTSTR(VoieEncours));

	TChannelConfiguration conf_courante = eqp->GetChannelConfiguration(VoieAss);

	m_EmetteurEmission = 0;

	if ( eqp->GetChannelEmissionEncours((char *)LPCTSTR(VoieEncours)) == TRUE)
		m_EmetteurEmission = 1;

	//Emi. Message en ALE [SACHEM]
	// FDI
	if (  conf_courante.waveform != "TRANSP")
		m_Alt_Msg.SetWindowText("Emi. Message en ALE [SACHEM]");
	else
		m_Alt_Msg.SetWindowText("Alternat sur TMFP");

	UpdateData(FALSE);
}

//*****************************************
// Fin d'émission d'un message en ALE_LAUTO
//*****************************************
void CDlgTRC1752_MOD_CONF_RDO::FinEmissionMsg()
{
	CString VoieEncours;

	c_Ale_Voie.GetLBText(c_Ale_Voie.GetCurSel(), VoieEncours);

	eqp->EmissionOff((char *)LPCTSTR(VoieEncours));
	eqp->SetEmissionMsg((char *)LPCTSTR(VoieEncours), FALSE);
	m_EmetteurEmission =0;

	KillTimer(timerMsg);

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_RDO::AfficheParams(bool res)
{
	c_VoieMaitre.EnableWindow(res);
	c_VoieEsclave.EnableWindow(res);
	c_NiveauBfReception.EnableWindow(res);
	c_NiveauBfReceptionEsclave.EnableWindow(res);
	c_NiveauQualite.EnableWindow(res);
	c_Doppler.EnableWindow(res);
	c_Ale_Voie.EnableWindow(res);
	GetDlgItem(IDC_EMETEUR_EMI)->EnableWindow(res);

	// RecMil
	m_RecMil.EnableWindow(res);
}

// Mise en place de l'option RecMil
void CDlgTRC1752_MOD_CONF_RDO::OnRecMil()
{
	if (m_RecMil.GetCheck() == 1 )
		eqp->SetRecMil(true);
	else
		eqp->SetRecMil(false);

}
