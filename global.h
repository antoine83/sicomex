/* **********************************************************************FICHIER :	Global.h				 	AUTEUR : PhB
DATE DE CREATION : 	13/12/96			DERNIERE MODIFICATION : 14/02/97
VERSION :	1.0
***********************************************************************	*/

/* **********************************************************************NOM DU COMPOSANT : 		Données globales
ROLE DU COMPOSANT :		Partage ses données avec les autres composants

REFRENCES EXTERNES :	aucune

REFRENCES INTERNES :	
	CDlgConfig			Fenêtre de configuration du simulateur
	CDlgAffecte			Fenêtre d'affectation des Liaisons/Equipements
***********************************************************************	*/
#include "Equip/ParamSim.h"
#include "DlgOutil.h"		// Accés au écran de contrôle des équipements

CParamSimu			*glob_paramsimu;

CSynchro    		*glob_synchro;
char glob_TOP[] = 	"TOP_SYNCHRO";				// Nom de l'evt Top Synchro
char glob_PIPE[] = 	"\\\\.\\PIPE\\PIPE_SYNCHRO";

CDlgAccueil 		*glob_ihm;					// Ecran d'accueil

CDlgOutil			*glob_barre;				// Boite d'outil

CProto 				*glob_proto;

char glob_CHEMIN[81];
char glob_REPERTOIRE[81];

// Fichier d'aide Simulateur
char glob_HELP_ACCUEIL[] 	=	"Aide\\Accueil.hlp";
char glob_HELP_CONFIG[] 	=	"Aide\\Config.hlp";
char glob_HELP_AFFECTE[] 	=	"Aide\\Affecte.hlp";

// Fichier d'aide Equipement
char glob_HELP_R_1241[] 	=	"Aide\\R_1241.hlp";
char glob_HELP_E_1236[] 	=	"Aide\\E_1236.hlp";
char glob_HELP_E_1237[] 	=	"Aide\\E_1237.hlp";
char glob_HELP_R_251[] 		=	"Aide\\R_251.hlp";
char glob_HELP_EMR_18[] 	=	"Aide\\EMR_18.hlp";

char glob_HELP_E_1225[] 	=	"Aide\\E_1225.hlp";
char glob_HELP_AUDIO[] 		=	"Aide\\Audio.hlp";
char glob_HELP_STANDHF[] 	=	"Aide\\StandHF.hlp";
char glob_HELP_ACCORD[] 	=	"Aide\\Accord.hlp";
char glob_HELP_AAD_20_4[] 	=	"Aide\\AAD_20_4.hlp";
char glob_HELP_AAD_20_8[] 	=	"Aide\\AAD_20_4.hlp";
char glob_HELP_MAT_SPIN[] 	=	"Aide\\MAT_SPIN.hlp";
char glob_HELP_MAT_L11[] 	=	"Aide\\MAT_L11.hlp";
char glob_HELP_CA150[]	 	=	"Aide\\CA150.hlp";
char glob_HELP_CV24[]	 	=	"Aide\\CV24.hlp";
char glob_HELP_TOR[]	 	=	"Aide\\TOR.hlp";
// Modem TRC1752
char glob_HELP_TRC1752[]	 	=	"\\Aide\\MODEM.HLP";
char glob_HELP_COMMUTATION_MATRIX[]	 	=	"Aide\\CommutationMatrix.hlp";
// ED42
char glob_HELP_ED42[]	 	=	"Aide\\ED42.hlp";

// Fichiers son
char glob_EQUIP_ON[] 		=	"Aide\\RINGOUT.WAV";
char glob_EQUIP_OFF[] 		=	"Aide\\RINGOUT.WAV";
char glob_SON_CORRECT[] 	=	"Aide\\DING.WAV";
char glob_SON_INCORRECT[] 	=	"Aide\\INCORREC.WAV";
//
char glob_SON_ALE[] 	=	"Aide\\ALE.WAV";

// Fichier de contextes d'exploitation par défaut
char glob_CONTEXT_RECHF[]		=	"Contexte\\REC_HF\\defaut.ctx";
char glob_CONTEXT_EMETHF[] 		=	"Contexte\\EM_HF\\defaut.ctx";
char glob_CONTEXT_AUDIO[]		=	"Contexte\\AUDIO\\defaut.ctx";
char glob_CONTEXT_STANDHF[]		=	"Contexte\\STANDARD\\defaut.ctx";
char glob_CONTEXT_EMREC[] 		=	"Contexte\\EM_REC\\defaut.ctx";
char glob_CONTEXT_ACCORD[] 		=	"Contexte\\ACCORD\\defaut.ctx";
char glob_CONTEXT_REC_251[] 	=	"Contexte\\REC_251\\defaut.ctx";
char glob_CONTEXT_AAD_20_4[] 	=	"Contexte\\AAD\\defaut_20x4.ctx";
char glob_CONTEXT_AAD_20_8[] 	=	"Contexte\\AAD\\defaut_20x8.ctx";
char glob_CONTEXT_MAT_SPIN[] 	=	"Contexte\\MAT\\defautSPIN.ctx";
char glob_CONTEXT_MAT_L11[] 	=	"Contexte\\MAT\\defautL11.ctx";
char cour_CONTEXT_MAT_SPIN[] 	=	"Contexte\\MAT\\M_10980_SPIN.dat";
char cour_CONTEXT_MAT_L11[] 	=	"Contexte\\MAT\\M_10980_L11.dat";
char glob_CONTEXT_CA150_MASTER[]=	"Contexte\\CA150\\defautMASTER.ctx";
char glob_CONTEXT_CA150_SLAVE[] =	"Contexte\\CA150\\defautSLAVE.ctx";
char glob_CONTEXT_CV24_KY58[]=	"Contexte\\CV24\\defautKY58.ctx";
char glob_CONTEXT_TOR_KY58[]=	"Contexte\\TOR\\defautKY58.ctx";
char glob_CONTEXT_CV24_ANDVT[] =	"Contexte\\CV24\\defautANDVT.ctx";
char glob_CONTEXT_TOR_ANDVT[] =	"Contexte\\TOR\\defautANDVT.ctx";
char glob_CONTEXT_TOR_CARD[]=	"Contexte\\TOR\\defautTOR.ctx";
char glob_CONTEXT_COMMUTATION_MATRIX[] =	"Contexte\\MAT\\defautCom.ctx";
char glob_CONTEXT_ED42[]		=	"Contexte\\ED42\\defaut.ctx";
