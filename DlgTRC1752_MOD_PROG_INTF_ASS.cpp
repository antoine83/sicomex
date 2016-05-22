// DlgTRC1752_MOD_PROG_INTF_ASS.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_INTF_ASS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_ASS dialog

/*Ce menu permet d’associer les interfaces série aux configurations prédéfinies.*/


CDlgTRC1752_MOD_PROG_INTF_ASS::CDlgTRC1752_MOD_PROG_INTF_ASS(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_INTF_ASS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_INTF_ASS)
	//}}AFX_DATA_INIT

	this->eqp = equip;
	quadrivoie = true;
}


void CDlgTRC1752_MOD_PROG_INTF_ASS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_INTF_ASS)
	DDX_Control(pDX, IDC_STATIC_INFO, m_Info);
	DDX_Control(pDX, IDC_STATIC_DONNEES, m_Donnees_Txt);
	DDX_Control(pDX, IDC_PROG_INTF_DONNEES, m_ChDonnees);
	DDX_Control(pDX, IDC_PROG_INTF_ASS_CONFIGURATION, m_ChConfiguration);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_INTF_ASS, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_INTF_ASS)
		ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_PROG_INTF_DONNEES, OnSelchangeProgIntfDonnees)
	ON_CBN_DROPDOWN(IDC_PROG_INTF_DONNEES, OnDropdownProgIntfDonnees)
	ON_CBN_DROPDOWN(IDC_PROG_INTF_ASS_CONFIGURATION, OnDropdownProgIntfAssConfiguration)
	ON_CBN_SELCHANGE(IDC_PROG_INTF_ASS_CONFIGURATION, OnSelchangeProgIntfAssConfiguration)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_ASS message handlers

BOOL CDlgTRC1752_MOD_PROG_INTF_ASS::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_ChDonnees.AddString("D1");
	m_ChDonnees.AddString("D2");
	m_ChDonnees.AddString("D5");
	m_ChDonnees.AddString("D6");

	m_ChDonnees.SetCurSel(0);

	//	Armement du timer
	//SetTimer(1,1000,NULL);

	return TRUE;
}

void CDlgTRC1752_MOD_PROG_INTF_ASS::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	if (eqp->IsModif()) return;

	UpdateData(TRUE);

	/*
	// Remplissage du champ data link en fonction de l'option
	if (eqp->Actif() == FALSE && eqp->GetQuadrivoie() != quadrivoie)
	{

		m_ChDonnees.ResetContent();

		quadrivoie = eqp->GetQuadrivoie();

		m_ChDonnees.AddString("D1");
		m_ChDonnees.AddString("D2");

		if (quadrivoie == true)
		{
			m_ChDonnees.AddString("D5");
			m_ChDonnees.AddString("D6");
		}

		m_ChDonnees.SetCurSel(0);

	}
	*/

	// Recuperation du data link courant
	/*
	CString data;
	m_ChDonnees.GetLBText(m_ChDonnees.GetCurSel(),data);

	m_ChConfiguration.SelectString(0, (eqp->GetDataLinkAssociatedConfiguration((char*)LPCTSTR(data))).c_str());

	UpdateData(FALSE);
	*/

	MiseJourAssociation();
}

void CDlgTRC1752_MOD_PROG_INTF_ASS::Valide()
{
	CString value;

	m_ChConfiguration.GetLBText(m_ChConfiguration.GetCurSel(),value);

	// Recuperation du data link courant
	CString data;
	m_ChDonnees.GetLBText(m_ChDonnees.GetCurSel(),data);

	eqp->SetDataLinkAssociatedConfiguration((char*)LPCTSTR(data), (char*)LPCTSTR(value));

	eqp->SetModif(false);
}

void CDlgTRC1752_MOD_PROG_INTF_ASS::OnSelchangeProgIntfDonnees()
{
	eqp->SetModif(false);
}

void CDlgTRC1752_MOD_PROG_INTF_ASS::OnDropdownProgIntfDonnees()
{
	eqp->SetModif(false);
}

void CDlgTRC1752_MOD_PROG_INTF_ASS::OnDropdownProgIntfAssConfiguration()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_INTF_ASS::OnSelchangeProgIntfAssConfiguration()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_INTF_ASS::razChoixDataLink()
{
	m_ChDonnees.SetCurSel(0);
}

void CDlgTRC1752_MOD_PROG_INTF_ASS::StartTimer()
{
	SetTimer(1,1000,NULL);
	MiseJourAssociation();
}

void CDlgTRC1752_MOD_PROG_INTF_ASS::StopTimer()
{
	KillTimer(1);
}

void CDlgTRC1752_MOD_PROG_INTF_ASS::MiseJourListeInterfaceTd()
{
		m_ChDonnees.ResetContent();

		m_ChDonnees.AddString("D1");
		m_ChDonnees.AddString("D2");

		if (eqp->GetQuadrivoie() == TRUE)
		{
			m_ChDonnees.AddString("D5");
			m_ChDonnees.AddString("D6");
		}

		m_ChDonnees.SetCurSel(0);
}

void CDlgTRC1752_MOD_PROG_INTF_ASS::MiseJourAssociation()
{
	CString data;
	m_ChDonnees.GetLBText(m_ChDonnees.GetCurSel(),data);

	m_ChConfiguration.SelectString(0, (eqp->GetDataLinkAssociatedConfiguration((char*)LPCTSTR(data))).c_str());

	UpdateData(FALSE);
}
