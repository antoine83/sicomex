/* **************************************************************************
FICHIER :	Div_Tmp.cpp 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
**************************************************************************	*/

#include "stdafx.h"
#include <time.h>
#include <sys\timeb.h>
#include <stdio.h>

#include "Divers\div_tmp.h"

/* *************************************************************************
FONCTION : Renvoi temps

ROLE DE LA FONCTION
		Retourne une chaine de caractère au format JJ/MM/AA hh:mm:ss

REFERENCES EXTERNES :
		Aucune


REFERENCES INTERNES :
		CJournal

DONNEES EXTERNES
	char   *buf 		Buffer destinataire rempli la chaine formatée
						Ce buffer doit avoir été alloué dans la fonction 
						appelante avec au moins 17+1 caractères

	char*	resultat	chaine formaté

DONNEES INTERNES : 		voir fichier d'implémentation
**************************************************************************	*/
char* Renvoi_temps(char *buf)
{
	time_t	t;
	tm		*tps;

	time(&t);
	tps = localtime(&t);

	sprintf(buf,"%2.2d/%2.2d/%2.2d %2.2d:%2.2d:%2.2d",
			tps->tm_mday,tps->tm_mon+1,(tps->tm_year) % 100,
			tps->tm_hour,tps->tm_min,tps->tm_sec);

	return buf;
}

/* *************************************************************************
FONCTION : Renvoi_temps_milli

ROLE DE LA FONCTION
		Retourne une chaine de caractère au format JJ/MM/AA hh:mm:ss mmm

REFERENCES EXTERNES :
		Aucune


REFERENCES INTERNES :
		CJournal

DONNEES EXTERNES
	char   *buf 		Buffer destinataire rempli la chaine formatée
						Ce buffer doit avoir été alloué dans la fonction 
						appelante avec au moins 17+1 caractères

	char*	resultat	chaine formaté

DONNEES INTERNES : 		voir fichier d'implémentation
**************************************************************************	*/
char* Renvoi_temps_milli(char *buf)
{
    _timeb	tstruct;
	tm		*tps;

    _ftime( &tstruct);

	tps = localtime(&tstruct.time);
  	sprintf(buf,"%2.2d/%2.2d/%2.2d %2.2d:%2.2d:%2.2d %3.3d",
			tps->tm_mday,tps->tm_mon+1,(tps->tm_year) % 100,
			tps->tm_hour,tps->tm_min,tps->tm_sec,
			tstruct.millitm);

	return buf;
}

char* Conv_S_H(char *buf,int nb_sec)
{
	int		h,m,s;

	nb_sec = nb_sec % 86400;

	h = nb_sec / 3600;
	m = (nb_sec - 3600*h) / 60;
	s = nb_sec - 3600*h - 60*m; 

	sprintf(buf,"%2.2d:%2.2d:%2.2d",h,m,s);
	return buf;
}

int Conv_H_S(char *buf)
{
	int		h,m,s;

	sscanf(buf,"%2d:%2d:%2d",&h,&m,&s);
	return h*3600+ m*60 + s;
}

/* *************************************************************************
FONCTION : Renvoi_temps_milli

ROLE DE LA FONCTION
		Retourne une chaine de caractère au format JJ/MM/AA hh:mm:ss mmm

REFERENCES EXTERNES :
		Aucune


REFERENCES INTERNES :
		CJournal

DONNEES EXTERNES
	char   *buf 		Buffer destinataire rempli la chaine formatée
						Ce buffer doit avoir été alloué dans la fonction 
						appelante avec au moins 17+1 caractères

	char*	resultat	chaine formaté

DONNEES INTERNES : 		voir fichier d'implémentation
**************************************************************************	*/
int Nb_milli(char *buf)
{
    _timeb	tstruct;
	tm		*tps;

    _ftime( &tstruct);

	tps = localtime(&tstruct.time);
  	sprintf(buf,"%2.2d/%2.2d/%2.2d %2.2d:%2.2d:%2.2d %3.3d",
			tps->tm_mday,tps->tm_mon+1,(tps->tm_year) % 100,
			tps->tm_hour,tps->tm_min,tps->tm_sec,
			tstruct.millitm);

	return tps->tm_sec * 1000 + tstruct.millitm;
}

int		Puissance(int	x, int	y)
{
	int		i,iResult;

	iResult = 1;
	for (i=0 ; i<y ; i++)
	{
		iResult *= x;
	}
	return iResult;
}
