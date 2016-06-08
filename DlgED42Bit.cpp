// DlgED42Bit.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42Bit.h"
#include "Divers\Logger.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

using namespace std;
using namespace CPlusPlusLogging;

extern Logger pLogger;

/////////////////////////////////////////////////////////////////////////////
// DlgED42Bit dialog


DlgED42Bit::DlgED42Bit(CEquipED42* eqp,CWnd* pParent /*=NULL*/)
	: CDialog(DlgED42Bit::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgED42Bit)
	m_resultTest = _T("");
	//}}AFX_DATA_INIT
	this->eqp = eqp;
}


void DlgED42Bit::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgED42Bit)
	DDX_Control(pDX, IDC_BUTTON_LANCER_TEST, c_lancerTest);
	DDX_Control(pDX, IDC_CHECK_RAM_TEST, c_ramTest);
	DDX_Control(pDX, IDC_CHECK_INTEGRITY_SOFTWARE, c_integritySoftware);
	DDX_Control(pDX, IDC_CHECK_FLASH_MEMORY_TEST, c_flashMemoryTest);
	DDX_Control(pDX, IDC_CHECK_EN_DECRYPTION_SIGNAL, c_enAndDecryptionSignal);
	DDX_Control(pDX, IDC_CHECK_CHECKING_SUPPLY_VOLTAGE, c_checkingSupplyVoltage);
	DDX_Control(pDX, IDC_CHECK_BIT_WITHOUT_TEST_PLUGS, c_bitTestPlugs);
	DDX_Control(pDX, IDC_CHECK_BIT_HEADSET, c_bitHeadset);
	DDX_Control(pDX, IDC_CHECK_BIT_DS_101_TEST, c_bitDS101Test);
	DDX_Control(pDX, IDC_CHECK_BATTERY_TEST, c_batteryTest);
	DDX_Control(pDX, IDC_CHECK_BIT_CONTROL_UNIT, c_bitControlUnit);
	DDX_Text(pDX, IDC_EDIT_RESULT_TEST, m_resultTest);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgED42Bit, CDialog)
	//{{AFX_MSG_MAP(DlgED42Bit)
	ON_BN_CLICKED(IDC_BUTTON_LANCER_TEST, OnButtonLancerTest)
	ON_BN_CLICKED(IDC_CHECK_BATTERY_TEST, OnCheckBatteryTest)
	ON_BN_CLICKED(IDC_CHECK_BIT_CONTROL_UNIT, OnCheckBitControlUnit)
	ON_BN_CLICKED(IDC_CHECK_BIT_WITHOUT_TEST_PLUGS, OnCheckBitWithoutTestPlugs)
	ON_BN_CLICKED(IDC_CHECK_BIT_DS_101_TEST, OnCheckBitDs101Test)
	ON_BN_CLICKED(IDC_CHECK_BIT_HEADSET, OnCheckBitHeadset)
	ON_BN_CLICKED(IDC_CHECK_CHECKING_SUPPLY_VOLTAGE, OnCheckCheckingSupplyVoltage)
	ON_BN_CLICKED(IDC_CHECK_EN_DECRYPTION_SIGNAL, OnCheckEnDecryptionSignal)
	ON_BN_CLICKED(IDC_CHECK_FLASH_MEMORY_TEST, OnCheckFlashMemoryTest)
	ON_BN_CLICKED(IDC_CHECK_INTEGRITY_SOFTWARE, OnCheckIntegritySoftware)
	ON_BN_CLICKED(IDC_CHECK_RAM_TEST, OnCheckRamTest)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgED42Bit message handlers

BOOL DlgED42Bit::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadData();

	return TRUE;  
}

void DlgED42Bit::LoadData()
{
	pLogger.LOG_TRACE("Dans DlgED42Bit::LoadData()!");

	//Partie Power on bit
	c_ramTest.EnableWindow(!eqp->GetMarcheEd42());
	c_integritySoftware.EnableWindow(!eqp->GetMarcheEd42());
	c_flashMemoryTest.EnableWindow(!eqp->GetMarcheEd42());
	c_enAndDecryptionSignal.EnableWindow(!eqp->GetMarcheEd42());
	c_checkingSupplyVoltage.EnableWindow(!eqp->GetMarcheEd42());

	//Partie Manually
	c_bitTestPlugs.EnableWindow(eqp->GetMarcheEd42());
	c_bitHeadset.EnableWindow(eqp->GetMarcheEd42());
	c_bitDS101Test.EnableWindow(eqp->GetMarcheEd42());
	c_batteryTest.EnableWindow(eqp->GetMarcheEd42());
	c_bitControlUnit.EnableWindow(eqp->GetMarcheEd42());

	c_ramTest.SetCheck(eqp->getPowerBitTable(POWER_ON_BIT_RAM_TEST));
	c_integritySoftware.SetCheck(eqp->getPowerBitTable(POWER_ON_BIT_INTEGRITY_SOFTWARE));
	c_flashMemoryTest.SetCheck(eqp->getPowerBitTable(POWER_ON_BIT_FLASH_MEMORY_TEST));
	c_enAndDecryptionSignal.SetCheck(eqp->getPowerBitTable(POWER_ON_BIT_EN_DECRYPTION_SIGNAL));
	c_checkingSupplyVoltage.SetCheck(eqp->getPowerBitTable(POWER_ON_BIT_CHECKING_SUPPLY_VOLTAGE));

	c_bitTestPlugs.SetCheck(eqp->getBitManuallyTable(BIT_MANUALLY_BIT_TEST_PLUGS));
	c_bitHeadset.SetCheck(eqp->getBitManuallyTable(BIT_MANUALLY_BIT_HEADSET));
	c_bitDS101Test.SetCheck(eqp->getBitManuallyTable(BIT_MANUALLY_BIT_DS101_TEST));
	c_batteryTest.SetCheck(eqp->getBitManuallyTable(BIT_MANUALLY_BATTERY_TEST));
	c_bitControlUnit.SetCheck(eqp->getBitManuallyTable(BIT_MANUALLY_BIT_CONTROL_UNIT));

	pLogger.LOG_TRACE("Fin DlgED42Bit::LoadData()!");

}

void DlgED42Bit::SaveData()
{
	pLogger.LOG_TRACE("Dans DlgED42Bit::SaveData()!");

	eqp->setPowerBitTable(POWER_ON_BIT_RAM_TEST,c_ramTest.GetCheck()==BST_CHECKED);
	eqp->setPowerBitTable(POWER_ON_BIT_INTEGRITY_SOFTWARE,c_integritySoftware.GetCheck()==BST_CHECKED);
	eqp->setPowerBitTable(POWER_ON_BIT_FLASH_MEMORY_TEST,c_flashMemoryTest.GetCheck()==BST_CHECKED);
	eqp->setPowerBitTable(POWER_ON_BIT_EN_DECRYPTION_SIGNAL,c_enAndDecryptionSignal.GetCheck()==BST_CHECKED);
	eqp->setPowerBitTable(POWER_ON_BIT_CHECKING_SUPPLY_VOLTAGE,c_checkingSupplyVoltage.GetCheck()==BST_CHECKED);

	eqp->setBitManuallyTable(BIT_MANUALLY_BIT_TEST_PLUGS,c_bitTestPlugs.GetCheck()==BST_CHECKED);
	eqp->setBitManuallyTable(BIT_MANUALLY_BIT_HEADSET,c_bitHeadset.GetCheck()==BST_CHECKED);
	eqp->setBitManuallyTable(BIT_MANUALLY_BIT_DS101_TEST,c_bitDS101Test.GetCheck()==BST_CHECKED);
	eqp->setBitManuallyTable(BIT_MANUALLY_BATTERY_TEST,c_batteryTest.GetCheck()==BST_CHECKED);
	eqp->setBitManuallyTable(BIT_MANUALLY_BIT_CONTROL_UNIT,c_bitControlUnit.GetCheck()==BST_CHECKED);

	//Recherche pour la mise à jour des flags errors et alarms pour le SYS et vérifier 
	//si il faut référencer l'erreur ou l'alarme dans leur table respective.

	// ------------------- Pour manually -------------------
	if(eqp->getBitManuallyTable(BIT_MANUALLY_BIT_TEST_PLUGS))
	{
		//Pour l'erreur
		eqp->setErrorTable(START_ERROR, TRUE);
		//Position du flag de l'erreur
		eqp->SetError(TRUE);
	}

	if(eqp->getBitManuallyTable(BIT_MANUALLY_BIT_CONTROL_UNIT))
	{
		//Pour l'alarme 
		eqp->setAlarmTable(ZSS_FLASH_ERROR,TRUE);
		//Position du flag de l'alarme
		eqp->SetAlarm(1);						//eqp->SetAlarm(TRUE);
	}

	eqp->setModifErreurPanne(FALSE);

	pLogger.LOG_TRACE("Fin DlgED42Bit::SaveData()!");
}

void DlgED42Bit::OnOK() 
{
	SaveData();
	eqp->setModifErreurPanne(FALSE);
}

void DlgED42Bit::OnCancel() 
{
	LoadData();
	eqp->setModifErreurPanne(FALSE);
}

void DlgED42Bit::OnButtonLancerTest() 
{
	SaveData();
	
	if(eqp->getBitManuallyTable(BIT_MANUALLY_BIT_TEST_PLUGS))
	{
		eqp->setBitManuallyResultTable(BIT_MANUALLY_BIT_TEST_PLUGS,!eqp->getBitManuallyResultTable(BIT_MANUALLY_BIT_TEST_PLUGS));

		if(eqp->getBitManuallyResultTable(BIT_MANUALLY_BIT_TEST_PLUGS))			
			m_resultTest = "BIT W/O TSTPLUGS ERROR!";
		else
			m_resultTest = "BIT W/O TSTPLUGS SUCCESS";		
	}
	else if(eqp->getBitManuallyTable(BIT_MANUALLY_BIT_HEADSET))
	{
		eqp->setBitManuallyResultTable(BIT_MANUALLY_BIT_HEADSET,!eqp->getBitManuallyResultTable(BIT_MANUALLY_BIT_HEADSET));

		if(eqp->getBitManuallyResultTable(BIT_MANUALLY_BIT_HEADSET))			
			m_resultTest = "ERROR !";
		else
			m_resultTest = "SUCCESS";
	}
	else if(eqp->getBitManuallyTable(BIT_MANUALLY_BIT_DS101_TEST))
	{
		eqp->setBitManuallyResultTable(BIT_MANUALLY_BIT_DS101_TEST,!eqp->getBitManuallyResultTable(BIT_MANUALLY_BIT_DS101_TEST));

		if(eqp->getBitManuallyResultTable(BIT_MANUALLY_BIT_DS101_TEST))			
			m_resultTest = "DS101 TEST ERROR!";
		else
			m_resultTest = "DS101 TEST SUCCESS!";
	}
	else if(eqp->getBitManuallyTable(BIT_MANUALLY_BATTERY_TEST))
	{
		eqp->setBitManuallyResultTable(BIT_MANUALLY_BATTERY_TEST,!eqp->getBitManuallyResultTable(BIT_MANUALLY_BATTERY_TEST));

		if(eqp->getBitManuallyResultTable(BIT_MANUALLY_BATTERY_TEST))			
			m_resultTest = "BATTERY TEST ERROR!";
		else
			m_resultTest = "BATTERY TEST SUCCESS!";
	}
	else if(eqp->getBitManuallyTable(BIT_MANUALLY_BIT_CONTROL_UNIT))
	{
		eqp->setBitManuallyResultTable(BIT_MANUALLY_BIT_CONTROL_UNIT,!eqp->getBitManuallyResultTable(BIT_MANUALLY_BIT_CONTROL_UNIT));

		if(eqp->getBitManuallyResultTable(BIT_MANUALLY_BIT_CONTROL_UNIT))			
			m_resultTest = "FLASH ERROR!";
		else
			m_resultTest = "FLASH SUCCESS!";
	}
	else
		m_resultTest = "";

	UpdateData(FALSE);
}

void DlgED42Bit::OnCheckBatteryTest() 
{
	c_bitTestPlugs.SetCheck(FALSE);
	c_bitHeadset.SetCheck(FALSE);
	c_bitDS101Test.SetCheck(FALSE);
	c_bitControlUnit.SetCheck(FALSE);

	//Element à changer sur l'IHM
	eqp->setModifErreurPanne(TRUE);
}

void DlgED42Bit::OnCheckBitControlUnit() 
{
	c_bitTestPlugs.SetCheck(FALSE);
	c_bitHeadset.SetCheck(FALSE);
	c_bitDS101Test.SetCheck(FALSE);
	c_batteryTest.SetCheck(FALSE);	

	//Element à changer sur l'IHM
	eqp->setModifErreurPanne(TRUE);
}

void DlgED42Bit::OnCheckBitWithoutTestPlugs() 
{
	c_bitControlUnit.SetCheck(FALSE);
	c_bitHeadset.SetCheck(FALSE);
	c_bitDS101Test.SetCheck(FALSE);
	c_batteryTest.SetCheck(FALSE);	

	//Element à changer sur l'IHM
	eqp->setModifErreurPanne(TRUE);
}

void DlgED42Bit::OnCheckBitDs101Test() 
{
	c_bitControlUnit.SetCheck(FALSE);
	c_bitHeadset.SetCheck(FALSE);
	c_bitTestPlugs.SetCheck(FALSE);
	c_batteryTest.SetCheck(FALSE);	

	//Element à changer sur l'IHM
	eqp->setModifErreurPanne(TRUE);
}

void DlgED42Bit::OnCheckBitHeadset() 
{
	c_bitControlUnit.SetCheck(FALSE);
	c_bitDS101Test.SetCheck(FALSE);
	c_bitTestPlugs.SetCheck(FALSE);
	c_batteryTest.SetCheck(FALSE);

	//Element à changer sur l'IHM
	eqp->setModifErreurPanne(TRUE);
}

void DlgED42Bit::OnCheckCheckingSupplyVoltage() 
{
	//Element à changer sur l'IHM
	eqp->setModifErreurPanne(TRUE);
}

void DlgED42Bit::OnCheckEnDecryptionSignal() 
{
	//Element à changer sur l'IHM
	eqp->setModifErreurPanne(TRUE);
}

void DlgED42Bit::OnCheckFlashMemoryTest() 
{
	//Element à changer sur l'IHM
	eqp->setModifErreurPanne(TRUE);
}

void DlgED42Bit::OnCheckIntegritySoftware() 
{
	//Element à changer sur l'IHM
	eqp->setModifErreurPanne(TRUE);
}

void DlgED42Bit::OnCheckRamTest() 
{
	//Element à changer sur l'IHM
	eqp->setModifErreurPanne(TRUE);
}
