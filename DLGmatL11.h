// CDLGmatL11.h: interface for the CDLGmatL11 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGMATL11_H__6628235E_9CCF_49EE_97CB_AD2BC75A1DF3__INCLUDED_)
#define AFX_DLGMATL11_H__6628235E_9CCF_49EE_97CB_AD2BC75A1DF3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

class CDLGmatL11:public CDlgEquip
{
protected:
	CInter		m_activite;
	CDiode		m_incident;
	CDiode		m_info;

public:
	//{{AFX_DATA(CDLGmatL11)
	enum { IDD = IDD_L11 };

	CButton		m_l11[2][14];
	CButton		m_local;
	CString		m_distant;
	CButton		m_dump;
	CComboBox	m_erreur;
	HBITMAP		bmp_BLACK;
	HBITMAP		bmp_WHITE;
	
	CListBox	m_liste_message;
	CButton		m_synchro;
	CButton		m_cycle;
	CString		m_err_retard;
	CString		m_periode;
	CString		m_tempo;
	//}}AFX_DATA

public:
// standard constructor
	CDLGmatL11(CWnd* pParent = NULL);
	virtual void GenerateurAuto();

// Overrides
	//{{AFX_VIRTUAL(CDLGmatL11)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
// Implementation
	//{{AFX_MSG(CDLGmatL11)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnComErreur();
	void		 OnLocal();
	void		 OnDump();
	void		 OnErreur();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void OnAide();
	void Verrouille(BOOL etat);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMATL11_H__6628235E_9CCF_49EE_97CB_AD2BC75A1DF3__INCLUDED_)
