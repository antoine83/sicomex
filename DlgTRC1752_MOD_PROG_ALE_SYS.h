#if !defined(AFX_DLGTRC1752_MOD_PROG_ALE_SYS_H__3F8AA4B2_3B5E_413F_A78D_C29EBCC864C6__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_ALE_SYS_H__3F8AA4B2_3B5E_413F_A78D_C29EBCC864C6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_ALE_SYS.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_ALE_SYS dialog

class CDlgTRC1752_MOD_PROG_ALE_SYS : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_ALE_SYS(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void marcheTimer();
	void arretTimer();
	void AffichageInfos();
	void RazCanal();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_ALE_SYS)
	enum { IDD = IDD_MOD_PROG_ALE_SYS };
	CEdit	c_AleSysTT;
	CEdit	c_AleSysTwt;
	CEdit	c_AleSysTwaMm;
	CEdit	c_AleSysTwaMa;
	CSpinButtonCtrl	s_AleSysTwt;
	CSpinButtonCtrl	s_AleSysTwaMm;
	CSpinButtonCtrl	s_AleSysTwaMA;
	CSpinButtonCtrl	s_AleSysTT;
	CComboBox	m_ChAleSysSR;
	CComboBox	m_ChAleSysSounding;
	CComboBox	m_ChAleSysPtt;
	CComboBox	m_ChAleSysIat;
	CComboBox	m_ChAleSysFscanning;
	CComboBox	m_ChAleSysCanal;
	int		m_AleSysCanal;
	int		m_AleSysFscanning;
	int		m_AleSysIat;
	int		m_AleSysPtt;
	int		m_AleSysSounding;
	int		m_AleSysSR;
	int		m_AleSysTT;
	int		m_AleSysTwaMa;
	int		m_AleSysTwaMm;
	int		m_AleSysTwt;
	//}}AFX_DATA
	int m_timerAleSys;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_ALE_SYS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_ALE_SYS)
	afx_msg void OnOutofmemorySpinTwaMa(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySpinTwt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySpinTwaMm(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemorySpinTt(NMHDR* pNMHDR, LRESULT* pResult);
	virtual BOOL OnInitDialog();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnDeltaposSpinTwaMa(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTwt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTwaMm(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposSpinTt(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeProgAleSysCanal();
	//}}AFX_MSG
	//void AffichageInfos();
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_ALE_SYS_H__3F8AA4B2_3B5E_413F_A78D_C29EBCC864C6__INCLUDED_)
