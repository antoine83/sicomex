#if !defined(AFX_DLGMODEOPERATIONNEL_H__BA0DB5AB_A91A_42BB_ADB7_76E3B411350B__INCLUDED_)
#define AFX_DLGMODEOPERATIONNEL_H__BA0DB5AB_A91A_42BB_ADB7_76E3B411350B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgModeOperationnel.h : header file
//

/////////////////////////////////////////////////////////////////////////////
// DlgModeOperationnel dialog

class DlgModeOperationnel : public CDialog
{
// Construction
public:
	DlgModeOperationnel(CWnd* pParent = NULL);   // standard constructor

// Dialog Data
	//{{AFX_DATA(DlgModeOperationnel)
	enum { IDD = IDD_COMMUTATION_MATRIX };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgModeOperationnel)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:

	// Generated message map functions
	//{{AFX_MSG(DlgModeOperationnel)
		// NOTE: the ClassWizard will add member functions here
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGMODEOPERATIONNEL_H__BA0DB5AB_A91A_42BB_ADB7_76E3B411350B__INCLUDED_)
