// DlgTRC1752_MOD_PROG_INTF_LIAS.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_INTF_LIAS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_LIAS dialog

/*Ce menu permet de définir des configurations relatives sur liaisons séries qui correspondent aux
interfaces de données.*/


CDlgTRC1752_MOD_PROG_INTF_LIAS::CDlgTRC1752_MOD_PROG_INTF_LIAS(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_INTF_LIAS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_INTF_LIAS)
	m_LiasDebitEmi = 10;
	m_LiasDebitRec = 10;
	m_LiasDpe = 0;
	m_LiasHEmi = 0;
	m_LiasPol = 0;
	m_LiasStab = 0;
	m_LiasSynchro = 0;
	m_LiasConf = 0;
	m_LiasDpe_A = 0;
	m_LiasInt_A = 1;
	m_LiasInt_S = 1;
	m_LiasStab_A = 0;
	m_LiasStab_S = 0;
	m_NbBits = 0;
	m_NbStop = 0;
	m_Parite = 0;
	m_LiasTypeElec = 0;
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_INTF_LIAS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_INTF_LIAS)
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_TYPE, c_LiasTypeElec);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_SYNCHRO, c_LiasSynchro);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_STAB_A, c_LiasStab_A);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_STAB_S, c_LiasStab_S);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_POL, c_LiasPol);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_INT_S, c_LiasIntS);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_INT_A, c_LiasIntA);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_H_EM, c_LiasHEmi);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_DPE_A, c_LiasDpeA);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_DPE, c_LiasDpe);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_DEBIT_R, c_LiasDebitRec);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_DEBIT_E, c_LiasDebitEmi);
	DDX_Control(pDX, IDC_PROG_INTF_LIAS_CONF, c_LiasConf);
	DDX_Control(pDX, IDC_PARITE, c_Parite);
	DDX_Control(pDX, IDC_NB_STOP, c_NbStop);
	DDX_Control(pDX, IDC_NB_BITS, c_NbBits);
	DDX_Control(pDX, IDC_STATIC_DPE_A, m_Dpe_A_Txt);
	DDX_Control(pDX, IDC_STATIC_DPE, m_Dpe_S_Txt);
	DDX_Control(pDX, IDC_STATIC_H_EM, m_H_Em_Txt);
	DDX_Control(pDX, IDC_STATIC_INT_S, m_Int_S_Txt);
	DDX_Control(pDX, IDC_STATIC_STAB_S, m_Stab_Txt);
	DDX_Control(pDX, IDC_STATIC_BITS, m_Bits_Txt);
	DDX_Control(pDX, IDC_STATIC_STOP, m_Stop_Txt);
	DDX_Control(pDX, IDC_STATIC_PARITE, m_Parite_Txt);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_DEBIT_E, m_LiasDebitEmi);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_DEBIT_R, m_LiasDebitRec);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_DPE, m_LiasDpe);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_H_EM, m_LiasHEmi);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_POL, m_LiasPol);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_SYNCHRO, m_LiasSynchro);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_CONF, m_LiasConf);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_DPE_A, m_LiasDpe_A);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_INT_A, m_LiasInt_A);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_INT_S, m_LiasInt_S);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_STAB_A, m_LiasStab_A);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_STAB_S, m_LiasStab_S);
	DDX_CBIndex(pDX, IDC_NB_BITS, m_NbBits);
	DDX_CBIndex(pDX, IDC_NB_STOP, m_NbStop);
	DDX_CBIndex(pDX, IDC_PARITE, m_Parite);
	DDX_CBIndex(pDX, IDC_PROG_INTF_LIAS_TYPE, m_LiasTypeElec);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_INTF_LIAS, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_INTF_LIAS)
	ON_CBN_SELCHANGE(IDC_PROG_INTF_LIAS_DEBIT_E, OnSelchangeProgIntfLiasDebitE)
	ON_CBN_SELCHANGE(IDC_PROG_INTF_LIAS_H_EM, OnSelchangeProgIntfLiasHEm)
	ON_CBN_SELCHANGE(IDC_PROG_INTF_LIAS_SYNCHRO, OnSelchangeProgIntfLiasSynchro)
	ON_CBN_SELCHANGE(IDC_PROG_INTF_LIAS_CONF, OnSelchangeProgIntfLiasConf)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_LIAS message handlers

void CDlgTRC1752_MOD_PROG_INTF_LIAS::OnSelchangeProgIntfLiasDebitE()
{
	/*Lorsque l’utilisateur choisit un débit en émission, le même débit est recopié en réception. Pour
	programmer des débits différents, l’utilisateur doit agir sur le paramètre débit de la voie réception.
	*/
	int nIndex = c_LiasDebitEmi.GetCurSel();
	if (nIndex != LB_ERR)
		c_LiasDebitRec.SetCurSel(nIndex);

	//Test sur le débit
	if (TestDebit())
	{
		//Prise en compte des modifications
	}
	else
	{
		//Non prise en compte des modifications.
	}

}

BOOL CDlgTRC1752_MOD_PROG_INTF_LIAS::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitSynchrone(true);
	//InitAsynchrone(false);


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//Test du débit pour les horloges
bool CDlgTRC1752_MOD_PROG_INTF_LIAS::TestDebit()
{
	bool res = true;

	//En mode synchrone sans horloge, le débit de l’interface série est limité à 2400 bits/s.

	if (c_LiasSynchro.GetCurSel() == 0 && c_LiasHEmi.GetCurSel() == 2 && (c_LiasDebitEmi.GetCurSel() > 10 || c_LiasDebitRec.GetCurSel() > 10))
	{
		AfxMessageBox("En mode synchrone sans horloge, le débit de l’interface série est limité à 2400 bits/s.");
		c_LiasDebitEmi.SetCurSel(10);
		c_LiasDebitRec.SetCurSel(10);
		res = false;
	}
	return res;
}

//--------------------------------
//Changement de l'horloge Emission
//--------------------------------
void CDlgTRC1752_MOD_PROG_INTF_LIAS::OnSelchangeProgIntfLiasHEm()
{
	int tmpSel = c_LiasHEmi.GetCurSel();

	//Test sur le débit
	if (TestDebit())
	{
		//Prise en compte des modifications
	}
	else
	{
		//Non prise en compte des modifications.
		c_LiasHEmi.SetCurSel(tmpSel);
	}
}

//-----------------------------
//Changement du type de liaison
//-----------------------------
void CDlgTRC1752_MOD_PROG_INTF_LIAS::OnSelchangeProgIntfLiasSynchro()
{

	int tmpSel = c_LiasSynchro.GetCurSel();

	if (tmpSel == 0)		//Synchrone
	{
		InitSynchrone(TRUE);
		//InitAsynchrone(false);

	}
	else
	{
		InitSynchrone(FALSE);
		//InitAsynchrone(true);
		c_LiasDpeA.SetCurSel(0);
		c_LiasIntA.SetCurSel(1);
		c_LiasStab_A.SetCurSel(0);
		c_NbBits.SetCurSel(0);
		c_NbStop.SetCurSel(0);
		c_Parite.SetCurSel(0);
	}

	//Test sur le débit
	if (TestDebit())
	{
		//Prise en compte des modifications
	}
	else
	{
		//Non prise en compte des modifications.
		c_LiasSynchro.SetCurSel(tmpSel);
	}

}


// Affiche_Cache les objets Synchrone suivant le type de liaison
void CDlgTRC1752_MOD_PROG_INTF_LIAS::InitSynchrone(bool affiche)
{
	//Raz de la liste
	c_LiasTypeElec.ResetContent();

	//Stabilité du terminal
	m_Stab_Txt.ShowWindow(affiche);
	c_LiasStab_S.ShowWindow(affiche);
	c_LiasIntS.ShowWindow(affiche);
	m_Int_S_Txt.ShowWindow(affiche);
	m_Dpe_S_Txt.ShowWindow(affiche);
	c_LiasDpe.ShowWindow(affiche);
	m_H_Em_Txt.ShowWindow(affiche);
	c_LiasHEmi.ShowWindow(affiche);
	//Données pour Ashynchrone
	m_Bits_Txt.ShowWindow(affiche);
	m_Stop_Txt.ShowWindow(affiche);
	m_Parite_Txt.ShowWindow(affiche);
	c_Parite.ShowWindow(affiche);
	c_NbStop.ShowWindow(affiche);
	c_NbBits.ShowWindow(affiche);

	//Initialisation de la liste suivant la synchronisation
	c_LiasTypeElec.AddString("V28");
	c_LiasTypeElec.AddString("EIA530");
	c_LiasTypeElec.AddString("530_DA");
	if (affiche == TRUE)
		c_LiasTypeElec.AddString("530_HA");
	c_LiasTypeElec.AddString("V10");
	c_LiasTypeElec.AddString("V11");
	c_LiasTypeElec.AddString("V11_DA");
	if (affiche == TRUE)
		c_LiasTypeElec.AddString("V11_HA");

	c_LiasTypeElec.SetCurSel(0);

	InitAsynchrone(!affiche);

}

// Affiche_Cache les objets Asynchrone suivant le type de liaison
void CDlgTRC1752_MOD_PROG_INTF_LIAS::InitAsynchrone(bool affiche)
{
	//Stabilité du terminal
	c_LiasStab_A.ShowWindow(affiche);
	c_LiasIntA.ShowWindow(affiche);
	c_LiasDpeA.ShowWindow(affiche);
	m_Dpe_A_Txt.ShowWindow(affiche);
	//Données pour Ashynchrone
	m_Bits_Txt.ShowWindow(affiche);
	m_Stop_Txt.ShowWindow(affiche);
	m_Parite_Txt.ShowWindow(affiche);
	c_Parite.ShowWindow(affiche);
	c_NbStop.ShowWindow(affiche);
	c_NbBits.ShowWindow(affiche);

}

void CDlgTRC1752_MOD_PROG_INTF_LIAS::Valide()
{
	// Changement impossible quand l'équipement est en Distant
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		UpdateData(FALSE);
		return;
	}

	UpdateData(TRUE);
	//***********************
	// InterfaceConfiguration
	// **********************
	CString str;

	TInterfaceConfiguration conf_courante = eqp->GetInterfaceConfiguration(INTERFACES_CONFIGURATION[c_LiasConf.GetCurSel()]);

	// type
	c_LiasSynchro.GetLBText(c_LiasSynchro.GetCurSel(), str);
	conf_courante.type = str;

	// electrical_characteristics
	c_LiasTypeElec.GetLBText(c_LiasTypeElec.GetCurSel(), str);
	conf_courante.electrical_characteristics = str;

	// transmission_baudrate
	c_LiasDebitEmi.GetLBText(c_LiasDebitEmi.GetCurSel(), str);
	if (str == "AUTO")
		conf_courante.transmission_baudrate = 0;
	else
		conf_courante.transmission_baudrate = atoi(str);

	// reception_baudrate
	c_LiasDebitRec.GetLBText(c_LiasDebitRec.GetCurSel(), str);
	if (str == "AUTO")
		conf_courante.reception_baudrate = 0;
	else
		conf_courante.reception_baudrate = atoi(str);

	// direction
	c_LiasHEmi.GetLBText(c_LiasHEmi.GetCurSel(), str);
	conf_courante.direction = str;

	// validity_time
	if (c_LiasSynchro.GetCurSel() == 0)		//SYNCHRONE
		c_LiasIntS.GetLBText(c_LiasIntS.GetCurSel(), str);
	else
		c_LiasIntA.GetLBText(c_LiasIntA.GetCurSel(), str);

	conf_courante.validity_time = str;


	// binary_integrity
	conf_courante.binary_integrity = "GRANDE";
	if (c_LiasSynchro.GetCurSel() == 0)		//SYNCHRONE
	{
		if (c_LiasStab_S.GetCurSel() == 1)
			conf_courante.binary_integrity = "PETITE";
	}
	else
	{
		if (c_LiasStab_A.GetCurSel() == 1)
			conf_courante.binary_integrity = "PETITE";
	}


	// polarity
	c_LiasPol.GetLBText(c_LiasPol.GetCurSel(), str);
	conf_courante.polarity = str;

	// handshake
	if (c_LiasSynchro.GetCurSel() == 0)		//SYNCHRONE
	{
		c_LiasDpe.GetLBText(c_LiasDpe.GetCurSel(), str);
		if (c_LiasDpe.GetCurSel() == 0)
			conf_courante.handshake = "DPE";
		else
			conf_courante.handshake = str;
	}
	else
	{
		c_LiasDpeA.GetLBText(c_LiasDpeA.GetCurSel(), str);
		if (c_LiasDpeA.GetCurSel() == 0)
			conf_courante.handshake = "DPE";
		else
			conf_courante.handshake = str;
	}

	// Paramètres d'une liaison asynchrone
	if (c_LiasSynchro.GetCurSel() == 1)		//ASYNCHRONE
	{
		//character_length
		c_NbBits.GetLBText(c_NbBits.GetCurSel(), str);
		conf_courante.character_length = atoi(str);

		//parity // PAIR/IMPAIR/SANS
		switch(c_Parite.GetCurSel())
		{
		case 0:
			conf_courante.parity = "SANS";
			break;
		case 1:
			conf_courante.parity = "IMPAIR";
			break;
		case 2:
			conf_courante.parity = "PAIR";
			break;
		default:
			conf_courante.parity = "SANS";
			break;
		}

		// number_stop_bits
		c_NbStop.GetLBText(c_NbStop.GetCurSel(), str);
		conf_courante.number_stop_bits = atoi(str);
	}

	//**************************************************************************
	//Mise en place dans la structure
	//**************************************************************************
	eqp->SetInterfaceConfiguration(INTERFACES_CONFIGURATION[c_LiasConf.GetCurSel()], conf_courante);

	UpdateData(FALSE);
	//*******************************************************************************************************************

}

void CDlgTRC1752_MOD_PROG_INTF_LIAS::OnSelchangeProgIntfLiasConf()
{

	// Mise à jour
	ModificationConfiguration();
}

// *************************************************
// Affichage suite à modification de la configuration
// *************************************************
void CDlgTRC1752_MOD_PROG_INTF_LIAS::ModificationConfiguration()
{
	CString str;

	TInterfaceConfiguration conf_courante = eqp->GetInterfaceConfiguration(INTERFACES_CONFIGURATION[c_LiasConf.GetCurSel()]);

	// Type
	c_LiasSynchro.SelectString(0, conf_courante.type.c_str());

	InitSynchrone(TRUE);
	if (conf_courante.type == "ASYNCHRONE")
		InitSynchrone(FALSE);

	// electrical_characteristics
	c_LiasTypeElec.SelectString(0, conf_courante.electrical_characteristics.c_str());

	// transmission_baudrate
	if (conf_courante.transmission_baudrate != 0)
	{
		if (conf_courante.transmission_baudrate<1000)
		{
			str.Format(_T("%03d"), conf_courante.transmission_baudrate);
		}else
		{
			str.Format(_T("%04d"), conf_courante.transmission_baudrate);
		}

		if (conf_courante.transmission_baudrate<100)
			str.Format(_T("%02d"), conf_courante.transmission_baudrate);

		c_LiasDebitEmi.SelectString(0, (LPCTSTR)str);
	}
	else
		c_LiasDebitEmi.SelectString(0, "AUTO");

	// reception_baudrate
	if (conf_courante.reception_baudrate != 0)
	{
		if (conf_courante.reception_baudrate<1000)
		{
			str.Format(_T("%03d"), conf_courante.reception_baudrate);
		}else
		{
			str.Format(_T("%04d"), conf_courante.reception_baudrate);
		}

		if (conf_courante.reception_baudrate<100)
			str.Format(_T("%02d"), conf_courante.reception_baudrate);

		c_LiasDebitRec.SelectString(0, (LPCTSTR)str);
	}
	else
		c_LiasDebitRec.SelectString(0, "AUTO");

	// direction
	c_LiasHEmi.SelectString(0, conf_courante.direction.c_str());

	// validity_time
	if(conf_courante.type == "SYNCHRONE")
		c_LiasIntS.SelectString(0, conf_courante.validity_time.c_str());
	else
		c_LiasIntA.SelectString(0, conf_courante.validity_time.c_str());

	// binary_integrity
	if (conf_courante.type == "SYNCHRONE")
	{
		c_LiasStab_S.SetCurSel(0);
		if (conf_courante.binary_integrity == "PETITE")
			c_LiasStab_S.SetCurSel(1);
	}
	if (conf_courante.type == "ASYNCHRONE")
	{
		c_LiasStab_A.SetCurSel(0);
		if (conf_courante.binary_integrity == "PETITE")
			c_LiasStab_A.SetCurSel(1);
	}

	// polarity
	c_LiasPol.SelectString(0, conf_courante.polarity.c_str());

	// handshake
	if (conf_courante.type == "SYNCHRONE")		//SYNCHRONE
	{
		if (conf_courante.handshake == "DPE")
			c_LiasDpe.SetCurSel(0);
		else
			c_LiasDpe.SelectString(0, conf_courante.handshake.c_str());
	}
	else
	{
		if (conf_courante.handshake == "DPE")
			c_LiasDpeA.SetCurSel(0);
		else
			c_LiasDpeA.SelectString(0, conf_courante.handshake.c_str());
	}

	// TODO
	if (conf_courante.type == "ASYNCHRONE")		//ASYNCHRONE
		c_Parite.SelectString(0, conf_courante.parity.substr(0,1).c_str());


	// Paramètres d'une liaison asynchrone
	if (conf_courante.type == "ASYNCHRONE")		//ASYNCHRONE
	{
		// character_length
		str.Format(_T("%01d"), conf_courante.character_length);
		c_NbBits.SelectString(0, (LPCTSTR)str);

		// number_stop_bits
		str.Format(_T("%01d"), conf_courante.number_stop_bits);
		c_NbStop.SelectString(0, (LPCTSTR)str);
	}

	UpdateData(TRUE);

	//*******************************************************************************************************************
}

// **********************************************************
// Mise à zero de la sélection de configuration
// **********************************************************
void CDlgTRC1752_MOD_PROG_INTF_LIAS::razChoixConfiguration()
{
	c_LiasConf.SetCurSel(0);

	ModificationConfiguration();

}

// **********************************************************
// Gestion du timer
// **********************************************************
void CDlgTRC1752_MOD_PROG_INTF_LIAS::marcheTimer()
{
	// FFT ADEL_97113
	razChoixConfiguration();

	// FFT ADEL_97113
	//if (eqp->GetMode() == false) return;		//il faut etre en distant

	m_timerLias = SetTimer(1,2000,NULL);
}

void CDlgTRC1752_MOD_PROG_INTF_LIAS::arretTimer()
{
	KillTimer(m_timerLias);
}

void CDlgTRC1752_MOD_PROG_INTF_LIAS::OnTimer(UINT nIDEvent)
{

	CDialog::OnTimer(nIDEvent);

	ModificationConfiguration();
}

// **********************************************************
