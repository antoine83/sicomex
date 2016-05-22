#if !defined(AFX_DLGED42ERR_H__5F80665E_9F9D_453C_BC43_96183DEF1C73__INCLUDED_)
#define AFX_DLGED42ERR_H__5F80665E_9F9D_453C_BC43_96183DEF1C73__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42ERR.h : header file
//
#include "Equip\EquipED42.h"


/////////////////////////////////////////////////////////////////////////////
// DlgED42ERR dialog

class DlgED42ERR : public CDialog
{
// Construction
public:
	DlgED42ERR(CEquipED42 * equip = NULL,CWnd* pParent = NULL);   // standard constructor
	
	void DlgED42ERR::SaveData() ;
	void DlgED42ERR::LoadData();
// Dialog Data
	//{{AFX_DATA(DlgED42ERR)
	enum { IDD = IDD_ED42_ERR };
	CComboBox	m_ErrorCrypto;
	CButton	m_WrongPassword;
	CButton	m_WrongDldPassword;
	CButton	m_WrongCik;
	CButton	m_VariableManagement;
	CButton	m_UpdateLimit;
	CButton	m_TimeoutCik;
	CButton	m_StartError;
	CButton	m_SelectVariable;
	CButton	m_PasswordCheck;
	CButton	m_MissingCik;
	CButton	m_FormatError;
	CButton	m_F101ErrorVariable;
	CButton	m_F101ErrorKek;
	CButton	m_ErrorSoftware;
	CButton	m_ErrorConnectCik;
	CButton	m_ConfigError;
	CButton	m_BilateralUpdateError;
	CButton	m_BilateralTagError;
	CButton	m_NoVariable;
	CButton	m_F101ErrorAction;
	CButton	m_F101Timeout;
	CButton	m_F101Interface;
	CComboBox	m_ErrorCodes;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgED42ERR)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * equip;
	// Generated message map functions
	//{{AFX_MSG(DlgED42ERR)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnSelchangeComboErrorCodes();
	afx_msg void OnCheckF101Interface();
	afx_msg void OnCheckF101Timeout();
	afx_msg void OnCheckF101ErrorAction();
	afx_msg void OnCheckNoVariable();
	afx_msg void OnCheckWrongPassword();
	afx_msg void OnCheckF101ErrorVariable();
	afx_msg void OnCheckF101ErrorKek();
	afx_msg void OnCheckConfigError();
	afx_msg void OnCheckStartError();
	afx_msg void OnCheckErrorSoftware();
	afx_msg void OnCheckSelectVariable();
	afx_msg void OnCheckUpdateLimit();
	afx_msg void OnCheckBilateralUpdateError();
	afx_msg void OnCheckBilateralTagError();
	afx_msg void OnCheckWrongDldPassword();
	afx_msg void OnCheckFormatError();
	afx_msg void OnCheckErrorConnectCik();
	afx_msg void OnCheckVariableManagement();
	afx_msg void OnSelchangeComboErrorCrypto();
	afx_msg void OnCheckMissingCik();
	afx_msg void OnCheckWrongCik();
	afx_msg void OnCheckTimeoutCik();
	afx_msg void OnCheckPasswordCheck();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42ERR_H__5F80665E_9F9D_453C_BC43_96183DEF1C73__INCLUDED_)
