#if !defined(AFX_DLGED42SECURITYTAB_H__058FE02A_C4CA_4B9A_91EC_D05063E6FBE3__INCLUDED_)
#define AFX_DLGED42SECURITYTAB_H__058FE02A_C4CA_4B9A_91EC_D05063E6FBE3__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42SecurityTab.h : header file
//
#include "Equip\EquipED42.h"
#include "XTabCtrl.h"
#include "DlgED42Password.h"
#include "DlgED42CikSystem.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgED42SecurityTab dialog

class CDlgED42SecurityTab : public CDialog
{
// Construction
public:
	CDlgED42SecurityTab(CEquipED42 * equip = NULL,CWnd* pParent = NULL);   // standard constructor
	~CDlgED42SecurityTab();
	void CDlgED42SecurityTab::LoadData();
	void CDlgED42SecurityTab::SaveData();
// Dialog Data
	//{{AFX_DATA(CDlgED42SecurityTab)
	enum { IDD = IDD_ED42_SECURITY_TAB };
	CXTabCtrl	c_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42SecurityTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	CDlgED42Password* m_Password;
	CDlgED42CikSystem* m_CikSystem;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42SecurityTab)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int ongletSelection;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42SECURITYTAB_H__058FE02A_C4CA_4B9A_91EC_D05063E6FBE3__INCLUDED_)
