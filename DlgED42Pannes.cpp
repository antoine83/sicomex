// DlgED42Pannes.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42Pannes.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgED42Pannes dialog


DlgED42Pannes::DlgED42Pannes(CEquipED42* equip,CWnd* pParent )
	: CDialog(DlgED42Pannes::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgED42Pannes)
	//}}AFX_DATA_INIT
	this->equip = equip;
}


void DlgED42Pannes::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgED42Pannes)
	DDX_Control(pDX, IDC_CHECK_CRYPTOALARM_TAMPER, m_CryptoalarmTamper);
	DDX_Control(pDX, IDC_CHECK_CRYPTOALARM_NOTL, m_CryptoalarmNotl);
	DDX_Control(pDX, IDC_CHECK_ZSS_UNEX_STATE_STARTUP, m_ZssUnexStateStartup);
	DDX_Control(pDX, IDC_CHECK_ZSS_UNEX_STATE_IDLE, m_ZssUnexStateIdle);
	DDX_Control(pDX, IDC_CHECK_ZSS_MANAG_CRC, m_ZssManagCrc);
	DDX_Control(pDX, IDC_CHECK_ZSS_FLASH_MAGIC_ERROR, m_ZssFlashMagicError);
	DDX_Control(pDX, IDC_CHECK_ZSS_FLASH_ERROR, m_ZssFlashError);
	DDX_Control(pDX, IDC_CHECK_ZSS_ERROR_INTERFACEBIT, m_ZssErrorInterfacebit);
	DDX_Control(pDX, IDC_CHECK_KE_UNEX_STATE_INDISPOSED, m_KeUnexStateIndisposed);
	DDX_Control(pDX, IDC_CHECK_CRYPTOALARM_GLOBAL, m_CryptoalarmGlobal);
	DDX_Control(pDX, IDC_CHECK_CE_VAR_STAT_ERROR, m_CeVarStatError);
	DDX_Control(pDX, IDC_CHECK_CE_UNEX_STATE_POWERON, m_CeUnexStatePoweron);
	DDX_Control(pDX, IDC_CHECK_CE_UNEX_STATE_INITCIK2_IDLE, m_CeUnexStateInitcik2Idle);
	DDX_Control(pDX, IDC_CHECK_CE_UNEX_STATE_DELCIKUSER_IDLE, m_CeUnexStateDelcikuserIdle);
	DDX_Control(pDX, IDC_CHECK_CE_UNEX_STATE_AOUT, m_CeUnexStateAout);
	DDX_Control(pDX, IDC_CHECK_CE_UNEX_ONLINE_MODE, m_CeUnexOnlineMode);
	DDX_Control(pDX, IDC_CHECK_CE_STARTTX_ERROR_ONLINE, m_CeStarttxErrorOnline);
	DDX_Control(pDX, IDC_CHECK_CE_STARTRX_ERROR_ONLINE, m_CeStartrxErrorOnline);
	DDX_Control(pDX, IDC_CHECK_CE_START_ERROR_ONLINE, m_CeStartErrorOnline);
	DDX_Control(pDX, IDC_CHECK_CE_SKM_TIMEOUT_AOUT, m_CeSkmTimeoutAout);
	DDX_Control(pDX, IDC_CHECK_CE_PWDTEST_ERROR, m_CePwdtestError);
	DDX_Control(pDX, IDC_CHECK_CE_PREP_ERROR_COMSETUP, m_CePrepErrorComsetup);
	DDX_Control(pDX, IDC_CHECK_CE_CIK_SYSTEM_ERROR, m_CeCikSystemError);
	DDX_Control(pDX, IDC_CHECK_CE_ACTIV_ERROR_CRYSETUP2, m_CeActivErrorCrysetup2);
	DDX_Control(pDX, IDC_CHECK_CE_ACTIV_ERROR_CRYSETUP, m_CeActivErrorCrysetup);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgED42Pannes, CDialog)
	//{{AFX_MSG_MAP(DlgED42Pannes)
	ON_BN_CLICKED(IDC_CHECK_ZSS_MANAG_CRC, OnCheckZssManagCrc)
	ON_BN_CLICKED(IDC_CHECK_ZSS_UNEX_STATE_STARTUP, OnCheckZssUnexStateStartup)
	ON_BN_CLICKED(IDC_CHECK_KE_UNEX_STATE_INDISPOSED, OnCheckKeUnexStateIndisposed)
	ON_BN_CLICKED(IDC_CHECK_ZSS_FLASH_MAGIC_ERROR, OnCheckZssFlashMagicError)
	ON_BN_CLICKED(IDC_CHECK_ZSS_FLASH_ERROR, OnCheckZssFlashError)
	ON_BN_CLICKED(IDC_CHECK_ZSS_UNEX_STATE_IDLE, OnCheckZssUnexStateIdle)
	ON_BN_CLICKED(IDC_CHECK_ZSS_ERROR_INTERFACEBIT, OnCheckZssErrorInterfacebit)
	ON_BN_CLICKED(IDC_CHECK_CE_SKM_TIMEOUT_AOUT, OnCheckCeSkmTimeoutAout)
	ON_BN_CLICKED(IDC_CHECK_CE_PWDTEST_ERROR, OnCheckCePwdtestError)
	ON_BN_CLICKED(IDC_CHECK_CE_VAR_STAT_ERROR, OnCheckCeVarStatError)
	ON_BN_CLICKED(IDC_CHECK_CE_UNEX_STATE_AOUT, OnCheckCeUnexStateAout)
	ON_BN_CLICKED(IDC_CHECK_CE_UNEX_STATE_POWERON, OnCheckCeUnexStatePoweron)
	ON_BN_CLICKED(IDC_CHECK_CE_UNEX_STATE_INITCIK2_IDLE, OnCheckCeUnexStateInitcik2Idle)
	ON_BN_CLICKED(IDC_CHECK_CE_UNEX_STATE_DELCIKUSER_IDLE, OnCheckCeUnexStateDelcikuserIdle)
	ON_BN_CLICKED(IDC_CHECK_CE_CIK_SYSTEM_ERROR, OnCheckCeCikSystemError)
	ON_BN_CLICKED(IDC_CHECK_CE_ACTIV_ERROR_CRYSETUP, OnCheckCeActivErrorCrysetup)
	ON_BN_CLICKED(IDC_CHECK_CE_ACTIV_ERROR_CRYSETUP2, OnCheckCeActivErrorCrysetup2)
	ON_BN_CLICKED(IDC_CHECK_CE_PREP_ERROR_COMSETUP, OnCheckCePrepErrorComsetup)
	ON_BN_CLICKED(IDC_CHECK_CE_UNEX_ONLINE_MODE, OnCheckCeUnexOnlineMode)
	ON_BN_CLICKED(IDC_CHECK_CE_START_ERROR_ONLINE, OnCheckCeStartErrorOnline)
	ON_BN_CLICKED(IDC_CHECK_CE_STARTRX_ERROR_ONLINE, OnCheckCeStartrxErrorOnline)
	ON_BN_CLICKED(IDC_CHECK_CE_STARTTX_ERROR_ONLINE, OnCheckCeStarttxErrorOnline)
	ON_BN_CLICKED(IDC_CHECK_CRYPTOALARM_NOTL, OnCheckCryptoalarmNotl)
	ON_BN_CLICKED(IDC_CHECK_CRYPTOALARM_TAMPER, OnCheckCryptoalarmTamper)
	ON_BN_CLICKED(IDC_CHECK_CRYPTOALARM_GLOBAL, OnCheckCryptoalarmGlobal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgED42Pannes message handlers
BOOL DlgED42Pannes::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadData();

	return TRUE;
}

void DlgED42Pannes::LoadData()
{
	TAlarm alarm;
	TVectorAlarm alarmList = equip->getAlarms();

	//Pour "ZSS_MANAG_CRC"
	alarm = equip->DecodeAlarm(alarmList[0]);
	if (alarm.used)
		m_ZssManagCrc.SetCheck(BST_CHECKED);
	else
		m_ZssManagCrc.SetCheck(BST_UNCHECKED);

	//Pour "ZSS_UNEX_SKM_STATE_STARUP"
	alarm = equip->DecodeAlarm(alarmList[1]);
	if (alarm.used)
		m_ZssUnexStateStartup.SetCheck(BST_CHECKED);
	else
		m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);

	//Pour "KE_UNEX_SKM_STATE_INDISPOSED"
	alarm = equip->DecodeAlarm(alarmList[2]);
	if (alarm.used)
		m_KeUnexStateIndisposed.SetCheck(BST_CHECKED);
	else
		m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);

	//Pour "ZSS_FLASH_MAGIC_ERROR"
	alarm = equip->DecodeAlarm(alarmList[3]);
	if (alarm.used)
		m_ZssFlashMagicError.SetCheck(BST_CHECKED);
	else
		m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);

	//Pour "ZSS_FLASH_ERROR"
	alarm = equip->DecodeAlarm(alarmList[4]);
	if (alarm.used)
		m_ZssFlashError.SetCheck(BST_CHECKED);
	else
		m_ZssFlashError.SetCheck(BST_UNCHECKED);

	//Pour "ZSS_UNEX_SKM_STATE_IDLE"
	alarm = equip->DecodeAlarm(alarmList[5]);
	if (alarm.used)
		m_ZssUnexStateIdle.SetCheck(BST_CHECKED);
	else
		m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);

	//Pour "ZSS_ERROR_INTERFACEBIT"
	alarm = equip->DecodeAlarm(alarmList[6]);
	if (alarm.used)
		m_ZssErrorInterfacebit.SetCheck(BST_CHECKED);
	else
		m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);

	//Pour "CE_SKM_TIMEOUT_AOUT"
	alarm = equip->DecodeAlarm(alarmList[7]);
	if (alarm.used)
		m_CeSkmTimeoutAout.SetCheck(BST_CHECKED);
	else
		m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);

	//Pour "CE_PWDTEST_ERROR"
	alarm = equip->DecodeAlarm(alarmList[8]);
	if (alarm.used)
		m_CePwdtestError.SetCheck(BST_CHECKED);
	else
		m_CePwdtestError.SetCheck(BST_UNCHECKED);

	//Pour "CE_VAR_STAT_ERROR"
	alarm = equip->DecodeAlarm(alarmList[9]);
	if (alarm.used)
		m_CeVarStatError.SetCheck(BST_CHECKED);
	else
		m_CeVarStatError.SetCheck(BST_UNCHECKED);

	//Pour "CE_UNEX_SKM_STATE_AOUT"
	alarm = equip->DecodeAlarm(alarmList[10]);
	if (alarm.used)
		m_CeUnexStateAout.SetCheck(BST_CHECKED);
	else
		m_CeUnexStateAout.SetCheck(BST_UNCHECKED);

	//Pour "CE_UNEX_SKM_STATE_POWERON"
	alarm = equip->DecodeAlarm(alarmList[11]);
	if (alarm.used)
		m_CeUnexStatePoweron.SetCheck(BST_CHECKED);
	else
		m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);

	//Pour "CE_UNEX_SKM_STATE_INITCIK2_IDLE"
	alarm = equip->DecodeAlarm(alarmList[12]);
	if (alarm.used)
		m_CeUnexStateInitcik2Idle.SetCheck(BST_CHECKED);
	else
		m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);

	//Pour "CE_UNEX_SKM_STATE_DELCIKUSER_IDLE"
	alarm = equip->DecodeAlarm(alarmList[13]);
	if (alarm.used)
		m_CeUnexStateDelcikuserIdle.SetCheck(BST_CHECKED);
	else
		m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);

	//Pour "CE_CIK_SYSTEM_ERROR"
	alarm = equip->DecodeAlarm(alarmList[14]);
	if (alarm.used)
		m_CeCikSystemError.SetCheck(BST_CHECKED);
	else
		m_CeCikSystemError.SetCheck(BST_UNCHECKED);

	//Pour "CE_ACTIV_ERROR_CRYSETUP"
	alarm = equip->DecodeAlarm(alarmList[15]);
	if (alarm.used)
		m_CeActivErrorCrysetup.SetCheck(BST_CHECKED);
	else
		m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);

	//Pour "CE_ACTIV_ERROR_CRYSETUP2"
	alarm = equip->DecodeAlarm(alarmList[16]);
	if (alarm.used)
		m_CeActivErrorCrysetup2.SetCheck(BST_CHECKED);
	else
		m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);

	//Pour "CE_PREP_ERROR_COMSETUP"
	alarm = equip->DecodeAlarm(alarmList[17]);
	if (alarm.used)
		m_CePrepErrorComsetup.SetCheck(BST_CHECKED);
	else
		m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);

	//Pour "CE_UNEX_ONLINE_MODE"
	alarm = equip->DecodeAlarm(alarmList[18]);
	if (alarm.used)
		m_CeUnexOnlineMode.SetCheck(BST_CHECKED);
	else
		m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);

	//Pour "CE_START_ERROR_ONLINE"
	alarm = equip->DecodeAlarm(alarmList[19]);
	if (alarm.used)
		m_CeStartErrorOnline.SetCheck(BST_CHECKED);
	else
		m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);

	//Pour "CE_STARTRX_ERROR_ONLINE"
	alarm = equip->DecodeAlarm(alarmList[20]);
	if (alarm.used)
		m_CeStartrxErrorOnline.SetCheck(BST_CHECKED);
	else
		m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);

	//Pour "CE_STARTTX_ERROR_ONLINE"
	alarm = equip->DecodeAlarm(alarmList[21]);
	if (alarm.used)
		m_CeStarttxErrorOnline.SetCheck(BST_CHECKED);
	else
		m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);

	//Pour "CRYPTOALARM_NOTL"
	alarm = equip->DecodeAlarm(alarmList[22]);
	if (alarm.used)
		m_CryptoalarmNotl.SetCheck(BST_CHECKED);
	else
		m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);

	//Pour "CRYPTOALARM_TAMPER"
	alarm = equip->DecodeAlarm(alarmList[23]);
	if (alarm.used)
		m_CryptoalarmTamper.SetCheck(BST_CHECKED);
	else
		m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);

	//Pour "CRYPTOALARM_GLOBAL"
	alarm = equip->DecodeAlarm(alarmList[24]);
	if (alarm.used)
		m_CryptoalarmGlobal.SetCheck(BST_CHECKED);
	else
		m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);

	UpdateData(FALSE);

}

void DlgED42Pannes::SaveData()
{
	TAlarm alarm;
	TVectorAlarm alarmList = equip->getAlarms();

	//Pour "ZSS_MANAG_CRC"
	alarm = equip->DecodeAlarm(alarmList[0]);
	alarm.used = m_ZssManagCrc.GetCheck()==BST_CHECKED;
	alarmList[0] = equip->EncodeAlarm(alarm);

	//Pour "ZSS_UNEX_SKM_STATE_STARUP"
	alarm = equip->DecodeAlarm(alarmList[1]);
	alarm.used = m_ZssUnexStateStartup.GetCheck()==BST_CHECKED;
	alarmList[1] = equip->EncodeAlarm(alarm);

	//Pour "KE_UNEX_SKM_STATE_INDISPOSED"
	alarm = equip->DecodeAlarm(alarmList[2]);
	alarm.used = m_KeUnexStateIndisposed.GetCheck()==BST_CHECKED;
	alarmList[2] = equip->EncodeAlarm(alarm);

	//Pour "ZSS_FLASH_MAGIC_ERROR"
	alarm = equip->DecodeAlarm(alarmList[3]);
	alarm.used = m_ZssFlashMagicError.GetCheck()==BST_CHECKED;
	alarmList[3] = equip->EncodeAlarm(alarm);

	//Pour "ZSS_FLASH_ERROR"
	alarm = equip->DecodeAlarm(alarmList[4]);
	alarm.used = m_ZssFlashError.GetCheck()==BST_CHECKED;
	alarmList[4] = equip->EncodeAlarm(alarm);

	//Pour "ZSS_UNEX_SKM_STATE_IDLE"
	alarm = equip->DecodeAlarm(alarmList[5]);
	alarm.used = m_ZssUnexStateIdle.GetCheck()==BST_CHECKED;
	alarmList[5] = equip->EncodeAlarm(alarm);

	//Pour "ZSS_ERROR_INTERFACEBIT"
	alarm = equip->DecodeAlarm(alarmList[6]);
	alarm.used = m_ZssErrorInterfacebit.GetCheck()==BST_CHECKED;
	alarmList[6] = equip->EncodeAlarm(alarm);

	//Pour "CE_SKM_TIMEOUT_AOUT"
	alarm = equip->DecodeAlarm(alarmList[7]);
	alarm.used = m_CeSkmTimeoutAout.GetCheck()==BST_CHECKED;
	alarmList[7] = equip->EncodeAlarm(alarm);

	//Pour "CE_PWDTEST_ERROR"
	alarm = equip->DecodeAlarm(alarmList[8]);
	alarm.used = m_CePwdtestError.GetCheck()==BST_CHECKED;
	alarmList[8] = equip->EncodeAlarm(alarm);

	//Pour "CE_VAR_STAT_ERROR"
	alarm = equip->DecodeAlarm(alarmList[9]);
	alarm.used = m_CeVarStatError.GetCheck()==BST_CHECKED;
	alarmList[9] = equip->EncodeAlarm(alarm);

	//Pour "CE_UNEX_SKM_STATE_AOUT"
	alarm = equip->DecodeAlarm(alarmList[10]);
	alarm.used = m_CeUnexStateAout.GetCheck()==BST_CHECKED;
	alarmList[10] = equip->EncodeAlarm(alarm);

	//Pour "CE_UNEX_SKM_STATE_POWERON"
	alarm = equip->DecodeAlarm(alarmList[11]);
	alarm.used = m_CeUnexStatePoweron.GetCheck()==BST_CHECKED;
	alarmList[11] = equip->EncodeAlarm(alarm);

	//Pour "CE_UNEX_SKM_STATE_INITCIK2_IDLE"
	alarm = equip->DecodeAlarm(alarmList[12]);
	alarm.used = m_CeUnexStateInitcik2Idle.GetCheck()==BST_CHECKED;
	alarmList[12] = equip->EncodeAlarm(alarm);

	//Pour "CE_UNEX_SKM_STATE_DELCIKUSER_IDLE"
	alarm = equip->DecodeAlarm(alarmList[13]);
	alarm.used = m_CeUnexStateDelcikuserIdle.GetCheck()==BST_CHECKED;
	alarmList[13] = equip->EncodeAlarm(alarm);

	//Pour "CE_CIK_SYSTEM_ERROR"
	alarm = equip->DecodeAlarm(alarmList[14]);
	alarm.used = m_CeCikSystemError.GetCheck()==BST_CHECKED;
	alarmList[14] = equip->EncodeAlarm(alarm);

	//Pour "CE_ACTIV_ERROR_CRYSETUP"
	alarm = equip->DecodeAlarm(alarmList[15]);
	alarm.used = m_CeActivErrorCrysetup.GetCheck()==BST_CHECKED;
	alarmList[15] = equip->EncodeAlarm(alarm);

	//Pour "CE_ACTIV_ERROR_CRYSETUP2"
	alarm = equip->DecodeAlarm(alarmList[16]);
	alarm.used = m_CeActivErrorCrysetup2.GetCheck()==BST_CHECKED;
	alarmList[16] = equip->EncodeAlarm(alarm);

	//Pour "CE_PREP_ERROR_COMSETUP"
	alarm = equip->DecodeAlarm(alarmList[17]);
	alarm.used = m_CePrepErrorComsetup.GetCheck()==BST_CHECKED;
	alarmList[17] = equip->EncodeAlarm(alarm);

	//Pour "CE_UNEX_ONLINE_MODE"
	alarm = equip->DecodeAlarm(alarmList[18]);
	alarm.used = m_CeUnexOnlineMode.GetCheck()==BST_CHECKED;
	alarmList[18] = equip->EncodeAlarm(alarm);

	//Pour "CE_START_ERROR_ONLINE"
	alarm = equip->DecodeAlarm(alarmList[19]);
	alarm.used = m_CeStartErrorOnline.GetCheck()==BST_CHECKED;
	alarmList[19] = equip->EncodeAlarm(alarm);

	//Pour "CE_STARTRX_ERROR_ONLINE"
	alarm = equip->DecodeAlarm(alarmList[20]);
	alarm.used = m_CeStartrxErrorOnline.GetCheck()==BST_CHECKED;
	alarmList[20] = equip->EncodeAlarm(alarm);

	//Pour "CE_STARTTX_ERROR_ONLINE"
	alarm = equip->DecodeAlarm(alarmList[21]);
	alarm.used = m_CeStarttxErrorOnline.GetCheck()==BST_CHECKED;
	alarmList[21] = equip->EncodeAlarm(alarm);

	//Pour "CRYPTOALARM_NOTL"
	alarm = equip->DecodeAlarm(alarmList[22]);
	alarm.used = m_CryptoalarmNotl.GetCheck()==BST_CHECKED;
	alarmList[22] = equip->EncodeAlarm(alarm);

	//Pour "CRYPTOALARM_TAMPER"
	alarm = equip->DecodeAlarm(alarmList[23]);
	alarm.used = m_CryptoalarmTamper.GetCheck()==BST_CHECKED;
	alarmList[23] = equip->EncodeAlarm(alarm);
	equip->SetKeStatus(TAMPER);

	//Pour "CRYPTOALARM_GLOBAL"
	alarm = equip->DecodeAlarm(alarmList[24]);
	alarm.used = m_CryptoalarmGlobal.GetCheck()==BST_CHECKED;
	alarmList[24] = equip->EncodeAlarm(alarm);

	equip->setAlarms(alarmList);

	equip->setModifErreurPanne(FALSE);

	//Recherche si il y a au moins une erreur
	equip->SetAlarm(FALSE);
	for(int i=0;i<equip->getAlarms().size();i++)
	{
		alarm = equip->DecodeAlarm(alarmList[i]);
		if (alarm.used)
		{
			equip->SetAlarm(TRUE);
		}
	}
}

void DlgED42Pannes::OnOK()
{
	if(equip->getModifErreurPanne())
	{
		SaveData();
	}
}

void DlgED42Pannes::OnCancel()
{
	LoadData();
	equip->setModifErreurPanne(FALSE);
}

void DlgED42Pannes::OnCheckZssManagCrc()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckZssUnexStateStartup()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckKeUnexStateIndisposed()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckZssFlashMagicError()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckZssFlashError()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckZssUnexStateIdle()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckZssErrorInterfacebit()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeSkmTimeoutAout()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCePwdtestError()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeVarStatError()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeUnexStateAout()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeUnexStatePoweron()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeUnexStateInitcik2Idle()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeUnexStateDelcikuserIdle()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeCikSystemError()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeActivErrorCrysetup()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeActivErrorCrysetup2()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCePrepErrorComsetup()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeUnexOnlineMode()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeStartErrorOnline()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeStartrxErrorOnline()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCeStarttxErrorOnline()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCryptoalarmNotl()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCryptoalarmTamper()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmGlobal.SetCheck(BST_UNCHECKED);
}

void DlgED42Pannes::OnCheckCryptoalarmGlobal()
{
	equip->setModifErreurPanne(TRUE);

	m_ZssManagCrc.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateStartup.SetCheck(BST_UNCHECKED);
	m_KeUnexStateIndisposed.SetCheck(BST_UNCHECKED);
	m_ZssFlashMagicError.SetCheck(BST_UNCHECKED);
	m_ZssFlashError.SetCheck(BST_UNCHECKED);
	m_ZssUnexStateIdle.SetCheck(BST_UNCHECKED);
	m_ZssErrorInterfacebit.SetCheck(BST_UNCHECKED);
	m_CeSkmTimeoutAout.SetCheck(BST_UNCHECKED);
	m_CePwdtestError.SetCheck(BST_UNCHECKED);
	m_CeVarStatError.SetCheck(BST_UNCHECKED);
	m_CeUnexStateAout.SetCheck(BST_UNCHECKED);
	m_CeUnexStatePoweron.SetCheck(BST_UNCHECKED);
	m_CeUnexStateInitcik2Idle.SetCheck(BST_UNCHECKED);
	m_CeUnexStateDelcikuserIdle.SetCheck(BST_UNCHECKED);
	m_CeCikSystemError.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup.SetCheck(BST_UNCHECKED);
	m_CeActivErrorCrysetup2.SetCheck(BST_UNCHECKED);
	m_CePrepErrorComsetup.SetCheck(BST_UNCHECKED);
	m_CeUnexOnlineMode.SetCheck(BST_UNCHECKED);
	m_CeStartErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStartrxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CeStarttxErrorOnline.SetCheck(BST_UNCHECKED);
	m_CryptoalarmNotl.SetCheck(BST_UNCHECKED);
	m_CryptoalarmTamper.SetCheck(BST_UNCHECKED);
}
