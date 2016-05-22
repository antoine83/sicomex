#if !defined(AFX_DLGTRC1752_MOD_PROG_STA_B2_H__5A0254B9_F9D4_4F86_8B4E_EE35C6785DA7__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_STA_B2_H__5A0254B9_F9D4_4F86_8B4E_EE35C6785DA7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_STA_B2.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA_B2 dialog

class CDlgTRC1752_MOD_PROG_STA_B2 : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_STA_B2(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	int GetConfB2();
	int GetCanalB2();
	int GetIaB2();

	void StartTimer();
	void StopTimer();

	void MiseJourListeInterfaceTd();		// V3.0.1

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_STA_B2)
	enum { IDD = IDD_MOD_PROG_STA_B2 };
	CComboBox	c_B2_Conf;
	CStatic	c_MessageDeux;
	CStatic	c_MessageUn;
	CComboBox	m_B2_TD;
	CComboBox	m_B2_TA;
	CComboBox	m_B2_ModeAlternat;
	CComboBox	m_B2_Cix;
	CComboBox	m_B2_AleIndex;
	CComboBox	m_B2_Canal;
	CString	m_B2_Ia;
	int		m_B2_Conf;
	CString	m_B2_Mode;
	CString	m_MessageUn;
	CString	m_MessageDeux;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_STA_B2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_STA_B2)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeProgStaB2Ta();
	afx_msg void OnSelchangeProgStaB2Td();
	afx_msg void OnDropdownProgStaB2Td();
	afx_msg void OnDropdownProgStaB2Canal();
	afx_msg void OnSelchangeProgStaB2Canal();
	afx_msg void OnDropdownProgStaB2Ta();
	afx_msg void OnDropdownProgStaB2Cix();
	afx_msg void OnSelchangeProgStaB2Cix();
	afx_msg void OnDropdownProgStaB2Ch();
	afx_msg void OnSelchangeProgStaB2Ch();
	afx_msg void OnDropdownProgStaB2Ma();
	afx_msg void OnSelchangeProgStaB2Ma();
	afx_msg void OnSelchangeProgStaB2Conf();
	afx_msg void OnProgStaB2Tst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool quadrivoie;
	int timerMsg;

	void AffichageFonctionTd();
	void AffichageFonctionMode(CString mdm);
	void AffichageFonctionTa();
	void AffichageIa(CString mdm);
	void InitialisationStation();
	void AffichageInfos();
	void AffichageInfosUn();
	void AffichageInfosDeux();
	void RazMessage();
	void AfficheMessageUn(CString msg);
	void AfficheMessageDeux(CString msg);
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_STA_B2_H__5A0254B9_F9D4_4F86_8B4E_EE35C6785DA7__INCLUDED_)
