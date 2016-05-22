/* **************************************************************************
FICHIER :	DlgAffec.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgAffecte
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"

#include "DlgAffec.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern	CParamSimu 	*glob_paramsimu;
extern 	char glob_HELP_AFFECTE[];

CDlgAffecte::CDlgAffecte(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgAffecte::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgAffecte)
	m_repere = _T("");
	//}}AFX_DATA_INIT
}


void CDlgAffecte::DoDataExchange(CDataExchange* pDX)
{
	int iTemp = 0;				//int i, iTemp = 0; //2009-11-27
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgAffecte)
	DDX_Control(pDX, F1_IDC_EQUIP, m_type);
	DDX_Control(pDX, F1_IDC_PORT, m_port);
	DDX_Text(pDX, F1_IDC_EDIT_REPERE, m_repere);
	// Bug
	DDV_MaxChars(pDX, m_repere, 20);
	//DDV_MaxChars(pDX, m_repere, 25);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgAffecte, CDialog)
	//{{AFX_MSG_MAP(CDlgAffecte)
	ON_BN_CLICKED(IDC_HELP, OnHelp)
	ON_CBN_SELCHANGE(F1_IDC_PORT, OnSelchangeIdcPort)
	ON_EN_KILLFOCUS(F1_IDC_EDIT_REPERE, OnKillfocusIdcEditRepere)
	ON_CBN_SELCHANGE(F1_IDC_EQUIP, OnSelchangeIdcEquip)
	ON_BN_CLICKED(F1_IDC_RADIO_D1, OnDcRadioD1)
	ON_BN_CLICKED(F1_IDC_RADIO_D2, OnIdcRadioD2)
	ON_BN_CLICKED(F1_IDC_RADIO_D3, OnIdcRadioD3)
	ON_BN_CLICKED(F1_IDC_RADIO_D4, OnIdcRadioD4)
	ON_BN_CLICKED(F1_IDC_RADIO_V1, OnIdcRadioV1)
	ON_BN_CLICKED(F1_IDC_RADIO_V2, OnIdcRadioV2)
	ON_BN_CLICKED(F1_IDC_RADIO_V3, OnIdcRadioV3)
	ON_BN_CLICKED(F1_IDC_RADIO_V4, OnIdcRadioV4)
	ON_BN_CLICKED(F1_IDC_RADIO_V5, OnIdcRadioV5)
	ON_BN_CLICKED(F1_IDC_RADIO_A1, OnIdcRadioA1)
	ON_BN_CLICKED(F1_IDC_RADIO_A2, OnIdcRadioA2)
	ON_BN_CLICKED(F1_IDC_RADIO_A3, OnIdcRadioA3)
	ON_BN_CLICKED(F1_IDC_RADIO_P1, OnIdcRadioP1)
	ON_BN_CLICKED(F1_IDC_RADIO_P2, OnIdcRadioP2)
	ON_BN_CLICKED(F1_IDC_RADIO_P3, OnIdcRadioP3)
	ON_BN_CLICKED(F1_IDC_CONTROLE, OnIdcControle)
	ON_WM_DESTROY()
	ON_BN_CLICKED(F1_IDC_RADIO_V10, OnIdcRadioV10)
	ON_BN_CLICKED(F1_IDC_RADIO_V11, OnIdcRadioV11)
	ON_BN_CLICKED(F1_IDC_RADIO_V12, OnIdcRadioV12)
	ON_BN_CLICKED(F1_IDC_RADIO_V6, OnIdcRadioV6)
	ON_BN_CLICKED(F1_IDC_RADIO_V7, OnIdcRadioV7)
	ON_BN_CLICKED(F1_IDC_RADIO_V8, OnIdcRadioV8)
	ON_BN_CLICKED(F1_IDC_RADIO_V9, OnIdcRadioV9)
	ON_BN_CLICKED(F1_IDC_RADIO_V18, OnIdcRadioV18)
	ON_BN_CLICKED(F1_IDC_RADIO_V13, OnIdcRadioV13)
	ON_BN_CLICKED(F1_IDC_RADIO_V14, OnIdcRadioV14)
	ON_BN_CLICKED(F1_IDC_RADIO_V15, OnIdcRadioV15)
	ON_BN_CLICKED(F1_IDC_RADIO_V16, OnIdcRadioV16)
	ON_BN_CLICKED(F1_IDC_RADIO_V17, OnIdcRadioV17)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


void CDlgAffecte::OnHelp() 
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_AFFECTE,"Affectation Liaison/Equipement");
	if(iResult >=  0) win.DoModal();
}

BOOL CDlgAffecte::OnInitDialog() 
{
	CDialog::OnInitDialog();

	int		i,j;
	int		nb_liaison = glob_paramsimu->MaxLiaison();
	char	message[80];
	
	j=0;
	m_port.ResetContent();
	for(i=0 ; i<nb_liaison ; i++)
	{
		if(glob_paramsimu->Affectable(i))
		{
			index[j]=i;
			glob_paramsimu->Equipement(index[j],&ligne[j]);
			if(ligne[j].Eqp != NULL) (ligne[j].Eqp)->Verrouiller(FALSE);	

			j++;
			sprintf(message,"COM%2d:",i+1);

			if(i == 50)
				sprintf(message,"ETH%2d:",0);

			m_port.AddString(message);
		}
	}

	m_port.SetCurSel(0);

	m_type.ResetContent();
	m_type.AddString("Pas d'équipement");			// 0
	m_type.AddString("Boite d'accord");
	m_type.AddString("Standard antenne HF");
	m_type.AddString("Standard Audio/TTY");
	m_type.AddString("Em HF - TRC1225M");
	m_type.AddString("E/R UHF - TRBM18A");
	m_type.AddString("E/R UHF - TRBM18C");
	m_type.AddString("Rec HF - TRC1241A (FF)");
	m_type.AddString("Rec HF - TRC1241A (L11)");
	m_type.AddString("Rec HF - TRC1241A (SPIN)");	// 9
	m_type.AddString("Em HF - TRC1236 (FF)");
	m_type.AddString("Em HF - TRC1236 (L11)");
	m_type.AddString("Em HF - TRC1236 (SPIN)");
	m_type.AddString("Em HF - TRC1237 (FF)");
	m_type.AddString("Em HF - TRC1237 (L11)");
	m_type.AddString("Em HF - TRC1237 (SPIN)");
	m_type.AddString("Rec HF - TRC251");			// 16
	m_type.AddString("AAD 20x4");
	m_type.AddString("AAD 20x8");
	m_type.AddString("Matrice SPIN");
	m_type.AddString("Matrice L11");
	m_type.AddString("CA150 - Maître");
	m_type.AddString("CA150 - Esclave");
	m_type.AddString("KY58 sur carte CV24");
	m_type.AddString("ANDVT sur carte CV24");
	m_type.AddString("Matrice Commutation");		// 25
	m_type.AddString("KY58 sur carte TOR");
	m_type.AddString("ANDVT sur carte TOR");
	m_type.AddString("Carte TOR seule");
	//  SICOMEX - V3_0
	m_type.AddString("MDM - TRC1752P");
	// SICOMEX - V4_0
	m_type.AddString("ED42");

	//m_type.AddString("Test");
	
	OnSelchangeIdcPort();

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgAffecte::OnOK() 
{
	int		i;
	int		nb_ligne=m_port.GetCount();

	BeginWaitCursor( );

	for(i=0 ; i<nb_ligne ; i++)
	{
		glob_paramsimu->Modif_Equipement(index[i],ligne[i]);
	}
	
	EndWaitCursor( );

	CDialog::OnOK();

}

void CDlgAffecte::OnSelchangeIdcPort() 
{
	BOOL	actif;
	int	i = m_port.GetCurSel();
	m_type.SetCurSel(ligne[i].type_eqp);
	m_repere = ligne[i].repere;
	m_repere.TrimRight(' ');

	UpdateData(FALSE);

	Format(i);

	actif = ligne[i].activite;

	m_type.EnableWindow(!actif);
	GetDlgItem(F1_IDC_EDIT_REPERE)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V1)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V2)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V3)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V4)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V5)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V6)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V7)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V8)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V9)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V10)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V11)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V12)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_V18)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_D1)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_D2)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_D3)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_D4)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_A1)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_A2)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_A3)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_P1)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_P2)->EnableWindow(!actif);
	GetDlgItem(F1_IDC_RADIO_P3)->EnableWindow(!actif);

	SendDlgItemMessage(F1_IDC_ACTIVITE,BM_SETCHECK,actif,0);

	GetDlgItem(F1_IDC_CONTROLE)->EnableWindow(ligne[i].type_eqp != EQP_NON_AFFECTE);
	SendDlgItemMessage(F1_IDC_CONTROLE,BM_SETCHECK,ligne[i].controle,0);
}

void CDlgAffecte::OnKillfocusIdcEditRepere() 
{
	int	i=m_port.GetCurSel();

	UpdateData(TRUE);
	m_repere.TrimRight(' ');
	strcpy(ligne[i].repere,m_repere);
}

void CDlgAffecte::OnSelchangeIdcEquip() 
{
	int	i=m_port.GetCurSel();

	UpdateData(TRUE);
	ligne[i].type_eqp = m_type.GetCurSel();

	GetDlgItem(F1_IDC_CONTROLE)->EnableWindow(ligne[i].type_eqp != EQP_NON_AFFECTE);
	ligne[i].controle = FALSE;
	((CButton*)GetDlgItem(F1_IDC_CONTROLE))->SetCheck(FALSE);

	m_repere="";
	switch(ligne[i].type_eqp)
	{

			case EQP_BOITE_ACCORD:
				m_repere="BAA";
				break;
			case EQP_STANDARD_HF:
				m_repere="STD HF";
				break;
			case EQP_AUDIO_TTY:
				m_repere="AUDIO/TTY";
				break;

			case EQP_TRC1225M:
				m_repere="TRC1225M";
				break;

			case EQP_TRBM18A:
				m_repere="TRBM18A";
				break;
			case EQP_TRBM18C:
				m_repere="TRBM18C";
				break;

			case EQP_TRC1241_FF:
				m_repere="TRC1241_FF";
				break;

			case EQP_TRC1241_L11:
				m_repere="TRC1241_L11";
				break;
			case EQP_TRC1241_SPIN:
				m_repere="TRC1241_SPIN";
				break;
			case EQP_TRC1236_FF:
				m_repere="TRC1236_FF";
				break;
			case EQP_TRC1236_L11:
				m_repere="TRC1236_L11";
				break;
			case EQP_TRC1236_SPIN:
				m_repere="TRC1236_SPIN";
				break;

			case EQP_TRC1237_FF:
				m_repere="TRC1237_FF";
				break;
			case EQP_TRC1237_L11:
				m_repere="TRC1237_L11";
				break;
			case EQP_TRC1237_SPIN:
				m_repere="TRC1237_SPIN";
				break;
			case EQP_TRC251:
				m_repere="TRC251";
				break;

			case AAD_20_4:
				m_repere="AAD_20_4";
				break;
			case AAD_20_8:
				m_repere="AAD_20_8";
				break;
			case MATRICE_SPIN:
				m_repere="MATRICE_SPIN";
				break;
			case MATRICE_L11:
				m_repere="MATRICE_L11";
				break;
			case CA_150_MASTER:
				m_repere="CA_150_MASTER";
				break;
			case CA_150_SLAVE:
				m_repere="CA_150_SLAVE";
				break;
			case KY58:
				m_repere="KY58";
				break;
			case ANDVT:
				m_repere="ANDVT";
				break;
			case COMMUTATION_MATRIX:
				m_repere="COMMUTATION_MATRIX";
				break;
			case TOR_KY58:
				m_repere="KY58 sur carte TOR";
				break;
			case TOR_ANDVT:
				m_repere="ANDVT sur carte TOR";
				break;
			case TOR_CARD:
				m_repere="Carte TOR seule";
				break;
			case MDM_TRC1752:
				m_repere="TRC1752";
				break;
			case ED42:
				m_repere="ED42_01";
				break;
			case Test:
				m_repere="Test";
				break;
			default:
				m_repere="NA";
				break;
	}
	UpdateData(FALSE);
	strcpy(ligne[i].repere,m_repere);

}

void CDlgAffecte::OnDcRadioD1() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.data = 5;
}

void CDlgAffecte::OnIdcRadioD2() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.data = 6;
}

void CDlgAffecte::OnIdcRadioD3() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.data = 7;
}

void CDlgAffecte::OnIdcRadioD4() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.data = 8;
}

void CDlgAffecte::OnIdcRadioV1() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 75;
}

void CDlgAffecte::OnIdcRadioV2() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 150;
}

void CDlgAffecte::OnIdcRadioV3() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 200;
}

void CDlgAffecte::OnIdcRadioV4() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 300;
}

void CDlgAffecte::OnIdcRadioV5() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 600;
}

void CDlgAffecte::OnIdcRadioV6() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 1200;
}

void CDlgAffecte::OnIdcRadioV7() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 1800;
}

void CDlgAffecte::OnIdcRadioV8() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 2400;
}

void CDlgAffecte::OnIdcRadioV9() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 3600;
}


void CDlgAffecte::OnIdcRadioV10() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 4800;
}

void CDlgAffecte::OnIdcRadioV11() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 7200;
}

void CDlgAffecte::OnIdcRadioV12() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 9600;
}

void CDlgAffecte::OnIdcRadioV13() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 19200;	
}

void CDlgAffecte::OnIdcRadioV14() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 38400;	
}

void CDlgAffecte::OnIdcRadioV15() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 57600;	
}

void CDlgAffecte::OnIdcRadioV16() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 115200;	
}

void CDlgAffecte::OnIdcRadioV17() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 230400;	
}

void CDlgAffecte::OnIdcRadioV18() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.vitesse = 460800;	
}

void CDlgAffecte::OnIdcRadioA1() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.stop = UN_STOP;
}

void CDlgAffecte::OnIdcRadioA2() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.stop = DEMI_STOP;
}

void CDlgAffecte::OnIdcRadioA3() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.stop = DEUX_STOP;
}

void CDlgAffecte::OnIdcRadioP1() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.parite = SANS_PARITE;
}

void CDlgAffecte::OnIdcRadioP2() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.parite = EVEN_PARITE;
}

void CDlgAffecte::OnIdcRadioP3() 
{
	int	i = m_port.GetCurSel();
	ligne[i].format.parite = ODD_PARITE;
}

void CDlgAffecte::Format(int	idx)
{
// Vitesse de transmission
	SendDlgItemMessage(F1_IDC_RADIO_V1,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V2,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V3,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V4,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V5,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V6,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V7,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V8,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V9,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V10,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V11,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V12,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V13,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V14,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V15,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V16,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V17,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_V18,BM_SETCHECK,0,0);

	switch(ligne[idx].format.vitesse)
	{
		case 75:
			SendDlgItemMessage(F1_IDC_RADIO_V1,BM_SETCHECK,1,0);
			break;

		case 150:
			SendDlgItemMessage(F1_IDC_RADIO_V2,BM_SETCHECK,1,0);
			break;

		case 200:
			SendDlgItemMessage(F1_IDC_RADIO_V3,BM_SETCHECK,1,0);
			break;

		case 300:
			SendDlgItemMessage(F1_IDC_RADIO_V4,BM_SETCHECK,1,0);
			break;

		case 600:
			SendDlgItemMessage(F1_IDC_RADIO_V5,BM_SETCHECK,1,0);
			break;

		case 1200:
			SendDlgItemMessage(F1_IDC_RADIO_V6,BM_SETCHECK,1,0);
			break;

		case 1800:
			SendDlgItemMessage(F1_IDC_RADIO_V7,BM_SETCHECK,1,0);
			break;

		case 2400:
			SendDlgItemMessage(F1_IDC_RADIO_V8,BM_SETCHECK,1,0);
			break;

		case 3600:
			SendDlgItemMessage(F1_IDC_RADIO_V9,BM_SETCHECK,1,0);
			break;

		case 4800:
			SendDlgItemMessage(F1_IDC_RADIO_V10,BM_SETCHECK,1,0);
			break;

		case 7200:
			SendDlgItemMessage(F1_IDC_RADIO_V11,BM_SETCHECK,1,0);
			break;

		case 19200:
			SendDlgItemMessage(F1_IDC_RADIO_V13,BM_SETCHECK,1,0);
			break;

		case 38400:
			SendDlgItemMessage(F1_IDC_RADIO_V14,BM_SETCHECK,1,0);
			break;

		case 57600:
			SendDlgItemMessage(F1_IDC_RADIO_V15,BM_SETCHECK,1,0);
			break;

		case 115200:
			SendDlgItemMessage(F1_IDC_RADIO_V16,BM_SETCHECK,1,0);
			break;

		case 230400:
			SendDlgItemMessage(F1_IDC_RADIO_V17,BM_SETCHECK,1,0);
			break;

		case 460800:
			SendDlgItemMessage(F1_IDC_RADIO_V18,BM_SETCHECK,1,0);
			break;

		default:
			SendDlgItemMessage(F1_IDC_RADIO_V12,BM_SETCHECK,1,0);
			break;
	}	

// Nombre de bit de données
	SendDlgItemMessage(F1_IDC_RADIO_D1,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_D2,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_D3,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_D4,BM_SETCHECK,0,0);
	switch(ligne[idx].format.data)
	{
		case 5:
			SendDlgItemMessage(F1_IDC_RADIO_D1,BM_SETCHECK,1,0);
			break;

		case 6:
			SendDlgItemMessage(F1_IDC_RADIO_D2,BM_SETCHECK,1,0);
			break;

		case 7:
			SendDlgItemMessage(F1_IDC_RADIO_D3,BM_SETCHECK,1,0);
			break;

		default:
			SendDlgItemMessage(F1_IDC_RADIO_D4,BM_SETCHECK,1,0);
			break;
	}	

// Nombre de bit de stop
	SendDlgItemMessage(F1_IDC_RADIO_A1,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_A2,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_A3,BM_SETCHECK,0,0);
	switch(ligne[idx].format.stop)
	{
		case DEMI_STOP:
			SendDlgItemMessage(F1_IDC_RADIO_A2,BM_SETCHECK,1,0);
			break;

		case DEUX_STOP:
			SendDlgItemMessage(F1_IDC_RADIO_A3,BM_SETCHECK,1,0);
			break;

		default:
			SendDlgItemMessage(F1_IDC_RADIO_A1,BM_SETCHECK,1,0);
			break;
	}	

// Type de parité
	SendDlgItemMessage(F1_IDC_RADIO_P1,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_P2,BM_SETCHECK,0,0);
	SendDlgItemMessage(F1_IDC_RADIO_P3,BM_SETCHECK,0,0);
	switch(ligne[idx].format.parite)
	{
		case EVEN_PARITE:
			SendDlgItemMessage(F1_IDC_RADIO_P2,BM_SETCHECK,1,0);
			break;

		case ODD_PARITE:
			SendDlgItemMessage(F1_IDC_RADIO_P3,BM_SETCHECK,1,0);
			break;

		default:
			SendDlgItemMessage(F1_IDC_RADIO_P1,BM_SETCHECK,1,0);
			break;
	}	

}

void CDlgAffecte::OnIdcControle() 
{
	int	i = m_port.GetCurSel();
	ligne[i].controle = ((CButton*)GetDlgItem(F1_IDC_CONTROLE))->GetCheck();
}



void CDlgAffecte::OnDestroy() 
{
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
