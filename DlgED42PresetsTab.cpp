// DlgED42PresetsTab.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42PresetsTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42PresetsTab dialog


CDlgED42PresetsTab::CDlgED42PresetsTab(CEquipED42 * eqp,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42PresetsTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42PresetsTab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	this->eqp = eqp;
	ongletSelection = 0;

	//presetSelected = new string;
	presetSelected = "255";

}

CDlgED42PresetsTab::~CDlgED42PresetsTab()
{
	m_generalParameter->DestroyWindow();
	delete m_generalParameter;
	m_digitalDCE->DestroyWindow();
	delete m_digitalDCE;
	m_analogDCE->DestroyWindow();
	delete m_analogDCE;
	m_digitalDTE->DestroyWindow();
	delete m_digitalDTE;
	m_analogDTE->DestroyWindow();
	delete m_analogDTE;
	//delete presetSelected;
}

void CDlgED42PresetsTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42PresetsTab)
	DDX_Control(pDX, IDC_TAB, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42PresetsTab, CDialog)
	//{{AFX_MSG_MAP(CDlgED42PresetsTab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42PresetsTab message handlers

BOOL CDlgED42PresetsTab::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_tab.SetAutoSizePannel();

	m_generalParameter = new CDlgED42GeneralParameter(eqp);
	m_generalParameter->Create(CDlgED42GeneralParameter::IDD, &m_tab);
	m_tab.AddTab(m_generalParameter, "General Parameter", 0);

	m_digitalDCE = new CDlgED42DigitalDCE(eqp);
	m_digitalDCE->Create(CDlgED42DigitalDCE::IDD, &m_tab);
	m_tab.AddTab(m_digitalDCE, "Digital DCE", 1);

	m_analogDCE = new CDlgED42AnalogDCE(eqp);
	m_analogDCE->Create(CDlgED42AnalogDCE::IDD, &m_tab);
	m_tab.AddTab(m_analogDCE, "Analog DCE", 2);

	m_digitalDTE = new CDlgED42DigitalDTE(eqp);
	m_digitalDTE->Create(CDlgED42DigitalDTE::IDD, &m_tab);
	m_tab.AddTab(m_digitalDTE, "Digital DTE", 3);

	m_analogDTE = new CDlgED42AnalogDTE(eqp);
	m_analogDTE->Create(CDlgED42AnalogDTE::IDD, &m_tab);
	m_tab.AddTab(m_analogDTE, "Analog DTE", 4);


	return TRUE;
}

void CDlgED42PresetsTab::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(eqp->getModifVue())
	{
		int reponse = MessageBox("Voulez-vous sauvegarder les dernières modifications ?","Attention",MB_YESNO);
		if(reponse==IDYES)
		{
			switch(ongletSelection)
			{
			case 0:
				m_generalParameter->SaveData(presetSelected);
				break;
			case 1:
				m_digitalDCE->SaveData(presetSelected);
				break;
			case 2:
				m_analogDCE->SaveData(presetSelected);
				break;
			case 3:
				m_digitalDTE->SaveData(presetSelected);
				break;
			case 4:
				m_analogDTE->SaveData(presetSelected);
				break;
			}
		}
		//Remise à zero du flag
		eqp->setModifVue(FALSE);
	}
	else
		ongletSelection = m_tab.GetCurSel();

	switch(m_tab.GetCurSel())
	{
		case 0:
			m_generalParameter->LoadData(presetSelected);
			break;
		case 1:
			m_digitalDCE->LoadData(presetSelected);
			break;
		case 2:
			m_analogDCE->LoadData(presetSelected);
			break;
		case 3:
			m_digitalDTE->LoadData(presetSelected);
			break;
		case 4:
			m_analogDTE->LoadData(presetSelected);
			break;
	}

	*pResult = 0;
}

void CDlgED42PresetsTab::LoadData(string preset)
{
	presetSelected = preset;

	switch(m_tab.GetCurSel())
	{
		case 0:
			m_generalParameter->LoadData(presetSelected);
			break;
		case 1:
			m_digitalDCE->LoadData(presetSelected);
			break;
		case 2:
			m_analogDCE->LoadData(presetSelected);
			break;
		case 3:
			m_digitalDTE->LoadData(presetSelected);
			break;
		case 4:
			m_analogDTE->LoadData(presetSelected);
			break;
	}
}

void CDlgED42PresetsTab::SaveData()
{
	switch(m_tab.GetCurSel())
	{
		case 0:
			m_generalParameter->SaveData(presetSelected);
			break;
		case 1:
			m_digitalDCE->SaveData(presetSelected);
			break;
		case 2:
			m_analogDCE->SaveData(presetSelected);
			break;
		case 3:
			m_digitalDTE->SaveData(presetSelected);
			break;
		case 4:
			m_analogDTE->SaveData(presetSelected);
			break;
	}
}
