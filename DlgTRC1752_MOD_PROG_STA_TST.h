#if !defined(AFX_DLGTRC1752_MOD_PROG_STA_TST_H__B66CA7F0_9EB1_4DBB_93E5_5F928A84ED45__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_STA_TST_H__B66CA7F0_9EB1_4DBB_93E5_5F928A84ED45__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_STA_TST.h : header file
//

#include "Equip\EquipM1752.h"

const int NB_INTTD = 4; // D1..D6

const string INTTD[NB_INTTD] = {
	"TEST_D1",
	"TEST_D2",
	"TEST_D5",
	"TEST_D6"
};

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA_TST dialog

class CDlgTRC1752_MOD_PROG_STA_TST : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_STA_TST(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void Esc();
	void InitVoie(const int voie);

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_STA_TST)
	enum { IDD = IDD_MOD_PROG_STA_TST };
	CComboBox	c_TypeRebouclage;
	CEdit	c_TestInterfaceTc;
	CEdit	c_TestInterfaceTd;
	CEdit	c_RebouclageBf;
	CEdit	c_1800Hz;
	CEdit	c_TstVoie;
	CStatic	c_TstMessageDeux;
	CStatic	c_TstMessageUn;
	CString	m_TstMessageUn;
	CString	m_TstMessageDeux;
	CString	m_TstVoie;
	CString	m_1800Hz;
	CString	m_RebouclageBf;
	CString	m_TestInterfaceTd;
	CString	m_TestInterfaceTc;
	int		m_TypeRebouclage;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_STA_TST)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_STA_TST)
	virtual BOOL OnInitDialog();
	afx_msg void OnSetfocus1800Hz();
	afx_msg void OnSetfocusRebouclageBf();
	afx_msg void OnSetfocusTestDx();
	afx_msg void OnSetfocusTestTc();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeTypeRebouclage();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

	void OnSetfocusVoie();
	void Tests(int typeTest);

private:
	string test_choisi;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_STA_TST_H__B66CA7F0_9EB1_4DBB_93E5_5F928A84ED45__INCLUDED_)
