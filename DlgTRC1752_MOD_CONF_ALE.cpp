// DlgTRC1752_MOD_CONF_ALE.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_CONF_ALE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_ALE dialog


CDlgTRC1752_MOD_CONF_ALE::CDlgTRC1752_MOD_CONF_ALE(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_CONF_ALE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_CONF_ALE)
	m_Marche = TRUE;
	m_Amd = FALSE;			//Indique l'utilisation de AMD ou CHAT
	m_Msg_Amd = _T("");
	m_Ch_50 = TRUE;
	m_Ch_51 = TRUE;
	m_Ch_52 = FALSE;
	m_Ch_53 = FALSE;
	m_Ch_54 = FALSE;
	m_Ch_55 = FALSE;
	m_Type_Ale = 0;
	m_CH_56 = FALSE;
	m_CH_57 = FALSE;
	m_CH_58 = FALSE;
	m_CH_59 = FALSE;
	m_Type_Call = 0;
	m_GicCleDeBase = _T("");
	m_AmdMsgRecu = _T("");
	//}}AFX_DATA_INIT

	this->eqp = equip;
	this->twa_a = false;
	this->twa_b = false;
	this->sound_a = false;
	this->sound_b = false;
}


void CDlgTRC1752_MOD_CONF_ALE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_CONF_ALE)
	DDX_Control(pDX, IDC_COMBO_Key, c_Key);
	DDX_Control(pDX, IDC_COMBO_LT0, c_LT0);
	DDX_Control(pDX, IDC_COMBO_LP, c_LP);
	DDX_Control(pDX, IDC_BUTTON_STAP, c_Stap);
	DDX_Control(pDX, IDC_BUTTON_STAM, c_Stam);
	DDX_Control(pDX, IDC_BUTTON_NETP, c_Netp);
	DDX_Control(pDX, IDC_BUTTON_NETM, c_Netm);
	DDX_Control(pDX, IDC_EFFACER_AMD, c_EffacerAmd);
	DDX_Control(pDX, IDC_VOIE_APPELEE, c_Voie);
	DDX_Control(pDX, IDC_LP_ORG_HEURE, c_OrigineHeure);
	DDX_Control(pDX, IDC_STATIC_LISTE_NET, t_ListeReseau);
	DDX_Control(pDX, IDC_STATIC_LISTE_STA, t_ListeStation);
	DDX_Control(pDX, IDC_SELF_ADRESSE, c_SelfAdresse);
	DDX_Control(pDX, IDC_SEND_CHAT, c_SendChat);
	DDX_Control(pDX, IDC_TYPE_CALL, c_Type_Call);
	DDX_Control(pDX, IDC_ALE_LNL_UNL, c_LnlUnl);
	DDX_Control(pDX, IDC_TYPE_ALE, c_Type_Ale);
	DDX_Control(pDX, IDC_AMD_MSG, c_Msg_Amd);
	DDX_Control(pDX, IDC_STATIONS, c_Stations);
	DDX_Control(pDX, IDC_RESEAUX, c_Reseaux);
	DDX_Check(pDX, IDC_MARCHE, m_Marche);
	DDX_Check(pDX, IDC_AMD, m_Amd);
	DDX_Text(pDX, IDC_AMD_MSG, m_Msg_Amd);
	DDV_MaxChars(pDX, m_Msg_Amd, 90);
	DDX_Check(pDX, IDC_CH_50, m_Ch_50);
	DDX_Check(pDX, IDC_CH_51, m_Ch_51);
	DDX_Check(pDX, IDC_CH_52, m_Ch_52);
	DDX_Check(pDX, IDC_CH_53, m_Ch_53);
	DDX_Check(pDX, IDC_CH_54, m_Ch_54);
	DDX_Check(pDX, IDC_CH_55, m_Ch_55);
	DDX_CBIndex(pDX, IDC_TYPE_ALE, m_Type_Ale);
	DDX_Check(pDX, IDC_CH_56, m_CH_56);
	DDX_Check(pDX, IDC_CH_57, m_CH_57);
	DDX_Check(pDX, IDC_CH_58, m_CH_58);
	DDX_Check(pDX, IDC_CH_59, m_CH_59);
	DDX_CBIndex(pDX, IDC_TYPE_CALL, m_Type_Call);
	DDX_Text(pDX, IDC_LP_GIC, m_GicCleDeBase);
	DDX_Text(pDX, IDC_AMD_MSG_RECU, m_AmdMsgRecu);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_CONF_ALE, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_CONF_ALE)
	ON_CBN_SELCHANGE(IDC_SELF_ADRESSE, OnSelchangeSelfAdresse)
	ON_CBN_SELCHANGE(IDC_STATIONS, OnSelchangeStations)
	ON_CBN_SELCHANGE(IDC_RESEAUX, OnSelchangeReseaux)
	ON_BN_CLICKED(IDC_AMD, OnAmd)
	ON_CBN_EDITCHANGE(IDC_TYPE_ALE, OnEditchangeTypeAle)
	ON_BN_CLICKED(IDC_CH_50, OnCh50)
	ON_BN_CLICKED(IDC_CH_51, OnCh51)
	ON_BN_CLICKED(IDC_CH_52, OnCh52)
	ON_BN_CLICKED(IDC_CH_53, OnCh53)
	ON_BN_CLICKED(IDC_CH_54, OnCh54)
	ON_BN_CLICKED(IDC_CH_55, OnCh55)
	ON_CBN_SELCHANGE(IDC_TYPE_CALL, OnSelchangeTypeCall)
	ON_BN_CLICKED(IDC_CH_56, OnCh56)
	ON_BN_CLICKED(IDC_CH_57, OnCh57)
	ON_BN_CLICKED(IDC_CH_58, OnCh58)
	ON_BN_CLICKED(IDC_CH_59, OnCh59)
	ON_BN_CLICKED(IDC_ALE_LNL_UNL, OnAleLnlUnl)
	ON_EN_KILLFOCUS(IDC_LP_GIC, OnKillfocusLpGic)
	ON_CBN_SELCHANGE(IDC_LP_ORG_HEURE, OnSelchangeLpOrgHeure)
	ON_BN_CLICKED(IDC_MARCHE, OnMarche)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_EFFACER_AMD, OnEffacerAmd)
	ON_BN_CLICKED(IDC_SEND_CHAT, OnSendChat)

	ON_EN_KILLFOCUS(IDC_AMD_MSG, OnKillfocusAmdMsg)
	ON_BN_CLICKED(IDC_BUTTON_SADP, OnButtonSadp)
	ON_BN_CLICKED(IDC_BUTTON_SADM, OnButtonSadm)
	ON_BN_CLICKED(IDC_BUTTON_STAP, OnButtonStap)
	ON_BN_CLICKED(IDC_BUTTON_STAM, OnButtonStam)
	ON_BN_CLICKED(IDC_BUTTON_NETP, OnButtonNetp)
	ON_BN_CLICKED(IDC_BUTTON_NETM, OnButtonNetm)
	ON_BN_CLICKED(IDC_BUTTON_LT0P, OnButtonLt0p)
	ON_BN_CLICKED(IDC_BUTTON_LT0M, OnButtonLt0m)
	ON_BN_CLICKED(IDC_BUTTON_KEYP, OnButtonKeyp)
	ON_BN_CLICKED(IDC_BUTTON_KEYM, OnButtonKeym)
	ON_CBN_SELCHANGE(IDC_COMBO_LT0, OnSelchangeComboLt0)
	ON_CBN_SELCHANGE(IDC_COMBO_LP, OnSelchangeComboLp)
	ON_CBN_SELCHANGE(IDC_COMBO_Key, OnSelchangeCOMBOKey)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_ALE message handlers

BOOL CDlgTRC1752_MOD_CONF_ALE::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Initialisations

	pBtn50 = (CButton*) GetDlgItem(IDC_CH_50);
	pBtn51 = (CButton*) GetDlgItem(IDC_CH_51);
	pBtn52 = (CButton*) GetDlgItem(IDC_CH_52);
	pBtn53 = (CButton*) GetDlgItem(IDC_CH_53);
	pBtn54 = (CButton*) GetDlgItem(IDC_CH_54);
	pBtn55 = (CButton*) GetDlgItem(IDC_CH_55);
	pBtn56 = (CButton*) GetDlgItem(IDC_CH_56);
	pBtn57 = (CButton*) GetDlgItem(IDC_CH_57);
	pBtn58 = (CButton*) GetDlgItem(IDC_CH_58);
	pBtn59 = (CButton*) GetDlgItem(IDC_CH_59);
	pBtnMarcheMdm = (CButton*) GetDlgItem(IDC_MARCHE);

	c_Msg_Amd.ShowWindow(FALSE);
	c_LnlUnl.ShowWindow(TRUE);
	GetDlgItem(IDC_SEND_CHAT)->EnableWindow(FALSE);


	//Formatage de l'affichage

	c_SelfAdresse.SetCurSel(0);
	c_LP.SetCurSel(0);
	c_LT0.SetCurSel(0);
	c_Key.SetCurSel(0);
	c_Stations.SetCurSel(0);

	LoadData();

	c_Voie.SetCurSel(0);

	OnSelchangeTypeCall();

	SetTimer(REFRESH, 1000, NULL);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/* **************************************************************************
METHODE :		LoadData()
TRAITEMENT:		Charge les données de la vue
***************************************************************************	*/
void CDlgTRC1752_MOD_CONF_ALE::LoadData()
{
	int i;

	UpdateData(TRUE);

	// Parametres locaux
	m_GicCleDeBase = eqp->GetGic().c_str();
	c_OrigineHeure.SelectString(0, eqp->GetOrigineHeure().c_str());

	TModemDistant modem = eqp->GetModemDistant();

	// Parametres distants
	c_Type_Ale.SelectString(0, modem.type_ale.c_str());
	m_Marche = modem.marche;
	c_Type_Call.SelectString(0, modem.type_appel.c_str());
	c_Type_Ale.SelectString(0, modem.type_ale.c_str());


	// Liste des channels
	m_Ch_50 = modem.channel[0];
	m_Ch_51 = modem.channel[1];
	m_Ch_52 = modem.channel[2];
	m_Ch_53 = modem.channel[3];
	m_Ch_54 = modem.channel[4];
	m_Ch_55 = modem.channel[5];
	m_CH_56 = modem.channel[6];
	m_CH_57 = modem.channel[7];
	m_CH_58 = modem.channel[8];
	m_CH_59 = modem.channel[9];

	// Selfaddresses
	c_SelfAdresse.ResetContent();
	for(i=0; i<modem.selfaddress.size();i++)
		c_SelfAdresse.AddString(modem.selfaddress[i].c_str());

	if(modem.current_selfaddress < modem.selfaddress.size()) c_SelfAdresse.SetCurSel(modem.current_selfaddress);

	// LP
	c_LP.ResetContent();
	for(i=0; i<modem.LP.size();i++)
		c_LP.AddString(modem.LP[i].c_str());

	if(modem.current_LP < modem.LP.size()) c_LP.SetCurSel(modem.current_LP);

	// LT0
	c_LT0.ResetContent();
	for(i=0; i<modem.LT0.size();i++)
		c_LT0.AddString(modem.LT0[i].c_str());

	if(modem.current_LT0 < modem.LT0.size()) c_LT0.SetCurSel(modem.current_LT0);

	// Key
	c_Key.ResetContent();
	for(i=0; i<modem.Key.size();i++)
		c_Key.AddString(modem.Key[i].c_str());

	if(modem.current_Key < modem.Key.size()) c_Key.SetCurSel(modem.current_Key);

	// Stations
	c_Stations.ResetContent();
	for(i=0; i<modem.stations.size();i++)
		c_Stations.AddString(modem.stations[i].c_str());

	if(modem.current_station < modem.stations.size()) c_Stations.SetCurSel(modem.current_station);

	// Reseaux
	c_Reseaux.ResetContent();
	string tmp;
	for(i=0; i<modem.reseaux.size();i++)
	{
		c_Reseaux.AddString(modem.reseaux[i].c_str());
		tmp = modem.reseaux[i].c_str();
	}

	if(modem.current_reseau < modem.reseaux.size()) c_Reseaux.SetCurSel(modem.current_reseau);

	UpdateData(FALSE);

	OnSelchangeTypeCall();

}

void CDlgTRC1752_MOD_CONF_ALE::OnSelchangeSelfAdresse()
{

	TModemDistant modem = eqp->GetModemDistant();

	modem.current_selfaddress = c_SelfAdresse.GetCurSel();

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnSelchangeStations()
{
	TModemDistant modem = eqp->GetModemDistant();

	modem.current_station = c_Stations.GetCurSel();

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnSelchangeReseaux()
{
	TModemDistant modem = eqp->GetModemDistant();

	modem.current_reseau = c_Reseaux.GetCurSel();

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnAmd()
{
	CString LnlUnl;
	c_LnlUnl.GetWindowText(LnlUnl);

	// AMD/CHAT: champ d'un message ALE permettant de transférer du texte libre
	CString str = "";
	if (m_Amd)
	{
		TModemDistant modem = eqp->GetModemDistant();

		UpdateData(TRUE);
		modem.amd_chat = (char*)LPCTSTR(str);
		eqp->SetModemDistant(modem);
		c_Msg_Amd.SetWindowText(str);
		UpdateData(FALSE);

		m_Amd = false;
		c_Msg_Amd.ShowWindow(FALSE);
		GetDlgItem(IDC_SEND_CHAT)->EnableWindow(FALSE);

	}
	else
	{
		m_Amd = true;
		c_Msg_Amd.ShowWindow(TRUE);
		c_Voie.GetLBText(c_Voie.GetCurSel(), str);
		if (LnlUnl == "Rompre" && eqp->GetChannelAfLevelReceived((char*)LPCTSTR(str))<-20)
			GetDlgItem(IDC_SEND_CHAT)->EnableWindow(TRUE);		//Si texte = Couper alors le lien est établi donc le CHAT est possible
	}

}


void CDlgTRC1752_MOD_CONF_ALE::Valide()
{



}

void CDlgTRC1752_MOD_CONF_ALE::OnEditchangeTypeAle()
{
	CString str;

	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	c_Type_Ale.GetLBText(c_Type_Ale.GetCurSel(), str);

	modem.type_ale = (char*)LPCTSTR(str);

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnCh50()
{
	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	modem.channel[0] = FALSE;

	if (pBtn50->GetCheck())
		modem.channel[0] = TRUE;

	//modem.channel[0] = m_Ch_50;

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnCh51()
{
	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	modem.channel[1] = FALSE;

	if (pBtn51->GetCheck())
		modem.channel[1] = TRUE;

	//modem.channel[1] = m_Ch_51;

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnCh52()
{
	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	modem.channel[2] = FALSE;

	if (pBtn52->GetCheck())
		modem.channel[2] = TRUE;

	//modem.channel[2] = m_Ch_52;

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnCh53()
{
	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	modem.channel[3] = FALSE;

	if (pBtn53->GetCheck())
		modem.channel[3] = TRUE;

	//modem.channel[3] = m_Ch_53;

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnCh54()
{
	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	modem.channel[4] = FALSE;

	if (pBtn54->GetCheck())
		modem.channel[4] = TRUE;

	//modem.channel[4] = m_Ch_54;

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnCh55()
{
	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	modem.channel[5] = FALSE;

	if (pBtn55->GetCheck())
		modem.channel[5] = TRUE;

	//modem.channel[5] = m_Ch_55;

	eqp->SetModemDistant(modem);
}

//Affichage en fonction de la selection du type appel
void CDlgTRC1752_MOD_CONF_ALE::OnSelchangeTypeCall()
{
	t_ListeReseau.ShowWindow(FALSE);
	c_Reseaux.ShowWindow(FALSE);
	c_Netp.ShowWindow(FALSE);
	c_Netm.ShowWindow(FALSE);
	t_ListeStation.ShowWindow(FALSE);
	c_Stations.ShowWindow(FALSE);
	c_Stam.ShowWindow(FALSE);
	c_Stap.ShowWindow(FALSE);

	// Station
	if (c_Type_Call.GetCurSel() == 0)
	{
		c_Stations.ShowWindow(TRUE);
		t_ListeStation.ShowWindow(TRUE);
		c_Stam.ShowWindow(TRUE);
		c_Stap.ShowWindow(TRUE);
	}

	// Reseaux
	if (c_Type_Call.GetCurSel() == 1)
	{
		c_Reseaux.ShowWindow(TRUE);
		t_ListeReseau.ShowWindow(TRUE);
		c_Netp.ShowWindow(TRUE);
		c_Netm.ShowWindow(TRUE);
	}

	CString str;

	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	c_Type_Call.GetLBText(c_Type_Call.GetCurSel(), str);

	modem.type_appel = (char*)LPCTSTR(str);

	eqp->SetModemDistant(modem);

}

void CDlgTRC1752_MOD_CONF_ALE::OnCh56()
{
	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	modem.channel[6] = FALSE;

	if (pBtn56->GetCheck())
		modem.channel[6] = TRUE;

	//modem.channel[6] = m_CH_56;

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnCh57()
{
	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	modem.channel[7] = FALSE;

	if (pBtn57->GetCheck())
		modem.channel[7] = TRUE;

	//modem.channel[7] = m_CH_57;

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnCh58()
{
	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	modem.channel[8] = FALSE;

	if (pBtn58->GetCheck())
		modem.channel[8] = TRUE;

	//modem.channel[8] = m_CH_58;

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnCh59()
{
	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	modem.channel[9] = FALSE;

	if (pBtn59->GetCheck())
		modem.channel[9] = TRUE;

	//modem.channel[9] = m_CH_59;

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnAleLnlUnl()
{
	// En fonction de la valeur du bouton on rompt ou etablie sur la voie selectionnée
	CString str;
	c_LnlUnl.GetWindowText(str);

	if (str == "Etablir")
	{
		c_Voie.GetLBText(c_Voie.GetCurSel(), str);
		//eqp->JouerSon(glob_EQUIP_ALE);
		eqp->LancerReceptionAppel((char*)LPCTSTR(str));
	} else
	{
		c_Voie.GetLBText(c_Voie.GetCurSel(), str);
		eqp->CasserAppel((char*)LPCTSTR(str));
		// FDI
		eqp->SetChannelAfLevelReceived((char*)LPCTSTR(str), -30);
	}
}

void CDlgTRC1752_MOD_CONF_ALE::OnKillfocusLpGic()
{
	UpdateData(TRUE);

	int value = atoi((char*)LPCTSTR(m_GicCleDeBase));

	if (value<0 || value>9999)
	{
		AfxMessageBox("La valeur doit être comprise entre 0 et 9999");
		m_GicCleDeBase = eqp->GetGic().c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	eqp->SetGic((char*)LPCTSTR(m_GicCleDeBase));
}

void CDlgTRC1752_MOD_CONF_ALE::OnSelchangeLpOrgHeure()
{
	CString str;

	UpdateData(TRUE);

	c_OrigineHeure.GetLBText(c_OrigineHeure.GetCurSel(), str);

	eqp->SetOrigineHeure((char*)LPCTSTR(str));
}

void CDlgTRC1752_MOD_CONF_ALE::OnMarche()
{
	UpdateData(TRUE);

	TModemDistant modem = eqp->GetModemDistant();

	if (pBtnMarcheMdm->GetCheck())
		modem.marche = TRUE;
	else
		modem.marche = FALSE;

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	switch(nIDEvent)
	{
	case REFRESH: // Rafraichissement de la vue
		{
			CString str,str_voie;
			c_Voie.GetLBText(c_Voie.GetCurSel(), str);

			string etat = eqp->GetAleParameter((char*)LPCTSTR(str)).ale_status;


			CString LnlUnl;
			c_LnlUnl.GetWindowText(LnlUnl);


			// Declenchement TWA
			//
			if (eqp->IsLink("A1") && eqp->GetChannelAfLevelReceived("A1") <= -20)
			{ // Start
				int time = eqp->GetAleTwa("A1");
				if (time != 999 && !twa_a)
				{
					twa_a = true;
					SetTimer(TWA_A, time*1000, NULL);
				}
				// Réarmement sur émission d'un message
				if  (twa_a && eqp->GetEmissionMsg((char*)LPCTSTR(str)) == TRUE)
					SetTimer(TWA_A, time*1000, NULL);

			} else
			{ // Stop
				if (twa_a)
				{
					KillTimer(TWA_A);
					twa_a = false;
				}
			}

			if (eqp->IsLink("B1") && eqp->GetChannelAfLevelReceived("B1") <= -20)
			{ // Start
				int time = eqp->GetAleTwa("B1");
				if (time != 999 && !twa_b)
				{
					twa_b = true;
					SetTimer(TWA_B, time*1000, NULL);
				}
				// Réarmement sur émission d'un message
				if  (twa_b && eqp->GetEmissionMsg((char*)LPCTSTR(str)) == TRUE)
					SetTimer(TWA_B, time*1000, NULL);
			} else
			{ // Stop
				if (twa_b)
				{
					KillTimer(TWA_B);
					twa_b = false;
				}
			}
			//
			// Fin TWA

			// Declenchement SOUNDING
			//
			if (eqp->GetAleParameter("A1").automatic_sounding == "ON")
			{
				if (etat == "LIS" || etat == "SCA")
				{
					// Si aucun sounding en cours
					if (!sound_a)
					{
						// On le lance
						sound_a = true;

						int val = eqp->GetAleSoundIndex("A1");
						val = eqp->GetRchSoundDelay("A1", val);
						if (val >= 0) SetTimer(SOUND_A, val*60000, NULL);
					}
				} else if (etat == "RCA" || etat == "CAL" || eqp->GetChannelState("A1") != "ACTIVE")
				{
					// On arrete le sounding en cours
					sound_a = false;
					KillTimer(SOUND_A);
				}
			}
			if (eqp->GetAleParameter("B1").automatic_sounding == "ON")
			{
				if (etat == "LIS" || etat == "SCA")
				{
					// Si aucun sounding en cours
					if (!sound_b)
					{
						// On le lance
						sound_b = true;

						int val = eqp->GetAleSoundIndex("B1");
						val = eqp->GetRchSoundDelay("B1", val);
						if (val >= 0) SetTimer(SOUND_B, val*60000, NULL);
					}
				} else if (etat == "RCA" || etat == "CAL" || eqp->GetChannelState("B1") != "ACTIVE")
				{
					// On arrete le sounding en cours
					sound_b = false;
					KillTimer(SOUND_B);
				}
			}
			//
			// Fin SOUNDING

			if (etat == "LKD" || etat == "LKG")
			{
				c_LnlUnl.GetWindowText(str);

				if (str != "Rompre")
				{
					c_LnlUnl.SetWindowText("Rompre");
				}


				c_Voie.GetLBText(c_Voie.GetCurSel(), str_voie);
				// FDI - 09/09/2015
				//if(eqp->GetChannelAfLevelReceived((char*)LPCTSTR(str_voie)) <= -20 && LnlUnl == "Rompre" && m_Amd==true)
				if(eqp->GetChannelAfLevelReceived((char*)LPCTSTR(str_voie)) <= -20 && LnlUnl == "Rompre" && m_Amd)
				{
					GetDlgItem(IDC_SEND_CHAT)->EnableWindow(TRUE);
				}
				else GetDlgItem(IDC_SEND_CHAT)->EnableWindow(FALSE);

			} else
			{
				c_LnlUnl.GetWindowText(str);

				if (str != "Etablir" && (etat == "SCA" || etat == "LIS"))
				{
					c_LnlUnl.SetWindowText("Etablir");
					c_SendChat.EnableWindow(FALSE);
				}
			}

			TModemDistant modem = eqp->GetModemDistant();

			// Message amd recu
			if (modem.amd_chat_recu != DEFAULT_STRING_VALUE)
			{
				UpdateData(TRUE);
				m_AmdMsgRecu = modem.amd_chat_recu.c_str();
				UpdateData(FALSE);
			}

			// Bouton effacer amd recu
			if (m_AmdMsgRecu != DEFAULT_STRING_VALUE)
				c_EffacerAmd.EnableWindow();
			else
				c_EffacerAmd.EnableWindow(FALSE);
		}
	break;
	case TWA_A:
		{
			eqp->CasserAppel("A1");
			KillTimer(TWA_A);
			twa_a = false;
		}
		break;
	case TWA_B:
		{
			eqp->CasserAppel("B1");
			KillTimer(TWA_B);
			twa_b = false;
		}
		break;
	case SOUND_A:
		{
			// Envoi du sound

			eqp->Sound("A1");
			sound_a = false;

			// Incrementation du sound et relance du timer pour le prochain
			KillTimer(SOUND_A);

		}
		break;
	case SOUND_B:
		{
			// Envoi du sound
			eqp->Sound("B1");
			sound_b = false;

			KillTimer(SOUND_B);

		}
		break;
	default:
		break;
	}

}

void CDlgTRC1752_MOD_CONF_ALE::OnEffacerAmd()
{
	UpdateData(TRUE);

	m_AmdMsgRecu = "";

	TModemDistant modem = eqp->GetModemDistant();
	modem.amd_chat_recu = DEFAULT_STRING_VALUE;
	eqp->SetModemDistant(modem);

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_ALE::OnSendChat()
{
	CString str;

	TModemDistant modem = eqp->GetModemDistant();
	c_Msg_Amd.GetWindowText(str);

	// FFT_1138
	modem.current_selfaddress = c_SelfAdresse.GetCurSel();
	// Fin FFT_1138

	modem.amd_chat = (char*)LPCTSTR(str);
	eqp->SetModemDistant(modem);

	c_Voie.GetLBText(c_Voie.GetCurSel(), str);

	eqp->RecevoirAmd((char*)LPCTSTR(str));
}


void CDlgTRC1752_MOD_CONF_ALE::OnKillfocusAmdMsg()
{
	CString str;
	c_Msg_Amd.GetWindowText(str);

	TModemDistant modem = eqp->GetModemDistant();

	if (eqp->ValidAleParameterAmdMessage((char*)LPCTSTR(str)) == FALSE)
	{
		AfxMessageBox("Le texte contient des caractères non valides");
		UpdateData(TRUE);
		str = "";
		modem.amd_chat = (char*)LPCTSTR(str);
		eqp->SetModemDistant(modem);
		c_Msg_Amd.SetWindowText(str);
		UpdateData(FALSE);
		return;
	}

	modem.amd_chat = (char*)LPCTSTR(str);

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnButtonSadp()
{
	CString str;
	c_SelfAdresse.GetWindowText(str);
	string adr = (char*)LPCTSTR(str);

	if (!eqp->ValidTableAddress(adr))
	{
		AfxMessageBox("Adresse incorrecte");
		return;
	}

	TModemDistant modem = eqp->GetModemDistant();

	modem.selfaddress.push_back(adr);
	modem.current_selfaddress = modem.selfaddress.size()-1;

	eqp->SetModemDistant(modem);

	UpdateData(TRUE);

	c_SelfAdresse.AddString(adr.c_str());
	c_SelfAdresse.SetCurSel(modem.current_selfaddress);

	UpdateData(FALSE);

}

void CDlgTRC1752_MOD_CONF_ALE::OnButtonSadm()
{
	int pos = c_SelfAdresse.GetCurSel();

	if (pos<0) return;
	if(c_SelfAdresse.GetCount()<=1)return;

	TModemDistant modem = eqp->GetModemDistant();

	modem.selfaddress.erase(modem.selfaddress.begin()+pos);
	modem.current_selfaddress = 0;

	eqp->SetModemDistant(modem);

	UpdateData(TRUE);

	c_SelfAdresse.DeleteString(pos);
	c_SelfAdresse.SetCurSel(0);

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_ALE::OnButtonStap()
{
	CString str;
	c_Stations.GetWindowText(str);
	string adr = (char*)LPCTSTR(str);

	if (!eqp->ValidTableAddress(adr))
	{
		AfxMessageBox("Adresse incorrecte");
		return;
	}

	TModemDistant modem = eqp->GetModemDistant();

	modem.stations.push_back(adr);
	modem.current_station = modem.stations.size()-1;

	eqp->SetModemDistant(modem);

	UpdateData(TRUE);

	c_Stations.AddString(adr.c_str());
	c_Stations.SetCurSel(modem.current_station);

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_ALE::OnButtonStam()
{
	int pos = c_Stations.GetCurSel();

	if (pos<0) return;
	if(c_Stations.GetCount()<=1)return;
	TModemDistant modem = eqp->GetModemDistant();

	modem.stations.erase(modem.stations.begin()+pos);
	modem.current_station = 0;

	eqp->SetModemDistant(modem);

	UpdateData(TRUE);

	c_Stations.DeleteString(pos);
	c_Stations.SetCurSel(0);

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_ALE::OnButtonNetp()
{
	CString str;
	c_Reseaux.GetWindowText(str);
	string adr = (char*)LPCTSTR(str);

	if (!eqp->ValidTableAddress(adr))
	{
		AfxMessageBox("Adresse incorrecte");
		return;
	}

	TModemDistant modem = eqp->GetModemDistant();

	modem.reseaux.push_back(adr);
	modem.current_reseau = modem.reseaux.size()-1;

	eqp->SetModemDistant(modem);

	UpdateData(TRUE);

	c_Reseaux.AddString(adr.c_str());
	c_Reseaux.SetCurSel(modem.current_reseau);

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_ALE::OnButtonNetm()
{
	int pos = c_Reseaux.GetCurSel();

	if (pos<0) return;
	if(c_Reseaux.GetCount()<=1)return;

	TModemDistant modem = eqp->GetModemDistant();

	modem.reseaux.erase(modem.reseaux.begin()+pos);
	modem.current_reseau = 0;

	eqp->SetModemDistant(modem);

	UpdateData(TRUE);

	c_Reseaux.DeleteString(pos);
	c_Reseaux.SetCurSel(0);

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_ALE::OnButtonLt0p()
{
	// TODO: Add your control notification handler code here
	CString str;
	c_LT0.GetWindowText(str);
	string adr = (char*)LPCTSTR(str);

	if (!eqp->ValidTableLt0(adr))
	{
		AfxMessageBox("Non incorrecte");
		return;
	}

	TModemDistant modem = eqp->GetModemDistant();

	modem.LT0.push_back(adr);
	modem.current_LT0 = modem.LT0.size()-1;

	eqp->SetModemDistant(modem);

	UpdateData(TRUE);

	c_LT0.AddString(adr.c_str());
	c_LT0.SetCurSel(modem.current_LT0);

	UpdateData(FALSE);

}

void CDlgTRC1752_MOD_CONF_ALE::OnButtonLt0m()
{
	// TODO: Add your control notification handler code here
	int pos = c_LT0.GetCurSel();

	if (pos<0) return;
	if(c_LT0.GetCount()<=1)return;
	TModemDistant modem = eqp->GetModemDistant();

	modem.LT0.erase(modem.LT0.begin()+pos);
	modem.current_LT0 = 0;

	eqp->SetModemDistant(modem);

	UpdateData(TRUE);

	c_LT0.DeleteString(pos);
	c_LT0.SetCurSel(0);

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_ALE::OnButtonKeyp()
{
	// TODO: Add your control notification handler code here
	CString str;
	c_Key.GetWindowText(str);
	string adr = (char*)LPCTSTR(str);

	if (!eqp->ValidTableKey(adr))
	{
		AfxMessageBox("Clé incorrecte");
		return;
	}

	TModemDistant modem = eqp->GetModemDistant();

	modem.Key.push_back(adr);
	modem.current_Key = modem.Key.size()-1;

	eqp->SetModemDistant(modem);

	UpdateData(TRUE);

	c_Key.AddString(adr.c_str());
	c_Key.SetCurSel(modem.current_Key);

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_ALE::OnButtonKeym()
{
	// TODO: Add your control notification handler code here
	int pos = c_Key.GetCurSel();

	if (pos<0) return;
	if(c_Key.GetCount()<=1)return;
	TModemDistant modem = eqp->GetModemDistant();

	modem.Key.erase(modem.Key.begin()+pos);
	modem.current_Key = 0;

	eqp->SetModemDistant(modem);

	UpdateData(TRUE);

	c_Key.DeleteString(pos);
	c_Key.SetCurSel(0);

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_ALE::OnSelchangeComboLt0()
{
	// TODO: Add your control notification handler code here
	TModemDistant modem = eqp->GetModemDistant();

	modem.current_LT0 = c_LT0.GetCurSel();

	eqp->SetModemDistant(modem);

}

void CDlgTRC1752_MOD_CONF_ALE::OnSelchangeComboLp()
{
	// TODO: Add your control notification handler code here
	TModemDistant modem = eqp->GetModemDistant();

	modem.current_LP = c_LP.GetCurSel();

	eqp->SetModemDistant(modem);
}

void CDlgTRC1752_MOD_CONF_ALE::OnSelchangeCOMBOKey()
{
	// TODO: Add your control notification handler code here
	TModemDistant modem = eqp->GetModemDistant();

	modem.current_Key = c_Key.GetCurSel();

	eqp->SetModemDistant(modem);
}
