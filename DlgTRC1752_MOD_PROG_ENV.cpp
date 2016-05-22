// DlgTRC1752_MOD_PROG_ENV.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_ENV.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ENV dialog


CDlgTRC1752_MOD_PROG_ENV::CDlgTRC1752_MOD_PROG_ENV(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_ENV::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_ENV)
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_ENV::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_ENV)
	DDX_Control(pDX, IDC_PROG_ENV_CH_LANGUES, m_ChLangue);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_ENV, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_ENV)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ENV message handlers

BOOL CDlgTRC1752_MOD_PROG_ENV::OnInitDialog()
{
	CDialog::OnInitDialog();

	//	Armement du timer
	SetTimer(1,1000,NULL);

	//Affichage de la Langue pae défaut
	m_ChLangue.SetCurSel(0);

	return TRUE;
}

void CDlgTRC1752_MOD_PROG_ENV::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	if (eqp->IsModif()) return;

	UpdateData(TRUE);

	string value;

	value = eqp->GetIdentity();
	SetDlgItemText(IDC_PROG_ID_MODEM, value.c_str());

	TBoard board;

	board = eqp->GetBoard1();

	//value = board.capabilities + " " + board.release + "." + board.number;
	value = board.capabilities + " " + board.number + "." + board.release;
	SetDlgItemText(IDC_PROG_ENV_VERSION_A, value.c_str());

	value = board.day + " " + board.month + " " + board.year;
	SetDlgItemText(IDC_PROG_ENV_DATE_A, value.c_str());

	board = eqp->GetBoard2();

	//value = board.capabilities + " " + board.release + "." + board.number;
	value = board.capabilities + " " + board.number + "." + board.release;
	SetDlgItemText(IDC_PROG_ENV_VERSION_B, value.c_str());

	value = board.day + " " + board.month + " " + board.year;
	SetDlgItemText(IDC_PROG_ENV_DATE_B, value.c_str());

	board = eqp->GetBoardManagement();

	//value = board.capabilities + " " + board.release + "." + board.number;
	value = board.capabilities + " " + board.number + "." + board.release;
	SetDlgItemText(IDC_PROG_ENV_VERSION_T, value.c_str());

	value = board.day + " " + board.month + " " + board.year;
	SetDlgItemText(IDC_PROG_ENV_DATE_T, value.c_str());

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_PROG_ENV::Valide() {}
