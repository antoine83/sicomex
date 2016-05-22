// DlgTRC1752_MOD_PROG_INTF_TC.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_INTF_TC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_TC dialog


CDlgTRC1752_MOD_PROG_INTF_TC::CDlgTRC1752_MOD_PROG_INTF_TC(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_INTF_TC::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_INTF_TC)
	m_LiaisonTc = 4;		//IA3
	m_DebitTc = 5;			//4800
	m_NbBitDonnees = 1;		//7
	m_Parite = 0;			//Pair
	m_NbBitStop = 1;		//1
	m_Type = 0;				//V28
	m_AdresseRadio = 0;		//0
	m_Radio = 0;			//NORAD
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_INTF_TC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_INTF_TC)
	DDX_Control(pDX, IDC_ADRESSE_RADIO, c_AdresseRadio);
	DDX_Control(pDX, IDC_STATIC_ADRESSE_RADIO, t_AdresseRadio);
	DDX_Control(pDX, IDC_STATIC_RADIO, t_Radio);
	DDX_Control(pDX, IDC_RADIO, c_Radio);
	DDX_Control(pDX, IDC_ADRESSE_RADIO_SPIN, s_AdresseRadio);
	DDX_Control(pDX, IDC_TYPE, c_Type);
	DDX_Control(pDX, IDC_NB_BIT_STOP, c_NbBitStop);
	DDX_Control(pDX, IDC_PARITE, c_Parite);
	DDX_Control(pDX, IDC_NB_BIT_DONNEES, c_NbBitDonnees);
	DDX_Control(pDX, IDC_DEBIT_TC, c_DebitTc);
	DDX_Control(pDX, IDC_TC, c_LiaisonTc);
	DDX_CBIndex(pDX, IDC_TC, m_LiaisonTc);
	DDX_CBIndex(pDX, IDC_DEBIT_TC, m_DebitTc);
	DDX_CBIndex(pDX, IDC_NB_BIT_DONNEES, m_NbBitDonnees);
	DDX_CBIndex(pDX, IDC_PARITE, m_Parite);
	DDX_CBIndex(pDX, IDC_NB_BIT_STOP, m_NbBitStop);
	DDX_CBIndex(pDX, IDC_TYPE, m_Type);
	DDX_Text(pDX, IDC_ADRESSE_RADIO, m_AdresseRadio);
	DDV_MinMaxInt(pDX, m_AdresseRadio, 0, 999);
	DDX_CBIndex(pDX, IDC_RADIO, m_Radio);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_INTF_TC, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_INTF_TC)
	ON_CBN_SELCHANGE(IDC_TC, OnSelchangeTc)
	ON_WM_TIMER()
	ON_NOTIFY(UDN_DELTAPOS, IDC_ADRESSE_RADIO_SPIN, OnDeltaposAdresseRadioSpin)
	ON_EN_KILLFOCUS(IDC_ADRESSE_RADIO, OnKillfocusAdresseRadio)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_TC message handlers

BOOL CDlgTRC1752_MOD_PROG_INTF_TC::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Initialisation de la plage d'adresses radio

	s_AdresseRadio.SetRange(0, 999);

	// Initialisation type
	initTypeInterfaceIA();

	//Initialisation de l'affichage
	AffichageRadio();




	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTRC1752_MOD_PROG_INTF_TC::OnSelchangeTc()
{
	// Affichage des equipement radio en fonction du type de telecommande // V3.0.2b
	initTypeRadio(c_LiaisonTc.GetCurSel());

	// Affichage en fonction du type de télécommande
	AffichageRadio();

	// Affichage des informations de télécommande
	AffichageConfigurationTC();
}


// *********************************************
// Affichage en fonction du type de télécommande
// *********************************************
void CDlgTRC1752_MOD_PROG_INTF_TC::AffichageRadio()
{
	// Positionnement en fonction du type de télécommande
	CString str;

	int nIndex = c_LiaisonTc.GetCurSel();

	if (nIndex != LB_ERR)
	{
		c_LiaisonTc.GetLBText(nIndex, str);

		if (strncmp(str, "TC", 2) == 0)				//TC1....TC4 et TC
		{
			initTypeInterfaceTC();
			t_AdresseRadio.ShowWindow(false);
			s_AdresseRadio.ShowWindow(false);
			c_AdresseRadio.ShowWindow(false);
			t_Radio.ShowWindow(false);
			c_Radio.ShowWindow(false);
		}
		else
		{
			initTypeInterfaceIA();					//IA3...IA6
			t_AdresseRadio.ShowWindow(true);
			s_AdresseRadio.ShowWindow(true);
			c_AdresseRadio.ShowWindow(true);
			t_Radio.ShowWindow(true);
			c_Radio.ShowWindow(true);
		}

		c_Type.SetCurSel(0);
	}
}

void CDlgTRC1752_MOD_PROG_INTF_TC::Valide()
{
	CString str, str_tc;

	// Changement impossible quand l'équipement est en Distant
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		UpdateData(FALSE);
		return;
	}

	UpdateData(TRUE);

	//******************************************
	// Mémorisation de la configuration en cours
	//******************************************
	//AUX_INTERFACES_CONFIGURATIONS				: IAx....	: TAuxInterfaceConfiguration/GetAuxInterfaceConfiguration
	//LOCAL_REMOTE_INTERFACES_CONFIGURATIONS	: TCx...	: TLocalRemoteInterfaceConfiguration/GetLocalRemoteInterfaceConfiguration

	c_LiaisonTc.GetLBText(c_LiaisonTc.GetCurSel(), str_tc);

	switch(c_LiaisonTc.GetCurSel())
	{
		case 0:			//TC4...TC1 et TC
		case 1:
		case 2:
		case 3:
		case 8:
			{
				TLocalRemoteInterfaceConfiguration conf_courante = eqp->GetLocalRemoteInterfaceConfiguration((char *)LPCTSTR(str_tc));

				// electrical_characteristics
				c_Type.GetLBText(c_Type.GetCurSel(), str);
				conf_courante.electrical_characteristics = str;

				// baudrate
				c_DebitTc.GetLBText(c_DebitTc.GetCurSel(), str);
				conf_courante.baudrate = atoi(str);

				// characters_length
				c_NbBitDonnees.GetLBText(c_NbBitDonnees.GetCurSel(), str);
				conf_courante.characters_length = atoi(str);

				// characters_parity
				// parity // PAIR/IMPAIR/SANS
				switch(c_Parite.GetCurSel())
				{
				case 0:
					conf_courante.characters_parity = "PAIR";
					break;
				case 1:
					conf_courante.characters_parity = "IMPAIR";
					break;
				case 2:
					conf_courante.characters_parity = "SANS";
					break;
				default:
					conf_courante.characters_parity = "SANS";
					break;
				}

				// number_stop_bits
				c_NbBitStop.GetLBText(c_NbBitStop.GetCurSel(), str);
				conf_courante.number_stop_bits = atoi(str);

				eqp->SetLocalRemoteInterfaceConfiguration((char *)LPCTSTR(str_tc), conf_courante);
				break;
			}
		case 4:			//IA3...IA6
		case 5:
		case 6:
		case 7:
			{
				TAuxInterfaceConfiguration conf_courante = eqp->GetAuxInterfaceConfiguration((char *)LPCTSTR(str_tc));

				// electrical_characteristics
				c_Type.GetLBText(c_Type.GetCurSel(), str);
				conf_courante.electrical_characteristics = str;

				// baudrate
				c_DebitTc.GetLBText(c_DebitTc.GetCurSel(), str);
				conf_courante.baudrate = atoi(str);

				// character_length
				c_NbBitDonnees.GetLBText(c_NbBitDonnees.GetCurSel(), str);
				conf_courante.character_length = atoi(str);

				// character_parity
				// parity // PAIR/IMPAIR/SANS
				switch(c_Parite.GetCurSel())
				{
				case 0:
					conf_courante.character_parity = "PAIR";
					break;
				case 1:
					conf_courante.character_parity = "IMPAIR";
					break;
				case 2:
					conf_courante.character_parity = "SANS";
					break;
				default:
					conf_courante.character_parity = "SANS";
					break;
				}

				// number_stop_bits
				c_NbBitStop.GetLBText(c_NbBitStop.GetCurSel(), str);
				conf_courante.number_stop_bits = atoi(str);

				// radio_address
				conf_courante.radio_address = m_AdresseRadio;

				// equipment_type
				c_Radio.GetLBText(c_Radio.GetCurSel(), str);
				conf_courante.equipment_type = str;


				eqp->SetAuxInterfaceConfiguration((char *)LPCTSTR(str_tc), conf_courante);
				break;
			}
		default:
			break;
	}

	UpdateData(FALSE);
}

//************************************************************************
//Raz de la sélection de l'interface TC sur ESC ou clique sur l'onglet Ops
//************************************************************************
void CDlgTRC1752_MOD_PROG_INTF_TC::razChoixInterfaceTC()
{
	c_LiaisonTc.SetCurSel(4);

	OnSelchangeTc();
}

// ******************************************
// Affichage des informations de télécommande
// ******************************************
void CDlgTRC1752_MOD_PROG_INTF_TC::AffichageConfigurationTC()
{
	// TAuxInterfaceConfiguration/TLocalRemoteInterfaceConfiguration
	//**************************************************************
	CString str_tc;

	//AUX_INTERFACES_CONFIGURATIONS : IAx.... : TAuxInterfaceConfiguration/GetAuxInterfaceConfiguration
	//LOCAL_REMOTE_INTERFACES_CONFIGURATIONS : TCx... : TLocalRemoteInterfaceConfiguration/GetLocalRemoteInterfaceConfiguration

	c_LiaisonTc.GetLBText(c_LiaisonTc.GetCurSel(), str_tc);

	switch(c_LiaisonTc.GetCurSel())
	{
		case 0:			//TC4...TC1 et TC
		case 1:
		case 2:
		case 3:
		case 8:
			{
				TLocalRemoteInterfaceConfiguration conf_courante = eqp->GetLocalRemoteInterfaceConfiguration((char *)LPCTSTR(str_tc));
				AffichageConfigurationTC(conf_courante);
				break;
			}
		case 4:			//IA3...IA6
		case 5:
		case 6:
		case 7:
			{
				TAuxInterfaceConfiguration conf_courante = eqp->GetAuxInterfaceConfiguration((char *)LPCTSTR(str_tc));
				AffichageConfigurationIA(conf_courante);
				break;
			}
		default:
			break;
	}
	//*************************************************************************************************
}
// **********************************************************
// Gestion du timer
// **********************************************************
void CDlgTRC1752_MOD_PROG_INTF_TC::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnTimer(nIDEvent);

	AffichageConfigurationTC();
}

void CDlgTRC1752_MOD_PROG_INTF_TC::marcheTimer()
{
	if (eqp->GetMode() == false) return;		//il faut etre en distant

	m_timerTC = SetTimer(1,2000,NULL);
}
void CDlgTRC1752_MOD_PROG_INTF_TC::arretTimer()
{
	KillTimer(m_timerTC);
}


//Affichage des informations
void CDlgTRC1752_MOD_PROG_INTF_TC::AffichageConfigurationTC(TLocalRemoteInterfaceConfiguration conf_courante)
{
	CString str;

	//LOCAL_REMOTE_INTERFACES_CONFIGURATIONS : TCx... : TLocalRemoteInterfaceConfiguration/GetLocalRemoteInterfaceConfiguration

	// electrical_characteristics
	c_Type.SelectString(0, conf_courante.electrical_characteristics.c_str());

	// baudrate
	if (conf_courante.baudrate<1000)
	{
		str.Format(_T("%03d"), conf_courante.baudrate);
	}else
	{
		str.Format(_T("%04d"), conf_courante.baudrate);
	}

	if (conf_courante.baudrate<100)
		str.Format(_T("%02d"), conf_courante.baudrate);

	c_DebitTc.SelectString(0, (LPCTSTR)str);

	//characters_length
	str.Format(_T("%01d"), conf_courante.characters_length);
	c_NbBitDonnees.SelectString(0, (LPCTSTR)str);

	//characters_parity
	c_Parite.SelectString(0, conf_courante.characters_parity.substr(0,1).c_str());

	//number_stop_bits
	str.Format(_T("%01d"), conf_courante.number_stop_bits);
	c_NbBitStop.SelectString(0, (LPCTSTR)str);


	UpdateData(TRUE);
}

void CDlgTRC1752_MOD_PROG_INTF_TC::AffichageConfigurationIA(TAuxInterfaceConfiguration conf_courante)
{
	CString str;

	//AUX_INTERFACES_CONFIGURATIONS : IAx.... : TAuxInterfaceConfiguration/GetAuxInterfaceConfiguration

	// electrical_characteristics
	c_Type.SelectString(0, conf_courante.electrical_characteristics.c_str());

	// baudrate
	if (conf_courante.baudrate<1000)
	{
		str.Format(_T("%03d"), conf_courante.baudrate);
	}else
	{
		str.Format(_T("%04d"), conf_courante.baudrate);
	}

	if (conf_courante.baudrate<100)
		str.Format(_T("%02d"), conf_courante.baudrate);

	c_DebitTc.SelectString(0, (LPCTSTR)str);

	//character_length
	str.Format(_T("%01d"), conf_courante.character_length);
	c_NbBitDonnees.SelectString(0, (LPCTSTR)str);

	//character_parity
	c_Parite.SelectString(0, conf_courante.character_parity.substr(0,1).c_str());

	//number_stop_bits
	str.Format(_T("%01d"), conf_courante.number_stop_bits);
	c_NbBitStop.SelectString(0, (LPCTSTR)str);

	// equipment_type
	c_Radio.SelectString(0, conf_courante.equipment_type.c_str());


	UpdateData(TRUE);

	// radio_address
	m_AdresseRadio = conf_courante.radio_address;

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_PROG_INTF_TC::OnDeltaposAdresseRadioSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	/*
	Adresse radio entre 0 et 999
	*/
	if (pNMUpDown->iDelta > 0)  m_AdresseRadio += 1;
		else m_AdresseRadio -= 1;


	if ( m_AdresseRadio > 999 )
	{
		AfxMessageBox("Adresse radio entre 0 et 999 !");
		m_AdresseRadio = 999;
	}

	if ( m_AdresseRadio < 0)
	{
		AfxMessageBox("Adresse radio entre 0 et 999 !");
		m_AdresseRadio = 0;
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_INTF_TC::OnKillfocusAdresseRadio()
{
	UpdateData(TRUE);

	if (m_AdresseRadio > 999 || m_AdresseRadio < 0)
	{
		m_AdresseRadio = 0;
		UpdateData(FALSE);

	}

}

// Mise en place du type d'interface suivant le type de télécommande
void CDlgTRC1752_MOD_PROG_INTF_TC::initTypeInterfaceTC()
{
	//RAZ de la liste
	c_Type.ResetContent();

	//Initialisation
	c_Type.AddString("V28");
	c_Type.AddString("V11");
	c_Type.AddString("V11_DA");

}
void CDlgTRC1752_MOD_PROG_INTF_TC::initTypeInterfaceIA()
{
	//RAZ de la liste
	c_Type.ResetContent();

	//Initialisation
	c_Type.AddString("V28");
	c_Type.AddString("EIA485");
	c_Type.AddString("EIA485_DA");
	c_Type.AddString("V11");
	c_Type.AddString("V11_DA");
}

// V3.0.2b
//***************************************************************
// Affichage des equipement radio en fonction du type d'interface
//***************************************************************
void CDlgTRC1752_MOD_PROG_INTF_TC::initTypeRadio(int typeInterface)
{
	//RAZ de la liste
	c_Radio.ResetContent();

	switch(typeInterface)
	{
		// IA3-IA5
	case 4:
	case 6:
		c_Radio.AddString("NORAD");
		c_Radio.AddString("TMR6200");	//Tx/Rx
		c_Radio.AddString("TMR6205");	//Tx/Rx
		c_Radio.AddString("TMR6209");	//Tx/Rx
		c_Radio.AddString("TMR6211");	//Tx/Rx
		c_Radio.AddString("TMR6300");	//Tx
		c_Radio.AddString("TMR6301");	//Tx
		c_Radio.AddString("TMR6309");	//Tx
		c_Radio.AddString("TMR5200");	//Tx/Rx
		c_Radio.AddString("TMR5201");	//Tx/Rx
		c_Radio.AddString("TMR5300");	//Tx
		c_Radio.AddString("TMR5309");	//Tx
		c_Radio.AddString("TRC1232");	//Tx
		c_Radio.AddString("TRC1242");	//Tx
		c_Radio.AddString("TRC1332");	//Tx
		c_Radio.AddString("TRC1352");	//Tx
		c_Radio.AddString("TRC109");	//Tx
		c_Radio.AddString("TRC110");	//Tx
		c_Radio.AddString("TRC1237");	//Tx
		c_Radio.AddString("XK2100");	//Tx/Rx
		c_Radio.AddString("XK2500");	//Tx/Rx
		c_Radio.AddString("TESTRAD");
		break;
		// IA4-IA6
	case 5:
	case 7:
		c_Radio.AddString("NORAD");
		c_Radio.AddString("TMR6100");	//Rx
		c_Radio.AddString("TMR6200");	//Tx/Rx
		c_Radio.AddString("TMR6205");	//Tx/Rx
		c_Radio.AddString("TMR6209");	//Tx/Rx
		c_Radio.AddString("TMR6211");	//Tx/Rx
		c_Radio.AddString("TMR5100");	//Rx
		c_Radio.AddString("TMR5200");	//Tx/Rx
		c_Radio.AddString("TMR5201");	//Tx/Rx
		c_Radio.AddString("TRC241");	//Rx
		c_Radio.AddString("TRC1241");	//Rx
		c_Radio.AddString("XK2100");	//Tx/Rx
		c_Radio.AddString("XK2500");	//Tx/Rx
		c_Radio.AddString("TESTRAD");
		break;
	default:
		c_Radio.AddString("NORAD");
		break;
	}
}

void CDlgTRC1752_MOD_PROG_INTF_TC::miseajourInterfaceTC()
{
	OnSelchangeTc();
}

/*

*/
