/* **************************************************************************
FICHIER :	P_18A.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CProto18A
***************************************************************************	*/

#include "stdafx.h"

#include "Comm\P_18A.h"
#include "Equip\Eqp18A.h"
#include "divers\div_tmp.h"

const int 	SOH		 	= 0x01;			// Caractère de début de message
const int 	ETX 		= 0x03;			// Caractère Fin de message
const int 	EOT 		= 0x04;			// Caractère de Fin de dialogue
const int 	STX 		= 0x02;			// Sépérateur entre adresse/données
/* **************************************************************************
METHODE :		CProto18A()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProto18A::CProto18A(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = FALSE;
	lecture_canal = 0;
}

/* **************************************************************************
METHODE :		~CProto18A()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProto18A::~CProto18A()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProto18A::EnvoyerTS(char *message)
{
	int		len_mes,iResult;
	int		nb_car_enveloppe;		// Nombre de caractère envelopant le message

	char	buf[TAILLE_BUFFER+1];
	char	adr[6];					// Adresse
	char	adr_controle[2];
	char	mes_controle[2];

	if(message[0]==EOT)
		strcpy(buf,message);
	else
	{
		len_mes = (int)strlen(message);	// Taille du message à envoyer
		nb_car_enveloppe = 1 + 4+1 + 1 + 1 + 1; // SOH + adresse+controle + STX
											// + controle + ETX
		if(len_mes+nb_car_enveloppe > TAILLE_BUFFER)
			return ERR_TAILLE_BUFFER;
	
		sprintf(adr,"%2.2XFF",((CEquip18A*)eqp)->Numero());

		sprintf(buf,"%c%s%s%c%s%s%c",erreur_com.pas_debut ?  0x20 : SOH,
						adr,
						ControleTrame(adr,adr_controle),
						STX,
						message,
						ControleTrame(message,mes_controle),
						erreur_com.pas_fin ? 0 : EOT);

	}
	iResult = ligne.Ecrire(buf);
	if(iResult < 0) return ERREUR_EXTERNE+iResult;

	return iResult;  // nb d'octet transmis
}

/* **************************************************************************
METHODE :		RecevoirTC()
TRAITEMENT:		Réceptionne une TC, Valide le bon format et en extrait la partie
				utile du message
***************************************************************************	*/
int CProto18A::RecevoirTC(char *message,int nb_car)
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

		if(buf[i]==SOH && i!=0)
		{
			buf[0] = SOH;
			i=0;
		}
		if(buf[i]==ETX || buf[i]==EOT) break;

		i++;
	}

	if(!ExtraitUtile(buf,message,&iResult))
		return ERR_NON_CONFORME;			// Message non conforme

	return iResult;
}

/* **************************************************************************
METHODE :		TraiteTC()
TRAITEMENT:		Traite une TC (partie utile) et formate le message TS reponse
				comme acquitement
***************************************************************************	*/
int CProto18A::TraiteTC(char *mes)
{
	int		code1, code2;
	int		valeur;

	char	*pcResult;

	int		iResult = 0;
	BOOL	success = FALSE;
	int 	f_em 	= -1;
	int 	f_rec 	= -1;
	int		accord_a_faire = 0;

	char	reponse[TAILLE_PIPE_MESSAGE+1];
	char	buf[80];

	int		old_status_evol = ((CEquip18A*)eqp)->StatusEvolution();

	switch(mes[0])
	{
		case 'E':					// Mesure ou données d'état
			return ERR_CDE_INCONNUE;// ce n'est pas une TC
			break;

		case 'F':					// Instruction
			if((int)strlen(mes) < 2)	return ERR_CDE_INCONNUE;

			sscanf(mes+1,"%1X",&code1);
			if(code1<6 || code1>0xF)	return ERR_CDE_INCONNUE;

			switch(code1)
			{
				case 6:
					if((int)strlen(mes+2) != 3)	return ERR_CDE_INCONNUE;
					sscanf(mes+2,"%2d",&valeur);
					iResult = ((CEquip18A*)eqp)->ChangeAdresse(valeur,FALSE);
					if(iResult<0) break;

					sscanf(mes+4,"%1d",&valeur);
					iResult = ((CEquip18A*)eqp)->ChangeReserve(valeur,FALSE);
					if(iResult>=0)
					{
						((CEquip18A*)eqp)->ChangeStatusEvolution((old_status_evol+1) % (0xF+1));
						AjouterTS(NULL,EMR_SURVEILLANCE);
						AjouterTS(NULL,EMR_EXPLOITATION);
					}			
					break;

				case 7:
					if((int)strlen(mes+2) != 0)	return ERR_CDE_INCONNUE;
					
					if(((CEquip18A*)eqp)->Silence()) return ERR_PAS_ACQUITTE;

					iResult = ((CEquip18A*)eqp)->ChangeAccord(1,FALSE);
					if(iResult>=0)
					{
						((CEquip18A*)eqp)->ChangeAccordMulti(0,1,FALSE);	// Accord non demandé == 1

						TraiteTS(EMR_SURVEILLANCE,reponse);
						EnvoyerTS(reponse);

						iResult = ((CEquip18A*)eqp)->ChangeEmission(1,FALSE);
						TraiteTS(EMR_STATUS,reponse);
						EnvoyerTS(reponse);

						Sleep(TEMPO_TRAVAIL);

						iResult = ((CEquip18A*)eqp)->ChangeAccord(0,FALSE);
						iResult = ((CEquip18A*)eqp)->ChangeEmission(0,FALSE);
						TraiteTS(EMR_STATUS,reponse);
						EnvoyerTS(reponse);
						Sleep(TEMPO_TRAVAIL);

						AjouterTS(NULL,EMR_EXPLOITATION);
					}			
					break;

				case 8:
					if((int)strlen(mes+2) != 0)	return ERR_CDE_INCONNUE;
					iResult = 0;
					if(iResult>=0)
					{
						EnvoyerTS("F8E9");		// D'après test
					}
					break;

				case 9:
					if((int)strlen(mes+2) != 2)	return ERR_CDE_INCONNUE;
					sscanf(mes+2,"%2d",&valeur);

					if(valeur<1 || valeur >99) return ERR_CDE_INCONNUE;

					ChangeCanalLecture(valeur);

					iResult = ((CEquip18A*)eqp)->FrequenceEm(CanalLecture());
					if(iResult>=0)
					{
						// 0,1
						sprintf(reponse,"F908%4.4d",iResult);
	
						// 2
						if(iResult>=0) sprintf(buf,"%2.2d",CanalLecture());
						strcat(reponse,buf);

						// 3
						sprintf(buf,"%1d%1d",
								((CEquip18A*)eqp)->Niveau(CanalLecture()),
								((CEquip18A*)eqp)->AccordMulti(CanalLecture()));
						strcat(reponse,buf);

						// 4
						if(((CEquip18A*)eqp)->Canal()==-1) strcpy(buf,"FF");
						else
						{
							sprintf(buf,"%1X%1X",
									((CEquip18A*)eqp)->Mode(CanalLecture()),
									(((CEquip18A*)eqp)->Bande(CanalLecture()))*8 + ((CEquip18A*)eqp)->CleCrypto(CanalLecture()));
						}
						strcat(reponse,buf);
	
						// 5
						sprintf(buf,"%1d%1d",
								((CEquip18A*)eqp)->Antenne(CanalLecture()),
								((CEquip18A*)eqp)->Squelch(CanalLecture()));
						strcat(reponse,buf);

						// 6,7
						iResult = ((CEquip18A*)eqp)->FrequenceRec(CanalLecture());
						sprintf(buf,"%4.4d",iResult);
						strcat(reponse,buf);

						// 8
						sprintf(buf,"%1X%1d",
								((CEquip18A*)eqp)->PasRec(CanalLecture()) | 4*((CEquip18A*)eqp)->PasEm(CanalLecture()),
								((CEquip18A*)eqp)->Protection(CanalLecture()));
						strcat(reponse,buf);

						EnvoyerTS(reponse);		
					}			
					break;

				case 0xA:
/*					iResult = ((CEquip18A*)eqp)->Local();
					if(iResult==0)
					{
						sprintf(reponse,"%c",EOT);
						EnvoyerTS(reponse);
						break;
					}
Pour facilter les testde TESR */
					iResult = ((CEquip18A*)eqp)->Scan();
					if(iResult==1)
					{
						sprintf(reponse,"%c",EOT);
						EnvoyerTS(reponse);
						break;
					}
					
					if((int)strlen(mes+2) == 2)
					{
						sscanf(mes+2,"%2d",&valeur);
						// TRaitement du canal n° valeur
						if(valeur<1 || valeur>99) iResult = ERR_NON_CONFORME;
						iResult = ((CEquip18A*)eqp)->MemoriseCanal(valeur,FALSE);

						AjouterTS(NULL,EMR_STATUS);
					}
					else
					{
						if((int)strlen(mes+2) <= 20)	return ERR_CDE_INCONNUE;
						sscanf(mes+2,"%2d",&valeur);	// N° canal
						if(valeur<1 || valeur>99) return ERR_NON_CONFORME;

						ChangeCanalLecture(valeur);

						sscanf(mes+4,"%2d",&valeur);	// adress 08
						if(valeur!=8) return ERR_NON_CONFORME;

						sscanf(mes+6,"%4d",&f_em);	// frequence Em
						if( ((CEquip18A*)eqp)->FrequenceEm(CanalLecture()) != f_em)
							accord_a_faire = 1;


						sscanf(mes+10,"%2d",&valeur);	// Canal->inutil

						sscanf(mes+12,"%1X",&valeur);
						iResult = ((CEquip18A*)eqp)->ChangeNiveau(CanalLecture(),valeur,FALSE);

						sscanf(mes+14,"%2X",&valeur);
						iResult = ((CEquip18A*)eqp)->ChangeMode(CanalLecture(),valeur>>4,FALSE);
						iResult = ((CEquip18A*)eqp)->ChangeBande(CanalLecture(),(valeur & 0xF)>>3,FALSE);
						iResult =((CEquip18A*)eqp)->ChangeCleCrypto(CanalLecture(),valeur & 0x7,FALSE);


						sscanf(mes+16,"%2X",&valeur);
						iResult = ((CEquip18A*)eqp)->ChangeAntenne(CanalLecture(),valeur>>4,FALSE);
						iResult = ((CEquip18A*)eqp)->ChangeSquelch(CanalLecture(),valeur & 0xF,FALSE);

						sscanf(mes+18,"%4d",&f_rec);
						if((f_em==f_rec) || CanalLecture()>=95)
						{
							iResult = ((CEquip18A*)eqp)->ChangeFrequenceRec(CanalLecture(),f_rec,FALSE);
							iResult = ((CEquip18A*)eqp)->ChangeFrequenceEm(CanalLecture(),f_em,FALSE);
						}

						sscanf(mes+22,"%2X",&valeur);
						iResult = ((CEquip18A*)eqp)->ChangePasEm(CanalLecture(),valeur>>6,FALSE);
						iResult = ((CEquip18A*)eqp)->ChangePasRec(CanalLecture(),(valeur&0x30)>>4,FALSE);
						iResult = ((CEquip18A*)eqp)->ChangeProtection(CanalLecture(),valeur & 0xF,FALSE);

						iResult = ((CEquip18A*)eqp)->ChangeCanal(CanalLecture(),FALSE);

						((CEquip18A*)eqp)->ChangeStatusEvolution((old_status_evol+1) % (0xF+1));
						TraiteTS(EMR_SURVEILLANCE,reponse);
						EnvoyerTS(reponse);
						TraiteTS(EMR_EXPLOITATION,reponse);
						EnvoyerTS(reponse);

						if(accord_a_faire && !((CEquip18A*)eqp)->Silence())
						{
			 				((CEquip18A*)eqp)->ChangeAccord(1,FALSE);
							((CEquip18A*)eqp)->ChangeAccordMulti(0,1,FALSE);	// Accord non demandé == 1
							((CEquip18A*)eqp)->ChangeEmission(1,FALSE);
					
							TraiteTS(EMR_STATUS,reponse);
							EnvoyerTS(reponse);

							AjouterTS(NULL,CDE_TEMPO_SEQ);

							((CEquip18A*)eqp)->ChangeAccord(0,FALSE);
							((CEquip18A*)eqp)->ChangeEmission(0,FALSE);
					
							AjouterTS(NULL,EMR_STATUS);
						}			
					}
					break;

				case 0xB:
/*					iResult = ((CEquip18A*)eqp)->Local();
					if(iResult==0)
					{
						sprintf(reponse,"%c",EOT);
						EnvoyerTS(reponse);
						break;
					}
Pour facilter les testde TESR */

					if((int)strlen(mes+2) != 2) return ERR_PAS_ACQUITTE;

					sscanf(mes+2,"%2d",&valeur);
					iResult = ((CEquip18A*)eqp)->ChangeCanal(valeur,FALSE);

					if(iResult >= 0)				// Modification acceptée Autre TS
					{
						ChangeCanalLecture(valeur);

						((CEquip18A*)eqp)->ChangeStatusEvolution((old_status_evol+1) % (0xF+1));
						AjouterTS(NULL,EMR_SURVEILLANCE);
						AjouterTS(NULL,EMR_EXPLOITATION);
						AjouterTS(NULL,EMR_STATUS);
					}
					break;

				case 0xC:
					if((int)strlen(mes+2) != 2) return ERR_PAS_ACQUITTE;

					sscanf(mes+2,"%1X",&code1);
					sscanf(mes+3,"%1X",&code2);

					if(code1<0 || code1>0xD)
					{
						iResult = ERR_CDE_INCONNUE;
						break;
					}
					if(code2<0 || code2>0xD)
					{
						iResult = ERR_CDE_INCONNUE;
						break;
					}
					if(code2<code1)
					{
						iResult = ERR_CDE_INCONNUE;
						break;
					}

					strncpy(reponse,mes+2,2);reponse[2]=0; 	// Force Fin de chaine
					TraiteTS(EMR_EXPLOITATION,buf);			// Recup un message complet 0-D
					strcat(reponse,buf+2+code1*2);			// Tronque à 1er adresse demandé
					reponse[2+(code2+1-code1)*2] = 0; 		// Force Fin de chaine
					EnvoyerTS(reponse);
					break;

				case 0xD:
					if((int)strlen(mes+2) != 0) return ERR_PAS_ACQUITTE;

/*					iResult = ((CEquip18A*)eqp)->Local();
					if(iResult==0)
					{
						sprintf(reponse,"%c",EOT);
						EnvoyerTS(reponse);
						break;
					}
Pour facilter les testde TESR */

					iResult = ((CEquip18A*)eqp)->ScanDebut();
					if(iResult==0)			// non programmé
					{
						sprintf(reponse,"%c",EOT);
						EnvoyerTS(reponse);
						break;
					}
					iResult = ((CEquip18A*)eqp)->ScanFin();
					if(iResult==0)			// non programmé
					{
						sprintf(reponse,"%c",EOT);
						EnvoyerTS(reponse);
						break;
					}

					((CEquip18A*)eqp)->ChangeStatusEvolution((old_status_evol+1) % (0xF+1));
					TraiteTS(EMR_SURVEILLANCE,reponse);
					EnvoyerTS(reponse);

					((CEquip18A*)eqp)->ChangeHfRecu(1,FALSE);
					((CEquip18A*)eqp)->ChangeScan(1,FALSE);
		
					TraiteTS(EMR_STATUS,reponse);
					EnvoyerTS(reponse);

					AjouterTS(NULL,EMR_EXPLOITATION);
					break;

				case 0xE:
					if((int)strlen(mes+2) != 0) return ERR_PAS_ACQUITTE;

					iResult = 0;
					if(iResult>=0)			// Distance
					{
						AjouterTS(NULL,EMR_STATUS);
					}
					break;

				case 0xF:
					if((int)strlen(mes+2) != 1) return ERR_PAS_ACQUITTE;

/*					iResult = ((CEquip18A*)eqp)->Local();
					if(iResult==0)
					{
						sprintf(reponse,"%c",EOT);
						EnvoyerTS(reponse);
						break;
					}
Pour facilter les testde TESR */
					iResult = ((CEquip18A*)eqp)->TestEnCours();
					if(iResult==1)
					{
						sprintf(reponse,"%c",EOT);
						EnvoyerTS(reponse);
						break;
					}

					sscanf(mes+2,"%1X",&code1);
					switch(code1)
					{
						case 0:		// Test recepteur
							type_test = 0;
							iResult = ((CEquip18A*)eqp)->ChangeTestEnCours(1,FALSE);

							TraiteTS(EMR_SURVEILLANCE,reponse);
							EnvoyerTS(reponse);
							TraiteTS(EMR_STATUS,reponse);
							EnvoyerTS(reponse);

							Sleep(TEMPO_TRAVAIL);
							((CEquip18A*)eqp)->ChangeHfRecu(1,FALSE);
							TraiteTS(EMR_STATUS,reponse);
							EnvoyerTS(reponse);

							Sleep(TEMPO_TRAVAIL);
							((CEquip18A*)eqp)->ChangeHfRecu(0,FALSE);
							TraiteTS(EMR_STATUS,reponse);
							EnvoyerTS(reponse);

							Sleep(TEMPO_TRAVAIL);
							((CEquip18A*)eqp)->ChangeTestEnCours(0,FALSE);
							TraiteTS(EMR_STATUS,reponse);
							EnvoyerTS(reponse);
							break;

						case 1:		// Test Emetteur
							type_test = 1;
							iResult = ((CEquip18A*)eqp)->ChangeTestEnCours(1,FALSE);

							TraiteTS(EMR_SURVEILLANCE,reponse);
							EnvoyerTS(reponse);
							TraiteTS(EMR_STATUS,reponse);
							EnvoyerTS(reponse);

							Sleep(TEMPO_TRAVAIL);
							((CEquip18A*)eqp)->ChangeHfRecu(1,FALSE);
							TraiteTS(EMR_STATUS,reponse);
							EnvoyerTS(reponse);

							Sleep(TEMPO_TRAVAIL);
							((CEquip18A*)eqp)->ChangeHfRecu(0,FALSE);
							((CEquip18A*)eqp)->ChangeEmission(1,FALSE);
							TraiteTS(EMR_STATUS,reponse);
							EnvoyerTS(reponse);

							Sleep(TEMPO_TRAVAIL);
							((CEquip18A*)eqp)->ChangeEmission(0,FALSE);
							TraiteTS(EMR_STATUS,reponse);
							EnvoyerTS(reponse);

							Sleep(TEMPO_TRAVAIL);
							((CEquip18A*)eqp)->ChangeTestEnCours(0,FALSE);
							TraiteTS(EMR_STATUS,reponse);
							EnvoyerTS(reponse);
							break;

						case 0xF:
							iResult = ((CEquip18A*)eqp)->TestEnCours();
							if(iResult>0)
									sprintf(reponse,"FFE%1d",type_test);
							else
							{
								iResult = ((CEquip18A*)eqp)->Test();
								if(iResult >0)
								{
									sprintf(reponse,"FFF%1d%X%X%2.2d",
											type_test,
											iResult/1000,
											((iResult%1000)/100)==1,
											(iResult%100));
								}
								else
								{
									iResult = ((CEquip18A*)eqp)->Silence();
									sprintf(reponse,"FF%1d%1d",iResult,type_test);
								}
							}
							EnvoyerTS(reponse);

							break;
					}
					break;

				default:
					iResult = ERR_CDE_INCONNUE;
					break;
			}

			break;
  
		default:					// Données d'exploitation
			iResult = ((CEquip18A*)eqp)->Local();
			if(iResult==0)
			{
				sprintf(reponse,"%c",EOT);
				EnvoyerTS(reponse);
				break;
			}

			iResult = ((CEquip18A*)eqp)->Scan();
			if(iResult==1)
			{
				sprintf(reponse,"%c",EOT);
				EnvoyerTS(reponse);
				break;
			}

			sscanf(mes,"%1X",&code1);
			sscanf(mes+1,"%1X",&code2);
			
			if(code1<0 || code1>0xD)
			{
				iResult = ERR_CDE_INCONNUE;
				break;
			}
			if(code2<0 || code2>0xD)
			{
				iResult = ERR_CDE_INCONNUE;
				break;
			}
			if(code2<code1)
			{
				iResult = ERR_CDE_INCONNUE;
				break;
			}

			pcResult = mes+2;
			while(pcResult <= mes+2 + (code2-code1)*2)
			{
				if((int)strlen(pcResult)<2)		// Les données par paires
					return ERR_CDE_INCONNUE;

				switch(code1+(pcResult-(mes+2))/2)	// Adresse données exploit
				{
					case 0:				// Frequence Em
						if((int)strlen(pcResult)>=4)	// adres 1 fourni
						{
							sscanf(pcResult,"%4d",&valeur);
							pcResult += 4;
						}
						else
						{
							sscanf(pcResult,"%2d",&valeur);
							valeur *= 100;
							pcResult += 2;
						}
						f_em = valeur;

						if( ((CEquip18A*)eqp)->FrequenceEm(0) != f_em)
							accord_a_faire = 1;

						break;

					case 1:				// Impossible sans adresse 0
						return ERR_CDE_INCONNUE;
						break;

					case 2:				// Canal préréglé
						sscanf(pcResult,"%2d",&valeur);
						pcResult += 2;

//						iResult = ((CEquip18A*)eqp)->ChangeCanal(valeur,FALSE);
						if(iResult>=0) success = TRUE;
						break;

					case 3:				// Niveau HF,accord multicoupleur
						sscanf(pcResult,"%1X",&valeur);
						pcResult += 2;
						iResult = ((CEquip18A*)eqp)->ChangeNiveau(0,valeur,FALSE);
						if(iResult>=0) success = TRUE;
						break;

					case 4:				// Mode, Bande, Clé crypto
						sscanf(pcResult,"%2X",&valeur);
						pcResult += 2;

						iResult = ((CEquip18A*)eqp)->ChangeMode(0,valeur>>4,FALSE);
						if(iResult<0)	break;

						iResult = ((CEquip18A*)eqp)->ChangeBande(0,(valeur & 0xF)>>3,FALSE);
						if(iResult<0)	break;

						iResult =((CEquip18A*)eqp)->ChangeCleCrypto(0,valeur & 0x7,FALSE);
						if(iResult>=0) success = TRUE;
						break;

					case 5:				// Config Antenne, Squelch
						sscanf(pcResult,"%2X",&valeur);
						pcResult += 2;

						iResult = ((CEquip18A*)eqp)->ChangeAntenne(0,valeur>>4,FALSE);
						if(iResult<0)	break;
				
						iResult = ((CEquip18A*)eqp)->ChangeSquelch(0,valeur & 0xF,FALSE);
						if(iResult>=0) success = TRUE;
						break;

					case 6:				// Frequence Rec
						if((int)strlen(pcResult)>=4)	// adres 7 fourni
						{
							sscanf(pcResult,"%4d",&valeur);
							pcResult += 4;
						}
						else
						{
							sscanf(pcResult,"%2d",&valeur);
							valeur *= 100;
							pcResult += 2;
						}

						f_rec = valeur;

						if(f_em == f_rec)
						{
							iResult = ((CEquip18A*)eqp)->ChangeFrequenceEm(0,f_em,FALSE);
							iResult = ((CEquip18A*)eqp)->ChangeFrequenceRec(0,f_rec,FALSE);
							if(iResult>=0) success = TRUE;
						}
						break;

					case 7:				// Impossible sans adresse 0
						return ERR_CDE_INCONNUE;
						break;

					case 8:				// Config Antenne, Squelch
						sscanf(pcResult,"%2X",&valeur);
						pcResult += 2;

						iResult = ((CEquip18A*)eqp)->ChangePasEm(0,valeur>>6,FALSE);
						if(iResult<0)	break;

						iResult = ((CEquip18A*)eqp)->ChangePasRec(0,(valeur&0x30)>>4,FALSE);
						if(iResult<0)	break;

						iResult = ((CEquip18A*)eqp)->ChangeProtection(0,valeur & 0xF,FALSE);
						if(iResult>=0) success = TRUE;
						break;

					case 9:				// Relais Externes, Protection
						sscanf(pcResult,"%2X",&valeur);
						pcResult += 2;

						iResult = ((CEquip18A*)eqp)->ChangeRelais(valeur>>4,FALSE);
						if(iResult<0)	break;

						iResult = ((CEquip18A*)eqp)->ChangeRecGarde(valeur & 0xF,FALSE);
						if(iResult>=0) success = TRUE;
						break;
						
					case 0xA:				// Canal de debut du scan
						sscanf(pcResult,"%2d",&valeur);
						pcResult += 2;

						iResult = ((CEquip18A*)eqp)->ChangeScanDebut(valeur,FALSE);
						if(iResult>=0) success = TRUE;
						break;

					case 0xB:				// Canal de debut du scan
						sscanf(pcResult,"%2d",&valeur);
						pcResult += 2;

						iResult = ((CEquip18A*)eqp)->ChangeScanFin(valeur,FALSE);
						if(iResult>=0) success = TRUE;
						break;

					case 0xC:				// Canal de debut du scan
						sscanf(pcResult,"%2X",&valeur);
						pcResult += 2;

						iResult = ((CEquip18A*)eqp)->ChangeAdresse(valeur,FALSE);
						if(iResult>=0) success = TRUE;
						break;

					case 0xD:				// Cle Crypto générale
						sscanf(pcResult,"%1X",&valeur);
						pcResult += 2;

						iResult = ((CEquip18A*)eqp)->ChangeGeneCrypto(valeur,FALSE);
						if(iResult>=0) success = TRUE;
						break;

					default:
						iResult =  ERR_CDE_INCONNUE;
						break;
				}

			}
			
			if(success)
			{
				((CEquip18A*)eqp)->ChangeStatusEvolution((old_status_evol+1) % (0xF+1));
				TraiteTS(EMR_SURVEILLANCE,reponse);
				EnvoyerTS(reponse);
				TraiteTS(EMR_EXPLOITATION,reponse);
				EnvoyerTS(reponse);

				if(accord_a_faire && !((CEquip18A*)eqp)->Silence())
				{
	 				((CEquip18A*)eqp)->ChangeAccord(1,FALSE);
					((CEquip18A*)eqp)->ChangeAccordMulti(1,1,FALSE);	// Accord non demandé == 1
					((CEquip18A*)eqp)->ChangeEmission(1,FALSE);
					
					TraiteTS(EMR_STATUS,reponse);
					EnvoyerTS(reponse);

					AjouterTS(NULL,CDE_TEMPO_SEQ);

					((CEquip18A*)eqp)->ChangeAccord(0,FALSE);
					((CEquip18A*)eqp)->ChangeEmission(0,FALSE);
					
					AjouterTS(NULL,EMR_STATUS);
				}			

			}
			else
			{
				sprintf(reponse,"%c",EOT);
				EnvoyerTS(reponse);
			}

			break;
	}

	return iResult;
}
/* **************************************************************************
METHODE :		TraiteTS()
TRAITEMENT:		Formate une TS en fonction en réccupérant les etats internes
				de l'equipement
***************************************************************************	*/
int CProto18A:: TraiteTS(int type_cde,char *reponse)
{
	int		iResult;
	char	buf[80];

	strcpy(reponse,"");
	switch(type_cde)
	{
		case EMR_EXPLOITATION:
			// 0,1
			iResult = ((CEquip18A*)eqp)->FrequenceEm(0);
			sprintf(reponse,"0D%4.4d",iResult);
	
			// 2
			iResult = ((CEquip18A*)eqp)->Canal();
			if(iResult>=0) sprintf(buf,"%2.2d",iResult);
			else strcpy(buf,"FF");
			strcat(reponse,buf);

			// 3
			sprintf(buf,"%1d%1d",
					((CEquip18A*)eqp)->Niveau(0),
					((CEquip18A*)eqp)->AccordMulti(0));
			strcat(reponse,buf);

			// 4
			if(((CEquip18A*)eqp)->Canal()==-1) strcpy(buf,"FF");
			else
			{
				sprintf(buf,"%1X%1X",
						((CEquip18A*)eqp)->Mode(0),
						(((CEquip18A*)eqp)->Bande(0))*8 + ((CEquip18A*)eqp)->CleCrypto(0));
			}
			strcat(reponse,buf);
	
			// 5
			sprintf(buf,"%1d%1d",
					((CEquip18A*)eqp)->Antenne(0),
					((CEquip18A*)eqp)->Squelch(0));
			strcat(reponse,buf);

			// 6,7
			iResult = ((CEquip18A*)eqp)->FrequenceRec(0);
			sprintf(buf,"%4.4d",iResult);
			strcat(reponse,buf);

			// 8
			sprintf(buf,"%1X%1d",
					((CEquip18A*)eqp)->PasRec(0) | 4*((CEquip18A*)eqp)->PasEm(0),
					((CEquip18A*)eqp)->Protection(0));
			strcat(reponse,buf);

			// 9
			sprintf(buf,"%1d%1d",
					((CEquip18A*)eqp)->Relais(),
					((CEquip18A*)eqp)->RecGarde());
			strcat(reponse,buf);

			// A
			iResult = ((CEquip18A*)eqp)->ScanDebut();
			sprintf(buf,"%2.2d",iResult);
			strcat(reponse,buf);

			// B
			iResult = ((CEquip18A*)eqp)->ScanFin();
			sprintf(buf,"%2.2d",iResult);
			strcat(reponse,buf);
	
			// C
			iResult = ((CEquip18A*)eqp)->Adresse();
			sprintf(buf,"%2.2X",iResult);
			strcat(reponse,buf);

			// D
			sprintf(buf,"%1d%1X",
					((CEquip18A*)eqp)->GeneCrypto(),
					((CEquip18A*)eqp)->StatusEvol());
			strcat(reponse,buf);

			break;

		case EMR_SURVEILLANCE:
			iResult = 	!((CEquip18A*)eqp)->Local();
			if(((CEquip18A*)eqp)->PanneEmr()) iResult |= 2;
			if(((CEquip18A*)eqp)->PanneAccord()) iResult |= 4;

			sprintf(reponse,"E%1X",iResult);
			break;

		case EMR_STATUS:
			TraiteTS(EMR_SURVEILLANCE,reponse);

			// status 1
			iResult = 		((CEquip18A*)eqp)->HfRecu()
						+	((((CEquip18A*)eqp)->Ros())<<1)
						+	((((CEquip18A*)eqp)->Emission())<<2)
						+	((((CEquip18A*)eqp)->Silence())<<3);

			sprintf(buf,"%1X",iResult);
			strcat(reponse,buf);

			// status 2
			iResult = 		((CEquip18A*)eqp)->Chiffre()
						+	((((CEquip18A*)eqp)->TestEnCours())<<1)
						+	((((CEquip18A*)eqp)->Scan())<<2)
						+	((((CEquip18A*)eqp)->Accord())<<3);

			sprintf(buf,"%1X",iResult);
			strcat(reponse,buf);

			// Evolution
			iResult = 		((CEquip18A*)eqp)->StatusEvol();

			sprintf(buf,"%1X",iResult);
			strcat(reponse,buf);

			break;

		default:
			iResult = ERR_CDE_INCONNUE;
			break;
	}

	return iResult;
}

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Retourne toujours TRUE (pas d'acquittement attendu)
***************************************************************************	*/
BOOL CProto18A::ValideAcquittement(int type_cde,char *buf)
{
	return TRUE;
}

/* **************************************************************************
METHODE :		ControleTrame()
TRAITEMENT:		Génére un octet de controle.
***************************************************************************	*/
char* CProto18A::ControleTrame(char *message,char *octet_controle)
{
	int		i,len_mes,iResult;
	char	pc;

	strcpy(octet_controle,"F");

	if(erreur_com.controle_parite) return octet_controle;

	len_mes = (int)strlen(message);

	pc = 0;
	i=0;
	while(i<len_mes)
	{	
		sscanf(message+i,"%1X",&iResult);
		pc = (pc ^ iResult) & 0xF;
		if(pc<8)	pc <<= 1;
		else
		{
			pc<<= 1;
			pc++;
		}
		pc &= 0xF;
		i++;
	}
	sprintf(octet_controle,"%1X",pc);
	return octet_controle;
}

/* **************************************************************************
METHODE :		ExtraitUtile()
TRAITEMENT:		Extrait la partie utile d'une trame de télécommande
***************************************************************************	*/
BOOL CProto18A::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	char 	adr[6];
	int		i;
	char 	octet_controle[2];
	int		len_mes;

	len_mes = (int)strlen(buf);		
	if(buf[0] != SOH && buf[len_mes -1] != ETX)
		return FALSE;

	strncpy(adr,buf+1,4); adr[4]=0;	// Force la fin de chaine
	
	ControleTrame(adr,octet_controle);
	if(!erreur_com.controle_parite)
		if(buf[5]!=octet_controle[0]) return FALSE;
	
	sscanf(adr,"%2X",&i);
	if(i!=(((CEquip18A*)eqp)->Numero())) return FALSE;

	if(buf[6]!=STX) return FALSE;

	strcpy(message,buf+7);

	if(message[(int)strlen(message)-1]!=ETX) return FALSE;
	message[(int)strlen(message) - 2]=0; // Ote les caracteres non utiles

	*long_utile = (int)strlen(message);

	ControleTrame(message,octet_controle);
	if(!erreur_com.controle_parite)
		if(buf[7+(int)strlen(message)]!=octet_controle[0]) return FALSE;

	return TRUE;
}
/* **************************************************************************
METHODE :		CanalLecture()
TRAITEMENT:		Retourne le n° de canal pour utiliser lors de l'envoi des TS
***************************************************************************	*/
int CProto18A::CanalLecture()
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
BOOL CProto18A::ChangeCanalLecture(int	valeur)
{
	if(valeur<0 || valeur > 99) return FALSE;
	
	EnterCriticalSection(&crit);
		lecture_canal = valeur;
	LeaveCriticalSection(&crit);

	return TRUE;
}
