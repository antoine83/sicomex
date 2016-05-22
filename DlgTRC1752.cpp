// DlgTRC1752.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "Equip\EquipM1752.h"
#include "DlgTRC1752.h"
#include "DlgAide.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_TRC1752[];
extern char glob_REPERTOIRE[];


//#include <sstream>
/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752 dialog


CDlgTRC1752::CDlgTRC1752(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDlgTRC1752::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752)
	m_err_retard = _T("");
	m_tempo = _T("");
	m_periode = _T("");
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDB_MDM_1752);
	actif = false;
}


void CDlgTRC1752::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752)
	DDX_Control(pDX, IDC_CHECK_SYNCHRO, m_synchro);
	DDX_Control(pDX, IDC_CHECK_CYCLE, m_cycle);
	DDX_Control(pDX, IDC_MES_STATUT, m_liste_message);
	DDX_Text(pDX, IDC_RETARD, m_err_retard);
	DDX_Text(pDX, IDC_EDIT_TEMPO, m_tempo);
	DDX_Text(pDX, IDC_EDIT_CYCLE, m_periode);
    DDX_Control(pDX, IDC_ACTIVITE, m_activite);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_VAL, OnVal)
	ON_BN_CLICKED(IDC_ESC, OnEsc)
	ON_BN_CLICKED(IDC_LOC, OnLoc)
	ON_BN_CLICKED(IDC_PROG, OnProg)
	ON_BN_CLICKED(IDC_EUA, OnEua)
	//}}AFX_MSG_MAP

	// Activation des tache de comm
	ON_COMMAND(IDC_ACTIVITE, OnActivite)

	// Aide
	ON_COMMAND(ID__AIDE, OnAide)

	// Masquage de l'ecran de controle
	ON_COMMAND(ID_AFF_CONTROLE, OnClose)

	// Envoi de trame
	ON_BN_CLICKED(IDC_ENVOI_TRAME, OnEnvoiTrame)

	// Contexte d'exploitation
	ON_COMMAND(ID_CONTEXTE_OUVRIR, OnOuvrir)
	ON_COMMAND(ID_CONTEXTE_SAUVER, OnSauver)

	// journal
	ON_COMMAND(ID_JOURNAL_COUPER, OnCouper)
	ON_COMMAND(ID_JOURNAL_COUPERTOUT, OnCouperTout)
	ON_COMMAND(ID_JOURNAL_ENREGISTRERSOUS, OnSauvegarde)
	ON_BN_CLICKED(IDC_PRECEDENT, OnPrecedent)
	ON_BN_CLICKED(IDC_SUIVANT, OnSuivant)
	ON_LBN_DBLCLK(IDC_JOURNAL, OnDblclkJournal)

	// Sequence de message : fonction definies dans la classe de base
	ON_BN_CLICKED(IDC_AJOUT_MESSAGE, OnAjoutMessage)
	ON_BN_CLICKED(IDC_RETIRE_MESSAGE, OnRetireMessage)
	ON_BN_CLICKED(IDC_CHECK_CYCLE, OnCheckCycle)
	ON_BN_CLICKED(IDC_CHECK_SYNCHRO, OnCheckSynchro)
	ON_EN_KILLFOCUS(IDC_EDIT_CYCLE, OnKillfocusEditCycle)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMPO, OnKillfocusEditTempo)
	ON_BN_CLICKED(IDC_ENVOI_STATUT, OnEnvoiStatut)
	ON_BN_CLICKED(IDC_ARRET_STATUT, OnArretStatut)

	//Passage en LOCAL
	ON_BN_CLICKED(IDC_LOC, OnTc)

END_MESSAGE_MAP()

/* **************************************************************************
METHODE :		OnAide()
TRAITEMENT:		Boite de dialogue d'aide
***************************************************************************	*/
void CDlgTRC1752::OnAide()
{
	//int			iResult;
	CDlgAide	win;

	HINSTANCE nerror;
    CString strOutputName;

	strOutputName.Format("%s",glob_REPERTOIRE);
	strOutputName = strOutputName + glob_HELP_TRC1752;

    if((nerror=ShellExecute(AfxGetMainWnd()->m_hWnd,
        "open",
        strOutputName,
        NULL,
        NULL,
        SW_SHOWNORMAL))<=(HINSTANCE)32)
    {
        CString mess;
        mess.Format("Impossible de Modifier ou d'Ouvrir le Document:\n%s Erreur n°:%d",
            strOutputName,nerror);
        AfxMessageBox(mess,MB_ICONEXCLAMATION);
    }

}

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752 message handlers

BOOL CDlgTRC1752::OnInitDialog()
{
	t_ComErreur	err;
	char	buf[10];

	CDialog::OnInitDialog();

	//	Armement du timer
	SetTimer(1,1000,NULL);

	// Gestion des erreurs de communication
	// ************************************
	equip->RetourneComErreur(&err);

	sprintf(buf,"%d",err.retard);
	m_err_retard = buf;

	sprintf(buf,"%d",equip->Periode());
	m_periode = buf;

	//m_parite.SetCheck(err.controle_parite);

	// Envoi de sequence de message
	// ****************************
	GetDlgItem(IDC_ENVOI_STATUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARRET_STATUT)->EnableWindow(FALSE);

	sprintf(buf,"%d",equip->DureeTempo());
	m_tempo = buf;

	m_cycle.SetCheck(equip->EnvoiCyclique());
	m_synchro.SetCheck(equip->Synchronise());


	//Initialisation de la liste des commandes de sequence
	InitListeCommande();


    m_Mod = new CDlgTRC1752_MOD((CEquipM1752*)equip);
    m_Mod->Create(CDlgTRC1752_MOD::IDD, this);
    m_Mod->ShowWindow(SW_SHOW);



	UpdateData(FALSE);

	//Initialiasation des boutons
	AffichageBoutons(FALSE);
	/*
	GetDlgItem(IDC_PROG)->EnableWindow(FALSE);
	GetDlgItem(IDC_LOC)->EnableWindow(FALSE);
	GetDlgItem(IDC_VAL)->EnableWindow(FALSE);
	GetDlgItem(IDC_ESC)->EnableWindow(FALSE);
	GetDlgItem(IDC_EUA)->EnableWindow(FALSE);
	*/

	return TRUE;
}

void CDlgTRC1752::OnEnvoiStatut()
{
	CDlgEquip::OnEnvoiStatut();

	m_Mod->m_Tab.SelectTab(1);
	m_Mod->m_ModProg->m_ModProgTab.SelectTab(4);
}

/* **************************************************************************
METHODE :		OnTimer(UINT nIDEvent)
TRAITEMENT:		Rafraichissement de l'ecran de controle
***************************************************************************	*/
void CDlgTRC1752::OnTimer(UINT nIDEvent)
{
    UpdateData(TRUE);

	CDialog::OnTimer(nIDEvent);

	// Rafraichissement des controles commun
	CDlgEquip::OnTimer();

	//Affichage des boutons du TRC1752
	//if ( (((CEquipM1752*)equip)->Actif() == TRUE || ((CEquipM1752*)equip)->IsEnTest() == TRUE) != actif )

	if ( (((CEquipM1752*)equip)->IsEnTest() != TRUE) != actif )
	{
		actif = !actif;

		AffichageBoutons(actif);
	}

	if ( ((CEquipM1752*)equip)->Actif() != TRUE)// || ((CEquipM1752*)equip)->Panne() != DEFAULT_INT_VALUE
	//	|| ((CEquipM1752*)equip)->IsEnTest() == TRUE)
	{
		AffichageBoutons(FALSE);
	} //else AffichageBoutons(TRUE);


	UpdateData(FALSE);
}

//*************************
// Action sur le bouton VAL
//*************************
void CDlgTRC1752::OnVal()
{
	int tmpConf;	//int tmpConf, tmpIa;
	string tmpCanal;

	UpdateData(TRUE);

	// On parcours les onglets pour trouver l'onglet courant
	switch (m_Mod->m_Tab.GetCurSel())
	{
	case 0 : //Ops
		m_Mod->m_ModOps->Valide();
		break;
	case 1 : // Programmation
		switch (m_Mod->m_ModProg->m_ModProgTab.GetCurSel())
		{
		case 0 : // Prog_Station
			switch(m_Mod->m_ModProg->m_ModProgSta->m_ProgStaTab.GetCurSel())
			{
			case 0 : // A1
				tmpConf = m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaA1->GetConfA1();
				tmpCanal = ((CEquipM1752*)equip)->GetChannelAssociatedAfConfiguration("A1");

				// La voie est déjà activée.
				if (tmpConf == 0 && ((CEquipM1752*)equip)->GetChannelState("A1") == "ACTIVE")
					break;

				// Modification de la Voie
				if (tmpConf == 2)
				{
					((CEquipM1752*)equip)->SetChannelAssociatedAfConfigurationModified("A1");

					// Modification de la configuration
					m_Mod->m_Tab.SelectTab(1);									// Programmation
					m_Mod->m_ModProg->m_ModProgTab.SelectTab(1);				// Prog_Configuration
					m_Mod->m_ModProg->m_ModProgConf->Modification("A1");
				}

				if (tmpConf == 3)
				{
					// Affichage de la configuration
					m_Mod->m_Tab.SelectTab(1);									// Programmation
					m_Mod->m_ModProg->m_ModProgTab.SelectTab(1);				// Prog_Configuration
					m_Mod->m_ModProg->m_ModProgConf->Consultation(tmpCanal);
				}

				// Activation DéActivation de la voie
				if (tmpConf != 2 && tmpConf != 3) //
					m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaA1->Valide();

				break;
			case 1 : // A2
				tmpConf = m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaA2->GetConfA2();
				tmpCanal = ((CEquipM1752*)equip)->GetChannelAssociatedAfConfigurationConverted("A2");

				// La voie est déjà activée.
				if (tmpConf == 0 && ((CEquipM1752*)equip)->GetChannelState("A2") == "ACTIVE")
					break;

				// Modification de la Voie
				if (tmpConf == 2)
				{
					((CEquipM1752*)equip)->SetChannelAssociatedAfConfigurationModified("A2");

					// Modification de la configuration
					m_Mod->m_Tab.SelectTab(1);									// Programmation
					m_Mod->m_ModProg->m_ModProgTab.SelectTab(1);				// Prog_Configuration
					m_Mod->m_ModProg->m_ModProgConf->Modification("A2");
				}

				// Consultation de la Voie
				if (tmpConf == 3 )
				{
					// Affichage de la configuration
					m_Mod->m_Tab.SelectTab(1);									// Programmation
					m_Mod->m_ModProg->m_ModProgTab.SelectTab(1);				// Prog_Configuration
					m_Mod->m_ModProg->m_ModProgConf->Consultation(tmpCanal);
				}

				// Activation DéActivation de la voie
				if (tmpConf != 2 && tmpConf != 3)
					m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaA2->Valide();

				break;
			case 2 : // B1
				tmpConf = m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaB1->GetConfB1();
				tmpCanal = ((CEquipM1752*)equip)->GetChannelAssociatedAfConfigurationConverted("B1");

				// La voie est déjà activée.
				if (tmpConf == 0 && ((CEquipM1752*)equip)->GetChannelState("B1") == "ACTIVE")
					break;

				// Modification de la Voie
				if (tmpConf == 2)
				{
					((CEquipM1752*)equip)->SetChannelAssociatedAfConfigurationModified("B1");

					// Modification de la configuration
					m_Mod->m_Tab.SelectTab(1);									// Programmation
					m_Mod->m_ModProg->m_ModProgTab.SelectTab(1);				// Prog_Configuration
					m_Mod->m_ModProg->m_ModProgConf->Modification("B1");
				}

				// Consultation de la Voie
				if (tmpConf == 3 )
				{
					// Affichage de la configuration
					m_Mod->m_Tab.SelectTab(1);									// Programmation
					m_Mod->m_ModProg->m_ModProgTab.SelectTab(1);				// Prog_Configuration
					m_Mod->m_ModProg->m_ModProgConf->Consultation(tmpCanal);
				}

				// Activation DéActivation de la voie
				if (tmpConf != 2 && tmpConf != 3)
					m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaB1->Valide();

				break;
			case 3 : // B2
				tmpConf = m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaB2->GetConfB2();
				tmpCanal = ((CEquipM1752*)equip)->GetChannelAssociatedAfConfigurationConverted("B2");

				// La voie est déjà activée.
				if (tmpConf == 0 && ((CEquipM1752*)equip)->GetChannelState("B2") == "ACTIVE")
					break;

				// Modification de la Voie
				if (tmpConf == 2)
				{
					((CEquipM1752*)equip)->SetChannelAssociatedAfConfigurationModified("B2");

					// Modification de la configuration
					m_Mod->m_Tab.SelectTab(1);									// Programmation
					m_Mod->m_ModProg->m_ModProgTab.SelectTab(1);				// Prog_Configuration
					m_Mod->m_ModProg->m_ModProgConf->Modification("B2");
				}

				// Consultation de la Voie
				if (tmpConf == 3 )
				{
					// Affichage de la configuration
					m_Mod->m_Tab.SelectTab(1);									// Programmation
					m_Mod->m_ModProg->m_ModProgTab.SelectTab(1);				// Prog_Configuration
					m_Mod->m_ModProg->m_ModProgConf->Consultation(tmpCanal);
				}

				// Activation DéActivation de la voie
				if (tmpConf != 2 && tmpConf != 3)
					m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaB2->Valide();

				break;
			case 4 : // Test
				m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaTst->Valide();
				break;
			default:
				break;
			}
			break;
		case 1 :	// Prog_Configuration
			m_Mod->m_ModProg->m_ModProgConf->Valide();
			break;
		case 2:		// Prog_ALE
			switch(m_Mod->m_ModProg->m_ModProgAle->m_ModProgTab.GetCurSel())
			{
			case 0 : // SYSTEMPARAM
				m_Mod->m_ModProg->m_ModProgAle->m_ModProgAleSys->Valide();
				break;
			case 1 : // CALLPARAM
				m_Mod->m_ModProg->m_ModProgAle->m_ModProgAleCall->Valide();
				break;
			case 2 : // GEST_TABLE
				m_Mod->m_ModProg->m_ModProgAle->m_ModProgAleTab->Valide();
				break;
			case 3 : // PROTECT_LIEN
				m_Mod->m_ModProg->m_ModProgAle->m_ModProgAleLp->Valide();
				break;
			default:
				break;
			}
			break;
		case 3 :	// Prog_Interface
			switch(m_Mod->m_ModProg->m_ModProgIntf->m_ModProgTab.GetCurSel())
			{
			case 0 : // Association
				m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfAss->Valide();
				break;
			case 1 : // Liaison Séries Données
				m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfLias->Valide();
				break;
			case 2 : // Interface de Télécommande
				m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfTc->Valide();
				break;
			case 3 : // Pilote
				m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfPil->Valide();
				break;
			case 4 : // Interface BF
				m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfBf->Valide();
				break;
			default:
				break;
			}
			break;
		case 4:		// Prog_AutoTest
			m_Mod->m_ModProg->m_ModProgStst->Valide();
			break;
		case 5:		// Prog_Environnement
			break;
		case 6 :	// Prog_Gestion TCL
			m_Mod->m_ModProg->m_ModProgTc->Valide();
			break;
		default:
			break;
		}
		break;
	case 2 : // Configuration
		switch (m_Mod->m_ModConf->m_ModConfTab.GetCurSel())
		{
		case 0 : // Environnement
			//m_Mod->m_ModConf->m_ModConfEnv->Valide();
			break;
		case 4 : // Radio
			m_Mod->m_ModConf->m_ModConfRdo->Valide();
			break;
		default :
			break;
		}
		break;
	default :
		break;
	}
}

//*************************
// Action sur le Bouton ESC
//*************************
void CDlgTRC1752::OnEsc()
{

	if (m_Mod->m_Tab.GetCurSel() == 1
		&& m_Mod->m_ModProg->m_ModProgTab.GetCurSel() == 0
		&& m_Mod->m_ModProg->m_ModProgSta->m_ProgStaTab.GetCurSel() == 4)
			m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaTst->Esc();

	switch (m_Mod->m_Tab.GetCurSel())
	{
	case 0 : //Ops
		m_Mod->m_ModOps->razOffsetFrequences();
		break;
	}

	// Mise à zero des onglets et choix divers.
	InitOnglets();


	// Ops
	m_Mod->m_Tab.SelectTab(0);

	((CEquipM1752*)equip)->SetModif(false);
}

void CDlgTRC1752::OnLoc()
{
	// Action que si on est en distant
	if (((CEquipM1752*)equip)->GetMode() == false) return;

	// Verifier si on est en test
	((CEquipM1752*)equip)->SetMode(false, true);

	// Mise à zero des onglets et choix divers.
	InitOnglets();

	// Ops
	m_Mod->m_Tab.SelectTab(0);
}

/************************************
// Liste des commandes de sequence
*************************************/
void CDlgTRC1752::InitListeCommande()
{
	// Liste des commandes - MAE page 114/124
	/*
	m_liste_message.AddString("AUTRE_ERR_INCIDENT 0x0000");
	m_liste_message.AddString("ERR_ADDRESS_ERROR 0x0001");
	m_liste_message.AddString(".............");
	m_liste_message.AddString("ERR_VAL_DISPLAY 0x0901");
	m_liste_message.AddString("ERR_VAL_STATLOC 0x0902");
	*/
	string error;
	for (int i=0; i<NB_ERREURS; i++)
	{
		error = ((CEquipM1752*)equip)->erreurs[i].erreur + " " + ((CEquipM1752*)equip)->erreurs[i].code;
		m_liste_message.AddString( error.c_str() );
	}
}

void CDlgTRC1752::OnProg()
{
	// Clique sur le bouton PROG
	m_Mod->m_Tab.SelectTab(1);									// Programmation
	m_Mod->m_ModProg->m_ModProgTab.SelectTab(0);				// Prog_Station
	m_Mod->m_ModProg->m_ModProgSta->m_ProgStaTab.SelectTab(0);	// Prog_Station_A1
	m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaA1->StartTimer();
}


void CDlgTRC1752::InitOnglets()
{
	// ***********************************************************
	// Mise à zero des onglets et choix divers.
	// ***********************************************************
	if (!((CEquipM1752*)equip)->GetTest("A1"))
		m_Mod->m_ModProg->m_ModProgSta->m_ProgStaTab.SelectTab(0);						// Prog_Station_A1
	else
		if (!((CEquipM1752*)equip)->GetTest("A2"))
			m_Mod->m_ModProg->m_ModProgSta->m_ProgStaTab.SelectTab(1);						// Prog_Station_A2
		else
			if (!((CEquipM1752*)equip)->GetTest("B1"))
				m_Mod->m_ModProg->m_ModProgSta->m_ProgStaTab.SelectTab(2);						// Prog_Station_B1
			else
				if (!((CEquipM1752*)equip)->GetTest("B2"))
					m_Mod->m_ModProg->m_ModProgSta->m_ProgStaTab.SelectTab(3);						// Prog_Station_B2

	m_Mod->m_ModProg->m_ModProgConf->razChoixCanal();								// Prog_Configuration
	m_Mod->m_ModProg->m_ModProgConf->arretTimer();									// Arret du Timer Conf
	m_Mod->m_ModProg->m_ModProgAle->m_ModProgTab.SelectTab(0);						// Prog_ALE
	m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfLias->razChoixConfiguration();	// Liaison Séries Données
	m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfLias->arretTimer();				// Arret du Timer Lias
	m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfBf->razChoixInterfaceBF();		// Interface BF
	m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfBf->arretTimer();					// Arret du Timer BF
	m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfTc->razChoixInterfaceTC();		// Interface TC
	m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfTc->arretTimer();					// Arret du Timer TC
	m_Mod->m_ModProg->m_ModProgIntf->m_ModProgTab.SelectTab(0);						// Interface
	m_Mod->m_ModProg->m_ModProgTab.SelectTab(0);									// Programmation
	m_Mod->m_ModConf->m_ModConfTab.SelectTab(0);									// Configuration
	m_Mod->m_ModProg->m_ModProgIntf->m_ModProgIntfAss->razChoixDataLink();			// Interface Association
	m_Mod->m_ModProg->m_ModProgAle->m_ModProgTab.SelectTab(0);						// Prog_ALE_SYSTEMPARAM
	m_Mod->m_ModProg->m_ModProgAle->m_ModProgAleSys->RazCanal();
	m_Mod->m_ModProg->m_ModProgAle->m_ModProgAleSys->arretTimer();					// Arret du Timer SYSTEMPARAM
	m_Mod->m_ModProg->m_ModProgAle->m_ModProgAleCall->arretTimer();					// Arret du Timer CALLPARAM
	m_Mod->m_ModProg->m_ModProgAle->m_ModProgAleLp->arretTimer();					// Arret du Timer LP
	// *****************************************************************
	// TODO - Pour Affichage de la Voie A1 si ESC
	//m_Mod->m_ModOps->razChoixConfiguration();

}

void CDlgTRC1752::OnEua()
{
	// Passage de l'équipement en Local
	//((CEquipM1752*)equip)->SetMode(false, true);

	AffichageBoutons(FALSE);
	((CEquipM1752*)equip)->EffacementUrgence();

	// TODO Affichage avant le test en cours "EFFACEMENT D'URGENCE DES TABLE ALE EN COURS"
}

// Affichage des boutons et de l'onglet Prog
void CDlgTRC1752::AffichageBoutons(bool affiche)
{
	if (((CEquipM1752*)equip)->Actif() != FALSE)
	{
		m_Mod->m_Tab.SelectTab(0);					// Sélection de l'onglet Opérationnel
		InitOnglets();								// Initialisation des onglets

	}

	m_Mod->m_Tab.EnableTab(1, affiche);				// On grise l'onglet Programmation
	GetDlgItem(IDC_PROG)->EnableWindow(affiche);	// On grise tous les boutons
	GetDlgItem(IDC_LOC)->EnableWindow(affiche);
	GetDlgItem(IDC_VAL)->EnableWindow(affiche);
	GetDlgItem(IDC_ESC)->EnableWindow(affiche);
	GetDlgItem(IDC_EUA)->EnableWindow(affiche);

	// Désactivation des voies
	if (affiche == FALSE)
	{
		((CEquipM1752*)equip)->Desactiver("A1");
		((CEquipM1752*)equip)->Desactiver("A2");
		((CEquipM1752*)equip)->Desactiver("B1");
		((CEquipM1752*)equip)->Desactiver("B2");
	}
}

// Affichage de la vue Ops aprés activation d'une voie
void CDlgTRC1752::AffichageOps()
{
	m_Mod->m_Tab.SelectTab(0);
}

// V3.0.1
void CDlgTRC1752::AffichageAct(const string voie)
{
	//m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaA1->AffichageActivation();
}

// Affichage Test
void CDlgTRC1752::AffichageTst(const int voie)
{
	m_Mod->m_ModProg->m_ModProgSta->m_ProgStaTab.SelectTab(4);
	m_Mod->m_ModProg->m_ModProgSta->m_ModProgStaTst->InitVoie(voie);
}

void CDlgTRC1752::AffichageAutotest(const string type_erreur)
{
	m_Mod->m_ModProg->m_ModProgStst->Erreur(type_erreur);
}

void CDlgTRC1752::AffichageAutotest(string *l1, string *l2, string *l3, string *l4)
{
	m_Mod->m_ModProg->m_ModProgStst->Erreur(l1, l2, l3, l4);
}

void CDlgTRC1752::AffichageTestCarte(const string nomvoie)
{
	m_Mod->m_Tab.SelectTab(1);
	m_Mod->m_ModProg->m_ModProgTab.SelectTab(4);				// Prog_Configuration

	if (nomvoie == "T")
		m_Mod->m_ModProg->m_ModProgStst->TestCartex(0);

	if (nomvoie == "A")
		m_Mod->m_ModProg->m_ModProgStst->TestCartex(1);

	if (nomvoie == "B")
		m_Mod->m_ModProg->m_ModProgStst->TestCartex(2);

}

