#ifndef UYGHURCODE_H
#define UYGHURCODE_H 1

#include <windows.h>
#include "ortaq.h"

#ifndef WS_EX_LAYOUTRTL
#define WS_EX_LAYOUTRTL                    0x00400000L
#endif

#ifndef GWL_USERDATA
#define GWL_USERDATA (-21)
#endif

#ifndef DWL_USER
#define DWL_USER 8
#endif

#ifdef _DEBUG
bool _trace(TCHAR *format, ...);
#endif

#define CP_BOGHDA		-1
#define CP_WEIDOS       -2
#define CP_WEIWIN       -3

#define CP_932			932
#define CP_936			936
#define CP_950			950

#define CP_JEUC			51932

#define CP_UTF16LE		1200
#define CP_UTF16BE		1201

#define CP_1250			1250
#define CP_1251			1251
#define CP_1252			1252
#define CP_1253			1253
#define CP_1254			1254
#define CP_1255			1255
#define CP_1256			1256
#define CP_1257			1257


#define	UEKRAN_X     0
#define	UEKRAN_Y     1
#define	UEKRAN_XY    2

#define RES_MAX 200
#define MAX_SOZ_LEN	50


wchar_t* gUGetVal(wchar_t *Key);
int gUGetUnicodeIndex(wchar_t Herp);
BOOL gUIsUyghur(wchar_t Herip);
BOOL gUIsSozuqTawushUNICODE(wchar_t Herip);
BOOL gUIsSozuqTawushUKY(wchar_t Herip);
int gUGetUKYIndex(wchar_t ukyHerip);
wchar_t gUGetBgdChar(wchar_t Herp);
wchar_t gUGetWeiFangWinChar(wchar_t Herp);
void gDoEvents(void);
wchar_t *gUGetUnicodeBuf(UINT codePage,char *Buf);
void gUInitUnicodeCode(void);
wchar_t gUGetHerpFromNotepad(wchar_t Herp);
wchar_t gUGetHerpFromIlikyurt(wchar_t Herp);
wchar_t gUGetUyghurSoftChar(wchar_t Herp);
wchar_t gUGetDuldulChar(wchar_t Herp);
wchar_t *gGetFromClipboard(void);
BOOL gIsClipBoradEmpty(void);
void gSetToClipboard(wchar_t* selText);
void gUSort(wchar_t *Buffer,wchar_t del);
int gUSetWindowCenter(HWND hWnd,int width,int height);
int gUSetWindowCenter(HWND hWnd);
wchar_t gGB2312_toUnicode(unsigned short gbChar);

HMODULE gLoadImlaDll();

/*
typedef void	(__stdcall *Init)(HWND prn,UINT msg,HINSTANCE parIns);
typedef BOOL	(__stdcall *IsCorrect)(wchar_t *Soz,bool checkQosh);
typedef int     (__stdcall *CheckWord)(wchar_t *Soz,bool checkQosh);
typedef BOOL	(__stdcall *LoadDictionary)();
typedef void	(__stdcall *UnLoadDictionary)();
typedef int		(__stdcall *GetCandidateWord)(wchar_t *Buf,int index);
typedef int     (__stdcall *GetOrgWord)(wchar_t *Buf);
typedef void    (__stdcall *ShowFindDialog)(HWND m_hWnd, LPVOID kk);
typedef void    (__stdcall *SetUILang)(int UILang);
*/

typedef void	(__cdecl *Init)(HWND prn,UINT msg,HINSTANCE parIns);
typedef BOOL	(__cdecl *IsCorrect)(wchar_t *Soz,bool checkQosh);
typedef int     (__cdecl *CheckWord)(wchar_t *Soz,bool checkQosh);
typedef BOOL	(__cdecl *LoadDictionary)();
typedef void	(__cdecl *UnLoadDictionary)();
typedef int		(__cdecl *GetCandidateWord)(wchar_t *Buf,int index);
typedef int     (__cdecl *GetOrgWord)(wchar_t *Buf);
typedef void    (__cdecl *ShowFindDialog)(HWND m_hWnd, LPVOID kk,UINT lang);
typedef void    (__cdecl *SetUILang)(int UILang);
typedef int     (__cdecl *GetToghrisi)(wchar_t *Eslisi,wchar_t *Toghrisi);



enum KUNUPKA{KUNUPKA_SYSTEM,KUNUPKA_UYGHUR,KUNUPKA_LATIN,KUNUPKA_ALAHIDE};
enum UINTERFACE_LANG
{
	LANG_UEY,
	LANG_ULY,
	LANG_USY,
	LANG_JPN,
	LANG_ENG,
	LANG_CHN,
    LANG_GER
};

typedef struct QelipUyghurEditFont
{
	double			mue_FontPoint;
	LONG			mue_QurArlighi;
	wchar_t			mue_UyghurFaceName[LF_FACESIZE];
	wchar_t			mue_LocalFaceName[LF_FACESIZE];
	BYTE			mue_Qiypash;
	BYTE			mue_Tom;
	COLORREF		mue_UUYG_ForeColor;
	COLORREF		mue_UBashqa_ForeColor;
	COLORREF		mue_UEkran_Color;
	COLORREF		mue_UTal_ForeColor;
	COLORREF		mue_UTal_BackColor;
	UINTERFACE_LANG mue_Lang;
	BOOL            mue_AutoQatlash;
	KUNUPKA         mue_Kunupka;
	BOOL            mue_RTL;
}UEDIT,*LPUEDIT;

#define MAX_IZ_SANI 10

typedef struct QelipIZLAR
{
	int 			m_IzSani;
	ULONG           m_IzPos[MAX_IZ_SANI+1];
	wchar_t			m_IzNami[MAX_IZ_SANI+1][MAX_PATH];
}IZLAR,*LPIZLAR;


typedef struct QelipNotify
{
	UINT      Qur;
	UINT      Ston;
	UINT      Herp;
	BOOL      Qisturush;
	KUNUPKA   Kunupka;
}UNOTIFY;

enum U_RESULT
{
	U_CORRECT=4,
	U_HAVE_CANDIDATES,
	U_SKIP,
	U_REPLACE,
	U_REPLACE_AUTO,
	U_STOP,
	U_START
};


#define QURBELGISI_R 0x000D
#define QURBELGISI_L 0x000A
#define QURBELGISI_Y 0x008D

#define sCEK			0xA1A1
#define bCEK			0xA1

#define UTF_16LE        0xFEFF

#define RES_NAME_JPN	TEXT("jpn_res.txt")
#define RES_NAME_CHN	TEXT("chn_res.txt")
#define RES_NAME_ENG	TEXT("eng_res.txt")
#define RES_NAME_UEY	TEXT("uey_res.txt")
#define RES_NAME_GER	TEXT("ger_res.txt")

#define	UVK_TABSIZE		5


enum Orni{U_6,U_YALGHUZ,U_BASH,U_OTTURA,U_AYAQ};

enum HerpIndex
{
	UYGIN_HM,
	UYGIN_A,
	UYGIN_E ,
	UYGIN_B ,
	UYGIN_P ,
	UYGIN_T ,
	UYGIN_J ,
	UYGIN_CH,
	UYGIN_X ,
	UYGIN_D ,
	UYGIN_R ,
	UYGIN_Z ,
	UYGIN_ZZ,
	UYGIN_S ,
	UYGIN_SH,
	UYGIN_GH,
	UYGIN_F ,
	UYGIN_Q ,
	UYGIN_K ,
	UYGIN_G ,
	UYGIN_NG,
	UYGIN_L ,
	UYGIN_M ,
	UYGIN_N ,
	UYGIN_H ,
	UYGIN_O ,
	UYGIN_U ,
	UYGIN_OO,
	UYGIN_UU,
	UYGIN_W ,
	UYGIN_EE,
	UYGIN_I ,
	UYGIN_Y,
	UYGIN_LA
};


struct QelipUnicode
{
	wchar_t Code[5];
	bool	Ulinish;  //Buning keynidin kelgen heripler ulinalamdu
};

struct QelipUKY
{
	wchar_t Kichik;
	wchar_t Chong;
};

enum QANDAQ
{
    SOZ_PUTUN,
    SOZ_BESHI,
    SOZ_AXIRI,
    SOZ_XALIGHAN
};

typedef struct QelipIzdesh
{
	wchar_t mi_EsliSoz[128];
	wchar_t mi_OrunbasarSoz[128];
	BOOL    mi_Yolunishi;          // True Bolsa Keynige Qarap izdeydu
	BOOL    mi_Dairsi;             // True Bolsa Hemmini Izdeydu
	QANDAQ  mi_Qandaq;           // True Bolsa Putun Sozni Izdeydu
	BOOL    mi_ChongKichik;        // True Bolsa Chong Kichikligige qaraydu
	int     mi_Action;           // 1=Izdesh,2-Almashturush,0-texi belgilenmigen
	int     mi_Cnt;
}IZDESH,*LPIZDESH;



enum Herket
{
	Herket_YOQ,
	Herket_IZDE,
	Herket_ALMASHTUR
};

enum TOKENTYPE
{
	TOK_UYGHUR,
	TOK_ENGLISH,
	TOK_ENGBELGE,
	TOK_OTHER
};


enum ALMASHTURUSH_USULI
{
	USUL_HE,
	USUL_HEMMINI,
	USUL_YAQ,
	USUL_TOHTASH
};

// Uyghurce Unicode (kona yeziq heriplerning Unicodesi)
//A
#define UYG_UN_A_6 0x0627	//Yalghuz
#define UYG_UN_A_Y 0xFE8D	//Yalghuz
#define UYG_UN_A_A 0xFE8E	//Ayaq
		// E Heripi
#define UYG_UN_E_6 0x06D5	//Yalghuz;
#define UYG_UN_E_Y 0xFEE9	//Yalghuz;
#define UYG_UN_E_A 0xFEEA	//Ayaq;
		// B
#define UYG_UN_B_6 0x0628	//Yalghuz;
#define UYG_UN_B_Y 0xFE8F	//Yalghuz;
#define UYG_UN_B_A 0xFE90	//Ayaq;
#define UYG_UN_B_B 0xFE91	//Bax;
#define UYG_UN_B_O 0xFE92	//Ottura;
		//P
#define UYG_UN_P_6 0x067E  //Yalghuz;
#define UYG_UN_P_Y 0xFB56  //Yalghuz;
#define UYG_UN_P_A 0xFB57	//Ayaq;
#define UYG_UN_P_B 0xFB58	//Bax;
#define UYG_UN_P_O 0xFB59	//Ottura;
		//T
#define UYG_UN_T_6 0x062A  //Yalghuz;
#define UYG_UN_T_Y 0xFE95  //Yalghuz;
#define UYG_UN_T_A 0xFE96	//Ayaq;
#define UYG_UN_T_B 0xFE97	//Bax;
#define UYG_UN_T_O 0xFE98	//Ottura;
		//J
#define UYG_UN_J_6 0x062C  //Yalghuz;
#define UYG_UN_J_Y 0xFE9D  //Yalghuz;
#define UYG_UN_J_A 0xFE9E	//Ayaq;
#define UYG_UN_J_B 0xFE9F	//Bax;
#define UYG_UN_J_O 0xFEA0	//Ottura;
		//Ch
#define UYG_UN_CH_6 0x0686  //Yalghuz;
#define UYG_UN_CH_Y 0xFB7A  //Yalghuz;
#define UYG_UN_CH_A 0xFB7B	//Ayaq;
#define UYG_UN_CH_B 0xFB7C	//Bax;
#define UYG_UN_CH_O 0xFB7D	//Ottura;
		//X
#define UYG_UN_X_6 0x062E  //Yalghuz;
#define UYG_UN_X_Y 0xFEA5 //Yalghuz;
#define UYG_UN_X_A 0xFEA6	//Ayaq;
#define UYG_UN_X_B 0xFEA7	//Bax;
#define UYG_UN_X_O 0xFEA8	//Ottura;
		//D
#define UYG_UN_D_6 0x062F  //Yalghuz;
#define UYG_UN_D_Y 0xFEA9  //Yalghuz;
#define UYG_UN_D_A 0xFEAA	//Ayaq;
		//R
#define UYG_UN_R_6 0x0631  //Yalghuz;
#define UYG_UN_R_Y 0xFEAD  //Yalghuz;
#define UYG_UN_R_A 0xFEAE	//Ayaq;
		//Z
#define UYG_UN_Z_6 0x0632  //Yalghuz;
#define UYG_UN_Z_Y 0xFEAF  //Yalghuz;
#define UYG_UN_Z_A 0xFEB0	//Ayaq;
		//Z..
#define UYG_UN_ZZ_6 0x0698  //Yalghuz;
#define UYG_UN_ZZ_Y 0xFB8A  //Yalghuz;
#define UYG_UN_ZZ_A 0xFB8B	//Ayaq;
		//S
#define UYG_UN_S_6 0x0633  //Yalghuz;
#define UYG_UN_S_Y 0xFEB1  //Yalghuz;
#define UYG_UN_S_A 0xFEB2	//Ayaq;
#define UYG_UN_S_B 0xFEB3	//Bax;
#define UYG_UN_S_O 0xFEB4	//Ottura;
		//SH
#define UYG_UN_SH_6 0x0634  //Yalghuz;
#define UYG_UN_SH_Y 0xFEB5  //Yalghuz;
#define UYG_UN_SH_A 0xFEB6	//Ayaq;
#define UYG_UN_SH_B 0xFEB7	//Bax;
#define UYG_UN_SH_O 0xFEB8	//Ottura;
		//GH
#define UYG_UN_GH_6 0x063A  //Yalghuz;
#define UYG_UN_GH_Y 0xFECD  //Yalghuz;
#define UYG_UN_GH_A 0xFECE	//Ayaq;
#define UYG_UN_GH_B 0xFECF	//Bax;
#define UYG_UN_GH_O 0xFED0	//Ottura;
		//F
#define UYG_UN_F_6 0x0641  //Yalghuz;
#define UYG_UN_F_Y 0xFED1  //Yalghuz;
#define UYG_UN_F_A 0xFED2	//Ayaq;
#define UYG_UN_F_B 0xFED3	//Bax;
#define UYG_UN_F_O 0xFED4	//Ottura;
		//Q
#define UYG_UN_Q_6 0x0642  //Yalghuz;
#define UYG_UN_Q_Y 0xFED5  //Yalghuz;
#define UYG_UN_Q_A 0xFED6	//Ayaq;
#define UYG_UN_Q_B 0xFED7	//Bax;
#define UYG_UN_Q_O 0xFED8	//Ottura;
		//K
#define UYG_UN_K_6 0x0643  //Yalghuz;
#define UYG_UN_K_Y 0xFED9  //Yalghuz;
#define UYG_UN_K_A 0xFEDA	//Ayaq;
#define UYG_UN_K_B 0xFEDB	//Bax;
#define UYG_UN_K_O 0xFEDC	//Ottura;
		//G
#define UYG_UN_G_6 0x06AF  //Yalghuz;
#define UYG_UN_G_Y 0xFB92  //Yalghuz;
#define UYG_UN_G_A 0xFB93	//Ayaq;
#define UYG_UN_G_B 0xFB94	//Bax;
#define UYG_UN_G_O 0xFB95	//Ottura;
		//NG
#define UYG_UN_NG_6 0x06AD  //Yalghuz;
#define UYG_UN_NG_Y 0xFBD3  //Yalghuz;
#define UYG_UN_NG_A 0xFBD4	//Ayaq;
#define UYG_UN_NG_B 0xFBD5	//Bax;
#define UYG_UN_NG_O 0xFBD6	//Ottura;
		//L
#define UYG_UN_L_6 0x0644  //Yalghuz;
#define UYG_UN_L_Y 0xFEDD  //Yalghuz;
#define UYG_UN_L_A 0xFEDE	//Ayaq;
#define UYG_UN_L_B 0xFEDF	//Bax;
#define UYG_UN_L_O 0xFEE0	//Ottura;
		//M
#define UYG_UN_M_6 0x0645  //Yalghuz;
#define UYG_UN_M_Y 0xFEE1  //Yalghuz;
#define UYG_UN_M_A 0xFEE2	//Ayaq;
#define UYG_UN_M_B 0xFEE3	//Bax;
#define UYG_UN_M_O 0xFEE4	//Ottura;
		//N
#define UYG_UN_N_6 0x0646  //Yalghuz;
#define UYG_UN_N_Y 0xFEE5  //Yalghuz;
#define UYG_UN_N_A 0xFEE6	//Ayaq;
#define UYG_UN_N_B 0xFEE7	//Bax;
#define UYG_UN_N_O 0xFEE8	//Ottura;
		//H..
#define UYG_UN_H_6 0x06BE  //Yalghuz;
#define UYG_UN_H_Y 0xFBAA  //Yalghuz;
#define UYG_UN_H_A 0xFBAB	//Ayaq;
#define UYG_UN_H_B 0xFBAC	//Bax;
#define UYG_UN_H_O 0xFBAD	//Ottura;

		//O
#define UYG_UN_O_6 0x0648  //Yalghuz;
#define UYG_UN_O_Y 0xFEED  //Yalghuz;
#define UYG_UN_O_A 0xFEEE	//Ayaq;
		//U
#define UYG_UN_U_6 0x06C7  //Yalghuz;
#define UYG_UN_U_Y 0xFBD7  //Yalghuz;
#define UYG_UN_U_A 0xFBD8	//Ayaq;
		//O..
#define UYG_UN_OO_6 0x06C6  //Yalghuz;
#define UYG_UN_OO_Y 0xFBD9  //Yalghuz;
#define UYG_UN_OO_A 0xFBDA	//Ayaq;
		//U..
#define UYG_UN_UU_6 0x06C8  //Yalghuz;
#define UYG_UN_UU_Y 0xFBDB  //Yalghuz;
#define UYG_UN_UU_A 0xFBDC	//Ayaq;
		//W
#define UYG_UN_W_6 0x06CB  //Yalghuz;
#define UYG_UN_W_Y 0xFBDE //Yalghuz;
#define UYG_UN_W_A 0xFBDF	//Ayaq;
		//E..
#define UYG_UN_EE_6 0x06D0  //Yalghuz;
#define UYG_UN_EE_Y 0xFBE4  //Yalghuz;
#define UYG_UN_EE_A 0xFBE5	//Ayaq;
#define UYG_UN_EE_B 0xFBE6	//Bax;
#define UYG_UN_EE_O 0xFBE7	//Ottura;
		//I
#define UYG_UN_I_6 0x0649  //Yalghuz;
#define UYG_UN_I_Y 0xFEEF  //Yalghuz;
#define UYG_UN_I_A 0xFEF0	//Ayaq;
#define UYG_UN_I_B 0xFBE8	//Bax;
#define UYG_UN_I_O 0xFBE9	//Ottura;
		//Y
#define UYG_UN_Y_6 0x064A  //Yalghuz;
#define UYG_UN_Y_Y 0xFEF1  //Yalghuz;
#define UYG_UN_Y_A 0xFEF2	//Ayaq;
#define UYG_UN_Y_B 0xFEF3	//Bax;
#define UYG_UN_Y_O 0xFEF4	//Ottura;

//La
#define UYG_UN_LA_6 0xFEFB  //Yalghuz;
#define UYG_UN_LA_Y 0xFEFB  //Yalghuz;
#define UYG_UN_LA_A 0xFEFC	//Ayaq;

//Amza
#define UYG_UN_HM_6 0x0626  //Yalghuz;
#define UYG_UN_HM_Y 0xFE8B  //Yalghuz;
#define UYG_UN_HM_O 0xFE8C	//Ottura;

// Towendikiler Uyghurche Heripler
// Biraq ular KeyBord Arqiliq kirguzgende ishlitilmidi

//hemze bilen A
#define UYGE_UN_HA_Y 0xFBEA  //Yalghuz;
#define UYGE_UN_HA_A 0xFBEB	//Ayaq;

//hemze bilen E
#define UYGE_UN_HE_Y 0xFBEC  //Yalghuz;
#define UYGE_UN_HE_A 0xFBED	//Ayaq;

//hemze bilen O
#define UYGE_UN_HO_Y 0xFBEE  //Yalghuz;
#define UYGE_UN_HO_A 0xFBEF	//Ayaq;

//hemze bilen U
#define UYGE_UN_HU_Y 0xFBF0  //Yalghuz;
#define UYGE_UN_HU_A 0xFBF1  //Ayaq;

//hemze bilen OO
#define UYGE_UN_HOO_Y 0xFBF2  //Yalghuz;
#define UYGE_UN_HOO_A 0xFBF3  //Ayaq;

//hemze bilen UU
#define UYGE_UN_HUU_Y 0xFBF4  //Yalghuz;
#define UYGE_UN_HUU_A 0xFBF5  //Ayaq;

//hemze bilen EE
#define UYGE_UN_HEE_Y 0xFBF6  //Yalghuz;
#define UYGE_UN_HEE_A 0xFBF7  //Ayaq;
#define UYGE_UN_HEE_B 0xFBF8  //Ayaq;

//hemze bilen I
#define UYGE_UN_HI_Y 0xFBF9  //Yalghuz;
#define UYGE_UN_HI_A 0xFBFA  //Ayaq;
#define UYGE_UN_HI_B 0xFBFB  //Ayaq;


//Bu Artuq Ishlitilgen H heripi(Hemze emes, Yulghunda H uchun muhsuni ishletken)
#define UYGE_UN_H_Y 0xFEEB   //Yalghuz;
#define UYGE_UN_H_A 0xFEEC    //Ayaq;


#define UYG_UN_BOSH      		0x0020 //Boshluq Belgisi
#define UYG_UN_UNDESH    		0x0021 //Undesh Belgisi
#define UYG_UN_QOSHPESH  		0x0022 //Qosh Pesh
#define UYG_UN_REQEM      		0x0023 //Reqem Belgisi #
#define UYG_UN_DOLLAR    		0x0024 //Dollar Belgisi
#define UYG_UN_PIRSENT   		0x0025 //Pirsent Belgisi
#define UYG_UN_WE	      		0x0026 //& belgisi
#define UYG_UN_TIKPESH		    0x0027 //yalang pesh '(yaki Tik Pesh)
#define UYG_UN_SOL_K_TIRNAQ		0x0028 //Sol Tirnaq(
#define UYG_UN_ONG_K_TIRNAQ		0x0029 //Ong tirnaq)
#define UYG_UN_YULTUZ			0x002A //Yultuz belgisi
#define UYG_UN_QOSHUSH			0x002B //Qoshush Belgisi
#define UYG_UN_PESH      		0x060C //Pesh
#define UYG_UN_SOZUSH			0x0640 //Sozlerni tengshesh belgisi
#define UYG_UN_CHEKIT			0x002E //Chekit
#define UYG_UN_0				0x0030 // Nol
#define UYG_UN_1				0x0031 // Bir
#define UYG_UN_2				0x0032 // Ikki
#define UYG_UN_3				0x0033 // Uch
#define UYG_UN_4				0x0034 // Tort
#define UYG_UN_5				0x0035 // Besh
#define UYG_UN_6				0x0036 // Alte
#define UYG_UN_7				0x0037 // Yette
#define UYG_UN_8				0x0038 // Sekkiz
#define UYG_UN_9				0x0039 // Toqquz
#define UYG_UN_QOSHCHEKIT		0x003A // Qosh Chekit
#define UYG_UN_CHEKITPESH 		0x061B // Chekitlik Pesh
#define UYG_UN_CHONG			0x203A // ChongBelgisi
#define UYG_UN_TENG				0x003D // Tenglik Belgisi
#define UYG_UN_KICHIK			0x2039 // Kichik Belgisi
#define UYG_UN_SOAL				0x061F // Soal Belgisi
#define UYG_UN_MEKTUP			0x0040 // E-mail Adres Belgisi@
#define UYG_UN_SOL_O_TIRNAQ		0x005B // Sol Ottura Tirnaq
#define UYG_UN_SOL_YANTO		0x005C // Sol Yantu siziq(ong yantu Siziq hemzige teqsimlengen)
#define UYG_UN_ONG_O_TIRNAQ		0x005D // Sol Ottura Tirnaq
#define UYG_UN_DERIJE		    0x005E // Sol Ottura Tirnaq
#define UYG_UN_SIZIQ			0x2014 // Siziq
#define UYG_UN_QIYPESH			0x0060 // Qiypash Pesh
#define UYG_UN_SOL_CH_TIRNAQ	0x007B // Chong Sol Tirnaq
#define UYG_UN_TIKSIZIQ			0x007C // Tik Siziq
#define UYG_UN_ONG_CH_TIRNAQ	0x007D // Chong Ong Tirnaq
#define UYG_UN_DOLQUN			0x007E // Dolqun belgisi~
#define UYG_UN_SOL_QOSH_TIRNAQ  0x00AB // Qosh Tirnaq<<
#define UYG_UN_ONG_QOSH_TIRNAQ  0x00BB // Qosh Tirnaq>>
#define UYG_UN_KOPCHEKIT        0x2026 // kop chekit

// UYGHUR KOMPUTER YEZIQI
//A
#define UYG_UKY_A_KICHIK 'a'	//Kichik yezilishi
#define UYG_UKY_A_CHONG  'A'	//Chong Yezilishi
		// E Heripi
#define UYG_UKY_E_KICHIK 'e'	//Kichik yezilishi;
#define UYG_UKY_E_CHONG  'E'	//Chong Yezilishi;
		// B
#define UYG_UKY_B_KICHIK 'b'	//Kichik yezilishi
#define UYG_UKY_B_CHONG  'B'	//Chong Yezilishi;
		//P
#define UYG_UKY_P_KICHIK 'p'	//Kichik yezilishi
#define UYG_UKY_P_CHONG  'P'	//Chong Yezilishi;
		//T
#define UYG_UKY_T_KICHIK 't'	//Kichik yezilishi
#define UYG_UKY_T_CHONG  'T'	//Chong Yezilishi;
		//J
#define UYG_UKY_J_KICHIK 'j'	//Kichik yezilishi
#define UYG_UKY_J_CHONG  'J'	//Chong Yezilishi;
		//Ch
//#define UYG_UKY_CH_KICHIK 'ch'	//Kichik yezilishi
//#define UYG_UKY_CH_CHONG  'CH'	//Chong Yezilishi;
		//X
#define UYG_UKY_X_KICHIK 'x'	//Kichik yezilishi
#define UYG_UKY_X_CHONG  'X'	//Chong Yezilishi;
		//D
#define UYG_UKY_D_KICHIK 'd'	//Kichik yezilishi;
#define UYG_UKY_D_CHONG  'D'	//Chong Yezilishi;
		//R
#define UYG_UKY_R_KICHIK 'r'	//Kichik yezilishi;
#define UYG_UKY_R_CHONG  'R'	//Chong Yezilishi;
		//Z
#define UYG_UKY_Z_KICHIK 'z'	//Kichik yezilishi;
#define UYG_UKY_Z_CHONG  'Z'	//Chong Yezilishi;

//Z..
#define UYG_UKY_ZZ_KICHIK 'j'	//Kichik yezilishi;
#define UYG_UKY_ZZ_CHONG  'J'	//Chong Yezilishi;
		//S
#define UYG_UKY_S_KICHIK 's'	//Kichik yezilishi;
#define UYG_UKY_S_CHONG  'S'	//Chong Yezilishi;
		//F
#define UYG_UKY_F_KICHIK 'f'	//Kichik yezilishi;
#define UYG_UKY_F_CHONG  'F'	//Chong Yezilishi;
		//Q
#define UYG_UKY_Q_KICHIK 'q'	//Kichik yezilishi;
#define UYG_UKY_Q_CHONG  'Q'	//Chong Yezilishi;
		//K
#define UYG_UKY_K_KICHIK 'k'	//Kichik yezilishi;
#define UYG_UKY_K_CHONG  'K'	//Chong Yezilishi;
		//G
#define UYG_UKY_G_KICHIK 'g'	//Kichik yezilishi;
#define UYG_UKY_G_CHONG  'G'	//Chong Yezilishi;
		//L
#define UYG_UKY_L_KICHIK 'l'	//Kichik yezilishi;
#define UYG_UKY_L_CHONG  'L'	//Chong Yezilishi;
		//M
#define UYG_UKY_M_KICHIK 'm'	//Kichik yezilishi;
#define UYG_UKY_M_CHONG  'M'	//Chong Yezilishi;
		//N
#define UYG_UKY_N_KICHIK 'n'	//Kichik yezilishi;
#define UYG_UKY_N_CHONG  'N'	//Chong Yezilishi;
		//H..
#define UYG_UKY_H_KICHIK 'h'	//Kichik yezilishi;
#define UYG_UKY_H_CHONG  'H'	//Chong Yezilishi;
		//O
#define UYG_UKY_O_KICHIK 'o'	//Kichik yezilishi;
#define UYG_UKY_O_CHONG  'O'	//Chong Yezilishi;
		//U
#define UYG_UKY_U_KICHIK 'u'	//Kichik yezilishi;
#define UYG_UKY_U_CHONG  'U'	//Chong Yezilishi;
		//O..
#define UYG_UKY_OO_KICHIK 0xf6	//Kichik yezilishi;
#define UYG_UKY_OO_CHONG  0xd6	//Chong Yezilishi;
		//U..
#define UYG_UKY_UU_KICHIK 0xfc	//Kichik yezilishi;
#define UYG_UKY_UU_CHONG  0xdc	//Chong Yezilishi;
		//W
#define UYG_UKY_W_KICHIK 'w'	//Kichik yezilishi;
#define UYG_UKY_W_CHONG  'W'	//Chong Yezilishi;

        // Bunimu W dep bir terep qildim
#define UYG_UKY_V_KICHIK 'v'	//Kichik yezilishi;
#define UYG_UKY_V_CHONG  'V'	//Chong Yezilishi;

		//E..
#define UYG_UKY_EE_KICHIK 0xe9	//Kichik yezilishi;
#define UYG_UKY_EE_CHONG  0xc9	//Chong Yezilishi;
		//I
#define UYG_UKY_I_KICHIK 'i'	//Kichik yezilishi;
#define UYG_UKY_I_CHONG  'I'	//Chong Yezilishi;
		//Y
#define UYG_UKY_Y_KICHIK 'y'	//Kichik yezilishi;
#define UYG_UKY_Y_CHONG  'Y'	//Chong Yezilishi;

//Amza
#define UYG_UKY_HM		 0x0027	//Kichik yezilishi;


#define UYG_UKY_BOSH      		0x0020 //Boshluq Belgisi
#define UYG_UKY_UNDESH    		0x0021 //Undesh Belgisi
#define UYG_UKY_QOSHPESH  		0x0022 //Qosh Pesh
#define UYG_UKY_REQEM      		0x0023 //Reqem Belgisi #
#define UYG_UKY_DOLLAR    		0x0024 //Dollar Belgisi
#define UYG_UKY_PIRSENT   		0x0025    //Pirsent Belgisi
#define UYG_UKY_WE	      		0x0026 //& belgisi
#define UYG_UKY_TIKPESH_OLD		0x0027 //yalang pesh '(yaki Tik Pesh)
#define UYG_UKY_TIKPESH         0x2019
#define UYG_UKY_SOL_K_TIRNAQ	0x0028 //Sol Tirnaq(
#define UYG_UKY_ONG_K_TIRNAQ	0x0029 //Ong tirnaq)
#define UYG_UKY_YULTUZ			0x002A    //Yultuz belgisi
#define UYG_UKY_QOSHUSH			0x002B //Qoshush Belgisi
#define UYG_UKY_PESH      		0x002C    //Pesh
#define UYG_UKY_SIZIQCHE		0x002D   //Boghum ayrish Belgisi
#define UYG_UKY_CHEKIT			0x002E //Chekit
#define UYG_UKY_ONG_YANTO		0x002F //Chekit
#define UYG_UKY_0				0x0030 // Nol
#define UYG_UKY_1				0x0031 // Bir
#define UYG_UKY_2				0x0032 // Ikki
#define UYG_UKY_3				0x0033 // Uch
#define UYG_UKY_4				0x0034 // Tort
#define UYG_UKY_5				0x0035 // Besh
#define UYG_UKY_6				0x0036 // Alte
#define UYG_UKY_7				0x0037 // Yette
#define UYG_UKY_8				0x0038 // Sekkiz
#define UYG_UKY_9				0x0039 // Toqquz
#define UYG_UKY_QOSHCHEKIT		0x003A // Qosh Chekit
#define UYG_UKY_CHEKITPESH 		0x003B    // Chekitlik Pesh
#define UYG_UKY_KICHIK			0x2039 // Kichik Belgisi
#define UYG_UKY_CHONG			0x203A // ChongBelgisi
#define UYG_UKY_TENG			0x003D // Tenglik Belgisi
#define UYG_UKY_SOAL			0x003F    // Soal Belgisi
#define UYG_UKY_MEKTUP			0x0040 // E-mail Adres Belgisi@
#define UYG_UKY_SOL_O_TIRNAQ	0x005B // Sol Ottura Tirnaq
#define UYG_UKY_SOL_YANTO		0x005C // Sol Yantu siziq(ong yantu Siziq hemzige teqsimlengen)
#define UYG_UKY_ONG_O_TIRNAQ	0x005D // Sol Ottura Tirnaq
#define UYG_UKY_DERIJE		    0x005E // Sol Ottura Tirnaq
#define UYG_UKY_SIZIQ		    0x2014 // Sol Ottura Tirnaq
#define UYG_UKY_QIYPESH			0x0060 // Qiypash Pesh
#define UYG_UKY_SOL_CH_TIRNAQ	0x00AB // Chong Sol Tirnaq
#define UYG_UKY_TIKSIZIQ		0x007C // Tik Siziq
#define UYG_UKY_ONG_CH_TIRNAQ	0x00BB // Chong Ong Tirnaq
#define UYG_UKY_DOLQUN			0x007E // Dolqun belgisi~

/*

//A
#define UYG_BGD_A_Y 0xF9A1	//Yalghuz
#define UYG_BGD_A_A 0xFAA1 //Ayaq
// E Heripi
#define UYG_BGD_E_Y 0xf9A2  //Yalghuz;
#define UYG_BGD_E_A 0xFAA2	//Ayaq;
// B
#define UYG_BGD_B_Y 0xf9b0  //Yalghuz;
#define UYG_BGD_B_A 0xFAB0	//Ayaq;
#define UYG_BGD_B_B 0xF9AF	//Bax;
#define UYG_BGD_B_O 0xFAAF	//Ottura;
//P
#define UYG_BGD_P_Y 0xf9b2  //Yalghuz;
#define UYG_BGD_P_A 0xFAB2	//Ayaq;
#define UYG_BGD_P_B 0xF9B1	//Bax;
#define UYG_BGD_P_O 0xFAB1	//Ottura;
//T
#define UYG_BGD_T_Y 0xf9b4  //Yalghuz;
#define UYG_BGD_T_A 0xFAB4	//Ayaq;
#define UYG_BGD_T_B 0xF9B3	//Bax;
#define UYG_BGD_T_O 0xFAB3	//Ottura;
//J
#define UYG_BGD_J_Y 0xf9b6  //Yalghuz;
#define UYG_BGD_J_B 0xF9B5	//Bax;
#define UYG_BGD_J_O 0xFAB5	//Ottura;
#define UYG_BGD_J_A 0xFAB6	//Ayaq;
//Ch
#define UYG_BGD_CH_Y 0xf9b8  //Yalghuz;
#define UYG_BGD_CH_A 0xFAB8	//Ayaq;
#define UYG_BGD_CH_B 0xF9B7	//Bax;
#define UYG_BGD_CH_O 0xFAB7	//Ottura;
//X
#define UYG_BGD_X_Y 0xf9BA  //Yalghuz;
#define UYG_BGD_X_A 0xFABA	//Ayaq;
#define UYG_BGD_X_B 0xF9B9	//Bax;
#define UYG_BGD_X_O 0xFAB9	//Ottura;
//D
#define UYG_BGD_D_Y 0xf9e7  //Yalghuz;
#define UYG_BGD_D_A 0xFAE7	//Ayaq;
//R
#define UYG_BGD_R_Y 0xf9e8  //Yalghuz;
#define UYG_BGD_R_A 0xFAE8	//Ayaq;
//Z
#define UYG_BGD_Z_Y 0xf9e9  //Yalghuz;
#define UYG_BGD_Z_A 0xFAE9	//Ayaq;
//Z..
#define UYG_BGD_ZZ_Y 0xf9EA  //Yalghuz;
#define UYG_BGD_ZZ_A 0xFAEA	//Ayaq;
//S
#define UYG_BGD_S_Y 0xf9bc  //Yalghuz;
#define UYG_BGD_S_A 0xFABC	//Ayaq;
#define UYG_BGD_S_B 0xF9BB	//Bax;
#define UYG_BGD_S_O 0xFABB	//Ottura;
//SH
#define UYG_BGD_SH_Y 0xf9be  //Yalghuz;
#define UYG_BGD_SH_A 0xFABE	//Ayaq;
#define UYG_BGD_SH_B 0xF9BD	//Bax;
#define UYG_BGD_SH_O 0xFABD	//Ottura;
//GH
#define UYG_BGD_GH_Y 0xf9c0  //Yalghuz;
#define UYG_BGD_GH_A 0xFAC0	//Ayaq;
#define UYG_BGD_GH_B 0xF9BF	//Bax;
#define UYG_BGD_GH_O 0xFABF	//Ottura;
//F
#define UYG_BGD_F_Y 0xf9c2  //Yalghuz;
#define UYG_BGD_F_A 0xFAC2	//Ayaq;
#define UYG_BGD_F_B 0xF9C1	//Bax;
#define UYG_BGD_F_O 0xFAC1	//Ottura;
//Q
#define UYG_BGD_Q_Y 0xf9c4  //Yalghuz;
#define UYG_BGD_Q_A 0xFAC4	//Ayaq;
#define UYG_BGD_Q_B 0xF9C3	//Bax;
#define UYG_BGD_Q_O 0xFAC3	//Ottura;
//K
#define UYG_BGD_K_Y 0xf9c6  //Yalghuz;
#define UYG_BGD_K_A 0xFAC6	//Ayaq;
#define UYG_BGD_K_B 0xF9C5	//Bax;
#define UYG_BGD_K_O 0xFAC5	//Ottura;
//G
#define UYG_BGD_G_Y 0xf9c8  //Yalghuz;
#define UYG_BGD_G_A 0xFAC8	//Ayaq;
#define UYG_BGD_G_B 0xF9C7	//Bax;
#define UYG_BGD_G_O 0xFAC7	//Ottura;
//NG
#define UYG_BGD_NG_Y 0xf9ca  //Yalghuz;
#define UYG_BGD_NG_A 0xFACA	//Ayaq;
#define UYG_BGD_NG_B 0xF9C9	//Bax;
#define UYG_BGD_NG_O 0xFAC9	//Ottura;
//L
#define UYG_BGD_L_Y 0xf9cc  //Yalghuz;
#define UYG_BGD_L_A 0xFACC	//Ayaq;
#define UYG_BGD_L_B 0xF9CB	//Bax;
#define UYG_BGD_L_O 0xFACB	//Ottura;
//M
#define UYG_BGD_M_Y 0xf9ce  //Yalghuz;
#define UYG_BGD_M_A 0xFACE	//Ayaq;
#define UYG_BGD_M_B 0xF9CD	//Bax;
#define UYG_BGD_M_O 0xFACD	//Ottura;
//N
#define UYG_BGD_N_Y 0xf9d0  //Yalghuz;
#define UYG_BGD_N_A 0xFAD0	//Ayaq;
#define UYG_BGD_N_B 0xF9CF	//Bax;
#define UYG_BGD_N_O 0xFACF	//Ottura;
//H..
#define UYG_BGD_H_Y 0xf9e2  //Yalghuz;
#define UYG_BGD_H_A 0xFAE2	//Ayaq;
#define UYG_BGD_H_B 0xF9E1	//Bax;
#define UYG_BGD_H_O 0xFAE1	//Ottura;
//O
#define UYG_BGD_O_Y 0xf9a3  //Yalghuz;
#define UYG_BGD_O_A 0xFAA3	//Ayaq;
//U
#define UYG_BGD_U_Y 0xf9a4  //Yalghuz;
#define UYG_BGD_U_A 0xFAA4	//Ayaq;
//O..
#define UYG_BGD_OO_Y 0xf9a5  //Yalghuz;
#define UYG_BGD_OO_A 0xFAA5	//Ayaq;
//U..
#define UYG_BGD_UU_Y 0xf9a6  //Yalghuz;
#define UYG_BGD_UU_A 0xFAA6	//Ayaq;
//W
#define UYG_BGD_W_Y 0xf9eB  //Yalghuz;
#define UYG_BGD_W_A 0xFAEB	//Ayaq;

//E..
#define UYG_BGD_EE_Y 0xf9ac  //Yalghuz;
#define UYG_BGD_EE_A 0xFAAC	//Ayaq;
#define UYG_BGD_EE_B 0xF9AB	//Bax;
#define UYG_BGD_EE_O 0xFAAB	//Ottura;

//I
#define UYG_BGD_I_Y 0xf9ae  //Yalghuz;
#define UYG_BGD_I_A 0xFAAE	//Ayaq;
#define UYG_BGD_I_B 0xF9AD	//Bax;
#define UYG_BGD_I_O 0xFAAD	//Ottura;
//Y
#define UYG_BGD_Y_Y 0xf9d2  //Yalghuz;
#define UYG_BGD_Y_A 0xFAD2	//Ayaq;
#define UYG_BGD_Y_B 0xF9D1	//Bax;
#define UYG_BGD_Y_O 0xFAD1	//Ottura;
//La
#define UYG_BGD_LA_Y 0xf9AA  //Yalghuz;
#define UYG_BGD_LA_A 0xFAAA	//Ayaq;
//Amza
#define UYG_BGD_HM_Y 0xf9df  //Yalghuz;
#define UYG_BGD_HM_O 0xFAdf	//Ottura;
#define UYG_BGD_HM_B 0xf9E0  //Yalghuz;
#define UYG_BGD_HM_A 0xfAE0  //Yalghuz;


#define UYG_BGD_BOSH      		0x0020 //Boshluq Belgisi
#define UYG_BGD_UNDESH    		0xFAF5 //Undesh Belgisi
#define UYG_BGD_QOSHPESH  		0x0022 //Qosh Pesh
#define UYG_BGD_REQEM      		0x0023 //Reqem Belgisi #
#define UYG_BGD_DOLLAR    		0x0024 //Dollar Belgisi
#define UYG_BGD_PIRSENT   		0x0025 //Pirsent Belgisi
#define UYG_BGD_WE	      		0x0026 //& belgisi
#define UYG_BGD_TIKPESH		    0x00F0 //yalang pesh '(yaki Tik Pesh)
#define UYG_BGD_SOL_K_TIRNAQ	0xFAF9 //Sol Tirnaq(
#define UYG_BGD_ONG_K_TIRNAQ	0xFAF7 //Ong tirnaq)
#define UYG_BGD_YULTUZ			0xF9EF //Yultuz belgisi
#define UYG_BGD_QOSHUSH			0xF9FA //Qoshush Belgisi
#define UYG_BGD_PESH      		0xFAF0 //Pesh
#define UYG_BGD_BOGHUM			0xFAEF //Boghum ayrish belgisi, Sozlerni Sozush uchunmu ishlitilidu
#define UYG_BGD_CHEKIT			0xFAf1 //Chekit
#define UYG_BGD_0				0xF9F0 // Nol
#define UYG_BGD_1				0xF9F1 // Bir
#define UYG_BGD_2				0xF9F2 // Ikki
#define UYG_BGD_3				0xF9F3 // Uch
#define UYG_BGD_4				0xF9F4 // Tort
#define UYG_BGD_5				0xF9F5 // Besh
#define UYG_BGD_6				0xF9F6 // Alte
#define UYG_BGD_7				0xF9F7 // Yette
#define UYG_BGD_8				0xF9F8 // Sekkiz
#define UYG_BGD_9				0xF9F9 // Toqquz
#define UYG_BGD_QOSHCHEKIT		0xFAF3 // Qosh Chekit
#define UYG_BGD_CHEKITPESH 		0xFAF2 // Chekitlik Pesh
#define UYG_BGD_CHONG			0xFAFB // ChongBelgisi
#define UYG_BGD_TENG			0x003D // Tenglik Belgisi
#define UYG_BGD_KICHIK			0xFAFD // Kichik Belgisi
#define UYG_BGD_SOAL			0xFAF6 // Soal Belgisi
#define UYG_BGD_MEKTUP			0x0040 // E-mail Adres Belgisi@
#define UYG_BGD_SOL_O_TIRNAQ    0xFAFE // Sol Ottura Tirnaq
#define UYG_BGD_SOL_YANTO       0x005C // Sol Yantu siziq(ong yantu Siziq hemzige teqsimlengen)
#define UYG_BGD_ONG_O_TIRNAQ    0xFAFC // ONG Ottura Tirnaq
#define UYG_BGD_DERIJE		    0x005E // dERIJE bELGISI
#define UYG_BGD_PESSIZIQ	    0xFAF4 // Sol Ottura Tirnaq
#define UYG_BGD_QIYPESH         0x0060 // Qiypash Pesh
#define UYG_BGD_SOL_CH_TIRNAQ   0x007B // Chong Sol Tirnaq
#define UYG_BGD_TIKSIZIQ        0x007C // Tik Siziq
#define UYG_BGD_ONG_CH_TIRNAQ   0x007D // Chong Ong Tirnaq
#define UYG_BGD_DOLQUN          0x007E // Dolqun belgisi~
*/
#endif
