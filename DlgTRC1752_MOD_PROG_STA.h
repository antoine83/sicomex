#if !defined(AFX_DLGTRC1752_MOD_PROG_STA_H__9220A0BD_2DFA_42FE_971E_F8BD941EAB9F__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_STA_H__9220A0BD_2DFA_42FE_971E_F8BD941EAB9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_STA.h : header file
//

#include "XTabCtrl.h"

#include "DlgTRC1752_MOD_PROG_STA_A1.h"
#include "DlgTRC1752_MOD_PROG_STA_A2.h"
#include "DlgTRC1752_MOD_PROG_STA_B1.h"
#include "DlgTRC1752_MOD_PROG_STA_B2.h"
#include "DlgTRC1752_MOD_PROG_STA_TST.h"

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA dialog

class CDlgTRC1752_MOD_PROG_STA : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_STA(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor

	CDlgTRC1752_MOD_PROG_STA_A1*	m_ModProgStaA1;
	CDlgTRC1752_MOD_PROG_STA_A2*	m_ModProgStaA2;
	CDlgTRC1752_MOD_PROG_STA_B1*	m_ModProgStaB1;
	CDlgTRC1752_MOD_PROG_STA_B2*	m_ModProgStaB2;
	CDlgTRC1752_MOD_PROG_STA_TST*	m_ModProgStaTst;

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_STA)
	enum { IDD = IDD_MOD_PROG_STA };
	CXTabCtrl	m_ProgStaTab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_STA)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_STA)
	afx_msg void OnSelchangeProgSta(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool quadrivoie;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_STA_H__9220A0BD_2DFA_42FE_971E_F8BD941EAB9F__INCLUDED_)
