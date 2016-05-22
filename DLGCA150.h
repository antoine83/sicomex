// CDLGCA150.h: interface for the DLGCA150 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGCA150_H__5A2BB29F_96F6_46C3_AD34_F75442C735BA__INCLUDED_)
#define AFX_DLGCA150_H__5A2BB29F_96F6_46C3_AD34_F75442C735BA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

#include "afxcmn.h"

class CDLGCA150:public CDlgEquip
{
protected:
	CInter		m_activite;
	CDiode		m_incident;
	CDiode		m_info;

public:
	//{{AFX_DATA(CDLGCA150)
	enum { IDD = IDD_CA_150 };

	CButton			m_SH[4];
	CButton			m_timer;
	CButton			m_defaut;
	CButton			m_mauvais_ros;
	CButton			m_local;
	CButton			m_charge[7];
	CButton			m_combine;
	// Variables de Slide Bar
	CSliderCtrl		m_incidente;
	CString			m_texte_incidente;
	CSpinButtonCtrl	m_spin_incidente;
	CSliderCtrl		m_reflechie;
	CString			m_texte_reflechie;
	CSpinButtonCtrl	m_spin_reflechie;
	
	CListBox	m_liste_message;
	CButton		m_synchro;
	CButton		m_cycle;
	CString		m_err_retard;
	CString		m_periode;
	CString		m_tempo;
	CString		m_pimax;
	CString		m_prmax;

	bool		bCouple;
	//}}AFX_DATA

public:
// standard constructor
	CDLGCA150(CWnd* pParent = NULL);
	virtual void GenerateurAuto();

// Overrides
	//{{AFX_VIRTUAL(CDLGCA150)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
// Implementation
	//{{AFX_MSG(CDLGCA150)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnComErreur();
	afx_msg void OnSlideIncidente(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpinIncidente (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSpinReflechie (NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSlideReflechie(NMHDR* pNMHDR, LRESULT* pResult);
	void OnValider();
	void OnCharge();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void OnAide();
	void Verrouille(BOOL etat);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCA150_H__5A2BB29F_96F6_46C3_AD34_F75442C735BA__INCLUDED_)
