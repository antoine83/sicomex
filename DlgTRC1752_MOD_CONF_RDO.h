#if !defined(AFX_DLGTRC1752_MOD_CONF_RDO_H__1211D6B6_3505_4ED0_BA98_33651C09DC34__INCLUDED_)
#define AFX_DLGTRC1752_MOD_CONF_RDO_H__1211D6B6_3505_4ED0_BA98_33651C09DC34__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_CONF_RDO.h : header file
//

#include "MyEdit.h"
#include "Equip\EquipM1752.h"

#define NIV_BF_MAX 10
#define NIV_BF_MIN -30
#define NIV_QUAL_MIN 0
#define NIV_QUAL_MAX 31
#define NIV_DOPPLER_MAX 250
#define NIV_DOPPLER_MIN -250


/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_RDO dialog

class CDlgTRC1752_MOD_CONF_RDO : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_CONF_RDO(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void LoadData();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_CONF_RDO)
	enum { IDD = IDD_MOD_CONF_RDO };
	CButton	m_RecMil;
	CButton	m_Alt_Msg;
	CMyEdit	c_NiveauQualite;
	CMyEdit	c_NiveauBfReceptionEsclave;
	CMyEdit	c_Doppler;
	CMyEdit	c_NiveauBfReception;
	CComboBox	c_Ale_Voie;
	CComboBox	c_VoieMaitre;
	CComboBox	c_VoieEsclave;
	CSpinButtonCtrl	s_Doppler;
	CSpinButtonCtrl	s_NiveauBfReceptionEsclave;
	CSpinButtonCtrl	s_NiveauQualite;
	CSpinButtonCtrl	s_NiveauBfReception;
	BOOL	m_MarcheRecepteur;
	BOOL	m_MarcheEmetteur;
	BOOL	m_PanneTcE;
	BOOL	m_PanneTcR;
	BOOL	m_PanneMajeureE;
	BOOL	m_PanneMajeureR;
	int		m_NiveauBfReception;
	int		m_NiveauQualite;
	int		m_NiveauBfReceptionEsclave;
	int		m_Doppler;
	BOOL	m_EmetteurEmission;
	BOOL	m_recMil;
	//}}AFX_DATA
	CButton* pBtnMarcheEmi;
	CButton* pBtnMarcheRec;
	CButton* pBtnPanneTcEmi;
	CButton* pBtnPanneMjEmi;
	CButton* pBtnPanneTcRec;
	CButton* pBtnPanneMjRec;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_CONF_RDO)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_CONF_RDO)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAmE();
	afx_msg void OnAmR();
	afx_msg void OnDeltaposNivBfRecSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposNiveuaQualiteSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposDopplerSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnDeltaposNivBfRecSSpin(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeConfVoieMaitre();
	afx_msg void OnSelchangeConfVoieEsclave();
	afx_msg void OnPanneMajE();
	afx_msg void OnPanneTcE();
	afx_msg void OnPanneMajR();
	afx_msg void OnPanneTcR();
	afx_msg void OnKillfocusNivBfRec();
	afx_msg void OnKillfocusNivBfRecS();
	afx_msg void OnKillfocusNiveauQualite();
	afx_msg void OnKillfocusDoppler();
	afx_msg void OnButtonAleMsg();
	afx_msg void OnEmeteurEmi();
	afx_msg void OnSetfocusNivBfRec();
	afx_msg void OnSetfocusNiveauQualite();
	afx_msg void OnSetfocusDoppler();
	afx_msg void OnSetfocusNivBfRecS();
	afx_msg void OnEditchangeComboAleVoie();
	afx_msg void OnSelchangeComboAleVoie();
	afx_msg void OnRecMil();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool inr_run;
	int inr_rate;
	int timerMsg;

	void FinEmissionMsg();
	void AfficheParams(bool res);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_CONF_RDO_H__1211D6B6_3505_4ED0_BA98_33651C09DC34__INCLUDED_)
