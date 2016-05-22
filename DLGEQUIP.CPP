/* **************************************************************************
FICHIER :	DlgEquip.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CDlgEquip
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"

#include "DlgEquip.h"
#include "Equip\ParamSim.h"
#include "divers\div_fic.h"
#include "DlgOutil.h"
#include "custom\inter.h"

#include <mmsystem.h>

#ifdef _DEBUG
#undef THIS_FILE
static char BASED_CODE THIS_FILE[] = __FILE__;
#endif

extern		CParamSimu *glob_paramsimu;
extern		CDlgOutil *glob_barre;

extern 	char glob_SON_CORRECT[];
extern 	char glob_SON_INCORRECT[];

extern char glob_EQUIP_ON[];
extern char glob_EQUIP_OFF[];

extern 	char glob_CHEMIN[];

const int	TAILLE_MESSAGE=81;

CDlgEquip::CDlgEquip(UINT nID, CWnd* pParent /*=NULL*/)
	: CDialog(nID, pParent)
{
	timer = 1;
	evolution = 0;

	m_hIcon = AfxGetApp()->LoadIcon(IDI_SICOMEX);
}

void CDlgEquip::Associe(CEquip	*eqp)
{
	equip = eqp;
}

/* *********************************************************************
METHODE : 	OnOuvrir()
TRAITEMENT:	Charge un contexte d'exploitation
********************************************************************** */
void CDlgEquip::OnOuvrir()
{
	int		i,iResult;
	char	fichier[80]="";

	int		index;
	char	buf[80];
	CListBox	*m_liste_message = (CListBox*)GetDlgItem(IDC_MES_STATUT);
	CListBox	*m_sequence = (CListBox*)GetDlgItem(IDC_SEQ_STATUT);

	CFileDialog win(TRUE,"ctx",fichier,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		,"Contexte (*.ctx)|*.ctx|Fichier ASCII (*.txt)|*.txt||"
 		,this);

	win.m_ofn.Flags &= ~OFN_SHOWHELP;
	win.m_ofn.Flags &= ~524288;		//OFN_EXPLORER;
	 	 				
	iResult = win.DoModal();
	if(iResult != IDOK) return;

	strcpy(fichier,win.GetPathName()); 
	equip->Charge_Contexte(fichier);

	m_sequence->ResetContent();

	i=0;
	while(TRUE)
	{
		index = equip->LireSequence(i);
	 	if(index <0) break;

		if(m_liste_message->GetTextLen(index) < 80)
			m_liste_message->GetText(index, buf);
		else
			strcpy(buf, "Item trop grand");

		m_sequence->AddString(buf);
		i++;
	}	
}
/* *********************************************************************
METHODE : 	OnSauver()
TRAITEMENT:	sauve un contexte d'exploitation
********************************************************************** */
void CDlgEquip::OnSauver()
{
	int		iResult;
	char	fichier[80]="";

	CFileDialog win(FALSE,"ctx",fichier,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		,"Contexte (*.ctx)|*.ctx|Fichier ASCII (*.txt)|*.txt||"
 		,this);
	 	 
	win.m_ofn.Flags &= ~OFN_SHOWHELP;
	win.m_ofn.Flags &= ~524288;		//OFN_EXPLORER;

	iResult = win.DoModal();
	if(iResult != IDOK) return;

	strcpy(fichier,win.GetPathName()); 
	equip->Sauve_Contexte(fichier);
}


void CDlgEquip::GenerateurAuto()
{
}

void CDlgEquip::OnTimer() 
{
	static	int compteur = 0;

	compteur = (compteur+1) % 30;

	// Forcer l'envoi de message non acquitté, ou des envois automatiques
	if(compteur==0)
		equip->EnvoyerMessage(NULL,CDE_TEXTE_SEUL);

	if(compteur%1==0)
		GenerateurAuto();			// Varaiation automatique de parametre

// Teste l'état d'un sequence en cours
	if(!equip->EnCours() && equip->Actif())
	{
		GetDlgItem(IDC_ENVOI_STATUT)->EnableWindow(TRUE);
		GetDlgItem(IDC_ARRET_STATUT)->EnableWindow(FALSE);
		GetDlgItem(IDC_AJOUT_MESSAGE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_CYCLE)->EnableWindow(TRUE);
		GetDlgItem(IDC_CHECK_SYNCHRO)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_CYCLE)->EnableWindow(TRUE);
		GetDlgItem(IDC_EDIT_TEMPO)->EnableWindow(TRUE);
		GetDlgItem(IDC_RETIRE_MESSAGE)->EnableWindow(TRUE);
	}
		
}

void CDlgEquip::AjoutJournal(char *mes,int code_erreur)
{
	if (glob_paramsimu == NULL)
		return;

	char 		buf[TAILLE_MESSAGE];
	int			i,iResult;
	int			nb_max_message = glob_paramsimu->MaxMessage();

	if(strlen(mes)>TAILLE_MESSAGE-5)		// 5 pour formatage code erreur 
		mes[TAILLE_MESSAGE-5]=0;			// Force limitte la taille des messsage

	if(code_erreur)
		sprintf(buf,"%s (%2d)",mes,code_erreur);
	else
		strcpy(buf,mes);
	
	journal = (CListBox*)GetDlgItem(IDC_JOURNAL);

	iResult = journal->GetCount();
		for(i=nb_max_message ; i<=iResult ; i++)
		journal->DeleteString(0);

	iResult = journal->AddString(buf);
	journal->SetCaretIndex(iResult,FALSE);	// Se place sur le message ajouter
}

void CDlgEquip::OnCouper()
{
	int		i;
	int		taille;

	journal = (CListBox*)GetDlgItem(IDC_JOURNAL);
	taille = journal->GetCount();

	for(i=taille-1 ; i>=0 ; i--)
	{
		if(journal->GetSel(i))
			journal->DeleteString(i);
	}
}

void CDlgEquip::OnCouperTout()
{
	int		i;
	int		taille;

	journal = (CListBox*)GetDlgItem(IDC_JOURNAL);
	taille = journal->GetCount();

	for(i=taille-1 ; i>=0 ; i--)
	{
		journal->DeleteString(i);
	}
}

void CDlgEquip::OnSauvegarde()
{
	int		i,iResult;
	int		taille;
	char	parametre[TAILLE_MESSAGE-1];
	char	*message;

	char	fichier[80]="";

	journal = (CListBox*)GetDlgItem(IDC_JOURNAL);

	CFileDialog win(TRUE,"jou",fichier,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT
		,"Journal(*.jou)|*.jou|Fichier ASCII (*.txt)|*.txt||"
 		,this);
	 	 
	win.m_ofn.Flags &= ~OFN_SHOWHELP;
	win.m_ofn.Flags &= ~524288;		//OFN_EXPLORER;

	iResult = win.DoModal();
	if(iResult != IDOK) return;

	strcpy(fichier,win.GetPathName()); 

	taille = journal->GetCount();
	message = (char*) malloc(taille*(TAILLE_MESSAGE));
	if(message==NULL) return;

	strcpy(message,"");
	for(i=0 ; i<taille ; i++)
	{
		journal->GetText(i,parametre);
		strcat(message,parametre);
		strcat(message,"\r\n");
	}

	i = Stocker_fichier(fichier,message);
   	if(message!= NULL) free(message);

	i = Stocker_fichier(fichier,message);
}

void CDlgEquip::OnClose() 
{
	if (glob_paramsimu == NULL)
		return;

	glob_barre->MasqueEcran(glob_paramsimu->Icone(equip->Index()));
}

/////////////////////////////////////////////////////////////////////////////
// CDlgEquip dialog

void CDlgEquip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgEquip)
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgEquip, CDialog)
	//{{AFX_MSG_MAP(CDlgEquip)
	ON_WM_CLOSE()
	ON_BN_CLICKED(IDC_AJOUT_MESSAGE, OnAjoutMessage)
	ON_BN_CLICKED(IDC_CHECK_CYCLE, OnCheckCycle)
	ON_BN_CLICKED(IDC_CHECK_SYNCHRO, OnCheckSynchro)
	ON_EN_KILLFOCUS(IDC_EDIT_CYCLE, OnKillfocusEditCycle)
	ON_EN_KILLFOCUS(IDC_EDIT_TEMPO, OnKillfocusEditTempo)
	ON_BN_CLICKED(IDC_ENVOI_STATUT, OnEnvoiStatut)
	ON_BN_CLICKED(IDC_ARRET_STATUT, OnArretStatut)
	ON_BN_CLICKED(IDC_RETIRE_MESSAGE, OnRetireMessage)
	ON_BN_CLICKED(IDC_PRECEDENT, OnPrecedent)
	ON_BN_CLICKED(IDC_SUIVANT, OnSuivant)
	ON_LBN_DBLCLK(IDC_JOURNAL, OnDblclkJournal)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_ENVOI_TRAME, OnEnvoiTrame)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

BOOL CDlgEquip::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	SetTimer(1,1000,NULL);	

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void CDlgEquip::OnAjoutMessage() 
{
	int			index;
	char	buf[80];
	CListBox	*m_liste_message = (CListBox*)GetDlgItem(IDC_MES_STATUT);
	CListBox	*m_sequence = (CListBox*)GetDlgItem(IDC_SEQ_STATUT);

	index = m_liste_message->GetCurSel();
 
 	if(index != LB_ERR)
	{
		if(m_liste_message->GetTextLen(index) < 80)
			m_liste_message->GetText(index, buf);
		else
			strcpy(buf, "Item trop grand");
	
		m_sequence->AddString(buf);
	
		equip->AjouterSequence(index);
	}	
}

void CDlgEquip::OnRetireMessage() 
{
	int			index;

	CListBox	*m_sequence = (CListBox*)GetDlgItem(IDC_SEQ_STATUT);

	index = m_sequence->GetCurSel();
 
 	if(index != LB_ERR)
	{
		m_sequence->DeleteString(index);
		equip->RetirerSequence(index);
	}
	
}

void CDlgEquip::OnEnvoiStatut() 
{
	GetDlgItem(IDC_ENVOI_STATUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_ARRET_STATUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_AJOUT_MESSAGE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_CYCLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_CHECK_SYNCHRO)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_CYCLE)->EnableWindow(FALSE);
	GetDlgItem(IDC_EDIT_TEMPO)->EnableWindow(FALSE);
	GetDlgItem(IDC_RETIRE_MESSAGE)->EnableWindow(FALSE);
	
	equip->ChangeEnCours(TRUE);
}

void CDlgEquip::OnArretStatut() 
{
	equip->ChangeEnCours(FALSE);

	GetDlgItem(IDC_ENVOI_STATUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_ARRET_STATUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_AJOUT_MESSAGE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_CYCLE)->EnableWindow(TRUE);
	GetDlgItem(IDC_CHECK_SYNCHRO)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_CYCLE)->EnableWindow(TRUE);
	GetDlgItem(IDC_EDIT_TEMPO)->EnableWindow(TRUE);
	GetDlgItem(IDC_RETIRE_MESSAGE)->EnableWindow(TRUE);
}

void CDlgEquip::OnCheckCycle() 
{
	CButton	*m_cycle = (CButton*)GetDlgItem(IDC_CHECK_CYCLE);
	equip->ChangeEnvoiCyclique(m_cycle->GetCheck());
}

void CDlgEquip::OnCheckSynchro() 
{
	CButton	*m_synchro = (CButton*)GetDlgItem(IDC_CHECK_SYNCHRO);
	equip->ChangeSynchronise(m_synchro->GetCheck());
}

void CDlgEquip::OnKillfocusEditCycle() 
{
	BOOL	bResult;
	char	buf[81];

	CEdit	*m_cycle = (CEdit*)GetDlgItem(IDC_EDIT_CYCLE);
	
	m_cycle->GetLine(0,buf,80);
	bResult = equip->ChangePeriode(atoi(buf));
	if(!bResult)
	{
		JouerSon(glob_SON_INCORRECT);
		sprintf(buf,"%d",equip->Periode());

		m_cycle->SetSel(0,-1,TRUE);
		m_cycle->ReplaceSel(buf);
	}
}

void CDlgEquip::OnKillfocusEditTempo() 
{
	BOOL	bResult;
	char	buf[81];

	CEdit	*m_cycle = (CEdit*)GetDlgItem(IDC_EDIT_TEMPO);
	
	m_cycle->GetLine(0,buf,80);
	bResult = equip->ChangeDureeTempo(atoi(buf));
	if(!bResult)
	{
		JouerSon(glob_SON_INCORRECT);
		sprintf(buf,"%d",equip->DureeTempo());

		m_cycle->SetSel(0,-1,TRUE);
		m_cycle->ReplaceSel(buf);
	}
}

void CDlgEquip::JouerSon(LPCTSTR lpszSound)
{
	char	nom_fichier[256];
  	char	*pcResult;
	
	pcResult = strstr((char *)lpszSound,":\\");
	if(pcResult == NULL) sprintf(nom_fichier,"%s\\%s",glob_CHEMIN,lpszSound);
	else strcpy(nom_fichier,lpszSound);

	sndPlaySound(nom_fichier,SND_SYNC);
}

void CDlgEquip::OnPrecedent()
{
	int 	index,taille;
	char	mot[TAILLE_MESSAGE];
	char	buf[TAILLE_MESSAGE];
	BOOL	trouve = FALSE;

	CEdit	*m_mot_cle = (CEdit*)GetDlgItem(IDC_CHERCHE);
	journal = (CListBox*)GetDlgItem(IDC_JOURNAL);

	m_mot_cle->GetLine(0,mot,TAILLE_MESSAGE-1);

	taille = journal->GetCount();
	// TODO
 	if(position_courante > taille-1) position_courante = taille-1;
	index = position_courante;

	BeginWaitCursor( );
	while(--index >= 0)
	{
		if(journal->GetTextLen(index) < TAILLE_MESSAGE-1)
			journal->GetText(index, buf);
		else
			strcpy(buf, "");
		
		if(NULL != strstr(buf,mot))
		{
		 	trouve = TRUE;
			break;
		}
	}
	EndWaitCursor( );

	if(trouve)
	{
	 	position_courante = index;
	 	journal->SetSel(index,TRUE);
		journal->SetCaretIndex(index,FALSE);	// Se place sur le message ajouter
		JouerSon(glob_SON_CORRECT);
	}
	else
		JouerSon(glob_SON_INCORRECT);

}

void CDlgEquip::OnSuivant() 
{
	int 	index,taille;
	char	mot[TAILLE_MESSAGE];
	char	buf[TAILLE_MESSAGE];
	BOOL	trouve = FALSE;

	CEdit	*m_mot_cle = (CEdit*)GetDlgItem(IDC_CHERCHE);
	journal = (CListBox*)GetDlgItem(IDC_JOURNAL);

	m_mot_cle->GetLine(0,mot,TAILLE_MESSAGE-1);

	taille = journal->GetCount();
	if(position_courante < 0)	position_courante = 0;
	index = position_courante;
 
	BeginWaitCursor( );
	while(++index <= taille)
	{
		if(journal->GetTextLen(index) < TAILLE_MESSAGE-1)
			journal->GetText(index, buf);
		else
			strcpy(buf, "");
		
		if(NULL != strstr(buf,mot))
		{
		 	trouve = TRUE;
			break;
		}
	}
	EndWaitCursor( );

	if(trouve)
	{
	 	position_courante = index;
	 	journal->SetSel(index,TRUE);
		journal->SetCaretIndex(index,FALSE);	// Se place sur le message ajouter
		JouerSon(glob_SON_CORRECT);
	}
	else
		JouerSon(glob_SON_INCORRECT);

}

void CDlgEquip::OnDblclkJournal() 
{
	journal = (CListBox*)GetDlgItem(IDC_JOURNAL);
	position_courante = journal->GetCaretIndex();
	journal->SetSel(position_courante,FALSE);
}

void CDlgEquip::OnPaint() 
{
	CPaintDC dc(this); // device context for painting
	
	if (IsIconic())
	{
		glob_barre->MasqueEcran(glob_paramsimu->Icone(equip->Index()));

/*
		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
*/
	}
	else
	{
		CDialog::OnPaint();
	// Do not call CDialog::OnPaint() for painting messages
	}
}

void CDlgEquip::OnEnvoiTrame() 
{

	int		i,code_ascii;
	char 	buffer[TAILLE_PIPE_MESSAGE+1];
	char	commande[TAILLE_PIPE_MESSAGE+1];
	char	*pcResult;

	CEdit	*m_trame	 = (CEdit*)GetDlgItem(IDC_TRAME);

	m_trame->GetLine(0,buffer,TAILLE_PIPE_MESSAGE);

	if(buffer[0]==0) return;	// Chaine vide

// Transformation en message ASCII 
	pcResult = buffer;
	strcpy(commande,"");
	i=0;
	while(pcResult <= buffer+(int)strlen(buffer))
	{
		sscanf(pcResult,"%2X",&code_ascii);
		commande[i]=code_ascii;
		i++;
		pcResult += 3 ;
	}
	commande[i]=0;

	equip->EnvoyerMessage(commande,CDE_HEXA);
}

void CDlgEquip::OnActivite() 
{
	CInter	*m_activite = (CInter*)GetDlgItem(IDC_ACTIVITE);
	CInter	*m_cik = (CInter*)GetDlgItem(IDC_ED42_DCP_CIK);
	CInter	*m_nl = (CInter*)GetDlgItem(IDC_ED42_DCP_NL);
	CInter	*m_eg = (CInter*)GetDlgItem(IDC_ED42_DCP_EG);

	BOOL	bResult = equip->Power();

	if(bResult)
	{
		JouerSon(glob_EQUIP_ON);
		GetMenu()->EnableMenuItem(ID_CONTEXTE_OUVRIR,MF_DISABLED | MF_GRAYED);
		GetMenu()->EnableMenuItem(ID_CONTEXTE_SAUVER,MF_DISABLED | MF_GRAYED);
	}
	else
	{
		JouerSon(glob_EQUIP_OFF);
		OnArretStatut();		// Arret la sequence

		GetMenu()->EnableMenuItem(ID_CONTEXTE_OUVRIR,MF_ENABLED);
		GetMenu()->EnableMenuItem(ID_CONTEXTE_SAUVER,MF_ENABLED);
	}
	
	GetDlgItem(IDC_ENVOI_STATUT)->EnableWindow(bResult);
//	GetDlgItem(IDC_ARRET_STATUT)->EnableWindow(bResult);
	m_activite->Positionne_etat(bResult);
}


void CDlgEquip::OnTc()
{
}
