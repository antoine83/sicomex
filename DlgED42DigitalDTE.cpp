// DlgED42DigitalDTE.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42DigitalDTE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42DigitalDTE dialog


CDlgED42DigitalDTE::CDlgED42DigitalDTE(CEquipED42 * eqp,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42DigitalDTE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42DigitalDTE)
	//}}AFX_DATA_INIT

	this->eqp = eqp;
}


void CDlgED42DigitalDTE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42DigitalDTE)
	DDX_Control(pDX, IDC_CHECK_ACT_DIGITAL_DTE, c_actDigitalDTE);
	DDX_Control(pDX, IDC_COMBO_XCK_DTE, c_xck);
	DDX_Control(pDX, IDC_COMBO_TXD_DTE, c_txd);
	DDX_Control(pDX, IDC_COMBO_RXD_DTE, c_rxd);
	DDX_Control(pDX, IDC_COMBO_RTS_DTE, c_rts);
	DDX_Control(pDX, IDC_COMBO_RTL_DTE, c_rtl);
	DDX_Control(pDX, IDC_COMBO_RNG_DTE, c_rng);
	DDX_Control(pDX, IDC_COMBO_RCK_DTE, c_rck);
	DDX_Control(pDX, IDC_COMBO_OUTPUT_LEVEL, c_outputLevel);
	DDX_Control(pDX, IDC_COMBO_LTL_DTE, c_ltl);
	DDX_Control(pDX, IDC_COMBO_LLR_DTE, c_llr);
	DDX_Control(pDX, IDC_COMBO_DTR_DTE, c_dtr);
	DDX_Control(pDX, IDC_COMBO_DSR_DTE, c_dsr);
	DDX_Control(pDX, IDC_COMBO_DCD_DTE, c_dcd);
	DDX_Control(pDX, IDC_COMBO_CTS_DTE, c_cts);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42DigitalDTE, CDialog)
	//{{AFX_MSG_MAP(CDlgED42DigitalDTE)
	ON_BN_CLICKED(IDC_CHECK_ACT_DIGITAL_DTE, OnCheckActDigitalDte)
	ON_CBN_SELCHANGE(IDC_COMBO_CTS_DTE, OnSelchangeComboCtsDte)
	ON_CBN_SELCHANGE(IDC_COMBO_DCD_DTE, OnSelchangeComboDcdDte)
	ON_CBN_SELCHANGE(IDC_COMBO_DSR_DTE, OnSelchangeComboDsrDte)
	ON_CBN_SELCHANGE(IDC_COMBO_DTR_DTE, OnSelchangeComboDtrDte)
	ON_CBN_SELCHANGE(IDC_COMBO_LLR_DTE, OnSelchangeComboLlrDte)
	ON_CBN_SELCHANGE(IDC_COMBO_LTL_DTE, OnSelchangeComboLtlDte)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT_LEVEL, OnSelchangeComboOutputLevel)
	ON_CBN_SELCHANGE(IDC_COMBO_RCK_DTE, OnSelchangeComboRckDte)
	ON_CBN_SELCHANGE(IDC_COMBO_RNG_DTE, OnSelchangeComboRngDte)
	ON_CBN_SELCHANGE(IDC_COMBO_RTL_DTE, OnSelchangeComboRtlDte)
	ON_CBN_SELCHANGE(IDC_COMBO_RTS_DTE, OnSelchangeComboRtsDte)
	ON_CBN_SELCHANGE(IDC_COMBO_RXD_DTE, OnSelchangeComboRxdDte)
	ON_CBN_SELCHANGE(IDC_COMBO_TXD_DTE, OnSelchangeComboTxdDte)
	ON_CBN_SELCHANGE(IDC_COMBO_XCK_DTE, OnSelchangeComboXckDte)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42DigitalDTE message handlers

BOOL CDlgED42DigitalDTE::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	return TRUE;  
}

void CDlgED42DigitalDTE::LoadData(string preset) 
{
	TDigitalDTE digitalDTE = eqp->GetDigitalDTEParameters(preset);

	c_actDigitalDTE.SetCheck(digitalDTE.activateDigitalDteInterface);

	BuildComboOutputLevel(preset);
	c_outputLevel.SetCurSel(digitalDTE.outputLevel);

	c_txd.SetCurSel(digitalDTE.polarityInputSignalTXD);
	c_rts.SetCurSel(digitalDTE.polarityInputSignalRTS);
	c_dtr.SetCurSel(digitalDTE.polarityInputSignalDTR);
	c_rtl.SetCurSel(digitalDTE.polarityInputSignalRTL);
	c_ltl.SetCurSel(digitalDTE.polarityInputSignalLTL);
	c_rxd.SetCurSel(digitalDTE.polarityOutputSignalRXD);
	c_cts.SetCurSel(digitalDTE.polarityOutputSignalCTS);
	c_dsr.SetCurSel(digitalDTE.polarityOutputSignalDSR);
	c_dcd.SetCurSel(digitalDTE.polarityOutputSignalDCD);
	c_xck.SetCurSel(digitalDTE.polarityOutputSignalXCK);
	c_rck.SetCurSel(digitalDTE.polarityOutputSignalRCK);
	c_rng.SetCurSel(digitalDTE.polarityOutputSignalRNG);
	c_llr.SetCurSel(digitalDTE.polarityOutputSignalLLR);

	//Mise à jour des éléments à griser
	c_outputLevel.EnableWindow(c_actDigitalDTE.GetCheck());
	c_txd.EnableWindow(c_actDigitalDTE.GetCheck());
	c_rts.EnableWindow(c_actDigitalDTE.GetCheck());
	c_dtr.EnableWindow(c_actDigitalDTE.GetCheck());
	c_rtl.EnableWindow(c_actDigitalDTE.GetCheck());
	c_ltl.EnableWindow(c_actDigitalDTE.GetCheck());
	c_rxd.EnableWindow(c_actDigitalDTE.GetCheck());
	c_cts.EnableWindow(c_actDigitalDTE.GetCheck());
	c_dsr.EnableWindow(c_actDigitalDTE.GetCheck());
	c_dcd.EnableWindow(c_actDigitalDTE.GetCheck());
	c_xck.EnableWindow(c_actDigitalDTE.GetCheck());
	c_rck.EnableWindow(c_actDigitalDTE.GetCheck());
	c_rng.EnableWindow(c_actDigitalDTE.GetCheck());
	c_llr.EnableWindow(c_actDigitalDTE.GetCheck());
}

void CDlgED42DigitalDTE::SaveData(string preset) 
{
	TDigitalDTE digitalDTE = eqp->GetDigitalDTEParameters(preset);

	digitalDTE.activateDigitalDteInterface	= c_actDigitalDTE.GetCheck() == 1;
	digitalDTE.outputLevel					= c_outputLevel.GetCurSel() == 1;
	digitalDTE.polarityInputSignalTXD		= c_txd.GetCurSel() == 1;
	digitalDTE.polarityInputSignalRTS		= c_rts.GetCurSel() == 1;
	digitalDTE.polarityInputSignalDTR		= c_dtr.GetCurSel() == 1;
	digitalDTE.polarityInputSignalRTL		= c_rtl.GetCurSel() == 1;
	digitalDTE.polarityInputSignalLTL		= c_ltl.GetCurSel() == 1;
	digitalDTE.polarityOutputSignalRXD		= c_rxd.GetCurSel() == 1;
	digitalDTE.polarityOutputSignalCTS		= c_cts.GetCurSel() == 1;
	digitalDTE.polarityOutputSignalDSR		= c_dsr.GetCurSel() == 1;
	digitalDTE.polarityOutputSignalDCD		= c_dcd.GetCurSel() == 1;
	digitalDTE.polarityOutputSignalXCK		= c_xck.GetCurSel() == 1;
	digitalDTE.polarityOutputSignalRCK		= c_rck.GetCurSel() == 1;
	digitalDTE.polarityOutputSignalRNG		= c_rng.GetCurSel() == 1;
	digitalDTE.polarityOutputSignalLLR		= c_llr.GetCurSel() == 1;

	eqp->SetDigitalDTEParameters(preset , digitalDTE);
}

void CDlgED42DigitalDTE::OnCheckActDigitalDte() 
{
	//Mise à jour des éléments à griser
	c_outputLevel.EnableWindow(c_actDigitalDTE.GetCheck());
	c_txd.EnableWindow(c_actDigitalDTE.GetCheck());
	c_rts.EnableWindow(c_actDigitalDTE.GetCheck());
	c_dtr.EnableWindow(c_actDigitalDTE.GetCheck());
	c_rtl.EnableWindow(c_actDigitalDTE.GetCheck());
	c_ltl.EnableWindow(c_actDigitalDTE.GetCheck());
	c_rxd.EnableWindow(c_actDigitalDTE.GetCheck());
	c_cts.EnableWindow(c_actDigitalDTE.GetCheck());
	c_dsr.EnableWindow(c_actDigitalDTE.GetCheck());
	c_dcd.EnableWindow(c_actDigitalDTE.GetCheck());
	c_xck.EnableWindow(c_actDigitalDTE.GetCheck());
	c_rck.EnableWindow(c_actDigitalDTE.GetCheck());
	c_rng.EnableWindow(c_actDigitalDTE.GetCheck());
	c_llr.EnableWindow(c_actDigitalDTE.GetCheck());

	eqp->setModifVue(TRUE);	
	
}

void CDlgED42DigitalDTE::OnSelchangeComboCtsDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboDcdDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboDsrDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboDtrDte() 
{
	eqp->setModifVue(TRUE);	
}

void CDlgED42DigitalDTE::OnSelchangeComboLlrDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboLtlDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboOutputLevel() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboRckDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboRngDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboRtlDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboRtsDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboRxdDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboTxdDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::OnSelchangeComboXckDte() 
{
	eqp->setModifVue(TRUE);		
}

void CDlgED42DigitalDTE::BuildComboOutputLevel(string preset)
{
	TGeneralParameters generalParameter = eqp->GetGeneralParameters(preset);
	if(generalParameter.transmission_mode == LOS 
		|| generalParameter.transmission_mode == HF)
	{
		c_outputLevel.ResetContent();
		c_outputLevel.AddString(OUTPUT_LEVEL_DIGITAL_INTERFACE[V10].c_str());
		c_outputLevel.AddString(OUTPUT_LEVEL_DIGITAL_INTERFACE[V11].c_str());
		c_outputLevel.EnableWindow(TRUE);
	}
	else
	{
		c_outputLevel.ResetContent();
		for(int cpt=0;cpt<NB_OUTPUT_LEVEL_DIGITAL_INTERFACE;cpt++)
		{
			c_outputLevel.AddString(OUTPUT_LEVEL_DIGITAL_INTERFACE[cpt].c_str());
		}
		c_outputLevel.EnableWindow(TRUE);
	}
}