#if !defined(AFX_DLGTRC1752_MOD_PROG_TC_H__41DA5C6F_82B3_4312_B245_2E508A9966D4__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_TC_H__41DA5C6F_82B3_4312_B245_2E508A9966D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_TC.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_TC dialog

class CDlgTRC1752_MOD_PROG_TC : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_TC(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();

	void StartTimer();
	void StopTimer();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_TC)
	enum { IDD = IDD_MOD_PROG_TC };
	CComboBox	m_ChVoie;
	CComboBox	m_ChTcl;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_TC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_TC)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDropdownEtaTcl();
	afx_msg void OnSelchangeEtaTcl();
	afx_msg void OnDropdownProgTcVoie();
	afx_msg void OnSelchangeProgTcVoie();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool quadrivoie;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_TC_H__41DA5C6F_82B3_4312_B245_2E508A9966D4__INCLUDED_)
