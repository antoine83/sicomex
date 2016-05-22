/* **********************************************************************
FICHIER :	Port.h					AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/
#ifndef _CPORT
#define _CPORT
/* **********************************************************************
NOM DU COMPOSANT : 		CPort

ROLE DU COMPOSANT :		Gestion des port série

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :
	CProtocole			Classe de base des protocole de communication
***********************************************************************	*/
const int DELAI_TIME_OUT=		10;		// 0,1 sec en inter-caractère
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
	int		num_ligne;		// numéro de port
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
TRAITEMENT:		Teste si le port a été ouvert
***********************************************************************	*/
	BOOL PortOuvert() const;

/* **********************************************************************
METHODE :		NumPort()
TRAITEMENT:		Retourne le numéro de port utilisé par l'objet
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
TRAITEMENT:		Fermeture et libération du port
***********************************************************************	*/
    int Fermeture ();

/* **********************************************************************
METHODE :		Purge()
TRAITEMENT:		vide les buffers d' I/O associé au port
***********************************************************************	*/
	int Purge ();

/* **********************************************************************
METHODE :		Ecrire()
TRAITEMENT:		Envoi d'un chaine de caractères sur le port série si la 
                port a bien été initialisé.
				Si la procédure abouti, elle retourne le nombre de carac
                écrit, sinon un code erreur négatif
***********************************************************************	*/
	int Ecrire(char *buf);
	int Ecrire(char *buf, int nbCar);
	
/* **********************************************************************
METHODE :		EcrireCar()
TRAITEMENT:		Envoi un caractères sur le port série. Si la procédure 
                abouti, elle retourne le nombre de caractère écrit, 
                sinon un code erreur négatif
***********************************************************************	*/
	int EcritCar(const char car);

/* **********************************************************************
METHODE :		Lire()
TRAITEMENT:		Lecture des octets sur le port de communication selon le 
			    time out défini dans Ouverture_port().
			    Les octets sont stockés dans buf, et le nombre d'octets
			    lus est retourné par la fonction. En cas d'échec, un code
                négatif est renvoyé
***********************************************************************	*/
	virtual int Lire(char *buf,const int nb_car);

/* **********************************************************************
METHODE :		Etat()
TRAITEMENT:		Compare l'etat du port avec celui passé en paramètre 
                (CTS,DSR,RING, RLSD)
***********************************************************************	*/
	int Etat(DWORD etat);
};
												
#endif
