/* **************************************************************************
FICHIER :	AppelAle.cpp		 			AUTEUR : DGE
DATE DE CREATION : 	16/12/2009
VERSION :	1.0
ROLE :		Implémentation de la classe CAppelAle
***************************************************************************	*/

#include "stdafx.h"

#include "Equip\AppelAle.h"
#include "divers\Div_tmp.h"

#include <time.h> 


/* **************************************************************************
METHODE :		CAppelAle()
TRAITEMENT:		Constructeur
***************************************************************************	*/
CAppelAle::CAppelAle(CEquipM1752 *pEqp, string channel)
{
	eqp					= pEqp;
	this->channel		= channel;
	this->appel			= FALSE;
	this->fin_appel		= FALSE;
	this->amd_recu		= FALSE;
	this->amd_envoye	= FALSE;
	this->automate		= IDLE;
	Activer();
}

/* **************************************************************************
METHODE :		~CAppelAle()
TRAITEMENT:		Destructeur
***************************************************************************	*/
CAppelAle::~CAppelAle()
{
	int		iResult;
	BOOL	bResult;

	eqp->SetAleStatus(channel, DEFAULT_STRING_VALUE);
	eqp->SetAppel(channel, FALSE);

	iResult = Desactiver();

	if (Handle() != NULL) bResult = TerminateThread(Handle(),0);
}

/* **************************************************************************
METHODE :		Desactiver()
TRAITEMENT:		Termine le thread associé
***************************************************************************	*/
int CAppelAle::Desactiver()
{
	DWORD	dwResult;

	if(EtatTache() == THREAD_NON_CREE) return ERR_CTACHE;

	ChangeEtat(THREAD_NON_CREE);

	dwResult = WaitForSingleObject(Handle(),1000);
	if(dwResult == WAIT_TIMEOUT)
	{
		TerminateThread(Handle(),0);
	}

	return 0;
}

/* **************************************************************************
METHODE :		Traitement()
TRAITEMENT:		Déroulement de l'appel
***************************************************************************	*/
DWORD WINAPI CAppelAle::Traitement(void *param)
{
	TSst sst;
	int sst_parcours = 0;
	int calling_try = 0;
	int canal_calling = 0;
	TModemDistant modem;

	while (EtatTache() != THREAD_NON_CREE)
	{
		switch(automate)
		{
		case IDLE:
			{
				if (eqp->GetChannelType(channel) == "S")
				{
					eqp->SetAleStatus(channel,"SCA");
					automate = SCANNING;
				}

				if (eqp->GetChannelType(channel) == "C")
				{
					eqp->SetAleStatus(channel,"LIS");
					automate = LISTENING;
				}

				eqp->SetAppel(channel, FALSE);

				// Retour en réception -30
				eqp->SetReceptionDown(channel);

				continue;
			}
			break;
		case LISTENING:
			{
				// Si on doit passer en calling
				if (Calling()) continue;

				// Si on doit passer en receive call
				if (appel_recu == TRUE) 
				{
					automate = RECEIVING_CALL;
					appel_recu = FALSE;
					canal_calling = 0;
					continue;
				}

				// Si on doit envoyer un sound
				if (sound == TRUE)
				{
					sound = FALSE;
					automate = SOUNDING;
				}

				Sleep(WAIT_TIME);

				//RM
				eqp->EmissionOff(channel);
				
			}
			break;
		case SCANNING:
			{
				if (FALSE == eqp->GetSst(channel, eqp->GetChannelIndexScansetChannel(channel), sst)) eqp->FinAppel(channel);

				// Si on doit passer en calling
				if (Calling()) continue;

				// Si on doit passer en receive call
				if (appel_recu == TRUE) 
				{
					automate = RECEIVING_CALL;
					appel_recu = FALSE;
					canal_calling = 0;
					continue;
				}

				// Si on doit envoyer un sound
				if (sound == TRUE)
				{
					sound = FALSE;
					automate = SOUNDING;
				}

				// Parcours des scansets
				while (sst.scan_set_channel[sst_parcours] != TRUE) 
					sst_parcours = ((sst_parcours+1)%(NB_LIST_CHANNEL-1));

				eqp->SetAleChannelInScanset(channel, sst_parcours);
				sst_parcours = ((sst_parcours+1)%(NB_LIST_CHANNEL-1));

				//RM
				eqp->EmissionOff(channel);

				Sleep(SCANNING_TIME);
			}
			break;
		case CALLING:
			{
				// FDI - 13/04/2012
				if (eqp->GetAleSilence(channel) == "ON")
				{
					// retour en idle le modem est en silence
					automate = IDLE;
					continue;
				}

				canal_calling = 0;

				// Test si emetteur ok
				if (!eqp->IsEmetteurMarche() || eqp->IsEmetteurPanneTC())
				{
					// LKL rad ko
					eqp->SendLKL(channel, "RAD_KO");

					// retour en idle
					automate = IDLE;
					continue;
				}

				// On charge le premier canal a appeler
				if(eqp->GetChannelType(channel) == "C") 
				{
						canal_calling = eqp->GetChannelIndexScansetChannel(channel);
				} else
				{
					if (FALSE == eqp->GetSst(channel, eqp->GetChannelIndexScansetChannel(channel), sst)) eqp->FinAppel(channel);
					while (sst.scan_set_channel[canal_calling] != TRUE) 
						canal_calling++;

					eqp->SetAleChannelInScanset(channel, canal_calling);
				}
				
				// Pour chaque canal
				while(canal_calling>=0 && canal_calling<=99)
				{
					eqp->SetAleStatus(channel,"CAL");

					// Boucle appel par canal
					for(calling_try=0; calling_try<3; calling_try++)
					{
						eqp->SetReceptionDown(channel);
						eqp->EmissionOn(channel);

						Sleep(CALLING_TIME);

						// Test de conditions d'appel réussi
						if(TestCalling(canal_calling)) 
						{
							automate = RECEIVING_RESPONSE;
							break;
						}
						
					}

					// S'il reste un canal en scanset on le charge on reboucle
					if(automate == CALLING && eqp->GetChannelType(channel) == "S")
					{
						for(canal_calling++; canal_calling < 100; canal_calling++)
						{
							if (sst.scan_set_channel[canal_calling] == TRUE) 
							{
								eqp->SetAleChannelInScanset(channel, canal_calling);
								break;
							}
						}
					} else break;
					
				}

				// l'appel n'a pas reussi
				if (automate != RECEIVING_RESPONSE)
				{
					// LKL no answer
					eqp->SendLKL(channel, "NOANSWER");
					automate = IDLE;
				}
				
				eqp->SetReceptionDown(channel);
				eqp->EmissionOn(channel);
			}
			break;
		case RECEIVE_RESPONSE:
			{
				eqp->SetAleStatus(channel,"RRE");
				Sleep(RECEIVE_TIME);
				automate = SEND_ACKNOWNLEDGEMENT;

				
				eqp->EmissionOff(channel);
				eqp->SetReceptionUp(channel);
			}
			break;
		case SEND_ACKNOWNLEDGEMENT:
			{
				// FDI - 13/04/2012
				if (eqp->GetAleSilence(channel) == "ON")
				{
					// retour en idle le modem est en silence
					automate = IDLE;
					continue;
				}

				eqp->SetAleStatus(channel,"SAK");

				modem = eqp->GetModemDistant();
				modem.amd_chat_recu = eqp->GetAleParameter(channel).amd_message;
				eqp->SetModemDistant(modem);

				
				eqp->SetReceptionDown(channel);
				eqp->EmissionOn(channel);

				Sleep(SEND_TIME);
				automate = LINKED_CALLING;
				eqp->SetAleStatus(channel,"LKG");
				eqp->SetAleEstAppele(channel, false);
				
				eqp->EmissionOff(channel);
				eqp->SetReceptionUp(channel);

			}
			break;
		case LINKED_CALLING:
			{
				LinkAction();
				Sleep(WAIT_TIME);
			}
			break;
		case RECEIVING_RESPONSE:
			{
				eqp->SetAleStatus(channel,"REC");
				automate = RECEIVE_RESPONSE;

				
				eqp->EmissionOff(channel);
				eqp->SetReceptionUp(channel);
			}
			break;
		case RECEIVE_CALL:
			{
				if (TestAdresseAppelee() == TRUE)
				{
					eqp->SetAleStatus(channel,"RCA");

					if (TestAdresseAppelante() == TRUE)
						automate = SEND_RESPONSE;
				}

				// L'appel est tout bon ?
				if (automate != SEND_RESPONSE)
				{
					// On repart sur l'appel des autres canaux
					automate = RECEIVING_CALL;
					canal_calling++;
				}
				
				eqp->EmissionOff(channel);
				eqp->SetReceptionUp(channel);
			}
			break;
		case LINKED_CALLED:
			{
				LinkAction();
				Sleep(WAIT_TIME);
			}
			break;
		case SEND_RESPONSE:
			{
				// FDI - 13/04/2012
				if (eqp->GetAleSilence(channel) == "ON")
				{
					// retour en idle le modem est en silence
					automate = IDLE;
					continue;
				}

				eqp->SetAleStatus(channel,"SRE");
				Sleep(SEND_TIME);
				automate = LINKED_CALLED;

				
				eqp->SetReceptionDown(channel);
				eqp->EmissionOn(channel);

				eqp->SetAleStatus(channel,"LKD");
				eqp->SetAleEstAppele(channel, true);

				
				eqp->EmissionOff(channel);
				eqp->SetReceptionUp(channel);
			}
			break;
		case RECEIVING_CALL:
			{
				appel_recu = FALSE;
				modem = eqp->GetModemDistant();

				automate = IDLE;

				// Au moins un canal est choisi sinon l'appel ne sert à rien
				for(; canal_calling<10; canal_calling++) 
					if (modem.channel[canal_calling] == TRUE && modem.marche == TRUE)
					{
						automate = RECEIVE_CALL;
						break;
					}

				if (automate != IDLE)
				{
					// Premier canal trouvé
					// Appel
					automate = IDLE;

					// Pour chaque canaux
					while(canal_calling>=0 && canal_calling<=9)
					{
						// Boucle appel par canal
						for(calling_try=0; calling_try<3; calling_try++)
						{
							Sleep(CALLING_TIME);
							// Test de conditions de reception
							if(TestCanalCalled(canal_calling)) 
							{
								automate = RECEIVE_CALL;
								break;
							}
						
						}

						// S'il reste un canal en scanset
						if(automate == IDLE && modem.type_ale == "S")
						{
							for(canal_calling++; canal_calling < 10; canal_calling++)
							{
								if (modem.channel[canal_calling] == TRUE) 
									break;
							}
						} else break;	
					}

					// L'appel a abouti ?
					if (automate == RECEIVE_CALL)
					{
						eqp->SetAleChannelInScanset(channel, canal_calling);
						eqp->SetAleStatus(channel,"REC");
						
						eqp->EmissionOff(channel);
						eqp->SetReceptionUp(channel);
					}
				} else
				{
					
					eqp->EmissionOff(channel);
					eqp->SetReceptionDown(channel);
				}
				
				
			}
			break;
		case SOUNDING:
			{
				// FDI - 13/04/2012
				if (eqp->GetAleSilence(channel) == "ON")
				{
					// retour en idle le modem est en silence
					automate = IDLE;
					continue;
				}

				eqp->SetAleStatus(channel,"SOU");
				automate = IDLE;
				// Incrementation du sound prochain
				eqp->NextSound(channel);
				eqp->EmissionOn(channel);
				eqp->SetReceptionOff(channel);
				// FDI - 13/04/2012
				Sleep(15000);
				eqp->EmissionOff(channel);

			}
			break;
		case SEND_AMD:
			{
				// FDI - 13/04/2012
				if (eqp->GetAleSilence(channel) == "ON")
				{
					// retour en idle le modem est en silence
					automate = IDLE;
					continue;
				}

				eqp->EmissionOn(channel);
				eqp->SetAleStatus(channel,"SAM");
				Sleep(5000);
				eqp->EmissionOff(channel);
				automate = automate_prec;
			}
			break;
		case RECEIVING_AMD:
			{
				eqp->SetAleStatus(channel, "REC");
				eqp->EmissionOff(channel);
				eqp->SetReceptionUp(channel);

				Sleep(RECEIVE_TIME);

				eqp->SetAleStatus(channel,"RAM");
				eqp->SetReceptionDown(channel);
				automate = automate_prec;

			}
			break;
		default:
			Sleep(WAIT_TIME);
			break;
		}

	}						
	return 0;
}

/* **************************************************************************
METHODE :		LancerAppel()
TRAITEMENT:		Lance l'appel concerné
***************************************************************************	*/
void CAppelAle::LancerAppel()
{
	if (automate == SCANNING || automate == LISTENING)
		appel = TRUE;

	eqp->SetAppel(channel, TRUE);

}

/* **************************************************************************
METHODE :		FinAppel()
TRAITEMENT:		Termine l'operation en cours pour retomber en idle
***************************************************************************	*/
void CAppelAle::CasserAppel()
{
	if (automate == LINKED_CALLING || automate == LINKED_CALLED)
		fin_appel = TRUE;

	eqp->SetAppel(channel, FALSE);
}

/* **************************************************************************
METHODE :		RecevoirAppel()
TRAITEMENT:		Recoit un appel pdt la phase d'écoute
***************************************************************************	*/
void CAppelAle::RecevoirAppel()
{
	if (automate == SCANNING || automate == LISTENING)
		appel_recu = TRUE;

	eqp->SetAppel(channel, TRUE);
}

/* **************************************************************************
METHODE :		RecevoirAmd()
TRAITEMENT:		Recoit un amd pdt le link
***************************************************************************	*/
void CAppelAle::RecevoirAmd()
{
	if (automate == LINKED_CALLING || automate == LINKED_CALLED)
		amd_recu = TRUE;
}

/* **************************************************************************
METHODE :		EnvoyerAmd()
TRAITEMENT:		Envoi un amd pdt le link
***************************************************************************	*/
void CAppelAle::EnvoyerAmd()
{
	if (automate == LINKED_CALLING || automate == LINKED_CALLED)
		amd_envoye = TRUE;
}

/* **************************************************************************
METHODE :		Sounding()
TRAITEMENT:		Emettre un sounding
***************************************************************************	*/
void CAppelAle::Sounding()
{
	if (automate == LISTENING || automate == SCANNING)
		sound = TRUE;
}

/* **************************************************************************
METHODE :		Calling()
TRAITEMENT:		Verifie si le passage en calling est attendu et possible
***************************************************************************	*/
bool CAppelAle::Calling()
{
	// Si la liaison le permet, etablissement appel
	if (appel == TRUE) 
	{
		automate = CALLING;

		//if (eqp->GetChannelLinkManagementType(channel) == "LMANU")
		appel = FALSE;

		return TRUE;
	}

	return FALSE;
}

/* **************************************************************************
METHODE :		TestCalling()
TRAITEMENT:		Verifie les conditions pour que l'appel aboutisse
***************************************************************************	*/
bool CAppelAle::TestCalling(int canal)
{
	bool test_ok = FALSE;
	TModemDistant modem = eqp->GetModemDistant();
	TAleParameter ale = eqp->GetAleParameter(channel);
	string adresse_appelee;
	string adresse_perso;
	int i;

	if (modem.marche == FALSE) return FALSE;

	if(ale.link_protection_level != 0 ) //LP = 1 or 2
	{
		if(ale.link_protection_level != atoi(modem.LP[modem.current_LP].c_str()))return FALSE;
		if(eqp->GetTableLtName(channel,"LT0") != modem.LT0[modem.current_LT0])return FALSE;
		if(ale.key_position != atoi(modem.Key[modem.current_Key].c_str())-1)return FALSE;
	}
	else if (ale.link_protection_level == 0)
	{
		if(ale.link_protection_level != atoi(modem.LP[modem.current_LP].c_str()))return FALSE;
	}

	// Appel en STD
	if (ale.call_type == "STD")
	{
		TSta sta;

		// Recuperation adresse appelee
		if (!eqp->GetSta(channel, ale.called_address, sta)) return FALSE;
		adresse_appelee = sta.address_ale;

		// L'adresse appelée doit exister dans les selfaddress
		for(i=0; i<modem.selfaddress.size(); i++)
		{
			if (adresse_appelee == modem.selfaddress[i]) 
			{
				test_ok = TRUE;
				break;
			}
		}

	// Appel en NET
	} else if (ale.call_type == "NET")
	{
		TNet net;

		// Recuperation adresse reseau
		if (!eqp->GetNet(channel, ale.called_address, net)) return FALSE;
		adresse_appelee = net.net_address;

		// L'adresse reseau doit exister dans les net
		for(i=0; i<modem.reseaux.size(); i++)
		{
			if (adresse_appelee == modem.reseaux[i]) 
			{
				test_ok = TRUE;
				break;
			}
		}

	// Appel en ALL
	} else if (ale.call_type == "ALL") 
	{
		test_ok = TRUE;
	}

	// L'adresse appelée est elle bonne ?
	if (!test_ok) return FALSE;

	// Recuperation adresse perso
	TSad sad;

	if (!eqp->GetSad(channel,ale.index_selfaddress, sad)) return FALSE;
	adresse_perso = sad.self_address;

	test_ok = FALSE;

	// L'adresse perso doit exister dans les stations
	for(i=0; i<modem.stations.size(); i++)
		{
			if (adresse_perso == modem.stations[i]) 
			{
				test_ok = TRUE;
				break;
			}
		}

	// L'adresse perso est elle bonne ?
	if (!test_ok) return FALSE;

	// Verification presence du canal
	if (canal>=0 && canal<10 && modem.channel[canal] == TRUE) return TRUE;

	return FALSE;
}

/* **************************************************************************
METHODE :		TestCanalCalled()
TRAITEMENT:		Verifie que le canal sur lequel on recoit l'appel est bon
***************************************************************************	*/
bool CAppelAle::TestCanalCalled(int canal)
{
	TAleParameter ale = eqp->GetAleParameter(channel);
	TModemDistant modem = eqp->GetModemDistant();

	if(ale.link_protection_level != 0)//LP = 1 or 2
	{
		if(ale.link_protection_level!=atoi(modem.LP[modem.current_LP].c_str()))return FALSE;
		if(eqp->GetTableLtName(channel,"LT0")!=modem.LT0[modem.current_LT0])return FALSE;
		if(ale.key_position!=atoi(modem.Key[modem.current_Key].c_str())-1)return FALSE;
	}
	else if(ale.link_protection_level == 0)
	{
		if(ale.link_protection_level!=atoi(modem.LP[modem.current_LP].c_str()))return FALSE;
	}

	if (eqp->GetChannelType(channel) == "C")
	{
		if (canal != eqp->GetChannelIndexScansetChannel(channel)) return FALSE;
	}
	else if (eqp->GetChannelType(channel) == "S")
	{
		TSst sst;

		if (!eqp->GetSst(channel, eqp->GetChannelIndexScansetChannel(channel), sst)) return FALSE;

		if (sst.scan_set_channel[canal] != TRUE) return FALSE;
	}

	return TRUE;
}

/* **************************************************************************
METHODE :		TestAdresseAppelee()
TRAITEMENT:		Verifie que l'adresse appelée est la notre
***************************************************************************	*/
bool CAppelAle::TestAdresseAppelee()
{
	TModemDistant modem = eqp->GetModemDistant();
	string adresse_appelee;

	// Les indices doivent etre dans les bornes
	if (modem.current_reseau >= modem.reseaux.size()
		|| modem.current_station >= modem.stations.size()) return FALSE;

	// Appel en STD
	if (modem.type_appel == "STA")
	{
		// Recuperation de l'adresse appelée
		adresse_appelee = modem.stations[modem.current_station];

		// L'adresse doit exister dans les SAD de la voie
		if (eqp->GetSad(channel, adresse_appelee) == DEFAULT_INT_VALUE) return FALSE;

	// Appel en NET
	} else if (modem.type_appel == "NET")
	{
		// Recuperation du reseau appelée
		adresse_appelee = modem.reseaux[modem.current_reseau];

		// L'adresse doit exister dans les NET de la voie
		if (eqp->GetNet(channel, adresse_appelee) == DEFAULT_INT_VALUE) return FALSE;

	// Appel en ALL tjs ok
	}

	return TRUE;
}

/* **************************************************************************
METHODE :		TestAdresseAppelante()
TRAITEMENT:		Verifie que l'adresse qui nous appelle est connue
***************************************************************************	*/
bool CAppelAle::TestAdresseAppelante()
{
	TModemDistant modem = eqp->GetModemDistant();
	string adresse_appelante;

	// Les indices doivent etre dans les bornes
	if (modem.current_station >= modem.stations.size()) return FALSE;

	// Recuperation adresse appelante
	adresse_appelante = modem.selfaddress[modem.current_selfaddress];

	// L'adresse doit exister dans les STA de la voie
	if (eqp->GetSta(channel, adresse_appelante) == DEFAULT_INT_VALUE) return FALSE;

	return TRUE;
}

/* **************************************************************************
METHODE :		SetReceptionValueOn()
TRAITEMENT:		Place la qualité et le level af receive aux valeurs de reception
***************************************************************************	*/
void CAppelAle::SetReceptionValueOn()
{
	for (int i=eqp->GetChannelAfLevelReceived(channel); i<=-1; i++)
		eqp->SetChannelAfLevelReceived(channel, i);

	eqp->SetChannelQualityValue(channel, 30);
}

/* **************************************************************************
METHODE :		SetReceptionValueOff()
TRAITEMENT:		Place la qualité et le level af receive aux valeurs de veille
***************************************************************************	*/
void CAppelAle::SetReceptionValueOff()
{
	for (int i=eqp->GetChannelAfLevelReceived(channel); i>=-30; i--)
		eqp->SetChannelAfLevelReceived(channel, i);

	eqp->SetChannelQualityValue(channel, 0);
}

/* **************************************************************************
METHODE :		LinkAction()
TRAITEMENT:		Test les actions possible pdt un link
***************************************************************************	*/
void CAppelAle::LinkAction()
{
	// Verification appel tjs en cours
	if (fin_appel == TRUE)
	{
		SetReceptionValueOff();
		fin_appel = FALSE;
		automate = IDLE;
	}

	// On recoit un amd
	if (amd_recu == TRUE)
	{
		amd_recu = FALSE;
		automate_prec = automate;
		automate = RECEIVING_AMD;
	}
	
	// On envoi un amd
	if (amd_envoye == TRUE)
	{
		amd_envoye = FALSE;
		automate_prec = automate;
		automate = SEND_AMD;
	}

	Sleep(500);
}
