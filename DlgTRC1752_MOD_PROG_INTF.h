#if !defined(AFX_DLGTRC1752_MOD_PROG_INTF_H__F8D9AF8D_2B78_415C_B83C_FBF7AAC61341__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_INTF_H__F8D9AF8D_2B78_415C_B83C_FBF7AAC61341__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_INTF.h : header file
//

#include "XTabCtrl.h"

#include "DlgTRC1752_MOD_PROG_INTF_LIAS.h"
#include "DlgTRC1752_MOD_PROG_INTF_BF.h"
#include "DlgTRC1752_MOD_PROG_INTF_TC.h"
#include "DlgTRC1752_MOD_PROG_INTF_PIL.h"
#include "DlgTRC1752_MOD_PROG_INTF_ASS.h"

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF dialog

class CDlgTRC1752_MOD_PROG_INTF : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_INTF(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor

	CDlgTRC1752_MOD_PROG_INTF_LIAS* m_ModProgIntfLias;
	CDlgTRC1752_MOD_PROG_INTF_BF* m_ModProgIntfBf;
	CDlgTRC1752_MOD_PROG_INTF_TC* m_ModProgIntfTc;
	CDlgTRC1752_MOD_PROG_INTF_ASS* m_ModProgIntfAss;
	CDlgTRC1752_MOD_PROG_INTF_PIL* m_ModProgIntfPil;

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_INTF)
	enum { IDD = IDD_MOD_PROG_INTF };
	CXTabCtrl	m_ModProgTab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_INTF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_INTF)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeModProg(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_INTF_H__F8D9AF8D_2B78_415C_B83C_FBF7AAC61341__INCLUDED_)
