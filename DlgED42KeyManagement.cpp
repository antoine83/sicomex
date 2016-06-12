// DlgED42KeyManagement.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42KeyManagement.h"
#include <time.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyManagement dialog


CDlgED42KeyManagement::CDlgED42KeyManagement(CEquipED42 * eqp,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42KeyManagement::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42KeyManagement)
	m_updateCount = _T("");
	m_presetTagged = _T("");
	//}}AFX_DATA_INIT

	this->eqp = eqp;
}

CDlgED42KeyManagement::~CDlgED42KeyManagement()
{
	DestroyWindow();
}


void CDlgED42KeyManagement::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42KeyManagement)
	DDX_Control(pDX, IDC_EDIT_PRESET_TAGGED, c_presetTagged);
	DDX_Control(pDX, IDC_COMBO_VAR_LOCATION, c_variableLocation);
	DDX_Control(pDX, IDC_COMBO_DATE_YEARS, c_years);
	DDX_Control(pDX, IDC_COMBO_DATE_MONTHS, c_months);
	DDX_Control(pDX, IDC_COMBO_DATE_DAYS, c_days);
	DDX_Control(pDX, IDC_COMBO_ACTION, c_action);
	DDX_Text(pDX, IDC_EDIT_UPDATE_COUNT, m_updateCount);
	DDX_Text(pDX, IDC_EDIT_PRESET_TAGGED, m_presetTagged);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42KeyManagement, CDialog)
	//{{AFX_MSG_MAP(CDlgED42KeyManagement)
	ON_CBN_SELCHANGE(IDC_COMBO_DATE_MONTHS, OnSelchangeComboDateMonths)
	ON_CBN_SELCHANGE(IDC_COMBO_DATE_YEARS, OnSelchangeComboDateYears)
	ON_CBN_SELCHANGE(IDC_COMBO_ACTION, OnSelchangeComboAction)
	ON_CBN_SELCHANGE(IDC_COMBO_VAR_LOCATION, OnSelchangeComboVarLocation)
	ON_CBN_SELCHANGE(IDC_COMBO_DATE_DAYS, OnSelchangeComboDateDays)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyManagement message handlers

BOOL CDlgED42KeyManagement::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	c_action.SetCurSel(0);
	c_variableLocation.SetCurSel(0);

	SetTimer(1,DUREE10S,NULL);

	LoadData();
	
	return TRUE;  
}

void CDlgED42KeyManagement::LoadData() 
{
	char buffer[4]="";
	CString tempVariableLocation = "";
	string variableLocation = "";

	buildComposant(IDC_COMBO_VAR_LOCATION);

	//Récupération de la valeur du combo box variable location
	c_variableLocation.GetLBText(c_variableLocation.GetCurSel(),tempVariableLocation);	
	variableLocation = tempVariableLocation;
	TKeyManagement keyManagement = eqp->GetKeyManagement(variableLocation);

	//Si updateCount != 255 , on affiche la date du jour.
	if(!(keyManagement.updateCount == 255 ))
	{
		c_days.SetCurSel(keyManagement.days - 1);
		c_months.SetCurSel(keyManagement.months - 1);
		c_years.SetCurSel(keyManagement.years);
	}
	else
	{
		time_t now = time(NULL);
		struct tm * my_date = localtime(&now);

		c_days.SetCurSel(my_date->tm_mday - 1);
		c_months.SetCurSel(my_date->tm_mon );
		c_years.SetCurSel((my_date->tm_year+1900)%100);
	}

	itoa(keyManagement.updateCount,buffer,10);
	m_updateCount = buffer;

	string tag = keyManagement.tag.c_str();
	for(int cpt=0;cpt<8;cpt++)
	{
		if(tag[cpt]=='-')
			tag[cpt]='_';
	}
	m_presetTagged = tag.c_str();
	UpdateData(FALSE);
}

void CDlgED42KeyManagement::SaveData() 
{
	char buffer[3] ={0};
	CString tempVariableLocation = "";
	string variableLocation = "";

	//Récupération de la valeur du combo box variable location
	c_variableLocation.GetLBText(c_variableLocation.GetCurSel(),tempVariableLocation);	
	variableLocation = tempVariableLocation;
	TKeyManagement keyManagement = eqp->GetKeyManagement(variableLocation);

	time_t now = time(NULL);
	struct tm * my_date = localtime(&now);

	switch(c_action.GetCurSel())
	{
	case 0: //Load CV

		if (eqp->GetOperatingMode() == OPE_MASTER)
		{
			if(eqp->GetUpdateLimit() == 0)
			{
				MessageBox("Update limit = 0 !","Attention",MB_ICONWARNING);
			}else{
				MessageBox("BILATERAL UPDATE OK !","Information",MB_ICONINFORMATION);
				keyManagement.updateCount	= keyManagement.updateCount+1;
				//Sauvegarde 
				eqp->SetKeyManagement(variableLocation,keyManagement);
				//Set du flag : Key List
				eqp->SetKeyList(1);
			}
			break;
		}

		if (eqp->GetOperatingStatus() == ONLINE)
		{
			MessageBox("Impossible de charger un CV si on est ONLINE.","Attention",MB_ICONWARNING);
			break;
		}

		if (eqp->GetKeStatus() == CIK_NOT_PLUGED)
		{
			MessageBox("Impossible de charger un CV si on est pas en CIK_MODE.","Attention",MB_ICONWARNING);
			break;
		}

		keyManagement.days			= c_days.GetCurSel()+1;
		keyManagement.months		= c_months.GetCurSel()+1;
		keyManagement.years			= c_years.GetCurSel();
		keyManagement.hours			= my_date->tm_hour;
		keyManagement.minutes		= 10 * (my_date->tm_min/10); //Résolution par pas de 10
		keyManagement.updateCount	= 0;

		//Sauvegarde 
		eqp->SetKeyManagement(variableLocation,keyManagement);

		//param 30 Flag : Key memory.
		eqp->SetKeyMemory(1);

		break;
	case 1: //Update CV
		// Uniquement si "The password lock time has not expired"
		if (eqp->getED42Lock())
		{
			MessageBox("Impossible de réaliser un UPDATE si on est LOCK.","Attention",MB_ICONWARNING);
			break;
		}

		if(eqp->GetUpdateLimit() == 0)
		{
			MessageBox("Update limit = 0 !","Attention",MB_ICONWARNING);
		}
		else{
		//Vérification updateCount ne doit pas être supérieur à updateLimit
		if(eqp->GetUpdateLimit() > keyManagement.updateCount)
		{
			keyManagement.days			= my_date->tm_mday;
			keyManagement.months		= my_date->tm_mon+1;
			keyManagement.years			= (my_date->tm_year+1900)%100;//(00 .. 99)
			keyManagement.hours			= my_date->tm_hour;
			keyManagement.minutes		= 10 * (my_date->tm_min/10); //Résolution par pas de 10
			keyManagement.updateCount	= keyManagement.updateCount+1;

			//Sauvegarde 
			eqp->SetKeyManagement(variableLocation,keyManagement);
		}
		else
			MessageBox("Limite de mise à jour atteinte","Attention",MB_ICONWARNING);
		}
		break;
	case 2: //Delete CV
		// Uniquement en "OFFLINE"
		if (eqp->GetOperatingStatus() == ONLINE)
		{
			MessageBox("Impossible de supprimer un CV si on est ONLINE.","Attention",MB_ICONWARNING);
			break;
		}
		// Uniquement si "The password lock time has not expired"
		if (eqp->getED42Lock())
		{
			MessageBox("Impossible de supprimer un CV si on est LOCK.","Attention",MB_ICONWARNING);
			break;
		}

		if (eqp->GetKeStatus() == CIK_NOT_PLUGED)
		{
			MessageBox("Impossible de supprimer un CV si on est pas en CIK_MODE.","Attention",MB_ICONWARNING);
			break;
		}


		//Si aucun preset est taggé alors on peut supprimer.
		if(keyManagement.tag.compare("--------") == 0)
		{
			keyManagement.days			= 00;
			keyManagement.months		= 00;
			keyManagement.years			= 00;
			keyManagement.hours			= 00;
			keyManagement.minutes		= 00;
			keyManagement.updateCount	= 255;

			//Sauvegarde 
			eqp->SetKeyManagement(variableLocation,keyManagement);

			//Quand on supprime un CV, on positionne le combo Action à LOAD CV
			//car la variable location n'existe plus
			c_action.SetCurSel(0);
		}
		else
		{
			MessageBox("Impossible de supprimer un CV tagged.","Attention",MB_ICONWARNING);
		}
		break;
	case 3: //Delete All CV

		// Uniquement en "OFFLINE"
		if (eqp->GetOperatingStatus() == ONLINE)
		{
			MessageBox("Impossible de supprimer les CV si on est ONLINE.","Attention",MB_ICONWARNING);
			c_action.SetCurSel(0);
			break;
		}
		// Uniquement si "The password lock time has not expired"
		if (eqp->getED42Lock())
		{
			MessageBox("Impossible de supprimer les CV si on est LOCK.","Attention",MB_ICONWARNING);
			c_action.SetCurSel(0);
			break;
		}

		if (eqp->GetKeStatus() == CIK_NOT_PLUGED)
		{
			MessageBox("Impossible de supprimer les CV si on est pas en CIK_MODE.","Attention",MB_ICONWARNING);
			c_action.SetCurSel(0);
			break;
		}
		eqp->RazTableCle();

		//Quand on supprime un CV, on positionne le combo Action à LOAD CV
		//car la variable location n'existe plus
		c_action.SetCurSel(0);
		break;
	}
	
	//Apres avoir sauvegarder il faut remettre à jour la vue
	LoadData();

	//Set du flag : Key List
	eqp->SetKeyList(1);
}

void CDlgED42KeyManagement::OnSelchangeComboDateMonths() 
{
	buildComposant(IDC_COMBO_DATE_DAYS);
	eqp->setModifVue(TRUE);
}

void CDlgED42KeyManagement::OnSelchangeComboDateYears() 
{
	buildComposant(IDC_COMBO_DATE_DAYS);
	eqp->setModifVue(TRUE);
}

void CDlgED42KeyManagement::buildComposant(int composant)
{
	int cpt = 0,nbreJour = 0,saveDay = 0,result =0;;
	char buffer[4]="";
	CString tempVariableLocation = "";
	TKeyManagement keyManagement;

	switch(composant)
	{
	//Construction du combo du jour
	case IDC_COMBO_DATE_DAYS:
		nbreJour =0;
		saveDay = c_days.GetCurSel()+1;
		if(c_months.GetCurSel() <=6)
		{
			if(c_months.GetCurSel()%2 == 0)
				nbreJour = 31;
			else
				nbreJour = 30;
		}
		else
		{
			if(c_months.GetCurSel()%2 == 1)
				nbreJour = 30;
			else
				nbreJour = 31;
		}

		if(c_months.GetCurSel() ==1)
		{
			if((c_years.GetCurSel() % 4 == 0 && c_years.GetCurSel() % 100 !=0) 
				|| c_years.GetCurSel() % 400 == 0)
				nbreJour = 29;
			else
				nbreJour = 28;
		}

		//Construction du combo box
		c_days.ResetContent();
		for(cpt=1;cpt<=nbreJour;cpt++)
		{
			itoa(cpt,buffer,10);
			c_days.AddString(buffer);
		}
	
		//Sélection de la valeur dans e combo
		if(saveDay<=nbreJour)
			c_days.SetCurSel(saveDay - 1);
		else
			c_days.SetCurSel(0);
		break;

	//Construction du combo Variable Location
	case IDC_COMBO_VAR_LOCATION:

		//Récupération de l'ancienne sélection
		c_variableLocation.GetLBText(c_variableLocation.GetCurSel(),tempVariableLocation);		
		
		//On construit le combo en fonction du combo action
		switch(c_action.GetCurSel())
		{
		case 0: //LOAD CV
			c_variableLocation.EnableWindow(TRUE);

			//On vérifie si le combo est déjà remplie avec toutes les valeurs
			if(c_variableLocation.GetCount()!=96)
			{
				//Construction du combo box
				c_variableLocation.ResetContent();
				
				for(cpt =1;cpt<97;cpt++)
				{
					itoa(cpt,buffer,10);
					c_variableLocation.AddString(buffer);
				}
			}
			break;
		case 1: //UPDATE CV
		case 2: //DELETE CV	
			//Construction du combo box
			c_variableLocation.ResetContent();

			c_variableLocation.EnableWindow(TRUE);
			for(cpt =1;cpt<97;cpt++)
			{
				itoa(cpt,buffer,10);
				keyManagement = eqp->GetKeyManagement(buffer);
				//Si updateCount = 255 alors on a effectué l'opération LOAD CV.
				if(!(keyManagement.updateCount == 255 ))
				{
					itoa(cpt,buffer,10);
					c_variableLocation.AddString(buffer);
				}
			}
			//Vérifie si le combo est vide
			if(c_variableLocation.GetCount()==0)
			{
				c_variableLocation.AddString("--");
			}
			break;
		case 3: //DELETE ALL CV
			c_variableLocation.EnableWindow(FALSE);
			break;
		}
		result = c_variableLocation.SelectString(-1,tempVariableLocation);
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			c_variableLocation.SetCurSel(0);//Premier élément par défaut
		
		break;
	}
}


void CDlgED42KeyManagement::OnSelchangeComboAction() 
{
	eqp->setModifVue(TRUE);
	buildComposant(IDC_COMBO_VAR_LOCATION);
}

void CDlgED42KeyManagement::OnSelchangeComboVarLocation() 
{
	eqp->setModifVue(TRUE);
	LoadData();
}

void CDlgED42KeyManagement::OnSelchangeComboDateDays() 
{
	eqp->setModifVue(TRUE);
}

void CDlgED42KeyManagement::OnTimer(UINT nIDEvent) 
{
	
	CDialog::OnTimer(nIDEvent);

	if (eqp->getED42Lock() && eqp->GetOperatingStatus() == OFFLINE)
	{
		if (c_action.GetCount() == 4)
		{
			c_action.ResetContent();
			c_action.AddString("LOAD CV");
			c_action.SetCurSel(0);
		}	
	}

	if (!eqp->getED42Lock() && eqp->GetOperatingStatus() == OFFLINE)
	{
		if (c_action.GetCount() == 1)
		{
			c_action.ResetContent();
			c_action.AddString("LOAD CV");
			c_action.AddString("UPDATE CV");
			c_action.AddString("DELETE CV");
			c_action.AddString("DELETE ALL CV");
			c_action.SetCurSel(0);
		}	
	}

	//if (!eqp->getED42Lock() && eqp->GetOperatingStatus() == OFFLINE)
	if (eqp->GetOperatingStatus() == ONLINE && (eqp->GetTransmissionMode() == DIGITAL || 
					 eqp->GetOperatingMode() == DATA_CRYPRO ) &&
					( (eqp->GetTransmissionProcedure() == V24 && 
					  (eqp->GetTraficMode() == DX || 
					   eqp->GetTraficMode() == DXD)) ||
					 eqp->GetTransmissionProcedure() == V25BIS ||
					 eqp->GetTransmissionProcedure() == X21) &&
					 eqp->GetOperatingMode() == OPE_MASTER)
	{
		if (c_action.GetCount() == 4)
		{
			c_action.ResetContent();
			//c_action.AddString("LOAD CV");
			c_action.AddString("BILATERAL UPDATE");
			//c_action.AddString("DELETE CV");
			//c_action.AddString("DELETE ALL CV");
			c_action.SetCurSel(0);
		}	
	}

}
