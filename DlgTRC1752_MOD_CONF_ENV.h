#if !defined(AFX_DLGTRC1752_MOD_CONF_ENV_H__F844B303_9A4C_453F_97A7_1C789D3828B7__INCLUDED_)
#define AFX_DLGTRC1752_MOD_CONF_ENV_H__F844B303_9A4C_453F_97A7_1C789D3828B7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_CONF_ENV.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_ENV dialog

class CDlgTRC1752_MOD_CONF_ENV : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_CONF_ENV(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	//void Valide();
	void LoadData();
//	void marcheTimer();
//	void arretTimer();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_CONF_ENV)
	enum { IDD = IDD_MOD_CONF_ENV };
	CString	m_Manufacturer;
	CString	m_IdModem;
	CString	m_ADd;
	CString	m_AMm;
	CString	m_ANr;
	CString	m_ANv;
	CString	m_AYy;
	CString	m_BDd;
	CString	m_BMm;
	CString	m_BNr;
	CString	m_BNv;
	CString	m_BYy;
	CString	m_ALg;
	CString	m_BLg;
	CString	m_TLg;
	CString	m_TDd;
	CString	m_TMm;
	CString	m_TNr;
	CString	m_TNv;
	CString	m_TYy;
	BOOL	m_TypeModem;
	//}}AFX_DATA
	CButton* pBtnTypeModem;


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_CONF_ENV)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_CONF_ENV)
		virtual BOOL OnInitDialog();
	afx_msg void OnKillfocusConfEnvManufacturer();
	afx_msg void OnKillfocusConfEnvIdModem();
	afx_msg void OnKillfocusConfEnvFoncALg();
	afx_msg void OnKillfocusConfEnvANv();
	afx_msg void OnKillfocusConfEnvANr();
	afx_msg void OnKillfocusConfEnvADd();
	afx_msg void OnKillfocusConfEnvAMm();
	afx_msg void OnKillfocusConfEnvAYy();
	afx_msg void OnKillfocusConfEnvFoncBLg();
	afx_msg void OnKillfocusConfEnvBNv();
	afx_msg void OnKillfocusConfEnvBNr();
	afx_msg void OnKillfocusConfEnvBDd();
	afx_msg void OnKillfocusConfEnvBMm();
	afx_msg void OnKillfocusConfEnvBYy();
	afx_msg void OnKillfocusConfEnvFoncTLg();
	afx_msg void OnKillfocusConfEnvTNv();
	afx_msg void OnKillfocusConfEnvTNr();
	afx_msg void OnKillfocusConfEnvTDd();
	afx_msg void OnKillfocusConfEnvTMm();
	afx_msg void OnKillfocusConfEnvTYy();
	afx_msg void OnTypeModem();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool validationJour(int jour);
	bool validationMois(int mois);
	bool validationAn(int an);


};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_CONF_ENV_H__F844B303_9A4C_453F_97A7_1C789D3828B7__INCLUDED_)
