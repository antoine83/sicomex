// DlgTRC1752_MOD_PROG_ALE_LP.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_ALE_LP.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_LP dialog


CDlgTRC1752_MOD_PROG_ALE_LP::CDlgTRC1752_MOD_PROG_ALE_LP(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_ALE_LP::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_ALE_LP)
	m_LpVoie = 0;
	m_LpNiveau = 1;
	m_LpNomLt0 = _T("");
	m_LpIndexCle = _T("");
	m_LpPeriodeCle = _T("24H");
	m_LpDateMiseAjour = _T("01/01/10");
	m_LpHeureMiseAjour = _T("00H00.01");
	m_LpOrigHeure = _T("DEM");
	m_LpPrecisionActuelle = _T("6000");
	m_LpNomLt1 = _T("00");
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_ALE_LP::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_ALE_LP)
	DDX_Control(pDX, IDC_HEURE_MAJ, c_LpHeureMiseAjour);
	DDX_Control(pDX, IDC_DATE_MAJ, c_LpDateMiseAjour);
	DDX_Control(pDX, IDC_PRECISION_ACT, c_LpPrecissionActuelle);
	DDX_Control(pDX, IDC_ORIG_HEURE, c_LpOrigHeure);
	DDX_Control(pDX, IDC_LP_LT1, c_LpNomLt1);
	DDX_Control(pDX, IDC_LP_PERIODE, c_LpPeriodeCle);
	DDX_Control(pDX, IDC_LP_CLE, c_LpIndexCle);
	DDX_Control(pDX, IDC_LP_LT0, c_LpNomLt0);
	DDX_Control(pDX, IDC_NIVEAU_LP, c_LpNiveau);
	DDX_Control(pDX, IDC_LP_CH_VOIE, c_LpVoie);
	DDX_CBIndex(pDX, IDC_LP_CH_VOIE, m_LpVoie);
	DDX_Text(pDX, IDC_NIVEAU_LP, m_LpNiveau);
	DDV_MinMaxInt(pDX, m_LpNiveau, 0, 2);
	DDX_Text(pDX, IDC_LP_LT0, m_LpNomLt0);
	DDX_Text(pDX, IDC_LP_CLE, m_LpIndexCle);
	DDV_MaxChars(pDX, m_LpIndexCle, 2);
	DDX_Text(pDX, IDC_LP_PERIODE, m_LpPeriodeCle);
	DDV_MaxChars(pDX, m_LpPeriodeCle, 3);
	DDX_Text(pDX, IDC_DATE_MAJ, m_LpDateMiseAjour);
	DDV_MaxChars(pDX, m_LpDateMiseAjour, 8);
	DDX_Text(pDX, IDC_HEURE_MAJ, m_LpHeureMiseAjour);
	DDV_MaxChars(pDX, m_LpHeureMiseAjour, 8);
	DDX_Text(pDX, IDC_ORIG_HEURE, m_LpOrigHeure);
	DDV_MaxChars(pDX, m_LpOrigHeure, 3);
	DDX_Text(pDX, IDC_PRECISION_ACT, m_LpPrecisionActuelle);
	DDV_MaxChars(pDX, m_LpPrecisionActuelle, 5);
	DDX_Text(pDX, IDC_LP_LT1, m_LpNomLt1);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_ALE_LP, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_ALE_LP)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_LP_CH_VOIE, OnSelchangeLpChVoie)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_LP message handlers

BOOL CDlgTRC1752_MOD_PROG_ALE_LP::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initialisation timer pour les changements d'index de la clé LP
	m_timerAleTime = SetTimer(2,1000,NULL);	//3600000

	AffichageConfigurationLP();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//*****************************************
// Affichage de la configuration de la voie
//*****************************************
void CDlgTRC1752_MOD_PROG_ALE_LP::AffichageConfigurationLP()
{
	CString str, str_lp;
	string value, valueLT0, valueLT1;

	TBoard board;

	c_LpVoie.GetLBText(c_LpVoie.GetCurSel(), str_lp);

	TAleParameter conf_courante = eqp->GetAleParameter((char *)LPCTSTR(str_lp));

	//int link_protection_level; // 0/1/2
	str.Format(_T("%01d"), conf_courante.link_protection_level);
	c_LpNiveau.SetWindowText(str);


	// Table Name - LT0
	valueLT0.empty();
	valueLT0 = eqp->GetTableLtName((char *)LPCTSTR(str_lp), "LT0");
	if (valueLT0 == "" ) valueLT0 = "ND";

	c_LpNomLt0.SetWindowText(valueLT0.c_str());


	// Table Name - LT1
	valueLT1.empty();
	valueLT1 = eqp->GetTableLtName((char *)LPCTSTR(str_lp), "LT1");
	if (valueLT1 == "" ) valueLT1 = "ND";

	c_LpNomLt1.SetWindowText(valueLT1.c_str());


	//int key_position; // 00...30 / -1 == vide
	str.Format(_T("%02d"), 1+conf_courante.key_position);
	if (conf_courante.key_position < 0 || valueLT0 == "ND")
		str = "ND";

	c_LpIndexCle.SetWindowText(str);


	//string key_management; // FIX/24H ou ND si pas de clé
	c_LpPeriodeCle.SetWindowText(conf_courante.key_management.c_str());
	if (conf_courante.key_position < 0 || valueLT0 == "ND")
		c_LpPeriodeCle.SetWindowText("ND");


	// Mise à jour des informations : date, heure et origine
	//string date_and_time; // jj/mm/aa.hhHmm.ss
	//int time_accuracy; // 00000...60000
	//string date_origin; // GPS/MRC/DEM
	//string last_date_and_time; // jj/mm/aa.hhHmm.ss
	//int time_lag; // -60000...+60000
	switch(c_LpVoie.GetCurSel())
	{
	case 0:	//A1
		board = eqp->GetBoard1();
		break;
	case 1:	//B1
		board = eqp->GetBoard2();
		break;
	}

	// time_accuracy
	str.Format(_T("%05d"), board.time_accuracy);
	c_LpPrecissionActuelle.SetWindowText(str);


	// date_origin
	c_LpOrigHeure.SetWindowText(board.date_origin.c_str());


	// last_date_and_time
	char heure[9];
	char date[9];
	GetTimeFormat (LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT , NULL, "HH'H'mm'.'ss", (LPTSTR) heure, 9);
	GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,NULL,"dd'/'MM'/'yy", date, 9);
	value.empty();
	value = board.last_date_and_time;

	strcpy(date, (value.substr(0,8)).c_str());
	strcpy(heure, (value.substr(9,8)).c_str());

	c_LpDateMiseAjour.SetWindowText(date);
	c_LpHeureMiseAjour.SetWindowText(heure);


}

void CDlgTRC1752_MOD_PROG_ALE_LP::Valide()
{
	AffichageConfigurationLP();
}

// **********************************************************
// Gestion du timer
// **********************************************************
void CDlgTRC1752_MOD_PROG_ALE_LP::marcheTimer()
{
	// Initialisation de la liste des voies
	c_LpVoie.ResetContent();
	c_LpVoie.AddString("A1");

	if (eqp->GetQuadrivoie() == TRUE)	//Quatri-Voies
	{
		c_LpVoie.AddString("B1");
	}
	c_LpVoie.SetCurSel(0);

	if (eqp->GetMode() == false) return;		//il faut etre en distant

	m_timerAleLp = SetTimer(1,2000,NULL);
}

void CDlgTRC1752_MOD_PROG_ALE_LP::arretTimer()
{
	KillTimer(m_timerAleLp);
}

void CDlgTRC1752_MOD_PROG_ALE_LP::OnTimer(UINT nIDEvent)
{

	CDialog::OnTimer(nIDEvent);

	switch(nIDEvent)
	{
	case 1:
		AffichageConfigurationLP();
		break;
	case 2:
		ChangementIndexCleLp();
		break;
	}

}

void CDlgTRC1752_MOD_PROG_ALE_LP::OnSelchangeLpChVoie()
{
	// Affcihage de la configuration courante
	AffichageConfigurationLP();

}

//********************************************
// Gestion du Timer pour le changement d'index
//********************************************
void CDlgTRC1752_MOD_PROG_ALE_LP::ChangementIndexCleLp()
{
	// TODO - Incrémentation de l'index de la clé LP à 00H00.00 !!
	int tmpKeyPos;
	char heure[9];
	char date[9];

	GetTimeFormat (LOCALE_SYSTEM_DEFAULT, TIME_FORCE24HOURFORMAT , NULL, "HH'H'mm'.'ss", (LPTSTR) heure, 9);
	GetDateFormat(LOCALE_SYSTEM_DEFAULT,0,NULL,"dd'/'MM'/'yy", date, 9);

	TTableLT carteALt0;
	TTableLT carteALt1;
	TTableLT carteBLt0;
	TTableLT carteBLt1;

	TAleParameter carteA1 = eqp->GetAleParameter("A1");
	TAleParameter carteB1 = eqp->GetAleParameter("B1");

	if (strncmp(heure, "00H00.00", 8) == 0)
	{
		carteALt0 = eqp->GetTableLT("A1", "LT0");
		carteALt1 = eqp->GetTableLT("A1", "LT1");
		carteBLt0 = eqp->GetTableLT("B1", "LT0");
		carteBLt1 = eqp->GetTableLT("B1", "LT1");

		// Vérification de la présence des tables
		if (carteALt0.name == "" && carteBLt0.name == "")
			return;

		// Vérification du type de gestion des clés
		if (carteALt0.name != "" && carteBLt0.name != "" && carteA1.key_management == "FIX" && carteB1.key_management == "FIX")
			return;

		//*************************
		// Traitement de la carte A
		//*************************
		if (carteALt0.name != "" && carteA1.key_management != "FIX")
		{
			// Position plus un jour
			tmpKeyPos = 1 + carteA1.key_position;  // Incrémentation de l'index


			if (tmpKeyPos != 31 && carteALt0.key[tmpKeyPos] != FALSE )
			{
				carteA1.key_position = tmpKeyPos;
			}
			else
			{
				//Traitement de l'index
				if ( carteALt1.name != "" )
				{
					carteALt0.name = carteALt1.name;
					carteALt1.name = "";
					carteA1.key_position = 0;
				}
				else
				{
					if ( carteALt1.name == "" || carteALt1.key[0] == FALSE)
					{
						carteALt0.name = "";
						carteA1.key_position = -1;
						// TODO - Si utilisaton dans une voie active, désactiver la voie
						if ( eqp->GetChannelState("A1") == "ACTIVE")
						{
								// FDI-2012
								carteA1.ale_status = "NKY";
								eqp->SetAleStatus("A1","NKY");
								eqp->Desactiver("A1");
						}
					}
				}

				// Mise à jour
				eqp->SetTableLT("A1", "LT0", carteALt0);
				eqp->SetTableLT("A1", "LT1", carteALt1);
			}

			// Mise à jour des paramètres ALE
			eqp->SetAleParameter("A1", carteA1);

		}

		//*************************
		// Traitement de la carte B
		//*************************
		if (carteBLt0.name != "" && carteB1.key_management != "FIX")
		{
			// Position plus un jour
			tmpKeyPos = 1 + carteB1.key_position;  // Incrémentation de l'index

			if (tmpKeyPos != 31 && carteBLt0.key[tmpKeyPos] != FALSE )
			{
				carteB1.key_position = tmpKeyPos;
			}
			else
			{
				//Traitement de l'index
				if ( carteBLt1.name != "" )
				{
					carteBLt0.name = carteALt1.name;
					carteBLt1.name = "";
					carteB1.key_position = 0;
				}
				else
				{
					if ( carteBLt1.name == "" || carteBLt1.key[0] == FALSE)
					{
						carteBLt0.name = "";
						carteB1.key_position = -1;
						// TODO - Si utilisaton dans une voie active, désactiver la voie
						if ( eqp->GetChannelState("B1") == "ACTIVE")
						{
								// FDI-2012
								carteB1.ale_status = "NKY";
								eqp->SetAleStatus("B1","NKY");
								eqp->Desactiver("B1");
						}
					}
				}

				// Mise à jour
				eqp->SetTableLT("B1", "LT0", carteBLt0);
				eqp->SetTableLT("B1", "LT1", carteBLt1);
			}

			// Mise à jour des paramètres ALE
			eqp->SetAleParameter("B1", carteB1);
		}
	}
}
