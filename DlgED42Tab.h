#if !defined(AFX_DLGED42TAB_H__C9ABEF0A_3485_4E62_8909_A825157CC1B1__INCLUDED_)
#define AFX_DLGED42TAB_H__C9ABEF0A_3485_4E62_8909_A825157CC1B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42Tab.h : header file
//

#include "Equip\EquipED42.h"

#include "XTabCtrl.h"
#include "DlgED42Info.h"
#include "DlgED42Presets.h"
#include "DlgED42KeyManagementTab.h"
#include "DlgED42SecurityTab.h"
#include "DlgED42Parametres.h"


/////////////////////////////////////////////////////////////////////////////
// CDlgED42Tab dialog

class CDlgED42Tab : public CDialog
{
// Construction
public:
	CDlgED42Tab(CEquipED42 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	~CDlgED42Tab();

	DlgED42Info* m_Info;
	CDlgED42Presets* m_Presets;
	CDlgED42KeyManagementTab* m_KeyManagementTab;
	CDlgED42SecurityTab* m_SecurityTab;
	CDlgED42Parametres* m_Parameters;
	
	void CDlgED42Tab::LoadData();
	void CDlgED42Tab::SaveData();

// Dialog Data
	//{{AFX_DATA(CDlgED42Tab)
	enum { IDD = IDD_ED42_TAB };
	CXTabCtrl	m_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42Tab)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgED42Tab)
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int ongletSelection;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42TAB_H__C9ABEF0A_3485_4E62_8909_A825157CC1B1__INCLUDED_)
