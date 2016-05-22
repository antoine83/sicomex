// DlgED42ERRPANNE.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42ERRPANNE.h"
#include <windows.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgED42ERRPANNE dialog


DlgED42ERRPANNE::DlgED42ERRPANNE(CEquipED42* equip, CWnd* pParent)
	: CDialog(DlgED42ERRPANNE::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgED42ERRPANNE)
	//}}AFX_DATA_INIT
	this->equip = equip;
	ongletSelection = 0;
}

DlgED42ERRPANNE::~DlgED42ERRPANNE()
{
	m_Err->DestroyWindow();
	delete m_Err;
	m_Pannes->DestroyWindow();
	delete m_Pannes;
	m_Bit->DestroyWindow();
	delete m_Bit;
	m_statusErr->DestroyWindow();
	delete m_statusErr;
	
}

void DlgED42ERRPANNE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgED42ERRPANNE)
	DDX_Control(pDX, IDC_ED42_TAB_ERR_PANNE, m_ErrPanneTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgED42ERRPANNE, CDialog)
	//{{AFX_MSG_MAP(DlgED42ERRPANNE)
	ON_NOTIFY(TCN_SELCHANGE, IDC_ED42_TAB_ERR_PANNE, OnSelchangeEd42TabErrPanne)
	ON_BN_CLICKED(ID_BUTTON_FERMER, OnButtonFermer)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgED42ERRPANNE message handlers

BOOL DlgED42ERRPANNE::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ErrPanneTab.SetAutoSizePannel();

	m_Err = new DlgED42ERR(equip);
	m_Err->Create(DlgED42ERR::IDD, &m_ErrPanneTab);
	m_ErrPanneTab.AddTab(m_Err, "Errors", 0);

	m_Pannes = new DlgED42Pannes(equip);
	m_Pannes->Create(DlgED42Pannes::IDD, &m_ErrPanneTab);
	m_ErrPanneTab.AddTab(m_Pannes, "Pannes", 1);

	m_Bit = new DlgED42Bit(equip);
	m_Bit->Create(DlgED42Bit::IDD, &m_ErrPanneTab);
	m_ErrPanneTab.AddTab(m_Bit, "Build-in (BIT)", 2);

	m_statusErr = new CDlgED42StatusERR(equip);
	m_statusErr->Create(CDlgED42StatusERR::IDD, &m_ErrPanneTab);
	m_ErrPanneTab.AddTab(m_statusErr, "Status Error", 3);

	return TRUE;
}

void DlgED42ERRPANNE::OnSelchangeEd42TabErrPanne(NMHDR* pNMHDR, LRESULT* pResult)
{
	if(equip->getModifErreurPanne())
	{
		int reponse = MessageBox("Voulez-vous sauvegarder les dernières modifications ?","Attention",MB_YESNO);
		if(reponse==IDYES)
		{
			switch(ongletSelection)
			{
			case 0:
				m_Err->SaveData();
				break;
			case 1:
				m_Pannes->SaveData();
				break;
			case 2:
				m_Bit->SaveData();
				break;
			case 3:
				m_statusErr->SaveData();
				break;
			}
		}
		//Remise à zero du flag
		equip->setModifErreurPanne(FALSE);
	}
	else
		ongletSelection = m_ErrPanneTab.GetCurSel();

	LoadData();

	*pResult = 0;
}

void DlgED42ERRPANNE::OnButtonFermer()
{
	if(equip->getModifErreurPanne())
	{
		int reponse = MessageBox("Voulez-vous sauvegarder les dernières modifications ?","Attention",MB_YESNO);
		if(reponse==IDYES)
		{
			switch(ongletSelection)
			{
				case 0:
					m_Err->SaveData();
					break;
				case 1:
					m_Pannes->SaveData();
					break;
				case 2:
					m_Bit->SaveData();
					break;
				case 3:
					m_statusErr->SaveData();
					break;
			}
		}
		//Remise à zero du flag
		equip->setModifErreurPanne(FALSE);
	}

	CDialog::OnOK();
}

void DlgED42ERRPANNE::LoadData()
{
	switch(m_ErrPanneTab.GetCurSel())
	{
		case 0:
			m_Err->LoadData();
			break;
		case 1:
			m_Pannes->LoadData();
			break;
		case 2:
			m_Bit->LoadData();
			break;
		case 3:
			m_statusErr->LoadData();
			break;
	}
}
