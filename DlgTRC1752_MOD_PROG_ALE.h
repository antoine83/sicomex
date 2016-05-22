#if !defined(AFX_DLGTRC1752_MOD_PROG_ALE_H__D414256C_308D_47F1_97A5_F8B8D957421A__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_ALE_H__D414256C_308D_47F1_97A5_F8B8D957421A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_ALE.h : header file
//

#include "XTabCtrl.h"

#include "DlgTRC1752_MOD_PROG_ALE_CALL.h"
#include "DlgTRC1752_MOD_PROG_ALE_SYS.h"
#include "DlgTRC1752_MOD_PROG_ALE_TAB.h"
#include "DlgTRC1752_MOD_PROG_ALE_LP.h"

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE dialog

class CDlgTRC1752_MOD_PROG_ALE : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_ALE(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor

	CDlgTRC1752_MOD_PROG_ALE_CALL*	m_ModProgAleCall;
	CDlgTRC1752_MOD_PROG_ALE_SYS*	m_ModProgAleSys;
	CDlgTRC1752_MOD_PROG_ALE_TAB*	m_ModProgAleTab;
	CDlgTRC1752_MOD_PROG_ALE_LP*	m_ModProgAleLp;

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_ALE)
	enum { IDD = IDD_MOD_PROG_ALE };
	CXTabCtrl	m_ModProgTab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_ALE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_ALE)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeModProg(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_ALE_H__D414256C_308D_47F1_97A5_F8B8D957421A__INCLUDED_)
