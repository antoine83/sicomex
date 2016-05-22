// DlgTRC1752_MOD_OPS.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"

#include "DlgTRC1752_MOD_OPS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_OPS dialog


CDlgTRC1752_MOD_OPS::CDlgTRC1752_MOD_OPS(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_OPS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_OPS)
	m_OpsMode = _T("REPOS");
	m_EtatAle = _T("N");
	m_VoieAle = 0;
	m_AleOps = FALSE;			//FALSE = Mode Ops/TRUE = Mode Actif
	m_AleStatus = 0;
	m_AleChannel = _T("00");
	m_AleQualite = _T("31");
	m_AleFrom = _T("1TX999");
	m_AleTo = _T("1TX000");
	m_VoieOps = 0;
	m_AleType = _T("S");
	m_MilEn = _T("S");
	m_FrqMark = _T("1575");		//Pour le FSKP recoit la fréquence centrale.
	m_FrqSpace = _T("2425");	//Pour le FSKP recoit le saut de shift.
	m_EtatDoppler = _T("----");
	m_EtatTc = FALSE;
	m_NiveauReception = _T("-30");
	m_EtatReception = _T("-----");			//Affiche "VEILLE" si la voie est activé
	m_EtatEmission = _T("-----");			//Affiche "INACTIF" si la voie est activé
	m_OpsType = _T("HD");
	m_OpsDiv = _T("--");
	m_AmdMsg = _T("");
	m_OpsMsgTest = _T("");
	m_OpsMsgTest2 = _T("");
	m_OpsMsgTest3 = _T("");
	m_NiveauEmission = 0;
	m_OpsMsgTest4 = _T("");
	//}}AFX_DATA_INIT

	this->eqp = equip;
	automate_test = 0;
	etat = FALSE;

	fen1 = FALSE;
	fen2 = FALSE;
	fen3 = FALSE;
}


void CDlgTRC1752_MOD_OPS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_OPS)
	DDX_Control(pDX, IDC_STATIC_MSG_TEST4, c_OpsMsgTest4);
	DDX_Control(pDX, IDC_PROGRESS_BF, m_Progress_Bf);
	DDX_Control(pDX, IDC_OPS_NIV_EMI1, c_NiveauEmission);
	DDX_Control(pDX, IDC_OPS_NIV_EMI_SPIN, s_NiveauEmission);
	DDX_Control(pDX, IDC_OPS_ALE_AMD_RAZ, m_AmdMsgRaz);
	DDX_Control(pDX, IDC_STATIC_ETAT_ALE, t_EtatAle);
	DDX_Control(pDX, IDC_STATIC_MSG_TEST3, c_OpsMsgTest3);
	DDX_Control(pDX, IDC_STATIC_MSG_TEST2, c_OpsMsgTest2);
	DDX_Control(pDX, IDC_STATIC_MSG_TEST, c_OpsMsgTest);
	DDX_Control(pDX, IDC_OPS_ETAT_TC, c_EtatTc);
	DDX_Control(pDX, IDC_STATIC_VOIE, c_Voie);
	DDX_Control(pDX, IDC_OPS_MODE, c_OpsMode);
	DDX_Control(pDX, IDC_OPS_ALE_AMD_MSG, c_AmdMsg);
	DDX_Control(pDX, IDC_OPS_DIV, c_OpsDiv);
	DDX_Control(pDX, IDC_OPS_TYPE, c_OpsType);
	DDX_Control(pDX, IDC_OPS_ETAT_EMI, c_EtatEmission);
	DDX_Control(pDX, IDC_OPS_ETAT_REC, c_EtatReception);
	DDX_Control(pDX, IDC_OPS_REC1, t_Rec1);
	DDX_Control(pDX, IDC_OPS_EMI1, t_Emi1);
	DDX_Control(pDX, IDC_OPS_DOP, t_OpsDoppler);
	DDX_Control(pDX, IDC_OPS_NIV_REC, t_NiveauReception);
	DDX_Control(pDX, IDC_OPS_RAZ_BIN, c_OpsRazBin);
	DDX_Control(pDX, IDC_OPS_HZ, t_Hz);
	DDX_Control(pDX, IDC_OPS_DBM_R, t_dbmr);
	DDX_Control(pDX, IDC_OPS_DBM_E, t_dbme);
	DDX_Control(pDX, IDC_OPS_P2, c_AleOpsP2);
	DDX_Control(pDX, IDC_OPS_DEBIT_REC, c_DebitRec);
	DDX_Control(pDX, IDC_OPS_DEBIT_EMI, c_DebitEmi);
	DDX_Control(pDX, IDC_OPS_REC2, t_Rec2);
	DDX_Control(pDX, IDC_OPS_EMI2, t_Emi2);
	DDX_Control(pDX, IDC_OPS_ETAT_DOPLER, c_EtatDoppler);
	DDX_Control(pDX, IDC_OPS_FRQ_SPACE, c_FrqSpace);
	DDX_Control(pDX, IDC_OPS_FRQ_MARK, c_FrqMark);
	DDX_Control(pDX, IDC_OPS_MIL_EN_VAL, c_MilEn);
	DDX_Control(pDX, IDC_OPS_MIL_EN, t_MilEn);
	DDX_Control(pDX, IDC_OPS_ETAT_ALE, c_EtatAle);
	DDX_Control(pDX, IDC_OPS_P3, c_AleOpsP3);
	DDX_Control(pDX, IDC_OPS_ALE_T_VAL, c_AleType);
	DDX_Control(pDX, IDC_STATIC_ALE_T, t_AleType);
	DDX_Control(pDX, IDC_OPS_ALE_DE_VAL, c_AleFrom);
	DDX_Control(pDX, IDC_STATIC_ALE_DE, t_AleFrom);
	DDX_Control(pDX, IDC_OPS_VOIE_CHOIX, c_VoieOps);
	DDX_Control(pDX, IDC_OPS_ALE_A_VAL, c_AleTo);
	DDX_Control(pDX, IDC_STATIC_ALE_A, t_AleTo);
	DDX_Control(pDX, IDC_OPS_ALE_Q_VAL, c_AleQualite);
	DDX_Control(pDX, IDC_STATIC_ALE_Q, t_AleQualite);
	DDX_Control(pDX, IDC_STATIC_ALE_CH_VAL, c_AleChannel);
	DDX_Control(pDX, IDC_STATIC_ALE_CH, t_AleChannel);
	DDX_Control(pDX, IDC_OPS_ALE_STATUS, c_AleStatus);
	DDX_Control(pDX, IDC_OPS_ALE_OPS, c_AleOps);
	DDX_Control(pDX, IDC_OPS_VOIE_ALE_CHOIX, c_VoieAle);
	DDX_Control(pDX, IDC_OPS_FRQ_SPACE_SPIN, s_FrqSpace);
	DDX_Control(pDX, IDC_OPS_FRQ_MARK_SPIN, s_FrqMark);
	DDX_Text(pDX, IDC_OPS_MODE, m_OpsMode);
	DDV_MaxChars(pDX, m_OpsMode, 11);
	DDX_Text(pDX, IDC_OPS_ETAT_ALE, m_EtatAle);
	DDV_MaxChars(pDX, m_EtatAle, 1);
	DDX_CBIndex(pDX, IDC_OPS_VOIE_ALE_CHOIX, m_VoieAle);
	DDX_Check(pDX, IDC_OPS_ALE_OPS, m_AleOps);
	DDX_CBIndex(pDX, IDC_OPS_ALE_STATUS, m_AleStatus);
	DDX_Text(pDX, IDC_STATIC_ALE_CH_VAL, m_AleChannel);
	DDX_Text(pDX, IDC_OPS_ALE_Q_VAL, m_AleQualite);
	DDX_Text(pDX, IDC_OPS_ALE_DE_VAL, m_AleFrom);
	DDV_MaxChars(pDX, m_AleFrom, 15);
	DDX_Text(pDX, IDC_OPS_ALE_A_VAL, m_AleTo);
	DDV_MaxChars(pDX, m_AleTo, 15);
	DDX_CBIndex(pDX, IDC_OPS_VOIE_CHOIX, m_VoieOps);
	DDX_Text(pDX, IDC_OPS_ALE_T_VAL, m_AleType);
	DDV_MaxChars(pDX, m_AleType, 1);
	DDX_Text(pDX, IDC_OPS_MIL_EN_VAL, m_MilEn);
	DDV_MaxChars(pDX, m_MilEn, 1);
	DDX_Text(pDX, IDC_OPS_FRQ_MARK, m_FrqMark);
	DDX_Text(pDX, IDC_OPS_FRQ_SPACE, m_FrqSpace);
	DDX_Text(pDX, IDC_OPS_ETAT_DOPLER, m_EtatDoppler);
	DDX_Check(pDX, IDC_OPS_ETAT_TC, m_EtatTc);
	DDX_Text(pDX, IDC_OPS_NIV_REC, m_NiveauReception);
	DDV_MaxChars(pDX, m_NiveauReception, 3);
	DDX_Text(pDX, IDC_OPS_ETAT_REC, m_EtatReception);
	DDX_Text(pDX, IDC_OPS_ETAT_EMI, m_EtatEmission);
	DDX_Text(pDX, IDC_OPS_TYPE, m_OpsType);
	DDX_Text(pDX, IDC_OPS_DIV, m_OpsDiv);
	DDX_Text(pDX, IDC_OPS_ALE_AMD_MSG, m_AmdMsg);
	DDV_MaxChars(pDX, m_AmdMsg, 90);
	DDX_Text(pDX, IDC_STATIC_MSG_TEST, m_OpsMsgTest);
	DDX_Text(pDX, IDC_STATIC_MSG_TEST2, m_OpsMsgTest2);
	DDX_Text(pDX, IDC_STATIC_MSG_TEST3, m_OpsMsgTest3);
	DDX_Text(pDX, IDC_OPS_NIV_EMI1, m_NiveauEmission);
	DDV_MinMaxInt(pDX, m_NiveauEmission, -30, 10);
	DDX_Text(pDX, IDC_STATIC_MSG_TEST4, m_OpsMsgTest4);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_OPS, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_OPS)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_OPS_FRQ_MARK_SPIN, OnOutofmemoryOpsFrqMarkSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_OPS_FRQ_MARK_SPIN, OnDeltaposOpsFrqMarkSpin)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_OPS_FRQ_SPACE_SPIN, OnOutofmemoryOpsFrqSpaceSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_OPS_FRQ_SPACE_SPIN, OnDeltaposOpsFrqSpaceSpin)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_OPS_NIV_EMI_SPIN, OnOutofmemoryOpsNivEmiSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_OPS_NIV_EMI_SPIN, OnDeltaposOpsNivEmiSpin)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_OPS_ALE_OPS, OnOpsAleOps)
	ON_BN_CLICKED(IDC_OPS_ALE_AMD_RAZ, OnOpsAleAmdRaz)
	ON_CBN_SELCHANGE(IDC_OPS_VOIE_CHOIX, OnSelchangeOpsVoieChoix)
	ON_BN_CLICKED(IDC_OPS_RAZ_BIN, OnOpsRazBin)
	ON_CBN_EDITCHANGE(IDC_OPS_ALE_STATUS, OnEditchangeOpsAleStatus)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_OPS message handlers



BOOL CDlgTRC1752_MOD_OPS::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initialisation des choix dans la vue
	// ************************************
	c_VoieOps.SetCurSel(0);			//Voie A1 par défaut
	c_VoieAle.SetCurSel(0);			// idem
	c_AleStatus.SetCurSel(5);		//Scanning par défaut
	c_AleStatus.EnableWindow(FALSE);

	// Initialisation des bornes
	s_NiveauEmission.SetRange(-30, 10);
	s_FrqMark.SetRange(-200, 200);
	s_FrqSpace.SetRange(-200, 200);

	// Initialisation des fenêtres
	AffichageFenetreUn(FALSE);
	AffichageFenetreDeux(FALSE);
	AffichageFenetreTrois(FALSE);
	c_Voie.ShowWindow(FALSE);
	c_VoieOps.ShowWindow(FALSE);
	c_OpsMode.ShowWindow(FALSE);
	c_EtatTc.ShowWindow(FALSE);

	//	Armement du timer
	m_timerOps = SetTimer(1,1000,NULL);

	// Initialisation du progress bar pour la BF
	m_Progress_Bf.ShowWindow(FALSE);

	return TRUE;
}

void CDlgTRC1752_MOD_OPS::OnTimer(UINT nIDEvent)
{

	switch (nIDEvent)
	{
	case 1:
		{
			if (eqp->Actif() != etat)
			{
				etat = eqp->Actif();
				if (etat == FALSE)
				{
					AffichageFenetreUn(FALSE);
					AffichageFenetreDeux(FALSE);
					AffichageFenetreTrois(FALSE);
					c_Voie.ShowWindow(FALSE);
					c_VoieOps.ShowWindow(FALSE);
					c_OpsMode.ShowWindow(FALSE);
					c_EtatTc.ShowWindow(FALSE);
					m_Progress_Bf.ShowWindow(FALSE);
					c_EtatEmission.ShowWindow(FALSE);
					c_EtatAle.ShowWindow(FALSE);
					t_EtatAle.ShowWindow(FALSE);

				} else {
					AffichageFenetreUn(TRUE);
					AffichageFenetreDeux(TRUE);
					AffichageFenetreTrois(TRUE);
					c_Voie.ShowWindow(TRUE);
					c_VoieOps.ShowWindow(TRUE);
					c_OpsMode.ShowWindow(TRUE);
					c_EtatTc.ShowWindow(TRUE);

					// Initialisation de la liste des voies en fonction des tests
					c_VoieOps.ResetContent();
					if (!eqp->GetTest("A1"))
						c_VoieOps.AddString("A1");
					if (!eqp->GetTest("A2"))
						c_VoieOps.AddString("A2");
					if (!eqp->GetTest("B1"))
						c_VoieOps.AddString("B1");
					if (!eqp->GetTest("B2"))
						c_VoieOps.AddString("B2");

				}
			}

			if (automate_test != 0) return;

			if (eqp->GetTestProgress() == "TIROIR" && eqp->IsEnTest() == FALSE)
			{
				automate_test = 1;
				eqp->StartTest();
				//Implémentation du §4.2.2 page 30/124
				AffichageFenetreUn(FALSE);
				AffichageFenetreDeux(FALSE);
				AffichageFenetreTrois(FALSE);
				c_Voie.ShowWindow(FALSE);
				c_VoieOps.ShowWindow(FALSE);
				c_OpsMode.ShowWindow(FALSE);
				c_EtatTc.ShowWindow(FALSE);
				m_Progress_Bf.ShowWindow(FALSE);
				m_EtatEmission = _T("AUTOTEST   EN   COURS");

				RemplirTest();

				c_EtatEmission.ShowWindow(TRUE);
				UpdateData(FALSE);

				SetTimer(2, TPS_TEST_INIT, NULL);

				break;
			}

			if((eqp->GetTestProgress() == "CARTE_A" || eqp->GetTestProgress() == "CARTE_B") && eqp->GetTestCarte()== FALSE)
			{

				if (eqp->GetTestProgress() == "CARTE_A")
					eqp->AffichageTestCartes("A");

				if (eqp->GetTestProgress() == "CARTE_B")
					eqp->AffichageTestCartes("B");


				eqp->SetTestCarte(true);

				break;

			}
			if (etat == FALSE) return;

			// Refresh modem
			LoadData();
		}
		break;
	case 2:
		switch (automate_test)
		{
		case 1:
			// On affiche les tests
			Test();
			if (resultat_test.empty())
				automate_test++;
			break;
		case 2:
			// On finit les tests
			// On reinit le modem
			FinTest();
			automate_test = 0;
			InitVoies();
			KillTimer(2);
			break;
		default:
			automate_test = 0;
			KillTimer(2);
			break;
		}
		break;
	case 3:
		{
			// Arret de la modif
			eqp->SetModif(FALSE);
			KillTimer(3);
		}
		break;
	default:
		KillTimer(nIDEvent);
		break;
	}
}

//**********************************
// LoadData()
//**********************************
void CDlgTRC1752_MOD_OPS::LoadData()
{
	CString str, tmpDebitEmi, tmpDebitRec;
	string tmpConf;

	int nIndex = c_VoieOps.GetCurSel();

	if (nIndex != LB_ERR)
		c_VoieOps.GetLBText(c_VoieOps.GetCurSel(), str);
	else
	{
		SetTimer(1,1000,NULL);
		return;
	}

	UpdateData(TRUE);

	m_EtatTc = eqp->GetMode();

	tmpConf = eqp->GetChannelAssociatedAfConfiguration((char *)LPCTSTR(str));

	TChannelConfiguration conf_courante = eqp->GetChannelConfiguration(tmpConf);

	// Traitement du Mode
	if (conf_courante.waveform == "BFSK")
	{
		m_OpsMode = "FSKV";
	}
	else
	{
		m_OpsMode = conf_courante.waveform.c_str();
	}

		// TODO
	if (m_OpsMode == "" )
		m_OpsMode = "REPOS";


	// Traitement du 4285 et 4529 en fonction de la direction et du codage
	if ( m_OpsMode == "4285" || m_OpsMode =="4529")
	{
		if (conf_courante.direction == "FD" || conf_courante.direction == "HD" || conf_courante.direction == "TX")
		{
			if (conf_courante.af_transmission_codingtype == "SANS")
				m_OpsMode = m_OpsMode + "S";
			if (conf_courante.af_transmission_codingtype == "CODE")
				m_OpsMode = m_OpsMode + "C";
		}
		if (conf_courante.direction == "RX")
		{
			if (conf_courante.af_reception_codingtype == "SANS")
				m_OpsMode = m_OpsMode + "S";
			if (conf_courante.af_reception_codingtype == "CODE")
				m_OpsMode = m_OpsMode + "C";
		}
	}

	// Traitement du Type
	m_OpsType = conf_courante.direction.c_str();
	if (conf_courante.direction == "RX")
		m_OpsType = "RE";
	if (conf_courante.direction == "TX")
		m_OpsType = "EM";


	// Traitement de la Diversité
	m_OpsDiv = "--";
	if (conf_courante.diversity == "AVEC")
		m_OpsDiv = "DI";

	// Affichage des débits - af_transmission_baudrate - af_reception_baudrate
	tmpDebitEmi.Format(_T("%04d"), conf_courante.af_transmission_baudrate);
	c_DebitEmi.SetWindowText(tmpDebitEmi);
	tmpDebitRec.Format(_T("%04d"), conf_courante.af_reception_baudrate);
	c_DebitRec.SetWindowText(tmpDebitRec);

	// Traitement du mode MIL110a
	if ( strncmp(m_OpsMode, "MIL", 3) == 0 )
	{
		c_DebitRec.SetWindowText("AUTO");
		if (eqp->GetChannelAfLevelReceived((char *)LPCTSTR(str)) >= -10 )
		{
			c_DebitRec.SetWindowText(tmpDebitEmi);
			eqp->SendPAO((char *)LPCTSTR(str), "RECEPTION");
		}

		// V3.0.1 affichage de l'entrelacement recu
		if (conf_courante.af_transmission_interleaving == "COURT")
			m_MilEn = _T("C");
		if (conf_courante.af_transmission_interleaving == "LONG")
			m_MilEn = _T("L");
		if (conf_courante.af_transmission_interleaving == "SANS")
			m_MilEn = _T("S");
	}

	// Traitement suivant la direction
	if (conf_courante.direction == "RX")
		c_DebitEmi.SetWindowText("------");
	if (conf_courante.direction == "TX")
		c_DebitRec.SetWindowText("------");


	// Traitement du Doppler
	// Mesuré avec une précission de +/- 1Hz en régime établi, donc != "VEILLE".
	m_EtatDoppler = "----";
	if (eqp->GetChannelState((char *)LPCTSTR(str)) == "ACTIVE" && eqp->GetChannelAfLevelReceived((char *)LPCTSTR(str)) > -15 && eqp->GetChannelEmissionEncours((char *)LPCTSTR(str)) != TRUE)
		m_EtatDoppler.Format(_T("%03d"), eqp->GetChannelDopplerOffset((char *)LPCTSTR(str)));


	// Etat ALE
	if ( eqp->GetChannelType((char *)LPCTSTR(str)) == "-")
		m_EtatAle = "-";


	// Affichage en fontion du Mode
	AffichageFonctionMode(str);	//Initialisation de l'affichage en fonction de m_OpsMode


	// Affichage si en ALE
	if ( eqp->GetChannelType((char *)LPCTSTR(str)) != "-" && conf_courante.waveform !="REPOS")

	{
		if (!eqp->IsModif())
			AffichageFonctionAle(str);
	}


	// Affichage de l'état Emi/Rec
	AffichageFonctionEmiRec(str);

	UpdateData(FALSE);

	SetTimer(1,1000,NULL);
}

void CDlgTRC1752_MOD_OPS::OnOutofmemoryOpsFrqMarkSpin(NMHDR* pNMHDR, LRESULT* pResult)
{

	*pResult = 0;
}

void CDlgTRC1752_MOD_OPS::OnDeltaposOpsFrqMarkSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	string tmpConf;
	int tmpFrq = 0;

	// Voie en cours
	c_VoieOps.GetLBText(c_VoieOps.GetCurSel(), str);

	// Récupération du niveau BF
	int tmpNiveauBF = eqp->GetChannelAfLevelReceived((char *)LPCTSTR(str));

	tmpConf = eqp->GetChannelAssociatedAfConfiguration((char *)LPCTSTR(str));
	TChannelConfiguration conf_courante = eqp->GetChannelConfiguration(tmpConf);

	// N'est possible que si m_EtatEmission = INACTIF et direction != FD et direction != RX ou niveau BF > -10 dBm
	if ((eqp->GetChannelEmissionEncours((char *)LPCTSTR(str)) && conf_courante.direction != "FD" && conf_courante.direction != "RX") || tmpNiveauBF < -10)
	{
		*pResult = 0;
		return;
	}

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	//*******************
	// Traitement de FSKV
	//*******************
	if (conf_courante.waveform == "FSKV" || conf_courante.waveform == "BFSK" )
	{
		tmpFrq = eqp->GetChannelOffsetMarkFrequency((char *)LPCTSTR(str));

		if (pNMUpDown->iDelta > 0)  tmpFrq += 1;
			else tmpFrq -= 1;

		if ( tmpFrq > 200 )
		{
			AfxMessageBox("Delta Fréquence max : 200 Hz.");
			tmpFrq = 200;
		}

		if ( tmpFrq < -200)
		{
			AfxMessageBox("Delta Fréquence min : -200 Hz.");
			tmpFrq = -200;
		}

		// Une modification de la fréquence basse "mark" entraîne une modification de la fréquence haute
		// "Space" et vice-versa.
		eqp->SetChannelOffsetMarkFrequency((char *)LPCTSTR(str), tmpFrq);
		eqp->SetChannelOffsetSpaceFrequency((char *)LPCTSTR(str), tmpFrq);
	}

	//*******************
	// Traitement de FSKP
	//*******************
	if (conf_courante.waveform == "FSKP" )
	{
		//tmpFrq = conf_courante.reception_carrier_frequency;
		tmpFrq = eqp->GetChannelOffsetCarrierFrequency((char *)LPCTSTR(str));

		if (pNMUpDown->iDelta > 0)  tmpFrq += 1;
			else tmpFrq -= 1;

		if ( tmpFrq > 200 )
		{
			AfxMessageBox("Delta Fréquence max : 200 Hz.");
			tmpFrq = 200;
		}

		if ( tmpFrq < -200)
		{
			AfxMessageBox("Delta Fréquence min : -200 Hz.");
			tmpFrq = -200;
		}

		eqp->SetChannelOffsetCarrierFrequency((char *)LPCTSTR(str), tmpFrq);
	}

	*pResult = 0;
}

void CDlgTRC1752_MOD_OPS::OnOutofmemoryOpsFrqSpaceSpin(NMHDR* pNMHDR, LRESULT* pResult)
{

	*pResult = 0;
}

void CDlgTRC1752_MOD_OPS::OnDeltaposOpsFrqSpaceSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString str;
	string tmpConf;
	int tmpFrq = 0;

	// Voie en cours
	c_VoieOps.GetLBText(c_VoieOps.GetCurSel(), str);

	tmpConf = eqp->GetChannelAssociatedAfConfiguration((char *)LPCTSTR(str));
	TChannelConfiguration conf_courante = eqp->GetChannelConfiguration(tmpConf);

	if (conf_courante.waveform == "FSKP" )
	{
		*pResult = 0;
		return;
	}

	// Récupération du niveau BF
	int tmpNiveauBF = eqp->GetChannelAfLevelReceived((char *)LPCTSTR(str));

	// N'est possible que si m_EtatEmission = INACTIF et direction != FD et direction != RX ou niveau BF > -10 dBm
	if ((eqp->GetChannelEmissionEncours((char *)LPCTSTR(str)) && conf_courante.direction != "FD" && conf_courante.direction != "RX") || tmpNiveauBF < -10)
	{
		*pResult = 0;
		return;
	}

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (conf_courante.waveform == "FSKV" || conf_courante.waveform == "BFSK")
	{
		tmpFrq = eqp->GetChannelOffsetSpaceFrequency((char *)LPCTSTR(str));

		if (pNMUpDown->iDelta > 0)  tmpFrq += 1;
			else tmpFrq -= 1;

		if ( tmpFrq > 200 )
		{
			AfxMessageBox("Deta Fréquence max : 200 Hz.");
			tmpFrq = 200;
		}

		if ( tmpFrq < -200)
		{
			AfxMessageBox("Delta Fréquence min : -200 Hz.");
			tmpFrq = -200;
		}

		UpdateData(FALSE);

	}

	// Une modification de la fréquence basse "mark" entraîne une modification de la fréquence haute
	// "Space" et vice-versa.
	eqp->SetChannelOffsetSpaceFrequency((char *)LPCTSTR(str), tmpFrq);
	eqp->SetChannelOffsetMarkFrequency((char *)LPCTSTR(str), tmpFrq);


	*pResult = 0;
}

void CDlgTRC1752_MOD_OPS::OnOutofmemoryOpsNivEmiSpin(NMHDR* pNMHDR, LRESULT* pResult)
{

	*pResult = 0;
}

void CDlgTRC1752_MOD_OPS::OnDeltaposOpsNivEmiSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	CString VoieEnCours;
	int tmpNiveauEmission, OffsetNiveauEmission;

	c_VoieOps.GetLBText(c_VoieOps.GetCurSel(), VoieEnCours);

	// N'est possible que si m_EtatEmission = EN COUR
	if (!eqp->GetChannelEmissionEncours((char *)LPCTSTR(VoieEnCours)))
	{
		*pResult = 0;
		return;
	}

	OffsetNiveauEmission = eqp->GetChannelAfLevelOutput((char *)LPCTSTR(VoieEnCours));
	tmpNiveauEmission = OffsetNiveauEmission;
	TAFChannelConfiguration conf_courante = eqp->GetAfChannelConfiguration(AF_CHANNELS_CONFIGURATIONS[c_VoieOps.GetCurSel()]);

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;


	if (pNMUpDown->iDelta > 0)  OffsetNiveauEmission += 1;
		else OffsetNiveauEmission -= 1;

	if ( conf_courante.output_level + OffsetNiveauEmission > 10 )
	{
		AfxMessageBox("Niveau max : 10 dBm.");
		OffsetNiveauEmission = tmpNiveauEmission;
	}

	if ( conf_courante.output_level + OffsetNiveauEmission < -30)
	{
		AfxMessageBox("Niveau min : -10 dBm.");
		OffsetNiveauEmission = tmpNiveauEmission;
	}

	UpdateData(FALSE);

	eqp->SetChannelAfLevelOutput((char *)LPCTSTR(VoieEnCours), OffsetNiveauEmission);

	*pResult = 0;
}

void CDlgTRC1752_MOD_OPS::Test(){
	//Suivant la saisie dans l'onglet Configuration/Paramètres test
	c_OpsMsgTest.ShowWindow(true);
	c_OpsMsgTest2.ShowWindow(true);
	c_OpsMsgTest3.ShowWindow(true);
	c_OpsMsgTest4.ShowWindow(true);

	//Affichage suivant §6.3.1 page 54/124

	TAffichage affichage = resultat_test.front();
	resultat_test.erase(resultat_test.begin());

	m_OpsMsgTest = _T(affichage.l1.c_str());
	m_OpsMsgTest2 = _T(affichage.l2.c_str());
	m_OpsMsgTest3 = _T(affichage.l3.c_str());
	m_OpsMsgTest4 = _T(affichage.l4.c_str());

	eqp->SetAutotestMessage(&(affichage.l1), &(affichage.l2), &(affichage.l3), &(affichage.l4));

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_OPS::FinTest(){

	m_OpsMsgTest	= _T("");
	m_OpsMsgTest2	= _T("");
	m_OpsMsgTest3	= _T("");
	m_OpsMsgTest4	= _T("");
	m_EtatEmission = _T("");
	c_OpsMsgTest.ShowWindow(FALSE);
	c_OpsMsgTest2.ShowWindow(FALSE);
	c_OpsMsgTest3.ShowWindow(FALSE);
	c_OpsMsgTest4.ShowWindow(FALSE);
	UpdateData(FALSE);

	eqp->StopTest();
}

void CDlgTRC1752_MOD_OPS::Valide ()
{
	// Changement impossible quand l'équipement est en Distant
	if (eqp->GetMode() == TRUE)
		return;

	// Modeification pour V3.0.1
	if ( c_AleStatus.GetCurSel() <= 5 )
	{
		OnOpsAleOps();
		return;
	}

	CString VoieAppelAle;

	c_VoieAle.GetLBText(c_VoieAle.GetCurSel(), VoieAppelAle);


	if (strcmp(m_EtatAle, "N") == 0)
		eqp->LancerAppel((LPCTSTR)VoieAppelAle);

	if (strcmp(m_EtatAle, "L") == 0)
		eqp->CasserAppel((char*)LPCTSTR(VoieAppelAle));

	OnOpsAleOps();

}

//-----------------------------
// Affichage en fontion du mode
//-----------------------------
void CDlgTRC1752_MOD_OPS::AffichageFonctionMode(CString str)
{
	string tmpConf;
	float t_shiftR;

	tmpConf = eqp->GetChannelAssociatedAfConfiguration((char *)LPCTSTR(str));
	TChannelConfiguration conf_courante = eqp->GetChannelConfiguration(tmpConf);

	AffichageFenetreUn(TRUE);
	AffichageFenetreDeux(TRUE);
	if ( eqp->GetChannelType((char *)LPCTSTR(str)) == "-" )
		AffichageFenetreTrois(FALSE);

	if (strncmp(m_OpsMode, "4285", 4) == 0 || strncmp(m_OpsMode, "4529", 4) == 0 || strncmp(m_OpsMode, "MIL", 3) == 0 || strncmp(m_OpsMode, "TRANS", 5) == 0)
	{
		c_FrqMark.ShowWindow(FALSE);
		s_FrqMark.ShowWindow(FALSE);
		c_FrqSpace.ShowWindow(FALSE);
		s_FrqSpace.ShowWindow(FALSE);
		t_EtatAle.ShowWindow(TRUE);
		c_EtatAle.SetWindowText(m_EtatAle);
		c_EtatDoppler.SetWindowText(m_EtatDoppler);
	}
	else
	{
		c_FrqMark.ShowWindow(TRUE);
		s_FrqMark.ShowWindow(TRUE);
		c_FrqSpace.ShowWindow(TRUE);
		s_FrqSpace.ShowWindow(TRUE);
		t_MilEn.ShowWindow(FALSE);
		c_MilEn.ShowWindow(FALSE);
		t_EtatAle.ShowWindow(TRUE);
		m_EtatAle = _T("-");
		c_EtatAle.SetWindowText(m_EtatAle);
		c_EtatAle.ShowWindow(FALSE);
		m_EtatDoppler = _T("----");
		c_EtatDoppler.SetWindowText(m_EtatDoppler);

	}

	// Traitement du mode 4529
	if (strncmp(m_OpsMode, "4529", 4) == 0)
	{
		m_EtatAle = _T("-");
		c_EtatAle.SetWindowText(m_EtatAle);
		c_EtatDoppler.SetWindowText(m_EtatDoppler);
		t_EtatAle.ShowWindow(FALSE);
		c_EtatAle.ShowWindow(FALSE);
	}

	// Traitement du mode MIL110
	if (strncmp(m_OpsMode, "MIL", 3) == 0)
	{
		t_MilEn.ShowWindow(TRUE);
		c_MilEn.ShowWindow(TRUE);
		t_EtatAle.ShowWindow(TRUE);
		c_EtatAle.ShowWindow(TRUE);
		c_EtatAle.SetWindowText(m_EtatAle);
	}
	else
	{
		t_MilEn.ShowWindow(FALSE);
		c_MilEn.ShowWindow(FALSE);
	}

	// Traitement du mode FSKV
	if ( strcmp(m_OpsMode, "FSKV") == 0 || conf_courante.waveform == "BFSK" )
	{
		m_FrqMark.Empty();
		t_EtatAle.ShowWindow(FALSE);
		c_OpsDiv.ShowWindow(FALSE);

		m_FrqMark.Format(_T("%04d"), conf_courante.reception_mark_frequency + eqp->GetChannelOffsetMarkFrequency((char *)LPCTSTR(str)));

		// Réception en cours pour la commande POR/Mark
		if (eqp->GetChannelAfLevelReceived((char *)LPCTSTR(str)) > -10)
			m_FrqMark.Format(_T("%04d"), conf_courante.reception_mark_frequency + eqp->GetChannelOffsetMarkFrequency((char *)LPCTSTR(str)) + eqp->GetChannelOffsetCarrierFrequency((char *)LPCTSTR(str)));

		c_FrqMark.SetWindowText(m_FrqMark);
		m_FrqSpace.Empty();
		m_FrqSpace.Format(_T("%04d"), conf_courante.reception_space_frequency + eqp->GetChannelOffsetSpaceFrequency((char *)LPCTSTR(str)));

		// Réception en cours pour la commande POR/Space
		if (eqp->GetChannelAfLevelReceived((char *)LPCTSTR(str)) > -10)
			m_FrqSpace.Format(_T("%04d"), conf_courante.reception_space_frequency + eqp->GetChannelOffsetSpaceFrequency((char *)LPCTSTR(str)) + eqp->GetChannelOffsetCarrierFrequency((char *)LPCTSTR(str)));

		c_FrqSpace.SetWindowText(m_FrqSpace);
	}

	// Traitement du mode FSKP
	if (strcmp(m_OpsMode, "FSKP") == 0)
	{
		m_FrqMark.Empty();
		m_FrqSpace.Empty();
		t_EtatAle.ShowWindow(FALSE);
		c_OpsDiv.ShowWindow(FALSE);
		s_FrqSpace.ShowWindow(FALSE);

		// Affichage de la fréquence centrale réception
		m_FrqMark.Format(_T("%04d"), conf_courante.reception_carrier_frequency + eqp->GetChannelOffsetCarrierFrequency((char *)LPCTSTR(str)));
		if ( conf_courante.reception_carrier_frequency <1000 )
			m_FrqMark.Format(_T("%03d"), conf_courante.reception_carrier_frequency + eqp->GetChannelOffsetCarrierFrequency((char *)LPCTSTR(str)));

		c_FrqMark.SetWindowText(m_FrqMark);

		// Affichage du saut de shift
		t_shiftR = conf_courante.reception_space_frequency - conf_courante.reception_carrier_frequency;

		/*Le saut de fréquence ± 42,5 Hz correspond à la plage de fréquence :
		[sous porteuse - 42 Hz, sous porteuse + 43 Hz].
		Mais pour l'affichage on montre 42.5
		*/
		if (t_shiftR == 43)
			t_shiftR = 42.5;

		m_FrqSpace.Format(_T("+/-%03.0f"), t_shiftR);
		if (t_shiftR < 100)
			m_FrqSpace.Format(_T("+/-%02.1f"), t_shiftR);


		c_FrqSpace.SetWindowText(m_FrqSpace);
	}

	// Traitement du mode TRANSPARENT
	if (strncmp(m_OpsMode, "TRANS", 5) == 0)
	{
		AffichageFenetreUn(FALSE);
		c_EtatEmission.ShowWindow(TRUE);
		c_EtatEmission.SetWindowText(m_EtatEmission);
		t_EtatAle.ShowWindow(TRUE);
		c_EtatAle.SetWindowText(m_EtatAle);
		c_EtatAle.ShowWindow(TRUE);
		AffichageFenetreDeux(FALSE);
	}

	// Traitement du mode REPOS
	if (strcmp(m_OpsMode, "REPOS") == 0)
	{
		m_EtatAle = _T("-");
		c_EtatAle.SetWindowText(m_EtatAle);
		AffichageFenetreUn(FALSE);
		AffichageFenetreTrois(FALSE);
		AffichageFenetreDeux(FALSE);
	}

	//*********************************
	// Toujours visible qlq soit le mode
	//*********************************
	c_Voie.ShowWindow(TRUE);
	c_VoieOps.ShowWindow(TRUE);
	c_OpsMode.ShowWindow(TRUE);
	c_EtatTc.ShowWindow(TRUE);

	//UpdateData(FALSE);
}

//************************************************
// Affichage en fonction de l'utilisation de l'ALE
//************************************************
void CDlgTRC1752_MOD_OPS::AffichageFonctionAle(CString str)
{
	AffichageFenetreTrois(TRUE);

	string tmpTypeCall, tmpAleStatus, tmpState, tmpChannelType;
	//int tmpNiveauBF;

	TSad sad;
	TSta sta;
	TNet net;

	TAleParameter conf_courante = eqp->GetAleParameter((char *)LPCTSTR(str));
	tmpState		= eqp->GetChannelState((char *)LPCTSTR(str));
	tmpChannelType	= eqp->GetChannelType((char *)LPCTSTR(str));

	// Affichage en fonction de [string ale_status]
	tmpAleStatus = conf_courante.ale_status;

	// Affichage de m_AleStatus - MAE/[AB] page 49/124
	if ( m_AleOps == FALSE && tmpState == "ACTIVE")
	{
		if (tmpChannelType == "S")		// Scanning
			m_AleStatus = 5;

		if (tmpChannelType == "C")		// Listenning
			m_AleStatus = 4;
	}

	// Affichage de l'état ALE - tmpAleStatus = LKG/LKD/SAM/RAM
	if(tmpAleStatus == "REC" && m_EtatAle == "L")
	{
		m_EtatAle = "L";
		m_AleStatus = 3;
	}
	else m_EtatAle = "N";

	if (tmpAleStatus == "LKG" || tmpAleStatus == "LKD" || tmpAleStatus == "SAM" || tmpAleStatus == "RAM")
	{
		m_EtatAle	= "L";
		m_AleStatus = 3;
	}

	// Traitement du Sound
	if (tmpState == "ACTIVE")
	{
		if (tmpAleStatus == "RSO")		// Sounded
			m_AleStatus = 0;

		if (tmpAleStatus == "SOU")		// Sounding
			m_AleStatus = 1;

		if (tmpAleStatus == "CAL")		// Calling
			m_AleStatus = 6;

	}

	// Affichage aprés un CALL ou UNL
	if (m_AleOps != FALSE && tmpState == "ACTIVE")
	{
		if (c_AleStatus.GetCurSel() == 5 || c_AleStatus.GetCurSel() == 6)
			m_AleOps = FALSE;
	}

	// Type d'appel
	tmpTypeCall = conf_courante.call_type;

	m_AleType = "X";
	if ( tmpTypeCall == "STD")	// Station
		m_AleType = "S";

	if ( tmpTypeCall == "NET")	// Réseau
		m_AleType = "N";

	if ( tmpTypeCall == "ALL")	// ALL
		m_AleType = "A";

	if ( tmpTypeCall == "GRP")	// Groupe
		m_AleType = "G";

	// Numéro de canal/réseau
	if (eqp->GetChannelType((char *)LPCTSTR(str)) == "S")
		m_AleChannel.Format(_T("%02d"), eqp->GetAleChannelInScanset((char *)LPCTSTR(str)));
	else
		m_AleChannel.Format(_T("%02d"), eqp->GetChannelIndexScansetChannel((char *)LPCTSTR(str)));

	// Traitement des voies esclaves
	if (str == "A2" || str == "B2")
	{
		AffichageFenetreDeux(FALSE);
		AffichageFenetreTrois(FALSE);
		return;
	}

	//************************
	// Traitement des adresses
	//************************
	// Adresse - FM - index_selfaddress - m_AleFrom
	m_AleFrom = " ";
	if (eqp->GetSad((char *)LPCTSTR(str), conf_courante.index_selfaddress, sad) == TRUE)
	{
		m_AleFrom = sad.self_address.c_str();
	}

	// Adresse - TO - called_address - ZUJ Station/Network et ALL - m_AleTo
	m_AleTo = " ";
	// Station
	if ( m_AleType == "S" )
	{
		if (eqp->GetSta((char *)LPCTSTR(str), conf_courante.called_address, sta) == TRUE)
		{
			m_AleTo = sta.address_ale.c_str();
		}

	}
	// Réseau
	if ( m_AleType == "N" )
	{
		if (eqp->GetNet((char *)LPCTSTR(str), conf_courante.called_address, net) == TRUE)
		{
			m_AleTo = net.net_address.c_str();
		}

	}
	// ALL
	if ( m_AleType == "A" )
		m_AleTo = "ALL";

	// Le reste ADU
	if ( m_AleType == "X" )
		m_AleTo = " ";

	//************************

	// Affichage en fonction de m_EtatAle [-,N ou L]
	if (strcmp(m_EtatAle, "-") == 0)
	{
		AffichageFenetreTrois(FALSE);		// Pas D'ALE
	}
	else
	{
		AffichageFenetreTrois(TRUE);
	}
}

//Affichage ou non de la fenêtre Un
void CDlgTRC1752_MOD_OPS::AffichageFenetreUn(BOOL act)
{
	if (fen1 != act)
	{
		t_Emi1.ShowWindow(act);
		t_Rec1.ShowWindow(act);
		c_FrqMark.ShowWindow(act);
		c_FrqSpace.ShowWindow(act);
		s_FrqMark.ShowWindow(act);
		s_FrqSpace.ShowWindow(act);
		c_EtatEmission.ShowWindow(act);
		c_EtatReception.ShowWindow(act);
		t_MilEn.ShowWindow(act);
		c_MilEn.ShowWindow(act);
		c_OpsType.ShowWindow(act);
		c_OpsDiv.ShowWindow(act);
		t_EtatAle.ShowWindow(act);
		c_EtatAle.ShowWindow(act);

		fen1 = act;
	}
}

//Affichage ou non de la fenêtre Deux
void CDlgTRC1752_MOD_OPS::AffichageFenetreDeux(BOOL act)
{
	if (fen2 != act)
	{
		t_Emi2.ShowWindow(act);
		t_Rec2.ShowWindow(act);
		c_DebitEmi.ShowWindow(act);
		c_DebitRec.ShowWindow(act);
		c_NiveauEmission.ShowWindow(act);
		s_NiveauEmission.ShowWindow(act);
		c_OpsRazBin.ShowWindow(act);
		t_NiveauReception.ShowWindow(act);
		t_OpsDoppler.ShowWindow(act);
		c_EtatDoppler.ShowWindow(act);
		t_dbme.ShowWindow(act);
		t_dbmr.ShowWindow(act);
		t_Hz.ShowWindow(act);

		fen2 = act;
	}
}
//Affichage ou non de la fenêtre Trois
void CDlgTRC1752_MOD_OPS::AffichageFenetreTrois(BOOL act)
{
	if (fen3 != act)
	{
		c_AleOpsP3.ShowWindow(act);
		c_AleOps.ShowWindow(act);
		c_AleOps.ShowWindow(act);
		c_VoieAle.ShowWindow(act);
		c_AleStatus.ShowWindow(act);
		t_AleChannel.ShowWindow(act);
		c_AleChannel.ShowWindow(act);
		t_AleType.ShowWindow(act);
		c_AleType.ShowWindow(act);
		t_AleQualite.ShowWindow(act);
		c_AleQualite.ShowWindow(act);
		t_AleFrom.ShowWindow(act);
		c_AleFrom.ShowWindow(act);
		t_AleTo.ShowWindow(act);
		c_AleTo.ShowWindow(act);
		AffichageMessageAMD();

		fen3 = act;
	}
	/**********************************************************
	/Gestion de l'AMD à ne pas oublier
	/**********************************************************/

}

void CDlgTRC1752_MOD_OPS::OnOpsAleOps()
{
	//*!!!!!------ En fonction de la selection de : c_VoieAle -----!!!!!*/

	/*
	En mode actif, le second champ (c_AleStatus[c_VoieAle]) est automatiquement positionné sur "CALL"
	ou "UNL" en fonction de l’état du mode ALE (m_EtatAle[c_VoieAle]).
	*/

	// Changement impossible quand l'équipement est en Distant
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		m_AleOps = FALSE;
		UpdateData(FALSE);
		return;
	}

	if(m_AleOps == FALSE)
	{
		KillTimer(m_timerOps);

		m_AleOps = TRUE;
		c_AleStatus.EnableWindow(TRUE);
		old_pos = c_AleStatus.GetCurSel();		//Memorisation de la position

		// Correction pour la V3.0.1
		if (strcmp(m_EtatAle, "N") == 0 && (c_VoieAle.GetCurSel() == c_VoieOps.GetCurSel()))
			c_AleStatus.SetCurSel(6);			//CALL

		// Correction pour la V3.0.1
		if (strcmp(m_EtatAle, "L") == 0 && (c_VoieAle.GetCurSel() == c_VoieOps.GetCurSel()))
			c_AleStatus.SetCurSel(7);			//UNL
	}
	else
	{
		m_AleOps = FALSE;
		m_timerOps = SetTimer(1,1000,NULL);
		c_AleStatus.EnableWindow(FALSE);
		c_AleStatus.SetCurSel(old_pos);		//Remise en place de la position
		UpdateData(FALSE);
	}
}

void CDlgTRC1752_MOD_OPS::OnOpsAleAmdRaz()
{
	// TODO
}

//Gestion des message AMD et CHAT
void CDlgTRC1752_MOD_OPS::AffichageMessageAMD()
{
	if (m_AmdMsg != _T("") && this->eqp->Actif())
	{
		c_AmdMsg.ShowWindow(TRUE);
		m_AmdMsgRaz.ShowWindow(TRUE);
	}
	else
	{
		c_AmdMsg.ShowWindow(FALSE);
		m_AmdMsgRaz.ShowWindow(FALSE);
	}
}

void CDlgTRC1752_MOD_OPS::OnSelchangeOpsVoieChoix()
{
	c_VoieAle.SetCurSel(c_VoieOps.GetCurSel());
	KillTimer(m_timerOps);
	LoadData();
	eqp->SetVoieSelect(c_VoieOps.GetCurSel());
}

//***************************************
// Affichage de l'état Emission Réception
//***************************************
void CDlgTRC1752_MOD_OPS::AffichageFonctionEmiRec(CString str)
{
	if (m_OpsMode == "REPOS" )
	{
		m_Progress_Bf.ShowWindow(FALSE);
		return;
	}

	// Initialisation de l'affuchage
	m_Progress_Bf.ShowWindow(FALSE);
	m_EtatReception = _T("-----");			//puis affiche "VEILLE" si la voie est activé
	m_NiveauEmission = 0;
	m_EtatEmission  = _T("-----");			//puis affiche "INACTIF" si la voie est activé
	m_NiveauReception.Format(_T("%02d"), -30);
	m_AleQualite = "##";

	//*******************************************************************************
	string tmpTypeCall, tmpAleStatus, tmpChannelType;
	string tmpConf, tmpCodage, tmpState, af_id, tmpEmissionStatus, tmpReceptionStatus;
	int tmpNiveauBF, tmpNiveauQualite, tmpOffsetEmission, tmpNiveauBFM, tmpNiveauBFE;
	bool tmpEmission;


	TAleParameter conf_courante_ale = eqp->GetAleParameter((char *)LPCTSTR(str));
	tmpChannelType	= eqp->GetChannelType((char *)LPCTSTR(str));

	// Affichage en fonction de [string ale_status]
	tmpAleStatus = conf_courante_ale.ale_status;

	// Configuration associée à la voie
	tmpConf		= eqp->GetChannelAssociatedAfConfiguration((char *)LPCTSTR(str));

	// Etat de la voie
	tmpState	= eqp->GetChannelState((char *)LPCTSTR(str));

	// Configuration de la voie en cours
	TChannelConfiguration conf_courante = eqp->GetChannelConfiguration(tmpConf);
	tmpCodage = conf_courante.af_reception_codingtype.c_str();

	// Configuration BF associée
	af_id= eqp->GetAfChannelFromModemChannel((char *)LPCTSTR(str));
	TAFChannelConfiguration af_channel = eqp->GetAfChannelConfiguration(af_id);

	// Etat de l'émission
	tmpEmission			= eqp->GetChannelEmissionEncours((char *)LPCTSTR(str));
	tmpEmissionStatus	= eqp->GetChannelEmissionStatus((char *)LPCTSTR(str));
	tmpOffsetEmission	= eqp->GetChannelAfLevelOutput((char *)LPCTSTR(str));

	// Récupération du niveau de Qualité et du niveau BF
	tmpReceptionStatus	= eqp->GetChannelReceptionStatus((char *)LPCTSTR(str));
	tmpNiveauBFM		= eqp->GetChannelAfLevelReceived((char *)LPCTSTR(str));
	tmpNiveauBFE		= eqp->GetChannelAfLevelReceivedSlave((char *)LPCTSTR(eqp->GetNameSlave()));
	tmpNiveauQualite	= eqp->GetChannelQualityValue((char *)LPCTSTR(str));

	// Diversité
	if (conf_courante.diversity == "AVEC")
	{
		if(tmpNiveauBFM>=tmpNiveauBFE) tmpNiveauBF=tmpNiveauBFM;

		else tmpNiveauBF=tmpNiveauBFE;
	}
	else tmpNiveauBF=tmpNiveauBFM;


	//**************************************************************************
	// Mise à jour de l'affichage Emission et Réception en fontion du mode et de
	// l'état des niveaux
	//***************************************************************************
	if ( tmpState == "ACTIVE")
	{
		// Traitement du mode TRANSPARENT - ACTIVE
		if ( (strncmp(m_OpsMode, "TRAN", 4) == 0))
		{
			m_EtatEmission = _T("ACTIF");
			m_EtatReception = _T("");
			return;
		}

		// Traitement de TX
		if (conf_courante.direction == "TX")
		{
			EmissionEnCours(tmpEmissionStatus, af_channel.output_level + tmpOffsetEmission);
			return;
		}

		// Traitement de RX
		if (conf_courante.direction == "RX")
		{
			ReceptionEnCours(tmpReceptionStatus, tmpNiveauQualite, tmpNiveauBF, tmpCodage);
			return;
		}

		// Traitement de HD et FD
		if (conf_courante.direction == "HD" || conf_courante.direction == "FD")
		{
			// Traitement des émission en ALE
			if (tmpChannelType != "-" )
			{

				tmpEmissionStatus	= eqp->GetChannelEmissionStatus((char *)LPCTSTR(str));
				tmpReceptionStatus	= eqp->GetChannelReceptionStatus((char *)LPCTSTR(str));
			}

			// Affichage du niveau d'émission
			EmissionEnCours(tmpEmissionStatus, af_channel.output_level + tmpOffsetEmission);
			if (tmpEmission && conf_courante.direction != "FD")
				return;

			// Affichage de l'état de la réception
			ReceptionEnCours(tmpReceptionStatus, tmpNiveauQualite, tmpNiveauBF, tmpCodage);

		}
	}
	else if (strncmp(m_OpsMode, "TRAN", 4) == 0)
	{
		m_Progress_Bf.ShowWindow(FALSE);
		m_EtatEmission	= _T("");
		m_NiveauEmission = 0;
		m_EtatReception = _T("");
		m_NiveauReception.Format(_T("%02d"), -30);
		m_AleQualite = "##";
	}

}

//********************************************
// Initialisation de l'onglet Ops à la voie A1
//********************************************
void CDlgTRC1752_MOD_OPS::razChoixConfiguration()
{
	c_VoieOps.SetCurSel(0);
}

void CDlgTRC1752_MOD_OPS::OnOpsRazBin()
{
	eqp->RazIntegrite();
}


void CDlgTRC1752_MOD_OPS::EmissionEnCours(string tmpStatus, int tmpNiveau)
{
	m_EtatEmission	= tmpStatus.c_str();

	if (tmpStatus == "INACTIF")
		return;

	// Niveau Emission
	m_NiveauEmission = tmpNiveau;

	// Raz Réception
	m_EtatReception  = _T("-----");
	m_Progress_Bf.ShowWindow(FALSE);
	m_NiveauReception.Format(_T("%02d"), -30);
	m_AleQualite = "##";
	m_EtatDoppler = "----";
}

void CDlgTRC1752_MOD_OPS::ReceptionEnCours(string tmpStatus, int tmpQual, int tmpBf, string tmpCode)
{
	m_EtatReception = tmpStatus.c_str();
	if (tmpStatus == "INACTIF")
		m_EtatReception ="VEILLE";

	if ( strncmp(m_OpsMode, "4285", 4) == 0 || strncmp(m_OpsMode, "4529", 4) == 0 || strncmp(m_OpsMode, "MIL", 3) == 0)
	{
		m_Progress_Bf.SetRange32(0,31);
		m_Progress_Bf.SetPos(0);
		m_Progress_Bf.SetPos(tmpQual);
		m_AleQualite = "##";
		if (tmpBf >= -10 && m_EtatAle != "-")
			m_AleQualite.Format(_T("%02d"), tmpQual);

	}
	else
	{
		m_Progress_Bf.SetRange32(-30,10);
		m_Progress_Bf.SetPos(-30);
		m_Progress_Bf.SetPos(tmpBf);
	}

	// Affichage du niveau BF dans la fenêtre Deux
	m_NiveauReception.Format(_T("%02d"), tmpBf);

	// Affichage pour un mode sans codage
	if (tmpBf >= -10 && tmpCode != "SANS")
		m_Progress_Bf.ShowWindow(TRUE);

	if (tmpBf >= -10 && (strncmp(m_OpsMode, "FSK", 3) == 0 || strncmp(m_OpsMode, "BFSK", 4) == 0))
		m_Progress_Bf.ShowWindow(TRUE);

}

void CDlgTRC1752_MOD_OPS::OnEditchangeOpsAleStatus()
{
	eqp->SetModif(TRUE);
	SetTimer(3, 20000, NULL);
}

void CDlgTRC1752_MOD_OPS::InitVoies()
{
	// Mise à jour de la liste des voies
	c_VoieOps.ResetContent();
	c_VoieOps.AddString("A1");
	c_VoieOps.AddString("A2");

	if (eqp->GetQuadrivoie() == TRUE)	//Quatri-Voies
	{
		c_VoieOps.AddString("B1");
		c_VoieOps.AddString("B2");
	}

	c_VoieOps.SetCurSel(0);
}

void CDlgTRC1752_MOD_OPS::RemplirTest()
{
	// Vidage des affichages d'erreurs précédentes
	resultat_test.empty();

	// Vérification s'il y a une erreur présente
	bool is_erreur = false;

	if (eqp->GetTest("A1") || eqp->GetTest("A2")
		|| eqp->GetTest("TC") || eqp->GetTest("TC1") || eqp->GetTest("TC2")
		|| eqp->GetTest("IA3") || eqp->GetTest("IA4")
		|| eqp->GetTest("D1") || eqp->GetTest("D2") || eqp->GetTest("D3") || eqp->GetTest("D4")
		|| eqp->GetTest("EEPROM"))
		is_erreur = true;

	if (eqp->GetQuadrivoie() &&
		(eqp->GetTest("B1") || eqp->GetTest("B2")
		|| eqp->GetTest("TC3") || eqp->GetTest("TC4")
		|| eqp->GetTest("IA5") || eqp->GetTest("IA6")
		|| eqp->GetTest("D5") || eqp->GetTest("D6") || eqp->GetTest("D7") || eqp->GetTest("D8")))
		is_erreur = true;

	TAffichage affichage;

	// Si pas d'erreur on remplit et on quitte
	if (!is_erreur)
	{
		affichage.l1 = "AUTOTEST TIROIR OK";
		eqp->GetIdentityString(affichage.l3,affichage.l4);

		resultat_test.push_back(affichage);
		return;
	}

	// Sinon on remplit les erreurs
	eqp->GetTestStringChannel(affichage.l1, affichage.l2);
	resultat_test.push_back(affichage);

	affichage.l1 = "";
	affichage.l2 = "";
	affichage.l3 = "";
	affichage.l4 = "";

	if(!eqp->GetTestStringTC(affichage.l1, affichage.l2))
		resultat_test.push_back(affichage);

	affichage.l1 = "";
	affichage.l2 = "";
	affichage.l3 = "";
	affichage.l4 = "";

	if(!eqp->GetTestStringIA(affichage.l1, affichage.l2, affichage.l3, affichage.l4))
		resultat_test.push_back(affichage);

	affichage.l1 = "";
	affichage.l2 = "";
	affichage.l3 = "";
	affichage.l4 = "";

	if(!eqp->GetTestStringDX(affichage.l1, affichage.l2, affichage.l3, affichage.l4))
		resultat_test.push_back(affichage);

	affichage.l1 = "";
	affichage.l2 = "";
	affichage.l3 = "";
	affichage.l4 = "";

	if(!eqp->GetTestStringEEPROM(affichage.l1, affichage.l2))
		resultat_test.push_back(affichage);
}

void CDlgTRC1752_MOD_OPS::razOffsetFrequences()
{
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		UpdateData(FALSE);
		return;
	}

	CString str;

	int nIndex = c_VoieOps.GetCurSel();

	if (nIndex != LB_ERR)
		c_VoieOps.GetLBText(c_VoieOps.GetCurSel(), str);

	if (eqp->GetChannelState((char *)LPCTSTR(str)) == "INACTIVE" || eqp->GetChannelAfLevelReceived((char *)LPCTSTR(str)) < -10)
		return;

	// L’utilisation de la touche ESC permet
    // d’annuler les modifications en cours.
	eqp->SetChannelOffsetMarkFrequency((char *)LPCTSTR(str), 0);
	eqp->SetChannelOffsetSpaceFrequency((char *)LPCTSTR(str), 0);
}
