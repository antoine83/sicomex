/* **************************************************************************
FICHIER :	Prop_Std.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CProtoStd
***************************************************************************	*/

#include "stdafx.h"

#include "Comm\Prot_Std.h"
#include "Equip\EqpStd.h"
#include "divers\div_tmp.h"

const int 	DEBUT_TRAME = 0x7F;
const int 	TAILLE_TRAME = 3;

/* **************************************************************************
METHODE :		CProtoStd()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProtoStd::CProtoStd(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = TRUE;
}

/* **************************************************************************
METHODE :		~CProtoStd()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProtoStd::~CProtoStd()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProtoStd::EnvoyerTS(char *message)
{
	int		i,len_mes,iResult;

	len_mes = (int)strlen(message);	// Taille du message à envoyer
												// n  PC par tranche de 8 car
	if(len_mes > TAILLE_BUFFER)
		 return ERR_TAILLE_BUFFER;
	
	for(i=erreur_com.pas_debut ; i<3 ; i++)
	{
		iResult = ligne.EcritCar(message[i]);
		if(iResult < 0) return ERREUR_EXTERNE+iResult;
	}

	return iResult;  // nb d'octet transmis
}
/* **************************************************************************
METHODE :		TraiteTC()
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquitement
***************************************************************************	*/
int CProtoStd::TraiteTC(char *mes)
{
	int		iResult = ERR_CDE_INCONNUE;
	//int		valeur;
	char	reponse[TAILLE_PIPE_MESSAGE+1];

	strcpy(reponse,"");

	if(mes[0] == 0x07)
	{
		iResult = 0;		// Pas d'erreur
		reponse[0]=0x7F;
		reponse[1]=0x0;
		reponse[2]=0x0;
		EnvoyerTS(reponse);

		AjouterTS(NULL,STD_TEST);
		AjouterTS(NULL,STD_LOCAL);
		AjouterTS(NULL,STD_COMMUTATION);
		if(((CEquipStd*)eqp)->Baa() == 1)
		{
			AjouterTS(NULL,STD_XMIT_1);
			AjouterTS(NULL,STD_MAT_1);
		}
		else
		{
			AjouterTS(NULL,STD_XMIT_2);
			AjouterTS(NULL,STD_MAT_2);
		}
		AjouterTS(NULL,STD_SILENCE);

	}

	if(mes[0] == 0x70)
	{
		if(mes[1]>=0 && mes[1]<=0x0F)
		{
			reponse[0]=0x7F;
			reponse[1]=0x0;
			reponse[2]=0x0;
			EnvoyerTS(reponse);

			AjouterTS(NULL,CDE_TEMPO_SEQ);

			if(((CEquipStd*)eqp)->Avarie())
			{
				iResult = 0;
				AjouterTS(NULL,STD_AVARIE_REL);
			}

			if(((CEquipStd*)eqp)->AbsenceTension())
			{
				iResult = 0;
				AjouterTS(NULL,STD_AVARIE_TENSION);
			}

			if(((CEquipStd*)eqp)->NonHissage())
			{
				iResult = 0;
				AjouterTS(NULL,STD_AVARIE_HISSAGE);
			}
			if(((CEquipStd*)eqp)->NoXmit())
			{
				iResult = 0;
				AjouterTS(NULL,STD_AVARIE_NOXMIT);
			}
			if(((CEquipStd*)eqp)->Temperature())
			{
				iResult = 0;
				AjouterTS(NULL,STD_AVARIE_TEMP);
			}

			if(iResult != 0)		// Pas de defaut signalé
			{
				iResult = mes[1];
				((CEquipStd*)eqp)->ChangeAccorde((iResult+1)%2,FALSE);
				((CEquipStd*)eqp)->ChangeEmet((iResult/2)%2 + 1,FALSE);
				((CEquipStd*)eqp)->ChangeRecep((iResult/4)%2 + 1,FALSE);
				((CEquipStd*)eqp)->ChangeBaa((iResult/8)%2 + 1,FALSE);
		
				AjouterTS(NULL,STD_COMMUTATION);

				if((iResult/8)%2 + 1 == 1)
				{
					AjouterTS(NULL,STD_XMIT_1);
					AjouterTS(NULL,STD_MAT_1);
				}
				else
				{
					AjouterTS(NULL,STD_XMIT_2);
					AjouterTS(NULL,STD_MAT_2);
				}
				AjouterTS(NULL,STD_SILENCE);
			}
		}
		if(mes[1] == 0x10)
		{
			reponse[0]=0x7F;
			reponse[1]=0x0;
			reponse[2]=0x0;
			EnvoyerTS(reponse);

			AjouterTS(NULL,CDE_TEMPO_SEQ);

			iResult = mes[1];
			((CEquipStd*)eqp)->ChangeSilenceRadio(1,FALSE);

			AjouterTS(NULL,STD_SILENCE);
		}
				
		if(mes[1] == 0x11)
		{
			reponse[0]=0x7F;
			reponse[1]=0x0;
			reponse[2]=0x0;
			EnvoyerTS(reponse);

			AjouterTS(NULL,CDE_TEMPO_SEQ);

			iResult = mes[1];
			((CEquipStd*)eqp)->ChangeSilenceRadio(0,FALSE);

			AjouterTS(NULL,STD_SILENCE);
		}

		if(mes[1] == 0x70)
		{
			iResult = 0;
			reponse[0]=0x7F;
			reponse[1]=0x0;
			reponse[2]=0x0;
			EnvoyerTS(reponse);

			AjouterTS(NULL,CDE_TEMPO_SEQ);

			reponse[1]=0x70;

			if(		((CEquipStd*)eqp)->Avarie()
				||	((CEquipStd*)eqp)->AbsenceTension()
				||	((CEquipStd*)eqp)->NonHissage()
				||	((CEquipStd*)eqp)->NoXmit())
			{
				reponse[2]=0x01;	// a trouver un défaut
				AjouterTS(reponse,STD_TEST);	// Envoyer err code autotest
	
				if(((CEquipStd*)eqp)->Avarie())
				{
					AjouterTS(NULL,STD_AVARIE_REL);
				}

				if(((CEquipStd*)eqp)->AbsenceTension())
				{
					AjouterTS(NULL,STD_AVARIE_TENSION);
				}

				if(((CEquipStd*)eqp)->NonHissage())
				{
					AjouterTS(NULL,STD_AVARIE_HISSAGE);
				}
				if(((CEquipStd*)eqp)->NoXmit())
				{
					AjouterTS(NULL,STD_AVARIE_NOXMIT);
				}
			}
			else
			{
				reponse[2]=0x00;	// n'a pas trouver de défaut
				AjouterTS(reponse,STD_TEST);	// Envoyer err code autotest
			}
		}
	}
	if(iResult <0)
	{
		reponse[0]=0x7F;
		reponse[1]=0x1;	   		// Ordre incorrect
		reponse[2]=0x0;
		EnvoyerTS(reponse);
	}

	return iResult;
}

/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
int CProtoStd:: TraiteTS(int type_cde,char *reponse)
{
	int		iResult;

	strcpy(reponse,"");
	switch(type_cde)
	{
		case STD_TEST:
			iResult = ((CEquipStd*)eqp)->EtatIncorrect();
			reponse[0]=0x7F;
			reponse[1]=0x70;
			reponse[2]=iResult;

			if(((CEquipStd*)eqp)->Avarie())
				AjouterTS(NULL,STD_AVARIE_REL);

			if(((CEquipStd*)eqp)->AbsenceTension())
				AjouterTS(NULL,STD_AVARIE_TENSION);

			if(((CEquipStd*)eqp)->NonHissage())
				AjouterTS(NULL,STD_AVARIE_HISSAGE);

			if(((CEquipStd*)eqp)->NoXmit())
				AjouterTS(NULL,STD_AVARIE_NOXMIT);

			if(((CEquipStd*)eqp)->Temperature())
				AjouterTS(NULL,STD_AVARIE_TEMP);

			break;

		case STD_COMMUTATION:
			iResult = 	((CEquipStd*)eqp)->Accorde()
					+	(((CEquipStd*)eqp)->Emet() - 1)*2
					+	(((CEquipStd*)eqp)->Recep() - 1)*4
					+	(((CEquipStd*)eqp)->Baa() - 1)*8;
			reponse[0]=0x7F;
			reponse[1]=0x07;
			reponse[2]=iResult;
			break;

		case STD_SILENCE:
			iResult = 	((CEquipStd*)eqp)->SilenceRadio();
			reponse[0]=0x7F;
			reponse[1]=0x07;
			reponse[2]=0x10+(iResult+1) % 2;
			break;

		case STD_AVARIE_REL:
			iResult = 	((CEquipStd*)eqp)->Avarie();
			reponse[0]=0x7F;
			reponse[1]=0x3C;
			reponse[2]=iResult;
			break;

		case STD_AVARIE_TENSION:
			iResult = 0;
			reponse[0]=0x7F;
			reponse[1]=0x1C;
			reponse[2]=0;
			break;

		case STD_AVARIE_HISSAGE:
			iResult = 0;
			reponse[0]=0x7F;
			reponse[1]=0x1C;
			reponse[2]=1;
			break;

		case STD_AVARIE_NOXMIT:
			iResult = 0;
			reponse[0]=0x7F;
			reponse[1]=0x1C;
			reponse[2]=2;
			break;

		case STD_LOCAL:
			iResult = 	((CEquipStd*)eqp)->Local();
			reponse[0]=0x7F;
			reponse[1]=0x07;
			reponse[2]=0x35+iResult;
			break;

		case STD_XMIT_1:
			iResult = 	((CEquipStd*)eqp)->Xmit_1();
			reponse[0]=0x7F;
			reponse[1]=0x07;
			reponse[2]=0x21+(iResult*2);
			break;

		case STD_XMIT_2:
			iResult = 	((CEquipStd*)eqp)->Xmit_2();
			reponse[0]=0x7F;
			reponse[1]=0x07;
			reponse[2]=0x22+(iResult*2);
			break;

		case STD_MAT_1:
			iResult = 	((CEquipStd*)eqp)->Mat_1();
			reponse[0]=0x7F;
			reponse[1]=0x07;
			reponse[2]=0x33-(iResult*2);
			break;

		case STD_MAT_2:
			iResult = 	((CEquipStd*)eqp)->Mat_2();
			reponse[0]=0x7F;
			reponse[1]=0x07;
			reponse[2]=0x34-(iResult*2);
			break;

		case STD_AVARIE_TEMP:
			iResult = 0;
			reponse[0]=0x7F;
			reponse[1]=0x1C;
			reponse[2]=3;
			break;

		default:
			iResult = ERR_CDE_INCONNUE;
			break;
	}

	if(iResult>=0) return 3; // longeur message pour affichage hexa
	return iResult;
}

/* **************************************************************************
METHODE :		RecevoirTC()
TRAITEMENT:		Réceptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProtoStd::RecevoirTC(char *message,int nb_car)
{
	char	buf[TAILLE_BUFFER+1];
	int		i,iResult;

	if(nb_car > TAILLE_BUFFER) return ERR_TAILLE_BUFFER;

	i=0;
	while(i<TAILLE_TRAME)
	{
		iResult = ligne.Lire(buf+i,1);
		if(iResult < 0) return ERREUR_EXTERNE+iResult;
		if(iResult == 0) return ERREUR_TIMEOUT;
		if(buf[i]==DEBUT_TRAME && i!=0)
		{
			buf[0] = DEBUT_TRAME;
			i=0;
		}
		i++;
	}

	if(!ExtraitUtile(buf,message,&iResult)) 
		return ERR_NON_CONFORME;			// Message non conforme

	return iResult;
}

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Retourne toujours TRUE car n'attend pas d'acquitement
***************************************************************************	*/
BOOL CProtoStd::ValideAcquittement(int type_cde,char *buf)
{
	return TRUE;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Retournes une chaine vide car aucun caratère de controle
				n'est demandé
***************************************************************************	*/
char* CProtoStd::ControleTrame(char *message,char *octet_controle)
{
	strcpy(octet_controle,"");
	return octet_controle;
}

/* **************************************************************************
METHODE :		ExtraitUtile()
TRAITEMENT:		Extrait la partie utile d'une trame de télécommande
***************************************************************************	*/
BOOL CProtoStd::ExtraitUtile(char *buf,char *message,int *long_utile)
{

	if(buf[0] != DEBUT_TRAME)
		return FALSE;

	message[0]=buf[1];
	message[1]=buf[2];
	message[2]=0;		// Force une fin de chaine pour journal

	*long_utile = 2;

	return TRUE;
}
