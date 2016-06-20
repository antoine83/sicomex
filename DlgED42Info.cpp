// DlgED42Info.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42Info.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgED42Info dialog


DlgED42Info::DlgED42Info(CEquipED42 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(DlgED42Info::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgED42Info)
	m_dcp1 = _T("");
	m_dcp2 = _T("");
	m_user_pwd = _T("");
	m_Transmission_Mode = _T("");
	m_Transmission_Procedure = _T("");
	m_Operating_Mode = _T("");
	m_Trafic_Mode = _T("");
	m_Preset_Exploitation = _T("");
	m_explEmi = FALSE;
	m_explRec = FALSE;
	m_dateRate = _T("");
	m_activeKey = _T("");
	m_updateCount = _T("");
	m_explCall = FALSE;
	m_explSync = FALSE;
	m_fullSimu = FALSE;
	//}}AFX_DATA_INIT

	this->eqp = equip;

}
DlgED42Info::~DlgED42Info()
{
	//DestroyWindow();
}


void DlgED42Info::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgED42Info)
	DDX_Control(pDX, IDC_BUTTON_UNLOCK, c_lockUnlock);
	DDX_Control(pDX, IDC_CHECK_FULL, c_fullSimu);
	DDX_Control(pDX, IDC_CHECK_SYNC, c_explSync);
	DDX_Control(pDX, IDC_CHECK_CALL, c_explCall);
	DDX_Control(pDX, IDC_BUTTON_ACT_DESACT, c_activation);
	DDX_Control(pDX, IDC_COMBO_PRESET, c_preset);
	DDX_Control(pDX, IDC_COMBO_OPERATION_MODE, c_operationMode);
	DDX_Control(pDX, IDC_DATA_RATE, c_dataRateString);
	DDX_Control(pDX, IDC_DAT_RATE, c_dataRate);
	DDX_Control(pDX, IDC_CHECK_REC, c_explRec);
	DDX_Control(pDX, IDC_CHECK_EMI, c_explEmi);
	DDX_Control(pDX, IDC_TRANS_MODE, c_Transmission_Mode);
	DDX_Control(pDX, IDC_TRANS_PRECED, c_Transmission_Procedure);
	DDX_Control(pDX, IDC_TRAF_MODE, c_Trafic_Mode);
	DDX_Text(pDX, IDC_ED42_DCP_1, m_dcp1);
	DDV_MaxChars(pDX, m_dcp1, 20);
	DDX_Text(pDX, IDC_ED42_DCP_2, m_dcp2);
	DDX_Text(pDX, IDC_EDIT_USER_PWD, m_user_pwd);
	DDX_Text(pDX, IDC_TRANS_MODE, m_Transmission_Mode);
	DDX_Text(pDX, IDC_TRANS_PRECED, m_Transmission_Procedure);
	DDX_Text(pDX, IDC_OPE_MODE, m_Operating_Mode);
	DDX_Text(pDX, IDC_TRAF_MODE, m_Trafic_Mode);
	DDX_Text(pDX, IDC_PRESET_EXPLOIT, m_Preset_Exploitation);
	DDX_Check(pDX, IDC_CHECK_EMI, m_explEmi);
	DDX_Check(pDX, IDC_CHECK_REC, m_explRec);
	DDX_Text(pDX, IDC_DAT_RATE, m_dateRate);
	DDX_Text(pDX, IDC_ACT_KEY, m_activeKey);
	DDX_Text(pDX, IDC_UPD_COUNT, m_updateCount);
	DDX_Check(pDX, IDC_CHECK_CALL, m_explCall);
	DDX_Check(pDX, IDC_CHECK_SYNC, m_explSync);
	DDX_Check(pDX, IDC_CHECK_FULL, m_fullSimu);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgED42Info, CDialog)
	//{{AFX_MSG_MAP(DlgED42Info)
	ON_BN_CLICKED(IDC_BUTTON_8, OnButton8)
	ON_EN_CHANGE(IDC_EDIT_USER_PWD, OnChangeEditUserPwd)
	ON_BN_CLICKED(IDC_CHECK_EMI, OnCheckEmi)
	ON_BN_CLICKED(IDC_CHECK_REC, OnCheckRec)
	ON_BN_CLICKED(IDC_BUTTON_ACT_DESACT, OnButtonActDesact)
	ON_BN_CLICKED(IDC_BUTTON_UNLOCK, OnButtonUnlock)
	ON_BN_CLICKED(IDC_CHECK_CALL, OnCheckCall)
	ON_BN_CLICKED(IDC_CHECK_SYNC, OnCheckSync)
	ON_BN_CLICKED(IDC_CHECK_FULL, OnCheckFull)
	ON_EN_UPDATE(IDC_EDIT_USER_PWD, OnUpdateEditUserPwd)
	ON_WM_KEYDOWN()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgED42Info message handlers

BOOL DlgED42Info::OnInitDialog()
{
	CDialog::OnInitDialog();

	GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);
	GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
	GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);

	c_operationMode.SetCurSel(0);
	c_operationMode.ShowWindow(FALSE);

	c_preset.SetCurSel(0);
	c_preset.ShowWindow(FALSE);

	GetDlgItem(IDC_BUTTON_ACT_DESACT)->ShowWindow(FALSE);

	if (eqp->GetFullSimu())
		c_fullSimu.SetCheck(1);
	else
		c_fullSimu.SetCheck(0);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DlgED42Info::OnButton8()
{
	OutputDebugString("Dans : DlgED42Info::OnButton8() !\n");

	eqp->SetClavier(TRUE);
	eqp->SetChaineClavier("V");
}

void DlgED42Info::OnChangeEditUserPwd()
{
	// TODO: If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO: Add your control notification handler code here

}

void DlgED42Info::OnUpdateEditUserPwd()
{
	// TODO: Add your control notification handler code here
}

void DlgED42Info::OnCheckEmi() 
{
	if (eqp->GetOperatingStatus() == OFFLINE )
		return;

	UpdateData(TRUE);

	eqp->SetStatusTx(m_explEmi);
}

void DlgED42Info::OnCheckRec() 
{
	UpdateData(TRUE);

	eqp->SetStatusRx(m_explRec);
	
}

void DlgED42Info::OnButtonActDesact() 
{
	OutputDebugString("Dans : DlgED42Info::OnButtonActDesact() !\n");

	char buffer[3] = {0};

	if (eqp->GetDureeBusy() != 0)
		eqp->SetStatusBusy(1);

	int presetOnline = c_operationMode.GetCurSel() * 8 + c_preset.GetCurSel();

	itoa(presetOnline,buffer,10);

	if(eqp->GetOperatingStatus() == ONLINE)
	{
		OutputDebugString("Dans : DlgED42Info::OnButtonActDesact() et if(eqp->GetOperatingStatus() == ONLINE)!\n");

		eqp->SetPresetList("255", 'X');					// Param 20
		eqp->SetOnlinePresetStatus(0);					// Param 21 : Flag : Online preset
		eqp->SetActiveKeyState(0);						// Param 29 : Flag : Active KEY state
		eqp->SetKeyList(1);								// Param 25 : Flag : key list
		eqp->SetOperatingStatus(OFFLINE);
		eqp->SetOnlinePreset(DEFAULT_INVALID_VALUE_ED42);
		eqp->SetStatusTx(0);
		eqp->SetStatusRx(0);
		eqp->SetStatusCall(0);
		eqp->SetStatusSync(0);
	}
	else
	{
		OutputDebugString("Dans : DlgED42Info::OnButtonActDesact() et // Activation!\n");

		// Activation
		int tmpMemIdx = eqp->GetMemoryIndexOfKey(presetOnline,c_operationMode.GetCurSel());

		if (tmpMemIdx == DEFAULT_INVALID_VALUE_ED42 && (c_operationMode.GetCurSel() == 0 || c_operationMode.GetCurSel() == 1))
		{
			MessageBox("Aucune CV trouvée","Attention",MB_ICONWARNING);
			return;
		}

		eqp->activationPreset(buffer);

		if (c_operationMode.GetCurSel() == 0 || c_operationMode.GetCurSel() == 1)
		{
			//Mise à jour du flag KEState utilisé par le SYS
			eqp->SetKeyList(1);						// Param 25 : Flag : key list
			eqp->SetKEState(1);						// Param 28 : Flag : KE state
			eqp->SetActiveKeyState(1);				// Param 29 : Flag : Active KEY state
		}

		eqp->SetOnlinePreset(presetOnline);
		eqp->SetOnlinePresetStatus(1);						// Param 21 : Flag : Online preset
		eqp->SetActivatedKey(tmpMemIdx);						// pour ACV
		eqp->SetOperatingStatus(ONLINE);
	}
	
	eqp->SetStatusBusy(0);
}

void DlgED42Info::OnButtonUnlock() 
{
	OutputDebugString("Dans : DlgED42Info::OnButtonUnlock() !\n");

	if(eqp->getED42Lock())
	{
		OutputDebugString("Dans : DlgED42Info::OnButtonUnlock() et if(eqp->getED42Lock()) !\n");
		// UNLOCK
		GetDlgItem(IDC_BUTTON_8)->ShowWindow(TRUE);	
	}
	else
	{
		OutputDebugString("Dans : DlgED42Info::OnButtonUnlock() et if(eqp->getED42Lock()) et else!\n");
		//LOCK
		eqp->setED42Lock(TRUE);
	}
	
}

void DlgED42Info::OnCheckCall() 
{
	if (eqp->GetOperatingStatus() == OFFLINE )
		return;

	UpdateData(TRUE);

	eqp->SetStatusCall(m_explCall);

	/*
	if (m_explCall)
		eqp->SetStatusCall(1);
	else
		eqp->SetStatusCall(0);
	*/	
}

void DlgED42Info::OnCheckSync() 
{
	if (eqp->GetOperatingStatus() == OFFLINE )
		return;

	UpdateData(TRUE);

	eqp->SetStatusSync(m_explSync);

	/*
	if (m_explSync)
		eqp->SetStatusSync(1);
	else
		eqp->SetStatusSync(0);
	*/
	
}

void DlgED42Info::OnCheckFull() 
{
	UpdateData(TRUE);

	//eqp->SetFullSimu(m_fullSimu);
	eqp->SetFullSimu(c_fullSimu.GetCheck() == 1);
	
}

void DlgED42Info::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags) 
{
	// TODO: Add your message handler code here and/or call default
	
	CDialog::OnKeyDown(nChar, nRepCnt, nFlags);

}

// *************************************************************
// Gestion des touches ENTER et ECHAP pour la saisie du password
// *************************************************************
BOOL DlgED42Info::PreTranslateMessage(MSG* pMsg)  
{ 
	  if(pMsg->message == WM_KEYDOWN) 
	  { 
		if(pMsg->wParam == VK_ESCAPE) 
		{
			eqp->SetChaineClavier("");
			return TRUE;
		}
		if(pMsg->wParam == VK_RETURN) 
		{
			eqp->SetChaineClavier("");
			return TRUE;
		}
	  } 
	  return CDialog::PreTranslateMessage(pMsg); 
}
