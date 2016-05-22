// DlgTRC1752_MOD_PROG_STA_TST.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_STA_TST.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA_TST dialog

int nrVoieTest = 2;		//Pour les essai de l'IHM


CDlgTRC1752_MOD_PROG_STA_TST::CDlgTRC1752_MOD_PROG_STA_TST(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_STA_TST::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_STA_TST)
	m_TstMessageUn = _T("");
	m_TstMessageDeux = _T("");
	m_TstVoie = _T("A1");
	m_1800Hz = _T("1800_HZ");
	m_RebouclageBf = _T("REBOUCLAGE_BF");
	m_TestInterfaceTd = _T("TEST_D1");
	m_TestInterfaceTc = _T("TEST_TC");
	m_TypeRebouclage = 0;
	//}}AFX_DATA_INIT

	this->eqp = equip;

	test_choisi = "1800HZ";
}


void CDlgTRC1752_MOD_PROG_STA_TST::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_STA_TST)
	DDX_Control(pDX, IDC_TYPE_REBOUCLAGE, c_TypeRebouclage);
	DDX_Control(pDX, IDC_TEST_TC, c_TestInterfaceTc);
	DDX_Control(pDX, IDC_TEST_DX, c_TestInterfaceTd);
	DDX_Control(pDX, IDC_REBOUCLAGE_BF, c_RebouclageBf);
	DDX_Control(pDX, IDC_1800_HZ, c_1800Hz);
	DDX_Control(pDX, IDC_PROG_STA_TST_VOIE, c_TstVoie);
	DDX_Control(pDX, IDC_STA_TST_MSG2, c_TstMessageDeux);
	DDX_Control(pDX, IDC_STA_TST_MSG1, c_TstMessageUn);
	DDX_Text(pDX, IDC_STA_TST_MSG1, m_TstMessageUn);
	DDX_Text(pDX, IDC_STA_TST_MSG2, m_TstMessageDeux);
	DDX_Text(pDX, IDC_PROG_STA_TST_VOIE, m_TstVoie);
	DDV_MaxChars(pDX, m_TstVoie, 2);
	DDX_Text(pDX, IDC_1800_HZ, m_1800Hz);
	DDX_Text(pDX, IDC_REBOUCLAGE_BF, m_RebouclageBf);
	DDX_Text(pDX, IDC_TEST_DX, m_TestInterfaceTd);
	DDX_Text(pDX, IDC_TEST_TC, m_TestInterfaceTc);
	DDX_CBIndex(pDX, IDC_TYPE_REBOUCLAGE, m_TypeRebouclage);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_STA_TST, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_STA_TST)
	ON_EN_SETFOCUS(IDC_1800_HZ, OnSetfocus1800Hz)
	ON_EN_SETFOCUS(IDC_REBOUCLAGE_BF, OnSetfocusRebouclageBf)
	ON_EN_SETFOCUS(IDC_TEST_DX, OnSetfocusTestDx)
	ON_EN_SETFOCUS(IDC_TEST_TC, OnSetfocusTestTc)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_TYPE_REBOUCLAGE, OnSelchangeTypeRebouclage)
	//}}AFX_MSG_MAP
	ON_EN_SETFOCUS(IDC_PROG_STA_TST_VOIE, OnSetfocusVoie)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA_TST message handlers


BOOL CDlgTRC1752_MOD_PROG_STA_TST::OnInitDialog()
{
	CDialog::OnInitDialog();


	c_TstVoie.SetFocus();
	m_TstVoie = CString(CHANNELS[nrVoieTest].c_str());

	//Test de la liaison de données associée à [m_TstVoie]
	m_TestInterfaceTd = CString(INTTD[nrVoieTest].c_str());


	//Type de rebouclage pour les tests : INT par défaut.
	c_TypeRebouclage.SetCurSel(0);

	SetTimer(1, 1500, NULL);

	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//-----------------------------------------
//Sélection du texte sur réception du focus
//-----------------------------------------
void CDlgTRC1752_MOD_PROG_STA_TST::OnSetfocusVoie()
{
	GetDlgItem(IDC_PROG_STA_TST_VOIE)->PostMessage(EM_SETSEL,0,-1);

}

//Déroulement du test et affichageTests
void CDlgTRC1752_MOD_PROG_STA_TST::Tests(int typeTest)
{
	m_TstMessageUn = _T("");
	m_TstMessageDeux = _T("");

	CString resultat = _T("");
	CString str;

	c_TypeRebouclage.GetLBText(c_TypeRebouclage.GetCurSel(), str);
	m_TypeRebouclage = c_TypeRebouclage.GetCurSel();

	CString v_type = _T("V28");			//Pour les tests


	//Message à afficher suivant le type de test...!!

	/*
	Test porteuse 1800 Hz	: Touche "VAL" ou "ESC" : pour arrêter le test en cours et revenir au menu test.
	Test rebouclage BF		: Touche "VAL" ou "ESC" : pour arrêter le test en cours et revenir au menu test.
	*/
	switch(typeTest)
	{
	case IDC_1800_HZ:
	case 0:
		m_TstMessageUn = _T("TEST 1800Hz EN COURS...");
		break;
	case IDC_REBOUCLAGE_BF:
	case 1:
		m_TstMessageUn = _T("REBOUCLAGE BF EN COURS...");
		break;
	case IDC_TEST_DX:
	case 2:
		/*En cas de test avec rebouclage interne, les signaux 113-115 ne sont pas testés, le résultat
		du test est toujours OK.
		*/

		m_TstMessageUn		= _T("TEST INTERFACE ") + CString(INTTD[nrVoieTest].c_str());
		m_TstMessageDeux	= _T("             EN COURS...");
		//
		//Traitement suivant résultat

		break;
	case IDC_TEST_TC:
	case 3:
		m_TstMessageUn		= _T("TEST TELECOMMANDE ");
		m_TstMessageDeux	= _T("TYPE ") + v_type + _T(" ") + str + _T("...");
		//
		//Traitement suivant résultat

		break;

	default:
		m_TstMessageUn = _T("");
		m_TstMessageDeux = _T("");
		break;
	}

	UpdateData(FALSE);

}

//Pour les tests
void CDlgTRC1752_MOD_PROG_STA_TST::Valide()
{
	string test_txt = eqp->GetChannelTest((LPCTSTR)m_TstVoie);

	// Si test en cours on l'arrete
	if (test_txt == "1800HZ" || test_txt == "BOUCLE_BF")
	{
		eqp->ArreterTestVoie((LPCTSTR)m_TstVoie);
		return;
	}

	if (test_choisi == "1800HZ" || test_choisi == "BOUCLE_BF")
	{
		eqp->LancerTestVoie((LPCTSTR)m_TstVoie, test_choisi);
	} else if (test_choisi == "TEST_DX")
	{
		test_txt = "TEST INTERFACE " + eqp->GetDataLinkFromChannel((LPCTSTR)m_TstVoie);
		m_TstMessageUn = _T(test_txt.c_str());
		m_TstMessageDeux = _T("EN COURS...");

		eqp->SetChannelTest((LPCTSTR)m_TstVoie, "TEST_DX");
	} else if (test_choisi == "TEST_TC")
	{
		m_TstMessageUn = _T("TEST TELECOMMANDE");
		test_txt = "TYPE V11 ";

		if (m_TypeRebouclage == 0)
			test_txt += "INTERNE";
		else
			test_txt += "EXTERNE";

		test_txt += " ....";

		m_TstMessageDeux = _T(test_txt.c_str());

		eqp->SetChannelTest((LPCTSTR)m_TstVoie, "TEST_TC");
	}

	UpdateData(FALSE);

}

//Pour les tests
void CDlgTRC1752_MOD_PROG_STA_TST::Esc()
{
	string test_txt = eqp->GetChannelTest((LPCTSTR)m_TstVoie);

	// Si test en cours on l'arrete
	if (test_txt == "1800HZ" || test_txt == "BOUCLE_BF")
		eqp->ArreterTestVoie((LPCTSTR)m_TstVoie);

}

void CDlgTRC1752_MOD_PROG_STA_TST::OnSetfocus1800Hz()
{
	test_choisi = "1800HZ";
}

void CDlgTRC1752_MOD_PROG_STA_TST::OnSetfocusRebouclageBf()
{
	test_choisi = "BOUCLE_BF";
}

void CDlgTRC1752_MOD_PROG_STA_TST::OnSetfocusTestDx()
{
	test_choisi = "TEST_DX";
}

void CDlgTRC1752_MOD_PROG_STA_TST::OnSetfocusTestTc()
{
	test_choisi = "TEST_TC";
}

void CDlgTRC1752_MOD_PROG_STA_TST::OnTimer(UINT nIDEvent)
{
	string test_txt;

	if (eqp->GetChannelTest((LPCTSTR)m_TstVoie) == "1800HZ")
		m_TstMessageUn = _T("TEST 1800Hz EN COURS...");
	else if (eqp->GetChannelTest((LPCTSTR)m_TstVoie) == "BOUCLE_BF")
		m_TstMessageUn = _T("REBOUCLAGE BF EN COURS");
	else if (eqp->GetChannelTest((LPCTSTR)m_TstVoie) == "TEST_DX")
	{
		if (eqp->GetTest(eqp->GetDataLinkFromChannel((LPCTSTR)m_TstVoie)) == FALSE)
		{ // Test ok
			test_txt = "TEST INTERFACE " + eqp->GetDataLinkFromChannel((LPCTSTR)m_TstVoie) + " OK";
			m_TstMessageUn = _T(test_txt.c_str());
			m_TstMessageDeux = _T("");
		} else
		{ // Test ko
			// Construction de l'erreur
			test_txt = eqp->GetDataLinkFromChannel((LPCTSTR)m_TstVoie) + "   ";

			test_txt += "103-4 ";
			if (eqp->GetTest("103-104") == TRUE)
				test_txt += "NOK";
			else
				test_txt += " OK";

			test_txt += " 105-6 ";
			if (eqp->GetTest("105-106") == TRUE)
				test_txt += "NOK";
			else
				test_txt += " OK";

			// affichage resultat du test
			m_TstMessageUn = _T(test_txt.c_str());

			// Construction de l'erreur
			test_txt = "       107-8 ";
			if (eqp->GetTest("103-104") == TRUE)
				test_txt += "NOK";
			else
				test_txt += " OK";

			test_txt += " 113-5 ";
			if (eqp->GetTest("113-115") == TRUE)
				test_txt += "NOK";
			else
				test_txt += " OK";

			// affichage resultat du test
			m_TstMessageDeux = _T(test_txt.c_str());
		}

		// fin du test
		eqp->SetChannelTest((LPCTSTR)m_TstVoie, DEFAULT_STRING_VALUE);
	}
	else if (eqp->GetChannelTest((LPCTSTR)m_TstVoie) == "TEST_TC")
	{
		test_txt = "TEST TELECOMMANDE  ";

		if (eqp->GetTest(eqp->GetLocalRemoteInterfaceConfigurationFromChannel((LPCTSTR)m_TstVoie)) == TRUE)
			test_txt += "NOK";
		else
			test_txt += " OK";

		// affichage resultat du test
		m_TstMessageUn = _T(test_txt.c_str());

		test_txt = "TYPE V11 ";
		if (m_TypeRebouclage == 0)
			test_txt += "INTERNE";
		else
			test_txt += "EXTERNE";

		test_txt += " ....";

		// affichage resultat du test
		m_TstMessageDeux = _T(test_txt.c_str());

		// fin du test
		eqp->SetChannelTest((LPCTSTR)m_TstVoie, DEFAULT_STRING_VALUE);
	}
	else
	{
		m_TstMessageUn = _T("");
		m_TstMessageDeux = _T("");
	}

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_PROG_STA_TST::InitVoie(const int voie)
{
	m_TstVoie = CString(CHANNELS[voie].c_str());
	//Test de la liaison de données associée à [m_TstVoie]
	m_TestInterfaceTd = CString(INTTD[voie].c_str());

	UpdateData(FALSE);
}

// FFT_1170
void CDlgTRC1752_MOD_PROG_STA_TST::OnSelchangeTypeRebouclage()
{
	m_TypeRebouclage = c_TypeRebouclage.GetCurSel();
}
