#if !defined(AFX_DLGTRC1752_MOD_PROG_STA_B1_H__422F33F6_AC92_4FD9_A54F_7CD0CAF10C81__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_STA_B1_H__422F33F6_AC92_4FD9_A54F_7CD0CAF10C81__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgTRC1752_MOD_PROG_STA_B1.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA_B1 dialog

class CDlgTRC1752_MOD_PROG_STA_B1 : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_STA_B1(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	int GetConfB1();
	int GetCanalB1();
	int GetIaB1();

	void StartTimer();
	void StopTimer();

	void MiseJourListeInterfaceTd();		// V3.0.1

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_STA_B1)
	enum { IDD = IDD_MOD_PROG_STA_B1 };
	CComboBox	c_B1_Conf;
	CStatic	c_MessageDeux;
	CStatic	c_MessageUn;
	CComboBox	m_B1_TD;
	CComboBox	m_B1_TA;
	CComboBox	m_B1_ModeAlternat;
	CComboBox	m_B1_Cix;
	CComboBox	m_B1_AleIndex;
	CComboBox	m_B1_Canal;
	CString	m_B1_Ia;
	int		m_B1_Conf;
	CString	m_B1_Mode;
	CString	m_MessageUn;
	CString	m_MessageDeux;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_STA_B1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_STA_B1)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeProgStaB1Ta();
	afx_msg void OnSelchangeProgStaB1Td();
	afx_msg void OnDropdownProgStaB1Td();
	afx_msg void OnDropdownProgStaB1Canal();
	afx_msg void OnSelchangeProgStaB1Canal();
	afx_msg void OnDropdownProgStaB1Ta();
	afx_msg void OnDropdownProgStaB1Cix();
	afx_msg void OnSelchangeProgStaB1Cix();
	afx_msg void OnDropdownProgStaB1Ch();
	afx_msg void OnSelchangeProgStaB1Ch();
	afx_msg void OnDropdownProgStaB1Ma();
	afx_msg void OnSelchangeProgStaB1Ma();
	afx_msg void OnSelchangeProgStaB1Conf();
	afx_msg void OnProgStaB1Tst();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	bool quadrivoie;
	int timerMsg;
	bool initScanSet;

	void AffichageFonctionTd();
	void AffichageFonctionMode(CString mdm);
	void AffichageFonctionTa();
	void AffichageIa(CString mdm);
	void InitialisationListeScanSet(int val);
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

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_STA_B1_H__422F33F6_AC92_4FD9_A54F_7CD0CAF10C81__INCLUDED_)
