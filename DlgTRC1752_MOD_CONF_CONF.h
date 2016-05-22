#if !defined(AFX_DLGTRC1752_MOD_CONF_CONF_H__934BE114_39DC_4D87_9E9F_65DC1A13C919__INCLUDED_)
#define AFX_DLGTRC1752_MOD_CONF_CONF_H__934BE114_39DC_4D87_9E9F_65DC1A13C919__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_CONF_CONF.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_CONF dialog

class CDlgTRC1752_MOD_CONF_CONF : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_CONF_CONF(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void LoadData();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_CONF_CONF)
	enum { IDD = IDD_MOD_CONF_CONF };
	CButton	c_Fft1302;
	CButton	c_ZtsPft;
	CButton	c_PiloteExterne;
	BOOL	m_PiloteExterne;
	BOOL	m_ZtsPft;
	BOOL	m_Fft1302;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_CONF_CONF)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_CONF_CONF)
	afx_msg void OnCheckPilExt();
	afx_msg void OnCheckZts();
	afx_msg void OnCheckFft1302();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_CONF_CONF_H__934BE114_39DC_4D87_9E9F_65DC1A13C919__INCLUDED_)
