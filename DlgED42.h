// DlgED42.h: interface for the CDlgED42 class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DLGED42_H__15B7E677_37DC_436D_95A3_A7CA05789424__INCLUDED_)
#define AFX_DLGED42_H__15B7E677_37DC_436D_95A3_A7CA05789424__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "custom\inter.h"
#include "custom\diode.h"
#include "Equip\EquipED42.h"
#include "DlgEquip.h"
#include "DlgED42Tab.h"
#include "DlgED42ERRPANNE.h"

#include <iostream>
#include <string.h>
#include <stdio.h>
#include <vector>


using namespace std;

/////////////////////////////////////////////////////////////////////////////
// CDlgED42 dialog

class CDlgED42 : public CDlgEquip
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
protected:
	CInter		m_activite;
	CInter		m_cik;
	CInter		m_nl;
	CInter		m_eg;

	t_ComErreur	err;

	CDlgED42Tab* m_dlgTab;
	


public:	
	// Dialog Data
	//{{AFX_DATA(CDlgED42)
	enum { IDD = F12_IDD_ED42 };
	CButton	c_cdeInconnue;
	CButton	c_pasDeReponse;
	CButton	c_errorNumMsg;
	CButton	c_pasDeCr;
	CButton	c_pasDeLf;
	CButton	c_checksum;
	CButton	m_synchro;
	CButton	m_cycle;
	CButton	m_btn_cik;
	CListBox	m_liste_message;
	CString	m_err_retard;
	CString	m_tempo;
	CString	m_periode;
	BOOL	m_debut;
	BOOL	m_fin;
	BOOL	m_inconnue;
	BOOL	m_reponse;
	//}}AFX_DATA
	//int m_timerEd;
	void LoadData();
	void RazEd42();
	BOOL GetClavier();
	void SetClavier(bool val);


	

private:
	BOOL etat;
	BOOL res;
	BOOL remoteMode, valBool;
	int  lockTimeChecker;
	int m_timerEd;

	BOOL isNum;
	//BOOL actionClavier;
	CString chaineSep;
	CString chaineEnCours;
	CString tmpPwd;
	int actionEnCours, actionEnCours1, actionEnCours2;
	int languageCours;

	void affichgeExploitation();
	void GestionAffichage(bool val=false, int param1=0, int param2=0);
	void GestionAffichageExploitation(bool val);
	void GestionAffichageEmRec(bool val);
	void GestionBoutonLockUnlock();
	void BuildComposant(int composant, int preset);
	
	
	
/* **********************************************************************
METHODE :		CDlgED42()
TRAITEMENT:		Constuit l'objet "écran de controle" de l'équipement
***********************************************************************	*/
public:
	CDlgED42(CWnd* pParent = NULL);   // standard constructor
	~CDlgED42();

/* **********************************************************************
METHODE :		DoDataExchange()
TRAITEMENT:		Validation et echande des donnes entre controle et 
				dialogBox
***********************************************************************	*/
	//{{AFX_VIRTUAL(CDlgED42)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL


protected:
	//{{AFX_MSG(CDlgED42)
		virtual BOOL OnInitDialog();
		afx_msg void OnInfo();
		afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnNl();
	afx_msg void OnEg();
	afx_msg void OnEd42DcpBtnFw();
	afx_msg void OnEd42DcpBtnSt();
	afx_msg void OnEd42DcpBtnRs();
	afx_msg void OnChecksum();
	afx_msg void OnNumMsg();
	afx_msg void OnFinTrame();
	afx_msg void OnDebutTrame();
	afx_msg void OnPasReponse();
	afx_msg void OnCdeInconue();
	afx_msg void OnKillfocusRetard();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

protected:
	CEquipED42 * eqp;

private:
	void OnAide();
	void OnErreursPannes();
	//void InitListeCommande();
	void GestionAffichageBoutons(bool affiche);
	void RazAffichage();

	BOOL MiseEnMarche();
	
	CString createAffiche(CString motIn, CString motAjout, int lenAjout);
	void TraitementTouches(CString dcp1, CString dcp2, bool flagAddFonc = FALSE, bool flagFW= FALSE);
	void initAffichageUn(CString ligne1, CString ligne2, int flag1=0, bool flag2=FALSE);
	BOOL userPasswordVerification(CString passwdTmp);

	string cstringTostring(CString motIn);

	BOOL MainMenu();
	BOOL ED42_Lock();
	BOOL ED42_UnLock(bool inZeroize = FALSE);
	BOOL Activ_Local_Ctrl();
	BOOL Cv_Data_Crypto();
	BOOL Cv_Voice_Crypto();

	CString saisieClavier();

	
};

#endif // !defined(AFX_DLGED42_H__15B7E677_37DC_436D_95A3_A7CA05789424__INCLUDED_)
