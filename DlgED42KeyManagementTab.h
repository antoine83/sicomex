#if !defined(AFX_DLGED42KEYMANAGEMENTTAB_H__616C0F6D_DEBB_497F_8B5D_E51BC09C6759__INCLUDED_)
#define AFX_DLGED42KEYMANAGEMENTTAB_H__616C0F6D_DEBB_497F_8B5D_E51BC09C6759__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42KeyManagementTab.h : header file
//
#include "Equip\EquipED42.h"
#include "XTabCtrl.h"
#include "DlgED42KeyDisplay.h"
#include "DlgED42KeyManagement.h"
#include "DlgED42KeyTag.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyManagementTab dialog

class CDlgED42KeyManagementTab : public CDialog
{
// Construction
public:
	CDlgED42KeyManagementTab(CEquipED42 * equip = NULL,CWnd* pParent = NULL);   // standard constructor
	~CDlgED42KeyManagementTab();
	void CDlgED42KeyManagementTab::LoadData();
	void CDlgED42KeyManagementTab::SaveData();
// Dialog Data
	//{{AFX_DATA(CDlgED42KeyManagementTab)
	enum { IDD = IDD_ED42_KEY_MANAGEMENT_TAB };
	CXTabCtrl	c_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42KeyManagementTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	CDlgED42KeyDisplay* m_KeyDisplay;
	CDlgED42KeyManagement* m_KeyManagement;
	CDlgED42KeyTag* m_KeyTag;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42KeyManagementTab)
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int ongletSelection;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42KEYMANAGEMENTTAB_H__616C0F6D_DEBB_497F_8B5D_E51BC09C6759__INCLUDED_)
