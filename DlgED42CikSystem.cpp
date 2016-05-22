// DlgED42CikSystem.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42CikSystem.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42CikSystem dialog


CDlgED42CikSystem::CDlgED42CikSystem(CEquipED42 * equip,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42CikSystem::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42CikSystem)
	m_initializeVerif = _T("");
	//}}AFX_DATA_INIT
	this->eqp = equip;
}

CDlgED42CikSystem::~CDlgED42CikSystem()
{
	DestroyWindow();
}



void CDlgED42CikSystem::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42CikSystem)
	DDX_Control(pDX, IDC_COMBO_DELETE_CIK, c_deleteCIKCombo);
	DDX_Control(pDX, IDC_BUTTON_INITIALIZE_CIK, c_initializeCIKButton);
	DDX_Control(pDX, IDC_COMBO_INITIALIZE_CIK, c_initializeCIK);
	DDX_Control(pDX, IDC_BUTTON_DELETE_CIK_SYSTEM, c_deleteCIKSystem);
	DDX_Control(pDX, IDC_BUTTON_DELETE_CIK, c_deleteCIK);
	DDX_Text(pDX, IDC_EDIT_INITIALIZE_VERIF, m_initializeVerif);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42CikSystem, CDialog)
	//{{AFX_MSG_MAP(CDlgED42CikSystem)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_CIK, OnButtonDeleteCik)
	ON_BN_CLICKED(IDC_BUTTON_DELETE_CIK_SYSTEM, OnButtonDeleteCikSystem)
	ON_BN_CLICKED(IDC_BUTTON_INITIALIZE_CIK, OnButtonInitializeCik)
	ON_CBN_SELCHANGE(IDC_COMBO_INITIALIZE_CIK, OnSelchangeComboInitializeCik)
	ON_BN_CLICKED(IDC_BUTTON_KEK, OnButtonKek)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42CikSystem message handlers

BOOL CDlgED42CikSystem::OnInitDialog() 
{
	CDialog::OnInitDialog();	
	
	return TRUE;  
}

void CDlgED42CikSystem::LoadData() 
{
	m_initializeVerif = "";
	EnableComponent();

	// Mise à jour CIK_STATE
	if (eqp->GetUserCik() == NO_CIK_USER)
		eqp->ChangeCik(WAITING_CIK_STATE,FALSE);
	else
		eqp->ChangeCik(VALID_CIK_STATE,FALSE);

}

void CDlgED42CikSystem::OnButtonDeleteCik() 
{
	CString tempVariableLocation = "";

	//Récupération de l'ancienne sélection
	c_deleteCIKCombo.GetLBText(c_deleteCIKCombo.GetCurSel(),tempVariableLocation);
	if(tempVariableLocation.Compare(CIK_USER[CIK_USER_1].c_str()) == 0)
	{
		if(eqp->GetUserCik() == CIK_USER_1_ET_2)
			eqp->SetUserCik(CIK_USER_2);
		else
			eqp->SetUserCik(NO_CIK_USER);
	}
	else if(tempVariableLocation.Compare(CIK_USER[CIK_USER_2].c_str()) == 0)
	{
		if(eqp->GetUserCik() == CIK_USER_1_ET_2)
			eqp->SetUserCik(CIK_USER_1);
		else
			eqp->SetUserCik(NO_CIK_USER);
	}

	LoadData();
}

void CDlgED42CikSystem::OnButtonDeleteCikSystem() 
{
	char buffer[3] = {0};
	
	//eqp->setSecureMode(NOT_DEFINED);	// TODO
	eqp->SetUserCik(NO_CIK_USER);
	eqp->SetKeStatus(NO_CIK_SET_UP);
	
	//Set du flag : Key List
	eqp->SetKeyList(1);

	LoadData();
}

void CDlgED42CikSystem::OnButtonInitializeCik() 
{
	CString tempVariableLocation = "";

	//Récupération de l'ancienne sélection
	c_initializeCIK.GetLBText(c_initializeCIK.GetCurSel(),tempVariableLocation);
	if(tempVariableLocation.Compare(CIK_USER[NO_CIK_USER].c_str()) == 0)
	{
		eqp->SetUserCik(c_initializeCIK.GetCurSel());
	}
	else if(tempVariableLocation.Compare(CIK_USER[CIK_USER_1].c_str()) == 0)
	{
		if(eqp->GetUserCik() == CIK_USER_2)
			eqp->SetUserCik(CIK_USER_1_ET_2);
		else
			eqp->SetUserCik(CIK_USER_1);
	}
	else if(tempVariableLocation.Compare(CIK_USER[CIK_USER_2].c_str()) == 0)
	{
		if(eqp->GetUserCik() == CIK_USER_1)
			eqp->SetUserCik(CIK_USER_1_ET_2);
		else
			eqp->SetUserCik(CIK_USER_2);
	}

	m_initializeVerif = "SUCCESSFUL";
	EnableComponent();

	// Mise à jour CIK_STATE
	if (eqp->GetUserCik() == NO_CIK_USER)
		eqp->ChangeCik(WAITING_CIK_STATE,FALSE);
	else
	{
		eqp->ChangeCik(VALID_CIK_STATE,FALSE);
		eqp->SetKeyMemory(1);
	}
}

void CDlgED42CikSystem::EnableComponent()
{
	CString tempVariableLocation = "";
	
	//Pour le combo Initialisation
	c_initializeCIK.ResetContent();

	//Pour le combo Delete
	c_deleteCIKCombo.ResetContent();
		
	switch(eqp->GetUserCik())
	{
		case NO_CIK_USER:
			c_initializeCIK.AddString(CIK_USER[NO_CIK_USER].c_str());
			c_initializeCIK.AddString(CIK_USER[CIK_USER_1].c_str());
			c_initializeCIK.SetCurSel(0);

			c_deleteCIKCombo.AddString(CIK_USER[NO_CIK_USER].c_str());
			c_deleteCIKCombo.SetCurSel(0);
			break;
		case CIK_USER_1:
			c_initializeCIK.AddString(CIK_USER[CIK_USER_2].c_str());
			c_initializeCIK.SetCurSel(0);

			c_deleteCIKCombo.AddString(CIK_USER[CIK_USER_1].c_str());
			c_deleteCIKCombo.SetCurSel(0);
			break;
		case CIK_USER_2:
			c_initializeCIK.AddString(CIK_USER[CIK_USER_1].c_str());
			c_initializeCIK.SetCurSel(0);

			c_deleteCIKCombo.AddString(CIK_USER[CIK_USER_2].c_str());
			c_deleteCIKCombo.SetCurSel(0);
			break;
		case CIK_USER_1_ET_2:
			c_initializeCIK.AddString(CIK_USER[CIK_USER_1_ET_2].c_str());
			c_initializeCIK.SetCurSel(0);

			c_deleteCIKCombo.AddString(CIK_USER[CIK_USER_1].c_str());
			c_deleteCIKCombo.AddString(CIK_USER[CIK_USER_2].c_str());
			c_deleteCIKCombo.SetCurSel(0);
			break;
	}	

	//Récupération de l'ancienne sélection
	c_initializeCIK.GetLBText(c_initializeCIK.GetCurSel(),tempVariableLocation);

	c_initializeCIKButton.EnableWindow((!eqp->getED42Lock())
										&& (tempVariableLocation.Compare(CIK_USER[NO_CIK_USER].c_str()) != 0) 
										&& (eqp->GetUserCik() != CIK_USER_1_ET_2) 
										&& (eqp->getSecureMode() == CIK_MODE));

	c_initializeCIK.EnableWindow((!eqp->getED42Lock()) 
								  && (eqp->GetUserCik() != CIK_USER_1_ET_2) 
								  && (eqp->getSecureMode() == CIK_MODE));

	c_deleteCIK.EnableWindow((!eqp->getED42Lock()) 
							  && (eqp->GetUserCik() != NO_CIK_USER) 
							  && (eqp->getSecureMode() == CIK_MODE));

	c_deleteCIKCombo.EnableWindow((!eqp->getED42Lock()) 
								   && (eqp->GetUserCik() != NO_CIK_USER) 
								   && (eqp->getSecureMode() == CIK_MODE));

	c_deleteCIKSystem.EnableWindow((!eqp->getED42Lock()) 
									&& (eqp->GetUserCik() != NO_CIK_USER) 
									&& (eqp->getSecureMode() == CIK_MODE));

	UpdateData(FALSE);
}

void CDlgED42CikSystem::OnSelchangeComboInitializeCik() 
{
	CString tempVariableLocation = "";

	//Récupération de l'ancienne sélection
	c_initializeCIK.GetLBText(c_initializeCIK.GetCurSel(),tempVariableLocation);

	c_initializeCIKButton.EnableWindow((tempVariableLocation.Compare(CIK_USER[NO_CIK_USER].c_str()) != 0) && (eqp->getSecureMode() == CIK_MODE));
	m_initializeVerif = "";

	UpdateData(FALSE);
}

void CDlgED42CikSystem::OnButtonKek() 
{
	
	time_t now = time(NULL);
	struct tm * my_date = localtime(&now);

	TKeyManagement keyManagement;

	keyManagement = eqp->GetKeyManagement("0");

	keyManagement.kekLoaded			= 0;
	keyManagement.variableLocation	= 0;
	keyManagement.days				= my_date->tm_mday;
	keyManagement.months			= my_date->tm_mon;
	keyManagement.years				= (my_date->tm_year+1900)%100;
	keyManagement.hours				= my_date->tm_hour;
	keyManagement.minutes			= 10 * (my_date->tm_min/10);
	keyManagement.updateCount		= 0;				//0; 255 : pas de clé - page 173
	keyManagement.tag			= "--------";




	eqp->SetKeyManagement("0",keyManagement);

	char buffer[3] ={0};
	int i = 1;

	for(i;i<97;i++)
		{
			itoa(i,buffer,10);
			keyManagement = eqp->GetKeyManagement(buffer);
			keyManagement.kekLoaded	= 0;
	
			//Sauvegarde 
			eqp->SetKeyManagement(buffer,keyManagement);
		}

		// Param 30 Flag key memory
		eqp->SetKeyMemory(0);
	
}
