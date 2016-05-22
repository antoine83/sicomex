#if !defined(AFX_DLGED42CIKSYSTEM_H__C33B28DB_63F1_43C8_BDF0_2DD9BDB7567D__INCLUDED_)
#define AFX_DLGED42CIKSYSTEM_H__C33B28DB_63F1_43C8_BDF0_2DD9BDB7567D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42CikSystem.h : header file
//

#include "Equip\EquipED42.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgED42CikSystem dialog

class CDlgED42CikSystem : public CDialog
{
// Construction
public:
	CDlgED42CikSystem(CEquipED42 * equip = NULL,CWnd* pParent = NULL);   // standard constructor
	~CDlgED42CikSystem();
	void CDlgED42CikSystem::LoadData();
// Dialog Data
	//{{AFX_DATA(CDlgED42CikSystem)
	enum { IDD = IDD_ED42_SECURITY_TAB_CIK_SYS };
	CComboBox	c_deleteCIKCombo;
	CButton	c_initializeCIKButton;
	CComboBox	c_initializeCIK;
	CButton	c_deleteCIKSystem;
	CButton	c_deleteCIK;
	CString	m_initializeVerif;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42CikSystem)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42CikSystem)
	virtual BOOL OnInitDialog();
	afx_msg void OnButtonDeleteCik();
	afx_msg void OnButtonDeleteCikSystem();
	afx_msg void OnButtonInitializeCik();
	afx_msg void OnSelchangeComboInitializeCik();
	afx_msg void OnButtonKek();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void CDlgED42CikSystem::EnableComponent();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42CIKSYSTEM_H__C33B28DB_63F1_43C8_BDF0_2DD9BDB7567D__INCLUDED_)
