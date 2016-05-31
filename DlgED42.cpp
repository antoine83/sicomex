// DlgED42.cpp: implementation of the CDlgED42 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42.h"
#include "Equip\EquipED42.h"
#include "DlgAide.h"
#include "DlgED42ERRPANNE.h"

#include <iostream>
#include <string>
#include <string.h>

#include "Divers\Logger.h"


extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_ED42[];
extern char glob_REPERTOIRE[];


#define DUREEHT	DUREE1MN

using namespace std;
using namespace CPlusPlusLogging;

extern Logger pLogger;


CDlgED42::CDlgED42(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDlgED42::IDD, pParent)
{

	//{{AFX_DATA_INIT(CDlgED42)
	m_err_retard	= _T("");
	m_tempo			= _T("");
	m_periode		= _T("");
	m_debut			= FALSE;
	m_fin			= FALSE;
	m_inconnue		= FALSE;
	m_reponse		= FALSE;
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDB_EQP_ED42);
	etat		= FALSE;
	isNum		= TRUE;				// TRUE = Touches numeriques
	//remoteMode	= FALSE;
	//valBool		= FALSE;

	LoadData();
}

CDlgED42::~CDlgED42()
{
	m_dlgTab->DestroyWindow();
	delete m_dlgTab;
}

void CDlgED42::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42)
	DDX_Control(pDX, IDC_CDE_INCONUE, c_cdeInconnue);
	DDX_Control(pDX, IDC_PAS_REPONSE, c_pasDeReponse);
	DDX_Control(pDX, IDC_NUM_MSG, c_errorNumMsg);
	DDX_Control(pDX, IDC_DEBUT_TRAME, c_pasDeCr);
	DDX_Control(pDX, IDC_FIN_TRAME, c_pasDeLf);
	DDX_Control(pDX, IDC_CHECKSUM, c_checksum);
	DDX_Control(pDX, IDC_CHECK_SYNCHRO, m_synchro);
	DDX_Control(pDX, IDC_CHECK_CYCLE, m_cycle);
	DDX_Text(pDX, IDC_RETARD, m_err_retard);
	DDX_Text(pDX, IDC_EDIT_TEMPO, m_tempo);
	DDX_Text(pDX, IDC_EDIT_CYCLE, m_periode);
	DDX_Check(pDX, IDC_DEBUT_TRAME, m_debut);
	DDX_Check(pDX, IDC_FIN_TRAME, m_fin);
	DDX_Check(pDX, IDC_CDE_INCONUE, m_inconnue);
	DDX_Check(pDX, IDC_PAS_REPONSE, m_reponse);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42, CDialog)
	//{{AFX_MSG_MAP(CDlgED42)
	ON_BN_CLICKED(IDC_ED42_DCP_CIK, OnInfo)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_ED42_DCP_NL, OnNl)
	ON_BN_CLICKED(IDC_ED42_DCP_EG, OnEg)
	ON_BN_CLICKED(IDC_ED42_DCP_BTN_FW, OnEd42DcpBtnFw)
	ON_BN_CLICKED(IDC_ED42_DCP_BTN_ST, OnEd42DcpBtnSt)
	ON_BN_CLICKED(IDC_ED42_DCP_BTN_RS, OnEd42DcpBtnRs)
	ON_BN_CLICKED(IDC_CHECKSUM, OnChecksum)
	ON_BN_CLICKED(IDC_NUM_MSG, OnNumMsg)
	ON_BN_CLICKED(IDC_FIN_TRAME, OnFinTrame)
	ON_BN_CLICKED(IDC_DEBUT_TRAME, OnDebutTrame)
	ON_BN_CLICKED(IDC_PAS_REPONSE, OnPasReponse)
	ON_BN_CLICKED(IDC_CDE_INCONUE, OnCdeInconue)
	ON_EN_KILLFOCUS(IDC_RETARD, OnKillfocusRetard)
	//}}AFX_MSG_MAP

	ON_WM_CLOSE()
	ON_WM_PAINT()

	// Activation des tache de comm
	ON_COMMAND(IDC_ACTIVITE, OnActivite)

	// Aide
	ON_COMMAND(ID__AIDE, OnAide)

	//Test
	ON_COMMAND(ID_CONTEXTE_ERREURS_PANNES, OnErreursPannes)

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


END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42 message handlers

/* **************************************************************************
METHODE :		OnAide()
TRAITEMENT:		Boite de dialogue d'aide
***************************************************************************	*/
void CDlgED42::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_ED42,"Chiffreur ED42");
	if(iResult >=  0)
	{
		win.DoModal();
	}

	delete win;
}

// ******************************************
// Gestion des erreurs et pannes
// ******************************************
void CDlgED42::OnErreursPannes()
{
	DlgED42ERRPANNE*	win2 = new DlgED42ERRPANNE(eqp);

	win2->DoModal();

	win2->DestroyWindow();
	delete win2;
}

// ******************************************
// OnInitDialog()
// ******************************************
BOOL CDlgED42::OnInitDialog()
{
	OutputDebugString("Dans : CDlgED42::OnInitDialog() !\n");
	pLogger.LOG_TRACE("Dans : CDlgED42::OnInitDialog() !");

	lockTimeChecker = 0;
	m_timerEd = 0;

	//t_ComErreur	err;
	char	buf[10];
	eqp = (CEquipED42*) equip;

	SetClavier(FALSE);

	chaineSep			= (" ");
	actionEnCours		= TRAIT;
	actionEnCours1		= CARVIDE;
	actionEnCours2		= CARVIDE;
	actionEnCoursTmp	= CARVIDE;

	CDialog::OnInitDialog();

	// Gestion des erreurs de communication
	// ************************************
	equip->RetourneComErreur(&err);

	sprintf(buf,"%d",err.retard);
	m_err_retard = buf;

	sprintf(buf,"%d",equip->Periode());
	m_periode = buf;

	// Envoi de sequence de message
	// ****************************
	GetDlgItem(IDC_ENVOI_STATUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARRET_STATUT)->EnableWindow(FALSE);

	sprintf(buf,"%d",equip->DureeTempo());
	m_tempo = buf;

	m_cycle.SetCheck(equip->EnvoiCyclique());
	m_synchro.SetCheck(equip->Synchronise());

// Custom control
// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);
	m_cik.SubclassDlgItem(IDC_ED42_DCP_CIK,this);
	m_nl.SubclassDlgItem(IDC_ED42_DCP_NL,this);
	m_eg.SubclassDlgItem(IDC_ED42_DCP_EG,this);

	//Initialiasation du bouton CIK
	GetDlgItem(IDC_ED42_DCP_CIK)->EnableWindow(TRUE);

	//Ajout du sous menu pour les pannes et les erreurs
	GetMenu()->GetSubMenu(0)->InsertMenu(2,MF_BYPOSITION,ID_CONTEXTE_ERREURS_PANNES,"Pannes et Erreurs...");

	m_dlgTab = new CDlgED42Tab((CEquipED42*)equip);
    m_dlgTab->Create(CDlgED42Tab::IDD, this);
    m_dlgTab->ShowWindow(SW_SHOW);

	UpdateData(FALSE);

	GestionAffichageBoutons(FALSE);
	RazAffichage();
	GestionAffichageExploitation(FALSE);
	//GestionBoutonLockUnlock();
	GestionAffichageEmRec(FALSE);
;
	//	Armement du timer
	SetTimer(1,DUREE1S,NULL);

	eqp->setReceptionDonnee(FALSE);

	eqp->SetOperatingStatus(MA);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

/* **************************************************************************
METHODE :		LoadData()
TRAITEMENT:		Charge les données de la vue
***************************************************************************	*/
void CDlgED42::LoadData()
{
	// TODO
}

/* **************************************************************************
METHODE :		OnInfo()
TRAITEMENT:		Action sur le bouton CIK
***************************************************************************	*/
void CDlgED42::OnInfo()
{
	int ret1 = NO_CIK_STATE;
	int ret2 = CIK_NOT_PLUGED;
	int ret3 = NOT_DEFINED;

	int	iResult = m_cik.Inverse_etat();

	if (iResult == 1)
	{
		ret1 = WAITING_CIK_STATE;
		ret2 = KE_IDLE;
		ret3 = CIK_MODE;
	}

	eqp->ChangeCik(ret1,FALSE); // Traitement de CIK pour CIK_STATE
	eqp->SetKeStatus(ret2);		// Traitement de CE State - KEStatus
	eqp->setSecureMode(ret3);
}

/* **************************************************************************
METHODE :		OnNl()
TRAITEMENT:		Action sur le bouton NL
***************************************************************************	*/
void CDlgED42::OnNl()
{
	int	iResult = m_nl.Inverse_etat();

 	eqp->ChangeNl(iResult);


	RazEd42();
	//remoteMode = FALSE;
	eqp->setRemoteStatus(FALSE);
	eqp->SetRemoteTC(LOCAL_TC);
	eqp->SetKEState(1);						// Param 28 : Flag : KE state
	eqp->RazTableCle(true);
	eqp->SetZeroizeStatus(true);
}

/* **************************************************************************
METHODE :		OnEg()
TRAITEMENT:		Action sur le bouton EG
***************************************************************************	*/
void CDlgED42::OnEg()
{
	int	iResult = m_eg.Inverse_etat();

 	eqp->ChangeEg(iResult);
}

/* **************************************************************************
METHODE :		SetClavier()
TRAITEMENT:		Action sur une touche
***************************************************************************	*/
void CDlgED42::SetClavier(const bool valeur)
{
	eqp->SetClavier(valeur);
}

/* **************************************************************************
METHODE :		GetClavier()
TRAITEMENT:		Action sur une touche ?
***************************************************************************	*/
BOOL CDlgED42::GetClavier()
{
	return eqp->GetClavier();
}

/* **************************************************************************
METHODE :		GestionAffichageBoutons()
TRAITEMENT:		Affichage des boutons et de l'onglet Prog
***************************************************************************	*/
void CDlgED42::GestionAffichageBoutons(bool affiche)
{
	OutputDebugString("Dans : CDlgED42::GestionAffichageBoutons(bool affiche) !\n");
	pLogger.LOG_TRACE("Dans : CDlgED42::GestionAffichageBoutons(bool affiche) !");

	if (eqp->GetMarcheEd42() && !eqp->GetStatusNl())
	{
		OutputDebugString("Dans : CDlgED42::GestionAffichageBoutons(bool affiche) et if (eqp->GetMarcheEd42() && !eqp->GetStatusNl())!\n");
		pLogger.LOG_TRACE("Dans : CDlgED42::GestionAffichageBoutons(bool affiche) et if (eqp->GetMarcheEd42() && !eqp->GetStatusNl())!");

		GetDlgItem(IDC_ED42_DCP_BTN_RS)->EnableWindow(affiche);
		GetDlgItem(IDC_ED42_DCP_BTN_FW)->EnableWindow(affiche);
		GetDlgItem(IDC_ED42_DCP_BTN_ST)->EnableWindow(affiche);
		GetDlgItem(IDC_ED42_DCP_CIK)->EnableWindow(affiche);
		GetDlgItem(IDC_ED42_DCP_NL)->EnableWindow(affiche);
		GetDlgItem(IDC_ED42_DCP_EG)->EnableWindow(affiche);
		for(int i=0;i<m_dlgTab->m_tab.GetCount();i++)
		{
			m_dlgTab->m_tab.EnableTab(i,affiche);
		}
	}

	if (!eqp->GetMarcheEd42())
	{
		OutputDebugString("Dans : CDlgED42::GestionAffichageBoutons(bool affiche) et if (!eqp->GetMarcheEd42())!\n");
		pLogger.LOG_TRACE("Dans : CDlgED42::GestionAffichageBoutons(bool affiche) et if (!eqp->GetMarcheEd42())!");

		GetDlgItem(IDC_ED42_DCP_BTN_RS)->EnableWindow(FALSE);
		GetDlgItem(IDC_ED42_DCP_BTN_FW)->EnableWindow(FALSE);
		GetDlgItem(IDC_ED42_DCP_BTN_ST)->EnableWindow(FALSE);
		GetDlgItem(IDC_ED42_DCP_CIK)->EnableWindow(FALSE);
		GetDlgItem(IDC_ED42_DCP_NL)->EnableWindow(FALSE);
		GetDlgItem(IDC_ED42_DCP_EG)->EnableWindow(FALSE);
		for(int i=0;i<m_dlgTab->m_tab.GetCount();i++)
		{
			m_dlgTab->m_tab.SelectTab(0);
			m_dlgTab->m_tab.EnableTab(i,FALSE);
		}
	}

	if (eqp->GetStatusNl() && eqp->GetMarcheEd42())
		GetDlgItem(IDC_ED42_DCP_BTN_RS)->EnableWindow(true);

	OutputDebugString("Fin : CDlgED42::GestionAffichageBoutons(bool affiche) !\n");
	pLogger.LOG_TRACE("Fin : CDlgED42::GestionAffichageBoutons(bool affiche) !");
}


/* **************************************************************************
METHODE :		OnTimer(UINT nIDEvent)
TRAITEMENT:		Rafraichissement de l'ecran de controle
***************************************************************************/
void CDlgED42::OnTimer(UINT nIDEvent)
{
	// TODO : Automate a simplifier et/ou modifier.

	//int	val, retPanne, iResult, cpt;
	int	retPanne, cpt;
	char bufferDebug[20] = {0};
	string AfficheDebug;

	bool presencePowerBitError = FALSE;

	CDialog::OnTimer(nIDEvent);

	chaineSep = eqp->GetChaineClavier().c_str();

	if (eqp->GetStatusBusy() == 1)
		SetTimer(11,DUREEBUSY,NULL);

	//IDC_CHECK_FULL
	m_dlgTab->m_Info->GetDlgItem(IDC_CHECK_FULL)->ShowWindow(eqp->GetMarcheEd42() && !eqp->GetResetEd42() && !eqp->GetStatusNl());

	//*******************************
	// Traitement de la touche A/M
	//*******************************
	if(equip->Actif() != etat)
	{
		etat = equip->Actif();
		if(etat == FALSE)
		{
			RazEd42();
		}
		else
		{
			OutputDebugString("Dans : début ED42_INITIALISATION !\n");
			pLogger.LOG_TRACE("Dans : debut ED42_INITIALISATION !");

			KillTimer(1);
			if (!eqp->GetStatusNl())
			{
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[TRAIT].c_str());
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[TRAIT].c_str());
				SetTimer(2,DUREE2S,NULL);
				eqp->SetOperatingStatus(ED42_INITIALISATION);			//actionEnCours = MA;
			}else{
				MiseEnMarche();
				GestionAffichageBoutons(FALSE);
			}

		}
	}

	// Mise en place de password lock time
	if (m_timerEd != 9 && eqp->GetPasswordHoldTime() != 0 && !eqp->getED42Lock() && !eqp->getRemoteStatus())
		m_timerEd = SetTimer(9,DUREEHT*eqp->GetPasswordHoldTime(),NULL);

	// Traitement de TAMPER
	if (eqp->GetKeStatus() == TAMPER)
	{
		eqp->SetStatusNl(1);
		RazEd42();
		//remoteMode = FALSE;
		eqp->setRemoteStatus(FALSE);
		eqp->SetRemoteTC(LOCAL_TC);
		//actionEnCours = ZEROIZE_ALARM;
		eqp->SetKeStatus(KE_IDLE);
	}
	
	// Traitement de ZEROIZE
	if (eqp->GetStatusNl() && actionEnCours != MA &&
							  actionEnCours != USER_PW_VERIFICATION &&
							  actionEnCours != RESTART_WITH_RESET &&
							  actionEnCours != ZEROIZE_ALARM &&
		                      actionEnCours != ZEROIZE_ALARM_C &&
							  actionEnCours != ZEROIZE_ALARM_S &&
							  actionEnCours != ACTIV_LOCAL_CTRL &&
							  actionEnCours != ACTIV_LOCAL_CTRL_1 &&
							  actionEnCours != ACTIV_LOCAL_CTRL_2 &&
							  actionEnCours != ENTER_ZEROIZE_PW &&
							  actionEnCours != ENTER_USER_PW &&
							  actionEnCours != ONLINE &&
							  equip->Actif())
	{
		sortieDebug("Dans : // Traitement de ZEROIZE : ", actionEnCours);

		eqp->SetOperatingStatus(ZEROIZE_ALARM);			// actionEnCours = ZEROIZE_ALARM;
	}


	// Affichage des pannes
	c_checksum.SetCheck(eqp->getStatusErrorTable(SYNTAX_RCS));		//|| eqp->getStatusErrorRCS());
	
	//actionEnCours = eqp->GetOperatingStatus();

	OutputDebugString("Avant : switch (nIDEvent) !\n");
	pLogger.LOG_TRACE("Avant : switch (nIDEvent) !");

	switch (nIDEvent)
	{
		OutputDebugString("Dans : switch (nIDEvent) !\n");
		pLogger.LOG_TRACE("Dans : switch (nIDEvent) !");

		case 1:
			OutputDebugString("Dans : case 1:) !\n");
			pLogger.LOG_TRACE("Dans : case 1:) !");

			//*******************************
			// Traitement de la touche RS
			//*******************************
			if (eqp->GetResetEd42())
			{
				OutputDebugString("Dans : // Traitement de RS !\n");
				pLogger.LOG_TRACE("Dans : // Traitement de RS !");

				KillTimer(m_timerEd);
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[RESTART_WITH_RESET].c_str());
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());

				eqp->SetOperatingStatus(RESTART_WITH_RESET);		//actionEnCours = RESTART_WITH_RESET;

				actionEnCours1 = CARVIDE;
				actionEnCours2 = CARVIDE;
				actionEnCoursTmp = CARVIDE;
				SetTimer(6, DUREE2S, NULL);

				// Mise à jour des flag's
				eqp->SetPresetList("255", 'X');					// Param 20
				eqp->SetOnlinePresetStatus(0);					// Param 21 : Flag : Online preset
				eqp->SetActiveKeyState(0);						// Param 29 : Flag : Active KEY state
				eqp->SetKeyList(1);								// Param 25 : Flag : key list

				eqp->SetOnlinePreset(DEFAULT_INVALID_VALUE_ED42);
				eqp->SetActivatedKey(DEFAULT_INVALID_VALUE_ED42);
				eqp->SetStatusTx(0);
				eqp->SetStatusRx(0);

				m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
				m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
				m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);
				m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);

				GestionAffichageEmRec(FALSE);
				GestionAffichageExploitation(FALSE);
			}

			actionEnCours = eqp->GetOperatingStatus();

			sortieDebug("Avant : switch (actionEnCours) : ", actionEnCours);

			switch (actionEnCours)
			{
				OutputDebugString("Dans : switch (actionEnCours) !\n");
				pLogger.LOG_TRACE("Dans : switch (actionEnCours) !");

				case MA:
					break;
				case TRAIT:
					break;
				case ED42_INITIALISATION:
					OutputDebugString("Dans : case ED42_INITIALISATION: !\n");
					pLogger.LOG_TRACE("Dans : case ED42_INITIALISATION: !");
					break;
				case POWER_ON_BIT:
					break;
				case ZEROIZE_ALARM_S:
					OutputDebugString("Dans : case ZEROIZE_ALARM_S: !\n");
					pLogger.LOG_TRACE("Dans : case ZEROIZE_ALARM_S: !");
					break;
				case ZEROIZE_ALARM:
					OutputDebugString("Dans : case ZEROIZE_ALARM: !\n");
					pLogger.LOG_TRACE("Dans : case ZEROIZE_ALARM: !");

					if (etat)
					{
						OutputDebugString("Dans : case ZEROIZE_ALARM: et if (etat) !\n");
						pLogger.LOG_TRACE("Dans : case ZEROIZE_ALARM: et if (etat) !");
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[ZEROIZE_ALARM].c_str());
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[RESTART_WITH_RESET].c_str());
						eqp->SetOperatingStatus(ZEROIZE_ALARM_S);			// actionEnCours = ZEROIZE_ALARM_S;
					}
					else
					{
						OutputDebugString("Dans : case ZEROIZE_ALARM: et else !\n");
						pLogger.LOG_TRACE("Dans : case ZEROIZE_ALARM: et else !");
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());
					}
					break;
				case RESTART_WITH_RESET:
					OutputDebugString("Dans : case RESTART_WITH_RESET: !\n");
					pLogger.LOG_TRACE("Dans : case RESTART_WITH_RESET !");
					KillTimer(1);
					eqp->SetResetEd42(false);
					break;
				case ENTER_ZEROIZE_PW:
					
					OutputDebugString("Dans : case ENTER_ZEROIZE_PW: !\n");
					pLogger.LOG_TRACE("Dans : case ENTER_ZEROIZE_PW !");

					GetDlgItem(IDC_ED42_DCP_BTN_ST)->EnableWindow(true);
					GetDlgItem(IDC_ED42_DCP_BTN_FW)->EnableWindow(true);

					initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[DEF_PW].c_str(), 1);

					m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(true);
					m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[DEF_PW].c_str());
					//m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
					m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(true);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);

					if (GetClavier())
					{
						OutputDebugString("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier())!\n");
						pLogger.LOG_TRACE("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier())!");

						if(eqp->GetChaineClavier() == "FW")
						{
							OutputDebugString("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'FW')!\n");
							pLogger.LOG_TRACE("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'FW')!");
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(true);
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(true);
							m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);
							eqp->SetChaineClavier("");
							break;
						}

						if(eqp->GetChaineClavier() == "V")
						{
							OutputDebugString("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V')!\n");
							pLogger.LOG_TRACE("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V')!");

							if (actionEnCours1 == ENTER_ZEROIZE_PW)
							{
								OutputDebugString("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V') et if (actionEnCours1 == ED42_UNLOCK)!\n");
								pLogger.LOG_TRACE("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V') et if (actionEnCours1 == ED42_UNLOCK)!");

								initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[DEF_PW].c_str(), 1);

								m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(true);
								m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
								m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(true);
								m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);
								eqp->SetChaineClavier("");
								break;
							}
						}

						if(eqp->GetChaineClavier() == "V")
						{
							OutputDebugString("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V')!\n");
							pLogger.LOG_TRACE("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V')!");

							initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[DEF_PW].c_str());

							actionEnCours1 = ENTER_ZEROIZE_PW;
							chaineSep = "";
							eqp->SetChaineClavier("");
						}

									
						if (eqp->GetChaineClavier() == "ST")
						{
							OutputDebugString("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST')!\n");
							pLogger.LOG_TRACE("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST')!");

							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(chaineEnCours);

							if (userPasswordVerification(chaineEnCours, eqp->GetDefPassWord()))
							{
								OutputDebugString("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST' et if (userPasswordVerification(chaineEnCours, eqp->GetDefPassWord())))!\n");
								pLogger.LOG_TRACE("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST' et if (userPasswordVerification(chaineEnCours, eqp->GetDefPassWord())))!");

								initAffichageUn(OPERATING_STATUS[ENTER_ZEROIZE_PW].c_str(), OPERATING_STATUS[SUCCESSFUL].c_str());
								actionEnCours1 = ENTER_ZEROIZE_PW;
								actionEnCours2 = CARVIDE;
								eqp->SetOperatingStatus(ACTIV_LOCAL_CTRL_1);			// SUCCESSFUL
								eqp->setED42Lock(false);
								m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(false);
								m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
								m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(false);
								m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);
								}else
								{
									OutputDebugString("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST' et if (userPasswordVerification(chaineEnCours, eqp->GetUserPassWord()))) et else!\n");
									pLogger.LOG_TRACE("Dans : case ENTER_ZEROIZE_PW: et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST' et if (userPasswordVerification(chaineEnCours, eqp->GetUserPassWord()))) et else!");

									initAffichageUn(OPERATING_STATUS[ENTER_ZEROIZE_PW].c_str(), OPERATING_STATUS[INCORRECT].c_str());
									actionEnCours1 = ENTER_ZEROIZE_PW;
									actionEnCours2 = INCORRECT;							   
									eqp->SetOperatingStatus(ACTIV_LOCAL_CTRL_2);		// INCORRECT
									m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
								}

								chaineSep = "";
								eqp->SetChaineClavier("");
							}
									
							SetClavier(FALSE);
						}
					break;
				case DEF_PW:
					//*******************************
					// Traitement de Default password
					//*******************************
					
					OutputDebugString("Dans : case DEF_PW: !\n");
					pLogger.LOG_TRACE("Dans : case DEF_PW: !");
					
					eqp->SetOperatingStatus(DEF_PW);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->ShowWindow(FALSE);
					eqp->SetFullSimu(false);
					//
					TraitementTouches(OPERATING_STATUS[ENTER_ZEROIZE_PW].c_str(), OPERATING_STATUS[DEF_PW].c_str(), TRUE);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(!(chaineSep == "V") && !(chaineSep == "FW"));

					if (GetClavier())
					{
						if (eqp->GetChaineClavier() == "V")
						{
							OutputDebugString("Dans : case DEF_PW: et if (chaineSep == 'V') !\n");
							pLogger.LOG_TRACE("Dans : case DEF_PW: et if (chaineSep == 'V') !");
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(TRUE);
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[DEF_PW].c_str());
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(TRUE);
						}

						if (eqp->GetChaineClavier() == "ST")
						{
							OutputDebugString("Dans : case DEF_PW: et if (chaineSep == 'ST') !\n");
							pLogger.LOG_TRACE("Dans : case DEF_PW: et if (chaineSep == 'ST') !");
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(chaineEnCours);

							CString ChS1(chaineEnCours);
							std::string s1((LPCTSTR)ChS1);
							int lenChS1 = s1.length();

							if (lenChS1<=0 || lenChS1>8)
							{
								Beep(440,500);
								m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
								m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
								m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);
								m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);
								SetClavier(FALSE);
								break;
							}

							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);
							m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);

							eqp->SetDefPassWord(s1);
							eqp->SetOperatingStatus(ENTER_USER_PW);	//actionEnCours = ENTER_USER_PW;
						}

						if (eqp->GetChaineClavier() == "FW")
						{
							OutputDebugString("Dans : case DEF_PW: et if (chaineSep == 'FW') !\n");
							pLogger.LOG_TRACE("Dans : case DEF_PW: et if (chaineSep == 'FW') !");
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(TRUE);
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(TRUE);
						}

						SetClavier(FALSE);
					}
					break;
				case ENTER_USER_PW:
					//****************************
					// Traitement de User password
					//****************************
					
					OutputDebugString("Dans : case ENTER_USER_PW: !\n");
					pLogger.LOG_TRACE("Dans : case ENTER_USER_PW: !");

					initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[USER_PW].c_str(), 1);

					m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(true);
					m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[USER_PW].c_str());
					//m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
					m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(true);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);

					if (GetClavier())
					{
						OutputDebugString("Dans : case ENTER_USER_PW: et if (GetClavier())!\n");
						pLogger.LOG_TRACE("Dans : case ENTER_USER_PW: et if (GetClavier())!");

						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[ENTER_USER_PW].c_str());

						if(eqp->GetChaineClavier() == "FW")
						{
							OutputDebugString("Dans : case ENTER_USER_PW: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'FW')!\n");
							pLogger.LOG_TRACE("Dans : case ENTER_USER_PW: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'FW')!");
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(true);
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(true);
							m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);
							eqp->SetChaineClavier("");
							break;
						}

						if (eqp->GetChaineClavier() == "V")
						{
							OutputDebugString("Dans : case ENTER_USER_PW: et if (GetClavier()) et if (chaineSep == 'V')!\n");
							pLogger.LOG_TRACE("Dans : case ENTER_USER_PW: et if (GetClavier()) et if (chaineSep == 'V')!");
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(TRUE);
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[USER_PW].c_str());
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(TRUE);
						}

						if (eqp->GetChaineClavier() == "ST")
						{
							OutputDebugString("Dans : case ENTER_USER_PW: et if (GetClavier()) et if (chaineSep == 'ST')!\n");
							pLogger.LOG_TRACE("Dans : case ENTER_USER_PW: et if (GetClavier()) et if (chaineSep == 'ST')!");

							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(chaineEnCours);

							CString ChS1(chaineEnCours);
							std::string s1((LPCTSTR)ChS1);
							int lenChS1 = s1.length();

							if (lenChS1<5 || lenChS1>8)
							{
								Beep(440,500);
								m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
								m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
								m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);
								m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);
								SetClavier(FALSE);
								break;
							}

							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);
							m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);

							eqp->SetUserPassWord(s1);
							eqp->SetOperatingStatus(USER_PW_VERIFICATION);			//actionEnCours = USER_PW_VERIFICATION;
							eqp->SetChaineClavier("");
							actionEnCours1 = ENTER_USER_PW;
						}

						SetClavier(FALSE);
					}
					break;
				case USER_PW_VERIFICATION:
					
					OutputDebugString("Dans : case USER_PW_VERIFICATION:!\n");
					pLogger.LOG_TRACE("Dans : case USER_PW_VERIFICATION:!");

					initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[USER_PW].c_str(), 1);

					m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(true);
					m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[USER_PW].c_str());
					//m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
					m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(true);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);
					

					if (GetClavier())
					{
						OutputDebugString("Dans : case USER_PW_VERIFICATION: et if (GetClavier())!\n");
						pLogger.LOG_TRACE("Dans : case USER_PW_VERIFICATION: et if (GetClavier())!");

						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[USER_PW_VERIFICATION].c_str());

						if(eqp->GetChaineClavier() == "FW")
						{
							OutputDebugString("Dans : case USER_PW_VERIFICATION: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'FW')!\n");
							pLogger.LOG_TRACE("Dans : case USER_PW_VERIFICATION: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'FW')!");

							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(true);
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(true);
							m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);
							eqp->SetChaineClavier("");
							break;
						}

						if (eqp->GetChaineClavier() == "V")
						{
							OutputDebugString("Dans : case USER_PW_VERIFICATION: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V')!\n");
							pLogger.LOG_TRACE("Dans : case USER_PW_VERIFICATION: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V')!");

							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(TRUE);
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[USER_PW].c_str());
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(TRUE);
						}

						if (eqp->GetChaineClavier() == "ST")
						{
							OutputDebugString("Dans : case USER_PW_VERIFICATION: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'ST')!\n");
							pLogger.LOG_TRACE("Dans : case USER_PW_VERIFICATION: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'ST')!");

							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(chaineEnCours);

							CString ChS1(chaineEnCours);
							std::string s1((LPCTSTR)ChS1);
							int lenChS1 = s1.length();

							if (lenChS1<5 || lenChS1>8 || !userPasswordVerification(chaineEnCours, eqp->GetUserPassWord()))
							{
								Beep(440,500);
								m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
								m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
								m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);
								m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);
								SetClavier(FALSE);
								break;
							}

							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);
							m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);

							eqp->SetUserPassWord(s1);
							eqp->ChangeNl(0);
							eqp->SetZeroizeStatus(FALSE);
							eqp->SetResetEd42(false);

							if (actionEnCours1 == ENTER_ZEROIZE_PW)
								 eqp->SetOperatingStatus(OFFLINE);
							
							if(actionEnCours1 == ENTER_USER_PW)
								eqp->SetOperatingStatus(LANGUAGE_SELECTION);		//actionEnCours = LANGUAGE_SELECTION;
						}

						SetClavier(FALSE);
					}
					break;
				case VERIFICATION_ERROR:
					break;
				case LANGUAGE_SELECTION:
					//*********************************
					// Traitement de selection language
					//*********************************
					
					OutputDebugString("Dans : case LANGUAGE_SELECTION:!\n");
					pLogger.LOG_TRACE("Dans : case LANGUAGE_SELECTION:!");
					
					eqp->SetOperatingStatus(LANGUAGE_SELECTION);
					TraitementTouches(OPERATING_STATUS[LANGUAGE_SELECTION].c_str(), LANGUAGES_SELECTION[eqp->GetLanguage()].c_str(), TRUE);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(TRUE);

					if (GetClavier())
					{
						SetClavier(FALSE);

						if (eqp->GetChaineClavier() == "V")
						{
							if (eqp->GetLanguage() == GERMAIN)
							{
								pLogger.LOG_TRACE("Dans : case LANGUAGE_SELECTION:et SetLanguage(ENGLICH)!");
								eqp->SetLanguage(ENGLICH);
								break;
							}
						}

						if (eqp->GetChaineClavier() == "V")
						{

							if (eqp->GetLanguage() == ENGLICH)
							{
								pLogger.LOG_TRACE("Dans : case LANGUAGE_SELECTION:et SetLanguage(GERMAIN)!");
								eqp->SetLanguage(GERMAIN);
								break;
							}
						}

						if (eqp->GetChaineClavier() == "ST")
						{
							pLogger.LOG_TRACE("Dans : case LANGUAGE_SELECTION:et if (eqp->GetChaineClavier() == 'ST')!");

							eqp->SetOperatingStatus(OFFLINE);
							eqp->SetMarcheEd42(true);
							eqp->SetFullSimu(true);
							m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());
							m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());
							m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);
						}

						SetClavier(FALSE);
					}
					break;
				case OFFLINE:
					OutputDebugString("Dans : case OFFLINE:!\n");
					pLogger.LOG_TRACE("Dans : case OFFLINE:!");

					UpdateData(FALSE);

					// Mémorisation de l'action en cours
					actionEnCoursTmp = OFFLINE;

					// Gestion Des Affichages
					GestionAffichageExploitation(FALSE);
					GestionAffichageEmRec(FALSE);

					//valBool = eqp->getRemoteStatus();

					// Affichage du boutton "V"
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(eqp->GetRemoteTC() == REMOTE_TC || eqp->getED42Lock());


					if(eqp->GetRemoteTC() == REMOTE_TC)
					{
						OutputDebugString("Dans : case OFFLINE: et if(eqp->GetRemoteTC() == REMOTE_TC)!\n");
						pLogger.LOG_TRACE("Dans : case OFFLINE: et if(eqp->GetRemoteTC() == REMOTE_TC)!");
							initAffichageUn(OPERATING_STATUS[OFFLINE].c_str(), OPERATING_STATUS[REMOTE_MODE].c_str());
							eqp->setED42Lock(FALSE); //TODO
							//remoteMode = valBool;
					}

					if(eqp->GetRemoteTC() == LOCAL_TC)
					{
						OutputDebugString("Dans : case OFFLINE: et if(eqp->GetRemoteTC() == LOCAL_TC) !\n");
						pLogger.LOG_TRACE("Dans : case OFFLINE: et if(eqp->GetRemoteTC() == LOCAL_TC)!");
						initAffichageUn(OPERATING_STATUS[OFFLINE].c_str(), "");
					}

					if(eqp->getED42Lock())
					{
						OutputDebugString("Dans : case OFFLINE: et if(eqp->getED42Lock()) !\n");
						pLogger.LOG_TRACE("Dans : case OFFLINE: et if(eqp->getED42Lock()) !");
						actionEnCoursTmp = eqp->GetOperatingStatus();
						eqp->SetOperatingStatus(ED42_UNLOCK);

					}

					// Gestion des actions de l'opérateur
					// Une action sur les touches ST, FW est traité dans ACTIV_LOCAL_CTRL 
					if (GetClavier())
					{
						OutputDebugString("Dans : case OFFLINE: et if (GetClavier())!\n");
						pLogger.LOG_TRACE("Dans : case OFFLINE: et if (GetClavier())!");

						if(eqp->GetChaineClavier() == "V" && eqp->GetRemoteTC() == REMOTE_TC)
						{
							OutputDebugString("Dans : case OFFLINE: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V' && eqp->GetRemoteTC() == REMOTE_TC)!\n");
							pLogger.LOG_TRACE("Dans : case OFFLINE: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V' && eqp->GetRemoteTC() == REMOTE_TC)!");

							initAffichageUn(OPERATING_STATUS[MAIN_MENU].c_str(), OPERATING_STATUS[ACTIV_LOCAL_CTRL].c_str());

							eqp->SetOperatingStatus(ACTIV_LOCAL_CTRL);

							eqp->SetChaineClavier("");
						}

						SetClavier(FALSE);
					}

					// Mise à jour des vues
					if (eqp->getModifVue())
						m_dlgTab->m_KeyManagementTab->LoadData();
					
					break;
				case ONLINE:
					OutputDebugString("Dans : case ONLINE:!\n");

					// Mémorisation de l'action en cours
					actionEnCoursTmp = ONLINE;
					
					initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[REMOTE].c_str());

					if (actionEnCours == ONLINE && eqp->GetRemoteTC() == REMOTE_TC)
						initAffichageUn(OPERATING_STATUS[CARVIDE].c_str(), OPERATING_STATUS[REMOTE_ONLINE].c_str());

					// Gestion des Affichages
					GestionAffichageEmRec(TRUE);
					GestionAffichageExploitation(TRUE);

					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(eqp->GetRemoteTC() == REMOTE_TC || eqp->getED42Lock());


					if(eqp->getED42Lock() && eqp->GetRemoteTC() == LOCAL_TC)
					{
						OutputDebugString("Dans : case ONLINE: et if(eqp->getED42Lock()) !\n");
						actionEnCoursTmp = eqp->GetOperatingStatus();
						eqp->SetOperatingStatus(ED42_UNLOCK);
					}

					// Gestion des actions de l'opérateur
					// Une action sur les touches ST, FW est traité dans ACTIV_LOCAL_CTRL
					if (GetClavier())
					{
						OutputDebugString("Dans : case ONLINE: et if (GetClavier())!\n");

						if(eqp->GetChaineClavier() == "V" && eqp->GetRemoteTC() == REMOTE_TC)
						{
							OutputDebugString("Dans : case ONLINE: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V' && eqp->GetRemoteTC() == REMOTE_TC)!\n");

							initAffichageUn(OPERATING_STATUS[MAIN_MENU].c_str(), OPERATING_STATUS[ACTIV_LOCAL_CTRL].c_str());

							eqp->SetOperatingStatus(ACTIV_LOCAL_CTRL);

							eqp->SetChaineClavier("");
						}

						SetClavier(FALSE);
					}
					break;
				case MAIN_MENU:
				case ACTIV_LOCAL_CTRL:
				case ACTIV_LOCAL_CTRL_1:
				case ACTIV_LOCAL_CTRL_2:
				case ZEROIZE_ALARM_C:
				case ED42_LOCK:
				case ED42_UNLOCK:
				case INCORRECT:
				case CV_DATA_CRYPTO:
				case CV_VOICE_CRYPTO:
						switch(actionEnCours)
						{
							case MAIN_MENU:
								//MainMenu();
								break;
							case ACTIV_LOCAL_CTRL:
								OutputDebugString("Dans : case ACTIV_LOCAL_CTRL:!\n");
								res = Activ_Local_Ctrl();
								break;
							case ACTIV_LOCAL_CTRL_1:		// SUCCESS
								OutputDebugString("Dans : case ACTIV_LOCAL_CTRL_1:!\n");
								eqp->SetStatusBusy(1);
								KillTimer(1);
								SetTimer(7,DUREE10S,NULL);
								break;
							case ACTIV_LOCAL_CTRL_2:		// INCORRECT
								OutputDebugString("Dans : case ACTIV_LOCAL_CTRL_2:!\n");
								eqp->SetStatusBusy(1);
								KillTimer(1);
								SetTimer(7,DUREE10S,NULL);
								break;
							case ED42_LOCK:
								break;
							case ED42_UNLOCK:
								OutputDebugString("Dans : case ED42_UNLOCK: !\n");

								if (GetClavier())
								{
									OutputDebugString("Dans : case ED42_UNLOCK: et if (GetClavier())!\n");

									if(eqp->GetChaineClavier() == "FW")
									{
										OutputDebugString("Dans : case ED42_UNLOCK: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'FW')!\n");
											m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(true);
											m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
											m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(true);
											m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);
											eqp->SetChaineClavier("");
											break;
									}

									if(eqp->GetChaineClavier() == "V")
									{
										OutputDebugString("Dans : case ED42_UNLOCK: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V')!\n");

										if (actionEnCours1 == ED42_UNLOCK)
										{
											OutputDebugString("Dans : case ED42_UNLOCK: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V') et if (actionEnCours1 == ED42_UNLOCK)!\n");

											initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[USER_PW].c_str(), 1);

											m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(true);
											m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
											m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(true);
											m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);
											eqp->SetChaineClavier("");
											break;
										}
									}

									if(eqp->GetChaineClavier() == "V")
									{
										OutputDebugString("Dans : case ED42_UNLOCK: et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V')!\n");

										initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[USER_PW].c_str());

										actionEnCours1 = ED42_UNLOCK;
										chaineSep = "";
										eqp->SetChaineClavier("");
									}

									
									if (eqp->GetChaineClavier() == "ST")
									{
										OutputDebugString("Dans : case ED42_UNLOCK: et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST')!\n");

										m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(chaineEnCours);

										if (userPasswordVerification(chaineEnCours, eqp->GetUserPassWord()))
										{
											OutputDebugString("Dans : case ED42_UNLOCK: et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST' et if (userPasswordVerification(chaineEnCours, eqp->GetUserPassWord())))!\n");
											initAffichageUn(OPERATING_STATUS[ED42_UNLOCK].c_str(), OPERATING_STATUS[SUCCESSFUL].c_str());
											actionEnCours1 = ED42_UNLOCK;
											actionEnCours2 = CARVIDE;
											eqp->SetOperatingStatus(ACTIV_LOCAL_CTRL_1);
											eqp->setED42Lock(false);
											m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(false);
											m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
											m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(false);
											m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);
										}else
										{
											OutputDebugString("Dans : case ED42_UNLOCK: et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST' et if (userPasswordVerification(chaineEnCours, eqp->GetUserPassWord()))) et else!\n");
											initAffichageUn(OPERATING_STATUS[ED42_UNLOCK].c_str(), OPERATING_STATUS[INCORRECT].c_str());
											actionEnCours1 = ED42_UNLOCK;
											actionEnCours2 = INCORRECT;							   
											eqp->SetOperatingStatus(ACTIV_LOCAL_CTRL_2);
											m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
										}

										chaineSep = "";
										eqp->SetChaineClavier("");
									}
									
									SetClavier(FALSE);
								}
								break;
							case ZEROIZE_ALARM_C:
								OutputDebugString("Dans : case ZEROIZE_ALARM_C: !\n");
								//m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(eqp->GetStatusNl());
								//res = ED42_UnLock(true);
								eqp->SetOperatingStatus(ENTER_ZEROIZE_PW);
								break;
							case CV_DATA_CRYPTO:
								Cv_Data_Crypto();
								break;
							case CV_VOICE_CRYPTO:
								Cv_Voice_Crypto();
								break;
							case INCORRECT:
								OutputDebugString("Dans : case INCORRECT: !\n");
								break;
						}

					break;

					OutputDebugString("Fin : switch (actionEnCours) !\n");
			}
			break;
			case 2:	// Timer2
				OutputDebugString("Dans : case 2: !\n");
				pLogger.LOG_TRACE("Dans : case 2: !");
				//KillTimer(1);
				KillTimer(2);
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[TRAIT_G].c_str());
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[TRAIT_D].c_str());
				SetTimer(3,DUREE4S,NULL);
				break;
			case 3:	// Timer3
				OutputDebugString("Dans : case 3: !\n");
				pLogger.LOG_TRACE("Dans : case 3: !");
				KillTimer(3);
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[TRAIT_D].c_str());
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[TRAIT_G].c_str());
				SetTimer(4,DUREE4S,NULL);
				break;
			case 4:	// Timer4
				OutputDebugString("Dans : case 4: !\n");
				pLogger.LOG_TRACE("Dans : case 4: !");
				KillTimer(4);
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[ED42_INITIALISATION].c_str());
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[POWER_ON_BIT].c_str());
				SetTimer(5,DUREE4S,NULL);
				break;
			case 5:	// Timer5
				OutputDebugString("Dans : case 5: !\n");
				pLogger.LOG_TRACE("Dans : case 5: !");
				KillTimer(5);
				//Vérification si aucune erreur sur les powers on bits sont présentes.
				for(cpt=0;cpt<NB_ERROR_POWER_ON_BIT;cpt++)
				{
					//Si on trouve au moins une erreur
					if(eqp->getPowerBitTable(cpt))
					{
						presencePowerBitError = TRUE;
						break;
					}
				}

				if(presencePowerBitError)
				{
					m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[POWER_ON_BIT_ERROR].c_str());

					if(cpt == POWER_ON_BIT_FLASH_MEMORY_TEST || cpt == POWER_ON_BIT_INTEGRITY_SOFTWARE)
					{
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[RESTART_WITH_RESET].c_str());
						GetDlgItem(IDC_ED42_DCP_BTN_RS)->EnableWindow(TRUE);
					}
					else
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());

					SetTimer(8,DUREE10R,NULL);
				}
				else
				{
					retPanne = MiseEnMarche();

					// TODO Traitement si panne
					GestionAffichageBoutons(TRUE);
					SetTimer(1,DUREE1S,NULL);

					if (eqp->GetDefPassWord().length() <= 2)
					{
						//isNum = TRUE;
						eqp->RazTableCle(true);
						eqp->SetOperatingStatus(DEF_PW);	//actionEnCours = DEF_PW;
						eqp->SetMarcheEd42(false);
						chaineSep = "";
					}
				}
				break;
			case 6:	// Timer6								// RST0 - RS
				OutputDebugString("Dans : case 6: !\n");
				pLogger.LOG_TRACE("Dans : case 6: !");
				KillTimer(6);
				//eqp->setRemoteStatus(FALSE);
				//eqp->setRemoteMode(LOCAL);
				//remoteMode = FALSE;
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[TRAIT].c_str());
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[TRAIT].c_str());
				SetTimer(2,DUREE1S,NULL);
				break;
            case 7:	// Timer7

				OutputDebugString("Dans : case 7: !\n");
				pLogger.LOG_TRACE("Dans : case 7: !");

				KillTimer(7);
				if (actionEnCours == ACTIV_LOCAL_CTRL_2)
				{
					OutputDebugString("Dans : case 7: et if (actionEnCours == ACTIV_LOCAL_CTRL_2)!\n");
					if (actionEnCours1 == ED42_UNLOCK)
					{
						ED42_UnLock(false);
						GestionBoutonLockUnlock();
					}

					if (actionEnCours1 == ED42_UNLOCK)
						initAffichageUn(OPERATING_STATUS[actionEnCours1].c_str(), OPERATING_STATUS[USER_PW].c_str());

					if (actionEnCours1 == ENTER_ZEROIZE_PW)
						initAffichageUn(OPERATING_STATUS[actionEnCours1].c_str(), OPERATING_STATUS[DEF_PW].c_str());

					eqp->SetOperatingStatus(actionEnCours1);
					actionEnCours1 = CARVIDE;
					actionEnCours2 = CARVIDE;
					eqp->SetChaineClavier("");
					SetTimer(1,DUREE1S,NULL);
				}

				if (actionEnCours == ACTIV_LOCAL_CTRL_1)
				{
					OutputDebugString("Dans : case 7: et if (actionEnCours == ACTIV_LOCAL_CTRL_1)!\n");

					if (actionEnCours1 == ACTIV_LOCAL_CTRL)
					{
						actionEnCours1 = CARVIDE;
						eqp->SetOperatingStatus(actionEnCoursTmp);
					}

					if (actionEnCours1 == ED42_UNLOCK)
					{
						actionEnCours1 = CARVIDE;
						eqp->SetOperatingStatus(actionEnCoursTmp);
					}

					if (actionEnCours1 == ENTER_ZEROIZE_PW)
					{
						//actionEnCours1 = CARVIDE;
						eqp->SetOperatingStatus(ENTER_USER_PW);
					}

					SetTimer(1,DUREE1S,NULL);
				}
				eqp->SetStatusBusy(0);
                break;
			case 8:	// Timer8
				OutputDebugString("Dans : case 8:!\n");
				pLogger.LOG_TRACE("Dans : case 8: !");
		
				KillTimer(8);
				//On vérifie que les erreurs Flash error et intégrity software provoque un blocage équipement
				if(!(eqp->getPowerBitTable(POWER_ON_BIT_FLASH_MEMORY_TEST)
					|| eqp->getPowerBitTable(POWER_ON_BIT_INTEGRITY_SOFTWARE)))
				{
					//On continue le démarrage
					retPanne = MiseEnMarche();
					// TODO Traitement si panne
					GestionAffichageBoutons(TRUE);
				}else
					eqp->RAZTable(); //Effacement des tables

				SetTimer(1,DUREE1S,NULL);
				
				break;
			case 9:	// Timer9							//LOCK&UNLOCK
				OutputDebugString("Dans : case 9:!\n");
				pLogger.LOG_TRACE("Dans : case 9: !");
				KillTimer(9);
				m_timerEd = 0;
				eqp->setED42Lock(TRUE);
				break;
			case 10:	// Timer10								
				OutputDebugString("Dans : case 10:!\n");
				pLogger.LOG_TRACE("Dans : case 10: !");
				/*
				KillTimer(10);
				eqp->setRemoteStatus(FALSE);
				eqp->setRemoteMode(LOCAL);
				eqp->SetRemoteTC(LOCAL_TC);
				remoteMode = FALSE;
				SetTimer(4,DUREE4S,NULL);
				//eqp->ChangeNl(0);
				*/
				break;
			case 11:	// Timer11								// After Zeroize/Emergency Clear page 83
				OutputDebugString("Dans : case 11: fin Busy!\n");
				pLogger.LOG_TRACE("Dans : case 11: fin Busy!");
				KillTimer(11);
				eqp->SetStatusBusy(0);
				break;
	}

	OutputDebugString("Fin : switch (nIDEvent) !\n");
	pLogger.LOG_TRACE("Fin : switch (nIDEvent) !");

	// Mise à jour de la vue exploitation
	affichgeExploitation();
	//GetState

// Presence CIK
	m_cik.Positionne_etat(eqp->GetStateCik() != NO_CIK_STATE);
// Presence NL
	m_nl.Positionne_etat(eqp->InfoNl());
// Presence EG
	m_eg.Positionne_etat(eqp->InfoEg());

//Vérifie si on a reçu une donnée à mettre à jour
	if(eqp->getReceptionDonnee())
	{
		OutputDebugString("Dans : CDlgED42::OnTimer(UINT nIDEvent) et if(eqp->getReceptionDonnee())!\n");

		if(m_dlgTab->m_tab.GetCurSel()==1) //Vérifie si on est dans l'onglet preset
		{
			//Si on modifie la vue et qu'on recoit une donnee, on sort de la vue
			//et on supprime les modification.
			if(eqp->getModifVue())
				eqp->setModifVue(FALSE);
			//Recharge de la vue
			m_dlgTab->m_Presets->LoadData();
			eqp->setReceptionDonnee(FALSE);
		}
	}
}

//***************************
// RAZ de l'affichage
//***************************
void CDlgED42::RazAffichage()
{
	OutputDebugString("Dans : CDlgED42::RazAffichage() !\n");
	m_dlgTab->m_Info->m_dcp1 = _T("");
	m_dlgTab->m_Info->m_dcp2 = _T("");
	UpdateData(FALSE);

	GestionBoutonLockUnlock();
}

//*****************************
// GestionAffichageExploitation
//*****************************
void CDlgED42::GestionAffichageExploitation(bool val)
{
	OutputDebugString("Dans : CDlgED42::GestionAffichageExploitation(bool val) !\n");

	m_dlgTab->m_Info->c_Transmission_Mode.ShowWindow(val);
	m_dlgTab->m_Info->c_Transmission_Procedure.ShowWindow(val);
	m_dlgTab->m_Info->c_Trafic_Mode.ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_OPE_MODE)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_TRANS_MODE)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_TRANS_PRECED)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_TRAF_MODE)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_PRESET_EXPLOIT)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_ACT_KEY)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_UPD_COUNT)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_DAT_RATE)->ShowWindow(val);
	// Les CStatic
	m_dlgTab->m_Info->GetDlgItem(IDC_OPERATING_MODE)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_PRESET_EXPL)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_TRANSMISSION_MODE)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_TRANSMISSION_PROCEDURE)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_TRAFIC_MODE)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_ACTIVE_KEY)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_UPDATE_COUNT)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_DATA_RATE)->ShowWindow(val);

}
//*****************************************
// GestionAffichage fonction OFFLINE/ONLINE
//*****************************************
void CDlgED42::GestionAffichage(bool val, int param1, int param2)
{
	OutputDebugString("Dans : début CDlgED42::GestionAffichage!\n");

	if (eqp->GetFullSimu())
	{
		OutputDebugString("Dans : CDlgED42::GestionAffichage et if (eqp->GetFullSimu())!\n");
		m_dlgTab->m_tab.EnableTab(1, eqp->GetMarcheEd42() &&
									!eqp->getRemoteStatus() &&
									!eqp->getED42Lock() &&
									!eqp->GetStatusNl());				//Operating Parameters

		m_dlgTab->m_tab.EnableTab(2, eqp->GetMarcheEd42() &&
									!eqp->getRemoteStatus() &&
									!eqp->GetStatusNl() &&
									 eqp->GetKeStatus() != CIK_NOT_PLUGED);				//Key Management

		m_dlgTab->m_tab.EnableTab(3, eqp->GetMarcheEd42() &&
									!eqp->getRemoteStatus() &&
									!eqp->getED42Lock() &&
									 eqp->GetOperatingStatus() == OFFLINE &&
									 !eqp->GetStatusNl());		//Security
		// && eqp->GetKeStatus() == KE_IDLE

		m_dlgTab->m_tab.EnableTab(4, eqp->GetMarcheEd42() &&
									!eqp->getRemoteStatus() &&
									!eqp->getED42Lock() &&
									!eqp->GetStatusNl());					//Basic Parameters

		// Key Management
		m_dlgTab->m_KeyManagementTab->c_tab.EnableTab(0, true );				//Display
		m_dlgTab->m_KeyManagementTab->c_tab.EnableTab(1, eqp->GetMarcheEd42() &&
														!eqp->getRemoteStatus() &&
														 eqp->GetOperatingStatus() == OFFLINE &&
														 eqp->GetFullSimu()); //Crypto
		if (eqp->GetOperatingMode() == OPE_MASTER)
			m_dlgTab->m_KeyManagementTab->c_tab.EnableTab(1, eqp->GetOperatingStatus() == ONLINE &&
															 eqp->GetRemoteTC() == LOCAL_TC);


		m_dlgTab->m_KeyManagementTab->c_tab.EnableTab(2, eqp->GetMarcheEd42() &&
														!eqp->getRemoteStatus() &&
														!eqp->getED42Lock()&&
														 eqp->GetOperatingStatus() == OFFLINE &&
														 eqp->GetFullSimu()); //Tag

		// Security
		m_dlgTab->m_SecurityTab->c_tab.EnableTab(1, eqp->GetKeStatus() != CIK_NOT_PLUGED &&
													eqp->GetFullSimu()); //CIK System


		// Basic Parameters
		m_dlgTab->m_Parameters->GetDlgItem(IDC_EDIT_P1)->EnableWindow(eqp->GetOperatingStatus() == OFFLINE);
		m_dlgTab->m_Parameters->GetDlgItem(IDC_BUTTON_P1)->EnableWindow(eqp->GetOperatingStatus() == OFFLINE);
		m_dlgTab->m_Parameters->GetDlgItem(IDC_EDIT_P2)->EnableWindow(eqp->GetOperatingStatus() == OFFLINE);
		m_dlgTab->m_Parameters->GetDlgItem(IDC_BUTTON_P2)->EnableWindow(eqp->GetOperatingStatus() == OFFLINE);
		m_dlgTab->m_Parameters->GetDlgItem(IDC_EDIT_HDLC)->EnableWindow(eqp->GetOperatingStatus() == OFFLINE &&
																		eqp->GetInterfaceKeyDownload() == DS101);
		m_dlgTab->m_Parameters->GetDlgItem(IDC_BUTTON_HDLC)->EnableWindow(eqp->GetOperatingStatus() == OFFLINE &&
																		eqp->GetInterfaceKeyDownload() == DS101);
		m_dlgTab->m_Parameters->GetDlgItem(IDC_SPIN_P1)->EnableWindow(eqp->GetOperatingStatus() == OFFLINE);
		m_dlgTab->m_Parameters->GetDlgItem(IDC_SPIN_P2)->EnableWindow(eqp->GetOperatingStatus() == OFFLINE);


		// Operating Parameters
		m_dlgTab->m_Presets->m_presetTab->m_tab.EnableTab(1,eqp->GetOperatingStatus() == OFFLINE); //Digital DCE
		m_dlgTab->m_Presets->m_presetTab->m_tab.EnableTab(2,eqp->GetOperatingStatus() == OFFLINE); //Analog DCE
		m_dlgTab->m_Presets->m_presetTab->m_tab.EnableTab(3,eqp->GetOperatingStatus() == OFFLINE); //Digital DTE
		m_dlgTab->m_Presets->m_presetTab->m_tab.EnableTab(4,eqp->GetOperatingStatus() == OFFLINE); //Analog DTE

	}else{
		OutputDebugString("Dans : CDlgED42::GestionAffichage et if (eqp->GetFullSimu()) et else !\n");

		m_dlgTab->m_tab.EnableTab(1, eqp->GetMarcheEd42());				//Operating Parameters

		m_dlgTab->m_tab.EnableTab(2, eqp->GetMarcheEd42());				//Key Management

		m_dlgTab->m_tab.EnableTab(3, eqp->GetMarcheEd42());				//Security

		m_dlgTab->m_tab.EnableTab(4, eqp->GetMarcheEd42());				//Basic Parameters

		// Key Management
		m_dlgTab->m_KeyManagementTab->c_tab.EnableTab(0, true);				//Display
		m_dlgTab->m_KeyManagementTab->c_tab.EnableTab(1, eqp->GetMarcheEd42()); //Crypto

		m_dlgTab->m_KeyManagementTab->c_tab.EnableTab(2, eqp->GetMarcheEd42()); //Tag

		// Security
		m_dlgTab->m_SecurityTab->c_tab.EnableTab(1, eqp->GetMarcheEd42()); //CIK System

		// Operating Parameters
		m_dlgTab->m_Presets->m_presetTab->m_tab.EnableTab(1,eqp->GetMarcheEd42()); //Digital DCE
		m_dlgTab->m_Presets->m_presetTab->m_tab.EnableTab(2,eqp->GetMarcheEd42()); //Analog DCE
		m_dlgTab->m_Presets->m_presetTab->m_tab.EnableTab(3,eqp->GetMarcheEd42()); //Digital DTE
		m_dlgTab->m_Presets->m_presetTab->m_tab.EnableTab(4,eqp->GetMarcheEd42()); //Analog DTE
	}

	GestionBoutonLockUnlock();

	OutputDebugString("Dans : fin CDlgED42::GestionAffichage!\n");

}

//********
// RazEd42
//********
void CDlgED42::RazEd42()
{
	OutputDebugString("Dans : début CDlgED42::RazEd42() !\n");

	RazAffichage();
	GestionAffichageExploitation(FALSE);
	GestionAffichageBoutons(eqp->GetStatusNl());
	GestionAffichageEmRec(FALSE);

	m_dlgTab->m_Info->c_operationMode.ShowWindow(FALSE);
	m_dlgTab->m_Info->c_preset.ShowWindow(FALSE);
	m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_ACT_DESACT)->ShowWindow(FALSE);

	eqp->setRemoteStatus(FALSE);
	eqp->SetRemoteTC(LOCAL_TC);
	//valBool = FALSE;
	//remoteMode = FALSE;
	eqp->SetOperatingStatus(TRAIT);		//actionEnCours = TRAIT;


	GetDlgItem(IDC_ED42_DCP_CIK)->EnableWindow(TRUE);
	m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());
	m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());
	m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);
	// Gestion saisie pwd
	m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
	m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
	m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);
	//************************************************************
	// Exploitation
	//************************************************************
	m_dlgTab->m_Info->GetDlgItem(IDC_TRANS_MODE)->SetWindowText(OPERATING_STATUS[CARTIRET].c_str());

	OutputDebugString("Dans : fin CDlgED42::RazEd42() !\n");
}

//*****************************
// Fonctions pour chaque touche
//*****************************
void CDlgED42::OnEd42DcpBtnFw()
{
	OutputDebugString("Dans : CDlgED42::OnEd42DcpBtnFw() !\n");

	m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(chaineEnCours);

	if (chaineEnCours == "" && eqp->GetOperatingStatus() != ACTIV_LOCAL_CTRL)
		return;

	OutputDebugString("Dans : CDlgED42::OnEd42DcpBtnFw() et suite1!\n");

	if (eqp->GetZeroizeStatus() && chaineEnCours == "")
		return;

	OutputDebugString("Dans : CDlgED42::OnEd42DcpBtnFw() et suite2!\n");

	eqp->SetChaineClavier("FW");
	eqp->SetClavier(TRUE);

	//Recherche si une valeur a changé
	if(eqp->getModifVue())
	{
		m_dlgTab->LoadData();
		eqp->setModifVue(FALSE);
	}

	OutputDebugString("Fin : CDlgED42::OnEd42DcpBtnFw() !\n");
}

void CDlgED42::OnEd42DcpBtnSt()
{
	OutputDebugString("Dans : CDlgED42::OnEd42DcpBtnSt() !\n");

	m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(chaineEnCours);
	//m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->

	if (chaineEnCours == "" && eqp->GetOperatingStatus() != LANGUAGE_SELECTION &&
							   eqp->GetOperatingStatus() != OFFLINE &&
							   eqp->GetOperatingStatus() != ONLINE)
		return;

	OutputDebugString("Dans : CDlgED42::OnEd42DcpBtnSt() et suite1!\n");

	if (eqp->GetZeroizeStatus() && chaineEnCours == "")
		return;

	OutputDebugString("Dans : CDlgED42::OnEd42DcpBtnSt() et suite2!\n");

	eqp->SetChaineClavier("ST");
	eqp->SetClavier(TRUE);

	m_dlgTab->SaveData();
	eqp->setModifVue(FALSE);
}

void CDlgED42::OnEd42DcpBtnRs()
{
	OutputDebugString("Dans : CDlgED42::OnEd42DcpBtnRs() !\n");

	//eqp->SetChaineClavier("RS");
	//eqp->SetClavier(TRUE);
	eqp->SetResetEd42(true);
	eqp->SetOperatingStatus(RESTART_WITH_RESET);			// actionEnCours = RESTART_WITH_RESET;
}

CString CDlgED42::createAffiche(CString motIn, CString motAjout, int lenAjout)
{
	CString chaineTmp;

	if (lenAjout == 1)
	{
		chaineTmp = motIn + motAjout;
	}
	else
	{
		for (int x=0;x<(19 - lenAjout); x++)
		{
			if (x == 0)
				chaineTmp = motIn + motAjout;
			else
				chaineTmp = chaineTmp + motAjout;
		}
	}

	return chaineTmp;
}

//****************************************************************
// Traitements de la touche
// flagAddFonc : TRUE si la fonction de la touche est une fonction
// flagFW : TRUE si le traitement de la touche est la fonction FW
//****************************************************************
void CDlgED42::TraitementTouches(CString dcp1, CString dcp2, bool flagAddFonc, bool flagFW)
{

	CString chaineTmp;
	CString chaineIn(dcp2);
	std::string s1((LPCTSTR)chaineIn);
	std::string s2((LPCTSTR)chaineEnCours);
	int lenChIn = s1.length() - s2.length();
	int lenChS2 = s2.length();

	if (flagAddFonc)
	{
		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(dcp1);
		//chaineTmp = createAffiche(chaineIn, (" "), lenChIn) + "S";
		chaineTmp = createAffiche(chaineIn, (" "), 0) + "S";
		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(chaineTmp);
		chaineEnCours = chaineIn;
		return;
	}

	if(flagFW)
	{
		std::string s3 = s2.substr(0, lenChS2-1);
		chaineIn = chaineIn + s3.c_str();
		lenChIn = s1.length() - s3.length();
		chaineEnCours = s3.c_str();
	}
	else
	{
		if (chaineEnCours = "") {
			chaineEnCours = chaineEnCours + chaineSep;
			chaineEnCours.TrimLeft();
			chaineIn = chaineIn + chaineEnCours;
		}
	}

	chaineTmp = createAffiche(chaineIn, (" "), lenChIn) + "S";

	m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(dcp1);
	m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(chaineTmp);
}

//********************************************************************************
// Initialisation de l'affichage
// flag1 : avec(1)/sans(0) affichage (ligne 2) de la demande de saisie par le bouton "S"
// flag2 : ADU
//********************************************************************************
void CDlgED42::initAffichageUn(CString ligne1, CString ligne2, int flag1, bool flag2)
{
	OutputDebugString("Dans : CDlgED42::initAffichageUn!\n");

	chaineEnCours = "";
	chaineSep = " ";

	RazAffichage();

	CString chaineTmp;
	CString chaineIn(ligne2);
	std::string s((LPCTSTR)chaineIn);
	int lenChIn = s.length();

	switch(flag1)
	{
	case 0:
		chaineTmp = createAffiche(chaineIn, chaineSep, lenChIn);
		break;
	case 1:
		chaineTmp = createAffiche(chaineIn, chaineSep, lenChIn) + "S";
		break;
	default:
		chaineTmp = "";
		break;
	}
	m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(ligne1);
	m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(chaineTmp);
}

//********************************************************
// Verification du mot de passe de l'operateur
// Reference : Compact User Guide page 33/70
//********************************************
BOOL CDlgED42::userPasswordVerification(CString passwdTmp, string passWord)
{
	OutputDebugString("Dans : CDlgED42::userPasswordVerification !\n");

		bool ret = TRUE;

		CString ChS1(passwdTmp);
		std::string s1((LPCTSTR)ChS1);
		int lenChS1 = s1.length();

		std::string userPwTmp	= cstringTostring(passwdTmp);
		//std::string userPw		= ((CEquipED42*)equip)->GetUserPassWord();
		//std::string defPwd		= ((CEquipED42*)equip)->GetDefPassWord();


		if (lenChS1<5 || lenChS1>8)
			return false;

		if (eqp->getED42Lock())
		{
			OutputDebugString("Dans : CDlgED42::userPasswordVerification et if ((eqp->getED42Lock()) !\n");

			if (userPwTmp != passWord)
				return false;
		}

		if (eqp->GetOperatingStatus() == ACTIV_LOCAL_CTRL)
		{
			OutputDebugString("Dans : CDlgED42::userPasswordVerification et if (eqp->GetOperatingStatus() == ACTIV_LOCAL_CTRL) !\n");

			if (userPwTmp != passWord)
				return false;
		}
												 
		if (eqp->GetOperatingStatus() == USER_PW_VERIFICATION)
		{
			OutputDebugString("Dans : CDlgED42::userPasswordVerification et if (eqp->GetOperatingStatus() == USER_PW_VERIFICATION) !\n");

			if (userPwTmp != passWord)
				return false;
		}

		if (eqp->GetOperatingStatus() == ENTER_ZEROIZE_PW)
		{
			OutputDebugString("Dans : CDlgED42::userPasswordVerification et if (eqp->GetOperatingStatus() == USER_PW_VERIFICATION) !\n");

			if (userPwTmp != passWord)
				return false;
		}

		

		/*
		if ((eqp->getED42Lock() || actionEnCours1 == ENTER_ZEROIZE_PW ||
								  actionEnCours == USER_PW_VERIFICATION ||
								  actionEnCours == ACTIV_LOCAL_CTRL) &&
								  !eqp->GetStatusNl())
		{
			if (userPwTmp != userPw)
				return false;
		}

		
		if (actionEnCours1 == ENTER_ZEROIZE_PW && eqp->GetStatusNl())
		{
			if (userPwTmp != userPw)
				return false;
		}

		
		if (actionEnCours == USER_PW_VERIFICATION)
		{
			if (userPwTmp != userPw)
				return false;

		}
		

		if (eqp->GetStatusNl() && actionEnCours1 != ENTER_ZEROIZE_PW)
		{
			if (userPwTmp != defPwd)
				return false;
		}
		*/


		return ret;
	}

//*************************************
// Conversion CString vers string
//*************************************
string CDlgED42::cstringTostring(CString cstringIn)
{
	std::string stringOut((LPCTSTR)cstringIn);

	return stringOut;
}

//*************************************
// Gestion des menus
//*************************************
BOOL CDlgED42::MainMenu()
{
	bool ret = true;

	/*
	actionEnCours = MAIN_MENU;

	if (GetClavier())
	{
			switch(chaineSep[0])
			{
				case '8':
					actionEnCours = actionEnCours1;
					actionEnCours1 = CARVIDE;
					break;
				case '6':
					actionEnCours1++;
					break;
				case '2':
					actionEnCours = OFFLINE;
					actionEnCours1 = CARVIDE;
					break;
				case '4':
					actionEnCours1--;
					break;
			}

			if (actionEnCours1 == ED42_LOCK && eqp->getED42Lock())
				actionEnCours1 = ED42_UNLOCK;

			//if (actionEnCours1 == ED42_UNLOCK && !eqp->getED42Lock())
				//actionEnCours1 = ED42_LOCK;

			if (actionEnCours1 == ACTIVATE_OPMODE && eqp->GetOperatingStatus() == ONLINE)
				actionEnCours1 = STOP_ONLINE_MODE;

			if (actionEnCours1 == STOP_ONLINE_MODE && eqp->GetOperatingStatus() == OFFLINE)
				actionEnCours1 = ACTIVATE_OPMODE;

			if (actionEnCours1 > BIT)
				actionEnCours1 = EMI_TEST;

			if (actionEnCours1 < EMI_TEST)
				actionEnCours1 = BIT;

			if (chaineSep == "FW" || chaineSep[0] == '2')
			{
				actionEnCours = OFFLINE;
				chaineSep = (" ");
				actionEnCours1 = CARVIDE;
			}
	}

	initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[actionEnCours1].c_str());

	SetClavier(FALSE);
	*/
	return ret;
}

//*************************************
// Gestion du menu ED42_Lock
//*************************************
BOOL CDlgED42::ED42_Lock()
{
	bool ret = true;

	eqp->setED42Lock(TRUE);
	actionEnCours = eqp->GetOperatingStatus();

	return ret;
}

//*************************************
// Gestion du menu ED42_UnLock
//*************************************
BOOL CDlgED42::ED42_UnLock(bool inZeroize)
{
	OutputDebugString("Dans : début CDlgED42::ED42_UnLock(bool inZeroize)!\n");

	bool ret = true;

	if (inZeroize)
	{
		OutputDebugString("Dans : CDlgED42::ED42_UnLock(bool inZeroize) et if (inZeroize)!\n");
		initAffichageUn(OPERATING_STATUS[ENTER_ZEROIZE_PW].c_str(), OPERATING_STATUS[DEF_PW].c_str(),1);
		actionEnCours = ACTIV_LOCAL_CTRL;
		return ret;
	}
	//else {
		//OutputDebugString("Dans : CDlgED42::ED42_UnLock(bool inZeroize) et if (inZeroize) et else!\n");
		//initAffichageUn(OPERATING_STATUS[ED42_UNLOCK].c_str(), OPERATING_STATUS[USER_PW].c_str(),1);
	//}

	initAffichageUn(OPERATING_STATUS[ED42_UNLOCK].c_str(), OPERATING_STATUS[USER_PW].c_str(),1);

	if (actionEnCours1 == ENTER_ZEROIZE_PW)
	{
		OutputDebugString("Dans : CDlgED42::ED42_UnLock(bool inZeroize) et if (actionEnCours1 == ENTER_ZEROIZE_PW)!\n");
		initAffichageUn(OPERATING_STATUS[ENTER_USER_PW].c_str(), OPERATING_STATUS[USER_PW].c_str(),1);
	}

	OutputDebugString("Dans : fin CDlgED42::ED42_UnLock(bool inZeroize)!\n");
	//actionEnCours = ACTIV_LOCAL_CTRL;

	return ret;
}

//*************************************
// Gestion du menu Activ_Local_Ctrl
//*************************************
BOOL CDlgED42::Activ_Local_Ctrl()
{
	// TODO : Automate a simplifier et/ou modifier.
	OutputDebugString("Dans : CDlgED42::Activ_Local_Ctrl()!\n");

	int ret = SUCCESS;
	tmpPwd = "";

	if (GetClavier())
	{
		OutputDebugString("Dans : CDlgED42::Activ_Local_Ctrl() et if (GetClavier())!\n");

		m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(chaineEnCours);

		if(eqp->GetChaineClavier() == "FW" && chaineEnCours == "")
		{
			OutputDebugString("Dans : CDlgED42::Activ_Local_Ctrl() et if (GetClavier()) et if(eqp->GetChaineClavier() == 'FW' && chaineEnCours == '')!\n");

			m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(false);
			m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
			m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(false);
			m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);

			eqp->SetOperatingStatus(actionEnCoursTmp);

			eqp->SetChaineClavier("");
			SetClavier(FALSE);
			return ret;
		}

		if(eqp->GetChaineClavier() == "FW")
		{
			OutputDebugString("Dans : CDlgED42::Activ_Local_Ctrl() et if (GetClavier()) et if(eqp->GetChaineClavier() == 'FW')!\n");

			m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(true);
			m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
			m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(true);
			m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);
			eqp->SetChaineClavier("");
			return ret;
		}


		if(eqp->GetChaineClavier() == "V")
		{
			OutputDebugString("Dans : CDlgED42::Activ_Local_Ctrl() et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V')!\n");

			if (actionEnCours1 == ACTIV_LOCAL_CTRL)
			{
				OutputDebugString("Dans : CDlgED42::Activ_Local_Ctrl() et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V') et if (actionEnCours1 == ED42_UNLOCK)!\n");

				initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[USER_PW].c_str(), 1);

				m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(true);
				m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
				m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(true);
				m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);
				eqp->SetChaineClavier("");
				return ret;

			}
		}

		if(eqp->GetChaineClavier() == "V")
		{
			OutputDebugString("Dans : CDlgED42::Activ_Local_Ctrl() et if (GetClavier()) et if(eqp->GetChaineClavier() == 'V')!\n");

			initAffichageUn(OPERATING_STATUS[ACTIV_LOCAL_CTRL].c_str(), OPERATING_STATUS[USER_PW].c_str());

			actionEnCours1 = ACTIV_LOCAL_CTRL;
			chaineSep = "";
			eqp->SetChaineClavier("");
		}

		 //****************************
		// Validation du mot de passe ?
		//*****************************
		if (eqp->GetChaineClavier() == "ST")
		{
			OutputDebugString("Dans : CDlgED42::Activ_Local_Ctrl() et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST')!\n");

			m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(chaineEnCours);

			if (userPasswordVerification(chaineEnCours, eqp->GetUserPassWord()))
			{
				OutputDebugString("Dans : CDlgED42::Activ_Local_Ctrl() et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST' et if (userPasswordVerification(chaineEnCours, eqp->GetUserPassWord())))!\n");

				initAffichageUn(OPERATING_STATUS[ACTIV_LOCAL_CTRL].c_str(), OPERATING_STATUS[SUCCESSFUL].c_str());

				actionEnCours1 = ACTIV_LOCAL_CTRL;
				actionEnCours2 = CARVIDE;

				eqp->SetOperatingStatus(ACTIV_LOCAL_CTRL_1);
				eqp->setRemoteStatus(FALSE);
				//remoteMode = FALSE;
				eqp->SetRemoteTC(LOCAL_TC);

				m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(false);
				m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
				m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(false);
				m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(false);

			}else
			{
				OutputDebugString("Dans : CDlgED42::Activ_Local_Ctrl() et if (GetClavier()) et if (eqp->GetChaineClavier() == 'ST' et if (userPasswordVerification(chaineEnCours, eqp->GetUserPassWord()))) et else!\n");
				initAffichageUn(OPERATING_STATUS[ACTIV_LOCAL_CTRL].c_str(), OPERATING_STATUS[INCORRECT].c_str());
				actionEnCours1 = ACTIV_LOCAL_CTRL;
				actionEnCours2 = INCORRECT;							   
				eqp->SetOperatingStatus(ACTIV_LOCAL_CTRL_2);
				m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
			}

			chaineSep = "";
			eqp->SetChaineClavier("");
		}
	}

	SetClavier(FALSE);

	return ret;
}

//************************************
// Saisie au clavier
//************************************
CString CDlgED42::saisieClavier()
{
	CString touche("");

	return touche;
}

//*************************************
// Gestion du menu Cv_Data_Crypto
//*************************************
BOOL CDlgED42::Cv_Data_Crypto()
{
	OutputDebugString("Dans : CDlgED42::Cv_Data_Crypto() !\n");

	bool ret = true;

	/*
	eqp->SetOperatingStatus(CV_DATA_CRYPTO);		//actionEnCours = CV_DATA_CRYPTO;

	if (GetClavier())
		{
			OutputDebugString("Dans : CDlgED42::Cv_Data_Crypto() et if (GetClavier())!\n");

			if (chaineSep == "FW" || chaineSep[0] == '2')
			{
				eqp->SetOperatingStatus(OFFLINE);	//actionEnCours = OFFLINE;
				chaineSep = (" ");
				actionEnCours1 = CARVIDE;
				actionEnCours2 = actionEnCours1;
			}
	}

	initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), "");
	*/

	return ret;
}

//*************************************
// Gestion du menu Cv_Voice_Crypto
//*************************************
BOOL CDlgED42::Cv_Voice_Crypto()
{
	OutputDebugString("Dans : CDlgED42::Cv_Voice_Crypto() !\n");

	bool ret = true;

	/*
	eqp->SetOperatingStatus(CV_VOICE_CRYPTO);		//CV_VOICE_CRYPTO;

	// TODO

	if (GetClavier())
		{
			OutputDebugString("Dans : CDlgED42::Cv_Voice_Crypto() et if (GetClavier())!\n");

			if (chaineSep == "FW" || chaineSep[0] == '2')
			{
				eqp->SetOperatingStatus(OFFLINE);	//actionEnCours = OFFLINE;
				chaineSep = (" ");
				actionEnCours1 = CARVIDE;
				actionEnCours2 = actionEnCours1;
			}
	}

	initAffichageUn(OPERATING_STATUS[eqp->GetOperatingStatus()].c_str(), "");
	*/

	return ret;
}
/* **************************************************************************
METHODE :		MiseEnMarche
TRAITEMENT:		Mise en marche de l'équipement
***************************************************************************/
BOOL CDlgED42::MiseEnMarche()
{
	OutputDebugString("Dans : début CDlgED42::MiseEnMarche() !\n");

	bool ret = true;

	KillTimer(1);

	ret = eqp->PowerOnBit();

    if (eqp->GetStatusNl() == FALSE)
	{
		OutputDebugString("Dans : début CDlgED42::MiseEnMarche() et if (eqp->GetStatusNl() == FALSE)!\n");

		if (eqp->GetDefPassWord().length() <= 2)
		{
			eqp->SetOperatingStatus(CARVIDE);	//actionEnCours	= CARVIDE;
		}else
		{
			if (eqp->GetOnlinePreset() == DEFAULT_INVALID_VALUE_ED42)
				eqp->SetOperatingStatus(OFFLINE);	//actionEnCours	= OFFLINE;
			else
				eqp->SetOperatingStatus(ONLINE);	//actionEnCours	= ONLINE;
		}
		actionEnCours1	= CARVIDE;
		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[eqp->GetOperatingStatus()].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[actionEnCours1].c_str());
	}
	else
	{
		OutputDebugString("Dans : début CDlgED42::MiseEnMarche() et if (eqp->GetStatusNl() == FALSE et else)!\n");

		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[ZEROIZE_ALARM].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[RESTART_WITH_RESET].c_str());

		if (eqp->GetMarcheEd42())
		{
			OutputDebugString("Dans : début CDlgED42::MiseEnMarche() et if (eqp->GetStatusNl() == FALSE et else et if (eqp->GetMarcheEd42()))!\n");
			eqp->SetOperatingStatus(ZEROIZE_ALARM_C);	//actionEnCours = ZEROIZE_ALARM_C;
		}
	}

	eqp->SetMarcheEd42(true);
	eqp->SetResetEd42(false);
	eqp->setRepetition(false);
	eqp->setLastNumber(0);
	GestionBoutonLockUnlock();

	//Mise à jour de la variable statusS20 (attente de INI, TAK et PWCHK)
	eqp->SetStatusS20(3);

	//Effacement des tables
	eqp->RAZTable();

	SetTimer(1,DUREETIMER,NULL);

	OutputDebugString("Dans : fin CDlgED42::MiseEnMarche() !\n");

	return ret;
}



void CDlgED42::OnChecksum()
{
	UpdateData(FALSE);

	eqp->setStatusErrorTable(SYNTAX_RCS, c_checksum.GetCheck() == 1);
}

void CDlgED42::OnNumMsg()
{
	eqp->setErrorMSG(c_errorNumMsg.GetCheck()==1);
}

void CDlgED42::OnFinTrame()
{
	eqp->setErrorLF(c_pasDeLf.GetCheck()==1);
	OnKillfocusRetard();
}

void CDlgED42::OnDebutTrame()
{
	eqp->setErrorCR(c_pasDeCr.GetCheck()==1);
	OnKillfocusRetard();
}

void CDlgED42::OnPasReponse()
{
	eqp->setPasDeReponse(c_pasDeReponse.GetCheck()==1);
	OnKillfocusRetard();
}

void CDlgED42::OnCdeInconue()
{
	eqp->setStatusErrorTable(UNKNOWN_COMMAND, c_cdeInconnue.GetCheck()==1);
	OnKillfocusRetard();
}

void CDlgED42::OnKillfocusRetard()
{
	//t_ComErreur	err;

	CButton		*m_debut	= (CButton*)GetDlgItem(IDC_DEBUT_TRAME);
	CButton		*m_fin		= (CButton*)GetDlgItem(IDC_FIN_TRAME);
	CButton		*m_inconnue = (CButton*)GetDlgItem(IDC_CDE_INCONUE);
	CButton		*m_reponse	= (CButton*)GetDlgItem(IDC_PAS_REPONSE);

	err.pas_debut		= m_debut->GetCheck();
	err.pas_fin			= m_fin->GetCheck();
	err.cde_inconnue	= m_inconnue->GetCheck();
	err.pas_de_reponse	= m_reponse->GetCheck();

	UpdateData(TRUE);
	err.retard = atoi(m_err_retard);

	equip->ChangeComErreur(err);
}


void CDlgED42::affichgeExploitation()
{
	OutputDebugString("Dans : début CDlgED42::affichgeExploitation() !\n");

	if(!eqp->GetMarcheEd42())
		return;

	char buffer[3] = {0};

	//int opm = ((CEquipED42*)equip)->GetOperatingMode();
	int pra = eqp->GetOnlinePreset();

	if(actionEnCoursTmp == ONLINE)
	{
		OutputDebugString("Dans : début CDlgED42::affichgeExploitation() et if(eqp->GetOperatingStatus() == ONLINE)!\n");
		if (eqp->GetOnlinePreset() == DEFAULT_INT_VALUE_ED42)
			return;

		int presetExploit = (pra -(pra/8)*8) + 1;
		string presetExploitString = "";

		m_dlgTab->m_Info->GetDlgItem(IDC_OPE_MODE)->SetWindowText(OPERATION_MODES[((CEquipED42*)equip)->GetOperatingMode()].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_TRANS_MODE)->SetWindowText(TRANSMISSION_MODES[((CEquipED42*)equip)->GetTransmissionMode()].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_TRANS_PRECED)->SetWindowText(TRANSMISSION_PROCEDURES[((CEquipED42*)equip)->GetTransmissionProcedure()].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_TRAF_MODE)->SetWindowText(TRAFFIC_MODES[((CEquipED42*)equip)->GetTraficMode()].c_str());

		switch(eqp->GetOperatingMode())
		{
		OutputDebugString("Dans : début CDlgED42::affichgeExploitation() et switch(eqp->GetOperatingMode())!\n");
		case DATA_CRYPRO:
		case OPE_MASTER:
			// Mise à jour de Activate key et update.
			if(eqp->GetTransmissionMode() == DIGITAL || eqp->GetTransmissionMode() == DIG5BIT)
			{
				m_dlgTab->m_Info->GetDlgItem(IDC_ACT_KEY)->SetWindowText("XX");
				m_dlgTab->m_Info->GetDlgItem(IDC_UPD_COUNT)->SetWindowText("XX");
			}
			else
			{
				itoa(eqp->GetActivatedKey(),buffer,10);
				m_dlgTab->m_Info->GetDlgItem(IDC_ACT_KEY)->SetWindowText(buffer);
				itoa(eqp->GetKeyManagement(buffer).updateCount,buffer,10);
				m_dlgTab->m_Info->GetDlgItem(IDC_UPD_COUNT)->SetWindowText(buffer);
			}
			//Mise à jour du preset Online
			presetExploitString = "DC";
			break;
		case DATA_PLAIN:
			//Mise à jour du preset Online
			presetExploitString = "DP";
			// Mise à jour de Activate key et update.
			m_dlgTab->m_Info->GetDlgItem(IDC_ACT_KEY)->SetWindowText("PLAIN");
			m_dlgTab->m_Info->GetDlgItem(IDC_UPD_COUNT)->SetWindowText("-");
			break;
		case VOICE_PLAIN:
			//Mise à jour du preset Online
			presetExploitString = "VP";
			// Mise à jour de Activate key et update.
			m_dlgTab->m_Info->GetDlgItem(IDC_ACT_KEY)->SetWindowText("PLAIN");
			m_dlgTab->m_Info->GetDlgItem(IDC_UPD_COUNT)->SetWindowText("-");
			break;
		case VOICE_CRYPRO:
			// Mise à jour de Activate key et update.
			itoa(eqp->GetActivatedKey(),buffer,10);
			m_dlgTab->m_Info->GetDlgItem(IDC_ACT_KEY)->SetWindowText(buffer);
			itoa(eqp->GetKeyManagement(buffer).updateCount,buffer,10);
			m_dlgTab->m_Info->GetDlgItem(IDC_UPD_COUNT)->SetWindowText(buffer);

			//Mise à jour du preset Online
			presetExploitString = "VC";
			break;
		}

		// Mise à jour du preset online.
		m_dlgTab->m_Info->GetDlgItem(IDC_PRESET_EXPLOIT)->SetWindowText(presetExploitString.append(PRESET_CONFIGURATION[presetExploit]).c_str());

		//Mise à jour de Data Rate
		itoa(eqp->GetOnlinePreset(),buffer,10);
		m_dlgTab->m_Info->GetDlgItem(IDC_DAT_RATE)->SetWindowText(DATA_RATE_SHORT[eqp->GetGeneralParameters(buffer).data_rate].c_str());

		BuildComposant(IDC_TRANS_MODE, pra);
		BuildComposant(IDC_TRANS_PRECED, pra);
		BuildComposant(IDC_TRAF_MODE, pra);
		BuildComposant(IDC_DAT_RATE, pra);

		//Pour le bouton Activation désactivation
		m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_ACT_DESACT)->SetWindowText("Désactiver");
		m_dlgTab->m_Info->c_operationMode.EnableWindow(FALSE);
		m_dlgTab->m_Info->c_preset.EnableWindow(FALSE);
	}
	else if(actionEnCoursTmp == OFFLINE && equip->Actif())
	{
		OutputDebugString("Dans : début CDlgED42::affichgeExploitation() et if(eqp->GetOperatingStatus() == ONLINE) et else if(eqp->GetOperatingStatus() == OFFLINE && equip->Actif())!\n");

		m_dlgTab->m_Info->c_Transmission_Mode.EnableWindow(TRUE);
		m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(TRUE);
		m_dlgTab->m_Info->c_Trafic_Mode.EnableWindow(TRUE);
		m_dlgTab->m_Info->GetDlgItem(IDC_OPE_MODE)->SetWindowText(OPERATION_MODES[OPE_NA].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_TRANS_MODE)->SetWindowText(TRANSMISSION_MODES[TRXM_NA].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_TRANS_PRECED)->SetWindowText(TRANSMISSION_PROCEDURES[TRXP_NA].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_TRAF_MODE)->SetWindowText(TRAFFIC_MODES[TXM_NA].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_PRESET_EXPLOIT)->SetWindowText(PRESET_CONFIGURATION[32].c_str());

		m_dlgTab->m_Info->GetDlgItem(IDC_ACT_KEY)->SetWindowText("-");
		m_dlgTab->m_Info->GetDlgItem(IDC_UPD_COUNT)->SetWindowText("-");
		m_dlgTab->m_Info->GetDlgItem(IDC_DAT_RATE)->SetWindowText("-");

		m_dlgTab->m_Info->c_dataRate.ShowWindow(FALSE);
		m_dlgTab->m_Info->c_dataRateString.ShowWindow(FALSE);


		//Pour le bouton Activation désactivation
		m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_ACT_DESACT)->SetWindowText("Activer");
		m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_ACT_DESACT)->EnableWindow(eqp->GetRemoteTC() == LOCAL_TC &&
																		 !eqp->getED42Lock() &&
																		  eqp->GetStatusBusy() == 0);
		m_dlgTab->m_Info->c_operationMode.EnableWindow(eqp->GetRemoteTC() == LOCAL_TC && !eqp->getED42Lock());
		m_dlgTab->m_Info->c_preset.EnableWindow(eqp->GetRemoteTC() == LOCAL_TC && !eqp->getED42Lock());

		GestionAffichageExploitation(FALSE);
	}

	//Affichage des élément pour l'activation ou la désactivation d'un preset
	if (eqp->GetRemoteTC() == REMOTE_TC)
		m_dlgTab->m_Info->c_operationMode.SetCurSel(eqp->GetOperatingMode());
	m_dlgTab->m_Info->c_operationMode.ShowWindow(eqp->GetRemoteTC() == LOCAL_TC &&
												 eqp->GetMarcheEd42() == TRUE &&
												 actionEnCours != RESTART_WITH_RESET &&
												!eqp->GetStatusNl());
	if (eqp->GetOperatingMode() == DATA_CRYPRO && eqp->GetRemoteTC() == REMOTE_TC)
		m_dlgTab->m_Info->c_preset.SetCurSel(eqp->GetOnlinePreset());
	if (eqp->GetOperatingMode() == VOICE_CRYPRO && eqp->GetRemoteTC() == REMOTE_TC)
		m_dlgTab->m_Info->c_preset.SetCurSel(eqp->GetOnlinePreset()-8);
	if (eqp->GetOperatingMode() == DATA_PLAIN && eqp->GetRemoteTC() == REMOTE_TC)
		m_dlgTab->m_Info->c_preset.SetCurSel(eqp->GetOnlinePreset()-16);
	if (eqp->GetOperatingMode() == VOICE_PLAIN && eqp->GetRemoteTC() == REMOTE_TC)
		m_dlgTab->m_Info->c_preset.SetCurSel(eqp->GetOnlinePreset()-24);
	m_dlgTab->m_Info->c_preset.ShowWindow(eqp->GetRemoteTC() == LOCAL_TC &&
										  eqp->GetMarcheEd42() == TRUE &&
										  actionEnCours != RESTART_WITH_RESET &&
										 !eqp->GetStatusNl());
	m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_ACT_DESACT)->ShowWindow(eqp->GetRemoteTC() == LOCAL_TC &&
																	eqp->GetMarcheEd42() &&
																	actionEnCours != RESTART_WITH_RESET &&
																	!eqp->GetStatusNl() &&
																	eqp->GetStatusBusy() == 0);
	//EnableWindow
	m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_ACT_DESACT)->EnableWindow(!eqp->getED42Lock());


	GestionAffichage();

	OutputDebugString("Dans : fin CDlgED42::affichgeExploitation() !\n");
}

void CDlgED42::GestionAffichageEmRec(bool val)
{

	// Gestion des case à cocher Emi, Rec, Call et Sync
	m_dlgTab->m_Info->c_explEmi.SetCheck(eqp->GetStatusTx());
	m_dlgTab->m_Info->c_explRec.SetCheck(eqp->GetStatusRx());
	m_dlgTab->m_Info->c_explCall.SetCheck(eqp->GetStatusCall());
	m_dlgTab->m_Info->c_explSync.SetCheck(eqp->GetStatusSync());

	m_dlgTab->m_Info->GetDlgItem(IDC_STATIC_EM_REC)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_CHECK_EMI)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_CHECK_REC)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_CHECK_CALL)->ShowWindow(val);
	m_dlgTab->m_Info->GetDlgItem(IDC_CHECK_SYNC)->ShowWindow(val);
}

//******************************************
void CDlgED42::BuildComposant(int composant, int preset)
{
	if (!equip->Actif())
		return;

	//-----------------------------------------------------------------------------
	//-----                      DATA CRYPTO                                  -----
	//-----------------------------------------------------------------------------
	if(preset>=0 && preset<8)
	{
		switch(composant)
		{
		//--------------Construction du combo transmission procédure--------------
		case IDC_TRANS_MODE:
			if(eqp->GetTransmissionMode() == DIGITAL)
			{
				m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(TRUE);
			}
			else
				m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(FALSE);
			break;
		//--------------Construction du combo traffic mode--------------
		case IDC_TRANS_PRECED:
			if(eqp->GetTransmissionMode() == DIGITAL)
			{
				m_dlgTab->m_Info->c_Trafic_Mode.EnableWindow(TRUE);

			}
			else
			{
				m_dlgTab->m_Info->c_Trafic_Mode.EnableWindow(FALSE);
			}
			break;
					//--------------Construction du combo traffic mode--------------
		case IDC_TRAF_MODE:
			switch(eqp->GetTransmissionMode())
			{
			case DIGITAL:
				m_dlgTab->m_Info->c_Trafic_Mode.EnableWindow(TRUE);
				break;
			case VUHFANA:
			case VUHFDIG:
				m_dlgTab->m_Info->c_Trafic_Mode.EnableWindow(TRUE);
				break;
			default:
				m_dlgTab->m_Info->c_Trafic_Mode.EnableWindow(FALSE);
				break;
			}
			break;
		//-------------- Construction du DATA RATE --------------
		case IDC_DAT_RATE:
			//m_dlgTab->m_Info->c_dataRateString.ShowWindow(TRUE && !eqp->GetStatusNl() && eqp->Actif());
			//m_dlgTab->m_Info->c_dataRate.ShowWindow(TRUE && !eqp->GetStatusNl() && eqp->Actif());
			break;
		}//fin du switch IDC
	}
	//-----------------------------------------------------------------------------
	//-----                      VOICE CRYPTO                                 -----
	//-----------------------------------------------------------------------------
	else if(preset>=8 && preset<16) //
	{
		switch(composant)
		{
		//--------------Construction du combo transmission mode--------------
		case IDC_TRANS_MODE:
			m_dlgTab->m_Info->c_Transmission_Mode.EnableWindow(TRUE);
			break;
		//--------------Construction du combo transmission procédure--------------
		case IDC_TRANS_PRECED:
			switch(((CEquipED42*)equip)->GetTransmissionMode())
			{
			case HF:
				m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(TRUE);
				break;
			case DIGITAL:
				m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(TRUE);
				break;
			case VUHFANA:
			case VUHFDIG:
				m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(TRUE);
				break;
			default:
				m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(FALSE);
				break;
			}
			break;
		//--------------Construction du combo traffic mode--------------
		case IDC_TRAF_MODE:
			switch(eqp->GetTransmissionMode())
			{
			case DIGITAL:
				m_dlgTab->m_Info->c_Trafic_Mode.EnableWindow(TRUE);
				break;
			case VUHFANA:
			case VUHFDIG:
				m_dlgTab->m_Info->c_Trafic_Mode.EnableWindow(TRUE);
				break;
			default:
				m_dlgTab->m_Info->c_Trafic_Mode.EnableWindow(FALSE);
				break;
			}
			break;
		//-------------- Construction du DATA RATE --------------
		case IDC_DAT_RATE:
			m_dlgTab->m_Info->c_dataRateString.ShowWindow(FALSE);
			m_dlgTab->m_Info->c_dataRate.ShowWindow(FALSE);
			break;
		}//fin du switch IDC
	}
	//-----------------------------------------------------------------------------
	//-----                      DATA PLAIN                                   -----
	//-----------------------------------------------------------------------------
	else if(preset>=16 && preset<24)
	{
		switch(composant)
		{
		//--------------Construction du combo transmission mode--------------
		case IDC_TRANS_MODE:
			m_dlgTab->m_Info->c_Transmission_Mode.EnableWindow(TRUE);
			break;
		//--------------Construction du combo transmission procédure--------------
		case IDC_TRANS_PRECED:
			if(eqp->GetTransmissionMode() == DIGITAL)
			{
				m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(TRUE);
			}
			else
				m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(FALSE);
			break;
		//--------------Construction du combo traffic mode--------------
		case IDC_TRAF_MODE:
			m_dlgTab->m_Info->c_Trafic_Mode.EnableWindow(FALSE);
			break;
		//-------------- Construction du DATA RATE --------------
		case IDC_DAT_RATE:
			//m_dlgTab->m_Info->c_dataRateString.ShowWindow(TRUE && !eqp->GetStatusNl() && eqp->Actif());
			//m_dlgTab->m_Info->c_dataRate.ShowWindow(TRUE && !eqp->GetStatusNl() && eqp->Actif());
			break;
		//--------------Construction du combo sync mode--------------
		}//fin du switch IDC
	}
	//-----------------------------------------------------------------------------
	//-----                      VOICE PLAIN                                  -----
	//-----------------------------------------------------------------------------
	else if(preset>=24 && preset<32)
	{
		switch(composant)
		{
		//--------------Construction du combo transmission mode--------------
		case IDC_TRANS_MODE:
			m_dlgTab->m_Info->c_Transmission_Mode.EnableWindow(TRUE);
			break;
		//--------------Construction du combo transmission procédure--------------
		case IDC_TRANS_PRECED:
			m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(FALSE);
			break;
		//--------------Construction du combo traffic mode--------------
		case IDC_TRAF_MODE:
			m_dlgTab->m_Info->c_Trafic_Mode.EnableWindow(FALSE);
			break;
		//-------------- Construction du DATA RATE --------------
		case IDC_DAT_RATE:
			m_dlgTab->m_Info->c_dataRateString.ShowWindow(FALSE);
			m_dlgTab->m_Info->c_dataRate.ShowWindow(FALSE);
			break;
		}//fin du switch IDC
	}
}

void CDlgED42::GestionBoutonLockUnlock()
{
	OutputDebugString("Dans : CDlgED42::GestionBoutonLockUnlock() !\n");

	if (eqp->GetMarcheEd42() && eqp->GetRemoteTC() == LOCAL_TC && !eqp->GetStatusNl())
	{
		m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->ShowWindow(TRUE);

			if (eqp->getED42Lock() && eqp->GetMarcheEd42())
			{
				m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->SetWindowText("ED4-2 UNLOCK");
				m_dlgTab->m_Info->c_lockUnlock.EnableWindow(FALSE);
				if (eqp->GetChaineClavier() == "V" && eqp->GetOperatingStatus() != ED42_UNLOCK)
				{
					eqp->SetOperatingStatus(ED42_UNLOCK);		//actionEnCours = ED42_UNLOCK;
				}
			}else{
				m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->SetWindowText("ED4-2 LOCK");
				m_dlgTab->m_Info->c_lockUnlock.EnableWindow(TRUE);
			}

		}else{
			m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->ShowWindow(FALSE);
	}

		if (eqp->GetOperatingStatus() == RESTART_WITH_RESET)
			m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->ShowWindow(FALSE);
}



void CDlgED42::sortieDebug(string param1, int param2, int param3)
{
	char buffer [3];
	string AfficherDebug;

	itoa (param2,buffer,10);

	AfficherDebug.append(param1);
	AfficherDebug.append(" : ");
	AfficherDebug.append(buffer);
	AfficherDebug.append(" : ");
	AfficherDebug.append(OPERATING_STATUS[param2].c_str());
	AfficherDebug.append(" !\n");

	OutputDebugString(AfficherDebug.c_str());
}
