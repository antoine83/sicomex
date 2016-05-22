// DLGCA150.cpp: implementation of the CDLGCA150 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sicomex.h"
#include "DLGCA150.h"
#include "Equip\EqpCA150.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_CA150[];

/* **************************************************************************
METHODE :		CDLGCA150()
TRAITEMENT:		Construction
***************************************************************************	*/
CDLGCA150::CDLGCA150(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDLGCA150::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGCA150)
	m_err_retard	= _T("");
	m_periode		= _T("");
	m_tempo			= _T("");
	m_texte_incidente	= _T("0");
	m_texte_reflechie	= _T("0");
	//}}AFX_DATA_INIT

	m_hIcon = AfxGetApp()->LoadIcon(IDB_CA_150);
}

/* **************************************************************************
METHODE :		DoDataExchange(CDataExchange* pDX)
TRAITEMENT:		Procedures d'echange
***************************************************************************	*/
void CDLGCA150::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGCA150)
	DDX_Control (pDX, IDC_MES_STATUT,	m_liste_message);
	DDX_Control (pDX, IDC_CHECK_SYNCHRO,m_synchro);
	DDX_Control (pDX, IDC_CHECK_CYCLE,	m_cycle);
	DDX_Text	(pDX, IDC_RETARD,		m_err_retard);
	DDX_Text	(pDX, IDC_EDIT_CYCLE,	m_periode);
	DDX_Text	(pDX, IDC_EDIT_TEMPO,	m_tempo);
	DDX_Text	(pDX, IDC_CA150_PIMAX,	m_pimax);
	DDX_Text	(pDX, IDC_CA150_PRMAX,	m_prmax);

	DDX_Control	(pDX, IDC_CA150_SH1,			m_SH[0]);
	DDX_Control	(pDX, IDC_CA150_SH2,			m_SH[1]);
	DDX_Control	(pDX, IDC_CA150_SH3,			m_SH[2]);
	DDX_Control	(pDX, IDC_CA150_SH4,			m_SH[3]);
	
	DDX_Control	(pDX, IDC_CA150_ENVOI_TS,		m_timer);
	DDX_Control	(pDX, IDC_CA150_DEFAUT,			m_defaut);
	DDX_Control	(pDX, IDC_CA150_ROS,			m_mauvais_ros);
	DDX_Control	(pDX, IDC_CA150_LOCAL,			m_local);
	DDX_Control	(pDX, IDC_CA150_HF1,			m_charge[1]);
	DDX_Control	(pDX, IDC_CA150_HF2,			m_charge[2]);
	DDX_Control	(pDX, IDC_CA150_HF3,			m_charge[3]);
	DDX_Control	(pDX, IDC_CA150_HF4,			m_charge[4]);
	DDX_Control	(pDX, IDC_CA150_HF5,			m_charge[5]);
	DDX_Control	(pDX, IDC_CA150_OP,				m_charge[6]);
	DDX_Control	(pDX, IDC_CA150_COMBINE,		m_combine);
	// Slide Bar
	DDX_Control	(pDX, IDC_CA150_INCIDENTE,		m_incidente);
	DDX_Text	(pDX, IDC_CA150_NB_INCIDENTE,	m_texte_incidente);
	DDX_Control	(pDX, IDC_CA150_SPIN_INCIDENTE,	m_spin_incidente);
	DDX_Control	(pDX, IDC_CA150_REFLECHIE,		m_reflechie);
	DDX_Text	(pDX, IDC_CA150_NB_REFLECHIE,	m_texte_reflechie);
	DDX_Control	(pDX, IDC_CA150_SPIN_REFLECHIE,	m_spin_reflechie);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGCA150, CDialog)
	//{{AFX_MSG_MAP(CDLGCA150)
	ON_WM_TIMER()
	
	ON_BN_CLICKED	(IDC_CDE_INCONUE,	OnComErreur)
	ON_BN_CLICKED	(IDC_DEBUT_TRAME,	OnComErreur)
	ON_BN_CLICKED	(IDC_FIN_TRAME,		OnComErreur)
	ON_EN_KILLFOCUS	(IDC_RETARD,		OnComErreur)
	ON_BN_CLICKED	(IDC_PAS_REPONSE,	OnComErreur)

	ON_BN_CLICKED	(IDC_CA150_VALIDER,	OnValider)
	ON_BN_CLICKED	(IDC_CA150_HF1,		OnCharge)
	ON_BN_CLICKED	(IDC_CA150_HF2,		OnCharge)
	ON_BN_CLICKED	(IDC_CA150_HF3,		OnCharge)
	ON_BN_CLICKED	(IDC_CA150_HF4,		OnCharge)
	ON_BN_CLICKED	(IDC_CA150_HF5,		OnCharge)
	ON_BN_CLICKED	(IDC_CA150_OP,		OnCharge)
	ON_BN_CLICKED	(IDC_CA150_COMBINE,	OnCharge)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_CA150_INCIDENTE,	OnSlideIncidente)
	ON_NOTIFY(UDN_DELTAPOS,	 IDC_CA150_SPIN_INCIDENTE,	OnSpinIncidente)
	ON_NOTIFY(UDN_DELTAPOS,	 IDC_CA150_SPIN_REFLECHIE,	OnSpinReflechie)
	ON_NOTIFY(NM_RELEASEDCAPTURE, IDC_CA150_REFLECHIE,	OnSlideReflechie)
	//}}AFX_MSG_MAP

	ON_WM_CLOSE()
	ON_WM_PAINT()

	// Activation des tache de comm
	ON_COMMAND		(IDC_ACTIVITE,					OnActivite)
	// Aide
	ON_COMMAND		(ID__AIDE,						OnAide)
	// Masquage de l'ecran de controle
	ON_COMMAND		(ID_AFF_CONTROLE,				OnClose)
	// Envoi de trame
	ON_BN_CLICKED	(IDC_ENVOI_TRAME,				OnEnvoiTrame)
	// Contexte d'exploitation
	ON_COMMAND		(ID_CONTEXTE_OUVRIR,			OnOuvrir)
	ON_COMMAND		(ID_CONTEXTE_SAUVER,			OnSauver)
	// journal
	ON_COMMAND		(ID_JOURNAL_COUPER,				OnCouper)
	ON_COMMAND		(ID_JOURNAL_COUPERTOUT,			OnCouperTout)
	ON_COMMAND		(ID_JOURNAL_ENREGISTRERSOUS,	OnSauvegarde)
	ON_BN_CLICKED	(IDC_PRECEDENT,					OnPrecedent)
	ON_BN_CLICKED	(IDC_SUIVANT,					OnSuivant)
	ON_LBN_DBLCLK	(IDC_JOURNAL,					OnDblclkJournal)
	// Sequence de message : fonction definies dans la classe de base
	ON_BN_CLICKED	(IDC_AJOUT_MESSAGE,				OnAjoutMessage)
	ON_BN_CLICKED	(IDC_RETIRE_MESSAGE,			OnRetireMessage)
	ON_BN_CLICKED	(IDC_CHECK_CYCLE,				OnCheckCycle)
	ON_BN_CLICKED	(IDC_CHECK_SYNCHRO,				OnCheckSynchro)
	ON_EN_KILLFOCUS	(IDC_EDIT_CYCLE,				OnKillfocusEditCycle)
	ON_EN_KILLFOCUS	(IDC_EDIT_TEMPO,				OnKillfocusEditTempo)
	ON_BN_CLICKED	(IDC_ENVOI_STATUT,				OnEnvoiStatut)
	ON_BN_CLICKED	(IDC_ARRET_STATUT,				OnArretStatut)

END_MESSAGE_MAP()


/* **************************************************************************
METHODE :		OnAide()
TRAITEMENT:		Boite de dialogue d'aide
***************************************************************************	*/
void CDLGCA150::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_CA150,"Multicoupleur CA150");
	if(iResult >=  0)
	{
		win.DoModal();
	}
}

/* **************************************************************************
METHODE :		OnInitDialog() 
TRAITEMENT:		Initialisation de la boite de dialogue
***************************************************************************	*/
BOOL CDLGCA150::OnInitDialog() 
{
	t_ComErreur	err;
	char		buf[10];
	int			i;

	CDialog::OnInitDialog();

	//	Armement du timer
	SetTimer(1,1000,NULL);	
	
	// Gestion des erreurs de communication
	// ************************************
	equip->RetourneComErreur(&err);
	sprintf(buf,"%d",err.retard);
	m_err_retard = buf;

	// Envoi de sequence de message
	// ****************************
	GetDlgItem(IDC_ENVOI_STATUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARRET_STATUT)->EnableWindow(FALSE);
	sprintf(buf,"%d",equip->DureeTempo());
	m_tempo = buf;
	sprintf(buf,"%d",equip->Periode());
	m_periode = buf;
	m_cycle.SetCheck(equip->EnvoiCyclique());
	m_synchro.SetCheck(equip->Synchronise());

	// Custom control
	// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);

	
	// Initialisation de la face avant
	// *******************************
	m_incidente.SetRange(0, 255);
	m_reflechie.SetRange(0, 255);

	if( ((CEquipCA150 *)equip)->TYPE == MASTER )
	{
		m_combine.ShowWindow(SW_SHOW);
		m_charge[5].ShowWindow(SW_HIDE);
	}
	if( ((CEquipCA150 *)equip)->TYPE == SLAVE )
	{
		m_combine.ShowWindow(SW_HIDE);
		m_charge[5].ShowWindow(SW_SHOW);
	}

	// Surchauffes
	for(i=0; i<4; i++)
	{
		if( ((CEquipCA150 *)equip)->SURCHAUFFE_HYBRIDE[i] )
			m_SH[i].SetCheck(1);
		else
			m_SH[i].SetCheck(0);
	}
	// TIMER
	if( ((CEquipCA150 *)equip)->TIMER )
		m_timer.SetCheck(1);
	else
		m_timer.SetCheck(0);
	// DEFAUT
	if( ((CEquipCA150 *)equip)->DEFAUT )
		m_defaut.SetCheck(1);
	else
		m_defaut.SetCheck(0);
	// mauvais ROS
	if( ((CEquipCA150 *)equip)->MAUVAIS_ROS )
		m_mauvais_ros.SetCheck(1);
	else
		m_mauvais_ros.SetCheck(0);
	// LOCAL
	if( ((CEquipCA150 *)equip)->LOCAL )
		m_local.SetCheck(1);
	else
		m_local.SetCheck(0);

	bCouple = false;
	
	// Validation de la position de la puissance incidente
	m_pimax = _T("5000");
	((CEquipCA150 *)equip)->PUISSANCE_INCIDENTE = m_incidente.GetPos();
	// Validation de la position de la puissance reflechie
	m_prmax = _T("5000");
	((CEquipCA150 *)equip)->PUISSANCE_REFLECHIE = m_reflechie.GetPos();

	UpdateData(FALSE);

	return TRUE;
}


/* **************************************************************************
METHODE :		GenerateurAuto()
TRAITEMENT:		Effectue les variations automatiques de certains composants
***************************************************************************	*/
void CDLGCA150::GenerateurAuto()
{
	if( ((CEquipCA150 *)equip)->TIMER )
		((CEquipCA150 *)equip)->EnvoiEtatCyclique();
}

/* **************************************************************************
METHODE :		OnTimer(UINT nIDEvent) 
TRAITEMENT:		Rafraichissement de l'ecran de controle
***************************************************************************	*/
void CDLGCA150::OnTimer(UINT nIDEvent) 
{
	int	 val, i;
	//char buf[10];				//2009-11-27

	UpdateData(TRUE);

	CDialog::OnTimer(nIDEvent);
	// Rafraichissement des controles commun
	CDlgEquip::OnTimer();

	// Test de changement dans la face avant
	val = equip->Evolution();
	// Rafraichissement inutile
	if(val==evolution)
	{
		return;
	}
	evolution = val;

	// Mise a jour de charge
	// HF1 a HF4
	for(i=1; i<=4; i++)
	{
		if( ((CEquipCA150 *)equip)->CHARGE[i] )
			m_charge[i].SetCheck(1);
		else
			m_charge[i].SetCheck(0);
	}
	// Cas Master
	if( ((CEquipCA150 *)equip)->TYPE == MASTER )
	{
		// O/P
		if( ((CEquipCA150 *)equip)->CHARGE[5] )
			m_charge[6].SetCheck(1);
		else
			m_charge[6].SetCheck(0);
		// Combine
		if( ((CEquipCA150 *)equip)->COMBINE)
		{
			m_combine.SetCheck(1);
			m_prmax = _T("9000");
			m_pimax = _T("9000");
			if(bCouple == false)
			{
				m_incidente.SetPos(0);
				m_texte_incidente = _T( "0" );
				m_reflechie.SetPos(0);
				m_texte_reflechie = _T( "0" );
				bCouple = true;
			}
		}
		if( !((CEquipCA150 *)equip)->COMBINE)
		{
			m_combine.SetCheck(0);
			m_pimax = _T("5000");
			m_prmax = _T("5000");
			if(bCouple == true)
			{			
				m_incidente.SetPos(0);
				m_texte_incidente = _T( "0" );
				m_reflechie.SetPos(0);
				m_texte_reflechie = _T( "0" );
				bCouple = false;
			}
		}
	}
	// Cas Slave
	if( ((CEquipCA150 *)equip)->TYPE == SLAVE )
	{
		// HF5
		if( ((CEquipCA150 *)equip)->CHARGE[5] )
			m_charge[5].SetCheck(1);
		else
			m_charge[5].SetCheck(0);
		// O/P
		if( ((CEquipCA150 *)equip)->CHARGE[6] )
			m_charge[6].SetCheck(1);
		else
			m_charge[6].SetCheck(0);
	}

	UpdateData(FALSE);
}

/* **************************************************************************
METHODE :		OnComErreur()
TRAITEMENT:		
***************************************************************************	*/
void CDLGCA150::OnComErreur() 
{
	t_ComErreur	err;
	
	CButton	*m_debut	= (CButton*)GetDlgItem(IDC_DEBUT_TRAME);
	CButton	*m_fin		= (CButton*)GetDlgItem(IDC_FIN_TRAME);
	CButton	*m_parite	= (CButton*)GetDlgItem(IDC_PARITE);
	CButton	*m_inconnue	= (CButton*)GetDlgItem(IDC_CDE_INCONUE);
	CButton	*m_reponse	= (CButton*)GetDlgItem(IDC_PAS_REPONSE);

	err.pas_debut		= m_debut->GetCheck();
	err.pas_fin			= m_fin->GetCheck();
	err.controle_parite	= m_parite->GetCheck();
	err.cde_inconnue	= m_inconnue->GetCheck();
	err.pas_de_reponse	= m_reponse->GetCheck();

	UpdateData(TRUE);
	err.retard = atoi(m_err_retard);
	equip->ChangeComErreur(err);
}

// Action par la face avant *****************************************************
// ******************************************************************************

/* **************************************************************************
METHODE :		Verrouille(BOOL etat)
TRAITEMENT:		Verrouillage de la face avant
***************************************************************************	*/
void CDLGCA150::Verrouille(BOOL etat)
{
	int i;

	// CheckBox TIMER
	m_timer.EnableWindow(etat);
	// Buttons SURCHAUFFE HYBRIDE
	for(i=0; i<4; i++)
		m_SH[i].EnableWindow(etat);
	// CheckBox DEFAUT
	m_defaut.EnableWindow(etat);
	// CheckBox MAUVAIS ROS
	m_mauvais_ros.EnableWindow(etat);
	// SlideBar Puissance incidente
	m_incidente.EnableWindow(etat);
	// SpinButton Puissance incidente
	m_spin_incidente.EnableWindow(etat);
	// SlideBar Puissance reflechie
	m_reflechie.EnableWindow(etat);
	// SpinButton Puissance reflechie
	m_spin_reflechie.EnableWindow(etat);
}

/* **************************************************************************
METHODE :		OnValider()
TRAITEMENT:		Valide l'etat de la matrice
***************************************************************************	*/
void CDLGCA150::OnValider()
{
	int  i;

	// Validation des surchauffes
	for(i=0; i<4; i++)
	{
		if(m_SH[i].GetCheck())
			((CEquipCA150 *)equip)->ChgtEtatSH(i, true);
		else
			((CEquipCA150 *)equip)->ChgtEtatSH(i, false);
	}
	// Validation de timer
	if(m_timer.GetCheck())
		((CEquipCA150 *)equip)->TIMER = true;
	else
		((CEquipCA150 *)equip)->TIMER = false;
	// Validation de defaut
	if(m_defaut.GetCheck())
		((CEquipCA150 *)equip)->DEFAUT = true;
	else
		((CEquipCA150 *)equip)->DEFAUT = false;
	// Validation du mauvais ROS
	if(m_mauvais_ros.GetCheck())
		((CEquipCA150 *)equip)->MAUVAIS_ROS = true;
	else
		((CEquipCA150 *)equip)->MAUVAIS_ROS = false;
	// Validation de local
	if(m_local.GetCheck())
		((CEquipCA150 *)equip)->LOCAL = true;
	else
		((CEquipCA150 *)equip)->LOCAL = false;
	
	// Validation de la position de la puissance incidente
	((CEquipCA150 *)equip)->PUISSANCE_INCIDENTE = m_incidente.GetPos();
	// Validation de la position de la puissance reflechie
	((CEquipCA150 *)equip)->PUISSANCE_REFLECHIE = m_reflechie.GetPos();

	if( !((CEquipCA150 *)equip)->TIMER )
		((CEquipCA150 *)equip)->EnvoiEtatCyclique();
}

/* **************************************************************************
METHODE :		OnSlideIncidente(NMHDR* pNMHDR, LRESULT* pResult)
TRAITEMENT:		Gere la barre analogique de la puissance incidente
***************************************************************************	*/
void CDLGCA150::OnSlideIncidente(NMHDR* pNMHDR, LRESULT* pResult)
{
	int  iTemp, iPosition;
	char cTemp[4];
	iTemp = m_incidente.GetPos();
	// TODO : modifier la puissance
	if(m_combine.GetCheck() == 1)
		iPosition = NIVEAU_PUISSANCE2[iTemp];
	else
		iPosition = NIVEAU_PUISSANCE1[iTemp];
	sprintf(cTemp, "%d", iPosition);
	m_texte_incidente = _T( cTemp );
	UpdateData(FALSE);
}

/* **************************************************************************
METHODE :		OnSpinIncidente(NMHDR* pNMHDR, LRESULT* pResult)
TRAITEMENT:		Gere le compteur de la puissance incidente
***************************************************************************	*/
void CDLGCA150::OnSpinIncidente(NMHDR* pNMHDR, LRESULT* pResult)
{
	int  iTemp, iPosition;
	char cTemp[4];
	NM_UPDOWN *pNMUpDown = (NM_UPDOWN *) pNMHDR;

	iTemp = m_incidente.GetPos();
	if (0 > pNMUpDown->iDelta && iTemp < 255)
	{
		iTemp ++;
		// TODO : modifier la puissance
		if(m_combine.GetCheck() == 1)
			iPosition = NIVEAU_PUISSANCE2[iTemp];
		else
			iPosition = NIVEAU_PUISSANCE1[iTemp];
		sprintf(cTemp, "%d", iPosition);
		m_texte_incidente = _T( cTemp );
		m_incidente.SetPos(iTemp);
	}
	if (0 < pNMUpDown->iDelta && iTemp > 0)
	{
		iTemp --;
		// TODO : modifier la puissance
		if(m_combine.GetCheck() == 1)
			iPosition = NIVEAU_PUISSANCE2[iTemp];
		else
			iPosition = NIVEAU_PUISSANCE1[iTemp];
		sprintf(cTemp, "%d", iPosition);
		m_texte_incidente = _T( cTemp );
		m_incidente.SetPos(iTemp);
	}
	
	*pResult = 0;

	UpdateData(FALSE);
}

/* **************************************************************************
METHODE :		OnSpinReflechie(NMHDR* pNMHDR, LRESULT* pResult)
TRAITEMENT:		Gere le compteur de la puissance reflechie
***************************************************************************	*/
void CDLGCA150::OnSpinReflechie(NMHDR* pNMHDR, LRESULT* pResult)
{
	int iTemp, iPosition;
	char cTemp[3];
	NM_UPDOWN *pNMUpDown = (NM_UPDOWN *) pNMHDR;

	iTemp = m_reflechie.GetPos();
	if (0 > pNMUpDown->iDelta && iTemp < 255)
	{
		iTemp ++;
		// TODO : modifier la puissance
		if(m_combine.GetCheck() == 1)
			iPosition = NIVEAU_PUISSANCE2[iTemp];
		else
			iPosition = NIVEAU_PUISSANCE1[iTemp];
		sprintf(cTemp, "%d", iPosition);
		m_texte_reflechie = _T( cTemp );
		m_reflechie.SetPos(iTemp);
	}
	if (0 < pNMUpDown->iDelta && iTemp > 0)
	{
		iTemp --;
		// TODO : modifier la puissance
		if(m_combine.GetCheck() == 1)
			iPosition = NIVEAU_PUISSANCE2[iTemp];
		else
			iPosition = NIVEAU_PUISSANCE1[iTemp];
		sprintf(cTemp, "%d", iPosition);
		m_texte_reflechie = _T( cTemp );
		m_reflechie.SetPos(iTemp);
	}
	
	*pResult = 0;
	
	UpdateData(FALSE);
}

/* **************************************************************************
METHODE :		OnSlideReflechie(NMHDR* pNMHDR, LRESULT* pResult)
TRAITEMENT:		Gere la barre analogique de la puissance reflechie
***************************************************************************	*/
void CDLGCA150::OnSlideReflechie(NMHDR* pNMHDR, LRESULT* pResult)
{
	int iTemp, iPosition;
	char cTemp[3];
	iTemp = m_reflechie.GetPos();
	// TODO : modifier la puissance
	if(m_combine.GetCheck() == 1)
		iPosition = NIVEAU_PUISSANCE2[iTemp];
	else
		iPosition = NIVEAU_PUISSANCE1[iTemp];
	sprintf(cTemp, "%d", iPosition);
	m_texte_reflechie = _T( cTemp );
	UpdateData(FALSE);
}

/* **************************************************************************
METHODE :		OnCharge()
TRAITEMENT:		Evite le changement des charges
***************************************************************************	*/
void CDLGCA150::OnCharge()
{
	int i;			//int i, index;		//2009-11-27

	for(i=1; i<=4; i++)
	{
		if( ((CEquipCA150 *)equip)->CHARGE[i] )
			m_charge[i].SetCheck(1);
		else
			m_charge[i].SetCheck(0);
	}

	if( ((CEquipCA150 *)equip)->TYPE == MASTER)
	{
		if( ((CEquipCA150 *)equip)->CHARGE[5] )
			m_charge[6].SetCheck(1);
		else
			m_charge[6].SetCheck(0);
	}
	if( ((CEquipCA150 *)equip)->TYPE == SLAVE)
	{
		if( ((CEquipCA150 *)equip)->CHARGE[5] )
			m_charge[5].SetCheck(1);
		else
			m_charge[5].SetCheck(0);
		if( ((CEquipCA150 *)equip)->CHARGE[6] )
			m_charge[6].SetCheck(1);
		else
			m_charge[6].SetCheck(0);
	}

	if( ((CEquipCA150 *)equip)->COMBINE)
		m_combine.SetCheck(1);
	else
		m_combine.SetCheck(0);
	
	UpdateData(FALSE);
}
