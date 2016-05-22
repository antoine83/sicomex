// DlgTRC1752_MOD_CONF_CONF.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_CONF_CONF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_CONF dialog


CDlgTRC1752_MOD_CONF_CONF::CDlgTRC1752_MOD_CONF_CONF(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_CONF_CONF::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_CONF_CONF)
	m_PiloteExterne = TRUE;
	m_ZtsPft = FALSE;
	m_Fft1302 = FALSE;
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_CONF_CONF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_CONF_CONF)
	DDX_Control(pDX, IDC_BUG_FFT_1302, c_Fft1302);
	DDX_Control(pDX, IDC_CHECK_ZTS, c_ZtsPft);
	DDX_Control(pDX, IDC_CHECK_PIL_EXT, c_PiloteExterne);
	DDX_Check(pDX, IDC_CHECK_PIL_EXT, m_PiloteExterne);
	DDX_Check(pDX, IDC_CHECK_ZTS, m_ZtsPft);
	DDX_Check(pDX, IDC_BUG_FFT_1302, m_Fft1302);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_CONF_CONF, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_CONF_CONF)
	ON_BN_CLICKED(IDC_CHECK_PIL_EXT, OnCheckPilExt)
	ON_BN_CLICKED(IDC_CHECK_ZTS, OnCheckZts)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUG_FFT_1302, OnCheckFft1302)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

void CDlgTRC1752_MOD_CONF_CONF::Valide() {}
/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_CONF message handlers

void CDlgTRC1752_MOD_CONF_CONF::OnCheckPilExt()
{
	UpdateData(TRUE);

	// FDI - 09/09/2015
	if (c_PiloteExterne.GetCheck())
		eqp->SetPilExt(TRUE);
	else
		eqp->SetPilExt(FALSE);

}

void CDlgTRC1752_MOD_CONF_CONF::LoadData()
{
	UpdateData(TRUE);

	m_PiloteExterne = eqp->GetPilExt();

	// FDI - ZTS
	m_ZtsPft = eqp->GetZtsPft();

	// FDI - FFT1302
	m_Fft1302 = eqp->GetFft1302();

	UpdateData(FALSE);
}

// FDI - ZTS (PFT)
void CDlgTRC1752_MOD_CONF_CONF::OnCheckZts()
{
	UpdateData(TRUE);

	if (c_ZtsPft.GetCheck())
		eqp->SetZtsPft(TRUE);
	else
		eqp->SetZtsPft(FALSE);

}

// FDI - FFT1302
void CDlgTRC1752_MOD_CONF_CONF::OnCheckFft1302()
{
	UpdateData(TRUE);

	if (c_Fft1302.GetCheck())
		eqp->SetFft1302(TRUE);
	else
		eqp->SetFft1302(FALSE);

}
