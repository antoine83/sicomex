// DlgTRC1752_MOD_CONF_ENV.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_CONF_ENV.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_ENV dialog


CDlgTRC1752_MOD_CONF_ENV::CDlgTRC1752_MOD_CONF_ENV(CEquipM1752 * equip, CWnd* pParent)
	: CDialog(CDlgTRC1752_MOD_CONF_ENV::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_CONF_ENV)
	m_Manufacturer = _T("");
	m_IdModem = _T("");
	m_ADd = _T("");
	m_AMm = _T("");
	m_ANr = _T("");
	m_ANv = _T("");
	m_AYy = _T("");
	m_BDd = _T("");
	m_BMm = _T("");
	m_BNr = _T("");
	m_BNv = _T("");
	m_BYy = _T("");
	m_ALg = _T("");
	m_BLg = _T("");
	m_TLg = _T("");
	m_TDd = _T("");
	m_TMm = _T("");
	m_TNr = _T("");
	m_TNv = _T("");
	m_TYy = _T("");
	m_TypeModem = FALSE;
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_CONF_ENV::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_CONF_ENV)
	DDX_Text(pDX, IDC_CONF_ENV_MANUFACTURER, m_Manufacturer);
	DDV_MaxChars(pDX, m_Manufacturer, 7);
	DDX_Text(pDX, IDC_CONF_ENV_ID_MODEM, m_IdModem);
	DDX_Text(pDX, IDC_CONF_ENV_A_DD, m_ADd);
	DDV_MaxChars(pDX, m_ADd, 2);
	DDX_Text(pDX, IDC_CONF_ENV_A_MM, m_AMm);
	DDV_MaxChars(pDX, m_AMm, 2);
	DDX_Text(pDX, IDC_CONF_ENV_A_NR, m_ANr);
	DDV_MaxChars(pDX, m_ANr, 1);
	DDX_Text(pDX, IDC_CONF_ENV_A_NV, m_ANv);
	DDV_MaxChars(pDX, m_ANv, 1);
	DDX_Text(pDX, IDC_CONF_ENV_A_YY, m_AYy);
	DDV_MaxChars(pDX, m_AYy, 2);
	DDX_Text(pDX, IDC_CONF_ENV_B_DD, m_BDd);
	DDV_MaxChars(pDX, m_BDd, 2);
	DDX_Text(pDX, IDC_CONF_ENV_B_MM, m_BMm);
	DDV_MaxChars(pDX, m_BMm, 2);
	DDX_Text(pDX, IDC_CONF_ENV_B_NR, m_BNr);
	DDV_MaxChars(pDX, m_BNr, 1);
	DDX_Text(pDX, IDC_CONF_ENV_B_NV, m_BNv);
	DDV_MaxChars(pDX, m_BNv, 1);
	DDX_Text(pDX, IDC_CONF_ENV_B_YY, m_BYy);
	DDV_MaxChars(pDX, m_BYy, 2);
	DDX_Text(pDX, IDC_CONF_ENV_FONC_A_LG, m_ALg);
	DDV_MaxChars(pDX, m_ALg, 2);
	DDX_Text(pDX, IDC_CONF_ENV_FONC_B_LG, m_BLg);
	DDV_MaxChars(pDX, m_BLg, 2);
	DDX_Text(pDX, IDC_CONF_ENV_FONC_T_LG, m_TLg);
	DDV_MaxChars(pDX, m_TLg, 2);
	DDX_Text(pDX, IDC_CONF_ENV_T_DD, m_TDd);
	DDV_MaxChars(pDX, m_TDd, 2);
	DDX_Text(pDX, IDC_CONF_ENV_T_MM, m_TMm);
	DDV_MaxChars(pDX, m_TMm, 2);
	DDX_Text(pDX, IDC_CONF_ENV_T_NR, m_TNr);
	DDV_MaxChars(pDX, m_TNr, 1);
	DDX_Text(pDX, IDC_CONF_ENV_T_NV, m_TNv);
	DDV_MaxChars(pDX, m_TNv, 1);
	DDX_Text(pDX, IDC_CONF_ENV_T_YY, m_TYy);
	DDV_MaxChars(pDX, m_TYy, 2);
	DDX_Check(pDX, IDC_TYPE_MODEM, m_TypeModem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_CONF_ENV, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_CONF_ENV)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_MANUFACTURER, OnKillfocusConfEnvManufacturer)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_ID_MODEM, OnKillfocusConfEnvIdModem)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_FONC_A_LG, OnKillfocusConfEnvFoncALg)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_A_NV, OnKillfocusConfEnvANv)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_A_NR, OnKillfocusConfEnvANr)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_A_DD, OnKillfocusConfEnvADd)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_A_MM, OnKillfocusConfEnvAMm)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_A_YY, OnKillfocusConfEnvAYy)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_FONC_B_LG, OnKillfocusConfEnvFoncBLg)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_B_NV, OnKillfocusConfEnvBNv)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_B_NR, OnKillfocusConfEnvBNr)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_B_DD, OnKillfocusConfEnvBDd)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_B_MM, OnKillfocusConfEnvBMm)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_B_YY, OnKillfocusConfEnvBYy)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_FONC_T_LG, OnKillfocusConfEnvFoncTLg)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_T_NV, OnKillfocusConfEnvTNv)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_T_NR, OnKillfocusConfEnvTNr)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_T_DD, OnKillfocusConfEnvTDd)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_T_MM, OnKillfocusConfEnvTMm)
	ON_EN_KILLFOCUS(IDC_CONF_ENV_T_YY, OnKillfocusConfEnvTYy)
	ON_BN_CLICKED(IDC_TYPE_MODEM, OnTypeModem)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgTRC1752_MOD_CONF_ENV::OnInitDialog()
{
	CDialog::OnInitDialog();

	//	Armement du timer
	//SetTimer(1,1000,NULL);
	pBtnTypeModem = (CButton*) GetDlgItem(IDC_TYPE_MODEM);

	LoadData();

	return TRUE;
}

void CDlgTRC1752_MOD_CONF_ENV::LoadData()
{
	UpdateData(TRUE);

	// Lecture des valeurs par défaut
	//string value;
	TBoard board;

	// Manufacturer
	m_Manufacturer = eqp->GetManufacturer().c_str();

	// Identity
	m_IdModem = eqp->GetIdentity().c_str();

	// Carte A
	board = eqp->GetBoard1();

	// Ability carte A
	m_ALg = board.capabilities.c_str();

	// Version carte A
	m_ANv = board.number.c_str();

	// Release carte A
	m_ANr = board.release.c_str();

	// Jour carte A
	m_ADd = board.day.c_str();

	// Mois carte A
	m_AMm = board.month.c_str();

	// Année carte A
	m_AYy = board.year.c_str();

	// Carte B
	board = eqp->GetBoard2();

	// Ability carte B
	m_BLg = board.capabilities.c_str();

	// Version carte B
	m_BNv = board.number.c_str();

	// Release carte B
	m_BNr = board.release.c_str();

	// Jour carte B
	m_BDd = board.day.c_str();

	// Mois carte B
	m_BMm = board.month.c_str();

	// Année carte B
	m_BYy = board.year.c_str();

	// Carte T
	board = eqp->GetBoardManagement();

	// Ability carte T
	m_TLg = board.capabilities.c_str();

	// Version carte T
	m_TNv = board.number.c_str();

	// Release carte T
	m_TNr = board.release.c_str();

	// Jour carte T
	m_TDd = board.day.c_str();

	// Mois carte T
	m_TMm = board.month.c_str();

	// Année carte T
	m_TYy = board.year.c_str();

	// Type de modem
	m_TypeModem = eqp->GetQuadrivoie();

	UpdateData(FALSE);
}

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_ENV message handlers

/************************* Champ Manufacturer ************************/
void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvManufacturer()
{
	string value = eqp->GetManufacturer();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_Manufacturer == CString(value.c_str()))
		return;

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_Manufacturer = value.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	value = (char*)LPCTSTR(m_Manufacturer);
	eqp->SetManufacturer(value);

}

/************************* Champ Identity ************************/
void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvIdModem()
{
	string value = eqp->GetIdentity();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_IdModem == CString(value.c_str()))
		return;

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_IdModem = value.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	value = (char*)LPCTSTR(m_IdModem);
	eqp->SetIdentity(value);

}

/************************* Champs A ************************/
void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvFoncALg()
{
	TBoard board = eqp->GetBoard1();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_ALg == CString(board.capabilities.c_str()))
		return;

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_ALg = board.capabilities.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.capabilities = (char*)LPCTSTR(m_ALg);
	eqp->SetBoard1(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvANv()
{
	TBoard board = eqp->GetBoard1();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_ANv == CString(board.number.c_str()))
		return;

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_ANv = board.number.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.number = (char*)LPCTSTR(m_ANv);
	eqp->SetBoard1(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvANr()
{
	TBoard board = eqp->GetBoard1();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_ANr == CString(board.release.c_str()))
		return;

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_ANr = board.release.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.release = (char*)LPCTSTR(m_ANr);
	eqp->SetBoard1(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvADd()
{
	TBoard board = eqp->GetBoard1();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_ADd == CString(board.day.c_str()))
		return;

	// Ajout en V3.0.1
	if (validationJour(atoi(m_ADd)) == FALSE )
	{
		AfxMessageBox("Saisie non Valide !");
		m_ADd = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_ADd = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.day = (char*)LPCTSTR(m_ADd);
	eqp->SetBoard1(board);


}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvAMm()
{
	TBoard board = eqp->GetBoard1();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_AMm == CString(board.month.c_str()))
		return;

	// Ajout en V3.0.1
	if (validationMois(atoi(m_AMm)) == FALSE )
	{
		AfxMessageBox("Saisie non Valide !");
		m_AMm = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_AMm = board.month.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.month = (char*)LPCTSTR(m_AMm);
	eqp->SetBoard1(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvAYy()
{
	TBoard board = eqp->GetBoard1();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_AYy == CString(board.year.c_str()))
		return;

	// Ajout en V3.0.1
	if (validationAn(atoi(m_AYy)) == FALSE )
	{
		AfxMessageBox("Saisie non Valide !");
		m_AYy = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_AYy = board.year.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.year = (char*)LPCTSTR(m_AYy);
	eqp->SetBoard1(board);

}

/************************* Champs B ************************/
void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvFoncBLg()
{
	TBoard board = eqp->GetBoard2();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_BLg == CString(board.capabilities.c_str()))
		return;

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_BLg = board.capabilities.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.capabilities = (char*)LPCTSTR(m_BLg);
	eqp->SetBoard2(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvBNv()
{
	TBoard board = eqp->GetBoard2();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_BNv == CString(board.number.c_str()))
		return;

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_BNv = board.number.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.number = (char*)LPCTSTR(m_BNv);
	eqp->SetBoard2(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvBNr()
{
	TBoard board = eqp->GetBoard2();;

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_BNr == CString(board.release.c_str()))
		return;

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_BNr = board.release.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.release = (char*)LPCTSTR(m_BNr);
	eqp->SetBoard2(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvBDd()
{
	TBoard board = eqp->GetBoard2();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_BDd == CString(board.day.c_str()))
		return;

	// Ajout en V3.0.1
	if (validationJour(atoi(m_BDd)) == FALSE )
	{
		AfxMessageBox("Saisie non Valide !");
		m_BDd = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_BDd = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.day = (char*)LPCTSTR(m_BDd);
	eqp->SetBoard2(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvBMm()
{
	TBoard board = eqp->GetBoard2();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_BMm == CString(board.month.c_str()))
		return;

	// Ajout en V3.0.1
	if (validationMois(atoi(m_BMm)) == FALSE )
	{
		AfxMessageBox("Saisie non Valide !");
		m_BMm = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_BMm = board.month.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.month = (char*)LPCTSTR(m_BMm);
	eqp->SetBoard2(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvBYy()
{
	TBoard board = eqp->GetBoard2();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_BYy == CString(board.year.c_str()))
		return;

	// Ajout en V3.0.1
	if (validationAn(atoi(m_BYy)) == FALSE )
	{
		AfxMessageBox("Saisie non Valide !");
		m_BYy = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_BYy = board.year.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.year = (char*)LPCTSTR(m_BYy);
	eqp->SetBoard2(board);

}

/************************* Champs T ************************/
void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvFoncTLg()
{
	TBoard board = eqp->GetBoardManagement();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_TLg == CString(board.capabilities.c_str()))
		return;

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_TLg = board.capabilities.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.capabilities = (char*)LPCTSTR(m_TLg);
	eqp->SetBoardManagement(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvTNv()
{
	TBoard board = eqp->GetBoardManagement();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_TNv == CString(board.number.c_str()))
		return;

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_TNv = board.number.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.number = (char*)LPCTSTR(m_TNv);
	eqp->SetBoardManagement(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvTNr()
{
	TBoard board = eqp->GetBoardManagement();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_TNr == CString(board.release.c_str()))
		return;

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_TNr = board.release.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.release = (char*)LPCTSTR(m_TNr);
	eqp->SetBoardManagement(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvTDd()
{
	TBoard board = eqp->GetBoardManagement();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_TDd == CString(board.day.c_str()))
		return;

	// Ajout en V3.0.1
	if (validationJour(atoi(m_TDd)) == FALSE )
	{
		AfxMessageBox("Saisie non Valide !");
		m_TDd = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_TDd = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.day = (char*)LPCTSTR(m_TDd);
	eqp->SetBoardManagement(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvTMm()
{
	TBoard board = eqp->GetBoardManagement();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_TMm == CString(board.month.c_str()))
		return;

	// Ajout en V3.0.1
	if (validationMois(atoi(m_TMm)) == FALSE )
	{
		AfxMessageBox("Saisie non Valide !");
		m_TMm = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_TMm = board.month.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.month = (char*)LPCTSTR(m_TMm);
	eqp->SetBoardManagement(board);

}

void CDlgTRC1752_MOD_CONF_ENV::OnKillfocusConfEnvTYy()
{
	TBoard board = eqp->GetBoardManagement();

	UpdateData(TRUE);

	// Nouvelle valeur ?
	if (m_TYy == CString(board.year.c_str()))
		return;

	// Ajout en V3.0.1
	if (validationAn(atoi(m_TYy)) == FALSE )
	{
		AfxMessageBox("Saisie non Valide !");
		m_TYy = board.day.c_str();
		UpdateData(FALSE);
		return;
	}

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_TYy = board.year.c_str();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur
	board.year = (char*)LPCTSTR(m_TYy);
	eqp->SetBoardManagement(board);

}

/************************* Type de modem ************************/
void CDlgTRC1752_MOD_CONF_ENV::OnTypeModem()
{
	UpdateData(TRUE);

	// Eqp en marche ?
	if (eqp->Actif() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en marche");
		m_TypeModem = eqp->GetQuadrivoie();
		UpdateData(FALSE);
		return;
	}

	// Set de la valeur - FDI - 09/09/2015
	if (pBtnTypeModem->GetCheck())
		eqp->SetQuadrivoie(TRUE);
	else
		eqp->SetQuadrivoie(FALSE);
}

//************************ Vérifications ************************/
bool CDlgTRC1752_MOD_CONF_ENV::validationJour(int jour)
{
	bool res = TRUE;

	if (jour <1 || jour >31)
		res = FALSE;

	return res;
}
bool CDlgTRC1752_MOD_CONF_ENV::validationMois(int mois)
{
	bool res = TRUE;

	if (mois <1 || mois >12)
		res = FALSE;

	return res;
}
bool CDlgTRC1752_MOD_CONF_ENV::validationAn(int an)
{
	bool res = TRUE;

	if (an <0 )
		res = FALSE;

	return res;
}
