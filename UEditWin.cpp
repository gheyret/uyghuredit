#include <io.h>
#include <stdio.h>
#include <stdint.h>

#include "UEditWin.h"
#include "UPrinter.h"
#include "resource.h"
#include "RegistryOperation.h"
#include "UyghurcheKodAlmashturush.h"
#include "UyghurKeyboard.h"
#include "SetFont.h"

#ifndef WM_MOUSEWHEEL
#define WM_MOUSEWHEEL                   0x020A
#endif
extern wchar_t _gmsgBuf[256];
extern wchar_t* gUGetVal(wchar_t *Key);
extern int gUGetUnicodeIndex(wchar_t Herp);
extern bool gUIsLowerULY(wchar_t Herp);
extern bool gUIsLowerAlahide(wchar_t Herp1);
extern wchar_t gUToLowerULY(wchar_t Herp);
extern wchar_t gUToLowerAlahide(wchar_t Herp);
extern BOOL gUIsUyghur(wchar_t Herip);
extern BOOL gUIsSozuqTawushUNICODE(wchar_t Herip);
extern BOOL gUIsSozuqTawushUKY(wchar_t Herip);
extern int gUGetUKYIndex(wchar_t ukyHerip);
extern int gUGetBgdIndex(wchar_t Herp);
extern wchar_t * gUUlash(wchar_t *Soz);
extern void gDoEvents(void);
extern wchar_t *gUGetUnicodeBuf(UINT codePage,char *Buf);
extern void gUInitUnicodeCode(void);
extern wchar_t gUGetHerpFromNotepad(wchar_t Herp);
extern wchar_t gUGetHerpFromIlikyurt(wchar_t Herp);
extern int gUGetUyghurSoftIndex(wchar_t Herp);
extern int gUGetDuldulIndex(wchar_t Herp);
extern wchar_t *gGetFromClipboard(void);
extern BOOL gIsClipBoradEmpty(void);
extern void gSetToClipboard(wchar_t* selText);
extern void gUSort(wchar_t *Buffer,wchar_t del,bool delSame);
extern int gUSetWindowCenter(HWND hWnd,int width,int height);
extern int gUSetWindowCenter(HWND hWnd);
extern int gUIsUTF8_16(unsigned char *s, unsigned int len);
extern int gUAutoDetectBOGHDAWEI(unsigned char *s, unsigned int len);

extern int gwctoutf8 (unsigned char *s, wchar_t c);
extern int gutf8towc(unsigned char *out, wchar_t *Herp);

extern Init UInitImla;
extern IsCorrect UIsCorrect;
extern CheckWord UCheckWord;
extern LoadDictionary ULoadDictionary;
extern UnLoadDictionary UUnLoadDictionary;
extern GetCandidateWord UGetCandidateWord;
extern GetOrgWord UGetOrgWord;
extern ShowFindDialog UShowFindDialog;
extern SetUILang USetUILang;
extern GetToghrisi UGetToghrisi;

CUyghurKeyboard g_UKeyboard;

LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    UEditWin *g_pUEditWin;
    g_pUEditWin = ( UEditWin* )::GetWindowLong( hWnd, GWL_USERDATA );
    if(g_pUEditWin==NULL)
    {
        return::DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    switch (uMsg)
    {
    case WM_COMMAND:
    {
        UINT cmdID    = LOWORD(wParam);
        switch(cmdID)
        {
        case UUKY_HERIP_UU_KICHIK:
        case UUKY_HERIP_EE_KICHIK:
        case UUKY_HERIP_OO_KICHIK:
        case UUKY_HERIP_UU_CHONG:
        case UUKY_HERIP_EE_CHONG:
        case UUKY_HERIP_OO_CHONG:
            g_pUEditWin->ULYKunupka(cmdID);
            break;
        case BIRIKME_PIRSENT_S:
        {
            g_pUEditWin->UOnImeChar((WPARAM)'%',0x0);
            g_pUEditWin->UOnImeChar((WPARAM)'s',0x0);
            break;
        }
        case BIRIKME_QAYTURUSH:
        {
            g_pUEditWin->UOnImeChar((WPARAM)'\\',0x0);
            g_pUEditWin->UOnImeChar((WPARAM)'n',0x0);
            break;
        }
        case BIRIKME_PUTUNSAN_D:
        {
            g_pUEditWin->UOnImeChar((WPARAM)'%',0x0);
            g_pUEditWin->UOnImeChar((WPARAM)'d',0x0);
            break;
        }
        default:
            SendMessage(GetParent(hWnd),WM_COMMAND,wParam, lParam);
            break;
        }
    }
    break;
    case WM_DROPFILES:
        SendMessage(GetParent(hWnd),WM_DROPFILES,wParam, lParam);
        break;
    case WM_CREATE:
        break;
    case WM_ERASEBKGND:
        break;
    case WM_PAINT:
        g_pUEditWin->UOnPaint(wParam,lParam);
        break;
    case WM_KEYDOWN:
        g_pUEditWin->UOnKeyDown(wParam,lParam);
        break;
    case WM_IME_CHAR:
        g_pUEditWin->UOnImeChar(wParam,lParam);
        break;
    case WM_CHAR:
        g_pUEditWin->UOnChar(wParam,lParam);
        break;
    case WM_LBUTTONUP:
    {
        int x=LOWORD(lParam);
        int y=HIWORD(lParam);
        g_pUEditWin->UOnLButtonUp(x,y);
    }
    break;

    case WM_RBUTTONUP:
    {
        int x=LOWORD(lParam);
        int y=HIWORD(lParam);
        g_pUEditWin->UOnRButtonUp(x,y);
    }
    break;
    case WM_MOUSEMOVE:
    {
        int x=LOWORD(lParam);
        int y=HIWORD(lParam);
        g_pUEditWin->UOnMouseMove(x,y);
    }
    break;
    case WM_LBUTTONDBLCLK:
    {
        int x=LOWORD(lParam);
        int y=HIWORD(lParam);
        g_pUEditWin->UOnLDoubleClick(x,y);
    }
    break;
    case WM_MOUSEWHEEL:
    {
        g_pUEditWin->UOnMouseWheel(wParam,lParam);
    }
    break;
    case WM_LBUTTONDOWN:
    {
        int x=LOWORD(lParam);
        int y=HIWORD(lParam);
        g_pUEditWin->UOnLButtonDown (x,y);
    }
    break;
    case WM_SETFOCUS:
        g_pUEditWin->UCreateCaret();
        break;
    case WM_KILLFOCUS:
        g_pUEditWin->UDestroyCaret();
        break;
    case WM_SIZE:
        g_pUEditWin->UOnSize(wParam,lParam);
        break;
    case WM_HSCROLL:
    {
        UINT code=LOWORD(wParam);
        UINT  pos=HIWORD(wParam);
        g_pUEditWin->UOnHScroll(code,pos);
    }
    break;
    case WM_VSCROLL:
    {
        UINT code=LOWORD(wParam);
        UINT  pos=HIWORD(wParam);
        g_pUEditWin->UOnVScroll(code,pos);
    }
    break;
    case UM_BUYRUQ:
        g_pUEditWin->UBuyruq(wParam,lParam);
        break;
    case UM_IMLA:
        g_pUEditWin->UOnImlaTekshur(wParam,lParam);
        break;
    default:
        return::DefWindowProc(hWnd, uMsg, wParam, lParam);
    }
    return TRUE;
}

void UEditWin::UCreateCaret()
{
    DestroyCaret();
    if(m_Qisturush)
    {
        m_NurKeng=1;
    }
    else
    {
        m_NurKeng=5;
    }
    ::CreateCaret(m_hWnd,NULL,m_NurKeng,m_UQurIgizligi);
    ShowCaret(m_hWnd);
    UShowCaret();
}

void UEditWin::UDestroyCaret()
{
    ::DestroyCaret();
}

UEditWin::UEditWin(HINSTANCE hInstance,HWND par)
{
    LANGID langid;

    mhInstance=hInstance;
    mhWndParent=par;
    WNDCLASSEX wnd;
    if (!(::GetClassInfoEx(hInstance, _CLSName, &wnd)))
    {
        wnd.cbSize    = sizeof(WNDCLASSEX);
        wnd.style        = CS_HREDRAW | CS_VREDRAW|CS_DBLCLKS;
        wnd.lpfnWndProc    = WndProc;
        wnd.cbClsExtra    = 0x0;
        wnd.cbWndExtra    = 0x0;
        wnd.hInstance    = hInstance;
        wnd.hIcon        = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_UYGHUREDITICO));
        wnd.hIconSm        = LoadIcon(hInstance, MAKEINTRESOURCE(IDR_UYGHUREDITICO_S));
        wnd.hCursor    = LoadCursor(hInstance, MAKEINTRESOURCE(RESIM_KORSETKUCH));
        wnd.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);
        wnd.lpszMenuName    = NULL;
        wnd.lpszClassName    = _CLSName;

        if (!RegisterClassEx(&wnd))
        {
            MessageBox(NULL, TEXT("Can not register UEDIT class"), TEXT("Error"), MB_OK | MB_ICONINFORMATION);
        }
    }
    m_USelPos=0;
    m_USelS=0;
    m_USelE=0;
    m_UnReDO=new CDoUndoManage();
    m_UFileName[0]=0x0;
    m_Qisturush=TRUE;
    m_UUyghurFont=NULL;
    m_ULocalFont=NULL;
    m_UEkranReng=NULL;
    m_UTalReng=NULL;

    m_UCurLine=NULL;

    m_VX=0;
    m_VY=0;
    m_JemiQurSani=0;
    m_EngKeng=0;
    m_HazirqiHerip=0;
    m_HazirqiQur=0;
    m_BetQurSani=0;
    m_UFirstLine=NULL;
    m_Qisturush=TRUE;


    m_Boshluq =3;               //Girwektin 3 chekit boshluq qalduridu
    m_UMouseBesildi=FALSE;
    m_UTextChanged=FALSE;
    gUInitUnicodeCode();
    g_UKeyboard.UInit();
    m_oldCursor=LoadCursor(hInstance,IDC_WAIT);
    m_UPopMenu=GetSubMenu(LoadMenu(hInstance, TEXT("IDM_UPOPUP")),0);
    m_SaveCodePage=CP_UTF8;
    m_BaseCode=TRUE;
    m_BOM=FALSE;


    CRegistryOperation op;
    if(op.GetSettings(&m_UEdit)==FALSE)
    {
        langid=GetUserDefaultLangID();
        wcscpy(m_UEdit.mue_UyghurFaceName,L"Boghda Tuz");
        wcscpy(m_UEdit.mue_LocalFaceName,L"Tahoma");
        m_UEdit.mue_FontPoint=14;
        m_UEdit.mue_Tom=FALSE;
        m_UEdit.mue_Qiypash=FALSE;
        m_UEdit.mue_QurArlighi=0;
        m_UEdit.mue_UUYG_ForeColor=RGB(0,0,0);
        m_UEdit.mue_UBashqa_ForeColor=RGB(0,110,0);
        m_UEdit.mue_UEkran_Color=RGB(255,255,255);
        m_UEdit.mue_UTal_ForeColor=RGB(255,255,255);
        m_UEdit.mue_UTal_BackColor=RGB(0,0,255);

        if(langid==1041)
        {
            m_UEdit.mue_Lang=LANG_JPN;
        }
        else if((langid&0x00FF)==0x0001||langid==1152)
        {
            m_UEdit.mue_Lang=LANG_UEY;
        }
        else if(langid==1049||langid==1087||langid==1088||langid==1092)
        {
            m_UEdit.mue_Lang=LANG_USY;
        }
        else if(langid==1055||langid==1142||langid==1090)
        {
            m_UEdit.mue_Lang=LANG_ULY;
        }
        else if((langid&0x00FF)==0x0004)
        {
            m_UEdit.mue_Lang=LANG_CHN;
        }
        else if((langid&0x00FF)==0x0013)
        {
            m_UEdit.mue_Lang=LANG_GER;
        }
        else
        {
            m_UEdit.mue_Lang=LANG_ENG;
        }

        m_UEdit.mue_RTL=TRUE;
        m_UEdit.mue_AutoQatlash=FALSE;
        m_UEdit.mue_Kunupka=KUNUPKA_UYGHUR;
    }
    m_UEdit.mue_AutoQatlash=FALSE;
    m_UEdit.mue_UBashqa_ForeColor=RGB(0,110,0);
    m_UEdit.mue_UEkran_Color=RGB(255,255,255);
    m_UIzdesh.mi_Action=Herket_YOQ;
    m_UIzdesh.mi_EsliSoz[0]=0x0;
    m_UIzdesh.mi_OrunbasarSoz[0]=0x0;
    m_UIzdesh.mi_Qandaq=SOZ_XALIGHAN;
}

HWND UEditWin::UCreate()
{
    RECT rc;
    ::GetClientRect(mhWndParent,&rc);
    m_hWnd =::CreateWindowEx(WS_EX_ACCEPTFILES|WS_EX_LEFTSCROLLBAR|WS_EX_RTLREADING,_CLSName,TEXT(""), WS_CHILD | WS_VISIBLE |WS_HSCROLL|WS_VSCROLL,	0, 0, rc.right, rc.bottom, mhWndParent,NULL, mhInstance, this);
    if(m_hWnd!=NULL)
    {
        ::SetWindowLong( m_hWnd, GWL_USERDATA,(LONG)this);
        UCreateFont();
        USetRTL(m_UEdit.mue_RTL);
        UYengiHojjet();
    }
    return m_hWnd;
}


UEditWin::~UEditWin()
{
    if(m_UPopMenu) DestroyMenu(m_UPopMenu);
    DeleteObject(m_UUyghurFont);
    DeleteObject(m_ULocalFont);

    if(m_UEkranReng!=NULL) DeleteObject(m_UEkranReng);
    if(m_UTalReng!=NULL) DeleteObject(m_UTalReng);
    if(m_UCurLine!=NULL) delete[] m_UCurLine;

    if(m_UnReDO!=NULL) delete m_UnReDO;
    CRegistryOperation op;
    op.SetSettings(&m_UEdit);
}


BOOL UEditWin::UShowWindow(int nCmdShow)
{
    return::ShowWindow(m_hWnd, nCmdShow);
}

BOOL UEditWin::UUpdateWindow()
{
    return::UpdateWindow(m_hWnd);
}

BOOL UEditWin::UTuzitildimu()
{
    return m_UTextChanged;
}

HDC UEditWin::UBeginPaint(LPPAINTSTRUCT ps)
{
    return::BeginPaint(m_hWnd, ps);
}

BOOL UEditWin::UEndPaint(LPPAINTSTRUCT ps)
{
    return::EndPaint(m_hWnd, ps);
}

void UEditWin::UCreateFont()
{
    if(m_UUyghurFont!=NULL) DeleteObject(m_UUyghurFont);
    if(m_ULocalFont!=NULL) DeleteObject(m_ULocalFont);

    if(m_UEkranReng!=NULL) DeleteObject(m_UEkranReng);
    if(m_UTalReng!=NULL) DeleteObject(m_UTalReng);

    m_UEkranReng=CreateSolidBrush(m_UEdit.mue_UEkran_Color);
    m_UTalReng=CreateSolidBrush(m_UEdit.mue_UTal_BackColor);

    LOGFONT logFnt;
    HDC dc=GetDC(m_hWnd);
    int reso=GetDeviceCaps(dc,LOGPIXELSY);
    memset(&logFnt,0x0,sizeof(LOGFONT));

    logFnt.lfHeight=-MulDiv((int)(m_UEdit.mue_FontPoint*10),reso,720);

    logFnt.lfItalic=m_UEdit.mue_Qiypash;
    if(m_UEdit.mue_Tom==TRUE)
    {
        logFnt.lfWeight=FW_BOLD;
    }
    else
    {
        logFnt.lfWeight=FW_REGULAR;
    }

    logFnt.lfOutPrecision=OUT_DEFAULT_PRECIS;
    logFnt.lfClipPrecision=CLIP_DEFAULT_PRECIS;
    logFnt.lfQuality=ANTIALIASED_QUALITY;
    logFnt.lfPitchAndFamily=DEFAULT_PITCH;


    wcscpy(logFnt.lfFaceName,m_UEdit.mue_UyghurFaceName);
    m_UUyghurFont=CreateFontIndirect(&logFnt);

    wcscpy(logFnt.lfFaceName,m_UEdit.mue_LocalFaceName);
    m_ULocalFont=CreateFontIndirect(&logFnt);

    //Ime ning Fontinimu LOcal Font bilen Oxshahs qilish

    HIMC hIMC = ImmGetContext(m_hWnd);
    ImmSetCompositionFont(hIMC,&logFnt);
    ImmReleaseContext(this->m_hWnd, hIMC);

    DeleteObject(SelectObject(dc, m_UUyghurFont));
    TEXTMETRIC tm;
    GetTextMetrics(dc,&tm);
    m_UQurIgizligi=tm.tmHeight+tm.tmExternalLeading+m_UEdit.mue_QurArlighi;
    ReleaseDC(m_hWnd,dc);
}


LRESULT UEditWin::UOnPaint(WPARAM wParam, LPARAM lParam)
{
    UINT keng;
    PAINTSTRUCT ps;
    HDC dc = UBeginPaint(&ps);
    HDC memDC;
    HBITMAP bitMap;
    RECT     rc;

    GetClientRect(m_hWnd,&rc);

    SetMapMode(dc,MM_TEXT);
    SetBkMode(dc,TRANSPARENT);

    memDC=CreateCompatibleDC(dc);
    bitMap=CreateCompatibleBitmap(dc,rc.right,rc.bottom);
    SelectObject(memDC,bitMap);
    SetMapMode(memDC,MM_TEXT);
    SetBkMode(memDC,TRANSPARENT);

    FillRect(memDC,&rc,m_UEkranReng);

    wchar_t *Line;
    UINT lineLen;
    UINT y=0;
    if(m_UFirstLine==NULL)
    {
        m_UFirstLine=m_UBuffer.GetLine(m_VY);
    }

    wchar_t *talBeshi=NULL;
    wchar_t *talAyaq=NULL;
    if(m_USelE>m_USelS)
    {
        talBeshi=m_UBuffer.GetAdressFromPos(m_USelS);
        talAyaq=m_UBuffer.GetAdressFromPos(m_USelE);
    }
    else
    {
        talBeshi=m_UBuffer.GetAdressFromPos(m_USelE);
        talAyaq=m_UBuffer.GetAdressFromPos(m_USelS);
    }
    m_EngKeng=0;
    Line=m_UFirstLine;
    while(Line!=NULL && y<=m_BetQurSani)
    {
        lineLen=m_UBuffer.GetLineLen(Line);
        if(lineLen>0)
        {
            if(y+m_VY==m_HazirqiQur)
            {
                keng=this->UTextOutLine(memDC,y,Line,lineLen,talBeshi,talAyaq,false);
            }
            else
            {
                keng=this->UTextOutLine(memDC,y,Line,lineLen,talBeshi,talAyaq,true);
            }
            if(keng>m_EngKeng)
            {
                m_EngKeng=keng;
            }
        }
        Line=m_UBuffer.GetNextLine(Line);
        y++;
    }
    BitBlt(dc,0,0,rc.right,rc.bottom,memDC,0,0,SRCCOPY);
    USetScroll();
    UEndPaint(&ps);
    DeleteObject(bitMap);
    DeleteDC(memDC);
    return 0;
}

COLORREF gAlahide=RGB(0, 0, 255);

UINT  UEditWin::UTextOutLine(HDC dc,int qur,wchar_t * aLine,int lineLen,wchar_t* talBeshi,wchar_t *talAxiri,bool useBidi)
{
    wchar_t Harip[UVK_TABSIZE+1];
    char    selSt;
    UINT    strWidth=0;
    RECT rc;
    int x;
    int y=qur*m_UQurIgizligi;
    GetClientRect(m_hWnd,&rc);
    if(m_UEdit.mue_RTL)
    {
        rc.right=rc.right-this->m_Boshluq;
        x=rc.right;
        x+=m_VX;
    }
    else
    {
        rc.left=m_Boshluq;
        x=rc.left;
        x-=m_VX;
    }

    long len=UMakeShowBuffer(aLine,lineLen,talBeshi,talAxiri);
    if(len==0) return 0;

    strWidth=UGetHeripTizmisiWidth(dc,m_UShowLine,len);

    int  *vIndex=NULL;
    if(useBidi)
    {
        vIndex=m_UBidi.getVisualOrder(m_UShowLine,m_UEdit.mue_RTL);
    }
    int i=0;
    int width;
    int disCnt;
    COLORREF fr;

    RECT    outRec;
    i=0;

    while(m_UShowLine[i]!=0x0)
    {
        if(useBidi)
        {
            if(m_UEdit.mue_RTL==TRUE)
            {
                Harip[0]=m_UBidi.Mirror(m_UShowLine[vIndex[len-i-1]]);
                selSt=m_USelSt[vIndex[len-i-1]];
            }
            else
            {
                Harip[0]=m_UShowLine[vIndex[i]];
                selSt=m_USelSt[vIndex[i]];
            }
        }
        else
        {
            Harip[0]=m_UShowLine[i];
            selSt=m_USelSt[i];
        }

        // Bu yerde Uyghurchimu yaki bashqilirimu Hokum qilidu
        // Uyghurceh bolsa Uyghurche Fontni
        // Bashqisi bolsa Local Fontni Belgilydu
        if(gUIsUyghur(Harip[0]))
        {
            fr=m_UEdit.mue_UUYG_ForeColor;
        }
        else if(Harip[0]>0xE020 && Harip[0]<0xE0FF)
        {
            fr=m_UEdit.mue_UUYG_ForeColor; //gAlahide;
            Harip[0]=(Harip[0]-0xE000);
        }
        else
        {
            fr=m_UEdit.mue_UBashqa_ForeColor;
        }
        width=UGetHerpKeng(Harip[0],dc);
        if(Harip[0]==VK_TAB)
        {
            wmemset(Harip,0x0020,UVK_TABSIZE);
            Harip[UVK_TABSIZE]=0x0;
            disCnt=UVK_TABSIZE;
        }
        else
        {
            Harip[1]=0x0;
            disCnt=1;
        }

        if(m_UEdit.mue_RTL)
        {
            x=x-width;
        }

        if(selSt==0x1)
        {
            fr=m_UEdit.mue_UTal_ForeColor;
            outRec.left=x;
            outRec.top=qur*m_UQurIgizligi;
            outRec.bottom=qur*m_UQurIgizligi+m_UQurIgizligi-m_UEdit.mue_QurArlighi;
            outRec.right=x+width;
            FillRect(dc,&outRec,m_UTalReng);
        }
        if(x>=rc.left && x<rc.right)
        {
            SetTextColor(dc,fr);
            TextOutW(dc, x,y,Harip,disCnt);
        }
        if(m_UEdit.mue_RTL==FALSE)
        {
            x=x+width;
        }
        i++;
    }
    delete[] m_UShowLine;
    delete[] m_USelSt;
    if(useBidi&&vIndex!=NULL) delete[] vIndex;
    return strWidth;
}

void UEditWin::USetFocus()
{
    ::SetFocus(m_hWnd);
}

void UEditWin::UOnImeChar(WPARAM wParam, LPARAM lParam)
{
    UINT nChar=(UINT)wParam;

    if(nChar==VK_RETURN)
    {
        UOnReturnKey();
        return;
    }

    if(nChar==VK_BACK )
    {
        UOnBackspaceKey();
        return;
    }

    int selChan=FALSE;
    m_UTextChanged=TRUE;
    wchar_t inBuf[3];
    int     inPos=0;
    wchar_t *esli_Txt=NULL;
    wchar_t *yengi_Txt=NULL;
    BOOL    sel=FALSE;

    if((nChar<0x0020 && nChar!=0x09)||(nChar>=0x0080 && nChar<=0x00A0)) return;

    if(this->UIsTextSelected())
    {
        sel=TRUE;
        esli_Txt=this->UGetSelectionText(FALSE);
        selChan=this->UClearSelection(TRUE);
    }

    int     Index=-1;
    wchar_t PreHerp;

    Index=gUGetUnicodeIndex((wchar_t)nChar);

    if(Index!=-1)
    {
        PreHerp=m_UBuffer.GetAt(m_USelPos-1);
        if(gUIsSozuqTawushUNICODE((wchar_t)nChar))
        {
            // Aldinqi Herp Sozuq tawush bolsa Hemze bilen bashlindighan herpler kelidu
            if(gUGetUnicodeIndex(PreHerp)==-1)
            {
                inBuf[inPos++]=UYG_UN_HM_6;
                inBuf[inPos++]=(wchar_t)nChar;
            }
            //Ikki sozuq tawush bir yerge kelse, keyinkisi chong yezildu
            // Azraq Guman bar,  bu Yerni choqum bir terep qilish kerek
            else if(gUIsSozuqTawushUNICODE(PreHerp))
            {
                inBuf[inPos++]=UYG_UN_HM_6;
                inBuf[inPos++]=(wchar_t)nChar;
            }
            else
            {
                inBuf[inPos++]=(wchar_t)nChar;
            }
        }
        else
        {
            inBuf[inPos++]=(wchar_t)nChar;
        }
    }
    else
    {
        inBuf[inPos++]=(wchar_t)nChar;
    }
    inBuf[inPos]=0x0;

    yengi_Txt=new wchar_t[inPos+1];
    yengi_Txt[0]=0x0;
    wcscpy(yengi_Txt,inBuf);


    wchar_t *oldText;

    if(this->m_Qisturush||sel)
    {
        this->m_UBuffer.Insert(m_USelPos,inBuf);
    }
    else
    {
        oldText=new wchar_t[2];
        oldText[0]=m_UBuffer.GetAt(m_USelPos);
        oldText[1]=0x0;
        esli_Txt=oldText;
        this->m_UBuffer.Put(m_USelPos,inBuf);
    }

    this->UAddUnDO(esli_Txt,yengi_Txt);

    m_HazirqiHerip+=inPos;
    m_USelPos+=inPos;
    m_USelS=m_USelE=m_USelPos;

    if(this->m_UEdit.mue_AutoQatlash==TRUE)
    {
        if(UAutoQatla()==TRUE)
        {
            UInvalidate();
        }
        else
        {
            UOutTextCurLine(m_HazirqiQur,false);
        }
    }
    else if(UKorundighanEkran(UEKRAN_X)==TRUE)
    {
        UInvalidate();
    }
    else
    {
        UOutTextCurLine(m_HazirqiQur,false);
    }
    UShowCaret();
}

void UEditWin::UOnTizishAbzas()
{
    UINT len=0;
    ULONG abBax=m_UBuffer.GetAbzasInfo(m_USelPos,&len); // Abzasning Beshi we Abzastiki herp sanini hesaplaydu
    if(len==0|| m_UBuffer.GetAt(m_USelPos)==QURBELGISI_R)
    {
        return;
    }
    wchar_t *newBuf=new wchar_t[len*2];
    if(newBuf==NULL)
    {
        return ;
    }
    wmemset(newBuf,0x00,len*2);
    RECT rc;
    ::GetClientRect(m_hWnd,&rc);
//	m_BetKeng=rc.right/2;
    wchar_t *abBuf=m_UBuffer.GetAdressFromPos(abBax);
    m_USelPos+=UTengsheshAbzas(abBuf,len,newBuf,rc.right-m_Boshluq,(m_USelPos-abBax));
    wchar_t *oldBuf=m_UBuffer.Delete(abBuf,len);
    this->m_UBuffer.Insert(abBuf,newBuf);
    if(wcscmp(oldBuf,newBuf)!=0)
    {
        m_USelE=m_USelS=m_USelPos;
        m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
        m_VX=0;

        /*	    if(((int)m_HazirqiQur-(int)m_VY)<0){
        		    m_VY=m_HazirqiQur;
        		}else */

        if((m_HazirqiQur-m_VY)>m_BetQurSani)
        {
            m_VY=m_HazirqiQur+1;
        }

        m_UFirstLine=m_UBuffer.GetLine(m_VY);
        this->UInvalidate();
        m_USelPos=abBax;
        wchar_t *tmpBuf=new wchar_t[wcslen(newBuf)+1];
        wcscpy(tmpBuf,newBuf);
        delete[] newBuf;
        this->UAddUnDO(oldBuf,tmpBuf);
        m_USelPos=m_USelE;
    }
    else
    {
        delete[] newBuf;
        delete[] oldBuf;
    }
    UShowCaret();
}

BOOL UEditWin::UAutoQatla()
{
    BOOL ret=FALSE;
    UINT len=0;
    ULONG abBash;
    long  offset;
    wchar_t *qurBeshi=m_UBuffer.GetLineInfo(m_USelPos,&len); // Abzasning Beshi we Abzastiki herp sanini hesaplaydu

    HDC dc=GetDC(m_hWnd);
    UINT qurKeng=this->UGetHeripTizmisiWidth(dc,qurBeshi,len);
    if(qurKeng>m_EngKeng)
    {
        ret=TRUE;
        abBash=m_UBuffer.GetAbzasInfo2(m_USelPos,&len);
        qurBeshi=m_UBuffer.GetAdressFromPos(abBash);
        wchar_t *newBuf=new wchar_t[2*len];
        wmemset(newBuf,0x00,2*len);
        offset=UTengsheshAbzas(qurBeshi,len,newBuf,m_EngKeng-m_Boshluq,(m_USelPos-abBash));
        m_USelPos+=offset;
        wchar_t *oldBuf=m_UBuffer.Delete(qurBeshi,len);
        m_UBuffer.Insert(qurBeshi,newBuf);
        len=wcslen(newBuf)+1;
        wchar_t *tmpBuf=new wchar_t[len];
        wcscpy(tmpBuf,newBuf);
        delete[] newBuf;

        m_USelE=m_USelS=m_USelPos;
        m_USelPos=abBash;
        this->UAddUnDO(oldBuf,tmpBuf);
        m_USelPos=m_USelE;

        m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
        m_VX=0;

        if(m_HazirqiQur>(m_VY+m_BetQurSani))
        {
            m_VY++;
            m_UFirstLine=m_UBuffer.GetLine(m_VY);
        }
    }
    ReleaseDC(m_hWnd,dc);
    return ret;
}

ULONG UEditWin::UTengsheshAbzas(wchar_t *oldBuf,UINT bufLen,wchar_t *newBuf,UINT kenglik,ULONG oldOffset)
{
    UINT x=0;
    ULONG cnt=0;
    int  HeripKeng;
    long newOffset=0;
    wchar_t Herip;
    HDC dc=GetDC(m_hWnd);
    wchar_t *tmpBuf=newBuf;
    wchar_t *tmpQur;
    while(cnt<bufLen)
    {
        Herip=oldBuf[cnt];
        if(Herip==QURBELGISI_Y)
        {
            if(cnt<oldOffset)
            {
                newOffset--;
            }
            cnt++;
            m_JemiQurSani--;
        }
        else
        {
            HeripKeng=UGetHerpKeng(Herip,dc);
            x+=HeripKeng;
            if(x>kenglik)
            {
                tmpQur=m_UBuffer.UQurQatlash(tmpBuf);
                if(cnt<oldOffset)
                {
                    newOffset++;
                }
                x=UGetHeripTizmisiWidth(dc,tmpQur,wcslen(tmpQur))+HeripKeng;
                tmpBuf+=1;
                m_JemiQurSani++;
            }
            *tmpBuf++=Herip;
            cnt++;
        }
    }
    *tmpBuf=0x0;
    ReleaseDC(m_hWnd,dc);
    return newOffset;
}


void UEditWin::UOutTextCurLine(ULONG curQur,bool useBidi)
{
    // Bir qurni yengilap yazidu
    wchar_t *talBeshi=NULL;
    wchar_t *talAyaq=NULL;
    UINT keng;

    // Towendiki uch xil ehwalda hazirqi qur korunmeydu
    if(curQur>this->m_JemiQurSani) return;
    if((long)curQur<0) return;
    if(curQur<m_VY) return;
    if(curQur>m_VY+m_BetQurSani) return;

    int lineLen;
    wchar_t *lineHead;

    if(m_UFirstLine==NULL) return;
    HideCaret(m_hWnd);

    lineHead=m_UBuffer.GetLine(m_UFirstLine,curQur-m_VY);
    if(lineHead==NULL) return;

    lineLen=m_UBuffer.GetLineLen(lineHead);


    if(m_USelE>m_USelS)
    {
        talBeshi=m_UBuffer.GetAdressFromPos(m_USelS);
        talAyaq=m_UBuffer.GetAdressFromPos(m_USelE);
    }
    else
    {
        talBeshi=m_UBuffer.GetAdressFromPos(m_USelE);
        talAyaq=m_UBuffer.GetAdressFromPos(m_USelS);
    }
    RECT qurRC;
    int qur=(curQur-m_VY)*m_UQurIgizligi;

    GetClientRect(m_hWnd,&qurRC);

    qurRC.bottom=m_UQurIgizligi-m_UEdit.mue_QurArlighi;

    HDC dc=GetDC(m_hWnd);
    HDC memDC=CreateCompatibleDC(dc);
    SetMapMode(memDC,MM_TEXT);
    SetBkMode(memDC,TRANSPARENT);

    HBITMAP bitMap=CreateCompatibleBitmap(dc,qurRC.right,qurRC.bottom);
    SelectObject(memDC,bitMap);
    FillRect(memDC,&qurRC,m_UEkranReng);

    keng=UTextOutLine(memDC,0,lineHead,lineLen,talBeshi,talAyaq,useBidi);

    BitBlt(dc,0,qur,qurRC.right,qur+m_UQurIgizligi-m_UEdit.mue_QurArlighi,memDC,0,0,SRCCOPY);

    DeleteObject(bitMap);
    DeleteDC(memDC);
    ReleaseDC(m_hWnd,dc);
    if(keng>m_EngKeng)
    {
        m_EngKeng=keng;
    }
    ShowCaret(m_hWnd);
}

// Bu Yerde bir kunupkidin bir herp kirguzulgende qurning uzunlighu uzirap, mezkun qur
// ekrangah patmay qalidu, bu chaghda horzintal scrollni korsitishke toghra kelidu
// bhu ishni qilish kerek idi?

void UEditWin::UUpdateHorScroll()
{
    UINT lineLen;
    wchar_t *lineHead=m_UBuffer.GetLineInfo(m_USelPos,&lineLen);
    UINT lineWidth=UGetXFromHeripPos(lineHead,lineLen);

    if(lineWidth>m_EngKeng)
    {
        /*		if(m_UEdit.mue_AutoQatlash==TRUE)
        		{
        			UOnTizishAbzas();
        			USetScroll();
        			UInvalidate();
        		}
        		else
        		{*/
        m_EngKeng=lineWidth;
        UInvalidate();
//		}
    }
}

void UEditWin::UOnChar(WPARAM wParam, LPARAM lParam)
{
    UINT nChar=(UINT)wParam;
    BOOL moveLeft=FALSE;

    if(nChar==VK_BACK || nChar==VK_RETURN||nChar==VK_ESCAPE) return;
    if((nChar<0x0020 && nChar!=0x09)||(nChar>=0x0080 && nChar<=0x00A0)) return;

    if(m_UEdit.mue_Kunupka==KUNUPKA_UYGHUR || m_UEdit.mue_Kunupka==KUNUPKA_LATIN|| m_UEdit.mue_Kunupka==KUNUPKA_ALAHIDE)
    {
        if(UIsRTL()==TRUE)
        {
            if(nChar==L'<')
            {
                nChar=L'>';
            }
            else if(nChar==L'>')
            {
                nChar=L'<';
            }
            else if(nChar==L'(')
            {
                nChar=L')';
            }
            else if(nChar==L')')
            {
                nChar=L'(';
            }
            else if(nChar==L'[')
            {
                nChar=L']';
            }
            else if(nChar==L']')
            {
                nChar=L'[';
            }
            else if(nChar==L'{')
            {
                nChar=L'}';
            }
            else if(nChar==L'}')
            {
                nChar=L'{';
            }
        }
        if(nChar==L'\\')
        {
            nChar=UYG_UN_SIZIQ;
        }
        else if(nChar==UYG_UKY_TIKSIZIQ)
        {
            nChar=UYG_UN_KOPCHEKIT;
        }
        else if(nChar==L'`' && m_UEdit.mue_Kunupka!=KUNUPKA_UYGHUR)
        {
            nChar=UYG_UKY_TIKPESH;
        }
        else if(nChar==L'<')
        {
            nChar=UYG_UKY_KICHIK;
            UOnImeChar((WPARAM)nChar,lParam);
            nChar=UYG_UKY_CHONG;
            moveLeft=TRUE;
        }
        else if(nChar==L'>')
        {
            nChar=UYG_UKY_CHONG;
        }
        else if(nChar==L'{')
        {
            nChar=UYG_UKY_SOL_CH_TIRNAQ;
            UOnImeChar((WPARAM)nChar,lParam);
            nChar=UYG_UKY_ONG_CH_TIRNAQ;
            moveLeft=TRUE;
        }
        else if(nChar==L'}')
        {
            nChar=UYG_UKY_ONG_CH_TIRNAQ;
        }
        else if(nChar==UYG_UKY_SOL_K_TIRNAQ)
        {
            UOnImeChar(nChar,lParam);
            nChar=UYG_UKY_ONG_K_TIRNAQ;
            moveLeft=TRUE;
        }
        else if(nChar==UYG_UKY_SOL_O_TIRNAQ)
        {
            UOnImeChar(nChar,lParam);
            nChar=UYG_UKY_ONG_O_TIRNAQ;
            moveLeft=TRUE;
        }
        else if(m_UEdit.mue_Kunupka==KUNUPKA_UYGHUR)
        {
            nChar=g_UKeyboard.UGetKonaUCode(nChar);
            if(nChar==UYG_UN_LA_6)
            {
                UOnImeChar((WPARAM)UYG_UN_L_6,lParam);
                nChar=UYG_UN_A_6;
            }
        }
        else if(m_UEdit.mue_Kunupka==KUNUPKA_ALAHIDE)
        {
            if((nChar>=L'a' && nChar<=L'z')||
                    (nChar>=L'A' && nChar<=L'Z')||
                    (nChar==UYG_UKY_UU_KICHIK) ||
                    (nChar==UYG_UKY_OO_KICHIK)||
                    (nChar==UYG_UKY_EE_KICHIK)||
                    (nChar==UYG_UKY_UU_CHONG)||
                    (nChar==UYG_UKY_OO_CHONG)||
                    (nChar==UYG_UKY_EE_CHONG)||
                    (nChar==UYG_UKY_SOAL)||
                    (nChar==UYG_UKY_PESH)||
                    (nChar==UYG_UKY_CHEKITPESH)
              )
            {
                nChar=nChar+0xE000;
            }
        }
    }
    UOnImeChar((WPARAM)nChar,lParam);
    if(moveLeft==TRUE)
    {
        UOnRightKey();
        m_USelE=m_USelS=m_USelPos;
        UShowCaret();
    }
}

/*
void UEditWin::UOnChar(WPARAM wParam, LPARAM lParam)
{
	UINT nChar=(UINT)wParam;
    BOOL moveLeft=FALSE;

	if(nChar==VK_BACK || nChar==VK_RETURN||nChar==VK_ESCAPE) return;
	if((nChar<0x0020 && nChar!=0x09)||(nChar>=0x0080 && nChar<=0x00A0)) return;

	if(m_UEdit.mue_Kunupka==KUNUPKA_UYGHUR || m_UEdit.mue_Kunupka==KUNUPKA_LATIN|| m_UEdit.mue_Kunupka==KUNUPKA_ALAHIDE)
	{
	    if(nChar==L'\\'){
	        nChar=UYG_UKY_SIZIQ;
	    }
		else if(nChar==UYG_UKY_TIKSIZIQ){
            nChar=UYG_UN_KOPCHEKIT;
		}
        if(m_UEdit.mue_Kunupka==KUNUPKA_LATIN|| m_UEdit.mue_Kunupka==KUNUPKA_ALAHIDE)
        {
            if(nChar==L'`'){
                nChar=UYG_UKY_TIKPESH;
            }
            else if(nChar==L'<'){
                nChar=UYG_UKY_KICHIK;
                UOnImeChar((WPARAM)nChar,lParam);
                nChar=UYG_UKY_CHONG;
                moveLeft=TRUE;
            }
            else if(nChar==L'>'){
                nChar=UYG_UKY_CHONG;
            }
            else if(nChar==L'{'||nChar==L'"'){
                nChar=UYG_UKY_SOL_CH_TIRNAQ;
                UOnImeChar((WPARAM)nChar,lParam);
                nChar=UYG_UKY_ONG_CH_TIRNAQ;
                moveLeft=TRUE;
            }
            else if(nChar==L'}'||nChar==L'\''){
                nChar=UYG_UKY_ONG_CH_TIRNAQ;
            }else if(nChar==UYG_UKY_SOL_K_TIRNAQ){
                UOnImeChar(nChar,lParam);
                nChar=UYG_UKY_ONG_K_TIRNAQ;
                moveLeft=TRUE;
            }else if(nChar==UYG_UKY_SOL_O_TIRNAQ){
                UOnImeChar(nChar,lParam);
                nChar=UYG_UKY_ONG_O_TIRNAQ;
                moveLeft=TRUE;
            }
        }
        else if(m_UEdit.mue_Kunupka==KUNUPKA_UYGHUR)
        {
            if(nChar==L'>'){
                nChar=UYG_UKY_KICHIK;
                UOnImeChar((WPARAM)nChar,lParam);
                nChar=UYG_UKY_CHONG;
                moveLeft=TRUE;
            }
            else if(nChar==L'<'){
                nChar=UYG_UKY_CHONG;
            }
            else if(nChar==L'}'||nChar==L'\"')
            {
                nChar=UYG_UKY_SOL_CH_TIRNAQ;
                UOnImeChar((WPARAM)nChar,lParam);
                nChar=UYG_UKY_ONG_CH_TIRNAQ;
                moveLeft=TRUE;
            }
            else if(nChar==L'{'||nChar==L'\''){
                nChar=UYG_UKY_ONG_CH_TIRNAQ;
            }
            else if(nChar==')'){
                nChar=UYG_UKY_SOL_K_TIRNAQ;
                UOnImeChar(nChar,lParam);
                nChar=UYG_UKY_ONG_K_TIRNAQ;
                moveLeft=TRUE;
            }
            else if(nChar=='(')
            {
                nChar=UYG_UKY_ONG_K_TIRNAQ;
            }
            else if(nChar==']'){
                nChar=UYG_UKY_SOL_O_TIRNAQ;
                UOnImeChar(nChar,lParam);
                nChar=UYG_UKY_ONG_O_TIRNAQ;
                moveLeft=TRUE;
            }
            else if(nChar=='[')
            {
                nChar=UYG_UKY_ONG_O_TIRNAQ;
            }
            else
            {
                nChar=g_UKeyboard.UGetKonaUCode(nChar);
                if(nChar==UYG_UN_LA_6)
                {
                    UOnImeChar((WPARAM)UYG_UN_L_6,lParam);
                    nChar=UYG_UN_A_6;
                }
            }
		}
		else if(m_UEdit.mue_Kunupka==KUNUPKA_ALAHIDE)
		{
			if((nChar>0x0020&&nChar<0x007E)|| (nChar==UYG_UKY_UU_KICHIK) || (nChar==UYG_UKY_OO_KICHIK)|| (nChar==UYG_UKY_EE_KICHIK)|| (nChar==UYG_UKY_UU_CHONG)|| (nChar==UYG_UKY_OO_CHONG)|| (nChar==UYG_UKY_EE_CHONG))
			{
				nChar=nChar+0xE000;
			}
		}
	}
	UOnImeChar((WPARAM)nChar,lParam);
    if(moveLeft==TRUE)
    {
         UOnRightKey();
		 m_USelE=m_USelS=m_USelPos;
		 UShowCaret();
    }
}
*/
void UEditWin::UInvalidate()
{
    InvalidateRect(m_hWnd,NULL,FALSE);
}


unsigned long UEditWin::UGetAsasKod(wchar_t *Buffer,wchar_t *newBuf)
{
    unsigned long rPos=0;
    unsigned long wPos=0;
    wchar_t Herp;
    int Index;

    m_JemiQurSaniZap=0;

    while(Buffer[rPos]!=0x0)
    {
        Herp=Buffer[rPos++];
        if(Herp==QURBELGISI_R)
        {
            if(Buffer[rPos]==QURBELGISI_L)
            {
                rPos++;
            }
            Herp=QURBELGISI_R;
            m_JemiQurSaniZap++;
        }
        else if(Herp==QURBELGISI_L)
        {
            Herp=QURBELGISI_R;
            m_JemiQurSaniZap++;
        }
        else
        {
            Index=gUGetUnicodeIndex(Herp);
            if(Index!=-1)
            {
                if (Index==UYGIN_LA)
                {
                    newBuf[wPos++]=g_Unicode[UYGIN_L].Code[U_6];
                    Herp=g_Unicode[UYGIN_A].Code[U_6];
                }
                else
                {
                    Herp=g_Unicode[Index].Code[U_6];
                }
            }
            else
            {
                switch(Herp)
                {
                case  UYGE_UN_HA_Y:
                case  UYGE_UN_HA_A:
                    newBuf[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_A].Code[U_6];
                    break;
                case  UYGE_UN_HE_Y:
                case  UYGE_UN_HE_A:
                    newBuf[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_E].Code[U_6];
                    break;

                case  UYGE_UN_HO_Y:
                case  UYGE_UN_HO_A:
                    newBuf[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_O].Code[U_6];
                    break;
                case  UYGE_UN_HU_Y:
                case  UYGE_UN_HU_A:
                    newBuf[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_U].Code[U_6];
                    break;
                case  UYGE_UN_HOO_Y:
                case  UYGE_UN_HOO_A:
                    newBuf[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_OO].Code[U_6];
                    break;
                case  UYGE_UN_HUU_Y:
                case  UYGE_UN_HUU_A:
                    newBuf[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_UU].Code[U_6];
                    break;

                case  UYGE_UN_HEE_Y:
                case  UYGE_UN_HEE_A:
                case  UYGE_UN_HEE_B:
                    newBuf[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_EE].Code[U_6];
                    break;
                case  UYGE_UN_HI_Y:
                case  UYGE_UN_HI_A:
                case  UYGE_UN_HI_B:
                    newBuf[wPos++]=g_Unicode[UYGIN_HM].Code[U_6];
                    Herp=g_Unicode[UYGIN_I].Code[U_6];
                    break;
                default:
                    break;
                }
            }
        }
        if(Herp!=0x640)
        {
            newBuf[wPos++]=Herp;
        }
    }
    newBuf[wPos]=0x0;
    return wPos;
}


void UEditWin::UOnSize(WPARAM wParam, LPARAM lParam)
{
    UINT cx = LOWORD(lParam);  // クライアント領域の幅
    UINT cy = HIWORD(lParam); // クライアント領域の高さ
    if(cx==0) return;
    m_BetQurSani=cy/m_UQurIgizligi;
    if(cx>(UINT)(m_Boshluq+20))
    {
        m_BetKeng=cx-m_Boshluq-20;
    }
    else
    {
        m_BetKeng=cx;
    }

    if(	m_UEdit.mue_AutoQatlash)
    {
        this->m_EngKeng=cx;
    }
    else
    {
        if(m_BetQurSani>m_JemiQurSani)
        {
            this->m_VY=0;
            this->m_UFirstLine=m_UBuffer.GetLine(0);
        }
        if(cx>=this->m_EngKeng)
        {
            this->m_VX=0;
        }
    }
    UShowCaret();
#ifdef _DEBUG
    _trace(L"Keldi : keng=%d,igiz=%d\n",cx,cy);
#endif
}

void UEditWin::UYengiHojjet()
{
    m_UFileName[0]=0x0;
    this->m_UBuffer.PutChar((ULONG)0,0x0);
    this->m_HazirqiQur=0;
    this->m_HazirqiHerip=0;
    this->m_USelPos=0;
    this->m_VX=0;
    this->m_VY=0;
    this->m_JemiQurSani=0;
    this->m_UFirstLine=this->m_UBuffer.GetBuffer();
    this->m_UTextChanged=FALSE;
    this->m_UnReDO->clear();

    UInvalidate();
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}

void UEditWin::USetScroll(void)
{
    SCROLLINFO inf;

    inf.cbSize=sizeof(SCROLLINFO);
    inf.nMin=0;
    inf.nMax=m_JemiQurSani;
    inf.nPage=m_BetQurSani;
    inf.nPos=m_VY;
    if(m_JemiQurSani>=m_BetQurSani)
    {
        inf.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
        EnableScrollBar(m_hWnd,SB_VERT,ESB_ENABLE_BOTH);
    }
    else
    {
        inf.fMask=SIF_PAGE|SIF_POS|SIF_RANGE|SIF_DISABLENOSCROLL;

    }
    SetScrollInfo(m_hWnd, SB_VERT,&inf,TRUE);


    inf.cbSize=sizeof(SCROLLINFO);
    inf.nMin=0;
    inf.nMax=m_EngKeng;
    inf.nPage=m_BetKeng;
    inf.nPos=m_VX;

    if((m_EngKeng>(m_BetKeng+2)))
    {
        inf.fMask=SIF_PAGE|SIF_POS|SIF_RANGE;
        EnableScrollBar(m_hWnd,SB_HORZ,ESB_ENABLE_BOTH);
    }
    else
    {
        inf.fMask=SIF_PAGE|SIF_POS|SIF_RANGE|SIF_DISABLENOSCROLL;
    }
    SetScrollInfo(m_hWnd, SB_HORZ,&inf,TRUE);

}

void UEditWin::UOnVScroll(UINT nSBCode,int pos)
{
    UINT lVY=m_VY;
    SCROLLINFO inf;
    switch(nSBCode)
    {
    case SB_TOP:
    case SB_LINEUP:
        m_VY--;
        break;
    case SB_PAGEUP:
        m_VY-=m_BetQurSani;
        break;
    case SB_BOTTOM:
    case SB_LINEDOWN:
        m_VY++;
        break;
    case SB_PAGEDOWN:
        m_VY+=m_BetQurSani;
        break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
        ZeroMemory(&inf, sizeof(inf));
        inf.cbSize = sizeof(inf);
        inf.fMask = SIF_TRACKPOS;
        GetScrollInfo(m_hWnd, SB_VERT, &inf);
        m_VY=inf.nTrackPos;
        break;
    default:
        return;
    }

    if((long)m_VY<0)
    {
        m_VY=0;
    }

    if(m_VY>(m_JemiQurSani-m_BetQurSani+1))
    {
        m_VY=m_JemiQurSani-m_BetQurSani+1;
    }
    if(m_UFirstLine==NULL)
    {
        m_UFirstLine=m_UBuffer.GetLine(m_VY);
    }
    else
    {
        m_UFirstLine=m_UBuffer.GetLine(m_UFirstLine,(m_VY-lVY));
    }
    /*
    	GetScrollInfo(m_hWnd,SB_VERT,&inf);
    	inf.nPos=(int)m_VY;
    	inf.fMask=SIF_POS;
    	SetScrollInfo(m_hWnd,SB_VERT,&inf,TRUE);
    */
    UInvalidate();
    UShowCaret();
    wsprintf(_gmsgBuf,L"Hazirqi bash qur %d ",(m_VY+1));
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_BUFFER_MESSAGE,(LPARAM)FALSE);
}

void UEditWin::UOnHScroll(UINT nSBCode,int pos)
{
    SCROLLINFO inf;
    switch(nSBCode)
    {
    case SB_TOP:
    case SB_LINEUP:
        m_VX++;
        break;
    case SB_PAGEUP:
        m_VX+=m_BetKeng;
        break;
    case SB_BOTTOM:
    case SB_LINEDOWN:
        m_VX--;
        break;
    case SB_PAGEDOWN:
        m_VX-=m_BetKeng;
        break;
    case SB_THUMBPOSITION:
    case SB_THUMBTRACK:
        ZeroMemory(&inf, sizeof(inf));
        inf.cbSize = sizeof(inf);
        inf.fMask = SIF_TRACKPOS;
        GetScrollInfo(m_hWnd, SB_HORZ, &inf);
        m_VX=inf.nTrackPos;
        break;
    default:
        return;
    }
    if((long)m_VX<0) m_VX=0;

    if(m_VX>m_EngKeng)
    {
        m_VX=m_EngKeng;
    }
    /*
    	GetScrollInfo(m_hWnd,SB_HORZ,&inf);
    	inf.nPos=m_VX;
    	inf.fMask=SIF_POS;
    	SetScrollInfo(m_hWnd,SB_HORZ,&inf,TRUE);
    */
    UInvalidate();
    UShowCaret();
}


UINT UEditWin::UGetHeripPosFromX(UINT curLine,int x)
{
    if(x<=0) return 0;

    wchar_t *pcurLine=m_UBuffer.GetLine(this->m_UFirstLine,curLine);
    long lineLen=m_UBuffer.GetLineLen(pcurLine);

    pcurLine=UUlash(pcurLine,lineLen,&lineLen);

    if(pcurLine==NULL) return 0;

    HDC  dc;
    dc=GetDC(m_hWnd);
    int  HeripPos=0;
    int  curKeng=0;
    int   HeripKeng;

    wchar_t Herip=pcurLine[HeripPos];
    int rPos=0;

    while(Herip!=0x0)
    {
        HeripKeng=UGetHerpKeng(Herip,dc);
        if(Herip==UYG_UN_LA_Y||Herip==UYG_UN_LA_A)
        {
            HeripPos++;
        }
        curKeng+=HeripKeng;
        if(curKeng>x)
        {
            curKeng-=x;							// Heripning ustidiki chekilgen arliq
            // yeni heripning qandaq ornigha chekilgen
            if(curKeng<(HeripKeng/2))
                HeripPos++;
            break;
        }
        rPos++;
        HeripPos++;
        Herip=pcurLine[rPos];
    }
    ReleaseDC(m_hWnd,dc);
    delete[] pcurLine;
    return HeripPos;
}



UINT UEditWin::UGetXFromHeripPos(wchar_t *pcurLine, int HeripPos)
{
    int cnt=0;
    int curX=0; //
    if(HeripPos<0)
    {
        return curX;
    }

    long len=0;
    pcurLine=UUlash(pcurLine,m_UBuffer.GetLineLen(pcurLine),&len);

    // Bu Yerde LA ning sanini hesaplaydu
    HDC  dc;
    dc=GetDC(m_hWnd);
    int  HeripKeng;
    wchar_t Herip=pcurLine[cnt];
    while(Herip!=0x0)
    {
        if(cnt==HeripPos)
        {
            break;
        }

        HeripKeng=UGetHerpKeng(Herip,dc);

        if(Herip==UYG_UN_LA_Y||Herip==UYG_UN_LA_A)
        {
            if((cnt+1)==HeripPos)
            {
                curX+=HeripKeng/2;
                break;
            }
            HeripPos--;
        }
        curX+=HeripKeng;
        cnt++;
        Herip=pcurLine[cnt];
    }
    ReleaseDC(m_hWnd,dc);
    delete[] pcurLine;
    return curX;
}


BOOL UEditWin::UIsEmpty(void)
{
    if(m_UBuffer.GetSize()==0) return TRUE;
    return FALSE;
}

int UEditWin::UGetHerpKeng(wchar_t Herp, HDC dc)
{
    int HeripKeng[1];
    HeripKeng[0]=0;

    if(gUIsUyghur(Herp))
    {
        SelectObject(dc,m_UUyghurFont);
    }
    else
    {
        SelectObject(dc,m_ULocalFont);
    }

    if(Herp==VK_TAB)
    {
        GetCharWidth32(dc,0x0020,0x0020,&HeripKeng[0]);
        HeripKeng[0]=UVK_TABSIZE*HeripKeng[0];
    }
    else if(Herp>0xE020 && Herp<0xE0FF)
    {
        Herp=Herp-0xE000;
        GetCharWidth32(dc,Herp,Herp,&HeripKeng[0]);
    }
    else
    {
        GetCharWidth32(dc,Herp,Herp,&HeripKeng[0]);
    }
    return HeripKeng[0];
}


void UEditWin::UOnImeInput(WPARAM wp,LPARAM lp)
{
    UOnChar(wp,lp);
    return;
}



// oldBuf din bashlanghan tekistni tengsheydu
// bir qurdiki heripni <kenglik> ke maslashturup toghirlaydu
// kengliktin exip ketse boshluq bar yedin uzup , keyinki qurgha cushuridu

ULONG UEditWin::UTengshesh(wchar_t *oldBuf,ULONG bufLen,wchar_t *newBuf,ULONG kenglik,ULONG oldOffset)
{
    ULONG x=0;
    ULONG cnt=0;
    int  HeripKeng;
    long newOffset=0;
    wchar_t Herip;
    HDC dc=GetDC(m_hWnd);
    wchar_t *tmpBuf=newBuf;
    wchar_t *tmpQur;

    while(cnt<bufLen)
    {
        Herip=oldBuf[cnt];
        if(Herip==QURBELGISI_R)
        {
            x=0;
            *tmpBuf++=Herip;
            cnt++;
            m_JemiQurSani++;
        }
        else if(Herip==QURBELGISI_Y)
        {
            if(cnt<oldOffset)
            {
                newOffset--;
            }
            cnt++;
        }
        else
        {

            HeripKeng=UGetHerpKeng(Herip,dc);
            x+=HeripKeng;
            if(x>kenglik)
            {
                tmpQur=m_UBuffer.UQurQatlash(tmpBuf);
                if(cnt<oldOffset)
                {
                    newOffset++;
                }
                x=UGetHeripTizmisiWidth(dc,tmpQur,wcslen(tmpQur))+HeripKeng;
                tmpBuf++;
                m_JemiQurSani++;
            }
            *tmpBuf++=Herip;
            cnt++;
        }
    }
    *tmpBuf=0x0;
    ReleaseDC(m_hWnd,dc);
    return newOffset;
}


int UEditWin::UGetHeripTizmisiWidth(HDC dc,wchar_t *buf,UINT len)
{
    int x=0;
    UINT Pos=0;
    wchar_t Herp;
    while(Pos<len)
    {
        Herp=buf[Pos++];
        x+=UGetHerpKeng(Herp,dc);
    }
    return x;
}


void UEditWin::UEndWaitCursor()
{
    m_oldCursor=SetCursor(m_oldCursor);
}

void UEditWin::UBeginWaitCursor()
{
    m_oldCursor=SetCursor(m_oldCursor);
}


void UEditWin::UShowCaret()
{
    POINT pt;
    pt.x=-1;
    pt.y=-1;
    RECT rc;
    long x;
    if(m_HazirqiQur>=m_VY && m_HazirqiQur<(m_VY+m_BetQurSani+1))
    {
        if(m_esliQur!=m_HazirqiQur)
        {
            UOutTextCurLine(m_esliQur,true);
            UOutTextCurLine(m_HazirqiQur,false);
            m_esliQur=m_HazirqiQur;
        }
        // Nur Belgisi Korush dairsi ichide bolsa shunga ornini hesaplaydu
        GetClientRect(m_hWnd,&rc);
        pt.y=(this->m_HazirqiQur-m_VY)*m_UQurIgizligi;
        UINT len;
        wchar_t *curLine=m_UBuffer.GetLineInfo(m_USelPos,&len);
        x=UGetXFromHeripPos(curLine,this->m_HazirqiHerip);
        x-=m_VX;
        if(m_UEdit.mue_RTL)
        {
            pt.x=(rc.right-m_Boshluq)-x-m_NurKeng+1;
        }
        else
        {
            pt.x=m_Boshluq+x;
        }

        // Nur Belgisi Turghan yerdiki heripni alidu
        m_UNotify.Qur=m_HazirqiQur+1;
        m_UNotify.Herp=m_UBuffer.GetAt(m_USelPos);
        m_UNotify.Ston=m_HazirqiHerip+1;
        m_UNotify.Qisturush=m_Qisturush;
        m_UNotify.Kunupka=m_UEdit.mue_Kunupka;
        PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)&m_UNotify,(LPARAM)TRUE);
    }
    SetCaretPos(pt.x,pt.y);
    USetImePos();
    return;
}

void UEditWin::UOnLDoubleClick(int x, int y)
{
    if(m_UFirstLine==NULL) return;
    wchar_t* curPos=this->m_UBuffer.GetAdressFromPos(m_USelPos);
    m_UBuffer.UGetSoz(curPos,&m_USelS,&m_USelE);
    m_USelE=m_USelPos+m_USelE;
    m_USelS=m_USelPos-m_USelS;
    m_USelPos=m_USelE;

    m_UBuffer.GetYXFromPos(m_UFirstLine,m_VY,m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);

    UInvalidate();
    UShowCaret();
}


void UEditWin::UOnLButtonDown(int mx, int my)
{
    if(m_UFirstLine==NULL) return;
    m_UMouseBesildi=TRUE;
    SetCapture(m_hWnd);

    this->m_HazirqiQur=(int)(my/m_UQurIgizligi)+m_VY;
    if(this->m_HazirqiQur>this->m_JemiQurSani)
    {
        this->m_HazirqiQur=this->m_JemiQurSani;
    }
    RECT rc;
    GetClientRect(m_hWnd,&rc);

    UINT x;
    UINT x1;

    if(m_UEdit.mue_RTL)
    {
        x=(rc.right-m_Boshluq-mx)+m_VX;
    }
    else
    {
        x=mx+m_VX-m_Boshluq;
    }

    m_HazirqiHerip=UGetHeripPosFromX(this->m_HazirqiQur-m_VY,x);

    UCalSelPos();
    UINT len;
    x1=this->UGetXFromHeripPos(m_UBuffer.GetLineInfo(m_USelPos,&len),m_HazirqiHerip);
    BOOL    selChange=FALSE;
    if(x1<=x)
    {
        selChange=this->UKorundighanEkran(UEKRAN_X);
    }

    int	keySt=GetKeyState(VK_SHIFT)&0x8000;
    if(keySt!=0)
    {
        this->m_USelE=m_USelPos;
        selChange=TRUE;
    }
    else
    {
        selChange |= this->UClearSelection(FALSE);
    }

    if(selChange)
    {
        this->UInvalidate();
    }
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}

void UEditWin::UOnLButtonUp(int mx,int my)
{
    m_UMouseBesildi=FALSE;
    ::ReleaseCapture();
}

void UEditWin::UOnMouseMove(int mx,int my)
{
    if(m_UMouseBesildi)
    {
        if(m_UFirstLine==NULL) return;
        this->m_HazirqiQur=(int)(my/m_UQurIgizligi)+m_VY;
        if(this->m_HazirqiQur>this->m_JemiQurSani)
        {
            this->m_HazirqiQur=this->m_JemiQurSani;
        }

        RECT rc;
        GetClientRect(m_hWnd,&rc);
        int x;
        if(m_UEdit.mue_RTL)
        {
            x=(rc.right-m_Boshluq-mx)+m_VX;
        }
        else
        {
            x=mx+m_VX-m_Boshluq;
        }

        m_HazirqiHerip=UGetHeripPosFromX(m_HazirqiQur-m_VY,x);
        UCalSelPos();
        m_USelE=m_USelPos;
        UInvalidate();
        UShowCaret();
    }
}

void UEditWin::USetImePos()
{
    POINT pp;
    GetCaretPos(&pp);
    HIMC hIMC = ImmGetContext(m_hWnd);
    COMPOSITIONFORM cf;
    cf.dwStyle = CFS_POINT;
    cf.ptCurrentPos.x = pp.x;
    cf.ptCurrentPos.y = pp.y;
    ImmSetCompositionWindow(hIMC, &cf);
    ImmReleaseContext(m_hWnd,hIMC);
}


BOOL UEditWin::UKorundighanEkran(int Type)
{
    int		perq;
    UINT    len;
    wchar_t	*curLine;

    RECT    rc;
    ULONG		esliVX=m_VX;
    ULONG		esliVY=m_VY;
    BOOL    ret=FALSE;

    if(Type==UEKRAN_Y)
    {
        perq=m_HazirqiQur-m_VY+1;
        if(perq<=0||(UINT)perq>m_BetQurSani)
        {
            if(perq<=0)
            {
                m_VY=m_HazirqiQur;				// Nur belgisi Korunmes ekranning ustide
            }
            else
            {
                m_VY=m_HazirqiQur-m_BetQurSani+4;
            }
            m_UFirstLine=m_UBuffer.GetLine(m_VY);
        }
        if(esliVY!=m_VY) ret=TRUE;
    }
    else if(Type==UEKRAN_X)
    {
        GetClientRect(m_hWnd,&rc);
        curLine=m_UBuffer.GetLineInfo(m_USelPos,&len);
        perq=this->UGetXFromHeripPos(curLine,this->m_HazirqiHerip);
        if((UINT)perq>(rc.right+m_VX-m_Boshluq) || (UINT)perq<m_VX)
        {
            m_VX=perq-this->m_BetKeng;
            if((long)m_VX<0) m_VX=0;
        }
        if(esliVX!=m_VX) ret=TRUE;
    }
    else if(Type==UEKRAN_XY)
    {
        perq=m_HazirqiQur-m_VY+1;
        if(perq<=0||(UINT)perq>m_BetQurSani)
        {
            if(perq<=0)
            {
                m_VY=m_HazirqiQur;				// Nur belgisi Korunmes ekranning ustide
            }
            else
            {
                m_VY=m_HazirqiQur-m_BetQurSani+4;
            }
            m_UFirstLine=m_UBuffer.GetLine(m_VY);
        }
        GetClientRect(m_hWnd,&rc);
        curLine=m_UBuffer.GetLineInfo(m_USelPos,&len);
        perq=this->UGetXFromHeripPos(curLine,this->m_HazirqiHerip);
        if((UINT)perq>(rc.right+m_VX-m_Boshluq) || (UINT)perq<m_VX)
        {
            m_VX=perq-this->m_BetKeng;
            if((long)m_VX<0) m_VX=0;
        }
        if(esliVX!=m_VX||esliVY!=m_VY) ret=TRUE;
    }
    return ret;
}


void UEditWin::UOnDeleteKey()
{
    //Eger Tallanghan yer bosla su yerni ochuridu
    wchar_t *esli_Txt=NULL;
    wchar_t *yengi_Txt=NULL;
    if(UIsTextSelected())
    {
        UChaplaStr(esli_Txt);
    }
    else
    {
        wchar_t Herp=this->m_UBuffer.GetAt(m_USelPos);
        if(Herp!=0x0)
        {
            esli_Txt=m_UBuffer.Delete(m_USelPos,1);

            UCalSelPos();
            m_UBuffer.GetYXFromPos(this->m_UFirstLine,m_VY, m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);

            UAddUnDO(esli_Txt,yengi_Txt);
            m_UTextChanged=TRUE;
            if(Herp==QURBELGISI_R||Herp==QURBELGISI_Y)
            {
                this->m_JemiQurSani--;
                UKorundighanEkran(UEKRAN_XY);
                UInvalidate();
                UShowCaret();
            }
            else
            {
                if(UKorundighanEkran(UEKRAN_X)==TRUE)
                {
                    UInvalidate();
                }
                else
                {
                    UOutTextCurLine(m_HazirqiQur,false);
                }
                UShowCaret();
            }
        }
    }
}

void UEditWin::UOnBackspaceKey()
{
    //Eger Tallanghan yer bosla su yerni ochuridu
    wchar_t *esli_Txt=NULL;
    wchar_t *yengi_Txt=NULL;
    //Eger Tallanghan yer bosla su yerni ochuridu

    if(UIsTextSelected())
    {
        UChaplaStr(esli_Txt);
    }
    else
    {
        if(m_USelPos==0) return;
        m_USelPos--;
        wchar_t Herp=this->m_UBuffer.GetAt(m_USelPos);
        if(Herp!=0x0)
        {
            esli_Txt=m_UBuffer.Delete(m_USelPos,1);
            m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
            UAddUnDO(esli_Txt,yengi_Txt);
            m_UTextChanged=TRUE;
            if(Herp==QURBELGISI_R||Herp==QURBELGISI_Y)
            {
                this->m_JemiQurSani--;
                UKorundighanEkran(UEKRAN_XY);
                UInvalidate();
                UShowCaret();
            }
            else
            {
                if(UKorundighanEkran(UEKRAN_X)==TRUE)
                {
                    UInvalidate();
                }
                else
                {
                    UOutTextCurLine(m_HazirqiQur,false);
                }
                UShowCaret();
            }
        }
    }
}

void UEditWin::UOnHomeKey()
{
    int		keySt;
    this->m_HazirqiHerip=0;
    this->m_VX=0;
    keySt=(short)(GetKeyState(VK_CONTROL)&0x8000);
    if(keySt!=0)
    {
        // Contrl+Home
        this->m_VY=0;
        this->m_USelPos=0;
        this->m_HazirqiQur=0;
        keySt=GetKeyState(VK_SHIFT)&0x8000;
        if(keySt!=0)
        {
            m_USelE=m_USelPos;
        }
        else
        {
            m_USelE=m_USelS=m_USelPos;
        }
        this->m_UFirstLine=m_UBuffer.GetBuffer();
    }
    else
    {
        // Shift + Home
        UCalSelPos();
        keySt=GetKeyState(VK_SHIFT)&0x8000;
        if(keySt!=0)
        {
            m_USelE=m_USelPos;
        }
        else
        {
            m_USelE=m_USelS=m_USelPos;
        }
    }
    UInvalidate();
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}

void UEditWin::UOnEndKey()
{
    wchar_t *curLine;
    int keySt=GetKeyState(VK_CONTROL)&0x8000; //Control Besildimu tekshuridu
    if(keySt==0)// Besilmighan
    {
        // NurBelgisi Turghan qurdiki Jemi Herip Sani Elish
        UINT lineLen=0;
        curLine=m_UBuffer.GetLineInfo(m_USelPos,&lineLen);
        m_HazirqiHerip=lineLen;
        UCalSelPos();
        keySt=GetKeyState(VK_SHIFT)&0x8000;
        if(keySt!=0)
        {
            m_USelE=m_USelPos;
        }
        else
        {
            m_USelE=m_USelS=m_USelPos;
        }
        UKorundighanEkran(UEKRAN_X);
    }
    else
    {
        /*
        		this->m_USelPos=m_UBuffer.GetSize();
        		m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
        		this->m_VY=this->m_HazirqiQur-this->m_BetQurSani+1;
        		if((int)this->m_VY<0) this->m_VY=0;
        		this->m_UFirstLine=m_UBuffer.GetLine(this->m_VY);*/
        m_HazirqiHerip=0;
        m_HazirqiQur=this->m_JemiQurSani;
        UCalSelPos();
        keySt=GetKeyState(VK_SHIFT)&0x8000;
        if(keySt!=0)
        {
            m_USelE=m_USelPos;
        }
        else
        {
            m_USelE=m_USelS=m_USelPos;
        }
        UKorundighanEkran(UEKRAN_X);
    }
    UInvalidate();
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}


void UEditWin::UOnUpKey()
{
    BOOL reDraw=FALSE;
    int shiftKey=GetKeyState(VK_SHIFT)&0x8000;
    if(m_USelE!=m_USelS)
    {
        reDraw=TRUE;
    }
    if(m_HazirqiQur>0)
    {
        m_HazirqiQur--;
    }

    reDraw|=UCalSelPos();

    if(shiftKey!=0)
    {
        m_USelE=m_USelPos;
        reDraw=TRUE;
    }
    else
    {
        m_USelE=m_USelS=m_USelPos;
    }

    reDraw|=UKorundighanEkran(UEKRAN_X);
    if(reDraw==TRUE)
    {
        this->UInvalidate();
    }
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}

void UEditWin::UOnDownKey()
{
    BOOL reDraw=FALSE;
    int shiftKey=GetKeyState(VK_SHIFT)&0x8000;
    if(m_USelE!=m_USelS)
    {
        reDraw=TRUE;
    }
    if(m_HazirqiQur < this->m_JemiQurSani)
    {
        m_HazirqiQur++;
    }

    reDraw|=UCalSelPos();

    if(shiftKey!=0)
    {
        m_USelE=m_USelPos;
        reDraw=TRUE;
    }
    else
    {
        m_USelE=m_USelS=m_USelPos;
    }
    reDraw|=UKorundighanEkran(UEKRAN_X);
    if(reDraw==TRUE)
    {
        this->UInvalidate();
    }
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}

BOOL UEditWin::UCalSelPos(void)
{
    BOOL reDraw=FALSE;
    INT  delta;
    UINT  maxLen;
    if((m_HazirqiQur>=m_VY) && (m_HazirqiQur<(m_VY+m_BetQurSani)))
    {
        m_USelPos=m_UBuffer.GetHerpPosAtYX(m_UFirstLine,m_VY,m_HazirqiQur,m_HazirqiHerip);
    }
    else
    {
        if(m_HazirqiQur<m_VY)
        {
            delta=m_VY-m_HazirqiQur;
            if((UINT)delta>=m_HazirqiQur)
            {
                m_UFirstLine=m_UBuffer.GetLine(m_HazirqiQur);
            }
            else
            {
                m_UFirstLine=m_UBuffer.GetLine(m_UFirstLine,-delta);
            }
            m_VY=m_HazirqiQur;
        }
        else
        {
            delta=m_HazirqiQur-m_VY-m_BetQurSani+1;
            m_UFirstLine=m_UBuffer.GetLine(m_UFirstLine,delta);
            m_VY=m_HazirqiQur-m_BetQurSani+1;
        }
        m_USelPos=m_UBuffer.GetHerpPosAtYX(m_UFirstLine,m_VY,m_HazirqiQur,m_HazirqiHerip);
        reDraw=TRUE;
    }

    //Bixeter bolush uchun Hazirqi Herp ornini qayta hesaplaymiz
    m_UBuffer.GetLineInfo(m_USelPos,&maxLen);
    if(maxLen<m_HazirqiHerip)
    {
        m_HazirqiHerip=maxLen;
    }
    return reDraw;
}


void UEditWin::UOnLeftKey()
{
    BOOL reDraw=FALSE;
    int shiftKey=GetKeyState(VK_SHIFT)&0x8000;
    wchar_t Herp;
    if(m_USelE!=m_USelS)
    {
        reDraw=TRUE;
    }

    if(m_USelPos<m_UBuffer.GetSize())
    {
        Herp=m_UBuffer.GetAt(m_USelPos);
        if(Herp==QURBELGISI_R || Herp==QURBELGISI_Y)
        {
            m_HazirqiQur++;
            m_HazirqiHerip=0;
        }
        else
        {
            m_HazirqiHerip++;
        }
        reDraw|=UCalSelPos();
    }

    if(shiftKey!=0)
    {
        m_USelE=m_USelPos;
        reDraw=TRUE;
    }
    else
    {
        m_USelE=m_USelS=m_USelPos;
    }
    reDraw|=UKorundighanEkran(UEKRAN_XY);
    if(reDraw==TRUE)
    {
        this->UInvalidate();
    }
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}

void UEditWin::UOnRightKey()
{
    BOOL reDraw=FALSE;
    wchar_t Herp;
    int shiftKey=GetKeyState(VK_SHIFT)&0x8000;
    if(m_USelE!=m_USelS)
    {
        reDraw=TRUE;
    }
    if(m_USelPos>0)
    {
        m_USelPos--;
        Herp=m_UBuffer.GetAt(m_USelPos);
        if(Herp==QURBELGISI_R || Herp==QURBELGISI_Y)
        {
            m_HazirqiQur--;
            m_UBuffer.GetLineInfo(m_USelPos,&m_HazirqiHerip);
        }
        else
        {
            m_HazirqiHerip--;
        }
        reDraw|=UCalSelPos();
    }

    if(shiftKey!=0)
    {
        m_USelE=m_USelPos;
        reDraw=TRUE;
    }
    else
    {
        m_USelE=m_USelS=m_USelPos;
    }

    reDraw|=UKorundighanEkran(UEKRAN_XY);
    if(reDraw==TRUE)
    {
        this->UInvalidate();
    }
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}

void UEditWin::UOnReturnKey()
{
    m_UTextChanged=TRUE;
    wchar_t *esli_Txt=NULL;
    if(UIsTextSelected())
    {
        esli_Txt=this->UGetSelectionText();
        UClearSelection(TRUE);
    }
    wchar_t *yengi_Txt=new wchar_t[2];
    yengi_Txt[0]=QURBELGISI_R;
    yengi_Txt[1]=0x0;
    this->UAddUnDO(esli_Txt,yengi_Txt);
    m_UBuffer.Insert(m_USelPos++,QURBELGISI_R);
    m_JemiQurSani++;
    m_HazirqiQur++;
    m_HazirqiHerip=0;
    m_VX=0;
    if(m_HazirqiQur>=(m_VY+m_BetQurSani))
    {
        m_VY++;
        m_UFirstLine=m_UBuffer.GetLine(m_VY);
    }
    UInvalidate();
    UShowCaret();
}

void UEditWin::UOnPageUpKey()
{
    UINT vy=m_VY;
    int keySt=GetKeyState(VK_SHIFT)&0x8000; //Shift Besildimu tekshuridu
    if(m_HazirqiQur==0) return;
    m_VY-=(this->m_BetQurSani-1);
    m_HazirqiQur-=(this->m_BetQurSani-1);
    if((int)m_VY<0)
    {
        m_VY=0;
        m_HazirqiQur=0;
    }

    m_UFirstLine=m_UBuffer.GetLine(m_UFirstLine,m_VY-vy);
    UCalSelPos();

    if(keySt!=0)
    {
        // Shift+PGUP Besilghan bolsa
        m_USelE=m_USelPos;
    }
    else
    {
        m_USelE=m_USelS=m_USelPos;
    }
    UInvalidate();
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}

void UEditWin::UOnPageDownKey()
{
    UINT vy=m_VY;
    if((m_JemiQurSani-m_VY)<m_BetQurSani)
    {
        m_HazirqiQur=m_JemiQurSani;
    }
    else
    {
        m_VY+=(this->m_BetQurSani-1);
        m_HazirqiQur+=(this->m_BetQurSani-1);
        if(m_HazirqiQur>m_JemiQurSani)
        {
            m_HazirqiQur=m_JemiQurSani;
        }
    }

    m_UFirstLine=m_UBuffer.GetLine(m_UFirstLine,m_VY-vy);
    UCalSelPos();

    int keySt=GetKeyState(VK_SHIFT)&0x8000; //Shift Besildimu tekshuridu
    if(keySt!=0)
    {
        // Shift+PGUP Besilghan bolsa
        m_USelE=m_USelPos;
    }
    else
    {
        m_USelE=m_USelS=m_USelPos;
    }
    this->UInvalidate();
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}

BOOL UEditWin::UOnKeyDown(WPARAM wParam, LPARAM lParam)
{
    UINT    nChar=(UINT)wParam;
    if(m_UEdit.mue_RTL==FALSE)
    {
        if(nChar==VK_LEFT)
        {
            nChar=VK_RIGHT;
        }
        else if(nChar==VK_RIGHT)
        {
            nChar=VK_LEFT;
        }
    }

    switch(nChar)
    {
    case VK_DELETE:
        UOnDeleteKey();
        break;
    case VK_BACK:
        UOnBackspaceKey();
        break;
    case VK_HOME:
        UOnHomeKey();
        break;
    case VK_END:
        UOnEndKey();
        break;
    case VK_UP:
        UOnUpKey();
        break;
    case VK_DOWN:
        UOnDownKey();
        break;
    case VK_PRIOR: //PGUP
        UOnPageUpKey();
        break;
    case VK_NEXT: //PGDM
        UOnPageDownKey();
        break;
    case VK_LEFT:
        UOnLeftKey();
        break;
    case VK_RIGHT:
        UOnRightKey();
        break;
    case  VK_INSERT:
        this->m_Qisturush=abs(m_Qisturush-1);
        this->UCreateCaret();
        m_UNotify.Qisturush=m_Qisturush;
        PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)&m_UNotify,(LPARAM)TRUE);
        break;
    case VK_RETURN:
        UOnReturnKey();
        break;
    default:
        return FALSE;
    }
    return TRUE;
}




BOOL UEditWin::UIsTextSelected(void)
{
    if(m_USelS==m_USelE)
    {
        return FALSE;
    }
    else
    {
        return TRUE;
    }
}


// Tallanghan rayondiki Textni Qayturdu
// Eger Remove=TRUE bolsa Yumshaq qayturush belgisini ochurup andin textni qayturdu
wchar_t *UEditWin::UGetSelectionText(BOOL remove)
{
    wchar_t *buffer;
    ULONG beshi=m_USelS;
    ULONG len;
    if(m_USelS>m_USelE)
    {
        beshi=m_USelE;
        len=m_USelS-m_USelE;
    }
    else
    {
        len=m_USelE-m_USelS;
    }
    buffer=new wchar_t[(len+1)*sizeof(wchar_t)];
    wchar_t Herp;
    ULONG rPos=0;
    ULONG wPos=0;
    while(rPos<len)
    {
        Herp=m_UBuffer.GetAt(beshi+rPos);
        if(remove && Herp==QURBELGISI_Y)
        {
            rPos++;
        }
        else
        {
            buffer[wPos++] =Herp;
            rPos++;
        }
    }
    buffer[wPos]=0x0;
    return buffer;
}

BOOL UEditWin::UClearSelection(BOOL Delete)
{
    BOOL   ret=TRUE;
    ULONG  len;
    if(m_USelS==m_USelE)
    {
        ret=FALSE;
        m_USelS=m_USelE=m_USelPos;
    }
    else
    {
        if(Delete)
        {
            if(m_USelS>m_USelE)
            {
                m_USelPos=m_USelE;
                len=m_USelS-m_USelE;
            }
            else
            {
                m_USelPos=m_USelS;
                len=m_USelE-m_USelS;
            }
            wchar_t *tmp=this->m_UBuffer.Delete(m_USelPos,len);
            wchar_t *tmp1=tmp;
            while(*tmp1!=0)
            {
                if(*tmp1==QURBELGISI_R || *tmp1==QURBELGISI_Y)
                {
                    if(m_JemiQurSani>0)
                    {
                        m_JemiQurSani--;
                    }
                }
                tmp1++;
            }
            delete[] tmp;
            this->m_UTextChanged=TRUE;
            ret=TRUE;
            m_USelS=m_USelE=m_USelPos;
            m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
        }
        else
        {
            m_USelS=m_USelE=m_USelPos;
        }
    }
    return ret;
}


void UEditWin::UAddUnDO(wchar_t *_esli, wchar_t *_yengi)
{
    LPDOUNDO  act=new DOUNDO;
    act->esli_Text=_esli;
    act->yengi_Text=_yengi;
    act->m_Pos=this->m_USelPos;
    m_UnReDO->Add(act);
}

void UEditWin::USetRTL(BOOL val)
{
    m_UEdit.mue_RTL=val;
    long exSt=GetWindowLong(this->m_hWnd,GWL_EXSTYLE);
    if(m_UEdit.mue_RTL)
    {
        exSt|=WS_EX_LEFTSCROLLBAR;
    }
    else
    {
        exSt&=~WS_EX_LEFTSCROLLBAR;
    }
    SetWindowLong(this->m_hWnd,GWL_EXSTYLE,exSt);
    UInvalidate();
    UShowCaret();
}


void UEditWin::ULYKunupka(UINT kun)
{
    UINT nCHar=0x0;
    if(m_UEdit.mue_Kunupka!=KUNUPKA_LATIN && m_UEdit.mue_Kunupka!=KUNUPKA_ALAHIDE) return;
    switch(kun)
    {
    case UUKY_HERIP_UU_KICHIK:
        nCHar=UYG_UKY_UU_KICHIK;
        break;
    case UUKY_HERIP_EE_KICHIK:
        nCHar=UYG_UKY_EE_KICHIK;
        break;
    case UUKY_HERIP_OO_KICHIK:
        nCHar=UYG_UKY_OO_KICHIK;
        break;
    case UUKY_HERIP_UU_CHONG:
        nCHar=UYG_UKY_UU_CHONG;
        break;
    case UUKY_HERIP_EE_CHONG:
        nCHar=UYG_UKY_EE_CHONG;
        break;
    case UUKY_HERIP_OO_CHONG:
        nCHar=UYG_UKY_OO_CHONG;
        break;
    default:
        break;
    }
    if(nCHar!=0x0)
    {
        UOnChar((WPARAM)nCHar,0x0);
    }
}

KUNUPKA UEditWin::UGetKunupka()
{
    return m_UEdit.mue_Kunupka;
}

KUNUPKA UEditWin::USetKunupka(KUNUPKA val)
{
    KUNUPKA old=m_UEdit.mue_Kunupka;
    m_UEdit.mue_Kunupka=val;

    if(val==KUNUPKA_ALAHIDE||val==KUNUPKA_LATIN)
    {
    }
    else if(val==KUNUPKA_UYGHUR)
    {
    }
    m_UNotify.Kunupka=m_UEdit.mue_Kunupka;
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)&m_UNotify,(LPARAM)TRUE);
    return old;
}

void UEditWin::UOnRButtonUp(int mx, int my)
{
    if(m_UFirstLine==NULL) return;
    UINT qur=(int)(my/m_UQurIgizligi)+m_VY;
    if(qur>this->m_JemiQurSani)
    {
        qur=this->m_JemiQurSani;
    }
    RECT rc;
    GetClientRect(m_hWnd,&rc);
    UINT x;
    if(m_UEdit.mue_RTL)
    {
        x=(rc.right-m_Boshluq-mx)+m_VX;
    }
    else
    {
        x=mx+m_VX-m_Boshluq;
    }

    UINT herp=UGetHeripPosFromX(qur-m_VY,x);
    ULONG Pos=this->m_UBuffer.GetHerpPosAtYX(m_UFirstLine,m_VY,qur,herp);

    if(gIsClipBoradEmpty())
    {
        EnableMenuItem(m_UPopMenu,TEHRIR_CHAPLASH,MFS_DISABLED|MF_BYCOMMAND);
    }
    else
    {
        EnableMenuItem(m_UPopMenu,TEHRIR_CHAPLASH,MFS_ENABLED|MF_BYCOMMAND);
    }

    BOOL inSel=FALSE;
    if(m_USelE>m_USelS)
    {
        if(Pos>=m_USelS&& Pos<m_USelE)
        {
            inSel=TRUE;
        }
    }
    else
    {
        if(Pos>=m_USelE&& Pos<m_USelS)
        {
            inSel=TRUE;
        }
    }

    if(inSel)
    {
        EnableMenuItem(m_UPopMenu,TEHRIR_KOCHURUSH,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_KOCHURUSH_ALL,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_KESISH,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_OCHURUSH,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALNIUKY,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALNIKONA,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALNISLAWIYAN,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALSLAWIYANUEY,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALNITURK,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALTURKUEY,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALNICHONG,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALNIKICHIK,MFS_ENABLED|MF_BYCOMMAND);
    }
    else
    {
        EnableMenuItem(m_UPopMenu,TEHRIR_KOCHURUSH,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_KOCHURUSH_ALL,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_KESISH,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_OCHURUSH,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALNIUKY,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALNIKONA,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALNISLAWIYAN,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALSLAWIYANUEY,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALNITURK,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALTURKUEY,MFS_DISABLED|MF_BYCOMMAND);

        EnableMenuItem(m_UPopMenu,TEHRIR_TALNICHONG,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(m_UPopMenu,TEHRIR_TALNIKICHIK,MFS_DISABLED|MF_BYCOMMAND);
    }

    POINT point;
    point.x=mx;
    point.y=my;
    ClientToScreen(m_hWnd,&point);
    TrackPopupMenu(m_UPopMenu,TPM_RIGHTALIGN|TPM_TOPALIGN,point.x,point.y,0,m_hWnd,(LPRECT)NULL);
    UShowCaret();
}

void UEditWin::UILangChanged()
{
    wchar_t *mnText;
    mnText=gUGetVal(L"TEHRIR_KOCHURUSH");
    ModifyMenu(m_UPopMenu,TEHRIR_KOCHURUSH,MF_STRING|MF_BYCOMMAND,TEHRIR_KOCHURUSH,mnText);
    mnText=gUGetVal(L"TEHRIR_KOCHURUSH_ALL");
    ModifyMenu(m_UPopMenu,TEHRIR_KOCHURUSH_ALL,MF_STRING|MF_BYCOMMAND,TEHRIR_KOCHURUSH_ALL,mnText);
    mnText=gUGetVal(L"TEHRIR_CHAPLASH");
    ModifyMenu(m_UPopMenu,TEHRIR_CHAPLASH,MF_STRING|MF_BYCOMMAND,TEHRIR_CHAPLASH,mnText);
    mnText=gUGetVal(L"TEHRIR_KESISH");
    ModifyMenu(m_UPopMenu,TEHRIR_KESISH,MF_STRING|MF_BYCOMMAND,TEHRIR_KESISH,mnText);
    mnText=gUGetVal(L"TEHRIR_OCHURUSH");
    ModifyMenu(m_UPopMenu,TEHRIR_OCHURUSH,MF_STRING|MF_BYCOMMAND,TEHRIR_OCHURUSH,mnText);

    mnText=gUGetVal(L"TEHRIR_TALNIUKY");
    ModifyMenu(m_UPopMenu,TEHRIR_TALNIUKY,MF_STRING|MF_BYCOMMAND,TEHRIR_TALNIUKY,mnText);
    mnText=gUGetVal(L"TEHRIR_TALNIKONA");
    ModifyMenu(m_UPopMenu,TEHRIR_TALNIKONA,MF_STRING|MF_BYCOMMAND,TEHRIR_TALNIKONA,mnText);

    mnText=gUGetVal(L"TEHRIR_TALNISLAWIYAN");
    ModifyMenu(m_UPopMenu,TEHRIR_TALNISLAWIYAN,MF_STRING|MF_BYCOMMAND,TEHRIR_TALNISLAWIYAN,mnText);
    mnText=gUGetVal(L"TEHRIR_TALSLAWIYANUEY");
    ModifyMenu(m_UPopMenu,TEHRIR_TALSLAWIYANUEY,MF_STRING|MF_BYCOMMAND,TEHRIR_TALSLAWIYANUEY,mnText);


    mnText=gUGetVal(L"TEHRIR_TALNITURK");
    ModifyMenu(m_UPopMenu,TEHRIR_TALNITURK,MF_STRING|MF_BYCOMMAND,TEHRIR_TALNITURK,mnText);
    mnText=gUGetVal(L"TEHRIR_TALTURKUEY");
    ModifyMenu(m_UPopMenu,TEHRIR_TALTURKUEY,MF_STRING|MF_BYCOMMAND,TEHRIR_TALTURKUEY,mnText);

    mnText=gUGetVal(L"TEHRIR_TALNICHONG");
    ModifyMenu(m_UPopMenu,TEHRIR_TALNICHONG,MF_STRING|MF_BYCOMMAND,TEHRIR_TALNICHONG,mnText);
    mnText=gUGetVal(L"TEHRIR_TALNIKICHIK");
    ModifyMenu(m_UPopMenu,TEHRIR_TALNIKICHIK,MF_STRING|MF_BYCOMMAND,TEHRIR_TALNIKICHIK,mnText);
}

void UEditWin::UOnUndo()
{
    if(m_UnReDO->isUnDoEmpyty()) return;
    LPDOUNDO top=m_UnReDO->getUndo();

    int lenEsli=0,lenYengi=0;
    int delLineCnt=0,addLineCnt=0;

    if(top->esli_Text!=NULL)
    {
        lenEsli=wcslen(top->esli_Text);
        addLineCnt=this->UGetQurSani(top->esli_Text);
    }

    if(top->yengi_Text!=NULL)
    {
        lenYengi=wcslen(top->yengi_Text);
        delLineCnt=this->UGetQurSani(top->yengi_Text);
    }
    m_USelPos=top->m_Pos;
    wchar_t *curPos=this->m_UBuffer.GetAdressFromPos(m_USelPos);
    wchar_t *tmp;
    if(curPos==NULL) return ;

    tmp=this->m_UBuffer.Delete(curPos,lenYengi);
    if(tmp!=NULL) delete[] tmp;
    tmp=this->m_UBuffer.Insert(curPos,top->esli_Text);

    this->m_JemiQurSani-=delLineCnt;
    this->m_JemiQurSani+=addLineCnt;
    m_USelPos=top->m_Pos+lenEsli;
    m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
    UKorundighanEkran(UEKRAN_XY);
    m_USelS=m_USelE=m_USelPos;
    UInvalidate();
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}


void UEditWin::UOnRedo()
{
    if(this->m_UnReDO->isReDoEmpyty()) return;
    LPDOUNDO top=m_UnReDO->getRedo();
    int lenEsli=0,lenYengi=0;

    int delLineCnt=0,addLineCnt=0;

    if(top->esli_Text!=NULL)
    {
        lenEsli=wcslen(top->esli_Text);
        delLineCnt=this->UGetQurSani(top->esli_Text);
    }

    if(top->yengi_Text!=NULL)
    {
        lenYengi=wcslen(top->yengi_Text);
        addLineCnt=this->UGetQurSani(top->yengi_Text);
    }

    m_USelPos=top->m_Pos;
    wchar_t *curPos=this->m_UBuffer.GetAdressFromPos(m_USelPos);
    wchar_t *tmp;
    if(curPos==NULL) return;

    tmp=this->m_UBuffer.Delete(curPos,lenEsli);
    if(tmp!=NULL)delete[] tmp;
    tmp=this->m_UBuffer.Insert(curPos,top->yengi_Text);

    this->m_JemiQurSani-=delLineCnt;
    this->m_JemiQurSani+=addLineCnt;

    m_USelPos=top->m_Pos+lenYengi;
    m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
    UKorundighanEkran(UEKRAN_XY);
    m_USelS=m_USelE=m_USelPos;
    UInvalidate();
    UShowCaret();
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
}

ULONG UEditWin::UGetQurSani(wchar_t* Str)
{
    int y=0;
    wchar_t Herp=*Str;
    while(Herp!=0x0)
    {
        if(Herp==QURBELGISI_R || Herp==QURBELGISI_Y)
        {
            y++;
        }
        Str++;
        Herp=*Str;
    }
    return y;
}

BOOL UEditWin::UCanUndo()
{
    return !m_UnReDO->isUnDoEmpyty();
}
BOOL UEditWin::UCanRedo()
{
    return !this->m_UnReDO->isReDoEmpyty();
}

void UEditWin::UOnMouseWheel(WPARAM wp,LPARAM lp)
{
    short zDelta=(short)HIWORD(wp);
    short line=(short)(zDelta/120);
    if(m_JemiQurSani>m_BetQurSani)
    {
        SCROLLINFO inf;
        UINT lVY=m_VY;
        int inc;
        GetScrollInfo(m_hWnd,SB_VERT,&inf);
        m_VY-=line;
        if((int)m_VY<0)
        {
            m_VY=0;
        }
        if(m_VY>(m_JemiQurSani-m_BetQurSani))
        {
            m_VY=m_JemiQurSani-m_BetQurSani+1;
        }
        if(m_VY!=(UINT)inf.nPos)
        {
            if(m_UFirstLine==NULL)
            {
                m_UFirstLine=m_UBuffer.GetLine(m_VY);
            }
            else
            {
                inc=m_VY-lVY;
                m_UFirstLine=m_UBuffer.GetLine(m_UFirstLine,inc);
            }
            /*
            			inf.nPos=m_VY;
            			inf.fMask=SIF_POS;
            			SetScrollInfo(m_hWnd,SB_VERT,&inf,TRUE);*/
            UInvalidate();
            UShowCaret();
            wsprintf(_gmsgBuf,L"Hazirqi bash qur %d ",(m_VY+1));
            PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_BUFFER_MESSAGE,(LPARAM)FALSE);
        }
    }
}


BOOL UEditWin::UIsFileNameEmpty()
{
    if(m_UFileName[0]==0x0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

wchar_t *UEditWin::UGetFileName()
{
    return m_UFileName;
}

void UEditWin::USetFileName(wchar_t * filenm)
{
    int rPos,wPos;
    rPos=0;
    wPos=0;
    wchar_t Herp=filenm[rPos];
    while(Herp!=0x0)
    {
        Herp=filenm[rPos++];
        if(Herp=='"')continue;
        m_UFileName[wPos++]=Herp;
    }
    m_UFileName[wPos]=0x0;
}

int UEditWin::USaveFileAsHTML(wchar_t *filenm,int CodePage, BOOL baseCode, BOOL bom)
{
    if(filenm==NULL || wcslen(filenm)==0) return -1;
    wchar_t  *newBuf;
    wchar_t  *buf;
    long rPos=0,wPos=0,len=0;
    long lineLen=0;
    wchar_t Herp=0x0;

    buf=this->m_UBuffer.GetBuffer();
    len=wcslen(buf);
    newBuf=new wchar_t[len*2+1280];
    if(newBuf==NULL)
    {
        return -1;
    }
    newBuf[0]=0x0;
    wcscat(newBuf,HEADS0);
    if(UIsRTL()==TRUE)
    {
        wcscat(newBuf,L" dir=\"RTL\"");
    }
    wcscat(newBuf,HEADS1);
    if(CodePage==CP_UTF8)
    {
        wcscat(newBuf,L"UTF-8");
    }
    else
    {
        wcscat(newBuf,L"UTF-16LE");
    }
    wcscat(newBuf,HEADS2);
    while(true)
    {
        lineLen=m_UBuffer.GetLineLen(buf);
        if(lineLen>0) break;
        buf=m_UBuffer.GetNextLine(buf);
        if(buf==NULL) break;
    }

    if(lineLen==0)
    {
        wcscat(newBuf,L"Mawzusiz");
    }
    else
    {
        if(lineLen>255)lineLen=255;
        if(baseCode==TRUE)
        {
            buf=UUlash(buf,lineLen,&lineLen);
            wcscat(newBuf,buf);
            delete[] buf;
        }
        else
        {
            wcsncat(newBuf,buf,lineLen);
        }
    }

    wcscat(newBuf,HEADS3);
    wPos=wcslen(newBuf);

    buf=this->m_UBuffer.GetBuffer();

    if(baseCode==FALSE)
    {
        buf=UUlash(buf,this->m_UBuffer.GetSize(),&len);
    }

    while(buf[rPos]!=0x0)
    {
        Herp=buf[rPos++];
        if(Herp==QURBELGISI_Y)
        {
            continue;
        }
        if(Herp==QURBELGISI_R)
        {
            newBuf[wPos++]=L'<';
            newBuf[wPos++]=L'/';
            newBuf[wPos++]=L'p';
            newBuf[wPos++]=L'>';
            newBuf[wPos++]=QURBELGISI_R;
            newBuf[wPos++]=QURBELGISI_L;
            newBuf[wPos++]=L'<';
            newBuf[wPos++]=L'p';
            newBuf[wPos++]=L'>';
            continue;
        }
        newBuf[wPos++]=Herp;
    }

    if(baseCode==FALSE) delete[] buf;

    newBuf[wPos]=0x0;
    wcscat(newBuf,L"</p>\n</body>\n</html>\n");
    len=wPos+18;

    unsigned char flgBuf[4];
    int flglen=0;
    char *SaveBuf=NULL;
    if(CodePage==CP_UTF8)
    {
        flglen=3;
        flgBuf[0]=0xEF;
        flgBuf[1]=0xBB;
        flgBuf[2]=0xBF;
        len=WideCharToMultiByte(CP_UTF8,0,newBuf,-1,NULL,0,NULL,NULL);
        char *utf8Buf=new char[len];
        if(utf8Buf!=NULL)
        {
            len=WideCharToMultiByte(CP_UTF8,0,newBuf,-1,utf8Buf,len,NULL,NULL);
            delete[] newBuf;
            if(len==0)
            {
                delete[] utf8Buf;
                SaveBuf=NULL;
            }
            else
            {
                SaveBuf=utf8Buf;
                len=strlen(SaveBuf);
            }
        }
        else
        {
            delete[] newBuf;
        }
    }
    else
    {
        flgBuf[0]=0xFF;
        flgBuf[1]=0xFE;
        flgBuf[2]=0x0;
        flglen=2;
        len=len*2;
        SaveBuf=(char*)newBuf;
    }

    if(SaveBuf==NULL) return -1;

    FILE *fp=_wfopen(filenm,L"wb");
    if(fp==NULL) return -1;
    if(bom==TRUE)
    {
        fwrite(flgBuf,1,flglen,fp);
    }
    fwrite(SaveBuf,1,len,fp);
    fclose(fp);
    delete[] SaveBuf;
    return 0;
}

int UEditWin::USaveFile()
{
    wchar_t  *buf;
    if(UIsFileNameEmpty()==TRUE) return -1;
    buf=this->m_UBuffer.GetBuffer();

    long len=0;
    if(m_BaseCode==FALSE)
    {
        buf=UUlash(buf,this->m_UBuffer.GetSize(),&len);
    }

    unsigned char flgBuf[7];
    int           flglen=0;
    FILE *fp=_wfopen(m_UFileName,L"wb");
    if(fp==NULL) return -1;
    if(m_BOM==TRUE)
    {
        if(m_SaveCodePage==CP_UTF8)
        {

            flglen=3;
            flgBuf[0]=0xEF;
            flgBuf[1]=0xBB;
            flgBuf[2]=0xBF;
        }
        else
        {
            flgBuf[0]=0xFF;
            flgBuf[1]=0xFE;
            flgBuf[2]=0x0;
            flglen=2;
        }
        fwrite(flgBuf,1,flglen,fp);
    }

    long rPos=0;
    wchar_t Herp;
    if(m_SaveCodePage==CP_UTF8)
    {
        while(buf[rPos]!=0x0)
        {
            Herp=buf[rPos++];
            if(Herp!=QURBELGISI_Y)
            {
                flglen=gwctoutf8(flgBuf,Herp);
                fwrite(flgBuf,1,flglen,fp);
                if(Herp==QURBELGISI_R)
                {
                    flglen=gwctoutf8(flgBuf,QURBELGISI_L);
                    fwrite(flgBuf,1,flglen,fp);
                }
            }
        }
    }
    else
    {
        while(buf[rPos]!=0x0)
        {
            Herp=buf[rPos];
            if(Herp!=QURBELGISI_Y)
            {
                flgBuf[0]=(unsigned char)Herp;
                flgBuf[1]=(unsigned char)(Herp>>8);
                fwrite(flgBuf,1,2,fp);
                if(Herp==QURBELGISI_R)
                {
                    flgBuf[0]=(unsigned char)QURBELGISI_L;
                    flgBuf[1]=(unsigned char)(QURBELGISI_L>>8);
                    fwrite(flgBuf,1,2,fp);
                }
            }
            rPos++;
        }
    }
    fclose(fp);
    if(m_BaseCode==FALSE)delete[] buf;

    this->m_UTextChanged=FALSE;
    return 0;
}

/*
int UEditWin::USaveFile()
{
	wchar_t  *newBuf;
	wchar_t  *buf;
	if(UIsFileNameEmpty()==TRUE) return -1;
	buf=this->m_UBuffer.GetBuffer();

	long len=0;
	if(m_BaseCode==FALSE)
	{
		buf=UUlash(buf,this->m_UBuffer.GetSize(),&len);
	}
	else
	{
		len=wcslen(buf);
	}

	newBuf=new wchar_t[len*2+1024];
	if(newBuf==NULL)
	{
		return -1;
	}

	long rPos=0,wPos=0;
	wchar_t Herp;
	while(buf[rPos]!=0x0)
	{
		Herp=buf[rPos++];
		if(Herp==QURBELGISI_Y)
		{
			continue;
		}
		newBuf[wPos++]=Herp;
		if(Herp==QURBELGISI_R)
		{
			newBuf[wPos++]=QURBELGISI_L;
		}
	}
	newBuf[wPos]=0x0;
	len=wPos;

	if(m_BaseCode==FALSE)delete[] buf;

	unsigned char flgBuf[4];
	int flglen=0;
	char *SaveBuf=NULL;
	if(m_SaveCodePage==CP_UTF8)
	{
		flglen=3;
		flgBuf[0]=0xEF;
		flgBuf[1]=0xBB;
		flgBuf[2]=0xBF;
		len=WideCharToMultiByte(CP_UTF8,0,newBuf,-1,NULL,0,NULL,NULL);
		char *utf8Buf=new char[len];
		if(utf8Buf!=NULL)
		{
			len=WideCharToMultiByte(CP_UTF8,0,newBuf,-1,utf8Buf,len,NULL,NULL);
			delete[] newBuf;
			if(len==0)
			{
				delete[] utf8Buf;
				SaveBuf=NULL;
			}
			else
			{
				SaveBuf=utf8Buf;
				len=strlen(SaveBuf);
			}
		}
		else
		{
			delete[] newBuf;
		}
	}
	else
	{
		flgBuf[0]=0xFF;
		flgBuf[1]=0xFE;
		flgBuf[2]=0x0;
		flglen=2;
		len=len*2;
		SaveBuf=(char*)newBuf;
	}

	if(SaveBuf==NULL) return -1;

	FILE *fp=_wfopen(m_UFileName,L"wb");
	if(fp==NULL) return -1;
	if(m_BOM==TRUE)
	{
		fwrite(flgBuf,1,flglen,fp);
	}
	fwrite(SaveBuf,1,len,fp);
	fclose(fp);
	delete[] SaveBuf;
	this->m_UTextChanged=FALSE;
	return 0;
}
*/

void UEditWin::USetSaveCodePage(int codePage)
{
    m_SaveCodePage=codePage;
    if(m_SaveCodePage!=CP_UTF16LE && m_SaveCodePage!=CP_UTF8)
    {
        m_SaveCodePage=CP_UTF8;
    }
}

void UEditWin::USetSaveBaseCode(BOOL baseCode)
{
    m_BaseCode=baseCode;
}

void UEditWin::USetSaveBOM(BOOL bom)
{
    m_BOM=bom;
}

BOOL UEditWin::UGetSaveBOM()
{
    return m_BOM;
}

void UEditWin::UReadFromCodePage(int codePage)
{
    m_BaseCode=TRUE;
    m_BOM=FALSE;
    this->m_UTextChanged=FALSE;
    bool  auto_det=false;
    m_SaveCodePage=CP_UTF8;
    FILE *fp=_wfopen(m_UFileName,L"rb");
    if(fp==NULL)
    {
        m_UFileName[0]=0x0;
        UYengiHojjet();
        return;
    }
    this->m_UnReDO->clear();
    ULONG len=(ULONG)filelength(_fileno(fp));
    unsigned char  *Buf=new unsigned char[len+2];
    unsigned char  *stBuf=Buf;
    fread(Buf,1,len,fp);
    fclose(fp);
    Buf[len]=0x0;
    Buf[len+1]=0x0;
    wchar_t *wBuf;
    if(codePage==0||codePage==CP_ACP)
    {
        if((unsigned char)Buf[0]==0xFF && (unsigned char)Buf[1]==0xFE)
        {
            m_BOM=TRUE;
            m_SaveCodePage=CP_UTF16LE;
            codePage=CP_UTF16LE;
            stBuf=Buf+2;
        }
        // Big Endian
        else if((unsigned char)Buf[0]==0xFE && (unsigned char)Buf[1]==0xFF)
        {
            m_BOM=TRUE;
            m_SaveCodePage=CP_UTF16LE;
            codePage=CP_UTF16BE;
            stBuf=Buf+2;
        }
        // UTF-8 Bolup Qalsa Uni Oquydu
        else if((unsigned char)Buf[0]==0xEF && (unsigned char)Buf[1]==0xBB &&(unsigned char)Buf[2]==0xBF)
        {
            m_BOM=TRUE;
            this->m_SaveCodePage=CP_UTF8;
            codePage=CP_UTF8;
            stBuf=Buf+3;
        }
        else if(gUIsUTF8_16(Buf,(len>1048575?1048575:len)))
        {
            this->m_SaveCodePage=CP_UTF8;
            codePage=CP_UTF8;
            stBuf=Buf;
        }
        else
        {
            codePage=gUAutoDetectBOGHDAWEI(Buf,len);
            this->m_SaveCodePage=CP_UTF8;
            if(codePage!=CP_ACP)
            {
                wcscat(m_UFileName,L".uut");
                auto_det=true;
            }
            stBuf=Buf;
        }
    }
    CUyghurcheKodAlmashturush uka;
    if (codePage==CP_BOGHDA)
    {
        wBuf=new wchar_t[len*2];
        if(wBuf==NULL)
        {
            m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_MEM"),MB_OK);
            return;
        }
        uka.UBgdToUyghur((unsigned char*)stBuf,wBuf);
        delete [] Buf;
        USetText(wBuf);
        delete[] wBuf;
        this->m_SaveCodePage=CP_UTF8;
        if(auto_det)
        {
            PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)CP_BOGHDA,(LPARAM)FALSE);
        }
    }
    else if(codePage==CP_WEIDOS)
    {
        wBuf=new wchar_t[len*2];
        if(wBuf==NULL)
        {
            m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_MEM"),MB_OK);
            return;
        }
        uka.UWeiDosToUyghur((unsigned char*)stBuf,wBuf);
        delete [] Buf;
        USetText(wBuf);
        delete[] wBuf;
        this->m_SaveCodePage=CP_UTF8;
        if(auto_det)
        {
            PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)CP_WEIDOS,(LPARAM)FALSE);
        }
    }
    else if(codePage==CP_WEIWIN)
    {
        wBuf=new wchar_t[len*2];
        if(wBuf==NULL)
        {
            m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_MEM"),MB_OK);
            return;
        }
        uka.UWeiWinToUyghur((unsigned char*)stBuf,wBuf);
        delete [] Buf;
        USetText(wBuf);
        delete[] wBuf;
        this->m_SaveCodePage=CP_UTF8;
        if(auto_det)
        {
            PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)CP_WEIWIN,(LPARAM)FALSE);
        }
    }
    else if(codePage==CP_UTF16LE)
    {
        this->m_SaveCodePage=CP_UTF16LE;
        if(len>m_UBuffer.UGetCapacity())
        {
            m_UBuffer.UResizeBuffer(len);
            if(m_UBuffer.UGetCapacity()<len)
            {
                delete [] Buf;
                m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_MEM"),MB_OK);
                return;
            }
        }
        USetText((wchar_t*)stBuf);
        delete [] Buf;
        PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)CP_UTF16LE,(LPARAM)FALSE);
    }
    else if (codePage==CP_UTF16BE)
    {
        m_SaveCodePage=CP_UTF16LE;
        unsigned char Hi,Lo;
        ULONG i=0;
        while(i<len)
        {
            Hi=stBuf[i];
            Lo=stBuf[i+1];
            stBuf[i]=Lo;
            stBuf[i+1]=Hi;
            i+=2;
        }
        if(len>m_UBuffer.UGetCapacity())
        {
            m_UBuffer.UResizeBuffer(len);
            if(m_UBuffer.UGetCapacity()<len)
            {
                delete [] Buf;
                m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_MEM"),MB_OK);
                return;
            }
        }
        USetText((wchar_t*)stBuf);
        delete [] Buf;
        PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)CP_UTF16LE,(LPARAM)FALSE);
    }
    /*	else if(codePage==CP_UTF8)
    	{
    		if(len>m_UBuffer.UGetCapacity())
    		{
    			m_UBuffer.UResizeBuffer(len/2);
    			if(m_UBuffer.UGetCapacity()<(len/2))
    			{
    				delete [] Buf;
    				m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_MEM"),MB_OK);
    				return;
    			}
    		}
    		wBuf=m_UBuffer.GetBuffer();
    		wchar_t Herp;
    		int     offset=0;
    		ULONG   wLen=0;
    		while(*stBuf!=0x00)
    		{
    			offset=gutf8towc(stBuf,&Herp);
    			wBuf[wLen++]=Herp;
    			stBuf+=offset;
    		}
    		wBuf[wLen]=0x0;
    		delete [] Buf;
    		wBuf=new wchar_t[wLen+1];
    		if(wBuf==NULL)
    		{
    			wLen=0;
    			m_UBuffer.PutChar(wLen,0x0);
    			m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_MEM"),MB_OK);
    			return;
    		}
    		wmemmove(wBuf,m_UBuffer.GetBuffer(),wLen+1);

    		USetText(wBuf);
    		delete[] wBuf;
    		PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)codePage,(LPARAM)FALSE);
    	}*/
    else
    {
        if(len>m_UBuffer.UGetCapacity())
        {
            m_UBuffer.UResizeBuffer(len);
            if(m_UBuffer.UGetCapacity()<len)
            {
                delete [] Buf;
                m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_MEM"),MB_OK);
                return;
            }
        }
        wBuf=m_UBuffer.GetBuffer();
        ULONG wLen=MultiByteToWideChar(codePage,0,(char *)stBuf,len,wBuf,m_UBuffer.UGetCapacity());
        wBuf[wLen]=0x0;
        delete [] Buf;
        wBuf=new wchar_t[wLen+1];
        if(wBuf==NULL)
        {
            wLen=0;
            m_UBuffer.PutChar(wLen,0x0);
            m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_MEM"),MB_OK);
            return;
        }
        wmemmove(wBuf,m_UBuffer.GetBuffer(),wLen+1);
        USetText(wBuf);
        delete[] wBuf;
        PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)codePage,(LPARAM)FALSE);
    }
    return;
}


void UEditWin::UOnKochurush()
{
    if(this->UIsTextSelected())
    {
        this->USetToClipboard();
    }
}

void UEditWin::USetToClipboard(void)
{
    wchar_t *esliText=UGetSelectionText(TRUE);
    gSetToClipboard(esliText);
    delete[] esliText;
}

BOOL UEditWin::UBuyruq(WPARAM wParam,LPARAM lParam)
{
    UINT buy=wParam;
    BOOL ret=TRUE;
    switch(buy)
    {
    case HOJJET_YENGI:
        UYengiHojjet();
        break;
    case HOJJET_BESISH:
        UOnBesish(lParam);
        break;
    case BASHQA_SOLDINONG:
    {
        BOOL val=(BOOL)lParam;
        USetRTL(val);
    }
    break;
    case TEHRIR_HEM_TAL:
        this->m_USelS=m_USelE=0;
        if(m_UBuffer.GetSize()>0)
        {
            this->m_USelE=m_UBuffer.GetSize();
            this->UInvalidate();
            UShowCaret();
        }
        break;
    case TEHRIR_HOJJETBESHI:
        this->m_VX=0;
        this->m_VY=0;
        this->m_USelPos=0;
        m_HazirqiQur=0;
        m_HazirqiHerip=0;
        m_USelE=m_USelS=m_USelPos;
        this->m_UFirstLine=m_UBuffer.GetBuffer();
        this->UInvalidate();
        PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
        break;
    case TEHRIR_HOJJETAHIRI:
        m_HazirqiHerip=0;
        m_HazirqiQur=m_JemiQurSani;
        UCalSelPos();
        m_USelE=m_USelS=m_USelPos;
        UKorundighanEkran(UEKRAN_XY);
        this->UInvalidate();
        PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_ATHOR,(LPARAM)FALSE);
        break;
    case TEHRIR_YENIWELISH:
        UOnUndo();
        break;
    case TEHRIR_QILISH:
        UOnRedo();
        break;
    case TEHRIR_KOCHURUSH:
        UOnKochurush();
        break;
    case TEHRIR_CHAPLASH:
        UOnChaplash();
        break;
    case TEHRIR_KESISH:
        UOnKesish();
        break;
    case TEHRIR_OCHURUSH:
        UOnOchurush();
        break;
    case TEHRIR_TALNIUKY:
        UOnToUyghurLatin();
        break;
    case TEHRIR_TALNIKONA:
        UOnToUyghurArabic();
        break;
    case TEHRIR_TALNISLAWIYAN:
        UOnToUyghurSlawiyan();
        break;
    case TEHRIR_TALSLAWIYANUEY:
        UOnSlawiyanToUyghurArabic();
        break;
    case TEHRIR_TALNITURK:
        UOnToTurk();
        break;
    case TEHRIR_TALTURKUEY:
        UOnTurkToUyghurArabic();
        break;
    case TEHRIR_TALNICHONG:
        UOnToChong();
        break;
    case TEHRIR_TALNIKICHIK:
        UOnToKichik();
        break;
    case TEHRIR_KOCHURUSH_ALL:
        UOnKochurushAll();
        break;
    case TEHRIR_BCHAPLASH_UYGHURSOFT:
    case TEHRIR_BCHAPLASH_ILIKYURT:
    case TEHRIR_BCHAPLASH_UIGHUR_NOTEPAD:
    case TEHRIR_BCHAPLASH_DULDUL:
    case TEHRIR_BCHAPLASH_BASHQILAR:
        UOnChaplashBashqa(buy);
        break;
    case BASHQA_KUNUPKA:
        USetKunupka((KUNUPKA)lParam);
        break;
    case BASHQA_TIZISHHEMME:
        UBeginWaitCursor();
        UOnTizishHemme();
        this->UInvalidate();
        UShowCaret();
        UEndWaitCursor();
        break;
    case BASHQA_TIZISHABZAS:
        UBeginWaitCursor();
        UOnTizishAbzas();
        UEndWaitCursor();
        break;
    case BASHQA_UKYGEAYLAN:
        UBeginWaitCursor();
        UOnToULY();
        UEndWaitCursor();
        break;
    case BASHQA_KONAGHAAYLAN_TXT:
        UBeginWaitCursor();
        UOnToUEY_TXT();
        UEndWaitCursor();
        break;
    case BASHQA_KONAGHAAYLAN_PRG:
        UOnToUEY_PRG();
        break;
    case BASHQA_KONAGHAAYLAN_INF:
        UOnToUEY_INF();
        break;

//		case BASHQA_UYGHUR2SLAWIYAN:
//			UBeginWaitCursor();
//			UOnUyghurToSlawiyan();
//			UEndWaitCursor();
//			break;
//		case BASHQA_SLAWIYAN2UYGHUR:
//			UBeginWaitCursor();
//			UOnSlawiyanToUyghur();
//			UEndWaitCursor();
//			break;
//		case BASHQA_UYGHUR2TURK:
//			UBeginWaitCursor();
//			UOnUyghurToTurk();
//			UEndWaitCursor();
//			break;
//		case BASHQA_TURK2UYGHUR:
//			UBeginWaitCursor();
//			UOnTurkToUyghur();
//			UEndWaitCursor();
//			break;

    case BASHQA_XETNUSXISI:
        UBeginWaitCursor();
        UOnSetFont();
        UEndWaitCursor();
        break;
    case BASHQA_IMLA:
        if(UInitImla==NULL||ULoadDictionary==NULL||UIsCorrect==NULL||UCheckWord==NULL||UUnLoadDictionary==NULL||UGetCandidateWord==NULL||UGetOrgWord==NULL)
        {
        }
        else
        {
            UInitImla(m_hWnd,UM_IMLA,mhInstance);
            USetUILang(m_UEdit.mue_Lang);
            ULoadDictionary();
            m_Alahide=UAlahideKodBarmu();
            UOnImlaTekshur((WPARAM)NULL,(LPARAM)U_START);
        }
        break;
    case USERMSG_APTOMATIC_TOGHRILA:  //F1
        UBeginWaitCursor();
        {
//			    USozgeParchila(true);
            m_Alahide=UAlahideKodBarmu();
            UAptomatikToghrila();
        }
        UEndWaitCursor();
        break;
    case USERMSG_SOZGEPARCHILASH: //F10
        UBeginWaitCursor();
        USozgeParchila(false);
        UEndWaitCursor();
        break;
    case USERMSG_SOZGEPARCHILASH_YOQ: //F11
        UBeginWaitCursor();
        USozgeParchila_Tekshurme();
        UEndWaitCursor();
        break;
    case USERMSG_ABZASQA_PARCHILASH: //
        UBeginWaitCursor();
        UAbsazni_Sort();
        UEndWaitCursor();
        break;
    case TEHRIR_IZDESH:
        UOnIzdesh();
        break;
    case TEHRIR_IZDESH_DAWAMLASHTURUSH:
        UOnIzdeshDawam();
        break;
    case KOCHUR_ALA2UYGHUR:
        Alhide2Uyghurwekochur();
        break;
    case BASHQA_UBUNTU:
//            UAtalghularniTap();
        UDelEnter(); //tallanghan rayondiki qattiq qur ayrish belgisini yumshaq qur ayrish belgisige ayladuruidu
        break;
    case BASHQA_UEY:
    case BASHQA_ULY:
    case BASHQA_USY:
    case BASHQA_OTY:
    case BASHQA_UMY:
        UGeAylandur(buy, NODETC);
        break;
    case BASHQA_UYGHUR2LATIN:
        UGeAylandur(BASHQA_ULY, UEY);
        break;
    case BASHQA_UYGHUR2SLAWIYAN:
        UGeAylandur(BASHQA_USY, UEY);
        break;
    case BASHQA_UYGHUR2MEWHUM:
        UGeAylandur(BASHQA_UMY, UEY);
        break;

    case BASHQA_LATIN2UYGHUR:
        UGeAylandur(BASHQA_UEY, ULY);
        break;
    case BASHQA_LATIN2SLAWIYAN:
        UGeAylandur(BASHQA_USY, ULY);
        break;
    case BASHQA_LATIN2MEWHUM:
        UGeAylandur(BASHQA_UMY, ULY);
        break;

    case BASHQA_SLAWIYAN2UYGHUR:
        UGeAylandur(BASHQA_USY, USY);
        break;
    case BASHQA_SLAWIYAN2LATIN:
        UGeAylandur(BASHQA_ULY, USY);
        break;
    case BASHQA_SLAWIYAN2MEWHUM:
        UGeAylandur(BASHQA_UMY, USY);
        break;
    case BASHQA_MEWHUM2UYGHUR:
        UGeAylandur(BASHQA_UEY, UMY);
        break;
    case BASHQA_MEWHUM2LATIN:
        UGeAylandur(BASHQA_ULY, UMY);
        break;
    case BASHQA_MEWHUM2SLAWIYAN:
        UGeAylandur(BASHQA_USY, UMY);
        break;
    default:
        ret=FALSE;
        break;
    }
    UShowCaret();
    return ret;
}

void UEditWin::UOnSetFont()
{
    USetFont setFont(&m_UEdit);
    INT_PTR ret=setFont.UShowModal(mhInstance,m_hWnd);
    if(ret==SETFONT_TAMAM)
    {
        setFont.UGetSettings(&m_UEdit);
        UCreateFont();
        RECT rc;
        GetClientRect(m_hWnd,&rc);
        m_BetQurSani=rc.bottom/m_UQurIgizligi;
//		m_BetKeng=rc.right/2;
        m_JemiQurSani=m_UBuffer.UGetJemiyQurSani();
        UInvalidate();
        UShowCaret();
    }
}

void UEditWin::UOnChaplash()
{
    wchar_t* clipData=gGetFromClipboard();
    if(clipData!=NULL)
    {
        long rPos=0,wPos=0;
        wchar_t Herp,AldinqiHerp=0x0;
        int Index;
        wchar_t *tmp=new wchar_t[wcslen(clipData)*2+1];
        while(clipData[rPos]!=0x0)
        {
            Herp=clipData[rPos++];
            Index=gUGetUnicodeIndex(Herp);
            if(Index!=-1)
            {
                if (Index==UYGIN_LA)
                {
                    tmp[wPos++]=g_Unicode[UYGIN_L].Code[U_6];
                    Herp=g_Unicode[UYGIN_A].Code[U_6];
                    AldinqiHerp=g_Unicode[UYGIN_L].Code[U_6];
                }
                else
                {
                    Herp=g_Unicode[Index].Code[U_6];
                }
            }
            if(Herp!=0x0640)
            {
                tmp[wPos++]=Herp;
                AldinqiHerp=Herp;
            }
            else
            {
                Herp=Herp;
            }
        }
        tmp[wPos]=0x0;
        rPos=0;
        this->UChaplaStr(tmp);
        delete[] clipData;
        delete[] tmp;
    }
}

void UEditWin::UChaplaStr(wchar_t *clipData)
{
    wchar_t  *esli_Txt=NULL;
    wchar_t  *yengi_Txt=NULL;

    UCalSelPos();
//    int	esliQurSani=this->m_JemiQurSani;
    BOOL selCh=FALSE;
    if(this->UIsTextSelected())
    {
        esli_Txt=this->UGetSelectionText();
        selCh=this->UClearSelection(TRUE);
    }
    long  len=0;
    if(clipData!=NULL)
    {
        int y;
        len=wcslen(clipData);
        yengi_Txt=new wchar_t[len+1];
        wmemcpy(yengi_Txt,clipData,len+1);
        y=this->UGetQurSani(clipData);
        this->m_JemiQurSani+=y;
        this->m_UBuffer.Insert(m_USelPos,clipData);
    }

    this->UAddUnDO(esli_Txt,yengi_Txt);
    m_USelPos+=len;
    m_USelS=m_USelE=m_USelPos;
    m_UBuffer.GetYXFromPos(this->m_UFirstLine,m_VY,m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);

//    BOOL EKRAN=this->UKorundighanEkran(UEKRAN_XY);
    this->UKorundighanEkran(UEKRAN_XY);
    this->UInvalidate();
    this->UShowCaret();
    m_UTextChanged=TRUE;
}

void UEditWin::UOnKesish()
{
    if(this->UIsTextSelected())
    {
        wchar_t  *yengi_Txt=NULL;
        this->USetToClipboard();
        UChaplaStr(yengi_Txt);
    }
}

void UEditWin::UOnOchurush()
{
    if(this->UIsTextSelected())
    {
        wchar_t  *yengi_Txt=NULL;
        UChaplaStr(yengi_Txt);
    }
}

//Tallanghan rayondiki Koan Yeziqni Uyghur Latin Yeziqi(Burunqi nami UKY)gha aylanduridu
void UEditWin::UOnToUyghurLatin()
{
    if(this->UIsTextSelected())
    {
        wchar_t *bufferUKY;
        wchar_t *buffer=UGetSelectionText(FALSE);
        if(buffer==NULL) return;
        // Uyghurchini UKY aylandurghanda Memeory kopiyidu shunga
        // kopraq mmory ajirtimiz
        bufferUKY=new wchar_t[wcslen(buffer)*2];
        if(bufferUKY==NULL) return;

        CUyghurcheKodAlmashturush kda;
        kda.UyghurToLatin(buffer,bufferUKY);
        UChaplaStr(bufferUKY);
        delete[] bufferUKY;
        delete[] buffer;
    }
}


void UEditWin::UOnToUyghurArabic()
{
    if(this->UIsTextSelected())
    {
        wchar_t *bufferKona;
        long len;
        wchar_t *bufferUKY=UGetSelectionText(FALSE);
        if(bufferUKY==NULL) return;
        len=wcslen(bufferUKY);
        bufferKona=new wchar_t[len*2];
        if(bufferKona==NULL) return;

        CUyghurcheKodAlmashturush kda;
        // awal Uniocde qa yalanduridu
        kda.LatinToUyghur(bufferUKY,bufferKona);
        delete[] bufferUKY;
        wchar_t *toghraBuf=NULL;
        if(toghraBuf==NULL)
        {
            UChaplaStr(bufferKona);
            delete[] bufferKona;
        }
        else
        {
            Toghrila(bufferKona,toghraBuf);
            delete[] bufferKona;
            UChaplaStr(toghraBuf);
            delete[] toghraBuf;
        }
    }
}

//Tallanghan rayondiki Kona Yeziqni Uyghur Slawiyan Yeziqi(Burunqi nami UKY)gha aylanduridu
void UEditWin::UOnToUyghurSlawiyan()
{
    if(this->UIsTextSelected())
    {
        wchar_t *bufferUKY;
        wchar_t *buffer=UGetSelectionText(FALSE);
        if(buffer==NULL) return;
        // Uyghurchini UKY aylandurghanda Memeory kopiyidu shunga
        // kopraq mmory ajirtimiz
        bufferUKY=new wchar_t[wcslen(buffer)*2];
        if(bufferUKY==NULL) return;

        CUyghurcheKodAlmashturush kda;
        kda.UyghurToSlawiyan(buffer,bufferUKY);
        UChaplaStr(bufferUKY);
        delete[] bufferUKY;
        delete[] buffer;
    }
}

void UEditWin::UOnSlawiyanToUyghurArabic()
{
    if(this->UIsTextSelected())
    {
        wchar_t *bufferKona;
        long len;
        wchar_t *bufferUKY=UGetSelectionText(FALSE);
        if(bufferUKY==NULL) return;
        len=wcslen(bufferUKY);
        bufferKona=new wchar_t[len*2];
        if(bufferKona==NULL) return;

        CUyghurcheKodAlmashturush kda;
        // awal Uniocde qa yalanduridu
        kda.SlawiyanToUyghur(bufferUKY,bufferKona);
        delete[] bufferUKY;
        wchar_t *toghraBuf=NULL;
        if(toghraBuf==NULL)
        {
            UChaplaStr(bufferKona);
            delete[] bufferKona;
        }
        else
        {
            Toghrila(bufferKona,toghraBuf);
            delete[] bufferKona;
            UChaplaStr(toghraBuf);
            delete[] toghraBuf;
        }
    }
}

//Tallanghan rayondiki Kona Yeziqni Uyghur Ortaq Turk Tili Elippbesige aylanduridu
void UEditWin::UOnToTurk()
{
    if(this->UIsTextSelected())
    {
        wchar_t *bufferUKY;
        wchar_t *buffer=UGetSelectionText(FALSE);
        if(buffer==NULL) return;
        // Uyghurchini UKY aylandurghanda Memeory kopiyidu shunga
        // kopraq mmory ajirtimiz
        bufferUKY=new wchar_t[wcslen(buffer)*2];
        if(bufferUKY==NULL) return;

        CUyghurcheKodAlmashturush kda;
        kda.UyghurToTurk(buffer,bufferUKY);
        UChaplaStr(bufferUKY);
        delete[] bufferUKY;
        delete[] buffer;
    }
}

void UEditWin::UOnTurkToUyghurArabic()
{
    if(this->UIsTextSelected())
    {
        wchar_t *bufferKona;
        long len;
        wchar_t *bufferUKY=UGetSelectionText(FALSE);
        if(bufferUKY==NULL) return;
        len=wcslen(bufferUKY);
        bufferKona=new wchar_t[len*2];
        if(bufferKona==NULL) return;

        CUyghurcheKodAlmashturush kda;
        // awal Uniocde qa yalanduridu
        kda.TurkToUyghur(bufferUKY,bufferKona);
        delete[] bufferUKY;
        wchar_t *toghraBuf=NULL;
        if(toghraBuf==NULL)
        {
            UChaplaStr(bufferKona);
            delete[] bufferKona;
        }
        else
        {
            Toghrila(bufferKona,toghraBuf);
            delete[] bufferKona;
            UChaplaStr(toghraBuf);
            delete[] toghraBuf;
        }
    }
}


void UEditWin::UOnToUyghurArabic_Program()
{
    if(this->UIsTextSelected())
    {
        wchar_t *bufferKona;
        long len;
        wchar_t *bufferUKY=UGetSelectionText(FALSE);
        if(bufferUKY==NULL) return;
        len=wcslen(bufferUKY);
        bufferKona=new wchar_t[len*2];
        if(bufferKona==NULL) return;

        CUyghurcheKodAlmashturush kda;
        // awal Uniocde qa yalanduridu
        kda.LatinToUyghur(bufferUKY,bufferKona);
        delete[] bufferUKY;
        wchar_t *toghraBuf=NULL;
        if(toghraBuf==NULL)
        {
            UChaplaStr(bufferKona);
            delete[] bufferKona;
        }
        else
        {
            Toghrila(bufferKona,toghraBuf);
            delete[] bufferKona;
            UChaplaStr(toghraBuf);
            delete[] toghraBuf;
        }
    }
}



// Tallanghan rayondiki Uyghurche we Englizche heriplerni CHong yezilihsqa aylanduridu
void UEditWin::UOnToChong()
{
    if(this->UIsTextSelected()==FALSE) return;

    CUyghurcheKodAlmashturush kda;
    wchar_t *buffer=UGetSelectionText(FALSE);
    kda.UChongYaz(buffer);
    UChaplaStr(buffer);
    delete[] buffer;
}

//Tallanghan rayondiki Uyghurche we Englizche heriplerni kichik yezilihsqa aylanduridu
void UEditWin::UOnToKichik()
{
    if(this->UIsTextSelected()==FALSE) return;

    CUyghurcheKodAlmashturush kda;
    wchar_t *buffer=UGetSelectionText(FALSE);
    kda.UKichikYaz(buffer);
    UChaplaStr(buffer);
    delete[] buffer;
}

// Bu Asasiy Kodini ishletmey kochuridu(Clip Board ) gha
void UEditWin::UOnKochurushAll()
{
    if(this->UIsTextSelected()==FALSE) return;
    wchar_t *selText=UGetSelectionText(TRUE);
    long newLen=0;
    wchar_t *newBuf=UUlash(selText,wcslen(selText),&newLen);
    delete[] selText;
    gSetToClipboard(newBuf);
    delete[] newBuf;
}

void UEditWin::UOnChaplashBashqa(UINT buy)
{
    wchar_t* clipData=gGetFromClipboard();
    wchar_t* bashqa;
    if(clipData!=NULL)
    {
        CUyghurcheKodAlmashturush uka;
        if(buy==TEHRIR_BCHAPLASH_UYGHURSOFT)
        {
            uka.UyghurSoftToUnicode(clipData);
            this->UChaplaStr(clipData);
        }
        else if(buy==TEHRIR_BCHAPLASH_ILIKYURT)
        {
            uka.IlikyurtToUnicode(clipData);
            this->UChaplaStr(clipData);
        }
        else if(buy==TEHRIR_BCHAPLASH_DULDUL)
        {
            uka.DuldulToUnicode(clipData);
            this->UChaplaStr(clipData);
        }
        else if(buy==TEHRIR_BCHAPLASH_UIGHUR_NOTEPAD)
        {
            uka.UighurNotePadToUnicode(clipData);
            this->UChaplaStr(clipData);
        }
        else if(buy==TEHRIR_BCHAPLASH_BASHQILAR)
        {
            bashqa=uka.BashqaToUnicode(clipData);
            UChaplaStr(bashqa);
            delete[] bashqa;
        }
        delete[] clipData;
    }
}


void UEditWin::UOnTizishHemme()
{
    wchar_t *newBuf=new wchar_t[m_UBuffer.GetSize()*2];
    if(newBuf==NULL)
    {
        return;
    }
    wmemset(newBuf,0x00,m_UBuffer.GetSize()*2);
    this->UClearSelection(FALSE);
    this->m_UnReDO->clear();

    this->m_JemiQurSani=0;

    RECT rc;
    ::GetClientRect(m_hWnd,&rc);
//	m_BetKeng=rc.right/2;
    m_EngKeng=rc.right;

    m_USelPos+=this->UTengshesh(m_UBuffer.GetBuffer(),m_UBuffer.GetSize(),newBuf,m_EngKeng-m_Boshluq,m_USelPos);
    m_UBuffer.Put(newBuf);
    delete[] newBuf;

    m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
    m_VX=0;
    UKorundighanEkran(UEKRAN_Y);
    return;
}


BOOL UEditWin::UIsRTL()
{
    return m_UEdit.mue_RTL;
}

void UEditWin::Toghrila(wchar_t *EsliBuf,wchar_t *newBuf)
{
    wchar_t Herp;
    wchar_t Soz[MAX_SOZ_LEN+1];
    wchar_t SozT[MAX_SOZ_LEN+1];
    Soz[0]=0x0;
    SozT[0]=0x0;
    int len=0;
    long wPos=0;
    bool tapqan=false;
    Herp=*EsliBuf;

    if(UInitImla==NULL || UGetToghrisi==NULL)
    {
        wcscpy(newBuf,EsliBuf);
        return;
    }

    UInitImla(NULL,UM_IMLA,mhInstance);

    while(Herp!=0x0)
    {
        if(gUGetUnicodeIndex(Herp)!=-1)
        {
            len=0;
            tapqan=false;
            while(Herp!=0x0)
            {
                if(Herp==L'-')
                {
                    if(tapqan==true)
                    {
                        break;
                    }
                    tapqan=true;
                    Soz[len++]=Herp;
                    EsliBuf++;
                    Herp=*EsliBuf;
                    continue;
                }
                if(gUGetUnicodeIndex(Herp)==-1) break;
                Soz[len++]=Herp;
                EsliBuf++;
                Herp=*EsliBuf;
            }
            Soz[len]=0x0;
            if(tapqan==true)
            {
                if(Soz[len-1]==L'-')
                {
                    EsliBuf--;
                    len--;
                    Soz[len]=0x0;
                }
            }
            if(len>MAX_SOZ_LEN)
            {
                len=MAX_SOZ_LEN;
                Soz[MAX_SOZ_LEN]=0x0;
            }
            SozT[0]=0x0;
            if((UIsCorrect(Soz,false)==FALSE) && (UGetToghrisi(Soz,SozT)==U_REPLACE))
            {
                len=0;
                while(SozT[len]!=0x0)
                {
                    newBuf[wPos++]=SozT[len++];
                }
            }
            else
            {
                len=0;
                while(Soz[len]!=0x0)
                {
                    newBuf[wPos++]=Soz[len++];
                }
            }
        }
        else
        {
            newBuf[wPos++]=Herp;
            EsliBuf++;
        }
        Herp=*EsliBuf;
    }
    newBuf[wPos]=0x0;
}

//Putkul Hojjet terkiwiidiki Uyghurche Kona yeziqta yezilghanni Slawiyan Yeziqigha aylanduridu
void UEditWin::UOnUyghurToSlawiyan()
{
    CUyghurcheKodAlmashturush tmp_Uka;
    ULONG size=m_UBuffer.GetSize();
    if(size==0) return;
    wchar_t *newBuf=new wchar_t[size*2];
    if(newBuf==NULL) return;
    wchar_t *curBuf=m_UBuffer.GetBuffer();
    tmp_Uka.UyghurToSlawiyan(curBuf,newBuf);

    m_UBuffer.Put(newBuf);
    delete[] newBuf;

    m_UFileName[0]=0x0;
    this->m_VX=0;
    this->m_VY=0;
    this->m_HazirqiHerip=0;
    this->m_HazirqiQur=0;
    this->m_USelPos=0;
    this->m_USelS=0;
    this->m_USelE=0;
    this->m_UFirstLine=m_UBuffer.GetBuffer();
    this->m_UnReDO->clear();
    m_JemiQurSani=m_UBuffer.UGetJemiyQurSani();
    this->UInvalidate();
    USetRTL(FALSE);
}

//Putkul Hojjet terkiwidiki Uyghurche Kona yeziqta yezilghanni Ortaq Turk Yeziqigha aylanduridu
void UEditWin::UOnUyghurToTurk()
{
    CUyghurcheKodAlmashturush tmp_Uka;
    ULONG size=m_UBuffer.GetSize();
    if(size==0) return;
    wchar_t *newBuf=new wchar_t[size*2];
    if(newBuf==NULL) return;
    wchar_t *curBuf=m_UBuffer.GetBuffer();
    tmp_Uka.UyghurToTurk(curBuf,newBuf);

    m_UBuffer.Put(newBuf);
    delete[] newBuf;

    m_UFileName[0]=0x0;
    this->m_VX=0;
    this->m_VY=0;
    this->m_HazirqiHerip=0;
    this->m_HazirqiQur=0;
    this->m_USelPos=0;
    this->m_USelS=0;
    this->m_USelE=0;
    this->m_UFirstLine=m_UBuffer.GetBuffer();
    this->m_UnReDO->clear();
    m_JemiQurSani=m_UBuffer.UGetJemiyQurSani();
    this->UInvalidate();
    USetRTL(FALSE);
}


void UEditWin::UOnSlawiyanToUyghur()
{
    CUyghurcheKodAlmashturush tmp_Uka;
    ULONG size=m_UBuffer.GetSize();
    if(size==0) return;
    wchar_t *newBuf=new wchar_t[size*2];
    if(newBuf==NULL) return;

    wchar_t *curBuf=m_UBuffer.GetBuffer();
    tmp_Uka.SlawiyanToUyghur(curBuf,newBuf);

    wchar_t *toghraBuf=NULL;
    if(toghraBuf==NULL)
    {
        m_UBuffer.Put(newBuf);
        delete[] newBuf;
    }
    else
    {
        Toghrila(newBuf,toghraBuf);
        m_UBuffer.Put(toghraBuf);
        delete[] newBuf;
        delete[] toghraBuf;
    }
    m_UFileName[0]=0x0;
    this->m_VX=0;
    this->m_VY=0;
    this->m_HazirqiHerip=0;
    this->m_HazirqiQur=0;
    this->m_USelPos=0;
    this->m_USelS=0;
    this->m_USelE=0;
    this->m_UFirstLine=m_UBuffer.GetBuffer();
    this->m_UnReDO->clear();
    m_JemiQurSani=m_UBuffer.UGetJemiyQurSani();
    this->UInvalidate();
    UShowCaret();
    USetRTL(TRUE);
}

void UEditWin::UOnTurkToUyghur()
{
    CUyghurcheKodAlmashturush tmp_Uka;
    ULONG size=m_UBuffer.GetSize();
    if(size==0) return;
    wchar_t *newBuf=new wchar_t[size*2];
    if(newBuf==NULL) return;

    wchar_t *curBuf=m_UBuffer.GetBuffer();
    tmp_Uka.TurkToUyghur(curBuf,newBuf);

    wchar_t *toghraBuf=NULL;
    if(toghraBuf==NULL)
    {
        m_UBuffer.Put(newBuf);
        delete[] newBuf;
    }
    else
    {
        Toghrila(newBuf,toghraBuf);
        m_UBuffer.Put(toghraBuf);
        delete[] newBuf;
        delete[] toghraBuf;
    }
    m_UFileName[0]=0x0;
    this->m_VX=0;
    this->m_VY=0;
    this->m_HazirqiHerip=0;
    this->m_HazirqiQur=0;
    this->m_USelPos=0;
    this->m_USelS=0;
    this->m_USelE=0;
    this->m_UFirstLine=m_UBuffer.GetBuffer();
    this->m_UnReDO->clear();
    m_JemiQurSani=m_UBuffer.UGetJemiyQurSani();
    this->UInvalidate();
    UShowCaret();
    USetRTL(TRUE);
}

//Uyghurche Kona yeziqta yezilghanni UKYgha aylanduridu
void UEditWin::UOnToULY()
{
    CUyghurcheKodAlmashturush tmp_Uka;
    ULONG size=m_UBuffer.GetSize();
    if(size==0) return;
    wchar_t *newBuf=new wchar_t[size*2];
    if(newBuf==NULL) return;
    wchar_t *curBuf=m_UBuffer.GetBuffer();
    tmp_Uka.UyghurToLatin(curBuf,newBuf);

    m_UBuffer.Put(newBuf);
    delete[] newBuf;

    m_UFileName[0]=0x0;
    this->m_VX=0;
    this->m_VY=0;
    this->m_HazirqiHerip=0;
    this->m_HazirqiQur=0;
    this->m_USelPos=0;
    this->m_USelS=0;
    this->m_USelE=0;
    this->m_UFirstLine=m_UBuffer.GetBuffer();
    this->m_UnReDO->clear();
    m_JemiQurSani=m_UBuffer.UGetJemiyQurSani();
    this->UInvalidate();
    USetRTL(FALSE);
}



void UEditWin::UOnToUEY_TXT()
{
    CUyghurcheKodAlmashturush tmp_Uka;
    ULONG size=m_UBuffer.GetSize();
    if(size==0) return;
    wchar_t *newBuf=new wchar_t[size*2];
    if(newBuf==NULL) return;

    wchar_t *curBuf=m_UBuffer.GetBuffer();
    tmp_Uka.LatinToUyghur(curBuf,newBuf);

    wchar_t *toghraBuf=NULL;
    if(toghraBuf==NULL)
    {
        m_UBuffer.Put(newBuf);
        delete[] newBuf;
    }
    else
    {
        Toghrila(newBuf,toghraBuf);
        if(wcslen(newBuf)!=wcslen(toghraBuf))
        {
            size=size;
        }
        m_UBuffer.Put(toghraBuf);
        delete[] newBuf;
        delete[] toghraBuf;
    }
    m_UFileName[0]=0x0;
    this->m_VX=0;
    this->m_VY=0;
    this->m_HazirqiHerip=0;
    this->m_HazirqiQur=0;
    this->m_USelPos=0;
    this->m_USelS=0;
    this->m_USelE=0;
    this->m_UFirstLine=m_UBuffer.GetBuffer();
    this->m_UnReDO->clear();
    m_JemiQurSani=m_UBuffer.UGetJemiyQurSani();
    this->UInvalidate();
    UShowCaret();
    USetRTL(TRUE);
}

/*
//Kona Yeziq qoshulghan programma we korsetme uchurlarni ULY aylanduridu
//Buni ayrim qilmisa, UEY ni ULY aylandurghanda, chong we kichik yezilishini
//aptomatik toghrilaydighan bolgahchqa mesile korulidu
//shunga shu eslidiki englizchini shu peti saqlap qelish mexsitide qollinildi
void UEditWin::UOnToULYINF()
{
	//Gheyret
	m_HazirqiHerip=0;
	UCalSelPos();
//	m_USelPos=m_UBuffer.GetHerpPosAtYX(m_HazirqiQur,m_HazirqiHerip);
	wchar_t *curLine=m_UBuffer.GetAdressFromPos(m_USelPos);
	int len=0;
	int  offset=0;
	UINT ret;
	bool hemme=false;
	while(true)
	{
		len=UGetUyghurTizma(curLine,&offset);
		if(len==-1) break;
		m_USelPos+=offset;
		m_USelS=m_USelPos;
		m_USelE=m_USelS+len;
		if(len>0)
		{
			m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
			if(hemme==false)
			{
                UKorundighanEkran(UEKRAN_XY);
                UInvalidate();
                USetScroll();
                ret=m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_PROG_AYLANDUR"),MB_YESNOALLSTOP);
                if(ret==IDCANCEL) break;
                if(ret==IDYES)
                {
                    UOnToUyghurLatinInf();
                }
                else if(ret==TAL_BTN_HEMMNI){
                    UOnToUyghurLatinInf();
                    hemme=true;
                }
                else
                {
                    m_USelPos+=len;
                }
			}
			else{
                    UOnToUyghurLatinInf();
			}
		}
		m_USelPos++;
		m_USelS=m_USelE=m_USelPos;
		curLine=m_UBuffer.GetAdressFromPos(m_USelPos);
	}
	m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
	UKorundighanEkran(UEKRAN_XY);
	USetScroll();
	UInvalidate();
}

void UEditWin::UOnToUyghurLatinInf()
{
	if(this->UIsTextSelected())
	{
    	wchar_t *bufferUKY;
		wchar_t *buffer=UGetSelectionText(FALSE);
    	if(buffer==NULL) return;
		// Uyghurchini UKY aylandurghanda Memeory kopiyidu shunga
		// kopraq mmory ajirtimiz
		bufferUKY=new wchar_t[wcslen(buffer)*2];
		if(bufferUKY==NULL) return;

		CUyghurcheKodAlmashturush kda;
		kda.UUnicodeToUKYInf(buffer,bufferUKY);
		UChaplaStr(bufferUKY);
		delete[] bufferUKY;
		delete[] buffer;
	}
}
*/

int UEditWin::UGetUyghurTizma(wchar_t *line,int *sPos)
{
    *sPos=0;
    wchar_t Herp;
    int curPos;
    bool find=false;
    curPos=0;
    Herp=line[curPos];
    while(Herp!=0x0)
    {
        Herp=line[curPos];
        if(gUGetUnicodeIndex(Herp)!=-1)
        {
            *sPos=curPos;
            find=true;
            break;
        }
        curPos++;
    }

    if(find==false) return -1;

    int cnt;
    cnt=0;
    find=false;
    Herp=line[curPos];
    while(Herp!=0x0)
    {
        Herp=line[curPos];
        if(gUIsUyghur(Herp)==TRUE)
        {
            curPos++;
            cnt++;
        }
        else
        {
            find=true;
            break;
        }
    }
    return cnt;
}


void UEditWin::UOnToUEY_PRG()
{
    //Gheyret
    m_HazirqiHerip=0;
    UCalSelPos();
//	m_USelPos=m_UBuffer.GetHerpPosAtYX(m_HazirqiQur,m_HazirqiHerip);
    wchar_t *curLine=m_UBuffer.GetAdressFromPos(m_USelPos);
    int len=0;
    int  offset=0;
    UINT ret;
    while(true)
    {
        len=UGetPoss(curLine,&offset);
        if(len==-1) break;
        m_USelPos+=offset;
        m_USelS=m_USelPos;
        m_USelE=m_USelS+len;
        if(len>0)
        {
            m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
            UKorundighanEkran(UEKRAN_XY);
            UInvalidate();
            ret=m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_PROG_AYLANDUR"),MB_YESNOSTOP);
            if(ret==IDCANCEL) break;
            if(ret==IDYES)
            {
                UOnToUyghurArabic_Program();
            }
            else
            {
                m_USelPos+=len;
            }
        }
        m_USelPos++;
        m_USelS=m_USelE=m_USelPos;
        curLine=m_UBuffer.GetAdressFromPos(m_USelPos);
    }
    m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
    UKorundighanEkran(UEKRAN_XY);
    UInvalidate();
}


// Korsetme uchurlarni aylandurush
void UEditWin::UOnToUEY_INF()
{
    m_HazirqiHerip=0;
    UCalSelPos();
//	m_USelPos=m_UBuffer.GetHerpPosAtYX(m_HazirqiQur,m_HazirqiHerip);
    wchar_t *curLine=m_UBuffer.GetAdressFromPos(m_USelPos);
    int len=0;
    int  offset=0;
    UINT ret;
    BOOL hemme=FALSE;
    while(true)
    {
        len=UGetTengPoss(curLine,&offset);
        if(len==-1) break;
        if(len>0)
        {
            m_USelPos=m_UBuffer.GetPosFromAdress(curLine);
            m_USelPos+=offset;
            m_USelS=m_USelPos;
            m_USelE=m_USelS+len;
            if(hemme==FALSE)
            {
                m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
                UKorundighanEkran(UEKRAN_XY);
                UInvalidate();
                ret=m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_PROG_AYLANDUR"),MB_YESNOALLSTOP);
                if(ret==IDCANCEL) break;
                if(ret==IDYES||ret==TAL_BTN_HEMMNI)
                {
                    UOnToUyghurArabic_Program();
                    if(ret==TAL_BTN_HEMMNI)
                    {
                        hemme=TRUE;
                    }

                }
            }
            else
            {
                UOnToUyghurArabic_Program();
            }
        }
        curLine=m_UBuffer.GetNextLine(curLine);
    }
    m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
    UKorundighanEkran(UEKRAN_XY);
    UInvalidate();
}


//Her Bir Qurdiki Tenglik Belgisining ornini tapidu
//sPos: bashlinish orni,
//return Tenglik Belgisining keynidiki Herplerning orni

int UEditWin::UGetTengPoss(wchar_t *line,int *sPos)
{
    int len=-1;
    *sPos=0;
    wchar_t Herp;
    int curPos;
    bool find=false;
    curPos=0;
    Herp=line[curPos];

    while(Herp!=0x0)
    {
        if(Herp==QURBELGISI_R)
        {
            len=0;
            break;
        }
        Herp=line[curPos];
        if(Herp=='=')
        {
            curPos++;
            *sPos=curPos;
            find=true;
            break;
        }
        curPos++;
    }

    if(find==false) return len; // Bi rqur ichide tanglik belgisi bolmisa 0 ni hojjetning axirigha kelgen bolsa -1 ni qayturidu

    int cnt;
    cnt=0;
    find=false;
    Herp=line[curPos];
    while(Herp!=0x0)
    {
        Herp=line[curPos];
        if(Herp==QURBELGISI_R)
        {
            find=true;
            break;
        }
        curPos++;
        cnt++;
    }
    return cnt;
}



//Qosh tirnaq bilen qorshalghan tekistni tapidu
// sPos: bashlinish orni,
// return tirna qichidiki herplerning sani

int UEditWin::UGetPoss(wchar_t *line,int *sPos)
{
    *sPos=0;
    wchar_t Herp;
    int curPos;
    wchar_t tirnaq=0x0;
    bool find=false;
    curPos=0;
    Herp=line[curPos];
    while(Herp!=0x0)
    {
        Herp=line[curPos];
        if(Herp=='"' || Herp=='\'')
        {
            tirnaq=Herp;
            curPos++;
            *sPos=curPos;
            find=true;
            break;
        }
        curPos++;
    }

    if(find==false) return -1;

    int cnt;
    cnt=0;
    find=false;
    Herp=line[curPos];
    while(Herp!=0x0)
    {
        Herp=line[curPos];
        if(Herp==tirnaq)
        {
            if(line[curPos-1]!=0x005c)
            {
                find=true;
                break;
            }
        }
        curPos++;
        cnt++;
    }
    return cnt;
}


void UEditWin::UOnBesish(LPARAM lp)
{
    LPPRINTDLG lpPdlg=(LPPRINTDLG)lp;
    wchar_t    docName[1024];
    wcscpy(docName,L"UyghurEdit - ");
    if(m_UFileName[0]==0x0)
    {
        wcscat(docName,L"Namsiz");
    }
    else
    {
        wcscat(docName,m_UFileName);
    }

    LPDEVMODE  pdm=(LPDEVMODE)GlobalLock(lpPdlg->hDevMode);
    if(lpPdlg!=NULL)
    {
        CUPrinter uPrin(lpPdlg->hDC,m_UEdit.mue_RTL);
        uPrin.USetFont(&m_UEdit);
        uPrin.USetMargin(25,20,25,20);
        uPrin.USetPaper(pdm);
        int betSani=uPrin.UTeyyarla(this->m_UBuffer.GetBuffer());

        int bashBet, axirqiBet;
        // bet numurini korsitip berish
        DWORD pp=PD_PAGENUMS & lpPdlg->Flags;
        if(pp)
        {
            bashBet=lpPdlg->nFromPage;
            axirqiBet=lpPdlg->nToPage;
        }
        else
        {
            // Hemme betni besish
            bashBet=1;
            axirqiBet=betSani;
        }
        DOCINFO info;
        ::ZeroMemory(&info, sizeof(DOCINFO));
        info.cbSize=sizeof(DOCINFO);
        info.lpszDocName = docName;
        StartDoc(lpPdlg->hDC,&info);
        for(int i=bashBet; i<=axirqiBet && i<=betSani ; i++)
        {
            uPrin.UBetniBas(i);
        }
        EndDoc(lpPdlg->hDC);
    }
}

UINTERFACE_LANG UEditWin::UGetInterfaceLang()
{
    return m_UEdit.mue_Lang;
}

void  UEditWin::USetInterfaceLang(UINTERFACE_LANG lang)
{
    m_UEdit.mue_Lang=lang;
    if(USetUILang!=NULL)
    {
        USetUILang(lang);
    }
}

//Ctrl+F10 ambarda yoq sozler
//Ctrl+F9 bolsa ambarda bar sozler
void UEditWin::USozgeParchila(bool qosh)
{
    if(UInitImla==NULL||ULoadDictionary==NULL||UIsCorrect==NULL)
    {
        USozgeParchila_Tekshurme();
        return;
    }

    UInitImla(NULL,UM_IMLA,mhInstance);
    ULoadDictionary();
    wchar_t Soz[MAX_SOZ_LEN+1];
    UINT len=0;
    BOOL  ret;

    UINT bufLen=0;
    bufLen=m_UBuffer.GetSize()+1;
    wchar_t *Buffer=new wchar_t[m_UBuffer.GetSize()+1];

    if(Buffer==NULL)
    {
        m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_MEM"),MB_OK);
        return;
    }

    Buffer[0]=0x0;
    m_USelPos=0;
    m_USelPos=m_UBuffer.UGetUyghurToken(m_USelPos,len);
    int SozSani=0;

    bufLen=0;
    if(qosh==true)  // F9
    {
        while(len!=0)
        {
            wcsncpy(Soz,m_UBuffer.GetAdressFromPos(m_USelPos),len);
            Soz[len]=0x0;
            ret=UIsCorrect(Soz,false);
            if(ret==TRUE)
            {
                Soz[len]=QURBELGISI_R;
                Soz[len+1]=0x0;
                wcscat(&Buffer[bufLen],Soz);
                bufLen+=(len+1);
                SozSani++;
            }
            m_USelPos+=len;
            m_USelPos=m_UBuffer.UGetUyghurToken(m_USelPos,len);
        }
    }
    else  //F10
    {
        while(len!=0)
        {
            wcsncpy(Soz,m_UBuffer.GetAdressFromPos(m_USelPos),len);
            Soz[len]=0x0;
            ret=UIsCorrect(Soz,false);
            if(ret==FALSE)
            {
                Soz[len]=QURBELGISI_R;
                Soz[len+1]=0x0;
                wcscat(&Buffer[bufLen],Soz);
                bufLen+=(len+1);
                SozSani++;
            }
            m_USelPos+=len;
            m_USelPos=m_UBuffer.UGetUyghurToken(m_USelPos,len);
        }
    }

    UUnLoadDictionary();
    gUSort(Buffer,QURBELGISI_R,true);
    gSetToClipboard(Buffer);
    UNewUyghurEdit();
    delete[] Buffer;
}

// Yengidin UyghurEditni qozghitidu
void UEditWin::UNewUyghurEdit()
{
    wchar_t parApp[MAX_PATH];
    int len=GetModuleFileName(mhInstance,parApp,MAX_PATH);
    if(len==0) return;
    wcscat(parApp,L" -clipboard");

    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si,sizeof(si));
    si.cb=sizeof(si);
    ZeroMemory(&pi,sizeof(pi));

    CreateProcess(NULL,parApp,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi);
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);
}


void UEditWin::USozgeParchila_Tekshurme()
{
    wchar_t Soz[MAX_SOZ_LEN+1];
    UINT len=0;
    wchar_t *Buffer=new wchar_t[m_UBuffer.GetSize()+1];

    if(Buffer==NULL)
    {
        m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_MEM"),MB_OK);
        return;
    }

    Buffer[0]=0x0;
    UINT bufLen=0;
    m_USelPos=0;
    m_USelPos=m_UBuffer.UGetUyghurToken(m_USelPos,len);
    int SozSani=0;
    while(len!=0)
    {
        wcsncpy(Soz,m_UBuffer.GetAdressFromPos(m_USelPos),len);
        Soz[len]=QURBELGISI_R;
        Soz[len+1]=0x0;
        wcscat(&Buffer[bufLen],Soz);
        bufLen+=(len+1);
        SozSani++;
        m_USelPos+=len;
        m_USelPos=m_UBuffer.UGetUyghurToken(m_USelPos,len);
    }
    gUSort(Buffer,QURBELGISI_R,true);

    gSetToClipboard(Buffer);
    UNewUyghurEdit();

    delete[] Buffer;
}

BOOL UEditWin::UAlahideKodBarmu()
{
    BOOL ret=FALSE;
    ULONG pos=0;
    wchar_t *Buf=m_UBuffer.GetBuffer();
    while(1)
    {
        if(Buf[pos]==0) break;
        if(Buf[pos]>0xE000 && Buf[pos]<0xE0FF)
        {
            ret=TRUE;
            break;
        }
        pos++;
    }
    return ret;
}

void UEditWin::UOnImlaTekshur(WPARAM wp,LPARAM lp)
{
    int		ret=(int)lp;
    if(ret==U_STOP)
    {
        UUnLoadDictionary();
        return;
    }

    UINT len=0;

    if(m_UEdit.mue_RTL==TRUE)
    {
        len=ImlaTekshurushUEY(ret);
    }
    else
    {
        if(m_Alahide==TRUE)
        {
            len=ImlaTekshurushAlahide(ret);
        }
        else
        {
            len=ImlaTekshurushULY(ret);
        }
    }

    m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
    UKorundighanEkran(UEKRAN_XY);
    m_USelS=m_USelPos;
    m_USelE=m_USelPos+len;
    UInvalidate();
    UShowCaret();
    if(len==0)
    {
        UUnLoadDictionary();
        m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_IMLA_TUGIDI"),MB_OK);
    }
}

UINT UEditWin::ImlaTekshurushUEY(UINT ope)
{
    wchar_t Soz[MAX_SOZ_LEN+1];
    UINT len=0;
    if(ope==U_START)
    {
        m_HazirqiHerip=0;
        UCalSelPos();
//		m_USelPos=m_UBuffer.GetHerpPosAtYX(m_HazirqiQur,m_HazirqiHerip);
    }
    else
    {
        if(ope==U_REPLACE)
        {
//			len=UGetOrgWord(Soz);
//			len=wcslen(Soz);
            len=m_USelE-m_USelPos;
            wchar_t *esli_Txt=m_UBuffer.Delete(m_USelPos,len);
            int wLen=UGetCandidateWord(Soz,-1);
            wLen=wcslen(Soz);
            wchar_t *yengi_Txt=new wchar_t[wLen+1];
            wcscpy(yengi_Txt,Soz);
            UAddUnDO(esli_Txt,yengi_Txt);
            m_UBuffer.Insert(m_USelPos,yengi_Txt);
            m_USelPos+=wLen;
            this->m_UTextChanged=TRUE;
        }
        else if(ope==U_SKIP)
        {
            len=m_USelE-m_USelPos;
            m_USelPos+=len;
        }
    }

    UINT ret;
    m_USelPos=m_UBuffer.UGetUyghurToken(m_USelPos,len);
    while(len!=0)
    {
        wcsncpy(Soz,m_UBuffer.GetAdressFromPos(m_USelPos),len);
        Soz[len]=0x0;
        ret=UCheckWord(Soz,false);
        if(ret==U_STOP)
        {
            break;
        }
        else if(ret==U_REPLACE_AUTO)
        {
            wchar_t *esli_Txt=m_UBuffer.Delete(m_USelPos,len);
            int wLen=UGetCandidateWord(Soz,-1);
            wLen=wcslen(Soz);
            wchar_t *yengi_Txt=new wchar_t[wLen+1];
            wcscpy(yengi_Txt,Soz);
            UAddUnDO(esli_Txt,yengi_Txt);
            m_UBuffer.Insert(m_USelPos,yengi_Txt);
            m_USelPos+=wLen;
            this->m_UTextChanged=TRUE;
        }
        else
        {
            m_USelPos+=len;
        }
        m_USelPos=m_UBuffer.UGetUyghurToken(m_USelPos,len);
    }
    return len;
}

UINT UEditWin::ImlaTekshurushULY(UINT ope)
{
    wchar_t Soz[MAX_SOZ_LEN+1];
    wchar_t SozULY[2*MAX_SOZ_LEN+1];

    CUyghurcheKodAlmashturush kda;

    UINT len=0;
    if(ope==U_START)
    {
        m_HazirqiHerip=0;
        UCalSelPos();
//		m_USelPos=m_UBuffer.GetHerpPosAtYX(m_HazirqiQur,m_HazirqiHerip);
    }
    else
    {
        if(ope==U_REPLACE)
        {
//			len=UGetOrgWord(Soz);
//			kda.UUnicodeToUKY(Soz,SozULY);
//			len=wcslen(SozULY);
            len=m_USelE-m_USelPos;
            wchar_t *esli_Txt=m_UBuffer.Delete(m_USelPos,len);
            int wLen=UGetCandidateWord(Soz,-1);
            kda.UyghurToLatin(Soz,SozULY);
            if(gUIsLowerULY(esli_Txt[0]))
            {
                SozULY[0]=gUToLowerULY(SozULY[0]);
            }
            wLen=wcslen(SozULY);
            wchar_t *yengi_Txt=new wchar_t[wLen+1];
            wcscpy(yengi_Txt,SozULY);
            UAddUnDO(esli_Txt,yengi_Txt);
            m_UBuffer.Insert(m_USelPos,yengi_Txt);
            m_USelPos+=wLen;
            this->m_UTextChanged=TRUE;
        }
        else if(ope==U_SKIP)
        {
//			len=UGetOrgWord(Soz);
//			len=wcslen(Soz);
            len=m_USelE-m_USelPos;
            m_USelPos+=len;
        }
    }

    UINT ret;
    m_USelPos=m_UBuffer.UGetULYToken(m_USelPos,len);
    while(len!=0)
    {
        wcsncpy(Soz,m_UBuffer.GetAdressFromPos(m_USelPos),len);
        Soz[len]=0x0;
        kda.LatinToUyghur(Soz,SozULY);
        ret=UCheckWord(SozULY,false);
        if(ret==U_STOP)
        {
            break;
        }
        else if(ret==U_REPLACE_AUTO)
        {
            wchar_t *esli_Txt=m_UBuffer.Delete(m_USelPos,len);
            int wLen=UGetCandidateWord(Soz,-1);
            kda.UyghurToLatin(Soz,SozULY);
            if(gUIsLowerULY(esli_Txt[0]))
            {
                SozULY[0]=gUToLowerULY(SozULY[0]);
            }
            wLen=wcslen(SozULY);
            wchar_t *yengi_Txt=new wchar_t[wLen+1];
            wcscpy(yengi_Txt,SozULY);
            UAddUnDO(esli_Txt,yengi_Txt);
            m_UBuffer.Insert(m_USelPos,yengi_Txt);
            m_USelPos+=wLen;
            this->m_UTextChanged=TRUE;
        }
        else
        {
            m_USelPos+=len;
        }
        m_USelPos=m_UBuffer.UGetULYToken(m_USelPos,len);
    }
    return len;
}

UINT UEditWin::ImlaTekshurushAlahide(UINT ope)
{
    wchar_t Soz[MAX_SOZ_LEN+1];
    wchar_t SozAlahide[2*MAX_SOZ_LEN+1];

    CUyghurcheKodAlmashturush kda;

    UINT len=0;
    if(ope==U_START)
    {
        m_HazirqiHerip=0;
        UCalSelPos();
    }
    else
    {
        if(ope==U_REPLACE)
        {
            len=m_USelE-m_USelPos;
            wchar_t *esli_Txt=m_UBuffer.Delete(m_USelPos,len);
            int wLen=UGetCandidateWord(Soz,-1);
            kda.UyghurToMewhum(Soz,SozAlahide);
            if(gUIsLowerAlahide(esli_Txt[0]))
            {
                SozAlahide[0]=gUToLowerAlahide(SozAlahide[0]);
            }
            wLen=wcslen(SozAlahide);
            wchar_t *yengi_Txt=new wchar_t[wLen+1];
            wcscpy(yengi_Txt,SozAlahide);
            UAddUnDO(esli_Txt,yengi_Txt);
            m_UBuffer.Insert(m_USelPos,yengi_Txt);
            m_USelPos+=wLen;
            this->m_UTextChanged=TRUE;
        }
        else if(ope==U_SKIP)
        {
//			len=UGetOrgWord(Soz);
//			len=wcslen(Soz);
            len=m_USelE-m_USelPos;
            m_USelPos+=len;
        }
    }

    UINT ret;
    m_USelPos=m_UBuffer.UGetAlahideToken(m_USelPos,len);
    while(len!=0)
    {
        wcsncpy(Soz,m_UBuffer.GetAdressFromPos(m_USelPos),len);
        Soz[len]=0x0;
        kda.MewhumToUyghur(Soz,SozAlahide);
        ret=UCheckWord(SozAlahide,false);
        if(ret==U_STOP)
        {
            break;
        }
        else if(ret==U_REPLACE_AUTO)
        {
            wchar_t *esli_Txt=m_UBuffer.Delete(m_USelPos,len);
            int wLen=UGetCandidateWord(Soz,-1);
            kda.UyghurToMewhum(Soz,SozAlahide);
            if(gUIsLowerAlahide(esli_Txt[0]))
            {
                SozAlahide[0]=gUToLowerAlahide(SozAlahide[0]);
            }
            wLen=wcslen(SozAlahide);
            wchar_t *yengi_Txt=new wchar_t[wLen+1];
            wcscpy(yengi_Txt,SozAlahide);
            UAddUnDO(esli_Txt,yengi_Txt);
            m_UBuffer.Insert(m_USelPos,yengi_Txt);
            m_USelPos+=wLen;
            this->m_UTextChanged=TRUE;
        }
        else
        {
            m_USelPos+=len;
        }
        m_USelPos=m_UBuffer.UGetAlahideToken(m_USelPos,len);
    }
    return len;
}


void UEditWin::UAptomatikToghrila(void)
{
    UINT cnt;
    if(UInitImla==NULL||ULoadDictionary==NULL||UGetToghrisi==NULL)
    {
        return;
    }

    UInitImla(NULL,UM_IMLA,mhInstance);
    ULoadDictionary();

    if(m_UEdit.mue_RTL==TRUE)
    {
        cnt=AptomatikToghrilaUEY();
    }
    else
    {
        if(m_Alahide==TRUE)
        {
            cnt=AptomatikToghrilaAlahide();
        }
        else
        {
            cnt=AptomatikToghrilaULY();
        }
    }

    UUnLoadDictionary();
    m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
    UKorundighanEkran(UEKRAN_XY);
    m_USelS=m_USelPos;
    m_USelE=m_USelPos;
    UInvalidate();
    UShowCaret();
    wsprintf(_gmsgBuf,L"Jemiy %d soz aptomatik almashturuldi",cnt);
    PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_BUFFER_MESSAGE,(LPARAM)FALSE);
    return;
}

UINT UEditWin::AptomatikToghrilaUEY()
{
    wchar_t Soz[MAX_SOZ_LEN+1];
    wchar_t Toghra[MAX_SOZ_LEN+1];
    UINT len=0,yengilen=0;
    UINT cnt=0;
    wchar_t *_esli;
    wchar_t *_yengi;

    m_HazirqiHerip=0;
    UCalSelPos();
    m_USelPos=m_UBuffer.UGetUyghurToken(m_USelPos,len);
    while(len!=0)
    {
        wcsncpy(Soz,m_UBuffer.GetAdressFromPos(m_USelPos),len);
        Soz[len]=0x0;
        Toghra[0]=0x0;
        if((UIsCorrect(Soz,false)==FALSE) && (UGetToghrisi(Soz,Toghra)==U_REPLACE_AUTO))
        {
            yengilen=wcslen(Toghra);
            m_UBuffer.Replace(m_USelPos,len,Toghra,yengilen);
            _esli=new wchar_t[len+1];
            _yengi=new wchar_t[yengilen+1];
            wcscpy(_esli,Soz);
            wcscpy(_yengi,Toghra);
            this->UAddUnDO(_esli,_yengi);
            this->m_UTextChanged=TRUE;
            cnt++;
            len=yengilen;
        }
        m_USelPos+=len;
        m_USelPos=m_UBuffer.UGetUyghurToken(m_USelPos,len);
    }
    return cnt;
}

UINT UEditWin::AptomatikToghrilaULY()
{
    wchar_t Soz[MAX_SOZ_LEN+1];
    wchar_t Toghra[MAX_SOZ_LEN+1];
    wchar_t SozULY[2*MAX_SOZ_LEN+1];
    CUyghurcheKodAlmashturush kda;

    UINT len=0,yengilen=0;
    UINT cnt=0;
    wchar_t *_esli;
    wchar_t *_yengi;

    m_HazirqiHerip=0;
    UCalSelPos();
    m_USelPos=m_UBuffer.UGetULYToken(m_USelPos,len);
    while(len!=0)
    {
        wcsncpy(Soz,m_UBuffer.GetAdressFromPos(m_USelPos),len);
        Soz[len]=0x0;
        kda.LatinToUyghur(Soz,SozULY);
        Toghra[0]=0x0;
        if((UIsCorrect(SozULY,false)==FALSE) && (UGetToghrisi(SozULY,Toghra)==U_REPLACE_AUTO))
        {
            kda.UyghurToLatin(Toghra,SozULY);
            yengilen=wcslen(SozULY);
            m_UBuffer.Replace(m_USelPos,len,SozULY,yengilen);
            _esli=new wchar_t[len+1];
            _yengi=new wchar_t[yengilen+1];
            wcscpy(_esli,Soz);
            wcscpy(_yengi,SozULY);
            this->UAddUnDO(_esli,_yengi);
            this->m_UTextChanged=TRUE;
            cnt++;
            len=yengilen;
        }
        m_USelPos+=len;
        m_USelPos=m_UBuffer.UGetULYToken(m_USelPos,len);
    }
    return cnt;
}

UINT UEditWin::AptomatikToghrilaAlahide()
{
    wchar_t Soz[MAX_SOZ_LEN+1];
    wchar_t Toghra[MAX_SOZ_LEN+1];
    wchar_t SozAlahide[2*MAX_SOZ_LEN+1];

    UINT len=0,yengilen=0;
    UINT cnt=0;
    wchar_t *_esli;
    wchar_t *_yengi;
    CUyghurcheKodAlmashturush kda;

    m_HazirqiHerip=0;
    UCalSelPos();
    m_USelPos=m_UBuffer.UGetAlahideToken(m_USelPos,len);
    while(len!=0)
    {
        wcsncpy(Soz,m_UBuffer.GetAdressFromPos(m_USelPos),len);
        Soz[len]=0x0;
        kda.MewhumToUyghur(Soz,SozAlahide);
        Toghra[0]=0x0;
        if((UIsCorrect(SozAlahide,false)==FALSE) && (UGetToghrisi(SozAlahide,Toghra)==U_REPLACE_AUTO))
        {
            kda.UyghurToMewhum(Toghra,SozAlahide);
            yengilen=wcslen(SozAlahide);
            m_UBuffer.Replace(m_USelPos,len,SozAlahide,yengilen);
            _esli=new wchar_t[len+1];
            _yengi=new wchar_t[yengilen+1];
            wcscpy(_esli,Soz);
            wcscpy(_yengi,SozAlahide);
            this->UAddUnDO(_esli,_yengi);
            this->m_UTextChanged=TRUE;
            cnt++;
            len=yengilen;
        }
        m_USelPos+=len;
        m_USelPos=m_UBuffer.UGetAlahideToken(m_USelPos,len);
    }
    return cnt;
}

void UEditWin::UOnIzdesh()
{
    if(UIsTextSelected())
    {
        wchar_t *selText=UGetSelectionText(TRUE);
        wcsncpy(m_UIzdesh.mi_EsliSoz,selText,128);
        m_UIzdesh.mi_EsliSoz[127]=0x0;
    }
    else
    {
        if(wcslen(m_UIzdesh.mi_EsliSoz)==0)
        {
            wchar_t *curPos=m_UBuffer.GetAdressFromPos(m_USelPos);
            m_UBuffer.UGetSoz(curPos,&m_USelS,&m_USelE);
            m_USelE=m_USelPos+m_USelE;
            m_USelS=m_USelPos-m_USelS;
            m_USelPos=m_USelS;
            int len=m_USelE-m_USelS;
            if(len>128) len=128;
            curPos=m_UBuffer.GetAdressFromPos(m_USelPos);
            wcsncpy(m_UIzdesh.mi_EsliSoz,curPos,len);
            m_UIzdesh.mi_EsliSoz[len]=0x0;
        }
    }

    if(UShowFindDialog==NULL)
    {
        return;
    }

    UShowFindDialog(m_hWnd,&m_UIzdesh,m_UEdit.mue_Lang);
    if(m_UIzdesh.mi_Action==Herket_YOQ)return;

    m_USelPos=m_USelE=m_USelS;
    m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);

    wchar_t tmp[128];

    unsigned long len=UGetAsasKod(m_UIzdesh.mi_EsliSoz,tmp);
    wcscpy(m_UIzdesh.mi_EsliSoz,tmp);
    len=UGetAsasKod(m_UIzdesh.mi_OrunbasarSoz,tmp);

    wcscpy(m_UIzdesh.mi_OrunbasarSoz,tmp);

    if(m_UIzdesh.mi_Action==Herket_IZDE)
    {
        UIzdesh();
    }
    else if(m_UIzdesh.mi_Action==Herket_ALMASHTUR)
    {
        UAlmashturush();
    }
}

void UEditWin::UOnIzdeshDawam()
{
    if(m_UIzdesh.mi_Action==Herket_YOQ)
    {
        UOnIzdesh();
    }
    if(m_UIzdesh.mi_Action==Herket_IZDE)
    {
        UIzdesh();
    }
    else if(m_UIzdesh.mi_Action==Herket_ALMASHTUR)
    {
        UAlmashturush();
    }
}


void UEditWin::UIzdesh()
{

    wchar_t *curPos=m_UBuffer.GetAdressFromPos(m_USelPos);
    curPos=UTizmaTap(curPos,m_UIzdesh.mi_EsliSoz,m_UIzdesh.mi_Qandaq);
    if(curPos!=NULL && wcslen(m_UIzdesh.mi_EsliSoz)>0)
    {
        m_UIzdesh.mi_Cnt++;
        m_USelPos=m_UBuffer.GetPosFromAdress(curPos);
        m_USelS=m_USelPos;
        m_USelE=m_USelPos+wcslen(m_UIzdesh.mi_EsliSoz);
        m_USelPos=m_USelE;
        m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
        UKorundighanEkran(UEKRAN_XY);
        UInvalidate();
    }
    else
    {
        if(m_UIzdesh.mi_Cnt==0)
        {
            m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_IZDESH_TEPILMIDI"),MB_OK);
        }
        else
        {
            m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_IZDESH_TUGIDI"),MB_OK);
        }
    }
}

wchar_t* UEditWin::UTizmaTap(wchar_t *curPos, wchar_t *strSrc,QANDAQ qan)
{
    wchar_t *retPos=NULL;
    retPos=wcsstr(curPos,strSrc);
    if(qan==SOZ_XALIGHAN) return retPos;
    int len=wcslen(strSrc);

    wchar_t herpBax;
    wchar_t herpAxiri;

    while(retPos!=NULL)
    {
        if(qan==SOZ_PUTUN)
        {
            herpBax=m_UBuffer.GetAt(retPos-1);
            herpAxiri=m_UBuffer.GetAt(retPos+len);
            if(gUGetUnicodeIndex(herpBax)==-1 && gUGetUnicodeIndex(herpAxiri)==-1)
            {
                break;
            }
            retPos++;
            if(*retPos==0x0) break;
            retPos=wcsstr(retPos,strSrc);
        }
        else if(qan==SOZ_BESHI)
        {
            herpBax=m_UBuffer.GetAt(retPos-1);
            herpAxiri=m_UBuffer.GetAt(retPos+len);
            if(gUGetUnicodeIndex(herpBax)==-1 && gUGetUnicodeIndex(herpAxiri)!=-1)
            {
                break;
            }
            retPos++;
            if(*retPos==0x0) break;
            retPos=wcsstr(retPos,strSrc);
        }
        else if(qan==SOZ_AXIRI)
        {
            herpBax=m_UBuffer.GetAt(retPos-1);
            herpAxiri=m_UBuffer.GetAt(retPos+len);
            if(gUGetUnicodeIndex(herpBax)!=-1 && gUGetUnicodeIndex(herpAxiri)==-1)
            {
                break;
            }
            retPos++;
            if(*retPos==0x0) break;
            retPos=wcsstr(retPos,strSrc);
        }
    }
    return retPos;
}

void UEditWin::UAlmashturush()
{
    wchar_t *curPos=m_UBuffer.GetAdressFromPos(m_USelPos);
//	curPos=wcsstr(curPos,m_UIzdesh.mi_EsliSoz);
    curPos=UTizmaTap(curPos,m_UIzdesh.mi_EsliSoz,m_UIzdesh.mi_Qandaq);
    if(curPos==NULL || wcslen(m_UIzdesh.mi_EsliSoz)==0)
    {
        if(m_UIzdesh.mi_Cnt==0)
        {
            m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_IZDESH_TEPILMIDI"),MB_OK);
        }
        else
        {
            m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),gUGetVal(L"MSG_IZDESH_TUGIDI"),MB_OK);
        }
    }
    else
    {
        int sozLen=wcslen(m_UIzdesh.mi_EsliSoz);
        int ysozLen=wcslen(m_UIzdesh.mi_OrunbasarSoz);
        wchar_t *esli_Txt=new wchar_t[sozLen+1];
        esli_Txt[0]=0x0;
        wcscpy(esli_Txt,m_UIzdesh.mi_EsliSoz);
        wchar_t *yengi_Txt=NULL;

        yengi_Txt=new wchar_t[ysozLen+1];
        yengi_Txt[0]=0x0;
        wcscpy(yengi_Txt,m_UIzdesh.mi_OrunbasarSoz);

        UINT usul=IDCANCEL;

        while(curPos!=NULL)
        {
            if(usul==TAL_BTN_HEMMNI)
            {
                m_UIzdesh.mi_Cnt++;
                m_USelPos=m_UBuffer.GetPosFromAdress(curPos);

//				wchar_t *delBuf=this->m_UBuffer.Delete(m_USelPos,sozLen);
//				delete[] delBuf;
//				m_UBuffer.Insert(m_USelPos,m_UIzdesh.mi_OrunbasarSoz);

                m_UBuffer.Replace(m_USelPos,sozLen,yengi_Txt,ysozLen);

                wchar_t *_esli=new wchar_t[sozLen+1];
                wchar_t *_yengi=new wchar_t[ysozLen+1];
                wcscpy(_esli,esli_Txt);
                wcscpy(_yengi,yengi_Txt);
                this->UAddUnDO(_esli,_yengi);
                this->m_UTextChanged=TRUE;
                m_USelPos+=ysozLen;
                curPos+=ysozLen;
                m_USelS=m_USelE=m_USelPos;
            }
            else
            {
                m_USelPos=m_UBuffer.GetPosFromAdress(curPos);
                m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
                m_USelS=m_USelPos;
                m_USelE=m_USelPos+sozLen;
                UKorundighanEkran(UEKRAN_XY);
                UInvalidate();
                usul=m_UMsgBox.UShow(mhInstance,m_hWnd,gUGetVal(L"MSG_TAL_TITLE"),gUGetVal(L"MSG_TAL_LAB_ALMASHTURAMSIZ"),MB_YESNOALLSTOP);
                if(usul==IDCANCEL) break;
                if(usul==IDYES||usul==TAL_BTN_HEMMNI)
                {
                    m_UIzdesh.mi_Cnt++;
//					UClearSelection(TRUE);
//					m_UBuffer.Insert(m_USelPos,m_UIzdesh.mi_OrunbasarSoz);

                    m_UBuffer.Replace(m_USelPos,sozLen,yengi_Txt,ysozLen);

                    wchar_t *_esli=new wchar_t[sozLen+1];
                    wchar_t *_yengi=new wchar_t[ysozLen+1];
                    wcscpy(_esli,esli_Txt);
                    wcscpy(_yengi,yengi_Txt);
                    this->UAddUnDO(_esli,_yengi);
                    this->m_UTextChanged=TRUE;
                    m_USelPos+=ysozLen;
                    m_USelS=m_USelE=m_USelPos;
                    curPos+=ysozLen;
                }
                else
                {
                    m_USelPos+=ysozLen;
                    curPos+=sozLen;
                    m_USelS=m_USelE=m_USelPos;
                }
            }
            curPos=UTizmaTap(curPos,m_UIzdesh.mi_EsliSoz,m_UIzdesh.mi_Qandaq);
        }

        if(esli_Txt!=NULL)   delete[] esli_Txt;
        if(yengi_Txt!=NULL) delete[] yengi_Txt;
        m_JemiQurSani=m_UBuffer.UGetJemiyQurSani();
        m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
        UKorundighanEkran(UEKRAN_XY);
        UInvalidate();
        if(m_UIzdesh.mi_Cnt>0)
        {
            wsprintf(_gmsgBuf,L"Jemiy %d tur almashturuldi",m_UIzdesh.mi_Cnt);
            PostMessage(mhWndParent,UM_NOTIFYPARENT,(WPARAM)SHOW_BUFFER_MESSAGE,(LPARAM)FALSE);
        }
    }
}


// Bu Funkitsiye qurBeshida korsitilgen rayondiki , Uzunliqi qurLen Bolghan Uyghurche Herplerni
// Oz-ara Ulap yengi Buffer qilip qayturup beridu.
// Buni chqarghan yerde choqum qayturghan bufferni ishlitip bolgahndin keyin Free qilish kerek
wchar_t *UEditWin::UUlash(wchar_t *qurBeshi,long qurLen,long *newLen)
{
    wchar_t *lineBuf=new wchar_t[qurLen+1];
    wmemmove(lineBuf,qurBeshi,qurLen);
    lineBuf[qurLen]=0x0;

    int rPos,wPos;
    rPos=0;
    wPos=0;

    wchar_t Herp;
    int Index,aldinqiIndex=-1;
    int aldinqiyezilishi=-1;          // Yalghuz yaki Ayaq yezilishi hatirlindu
    bool bashtin=true;

    while(lineBuf[rPos]!=0x00)
    {
        Herp=lineBuf[rPos++];

        Index=gUGetUnicodeIndex(Herp);
        if(Index==-1 )
        {
            lineBuf[wPos++]=Herp;
            bashtin=true;
        }
        else
        {
            if(Index==UYGIN_L && gUGetUnicodeIndex(lineBuf[rPos])==UYGIN_A)
            {
                rPos++;
                Index=UYGIN_LA;
            }

            if (bashtin)
            {
                aldinqiIndex=Index;
                bashtin=false;
                lineBuf[wPos++]=g_Unicode[Index].Code[U_YALGHUZ];
                aldinqiyezilishi=U_YALGHUZ;
            }
            else
            {
                // Aldinqi herpke qoshup yazghili bolamdu tekshuridu
                // Qoshup yazghili bolsa
                if (g_Unicode[aldinqiIndex].Ulinish)
                {
                    // Aldinqi heripning yezilishini ozgertidu yeni
                    // aldinqi heripni ozgertidu
                    if(aldinqiyezilishi==U_YALGHUZ)
                    {
                        lineBuf[wPos-1]=g_Unicode[aldinqiIndex].Code[U_BASH];
                    }
                    else
                    {
                        lineBuf[wPos-1]=g_Unicode[aldinqiIndex].Code[U_OTTURA];
                    }
                    // Hazirqi Herp ayaq yezilishi bolishi kerek
                    lineBuf[wPos++]=g_Unicode[Index].Code[U_AYAQ];
                    aldinqiyezilishi=U_AYAQ;
                }
                else
                {
                    lineBuf[wPos++]=g_Unicode[Index].Code[U_YALGHUZ];
                    aldinqiyezilishi=U_YALGHUZ;                        // Keyinki Haripning Bash yezilishi kerek
                }
                aldinqiIndex=Index;
            }
        }
    }
    lineBuf[wPos]=0x0;
    *newLen=wPos;
    return lineBuf;
}


long UEditWin::UMakeShowBuffer(wchar_t *qurBeshi,long qurLen,wchar_t *selS,wchar_t *selE)
{
    m_UShowLine=new wchar_t[qurLen+1];
    m_USelSt=new char[qurLen+1];
    wmemmove(m_UShowLine,qurBeshi,qurLen);
    m_UShowLine[qurLen]=0x0;
    memset(m_USelSt,0x0,qurLen+1);

    int rPos,wPos;
    rPos=0;
    wPos=0;

    wchar_t Herp;
    int Index,aldinqiIndex=-1;
    int aldinqiyezilishi=-1;          // Yalghuz yaki Ayaq yezilishi hatirlindu
    bool bashtin=true;

    while(m_UShowLine[rPos]!=0x00)
    {
        if(&qurBeshi[rPos]>=selS && &qurBeshi[rPos]<selE)
        {
            m_USelSt[wPos]=0x01;
        }
        Herp=m_UShowLine[rPos++];
        Index=gUGetUnicodeIndex(Herp);
        if(Index==-1 )
        {
            m_UShowLine[wPos++]=Herp;
            bashtin=true;
        }
        else
        {
            if(Index==UYGIN_L && gUGetUnicodeIndex(m_UShowLine[rPos])==UYGIN_A)
            {
                rPos++;
                Index=UYGIN_LA;
            }

            if (bashtin)
            {
                aldinqiIndex=Index;
                bashtin=false;
                m_UShowLine[wPos++]=g_Unicode[Index].Code[U_YALGHUZ];
                aldinqiyezilishi=U_YALGHUZ;
            }
            else
            {
                // Aldinqi herpke qoshup yazghili bolamdu tekshuridu
                // Qoshup yazghili bolsa
                if (g_Unicode[aldinqiIndex].Ulinish)
                {
                    // Aldinqi heripning yezilishini ozgertidu yeni
                    // aldinqi heripni ozgertidu
                    if(aldinqiyezilishi==U_YALGHUZ)
                    {
                        m_UShowLine[wPos-1]=g_Unicode[aldinqiIndex].Code[U_BASH];
                    }
                    else
                    {
                        m_UShowLine[wPos-1]=g_Unicode[aldinqiIndex].Code[U_OTTURA];
                    }
                    // Hazirqi Herp ayaq yezilishi bolishi kerek
                    m_UShowLine[wPos++]=g_Unicode[Index].Code[U_AYAQ];
                    aldinqiyezilishi=U_AYAQ;
                }
                else
                {
                    m_UShowLine[wPos++]=g_Unicode[Index].Code[U_YALGHUZ];
                    aldinqiyezilishi=U_YALGHUZ;                        // Keyinki Haripning Bash yezilishi kerek
                }
                aldinqiIndex=Index;
            }
        }
    }
    m_UShowLine[wPos]=0x0;
    return wPos;
}

void UEditWin::UAbsazni_Sort()
{
    wchar_t *caption=L"UyghurEdit - Abzasni Tizish";
    UINT ret=m_UMsgBox.UShow(mhInstance,m_hWnd,caption,gUGetVal(L"MSG_ABZAS_TIZ"),MB_YESNO);
    if(ret==IDCANCEL) return;
    bool unic=true;
    if(ret==IDNO)unic=false;

    wchar_t *Buffer=new wchar_t[m_UBuffer.GetSize()+1];
    wchar_t *uBuf=m_UBuffer.GetBuffer();
    ULONG wPos=0,rPos=0;
    wchar_t Herp=uBuf[rPos++];
    while(Herp!=0x0)
    {
        if(Herp!=QURBELGISI_Y)
        {
            Buffer[wPos++]=Herp;
        }
        Herp=uBuf[rPos++];
    }
    Buffer[wPos++]=Herp;
    gUSort(Buffer,QURBELGISI_R,unic);

    gSetToClipboard(Buffer);
    UNewUyghurEdit();

    delete[] Buffer;

}


void UEditWin::USetText(wchar_t *Buffer)
{
    ULONG len;
    len=UGetAsasKod(Buffer,m_UBuffer.GetBuffer());
    m_UBuffer.PutSize(len);
    m_VX=0;
    m_VY=0;
    m_HazirqiHerip=0;
    m_esliQur=0;
    m_HazirqiQur=0;
    m_USelPos=0;
    m_USelS=0;
    m_USelE=0;
    m_UFirstLine=NULL;
    UClearSelection(FALSE);
    m_UnReDO->clear();
    m_Alahide=FALSE;
}

void UEditWin::USetSelPos(ULONG Pos)
{
    m_USelPos=Pos;
    m_USelE=m_USelS=m_USelPos;
    m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);

    if(this->m_UEdit.mue_AutoQatlash)
    {
        UOnTizishHemme();
    }
    else
    {
        m_JemiQurSani=m_JemiQurSaniZap;
        m_VX=0;
        m_VY=0;
        UKorundighanEkran(UEKRAN_Y);
        if(m_HazirqiQur>m_BetQurSani)
        {
            m_VY=m_HazirqiQur-m_BetQurSani+1;
        }
        m_UFirstLine=m_UBuffer.GetLine(m_VY);
        /*
        		UINT x=0;
        		UINT y=0;
        		int  HeripKeng[1];
        		wchar_t Herip;
        		HDC dc=GetDC(m_hWnd);
        		m_EngKeng=0;
        		wchar_t *Buf=m_UFirstLine;
        		Herip=*Buf;
        		HeripKeng[0]=0;
        		while(Herip!=0x00 && y<=m_BetQurSani)
        		{
        			if(Herip==QURBELGISI_R || Herip==QURBELGISI_Y)
        			{
        				if(x>m_EngKeng)
        				{
        					m_EngKeng=x;
        				}
        				x=0;
        				y++;
        			}
        			else
        			{
        				x+=UGetHerpKeng(Herip,dc);
        			}
        			Buf++;
        			Herip=*Buf;
        		}
        		ReleaseDC(m_hWnd,dc);*/
    }
    this->UInvalidate();
    this->UShowCaret();
}

ULONG UEditWin::UGetSelPos()
{
    UINT ll=0;
    ULONG curPos=m_UBuffer.GetAbzasInfo(m_USelPos,&ll);
    ULONG yumCnt=0;
    wchar_t *buf=m_UBuffer.GetBuffer();
    ULONG rPos=0;
    while(buf[rPos]!=0x0)
    {
        if(buf[rPos]==QURBELGISI_Y)
        {
            if(rPos<curPos)yumCnt++;
        }
        if(rPos>=curPos)break;
        rPos++;
    }
    return curPos-yumCnt;
}

void UEditWin::UAlahide2Latin()
{
    bool    alahidebar=false;
    wchar_t *Buffer=new wchar_t[m_UBuffer.GetSize()+1];
    wchar_t *uBuf=m_UBuffer.GetBuffer();
    ULONG wPos=0,rPos=0;
    wchar_t Herp=uBuf[rPos++];
    while(Herp!=0x0)
    {
        if(Herp>0xE000 && Herp<0xE0FF)
        {
            Herp=(Herp-0xE000);
            alahidebar=true;
        }
        Buffer[wPos++]=Herp;
        Herp=uBuf[rPos++];
    }
    Buffer[wPos++]=Herp;
    if(alahidebar==true)
    {
        gSetToClipboard(Buffer);
        UNewUyghurEdit();
    }
    delete[] Buffer;
}

void UEditWin::MewhumToUyghur()
{
    CUyghurcheKodAlmashturush tmp_Uka;
    ULONG size=m_UBuffer.GetSize();
    if(size==0) return;
    wchar_t *newBuf=new wchar_t[size*2];
    if(newBuf==NULL) return;
    wchar_t *curBuf=m_UBuffer.GetBuffer();
    UINT  tmpHazirqiQur=m_HazirqiQur;
    UINT  tmpm_VY=m_VY;
    if(tmp_Uka.MewhumToUyghur(curBuf,newBuf))
    {
        this->m_USelS=m_USelE=0;
        this->m_USelE=m_UBuffer.GetSize();
        UChaplaStr(newBuf);
        m_VX=0;
        m_VY=0;
        m_esliQur=0;
        m_HazirqiQur=tmpHazirqiQur;
        m_HazirqiHerip=0;
        m_USelPos=m_UBuffer.GetHerpPosAtYX(m_HazirqiQur, m_HazirqiHerip);
        m_USelS=m_USelPos;
        m_USelE=m_USelPos;
        m_VY=tmpm_VY;
        m_UFirstLine=m_UBuffer.GetLine(m_VY);
    }
    else
    {
        delete[] newBuf;
    }
    this->USetRTL(TRUE);
}

//Uyghurche Kona yeziqta yezilghanni Alhide Latinchigha aylanduridu
void UEditWin::UyghurToMewhum()
{
    CUyghurcheKodAlmashturush tmp_Uka;
    ULONG size=m_UBuffer.GetSize();
    if(size==0) return;
    wchar_t *newBuf=new wchar_t[size*2];
    if(newBuf==NULL) return;
    wchar_t *curBuf=m_UBuffer.GetBuffer();
    tmp_Uka.UyghurToMewhum(curBuf,newBuf);

    UINT  tmpHazirqiQur=m_HazirqiQur;
    UINT  tmpm_VY=m_VY;
    this->m_USelS=m_USelE=0;
    this->m_USelE=m_UBuffer.GetSize();
    UChaplaStr(newBuf);
    m_VX=0;
    m_HazirqiHerip=0;
    m_esliQur=0;
    m_HazirqiQur=tmpHazirqiQur;
    m_USelPos=m_UBuffer.GetHerpPosAtYX(m_HazirqiQur, m_HazirqiHerip);
    m_USelS=m_USelPos;
    m_USelE=m_USelPos;
    m_VY=tmpm_VY;
    m_UFirstLine=m_UBuffer.GetLine(m_VY);
    this->USetRTL(FALSE);
}

//Bu Tallanghan alahide tekistni Uyghurchigha ayalandurup, clipboard qa saqlap beridu.
//Ctrl+B
void UEditWin::Alhide2Uyghurwekochur()
{
    CUyghurcheKodAlmashturush tmp_Uka;
    if(this->UIsTextSelected())
    {
        wchar_t *esliText=UGetSelectionText(TRUE);
        ULONG size=wcslen(esliText);
        if(size==0)
        {
            delete[] esliText;
            return;
        }
        wchar_t *newBuf=new wchar_t[size*2];
        if(newBuf==NULL)
        {
            delete[] esliText;
            return;
        }
        tmp_Uka.MewhumToUyghur(esliText,newBuf);
        gSetToClipboard(newBuf);
        delete[] esliText;
        delete[] newBuf;
    }
}

void UEditWin::UAtalghularniTap()
{
    wchar_t *curPos;
    curPos=m_UBuffer.GetAdressFromPos(m_USelPos);
    curPos=m_UBuffer.GetNextLine(curPos);
    while(curPos!=NULL && (curPos[0]==L'#'||m_UBuffer.GetLineLen(curPos)==0||UAtalghuBarmu(curPos)==FALSE))
    {
        curPos=m_UBuffer.GetNextLine(curPos);
    }
    if(curPos==NULL)
    {
        m_HazirqiHerip=0;
        m_HazirqiQur=this->m_JemiQurSani;
        UCalSelPos();
        m_USelE=m_USelS=m_USelPos;
    }
    else
    {
        m_USelPos=m_UBuffer.GetPosFromAdress(curPos);
    }
    m_USelS=m_USelPos;
    m_USelE=m_USelPos;
    m_UBuffer.GetYXFromPos(m_USelPos,&m_HazirqiQur,&m_HazirqiHerip);
    UKorundighanEkran(UEKRAN_XY);
    UInvalidate();
}
BOOL UEditWin::UAtalghuBarmu(wchar_t *Qur)
{
    BOOL ret=FALSE;
    wchar_t* atalghu[36] = {L"label",L"string",L"widget",L"scroll",L"slide",L"drag",L"indent",L"tooltip",L"custom",L"vertical",
                            L"horizontal",L"margin",L"list",L"offset",L"cursor",L"timeout",L"shortcut",L"program",L"encode",L"decode",L"mount",L"type",
                            L"link",L"dialog",L"instance",L"connect",L"librar",L"version",L"thread",L"process",L"toggl",L"revision",L"commit",L"revert",
                            L"associat",L"theme",
                           } ;
    UINT len=m_UBuffer.GetLineLen(Qur);
    wchar_t *yengiBuf=new wchar_t[len+1];
    wcsncpy(yengiBuf,Qur,len);
    yengiBuf[len]=0x0;
    wcslwr(yengiBuf);
    for(int i=0; i<36; i++)
    {
        if(wcsstr(yengiBuf,atalghu[i])!=NULL)
        {
            ret=TRUE;
            break;
        }
    }
    delete[] yengiBuf;
    return ret;
}

void UEditWin::UGeAylandur(UINT til, YEZIQ yez)
{
    BOOL seltxt=FALSE;
    if(m_UBuffer.GetSize()==0) return;
    wchar_t *esliText=this->m_UBuffer.GetBuffer();
    if (UIsTextSelected())
    {
        seltxt = TRUE;
        esliText=UGetSelectionText(FALSE); //Eslidiki tekistning Yushmaq qayturush belgisini ochurmey kochurdiu
    }
    if(esliText==NULL) return;
    YEZIQ ret = yez;
    if( yez == NODETC)
    {
        ret = DetectYeziq(esliText);
    }
    if(til == BASHQA_UEY)
    {
        if(ret != UEY )
        {
            ToUyghur(seltxt,ret,esliText);
        }
    }
    else if(til == BASHQA_ULY)
    {
        if( ret!= ULY)
        {
            ToLatin(seltxt,ret,esliText);
        }
    }
    else if(til == BASHQA_USY)
    {
        if( ret!=USY)
        {
            ToSlawiyan(seltxt,ret,esliText);
        }
    }
    else if(til == BASHQA_OTY)
    {
        if( ret != OTY)
        {
            ToTurk(seltxt,ret,esliText);
        }
    }
    else if(til == BASHQA_UMY)
    {
        if(ret != UMY)
        {
            ToMewhum(seltxt, ret,esliText);
        }
    }
    if(seltxt)delete[] esliText;
}

YEZIQ UEditWin::DetectYeziq(wchar_t *buf)
{
    wchar_t Herp;
    uint32_t rPos=0;
    uint32_t cntUEY = 0;
    uint32_t cntULY = 0;
    uint32_t cntUSY = 0;
    //uint32_t cntOTY = 0;
    uint32_t cntMUY = 0;
    int      stopChange=0;

    YEZIQ ret = NODETC;

    while(buf[rPos]!=0x0)
    {
        Herp=buf[rPos++];
        if(Herp==NO_CHANGE_START)
        {
            stopChange++;
            continue;
        }
        else if(Herp==NO_CHANGE_END)
        {
            stopChange--;
            if(stopChange<0)stopChange=0;
            continue;
        }
        if(stopChange!=0 || Herp<=0x40 || (Herp>=0x5b && Herp<=0x60) ||(Herp>=0x7b && Herp<=0x7F))
        {
            continue;
        }

        if(Herp>=0x41 && Herp<0x7F)
        {
            cntULY++;
        }
        if(Herp>=0x0600 && Herp<0x067F)
        {
            cntUEY++;
        }
        if(Herp>=0x0400 && Herp<0x047F)
        {
            cntUSY++;
        }
        if(Herp>0xE020 && Herp<0xE0FF)
        {
            cntMUY++;
        }
    }

    if(cntMUY>0 || (cntMUY>cntUEY && cntMUY>cntUSY && cntMUY > cntULY))
    {
        ret = UMY;
    }
    else if(cntUEY>0 || (cntUEY>cntULY && cntUEY>cntUSY && cntUEY > cntMUY))
    {
        ret = UEY;
    }
    else if(cntULY>cntUEY && cntULY>cntUSY && cntULY > cntMUY)
    {
        ret = ULY;
    }
    else if(cntUSY>cntUEY && cntUSY>cntULY && cntUSY > cntMUY)
    {
        ret = USY;
    }
    return ret;
}

//Herqandaq teskitni Uyghur Ereb yeziqigha aylanduridu
//sel == TRUE bolsa, tallanghan rayonnila aylanduridu
void UEditWin::ToUyghur(BOOL sel, YEZIQ hazir, wchar_t *esliText)
{
    wchar_t *bufNew=new wchar_t[wcslen(esliText)*2];
    if(bufNew==NULL) return;
    bufNew[0]=0x0;

    CUyghurcheKodAlmashturush kda;
    if(hazir == UMY)
    {
//        delete[] bufNew;
//        MewhumToUyghur();
//        return;
        kda.MewhumToUyghur(esliText,bufNew);
    }
    else if(hazir == ULY)
    {
        //Uyghur Latin --> Uyghur Ereb
        kda.LatinToUyghur(esliText, bufNew);
    }
    else if(hazir == USY)
    {
        //Uyghur Slawyan --> Uyghur Ereb
        kda.SlawiyanToUyghur(esliText, bufNew);
    }
    else if(hazir == OTY)
    {
        //Ortaq Turk --> Uyghur Ereb
        kda.TurkToUyghur(esliText, bufNew);
    }
    if(bufNew[0]!=0x0)
    {
        if(sel == TRUE)
        {
            UChaplaStr(bufNew);
        }
        else
        {
            gSetToClipboard(bufNew);
            UNewUyghurEdit();
        }
    }
    delete[] bufNew;
}

void UEditWin::ToLatin(BOOL sel, YEZIQ hazir, wchar_t *esliText)
{
    wchar_t *bufNew=new wchar_t[wcslen(esliText)*2];
    if(bufNew==NULL) return;
    bufNew[0]=0x0;

    CUyghurcheKodAlmashturush kda;

    if(hazir == UEY)
    {
        kda.UyghurToLatin(esliText, bufNew);
    }
    else if(hazir == USY)
    {
        kda.SlawiyanToLatin(esliText, bufNew);
    }
    else if(hazir == OTY)
    {
        //      kda.TurkToLatin(esliText, bufNew);
    }
    else if(hazir == UMY)
    {
        kda.MewhumToLatin(esliText,bufNew);
    }
    if(bufNew[0]!=0x0)
    {
        if(sel == TRUE)
        {
            UChaplaStr(bufNew);
        }
        else
        {
            gSetToClipboard(bufNew);
            UNewUyghurEdit();
        }
    }
    delete[] bufNew;
}

void UEditWin::ToSlawiyan(BOOL sel, YEZIQ hazir, wchar_t *esliText)
{
    wchar_t *bufNew=new wchar_t[wcslen(esliText)*2];
    if(bufNew==NULL) return;
    bufNew[0]=0x0;

    CUyghurcheKodAlmashturush kda;

    if(hazir == UEY)
    {
        kda.UyghurToSlawiyan(esliText, bufNew);
    }
    else if(hazir == ULY)
    {
        kda.LatinToSlawyan(esliText, bufNew);
    }
    else if(hazir == OTY)
    {
//        kda.TurkToSlawiyan(esliText, bufNew);
    }
    else if(hazir == UMY)
    {
        //Uyghur Mewhum --> Uyghur Latin
        kda.MewhumToSlawiyan(esliText,bufNew);
    }
    if(bufNew[0]!=0x0)
    {
        if(sel == TRUE)
        {
            UChaplaStr(bufNew);
        }
        else
        {
            gSetToClipboard(bufNew);
            UNewUyghurEdit();
        }
    }
    delete[] bufNew;
}

void UEditWin::ToTurk(BOOL sel,YEZIQ hazir, wchar_t *esliText)
{
#if 0
    wchar_t *bufNew=new wchar_t[wcslen(esliText)*2];
    if(bufNew==NULL) return;

    CUyghurcheKodAlmashturush kda;

    if(hazir == UEY)
    {
        kda.UyghurToTurk(esliText, bufNew);
    }
    else if(hazir == USY)
    {
//        kda.SlawiyanToTurk(esliText, bufNew);
    }
    else if(hazir == ULY)
    {
//        kda.LatinToTurk(esliText, bufNew);
    }
    else if(hazir == MUY)
    {
//        kda.MewhumToTurk(esliText,bufNew);
    }

    if(sel == TRUE)
    {
        UChaplaStr(bufNew);
    }
    else
    {
        gSetToClipboard(bufNew);
        UNewUyghurEdit();
    }
    delete[] bufNew;
#endif //0
}

void UEditWin::ToMewhum(BOOL sel, YEZIQ hazir, wchar_t *esliText)
{
    wchar_t *bufNew=new wchar_t[wcslen(esliText)*2];
    if(bufNew==NULL) return;
    bufNew[0]=0x0;

    CUyghurcheKodAlmashturush kda;
    if(hazir == UEY)
    {
        kda.UyghurToMewhum(esliText,bufNew);
    }
    else if(hazir == ULY)
    {
        kda.LatinToMewhum(esliText, bufNew);
    }
    else if(hazir == USY)
    {
        kda.SlawiyanToMewhum(esliText, bufNew);
    }
    else if(hazir == OTY)
    {
//        kda.TurkToMewhum(esliText, bufNew);
    }
    if(bufNew[0]!=0x0)
    {
        if(sel == TRUE)
        {
            UChaplaStr(bufNew);
        }
        else
        {
            gSetToClipboard(bufNew);
            UNewUyghurEdit();
        }
    }
    delete[] bufNew;
}

void UEditWin::UDelEnter()
{
    wchar_t Herp;
    ULONG   rPos=0;
    if(m_UBuffer.GetSize()==0) return;
    wchar_t *esliText= NULL;
    if (UIsTextSelected())
    {
        esliText=UGetSelectionText(FALSE); //Eslidiki tekistning Yushmaq qayturush belgisini ochurmey kochurdiu
        if(esliText==NULL) return;
        while(true)
        {
            Herp=esliText[rPos];
            if(Herp == 0x0) break;
            if(Herp == QURBELGISI_R)
            {
                esliText[rPos] = QURBELGISI_Y;
            }
            rPos++;
        }
        UChaplaStr(esliText);
        delete[] esliText;
    }
}
