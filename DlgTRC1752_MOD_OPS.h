#if !defined(AFX_DLGTRC1752_MOD_OPS_H__F4386573_3DCF_4751_B913_12C22F1EE317__INCLUDED_)
#define AFX_DLGTRC1752_MOD_OPS_H__F4386573_3DCF_4751_B913_12C22F1EE317__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_OPS.h : header file
//

#include "Equip\EquipM1752.h"

typedef struct
{
	string l1;
	string l2;
	string l3;
	string l4;
} TAffichage;

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_OPS dialog

class CDlgTRC1752_MOD_OPS : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_OPS(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void razChoixConfiguration();
	void razOffsetFrequences();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_OPS)
	enum { IDD = IDD_MOD_OPS };
	CStatic	c_OpsMsgTest4;
	CProgressCtrl	m_Progress_Bf;
	CEdit	c_NiveauEmission;
	CSpinButtonCtrl	s_NiveauEmission;
	CButton	m_AmdMsgRaz;
	CStatic	t_EtatAle;
	CStatic	t_Distante;
	CStatic	c_OpsMsgTest3;
	CStatic	c_OpsMsgTest2;
	CStatic	c_OpsMsgTest;
	CButton	c_EtatTc;
	CStatic	c_Voie;
	CStatic	c_OpsMode;
	CEdit	c_AmdMsg;
	CStatic	c_OpsDiv;
	CStatic	c_OpsType;
	CStatic	c_EtatEmission;
	CStatic	c_EtatReception;
	CStatic	t_Rec1;
	CStatic	t_Emi1;
	CStatic	t_OpsDoppler;
	CStatic	t_NiveauReception;
	CButton	c_OpsRazBin;
	CStatic	t_Hz;
	CStatic	t_dbmr;
	CStatic	t_dbme;
	CButton	c_AleOpsP2;
	CStatic	c_DebitRec;
	CStatic	c_DebitEmi;
	CStatic	t_Rec2;
	CStatic	t_Emi2;
	CStatic	c_EtatDoppler;
	CStatic	c_FrqSpace;
	CStatic	c_FrqMark;
	CStatic	c_MilEn;
	CStatic	t_MilEn;
	CStatic	c_EtatAle;
	CButton	c_AleOpsP3;
	CStatic	c_AleType;
	CStatic	t_AleType;
	CStatic	c_AleFrom;
	CStatic	t_AleFrom;
	CComboBox	c_VoieOps;
	CStatic	c_AleTo;
	CStatic	t_AleTo;
	CStatic	c_AleQualite;
	CStatic	t_AleQualite;
	CStatic	c_AleChannel;
	CStatic	t_AleChannel;
	CComboBox	c_AleStatus;
	CButton	c_AleOps;
	CComboBox	c_VoieAle;
	CSpinButtonCtrl	s_FrqSpace;
	CSpinButtonCtrl	s_FrqMark;
	CString	m_OpsMode;
	CString	m_EtatAle;
	int		m_VoieAle;
	BOOL	m_AleOps;
	int		m_AleStatus;
	CString	m_AleChannel;
	CString	m_AleQualite;
	CString	m_AleFrom;
	CString	m_AleTo;
	int		m_VoieOps;
	CString	m_AleType;
	CString	m_MilEn;
	CString	m_FrqMark;
	CString	m_FrqSpace;
	CString	m_EtatDoppler;
	BOOL	m_EtatTc;
	CString	m_NiveauReception;
	CString	m_EtatReception;
	CString	m_EtatEmission;
	CString	m_OpsType;
	CString	m_OpsDiv;
	CString	m_AmdMsg;
	CString	m_OpsMsgTest;
	CString	m_OpsMsgTest2;
	CString	m_OpsMsgTest3;
	int		m_NiveauEmission;
	CString	m_OpsMsgTest4;
	//}}AFX_DATA
	int old_pos;
	int m_timerOps;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_OPS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL
	void AffichageFonctionMode(CString str);
	void AffichageFonctionAle(CString str);
	void AffichageFenetreUn(BOOL act);
	void AffichageFenetreDeux(BOOL act);
	void AffichageFenetreTrois(BOOL act);
	void AffichageMessageAMD();
	void AffichageFonctionEmiRec(CString str);

	void EmissionEnCours(string tmpStatus, int tmpNiveau);
	

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_OPS)
	virtual BOOL OnInitDialog();
	afx_msg void OnOutofmemoryOpsFrqMarkSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposOpsFrqMarkSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemoryOpsFrqSpaceSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposOpsFrqSpaceSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemoryOpsNivEmiSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposOpsNivEmiSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnOpsAleOps();
	afx_msg void OnOpsAleAmdRaz();
	afx_msg void OnSelchangeOpsVoieChoix();
	afx_msg void OnOpsRazBin();
	afx_msg void OnEditchangeOpsAleStatus();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int automate_test;

	BOOL fen1;
	BOOL fen2;
	BOOL fen3;

	vector<TAffichage> resultat_test;

	BOOL etat;
	void Test();
	void RemplirTest();
	void FinTest();
	void LoadData();
	void InitVoies();
	void ReceptionEnCours(string tmpStatus, int tmpQual, int tmpBf, string tmpCode);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_OPS_H__F4386573_3DCF_4751_B913_12C22F1EE317__INCLUDED_)
