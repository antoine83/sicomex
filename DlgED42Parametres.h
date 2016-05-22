#if !defined(AFX_DLGED42PARAMETRES_H__AC23FFFE_019F_47FC_AF7E_0F52DFF5199E__INCLUDED_)
#define AFX_DLGED42PARAMETRES_H__AC23FFFE_019F_47FC_AF7E_0F52DFF5199E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42Parametres.h : header file
//
#include "Equip\EquipED42.h"
#include "MyListCtrl.h"
#include "MyEdit.h"

#define DEVICE_ADDRESS_MAX 99
#define DEVICE_ADDRESS_MIN 1

#define HDLC_ADDRESS_MAX 254
#define HDLC_ADDRESS_MIN 1

/////////////////////////////////////////////////////////////////////////////
// CDlgED42Parametres dialog

class CDlgED42Parametres : public CDialog
{
// Construction
public:
	CDlgED42Parametres(CEquipED42 * equip = NULL, CWnd* pParent = NULL);   // standard constructor

	void LoadData();

// Dialog Data
	//{{AFX_DATA(CDlgED42Parametres)
	enum { IDD = IDD_ED42_PARAMETERS };
	CComboBox	c_remoteCtrl;
	CSpinButtonCtrl	s_hdlcAdrdess;
	CMyEdit	c_hdlcAddress;
	CButton	c_setHdlcAddress;
	CButton	c_setDeviceAddress;
	CButton	c_setDeviceId;
	CMyEdit	c_deviceAddress;
	CSpinButtonCtrl	s_deviceAddress;
	CEdit	c_deviceId;
	CMyListCtrl	m_parametres;
	int		m_deviceAddress;
	int		m_dsInterface;
	int		m_hdlcAddress;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42Parametres)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42Parametres)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDeltaposSpinDeviceAddress(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSetDeviceID();
	afx_msg void OnSetDeviceAddress();
	afx_msg void OnSetFactoryDefault();
	afx_msg void OnSetDsInterface();
	afx_msg void OnSetDSInterface102();
	afx_msg void OnSetHdlcAddress();
	afx_msg void OnDeltaposSpinP2(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnSelchangeComboRemote();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42PARAMETRES_H__AC23FFFE_019F_47FC_AF7E_0F52DFF5199E__INCLUDED_)
