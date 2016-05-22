// DlgED42Password.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42Password.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42Password dialog


CDlgED42Password::CDlgED42Password(CEquipED42 * equip,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42Password::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42Password)
	m_checkVerif = _T("");
	m_holdTime = 0;
	m_updateLimit = 0;
	//}}AFX_DATA_INIT
	this->eqp = equip;
}

CDlgED42Password::~CDlgED42Password()
{
	DestroyWindow();
}



void CDlgED42Password::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42Password)
	DDX_Control(pDX, IDC_EDIT_UPDATE_LIMIT, c_updateLimit);
	DDX_Control(pDX, IDC_EDIT_HOLD_TIME, c_holdTime);
	DDX_Control(pDX, IDC_EDIT_CHANGE_CONFIRM_PASS, c_changeConfirmPassword);
	DDX_Control(pDX, IDC_EDIT_CHECK_PASSWORD, c_checkPassword);
	DDX_Control(pDX, IDC_EDIT_CHANGE_OLD_PASS, c_changeOldPassword);
	DDX_Control(pDX, IDC_EDIT_CHANGE_NEW_PASS, c_changeNewPassword);
	DDX_Control(pDX, IDC_SPIN_UPDATE_LIMIT, s_updateLimit);
	DDX_Control(pDX, IDC_SPIN_HOLD_TIME, s_holdTime);
	DDX_Control(pDX, IDC_BUTTON_CHECK, c_check);
	DDX_Control(pDX, IDC_BUTTON_CHANGE_PASSWORD, c_changePassword);
	DDX_Text(pDX, IDC_EDIT_CHECK_VERIF, m_checkVerif);
	DDX_Text(pDX, IDC_EDIT_HOLD_TIME, m_holdTime);
	DDX_Text(pDX, IDC_EDIT_UPDATE_LIMIT, m_updateLimit);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42Password, CDialog)
	//{{AFX_MSG_MAP(CDlgED42Password)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_HOLD_TIME, OnDeltaposSpinHoldTime)
	ON_NOTIFY(UDN_DELTAPOS, IDC_SPIN_UPDATE_LIMIT, OnDeltaposSpinUpdateLimit)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE_PASSWORD, OnButtonChangePassword)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, OnButtonCheck)
	ON_EN_CHANGE(IDC_EDIT_HOLD_TIME, OnChangeEditHoldTime)
	ON_EN_CHANGE(IDC_EDIT_UPDATE_LIMIT, OnChangeEditUpdateLimit)
	ON_EN_CHANGE(IDC_EDIT_CHANGE_OLD_PASS, OnChangeEditChangeOldPass)
	ON_EN_CHANGE(IDC_EDIT_CHANGE_NEW_PASS, OnChangeEditChangeNewPass)
	ON_EN_CHANGE(IDC_EDIT_CHANGE_CONFIRM_PASS, OnChangeEditChangeConfirmPass)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42Password message handlers

BOOL CDlgED42Password::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	c_checkPassword.LimitText(8);
	c_changeOldPassword.LimitText(8);
	c_changeNewPassword.LimitText(8);
	c_changeConfirmPassword.LimitText(8);
	c_holdTime.LimitText(2);
	c_updateLimit.LimitText(2);	

	return TRUE;  
}

void CDlgED42Password::LoadData() 
{
	m_holdTime = eqp->GetPasswordHoldTime();
	m_updateLimit = eqp->GetUpdateLimit();

	c_checkPassword.SetWindowText("");
	m_checkVerif = "";
	c_changeOldPassword.SetWindowText("");
	c_changeNewPassword.SetWindowText("");
	c_changeConfirmPassword.SetWindowText("");

	c_changeNewPassword.EnableWindow(FALSE);
	c_changeConfirmPassword.EnableWindow(FALSE);
	c_changePassword.EnableWindow(FALSE);

	UpdateData(FALSE);
}

void CDlgED42Password::SaveData() 
{
	eqp->SetPasswordHoldTime(m_holdTime);
	eqp->SetUpdateLimit(m_updateLimit);

	if (eqp->GetPasswordHoldTime() == 0)
		eqp->setED42Lock(FALSE);
}

void CDlgED42Password::OnDeltaposSpinHoldTime(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;

	if (pNMUpDown->iDelta > 0)  m_holdTime -= 1;
		else       m_holdTime += 1;

	if ( m_holdTime > HOLD_TIME_MAX )
	{
		AfxMessageBox("Le password hold time peut prendre les valeurs : 0 à 60 minutes");
		m_holdTime = HOLD_TIME_MAX;
	}

	if ( m_holdTime < HOLD_TIME_MIN)
	{
		AfxMessageBox("Le password hold time peut prendre les valeurs : 0 à 60 minutes");
		m_holdTime = HOLD_TIME_MIN;
	}			

	if (oldHoldTime != m_holdTime)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);
	
	*pResult = 0;
}

void CDlgED42Password::OnDeltaposSpinUpdateLimit(NMHDR* pNMHDR, LRESULT* pResult) 
{
	NM_UPDOWN* pNMUpDown = (NM_UPDOWN*)pNMHDR;
	
	if (pNMUpDown->iDelta > 0)  m_updateLimit -= 1;
		else       m_updateLimit += 1;

	if ( m_updateLimit > UPDATE_LIMIT_MAX )
	{
		AfxMessageBox("Le update limit peut prendre les valeurs : 1 à 99");
		m_updateLimit = UPDATE_LIMIT_MAX;
	}

	if ( m_updateLimit < UPDATE_LIMIT_MIN)
	{
		AfxMessageBox("Le update limit peut prendre les valeurs : 1 à 99");
		m_updateLimit = UPDATE_LIMIT_MIN;
	}			

	if (oldUpdateLimit != m_updateLimit)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);
	
	*pResult = 0;
}

void CDlgED42Password::OnButtonChangePassword() 
{
	// Uniquement si "The password lock time has not expired"
	if (eqp->getED42Lock())
	{
		MessageBox("Impossible de réaliser un CHANGE USER PWD si on est LOCK.","Attention",MB_ICONWARNING);
		return;
	}

	CString str;

	c_changeOldPassword.GetWindowText(str);
	string oldPassword = str;

	c_changeNewPassword.GetWindowText(str);
	string newPassword = str;

	c_changeConfirmPassword.GetWindowText(str);
	string confirmPassword = str;

	string password = eqp->GetUserPassWord();

	if(password.compare(oldPassword) != 0)
		AfxMessageBox("L'ancien password est incorrecte");

	else if(newPassword.compare(confirmPassword) != 0)
		AfxMessageBox("Saisie incorrecte entre le nouveau password et la confirmation");
	else
		eqp->SetUserPassWord(newPassword);

	LoadData();
}

void CDlgED42Password::OnButtonCheck() 
{
	// Uniquement si "The password lock time has not expired"
	if (eqp->getED42Lock())
	{
		MessageBox("Impossible de réaliser un UPDATE si on est LOCK.","Attention",MB_ICONWARNING);
		return;
	}

	CString str;

	c_checkPassword.GetWindowText(str);
	string checkPassword = str;

	string password = eqp->GetUserPassWord();

	if(password.compare(checkPassword) == 0)
		m_checkVerif = "CHECKED";
	else
		m_checkVerif = "UNCHECKED";
	
	c_checkPassword.SetWindowText("");

	UpdateData(FALSE);
}

void CDlgED42Password::OnChangeEditHoldTime() 
{
	CString str;

	c_holdTime.GetWindowText(str);

	m_holdTime = atoi((char*)LPCTSTR(str));

	if ( m_holdTime > HOLD_TIME_MAX )
	{
		AfxMessageBox("Le password hold time peut prendre les valeurs : 0 à 60 minutes");
		m_holdTime = HOLD_TIME_MAX;
	}

	if ( m_holdTime < HOLD_TIME_MIN)
	{
		AfxMessageBox("Le password hold time peut prendre les valeurs : 0 à 60 minutes");
		m_holdTime = HOLD_TIME_MIN;
	}			

	if (oldHoldTime != m_holdTime)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);	
}

void CDlgED42Password::OnChangeEditUpdateLimit() 
{
	CString str;

	c_updateLimit.GetWindowText(str);

	m_updateLimit = atoi((char*)LPCTSTR(str));

	if ( m_updateLimit > UPDATE_LIMIT_MAX )
	{
		AfxMessageBox("Le update limit peut prendre les valeurs : 1 à 99");
		m_updateLimit = UPDATE_LIMIT_MAX;
	}

	if ( m_updateLimit < UPDATE_LIMIT_MIN)
	{
		AfxMessageBox("Le update limit peut prendre les valeurs : 1 à 99");
		m_updateLimit = UPDATE_LIMIT_MIN;
	}			

	if (oldUpdateLimit != m_updateLimit)
		eqp->setModifVue(TRUE);

	UpdateData(FALSE);	
}

void CDlgED42Password::OnChangeEditChangeOldPass() 
{
	CString str;
	c_changeOldPassword.GetWindowText(str);
	
	if(str.IsEmpty() || str.GetLength() < 5)
	{
		c_changeNewPassword.SetWindowText("");
		c_changeNewPassword.EnableWindow(FALSE);
		c_changeConfirmPassword.SetWindowText("");
		c_changeConfirmPassword.EnableWindow(FALSE);
		c_changePassword.EnableWindow(FALSE);
	}
	else
		c_changeNewPassword.EnableWindow(TRUE);
}

void CDlgED42Password::OnChangeEditChangeNewPass() 
{
	CString str;
	c_changeNewPassword.GetWindowText(str);
	
	if(str.IsEmpty() || str.GetLength() < 5)
	{
		c_changeConfirmPassword.SetWindowText("");
		c_changeConfirmPassword.EnableWindow(FALSE);
		c_changePassword.EnableWindow(FALSE);
	}
	else
		c_changeConfirmPassword.EnableWindow(TRUE);
}

void CDlgED42Password::OnChangeEditChangeConfirmPass() 
{
	CString str;
	c_changeConfirmPassword.GetWindowText(str);
	
	if(str.IsEmpty() || str.GetLength() < 5)
		c_changePassword.EnableWindow(FALSE);
	else
		c_changePassword.EnableWindow(TRUE);
}
