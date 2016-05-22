// DLGaad_20_4.h: interface for the CDLGaad_20_4 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGAAD_20_8_H__7B89060C_7B43_4884_B865_A666D94F5577__INCLUDED_)
#define AFX_DLGAAD_20_8_H__7B89060C_7B43_4884_B865_A666D94F5577__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

class CDLGaad_20_8:public CDlgEquip
{
protected:
	CInter		m_activite;
	CDiode		m_incident;
	CDiode		m_info;

public:
	//{{AFX_DATA(CDLGaad_20_8)
	enum { IDD = IDD_AAD_20_8 };

	CComboBox	EtatAntenne_20_8[8];
	CComboBox	EtatPreampli_20_8[8];
	CComboBox	EtatAmpli_20_8[40];
	CButton		m_20_8[8][20];
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
	CDLGaad_20_8(CWnd* pParent = NULL);
	virtual void GenerateurAuto();

// Overrides
	//{{AFX_VIRTUAL(CDLGaad_20_8)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
// Implementation
	//{{AFX_MSG(CDLGaad_20_8)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnComErreur();
	afx_msg void OnButtonValider();
	// TODO : integrer les fonctions liees aux evenements
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void OnAide();
	void Verrouille(BOOL etat);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGAAD_20_8_H__7B89060C_7B43_4884_B865_A666D94F5577__INCLUDED_)
