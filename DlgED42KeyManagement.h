#if !defined(AFX_DLGED42KEYMANAGEMENT_H__AFB6963C_90DA_406E_8542_20947F5A4F02__INCLUDED_)
#define AFX_DLGED42KEYMANAGEMENT_H__AFB6963C_90DA_406E_8542_20947F5A4F02__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42KeyManagement.h : header file
//
#include "Equip\EquipED42.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyManagement dialog

class CDlgED42KeyManagement : public CDialog
{
// Construction
public:
	CDlgED42KeyManagement(CEquipED42 * equip,CWnd* pParent = NULL);   // standard constructor
	~CDlgED42KeyManagement();
	void CDlgED42KeyManagement::LoadData();
	void CDlgED42KeyManagement::SaveData();
// Dialog Data
	//{{AFX_DATA(CDlgED42KeyManagement)
	enum { IDD = IDD_ED42_KEY_TAB_KEY_MANAGEMENT };
	CEdit	c_presetTagged;
	CComboBox	c_variableLocation;
	CComboBox	c_years;
	CComboBox	c_months;
	CComboBox	c_days;
	CComboBox	c_action;
	CString	m_updateCount;
	CString	m_presetTagged;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42KeyManagement)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	void CDlgED42KeyManagement::buildComposant(int composant);
	// Generated message map functions
	//{{AFX_MSG(CDlgED42KeyManagement)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboDateMonths();
	afx_msg void OnSelchangeComboDateYears();
	afx_msg void OnSelchangeComboAction();
	afx_msg void OnSelchangeComboVarLocation();
	afx_msg void OnSelchangeComboDateDays();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42KEYMANAGEMENT_H__AFB6963C_90DA_406E_8542_20947F5A4F02__INCLUDED_)
