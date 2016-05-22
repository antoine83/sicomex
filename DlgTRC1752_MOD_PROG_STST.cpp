// DlgTRC1752_MOD_PROG_STST.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_STST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STST dialog


CDlgTRC1752_MOD_PROG_STST::CDlgTRC1752_MOD_PROG_STST(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_STST::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_STST)
	m_Version_A = _T("");
	m_Version_B = _T("");
	m_Version_T = _T("");
	m_Date_A = _T("");
	m_Date_B = _T("");
	m_Date_T = _T("");
	m_Msg1 = _T("");
	m_Msg2 = _T("");
	m_Msg11 = _T("");
	m_Msg21 = _T("");
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_STST::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_STST)
	DDX_Control(pDX, IDC_STST_MSG_21, c_Msg21);
	DDX_Control(pDX, IDC_STST_MSG_11, c_Msg11);
	DDX_Control(pDX, IDC_STST_MSG_2, c_Msg2);
	DDX_Control(pDX, IDC_STST_MSG_1, c_Msg1);
	DDX_Control(pDX, IDC_STATIC_TST, m_Tst);
	DDX_Control(pDX, IDC_STATIC_VAL, m_Val);
	DDX_Control(pDX, IDC_STATIC_ESC, m_Esc);
	DDX_Control(pDX, IDC_STST_DATE_T, m_Date_TT);
	DDX_Control(pDX, IDC_STST_DATE_B, m_Date_BB);
	DDX_Control(pDX, IDC_STST_DATE_A, m_Date_AA);
	DDX_Control(pDX, IDC_STST_VERSION_T, m_Version_TT);
	DDX_Control(pDX, IDC_STST_VERSION_B, m_Version_BB);
	DDX_Control(pDX, IDC_STST_VERSION_A, m_Version_AA);
	DDX_Control(pDX, IDC_STST_STATIC_T, m_Stst_T);
	DDX_Control(pDX, IDC_STST_STATIC_B, m_Stst_B);
	DDX_Control(pDX, IDC_STST_STATIC_A, m_Stst_A);
	DDX_Control(pDX, IDC_PROG_STST_CH_TYPE, m_TypeTst);
	DDX_Text(pDX, IDC_STST_VERSION_A, m_Version_A);
	DDX_Text(pDX, IDC_STST_VERSION_B, m_Version_B);
	DDX_Text(pDX, IDC_STST_VERSION_T, m_Version_T);
	DDX_Text(pDX, IDC_STST_DATE_A, m_Date_A);
	DDX_Text(pDX, IDC_STST_DATE_B, m_Date_B);
	DDX_Text(pDX, IDC_STST_DATE_T, m_Date_T);
	DDX_Text(pDX, IDC_STST_MSG_1, m_Msg1);
	DDX_Text(pDX, IDC_STST_MSG_2, m_Msg2);
	DDX_Text(pDX, IDC_STST_MSG_11, m_Msg11);
	DDX_Text(pDX, IDC_STST_MSG_21, m_Msg21);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_STST, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_STST)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_PROG_STST_CH_TYPE, OnSelchangeProgStstChType)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STST message handlers

BOOL CDlgTRC1752_MOD_PROG_STST::OnInitDialog()
{
	CDialog::OnInitDialog();

	//	Armement du timer
	//SetTimer(1,1000,NULL);

	//Initialisation du choix
	m_TypeTst.SetCurSel(0);

	//Cache les champs avant le test
	//AfficheCacheResultat(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTRC1752_MOD_PROG_STST::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	if(eqp->GetTestProgress() == "CARTE_A")
	{
		if (eqp->GetTest("A1") || eqp->GetTest("A2")
			|| eqp->GetTest("IA3") || eqp->GetTest("IA4")
			|| eqp->GetTest("D1") || eqp->GetTest("D2")
			|| eqp->GetTest("D3") || eqp->GetTest("D4"))
			c_Msg1.SetWindowText("AUTOTEST   CARTE   A  NOK");
		else
			c_Msg1.SetWindowText("AUTOTEST   CARTE   A  OK");
	}

	if(eqp->GetTestProgress() == "CARTE_B")
	{
		if (eqp->GetTest("B1") || eqp->GetTest("B2")
			|| eqp->GetTest("IA5") || eqp->GetTest("IA6")
			|| eqp->GetTest("D5") || eqp->GetTest("D6")
			|| eqp->GetTest("D7") || eqp->GetTest("D8"))
			c_Msg1.SetWindowText("AUTOTEST   CARTE   B  NOK");
		else
			c_Msg1.SetWindowText("AUTOTEST   CARTE   B  OK");
	}

	eqp->StopTest();
	//mise à zéro de la variable test carte //CC
	eqp->SetTestCarte(false);

	KillTimer(1);

}

void CDlgTRC1752_MOD_PROG_STST::Valide() {
	CString value;

	m_TypeTst.GetLBText(m_TypeTst.GetCurSel(),value);
	eqp->SetTestProgress((char*)LPCTSTR(value));
	// Si c'est un test tiroir, il sera executé par les timers de la vue ops
	// Si c'est une carte on l'execute dans les timers de cette vue
	if (eqp->GetTestProgress() == "CARTE_A" || eqp->GetTestProgress() == "CARTE_B")
	{
		eqp->StartTest();
		VideResultat();
		SetTimer(1, TPS_TEST, NULL);
		c_Msg1.SetWindowText("AUTOTEST   EN   COURS");
	}

}

/* **************************************************************************
METHODE :		Erreur()
TRAITEMENT:		Affiche le message d'erreur en parametre
***************************************************************************	*/
void CDlgTRC1752_MOD_PROG_STST::Erreur(const string type_erreur)
{
	VideResultat();
	c_Msg1.SetWindowText(type_erreur.c_str());
}

/* **************************************************************************
METHODE :		Erreur()
TRAITEMENT:		Affiche les messages d'erreurs en parametre
***************************************************************************	*/
void CDlgTRC1752_MOD_PROG_STST::Erreur(string *l1, string *l2, string *l3, string *l4)
{
	VideResultat();

	if (l1 != NULL)
		c_Msg1.SetWindowText(l1->c_str());

	if (l2 != NULL)
		c_Msg11.SetWindowText(l2->c_str());

	if (l3 != NULL)
		c_Msg2.SetWindowText(l3->c_str());

	if (l4 != NULL)
		c_Msg21.SetWindowText(l4->c_str());
}

void CDlgTRC1752_MOD_PROG_STST::AfficheCacheResultat(bool val)
{
	c_Msg1.ShowWindow(val);
	c_Msg2.ShowWindow(val);
	c_Msg11.ShowWindow(val);
	c_Msg21.ShowWindow(val);
}

void CDlgTRC1752_MOD_PROG_STST::VideResultat()
{
	c_Msg1.SetWindowText("");
	c_Msg2.SetWindowText("");
	c_Msg11.SetWindowText("");
	c_Msg21.SetWindowText("");
}

void CDlgTRC1752_MOD_PROG_STST::OnSelchangeProgStstChType()
{
	VideResultat();
}

//
void CDlgTRC1752_MOD_PROG_STST::TestCartex(int cartex)
{
	m_TypeTst.SetCurSel(cartex);

	if(cartex!=0)	Valide();
}

// Mise à jour de la liste en fonctionde quadrivoie
void CDlgTRC1752_MOD_PROG_STST::MiseJourListeCarte()
{
	//RAZ des listes
	m_TypeTst.ResetContent();


	//Initialisation
	m_TypeTst.AddString("TIROIR");
	m_TypeTst.AddString("CARTE_A");

	if (eqp->GetQuadrivoie() == TRUE)
		m_TypeTst.AddString("CARTE_B");

	m_TypeTst.SetCurSel(0);
}
