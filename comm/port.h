/* **********************************************************************
FICHIER :	Port.h					AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _CPORT
#define _CPORT
/* **********************************************************************
NOM DU COMPOSANT : 		CPort

ROLE DU COMPOSANT :		Gestion des port s�rie

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :
	CProtocole			Classe de base des protocole de communication
***********************************************************************	*/
const int DELAI_TIME_OUT=		10;		// 0,1 sec en inter-caract�re
const int DELAI_TIME_OUT_1=		50;		// 0,5 sec pour recevoir le 1er caractere
const int DELAI_TIME_OUT_2=		0;		// delai de recption entre 2 car

const int ERR_OUVERT_HANDLE=	-2; 	// Erreur d'ouverture des fichiers
const int ERR_OUVERTURE_PORT=	-3;
const int ERR_FERMETURE_PORT=	-4;
const int ERR_PURGE_PORT=		-5;
const int ERR_ECRIRE_PORT=		-6;
const int ERR_LIRE_PORT=		-7;
const int ERR_ETAT_PORT=		-8;
const int ERR_ATTENTE_EVENT=	-9;
const int ERR_LIGNE_FERMEE=		-10;	// CreateFile n'avait pas abouti

/* **********************************************************************
DONNEES EXTERNES :		aucune
***********************************************************************	*/

class CPort
{
/* **********************************************************************
DONNEES INTERNES
***********************************************************************	*/
private:
	int		num_ligne;		// num�ro de port
	BOOL	ouverte;		// ligne exploitable V/F
	HANDLE	hcom;			// HANDLE du port

/* **********************************************************************
METHODE :		CPort()
TRAITEMENT:		Constuit l'objet mais n'ouvre pas le port 
***********************************************************************	*/
public:
	CPort();

/* **********************************************************************
METHODE :		~CPort()
TRAITEMENT:		Destructeur de l'objet
***********************************************************************	*/
    ~CPort();

/* **********************************************************************
METHODE :		PortOuvert()
TRAITEMENT:		Teste si le port a �t� ouvert
***********************************************************************	*/
	BOOL PortOuvert() const;

/* **********************************************************************
METHODE :		NumPort()
TRAITEMENT:		Retourne le num�ro de port utilis� par l'objet
***********************************************************************	*/
	int NumPort() const;

/* **********************************************************************
METHODE :		Ouverture()
TRAITEMENT:		Ouverture et initialisation du port
***********************************************************************	*/
    int Ouverture (const int numero,const int vitesse,const int nb_bit,
    					const int stop_bit,const int parite);
		
/* **********************************************************************
METHODE :		Fermeture()
TRAITEMENT:		Fermeture et lib�ration du port
***********************************************************************	*/
    int Fermeture ();

/* **********************************************************************
METHODE :		Purge()
TRAITEMENT:		vide les buffers d' I/O associ� au port
***********************************************************************	*/
	int Purge ();

/* **********************************************************************
METHODE :		Ecrire()
TRAITEMENT:		Envoi d'un chaine de caract�res sur le port s�rie si la 
                port a bien �t� initialis�.
				Si la proc�dure abouti, elle retourne le nombre de carac
                �crit, sinon un code erreur n�gatif
***********************************************************************	*/
	int Ecrire(char *buf);
	int Ecrire(char *buf, int nbCar);
	
/* **********************************************************************
METHODE :		EcrireCar()
TRAITEMENT:		Envoi un caract�res sur le port s�rie. Si la proc�dure 
                abouti, elle retourne le nombre de caract�re �crit, 
                sinon un code erreur n�gatif
***********************************************************************	*/
	int EcritCar(const char car);

/* **********************************************************************
METHODE :		Lire()
TRAITEMENT:		Lecture des octets sur le port de communication selon le 
			    time out d�fini dans Ouverture_port().
			    Les octets sont stock�s dans buf, et le nombre d'octets
			    lus est retourn� par la fonction. En cas d'�chec, un code
                n�gatif est renvoy�
***********************************************************************	*/
	virtual int Lire(char *buf,const int nb_car);

/* **********************************************************************
METHODE :		Etat()
TRAITEMENT:		Compare l'etat du port avec celui pass� en param�tre 
                (CTS,DSR,RING, RLSD)
***********************************************************************	*/
	int Etat(DWORD etat);
};
												
#endif
