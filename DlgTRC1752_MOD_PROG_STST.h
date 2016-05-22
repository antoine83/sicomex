#if !defined(AFX_DLGTRC1752_MOD_PROG_STST_H__5DFA6F3E_49DA_45ED_A103_76EA50D41B9F__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_STST_H__5DFA6F3E_49DA_45ED_A103_76EA50D41B9F__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_STST.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STST dialog

class CDlgTRC1752_MOD_PROG_STST : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_STST(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void Erreur(const string type_erreur);
	void Erreur(string *l1 = NULL, string *l2 = NULL, string *l3 = NULL, string *l4 = NULL);
	void TestCartex(int cartex);
	void MiseJourListeCarte();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_STST)
	enum { IDD = IDD_MOD_PROG_STST };
	CStatic	c_Msg21;
	CStatic	c_Msg11;
	CStatic	c_Msg2;
	CStatic	c_Msg1;
	CStatic	m_Tst;
	CStatic	m_Val;
	CStatic	m_Esc;
	CStatic	m_Date_TT;
	CStatic	m_Date_BB;
	CStatic	m_Date_AA;
	CStatic	m_Version_TT;
	CStatic	m_Version_BB;
	CStatic	m_Version_AA;
	CStatic	m_Stst_T;
	CStatic	m_Stst_B;
	CStatic	m_Stst_A;
	CComboBox	m_TypeTst;
	CString	m_Version_A;
	CString	m_Version_B;
	CString	m_Version_T;
	CString	m_Date_A;
	CString	m_Date_B;
	CString	m_Date_T;
	CString	m_Msg1;
	CString	m_Msg2;
	CString	m_Msg11;
	CString	m_Msg21;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_STST)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;
	void AfficheCacheResultat( bool val);

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_STST)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeProgStstChType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void VideResultat();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_STST_H__5DFA6F3E_49DA_45ED_A103_76EA50D41B9F__INCLUDED_)
