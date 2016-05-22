#if !defined(AFX_DLGTRC1752_MOD_PROG_H__BB86FC10_A5CB_4E93_8EFF_EA63C449532D__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_H__BB86FC10_A5CB_4E93_8EFF_EA63C449532D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG.h : header file
//

#include "XTabCtrl.h"

#include "DlgTRC1752_MOD_PROG_ALE.h"
#include "DlgTRC1752_MOD_PROG_CONF.h"
#include "DlgTRC1752_MOD_PROG_INTF.h"
#include "DlgTRC1752_MOD_PROG_ENV.h"
#include "DlgTRC1752_MOD_PROG_STA.h"
#include "DlgTRC1752_MOD_PROG_STST.h"
#include "DlgTRC1752_MOD_PROG_TC.h"

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG dialog

class CDlgTRC1752_MOD_PROG : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor

	CDlgTRC1752_MOD_PROG_ALE* m_ModProgAle;
	CDlgTRC1752_MOD_PROG_CONF* m_ModProgConf;
    CDlgTRC1752_MOD_PROG_INTF* m_ModProgIntf;
	CDlgTRC1752_MOD_PROG_STA* m_ModProgSta;
	CDlgTRC1752_MOD_PROG_STST* m_ModProgStst;
	CDlgTRC1752_MOD_PROG_TC* m_ModProgTc;
	CDlgTRC1752_MOD_PROG_ENV* m_ModProgEnv;

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG)
	enum { IDD = IDD_MOD_PROG };
	CXTabCtrl	m_ModProgTab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG)
	afx_msg void OnSelchangeModProg(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_H__BB86FC10_A5CB_4E93_8EFF_EA63C449532D__INCLUDED_)
