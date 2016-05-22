#if !defined(AFX_DLGTRC1752_MOD_PROG_ENV_H__AE27A696_C0A9_4542_9FA4_6B214B2A6707__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_ENV_H__AE27A696_C0A9_4542_9FA4_6B214B2A6707__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_ENV.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ENV dialog

class CDlgTRC1752_MOD_PROG_ENV : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_ENV(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_ENV)
	enum { IDD = IDD_MOD_PROG_ENV };
	CComboBox	m_ChLangue;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_ENV)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_ENV)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_ENV_H__AE27A696_C0A9_4542_9FA4_6B214B2A6707__INCLUDED_)
