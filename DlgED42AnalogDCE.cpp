// DlgED42AnalogDCE.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42AnalogDCE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42AnalogDCE dialog


CDlgED42AnalogDCE::CDlgED42AnalogDCE(CEquipED42 * eqp,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42AnalogDCE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42AnalogDCE)
	m_txnbLevel = 0;
	m_rxnbLevel = 0;
	m_rxwbLevel = 0;
	m_txwbLevel = 0;
	//}}AFX_DATA_INIT

	this->eqp = eqp;

	oldLevelTXNB = 0;
	oldLevelRXNB = 0;
	oldLevelTXWB = 0;
	oldLevelRXWB = 0;
}


void CDlgED42AnalogDCE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42AnalogDCE)
	DDX_Control(pDX, IDC_SPIN_TXWB_LEVEL, s_txwbLevel);
	DDX_Control(pDX, IDC_SPIN_RXWB_LEVEL, s_rxwbLevel);
	DDX_Control(pDX, IDC_SPIN_RXNB_LEVEL, s_rxnbLevel);
	DDX_Control(pDX, IDC_EDIT_TXWB_LEVEL, c_txwbLevel);
	DDX_Control(pDX, IDC_EDIT_RXWB_LEVEL, c_rxwbLevel);
	DDX_Control(pDX, IDC_EDIT_RXNB_LEVEL, c_rxnbLevel);
	DDX_Control(pDX, IDC_SPIN_TXNB_LEVEL, s_txnbLevel);
	DDX_Control(pDX, IDC_EDIT_TXNB_LEVEL, c_txnbLevel);
	DDX_Control(pDX, IDC_COMBO_SQUELCH_TYPE_DCE, c_squelchType);
	DDX_Control(pDX, IDC_COMBO_SQM_TYPE_DCE, c_sqmType);
	DDX_Control(pDX, IDC_COMBO_SQM_POLA_DCE, c_sqmPolarity);
	DDX_Control(pDX, IDC_COMBO_SQG_TYPE_DCE, c_sqgType);
	DDX_Control(pDX, IDC_COMBO_SQG_POLA_DCE, c_sqgPolarity);
	DDX_Control(pDX, IDC_COMBO_PTT_POLA_DCE, c_pttPolarity);
	DDX_Control(pDX, IDC_COMBO_NBWB_POLA_DCE, c_nbwbPolarity);
	DDX_Control(pDX, IDC_COMBO_DPTT_TYPE_DCE, c_dpttType);
	DDX_Control(pDX, IDC_COMBO_DPTT_POLA_DCE, c_dpttPolarity);
	DDX_Control(pDX, IDC_COMBO_BBDP_POLA_DCE, c_bbdpPolarity);
	DDX_Control(pDX, IDC_CHECK_ACT_ANALOG_DCE, c_actAnalog);
	DDX_Text(pDX, IDC_EDIT_TXNB_LEVEL, m_txnbLevel);
	DDX_Text(pDX, IDC_EDIT_RXNB_LEVEL, m_rxnbLevel);
	DDX_Text(pDX, IDC_EDIT_RXWB_LEVEL, m_rxwbLevel);
	DDX_Text(pDX, IDC_EDIT_TXWB_LEVEL, m_txwbLevel);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42AnalogDCE, CDialog)
	//{{AFX_MSG_MAP(CDlgED42AnalogDCE)
	ON_CBN_SELCHANGE(IDC_COMBO_BBDP_POLA_DCE, OnSelchangeComboBbdpPolaDce)
	ON_CBN_SELCHANGE(IDC_COMBO_DPTT_POLA_DCE, OnSelchangeComboDpttPolaDce)
	ON_CBN_SELCHANGE(IDC_COMBO_DPTT_TYPE_DCE, OnSelchangeComboDpttTypeDce)
	ON_CBN_SELCHANGE(IDC_COMBO_NBWB_POLA_DCE, OnSelchangeComboNbwbPolaDce)
	ON_CBN_SELCHANGE(IDC_COMBO_PTT_POLA_DCE, OnSelchangeComboPttPolaDce)
	ON_CBN_SELCHANGE(IDC_COMBO_SQG_POLA_DCE, OnSelchangeComboSqgPolaDce)
	ON_CBN_SELCHANGE(IDC_COMBO_SQG_TYPE_DCE, OnSelchangeComboSqgTypeDce)
	ON_CBN_SELCHANGE(IDC_COMBO_SQM_POLA_DCE, OnSelchangeComboSqmPolaDce)
	ON_CBN_SELCHANGE(IDC_COMBO_SQM_TYPE_DCE, OnSelchangeComboSqmTypeDce)
	ON_CBN_SELCHANGE(IDC_COMBO_SQUELCH_TYPE_DCE, OnSelchangeComboSquelchTypeDce)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TXNB_LEVEL, OnDeltaposSpinTxnbLevel)
	ON_EN_CHANGE(IDC_EDIT_TXNB_LEVEL, OnChangeEditTxnbLevel)
	ON_EN_CHANGE(IDC_EDIT_RXNB_LEVEL, OnChangeEditRxnbLevel)
	ON_EN_CHANGE(IDC_EDIT_RXWB_LEVEL, OnChangeEditRxwbLevel)
	ON_EN_CHANGE(IDC_EDIT_TXWB_LEVEL, OnChangeEditTxwbLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RXNB_LEVEL, OnDeltaposSpinRxnbLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_RXWB_LEVEL, OnDeltaposSpinRxwbLevel)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TXWB_LEVEL, OnDeltaposSpinTxwbLevel)
	ON_BN_CLICKED(IDC_CHECK_ACT_ANALOG_DCE, OnCheckActAnalogDce)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42AnalogDCE message handlers

BOOL CDlgED42AnalogDCE::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Size de TXNB level
	c_txnbLevel.LimitText(3);

	//Initialisation TXNB level
	s_txnbLevel.SetRange(TX_MIN, TX_MAX);

	//Size de TXWB level
	c_txwbLevel.LimitText(3);

	//Initialisation TXWB level
	s_txwbLevel.SetRange(TX_MIN, TX_MAX);

	//Size de RXNB level
	c_rxnbLevel.LimitText(3);

	//Initialisation RXNB level
	s_rxnbLevel.SetRange(RX_MIN, RX_MAX);

	//Size de RXWB level
	c_rxwbLevel.LimitText(3);

	//Initialisation RXWB level
	s_rxwbLevel.SetRange(RX_MIN, RX_MAX);

	UpdateData(FALSE);

	return TRUE;
}

void CDlgED42AnalogDCE::LoadData(string preset)
{
	char buffer[3] = "";

	TAnalogDCE analogDCE = eqp->GetAnalogDCEParameters(preset);

	c_actAnalog.SetCheck(analogDCE.activateAnalogDceInterface);
	c_sqgPolarity.SetCurSel(analogDCE.polaritySQG);
	c_sqmPolarity.SetCurSel(analogDCE.polaritySQM);
	c_dpttPolarity.SetCurSel(analogDCE.polarityDPTT);
	c_pttPolarity.SetCurSel(analogDCE.polarityPTT);
	c_bbdpPolarity.SetCurSel(analogDCE.polarityBBDP);
	c_nbwbPolarity.SetCurSel(analogDCE.polarityNBWB);
	c_sqgType.SetCurSel(analogDCE.confTypeSQG);
	c_sqmType.SetCurSel(analogDCE.confTypeSQM);
	c_dpttType.SetCurSel(analogDCE.confTypeDPTT);
	c_squelchType.SetCurSel(analogDCE.confTypeSQUELCH);

	itoa(analogDCE.levelTXNB,buffer,10);
	//Mise à jour de la derniere valeur de TXNB afin de ne pas lever le flag de modification
	oldLevelTXNB = analogDCE.levelTXNB;
	c_txnbLevel.SetWindowText(buffer);

	itoa(analogDCE.levelRXNB,buffer,10);
	//Mise à jour de la derniere valeur de RXNB afin de ne pas lever le flag de modification
	oldLevelRXNB = analogDCE.levelRXNB;
	c_rxnbLevel.SetWindowText(buffer);

	itoa(analogDCE.levelTXWB,buffer,10);
	//Mise à jour de la derniere valeur de TXWB afin de ne pas lever le flag de modification
	oldLevelTXWB = analogDCE.levelTXWB;
	c_txwbLevel.SetWindowText(buffer);

	itoa(analogDCE.levelRXWB,buffer,10);
	//Mise à jour de la derniere valeur de RXWB afin de ne pas lever le flag de modification
	oldLevelRXWB = analogDCE.levelRXWB;
	c_rxwbLevel.SetWindowText(buffer);

	//Mise à jour des éléments à griser
	c_sqgPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_sqmPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_dpttPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_pttPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_bbdpPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_nbwbPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_sqgType.EnableWindow(c_actAnalog.GetCheck());
	c_sqmType.EnableWindow(c_actAnalog.GetCheck());
	c_dpttType.EnableWindow(c_actAnalog.GetCheck());
	c_squelchType.EnableWindow(c_actAnalog.GetCheck());
	c_txnbLevel.EnableWindow(c_actAnalog.GetCheck());
	s_txnbLevel.EnableWindow(c_actAnalog.GetCheck());
	c_rxnbLevel.EnableWindow(c_actAnalog.GetCheck());
	s_rxnbLevel.EnableWindow(c_actAnalog.GetCheck());
	c_txwbLevel.EnableWindow(c_actAnalog.GetCheck());
	s_txwbLevel.EnableWindow(c_actAnalog.GetCheck());
	c_rxwbLevel.EnableWindow(c_actAnalog.GetCheck());
	s_rxwbLevel.EnableWindow(c_actAnalog.GetCheck());
}

void CDlgED42AnalogDCE::SaveData(string preset)
{
	CString val = "";

	TAnalogDCE analogDCE = eqp->GetAnalogDCEParameters(preset);

	analogDCE.activateAnalogDceInterface	= c_actAnalog.GetCheck()==1;
	analogDCE.polaritySQG					= c_sqgPolarity.GetCurSel()==1;
	analogDCE.polaritySQM					= c_sqmPolarity.GetCurSel()==1;
	analogDCE.polarityDPTT					= c_dpttPolarity.GetCurSel()==1;
	analogDCE.polarityPTT					= c_pttPolarity.GetCurSel()==1;
	analogDCE.polarityBBDP					= c_bbdpPolarity.GetCurSel()==1;
	analogDCE.polarityNBWB					= c_nbwbPolarity.GetCurSel()==1;
	analogDCE.confTypeSQG					= c_sqgType.GetCurSel();
	analogDCE.confTypeSQM					= c_sqmType.GetCurSel();
	analogDCE.confTypeDPTT					= c_dpttType.GetCurSel();
	analogDCE.confTypeSQUELCH				= c_squelchType.GetCurSel();

	c_txnbLevel.GetWindowText(val);
	analogDCE.levelTXNB						= atoi(val);

	c_rxnbLevel.GetWindowText(val);
	analogDCE.levelRXNB						= atoi(val);

	c_txwbLevel.GetWindowText(val);
	analogDCE.levelTXWB						= atoi(val);

	c_rxwbLevel.GetWindowText(val);
	analogDCE.levelRXWB						= atoi(val);

	eqp->SetAnalogDCEParameters(preset , analogDCE);
}

void CDlgED42AnalogDCE::OnSelchangeComboBbdpPolaDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42AnalogDCE::OnSelchangeComboDpttPolaDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42AnalogDCE::OnSelchangeComboDpttTypeDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42AnalogDCE::OnSelchangeComboNbwbPolaDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42AnalogDCE::OnSelchangeComboPttPolaDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42AnalogDCE::OnSelchangeComboSqgPolaDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42AnalogDCE::OnSelchangeComboSqgTypeDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42AnalogDCE::OnSelchangeComboSqmPolaDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42AnalogDCE::OnSelchangeComboSqmTypeDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42AnalogDCE::OnSelchangeComboSquelchTypeDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42AnalogDCE::OnChangeEditTxnbLevel()
{
	CString str;

	c_txnbLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_txnbLevel = atoi((char*)LPCTSTR(str));

	if ( m_txnbLevel > TX_MAX )
	{
		AfxMessageBox("Le TXNB level peut prendre les valeurs : -47 à 13 dB");
		m_txnbLevel = TX_MAX;
	}

	if ( m_txnbLevel < TX_MIN)
	{
		AfxMessageBox("Le TXNB level peut prendre les valeurs : -47 à 13 dB");
		m_txnbLevel = TX_MIN;
	}

	if (oldLevelTXNB != m_txnbLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

}

void CDlgED42AnalogDCE::OnChangeEditRxnbLevel()
{
	CString str;

	c_rxnbLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_rxnbLevel = atoi((char*)LPCTSTR(str));

	if ( m_rxnbLevel > RX_MAX )
	{
		AfxMessageBox("Le RXNB level peut prendre les valeurs : -47 à 13 dB");
		m_rxnbLevel = RX_MAX;
	}

	if ( m_rxnbLevel < RX_MIN)
	{
		AfxMessageBox("Le RXNB level peut prendre les valeurs : -47 à 13 dB");
		m_rxnbLevel = RX_MIN;
	}

	if (oldLevelRXNB != m_rxnbLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

}

void CDlgED42AnalogDCE::OnChangeEditRxwbLevel()
{
	CString str;

	c_rxwbLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_rxwbLevel = atoi((char*)LPCTSTR(str));

	if ( m_rxwbLevel > RX_MAX )
	{
		AfxMessageBox("Le RXWB level peut prendre les valeurs : -40 à 20 dB");
		m_rxwbLevel = RX_MAX;
	}

	if ( m_rxwbLevel < RX_MIN)
	{
		AfxMessageBox("Le RXWB level peut prendre les valeurs : -40 à 20 dB");
		m_rxwbLevel = RX_MIN;
	}

	if (oldLevelRXWB != m_rxwbLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

}

void CDlgED42AnalogDCE::OnChangeEditTxwbLevel()
{
	CString str;

	c_txwbLevel.GetWindowText(str);

	//Si on recoit un '-', on ne fait pas de traitement
	if(str.Compare("-") ==0)
		return;

	m_txwbLevel = atoi((char*)LPCTSTR(str));

	if ( m_txwbLevel > TX_MAX )
	{
		AfxMessageBox("Le TXWB level peut prendre les valeurs : -40 à 20 dB");
		m_txwbLevel = TX_MAX;
	}

	if ( m_txwbLevel < TX_MIN)
	{
		AfxMessageBox("Le TXWB level peut prendre les valeurs : -40 à 20 dB");
		m_txwbLevel = TX_MIN;
	}

	if (oldLevelTXWB != m_txwbLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

}

void CDlgED42AnalogDCE::OnDeltaposSpinTxnbLevel(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_txnbLevel += 1;
		else       m_txnbLevel -= 1;


	if ( m_txnbLevel > TX_MAX )
	{
		AfxMessageBox("Le TXNB level peut prendre les valeurs : -47 à 13 dB");
		m_txnbLevel = TX_MAX;
	}

	if ( m_txnbLevel < TX_MIN)
	{
		AfxMessageBox("Le TXNB level peut prendre les valeurs : -47 à 13 dB");
		m_txnbLevel = TX_MIN;
	}

	if (oldLevelTXNB != m_txnbLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgED42AnalogDCE::OnDeltaposSpinRxnbLevel(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_rxnbLevel += 1;
		else       m_rxnbLevel -= 1;


	if ( m_rxnbLevel > RX_MAX )
	{
		AfxMessageBox("Le RXNB level peut prendre les valeurs : -40 à 20 dB");
		m_rxnbLevel = RX_MAX;
	}

	if ( m_rxnbLevel < RX_MIN)
	{
		AfxMessageBox("Le RXNB level peut prendre les valeurs : -40 à 20 dB");
		m_rxnbLevel = RX_MIN;
	}

	if (oldLevelRXNB != m_rxnbLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgED42AnalogDCE::OnDeltaposSpinRxwbLevel(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_rxwbLevel += 1;
		else       m_rxwbLevel -= 1;


	if ( m_rxwbLevel > RX_MAX )
	{
		AfxMessageBox("Le RXWB level peut prendre les valeurs : -40 à 20 dB");
		m_rxwbLevel = RX_MAX;
	}

	if ( m_rxwbLevel < RX_MIN)
	{
		AfxMessageBox("Le RXWB level peut prendre les valeurs : -40 à 20 dB");
		m_rxwbLevel = RX_MIN;
	}

	if (oldLevelRXWB != m_rxwbLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgED42AnalogDCE::OnDeltaposSpinTxwbLevel(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_txwbLevel += 1;
		else       m_txwbLevel -= 1;


	if ( m_txwbLevel > TX_MAX )
	{
		AfxMessageBox("Le TXWB level peut prendre les valeurs : -47 à 13 dB");
		m_txwbLevel = TX_MAX;
	}

	if ( m_txwbLevel < TX_MIN)
	{
		AfxMessageBox("Le TXWB level peut prendre les valeurs : -47 à 13 dB");
		m_txwbLevel = TX_MIN;
	}

	if (oldLevelTXWB != m_txwbLevel)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgED42AnalogDCE::OnCheckActAnalogDce()
{
	//Mise à jour des éléments à griser
	c_sqgPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_sqmPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_dpttPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_pttPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_bbdpPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_nbwbPolarity.EnableWindow(c_actAnalog.GetCheck());
	c_sqgType.EnableWindow(c_actAnalog.GetCheck());
	c_sqmType.EnableWindow(c_actAnalog.GetCheck());
	c_dpttType.EnableWindow(c_actAnalog.GetCheck());
	c_squelchType.EnableWindow(c_actAnalog.GetCheck());
	c_txnbLevel.EnableWindow(c_actAnalog.GetCheck());
	s_txnbLevel.EnableWindow(c_actAnalog.GetCheck());
	c_rxnbLevel.EnableWindow(c_actAnalog.GetCheck());
	s_rxnbLevel.EnableWindow(c_actAnalog.GetCheck());
	c_txwbLevel.EnableWindow(c_actAnalog.GetCheck());
	s_txwbLevel.EnableWindow(c_actAnalog.GetCheck());
	c_rxwbLevel.EnableWindow(c_actAnalog.GetCheck());
	s_rxwbLevel.EnableWindow(c_actAnalog.GetCheck());
	eqp->setModifVue(TRUE);
}
