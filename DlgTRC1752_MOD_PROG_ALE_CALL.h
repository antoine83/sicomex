#if !defined(AFX_DLGTRC1752_MOD_PROG_ALE_CALL_H__60C9D085_8BF0_493C_B8A3_92DE988C64CF__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_ALE_CALL_H__60C9D085_8BF0_493C_B8A3_92DE988C64CF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_ALE_CALL.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_CALL dialog

class CDlgTRC1752_MOD_PROG_ALE_CALL : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_ALE_CALL(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void marcheTimer();
	void arretTimer();


// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_ALE_CALL)
	enum { IDD = IDD_MOD_PROG_ALE_CALL };
	CComboBox	c_AleCallFrom;
	CComboBox	c_AleCallTo;
	CEdit	c_AleCanalF2;
	CComboBox	c_AleCallTerm;
	CComboBox	c_AleCallLqa;
	CComboBox	c_AleCallCagRec;
	CComboBox	m_ChAleCallType;
	CComboBox	m_ChAleCallCanal;
	int		m_AleCallFrom;
	int		m_AleCallTo;
	int		m_AleCallCanal;
	int		m_AleCallType;
	CString	m_AleCanalF2;
	int		m_ALeCallCagRec;
	int		m_AleCallLqa;
	int		m_AleCallTerm;
	//}}AFX_DATA
	int CALL_TYPE;
	int m_timerAleCall;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_ALE_CALL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_ALE_CALL)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeProgAleCallTa();
	afx_msg void OnSelchangeProgAleSysCanal();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEditchangeProgAleCallTo();
	//}}AFX_MSG
	void InitialisationListeFrom();
	void InitialisationListeTo(int Call_Type);
	void AffichageInfos();
	void MemorisationConfiguration();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_ALE_CALL_H__60C9D085_8BF0_493C_B8A3_92DE988C64CF__INCLUDED_)
