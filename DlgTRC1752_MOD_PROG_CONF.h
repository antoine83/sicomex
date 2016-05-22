#if !defined(AFX_DLGTRC1752_MOD_PROG_CONF_H__7BE379ED_FCDF_4768_AFA6_053360491B8C__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_CONF_H__7BE379ED_FCDF_4768_AFA6_053360491B8C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_CONF.h : header file
//

#include "Equip\EquipM1752.h"

//La fréquence centrale utilisée dans le sens émission réglable de 900 Hz à 2400 Hz par pas de 100 Hz,
#define FRQCMIN 900
#define FRQCMAX 2400
#define FRQCPAS 100

//fréquence "Space" et "Mark" : réglable de 300 Hz à 3300 Hz par pas de 1 Hz.
#define FRQBASSE 300
#define FRQHAUTE 3300
#define FRQPAS	1

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_CONF dialog

class CDlgTRC1752_MOD_PROG_CONF : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_CONF(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void razChoixCanal();
	void marcheTimer();
	void arretTimer();
	void Consultation(string conf);
	void Modification(string conf);
	void enleveMC();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_CONF)
	enum { IDD = IDD_MOD_PROG_CONF };
	CSpinButtonCtrl	s_Frq_Div_C_E;
	CEdit	c_Frq_Div_C_E;
	CComboBox	c_DivSousMode;
	CComboBox	c_DivEntrelaceurEmi;
	CComboBox	c_DivDebitEmi;
	CStatic	t_DivE;
	CComboBox	c_DivSortieData;
	CStatic	t_DivInfo;
	CButton	m_ModProgDiv;
	CStatic	t_ChoixDiv;
	CEdit	c_Frq_H_Rec;
	CEdit	c_Frq_H_Emi;
	CEdit	c_Frq_B_Emi;
	CComboBox	c_ChoixDiv;
	CComboBox	c_ChoixEntE;
	CComboBox	c_ChoixEntR;
	CComboBox	c_ChoixSousMode;
	CComboBox	c_Shift_R;
	CComboBox	c_Shift_E;
	CEdit	c_Frq_B_Rec;
	CComboBox	c_SP_E;
	CComboBox	c_SP_R;
	CComboBox	c_ChoixDebitR;
	CComboBox	c_ChoixDebitE;
	CComboBox	c_ChoixMode;
	CComboBox	c_ChoixCanal;
	CStatic	t_E;
	CStatic	t_T;
	CStatic	t_SP_E;
	CStatic	t_Shift;
	CStatic	t_R;
	CStatic	t_Frq_C_E;
	CStatic	t_Frq_H_E;
	CStatic	t_Frq_B_E;
	CStatic	t_Entrelaceur;
	CStatic	t_Debit;
	CSpinButtonCtrl	s_FrqE;
	CSpinButtonCtrl	s_Frq_H_E;
	CSpinButtonCtrl	s_Frq_H_R;
	CSpinButtonCtrl	s_FrqR;
	CSpinButtonCtrl	s_Frq_B_R;
	CSpinButtonCtrl	s_Frq_B_E;
	CEdit	m_FrqR;
	CEdit	m_FrqE;
	int		m_Frq_C_E;
	int		m_Frq_B_Emi;
	int		m_Frq_B_Rec;
	int		m_Frq_H_Emi;
	int		m_Frq_H_Rec;
	int		m_Frq_C_R;
	int		m_ChoixCanal;
	int		m_ChoixMode;
	int		m_ChoixDebitE;
	int		m_ChoixDebitR;
	int		m_SP_R;
	int		m_SP_E;
	int		m_Shift_E;
	int		m_Shift_R;
	int		m_ChoixSousMode;
	int		m_ChoixEntR;
	int		m_ChoixEntE;
	int		m_ChoixDiv;
	int		m_DivSortieData;
	int		m_DivDebitEmi;
	int		m_DivEntrelaceurEmi;
	int		m_DivSousMode;
	int		m_Frq_Div_C_E;
	//}}AFX_DATA
	int m_timerConf;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_CONF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_CONF)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeProgConfChMode();
	afx_msg void OnShowWindow(BOOL bShow, UINT nStatus);
	afx_msg void OnOutofmemoryProgConfFrqESpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposProgConfFrqESpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemoryProgConfFrqHESpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposProgConfFrqHESpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemoryProgConfFrqHRSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposProgConfFrqHRSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemoryProgConfFrqRSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposProgConfFrqRSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemoryProgConfFrqBESpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposProgConfFrqBESpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnOutofmemoryProgConfFrqBRSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposProgConfFrqBRSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeProgConfChCanal();
	afx_msg void OnEditupdateProgConfChMode();
	afx_msg void OnEditchangeProgConfChDebitE();
	afx_msg void OnSelchangeProgConfChDebitE();
	afx_msg void OnSelchangeProgConfChEntE();
	afx_msg void OnSelchangeProgConfChDebitR();
	afx_msg void OnSelchangeProgConfChEntR();
	afx_msg void OnEditupdateProgConfChDebitE();
	afx_msg void OnEditchangeProgConfChDebitR();
	afx_msg void OnEditupdateProgConfChDebitR();
	afx_msg void OnEditchangeProgConfChEntE();
	afx_msg void OnEditupdateProgConfChEntE();
	afx_msg void OnEditchangeProgConfChEntR();
	afx_msg void OnEditupdateProgConfChEntR();
	afx_msg void OnSelchangeProgConfChSMode();
	afx_msg void OnEditchangeProgConfChSMode();
	afx_msg void OnEditupdateProgConfChSMode();
	afx_msg void OnKillfocusProgConfFrqE();
	afx_msg void OnKillfocusProgConfFrqR();
	afx_msg void OnKillfocusProgConfFrqBE();
	afx_msg void OnKillfocusProgConfFrqBR();
	afx_msg void OnSelchangeProgConfShiftE();
	afx_msg void OnSelchangeProgConfSpE();
	afx_msg void OnSelchangeProgConfSpR();
	afx_msg void OnSelchangeProgConfShiftR();
	afx_msg void OnSelchangeProgConfChDiv();
	afx_msg void OnChangeProgConfFrqHE();
	afx_msg void OnChangeProgConfFrqBE();
	afx_msg void OnKillfocusProgConfFrqHE();
	afx_msg void OnKillfocusProgConfFrqHR();
	afx_msg void OnOutofmemoryProgConfFrqEDivSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposProgConfFrqEDivSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeProgDivSortieData();
	afx_msg void OnSelchangeProgDivSousMode();
	afx_msg void OnSelchangeProgDivChDebitE();
	afx_msg void OnSelchangeProgDivChEntE();
	afx_msg void OnChangeProgConfFrqHR();
	afx_msg void OnChangeProgConfFrqBR();
	//}}AFX_MSG
	void EffaceALL();
	void Affiche4285();
	void InitialisationListeDebitE();
	void InitialisationListeDebitR();
	void InitialisationEntrelaceurRec();
	void InitialisationEntrelaceurMIL110();
	void InitialisationListeDebit4285();
	void InitialisationListeDebit4529();
	void InitialisationListeDebitFSK();
	void InitialisationListeDebitMIL110();
	void InitialisationListeEntrelaceurMIL110();
	void Affiche4529();
	void AfficheFSKV();
	void AfficheFSKP();
	void AfficheMIL110();
	void CacheControles(int selection);
	void AfficheFonctionSousModeRE(bool selection);
	void AfficheFonctionSousModeEM(bool selection);
	void AfficheCacheDebitE(bool act);
	void AfficheCacheDebitR(bool act);
	void AfficheCacheEntrelaceurE(bool act);
	void AfficheCacheEntrelaceurR(bool act);
	void AfficheCacheFrqHauteE(bool act);
	void AfficheCacheFrqBasseE(bool act);
	void AfficheCacheFrqHauteR(bool act);
	void AfficheCacheFrqBasseR(bool act);
	void AfficheCacheFrqCentraleE(bool act);
	void AfficheCacheFrqCentraleR(bool act);
	void AfficheCacheDiversite(bool act);
	void AfficheCache2cas(bool act);
	bool verifFskv(int Fh, int Fb, CString Debit);
	void ModificationCanal();

	void OnSetfocusFRQ_H_E();
	void OnSetfocusFRQ_H_R();
	void OnSetfocusFRQ_B_E();
	void OnSetfocusFRQ_B_R();

	bool TestCanal();

	void ActivElemConsult();	//Activation de éléments de la fenetre Prog Conf
	void DesactivElemConsult();	//Désactivation de éléments de la fenetre Prog Conf

	DECLARE_MESSAGE_MAP()

private:
	string mc_value;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_CONF_H__7BE379ED_FCDF_4768_AFA6_053360491B8C__INCLUDED_)
