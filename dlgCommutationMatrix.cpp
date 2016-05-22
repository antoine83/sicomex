/* **************************************************************************
FICHIER :	DlgCommutztionMatrix.CPP		 		AUTEUR : FSA
DATE DE CREATION : 	26/02/07			DERNIERE MODIFICATION : 27/02/07
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgCommutationMatrix
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "DlgCommutationMatrix.h"
#include "Equip\EqpMatCom.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_HELP_COMMUTATION_MATRIX[];

CDlgCommutationMatrix::CDlgCommutationMatrix(CWnd* pParent)
	: CDlgEquip(CDlgCommutationMatrix::IDD, pParent)
{
	// TODO -
	//{{AFX_DATA_INIT(CDlgCommutationMatrix)
	m_err_retard = _T("");
	m_periode = _T("");
	m_tempo = _T("");
	//}}AFX_DATA_INIT

	bmp_BLACK = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BLACK));
	bmp_WHITE = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_WHITE));
	m_hIcon = AfxGetApp()->LoadIcon(IDI_EM_HF);
}


void CDlgCommutationMatrix::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgCommutationMatrix)
	DDX_Control(pDX, IDC_MES_STATUT, m_liste_message);
	DDX_Control(pDX, IDC_CHECK_SYNCHRO, m_synchro);
	DDX_Control(pDX, IDC_CHECK_CYCLE, m_cycle);
	DDX_Text(pDX, IDC_RETARD, m_err_retard);
	DDX_Text(pDX, IDC_EDIT_CYCLE, m_periode);
	DDX_Text(pDX, IDC_EDIT_TEMPO, m_tempo);
	DDX_Text(pDX, IDC_EDIT1, m_result_test);


	DDX_Control	(pDX, IDC_COM_MAT_TX_1x1,				m_tx[0][0]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_1x2,				m_tx[0][1]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_1x3,				m_tx[0][2]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_1x4,				m_tx[0][3]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_1x5,				m_tx[0][4]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_1x6,				m_tx[0][5]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_1x7,				m_tx[0][6]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_1x8,				m_tx[0][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_TX_2x1,				m_tx[1][0]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_2x2,				m_tx[1][1]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_2x3,				m_tx[1][2]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_2x4,				m_tx[1][3]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_2x5,				m_tx[1][4]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_2x6,				m_tx[1][5]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_2x7,				m_tx[1][6]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_2x8,				m_tx[1][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_TX_3x1,				m_tx[2][0]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_3x2,				m_tx[2][1]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_3x3,				m_tx[2][2]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_3x4,				m_tx[2][3]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_3x5,				m_tx[2][4]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_3x6,				m_tx[2][5]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_3x7,				m_tx[2][6]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_3x8,				m_tx[2][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_TX_4x1,				m_tx[3][0]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_4x2,				m_tx[3][1]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_4x3,				m_tx[3][2]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_4x4,				m_tx[3][3]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_4x5,				m_tx[3][4]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_4x6,				m_tx[3][5]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_4x7,				m_tx[3][6]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_4x8,				m_tx[3][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_TX_5x1,				m_tx[4][0]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_5x2,				m_tx[4][1]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_5x3,				m_tx[4][2]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_5x4,				m_tx[4][3]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_5x5,				m_tx[4][4]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_5x6,				m_tx[4][5]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_5x7,				m_tx[4][6]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_5x8,				m_tx[4][7]);

	DDX_Control	(pDX, IDC_COM_MAT_TX_6x1,				m_tx[5][0]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_6x2,				m_tx[5][1]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_6x3,				m_tx[5][2]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_6x4,				m_tx[5][3]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_6x5,				m_tx[5][4]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_6x6,				m_tx[5][5]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_6x7,				m_tx[5][6]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_6x8,				m_tx[5][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_TX_7x1,				m_tx[6][0]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_7x2,				m_tx[6][1]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_7x3,				m_tx[6][2]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_7x4,				m_tx[6][3]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_7x5,				m_tx[6][4]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_7x6,				m_tx[6][5]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_7x7,				m_tx[6][6]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_7x8,				m_tx[6][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_TX_8x1,				m_tx[7][0]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_8x2,				m_tx[7][1]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_8x3,				m_tx[7][2]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_8x4,				m_tx[7][3]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_8x5,				m_tx[7][4]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_8x6,				m_tx[7][5]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_8x7,				m_tx[7][6]);
	DDX_Control	(pDX, IDC_COM_MAT_TX_8x8,				m_tx[7][7]);

	DDX_Control	(pDX, IDC_COM_MAT_RX_1x1,				m_rx[0][0]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_1x2,				m_rx[0][1]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_1x3,				m_rx[0][2]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_1x4,				m_rx[0][3]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_1x5,				m_rx[0][4]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_1x6,				m_rx[0][5]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_1x7,				m_rx[0][6]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_1x8,				m_rx[0][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_RX_2x1,				m_rx[1][0]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_2x2,				m_rx[1][1]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_2x3,				m_rx[1][2]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_2x4,				m_rx[1][3]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_2x5,				m_rx[1][4]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_2x6,				m_rx[1][5]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_2x7,				m_rx[1][6]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_2x8,				m_rx[1][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_RX_3x1,				m_rx[2][0]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_3x2,				m_rx[2][1]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_3x3,				m_rx[2][2]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_3x4,				m_rx[2][3]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_3x5,				m_rx[2][4]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_3x6,				m_rx[2][5]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_3x7,				m_rx[2][6]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_3x8,				m_rx[2][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_RX_4x1,				m_rx[3][0]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_4x2,				m_rx[3][1]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_4x3,				m_rx[3][2]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_4x4,				m_rx[3][3]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_4x5,				m_rx[3][4]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_4x6,				m_rx[3][5]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_4x7,				m_rx[3][6]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_4x8,				m_rx[3][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_RX_5x1,				m_rx[4][0]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_5x2,				m_rx[4][1]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_5x3,				m_rx[4][2]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_5x4,				m_rx[4][3]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_5x5,				m_rx[4][4]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_5x6,				m_rx[4][5]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_5x7,				m_rx[4][6]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_5x8,				m_rx[4][7]);

	DDX_Control	(pDX, IDC_COM_MAT_RX_6x1,				m_rx[5][0]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_6x2,				m_rx[5][1]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_6x3,				m_rx[5][2]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_6x4,				m_rx[5][3]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_6x5,				m_rx[5][4]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_6x6,				m_rx[5][5]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_6x7,				m_rx[5][6]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_6x8,				m_rx[5][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_RX_7x1,				m_rx[6][0]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_7x2,				m_rx[6][1]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_7x3,				m_rx[6][2]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_7x4,				m_rx[6][3]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_7x5,				m_rx[6][4]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_7x6,				m_rx[6][5]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_7x7,				m_rx[6][6]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_7x8,				m_rx[6][7]);
	
	DDX_Control	(pDX, IDC_COM_MAT_RX_8x1,				m_rx[7][0]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_8x2,				m_rx[7][1]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_8x3,				m_rx[7][2]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_8x4,				m_rx[7][3]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_8x5,				m_rx[7][4]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_8x6,				m_rx[7][5]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_8x7,				m_rx[7][6]);
	DDX_Control	(pDX, IDC_COM_MAT_RX_8x8,				m_rx[7][7]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgCommutationMatrix, CDialog)
	//{{AFX_MSG_MAP(CDlgCommutationMatrix)
	ON_BN_CLICKED(IDC_REMOTE_CONTROL_MODE, OnRemoteControlClicked)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_CDE_INCONUE, OnComErreur)
	ON_BN_CLICKED(IDC_DEBUT_TRAME, OnComErreur)
	ON_BN_CLICKED(IDC_FIN_TRAME, OnComErreur)
	ON_EN_KILLFOCUS(IDC_RETARD, OnComErreur)
	ON_BN_CLICKED(IDC_PAS_REPONSE, OnComErreur)
	ON_BN_CLICKED(IDC_COM_MAT_TX_1x1,OnClickButtonTX1x1)
	ON_BN_CLICKED(IDC_COM_MAT_TX_1x2,OnClickButtonTX1x2)
	ON_BN_CLICKED(IDC_COM_MAT_TX_1x3,OnClickButtonTX1x3)
	ON_BN_CLICKED(IDC_COM_MAT_TX_1x4,OnClickButtonTX1x4)
	ON_BN_CLICKED(IDC_COM_MAT_TX_1x5,OnClickButtonTX1x5)
	ON_BN_CLICKED(IDC_COM_MAT_TX_1x6,OnClickButtonTX1x6)
	ON_BN_CLICKED(IDC_COM_MAT_TX_1x7,OnClickButtonTX1x7)
	ON_BN_CLICKED(IDC_COM_MAT_TX_1x8,OnClickButtonTX1x8)
	ON_BN_CLICKED(IDC_COM_MAT_TX_2x1,OnClickButtonTX2x1)
	ON_BN_CLICKED(IDC_COM_MAT_TX_2x2,OnClickButtonTX2x2)
	ON_BN_CLICKED(IDC_COM_MAT_TX_2x3,OnClickButtonTX2x3)
	ON_BN_CLICKED(IDC_COM_MAT_TX_2x4,OnClickButtonTX2x4)
	ON_BN_CLICKED(IDC_COM_MAT_TX_2x5,OnClickButtonTX2x5)
	ON_BN_CLICKED(IDC_COM_MAT_TX_2x6,OnClickButtonTX2x6)
	ON_BN_CLICKED(IDC_COM_MAT_TX_2x7,OnClickButtonTX2x7)
	ON_BN_CLICKED(IDC_COM_MAT_TX_2x8,OnClickButtonTX2x8)
	ON_BN_CLICKED(IDC_COM_MAT_TX_3x1,OnClickButtonTX3x1)
	ON_BN_CLICKED(IDC_COM_MAT_TX_3x2,OnClickButtonTX3x2)
	ON_BN_CLICKED(IDC_COM_MAT_TX_3x3,OnClickButtonTX3x3)
	ON_BN_CLICKED(IDC_COM_MAT_TX_3x4,OnClickButtonTX3x4)
	ON_BN_CLICKED(IDC_COM_MAT_TX_3x5,OnClickButtonTX3x5)
	ON_BN_CLICKED(IDC_COM_MAT_TX_3x6,OnClickButtonTX3x6)
	ON_BN_CLICKED(IDC_COM_MAT_TX_3x7,OnClickButtonTX3x7)
	ON_BN_CLICKED(IDC_COM_MAT_TX_3x8,OnClickButtonTX3x8)
	ON_BN_CLICKED(IDC_COM_MAT_TX_4x1,OnClickButtonTX4x1)
	ON_BN_CLICKED(IDC_COM_MAT_TX_4x2,OnClickButtonTX4x2)
	ON_BN_CLICKED(IDC_COM_MAT_TX_4x3,OnClickButtonTX4x3)
	ON_BN_CLICKED(IDC_COM_MAT_TX_4x4,OnClickButtonTX4x4)
	ON_BN_CLICKED(IDC_COM_MAT_TX_4x5,OnClickButtonTX4x5)
	ON_BN_CLICKED(IDC_COM_MAT_TX_4x6,OnClickButtonTX4x6)
	ON_BN_CLICKED(IDC_COM_MAT_TX_4x7,OnClickButtonTX4x7)
	ON_BN_CLICKED(IDC_COM_MAT_TX_4x8,OnClickButtonTX4x8)
	ON_BN_CLICKED(IDC_COM_MAT_TX_5x1,OnClickButtonTX5x1)
	ON_BN_CLICKED(IDC_COM_MAT_TX_5x2,OnClickButtonTX5x2)
	ON_BN_CLICKED(IDC_COM_MAT_TX_5x3,OnClickButtonTX5x3)
	ON_BN_CLICKED(IDC_COM_MAT_TX_5x4,OnClickButtonTX5x4)
	ON_BN_CLICKED(IDC_COM_MAT_TX_5x5,OnClickButtonTX5x5)
	ON_BN_CLICKED(IDC_COM_MAT_TX_5x6,OnClickButtonTX5x6)
	ON_BN_CLICKED(IDC_COM_MAT_TX_5x7,OnClickButtonTX5x7)
	ON_BN_CLICKED(IDC_COM_MAT_TX_5x8,OnClickButtonTX5x8)
	ON_BN_CLICKED(IDC_COM_MAT_TX_6x1,OnClickButtonTX6x1)
	ON_BN_CLICKED(IDC_COM_MAT_TX_6x2,OnClickButtonTX6x2)
	ON_BN_CLICKED(IDC_COM_MAT_TX_6x3,OnClickButtonTX6x3)
	ON_BN_CLICKED(IDC_COM_MAT_TX_6x4,OnClickButtonTX6x4)
	ON_BN_CLICKED(IDC_COM_MAT_TX_6x5,OnClickButtonTX6x5)
	ON_BN_CLICKED(IDC_COM_MAT_TX_6x6,OnClickButtonTX6x6)
	ON_BN_CLICKED(IDC_COM_MAT_TX_6x7,OnClickButtonTX6x7)
	ON_BN_CLICKED(IDC_COM_MAT_TX_6x8,OnClickButtonTX6x8)
	ON_BN_CLICKED(IDC_COM_MAT_TX_7x1,OnClickButtonTX7x1)
	ON_BN_CLICKED(IDC_COM_MAT_TX_7x2,OnClickButtonTX7x2)
	ON_BN_CLICKED(IDC_COM_MAT_TX_7x3,OnClickButtonTX7x3)
	ON_BN_CLICKED(IDC_COM_MAT_TX_7x4,OnClickButtonTX7x4)
	ON_BN_CLICKED(IDC_COM_MAT_TX_7x5,OnClickButtonTX7x5)
	ON_BN_CLICKED(IDC_COM_MAT_TX_7x6,OnClickButtonTX7x6)
	ON_BN_CLICKED(IDC_COM_MAT_TX_7x7,OnClickButtonTX7x7)
	ON_BN_CLICKED(IDC_COM_MAT_TX_7x8,OnClickButtonTX7x8)
	ON_BN_CLICKED(IDC_COM_MAT_TX_8x1,OnClickButtonTX8x1)
	ON_BN_CLICKED(IDC_COM_MAT_TX_8x2,OnClickButtonTX8x2)
	ON_BN_CLICKED(IDC_COM_MAT_TX_8x3,OnClickButtonTX8x3)
	ON_BN_CLICKED(IDC_COM_MAT_TX_8x4,OnClickButtonTX8x4)
	ON_BN_CLICKED(IDC_COM_MAT_TX_8x5,OnClickButtonTX8x5)
	ON_BN_CLICKED(IDC_COM_MAT_TX_8x6,OnClickButtonTX8x6)
	ON_BN_CLICKED(IDC_COM_MAT_TX_8x7,OnClickButtonTX8x7)
	ON_BN_CLICKED(IDC_COM_MAT_TX_8x8,OnClickButtonTX8x8)
	ON_BN_CLICKED(IDC_COM_MAT_RX_1x1,OnClickButtonRX1x1)
	ON_BN_CLICKED(IDC_COM_MAT_RX_1x2,OnClickButtonRX1x2)
	ON_BN_CLICKED(IDC_COM_MAT_RX_1x3,OnClickButtonRX1x3)
	ON_BN_CLICKED(IDC_COM_MAT_RX_1x4,OnClickButtonRX1x4)
	ON_BN_CLICKED(IDC_COM_MAT_RX_1x5,OnClickButtonRX1x5)
	ON_BN_CLICKED(IDC_COM_MAT_RX_1x6,OnClickButtonRX1x6)
	ON_BN_CLICKED(IDC_COM_MAT_RX_1x7,OnClickButtonRX1x7)
	ON_BN_CLICKED(IDC_COM_MAT_RX_1x8,OnClickButtonRX1x8)
	ON_BN_CLICKED(IDC_COM_MAT_RX_2x1,OnClickButtonRX2x1)
	ON_BN_CLICKED(IDC_COM_MAT_RX_2x2,OnClickButtonRX2x2)
	ON_BN_CLICKED(IDC_COM_MAT_RX_2x3,OnClickButtonRX2x3)
	ON_BN_CLICKED(IDC_COM_MAT_RX_2x4,OnClickButtonRX2x4)
	ON_BN_CLICKED(IDC_COM_MAT_RX_2x5,OnClickButtonRX2x5)
	ON_BN_CLICKED(IDC_COM_MAT_RX_2x6,OnClickButtonRX2x6)
	ON_BN_CLICKED(IDC_COM_MAT_RX_2x7,OnClickButtonRX2x7)
	ON_BN_CLICKED(IDC_COM_MAT_RX_2x8,OnClickButtonRX2x8)
	ON_BN_CLICKED(IDC_COM_MAT_RX_3x1,OnClickButtonRX3x1)
	ON_BN_CLICKED(IDC_COM_MAT_RX_3x2,OnClickButtonRX3x2)
	ON_BN_CLICKED(IDC_COM_MAT_RX_3x3,OnClickButtonRX3x3)
	ON_BN_CLICKED(IDC_COM_MAT_RX_3x4,OnClickButtonRX3x4)
	ON_BN_CLICKED(IDC_COM_MAT_RX_3x5,OnClickButtonRX3x5)
	ON_BN_CLICKED(IDC_COM_MAT_RX_3x6,OnClickButtonRX3x6)
	ON_BN_CLICKED(IDC_COM_MAT_RX_3x7,OnClickButtonRX3x7)
	ON_BN_CLICKED(IDC_COM_MAT_RX_3x8,OnClickButtonRX3x8)
	ON_BN_CLICKED(IDC_COM_MAT_RX_4x1,OnClickButtonRX4x1)
	ON_BN_CLICKED(IDC_COM_MAT_RX_4x2,OnClickButtonRX4x2)
	ON_BN_CLICKED(IDC_COM_MAT_RX_4x3,OnClickButtonRX4x3)
	ON_BN_CLICKED(IDC_COM_MAT_RX_4x4,OnClickButtonRX4x4)
	ON_BN_CLICKED(IDC_COM_MAT_RX_4x5,OnClickButtonRX4x5)
	ON_BN_CLICKED(IDC_COM_MAT_RX_4x6,OnClickButtonRX4x6)
	ON_BN_CLICKED(IDC_COM_MAT_RX_4x7,OnClickButtonRX4x7)
	ON_BN_CLICKED(IDC_COM_MAT_RX_4x8,OnClickButtonRX4x8)
	ON_BN_CLICKED(IDC_COM_MAT_RX_5x1,OnClickButtonRX5x1)
	ON_BN_CLICKED(IDC_COM_MAT_RX_5x2,OnClickButtonRX5x2)
	ON_BN_CLICKED(IDC_COM_MAT_RX_5x3,OnClickButtonRX5x3)
	ON_BN_CLICKED(IDC_COM_MAT_RX_5x4,OnClickButtonRX5x4)
	ON_BN_CLICKED(IDC_COM_MAT_RX_5x5,OnClickButtonRX5x5)
	ON_BN_CLICKED(IDC_COM_MAT_RX_5x6,OnClickButtonRX5x6)
	ON_BN_CLICKED(IDC_COM_MAT_RX_5x7,OnClickButtonRX5x7)
	ON_BN_CLICKED(IDC_COM_MAT_RX_5x8,OnClickButtonRX5x8)
	ON_BN_CLICKED(IDC_COM_MAT_RX_6x1,OnClickButtonRX6x1)
	ON_BN_CLICKED(IDC_COM_MAT_RX_6x2,OnClickButtonRX6x2)
	ON_BN_CLICKED(IDC_COM_MAT_RX_6x3,OnClickButtonRX6x3)
	ON_BN_CLICKED(IDC_COM_MAT_RX_6x4,OnClickButtonRX6x4)
	ON_BN_CLICKED(IDC_COM_MAT_RX_6x5,OnClickButtonRX6x5)
	ON_BN_CLICKED(IDC_COM_MAT_RX_6x6,OnClickButtonRX6x6)
	ON_BN_CLICKED(IDC_COM_MAT_RX_6x7,OnClickButtonRX6x7)
	ON_BN_CLICKED(IDC_COM_MAT_RX_6x8,OnClickButtonRX6x8)
	ON_BN_CLICKED(IDC_COM_MAT_RX_7x1,OnClickButtonRX7x1)
	ON_BN_CLICKED(IDC_COM_MAT_RX_7x2,OnClickButtonRX7x2)
	ON_BN_CLICKED(IDC_COM_MAT_RX_7x3,OnClickButtonRX7x3)
	ON_BN_CLICKED(IDC_COM_MAT_RX_7x4,OnClickButtonRX7x4)
	ON_BN_CLICKED(IDC_COM_MAT_RX_7x5,OnClickButtonRX7x5)
	ON_BN_CLICKED(IDC_COM_MAT_RX_7x6,OnClickButtonRX7x6)
	ON_BN_CLICKED(IDC_COM_MAT_RX_7x7,OnClickButtonRX7x7)
	ON_BN_CLICKED(IDC_COM_MAT_RX_7x8,OnClickButtonRX7x8)
	ON_BN_CLICKED(IDC_COM_MAT_RX_8x1,OnClickButtonRX8x1)
	ON_BN_CLICKED(IDC_COM_MAT_RX_8x2,OnClickButtonRX8x2)
	ON_BN_CLICKED(IDC_COM_MAT_RX_8x3,OnClickButtonRX8x3)
	ON_BN_CLICKED(IDC_COM_MAT_RX_8x4,OnClickButtonRX8x4)
	ON_BN_CLICKED(IDC_COM_MAT_RX_8x5,OnClickButtonRX8x5)
	ON_BN_CLICKED(IDC_COM_MAT_RX_8x6,OnClickButtonRX8x6)
	ON_BN_CLICKED(IDC_COM_MAT_RX_8x7,OnClickButtonRX8x7)
	ON_BN_CLICKED(IDC_COM_MAT_RX_8x8,OnClickButtonRX8x8)
	ON_EN_KILLFOCUS(IDC_EDIT1, OnKillfocusEdit)
	//}}AFX_MSG_MAP

	ON_WM_CLOSE()
	ON_WM_PAINT()

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

END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgCommutationMatrix message handlers

void CDlgCommutationMatrix::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_COMMUTATION_MATRIX,"Matrice de commutation");
	if(iResult >=  0) win.DoModal();
}

BOOL CDlgCommutationMatrix::OnInitDialog() 
{
	t_ComErreur	err;
	char		buf[10];

	CDialog::OnInitDialog();

	// Armement du timer
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

	// Custom controls.
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);
	m_local.SubclassDlgItem(IDC_REMOTE_CONTROL_MODE, this);

	m_local.Positionne_etat(!((CEquipCommutationMatrix *)equip)->isLocal());
	m_result_test="OK";
	refresh();

	return TRUE;
}

// OnTimer : Rafraichissement de l'écran de controle **************************
// ****************************************************************************
void CDlgCommutationMatrix::OnTimer(UINT nIDEvent) 
{
	int	 val;
	//char buf[10];							//2009-11-27

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

	refresh();
}

void CDlgCommutationMatrix::refresh() {
	
	for(short i=0; i< RECEPTACLE_COUNT; i++) {
		//m_inputs[i] = ((CEquipCommutationMatrix *)equip)->getInputName(i + 1);
		//m_outputs[i] = ((CEquipCommutationMatrix *)equip)->getOutputName(i + 1);
		short emissionDownlink = ((CEquipCommutationMatrix*)equip)->getEmissionConnection(i+1);
		short receptionDownlink = ((CEquipCommutationMatrix*)equip)->getReceptionConnection(i+1);
		for (short eachDownlink = 1; eachDownlink <= RECEPTACLE_COUNT; eachDownlink++) {
			if(emissionDownlink == eachDownlink) {
				m_tx[i][eachDownlink - 1].SetBitmap(bmp_BLACK);
			} else {
				m_tx[i][eachDownlink - 1].SetBitmap(bmp_WHITE);
			}
			if(receptionDownlink == eachDownlink) {
				m_rx[i][eachDownlink - 1].SetBitmap(bmp_BLACK);
			} else {
				m_rx[i][eachDownlink - 1].SetBitmap(bmp_WHITE);
			}
		}
	}
	UpdateData(FALSE);
}

// Comm erreur ********************************************
void CDlgCommutationMatrix::OnComErreur() 
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


void CDlgCommutationMatrix::OnRemoteControlClicked() {
	((CEquipCommutationMatrix *)equip)->setLocal(
		! ((CEquipCommutationMatrix *)equip)->isLocal());
	m_local.Positionne_etat(!((CEquipCommutationMatrix *)equip)->isLocal());
}

/**Button of matrix emission*/
//test function button1x1
void CDlgCommutationMatrix::OnClickButtonTX1x1(){OnTraitement(0, 0 ,true);}

//test function button1x2
void CDlgCommutationMatrix::OnClickButtonTX1x2(){OnTraitement(0, 1 ,true);}

//test function button1x3
void CDlgCommutationMatrix::OnClickButtonTX1x3(){OnTraitement(0, 2 ,true);}

//test function button1x4
void CDlgCommutationMatrix::OnClickButtonTX1x4(){OnTraitement(0, 3 ,true);}

//test function button1x5
void CDlgCommutationMatrix::OnClickButtonTX1x5(){OnTraitement(0, 4 ,true);}

//test function button1x6
void CDlgCommutationMatrix::OnClickButtonTX1x6(){OnTraitement(0, 5 ,true);}

//test function button1x7
void CDlgCommutationMatrix::OnClickButtonTX1x7(){OnTraitement(0, 6 ,true);}

//test function button2x8
void CDlgCommutationMatrix::OnClickButtonTX1x8(){OnTraitement(0, 7 ,true);}

//test function button2x1
void CDlgCommutationMatrix::OnClickButtonTX2x1(){OnTraitement(1, 0 ,true);}

//test function button2x2
void CDlgCommutationMatrix::OnClickButtonTX2x2(){OnTraitement(1, 1 ,true);}

//test function button2x3
void CDlgCommutationMatrix::OnClickButtonTX2x3(){OnTraitement(1, 2 ,true);}

//test function button2x4
void CDlgCommutationMatrix::OnClickButtonTX2x4(){OnTraitement(1, 3 ,true);}

//test function button2x5
void CDlgCommutationMatrix::OnClickButtonTX2x5(){OnTraitement(1, 4 ,true);}

//test function button2x6
void CDlgCommutationMatrix::OnClickButtonTX2x6(){OnTraitement(1, 5 ,true);}

//test function button2x7
void CDlgCommutationMatrix::OnClickButtonTX2x7(){OnTraitement(1, 6 ,true);}

//test function button2x8
void CDlgCommutationMatrix::OnClickButtonTX2x8(){OnTraitement(1, 7 ,true);}

//test function button3x1
void CDlgCommutationMatrix::OnClickButtonTX3x1(){OnTraitement(2, 0 ,true);}

//test function button3x2
void CDlgCommutationMatrix::OnClickButtonTX3x2(){OnTraitement(2, 1 ,true);}

//test function button3x3
void CDlgCommutationMatrix::OnClickButtonTX3x3(){OnTraitement(2, 2 ,true);}

//test function button3x4
void CDlgCommutationMatrix::OnClickButtonTX3x4(){OnTraitement(2, 3 ,true);}

//test function button3x5
void CDlgCommutationMatrix::OnClickButtonTX3x5(){OnTraitement(2, 4 ,true);}

//test function button3x6
void CDlgCommutationMatrix::OnClickButtonTX3x6(){OnTraitement(2, 5 ,true);}

//test function button3x7
void CDlgCommutationMatrix::OnClickButtonTX3x7(){OnTraitement(2, 6 ,true);}

//test function button3x8
void CDlgCommutationMatrix::OnClickButtonTX3x8(){OnTraitement(2, 7 ,true);}

//test function button4x1
void CDlgCommutationMatrix::OnClickButtonTX4x1(){OnTraitement(3, 0 ,true);}

//test function button4x2
void CDlgCommutationMatrix::OnClickButtonTX4x2(){OnTraitement(3, 1 ,true);}

//test function button4x3
void CDlgCommutationMatrix::OnClickButtonTX4x3(){OnTraitement(3, 2 ,true);}

//test function button4x4
void CDlgCommutationMatrix::OnClickButtonTX4x4(){OnTraitement(3, 3 ,true);}

//test function button4x5
void CDlgCommutationMatrix::OnClickButtonTX4x5(){OnTraitement(3, 4 ,true);}

//test function button4x6
void CDlgCommutationMatrix::OnClickButtonTX4x6(){OnTraitement(3, 5 ,true);}

//test function button4x7
void CDlgCommutationMatrix::OnClickButtonTX4x7(){OnTraitement(3, 6 ,true);}

//test function button4x8
void CDlgCommutationMatrix::OnClickButtonTX4x8(){OnTraitement(3, 7 ,true);}

//test function button5x1
void CDlgCommutationMatrix::OnClickButtonTX5x1(){OnTraitement(4, 0 ,true);}

//test function button5x2
void CDlgCommutationMatrix::OnClickButtonTX5x2(){OnTraitement(4, 1 ,true);}

//test function button5x3
void CDlgCommutationMatrix::OnClickButtonTX5x3(){OnTraitement(4, 2 ,true);}

//test function button5x4
void CDlgCommutationMatrix::OnClickButtonTX5x4(){OnTraitement(4, 3 ,true);}

//test function button5x5
void CDlgCommutationMatrix::OnClickButtonTX5x5(){OnTraitement(4, 4 ,true);}

//test function button5x6
void CDlgCommutationMatrix::OnClickButtonTX5x6(){OnTraitement(4, 5 ,true);}

//test function button5x7
void CDlgCommutationMatrix::OnClickButtonTX5x7(){OnTraitement(4, 6 ,true);}

//test function button5x8
void CDlgCommutationMatrix::OnClickButtonTX5x8(){OnTraitement(4, 7 ,true);}

//test function button6x1
void CDlgCommutationMatrix::OnClickButtonTX6x1(){OnTraitement(5, 0 ,true);}

//test function button6x2
void CDlgCommutationMatrix::OnClickButtonTX6x2(){OnTraitement(5, 1 ,true);}

//test function button6x3
void CDlgCommutationMatrix::OnClickButtonTX6x3(){OnTraitement(5, 2 ,true);}

//test function button6x4
void CDlgCommutationMatrix::OnClickButtonTX6x4(){OnTraitement(5, 3 ,true);}

//test function button6x5
void CDlgCommutationMatrix::OnClickButtonTX6x5(){OnTraitement(5, 4 ,true);}

//test function button6x6
void CDlgCommutationMatrix::OnClickButtonTX6x6(){OnTraitement(5, 5 ,true);}

//test function button6x7
void CDlgCommutationMatrix::OnClickButtonTX6x7(){OnTraitement(5, 6 ,true);}

//test function button6x8
void CDlgCommutationMatrix::OnClickButtonTX6x8(){OnTraitement(5, 7 ,true);}

//test function button7x1
void CDlgCommutationMatrix::OnClickButtonTX7x1(){OnTraitement(6, 0 ,true);}

//test function button7x2
void CDlgCommutationMatrix::OnClickButtonTX7x2(){OnTraitement(6, 1 ,true);}

//test function button7x3
void CDlgCommutationMatrix::OnClickButtonTX7x3(){OnTraitement(6, 2 ,true);}

//test function button7x4
void CDlgCommutationMatrix::OnClickButtonTX7x4(){OnTraitement(6, 3 ,true);}

//test function button7x5
void CDlgCommutationMatrix::OnClickButtonTX7x5(){OnTraitement(6, 4 ,true);}

//test function button7x6
void CDlgCommutationMatrix::OnClickButtonTX7x6(){OnTraitement(6, 5 ,true);}

//test function button7x7
void CDlgCommutationMatrix::OnClickButtonTX7x7(){OnTraitement(6, 6 ,true);}

//test function button7x8
void CDlgCommutationMatrix::OnClickButtonTX7x8(){OnTraitement(6, 7 ,true);}

//test function button8x1
void CDlgCommutationMatrix::OnClickButtonTX8x1(){OnTraitement(7, 0 ,true);}

//test function button8x2
void CDlgCommutationMatrix::OnClickButtonTX8x2(){OnTraitement(7, 1 ,true);}

//test function button8x3
void CDlgCommutationMatrix::OnClickButtonTX8x3(){OnTraitement(7, 2 ,true);}

//test function button8x4
void CDlgCommutationMatrix::OnClickButtonTX8x4(){OnTraitement(7, 3 ,true);}

//test function button8x5
void CDlgCommutationMatrix::OnClickButtonTX8x5(){OnTraitement(7, 4 ,true);}

//test function button8x6
void CDlgCommutationMatrix::OnClickButtonTX8x6(){OnTraitement(7, 5 ,true);}

//test function button8x7
void CDlgCommutationMatrix::OnClickButtonTX8x7(){OnTraitement(7, 6 ,true);}

//test function button8x8
void CDlgCommutationMatrix::OnClickButtonTX8x8(){OnTraitement(7, 7 ,true);}

/*Button of matrix reception*/
//test function button1x1
void CDlgCommutationMatrix::OnClickButtonRX1x1(){OnTraitement(0, 0 ,false);}

//test function button1x2
void CDlgCommutationMatrix::OnClickButtonRX1x2(){OnTraitement(0, 1 ,false);}

//test function button1x3
void CDlgCommutationMatrix::OnClickButtonRX1x3(){OnTraitement(0, 2 ,false);}

//test function button1x4
void CDlgCommutationMatrix::OnClickButtonRX1x4(){OnTraitement(0, 3 ,false);}

//test function button1x5
void CDlgCommutationMatrix::OnClickButtonRX1x5(){OnTraitement(0, 4 ,false);}

//test function button1x6
void CDlgCommutationMatrix::OnClickButtonRX1x6(){OnTraitement(0, 5 ,false);}

//test function button1x7
void CDlgCommutationMatrix::OnClickButtonRX1x7(){OnTraitement(0, 6 ,false);}

//test function button2x8
void CDlgCommutationMatrix::OnClickButtonRX1x8(){OnTraitement(0, 7 ,false);}

//test function button2x1
void CDlgCommutationMatrix::OnClickButtonRX2x1(){OnTraitement(1, 0 ,false);}

//test function button2x2
void CDlgCommutationMatrix::OnClickButtonRX2x2(){OnTraitement(1, 1 ,false);}

//test function button2x3
void CDlgCommutationMatrix::OnClickButtonRX2x3(){OnTraitement(1, 2 ,false);}

//test function button2x4
void CDlgCommutationMatrix::OnClickButtonRX2x4(){OnTraitement(1, 3 ,false);}

//test function button2x5
void CDlgCommutationMatrix::OnClickButtonRX2x5(){OnTraitement(1, 4 ,false);}

//test function button2x6
void CDlgCommutationMatrix::OnClickButtonRX2x6(){OnTraitement(1, 5 ,false);}

//test function button2x7
void CDlgCommutationMatrix::OnClickButtonRX2x7(){OnTraitement(1, 6 ,false);}

//test function button2x8
void CDlgCommutationMatrix::OnClickButtonRX2x8(){OnTraitement(1, 7 ,false);}

//test function button3x1
void CDlgCommutationMatrix::OnClickButtonRX3x1(){OnTraitement(2, 0 ,false);}

//test function button3x2
void CDlgCommutationMatrix::OnClickButtonRX3x2(){OnTraitement(2, 1 ,false);}

//test function button3x3
void CDlgCommutationMatrix::OnClickButtonRX3x3(){OnTraitement(2, 2 ,false);}

//test function button3x4
void CDlgCommutationMatrix::OnClickButtonRX3x4(){OnTraitement(2, 3 ,false);}

//test function button3x5
void CDlgCommutationMatrix::OnClickButtonRX3x5(){OnTraitement(2, 4 ,false);}

//test function button3x6
void CDlgCommutationMatrix::OnClickButtonRX3x6(){OnTraitement(2, 5 ,false);}

//test function button3x7
void CDlgCommutationMatrix::OnClickButtonRX3x7(){OnTraitement(2, 6 ,false);}

//test function button3x8
void CDlgCommutationMatrix::OnClickButtonRX3x8(){OnTraitement(2, 7 ,false);}

//test function button4x1
void CDlgCommutationMatrix::OnClickButtonRX4x1(){OnTraitement(3, 0 ,false);}

//test function button4x2
void CDlgCommutationMatrix::OnClickButtonRX4x2(){OnTraitement(3, 1 ,false);}

//test function button4x3
void CDlgCommutationMatrix::OnClickButtonRX4x3(){OnTraitement(3, 2 ,false);}

//test function button4x4
void CDlgCommutationMatrix::OnClickButtonRX4x4(){OnTraitement(3, 3 ,false);}

//test function button4x5
void CDlgCommutationMatrix::OnClickButtonRX4x5(){OnTraitement(3, 4 ,false);}

//test function button4x6
void CDlgCommutationMatrix::OnClickButtonRX4x6(){OnTraitement(3, 5 ,false);}

//test function button4x7
void CDlgCommutationMatrix::OnClickButtonRX4x7(){OnTraitement(3, 6 ,false);}

//test function button4x8
void CDlgCommutationMatrix::OnClickButtonRX4x8(){OnTraitement(3, 7 ,false);}

//test function button5x1
void CDlgCommutationMatrix::OnClickButtonRX5x1(){OnTraitement(4, 0 ,false);}

//test function button5x2
void CDlgCommutationMatrix::OnClickButtonRX5x2(){OnTraitement(4, 1 ,false);}

//test function button5x3
void CDlgCommutationMatrix::OnClickButtonRX5x3(){OnTraitement(4, 2 ,false);}

//test function button5x4
void CDlgCommutationMatrix::OnClickButtonRX5x4(){OnTraitement(4, 3 ,false);}

//test function button5x5
void CDlgCommutationMatrix::OnClickButtonRX5x5(){OnTraitement(4, 4 ,false);}

//test function button5x6
void CDlgCommutationMatrix::OnClickButtonRX5x6(){OnTraitement(4, 5 ,false);}

//test function button5x7
void CDlgCommutationMatrix::OnClickButtonRX5x7(){OnTraitement(4, 6 ,false);}

//test function button5x8
void CDlgCommutationMatrix::OnClickButtonRX5x8(){OnTraitement(4, 7 ,false);}

//test function button6x1
void CDlgCommutationMatrix::OnClickButtonRX6x1(){OnTraitement(5, 0 ,false);}

//test function button6x2
void CDlgCommutationMatrix::OnClickButtonRX6x2(){OnTraitement(5, 1 ,false);}

//test function button6x3
void CDlgCommutationMatrix::OnClickButtonRX6x3(){OnTraitement(5, 2 ,false);}

//test function button6x4
void CDlgCommutationMatrix::OnClickButtonRX6x4(){OnTraitement(5, 3 ,false);}

//test function button6x5
void CDlgCommutationMatrix::OnClickButtonRX6x5(){OnTraitement(5, 4 ,false);}

//test function button6x6
void CDlgCommutationMatrix::OnClickButtonRX6x6(){OnTraitement(5, 5 ,false);}

//test function button6x7
void CDlgCommutationMatrix::OnClickButtonRX6x7(){OnTraitement(5, 6 ,false);}

//test function button6x8
void CDlgCommutationMatrix::OnClickButtonRX6x8(){OnTraitement(5, 7 ,false);}

//test function button7x1
void CDlgCommutationMatrix::OnClickButtonRX7x1(){OnTraitement(6, 0 ,false);}

//test function button7x2
void CDlgCommutationMatrix::OnClickButtonRX7x2(){OnTraitement(6, 1 ,false);}

//test function button7x3
void CDlgCommutationMatrix::OnClickButtonRX7x3(){OnTraitement(6, 2 ,false);}

//test function button7x4
void CDlgCommutationMatrix::OnClickButtonRX7x4(){OnTraitement(6, 3 ,false);}

//test function button7x5
void CDlgCommutationMatrix::OnClickButtonRX7x5(){OnTraitement(6, 4 ,false);}

//test function button7x6
void CDlgCommutationMatrix::OnClickButtonRX7x6(){OnTraitement(6, 5 ,false);}

//test function button7x7
void CDlgCommutationMatrix::OnClickButtonRX7x7(){OnTraitement(6, 6 ,false);}

//test function button7x8
void CDlgCommutationMatrix::OnClickButtonRX7x8(){OnTraitement(6, 7 ,false);}

//test function button8x1
void CDlgCommutationMatrix::OnClickButtonRX8x1(){OnTraitement(7, 0 ,false);}

//test function button8x2
void CDlgCommutationMatrix::OnClickButtonRX8x2(){OnTraitement(7, 1 ,false);}

//test function button8x3
void CDlgCommutationMatrix::OnClickButtonRX8x3(){OnTraitement(7, 2 ,false);}

//test function button8x4
void CDlgCommutationMatrix::OnClickButtonRX8x4(){OnTraitement(7, 3 ,false);}

//test function button8x5
void CDlgCommutationMatrix::OnClickButtonRX8x5(){OnTraitement(7, 4 ,false);}

//test function button8x6
void CDlgCommutationMatrix::OnClickButtonRX8x6(){OnTraitement(7, 5 ,false);}

//test function button8x7
void CDlgCommutationMatrix::OnClickButtonRX8x7(){OnTraitement(7, 6 ,false);}

//test function button8x8
void CDlgCommutationMatrix::OnClickButtonRX8x8(){OnTraitement(7, 7 ,false);}

//treatment function button
void CDlgCommutationMatrix::OnTraitement(int para1, int para2, bool sens)
{
	if(((CEquipCommutationMatrix *)equip)->isActif()==true && ((CEquipCommutationMatrix *)equip)->isLocal()==true)
	{
		if(sens)((CEquipCommutationMatrix *)equip)->setConnectionEmission(para1+1,para2+1);//mode emission
		else ((CEquipCommutationMatrix *)equip)->setConnectionReception(para1+1,para2+1);//mode reception
		UpdateData(FALSE);
	}
}

//function Edit of result of test
void CDlgCommutationMatrix::OnKillfocusEdit()
{
	((CEquipCommutationMatrix *)equip)->ChangeEdit(m_result_test);
}