/* **************************************************************************
FICHIER :	Table.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CTable
***************************************************************************	*/
#include <stdio.h>

#include "stdafx.h"

#include "Table.h"

/* **************************************************************************
METHODE :		Est vide
TRAITEMENT:		vérifie si la liste est vide
***************************************************************************	*/
int CTable::EstNonVide() const
{
	int		iResult;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
	  	iResult = nombre;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return iResult;
}

/*************************************************************************
Ajouter : Ajoute 1 élément dans la table tournante et retourne TRUE
		ou FALSE si la table est pleine
*************************************************************************/
BOOL CTable::Ajouter(char *mes,int type_cde)
{
	int	indice;

	EnterCriticalSection(&crit);
	  	indice = (premier+nombre) % TAILLE_PIPE_MAX;
		if(nombre==TAILLE_PIPE_MAX)
		{
			LeaveCriticalSection(&crit);
			return FALSE;
		}

		if(mes != NULL) strcpy(file[indice].message,mes);
		else 
		strcpy(file[indice].message,"");

		file[indice].type_commande = type_cde;

  		nombre++;
	LeaveCriticalSection(&crit);

	return TRUE;
}

/*************************************************************************
Retirer : Retire 1 élément dans la table tournante et retourne TRUE
		ou FALSE si la table est vide
*************************************************************************/
BOOL CTable::Retirer(char *mes,int *type_cde)
{
	int	indice;

	EnterCriticalSection(&crit);
		if(nombre==0)
		{
			LeaveCriticalSection(&crit);
			return FALSE;
		}

  		indice = premier;

		strcpy(mes,file[indice].message);
		*type_cde = file[indice].type_commande;

	  	premier = (indice+1) % TAILLE_PIPE_MAX;

		nombre--;

	LeaveCriticalSection(&crit);

	return TRUE;
}

/* **************************************************************************
METHODE :		Lire
TRAITEMENT:		Reccupère les iformation de la index ieme position
***************************************************************************	*/
BOOL CTable::Lire(int index,char *mes,int *type_cde) const
{
	int	indice;

	EnterCriticalSection((CRITICAL_SECTION*)&crit);
		if(index > nombre-1 || index < 0)		// Hors limite
		{
			LeaveCriticalSection((CRITICAL_SECTION*)&crit);
			return FALSE;
		}

	  	indice = (premier+index) % TAILLE_PIPE_MAX;
	
		strcpy(mes,file[indice].message);
		*type_cde = file[indice].type_commande;
	LeaveCriticalSection((CRITICAL_SECTION*)&crit);

	return TRUE;
}

/* **************************************************************************
METHODE :		Supprime
TRAITEMENT:		Supprime les ligne à la index ieme position
***************************************************************************	*/
BOOL CTable::Supprime(int index)
{
	int	i,indice;

	EnterCriticalSection(&crit);
		if(index > nombre-1 || index < 0)		// Hors limite
		{
			LeaveCriticalSection(&crit);
			return FALSE;
		}

		for(i = index+1 ; i< nombre ; i++)
		{
 		  	indice = (premier+i) % TAILLE_PIPE_MAX;
	
			strcpy(file[indice-1].message,file[indice].message);
			file[indice-1].type_commande = file[indice].type_commande;
		}
		nombre--;

	LeaveCriticalSection(&crit);

	return TRUE;
	
}

