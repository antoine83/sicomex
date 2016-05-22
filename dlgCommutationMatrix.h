/* **********************************************************************
FICHIER :	dlgMatCom.h		 			AUTEUR : FSA
DATE DE CREATION : 	26/02/07			DERNIERE MODIFICATION : 26/02/07
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		CDlgCommutationMatrix

ROLE DU COMPOSANT :		Gestion de l'écran de contrôle de la matrice de
							commutation.

REFRENCES EXTERNES :
	CCommutationMatrix: Equipement Matrice de commutation
	CInter :			Interrupteur 2 positions M/A
	CDiode :			Indicateur 3 états Oui/Non/Alarme

REFRENCES INTERNES :
	CDlgSimu			Ecran d'accueil du simulateur
	CDlgOutil			Boite d'outil du simulateur
***********************************************************************	*/

#include "custom\inter.h"
#include "custom\diode.h"
#include "DlgEquip.h"

/**
 * This class is a dialogue window for commutation matrix.
 */
class CDlgCommutationMatrix : public CDlgEquip
{
	// ****** Fields ******
protected:
	CInter		m_activite;
	CInter		m_local;


	// ****** Methods ******
public:
	CDlgCommutationMatrix(CWnd* pParent = NULL);

	//{{AFX_DATA(CDlgCommutationMatrix)
	enum { IDD = IDD_COMMUTATION_MATRIX };
	CButton		m_rx[8][8];
	CButton		m_tx[8][8];
	CString		m_inputs[8];
	CString		m_outputs[8];
	HBITMAP		bmp_BLACK;
	HBITMAP		bmp_WHITE;
	CListBox	m_liste_message;
	CButton	m_synchro;
	CButton	m_cycle;
	CString	m_err_retard;
	CString	m_periode;
	CString	m_tempo;
	CString m_result_test;
	//}}AFX_DATA
	void refresh() ;


	//{{AFX_VIRTUAL(CDlgCommutationMatrix)
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	//{{AFX_MSG(CDlgCommutationMatrix)
	virtual BOOL OnInitDialog();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnRemoteControlClicked();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()

private:
	void OnAide();
	void OnComErreur() ;
	void OnClickButtonTX1x1();
	void OnClickButtonTX1x2();
	void OnClickButtonTX1x3();
	void OnClickButtonTX1x4();
	void OnClickButtonTX1x5();
	void OnClickButtonTX1x6();
	void OnClickButtonTX1x7();
	void OnClickButtonTX1x8();
	void OnClickButtonTX2x1();
	void OnClickButtonTX2x2();
	void OnClickButtonTX2x3();
	void OnClickButtonTX2x4();
	void OnClickButtonTX2x5();
	void OnClickButtonTX2x6();
	void OnClickButtonTX2x7();
	void OnClickButtonTX2x8();
	void OnClickButtonTX3x1();
	void OnClickButtonTX3x2();
	void OnClickButtonTX3x3();
	void OnClickButtonTX3x4();
	void OnClickButtonTX3x5();
	void OnClickButtonTX3x6();
	void OnClickButtonTX3x7();
	void OnClickButtonTX3x8();
	void OnClickButtonTX4x1();
	void OnClickButtonTX4x2();
	void OnClickButtonTX4x3();
	void OnClickButtonTX4x4();
	void OnClickButtonTX4x5();
	void OnClickButtonTX4x6();
	void OnClickButtonTX4x7();
	void OnClickButtonTX4x8();
	void OnClickButtonTX5x1();
	void OnClickButtonTX5x2();
	void OnClickButtonTX5x3();
	void OnClickButtonTX5x4();
	void OnClickButtonTX5x5();
	void OnClickButtonTX5x6();
	void OnClickButtonTX5x7();
	void OnClickButtonTX5x8();
	void OnClickButtonTX6x1();
	void OnClickButtonTX6x2();
	void OnClickButtonTX6x3();
	void OnClickButtonTX6x4();
	void OnClickButtonTX6x5();
	void OnClickButtonTX6x6();
	void OnClickButtonTX6x7();
	void OnClickButtonTX6x8();
	void OnClickButtonTX7x1();
	void OnClickButtonTX7x2();
	void OnClickButtonTX7x3();
	void OnClickButtonTX7x4();
	void OnClickButtonTX7x5();
	void OnClickButtonTX7x6();
	void OnClickButtonTX7x7();
	void OnClickButtonTX7x8();
	void OnClickButtonTX8x1();
	void OnClickButtonTX8x2();
	void OnClickButtonTX8x3();
	void OnClickButtonTX8x4();
	void OnClickButtonTX8x5();
	void OnClickButtonTX8x6();
	void OnClickButtonTX8x7();
	void OnClickButtonTX8x8();
	void OnClickButtonRX1x1();
	void OnClickButtonRX1x2();
	void OnClickButtonRX1x3();
	void OnClickButtonRX1x4();
	void OnClickButtonRX1x5();
	void OnClickButtonRX1x6();
	void OnClickButtonRX1x7();
	void OnClickButtonRX1x8();
	void OnClickButtonRX2x1();
	void OnClickButtonRX2x2();
	void OnClickButtonRX2x3();
	void OnClickButtonRX2x4();
	void OnClickButtonRX2x5();
	void OnClickButtonRX2x6();
	void OnClickButtonRX2x7();
	void OnClickButtonRX2x8();
	void OnClickButtonRX3x1();
	void OnClickButtonRX3x2();
	void OnClickButtonRX3x3();
	void OnClickButtonRX3x4();
	void OnClickButtonRX3x5();
	void OnClickButtonRX3x6();
	void OnClickButtonRX3x7();
	void OnClickButtonRX3x8();
	void OnClickButtonRX4x1();
	void OnClickButtonRX4x2();
	void OnClickButtonRX4x3();
	void OnClickButtonRX4x4();
	void OnClickButtonRX4x5();
	void OnClickButtonRX4x6();
	void OnClickButtonRX4x7();
	void OnClickButtonRX4x8();
	void OnClickButtonRX5x1();
	void OnClickButtonRX5x2();
	void OnClickButtonRX5x3();
	void OnClickButtonRX5x4();
	void OnClickButtonRX5x5();
	void OnClickButtonRX5x6();
	void OnClickButtonRX5x7();
	void OnClickButtonRX5x8();
	void OnClickButtonRX6x1();
	void OnClickButtonRX6x2();
	void OnClickButtonRX6x3();
	void OnClickButtonRX6x4();
	void OnClickButtonRX6x5();
	void OnClickButtonRX6x6();
	void OnClickButtonRX6x7();
	void OnClickButtonRX6x8();
	void OnClickButtonRX7x1();
	void OnClickButtonRX7x2();
	void OnClickButtonRX7x3();
	void OnClickButtonRX7x4();
	void OnClickButtonRX7x5();
	void OnClickButtonRX7x6();
	void OnClickButtonRX7x7();
	void OnClickButtonRX7x8();
	void OnClickButtonRX8x1();
	void OnClickButtonRX8x2();
	void OnClickButtonRX8x3();
	void OnClickButtonRX8x4();
	void OnClickButtonRX8x5();
	void OnClickButtonRX8x6();
	void OnClickButtonRX8x7();
	void OnClickButtonRX8x8();
	void OnTraitement(int,int,bool);
	void OnKillfocusEdit();

};
