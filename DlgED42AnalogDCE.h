#if !defined(AFX_DLGED42ANALOGDCE_H__EF100A27_4CF0_4ED1_9A22_4CE7AC0C90A4__INCLUDED_)
#define AFX_DLGED42ANALOGDCE_H__EF100A27_4CF0_4ED1_9A22_4CE7AC0C90A4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42AnalogDCE.h : header file
//
#include "Equip\EquipED42.h"

#define TX_MAX 13
#define TX_MIN -47
#define RX_MAX 20
#define RX_MIN -40

/////////////////////////////////////////////////////////////////////////////
// CDlgED42AnalogDCE dialog

class CDlgED42AnalogDCE : public CDialog
{
// Construction
public:
	CDlgED42AnalogDCE(CEquipED42 * eqp = NULL,CWnd* pParent = NULL);   // standard constructor
	void CDlgED42AnalogDCE::LoadData(string preset);
	void CDlgED42AnalogDCE::SaveData(string preset);
// Dialog Data
	//{{AFX_DATA(CDlgED42AnalogDCE)
	enum { IDD = IDD_ED42_PRESETS_TAB_ANALOG_DCE };
	CSpinButtonCtrl	s_txwbLevel;
	CSpinButtonCtrl	s_rxwbLevel;
	CSpinButtonCtrl	s_rxnbLevel;
	CEdit	c_txwbLevel;
	CEdit	c_rxwbLevel;
	CEdit	c_rxnbLevel;
	CSpinButtonCtrl	s_txnbLevel;
	CEdit	c_txnbLevel;
	CComboBox	c_squelchType;
	CComboBox	c_sqmType;
	CComboBox	c_sqmPolarity;
	CComboBox	c_sqgType;
	CComboBox	c_sqgPolarity;
	CComboBox	c_pttPolarity;
	CComboBox	c_nbwbPolarity;
	CComboBox	c_dpttType;
	CComboBox	c_dpttPolarity;
	CComboBox	c_bbdpPolarity;
	CButton	c_actAnalog;
	int		m_txnbLevel;
	int		m_rxnbLevel;
	int		m_rxwbLevel;
	int		m_txwbLevel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42AnalogDCE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42AnalogDCE)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboBbdpPolaDce();
	afx_msg void OnSelchangeComboDpttPolaDce();
	afx_msg void OnSelchangeComboDpttTypeDce();
	afx_msg void OnSelchangeComboNbwbPolaDce();
	afx_msg void OnSelchangeComboPttPolaDce();
	afx_msg void OnSelchangeComboSqgPolaDce();
	afx_msg void OnSelchangeComboSqgTypeDce();
	afx_msg void OnSelchangeComboSqmPolaDce();
	afx_msg void OnSelchangeComboSqmTypeDce();
	afx_msg void OnSelchangeComboSquelchTypeDce();
	afx_msg void OnDeltaposSpinTxnbLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnChangeEditTxnbLevel();
	afx_msg void OnChangeEditRxnbLevel();
	afx_msg void OnChangeEditRxwbLevel();
	afx_msg void OnChangeEditTxwbLevel();
	afx_msg void OnDeltaposSpinRxnbLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinRxwbLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTxwbLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnCheckActAnalogDce();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int oldLevelTXNB;
	int oldLevelRXNB;
	int oldLevelTXWB;
	int oldLevelRXWB;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42ANALOGDCE_H__EF100A27_4CF0_4ED1_9A22_4CE7AC0C90A4__INCLUDED_)
