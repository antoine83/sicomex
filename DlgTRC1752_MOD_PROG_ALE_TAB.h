#if !defined(AFX_DLGTRC1752_MOD_PROG_ALE_TAB_H__FF6C608D_95A6_48B5_AD90_30CC70636122__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_ALE_TAB_H__FF6C608D_95A6_48B5_AD90_30CC70636122__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_ALE_TAB.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_TAB dialog

class CDlgTRC1752_MOD_PROG_ALE_TAB : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_ALE_TAB(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_ALE_TAB)
	enum { IDD = IDD_MOD_PROG_ALE_TAB };
	CComboBox	m_ChAleAct;
	CComboBox	m_ChAleTable;
	CComboBox	m_ChAleCanal;
	int		m_AleCanal;
	int		m_AleTable;
	int		m_AleAct;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_ALE_TAB)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_ALE_TAB)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_ALE_TAB_H__FF6C608D_95A6_48B5_AD90_30CC70636122__INCLUDED_)
