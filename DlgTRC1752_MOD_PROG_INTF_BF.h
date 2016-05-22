#if !defined(AFX_DLGTRC1752_MOD_PROG_INTF_BF_H__01357AC6_A213_43D8_8EF3_1880F41C11A9__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_INTF_BF_H__01357AC6_A213_43D8_8EF3_1880F41C11A9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_INTF_BF.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_BF dialog

class CDlgTRC1752_MOD_PROG_INTF_BF : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_INTF_BF(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void razChoixInterfaceBF();
	void marcheTimer();
	void arretTimer();
	void MiseJourListeInterfaceBf();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_INTF_BF)
	enum { IDD = IDD_MOD_PROG_INTF_BF };
	CComboBox	c_TypeInterfaceBf;
	CComboBox	c_BlRec;
	CComboBox	c_TypeAlternat;
	CSpinButtonCtrl	s_TempoBourRadio;
	CEdit	c_TempoBourRadio;
	CSpinButtonCtrl	s_TempoBlRec;
	CEdit	c_TempoBlRec;
	CSpinButtonCtrl	s_TempoAlternat;
	CEdit	c_TempoAlternat;
	CStatic	t_NiveauBfSortie;
	CComboBox	c_InterfaceBf1;
	CStatic	t_Alternat;
	CSpinButtonCtrl	s_NiveauBfSortie;
	CEdit	c_InterfaceBf4;
	CEdit	c_InterfaceBf3;
	CEdit	c_InterfaceBf2;
	CSpinButtonCtrl	s_NiveauBfEmission;
	CString	m_InterfaceBf2;
	CString	m_InterfaceBf3;
	CString	m_InterfaceBf4;
	int		m_InterfaceBf1;
	int		m_NiveauBfSortie;
	int		m_NiveauBfEntree;
	int		m_TypeAlternat;
	int		m_TempoAlternat;
	int		m_BlRec;
	int		m_TempoBlRec;
	int		m_TypeInterfaceBf;
	int		m_TempoBourRadio;
	//}}AFX_DATA
	int m_timerBF;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_INTF_BF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_INTF_BF)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeProgIntfBf();
	afx_msg void OnDeltaposNivBfESpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDeltaposNivBfSSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusNivBfSortie();
	afx_msg void OnKillfocusNivBfEntree();
	afx_msg void OnKillfocusTempoAlt();
	afx_msg void OnKillfocusTempoBlRec();
	afx_msg void OnKillfocusTempoBourRadio();
	afx_msg void OnDeltaposTempoAltSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposTempoBlRecSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposTempoBourRadioSpin(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	void AffichageConfiguration();
	void MemorisationConfiguration();

	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_INTF_BF_H__01357AC6_A213_43D8_8EF3_1880F41C11A9__INCLUDED_)
