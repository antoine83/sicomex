// DlgTRC1752_MOD_PROG_ALE_SYS.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_PROG_ALE_SYS.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_SYS dialog

/*SYSTEMPARAM = paramètres système de la fonction ALE*/


CDlgTRC1752_MOD_PROG_ALE_SYS::CDlgTRC1752_MOD_PROG_ALE_SYS(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_PROG_ALE_SYS::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_PROG_ALE_SYS)
	m_AleSysCanal = 0;
	m_AleSysFscanning = 0;
	m_AleSysIat = 3;
	m_AleSysPtt = 0;
	m_AleSysSounding = 0;
	m_AleSysSR = 0;
	m_AleSysTT = 200;
	m_AleSysTwaMa = 120;
	m_AleSysTwaMm = 999;
	m_AleSysTwt = 3;
	//}}AFX_DATA_INIT

	this->eqp = equip;
}


void CDlgTRC1752_MOD_PROG_ALE_SYS::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_PROG_ALE_SYS)
	DDX_Control(pDX, IDC_PROG_ALE_SYS_TT, c_AleSysTT);
	DDX_Control(pDX, IDC_PROG_ALE_SYS_TWT, c_AleSysTwt);
	DDX_Control(pDX, IDC_PROG_ALE_SYS_TWA_MM, c_AleSysTwaMm);
	DDX_Control(pDX, IDC_PROG_ALE_SYS_TWA_MA, c_AleSysTwaMa);
	DDX_Control(pDX, IDC_SPIN_TWT, s_AleSysTwt);
	DDX_Control(pDX, IDC_SPIN_TWA_MM, s_AleSysTwaMm);
	DDX_Control(pDX, IDC_SPIN_TWA_MA, s_AleSysTwaMA);
	DDX_Control(pDX, IDC_SPIN_TT, s_AleSysTT);
	DDX_Control(pDX, IDC_PROG_ALE_SYS_SR, m_ChAleSysSR);
	DDX_Control(pDX, IDC_PROG_ALE_SYS_SOUND, m_ChAleSysSounding);
	DDX_Control(pDX, IDC_PROG_ALE_SYS_PTT, m_ChAleSysPtt);
	DDX_Control(pDX, IDC_PROG_ALE_SYS_IAT, m_ChAleSysIat);
	DDX_Control(pDX, IDC_PROG_ALE_SYS_FS, m_ChAleSysFscanning);
	DDX_Control(pDX, IDC_PROG_ALE_SYS_CANAL, m_ChAleSysCanal);
	DDX_CBIndex(pDX, IDC_PROG_ALE_SYS_CANAL, m_AleSysCanal);
	DDX_CBIndex(pDX, IDC_PROG_ALE_SYS_FS, m_AleSysFscanning);
	DDX_CBIndex(pDX, IDC_PROG_ALE_SYS_IAT, m_AleSysIat);
	DDX_CBIndex(pDX, IDC_PROG_ALE_SYS_PTT, m_AleSysPtt);
	DDX_CBIndex(pDX, IDC_PROG_ALE_SYS_SOUND, m_AleSysSounding);
	DDX_CBIndex(pDX, IDC_PROG_ALE_SYS_SR, m_AleSysSR);
	DDX_Text(pDX, IDC_PROG_ALE_SYS_TT, m_AleSysTT);
	DDV_MinMaxInt(pDX, m_AleSysTT, 0, 9999);
	DDX_Text(pDX, IDC_PROG_ALE_SYS_TWA_MA, m_AleSysTwaMa);
	DDV_MinMaxInt(pDX, m_AleSysTwaMa, 0, 999);
	DDX_Text(pDX, IDC_PROG_ALE_SYS_TWA_MM, m_AleSysTwaMm);
	DDV_MinMaxInt(pDX, m_AleSysTwaMm, 0, 999);
	DDX_Text(pDX, IDC_PROG_ALE_SYS_TWT, m_AleSysTwt);
	DDV_MinMaxInt(pDX, m_AleSysTwt, 0, 99);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_PROG_ALE_SYS, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_PROG_ALE_SYS)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SPIN_TWA_MA, OnOutofmemorySpinTwaMa)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SPIN_TWT, OnOutofmemorySpinTwt)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SPIN_TWA_MM, OnOutofmemorySpinTwaMm)
	ON_NOTIFY(NM_OUTOFMEMORY, IDC_SPIN_TT, OnOutofmemorySpinTt)
	ON_WM_LBUTTONDOWN()
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TWA_MA, OnDeltaposSpinTwaMa)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TWT, OnDeltaposSpinTwt)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TWA_MM, OnDeltaposSpinTwaMm)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_TT, OnDeltaposSpinTt)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_PROG_ALE_SYS_CANAL, OnSelchangeProgAleSysCanal)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_SYS message handlers

void CDlgTRC1752_MOD_PROG_ALE_SYS::OnOutofmemorySpinTwaMa(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_ALE_SYS::OnOutofmemorySpinTwt(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_ALE_SYS::OnOutofmemorySpinTwaMm(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_ALE_SYS::OnOutofmemorySpinTt(NMHDR* pNMHDR, LRESULT* pResult)
{
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

BOOL CDlgTRC1752_MOD_PROG_ALE_SYS::OnInitDialog()
{
	CDialog::OnInitDialog();

	// Initialisation de bornes
	s_AleSysTT.SetRange(0, 9999);
	s_AleSysTwaMA.SetRange(0, 999);
	s_AleSysTwaMm.SetRange(0, 999);
	s_AleSysTwt.SetRange(0, 99);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTRC1752_MOD_PROG_ALE_SYS::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: Add your message handler code here and/or call default

	CDialog::OnLButtonDown(nFlags, point);

}

void CDlgTRC1752_MOD_PROG_ALE_SYS::OnDeltaposSpinTwaMa(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_ALE_SYS::OnDeltaposSpinTwt(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_ALE_SYS::OnDeltaposSpinTwaMm(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

void CDlgTRC1752_MOD_PROG_ALE_SYS::OnDeltaposSpinTt(NMHDR* pNMHDR, LRESULT* pResult)
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	// TODO: Add your control notification handler code here

	*pResult = 0;
}

//***************************
// Affichage des informations
//***************************
void CDlgTRC1752_MOD_PROG_ALE_SYS::AffichageInfos()
{
	CString str, str_sys;

	m_ChAleSysCanal.GetLBText(m_ChAleSysCanal.GetCurSel(), str_sys);

	TAleParameter conf_courante = eqp->GetAleParameter((char *)LPCTSTR(str_sys));

	// scanrate - FS
	str.Format(_T("%01d"), conf_courante.scanrate);
	m_ChAleSysFscanning.SelectString(0, str);

	// aging_time - IAT
	str = conf_courante.aging_time.substr(1,1).c_str();
	m_ChAleSysIat.SelectString(0, str);

	// respond - Silence
	m_ChAleSysSR.SetCurSel(0);			//Pas de silence radio par défaut
	if ( conf_courante.respond == "ON" )
		m_ChAleSysSR.SetCurSel(1);

	// automatic_sounding - Sound-auto
	m_ChAleSysSounding.SetCurSel(0);			//Pas de sounding par défaut
	if ( conf_courante.automatic_sounding == "ON" )
		m_ChAleSysSounding.SetCurSel(1);

	// ptt_gestion - PTT
	m_ChAleSysPtt.SetCurSel(0);			//Cable (wire) par défaut
	if ( conf_courante.ptt_gestion == "SERIAL" )
		m_ChAleSysPtt.SetCurSel(1);

	// twa_manual - TWA_MM
	str.Format(_T("%03d"), conf_courante.twa_manual);
	c_AleSysTwaMm.SetWindowText(str);

	// twa_automatic - TWA_MA
	str.Format(_T("%03d"), conf_courante.twa_automatic);
	c_AleSysTwaMa.SetWindowText(str);

	// twt - TWT
	str.Format(_T("%04d"), conf_courante.twt);
	c_AleSysTwt.SetWindowText(str);

	// tunetime_local - TT
	str.Format(_T("%04d"), conf_courante.tunetime_local);
	c_AleSysTT.SetWindowText(str);

	UpdateData(TRUE);

}

//*************************************************
// Validation des choix de l'opérateur - Touche VAL
//*************************************************
void CDlgTRC1752_MOD_PROG_ALE_SYS::Valide()
{
	// Changement impossible quand l'équipement est en Distant
	if (eqp->GetMode() == TRUE)
	{
		AfxMessageBox("Changement impossible quand l'équipement est en Distant");
		UpdateData(FALSE);
		return;
	}

	UpdateData(TRUE);

	CString str, str_sys;
	int tmpIat;

	m_ChAleSysCanal.GetLBText(m_ChAleSysCanal.GetCurSel(), str_sys);

	TAleParameter conf_courante = eqp->GetAleParameter((char *)LPCTSTR(str_sys));

	// scanrate
	m_ChAleSysFscanning.GetLBText(m_ChAleSysFscanning.GetCurSel(), str);
	conf_courante.scanrate = atoi(str);

	// aging_time - IAT
	conf_courante.aging_time = "04.0";
	m_ChAleSysIat.GetLBText(m_ChAleSysIat.GetCurSel(), str);
	tmpIat = atoi(str);
	str.Format(_T("0%01d.0"), tmpIat);
	conf_courante.aging_time = str;

	// respond
	conf_courante.respond = "ON";
	if (m_ChAleSysSR.GetCurSel() == 0)
		conf_courante.respond = "OFF";

	// automatic_sounding
	conf_courante.automatic_sounding = "OFF";
	if (m_ChAleSysSounding.GetCurSel() == 1)
		conf_courante.automatic_sounding = "ON";

	// ptt_gestion
	conf_courante.ptt_gestion = "WIRE";
	if ( m_ChAleSysPtt.GetCurSel() == 1)
		conf_courante.ptt_gestion = "SERIAL";

	// twa_automatic
	conf_courante.twa_automatic = m_AleSysTwaMa;

	// twa_manual
	conf_courante.twa_manual = m_AleSysTwaMm;

	// twt
	conf_courante.twt = m_AleSysTwt;

	// tunetime_local
	conf_courante.tunetime_local = m_AleSysTT;

	//********************************
	// Mise en place dans la structure
	//********************************
	eqp->SetAleParameter((char *)LPCTSTR(str_sys), conf_courante);

	UpdateData(FALSE);
}

// **********************************************************
// Gestion du timer
// **********************************************************
void CDlgTRC1752_MOD_PROG_ALE_SYS::marcheTimer()
{
	m_ChAleSysCanal.ResetContent();
	m_ChAleSysCanal.AddString("A1");

	if (eqp->GetQuadrivoie() == TRUE)	//Quatri-Voies
	{
		m_ChAleSysCanal.AddString("B1");
	}
	m_ChAleSysCanal.SetCurSel(0);

	if (eqp->GetMode() == false) return;		//il faut etre en distant

	m_timerAleSys = SetTimer(1,2000,NULL);
}

void CDlgTRC1752_MOD_PROG_ALE_SYS::arretTimer()
{
	KillTimer(m_timerAleSys);
}


void CDlgTRC1752_MOD_PROG_ALE_SYS::OnTimer(UINT nIDEvent)
{
	CDialog::OnTimer(nIDEvent);

	AffichageInfos();
}

//*******************
// Changement de voie
//*******************
void CDlgTRC1752_MOD_PROG_ALE_SYS::OnSelchangeProgAleSysCanal()
{
	AffichageInfos();
}

// Initialisation du Canal
void CDlgTRC1752_MOD_PROG_ALE_SYS::RazCanal()
{
	m_ChAleSysCanal.SetCurSel(0);
	AffichageInfos();

}
