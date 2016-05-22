// DlgTRC1752_MOD_PROG_INTF_PIL.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_INTF_PIL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_PIL dialog

/*Ce menu permet d’activer ou de désactiver l’interface avec un pilote externe.*/


CDlgTRC1752_MOD_PROG_INTF_PIL::CDlgTRC1752_MOD_PROG_INTF_PIL(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_INTF_PIL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_INTF_PIL)
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_INTF_PIL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_INTF_PIL)
	DDX_Control(pDX, IDC_STATIC_INFO_PILOTE, c_PiloteInfo);
	DDX_Control(pDX, IDC_STATIC_PILOTE, m_Pilote_Txt);
	DDX_Control(pDX, IDC_PROG_INTF_PIL, m_ChPilote);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_INTF_PIL, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_INTF_PIL)
	ON_WM_TIMER()
	ON_WM_SHOWWINDOW()
	ON_CBN_DROPDOWN(IDC_PROG_INTF_PIL, OnDropdownProgIntfPil)
	ON_CBN_SELCHANGE(IDC_PROG_INTF_PIL, OnSelchangeProgIntfPil)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_PIL message handlers

BOOL CDlgTRC1752_MOD_PROG_INTF_PIL::OnInitDialog()
{
	CDialog::OnInitDialog();

	//	Armement du timer
	SetTimer(1,1000,NULL);

	c_PiloteInfo.ShowWindow(FALSE);

	return TRUE;
}

void CDlgTRC1752_MOD_PROG_INTF_PIL::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	// Gestion de l'affichage du message pour le pilote
	if (nIDEvent == 2)
	{
		arretTimer();
		return;
	}


	if (eqp->IsModif()) return;

	UpdateData(TRUE);

	m_ChPilote.SelectString(0, eqp->GetClockPilot().c_str());

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_PROG_INTF_PIL::Valide()
{
	if (eqp->GetPilExt() == FALSE)
	{
		//************************************************************************************************
		//Lorsque le pilote externe est sélectionné et n’est pas présent ou ne présente pas les
		//caractéristiques de niveau attendues,
		//le modem HF reste en fonctionnement sur le pilote interne et affiche un message de refus pendant
		//5s avant de revenir dans le menu pilote.
		//************************************************************************************************
		m_ChPilote.SetCurSel(0);
		marcheTimer();
		return;
	}

	CString value;

	m_ChPilote.GetLBText(m_ChPilote.GetCurSel(),value);

	eqp->SetClockPilot((char*)LPCTSTR(value));

	eqp->SetModif(false);
}

void CDlgTRC1752_MOD_PROG_INTF_PIL::OnDropdownProgIntfPil()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_INTF_PIL::OnSelchangeProgIntfPil()
{
	eqp->SetModif(true);
}

// **********************************************************
// Gestion du timer
// **********************************************************
void CDlgTRC1752_MOD_PROG_INTF_PIL::marcheTimer()
{
	m_timerPIL = SetTimer(2,5000,NULL);
	c_PiloteInfo.ShowWindow(TRUE);
}

void CDlgTRC1752_MOD_PROG_INTF_PIL::arretTimer()
{
	KillTimer(m_timerPIL);
	c_PiloteInfo.ShowWindow(FALSE);
}
