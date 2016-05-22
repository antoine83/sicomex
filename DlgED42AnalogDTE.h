#if !defined(AFX_DLGED42ANALOGDTE_H__8FAD6A52_8221_4B76_8EBF_55C7CAD4D13D__INCLUDED_)
#define AFX_DLGED42ANALOGDTE_H__8FAD6A52_8221_4B76_8EBF_55C7CAD4D13D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42AnalogDTE.h : header file
//
#include "Equip\EquipED42.h"

#define AUDIO_MAX 13
#define AUDIO_MIN -47
#define CONTROL_MAX 20
#define CONTROL_MIN -40

/////////////////////////////////////////////////////////////////////////////
// CDlgED42AnalogDTE dialog

class CDlgED42AnalogDTE : public CDialog
{
// Construction
public:
	CDlgED42AnalogDTE(CEquipED42 * eqp = NULL,CWnd* pParent = NULL);   // standard constructor
	void CDlgED42AnalogDTE::LoadData(string preset);
	void CDlgED42AnalogDTE::SaveData(string preset);

// Dialog Data
	//{{AFX_DATA(CDlgED42AnalogDTE)
	enum { IDD = IDD_ED42_PRESETS_TAB_ANALOG_DTE };
	CComboBox	c_microType;
	CButton	c_microSupply;
	CSpinButtonCtrl	s_txctrLevel;
	CSpinButtonCtrl	s_txbypassLevel;
	CSpinButtonCtrl	s_sidetoneLevel;
	CSpinButtonCtrl	s_rxctrLevel;
	CSpinButtonCtrl	s_rxbypassLevel;
	CSpinButtonCtrl	s_phoneLevel;
	CEdit	c_monitorLevel;
	CSpinButtonCtrl	s_monitorLevel;
	CSpinButtonCtrl	s_microLevel;
	CSpinButtonCtrl	s_alarmtoneLevel;
	CEdit	c_txctrLevel;
	CEdit	c_txbypassLevel;
	CEdit	c_sidetoneLevel;
	CEdit	c_rxctrLevel;
	CEdit	c_rxbypassLevel;
	CEdit	c_phoneLevel;
	CEdit	c_microLevel;
	CEdit	c_alarmtoneLevel;
	CComboBox	c_voltageSupply;
	CComboBox	c_ri;
	CComboBox	c_pttctrConfigType;
	CComboBox	c_ptt42ConfigType;
	CButton	c_actMonitoring;
	CButton	c_actLocalAudio;
	CButton	c_actCentralAudio;
	CButton	c_actAnalogDTE;
	int		m_alarmtoneLevel;
	int		m_microLevel;
	int		m_monitorLevel;
	int		m_phoneLevel;
	int		m_rxbypassLevel;
	int		m_rxctrLevel;
	int		m_sidetoneLevel;
	int		m_txbypassLevel;
	int		m_txctrLevel;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42AnalogDTE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	void CDlgED42AnalogDTE::MiseAJourVue();
	// Generated message map functions
	//{{AFX_MSG(CDlgED42AnalogDTE)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckActAnalogDte();
	afx_msg void OnCheckActCentralAudio();
	afx_msg void OnCheckActLocalAudio();
	afx_msg void OnCheckActMonitoring();
	afx_msg void OnCheckMicroSupply();
	afx_msg void OnSelchangeComboMicroType();
	afx_msg void OnSelchangeComboPtt42ConfigType();
	afx_msg void OnSelchangeComboPttctrConfigType();
	afx_msg void OnSelchangeComboRi();
	afx_msg void OnSelchangeComboVoltageSupply();
	afx_msg void OnChangeEditAlarmtoneLevel();
	afx_msg void OnChangeEditMicroLevel();
	afx_msg void OnChangeEditMonitorLevel();
	afx_msg void OnChangeEditPhoneLevel();
	afx_msg void OnChangeEditRxbypassLevel();
	afx_msg void OnChangeEditRxctrLevel();
	afx_msg void OnChangeEditSidetoneLevel();
	afx_msg void OnChangeEditTxbypassLevel();
	afx_msg void OnChangeEditTxctrLevel();
	afx_msg void OnDeltaposSpinAlarmtoneLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinMicroLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinMonitorLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinPhoneLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinRxbypassLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinRxctrLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinSidetoneLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTxbypassLevel(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTxctrLevel(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int oldMicroLevel;
	int oldPhoneLevel;
	int oldTxctrLevel;
	int oldRxctrLevel;
	int oldMonitorLevel;
	int oldSidetoneLevel;
	int oldAlarmtoneLevel;
	int oldTxbypassLevel;
	int oldRxbypassLevel;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42ANALOGDTE_H__8FAD6A52_8221_4B76_8EBF_55C7CAD4D13D__INCLUDED_)
