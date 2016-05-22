// DlgTRC1752_MOD_PROG.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"

#include "DlgTRC1752_MOD_PROG.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG dialog


CDlgTRC1752_MOD_PROG::CDlgTRC1752_MOD_PROG(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG::IDD, pParent)
{

	m_ModProgAle	= NULL;
	m_ModProgConf	= NULL;
    m_ModProgIntf	= NULL;
	m_ModProgSta	= NULL;
	m_ModProgStst	= NULL;
	m_ModProgTc		= NULL;

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG)
	DDX_Control(pDX, IDC_MOD_PROG, m_ModProgTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MOD_PROG, OnSelchangeModProg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG message handlers

BOOL CDlgTRC1752_MOD_PROG::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_ModProgTab.SetAutoSizePannel();

	m_ModProgSta = new CDlgTRC1752_MOD_PROG_STA(eqp);
	m_ModProgSta->Create(CDlgTRC1752_MOD_PROG_STA::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgSta, "Station", 0);

	m_ModProgConf = new CDlgTRC1752_MOD_PROG_CONF(eqp);
	m_ModProgConf->Create(CDlgTRC1752_MOD_PROG_CONF::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgConf, "Configurations", 1);

	m_ModProgAle = new CDlgTRC1752_MOD_PROG_ALE(eqp);
	m_ModProgAle->Create(CDlgTRC1752_MOD_PROG_ALE::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgAle, "ALE", 2);

	m_ModProgIntf = new CDlgTRC1752_MOD_PROG_INTF(eqp);
	m_ModProgIntf->Create(CDlgTRC1752_MOD_PROG_INTF::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgIntf, "Interfaces", 3);

	m_ModProgStst = new CDlgTRC1752_MOD_PROG_STST(eqp);
	m_ModProgStst->Create(CDlgTRC1752_MOD_PROG_STST::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgStst, "Autotest", 4);

	m_ModProgEnv = new CDlgTRC1752_MOD_PROG_ENV(eqp);
	m_ModProgEnv->Create(CDlgTRC1752_MOD_PROG_ENV::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgEnv, "Environnement", 5);

	m_ModProgTc = new CDlgTRC1752_MOD_PROG_TC(eqp);
	m_ModProgTc->Create(CDlgTRC1752_MOD_PROG_TC::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgTc, "Gestion Télécommandes", 6);

	return TRUE;
}


void CDlgTRC1752_MOD_PROG::OnSelchangeModProg(NMHDR* pNMHDR, LRESULT* pResult)
{
	eqp->SetModif(false);

	switch(m_ModProgTab.GetCurSel())
	{
		case 0:									// Onglet Station
			m_ModProgSta->m_ModProgStaA1->StartTimer();
			break;
		case 1:									// Onglet "Configurations"
			m_ModProgConf->razChoixCanal();
			m_ModProgConf->marcheTimer();
			m_ModProgConf->enleveMC();			// retire mc de la liste des conf si il est present
			m_ModProgSta->m_ModProgStaA1->StopTimer();
			m_ModProgSta->m_ModProgStaA2->StopTimer();
			m_ModProgSta->m_ModProgStaB1->StopTimer();
			m_ModProgSta->m_ModProgStaB2->StopTimer();
			break;
		case 2:									// Onglet "ALE"
			m_ModProgAle->m_ModProgAleSys->marcheTimer();
			m_ModProgSta->m_ModProgStaA1->StopTimer();
			m_ModProgSta->m_ModProgStaA2->StopTimer();
			m_ModProgSta->m_ModProgStaB1->StopTimer();
			m_ModProgSta->m_ModProgStaB2->StopTimer();
			break;
		case 3:									// Onglet Interfaces
			m_ModProgIntf->m_ModProgIntfAss->StartTimer();
			m_ModProgIntf->m_ModProgIntfAss->MiseJourListeInterfaceTd();
			break;
		case 4:									// Onglet Autotest
			m_ModProgStst->MiseJourListeCarte();
			break;
		case 5:									// Onglet Environement
			break;
		case 6:									// Onglet TCL
			m_ModProgTc->StartTimer();
		default:
			m_ModProgSta->m_ModProgStaA1->StopTimer();
			m_ModProgSta->m_ModProgStaA2->StopTimer();
			m_ModProgSta->m_ModProgStaB1->StopTimer();
			m_ModProgSta->m_ModProgStaB2->StopTimer();
			break;
	}

	*pResult = 0;
}
