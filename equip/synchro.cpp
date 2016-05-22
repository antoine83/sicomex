/* **************************************************************************
FICHIER :	Synchro.CPP		 			AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
ROLE :		Implémentation de la classe CSynchro
***************************************************************************	*/

#include "stdafx.h"
#include "sicomex.h"
#include "synchro.h"
#include "divers\Div_tmp.h"
#include "ParamSim.h"

#include "DlgAccue.h"

const int	MAX_PIPE_INSTANCES 	= 100;
const int	IN_BUF_SIZE			= 64;
const int	OUT_BUF_SIZE       	= 64;

extern 	char glob_TOP[];
extern 	char glob_PIPE[];
extern  CParamSimu 	*glob_paramsimu;
extern	CDlgAccueil	*glob_ihm;

CSynchro::CSynchro()
{
	if (glob_paramsimu == NULL)
		return;

	int		ext,dep,per;

	event = CreateEvent(NULL,FALSE,FALSE,NULL);

	top = CreateEvent(NULL,TRUE,FALSE,glob_TOP);
	if(top == NULL)
	{
		if(GetLastError()==ERROR_ALREADY_EXISTS)
		{
			top = OpenEvent(SYNCHRONIZE,FALSE,glob_TOP);
		}
	}

	glob_paramsimu->Top_synchro(&ext,&dep,&per);
	depart = dep;
	periode = per;
}

CSynchro::~CSynchro()
{
	int		iResult;
	BOOL	bResult;

	iResult = Desactiver();

	CloseHandle(event);
	CloseHandle(top);

	if (Handle() != NULL) bResult = TerminateThread(Handle(),0);
}

int CSynchro::Activer()
{
	return CTache::Activer();
	return 0;
}

/* **************************************************************************
METHODE :		Change_Top()
TRAITEMENT:		Prévient le thread d'un modification des carcatéristique du
				top synchro
***************************************************************************	*/
void CSynchro::Change_Top()
{
	if (glob_paramsimu == NULL)
		return;

	int		ext,dep,per;

	Desactiver();
	glob_paramsimu->Top_synchro(&ext,&dep,&per);
	externe = ext;
	depart = dep;
	periode = per;
	Activer();
}

/* **************************************************************************
METHODE :		Desactiver()
TRAITEMENT:		Termine le thread associé
***************************************************************************	*/
int CSynchro::Desactiver()
{
	DWORD	dwResult;
	BOOL	bResult;

	if(EtatTache() == THREAD_NON_CREE) return ERR_CTACHE;

	ChangeEtat(THREAD_NON_CREE);
	PulseEvent(event);


	dwResult = WaitForSingleObject(Handle(),1000);
	//dwResult = WaitForSingleObject(Handle(),INFINITE);
	if(dwResult == WAIT_TIMEOUT)
	{
		bResult = TerminateThread(Handle(),0);
		Beep(840,100);
	}

	return 0;
}

/* **************************************************************************
METHODE :		Traitement()
TRAITEMENT:		Traitement à effecter dans le thread
***************************************************************************	*/
DWORD WINAPI CSynchro::Traitement(void *param)
{
    char    temps[25];
    char    message[80];
	int		offset = 0;			// Pour recallage du temps
	int		timeout;
	int		car_lu;
	int		i,iResult;
	DWORD	dwResult;
	
	if(!externe)
	{
		for(i=0 ; i<NB_MAX_PIPE ; i++)
		{
			sprintf(message,"%s%2.2d",glob_PIPE,i);
			pipe[i] = CreateNamedPipe(message,
				PIPE_ACCESS_DUPLEX,
				PIPE_WAIT | PIPE_READMODE_MESSAGE | PIPE_TYPE_MESSAGE,
               	MAX_PIPE_INSTANCES,
               	OUT_BUF_SIZE,
               	IN_BUF_SIZE,
               	1000,				// Timout
               	NULL);
		}
	}
	else
	{
		for(i=0 ; i<NB_MAX_PIPE ; i++)
		{
			sprintf(message,"%s%2.2d",glob_PIPE,i);
			pipe[0] = CreateFile (message,              // Pipe name.
                           GENERIC_WRITE          // Generic access, read/write.
                           | GENERIC_READ,
                           FILE_SHARE_READ        // Share both read and write.
                           | FILE_SHARE_WRITE ,
                           NULL,                  // No security.
                           OPEN_EXISTING,         // Fail if not existing.
                           NULL,  // Use overlap.
                           NULL);                 // No template.
			if((DWORD)pipe[0] != 0xFFFFFFFF) break;
		}
	}

	offset = Nb_milli(temps);
	while (EtatTache() != THREAD_NON_CREE)
	{
	
		if(externe)
		{
			dwResult = WaitForSingleObject(event,0);
			if(dwResult == WAIT_OBJECT_0)		// Desactivation du thread
			{
				ChangeEtat(THREAD_NON_CREE);
				break;
			}

			iResult = ReadFile(pipe[0],message,5,(DWORD*) &car_lu,NULL);	
			if(iResult<=0)
			{
				for(i=0 ; i<NB_MAX_PIPE ; i++)
				{
					sprintf(message,"%s%2.2d",glob_PIPE,i);
					pipe[0] = CreateFile (message,              // Pipe name.
		                           GENERIC_WRITE          // Generic access, read/write.
		                           | GENERIC_READ,
		                           FILE_SHARE_READ        // Share both read and write.
		                           | FILE_SHARE_WRITE ,
		                           NULL,                  // No security.
		                           OPEN_EXISTING,         // Fail if not existing.
		                           NULL,  // Use overlap.
		                           NULL);                 // No template.
					if((DWORD)pipe[0] != 0xFFFFFFFF) break;
				}
				if(i==NB_MAX_PIPE) Sleep(TEMPO_TRAVAIL);
				continue;
			}
			if(car_lu==0) continue;

			offset = Nb_milli(temps);
	        sprintf(message,"%s - Réception Top Synchro externe",
            	temps);

		}
		else
		{
			i=Nb_milli(temps);
			if((iResult = Conv_H_S(temps+9)) < depart - periode)
			{
				Sleep(500);
				offset = Nb_milli(temps);

				continue;
			}

			timeout = 1000*periode - (i+60000-offset)%60000;
			dwResult = WaitForSingleObject(event,timeout);
			offset = Nb_milli(temps);


	        sprintf(message,"%d",offset);
			for(i=0 ; i<NB_MAX_PIPE ; i++)
			{
				iResult = WriteFile(pipe[i],message,(int)strlen(message),(DWORD*) &car_lu,NULL);	
			}
	
	        sprintf(message,"%s - Déclenchement Top Synchronisation",
	           	temps);
		}

		if(dwResult == WAIT_TIMEOUT)		// Fin tempo
		{

			PulseEvent(top);
//			Beep(1320,100);

            if(EtatTache() != THREAD_NON_CREE)
            	glob_ihm->Ajout_message(message);

			continue;
		}

	}

	for(i=0 ; i<NB_MAX_PIPE ; i++)
	{
		CloseHandle(pipe[i]);
	}

	return 0; 
}

