#include "ortaq.h"
#include <windows.h>
#include "UCommon.h"
#include <stdio.h>
#include <stdlib.h>
#include <io.h>

wchar_t *_resKey[RES_MAX];
wchar_t *_resVal[RES_MAX];
wchar_t _gmsgBuf[256];

int     _resCnt=0;
struct  QelipUnicode	g_Unicode[34];

// Towendikiler Imla DLL diki munasiwetlik Funkitsiyeler

Init UInitImla;
IsCorrect UIsCorrect;
CheckWord UCheckWord;
LoadDictionary ULoadDictionary;
UnLoadDictionary UUnLoadDictionary;
GetCandidateWord UGetCandidateWord;
GetOrgWord UGetOrgWord;
ShowFindDialog UShowFindDialog;
SetUILang USetUILang;
GetToghrisi UGetToghrisi;

HMODULE gLoadImlaDll()
{
	HMODULE mhImla=LoadLibrary(L"Kenjimla.Dll");
	UInitImla=(Init)GetProcAddress(mhImla,"UInit");
	UIsCorrect=(IsCorrect)GetProcAddress(mhImla,"UIsCorrect");
	UCheckWord=(CheckWord)GetProcAddress(mhImla,"UCheckWord");
	ULoadDictionary=(LoadDictionary)GetProcAddress(mhImla,"ULoadDictionary");
	UUnLoadDictionary=(UnLoadDictionary)GetProcAddress(mhImla,"UUnLoadDictionary");
	UGetCandidateWord=(GetCandidateWord)GetProcAddress(mhImla,"UGetCandidateWord");
	UGetOrgWord=(GetOrgWord)GetProcAddress(mhImla,"UGetOrgWord");
	UShowFindDialog=(ShowFindDialog)GetProcAddress(mhImla,"UShowFindDialog");
	USetUILang=(SetUILang)GetProcAddress(mhImla,"USetUILang");
	UGetToghrisi=(GetToghrisi)GetProcAddress(mhImla,"UGetToghrisi");
	return mhImla;
}

int gUGetUnicodeIndex(wchar_t Herp)
{
	int ret=-1;
	switch(Herp)
	{
		case  UYG_UN_A_6:
		case  UYG_UN_A_Y:
		case  UYG_UN_A_A:
			ret=UYGIN_A ;
			break;
		case  UYG_UN_E_6:
		case  UYG_UN_E_Y:
		case  UYG_UN_E_A:
			ret=UYGIN_E ;
			break;
		case  UYG_UN_B_6:
		case  UYG_UN_B_Y:
		case  UYG_UN_B_B:
		case  UYG_UN_B_O:
		case  UYG_UN_B_A:
			ret=UYGIN_B ;
			break;
		case  UYG_UN_P_6:
		case  UYG_UN_P_Y:
		case  UYG_UN_P_B:
		case  UYG_UN_P_O:
		case  UYG_UN_P_A:
			ret=UYGIN_P;
			break;
		case  UYG_UN_T_6:
		case  UYG_UN_T_Y:
		case  UYG_UN_T_B:
		case  UYG_UN_T_O:
		case  UYG_UN_T_A:
			ret=UYGIN_T ;
			break;
		case  UYG_UN_J_6:
		case  UYG_UN_J_Y:
		case  UYG_UN_J_B:
		case  UYG_UN_J_O:
		case  UYG_UN_J_A:
			ret=UYGIN_J ;
			break;
		case  UYG_UN_CH_6:
		case  UYG_UN_CH_Y:
		case  UYG_UN_CH_B:
		case  UYG_UN_CH_O:
		case  UYG_UN_CH_A:
			ret=UYGIN_CH;
			break;
		case  UYG_UN_X_6:
		case  UYG_UN_X_Y:
		case  UYG_UN_X_B:
		case  UYG_UN_X_O:
		case  UYG_UN_X_A:
			ret=UYGIN_X;
			break;
		case  UYG_UN_D_6:
		case  UYG_UN_D_Y:
		case  UYG_UN_D_A:
			ret=UYGIN_D ;
			break;
		case  UYG_UN_R_6:
		case  UYG_UN_R_Y:
		case  UYG_UN_R_A:
			ret=UYGIN_R;
			break;
		case  UYG_UN_Z_6:
		case  UYG_UN_Z_Y:
		case  UYG_UN_Z_A:
			ret=UYGIN_Z;
			break;
		case  UYG_UN_ZZ_6:
		case  UYG_UN_ZZ_Y:
		case  UYG_UN_ZZ_A:
			ret=UYGIN_ZZ;
			break;
		case  UYG_UN_S_6:
		case  UYG_UN_S_Y:
		case  UYG_UN_S_B:
		case  UYG_UN_S_O:
		case  UYG_UN_S_A:
			ret=UYGIN_S;
			break;
		case  UYG_UN_SH_6:
		case  UYG_UN_SH_Y:
		case  UYG_UN_SH_B:
		case  UYG_UN_SH_O:
		case  UYG_UN_SH_A:
			ret=UYGIN_SH;
			break;
		case  UYG_UN_GH_6:
		case  UYG_UN_GH_Y:
		case  UYG_UN_GH_B:
		case  UYG_UN_GH_O:
		case  UYG_UN_GH_A:
			ret=UYGIN_GH;
			break;
		case  UYG_UN_F_6:
		case  UYG_UN_F_Y:
		case  UYG_UN_F_B:
		case  UYG_UN_F_O:
		case  UYG_UN_F_A:
			ret=UYGIN_F ;
			break;
		case  UYG_UN_Q_6:
		case  UYG_UN_Q_Y:
		case  UYG_UN_Q_B:
		case  UYG_UN_Q_O:
		case  UYG_UN_Q_A:
			ret=UYGIN_Q;
			break;
		case  UYG_UN_K_6:
		case  UYG_UN_K_Y:
		case  UYG_UN_K_B:
		case  UYG_UN_K_O:
		case  UYG_UN_K_A:
			ret=UYGIN_K;
			break;
		case  UYG_UN_G_6:
		case  UYG_UN_G_Y:
		case  UYG_UN_G_B:
		case  UYG_UN_G_O:
		case  UYG_UN_G_A:
			ret=UYGIN_G ;
			break;
		case  UYG_UN_NG_6:
		case  UYG_UN_NG_Y:
		case  UYG_UN_NG_B:
		case  UYG_UN_NG_O:
		case  UYG_UN_NG_A:
			ret=UYGIN_NG ;
			break;
		case  UYG_UN_L_6:
		case  UYG_UN_L_Y:
		case  UYG_UN_L_B:
		case  UYG_UN_L_O:
		case  UYG_UN_L_A:
			ret=UYGIN_L ;
			break;
		case  UYG_UN_M_6:
		case  UYG_UN_M_Y:
		case  UYG_UN_M_B:
		case  UYG_UN_M_O:
		case  UYG_UN_M_A:
			ret=UYGIN_M ;
			break;
		case  UYG_UN_N_6:
		case  UYG_UN_N_Y:
		case  UYG_UN_N_B:
		case  UYG_UN_N_O:
		case  UYG_UN_N_A:
			ret=UYGIN_N;
			break;
		case  UYG_UN_H_6:
		case  UYG_UN_H_Y:
		case  UYG_UN_H_A:
		case  UYG_UN_H_B:
		case  UYG_UN_H_O:
		case  UYGE_UN_H_Y:   // Yulghunda Ishlitilgen
		case  UYGE_UN_H_A:   // Yulghunda ishlitilgen
			ret=UYGIN_H ;
			break;
		case  UYG_UN_O_6:
		case  UYG_UN_O_Y:
		case  UYG_UN_O_A:
			ret=UYGIN_O ;
			break;
		case  UYG_UN_U_6:
		case  UYG_UN_U_Y:
		case  UYG_UN_U_A:
			ret=UYGIN_U ;
			break;
		case  UYG_UN_OO_6:
		case  UYG_UN_OO_Y:
		case  UYG_UN_OO_A:
			ret=UYGIN_OO;
			break;
		case  UYG_UN_UU_6:
		case  UYG_UN_UU_Y:
		case  UYG_UN_UU_A:
			ret=UYGIN_UU;
			break;
		case  UYG_UN_W_6:
		case  UYG_UN_W_Y:
		case  UYG_UN_W_A:
			ret=UYGIN_W;
			break;
		case  UYG_UN_EE_6:
		case  UYG_UN_EE_Y:
		case  UYG_UN_EE_B:
		case  UYG_UN_EE_O:
		case  UYG_UN_EE_A:
			ret=UYGIN_EE;
			break;
		case  UYG_UN_I_6:
		case  UYG_UN_I_Y:
		case  UYG_UN_I_B:
		case  UYG_UN_I_O:
		case  UYG_UN_I_A:
			ret=UYGIN_I ;
			break;
		case  UYG_UN_Y_6:
		case  UYG_UN_Y_Y:
		case  UYG_UN_Y_B:
		case  UYG_UN_Y_O:
		case  UYG_UN_Y_A:
			ret=UYGIN_Y ;
			break;
		case  UYG_UN_LA_Y:
		case  UYG_UN_LA_A:
			ret=UYGIN_LA;
			break;
		case  UYG_UN_HM_6:
		case  UYG_UN_HM_Y:
		case  UYG_UN_HM_O:
			ret=UYGIN_HM;
			break;
		default:
			break;

	}
	return ret;
}

// Bu Herip ning Uyghurche herip kodimu Hokum qilidu
// Eger Uyghgurche bolsa Uyghurche Fontni Ishlitidu
// Bolmisa Bashqa FOntni ishlitidu

BOOL gUIsUyghur(wchar_t Herip)
{
	BOOL ret;
	switch(Herip)
	{
		case  UYG_UN_A_6:
		case  UYG_UN_A_Y:
		case  UYG_UN_A_A:
		case  UYG_UN_E_6:
		case  UYG_UN_E_Y:
		case  UYG_UN_E_A:
		case  UYG_UN_B_6:
		case  UYG_UN_B_Y:
		case  UYG_UN_B_B:
		case  UYG_UN_B_O:
		case  UYG_UN_B_A:
		case  UYG_UN_P_6:
		case  UYG_UN_P_Y:
		case  UYG_UN_P_B:
		case  UYG_UN_P_O:
		case  UYG_UN_P_A:
		case  UYG_UN_T_6:
		case  UYG_UN_T_Y:
		case  UYG_UN_T_B:
		case  UYG_UN_T_O:
		case  UYG_UN_T_A:
		case  UYG_UN_J_6:
		case  UYG_UN_J_Y:
		case  UYG_UN_J_B:
		case  UYG_UN_J_O:
		case  UYG_UN_J_A:
		case  UYG_UN_CH_6:
		case  UYG_UN_CH_Y:
		case  UYG_UN_CH_B:
		case  UYG_UN_CH_O:
		case  UYG_UN_CH_A:
		case  UYG_UN_X_6:
		case  UYG_UN_X_Y:
		case  UYG_UN_X_B:
		case  UYG_UN_X_O:
		case  UYG_UN_X_A:
		case  UYG_UN_D_6:
		case  UYG_UN_D_Y:
		case  UYG_UN_D_A:
		case  UYG_UN_R_6:
		case  UYG_UN_R_Y:
		case  UYG_UN_R_A:
		case  UYG_UN_Z_6:
		case  UYG_UN_Z_Y:
		case  UYG_UN_Z_A:
		case  UYG_UN_ZZ_6:
		case  UYG_UN_ZZ_Y:
		case  UYG_UN_ZZ_A:
		case  UYG_UN_S_6:
		case  UYG_UN_S_Y:
		case  UYG_UN_S_B:
		case  UYG_UN_S_O:
		case  UYG_UN_S_A:
		case  UYG_UN_SH_6:
		case  UYG_UN_SH_Y:
		case  UYG_UN_SH_B:
		case  UYG_UN_SH_O:
		case  UYG_UN_SH_A:
		case  UYG_UN_GH_6:
		case  UYG_UN_GH_Y:
		case  UYG_UN_GH_B:
		case  UYG_UN_GH_O:
		case  UYG_UN_GH_A:
		case  UYG_UN_F_6:
		case  UYG_UN_F_Y:
		case  UYG_UN_F_B:
		case  UYG_UN_F_O:
		case  UYG_UN_F_A:
		case  UYG_UN_Q_6:
		case  UYG_UN_Q_Y:
		case  UYG_UN_Q_B:
		case  UYG_UN_Q_O:
		case  UYG_UN_Q_A:
		case  UYG_UN_K_6:
		case  UYG_UN_K_Y:
		case  UYG_UN_K_B:
		case  UYG_UN_K_O:
		case  UYG_UN_K_A:
		case  UYG_UN_G_6:
		case  UYG_UN_G_Y:
		case  UYG_UN_G_B:
		case  UYG_UN_G_O:
		case  UYG_UN_G_A:
		case  UYG_UN_NG_6:
		case  UYG_UN_NG_Y:
		case  UYG_UN_NG_B:
		case  UYG_UN_NG_O:
		case  UYG_UN_NG_A:
		case  UYG_UN_L_6:
		case  UYG_UN_L_Y:
		case  UYG_UN_L_B:
		case  UYG_UN_L_O:
		case  UYG_UN_L_A:
		case  UYG_UN_M_6:
		case  UYG_UN_M_Y:
		case  UYG_UN_M_B:
		case  UYG_UN_M_O:
		case  UYG_UN_M_A:
		case  UYG_UN_N_6:
		case  UYG_UN_N_Y:
		case  UYG_UN_N_B:
		case  UYG_UN_N_O:
		case  UYG_UN_N_A:
		case  UYG_UN_H_6:
		case  UYG_UN_H_Y:
		case  UYG_UN_H_A:
		case  UYG_UN_H_B:
		case  UYG_UN_H_O:
		case  UYG_UN_O_6:
		case  UYG_UN_O_Y:
		case  UYG_UN_O_A:
		case  UYG_UN_U_6:
		case  UYG_UN_U_Y:
		case  UYG_UN_U_A:
		case  UYG_UN_OO_6:
		case  UYG_UN_OO_Y:
		case  UYG_UN_OO_A:
		case  UYG_UN_UU_6:
		case  UYG_UN_UU_Y:
		case  UYG_UN_UU_A:
		case  UYG_UN_W_6:
		case  UYG_UN_W_Y:
		case  UYG_UN_W_A:
		case  UYG_UN_EE_6:
		case  UYG_UN_EE_Y:
		case  UYG_UN_EE_B:
		case  UYG_UN_EE_O:
		case  UYG_UN_EE_A:
		case  UYG_UN_I_6:
		case  UYG_UN_I_Y:
		case  UYG_UN_I_B:
		case  UYG_UN_I_O:
		case  UYG_UN_I_A:
		case  UYG_UN_Y_6:
		case  UYG_UN_Y_Y:
		case  UYG_UN_Y_B:
		case  UYG_UN_Y_O:
		case  UYG_UN_Y_A:
		case  UYG_UN_LA_Y:
		case  UYG_UN_LA_A:
		case  UYG_UN_HM_6:
		case  UYG_UN_HM_Y:
		case  UYG_UN_HM_O:

		// Qoshumche Heripler
		case UYGE_UN_HA_Y:
		case UYGE_UN_HA_A:
		case UYGE_UN_HE_Y:
		case UYGE_UN_HE_A:
		//hemze bilen O
		case UYGE_UN_HO_Y:
		case UYGE_UN_HO_A:
		//hemze bilen U
		case UYGE_UN_HU_Y:
		case UYGE_UN_HU_A:
		//hemze bilen OO
		case UYGE_UN_HOO_Y:
		case UYGE_UN_HOO_A:
		//hemze bilen UU
		case UYGE_UN_HUU_Y:
		case UYGE_UN_HUU_A:
		//hemze bilen EE
		case UYGE_UN_HEE_Y:
		case UYGE_UN_HEE_A:
		case UYGE_UN_HEE_B:
		//hemze bilen I
		case UYGE_UN_HI_Y:
		case UYGE_UN_HI_A:
		case UYGE_UN_HI_B:

		// Belgiler
		case UYG_UN_PESH:
		case UYG_UN_SOZUSH:
		case UYG_UN_CHEKITPESH:
		case UYG_UN_SOAL:
		case VK_SPACE:         // Bolshuq we TAB bolsimu Uyghurceh FOntni Ishlitidu
		case VK_TAB:
			ret=TRUE;
			break;
		default:
			ret=FALSE;
			break;
	}
	return ret;
}

// Bu Herip ning Uyghurche sozuq tawush heripimu Hokum Qilidu
BOOL gUIsSozuqTawushUNICODE(wchar_t Herip)
{
	BOOL ret;
	switch(Herip)
	{
		case  UYG_UN_A_6:
		case  UYG_UN_A_Y:
		case  UYG_UN_A_A:
		case  UYG_UN_E_6:
		case  UYG_UN_E_Y:
		case  UYG_UN_E_A:
		case  UYG_UN_O_6:
		case  UYG_UN_O_Y:
		case  UYG_UN_O_A:
		case  UYG_UN_U_6:
		case  UYG_UN_U_Y:
		case  UYG_UN_U_A:
		case  UYG_UN_OO_6:
		case  UYG_UN_OO_Y:
		case  UYG_UN_OO_A:
		case  UYG_UN_UU_6:
		case  UYG_UN_UU_Y:
		case  UYG_UN_UU_A:
		case  UYG_UN_EE_6:
		case  UYG_UN_EE_Y:
		case  UYG_UN_EE_B:
		case  UYG_UN_EE_O:
		case  UYG_UN_EE_A:
		case  UYG_UN_I_6:
		case  UYG_UN_I_Y:
		case  UYG_UN_I_B:
		case  UYG_UN_I_O:
		case  UYG_UN_I_A:
		case  UYG_UN_LA_Y:
		case  UYG_UN_LA_A:
		// Qoshumche Heripler
		case UYGE_UN_HA_Y:
		case UYGE_UN_HA_A:
		case UYGE_UN_HE_Y:
		case UYGE_UN_HE_A:
		//hemze bilen O
		case UYGE_UN_HO_Y:
		case UYGE_UN_HO_A:
		//hemze bilen U
		case UYGE_UN_HU_Y:
		case UYGE_UN_HU_A:
		//hemze bilen OO
		case UYGE_UN_HOO_Y:
		case UYGE_UN_HOO_A:
		//hemze bilen UU
		case UYGE_UN_HUU_Y:
		case UYGE_UN_HUU_A:
		//hemze bilen EE
		case UYGE_UN_HEE_Y:
		case UYGE_UN_HEE_A:
		case UYGE_UN_HEE_B:
		//hemze bilen I
		case UYGE_UN_HI_Y:
		case UYGE_UN_HI_A:
		case UYGE_UN_HI_B:
			ret=TRUE;
			break;
		default:
			ret=FALSE;
			break;
	}
	return ret;
}


BOOL gUIsSozuqTawushUKY(wchar_t Herip)
{
	BOOL ret;
	switch(Herip)
	{
		case  UYG_UKY_A_KICHIK:
		case  UYG_UKY_A_CHONG:
		case  UYG_UKY_E_KICHIK:
		case  UYG_UKY_E_CHONG:
		case  UYG_UKY_O_KICHIK:
		case  UYG_UKY_O_CHONG:
		case  UYG_UKY_U_KICHIK:
		case  UYG_UKY_U_CHONG:
		case  UYG_UKY_OO_KICHIK:
		case  UYG_UKY_OO_CHONG:
		case  UYG_UKY_UU_KICHIK:
		case  UYG_UKY_UU_CHONG:
		case  UYG_UKY_EE_KICHIK:
		case  UYG_UKY_EE_CHONG:
		case  UYG_UKY_I_KICHIK:
		case  UYG_UKY_I_CHONG:
//		case  0x00e8:
//		case  0x00c8:
			ret=TRUE;
			break;
		default:
			ret=FALSE;
			break;
	}
	return ret;
}

wchar_t gUToLowerULY(wchar_t Herp)
{
    wchar_t ret=Herp;
    switch(Herp)
    {
		case  UYG_UKY_A_CHONG:
			ret=UYG_UKY_A_KICHIK ;
			break;
		case  UYG_UKY_E_CHONG:
			ret=UYG_UKY_E_KICHIK ;
			break;
		case  UYG_UKY_B_CHONG:
			ret=UYG_UKY_B_KICHIK ;
			break;
		case  UYG_UKY_P_CHONG:
			ret=UYG_UKY_P_KICHIK;
			break;
		case  UYG_UKY_T_CHONG:
			ret=UYG_UKY_T_KICHIK ;
			break;
		case  UYG_UKY_J_CHONG:
			ret=UYG_UKY_J_KICHIK ;
			break;
		case  UYG_UKY_X_CHONG:
			ret=UYG_UKY_X_KICHIK;
			break;
		case  UYG_UKY_D_CHONG:
			ret=UYG_UKY_D_KICHIK ;
			break;
		case  UYG_UKY_R_CHONG:
			ret=UYG_UKY_R_KICHIK;
			break;
		case  UYG_UKY_Z_CHONG:
			ret=UYG_UKY_Z_KICHIK;
			break;
		case  UYG_UKY_S_CHONG:
			ret=UYG_UKY_S_KICHIK;
			break;
		case  UYG_UKY_F_CHONG:
			ret=UYG_UKY_F_KICHIK ;
			break;
		case  UYG_UKY_Q_CHONG:
			ret=UYG_UKY_Q_KICHIK;
			break;
		case  UYG_UKY_K_CHONG:
			ret=UYG_UKY_K_KICHIK;
			break;
		case  UYG_UKY_G_CHONG:
			ret=UYG_UKY_G_KICHIK ;
			break;
		case  UYG_UKY_L_CHONG:
			ret=UYG_UKY_L_KICHIK ;
			break;
		case  UYG_UKY_M_CHONG:
			ret=UYG_UKY_M_KICHIK ;
			break;
		case  UYG_UKY_N_CHONG:
			ret=UYG_UKY_N_KICHIK;
			break;
		case  UYG_UKY_H_KICHIK:
		case  UYG_UKY_H_CHONG:
			ret=UYG_UKY_H_KICHIK ;
			break;
		case  UYG_UKY_O_CHONG:
			ret=UYG_UKY_O_KICHIK ;
			break;
		case  UYG_UKY_U_CHONG:
			ret=UYG_UKY_U_KICHIK ;
			break;
		case  UYG_UKY_OO_CHONG:
			ret=UYG_UKY_OO_KICHIK;
			break;
		case  UYG_UKY_UU_CHONG:
			ret=UYG_UKY_UU_KICHIK;
			break;
		case  UYG_UKY_W_CHONG:
			ret=UYG_UKY_W_KICHIK;
			break;
		case  UYG_UKY_EE_CHONG:
			ret=UYG_UKY_EE_KICHIK;
			break;
		case  UYG_UKY_I_CHONG:
			ret=UYG_UKY_I_KICHIK ;
			break;
		case  UYG_UKY_Y_CHONG:
			ret=UYG_UKY_Y_KICHIK;
			break;
		case  L'C':
			ret=L'c';
			break;
    }
    return ret;
}

wchar_t gUToLowerAlahide(wchar_t Herp)
{
    wchar_t ret;
    ret=Herp;
    if(Herp>0xE000 && Herp<0xE0FF)
    {
        ret=ret-0xE000;
        ret=gUToLowerULY(ret);
        ret=0xE000+ret;
    }
    return ret;
}

wchar_t gUToUpperULY(wchar_t Herp)
{
    wchar_t ret=Herp;
    switch(Herp)
    {
		case  UYG_UKY_A_KICHIK:
			ret=UYG_UKY_A_CHONG ;
			break;
		case  UYG_UKY_E_KICHIK:
			ret=UYG_UKY_E_CHONG ;
			break;
		case  UYG_UKY_B_KICHIK:
			ret=UYG_UKY_B_CHONG ;
			break;
		case  UYG_UKY_P_KICHIK:
			ret=UYG_UKY_P_CHONG;
			break;
		case  UYG_UKY_T_KICHIK:
			ret=UYG_UKY_T_CHONG ;
			break;
		case  UYG_UKY_J_KICHIK:
			ret=UYG_UKY_J_CHONG ;
			break;
		case  UYG_UKY_X_KICHIK:
			ret=UYG_UKY_X_CHONG;
			break;
		case  UYG_UKY_D_KICHIK:
			ret=UYG_UKY_D_CHONG ;
			break;
		case  UYG_UKY_R_KICHIK:
			ret=UYG_UKY_R_CHONG;
			break;
		case  UYG_UKY_Z_KICHIK:
			ret=UYG_UKY_Z_CHONG;
			break;
		case  UYG_UKY_S_KICHIK:
			ret=UYG_UKY_S_CHONG;
			break;
		case  UYG_UKY_F_KICHIK:
			ret=UYG_UKY_F_CHONG ;
			break;
		case  UYG_UKY_Q_KICHIK:
			ret=UYG_UKY_Q_CHONG;
			break;
		case  UYG_UKY_K_KICHIK:
			ret=UYG_UKY_K_CHONG;
			break;
		case  UYG_UKY_G_KICHIK:
			ret=UYG_UKY_G_CHONG ;
			break;
		case  UYG_UKY_L_KICHIK:
			ret=UYG_UKY_L_CHONG ;
			break;
		case  UYG_UKY_M_KICHIK:
			ret=UYG_UKY_M_CHONG ;
			break;
		case  UYG_UKY_N_KICHIK:
			ret=UYG_UKY_N_CHONG;
			break;
		case  UYG_UKY_H_CHONG:
		case  UYG_UKY_H_KICHIK:
			ret=UYG_UKY_H_CHONG ;
			break;
		case  UYG_UKY_O_KICHIK:
			ret=UYG_UKY_O_CHONG ;
			break;
		case  UYG_UKY_U_KICHIK:
			ret=UYG_UKY_U_CHONG ;
			break;
		case  UYG_UKY_OO_KICHIK:
			ret=UYG_UKY_OO_CHONG;
			break;
		case  UYG_UKY_UU_KICHIK:
			ret=UYG_UKY_UU_CHONG;
			break;
		case  UYG_UKY_W_KICHIK:
			ret=UYG_UKY_W_CHONG;
			break;
		case  UYG_UKY_EE_KICHIK:
			ret=UYG_UKY_EE_CHONG;
			break;
		case  UYG_UKY_I_KICHIK:
			ret=UYG_UKY_I_CHONG ;
			break;
		case  UYG_UKY_Y_KICHIK:
			ret=UYG_UKY_Y_CHONG;
			break;
		case  L'c':
			ret=L'C';
			break;
    }
    return ret;
}

wchar_t gUToUpperSlawiyan(wchar_t Herp)
{
	wchar_t UHerp=Herp;
	switch(Herp)
	{
		case  0x0430:	/*а*/
		case  0x0410: /*А*/
			UHerp=0x0410;
			break;
		case  0x04d9:	/*ә*/
		case  0x04d8:   /*Ә*/
			UHerp=0x04d8;
			break;
		case  0x0435:	/*е*/
		case  0x0415:   /*Е*/
			UHerp=0x0415;
			break;
		case  0x0438:	/*и*/
		case  0x0418:   /*И*/
			UHerp=0x0418;
			break;
		case  0x043e:	/*о*/
		case  0x041e:   /*О*/
			UHerp=0x041e;
			break;
		case  0x0443:	/*у*/
		case  0x0423:   /*У*/
			UHerp=0x0423;
			break;
		case  0x04e9:	/*ө*/
		case  0x04e8:   /*Ө*/
			UHerp=0x04e8;
			break;
		case  0x04af:	/*ү*/
		case  0x04AE:   /*Ү*/
			UHerp=0x04AE;
			break;
		case  0x0431:	/*б*/;
		case  0x0411: /*Б*/
			UHerp=0x0411;
            break;
		case  0x043f:	/*п*/
		case  0x041F:  /*П*/
			UHerp=0x041F;
			break;
		case  0x0442:	/*т*/
		case  0x0422: /*Т*/
			UHerp=0x0422;
			break;
		case  0x0497:	/*җ*/
		case  0x0496:   /*Җ*/
			UHerp=0x0496;
			break;
		case  0x0447:	/*ч*/
		case  0x0427:  /*Ч*/
			UHerp=0x0427;
			break;
		case  0x0445:	/*х*/
		case  0x0425:   /*Х*/
			UHerp=0x0425;
			break;
		case  0x0434:	/*д*/
		case  0x0414:   /*Д*/
			UHerp=0x0414;
			break;
		case  0x0440:	/*р*/
		case  0x0420:   /*Р*/
            UHerp=0x0420;
			break;
		case  0x0437:	/*з*/
		case  0x0417:   /*З*/
			UHerp=0x0417;
			break;
		case  0x0436:	/*ж*/
		case  0x0416:   /*Ж*/
			UHerp=0x0416;
			break;
		case  0x0441:	/*с*/
		case  0x0421:   /*С*/
			UHerp=0x0421;
			break;
		case  0x0448:	/*ш*/
		case  0x0428:   /*Ш*/
			UHerp=0x0428;
			break;
		case  0x0493:	/*ғ*/
		case  0x0492:   /*Ғ*/
			UHerp=0x0492;
			break;
		case  0x0444:	/*ф*/
		case  0x0424:   /*Ф*/
			UHerp=0x0424;
			break;
		case  0x049b:	/*қ*/
		case  0x049A:   /*Қ*/
			UHerp=0x049A;
			break;
		case  0x043a:	/*к*/
		case  0x041a:   /*К*/
			UHerp=0x041a;
			break;
		case  0x0433:	/*г*/
		case  0x0413:   /*Г*/
			UHerp=0x0413;
			break;
		case  0x04a3:	/*ң*/
		case  0x04a2:   /*Ң*/
			UHerp=0x04a2;
			break;
		case  0x043b:	/*л*/
		case  0x041B:   /*Л*/
			UHerp=0x041B;
			break;
		case  0x043c:	/*м*/
		case  0x041c:   /*М*/
			UHerp=0x041c;
			break;
		case  0x043d:	/*н*/
		case  0x041D:   /*Н*/
			UHerp=0x041D;
			break;
		case  0x04bb:	/*һ*/
		case  0x04ba:   /*Һ*/
			UHerp=0x04ba;
			break;
		case  0x0432:	/*в*/
		case  0x0412:   /*В*/
			UHerp=0x0412;
			break;
		case  0x0439:	/*й*/
		case  0x0419:   /*Й*/
			UHerp=0x0419;
			break;
		case  0x044f:   /*'я'*/
		case  0x042F:   /*Я*/
			UHerp=0x042F;
			break;
		case  0x044E: /*'ю'*/
		case  0x042E: /*Ю*/
			UHerp=0x042E;
			break;
        default:
            UHerp=Herp;
            break;
	}
	return UHerp;
}

bool gUIsLowerULY(wchar_t Herp)
{
    bool ret=false;
    switch(Herp)
    {
		case  UYG_UKY_A_KICHIK:
		case  UYG_UKY_E_KICHIK:
		case  UYG_UKY_B_KICHIK:
		case  UYG_UKY_P_KICHIK:
		case  UYG_UKY_T_KICHIK:
		case  UYG_UKY_J_KICHIK:
		case  UYG_UKY_X_KICHIK:
		case  UYG_UKY_D_KICHIK:
		case  UYG_UKY_R_KICHIK:
		case  UYG_UKY_Z_KICHIK:
		case  UYG_UKY_S_KICHIK:
		case  UYG_UKY_F_KICHIK:
		case  UYG_UKY_Q_KICHIK:
		case  UYG_UKY_K_KICHIK:
		case  UYG_UKY_G_KICHIK:
		case  UYG_UKY_L_KICHIK:
		case  UYG_UKY_M_KICHIK:
		case  UYG_UKY_N_KICHIK:
		case  UYG_UKY_H_KICHIK:
		case  UYG_UKY_O_KICHIK:
		case  UYG_UKY_U_KICHIK:
		case  UYG_UKY_OO_KICHIK:
		case  UYG_UKY_UU_KICHIK:
		case  UYG_UKY_W_KICHIK:
		case  UYG_UKY_EE_KICHIK:
		case  UYG_UKY_I_KICHIK:
		case  UYG_UKY_Y_KICHIK:
		case  'c':
            ret=true;
            break;
        default:
            ret=false;
            break;
    }
    return ret;
}

bool gUIsLowerAlahide(wchar_t Herp1)
{
    bool ret=false;
    wchar_t Herp=Herp1;
    if(Herp>0xE000 && Herp<0xE0FF)
    {
        Herp=Herp-0xE000;
    }
    switch(Herp)
    {
		case  UYG_UKY_A_KICHIK:
		case  UYG_UKY_E_KICHIK:
		case  UYG_UKY_B_KICHIK:
		case  UYG_UKY_P_KICHIK:
		case  UYG_UKY_T_KICHIK:
		case  UYG_UKY_J_KICHIK:
		case  UYG_UKY_X_KICHIK:
		case  UYG_UKY_D_KICHIK:
		case  UYG_UKY_R_KICHIK:
		case  UYG_UKY_Z_KICHIK:
		case  UYG_UKY_S_KICHIK:
		case  UYG_UKY_F_KICHIK:
		case  UYG_UKY_Q_KICHIK:
		case  UYG_UKY_K_KICHIK:
		case  UYG_UKY_G_KICHIK:
		case  UYG_UKY_L_KICHIK:
		case  UYG_UKY_M_KICHIK:
		case  UYG_UKY_N_KICHIK:
		case  UYG_UKY_H_KICHIK:
		case  UYG_UKY_O_KICHIK:
		case  UYG_UKY_U_KICHIK:
		case  UYG_UKY_OO_KICHIK:
		case  UYG_UKY_UU_KICHIK:
		case  UYG_UKY_W_KICHIK:
		case  UYG_UKY_EE_KICHIK:
		case  UYG_UKY_I_KICHIK:
		case  UYG_UKY_Y_KICHIK:
		case  'c':
            ret=true;
            break;
        default:
            ret=false;
            break;
    }
    return ret;
}

int gUGetUKYIndex(wchar_t ukyHerip)
{
	int ret;
	switch(ukyHerip)
	{
		case  UYG_UKY_A_KICHIK:
		case  UYG_UKY_A_CHONG:
			ret=UYGIN_A ;
			break;
        case  0x00c4:
        case  0x00e4:
		case  UYG_UKY_E_KICHIK:
		case  UYG_UKY_E_CHONG:
			ret=UYGIN_E ;
			break;
		case  UYG_UKY_B_KICHIK:
		case  UYG_UKY_B_CHONG:
			ret=UYGIN_B ;
			break;
		case  UYG_UKY_P_KICHIK:
		case  UYG_UKY_P_CHONG:
			ret=UYGIN_P;
			break;
		case  UYG_UKY_T_KICHIK:
		case  UYG_UKY_T_CHONG:
			ret=UYGIN_T ;
			break;
		case  UYG_UKY_J_KICHIK:
		case  UYG_UKY_J_CHONG:
			ret=UYGIN_J ;
			break;
		case  UYG_UKY_X_KICHIK:
		case  UYG_UKY_X_CHONG:
			ret=UYGIN_X;
			break;
		case  UYG_UKY_D_KICHIK:
		case  UYG_UKY_D_CHONG:
			ret=UYGIN_D ;
			break;
		case  UYG_UKY_R_KICHIK:
		case  UYG_UKY_R_CHONG:
			ret=UYGIN_R;
			break;
		case  UYG_UKY_Z_KICHIK:
		case  UYG_UKY_Z_CHONG:
			ret=UYGIN_Z;
			break;
		case  UYG_UKY_S_KICHIK:
		case  UYG_UKY_S_CHONG:
			ret=UYGIN_S;
			break;
		case  UYG_UKY_F_KICHIK:
		case  UYG_UKY_F_CHONG:
			ret=UYGIN_F ;
			break;
		case  UYG_UKY_Q_KICHIK:
		case  UYG_UKY_Q_CHONG:
			ret=UYGIN_Q;
			break;
		case  UYG_UKY_K_KICHIK:
		case  UYG_UKY_K_CHONG:
			ret=UYGIN_K;
			break;
		case  UYG_UKY_G_KICHIK:
		case  UYG_UKY_G_CHONG:
			ret=UYGIN_G ;
			break;
		case  UYG_UKY_L_KICHIK:
		case  UYG_UKY_L_CHONG:
			ret=UYGIN_L ;
			break;
		case  UYG_UKY_M_KICHIK:
		case  UYG_UKY_M_CHONG:
			ret=UYGIN_M ;
			break;
		case  UYG_UKY_N_KICHIK:
		case  UYG_UKY_N_CHONG:
			ret=UYGIN_N;
			break;
		case  UYG_UKY_H_KICHIK:
		case  UYG_UKY_H_CHONG:
			ret=UYGIN_H ;
			break;
		case  UYG_UKY_O_KICHIK:
		case  UYG_UKY_O_CHONG:
			ret=UYGIN_O ;
			break;
		case  UYG_UKY_U_KICHIK:
		case  UYG_UKY_U_CHONG:
			ret=UYGIN_U ;
			break;
		case  UYG_UKY_OO_KICHIK:
		case  UYG_UKY_OO_CHONG:
			ret=UYGIN_OO;
			break;
		case  UYG_UKY_UU_KICHIK:
		case  UYG_UKY_UU_CHONG:
			ret=UYGIN_UU;
			break;
		case  UYG_UKY_W_KICHIK:
		case  UYG_UKY_W_CHONG:
		case  UYG_UKY_V_KICHIK:
		case  UYG_UKY_V_CHONG:
			ret=UYGIN_W;
			break;
		case  UYG_UKY_EE_KICHIK:
		case  UYG_UKY_EE_CHONG:
//		case  0x00e8:
//		case  0x00c8:
			ret=UYGIN_EE;
			break;
		case  UYG_UKY_I_KICHIK:
		case  UYG_UKY_I_CHONG:
			ret=UYGIN_I ;
			break;
		case  UYG_UKY_Y_KICHIK:
		case  UYG_UKY_Y_CHONG:
			ret=UYGIN_Y;
			break;
// Sherqiy Turkistan Information Center ning ishletken Code
		case 0x015f: //
		case 0x015e:
			ret=UYGIN_SH;
			break;
		case 0x011e: //
		case 0x011f:
			ret=UYGIN_GH;
			break;
		case 0x00E7: //
		case 0x00C7:
			ret=UYGIN_CH;
			break;
        case  0x00d1:  /*Ññ*/
        case  0x00f1:
            ret=UYGIN_NG;
            break;
        default:
			ret=-1;
			break;
	}
	return ret;
}

/*
wchar_t gUGetBgdChar(wchar_t Herp)
{
	wchar_t ret;
	switch(Herp)
	{
		case  UYG_BGD_A_Y:
		case  UYG_BGD_A_A:
			ret=UYG_UN_A_6 ;
			break;
		case  UYG_BGD_E_Y:
		case  UYG_BGD_E_A:
			ret=UYG_UN_E_6 ;
			break;
		case  UYG_BGD_B_Y:
		case  UYG_BGD_B_B:
		case  UYG_BGD_B_O:
		case  UYG_BGD_B_A:
			ret=UYG_UN_B_6 ;
			break;
		case  UYG_BGD_P_Y:
		case  UYG_BGD_P_B:
		case  UYG_BGD_P_O:
		case  UYG_BGD_P_A:
			ret=UYG_UN_P_6;
			break;
		case  UYG_BGD_T_Y:
		case  UYG_BGD_T_B:
		case  UYG_BGD_T_O:
		case  UYG_BGD_T_A:
			ret=UYG_UN_T_6 ;
			break;
		case  UYG_BGD_J_Y:
		case  UYG_BGD_J_B:
		case  UYG_BGD_J_O:
		case  UYG_BGD_J_A:
			ret=UYG_UN_J_6 ;
			break;
		case  UYG_BGD_CH_Y:
		case  UYG_BGD_CH_B:
		case  UYG_BGD_CH_O:
		case  UYG_BGD_CH_A:
			ret=UYG_UN_CH_6;
			break;
		case  UYG_BGD_X_Y:
		case  UYG_BGD_X_B:
		case  UYG_BGD_X_O:
		case  UYG_BGD_X_A:
			ret=UYG_UN_X_6;
			break;
		case  UYG_BGD_D_Y:
		case  UYG_BGD_D_A:
			ret=UYG_UN_D_6;
			break;
		case  UYG_BGD_R_Y:
		case  UYG_BGD_R_A:
			ret=UYG_UN_R_6;
			break;
		case  UYG_BGD_Z_Y:
		case  UYG_BGD_Z_A:
			ret=UYG_UN_Z_6;
			break;
		case  UYG_BGD_ZZ_Y:
		case  UYG_BGD_ZZ_A:
			ret=UYG_UN_ZZ_6;
			break;
		case  UYG_BGD_S_Y:
		case  UYG_BGD_S_B:
		case  UYG_BGD_S_O:
		case  UYG_BGD_S_A:
			ret=UYG_UN_S_6;
			break;
		case  UYG_BGD_SH_Y:
		case  UYG_BGD_SH_B:
		case  UYG_BGD_SH_O:
		case  UYG_BGD_SH_A:
			ret=UYG_UN_SH_6;
			break;
		case  UYG_BGD_GH_Y:
		case  UYG_BGD_GH_B:
		case  UYG_BGD_GH_O:
		case  UYG_BGD_GH_A:
			ret=UYG_UN_GH_6;
			break;
		case  UYG_BGD_F_Y:
		case  UYG_BGD_F_B:
		case  UYG_BGD_F_O:
		case  UYG_BGD_F_A:
			ret=UYG_UN_F_6;
			break;
		case  UYG_BGD_Q_Y:
		case  UYG_BGD_Q_B:
		case  UYG_BGD_Q_O:
		case  UYG_BGD_Q_A:
			ret=UYG_UN_Q_6;
			break;
		case  UYG_BGD_K_Y:
		case  UYG_BGD_K_B:
		case  UYG_BGD_K_O:
		case  UYG_BGD_K_A:
			ret=UYG_UN_K_6;
			break;
		case  UYG_BGD_G_Y:
		case  UYG_BGD_G_B:
		case  UYG_BGD_G_O:
		case  UYG_BGD_G_A:
			ret=UYG_UN_G_6 ;
			break;
		case  UYG_BGD_NG_Y:
		case  UYG_BGD_NG_B:
		case  UYG_BGD_NG_O:
		case  UYG_BGD_NG_A:
			ret=UYG_UN_NG_6 ;
			break;
		case  UYG_BGD_L_Y:
		case  UYG_BGD_L_B:
		case  UYG_BGD_L_O:
		case  UYG_BGD_L_A:
			ret=UYG_UN_L_6 ;
			break;
		case  UYG_BGD_M_Y:
		case  UYG_BGD_M_B:
		case  UYG_BGD_M_O:
		case  UYG_BGD_M_A:
			ret=UYG_UN_M_6 ;
			break;
		case  UYG_BGD_N_Y:
		case  UYG_BGD_N_B:
		case  UYG_BGD_N_O:
		case  UYG_BGD_N_A:
			ret=UYG_UN_N_6;
			break;
		case  UYG_BGD_H_Y:
		case  UYG_BGD_H_A:
		case  UYG_BGD_H_B:
		case  UYG_BGD_H_O:
			ret=UYG_UN_H_6 ;
			break;
		case  UYG_BGD_O_Y:
		case  UYG_BGD_O_A:
			ret=UYG_UN_O_6 ;
			break;
		case  UYG_BGD_U_Y:
		case  UYG_BGD_U_A:
			ret=UYG_UN_U_6 ;
			break;
		case  UYG_BGD_OO_Y:
		case  UYG_BGD_OO_A:
			ret=UYG_UN_OO_6;
			break;
		case  UYG_BGD_UU_Y:
		case  UYG_BGD_UU_A:
			ret=UYG_UN_UU_6;
			break;
		case  UYG_BGD_W_Y:
		case  UYG_BGD_W_A:
			ret=UYG_UN_W_6;
			break;
		case  UYG_BGD_EE_Y:
		case  UYG_BGD_EE_B:
		case  UYG_BGD_EE_O:
		case  UYG_BGD_EE_A:
			ret=UYG_UN_EE_6;
			break;
		case  UYG_BGD_I_Y:
		case  UYG_BGD_I_B:
		case  UYG_BGD_I_O:
		case  UYG_BGD_I_A:
			ret=UYG_UN_I_6 ;
			break;
		case  UYG_BGD_Y_Y:
		case  UYG_BGD_Y_B:
		case  UYG_BGD_Y_O:
		case  UYG_BGD_Y_A:
			ret=UYG_UN_Y_6 ;
			break;
		case  UYG_BGD_LA_Y:
		case  UYG_BGD_LA_A:
			ret=UYG_UN_LA_6;
			break;
		case  UYG_BGD_HM_Y:
		case  UYG_BGD_HM_O:
		case  UYG_BGD_HM_A:
		case  UYG_BGD_HM_B:
			ret=UYG_UN_HM_6;
			break;
		case  UYG_BGD_UNDESH:    		//0xFAF5 //Undesh Belgisi
			ret=UYG_UN_UNDESH;
			break;
		case  UYG_BGD_SOL_K_TIRNAQ:		//0xFAF9 //Sol Tirnaq(
			ret=UYG_UN_SOL_K_TIRNAQ;
			break;
		case  UYG_BGD_ONG_K_TIRNAQ:		//0xFAF7 //Ong tirnaq)
			ret=UYG_UN_ONG_K_TIRNAQ;
			break;
		case  UYG_BGD_YULTUZ:			//0xF9EF //Yultuz belgisi
			ret=UYG_UN_YULTUZ;
			break;
		case  UYG_BGD_QOSHUSH:			//0xF9FA //Qoshush Belgisi
			ret=UYG_UN_QOSHUSH;
			break;
		case  UYG_BGD_PESH:      		//0xFAF0 //Pesh
			ret=UYG_UN_PESH;
			break;
		case  UYG_BGD_BOGHUM:			//0xFAEF //Boghum ayrish belgisi, Sozlerni Sozush uchunmu ishlitilidu
			ret=UYG_UKY_BOGHUM;
			break;
		case  UYG_BGD_CHEKIT:			//0xFAf1 //Chekit
			ret=UYG_UN_CHEKIT;
			break;
		case  UYG_BGD_0:				//0xF9F0 // Nol
			ret=UYG_UN_0;
			break;
		case  UYG_BGD_1:				//0xF9F1 // Bir
			ret=UYG_UN_1;
			break;
		case  UYG_BGD_2:				//0xF9F2 // Ikki
			ret=UYG_UN_2;
			break;
		case  UYG_BGD_3:				//0xF9F3 // Uch
			ret=UYG_UN_3;
			break;
		case  UYG_BGD_4:				//0xF9F4 // Tort
			ret=UYG_UN_4;
			break;
		case  UYG_BGD_5:				//0xF9F5 // Besh
			ret=UYG_UN_5;
			break;
		case  UYG_BGD_6:				//0xF9F6 // Alte
			ret=UYG_UN_6;
			break;
		case  UYG_BGD_7:				//0xF9F7 // Yette
			ret=UYG_UN_7;
			break;
		case  UYG_BGD_8:				//0xF9F8 // Sekkiz
			ret=UYG_UN_8;
			break;
		case  UYG_BGD_9:				//0xF9F9 // Toqquz
			ret=UYG_UN_9;
			break;
		case  UYG_BGD_QOSHCHEKIT:		//0xFAF3 // Qosh Chekit
			ret=UYG_UN_QOSHCHEKIT;
			break;
		case  UYG_BGD_CHEKITPESH: 		//0xFAF2 // Chekitlik Pesh
			ret=UYG_UN_CHEKITPESH;
			break;
		case  UYG_BGD_CHONG:			//0xFAFB // ChongBelgisi
			ret=UYG_UN_CHONG;
			break;
		case  UYG_BGD_KICHIK:				//0xFAFD // Kichik Belgisi
			ret=UYG_UN_KICHIK;
			break;
		case  UYG_BGD_SOAL:					//0xFAF6 // Soal Belgisi
			ret=UYG_UN_SOAL;
			break;
		case  UYG_BGD_SOL_O_TIRNAQ:			//FAFE // Sol Ottura Tirnaq
			ret=UYG_UN_SOL_O_TIRNAQ;
			break;
		case  UYG_BGD_ONG_O_TIRNAQ:			//FAFC // ONG Ottura Tirnaq
			ret=UYG_UN_ONG_O_TIRNAQ;
			break;
		case  UYG_BGD_PESSIZIQ:				//FAF4 // Sol Ottura Tirnaq
			ret=UYG_UN_PESSIZIQ;
			break;
		default:
			ret=gGB2312_toUnicode(Herp);
			break;
	}
	return ret;
}
*/

void gDoEvents(void)
{
	MSG msg;
	while(PeekMessage(&msg,NULL,0,0,PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

wchar_t *gUGetUnicodeBuf(UINT codePage,char *Buf)
{
	ULONG wLen;
	wchar_t *wBuf;
	ULONG len;

	len=strlen(Buf);
	wLen=MultiByteToWideChar(codePage,0,Buf,len,NULL,0);
	wBuf=new wchar_t[wLen+1];

	if(wBuf==NULL)
	{
		return NULL;
	}
	wLen=MultiByteToWideChar(codePage,0,Buf,len,wBuf,wLen+1);
	wBuf[wLen]=0x0;
	return  wBuf;
}

void gUInitUnicodeCode(void)
{
	g_Unicode[UYGIN_A ].Code[U_6]=		 UYG_UN_A_6 ;
	g_Unicode[UYGIN_A ].Code[U_YALGHUZ]= UYG_UN_A_Y ;
	g_Unicode[UYGIN_A ].Code[U_BASH]=    UYG_UN_A_Y ;
	g_Unicode[UYGIN_A ].Code[U_OTTURA]=  UYG_UN_A_A ;
	g_Unicode[UYGIN_A ].Code[U_AYAQ]=    UYG_UN_A_A ;
	g_Unicode[UYGIN_A ].Ulinish=false;

	g_Unicode[UYGIN_E ].Code[U_6]=       UYG_UN_E_6 ;
	g_Unicode[UYGIN_E ].Code[U_YALGHUZ]= UYG_UN_E_Y ;
	g_Unicode[UYGIN_E ].Code[U_BASH]=    UYG_UN_E_Y ;
	g_Unicode[UYGIN_E ].Code[U_OTTURA]=  UYG_UN_E_A ;
	g_Unicode[UYGIN_E ].Code[U_AYAQ]=    UYG_UN_E_A ;
	g_Unicode[UYGIN_E ].Ulinish=false;

	g_Unicode[UYGIN_B ].Code[U_6]=       UYG_UN_B_6 ;
	g_Unicode[UYGIN_B ].Code[U_YALGHUZ]= UYG_UN_B_Y ;
	g_Unicode[UYGIN_B ].Code[U_BASH]=    UYG_UN_B_B ;
	g_Unicode[UYGIN_B ].Code[U_OTTURA]=  UYG_UN_B_O ;
	g_Unicode[UYGIN_B ].Code[U_AYAQ]=    UYG_UN_B_A ;
	g_Unicode[UYGIN_B ].Ulinish=true;

	g_Unicode[UYGIN_P ].Code[U_6]=       UYG_UN_P_6 ;
	g_Unicode[UYGIN_P ].Code[U_YALGHUZ]= UYG_UN_P_Y ;
	g_Unicode[UYGIN_P ].Code[U_BASH]=    UYG_UN_P_B ;
	g_Unicode[UYGIN_P ].Code[U_OTTURA]=  UYG_UN_P_O ;
	g_Unicode[UYGIN_P ].Code[U_AYAQ]=    UYG_UN_P_A ;
	g_Unicode[UYGIN_P ].Ulinish=true;

	g_Unicode[UYGIN_T ].Code[U_6]=       UYG_UN_T_6 ;
	g_Unicode[UYGIN_T ].Code[U_YALGHUZ]= UYG_UN_T_Y ;
	g_Unicode[UYGIN_T ].Code[U_BASH]=    UYG_UN_T_B ;
	g_Unicode[UYGIN_T ].Code[U_OTTURA]=  UYG_UN_T_O ;
	g_Unicode[UYGIN_T ].Code[U_AYAQ]=    UYG_UN_T_A ;
	g_Unicode[UYGIN_T ].Ulinish=true;

	g_Unicode[UYGIN_J ].Code[U_6]=		  UYG_UN_J_6 ;
	g_Unicode[UYGIN_J ].Code[U_YALGHUZ]= UYG_UN_J_Y ;
	g_Unicode[UYGIN_J ].Code[U_BASH]=    UYG_UN_J_B ;
	g_Unicode[UYGIN_J ].Code[U_OTTURA]=  UYG_UN_J_O ;
	g_Unicode[UYGIN_J ].Code[U_AYAQ]=    UYG_UN_J_A ;
	g_Unicode[UYGIN_J ].Ulinish=true;

	g_Unicode[UYGIN_CH].Code[U_6]=		  UYG_UN_CH_6;
	g_Unicode[UYGIN_CH].Code[U_YALGHUZ]= UYG_UN_CH_Y;
	g_Unicode[UYGIN_CH].Code[U_BASH]=    UYG_UN_CH_B;
	g_Unicode[UYGIN_CH].Code[U_OTTURA]=  UYG_UN_CH_O;
	g_Unicode[UYGIN_CH].Code[U_AYAQ]=    UYG_UN_CH_A;
	g_Unicode[UYGIN_CH].Ulinish=true;

	g_Unicode[UYGIN_X ].Code[U_6]=		  UYG_UN_X_6 ;
	g_Unicode[UYGIN_X ].Code[U_YALGHUZ]= UYG_UN_X_Y ;
	g_Unicode[UYGIN_X ].Code[U_BASH]=    UYG_UN_X_B ;
	g_Unicode[UYGIN_X ].Code[U_OTTURA]=  UYG_UN_X_O ;
	g_Unicode[UYGIN_X ].Code[U_AYAQ]=    UYG_UN_X_A ;
	g_Unicode[UYGIN_X ].Ulinish=true;

	g_Unicode[UYGIN_D ].Code[U_6]=		  UYG_UN_D_6 ;
	g_Unicode[UYGIN_D ].Code[U_YALGHUZ]= UYG_UN_D_Y ;
	g_Unicode[UYGIN_D ].Code[U_BASH]=    UYG_UN_D_Y ;
	g_Unicode[UYGIN_D ].Code[U_OTTURA]=  UYG_UN_D_A ;
	g_Unicode[UYGIN_D ].Code[U_AYAQ]=    UYG_UN_D_A ;
	g_Unicode[UYGIN_D ].Ulinish=false;

	g_Unicode[UYGIN_R ].Code[U_6]=       UYG_UN_R_6 ;
	g_Unicode[UYGIN_R ].Code[U_YALGHUZ]= UYG_UN_R_Y ;
	g_Unicode[UYGIN_R ].Code[U_BASH]=    UYG_UN_R_Y ;
	g_Unicode[UYGIN_R ].Code[U_OTTURA]=  UYG_UN_R_A ;
	g_Unicode[UYGIN_R ].Code[U_AYAQ]=    UYG_UN_R_A ;
	g_Unicode[UYGIN_R ].Ulinish=false;

	g_Unicode[UYGIN_Z ].Code[U_6]=       UYG_UN_Z_6 ;
	g_Unicode[UYGIN_Z ].Code[U_YALGHUZ]= UYG_UN_Z_Y ;
	g_Unicode[UYGIN_Z ].Code[U_BASH]=    UYG_UN_Z_Y ;
	g_Unicode[UYGIN_Z ].Code[U_OTTURA]=  UYG_UN_Z_A ;
	g_Unicode[UYGIN_Z ].Code[U_AYAQ]=    UYG_UN_Z_A ;
	g_Unicode[UYGIN_Z ].Ulinish=false;

	g_Unicode[UYGIN_ZZ].Code[U_6]=       UYG_UN_ZZ_6;
	g_Unicode[UYGIN_ZZ].Code[U_YALGHUZ]= UYG_UN_ZZ_Y;
	g_Unicode[UYGIN_ZZ].Code[U_BASH]=    UYG_UN_ZZ_Y;
	g_Unicode[UYGIN_ZZ].Code[U_OTTURA]=  UYG_UN_ZZ_A;
	g_Unicode[UYGIN_ZZ].Code[U_AYAQ]=    UYG_UN_ZZ_A;
	g_Unicode[UYGIN_ZZ].Ulinish=false;

	g_Unicode[UYGIN_S ].Code[U_6]=       UYG_UN_S_6 ;
	g_Unicode[UYGIN_S ].Code[U_YALGHUZ]= UYG_UN_S_Y ;
	g_Unicode[UYGIN_S ].Code[U_BASH]=    UYG_UN_S_B ;
	g_Unicode[UYGIN_S ].Code[U_OTTURA]=  UYG_UN_S_O ;
	g_Unicode[UYGIN_S ].Code[U_AYAQ]=    UYG_UN_S_A ;
	g_Unicode[UYGIN_S ].Ulinish=true;

	g_Unicode[UYGIN_SH].Code[U_6]=       UYG_UN_SH_6;
	g_Unicode[UYGIN_SH].Code[U_YALGHUZ]= UYG_UN_SH_Y;
	g_Unicode[UYGIN_SH].Code[U_BASH]=    UYG_UN_SH_B;
	g_Unicode[UYGIN_SH].Code[U_OTTURA]=  UYG_UN_SH_O;
	g_Unicode[UYGIN_SH].Code[U_AYAQ]=    UYG_UN_SH_A;
	g_Unicode[UYGIN_SH].Ulinish=true;

	g_Unicode[UYGIN_GH].Code[U_6]=       UYG_UN_GH_6;
	g_Unicode[UYGIN_GH].Code[U_YALGHUZ]= UYG_UN_GH_Y;
	g_Unicode[UYGIN_GH].Code[U_BASH]=    UYG_UN_GH_B;
	g_Unicode[UYGIN_GH].Code[U_OTTURA]=  UYG_UN_GH_O;
	g_Unicode[UYGIN_GH].Code[U_AYAQ]=    UYG_UN_GH_A;
	g_Unicode[UYGIN_GH].Ulinish=true;

	g_Unicode[UYGIN_F ].Code[U_6]=       UYG_UN_F_6 ;
	g_Unicode[UYGIN_F ].Code[U_YALGHUZ]= UYG_UN_F_Y ;
	g_Unicode[UYGIN_F ].Code[U_BASH]=    UYG_UN_F_B ;
	g_Unicode[UYGIN_F ].Code[U_OTTURA]=  UYG_UN_F_O ;
	g_Unicode[UYGIN_F ].Code[U_AYAQ]=    UYG_UN_F_A ;
	g_Unicode[UYGIN_F ].Ulinish=true;

	g_Unicode[UYGIN_Q ].Code[U_6]=       UYG_UN_Q_6 ;
	g_Unicode[UYGIN_Q ].Code[U_YALGHUZ]= UYG_UN_Q_Y ;
	g_Unicode[UYGIN_Q ].Code[U_BASH]=    UYG_UN_Q_B ;
	g_Unicode[UYGIN_Q ].Code[U_OTTURA]=  UYG_UN_Q_O ;
	g_Unicode[UYGIN_Q ].Code[U_AYAQ]=    UYG_UN_Q_A ;
	g_Unicode[UYGIN_Q ].Ulinish=true;

	g_Unicode[UYGIN_K ].Code[U_6]=       UYG_UN_K_6 ;
	g_Unicode[UYGIN_K ].Code[U_YALGHUZ]= UYG_UN_K_Y ;
	g_Unicode[UYGIN_K ].Code[U_BASH]=    UYG_UN_K_B ;
	g_Unicode[UYGIN_K ].Code[U_OTTURA]=  UYG_UN_K_O ;
	g_Unicode[UYGIN_K ].Code[U_AYAQ]=    UYG_UN_K_A ;
	g_Unicode[UYGIN_K ].Ulinish=true;

	g_Unicode[UYGIN_G ].Code[U_6]=       UYG_UN_G_6 ;
	g_Unicode[UYGIN_G ].Code[U_YALGHUZ]= UYG_UN_G_Y ;
	g_Unicode[UYGIN_G ].Code[U_BASH]=    UYG_UN_G_B ;
	g_Unicode[UYGIN_G ].Code[U_OTTURA]=  UYG_UN_G_O ;
	g_Unicode[UYGIN_G ].Code[U_AYAQ]=    UYG_UN_G_A ;
	g_Unicode[UYGIN_G ].Ulinish=true;

	g_Unicode[UYGIN_NG].Code[U_6]=       UYG_UN_NG_6;
	g_Unicode[UYGIN_NG].Code[U_YALGHUZ]= UYG_UN_NG_Y;
	g_Unicode[UYGIN_NG].Code[U_BASH]=    UYG_UN_NG_B;
	g_Unicode[UYGIN_NG].Code[U_OTTURA]=  UYG_UN_NG_O;
	g_Unicode[UYGIN_NG].Code[U_AYAQ]=    UYG_UN_NG_A;
	g_Unicode[UYGIN_NG].Ulinish=true;

	g_Unicode[UYGIN_L ].Code[U_6]=       UYG_UN_L_6 ;
	g_Unicode[UYGIN_L ].Code[U_YALGHUZ]= UYG_UN_L_Y ;
	g_Unicode[UYGIN_L ].Code[U_BASH]=    UYG_UN_L_B ;
	g_Unicode[UYGIN_L ].Code[U_OTTURA]=  UYG_UN_L_O ;
	g_Unicode[UYGIN_L ].Code[U_AYAQ]=    UYG_UN_L_A ;
	g_Unicode[UYGIN_L ].Ulinish=true;

	g_Unicode[UYGIN_M ].Code[U_6]=       UYG_UN_M_6 ;
	g_Unicode[UYGIN_M ].Code[U_YALGHUZ]= UYG_UN_M_Y ;
	g_Unicode[UYGIN_M ].Code[U_BASH]=    UYG_UN_M_B ;
	g_Unicode[UYGIN_M ].Code[U_OTTURA]=  UYG_UN_M_O ;
	g_Unicode[UYGIN_M ].Code[U_AYAQ]=    UYG_UN_M_A ;
	g_Unicode[UYGIN_M ].Ulinish=true;

	g_Unicode[UYGIN_N ].Code[U_6]=       UYG_UN_N_6 ;
	g_Unicode[UYGIN_N ].Code[U_YALGHUZ]= UYG_UN_N_Y ;
	g_Unicode[UYGIN_N ].Code[U_BASH]=    UYG_UN_N_B ;
	g_Unicode[UYGIN_N ].Code[U_OTTURA]=  UYG_UN_N_O ;
	g_Unicode[UYGIN_N ].Code[U_AYAQ]=    UYG_UN_N_A ;
	g_Unicode[UYGIN_N ].Ulinish=true;

	g_Unicode[UYGIN_H ].Code[U_6]=       UYG_UN_H_6 ;
	g_Unicode[UYGIN_H ].Code[U_YALGHUZ]= UYG_UN_H_Y ;
	g_Unicode[UYGIN_H ].Code[U_BASH]=    UYG_UN_H_B ;
	g_Unicode[UYGIN_H ].Code[U_OTTURA]=  UYG_UN_H_O ;
	g_Unicode[UYGIN_H ].Code[U_AYAQ]=    UYG_UN_H_A ;
	g_Unicode[UYGIN_H ].Ulinish=true;

	g_Unicode[UYGIN_O ].Code[U_6]=       UYG_UN_O_6 ;
	g_Unicode[UYGIN_O ].Code[U_YALGHUZ]= UYG_UN_O_Y ;
	g_Unicode[UYGIN_O ].Code[U_BASH]=    UYG_UN_O_Y ;
	g_Unicode[UYGIN_O ].Code[U_OTTURA]=  UYG_UN_O_A ;
	g_Unicode[UYGIN_O ].Code[U_AYAQ]=    UYG_UN_O_A ;
	g_Unicode[UYGIN_O ].Ulinish=false;

	g_Unicode[UYGIN_U ].Code[U_6]=       UYG_UN_U_6 ;
	g_Unicode[UYGIN_U ].Code[U_YALGHUZ]= UYG_UN_U_Y ;
	g_Unicode[UYGIN_U ].Code[U_BASH]=    UYG_UN_U_Y ;
	g_Unicode[UYGIN_U ].Code[U_OTTURA]=  UYG_UN_U_A ;
	g_Unicode[UYGIN_U ].Code[U_AYAQ]=    UYG_UN_U_A ;
	g_Unicode[UYGIN_U ].Ulinish=false;

	g_Unicode[UYGIN_OO].Code[U_6]=       UYG_UN_OO_6;
	g_Unicode[UYGIN_OO].Code[U_YALGHUZ]= UYG_UN_OO_Y;
	g_Unicode[UYGIN_OO].Code[U_BASH]=    UYG_UN_OO_Y;
	g_Unicode[UYGIN_OO].Code[U_OTTURA]=  UYG_UN_OO_A;
	g_Unicode[UYGIN_OO].Code[U_AYAQ]=    UYG_UN_OO_A;
	g_Unicode[UYGIN_OO].Ulinish=false;

	g_Unicode[UYGIN_UU].Code[U_6]=       UYG_UN_UU_6;
	g_Unicode[UYGIN_UU].Code[U_YALGHUZ]= UYG_UN_UU_Y;
	g_Unicode[UYGIN_UU].Code[U_BASH]=    UYG_UN_UU_Y;
	g_Unicode[UYGIN_UU].Code[U_OTTURA]=  UYG_UN_UU_A;
	g_Unicode[UYGIN_UU].Code[U_AYAQ]=    UYG_UN_UU_A;
	g_Unicode[UYGIN_UU].Ulinish=false;

	g_Unicode[UYGIN_W ].Code[U_6]=       UYG_UN_W_6 ;
	g_Unicode[UYGIN_W ].Code[U_YALGHUZ]= UYG_UN_W_Y ;
	g_Unicode[UYGIN_W ].Code[U_BASH]=    UYG_UN_W_Y ;
	g_Unicode[UYGIN_W ].Code[U_OTTURA]=  UYG_UN_W_A ;
	g_Unicode[UYGIN_W ].Code[U_AYAQ]=    UYG_UN_W_A ;
	g_Unicode[UYGIN_W ].Ulinish=false;

	g_Unicode[UYGIN_EE].Code[U_6]=       UYG_UN_EE_6;
	g_Unicode[UYGIN_EE].Code[U_YALGHUZ]= UYG_UN_EE_Y;
	g_Unicode[UYGIN_EE].Code[U_BASH]=    UYG_UN_EE_B;
	g_Unicode[UYGIN_EE].Code[U_OTTURA]=  UYG_UN_EE_O;
	g_Unicode[UYGIN_EE].Code[U_AYAQ]=    UYG_UN_EE_A;
	g_Unicode[UYGIN_EE].Ulinish=true;

	g_Unicode[UYGIN_I ].Code[U_6]=       UYG_UN_I_6 ;
	g_Unicode[UYGIN_I ].Code[U_YALGHUZ]= UYG_UN_I_Y ;
	g_Unicode[UYGIN_I ].Code[U_BASH]=    UYG_UN_I_B ;
	g_Unicode[UYGIN_I ].Code[U_OTTURA]=  UYG_UN_I_O ;
	g_Unicode[UYGIN_I ].Code[U_AYAQ]=    UYG_UN_I_A ;
	g_Unicode[UYGIN_I ].Ulinish=true;

	g_Unicode[UYGIN_Y].Code[U_6]=        UYG_UN_Y_6 ;
	g_Unicode[UYGIN_Y].Code[U_YALGHUZ]=  UYG_UN_Y_Y ;
	g_Unicode[UYGIN_Y].Code[U_BASH]=     UYG_UN_Y_B ;
	g_Unicode[UYGIN_Y].Code[U_OTTURA]=   UYG_UN_Y_O ;
	g_Unicode[UYGIN_Y].Code[U_AYAQ]=     UYG_UN_Y_A ;
	g_Unicode[UYGIN_Y].Ulinish=true;

	g_Unicode[UYGIN_LA].Code[U_6]=       UYG_UN_LA_6;
	g_Unicode[UYGIN_LA].Code[U_YALGHUZ]= UYG_UN_LA_Y;
	g_Unicode[UYGIN_LA].Code[U_BASH]=    UYG_UN_LA_Y;
	g_Unicode[UYGIN_LA].Code[U_OTTURA]=  UYG_UN_LA_A;
	g_Unicode[UYGIN_LA].Code[U_AYAQ]=    UYG_UN_LA_A;
	g_Unicode[UYGIN_LA].Ulinish=false;

	g_Unicode[UYGIN_HM].Code[U_6]=       UYG_UN_HM_6;
	g_Unicode[UYGIN_HM].Code[U_YALGHUZ]= UYG_UN_HM_Y;
	g_Unicode[UYGIN_HM].Code[U_BASH]=    UYG_UN_HM_Y;
	g_Unicode[UYGIN_HM].Code[U_OTTURA]=  UYG_UN_HM_O;
	g_Unicode[UYGIN_HM].Code[U_AYAQ]=    UYG_UN_HM_O;
	g_Unicode[UYGIN_HM].Ulinish=true;
}

wchar_t gUGetHerpFromNotepad(wchar_t Herp)
{
	wchar_t nHerp;
	switch(Herp)
	{
		case 35:
		case 60:
		case 103:
			nHerp=UYG_UN_E_6;
			break;
		case 36:
		case 62:
		case 89:
		case 121:
			nHerp=UYG_UN_Y_6;
			break;
		case 37:
			nHerp=UYG_UN_PIRSENT;
			break;
		case 38:
		case 124:
		case 127:
		case 120:
			nHerp=UYG_UN_SH_6;
			break;
		case 42:
			nHerp=UYG_UN_YULTUZ;
			break;
		case 44:
			nHerp=UYG_UN_PESH;
			break;
		case 47:
		case 87:
			nHerp=UYG_UN_HM_6;
			break;
		case 61:
		case 69:
		case 101:
			nHerp=UYG_UN_EE_6;
			break;
		case 63:
			nHerp=UYG_UN_SOAL;
			break;
		case 64:
		case 108:
			nHerp=UYG_UN_L_6;
			break;
		case 65:
		case 102:
			nHerp=UYG_UN_A_6;
			break;
		case 66:
		case 98:
			nHerp=UYG_UN_B_6;
			break;
		case 67:
		case 88:
		case 96:
		case 99:
			nHerp=UYG_UN_GH_6;
			break;
		case 68:
			nHerp=UYG_UN_ZZ_6;
			break;
		case 70:
			nHerp=UYG_UN_F_6;
			break;
		case 71:
			nHerp=UYG_UN_G_6;
			break;
		case 72:
		case 94:
		case 95:
			nHerp=UYG_UN_X_6;
			break;
		case 73:
		case 105:
			nHerp=UYG_UN_NG_6;
			break;
		case 74:
		case 90:
		case 91:
			nHerp=UYG_UN_J_6;
			break;
		case 75:
			nHerp=UYG_UN_OO_6;
			break;
		case 76:
			nHerp=UYG_UN_LA_6;
			break;
		case 77:
		case 109:
			nHerp=UYG_UN_M_6;
			break;
		case 78:
		case 110:
			nHerp=UYG_UN_N_6;
			break;
		case 79:
		case 85:
		case 106:
			nHerp=UYG_UN_Q_6;
			break;
		case 80:
		case 112:
			nHerp=UYG_UN_P_6;
			break;
		case 81:
		case 107:
			nHerp=UYG_UN_K_6;
			break;
		case 82:
		case 83:
			nHerp=UYG_UN_F_6;
			break;
		case 84:
		case 116:
			nHerp=UYG_UN_T_6;
			break;
		case 86:
		case 97:
			nHerp=UYG_UN_H_6;
			break;
		case 92:
		case 93:
		case 113:
			nHerp=UYG_UN_CH_6;
			break;
		case 100:
			nHerp=UYG_UN_D_6;
			break;
		case 104:
		case 125:
		case 126:
			nHerp=UYG_UN_I_6;
			break;
		case 111:
			nHerp=UYG_UN_O_6;
			break;
		case 114:
			nHerp=UYG_UN_R_6;
			break;
		case 115:
		case 123:
			nHerp=UYG_UN_S_6;
			break;
		case 117:
			nHerp=UYG_UN_U_6;
			break;
		case 118:
			nHerp=UYG_UN_UU_6;
			break;
		case 119:
			nHerp=UYG_UN_W_6;
			break;
		case 122:
			nHerp=UYG_UN_Z_6;
			break;
		default:
			nHerp=Herp;
			break;
	}
	return nHerp;
}

wchar_t gUGetHerpFromIlikyurt(wchar_t Herp)
{
	wchar_t nHerp=0x00;
	switch(Herp)
	{
		case 0x0022:
		case 0x0023:
			nHerp=UYG_UN_HM_6;
			break;
		case 0x0024:
		case 0x0025:
			nHerp=UYG_UN_LA_6;
			break;
		case 0x0026:
		case 0x0027:
			nHerp=UYG_UN_A_6;
			break;
		case 0x0028:
		case 0x0029:
			nHerp=UYG_UN_E_6;
			break;
		case 0x002A:
		case 0x002B:
		case 0x002D:
		case 0x005B:
			nHerp=UYG_UN_B_6;
			break;
		case 0x002C:
			nHerp=UYG_UN_PESH;
			break;
		case 0x002E:
			nHerp=UYG_UN_CHEKIT;
			break;
		case 0x002F:
		case 0x0030:
		case 0x0031:
		case 0x005E:
			nHerp=UYG_UN_P_6;
			break;
		case 0x0032:
		case 0x0033:
		case 0x0034:
		case 0x0061:
			nHerp=UYG_UN_T_6;
			break;
		case 0x0035:
		case 0x0036:
		case 0x0037:
		case 0x0038:
			nHerp=UYG_UN_J_6;
			break;
		case 0x0039:
		case 0x003A:
		case 0x003C:
		case 0x003D:
			nHerp=UYG_UN_CH_6;
			break;
		case 0x003B:
			nHerp=UYG_UN_CHEKITPESH;
			break;
		case 0x003E:
		case 0x0040:
		case 0x0041:
		case 0x0042:
			nHerp=UYG_UN_X_6;
			break;
		case 0x003F:
			nHerp=UYG_UN_SOAL;
			break;
		case 0x0043:
			nHerp=UYG_UN_D_6;
			break;
		case 0x0044:
			nHerp=UYG_UN_R_6;
			break;
		case 0x0045:
			nHerp=UYG_UN_Z_6;
			break;
		case 0x0046:
			nHerp=UYG_UN_ZZ_6;
			break;
		case 0x0047:
		case 0x0048:
		case 0x0049:
		case 0x004A:
			nHerp=UYG_UN_S_6;
			break;
		case 0x004B:
		case 0x004C:
		case 0x004D:
		case 0x004E:
			nHerp=UYG_UN_SH_6;
			break;
		case 0x004F:
		case 0x0050:
		case 0x0051:
		case 0x0052:
			nHerp=UYG_UN_GH_6;
			break;
		case 0x0053:
		case 0x0054:
		case 0x0055:
			nHerp=UYG_UN_F_6;
			break;
		case 0x0056:
		case 0x0057:
		case 0x0058:
			nHerp=UYG_UN_Q_6;
			break;
		case 0x0059:
		case 0x005A:
			nHerp=UYG_UN_G_6;
			break;
		case 0x005C:
		case 0x005D:
			nHerp=UYG_UN_K_6;
			break;
		case 0x005F:
		case 0x0060:
			nHerp=UYG_UN_NG_6;
			break;
		case 0x0062:
		case 0x0063:
		case 0x0064:
			nHerp=UYG_UN_L_6;
			break;
		case 0x0065:
		case 0x0066:
		case 0x0067:
		case 0x0068:
			nHerp=UYG_UN_M_6;
			break;
		case 0x0069:
		case 0x006A:
		case 0x006B:
			nHerp=UYG_UN_N_6;
			break;
		case 0x006C:
		case 0x006D:
			nHerp=UYG_UN_H_6;
			break;
		case 0x006E:
			nHerp=UYG_UN_O_6;
			break;
		case 0x006F:
			nHerp=UYG_UN_U_6;
			break;
		case 0x0070:
			nHerp=UYG_UN_OO_6;
			break;
		case 0x0071:
			nHerp=UYG_UN_UU_6;
			break;
		case 0x0072:
			nHerp=UYG_UN_W_6;
			break;
		case 0x0073:
		case 0x0074:
		case 0x0075:
		case 0x0076:
			nHerp=UYG_UN_EE_6;
			break;
		case 0x0077:
		case 0x0078:
		case 0x0079:
		case 0x007A:
			nHerp=UYG_UN_I_6;
			break;
		case 0x007B:
		case 0x007C:
		case 0x007D:
		case 0x007E:
			nHerp=UYG_UN_Y_6;
			break;
		default:
			nHerp=Herp;
			break;
	}
	return nHerp;
}

wchar_t gUGetSlawiyan(wchar_t Herp)
{
    wchar_t ret=Herp;
	switch(Herp)
	{
		case  UYG_UN_A_6:
		case  UYG_UN_A_Y:
		case  UYG_UN_A_A:
			ret=0x0430;/*а*/
			break;
		case  UYG_UN_E_6:
		case  UYG_UN_E_Y:
		case  UYG_UN_E_A:
			ret=0x04d9;/*ә*/
			break;
		case  UYG_UN_B_6:
		case  UYG_UN_B_Y:
		case  UYG_UN_B_B:
		case  UYG_UN_B_O:
		case  UYG_UN_B_A:
			ret=0x0431;/*б*/
			break;
		case  UYG_UN_P_6:
		case  UYG_UN_P_Y:
		case  UYG_UN_P_B:
		case  UYG_UN_P_O:
		case  UYG_UN_P_A:
			ret=0x043f;/*п*/
			break;
		case  UYG_UN_T_6:
		case  UYG_UN_T_Y:
		case  UYG_UN_T_B:
		case  UYG_UN_T_O:
		case  UYG_UN_T_A:
			ret=0x0442;/*т*/
			break;
		case  UYG_UN_J_6:
		case  UYG_UN_J_Y:
		case  UYG_UN_J_B:
		case  UYG_UN_J_O:
		case  UYG_UN_J_A:
			ret=0x0497;/*җ*/
			break;
		case  UYG_UN_CH_6:
		case  UYG_UN_CH_Y:
		case  UYG_UN_CH_B:
		case  UYG_UN_CH_O:
		case  UYG_UN_CH_A:
			ret=0x0447;/*ч*/
			break;
		case  UYG_UN_X_6:
		case  UYG_UN_X_Y:
		case  UYG_UN_X_B:
		case  UYG_UN_X_O:
		case  UYG_UN_X_A:
			ret=0x0445;/*х*/
			break;
		case  UYG_UN_D_6:
		case  UYG_UN_D_Y:
		case  UYG_UN_D_A:
			ret=0x0434;/*д*/
			break;
		case  UYG_UN_R_6:
		case  UYG_UN_R_Y:
		case  UYG_UN_R_A:
			ret=0x0440;/*р*/
			break;
		case  UYG_UN_Z_6:
		case  UYG_UN_Z_Y:
		case  UYG_UN_Z_A:
			ret=0x0437;/*з*/
			break;
		case  UYG_UN_ZZ_6:
		case  UYG_UN_ZZ_Y:
		case  UYG_UN_ZZ_A:
			ret=0x0436;/*ж*/
			break;
		case  UYG_UN_S_6:
		case  UYG_UN_S_Y:
		case  UYG_UN_S_B:
		case  UYG_UN_S_O:
		case  UYG_UN_S_A:
			ret=0x0441;/*с*/
			break;
		case  UYG_UN_SH_6:
		case  UYG_UN_SH_Y:
		case  UYG_UN_SH_B:
		case  UYG_UN_SH_O:
		case  UYG_UN_SH_A:
			ret=0x0448;/*ш*/
			break;
		case  UYG_UN_GH_6:
		case  UYG_UN_GH_Y:
		case  UYG_UN_GH_B:
		case  UYG_UN_GH_O:
		case  UYG_UN_GH_A:
			ret=0x0493;/*ғ*/
			break;
		case  UYG_UN_F_6:
		case  UYG_UN_F_Y:
		case  UYG_UN_F_B:
		case  UYG_UN_F_O:
		case  UYG_UN_F_A:
			ret=0x0444;/*ф*/
			break;
		case  UYG_UN_Q_6:
		case  UYG_UN_Q_Y:
		case  UYG_UN_Q_B:
		case  UYG_UN_Q_O:
		case  UYG_UN_Q_A:
			ret=0x049b;/*қ*/
			break;
		case  UYG_UN_K_6:
		case  UYG_UN_K_Y:
		case  UYG_UN_K_B:
		case  UYG_UN_K_O:
		case  UYG_UN_K_A:
			ret=0x043a;/*к*/
			break;
		case  UYG_UN_G_6:
		case  UYG_UN_G_Y:
		case  UYG_UN_G_B:
		case  UYG_UN_G_O:
		case  UYG_UN_G_A:
			ret=0x0433;/*г*/
			break;
		case  UYG_UN_NG_6:
		case  UYG_UN_NG_Y:
		case  UYG_UN_NG_B:
		case  UYG_UN_NG_O:
		case  UYG_UN_NG_A:
			ret=0x04a3;/*ң*/
			break;
		case  UYG_UN_L_6:
		case  UYG_UN_L_Y:
		case  UYG_UN_L_B:
		case  UYG_UN_L_O:
		case  UYG_UN_L_A:
			ret=0x043b;/*л*/
			break;
		case  UYG_UN_M_6:
		case  UYG_UN_M_Y:
		case  UYG_UN_M_B:
		case  UYG_UN_M_O:
		case  UYG_UN_M_A:
			ret=0x043c;/*м*/
			break;
		case  UYG_UN_N_6:
		case  UYG_UN_N_Y:
		case  UYG_UN_N_B:
		case  UYG_UN_N_O:
		case  UYG_UN_N_A:
			ret=0x043d;/*н*/
			break;
		case  UYG_UN_H_6:
		case  UYG_UN_H_Y:
		case  UYG_UN_H_A:
		case  UYG_UN_H_B:
		case  UYG_UN_H_O:
		case  UYGE_UN_H_Y:   // Yulghunda Ishlitilgen
		case  UYGE_UN_H_A:   // Yulghunda ishlitilgen
			ret=0x04bb;/*һ*/
			break;
		case  UYG_UN_O_6:
		case  UYG_UN_O_Y:
		case  UYG_UN_O_A:
			ret=0x043e;/*о*/
			break;
		case  UYG_UN_U_6:
		case  UYG_UN_U_Y:
		case  UYG_UN_U_A:
			ret=0x0443;/*у*/
			break;
		case  UYG_UN_OO_6:
		case  UYG_UN_OO_Y:
		case  UYG_UN_OO_A:
			ret=0x04e9;/*ө*/
			break;
		case  UYG_UN_UU_6:
		case  UYG_UN_UU_Y:
		case  UYG_UN_UU_A:
			ret=0x04af;/*ү*/
			break;
		case  UYG_UN_W_6:
		case  UYG_UN_W_Y:
		case  UYG_UN_W_A:
			ret=0x0432;/*в*/
			break;
		case  UYG_UN_EE_6:
		case  UYG_UN_EE_Y:
		case  UYG_UN_EE_B:
		case  UYG_UN_EE_O:
		case  UYG_UN_EE_A:
			ret=0x0435;/*е*/
			break;
		case  UYG_UN_I_6:
		case  UYG_UN_I_Y:
		case  UYG_UN_I_B:
		case  UYG_UN_I_O:
		case  UYG_UN_I_A:
			ret=0x0438;/*и*/
			break;
		case  UYG_UN_Y_6:
		case  UYG_UN_Y_Y:
		case  UYG_UN_Y_B:
		case  UYG_UN_Y_O:
		case  UYG_UN_Y_A:
			ret=0x0439;/*й*/
			break;
		case  UYG_UN_HM_6:
		case  UYG_UN_HM_Y:
		case  UYG_UN_HM_O:
			ret=UYG_UN_HM_6;
			break;
		case  UYG_UN_SOAL:
			ret=UYG_UKY_SOAL;
			break;
		case  UYG_UN_PESH:
			ret=UYG_UKY_PESH;
			break;
		case  UYG_UN_PIRSENT:
			ret=UYG_UKY_PIRSENT;
			break;
		case  UYG_UN_CHEKITPESH:
            ret=UYG_UKY_CHEKITPESH;
			break;
		case  UYG_UN_YULTUZ:
            ret=UYG_UKY_YULTUZ;
			break;
		default:
			break;
	}
	return ret;
}


wchar_t gUGetTurk(wchar_t Herp)
{
    wchar_t ret=Herp;
	switch(Herp)
	{
		case  UYG_UN_A_6:
		case  UYG_UN_A_Y:
		case  UYG_UN_A_A:
			ret=L'a';
			break;
		case  UYG_UN_E_6:
		case  UYG_UN_E_Y:
		case  UYG_UN_E_A:
			ret=L'ä';
			break;
		case  UYG_UN_B_6:
		case  UYG_UN_B_Y:
		case  UYG_UN_B_B:
		case  UYG_UN_B_O:
		case  UYG_UN_B_A:
			ret=L'b';
			break;
		case  UYG_UN_P_6:
		case  UYG_UN_P_Y:
		case  UYG_UN_P_B:
		case  UYG_UN_P_O:
		case  UYG_UN_P_A:
			ret=L'p';
			break;
		case  UYG_UN_T_6:
		case  UYG_UN_T_Y:
		case  UYG_UN_T_B:
		case  UYG_UN_T_O:
		case  UYG_UN_T_A:
			ret=L't';
			break;
		case  UYG_UN_J_6:
		case  UYG_UN_J_Y:
		case  UYG_UN_J_B:
		case  UYG_UN_J_O:
		case  UYG_UN_J_A:
			ret=L'c';
			break;
		case  UYG_UN_CH_6:
		case  UYG_UN_CH_Y:
		case  UYG_UN_CH_B:
		case  UYG_UN_CH_O:
		case  UYG_UN_CH_A:
			ret=0x00e7 /*ç*/;
			break;
		case  UYG_UN_X_6:
		case  UYG_UN_X_Y:
		case  UYG_UN_X_B:
		case  UYG_UN_X_O:
		case  UYG_UN_X_A:
			ret=L'x';
			break;
		case  UYG_UN_D_6:
		case  UYG_UN_D_Y:
		case  UYG_UN_D_A:
			ret=L'd';
			break;
		case  UYG_UN_R_6:
		case  UYG_UN_R_Y:
		case  UYG_UN_R_A:
			ret=L'r';
			break;
		case  UYG_UN_Z_6:
		case  UYG_UN_Z_Y:
		case  UYG_UN_Z_A:
			ret=L'z';
			break;
		case  UYG_UN_ZZ_6:
		case  UYG_UN_ZZ_Y:
		case  UYG_UN_ZZ_A:
			ret=L'j';
			break;
		case  UYG_UN_S_6:
		case  UYG_UN_S_Y:
		case  UYG_UN_S_B:
		case  UYG_UN_S_O:
		case  UYG_UN_S_A:
			ret=L's';
			break;
		case  UYG_UN_SH_6:
		case  UYG_UN_SH_Y:
		case  UYG_UN_SH_B:
		case  UYG_UN_SH_O:
		case  UYG_UN_SH_A:
			ret=0x015f; /*Şş*/
			break;
		case  UYG_UN_GH_6:
		case  UYG_UN_GH_Y:
		case  UYG_UN_GH_B:
		case  UYG_UN_GH_O:
		case  UYG_UN_GH_A:
			ret=0x011f /*ğ*/;
			break;
		case  UYG_UN_F_6:
		case  UYG_UN_F_Y:
		case  UYG_UN_F_B:
		case  UYG_UN_F_O:
		case  UYG_UN_F_A:
			ret=L'f';
			break;
		case  UYG_UN_Q_6:
		case  UYG_UN_Q_Y:
		case  UYG_UN_Q_B:
		case  UYG_UN_Q_O:
		case  UYG_UN_Q_A:
			ret=L'q';
			break;
		case  UYG_UN_K_6:
		case  UYG_UN_K_Y:
		case  UYG_UN_K_B:
		case  UYG_UN_K_O:
		case  UYG_UN_K_A:
			ret=L'k';
			break;
		case  UYG_UN_G_6:
		case  UYG_UN_G_Y:
		case  UYG_UN_G_B:
		case  UYG_UN_G_O:
		case  UYG_UN_G_A:
			ret=L'g';
			break;
		case  UYG_UN_NG_6:
		case  UYG_UN_NG_Y:
		case  UYG_UN_NG_B:
		case  UYG_UN_NG_O:
		case  UYG_UN_NG_A:
			ret=0x00f1;/*ñ*/
			break;
		case  UYG_UN_L_6:
		case  UYG_UN_L_Y:
		case  UYG_UN_L_B:
		case  UYG_UN_L_O:
		case  UYG_UN_L_A:
			ret=L'l';
			break;
		case  UYG_UN_M_6:
		case  UYG_UN_M_Y:
		case  UYG_UN_M_B:
		case  UYG_UN_M_O:
		case  UYG_UN_M_A:
			ret=L'm';
			break;
		case  UYG_UN_N_6:
		case  UYG_UN_N_Y:
		case  UYG_UN_N_B:
		case  UYG_UN_N_O:
		case  UYG_UN_N_A:
			ret=L'n';
			break;
		case  UYG_UN_H_6:
		case  UYG_UN_H_Y:
		case  UYG_UN_H_A:
		case  UYG_UN_H_B:
		case  UYG_UN_H_O:
		case  UYGE_UN_H_Y:   // Yulghunda Ishlitilgen
		case  UYGE_UN_H_A:   // Yulghunda ishlitilgen
			ret=L'h';
			break;
		case  UYG_UN_O_6:
		case  UYG_UN_O_Y:
		case  UYG_UN_O_A:
			ret=L'o';
			break;
		case  UYG_UN_U_6:
		case  UYG_UN_U_Y:
		case  UYG_UN_U_A:
			ret=L'u';
			break;
		case  UYG_UN_OO_6:
		case  UYG_UN_OO_Y:
		case  UYG_UN_OO_A:
			ret=0x00f6; /*ö*/
			break;
		case  UYG_UN_UU_6:
		case  UYG_UN_UU_Y:
		case  UYG_UN_UU_A:
			ret=0x00fc; /*ü*/
			break;
		case  UYG_UN_W_6:
		case  UYG_UN_W_Y:
		case  UYG_UN_W_A:
			ret=L'w';
			break;
		case  UYG_UN_EE_6:
		case  UYG_UN_EE_Y:
		case  UYG_UN_EE_B:
		case  UYG_UN_EE_O:
		case  UYG_UN_EE_A:
			ret=L'e';
			break;
		case  UYG_UN_I_6:
		case  UYG_UN_I_Y:
		case  UYG_UN_I_B:
		case  UYG_UN_I_O:
		case  UYG_UN_I_A:
			ret=0x0131;/*ı*/
			break;
		case  UYG_UN_Y_6:
		case  UYG_UN_Y_Y:
		case  UYG_UN_Y_B:
		case  UYG_UN_Y_O:
		case  UYG_UN_Y_A:
			ret=L'y';
			break;
		case  UYG_UN_HM_6:
		case  UYG_UN_HM_Y:
		case  UYG_UN_HM_O:
			ret=UYG_UN_HM_6;
			break;
		case  UYG_UN_SOAL:
			ret=UYG_UKY_SOAL;
			break;
		case  UYG_UN_PESH:
			ret=UYG_UKY_PESH;
			break;
		case  UYG_UN_PIRSENT:
			ret=UYG_UKY_PIRSENT;
			break;
		case  UYG_UN_CHEKITPESH:
            ret=UYG_UKY_CHEKITPESH;
			break;
		case  UYG_UN_YULTUZ:
            ret=UYG_UKY_YULTUZ;
			break;
		default:
			break;
	}
	return ret;
}

wchar_t gUGetUyghurSoftChar(wchar_t Herp)
{
	wchar_t	ret=Herp;
	switch(Herp)
	{
		case  0x0629:
			ret=UYG_UN_E_6 ;
			break;
		case  0x0635:
			ret=UYG_UN_P_6;
			break;
		case  0x062d:
			ret=UYG_UN_CH_6;
			break;
		case  0x0622:
			ret=UYG_UN_ZZ_6;
			break;
		case  0x0636:
			ret=UYG_UN_G_6 ;
			break;
		case  0x062B:
			ret=UYG_UN_NG_6 ;
			break;
		case  0x0647:
			ret=UYG_UN_H_6 ;
			break;
		case  0x0630:
			ret=UYG_UN_U_6 ;
			break;
		case  0x0623:
			ret=UYG_UN_OO_6;
			break;
		case  0x0649:
			ret=UYG_UN_UU_6;
			break;
		case  0x0624:
			ret=UYG_UN_W_6;
			break;
		case  0x0626:
			ret=UYG_UN_EE_6;
			break;
		case 0x06CC:
		case  0x0639:
			ret=UYG_UN_I_6 ;
			break;
		case  0x0638:
			ret=UYG_UN_HM_6;
			break;
		default:
			break;
	}
	return ret;
}


wchar_t gUGetDuldulChar(wchar_t Herp)
{
	wchar_t		ret=Herp;
	switch(Herp)
	{
		case  0x0629:
			ret=UYG_UN_E_6 ;
			break;
		case  0x062B:
			ret=UYG_UN_NG_6 ;
			break;
		case  0x0647:
			ret=UYG_UN_H_6 ;
			break;
		case  0x0630:
			ret=UYG_UN_U_6 ;
			break;
		case  0x0623:
			ret=UYG_UN_OO_6;
			break;
		case  0x0625:
			ret=UYG_UN_UU_6;
			break;
		case  0x0624:
			ret=UYG_UN_W_6;
			break;
		case  0x0635:
			ret=UYG_UN_EE_6;
			break;
		case  0x0626:
			ret=UYG_UN_I_6;
			break;
		case  0x0638:
			ret=UYG_UN_HM_6;
			break;
		default:
			break;
	}
	return ret;
}


// Clipboard din herip tizmisini elip bash adresini qayturdu
wchar_t *gGetFromClipboard(void)
{
	HGLOBAL ClipBuf;
	wchar_t *esliBuf=NULL;
	if(IsClipboardFormatAvailable(CF_UNICODETEXT))
	{
		if(::OpenClipboard(NULL))
		{
			ClipBuf = GetClipboardData(CF_UNICODETEXT);
			if(ClipBuf!=NULL)
			{
				esliBuf=(wchar_t*) GlobalLock(ClipBuf);
			}
			CloseClipboard();
		}
	}
	else if(IsClipboardFormatAvailable(CF_TEXT))
	{
		if(OpenClipboard(NULL))
		{
			ClipBuf = GetClipboardData(CF_TEXT);
			if(ClipBuf!=NULL)
			{
				esliBuf=gUGetUnicodeBuf(CP_ACP,(char*)GlobalLock(ClipBuf));
			}
			CloseClipboard();
		}
	}

	if(esliBuf==NULL) return NULL;

    wchar_t *ClipData=new wchar_t[wcslen(esliBuf)+1];
    if(ClipData==NULL) return NULL;

	// Towendikisi Barliq 0d0a ni 0a gh ayalanduridu
	long rPos=0,wPos=0;
	wchar_t Herp;
	while(esliBuf[rPos]!=0x0)
	{
		Herp=esliBuf[rPos++];
		if(Herp==QURBELGISI_R)
		{
			if(esliBuf[rPos]==QURBELGISI_L)
			{
				rPos++;
			}
			Herp=QURBELGISI_R;
		}
		else if(Herp==QURBELGISI_L){
			Herp=QURBELGISI_R;
		}

		ClipData[wPos++]=Herp;
	}
	ClipData[wPos]=0x0;
	return ClipData;
}

BOOL gIsClipBoradEmpty(void)
{
	BOOL ret=TRUE;
	HGLOBAL ClipBuf;
	if(IsClipboardFormatAvailable(CF_UNICODETEXT))
	{
		if(OpenClipboard(NULL))
		{
			ClipBuf = GetClipboardData(CF_UNICODETEXT);
			if(ClipBuf!=NULL)
			{
				ret=FALSE;
			}
			CloseClipboard();
		}
	}
	else if(IsClipboardFormatAvailable(CF_TEXT))
	{
		if(OpenClipboard(NULL))
		{
			ClipBuf = GetClipboardData(CF_TEXT);
			if(ClipBuf!=NULL)
			{
				ret=FALSE;
			}
			CloseClipboard();
		}
	}
	return ret;
}

void gSetToClipboard(wchar_t* selText)
{
	HGLOBAL ClipBuf;

	int crLen=0;
	int rPos=0;
	int wPos=0;
	while(selText[rPos]!=0x0)
	{
		if(selText[rPos++]==QURBELGISI_R)crLen++;
	}

	ClipBuf = GlobalAlloc(GMEM_DDESHARE | GMEM_MOVEABLE,(wcslen(selText)+crLen+1)*sizeof(wchar_t));
	wchar_t *buffer = (wchar_t*)GlobalLock(ClipBuf);
    *buffer=0x0;
	rPos=0;
	while(selText[rPos]!=0x0)
	{
		buffer[wPos++]=selText[rPos];
		if(selText[rPos]==QURBELGISI_R)
		{
				buffer[wPos++]=QURBELGISI_L;
		}
		rPos++;
	}
	buffer[wPos]=0x0;

	if(OpenClipboard(NULL))
	{
		EmptyClipboard();
		SetClipboardData(CF_UNICODETEXT,ClipBuf);
		CloseClipboard();
	}
	GlobalUnlock(ClipBuf);
	GlobalFree(ClipBuf);
}

int gUSeleshturghuch_Org(const void *Soz1,const void *Soz2)
{
	const wchar_t *a=*(wchar_t**)Soz1;
	const wchar_t *b=*(wchar_t**)Soz2;
	int ret=0;
	int lenA=wcslen(a);
	int lenB=wcslen(b);
	int posA=0,posB=0;
	int indexA=0,indexB=0;
	ret=0;
	bool hemze=false;

	while((posA<=lenA) && (posB<=lenB))
	{
		indexA=gUGetUnicodeIndex(a[posA]);
		indexB=gUGetUnicodeIndex(b[posB]);
		if(indexA==UYGIN_HM){posA++;hemze=true;continue;}
		if(indexB==UYGIN_HM){posB++;hemze=true;continue;}
		if(indexA>=0 && indexB>=0)
		{
			ret=indexA-indexB;
		}
		else{
			ret=(int)(a[posA]-b[posB]);
		}
		if(ret!=0)
		{
			break;
		}
		posA++;
		posB++;
	}

	if(ret==0)
	{
       if(hemze==true){
            ret=lenA-lenB;
       }
	}
	return ret;
}


int gUSeleshturghuch_NEWORG(const void *Soz1,const void *Soz2)
{
	const wchar_t *a=*(wchar_t**)Soz1;
	const wchar_t *b=*(wchar_t**)Soz2;
	int ret=0;
	int lenA=wcslen(a);
	int lenB=wcslen(b);
	int posA=0,posB=0;
	int indexA=0,indexB=0;
	int index;
    bool siziqche=false;
	while((posA<=lenA) && (posB<=lenB))
	{
	    if(a[posA]==UYG_UKY_SIZIQCHE||a[posA]==UYG_UKY_BOSH)
	    {
	        posA++;
	        siziqche=true;
	        continue;
	    }

	    if(b[posB]==UYG_UKY_SIZIQCHE||b[posB]==UYG_UKY_BOSH)
	    {
	        posB++;
	        siziqche=true;
	        continue;
	    }

		indexA=2*gUGetUnicodeIndex(a[posA]);
		indexB=2*gUGetUnicodeIndex(b[posB]);
		if(indexA==2*UYGIN_HM)
		{
		    if((posA+1)<=lenA){
                index=2*gUGetUnicodeIndex(a[posA+1]);
                if(index>0)
                {
                    posA++;
                    indexA=index-1;
                }
		    }
        }
		if(indexB==2*UYGIN_HM)
		{
		    if((posB+1)<=lenB){
                index=2*gUGetUnicodeIndex(b[posB+1]);
                if(index>0)
                {
                    posB++;
                    indexB=index-1;
                }
		    }
        }
		if(indexA>=0 && indexB>=0)
		{
		 	ret=indexA-indexB;
		}
		else{
			ret=(int)(a[posA]-b[posB]);
		}
		if(ret!=0)
		{
			break;
		}
		posA++;
		posB++;
	}
	if(ret==0 && siziqche==true)
	{
	    posA=0;
	    posB=0;
        while((posA<=lenA) && (posB<=lenB))
        {
            indexA=2*gUGetUnicodeIndex(a[posA]);
            indexB=2*gUGetUnicodeIndex(b[posB]);
            if(indexA==2*UYGIN_HM)
            {
                if((posA+1)<=lenA){
                    index=2*gUGetUnicodeIndex(a[posA+1]);
                    if(index>=0)
                    {
                        posA++;
                        indexA=index-1;
                    }
                }
            }
            if(indexB==2*UYGIN_HM)
            {
                if((posB+1)<=lenB){
                    index=2*gUGetUnicodeIndex(b[posB+1]);
                    if(index>=0)
                    {
                        posB++;
                        indexB=index-1;
                    }
                }
            }
            if(indexA>=0 && indexB>=0)
            {
                ret=indexA-indexB;
            }
            else{
                ret=(int)(a[posA]-b[posB]);
            }
            if(ret!=0)
            {
                break;
            }
            posA++;
            posB++;
        }
	}
	return ret;
}


int gUSeleshturghuch(const void *Soz1,const void *Soz2)
{
	const wchar_t *a=*(wchar_t**)Soz1;
	const wchar_t *b=*(wchar_t**)Soz2;
	int ret=0;
	int lenA=wcslen(a);
	int lenB=wcslen(b);
	int posA=0,posB=0;
	int indexA=0,indexB=0;
	int index;
    bool siziqche=false;
	while((posA<=lenA) && (posB<=lenB))
	{
	    if(a[posA]==UYG_UKY_SIZIQCHE||a[posA]==UYG_UKY_BOSH)
	    {
	        posA++;
	        siziqche=true;
	        continue;
	    }

	    if(b[posB]==UYG_UKY_SIZIQCHE||b[posB]==UYG_UKY_BOSH)
	    {
	        posB++;
	        siziqche=true;
	        continue;
	    }

		indexA=2*gUGetUnicodeIndex(a[posA]);
		indexB=2*gUGetUnicodeIndex(b[posB]);
		if(indexA==2*UYGIN_HM)
		{
            indexA=67;
		    if((posA+1)<=lenA){
               index=gUGetUnicodeIndex(a[posA+1]);
               if(index==UYGIN_A || index==UYGIN_E|| index==UYGIN_EE || index==UYGIN_I|| index==UYGIN_O|| index==UYGIN_OO|| index==UYGIN_U|| index==UYGIN_UU)
               {
                    posA++;
                    indexA=index*2-1;
               }
		    }
        }
		if(indexB==2*UYGIN_HM)
		{
            indexB=67;
		    if((posB+1)<=lenB){
               index=gUGetUnicodeIndex(b[posB+1]);
               if(index==UYGIN_A || index==UYGIN_E|| index==UYGIN_EE || index==UYGIN_I|| index==UYGIN_O|| index==UYGIN_OO|| index==UYGIN_U|| index==UYGIN_UU)
               {
                    posB++;
                    indexB=index*2-1;
               }
		    }
        }

		if(indexA>=0 && indexB>=0)
		{
		 	ret=indexA-indexB;
		}
		else{
			ret=(int)(a[posA]-b[posB]);
		}
		if(ret!=0)
		{
			break;
		}
		posA++;
		posB++;
	}

	if(ret==0 && siziqche==true)
	{
	    posA=0;
	    posB=0;
        while((posA<=lenA) && (posB<=lenB))
        {
            indexA=2*gUGetUnicodeIndex(a[posA]);
            indexB=2*gUGetUnicodeIndex(b[posB]);
            if(indexA==2*UYGIN_HM)
            {
                indexA=65;
                if((posA+1)<=lenA){
                    index=gUGetUnicodeIndex(a[posA+1]);
                    if(index==UYGIN_A || index==UYGIN_E|| index==UYGIN_EE || index==UYGIN_I|| index==UYGIN_O|| index==UYGIN_OO|| index==UYGIN_U|| index==UYGIN_UU)
                    {
                        posA++;
                        indexA=index*2-1;
                    }
                }
            }
            if(indexB==2*UYGIN_HM)
            {
                indexB=65;
                if((posB+1)<=lenB){
                    index=gUGetUnicodeIndex(b[posB+1]);
                    if(index==UYGIN_A || index==UYGIN_E|| index==UYGIN_EE || index==UYGIN_I|| index==UYGIN_O|| index==UYGIN_OO|| index==UYGIN_U|| index==UYGIN_UU)
                    {
                        posB++;
                        indexB=index*2-1;
                    }
                }
            }

            if(indexA>=0 && indexB>=0)
            {
                ret=indexA-indexB;
            }
            else{
                ret=(int)(a[posA]-b[posB]);
            }
            if(ret!=0)
            {
                break;
            }
            posA++;
            posB++;
        }
	}
	return ret;
}


void gUSave(wchar_t *FileName,wchar_t **Array,int Cnt)
{
	FILE *netfp=_wfopen(FileName,L"wb");
	if(netfp==NULL) return;
	putwc(0xFEFF,netfp);
	int i=0;
	for(i=0;i<Cnt;i++)
	{
		fputws(Array[i],netfp);
		fputws(L"\n",netfp);
	}
	fclose(netfp);
}

void gUSort(wchar_t *Buffer,wchar_t del,bool delSame)
{
	wchar_t Ayr[2];
	Ayr[0]=del;
	Ayr[1]=0x0;

	int SozSani=0;
	int i=0;
	int index=0;
	int bufLen=wcslen(Buffer);
	while(Buffer[i]!=0x0)
	{
		if(Buffer[i]==del)SozSani++;
		i++;
	}
	if(Buffer[i-1]!=del)SozSani++;

	if(SozSani<=1) return;

	wchar_t **Sozler=new wchar_t*[SozSani+1];
	if(Sozler==NULL) return ;

	index=0;
	Sozler[index]=Buffer;

	index++;
	i=0;
	while(Buffer[i]!=0x0)
	{
		if(Buffer[i]==del)
		{
		   Buffer[i]=0x0;
	   	   Sozler[index]=&Buffer[i+1];
	   	   index++;
		}
		i++;
    }

	qsort(Sozler,SozSani,sizeof(wchar_t*),gUSeleshturghuch);

    //Oxshashlirini chiqirwetidu
	if(delSame)
	{
        wchar_t *Soz=Sozler[0];
        for(int i=1;i<SozSani;i++)
        {
            if(wcscmp(Soz,Sozler[i])==0)
            {
                Sozler[i]=NULL;
            }
            else{
                Soz=Sozler[i];
            }
        }
	}
	wchar_t *newBuf=new wchar_t[bufLen+1];

	if(newBuf==NULL)
	{
		return;
	}

	newBuf[0]=0x0;
	bufLen=0;
	for(i=0;i<SozSani;i++)
	{
		if(Sozler[i]!=NULL)
		{
			wcscat(&newBuf[bufLen],Sozler[i]);
			wcscat(&newBuf[bufLen],Ayr);
			bufLen+=wcslen(Sozler[i])+1;
		}
	}
	Buffer[0]=0x0;
	wcscpy(Buffer,newBuf);
	delete[] Sozler;
	delete[] newBuf;
}



int gUSetWindowCenter(HWND hWnd,int width,int height)
{
    HWND hParentWnd;
    RECT Parentrc;
    RECT New;
    hParentWnd =GetParent(hWnd);
    GetWindowRect(hParentWnd, (LPRECT)&Parentrc);
    New.left = Parentrc.left +(Parentrc.right-Parentrc.left - width)/2;
    New.top = Parentrc.top+(Parentrc.bottom -Parentrc.top- height)/2;
	New.bottom =height;
	New.right =width;
	MoveWindow(hWnd, New.left ,New.top ,New.right,New.bottom ,TRUE);
    return 0;
}

int gUSetWindowCenter(HWND hWnd)
{
    HWND hParentWnd;
    RECT Parentrc;
    RECT New,rc;

    int width,height;
	GetWindowRect(hWnd,&rc);
	width=rc.right-rc.left;
	height=rc.bottom-rc.top;
    hParentWnd =GetParent(hWnd);
    GetWindowRect(hParentWnd, (LPRECT)&Parentrc);
    New.left = Parentrc.left +(Parentrc.right-Parentrc.left - width)/2;
    New.top = Parentrc.top+(Parentrc.bottom -Parentrc.top- height)/2;
	New.bottom =height;
	New.right =width;
	MoveWindow(hWnd, New.left ,New.top ,New.right,New.bottom ,TRUE);
    return 0;
}

wchar_t* gUGetVal(wchar_t *Key)
{
	wchar_t *ret=0x0;
	int i;
	bool find=false;
	for(i=0;i<_resCnt;i++)
	{
		if(wcscmp(Key,_resKey[i])==0){
			ret=_resVal[i];
			find=true;
			break;
		}
	}
	if(!find)
	{
		ret=Key;
	}

	return ret;
}



wchar_t gGB2312_toUnicode(unsigned short gbChar)
{
	wchar_t uBuf[2];
	char    gBuf[3];
	if(gbChar<0x100)
	{
		uBuf[0]=(wchar_t)gbChar;
	}
	else
	{
		gBuf[0]=(char)(gbChar>>8);
		gBuf[1]=(char)(gbChar);
		gBuf[2]=0x0;
		MultiByteToWideChar(CP_936,0,gBuf,2,uBuf,1);
	}
	return uBuf[0];
}
/*
wchar_t gUGetWeiFangWinChar(wchar_t inWei)
{
	wchar_t ret;
	switch(inWei)
	{
		case 0xb0a1:
			ret=0x0021;
			break;
		case 0xb0a2:
			ret=0x0022;
			break;
		case 0xb0a3:
			ret=0x0023;
			break;
		case 0xb0a4:
			ret=0x00A5;
			break;
		case 0xb0a5:  // Pirsent Belgisi
			ret=0x066A;
			break;
		case 0xb0a6:
			ret=0x00A7;
			break;
		case 0xb0a7:
			ret=0x00B4;
			break;
		case 0xb0a8:
			ret=0x0028;
			break;
		case 0xb0a9:
			ret=0x0029;
			break;
		case 0xb0aa:
			ret=0x002A;
			break;
		case 0xb0ab:
			ret=0x002B;
			break;
		case 0xb0ac:    //Pesh
			ret=0x060C;
			break;
		case 0xb0ad:    // elish belgisi
			ret=0x2010;
			break;
		case 0xb0ae:
			ret=0x002E;
			break;
		case 0xb0af:
			ret=0x061F;  //Soal Belgisi
			break;
		case 0xb0b0:
			ret=0x0030;
			break;
		case 0xb0b1:
			ret=0x0031;
			break;
		case 0xb0b2:
			ret=0x0032;
			break;
		case 0xb0b3:
			ret=0x0033;
			break;
		case 0xb0b4:
			ret=0x0034;
			break;
		case 0xb0b5:
			ret=0x0035;
			break;
		case 0xb0b6:
			ret=0x0036;
			break;
		case 0xb0b7:
			ret=0x0037;
			break;
		case 0xb0b8:
			ret=0x0038;
			break;
		case 0xb0b9:
			ret=0x0039;
			break;
		case 0xb0ba:
			ret=0x003A;
			break;
		case 0xb0bb:
			ret=0x061B;    //CHekitlik Pesh
			break;
		case 0xb0bc:       //Hemze
		case 0xb0fc:
		case 0xb1a8:
			ret=0x0626;
			break;
		case 0xb0bd:
			ret=0x003D;
			break;
		case 0xb0be:  //LA
			ret=0xFEFC;
			break;
		case 0xb0fe:  //LA
			ret=0xFEFB;
			break;
		case 0xb0bf:       //A
		case 0xb1df:
		case 0xc0a1:
		case 0xc0a2:
			ret=0x0627;
			break;
		case 0xb0c0:      // E
		case 0xb1e0:
		case 0xc0a3:
		case 0xc0a4:
			ret=0x06D5;
			break;
		case 0xb0c1:      //B
		case 0xb1a1:
		case 0xb1c1:
		case 0xb1e1:
			ret=0x0628;
			break;
		case 0xb0c2:      //P
		case 0xb1a2:
		case 0xb1c2:
		case 0xb1e2:
			ret=0x067E;
			break;
		case 0xb0c3: //T
		case 0xb1a3:
		case 0xb1c3:
		case 0xb1e3:
			ret=0x062A;
			break;
		case 0xb0c4:      //J
		case 0xb1a4:
		case 0xb1c4:
		case 0xb1e4:
			ret=0x062C;
			break;
		case 0xb0c5:      //CH
		case 0xb1a5:
		case 0xb1c5:
		case 0xb1e5:
			ret=0x0686;
			break;
		case 0xb0c6:     //X
		case 0xb1a6:
		case 0xb1c6:
		case 0xb1e6:
			ret=0x062E;
			break;
		case 0xb0c7:     //D
		case 0xb1e7:
			ret=0x062F;
			break;
		case 0xb0c8:     //R
		case 0xb1e8:
			ret=0x0631;
			break;
//		case 0xb0c9:     //e??
//            ret=0x06c0;
//			break;

		case 0xb0c9:
		case 0xb1e9:
			ret=0x0632;
			break;
			case 0xb0ca:     //ZZ
		case 0xb1ea:
			ret=0x0698;
			break;
		case 0xb0cb:     //S
		case 0xb1ab:
		case 0xb1cb:
		case 0xb1eb:
			ret=0x0633;
			break;
		case 0xb0cc:     //SH
		case 0xb1ac:
		case 0xb1cc:
		case 0xb1ec:
			ret=0x0634;
			break;
		case 0xb0cd:     //GH
		case 0xb1ad:
		case 0xb1cd:
		case 0xb1ed:
			ret=0x063A;
			break;
		case 0xb0ce:     //F
		case 0xb1ae:
		case 0xb1ce:
		case 0xb1ee:
			ret=0x0641;
			break;
		case 0xb0cf:     // Q
		case 0xb1af:
		case 0xb1cf:
		case 0xb1ef:
			ret=0x0642;
			break;
		case 0xb0d0:     //K
		case 0xb1b0:
		case 0xb1d0:
		case 0xb1f0:
			ret=0x0643;
			break;
		case 0xb0d1:     //G
		case 0xb1b1:
		case 0xb1d1:
		case 0xb1f1:
			ret=0x06AF;
			break;
		case 0xb0d2:     //NG
		case 0xb1b2:
		case 0xb1d2:
		case 0xb1f2:
			ret=0x06AD;
			break;
		case 0xb0d3:     //L
		case 0xb1b3:
		case 0xb1d3:
		case 0xb1f3:
			ret=0x0644;
			break;
		case 0xb0d4:     //M
		case 0xb1b4:
		case 0xb1d4:
		case 0xb1f4:
			ret=0x0645;
			break;
		case 0xb0d5:     //N
		case 0xb1b5:
		case 0xb1d5:
		case 0xb1f5:
			ret=0x0646;
			break;
		case 0xb0d6:     //H
		case 0xb1b6:
		case 0xb1d6:
		case 0xb1f6:
			ret=0x06BE;
			break;
		case 0xb0d7:     //O
		case 0xc0a5:
		case 0xc0a6:
			ret=0x0648;
			break;
		case 0xb0d8:      //U
		case 0xb1f8:
		case 0xc0a7:
		case 0xc0a8:
			ret=0x06C7;
			break;
		case 0xb0d9:     //OO
		case 0xb1f9:
		case 0xc0a9:
		case 0xc0aa:
			ret=0x06C6;
			break;
		case 0xb0da:     //UU
		case 0xb1fa:
		case 0xc0ab:
		case 0xc0ac:
			ret=0x06C8;
			break;
		case 0xb0db:      //W
		case 0xb1fb:
			ret=0x06CB;
			break;
		case 0xb0dc:      //EE
		case 0xb1bc:
		case 0xb1dc:
		case 0xb1fc:
		case 0xc0ad:
		case 0xc0ae:
		case 0xc0b0:
			ret=0x06D0;
			break;
		case 0xb0dd:     //I
		case 0xb1bd:
		case 0xb1dd:
		case 0xb1fd:
		case 0xc0b1:
		case 0xc0b2:
		case 0xc0b4:
			ret=0x0649;
			break;
		case 0xb0de:     //Y
		case 0xb1be:
		case 0xb1de:
		case 0xb1fe:
			ret=0x064A;
			break;
		case 0xb0df:     //qazaq
			ret=0x0675;
			break;
		case 0xb0e0:     //qazaq
			ret=0x0639;
			break;
		case 0xb0e1:     //qazaq
			ret=0xFECB;
			break;
		case 0xb0e2:  //qazaq
			ret=0xFECC;
			break;
		case 0xb0e3:   //qazaq
			ret=0xFECA;
			break;
		case 0xb0e4:  // qazaq
			ret=0x0676;
			break;
		case 0xb0e5:  // qazaq
			ret=0x0677;
			break;
		case 0xb0e6:  //qazaq
			ret=0x06C5;
			break;
		case 0xb0e7: //qazaq
			ret=0xFBE1;
			break;
		case 0xb0e8:  //qazaq
			ret=0x06C9;
			break;
		case 0xb0e9:  //qazaq
			ret=0xFBE3;
			break;
		case 0xb0ea:  // Siziq Herplerni sozush uchun qisturush belgisi
			ret=0x0640;
			break;
		case 0xb0eb:
			ret=0x2212;
			break;
		case 0xb0ec: //qazaq
			ret=0x062D;
			break;
		case 0xb0ed: //qazaq
			ret=0xFEA3;
			break;
		case 0xb0ee: //qazaq
			ret=0xFEA4;
			break;
		case 0xb0ef:  //qazaq
			ret=0xFEA2;
			break;
		case 0xb0f0:
			ret=0x005F;
			break;
		case 0xb0f1:
			ret=0x2026;
			break;
		case 0xb0f2:
			ret=0x003C;
			break;
		case 0xb0f3:
			ret=0x003E;
			break;
		case 0xb0f4:
			ret=0x201D;
			break;
		case 0xb0f5:
			ret=0x201C;
			break;
		case 0xb0f6:
			ret=0x2018;
			break;
		case 0xb0f7:
			ret=0x2019;
			break;
		case 0xb0f8:  //Qosh tirnaq>>
			ret=0x00BB;
			break;
		case 0xb0f9:  //Qosh tirnaq<<
			ret=0x00AB;
			break;
		case 0xb0fa:
			ret=0x227C;
			break;
		case 0xb0fb:
			ret=0x227D;
			break;
		case 0xb0fd:
			ret=0x00B1;
			break;
		case 0xb1a7:
			ret=0x0060;
			break;
		case 0xb1aa:
			ret=0x00F7;
			break;
		case 0xb1b7:
			ret=0x002D;
			break;
		case 0xb1b8:
			ret=0x00D7;
			break;
		case 0xb1ba:
			ret=0x005D;
			break;
		case 0xb1bb:
			ret=0x005B;
			break;
		case 0xb1c7:
			ret=0x007D;
			break;
		case 0xb1c8:
			ret=0x007B;
			break;
		case 0xb1c9:
			ret=0x002F;
			break;
		case 0xb1ca:
			ret=0x005C;
			break;
		case 0xb1d7:
			ret=0x2225;
			break;
		case 0xb1d8:
			ret=0x2016;
			break;
		case 0xb1d9:
			ret=0x007E;
			break;
		case 0xc0b5:
			ret=0x2236;
			break;
		case 0xc0b6:
			ret=0x0026;
			break;
		case 0xc0b7:
			ret=0x2116;
			break;
		case 0xc0b8:
			ret=0x2160;
			break;
		case 0xc0b9:
			ret=0x2164;
			break;
		case 0xc0ba:
			ret=0x2169;
			break;
		case 0xc0bb:
			ret=0x227A;
			break;
		case 0xc0bc:
			ret=0x227B;
			break;
		case 0xb1a9:
			ret=0x0621;
			break;
		case 0xb1c0:   //qazaq
			ret=0x0678;
			break;
		case 0xb1f7:    // Bu Yer Azraq gumanliq
			ret=0xFEEE;
			break;
//		case 0xc0af:    // Bu Unicode yoq
//			ret=0xFBD1;
//			break;
//		case 0xc0b3:    // Bu unicode yoq
//			ret=0xFBD2;
//			break;
		default:
			ret=gGB2312_toUnicode(inWei);
			break;
	}
	return ret;
}
*/

wchar_t gUGetBoghFangWei(wchar_t inWei)
{
    wchar_t ret;
    switch (inWei) {
      case 0xf9a1:
      case 0xb0bf:
      case 0xfaa1:
      case 0xb1df:
        ret = 0x0627; //A
        break;
      case 0xf9a2:
      case 0xb0c0:
      case 0xfaa2:
      case 0xb1e0:
        ret = 0x06d5; //AA
        break;
      case 0xf9af:
      case 0xb1a1:
      case 0xfaaf:
      case 0xb1c1:
      case 0xfab0:
      case 0xb1e1:
      case 0xf9b0:
      case 0xb0c1:
        ret = 0x0628; //B  bash
        break;
      case 0xf9b1:
      case 0xb1a2:
      case 0xfab1:
      case 0xb1c2:
      case 0xfab2:
      case 0xb1e2:
      case 0xf9b2:
      case 0xb0c2:
        ret = 0x067e; //P
        break;
      case 0xf9b3:
      case 0xb1a3:
      case 0xfab3:
      case 0xb1c3:
      case 0xfab4:
      case 0xb1e3:
      case 0xf9b4:
      case 0xb0c3:
        ret = 0x062a; //T
        break;
      case 0xf9b5:
      case 0xb1a4:
      case 0xfab5:
      case 0xb1c4:
      case 0xfab6:
      case 0xb1e4:
      case 0xf9b6:
      case 0xb0c4:
        ret = 0x062c; //J
        break;
      case 0xf9b7:
      case 0xb1a5:
      case 0xfab7:
      case 0xb1c5:
      case 0xfab8:
      case 0xb1e5:
      case 0xf9b8:
      case 0xb0c5:
        ret = 0x0686; //Q
        break;
      case 0xf9b9:
      case 0xb1a6:
      case 0xfab9:
      case 0xb1c6:
      case 0xfaba:
      case 0xb1e6:
      case 0xf9ba:
      case 0xb0c6:
        ret = 0x062e; //H
        break;
      case 0xf9e7:
      case 0xb0c7:
      case 0xfae7:
      case 0xb1e7:
        ret = 0x062f; //D
        break;
      case 0xf9e8:
      case 0xb0c8:
      case 0xfae8:
      case 0xb1e8:
        ret = 0x0631; //R
        break;
      case 0xf9e9:
      case 0xb0c9:
      case 0xfae9:
      case 0xb1e9:
        ret = 0x0632; //Z
        break;
      case 0xf9ea:
      case 0xb0ca:
      case 0xfaea:
      case 0xb1ea:
        ret = 0x0698; //ZZ
        break;
      case 0xf9bb:
      case 0xb1ab:
      case 0xfabb:
      case 0xb1cb:
      case 0xfabc:
      case 0xb1eb:
      case 0xf9bc:
      case 0xb0cb:
        ret = 0x0633; //S
        break;
      case 0xf9bd:
      case 0xb1ac:
      case 0xfabd:
      case 0xb1cc:
      case 0xfabe:
      case 0xb1ec:
      case 0xf9be:
      case 0xb0cc:
        ret = 0x0634; //X
        break;
      case 0xf9bf:
      case 0xb1ad:
      case 0xfabf:
      case 0xb1cd:
      case 0xfac0:
      case 0xb1ed:
      case 0xf9c0:
      case 0xb0cd:
        ret = 0x063a; //GH
        break;
      case 0xf9c1:
      case 0xb1ae:
      case 0xfac1:
      case 0xb1ce:
      case 0xfac2:
      case 0xb1ee:
      case 0xf9c2:
      case 0xb0ce:
        ret = 0x0641; //F
        break;
      case 0xf9c3:
      case 0xb1af:
      case 0xfac3:
      case 0xb1cf:
      case 0xfac4:
      case 0xb1ef:
      case 0xf9c4:
      case 0xb0cf:
        ret = 0x0642; //KK
        break;
      case 0xf9c5:
      case 0xb1b0:
      case 0xfac5:
      case 0xb1d0:
      case 0xfac6:
      case 0xb1f0:
      case 0xf9c6:
      case 0xb0d0:
        ret = 0x0643; //K
        break;
      case 0xf9c7:
      case 0xb1b1:
      case 0xfac7:
      case 0xb1d1:
      case 0xfac8:
      case 0xb1f1:
      case 0xf9c8:
      case 0xb0d1:
        ret = 0x06af; //G
        break;
      case 0xf9c9:
      case 0xb1b2:
      case 0xfac9:
      case 0xb1d2:
      case 0xfaca:
      case 0xb1f2:
      case 0xf9ca:
      case 0xb0d2:
        ret = 0x06ad; //NG
        break;
      case 0xf9cb:
      case 0xb1b3:
      case 0xfacb:
      case 0xb1d3:
      case 0xfacc:
      case 0xb1f3:
      case 0xf9cc:
      case 0xb0d3:
        ret = 0x0644; //L
        break;
      case 0xf9cd:
      case 0xb1b4:
      case 0xfacd:
      case 0xb1d4:
      case 0xface:
      case 0xb1f4:
      case 0xf9ce:
      case 0xb0d4:
        ret = 0x0645; //M
        break;
      case 0xf9cf:
      case 0xb1b5:
      case 0xfacf:
      case 0xb1d5:
      case 0xfad0:
      case 0xb1f5:
      case 0xf9d0:
      case 0xb0d5:
        ret = 0x0646; //N
        break;
      case 0xf9e1:
      case 0xb1b6:
      case 0xfae1:
      case 0xb1d6:
      case 0xfae2:
      case 0xb1f6:
      case 0xf9e2:
      case 0xb0d6:
        ret = 0x06be; //HH
        break;
      case 0xf9a3:
      case 0xb0d7:
      case 0xfaa3:
      case 0xb1f7:
        ret = 0x0648; //O
        break;
      case 0xf9a4:
      case 0xb0d8:
      case 0xfaa4:
      case 0xb1f8:
        ret = 0x06c7; //U
        break;
      case 0xf9a5:
      case 0xb0d9:
      case 0xfaa5:
      case 0xb1f9:
        ret = 0x06c6; //OO
        break;
      case 0xf9a6:
      case 0xb0da:
      case 0xfaa6:
      case 0xb1fa:
        ret = 0x06c8; //UU
        break;
      case 0xf9eb:
      case 0xb0db:
      case 0xfaeb:
      case 0xb1fb:
        ret = 0x06cb; //W
        break;
      case 0xf9ab:
      case 0xb1bc:
      case 0xfaab:
      case 0xb1dc:
      case 0xfaac:
      case 0xb1fc:
      case 0xf9ac:
      case 0xb0dc:
        ret = 0x06d0; //E
        break;
      case 0xf9ad:
      case 0xb1bd:
      case 0xfaad:
      case 0xb1dd:
      case 0xfaae:
      case 0xb1fd:
      case 0xf9ae:
      case 0xb0dd:
        ret = 0x0649; //I
        break;
      case 0xf9d1:
      case 0xb1be:
      case 0xfad1:
      case 0xb1de:
      case 0xfad2:
      case 0xb1fe:
      case 0xf9d2:
      case 0xb0de:
        ret = 0x064a; //Y
        break;
      case 0xf9df:
      case 0xf9e0:
      case 0xb0bc:
      case 0xfadf:
      case 0xb0fc:
      case 0xfae0:
        ret = 0x0626; //amza  bash
        break;
      case 0xf9ef:
      case 0xb0aa:
        ret = 0x002a; //*
        break;
      case 0xf9f0:
      case 0xb0b0:
        ret = 0x0030; //0
        break;
      case 0xf9f1:
      case 0xb0b1:
        ret = 0x0031; //1
        break;
      case 0xf9f2:
      case 0xb0b2:
        ret = 0x0032; //2
        break;
      case 0xf9f3:
      case 0xb0b3:
        ret = 0x0033; //3
        break;
      case 0xf9f4:
      case 0xb0b4:
        ret = 0x0034; //4
        break;
      case 0xf9f5:
      case 0xb0b5:
        ret = 0x0035; //5
        break;
      case 0xf9f6:
      case 0xb0b6:
        ret = 0x0036; //6
        break;
      case 0xf9f7:
      case 0xb0b7:
        ret = 0x0037; //7
        break;
      case 0xf9f8:
      case 0xb0b8:
        ret = 0x0038; //8
        break;
      case 0xf9f9:
      case 0xb0b9:
        ret = 0x0039; //9
        break;
      case 0xf9fa:
      case 0xb0ab:
        ret = 0x002b; //+
        break;
      case 0xf9fb:
      case 0xb0eb:
        ret = 0x002d; //-
        break;
      case 0xf9fc:
      case 0xb1aa:
        ret = 0x00f7; //BULUSH
        break;
      case 0xf9fd:
      case 0xb1b8:
        ret = 0x00d7; //KOPAYTIX
        break;
      case 0xf9fe:
      case 0xb0bd:
        ret = 0x003d; //=
        break;
      case 0xfaee:
      case 0xb0ea:
        ret = 0x2212; //---
        break;
      case 0xfaef:
      case 0xb0ad:
        ret = 0x002d; //-
        break;
      case 0xfaf0:
      case 0xb0ac:
        ret = 0x060c; //
        break;
      case 0xfaf1:
      case 0xb0ae:
        ret = 0x002e; //.
        break;
      case 0xfaf2:
      case 0xb0bb:
        ret = 0x061b; //;
        break;
      case 0xfaf3:
      case 0xb0ba:
        ret = 0x003a; //:
        break;
      case 0xfaf4:
      case 0xb0f0:
        ret = 0x002d; //-
        break;
      case 0xfaf5:
      case 0xb0a1:
        ret = 0x0021; //!
        break;
      case 0xfaf6:
      case 0xb0af:
        ret = 0x061f; //?
        break;
      case 0xfaf7:
      case 0xb0a9:
        ret = 0x0029; //)
        break;
      case 0xfaf8:
      case 0xb0f8:
        ret = 0x00bb; //>>
        break;
      case 0xfaf9:
      case 0xb0a8:
        ret = 0x0028; //(
        break;
      case 0xfafa:
      case 0xb0f9:
        ret = 0x00ab; //<<
        break;
      case 0xfafb:
      case 0xb0f3:
        ret = 0x003e; //>
        break;
      case 0xfafc:
      case 0xb0f4:
        ret = 0x201d; //"
        break;
      case 0xfafd:
      case 0xb0f2:
        ret = 0x003c; //<
        break;
      case 0xfafe:
      case 0xb0f5:
        ret = 0x201c;
        break;
      case 0xb1b7: // uzun siziq
        ret=0x2015;
        break;
      case 0xb0a5:  // %
        ret=0x0025;
        break;
      default:
        ret = gGB2312_toUnicode(inWei);
        break;
    }
    return ret;
}

// return 0 for neither
// return 1 for ANSI
// return 2 for UTF-8 16-bit
int gUIsUTF8_16(unsigned char *s, unsigned int len) {
  int rv=2;
  int ASCII7only=1;
  unsigned char *sx=s;
  unsigned char *endx=sx+len;
  while (sx<endx) {
    if (!*sx) {  // For detection, we'll say that NUL means not UTF8
      ASCII7only=0;
      rv=0;
      break;
    } else if (*sx < 0x80) { // 0nnnnnnn If the byte's first hex code begins with 0-7, it is an ASCII character.
      sx++;
    } else if (*sx < (0x80 + 0x40)) { // 10nnnnnn 8 through B cannot be first hex codes
      ASCII7only=0;
      rv=0;
      break;
    } else if (*sx < (0x80 + 0x40 + 0x20)) { // 110xxxvv 10nnnnnn  If it begins with C or D, it is an 11 bit character
      ASCII7only=0;
      if (sx>=endx-1)
	  {
		  break;
	  }
      if (!(*sx & 0x1F) || (sx[1]&(0x80+0x40)) != 0x80)
	  {
		  rv=0;
		  break;
	  }
      sx+=2;
    } else if (*sx < (0x80 + 0x40 + 0x20 + 0x10)) { // 1110qqqq 10xxxxvv 10nnnnnn If it begins with E, it is 16 bit
      ASCII7only=0;
      if (sx>=endx-2)
	  {
		  break;
	  }
      if (!(*sx & 0xF) || (sx[1]&(0x80+0x40)) != 0x80 || (sx[2]&(0x80+0x40)) != 0x80)
	  {
		  rv=0;
		  break;
	  }
      sx+=3;
    } else { /* more than 16 bits are not allowed here */
      ASCII7only=0;
      rv=0;
      break;
    }
  }
  rv=ASCII7only?1:rv;
  return rv;
}


int gwctoutf8(unsigned char *s, wchar_t c)
{
	if (c <0x80)
	{
		*s++ = (unsigned char)c;
		return 1;
	}
	else if (c<0x800)
	{
		*s++ = (unsigned char)(0xc0 | (c >> 6));
		*s++ = (unsigned char)(0x80 | (c & 0x3f));
		return 2;
	}
	else
	{
		*s++ = (unsigned char)(0xe0 | (c >> 12));
		*s++ = (unsigned char)(0x80 | ((c >> 6) & 0x3f));
		*s++ = (unsigned char)(0x80 | (c & 0x3f));
		return 3;
	}
/*	else if (c < (1 << 21))
	{
		*s++ = 0xf0 | (c >> 18);
		*s++ = 0x80 | ((c >> 12) & 0x3f);
		*s++ = 0x80 | ((c >> 6) & 0x3f);
		*s++ = 0x80 | (c & 0x3f);
		return 4;
	}
	else if (c < (1 << 26))
	{
		*s++ = 0xf8 | (c >> 24);
		*s++ = 0x80 | ((c >> 18) & 0x3f);
		*s++ = 0x80 | ((c >> 12) & 0x3f);
		*s++ = 0x80 | ((c >> 6) & 0x3f);
		*s++ = 0x80 | (c & 0x3f);
		return 5;
	}
	else if (c < (1 << 31))
	{
		*s++ = 0xfc | (c >> 30);
		*s++ = 0x80 | ((c >> 24) & 0x3f);
		*s++ = 0x80 | ((c >> 18) & 0x3f);
		*s++ = 0x80 | ((c >> 12) & 0x3f);
		*s++ = 0x80 | ((c >> 6) & 0x3f);
		*s++ = 0x80 | (c & 0x3f);
		return 6;
	}*/
}
/*
	UTF-8 ni Unicode qa aylanduridu
*/

int gutf8towc (unsigned char *out, wchar_t *Herp)
{
	int len=0;
	if (out[0] < 0x80)
	{
		*Herp=out[0];
		len=1;
	}
	else if (out[0] >= 0xc0 && out[0] < 0xe0)
	{
		*Herp=((out[0] & 0x1f) << 6) + (out[1] & 0x3f);
		len=2;
	}
	else if (out[0] >= 0xe0 && out[0] < 0xf0)
	{
		*Herp=((out[0] & 0x0f) << 12)+ ((out[1] & 0x3f) << 6) + (out[2] & 0x3f);
		len=3;
	}
	return len;
}

unsigned char *gUGetMBChar(unsigned char *curPos,wchar_t* Herp)
{
	unsigned char First,Next;
	wchar_t    Hrp;
	First=*curPos++;
	if(First>=bCEK)
	{
		Next=*curPos++;
	}
	else
	{
		Next=First;
		First=0x0;
	}
	Hrp=First;
	Hrp=(wchar_t)((Hrp<<8)|Next);
	*Herp=Hrp;
	return curPos;
}

int gUAutoDetectBOGHDAWEI(unsigned char *s, unsigned int len)
{
	int ret=CP_ACP;
	wchar_t Herp;

	unsigned char    *beshi=s;
	unsigned char    *curPos;

	unsigned int  bogh=0;
	unsigned int  weiwin=0;
	unsigned int  weidos=0;
	unsigned int  kereksiz=0;

	float rate=0;

	curPos=gUGetMBChar(beshi,&Herp);
	while(Herp!=0x0)
	{
		if(Herp>=sCEK)
		{
		    if((Herp>=0xf9a1 && Herp<0xfba1) || (Herp==0xf9aa || Herp==0xfaaa)){
				bogh++;
			}
		    else if((Herp>=0xb0a1 && Herp<0xb0ff) || (Herp>=0xb1a1 && Herp<0xb1ff)){
				weidos++;
			}
		    else if((Herp>=0xb021 && Herp<0xb07f) || (Herp>=0xb121 && Herp<0xb17f)){
				weiwin++;
			}
		}else if(Herp>=0x80 && Herp<=bCEK){
			kereksiz++;
		}
		curPos=gUGetMBChar(curPos,&Herp);
	}
	len=len-kereksiz;
	rate=2.0f*bogh/len;
	if(rate>=0.5){
		ret=CP_BOGHDA;
	}
	rate=2.0f*weiwin/len;
	if(rate>=0.5){
		ret=CP_WEIWIN;
	}
	rate=2.0f*weidos/len;
	if(rate>=0.5){
		ret=CP_WEIDOS;
	}
	return ret;
}

BOOL gUIsULY(wchar_t Herp)
{
        BOOL ret=FALSE;
        if((Herp>=L'A' && Herp<=L'Z')||(Herp>=L'a' && Herp<=L'z')||Herp==UYG_UKY_OO_KICHIK||Herp==UYG_UKY_OO_CHONG||
           Herp==UYG_UKY_UU_KICHIK||Herp==UYG_UKY_UU_CHONG||Herp==UYG_UKY_EE_KICHIK||Herp==UYG_UKY_EE_CHONG|| //||Herp==0x00e8|| Herp==0x00c8)
           Herp==L'ş' || Herp ==L'ñ'|| Herp ==L'ğ'||Herp ==L'ç'
           )
        {
            ret=TRUE;
        }
        return ret;
}

BOOL gUIsAlahide(wchar_t Herp)
{
        BOOL ret=FALSE;
        if(Herp>0xE000 && Herp<0xE0FF)
        {
            ret=gUIsULY(Herp-0xE000);
        }
        return ret;
}

BOOL gIsConstanToken(wchar_t *stAdd,int len)
{
	BOOL ret=FALSE;
	wchar_t *token=new wchar_t[len+1];
	wcsncpy(token,stAdd,len);
	token[len]=0x0;
	token=wcslwr(token);
	if(
		(wcsstr(token,L"http")!=NULL)||
		(wcsstr(token,L"www")!=NULL)  ||
		(wcsstr(token,L"ftp")!=NULL) ||
		(wcsstr(token,L"mailto")!=NULL) ||
		(wcsstr(token,L".com")!=NULL) ||
		(wcsstr(token,L".net")!=NULL) ||
		(wcsstr(token,L".cn")!=NULL) ||
		(wcsstr(token,L"mp3")!=NULL) ||
		(wcsstr(token,L".zip")!=NULL) ||
		(wcsstr(token,L"pdf")!=NULL) ||
		(wcsstr(token,L"txt")!=NULL) ||
		(wcsstr(token,L"php")!=NULL) ||
		(wcsstr(token,L".exe")!=NULL)||
		(wcsstr(token,L".jp")!=NULL)||
		(wcsstr(token,L"htm")!=NULL)||
		(wcsstr(token,L"@")!=NULL)||
		(wcsstr(token,L".org")!=NULL)||
		(wcsstr(token,L"skype")!=NULL)||
		(wcsstr(token,L"windows")!=NULL)||
		(wcsstr(token,L"linux")!=NULL)||
		(wcsstr(token,L"ubuntu")!=NULL)||
		(token[0]==L'&' && token[len-1]==L';')||
		(token[0]==L'%')
		)
	{
		ret=TRUE;
	}
	delete[] token;
	return ret;
}

BOOL gIsStartedWithURL(wchar_t *buf)
{
    BOOL ret=FALSE;
    if(wcsstr(buf,L"http")==buf || wcsstr(buf,L"ftp")==buf)
    {
        ret=TRUE;
    }
    return ret;
}

#ifdef _DEBUG
bool _trace(TCHAR *format, ...)
{
   TCHAR buffer[1000];

   va_list argptr;
   va_start(argptr, format);
   wvsprintf(buffer, format, argptr);
   va_end(argptr);

   OutputDebugString(buffer);

   return true;
}
#endif

