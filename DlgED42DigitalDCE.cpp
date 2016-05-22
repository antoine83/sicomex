// DlgED42DigitalDCE.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42DigitalDCE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42DigitalDCE dialog


CDlgED42DigitalDCE::CDlgED42DigitalDCE(CEquipED42 * eqp,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42DigitalDCE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42DigitalDCE)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
	this->eqp = eqp;
}


void CDlgED42DigitalDCE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42DigitalDCE)
	DDX_Control(pDX, IDC_COMBO_XCK_DCE, m_xck);
	DDX_Control(pDX, IDC_COMBO_TXD_DCE, m_txd);
	DDX_Control(pDX, IDC_COMBO_TCK_DCE, m_tck);
	DDX_Control(pDX, IDC_COMBO_RXD_DCE, m_rxd);
	DDX_Control(pDX, IDC_COMBO_RTS_DCE, m_rts);
	DDX_Control(pDX, IDC_COMBO_RTL_DCE, m_rtl);
	DDX_Control(pDX, IDC_COMBO_RNG_DCE, m_rng);
	DDX_Control(pDX, IDC_COMBO_RCK_DCE, m_rck);
	DDX_Control(pDX, IDC_COMBO_OUTPUT_LEVEL, m_outputLevel);
	DDX_Control(pDX, IDC_COMBO_LTL_DCE, m_ltl);
	DDX_Control(pDX, IDC_COMBO_LLR_DCE, m_llr);
	DDX_Control(pDX, IDC_COMBO_DTR_DCE, m_dtr);
	DDX_Control(pDX, IDC_COMBO_DSR_DCE, m_dsr);
	DDX_Control(pDX, IDC_COMBO_DCD_DCE, m_dcd);
	DDX_Control(pDX, IDC_COMBO_CTS_DCE, m_cts);
	DDX_Control(pDX, IDC_CHECK_ACT_DIGITAL_DCE, m_actDigitalDCE);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42DigitalDCE, CDialog)
	//{{AFX_MSG_MAP(CDlgED42DigitalDCE)
	ON_BN_CLICKED(IDC_CHECK_ACT_DIGITAL_DCE, OnCheckActDigitalDce)
	ON_CBN_SELCHANGE(IDC_COMBO_CTS_DCE, OnSelchangeComboCtsDce)
	ON_CBN_SELCHANGE(IDC_COMBO_DCD_DCE, OnSelchangeComboDcdDce)
	ON_CBN_SELCHANGE(IDC_COMBO_DSR_DCE, OnSelchangeComboDsrDce)
	ON_CBN_SELCHANGE(IDC_COMBO_DTR_DCE, OnSelchangeComboDtrDce)
	ON_CBN_SELCHANGE(IDC_COMBO_LLR_DCE, OnSelchangeComboLlrDce)
	ON_CBN_SELCHANGE(IDC_COMBO_LTL_DCE, OnSelchangeComboLtlDce)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT_LEVEL, OnSelchangeComboOutputLevel)
	ON_CBN_SELCHANGE(IDC_COMBO_RCK_DCE, OnSelchangeComboRckDce)
	ON_CBN_SELCHANGE(IDC_COMBO_RNG_DCE, OnSelchangeComboRngDce)
	ON_CBN_SELCHANGE(IDC_COMBO_RTL_DCE, OnSelchangeComboRtlDce)
	ON_CBN_SELCHANGE(IDC_COMBO_RTS_DCE, OnSelchangeComboRtsDce)
	ON_CBN_SELCHANGE(IDC_COMBO_RXD_DCE, OnSelchangeComboRxdDce)
	ON_CBN_SELCHANGE(IDC_COMBO_TCK_DCE, OnSelchangeComboTckDce)
	ON_CBN_SELCHANGE(IDC_COMBO_TXD_DCE, OnSelchangeComboTxdDce)
	ON_CBN_SELCHANGE(IDC_COMBO_XCK_DCE, OnSelchangeComboXckDce)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42DigitalDCE message handlers

BOOL CDlgED42DigitalDCE::OnInitDialog()
{
	CDialog::OnInitDialog();

	return TRUE;
}

void CDlgED42DigitalDCE::LoadData(string preset)
{
	TDigitalDCE digitalDCE = eqp->GetDigitalDCEParameters(preset);

	m_actDigitalDCE.SetCheck(digitalDCE.activateDigitalDceInterface);
	m_outputLevel.SetCurSel(digitalDCE.outputLevel);
	m_txd.SetCurSel(digitalDCE.polarityOutputSignalTXD);
	m_rts.SetCurSel(digitalDCE.polarityOutputSignalRTS);
	m_dtr.SetCurSel(digitalDCE.polarityOutputSignalDTR);
	m_tck.SetCurSel(digitalDCE.polarityOutputSignalTCK);
	m_rtl.SetCurSel(digitalDCE.polarityOutputSignalRTL);
	m_ltl.SetCurSel(digitalDCE.polarityOutputSignalLTL);
	m_rxd.SetCurSel(digitalDCE.polarityInputSignalRXD);
	m_cts.SetCurSel(digitalDCE.polarityInputSignalCTS);
	m_dsr.SetCurSel(digitalDCE.polarityInputSignalDSR);
	m_dcd.SetCurSel(digitalDCE.polarityInputSignalDCD);
	m_xck.SetCurSel(digitalDCE.polarityInputSignalXCK);
	m_rck.SetCurSel(digitalDCE.polarityInputSignalRCK);
	m_rng.SetCurSel(digitalDCE.polarityInputSignalRNG);
	m_llr.SetCurSel(digitalDCE.polarityInputSignalLLR);

	//Mise à jour des éléments à griser
	m_outputLevel.EnableWindow(m_actDigitalDCE.GetCheck());
	m_txd.EnableWindow(m_actDigitalDCE.GetCheck());
	m_rts.EnableWindow(m_actDigitalDCE.GetCheck());
	m_dtr.EnableWindow(m_actDigitalDCE.GetCheck());
	m_tck.EnableWindow(m_actDigitalDCE.GetCheck());
	m_rtl.EnableWindow(m_actDigitalDCE.GetCheck());
	m_ltl.EnableWindow(m_actDigitalDCE.GetCheck());
	m_rxd.EnableWindow(m_actDigitalDCE.GetCheck());
	m_cts.EnableWindow(m_actDigitalDCE.GetCheck());
	m_dsr.EnableWindow(m_actDigitalDCE.GetCheck());
	m_dcd.EnableWindow(m_actDigitalDCE.GetCheck());
	m_xck.EnableWindow(m_actDigitalDCE.GetCheck());
	m_rck.EnableWindow(m_actDigitalDCE.GetCheck());
	m_rng.EnableWindow(m_actDigitalDCE.GetCheck());
	m_llr.EnableWindow(m_actDigitalDCE.GetCheck());
}

void CDlgED42DigitalDCE::SaveData(string preset)
{
	TDigitalDCE digitalDCE = eqp->GetDigitalDCEParameters(preset);

	digitalDCE.activateDigitalDceInterface	= m_actDigitalDCE.GetCheck()==1;
	digitalDCE.outputLevel					= m_outputLevel.GetCurSel();
	digitalDCE.polarityOutputSignalTXD		= m_txd.GetCurSel()==1;
	digitalDCE.polarityOutputSignalRTS		= m_rts.GetCurSel()==1;
	digitalDCE.polarityOutputSignalDTR		= m_dtr.GetCurSel()==1;
	digitalDCE.polarityOutputSignalTCK		= m_tck.GetCurSel()==1;
	digitalDCE.polarityOutputSignalRTL		= m_rtl.GetCurSel()==1;
	digitalDCE.polarityOutputSignalLTL		= m_ltl.GetCurSel()==1;
	digitalDCE.polarityInputSignalRXD		= m_rxd.GetCurSel()==1;
	digitalDCE.polarityInputSignalCTS		= m_cts.GetCurSel()==1;
	digitalDCE.polarityInputSignalDSR		= m_dsr.GetCurSel()==1;
	digitalDCE.polarityInputSignalDCD		= m_dcd.GetCurSel()==1;
	digitalDCE.polarityInputSignalXCK		= m_xck.GetCurSel()==1;
	digitalDCE.polarityInputSignalRCK		= m_rck.GetCurSel()==1;
	digitalDCE.polarityInputSignalRNG		= m_rng.GetCurSel()==1;
	digitalDCE.polarityInputSignalLLR		= m_llr.GetCurSel()==1;

	eqp->SetDigitalDCEParameters(preset , digitalDCE);
}

void CDlgED42DigitalDCE::OnCheckActDigitalDce()
{
	//Mise à jour des éléments à griser
	m_outputLevel.EnableWindow(m_actDigitalDCE.GetCheck());
	m_txd.EnableWindow(m_actDigitalDCE.GetCheck());
	m_rts.EnableWindow(m_actDigitalDCE.GetCheck());
	m_dtr.EnableWindow(m_actDigitalDCE.GetCheck());
	m_tck.EnableWindow(m_actDigitalDCE.GetCheck());
	m_rtl.EnableWindow(m_actDigitalDCE.GetCheck());
	m_ltl.EnableWindow(m_actDigitalDCE.GetCheck());
	m_rxd.EnableWindow(m_actDigitalDCE.GetCheck());
	m_cts.EnableWindow(m_actDigitalDCE.GetCheck());
	m_dsr.EnableWindow(m_actDigitalDCE.GetCheck());
	m_dcd.EnableWindow(m_actDigitalDCE.GetCheck());
	m_xck.EnableWindow(m_actDigitalDCE.GetCheck());
	m_rck.EnableWindow(m_actDigitalDCE.GetCheck());
	m_rng.EnableWindow(m_actDigitalDCE.GetCheck());
	m_llr.EnableWindow(m_actDigitalDCE.GetCheck());

	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboCtsDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboDcdDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboDsrDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboDtrDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboLlrDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboLtlDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboOutputLevel()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboRckDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboRngDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboRtlDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboRtsDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboRxdDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboTckDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboTxdDce()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42DigitalDCE::OnSelchangeComboXckDce()
{
	eqp->setModifVue(TRUE);
}
