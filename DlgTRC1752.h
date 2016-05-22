#if !defined(AFX_DLGTRC1752_H__D8122371_3495_4660_BCF1_A889A4EB5B65__INCLUDED_)
#define AFX_DLGTRC1752_H__D8122371_3495_4660_BCF1_A889A4EB5B65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752.h : header file
//

#include "DlgEquip.h"

#include "XTabCtrl.h"

#include "DlgTRC1752_MOD.h"

#include "custom\inter.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752 dialog

class CDlgTRC1752 : public CDlgEquip
{
// Construction
public:
	CDlgTRC1752(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752)
	enum { IDD = F10_IDD_TRC1752 };
	CButton	m_synchro;
	CButton	m_cycle;
	CListBox	m_liste_message;
	CString	m_err_retard;
	CString	m_tempo;
	CString	m_periode;
	//}}AFX_DATA
	void CDlgTRC1752::AffichageOps();
	void CDlgTRC1752::AffichageTst(const int voie);
	void CDlgTRC1752::AffichageAutotest(const string type_erreur);
	void CDlgTRC1752::AffichageAutotest(string *l1, string *l2, string *l3, string *l4);
	void AffichageAct(const string voie);
	//
	void CDlgTRC1752::AffichageTestCarte(const string nomvoie);


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	


// Implementation
protected:
	CDlgTRC1752_MOD* m_Mod;
	CInter		m_activite;
	void OnEnvoiStatut();
	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnVal();
	afx_msg void OnEsc();
	afx_msg void OnLoc();
	afx_msg void OnProg();
	afx_msg void OnEua();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool actif;
	void OnAide();
	void InitListeCommande();
	void InitOnglets();
	void AffichageBoutons(bool affiche);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_H__D8122371_3495_4660_BCF1_A889A4EB5B65__INCLUDED_)
