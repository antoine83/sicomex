/* **************************************************************************
FICHIER :	P_1241.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CProto1241
***************************************************************************	*/

#include "stdafx.h"
#include "stdlib.h"

#include "Comm\p_1241.h"
#include "Equip\Eqp1241.h"
#include "divers\div_tmp.h"

const int 	DEBUT_TRAME = 0xD;
const int 	FIN_TRAME 	= 0xA;

/* **************************************************************************
METHODE :		CProtoRecHF()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProtoRecHF::CProtoRecHF(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;

	indice_veille 		= 0;
	indice_maintien 	= 0;
	indice_frequence 	= 0;
	indice_vitesse 		= 0;

	lecture_canal		= 0;
}

/* **************************************************************************
METHODE :		~CProtoRecHF()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProtoRecHF::~CProtoRecHF()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProtoRecHF::EnvoyerTS(char *message)
{
	int		len_mes,iResult;
	int		nb_car_enveloppe;		// Nombre de caractère envlopant le message

	char	buf[TAILLE_BUFFER+1];
	char	octet_controle[8];

	len_mes = (int)strlen(message);	// Taille du message à envoyer
	nb_car_enveloppe = 1 + 1 + len_mes/9 + 1; 	// Debut Trame + Fin Trame
												// n  PC par tranche de 8 car
	if(len_mes+nb_car_enveloppe > TAILLE_BUFFER)
		 return ERR_TAILLE_BUFFER;
	
	buf[0] = DEBUT_TRAME;
	strcpy(buf+1,message);
	strcat(buf,ControleTrame(message,octet_controle));
	iResult = (int)strlen(buf);
	buf[iResult] = FIN_TRAME;
	buf[iResult+1]=0;				// Force la fin de chaine

	if(erreur_com.pas_debut) buf[0]=0x20;
	if(erreur_com.pas_fin) buf[iResult]=0;
	
	iResult = ligne.Ecrire(buf);
	if(iResult < 0) return ERREUR_EXTERNE+iResult;

	return iResult;  // nb d'octet transmis
}

/* **************************************************************************
METHODE :		TraiteTC()
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquitement
***************************************************************************	*/
int CProtoRecHF::TraiteTC(char *mes)
{
	int		iResult = 0;
	int		cResult = 0;
	int		valeur;
	long	long_valeur;
	long	lResult = 0;
	char	reponse[TAILLE_PIPE_MESSAGE+1];

	int 	old_bp5;

	strcpy(reponse,"");

	if(strcmp(mes,"XXB")==0)		// Sortie mode SPIN
	{
		iResult = ((CEquip1241*)eqp)->ChangeSpin(0,TRUE);
		
		strcpy(reponse,"xxB");
		EnvoyerTS(reponse);
		return 0;
	}


	iResult = ((CEquip1241*)eqp)->Spin();
	if(iResult)	return ERR_PAS_ACQUITTE;

	if(strcmp(mes,"XX@")==0)		// Passage en mode SPIN
	{
		iResult = ((CEquip1241*)eqp)->ChangeSpin(1,FALSE);
		
		strcpy(reponse,"xx@");
		EnvoyerTS(reponse);
		return 0;
	}

	if(strcmp(mes,"LOC")==0)		// Passage en Local
	{
		iResult = ((CEquip1241*)eqp)->ChangeLocal(0,FALSE);
		strcpy(reponse,"loc");
		EnvoyerTS(reponse);
		return 0;
	}

	if(strcmp(mes,"RMT")==0)		// Passage en commande
	{
		iResult = ((CEquip1241*)eqp)->ChangeLocal(1,FALSE);
		
		strcpy(reponse,"rmt");
		EnvoyerTS(reponse);

		AjouterTS(NULL,REC_1241_MODE_RECEP);
		AjouterTS(NULL,REC_1241_OPTION_REC);
		AjouterTS(NULL,REC_1241_FREQUENCE);
		AjouterTS(NULL,REC_1241_FILTRE_FI);
		AjouterTS(NULL,REC_1241_ATTENUATEUR);
		AjouterTS(NULL,REC_1241_CAG);
		AjouterTS(NULL,REC_1241_REJECTEUR);
		AjouterTS(NULL,REC_1241_SQUELCH);
		AjouterTS(NULL,REC_1241_BFO);
		AjouterTS(NULL,REC_1241_NIVEAU_HF);
		AjouterTS(NULL,REC_1241_SEUIL_COR);
		return 0;
	}
	else
		if(((CEquip1241*)eqp)->Local() == 0) return ERR_PAS_ACQUITTE;

	switch(mes[0])
	{
		case 'M':
			valeur = atoi(mes+1);
			iResult = ((CEquip1241*)eqp)->ChangeModeRecep(0,valeur,FALSE);

			// Renvoyer le mode même en cas d'echec de la modif
			sprintf(reponse,"m%d",abs(iResult));
			EnvoyerTS(reponse);

			cResult = ((CEquip1241*)eqp)->ChangeCanal(0,TRUE);
			//ChangeCanalLecture(0);
			ChangeCanalLecture(cResult);

			if(iResult >= 0)				// Modification acceptée
			{

				if(iResult == 5)		// Mode F1
				{
					AjouterTS(NULL,REC_1241_SHIFT);

					AjouterTS(NULL,REC_1241_SENS_MANIP);
				}

				AjouterTS(NULL,REC_1241_FILTRE_FI);

				AjouterTS(NULL,REC_1241_BFO);

				AjouterTS(NULL,REC_1241_CAG);
			}

			break;

		case 'A':
			valeur = atoi(mes+1);
			iResult = ((CEquip1241*)eqp)->ChangeAttenuateur(0,valeur,FALSE);
			if(iResult >= 0)				// Modification acceptée Autre TS
			{
				ChangeCanalLecture(0);
	  			sprintf(reponse,"a%d",abs(iResult));
				EnvoyerTS(reponse);
			}
			break;
		
		case 'K':
			old_bp5 = ((CEquip1241*)eqp)->FiltreFI(0) / 5;
			valeur = atoi(mes+1);
			iResult = ((CEquip1241*)eqp)->ChangeFiltreFI(0,valeur,FALSE);

			// Renvoyer le mode même en cas d'echec de la modif
  			sprintf(reponse,"k%d",abs(iResult));
			EnvoyerTS(reponse);
		
			if(iResult >= 0)				// Modification acceptée
			{
				ChangeCanalLecture(0);
				if((iResult/5) != old_bp5) AjouterTS(NULL,REC_1241_FREQUENCE);
			}
			break;

		case 'G':
			switch(mes[1])
			{
				case '#':
					valeur = 0;
					break;
				case '<':
					valeur = 1;
					break;
				case '=':
					valeur = 2;
					break;
				case '>':
					valeur = 3;
					break;
				case '!':
					valeur = 4;
					break;
			}
			iResult = ((CEquip1241*)eqp)->ChangeCag(0,valeur,FALSE);
			ChangeCanalLecture(0);

			// Renvoyer le mode même en cas d'echec de la modif
			sprintf(reponse,"g%c",mes[1]);
			EnvoyerTS(reponse);
			break;

		case 'Q':
			valeur = atoi(mes+1);
			iResult = ((CEquip1241*)eqp)->ChangeSquelch(0,valeur,FALSE);
		
			if(iResult >= 0)				// Modification acceptée Autre TS
			{
				ChangeCanalLecture(0);
	  			sprintf(reponse,"q%d",abs(iResult));
				EnvoyerTS(reponse);
			}
			break;

		case 'N':
			valeur = atoi(mes+1);
			iResult = ((CEquip1241*)eqp)->ChangeSensManip(0,valeur,FALSE);

			if(iResult >= 0)				// Modification acceptée Autre TS
			{
				ChangeCanalLecture(0);
	  			sprintf(reponse,"n%d",abs(iResult));
				EnvoyerTS(reponse);
			}
			break;

		case 'E':
			valeur = atoi(mes+1);
			iResult = ((CEquip1241*)eqp)->ChangeShift(0,valeur,FALSE);

			if(iResult >= 0)				// Modification acceptée Autre TS
			{
				ChangeCanalLecture(0);
	  			sprintf(reponse,"e%d",abs(iResult));
				EnvoyerTS(reponse);
			}
			break;

		case 'F':
			long_valeur = atol(mes+1) * Puissance(10,8-(int)strlen(mes+1));

			lResult = ((CEquip1241*)eqp)->ChangeFrequence(0,long_valeur,FALSE);
  
			if(lResult >= 0)				// Modification acceptée Autre TS
			{
				cResult = ((CEquip1241*)eqp)->ChangeCanal(0,TRUE);
				//ChangeCanalLecture(0);
				ChangeCanalLecture(cResult);
				TraiteTS(REC_1241_FREQUENCE,reponse);
				reponse[0]='f';
				EnvoyerTS(reponse);
			}
			else iResult = ERR_PAS_ACQUITTE;
			break;

		case 'B':
			valeur = atoi(mes+1) * 10;
			if((int)strlen(mes+1) != 3+(valeur<0)) //Nb car incorrect
			{
				iResult = ERR_PAS_ACQUITTE;
				break;
			}

			valeur = atoi(mes+1) * 10;
			iResult = ((CEquip1241*)eqp)->ChangeBfo(0,valeur,FALSE);
			
			if(abs(iResult) <= 7990)
			{
				ChangeCanalLecture(0);

				sprintf(reponse,"b%3.3d",iResult/10);
				EnvoyerTS(reponse);
				iResult = 0;			// Acquitement correct
			}
			else
				iResult = ERR_PAS_ACQUITTE;

			break;

		case 'R':
			if(mes[1]=='#')
			{
				iResult = ((CEquip1241*)eqp)->ChangeAvecRejecteur(0,FALSE);
				strcpy(reponse,"r#");
				EnvoyerTS(reponse);
			}
			else
			{
				if(((CEquip1241*)eqp)->ChangeAvecRejecteur(1,FALSE))	// Avec rejecteur
				{
					valeur = atoi(mes+1) * 10;
					if((int)strlen(mes+1) != 3+(valeur<0)) //Nb car incorrect
					{
						iResult = ERR_PAS_ACQUITTE;
						break;
					}

					iResult = ((CEquip1241*)eqp)->ChangeRejecteur(valeur,FALSE);
					if(abs(iResult) <= 7990)
					{
						sprintf(reponse,"r%3.3d",iResult/10);
						EnvoyerTS(reponse);
						iResult = 0;			// Acquitement correct
					}
				}
				else
					iResult = ERR_PAS_ACQUITTE;

			}
			break;

		case 'I':
		case 'J':
			if(mes[1]<0x20 || mes[1]>0x3F)		// Incrément non conforme
			{
				iResult = ERR_PAS_ACQUITTE;
				break;
			}

			switch(mes[1])
 			{
				case '=':
					long_valeur = 12000000;	// 12 MHz
					break;
				case '>':
					long_valeur = 15000000;	// 15 MHz
					break;
				case '?':
					long_valeur = 17000000;	// 17 MHz
					break;
				default:
					switch((mes[1]-0x20) %4)
					{
						case 0:
							long_valeur = 1 * Puissance(10,(mes[1]-0x20)/4);
							break;
						case 1:
							long_valeur = 2 * Puissance(10,(mes[1]-0x20)/4);
							break;
						case 2:
							long_valeur = 5 * Puissance(10,(mes[1]-0x20)/4);
							break;
						case 3:
							long_valeur = 7 * Puissance(10,(mes[1]-0x20)/4);
							break;
					}
					break;
			}

			if(mes[0]=='J') long_valeur *= -1;

			lResult = ((CEquip1241*)eqp)->IncrementeFrequence(long_valeur,FALSE);
	
			ChangeCanalLecture(0);

			// Réponse systématique
			TraiteTS(REC_1241_FREQUENCE,reponse);
			reponse[0]='f';
			EnvoyerTS(reponse);
			break;

		case 'H':
			valeur = (mes[1]-0x30)*16 + mes[2]-0x30;
			iResult = ((CEquip1241*)eqp)->ChangeGainHF(0,valeur,FALSE);

			ChangeCanalLecture(0);

			// Renvoyer le mode même en cas d'echec de la modif
			sprintf(reponse,"h%C%C",abs(iResult)/16 + 0x30,(abs(iResult)%16) + 0x30);
			EnvoyerTS(reponse);
		
			if(iResult >= 0)				// Modification acceptée
			{
			}
			break;

		case 'V':
			if(mes[1] == '#' || mes[1] == '=')
			{
				TraiteTS(REC_1241_MESUREUR,reponse);
				reponse[0]='v';
				EnvoyerTS(reponse);

				((CEquip1241*)eqp)->ChangeAutoMesureur(mes[1] == '=');

			}

			break;

		case 'U':
			valeur = (mes[1]-0x30)*16 + (mes[2]-0x30);
			iResult = ((CEquip1241*)eqp)->ChangeCorSquelch(valeur,FALSE);

			// Renvoyer le mode même en cas d'echec de la modif
			sprintf(reponse,"u%C%C",abs(iResult)/16 + 0x30,(abs(iResult)%16) + 0x30);
			EnvoyerTS(reponse);
		
			if(iResult >= 0)				// Modification acceptée
			{
				AjouterTS(NULL,REC_1241_SEUIL_COR);
			}
			break;

		case 'L':
			if(mes[1] == '#' || mes[1] == '=')
			{
				TraiteTS(REC_1241_CENTRAGE_F1,reponse);
				reponse[0]='l';
				EnvoyerTS(reponse);

				((CEquip1241*)eqp)->ChangeAutoCentrageF1(mes[1] == '=');
			}
			break;

		case 'P':
			iResult = 0;
			if(mes[1] != '#' && mes[1] != '=')
			{
				valeur = atoi(mes+1);
				iResult = ((CEquip1241*)eqp)->ChangeCanal(valeur,FALSE);
			}

			if(iResult >= 0)				// Modification acceptée Autre TS
			{
				ChangeCanalLecture(iResult);

				TraiteTS(REC_1241_CANAL_POSI,reponse);
				reponse[0]='p';
				EnvoyerTS(reponse);
			}
			break;

		case 'C':
			iResult = 0;
			strncpy(reponse,mes+1,2);reponse[2]=0;
			valeur = atoi(reponse);
			if(valeur<1 || valeur >99) return ERR_CDE_INCONNUE;

			ChangeCanalLecture(valeur);

			if((int)strlen(mes+1)>5)		// canal + parametre : Modif canal
			{
				strcpy(reponse,mes+3);

				// Seuil
				if((int)strlen(reponse)<2) break;		// pas d'info Seuil
				valeur = atoi(reponse+(int)strlen(reponse)-2);
				reponse[(int)strlen(reponse)-2] = 0;
				iResult = ((CEquip1241*)eqp)->ChangeMesureur(CanalLecture(),valeur,FALSE);

				// Gain
				if((int)strlen(reponse)<2) break;		// pas d'info Gain
				valeur = (reponse[(int)strlen(reponse)-2]-0x30)*16 + reponse[(int)strlen(reponse)-1]-0x30;
				reponse[(int)strlen(reponse)-2] = 0;
				iResult = ((CEquip1241*)eqp)->ChangeGainHF(CanalLecture(),valeur,FALSE);

				// BFO
				if((int)strlen(reponse)<3) break;		// pas d'info BFO
				valeur = atoi(reponse+(int)strlen(reponse)-3)*10;
				reponse[(int)strlen(reponse)-3] = 0;

				if(reponse[strlen(reponse)-1] == '-')
				{
					valeur *= -1;
					reponse[(int)strlen(reponse)-1] = 0;
				}
				iResult = ((CEquip1241*)eqp)->ChangeBfo(CanalLecture(),valeur,FALSE);
				iResult = 0;

				// Squelch
				if((int)strlen(reponse)<1) break;		// pas d'info Squelch
				valeur = atoi(reponse+(int)strlen(reponse)-1);
				reponse[(int)strlen(reponse)-1] = 0;
				iResult = ((CEquip1241*)eqp)->ChangeSquelch(CanalLecture(),valeur,FALSE);

				// caractere réservé
				if((int)strlen(reponse)<1) break;		// pas de carac reserve
				reponse[(int)strlen(reponse)-1] = 0;

				// Cag
				if((int)strlen(reponse)<1) break;		// pas de CAG
				switch(reponse[(int)strlen(reponse)-1])
				{
					case '<':
						valeur = 1;
						break;
					case '=':
						valeur = 2;
						break;
					case '>':
						valeur = 3;
						break;
					default: 				// case '#':
						valeur = 0;
						break;
				}
				iResult = ((CEquip1241*)eqp)->ChangeCag(0,valeur,FALSE);
				reponse[(int)strlen(reponse)-1] = 0;

				// Attenuateur
				if((int)strlen(reponse)<1) break;		// pas d'attenuateur
				valeur = atoi(reponse+(int)strlen(reponse)-1);
				reponse[(int)strlen(reponse)-1] = 0;
				iResult = ((CEquip1241*)eqp)->ChangeAttenuateur(CanalLecture(),valeur,FALSE);

				// Filtre
				if((int)strlen(reponse)<1) break;		// pas de filtre
				valeur = atoi(reponse+(int)strlen(reponse)-1);
				reponse[(int)strlen(reponse)-1] = 0;
				iResult = ((CEquip1241*)eqp)->ChangeFiltreFI(CanalLecture(),valeur,FALSE);


				// telegraphie
				if((int)strlen(reponse)<1) break;		// pas de Mode
				if(reponse[(int)strlen(reponse)-1] >= 60)
				{
					if((int)strlen(reponse)<1) break;
					valeur = reponse[(int)strlen(reponse)-1]-12;
					reponse[(int)strlen(reponse)-1] = 0;
					iResult = ((CEquip1241*)eqp)->ChangeSensManip(CanalLecture(),valeur,FALSE);

					// Shift
					if((int)strlen(reponse)<1) break;
					valeur = atoi(reponse+(int)strlen(reponse)-1);
					reponse[(int)strlen(reponse)-1] = 0;
					iResult = ((CEquip1241*)eqp)->ChangeShift(CanalLecture(),valeur,FALSE);
				}

				// Mode
				if((int)strlen(reponse)<1) break;		// pas de Mode
				valeur = atoi(reponse+(int)strlen(reponse)-1);
				reponse[(int)strlen(reponse)-1] = 0;
				iResult = ((CEquip1241*)eqp)->ChangeModeRecep(CanalLecture(),valeur,FALSE);

				// Frequence
				if((int)strlen(reponse)<1) break;		// pas de frequence

				long_valeur = atol(reponse) * Puissance(10,8-(int)strlen(reponse));
				iResult = ((CEquip1241*)eqp)->ChangeFrequence(CanalLecture(),long_valeur,FALSE);
			}

			if(iResult >= 0)				// Modification acceptée Autre TS
			{
				TraiteTS(REC_1241_CANAL_LECT,reponse);
				reponse[0]='c';
				EnvoyerTS(reponse);
			}
			break;

		case 'W':
			switch(mes[1])
			{
				case '0':		// demande de positionnement
					valeur = atoi(mes+2);
					iResult = ((CEquip1241*)eqp)->Veille(valeur);

					if(iResult<0) break;		// paramètre incorrect

					if(iResult == 0)			// Canal de veille annulé
						sprintf(reponse,"w1%2.2d00",valeur);
					else						// Positionnement
					{
						indice_veille = valeur;
						iResult = ((CEquip1241*)eqp)->ChangeCanal(iResult,FALSE);
						TraiteTS(REC_1241_VEILLE_POSI,reponse);
						reponse[0]='w';
					}
					EnvoyerTS(reponse);
					break;

				case '1':		// demande de lecture
					valeur = atoi(mes+2);
					iResult = ((CEquip1241*)eqp)->Veille(valeur);

					if(iResult<0) break;		// paramètre incorrect

					if(iResult == 0)			// Canal de veille annulé
						sprintf(reponse,"w1%2.2d00",valeur);
					else						// Positionnement
					{
						indice_veille = valeur;
						iResult = ((CEquip1241*)eqp)->ChangeCanal(iResult,FALSE);
						TraiteTS(REC_1241_VEILLE_LECT,reponse);
						reponse[0]='w';
					}

					EnvoyerTS(reponse);
					break;

				case '2':		// Modification d'un canal de veille
					if((int)strlen(mes+2)!=4)
					{
						iResult = ERR_PAS_ACQUITTE;
						break;
					}
					strncpy(reponse,mes+2,2);reponse[2]=0; // indice veille
					valeur = atoi(reponse);
					strncpy(reponse,mes+4,2);reponse[2]=0; // n° Canal
					iResult = atoi(reponse);

					iResult = ((CEquip1241*)eqp)->ChangeVeille(valeur,iResult);
					if(iResult>=0)
					{
						indice_veille = valeur;
						sprintf(reponse,"w2%2.2d%2.2d",valeur,iResult);
   						EnvoyerTS(reponse);
					}
					break;

				case '6':		// Définition du cycle
					if((int)strlen(mes+2)!=2)
					{
						iResult = ERR_PAS_ACQUITTE;
						break;
					}
					strncpy(reponse,mes+2,2);reponse[2]=0; // indice veille
					valeur = atoi(reponse);
					if(valeur<1 || valeur>99)
					{
						iResult = ERR_PAS_ACQUITTE;
						break;
					}

					sprintf(reponse,"w6%2.2d",valeur);
					EnvoyerTS(reponse);

					iResult = 0;
					break;

				case '8':		// Temps de maintien
					iResult = mes[2]-0x3C;		// degre
					if(iResult<0 || iResult>2)
					{
						iResult = ERR_PAS_ACQUITTE;
 						break;
					}

					indice_maintien = iResult;
					
					if((int)strlen(mes+2)>1)	// demande de modification
					{
						valeur = atoi(mes+3);
						iResult = ((CEquip1241*)eqp)->ChangeTempsMaintien(indice_maintien,valeur);
					}

					if(iResult>=0)				// Pas d'erreur sur modification
					{
						TraiteTS(REC_1241_TEMPS_MAINT,reponse);
						reponse[0]='w';
						EnvoyerTS(reponse);
					}
					break;

				case '3':		// demande de positionnement
					valeur = atoi(mes+2);
					lResult = ((CEquip1241*)eqp)->FrequenceBalayage(valeur);

					if(lResult<0) break;		// paramètre incorrect

					if(lResult == 0)			// Canal de veille annulé
						sprintf(reponse,"w4%2.2d00",valeur);
					else						// Positionnement
					{
						indice_frequence = valeur;
						iResult = ((CEquip1241*)eqp)->ChangeFrequence(0,lResult,FALSE);
						TraiteTS(REC_1241_BALAY_POSI,reponse);
						reponse[0]='w';
					}
					EnvoyerTS(reponse);
					break;

				case '4':		// demande de lecture
					valeur = atoi(mes+2);
					lResult = ((CEquip1241*)eqp)->FrequenceBalayage(valeur);

					if(lResult<0) break;		// paramètre incorrect

					if(lResult == 0)			// Borne de veille annulé
						sprintf(reponse,"w4%2.2d00",valeur);
					else						// Positionnement
					{
						indice_frequence = valeur;
						iResult = ((CEquip1241*)eqp)->ChangeFrequence(0,lResult,FALSE);
						TraiteTS(REC_1241_BALAY_LECT,reponse);
						reponse[0]='w';
					}

					EnvoyerTS(reponse);
					break;

				case '5':		// Modification d'un canal de veille
					if((int)strlen(mes+2)<3)
					{
						iResult = ERR_PAS_ACQUITTE;
						break;
					}
					strncpy(reponse,mes+2,2);reponse[2]=0; 	// indice freq
					valeur = atoi(reponse);
	
					strcpy(reponse,mes+4);					// frequence
					long_valeur = atol(reponse) * Puissance(10,8-(int)strlen(reponse));
	
					lResult = ((CEquip1241*)eqp)->ChangeFrequenceBalayage(valeur,long_valeur);
					if(lResult>=0)
					{
						indice_frequence = valeur;
						if(long_valeur != 0)
						{
							sprintf(reponse,"w5%2.2d%8.8ld",valeur,long_valeur);
							// Purge des 0 de fin de message
							while(reponse[(int)strlen(reponse)-1] == '0') 
								reponse[(int)strlen(reponse)-1]=0;
						}
						else
							sprintf(reponse,"w5%2.2d00",valeur);

   						EnvoyerTS(reponse);
						iResult = 0;
					}
					break;

				case '7':		// Définition du cycle
					if((int)strlen(mes+2)!=2)
					{
						iResult = ERR_PAS_ACQUITTE;
						break;
					}
					strncpy(reponse,mes+2,2);reponse[2]=0; // indice Bande
					valeur = atoi(reponse);
					if(valeur<1 || valeur>10)
					{
						iResult = ERR_PAS_ACQUITTE;
						break;
					}

					sprintf(reponse,"w7%2.2d",valeur);
					EnvoyerTS(reponse);

					iResult = 0;
					break;

				case '9':		// Vitesse balayage
					iResult = mes[2]-0x3C;		// degre
					if(iResult<0 || iResult>2)
					{
						iResult = ERR_PAS_ACQUITTE;
						break;
					}

					indice_vitesse = iResult;
					
					if((int)strlen(mes+2)>1)	// demande de modification
					{
						valeur = atoi(mes+3);
						iResult = ((CEquip1241*)eqp)->ChangeVitesseBalayage(indice_vitesse,valeur);
					}

					if(iResult>=0)				// Pas d'erreur sur modification
					{
						TraiteTS(REC_1241_VITESSE_BAL,reponse);
						reponse[0]='w';
						EnvoyerTS(reponse);
					}
					break;
			}
			break;

		case 'T':					   // de mande de test
			iResult = strcmp(mes,"TST");
			if(iResult == 0)				// Commande correcte
			{
				strcpy(reponse,"tst");
				EnvoyerTS(reponse);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);
				AjouterTS(NULL,CDE_TEMPO_SEQ);

				AjouterTS(NULL,REC_1241_TEST);
			}
			break;

		case 'Z':		// Lancement du balayage
			if((int)strlen(mes+1)>4)
			{
				iResult = ERR_PAS_ACQUITTE;
				break;
			}
			strcpy(reponse,mes);
			reponse[0]='z';

			EnvoyerTS(reponse);
			iResult = 0;
			break;

		case 'X':		// Etat logique
			if((int)strlen(mes)!=3)
			{
				iResult = ERR_PAS_ACQUITTE;
				break;
			}
			strcpy(reponse,mes);
			reponse[0]='x';
			reponse[1]='x';
			EnvoyerTS(reponse);
			iResult = 0;
			break;

		case 'Y':		// Data out
			if((int)strlen(mes)!=1)
			{
				iResult = ERR_PAS_ACQUITTE;
				break;
			}
			EnvoyerTS("y");
			AjouterTS(NULL,REC_1241_MODE_RECEP);
			AjouterTS(NULL,REC_1241_FILTRE_FI);
			AjouterTS(NULL,REC_1241_ATTENUATEUR);
			AjouterTS(NULL,REC_1241_CAG);
			AjouterTS(NULL,REC_1241_REJECTEUR);
			AjouterTS(NULL,REC_1241_SQUELCH);
			AjouterTS(NULL,REC_1241_BFO);
			AjouterTS(NULL,REC_1241_CANAL_POSI);
			iResult = 0;
			break;

		default:
//			iResult = ERR_PAS_ACQUITTE;
			iResult = ERR_CDE_INCONNUE;
			break;
	}

	return iResult;
}

/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
int CProtoRecHF:: TraiteTS(int type_REC,char *reponse)
{
	int		iResult;
	long	lResult;

	char	buf[80];

	iResult = ((CEquip1241*)eqp)->Spin();
	if(iResult)	return ERR_CDE_INCONNUE;

	strcpy(reponse,"");
	switch(type_REC)
	{
		case REC_1241_MODE_RECEP:
			iResult = ((CEquip1241*)eqp)->ModeRecep(CanalLecture());
			sprintf(reponse,"M%d",iResult);
			break;

		case REC_1241_ATTENUATEUR:
			iResult = ((CEquip1241*)eqp)->Attenuateur(CanalLecture());
			sprintf(reponse,"A%d",iResult);
			break;

		case REC_1241_FILTRE_FI:
			iResult = ((CEquip1241*)eqp)->FiltreFI(CanalLecture());
			sprintf(reponse,"K%d",iResult);
			break;

		case REC_1241_CAG:
			iResult = ((CEquip1241*)eqp)->Cag(CanalLecture());
			switch(iResult)
			{
				case 0:
					strcpy(reponse,"G#");
					break;
				case 1:
					strcpy(reponse,"G<");
					break;
				case 2:
					strcpy(reponse,"G=");
					break;
				case 3:
					strcpy(reponse,"G>");
					break;
				case 4:
					strcpy(reponse,"G!");
					break;
			}
			break;

		case REC_1241_SQUELCH:
			iResult = ((CEquip1241*)eqp)->Squelch(CanalLecture());
			sprintf(reponse,"Q%d",iResult);
			break;

		case REC_1241_SENS_MANIP:
			iResult = ((CEquip1241*)eqp)->SensManip(CanalLecture());
			sprintf(reponse,"N%d",iResult);
			break;
	
		case REC_1241_SHIFT:
			iResult = ((CEquip1241*)eqp)->Shift(CanalLecture());
			sprintf(reponse,"E%d",iResult);
			break;
	
		case REC_1241_FREQUENCE:
			lResult = ((CEquip1241*)eqp)->Frequence(CanalLecture());
			sprintf(reponse,"F%8.8ld",lResult);

			// Purge des 0 de fin de message
			while(reponse[(int)strlen(reponse)-1] == '0') 
				reponse[(int)strlen(reponse)-1]=0;

			break;

		case REC_1241_BFO:
			iResult = ((CEquip1241*)eqp)->Bfo(CanalLecture());
			sprintf(reponse,"B%3.3d",iResult/10);
			iResult = 0;
			break;

		case REC_1241_REJECTEUR:
			if(((CEquip1241*)eqp)->AvecRejecteur())
			{
				iResult = ((CEquip1241*)eqp)->Rejecteur();
				sprintf(reponse,"R%d",iResult/10);
				iResult = 0;
			}
			else
				strcpy(reponse,"R#");
			break;

		case REC_1241_NIVEAU_HF:
			iResult = ((CEquip1241*)eqp)->GainHF(CanalLecture());
			sprintf(reponse,"H%C%C",iResult/16 + 0x30,(iResult%16) + 0x30);
			break;

		case REC_1241_MESUREUR:
			iResult = ((CEquip1241*)eqp)->Mesureur(CanalLecture());
			sprintf(reponse,"V%C%C",iResult/16 + 0x30,(iResult%16) + 0x30);
			break;

		case REC_1241_SEUIL_COR:
			iResult = ((CEquip1241*)eqp)->CorSquelch();
			sprintf(reponse,"U%C%C",iResult/16 + 0x30,(iResult%16) + 0x30);
			break;

		case REC_1241_CENTRAGE_F1:
			iResult = ((CEquip1241*)eqp)->CentrageF1();
			sprintf(reponse,"L%2.2o",iResult);
			break;

		case REC_1241_CANAL_POSI:
			iResult = ((CEquip1241*)eqp)->Canal();
			sprintf(reponse,"P%2.2d",iResult);

			TraiteTS(REC_1241_FREQUENCE,buf);
			strcat(reponse,buf+1);

			TraiteTS(REC_1241_MODE_RECEP,buf);
			strcat(reponse,buf+1);

			if(buf[1]=='5')		// Mode F1
			{
				TraiteTS(REC_1241_SHIFT,buf);
				strcat(reponse,buf+1);

				TraiteTS(REC_1241_SENS_MANIP,buf);
				buf[1] += 12;
				strcat(reponse,buf+1);
			}

			TraiteTS(REC_1241_FILTRE_FI,buf);
			strcat(reponse,buf+1);

			TraiteTS(REC_1241_ATTENUATEUR,buf);
			strcat(reponse,buf+1);

			TraiteTS(REC_1241_CAG,buf);
			strcat(reponse,buf+1);

			// Caractère réservé
			strcat(reponse,"0");

			TraiteTS(REC_1241_SQUELCH,buf);
			strcat(reponse,buf+1);

			TraiteTS(REC_1241_BFO,buf);
			strcat(reponse,buf+1);

			break;

		case REC_1241_CANAL_LECT:
			sprintf(reponse,"C%2.2d",CanalLecture());

			TraiteTS(REC_1241_FREQUENCE,buf);
			strcat(reponse,buf+1);

			TraiteTS(REC_1241_MODE_RECEP,buf);
			strcat(reponse,buf+1);

			if(buf[1]=='5')		// Mode F1
			{
				TraiteTS(REC_1241_SHIFT,buf);
				strcat(reponse,buf+1);
							 
				TraiteTS(REC_1241_SENS_MANIP,buf);
				buf[1] += 12;
				strcat(reponse,buf+1);
			}

			TraiteTS(REC_1241_FILTRE_FI,buf);
			strcat(reponse,buf+1);

			TraiteTS(REC_1241_ATTENUATEUR,buf);
			strcat(reponse,buf+1);

			TraiteTS(REC_1241_CAG,buf);
			strcat(reponse,buf+1);

			// Caractère réservé
			strcat(reponse,"0");

			TraiteTS(REC_1241_SQUELCH,buf);
			strcat(reponse,buf+1);

			TraiteTS(REC_1241_BFO,buf);
			strcat(reponse,buf+1);

		
			TraiteTS(REC_1241_NIVEAU_HF,buf);
			strcat(reponse,buf+1);

			TraiteTS(REC_1241_SEUIL_COR,buf);
			strcat(reponse,buf+1);
			break;

		case REC_1241_VEILLE_POSI:
			iResult = ((CEquip1241*)eqp)->Veille(indice_veille);
			if(iResult <=0)
			{
				iResult = ERR_PAS_ACQUITTE;
				break;
			}
			sprintf(reponse,"W0%2.2d%2.2d",indice_veille,iResult);

			TraiteTS(REC_1241_CANAL_POSI,buf);
			strcat(reponse,buf+3);
			break;

		case REC_1241_VEILLE_LECT:
			iResult = ((CEquip1241*)eqp)->Veille(indice_veille);
			if(iResult <=0)
			{
				iResult = ERR_PAS_ACQUITTE;
				break;
			}
			sprintf(reponse,"W1%2.2d%2.2d",indice_veille,iResult);

			TraiteTS(REC_1241_CANAL_LECT,buf);
			strcat(reponse,buf+3);
			break;

		case REC_1241_TEMPS_MAINT:
			iResult = ((CEquip1241*)eqp)->TempsMaintien(indice_maintien);
			sprintf(reponse,"W8%C%2.2d",indice_maintien+0x3C,iResult);
			break;

		case REC_1241_BALAY_POSI:
			lResult = ((CEquip1241*)eqp)->FrequenceBalayage(indice_frequence);
			if(lResult <=0)
			{
				iResult = ERR_PAS_ACQUITTE;
				break;
			}

			sprintf(reponse,"W3%2.2d%8.8ld",indice_frequence,lResult);
			// Purge des 0 de fin de message
			while(reponse[(int)strlen(reponse)-1] == '0') 
				reponse[(int)strlen(reponse)-1]=0;
			iResult = 0;
			break;

		case REC_1241_BALAY_LECT:
			lResult = ((CEquip1241*)eqp)->FrequenceBalayage(indice_frequence);
			if(lResult <=0)
			{
				iResult = ERR_PAS_ACQUITTE;
				break;
			}

			sprintf(reponse,"W4%2.2d%8.8ld",indice_frequence,lResult);
			// Purge des 0 de fin de message
			while(reponse[(int)strlen(reponse)-1] == '0') 
				reponse[(int)strlen(reponse)-1]=0;
			iResult = 0;
			break;

		case REC_1241_VITESSE_BAL:
			iResult = ((CEquip1241*)eqp)->VitesseBalayage(indice_vitesse);
			sprintf(reponse,"W9%C%2.2d",indice_vitesse+0x3C,iResult);
			break;

		case REC_1241_OPTION_REC:
			sprintf(reponse,"OPT5%?",iResult);
			break;

		case REC_1241_TEST:
			iResult = ((CEquip1241*)eqp)->Test();
			sprintf(reponse,"TST%2.2d",iResult);
			break;

		case REC_1241_INFO:
			iResult = ((CEquip1241*)eqp)->Info();
			sprintf(reponse,"T%d",iResult);
			break;
//
		case REC_1241_BALAYAGE:
//			sprintf(reponse,"Z%d",iResult);
//			break;

		case REC_1241_ETAT_LOGI:
			strcpy(reponse,"XXU");
			break;

		case REC_1241_MODE_LOCAL:
			iResult = ((CEquip1241*)eqp)->Local();
			if(iResult)	strcpy(reponse,"RMT");
			else strcpy(reponse,"LOC");
			break;

		default:
			iResult = ERR_CDE_INCONNUE;
			break;
	}

	return iResult;
}

/* **************************************************************************
METHODE :		RecevoirTC()
TRAITEMENT:		Réceptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProtoRecHF::RecevoirTC(char *message,int nb_car)
{
	char	buf[TAILLE_BUFFER+1];
	int		i,iResult;

	if(nb_car > TAILLE_BUFFER) return ERR_TAILLE_BUFFER;

	i=0;
	while(i<nb_car)
	{
		iResult = ligne.Lire(buf+i,1);
		if(iResult < 0) return ERREUR_EXTERNE+iResult;
		if(iResult == 0) return ERREUR_TIMEOUT;
		if(buf[i]==DEBUT_TRAME && i!=0)
		{
			buf[0] = DEBUT_TRAME;
			i=0;
		}
		if(buf[i]==FIN_TRAME) break;

		i++;
	}

	if(!ExtraitUtile(buf,message,&iResult)) 
		return ERR_NON_CONFORME;			// Message non conforme

	return iResult;
}

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Attend un message d'acquitement du type de commande précedement
				envoyé comme TS Maitre
***************************************************************************	*/
BOOL CProtoRecHF::ValideAcquittement(int type_cde,char *buf)
{
	int		iResult = NULL;
	BOOL	bResult;

	if(!erreur_com.controle_parite)	return TRUE;

	bResult = TRUE;
	switch(type_cde)
	{
		case REC_1241_MODE_RECEP:
			if(strcmp(buf,"m") != 0)	bResult = FALSE;
			break;
		case REC_1241_ATTENUATEUR:
			if(strcmp(buf,"a") != 0)	bResult = FALSE;
			break;
		case REC_1241_FILTRE_FI:
			if(strcmp(buf,"k") != 0)	bResult = FALSE;
			break;
		case REC_1241_CAG:
			if(strcmp(buf,"g") != 0)	bResult = FALSE;
			break;
		case REC_1241_SQUELCH:
			if(strcmp(buf,"q") != 0)	bResult = FALSE;
			break;
		case REC_1241_SENS_MANIP:
			if(strcmp(buf,"n") != 0)	bResult = FALSE;
			break;
		case REC_1241_SHIFT:
			if(strcmp(buf,"e") != 0)	bResult = FALSE;
			break;
		case REC_1241_FREQUENCE:
			if(strcmp(buf,"f") != 0)	bResult = FALSE;
			break;
		case REC_1241_BFO:
			if(strcmp(buf,"b") != 0)	bResult = FALSE;
			break;
		case REC_1241_REJECTEUR:
			if(strcmp(buf,"r") != 0)	bResult = FALSE;
			break;
		case REC_1241_NIVEAU_HF:
			if(strcmp(buf,"h") != 0)	bResult = FALSE;
			break;
		case REC_1241_MESUREUR:
			if(strcmp(buf,"v") != 0)	bResult = FALSE;
			break;
		case REC_1241_SEUIL_COR:
			if(strcmp(buf,"u") != 0)	bResult = FALSE;
			break;
		case REC_1241_CENTRAGE_F1:
			if(strcmp(buf,"l") != 0)	bResult = FALSE;
			break;
		case REC_1241_CANAL_POSI:
			if(strcmp(buf,"p") != 0)	bResult = FALSE;
			break;
		case REC_1241_CANAL_LECT:
			if(strcmp(buf,"c") != 0)	bResult = FALSE;
			break;
		case REC_1241_VEILLE_POSI:
			if(strcmp(buf,"w0") != 0)	bResult = FALSE;
			break;
		case REC_1241_VEILLE_LECT:
			if(strcmp(buf,"w1") != 0)	bResult = FALSE;
			break;
		case REC_1241_TEMPS_MAINT:
			if(strcmp(buf,"w8") != 0)	bResult = FALSE;
			break;
		case REC_1241_BALAY_POSI:
			if(strcmp(buf,"w3") != 0)	bResult = FALSE;
			break;
		case REC_1241_BALAY_LECT:
			if(strcmp(buf,"w4") != 0)	bResult = FALSE;
			break;
		case REC_1241_VITESSE_BAL:
			if(strcmp(buf,"w9") != 0)	bResult = FALSE;
			break;
		case REC_1241_OPTION_REC:
			if(strcmp(buf,"op") != 0)	bResult = FALSE;
			break;
		case REC_1241_TEST:
			if(strcmp(buf,"tst") != 0)	bResult = FALSE;
			break;
		case REC_1241_INFO:
			if(strcmp(buf,"t") != 0)	bResult = FALSE;
			break;
		case REC_1241_BALAYAGE:
			if(strcmp(buf,"z") != 0)	bResult = FALSE;
			break;
		case REC_1241_ETAT_LOGI:
			if(strcmp(buf,"xx") != 0)	bResult = FALSE;
			break;

		case REC_1241_MODE_LOCAL:
			if(strstr(" loc rmt ",buf) ==0 )	bResult = FALSE;
			break;
		default:
			break;
	}

	return bResult;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
char* CProtoRecHF::ControleTrame(char *message,char *octet_controle)
{
	int		i,len_mes;
	char	pc;

	strcpy(octet_controle,"");

	if(!erreur_com.controle_parite) 	return octet_controle;

	len_mes = (int)strlen(message);

	pc = 0;
	i=len_mes-1;
	while(i>=0)
	{	
		pc = pc ^ message[i];
		
		if((i) % 8 == 0)	// caract précedent = debut de tranche
		{
			if(pc < 64) pc += 64;
			strncat(octet_controle,&pc,1);
			pc = 0;
		}
		i--;
	}
	return octet_controle;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génère les octets de controle du message
				Un octet est necessaire par tranche de 8 caractere
***************************************************************************	*/
BOOL CProtoRecHF::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	char 	octet_controle[8];
	int		len_mes,nb_tranche;

	len_mes = (int)strlen(buf);		
	if(buf[0] != DEBUT_TRAME && buf[len_mes -1] != FIN_TRAME)
		return FALSE;

// 1 tranche = 8 caractère utile + 1 PC sans oublier d'oter les
// caracteres de debut et de fin de trame
	if(erreur_com.controle_parite)
		nb_tranche = (len_mes-2)/9 + !((len_mes-2)%9 == 0);
	else
		nb_tranche = 0;		// Aucun caractere de parite

	*long_utile = len_mes - 2 - nb_tranche;
	strcpy(message,"");
	strncat(message,buf+1,*long_utile);

	ControleTrame(message,octet_controle);
	if(strncmp(octet_controle,buf+1+(len_mes - 2 - nb_tranche),nb_tranche))
		return FALSE;

	return TRUE;
}

/* **************************************************************************
METHODE :		CanalLecture()
TRAITEMENT:		Retourne le n° de canal pour utiliser lors de l'envoi des TS
***************************************************************************	*/
int CProtoRecHF::CanalLecture()
{
	int	valeur;
	
	EnterCriticalSection(&crit);
		valeur = lecture_canal;
	LeaveCriticalSection(&crit);

	return valeur;
}

/* **************************************************************************
METHODE :		ChangeCanalLecture()
TRAITEMENT:		Force un n° de canal pour utiliser lors de l'envoi des TS
***************************************************************************	*/
BOOL CProtoRecHF::ChangeCanalLecture(int	valeur)
{
	if(valeur<0 || valeur > 99) return FALSE;
	
	EnterCriticalSection(&crit);
		lecture_canal = valeur;
	LeaveCriticalSection(&crit);

	return TRUE;
}
