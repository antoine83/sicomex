/*************************************************************************
FICHIER :	Table.h					 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
*************************************************************************/
#ifndef _CTABLE
#define _CTABLE
/* **************************************************************************
NOM DU COMPOSANT : 		CTable

ROLE DU COMPOSANT :		Gestion d'une liste de commande à envoyer

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	aucune
***************************************************************************	*/

const int  TAILLE_PIPE_MAX = 100;	 	// Dimension de la table tournante
const int  TAILLE_PIPE_MESSAGE=512;		// Taille des messages

/* **************************************************************************
DONNEES EXTERNES : aucune
***************************************************************************	*/

typedef struct				
{
	char	message[TAILLE_PIPE_MESSAGE];
	int		type_commande;
} t_message;					// Gestion des messages

class CTable
{
/* **************************************************************************
DONNEES INTERNES
***************************************************************************	*/
private:
	t_message	file[TAILLE_PIPE_MAX];
	int			premier;			// position du premier
	int			nombre;				// nombre de message
	CRITICAL_SECTION	crit;		// Section critique


/* **************************************************************************
METHODE :		CTable()
TRAITEMENT:		Crée la liste avec 0 élément
***************************************************************************	*/
public:
	CTable()
	{
		premier = 0;
		nombre = 0;
		InitializeCriticalSection(&crit);
	}

/* **************************************************************************
METHODE :		~CTache()
TRAITEMENT:		Destructeur
***************************************************************************	*/
	~CTable()
	{
		DeleteCriticalSection(&crit);
	}

/* **************************************************************************
METHODE :		Est vide
TRAITEMENT:		vérifie si la liste est vide
***************************************************************************	*/
	int EstNonVide() const;
	
						// La table contient au moins
/* **************************************************************************
METHODE :		Ajouter
TRAITEMENT:		Ajoute un message à la liste
***************************************************************************	*/
	BOOL Ajouter(char *mes,int type_cde);

/* **************************************************************************
METHODE :		Retirer
TRAITEMENT:		Retire un message de la liste
***************************************************************************	*/
	BOOL Retirer(char *mes,int *type_cde);

/* **************************************************************************
METHODE :		Lire
TRAITEMENT:		Reccupère les iformation de la index ieme position
***************************************************************************	*/
	BOOL Lire(int index,char *mes,int *type_cde) const;

/* **************************************************************************
METHODE :		Supprime
TRAITEMENT:		Supprime les ligne à la index ieme position
***************************************************************************	*/
	BOOL Supprime(int index);
};

#endif
