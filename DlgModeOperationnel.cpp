// DlgModeOperationnel.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgModeOperationnel.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// DlgModeOperationnel dialog


DlgModeOperationnel::DlgModeOperationnel(CWnd* pParent /*=NULL*/)
	: CDialog(DlgModeOperationnel::IDD, pParent)
{
	//{{AFX_DATA_INIT(DlgModeOperationnel)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT
}


void DlgModeOperationnel::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DlgModeOperationnel)
		// NOTE: the ClassWizard will add DDX and DDV calls here
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DlgModeOperationnel, CDialog)
	//{{AFX_MSG_MAP(DlgModeOperationnel)
		// NOTE: the ClassWizard will add message map macros here
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DlgModeOperationnel message handlers
