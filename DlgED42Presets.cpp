// DlgED42Presets.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42Presets.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42Presets dialog


CDlgED42Presets::CDlgED42Presets(CEquipED42 * eqp,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42Presets::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42Presets)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	this->eqp = eqp;
	presetSelected = "0";
}

CDlgED42Presets::~CDlgED42Presets()
{
	m_presetTab->DestroyWindow();
	delete m_presetTab;
}

void CDlgED42Presets::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42Presets)
		DDX_Control(pDX, IDC_COMBO_TYPE, c_type);
		DDX_Control(pDX, IDC_COMBO_PRESET, c_preset);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42Presets, CDialog)
	//{{AFX_MSG_MAP(CDlgED42Presets)
		ON_CBN_SELCHANGE(IDC_COMBO_PRESET, OnSelchangePreset)
		ON_CBN_SELCHANGE(IDC_COMBO_TYPE, OnSelchangeType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42Presets message handlers
BOOL CDlgED42Presets::OnInitDialog()
{
	CDialog::OnInitDialog();

	c_type.SetCurSel(0);
	c_preset.SetCurSel(0);

	presetSelected = "0";

	m_presetTab = new CDlgED42PresetsTab(eqp);
    m_presetTab->Create(CDlgED42PresetsTab::IDD, this);
    m_presetTab->ShowWindow(SW_SHOW);

	UpdateData(FALSE);

	LoadData();

	return TRUE;
}

void CDlgED42Presets::LoadData()
{
	m_presetTab->LoadData(presetSelected);
}


void CDlgED42Presets::SaveData()
{
	m_presetTab->SaveData();
}


void CDlgED42Presets::OnSelchangePreset()
{
	char buffer[3] = "";

	itoa((c_type.GetCurSel() * 8) + c_preset.GetCurSel(), buffer,10);

	presetSelected = buffer;

	LoadData() ;
}

void CDlgED42Presets::OnSelchangeType()
{
	char buffer[3] = "";

	itoa((c_type.GetCurSel() * 8) + c_preset.GetCurSel(), buffer,10);

	presetSelected = buffer;

	LoadData() ;
}

CDlgED42PresetsTab* CDlgED42Presets::getTab()
{
	return m_presetTab;
}
