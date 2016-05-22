// DlgED42KeyDisplay.cpp : implementation file
//

#include "stdafx.h"
#include "sicomex.h"
#include "DlgED42KeyDisplay.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyDisplay dialog


CDlgED42KeyDisplay::CDlgED42KeyDisplay(CEquipED42 * eqp,CWnd* pParent /*=NULL*/)
	: CDialog(CDlgED42KeyDisplay::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlgED42KeyDisplay)
	m_kek = _T("");
	//}}AFX_DATA_INIT
	this->eqp = eqp;
}

CDlgED42KeyDisplay::~CDlgED42KeyDisplay()
{
	DestroyWindow();
}



void CDlgED42KeyDisplay::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlgED42KeyDisplay)
	DDX_Control(pDX, IDC_LIST_DATA, c_listData);
	DDX_Control(pDX, IDC_LIST_VOICE, c_listVoice);
	DDX_Text(pDX, IDC_EDIT_KEK, m_kek);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlgED42KeyDisplay, CDialog)
	//{{AFX_MSG_MAP(CDlgED42KeyDisplay)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlgED42KeyDisplay message handlers
BOOL CDlgED42KeyDisplay::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//Init tableau
	CString strText;
	char buffer[3]={0};

	//Affichage du quadrillage
	c_listData.SetExtendedStyle( LVS_EX_GRIDLINES );
	c_listVoice.SetExtendedStyle( LVS_EX_GRIDLINES );
	
	//Hearder
	strText.Format(TEXT("CVLoc"));
	c_listData.InsertColumn(0,strText,LVCFMT_CENTER,60);
	c_listVoice.InsertColumn(0,strText,LVCFMT_CENTER,60);

	strText.Format(TEXT("DC1"));
	c_listData.InsertColumn(1,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("DC2"));
	c_listData.InsertColumn(2,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("DC3"));
	c_listData.InsertColumn(3,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("DC4"));
	c_listData.InsertColumn(4,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("DC5"));
	c_listData.InsertColumn(5,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("DC6"));
	c_listData.InsertColumn(6,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("DC7"));
	c_listData.InsertColumn(7,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("DC8"));
	c_listData.InsertColumn(8,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("VC1"));
	c_listVoice.InsertColumn(1,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("VC2"));
	c_listVoice.InsertColumn(2,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("VC3"));
	c_listVoice.InsertColumn(3,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("VC4"));
	c_listVoice.InsertColumn(4,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("VC5"));
	c_listVoice.InsertColumn(5,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("VC6"));
	c_listVoice.InsertColumn(6,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("VC7"));
	c_listVoice.InsertColumn(7,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("VC8"));
	c_listVoice.InsertColumn(8,strText,LVCFMT_CENTER,50);

	strText.Format(TEXT("Update"));
	c_listData.InsertColumn(9,strText,LVCFMT_CENTER,65);
	c_listVoice.InsertColumn(9,strText,LVCFMT_CENTER,65);

	/*
	//Lignes
	for(int i=1;i<97;i++)
	{
		itoa(i,buffer,10);
		strText.Format(buffer);
		c_listData.InsertItem(i,strText);
		c_listVoice.InsertItem(i,strText);

	}
	*/
	
	return TRUE;
}

void CDlgED42KeyDisplay::LoadData() 
{
	char buffer[4]={0};
	CString strText;
	TKeyManagement keyManagement;

	//Pour KEK
	keyManagement = eqp->GetKeyManagement("0");
	if(keyManagement.kekLoaded == 0)
	{
		string date = "";
		itoa(keyManagement.days ,buffer,10);
		date.append(buffer);
		date.append(" / ");
		itoa(keyManagement.months ,buffer,10);
		date.append(buffer);
		date.append(" / ");
		itoa(keyManagement.years ,buffer,10);
		date.append(buffer);
		m_kek = date.c_str();
	}
	else
		m_kek = "XX / XX / XX";

	c_listData.DeleteAllItems();
	c_listVoice.DeleteAllItems();

	for(int i=1;i<97;i++)
	{
		itoa(i,buffer,10);
		keyManagement = eqp->GetKeyManagement(buffer);

		if (!eqp->GetCvChargement(&keyManagement))
		{
			strText.Format(buffer);
			c_listData.InsertItem(i,strText);
			c_listVoice.InsertItem(i,strText);

		for(int j=1;j<=8;j++)
		{
			switch(keyManagement.tag[j-1])
			{
			case 'V':				
				strText.Format(TEXT("X"));
				c_listVoice.SetItemText(c_listVoice.GetItemCount()-1,j,strText);
				break;
			case 'D':
				strText.Format(TEXT("X"));
				c_listData.SetItemText(c_listData.GetItemCount()-1,j,strText);
				break;
			case 'B':
				strText.Format(TEXT("X"));	
				c_listData.SetItemText(c_listData.GetItemCount()-1,j,strText);
				c_listVoice.SetItemText(c_listVoice.GetItemCount()-1,j,strText);
				break;
			default:
				strText.Format(TEXT(" "));	
				c_listData.SetItemText(c_listData.GetItemCount()-1,j,strText);
				c_listVoice.SetItemText(c_listVoice.GetItemCount()-1,j,strText);
			}
		}
		//Pour updateCount
		itoa(keyManagement.updateCount,buffer,10);
		strText.Format(buffer);
		c_listData.SetItemText(c_listData.GetItemCount()-1,c_listData.GetHeaderCtrl()->GetItemCount()-1,strText);
		c_listVoice.SetItemText(c_listVoice.GetItemCount()-1,c_listVoice.GetHeaderCtrl()->GetItemCount()-1,strText);

		}
	}

	UpdateData(FALSE);
}
