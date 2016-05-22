#if !defined(AFX_DLGED42KEYDISPLAY_H__BC7DFFA0_AAA6_4181_94F0_5900DF5A26B1__INCLUDED_)
#define AFX_DLGED42KEYDISPLAY_H__BC7DFFA0_AAA6_4181_94F0_5900DF5A26B1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DlgED42KeyDisplay.h : header file
//

#include "Equip\EquipED42.h"
#include "myListCtrl.h"

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyDisplay dialog

class CDlgED42KeyDisplay : public CDialog
{
// Construction
public:
	CDlgED42KeyDisplay(CEquipED42 * eqp = NULL,CWnd* pParent = NULL);   // standard constructor
	~CDlgED42KeyDisplay();
	void CDlgED42KeyDisplay::LoadData();
	 
// Dialog Data
	//{{AFX_DATA(CDlgED42KeyDisplay)
	enum { IDD = IDD_ED42_KEY_TAB_DISPLAY };
	CMyListCtrl	c_listData;
	CMyListCtrl	c_listVoice;
	CString	m_kek;
	//}}AFX_DATA


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CDlgED42KeyDisplay)
	protected:
	virtual BOOL OnInitDialog();
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support	
	//}}AFX_VIRTUAL
//	void CDlgED42KeyDisplay::OnItemchangedList(NMHDR* pNMHDR, LRESULT* pResult);

// Implementation
protected:
	CEquipED42 * eqp;
	// Generated message map functions
	//{{AFX_MSG(CDlgED42KeyDisplay)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_DLGED42VARIABLES_H__DB8C0077_A039_4CAB_9C33_474C5089713D__INCLUDED_)
