// MyEdit.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "MyEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMyEdit

CMyEdit::CMyEdit()
{
}

CMyEdit::~CMyEdit()
{
}


BEGIN_MESSAGE_MAP(CMyEdit, CEdit)
	//{{AFX_MSG_MAP(CMyEdit)
		ON_WM_CHAR()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMyEdit message handlers

void CMyEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{

	if( (nChar != '-') && (nChar < 48 || nChar >57 ) && (nChar != 8) )
    {
        return;
    }

	CEdit::OnChar(nChar, nRepCnt, nFlags);
}

// Intercepter la touche [Entée]
BOOL CMyEdit::PreTranslateMessage(MSG* pMsg)
{
    if(pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_RETURN)
    {
		return TRUE;
    }

    return CEdit::PreTranslateMessage(pMsg);
}
