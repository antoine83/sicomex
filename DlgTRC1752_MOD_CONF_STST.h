#if !defined(AFX_DLGTRC1752_MOD_CONF_STST_H__26668556_55F9_4FB1_919A_2E25435A0F58__INCLUDED_)
#define AFX_DLGTRC1752_MOD_CONF_STST_H__26668556_55F9_4FB1_919A_2E25435A0F58__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_CONF_STST.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_STST dialog

class CDlgTRC1752_MOD_CONF_STST : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_CONF_STST(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();

	void LoadData();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_CONF_STST)
	enum { IDD = IDD_MOD_CONF_STST };
	CButton	m_Sauvegarde;
	CButton	m_TC4;
	CButton	m_TC3;
	CButton	m_TC2;
	CButton	m_TC;
	CButton	m_TC1;
	CButton	m_IA6;
	CButton	m_IA5;
	CButton	m_IA4;
	CButton	m_IA3;
	CButton	m_D8;
	CButton	m_D7;
	CButton	m_D6;
	CButton	m_D5;
	CButton	m_D4;
	CButton	m_D3;
	CButton	m_D2;
	CButton	m_D1;
	CButton	m_113;
	CButton	m_107;
	CButton	m_105;
	CButton	m_103;
	CButton	m_IntB2;
	CButton	m_IntB1;
	CButton	m_IntA2;
	CButton	m_IntA1;
	CButton	m_B2;
	CButton	m_B1;
	CButton	m_A2;
	CButton	m_A1;
	CButton	m_Tiroir;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_CONF_STST)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_CONF_STST)
	virtual BOOL OnInitDialog();
	afx_msg void OnCarteA1();
	afx_msg void OnCarteA2();
	afx_msg void OnCarteB1();
	afx_msg void OnCarteB2();
	afx_msg void OnSauvegarde();
	afx_msg void OnTiroir();
	afx_msg void OnPanneD1();
	afx_msg void OnPanneD2();
	afx_msg void OnPanneD3();
	afx_msg void OnPanneD4();
	afx_msg void OnPanneD5();
	afx_msg void OnPanneD6();
	afx_msg void OnPanneD7();
	afx_msg void OnPanneD8();
	afx_msg void OnPanne103();
	afx_msg void OnPanne105();
	afx_msg void OnPanne107();
	afx_msg void OnPanne113();
	afx_msg void OnIntA1();
	afx_msg void OnIntA2();
	afx_msg void OnIntB1();
	afx_msg void OnIntB2();
	afx_msg void OnPanneIa3();
	afx_msg void OnPanneIa4();
	afx_msg void OnPanneIa5();
	afx_msg void OnPanneIa6();
	afx_msg void OnPanneTc();
	afx_msg void OnPanneTc1();
	afx_msg void OnPanneTc2();
	afx_msg void OnPanneTc3();
	afx_msg void OnPanneTc4();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_CONF_STST_H__26668556_55F9_4FB1_919A_2E25435A0F58__INCLUDED_)
