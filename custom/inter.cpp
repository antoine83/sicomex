/* **************************************************************************
FICHIER :	Inter.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CInter
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "inter.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CInter::CInter()
{
	etat = FALSE;
	bmp_on = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_INTER_ON));
	bmp_off = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_INTER_OFF));
}

CInter::~CInter()
{
	BOOL	bResult;
	bResult = DeleteObject(bmp_on);
	bResult = DeleteObject(bmp_off);
}

const BOOL	CInter::Retourne_etat()
{
	return etat;
}

void	CInter::Positionne_etat(BOOL valeur)
{
	etat = valeur;
	RedrawWindow();
}


BOOL	CInter::Inverse_etat()
{
	etat = !etat;
	RedrawWindow();
	return etat;
}


BEGIN_MESSAGE_MAP(CInter, CButton)
	//{{AFX_MSG_MAP(CInter)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CInter message handlers

void CInter::DrawItem(LPDRAWITEMSTRUCT lpDraw) 
{
	HDC  hdc = CreateCompatibleDC(lpDraw->hDC);

	if(etat)
		SelectObject(hdc,bmp_on);
	else
		SelectObject(hdc,bmp_off);
	
	StretchBlt(lpDraw->hDC,
				lpDraw->rcItem.left,
				lpDraw->rcItem.top,
				lpDraw->rcItem.right - lpDraw->rcItem.left,
				lpDraw->rcItem.bottom - lpDraw->rcItem.top,
				hdc,
				0,0,LARG_BMP,HAUT_BMP,
				SRCCOPY);

	DeleteDC(hdc);

}
