/* **************************************************************************
FICHIER :	Div_fic.h	 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***************************************************************************	*/

/* **************************************************************************
NOM DU COMPOSANT : 		Div_fichier 	

ROLE DU COMPOSANT :		Contient des procedures de gestion de fichier

REFERENCES EXTERNES :	Aucune

REFERENCES INTERNES :	bibliothèque

FONCTIONS :	
	Lire_fichier: 			Lit nb_car caractères à partir du début d'un 
							fichier (référencé par son HANDLE)

 	Recup_fichier:	 		Stocke le contenu d'un fichier dans un buffer

	Stocker_fichier:		Remplace le contenu du fichier par un buffer

	Append_fichier:			Ajoute les caractères du buffer à un fichier
							
	Extrait_ligne:			Extrait une ligne de commande d'un buffer 

	Extrait_commande:		Extrait une commande d'un ligne de commande 

	Extrait_commentaire:	Extrait un commentaire d'un ligne de commande 
***************************************************************************	*/

#ifndef _DIV_FICHIER
#define _DIV_FICHIER

#define TAILLE_MAX_MESSAGE	20*1024
#define TAILLE_MAX_LIGNE	512

#define CHAR_LF				10		// Line Feed
#define CHAR_CR				13		// Cariage Return
#define CHAR_SEPA			32		// Separateur

#define ERR_OUVERT_HANDLE	-1

int Lire_fichier(HANDLE hdl,char *buf,int nb_car);
int Recup_fichier(const char *fichier,char *reponse);
int Stocker_fichier(char *fichier,char *message);
int Append_fichier(char *fichier,char *message);

int Extrait_ligne(char *fichier,char *cle,char *ligne,int nb_car_max);
int Extrait_parametre(char *ligne,char *cle, char *param,int nb_car_max);


#endif
