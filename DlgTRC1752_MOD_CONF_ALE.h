#if !defined(AFX_DLGTRC1752_MOD_CONF_ALE_H__500D4C58_F5A9_4E52_ADB3_8EC153A7001A__INCLUDED_)
#define AFX_DLGTRC1752_MOD_CONF_ALE_H__500D4C58_F5A9_4E52_ADB3_8EC153A7001A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_CONF_ALE.h : header file
//

#include "Equip\EquipM1752.h"
#include "dlgequip.h"


#define REFRESH 1
#define TWA_A 2
#define TWA_B 3
#define SOUND_A 4
#define SOUND_B 5

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_ALE dialog

class CDlgTRC1752_MOD_CONF_ALE : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_CONF_ALE(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void LoadData();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_CONF_ALE)
	enum { IDD = IDD_MOD_CONF_ALE };
	CComboBox	c_Key;
	CComboBox	c_LT0;
	CComboBox	c_LP;
	CButton	c_Stap;
	CButton	c_Stam;
	CButton	c_Netp;
	CButton	c_Netm;
	CButton	c_EffacerAmd;
	CComboBox	c_Voie;
	CComboBox	c_OrigineHeure;
	CStatic	t_ListeReseau;
	CStatic	t_ListeStation;
	CComboBox	c_SelfAdresse;
	CButton	c_SendChat;
	CComboBox	c_Type_Call;
	CButton	c_LnlUnl;
	CComboBox	c_Type_Ale;
	CEdit	c_Msg_Amd;
	CComboBox	c_Stations;
	CComboBox	c_Reseaux;
	BOOL	m_Marche;
	BOOL	m_Amd;
	CString	m_Msg_Amd;
	BOOL    m_Chat;
	BOOL	m_Ch_50;
	BOOL	m_Ch_51;
	BOOL	m_Ch_52;
	BOOL	m_Ch_53;
	BOOL	m_Ch_54;
	BOOL	m_Ch_55;
	int		m_Type_Ale;
	BOOL	m_CH_56;
	BOOL	m_CH_57;
	BOOL	m_CH_58;
	BOOL	m_CH_59;
	int		m_Type_Call;
	CString	m_GicCleDeBase;
	CString	m_AmdMsgRecu;
	//}}AFX_DATA
	CButton* pBtn50;
	CButton* pBtn51;
	CButton* pBtn52;
	CButton* pBtn53;
	CButton* pBtn54;
	CButton* pBtn55;
	CButton* pBtn56;
	CButton* pBtn57;
	CButton* pBtn58;
	CButton* pBtn59;
	CButton* pBtnMarcheMdm;
	

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_CONF_ALE)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_CONF_ALE)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeSelfAdresse();
	afx_msg void OnSelchangeStations();
	afx_msg void OnSelchangeReseaux();
	afx_msg void OnAmd();
	afx_msg void OnEditchangeTypeAle();
	afx_msg void OnCh50();
	afx_msg void OnCh51();
	afx_msg void OnCh52();
	afx_msg void OnCh53();
	afx_msg void OnCh54();
	afx_msg void OnCh55();
	afx_msg void OnSelchangeTypeCall();
	afx_msg void OnCh56();
	afx_msg void OnCh57();
	afx_msg void OnCh58();
	afx_msg void OnCh59();
	afx_msg void OnAleLnlUnl();
	afx_msg void OnKillfocusLpGic();
	afx_msg void OnSelchangeLpOrgHeure();
	afx_msg void OnMarche();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnEffacerAmd();
	afx_msg void OnSendChat();
	afx_msg void OnKillfocusAmdMsg();
	afx_msg void OnButtonSadp();
	afx_msg void OnButtonSadm();
	afx_msg void OnButtonStap();
	afx_msg void OnButtonStam();
	afx_msg void OnButtonNetp();
	afx_msg void OnButtonNetm();
	afx_msg void OnButtonLt0p();
	afx_msg void OnButtonLt0m();
	afx_msg void OnButtonKeyp();
	afx_msg void OnButtonKeym();
	afx_msg void OnSelchangeComboLt0();
	afx_msg void OnSelchangeComboLp();
	afx_msg void OnSelchangeCOMBOKey();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool twa_a;
	bool twa_b;
	bool sound_a;
	bool sound_b;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_CONF_ALE_H__500D4C58_F5A9_4E52_ADB3_8EC153A7001A__INCLUDED_)
