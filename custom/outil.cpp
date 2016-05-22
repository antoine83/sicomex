/* **************************************************************************
FICHIER :	Outil.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe COutil
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "outil.h"

#include "Equip\paramSim.h"
#include "DlgOutil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

const int ITEM_HEIGHT = 36;
const int ITEM_MARGE = 3;
const int TAILLE_ICONE = 40;

/////////////////////////////////////////////////////////////////////////////
// COutil

COutil::COutil()
{
	bmp_1 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_ACCORD));
	bmp_2 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_STD_HF));
	bmp_3 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_AUDIO));
	bmp_4 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_EMET_HF));

	bmp_5 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_EMREC_UHF));
	bmp_6 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_EMREC_UHF));

	bmp_7 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_RECEP_HF));
	bmp_8 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_RECEP_HF));
	bmp_9 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_RECEP_HF));
	
	bmp_10 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_EMET_HF));
	bmp_11 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_EMET_HF));
	bmp_12 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_EMET_HF));

	bmp_13 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_EMET_HF));
	bmp_14 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_EMET_HF));
	bmp_15 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_EMET_HF));

	bmp_16 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_RECEP_HF));

	bmp_17 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_AAD_20_4));
	bmp_18 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_AAD_20_8));

	bmp_19 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_MATSPIN));
	bmp_20 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_MATL11));

	bmp_21 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_CA_150));
	bmp_22 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_CA_150));

	bmp_23 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_KY58));
	bmp_24 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_ANDVT));

	bmp_25 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_COMMUTATION_MATRIX));

	bmp_26 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_KY58));
	bmp_27 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_ANDVT));
	bmp_28 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_TOR));

	bmp_29 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_TEST));

	bmp_30 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_MDM_1752));
	bmp_31 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_ED42));
	bmp_32 = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_EQP_M3SR));
}

COutil::~COutil()
{
	DeleteObject(bmp_1);
	DeleteObject(bmp_2);
	DeleteObject(bmp_3);
	DeleteObject(bmp_4);
	DeleteObject(bmp_5);
	DeleteObject(bmp_6);
	DeleteObject(bmp_7);
	DeleteObject(bmp_8);
	DeleteObject(bmp_9);
	DeleteObject(bmp_10);
	DeleteObject(bmp_11);
	DeleteObject(bmp_12);
	DeleteObject(bmp_13);
	DeleteObject(bmp_14);
	DeleteObject(bmp_15);
	DeleteObject(bmp_16);
	DeleteObject(bmp_17);
	DeleteObject(bmp_18);
	DeleteObject(bmp_19);
	DeleteObject(bmp_20);
	DeleteObject(bmp_21);
	DeleteObject(bmp_22);
	DeleteObject(bmp_23);
	DeleteObject(bmp_24);
	DeleteObject(bmp_25);
	DeleteObject(bmp_26);
	DeleteObject(bmp_27);
	DeleteObject(bmp_28);
	DeleteObject(bmp_29);
	DeleteObject(bmp_30);
	DeleteObject(bmp_31);
	DeleteObject(bmp_32);
}


BEGIN_MESSAGE_MAP(COutil, CListBox)
	//{{AFX_MSG_MAP(COutil)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
void COutil::MeasureItem(LPMEASUREITEMSTRUCT lpMIS)
{
	lpMIS->itemHeight = ITEM_HEIGHT;
}

void COutil::DrawItem(LPDRAWITEMSTRUCT lpDIS)
{
	CDC* pDC = CDC::FromHandle(lpDIS->hDC);
	HDC  hdc = CreateCompatibleDC(lpDIS->hDC);

	RECT	rect = lpDIS->rcItem;
	RECT	rect_icone;

	rect.left += ITEM_MARGE;
	rect.top += ITEM_MARGE;
	rect.right -= ITEM_MARGE;
	rect.bottom -= ITEM_MARGE;

	rect_icone = rect;
	rect_icone.left = rect.left + ITEM_MARGE;
	rect_icone.top = rect.top + ITEM_MARGE;
	rect_icone.right = rect.right - ITEM_MARGE;
	rect_icone.bottom = rect.bottom - ITEM_MARGE;

	rect_icone.right = rect.left + ITEM_HEIGHT-2*ITEM_MARGE;


// A redessiner
	if (lpDIS->itemAction & ODA_DRAWENTIRE)	// A redessiner
	{
		switch (((CIcone*)(lpDIS->itemData))->Equip())
		{
			case EQP_BOITE_ACCORD:
				SelectObject(hdc,bmp_1);
				break;
			case EQP_STANDARD_HF:
				SelectObject(hdc,bmp_2);
				break;
			case EQP_AUDIO_TTY:
				SelectObject(hdc,bmp_3);
				break;

			case EQP_TRC1225M:
				SelectObject(hdc,bmp_4);
				break;

			case EQP_TRBM18A:
				SelectObject(hdc,bmp_5);
				break;
			case EQP_TRBM18C:
				SelectObject(hdc,bmp_6);
				break;

			case EQP_TRC1241_FF:
				SelectObject(hdc,bmp_7);
				break;

			case EQP_TRC1241_L11:
				SelectObject(hdc,bmp_8);
				break;
			case EQP_TRC1241_SPIN:
				SelectObject(hdc,bmp_9);
				break;
			case EQP_TRC1236_FF:
				SelectObject(hdc,bmp_10);
				break;
			case EQP_TRC1236_L11:
				SelectObject(hdc,bmp_11);
				break;
			case EQP_TRC1236_SPIN:
				SelectObject(hdc,bmp_12);
				break;

			case EQP_TRC1237_FF:
				SelectObject(hdc,bmp_13);
				break;
			case EQP_TRC1237_L11:
				SelectObject(hdc,bmp_14);
				break;
			case EQP_TRC1237_SPIN:
				SelectObject(hdc,bmp_15);
				break;

			case EQP_TRC251:
				SelectObject(hdc,bmp_16);
				break;
			
			case AAD_20_4:
				SelectObject(hdc,bmp_17);
				break;
			case AAD_20_8:
				SelectObject(hdc,bmp_18);
				break;
			
			case MATRICE_SPIN:
				SelectObject(hdc,bmp_19);
				break;
			case MATRICE_L11:
				SelectObject(hdc,bmp_20);
				break;

			case CA_150_MASTER:
				SelectObject(hdc,bmp_21);
				break;
			case CA_150_SLAVE:
				SelectObject(hdc,bmp_22);
				break;
			case KY58:
				SelectObject(hdc,bmp_23);
				break;
			case ANDVT:
				SelectObject(hdc,bmp_24);
				break;
			case COMMUTATION_MATRIX:
				SelectObject(hdc,bmp_25);
				break;
			case TOR_KY58:
				SelectObject(hdc,bmp_26);
				break;
			case TOR_ANDVT:
				SelectObject(hdc,bmp_27);
				break;
			case TOR_CARD:
				SelectObject(hdc,bmp_28);
				break;

			case Test:
				SelectObject(hdc,bmp_29);
				break;

			case MDM_TRC1752:
				SelectObject(hdc,bmp_30);
				break;

			case ED42:
				SelectObject(hdc,bmp_31);
				break;
		}

		StretchBlt(lpDIS->hDC,
				rect_icone.left,
				rect_icone.top,
				rect_icone.right - rect_icone.left,
				rect_icone.bottom - rect_icone.top,
				hdc,
				0,
				0,
				TAILLE_ICONE,						//	 Taille des icone
				TAILLE_ICONE,						//
				SRCCOPY);


		rect.left += ITEM_HEIGHT;
		pDC->DrawText( ((CIcone*)(lpDIS->itemData))->Libel(),
			 (int)strlen(((CIcone*)(lpDIS->itemData))->Libel()),
			 &rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		rect.left -= ITEM_HEIGHT;

		if(((CIcone*)(lpDIS->itemData))->Actif())
			Profondeur(&rect_icone,pDC,TRUE);
		else
			Profondeur(&rect_icone,pDC,FALSE);
	}

// dessine la selection
	if ((lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & (ODA_SELECT | ODA_DRAWENTIRE)))
	{
//		((CIcone*)(lpDIS->itemData))->Active(TRUE);
		Profondeur(&rect_icone,pDC,TRUE);
	}

// dessine la deselection
	if (!(lpDIS->itemState & ODS_SELECTED) &&
		(lpDIS->itemAction & ODA_SELECT))
	{
//		((CIcone*)(lpDIS->itemData))->Active(FALSE);
		Profondeur(&rect_icone,pDC,FALSE);
	}
	
	if(hdc != NULL) DeleteDC(hdc);
	pDC->DeleteTempMap();
}

void COutil::Profondeur(RECT *rect,CDC *pDC,BOOL enfonce)
{
	CPen blanc(PS_SOLID | PS_JOIN_ROUND,1,RGB(250,250,250));
	CPen noir(PS_SOLID | PS_JOIN_ROUND,1,RGB(50,50,50));

	if(!enfonce)
		pDC->SelectObject(&blanc);
	else
		pDC->SelectObject(&noir);
	pDC->MoveTo(rect->left,rect->bottom);
	pDC->LineTo(rect->left,rect->top);
	pDC->LineTo(rect->right,rect->top);

	if(!enfonce)
		pDC->SelectObject(&noir);
	else
		pDC->SelectObject(&blanc);
	pDC->LineTo(rect->right,rect->bottom);
	pDC->LineTo(rect->left,rect->bottom);

}
