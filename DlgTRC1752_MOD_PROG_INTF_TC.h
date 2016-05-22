#if !defined(AFX_DLGTRC1752_MOD_PROG_INTF_TC_H__1DD78987_8E01_4A3E_80DA_8FA7691E1BD4__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_INTF_TC_H__1DD78987_8E01_4A3E_80DA_8FA7691E1BD4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_INTF_TC.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_TC dialog

class CDlgTRC1752_MOD_PROG_INTF_TC : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_INTF_TC(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void razChoixInterfaceTC();
	void marcheTimer();
	void arretTimer();
	void miseajourInterfaceTC();


// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_INTF_TC)
	enum { IDD = IDD_MOD_PROG_INTF_TC };
	CEdit	c_AdresseRadio;
	CStatic	t_AdresseRadio;
	CStatic	t_Radio;
	CComboBox	c_Radio;
	CSpinButtonCtrl	s_AdresseRadio;
	CComboBox	c_Type;
	CComboBox	c_NbBitStop;
	CComboBox	c_Parite;
	CComboBox	c_NbBitDonnees;
	CComboBox	c_DebitTc;
	CComboBox	c_LiaisonTc;
	int		m_LiaisonTc;
	int		m_DebitTc;
	int		m_NbBitDonnees;
	int		m_Parite;
	int		m_NbBitStop;
	int		m_Type;
	int		m_AdresseRadio;
	int		m_Radio;
	//}}AFX_DATA
	int m_timerTC;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_INTF_TC)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void AffichageRadio();

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_INTF_TC)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTc();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnDeltaposAdresseRadioSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnKillfocusAdresseRadio();
	//}}AFX_MSG
	void AffichageConfigurationTC();
	void AffichageConfigurationTC(TLocalRemoteInterfaceConfiguration conf_courante);
	void AffichageConfigurationIA(TAuxInterfaceConfiguration conf_courante);
	void initTypeInterfaceTC();
	void initTypeInterfaceIA();
	// V3.0.2b
	void initTypeRadio(int typeInterface);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_INTF_TC_H__1DD78987_8E01_4A3E_80DA_8FA7691E1BD4__INCLUDED_)
