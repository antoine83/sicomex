// DlgTRC1752_MOD_PROG_INTF.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_INTF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF dialog


CDlgTRC1752_MOD_PROG_INTF::CDlgTRC1752_MOD_PROG_INTF(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_INTF::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_INTF)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_ModProgIntfLias	= NULL;
	m_ModProgIntfBf		= NULL;
	m_ModProgIntfTc		= NULL;
	m_ModProgIntfAss	= NULL;
	m_ModProgIntfPil	= NULL;

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_INTF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_INTF)
	DDX_Control(pDX, IDC_MOD_PROG, m_ModProgTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_INTF, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_INTF)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MOD_PROG, OnSelchangeModProg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF message handlers

BOOL CDlgTRC1752_MOD_PROG_INTF::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ModProgTab.SetAutoSizePannel();

	m_ModProgIntfAss = new CDlgTRC1752_MOD_PROG_INTF_ASS(eqp);
	m_ModProgIntfAss->Create(CDlgTRC1752_MOD_PROG_INTF_ASS::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgIntfAss, "Association", 0);

	m_ModProgIntfLias = new CDlgTRC1752_MOD_PROG_INTF_LIAS(eqp);
	m_ModProgIntfLias->Create(CDlgTRC1752_MOD_PROG_INTF_LIAS::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgIntfLias, "Liaisons Séries Données", 1);

	m_ModProgIntfTc = new CDlgTRC1752_MOD_PROG_INTF_TC(eqp);
	m_ModProgIntfTc->Create(CDlgTRC1752_MOD_PROG_INTF_TC::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgIntfTc, "Interface de Télécommande", 2);

	m_ModProgIntfPil = new CDlgTRC1752_MOD_PROG_INTF_PIL(eqp);
	m_ModProgIntfPil->Create(CDlgTRC1752_MOD_PROG_INTF_PIL::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgIntfPil, "Pilote", 3);

	m_ModProgIntfBf = new CDlgTRC1752_MOD_PROG_INTF_BF(eqp);
	m_ModProgIntfBf->Create(CDlgTRC1752_MOD_PROG_INTF_BF::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgIntfBf, "Interfaces BF", 4);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTRC1752_MOD_PROG_INTF::OnSelchangeModProg(NMHDR* pNMHDR, LRESULT* pResult)
{
	eqp->SetModif(false);

	switch(m_ModProgTab.GetCurSel())
	{
		case 0:									// Onglet "Association"
			m_ModProgIntfAss->MiseJourListeInterfaceTd();
			break;
		case 1:									// Onglet "Liaison Séries Données"
			m_ModProgIntfLias->marcheTimer();
			break;
		case 2:									// Onglet "Interface de Télécommande"
			m_ModProgIntfTc->miseajourInterfaceTC();
			m_ModProgIntfTc->marcheTimer();
			break;
		case 4:									// Onglet "Interface BF"
			m_ModProgIntfBf->MiseJourListeInterfaceBf();
			m_ModProgIntfBf->marcheTimer();
			break;
	}


	*pResult = 0;
}
