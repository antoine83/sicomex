#if !defined(AFX_DLGED42STATUSERR_H__89B5716C_7960_4E8E_A9D4_E36EE70DB8E5__INCLUDED_)
#define AFX_DLGED42STATUSERR_H__89B5716C_7960_4E8E_A9D4_E36EE70DB8E5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42StatusERR.h : header file
//
#include "Equip\EquipED42.h"

#define DEFAULT_KE_STATUS 6
#define DEFAULT_SECURE_MODE 2

#define NB_REPEAT_MAX 10
#define NB_REPEAT_MIN 0
/////////////////////////////////////////////////////////////////////////////
// CDlgED42StatusERR dialog

class CDlgED42StatusERR : public CDialog
{
// Construction
public:
	CDlgED42StatusERR(CEquipED42 * eqp = NULL,CWnd* pParent = NULL);   // standard constructor
	void CDlgED42StatusERR::SaveData() ;
	void CDlgED42StatusERR::LoadData();
// Dialog Data
	//{{AFX_DATA(CDlgED42StatusERR)
	enum { IDD = IDD_ED42_STATUS_ERR };
	CSpinButtonCtrl	s_nbRepeat;
	CEdit	c_nbRepeat;
	CComboBox	c_secureMode;
	CComboBox	c_KEState;
	CButton	c_wrongState;
	CButton	c_wrongCommand;
	CButton	c_unknownCommand;
	CButton	c_syntaxChecksum;
	CButton	c_slaveNotRemote;
	CButton	c_parity;
	CButton	c_maxMessageLength;
	CButton	c_invalidParameter;
	int		m_nbRepeat;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42StatusERR)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42StatusERR)
	virtual BOOL OnInitDialog();
	afx_msg void OnCheckInvalidParameter();
	afx_msg void OnCheckMaxMessLength();
	afx_msg void OnCheckParity();
	afx_msg void OnCheckSlaveNotRemote();
	afx_msg void OnCheckSyntaxChecksum();
	afx_msg void OnCheckUnknownCommand();
	afx_msg void OnCheckWrongCommand();
	afx_msg void OnCheckWrongState();
	afx_msg void OnSelchangeComboKeState();
	afx_msg void OnSelchangeComboSecureMode();
	afx_msg void OnRaz();
	virtual void OnCancel();
	virtual void OnOK();
	afx_msg void OnChangeEditNbRepeat();
	afx_msg void OnDeltaposSpinNbRepeat(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int oldNbRepeat;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42STATUSERR_H__89B5716C_7960_4E8E_A9D4_E36EE70DB8E5__INCLUDED_)
