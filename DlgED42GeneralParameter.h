#if !defined(AFX_DLGED42GENERALPARAMETER_H__570F96F5_7DB5_4A1C_9E0C_9BC43DAEF9EF__INCLUDED_)
#define AFX_DLGED42GENERALPARAMETER_H__570F96F5_7DB5_4A1C_9E0C_9BC43DAEF9EF__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42GeneralParameter.h : header file
//
#include "Equip\EquipED42.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgED42GeneralParameter dialog

class CDlgED42GeneralParameter : public CDialog
{
// Construction
public:
	CDlgED42GeneralParameter(CEquipED42 * eqp = NULL,CWnd* pParent = NULL);   // standard constructor
	void CDlgED42GeneralParameter::LoadData(string preset);
	void CDlgED42GeneralParameter::SaveData(string preset);

// Dialog Data
	//{{AFX_DATA(CDlgED42GeneralParameter)
	enum { IDD = IDD_ED42_PRESETS_TAB_GEN_PARAM };
	CEdit	m_leadTime;
	CComboBox	m_transProc;
	CComboBox	m_transMode;
	CComboBox	m_traffMode;
	CComboBox	m_synchroMode;
	CComboBox	m_parity;
	CComboBox	m_outputSel;
	CComboBox	m_numStopBit;
	CComboBox	m_numDataBit;
	CComboBox	m_dataRate;
	CComboBox	m_clockMode;
	CButton	m_fec;
	CButton	m_antispoof;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42GeneralParameter)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42GeneralParameter)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboTransMode();
	afx_msg void OnSelchangeComboTransProc();
	afx_msg void OnSelchangeComboTraffMode();
	afx_msg void OnSelchangeComboOutputSel();
	afx_msg void OnSelchangeComboSynchroMode();
	afx_msg void OnSelchangeComboDataRate();
	afx_msg void OnSelchangeComboClockMode();
	afx_msg void OnSelchangeComboNumDataBit();
	afx_msg void OnSelchangeComboParity();
	afx_msg void OnSelchangeComboNumStopBit();
	afx_msg void OnChangeEditLeadTime();
	afx_msg void OnCheckFec();
	afx_msg void OnCheckAntispoof();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	TGeneralParameters generalParameter;
	TDigitalDCE digitalDCE;
	TAnalogDCE analogDCE;
	TDigitalDTE digitalDTE;
	TAnalogDTE analogDTE;

	string oldLead_time;
	void CDlgED42GeneralParameter::BuildComposant(int composant);

	int CDlgED42GeneralParameter::GetCurSelComboToValue(int composant);
	void CDlgED42GeneralParameter::SetCurSelValueToCombo(int composant);

	void CDlgED42GeneralParameter::UpdateDialog(int value);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42GENERALPARAMETER_H__570F96F5_7DB5_4A1C_9E0C_9BC43DAEF9EF__INCLUDED_)
