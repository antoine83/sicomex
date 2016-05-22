// DlgTRC1752_MOD_CONF_STST.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_CONF_STST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_STST dialog

/*Ce menu permet de réaliser l’autotest du tiroir complet, ou au choix, l’autotest de chacune des
deux cartes modem.
L’état du tiroir déterminé par l’autotest est mémorisé et peut être consulté. Lorsque l’opérateur
lance le test d’une carte modem-processeur, le résultat de ce test met à jour cet état mémorisé du
tiroir.*/


CDlgTRC1752_MOD_CONF_STST::CDlgTRC1752_MOD_CONF_STST(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_CONF_STST::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_CONF_STST)
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_CONF_STST::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_CONF_STST)
	DDX_Control(pDX, IDC_SAUVEGARDE, m_Sauvegarde);
	DDX_Control(pDX, IDC_PANNE_TC4, m_TC4);
	DDX_Control(pDX, IDC_PANNE_TC3, m_TC3);
	DDX_Control(pDX, IDC_PANNE_TC2, m_TC2);
	DDX_Control(pDX, IDC_PANNE_TC, m_TC);
	DDX_Control(pDX, IDC_PANNE_TC1, m_TC1);
	DDX_Control(pDX, IDC_PANNE_IA6, m_IA6);
	DDX_Control(pDX, IDC_PANNE_IA5, m_IA5);
	DDX_Control(pDX, IDC_PANNE_IA4, m_IA4);
	DDX_Control(pDX, IDC_PANNE_IA3, m_IA3);
	DDX_Control(pDX, IDC_PANNE_D8, m_D8);
	DDX_Control(pDX, IDC_PANNE_D7, m_D7);
	DDX_Control(pDX, IDC_PANNE_D6, m_D6);
	DDX_Control(pDX, IDC_PANNE_D5, m_D5);
	DDX_Control(pDX, IDC_PANNE_D4, m_D4);
	DDX_Control(pDX, IDC_PANNE_D3, m_D3);
	DDX_Control(pDX, IDC_PANNE_D2, m_D2);
	DDX_Control(pDX, IDC_PANNE_D1, m_D1);
	DDX_Control(pDX, IDC_PANNE_113, m_113);
	DDX_Control(pDX, IDC_PANNE_107, m_107);
	DDX_Control(pDX, IDC_PANNE_105, m_105);
	DDX_Control(pDX, IDC_PANNE_103, m_103);
	DDX_Control(pDX, IDC_INT_B2, m_IntB2);
	DDX_Control(pDX, IDC_INT_B1, m_IntB1);
	DDX_Control(pDX, IDC_INT_A2, m_IntA2);
	DDX_Control(pDX, IDC_INT_A1, m_IntA1);
	DDX_Control(pDX, IDC_CARTE_B2, m_B2);
	DDX_Control(pDX, IDC_CARTE_B1, m_B1);
	DDX_Control(pDX, IDC_CARTE_A2, m_A2);
	DDX_Control(pDX, IDC_CARTE_A1, m_A1);
	DDX_Control(pDX, IDC_TIROIR, m_Tiroir);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_CONF_STST, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_CONF_STST)
	ON_BN_CLICKED(IDC_CARTE_A1, OnCarteA1)
	ON_BN_CLICKED(IDC_CARTE_A2, OnCarteA2)
	ON_BN_CLICKED(IDC_CARTE_B1, OnCarteB1)
	ON_BN_CLICKED(IDC_CARTE_B2, OnCarteB2)
	ON_BN_CLICKED(IDC_SAUVEGARDE, OnSauvegarde)
	ON_BN_CLICKED(IDC_TIROIR, OnTiroir)
	ON_BN_CLICKED(IDC_PANNE_D1, OnPanneD1)
	ON_BN_CLICKED(IDC_PANNE_D2, OnPanneD2)
	ON_BN_CLICKED(IDC_PANNE_D3, OnPanneD3)
	ON_BN_CLICKED(IDC_PANNE_D4, OnPanneD4)
	ON_BN_CLICKED(IDC_PANNE_D5, OnPanneD5)
	ON_BN_CLICKED(IDC_PANNE_D6, OnPanneD6)
	ON_BN_CLICKED(IDC_PANNE_D7, OnPanneD7)
	ON_BN_CLICKED(IDC_PANNE_D8, OnPanneD8)
	ON_BN_CLICKED(IDC_PANNE_103, OnPanne103)
	ON_BN_CLICKED(IDC_PANNE_105, OnPanne105)
	ON_BN_CLICKED(IDC_PANNE_107, OnPanne107)
	ON_BN_CLICKED(IDC_PANNE_113, OnPanne113)
	ON_BN_CLICKED(IDC_INT_A1, OnIntA1)
	ON_BN_CLICKED(IDC_INT_A2, OnIntA2)
	ON_BN_CLICKED(IDC_INT_B1, OnIntB1)
	ON_BN_CLICKED(IDC_INT_B2, OnIntB2)
	ON_BN_CLICKED(IDC_PANNE_IA3, OnPanneIa3)
	ON_BN_CLICKED(IDC_PANNE_IA4, OnPanneIa4)
	ON_BN_CLICKED(IDC_PANNE_IA5, OnPanneIa5)
	ON_BN_CLICKED(IDC_PANNE_IA6, OnPanneIa6)
	ON_BN_CLICKED(IDC_PANNE_TC, OnPanneTc)
	ON_BN_CLICKED(IDC_PANNE_TC1, OnPanneTc1)
	ON_BN_CLICKED(IDC_PANNE_TC2, OnPanneTc2)
	ON_BN_CLICKED(IDC_PANNE_TC3, OnPanneTc3)
	ON_BN_CLICKED(IDC_PANNE_TC4, OnPanneTc4)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_STST message handlers

BOOL CDlgTRC1752_MOD_CONF_STST::OnInitDialog()
{
	CDialog::OnInitDialog();

	SetTimer(1,1000, NULL);

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


void CDlgTRC1752_MOD_CONF_STST::Valide () {}


//********************
//Panne de la Carte A1
//********************
void CDlgTRC1752_MOD_CONF_STST::OnCarteA1()
{
	// Set de la valeur
	if (m_A1.GetCheck())
		eqp->SetTest("A1", TRUE);
	else
		eqp->SetTest("A1", FALSE);

}

//********************
//Panne de la Carte A2
//********************
void CDlgTRC1752_MOD_CONF_STST::OnCarteA2()
{
	// Set de la valeur
	if (m_A2.GetCheck())
		eqp->SetTest("A2", TRUE);
	else
		eqp->SetTest("A2", FALSE);

}

//********************
//Panne de la Carte B1
//********************
void CDlgTRC1752_MOD_CONF_STST::OnCarteB1()
{
	// Set de la valeur
	eqp->SetTest("B1", m_B1.GetCheck()!=0);

}


//********************
//Panne de la Carte B2
//********************
void CDlgTRC1752_MOD_CONF_STST::OnCarteB2()
{
	// Set de la valeur
	eqp->SetTest("B2", m_B2.GetCheck()!=0);

}

//******************************************
//Panne Mineure sur Sauvegarde Configuration
//******************************************
void CDlgTRC1752_MOD_CONF_STST::OnSauvegarde()
{
	// Set de la valeur
	eqp->SetTest("EEPROM", m_Sauvegarde.GetCheck()!=0);

}

void CDlgTRC1752_MOD_CONF_STST::OnTiroir()
{
	// Set de la valeur
	eqp->SetTest("TIROIR", m_Tiroir.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneD1()
{
	// Set de la valeur
	eqp->SetTest("D1", m_D1.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneD2()
{
	// Set de la valeur
	eqp->SetTest("D2", m_D2.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneD3()
{
	// Set de la valeur
	eqp->SetTest("D3", m_D3.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneD4()
{
	// Set de la valeur
	eqp->SetTest("D4", m_D4.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneD5()
{
	// Set de la valeur
	eqp->SetTest("D5", m_D5.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneD6()
{
	// Set de la valeur
	eqp->SetTest("D6", m_D6.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneD7()
{
	// Set de la valeur
	eqp->SetTest("D7", m_D7.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneD8()
{
	// Set de la valeur
	eqp->SetTest("D8", m_D8.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanne103()
{
	// Set de la valeur
	eqp->SetTest("103-104", m_103.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanne105()
{
	// Set de la valeur
	eqp->SetTest("105-106", m_105.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanne107()
{
	// Set de la valeur
	eqp->SetTest("107-108", m_107.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanne113()
{
	// Set de la valeur
	eqp->SetTest("113-114", m_113.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnIntA1()
{
	// Set de la valeur
	eqp->SetTest("IntA1", m_IntA1.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnIntA2()
{
	// Set de la valeur
	eqp->SetTest("IntA2", m_IntA2.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnIntB1()
{
	// Set de la valeur
	eqp->SetTest("IntB1", m_IntB1.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnIntB2()
{
	// Set de la valeur
	eqp->SetTest("IntB2", m_IntB2.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneIa3()
{
	// Set de la valeur
	eqp->SetTest("IA3", m_IA3.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneIa4()
{
	// Set de la valeur
	eqp->SetTest("IA4", m_IA4.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneIa5()
{
	// Set de la valeur
	eqp->SetTest("IA5", m_IA5.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneIa6()
{
	// Set de la valeur
	eqp->SetTest("IA6", m_IA6.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneTc()
{
	// Set de la valeur
	eqp->SetTest("TC", m_TC.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneTc1()
{
	// Set de la valeur
	eqp->SetTest("TC1", m_TC1.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneTc2()
{
	// Set de la valeur
	eqp->SetTest("TC2", m_TC2.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneTc3()
{
	// Set de la valeur
	eqp->SetTest("TC3", m_TC3.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnPanneTc4()
{
	// Set de la valeur
	eqp->SetTest("TC4", m_TC4.GetCheck()!=0);
}

void CDlgTRC1752_MOD_CONF_STST::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	// L'integrité est mise à jour par un reset
	UpdateData(TRUE);
	m_IntA1.SetCheck(eqp->GetTest("IntA1"));
	m_IntA2.SetCheck(eqp->GetTest("IntA2"));
	m_IntB1.SetCheck(eqp->GetTest("IntB1"));
	m_IntB2.SetCheck(eqp->GetTest("IntB2"));
	UpdateData(FALSE);

	// Envoi du signal INT
	if (m_IntA1) eqp->SendINT("A1");
	if (m_IntA2) eqp->SendINT("A2");
	if (m_IntB1) eqp->SendINT("B1");
	if (m_IntB2) eqp->SendINT("B2");
}

void CDlgTRC1752_MOD_CONF_STST::LoadData()
{
	m_Tiroir.SetCheck(eqp->GetTest("TIROIR"));
	m_Sauvegarde.SetCheck(eqp->GetTest("EEPROM"));
	m_TC4.SetCheck(eqp->GetTest("TC4"));
	m_TC3.SetCheck(eqp->GetTest("TC3"));
	m_TC2.SetCheck(eqp->GetTest("TC2"));
	m_TC.SetCheck(eqp->GetTest("TC"));
	m_TC1.SetCheck(eqp->GetTest("TC1"));
	m_IA6.SetCheck(eqp->GetTest("IA6"));
	m_IA5.SetCheck(eqp->GetTest("IA5"));
	m_IA4.SetCheck(eqp->GetTest("IA4"));
	m_IA3.SetCheck(eqp->GetTest("IA3"));
	m_D8.SetCheck(eqp->GetTest("D8"));
	m_D7.SetCheck(eqp->GetTest("D7"));
	m_D6.SetCheck(eqp->GetTest("D6"));
	m_D5.SetCheck(eqp->GetTest("D5"));
	m_D4.SetCheck(eqp->GetTest("D4"));
	m_D3.SetCheck(eqp->GetTest("D3"));
	m_D2.SetCheck(eqp->GetTest("D2"));
	m_D1.SetCheck(eqp->GetTest("D1"));
	m_113.SetCheck(eqp->GetTest("113-114"));
	m_107.SetCheck(eqp->GetTest("107-108"));
	m_105.SetCheck(eqp->GetTest("105-106"));
	m_103.SetCheck(eqp->GetTest("103-104"));
}
