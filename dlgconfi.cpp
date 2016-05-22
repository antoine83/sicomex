/* **************************************************************************
FICHIER :	DlgConfi.CPP		 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgConfig
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "DlgConfi.h"
#include "DlgAide.h"

#include "divers\Div_tmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern	CParamSimu 	*glob_paramsimu;
extern 	char glob_HELP_CONFIG[];

CDlgConfig::CDlgConfig(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgConfig::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgConfig)
	m_num_port = 1;
	m_nb_liaison = 1;
	m_taille = 1;
	m_periode = 0;
	m_depart = _T("");
	//}}AFX_DATA_INIT
}


void CDlgConfig::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgConfig)
	DDX_Control(pDX, F1_IDC_TOP_EXTERNE, m_top_externe);
	DDX_Control(pDX, F1_IDC_AFFECTABLE, m_affectable);
	DDX_Control(pDX, F1_IDC_LISTE_LIAISON, m_liste_liaison);
	DDX_Text(pDX, F1_IDC_NUM_PORT, m_num_port);
	DDV_MinMaxUInt(pDX, m_num_port, 1, 51);
	DDX_Text(pDX, F1_IDC_NB_LIAISON, m_nb_liaison);
	DDV_MinMaxUInt(pDX, m_nb_liaison, 1, 51);
	DDX_Text(pDX, F1_IDC_TAILLE_JOURNAUX, m_taille);
	DDV_MinMaxUInt(pDX, m_taille, 1, 100000);
	DDX_Text(pDX, F1_IDC_TOP_PERIODE, m_periode);
	DDV_MinMaxUInt(pDX, m_periode, 0, 86400);
	DDX_Text(pDX, F1_IDC_TOP_DEPART, m_depart);
	DDV_MaxChars(pDX, m_depart, 8);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgConfig, CDialog)
	//{{AFX_MSG_MAP(CDlgConfig)
	ON_EN_KILLFOCUS(F1_IDC_NB_LIAISON, OnKillfocusIdcNbLiaison)
	ON_LBN_SELCHANGE(F1_IDC_LISTE_LIAISON, OnSelchangeIdcListeLiaison)
	ON_BN_CLICKED(F1_IDC_AFFECTABLE, OnIdcAffectable)
	ON_EN_KILLFOCUS(F1_IDC_TAILLE_JOURNAUX, OnKillfocusIdcTailleJournaux)
	ON_BN_CLICKED(F1_IDC_TOP_EXTERNE, OnIdcTopExterne)
	ON_EN_KILLFOCUS(F1_IDC_TOP_DEPART, OnKillfocusIdcTopDepart)
	ON_EN_KILLFOCUS(F1_IDC_TOP_PERIODE, OnKillfocusIdcTopPeriode)
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	ON_LBN_DBLCLK(F1_IDC_LISTE_LIAISON, OnDblclkIdcListeLiaison)
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgConfig message handlers

BOOL CDlgConfig::OnInitDialog() 
{
	UINT		i;
	char		tps[25];
	t_affecte 	ligne;

	CDialog::OnInitDialog();

	nb_liaison = glob_paramsimu->MaxLiaison();
	m_nb_liaison = nb_liaison;
	m_num_port = nb_liaison;

	for(i=0 ; i<NB_MAX_LIAISON ; i++)
	{
		glob_paramsimu->Equipement(i,&ligne);
		if(ligne.Eqp != NULL) (ligne.Eqp)->Verrouiller(FALSE);	
		affecte[i]=	ligne.affectable;
//		affecte[i]=	glob_paramsimu->Affectable(i);
	}

	taille = glob_paramsimu->MaxMessage();
	m_taille = taille;

	glob_paramsimu->Top_synchro(&top_externe,&depart,&periode);
	m_top_externe.SetCheck(top_externe);
	m_depart = Conv_S_H(tps,depart);
	m_periode = periode;

	GetDlgItem(F1_IDC_TOP_PERIODE)->EnableWindow(!top_externe);
	GetDlgItem(F1_IDC_TOP_DEPART)->EnableWindow(!top_externe);

	GetDlgItem(F1_IDC_NUM_PORT)->EnableWindow(FALSE);

	UpdateData(FALSE);

	Rafraichir_liste();	// Rafrichissement de la liste liaison
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgConfig::OnKillfocusIdcNbLiaison() 
{
	if(UpdateData(TRUE))
	{
		if(m_nb_liaison != nb_liaison)	// Changement de valeur
		{
			nb_liaison = m_nb_liaison;	
			Rafraichir_liste();
		}
	}
	else
	{
		m_nb_liaison = nb_liaison;
		UpdateData(FALSE);
	}
}

void CDlgConfig::Rafraichir_liste() 
{
	int		i;
	char	message[80];
	
	m_liste_liaison.ResetContent();

	for(i=0 ; i<(int)nb_liaison ; i++)
	{
		if(affecte[i]) sprintf(message,"COM%2d - Affectable",i+1);
		else sprintf(message,"COM%2d - *** Réservée ***",i+1);
		
		if(i == 50)
			sprintf(message,"ETH%2d - Affectable",0);

		m_liste_liaison.AddString(message);
		
	}


	if(m_num_port>nb_liaison)
	{
		m_num_port = nb_liaison;
		UpdateData(FALSE);
	}

	m_liste_liaison.SetCurSel(m_num_port-1);
	m_affectable.SetCheck(!affecte[m_num_port-1]); 
}


void CDlgConfig::OnOK() 
{
	UINT		i;

// Config liaison
	glob_paramsimu->Modif_Nb_liaison(nb_liaison);

	for(i=0; i<nb_liaison ; i++)
	{
		glob_paramsimu->Modif_Affecte(i,affecte[i]);
	}

// Taille des journaux
	glob_paramsimu->Modif_taille(taille);

// Top_synchro
	glob_paramsimu->Change_top_synchro(top_externe,depart,periode);

	CDialog::OnOK();
}

void CDlgConfig::OnSelchangeIdcListeLiaison() 
{
	int		index;

	index = m_liste_liaison.GetCurSel();
	m_num_port = index+1;
	m_affectable.SetCheck(!affecte[index]); 
	UpdateData(FALSE);
}

void CDlgConfig::OnIdcAffectable() 
{
	char	message[80];

	UpdateData(TRUE);
	affecte[m_num_port -1] = !m_affectable.GetCheck();

	m_liste_liaison.DeleteString(m_num_port -1);
	if(affecte[m_num_port -1]) sprintf(message,"COM%2d - Affectable",m_num_port);
	else sprintf(message,"COM%2d - *** Réservée ***",m_num_port);
	m_liste_liaison.AddString(message);

}

void CDlgConfig::OnDblclkIdcListeLiaison() 
{
	int		index;
	char	message[80];

	index = m_liste_liaison.GetCurSel();
	m_num_port = index+1;

	affecte[index] = !affecte[index];
	m_affectable.SetCheck(!affecte[index]); 

	UpdateData(FALSE);

	m_liste_liaison.DeleteString(index);
	if(affecte[index]) sprintf(message,"COM%2d - Affectable",index+1);
	else sprintf(message,"COM%2d - *** Réservée ***",index+1);
	index = m_liste_liaison.AddString(message);
	m_liste_liaison.SetCaretIndex(index,TRUE);

}

void CDlgConfig::OnKillfocusIdcTailleJournaux() 
{
	if(UpdateData(TRUE))
	{
		if(m_taille != taille)	// Changement de valeur
			taille = m_taille;	
	}
	else
	{
		m_taille = taille;
		UpdateData(FALSE);
	}
}

void CDlgConfig::OnIdcTopExterne() 
{
	top_externe = m_top_externe.GetCheck();
	GetDlgItem(F1_IDC_TOP_PERIODE)->EnableWindow(!top_externe);
	GetDlgItem(F1_IDC_TOP_DEPART)->EnableWindow(!top_externe);
}

void CDlgConfig::OnKillfocusIdcTopDepart() 
{
	char		tps[25];
	if(UpdateData(TRUE))
	{
		strcpy(tps,m_depart);
		if(Conv_H_S(tps) != depart)	// Changement de valeur
			depart = Conv_H_S(tps);	
	}
	else
	{
		m_depart = Conv_S_H(tps,depart);
		UpdateData(FALSE);
	}
}

void CDlgConfig::OnKillfocusIdcTopPeriode() 
{
	if(UpdateData(TRUE))
	{
		if(m_periode != (UINT)periode)	// Changement de valeur
			periode = m_periode;	
	}
	else
	{
		m_periode = periode;
		UpdateData(FALSE);
	}
}

void CDlgConfig::OnHelp() 
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_CONFIG,"Configuration du simulateur");
	if(iResult >=  0) win.DoModal();
}

void CDlgConfig::OnDestroy() 
{
	if (glob_paramsimu == NULL)
		return;

	CDialog::OnDestroy();
	
	int		i;
	int		nb_liaison;
	t_affecte	ligne;

	nb_liaison = glob_paramsimu->MaxLiaison();
	for(i=0 ; i<nb_liaison ; i++)
	{
		glob_paramsimu->Equipement(i,&ligne);
		if(ligne.Eqp != NULL) (ligne.Eqp)->Verrouiller(TRUE);	
	}
	
}
