// DlgED42Parametres.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42Parametres.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42Parametres dialog


CDlgED42Parametres::CDlgED42Parametres(CEquipED42 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42Parametres::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42Parametres)
	m_deviceAddress = 0;
	m_dsInterface = -1;
	m_hdlcAddress = 0;
	//}}AFX_DATA_INIT

		this->eqp = equip;
}


void CDlgED42Parametres::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42Parametres)
	DDX_Control(pDX, IDC_COMBO_REMOTE, c_remoteCtrl);
	DDX_Control(pDX, IDC_SPIN_P2, s_hdlcAdrdess);
	DDX_Control(pDX, IDC_EDIT_HDLC, c_hdlcAddress);
	DDX_Control(pDX, IDC_BUTTON_HDLC, c_setHdlcAddress);
	DDX_Control(pDX, IDC_BUTTON_P2, c_setDeviceAddress);
	DDX_Control(pDX, IDC_BUTTON_P1, c_setDeviceId);
	DDX_Control(pDX, IDC_EDIT_P2, c_deviceAddress);
	DDX_Control(pDX, IDC_SPIN_P1, s_deviceAddress);
	DDX_Control(pDX, IDC_EDIT_P1, c_deviceId);
	DDX_Control(pDX, IDC_LIST_PARAMETRES, m_parametres);
	DDX_Text(pDX, IDC_EDIT_P2, m_deviceAddress);
	DDX_Radio(pDX, IDC_RADIO_101, m_dsInterface);
	DDX_Text(pDX, IDC_EDIT_HDLC, m_hdlcAddress);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42Parametres, CDialog)
	//{{AFX_MSG_MAP(CDlgED42Parametres)
	ON_WM_TIMER()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_P1, OnDeltaposSpinDeviceAddress)
	ON_BN_CLICKED(IDC_BUTTON_P1, OnSetDeviceID)
	ON_BN_CLICKED(IDC_BUTTON_P2, OnSetDeviceAddress)
	ON_BN_CLICKED(IDC_BUTTON_P3, OnSetFactoryDefault)
	ON_BN_CLICKED(IDC_RADIO_101, OnSetDsInterface)
	ON_BN_CLICKED(IDC_RADIO_102, OnSetDSInterface102)
	ON_BN_CLICKED(IDC_BUTTON_HDLC, OnSetHdlcAddress)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_P2, OnDeltaposSpinP2)
	ON_CBN_SELCHANGE(IDC_COMBO_REMOTE, OnSelchangeComboRemote)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42Parametres message handlers

void CDlgED42Parametres::OnTimer(UINT nIDEvent)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnTimer(nIDEvent);
}

BOOL CDlgED42Parametres::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Init tableau
	CString strText;

	//Affichage du quadrillage
	m_parametres.SetExtendedStyle(LVS_EX_GRIDLINES);

	//Hearder
	strText.Format(TEXT("Module Name"));
	m_parametres.InsertColumn(0,strText,LVCFMT_LEFT,260);

	strText.Format(TEXT("Version"));
	m_parametres.InsertColumn(1,strText,LVCFMT_LEFT,100);

	strText.Format(TEXT("Date"));
	m_parametres.InsertColumn(2,strText,LVCFMT_LEFT,130);

	strText.Format(TEXT("ID"));
	m_parametres.InsertColumn(3,strText,LVCFMT_LEFT,80);

	//Lignes
	strText.Format(TEXT("Red Basic Device"));
	m_parametres.InsertItem(0,strText);

	strText.Format(TEXT("Black Basic Device"));
	m_parametres.InsertItem(1,strText);

	strText.Format(TEXT("Red PLD"));
	m_parametres.InsertItem(2,strText);

	strText.Format(TEXT("Black PLD"));
	m_parametres.InsertItem(3,strText);

	strText.Format(TEXT("Operating Device"));
	m_parametres.InsertItem(4,strText);

	strText.Format(TEXT("MIL-Bus Module"));
	m_parametres.InsertItem(5,strText);

	strText.Format(TEXT("Crypto Board"));
	m_parametres.InsertItem(6,strText);

	strText.Format(TEXT("Firmware FPGA"));
	m_parametres.InsertItem(7,strText);

	//size de device ID
	c_deviceId.LimitText(6);
	c_deviceId.Clear();

	//Size de device address
	c_deviceAddress.LimitText(2);

	//Size de hdlc address
	c_hdlcAddress.LimitText(3);

	//Initialisation Niveau de Qualité
	s_deviceAddress.SetRange(DEVICE_ADDRESS_MIN, DEVICE_ADDRESS_MAX);
	s_hdlcAdrdess.SetRange(HDLC_ADDRESS_MIN, HDLC_ADDRESS_MAX);


	UpdateData(FALSE);


	LoadData();

	return TRUE;
}

void CDlgED42Parametres::LoadData()
{
	UpdateData(TRUE);

	char buffer[7] = "";
	string version ="";
	string date = "";

	//Attention la date doit avoir toujours la meme taille 
	if(eqp->GetVersionRed().size()>6)
	{
		date = eqp->GetVersionRed().substr(eqp->GetVersionRed().size()-6,6);
		version = eqp->GetVersionRed().substr(0,eqp->GetVersionRed().size()-date.size());

		m_parametres.SetItemText(0,1,version.c_str());
		m_parametres.SetItemText(0,2,date.c_str());
	}	

	if(eqp->GetVersionBlack().size()>6)
	{
		date = eqp->GetVersionBlack().substr(eqp->GetVersionBlack().size()-6,6);
		version = eqp->GetVersionBlack().substr(0,eqp->GetVersionBlack().size()-date.size());

		m_parametres.SetItemText(1,1,version.c_str());
		m_parametres.SetItemText(1,2,date.c_str());
	}

	if(eqp->GetVersionPldRed().size()>6)
	{
		date = eqp->GetVersionPldRed().substr(eqp->GetVersionPldRed().size()-6,6);
		version = eqp->GetVersionPldRed().substr(0,eqp->GetVersionPldRed().size()-date.size());

		m_parametres.SetItemText(2,1,version.c_str());
		m_parametres.SetItemText(2,2,date.c_str());
	}

	if(eqp->GetVersionPldBlack().size()>6)
	{
		date = eqp->GetVersionPldBlack().substr(eqp->GetVersionPldBlack().size()-6,6);
		version = eqp->GetVersionPldBlack().substr(0,eqp->GetVersionPldBlack().size()-date.size());

		m_parametres.SetItemText(3,1,version.c_str());
		m_parametres.SetItemText(3,2,date.c_str());
	}

	if(eqp->GetVersionOpeDevice().size()>6)
	{
		date = eqp->GetVersionOpeDevice().substr(eqp->GetVersionOpeDevice().size()-6,6);
		version = eqp->GetVersionOpeDevice().substr(0,eqp->GetVersionOpeDevice().size()-date.size());

		m_parametres.SetItemText(4,1,version.c_str());
		m_parametres.SetItemText(4,2,date.c_str());
	}

	if(eqp->GetVersionMilBus().size()>6)
	{
		date = eqp->GetVersionMilBus().substr(eqp->GetVersionMilBus().size()-6,6);
		version = eqp->GetVersionMilBus().substr(0,eqp->GetVersionMilBus().size()-date.size());

		m_parametres.SetItemText(5,1,version.c_str());
		m_parametres.SetItemText(5,2,date.c_str());
	}

	
	// Initialisation DS Interface
	m_dsInterface = eqp->GetInterfaceKeyDownload() - 1;

	// Initialisation Device ID
	itoa(eqp->GetDeviceID(),buffer,10);
	c_deviceId.SetWindowText(buffer);
	//c_deviceId.EnableWindow(eqp->GetInterfaceKeyDownload() == DS101 && eqp->GetStateCik() == VALID_CIK_STATE);
	//Visibilité du bouton
	//c_setDeviceId.EnableWindow(eqp->GetInterfaceKeyDownload() == DS101 && eqp->GetStateCik() == VALID_CIK_STATE);

	// Initialisation Device Address
	m_deviceAddress = eqp->getRemoteAdress();
	//c_deviceAddress.EnableWindow(eqp->GetInterfaceKeyDownload() == DS102 && eqp->GetStateCik() == VALID_CIK_STATE);
	//Visibilité du bouton
	//c_setDeviceAddress.EnableWindow(eqp->GetInterfaceKeyDownload() == DS102 && eqp->GetStateCik() == VALID_CIK_STATE);

	// Initialisation HDLC Address
	m_hdlcAddress = eqp->getHDLCAddress();
	if (eqp->GetOperatingStatus() == OFFLINE)
	{
		c_hdlcAddress.EnableWindow(eqp->GetInterfaceKeyDownload() == DS101 && eqp->GetStateCik() == VALID_CIK_STATE);
		s_hdlcAdrdess.EnableWindow(eqp->GetInterfaceKeyDownload() == DS101 && eqp->GetStateCik() == VALID_CIK_STATE);
		//Visibilité du bouton
		c_setHdlcAddress.EnableWindow(eqp->GetInterfaceKeyDownload() == DS101 && eqp->GetStateCik() == VALID_CIK_STATE);
	}

	// Initialisation de REMOTECTRL

	if (eqp->getRemoteMode() == REMOTE)
		c_remoteCtrl.SetCurSel(0);
	else
		c_remoteCtrl.SetCurSel(1);

	UpdateData(FALSE);
}

// Device Address
void CDlgED42Parametres::OnDeltaposSpinDeviceAddress(NMHDR* pNMHDR, LRESULT* pResult)
{
	//CString str;

	//Le device address peut prendre les valeurs : 1 à 99
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_deviceAddress += 1;
		else       m_deviceAddress -= 1;


	if ( m_deviceAddress > DEVICE_ADDRESS_MAX )
	{
		AfxMessageBox("Le device address peut prendre les valeurs : 1 à 99");
		m_deviceAddress = DEVICE_ADDRESS_MAX;
	}

	if ( m_deviceAddress < DEVICE_ADDRESS_MIN)
	{
		AfxMessageBox("Le device address peut prendre les valeurs : 1 à 99");
		m_deviceAddress = DEVICE_ADDRESS_MIN;
	}

	UpdateData(FALSE);

	*pResult = 0;
}

// HDLC Address
void CDlgED42Parametres::OnDeltaposSpinP2(NMHDR* pNMHDR, LRESULT* pResult) 
{
	//Le hdlc address peut prendre les valeurs : 1 à 254
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_hdlcAddress += 1;
		else       m_hdlcAddress -= 1;


	if ( m_hdlcAddress > HDLC_ADDRESS_MAX )
	{
		AfxMessageBox("Le HDLC address peut prendre les valeurs : 1 à 254");
		m_hdlcAddress = HDLC_ADDRESS_MAX;
	}

	if ( m_hdlcAddress < HDLC_ADDRESS_MIN)
	{
		AfxMessageBox("Le HDLC address peut prendre les valeurs : 1 à 254");
		m_hdlcAddress = HDLC_ADDRESS_MIN;
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgED42Parametres::OnSetDeviceID()
{
	CString tmpId;

	c_deviceId.GetWindowText(tmpId);

	eqp->SetDeviceID(tmpId);

}

void CDlgED42Parametres::OnSetDeviceAddress()
{
	CString tmpId;

	c_deviceAddress.GetWindowText(tmpId);

	eqp->setRemoteAdress(tmpId);
}

void CDlgED42Parametres::OnSetHdlcAddress() 
{
	CString tmpId;

	c_hdlcAddress.GetWindowText(tmpId);

	eqp->setHDLCAddress(tmpId);
	
}

void CDlgED42Parametres::OnSetDsInterface()
{
	eqp->SetInterfaceKeyDownload(DS101);

	LoadData();
}

void CDlgED42Parametres::OnSetFactoryDefault()
{
	eqp->setRemoteAdress("1");
	eqp->SetDeviceID("123456");
	eqp->SetInterfaceKeyDownload(DS102);
	eqp->setHDLCAddress("127");
	eqp->setRemoteMode(REMOTE);
	
	LoadData();

}

void CDlgED42Parametres::OnSetDSInterface102() 
{
	eqp->SetInterfaceKeyDownload(DS102);
	
	LoadData();
}


void CDlgED42Parametres::OnSelchangeComboRemote() 
{
	if (c_remoteCtrl.GetCurSel() == 0)
		eqp->setRemoteMode(REMOTE);
	else
		eqp->setRemoteMode(LF_DIG);
	
}
