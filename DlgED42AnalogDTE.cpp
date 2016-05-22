// DlgED42AnalogDTE.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42AnalogDTE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42AnalogDTE dialog


CDlgED42AnalogDTE::CDlgED42AnalogDTE(CEquipED42 * eqp,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42AnalogDTE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42AnalogDTE)
	m_alarmtoneLevel = 0;
	m_microLevel = 0;
	m_monitorLevel = 0;
	m_phoneLevel = 0;
	m_rxbypassLevel = 0;
	m_rxctrLevel = 0;
	m_sidetoneLevel = 0;
	m_txbypassLevel = 0;
	m_txctrLevel = 0;
	//}}AFX_DATA_INIT

	this->eqp = eqp;

	oldMicroLevel = 0;
	oldPhoneLevel = 0;
	oldTxctrLevel = 0;
	oldRxctrLevel = 0;
	oldMonitorLevel = 0;
	oldSidetoneLevel = 0;
	oldAlarmtoneLevel = 0;
	oldTxbypassLevel = 0;
	oldRxbypassLevel = 0;
}


void CDlgED42AnalogDTE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42AnalogDTE)
	DDX_Control(pDX, IDC_COMBO_MICRO_TYPE, c_microType);
	DDX_Control(pDX, IDC_CHECK_MICRO_SUPPLY, c_microSupply);
	DDX_Control(pDX, IDC_SPIN_TXCTR_LEVEL, s_txctrLevel);
	DDX_Control(pDX, IDC_SPIN_TXBYPASS_LEVEL, s_txbypassLevel);
	DDX_Control(pDX, IDC_SPIN_SIDETONE_LEVEL, s_sidetoneLevel);
	DDX_Control(pDX, IDC_SPIN_RXCTR_LEVEL, s_rxctrLevel);
	DDX_Control(pDX, IDC_SPIN_RXBYPASS_LEVEL, s_rxbypassLevel);
	DDX_Control(pDX, IDC_SPIN_PHONE_LEVEL, s_phoneLevel);
	DDX_Control(pDX, IDC_EDIT_MONITOR_LEVEL, c_monitorLevel);
	DDX_Control(pDX, IDC_SPIN_MONITOR_LEVEL, s_monitorLevel);
	DDX_Control(pDX, IDC_SPIN_MICRO_LEVEL, s_microLevel);
	DDX_Control(pDX, IDC_SPIN_ALARMTONE_LEVEL, s_alarmtoneLevel);
	DDX_Control(pDX, IDC_EDIT_TXCTR_LEVEL, c_txctrLevel);
	DDX_Control(pDX, IDC_EDIT_TXBYPASS_LEVEL, c_txbypassLevel);
	DDX_Control(pDX, IDC_EDIT_SIDETONE_LEVEL, c_sidetoneLevel);
	DDX_Control(pDX, IDC_EDIT_RXCTR_LEVEL, c_rxctrLevel);
	DDX_Control(pDX, IDC_EDIT_RXBYPASS_LEVEL, c_rxbypassLevel);
	DDX_Control(pDX, IDC_EDIT_PHONE_LEVEL, c_phoneLevel);
	DDX_Control(pDX, IDC_EDIT_MICRO_LEVEL, c_microLevel);
	DDX_Control(pDX, IDC_EDIT_ALARMTONE_LEVEL, c_alarmtoneLevel);
	DDX_Control(pDX, IDC_COMBO_VOLTAGE_SUPPLY, c_voltageSupply);
	DDX_Control(pDX, IDC_COMBO_RI, c_ri);
	DDX_Control(pDX, IDC_COMBO_PTTCTR_CONFIG_TYPE, c_pttctrConfigType);
	DDX_Control(pDX, IDC_COMBO_PTT42_CONFIG_TYPE, c_ptt42ConfigType);
	DDX_Control(pDX, IDC_CHECK_ACT_MONITORING, c_actMonitoring);
	DDX_Control(pDX, IDC_CHECK_ACT_LOCAL_AUDIO, c_actLocalAudio);
	DDX_Control(pDX, IDC_CHECK_ACT_CENTRAL_AUDIO, c_actCentralAudio);
	DDX_Control(pDX, IDC_CHECK_ACT_ANALOG_DTE, c_actAnalogDTE);
	DDX_Text(pDX, IDC_EDIT_ALARMTONE_LEVEL, m_alarmtoneLevel);
	DDX_Text(pDX, IDC_EDIT_MICRO_LEVEL, m_microLevel);
	DDX_Text(pDX, IDC_EDIT_MONITOR_LEVEL, m_monitorLevel);
	DDX_Text(pDX, IDC_EDIT_PHONE_LEVEL, m_phoneLevel);
	DDX_Text(pDX, IDC_EDIT_RXBYPASS_LEVEL, m_rxbypassLevel);
	DDX_Text(pDX, IDC_EDIT_RXCTR_LEVEL, m_rxctrLevel);
	DDX_Text(pDX, IDC_EDIT_SIDETONE_LEVEL, m_sidetoneLevel);
	DDX_Text(pDX, IDC_EDIT_TXBYPASS_LEVEL, m_txbypassLevel);
	DDX_Text(pDX, IDC_EDIT_TXCTR_LEVEL, m_txctrLevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42AnalogDTE, CDialog)
	//{{AFX_MSG_MAP(CDlgED42AnalogDTE)
	ON_BN_CLICKED(IDC_CHECK_ACT_ANALOG_DTE, OnCheckActAnalogDte)
	ON_BN_CLICKED(IDC_CHECK_ACT_CENTRAL_AUDIO, OnCheckActCentralAudio)
	ON_BN_CLICKED(IDC_CHECK_ACT_LOCAL_AUDIO, OnCheckActLocalAudio)
	ON_BN_CLICKED(IDC_CHECK_ACT_MONITORING, OnCheckActMonitoring)
	ON_BN_CLICKED(IDC_CHECK_MICRO_SUPPLY, OnCheckMicroSupply)
	ON_CBN_SELCHANGE(IDC_COMBO_MICRO_TYPE, OnSelchangeComboMicroType)
	ON_CBN_SELCHANGE(IDC_COMBO_PTT42_CONFIG_TYPE, OnSelchangeComboPtt42ConfigType)
	ON_CBN_SELCHANGE(IDC_COMBO_PTTCTR_CONFIG_TYPE, OnSelchangeComboPttctrConfigType)
	ON_CBN_SELCHANGE(IDC_COMBO_RI, OnSelchangeComboRi)
	ON_CBN_SELCHANGE(IDC_COMBO_VOLTAGE_SUPPLY, OnSelchangeComboVoltageSupply)
	ON_EN_CHANGE(IDC_EDIT_ALARMTONE_LEVEL, OnChangeEditAlarmtoneLevel)
	ON_EN_CHANGE(IDC_EDIT_MICRO_LEVEL, OnChangeEditMicroLevel)
	ON_EN_CHANGE(IDC_EDIT_MONITOR_LEVEL, OnChangeEditMonitorLevel)
	ON_EN_CHANGE(IDC_EDIT_PHONE_LEVEL, OnChangeEditPhoneLevel)
	ON_EN_CHANGE(IDC_EDIT_RXBYPASS_LEVEL, OnChangeEditRxbypassLevel)
	ON_EN_CHANGE(IDC_EDIT_RXCTR_LEVEL, OnChangeEditRxctrLevel)
	ON_EN_CHANGE(IDC_EDIT_SIDETONE_LEVEL, OnChangeEditSidetoneLevel)
	ON_EN_CHANGE(IDC_EDIT_TXBYPASS_LEVEL, OnChangeEditTxbypassLevel)
	ON_EN_CHANGE(IDC_EDIT_TXCTR_LEVEL, OnChangeEditTxctrLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_ALARMTONE_LEVEL, OnDeltaposSpinAlarmtoneLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MICRO_LEVEL, OnDeltaposSpinMicroLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_MONITOR_LEVEL, OnDeltaposSpinMonitorLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_PHONE_LEVEL, OnDeltaposSpinPhoneLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RXBYPASS_LEVEL, OnDeltaposSpinRxbypassLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RXCTR_LEVEL, OnDeltaposSpinRxctrLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_SIDETONE_LEVEL, OnDeltaposSpinSidetoneLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TXBYPASS_LEVEL, OnDeltaposSpinTxbypassLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TXCTR_LEVEL, OnDeltaposSpinTxctrLevel)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42AnalogDTE message handlers

BOOL CDlgED42AnalogDTE::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	//Size de micro level
	c_microLevel.LimitText(3);
	//Initialisation micro level
	s_microLevel.SetRange(AUDIO_MIN, AUDIO_MAX);

	//Size de phone level
	c_phoneLevel.LimitText(3);
	//Initialisation phone level
	s_phoneLevel.SetRange(AUDIO_MIN, AUDIO_MAX);

	//Size de TXCTR level
	c_txctrLevel.LimitText(3);
	//Initialisation TXCTR level
	s_txctrLevel.SetRange(AUDIO_MIN, AUDIO_MAX);

	//Size de RXCTR level
	c_rxctrLevel.LimitText(3);
	//Initialisation RXCTR level
	s_rxctrLevel.SetRange(AUDIO_MIN, AUDIO_MAX);

	//Size de monitor level
	c_monitorLevel.LimitText(3);
	//Initialisation monitor level
	s_monitorLevel.SetRange(CONTROL_MIN, CONTROL_MAX);

	//Size de sidetone level
	c_sidetoneLevel.LimitText(3);
	//Initialisation sidetone level
	s_sidetoneLevel.SetRange(CONTROL_MIN, CONTROL_MAX);

	//Size de alarmtone level
	c_alarmtoneLevel.LimitText(3);
	//Initialisation alarmtone level
	s_alarmtoneLevel.SetRange(CONTROL_MIN, CONTROL_MAX);

	//Size de tx by pass level
	c_txbypassLevel.LimitText(3);
	//Initialisation tx by pass level
	s_txbypassLevel.SetRange(CONTROL_MIN, CONTROL_MAX);

	//Size de rx by pass level
	c_rxbypassLevel.LimitText(3);
	//Initialisation rx by pass level
	s_rxbypassLevel.SetRange(CONTROL_MIN, CONTROL_MAX);

	UpdateData(FALSE);
	
	return TRUE;  
}

void CDlgED42AnalogDTE::LoadData(string preset) 
{
	char buffer[3] = "";

	TAnalogDTE analogDTE = eqp->GetAnalogDTEParameters(preset);
	
	c_actAnalogDTE.SetCheck(analogDTE.activateAnalogDteInterface);
	c_actLocalAudio.SetCheck(analogDTE.activateLocalAudioInterface);
	c_ptt42ConfigType.SetCurSel(analogDTE.confTypePTT42);
	itoa(analogDTE.microLevel,buffer,10);
	//Mise à jour de la derniere valeur de micro level afin de ne pas lever le flag de modification
	oldMicroLevel = analogDTE.microLevel;
	c_microLevel.SetWindowText(buffer);
	itoa(analogDTE.phoneLevel,buffer,10);
	//Mise à jour de la derniere valeur de phone level afin de ne pas lever le flag de modification
	oldPhoneLevel = analogDTE.phoneLevel;
	c_phoneLevel.SetWindowText(buffer);

	c_ri.SetCurSel(analogDTE.microRi);
	c_microSupply.SetCheck(analogDTE.microSupply);
	c_microType.SetCurSel(analogDTE.microType);
	c_voltageSupply.SetCurSel(analogDTE.voltageSupply);

	c_actCentralAudio.SetCheck(analogDTE.activateCentralAudioInterface);
	c_pttctrConfigType.SetCurSel(analogDTE.confTypePTTCTR);
	itoa(analogDTE.txctrLevel,buffer,10);
	//Mise à jour de la derniere valeur de TXCTR level afin de ne pas lever le flag de modification
	oldTxctrLevel = analogDTE.txctrLevel;
	c_txctrLevel.SetWindowText(buffer);
	itoa(analogDTE.rxctrLevel,buffer,10);
	//Mise à jour de la derniere valeur de RXCTR level afin de ne pas lever le flag de modification
	oldRxctrLevel = analogDTE.rxctrLevel;
	c_rxctrLevel.SetWindowText(buffer);

	c_actMonitoring.SetCheck(analogDTE.activateMonitoring);
	itoa(analogDTE.monitorLevel,buffer,10);
	//Mise à jour de la derniere valeur de monitor level afin de ne pas lever le flag de modification
	oldMonitorLevel = analogDTE.monitorLevel;
	c_monitorLevel.SetWindowText(buffer);
	itoa(analogDTE.sidetoneLevel,buffer,10);
	//Mise à jour de la derniere valeur de sidetone level afin de ne pas lever le flag de modification
	oldSidetoneLevel = analogDTE.sidetoneLevel;
	c_sidetoneLevel.SetWindowText(buffer);
	itoa(analogDTE.alarmeLevel,buffer,10);
	//Mise à jour de la derniere valeur de alarme level afin de ne pas lever le flag de modification
	oldAlarmtoneLevel = analogDTE.alarmeLevel;
	c_alarmtoneLevel.SetWindowText(buffer);
	itoa(analogDTE.txbypassLevel,buffer,10);
	//Mise à jour de la derniere valeur de tx by pass level afin de ne pas lever le flag de modification
	oldTxbypassLevel = analogDTE.txbypassLevel;
	c_txbypassLevel.SetWindowText(buffer);
	itoa(analogDTE.rxbypassLevel,buffer,10);
	//Mise à jour de la derniere valeur de rx by pass level afin de ne pas lever le flag de modification
	oldRxbypassLevel = analogDTE.rxbypassLevel;
	c_rxbypassLevel.SetWindowText(buffer);

	MiseAJourVue();
}

void CDlgED42AnalogDTE::SaveData(string preset)
{
	CString val = "";

	TAnalogDTE analogDTE = eqp->GetAnalogDTEParameters(preset);

	analogDTE.activateAnalogDteInterface	= c_actAnalogDTE.GetCheck()==1;
	analogDTE.activateLocalAudioInterface	= c_actLocalAudio.GetCheck()==1;
	analogDTE.confTypePTT42					= c_ptt42ConfigType.GetCurSel();
	c_microLevel.GetWindowText(val);
	analogDTE.microLevel					= atoi(val);
	c_phoneLevel.GetWindowText(val);
	analogDTE.phoneLevel					= atoi(val);
	analogDTE.microRi						= c_ri.GetCurSel();
	analogDTE.microSupply					= c_microSupply.GetCheck()==1;
	analogDTE.microType						= c_microType.GetCurSel();
	analogDTE.voltageSupply					= c_voltageSupply.GetCurSel();

	analogDTE.activateCentralAudioInterface = c_actCentralAudio.GetCheck()==1;
	analogDTE.confTypePTTCTR				= c_pttctrConfigType.GetCurSel();
	c_txctrLevel.GetWindowText(val);
	analogDTE.txctrLevel					= atoi(val);
	c_rxctrLevel.GetWindowText(val);
	analogDTE.rxctrLevel					= atoi(val);

	analogDTE.activateMonitoring			= c_actMonitoring.GetCheck()==1;
	c_monitorLevel.GetWindowText(val);
	analogDTE.monitorLevel					= atoi(val);
	c_sidetoneLevel.GetWindowText(val);
	analogDTE.sidetoneLevel					= atoi(val);
	c_txbypassLevel.GetWindowText(val);
	analogDTE.txbypassLevel					= atoi(val);
	c_rxbypassLevel.GetWindowText(val);
	analogDTE.rxbypassLevel					= atoi(val);

	eqp->SetAnalogDTEParameters(preset , analogDTE);
}

void CDlgED42AnalogDTE::OnCheckActAnalogDte() 
{
	MiseAJourVue();

	eqp->setModifVue(TRUE);	
}

void CDlgED42AnalogDTE::OnCheckActCentralAudio() 
{
	c_actLocalAudio.SetCheck(!c_actCentralAudio.GetCheck());

	MiseAJourVue();

	eqp->setModifVue(TRUE);	
}

void CDlgED42AnalogDTE::OnCheckActLocalAudio() 
{
	c_actCentralAudio.SetCheck(!c_actLocalAudio.GetCheck());

	MiseAJourVue();
	
	eqp->setModifVue(TRUE);	
}

void CDlgED42AnalogDTE::OnCheckActMonitoring() 
{
	MiseAJourVue();

	eqp->setModifVue(TRUE);	
}

void CDlgED42AnalogDTE::OnCheckMicroSupply() 
{
	eqp->setModifVue(TRUE);	
}

void CDlgED42AnalogDTE::OnSelchangeComboMicroType() 
{
	eqp->setModifVue(TRUE);	
}

void CDlgED42AnalogDTE::OnSelchangeComboPtt42ConfigType() 
{
	eqp->setModifVue(TRUE);	
}

void CDlgED42AnalogDTE::OnSelchangeComboPttctrConfigType() 
{
	eqp->setModifVue(TRUE);	
}

void CDlgED42AnalogDTE::OnSelchangeComboRi() 
{
	eqp->setModifVue(TRUE);	
}

void CDlgED42AnalogDTE::OnSelchangeComboVoltageSupply() 
{
	eqp->setModifVue(TRUE);	
}

void CDlgED42AnalogDTE::OnChangeEditAlarmtoneLevel() 
{
	CString str;

	c_alarmtoneLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_alarmtoneLevel = atoi((char*)LPCTSTR(str));

	if ( m_alarmtoneLevel > CONTROL_MAX )
	{
		AfxMessageBox("L'alarmtone level peut prendre les valeurs : -40 à 20 dB");
		m_alarmtoneLevel = CONTROL_MAX;
	}

	if ( m_alarmtoneLevel < CONTROL_MIN)
	{
		AfxMessageBox("L'alarmtone level peut prendre les valeurs : -40 à 20 dB");
		m_alarmtoneLevel = CONTROL_MIN;
	}			

	if (oldAlarmtoneLevel != m_alarmtoneLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);	
}

void CDlgED42AnalogDTE::OnChangeEditMicroLevel() 
{
	CString str;

	c_microLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_microLevel = atoi((char*)LPCTSTR(str));

	if ( m_microLevel > AUDIO_MAX )
	{
		AfxMessageBox("Le micro level peut prendre les valeurs : -47 à 13 dB");
		m_microLevel = AUDIO_MAX;
	}

	if ( m_microLevel < AUDIO_MIN)
	{
		AfxMessageBox("Le micro level peut prendre les valeurs : -47 à 13 dB");
		m_microLevel = AUDIO_MIN;
	}			

	if (oldMicroLevel != m_microLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);	
}

void CDlgED42AnalogDTE::OnChangeEditMonitorLevel() 
{
	CString str;

	c_monitorLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_monitorLevel = atoi((char*)LPCTSTR(str));

	if ( m_monitorLevel > CONTROL_MAX )
	{
		AfxMessageBox("Le monitor level peut prendre les valeurs : -40 à 20 dB");
		m_monitorLevel = CONTROL_MAX;
	}

	if ( m_monitorLevel < CONTROL_MIN)
	{
		AfxMessageBox("Le monitor level peut prendre les valeurs : -40 à 20 dB");
		m_monitorLevel = CONTROL_MIN;
	}			

	if (oldMonitorLevel != m_monitorLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);	
}

void CDlgED42AnalogDTE::OnChangeEditPhoneLevel() 
{
	CString str;

	c_phoneLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_phoneLevel = atoi((char*)LPCTSTR(str));

	if ( m_phoneLevel > AUDIO_MAX )
	{
		AfxMessageBox("Le phone level peut prendre les valeurs : -47 à 13 dB");
		m_phoneLevel = AUDIO_MAX;
	}

	if ( m_phoneLevel < AUDIO_MIN)
	{
		AfxMessageBox("Le phone level peut prendre les valeurs : -47 à 13 dB");
		m_phoneLevel = AUDIO_MIN;
	}			

	if (oldPhoneLevel != m_phoneLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);	
}

void CDlgED42AnalogDTE::OnChangeEditRxbypassLevel() 
{
	CString str;

	c_rxbypassLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_rxbypassLevel = atoi((char*)LPCTSTR(str));

	if ( m_rxbypassLevel > CONTROL_MAX )
	{
		AfxMessageBox("Le rx by pass level peut prendre les valeurs : -40 à 20 dB");
		m_rxbypassLevel = CONTROL_MAX;
	}

	if ( m_rxbypassLevel < CONTROL_MIN)
	{
		AfxMessageBox("Le rx by pass level peut prendre les valeurs : -40 à 20 dB");
		m_rxbypassLevel = CONTROL_MIN;
	}			

	if (oldRxbypassLevel != m_rxbypassLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);	
}

void CDlgED42AnalogDTE::OnChangeEditRxctrLevel() 
{
	CString str;

	c_rxctrLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_rxctrLevel = atoi((char*)LPCTSTR(str));

	if ( m_rxctrLevel > AUDIO_MAX )
	{
		AfxMessageBox("Le RXCTR level peut prendre les valeurs : -47 à 13 dB");
		m_rxctrLevel = AUDIO_MAX;
	}

	if ( m_rxctrLevel < AUDIO_MIN)
	{
		AfxMessageBox("Le RXCTR level peut prendre les valeurs : -47 à 13 dB");
		m_rxctrLevel = AUDIO_MIN;
	}			

	if (oldRxctrLevel != m_rxctrLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);		
}

void CDlgED42AnalogDTE::OnChangeEditSidetoneLevel() 
{
CString str;

	c_sidetoneLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_sidetoneLevel = atoi((char*)LPCTSTR(str));

	if ( m_sidetoneLevel > CONTROL_MAX )
	{
		AfxMessageBox("Le sidetone level peut prendre les valeurs : -40 à 20 dB");
		m_sidetoneLevel = CONTROL_MAX;
	}

	if ( m_sidetoneLevel < CONTROL_MIN)
	{
		AfxMessageBox("Le sidetone level peut prendre les valeurs : -40 à 20 dB");
		m_sidetoneLevel = CONTROL_MIN;
	}			

	if (oldSidetoneLevel != m_sidetoneLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);
}

void CDlgED42AnalogDTE::OnChangeEditTxbypassLevel() 
{
	CString str;

	c_txbypassLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_txbypassLevel = atoi((char*)LPCTSTR(str));

	if ( m_txbypassLevel > CONTROL_MAX )
	{
		AfxMessageBox("Le tx by pass level peut prendre les valeurs : -40 à 20 dB");
		m_txbypassLevel = CONTROL_MAX;
	}

	if ( m_txbypassLevel < CONTROL_MIN)
	{
		AfxMessageBox("Le tx by pass level peut prendre les valeurs : -40 à 20 dB");
		m_txbypassLevel = CONTROL_MIN;
	}			

	if (oldTxbypassLevel != m_txbypassLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);
}

void CDlgED42AnalogDTE::OnChangeEditTxctrLevel() 
{
	CString str;

	c_txctrLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_txctrLevel = atoi((char*)LPCTSTR(str));

	if ( m_txctrLevel > AUDIO_MAX )
	{
		AfxMessageBox("Le TXCTR level peut prendre les valeurs : -47 à 13 dB");
		m_txctrLevel = AUDIO_MAX;
	}

	if ( m_txctrLevel < AUDIO_MIN)
	{
		AfxMessageBox("Le TXCTR level peut prendre les valeurs : -47 à 13 dB");
		m_txctrLevel = AUDIO_MIN;
	}			

	if (oldTxctrLevel != m_txctrLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);
}

void CDlgED42AnalogDTE::OnDeltaposSpinAlarmtoneLevel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if (pNMUpDown->iDelta > 0)  m_alarmtoneLevel += 1;
		else       m_alarmtoneLevel -= 1;
	
	if ( m_alarmtoneLevel > CONTROL_MAX )
	{
		AfxMessageBox("L'alarmtone level peut prendre les valeurs : -40 à 20 dB");
		m_alarmtoneLevel = CONTROL_MAX;
	}

	if ( m_alarmtoneLevel < CONTROL_MIN)
	{
		AfxMessageBox("L'alarmtone level peut prendre les valeurs : -40 à 20 dB");
		m_alarmtoneLevel = CONTROL_MIN;
	}			

	if (oldAlarmtoneLevel != m_alarmtoneLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);	

	*pResult = 0;
}

void CDlgED42AnalogDTE::OnDeltaposSpinMicroLevel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if (pNMUpDown->iDelta > 0)  m_microLevel += 1;
		else       m_microLevel -= 1;
	
	if ( m_microLevel > AUDIO_MAX )
	{
		AfxMessageBox("Le micro level peut prendre les valeurs : -47 à 13 dB");
		m_microLevel = AUDIO_MAX;
	}

	if ( m_microLevel < AUDIO_MIN)
	{
		AfxMessageBox("Le micro level peut prendre les valeurs : -47 à 13 dB");
		m_microLevel = AUDIO_MIN;
	}			

	if (oldMicroLevel != m_microLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgED42AnalogDTE::OnDeltaposSpinMonitorLevel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if (pNMUpDown->iDelta > 0)  m_monitorLevel += 1;
		else       m_monitorLevel -= 1;
	
	if ( m_monitorLevel > CONTROL_MAX )
	{
		AfxMessageBox("Le monitor level peut prendre les valeurs : -40 à 20 dB");
		m_monitorLevel = CONTROL_MAX;
	}

	if ( m_monitorLevel < CONTROL_MIN)
	{
		AfxMessageBox("Le monitor level peut prendre les valeurs : -40 à 20 dB");
		m_monitorLevel = CONTROL_MIN;
	}			

	if (oldMonitorLevel != m_monitorLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgED42AnalogDTE::OnDeltaposSpinPhoneLevel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if (pNMUpDown->iDelta > 0)  m_phoneLevel += 1;
		else       m_phoneLevel -= 1;
	
	if ( m_phoneLevel > AUDIO_MAX )
	{
		AfxMessageBox("Le phone level peut prendre les valeurs : -47 à 13 dB");
		m_phoneLevel = AUDIO_MAX;
	}

	if ( m_phoneLevel < AUDIO_MIN)
	{
		AfxMessageBox("Le phone level peut prendre les valeurs : -47 à 13 dB");
		m_phoneLevel = AUDIO_MIN;
	}			

	if (oldPhoneLevel != m_phoneLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);	

	*pResult = 0;
}

void CDlgED42AnalogDTE::OnDeltaposSpinRxbypassLevel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_rxbypassLevel += 1;
		else       m_rxbypassLevel -= 1;
	
	if ( m_rxbypassLevel > CONTROL_MAX )
	{
		AfxMessageBox("Le rx by pass level peut prendre les valeurs : -40 à 20 dB");
		m_rxbypassLevel = CONTROL_MAX;
	}

	if ( m_rxbypassLevel < CONTROL_MIN)
	{
		AfxMessageBox("Le rx by pass level peut prendre les valeurs : -40 à 20 dB");
		m_rxbypassLevel = CONTROL_MIN;
	}			

	if (oldRxbypassLevel != m_rxbypassLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgED42AnalogDTE::OnDeltaposSpinRxctrLevel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if (pNMUpDown->iDelta > 0)  m_rxctrLevel += 1;
		else       m_rxctrLevel -= 1;

	if ( m_rxctrLevel > AUDIO_MAX )
	{
		AfxMessageBox("Le RXCTR level peut prendre les valeurs : -47 à 13 dB");
		m_rxctrLevel = AUDIO_MAX;
	}

	if ( m_rxctrLevel < AUDIO_MIN)
	{
		AfxMessageBox("Le RXCTR level peut prendre les valeurs : -47 à 13 dB");
		m_rxctrLevel = AUDIO_MIN;
	}			

	if (oldRxctrLevel != m_rxctrLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);	

	*pResult = 0;
}

void CDlgED42AnalogDTE::OnDeltaposSpinSidetoneLevel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if (pNMUpDown->iDelta > 0)  m_sidetoneLevel += 1;
		else       m_sidetoneLevel -= 1;
	
	if ( m_sidetoneLevel > CONTROL_MAX )
	{
		AfxMessageBox("Le sidetone level peut prendre les valeurs : -40 à 20 dB");
		m_sidetoneLevel = CONTROL_MAX;
	}

	if ( m_sidetoneLevel < CONTROL_MIN)
	{
		AfxMessageBox("Le sidetone level peut prendre les valeurs : -40 à 20 dB");
		m_sidetoneLevel = CONTROL_MIN;
	}			

	if (oldSidetoneLevel != m_sidetoneLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgED42AnalogDTE::OnDeltaposSpinTxbypassLevel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if (pNMUpDown->iDelta > 0)  m_txbypassLevel += 1;
		else       m_txbypassLevel -= 1;
	
	if ( m_txbypassLevel > CONTROL_MAX )
	{
		AfxMessageBox("Le tx by pass level peut prendre les valeurs : -40 à 20 dB");
		m_txbypassLevel = CONTROL_MAX;
	}

	if ( m_txbypassLevel < CONTROL_MIN)
	{
		AfxMessageBox("Le tx by pass level peut prendre les valeurs : -40 à 20 dB");
		m_txbypassLevel = CONTROL_MIN;
	}			

	if (oldTxbypassLevel != m_txbypassLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgED42AnalogDTE::OnDeltaposSpinTxctrLevel(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if (pNMUpDown->iDelta > 0)  m_txctrLevel += 1;
		else       m_txctrLevel -= 1;
	
	if ( m_txctrLevel > AUDIO_MAX )
	{
		AfxMessageBox("Le TXCTR level peut prendre les valeurs : -47 à 13 dB");
		m_txctrLevel = AUDIO_MAX;
	}

	if ( m_txctrLevel < AUDIO_MIN)
	{
		AfxMessageBox("Le TXCTR level peut prendre les valeurs : -47 à 13 dB");
		m_txctrLevel = AUDIO_MIN;
	}			

	if (oldTxctrLevel != m_txctrLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}
void CDlgED42AnalogDTE::MiseAJourVue()
{
	//Mise à jour des éléments à griser
	c_actLocalAudio.EnableWindow(c_actAnalogDTE.GetCheck());
	c_ptt42ConfigType.EnableWindow(c_actAnalogDTE.GetCheck() && c_actLocalAudio.GetCheck());
	c_microLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actLocalAudio.GetCheck());
	s_microLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actLocalAudio.GetCheck());
	c_phoneLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actLocalAudio.GetCheck());
	s_phoneLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actLocalAudio.GetCheck());
	c_ri.EnableWindow(c_actAnalogDTE.GetCheck() && c_actLocalAudio.GetCheck());
	c_microSupply.EnableWindow(c_actAnalogDTE.GetCheck() && c_actLocalAudio.GetCheck());
	c_microType.EnableWindow(c_actAnalogDTE.GetCheck() && c_actLocalAudio.GetCheck());
	c_voltageSupply.EnableWindow(c_actAnalogDTE.GetCheck() && c_actLocalAudio.GetCheck());

	c_actCentralAudio.EnableWindow(c_actAnalogDTE.GetCheck());
	c_pttctrConfigType.EnableWindow(c_actAnalogDTE.GetCheck() && c_actCentralAudio.GetCheck());
	c_txctrLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actCentralAudio.GetCheck());
	s_txctrLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actCentralAudio.GetCheck());
	c_rxctrLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actCentralAudio.GetCheck());
	s_rxctrLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actCentralAudio.GetCheck());

	c_actMonitoring.EnableWindow(c_actAnalogDTE.GetCheck());
	c_monitorLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actMonitoring.GetCheck());
	s_monitorLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actMonitoring.GetCheck());
	c_sidetoneLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actMonitoring.GetCheck());
	s_sidetoneLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actMonitoring.GetCheck());
	c_alarmtoneLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actMonitoring.GetCheck());
	s_alarmtoneLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actMonitoring.GetCheck());
	c_txbypassLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actMonitoring.GetCheck());
	s_txbypassLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actMonitoring.GetCheck());
	c_rxbypassLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actMonitoring.GetCheck());
	s_rxbypassLevel.EnableWindow(c_actAnalogDTE.GetCheck() && c_actMonitoring.GetCheck());	
}

