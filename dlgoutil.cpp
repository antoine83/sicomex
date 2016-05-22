/* **************************************************************************
FICHIER :	DlgOutil.CPP		 		AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgOutil
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "DlgOutil.h"

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgOutil dialog


CDlgOutil::CDlgOutil(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgOutil::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgOutil)
	//}}AFX_DATA_INIT

}

void CDlgOutil::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgOutil)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgOutil, CDialog)
	//{{AFX_MSG_MAP(CDlgOutil)
	ON_WM_SIZE()
	ON_LBN_SELCHANGE(IDC_BARRE, OnSelchangeBarre)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlgOutil message handlers

BOOL CDlgOutil::OnInitDialog() 
{
	CDialog::OnInitDialog();

	VERIFY(outil.SubclassDlgItem(IDC_BARRE, this));
  
	PostMessage(WM_SIZE);		// Redimensionnement du jouranl
	
	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgOutil::OnSize(UINT nType, int cx, int cy) 
{
	RECT	dim;

	CDialog::OnSize(nType, cx, cy);

	GetClientRect(&dim);
	if(outil.m_hWnd != NULL)
		outil.MoveWindow(&dim,TRUE);

	
}

CIcone *CDlgOutil::Ajoute_icone(int typ,char *titre,BOOL etat,CEquip *lien)
{
	int	index;
	CIcone	*element;

	element = new CIcone(typ,titre,etat,lien);

	index = ListeIcone.Add(element);
	outil.AddString((LPCTSTR)element);
	outil.SetSel(index,etat);
	
	return element;
}

/* **********************************************************************
METHODE :		ChangeNomcone(char *titre BOOL etat)
TRAITEMENT:		Ajoute un icone dans la barre d'outil et retourne handle
***********************************************************************	*/
void CDlgOutil::ChangeNomIcone(CIcone *element,char *titre,BOOL etat)
{
	element->ChangeLibel(titre);

	int index = 0;
	int	iResult;

	while(index < ListeIcone.GetSize())
	{
		if (element == ListeIcone.GetAt(index))
		{
			element->Active(etat);
			iResult = outil.SetSel(index,etat);

			break;
		}
		index++;
	}
	outil.RedrawWindow();
}

void CDlgOutil::Retire_icone(CIcone *element)
{
	int index = 0;
	while(index < ListeIcone.GetSize())
	{
		if (element==ListeIcone.GetAt(index))
		{
			outil.DeleteString(index);
			ListeIcone.RemoveAt(index,1);
			delete element;

			break;
		}
		index++;
	}
}

void CDlgOutil::MasqueEcran(CIcone* element)
{
	int index = 0;
	int	iResult;

	while(index < ListeIcone.GetSize())
	{
		if (element == ListeIcone.GetAt(index))
		{
			element->Active(FALSE);
			iResult = outil.SetSel(index,FALSE);

			break;
		}
		index++;
	}
}

void CDlgOutil::OnSelchangeBarre() 
{
	CIcone	*element;
	int	index = outil.GetCaretIndex();

	element	=	(CIcone*)ListeIcone.GetAt(index);
	element->Active(!(element->Actif()));
}

BOOL CDlgOutil::DestroyWindow() 
{
	int index = ListeIcone.GetSize();

	outil.ResetContent();
	while(index--)
		delete ListeIcone.GetAt(index);
	
	ListeIcone.RemoveAll();
	return CDialog::DestroyWindow();
}
