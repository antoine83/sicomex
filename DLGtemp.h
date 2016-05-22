// DLGtemp.h: interface for the CDLGtemp class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGTEMP_H__7EFABEE2_4690_4D8E_B82D_072BCE956E96__INCLUDED_)
#define AFX_DLGTEMP_H__7EFABEE2_4690_4D8E_B82D_072BCE956E96__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

class CDLGtemp:public CDlgEquip
{
protected:
	CInter		m_activite;
	CDiode		m_incident;
	CDiode		m_info;

public:
	//{{AFX_DATA(CDLGtemp)
	enum { IDD = IDD_TEMP };

	// TODO : integrer les variables membre
	
	CListBox	m_liste_message;
	CButton		m_synchro;
	CButton		m_cycle;
	CString		m_err_retard;
	CString		m_periode;
	CString		m_tempo;
	//}}AFX_DATA

public:
// standard constructor
	CDLGtemp(CWnd* pParent = NULL);
	virtual void GenerateurAuto();

// Overrides
	//{{AFX_VIRTUAL(CDLGtemp)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);
	//}}AFX_VIRTUAL

protected:
// Implementation
	//{{AFX_MSG(CDLGtemp)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnComErreur();
	// TODO : integrer les fonctions liees aux evenements
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void OnAide();
	void Verrouille(BOOL etat);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTEMP_H__7EFABEE2_4690_4D8E_B82D_072BCE956E96__INCLUDED_)
