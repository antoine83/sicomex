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


extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_ED42[];
extern char glob_REPERTOIRE[];


#define DUREEHT	DUREE1MN


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

	m_hIcon		= AfxGetApp()->LoadIcon(IDB_EQP_ED42);
	etat		= FALSE;
	isNum		= TRUE;				// TRUE = Touches numeriques
	remoteMode	= FALSE;
	valBool		= FALSE;

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
	//int	iResult;

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
	lockTimeChecker = 0;
	m_timerEd		= 0;

	//t_ComErreur	err;
	char	buf[10];
	eqp = (CEquipED42*) equip;

	SetClavier(FALSE);

	chaineSep		= (" ");
	actionEnCours	= TRAIT;
	actionEnCours1	= CARVIDE;
	actionEnCours2	= CARVIDE;

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
	GestionBoutonLockUnlock();
	GestionAffichageEmRec(FALSE);
;

	//	Armement du timer
	SetTimer(1,DUREE1S,NULL);

	eqp->setReceptionDonnee(FALSE);

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
	eqp->SetKeStatus(ret2);	 // Traitement de CE State - KEStatus
	eqp->setSecureMode(ret3);

}

/* **************************************************************************
METHODE :		OnNl()
TRAITEMENT:		Action sur le bouton NL
***************************************************************************	*/
void CDlgED42::OnNl()
{
// TODO (afaddi#1#): Mise à jour des actions
	int	iResult = m_nl.Inverse_etat();

	eqp->ChangeNl(iResult);

	RazEd42();
	remoteMode = FALSE;
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
	//if (eqp->GetMarcheEd42() != FALSE)
	if (eqp->GetMarcheEd42())
	{
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

	bool presencePowerBitError = FALSE;

	CDialog::OnTimer(nIDEvent);

	chaineSep = eqp->GetChaineClavier().c_str();

	if (eqp->GetStatusBusy() == 1)
		SetTimer(11,500,NULL);

	//IDC_CHECK_FULL
	m_dlgTab->m_Info->GetDlgItem(IDC_CHECK_FULL)->ShowWindow(eqp->GetMarcheEd42() && !eqp->GetResetEd42() && !eqp->GetStatusNl());

	// Mise en place de password lock time
	if (m_timerEd != 9 && eqp->GetPasswordHoldTime() != 0 && !eqp->getED42Lock() && !eqp->getRemoteStatus())
		m_timerEd = SetTimer(9,DUREEHT*eqp->GetPasswordHoldTime(),NULL);

	// Traitement de TAMPER
	if (eqp->GetKeStatus() == TAMPER)
	{
		eqp->SetStatusNl(1);
		RazEd42();
		remoteMode = FALSE;
		eqp->SetRemoteTC(LOCAL_TC);
		//actionEnCours = ZEROIZE_ALARM;
		eqp->SetKeStatus(KE_IDLE);
	}


	// Traitement de RS
	if (eqp->GetResetEd42())
	{
		KillTimer(m_timerEd);
		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[RESTART_WITH_RESET].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());
		actionEnCours = RESTART_WITH_RESET;
		actionEnCours1 = CARVIDE;
		actionEnCours2 = CARVIDE;
		SetTimer(6,DUREE2S,NULL);
		eqp->SetResetEd42(false);
		// Mise à jour des flag's
		eqp->SetPresetList("255",'X');
		eqp->SetOnlinePresetStatus(1);					// Param 21 : Flag : Online preset
		eqp->SetActiveKeyState(1);						// Param 29 : Flag : Active KEY state
		eqp->SetKeyList(1);								// Param 25 : Flag : key list
		eqp->SetOperatingStatus(OFFLINE);
		eqp->SetOnlinePreset(DEFAULT_INVALID_VALUE_ED42);
		eqp->SetActivatedKey(DEFAULT_INVALID_VALUE_ED42);
		eqp->SetStatusTx(0);
		eqp->SetStatusRx(0);
		m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
		m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
		m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);
		m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);
	}

	// Traitement de ZEROIZE
	if (eqp->GetStatusNl() && actionEnCours != MA &&
		                      actionEnCours != ZEROIZE_ALARM_C &&
							  actionEnCours != ZEROIZE_ALARM_S &&
							  actionEnCours != ACTIV_LOCAL_CTRL &&
							  actionEnCours != ACTIV_LOCAL_CTRL_1 &&
							  actionEnCours != ACTIV_LOCAL_CTRL_2 &&
							  actionEnCours != ENTER_ZEROIZE_PW &&
							  actionEnCours != ENTER_USER_PW &&
							  actionEnCours != ONLINE)
	{
		actionEnCours = ZEROIZE_ALARM;
	}

	// Affichage des pannes
	c_checksum.SetCheck(eqp->getStatusErrorTable(SYNTAX_RCS) /*|| eqp->getStatusErrorRCS()*/);

	switch (nIDEvent)
	{
		case 1:
			if(equip->Actif() != etat)
			{
				etat = equip->Actif();
					if(etat == FALSE)
					{
						RazEd42();
					}
					else
					{
						if (!eqp->GetStatusNl())
						{
							m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[TRAIT].c_str());
							m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[TRAIT].c_str());
							SetTimer(2,DUREE2S,NULL);
							actionEnCours = MA;
						}else{
							MiseEnMarche();
							GestionAffichageBoutons(FALSE);
						}
					}
			}
			//***********************************************
			switch (actionEnCours)
			{
				case MA:
					break;
				case TRAIT:
					break;
				case ED42_INITIALISATION:
					break;
				case POWER_ON_BIT:
					break;
				case ZEROIZE_ALARM_S:
					break;
				case ZEROIZE_ALARM:
					if (etat)
					{
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[ZEROIZE_ALARM].c_str());
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[RESTART_WITH_RESET].c_str());
						actionEnCours = ZEROIZE_ALARM_S;
					}
					else
					{
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());
					}
					break;
				case RESTART_WITH_RESET:
					// Gestion Des Affichages
					GestionAffichageExploitation(FALSE);
					GestionAffichageEmRec(FALSE);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->ShowWindow(FALSE);
					// Mise à jour des flag's
					eqp->SetOnlinePresetStatus(0);					// Param 21 : Flag : Online preset
					eqp->SetKeyList(1);								// Param 25 : Flag : key list
					eqp->SetActiveKeyState(0);						// Param 29 : Flag : Active KEY state
					eqp->SetOperatingStatus(OFFLINE);
					eqp->SetOnlinePreset(DEFAULT_INVALID_VALUE_ED42);
					eqp->SetRemoteTC(LOCAL_TC);
					eqp->SetStatusTx(0);
					eqp->SetStatusRx(0);
					break;
				case ENTER_ZEROIZE_PW:
					if (GetClavier())
					{
						if (chaineSep == "ST")
						{
							TraitementTouches(OPERATING_STATUS[ENTER_ZEROIZE_PW].c_str(), OPERATING_STATUS[DEF_PW].c_str(), NULL, TRUE);
							SetClavier(FALSE);
							isNum = TRUE;
							actionEnCours = DEF_PW;
						}
					}else
					{
							m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[ED42_INITIALISATION].c_str());
							m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[POWER_ON_BIT].c_str());
					}
					break;
				case DEF_PW:
					//*******************************
					// Traitement de Default password
					//*******************************
					eqp->SetOperatingStatus(DEF_PW);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->ShowWindow(FALSE);
					eqp->SetFullSimu(false);
					//
					TraitementTouches(OPERATING_STATUS[ENTER_ZEROIZE_PW].c_str(), OPERATING_STATUS[DEF_PW].c_str(), TRUE);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(!(chaineSep == "V") && !(chaineSep == "FW"));

					if (GetClavier())
					{
						if (chaineSep == "V")
						{
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(TRUE);
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[DEF_PW].c_str());
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(TRUE);
						}

						if (chaineSep == "ST")
						{
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
							actionEnCours = ENTER_USER_PW;
						}

						if (chaineSep == "FW")
						{
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
					if (GetClavier() && eqp->GetMarcheEd42())
					{
						m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(TRUE);
						res = ED42_UnLock();

						SetClavier(FALSE);
						break;
					}
					// Configuration Usine
					eqp->SetOperatingStatus(ENTER_USER_PW);
					TraitementTouches(OPERATING_STATUS[ENTER_USER_PW].c_str(), OPERATING_STATUS[USER_PW].c_str(), TRUE);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(!(chaineSep == "V") && !(chaineSep == "FW"));

					if (GetClavier())
					{
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[ENTER_USER_PW].c_str());

						if (chaineSep == "V")
						{
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(TRUE);
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[USER_PW].c_str());
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(TRUE);
						}

						if (chaineSep == "ST")
						{
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
							actionEnCours = USER_PW_VERIFICATION;
						}

						if (chaineSep == "FW")
						{
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(TRUE);
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(TRUE);
						}

						SetClavier(FALSE);
					}
					break;
				case USER_PW_VERIFICATION:
					eqp->SetOperatingStatus(USER_PW_VERIFICATION);
					TraitementTouches(OPERATING_STATUS[USER_PW_VERIFICATION].c_str(), OPERATING_STATUS[USER_PW].c_str(), TRUE);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(!(chaineSep == "V") && !(chaineSep == "FW"));

					if (GetClavier())
					{
						m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[USER_PW_VERIFICATION].c_str());

						if (chaineSep == "V")
						{
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(TRUE);
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[USER_PW].c_str());
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(TRUE);
						}

						if (chaineSep == "ST")
						{
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(chaineEnCours);

							CString ChS1(chaineEnCours);
							std::string s1((LPCTSTR)ChS1);
							int lenChS1 = s1.length();


							if (lenChS1<5 || lenChS1>8 || !userPasswordVerification(chaineEnCours))
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
							actionEnCours = LANGUAGE_SELECTION;
						}

						if (chaineSep == "FW")
						{
							m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(TRUE);
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
							m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(TRUE);
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
					eqp->SetOperatingStatus(LANGUAGE_SELECTION);
					TraitementTouches(OPERATING_STATUS[LANGUAGE_SELECTION].c_str(), LANGUAGES_SELECTION[eqp->GetLanguage()].c_str(), TRUE);
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(TRUE);

					if (GetClavier())
					{
						SetClavier(FALSE);

						if (chaineSep == "V")
						{
							if (eqp->GetLanguage() == GERMAIN)
							{
								eqp->SetLanguage(ENGLICH);
								break;
							}
						}

						if (chaineSep == "V")
						{

							if (eqp->GetLanguage() == ENGLICH)
							{
								eqp->SetLanguage(GERMAIN);
								break;
							}
						}

						if (chaineSep == "ST")
						{
							actionEnCours = OFFLINE;
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
					//********
					// OFFLINE
					//********
					valBool = eqp->getRemoteStatus();

					actionEnCours = eqp->GetOperatingStatus();

					UpdateData(FALSE);

					// Gestion Des Affichages
					GestionAffichageExploitation(FALSE);
					GestionAffichageEmRec(FALSE);

					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(eqp->GetRemoteTC() == REMOTE_TC || eqp->getED42Lock());

					//if(valBool!= remoteMode)
					if(eqp->GetRemoteTC() == REMOTE_TC)
					{
							initAffichageUn(OPERATING_STATUS[OFFLINE].c_str(), OPERATING_STATUS[REMOTE_MODE].c_str());
							//eqp->SetOperatingStatus(OFFLINE);
							eqp->setED42Lock(FALSE); //TODO
							remoteMode = valBool;
							//m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(TRUE);
					}

					if(eqp->GetRemoteTC() == LOCAL_TC)
						initAffichageUn(OPERATING_STATUS[OFFLINE].c_str(), "");

					if (actionEnCours == OFFLINE && eqp->GetRemoteTC() == REMOTE_TC)
						initAffichageUn(OPERATING_STATUS[OFFLINE].c_str(), OPERATING_STATUS[REMOTE_MODE].c_str());


					if (GetClavier())
					{
						//if(eqp->GetChaineClavier() == "V" && eqp->getRemoteStatus())
						if(eqp->GetChaineClavier() == "V" && eqp->GetRemoteTC() == REMOTE_TC)
						{
							if (actionEnCours != INCORRECT)
							{
								initAffichageUn(OPERATING_STATUS[MAIN_MENU].c_str(), OPERATING_STATUS[ACTIV_LOCAL_CTRL].c_str());
								actionEnCours = ACTIV_LOCAL_CTRL;
								isNum = FALSE;
							}
						}

						if (eqp->GetChaineClavier() == "V")
						{
							chaineSep = "";
							eqp->SetChaineClavier("");

							if (eqp->getED42Lock())
								actionEnCours = ED42_UNLOCK;
						}

						SetClavier(FALSE);
					}

					// Mise à jour des vues
					if (eqp->getModifVue())
						m_dlgTab->m_KeyManagementTab->LoadData();

					break;
				case ONLINE:
					initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[REMOTE].c_str());

					if (actionEnCours == ONLINE && eqp->GetRemoteTC() == REMOTE_TC)
						initAffichageUn(OPERATING_STATUS[CARVIDE].c_str(), OPERATING_STATUS[REMOTE_ONLINE].c_str());

					actionEnCours = eqp->GetOperatingStatus();

					// Gestion des Affichages
					GestionAffichageEmRec(TRUE);
					GestionAffichageExploitation(TRUE);

					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(eqp->GetRemoteTC() == REMOTE_TC || eqp->getED42Lock());


					if (GetClavier())
					{
						if(eqp->GetChaineClavier() == "V" && eqp->GetRemoteTC() == REMOTE_TC)
						{
							if (actionEnCours != INCORRECT)
							{
								initAffichageUn(OPERATING_STATUS[MAIN_MENU].c_str(), OPERATING_STATUS[ACTIV_LOCAL_CTRL].c_str());
								actionEnCours = ACTIV_LOCAL_CTRL;
								isNum = FALSE;
							}
						}

						if (eqp->GetChaineClavier() == "V")
						{
							chaineSep = "";
							eqp->SetChaineClavier("");

							if (eqp->getED42Lock())
								actionEnCours = ED42_UNLOCK;
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
								MainMenu();
								break;
							case ACTIV_LOCAL_CTRL:
								res = Activ_Local_Ctrl();
								if (res == ENTER_ZEROIZE_PW )
									actionEnCours = ENTER_USER_PW;
								if (res == REMOTE_TC_A && eqp->GetOnlinePreset() == DEFAULT_INVALID_VALUE_ED42)
									actionEnCours = OFFLINE;
								if (res == REMOTE_TC_A && eqp->GetOnlinePreset() != DEFAULT_INVALID_VALUE_ED42)
									actionEnCours = ONLINE;
								break;
							case ACTIV_LOCAL_CTRL_1:		// SUCCESS
								break;
							case ACTIV_LOCAL_CTRL_2:		// INCORRECT
								m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(TRUE);
								break;
							case ED42_LOCK:
								break;
							case ED42_UNLOCK:
								res = ED42_UnLock();
								break;
							case ZEROIZE_ALARM_C:
								m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(eqp->GetStatusNl());
								res = ED42_UnLock(true);
								break;
							case CV_DATA_CRYPTO:
								Cv_Data_Crypto();
								break;
							case CV_VOICE_CRYPTO:
								Cv_Voice_Crypto();
								break;
							case INCORRECT:
								break;
						}

					break;
			}
			break;
			case 2:
				KillTimer(1);
				KillTimer(2);
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[TRAIT_G].c_str());
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[TRAIT_D].c_str());
				SetTimer(3,DUREE4S,NULL);
				break;
			case 3:
				KillTimer(3);
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[TRAIT_D].c_str());
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[TRAIT_G].c_str());
				SetTimer(4,DUREE4S,NULL);
				break;
			case 4:
				KillTimer(4);
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[ED42_INITIALISATION].c_str());
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[POWER_ON_BIT].c_str());
				SetTimer(5,DUREE4S,NULL);
				break;
			case 5:
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
						actionEnCours = DEF_PW;
						eqp->SetMarcheEd42(false);
						chaineSep = "";
					}

				}

				break;
			case 6:								// RST0
				KillTimer(6);
				//eqp->setRemoteStatus(FALSE);
				//eqp->setRemoteMode(LOCAL);
				remoteMode = FALSE;
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[TRAIT].c_str());
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[TRAIT].c_str());
				SetTimer(2,DUREE1S,NULL);
				break;
            case 7:
				KillTimer(7);
				if (actionEnCours == ACTIV_LOCAL_CTRL_2)
				{
					actionEnCours = ACTIV_LOCAL_CTRL;
					actionEnCours1 = ACTIV_LOCAL_CTRL_2;
					eqp->SetChaineClavier("");
				}
				if (actionEnCours == ACTIV_LOCAL_CTRL_1)
				{
					//actionEnCours = OFFLINE;
					actionEnCours = eqp->GetOperatingStatus();
				}
                break;
			case 8:
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
			case 9:							//LOCK&UNLOCK
				KillTimer(9);
				m_timerEd = 0;
				eqp->setED42Lock(TRUE);
				break;
			case 10:								// After Zeroize/Emergency Clear page 83
				KillTimer(10);
				eqp->setRemoteStatus(FALSE);
				eqp->setRemoteMode(LOCAL);
				eqp->SetRemoteTC(LOCAL_TC);
				remoteMode = FALSE;
				SetTimer(4,DUREE4S,NULL);
				//eqp->ChangeNl(0);
				break;
			case 11:								// After Zeroize/Emergency Clear page 83
				KillTimer(11);
				eqp->SetStatusBusy(0);
				break;
	}

	// Mise à jour de la vue exploitation
	affichgeExploitation();
	//GetState

// Presence CIK
	m_cik.Positionne_etat(((CEquipED42*)equip)->GetStateCik() != NO_CIK_STATE);
// Presence NL
	m_nl.Positionne_etat(((CEquipED42*)equip)->InfoNl());
// Presence EG
	m_eg.Positionne_etat(((CEquipED42*)equip)->InfoEg());

//Vérifie si on a reçu une donnée à mettre à jour
	if(eqp->getReceptionDonnee())
	{
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

	if (val)
		m_dlgTab->m_Info->GetDlgItem(IDC_OPE_MODE)->SetWindowText("-");
}
//*****************************************
// GestionAffichage fonction OFFLINE/ONLINE
//*****************************************
void CDlgED42::GestionAffichage(bool val, int param1, int param2)
{
	if (eqp->GetFullSimu())
	{
		m_dlgTab->m_tab.EnableTab(1, eqp->GetMarcheEd42() &&
									!eqp->getRemoteStatus() &&
									!eqp->getED42Lock() &&
									!eqp->GetStatusNl());				//Operating Parameters

		m_dlgTab->m_tab.EnableTab(2, eqp->GetMarcheEd42() &&
									!eqp->getRemoteStatus() &&
									!eqp->GetStatusNl());				//Key Management

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
		m_dlgTab->m_KeyManagementTab->c_tab.EnableTab(0, true);				//Display
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

}

//********
// RazEd42
//********
void CDlgED42::RazEd42()
{
	RazAffichage();
	GestionAffichageExploitation(FALSE);
	((CEquipED42*)equip)->setRemoteStatus(FALSE);
	eqp->SetRemoteTC(LOCAL_TC);
	GestionAffichageBoutons(eqp->GetStatusNl());
	GestionAffichageEmRec(FALSE);

	m_dlgTab->m_Info->c_operationMode.ShowWindow(FALSE);
	m_dlgTab->m_Info->c_preset.ShowWindow(FALSE);
	m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_ACT_DESACT)->ShowWindow(FALSE);

	valBool = FALSE;
	remoteMode = FALSE;
	actionEnCours = TRAIT;


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
}

//*****************************
// Fonctions pour chaque touche
//*****************************
void CDlgED42::OnEd42DcpBtnFw()
{
	if (eqp->GetStatusNl() && actionEnCours != ACTIV_LOCAL_CTRL)
		return;

	eqp->SetChaineClavier("FW");
	eqp->SetClavier(TRUE);

	//Recherche si une valeur a changé
	if(eqp->getModifVue())
	{
		m_dlgTab->LoadData();
		eqp->setModifVue(FALSE);
	}
}

void CDlgED42::OnEd42DcpBtnSt()
{
	if (eqp->GetStatusNl() && actionEnCours != ACTIV_LOCAL_CTRL)
		return;

	eqp->SetChaineClavier("ST");
	eqp->SetClavier(TRUE);

	m_dlgTab->SaveData();
	eqp->setModifVue(FALSE);
}

void CDlgED42::OnEd42DcpBtnRs()
{
	//eqp->SetChaineClavier("RS");
	//eqp->SetClavier(TRUE);
	eqp->SetResetEd42(true);
	actionEnCours = RESTART_WITH_RESET;
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
BOOL CDlgED42::userPasswordVerification(CString passwdTmp)
	{
		bool ret = TRUE;

		CString ChS1(passwdTmp);
		std::string s1((LPCTSTR)ChS1);
		int lenChS1 = s1.length();

		std::string userPwTmp	= cstringTostring(passwdTmp);
		std::string userPw		= ((CEquipED42*)equip)->GetUserPassWord();
		std::string defPwd		= ((CEquipED42*)equip)->GetDefPassWord();


		if (lenChS1<5 || lenChS1>8)
			return !ret;

		if (eqp->getED42Lock())
		{
			if (userPwTmp != userPw)
				return !ret;

			//if (userPwTmp == defPwd)
				//return !ret;
		}

		if (actionEnCours1 == ENTER_ZEROIZE_PW)
		{
			if (userPwTmp != userPw)
				return !ret;

			//if (userPwTmp == defPwd)
				//return !ret;
		}


		if (actionEnCours == USER_PW_VERIFICATION)
		{
			if (userPwTmp != userPw)
				return !ret;

		}

		if (eqp->GetStatusNl() && actionEnCours1 != ENTER_ZEROIZE_PW)
		{
			if (userPwTmp != defPwd)
				return !ret;

			//if (userPwTmp == defPwd)
				//return !ret;
		}


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
	bool ret = true;

	if (inZeroize)
		initAffichageUn(OPERATING_STATUS[ENTER_ZEROIZE_PW].c_str(), OPERATING_STATUS[DEF_PW].c_str(),1);
	else
		initAffichageUn(OPERATING_STATUS[ED42_UNLOCK].c_str(), OPERATING_STATUS[USER_PW].c_str(),1);

	if (actionEnCours1 == ENTER_ZEROIZE_PW)
	{
		initAffichageUn(OPERATING_STATUS[ENTER_USER_PW].c_str(), OPERATING_STATUS[USER_PW].c_str(),1);
	}

	actionEnCours = ACTIV_LOCAL_CTRL;

	return ret;
}

//*************************************
// Gestion du menu Activ_Local_Ctrl
//*************************************
BOOL CDlgED42::Activ_Local_Ctrl()
{
	// TODO : Automate a simplifier et/ou modifier.

	if (eqp->GetRemoteTC() == REMOTE_TC && chaineSep == "FW")
	{
		SetClavier(FALSE);
		eqp->SetChaineClavier("");
		m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
		m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
		m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);
		return REMOTE_TC_A;
	}

	int ret = SUCCESS;
	tmpPwd = "";

	if (GetClavier() || actionEnCours2 == INCORRECT)
	{
		actionEnCours2 = CARVIDE;

		if (eqp->getED42Lock())
			actionEnCours = ED42_UNLOCK;

		if (chaineSep == "V" && (eqp->getED42Lock() || eqp->GetStatusNl()) && !isNum)
		{
			if (eqp->GetStatusNl())
				initAffichageUn(OPERATING_STATUS[ENTER_ZEROIZE_PW].c_str(), OPERATING_STATUS[DEF_PW].c_str(),1);
			else
				initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[USER_PW].c_str(),1);

			isNum = TRUE;
			chaineEnCours = "";
			if (actionEnCours == ACTIV_LOCAL_CTRL) return actionEnCours;
			m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);
		}

		m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(tmpPwd);

		if (chaineSep != "ST")
		{
			m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(TRUE);

			if (eqp->GetStatusNl())
				m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[DEF_PW].c_str());

			//if (actionEnCours1 == ENTER_ZEROIZE_PW)
				//m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[ENTER_USER_PW].c_str());

			if (eqp->getED42Lock() || actionEnCours1 == ENTER_ZEROIZE_PW || eqp->GetRemoteTC() == REMOTE_TC)
				m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->SetWindowText(OPERATING_STATUS[ENTER_USER_PW].c_str());

			m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(TRUE);
			m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
			m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);
			if (chaineSep != "FW")
			{
				chaineSep = "";

				if (eqp->getED42Lock())
					TraitementTouches(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[USER_PW].c_str(), FALSE, FALSE);
				else{
					if (actionEnCours1 == ENTER_ZEROIZE_PW || eqp->GetRemoteTC() == REMOTE_TC)
						TraitementTouches(OPERATING_STATUS[ENTER_USER_PW].c_str(), OPERATING_STATUS[USER_PW].c_str(), FALSE, FALSE);
					else
						TraitementTouches(OPERATING_STATUS[ENTER_ZEROIZE_PW].c_str(), OPERATING_STATUS[DEF_PW].c_str(), FALSE, FALSE);
				}
			}
			else {
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());
				m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[CARVIDE].c_str());

				if (eqp->getED42Lock())
					TraitementTouches(OPERATING_STATUS[actionEnCours].c_str(), OPERATING_STATUS[USER_PW].c_str(), FALSE, TRUE);
				else
					if (actionEnCours1 == ENTER_ZEROIZE_PW)
							TraitementTouches(OPERATING_STATUS[ENTER_USER_PW].c_str(), OPERATING_STATUS[USER_PW].c_str(), FALSE, TRUE);
						else
							TraitementTouches(OPERATING_STATUS[ENTER_ZEROIZE_PW].c_str(), OPERATING_STATUS[DEF_PW].c_str(), FALSE, TRUE);

				if ((eqp->getED42Lock() || eqp->GetStatusNl())  && chaineSep == "FW")
				{
					if (tmpPwd == "")
					{
						actionEnCours = eqp->GetOperatingStatus();
						m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
						m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
						m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);
					}else
						m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText(_T(""));
				}
			}
		}
		else
		{
			m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->GetWindowText(chaineEnCours);

			if (userPasswordVerification(chaineEnCours))
			{
				eqp->setRemoteStatus(FALSE);
				remoteMode = FALSE;
				//eqp->setRemoteMode(LOCAL);
				eqp->SetRemoteTC(LOCAL_TC);
				actionEnCours = ACTIV_LOCAL_CTRL_1;

				//if (eqp->GetStatusNl() && actionEnCours1 == CARVIDE && actionEnCours1 != ED42_UNLOCK && actionEnCours1 != USER_PW_VERIFICATION)
				if (eqp->GetStatusNl() && actionEnCours1 == CARVIDE)
				{
					actionEnCours1 = ENTER_ZEROIZE_PW;
					ret = ENTER_ZEROIZE_PW;
				}
				else{
					if(actionEnCours1 == ENTER_ZEROIZE_PW)
					{
						actionEnCours1 = USER_PW_VERIFICATION;
						eqp->ChangeNl(0);
						if (!eqp->GetZeroizeStatus())
							eqp->SetKeStatus(KE_IDLE);
						eqp->SetKEState(1);						// Param 28 : Flag : KE state
					}
					else
					{
						actionEnCours1 = ED42_UNLOCK;
					}
				}

				eqp->setED42Lock(FALSE);
				//eqp->ChangeNl(0);
				actionEnCours2 = SUCCESSFUL;
				chaineSep = " ";
				m_dlgTab->m_Info->m_user_pwd.Empty();
				m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_8)->ShowWindow(FALSE);
				m_dlgTab->m_Info->GetDlgItem(IDC_USER_PWD)->ShowWindow(FALSE);
				m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->ShowWindow(FALSE);

				if (eqp->GetOperatingStatus() == ONLINE)
					m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_ACT_DESACT)->ShowWindow(TRUE);
			}
			else
			{
				m_dlgTab->m_Info->m_user_pwd.Empty();
				m_dlgTab->m_Info->GetDlgItem(IDC_EDIT_USER_PWD)->SetWindowText("");
				actionEnCours = ACTIV_LOCAL_CTRL_2;
				if (eqp->GetStatusNl())
					actionEnCours1 = ENTER_ZEROIZE_PW;
					else
					actionEnCours1 = ED42_UNLOCK;
				actionEnCours2 = INCORRECT;
				chaineSep = " ";
				ret = INCORRECT;
			}
			initAffichageUn(OPERATING_STATUS[actionEnCours1].c_str(), OPERATING_STATUS[actionEnCours2].c_str());
			SetTimer(7,DUREE10S,NULL);
		}
	}

	if (ret != ENTER_ZEROIZE_PW)
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
	bool ret = true;

	actionEnCours = CV_DATA_CRYPTO;

	if (GetClavier())
		{
			if (chaineSep == "FW" || chaineSep[0] == '2')
			{
				actionEnCours = OFFLINE;
				chaineSep = (" ");
				actionEnCours1 = CARVIDE;
				actionEnCours2 = actionEnCours1;
			}
	}

	initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), "");

	return ret;
}

//*************************************
// Gestion du menu Cv_Voice_Crypto
//*************************************
BOOL CDlgED42::Cv_Voice_Crypto()
{
	bool ret = true;

	actionEnCours = CV_VOICE_CRYPTO;

	// TODO

	if (GetClavier())
		{
			if (chaineSep == "FW" || chaineSep[0] == '2')
			{
				actionEnCours = OFFLINE;
				chaineSep = (" ");
				actionEnCours1 = CARVIDE;
				actionEnCours2 = actionEnCours1;
			}
	}

	initAffichageUn(OPERATING_STATUS[actionEnCours].c_str(), "");

	return ret;
}
/* **************************************************************************
METHODE :		MiseEnMarche
TRAITEMENT:		Mise en marche de l'équipement
***************************************************************************/
BOOL CDlgED42::MiseEnMarche()
{
	bool ret = true;

	KillTimer(1);

	ret = ((CEquipED42*)equip)->PowerOnBit();

    if (((CEquipED42*)equip)->GetStatusNl() == FALSE)
	{
		if (eqp->GetDefPassWord().length() <= 2)
		{
			actionEnCours	= CARVIDE;
		}else
		{
			actionEnCours	= OFFLINE;
		}
		actionEnCours1	= CARVIDE;
		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[actionEnCours].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[actionEnCours1].c_str());
	}
	else
	{
		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_1)->SetWindowText(OPERATING_STATUS[ZEROIZE_ALARM].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_ED42_DCP_2)->SetWindowText(OPERATING_STATUS[RESTART_WITH_RESET].c_str());

		if (eqp->GetMarcheEd42())
			actionEnCours = ZEROIZE_ALARM_C;
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

	return ret;
}



void CDlgED42::OnChecksum()
{
	UpdateData(FALSE);

	((CEquipED42*)equip)->setStatusErrorTable(SYNTAX_RCS, c_checksum.GetCheck() == 1);
}

void CDlgED42::OnNumMsg()
{
	((CEquipED42*)equip)->setErrorMSG(c_errorNumMsg.GetCheck()==1);
}

void CDlgED42::OnFinTrame()
{
	((CEquipED42*)equip)->setErrorLF(c_pasDeLf.GetCheck()==1);
	OnKillfocusRetard();
}

void CDlgED42::OnDebutTrame()
{
	((CEquipED42*)equip)->setErrorCR(c_pasDeCr.GetCheck()==1);
	OnKillfocusRetard();
}

void CDlgED42::OnPasReponse()
{
	((CEquipED42*)equip)->setPasDeReponse(c_pasDeReponse.GetCheck()==1);
	OnKillfocusRetard();
}

void CDlgED42::OnCdeInconue()
{
	((CEquipED42*)equip)->setStatusErrorTable(UNKNOWN_COMMAND, c_cdeInconnue.GetCheck()==1);
	OnKillfocusRetard();
}

void CDlgED42::OnKillfocusRetard()
{
	//t_ComErreur	err;

	CButton		*m_debut = (CButton*)GetDlgItem(IDC_DEBUT_TRAME);
	CButton		*m_fin = (CButton*)GetDlgItem(IDC_FIN_TRAME);
	CButton		*m_inconnue = (CButton*)GetDlgItem(IDC_CDE_INCONUE);
	CButton		*m_reponse = (CButton*)GetDlgItem(IDC_PAS_REPONSE);

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
	if(!eqp->GetMarcheEd42())
		return;

	char buffer[3] = {0};

	//int opm = ((CEquipED42*)equip)->GetOperatingMode();
	int pra = ((CEquipED42*)equip)->GetOnlinePreset();

	if(eqp->GetOperatingStatus() == ONLINE)
	{
		if (((CEquipED42*)equip)->GetOnlinePreset() == DEFAULT_INT_VALUE_ED42)
			return;

		int presetExploit = (pra -(pra/8)*8) + 1;
		string presetExploitString = "";

		m_dlgTab->m_Info->GetDlgItem(IDC_OPE_MODE)->SetWindowText(OPERATION_MODES[((CEquipED42*)equip)->GetOperatingMode()].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_TRANS_MODE)->SetWindowText(TRANSMISSION_MODES[((CEquipED42*)equip)->GetTransmissionMode()].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_TRANS_PRECED)->SetWindowText(TRANSMISSION_PROCEDURES[((CEquipED42*)equip)->GetTransmissionProcedure()].c_str());
		m_dlgTab->m_Info->GetDlgItem(IDC_TRAF_MODE)->SetWindowText(TRAFFIC_MODES[((CEquipED42*)equip)->GetTraficMode()].c_str());

		switch(((CEquipED42*)equip)->GetOperatingMode())
		{
		case DATA_CRYPRO:
		case OPE_MASTER:
			// Mise à jour de Activate key et update.
			if(((CEquipED42*)equip)->GetTransmissionMode() == DIGITAL || ((CEquipED42*)equip)->GetTransmissionMode() == DIG5BIT)
			{
				m_dlgTab->m_Info->GetDlgItem(IDC_ACT_KEY)->SetWindowText("XX");
				m_dlgTab->m_Info->GetDlgItem(IDC_UPD_COUNT)->SetWindowText("XX");
			}
			else
			{
				itoa(((CEquipED42*)equip)->GetActivatedKey(),buffer,10);
				m_dlgTab->m_Info->GetDlgItem(IDC_ACT_KEY)->SetWindowText(buffer);
				itoa(((CEquipED42*)equip)->GetKeyManagement(buffer).updateCount,buffer,10);
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
			itoa(((CEquipED42*)equip)->GetActivatedKey(),buffer,10);
			m_dlgTab->m_Info->GetDlgItem(IDC_ACT_KEY)->SetWindowText(buffer);
			itoa(((CEquipED42*)equip)->GetKeyManagement(buffer).updateCount,buffer,10);
			m_dlgTab->m_Info->GetDlgItem(IDC_UPD_COUNT)->SetWindowText(buffer);

			//Mise à jour du preset Online
			presetExploitString = "VC";
			break;
		}

		// Mise à jour du preset online.
		m_dlgTab->m_Info->GetDlgItem(IDC_PRESET_EXPLOIT)->SetWindowText(presetExploitString.append(PRESET_CONFIGURATION[presetExploit]).c_str());

		//Mise à jour de Data Rate
		itoa(((CEquipED42*)equip)->GetOnlinePreset(),buffer,10);
		m_dlgTab->m_Info->GetDlgItem(IDC_DAT_RATE)->SetWindowText(DATA_RATE_SHORT[((CEquipED42*)equip)->GetGeneralParameters(buffer).data_rate].c_str());

		BuildComposant(IDC_TRANS_MODE, pra);
		BuildComposant(IDC_TRANS_PRECED, pra);
		BuildComposant(IDC_TRAF_MODE, pra);
		BuildComposant(IDC_DAT_RATE, pra);

		//Pour le bouton Activation désactivation
		m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_ACT_DESACT)->SetWindowText("Désactiver");
		m_dlgTab->m_Info->c_operationMode.EnableWindow(FALSE);
		m_dlgTab->m_Info->c_preset.EnableWindow(FALSE);
	}
	else if(eqp->GetOperatingStatus() == OFFLINE && equip->Actif())
	{
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
		m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_ACT_DESACT)->EnableWindow(eqp->GetRemoteTC() == LOCAL_TC && !eqp->getED42Lock());
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
																!eqp->GetStatusNl());
	//EnableWindow
	m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_ACT_DESACT)->EnableWindow(!eqp->getED42Lock());

	GestionAffichage();
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
			if(((CEquipED42*)equip)->GetTransmissionMode() == DIGITAL)
			{
				m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(TRUE);
			}
			else
				m_dlgTab->m_Info->c_Transmission_Procedure.EnableWindow(FALSE);
			break;
		//--------------Construction du combo traffic mode--------------
		case IDC_TRANS_PRECED:
			if(((CEquipED42*)equip)->GetTransmissionMode() == DIGITAL)
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
			switch(((CEquipED42*)equip)->GetTransmissionMode())
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
			switch(((CEquipED42*)equip)->GetTransmissionMode())
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
			if(((CEquipED42*)equip)->GetTransmissionMode() == DIGITAL)
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
	if (eqp->GetMarcheEd42() && eqp->GetRemoteTC() == LOCAL_TC && !eqp->GetStatusNl())
	{
		m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->ShowWindow(TRUE);

		if (eqp->getED42Lock() && eqp->GetMarcheEd42())
		{
			m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->SetWindowText("ED4-2 UNLOCK");
			m_dlgTab->m_Info->c_lockUnlock.EnableWindow(FALSE);
			if (eqp->GetChaineClavier() == "V"){
				actionEnCours = ED42_UNLOCK;
			}
		}else{
			m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->SetWindowText("ED4-2 LOCK");
			m_dlgTab->m_Info->c_lockUnlock.EnableWindow(TRUE);
		}

		}else{
			m_dlgTab->m_Info->GetDlgItem(IDC_BUTTON_UNLOCK)->ShowWindow(FALSE);
	}

}
