// DlgTRC1752_MOD_PROG_ALE_TAB.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_ALE_TAB.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_TAB dialog

/*TABLE_MGT = gestion des tables ALE*/


CDlgTRC1752_MOD_PROG_ALE_TAB::CDlgTRC1752_MOD_PROG_ALE_TAB(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_ALE_TAB::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_ALE_TAB)
	m_AleCanal = 0;
	m_AleTable = 0;
	m_AleAct = 0;
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_ALE_TAB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_ALE_TAB)
	DDX_Control(pDX, IDC_PROG_ALE_TAB_ACT, m_ChAleAct);
	DDX_Control(pDX, IDC_PROG_ALE_TAB_TABLE, m_ChAleTable);
	DDX_Control(pDX, IDC_PROG_ALE_TAB_CANAL, m_ChAleCanal);
	DDX_CBIndex(pDX, IDC_PROG_ALE_TAB_CANAL, m_AleCanal);
	DDX_CBIndex(pDX, IDC_PROG_ALE_TAB_TABLE, m_AleTable);
	DDX_CBIndex(pDX, IDC_PROG_ALE_TAB_ACT, m_AleAct);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_ALE_TAB, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_ALE_TAB)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_TAB message handlers

BOOL CDlgTRC1752_MOD_PROG_ALE_TAB::OnInitDialog()
{
	CDialog::OnInitDialog();

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTRC1752_MOD_PROG_ALE_TAB::Valide()
{

	CString channel, num;

	m_ChAleCanal.GetLBText(m_ChAleCanal.GetCurSel(), channel);

	if (eqp->GetChannelState((char *)LPCTSTR(channel)) == "ACTIVE")
	{
		AfxMessageBox("Action impossible quand la voie est en Active !");
		UpdateData(FALSE);
		return;
	}

	m_ChAleTable.GetLBText(m_ChAleTable.GetCurSel(), num);

	switch (m_ChAleAct.GetCurSel())
	{
		case 0 : // SEL
			eqp->SelectionMemoire((char*)LPCTSTR(channel), (char*)LPCTSTR(num));
			break;
		case 1: // SAV
			eqp->EcritureMemoire((char*)LPCTSTR(channel), (char*)LPCTSTR(num));
			break;
		case 2 : // ERA
			eqp->EffacementMemoire((char*)LPCTSTR(channel), (char*)LPCTSTR(num));
			break;
		default:
			break;
	}
}
