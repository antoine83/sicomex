// DlgTRC1752_MOD_CONF_ARQ.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgTRC1752_MOD_CONF_ARQ.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

//***************************************************************************************
// Utilisation de la voie A1 ou B1
//
// Si le choix est sur A1(B1) le bouton "Activer" est autorisé si la voie A1(B1)
// est "A" pour IDC_PROG_STA_A1_IA(IDC_PROG_STA_B1_IA) dans "Programmation_Station".
//
// Si le choix pour "m_FonctionArq" est "NO ALE" ou "ALE" alors m_isArq = TRUE !!
// et on peut réaliser l'aiguillage des commandes :
//
//	ACT, DAC, DVM, ART, DCP, LNL, MDV, LID et UNL
//
// ces commandes retournent un NAC;....;ACCES si la TCL n'est pas possitionnée à ACTIVE !!
//
// Dans m_EtatArq affichage de l'état de l'ARQ et des erreurs de type ACCESS !!
//****************************************************************************************

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_ARQ dialog


CDlgTRC1752_MOD_CONF_ARQ::CDlgTRC1752_MOD_CONF_ARQ(CEquipM1752 * equip, CWnd* pParent /*=NULL*/)
	: CDialog(CDlgTRC1752_MOD_CONF_ARQ::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgTRC1752_MOD_CONF_ARQ)
	m_ArqVoie = 0;
	m_AdaptSans = FALSE;
	m_Mod4285 = TRUE;
	m_ModMil110 = FALSE;
	m_AdaptAvec = TRUE;
	m_voieSachem = FALSE;
	//}}AFX_DATA_INIT

	m_isAdapt	= TRUE;

	this->eqp = equip;
}


void CDlgTRC1752_MOD_CONF_ARQ::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgTRC1752_MOD_CONF_ARQ)
	DDX_Control(pDX, IDC_STATIC_ARQ_DEB, t_ArqDebEmi);
	DDX_Control(pDX, IDC_ARQ_DEB_REC, c_ArqDebRec);
	DDX_Control(pDX, IDC_BUTTON_LOCP, m_Fmp);
	DDX_Control(pDX, IDC_BUTTON_LOCM, m_Fmm);
	DDX_Control(pDX, IDC_BUTTON_DESP, m_Top);
	DDX_Control(pDX, IDC_BUTTON_DESM, m_Tom);
	DDX_Control(pDX, IDC_ETAT_ARQ, c_EtatArq);
	DDX_Control(pDX, IDC_ARQ_ETABLIR, c_ArqEtablire);
	DDX_Control(pDX, IDC_ADAPT_VALIDER, c_AdaptValider);
	DDX_Control(pDX, IDC_ARQ_ACTIVER, c_ArqActiver);
	DDX_Control(pDX, IDC_STATIC_TO, t_To);
	DDX_Control(pDX, IDC_STATIC_ARQ_FM, t_Fm);
	DDX_Control(pDX, IDC_STATIC_ADAPT, t_Adapt);
	DDX_Control(pDX, IDC_FONC_ARQ, c_FonctionArq);
	DDX_Control(pDX, IDC_ATQ_TO, c_ArqTo);
	DDX_Control(pDX, IDC_ARQ_VOIE, c_ArqVoie);
	DDX_Control(pDX, IDC_ARQ_FM, c_ArqFm);
	DDX_Control(pDX, IDC_ADAPT_ENTR, c_AdaptEntrelacement);
	DDX_Control(pDX, IDC_ADAPT_DEBIT, c_AdaptDebit);
	DDX_CBIndex(pDX, IDC_ARQ_VOIE, m_ArqVoie);
	DDX_Check(pDX, IDC_ADAPT_SANS, m_AdaptSans);
	DDX_Check(pDX, IDC_MOD_4285, m_Mod4285);
	DDX_Check(pDX, IDC_MOD_MIL110, m_ModMil110);
	DDX_Check(pDX, IDC_ADAPT_AVEC, m_AdaptAvec);
	DDX_Check(pDX, IDC_SACHEM_VOIE, m_voieSachem);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgTRC1752_MOD_CONF_ARQ, CDialog)
	//{{AFX_MSG_MAP(CDlgTRC1752_MOD_CONF_ARQ)
	ON_CBN_SELCHANGE(IDC_FONC_ARQ, OnSelchangeFoncArq)
	ON_BN_CLICKED(IDC_MOD_4285, OnMod4285)
	ON_BN_CLICKED(IDC_ADAPT_AVEC, OnAdaptAvec)
	ON_BN_CLICKED(IDC_ADAPT_SANS, OnAdaptSans)
	ON_BN_CLICKED(IDC_MOD_MIL110, OnModMil110)
	ON_BN_CLICKED(IDC_ARQ_ACTIVER, OnArqActiver)
	ON_BN_CLICKED(IDC_ADAPT_VALIDER, OnAdaptValider)
	ON_BN_CLICKED(IDC_ARQ_ETABLIR, OnArqEtablir)
	ON_WM_TIMER()
	ON_CBN_SELCHANGE(IDC_ARQ_VOIE, OnSelchangeArqVoie)
	ON_BN_CLICKED(IDC_BUTTON_LOCP, OnButtonLocp)
	ON_BN_CLICKED(IDC_BUTTON_LOCM, OnButtonLocm)
	ON_BN_CLICKED(IDC_BUTTON_DESP, OnButtonDesp)
	ON_BN_CLICKED(IDC_BUTTON_DESM, OnButtonDesm)
	ON_BN_CLICKED(IDC_SACHEM_VOIE, OnSachemVoie)
	ON_CBN_SELCHANGE(IDC_ARQ_FM, OnSelchangeArqFm)
	ON_CBN_SELCHANGE(IDC_ATQ_TO, OnSelchangeAtqTo)
	ON_BN_CLICKED(IDC_ARQ_DEB_REC, OnArqDebRec)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgTRC1752_MOD_CONF_ARQ message handlers

void CDlgTRC1752_MOD_CONF_ARQ::Valide ()
{
}


BOOL CDlgTRC1752_MOD_CONF_ARQ::OnInitDialog()
{
	CDialog::OnInitDialog();

	LoadData();
	SetTimer(1, 1500, NULL);

	pBtnVoieSachem = (CButton*) GetDlgItem(IDC_SACHEM_VOIE);

	c_AdaptValider.EnableWindow(FALSE);
	c_ArqEtablire.EnableWindow(FALSE);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgTRC1752_MOD_CONF_ARQ::OnSelchangeFoncArq()
{
	// FDI
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	TPCArq arq = eqp->GetPcArq(channel);
	//

	//CString str;

	c_FonctionArq.GetLBText(c_FonctionArq.GetCurSel(), str);

	if (str != "TRANS")
		AfficheAle(TRUE);
	else
		AfficheAle(FALSE);

	// FDI
	arq.fonction = (char*)LPCTSTR(str);
	eqp->SetPcArq(channel, arq);


}

void CDlgTRC1752_MOD_CONF_ARQ::OnMod4285()
{
	// FDI
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	TPCArq arq = eqp->GetPcArq(channel);
	//

	m_Mod4285 = TRUE;
	m_ModMil110 = FALSE;
	UpdateData(FALSE);

	// FDI
	arq.modulation = "4285";
	eqp->SetPcArq(channel, arq);
}

void CDlgTRC1752_MOD_CONF_ARQ::OnModMil110()
{
	// FDI
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	TPCArq arq = eqp->GetPcArq(channel);
	//

	m_Mod4285 = FALSE;
	m_ModMil110 = TRUE;
	UpdateData(FALSE);

	// FDI
	arq.modulation = "MIL110";
	eqp->SetPcArq(channel, arq);
}

void CDlgTRC1752_MOD_CONF_ARQ::OnAdaptAvec()
{
	// FDI
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	TPCArq arq = eqp->GetPcArq(channel);
	//

	m_isAdapt = TRUE;

	m_AdaptSans = FALSE;
	m_AdaptAvec = TRUE;
	// FDI - 201202
	arq.arqdebrec = FALSE;
	c_ArqDebRec.SetCheck(0);
	//

	AfficheAdapt(TRUE);		//AfficheAdapt(m_isAdapt);
	UpdateData(FALSE);

	// FDI
	arq.adaptabilite = "AVEC";
	eqp->SetPcArq(channel, arq);

}

void CDlgTRC1752_MOD_CONF_ARQ::OnAdaptSans()
{
	// FDI
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	TPCArq arq = eqp->GetPcArq(channel);
	//

	m_isAdapt = FALSE;

	m_AdaptSans = TRUE;
	m_AdaptAvec = FALSE;
	// FDI - 201202
	arq.arqdebrec = FALSE;
	c_ArqDebRec.SetCheck(0);
	//

	AfficheAdapt(FALSE);			//AfficheAdapt(m_isAdapt);
	UpdateData(FALSE);

	// FDI
	arq.adaptabilite = "SANS";
	eqp->SetPcArq(channel, arq);
}


// Affichage de la sélection des adresses
void CDlgTRC1752_MOD_CONF_ARQ::AfficheAle(bool val)
{
	c_ArqFm.ShowWindow(val);
	c_ArqTo.ShowWindow(val);
	t_Fm.ShowWindow(val);
	m_Fmp.ShowWindow(val);
	m_Fmm.ShowWindow(val);
	t_To.ShowWindow(val);
	m_Top.ShowWindow(val);
	m_Tom.ShowWindow(val);

	c_ArqEtablire.ShowWindow(val);
}

// De/Grise les paramètres de l'arq
void CDlgTRC1752_MOD_CONF_ARQ::GriseParametres(bool val)
{
	c_FonctionArq.EnableWindow(val);
	GetDlgItem(IDC_MOD_4285)->EnableWindow(val);
	GetDlgItem(IDC_MOD_MIL110)->EnableWindow(val);
	c_ArqFm.EnableWindow(val);
	m_Fmm.EnableWindow(val);
	m_Fmp.EnableWindow(val);
	c_ArqTo.EnableWindow(val);
	m_Tom.EnableWindow(val);
	m_Top.EnableWindow(val);
}

// Affichage des choix si Adaptativité = Avec
void CDlgTRC1752_MOD_CONF_ARQ::AfficheAdapt(bool val)
{
	c_AdaptDebit.ShowWindow(val);
	c_AdaptEntrelacement.ShowWindow(val);
	c_AdaptValider.ShowWindow(val);
	//c_ArqDebRec.ShowWindow(val);
	t_ArqDebEmi.ShowWindow(val);
}


void CDlgTRC1752_MOD_CONF_ARQ::OnArqActiver()
{
	// Activation de l'ARQ le bouton passe à Désactiver !!

	// Réalise les action suivantes :
	// DAC, DVM, DCP puis ACT.
	// Pour le DAC retournent un NAC;DAC;ACCES si la TCL n'est pas possitionnée à ACTIVE !!
	// Et on ne va pa plus loin !!
	// Affichage de NAC;DAC;ACCES dans IDC_ETAT_ARQ;
	// Si la réponse à toutes les commandes est ACK;...... et (isALE = FALSE && isARQ=TRUE) alors c_ArqEtablire.ShowWindow(TRUE);

	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	TPCArq arq = eqp->GetPcArq(channel);
	c_FonctionArq.GetLBText(c_FonctionArq.GetCurSel(), str);
	arq.fonction = (char*)LPCTSTR(str);


	if (arq.active)
	{
		// Desactivation
		if (arq.fonction != "TRANS" && arq.fonction != "NO PIL")
		{
			if (0 != eqp->Desactiver(channel)) return;
		}

		arq.active		= FALSE;
		arq.etabli		= FALSE;
		arq.etat		= "INACTIF";
		// FDI - 201202
		arq.arqdebrec	= FALSE;

		// Mise à jour de la structure ARQ
		eqp->SetPcArq(channel, arq);
	} else
	{
		// Activation

		if (arq.fonction != "TRANS" && arq.fonction != "NO PIL")
		{
			// DAC
			// Verification TCL
			if (eqp->GetChannelLocalRemoteControl(channel) != "LOCAL")
			{
				AfxMessageBox("Refusé, la TCL n'est pas active");
				return;
			}

			string channel_type = eqp->GetChannelType(channel);

			if (eqp->GetChannelState(channel) == "ACTIVE")
			{
				if (0 != eqp->Desactiver(channel)) return;
			}

			c_FonctionArq.GetLBText(c_FonctionArq.GetCurSel(), str);
			arq.fonction = (char*)LPCTSTR(str);

			if (m_Mod4285 == TRUE) arq.modulation = "4285";
			else arq.modulation = "MIL110";

			arq.current_adresse_locale = c_ArqFm.GetCurSel();
			arq.current_adresse_destinataire = c_ArqTo.GetCurSel();

			if (arq.current_adresse_locale == -1 || arq.current_adresse_destinataire == -1)
			{
				AfxMessageBox("Refusé, adresses non Validées");
				return;
			}

			// DVM & DCP & ART
			if (0 != eqp->DefinitionArq(channel, arq.fonction, arq.modulation,
										arq.current_adresse_locale, arq.current_adresse_destinataire))
			{
				AfxMessageBox("Refusé, adresses incorrectes");
				return;
			}

			eqp->SetChannelType(channel, channel_type);

			// ACT sur MC de la voie
			if (0 != eqp->Activer(channel)) return;
			eqp->SendTSP(channel);
		}

		// Reussi
		if (arq.fonction == "TRANS")
		{
			arq.etat = "TRANSPARENT";
			arq.active = TRUE;
		}
		else
			arq.etat = "ACTIVATION";
		eqp->SetPcArq(channel, arq);
	}


}

void CDlgTRC1752_MOD_CONF_ARQ::OnAdaptValider()
{
	// Permet d'envoyer la commande MDV si :
	// m_isAdapt = TRUE && (m_isArq = TRUE || (isArq = TRUE && isAle = TREU)  && c_ArqActiver= Désactiver

	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	TPCArq arq = eqp->GetPcArq(channel);

	c_AdaptDebit.GetLBText(c_AdaptDebit.GetCurSel(), str);
	arq.debit = (char*)LPCTSTR(str);

	c_AdaptEntrelacement.GetLBText(c_AdaptEntrelacement.GetCurSel(), str);
	arq.codage = (char*)LPCTSTR(str);

	if (eqp->ModificationArq(channel, arq.debit, arq.codage) < 0)
	{
		AfxMessageBox("Erreur dans le MDV");
		return;
	}

	eqp->SetPcArq(channel, arq);
}


void CDlgTRC1752_MOD_CONF_ARQ::OnArqEtablir()
{

	// Les cas à considérer sont :
	//		- isArq = TRUE et isAle = FALSE,
	//		- isArq = TRUE et isAle = TRUE.
	//		- isArq = FALSE et isAle = FALSE (mode TRANSPARENT n'a pas d'interet pour les télécommandes)..
	// Passe le bouton passe à "Couper" si :
	// - Affichage de "LIEN ETABLI" dans m_EtatArq (tjrs si isArq = TRUE°,
	// - Affichage de "LIEN ETABLI" dans m_EtatArq si le lien ALE est "LINKED" ou
	//   "LINKING" si isAle = TRUE.

	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	TPCArq arq = eqp->GetPcArq((char*)LPCTSTR(str));

	arq.arqdebrec	= FALSE;

	if (arq.etabli)
	{
		if (eqp->GetChannelType(channel) != "-")
		{
			eqp->CasserAppel(channel);
		}else arq.etat = "VEILLE";

		arq.etabli		= FALSE;
	}
	else
	{
		if (arq.fonction == "ALE" && eqp->GetChannelType(channel) != "-")
		{
			eqp->LancerAppel(channel);
		}

		arq.etat = "APPEL EN COURS";
	}

	eqp->SetPcArq(channel, arq);

}

void CDlgTRC1752_MOD_CONF_ARQ::LoadData()
{
	int i;

	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);

	TPCArq arq = eqp->GetPcArq((char*)LPCTSTR(str));

	UpdateData(TRUE);

	// FDI - Voie SACHEM
	m_voieSachem = arq.sachem;
	UpdateData(FALSE);

	c_FonctionArq.SelectString(0, arq.fonction.c_str());

	if (arq.fonction != "TRANS")
		AfficheAle(TRUE);
	else
		AfficheAle(FALSE);

	if (arq.modulation == "MIL110")
	{
		m_Mod4285 = FALSE;
		m_ModMil110 = TRUE;
	} else
	{
		m_Mod4285 = TRUE;
		m_ModMil110 = FALSE;
	}

	if (arq.adaptabilite == "SANS")
	{
		m_AdaptAvec = FALSE;
		m_AdaptSans = TRUE;
		AfficheAdapt(FALSE);
	} else
	{
		m_AdaptAvec = TRUE;
		m_AdaptSans = FALSE;
		AfficheAdapt(TRUE);
	}

	c_AdaptDebit.SelectString(0, arq.debit.c_str());
	c_AdaptEntrelacement.SelectString(0, arq.codage.c_str());

	c_ArqFm.ResetContent();
	for(int i=0; i<arq.adresses_locales.size();i++)
		c_ArqFm.AddString(arq.adresses_locales[i].c_str());

	if(arq.current_adresse_locale < arq.adresses_locales.size())
		c_ArqFm.SetCurSel(arq.current_adresse_locale);

	c_ArqTo.ResetContent();
	for(i=0; i<arq.adresses_destinataires.size();i++)
		c_ArqTo.AddString(arq.adresses_destinataires[i].c_str());

	if(arq.current_adresse_destinataire < arq.adresses_destinataires.size())
		c_ArqTo.SetCurSel(arq.current_adresse_destinataire);

	if (arq.active)
		c_ArqActiver.SetWindowText("Desactiver");
	else
		c_ArqActiver.SetWindowText("Activer");

	if (arq.etabli)
		c_ArqEtablire.SetWindowText("Couper");
	else
		c_ArqEtablire.SetWindowText("Etablir");

	// FDI - 201202
	if (arq.arqdebrec)
		c_ArqDebRec.SetCheck(1);
	else
		c_ArqDebRec.SetCheck(0);

	UpdateData(FALSE);

}

void CDlgTRC1752_MOD_CONF_ARQ::OnTimer(UINT nIDEvent)
{
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);
	c_ArqActiver.GetWindowText(str);
	string activer = (char*)LPCTSTR(str);
	c_ArqEtablire.GetWindowText(str);
	string etablir = (char*)LPCTSTR(str);
	c_EtatArq.GetWindowText(str);
	string etat = (char*)LPCTSTR(str);
	TPCArq arq = eqp->GetPcArq(channel);


	// Etat arq
	if (arq.etat != etat)
		c_EtatArq.SetWindowText(arq.etat.c_str());

	// Changement des boutons
	if (arq.active && activer != "Desactiver")
		c_ArqActiver.SetWindowText("Desactiver");
	else if (!arq.active && activer != "Activer")
		c_ArqActiver.SetWindowText("Activer");

	if (arq.etabli && etablir != "Couper")
		c_ArqEtablire.SetWindowText("Couper");
	else if (!arq.etabli && etablir != "Etablir")
		c_ArqEtablire.SetWindowText("Etablir");

	// Affichage des boutons
	if (eqp->GetChannelState(channel) != "ACTIVE" && arq.fonction != "TRANS" && arq.fonction != "NO PIL")
	{
		GriseParametres(TRUE);
		c_ArqEtablire.EnableWindow(FALSE);
		c_AdaptValider.EnableWindow(FALSE);
		arq.active = FALSE;
		arq.etabli = FALSE;
		arq.etat = "INACTIF";
		eqp->SetPcArq(channel, arq);
		return;
	}
	else // chaine active
	{
		c_ArqActiver.EnableWindow(TRUE);

		if (arq.active)
		{ // lien actif

			// On cache les fonctions non autorisée
			GriseParametres(FALSE);

			// si on est en ale
			if (arq.fonction == "ALE" && eqp->GetChannelType(channel) != "-")
			{
				string etat_ale = eqp->GetAleParameter(channel).ale_status;

				if (eqp->IsAppel(channel))
				{
					if (etat_ale == "LKG" || etat_ale == "LKD")
					{
						arq.etabli = TRUE;
						arq.etat = "LIEN ETABLI";
					}
				} else
				{
					arq.etabli = FALSE;
					arq.etat = "VEILLE";
					// FDI
					if (arq.sachem == FALSE)
							arq.etat = "LIEN ACP ROMPU";

				}

				eqp->SetPcArq(channel, arq);
			} else
			{
				// Si un etablissement est en cours, on le valide pour le prochain cycle
				if (arq.etat == "APPEL EN COURS")
				{
					if (arq.fonction != "NO ARQ") // en no arq il reste en appel en cours
						arq.etat = "LIEN ETABLI";

					arq.etabli = TRUE;
					eqp->SetPcArq(channel, arq);
				}
			}

			if (arq.fonction != "TRANS")
				c_ArqEtablire.EnableWindow(TRUE);

			if (arq.etabli)
			{ // lien etabli
				c_AdaptValider.EnableWindow(TRUE);
			}
			else
			{
				c_AdaptValider.EnableWindow(FALSE);
			}
		}
		else
		{
			// On montre les fonctions arq
			GriseParametres(TRUE);

			// Si activation en cours, on valide l'activation pour le prochain cycle
			if (arq.etat == "ACTIVATION")
			{
				arq.active = TRUE;
				arq.etat = "VEILLE";
				// FDI
				if (arq.sachem == FALSE)
						arq.etat = "LIEN ACP ROMPU";

				eqp->SetPcArq(channel, arq);
			}

			c_ArqEtablire.EnableWindow(FALSE);
		}
	}

	// FDI
	if (m_voieSachem == FALSE && arq.active == TRUE && arq.fonction != "TRANS")
	{
		// La voie SACHEM est ouverte
		arq.sachem = FALSE;
		arq.etat = "LIEN ACP ROMPU";
		eqp->SetPcArq(channel, arq);
	}

}

void CDlgTRC1752_MOD_CONF_ARQ::OnSelchangeArqVoie()
{
	LoadData();
}

void CDlgTRC1752_MOD_CONF_ARQ::OnButtonLocp()
{
	// Ajout d'une adresse
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);
	c_ArqFm.GetWindowText(str);
	string adr = (char*)LPCTSTR(str);

	if (!eqp->ValidTableAddress(adr))
	{
		AfxMessageBox("Adresse incorrecte");
		return;
	}

	TPCArq arq = eqp->GetPcArq(channel);

	arq.adresses_locales.push_back(adr);
	arq.current_adresse_locale = arq.adresses_locales.size()-1;

	eqp->SetPcArq(channel, arq);

	UpdateData(TRUE);

	c_ArqFm.AddString(adr.c_str());
	c_ArqFm.SetCurSel(arq.current_adresse_locale);

	UpdateData(FALSE);

	c_ArqFm.SetCurSel(arq.current_adresse_locale);
}

void CDlgTRC1752_MOD_CONF_ARQ::OnButtonLocm()
{
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	int pos = c_ArqFm.GetCurSel();

	if (pos<0) return;
	if(c_ArqFm.GetCount()<=1)return;

	TPCArq arq = eqp->GetPcArq(channel);

	arq.adresses_locales.erase(arq.adresses_locales.begin()+pos);
	arq.current_adresse_locale = 0;

	eqp->SetPcArq(channel, arq);

	UpdateData(TRUE);

	c_ArqFm.DeleteString(pos);
	c_ArqFm.SetCurSel(0);

	UpdateData(FALSE);
}

void CDlgTRC1752_MOD_CONF_ARQ::OnButtonDesp()
{
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);
	c_ArqTo.GetWindowText(str);
	string adr = (char*)LPCTSTR(str);

	if (!eqp->ValidTableAddress(adr))
	{
		AfxMessageBox("Adresse incorrecte");
		return;
	}

	TPCArq arq = eqp->GetPcArq(channel);

	arq.adresses_destinataires.push_back(adr);
	arq.current_adresse_destinataire = arq.adresses_destinataires.size()-1;

	eqp->SetPcArq(channel, arq);

	UpdateData(TRUE);

	c_ArqTo.AddString(adr.c_str());
	c_ArqTo.SetCurSel(arq.current_adresse_destinataire);

	UpdateData(FALSE);

	c_ArqTo.SetCurSel(arq.current_adresse_destinataire);
	c_AdaptValider.EnableWindow(TRUE);
}

void CDlgTRC1752_MOD_CONF_ARQ::OnButtonDesm()
{
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	int pos = c_ArqTo.GetCurSel();

	if (pos<0) return;
	if(c_ArqTo.GetCount()<=1)return;
	TPCArq arq = eqp->GetPcArq(channel);

	arq.adresses_destinataires.erase(arq.adresses_destinataires.begin()+pos);
	arq.current_adresse_destinataire = 0;

	eqp->SetPcArq(channel, arq);

	UpdateData(TRUE);

	c_ArqTo.DeleteString(pos);
	c_ArqTo.SetCurSel(0);

	UpdateData(FALSE);
}


void CDlgTRC1752_MOD_CONF_ARQ::OnSachemVoie()
{
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	TPCArq arq = eqp->GetPcArq(channel);

	if (arq.sachem == false )
	{
		m_voieSachem = TRUE;
	}
	else
	{
		m_voieSachem = FALSE;
	}

	UpdateData(FALSE);

	// FDI - 09/09/2015
	if (pBtnVoieSachem->GetCheck())
		arq.sachem = TRUE;
	else
		arq.sachem = FALSE;
	eqp->SetPcArq(channel, arq);

}

void CDlgTRC1752_MOD_CONF_ARQ::OnSelchangeArqFm()
{
	// FDI
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);


	TPCArq arq = eqp->GetPcArq(channel);


	arq.current_adresse_locale = c_ArqFm.GetCurSel();
	eqp->SetPcArq(channel, arq);

}

void CDlgTRC1752_MOD_CONF_ARQ::OnSelchangeAtqTo()
{
	// FDI
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);


	TPCArq arq = eqp->GetPcArq(channel);


	arq.current_adresse_destinataire = c_ArqTo.GetCurSel();
	eqp->SetPcArq(channel, arq);

}

void CDlgTRC1752_MOD_CONF_ARQ::OnArqDebRec()
{
	// FDI - 201202
	CString str;
	c_ArqVoie.GetLBText(c_ArqVoie.GetCurSel(), str);
	string channel = (char*)LPCTSTR(str);

	TPCArq arq = eqp->GetPcArq(channel);
	//

	UpdateData(FALSE);

	arq.arqdebrec = FALSE;

	if (c_ArqDebRec.GetCheck() == 1)
	{
		arq.arqdebrec = TRUE;
	}

	eqp->SetPcArq(channel, arq);
}
