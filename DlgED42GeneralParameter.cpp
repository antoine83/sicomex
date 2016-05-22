// DlgED42GeneralParameter.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42GeneralParameter.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif



/////////////////////////////////////////////////////////////////////////////
// CDlgED42GeneralParameter dialog


CDlgED42GeneralParameter::CDlgED42GeneralParameter(CEquipED42 * eqp,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42GeneralParameter::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42GeneralParameter)
	//}}AFX_DATA_INIT
	this->eqp = eqp;
	oldLead_time = "";
}


void CDlgED42GeneralParameter::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42GeneralParameter)
	DDX_Control(pDX, IDC_EDIT_LEAD_TIME, m_leadTime);
	DDX_Control(pDX, IDC_COMBO_TRANS_PROC, m_transProc);
	DDX_Control(pDX, IDC_COMBO_TRANS_MODE, m_transMode);
	DDX_Control(pDX, IDC_COMBO_TRAFF_MODE, m_traffMode);
	DDX_Control(pDX, IDC_COMBO_SYNCHRO_MODE, m_synchroMode);
	DDX_Control(pDX, IDC_COMBO_PARITY, m_parity);
	DDX_Control(pDX, IDC_COMBO_OUTPUT_SEL, m_outputSel);
	DDX_Control(pDX, IDC_COMBO_NUM_STOP_BIT, m_numStopBit);
	DDX_Control(pDX, IDC_COMBO_NUM_DATA_BIT, m_numDataBit);
	DDX_Control(pDX, IDC_COMBO_DATA_RATE, m_dataRate);
	DDX_Control(pDX, IDC_COMBO_CLOCK_MODE, m_clockMode);
	DDX_Control(pDX, IDC_CHECK_FEC, m_fec);
	DDX_Control(pDX, IDC_CHECK_ANTISPOOF, m_antispoof);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42GeneralParameter, CDialog)
	//{{AFX_MSG_MAP(CDlgED42GeneralParameter)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANS_MODE, OnSelchangeComboTransMode)
	ON_CBN_SELCHANGE(IDC_COMBO_TRANS_PROC, OnSelchangeComboTransProc)
	ON_CBN_SELCHANGE(IDC_COMBO_TRAFF_MODE, OnSelchangeComboTraffMode)
	ON_CBN_SELCHANGE(IDC_COMBO_OUTPUT_SEL, OnSelchangeComboOutputSel)
	ON_CBN_SELCHANGE(IDC_COMBO_SYNCHRO_MODE, OnSelchangeComboSynchroMode)
	ON_CBN_SELCHANGE(IDC_COMBO_DATA_RATE, OnSelchangeComboDataRate)
	ON_CBN_SELCHANGE(IDC_COMBO_CLOCK_MODE, OnSelchangeComboClockMode)
	ON_CBN_SELCHANGE(IDC_COMBO_NUM_DATA_BIT, OnSelchangeComboNumDataBit)
	ON_CBN_SELCHANGE(IDC_COMBO_PARITY, OnSelchangeComboParity)
	ON_CBN_SELCHANGE(IDC_COMBO_NUM_STOP_BIT, OnSelchangeComboNumStopBit)
	ON_EN_CHANGE(IDC_EDIT_LEAD_TIME, OnChangeEditLeadTime)
	ON_BN_CLICKED(IDC_CHECK_FEC, OnCheckFec)
	ON_BN_CLICKED(IDC_CHECK_ANTISPOOF, OnCheckAntispoof)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42GeneralParameter message handlers

BOOL CDlgED42GeneralParameter::OnInitDialog()
{
	CDialog::OnInitDialog();
	m_leadTime.LimitText(2);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgED42GeneralParameter::LoadData(string preset)
{
	char buffer[3] = "";

	this->generalParameter = eqp->GetGeneralParameters(preset);
	this->digitalDCE = eqp->GetDigitalDCEParameters(preset);
	this->analogDCE = eqp->GetAnalogDCEParameters(preset);
	this->digitalDTE = eqp->GetDigitalDTEParameters(preset);
	this->analogDTE = eqp->GetAnalogDTEParameters(preset);

	BuildComposant(IDC_COMBO_TRANS_MODE);
	SetCurSelValueToCombo(IDC_COMBO_TRANS_MODE);

	UpdateDialog(IDC_COMBO_TRANS_MODE);
}

void CDlgED42GeneralParameter::SaveData(string preset)
{
	CString leadTime = "";

	generalParameter.transmission_mode		= GetCurSelComboToValue(IDC_COMBO_TRANS_MODE);
	generalParameter.transmission_procedure = GetCurSelComboToValue(IDC_COMBO_TRANS_PROC);
	generalParameter.trafic_mode			= GetCurSelComboToValue(IDC_COMBO_TRAFF_MODE);
	generalParameter.synchronisation_mode	= GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE);
	generalParameter.parity					= GetCurSelComboToValue(IDC_COMBO_PARITY);
	generalParameter.output_selection		= GetCurSelComboToValue(IDC_COMBO_OUTPUT_SEL);
	generalParameter.nb_of_stop_bite		= GetCurSelComboToValue(IDC_COMBO_NUM_STOP_BIT);
	generalParameter.nb_of_data_bite		= GetCurSelComboToValue(IDC_COMBO_NUM_DATA_BIT);
	generalParameter.data_rate				= GetCurSelComboToValue(IDC_COMBO_DATA_RATE);
	generalParameter.clock_mode				= GetCurSelComboToValue(IDC_COMBO_CLOCK_MODE);

	m_leadTime.GetWindowText(leadTime);
	generalParameter.lead_time				= atoi(leadTime);
	generalParameter.fec					= (m_fec.GetCheck() == 1);
	generalParameter.antispoof				= (m_antispoof.GetCheck() == 1);

	if(eqp->GetOperatingStatus() == ONLINE)
	{
		eqp->SetTransmissionProcedure(GetCurSelComboToValue(IDC_COMBO_TRANS_PROC));
		eqp->SetTraficMode(GetCurSelComboToValue(IDC_COMBO_TRAFF_MODE));
	}


	switch(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE))
	{
	case VUHFANA:
	case VUHFPL:
	case HF:
	case LOS:
		digitalDCE.activateDigitalDceInterface	= FALSE;
		analogDCE.activateAnalogDceInterface	= TRUE;
		digitalDTE.activateDigitalDteInterface	= FALSE;
		analogDTE.activateAnalogDteInterface	= TRUE;
		analogDTE.activateCentralAudioInterface = FALSE;
		analogDTE.activateLocalAudioInterface	= TRUE;
		break;
	case VUHFDIG:
		digitalDCE.activateDigitalDceInterface	= FALSE;
		analogDCE.activateAnalogDceInterface	= TRUE;
		digitalDTE.activateDigitalDteInterface	= FALSE;
		analogDTE.activateAnalogDteInterface	= TRUE;
		analogDTE.activateCentralAudioInterface = FALSE;
		analogDTE.activateLocalAudioInterface	= TRUE;
		break;
	case DIGITAL:
		digitalDCE.activateDigitalDceInterface	= TRUE;
		analogDCE.activateAnalogDceInterface	= FALSE;
		digitalDTE.activateDigitalDteInterface	= FALSE;
		analogDTE.activateAnalogDteInterface	= TRUE;
		analogDTE.activateCentralAudioInterface = FALSE;
		analogDTE.activateLocalAudioInterface	= TRUE;
		break;
	default:
		digitalDCE.activateDigitalDceInterface	= FALSE;
		analogDCE.activateAnalogDceInterface	= FALSE;
		digitalDTE.activateDigitalDteInterface	= FALSE;
		analogDTE.activateAnalogDteInterface	= FALSE;
		analogDTE.activateCentralAudioInterface = FALSE;
		analogDTE.activateLocalAudioInterface	= FALSE;
		break;
	}

	switch(GetCurSelComboToValue(IDC_COMBO_OUTPUT_SEL))
	{
	case TXD:
		digitalDCE.activateDigitalDceInterface	= TRUE;
		break;
	}

	if ((generalParameter.preset>=0 && generalParameter.preset<8) ||
		(generalParameter.preset>=16 && generalParameter.preset<24) )
	{
		digitalDCE.activateDigitalDceInterface	= TRUE;
		analogDCE.activateAnalogDceInterface	= FALSE;
		digitalDTE.activateDigitalDteInterface	= TRUE;
		analogDTE.activateAnalogDteInterface	= FALSE;
		analogDTE.activateCentralAudioInterface = FALSE;
		analogDTE.activateLocalAudioInterface	= FALSE;
	}

	if ((generalParameter.preset>=0 && generalParameter.preset<8) && 
		(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == LOS ||
		 GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == HF))
	{
		digitalDCE.activateDigitalDceInterface	= FALSE;
		analogDCE.activateAnalogDceInterface	= TRUE;
		digitalDTE.activateDigitalDteInterface	= TRUE;
		analogDTE.activateAnalogDteInterface	= TRUE;
		analogDTE.activateCentralAudioInterface = FALSE;
		analogDTE.activateLocalAudioInterface	= TRUE;
	}

	eqp->SetGeneralParameters(preset, generalParameter);
	eqp->SetDigitalDCEParameters(preset, digitalDCE);
	eqp->SetAnalogDCEParameters(preset, analogDCE);
	eqp->SetDigitalDTEParameters(preset, digitalDTE);
	eqp->SetAnalogDTEParameters(preset, analogDTE);
}

void CDlgED42GeneralParameter::OnSelchangeComboTransMode()
{
	eqp->setModifVue(TRUE);
	UpdateDialog(IDC_COMBO_TRANS_MODE);
}

void CDlgED42GeneralParameter::OnSelchangeComboTransProc()
{
	eqp->setModifVue(TRUE);
	UpdateDialog(IDC_COMBO_TRANS_PROC);
}

void CDlgED42GeneralParameter::OnSelchangeComboTraffMode()
{
	eqp->setModifVue(TRUE);
	UpdateDialog(IDC_COMBO_TRAFF_MODE);
}

void CDlgED42GeneralParameter::OnSelchangeComboOutputSel()
{
	eqp->setModifVue(TRUE);
	UpdateDialog(IDC_COMBO_OUTPUT_SEL);
}

void CDlgED42GeneralParameter::OnSelchangeComboSynchroMode()
{
	eqp->setModifVue(TRUE);
	UpdateDialog(IDC_COMBO_SYNCHRO_MODE);
}

void CDlgED42GeneralParameter::OnSelchangeComboDataRate()
{
	eqp->setModifVue(TRUE);
	UpdateDialog(IDC_COMBO_DATA_RATE);
}

void CDlgED42GeneralParameter::OnSelchangeComboClockMode()
{
	eqp->setModifVue(TRUE);
	UpdateDialog(IDC_COMBO_CLOCK_MODE);
}

void CDlgED42GeneralParameter::OnSelchangeComboNumDataBit()
{
	eqp->setModifVue(TRUE);
	UpdateDialog(IDC_COMBO_NUM_DATA_BIT);
}

void CDlgED42GeneralParameter::OnSelchangeComboParity()
{
	eqp->setModifVue(TRUE);
	UpdateDialog(IDC_COMBO_PARITY);
}

void CDlgED42GeneralParameter::OnSelchangeComboNumStopBit()
{
	eqp->setModifVue(TRUE);
	UpdateDialog(IDC_COMBO_NUM_STOP_BIT);
}

void CDlgED42GeneralParameter::OnChangeEditLeadTime()
{
	CString val;
	m_leadTime.GetWindowText(val);

	if (oldLead_time.compare(val)!=0)
		eqp->setModifVue(TRUE);
}

void CDlgED42GeneralParameter::OnCheckFec()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42GeneralParameter::OnCheckAntispoof()
{
	eqp->setModifVue(TRUE);
}

void CDlgED42GeneralParameter::BuildComposant(int composant)
{
	int cpt =0;
	eqp->setReceptionDonnee(FALSE);
	//-----------------------------------------------------------------------------
	//-----                      DATA CRYPTO                                  -----
	//-----------------------------------------------------------------------------
	if(generalParameter.preset>=0 && generalParameter.preset<8)
	{
		switch(composant)
		{
		//--------------Construction du combo transmission mode--------------
		case IDC_COMBO_TRANS_MODE:
			m_transMode.ResetContent();
			for(cpt=0;cpt<(sizeof(TRANSMISSION_MODES_DATA_CRYPTO)/sizeof(string));cpt++)
			{
				m_transMode.AddString(TRANSMISSION_MODES_DATA_CRYPTO[cpt].c_str());
			}
			m_transMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			break;
		//--------------Construction du combo transmission procédure--------------
		case IDC_COMBO_TRANS_PROC:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				m_transProc.ResetContent();
				for(cpt=0;cpt<(sizeof(TRANSMISSION_PROCEDURES_DATA_CRYPTO_DIGITAL)/sizeof(string));cpt++)
				{
					m_transProc.AddString(TRANSMISSION_PROCEDURES_DATA_CRYPTO_DIGITAL[cpt].c_str());
				}
				m_transProc.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			}
			else
				m_transProc.EnableWindow(FALSE);
			break;
		//--------------Construction du combo traffic mode--------------
		case IDC_COMBO_TRAFF_MODE:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				switch(GetCurSelComboToValue(IDC_COMBO_TRANS_PROC))
				{
				case V24:
					m_traffMode.ResetContent();
					for(cpt=0;cpt<(sizeof(TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_V24)/sizeof(string));cpt++)
					{
						m_traffMode.AddString(TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_V24[cpt].c_str());
					}
					m_traffMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				case V25BIS:
					m_traffMode.ResetContent();
					for(cpt=0;cpt<(sizeof(TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_V25BIS)/sizeof(string));cpt++)
					{
						m_traffMode.AddString(TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_V25BIS[cpt].c_str());
					}
					m_traffMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				case X21:
					m_traffMode.ResetContent();
					for(cpt=0;cpt<(sizeof(TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_X21)/sizeof(string));cpt++)
					{
						m_traffMode.AddString(TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_X21[cpt].c_str());
					}
					m_traffMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				case V24HA:
					m_traffMode.ResetContent();
					for(cpt=0;cpt<(sizeof(TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_V24HA)/sizeof(string));cpt++)
					{
						m_traffMode.AddString(TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_V24HA[cpt].c_str());
						string toto = TRAFFIC_MODES_DATA_CRYPTO_DIGITAL_V24HA[cpt];
					}
					m_traffMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				}
			}
			else
			{
				m_traffMode.EnableWindow(FALSE);
			}
			break;
		//--------------Construction du combo sync mode--------------
		case IDC_COMBO_SYNCHRO_MODE:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				switch(GetCurSelComboToValue(IDC_COMBO_TRANS_PROC))
				{
				case V24:
					switch(GetCurSelComboToValue(IDC_COMBO_TRAFF_MODE))
					{
					case DX:
					case DXD:
						m_synchroMode.ResetContent();
						for(cpt=0;cpt<NB_SYNC_MODES;cpt++)
						{
							m_synchroMode.AddString(SYNC_MODES_SHORT[cpt].c_str());
						}
						m_synchroMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					case HDX:
						m_synchroMode.ResetContent();
						m_synchroMode.AddString(SYNC_MODES_SHORT[SYN_SYN].c_str());
						m_synchroMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					default:
						m_synchroMode.ResetContent();
						m_synchroMode.AddString(SYNC_MODES_SHORT[SYN_SYN].c_str());
						m_synchroMode.AddString(SYNC_MODES_SHORT[ASY_SYN].c_str());
						m_synchroMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					}
					break;
				case V25BIS:
					switch(GetCurSelComboToValue(IDC_COMBO_TRAFF_MODE))
					{
					case AAS:
					case AEB:
						m_synchroMode.ResetContent();
						m_synchroMode.AddString(SYNC_MODES_SHORT[ASY_ASY].c_str());
						m_synchroMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					default:
						m_synchroMode.ResetContent();
						m_synchroMode.AddString(SYNC_MODES_SHORT[SYN_SYN].c_str());
						m_synchroMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					}
					break;
				case X21:
					m_synchroMode.ResetContent();
					m_synchroMode.AddString(SYNC_MODES_SHORT[SYN_SYN].c_str());
					m_synchroMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				case V24HA:
					m_synchroMode.ResetContent();
					m_synchroMode.AddString(SYNC_MODES_SHORT[ASY_ASY].c_str());
					m_synchroMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				}
			}
			else
			{
				m_synchroMode.EnableWindow(FALSE);
			}
			break;
		//--------------Construction du combo output--------------
		case IDC_COMBO_OUTPUT_SEL:
			m_outputSel.EnableWindow(FALSE);
			break;
		//--------------Construction du combo clock mode--------------
		case IDC_COMBO_CLOCK_MODE:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				switch(GetCurSelComboToValue(IDC_COMBO_TRANS_PROC))
				{
				case V24:
					switch(GetCurSelComboToValue(IDC_COMBO_TRAFF_MODE))
					{
					case DX:
					case DXD:
						if(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE) == ASY_ASY)
							m_clockMode.EnableWindow(FALSE);
						else
						{
							m_clockMode.ResetContent();
							for(cpt=0;cpt<NB_CLOCK_MODES;cpt++)
							{
								m_clockMode.AddString(CLOCK_MODES[cpt].c_str());
							}
							m_clockMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						}
						break;
					default :
						m_clockMode.ResetContent();
						for(cpt=0;cpt<NB_CLOCK_MODES;cpt++)
						{
							m_clockMode.AddString(CLOCK_MODES[cpt].c_str());
						}
						m_clockMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					}
					break;
				case V25BIS:
					if(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE) == ASY_ASY)
						m_clockMode.EnableWindow(FALSE);
					else
					{
						m_clockMode.ResetContent();
						for(cpt=0;cpt<NB_CLOCK_MODES;cpt++)
						{
							m_clockMode.AddString(CLOCK_MODES[cpt].c_str());
						}
						m_clockMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					}
					break;
				case X21:
					m_clockMode.ResetContent();
					m_clockMode.AddString(CLOCK_MODES[DCE].c_str());
					m_clockMode.EnableWindow(TRUE);
					break;

				default:
					m_clockMode.EnableWindow(FALSE);
					break;
				}
			}
			else
			{
				m_clockMode.EnableWindow(FALSE);
			}
			break;
		//--------------Construction du combo number of data bits--------------
		case IDC_COMBO_NUM_DATA_BIT:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				switch(GetCurSelComboToValue(IDC_COMBO_TRANS_PROC))
				{
				case V24:
				case V24HA:
					if(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE) == SYN_SYN)
						m_numDataBit.EnableWindow(FALSE);
					else
					{
						m_numDataBit.ResetContent();
						m_numDataBit.AddString(NUMBERS_OF_DATA_BITS_SHORT[BITS_7].c_str());
						m_numDataBit.AddString(NUMBERS_OF_DATA_BITS_SHORT[BITS_8].c_str());
						m_numDataBit.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					}
					break;
				case V25BIS:
					switch(GetCurSelComboToValue(IDC_COMBO_TRAFF_MODE))
					{
					case AAS:
						m_numDataBit.ResetContent();
						m_numDataBit.AddString(NUMBERS_OF_DATA_BITS_SHORT[BITS_7].c_str());
						m_numDataBit.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					case AEB:
						m_numDataBit.ResetContent();
						m_numDataBit.AddString(NUMBERS_OF_DATA_BITS_SHORT[BITS_8].c_str());
						m_numDataBit.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					default:
						m_numDataBit.EnableWindow(FALSE);
						break;
					}
					break;
				default:
					m_numDataBit.EnableWindow(FALSE);
					break;
				}
			}
			else
			{
				m_numDataBit.EnableWindow(FALSE);
			}
			break;
		//--------------Construction du combo parity--------------
		case IDC_COMBO_PARITY:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				switch(GetCurSelComboToValue(IDC_COMBO_TRANS_PROC))
				{
				case V24:
				case V24HA:
					if(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE) == SYN_SYN)
						m_parity.EnableWindow(FALSE);
					else
					{
						m_parity.ResetContent();
						for(cpt=0;cpt<NB_PARITY_MODE;cpt++)
						{
							m_parity.AddString(PARITY_MODE[cpt].c_str());
						}
						m_parity.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					}
					break;
				case V25BIS:
					switch(GetCurSelComboToValue(IDC_COMBO_TRAFF_MODE))
					{
					case AAS:
						m_parity.ResetContent();
						m_parity.AddString(PARITY_MODE[ODD].c_str());
						m_parity.AddString(PARITY_MODE[EVEN].c_str());
						m_parity.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					case AEB:
						m_parity.ResetContent();
						m_parity.AddString(PARITY_MODE[NONE].c_str());
						m_parity.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					default:
						m_parity.EnableWindow(FALSE);
						break;
					}
					break;
				default:
					m_parity.EnableWindow(FALSE);
					break;
				}
			}
			else
			{
				m_parity.EnableWindow(FALSE);
			}
			break;
		//--------------Construction du combo number of stop bits--------------
		case IDC_COMBO_NUM_STOP_BIT:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				switch(GetCurSelComboToValue(IDC_COMBO_TRANS_PROC))
				{
				case V24:
				case V24HA:
					switch(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE))
					{
					case ASY_SYN:
						m_numStopBit.ResetContent();
						m_numStopBit.AddString(NUMBERS_OF_STOP_BITS_SHORT[BITS_2].c_str());
						m_numStopBit.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					case ASY_ASY:
						m_numStopBit.ResetContent();
						for(cpt=0;cpt<NB_NUMBERS_OF_STOP_BITS;cpt++)
						{
							m_numStopBit.AddString(NUMBERS_OF_STOP_BITS_SHORT[cpt].c_str());
						}
						m_numStopBit.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					default:
						m_numStopBit.EnableWindow(FALSE);
						break;
					}
					break;
				case V25BIS:
					switch(GetCurSelComboToValue(IDC_COMBO_TRAFF_MODE))
					{
					case AAS:
					case AEB:
						m_numStopBit.ResetContent();
						m_numStopBit.AddString(NUMBERS_OF_STOP_BITS_SHORT[BITS_1].c_str());
						m_numStopBit.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
						break;
					default:
						m_numStopBit.EnableWindow(FALSE);
						break;
					}
					break;
				default:
					m_numStopBit.EnableWindow(FALSE);
					break;
				}
			}
			else
			{
				m_numStopBit.EnableWindow(FALSE);
			}
			break;
		//--------------Construction du combo data rate--------------
		case IDC_COMBO_DATA_RATE:
			switch(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE))
			{
			case LOS:
				m_dataRate.ResetContent();
				for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_2)/sizeof(string));cpt++)
				{
					m_dataRate.AddString(DATA_RATE_ITEMS_2[cpt].c_str());
				}
				m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
				break;
			case HF:
				m_dataRate.ResetContent();
				for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_4)/sizeof(string));cpt++)
				{
					m_dataRate.AddString(DATA_RATE_ITEMS_4[cpt].c_str());
				}
				m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
				break;
			case DIGITAL:
				switch(GetCurSelComboToValue(IDC_COMBO_TRANS_PROC))
				{
				case V24:
				case X21:
				case V24HA:
					if(GetCurSelComboToValue(IDC_COMBO_TRAFF_MODE) == HDX)
					{
						m_dataRate.ResetContent();
						for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_4)/sizeof(string));cpt++)
						{
							m_dataRate.AddString(DATA_RATE_ITEMS_4[cpt].c_str());
						}
						m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					}
					else
					{
						switch(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE))
						{
						case ASY_ASY:
							m_dataRate.ResetContent();
							for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_10)/sizeof(string));cpt++)
							{
								m_dataRate.AddString(DATA_RATE_ITEMS_10[cpt].c_str());
							}
							m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
							break;
						case ASY_SYN:
							m_dataRate.ResetContent();
							for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_9)/sizeof(string));cpt++)
							{
								m_dataRate.AddString(DATA_RATE_ITEMS_9[cpt].c_str());
							}
							m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
							break;
						default:
							m_dataRate.ResetContent();
							for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_14)/sizeof(string));cpt++)
							{
								m_dataRate.AddString(DATA_RATE_ITEMS_14[cpt].c_str());
							}
							m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
							break;
						}

					}
					break;
				case V25BIS:
					if(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE) == SYN_SYN)
					{
						m_dataRate.ResetContent();
						for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_7)/sizeof(string));cpt++)
						{
							m_dataRate.AddString(DATA_RATE_ITEMS_7[cpt].c_str());
						}
						m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					}
					else
					{
						m_dataRate.ResetContent();
						for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_6)/sizeof(string));cpt++)
						{
							m_dataRate.AddString(DATA_RATE_ITEMS_6[cpt].c_str());
						}
						m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					}
					break;
				}
				break;
			case DIG5BIT:
				m_dataRate.ResetContent();
				for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_7)/sizeof(string));cpt++)
				{
					m_dataRate.AddString(DATA_RATE_ITEMS_7[cpt].c_str());
				}
				m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
				break;
			}
			break;
		//--------------Mise à jour du checkbox FEC--------------
		case IDC_CHECK_FEC:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL
				&& GetCurSelComboToValue(IDC_COMBO_TRANS_PROC) == V24
				&& GetCurSelComboToValue(IDC_COMBO_TRAFF_MODE) == HDX)
			{
				m_fec.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			}
			else
			{
				m_fec.EnableWindow(FALSE);
			}
			break;
		//--------------Mise à jour du checkbox Lead time--------------
		case IDC_EDIT_LEAD_TIME:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == LOS
				|| GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == HF)
			{
				m_leadTime.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			}
			else
			{
				m_leadTime.EnableWindow(FALSE);
			}
			break;
		//--------------Mise à jour du checkbox Antispoof--------------
		case IDC_CHECK_ANTISPOOF:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIG5BIT)
			{
				m_antispoof.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			}
			else
			{
				m_antispoof.EnableWindow(FALSE);
			}
			break;
		}//fin du switch IDC
	}
	//-----------------------------------------------------------------------------
	//-----                      VOICE CRYPTO                                 -----
	//-----------------------------------------------------------------------------
	else if(generalParameter.preset>=8 && generalParameter.preset<16) //
	{
		OutputDebugString("Dans : VOICE CRYPTO !\n");
		
		switch(composant)
		{
		
		//--------------Construction du combo transmission mode--------------
		case IDC_COMBO_TRANS_MODE:
			m_transMode.ResetContent();
			for(cpt=0;cpt<(sizeof(TRANSMISSION_MODES_VOICE_CRYPTO)/sizeof(string));cpt++)
			{
				m_transMode.AddString(TRANSMISSION_MODES_VOICE_CRYPTO[cpt].c_str());
			}
			m_transMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			break;
		//--------------Construction du combo transmission procédure--------------
		case IDC_COMBO_TRANS_PROC:
			switch(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE))
			{
			case HF:
				m_transProc.ResetContent();
				for(cpt=0;cpt<(sizeof(TRANSMISSION_PROCEDURES_VOICE_CRYPTO_HF)/sizeof(string));cpt++)
				{
					m_transProc.AddString(TRANSMISSION_PROCEDURES_VOICE_CRYPTO_HF[cpt].c_str());
				}
				m_transProc.EnableWindow(TRUE);
				break;
			case DIGITAL:
				m_transProc.ResetContent();
				for(cpt=0;cpt<(sizeof(TRANSMISSION_PROCEDURES_DATA_P_AND_VOICE_C_DIGITAL)/sizeof(string));cpt++)
				{
					m_transProc.AddString(TRANSMISSION_PROCEDURES_DATA_P_AND_VOICE_C_DIGITAL[cpt].c_str());
				}
				m_transProc.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
				break;
			case VUHFANA:
			case VUHFDIG:
				m_transProc.ResetContent();
				for(cpt=0;cpt<(sizeof(TRANSMISSION_PROCEDURES_VOICE_CRYPTO_VUHF)/sizeof(string));cpt++)
				{
					m_transProc.AddString(TRANSMISSION_PROCEDURES_VOICE_CRYPTO_VUHF[cpt].c_str());
				}
				m_transProc.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
				break;
			default:
				m_transProc.EnableWindow(FALSE);
				break;
			}
			break;
		//--------------Construction du combo traffic mode--------------
		case IDC_COMBO_TRAFF_MODE:
			switch(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE))
			{
			case DIGITAL:
				m_traffMode.ResetContent();
				for(cpt=0;cpt<(sizeof(TRAFFIC_MODES_VOICE_CRYPTO_DIGITAL)/sizeof(string));cpt++)
				{
					m_traffMode.AddString(TRAFFIC_MODES_VOICE_CRYPTO_DIGITAL[cpt].c_str());
				}
				m_traffMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
				break;
			case VUHFANA:
			case VUHFDIG:
				m_traffMode.ResetContent();
				for(cpt=0;cpt<(sizeof(TRAFFIC_MODES_VOICE_CRYPTO_VUHF)/sizeof(string));cpt++)
				{
					m_traffMode.AddString(TRAFFIC_MODES_VOICE_CRYPTO_VUHF[cpt].c_str());
				}
				m_traffMode.EnableWindow(TRUE);
				break;
			default:
				m_traffMode.EnableWindow(FALSE);
				break;
			}
			break;
		//--------------Construction du combo sync mode--------------
		case IDC_COMBO_SYNCHRO_MODE:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				m_synchroMode.ResetContent();
				m_synchroMode.AddString(SYNC_MODES_SHORT[SYN_SYN].c_str());
				m_synchroMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			}
			else
			{
				m_synchroMode.EnableWindow(FALSE);
			}
			break;
		//--------------Construction du combo output--------------
		case IDC_COMBO_OUTPUT_SEL:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == VUHFDIG)
			{
				m_outputSel.ResetContent();
				for(cpt=0;cpt<NB_OUTPUT_SELECT;cpt++)
				{
					m_outputSel.AddString(OUTPUT_SELECT[cpt].c_str());
				}
				m_outputSel.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			}
			else
				m_outputSel.EnableWindow(FALSE);
			break;
		//--------------Construction du combo clock mode--------------
		case IDC_COMBO_CLOCK_MODE:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				m_clockMode.ResetContent();
				for(cpt=0;cpt<NB_CLOCK_MODES;cpt++)
				{
					m_clockMode.AddString(CLOCK_MODES[cpt].c_str());
				}
				m_clockMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			}
			else
				m_clockMode.EnableWindow(FALSE);
			break;
		//--------------Construction du combo number of data bits--------------
		case IDC_COMBO_NUM_DATA_BIT:
			m_numDataBit.EnableWindow(FALSE);
			break;
		//--------------Construction du combo parity--------------
		case IDC_COMBO_PARITY:
			m_parity.EnableWindow(FALSE);
			break;
		//--------------Construction du combo number of stop bits--------------
		case IDC_COMBO_NUM_STOP_BIT:
			m_numStopBit.EnableWindow(FALSE);
			break;
		//--------------Construction du combo data rate--------------
		case IDC_COMBO_DATA_RATE:
			m_dataRate.EnableWindow(FALSE);
			break;
		//--------------Mise à jour du checkbox FEC--------------
		case IDC_CHECK_FEC:
			m_fec.EnableWindow(FALSE);
			break;
		//--------------Mise à jour du checkbox Lead time--------------
		case IDC_EDIT_LEAD_TIME:
			switch(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE))
			{
			case DIGITAL:
			case LFDIGI:
				m_leadTime.EnableWindow(FALSE);
				break;
			default:
				m_leadTime.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
				break;
			}
			break;
		//--------------Mise à jour du checkbox Antispoof--------------
		case IDC_CHECK_ANTISPOOF:
			m_antispoof.EnableWindow(FALSE);
			break;
		
		}//fin du switch IDC
	}
	//-----------------------------------------------------------------------------
	//-----                      DATA PLAIN                                   -----
	//-----------------------------------------------------------------------------
	else if(generalParameter.preset>=16 && generalParameter.preset<24)
	{
		switch(composant)
		{
		//--------------Construction du combo transmission mode--------------
		case IDC_COMBO_TRANS_MODE:
			m_transMode.ResetContent();
			for(cpt=0;cpt<(sizeof(TRANSMISSION_MODES_DATA_PLAIN)/sizeof(string));cpt++)
			{
				m_transMode.AddString(TRANSMISSION_MODES_DATA_PLAIN[cpt].c_str());
			}
			m_transMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			break;
		//--------------Construction du combo transmission procédure--------------
		case IDC_COMBO_TRANS_PROC:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				m_transProc.ResetContent();
				for(cpt=0;cpt<(sizeof(TRANSMISSION_PROCEDURES_DATA_P_AND_VOICE_C_DIGITAL)/sizeof(string));cpt++)
				{
					m_transProc.AddString(TRANSMISSION_PROCEDURES_DATA_P_AND_VOICE_C_DIGITAL[cpt].c_str());
				}
				m_transProc.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			}
			else
				m_transProc.EnableWindow(FALSE);
			break;
		//--------------Construction du combo traffic mode--------------
		case IDC_COMBO_TRAFF_MODE:
			m_traffMode.EnableWindow(FALSE);
			break;
		//--------------Construction du combo sync mode--------------
		case IDC_COMBO_SYNCHRO_MODE:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				m_synchroMode.ResetContent();
				for(cpt=0;cpt<NB_SYNC_MODES;cpt++)
				{
					m_synchroMode.AddString(SYNC_MODES_SHORT[cpt].c_str());
				}
				m_synchroMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			}
			else
				m_synchroMode.EnableWindow(FALSE);
			break;
		//--------------Construction du combo output--------------
		case IDC_COMBO_OUTPUT_SEL:
			m_outputSel.EnableWindow(FALSE);
			break;
		//--------------Construction du combo clock mode--------------
		case IDC_COMBO_CLOCK_MODE:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				switch(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE))
				{
				case SYN_SYN:
				case ASY_SYN:
					m_clockMode.ResetContent();
					for(cpt=0;cpt<NB_CLOCK_MODES;cpt++)
					{
						m_clockMode.AddString(CLOCK_MODES[cpt].c_str());
					}
					m_clockMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				default:
					m_clockMode.EnableWindow(FALSE);
				}
			}
			else
			{
				m_clockMode.EnableWindow(FALSE);
			}
			break;
		//--------------Construction du combo number of data bits--------------
		case IDC_COMBO_NUM_DATA_BIT:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				switch(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE))
				{
				case ASY_SYN:
				case ASY_ASY:
					m_numDataBit.ResetContent();
					m_numDataBit.AddString(NUMBERS_OF_DATA_BITS_SHORT[BITS_7].c_str());
					m_numDataBit.AddString(NUMBERS_OF_DATA_BITS_SHORT[BITS_8].c_str());
					m_numDataBit.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				default:
					m_numDataBit.EnableWindow(FALSE);
				}
			}
			else
				m_numDataBit.EnableWindow(FALSE);
			break;
		//--------------Construction du combo parity--------------
		case IDC_COMBO_PARITY:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				switch(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE))
				{
				case ASY_SYN:
				case ASY_ASY:
					m_parity.ResetContent();
					for(cpt=0;cpt<NB_PARITY_MODE;cpt++)
					{
						m_parity.AddString(PARITY_MODE[cpt].c_str());
					}
					m_parity.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				default:
					m_parity.EnableWindow(FALSE);
				}
			}
			else
				m_parity.EnableWindow(FALSE);
			break;
		//--------------Construction du combo number of stop bits--------------
		case IDC_COMBO_NUM_STOP_BIT:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				switch(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE))
				{
				case ASY_SYN:
					m_numStopBit.ResetContent();
					m_numStopBit.AddString(NUMBERS_OF_STOP_BITS_SHORT[BITS_2].c_str());
					m_numStopBit.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				case ASY_ASY:
					m_numStopBit.ResetContent();
					for(cpt=0;cpt<NB_NUMBERS_OF_STOP_BITS;cpt++)
					{
						m_numStopBit.AddString(NUMBERS_OF_STOP_BITS_SHORT[cpt].c_str());
					}
					m_numStopBit.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				default:
					m_numStopBit.EnableWindow(FALSE);
				}
			}
			else
				m_numStopBit.EnableWindow(FALSE);
			break;
		//--------------Construction du combo data rate--------------
		case IDC_COMBO_DATA_RATE:
			if(GetCurSelComboToValue(IDC_COMBO_TRANS_MODE) == DIGITAL)
			{
				switch(GetCurSelComboToValue(IDC_COMBO_SYNCHRO_MODE))
				{
				case ASY_SYN:
					m_dataRate.ResetContent();
					for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_9)/sizeof(string));cpt++)
					{
						m_dataRate.AddString(DATA_RATE_ITEMS_9[cpt].c_str());
					}
					m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				case ASY_ASY:
					m_dataRate.ResetContent();
					for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_10)/sizeof(string));cpt++)
					{
						m_dataRate.AddString(DATA_RATE_ITEMS_10[cpt].c_str());
					}
					m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
					break;
				default:
					m_dataRate.ResetContent();
					for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_14)/sizeof(string));cpt++)
					{
						m_dataRate.AddString(DATA_RATE_ITEMS_14[cpt].c_str());
					}
					m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
				}
			}
			else
			{
				m_dataRate.ResetContent();
				for(cpt=0;cpt<(sizeof(DATA_RATE_ITEMS_7)/sizeof(string));cpt++)
				{
					m_dataRate.AddString(DATA_RATE_ITEMS_7[cpt].c_str());
				}
				m_dataRate.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			}
			break;
		//--------------Mise à jour du checkbox FEC--------------
		case IDC_CHECK_FEC:
			m_fec.EnableWindow(FALSE);
			break;
		//--------------Mise à jour du checkbox Lead time--------------
		case IDC_EDIT_LEAD_TIME:
			m_leadTime.EnableWindow(FALSE);
			break;
		//--------------Mise à jour du checkbox Antispoof--------------
		case IDC_CHECK_ANTISPOOF:
			m_antispoof.EnableWindow(FALSE);
			break;
		}//fin du switch IDC
	}
	//-----------------------------------------------------------------------------
	//-----                      VOICE PLAIN                                  -----
	//-----------------------------------------------------------------------------
	else if(generalParameter.preset>=24 && generalParameter.preset<32)
	{
		switch(composant)
		{
		//--------------Construction du combo transmission mode--------------
		case IDC_COMBO_TRANS_MODE:
			m_transMode.ResetContent();
			for(cpt=0;cpt<(sizeof(TRANSMISSION_MODES_VOICE_PLAIN)/sizeof(string));cpt++)
			{
				m_transMode.AddString(TRANSMISSION_MODES_VOICE_PLAIN[cpt].c_str());
			}
			m_transMode.EnableWindow(TRUE && eqp->GetOperatingStatus() == OFFLINE);
			break;
		//--------------Construction du combo transmission procédure--------------
		case IDC_COMBO_TRANS_PROC:
			m_transProc.EnableWindow(FALSE);
			break;
		//--------------Construction du combo traffic mode--------------
		case IDC_COMBO_TRAFF_MODE:
			m_traffMode.EnableWindow(FALSE);
			break;
		//--------------Construction du combo sync mode--------------
		case IDC_COMBO_SYNCHRO_MODE:
			m_synchroMode.EnableWindow(FALSE);
			break;
		//--------------Construction du combo output--------------
		case IDC_COMBO_OUTPUT_SEL:
			m_outputSel.EnableWindow(FALSE);
			break;
		//--------------Construction du combo clock mode--------------
		case IDC_COMBO_CLOCK_MODE:
			m_clockMode.EnableWindow(FALSE);
			break;
		//--------------Construction du combo number of data bits--------------
		case IDC_COMBO_NUM_DATA_BIT:
			m_numDataBit.EnableWindow(FALSE);
			break;
		//--------------Construction du combo parity--------------
		case IDC_COMBO_PARITY:
			m_parity.EnableWindow(FALSE);
			break;
		//--------------Construction du combo number of stop bits--------------
		case IDC_COMBO_NUM_STOP_BIT:
			m_numStopBit.EnableWindow(FALSE);
			break;
		//--------------Construction du combo data rate--------------
		case IDC_COMBO_DATA_RATE:
			m_dataRate.EnableWindow(FALSE);
			break;
		//--------------Mise à jour du checkbox FEC--------------
		case IDC_CHECK_FEC:
			m_fec.EnableWindow(FALSE);
			break;
		//--------------Mise à jour du checkbox Lead time--------------
		case IDC_EDIT_LEAD_TIME:
			m_leadTime.EnableWindow(FALSE);
			break;
		//--------------Mise à jour du checkbox Antispoof--------------
		case IDC_CHECK_ANTISPOOF:
			m_antispoof.EnableWindow(FALSE);
			break;
		}//fin du switch IDC
	}
}

int CDlgED42GeneralParameter::GetCurSelComboToValue(int composant)
{
	int cpt =0;
	CString value = "";
	switch(composant)
	{
	//--------------Récupération de la valeur du combo transmission mode --------------
	case IDC_COMBO_TRANS_MODE:
		m_transMode.GetLBText(m_transMode.GetCurSel(),value);

		for(cpt=0;cpt<NB_TRANSMISSION_MODES;cpt++)
			if(TRANSMISSION_MODES_SHORT[cpt].compare(value) == 0)
				return cpt;
		break;
	//--------------Récupération de la valeur du combo transmission procédure--------------
	case IDC_COMBO_TRANS_PROC:
		m_transProc.GetLBText(m_transProc.GetCurSel(),value);
		for(cpt=0;cpt<NB_TRANSMISSION_PROCEDURES;cpt++)
		{
			if(TRANSMISSION_PROCEDURES_SHORT[cpt].compare(value) == 0)
			{
				return cpt;
			}
		}
		break;
	//--------------Récupération de la valeur du combo traffic mode--------------
	case IDC_COMBO_TRAFF_MODE:
		m_traffMode.GetLBText(m_traffMode.GetCurSel(),value);
		for(cpt=0;cpt<NB_TRAFFIC_MODES;cpt++)
		{
			if(TRAFFIC_MODES[cpt].compare(value) == 0)
			{
				return cpt;
			}
		}
		break;
	//--------------Récupération de la valeur du combo sync mode--------------
	case IDC_COMBO_SYNCHRO_MODE:
		m_synchroMode.GetLBText(m_synchroMode.GetCurSel(),value);
		for(cpt=0;cpt<NB_SYNC_MODES;cpt++)
		{
			if(SYNC_MODES_SHORT[cpt].compare(value) == 0)
			{
				return cpt;
			}
		}
		break;
	//--------------Récupération de la valeur du combo output--------------
	case IDC_COMBO_OUTPUT_SEL:
		m_outputSel.GetLBText(m_outputSel.GetCurSel(),value);
		for(cpt=0;cpt<NB_OUTPUT_SELECT;cpt++)
		{
			if(OUTPUT_SELECT[cpt].compare(value) == 0)
			{
				return cpt;
			}
		}
		break;
	//--------------Récupération de la valeur du combo clock mode--------------
	case IDC_COMBO_CLOCK_MODE:
		m_clockMode.GetLBText(m_clockMode.GetCurSel(),value);
		for(cpt=0;cpt<NB_CLOCK_MODES;cpt++)
		{
			if(CLOCK_MODES[cpt].compare(value) == 0)
			{
				return cpt;
			}
		}
		break;
	//--------------Récupération de la valeur du combo number of data bits--------------
	case IDC_COMBO_NUM_DATA_BIT:
			m_numDataBit.GetLBText(m_numDataBit.GetCurSel(),value);
		for(cpt=0;cpt<NB_NUMBERS_OF_DATA_BITS;cpt++)
		{
			if(NUMBERS_OF_DATA_BITS_SHORT[cpt].compare(value) == 0)
			{
				return cpt;
			}
		}
		break;
	//--------------Récupération de la valeur du combo parity--------------
	case IDC_COMBO_PARITY:
		m_parity.GetLBText(m_parity.GetCurSel(),value);
		for(cpt=0;cpt<NB_PARITY_MODE;cpt++)
		{
			if(PARITY_MODE[cpt].compare(value) == 0)
			{
				return cpt;
			}
		}
		break;
	//--------------Récupération de la valeur du combo number of stop bits--------------
	case IDC_COMBO_NUM_STOP_BIT:
		m_numStopBit.GetLBText(m_numStopBit.GetCurSel(),value);
		for(cpt=0;cpt<NB_NUMBERS_OF_STOP_BITS;cpt++)
		{
			if(NUMBERS_OF_STOP_BITS[cpt].compare(value) == 0)
			{
				return cpt;
			}
		}
		break;
	//--------------Récupération de la valeur du combo data rate--------------
	case IDC_COMBO_DATA_RATE:
		m_dataRate.GetLBText(m_dataRate.GetCurSel(),value);
		for(cpt=0;cpt<NB_DATA_RATE;cpt++)
		{
			if(DATA_RATE_SHORT[cpt].compare(value) == 0)
			{
				return cpt;
			}
		}
		break;
	}//fin du switch IDC
	return 0;
}

void CDlgED42GeneralParameter::SetCurSelValueToCombo(int composant)
{
	int result =0;
	switch(composant)
	{
	//--------------Sélectionne de la valeur du combo transmission mode --------------
	case IDC_COMBO_TRANS_MODE:
		result = m_transMode.SelectString(0,TRANSMISSION_MODES_SHORT[generalParameter.transmission_mode].c_str());
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			m_transMode.SetCurSel(0);//Premier élément par défaut
		break;
	//--------------Sélectionne de la valeur du combo transmission procédure--------------
	case IDC_COMBO_TRANS_PROC:
		result = m_transProc.SelectString(0,TRANSMISSION_PROCEDURES_SHORT[generalParameter.transmission_procedure].c_str());
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			m_transProc.SetCurSel(0);//Premier élément par défaut
		break;
	//--------------Sélectionne de la valeur du combo traffic mode--------------
	case IDC_COMBO_TRAFF_MODE:
		result = m_traffMode.SelectString(0,TRAFFIC_MODES[generalParameter.trafic_mode].c_str());
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			m_traffMode.SetCurSel(0);//Premier élément par défaut
		break;
	//--------------Sélectionne de la valeur du combo sync mode--------------
	case IDC_COMBO_SYNCHRO_MODE:
		result = m_synchroMode.SelectString(0,SYNC_MODES_SHORT[generalParameter.synchronisation_mode].c_str());
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			m_synchroMode.SetCurSel(0);//Premier élément par défaut
		break;
	//--------------Sélectionne de la valeur du combo output--------------
	case IDC_COMBO_OUTPUT_SEL:
		result = m_outputSel.SelectString(0,OUTPUT_SELECT[generalParameter.output_selection].c_str());
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			m_outputSel.SetCurSel(0);//Premier élément par défaut
		break;
	//--------------Sélectionne de la valeur du combo clock mode--------------
	case IDC_COMBO_CLOCK_MODE:
		result = m_clockMode.SelectString(0,CLOCK_MODES[generalParameter.clock_mode].c_str());
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			m_clockMode.SetCurSel(0);//Premier élément par défaut
		break;
	//--------------Sélectionne de la valeur du combo number of data bits--------------
	case IDC_COMBO_NUM_DATA_BIT:
		result = m_numDataBit.SelectString(0,NUMBERS_OF_DATA_BITS_SHORT[generalParameter.nb_of_data_bite].c_str());
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			m_numDataBit.SetCurSel(0);//Premier élément par défaut
		break;
	//--------------Sélectionne de la valeur du combo parity--------------
	case IDC_COMBO_PARITY:
		result = m_parity.SelectString(0,PARITY_MODE[generalParameter.parity].c_str());
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			m_parity.SetCurSel(0);//Premier élément par défaut
		break;
	//--------------Sélectionne de la valeur du combo number of stop bits--------------
	case IDC_COMBO_NUM_STOP_BIT:
		result = m_numStopBit.SelectString(0,NUMBERS_OF_STOP_BITS[generalParameter.nb_of_stop_bite].c_str());
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			m_numStopBit.SetCurSel(0);//Premier élément par défaut
		break;
	//--------------Sélectionne de la valeur du combo data rate--------------
	case IDC_COMBO_DATA_RATE:
		result = m_dataRate.SelectString(0,DATA_RATE_SHORT[generalParameter.data_rate].c_str());
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			m_dataRate.SetCurSel(0);//Premier élément par défaut
		break;
	}//fin du switch IDC
}

//Modification de la vue en fonction de l'élément modifié.
void CDlgED42GeneralParameter::UpdateDialog(int value)
{
	char buffer[3] = "";

	switch(value)
	{
	case IDC_COMBO_TRANS_MODE:
		BuildComposant(IDC_COMBO_TRANS_PROC);
		SetCurSelValueToCombo(IDC_COMBO_TRANS_PROC);

	case IDC_COMBO_TRANS_PROC:
		BuildComposant(IDC_COMBO_TRAFF_MODE);
		SetCurSelValueToCombo(IDC_COMBO_TRAFF_MODE);

	case IDC_COMBO_TRAFF_MODE:
		BuildComposant(IDC_COMBO_SYNCHRO_MODE);
		SetCurSelValueToCombo(IDC_COMBO_SYNCHRO_MODE);

	case IDC_COMBO_SYNCHRO_MODE:
		BuildComposant(IDC_COMBO_CLOCK_MODE);
		SetCurSelValueToCombo(IDC_COMBO_CLOCK_MODE);

	case IDC_COMBO_CLOCK_MODE:
		BuildComposant(IDC_COMBO_PARITY);
		SetCurSelValueToCombo(IDC_COMBO_PARITY);

	case IDC_COMBO_PARITY:
		BuildComposant(IDC_COMBO_OUTPUT_SEL);
		SetCurSelValueToCombo(IDC_COMBO_OUTPUT_SEL);

	case IDC_COMBO_OUTPUT_SEL:
		BuildComposant(IDC_COMBO_NUM_STOP_BIT);
		SetCurSelValueToCombo(IDC_COMBO_NUM_STOP_BIT);

	case IDC_COMBO_NUM_STOP_BIT:
		BuildComposant(IDC_COMBO_NUM_DATA_BIT);
		SetCurSelValueToCombo(IDC_COMBO_NUM_DATA_BIT);

	case IDC_COMBO_NUM_DATA_BIT:
		BuildComposant(IDC_COMBO_DATA_RATE);
		SetCurSelValueToCombo(IDC_COMBO_DATA_RATE);

	default:
		BuildComposant(IDC_EDIT_LEAD_TIME);
		itoa(generalParameter.lead_time,buffer,10);
		//Mise à jour de la derniere valeur de leadTime afin de ne pas lever le flag de modification
		oldLead_time = buffer;
		m_leadTime.SetWindowText(buffer);

		BuildComposant(IDC_CHECK_FEC);
		m_fec.SetCheck(generalParameter.fec);

		BuildComposant(IDC_CHECK_ANTISPOOF);
		m_antispoof.SetCheck(generalParameter.antispoof);
	}
}
