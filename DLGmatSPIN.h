// DLGmatSPIN.h: interface for the CDLGmatSPIN class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGMATSPIN_H__77B3D00D_2412_42DE_B608_04BDD8F2A3B7__INCLUDED_)
#define AFX_DLGMATSPIN_H__77B3D00D_2412_42DE_B608_04BDD8F2A3B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

class CDLGmatSPIN:public CDlgEquip
{
protected:
	CInter		m_activite;
	CDiode		m_incident;
	CDiode		m_info;

public:
	//{{AFX_DATA(CDLGmatSPIN)
	enum { IDD = IDD_SPIN };

	CButton		m_spin[4][9];
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
	CDLGmatSPIN(CWnd* pParent = NULL);
	virtual void GenerateurAuto();

// Overrides
	//{{AFX_VIRTUAL(CDLGmatSPIN)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
// Implementation
	//{{AFX_MSG(CDLGmatSPIN)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnComErreur();
	void		 OnLocal();
	void		 OnDump();
	void		 OnErreur();
	// TODO : integrer les fonctions liees aux evenements
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void OnAide();
	void Verrouille(BOOL etat);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMATSPIN_H__77B3D00D_2412_42DE_B608_04BDD8F2A3B7__INCLUDED_)
