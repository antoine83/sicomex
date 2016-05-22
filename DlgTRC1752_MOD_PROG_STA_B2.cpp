// DlgTRC1752_MOD_PROG_STA_B2.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_STA_B2.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA_B2 dialog

/*Le menu station affiche ACTIVATION, la voie modem sélectionnée, B2 dans l’exemple cidessus,
n’est pas active pour autant. Seul l’indicateur d’activité (I pour voie Inactive, A pour
voie Active) permet de connaître l’état réel de la voie B2.
Une voie sur laquelle une panne bloquante a été détectée lors d’un autotest n’est plus accessible
au moyen de ce menu.*/


CDlgTRC1752_MOD_PROG_STA_B2::CDlgTRC1752_MOD_PROG_STA_B2(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_STA_B2::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_STA_B2)
	m_B2_Conf = 0;
	m_B2_Mode = _T("MIL110");
	m_MessageUn = _T("");
	m_MessageDeux = _T("");
	//}}AFX_DATA_INIT

	this->eqp = equip;
	quadrivoie = true;
}


void CDlgTRC1752_MOD_PROG_STA_B2::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_STA_B2)
	DDX_Control(pDX, IDC_PROG_STA_B2_CONF, c_B2_Conf);
	DDX_Control(pDX, IDC_STA_B2_MSG2, c_MessageDeux);
	DDX_Control(pDX, IDC_STA_B2_MSG1, c_MessageUn);
	DDX_Control(pDX, IDC_PROG_STA_B2_TD, m_B2_TD);
	DDX_Control(pDX, IDC_PROG_STA_B2_TA, m_B2_TA);
	DDX_Control(pDX, IDC_PROG_STA_B2_MA, m_B2_ModeAlternat);
	DDX_Control(pDX, IDC_PROG_STA_B2_CIX, m_B2_Cix);
	DDX_Control(pDX, IDC_PROG_STA_B2_CH, m_B2_AleIndex);
	DDX_Control(pDX, IDC_PROG_STA_B2_CANAL, m_B2_Canal);
	DDX_Text(pDX, IDC_PROG_STA_B2_IA, m_B2_Ia);
	DDX_CBIndex(pDX, IDC_PROG_STA_B2_CONF, m_B2_Conf);
	DDX_Text(pDX, IDC_PROG_STA_B2_MODE, m_B2_Mode);
	DDV_MaxChars(pDX, m_B2_Mode, 11);
	DDX_Text(pDX, IDC_STA_B2_MSG1, m_MessageUn);
	DDX_Text(pDX, IDC_STA_B2_MSG2, m_MessageDeux);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_STA_B2, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_STA_B2)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_PROG_STA_B2_TA, OnSelchangeProgStaB2Ta)
	ON_CBN_SELCHANGE(IDC_PROG_STA_B2_TD, OnSelchangeProgStaB2Td)
	ON_CBN_DROPDOWN(IDC_PROG_STA_B2_TD, OnDropdownProgStaB2Td)
	ON_CBN_DROPDOWN(IDC_PROG_STA_B2_CANAL, OnDropdownProgStaB2Canal)
	ON_CBN_SELCHANGE(IDC_PROG_STA_B2_CANAL, OnSelchangeProgStaB2Canal)
	ON_CBN_DROPDOWN(IDC_PROG_STA_B2_TA, OnDropdownProgStaB2Ta)
	ON_CBN_DROPDOWN(IDC_PROG_STA_B2_CIX, OnDropdownProgStaB2Cix)
	ON_CBN_SELCHANGE(IDC_PROG_STA_B2_CIX, OnSelchangeProgStaB2Cix)
	ON_CBN_DROPDOWN(IDC_PROG_STA_B2_CH, OnDropdownProgStaB2Ch)
	ON_CBN_SELCHANGE(IDC_PROG_STA_B2_CH, OnSelchangeProgStaB2Ch)
	ON_CBN_DROPDOWN(IDC_PROG_STA_B2_MA, OnDropdownProgStaB2Ma)
	ON_CBN_SELCHANGE(IDC_PROG_STA_B2_MA, OnSelchangeProgStaB2Ma)
	ON_CBN_SELCHANGE(IDC_PROG_STA_B2_CONF, OnSelchangeProgStaB2Conf)
	ON_BN_CLICKED(IDC_PROG_STA_B2_TST, OnProgStaB2Tst)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA_B2 message handlers

BOOL CDlgTRC1752_MOD_PROG_STA_B2::OnInitDialog()
{

	CDialog::OnInitDialog();

	m_B2_TD.AddString("D1");
	m_B2_TD.AddString("D2");
	m_B2_TD.AddString("D5");
	m_B2_TD.AddString("D6");
	m_B2_TD.AddString("INT");

	m_B2_TD.SetCurSel(0);
	m_B2_TA.SetCurSel(0);

	InitialisationStation();


	//	Armement du timer
	SetTimer(1,1000,NULL);

	return TRUE;
}


void CDlgTRC1752_MOD_PROG_STA_B2::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	if (eqp->IsModif()) return;

	AffichageInfosDeux();

	if (nIDEvent == 2)
		RazMessage();
}

void CDlgTRC1752_MOD_PROG_STA_B2::Valide()
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

	AffichageInfosUn();

	CString tmpMsg, tmpMsgDeux;

	AffichageInfosUn();

	tmpMsg.Empty();
	tmpMsgDeux.Empty();


	// Test Activation
	if (eqp->GetChannelState("B2") == "INACTIVE")
		tmpMsgDeux = eqp->TestActivation("B2");

// Activation/Désactivation de la voie
	if (GetConfB2() == 0 && eqp->GetChannelState("B2") == "INACTIVE")
	{
		tmpMsg = "ACTIVATION  VOIE  B2";

		if (eqp->Activer("B2") == ERR_NON_CONFORME)
		{
			AfxMessageBox("Echec activation");
			tmpMsg = "";
		}
	}
	else if (GetConfB2() == 1 && eqp->GetChannelState("B2") == "ACTIVE")
	{
		tmpMsg = "DESACTIVATION  VOIE  B2";
		if (eqp->Desactiver("B2") == ERR_NON_CONFORME)
		{
			AfxMessageBox("Echec desactivation");
			tmpMsg = "";
		}
	}

	// TODO_B2 -----------------------------
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

void CDlgTRC1752_MOD_PROG_STA_B2::OnSelchangeProgStaB2Ta()
{
	//**************************************************************************
	// Eqp en Distant ?
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		m_B2_TA.SelectString(0, eqp->GetChannelType("B2").c_str());
		UpdateData(FALSE);
		return;
	}
	//***************************************************************************
	eqp->SetModif(true);

	//Affichage suivant le sélection du Type d'appel.
	AffichageFonctionTa();
}

void CDlgTRC1752_MOD_PROG_STA_B2::OnDropdownProgStaB2Ta()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_B2::OnSelchangeProgStaB2Td()
{
	//**************************************************************************
	// Eqp en Distant ou Voie Activée
	if (eqp->GetMode() == TRUE || eqp->GetChannelState("B2") == "ACTIVE")
	{
		m_B2_TD.SelectString(0, eqp->GetChannelDataLinkId("B2").c_str());
		UpdateData(FALSE);

		//Voie Active
		if (eqp->GetChannelState("B2") == "ACTIVE")
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

	m_B2_TD.GetLBText(m_B2_TD.GetCurSel(),data);

	// Chargement du CI associé
	UpdateData(TRUE);
	m_B2_Cix.SelectString(0, (eqp->GetDataLinkAssociatedConfiguration((char*)LPCTSTR(data))).c_str());
	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_PROG_STA_B2::OnDropdownProgStaB2Td()
{
	eqp->SetModif(true);
}

//Affichage en focntion du choix dans Interface données
void CDlgTRC1752_MOD_PROG_STA_B2::AffichageFonctionTd()
{
	CString data;
	m_B2_TD.GetLBText(m_B2_TD.GetCurSel(),data);

	//Affichage suivant la sélection
	if (data == "INT")			//Choix INT
	{
		m_B2_TA.SetCurSel(0);				//Positionné à sans ALE
		m_B2_TA.ShowWindow(FALSE);
		m_B2_AleIndex.ShowWindow(FALSE);
	}
	else
	{
		m_B2_TA.ShowWindow(TRUE);
		m_B2_AleIndex.ShowWindow(TRUE);
	}
}

void CDlgTRC1752_MOD_PROG_STA_B2::AffichageFonctionTa()
{
	//Pas d'ALE sur la voie B2
	m_B2_TA.SetCurSel(0);
	m_B2_AleIndex.ShowWindow(false);
	return;

	switch(m_B2_TA.GetCurSel())
	{
	case 0:	//Pas de ALE
		m_B2_AleIndex.ShowWindow(false);
		break;

	case 1:	//ALE avec Scanset
		m_B2_AleIndex.ShowWindow(true);

		//La liste du ComboBox à initialiser avec les valeurs
		//du fichier xxxx.sst

		break;

	case 2:	//ALE avec Canal
		m_B2_AleIndex.ShowWindow(true);

		//La liste du ComboBox à initialiser avec les valeurs
		//du fichier xxxx.rch

		break;

	default:
		//m_B2_AleIndex = 0;
		//m_B2_AleIndex.ShowWindow(false);
		break;
	}
}

void CDlgTRC1752_MOD_PROG_STA_B2::AffichageIa(CString mdm) {
	/*Si la voie courante est Inactive, et qu’elle se trouve dans l’état REPOS (pas de configuration
	associée, ou configuration associée configurée à l’état REPOS), le menu se trouve dans l’état
	"modification".
	Si la voie courante est Inactive, et qu'une configuration radio est associée !=REPOS alors le menu
	se trouve dans l'état "activer"
	*/
	if (m_B2_Ia == "I")
	{
		if (mdm == "REPOS")
			m_B2_Conf = 2;
		else
			m_B2_Conf = 0;
	}

	//si la voie courante est Active, le menu se trouve dans l’état « consultation ».
	if (m_B2_Ia == "A")
	{
		m_B2_Conf = 3;
	}
}

//Affichage en focntion du mode
void CDlgTRC1752_MOD_PROG_STA_B2::AffichageFonctionMode(CString mdm)
{
	if (mdm == "FSKV" || mdm == "FSKP" || mdm == "4529")
	{
		m_B2_TA.SetCurSel(0);
		m_B2_TA.ShowWindow(FALSE);
		//m_B2_AleIndex = 0;
		m_B2_AleIndex.ShowWindow(false);
	}
}


void CDlgTRC1752_MOD_PROG_STA_B2::OnDropdownProgStaB2Canal()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_B2::OnSelchangeProgStaB2Canal()
{
	//**************************************************************************
	// Eqp en Distant ou Voie Activée
	if (eqp->GetMode() == TRUE || eqp->GetChannelState("B2") == "ACTIVE")
	{
		m_B2_Canal.SelectString(0, (eqp->GetChannelAssociatedAfConfigurationConverted("B2")).c_str());
		UpdateData(FALSE);

		//Voie Active
		if (eqp->GetChannelState("B2") == "ACTIVE")
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

void CDlgTRC1752_MOD_PROG_STA_B2::OnDropdownProgStaB2Cix()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_B2::OnSelchangeProgStaB2Cix()
{
	//**************************************************************************
	// Eqp en Distant ou Voie Activée
	if (eqp->GetMode() == TRUE || eqp->GetChannelState("B2") == "ACTIVE")
	{
		m_B2_Cix.SelectString(0, (eqp->GetDataLinkAssociatedConfiguration(eqp->GetChannelDataLinkId("B2"))).c_str());
		UpdateData(FALSE);

		//Voie Active
		if (eqp->GetChannelState("B2") == "ACTIVE")
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

void CDlgTRC1752_MOD_PROG_STA_B2::OnDropdownProgStaB2Ch()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_B2::OnSelchangeProgStaB2Ch()
{
	//**************************************************************************
	// Eqp en Distant ?
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		m_B2_AleIndex.SetCurSel(eqp->GetChannelIndexScansetChannel("B2"));
		UpdateData(FALSE);
		return;
	}
	//***************************************************************************

	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_B2::OnDropdownProgStaB2Ma()
{
	eqp->SetModif(true);
}

void CDlgTRC1752_MOD_PROG_STA_B2::OnSelchangeProgStaB2Ma()
{
	//**************************************************************************
	// Eqp en Distant ?
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		m_B2_ModeAlternat.SelectString(0, (eqp->GetChannelLinkManagementTypeIhm("B2")).c_str());
		UpdateData(FALSE);
		return;
	}
	//***************************************************************************

	eqp->SetModif(true);
}

//****************************
//Initialisation de la Station
//****************************
void CDlgTRC1752_MOD_PROG_STA_B2::InitialisationStation()
{
	m_B2_Mode = eqp->GetChannelConfiguration("B2").waveform.c_str();
	c_B2_Conf.SetCurSel(2);
}

void CDlgTRC1752_MOD_PROG_STA_B2::OnSelchangeProgStaB2Conf()
{
	// TODO : Uniquement la CONSULTATION est autorisée si al voie est ACTIVE
	eqp->SetModif(true);

}

//*************************************************
// Retourne l'etat du combobox IDC_PROG_STA_B2_CONF
//*************************************************
int CDlgTRC1752_MOD_PROG_STA_B2::GetConfB2()
{
	return (c_B2_Conf.GetCurSel());
}

//**************************************
// Retourne le canal utilisé par la voie
//**************************************
int CDlgTRC1752_MOD_PROG_STA_B2::GetCanalB2()
{
	return (m_B2_Canal.GetCurSel());
}

//********************************************
// Retourne l'Indicateur d'activité de la voie
//********************************************
int CDlgTRC1752_MOD_PROG_STA_B2::GetIaB2()
{
	int res = 0;

	if (m_B2_Ia == "A")
		res =1;

	return res;
}

//***********************************************
// Affichage des Informations
//***********************************************
void CDlgTRC1752_MOD_PROG_STA_B2::AffichageInfos()
{
	// TODO - Ménage à faire

	AffichageInfosUn();

	AffichageInfosDeux();

}

void CDlgTRC1752_MOD_PROG_STA_B2::AffichageInfosUn()
{
	// Recuperation valeurs des champs
	CString data_link;
	CString cix;
	CString associated_af_conf;
	CString type_appel;
	CString link_management_type;
	CString index;

	m_B2_TA.GetLBText(m_B2_TA.GetCurSel(),type_appel);
	if (type_appel != "-")
		m_B2_AleIndex.GetLBText(m_B2_AleIndex.GetCurSel(),index);

	// Vérification de la sélection des ScanSet/Channel
	if (type_appel != "-" && index =="-")
	{
		if (type_appel == "S")
			AfxMessageBox("Sélection ScanSet non valide !");
		if (type_appel == "C")
			AfxMessageBox("Sélection Canal non valide !");

		m_B2_AleIndex.SetCurSel(0);
		return;
	}

	m_B2_TD.GetLBText(m_B2_TD.GetCurSel(),data_link);
	m_B2_Cix.GetLBText(m_B2_Cix.GetCurSel(),cix);
	m_B2_Canal.GetLBText(m_B2_Canal.GetCurSel(),associated_af_conf);
	m_B2_ModeAlternat.GetLBText(m_B2_ModeAlternat.GetCurSel(),link_management_type);

	// Association cix
	eqp->SetDataLinkAssociatedConfiguration((char*)LPCTSTR(data_link), (char*)LPCTSTR(cix));

	// data link
	eqp->SetChannelDataLinkId("B2", (char*)LPCTSTR(data_link));

	// associated af conf
	eqp->SetChannelAssociatedAfConfiguration("B2", (char*)LPCTSTR(associated_af_conf));

	// type appel
	eqp->SetChannelType("B2", (char*)LPCTSTR(type_appel));

	// link management type
	eqp->SetChannelLinkManagementTypeIhm("B2", (char*)LPCTSTR(link_management_type));

	// index scanset channel
	if (m_B2_AleIndex.GetCount() == 0)
		index = "0";

	if (type_appel == "-")
		eqp->SetChannelIndexScansetChannel("B2", 0);
	else
		eqp->SetChannelIndexScansetChannel("B2", atoi((char*)LPCTSTR(index)));

}
void CDlgTRC1752_MOD_PROG_STA_B2::AffichageInfosDeux()
{
		UpdateData(TRUE);

		// Remplissage du champ data link en fonction de l'option
		if (eqp->Actif() == FALSE && eqp->GetQuadrivoie() != quadrivoie)
		{
			m_B2_TD.ResetContent();

			quadrivoie = eqp->GetQuadrivoie();

			m_B2_TD.AddString("D1");
			m_B2_TD.AddString("D2");

			if (quadrivoie == true)
			{
				m_B2_TD.AddString("D5");
				m_B2_TD.AddString("D6");
			}

			m_B2_TD.AddString("INT");
			m_B2_TD.SetCurSel(0);
		}

		// Mise à jour des données

		string data = eqp->GetChannelDataLinkId("B2");

		// Mise à jour du Data Link
		m_B2_TD.SelectString(0, data.c_str());
		AffichageFonctionTd();

		m_B2_Cix.SelectString(0, (eqp->GetDataLinkAssociatedConfiguration(data)).c_str());

		m_B2_Canal.SelectString(0, (eqp->GetChannelAssociatedAfConfigurationConverted("B2")).c_str());

		m_B2_TA.SelectString(0, (eqp->GetChannelType("B2")).c_str());
		AffichageFonctionTa();

		m_B2_ModeAlternat.SelectString(0, (eqp->GetChannelLinkManagementTypeIhm("B2")).c_str());

		char val[2];

		sprintf(val, "%i", eqp->GetChannelIndexScansetChannel("B2"));

		m_B2_AleIndex.SelectString(0, val);

		m_B2_Ia = eqp->GetChannelStateIhm("B2").c_str();
		//AffichageIa();

		//*****************
		//Affichage du mode
		//*****************
		//m_B2_Mode = eqp->GetChannelConfiguration("B2").waveform.c_str();
		CString str;
		m_B2_Canal.GetWindowText(str);

		if (str == "MC")
			m_B2_Mode = eqp->GetChannelConfiguration("B2").waveform.c_str();
		else
			m_B2_Mode = eqp->GetChannelConfiguration(CHANNELS_CONFIGURATION[m_B2_Canal.GetCurSel()]).waveform.c_str();

		// Traitement du BFSK
		if (m_B2_Mode == "BFSK")
			m_B2_Mode = "FSKV";

		AffichageFonctionMode(m_B2_Mode);

		AffichageIa(m_B2_Mode);


		UpdateData(FALSE);

}
void CDlgTRC1752_MOD_PROG_STA_B2::OnProgStaB2Tst()
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

	eqp->VueTst(3);

}

//**************************************************
// Gestion des messages à l'activation de la voie B2
//**************************************************
void CDlgTRC1752_MOD_PROG_STA_B2::RazMessage()
{
	m_MessageUn = "";
	m_MessageDeux = "";
	GetDlgItem(IDC_STA_B2_MSG1)->EnableWindow(FALSE);
	GetDlgItem(IDC_STA_B2_MSG2)->EnableWindow(FALSE);

	KillTimer(timerMsg);

	UpdateData(FALSE);
	eqp->VueOps("B2");
}

void CDlgTRC1752_MOD_PROG_STA_B2::AfficheMessageUn(CString msg)
{
	m_MessageUn = msg;
	GetDlgItem(IDC_STA_B2_MSG1)->EnableWindow(TRUE);
}

void CDlgTRC1752_MOD_PROG_STA_B2::AfficheMessageDeux(CString msg)
{
	m_MessageDeux = msg;
	GetDlgItem(IDC_STA_B2_MSG2)->EnableWindow(TRUE);
}

void CDlgTRC1752_MOD_PROG_STA_B2::StartTimer()
{
	SetTimer(1,1000,NULL);
}

void CDlgTRC1752_MOD_PROG_STA_B2::StopTimer()
{
	KillTimer(1);
}


// Mise à jour de la sélection des interfaces TD - V3.0.1
void CDlgTRC1752_MOD_PROG_STA_B2::MiseJourListeInterfaceTd()
{
		m_B2_TD.ResetContent();

		m_B2_TD.AddString("D1");
		m_B2_TD.AddString("D2");

		if (eqp->GetQuadrivoie() == TRUE)
		{
			m_B2_TD.AddString("D5");
			m_B2_TD.AddString("D6");
		}

		m_B2_TD.AddString("INT");
		m_B2_TD.SetCurSel(0);
}
