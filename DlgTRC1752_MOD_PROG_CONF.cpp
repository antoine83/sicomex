// DlgTRC1752_MOD_PROG_CONF.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_CONF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_CONF dialog


CDlgTRC1752_MOD_PROG_CONF::CDlgTRC1752_MOD_PROG_CONF(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_CONF::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_CONF)
	m_Frq_C_E = 2000;
	m_Frq_B_Emi = 1575;
	m_Frq_B_Rec = 1575;
	m_Frq_H_Emi = 2425;
	m_Frq_H_Rec = 2425;
	m_Frq_C_R = 2000;
	m_ChoixCanal = 0;
	m_ChoixMode = 0;
	m_ChoixDebitE = 2400;
	m_ChoixDebitR = 2400;
	m_SP_R = -1;
	m_SP_E = -1;
	m_Shift_E = -1;
	m_Shift_R = -1;
	m_ChoixSousMode = 2;
	m_ChoixEntR = 1;
	m_ChoixEntE = 1;
	m_ChoixDiv = 1;
	m_DivSortieData = 0;		//----
	m_DivDebitEmi = 7;
	m_DivEntrelaceurEmi = 2;	//Long
	m_DivSousMode = 1;			//FD
	m_Frq_Div_C_E = 2000;
	//}}AFX_DATA_INIT

	this->eqp = equip;
	mc_value = "A1";
}


void CDlgTRC1752_MOD_PROG_CONF::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_CONF)
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_E_DIV_SPIN, s_Frq_Div_C_E);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_E_DIV, c_Frq_Div_C_E);
	DDX_Control(pDX, IDC_PROG_DIV_SOUS_MODE, c_DivSousMode);
	DDX_Control(pDX, IDC_PROG_DIV_CH_ENT_E, c_DivEntrelaceurEmi);
	DDX_Control(pDX, IDC_PROG_DIV_CH_DEBIT_E, c_DivDebitEmi);
	DDX_Control(pDX, IDC_STATIC_DIV_E, t_DivE);
	DDX_Control(pDX, IDC_PROG_DIV_SORTIE_DATA, c_DivSortieData);
	DDX_Control(pDX, IDC_STATIC_DIV_INFO, t_DivInfo);
	DDX_Control(pDX, IDC_MOD_PROG_DIV, m_ModProgDiv);
	DDX_Control(pDX, IDC_STATIC_DIV, t_ChoixDiv);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_H_R, c_Frq_H_Rec);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_H_E, c_Frq_H_Emi);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_B_E, c_Frq_B_Emi);
	DDX_Control(pDX, IDC_PROG_CONF_CH_DIV, c_ChoixDiv);
	DDX_Control(pDX, IDC_PROG_CONF_CH_ENT_E, c_ChoixEntE);
	DDX_Control(pDX, IDC_PROG_CONF_CH_ENT_R, c_ChoixEntR);
	DDX_Control(pDX, IDC_PROG_CONF_CH_S_MODE, c_ChoixSousMode);
	DDX_Control(pDX, IDC_PROG_CONF_SHIFT_R, c_Shift_R);
	DDX_Control(pDX, IDC_PROG_CONF_SHIFT_E, c_Shift_E);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_B_R, c_Frq_B_Rec);
	DDX_Control(pDX, IDC_PROG_CONF_SP_E, c_SP_E);
	DDX_Control(pDX, IDC_PROG_CONF_SP_R, c_SP_R);
	DDX_Control(pDX, IDC_PROG_CONF_CH_DEBIT_R, c_ChoixDebitR);
	DDX_Control(pDX, IDC_PROG_CONF_CH_DEBIT_E, c_ChoixDebitE);
	DDX_Control(pDX, IDC_PROG_CONF_CH_MODE, c_ChoixMode);
	DDX_Control(pDX, IDC_PROG_CONF_CH_CANAL, c_ChoixCanal);
	DDX_Control(pDX, IDC_STATIC_E, t_E);
	DDX_Control(pDX, IDC_STATIC_T, t_T);
	DDX_Control(pDX, IDC_STATIC_SP_E, t_SP_E);
	DDX_Control(pDX, IDC_STATIC_SHIFT, t_Shift);
	DDX_Control(pDX, IDC_STATIC_R, t_R);
	DDX_Control(pDX, IDC_STATIC_FRQ_C_EMI, t_Frq_C_E);
	DDX_Control(pDX, IDC_STATIC_FQ_H_E, t_Frq_H_E);
	DDX_Control(pDX, IDC_STATIC_FQ_B_E, t_Frq_B_E);
	DDX_Control(pDX, IDC_STATIC_ENT_E, t_Entrelaceur);
	DDX_Control(pDX, IDC_STATIC_DEB_COD_E, t_Debit);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_E_SPIN, s_FrqE);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_H_E_SPIN, s_Frq_H_E);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_H_R_SPIN, s_Frq_H_R);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_R_SPIN, s_FrqR);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_B_R_SPIN, s_Frq_B_R);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_B_E_SPIN, s_Frq_B_E);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_R, m_FrqR);
	DDX_Control(pDX, IDC_PROG_CONF_FRQ_E, m_FrqE);
	DDX_Text(pDX, IDC_PROG_CONF_FRQ_E, m_Frq_C_E);
	DDV_MinMaxInt(pDX, m_Frq_C_E, 900, 2400);
	DDX_Text(pDX, IDC_PROG_CONF_FRQ_B_E, m_Frq_B_Emi);
	DDX_Text(pDX, IDC_PROG_CONF_FRQ_B_R, m_Frq_B_Rec);
	DDX_Text(pDX, IDC_PROG_CONF_FRQ_H_E, m_Frq_H_Emi);
	DDX_Text(pDX, IDC_PROG_CONF_FRQ_H_R, m_Frq_H_Rec);
	DDX_Text(pDX, IDC_PROG_CONF_FRQ_R, m_Frq_C_R);
	DDV_MinMaxInt(pDX, m_Frq_C_R, 900, 2400);
	DDX_CBIndex(pDX, IDC_PROG_CONF_CH_CANAL, m_ChoixCanal);
	DDX_CBIndex(pDX, IDC_PROG_CONF_CH_MODE, m_ChoixMode);
	DDX_CBIndex(pDX, IDC_PROG_CONF_CH_DEBIT_E, m_ChoixDebitE);
	DDX_CBIndex(pDX, IDC_PROG_CONF_CH_DEBIT_R, m_ChoixDebitR);
	DDX_CBIndex(pDX, IDC_PROG_CONF_SP_R, m_SP_R);
	DDX_CBIndex(pDX, IDC_PROG_CONF_SP_E, m_SP_E);
	DDX_CBIndex(pDX, IDC_PROG_CONF_SHIFT_E, m_Shift_E);
	DDX_CBIndex(pDX, IDC_PROG_CONF_SHIFT_R, m_Shift_R);
	DDX_CBIndex(pDX, IDC_PROG_CONF_CH_S_MODE, m_ChoixSousMode);
	DDX_CBIndex(pDX, IDC_PROG_CONF_CH_ENT_R, m_ChoixEntR);
	DDX_CBIndex(pDX, IDC_PROG_CONF_CH_ENT_E, m_ChoixEntE);
	DDX_CBIndex(pDX, IDC_PROG_CONF_CH_DIV, m_ChoixDiv);
	DDX_CBIndex(pDX, IDC_PROG_DIV_SORTIE_DATA, m_DivSortieData);
	DDX_CBIndex(pDX, IDC_PROG_DIV_CH_DEBIT_E, m_DivDebitEmi);
	DDX_CBIndex(pDX, IDC_PROG_DIV_CH_ENT_E, m_DivEntrelaceurEmi);
	DDX_CBIndex(pDX, IDC_PROG_DIV_SOUS_MODE, m_DivSousMode);
	DDX_Text(pDX, IDC_PROG_CONF_FRQ_E_DIV, m_Frq_Div_C_E);
	DDV_MinMaxInt(pDX, m_Frq_Div_C_E, 900, 2400);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_CONF, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_CONF)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_CH_MODE, OnSelchangeProgConfChMode)
	ON_WM_SHOWWINDOW()
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_PROG_CONF_FRQ_E_SPIN, OnOutofmemoryProgConfFrqESpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PROG_CONF_FRQ_E_SPIN, OnDeltaposProgConfFrqESpin)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_PROG_CONF_FRQ_H_E_SPIN, OnOutofmemoryProgConfFrqHESpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PROG_CONF_FRQ_H_E_SPIN, OnDeltaposProgConfFrqHESpin)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_PROG_CONF_FRQ_H_R_SPIN, OnOutofmemoryProgConfFrqHRSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PROG_CONF_FRQ_H_R_SPIN, OnDeltaposProgConfFrqHRSpin)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_PROG_CONF_FRQ_R_SPIN, OnOutofmemoryProgConfFrqRSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PROG_CONF_FRQ_R_SPIN, OnDeltaposProgConfFrqRSpin)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_PROG_CONF_FRQ_B_E_SPIN, OnOutofmemoryProgConfFrqBESpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PROG_CONF_FRQ_B_E_SPIN, OnDeltaposProgConfFrqBESpin)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_PROG_CONF_FRQ_B_R_SPIN, OnOutofmemoryProgConfFrqBRSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PROG_CONF_FRQ_B_R_SPIN, OnDeltaposProgConfFrqBRSpin)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_CH_CANAL, OnSelchangeProgConfChCanal)
	ON_CBN_EDITUPDATE(IDC_PROG_CONF_CH_MODE, OnEditupdateProgConfChMode)
	ON_CBN_EDITCHANGE(IDC_PROG_CONF_CH_DEBIT_E, OnEditchangeProgConfChDebitE)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_CH_DEBIT_E, OnSelchangeProgConfChDebitE)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_CH_ENT_E, OnSelchangeProgConfChEntE)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_CH_DEBIT_R, OnSelchangeProgConfChDebitR)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_CH_ENT_R, OnSelchangeProgConfChEntR)
	ON_CBN_EDITUPDATE(IDC_PROG_CONF_CH_DEBIT_E, OnEditupdateProgConfChDebitE)
	ON_CBN_EDITCHANGE(IDC_PROG_CONF_CH_DEBIT_R, OnEditchangeProgConfChDebitR)
	ON_CBN_EDITUPDATE(IDC_PROG_CONF_CH_DEBIT_R, OnEditupdateProgConfChDebitR)
	ON_CBN_EDITCHANGE(IDC_PROG_CONF_CH_ENT_E, OnEditchangeProgConfChEntE)
	ON_CBN_EDITUPDATE(IDC_PROG_CONF_CH_ENT_E, OnEditupdateProgConfChEntE)
	ON_CBN_EDITCHANGE(IDC_PROG_CONF_CH_ENT_R, OnEditchangeProgConfChEntR)
	ON_CBN_EDITUPDATE(IDC_PROG_CONF_CH_ENT_R, OnEditupdateProgConfChEntR)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_CH_S_MODE, OnSelchangeProgConfChSMode)
	ON_CBN_EDITCHANGE(IDC_PROG_CONF_CH_S_MODE, OnEditchangeProgConfChSMode)
	ON_CBN_EDITUPDATE(IDC_PROG_CONF_CH_S_MODE, OnEditupdateProgConfChSMode)
	ON_EN_KILLFOCUS(IDC_PROG_CONF_FRQ_E, OnKillfocusProgConfFrqE)
	ON_EN_KILLFOCUS(IDC_PROG_CONF_FRQ_R, OnKillfocusProgConfFrqR)
	ON_EN_KILLFOCUS(IDC_PROG_CONF_FRQ_B_E, OnKillfocusProgConfFrqBE)
	ON_EN_KILLFOCUS(IDC_PROG_CONF_FRQ_B_R, OnKillfocusProgConfFrqBR)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_SHIFT_E, OnSelchangeProgConfShiftE)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_SP_E, OnSelchangeProgConfSpE)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_SP_R, OnSelchangeProgConfSpR)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_SHIFT_R, OnSelchangeProgConfShiftR)
	ON_CBN_SELCHANGE(IDC_PROG_CONF_CH_DIV, OnSelchangeProgConfChDiv)
	ON_EN_CHANGE(IDC_PROG_CONF_FRQ_H_E, OnChangeProgConfFrqHE)
	ON_EN_CHANGE(IDC_PROG_CONF_FRQ_B_E, OnChangeProgConfFrqBE)
	ON_EN_KILLFOCUS(IDC_PROG_CONF_FRQ_H_E, OnKillfocusProgConfFrqHE)
	ON_EN_KILLFOCUS(IDC_PROG_CONF_FRQ_H_R, OnKillfocusProgConfFrqHR)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_PROG_CONF_FRQ_E_DIV_SPIN, OnOutofmemoryProgConfFrqEDivSpin)
	ON_NOTIFY(UDN_DELTAPOS, IDC_PROG_CONF_FRQ_E_DIV_SPIN, OnDeltaposProgConfFrqEDivSpin)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_PROG_DIV_SORTIE_DATA, OnSelchangeProgDivSortieData)
	ON_CBN_SELCHANGE(IDC_PROG_DIV_SOUS_MODE, OnSelchangeProgDivSousMode)
	ON_CBN_SELCHANGE(IDC_PROG_DIV_CH_DEBIT_E, OnSelchangeProgDivChDebitE)
	ON_CBN_SELCHANGE(IDC_PROG_DIV_CH_ENT_E, OnSelchangeProgDivChEntE)
	ON_EN_CHANGE(IDC_PROG_CONF_FRQ_H_R, OnChangeProgConfFrqHR)
	ON_WM_SETFOCUS()
	ON_EN_CHANGE(IDC_PROG_CONF_FRQ_B_R, OnChangeProgConfFrqBR)
	//}}AFX_MSG_MAP
	ON_EN_SETFOCUS(IDC_PROG_CONF_FRQ_H_E, OnSetfocusFRQ_H_E)
	ON_EN_SETFOCUS(IDC_PROG_CONF_FRQ_H_R, OnSetfocusFRQ_H_R)
	ON_EN_SETFOCUS(IDC_PROG_CONF_FRQ_B_E, OnSetfocusFRQ_B_E)
	ON_EN_SETFOCUS(IDC_PROG_CONF_FRQ_B_R, OnSetfocusFRQ_B_R)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_CONF message handlers

BOOL CDlgTRC1752_MOD_PROG_CONF::OnInitDialog()
{
	CDialog::OnInitDialog();

	//Choix du Canal
	m_ChoixCanal = 0;				//CA

	//Choix Initialisation du mode
	m_ChoixMode = 6;				//REPOS


	//Raz de l'IHM
	EffaceALL();

	//Initialisation à la création
	CacheControles(m_ChoixMode);

	//Initialisation des Choix
	c_ChoixCanal.SetCurSel(0);		//CA
	c_ChoixMode.SetCurSel(6);		//REPOS
	c_ChoixDebitE.SetCurSel(6);		//2400C
	c_ChoixDebitR.SetCurSel(6);		//2400C
	c_ChoixDiv.SetCurSel(1);		//--
	c_ChoixEntE.SetCurSel(1);		//C
	c_ChoixEntR.SetCurSel(1);		//C
	c_ChoixSousMode.SetCurSel(2);	//HD

	//Initialisation Diversité
	c_DivSortieData.SetCurSel(0);		//----
	c_DivSousMode.SetCurSel(1);			//FD
	c_DivDebitEmi.SetCurSel(6);			//2400C
	c_DivEntrelaceurEmi.SetCurSel(2);	//L


	//-------------------------
	//Initialisation des SPIN's
	//-------------------------
	//Fréquence centrale
	s_FrqE.SetRange(900, 2400);
	s_FrqR.SetRange(900, 2400);
	//Diversite en 4529
	s_Frq_Div_C_E.SetRange(900, 2400);

	//Fréquence Haute et Basse
	s_Frq_B_E.SetRange(300, 3300);
	s_Frq_H_E.SetRange(300, 3300);
	s_Frq_B_R.SetRange(300, 3300);
	s_Frq_H_R.SetRange(300, 3300);


	UpdateData(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

//------------------
//Selection du Canal
//------------------
void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfChCanal()
{
	//Affichage apres modification du canal
	ModificationCanal();
}

//-----------------
//Selection du Mode
//-----------------
void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfChMode()
{


	//Initialisation au changement
	EffaceALL();

	//Selection du mode
	m_ChoixMode = c_ChoixMode.GetCurSel();

	//Affichage en fonction du mode
	if (m_ChoixMode != LB_ERR)
		CacheControles(m_ChoixMode);					//Affichage des objets en fonction de la sélection du mode

	//Verification des Conditions sur le Sous-Mode
	OnSelchangeProgConfChSMode();

	//Verification des Conditions sur les Débits
	OnSelchangeProgConfChDebitE();
	OnSelchangeProgConfChDebitR();

	CString conf;

	c_ChoixCanal.GetLBText(c_ChoixCanal.GetCurSel(), conf);
	/*

	if ( (eqp->GetChannelAssociatedAfConfiguration("A1") == (LPCTSTR)conf && eqp->GetChannelState("A1") == "ACTIVE")
		|| (eqp->GetChannelAssociatedAfConfiguration("A2") == (LPCTSTR)conf && eqp->GetChannelState("A2") == "ACTIVE")
		 || (eqp->GetChannelAssociatedAfConfiguration("B1") == (LPCTSTR)conf && eqp->GetChannelState("B1") == "ACTIVE")
		  || (eqp->GetChannelAssociatedAfConfiguration("B2") == (LPCTSTR)conf && eqp->GetChannelState("B2") == "ACTIVE"))
	{
		DesactivElemConsult();
	}
	else	ActivElemConsult();
	*/

}

void CDlgTRC1752_MOD_PROG_CONF::OnEditupdateProgConfChMode()
{
	OnSelchangeProgConfChMode();
}

//--------------------------------------------------------
//Affichage des objets en fonction de la sélection du mode
//--------------------------------------------------------
void CDlgTRC1752_MOD_PROG_CONF::CacheControles(int ModeEnCours)
{
	t_Debit.SetWindowText("Debit/Codage");

	switch(ModeEnCours)
	{
	case 0:			//4285
		//Mise à jour des débits
		InitialisationListeDebit4285();

		//Débit
		c_ChoixDebitE.SetCurSel(6);		//2400C
		c_ChoixDebitR.SetCurSel(6);
		c_ChoixEntE.SetCurSel(1);		//Court
		c_ChoixEntR.SetCurSel(1);
		c_ChoixDiv.SetCurSel(1);
		c_ChoixSousMode.SetCurSel(2);
		c_DivSousMode.SetCurSel(1);

		//Mise à jour Affichage
		Affiche4285();
		break;
	case 1:			//4529
		//Mise à jour des débits
		InitialisationListeDebit4529();

		//Débit
		c_ChoixDebitE.SetCurSel(5);		//1200C
		c_ChoixDebitR.SetCurSel(5);
		c_ChoixEntE.SetCurSel(1);		//Court
		c_ChoixEntR.SetCurSel(1);
		c_ChoixDiv.SetCurSel(1);
		c_ChoixSousMode.SetCurSel(2);
		c_DivSousMode.SetCurSel(1);
		// FFT ADEL_97099
		m_FrqE.SetWindowText("2000");
		m_FrqR.SetWindowText("2000");
		m_Frq_C_E = 2000;
		m_Frq_C_R = 2000;

		//Mise à jour Affichage
		Affiche4529();
		break;
	case 2:			//FSKP
		c_ChoixDiv.SetCurSel(1);
		t_Debit.SetWindowText("Debit");

		//Mise à jour des débits
		InitialisationListeDebitFSK();

		//Débit
		c_ChoixDebitE.SetCurSel(7);
		c_ChoixDebitR.SetCurSel(7);
		c_SP_E.SetCurSel(5);
		c_SP_R.SetCurSel(5);
		c_Shift_E.SetCurSel(4);
		c_Shift_R.SetCurSel(4);
		c_ChoixSousMode.SetCurSel(2);

		//Mise à jour Affichage
		AfficheFSKP();
		break;
	case 3:			//FSKV
		c_ChoixDiv.SetCurSel(1);
		t_Debit.SetWindowText("Debit");
		//Mise à jour des débits
		InitialisationListeDebitFSK();

		//Initialisation Affichage
		AfficheFSKV();

		//Débit
		c_ChoixDebitE.SetCurSel(7);
		c_ChoixDebitR.SetCurSel(7);
		c_ChoixSousMode.SetCurSel(2);
		break;
	case 4:			//MIL110
		c_ChoixDiv.SetCurSel(1);
		//Mise à jour des débits
		InitialisationListeDebitMIL110();

		//Débit
		c_ChoixDebitE.SetCurSel(5);
		c_ChoixDebitR.SetCurSel(0);
		c_ChoixSousMode.SetCurSel(2);

		//Mise à jour Affichage
		AfficheMIL110();
		break;
	case 5:			//TARNSPARENT
	case 6:			//REPOS
				c_SP_E.SetCurSel(5);
				c_SP_R.SetCurSel(5);
				c_Shift_E.SetCurSel(4);
				c_Shift_R.SetCurSel(4);
		c_ChoixDiv.SetCurSel(1);
		EffaceALL();
		t_Debit.ShowWindow(FALSE);
		break;
	default:
		//Cache les objets
		EffaceALL();
		break;
	}

}

//---------------------------
//Cache les objets de la vue
//---------------------------
void CDlgTRC1752_MOD_PROG_CONF::EffaceALL()
{
	//Efface les débit
	InitialisationListeDebitE();
	InitialisationListeDebitR();

	//Débit
	t_Debit.ShowWindow(FALSE);
	AfficheCacheDebitE(FALSE);
	AfficheCacheDebitR(FALSE);

	//Entrelaceur
	t_Entrelaceur.ShowWindow(FALSE);
	AfficheCacheEntrelaceurE(FALSE);
	AfficheCacheEntrelaceurR(FALSE);

	//Fréquence Centrale Emission/Réception
	t_Frq_C_E.ShowWindow(FALSE);
	AfficheCacheFrqCentraleE(FALSE);
	AfficheCacheFrqCentraleR(FALSE);

	//Fréquence Haute Emission/Réception
	t_Frq_H_E.ShowWindow(FALSE);
	c_Frq_H_Emi.ShowWindow(FALSE);
	s_Frq_H_E.ShowWindow(FALSE);
	c_Frq_H_Rec.ShowWindow(FALSE);
	s_Frq_H_R.ShowWindow(FALSE);
	//Fréquence Basse Emission/Réception
	t_Frq_B_E.ShowWindow(FALSE);
	c_Frq_B_Emi.ShowWindow(FALSE);
	s_Frq_B_E.ShowWindow(FALSE);
	c_Frq_B_Rec.ShowWindow(FALSE);
	s_Frq_B_R.ShowWindow(FALSE);
	//Fréquence Sous-Porteuse Emission/Réception
	t_SP_E.ShowWindow(FALSE);
	c_SP_E.ShowWindow(FALSE);
	c_SP_R.ShowWindow(FALSE);
	//Saut de fréquence Emission/Réception
	t_Shift.ShowWindow(FALSE);
	c_Shift_E.ShowWindow(FALSE);
	c_Shift_R.ShowWindow(FALSE);

	//Diversité
	AfficheCacheDiversite(FALSE);

	//Sous-Mode
	t_T.ShowWindow(FALSE);
	c_ChoixSousMode.ShowWindow(FALSE);

	//Fenetre Diversité - 2ème Cas
	GetDlgItem(IDC_MOD_PROG_DIV)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_DIV_INFO)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROG_DIV_SORTIE_DATA)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROG_DIV_SOUS_MODE)->ShowWindow(FALSE);
	GetDlgItem(IDC_STATIC_DIV_E)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROG_DIV_CH_DEBIT_E)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROG_DIV_CH_ENT_E)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROG_CONF_FRQ_E_DIV)->ShowWindow(FALSE);
	GetDlgItem(IDC_PROG_CONF_FRQ_E_DIV_SPIN)->ShowWindow(FALSE);
}

//---------------------------
//Affiche pour le Mode : 4285
//---------------------------
void CDlgTRC1752_MOD_PROG_CONF::Affiche4285()
{
	//Débit
	AfficheCacheDebitE(TRUE);
	AfficheCacheDebitR(TRUE);

	//Entrelaceur
	t_Entrelaceur.ShowWindow(TRUE);
	AfficheCacheEntrelaceurE(TRUE);
	AfficheCacheEntrelaceurR(TRUE);

	//Fréquence Centrale Emission/Réception
	t_Frq_C_E.ShowWindow(FALSE);
	AfficheCacheFrqCentraleE(FALSE);
	AfficheCacheFrqCentraleR(FALSE);

	//Fréquence Haute Emission/Réception
	t_Frq_H_E.ShowWindow(FALSE);
	c_Frq_H_Emi.ShowWindow(FALSE);
	s_Frq_H_E.ShowWindow(FALSE);
	c_Frq_H_Rec.ShowWindow(FALSE);
	s_Frq_H_R.ShowWindow(FALSE);
	//Fréquence Basse Emission/Réception
	t_Frq_B_E.ShowWindow(FALSE);
	c_Frq_B_Emi.ShowWindow(FALSE);
	s_Frq_B_E.ShowWindow(FALSE);
	c_Frq_B_Rec.ShowWindow(FALSE);
	s_Frq_B_R.ShowWindow(FALSE);
	//Fréquence Sous-Porteuse Emission/Réception
	t_SP_E.ShowWindow(FALSE);
	c_SP_E.ShowWindow(FALSE);
	c_SP_R.ShowWindow(FALSE);
	//Saut de fréquence Emission/Réception
	t_Shift.ShowWindow(FALSE);
	c_Shift_E.ShowWindow(FALSE);
	c_Shift_R.ShowWindow(FALSE);
	//Diversité
	AfficheCacheDiversite(TRUE);

	//Sous-Mode
	t_T.ShowWindow(TRUE);
	c_ChoixSousMode.ShowWindow(TRUE);

	//TODO : Affiche/cache la fenêtre div2emeCas
	//si DIV&&RE alors : AfficheCache2cas(TRUE)
	//si --&&RE  alors : AfficheCache2cas(FALSE)

	AfficheCache2cas(FALSE);

	if (c_ChoixDiv.GetCurSel() == 0)
		AfficheCache2cas(TRUE);

}

//---------------------------
//Affiche pour le Mode : 4529
//---------------------------
void CDlgTRC1752_MOD_PROG_CONF::Affiche4529()
{
	//Débit
	AfficheCacheDebitE(TRUE);
	AfficheCacheDebitR(TRUE);

	//Entrelaceur
	t_Entrelaceur.ShowWindow(TRUE);
	AfficheCacheEntrelaceurE(TRUE);
	AfficheCacheEntrelaceurR(TRUE);

	//Fréquence Centrale Emission/Réception
	t_Frq_C_E.ShowWindow(TRUE);
	AfficheCacheFrqCentraleE(TRUE);
	AfficheCacheFrqCentraleR(TRUE);

	//Fréquence Haute Emission/Réception
	t_Frq_H_E.ShowWindow(FALSE);
	c_Frq_H_Emi.ShowWindow(FALSE);
	s_Frq_H_E.ShowWindow(FALSE);
	c_Frq_H_Rec.ShowWindow(FALSE);
	s_Frq_H_R.ShowWindow(FALSE);
	//Fréquence Basse Emission/Réception
	t_Frq_B_E.ShowWindow(FALSE);
	c_Frq_B_Emi.ShowWindow(FALSE);
	s_Frq_B_E.ShowWindow(FALSE);
	c_Frq_B_Rec.ShowWindow(FALSE);
	s_Frq_B_R.ShowWindow(FALSE);
	//Fréquence Sous-Porteuse Emission/Réception
	t_SP_E.ShowWindow(FALSE);
	c_SP_E.ShowWindow(FALSE);
	c_SP_R.ShowWindow(FALSE);
	//Saut de fréquence Emission/Réception
	t_Shift.ShowWindow(FALSE);
	c_Shift_E.ShowWindow(FALSE);
	c_Shift_R.ShowWindow(FALSE);
	//Diversité
	AfficheCacheDiversite(TRUE);

	//Sous-Mode
	t_T.ShowWindow(TRUE);
	c_ChoixSousMode.ShowWindow(TRUE);

	//TODO : Affiche/cache la fenêtre div2emeCas
	//si DIV&&RE alors : AfficheCache2cas(TRUE)
	//si --&&RE  alors : AfficheCache2cas(FALSE)

	//TODO : Affiche/cache la fenêtre div2emeCas
	//si DIV&&RE alors : AfficheCache2cas(TRUE)
	//si --&&RE  alors : AfficheCache2cas(FALSE)

	AfficheCache2cas(FALSE);

	if (c_ChoixDiv.GetCurSel() == 0)
		AfficheCache2cas(TRUE);

}

//---------------------------
//Affiche pour le Mode : FSKV
//---------------------------
void CDlgTRC1752_MOD_PROG_CONF::AfficheFSKV()
{
	//Débit
	AfficheCacheDebitE(TRUE);
	AfficheCacheDebitR(TRUE);

	//Fréquence Haute Emission/Réception
	t_Frq_H_E.ShowWindow(TRUE);
	AfficheCacheFrqHauteE(TRUE);
	AfficheCacheFrqHauteR(TRUE);

	//Fréquence Basse Emission/Réception
	t_Frq_B_E.ShowWindow(TRUE);
	AfficheCacheFrqBasseE(TRUE);
	AfficheCacheFrqBasseR(TRUE);

	//Choix simplex Réception
	if (c_ChoixSousMode.GetCurSel() == 0 )
	{
		//Débit
		AfficheCacheDebitE(FALSE);

		//Fréquence Haute Emission
		AfficheCacheFrqHauteE(FALSE);

		//Fréquence Basse Emission
		AfficheCacheFrqBasseE(FALSE);
	}

	//Choix simplex Emission
	if (c_ChoixSousMode.GetCurSel() == 1 )
	{
		//Débit
		AfficheCacheDebitR(FALSE);

		//Fréquence Haute Réception
		AfficheCacheFrqHauteR(FALSE);

		//Fréquence Basse Réception
		AfficheCacheFrqBasseR(FALSE);
	}

	//Entrelaceur
	t_Entrelaceur.ShowWindow(FALSE);
	AfficheCacheEntrelaceurE(FALSE);
	AfficheCacheEntrelaceurR(FALSE);

	//Fréquence Centrale Emission/Réception
	t_Frq_C_E.ShowWindow(FALSE);
	AfficheCacheFrqCentraleE(FALSE);
	AfficheCacheFrqCentraleR(FALSE);

	//Fréquence Sous-Porteuse Emission/Réception
	t_SP_E.ShowWindow(FALSE);
	c_SP_E.ShowWindow(FALSE);
	c_SP_R.ShowWindow(FALSE);

	//Saut de fréquence Emission/Réception
	t_Shift.ShowWindow(FALSE);
	c_Shift_E.ShowWindow(FALSE);
	c_Shift_R.ShowWindow(FALSE);

	//Diversité
	AfficheCacheDiversite(FALSE);

	//Sous-Mode
	t_T.ShowWindow(TRUE);
	c_ChoixSousMode.ShowWindow(TRUE);
}

//---------------------------
//Affiche pour le Mode : FSKP
//---------------------------
void CDlgTRC1752_MOD_PROG_CONF::AfficheFSKP()
{
	//Débit
	AfficheCacheDebitE(TRUE);
	AfficheCacheDebitR(TRUE);

	//Fréquence Sous-Porteuse Emission/Réception
	t_SP_E.ShowWindow(TRUE);
	c_SP_E.ShowWindow(TRUE);
	c_SP_R.ShowWindow(TRUE);

	//Saut de fréquence Emission/Réception
	t_Shift.ShowWindow(TRUE);
	c_Shift_E.ShowWindow(TRUE);
	c_Shift_R.ShowWindow(TRUE);

	//Sous-Mode
	t_T.ShowWindow(TRUE);
	c_ChoixSousMode.ShowWindow(TRUE);

	//Choix simplex Réception
	if (c_ChoixSousMode.GetCurSel() == 0 )
	{
		//Débit
		AfficheCacheDebitE(FALSE);
		//Fréquence Sous-Porteuse Emission
		c_SP_E.ShowWindow(FALSE);
		//Saut de fréquence Emission
		c_Shift_E.ShowWindow(FALSE);
	}

	//Choix simplex Emission
	if (c_ChoixSousMode.GetCurSel() == 1 )
	{
		//Débit
		AfficheCacheDebitR(FALSE);
		//Fréquence Sous-Porteuse Réception
		c_SP_R.ShowWindow(FALSE);
		//Saut de fréquence Réception
		c_Shift_R.ShowWindow(FALSE);
	}

	//Entrelaceur
	t_Entrelaceur.ShowWindow(FALSE);
	AfficheCacheEntrelaceurE(FALSE);
	AfficheCacheEntrelaceurR(FALSE);

	//Fréquence Centrale Emission/Réception
	t_Frq_C_E.ShowWindow(FALSE);
	AfficheCacheFrqCentraleE(FALSE);
	AfficheCacheFrqCentraleR(FALSE);

	//Fréquence Haute Emission/Réception
	t_Frq_H_E.ShowWindow(FALSE);
	AfficheCacheFrqHauteE(FALSE);
	AfficheCacheFrqHauteR(FALSE);

	//Fréquence Basse Emission/Réception
	t_Frq_B_E.ShowWindow(FALSE);
	AfficheCacheFrqBasseE(FALSE);
	AfficheCacheFrqBasseR(FALSE);

	//Diversité
	AfficheCacheDiversite(FALSE);

}

//-----------------------------
//Affiche pour le Mode : MIL110
//-----------------------------
void CDlgTRC1752_MOD_PROG_CONF::AfficheMIL110()
{
	//Débit
	AfficheCacheDebitE(TRUE);
	AfficheCacheDebitR(TRUE);

	//Entrelaceur
	t_Entrelaceur.ShowWindow(TRUE);
	AfficheCacheEntrelaceurE(TRUE);
	AfficheCacheEntrelaceurE(TRUE);

	//Sous-Mode
	t_T.ShowWindow(TRUE);
	c_ChoixSousMode.ShowWindow(TRUE);

	//Choix simplex Réception
	if (c_ChoixSousMode.GetCurSel() == 0 )
	{
		//Débit
		AfficheCacheDebitE(FALSE);

		//Entrelaceur
		AfficheCacheEntrelaceurE(FALSE);
	}

	//Choix simplex Emission
	if (c_ChoixSousMode.GetCurSel() == 1 )
	{
		//Débit
		AfficheCacheDebitR(FALSE);

		//Entrelaceur
		AfficheCacheEntrelaceurR(FALSE);
	}

	//Fréquence Centrale Emission/Réception
	t_Frq_C_E.ShowWindow(FALSE);
	AfficheCacheFrqCentraleE(FALSE);
	AfficheCacheFrqCentraleR(FALSE);

	//Fréquence Haute Emission/Réception
	t_Frq_H_E.ShowWindow(FALSE);
	c_Frq_H_Emi.ShowWindow(FALSE);
	s_Frq_H_E.ShowWindow(FALSE);
	c_Frq_H_Rec.ShowWindow(FALSE);
	s_Frq_H_R.ShowWindow(FALSE);
	//Fréquence Basse Emission/Réception
	t_Frq_B_E.ShowWindow(FALSE);
	c_Frq_B_Emi.ShowWindow(FALSE);
	s_Frq_B_E.ShowWindow(FALSE);
	c_Frq_B_Rec.ShowWindow(FALSE);
	s_Frq_B_R.ShowWindow(FALSE);
	//Fréquence Sous-Porteuse Emission/Réception
	t_SP_E.ShowWindow(FALSE);
	c_SP_E.ShowWindow(FALSE);
	c_SP_R.ShowWindow(FALSE);
	//Saut de fréquence Emission/Réception
	t_Shift.ShowWindow(FALSE);
	c_Shift_E.ShowWindow(FALSE);
	c_Shift_R.ShowWindow(FALSE);

	//Diversité
	AfficheCacheDiversite(FALSE);

}

//RAZ de la lise des débits Emission
void CDlgTRC1752_MOD_PROG_CONF::InitialisationListeDebitE()
{
	c_ChoixDebitE.ResetContent();
	c_DivDebitEmi.ResetContent();
}
//RAZ de la lise des débits Réception
void CDlgTRC1752_MOD_PROG_CONF::InitialisationListeDebitR()
{
	c_ChoixDebitR.ResetContent();
}

//RAZ de la liste  Entrelaceur réception MIL110
void CDlgTRC1752_MOD_PROG_CONF::InitialisationEntrelaceurMIL110()
{
	c_ChoixEntR.ResetContent();
}
//-----------------------------------------------------
//Initialisation de liste des débit pour le mode : 4285
//-----------------------------------------------------
void CDlgTRC1752_MOD_PROG_CONF::InitialisationListeDebit4285()
{
	//RAZ des listes
	InitialisationListeDebitE();
	InitialisationListeDebitR();

	//Initialisation
	c_ChoixDebitE.AddString("75C");
	c_ChoixDebitR.AddString("75C");
	c_ChoixDebitE.AddString("150C");
	c_ChoixDebitR.AddString("150C");
	c_ChoixDebitE.AddString("300C");
	c_ChoixDebitR.AddString("300C");
	c_ChoixDebitE.AddString("600C");
	c_ChoixDebitR.AddString("600C");
	c_ChoixDebitE.AddString("1200C");
	c_ChoixDebitR.AddString("1200C");
	c_ChoixDebitE.AddString("1200S");
	c_ChoixDebitR.AddString("1200S");
	c_ChoixDebitE.AddString("2400C");
	c_ChoixDebitR.AddString("2400C");
	c_ChoixDebitE.AddString("2400S");
	c_ChoixDebitR.AddString("2400S");
	c_ChoixDebitE.AddString("3600S");
	c_ChoixDebitR.AddString("3600S");

	//Initialisation - Diversité Emission
	c_DivDebitEmi.AddString("75C");
	c_DivDebitEmi.AddString("150C");
	c_DivDebitEmi.AddString("300C");
	c_DivDebitEmi.AddString("600C");
	c_DivDebitEmi.AddString("1200C");
	c_DivDebitEmi.AddString("1200S");
	c_DivDebitEmi.AddString("2400C");
	c_DivDebitEmi.AddString("2400S");
	c_DivDebitEmi.AddString("3600S");
	c_DivDebitEmi.SetCurSel(6);			//2400S

	//Initialisation de la liste Entrelaceur Réception
	InitialisationEntrelaceurRec();
	c_ChoixEntR.SetCurSel(2);

}


//Initialisation de liste des débit pour le mode : 4529
void CDlgTRC1752_MOD_PROG_CONF::InitialisationListeDebit4529()
{
	//RAZ des listes
	InitialisationListeDebitE();
	InitialisationListeDebitR();

	//Initialisation
	c_ChoixDebitE.AddString("75C");
	c_ChoixDebitR.AddString("75C");
	c_ChoixDebitE.AddString("150C");
	c_ChoixDebitR.AddString("150C");
	c_ChoixDebitE.AddString("300C");
	c_ChoixDebitR.AddString("300C");
	c_ChoixDebitE.AddString("600C");
	c_ChoixDebitR.AddString("600C");
	c_ChoixDebitE.AddString("600S");
	c_ChoixDebitR.AddString("600S");
	c_ChoixDebitE.AddString("1200C");
	c_ChoixDebitR.AddString("1200C");
	c_ChoixDebitE.AddString("1200S");
	c_ChoixDebitR.AddString("1200S");
	c_ChoixDebitE.AddString("1800S");
	c_ChoixDebitR.AddString("1800S");

	//Initialisation - Diversité Emission
	c_DivDebitEmi.AddString("75C");
	c_DivDebitEmi.AddString("150C");
	c_DivDebitEmi.AddString("300C");
	c_DivDebitEmi.AddString("600C");
	c_DivDebitEmi.AddString("600S");
	c_DivDebitEmi.AddString("1200C");
	c_DivDebitEmi.AddString("1200S");
	c_DivDebitEmi.AddString("1800C");
	c_DivDebitEmi.SetCurSel(5);			//2400S

	//Initialisation de la liste Entrelaceur Réception
	InitialisationEntrelaceurRec();
	c_ChoixEntR.SetCurSel(2);
}

//Initialisation de liste des débit pour le mode : FSK
void CDlgTRC1752_MOD_PROG_CONF::InitialisationListeDebitFSK()
{
	//RAZ des listes
	InitialisationListeDebitE();
	InitialisationListeDebitR();

	//Initialisation
	c_ChoixDebitE.AddString("50");
	c_ChoixDebitR.AddString("50");
	c_ChoixDebitE.AddString("75");
	c_ChoixDebitR.AddString("75");
	c_ChoixDebitE.AddString("100");
	c_ChoixDebitR.AddString("100");
	c_ChoixDebitE.AddString("150");
	c_ChoixDebitR.AddString("150");
	c_ChoixDebitE.AddString("200");
	c_ChoixDebitR.AddString("200");
	c_ChoixDebitE.AddString("300");
	c_ChoixDebitR.AddString("300");
	c_ChoixDebitE.AddString("600");
	c_ChoixDebitR.AddString("600");
	c_ChoixDebitE.AddString("1200");
	c_ChoixDebitR.AddString("1200");
}

//Initialisation de liste des débit pour le mode : MIL110
void CDlgTRC1752_MOD_PROG_CONF::InitialisationListeDebitMIL110()
{
	//RAZ des listes
	InitialisationListeDebitE();
	InitialisationListeDebitR();

	//Initialisation
	c_ChoixDebitE.AddString("75C");
	c_ChoixDebitE.AddString("150C");
	c_ChoixDebitE.AddString("300C");
	c_ChoixDebitE.AddString("600C");
	c_ChoixDebitE.AddString("1200C");
	c_ChoixDebitE.AddString("2400C");
	c_ChoixDebitE.AddString("2400P");
	c_ChoixDebitE.AddString("4800S");
	c_ChoixDebitR.AddString("AUTO");

	//Initialisation de la liste Entrelaceur Réception
	InitialisationListeEntrelaceurMIL110();

	/*L’entrelacement utilisé en réception est déterminé par le modem HF en fonction du préambule
	reçu. Lorsque ce préambule est ambigu, (entrelacement court / pas d’entrelacement) le modem
	utilise la valeur indiquée dans le champ "entrelaceur supposé".
	*/
	c_ChoixEntR.SetCurSel(0);
}

//InitialisationListeEntrelaceurMIL110
void CDlgTRC1752_MOD_PROG_CONF::InitialisationListeEntrelaceurMIL110()
{
	//RAZ de la liste
	InitialisationEntrelaceurMIL110();

	//Initialisation
	c_ChoixEntR.AddString("S");
	c_ChoixEntR.AddString("C");
}

//Initialisation de la liste Entrelaceur pour les autres mode
void CDlgTRC1752_MOD_PROG_CONF::InitialisationEntrelaceurRec()
{
	//RAZ de la liste
	c_ChoixEntR.ResetContent();

	//Initialisation
	c_ChoixEntR.AddString("S");
	c_ChoixEntR.AddString("C");
	c_ChoixEntR.AddString("L");
}
//-------------------------------------------------------------------------------------------
//Choix des paramètres et Vérification des conditions
//-------------------------------------------------------------------------------------------

//-----------------------
//Choix du Débit Emission
//-----------------------
void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfChDebitE()
{
	/*
	Condirions 4285 :
	- La configuration 2400 bits/s avec codage permet un entrelacement court ou long seulement.
	- La configuration 3600 bit/s sans codage est réalisée sans entrelacement.
	Conditions 4529 :
	- La configuration 1200 bits/s avec codage permet un entrelacement Court ou Long seulement.
	- La configuration 1800 bits/s sans codage est réalisée Sans entrelacement.
	Condition MIL110 :
	- Le débit 4800 b/s est nécessairement avec entrelaceur nul
	*/


	if (m_ChoixMode == 5 || m_ChoixMode == 6)	//TRANSPARENT ou REPOS
		return;

	//Selection du débit émission
	m_ChoixDebitE = c_ChoixDebitE.GetCurSel();

	//Selection de lentrelacement
	m_ChoixEntE = c_ChoixEntE.GetCurSel();

	/*
	Lorsque l’utilisateur choisi un paramètre (débit/codage/entrelacement) en émission, ce paramètre
	est copié en réception.
	*/
	if (m_ChoixMode != 4 )						//Autre que MIL110
	{
		//Débit
		m_ChoixDebitR = m_ChoixDebitE;
		c_ChoixDebitR.SetCurSel(m_ChoixDebitR);
		//Entrelacement
		m_ChoixEntR = m_ChoixEntE;
		c_ChoixEntR.SetCurSel(m_ChoixEntR);
	}

	//4285 : La configuration 2400 bits/s avec codage permet un entrelacement court ou long seulement.
	if (m_ChoixMode == 0 && m_ChoixEntE == 0 && m_ChoixDebitE == 6)
	{
		AfxMessageBox("La configuration 2400 bits/s avec codage permet un entrelacement court ou long seulement.");
		c_ChoixEntE.SetCurSel(2);
		m_ChoixEntE = c_ChoixEntE.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2 || c_ChoixSousMode.GetCurSel() == 3)
			c_ChoixEntR.SetCurSel(2);
	}
	//4285		: La configuration 3600 bit/s sans codage est réalisée Sans entrelacement.
	//4529		: La configuration 1800 bits/s sans codage est réalisée Sans entrelacement.
	//MIL110	: Le débit 4800 b/s est nécessairement Sans entrelacement.
	if ((m_ChoixMode == 0 && m_ChoixDebitE == 8) || (m_ChoixMode == 1 && m_ChoixDebitE == 7) || (m_ChoixMode == 4 && m_ChoixDebitE == 7))
	{
		c_ChoixEntE.SetCurSel(0);
		m_ChoixEntE = c_ChoixEntE.GetCurSel();
		c_ChoixEntR.SetCurSel(0);
		m_ChoixEntR = c_ChoixEntR.GetCurSel();
	}

	//4529 : La configuration 1200 bits/s avec codage permet un entrelacement Court ou Long seulement.
	if (m_ChoixMode == 1 && m_ChoixEntE == 0 && m_ChoixDebitE == 5)
	{
		AfxMessageBox("La configuration 1200 bits/s avec codage permet un entrelacement Court ou Long seulement.");
		c_ChoixEntE.SetCurSel(2);
		m_ChoixEntE = c_ChoixEntE.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2 || c_ChoixSousMode.GetCurSel() == 3)
			c_ChoixEntR.SetCurSel(2);
	}

	//MIL110 : Le débit 2400 bits/s phonie est avec entrelaceur court ou nul.
	if (m_ChoixMode == 4 && m_ChoixEntE == 2 && m_ChoixDebitE == 6)
	{
		AfxMessageBox("Le débit 2400 bits/s phonie est avec entrelaceur court ou nul.");
		c_ChoixEntE.SetCurSel(0);
		m_ChoixEntE = c_ChoixEntE.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2)
			c_ChoixEntR.SetCurSel(0);
	}

}

void CDlgTRC1752_MOD_PROG_CONF::OnEditchangeProgConfChDebitE()
{
	OnSelchangeProgConfChDebitE();
}

void CDlgTRC1752_MOD_PROG_CONF::OnEditupdateProgConfChDebitE()
{
	OnSelchangeProgConfChDebitE();
}
//-----------------------------------
//Selection de l'entrelaceur emission
//-----------------------------------
void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfChEntE()
{

	//Selection de lentrelacement
	m_ChoixEntE = c_ChoixEntE.GetCurSel();
	//Selection du débit émission
	m_ChoixDebitE = c_ChoixDebitE.GetCurSel();

	//Si on est en HD
	if (c_ChoixSousMode.GetCurSel() == 2 )
	{
		m_ChoixEntR = m_ChoixEntE;
		c_ChoixEntR.SetCurSel(m_ChoixEntE);
	}

	//4285 : La configuration 2400 bits/s avec codage permet un entrelacement court ou long seulement.
	if (m_ChoixMode == 0 && m_ChoixEntE == 0 && m_ChoixDebitE == 6)
	{
		AfxMessageBox("La configuration 2400 bits/s avec codage permet un entrelacement court ou long seulement.");
		c_ChoixEntE.SetCurSel(2);
		m_ChoixEntE = c_ChoixEntE.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2)
			c_ChoixEntR.SetCurSel(2);
	}

	//4285		: La configuration 3600 bit/s sans codage est réalisée Sans entrelacement.
	//4529		: La configuration 1800 bits/s sans codage est réalisée Sans entrelacement.
	//MIL110	: Le débit 4800 b/s est nécessairement Sans entrelacement.
	if ((m_ChoixMode == 0 && (m_ChoixEntE == 1 || m_ChoixEntE == 2)  && m_ChoixDebitE == 8) |
		(m_ChoixMode == 1 && (m_ChoixEntE == 1 || m_ChoixEntE == 2)  && m_ChoixDebitE == 7) |
		(m_ChoixMode == 4 && (m_ChoixEntE == 1 || m_ChoixEntE == 2)  && m_ChoixDebitE == 7))
	{
		if (m_ChoixMode == 0)
			AfxMessageBox("La configuration 3600 bit/s sans codage est réalisée sans entrelacement.");
		if (m_ChoixMode == 1)
			AfxMessageBox("La configuration 1800 bit/s sans codage est réalisée sans entrelacement.");
		if (m_ChoixMode == 4)
			AfxMessageBox("Le débit 4800 b/s est nécessairement Sans entrelacement.");

		c_ChoixEntE.SetCurSel(0);
		m_ChoixEntE = c_ChoixEntE.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2)
			c_ChoixEntR.SetCurSel(0);
	}

	//4529 : La configuration 1200 bits/s avec codage permet un entrelacement Court ou Long seulement.
	if (m_ChoixMode == 1 && m_ChoixEntE == 0 && m_ChoixDebitE == 5)
	{
		AfxMessageBox("La configuration 1200 bits/s avec codage permet un entrelacement Court ou Long seulement.");
		c_ChoixEntE.SetCurSel(2);
		m_ChoixEntE = c_ChoixEntE.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2)
			c_ChoixEntR.SetCurSel(2);
	}

	//MIL110 : Le débit 2400 bits/s phonie est avec entrelaceur court ou nul.
	if (m_ChoixMode == 4 && m_ChoixEntE == 2 && m_ChoixDebitE == 6)
	{
		AfxMessageBox("Le débit 2400 bits/s phonie est avec entrelaceur court ou nul.");
		c_ChoixEntE.SetCurSel(0);
		m_ChoixEntE = c_ChoixEntE.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2)
			c_ChoixEntR.SetCurSel(0);
	}
}

void CDlgTRC1752_MOD_PROG_CONF::OnEditchangeProgConfChEntE()
{
	OnSelchangeProgConfChEntE();
}

void CDlgTRC1752_MOD_PROG_CONF::OnEditupdateProgConfChEntE()
{
	OnSelchangeProgConfChDebitR();
}
//------------------------
//Choix du Débit Réception
//------------------------
void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfChDebitR()
{
	/*
	Conditions 4285 :
	- La configuration 2400 bits/s avec codage permet un entrelacement court ou long seulement.
	- La configuration 3600 bit/s sans codage est réalisée sans entrelacement.
	Conditions 4529 :
	- La configuration 1200 bits/s avec codage permet un entrelacement Court ou Long seulement.
	- La configuration 1800 bits/s sans codage est réalisée Sans entrelacement.
	*/

	if (m_ChoixMode == 5 || m_ChoixMode == 6)	//TRANSPARENT ou REPOS
		return;

	//Selection du débit réception
	m_ChoixDebitR = c_ChoixDebitR.GetCurSel();

	//Si on est en HD et autre que MIL110
	if (c_ChoixSousMode.GetCurSel() == 2 && c_ChoixMode.GetCurSel() != 4)
	{
		m_ChoixDebitE = m_ChoixDebitR;
		c_ChoixDebitE.SetCurSel(m_ChoixDebitR);
	}


	//Selection de lentrelacement
	m_ChoixEntR = c_ChoixEntR.GetCurSel();

	//4285 : La configuration 2400 bits/s avec codage permet un entrelacement court ou long seulement.
	if (m_ChoixMode == 0 && m_ChoixEntR == 0 && m_ChoixDebitR == 6)
	{
		AfxMessageBox("La configuration 2400 bits/s avec codage permet un entrelacement court ou long seulement.");
		c_ChoixEntR.SetCurSel(2);
		m_ChoixEntR = c_ChoixEntR.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2)
			c_ChoixEntR.SetCurSel(2);
	}
	//4285		: La configuration 3600 bit/s sans codage est réalisée sans entrelacement.
	//4529		: La configuration 1800 bits/s sans codage est réalisée Sans entrelacement.
	if ((m_ChoixMode == 0 && m_ChoixDebitE == 8) || (m_ChoixMode == 1 && m_ChoixDebitE == 7))
	{
		c_ChoixEntR.SetCurSel(0);
		m_ChoixEntR = c_ChoixEntR.GetCurSel();
		c_ChoixEntE.SetCurSel(0);
		m_ChoixEntE = c_ChoixEntR.GetCurSel();
	}

	//4529 : La configuration 1200 bits/s avec codage permet un entrelacement Court ou Long seulement.
	if (m_ChoixMode == 1 && m_ChoixEntR == 0 && m_ChoixDebitR == 5)
	{
		AfxMessageBox("La configuration 1200 bits/s avec codage permet un entrelacement Court ou Long seulement.");
		c_ChoixEntR.SetCurSel(2);
		m_ChoixEntR = c_ChoixEntR.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2)
			c_ChoixEntE.SetCurSel(2);
	}
}

void CDlgTRC1752_MOD_PROG_CONF::OnEditchangeProgConfChDebitR()
{
	OnSelchangeProgConfChDebitR();
}

void CDlgTRC1752_MOD_PROG_CONF::OnEditupdateProgConfChDebitR()
{
	OnSelchangeProgConfChDebitR();
}

//-----------------------------------
//Selection de l'entrelaceur réception
//-----------------------------------
void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfChEntR()
{

	//Selection de lentrelacement
	m_ChoixEntR = c_ChoixEntR.GetCurSel();
	//Selection du débit réception
	m_ChoixDebitR = c_ChoixDebitR.GetCurSel();

	//Si on est en HD
	if (c_ChoixSousMode.GetCurSel() == 2 )
	{
		m_ChoixEntE = m_ChoixEntR;
		c_ChoixEntE.SetCurSel(m_ChoixEntR);
	}

	//4285 : La configuration 2400 bits/s avec codage permet un entrelacement court ou long seulement.
	if (m_ChoixMode == 0 && m_ChoixEntR == 0 && m_ChoixDebitR == 6)
	{
		AfxMessageBox("La configuration 2400 bits/s avec codage permet un entrelacement court ou long seulement.");
		c_ChoixEntR.SetCurSel(2);
		m_ChoixEntR = c_ChoixEntR.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2)
			c_ChoixEntE.SetCurSel(2);
	}
	//4285		: La configuration 3600 bit/s sans codage est réalisée sans entrelacement.
	//4529		: La configuration 1800 bits/s sans codage est réalisée Sans entrelacement.
	if ((m_ChoixMode == 0 && (m_ChoixEntR == 1 || m_ChoixEntR == 2)  && m_ChoixDebitR == 8) |
		(m_ChoixMode == 1 && (m_ChoixEntR == 1 || m_ChoixEntR == 2)  && m_ChoixDebitR == 7))
	{
		if (m_ChoixMode == 0)
			AfxMessageBox("La configuration 3600 bit/s sans codage est réalisée sans entrelacement.");
		if (m_ChoixMode == 1)
			AfxMessageBox("La configuration 1800 bit/s sans codage est réalisée sans entrelacement.");

		c_ChoixEntR.SetCurSel(0);
		m_ChoixEntR = c_ChoixEntE.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2)
			c_ChoixEntE.SetCurSel(0);
	}

	//4529 : La configuration 1200 bits/s avec codage permet un entrelacement Court ou Long seulement.
	if (m_ChoixMode == 1 && m_ChoixEntR == 0 && m_ChoixDebitR == 5)
	{
		AfxMessageBox("La configuration 1200 bits/s avec codage permet un entrelacement Court ou Long seulement.");
		c_ChoixEntR.SetCurSel(2);
		m_ChoixEntR = c_ChoixEntR.GetCurSel();
		if (c_ChoixSousMode.GetCurSel() == 2)
			c_ChoixEntE.SetCurSel(2);
	}
}

void CDlgTRC1752_MOD_PROG_CONF::OnEditchangeProgConfChEntR()
{
	OnSelchangeProgConfChEntR();
}

void CDlgTRC1752_MOD_PROG_CONF::OnEditupdateProgConfChEntR()
{
	OnSelchangeProgConfChEntR();
}
//--------------------------------------------------------------------

//----------------------
//Selection du Sous Mode
//----------------------
void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfChSMode()
{

	if (m_ChoixMode == 5 || m_ChoixMode == 6)	//TRANSPARENT ou REPOS
		return;

	//Selection du Sous Mode
	m_ChoixSousMode = c_ChoixSousMode.GetCurSel();

	//Choix simplex Réception
	if (m_ChoixSousMode == 0 )
	{
		AfficheFonctionSousModeEM(FALSE);
	}
	else
	{
		AfficheFonctionSousModeEM(TRUE);
	}

	//Choix simplex Emission
	if (m_ChoixSousMode == 1 )
	{
		AfficheFonctionSousModeRE(FALSE);
		m_ChoixDiv = 1;
		c_ChoixDiv.SetCurSel(m_ChoixDiv);
	}
	else
	{
		AfficheFonctionSousModeRE(TRUE);
	}

	//Si choix HD alors remise à jour en fonction de la sélection de l'émission
	if (m_ChoixSousMode == 2)
	{
		m_ChoixDebitR = c_ChoixDebitE.GetCurSel();
		c_ChoixDebitR.SetCurSel(m_ChoixDebitR);
		m_ChoixEntR = c_ChoixEntE.GetCurSel();
		c_ChoixEntR.SetCurSel(m_ChoixEntR);
		c_SP_R.SetCurSel(c_SP_E.GetCurSel());
		c_Shift_R.SetCurSel(c_Shift_E.GetCurSel());


		if (m_ChoixMode == 2)	//FSKP
			AfficheFSKP();
		if (m_ChoixMode == 3)	//FSKV
		{
			// FFT ADEL_97099
			CString str;

			m_Frq_H_Rec = m_Frq_H_Emi;
			m_Frq_B_Rec = m_Frq_B_Emi;

			c_Frq_H_Emi.GetWindowText(str);
			c_Frq_H_Rec.SetWindowText(str);
			str.Empty();
			c_Frq_B_Emi.GetWindowText(str);
			c_Frq_B_Rec.SetWindowText(str);

			AfficheFSKV();
		}
		if (m_ChoixMode == 4)	//MIL
			AfficheMIL110();
		//if (m_ChoixMode == 5 | m_ChoixMode == 6)	//TRANSPARENT ou REPOS
			//EffaceALL();
	}
	//Si choix FD
	if (m_ChoixSousMode == 3 && c_ChoixDiv.GetCurSel() == 0)
	{
		GetDlgItem(IDC_MOD_PROG_DIV)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_DIV_INFO)->ShowWindow(FALSE);
		GetDlgItem(IDC_PROG_DIV_SORTIE_DATA)->ShowWindow(FALSE);
		GetDlgItem(IDC_PROG_DIV_SOUS_MODE)->ShowWindow(FALSE);
		GetDlgItem(IDC_STATIC_DIV_E)->ShowWindow(FALSE);
		GetDlgItem(IDC_PROG_DIV_CH_DEBIT_E)->ShowWindow(FALSE);
		GetDlgItem(IDC_PROG_DIV_CH_ENT_E)->ShowWindow(FALSE);
	}
}

void CDlgTRC1752_MOD_PROG_CONF::OnEditchangeProgConfChSMode()
{
	OnSelchangeProgConfChSMode();
}

void CDlgTRC1752_MOD_PROG_CONF::OnEditupdateProgConfChSMode()
{
	OnSelchangeProgConfChSMode();
}
//-------------------------------------------------------------------------------------------

void CDlgTRC1752_MOD_PROG_CONF::OnShowWindow(BOOL bShow, UINT nStatus)
{
	CDialog::OnShowWindow(bShow, nStatus);

	OnSelchangeProgConfChMode();

}


void CDlgTRC1752_MOD_PROG_CONF::OnOutofmemoryProgConfFrqESpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnDeltaposProgConfFrqESpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	/*
	La fréquence centrale utilisée dans le sens émission réglable de 900 Hz à 2400 Hz par pas de
	100 Hz,
	*/
	if (pNMUpDown->iDelta > 0)  m_Frq_C_E += FRQCPAS;
		else m_Frq_C_E -= FRQCPAS;


	if ( m_Frq_C_E > FRQCMAX )
	{
		AfxMessageBox("La fréquence centrale émission réglable de 900 Hz à 2400 Hz");
		m_Frq_C_E = FRQCMAX;
	}

	if ( m_Frq_C_E < FRQCMIN)
	{
		AfxMessageBox("La fréquence centrale émission réglable de 900 Hz à 2400 Hz");
		m_Frq_C_E = FRQCMIN;
	}

	//Si on est en HD
	if (c_ChoixSousMode.GetCurSel() == 2 )
	{
		m_Frq_C_R = m_Frq_C_E;
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnOutofmemoryProgConfFrqHESpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnDeltaposProgConfFrqHESpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	/*
	La fréquence "Space" (Fréquance Haute) : réglable de 300 Hz à 3300 Hz par pas de 1 Hz,
	*/
	if (pNMUpDown->iDelta > 0)  m_Frq_H_Emi += FRQPAS;
		else m_Frq_H_Emi -= FRQPAS;


	if ( m_Frq_H_Emi > FRQHAUTE )
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_H_Emi = FRQHAUTE;
	}

	if ( m_Frq_H_Emi < FRQBASSE)
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_H_Emi = FRQBASSE;
	}

	/*
	En mode Half Duplex, lorsque l’utilisateur programme un paramètre émission (fréquence
	haute, fréquence basse), les paramètres de la voie réception sont forcés aux mêmes valeurs.
	Si l’utilisateur désire choisir des valeurs de paramètres réception, différentes de celles de
	l’émission, il peut les programmer en agissant directement sur les paramètres de la voie réception.
	*/
	if (c_ChoixSousMode.GetCurSel() == 2)	// HD
	{
		//CString str;
		//c_Frq_H_Emi.GetWindowText(str);
		m_Frq_H_Rec = m_Frq_H_Emi;
		//c_Frq_H_Rec.SetWindowText(str);
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnOutofmemoryProgConfFrqHRSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnDeltaposProgConfFrqHRSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	/*
	La fréquence "Space" (Fréquance Haute) : réglable de 300 Hz à 3300 Hz par pas de 1 Hz,
	*/
	if (pNMUpDown->iDelta > 0)  m_Frq_H_Rec += FRQPAS;
		else m_Frq_H_Rec -= FRQPAS;


	if ( m_Frq_H_Rec > FRQHAUTE )
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_H_Rec = FRQHAUTE;
	}

	if ( m_Frq_H_Rec < FRQBASSE)
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_H_Rec = FRQBASSE;
	}


	if (c_ChoixSousMode.GetCurSel() == 2)	// HD
	{
		//CString str;
		//c_Frq_H_Rec.GetWindowText(str);
		m_Frq_H_Emi = m_Frq_H_Rec;
		//c_Frq_H_Rec.SetWindowText(str);
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnOutofmemoryProgConfFrqRSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnDeltaposProgConfFrqRSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	/*
	La fréquence centrale utilisée dans le sens émission réglable de 900 Hz à 2400 Hz par pas de
	100 Hz,
	*/
	if (pNMUpDown->iDelta > 0)  m_Frq_C_R += FRQCPAS;
		else m_Frq_C_R -= FRQCPAS;


	if ( m_Frq_C_R > FRQCMAX )
	{
		AfxMessageBox("La fréquence centrale émission réglable de 900 Hz à 2400 Hz");
		m_Frq_C_R = FRQCMAX;
	}

	if ( m_Frq_C_R < FRQCMIN)
	{
		AfxMessageBox("La fréquence centrale émission réglable de 900 Hz à 2400 Hz");
		m_Frq_C_R = FRQCMIN;
	}

	//Si on est en HD
	if (c_ChoixSousMode.GetCurSel() == 2 )
	{
		m_Frq_C_E = m_Frq_C_R;
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnOutofmemoryProgConfFrqBESpin(NMHDR* pNMHDR, LRESULT* pResult)
{

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnDeltaposProgConfFrqBESpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
		/*
	La fréquence "Mark" (Fréquance Basse) : réglable de 300 Hz à 3300 Hz par pas de 1 Hz,
	*/
	if (pNMUpDown->iDelta > 0)  m_Frq_B_Emi += FRQPAS;
		else m_Frq_B_Emi -= FRQPAS;


	if ( m_Frq_B_Emi > FRQHAUTE )
	{
		AfxMessageBox("La fréquence \"Mark\" [Fréquance Basse] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_B_Emi = FRQHAUTE;
	}

	if ( m_Frq_B_Emi < FRQBASSE)
	{
		AfxMessageBox("La fréquence \"Mark\" [Fréquance Basse] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_B_Emi = FRQBASSE;
	}

	/*
	En mode Half Duplex, lorsque l’utilisateur programme un paramètre émission (fréquence
	haute, fréquence basse), les paramètres de la voie réception sont forcés aux mêmes valeurs.
	Si l’utilisateur désire choisir des valeurs de paramètres réception, différentes de celles de
	l’émission, il peut les programmer en agissant directement sur les paramètres de la voie réception.
	*/
	if (c_ChoixSousMode.GetCurSel() == 2)
	{
		//CString str;
		//c_Frq_B_Emi.GetWindowText(str);
		m_Frq_B_Rec = m_Frq_B_Emi;
		//c_Frq_B_Rec.SetWindowText(str);
	}

	UpdateData(FALSE);

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnOutofmemoryProgConfFrqBRSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnDeltaposProgConfFrqBRSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	/*
	La fréquence "Mark" (Fréquance Haute) : réglable de 300 Hz à 3300 Hz par pas de 1 Hz,
	*/
	if (pNMUpDown->iDelta > 0)  m_Frq_B_Rec += FRQPAS;
		else m_Frq_B_Rec -= FRQPAS;


	if ( m_Frq_B_Rec > FRQHAUTE )
	{
		AfxMessageBox("La fréquence \"Mark\" [Fréquance Basse] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_B_Rec = FRQHAUTE;
	}

	if ( m_Frq_B_Rec < FRQBASSE)
	{
		AfxMessageBox("La fréquence \"Mark\" [Fréquance Basse] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_B_Rec = FRQBASSE;
	}

	if (c_ChoixSousMode.GetCurSel() == 2)
	{
		//CString str;
		//c_Frq_B_Emi.GetWindowText(str);
		m_Frq_B_Emi = m_Frq_B_Rec;
		//c_Frq_B_Rec.SetWindowText(str);
	}

	UpdateData(FALSE);

	*pResult = 0;
}

//**************************************
// Fonction Valide()
//**************************************
void CDlgTRC1752_MOD_PROG_CONF::Valide()
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

	// Test si la configuration est utilisée dans un canal actif
	// FFT_1169
	if (TestCanal() == FALSE)
	{
		OnSelchangeProgConfChCanal();
		return;
	}

	UpdateData(TRUE);

	//Affichage de la vue pour l'utilisation de la diversité en émission, si elle n'est
	//pas affichée, par un clique sur le bouton VAL.
	if((c_ChoixSousMode.GetCurSel() == 0) && !GetDlgItem(IDC_MOD_PROG_DIV)->IsWindowVisible() && c_ChoixDiv.GetCurSel() == 0)
	{
		AfficheCache2cas(TRUE);

		if (c_ChoixMode.GetCurSel() == 0)
		{
			GetDlgItem(IDC_PROG_CONF_FRQ_E_DIV)->ShowWindow(FALSE);
			GetDlgItem(IDC_PROG_CONF_FRQ_E_DIV_SPIN)->ShowWindow(FALSE);
		}
		return;
	}

	//*******************************************************************************************************************
	CString str;
	TChannelConfiguration conf_courante;
	int l_str;
	c_ChoixCanal.GetWindowText(str);

	if (str == "MC")
		conf_courante = eqp->GetChannelConfiguration(mc_value);
	else
		conf_courante = eqp->GetChannelConfiguration(CHANNELS_CONFIGURATION[c_ChoixCanal.GetCurSel()]);

	//*******************
	// Traitement du Mode
	//*******************
	/*
	if (c_ChoixMode.GetCurSel() == 2 || c_ChoixMode.GetCurSel() == 3)	//FSKV ou FSKP vesr BFSK
		str = "BFSK";
	else
	*/
	if (c_ChoixMode.GetCurSel() == 5)								//TRANSPARENT vers TRANSP
			str = "TRANSP";
		else
			c_ChoixMode.GetLBText(c_ChoixMode.GetCurSel(), str);

	conf_courante.waveform = str;

	// Mode TRANSPARENT ou REPOS
	if (c_ChoixMode.GetCurSel() == 5 || c_ChoixMode.GetCurSel() == 6)
	{
		eqp->SetChannelConfiguration(CHANNELS_CONFIGURATION[c_ChoixCanal.GetCurSel()], conf_courante);
		UpdateData(FALSE);
		return;
	}

	//********************
	// DébitCodageEmission
	//********************
	c_ChoixDebitE.GetLBText(c_ChoixDebitE.GetCurSel(), str);			//dans str = 2400C ou 1200
	l_str = str.GetLength();

	// 4285-4529-MIL110
	if (c_ChoixMode.GetCurSel() == 0 || c_ChoixMode.GetCurSel() == 1 || c_ChoixMode.GetCurSel() == 4)
		conf_courante.af_transmission_baudrate = atoi(str.Left(l_str-1));

	// FSKV-FSKP
	if (c_ChoixMode.GetCurSel() == 2 || c_ChoixMode.GetCurSel() == 3)
		conf_courante.af_transmission_baudrate = atoi(str);

	//*******
	// Coding
	//*******
	if (str.Right(1) == "C")
		conf_courante.af_transmission_codingtype = "CODE";
	if (str.Right(1) == "L")
		conf_courante.af_transmission_codingtype = "LONG";
	if (str.Right(1) == "S")
		conf_courante.af_transmission_codingtype = "SANS";
	if (str.Right(1) == "P")
		conf_courante.af_transmission_codingtype = "PHONIE";


	//**********************
	// EntrelacementEmission
	//**********************
	switch(c_ChoixEntE.GetCurSel())
	{
	case 0:
		conf_courante.af_transmission_interleaving = "SANS";
		break;
	case 1:
		conf_courante.af_transmission_interleaving = "COURT";
		break;
	case 2:
		conf_courante.af_transmission_interleaving = "LONG";
		break;
	default:
		conf_courante.af_transmission_interleaving = "SANS";
		break;
	}

	//*********************
	// DébitCodageRéception
	//*********************
	c_ChoixDebitR.GetLBText(c_ChoixDebitR.GetCurSel(), str);
	l_str = str.GetLength();

	// 4285-4529-MIL110
	if (c_ChoixMode.GetCurSel() == 0 || c_ChoixMode.GetCurSel() == 1 || c_ChoixMode.GetCurSel() == 4)
		conf_courante.af_reception_baudrate = atoi(str.Left(l_str-1));

	// FSKV-FSKP
	if (c_ChoixMode.GetCurSel() == 2 || c_ChoixMode.GetCurSel() == 3)
		conf_courante.af_reception_baudrate = atoi(str);

	//*******
	// Coding
	//*******
	if (str.Right(1) == "C")
		conf_courante.af_reception_codingtype = "CODE";
	if (str.Right(1) == "L")
		conf_courante.af_reception_codingtype = "LONG";
	if (str.Right(1) == "S")
		conf_courante.af_reception_codingtype = "SANS";
	if (str.Right(1) == "P")
		conf_courante.af_reception_codingtype = "PHONIE";

	//***********************
	// EntrelacementRéception
	//***********************
	switch(c_ChoixEntR.GetCurSel())
	{
	case 0:
		conf_courante.af_reception_interleaving = "SANS";
		break;
	case 1:
		conf_courante.af_reception_interleaving = "COURT";
		break;
	case 2:
		conf_courante.af_reception_interleaving = "LONG";
		break;
	default:
		conf_courante.af_reception_interleaving = "SANS";
		break;
	}

	//**********
	// Direction
	//**********
	switch(c_ChoixSousMode.GetCurSel())
	{
	case 0:
		str = "RX";			//Pour RE
		break;
	case 1:
		str = "TX";			//Pour EM
		break;
	default:
		c_ChoixSousMode.GetLBText(c_ChoixSousMode.GetCurSel(), str);
		break;
	}
	conf_courante.direction = str;

	//**********
	// Diversité
	//**********
	conf_courante.diversity = "SANS";
	if (c_ChoixDiv.GetCurSel() == 0)
	{
		conf_courante.diversity = "AVEC";

		c_DivDebitEmi.GetLBText(c_DivDebitEmi.GetCurSel(), str);			//dans str = 2400C ou 1200
		l_str = str.GetLength();

		//***********************************
		// Diversité : Debit 4285-4529-MIL110
		//***********************************
		if (c_ChoixMode.GetCurSel() == 0 || c_ChoixMode.GetCurSel() == 1 || c_ChoixMode.GetCurSel() == 4)
		conf_courante.slave_baudrate = atoi(str.Left(l_str-1));

		//Diversité : Coding
		if (str.Right(1) == "C")
			conf_courante.slave_codingtype = "CODE";
		if (str.Right(1) == "L")
			conf_courante.slave_codingtype = "LONG";
		if (str.Right(1) == "P")
			conf_courante.slave_codingtype = "PHONIE";

		//***********************************
		// Diversité : Entrelacement Emission
		//***********************************
		switch(c_DivEntrelaceurEmi.GetCurSel())
		{
		case 0:
			conf_courante.slave_interleaving = "SANS";
			break;
		case 1:
			conf_courante.slave_interleaving = "COURT";
			break;
		case 2:
			conf_courante.slave_interleaving = "LONG";
			break;
		default:
			conf_courante.slave_interleaving = "SANS";
		break;
		}

		//***********************************************************************
		// Diversité : Fréquence centrale Emission en Diversité pour le mode 4529
		//***********************************************************************
		conf_courante.slave_carrier_frequency = m_Frq_Div_C_E;

		//**********************
		// Diversité : direction
		//**********************
		switch(c_DivSousMode.GetCurSel())
		{
		case 0:
			str = "RX";			//Pour RE
			break;
		default:
			c_DivSousMode.GetLBText(c_DivSousMode.GetCurSel(), str);		//Pour FD
			break;
		}
		conf_courante.slave_direction = str;

		// Diversité : use_data
		//*********************
		conf_courante.use_data = "SANS";
		if(c_DivSortieData.GetCurSel() == 1)
			conf_courante.use_data = "AVEC";
	}


	//**************************************************************************
	// Fréquence centrale Emission/Réception en 4529
	//**************************************************************************
	if (c_ChoixMode.GetCurSel() == 1 && c_ChoixSousMode.GetCurSel() == 1)		//Emission
		conf_courante.transmission_carrier_frequency = m_Frq_C_E;

	if (c_ChoixMode.GetCurSel() == 1 && c_ChoixSousMode.GetCurSel() == 0)		//Réception
		conf_courante.reception_carrier_frequency = m_Frq_C_R;

	if (c_ChoixMode.GetCurSel() == 1 && ( c_ChoixSousMode.GetCurSel() == 2 || c_ChoixSousMode.GetCurSel() == 3))	//HD ou FD
	{
		conf_courante.transmission_carrier_frequency = m_Frq_C_E;
		conf_courante.reception_carrier_frequency = m_Frq_C_R;
	}

	//*********************************************************************
	// TODO Fréquence Haute/Basse Emission/Réception en FSKV et FSKP (BFSK)
	//*********************************************************************

	if ( c_ChoixMode.GetCurSel() == 3 && c_ChoixSousMode.GetCurSel() == 1)		//Emission
	{
		if (m_Frq_H_Emi<m_Frq_B_Emi)
		{
			AfxMessageBox("La fréquence Haute est toujours supérieure à la fréquence Basse !");
			return;
		}
		conf_courante.transmission_space_frequency = m_Frq_H_Emi;
		conf_courante.transmission_mark_frequency = m_Frq_B_Emi;
	}

	if ( c_ChoixMode.GetCurSel() == 3 && c_ChoixSousMode.GetCurSel() == 0)		//Réception
	{
		conf_courante.reception_space_frequency = m_Frq_H_Rec;
		conf_courante.reception_mark_frequency = m_Frq_B_Rec;
	}

	if (c_ChoixMode.GetCurSel() == 3 && ( c_ChoixSousMode.GetCurSel() == 2 || c_ChoixSousMode.GetCurSel() == 3))	//HD ou FD
	{
		conf_courante.transmission_space_frequency = m_Frq_H_Emi;
		conf_courante.transmission_mark_frequency = m_Frq_B_Emi;
		conf_courante.reception_space_frequency = m_Frq_H_Rec;
		conf_courante.reception_mark_frequency = m_Frq_B_Rec;
	}

	//************
	// Cas de FSKP
	//************
	//if (c_ChoixMode.GetCurSel() == 2 && ( c_ChoixSousMode.GetCurSel() == 2 || c_ChoixSousMode.GetCurSel() == 3))
	// FFT : ADEL_97105
	if (c_ChoixMode.GetCurSel() == 2 )
	{
		CString t_spe, t_spr;
		c_SP_E.GetLBText(c_SP_E.GetCurSel(), t_spe);
		c_SP_R.GetLBText(c_SP_R.GetCurSel(), t_spr);

		int t_shiftE = 425, t_shiftR = 425;

		// Traitement de HD, FD et EM
		if ( c_ChoixSousMode.GetCurSel() == 2 || c_ChoixSousMode.GetCurSel() == 3 || c_ChoixSousMode.GetCurSel() == 1)
		{
			switch(c_Shift_E.GetCurSel())
			{
			case 0:
				t_shiftE = 42.5;
				break;
			case 1:
				t_shiftE = 85;
				break;
			case 2:
				t_shiftE = 100;
				break;
			case 3:
				t_shiftE = 200;
				break;
			case 4:
				t_shiftE = 425;
				break;
			default:
				t_shiftE = 425;
				break;
			}
		}

		// Traitement de HD, FD et RE
		if ( c_ChoixSousMode.GetCurSel() == 2 || c_ChoixSousMode.GetCurSel() == 3 || c_ChoixSousMode.GetCurSel() == 0)
		{
			switch(c_Shift_R.GetCurSel())
			{
			case 0:
				t_shiftR = 42.5;
				break;
			case 1:
				t_shiftR = 85;
				break;
			case 2:
				t_shiftR = 100;
				break;
			case 3:
				t_shiftR = 200;
				break;
			case 4:
				t_shiftR = 425;
				break;
			default:
				t_shiftR = 425;
				break;
			}
		}

		conf_courante.transmission_space_frequency	= atoi(t_spe) + t_shiftE;
		conf_courante.transmission_mark_frequency	= atoi(t_spe) - t_shiftE;

		conf_courante.reception_space_frequency		= atoi(t_spr) + t_shiftR;
		conf_courante.reception_mark_frequency		= atoi(t_spr) - t_shiftR;

		/*
		Le saut de fréquence ± 42,5 Hz correspond à la plage de fréquence :
		[sous porteuse - 42 Hz, sous porteuse + 43 Hz].
		*/
		if (c_ChoixSousMode.GetCurSel() == 2 && (c_Shift_E.GetCurSel() == 0 || c_Shift_R.GetCurSel() == 0))
		{
			conf_courante.transmission_space_frequency	= atoi(t_spe) + 43;
			conf_courante.transmission_mark_frequency	= atoi(t_spe) - 42;
			conf_courante.reception_space_frequency		= atoi(t_spr) + 43;
			conf_courante.reception_mark_frequency		= atoi(t_spr) - 42;
		}
		// Traitement de FD Emission
		if (c_ChoixSousMode.GetCurSel() == 3 && c_Shift_E.GetCurSel() == 0)
		{
			conf_courante.transmission_space_frequency	= atoi(t_spe) + 43;
			conf_courante.transmission_mark_frequency	= atoi(t_spe) - 42;
		}
		// Traitement de FD Réception
		if (c_ChoixSousMode.GetCurSel() == 3 && c_Shift_R.GetCurSel() == 0)
		{
			conf_courante.reception_space_frequency		= atoi(t_spr) + 43;
			conf_courante.reception_mark_frequency		= atoi(t_spr) - 42;
		}

		//**********************************************
		// Fréquence centrale Emission/Réception en FSKP
		//**********************************************
		if (c_ChoixMode.GetCurSel() == 2 && c_ChoixSousMode.GetCurSel() == 1)		//Emission
			conf_courante.transmission_carrier_frequency = atoi(t_spe);

		if (c_ChoixMode.GetCurSel() == 2 && c_ChoixSousMode.GetCurSel() == 0)		//Réception
			conf_courante.reception_carrier_frequency = atoi(t_spr);

		if (c_ChoixMode.GetCurSel() == 2 && ( c_ChoixSousMode.GetCurSel() == 2 || c_ChoixSousMode.GetCurSel() == 3))	//HD ou FD
		{
			conf_courante.transmission_carrier_frequency = atoi(t_spe);
			conf_courante.reception_carrier_frequency = atoi(t_spr);
		}
	}

	//********************************
	// Mise en place dans la structure
	//********************************

	if (str == "MC")
		eqp->SetChannelConfiguration(mc_value, conf_courante);
	else
		eqp->SetChannelConfiguration(CHANNELS_CONFIGURATION[c_ChoixCanal.GetCurSel()], conf_courante);

	UpdateData(FALSE);
}

//***********************************
// Affichage en fonction du Sous-Mode
//***********************************
void CDlgTRC1752_MOD_PROG_CONF::AfficheFonctionSousModeRE(bool selection)
{
	AfficheCacheDebitR(selection);
	if (m_ChoixMode != 3 && m_ChoixMode != 2)	////FSKV et FSKP
		AfficheCacheEntrelaceurR(selection);

	AfficheCacheDiversite(selection);

	if (m_ChoixMode == 1)	//4529
		AfficheCacheFrqCentraleR(selection);

	if (m_ChoixMode == 2)	//FSKP
		AfficheFSKP();

	if (m_ChoixMode == 3)	//FSKV
		AfficheFSKV();

	if (m_ChoixMode == 4)	//MIL110
		AfficheMIL110();
}
void CDlgTRC1752_MOD_PROG_CONF::AfficheFonctionSousModeEM(bool selection)
{
	AfficheCacheDebitE(selection);
	if (m_ChoixMode != 3 && m_ChoixMode != 2)	////FSKV et FSKP
		AfficheCacheEntrelaceurE(selection);

	AfficheCacheDiversite(selection);

	if (m_ChoixMode == 1)	//4529
		AfficheCacheFrqCentraleE(selection);

	if (m_ChoixMode == 2)	//FSKP
		AfficheFSKP();

	if (m_ChoixMode == 3)	//FSKV
		AfficheFSKV();

	if (m_ChoixMode == 4)	//MIL110
		AfficheMIL110();
}

//AfficheCacheDebit
void CDlgTRC1752_MOD_PROG_CONF::AfficheCacheDebitE(bool act)
{
	t_Debit.ShowWindow(TRUE);
	t_E.ShowWindow(act);
	c_ChoixDebitE.ShowWindow(act);
}
void CDlgTRC1752_MOD_PROG_CONF::AfficheCacheDebitR(bool act)
{
	t_Debit.ShowWindow(TRUE);
	t_R.ShowWindow(act);
	c_ChoixDebitR.ShowWindow(act);
}
//AfficheCacheEntrelaceur
void CDlgTRC1752_MOD_PROG_CONF::AfficheCacheEntrelaceurE(bool act)
{
	c_ChoixEntE.ShowWindow(act);
}
void CDlgTRC1752_MOD_PROG_CONF::AfficheCacheEntrelaceurR(bool act)
{
	c_ChoixEntR.ShowWindow(act);
}
//AfficheCacheDiversite
void CDlgTRC1752_MOD_PROG_CONF::AfficheCacheDiversite(bool act)
{
	c_ChoixDiv.ShowWindow(act);
	t_ChoixDiv.ShowWindow(act);
}
//AfficheCacheFrqCentrale
void CDlgTRC1752_MOD_PROG_CONF::AfficheCacheFrqCentraleE(bool act)
{
	m_FrqE.ShowWindow(act);
	s_FrqE.ShowWindow(act);
}
void CDlgTRC1752_MOD_PROG_CONF::AfficheCacheFrqCentraleR(bool act)
{
	m_FrqR.ShowWindow(act);
	s_FrqR.ShowWindow(act);
}
//AfficheCacheFrqHauteE et AfficheCacheFrqBasseE
void CDlgTRC1752_MOD_PROG_CONF::AfficheCacheFrqHauteE(bool act)
{
	//Fréquence Haute Emission
	c_Frq_H_Emi.ShowWindow(act);
	s_Frq_H_E.ShowWindow(act);
}
void CDlgTRC1752_MOD_PROG_CONF::AfficheCacheFrqBasseE(bool act)
{
	//Fréquence Basse Emission
	c_Frq_B_Emi.ShowWindow(act);
	s_Frq_B_E.ShowWindow(act);
}
//AfficheCacheFrqHauteR et AfficheCacheFrqBasseR
void CDlgTRC1752_MOD_PROG_CONF::AfficheCacheFrqHauteR(bool act)
{
	//Fréquence Haute Réception
	c_Frq_H_Rec.ShowWindow(act);
	s_Frq_H_R.ShowWindow(act);
}
void CDlgTRC1752_MOD_PROG_CONF::AfficheCacheFrqBasseR(bool act)
{
	//Fréquence Basse Réception
	c_Frq_B_Rec.ShowWindow(act);
	s_Frq_B_R.ShowWindow(act);
}

void CDlgTRC1752_MOD_PROG_CONF::OnKillfocusProgConfFrqE()
{
	/*

	if (c_ChoixSousMode.GetCurSel() == 2)  // HD
	{
		CString str;
		m_FrqE.GetWindowText(str);

		m_Frq_C_R = m_Frq_C_E;
		m_FrqR.SetWindowText(str);
	}

	UpdateData(TRUE);
	*/
}

void CDlgTRC1752_MOD_PROG_CONF::OnKillfocusProgConfFrqR()
{
	/*
	if (c_ChoixSousMode.GetCurSel() == 2)  // HD
	{
		CString str;
		m_FrqR.GetWindowText(str);

		m_Frq_C_E = m_Frq_C_R;
		m_FrqE.SetWindowText(str);
	}

	UpdateData(TRUE);
	*/
}

void CDlgTRC1752_MOD_PROG_CONF::OnKillfocusProgConfFrqHE()
{
	UpdateData(TRUE);

	if ( m_Frq_H_Emi > FRQHAUTE )
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_H_Emi = FRQHAUTE;

		if (c_ChoixSousMode.GetCurSel() == 2)		// HD
			m_Frq_H_Rec = FRQHAUTE;

		UpdateData(FALSE);
		c_Frq_H_Emi.SetFocus();
	}

	if ( m_Frq_H_Emi < FRQBASSE)
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_H_Emi = FRQBASSE;

		if (c_ChoixSousMode.GetCurSel() == 2)		// HD
			m_Frq_H_Rec = FRQBASSE;

		UpdateData(FALSE);
		c_Frq_H_Emi.SetFocus();
	}

	if (m_Frq_B_Emi > m_Frq_H_Emi)
	{
		m_Frq_H_Emi = 2425;
		m_Frq_B_Emi = 1575;

		if (c_ChoixSousMode.GetCurSel() == 2)		// HD
			m_Frq_H_Rec = 2425;

		c_Frq_H_Emi.SetFocus();
		UpdateData(FALSE);
	}
}

void CDlgTRC1752_MOD_PROG_CONF::OnKillfocusProgConfFrqHR()
{
	UpdateData(TRUE);

	if ( m_Frq_H_Rec > FRQHAUTE )
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_H_Rec = FRQHAUTE;

		if (c_ChoixSousMode.GetCurSel() == 2)		// HD
			m_Frq_H_Rec = FRQHAUTE;

		UpdateData(FALSE);
		c_Frq_H_Rec.SetFocus();
	}

	if ( m_Frq_H_Rec < FRQBASSE)
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_H_Rec = FRQBASSE;

		if (c_ChoixSousMode.GetCurSel() == 2)		// HD
			m_Frq_H_Rec = FRQBASSE;

		UpdateData(FALSE);
		c_Frq_H_Rec.SetFocus();
	}

	if (m_Frq_B_Rec > m_Frq_H_Rec)
	{
		m_Frq_H_Rec = 2425;
		m_Frq_B_Rec = 1575;

		if (c_ChoixSousMode.GetCurSel() == 2)		// HD
			m_Frq_H_Emi = 2425;

		c_Frq_H_Rec.SetFocus();
		UpdateData(FALSE);
	}
}

void CDlgTRC1752_MOD_PROG_CONF::OnKillfocusProgConfFrqBE()
{
	UpdateData(TRUE);

	if ( m_Frq_B_Emi > FRQHAUTE )
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_B_Emi = FRQHAUTE;

		if (c_ChoixSousMode.GetCurSel() == 2)		// HD
			m_Frq_B_Rec = FRQHAUTE;

		UpdateData(FALSE);
		c_Frq_B_Emi.SetFocus();
	}

	if ( m_Frq_B_Emi < FRQBASSE)
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_B_Emi = FRQBASSE;

		if (c_ChoixSousMode.GetCurSel() == 2)		// HD
			m_Frq_B_Rec = FRQBASSE;

		UpdateData(FALSE);
		c_Frq_B_Emi.SetFocus();
	}

	if (m_Frq_B_Emi > m_Frq_H_Emi)
	{
		AfxMessageBox("La fréquence Haute est toujours supérieure à la fréquence Basse !");

		m_Frq_B_Emi = 1575;
		c_Frq_B_Emi.SetWindowText(_T("1575"));
		UpdateData(TRUE);

		c_Frq_H_Emi.SetFocus();
	}
	else
	{
		//Vérification de l'indice de modulation
		CString Debit_Emi;

		int nIndex = c_ChoixDebitE.GetCurSel();
		c_ChoixDebitE.GetLBText(nIndex, Debit_Emi);  //Dans Debit_Emi le debit en CString

		if (!verifFskv(m_Frq_H_Emi, m_Frq_B_Emi, Debit_Emi))
		{
			m_Frq_H_Emi = 2425;
			m_Frq_B_Emi = 1575;
			c_Frq_H_Emi.SetFocus();
			UpdateData(FALSE);
		}
	}
}


void CDlgTRC1752_MOD_PROG_CONF::OnKillfocusProgConfFrqBR()
{
	UpdateData(TRUE);

	if ( m_Frq_B_Rec > FRQHAUTE )
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_B_Rec = FRQHAUTE;

		if (c_ChoixSousMode.GetCurSel() == 2)		// HD
			m_Frq_B_Emi = FRQHAUTE;

		UpdateData(FALSE);
		c_Frq_B_Rec.SetFocus();
	}

	if ( m_Frq_B_Rec < FRQBASSE)
	{
		AfxMessageBox("La fréquence \"Space\" [Fréquance Haute] : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.");
		m_Frq_B_Rec = FRQBASSE;

		if (c_ChoixSousMode.GetCurSel() == 2)		// HD
			m_Frq_B_Emi = FRQBASSE;

		UpdateData(FALSE);
		c_Frq_B_Rec.SetFocus();
	}

	if (m_Frq_B_Rec > m_Frq_H_Rec)
	{
		AfxMessageBox("La fréquence Haute est toujours supérieure à la fréquence Basse !");

		m_Frq_B_Rec = 1575;
		UpdateData(TRUE);

		c_Frq_H_Rec.SetFocus();
	}

}

//------------------------------------------
// Sélection du texte sur réception du focus
//------------------------------------------
void CDlgTRC1752_MOD_PROG_CONF::OnSetfocusFRQ_H_E()
{
	GetDlgItem(IDC_PROG_CONF_FRQ_H_E)->PostMessage(EM_SETSEL,0,-1);

}
void CDlgTRC1752_MOD_PROG_CONF::OnSetfocusFRQ_H_R()
{
	GetDlgItem(IDC_PROG_CONF_FRQ_H_R)->PostMessage(EM_SETSEL,0,-1);

}
void CDlgTRC1752_MOD_PROG_CONF::OnSetfocusFRQ_B_E()
{
	GetDlgItem(IDC_PROG_CONF_FRQ_B_E)->PostMessage(EM_SETSEL,0,-1);

}
void CDlgTRC1752_MOD_PROG_CONF::OnSetfocusFRQ_B_R()
{
	GetDlgItem(IDC_PROG_CONF_FRQ_B_R)->PostMessage(EM_SETSEL,0,-1);

}
//-----------------------------------------------------------------

void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfShiftE()
{
	/*La combinaison 600 Hz ± 425 Hz n’est pas autorisée car sa fréquence basse sortirait de la
	bande passante des équipements radios.
	*/
	if (c_Shift_E.GetCurSel() == 4 && c_SP_E.GetCurSel() == 0)
	{
		AfxMessageBox("La combinaison 600 Hz ± 425 Hz n’est pas autorisée !");
		c_Shift_E.SetCurSel(3);
	}

	/*
	En mode Half Duplex, lorsque l’utilisateur programme un paramètre émission (fréquence
	haute, fréquence basse), les paramètres de la voie réception sont forcés aux mêmes valeurs.
	*/
	if (c_ChoixSousMode.GetCurSel() == 2)
	{
		c_Shift_R.SetCurSel(c_Shift_E.GetCurSel());
	}
}

void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfSpE()
{
	/*La combinaison 600 Hz ± 425 Hz n’est pas autorisée car sa fréquence basse sortirait de la
	bande passante des équipements radios.
	*/
	if (c_Shift_E.GetCurSel() == 4 && c_SP_E.GetCurSel() == 0)
	{
		AfxMessageBox("La combinaison 600 Hz ± 425 Hz n’est pas autorisée !");
		c_SP_E.SetCurSel(5);
		return;
	}

	/*
	En mode Half Duplex, lorsque l’utilisateur programme un paramètre émission (fréquence
	haute, fréquence basse), les paramètres de la voie réception sont forcés aux mêmes valeurs.
	*/
	if (c_ChoixSousMode.GetCurSel() == 2)
	{
		c_SP_R.SetCurSel(c_SP_E.GetCurSel());
	}


}

void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfShiftR()
{
	/*La combinaison 600 Hz ± 425 Hz n’est pas autorisée car sa fréquence basse sortirait de la
	bande passante des équipements radios.
	*/
	if (c_Shift_R.GetCurSel() == 4 && c_SP_R.GetCurSel() == 0)
	{
		AfxMessageBox("La combinaison 600 Hz ± 425 Hz n’est pas autorisée !");
		c_Shift_R.SetCurSel(3);
	}
}

void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfSpR()
{
	/*La combinaison 600 Hz ± 425 Hz n’est pas autorisée car sa fréquence basse sortirait de la
	bande passante des équipements radios.
	*/
	if (c_Shift_R.GetCurSel() == 4 && c_SP_R.GetCurSel() == 0)
	{
		AfxMessageBox("La combinaison 600 Hz ± 425 Hz n’est pas autorisée !");
		c_SP_R.SetCurSel(5);
		return;
	}

}

//---------------------------------------
// Vérification de l'indice de modulation
//---------------------------------------
bool CDlgTRC1752_MOD_PROG_CONF::verifFskv(int Fh, int Fb, CString Debit)
{
	char	*stopstring;
	int		debitEmi;
	float	m;
	bool	res = TRUE;

	debitEmi = strtod(Debit, &stopstring);

	m = (((float)Fh-(float)Fb)/(float)debitEmi);

	if ( m < 0.6f)
	{
		res = FALSE;
		AfxMessageBox("Il est recommandé de choisir les fréquences hautes Fh et basses Fb pour obtenir un indice de modulation m sup 0,66 (m= (Fh-Fb)/D) où D est le débit des données à transmettre.");
	}

	return res;
}

void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgConfChDiv()
{
	/*
	Il est supposé que la réception sans diversité est effectuée sur la voie A1 avec la configuration
	CA définie comme suit :
	CA	4285		E : 300C - L
	- -  T : RE		R : 300C - L

	Pour passer en réception avec diversité l’opérateur doit :
		1 - Désactiver les voies A1 et A2 (si besoin),
		2 - Connecter le deuxième récepteur sur l’entrée BF2 (A2) du modem et programmer sa fréquence sur
		l’une des fréquences émises par la même station d’émission que celle reçue précédemment.
		Modification du niveau de réception de la voie esclave.
		3 - Modifier la configuration CA du modem pour obtenir :

	CA	4285		E : 300C - L
	DI  T : FD		R : 300C - L

		4 - Réactiver la voie A1 sans rien changer aux autres paramètres.

	Le modem fonctionne alors en réception avec diversité. Les écrans du mode opérationnel des
	deux voies sont identiques à ceux d’une réception sans diversité. Ils indiquent le
	niveau, la qualité, et le décalage de fréquence sur chacune des deux entrées BF du modem.
	*/

}

void CDlgTRC1752_MOD_PROG_CONF::OnChangeProgConfFrqHE()
{
	/*
	En mode Half Duplex, lorsque l’utilisateur programme un paramètre émission (fréquence
	haute, fréquence basse), les paramètres de la voie réception sont forcés aux mêmes valeurs.
	Si l’utilisateur désire choisir des valeurs de paramètres réception, différentes de celles de
	l’émission, il peut les programmer en agissant directement sur les paramètres de la voie réception.
	*/

	if ((m_ChoixSousMode == 2 ) && eqp->Actif())
	{
		CString str;
		CString resultat;
		char *stopstring;
		int cdp;

		c_Frq_H_Emi.GetWindowText(str);
		cdp = strtod(str, &stopstring);

		resultat.Format(_T("%.0f"), cdp*1.0f);

		c_Frq_H_Rec.SetWindowText(resultat);

		m_Frq_H_Rec = m_Frq_H_Emi;
		c_Frq_H_Emi.PostMessage(WM_KEYDOWN,VK_END,0);
	}

}

void CDlgTRC1752_MOD_PROG_CONF::OnChangeProgConfFrqBE()
{
	/*
	En mode Half Duplex, lorsque l’utilisateur programme un paramètre émission (fréquence
	haute, fréquence basse), les paramètres de la voie réception sont forcés aux mêmes valeurs.
	Si l’utilisateur désire choisir des valeurs de paramètres réception, différentes de celles de
	l’émission, il peut les programmer en agissant directement sur les paramètres de la voie réception.
	*/

	if ((m_ChoixSousMode == 2 ) && eqp->Actif())
	{
		CString str;
		CString resultat;
		char *stopstring;
		int cdp;

		c_Frq_B_Emi.GetWindowText(str);
		cdp = strtod(str, &stopstring);

		resultat.Format(_T("%.0f"), cdp*1.0f);

		c_Frq_B_Rec.SetWindowText(resultat);

		m_Frq_B_Rec = m_Frq_B_Emi;
		c_Frq_B_Emi.PostMessage(WM_KEYDOWN,VK_END,0);
	}
}


void CDlgTRC1752_MOD_PROG_CONF::OnChangeProgConfFrqHR()
{
	/*
	En mode Half Duplex, lorsque l’utilisateur programme un paramètre émission (fréquence
	haute, fréquence basse), les paramètres de la voie réception sont forcés aux mêmes valeurs.
	Si l’utilisateur désire choisir des valeurs de paramètres réception, différentes de celles de
	l’émission, il peut les programmer en agissant directement sur les paramètres de la voie réception.
	*/

	if ((m_ChoixSousMode == 2 ) && eqp->Actif())
	{
		CString str;
		CString resultat;
		char *stopstring;
		int cdp;

		c_Frq_H_Rec.GetWindowText(str);
		cdp = strtod(str, &stopstring);

		resultat.Format(_T("%.0f"), cdp*1.0f);

		c_Frq_H_Emi.SetWindowText(resultat);

		m_Frq_H_Emi = m_Frq_H_Rec;
		c_Frq_H_Rec.PostMessage(WM_KEYDOWN,VK_END,0);

	}

}

void CDlgTRC1752_MOD_PROG_CONF::OnChangeProgConfFrqBR()
{
	/*
	En mode Half Duplex, lorsque l’utilisateur programme un paramètre émission (fréquence
	haute, fréquence basse), les paramètres de la voie réception sont forcés aux mêmes valeurs.
	Si l’utilisateur désire choisir des valeurs de paramètres réception, différentes de celles de
	l’émission, il peut les programmer en agissant directement sur les paramètres de la voie réception.
	*/

	if ((m_ChoixSousMode == 2 ) && eqp->Actif())
	{
		CString str;
		CString resultat;
		char *stopstring;
		int cdp;

		c_Frq_B_Rec.GetWindowText(str);
		cdp = strtod(str, &stopstring);

		resultat.Format(_T("%.0f"), cdp*1.0f);

		c_Frq_B_Emi.SetWindowText(resultat);

		m_Frq_B_Emi = m_Frq_B_Rec;
		c_Frq_B_Rec.PostMessage(WM_KEYDOWN,VK_END,0);
	}

}

//*************************************************
// Affiche ou cache le fenêtre diversité - 2ème Cas
//*************************************************
void CDlgTRC1752_MOD_PROG_CONF::AfficheCache2cas(bool act)
{
	GetDlgItem(IDC_MOD_PROG_DIV)->ShowWindow(act);
	GetDlgItem(IDC_STATIC_DIV_INFO)->ShowWindow(act);
	GetDlgItem(IDC_PROG_DIV_SORTIE_DATA)->ShowWindow(act);
	GetDlgItem(IDC_PROG_DIV_SOUS_MODE)->ShowWindow(act);
	GetDlgItem(IDC_STATIC_DIV_E)->ShowWindow(!c_ChoixDiv.GetCurSel());
	GetDlgItem(IDC_PROG_DIV_CH_DEBIT_E)->ShowWindow(act);
	GetDlgItem(IDC_PROG_DIV_CH_ENT_E)->ShowWindow(act);
	GetDlgItem(IDC_PROG_CONF_FRQ_E_DIV)->ShowWindow(act);
	GetDlgItem(IDC_PROG_CONF_FRQ_E_DIV_SPIN)->ShowWindow(act);
}



void CDlgTRC1752_MOD_PROG_CONF::OnOutofmemoryProgConfFrqEDivSpin(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_CONF::OnDeltaposProgConfFrqEDivSpin(NMHDR* pNMHDR, LRESULT* pResult)
{

	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	/*
	La fréquence centrale utilisée dans le sens émission réglable de 900 Hz à 2400 Hz par pas de
	100 Hz,
	*/
	if (pNMUpDown->iDelta > 0)  m_Frq_Div_C_E += FRQCPAS;
		else m_Frq_Div_C_E -= FRQCPAS;


	if ( m_Frq_Div_C_E > FRQCMAX )
	{
		AfxMessageBox("La fréquence centrale émission réglable de 900 Hz à 2400 Hz");
		m_Frq_Div_C_E = FRQCMAX;
	}

	if ( m_Frq_Div_C_E < FRQCMIN)
	{
		AfxMessageBox("La fréquence centrale émission réglable de 900 Hz à 2400 Hz");
		m_Frq_Div_C_E = FRQCMIN;
	}

	UpdateData(FALSE);

	*pResult = 0;
}

//**************************************
// Affichage apres modification du canal
//**************************************
void CDlgTRC1752_MOD_PROG_CONF::ModificationCanal()
{
	ActivElemConsult();
	c_ChoixCanal.EnableWindow(TRUE);

	CString str;
	int t_shiftE, t_shiftR;

	m_ChoixCanal = c_ChoixCanal.GetCurSel();

	TChannelConfiguration conf_courante;

	c_ChoixCanal.GetWindowText(str);

	if (str == "MC")
		conf_courante = eqp->GetChannelConfiguration(mc_value);
	else
		conf_courante = eqp->GetChannelConfiguration(CHANNELS_CONFIGURATION[c_ChoixCanal.GetCurSel()]);

	//*****
	// Mode
	//*****
	if (conf_courante.waveform == "BFSK" )			//Vers affichage FSKV
		c_ChoixMode.SetCurSel(3);
	else if (conf_courante.waveform == "TRANSP")	//Vers affichage TRANSPARENT
		c_ChoixMode.SetCurSel(5);
	else if (conf_courante.waveform != "")
		c_ChoixMode.SelectString(0, conf_courante.waveform.c_str());
	else
		c_ChoixMode.SetCurSel(6);					//Repos



	//*********************************************
	// Mise à jour suivant le mode du nouveau Canal
	//*********************************************
	OnSelchangeProgConfChMode();


	//**********
	// Direction
	//**********
	if (conf_courante.direction == "RX")
		c_ChoixSousMode.SetCurSel(0);
	else if(conf_courante.direction == "TX")
		c_ChoixSousMode.SetCurSel(1);
	else
		c_ChoixSousMode.SelectString(0, conf_courante.direction.c_str());

	//**************************************************
	// Mise à jour suivant le sous-mode du nouveau Canal
	//**************************************************
	OnSelchangeProgConfChSMode();

	//*********************************************
	// Mise à jour suivant le mode du nouveau Canal
	//*********************************************


	//********************
	// DébitCodageEmission
	//********************
	if (conf_courante.af_transmission_baudrate<1000)
	{
		str.Format(_T("%03d"), conf_courante.af_transmission_baudrate);
	}else
	{
		str.Format(_T("%04d"), conf_courante.af_transmission_baudrate);
	}

	if (conf_courante.af_transmission_baudrate<100)
		str.Format(_T("%02d"), conf_courante.af_transmission_baudrate);

	// Fabrication des débits du type 2400C
	if (c_ChoixMode.GetCurSel() == 0 || c_ChoixMode.GetCurSel() == 1 || c_ChoixMode.GetCurSel() == 4)
		str.Insert(str.GetLength(),conf_courante.af_transmission_codingtype.substr(0,1).c_str());

	c_ChoixDebitE.SelectString(0, (LPCTSTR)str);

	//**********************
	// EntrelacementEmission
	//**********************
	c_ChoixEntE.SetCurSel(0);
	if (conf_courante.af_transmission_interleaving == "COURT")
		c_ChoixEntE.SetCurSel(1);
	if (conf_courante.af_transmission_interleaving == "LONG")
		c_ChoixEntE.SetCurSel(2);

	//*********************
	// DébitCodageReception
	//*********************
	if (conf_courante.af_reception_baudrate<1000)
	{
		str.Format(_T("%03d"), conf_courante.af_reception_baudrate);
	}else
	{
		str.Format(_T("%04d"), conf_courante.af_reception_baudrate);
	}

	if (conf_courante.af_reception_baudrate<100)
		str.Format(_T("%02d"), conf_courante.af_reception_baudrate);

	// Fabrication des débits du type 2400C
	if (c_ChoixMode.GetCurSel() == 0 || c_ChoixMode.GetCurSel() == 1 || c_ChoixMode.GetCurSel() == 4)
		str.Insert(str.GetLength(),conf_courante.af_reception_codingtype.substr(0,1).c_str());

	c_ChoixDebitR.SelectString(0, (LPCTSTR)str);

	//**********************
	//EntrelacementRéception
	//**********************
	if (conf_courante.af_reception_interleaving == "SANS")
		c_ChoixEntR.SetCurSel(0);	//Sans
	if (conf_courante.af_reception_interleaving == "COURT")
		c_ChoixEntR.SetCurSel(1);
	if (conf_courante.af_reception_interleaving == "LONG")
		c_ChoixEntR.SetCurSel(2);

	//**********
	// Diversité
	//**********
	c_ChoixDiv.SetCurSel(1);
	AfficheCache2cas(FALSE);
	if (conf_courante.diversity == "AVEC")
		c_ChoixDiv.SetCurSel(0);

	//if (c_ChoixDiv.GetCurSel() == 0 && c_ChoixSousMode.GetCurSel() == 0)
	if (conf_courante.diversity == "AVEC" &&  conf_courante.direction == "RX" && conf_courante.waveform != "REPOS" )
	{
		AfficheCache2cas(TRUE);

		if (conf_courante.waveform == "4285")
		{
			GetDlgItem(IDC_PROG_CONF_FRQ_E_DIV)->ShowWindow(FALSE);
			GetDlgItem(IDC_PROG_CONF_FRQ_E_DIV_SPIN)->ShowWindow(FALSE);
		}

		// Sortie Data
		c_DivSortieData.SetCurSel(0);
		if (conf_courante.use_data == "AVEC")
			c_DivSortieData.SetCurSel(1);

		// Sous-Mode
		c_DivSousMode.SetCurSel(1);
		if (conf_courante.slave_direction == "RX")
			c_DivSousMode.SetCurSel(0);

		//Débit
		if (conf_courante.slave_baudrate<1000)
		{
			str.Format(_T("%03d"), conf_courante.slave_baudrate);
		}else
		{
			str.Format(_T("%04d"), conf_courante.slave_baudrate);
		}

		if (conf_courante.slave_baudrate<100)
			str.Format(_T("%02d"), conf_courante.slave_baudrate);

		str.Insert(str.GetLength(),conf_courante.slave_codingtype.substr(0,1).c_str());

		c_DivDebitEmi.SelectString(0, (LPCTSTR)str);

		// Entrelacement
		if (conf_courante.slave_interleaving == "SANS")
			c_DivEntrelaceurEmi.SetCurSel(0);
		if (conf_courante.slave_interleaving == "COURT")
			c_DivEntrelaceurEmi.SetCurSel(1);
		if (conf_courante.slave_interleaving == "LONG")
			c_DivEntrelaceurEmi.SetCurSel(2);

		//Fréquence centrale en 4529
		if(conf_courante.waveform == "4529")
			m_Frq_Div_C_E = conf_courante.slave_carrier_frequency;

	}

	UpdateData(TRUE);

	//*************************************************************************
	//Fréquence centrale Emission/Réception en 4529
	//**************************************************************************
	if (conf_courante.waveform == "4529")
	{
		m_Frq_C_E = conf_courante.transmission_carrier_frequency;
		m_Frq_C_R = conf_courante.reception_carrier_frequency;
	}


	//Fréquence Haute/Basse Emission/Réception en FSKV et FSKP (BFSK)
	m_Frq_H_Emi = conf_courante.transmission_space_frequency;
	m_Frq_B_Emi = conf_courante.transmission_mark_frequency;
	m_Frq_H_Rec = conf_courante.reception_space_frequency;
	m_Frq_B_Rec = conf_courante.reception_mark_frequency;

	UpdateData(FALSE);

	//****************************
	// Traitement du FSKP en local
	//****************************
	if (conf_courante.waveform == "FSKP")
	{
		t_shiftE = conf_courante.transmission_space_frequency - conf_courante.transmission_carrier_frequency;
		t_shiftR = conf_courante.reception_space_frequency - conf_courante.reception_carrier_frequency;

		// Traitement de la fréquence centrale émission
		str.Format(_T("%04d"), conf_courante.transmission_carrier_frequency);
		if ( conf_courante.transmission_carrier_frequency <1000 )
			str.Format(_T("%03d"), conf_courante.transmission_carrier_frequency);

		c_SP_E.SelectString(0, (LPCTSTR)str);

		// Traitement de la fréquence centrale réception
		str.Format(_T("%04d"), conf_courante.reception_carrier_frequency);
		if ( conf_courante.reception_carrier_frequency <1000 )
			str.Format(_T("%03d"), conf_courante.reception_carrier_frequency);

		c_SP_R.SelectString(0, (LPCTSTR)str);

		// Traitement du saut de shift émission
		str.Format(_T("+/-%03d"), t_shiftE);
		if (t_shiftE < 100)
			str.Format(_T("+/-%02d"), t_shiftE);

		c_Shift_E.SelectString(0, (LPCTSTR)str);

		if (t_shiftE == 42)
			c_Shift_E.SetCurSel(0);

		// Traitement du saut de shift réception
		str.Format(_T("+/-%03d"), t_shiftR);
		if (t_shiftR < 100)
			str.Format(_T("+/-%02d"), t_shiftR);

		c_Shift_R.SelectString(0, (LPCTSTR)str);

		// Cas du +/-42.5
		if (t_shiftR == 42)
			c_Shift_R.SetCurSel(0);

		UpdateData(TRUE);
	}
}

// Mise à zero de la sélection du canal
void CDlgTRC1752_MOD_PROG_CONF::razChoixCanal()
{
	c_ChoixCanal.SetCurSel(0);
	ModificationCanal();
}

// **********************************************************
// Gestion du timer
// **********************************************************
void CDlgTRC1752_MOD_PROG_CONF::marcheTimer()
{
	if (eqp->GetMode() == false) return;		//il faut etre en distant

	m_timerConf = SetTimer(1,2000,NULL);		// Mise en marche du Timer - 2s
}

void CDlgTRC1752_MOD_PROG_CONF::arretTimer()
{
	KillTimer(m_timerConf);						// Arrêt du Timer
}

void CDlgTRC1752_MOD_PROG_CONF::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	ModificationCanal();						// Affichage des paramètres
}

//*********************************
// Consultation de la configuration
//*********************************
void CDlgTRC1752_MOD_PROG_CONF::Consultation(string conf)
{
	// Mise à jour de la configuration en cours
	if (conf == "A1" || conf == "A2" || conf == "B1" || conf == "B2")
	{
		enleveMC();
		c_ChoixCanal.AddString("MC");
		mc_value = conf;
		conf = "MC";
	} else enleveMC();

	c_ChoixCanal.SelectString(0, conf.c_str());



	// Affichage des paramètres avant celui du OnTimer
	ModificationCanal();

	// FFT ADEL_97192
	//DesactivElemConsult();
	//c_ChoixCanal.EnableWindow(FALSE);

	// Mise en marche du timer
	marcheTimer();
}

//*********************************
// Modification de la configuration
//*********************************
void CDlgTRC1752_MOD_PROG_CONF::Modification(string conf)
{
	// Mise à jour de la configuration en cours
	if (conf == "A1" || conf == "A2" || conf == "B1" || conf == "B2")
	{
		enleveMC();
		c_ChoixCanal.AddString("MC");
		mc_value = conf;
		conf = "MC";
	} else enleveMC();

	c_ChoixCanal.SelectString(0, conf.c_str());

	// Affichage des paramètres avant celui du OnTimer
	ModificationCanal();

	// Mise en marche du timer
	marcheTimer();
}

//******************************************
// Enleve MC s'il est present dans la liste
//******************************************
void CDlgTRC1752_MOD_PROG_CONF::enleveMC()
{
	int res = c_ChoixCanal.FindString(0,"MC");

	if (res != LB_ERR)
		c_ChoixCanal.DeleteString( res );
}

// Test si la configuration est utilisée par un canal actif
bool CDlgTRC1752_MOD_PROG_CONF::TestCanal()
{
	bool res = TRUE;
	CString str;
	c_ChoixCanal.GetWindowText(str);

	if ( (eqp->GetChannelAssociatedAfConfiguration("A1") == (LPCTSTR)str && eqp->GetChannelState("A1") == "ACTIVE")
		|| (eqp->GetChannelAssociatedAfConfiguration("A2") == (LPCTSTR)str && eqp->GetChannelState("A2") == "ACTIVE")
		 || (eqp->GetChannelAssociatedAfConfiguration("B1") == (LPCTSTR)str && eqp->GetChannelState("B1") == "ACTIVE")
		  || (eqp->GetChannelAssociatedAfConfiguration("B2") == (LPCTSTR)str && eqp->GetChannelState("B2") == "ACTIVE"))
	{
		AfxMessageBox("Changement impossible de la configuration.");
		UpdateData(FALSE);
		res = FALSE;
	}

	return res;
}


void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgDivSortieData()
{
}

void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgDivSousMode()
{
}

void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgDivChDebitE()
{
}

void CDlgTRC1752_MOD_PROG_CONF::OnSelchangeProgDivChEntE()
{
}

//*********************************
//	Consultation des configurations
//*********************************
void CDlgTRC1752_MOD_PROG_CONF::ActivElemConsult()
{
c_ChoixMode.EnableWindow(TRUE);
c_ChoixDebitE.EnableWindow(TRUE);
c_ChoixDebitR.EnableWindow(TRUE);
c_ChoixEntE.EnableWindow(TRUE);
c_ChoixEntR.EnableWindow(TRUE);
c_ChoixDiv.EnableWindow(TRUE);
c_ChoixSousMode.EnableWindow(TRUE);
c_Frq_Div_C_E.EnableWindow(TRUE);
c_DivSousMode.EnableWindow(TRUE);
c_DivEntrelaceurEmi.EnableWindow(TRUE);
c_DivDebitEmi.EnableWindow(TRUE);
c_DivSortieData.EnableWindow(TRUE);
c_Frq_H_Rec.EnableWindow(TRUE);
c_Frq_H_Emi.EnableWindow(TRUE);
c_Frq_B_Emi.EnableWindow(TRUE);
c_Frq_B_Rec.EnableWindow(TRUE);
c_Shift_R.EnableWindow(TRUE);
c_Shift_E.EnableWindow(TRUE);
c_SP_E.EnableWindow(TRUE);
c_SP_R.EnableWindow(TRUE);
m_FrqE.EnableWindow(TRUE);
m_FrqR.EnableWindow(TRUE);
}

void CDlgTRC1752_MOD_PROG_CONF::DesactivElemConsult()
{
c_ChoixMode.EnableWindow(FALSE);
c_ChoixDebitE.EnableWindow(FALSE);
c_ChoixDebitR.EnableWindow(FALSE);
c_ChoixEntE.EnableWindow(FALSE);
c_ChoixEntR.EnableWindow(FALSE);
c_ChoixDiv.EnableWindow(FALSE);
c_ChoixSousMode.EnableWindow(FALSE);
c_Frq_Div_C_E.EnableWindow(FALSE);
c_DivSousMode.EnableWindow(FALSE);
c_DivEntrelaceurEmi.EnableWindow(FALSE);
c_DivDebitEmi.EnableWindow(FALSE);
c_DivSortieData.EnableWindow(FALSE);
c_Frq_H_Rec.EnableWindow(FALSE);
c_Frq_H_Emi.EnableWindow(FALSE);
c_Frq_B_Emi.EnableWindow(FALSE);
c_Frq_B_Rec.EnableWindow(FALSE);
c_Shift_R.EnableWindow(FALSE);
c_Shift_E.EnableWindow(FALSE);
c_SP_E.EnableWindow(FALSE);
c_SP_R.EnableWindow(FALSE);
m_FrqE.EnableWindow(FALSE);
m_FrqR.EnableWindow(FALSE);
}
