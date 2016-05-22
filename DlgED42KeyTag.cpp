// DlgED42KeyTag.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42KeyTag.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyTag dialog


CDlgED42KeyTag::CDlgED42KeyTag(CEquipED42 * eqp,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42KeyTag::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42KeyTag)
	m_date = _T("");
	m_presetTagged = _T("");
	m_updateCount = _T("");
	//}}AFX_DATA_INIT
	this->eqp = eqp;
}


void CDlgED42KeyTag::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42KeyTag)
	DDX_Control(pDX, IDC_COMBO_PRESET_LOCATION, c_presetLocation);
	DDX_Control(pDX, IDC_COMBO_VAR_LOCATION, c_variableLocation);
	DDX_Control(pDX, IDC_COMBO_PRESET_TYPE, c_presetType);
	DDX_Text(pDX, IDC_EDIT_DATE, m_date);
	DDX_Text(pDX, IDC_EDIT_PRESET_TAG, m_presetTagged);
	DDX_Text(pDX, IDC_EDIT_UPDATE_COUNT, m_updateCount);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42KeyTag, CDialog)
	//{{AFX_MSG_MAP(CDlgED42KeyTag)
	ON_CBN_SELCHANGE(IDC_COMBO_PRESET_TYPE, OnSelchangeComboPresetType)
	ON_CBN_SELCHANGE(IDC_COMBO_VAR_LOCATION, OnSelchangeComboVarLocation)
	ON_CBN_SELCHANGE(IDC_COMBO_PRESET_LOCATION, OnSelchangeComboPresetLocation)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyTag message handlers

BOOL CDlgED42KeyTag::OnInitDialog() 
{
	CDialog::OnInitDialog();

	c_presetType.SetCurSel(0);
	c_presetLocation.SetCurSel(0);
	c_variableLocation.SetCurSel(0);
	
	LoadData();
	
	return TRUE;  
}

void CDlgED42KeyTag::LoadData() 
{
	char buffer[3] = "";
	CString tempVariableLocation = "";
	string variableLocation = "";

	buildComposant(IDC_COMBO_VAR_LOCATION);

	//Récupération de la valeur du combo box variable location
	c_variableLocation.GetLBText(c_variableLocation.GetCurSel(),tempVariableLocation);	
	variableLocation = tempVariableLocation;
	//Si aucune variable n'a été chargé pas LOAD CV, on met des valeurs par défaut.
	if(variableLocation.compare("--") != 0)
	{
		TKeyManagement keyManagement = eqp->GetKeyManagement(variableLocation);

		string date = "";
		itoa(keyManagement.days ,buffer,10);
		date.append(buffer);
		date.append(" / ");
		itoa(keyManagement.months ,buffer,10);
		date.append(buffer);
		date.append(" / ");
		itoa(keyManagement.years ,buffer,10);
		date.append(buffer);
		m_date = date.c_str();

		itoa(keyManagement.updateCount,buffer,10);
		m_updateCount = buffer;

		string tag = keyManagement.tag.c_str();
		for(int cpt=0;cpt<8;cpt++)
		{
			if(tag[cpt]=='-')
				tag[cpt]='_';
		}
		m_presetTagged = tag.c_str();		
	}
	//Valeur par défaut
	else 
	{
		m_date = "1/1/70";
		m_updateCount = "0";
		m_presetTagged = "________";
	}
	UpdateData(FALSE);
}

void CDlgED42KeyTag::SaveData() 
{
	// Uniquement si "The password lock time has not expired"
	if (eqp->getED42Lock())
	{
		MessageBox("Impossible de réaliser un TAG si on est LOCK.","Attention",MB_ICONWARNING);
		return;
	}

	CString tempVariableLocation = "";
	string variableLocation = "";
	//char buffer[3] = {0};
	TKeyManagement keyManagement;		

	//Preset sélectionné
	int preset = c_presetLocation.GetCurSel();
	//Vérification si il y a une variable location présente
	c_variableLocation.GetLBText(c_variableLocation.GetCurSel(),tempVariableLocation);	
	variableLocation = tempVariableLocation;
	if(variableLocation.compare("--") == 0)
		return;

	//Mise à jour, il faut retirer le nouveau preset dans les autres variables locations.
	for(int cpt=0;cpt<c_variableLocation.GetCount();cpt++)
	{
		c_variableLocation.GetLBText(cpt,tempVariableLocation);	
		variableLocation = tempVariableLocation;
		//itoa(cpt,buffer,10);
		keyManagement = eqp->GetKeyManagement(variableLocation);
		if(c_presetType.GetCurSel() == 0) //DATA
		{		
			//Vérifie si il y a un tag data et voice sur ce preset
			if(keyManagement.tag[preset]=='B')
				keyManagement.tag[preset]='V';
			else if(keyManagement.tag[preset]=='D')
				keyManagement.tag[preset]='-';
		}
		else //VOICE
		{
			//Vérifie si il y a un tag data et voice sur ce preset
			if(keyManagement.tag[preset]=='B')
				keyManagement.tag[preset]='D';
			else if(keyManagement.tag[preset]=='V')
				keyManagement.tag[preset]='-';
		}
		eqp->SetKeyManagement(variableLocation,keyManagement);
	}

	//Récupération de la valeur du combo box variable location
	c_variableLocation.GetLBText(c_variableLocation.GetCurSel(),tempVariableLocation);	
	variableLocation = tempVariableLocation;
	keyManagement = eqp->GetKeyManagement(variableLocation);

	if(c_presetType.GetCurSel() == 0) //DATA
	{		
		//Vérifie si il y a un tag voice sur ce preset
		if(keyManagement.tag[preset]=='V')
			keyManagement.tag[preset]='B';
		else
			keyManagement.tag[preset]='D';
	}
	else //VOICE
	{
		//Vérifie si il y a un tag data sur ce preset
		if(keyManagement.tag[preset]=='D')
			keyManagement.tag[preset]='B';
		else
			keyManagement.tag[preset]='V';
	}

	eqp->SetKeyManagement(variableLocation,keyManagement);

	//Set du flag : Key List
	eqp->SetKeyList(1);

	//Apres avoir sauvegarder il faut remettre à jour la vue
	LoadData();
}

void CDlgED42KeyTag::OnSelchangeComboPresetLocation() 
{
	eqp->setModifVue(TRUE);
	
}

void CDlgED42KeyTag::OnSelchangeComboPresetType() 
{
	eqp->setModifVue(TRUE);
}

void CDlgED42KeyTag::OnSelchangeComboVarLocation() 
{
	eqp->setModifVue(TRUE);
	LoadData();
}

void CDlgED42KeyTag::buildComposant(int composant)
{
	int cpt = 0,result =0;;
	char buffer[4]="";
	CString tempVariableLocation = "";
	TKeyManagement keyManagement;

	switch(composant)
	{
	//Construction du combo Variable Location
	case IDC_COMBO_VAR_LOCATION:

		//Récupération de l'ancienne sélection
		c_variableLocation.GetLBText(c_variableLocation.GetCurSel(),tempVariableLocation);			
		
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
			
		result = c_variableLocation.SelectString(-1,tempVariableLocation);
		//Vérifie si la valeur a été trouvée.
		if(result == CB_ERR)
			c_variableLocation.SetCurSel(0);//Premier élément par défaut
		
		break;
	}
}

