#if !defined(AFX_DLGCV24CARD_H__2721CC13_7CC4_4EC0_B7BC_F9316D49861D__INCLUDED_)
#define AFX_DLGCV24CARD_H__2721CC13_7CC4_4EC0_B7BC_F9316D49861D__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DLGCV24Card.h : header file
//

#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

#include "afxcmn.h"

/////////////////////////////////////////////////////////////////////////////
// CDLGCV24Card dialog

class CDLGCV24Card : public CDlgEquip
{
// Construction
public:
	CDLGCV24Card(CWnd* pParent = NULL);   // standard constructor

	void onStatusChange() ;
	void onInputValueChange(int id);
	void onInputMaskValueChange(int id);
	void onOutputValueChange(int id);
	void onKeyChange(int value);
	void refresh();

// Dialog Data
	//{{AFX_DATA(CDLGCV24Card)
	enum { IDD = IDD_CV24_CARD };

	CListBox	m_liste_message;
	CButton		m_synchro;
	CButton		m_cycle;
	CString		m_err_retard;
	CString		m_periode;
	CString		m_tempo;
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDLGCV24Card)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CInter		m_activite;
	CInter		m_status;
	CDiode		m_inputLed[4];
	CInter		m_inputStatus[4];
	CInter		m_outputStatus[8];
	CEdit		m_keyNumber;

	void OnEnvoiTrame();
	// Generated message map functions
	//{{AFX_MSG(CDLGCV24Card)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnAide();
	afx_msg void OnInput0Clicked();
	afx_msg void OnInput1Clicked();
	afx_msg void OnInput2Clicked();
	afx_msg void OnInput15Clicked();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	void OnComErreur() ;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGCV24CARD_H__2721CC13_7CC4_4EC0_B7BC_F9316D49861D__INCLUDED_)
