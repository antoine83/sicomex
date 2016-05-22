// DlgTRC1752_MOD_CONF.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_CONF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF dialog


CDlgTRC1752_MOD_CONF::CDlgTRC1752_MOD_CONF(CEquipM1752 * equip, CWnd* pParent)
	: CDialog(CDlgTRC1752_MOD_CONF::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_CONF)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_ModConfEnv	= NULL;
	m_ModConfStst	= NULL;
	m_ModConfAle	= NULL;
	m_ModConfRdo	= NULL;
	m_ModConfCnf	= NULL;
	m_ModConfArq	= NULL;

	this->eqp = equip;
}


void CDlgTRC1752_MOD_CONF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_CONF)
	DDX_Control(pDX, IDC_MOD_PROG, m_ModConfTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_CONF, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_CONF)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MOD_PROG, OnSelchangeModProg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF message handlers

BOOL CDlgTRC1752_MOD_CONF::OnInitDialog()
{
	CDialog::OnInitDialog();

    m_ModConfTab.SetAutoSizePannel();

	m_ModConfEnv = new CDlgTRC1752_MOD_CONF_ENV(eqp);
	m_ModConfEnv->Create(CDlgTRC1752_MOD_CONF_ENV::IDD, &m_ModConfTab);
	m_ModConfTab.AddTab(m_ModConfEnv, "Environnement", 0);

	m_ModConfStst = new CDlgTRC1752_MOD_CONF_STST(eqp);
	m_ModConfStst->Create(CDlgTRC1752_MOD_CONF_STST::IDD, &m_ModConfTab);
	m_ModConfTab.AddTab(m_ModConfStst, "Paramètres Test", 1);

	m_ModConfCnf = new CDlgTRC1752_MOD_CONF_CONF(eqp);
	m_ModConfCnf->Create(CDlgTRC1752_MOD_CONF_CONF::IDD, &m_ModConfTab);
	m_ModConfTab.AddTab(m_ModConfCnf, "Paramètres Modem", 2);

	m_ModConfAle = new CDlgTRC1752_MOD_CONF_ALE(eqp);
	m_ModConfAle->Create(CDlgTRC1752_MOD_CONF_ALE::IDD, &m_ModConfTab);
	m_ModConfTab.AddTab(m_ModConfAle, "Paramètres ALE", 3);

	m_ModConfRdo = new CDlgTRC1752_MOD_CONF_RDO(eqp);
	m_ModConfRdo->Create(CDlgTRC1752_MOD_CONF_RDO::IDD, &m_ModConfTab);
	m_ModConfTab.AddTab(m_ModConfRdo, "Paramètres Radio", 4);

	m_ModConfArq = new CDlgTRC1752_MOD_CONF_ARQ(eqp);
	m_ModConfArq->Create(CDlgTRC1752_MOD_CONF_ARQ::IDD, &m_ModConfTab);
	m_ModConfTab.AddTab(m_ModConfArq, "PC_ARQ", 5);


	return TRUE;
}

void CDlgTRC1752_MOD_CONF::OnSelchangeModProg(NMHDR* pNMHDR, LRESULT* pResult)
{
	eqp->SetModif(false);

	switch(m_ModConfTab.GetCurSel())
	{
		case 0:
			m_ModConfEnv->LoadData();
			break;
		case 1:
			m_ModConfStst->LoadData();
			break;
		case 2:
			m_ModConfCnf->LoadData();
			break;
		case 3:
			m_ModConfAle->LoadData();
			break;
		case 4:
			m_ModConfRdo->LoadData();
			break;
		case 5:
			m_ModConfArq->LoadData();
			break;
		default:
			break;
	}

	*pResult = 0;
}
