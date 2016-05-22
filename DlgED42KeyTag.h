#if !defined(AFX_DLGED42KEYTAG_H__A2E04241_2835_4F42_B1F9_F6CCC7075BD9__INCLUDED_)
#define AFX_DLGED42KEYTAG_H__A2E04241_2835_4F42_B1F9_F6CCC7075BD9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42KeyTag.h : header file
//
#include "Equip\EquipED42.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyTag dialog

class CDlgED42KeyTag : public CDialog
{
// Construction
public:
	CDlgED42KeyTag(CEquipED42 * eqp = NULL,CWnd* pParent = NULL);   // standard constructor
	void CDlgED42KeyTag::LoadData();
	void CDlgED42KeyTag::SaveData();
// Dialog Data
	//{{AFX_DATA(CDlgED42KeyTag)
	enum { IDD = IDD_ED42_KEY_TAB_TAG };
	CComboBox	c_presetLocation;
	CComboBox	c_variableLocation;
	CComboBox	c_presetType;
	CString	m_date;
	CString	m_presetTagged;
	CString	m_updateCount;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42KeyTag)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42 * eqp;
	void CDlgED42KeyTag::buildComposant(int composant);
	// Generated message map functions
	//{{AFX_MSG(CDlgED42KeyTag)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeComboPresetType();
	afx_msg void OnSelchangeComboVarLocation();
	afx_msg void OnSelchangeComboPresetLocation();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42KEYTAG_H__A2E04241_2835_4F42_B1F9_F6CCC7075BD9__INCLUDED_)
