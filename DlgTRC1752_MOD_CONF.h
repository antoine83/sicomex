#if !defined(AFX_DLGTRC1752_MOD_CONF_H__BCC41F43_5D0C_49B8_B307_DAD8E834C6FB__INCLUDED_)
#define AFX_DLGTRC1752_MOD_CONF_H__BCC41F43_5D0C_49B8_B307_DAD8E834C6FB__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_CONF.h : header file
//

#include "XTabCtrl.h"

#include "DlgTRC1752_MOD_CONF_ENV.h"
#include "DlgTRC1752_MOD_CONF_STST.h"
#include "DlgTRC1752_MOD_CONF_ALE.h"
#include "DlgTRC1752_MOD_CONF_RDO.h"
#include "DlgTRC1752_MOD_CONF_CONF.h"
#include "DlgTRC1752_MOD_CONF_ARQ.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF dialog

class CDlgTRC1752_MOD_CONF : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_CONF(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor

	CDlgTRC1752_MOD_CONF_ENV*	m_ModConfEnv;
	CDlgTRC1752_MOD_CONF_STST*	m_ModConfStst;
	CDlgTRC1752_MOD_CONF_ALE*	m_ModConfAle;
	CDlgTRC1752_MOD_CONF_RDO*	m_ModConfRdo;
	CDlgTRC1752_MOD_CONF_CONF*	m_ModConfCnf;
	CDlgTRC1752_MOD_CONF_ARQ*	m_ModConfArq;

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_CONF)
	enum { IDD = IDD_MOD_CONF };
	CXTabCtrl	m_ModConfTab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_CONF)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_CONF)
	afx_msg void OnSelchangeModProg(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_CONF_H__BCC41F43_5D0C_49B8_B307_DAD8E834C6FB__INCLUDED_)
