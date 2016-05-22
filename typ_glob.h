/*************************************************************************
FICHIER :	typ_glob.h			 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _TYPE_GLOBAL
#define _TYPE_GLOBAL

const int	SANS_PARITE		=0;
const int 	EVEN_PARITE		=2;
const int 	ODD_PARITE		=1;

const int	UN_STOP			=0;
const int	DEUX_STOP		=2;
const int	DEMI_STOP		=1;			// 1,5 bit de stop

typedef struct				
{
	int		num_port;					

	int		vitesse;					// vitesse de transmission
	int		data;						// nb de bit de donnée
	int		stop;						// nb bit de stop
	int		parite;						// parite
	BOOL 	control_parite;				
} t_format;								// Format de transmission

typedef struct
{
	BOOL	pas_debut;
	BOOL	pas_fin;
	BOOL	controle_parite;
	BOOL	cde_inconnue;
	BOOL	pas_de_reponse;

	int		retard;				// retard dans la reponse en millisecode
}	t_ComErreur;				// Gestion des erreurs de parite


#endif
