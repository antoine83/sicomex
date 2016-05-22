#if !defined(AFX_DLGED42PRESETSTAB_H__FF381272_CEDA_4828_9927_47701A2F1F0E__INCLUDED_)
#define AFX_DLGED42PRESETSTAB_H__FF381272_CEDA_4828_9927_47701A2F1F0E__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42PresetsTab.h : header file
//
#include "XTabCtrl.h"
#include "DlgED42GeneralParameter.h"
#include "DlgED42DigitalDCE.h"
#include "DlgED42AnalogDCE.h"
#include "DlgED42DigitalDTE.h"
#include "DlgED42AnalogDTE.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgED42PresetsTab dialog

class CDlgED42PresetsTab : public CDialog
{
// Construction
public:
	CDlgED42PresetsTab(CEquipED42 * eqp = NULL,CWnd* pParent = NULL);   // standard constructor	
	~CDlgED42PresetsTab();
	void CDlgED42PresetsTab::LoadData(string preset);
	void CDlgED42PresetsTab::SaveData();

// Dialog Data
	//{{AFX_DATA(CDlgED42PresetsTab)
	enum { IDD = IDD_ED42_PRESETS_TAB };
	CXTabCtrl	m_tab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42PresetsTab)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
public:
	CDlgED42GeneralParameter* m_generalParameter;
	

protected:
	CEquipED42 * eqp;
	//CDlgED42GeneralParameter* m_generalParameter;
	CDlgED42DigitalDCE* m_digitalDCE;
	CDlgED42AnalogDCE* m_analogDCE;
	CDlgED42DigitalDTE* m_digitalDTE;
	CDlgED42AnalogDTE* m_analogDTE;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42PresetsTab)
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeTab(NMHDR* pNMHDR, LRESULT* pResult);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private :
	int ongletSelection;
	//string* presetSelected;
	string presetSelected;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42PRESETSTAB_H__FF381272_CEDA_4828_9927_47701A2F1F0E__INCLUDED_)
