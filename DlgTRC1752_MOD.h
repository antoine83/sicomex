#if !defined(AFX_DLGTRC1752_MOD_H__3150B053_E7BF_4832_91AB_A3DBA64D8E65__INCLUDED_)
#define AFX_DLGTRC1752_MOD_H__3150B053_E7BF_4832_91AB_A3DBA64D8E65__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD.h : header file
//

#include "XTabCtrl.h"

#include "DlgTRC1752_MOD_CONF.h"
#include "DlgTRC1752_MOD_PROG.h"
#include "DlgTRC1752_MOD_OPS.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD dialog

class CDlgTRC1752_MOD : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor

	CDlgTRC1752_MOD_CONF* m_ModConf;
	CDlgTRC1752_MOD_OPS* m_ModOps;
    CDlgTRC1752_MOD_PROG* m_ModProg;

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD)
	enum { IDD = IDD_TRC1752_MOD };
	CXTabCtrl	m_Tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD)
	protected:
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD)
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_H__3150B053_E7BF_4832_91AB_A3DBA64D8E65__INCLUDED_)
