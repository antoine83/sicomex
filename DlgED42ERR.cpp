// DlgED42ERR.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42ERR.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgED42ERR dialog


DlgED42ERR::DlgED42ERR(CEquipED42 * equip,CWnd* pParent )
	: CDialog(DlgED42ERR::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgED42ERR)
	//}}AFX_DATA_INIT
	this->equip=equip;
}


void DlgED42ERR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgED42ERR)
	DDX_Control(pDX, IDC_COMBO_ERROR_CRYPTO, m_ErrorCrypto);
	DDX_Control(pDX, IDC_CHECK_WRONG_PASSWORD, m_WrongPassword);
	DDX_Control(pDX, IDC_CHECK_WRONG_DLD_PASSWORD, m_WrongDldPassword);
	DDX_Control(pDX, IDC_CHECK_WRONG_CIK, m_WrongCik);
	DDX_Control(pDX, IDC_CHECK_VARIABLE_MANAGEMENT, m_VariableManagement);
	DDX_Control(pDX, IDC_CHECK_UPDATE_LIMIT, m_UpdateLimit);
	DDX_Control(pDX, IDC_CHECK_TIMEOUT_CIK, m_TimeoutCik);
	DDX_Control(pDX, IDC_CHECK_START_ERROR, m_StartError);
	DDX_Control(pDX, IDC_CHECK_SELECT_VARIABLE, m_SelectVariable);
	DDX_Control(pDX, IDC_CHECK_PASSWORD_CHECK, m_PasswordCheck);
	DDX_Control(pDX, IDC_CHECK_MISSING_CIK, m_MissingCik);
	DDX_Control(pDX, IDC_CHECK_FORMAT_ERROR, m_FormatError);
	DDX_Control(pDX, IDC_CHECK_F101_ERROR_VARIABLE, m_F101ErrorVariable);
	DDX_Control(pDX, IDC_CHECK_F101_ERROR_KEK, m_F101ErrorKek);
	DDX_Control(pDX, IDC_CHECK_ERROR_SOFTWARE, m_ErrorSoftware);
	DDX_Control(pDX, IDC_CHECK_ERROR_CONNECT_CIK, m_ErrorConnectCik);
	DDX_Control(pDX, IDC_CHECK_CONFIG_ERROR, m_ConfigError);
	DDX_Control(pDX, IDC_CHECK_BILATERAL_UPDATE_ERROR, m_BilateralUpdateError);
	DDX_Control(pDX, IDC_CHECK_BILATERAL_TAG_ERROR, m_BilateralTagError);
	DDX_Control(pDX, IDC_CHECK_NO_VARIABLE, m_NoVariable);
	DDX_Control(pDX, IDC_CHECK_F101_ERROR_ACTION, m_F101ErrorAction);
	DDX_Control(pDX, IDC_CHECK_F101_TIMEOUT, m_F101Timeout);
	DDX_Control(pDX, IDC_CHECK_F101_INTERFACE, m_F101Interface);
	DDX_Control(pDX, IDC_COMBO_ERROR_CODES, m_ErrorCodes);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgED42ERR, CDialog)
	//{{AFX_MSG_MAP(DlgED42ERR)
	ON_CBN_SELCHANGE(IDC_COMBO_ERROR_CODES, OnSelchangeComboErrorCodes)
	ON_BN_CLICKED(IDC_CHECK_F101_INTERFACE, OnCheckF101Interface)
	ON_BN_CLICKED(IDC_CHECK_F101_TIMEOUT, OnCheckF101Timeout)
	ON_BN_CLICKED(IDC_CHECK_F101_ERROR_ACTION, OnCheckF101ErrorAction)
	ON_BN_CLICKED(IDC_CHECK_NO_VARIABLE, OnCheckNoVariable)
	ON_BN_CLICKED(IDC_CHECK_WRONG_PASSWORD, OnCheckWrongPassword)
	ON_BN_CLICKED(IDC_CHECK_F101_ERROR_VARIABLE, OnCheckF101ErrorVariable)
	ON_BN_CLICKED(IDC_CHECK_F101_ERROR_KEK, OnCheckF101ErrorKek)
	ON_BN_CLICKED(IDC_CHECK_CONFIG_ERROR, OnCheckConfigError)
	ON_BN_CLICKED(IDC_CHECK_START_ERROR, OnCheckStartError)
	ON_BN_CLICKED(IDC_CHECK_ERROR_SOFTWARE, OnCheckErrorSoftware)
	ON_BN_CLICKED(IDC_CHECK_SELECT_VARIABLE, OnCheckSelectVariable)
	ON_BN_CLICKED(IDC_CHECK_UPDATE_LIMIT, OnCheckUpdateLimit)
	ON_BN_CLICKED(IDC_CHECK_BILATERAL_UPDATE_ERROR, OnCheckBilateralUpdateError)
	ON_BN_CLICKED(IDC_CHECK_BILATERAL_TAG_ERROR, OnCheckBilateralTagError)
	ON_BN_CLICKED(IDC_CHECK_WRONG_DLD_PASSWORD, OnCheckWrongDldPassword)
	ON_BN_CLICKED(IDC_CHECK_FORMAT_ERROR, OnCheckFormatError)
	ON_BN_CLICKED(IDC_CHECK_ERROR_CONNECT_CIK, OnCheckErrorConnectCik)
	ON_BN_CLICKED(IDC_CHECK_VARIABLE_MANAGEMENT, OnCheckVariableManagement)
	ON_CBN_SELCHANGE(IDC_COMBO_ERROR_CRYPTO, OnSelchangeComboErrorCrypto)
	ON_BN_CLICKED(IDC_CHECK_MISSING_CIK, OnCheckMissingCik)
	ON_BN_CLICKED(IDC_CHECK_WRONG_CIK, OnCheckWrongCik)
	ON_BN_CLICKED(IDC_CHECK_TIMEOUT_CIK, OnCheckTimeoutCik)
	ON_BN_CLICKED(IDC_CHECK_PASSWORD_CHECK, OnCheckPasswordCheck)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgED42ERR message handlers
BOOL DlgED42ERR::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadData();

	return TRUE;
}


void DlgED42ERR::LoadData()
{
	TError error;
	TVectorError errorList = equip->getErrors();

	//Pour "error codes of cryptomodul"
	error = equip->DecodeError(errorList[ERROR_CODES]);
	if (error.used)
		m_ErrorCodes.SetCurSel(error.extendedCodes);
	else
		m_ErrorCodes.SetCurSel(0);

	//Pour "F101 interface not activated"
	error = equip->DecodeError(errorList[F101_INTERFACE]);
	if (error.used)
		m_F101Interface.SetCheck(BST_CHECKED);
	else
		m_F101Interface.SetCheck(BST_UNCHECKED);
	//Pour "F101 timeout from SKM"
	error = equip->DecodeError(errorList[F101_TIMEOUT]);
	if (error.used)
		m_F101Timeout.SetCheck(BST_CHECKED);
	else
		m_F101Timeout.SetCheck(BST_UNCHECKED);

	//Pour "F101 error - give header action"
	error = equip->DecodeError(errorList[F101_ERROR_ACTION]);
	if (error.used)
		m_F101ErrorAction.SetCheck(BST_CHECKED);
	else
		m_F101ErrorAction.SetCheck(BST_UNCHECKED);

	//Pour "no variable available"
	error = equip->DecodeError(errorList[NO_VARIABLE_AVAILABLE]);
	if (error.used)
		m_NoVariable.SetCheck(BST_CHECKED);
	else
		m_NoVariable.SetCheck(BST_UNCHECKED);

	//Pour "wrong password type"
	error = equip->DecodeError(errorList[WRONG_PASSWORD]);
	if (error.used)
		m_WrongPassword.SetCheck(BST_CHECKED);
	else
		m_WrongPassword.SetCheck(BST_UNCHECKED);

	//Pour "F101 error - store variable"
	error = equip->DecodeError(errorList[F101_ERROR_VARIABLE]);
	if (error.used)
		m_F101ErrorVariable.SetCheck(BST_CHECKED);
	else
		m_F101ErrorVariable.SetCheck(BST_UNCHECKED);

	//Pour "F101 error - store KEK"
	error = equip->DecodeError(errorList[F101_ERROR_KEK]);
	if (error.used)
		m_F101ErrorKek.SetCheck(BST_CHECKED);
	else
		m_F101ErrorKek.SetCheck(BST_UNCHECKED);

	//Pour "configuration error"
	error = equip->DecodeError(errorList[CONFIGURATION_ERROR]);
	if (error.used)
		m_ConfigError.SetCheck(BST_CHECKED);
	else
		m_ConfigError.SetCheck(BST_UNCHECKED);

	//Pour "start error"
	error = equip->DecodeError(errorList[START_ERROR]);
	if (error.used)
		m_StartError.SetCheck(BST_CHECKED);
	else
		m_StartError.SetCheck(BST_UNCHECKED);

	//Pour "error in software"
	error = equip->DecodeError(errorList[ERROR_SOFTWARE]);
	if (error.used)
		m_ErrorSoftware.SetCheck(BST_CHECKED);
	else
		m_ErrorSoftware.SetCheck(BST_UNCHECKED);

	//Pour "selected variable not defined"
	error = equip->DecodeError(errorList[VARIABLE_NOT_DEFINED]);
	if (error.used)
		m_SelectVariable.SetCheck(BST_CHECKED);
	else
		m_SelectVariable.SetCheck(BST_UNCHECKED);

	//Pour "update limit exceeded"
	error = equip->DecodeError(errorList[UPDATE_LIMIT_EXCEEDED]);
	if (error.used)
		m_UpdateLimit.SetCheck(BST_CHECKED);
	else
		m_UpdateLimit.SetCheck(BST_UNCHECKED);

	//Pour "bilateral update global error"
	error = equip->DecodeError(errorList[BILATERAL_UPDATE_ERROR]);
	if (error.used)
		m_BilateralUpdateError.SetCheck(BST_CHECKED);
	else
		m_BilateralUpdateError.SetCheck(BST_UNCHECKED);

	//Pour "bilateral tag global error"
	error = equip->DecodeError(errorList[BILATERAL_TAG_ERROR]);
	if (error.used)
		m_BilateralTagError.SetCheck(BST_CHECKED);
	else
		m_BilateralTagError.SetCheck(BST_UNCHECKED);

	//Pour "wrong dld password fron user"
	error = equip->DecodeError(errorList[WRONG_DLD_PASSWORD_USER]);
	if (error.used)
		m_WrongDldPassword.SetCheck(BST_CHECKED);
	else
		m_WrongDldPassword.SetCheck(BST_UNCHECKED);

	//Pour "format error"
	error = equip->DecodeError(errorList[FORMAT_ERROR]);
	if (error.used)
		m_FormatError.SetCheck(BST_CHECKED);
	else
		m_FormatError.SetCheck(BST_UNCHECKED);

	//Pour "error while connecting CIK"
	error = equip->DecodeError(errorList[ERROR_CONNECTING_CIK]);
	if (error.used)
		m_ErrorConnectCik.SetCheck(BST_CHECKED);
	else
		m_ErrorConnectCik.SetCheck(BST_UNCHECKED);

	//Pour "variable management"
	error = equip->DecodeError(errorList[VARIABLE_MANAGEMENT]);
	if (error.used)
		m_VariableManagement.SetCheck(BST_CHECKED);
	else
		m_VariableManagement.SetCheck(BST_UNCHECKED);

	//Pour "missing CIK"
	error = equip->DecodeError(errorList[MISSING_CIK]);
	if (error.used)
		m_MissingCik.SetCheck(BST_CHECKED);
	else
		m_MissingCik.SetCheck(BST_UNCHECKED);

	//Pour "wrong condition CIK"
	error = equip->DecodeError(errorList[WRONG_CONDITION_CIK]);
	if (error.used)
		m_WrongCik.SetCheck(BST_CHECKED);
	else
		m_WrongCik.SetCheck(BST_UNCHECKED);

	//Pour "timeout while CIK-init"
	error = equip->DecodeError(errorList[TIMEOUT_CIK_INIT]);
	if (error.used)
		m_TimeoutCik.SetCheck(BST_CHECKED);
	else
		m_TimeoutCik.SetCheck(BST_UNCHECKED);

	//Pour "error fron cryptomodul"
	error = equip->DecodeError(errorList[ERROR_CRYPTOMODUL]);
	if (error.used)
		m_ErrorCrypto.SetCurSel(error.extendedCodes-2);
	else
		m_ErrorCrypto.SetCurSel(0);

	//Pour "password check"
	error = equip->DecodeError(errorList[PASSWORD_CHECK]);
	if (error.used)
		m_PasswordCheck.SetCheck(BST_CHECKED);
	else
		m_PasswordCheck.SetCheck(BST_UNCHECKED);

	UpdateData(FALSE);

}


void DlgED42ERR::SaveData()
{
	TError error;
	TVectorError errorList = equip->getErrors();

	//Pour "error codes of cryptomodul"
	error = equip->DecodeError(errorList[ERROR_CODES]);
	if(m_ErrorCodes.GetCurSel()==0)
		error.used = FALSE;
	else
	{
		error.used = TRUE;
		error.extendedCodes = m_ErrorCodes.GetCurSel();
	}
	errorList[ERROR_CODES] = equip->EncodeError(error);

	//Pour "F101 interface not activated"
	error = equip->DecodeError(errorList[F101_INTERFACE]);
	error.used = m_F101Interface.GetCheck()==BST_CHECKED;
	errorList[F101_INTERFACE] = equip->EncodeError(error);

	//Pour "F101 timeout from SKM"
	error = equip->DecodeError(errorList[F101_TIMEOUT]);
	error.used = m_F101Timeout.GetCheck()==BST_CHECKED;
	errorList[F101_TIMEOUT] = equip->EncodeError(error);

	//Pour "F101 error - give header action"
	error = equip->DecodeError(errorList[F101_ERROR_ACTION]);
	error.used = m_F101ErrorAction.GetCheck()==BST_CHECKED;
	errorList[F101_ERROR_ACTION] = equip->EncodeError(error);

	//Pour "no variable available"
	error = equip->DecodeError(errorList[NO_VARIABLE_AVAILABLE]);
	error.used = m_NoVariable.GetCheck()==BST_CHECKED;
	errorList[NO_VARIABLE_AVAILABLE] = equip->EncodeError(error);

	//Pour "wrong password type"
	error = equip->DecodeError(errorList[WRONG_PASSWORD]);
	error.used = m_WrongPassword.GetCheck()==BST_CHECKED;
	errorList[WRONG_PASSWORD] = equip->EncodeError(error);

	//Pour "F101 error - store variable"
	error = equip->DecodeError(errorList[F101_ERROR_VARIABLE]);
	error.used = m_F101ErrorVariable.GetCheck()==BST_CHECKED;
	errorList[F101_ERROR_VARIABLE] = equip->EncodeError(error);

	//Pour "F101 error - store KEK"
	error = equip->DecodeError(errorList[F101_ERROR_KEK]);
	error.used = m_F101ErrorKek.GetCheck()==BST_CHECKED;
	errorList[F101_ERROR_KEK] = equip->EncodeError(error);

	//Pour "configuration error"
	error = equip->DecodeError(errorList[CONFIGURATION_ERROR]);
	error.used = m_ConfigError.GetCheck()==BST_CHECKED;
	errorList[CONFIGURATION_ERROR] = equip->EncodeError(error);

	//Pour "start error"
	error = equip->DecodeError(errorList[START_ERROR]);
	error.used = m_StartError.GetCheck()==BST_CHECKED;
	errorList[START_ERROR] = equip->EncodeError(error);

	//Pour "error in software"
	error = equip->DecodeError(errorList[ERROR_SOFTWARE]);
	error.used = m_ErrorSoftware.GetCheck()==BST_CHECKED;
	errorList[ERROR_SOFTWARE] = equip->EncodeError(error);

	//Pour "selected variable not defined"
	error = equip->DecodeError(errorList[VARIABLE_NOT_DEFINED]);
	error.used = m_SelectVariable.GetCheck()==BST_CHECKED;
	errorList[VARIABLE_NOT_DEFINED] = equip->EncodeError(error);

	//Pour "update limit exceeded"
	error = equip->DecodeError(errorList[UPDATE_LIMIT_EXCEEDED]);
	error.used = m_UpdateLimit.GetCheck()==BST_CHECKED;
	errorList[UPDATE_LIMIT_EXCEEDED] = equip->EncodeError(error);

	//Pour "bilateral update global error"
	error = equip->DecodeError(errorList[BILATERAL_UPDATE_ERROR]);
	error.used = m_BilateralUpdateError.GetCheck()==BST_CHECKED;
	errorList[BILATERAL_UPDATE_ERROR] = equip->EncodeError(error);

	//Pour "bilateral tag global error"
	error = equip->DecodeError(errorList[BILATERAL_TAG_ERROR]);
	error.used = m_BilateralTagError.GetCheck()==BST_CHECKED;
	if (m_BilateralTagError.GetCheck()==BST_CHECKED)
	errorList[BILATERAL_TAG_ERROR] = equip->EncodeError(error);

	//Pour "wrong dld password fron user"
	error = equip->DecodeError(errorList[WRONG_DLD_PASSWORD_USER]);
	error.used = m_WrongDldPassword.GetCheck()==BST_CHECKED;
	errorList[WRONG_DLD_PASSWORD_USER] = equip->EncodeError(error);

	//Pour "format error"
	error = equip->DecodeError(errorList[FORMAT_ERROR]);
	error.used = m_FormatError.GetCheck()==BST_CHECKED;
	errorList[FORMAT_ERROR] = equip->EncodeError(error);

	//Pour "error while connecting CIK"
	error = equip->DecodeError(errorList[ERROR_CONNECTING_CIK]);
	error.used = m_ErrorConnectCik.GetCheck()==BST_CHECKED;
	errorList[ERROR_CONNECTING_CIK] = equip->EncodeError(error);

	//Pour "variable management"
	error = equip->DecodeError(errorList[VARIABLE_MANAGEMENT]);
	error.used = m_VariableManagement.GetCheck()==BST_CHECKED;
	errorList[VARIABLE_MANAGEMENT] = equip->EncodeError(error);

	//Pour "missing CIK"
	error = equip->DecodeError(errorList[MISSING_CIK]);
	error.used = m_MissingCik.GetCheck()==BST_CHECKED;
	errorList[MISSING_CIK] = equip->EncodeError(error);

	//Pour "wrong condition CIK"
	error = equip->DecodeError(errorList[WRONG_CONDITION_CIK]);
	error.used = m_WrongCik.GetCheck()==BST_CHECKED;
	errorList[WRONG_CONDITION_CIK] = equip->EncodeError(error);

	//Pour "timeout while CIK-init"
	error = equip->DecodeError(errorList[TIMEOUT_CIK_INIT]);
	error.used = m_TimeoutCik.GetCheck()==BST_CHECKED;
	errorList[TIMEOUT_CIK_INIT] = equip->EncodeError(error);

	//Pour "error fron cryptomodul"
	error = equip->DecodeError(errorList[ERROR_CRYPTOMODUL]);
	if(m_ErrorCrypto.GetCurSel()==0)
		error.used = FALSE;
	else
	{
		error.used = TRUE;
		error.extendedCodes = m_ErrorCrypto.GetCurSel()+2;
	}
	errorList[ERROR_CRYPTOMODUL] = equip->EncodeError(error);

	//Pour "password check"
	error = equip->DecodeError(errorList[PASSWORD_CHECK]);
	error.used = m_PasswordCheck.GetCheck()==BST_CHECKED;
	errorList[PASSWORD_CHECK] = equip->EncodeError(error);

	equip->setErrors(errorList);

	equip->setModifErreurPanne(FALSE);

	//Recherche si il y a au moins une erreur
	equip->SetError(FALSE);
	for(int i=1;i<equip->getErrors().size();i++)
	{
		error = equip->DecodeError(errorList[i]);
		if (error.used)
		{
			equip->SetError(TRUE);
		}
	}
}

void DlgED42ERR::OnOK()
{
	if(equip->getModifErreurPanne())
	{
		SaveData();
	}
}

void DlgED42ERR::OnCancel()
{
	LoadData();
	equip->setModifErreurPanne(FALSE);
}


void DlgED42ERR::OnSelchangeComboErrorCodes()
{
	equip->setModifErreurPanne(TRUE);

	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckF101Interface()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckF101Timeout()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckF101ErrorAction()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckNoVariable()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckWrongPassword()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckF101ErrorVariable()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckF101ErrorKek()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckConfigError()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckStartError()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckErrorSoftware()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckSelectVariable()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckUpdateLimit()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckBilateralUpdateError()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckBilateralTagError()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckWrongDldPassword()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckFormatError()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckErrorConnectCik()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckVariableManagement()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnSelchangeComboErrorCrypto()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckMissingCik()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckWrongCik()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckTimeoutCik()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_PasswordCheck.SetCheck(BST_UNCHECKED);
}

void DlgED42ERR::OnCheckPasswordCheck()
{
	equip->setModifErreurPanne(TRUE);

	m_ErrorCodes.SetCurSel(0);
	m_F101Interface.SetCheck(BST_UNCHECKED);
	m_F101Timeout.SetCheck(BST_UNCHECKED);
	m_F101ErrorAction.SetCheck(BST_UNCHECKED);
	m_NoVariable.SetCheck(BST_UNCHECKED);
	m_WrongPassword.SetCheck(BST_UNCHECKED);
	m_F101ErrorVariable.SetCheck(BST_UNCHECKED);
	m_F101ErrorKek.SetCheck(BST_UNCHECKED);
	m_ConfigError.SetCheck(BST_UNCHECKED);
	m_StartError.SetCheck(BST_UNCHECKED);
	m_ErrorSoftware.SetCheck(BST_UNCHECKED);
	m_SelectVariable.SetCheck(BST_UNCHECKED);
	m_UpdateLimit.SetCheck(BST_UNCHECKED);
	m_BilateralUpdateError.SetCheck(BST_UNCHECKED);
	m_BilateralTagError.SetCheck(BST_UNCHECKED);
	m_WrongDldPassword.SetCheck(BST_UNCHECKED);
	m_FormatError.SetCheck(BST_UNCHECKED);
	m_ErrorConnectCik.SetCheck(BST_UNCHECKED);
	m_VariableManagement.SetCheck(BST_UNCHECKED);
	m_ErrorCrypto.SetCurSel(0);
	m_MissingCik.SetCheck(BST_UNCHECKED);
	m_WrongCik.SetCheck(BST_UNCHECKED);
	m_TimeoutCik.SetCheck(BST_UNCHECKED);
}

