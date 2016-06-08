// DlgED42StatusERR.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42StatusERR.h"
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
// CDlgED42StatusERR dialog


CDlgED42StatusERR::CDlgED42StatusERR(CEquipED42 * eqp,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42StatusERR::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42StatusERR)
	m_nbRepeat = 0;
	//}}AFX_DATA_INIT

	this->eqp = eqp;
	oldNbRepeat = 0;
}


void CDlgED42StatusERR::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42StatusERR)
	DDX_Control(pDX, IDC_SPIN_NB_REPEAT, s_nbRepeat);
	DDX_Control(pDX, IDC_EDIT_NB_REPEAT, c_nbRepeat);
	DDX_Control(pDX, IDC_COMBO_SECURE_MODE, c_secureMode);
	DDX_Control(pDX, IDC_COMBO_KE_STATE, c_KEState);
	DDX_Control(pDX, IDC_CHECK_WRONG_STATE, c_wrongState);
	DDX_Control(pDX, IDC_CHECK_WRONG_COMMAND, c_wrongCommand);
	DDX_Control(pDX, IDC_CHECK_UNKNOWN_COMMAND, c_unknownCommand);
	DDX_Control(pDX, IDC_CHECK_SYNTAX_CHECKSUM, c_syntaxChecksum);
	DDX_Control(pDX, IDC_CHECK_SLAVE_NOT_REMOTE, c_slaveNotRemote);
	DDX_Control(pDX, IDC_CHECK_PARITY, c_parity);
	DDX_Control(pDX, IDC_CHECK_MAX_MESS_LENGTH, c_maxMessageLength);
	DDX_Control(pDX, IDC_CHECK_INVALID_PARAMETER, c_invalidParameter);
	DDX_Text(pDX, IDC_EDIT_NB_REPEAT, m_nbRepeat);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42StatusERR, CDialog)
	//{{AFX_MSG_MAP(CDlgED42StatusERR)
	ON_BN_CLICKED(IDC_CHECK_INVALID_PARAMETER, OnCheckInvalidParameter)
	ON_BN_CLICKED(IDC_CHECK_MAX_MESS_LENGTH, OnCheckMaxMessLength)
	ON_BN_CLICKED(IDC_CHECK_PARITY, OnCheckParity)
	ON_BN_CLICKED(IDC_CHECK_SLAVE_NOT_REMOTE, OnCheckSlaveNotRemote)
	ON_BN_CLICKED(IDC_CHECK_SYNTAX_CHECKSUM, OnCheckSyntaxChecksum)
	ON_BN_CLICKED(IDC_CHECK_UNKNOWN_COMMAND, OnCheckUnknownCommand)
	ON_BN_CLICKED(IDC_CHECK_WRONG_COMMAND, OnCheckWrongCommand)
	ON_BN_CLICKED(IDC_CHECK_WRONG_STATE, OnCheckWrongState)
	ON_CBN_SELCHANGE(IDC_COMBO_KE_STATE, OnSelchangeComboKeState)
	ON_CBN_SELCHANGE(IDC_COMBO_SECURE_MODE, OnSelchangeComboSecureMode)
	ON_BN_CLICKED(IDC_RAZ, OnRaz)
	ON_EN_CHANGE(IDC_EDIT_NB_REPEAT, OnChangeEditNbRepeat)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_NB_REPEAT, OnDeltaposSpinNbRepeat)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42StatusERR message handlers

BOOL CDlgED42StatusERR::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	LoadData() ;
	
	return TRUE;  
}

void CDlgED42StatusERR::LoadData() 
{
	pLogger.LOG_TRACE("Dans : CDlgED42StatusERR::LoadData()!");

	TStatusError statusError;
	TVectorStatusError errorStatusList = eqp->getStatusErrors();

	//------------------ Pour "Parity, framing" ------------------
	statusError = eqp->DecodeStatusError(errorStatusList[PARITY_FRAMING]);
	c_parity.SetCheck(statusError.used);

	// Affiche le nbRepeat le plus grand de la table des erreurs.
	// De plus, le nbRepeat est identique a toutes les erreurs sélectionnées
	if(m_nbRepeat < statusError.nbRepeat)
		m_nbRepeat = statusError.nbRepeat;

	//------------------ Pour "Syntax or checksum error" ------------------
	statusError = eqp->DecodeStatusError(errorStatusList[SYNTAX_RCS]);
	c_syntaxChecksum.SetCheck(statusError.used);

	// Affiche le nbRepeat le plus grand de la table des erreurs.
	// De plus, le nbRepeat est identique a toutes les erreurs sélectionnées
	if(m_nbRepeat < statusError.nbRepeat)
		m_nbRepeat = statusError.nbRepeat;

	//------------------ Pour "Maximum message length error" ------------------
	statusError = eqp->DecodeStatusError(errorStatusList[MAX_MSG_LENGTH]);
	c_maxMessageLength.SetCheck(statusError.used);

	// Affiche le nbRepeat le plus grand de la table des erreurs.
	// De plus, le nbRepeat est identique a toutes les erreurs sélectionnées
	if(m_nbRepeat < statusError.nbRepeat)
		m_nbRepeat = statusError.nbRepeat;

	//------------------ Pour "Unknown command word" ------------------
	statusError = eqp->DecodeStatusError(errorStatusList[UNKNOWN_COMMAND]);
	c_unknownCommand.SetCheck(statusError.used);

	// Affiche le nbRepeat le plus grand de la table des erreurs.
	// De plus, le nbRepeat est identique a toutes les erreurs sélectionnées
	if(m_nbRepeat < statusError.nbRepeat)
		m_nbRepeat = statusError.nbRepeat;

	//------------------ Pour "Slave is not remote mode" ------------------
	statusError = eqp->DecodeStatusError(errorStatusList[NOT_REMOTE_MODE]);
	c_slaveNotRemote.SetCheck(statusError.used);

	// Affiche le nbRepeat le plus grand de la table des erreurs.
	// De plus, le nbRepeat est identique a toutes les erreurs sélectionnées
	if(m_nbRepeat < statusError.nbRepeat)
		m_nbRepeat = statusError.nbRepeat;

	//------------------ Pour "Sequence conflict, slave not ready, wrong state" ------------------
	statusError = eqp->DecodeStatusError(errorStatusList[CONFLICT]);
	c_wrongState.SetCheck(statusError.used);

	// Affiche le nbRepeat le plus grand de la table des erreurs.
	// De plus, le nbRepeat est identique a toutes les erreurs sélectionnées
	if(m_nbRepeat < statusError.nbRepeat)
		m_nbRepeat = statusError.nbRepeat;

	//------------------ Pour "Wrong command word" ------------------
	statusError = eqp->DecodeStatusError(errorStatusList[WRONG_COMMAND]);
	c_wrongCommand.SetCheck(statusError.used);

	// Affiche le nbRepeat le plus grand de la table des erreurs.
	// De plus, le nbRepeat est identique a toutes les erreurs sélectionnées
	if(m_nbRepeat < statusError.nbRepeat)
		m_nbRepeat = statusError.nbRepeat;

	//------------------ Pour "Invalid parameter value" ------------------
	statusError = eqp->DecodeStatusError(errorStatusList[INVALID_PARAMETER]);
	c_invalidParameter.SetCheck(statusError.used);

	// Affiche le nbRepeat le plus grand de la table des erreurs.
	// De plus, le nbRepeat est identique a toutes les erreurs sélectionnées
	if(m_nbRepeat < statusError.nbRepeat)
		m_nbRepeat = statusError.nbRepeat;

	//------------------ Pour "KE state" ------------------
	switch(eqp->GetKeStatus())
	{
	case TAMPER:
		c_KEState.SetCurSel(0);
		break;

	case ALARM:
		c_KEState.SetCurSel(1);
		break;

	case NO_SECURE_SYSTEM:
		c_KEState.SetCurSel(2);
		break;

	case ZEROIZED:
		c_KEState.SetCurSel(3);
		break;

	case NO_CIK_SET_UP:
		c_KEState.SetCurSel(4);
		break;

	case CIK_NOT_PLUGED:
		c_KEState.SetCurSel(5);
		break;

	case KE_IDLE:
		c_KEState.SetCurSel(6);
		break;
	}

	//------------------ Pour "Secure mode" ------------------
	c_secureMode.SetCurSel(eqp->getSecureMode());	

	UpdateData(FALSE);

	pLogger.LOG_TRACE("Fin : CDlgED42StatusERR::LoadData()!");
}

void CDlgED42StatusERR::SaveData() 
{
	pLogger.LOG_TRACE("Dans : CDlgED42StatusERR::SaveData()!");

	TStatusError statusError;
	TVectorStatusError errorStatusList = eqp->getStatusErrors();

	//Pour "Parity, framing"
	statusError = eqp->DecodeStatusError(errorStatusList[PARITY_FRAMING]);
	statusError.used = (c_parity.GetCheck() == 1);
	//Repeat
	// Si on sélectionne l'erreur, on récupère le nombre de répétition
	// Attention si on a 1, envoi de l'erreur + répétition de l'erreur (donc 2 envoi de l'erreur)
	if(c_parity.GetCheck()) 
		statusError.nbRepeat = m_nbRepeat;
	else
		statusError.nbRepeat = 0; 
	errorStatusList[PARITY_FRAMING] = eqp->EncodeStatusError(statusError);

	//Pour "Syntax or checksum error"
	statusError = eqp->DecodeStatusError(errorStatusList[SYNTAX_RCS]);
	statusError.used = (c_syntaxChecksum.GetCheck() == 1);
	// Si on sélectionne l'erreur, on récupère le nombre de répétition
	// Attention si on a 1, envoi de l'erreur + répétition de l'erreur (donc 2 envoi de l'erreur)
	if(c_syntaxChecksum.GetCheck()) 
		statusError.nbRepeat = m_nbRepeat;
	else
		statusError.nbRepeat = 0;  
	errorStatusList[SYNTAX_RCS] = eqp->EncodeStatusError(statusError);

	//Pour "Maximum message length error"
	statusError = eqp->DecodeStatusError(errorStatusList[MAX_MSG_LENGTH]);
	statusError.used = (c_maxMessageLength.GetCheck() == 1);
	//Repeat
	// Si on sélectionne l'erreur, on récupère le nombre de répétition
	// Attention si on a 1, envoi de l'erreur + répétition de l'erreur (donc 2 envoi de l'erreur)
	if(c_maxMessageLength.GetCheck()) 
		statusError.nbRepeat = m_nbRepeat;
	else
		statusError.nbRepeat = 0; 
	errorStatusList[MAX_MSG_LENGTH] = eqp->EncodeStatusError(statusError);

	//Pour "Unknown command word"
	statusError = eqp->DecodeStatusError(errorStatusList[UNKNOWN_COMMAND]);
	statusError.used = (c_unknownCommand.GetCheck() == 1);
	//Repeat
	// Si on sélectionne l'erreur, on récupère le nombre de répétition
	// Attention si on a 1, envoi de l'erreur + répétition de l'erreur (donc 2 envoi de l'erreur)
	if(c_unknownCommand.GetCheck()) 
		statusError.nbRepeat = m_nbRepeat;
	else
		statusError.nbRepeat = 0; 
	errorStatusList[UNKNOWN_COMMAND] = eqp->EncodeStatusError(statusError);

	//Pour "Slave is not remote mode"
	statusError = eqp->DecodeStatusError(errorStatusList[NOT_REMOTE_MODE]);
	statusError.used = (c_slaveNotRemote.GetCheck() == 1);
	//Repeat
	// Si on sélectionne l'erreur, on récupère le nombre de répétition
	// Attention si on a 1, envoi de l'erreur + répétition de l'erreur (donc 2 envoi de l'erreur)
	if(c_slaveNotRemote.GetCheck()) 
		statusError.nbRepeat = m_nbRepeat;
	else
		statusError.nbRepeat = 0;  
	errorStatusList[NOT_REMOTE_MODE] = eqp->EncodeStatusError(statusError);

	//Pour "Sequence conflict, slave not ready, wrong state"
	statusError = eqp->DecodeStatusError(errorStatusList[CONFLICT]);
	statusError.used = (c_wrongState.GetCheck() == 1);
	//Attention
	//Il n'y a pas de répétion pour cette erreur car elle provoque une exécution ou une non 
	//exécution des commandes. Pour débloquer, il faut faire INI TAK et PWCHK
	if(c_wrongState.GetCheck()) 
		eqp->SetStatusS20(3); //Attente des commandes INI TAK et PWCHK
	else
		eqp->SetStatusS20(0);
	errorStatusList[CONFLICT] = eqp->EncodeStatusError(statusError);

	//Pour "Wrong command word"
	statusError = eqp->DecodeStatusError(errorStatusList[WRONG_COMMAND]);
	statusError.used = (c_wrongCommand.GetCheck() == 1);
	//Repeat
	// Si on sélectionne l'erreur, on récupère le nombre de répétition
	// Attention si on a 1, envoi de l'erreur + répétition de l'erreur (donc 2 envoi de l'erreur)
	if(c_wrongCommand.GetCheck()) 
		statusError.nbRepeat = m_nbRepeat;
	else
		statusError.nbRepeat = 0; 
	errorStatusList[WRONG_COMMAND] = eqp->EncodeStatusError(statusError);

	//Pour "Invalid parameter value"
	statusError = eqp->DecodeStatusError(errorStatusList[INVALID_PARAMETER]);
	statusError.used = (c_invalidParameter.GetCheck() == 1);
	//Repeat
	// Si on sélectionne l'erreur, on récupère le nombre de répétition
	// Attention si on a 1, envoi de l'erreur + répétition de l'erreur (donc 2 envoi de l'erreur)
	if(c_invalidParameter.GetCheck()) 
		statusError.nbRepeat = m_nbRepeat;
	else
		statusError.nbRepeat = 0;  
	errorStatusList[INVALID_PARAMETER] = eqp->EncodeStatusError(statusError);

	//Pour "KE state"
	//Récupération de l'ancienne valeur de KEStatus
	int KEStatusOld = eqp->GetKeStatus();

	switch(c_KEState.GetCurSel())
	{
	case 0:		
		eqp->SetKeStatus(TAMPER);
		break;

	case 1:
		eqp->SetKeStatus(ALARM);
		break;

	case 2:
		eqp->SetKeStatus(NO_SECURE_SYSTEM);
		break;

	case 3:
		eqp->SetKeStatus(ZEROIZED);
		break;

	case 4:
		eqp->SetKeStatus(NO_CIK_SET_UP);
		break;

	case 5:
		eqp->SetKeStatus(CIK_NOT_PLUGED);
		break;

	case 6:
		eqp->SetKeStatus(KE_IDLE);
		break;
	}

	//Vérification si la valeur a été changé
	if(eqp->GetKeStatus() != KEStatusOld)
		eqp->SetKEState(1);

	//Pour "Secure mode"
	eqp->setSecureMode(c_secureMode.GetCurSel());

	eqp->setStatusErrors(errorStatusList);

	eqp->setModifErreurPanne(FALSE);

	pLogger.LOG_TRACE("Fin : CDlgED42StatusERR::SaveData()!");
}

void CDlgED42StatusERR::OnCheckInvalidParameter() 
{
	eqp->setModifErreurPanne(TRUE);	
}

void CDlgED42StatusERR::OnCheckMaxMessLength() 
{
	eqp->setModifErreurPanne(TRUE);	
}

void CDlgED42StatusERR::OnCheckParity() 
{
	eqp->setModifErreurPanne(TRUE);	
}

void CDlgED42StatusERR::OnCheckSlaveNotRemote() 
{
	eqp->setModifErreurPanne(TRUE);	
}

void CDlgED42StatusERR::OnCheckSyntaxChecksum() 
{
	eqp->setModifErreurPanne(TRUE);	
}

void CDlgED42StatusERR::OnCheckUnknownCommand() 
{
	eqp->setModifErreurPanne(TRUE);	
}

void CDlgED42StatusERR::OnCheckWrongCommand() 
{
	eqp->setModifErreurPanne(TRUE);	
}

void CDlgED42StatusERR::OnCheckWrongState() 
{
	eqp->setModifErreurPanne(TRUE);	
}

void CDlgED42StatusERR::OnSelchangeComboKeState() 
{
	eqp->setModifErreurPanne(TRUE);	
}

void CDlgED42StatusERR::OnSelchangeComboSecureMode() 
{
	eqp->setModifErreurPanne(TRUE);	
}

void CDlgED42StatusERR::OnRaz() 
{
	//Pour "Parity, framing"
	if (c_parity.GetCheck() == TRUE)
		eqp->setModifErreurPanne(TRUE);	
	c_parity.SetCheck(FALSE);

	//Pour "Syntax or checksum error"
	if (c_syntaxChecksum.GetCheck() == TRUE)
		eqp->setModifErreurPanne(TRUE);
	c_syntaxChecksum.SetCheck(FALSE);

	//Pour "Maximum message length error"
	if (c_maxMessageLength.GetCheck() == TRUE)
		eqp->setModifErreurPanne(TRUE);
	c_maxMessageLength.SetCheck(FALSE);

	//Pour "Unknown command word"
	if (c_unknownCommand.GetCheck() == TRUE)
		eqp->setModifErreurPanne(TRUE);
	c_unknownCommand.SetCheck(FALSE);

	//Pour "Slave is not remote mode"
	if (c_slaveNotRemote.GetCheck() == TRUE)
		eqp->setModifErreurPanne(TRUE);
	c_slaveNotRemote.SetCheck(FALSE);

	//Pour "Sequence conflict, slave not ready, wrong state"
	if (c_wrongState.GetCheck() == TRUE)
		eqp->setModifErreurPanne(TRUE);
	c_wrongState.SetCheck(FALSE);

	//Pour "Wrong command word"
	if (c_wrongCommand.GetCheck() == TRUE)
		eqp->setModifErreurPanne(TRUE);
	c_wrongCommand.SetCheck(FALSE);

	//Pour "Invalid parameter value"
	if (c_invalidParameter.GetCheck() == TRUE)
		eqp->setModifErreurPanne(TRUE);
	c_invalidParameter.SetCheck(FALSE);

	//Pour la répétition
	if(m_nbRepeat != 0)
		eqp->setModifErreurPanne(TRUE);
	m_nbRepeat = 0;

	//Pour "KE state"
	if (c_KEState.GetCurSel() != DEFAULT_KE_STATUS)
		eqp->setModifErreurPanne(TRUE);
	c_KEState.SetCurSel(DEFAULT_KE_STATUS);

	//Pour "Secure mode"
	if (c_secureMode.GetCurSel() != DEFAULT_SECURE_MODE)
		eqp->setModifErreurPanne(TRUE);
	c_secureMode.SetCurSel(DEFAULT_SECURE_MODE);
}

void CDlgED42StatusERR::OnCancel() 
{
	LoadData();
	eqp->setModifErreurPanne(FALSE);
}

void CDlgED42StatusERR::OnOK() 
{
	if(eqp->getModifErreurPanne())
	{
		SaveData();
	}
}

void CDlgED42StatusERR::OnChangeEditNbRepeat() 
{
	CString str;

	c_nbRepeat.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_nbRepeat = atoi((char*)LPCTSTR(str));

	if ( m_nbRepeat > NB_REPEAT_MAX )
	{
		AfxMessageBox("Le nombre de répétition peut prendre les valeurs : 0 à 10");
		m_nbRepeat = NB_REPEAT_MAX;
	}

	if ( m_nbRepeat < NB_REPEAT_MIN)
	{
		AfxMessageBox("Le nombre de répétition peut prendre les valeurs : 0 à 10");
		m_nbRepeat = NB_REPEAT_MIN;
	}			

	if (oldNbRepeat != m_nbRepeat)
		eqp->setModifErreurPanne(TRUE);	

	UpdateData(FALSE);	
}

void CDlgED42StatusERR::OnDeltaposSpinNbRepeat(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if (pNMUpDown->iDelta > 0)  m_nbRepeat -= 1;
		else       m_nbRepeat += 1;


	if ( m_nbRepeat > NB_REPEAT_MAX )
	{
		AfxMessageBox("Le nombre de répétition peut prendre les valeurs : 0 à 10");
		m_nbRepeat = NB_REPEAT_MAX;
	}

	if ( m_nbRepeat < NB_REPEAT_MIN)
	{
		AfxMessageBox("Le nombre de répétition peut prendre les valeurs : 0 à 10");
		m_nbRepeat = NB_REPEAT_MIN;
	}			

	if (oldNbRepeat != m_nbRepeat)
		eqp->setModifErreurPanne(TRUE);

	UpdateData(FALSE);
	
	*pResult = 0;
}
