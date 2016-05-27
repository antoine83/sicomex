/* ******************************************************************
FICHIER :	Port.cpp		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CPort (gestion des port série)
*********************************************************************/
#include "stdafx.h"
#include <stdio.h>

#include "comm\Port.h"

/* **********************************************************************
METHODE :		CPort()
TRAITEMENT:		Constuit l'objet mais n'ouvre pas le port 
***********************************************************************	*/
CPort::CPort()
{
	ouverte = FALSE;
}

/* **********************************************************************
METHODE :		~CPort()
TRAITEMENT:		Destructeur de l'objet
***********************************************************************	*/
CPort::~CPort()
{
   	Fermeture();
}

/* **********************************************************************
METHODE :		PortOuvert()
TRAITEMENT:		Teste si le port a été ouvert
***********************************************************************	*/
BOOL CPort::PortOuvert() const
{
	return ouverte;
}

/* **********************************************************************
METHODE :		NumPort()
TRAITEMENT:		Retourne le numéro de port utilisé par l'objet
***********************************************************************	*/
int CPort::NumPort() const
{
	return num_ligne;
}

/* **********************************************************************
METHODE :		Ouverture()
TRAITEMENT:		Ouverture et initialisation du port
				* 	Dimensionne les buffers I/O
				* 	Parametre le format de transmission (vitesse, parité,
					controle de flux, ...)
				* 	Paramétrage des TimeOut écriture/lecture
				*	Purge des buffers I/O
***********************************************************************	*/
int CPort::Ouverture(const int numero,const int vitesse,const int nb_bit,
							const int stop_bit,const int parite)
{
	char	nom_port[14];
	int		iResult;
	DCB		dcb;				// structure de configuration du port
	COMMTIMEOUTS	timeout;	// Structure de gestion du time out


	num_ligne = numero;			// numero du port utilisé

	sprintf(nom_port,"\\\\.\\COM%d",num_ligne);

// Ouverture du port
	
	hcom = CreateFile(nom_port,
		GENERIC_READ | GENERIC_WRITE,
		0,			   					// Accès exclusif
		NULL,							// pas d'attribut de sécurité
		OPEN_EXISTING, 					// Le port doit exister
		0,								// I/O limité dans le temps
		NULL);	   						// NULL pour un péripherique COM
		
		

	/*
	   hcom = CreateFile( nom_port,
				GENERIC_READ | GENERIC_WRITE,
				0,
				NULL,
				OPEN_EXISTING,
				FILE_FLAG_OVERLAPPED,
				NULL );
	*/

	if (hcom == INVALID_HANDLE_VALUE)
		return ERR_OUVERT_HANDLE;

	ouverte = TRUE;

// Dimensionnement des buffer I/O
	if (!SetupComm(hcom,1200,1200))
		return ERR_OUVERTURE_PORT;

// purge des buffer I/O
	iResult = Purge();						

// Paramétrage du time out
	if (!GetCommTimeouts(hcom,&timeout))	// ancien timeout -> dcb
		return ERR_OUVERTURE_PORT;

	timeout.ReadIntervalTimeout = DELAI_TIME_OUT*4;		// inter-caractere
	timeout.ReadTotalTimeoutMultiplier = DELAI_TIME_OUT_2*4;
	timeout.ReadTotalTimeoutConstant = DELAI_TIME_OUT_1*4;// timeout 1er car

	timeout.WriteTotalTimeoutMultiplier = DELAI_TIME_OUT*4;

	if (!SetCommTimeouts(hcom,&timeout))	// nouveau timout <- timeout
		return ERR_OUVERTURE_PORT;

// Initialisation du port 
	if (!GetCommState(hcom,&dcb))	// ancienne configuration -> dcb
		return ERR_OUVERTURE_PORT;

	dcb.BaudRate = vitesse;
	dcb.ByteSize = nb_bit;
	dcb.Parity = parite;
	dcb.StopBits = stop_bit;

	dcb.fDsrSensitivity = FALSE;

	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_ENABLE;			 

	dcb.fOutxCtsFlow = FALSE;

 	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
  
	dcb.fInX = dcb.fOutX = FALSE ;
   	dcb.XonLim = 100 ;
   	dcb.XoffLim = 100 ;

   	dcb.fBinary = TRUE ;
   	dcb.fParity = TRUE ;

	if (!SetCommState(hcom,&dcb))
	{
		iResult = GetLastError();
		// nouvelle config <- dcb
		return ERR_OUVERTURE_PORT;
	}


// Force les etats RTS
//	if (!EscapeCommFunction(hcom,SETRTS))
	if (!EscapeCommFunction(hcom,SETDTR))
		return ERR_OUVERTURE_PORT;
	return 0;
}


/* **********************************************************************
METHODE :		Fermeture()
TRAITEMENT:		Fermeture et libération du port
***********************************************************************	*/
int CPort::Fermeture()
{
	if (!ouverte) return ERR_LIGNE_FERMEE;

// Fermeture du port
	if (!CloseHandle(hcom)) return ERR_FERMETURE_PORT;
	ouverte = FALSE;
	return 0;
}

/* **********************************************************************
METHODE :		Purge()
TRAITEMENT:		vide les buffers d' I/O associé au port
***********************************************************************	*/
int CPort::Purge()
{
	OutputDebugString("Dans : CPort::Purge() !\n");

	if (!ouverte) return ERR_LIGNE_FERMEE;

	if (!PurgeComm(hcom, PURGE_TXABORT | PURGE_RXABORT | PURGE_TXCLEAR | PURGE_RXCLEAR))
		return ERR_PURGE_PORT;
	return 0;
}

/* **********************************************************************
METHODE :		Ecrire()
TRAITEMENT:		Envoi d'un chaine de caractères sur le port série.
				Si la procédure abouti, elle retourne le nombre de carac
                écrit, sinon un code erreur négatif
***********************************************************************	*/
int CPort::Ecrire(char *buf)
{
	BOOL	bResult;
	int 	nb_car_ecrit;

	if (!ouverte) return ERR_LIGNE_FERMEE;

	bResult = WriteFile(hcom,buf,strlen(buf),(DWORD*) &nb_car_ecrit,NULL);

	if (bResult && nb_car_ecrit) return nb_car_ecrit;
	else return ERR_ECRIRE_PORT;	
}

/* **********************************************************************
METHODE :		Ecrire()
TRAITEMENT:		Envoi d'un chaine de caractères sur le port série.
				Si la procédure abouti, elle retourne le nombre de carac
                écrit, sinon un code erreur négatif
***********************************************************************	*/
int CPort::Ecrire(char *buf,int nbCar)
{
	BOOL	bResult;
	int 	nb_car_ecrit;

	if (!ouverte) return ERR_LIGNE_FERMEE;

	bResult = WriteFile(hcom,buf,nbCar,(DWORD*) &nb_car_ecrit,NULL);

	if (bResult && nb_car_ecrit) return nb_car_ecrit;
	else return ERR_ECRIRE_PORT;	
}

/* **********************************************************************
METHODE :		EcrireCar()
TRAITEMENT:		Envoi un caractères sur le port série. Si la procédure 
                abouti, elle retourne le nombre de caractère écrit, 
                sinon un code erreur négatif
***********************************************************************	*/
int CPort::EcritCar(const char car)
{
BOOL	bResult;
int 	nb_car_ecrit;

	if (!ouverte) return ERR_LIGNE_FERMEE;

	bResult = WriteFile(hcom,&car,1,(DWORD*) &nb_car_ecrit,NULL);
	if (bResult && nb_car_ecrit) return nb_car_ecrit;
	else return ERR_ECRIRE_PORT;	
}
 
/* **********************************************************************
METHODE :		Lire()
TRAITEMENT:		Lecture des octets sur le port de communication selon le 
			    time out défini dans Ouverture_port().
			    Les octets sont stockés dans buf, et le nombre d'octets
			    lus est retourné par la fonction. En cas d'échec, un code
                négatif est renvoyé
***********************************************************************	*/
int CPort::Lire(char *buf,const int nb_car)
{
int 	nb_car_lu=0;

	if (!ouverte) return ERR_LIGNE_FERMEE;

	if (ReadFile(hcom,buf,nb_car,(DWORD*) &nb_car_lu,NULL))
	{
		buf[nb_car_lu]=0;
		return nb_car_lu;
	}
	else
		return ERR_LIRE_PORT;
}

/* **********************************************************************
METHODE :		Etat()
TRAITEMENT:		Compare l'etat du port avec celui passé en paramètre 
                (CTS,DSR,RING, RLSD)
***********************************************************************	*/
int CPort::Etat(DWORD etat)
{
	DWORD	status;

	if (!ouverte) return ERR_LIGNE_FERMEE;

	if(GetCommModemStatus(hcom,&status))
	{
		if (status & etat) return status;
	}
	return ERR_ETAT_PORT;
}

