// DLGaad_20_4.h: interface for the CDLGaad_20_4 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_CDLGaad_20_4_H__6A86A50C_9D6B_4615_8C55_EFC7C0E74729__INCLUDED_)
#define AFX_CDLGaad_20_4_H__6A86A50C_9D6B_4615_8C55_EFC7C0E74729__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

class CDLGaad_20_4:public CDlgEquip
{
protected:
	CInter		m_activite;
	CDiode		m_incident;
	CDiode		m_info;

public:
	//{{AFX_DATA(CDLGaad_20_4)
	enum { IDD = IDD_AAD_20_4 };

	CComboBox	EtatAntenne_20_4[4];
	CComboBox	EtatPreampli_20_4[4];
	CComboBox	EtatAmpli_20_4[20];
	CButton		m_20_4[4][20];
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
	CDLGaad_20_4(CWnd* pParent = NULL);
	virtual void GenerateurAuto();

// Overrides
	//{{AFX_VIRTUAL(CDLGaad_20_4)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
// Implementation
	//{{AFX_MSG(CDLGaad_20_4)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnComErreur();
	afx_msg void OnButtonValider();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void OnAide();
	void Verrouille(BOOL etat);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_CDLGaad_20_4_H__6A86A50C_9D6B_4615_8C55_EFC7C0E74729__INCLUDED_)
