#if !defined(AFX_DLGTRC1752_MOD_PROG_INTF_LIAS_H__61A79166_5164_45F2_8E1D_54840E2D1342__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_INTF_LIAS_H__61A79166_5164_45F2_8E1D_54840E2D1342__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_INTF_LIAS.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_LIAS dialog

class CDlgTRC1752_MOD_PROG_INTF_LIAS : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_INTF_LIAS(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void razChoixConfiguration();
	void marcheTimer();
	void arretTimer();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_INTF_LIAS)
	enum { IDD = IDD_MOD_PROG_INTF_LIAS };
	CComboBox	c_LiasTypeElec;
	CComboBox	c_LiasSynchro;
	CComboBox	c_LiasStab_A;
	CComboBox	c_LiasStab_S;
	CComboBox	c_LiasPol;
	CComboBox	c_LiasIntS;
	CComboBox	c_LiasIntA;
	CComboBox	c_LiasHEmi;
	CComboBox	c_LiasDpeA;
	CComboBox	c_LiasDpe;
	CComboBox	c_LiasDebitRec;
	CComboBox	c_LiasDebitEmi;
	CComboBox	c_LiasConf;
	CComboBox	c_Parite;
	CComboBox	c_NbStop;
	CComboBox	c_NbBits;
	CStatic	m_Dpe_A_Txt;
	CStatic	m_Dpe_S_Txt;
	CStatic	m_H_Em_Txt;
	CStatic	m_Int_S_Txt;
	CStatic	m_Stab_Txt;
	CStatic	m_Bits_Txt;
	CStatic	m_Stop_Txt;
	CStatic	m_Parite_Txt;
	CComboBox	m_CHLiasDpeA;
	CStatic	m_LiasStabS;
	CComboBox	m_ChLiasStab;
	int		m_LiasDebitEmi;
	int		m_LiasDebitRec;
	int		m_LiasDpe;
	int		m_LiasHEmi;
	int		m_LiasPol;
	int		m_LiasStab;
	int		m_LiasSynchro;
	int		m_LiasConf;
	int		m_LiasDpe_A;
	int		m_LiasInt_A;
	int		m_LiasInt_S;
	int		m_LiasStab_A;
	int		m_LiasStab_S;
	int		m_NbBits;
	int		m_NbStop;
	int		m_Parite;
	int		m_LiasTypeElec;
	//}}AFX_DATA
	int m_timerLias;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_INTF_LIAS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	bool TestDebit();
	void InitAsynchrone(bool affiche);
	void InitSynchrone(bool affiche);
	void ModificationConfiguration();

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_INTF_LIAS)
	afx_msg void OnSelchangeProgIntfLiasDebitE();
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeProgIntfLiasHEm();
	afx_msg void OnSelchangeProgIntfLiasSynchro();
	afx_msg void OnSelchangeProgIntfLiasConf();
	afx_msg void OnTimer(UINT nIDEvent);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_INTF_LIAS_H__61A79166_5164_45F2_8E1D_54840E2D1342__INCLUDED_)
