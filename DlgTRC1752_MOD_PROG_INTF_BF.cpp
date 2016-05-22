// DlgTRC1752_MOD_PROG_INTF_BF.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_INTF_BF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_BF dialog

/*Ce menu permet de définir les quatre configurations des quatre interfaces BF.*/


CDlgTRC1752_MOD_PROG_INTF_BF::CDlgTRC1752_MOD_PROG_INTF_BF(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_INTF_BF::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_INTF_BF)
	m_InterfaceBf2 = _T("BF1");
	m_InterfaceBf3 = _T("BF1");
	m_InterfaceBf4 = _T("BF1");
	m_InterfaceBf1 = 0;
	m_NiveauBfSortie = 0;
	m_NiveauBfEntree = 0;
	m_TypeAlternat = 0;
	m_TempoAlternat = 300;
	m_BlRec = 0;
	m_TempoBlRec = 300;
	m_TypeInterfaceBf = 0;
	m_TempoBourRadio = 300;
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_INTF_BF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_INTF_BF)
	DDX_Control(pDX, IDC_TYPE_INTERFACE_BF, c_TypeInterfaceBf);
	DDX_Control(pDX, IDC_TYPE_BL_REC, c_BlRec);
	DDX_Control(pDX, IDC_TYPE_ALTERNAT, c_TypeAlternat);
	DDX_Control(pDX, IDC_TEMPO_BOUR_RADIO_SPIN, s_TempoBourRadio);
	DDX_Control(pDX, IDC_TEMPO_BOUR_RADIO, c_TempoBourRadio);
	DDX_Control(pDX, IDC_TEMPO_BL_REC_SPIN, s_TempoBlRec);
	DDX_Control(pDX, IDC_TEMPO_BL_REC, c_TempoBlRec);
	DDX_Control(pDX, IDC_TEMPO_ALT_SPIN, s_TempoAlternat);
	DDX_Control(pDX, IDC_TEMPO_ALT, c_TempoAlternat);
	DDX_Control(pDX, IDC_STATIC_NIV_SORTIE, t_NiveauBfSortie);
	DDX_Control(pDX, IDC_PROG_INTF_BF, c_InterfaceBf1);
	DDX_Control(pDX, IDC_STATIC_ALTERNAT, t_Alternat);
	DDX_Control(pDX, IDC_NIV_BF_S_SPIN, s_NiveauBfSortie);
	DDX_Control(pDX, IDC_EDIT_BF_F4, c_InterfaceBf4);
	DDX_Control(pDX, IDC_EDIT_BF_F3, c_InterfaceBf3);
	DDX_Control(pDX, IDC_EDIT_BF_F2, c_InterfaceBf2);
	DDX_Control(pDX, IDC_NIV_BF_E_SPIN, s_NiveauBfEmission);
	DDX_Text(pDX, IDC_EDIT_BF_F2, m_InterfaceBf2);
	DDV_MaxChars(pDX, m_InterfaceBf2, 3);
	DDX_Text(pDX, IDC_EDIT_BF_F3, m_InterfaceBf3);
	DDV_MaxChars(pDX, m_InterfaceBf3, 3);
	DDX_Text(pDX, IDC_EDIT_BF_F4, m_InterfaceBf4);
	DDV_MaxChars(pDX, m_InterfaceBf4, 3);
	DDX_CBIndex(pDX, IDC_PROG_INTF_BF, m_InterfaceBf1);
	DDX_Text(pDX, IDC_NIV_BF_SORTIE, m_NiveauBfSortie);
	DDV_MinMaxInt(pDX, m_NiveauBfSortie, -30, 10);
	DDX_Text(pDX, IDC_NIV_BF_ENTREE, m_NiveauBfEntree);
	DDV_MinMaxInt(pDX, m_NiveauBfEntree, 0, 18);
	DDX_CBIndex(pDX, IDC_TYPE_ALTERNAT, m_TypeAlternat);
	DDX_Text(pDX, IDC_TEMPO_ALT, m_TempoAlternat);
	DDV_MinMaxInt(pDX, m_TempoAlternat, 0, 9999);
	DDX_CBIndex(pDX, IDC_TYPE_BL_REC, m_BlRec);
	DDX_Text(pDX, IDC_TEMPO_BL_REC, m_TempoBlRec);
	DDV_MinMaxInt(pDX, m_TempoBlRec, 0, 5000);
	DDX_CBIndex(pDX, IDC_TYPE_INTERFACE_BF, m_TypeInterfaceBf);
	DDX_Text(pDX, IDC_TEMPO_BOUR_RADIO, m_TempoBourRadio);
	DDV_MinMaxInt(pDX, m_TempoBourRadio, 0, 9999);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_INTF_BF, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_INTF_BF)
	ON_CBN_SELCHANGE(IDC_PROG_INTF_BF, OnSelchangeProgIntfBf)
	ON_NOTIFY(UDN_DELTAPOS, IDC_NIV_BF_E_SPIN, OnDeltaposNivBfESpin)
	ON_WM_TIMER()
	ON_NOTIFY(UDN_DELTAPOS, IDC_NIV_BF_S_SPIN, OnDeltaposNivBfSSpin)
	ON_EN_KILLFOCUS(IDC_NIV_BF_SORTIE, OnKillfocusNivBfSortie)
	ON_EN_KILLFOCUS(IDC_NIV_BF_ENTREE, OnKillfocusNivBfEntree)
	ON_EN_KILLFOCUS(IDC_TEMPO_ALT, OnKillfocusTempoAlt)
	ON_EN_KILLFOCUS(IDC_TEMPO_BL_REC, OnKillfocusTempoBlRec)
	ON_EN_KILLFOCUS(IDC_TEMPO_BOUR_RADIO, OnKillfocusTempoBourRadio)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TEMPO_ALT_SPIN, OnDeltaposTempoAltSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TEMPO_BL_REC_SPIN, OnDeltaposTempoBlRecSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_TEMPO_BOUR_RADIO_SPIN, OnDeltaposTempoBourRadioSpin)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_BF message handlers

BOOL CDlgTRC1752_MOD_PROG_INTF_BF::OnInitDialog()
{

	CDialog::OnInitDialog();

	//Bornage du niveau de sortie BF
	s_NiveauBfSortie.SetRange(-30, 10);
	//Bornage des tempos
	s_TempoAlternat.SetRange(0, 9999);
	s_TempoBlRec.SetRange(0, 5000);
	s_TempoBourRadio.SetRange(0, 9999);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTRC1752_MOD_PROG_INTF_BF::OnSelchangeProgIntfBf()
{
	// Mise à jour des autres fenêtres
	CString str;
	int nIndex = c_InterfaceBf1.GetCurSel();

	if (nIndex != LB_ERR)
		c_InterfaceBf1.GetLBText(nIndex,str);

	c_InterfaceBf2.SetWindowText(str);
	c_InterfaceBf3.SetWindowText(str);
	c_InterfaceBf4.SetWindowText(str);

	//Affichage de la configuration
	AffichageConfiguration();

}


//---------------------------------------
//Gestion de la saisie du Niveau d'Entrée
//---------------------------------------
void CDlgTRC1752_MOD_PROG_INTF_BF::OnDeltaposNivBfESpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	//Le Niveau d’Entrée d’une interface BF peut prendre deux valeurs : 0 dBm ou +18 dBm.
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;


	if (pNMUpDown->iDelta > 0)  m_NiveauBfEntree += 18;
		else       m_NiveauBfEntree -= 18;

	if ( m_NiveauBfEntree > 18 )
	{
		AfxMessageBox("Le Niveau d’Entrée d’une interface BF peut prendre deux valeurs : 0 dBm ou +18 dBm.");
		m_NiveauBfEntree = 18;
	}

	if ( m_NiveauBfEntree < 0)
	{
		AfxMessageBox("Le Niveau d’Entrée d’une interface BF peut prendre deux valeurs : 0 dBm ou +18 dBm.");
		m_NiveauBfEntree = 0;
	}

	UpdateData(FALSE);

	*pResult = 0;

}

void CDlgTRC1752_MOD_PROG_INTF_BF::OnKillfocusNivBfEntree()
{
	UpdateData(TRUE);

	if (m_NiveauBfEntree != 0 || m_NiveauBfEntree != 18)
	{
		m_NiveauBfEntree = 0;
		UpdateData(FALSE);

	}
}

//----------------------------------------
//Gestion de la saisie du Niveau de Sortie
//----------------------------------------
void CDlgTRC1752_MOD_PROG_INTF_BF::OnDeltaposNivBfSSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	//Le Niveau de Sortie d’une interface BF peut prendre les valeurs de : -30 dBm à +10 dBm.
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_NiveauBfSortie += 1;
		else       m_NiveauBfSortie -= 1;

	if ( m_NiveauBfSortie > 10 )
	{
		AfxMessageBox("Le Niveau de Sortie d’une interface BF peut prendre les valeurs de : -30 dBm à +10 dBm.");
		m_NiveauBfSortie = 10;
	}

	if ( m_NiveauBfSortie < -30)
	{
		AfxMessageBox("Le Niveau de Sortie d’une interface BF peut prendre les valeurs de : -30 dBm à +10 dBm.");
		m_NiveauBfSortie = -30;
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_INTF_BF::OnKillfocusNivBfSortie()
{
	UpdateData(TRUE);

	if (m_NiveauBfSortie > 10 || m_NiveauBfSortie <-30)
	{
		m_NiveauBfSortie = 0;
		UpdateData(FALSE);

	}

}

//--------------------------------------
//Gestion de la saisie du Tempo Alternat
//--------------------------------------
void CDlgTRC1752_MOD_PROG_INTF_BF::OnDeltaposTempoAltSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_TempoAlternat += 1;
		else       m_TempoAlternat -= 1;

	if ( m_TempoAlternat > 9999 || m_TempoAlternat < 0)
	{
		AfxMessageBox("Le Tempo d'Alternat d’une interface BF peut prendre les valeurs de : 0 ms à 9999 ms.");
		m_TempoAlternat = 300;
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_INTF_BF::OnKillfocusTempoAlt()
{
	UpdateData(TRUE);

	if (m_TempoAlternat > 9999 || m_TempoAlternat < 0)
	{
		m_TempoAlternat = 300;
		UpdateData(FALSE);

	}
}

//----------------------------------
//Gestion de la saisie du Tempo Mute
//----------------------------------
void CDlgTRC1752_MOD_PROG_INTF_BF::OnDeltaposTempoBlRecSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_TempoBlRec += 1;
		else       m_TempoBlRec -= 1;

	if ( m_TempoBlRec > 5000 || m_TempoBlRec < 0)
	{
		AfxMessageBox("Le Tempo Mute d’une interface BF peut prendre les valeurs de : 0 ms à 5000 ms.");
		m_TempoBlRec = 300;
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_INTF_BF::OnKillfocusTempoBlRec()
{
	UpdateData(TRUE);

	if (m_TempoBlRec > 5000 || m_TempoBlRec < 0)
	{
		m_TempoBlRec = 300;
		UpdateData(FALSE);

	}

}

//--------------------------------------------
//Gestion de la saisie du Tempo Bourrage Radio
//--------------------------------------------
void CDlgTRC1752_MOD_PROG_INTF_BF::OnDeltaposTempoBourRadioSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_TempoBourRadio += 1;
		else       m_TempoBourRadio -= 1;

	if ( m_TempoBourRadio > 9999 || m_TempoBourRadio < 0)
	{
		AfxMessageBox("Le Tempo Bourage Radio d’une interface BF peut prendre les valeurs de : 0 ms à 9999 ms.");
		m_TempoBourRadio = 300;
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_INTF_BF::OnKillfocusTempoBourRadio()
{
	UpdateData(TRUE);

	if (m_TempoBourRadio > 9999 || m_TempoBourRadio < 0)
	{
		m_TempoBourRadio = 300;
		UpdateData(FALSE);

	}
}


void CDlgTRC1752_MOD_PROG_INTF_BF::Valide()
{
	// Changement impossible quand l'équipement est en Distant
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		UpdateData(FALSE);
		return;
	}

	UpdateData(TRUE);

	//Mémorisation de la configuration en cours
	MemorisationConfiguration();

}

//Mémorisation de la configuration
void CDlgTRC1752_MOD_PROG_INTF_BF::MemorisationConfiguration()
{
	//***********************
	// AfChannelConfiguration
	//***********************
	CString str;

	TAFChannelConfiguration conf_courante = eqp->GetAfChannelConfiguration(AF_CHANNELS_CONFIGURATIONS[c_InterfaceBf1.GetCurSel()]);

	// output_level = 0
	conf_courante.output_level = m_NiveauBfSortie;

	// input_level = 0
	conf_courante.input_level = m_NiveauBfEntree;


	// ptt_type = COL_OUV_M/COL_OUV/TTL
	switch (c_TypeAlternat.GetCurSel())
	{
	case 0:
		str = "COL_OUV_M";
		break;
	case 1:
		str = "COL_OUV";
		break;
	case 2:
		str = "TTL";
		break;
	default:
		str = "COL_OUV_M";
		break;
	}
	conf_courante.ptt_type = str;

	// ptt_tempo = 300
	conf_courante.ptt_tempo = m_TempoAlternat;

	// mute_characteristics = COL_OUV_M/COL_OUV/TTL
	switch (c_BlRec.GetCurSel())
	{
	case 0:
		str = "COL_OUV_M";
		break;
	case 1:
		str = "COL_OUV";
		break;
	case 2:
		str = "TTL";
		break;
	default:
		str = "COL_OUV_M";
		break;
	}
	conf_courante.mute_characteristics = str;

	// mute_delay = 300
	conf_courante.mute_delay = m_TempoBlRec;

	// interface_type = "SYMETRIQUE"/"ASYMETRIQUE"
	c_TypeInterfaceBf.GetLBText(c_TypeInterfaceBf.GetCurSel(), str);
	conf_courante.interface_type = str;

	// radio_delay = 300
	conf_courante.radio_delay = m_TempoBourRadio;


	//**************************************************************************
	//Mise en place dans la structure
	//**************************************************************************
	eqp->SetAfChannelConfiguration(AF_CHANNELS_CONFIGURATIONS[c_InterfaceBf1.GetCurSel()], conf_courante);

	UpdateData(FALSE);

	//*************************************************************************************************
}

//Affichage de la configuration
void CDlgTRC1752_MOD_PROG_INTF_BF::AffichageConfiguration()
{
	//**********************
	//AfChannelConfiguration
	//**********************

	TAFChannelConfiguration conf_courante = eqp->GetAfChannelConfiguration(AF_CHANNELS_CONFIGURATIONS[c_InterfaceBf1.GetCurSel()]);


	// ptt_type = COL_OUV_M/COL_OUV/TTL
	if (conf_courante.ptt_type == "COL_OUV_M")
		c_TypeAlternat.SetCurSel(0);
	else if (conf_courante.ptt_type == "COL_OUV")
		c_TypeAlternat.SetCurSel(1);
	else if (conf_courante.ptt_type == "TTL")
		c_TypeAlternat.SetCurSel(2);
	else
		c_TypeAlternat.SetCurSel(0);


	// mute_characteristics = COL_OUV_M/COL_OUV/TTL
	if (conf_courante.mute_characteristics == "COL_OUV_M")
		c_BlRec.SetCurSel(0);
	else if (conf_courante.mute_characteristics == "COL_OUV")
		c_BlRec.SetCurSel(1);
	else if (conf_courante.mute_characteristics == "TTL")
		c_BlRec.SetCurSel(2);
	else
		c_BlRec.SetCurSel(0);

	// interface_type
	c_TypeInterfaceBf.SelectString(0, conf_courante.interface_type.c_str());

	UpdateData(TRUE);

	// output_level = 0
	m_NiveauBfSortie = conf_courante.output_level;

	// input_level = 0
	m_NiveauBfEntree = conf_courante.input_level;

	// ptt_tempo = 300
	m_TempoAlternat = conf_courante.ptt_tempo;

	// mute_delay = 300
	m_TempoBlRec = conf_courante.mute_delay;

	// radio_delay = 300
	m_TempoBourRadio = conf_courante.radio_delay;

	UpdateData(FALSE);

	//*************************************************************************************************
}

// Mise à zero du choix de l'interface BF
void CDlgTRC1752_MOD_PROG_INTF_BF::razChoixInterfaceBF()
{
	c_InterfaceBf1.SetCurSel(0);

	OnSelchangeProgIntfBf();

}

// **********************************************************
// Gestion du timer
// **********************************************************
void CDlgTRC1752_MOD_PROG_INTF_BF::marcheTimer()
{
	if (eqp->GetMode() == false) return;		//il faut etre en distant

	m_timerBF = SetTimer(1,2000,NULL);
}

void CDlgTRC1752_MOD_PROG_INTF_BF::arretTimer()
{
	KillTimer(m_timerBF);
}

void CDlgTRC1752_MOD_PROG_INTF_BF::OnTimer(UINT nIDEvent)
{

	CDialog::OnTimer(nIDEvent);

	AffichageConfiguration();
}

// Mise à jour de la liste en fonctionde quadrivoie
void CDlgTRC1752_MOD_PROG_INTF_BF::MiseJourListeInterfaceBf()
{
	//RAZ des listes
	c_InterfaceBf1.ResetContent();

	//Initialisation
	c_InterfaceBf1.AddString("BF1");
	c_InterfaceBf1.AddString("BF2");

	if (eqp->GetQuadrivoie() == TRUE)
	{
		c_InterfaceBf1.AddString("BF3");
		c_InterfaceBf1.AddString("BF4");
	}

	c_InterfaceBf1.SetCurSel(0);
}
