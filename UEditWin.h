#ifndef UEDITWIN_H
#define UEDITWIN_H 1
#include <windows.h>
#include <winnls.h>
#include "CDoUndoManage.h"
#include "UYGString.h"
#include "UMessageBox.h"
#include "UCommon.h"
#include "UBidiLine.h"
#include "ortaq.h"


#define _CLSName TEXT("UEDITWIN")

#define  HEADS0 TEXT("<html")
#define  HEADS1 TEXT(">\n<head>\n<meta http-equiv=\"Content-Type\" content=\"text/html; charset=")
#define  HEADS2 TEXT("\">\n<meta name=\"GENERATOR\" content=\"UyghurEdit By Gheyret T.Kenji\">\n<style type=\"text/css\">\n<!--\np{\n\tfont-size: 120%;\n\tfont-family: Boghda Tuz, UKIJ Nasq, UKIJ Tuz, UKIJ Basma, UKIJ Zilwa, Arial Unicode MS,Tahoma;\n\ttext-align: justify;\n}\n-->\n</style>\n<title>")
#define  HEADS3 TEXT("</title>\n</head>\n<body>\n<p>")

enum YEZIQ{NODETC,UEY,ULY,USY,OTY,UMY};
class UEditWin
{
private:
    HWND 		m_hWnd;
	HINSTANCE 	mhInstance;
	HWND      	mhWndParent;
    HDC  		UBeginPaint(LPPAINTSTRUCT ps);
    BOOL 		UEndPaint(LPPAINTSTRUCT ps);
    TCHAR		m_UFileName[MAX_PATH];
    ULONG       m_USelPos;
    ULONG       m_USelS,m_USelE;

    CDoUndoManage  *m_UnReDO;
    BOOL 		m_Qisturush;
    int  		m_NurKeng;

	UINT		m_VY;
	UINT        m_VX;
	UNOTIFY     m_UNotify;

	HFONT		m_UUyghurFont;			// Ekranda Ishlitiliwatqan Uyghurche Heriplerning
	HFONT		m_ULocalFont;			// Ekranda Ishlitiliwatqan Uyghurchidin bashqisining
  	int 		m_UQurIgizligi;
  	UINT        m_BetQurSani;
  	ULONG       m_JemiQurSani;
	ULONG		m_JemiQurSaniZap;
  	UINT        m_BetKeng;
  	UINT        m_EngKeng;
	wchar_t*	m_UFirstLine;			// Ekranda Korsitilgen birinchi qurning Adresi
	UINT  		m_HazirqiQur;           // Nur belgisi Turghan Qur
	UINT        m_HazirqiHerip;         // Nur Belgisi Turghan ston
	UINT        m_esliQur;

	int			m_Boshluq;             // Ramka girwigidin bashlap heripni korsitidighan boshluq
	BOOL        m_UTextChanged;
	BOOL		m_UMouseBesildi;

  	void UCreateFont();
  	void USetScroll(void);
  	UYGString   m_UBuffer;
	UEDIT	    m_UEdit;
	HBRUSH      m_UEkranReng;
	HBRUSH      m_UTalReng;
	wchar_t     *m_UCurLine;

	HCURSOR     m_oldCursor;
	HMENU       m_UPopMenu;
	void UYengiHojjet();
//	void UShowInfo(wchar_t *msgKey);
//	int  UShowAgahlandurush(wchar_t *msgKey,UINT mb);
	void UUpdateHorScroll();
	void UOnTizishAbzas();
	void UOnTizishHemme();
	void UChaplaStr(wchar_t *clipData);
	int  m_SaveCodePage;
	BOOL m_BaseCode;
	BOOL m_BOM;

	void UOnDeleteKey();
	void UOnBackspaceKey();
	void UOnHomeKey();
	void UOnEndKey();
	void UOnUpKey();
	void UOnDownKey();
	void UOnLeftKey();
	void UOnRightKey();
	void UOnReturnKey();
	void UOnPageUpKey();
	void UOnPageDownKey();
	void UOnToULY();
	void UOnToUEY_TXT();
	void UOnToUEY_PRG();
	void UOnToUEY_INF();
	void UOnBesish(LPARAM lp);
	void UOnSetFont();
	KUNUPKA  USetKunupka(KUNUPKA val);

	int      UGetPoss(wchar_t *line,int *sPos); //Qosh tirnaq bilen qorshalghan tekistni tapidu
	int      UGetTengPoss(wchar_t *line,int *sPos); //Tenglik Belgisining Ornini we tenglik belgisidin keyinki mezmunning uzunliqini tapidu
    int      UGetUyghurTizma(wchar_t *line,int *sPos);
    void     UOnToUyghurLatinInf();
	void     USozgeParchila(bool qosh);
	void     USozgeParchila_Tekshurme();
	void     UAbsazni_Sort();

	UMessageBox m_UMsgBox;

	IZDESH      m_UIzdesh;
	void        UOnIzdesh();
	void        UOnIzdeshDawam();

	void        UIzdesh();
	void        UAlmashturush();
	wchar_t 	*UUlash(wchar_t *qurBeshi,long qurLen,long *newLen);

	char        *m_USelSt;
	wchar_t     *m_UShowLine;
	long        UMakeShowBuffer(wchar_t *qurBeshi,long qurLen,wchar_t *selS,wchar_t *selE);
	unsigned long        UGetAsasKod(wchar_t *esliBuf,wchar_t *asasBuf);
	void        UOutTextCurLine(ULONG lineNum,bool useBidi);  // Nur Belgisi Turghan qurni qayta ekrangha yazidu
	UBidiLine   m_UBidi;
    wchar_t*    UTizmaTap(wchar_t *curPos, wchar_t *strSrc,QANDAQ qan);
    UINT ImlaTekshurushULY(UINT ope);
    UINT ImlaTekshurushUEY(UINT ope);
    UINT ImlaTekshurushAlahide(UINT ope);
    //Bu Eslibuf tiki UEY diki mezmunni, UYghur_XATA.dic ti npaydilinip aptomatik toghrilaydu
    void Toghrila(wchar_t *EsliBuf,wchar_t *newBuf);
    //Yengidin UyghurEdit ni qozghitidu, (Memorydiki tekistni yengi ramkida korsitidu)
    void  UNewUyghurEdit();
	BOOL  UCalSelPos(void);

	void  MewhumToUyghur(void);
	void  UAlahide2Latin(void);
	void  UyghurToMewhum(void);
    BOOL  UAlahideKodBarmu();
	BOOL  m_Alahide;
    void  Alhide2Uyghurwekochur(void);

	UINT AptomatikToghrilaAlahide(void);
	UINT AptomatikToghrilaULY(void);
	UINT AptomatikToghrilaUEY(void);
	void UAptomatikToghrila(void);
    YEZIQ DetectYeziq(wchar_t *buf);

public:
	void UOnImlaTekshur(WPARAM wParam, LPARAM lParam);
    UEditWin(HINSTANCE hInstance,HWND par);
    ~UEditWin();
    BOOL UShowWindow(int nCmdShow);
    BOOL UUpdateWindow();
    void USetFocus();
	HWND UCreate();
    LRESULT UOnPaint(WPARAM wParam, LPARAM lParam);
    LRESULT UOnCreate(WPARAM wParam, LPARAM lParam);
	void UOnChar(WPARAM wParam, LPARAM lParam);
	void UOnImeChar(WPARAM wParam, LPARAM lParam);
    void UOnSize(WPARAM wParam, LPARAM lParam);
    BOOL UTuzitildimu();
    void UCreateCaret();
    void UDestroyCaret();
	//Sinaq uchun
	void USetText(wchar_t *txt);
	void UOnHScroll(UINT nSBCode,int pos);
	void UOnVScroll(UINT nSBCode,int pos);
	UINT UGetHeripPosFromX(UINT curLine,int x);
	UINT UGetXFromHeripPos(wchar_t *pcurLine, int HeripPos);
	BOOL UIsEmpty(void);
	int  UGetHerpKeng(wchar_t Herp , HDC dc);
	void UOnImeInput(WPARAM wp,LPARAM lp);

	int  UGetHeripTizmisiWidth(HDC dc,wchar_t *buf,UINT len);

	ULONG UTengshesh(wchar_t *oldBuf,ULONG bufLen,wchar_t *newBuf,ULONG kenglik,ULONG oldOffset);
	ULONG UTengsheshAbzas(wchar_t *oldBuf,UINT bufLen,wchar_t *newBuf,UINT kenglik,ULONG oldOffset);

	void UBeginWaitCursor();
	void UEndWaitCursor();
	void UShowCaret();
	BOOL UKorundighanEkran(int Type);
	void USetImePos();
	void UOnLButtonDown(int x,int y);
	void UOnLButtonUp(int x, int y);
	void UOnMouseMove(int x, int y);
	void UOnLDoubleClick(int x, int y);
	void UOnRButtonUp(int mx, int my);
	void UOnMouseWheel(WPARAM wp,LPARAM lp);
	BOOL UOnKeyDown(WPARAM wParam, LPARAM lParam);
	BOOL UIsTextSelected(void);
	wchar_t *UGetSelectionText(BOOL remove=FALSE);
	BOOL UClearSelection(BOOL Delete);
	void UAddUnDO(wchar_t *_esli, wchar_t *_yengi);
	void UInvalidate();
	UINT  UTextOutLine(HDC dc,int qur,wchar_t * aLine,int lineLen,wchar_t* talBeshi,wchar_t *talAxiri,bool useBidi);
	void USetRTL(BOOL val);
	BOOL UBuyruq(WPARAM wParam,LPARAM lParam);
	void ULYKunupka(UINT kun);
	KUNUPKA  UGetKunupka();
	void  UILangChanged();
	ULONG UGetQurSani(wchar_t* Str);
	void UOnRedo();
	void UOnUndo();
	BOOL UCanUndo();
	BOOL UCanRedo();
	BOOL UIsFileNameEmpty();
	BOOL UIsRTL();
	wchar_t *UGetFileName();
	void USetFileName(wchar_t * filenm);
	int  USaveFile();
	int  USaveFileAsHTML(wchar_t *filenm,int CodePage, BOOL baseCode, BOOL bom);

	UINTERFACE_LANG UGetInterfaceLang();
	void            USetInterfaceLang(UINTERFACE_LANG lang);

	void USetSaveCodePage(int codePage);
	void USetSaveBaseCode(BOOL baseCode);
	void USetSaveBOM(BOOL bom);
	BOOL  UGetSaveBOM();
	void UReadFromCodePage(int codePage);
	void UOnKochurush();
	void USetToClipboard();
	void UOnChaplash();
	void UOnKesish();
	void UOnOchurush();

	void UOnToUyghurLatin();
	void UOnToUyghurArabic();
	void UOnToUyghurSlawiyan();
    void UOnSlawiyanToUyghurArabic();
    void UOnToTurk();
    void UOnTurkToUyghurArabic();

    void UOnToUyghurArabic_Program();
	void UOnToChong();
	void UOnToKichik();
	void UOnKochurushAll();
	void UOnChaplashBashqa(UINT );
	void USetSelPos(ULONG Pos);
	ULONG UGetSelPos();
	BOOL UAutoQatla();

    // Towendikiler Putkul Hojjetni aylanduridu
	void UOnUyghurToSlawiyan();
	void UOnSlawiyanToUyghur();
	void UOnUyghurToTurk();
	void UOnTurkToUyghur();
	void UAtalghularniTap();
	BOOL UAtalghuBarmu(wchar_t *Qur);

	void UGeAylandur(UINT buy, YEZIQ yez);
    void ToUyghur(BOOL sel, YEZIQ hazir, wchar_t *esliText);
    void ToLatin(BOOL sel, YEZIQ hazir, wchar_t *esliText);
    void ToSlawiyan(BOOL sel, YEZIQ hazir, wchar_t *esliText);
    void ToTurk(BOOL sel, YEZIQ hazir, wchar_t *esliText);
    void ToMewhum(BOOL sel, YEZIQ hazir, wchar_t *esliText);
    void UDelEnter();
};
#endif
