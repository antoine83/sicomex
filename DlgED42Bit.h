#if !defined(AFX_DLGED42BIT_H__6581D225_8FA0_45D2_98EE_8AA8EE878AE2__INCLUDED_)
#define AFX_DLGED42BIT_H__6581D225_8FA0_45D2_98EE_8AA8EE878AE2__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42Bit.h : header file
//
#include "Equip\EquipED42.h"

/////////////////////////////////////////////////////////////////////////////
// DlgED42Bit dialog

class DlgED42Bit : public CDialog
{
// Construction
public:
	DlgED42Bit(CEquipED42* eqp=NULL ,CWnd* pParent = NULL);   // standard constructor
	void DlgED42Bit::SaveData();
	void DlgED42Bit::LoadData();
// Dialog Data
	//{{AFX_DATA(DlgED42Bit)
	enum { IDD = IDD_ED42_BIT };
	CButton	c_lancerTest;
	CButton	c_ramTest;
	CButton	c_integritySoftware;
	CButton	c_flashMemoryTest;
	CButton	c_enAndDecryptionSignal;
	CButton	c_checkingSupplyVoltage;
	CButton	c_bitTestPlugs;
	CButton	c_bitHeadset;
	CButton	c_bitDS101Test;
	CButton	c_batteryTest;
	CButton	c_bitControlUnit;
	CString	m_resultTest;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgED42Bit)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42* eqp;
	// Generated message map functions
	//{{AFX_MSG(DlgED42Bit)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	virtual void OnCancel();
	afx_msg void OnButtonLancerTest();
	afx_msg void OnCheckBatteryTest();
	afx_msg void OnCheckBitControlUnit();
	afx_msg void OnCheckBitWithoutTestPlugs();
	afx_msg void OnCheckBitDs101Test();
	afx_msg void OnCheckBitHeadset();
	afx_msg void OnCheckCheckingSupplyVoltage();
	afx_msg void OnCheckEnDecryptionSignal();
	afx_msg void OnCheckFlashMemoryTest();
	afx_msg void OnCheckIntegritySoftware();
	afx_msg void OnCheckRamTest();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42BIT_H__6581D225_8FA0_45D2_98EE_8AA8EE878AE2__INCLUDED_)
