// DlgTRC1752_MOD_PROG_TC.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_TC.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_TC dialog

/*Ce menu permet l’activation ou la désactivation de la télécommande locale d’une voie*/


CDlgTRC1752_MOD_PROG_TC::CDlgTRC1752_MOD_PROG_TC(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_TC::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_TC)
	//}}AFX_DATA_INIT

	this->eqp = equip;
	quadrivoie = true;
}


void CDlgTRC1752_MOD_PROG_TC::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_TC)
	DDX_Control(pDX, IDC_PROG_TC_VOIE, m_ChVoie);
	DDX_Control(pDX, IDC_ETA_TCL, m_ChTcl);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_TC, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_TC)
	ON_WM_TIMER()
	ON_CBN_DROPDOWN(IDC_ETA_TCL, OnDropdownEtaTcl)
	ON_CBN_SELCHANGE(IDC_ETA_TCL, OnSelchangeEtaTcl)
	ON_CBN_DROPDOWN(IDC_PROG_TC_VOIE, OnDropdownProgTcVoie)
	ON_CBN_SELCHANGE(IDC_PROG_TC_VOIE, OnSelchangeProgTcVoie)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_TC message handlers

BOOL CDlgTRC1752_MOD_PROG_TC::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ChVoie.AddString("A1");
	m_ChVoie.AddString("A2");
	m_ChVoie.AddString("B1");
	m_ChVoie.AddString("B2");

	m_ChVoie.SetCurSel(0);

	//	Armement du timer
	//SetTimer(1,1000,NULL);

	return TRUE;
}

void CDlgTRC1752_MOD_PROG_TC::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	if (eqp->IsModif()) return;

	UpdateData(TRUE);

	// Remplissage du champ voie en fonction de l'option
	if (eqp->Actif() == FALSE && eqp->GetQuadrivoie() != quadrivoie)
	{
		m_ChVoie.ResetContent();

		quadrivoie = eqp->GetQuadrivoie();

		m_ChVoie.AddString("A1");
		m_ChVoie.AddString("A2");

		if (quadrivoie == true)
		{
			m_ChVoie.AddString("B1");
			m_ChVoie.AddString("B2");
		}

		m_ChVoie.SetCurSel(0);
	}


	// Recuperation de la voie courante
	CString voie;
	m_ChVoie.GetLBText(m_ChVoie.GetCurSel(),voie);

	// La valeur de la TC et de l'IHM est différente
	// On doit la convertir

	if (eqp->GetChannelLocalRemoteControl((char*)LPCTSTR(voie)) == "LOCAL")
		m_ChTcl.SelectString(0, "ACTIVE");

	if (eqp->GetChannelLocalRemoteControl((char*)LPCTSTR(voie)) == "MAIN")
		m_ChTcl.SelectString(0, "INACTIVE");


	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_PROG_TC::Valide()
{
	CString value;

	m_ChTcl.GetLBText(m_ChTcl.GetCurSel(),value);

	// Recuperation de la voie courante
	CString voie;

	m_ChVoie.GetLBText(m_ChVoie.GetCurSel(),voie);

	// La valeur de la TC et de l'IHM est différente
	// On doit la convertir

	if (value == "ACTIVE")
		eqp->SetChannelLocalRemoteControl((char*)LPCTSTR(voie), "LOCAL");

	if (value == "INACTIVE")
		eqp->SetChannelLocalRemoteControl((char*)LPCTSTR(voie), "MAIN");

	eqp->SetModif(false);
}

void CDlgTRC1752_MOD_PROG_TC::OnDropdownEtaTcl()
{
	eqp->SetModif(true);

}

void CDlgTRC1752_MOD_PROG_TC::OnSelchangeEtaTcl()
{
	eqp->SetModif(true);

}

void CDlgTRC1752_MOD_PROG_TC::OnDropdownProgTcVoie()
{
	eqp->SetModif(false);

}

void CDlgTRC1752_MOD_PROG_TC::OnSelchangeProgTcVoie()
{
	eqp->SetModif(false);

}

void CDlgTRC1752_MOD_PROG_TC::StartTimer()
{
	SetTimer(1,1000,NULL);
}

void CDlgTRC1752_MOD_PROG_TC::StopTimer()
{
	KillTimer(1);
}
