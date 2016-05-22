#if !defined(AFX_DLGED42PRESETS_H__064461CF_9249_4A3F_BB20_B93B3C180F1A__INCLUDED_)
#define AFX_DLGED42PRESETS_H__064461CF_9249_4A3F_BB20_B93B3C180F1A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42Presets.h : header file
//
#include "Equip\EquipED42.h"
#include "DlgED42PresetsTab.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgED42Presets dialog

class CDlgED42Presets : public CDialog
{
// Construction
public:
	CDlgED42Presets(CEquipED42 * eqp = NULL,CWnd* pParent = NULL);   // standard constructor
	~CDlgED42Presets();
	void CDlgED42Presets::LoadData();
	void CDlgED42Presets::SaveData();
	CDlgED42PresetsTab* CDlgED42Presets::getTab();

// Dialog Data
	//{{AFX_DATA(CDlgED42Presets)
	enum { IDD = IDD_ED42_PRESETS };
	CComboBox	c_type;
	CComboBox	c_preset;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42Presets)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

	

// Implementation
protected:
	CEquipED42 * eqp;
	//CDlgED42PresetsTab* m_presetTab;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42Presets)
		afx_msg void OnSelchangePreset();
		afx_msg void OnSelchangeType();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private :
	string presetSelected;
public:
	CDlgED42PresetsTab* m_presetTab;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42PRESETS_H__064461CF_9249_4A3F_BB20_B93B3C180F1A__INCLUDED_)
