/* **************************************************************************
FICHIER :	P_251.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CProto251
***************************************************************************	*/

#include "stdafx.h"

#include "Comm\p_251.h"
#include "Equip\Eqp251.h"
#include "divers\div_tmp.h"

const int 	DEBUT_TRAME = 0xD;
const int 	FIN_TRAME 	= 0xA;

/* **************************************************************************
METHODE :		CProto251()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CProto251::CProto251(t_format fmt,CEquip *pEqp):CProto(fmt,pEqp)
{
	hexa = TRUE;

	lecture_canal		= 0;
	config_canal		=0;
}

/* **************************************************************************
METHODE :		~CProto251()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CProto251::~CProto251()
{
}

/* **************************************************************************
METHODE :		EnvoyerTS()
TRAITEMENT:		Prend un message TS, l'encapsule en fonction du protocole
				et l'envoi sur la ligne
***************************************************************************	*/
int CProto251::EnvoyerTS(char *message)
{
	int		i,len_mes,iResult;
	int		nb_car_enveloppe;		// Nombre de caractère envlopant le message

	char	buf[TAILLE_BUFFER+1];
	char	octet_controle[8];

	if(((CEquip251*)eqp)->Telecommande()==0 && strcmp(message,"\001\005")!=0)
	{
		iResult = ligne.Ecrire(message);
		if(iResult < 0) return ERREUR_EXTERNE+iResult;
		return iResult;
	}
	len_mes = message[0];			// Taille du message à envoyer
	nb_car_enveloppe = 1 + 1 + len_mes/9 + ((len_mes%9)!=0) + 1; 	// Debut Trame + long message + Fin Trame
												// n  PC par tranche de 8 car
	if(len_mes+nb_car_enveloppe > TAILLE_BUFFER)
		 return ERR_TAILLE_BUFFER;
	
	buf[0] = DEBUT_TRAME;
	for(i=0 ; i<=len_mes ; i++)
		buf[i+1]=message[i];

	ControleTrame(message,octet_controle);
	for(i=0 ; i<len_mes/9 + ((len_mes%9)!=0) ; i++)
		buf[i+1+1+len_mes] = octet_controle[i];

	buf[len_mes+nb_car_enveloppe-1] = FIN_TRAME;
	buf[len_mes+nb_car_enveloppe]=0;				// Force la fin de chaine

	if(erreur_com.pas_debut) buf[0]=0x20;
	if(erreur_com.pas_fin) buf[len_mes+nb_car_enveloppe-1]=0;
	
	for(i=erreur_com.pas_debut ; i<len_mes+nb_car_enveloppe ; i++)
	{
		iResult = ligne.EcritCar(buf[i]);
		if(iResult < 0) return ERREUR_EXTERNE+iResult;
	}
	return i;  // nb d'octet transmis
}
/* **************************************************************************
METHODE :		TraiteTC()
TRAITEMENT:		Traite une TC (Octet longueur + partie utile) et formate le 
				message TS reponse comme acquitement
***************************************************************************	*/
int CProto251::TraiteTC(char *mes)
{
	int		iResult = 0;
	int		i;
	char	reponse[TAILLE_PIPE_MESSAGE+1];
	int		tab_voie[REC_251_NB_VOIE];
	int		tab1_val[REC_251_NB_VOIE];
	int		tab2_val[REC_251_NB_VOIE];

	int		maj1,maj2;

	strcpy(reponse,"");

	if((((CEquip251*)eqp)->Local()==0) && mes[1]!=0x5 && mes[1]!=0xA) return ERR_PAS_ACQUITTE;
	if((((CEquip251*)eqp)->Telecommande()==0) && mes[1]!=0x5) return ERR_PAS_ACQUITTE;

	switch(mes[1])
	{
		case 0x5:
			AjouterTS(NULL,REC_251_ACK);
			iResult = ((CEquip251*)eqp)->ChangeTelecommande(1,TRUE);
			break;


		case 0xA:
			AjouterTS(NULL,REC_251_MODE_LOCAL);
			AjouterTS(NULL,REC_251_CONFIG_OP);
			iResult = 0;
			break;

		case 0x34:
			if(mes[(int)strlen(mes)-1] != 0x2E)
			{
				iResult = ERR_NON_CONFORME;
				break;
			}

			if(ConfigCanal()==0)
			{
			 	((CEquip251*)eqp)->ChangeCanal(0,FALSE);
			 	ChangeCanalLecture(0);
			}

			iResult = ((CEquip251*)eqp)->VoieActive(ConfigCanal(),tab_voie);
			iResult = ((CEquip251*)eqp)->Polarite(ConfigCanal(),tab1_val);
			iResult = ((CEquip251*)eqp)->Interface(ConfigCanal(),tab2_val);

			i=0;
			while(mes[2+i]>=0x31 && mes[2+i]<=0x39)
			{
				switch(mes[2+i])
				{
					case 0x31:
					case 0x32:
					case 0x34:
						if(tab_voie[mes[2+i]-0x31])
						{
							tab1_val[mes[2+i]-0x31] = !tab1_val[mes[2+i]-0x31];
							((CEquip251*)eqp)->ChangePolarite(0,tab1_val,FALSE);
							((CEquip251*)eqp)->ChangePolarite(ConfigCanal(),tab1_val,FALSE);
							if(!CanalLecture())
								TraiteTS(REC_251_POLARITE,reponse);
							else
								TraiteTS(REC_251_POLARITE_CANAL,reponse);

							EnvoyerTS(reponse);

						}
						break;
					case 0x33:
						if(tab_voie[mes[2+i]-0x31])
						{
							tab1_val[mes[2+i]-0x31] = !tab1_val[mes[2+i]-0x31];
							((CEquip251*)eqp)->ChangePolarite(0,tab1_val,FALSE);
							((CEquip251*)eqp)->ChangePolarite(ConfigCanal(),tab1_val,FALSE);

							if(!CanalLecture())
								TraiteTS(REC_251_POLARITE,reponse);
							else
								TraiteTS(REC_251_POLARITE_CANAL,reponse);

							EnvoyerTS(reponse);
						}
						else
						{
							if(((CEquip251*)eqp)->ModeRecep(ConfigCanal())== 6)// MSK2
							{
								tab2_val[1] = !tab2_val[1];			// action V2
								((CEquip251*)eqp)->ChangeInterface(0,tab2_val,FALSE);
								((CEquip251*)eqp)->ChangeInterface(ConfigCanal(),tab2_val,FALSE);

								if(!CanalLecture())
									TraiteTS(REC_251_MODE_INTERFACE,reponse);
								else
									TraiteTS(REC_251_MODUL_INTERF_CANAL,reponse);

								EnvoyerTS(reponse);

								if(!CanalLecture())
									TraiteTS(REC_251_POLARITE,reponse);
								else
									TraiteTS(REC_251_POLARITE_CANAL,reponse);
					
								EnvoyerTS(reponse);
							}

							iResult = ((CEquip251*)eqp)->ModeRecep(ConfigCanal());
							if(iResult>=2 && iResult <=5)			// MSK1,F1,CPFSK
							{
								tab2_val[3] = !tab2_val[3];			// action V4
								((CEquip251*)eqp)->ChangeInterface(0,tab2_val,FALSE);
								((CEquip251*)eqp)->ChangeInterface(ConfigCanal(),tab2_val,FALSE);

								if(!CanalLecture())
									TraiteTS(REC_251_MODE_INTERFACE,reponse);
								else
									TraiteTS(REC_251_MODUL_INTERF_CANAL,reponse);

								EnvoyerTS(reponse);

								if(!CanalLecture())
									TraiteTS(REC_251_POLARITE,reponse);
								else
									TraiteTS(REC_251_POLARITE_CANAL,reponse);
					
								EnvoyerTS(reponse);
							}
						}
						break;

					case 0x37:
					case 0x38:
					case 0x39:
						if(((CEquip251*)eqp)->ModeRecep(ConfigCanal()) == 7) 	// MSK4
						{
							tab2_val[mes[2+i]-0x36] = !tab2_val[mes[2+i]-0x36];
							((CEquip251*)eqp)->ChangeInterface(0,tab2_val,FALSE);
							((CEquip251*)eqp)->ChangeInterface(ConfigCanal(),tab2_val,FALSE);

							if(!CanalLecture())
								TraiteTS(REC_251_MODE_INTERFACE,reponse);
							else
								TraiteTS(REC_251_MODUL_INTERF_CANAL,reponse);

							EnvoyerTS(reponse);

							if(!CanalLecture())
								TraiteTS(REC_251_POLARITE,reponse);
							else
								TraiteTS(REC_251_POLARITE_CANAL,reponse);
				
							EnvoyerTS(reponse);

						}
						break;
				}
				i++;
			}
			iResult = 0;
			break;



		case 0x31:
			maj1 = maj2 = 0;
			iResult = sscanf(mes+2,"%2d%3d",&maj1,&maj2);

			// Changement de frequence
			if((iResult==2) && mes[7]==0x0D)
			{
				iResult = ((CEquip251*)eqp)->Canal();
				iResult = ((CEquip251*)eqp)->ChangeFrequence(CanalLecture(),maj1*1000 + maj2,FALSE);
				if(!CanalLecture())
					AjouterTS(NULL,REC_251_FREQUENCE);
				else
					AjouterTS(NULL,REC_251_FREQUENCE_CANAL);

			}
			else
			{
				iResult = ((CEquip251*)eqp)->Canal();
				if(iResult!=0)			// Canal en cours de Lecture
				{
					// Message 29E
					if(mes[2]==0)
					{
						ChangeConfigCanal(iResult);
						break;
					}
					// Message 28
					if(mes[3]==0x2E)
					{
						switch(mes[2])
						{
							case 0x31:
								iResult = ((CEquip251*)eqp)->ChangeModeRecep(CanalLecture(),7,FALSE);
								break;
							case 0x32:
								iResult = ((CEquip251*)eqp)->ChangeModeRecep(CanalLecture(),6,FALSE);
								break;
							case 0x33:
								iResult = ((CEquip251*)eqp)->ChangeModeRecep(CanalLecture(),5,FALSE);
								break;
							case 0x34:
								iResult = ((CEquip251*)eqp)->ChangeModeRecep(CanalLecture(),4,FALSE);
								break;
							case 0x35:
								iResult = ((CEquip251*)eqp)->ChangeModeRecep(CanalLecture(),3,FALSE);
								break;
							case 0x36:
								iResult = ((CEquip251*)eqp)->ChangeModeRecep(CanalLecture(),2,FALSE);
								break;
							case 0x37:
								iResult = ((CEquip251*)eqp)->ChangeModeRecep(CanalLecture(),1,FALSE);
								break;
							case 0x39:
								iResult = ((CEquip251*)eqp)->ChangeModeRecep(CanalLecture(),0,FALSE);
								break;
						}
						if(!CanalLecture())
						{
							AjouterTS(NULL,REC_251_LIMITTEUR);
							AjouterTS(NULL,REC_251_MODE_INTERFACE);
							AjouterTS(NULL,REC_251_POLARITE);
						}
						else
						{
							AjouterTS(NULL,REC_251_MODUL_INTERF_CANAL);
							AjouterTS(NULL,REC_251_POLARITE_CANAL);
						}

					}
					else
						iResult = ERR_NON_CONFORME;
				}
				else
					iResult = ERR_NON_CONFORME;
			}

			break;

		case 0x32:
			if(CanalLecture()!=0 && ConfigCanal()==0) // En fonction Lecture canal
			{
				iResult = sscanf(mes+2,"%2d",&maj1);
				if((iResult==1) && mes[4]==0x0D)
				{
					iResult = CanalLecture();
					iResult = ((CEquip251*)eqp)->MemoriseCanal(iResult,TRUE);
				}
			}
			else			// Config canal ou param operationnel
			{
				if(ConfigCanal()==0)
				{
			 		((CEquip251*)eqp)->ChangeCanal(0,FALSE);
			 		ChangeCanalLecture(0);
				}

				maj1 = maj2 = 0;
				iResult = sscanf(mes+2,"%1d%2d",&maj1,&maj2);
				if((iResult==2) && mes[5]==0x0D)
				{
					iResult = ((CEquip251*)eqp)->ChangeBfo(0,maj1*1000 + maj2*10,FALSE);
					iResult = ((CEquip251*)eqp)->ChangeBfo(ConfigCanal(),maj1*1000 + maj2*10,TRUE);
				}
			}
			break;

		case 0x30:
			iResult = ((CEquip251*)eqp)->Trafic();
			if(mes[2]==0x0D)
				iResult = ((CEquip251*)eqp)->ChangeTrafic(!iResult,TRUE);
			break;

		case 0x35:
			iResult = ERR_NON_CONFORME;

			if(ConfigCanal()==0)
			{
			 	((CEquip251*)eqp)->ChangeCanal(0,FALSE);
			 	ChangeCanalLecture(0);
			}

			if(mes[3]==0x2E)
			{
				switch(mes[2])
				{
					case 0x32:
						iResult = ((CEquip251*)eqp)->ChangeAttenuation(0,0,FALSE);
						iResult = ((CEquip251*)eqp)->ChangeAttenuation(ConfigCanal(),0,FALSE);
						break;
					case 0x34:
						iResult = ((CEquip251*)eqp)->ChangeAttenuation(0,1,FALSE);
						iResult = ((CEquip251*)eqp)->ChangeAttenuation(ConfigCanal(),1,FALSE);
						break;
					case 0x36:
						iResult = ((CEquip251*)eqp)->ChangeAttenuation(0,2,FALSE);
						iResult = ((CEquip251*)eqp)->ChangeAttenuation(ConfigCanal(),2,FALSE);
						break;
				}
				if(!CanalLecture())
					AjouterTS(NULL,REC_251_ATTENUATION);
				else
					AjouterTS(NULL,REC_251_ATTENUATION_CANAL);
	
			}
			break;

		case 0x36:
			if(ConfigCanal()==0)
			{
			 	((CEquip251*)eqp)->ChangeCanal(0,FALSE);
			 	ChangeCanalLecture(0);
			}

			iResult = ((CEquip251*)eqp)->Limiteur(ConfigCanal());
			((CEquip251*)eqp)->ChangeLimiteur(0,!iResult,FALSE);
			((CEquip251*)eqp)->ChangeLimiteur(ConfigCanal(),!iResult,FALSE);

			if(ConfigCanal())
				AjouterTS(NULL,REC_251_LIMITTEUR);
			else
				AjouterTS(NULL,REC_251_LIMITEUR_CANAL);

			break;

		case 0x33:
			iResult = ERR_NON_CONFORME;

			if(ConfigCanal()==0)
			{
			 	((CEquip251*)eqp)->ChangeCanal(0,FALSE);
			 	ChangeCanalLecture(0);
			}

			if(mes[3]==0x2E)
			{
				switch(mes[2])
				{
					case 0x31:
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(0,7,FALSE);
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(ConfigCanal(),7,FALSE);
						break;
					case 0x32:
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(0,6,FALSE);
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(ConfigCanal(),6,FALSE);
						break;
					case 0x33:
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(0,5,FALSE);
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(ConfigCanal(),5,FALSE);
						break;
					case 0x34:
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(0,4,FALSE);
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(ConfigCanal(),4,FALSE);
						break;
					case 0x35:
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(0,3,FALSE);
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(ConfigCanal(),3,FALSE);
						break;
					case 0x36:
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(0,2,FALSE);
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(ConfigCanal(),2,FALSE);
						break;
					case 0x37:
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(0,1,FALSE);
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(ConfigCanal(),1,FALSE);
						break;
					case 0x39:
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(0,0,FALSE);
						iResult = ((CEquip251*)eqp)->ChangeModeRecep(ConfigCanal(),0,FALSE);
						break;
				}
				if(!ConfigCanal())
				{
					AjouterTS(NULL,REC_251_LIMITTEUR);
					AjouterTS(NULL,REC_251_MODE_INTERFACE);
					AjouterTS(NULL,REC_251_POLARITE);
				}
				else
				{
					AjouterTS(NULL,REC_251_LIMITEUR_CANAL);
					AjouterTS(NULL,REC_251_MODUL_INTERF_CANAL);
					AjouterTS(NULL,REC_251_POLARITE_CANAL);
				}

			}
			break;

		case 0x38:
			iResult = ERR_NON_CONFORME;
			maj1 = 0;
			iResult = sscanf(mes+2,"%2d",&maj1);
			if((iResult==1) && mes[4]==0x0D)
				iResult = ((CEquip251*)eqp)->MemoriseCanal(maj1,FALSE);
			break;

		case 0x37:
			iResult = ERR_NON_CONFORME;
			maj1 = 0;
			iResult = sscanf(mes+2,"%2d",&maj1);
			if(iResult==1)
			{
				// Sauvegarde des param op dans canal 100
				iResult = ((CEquip251*)eqp)->MemoriseCanal(100,FALSE);

				iResult = ((CEquip251*)eqp)->ChangeCanal(maj1,TRUE);
				iResult = ChangeCanalLecture(maj1);
			}
			break;

		case 0x0D:
			if(ConfigCanal() == 0)
			{
				iResult = CanalLecture();

				iResult = ((CEquip251*)eqp)->ChangeCanal(iResult,FALSE);
				iResult = ChangeCanalLecture(0);
				iResult = ((CEquip251*)eqp)->ChangeCanal(0,FALSE);

				AjouterTS(NULL,REC_251_LIMITTEUR);
				AjouterTS(NULL,REC_251_SORTIE_CANAL);
				AjouterTS(NULL,REC_251_FREQUENCE);
				AjouterTS(NULL,REC_251_FREQ_BFO);
				AjouterTS(NULL,REC_251_LIMITTEUR);
				AjouterTS(NULL,REC_251_CAG);
				AjouterTS(NULL,REC_251_ATTENUATION);
				AjouterTS(NULL,REC_251_MODE_INTERFACE);
				AjouterTS(NULL,REC_251_POLARITE);
			}
			break;

		case 0x2E:
			iResult = ERR_NON_CONFORME;
			if(ConfigCanal()!=0) // Canal en cours de modif
			{
				ChangeConfigCanal(0);
				iResult = 0;
			}
			else
			{
				if(CanalLecture()!=0) // Canal en cours de modif
				{
					// Restauration des param operationnel
					iResult = ((CEquip251*)eqp)->ChangeCanal(100,FALSE);

					iResult = ((CEquip251*)eqp)->ChangeCanal(0,FALSE);
					iResult = ChangeCanalLecture(0);
					AjouterTS(NULL,REC_251_SORTIE_CANAL);
					iResult = 0;
				}
			}
			break;

		case 0x39:
			iResult = ((CEquip251*)eqp)->ChangeEtatTest(2,FALSE);
			TraiteTS(REC_251_ETAT_TEST,reponse);
			EnvoyerTS(reponse);
			Sleep(TEMPO_TRAVAIL);

			iResult = ((CEquip251*)eqp)->ChangeEtatTest(1,FALSE);
			TraiteTS(REC_251_ETAT_TEST,reponse);
			EnvoyerTS(reponse);
			Sleep(TEMPO_TRAVAIL);

			iResult = ((CEquip251*)eqp)->ChangeEtatTest(0,FALSE);
			AjouterTS(NULL,REC_251_LIMITTEUR);
			AjouterTS(NULL,REC_251_FREQUENCE);
			AjouterTS(NULL,REC_251_FREQ_BFO);
			AjouterTS(NULL,REC_251_LIMITTEUR);
			AjouterTS(NULL,REC_251_CAG);
			AjouterTS(NULL,REC_251_ATTENUATION);
			AjouterTS(NULL,REC_251_MODE_INTERFACE);
			AjouterTS(NULL,REC_251_POLARITE);
			AjouterTS(NULL,REC_251_MODE_LOCAL);
			break;

		case 0x20:
			iResult = ((CEquip251*)eqp)->ChangeAutoAlarme(0,FALSE);
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
int CProto251:: TraiteTS(int type_REC,char *reponse)
{
	int		iResult,num_canal;

	int		tab_val[REC_251_NB_VOIE];

	strcpy(reponse,"");
	switch(type_REC)
	{

		case REC_251_INIT:
			strcpy(reponse,"\r**** Chaine d'initialisation du TRC251 ");
			iResult = 40;
			break;

		case REC_251_ENQ:
			sprintf(reponse,"%c%c",1,5);
			iResult = 2;
			break;

		case REC_251_ACK:
			sprintf(reponse,"%c%c",1,6);
			iResult = 2;
			break;

		case REC_251_BEL:
			sprintf(reponse,"%c%c",1,7);
			iResult = 2;
			break;

		case REC_251_CONFIG_OP:
			sprintf(reponse,"%c%c%c%3.3d.%3.3d%1d.%3.3d%c%c%c%c",
				20,
				0x3C,
				((CEquip251*)eqp)->Trafic(),
				((CEquip251*)eqp)->Frequence(0)/1000,
				((CEquip251*)eqp)->Frequence(0)%1000,
				((CEquip251*)eqp)->Bfo(0)/1000,
				((CEquip251*)eqp)->Bfo(0)%1000,
				4-((CEquip251*)eqp)->Limiteur(0),
				6-((CEquip251*)eqp)->Cag(0),
				((CEquip251*)eqp)->Attenuation(0),
				1+((CEquip251*)eqp)->ModeRecep(0));

				((CEquip251*)eqp)->Interface(0,tab_val);
				reponse[19] = tab_val[3]+2*tab_val[2]+4*tab_val[1];

				((CEquip251*)eqp)->Polarite(0,tab_val);
				reponse[20] = tab_val[3]+2*tab_val[2]+4*tab_val[1]+8*tab_val[0];

				reponse[21] = 0;

			iResult = 21;
			break;

		case REC_251_POLARITE:
			sprintf(reponse,"%c%c",
				2,
				0x3D);

				((CEquip251*)eqp)->Polarite(0,tab_val);
				reponse[2] = tab_val[3]+2*tab_val[2]+4*tab_val[1]+8*tab_val[0];

				reponse[3] = 0;

			iResult = 3;
			break;

		case REC_251_FREQUENCE:
			sprintf(reponse,"%c%c%3.3d.%3.3d",
				8,
				0x3F,
				((CEquip251*)eqp)->Frequence(0)/1000,
				((CEquip251*)eqp)->Frequence(0)%1000);
			iResult = 9;
			break;

		case REC_251_FREQ_BFO:
			sprintf(reponse,"%c%c%1d.%3.3d",
				6,
				0x40,
				((CEquip251*)eqp)->Bfo(0)/1000,
				((CEquip251*)eqp)->Bfo(0)%1000);
			iResult = 7;
			break;

		case REC_251_TRAFIC:
			sprintf(reponse,"%c%c%c",
				2,
				0x41,
				((CEquip251*)eqp)->Trafic());
			iResult = 3;
			break;

		case REC_251_ATTENUATION:
			sprintf(reponse,"%c%c%c",
				2,
				0x42,
				((CEquip251*)eqp)->Attenuation(0));
			iResult = 3;
			break;

		case REC_251_LIMITTEUR:
			sprintf(reponse,"%c%c%c",
				2,
				0x43,
				4-((CEquip251*)eqp)->Limiteur(0));
			iResult = 3;
			break;

		case REC_251_MODE_INTERFACE:
			iResult = ((CEquip251*)eqp)->ModeRecep(0);
			sprintf(reponse,"%c%c%c",
				3,
				0x44,
				1+iResult+(iResult>7)*2);

				((CEquip251*)eqp)->Interface(0,tab_val);
				reponse[3] = tab_val[3]+2*tab_val[2]+4*tab_val[1];

				reponse[4] = 0;

			iResult = 4;
			break;

		case REC_251_ENTREE_CANAL:
			sprintf(reponse,"%c%c%2.2d",
				3,
				0x46,
				CanalLecture());

			iResult = 4;
			break;

		case REC_251_POLARITE_CANAL:
			num_canal = CanalLecture();

			sprintf(reponse,"%c%c",
				2,
				0x47);

				((CEquip251*)eqp)->Polarite(num_canal,tab_val);
				reponse[2] = tab_val[3]+2*tab_val[2]+4*tab_val[1]+8*tab_val[0];

				reponse[3] = 0;

			iResult = 3;
			break;

		case REC_251_SORTIE_CANAL:
			sprintf(reponse,"%c%c",
				1,
				0x48);

			iResult = 2;
			break;

		case REC_251_FREQUENCE_CANAL:
			num_canal = CanalLecture();
			sprintf(reponse,"%c%c%3.3d.%3.3d",
				8,
				0x49,
				((CEquip251*)eqp)->Frequence(num_canal)/1000,
				((CEquip251*)eqp)->Frequence(num_canal)%1000);
			iResult = 9;
			break;

		case REC_251_FREQ_BFO_CANAL:
			num_canal = CanalLecture();

			sprintf(reponse,"%c%c%1d.%3.3d",
				6,
				0x4A,
				((CEquip251*)eqp)->Bfo(num_canal)/1000,
				((CEquip251*)eqp)->Bfo(num_canal)%1000);
			iResult = 7;
			break;

		case REC_251_ATTENUATION_CANAL:
			num_canal = CanalLecture();

			sprintf(reponse,"%c%c%c",
				2,
				0x4C,
				((CEquip251*)eqp)->Attenuation(num_canal));
			iResult = 3;
			break;

		case REC_251_LIMITEUR_CANAL:
			num_canal = CanalLecture();

			sprintf(reponse,"%c%c%c",
				2,
				0x4D,
				4-((CEquip251*)eqp)->Limiteur(num_canal));
			iResult = 3;
			break;
		case REC_251_MODUL_INTERF_CANAL:
			num_canal = CanalLecture();

			sprintf(reponse,"%c%c%c",
				3,
				0x4E,
				1+((CEquip251*)eqp)->ModeRecep(num_canal));

				((CEquip251*)eqp)->Interface(num_canal,tab_val);
				reponse[3] = tab_val[3]+2*tab_val[2]+4*tab_val[1];

				reponse[4] = 0;

			iResult = 4;
			break;

		case REC_251_STOCKAGE_CANAL:
			sprintf(reponse,"%c%c",
				1,
				0x50);

			iResult = 2;
			break;

		case REC_251_ETAT_TEST:
			sprintf(reponse,"%c%c",
				1,
				0x53 - ((CEquip251*)eqp)->EtatTest());

			iResult = 2;
			break;

		case REC_251_CAG:
			sprintf(reponse,"%c%c%c",
				2,
				0x6E,
				6-((CEquip251*)eqp)->Cag(0));
			iResult = 3;
			break;

		case REC_251_SYNCHRONISATION_BIT:
			sprintf(reponse,"%c%c%c%c",
				3,
				0x6F,
				0,
				((CEquip251*)eqp)->EtatSynchro());
			iResult = 4;
			break;

		case REC_251_SYNCHRONISATION_TRAME1:
			((CEquip251*)eqp)->SynchroTrame(tab_val);

			sprintf(reponse,"%c%c%c%c",
				3,
				0x6F,
				1,
				2*tab_val[0]);
			iResult = 4;
			break;

		case REC_251_SYNCHRONISATION_TRAME2:
			((CEquip251*)eqp)->SynchroTrame(tab_val);

			sprintf(reponse,"%c%c%c%c",
				3,
				0x6F,
				2,
				2*tab_val[1]);
			iResult = 4;
			break;

		case REC_251_SYNCHRONISATION_TRAME3:
			((CEquip251*)eqp)->SynchroTrame(tab_val);

			sprintf(reponse,"%c%c%c%c",
				3,
				0x6F,
				3,
				2*tab_val[2]);
			iResult = 4;
			break;

		case REC_251_SYNCHRONISATION_TRAME4:
			((CEquip251*)eqp)->SynchroTrame(tab_val);

			sprintf(reponse,"%c%c%c%c",
				3,
				0x6F,
				4,
				2*tab_val[3]);
			iResult = 4;
			break;

		case REC_251_QUALITE_BIT:
			sprintf(reponse,"%c%c%c%c",
				3,
				0x70,
				((CEquip251*)eqp)->QBitMini(),
				((CEquip251*)eqp)->QBitMaxi());
			iResult = 4;
			break;

		case REC_251_NOTE_FIBO1:
			((CEquip251*)eqp)->Fibo(tab_val);
			sprintf(reponse,"%c%c%c%c",
				3,
				0x71,
				1,
				tab_val[0]);
			iResult = 4;
			break;

		case REC_251_NOTE_FIBO2:
			((CEquip251*)eqp)->Fibo(tab_val);
			sprintf(reponse,"%c%c%c%c",
				3,
				0x71,
				2,
				tab_val[1]);
			iResult = 4;
			break;

		case REC_251_NOTE_FIBO3:
			((CEquip251*)eqp)->Fibo(tab_val);
			sprintf(reponse,"%c%c%c%c",
				3,
				0x71,
				3,
				tab_val[2]);
			iResult = 4;
			break;

		case REC_251_NOTE_FIBO4:
			((CEquip251*)eqp)->Fibo(tab_val);
			sprintf(reponse,"%c%c%c%c",
				3,
				0x71,
				4,
				tab_val[3]);
			iResult = 4;
			break;

		case REC_251_NUM_PEIGNE:
			
			sprintf(reponse,"%c%c%c",
				2,
				0x72,
				4*(((CEquip251*)eqp)->Peigne())+2*(((CEquip251*)eqp)->Vitesse()));
			iResult = 3;
			break;

		case REC_251_DEFAUT:
			sprintf(reponse,"%c%c%2.2d%c%c%c%c",
				7,
				0x73,
				((CEquip251*)eqp)->Defaut(),

				4*((CEquip251*)eqp)->DefautCarte1() 
				+ 2*((CEquip251*)eqp)->DefautCarte2() 
				+	((CEquip251*)eqp)->DefautCarte3(),

				((CEquip251*)eqp)->DefautCarte1(),
				((CEquip251*)eqp)->DefautCarte2(),
				((CEquip251*)eqp)->DefautCarte3());
			iResult = 8;
			break;

		case REC_251_MODE_LOCAL:
			sprintf(reponse,"%c%c",
				1,
				0x74 + ((CEquip251*)eqp)->Local());

			iResult = 2;
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
int CProto251::RecevoirTC(char *message,int nb_car)
{
	char	buf[TAILLE_BUFFER+1];
	int		i,iResult;

	if(nb_car > TAILLE_BUFFER) return ERR_TAILLE_BUFFER;

	i=0;
	while(i<2)
	{
		iResult = ligne.Lire(buf+i,1);
		if(iResult < 0) return ERREUR_EXTERNE+iResult;
		if(iResult == 0) return ERREUR_TIMEOUT;

		if(buf[0]==DEBUT_TRAME)	i++;
	}

// 1 tranche = 8 caractère utile + 1 PC sans oublier d'oter les
// caracteres de debut et de fin de trame
	if((1 + 1 + buf[1] + buf[1]/9 + ((buf[1]%9)!=0) + 1) > nb_car)
 		return ERR_TAILLE_BUFFER;

	iResult = ligne.Lire(buf+2,buf[1] + buf[1]/9 + ((buf[1]%9)!=0) + 1);
	if(iResult < 0) return ERREUR_EXTERNE+iResult;
	if(iResult == 0) return ERREUR_TIMEOUT;

	if(!((CEquip251*)eqp)->FinPhaseInit()) return ERR_NON_CONFORME;

	if(!ExtraitUtile(buf,message,&iResult)) 
		return ERR_NON_CONFORME;			// Message non conforme

	return iResult;
}

/* **************************************************************************
METHODE :		ValideAcquitement()
TRAITEMENT:		Attend un message d'acquitement du type de commande précedement
				envoyé comme TS Maitre
***************************************************************************	*/
BOOL CProto251::ValideAcquittement(int type_cde,char *buf)
{
	BOOL	bResult;

	bResult = TRUE;
	switch(type_cde)
	{
		case REC_251_ENQ:
			if(strcmp(buf,"\001\006") == 0)
				((CEquip251*)eqp)->ChangeTelecommande(1,TRUE);

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
char* CProto251::ControleTrame(char *message,char *octet_controle)
{
	int		i,len_mes;
	char	pc;

	strcpy(octet_controle,"");			//
	if(erreur_com.controle_parite) 	return octet_controle;

	len_mes = message[0];

	pc = 0;
	i=len_mes-1;
	while(i>=0)
	{	
		pc = pc ^ message[i+1];
		
		if((i) % 8 == 0)	// caract précedent = debut de tranche
		{
//			if(pc < 64) pc += 64;
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
BOOL CProto251::ExtraitUtile(char *buf,char *message,int *long_utile)
{
	char 	octet_controle[8];
	int		len_mes,nb_tranche;

// 1 tranche = 8 caractère utile + 1 PC sans oublier d'oter les
// caracteres de debut et de fin de trame
	len_mes = (1 + 1 + buf[1] + buf[1]/9 + ((buf[1]%9)!=0) + 1);

	if(buf[0] != DEBUT_TRAME && buf[len_mes -1] != FIN_TRAME)
		return FALSE;

	nb_tranche = (len_mes-2)/9 + ((len_mes-2)%9 != 0);

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
int CProto251::CanalLecture()
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
BOOL CProto251::ChangeCanalLecture(int	valeur)
{
	if(valeur<0 || valeur > 99) return FALSE;
	
	EnterCriticalSection(&crit);
		lecture_canal = valeur;
	LeaveCriticalSection(&crit);

	return TRUE;
}

/* **************************************************************************
METHODE :		CanalLecture()
TRAITEMENT:		Retourne le n° de canal pour utiliser lors de l'envoi des TS
***************************************************************************	*/
int CProto251::ConfigCanal()
{
	int	valeur;
	
	EnterCriticalSection(&crit);
		valeur = config_canal;
	LeaveCriticalSection(&crit);

	return valeur;
}

/* **************************************************************************
METHODE :		ChangeCanalLecture()
TRAITEMENT:		Force un n° de canal pour utiliser lors de l'envoi des TS
***************************************************************************	*/
BOOL CProto251::ChangeConfigCanal(int	valeur)
{
	if(valeur<0 || valeur>99) return FALSE;
	
	EnterCriticalSection(&crit);
		config_canal = valeur;
	LeaveCriticalSection(&crit);

	return TRUE;
}
