#if !defined(AFX_DLGTRC1752_MOD_CONF_ARQ_H__355D60C2_1099_49A8_9A5B_CF0D1BC9EF54__INCLUDED_)
#define AFX_DLGTRC1752_MOD_CONF_ARQ_H__355D60C2_1099_49A8_9A5B_CF0D1BC9EF54__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_CONF_ARQ.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_ARQ dialog

class CDlgTRC1752_MOD_CONF_ARQ : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_CONF_ARQ(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void LoadData();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_CONF_ARQ)
	enum { IDD = IDD_MOD_CONF_ARQ };
	CStatic	t_ArqDebEmi;
	CButton	c_ArqDebRec;
	CButton	m_Fmp;
	CButton	m_Fmm;
	CButton	m_Top;
	CButton	m_Tom;
	CEdit	c_EtatArq;
	CButton	c_ArqEtablire;
	CButton	c_AdaptValider;
	CButton	c_ArqActiver;
	CStatic	t_To;
	CStatic	t_Fm;
	CStatic	t_Adapt;
	CComboBox	c_FonctionArq;
	CComboBox	c_ArqTo;
	CComboBox	c_ArqVoie;
	CComboBox	c_ArqFm;
	CComboBox	c_AdaptEntrelacement;
	CComboBox	c_AdaptDebit;
	int		m_ArqVoie;
	BOOL	m_AdaptSans;
	BOOL	m_Mod4285;
	BOOL	m_ModMil110;
	BOOL	m_AdaptAvec;
	BOOL	m_voieSachem;
	//}}AFX_DATA
	//BOOL	m_isAle;
	//BOOL	m_isArq;
	BOOL	m_isAdapt;
	CButton* pBtnVoieSachem;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_CONF_ARQ)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_CONF_ARQ)
	afx_msg void OnSelchangeFoncArq();
	virtual BOOL OnInitDialog();
	afx_msg void OnMod4285();
	afx_msg void OnAdaptAvec();
	afx_msg void OnAdaptSans();
	afx_msg void OnModMil110();
	afx_msg void OnArqActiver();
	afx_msg void OnAdaptValider();
	afx_msg void OnArqEtablir();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeArqVoie();
	afx_msg void OnButtonLocp();
	afx_msg void OnButtonLocm();
	afx_msg void OnButtonDesp();
	afx_msg void OnButtonDesm();
	afx_msg void OnSachemVoie();
	afx_msg void OnSelchangeArqFm();
	afx_msg void OnSelchangeAtqTo();
	afx_msg void OnArqDebRec();
	//}}AFX_MSG
	void AfficheAle(bool val);
	void AfficheAdapt(bool val);
	void GriseParametres(bool val);
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_CONF_ARQ_H__355D60C2_1099_49A8_9A5B_CF0D1BC9EF54__INCLUDED_)
