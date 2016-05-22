#if !defined(AFX_DLGTRC1752_MOD_PROG_INTF_PIL_H__66765229_9B9E_44BA_BFCC_2BFB8F1AFB11__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_INTF_PIL_H__66765229_9B9E_44BA_BFCC_2BFB8F1AFB11__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_INTF_PIL.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_INTF_PIL dialog

class CDlgTRC1752_MOD_PROG_INTF_PIL : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_INTF_PIL(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	void marcheTimer();
	void arretTimer();

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_INTF_PIL)
	enum { IDD = IDD_MOD_PROG_INTF_PIL };
	CStatic	c_PiloteInfo;
	CStatic	m_Pilote_Txt;
	CComboBox	m_ChPilote;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_INTF_PIL)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;
	bool modif;
	int m_timerPIL;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_INTF_PIL)
	afx_msg void OnTimer(UINT nIDEvent);
	virtual BOOL OnInitDialog();
	afx_msg void OnDropdownProgIntfPil();
	afx_msg void OnSelchangeProgIntfPil();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_INTF_PIL_H__66765229_9B9E_44BA_BFCC_2BFB8F1AFB11__INCLUDED_)
