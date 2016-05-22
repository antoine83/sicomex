#if !defined(AFX_DLGTRC1752_MOD_PROG_STA_A2_H__47C1F723_12DD_4E15_AC9F_D7F24C01A558__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_STA_A2_H__47C1F723_12DD_4E15_AC9F_D7F24C01A558__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_STA_A2.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA_A2 dialog

class CDlgTRC1752_MOD_PROG_STA_A2 : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_STA_A2(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	int GetConfA2();
	int GetCanalA2();
	int GetIaA2();

	void StartTimer();
	void StopTimer();

	void MiseJourListeInterfaceTd();			// V3.0.1

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_STA_A2)
	enum { IDD = IDD_MOD_PROG_STA_A2 };
	CComboBox	c_A2_Conf;
	CStatic	c_MessageDeux;
	CStatic	c_MessageUn;
	CComboBox	m_A2_TD;
	CComboBox	m_A2_TA;
	CComboBox	m_A2_ModeAlternat;
	CComboBox	m_A2_Cix;
	CComboBox	m_A2_AleIndex;
	CComboBox	m_A2_Canal;
	CString	m_A2_Ia;
	int		m_A2_Conf;
	CString	m_A2_Mode;
	CString	m_MessageUn;
	CString	m_MessageDeux;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_STA_A2)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_STA_A2)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeProgStaA2Ta();
	afx_msg void OnSelchangeProgStaA2Td();
	afx_msg void OnDropdownProgStaA2Td();
	afx_msg void OnDropdownProgStaA2Canal();
	afx_msg void OnSelchangeProgStaA2Canal();
	afx_msg void OnDropdownProgStaA2Ta();
	afx_msg void OnDropdownProgStaA2Cix();
	afx_msg void OnSelchangeProgStaA2Cix();
	afx_msg void OnDropdownProgStaA2Ch();
	afx_msg void OnSelchangeProgStaA2Ch();
	afx_msg void OnDropdownProgStaA2Ma();
	afx_msg void OnSelchangeProgStaA2Ma();
	afx_msg void OnSelchangeProgStaA2Conf();
	afx_msg void OnProgStaA2Tst();
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

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_STA_A2_H__47C1F723_12DD_4E15_AC9F_D7F24C01A558__INCLUDED_)
