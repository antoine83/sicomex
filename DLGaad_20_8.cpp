// DLGaad_20_8.cpp: implementation of the CDLGaad_20_8 class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "sicomex.h"
#include "DLGaad_20_8.h"
#include "Equip\EqpAAD.h"
#include "DlgAide.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern char glob_HELP_AAD_20_4[];

/* **************************************************************************
METHODE :		CDLGaad_20_8()
TRAITEMENT:		Construction
***************************************************************************	*/
CDLGaad_20_8::CDLGaad_20_8(CWnd* pParent /*=NULL*/)
	: CDlgEquip(CDLGaad_20_8::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDLGaad_20_8)
	m_err_retard	= _T("");
	m_periode		= _T("");
	m_tempo			= _T("");
	//}}AFX_DATA_INIT

	bmp_BLACK = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_BLACK));
	bmp_WHITE = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_WHITE));
	m_hIcon = AfxGetApp()->LoadIcon(IDB_AAD_20_8);
}

/* **************************************************************************
METHODE :		DoDataExchange(CDataExchange* pDX)
TRAITEMENT:		Procedures d'echange
***************************************************************************	*/
void CDLGaad_20_8::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDLGaad_20_8)
	DDX_Control (pDX, IDC_MES_STATUT,			m_liste_message);
	DDX_Control (pDX, IDC_CHECK_SYNCHRO,		m_synchro);
	DDX_Control (pDX, IDC_CHECK_CYCLE,			m_cycle);
	DDX_Text	(pDX, IDC_RETARD,				m_err_retard);
	DDX_Text	(pDX, IDC_EDIT_CYCLE,			m_periode);
	DDX_Text	(pDX, IDC_EDIT_TEMPO,			m_tempo);

	DDX_Control	(pDX, IDC_20_8_EtatAntenne1,	EtatAntenne_20_8[0]);
	DDX_Control	(pDX, IDC_20_8_EtatAntenne2,	EtatAntenne_20_8[1]);
	DDX_Control	(pDX, IDC_20_8_EtatAntenne3,	EtatAntenne_20_8[2]);
	DDX_Control	(pDX, IDC_20_8_EtatAntenne4,	EtatAntenne_20_8[3]);
	DDX_Control	(pDX, IDC_20_8_EtatAntenne5,	EtatAntenne_20_8[4]);
	DDX_Control	(pDX, IDC_20_8_EtatAntenne6,	EtatAntenne_20_8[5]);
	DDX_Control	(pDX, IDC_20_8_EtatAntenne7,	EtatAntenne_20_8[6]);
	DDX_Control	(pDX, IDC_20_8_EtatAntenne8,	EtatAntenne_20_8[7]);

	DDX_Control	(pDX, IDC_20_8_EtatPreampli1,	EtatPreampli_20_8[0]);
	DDX_Control	(pDX, IDC_20_8_EtatPreampli2,	EtatPreampli_20_8[1]);
	DDX_Control	(pDX, IDC_20_8_EtatPreampli3,	EtatPreampli_20_8[2]);
	DDX_Control	(pDX, IDC_20_8_EtatPreampli4,	EtatPreampli_20_8[3]);
	DDX_Control	(pDX, IDC_20_8_EtatPreampli5,	EtatPreampli_20_8[4]);
	DDX_Control	(pDX, IDC_20_8_EtatPreampli6,	EtatPreampli_20_8[5]);
	DDX_Control	(pDX, IDC_20_8_EtatPreampli7,	EtatPreampli_20_8[6]);
	DDX_Control	(pDX, IDC_20_8_EtatPreampli8,	EtatPreampli_20_8[7]);

	DDX_Control	(pDX, IDC_20_8_EtatAmpli1,		EtatAmpli_20_8[0]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli2,		EtatAmpli_20_8[1]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli3,		EtatAmpli_20_8[2]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli4,		EtatAmpli_20_8[3]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli5,		EtatAmpli_20_8[4]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli6,		EtatAmpli_20_8[5]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli7,		EtatAmpli_20_8[6]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli8,		EtatAmpli_20_8[7]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli9,		EtatAmpli_20_8[8]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli10,		EtatAmpli_20_8[9]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli11,		EtatAmpli_20_8[10]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli12,		EtatAmpli_20_8[11]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli13,		EtatAmpli_20_8[12]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli14,		EtatAmpli_20_8[13]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli15,		EtatAmpli_20_8[14]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli16,		EtatAmpli_20_8[15]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli17,		EtatAmpli_20_8[16]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli18,		EtatAmpli_20_8[17]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli19,		EtatAmpli_20_8[18]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli20,		EtatAmpli_20_8[19]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli21,		EtatAmpli_20_8[20]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli22,		EtatAmpli_20_8[21]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli23,		EtatAmpli_20_8[22]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli24,		EtatAmpli_20_8[23]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli25,		EtatAmpli_20_8[24]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli26,		EtatAmpli_20_8[25]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli27,		EtatAmpli_20_8[26]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli28,		EtatAmpli_20_8[27]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli29,		EtatAmpli_20_8[28]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli30,		EtatAmpli_20_8[29]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli31,		EtatAmpli_20_8[30]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli32,		EtatAmpli_20_8[31]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli33,		EtatAmpli_20_8[32]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli34,		EtatAmpli_20_8[33]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli35,		EtatAmpli_20_8[34]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli36,		EtatAmpli_20_8[35]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli37,		EtatAmpli_20_8[36]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli38,		EtatAmpli_20_8[37]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli39,		EtatAmpli_20_8[38]);
	DDX_Control	(pDX, IDC_20_8_EtatAmpli40,		EtatAmpli_20_8[39]);

	
	DDX_Control	(pDX, IDC_20_8_1x1,				m_20_8[0][0]);
	DDX_Control	(pDX, IDC_20_8_1x2,				m_20_8[0][1]);
	DDX_Control	(pDX, IDC_20_8_1x3,				m_20_8[0][2]);
	DDX_Control	(pDX, IDC_20_8_1x4,				m_20_8[0][3]);
	DDX_Control	(pDX, IDC_20_8_1x5,				m_20_8[0][4]);
	DDX_Control	(pDX, IDC_20_8_1x6,				m_20_8[0][5]);
	DDX_Control	(pDX, IDC_20_8_1x7,				m_20_8[0][6]);
	DDX_Control	(pDX, IDC_20_8_1x8,				m_20_8[0][7]);
	DDX_Control	(pDX, IDC_20_8_1x9,				m_20_8[0][8]);
	DDX_Control	(pDX, IDC_20_8_1x10,			m_20_8[0][9]);
	DDX_Control	(pDX, IDC_20_8_1x11,			m_20_8[0][10]);
	DDX_Control	(pDX, IDC_20_8_1x12,			m_20_8[0][11]);
	DDX_Control	(pDX, IDC_20_8_1x13,			m_20_8[0][12]);
	DDX_Control	(pDX, IDC_20_8_1x14,			m_20_8[0][13]);
	DDX_Control	(pDX, IDC_20_8_1x15,			m_20_8[0][14]);
	DDX_Control	(pDX, IDC_20_8_1x16,			m_20_8[0][15]);
	DDX_Control	(pDX, IDC_20_8_1x17,			m_20_8[0][16]);
	DDX_Control	(pDX, IDC_20_8_1x18,			m_20_8[0][17]);
	DDX_Control	(pDX, IDC_20_8_1x19,			m_20_8[0][18]);
	DDX_Control	(pDX, IDC_20_8_1x20,			m_20_8[0][19]);

	DDX_Control	(pDX, IDC_20_8_2x1,				m_20_8[1][0]);
	DDX_Control	(pDX, IDC_20_8_2x2,				m_20_8[1][1]);
	DDX_Control	(pDX, IDC_20_8_2x3,				m_20_8[1][2]);
	DDX_Control	(pDX, IDC_20_8_2x4,				m_20_8[1][3]);
	DDX_Control	(pDX, IDC_20_8_2x5,				m_20_8[1][4]);
	DDX_Control	(pDX, IDC_20_8_2x6,				m_20_8[1][5]);
	DDX_Control	(pDX, IDC_20_8_2x7,				m_20_8[1][6]);
	DDX_Control	(pDX, IDC_20_8_2x8,				m_20_8[1][7]);
	DDX_Control	(pDX, IDC_20_8_2x9,				m_20_8[1][8]);
	DDX_Control	(pDX, IDC_20_8_2x10,			m_20_8[1][9]);
	DDX_Control	(pDX, IDC_20_8_2x11,			m_20_8[1][10]);
	DDX_Control	(pDX, IDC_20_8_2x12,			m_20_8[1][11]);
	DDX_Control	(pDX, IDC_20_8_2x13,			m_20_8[1][12]);
	DDX_Control	(pDX, IDC_20_8_2x14,			m_20_8[1][13]);
	DDX_Control	(pDX, IDC_20_8_2x15,			m_20_8[1][14]);
	DDX_Control	(pDX, IDC_20_8_2x16,			m_20_8[1][15]);
	DDX_Control	(pDX, IDC_20_8_2x17,			m_20_8[1][16]);
	DDX_Control	(pDX, IDC_20_8_2x18,			m_20_8[1][17]);
	DDX_Control	(pDX, IDC_20_8_2x19,			m_20_8[1][18]);
	DDX_Control	(pDX, IDC_20_8_2x20,			m_20_8[1][19]);

	DDX_Control	(pDX, IDC_20_8_3x1,				m_20_8[2][0]);
	DDX_Control	(pDX, IDC_20_8_3x2,				m_20_8[2][1]);
	DDX_Control	(pDX, IDC_20_8_3x3,				m_20_8[2][2]);
	DDX_Control	(pDX, IDC_20_8_3x4,				m_20_8[2][3]);
	DDX_Control	(pDX, IDC_20_8_3x5,				m_20_8[2][4]);
	DDX_Control	(pDX, IDC_20_8_3x6,				m_20_8[2][5]);
	DDX_Control	(pDX, IDC_20_8_3x7,				m_20_8[2][6]);
	DDX_Control	(pDX, IDC_20_8_3x8,				m_20_8[2][7]);
	DDX_Control	(pDX, IDC_20_8_3x9,				m_20_8[2][8]);
	DDX_Control	(pDX, IDC_20_8_3x10,			m_20_8[2][9]);
	DDX_Control	(pDX, IDC_20_8_3x11,			m_20_8[2][10]);
	DDX_Control	(pDX, IDC_20_8_3x12,			m_20_8[2][11]);
	DDX_Control	(pDX, IDC_20_8_3x13,			m_20_8[2][12]);
	DDX_Control	(pDX, IDC_20_8_3x14,			m_20_8[2][13]);
	DDX_Control	(pDX, IDC_20_8_3x15,			m_20_8[2][14]);
	DDX_Control	(pDX, IDC_20_8_3x16,			m_20_8[2][15]);
	DDX_Control	(pDX, IDC_20_8_3x17,			m_20_8[2][16]);
	DDX_Control	(pDX, IDC_20_8_3x18,			m_20_8[2][17]);
	DDX_Control	(pDX, IDC_20_8_3x19,			m_20_8[2][18]);
	DDX_Control	(pDX, IDC_20_8_3x20,			m_20_8[2][19]);

	DDX_Control	(pDX, IDC_20_8_4x1,				m_20_8[3][0]);
	DDX_Control	(pDX, IDC_20_8_4x2,				m_20_8[3][1]);
	DDX_Control	(pDX, IDC_20_8_4x3,				m_20_8[3][2]);
	DDX_Control	(pDX, IDC_20_8_4x4,				m_20_8[3][3]);
	DDX_Control	(pDX, IDC_20_8_4x5,				m_20_8[3][4]);
	DDX_Control	(pDX, IDC_20_8_4x6,				m_20_8[3][5]);
	DDX_Control	(pDX, IDC_20_8_4x7,				m_20_8[3][6]);
	DDX_Control	(pDX, IDC_20_8_4x8,				m_20_8[3][7]);
	DDX_Control	(pDX, IDC_20_8_4x9,				m_20_8[3][8]);
	DDX_Control	(pDX, IDC_20_8_4x10,			m_20_8[3][9]);
	DDX_Control	(pDX, IDC_20_8_4x11,			m_20_8[3][10]);
	DDX_Control	(pDX, IDC_20_8_4x12,			m_20_8[3][11]);
	DDX_Control	(pDX, IDC_20_8_4x13,			m_20_8[3][12]);
	DDX_Control	(pDX, IDC_20_8_4x14,			m_20_8[3][13]);
	DDX_Control	(pDX, IDC_20_8_4x15,			m_20_8[3][14]);
	DDX_Control	(pDX, IDC_20_8_4x16,			m_20_8[3][15]);
	DDX_Control	(pDX, IDC_20_8_4x17,			m_20_8[3][16]);
	DDX_Control	(pDX, IDC_20_8_4x18,			m_20_8[3][17]);
	DDX_Control	(pDX, IDC_20_8_4x19,			m_20_8[3][18]);
	DDX_Control	(pDX, IDC_20_8_4x20,			m_20_8[3][19]);

	DDX_Control	(pDX, IDC_20_8_5x1,				m_20_8[4][0]);
	DDX_Control	(pDX, IDC_20_8_5x2,				m_20_8[4][1]);
	DDX_Control	(pDX, IDC_20_8_5x3,				m_20_8[4][2]);
	DDX_Control	(pDX, IDC_20_8_5x4,				m_20_8[4][3]);
	DDX_Control	(pDX, IDC_20_8_5x5,				m_20_8[4][4]);
	DDX_Control	(pDX, IDC_20_8_5x6,				m_20_8[4][5]);
	DDX_Control	(pDX, IDC_20_8_5x7,				m_20_8[4][6]);
	DDX_Control	(pDX, IDC_20_8_5x8,				m_20_8[4][7]);
	DDX_Control	(pDX, IDC_20_8_5x9,				m_20_8[4][8]);
	DDX_Control	(pDX, IDC_20_8_5x10,			m_20_8[4][9]);
	DDX_Control	(pDX, IDC_20_8_5x11,			m_20_8[4][10]);
	DDX_Control	(pDX, IDC_20_8_5x12,			m_20_8[4][11]);
	DDX_Control	(pDX, IDC_20_8_5x13,			m_20_8[4][12]);
	DDX_Control	(pDX, IDC_20_8_5x14,			m_20_8[4][13]);
	DDX_Control	(pDX, IDC_20_8_5x15,			m_20_8[4][14]);
	DDX_Control	(pDX, IDC_20_8_5x16,			m_20_8[4][15]);
	DDX_Control	(pDX, IDC_20_8_5x17,			m_20_8[4][16]);
	DDX_Control	(pDX, IDC_20_8_5x18,			m_20_8[4][17]);
	DDX_Control	(pDX, IDC_20_8_5x19,			m_20_8[4][18]);
	DDX_Control	(pDX, IDC_20_8_5x20,			m_20_8[4][19]);

	DDX_Control	(pDX, IDC_20_8_6x1,				m_20_8[5][0]);
	DDX_Control	(pDX, IDC_20_8_6x2,				m_20_8[5][1]);
	DDX_Control	(pDX, IDC_20_8_6x3,				m_20_8[5][2]);
	DDX_Control	(pDX, IDC_20_8_6x4,				m_20_8[5][3]);
	DDX_Control	(pDX, IDC_20_8_6x5,				m_20_8[5][4]);
	DDX_Control	(pDX, IDC_20_8_6x6,				m_20_8[5][5]);
	DDX_Control	(pDX, IDC_20_8_6x7,				m_20_8[5][6]);
	DDX_Control	(pDX, IDC_20_8_6x8,				m_20_8[5][7]);
	DDX_Control	(pDX, IDC_20_8_6x9,				m_20_8[5][8]);
	DDX_Control	(pDX, IDC_20_8_6x10,			m_20_8[5][9]);
	DDX_Control	(pDX, IDC_20_8_6x11,			m_20_8[5][10]);
	DDX_Control	(pDX, IDC_20_8_6x12,			m_20_8[5][11]);
	DDX_Control	(pDX, IDC_20_8_6x13,			m_20_8[5][12]);
	DDX_Control	(pDX, IDC_20_8_6x14,			m_20_8[5][13]);
	DDX_Control	(pDX, IDC_20_8_6x15,			m_20_8[5][14]);
	DDX_Control	(pDX, IDC_20_8_6x16,			m_20_8[5][15]);
	DDX_Control	(pDX, IDC_20_8_6x17,			m_20_8[5][16]);
	DDX_Control	(pDX, IDC_20_8_6x18,			m_20_8[5][17]);
	DDX_Control	(pDX, IDC_20_8_6x19,			m_20_8[5][18]);
	DDX_Control	(pDX, IDC_20_8_6x20,			m_20_8[5][19]);

	DDX_Control	(pDX, IDC_20_8_7x1,				m_20_8[6][0]);
	DDX_Control	(pDX, IDC_20_8_7x2,				m_20_8[6][1]);
	DDX_Control	(pDX, IDC_20_8_7x3,				m_20_8[6][2]);
	DDX_Control	(pDX, IDC_20_8_7x4,				m_20_8[6][3]);
	DDX_Control	(pDX, IDC_20_8_7x5,				m_20_8[6][4]);
	DDX_Control	(pDX, IDC_20_8_7x6,				m_20_8[6][5]);
	DDX_Control	(pDX, IDC_20_8_7x7,				m_20_8[6][6]);
	DDX_Control	(pDX, IDC_20_8_7x8,				m_20_8[6][7]);
	DDX_Control	(pDX, IDC_20_8_7x9,				m_20_8[6][8]);
	DDX_Control	(pDX, IDC_20_8_7x10,			m_20_8[6][9]);
	DDX_Control	(pDX, IDC_20_8_7x11,			m_20_8[6][10]);
	DDX_Control	(pDX, IDC_20_8_7x12,			m_20_8[6][11]);
	DDX_Control	(pDX, IDC_20_8_7x13,			m_20_8[6][12]);
	DDX_Control	(pDX, IDC_20_8_7x14,			m_20_8[6][13]);
	DDX_Control	(pDX, IDC_20_8_7x15,			m_20_8[6][14]);
	DDX_Control	(pDX, IDC_20_8_7x16,			m_20_8[6][15]);
	DDX_Control	(pDX, IDC_20_8_7x17,			m_20_8[6][16]);
	DDX_Control	(pDX, IDC_20_8_7x18,			m_20_8[6][17]);
	DDX_Control	(pDX, IDC_20_8_7x19,			m_20_8[6][18]);
	DDX_Control	(pDX, IDC_20_8_7x20,			m_20_8[6][19]);

	DDX_Control	(pDX, IDC_20_8_8x1,				m_20_8[7][0]);
	DDX_Control	(pDX, IDC_20_8_8x2,				m_20_8[7][1]);
	DDX_Control	(pDX, IDC_20_8_8x3,				m_20_8[7][2]);
	DDX_Control	(pDX, IDC_20_8_8x4,				m_20_8[7][3]);
	DDX_Control	(pDX, IDC_20_8_8x5,				m_20_8[7][4]);
	DDX_Control	(pDX, IDC_20_8_8x6,				m_20_8[7][5]);
	DDX_Control	(pDX, IDC_20_8_8x7,				m_20_8[7][6]);
	DDX_Control	(pDX, IDC_20_8_8x8,				m_20_8[7][7]);
	DDX_Control	(pDX, IDC_20_8_8x9,				m_20_8[7][8]);
	DDX_Control	(pDX, IDC_20_8_8x10,			m_20_8[7][9]);
	DDX_Control	(pDX, IDC_20_8_8x11,			m_20_8[7][10]);
	DDX_Control	(pDX, IDC_20_8_8x12,			m_20_8[7][11]);
	DDX_Control	(pDX, IDC_20_8_8x13,			m_20_8[7][12]);
	DDX_Control	(pDX, IDC_20_8_8x14,			m_20_8[7][13]);
	DDX_Control	(pDX, IDC_20_8_8x15,			m_20_8[7][14]);
	DDX_Control	(pDX, IDC_20_8_8x16,			m_20_8[7][15]);
	DDX_Control	(pDX, IDC_20_8_8x17,			m_20_8[7][16]);
	DDX_Control	(pDX, IDC_20_8_8x18,			m_20_8[7][17]);
	DDX_Control	(pDX, IDC_20_8_8x19,			m_20_8[7][18]);
	DDX_Control	(pDX, IDC_20_8_8x20,			m_20_8[7][19]);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDLGaad_20_8, CDialog)
	//{{AFX_MSG_MAP(CDLGaad_20_8)
	ON_WM_TIMER()

	ON_BN_CLICKED	(IDC_CDE_INCONUE,	OnComErreur)
	ON_BN_CLICKED	(IDC_DEBUT_TRAME,	OnComErreur)
	ON_BN_CLICKED	(IDC_FIN_TRAME,		OnComErreur)
	ON_EN_KILLFOCUS	(IDC_RETARD,		OnComErreur)
	ON_BN_CLICKED	(IDC_PAS_REPONSE,	OnComErreur)

	ON_BN_CLICKED	(IDC_20_4_Valider,	OnButtonValider)
	// TODO : integrer les evenements lies a l'interface
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
void CDLGaad_20_8::OnAide()
{
	int			iResult;
	CDlgAide	win;

	iResult = win.Charge(glob_HELP_AAD_20_4,"Matrice AAD 20x4");
	if(iResult >=  0)
	{
		win.DoModal();
	}
}

/* **************************************************************************
METHODE :		OnInitDialog() 
TRAITEMENT:		Initialisation de la boite de dialogue
***************************************************************************	*/
BOOL CDLGaad_20_8::OnInitDialog() 
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

	// Liste des commandes de sequence
	// *******************************

	// Custom control
	// **************
	m_activite.SubclassDlgItem(IDC_ACTIVITE,this);

	
	// Initialisation de la face avant
	// *******************************
	for(i=0; i< ((CEquipAAD*)equip)->NB_ANTENNES; i++)
	{
		EtatAntenne_20_8[i].AddString("Absent");
		EtatAntenne_20_8[i].AddString("Correct");
		EtatAntenne_20_8[i].AddString("AlimHS");
		EtatAntenne_20_8[i].AddString("Surchauffe");
		switch (((CEquipAAD*)equip)->TAB_ANTENNE[i])
		{
		case ABSENT0:
			EtatAntenne_20_8[i].SetCurSel(0);
			break;
		case CORRECT0:
			EtatAntenne_20_8[i].SetCurSel(1);
			break;
		case ALIM_HS0:
			EtatAntenne_20_8[i].SetCurSel(2);
			break;
		case SURCHAUFFE0:
			EtatAntenne_20_8[i].SetCurSel(3);
			break;
		default:
			break;
		}
	}

	for(i=0; i<((CEquipAAD*)equip)->NB_PREAMPLIS; i++)
	{
		EtatPreampli_20_8[i].AddString("Absent");
		EtatPreampli_20_8[i].AddString("Correct");
		EtatPreampli_20_8[i].AddString("Defaut");
		switch (((CEquipAAD*)equip)->TAB_PREAMPLI[i])
		{
		case ABSENT1:
			EtatPreampli_20_8[i].SetCurSel(0);
			break;
		case CORRECT1:
			EtatPreampli_20_8[i].SetCurSel(1);
			break;
		case DEFAUT1:
			EtatPreampli_20_8[i].SetCurSel(2);
			break;
		default:
			break;
		}
	}

	for(i=0; i<((CEquipAAD*)equip)->NB_AMPLIS; i++)
	{
		EtatAmpli_20_8[i].AddString("Absent");
		EtatAmpli_20_8[i].AddString("Correct");
		EtatAmpli_20_8[i].AddString("Defaut");
		switch (((CEquipAAD*)equip)->TAB_AMPLI[i])
		{
		case ABSENT1:
			EtatAmpli_20_8[i].SetCurSel(0);
			break;
		case CORRECT1:
			EtatAmpli_20_8[i].SetCurSel(1);
			break;
		case DEFAUT1:
			EtatAmpli_20_8[i].SetCurSel(2);
			break;
		default:
			break;
		}
	}

	UpdateData(FALSE);

	return TRUE;
}


/* **************************************************************************
METHODE :		GenerateurAuto()
TRAITEMENT:		Effectue les variations automatiques de certains composants
***************************************************************************	*/
void CDLGaad_20_8::GenerateurAuto()
{
	// Aucune variation automatique sur cet equipement
}

/* **************************************************************************
METHODE :		OnTimer(UINT nIDEvent) 
TRAITEMENT:		Rafraichissement de l'ecran de controle
***************************************************************************	*/
void CDLGaad_20_8::OnTimer(UINT nIDEvent) 
{
	int	 val, i, j;
	//char buf[10];			//2009-11-27

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

	for(i=0; i<((CEquipAAD*)equip)->NB_ANTENNES; i++)
	{
		for(j=0; j<NB_VOIES; j++)
		{
			if(((CEquipAAD*)equip)->MATRICE_20_4[i][j] == true)
			{
				m_20_8[i][j].SetBitmap(bmp_BLACK);
			}
			else
			{
				m_20_8[i][j].SetBitmap(bmp_WHITE);
			}
		}
	}

	UpdateData(FALSE);
}

/* **************************************************************************
METHODE :		OnComErreur()
TRAITEMENT:		
***************************************************************************	*/
void CDLGaad_20_8::OnComErreur() 
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
void CDLGaad_20_8::Verrouille(BOOL etat)
{
	// Pas de verouillage sur cet equipement
}

/* **************************************************************************
METHODE :		OnButtonValider()
TRAITEMENT:		Evenement bouton Valider
***************************************************************************	*/
void CDLGaad_20_8::OnButtonValider()
{
	int i, temp;

	for(i=0; i< ((CEquipAAD*)equip)->NB_ANTENNES ; i++)
	{
		temp = EtatAntenne_20_8[i].GetCurSel();
		switch (temp)
		{
			// ABSENT0
		case 0:
			((CEquipAAD*)equip)->ChgtEtatAntenne(i, 0);
			break;
		// CORRECT0
		case 1:
			((CEquipAAD*)equip)->ChgtEtatAntenne(i, 1);
			break;
		// ALIM_HS0
		case 2:
			((CEquipAAD*)equip)->ChgtEtatAntenne(i, 2);
			break;
		// SURCHAUFFE0
		case 3:
			((CEquipAAD*)equip)->ChgtEtatAntenne(i, 3);
			break;
		default:
			break;
		}
	}

	for(i=0; i< ((CEquipAAD*)equip)->NB_PREAMPLIS; i++)
	{
		temp = EtatPreampli_20_8[i].GetCurSel();
		switch (temp)
		{
		// ABSENT1
		case 0:
			((CEquipAAD*)equip)->ChgtEtatPreampli(i, 0);
			break;
		// CORRECT1
		case 1:
			((CEquipAAD*)equip)->ChgtEtatPreampli(i, 1);
			break;
		// DEFAUT1
		case 2:
			((CEquipAAD*)equip)->ChgtEtatPreampli(i, 2);
			break;
		default:
			break;
		}
	}

	for(i=0; i< ((CEquipAAD*)equip)->NB_AMPLIS ; i++)
	{
		temp = EtatAmpli_20_8[i].GetCurSel();
		switch (temp)
		{
		// ABSENT1
		case 0:
			((CEquipAAD*)equip)->ChgtEtatAmpli(i, 0);
			break;
		// CORRECT1
		case 1:
			((CEquipAAD*)equip)->ChgtEtatAmpli(i, 1);
			break;
		// DEFAUT1
		case 2:
			((CEquipAAD*)equip)->ChgtEtatAmpli(i, 2);
			break;
		default:
			break;
		}
	}
}