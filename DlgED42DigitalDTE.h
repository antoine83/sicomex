#if !defined(AFX_DLGED42DIGITALDTE_H__1113C469_2BD5_43F7_9723_CA3B3F7ECB7B__INCLUDED_)
#define AFX_DLGED42DIGITALDTE_H__1113C469_2BD5_43F7_9723_CA3B3F7ECB7B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42DigitalDTE.h : header file
//
#include "Equip\EquipED42.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgED42DigitalDTE dialog

class CDlgED42DigitalDTE : public CDialog
{
// Construction
public:
	CDlgED42DigitalDTE(CEquipED42 * eqp = NULL,CWnd* pParent = NULL);   // standard constructor
	void CDlgED42DigitalDTE::LoadData(string preset);
	void CDlgED42DigitalDTE::SaveData(string preset);

// Dialog Data
	//{{AFX_DATA(CDlgED42DigitalDTE)
	enum { IDD = IDD_ED42_PRESETS_TAB_DIG_DTE };
	CButton	c_actDigitalDTE;
	CComboBox	c_xck;
	CComboBox	c_txd;
	CComboBox	c_rxd;
	CComboBox	c_rts;
	CComboBox	c_rtl;
	CComboBox	c_rng;
	CComboBox	c_rck;
	CComboBox	c_outputLevel;
	CComboBox	c_ltl;
	CComboBox	c_llr;
	CComboBox	c_dtr;
	CComboBox	c_dsr;
	CComboBox	c_dcd;
	CComboBox	c_cts;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42DigitalDTE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42DigitalDTE)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckActDigitalDte();
	afx_msg void OnSelchangeComboCtsDte();
	afx_msg void OnSelchangeComboDcdDte();
	afx_msg void OnSelchangeComboDsrDte();
	afx_msg void OnSelchangeComboDtrDte();
	afx_msg void OnSelchangeComboLlrDte();
	afx_msg void OnSelchangeComboLtlDte();
	afx_msg void OnSelchangeComboOutputLevel();
	afx_msg void OnSelchangeComboRckDte();
	afx_msg void OnSelchangeComboRngDte();
	afx_msg void OnSelchangeComboRtlDte();
	afx_msg void OnSelchangeComboRtsDte();
	afx_msg void OnSelchangeComboRxdDte();
	afx_msg void OnSelchangeComboTxdDte();
	afx_msg void OnSelchangeComboXckDte();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CDlgED42DigitalDTE::BuildComboOutputLevel(string preset);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42DIGITALDTE_H__1113C469_2BD5_43F7_9723_CA3B3F7ECB7B__INCLUDED_)
