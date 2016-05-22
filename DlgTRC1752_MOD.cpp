// DlgTRC1752_MOD.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD dialog


CDlgTRC1752_MOD::CDlgTRC1752_MOD(CEquipM1752 * equip, CWnd* pParent)
	: CDialog(CDlgTRC1752_MOD::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_ModConf	= NULL;
	m_ModOps	= NULL;
	m_ModProg	= NULL;

	this->eqp = equip;
}


void CDlgTRC1752_MOD::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD)
	DDX_Control(pDX, IDC_TAB, m_Tab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD)
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_TAB, OnSelchangeTab)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD message handlers

BOOL CDlgTRC1752_MOD::OnInitDialog()
{
	CDialog::OnInitDialog();

	//	Armement du timer
	SetTimer(1,1000,NULL);

    m_Tab.SetAutoSizePannel();

	m_ModOps = new CDlgTRC1752_MOD_OPS(eqp);
	m_ModOps->Create(CDlgTRC1752_MOD_OPS::IDD, &m_Tab);
	m_Tab.AddTab(m_ModOps, "Opérationnel", 0);

	m_ModProg = new CDlgTRC1752_MOD_PROG(eqp);
	m_ModProg->Create(CDlgTRC1752_MOD_PROG::IDD, &m_Tab);
	m_Tab.AddTab(m_ModProg, "Programmation", 1);

	m_ModConf = new CDlgTRC1752_MOD_CONF(eqp);
	m_ModConf->Create(CDlgTRC1752_MOD_CONF::IDD, &m_Tab);
	m_Tab.AddTab(m_ModConf, "Configuration", 2);

	return TRUE;
}

void CDlgTRC1752_MOD::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);



	if (this->eqp->Actif() == FALSE || this->eqp->IsEnTest() == TRUE)
	{
		if (m_Tab.GetCurSel() == 1)
		{
			UpdateData(TRUE);
			m_Tab.SelectTab(0);
			UpdateData(FALSE);
		}
	}

}

void CDlgTRC1752_MOD::OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult)
{
	eqp->SetModif(false);

	//Sélection de l'onglet "Opérationnel"
	switch(m_Tab.GetCurSel())
	{
	case 0:
	case 2:
		m_ModProg->m_ModProgSta->m_ProgStaTab.SelectTab(0);						// Prog_Station
		m_ModProg->m_ModProgConf->razChoixCanal();								// Prog_Configuration
		m_ModProg->m_ModProgConf->arretTimer();									// Arret du Timer Conf
		m_ModProg->m_ModProgAle->m_ModProgTab.SelectTab(0);						// Prog_ALE
		m_ModProg->m_ModProgIntf->m_ModProgIntfLias->razChoixConfiguration();	// Liaison Séries Données
		m_ModProg->m_ModProgIntf->m_ModProgIntfLias->arretTimer();				// Arret du Timer Lias
		m_ModProg->m_ModProgIntf->m_ModProgIntfBf->razChoixInterfaceBF();		// Interface BF
		m_ModProg->m_ModProgIntf->m_ModProgIntfBf->arretTimer();				// Arret du Timer BF
		m_ModProg->m_ModProgIntf->m_ModProgIntfTc->razChoixInterfaceTC();		// Interface TC
		m_ModProg->m_ModProgIntf->m_ModProgIntfTc->arretTimer();				// Arret du Timer TC
		m_ModProg->m_ModProgIntf->m_ModProgTab.SelectTab(0);					// Interface
		m_ModProg->m_ModProgTab.SelectTab(0);									// Programmation
		m_ModConf->m_ModConfTab.SelectTab(0);									// Configuration
		m_ModProg->m_ModProgIntf->m_ModProgIntfAss->razChoixDataLink();			// Interface Association

		m_ModProg->m_ModProgSta->m_ModProgStaA1->StopTimer();					// Station A1
		m_ModProg->m_ModProgSta->m_ModProgStaA2->StopTimer();					// Station A2
		m_ModProg->m_ModProgSta->m_ModProgStaB1->StopTimer();					// Station B1
		m_ModProg->m_ModProgSta->m_ModProgStaB2->StopTimer();					// Station B2

		m_ModProg->m_ModProgIntf->m_ModProgIntfAss->StopTimer();
		m_ModProg->m_ModProgTc->StopTimer();
		break;
	case 1:
		m_ModProg->m_ModProgSta->m_ModProgStaA1->StartTimer();					// Station A1
		m_ModProg->m_ModProgSta->m_ModProgStaA1->MiseJourListeInterfaceTd();
		break;
	}

	*pResult = 0;
}
