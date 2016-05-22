// DlgTRC1752_MOD_PROG_STA.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"

#include "DlgTRC1752_MOD_PROG_STA.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA dialog


CDlgTRC1752_MOD_PROG_STA::CDlgTRC1752_MOD_PROG_STA(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_STA::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_STA)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	this->eqp = equip;
	quadrivoie = true;
}


void CDlgTRC1752_MOD_PROG_STA::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_STA)
	DDX_Control(pDX, IDC_PROG_STA, m_ProgStaTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_STA, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_STA)
	ON_WM_TIMER()
	ON_NOTIFY(TCN_SELCHANGE, IDC_PROG_STA, OnSelchangeProgSta)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA message handlers

BOOL CDlgTRC1752_MOD_PROG_STA::OnInitDialog()
{
	CDialog::OnInitDialog();

	//	Armement du timer
	SetTimer(1,1000,NULL);

    m_ProgStaTab.SetAutoSizePannel();

	m_ModProgStaA1 = new CDlgTRC1752_MOD_PROG_STA_A1(eqp);
	m_ModProgStaA1->Create(CDlgTRC1752_MOD_PROG_STA_A1::IDD, &m_ProgStaTab);
	m_ProgStaTab.AddTab(m_ModProgStaA1, "A1", 0);

	m_ModProgStaA2 = new CDlgTRC1752_MOD_PROG_STA_A2(eqp);
	m_ModProgStaA2->Create(CDlgTRC1752_MOD_PROG_STA_A2::IDD, &m_ProgStaTab);
	m_ProgStaTab.AddTab(m_ModProgStaA2, "A2", 1);

	m_ModProgStaB1 = new CDlgTRC1752_MOD_PROG_STA_B1(eqp);
	m_ModProgStaB1->Create(CDlgTRC1752_MOD_PROG_STA_B1::IDD, &m_ProgStaTab);
	m_ProgStaTab.AddTab(m_ModProgStaB1, "B1", 2);

	m_ModProgStaB2 = new CDlgTRC1752_MOD_PROG_STA_B2(eqp);
	m_ModProgStaB2->Create(CDlgTRC1752_MOD_PROG_STA_B2::IDD, &m_ProgStaTab);
	m_ProgStaTab.AddTab(m_ModProgStaB2, "B2", 3);

	m_ModProgStaTst = new CDlgTRC1752_MOD_PROG_STA_TST(eqp);
	m_ModProgStaTst->Create(CDlgTRC1752_MOD_PROG_STA_TST::IDD, &m_ProgStaTab);
	m_ProgStaTab.AddTab(m_ModProgStaTst, "Menu Test", 4);

	return TRUE;
}

void CDlgTRC1752_MOD_PROG_STA::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);


	//********************************
	m_ProgStaTab.EnableTab(0, !eqp->GetTest("A1"));
	m_ProgStaTab.EnableTab(1, !eqp->GetTest("A2"));
	m_ProgStaTab.EnableTab(2, eqp->GetQuadrivoie() && !eqp->GetTest("B1"));
	m_ProgStaTab.EnableTab(3, eqp->GetQuadrivoie() && !eqp->GetTest("B2"));



	if (eqp->Actif() == FALSE && eqp->GetQuadrivoie() != quadrivoie)
	{
		UpdateData(TRUE);

		quadrivoie = eqp->GetQuadrivoie();

		if (quadrivoie == true)
		{
			//m_ProgStaTab.EnableTab(2, TRUE);
			//m_ProgStaTab.EnableTab(3, TRUE);
		} else {
			m_ProgStaTab.EnableTab(2, FALSE);
			m_ProgStaTab.EnableTab(3, FALSE);
			if ((m_ProgStaTab.GetCurSel() == 2) || (m_ProgStaTab.GetCurSel() == 3))
				m_ProgStaTab.SelectTab(0);
		}

		UpdateData(FALSE);
	}

}

void CDlgTRC1752_MOD_PROG_STA::OnSelchangeProgSta(NMHDR* pNMHDR, LRESULT* pResult)
{
	eqp->SetModif(false);

	switch(m_ProgStaTab.GetCurSel())
	{
	case 0:				// Voie A1
		m_ModProgStaA1->StartTimer();
		m_ModProgStaA1->MiseJourListeInterfaceTd();
		m_ModProgStaA2->StopTimer();
		m_ModProgStaB1->StopTimer();
		m_ModProgStaB2->StopTimer();
		break;
	case 1:				// Voie A2
		m_ModProgStaA1->StopTimer();
		m_ModProgStaA2->StartTimer();
		m_ModProgStaA2->MiseJourListeInterfaceTd();
		m_ModProgStaB1->StopTimer();
		m_ModProgStaB2->StopTimer();
		break;
	case 2:				// Voie B1
		m_ModProgStaA1->StopTimer();
		m_ModProgStaA2->StopTimer();
		m_ModProgStaB1->StartTimer();
		m_ModProgStaB1->MiseJourListeInterfaceTd();
		m_ModProgStaB2->StopTimer();
		break;
	case 3:				// Voie B2
		m_ModProgStaA1->StopTimer();
		m_ModProgStaA2->StopTimer();
		m_ModProgStaB1->StopTimer();
		m_ModProgStaB2->StartTimer();
		m_ModProgStaB2->MiseJourListeInterfaceTd();
		break;
	default:
		m_ModProgStaA1->StopTimer();
		m_ModProgStaA2->StopTimer();
		m_ModProgStaB1->StopTimer();
		m_ModProgStaB2->StopTimer();
		break;
	}

	*pResult = 0;
}
