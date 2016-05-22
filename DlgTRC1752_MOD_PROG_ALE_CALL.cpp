// DlgTRC1752_MOD_PROG_ALE_CALL.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_ALE_CALL.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_CALL dialog

/*CALLPARAM = paramètres d’appel de la fonction ALE*/


CDlgTRC1752_MOD_PROG_ALE_CALL::CDlgTRC1752_MOD_PROG_ALE_CALL(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_ALE_CALL::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_ALE_CALL)
	m_AleCallFrom = 0;
	m_AleCallTo = 0;
	m_AleCallCanal = 0;
	m_AleCallType = 0;
	m_AleCanalF2 = _T("");
	m_ALeCallCagRec = 0;
	m_AleCallLqa = 0;
	m_AleCallTerm = 0;
	//}}AFX_DATA_INIT
	CALL_TYPE = 0;

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_ALE_CALL::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_ALE_CALL)
	DDX_Control(pDX, IDC_PROG_ALE_CALL_FROM, c_AleCallFrom);
	DDX_Control(pDX, IDC_PROG_ALE_CALL_TO, c_AleCallTo);
	DDX_Control(pDX, IDC_ALE_SYS_CANAL_F2, c_AleCanalF2);
	DDX_Control(pDX, IDC_PROG_ALE_CALL_TERM, c_AleCallTerm);
	DDX_Control(pDX, IDC_PROG_ALE_CALL_LQA, c_AleCallLqa);
	DDX_Control(pDX, IDC_PROG_ALE_CALL_CAG_REC, c_AleCallCagRec);
	DDX_Control(pDX, IDC_PROG_ALE_CALL_TA, m_ChAleCallType);
	DDX_Control(pDX, IDC_PROG_ALE_SYS_CANAL, m_ChAleCallCanal);
	DDX_CBIndex(pDX, IDC_PROG_ALE_CALL_FROM, m_AleCallFrom);
	DDX_CBIndex(pDX, IDC_PROG_ALE_CALL_TO, m_AleCallTo);
	DDX_CBIndex(pDX, IDC_PROG_ALE_SYS_CANAL, m_AleCallCanal);
	DDX_CBIndex(pDX, IDC_PROG_ALE_CALL_TA, m_AleCallType);
	DDX_Text(pDX, IDC_ALE_SYS_CANAL_F2, m_AleCanalF2);
	DDV_MaxChars(pDX, m_AleCanalF2, 2);
	DDX_CBIndex(pDX, IDC_PROG_ALE_CALL_CAG_REC, m_ALeCallCagRec);
	DDX_CBIndex(pDX, IDC_PROG_ALE_CALL_LQA, m_AleCallLqa);
	DDX_CBIndex(pDX, IDC_PROG_ALE_CALL_TERM, m_AleCallTerm);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_ALE_CALL, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_ALE_CALL)
	ON_CBN_SELCHANGE(IDC_PROG_ALE_CALL_TA, OnSelchangeProgAleCallTa)
	ON_CBN_SELCHANGE(IDC_PROG_ALE_SYS_CANAL, OnSelchangeProgAleSysCanal)
	ON_WM_TIMER()
	ON_CBN_EDITCHANGE(IDC_PROG_ALE_CALL_TO, OnEditchangeProgAleCallTo)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_CALL message handlers

BOOL CDlgTRC1752_MOD_PROG_ALE_CALL::OnInitDialog()
{
	CDialog::OnInitDialog();

	InitialisationListeFrom();
	InitialisationListeTo(CALL_TYPE);

	//Mise à jour de F2
	OnSelchangeProgAleSysCanal();


	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}


//********************************************
// Initialisation de la table des SelfAdresses
//********************************************
void CDlgTRC1752_MOD_PROG_ALE_CALL::InitialisationListeFrom()
{
	CString str_From;
	//int res;
	bool trou_table = false;

	TSad sad;

	// Raz de la table
	c_AleCallFrom.ResetContent();

	m_ChAleCallCanal.GetLBText(m_ChAleCallCanal.GetCurSel(), str_From);

	if (eqp->IsSadPresent((char *)LPCTSTR(str_From)) == FALSE)
		return;

	// Raz de la table
	//c_AleCallFrom.ResetContent();

	//Lecture de la table des SelfAddress
	for (int nb = 0; nb<NB_SAD; nb++)
	{
		if (eqp->GetSad((char *)LPCTSTR(str_From), nb, sad) == TRUE)
		{
			if ( trou_table == true)
					c_AleCallFrom.AddString("-");

			c_AleCallFrom.AddString(sad.self_address.c_str());
			trou_table = false;
		}
		else
			trou_table = true;

	}

}

//*********************************************
// Initialisation de la table des destinataires
//*********************************************
void CDlgTRC1752_MOD_PROG_ALE_CALL::InitialisationListeTo(int Call_Type)
{
	CString str_To;
	int nb;
	bool trou_table = false;

	TSta sta;
	TNet net;

	// Raz de la table
	c_AleCallTo.ResetContent();
	c_AleCallTo.ShowWindow(true);

	m_ChAleCallCanal.GetLBText(m_ChAleCallCanal.GetCurSel(), str_To);

	// Vérification de la précense de la table des Stations si STD_Call
	if (eqp->IsStaPresent((char *)LPCTSTR(str_To)) == FALSE && Call_Type == 0)		// Station = STA = STD
		return;

	// Vérification de la précense de la table des Réseaux si NET_Call
	if (eqp->IsNetPresent((char *)LPCTSTR(str_To)) == FALSE && Call_Type == 6)		// Reseau = NET
		return;

	// Raz de la table
	//c_AleCallTo.ResetContent();
	//c_AleCallTo.ShowWindow(true);

	switch(Call_Type)
	{
	case 0:
		//Initialisation depuis la tabe des stations - STA/STD
		for (nb = 0; nb<NB_STA; nb++)
		{
			if (eqp->GetSta((char *)LPCTSTR(str_To), nb, sta) == TRUE)
			{
				if ( trou_table == true)
					c_AleCallTo.AddString("-");

				c_AleCallTo.AddString(sta.address_ale.c_str());
				trou_table = false;
			}
			else
				trou_table = true;
		}
		break;
	case 1:
		// ANY-call - PROVISION
		c_AleCallTo.AddString("ADU");
		break;
	case 2:
		// SelectiveANy-call - PROVISION
		c_AleCallTo.AddString("ADU");
		break;
	case 3:
		// NUL-call - PROVISION
		c_AleCallTo.AddString("ADU");
		break;
	case 4:
		// SELfaddress-call - PROVISION
		c_AleCallTo.AddString("ADU");
		break;
	case 5:
		// WILdcard-call - PROVISION
		c_AleCallTo.AddString("ADU");
		break;
	case 6:
		//Initialisation depuis la tabe des reseaux - NET
		for (nb = 0; nb<NB_NET; nb++)
		{
			if (eqp->GetNet((char *)LPCTSTR(str_To), nb, net) == TRUE)
			{
				if ( trou_table == true)
					c_AleCallTo.AddString("-");

				c_AleCallTo.AddString(net.net_address.c_str());
				trou_table = false;
			}
			else
				trou_table = true;
		}
		break;
	case 7:
		//Initialisation pour ALL
		c_AleCallTo.ResetContent();
		c_AleCallTo.AddString("ALL");
		c_AleCallTo.ShowWindow(false);
		break;
	case 8:
		// GRouP-call - PROVISION
		c_AleCallTo.AddString("ADU");
		break;
	case 9:
		// SelectiveALlcall - PROVISION
		c_AleCallTo.AddString("ADU");
		break;
	default:
		c_AleCallTo.AddString("ADU");
		break;
	}

	//Initialisation de la position
	if (eqp->GetMode() == FALSE)
	{
		c_AleCallFrom.SetCurSel(0);
		c_AleCallTo.SetCurSel(0);
	}
}


//*************************
// Changement du Type Appel
//*************************
void CDlgTRC1752_MOD_PROG_ALE_CALL::OnSelchangeProgAleCallTa()
{
	InitialisationListeFrom();
	InitialisationListeTo(m_ChAleCallType.GetCurSel());
}

//********************
// Changement du Canal
//********************
void CDlgTRC1752_MOD_PROG_ALE_CALL::OnSelchangeProgAleSysCanal()
{
	CString str;
	int cIndex = m_ChAleCallCanal.GetCurSel();
	m_ChAleCallCanal.GetLBText(cIndex, str);

	c_AleCanalF2.SetWindowText(str);

	AffichageInfos();

}

//*********************************************
// Affichages des informations
//*********************************************
void CDlgTRC1752_MOD_PROG_ALE_CALL::AffichageInfos()
{

	CString str, str_call;
	int index_selfaddress, called_address;

	m_ChAleCallCanal.GetLBText(m_ChAleCallCanal.GetCurSel(), str_call);

	TAleParameter conf_courante = eqp->GetAleParameter((char *)LPCTSTR(str_call));

	// call_type
	m_ChAleCallType.SetCurSel(0);		//STA = STD par défaut
	if (conf_courante.call_type != "STD")
		m_ChAleCallType.SelectString(0, conf_courante.call_type.c_str());

	//Initialisation de la position
	c_AleCallFrom.SetCurSel(0);
	c_AleCallTo.SetCurSel(0);

	//*****************************
	// Mise à jour des self-adresse
	InitialisationListeFrom();

	// index_selfaddress
	index_selfaddress = conf_courante.index_selfaddress;
	c_AleCallFrom.SetCurSel(index_selfaddress);
	//*****************************

	//***************************************
	// Mise à jour des adresses destinataires
	InitialisationListeTo(m_ChAleCallType.GetCurSel());

	// called_address - index
	called_address = conf_courante.called_address;
	c_AleCallTo.SetCurSel(called_address);
	//***************************************


	// ale_termination_frame
	c_AleCallTerm.SetCurSel(0);				//TIS par défaut
	if (conf_courante.ale_termination_frame == "TAS")
		c_AleCallTerm.SetCurSel(1);

	// quality_analysis
	c_AleCallLqa.SetCurSel(0);				//Lqa = On par défaut
	if (conf_courante.quality_analysis == "OFF")
		c_AleCallLqa.SetCurSel(1);

	// agc
	c_AleCallCagRec.SetCurSel(0);			//FAST = RAPIDE par défaut
	if (conf_courante.agc == "OFF")
		c_AleCallCagRec.SetCurSel(3);

	if (conf_courante.agc == "SLOW")
		c_AleCallCagRec.SetCurSel(2);

	if (conf_courante.agc == "MEDIUM")
		c_AleCallCagRec.SetCurSel(1);


	UpdateData(TRUE);
}

//*************************************************
// Validation des choix
//*************************************************
void CDlgTRC1752_MOD_PROG_ALE_CALL::Valide()
{
	CString adre_fm, adre_to;

	// Changement impossible quand l'équipement est en Distant
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		UpdateData(FALSE);
		return;
	}


	//******************************************
	// Vérification de la sélection des adresses
	//******************************************
	c_AleCallFrom.GetLBText(c_AleCallFrom.GetCurSel(), adre_fm);
	c_AleCallTo.GetLBText(c_AleCallTo.GetCurSel(), adre_to);

	if (adre_fm == "-")
	{
		AfxMessageBox("Sélcetion d'une adresse SAD non valide !");
		UpdateData(FALSE);
		c_AleCallFrom.SetCurSel(0);
		return;
	}

	if (adre_to == "-")
	{
		AfxMessageBox("Sélcetion d'une adresse STA non valide !");
		UpdateData(FALSE);
		c_AleCallTo.SetCurSel(0);
		return;
	}

	// Passage à la suite
	UpdateData(TRUE);


	//Mémorisation de la configuration en cours
	MemorisationConfiguration();
}

//*********************************
// Mémorisation de la configuration
//*********************************
void CDlgTRC1752_MOD_PROG_ALE_CALL::MemorisationConfiguration()
{
	//******************
	// ALE CallParametre
	//******************
	CString str, str_call;
	int index_selfaddress, called_address;

	m_ChAleCallCanal.GetLBText(m_ChAleCallCanal.GetCurSel(), str_call);

	TAleParameter conf_courante = eqp->GetAleParameter((char *)LPCTSTR(str_call));

	// call_type
	if (m_ChAleCallType.GetCurSel() == 0)
	{
		str = "STD";
	}
	else
	{
		m_ChAleCallType.GetLBText(m_ChAleCallType.GetCurSel(), str);
	}
	conf_courante.call_type = str;

	// station_network_group - Mise à jour paramètre 13
	conf_courante.station_network_group = "S";
	if (m_ChAleCallType.GetCurSel() == 6)
		conf_courante.station_network_group = "N";


	if (m_ChAleCallType.GetCurSel() == 8)
		conf_courante.station_network_group = "G";


	// index_selfaddress
	index_selfaddress = c_AleCallFrom.GetCurSel();
	conf_courante.index_selfaddress = index_selfaddress;


	// called_address - index
	called_address = c_AleCallTo.GetCurSel();
	conf_courante.called_address = called_address;

	// ale_termination_frame
	conf_courante.ale_termination_frame = "TIS";
	if (c_AleCallTerm.GetCurSel() == 1)
		conf_courante.ale_termination_frame = "TAS";

	// quality_analysis
	conf_courante.quality_analysis == "ON";
	if (c_AleCallLqa.GetCurSel() == 1)
		conf_courante.quality_analysis = "OFF";

	// agc
	conf_courante.agc = "FAST";			//FAST = RAPIDE par défaut
	if (c_AleCallCagRec.GetCurSel() == 3)
		conf_courante.agc = "SANS";

	if (c_AleCallCagRec.GetCurSel() == 2)
		conf_courante.agc = "SLOW";

	if (c_AleCallCagRec.GetCurSel() == 1)
		conf_courante.agc = "MEDIUM";


	//**************************************************************************
	//Mise en place dans la structure
	//**************************************************************************
	eqp->SetAleParameter((char *)LPCTSTR(str_call), conf_courante);

	UpdateData(FALSE);

	//*************************************************************************************************
}

// **********************************************************
// Gestion du timer
// **********************************************************
void CDlgTRC1752_MOD_PROG_ALE_CALL::marcheTimer()
{
	// Initialisation de la liste des voies
	m_ChAleCallCanal.ResetContent();
	m_ChAleCallCanal.AddString("A1");

	if (eqp->GetQuadrivoie() == TRUE)	//Quatri-Voies
	{
		m_ChAleCallCanal.AddString("B1");
	}
	m_ChAleCallCanal.SetCurSel(0);

	// Mise à jour de l'affichage
	AffichageInfos();

	if (eqp->GetMode() == false) return;		//il faut être en distant

	m_timerAleCall = SetTimer(1,2000,NULL);
}

void CDlgTRC1752_MOD_PROG_ALE_CALL::arretTimer()
{
	KillTimer(m_timerAleCall);
}

void CDlgTRC1752_MOD_PROG_ALE_CALL::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	AffichageInfos();
}

void CDlgTRC1752_MOD_PROG_ALE_CALL::OnEditchangeProgAleCallTo()
{
	//MemorisationConfiguration();
}
