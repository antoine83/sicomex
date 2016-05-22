#if !defined(AFX_DLGED42DIGITALDCE_H__C58CB2D8_8A26_454C_82E1_6DB1278DD7EE__INCLUDED_)
#define AFX_DLGED42DIGITALDCE_H__C58CB2D8_8A26_454C_82E1_6DB1278DD7EE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42DigitalDCE.h : header file
//
#include "Equip\EquipED42.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgED42DigitalDCE dialog

class CDlgED42DigitalDCE : public CDialog
{
// Construction
public:
	CDlgED42DigitalDCE(CEquipED42 * eqp = NULL,CWnd* pParent = NULL);   // standard constructor
	void CDlgED42DigitalDCE::LoadData(string preset);
	void CDlgED42DigitalDCE::SaveData(string preset);

// Dialog Data
	//{{AFX_DATA(CDlgED42DigitalDCE)
	enum { IDD = IDD_ED42_PRESETS_TAB_DIG_DCE };
	CComboBox	m_xck;
	CComboBox	m_txd;
	CComboBox	m_tck;
	CComboBox	m_rxd;
	CComboBox	m_rts;
	CComboBox	m_rtl;
	CComboBox	m_rng;
	CComboBox	m_rck;
	CComboBox	m_outputLevel;
	CComboBox	m_ltl;
	CComboBox	m_llr;
	CComboBox	m_dtr;
	CComboBox	m_dsr;
	CComboBox	m_dcd;
	CComboBox	m_cts;
	CButton	m_actDigitalDCE;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42DigitalDCE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42DigitalDCE)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckActDigitalDce();
	afx_msg void OnSelchangeComboCtsDce();
	afx_msg void OnSelchangeComboDcdDce();
	afx_msg void OnSelchangeComboDsrDce();
	afx_msg void OnSelchangeComboDtrDce();
	afx_msg void OnSelchangeComboLlrDce();
	afx_msg void OnSelchangeComboLtlDce();
	afx_msg void OnSelchangeComboOutputLevel();
	afx_msg void OnSelchangeComboRckDce();
	afx_msg void OnSelchangeComboRngDce();
	afx_msg void OnSelchangeComboRtlDce();
	afx_msg void OnSelchangeComboRtsDce();
	afx_msg void OnSelchangeComboRxdDce();
	afx_msg void OnSelchangeComboTckDce();
	afx_msg void OnSelchangeComboTxdDce();
	afx_msg void OnSelchangeComboXckDce();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42DIGITALDCE_H__C58CB2D8_8A26_454C_82E1_6DB1278DD7EE__INCLUDED_)
