// DlgED42SecurityTab.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42SecurityTab.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42SecurityTab dialog


CDlgED42SecurityTab::CDlgED42SecurityTab(CEquipED42 * equip,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42SecurityTab::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42SecurityTab)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	this->eqp = equip;

	ongletSelection = 0;
}

CDlgED42SecurityTab::~CDlgED42SecurityTab()
{
	m_Password->DestroyWindow();
	delete m_Password;
	m_CikSystem->DestroyWindow();
	delete m_CikSystem;
}

void CDlgED42SecurityTab::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42SecurityTab)
	DDX_Control(pDX, IDC_TAB, c_tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42SecurityTab, CDialog)
	//{{AFX_MSG_MAP(CDlgED42SecurityTab)
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42SecurityTab message handlers

BOOL CDlgED42SecurityTab::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	c_tab.SetAutoSizePannel();

	m_Password = new CDlgED42Password(eqp);
	m_Password->Create(CDlgED42Password::IDD, &c_tab);
	c_tab.AddTab(m_Password, "Password", 0);

	m_CikSystem = new CDlgED42CikSystem(eqp);
	m_CikSystem->Create(CDlgED42CikSystem::IDD, &c_tab);
	c_tab.AddTab(m_CikSystem, "CIK/KEK System", 1);
	
	return TRUE;  
}

void CDlgED42SecurityTab::LoadData() 
{
	switch(c_tab.GetCurSel())
	{
	case 0:	
		m_Password->LoadData();
		break;
	case 1:
		m_CikSystem->LoadData();
		break;
	}
}

void CDlgED42SecurityTab::SaveData() 
{
	switch(c_tab.GetCurSel())
	{
	case 0:			
		m_Password->SaveData();
		break;
	case 1:
		break;
	} 
}

void CDlgED42SecurityTab::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult) 
{
	if(eqp->getModifVue())
	{
		int reponse = MessageBox("Voulez-vous sauvegarder les dernières modifications ?","Attention",MB_YESNO);
		if(reponse==IDYES)
		{
			switch(ongletSelection)
			{
			case 0:
				m_Password->SaveData();
				break;
			case 1:
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
