// DlgED42Tab.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42Tab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42Tab dialog


CDlgED42Tab::CDlgED42Tab(CEquipED42 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42Tab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42Tab)
	//}}AFX_DATA_INIT

	m_Info				= NULL;
	m_Presets			= NULL;
	m_KeyManagementTab	= NULL;
	m_SecurityTab		= NULL;
	m_Parameters		= NULL;

	this->eqp = equip;

	ongletSelection = 0;
}

CDlgED42Tab::~CDlgED42Tab()
{
	m_Info->DestroyWindow();
	delete m_Info;
	m_Presets->DestroyWindow();
	delete m_Presets;
	m_KeyManagementTab->DestroyWindow();
	delete m_KeyManagementTab;
	m_SecurityTab->DestroyWindow();
	delete m_SecurityTab;
	m_Parameters->DestroyWindow();
	delete m_Parameters;
}

void CDlgED42Tab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42Tab)
	DDX_Control(pDX, IDC_TAB, m_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42Tab, CDialog)
	//{{AFX_MSG_MAP(CDlgED42Tab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42Tab message handlers
BOOL CDlgED42Tab::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_tab.SetAutoSizePannel();

	m_Info = new DlgED42Info(eqp);
	m_Info->Create(DlgED42Info::IDD, &m_tab);
	m_tab.AddTab(m_Info, "Status", 0);

	m_Presets = new CDlgED42Presets(eqp);
	m_Presets->Create(CDlgED42Presets::IDD, &m_tab);
	m_tab.AddTab(m_Presets, "Operating Parameters", 1);

	m_KeyManagementTab = new CDlgED42KeyManagementTab(eqp);
	m_KeyManagementTab->Create(CDlgED42KeyManagementTab::IDD, &m_tab);
	m_tab.AddTab(m_KeyManagementTab, "Key Management", 2);

	m_SecurityTab = new CDlgED42SecurityTab(eqp);
	m_SecurityTab->Create(CDlgED42SecurityTab::IDD, &m_tab);
	m_tab.AddTab(m_SecurityTab, "Security", 3);

	m_Parameters = new CDlgED42Parametres(eqp);
	m_Parameters->Create(CDlgED42Parametres::IDD, &m_tab);
	m_tab.AddTab(m_Parameters, "Basic Parameters", 4);


	return TRUE;
}

void CDlgED42Tab::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(eqp->getModifVue())
	{
		int reponse = IDYES;

		if(eqp->GetRemoteTC() == LOCAL_TC)
			reponse = MessageBox("Voulez-vous sauvegarder les dernières modifications ?","Attention",MB_YESNO);

		if(reponse==IDYES)
		{
			switch(ongletSelection)
			{
			case 0:
				break;
			case 1:
				m_Presets->SaveData();
				break;
			case 2:
				m_KeyManagementTab->SaveData();
				break;

			case 3:
				m_SecurityTab->SaveData();
				break;
			}
		}
		//Remise à zero du flag
		eqp->setModifVue(FALSE);
	}
	else
		ongletSelection = m_tab.GetCurSel();

	LoadData();

	*pResult = 0;
}

void CDlgED42Tab::LoadData()
{
	switch(m_tab.GetCurSel())
	{
		case 0:	//Info
			//m_Info->LoadData();
            m_Presets->m_presetTab->m_tab.SelectTab(0);
			m_KeyManagementTab->c_tab.SelectTab(0);
			m_SecurityTab->c_tab.SelectTab(0);
			break;
		case 1:	//Presets
			m_Presets->LoadData();
			m_KeyManagementTab->c_tab.SelectTab(0);
			m_SecurityTab->c_tab.SelectTab(0);

			break;

		case 2:	//KeyManagementTab
			m_KeyManagementTab->LoadData();
			m_Presets->m_presetTab->m_tab.SelectTab(0);
			m_SecurityTab->c_tab.SelectTab(0);
			break;

		case 3:	//SecurityTab
			m_SecurityTab->LoadData();
			m_Presets->m_presetTab->m_tab.SelectTab(0);
			m_KeyManagementTab->c_tab.SelectTab(0);
			break;

		case 4:	//Parameters
			m_Parameters->LoadData();
			m_Presets->m_presetTab->m_tab.SelectTab(0);
			m_KeyManagementTab->c_tab.SelectTab(0);
			m_SecurityTab->c_tab.SelectTab(0);
			break;
	}
}

void CDlgED42Tab::SaveData()
{
	switch(m_tab.GetCurSel())
	{
		case 0:
			//m_Info->SaveData();
			break;
		case 1:
			//Recherche si une valeur a changé
			if(eqp->getModifVue())
				m_Presets->SaveData();
			break;

		case 2:
			//Pas de vérification si on a déjà effectué une modification
			m_KeyManagementTab->SaveData();
			break;

		case 3:
			m_SecurityTab->SaveData();
			break;

		case 4:
			//m_Parameters->SaveData();
			break;
	}
	//Remise à zéro du flag qui permet de savoir si il y a eu une modification
	eqp->setModifVue(FALSE);
}
