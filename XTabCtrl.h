#if !defined(AFX_CXTabCtrl_H__A11951B3_2F95_11D3_A896_00A0C9B6FB28__INCLUDED_)
#define AFX_CXTabCtrl_H__A11951B3_2F95_11D3_A896_00A0C9B6FB28__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// CXTabCtrl.h : header file
//

template <class GENERIC_DLGCOLOR = CWnd>
class CTplDlgColor : public GENERIC_DLGCOLOR
{
public:

	CTplDlgColor(UINT nID=0,CWnd* pParent=NULL) :GENERIC_DLGCOLOR(nID,pParent)
	{
	/* HBRUSH   */  m_HbrClrCtlBk=::CreateSolidBrush(::GetSysColor(COLOR_BTNFACE));  
	/* COLORREF */  m_ClrCtlText= RGB(0, 0, 0) ;
	}
	//---------------------------------------------------------------------------------
	~CTplDlgColor()
	{
		if(m_HbrClrCtlBk) ::DeleteObject(m_HbrClrCtlBk);
	}

	//---------------------------------------------------------------------------------
	void SetDialogBkColor(COLORREF clrCtlBk = RGB(192, 192, 192),
						  COLORREF clrCtlText = RGB(0, 0, 0) )
	{ 
		//m_HbrClrCtlBk est à null dans le constructeur
		if(m_HbrClrCtlBk) ::DeleteObject(m_HbrClrCtlBk); 
		m_HbrClrCtlBk = ::CreateSolidBrush(clrCtlBk);  
		m_ClrCtlText    = clrCtlText;
		/* COLORREF */m_ClrCtlBk= clrCtlBk;
	}

	//---------------------------------------------------------------------------------
	HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor) 
	{
		HBRUSH hbr;
		
		if(pWnd->m_hWnd == m_hWnd)
		hbr= GENERIC_DLGCOLOR::OnCtlColor(pDC, pWnd, nCtlColor);	// for dialogs
		else hbr= GENERIC_DLGCOLOR::OnCtlColor(pDC, this, nCtlColor);		// send reflect message

	/* CTLCOLOR_BTN         button control
	   CTLCOLOR_DLG         dialog box
	   CTLCOLOR_EDIT        edit control
	   CTLCOLOR_LISTBOX     list box
	   CTLCOLOR_MSGBOX      message box
	   CTLCOLOR_SCROLLBAR   scroll bar
	   CTLCOLOR_STATIC      static text, frame, or rectangle 
	*/

	// TODO: Change any attributes of the DC here

	// par exemple en fonction de nCtlColor voir doc.
		switch(nCtlColor)
		{
			// Intercepte le message pour la dialogue et les statics. 
			case CTLCOLOR_DLG:
			case CTLCOLOR_STATIC  :
					//  Fixe la couleur d’ecriture du texte
					pDC->SetTextColor(m_ClrCtlText);
					// enventuellement suivant les cas
					// pDC->pDC->SetBkColor(m_ClrCtlBk);
					// Fixe le fond en transparent  pour le texte 
					// à ne pas faire pour un edit.
					pDC->SetBkMode(TRANSPARENT);
					// retourne le handle de la brush pour le fond si il existe.
					if(m_HbrClrCtlBk ) hbr = m_HbrClrCtlBk;
					break;
		 }
		// TODO: Return a different brush if the default is not desired
		return hbr;
	}
	//---------------------------------------------------------------------------------
	virtual BOOL OnWndMsg(UINT message, WPARAM wParam, LPARAM lParam, LRESULT* pResult)
	{
		if(message==WM_CTLCOLOR)
		{		
			_AFX_CTLCOLOR* pCtl = (_AFX_CTLCOLOR*)lParam;
			CDC dcTemp; dcTemp.m_hDC = pCtl->hDC;
			CWnd wndTemp; wndTemp.m_hWnd = pCtl->hWnd;
			UINT nCtlType = pCtl->nCtlType;
			
			if(nCtlType==CTLCOLOR_STATIC)
			{
				char szClassName[30];
				if(GetClassName(pCtl->hWnd,szClassName,sizeof(szClassName)))
					if(strcmp(szClassName,"Static")) nCtlType=0;
			}
			if(nCtlType==CTLCOLOR_DLG || nCtlType==CTLCOLOR_STATIC)
			{								
				HBRUSH hbr = OnCtlColor(&dcTemp, &wndTemp, nCtlType);
				// fast detach of temporary objects
				dcTemp.m_hDC = NULL;
				wndTemp.m_hWnd = NULL;	
				*pResult = (LRESULT)hbr;
				return TRUE;
			}
			// fast detach of temporary objects
			dcTemp.m_hDC = NULL;
			wndTemp.m_hWnd = NULL;	
		}
		return GENERIC_DLGCOLOR::OnWndMsg(message, wParam, lParam, pResult);
	 }
	//---------------------------------------------------------------------------------

	private:
	struct _AFX_CTLCOLOR
	{
		HWND hWnd;
		HDC hDC;
		UINT nCtlType;
	};

	HBRUSH     m_HbrClrCtlBk;
	COLORREF   m_ClrCtlText;
	COLORREF   m_ClrCtlBk;
	
};

/////////////////////////////////////////////////////////////////////////////
// CXTabCtrl window
#include <afxtempl.h>
class CXTabCtrl : public CTabCtrl
{
// Construction
public:
	DECLARE_DYNAMIC(CXTabCtrl)

	CXTabCtrl();

	

// Attributes
public:
	BOOL m_bAutoPannelSize;
	COLORREF m_crBackColor;
	BOOL	 m_bFirstBackColor;	
// Operations

public:
	void AddTab(CWnd* pWnd, LPTSTR lpszCaption, int iImage =0);
	void EnableTab(int iIndex, BOOL bEnable = TRUE);
	BOOL SelectTab(int iIndex);
	void DeleteAllTabs();
	void DeleteTab(int iIndex);
	void SetTopLeftCorner(CPoint pt);
	BOOL IsTabEnabled(int iIndex);

	void SetDisabledColor(COLORREF cr);
	void SetSelectedColor(COLORREF cr);
	void SetNormalColor(COLORREF cr);
	void SetMouseOverColor(COLORREF cr);
	void SetAutoSizePannel(BOOL bEnable=TRUE){m_bAutoPannelSize=bEnable;}
	// fixe la couleur de fond de la fenêtre
	void SetBackGroundColor(COLORREF cBackColor);
	// fixe la couleur du bouton d'onglet non selectionné
	void SetNoSelBackGroundColor(COLORREF cBackColor);

	void ReSizeCurPannel();

	// nombre d'onglet.
	int GetCount(){ return m_arrayStatusTab.GetSize();}

	// renvoie un pointeur sur la dialogue correspondant a l'index.
	CDialog *GetDialogCtrl(int nIndex);

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CXTabCtrl)
	protected:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CXTabCtrl();

	// Generated message map functions
protected:
	CArray<BOOL, BOOL> m_arrayStatusTab; //** enabled Y\N
	int m_iSelectedTab;
	POINT m_ptTabs;
	COLORREF m_crSelected;
	COLORREF m_crDisabled;
	COLORREF m_crNormal;
	COLORREF m_crMouseOver;
	COLORREF m_crNoBackColor;

	int m_iIndexMouseOver;
	
	bool m_bMouseOver;
	bool m_bColorMouseOver;
	bool m_bColorNormal;
	bool m_bColorDisabled;
	bool m_bColorSelected;
	bool m_bInit;
	//{{AFX_MSG(CXTabCtrl)
	afx_msg BOOL OnSelchange(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg BOOL OnSelchanging(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSize(UINT nType, int cx, int cy);	
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
//	afx_msg HBRUSH CtlColor(CDC* pDC, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CXTabCtrl_H__A11951B3_2F95_11D3_A896_00A0C9B6FB28__INCLUDED_)

