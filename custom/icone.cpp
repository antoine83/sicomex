/* **********************************************************************
FICHIER :	Icone.cpp					AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CIcone
***********************************************************************	*/
#include "stdafx.h"
#include "icone.h"

CIcone::CIcone(int typ,char *titre,BOOL etat,CEquip *lien)
{
	type_eqp = typ;
	strcpy(lib,titre);
	actif = etat;
	Eqp = lien;
}

CIcone::~CIcone()
{
}


int	CIcone::Equip() const
{
	return type_eqp;
}

void CIcone::ChangeLibel(char *titre)
{
	strcpy(lib,titre);
}

char* CIcone::Libel() const
{
	return (char*)lib;
}

BOOL CIcone::Actif() const
{
	return actif;
}

void CIcone::Active(BOOL etat)
{
	actif = etat;
	if(Eqp != NULL) Eqp->Afficher(etat);
}
