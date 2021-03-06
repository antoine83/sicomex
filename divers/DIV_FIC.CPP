/* **************************************************************************
FICHIER :	Div_fic.cpp 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
**************************************************************************	*/

#include "stdafx.h"

#include <stdio.h>
#include "Divers\div_fic.h"

extern 	char glob_CHEMIN[];

/* *************************************************************************
FONCTION : Lire_fichier

ROLE DE LA FONCTION
		Lit nb_car caract�res � partir du d�but d'un fichier (r�f�renc� par 
		son HANDLE)

REFERENCES EXTERNES :	Aucune

REFERENCES INTERNES	:	biblioth�que

DONNEES EXTERNES
		HANDLE *hld 	Handle du fichier � lire
		char   *buf 	Buffer destinataire rempli par les octet lus
		int    *nb_car	Taille du buffer destinataire

		int	resultat	n = nombre d'octet lu
						-1 pour une erreur de lecture
						-2 si la taille du fichier est > nb_car demand�

DONNEES INTERNES : 		voir impl�mentation
**************************************************************************	*/
int Lire_fichier(HANDLE hdl,char *buf,int nb_car)
{
	int 	nb_car_lu=0;
	DWORD	taille,t2;
	
	taille = GetFileSize(hdl,&t2);				// taille du fichier
	t2 = SetFilePointer(hdl,0,NULL,FILE_BEGIN); //debut de fichier

	if(ReadFile(hdl,(LPVOID) buf,nb_car,(DWORD*) &nb_car_lu,NULL))
	{
		if (((DWORD) nb_car) < taille) return -2;
		else return nb_car_lu;
	}
	else
		return -1;
}

/* *************************************************************************
FONCTION : Recup_fichier

ROLE DE LA FONCTION
		Ouvre le fichier de nom "fichier" et charge les informations 
		qu'il contient dans le buffer pass� en parametre

REFERENCES EXTERNES :	Aucune

REFERENCES INTERNES	:	biblioth�que

DONNEES EXTERNES
		char   *fichier:	nom du fichier (Chemin d'acc�s)
		char   *reponse:	Buffer destinataire de la reponse 
							(Dimensionner � TAILLE_MAX_MESSAGE caracteres)

		int	resultat	n = nombre d'octet lu
						-1 pour une erreur de lecture
						-2 si la taille du fichier est > TAILLE_MAX_MESSAGE

DONNEES INTERNES : 		voir impl�mentation
**************************************************************************	*/
int Recup_fichier(const char *fichier,char *reponse)
{
	int		iResult;
	HANDLE	hFichier;
	char	nom_fichier[256];
	char	*pcResult;
	
	pcResult = strstr((char *)fichier,":\\");
	if(pcResult == NULL) sprintf(nom_fichier,"%s\\%s",glob_CHEMIN,fichier);
	else strcpy(nom_fichier,fichier);

	hFichier = CreateFile(nom_fichier,GENERIC_READ,FILE_SHARE_READ,
			NULL,OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFichier == INVALID_HANDLE_VALUE)
	{
		printf("////* Erreur d'ouverture du fichier %s\n",fichier);
		return ERR_OUVERT_HANDLE;
	}

	iResult = Lire_fichier(hFichier,reponse,TAILLE_MAX_MESSAGE);
	if(iResult>=0) reponse[iResult]=0;
	else MessageBox (NULL,"Erreur en lecture du fichier","Erreur",NULL);
	CloseHandle(hFichier);
   return(iResult);

}

/* *************************************************************************
FONCTION : Stocker_fichier

ROLE DE LA FONCTION
		Remplace le contenu du fichier par le buffer pass� en param�tre

REFERENCES EXTERNES :	Aucune

REFERENCES INTERNES	:	biblioth�que

DONNEES EXTERNES
	char   *fichier:	Nom du fichier de stockage
	char   *message:	Contenu � stocker

	int	resultat 		: 0 = Ecriture correcte
						:-1 pour une erreur de stockage

DONNEES INTERNES : 		voir impl�mentation
**************************************************************************	*/
int Stocker_fichier(char *fichier,char *message)
{
	int		iResult;
	HANDLE	hFichier;
	DWORD	nb_car_ecrit;

	hFichier = CreateFile(fichier,GENERIC_WRITE,FILE_SHARE_READ,
			NULL,CREATE_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFichier == INVALID_HANDLE_VALUE)
	{
		printf("////* Erreur d'ouverture du fichier %s\n",fichier);
		return ERR_OUVERT_HANDLE;
	}

	iResult = 0;
	if(!WriteFile(hFichier,(LPVOID) message,(int)strlen(message),
			&nb_car_ecrit,NULL))
		iResult = -1;
  
	CloseHandle(hFichier);

	return iResult;
}

/* *************************************************************************
FONCTION : Append_fichier

ROLE DE LA FONCTION
		Ajoute les carct�res du buffer pass� en param�tre � un fichier

REFERENCES EXTERNES :	Aucune

REFERENCES INTERNES	:	biblioth�que

DONNEES EXTERNES
	char   *fichier:	Nom du fichier de stockage
	char   *message:	Buffer � ajouter en fin du fichier

	int	resultat 		: 0 = Ecriture correcte
						:-1 pour une erreur de stockage

DONNEES INTERNES : 		voir impl�mentation
**************************************************************************	*/
int Append_fichier(char *fichier,char *message)
{
	int		iResult;
	HANDLE	hFichier;
	DWORD	nb_car_ecrit;

	hFichier = CreateFile(fichier,GENERIC_WRITE,FILE_SHARE_READ,
			NULL,OPEN_ALWAYS,FILE_ATTRIBUTE_NORMAL,NULL);

	if (hFichier == INVALID_HANDLE_VALUE)
	{
		printf("////* Erreur d'ouverture du fichier %s\n",fichier);
		return ERR_OUVERT_HANDLE;
	}

	// positionnement en fin de fichier
	SetFilePointer(hFichier,0,(LPLONG)NULL,FILE_END);

	iResult = 0;
	if(!WriteFile(hFichier,(LPVOID) message,(int)strlen(message),
			&nb_car_ecrit,NULL))
		iResult = -1;
  
	CloseHandle(hFichier);
	return iResult;
}

/* *************************************************************************
FONCTION : Extrait_ligne

ROLE DE LA FONCTION
		Extrait une ligne de commande d'un buffer.
		Une ligne commence par le caract�re sp�cial CHAR_CDE
		et termine par un des caract�re CHAR_LF, CHAR_CR ou 0 (fin de chaine)

REFERENCES EXTERNES :	Aucune

REFERENCES INTERNES	:	biblioth�que

DONNEES EXTERNES
	char  *fichier:		Contenu du fichier
	char *ligne:		buffer destinataire recevant la ligne

	int	resultat : 		0 si la chaine a �t� trouv�
						-1 sinon

DONNEES INTERNES : 		voir impl�mentation
**************************************************************************	*/
int Extrait_ligne(char *fichier,char *cle,char *ligne,int nb_car_max)
{
	char 	*pcResult;			// pointeur sur une partie de config
	int		i = 0;
	
	pcResult = strstr(fichier,cle);
	if(pcResult == NULL) return -1; 
	strncpy(ligne,pcResult,nb_car_max);ligne[nb_car_max]=0;

	while(ligne[i]!=CHAR_LF && ligne[i]!=CHAR_CR && ligne[i]!=0)
		i++;
	ligne[i]=0;					// force un fin de chaine

	return 0;
}

/* *************************************************************************
FONCTION : Extrait_parametre

ROLE DE LA FONCTION
		Extrait une commande d'une ligne de commande (commande + commentaire)
		Une ligne commence par le caract�re sp�cial CHAR_CDE
		et termine par un des caract�re CHAR_COM, CHAR_LF, CHAR_CR ou 0

REFERENCES EXTERNES : 	Aucune

REFERENCES INTERNES	:	biblioth�que

DONNEES EXTERNES
	char *ligne:		ligne
	char *param:		Commande extraite	
	int	nb_car_max: 	Nombre de caract�re maximum de la commande

	int	resultat 	: 0 si la chaine a �t� trouv�
					:-1 sinon

DONNEES INTERNES : 		voir fichier d'impl�mentation
**************************************************************************	*/
int Extrait_parametre(char *ligne,char *cle,char *param,int nb_car_max)
{
	char 	*pcResult;			// pointeur sur une partie de config
	int		i = 0;
	
	pcResult = strstr(ligne,cle);
	if(pcResult == NULL) return -1; 
	strncpy(param,pcResult,nb_car_max);param[nb_car_max]=0;

	while(param[i]!=CHAR_SEPA && param[i]!=CHAR_LF && param[i]!=CHAR_CR 
		&& param[i]!=0)
		i++;					// Separateur, [LF], [CR], Fin de message
	param[i]=0;					// force un fin de chaine

	return 0;
}



