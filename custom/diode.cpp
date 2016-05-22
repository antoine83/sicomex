/* **************************************************************************
FICHIER :	Diode.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDiode
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "diode.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

CDiode::CDiode()
{
	etat = ETAT_OFF;
	bmp_on = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_DIODE_ON));
	bmp_off = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_DIODE_OFF));
	bmp_err = LoadBitmap(AfxGetApp()->m_hInstance,MAKEINTRESOURCE(IDB_DIODE_ERR));
}

CDiode::~CDiode()
{
	BOOL	bResult;

	bResult = DeleteObject(bmp_on);
	bResult = DeleteObject(bmp_off);
	bResult = DeleteObject(bmp_err);
}

const BOOL	CDiode::Retourne_etat()
{
	return etat;
}

void CDiode::Positionne_etat(int valeur)
{
	if(valeur == ETAT_ON ||	valeur == ETAT_OFF || valeur == ETAT_ERR)
	{
			etat = valeur;
			RedrawWindow();
	}
}


BEGIN_MESSAGE_MAP(CDiode, CButton)
	//{{AFX_MSG_MAP(CDiode)
		// NOTE - the ClassWizard will add and remove mapping macros here.
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CInter message handlers

void CDiode::DrawItem(LPDRAWITEMSTRUCT lpDraw) 
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

