// CDLGTest.h: interface for the CDLGTest class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGTEST1_H__133DFD48_782F_4545_AA8D_5AF4DD3EF4FB__INCLUDED_)
#define AFX_DLGTEST1_H__133DFD48_782F_4545_AA8D_5AF4DD3EF4FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

class CDLGTest : public CDlgEquip
{
protected:
	CInter		m_activite;
	CDiode		m_incident;
	CInter		m_info;

public:
	CDLGTest(CWnd* pParent = NULL);
	void GenerateurAuto();

	//{{AFX_DATA(CDLGTest)
	enum { IDD = IDD_TEST };

	CButton		m_debut_CR;
	CButton		m_debut_LF;
	CButton		m_debut_SUB;
	CButton		m_fin_CR;
	CButton		m_fin_LF;
	CButton		m_fin_SUB;

	CButton		m_benvoyer;
	CEdit		m_envoyer;
	CButton		m_brecevoir;
	CListBox	m_recevoir;
	
	CListBox	m_liste_message;
	CButton		m_synchro;
	CButton		m_cycle;
	CButton		m_statut_envoi;
	CButton		m_statut_arret;
	CButton		m_ajout_msg;
	CButton		m_retire_msg;
	CString		m_err_retard;
	CString		m_periode;
	CString		m_tempo;
	//}}AFX_DATA


// Overrides
	//{{AFX_VIRTUAL(CDLGTest)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CDLGTest)
	afx_msg void	OnComErreur();
	virtual BOOL	OnInitDialog();
	void			OnBEnvoi();
	void			OnReception();
	void			OnBReception();
	void			OnDebutCR();
	void			OnDebutLF();
	void			OnDebutSUB();
	void			OnFinCR();
	void			OnFinLF();
	void			OnFinSUB();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void OnAide();
	void Verrouille(BOOL etat);
	//void GenerateurAuto();
	void OnTimer(UINT nIDEvent);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEST1_H__133DFD48_782F_4545_AA8D_5AF4DD3EF4FB__INCLUDED_)
