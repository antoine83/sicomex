#if !defined(AFX_DLGTRC1752_MOD_PROG_ALE_LP_H__303F64A5_B1C3_4577_B516_471A83A7DDD4__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_ALE_LP_H__303F64A5_B1C3_4577_B516_471A83A7DDD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_ALE_LP.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_LP dialog

class CDlgTRC1752_MOD_PROG_ALE_LP : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_ALE_LP(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void marcheTimer();
	void arretTimer();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_ALE_LP)
	enum { IDD = IDD_MOD_PROG_ALE_LP };
	CEdit	c_LpHeureMiseAjour;
	CEdit	c_LpDateMiseAjour;
	CEdit	c_LpPrecissionActuelle;
	CEdit	c_LpOrigHeure;
	CEdit	c_LpNomLt1;
	CEdit	c_LpPeriodeCle;
	CEdit	c_LpIndexCle;
	CEdit	c_LpNomLt0;
	CEdit	c_LpNiveau;
	CComboBox	c_LpVoie;
	int		m_LpVoie;
	int		m_LpNiveau;
	CString	m_LpNomLt0;
	CString	m_LpIndexCle;
	CString	m_LpPeriodeCle;
	CString	m_LpDateMiseAjour;
	CString	m_LpHeureMiseAjour;
	CString	m_LpOrigHeure;
	CString	m_LpPrecisionActuelle;
	CString	m_LpNomLt1;
	//}}AFX_DATA
	int m_timerAleLp;
	int m_timerAleTime;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_ALE_LP)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_ALE_LP)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeLpChVoie();
	//}}AFX_MSG
	void AffichageConfigurationLP();
	void ChangementIndexCleLp();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_ALE_LP_H__303F64A5_B1C3_4577_B516_471A83A7DDD4__INCLUDED_)
