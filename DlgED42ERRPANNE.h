#if !defined(AFX_DLGED42ERRPANNE_H__4B3265F5_F5D1_49A2_B770_4CC1AC4CC73B__INCLUDED_)
#define AFX_DLGED42ERRPANNE_H__4B3265F5_F5D1_49A2_B770_4CC1AC4CC73B__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42ERRPANNE.h : header file
//

#include "XTabCtrl.h"

#include "DlgED42ERR.h"
#include "DlgED42Pannes.h"
#include "DlgED42Bit.h"
#include "DlgED42StatusERR.h"

/////////////////////////////////////////////////////////////////////////////
// DlgED42ERRPANNE dialog

class DlgED42ERRPANNE : public CDialog
{
// Construction
public:
	DlgED42ERRPANNE(CEquipED42* equip = NULL, CWnd* pParent = NULL);   // standard constructor
	~DlgED42ERRPANNE();	

	void DlgED42ERRPANNE::LoadData();

// Dialog Data
	//{{AFX_DATA(DlgED42ERRPANNE)
	enum { IDD = F12_IDD_ED42_ERR_PANNE };
	CXTabCtrl	m_ErrPanneTab;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(DlgED42ERRPANNE)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	CEquipED42* equip;
	DlgED42ERR* m_Err;
	DlgED42Pannes* m_Pannes;
	DlgED42Bit* m_Bit;
	CDlgED42StatusERR* m_statusErr;
	// Generated message map functions
	//{{AFX_MSG(DlgED42ERRPANNE)
	afx_msg void OnSelchangeEd42TabErrPanne(NMHDR* pNMHDR, LRESULT* pResult);
	afx_msg void OnButtonFermer();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
	int ongletSelection;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42ERRPANNE_H__4B3265F5_F5D1_49A2_B770_4CC1AC4CC73B__INCLUDED_)
