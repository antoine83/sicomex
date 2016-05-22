#if !defined(AFX_DLGED42PASSWORD_H__D3EB7C00_77E1_49FF_B0F2_8A6B29335C69__INCLUDED_)
#define AFX_DLGED42PASSWORD_H__D3EB7C00_77E1_49FF_B0F2_8A6B29335C69__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42Password.h : header file
//
#include "Equip\EquipED42.h"

#define HOLD_TIME_MAX 60
#define HOLD_TIME_MIN 0
#define UPDATE_LIMIT_MAX 99
#define UPDATE_LIMIT_MIN 1

/////////////////////////////////////////////////////////////////////////////
// CDlgED42Password dialog

class CDlgED42Password : public CDialog
{
// Construction
public:
	CDlgED42Password(CEquipED42 * equip = NULL,CWnd* pParent = NULL);   // standard constructor
	~CDlgED42Password();
	void CDlgED42Password::LoadData();
	void CDlgED42Password::SaveData();

// Dialog Data
	//{{AFX_DATA(CDlgED42Password)
	enum { IDD = IDD_ED42_SECURITY_TAB_PASSWORD };
	CEdit	c_updateLimit;
	CEdit	c_holdTime;
	CEdit	c_changeConfirmPassword;
	CEdit	c_checkPassword;
	CEdit	c_changeOldPassword;
	CEdit	c_changeNewPassword;
	CSpinButtonCtrl	s_updateLimit;
	CSpinButtonCtrl	s_holdTime;
	CButton	c_check;
	CButton	c_changePassword;
	CString	m_checkVerif;
	int		m_holdTime;
	int		m_updateLimit;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42Password)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42Password)
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinHoldTime(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinUpdateLimit(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonChangePassword();
	afx_msg void OnButtonCheck();
	afx_msg void OnChangeEditHoldTime();
	afx_msg void OnChangeEditUpdateLimit();
	afx_msg void OnChangeEditChangeOldPass();
	afx_msg void OnChangeEditChangeNewPass();
	afx_msg void OnChangeEditChangeConfirmPass();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int oldHoldTime;
	int oldUpdateLimit;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42PASSWORD_H__D3EB7C00_77E1_49FF_B0F2_8A6B29335C69__INCLUDED_)
