#if !defined(AFX_DLGTRC1752_MOD_PROG_STA_A1_H__F4D7DAB1_08B4_4794_996F_EA347A1C4DFE__INCLUDED_)
#define AFX_DLGTRC1752_MOD_PROG_STA_A1_H__F4D7DAB1_08B4_4794_996F_EA347A1C4DFE__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

// DlgTRC1752_MOD_PROG_STA_A1.h : header file
//

#include "Equip\EquipM1752.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_PROG_STA_A1 dialog

class CDlgTRC1752_MOD_PROG_STA_A1 : public CDialog
{
// Construction
public:
	CDlgTRC1752_MOD_PROG_STA_A1(CEquipM1752 * equip = NULL, CWnd* pParent = NULL);   // standard constructor
	void Valide();
	int GetConfA1();
	int GetCanalA1();
	int GetIaA1();

	void StartTimer();
	void StopTimer();

	void MiseJourListeInterfaceTd();		// V3.0.1
	void AffichageActivation();				// V3.0.1

// Dialog Data
	//{{AFX_DATA(CDlgTRC1752_MOD_PROG_STA_A1)
	enum { IDD = IDD_MOD_PROG_STA_A1 };
	CComboBox	c_A1_Conf;
	CStatic	c_A1_Mode;
	CComboBox	m_A1_Cix;
	CComboBox	m_A1_ModeAlternat;
	CComboBox	m_A1_AleIndex;
	CComboBox	m_A1_TA;
	CComboBox	m_A1_Canal;
	CComboBox	m_A1_TD;
	CStatic	c_MessageDeux;
	CStatic	c_MessageUn;
	CString	m_A1_Ia;
	int		m_A1_Conf;
	CString	m_A1_Mode;
	CString	m_MessageUn;
	CString	m_MessageDeux;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgTRC1752_MOD_PROG_STA_A1)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipM1752 * eqp;

	// Generated message map functions
	//{{AFX_MSG(CDlgTRC1752_MOD_PROG_STA_A1)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnSelchangeProgStaA1Ta();
	afx_msg void OnSelchangeProgStaA1Td();
	afx_msg void OnDropdownProgStaA1Td();
	afx_msg void OnDropdownProgStaA1Canal();
	afx_msg void OnSelchangeProgStaA1Canal();
	afx_msg void OnDropdownProgStaA1Ta();
	afx_msg void OnDropdownProgStaA1Cix();
	afx_msg void OnSelchangeProgStaA1Cix();
	afx_msg void OnDropdownProgStaA1Ch();
	afx_msg void OnSelchangeProgStaA1Ch();
	afx_msg void OnDropdownProgStaA1Ma();
	afx_msg void OnSelchangeProgStaA1Ma();
	afx_msg void OnSelchangeProgStaA1Conf();
	afx_msg void OnSetFocus(CWnd* pOldWnd);
	afx_msg void OnProgStaA1Tst();
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

#endif // !defined(AFX_DLGTRC1752_MOD_PROG_STA_A1_H__F4D7DAB1_08B4_4794_996F_EA347A1C4DFE__INCLUDED_)
