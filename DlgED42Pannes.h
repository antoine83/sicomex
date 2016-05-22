#if !defined(AFX_DLGED42PANNES_H__629D82D0_2A73_4716_8F26_BF7C01063888__INCLUDED_)
#define AFX_DLGED42PANNES_H__629D82D0_2A73_4716_8F26_BF7C01063888__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42Pannes.h : header file
//
#include "Equip\EquipED42.h"

/////////////////////////////////////////////////////////////////////////////
// DlgED42Pannes dialog

class DlgED42Pannes : public CDialog
{
// Construction
public:
	DlgED42Pannes(CEquipED42* equip=NULL ,CWnd* pParent = NULL);   // standard constructor

	void DlgED42Pannes::SaveData();
	void DlgED42Pannes::LoadData();
// Dialog Data
	//{{AFX_DATA(DlgED42Pannes)
	enum { IDD = IDD_ED42_PANNES };
	CButton	m_CryptoalarmTamper;
	CButton	m_CryptoalarmNotl;
	CButton	m_ZssUnexStateStartup;
	CButton	m_ZssUnexStateIdle;
	CButton	m_ZssManagCrc;
	CButton	m_ZssFlashMagicError;
	CButton	m_ZssFlashError;
	CButton	m_ZssErrorInterfacebit;
	CButton	m_KeUnexStateIndisposed;
	CButton	m_CryptoalarmGlobal;
	CButton	m_CeVarStatError;
	CButton	m_CeUnexStatePoweron;
	CButton	m_CeUnexStateInitcik2Idle;
	CButton	m_CeUnexStateDelcikuserIdle;
	CButton	m_CeUnexStateAout;
	CButton	m_CeUnexOnlineMode;
	CButton	m_CeStarttxErrorOnline;
	CButton	m_CeStartrxErrorOnline;
	CButton	m_CeStartErrorOnline;
	CButton	m_CeSkmTimeoutAout;
	CButton	m_CePwdtestError;
	CButton	m_CePrepErrorComsetup;
	CButton	m_CeCikSystemError;
	CButton	m_CeActivErrorCrysetup2;
	CButton	m_CeActivErrorCrysetup;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgED42Pannes)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42* equip;
	// Generated message map functions
	//{{AFX_MSG(DlgED42Pannes)
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnCheckZssManagCrc();
	afx_msg void OnCheckZssUnexStateStartup();
	afx_msg void OnCheckKeUnexStateIndisposed();
	afx_msg void OnCheckZssFlashMagicError();
	afx_msg void OnCheckZssFlashError();
	afx_msg void OnCheckZssUnexStateIdle();
	afx_msg void OnCheckZssErrorInterfacebit();
	afx_msg void OnCheckCeSkmTimeoutAout();
	afx_msg void OnCheckCePwdtestError();
	afx_msg void OnCheckCeVarStatError();
	afx_msg void OnCheckCeUnexStateAout();
	afx_msg void OnCheckCeUnexStatePoweron();
	afx_msg void OnCheckCeUnexStateInitcik2Idle();
	afx_msg void OnCheckCeUnexStateDelcikuserIdle();
	afx_msg void OnCheckCeCikSystemError();
	afx_msg void OnCheckCeActivErrorCrysetup();
	afx_msg void OnCheckCeActivErrorCrysetup2();
	afx_msg void OnCheckCePrepErrorComsetup();
	afx_msg void OnCheckCeUnexOnlineMode();
	afx_msg void OnCheckCeStartErrorOnline();
	afx_msg void OnCheckCeStartrxErrorOnline();
	afx_msg void OnCheckCeStarttxErrorOnline();
	afx_msg void OnCheckCryptoalarmNotl();
	afx_msg void OnCheckCryptoalarmTamper();
	afx_msg void OnCheckCryptoalarmGlobal();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()	
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42PANNES_H__629D82D0_2A73_4716_8F26_BF7C01063888__INCLUDED_)
