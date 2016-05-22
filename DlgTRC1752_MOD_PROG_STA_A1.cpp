// DlgTRC1752_MOD_PROG_STA_A1.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_STA_A1.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA_A1 dialog

/*Le menu station affiche ACTIVATION, la voie modem sélectionnée, A1 dans l’exemple cidessus,
n’est pas active pour autant. Seul l’indicateur d’activité (I pour voie Inactive, A pour
voie Active) permet de connaître l’état réel de la voie A1.
Une voie sur laquelle une panne bloquante a été détectée lors d’un autotest n’est plus accessible
au moyen de ce menu.*/


CDlgTRC1752_MOD_PROG_STA_A1::CDlgTRC1752_MOD_PROG_STA_A1(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_STA_A1::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_STA_A1)
	m_A1_Conf = 0;
	m_A1_Mode = _T("4285");
	m_MessageUn = _T("");
	m_MessageDeux = _T("");
	//}}AFX_DATA_INIT

	this->eqp = equip;
	quadrivoie = true;
}


void CDlgTRC1752_MOD_PROG_STA_A1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_STA_A1)
	DDX_Control(pDX, IDC_PROG_STA_A1_CONF, c_A1_Conf);
	DDX_Control(pDX, IDC_PROG_STA_A1_MODE, c_A1_Mode);
	DDX_Control(pDX, IDC_PROG_STA_A1_CIX, m_A1_Cix);
	DDX_Control(pDX, IDC_PROG_STA_A1_MA, m_A1_ModeAlternat);
	DDX_Control(pDX, IDC_PROG_STA_A1_CH, m_A1_AleIndex);
	DDX_Control(pDX, IDC_PROG_STA_A1_TA, m_A1_TA);
	DDX_Control(pDX, IDC_PROG_STA_A1_CANAL, m_A1_Canal);
	DDX_Control(pDX, IDC_PROG_STA_A1_TD, m_A1_TD);
	DDX_Control(pDX, IDC_STA_A1_MSG2, c_MessageDeux);
	DDX_Control(pDX, IDC_STA_A1_MSG1, c_MessageUn);
	DDX_Text(pDX, IDC_PROG_STA_A1_IA, m_A1_Ia);
	DDV_MaxChars(pDX, m_A1_Ia, 1);
	DDX_CBIndex(pDX, IDC_PROG_STA_A1_CONF, m_A1_Conf);
	DDX_Text(pDX, IDC_PROG_STA_A1_MODE, m_A1_Mode);
	DDV_MaxChars(pDX, m_A1_Mode, 11);
	DDX_Text(pDX, IDC_STA_A1_MSG1, m_MessageUn);
	DDX_Text(pDX, IDC_STA_A1_MSG2, m_MessageDeux);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_STA_A1, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_STA_A1)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_PROG_STA_A1_TA, OnSelchangeProgStaA1Ta)
	ON_CBN_SELCHANGE(IDC_PROG_STA_A1_TD, OnSelchangeProgStaA1Td)
	ON_CBN_DROPDOWN(IDC_PROG_STA_A1_TD, OnDropdownProgStaA1Td)
	ON_CBN_DROPDOWN(IDC_PROG_STA_A1_CANAL, OnDropdownProgStaA1Canal)
	ON_CBN_SELCHANGE(IDC_PROG_STA_A1_CANAL, OnSelchangeProgStaA1Canal)
	ON_CBN_DROPDOWN(IDC_PROG_STA_A1_TA, OnDropdownProgStaA1Ta)
	ON_CBN_DROPDOWN(IDC_PROG_STA_A1_CIX, OnDropdownProgStaA1Cix)
	ON_CBN_SELCHANGE(IDC_PROG_STA_A1_CIX, OnSelchangeProgStaA1Cix)
	ON_CBN_DROPDOWN(IDC_PROG_STA_A1_CH, OnDropdownProgStaA1Ch)
	ON_CBN_SELCHANGE(IDC_PROG_STA_A1_CH, OnSelchangeProgStaA1Ch)
	ON_CBN_DROPDOWN(IDC_PROG_STA_A1_MA, OnDropdownProgStaA1Ma)
	ON_CBN_SELCHANGE(IDC_PROG_STA_A1_MA, OnSelchangeProgStaA1Ma)
	ON_CBN_SELCHANGE(IDC_PROG_STA_A1_CONF, OnSelchangeProgStaA1Conf)
	ON_WM_SETFOCUS()
	ON_BN_CLICKED(IDC_PROG_STA_A1_TST, OnProgStaA1Tst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA_A1 message handlers

BOOL CDlgTRC1752_MOD_PROG_STA_A1::OnInitDialog()
{

	CDialog::OnInitDialog();

	m_A1_TD.AddString("D1");
	m_A1_TD.AddString("D2");
	m_A1_TD.AddString("D5");
	m_A1_TD.AddString("D6");
	m_A1_TD.AddString("INT");

	m_A1_TD.SetCurSel(0);
	m_A1_TA.SetCurSel(0);

	InitialisationStation();

	//	Armement du timer
	//SetTimer(1,1000,NULL);

	return TRUE;
}


void CDlgTRC1752_MOD_PROG_STA_A1::OnTimer(UINT nIDEvent)
{
	CString str;

	CDialog::OnTimer(nIDEvent);

	if (eqp->IsModif()) return;

	AffichageInfosDeux();


	if (nIDEvent == 2)
		RazMessage();

}

//*************************************************
// Validation des choix de l'opérateur - Touche VAL
//*************************************************
void CDlgTRC1752_MOD_PROG_STA_A1::Valide()
{
	//********************************************************
	// Changement impossible quand l'équipement est en Distant
	//********************************************************
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		UpdateData(FALSE);
		return;
	}

	CString tmpMsg, tmpMsgDeux;

	AffichageInfosUn();

	tmpMsg.Empty();
	tmpMsgDeux.Empty();


	// Test Activation
	if (eqp->GetChannelState("A1") == "INACTIVE")
		tmpMsgDeux = eqp->TestActivation("A1");

// Activation/Désactivation de la voie
	if (GetConfA1() == 0 && eqp->GetChannelState("A1") == "INACTIVE")
	{
		tmpMsg = "ACTIVATION  VOIE  A1";

		if (eqp->Activer("A1") == ERR_NON_CONFORME )
		{
			AfxMessageBox("Echec activation");
			tmpMsg = "";
		}
	}
	else if (GetConfA1() == 1 && eqp->GetChannelState("A1") == "ACTIVE")
	{
		initScanSet = FALSE;			// V3.0.1
		tmpMsg = "DESACTIVATION  VOIE  A1";
		if (eqp->Desactiver("A1") == ERR_NON_CONFORME)
		{
			AfxMessageBox("Echec desactivation");
			tmpMsg = "";
		}
	}

	// TODO_A1 -----------------------------
	if (tmpMsg != "" || tmpMsgDeux != "")
	{
		if (tmpMsgDeux == "")
			AfficheMessageUn(tmpMsg);
		else
			AfficheMessageUn(tmpMsgDeux);


		//AfficheMessageDeux(tmpMsgDeux);
		timerMsg = SetTimer(2,5000,NULL);
	}

	UpdateData(FALSE);
	//--------------------------------------

	eqp->SetModif(false);

}

//*****************************
// Modification du Type d'Appel
//*****************************
void CDlgTRC1752_MOD_PROG_STA_A1::OnSelchangeProgStaA1Ta()
{
	//**************************************************************************
	// Eqp en Distant ?
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		m_A1_TA.SelectString(0, eqp->GetChannelType("A1").c_str());
		UpdateData(FALSE);
		return;
	}
	//***************************************************************************

	eqp->SetModif(true);

	//Affichage suivant le sélection du Type d'appel.
	initScanSet = FALSE;			// V3.0.1
	AffichageFonctionTa();
}

void CDlgTRC1752_MOD_PROG_STA_A1::OnDropdownProgStaA1Ta()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_A1::OnSelchangeProgStaA1Td()
{
	//**************************************************************************
	// Eqp en Distant ou Voie Activée
	if (eqp->GetMode() == TRUE || eqp->GetChannelState("A1") == "ACTIVE")
	{
		m_A1_TD.SelectString(0, eqp->GetChannelDataLinkId("A1").c_str());
		UpdateData(FALSE);

		//Voie Active
		if (eqp->GetChannelState("A1") == "ACTIVE")
		{
			AfxMessageBox("Changement impossible quand la voie est Active");
			return;
		}

		//Equipement en Distant
		if (eqp->GetMode() == TRUE)
		{
			AfxMessageBox("Changement impossible quand l'équipement est en Distant");
			return;
		}

		return;
	}
	//***************************************************************************

	eqp->SetModif(true);

	AffichageFonctionTd();
	AffichageFonctionTa();

	CString data;

	m_A1_TD.GetLBText(m_A1_TD.GetCurSel(),data);

	// Chargement du CI associé
	UpdateData(TRUE);
	m_A1_Cix.SelectString(0, (eqp->GetDataLinkAssociatedConfiguration((char*)LPCTSTR(data))).c_str());
	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_PROG_STA_A1::OnDropdownProgStaA1Td()
{
	eqp->SetModif(true);
}

//Affichage en focntion du choix dans Interface données
void CDlgTRC1752_MOD_PROG_STA_A1::AffichageFonctionTd()
{
	CString data;
	m_A1_TD.GetLBText(m_A1_TD.GetCurSel(),data);

	//Affichage suivant la sélection
	if (data == "INT")			//Choix INT
	{
		m_A1_TA.SetCurSel(0);				//Positionné à sans ALE
		m_A1_TA.ShowWindow(FALSE);
		//c_A1_AleIndex.SetCurSel(0);
		m_A1_AleIndex.ShowWindow(FALSE);
		//m_A1_AleIndex = 0;					//Positionné à index 0
	}
	else
	{
		m_A1_TA.ShowWindow(TRUE);
		m_A1_AleIndex.ShowWindow(TRUE);
	}
}

void CDlgTRC1752_MOD_PROG_STA_A1::AffichageFonctionTa()
{
	switch(m_A1_TA.GetCurSel())
	{
	case 0:	//Pas de ALE
		m_A1_AleIndex.ShowWindow(false);
		break;

	case 1:	//ALE avec Scanset
		m_A1_AleIndex.ShowWindow(true);
		//La liste du ComboBox à initialiser avec les valeurs
		//du fichier xxxx.sst
		break;

	case 2:	//ALE avec Canal
		m_A1_AleIndex.ShowWindow(true);
		//La liste du ComboBox à initialiser avec les valeurs
		//du fichier xxxx.rch de la forme 0:50 [index:NrChannel]
		break;

	default:
		//m_A1_AleIndex = 0;
		//m_A1_AleIndex.ShowWindow(false);
		break;
	}

	//Initialisation de la liste ScanSet/Channel suivant le choix [TypeAle/m_A1_TA] - V3.0.1
	if (m_A1_TA.GetCurSel() == 1 || m_A1_TA.GetCurSel() == 2)
	{
		InitialisationListeScanSet(m_A1_TA.GetCurSel());
		m_A1_AleIndex.SetCurSel(0);
	}
}

void CDlgTRC1752_MOD_PROG_STA_A1::AffichageIa(CString mdm) {
	/*Si la voie courante est Inactive, et qu’elle se trouve dans l’état REPOS (pas de configuration
	associée, ou configuration associée configurée à l’état REPOS), le menu se trouve dans l’état
	"modification".

	Si la voie courante est Inactive, et qu'une configuration radio est associée !=REPOS alors le menu
	se trouve dans l'état "activer"
	*/
	if (m_A1_Ia == "I")
	{
		if (mdm == "REPOS")
			m_A1_Conf = 2;
			//c_A1_Conf.SetCurSel(2);
		else
			m_A1_Conf = 0;
			//c_A1_Conf.SetCurSel(0);
	}

	//si la voie courante est Active, le menu se trouve dans l’état « consultation ».
	if (m_A1_Ia == "A")
	{
		//c_A1_Conf.SetCurSel(3);
		m_A1_Conf = 3;
	}

}

//Affichage en focntion du mode
void CDlgTRC1752_MOD_PROG_STA_A1::AffichageFonctionMode(CString mdm)
{
	if (mdm == "FSKV" || mdm == "FSKP" || mdm == "4529")
	{
		m_A1_TA.SetCurSel(0);
		m_A1_TA.ShowWindow(FALSE);
		//m_A1_AleIndex = 0;
		m_A1_AleIndex.ShowWindow(false);
	}

	//REPOS
	if (mdm == "REPOS")
		c_A1_Conf.SetCurSel(2);
}


void CDlgTRC1752_MOD_PROG_STA_A1::OnDropdownProgStaA1Canal()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_A1::OnSelchangeProgStaA1Canal()
{
	//**************************************************************************
	// Eqp en Distant ou Voie Activée
	if (eqp->GetMode() == TRUE || eqp->GetChannelState("A1") == "ACTIVE")
	{
		m_A1_Canal.SelectString(0, (eqp->GetChannelAssociatedAfConfigurationConverted("A1")).c_str());
		UpdateData(FALSE);

		//Voie Active
		if (eqp->GetChannelState("A1") == "ACTIVE")
		{
			AfxMessageBox("Changement impossible quand la voie est Active");
			return;
		}

		//Equipement en Distant
		if (eqp->GetMode() == TRUE)
		{
			AfxMessageBox("Changement impossible quand l'équipement est en Distant");
			return;
		}

		return;
	}
	else
	{
		AffichageInfos();
	}
	//***************************************************************************

	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_A1::OnDropdownProgStaA1Cix()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_A1::OnSelchangeProgStaA1Cix()
{
	//**************************************************************************
	// Eqp en Distant ou Voie Activée
	if (eqp->GetMode() == TRUE || eqp->GetChannelState("A1") == "ACTIVE")
	{
		m_A1_Cix.SelectString(0, (eqp->GetDataLinkAssociatedConfiguration(eqp->GetChannelDataLinkId("A1"))).c_str());
		UpdateData(FALSE);

		//Voie Active
		if (eqp->GetChannelState("A1") == "ACTIVE")
		{
			AfxMessageBox("Changement impossible quand la voie est Active");
			return;
		}

		//Equipement en Distant
		if (eqp->GetMode() == TRUE)
		{
			AfxMessageBox("Changement impossible quand l'équipement est en Distant");
			return;
		}

		return;
	}
	//***************************************************************************

	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_A1::OnDropdownProgStaA1Ch()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_A1::OnSelchangeProgStaA1Ch()
{
	//**************************************************************************
	// Eqp en Distant
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		m_A1_AleIndex.SetCurSel(eqp->GetChannelIndexScansetChannel("A1"));
		UpdateData(FALSE);
		return;
	}
	//***************************************************************************

	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_A1::OnDropdownProgStaA1Ma()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_A1::OnSelchangeProgStaA1Ma()
{
	//**************************************************************************
	// Eqp en Distant ?
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		m_A1_ModeAlternat.SelectString(0, (eqp->GetChannelLinkManagementTypeIhm("A1")).c_str());
		UpdateData(FALSE);
		return;
	}
	//***************************************************************************

	eqp->SetModif(true);
}

//*************************************************************
// Initialisation de la liste des index pour ScanSet ou Channel
//*************************************************************
void CDlgTRC1752_MOD_PROG_STA_A1::InitialisationListeScanSet(int val)
{

	// V3.0.1
	if ( initScanSet == TRUE )
		return;

	initScanSet = TRUE;

	int nb;
	bool trou_table = false;
	CString nr_idx;

	if (eqp->IsRchPresent((char *)LPCTSTR("A1")) == FALSE)				// La table RCH est un minimum
		return;

	// Raz de la table
	m_A1_AleIndex.ResetContent();

	TSst sst;
	TRch rch;

	switch(val)
	{
	case 0:	//Pas de ALE
		break;
	case 1:	//ALE avec Scanset
		// Vérification de la présence de la table
		if (eqp->IsSstPresent((char *)LPCTSTR("A1")) == FALSE)
			break;

		//Lecture de la table des ScanSet
		for (nb = 0; nb<NB_SST; nb++)
		{
			if (eqp->GetSst((char *)LPCTSTR("A1"), nb, sst) == TRUE)
			{
				if ( trou_table == true)
						m_A1_AleIndex.AddString("-");		//Si l'index n'existe pas

				nr_idx.Format(_T("%1d"), nb);
				m_A1_AleIndex.AddString(nr_idx);
				trou_table = false;
			}
			else
				trou_table = true;
		}
		break;
	case 2:	//ALE avec Canal
		//Lecture de la table des Channels
		for (nb = 0; nb<NB_RCH; nb++)
		{
			if (eqp->GetRch((char *)LPCTSTR("A1"), nb, rch) == TRUE)
			{
				if ( trou_table == true)
						m_A1_AleIndex.AddString("-");		//Si l'index n'existe pas

				nr_idx.Format(_T("%01d:%01d"), nb, rch.channel);
				m_A1_AleIndex.AddString(nr_idx);
				trou_table = false;
			}
			else
				trou_table = true;
		}
		break;
	default:
		break;
	}
}

//****************************
//Initialisation de la Station
//§6.6 page 80/124 de la MAE
//****************************
void CDlgTRC1752_MOD_PROG_STA_A1::InitialisationStation()
{
	m_A1_Mode = eqp->GetChannelConfiguration("A1").waveform.c_str();
	c_A1_Conf.SetCurSel(2);
}


void CDlgTRC1752_MOD_PROG_STA_A1::OnSelchangeProgStaA1Conf()
{
	// TODO : Uniquement la CONSULTATION est autorisée si al voie est ACTIVE

	eqp->SetModif(true);
}

//*************************************************
// Retourne l'etat du combobox IDC_PROG_STA_A1_CONF
//*************************************************
int CDlgTRC1752_MOD_PROG_STA_A1::GetConfA1()
{
	return (c_A1_Conf.GetCurSel());
}

//**************************************
// Retourne le canal utilisé par la voie
//**************************************
int CDlgTRC1752_MOD_PROG_STA_A1::GetCanalA1()
{
	return (m_A1_Canal.GetCurSel());
}

//********************************************
// Retourne l'Indicateur d'activité de la voie
//********************************************
int CDlgTRC1752_MOD_PROG_STA_A1::GetIaA1()
{
	int res = 0;

	if (m_A1_Ia == "A")
		res =1;

	return res;
}

void CDlgTRC1752_MOD_PROG_STA_A1::OnSetFocus(CWnd* pOldWnd)
{
	CDialog::OnSetFocus(pOldWnd);
}

//***********************************************
// Affichage des Informations
//***********************************************
void CDlgTRC1752_MOD_PROG_STA_A1::AffichageInfos()
{
	// TODO - Ménage à faire

	AffichageInfosUn();

	AffichageInfosDeux();

}

void CDlgTRC1752_MOD_PROG_STA_A1::AffichageInfosUn()
{
	// Recuperation valeurs des champs
	CString data_link;
	CString cix;
	CString associated_af_conf;
	CString type_appel;
	CString link_management_type;
	CString index;

	m_A1_TA.GetLBText(m_A1_TA.GetCurSel(),type_appel);
	if (type_appel != "-")
		m_A1_AleIndex.GetLBText(m_A1_AleIndex.GetCurSel(),index);

	// Vérification de la sélection des ScanSet/Channel
	if (type_appel != "-" && index =="-")
	{
		if (type_appel == "S")
			AfxMessageBox("Sélection ScanSet non valide !");
		if (type_appel == "C")
			AfxMessageBox("Sélection Canal non valide !");

		m_A1_AleIndex.SetCurSel(0);
		return;
	}

	m_A1_TD.GetLBText(m_A1_TD.GetCurSel(),data_link);
	m_A1_Cix.GetLBText(m_A1_Cix.GetCurSel(),cix);
	m_A1_Canal.GetLBText(m_A1_Canal.GetCurSel(),associated_af_conf);
	m_A1_ModeAlternat.GetLBText(m_A1_ModeAlternat.GetCurSel(),link_management_type);


	// Association cix
	eqp->SetDataLinkAssociatedConfiguration((char*)LPCTSTR(data_link), (char*)LPCTSTR(cix));

	// data link
	eqp->SetChannelDataLinkId("A1", (char*)LPCTSTR(data_link));

	// associated af conf
	eqp->SetChannelAssociatedAfConfiguration("A1", (char*)LPCTSTR(associated_af_conf));

	// type appel
	eqp->SetChannelType("A1", (char*)LPCTSTR(type_appel));

	// link management type
	eqp->SetChannelLinkManagementTypeIhm("A1", (char*)LPCTSTR(link_management_type));

	// index scanset channel
	if (m_A1_AleIndex.GetCount() == 0)
		index = "0";

	if (type_appel == "-")
		eqp->SetChannelIndexScansetChannel("A1", 0);
	else
		eqp->SetChannelIndexScansetChannel("A1", atoi((char*)LPCTSTR(index)));

}
void CDlgTRC1752_MOD_PROG_STA_A1::AffichageInfosDeux()
{
		UpdateData(TRUE);

		/* V3.0.1
		// Remplissage du champ data link en fonction de l'option
		if (eqp->Actif() == FALSE && eqp->GetQuadrivoie() != quadrivoie)
		{
			m_A1_TD.ResetContent();

			quadrivoie = eqp->GetQuadrivoie();

			m_A1_TD.AddString("D1");
			m_A1_TD.AddString("D2");

			if (quadrivoie == true)
			{
				m_A1_TD.AddString("D5");
				m_A1_TD.AddString("D6");
			}

			m_A1_TD.AddString("INT");
			m_A1_TD.SetCurSel(0);
		}
		*/

		// Mise à jour des données
		string data = eqp->GetChannelDataLinkId("A1");

		// Mise à jour du Data Link
		m_A1_TD.SelectString(0, data.c_str());
		AffichageFonctionTd();

		m_A1_Cix.SelectString(0, (eqp->GetDataLinkAssociatedConfiguration(data)).c_str());

		m_A1_Canal.SelectString(0, (eqp->GetChannelAssociatedAfConfigurationConverted("A1")).c_str());

		m_A1_TA.SelectString(0, (eqp->GetChannelType("A1")).c_str());
		AffichageFonctionTa();

		m_A1_ModeAlternat.SelectString(0, (eqp->GetChannelLinkManagementTypeIhm("A1")).c_str());

		char val[2];

		sprintf(val, "%i", eqp->GetChannelIndexScansetChannel("A1"));

		m_A1_AleIndex.SelectString(0, val);

		m_A1_Ia = eqp->GetChannelStateIhm("A1").c_str();
		//AffichageIa();

		//*****************
		//Affichage du mode
		//*****************
		//m_A1_Mode = eqp->GetChannelConfiguration("A1").waveform.c_str();
		CString str;
		m_A1_Canal.GetWindowText(str);

		if (str == "MC")
			m_A1_Mode = eqp->GetChannelConfiguration("A1").waveform.c_str();
		else
			m_A1_Mode = eqp->GetChannelConfiguration(CHANNELS_CONFIGURATION[m_A1_Canal.GetCurSel()]).waveform.c_str();

		// Traitement du BFSK
		if (m_A1_Mode == "BFSK")
			m_A1_Mode = "FSKV";

		AffichageFonctionMode(m_A1_Mode);

		AffichageIa(m_A1_Mode);


		UpdateData(FALSE);

}

void CDlgTRC1752_MOD_PROG_STA_A1::OnProgStaA1Tst()
{
	// TODO: Gestion des tests déclenchés
	// Ces tests déclenchés ne sont accessible qu'en explotation locale.
	// Il interrompent le mode opérationnel en cours sur la voie modem sélectionnée (mais pas les autres voie).
	// Les carractéristiques du mode opérationnel précédent sont restituées aprés le test,
	// mais la voie affectée par le test reste désactivée.

	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Tests impossible quand l'équipement est en Distant");
		UpdateData(FALSE);
		return;
	}

	eqp->VueTst(0);
}

//**************************************************
// Gestion des messages à l'activation de la voie A1
//**************************************************
void CDlgTRC1752_MOD_PROG_STA_A1::RazMessage()
{
	m_MessageUn = "";
	m_MessageDeux = "";
	GetDlgItem(IDC_STA_A1_MSG1)->EnableWindow(FALSE);
	GetDlgItem(IDC_STA_A1_MSG2)->EnableWindow(FALSE);

	KillTimer(timerMsg);

	UpdateData(FALSE);
	eqp->VueOps("A1");
}

void CDlgTRC1752_MOD_PROG_STA_A1::AfficheMessageUn(CString msg)
{
	m_MessageUn = msg;
	GetDlgItem(IDC_STA_A1_MSG1)->EnableWindow(TRUE);
}

void CDlgTRC1752_MOD_PROG_STA_A1::AfficheMessageDeux(CString msg)
{
	m_MessageDeux = msg;
	GetDlgItem(IDC_STA_A1_MSG2)->EnableWindow(TRUE);
}

void CDlgTRC1752_MOD_PROG_STA_A1::StartTimer()
{
	AffichageInfosDeux();	// Affichage avant le démarrage du timer.
	SetTimer(1,1000,NULL);
}

void CDlgTRC1752_MOD_PROG_STA_A1::StopTimer()
{
	KillTimer(1);
}

// Mise à jour de la sélection des interfaces TD - V3.0.1
void CDlgTRC1752_MOD_PROG_STA_A1::MiseJourListeInterfaceTd()
{
		m_A1_TD.ResetContent();

		m_A1_TD.AddString("D1");
		m_A1_TD.AddString("D2");

		if (eqp->GetQuadrivoie() == TRUE)
		{
			m_A1_TD.AddString("D5");
			m_A1_TD.AddString("D6");
		}

		m_A1_TD.AddString("INT");
		m_A1_TD.SetCurSel(0);
}

void CDlgTRC1752_MOD_PROG_STA_A1::AffichageActivation()
{
}
