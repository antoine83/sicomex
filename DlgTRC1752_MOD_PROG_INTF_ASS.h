#if !defined(AFX_DLGTRC1752_MOD_PROG_INTF_ASS_H__E5B31021_299B_400B_896E_480506FE0559__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_INTF_ASS_H__E5B31021_299B_400B_896E_480506FE0559__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_INTF_ASS.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_ASS dialog

class CDlgTRC1752_MOD_PROG_INTF_ASS : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_INTF_ASS(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void razChoixDataLink();

	void StartTimer();
	void StopTimer();
	void MiseJourListeInterfaceTd();			// V3.0.1

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_INTF_ASS)
	enum { IDD = IDD_MOD_PROG_INTF_ASS };
	CStatic	m_Info;
	CStatic	m_Donnees_Txt;
	CComboBox	m_ChDonnees;
	CComboBox	m_ChConfiguration;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_INTF_ASS)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_INTF_ASS)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnSelchangeProgIntfDonnees();
	afx_msg void OnDropdownProgIntfDonnees();
	afx_msg void OnDropdownProgIntfAssConfiguration();
	afx_msg void OnSelchangeProgIntfAssConfiguration();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool quadrivoie;
	void MiseJourAssociation();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_INTF_ASS_H__E5B31021_299B_400B_896E_480506FE0559__INCLUDED_)
