// DlgTRC1752_MOD_PROG_ALE.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_ALE.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE dialog


CDlgTRC1752_MOD_PROG_ALE::CDlgTRC1752_MOD_PROG_ALE(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_ALE::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_ALE)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_ModProgAleSys		= NULL;
	m_ModProgAleCall	= NULL;
	m_ModProgAleTab		= NULL;
	m_ModProgAleLp		= NULL;

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_ALE::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_ALE)
	DDX_Control(pDX, IDC_MOD_PROG, m_ModProgTab);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_ALE, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_ALE)
	ON_NOTIFY(TCN_SELCHANGE, IDC_MOD_PROG, OnSelchangeModProg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE message handlers

BOOL CDlgTRC1752_MOD_PROG_ALE::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ModProgTab.SetAutoSizePannel();

	m_ModProgAleSys = new CDlgTRC1752_MOD_PROG_ALE_SYS(eqp);
	m_ModProgAleSys->Create(CDlgTRC1752_MOD_PROG_ALE_SYS::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgAleSys, "SYSTEMPARAM", 0);

	m_ModProgAleCall = new CDlgTRC1752_MOD_PROG_ALE_CALL(eqp);
	m_ModProgAleCall->Create(CDlgTRC1752_MOD_PROG_ALE_CALL::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgAleCall, "CALLPARAM", 1);

	m_ModProgAleTab = new CDlgTRC1752_MOD_PROG_ALE_TAB(eqp);
	m_ModProgAleTab->Create(CDlgTRC1752_MOD_PROG_ALE_TAB::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgAleTab, "GEST_TABLE", 2);

	m_ModProgAleLp = new CDlgTRC1752_MOD_PROG_ALE_LP(eqp);
	m_ModProgAleLp->Create(CDlgTRC1752_MOD_PROG_ALE_LP::IDD, &m_ModProgTab);
	m_ModProgTab.AddTab(m_ModProgAleLp, "PROTECT_LIEN", 3);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTRC1752_MOD_PROG_ALE::OnSelchangeModProg(NMHDR* pNMHDR, LRESULT* pResult)
{
	eqp->SetModif(false);

	switch(m_ModProgTab.GetCurSel())
	{
		case 0:									//Onglet "SYSTEMPARAM"
			m_ModProgAleSys->marcheTimer();
			break;
		case 1:									//Onglet "CALLPARAM"
			m_ModProgAleCall->marcheTimer();
			break;
		case 2:									//Onglet "GEST_TABLE"
			//m_ModProgAleTab->marcheTimer();
			break;
		case 3:									//Onglet "PROTECT_LIEN"
			m_ModProgAleLp->Valide();
			m_ModProgAleLp->marcheTimer();
			break;
	}

	*pResult = 0;
}
