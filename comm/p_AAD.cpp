// p_AAD.cpp: implementation of the CProtoAAD class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#include "Comm\p_AAD.h"
#include "Equip\EqpAAD.h"
#include "divers\div_tmp.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

const int SEPARE_TRAME	= 0x0D;	// Separateur de commande 13
const int FIN_TRAME		= 0x1A;	// Fin de trame 26

/* **************************************************************************
METHODE :		CProtoAAD()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProtoAAD::CProtoAAD(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;
}

/* **************************************************************************
METHODE :		~CProtoTemp()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProtoAAD::~CProtoAAD()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProtoAAD::EnvoyerTS(char *message)
{
	char	buf[TAILLE_BUFFER+2];
	int		len_mes, iResult;

	len_mes = (int)strlen(message);
	if(len_mes > TAILLE_BUFFER)
		 return ERR_TAILLE_BUFFER;

	memset(buf, 0, sizeof(buf));
	sprintf(buf, "%s%c", message, FIN_TRAME);

	iResult = ligne.Ecrire(buf);

	if(iResult < 0)
		return ERREUR_EXTERNE+iResult;

	// nb d'octet transmis
	return iResult;
}
/* **************************************************************************
METHODE :		TraiteTC(char *mes)
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquittement
***************************************************************************	*/
int CProtoAAD::TraiteTC(char *mes)
{
	int	 no_elt, no_voie;
	int	 flagADA, taille;					//int	 i, j, flagADA, taille;   //2009-11-27
	char reponse[TAILLE_PIPE_MESSAGE+1];

	strcpy(reponse,"");

	// Reception de la requete d'interrogation de la matrice par SCREOF
	if(mes[0] == 'S')
	{
		((CEquipAAD*)eqp)->EtatMatrice();
		return 0;
	}

	// Reception de la requete d'interrogation du materiel par FCREOF
	if(mes[0] == 'F')
	{
		((CEquipAAD*)eqp)->EtatMateriel();
		return 0;
	}

	// Reception de la requete d'initialisation de la matrice par RCREOF
	if(mes[0] == 'R')
	{
		((CEquipAAD*)eqp)->ResetMatrice();
		return 0;
	}

	// Modification de la matrice ET réponse du FCREOF
	taille = strlen((const char *) mes);
	flagADA = 0;
	while(flagADA != -1 && taille>=0)
	{
		if(mes[flagADA+0] == 'A')
		{
			if(isdigit(mes[flagADA+1]))
			{
				if(mes[flagADA+2] == ',')
				{
					// Modification de la matrice
					if(mes[flagADA+3] == 'E')
					{
						if(isdigit(mes[flagADA+4]))
						{
							if(isdigit(mes[flagADA+5]))
							{
								no_elt  = mes[flagADA+1]-48;
								no_voie = (mes[flagADA+4]-48) * 10;
								no_voie = no_voie + mes[flagADA+5]-48;
								if( ((CEquipAAD*)eqp)->ChgtEtatMatrice(no_elt-1, no_voie-1) == FALSE)
								{
									return ERR_NON_CONFORME;
								}
								if(mes[flagADA+6] == SEPARE_TRAME && mes[flagADA+7] == FIN_TRAME)
								{
									flagADA = -1;
									return 0;
								}
								flagADA = flagADA +7;
								taille = taille -7;
							}
							else
							{
								no_elt  = mes[flagADA+1]-48;
								no_voie = mes[flagADA+4]-48;
								if( ((CEquipAAD*)eqp)->ChgtEtatMatrice(no_elt-1, no_voie-1) == FALSE)
								{
									return ERR_NON_CONFORME;
								}
								if(mes[flagADA+5] == SEPARE_TRAME && mes[flagADA+6] == FIN_TRAME)
								{
									flagADA = -1;
									return 0;
								}
								flagADA = flagADA +6;
								taille = taille -6;
							}
						}
						else
							return ERR_NON_CONFORME;
					}
					else
						return ERR_NON_CONFORME;
				}
				else
					return ERR_NON_CONFORME;
			}
			else
				return ERR_NON_CONFORME;
		}
		else
			return ERR_NON_CONFORME;
	}
	return ERR_CDE_INCONNUE;
}

/* **************************************************************************
METHODE :		TraiteTS(int type_cde,char *reponse)
TRAITEMENT:		Formate une TS en fonction en recuperant les etats internes
				de l'equipement
***************************************************************************	*/
int CProtoAAD:: TraiteTS(int type_cde,char *reponse)
{
	strcpy(reponse, "");

	return ERR_CDE_INCONNUE;
}

/* **************************************************************************
METHODE :		RecevoirTC(char *message,int nb_car)
TRAITEMENT:		Receptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProtoAAD::RecevoirTC(char *message,int nb_car)
{
	/*char buf[TAILLE_BUFFER+1];
	int	 len_mes, iResult;
	char cF[4], cR[4], cS[4], cA[7];

	if(nb_car > TAILLE_BUFFER)
	{
		return ERR_TAILLE_BUFFER;
	}

	iResult = ligne.Lire(buf,8);
	if(iResult < 0)
	{
		return ERREUR_EXTERNE+iResult;
	}
	if(iResult == 0)
	{
		return ERREUR_TIMEOUT;
	}

	len_mes = (int)strlen(buf);
	if(buf[0] == 'F')
	{
		if(buf[1] == SEPARE_TRAME && buf[2] == FIN_TRAME)
		{
			strcpy(message, "F");
			return 1;
		}
	}
	if(buf[0] == 'R')
	{
		if(buf[1] == SEPARE_TRAME && buf[2] == FIN_TRAME)
		{
			strcpy(message, "R");
			return 1;
		}
	}
	if(buf[0] == 'S')
	{
		if(buf[1] == SEPARE_TRAME && buf[2] == FIN_TRAME)
		{
			strcpy(message, "S");
			return 1;
		}
	}
	if(buf[0] == 'A')
	{
		if(buf[len_mes-2] == SEPARE_TRAME && buf[len_mes-1] == FIN_TRAME)
		{
			strcpy(message, buf);
			return 1;
		}
	}

	// Message non conforme
	/*if(!ExtraitUtile(buf,message,&iResult))
	{
		return ERR_NON_CONFORME;
	}*/

	char buf[TAILLE_BUFFER+1];
	int	 i,iResult;

	if(nb_car > TAILLE_BUFFER)
	{
		return ERR_TAILLE_BUFFER;
	}

	strcpy(message, "");

	i=0;
	while(i<nb_car)
	{
		iResult = ligne.Lire(buf+i,1);
		if(iResult < 0)
		{
			return ERREUR_EXTERNE+iResult;
		}
		if(iResult == 0)
		{
			return ERREUR_TIMEOUT;
		}
		if(buf[i] == 'F' && i!=0)
		{
			buf[0] = 'F';
			sprintf(message, "F");
			i=0;
			break;
		}
		if(buf[i] == 'R' && i!=0)
		{
			buf[0] = 'R';
			sprintf(message, "R");
			i=0;
			break;
		}
		if(buf[i] == 'S' && i!=0)
		{
			buf[0] = 'S';
			sprintf(message, "S");
			i=0;
			break;
		}
		/*if(buf[i] == 'A' && i==0)
		{
			buf[0] = 'A';
			//i=0;
		}*/
		/*if(buf[i]==SEPARE_TRAME)
		{
			buf[0] = SEPARE_TRAME;
			continue;
		}*/
		if(buf[i]==FIN_TRAME)
			break;
		sprintf(message, "%s%c", message, buf[i]);
		i++;
	}

	return iResult;

}

/* **************************************************************************
METHODE :		ValideAcquittement(int type_cde,char *buf)
TRAITEMENT:		Attend un message d'acquittement du type de commande precedement
				envoye comme TS Maitre
***************************************************************************	*/
BOOL CProtoAAD::ValideAcquittement(int type_cde,char *buf)
{
	BOOL bResult = TRUE;

	return bResult;
}

/* **************************************************************************
METHODE :		ControleTrame(char *message,char *octet_controle)
TRAITEMENT:		Genere les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
char* CProtoAAD::ControleTrame(char *message,char *octet_controle)
{
	int	 i,len_mes;
	char pc;

	strcpy(octet_controle,"");

	if(!erreur_com.controle_parite)
	{
		return octet_controle;
	}

	len_mes = (int)strlen(message);

	pc = 0;
	i=len_mes-1;
	while(i>=0)
	{
		pc = pc ^ message[i];
		// caract précedent = debut de tranche
		if((i) % 8 == 0)
		{
			if(pc < 64)
			{
				pc += 64;
			}
			strncat(octet_controle,&pc,1);
			pc = 0;
		}
		i--;
	}
	return octet_controle;
}

/* **************************************************************************
METHODE :		ExtraitUtile(char *buf,char *message,int *long_utile)
TRAITEMENT:		Extrait les octets utiles
***************************************************************************	*/
BOOL CProtoAAD::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	char octet_controle[8];
	int	 len_mes,nb_tranche;

	len_mes = (int)strlen(buf);

	if(buf[len_mes -2] != SEPARE_TRAME && buf[len_mes -1] != FIN_TRAME)
	{
		return FALSE;
	}

	// 1 tranche = 8 caractère utile + 1 PC sans oublier d'oter les
	// caracteres de debut et de fin de trame
	if(erreur_com.controle_parite)
	{
		nb_tranche = (len_mes-2)/9 + !((len_mes-2)%9 == 0);
	}
	// Aucun caractere de parite
	else
	{
		nb_tranche = 0;
	}

	*long_utile = len_mes - 2 - nb_tranche;
	strcpy(message,"");
	strncat(message,buf+1,*long_utile);

	ControleTrame(message,octet_controle);
	if(strncmp(octet_controle,buf+1+(len_mes - 2 - nb_tranche),nb_tranche))
	{
		return FALSE;
	}

	return TRUE;
}
