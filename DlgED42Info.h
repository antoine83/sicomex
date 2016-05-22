#if !defined(AFX_DLGED42INFO_H__120974AA_540F_4649_B9F1_25200A392CD2__INCLUDED_)
#define AFX_DLGED42INFO_H__120974AA_540F_4649_B9F1_25200A392CD2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42Info.h : header file
//

#include "Equip\EquipED42.h"
/////////////////////////////////////////////////////////////////////////////
// DlgED42Info dialog

class DlgED42Info : public CDialog
{
// Construction
public:
	DlgED42Info(CEquipED42 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	~DlgED42Info();

// Dialog Data
	//{{AFX_DATA(DlgED42Info)
	enum { IDD = IDD_ED42_INFO };
	CButton	c_lockUnlock;
	CButton	c_fullSimu;
	CButton	c_explSync;
	CButton	c_explCall;
	CButton	c_activation;
	CComboBox	c_preset;
	CComboBox	c_operationMode;
	CStatic	c_dataRateString;
	CEdit	c_dataRate;
	CButton	c_explRec;
	CButton	c_explEmi;
	CEdit	c_Transmission_Mode;
	CEdit	c_Transmission_Procedure;
	CEdit	c_Trafic_Mode;
	CString	m_dcp1;
	CString	m_dcp2;
	CString	m_user_pwd;
	CString	m_Transmission_Mode;
	CString	m_Transmission_Procedure;
	CString	m_Operating_Mode;
	CString	m_Trafic_Mode;
	CString	m_Preset_Exploitation;
	BOOL	m_explEmi;
	BOOL	m_explRec;
	CString	m_dateRate;
	CString	m_activeKey;
	CString	m_updateCount;
	BOOL	m_explCall;
	BOOL	m_explSync;
	BOOL	m_fullSimu;
	//}}AFX_DATA

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgED42Info)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
private:
	virtual BOOL PreTranslateMessage( MSG* pMsg );

// Implementation
protected:
	CEquipED42 * eqp;
	// Generated message map functions
	//{{AFX_MSG(DlgED42Info)
	virtual BOOL OnInitDialog();
	afx_msg void OnButton8();
	afx_msg void OnChangeEditUserPwd();
	afx_msg void OnCheckEmi();
	afx_msg void OnCheckRec();
	afx_msg void OnButtonActDesact();
	afx_msg void OnButtonUnlock();
	afx_msg void OnCheckCall();
	afx_msg void OnCheckSync();
	afx_msg void OnCheckFull();
	afx_msg void OnUpdateEditUserPwd();
	afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42INFO_H__120974AA_540F_4649_B9F1_25200A392CD2__INCLUDED_)
