/* **********************************************************************
FICHIER :	Div_tmp.h	 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************
NOM DU COMPOSANT : 		Div_temps 	

ROLE DU COMPOSANT :		Contient des procedures de gestion de temps

REFERENCES EXTERNES :	Aucune

REFERENCES INTERNES :	bibliothèque

FONCTIONS :
	Renvoi_temps: 		Retourne une chaine de caractère au format 
						JJ/MM/AA hh:mm:ss

	Renvoi_temps_milli:	Retourne une chaine de caractère au format 
						JJ/MM/AA hh:mm:ss nnn

	Nb_milli :			Retourne le nombre de seconde et de ses milliemes
						en instantané

	Conv_S_H :			Converti un nombre de seconde au format HH:MM:SS

	Conv_H_S : 			Converti une heuer au format HH:MM:SS en nombre de
						seconde
***********************************************************************	*/

#ifndef _DIV_TEMPS
#define _DIV_TEMPS

char* Renvoi_temps(char	*temps);
char* Renvoi_temps_milli(char	*temps);

int   Nb_milli(char	*temps);

char* Conv_S_H(char *buf,int nb_sec);
int Conv_H_S(char *buf);

int	Puissance(int	x, int	y);

#endif
