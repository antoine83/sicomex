// DlgED42KeyManagementTab.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42KeyManagementTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyManagementTab dialog


CDlgED42KeyManagementTab::CDlgED42KeyManagementTab(CEquipED42 * equip,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42KeyManagementTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42KeyManagementTab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_KeyDisplay	= NULL;
	m_KeyManagement	= NULL;
	m_KeyTag		= NULL;

	this->eqp = equip;

	ongletSelection = 0;
}

CDlgED42KeyManagementTab::~CDlgED42KeyManagementTab()
{
	m_KeyDisplay->DestroyWindow();
	delete m_KeyDisplay;
	m_KeyManagement->DestroyWindow();
	delete m_KeyManagement;
	m_KeyTag->DestroyWindow();
	delete m_KeyTag;
}

void CDlgED42KeyManagementTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42KeyManagementTab)
	DDX_Control(pDX, IDC_TAB, c_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42KeyManagementTab, CDialog)
	//{{AFX_MSG_MAP(CDlgED42KeyManagementTab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyManagementTab message handlers

BOOL CDlgED42KeyManagementTab::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	c_tab.SetAutoSizePannel();

	m_KeyDisplay = new CDlgED42KeyDisplay(eqp);
	m_KeyDisplay->Create(CDlgED42KeyDisplay::IDD, &c_tab);
	c_tab.AddTab(m_KeyDisplay, "Display", 0);

	m_KeyManagement = new CDlgED42KeyManagement(eqp);
	m_KeyManagement->Create(CDlgED42KeyManagement::IDD, &c_tab);
	c_tab.AddTab(m_KeyManagement, "Crypto", 1);

	m_KeyTag = new CDlgED42KeyTag(eqp);
	m_KeyTag->Create(CDlgED42KeyTag::IDD, &c_tab);
	c_tab.AddTab(m_KeyTag, "Tag", 2);
	
	return TRUE;   
}

void CDlgED42KeyManagementTab::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(eqp->getModifVue())
	{
		int reponse = MessageBox("Voulez-vous sauvegarder les dernières modifications ?","Attention",MB_YESNO);
		if(reponse==IDYES)
		{
			switch(ongletSelection)
			{
			case 0:
				break;
			case 1:
				m_KeyManagement->SaveData();
				break;
			case 2:
				m_KeyTag->SaveData();
				break;
			}
		}
		//Remise à zero du flag
		eqp->setModifVue(FALSE);
	}
	else
		ongletSelection = c_tab.GetCurSel();

	LoadData();
	
	*pResult = 0;
}

void CDlgED42KeyManagementTab::LoadData() 
{
	switch(c_tab.GetCurSel())
	{
	case 0:	
		m_KeyDisplay->LoadData();
		break;
	case 1:
		m_KeyManagement->LoadData();
		break;
	case 2:
		m_KeyTag->LoadData();
		break;
	}
}

void CDlgED42KeyManagementTab::SaveData() 
{
	switch(c_tab.GetCurSel())
	{
	case 0:			
		break;
	case 1:
		m_KeyManagement->SaveData();
		break;
	case 2:
		m_KeyTag->SaveData();
		break;
	} 
}
