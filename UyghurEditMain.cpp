#define _WIN32_IE 0x0600
#define _WIN32_WINNT	0x0501

#include "UyghurEditMain.h"
#include "RegistryOperation.h"
#include "UyghurcheKodAlmashturush.h"
#include <stdio.h>

extern wchar_t *_resKey[RES_MAX];
extern wchar_t *_resVal[RES_MAX];
extern int     _resCnt;
extern wchar_t _gmsgBuf[256];

extern wchar_t* gUGetVal(wchar_t *Key);
extern HMODULE gLoadImlaDll();
extern Init UInitImla;
extern IsCorrect UIsCorrect;
extern CheckWord UCheckWord;
extern LoadDictionary ULoadDictionary;
extern UnLoadDictionary UUnLoadDictionary;
extern GetCandidateWord UGetCandidateWord;
extern GetOrgWord UGetOrgWord;
extern ShowFindDialog UShowFindDialog;
extern SetUILang USetUILang;

bool showMuqeddime=true;


LRESULT CALLBACK WindowProcedure (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    UyghurEditMain *cMain=(UyghurEditMain*)::GetWindowLong(hwnd,GWL_USERDATA);
    if(cMain!=NULL)
    {
        return cMain->UProcessMessage(hwnd,message,wParam,lParam);
    }
    else
    {
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
}

// Bu Mueqeddime Ramkini Korsitidu
LRESULT CALLBACK Muqeddime( HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam )
{
    static HBITMAP hMuqeddime;
    BITMAP        bm;
    switch( message )
    {
    case WM_INITDIALOG:
    {
        HWND par=::GetParent(hDlg);
        HINSTANCE hIns=(HINSTANCE)GetWindowLong(par,GWL_HINSTANCE);
        hMuqeddime=(HBITMAP)LoadBitmap(hIns,(LPCTSTR)RESIM_ELIPBE);
        GetObject(hMuqeddime,sizeof(BITMAP),&bm);
        gUSetWindowCenter(hDlg,bm.bmWidth,bm.bmHeight);
        ShowWindow(hDlg,1);
        UpdateWindow(hDlg);
        break;
    }
    case WM_PAINT:
    {
        int a;
        RECT rc;
        PAINTSTRUCT ps;
        HDC muDC = BeginPaint (hDlg, &ps);
        SetMapMode(muDC,MM_TEXT);
        GetClientRect(hDlg,&rc);
        HDC memDC=CreateCompatibleDC(muDC);
        SelectObject(memDC,hMuqeddime);
        a=BitBlt(muDC,0,0,rc.right,rc.bottom,memDC,0,0,SRCCOPY);
        DeleteDC(memDC);
        EndPaint(hDlg,&ps);
        Sleep(3000);
        EndDialog(hDlg, LOWORD(wParam));
        return TRUE;
    }
    }
    return FALSE;
}

UyghurEditMain::UyghurEditMain()
{
    _app_ResBuf=NULL;
    _tbSep.iBitmap=0;
    _tbSep.idCommand=0;
    _tbSep.fsState=TBSTATE_ENABLED;
    _tbSep.fsStyle=TBSTYLE_SEP;
    _tbSep.bReserved[0]=0;
    _tbSep.bReserved[1]=0;
    _tbSep.dwData=0;
    _tbSep.iString=0;

    _tbNew.iBitmap=0;
    _tbNew.idCommand=HOJJET_YENGI;
    _tbNew.fsState=TBSTATE_ENABLED;
    _tbNew.fsStyle=TBSTYLE_BUTTON;
    _tbNew.bReserved[0]=0;
    _tbNew.bReserved[1]=0;
    _tbNew.dwData=0;
    _tbNew.iString=0;

    _tbOpen.iBitmap=1;
    _tbOpen.idCommand=HOJJET_ECHISH;
    _tbOpen.fsState=TBSTATE_ENABLED;
    _tbOpen.fsStyle=TBSTYLE_BUTTON;
    _tbOpen.bReserved[0]=0;
    _tbOpen.bReserved[1]=0;
    _tbOpen.dwData=0;
    _tbOpen.iString=0;

    _tbSave.iBitmap=2;
    _tbSave.idCommand=HOJJET_SAQLASH;
    _tbSave.fsState=TBSTATE_ENABLED;
    _tbSave.fsStyle=TBSTYLE_BUTTON;
    _tbSave.bReserved[0]=0;
    _tbSave.bReserved[1]=0;
    _tbSave.dwData=0;
    _tbSave.iString=0;

    _tbPrint.iBitmap=3;
    _tbPrint.idCommand=HOJJET_BESISH;
    _tbPrint.fsState=TBSTATE_ENABLED;
    _tbPrint.fsStyle=TBSTYLE_BUTTON;
    _tbPrint.bReserved[0]=0;
    _tbPrint.bReserved[1]=0;
    _tbPrint.dwData=0;
    _tbPrint.iString=0;

    _tbCut.iBitmap=4;
    _tbCut.idCommand=TEHRIR_KESISH;
    _tbCut.fsState=TBSTATE_ENABLED;
    _tbCut.fsStyle=TBSTYLE_BUTTON;
    _tbCut.bReserved[0]=0;
    _tbCut.bReserved[1]=0;
    _tbCut.dwData=0;
    _tbCut.iString=0;


    _tbCopy.iBitmap=5;
    _tbCopy.idCommand=TEHRIR_KOCHURUSH;
    _tbCopy.fsState=TBSTATE_ENABLED;
    _tbCopy.fsStyle=TBSTYLE_BUTTON;
    _tbCopy.bReserved[0]=0;
    _tbCopy.bReserved[1]=0;
    _tbCopy.dwData=0;
    _tbCopy.iString=0;


    _tbPaste.iBitmap=6;
    _tbPaste.idCommand=TEHRIR_CHAPLASH;
    _tbPaste.fsState=TBSTATE_ENABLED;
    _tbPaste.fsStyle=TBSTYLE_BUTTON;
    _tbPaste.bReserved[0]=0;
    _tbPaste.bReserved[1]=0;
    _tbPaste.dwData=0;
    _tbPaste.iString=0;

    _tbUndo.iBitmap=7;
    _tbUndo.idCommand=TEHRIR_YENIWELISH;
    _tbUndo.fsState=TBSTATE_ENABLED;
    _tbUndo.fsStyle=TBSTYLE_BUTTON;
    _tbUndo.bReserved[0]=0;
    _tbUndo.bReserved[1]=0;
    _tbUndo.dwData=0;
    _tbUndo.iString=0;

    _tbRedo.iBitmap=8;
    _tbRedo.idCommand=TEHRIR_QILISH;
    _tbRedo.fsState=TBSTATE_ENABLED;
    _tbRedo.fsStyle=TBSTYLE_BUTTON;
    _tbRedo.bReserved[0]=0;
    _tbRedo.bReserved[1]=0;
    _tbRedo.dwData=0;
    _tbRedo.iString=0;

    _tbFind.iBitmap=9;
    _tbFind.idCommand=TEHRIR_IZDESH;
    _tbFind.fsState=TBSTATE_ENABLED;
    _tbFind.fsStyle=TBSTYLE_BUTTON;
    _tbFind.bReserved[0]=0;
    _tbFind.bReserved[1]=0;
    _tbFind.dwData=0;
    _tbFind.iString=0;

    _tbFindCon.iBitmap=10;
    _tbFindCon.idCommand=TEHRIR_IZDESH_DAWAMLASHTURUSH;
    _tbFindCon.fsState=TBSTATE_ENABLED;
    _tbFindCon.fsStyle=TBSTYLE_BUTTON;
    _tbFindCon.bReserved[0]=0;
    _tbFindCon.bReserved[1]=0;
    _tbFindCon.dwData=0;
    _tbFindCon.iString=0;

    _tbSpel.iBitmap=11;
    _tbSpel.idCommand=BASHQA_IMLA;
    _tbSpel.fsState=TBSTATE_ENABLED;
    _tbSpel.fsStyle=TBSTYLE_BUTTON;
    _tbSpel.bReserved[0]=0;
    _tbSpel.bReserved[1]=0;
    _tbSpel.dwData=0;
    _tbSpel.iString=0;


    _tbUEY.iBitmap=12;
    _tbUEY.idCommand=BASHQA_UEY;
    _tbUEY.fsState=TBSTATE_ENABLED;
    _tbUEY.fsStyle=TBSTYLE_BUTTON;
    _tbUEY.bReserved[0]=0;
    _tbUEY.bReserved[1]=0;
    _tbUEY.dwData=0;
    _tbUEY.iString=0;

    _tbULY.iBitmap=13;
    _tbULY.idCommand=BASHQA_ULY;
    _tbULY.fsState=TBSTATE_ENABLED;
    _tbULY.fsStyle=TBSTYLE_BUTTON;
    _tbULY.bReserved[0]=0;
    _tbULY.bReserved[1]=0;
    _tbULY.dwData=0;
    _tbULY.iString=0;

    _tbUSY.iBitmap=14;
    _tbUSY.idCommand=BASHQA_USY;
    _tbUSY.fsState=TBSTATE_ENABLED;
    _tbUSY.fsStyle=TBSTYLE_BUTTON;
    _tbUSY.bReserved[0]=0;
    _tbUSY.bReserved[1]=0;
    _tbUSY.dwData=0;
    _tbUSY.iString=0;

    _tbUMY.iBitmap=15;
    _tbUMY.idCommand=BASHQA_UMY;
    _tbUMY.fsState=TBSTATE_ENABLED;
    _tbUMY.fsStyle=TBSTYLE_BUTTON;
    _tbUMY.bReserved[0]=0;
    _tbUMY.bReserved[1]=0;
    _tbUMY.dwData=0;
    _tbUMY.iString=0;

    _tbRTL.iBitmap=16;
    _tbRTL.idCommand=BASHQA_SOLDINONG;
    _tbRTL.fsState=TBSTATE_ENABLED;
    _tbRTL.fsStyle=TBSTYLE_BUTTON;
    _tbRTL.bReserved[0]=0;
    _tbRTL.bReserved[1]=0;
    _tbRTL.dwData=0;
    _tbRTL.iString=0;

    _tbTIZ.iBitmap=17;
    _tbTIZ.idCommand=BASHQA_TIZISHHEMME;
    _tbTIZ.fsState=TBSTATE_ENABLED;
    _tbTIZ.fsStyle=TBSTYLE_BUTTON;
    _tbTIZ.bReserved[0]=0;
    _tbTIZ.bReserved[1]=0;
    _tbTIZ.dwData=0;
    _tbTIZ.iString=0;


    mhImla=NULL;
    UInitImla=NULL;
    UIsCorrect=NULL;
    UCheckWord=NULL;
    ULoadDictionary=NULL;
    UUnLoadDictionary=NULL;
    UGetCandidateWord=NULL;
    UGetOrgWord=NULL;
    UShowFindDialog=NULL;
    USetUILang=NULL;
    m_Izlar.m_IzSani=0;

    showMuqeddime=true;

//	set_new_handler(no_memory);
}

UyghurEditMain::~UyghurEditMain()
{
    if(_app_ResBuf!=NULL) delete[] _app_ResBuf;
    ::DestroyWindow( _ghStatusBar );
    ::DestroyWindow(_ghToolBar);
    if(mhImla!=NULL) FreeLibrary(mhImla);
    CRegistryOperation op;
    op.SetIzlar(&m_Izlar);
}


LRESULT UyghurEditMain::UProcessMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    BOOL ret=FALSE;
    switch (message)                  /* handle the messages */
    {
    case WM_ACTIVATE:
    {
        UINT st = (UINT) LOWORD(wParam);
        if(WA_ACTIVE==st || WA_CLICKACTIVE==st)
        {
            SetFocus(_ghEditWin);
        }
    }
    break;
    case WM_DESTROY:
        PostQuitMessage (0);       /* send a WM_QUIT to the message queue */
        ret=TRUE;
        break;
    case WM_CLOSE:
        if(UOnClose()==TRUE)
        {
            DestroyWindow(hwnd);
        }
        ret=FALSE;
        break;
    case WM_SIZE:
        UOnSize(wParam,lParam);
        ret=TRUE;
        break;
    case WM_COMMAND:
        UProcessCommand(hwnd,wParam,lParam);
        ret=TRUE;
        break;
    case WM_INITMENUPOPUP:
        USetMenu_ToolStatus();
        ret=TRUE;
        break;
    case WM_SETFOCUS:
        ret=FALSE;
        break;
    case UM_WINDOWCLOSED:
    {
        UINT id=(UINT)wParam;
        if(id==IDD_ABOUTBOX)
        {
            if(_About!=NULL)
            {
                delete _About;
                _About=NULL;
            }
        }
        else if(id==IDD_KUNUPKA)
        {
            if(_Kunupka!=NULL)
            {
                delete _Kunupka;
                _Kunupka=NULL;
            }
        }
        else if(id==IDD_ELIPBE)
        {
            if(_Elipbe!=NULL)
            {
                delete _Elipbe;
                _Elipbe=NULL;
            }
        }
        ret=TRUE;
        break;
    }
    case WM_MENUSELECT:
        if( NULL != _ghStatusBar )
        {
            UINT uItem = (UINT) LOWORD(wParam);
            UShowMenuHelp(uItem);
        }
        ret=TRUE;
        break;
    case  UM_NOTIFYPARENT:
    {
        BOOL par=(BOOL)lParam;
        if(par)
        {
            UNOTIFY *par=(UNOTIFY*)wParam;
            if( NULL != _ghStatusBar )
            {
                wchar_t QurSton[100];
                wchar_t Unicode[100];
                wchar_t Kunupka[100];
                wchar_t *Insert;

                wsprintf(Unicode,L"U%04X",par->Herp);
                wsprintf(QurSton,gUGetVal(L"MSG_LINE_COL"),par->Qur,par->Ston);

                if(par->Kunupka==KUNUPKA_SYSTEM)
                {
                    wsprintf(Kunupka,L"System");
                }
                else if(par->Kunupka==KUNUPKA_LATIN)
                {
                    wsprintf(Kunupka,L"Uyghurche");
                }
                else if(par->Kunupka==KUNUPKA_UYGHUR)
                {
                    wsprintf(Kunupka,L"ئۇيغۇرچە");
                }
                else if(par->Kunupka==KUNUPKA_ALAHIDE)
                {
                    wsprintf(Kunupka,L"Mewhum");
                }

                if(par->Qisturush)
                {
                    Insert=gUGetVal(L"MSG_INSERT");
                }
                else
                {
                    Insert=gUGetVal(L"MSG_WRITE");
                }
                SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 5,(LPARAM)Kunupka);
                SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 3,(LPARAM)Insert);
                SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 2,(LPARAM)Unicode);
                SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 1,(LPARAM)QurSton);
            }
        }
        else
        {
            UINT msgID=(UINT)wParam;
            wchar_t *mnText=NULL;
            if(msgID==SHOW_BUFFER_MESSAGE)
            {
                mnText=_gmsgBuf;
                SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM)0,(LPARAM)mnText);
            }
            else if(msgID==SHOW_ATHOR)
            {
                mnText=UYGHUREDIT_VERSION;
                SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM)0,(LPARAM)mnText);
            }
            else
            {
                switch(msgID)
                {
                case CP_ACP:
                    mnText=L"System";
                    break;
                case CP_BOGHDA:
                    mnText=L"Boghda";
                    break;
                case CP_WEIDOS:
                    mnText=L"Weifang Dos";
                    break;
                case CP_WEIWIN:
                    mnText=L"Weifang Windows";
                    break;
                case CP_UTF16LE:
                    mnText=L"Unicode (LE)";
                    break;
                case CP_UTF16BE:
                    mnText=L"Unicode(BE)";
                    break;
                case CP_UTF8:
                    mnText=L"Unicode (UTF8)";
                    break;
                case CP_UTF7:
                    mnText=L"Unicode  (UTF7)";
                    break;
                case CP_1252:
                    mnText=L"";
                    break;
                case CP_1250:
                    mnText=L"";
                    break;
                case CP_932:
                    mnText=L"";
                    break;
                case CP_JEUC:
                    mnText=L"";
                    break;
                case CP_936:
                    mnText=L"";
                    break;
                case CP_950:
                    mnText=L"";
                    break;
                case CP_1251:
                    mnText=L"";
                    break;
                case CP_1253:
                    mnText=L"";
                    break;
                case CP_1254:
                    mnText=L"";
                    break;
                case CP_1255:
                    mnText=L"";
                    break;
                case CP_1256:
                    mnText=L"";
                    break;
                case CP_1257:
                    mnText=L"";
                    break;
                }
                SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM)4,(LPARAM)mnText);
            }
        }
        UUpdateStatusbar();
        USetMenu_ToolStatus();
    }
    ret=TRUE;
    break;
    case WM_NOTIFY:
        UProcessNotify(wParam, lParam);
        ret=FALSE;
        break;
    case WM_DROPFILES:
        UHojjetTashlandi(wParam, lParam);
        ret=TRUE;
        break;
    case WM_DRAWITEM:
        UDrawItem(wParam, lParam);
        ret=TRUE;
        break;
    case WM_MEASUREITEM:
        UMeasureItem(wParam, lParam);
        ret=TRUE;
        break;
    case WM_PRINTCLIENT:
    case WM_PRINT:
//		   m_UMsgBox.UShow(_gHInstance,_ghWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),L"Keldi",MB_OK);
        break;
    case WM_RBUTTONDOWN:
//		   m_UMsgBox.UShow(_gHInstance,_ghWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),L"Keldi",MB_OK);
        break;
    case WM_PARENTNOTIFY:
        if(LOWORD(wParam)==WM_LBUTTONDOWN)
        {
//                RECT windowRect;
//                GetWindowRect(_ghStatusBar, &windowRect );
//                int x=LOWORD(lParam);
//                int y=HIWORD(lParam);
//                POINT cursorPos = { x, y };
//                ScreenToClient(_ghStatusBar,&cursorPos);
//				ClientToScreen(_ghStatusBar, &cursorPos);
//                if(PtInRect(&windowRect, cursorPos )){
//                    m_UMsgBox.UShow(_gHInstance,_ghWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),L"Keldi",MB_OK);
//                }
        }
        break;
    default:
#ifdef _DEBUG
//		   _trace(L"Keldi : Uchur=%4X\n", message);
#endif
        return DefWindowProc (hwnd, message, wParam, lParam);
    }
    return ret;
}

void UyghurEditMain::UCreateStatusPane()
{
    RECT rc;
    GetClientRect(_ghStatusBar,&rc);
    int width=rc.right-16;
    int w[]= {0,0,0,0,0,0};

    w[5]=width;
    wchar_t *def=L"UTF-8";
    HDC hdc=GetDC(_ghStatusBar);
    if(hdc!=NULL)
    {
        SIZE sz;
        GetTextExtentPoint32(hdc,def,wcslen(def),&sz);
        w[4]=width-(sz.cx+3);
        w[3]=w[4]-(sz.cx-10);
        w[2]=w[3]-(sz.cx-20);
        w[1]=w[2]-(sz.cx-20);
        w[0]=w[1]-sz.cx;
        ReleaseDC(_ghStatusBar,hdc);
    }

    SendMessage(_ghStatusBar,SB_SETUNICODEFORMAT,(WPARAM)TRUE,(LPARAM)0x0);
    SendMessage (_ghStatusBar, SB_SETPARTS, (WPARAM) 6, (LPARAM)w);
    SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 5,(LPARAM)def);
    SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 4,(LPARAM)def);
    SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 3,(LPARAM)def);
    SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 2,(LPARAM)def);
    SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 1,(LPARAM)def);
}

void UyghurEditMain::UUpdateStatusbar()
{
    RECT rc;
    GetClientRect(_ghStatusBar,&rc);
    int width=rc.right-10;
    int w[]= {0,0,0,0,0,0};
    w[5]=width;

    wchar_t sbText1[100];
    wchar_t sbText2[100];
    wchar_t sbText3[100];
    wchar_t sbText4[100];
    wchar_t sbText5[100];

    sbText1[0]=0x0;
    sbText2[0]=0x0;
    sbText3[0]=0x0;
    sbText4[0]=0x0;
    sbText5[0]=0x0;

    HFONT hFont=HFONT(SendMessage(_ghStatusBar,WM_GETFONT,0,0));
//	if(hFont==NULL)hFont=HFONT(GetStockObject(SYSTEM_FONT));
    HDC hdc=GetDC(_ghStatusBar);
    if(hdc!=NULL)
    {
        SIZE sz;
        hFont=HFONT(SelectObject(hdc,hFont));

        SendMessage(_ghStatusBar,SB_GETTEXT,(WPARAM)5,(LPARAM)sbText5);
        GetTextExtentPoint32(hdc,sbText5,wcslen(sbText5),&sz);
        w[4]=width-(sz.cx+18);

        SendMessage(_ghStatusBar,SB_GETTEXT,(WPARAM)4,(LPARAM)sbText4);
        GetTextExtentPoint32(hdc,sbText4,wcslen(sbText4),&sz);
        w[3]=w[4]-(sz.cx+8);

        SendMessage(_ghStatusBar,SB_GETTEXT,(WPARAM)3,(LPARAM)sbText3);
        GetTextExtentPoint32(hdc,sbText3,wcslen(sbText3),&sz);
        w[2]=w[3]-(sz.cx+8);

        SendMessage(_ghStatusBar,SB_GETTEXT,(WPARAM)2,(LPARAM)sbText2);
        GetTextExtentPoint32(hdc,sbText2,wcslen(sbText2),&sz);
        w[1]=w[2]-(sz.cx+8);

        SendMessage(_ghStatusBar,SB_GETTEXT,(WPARAM)1,(LPARAM)sbText1);
        GetTextExtentPoint32(hdc,sbText1,wcslen(sbText1),&sz);
        w[0]=w[1]-(sz.cx+8);

        hFont=HFONT(SelectObject(hdc,hFont));
        ReleaseDC(_ghStatusBar,hdc);
    }
    SendMessage (_ghStatusBar, SB_SETPARTS, (WPARAM) 6, (LPARAM)w);
    SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 5,(LPARAM)sbText5);
    SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 4,(LPARAM)sbText4);
    SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 3,(LPARAM)sbText3);
    SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 2,(LPARAM)sbText2);
    SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM) 1,(LPARAM)sbText1);
}




void UyghurEditMain::UProcessNotify(WPARAM wp, LPARAM lp)
{
    BOOL isSel = _pEditWin->UIsTextSelected();
    LPNMHDR par = (LPNMHDR)lp;
    UINT code = par->code;
    if (wp == UM_WINDOWSTATUS)
    {
#ifdef _DEBUG
        _trace(L"wparam = %4x, Code=%4X, idfrom=%4x\n", wp, par->code, par->idFrom);
#endif
    }
    else
    {
        switch (code)
        {
        case TTN_GETDISPINFO:
        {
            LPTOOLTIPTEXT lpttt;
            lpttt = (LPTOOLTIPTEXT)lp;
            lpttt->hinst = _gHInstance;
            UINT idButton = lpttt->hdr.idFrom;
            switch (idButton)
            {
            case HOJJET_YENGI:
                lpttt->lpszText = gUGetVal(L"MSG_HOJJET_YENGI");
                break;
            case HOJJET_ECHISH:
                lpttt->lpszText = gUGetVal(L"MSG_HOJJET_ECHISH");
                break;
            case HOJJET_SAQLASH:
                lpttt->lpszText = gUGetVal(L"MSG_HOJJET_SAQLASH");
                break;
            case HOJJET_BESISH:
                lpttt->lpszText = gUGetVal(L"MSG_HOJJET_BESISH");
                break;
            case TEHRIR_YENIWELISH:
                lpttt->lpszText = gUGetVal(L"MSG_TEHRIR_YENIWELISH");
                break;
            case TEHRIR_QILISH:
                lpttt->lpszText = gUGetVal(L"MSG_TEHRIR_QILISH");
                break;
            case TEHRIR_KOCHURUSH:
                lpttt->lpszText = gUGetVal(L"MSG_TEHRIR_KOCHURUSH");
                break;
            case TEHRIR_CHAPLASH:
                lpttt->lpszText = gUGetVal(L"MSG_TEHRIR_CHAPLASH");
                break;
            case TEHRIR_KESISH:
                lpttt->lpszText = gUGetVal(L"MSG_TEHRIR_KESISH");
                break;
            case TEHRIR_IZDESH:
                lpttt->lpszText = gUGetVal(L"MSG_TEHRIR_IZDESH");
                break;
            case TEHRIR_IZDESH_DAWAMLASHTURUSH:
                lpttt->lpszText = gUGetVal(L"MSG_TEHRIR_IZDESH_DAWAMLASHTURUSH");
                break;
            case BASHQA_IMLA:
                lpttt->lpszText = gUGetVal(L"MSG_BASHQA_IMLA");
                break;
            case BASHQA_UEY:
                if(isSel)
                {
                    lpttt->lpszText = gUGetVal(L"MSG_BASHQA_UEY_SEL");
                }
                else
                {
                    lpttt->lpszText = gUGetVal(L"MSG_BASHQA_UEY");
                }
                break;
            case BASHQA_ULY:
                if(isSel)
                {
                    lpttt->lpszText = gUGetVal(L"MSG_BASHQA_ULY_SEL");
                }
                else
                {
                    lpttt->lpszText = gUGetVal(L"MSG_BASHQA_ULY");
                }
                break;
            case BASHQA_USY:
                if(isSel)
                {
                    lpttt->lpszText = gUGetVal(L"MSG_BASHQA_USY_SEL");
                }
                else
                {
                    lpttt->lpszText = gUGetVal(L"MSG_BASHQA_USY");
                }
                break;
            case BASHQA_OTY:
                if(isSel)
                {
                    lpttt->lpszText = gUGetVal(L"MSG_BASHQA_OTY_SEL");
                }
                else
                {
                    lpttt->lpszText = gUGetVal(L"MSG_BASHQA_OTY");
                }
                break;
            case BASHQA_UMY:
                if(isSel)
                {
                    lpttt->lpszText = gUGetVal(L"MSG_BASHQA_UMY_SEL");
                }
                else
                {
                    lpttt->lpszText = gUGetVal(L"MSG_BASHQA_UMY");
                }
                break;
            case BASHQA_SOLDINONG:
                lpttt->lpszText = gUGetVal(L"MSG_BASHQA_RTL");
                break;
            case BASHQA_TIZISHHEMME:
                lpttt->lpszText = gUGetVal(L"MSG_BASHQA_TIZISHHEMME");
                break;
            }
        }
        break;
        default:
            break;
        }
    }
}



int UyghurEditMain::UShowAgahlandurush(wchar_t *msgKey,UINT mb)
{
    return m_UMsgBox.UShow(_gHInstance,_ghWnd,gUGetVal(L"MSG_CAPTION"),gUGetVal(msgKey),mb);
}


BOOL UyghurEditMain::UInit(HINSTANCE hThisInstance)
{
    WNDCLASSEX wincl;        /* Data structure for the windowclass */
    _gHInstance=hThisInstance;
    TCHAR szClassName[] = UYGHUREDIT_NAME;

    /* The Window structure */
    wincl.hInstance = _gHInstance;
    wincl.lpszClassName = szClassName;
    wincl.lpfnWndProc = WindowProcedure;
    wincl.style = CS_DBLCLKS;
    wincl.cbSize = sizeof (WNDCLASSEX);

    wincl.hIcon = LoadIcon (NULL, IDI_APPLICATION);
    wincl.hIcon = LoadIcon(_gHInstance, MAKEINTRESOURCE(IDR_UYGHUREDITICO));
    wincl.hIconSm= LoadIcon(_gHInstance, MAKEINTRESOURCE(IDR_UYGHUREDITICO_S));
    wincl.hCursor = LoadCursor (NULL, IDC_ARROW);
    wincl.lpszMenuName = TEXT("IDM_UYGHUREDIT");
    wincl.cbClsExtra = 0;
    wincl.cbWndExtra = 0;
    wincl.hbrBackground    = (HBRUSH)GetStockObject(WHITE_BRUSH);

    if (!RegisterClassEx (&wincl))
    {
        MessageBox(NULL, TEXT("Can not register UyghurEdit class"), TEXT("Error"), MB_OK | MB_ICONINFORMATION);
        return FALSE;
    }
    _ghWnd = CreateWindowEx (
                 WS_EX_ACCEPTFILES,                   /* Extended possibilites for variation */
                 szClassName,         /* Classname */
                 UYGHUREDIT_NAME,       /* Title Text */
                 WS_OVERLAPPEDWINDOW, /* default window */
                 CW_USEDEFAULT,       /* Windows decides the position */
                 CW_USEDEFAULT,       /* where the window ends up on the screen */
                 1024,                 /* The programs width */
                 720,                 /* and height in pixels */
                 HWND_DESKTOP,        /* The window is a child-window to desktop */
                 NULL,                /* No menu */
                 _gHInstance,       /* Program Instance handler */
                 NULL                 /* No Window Creation data */
             );

    if(_ghWnd==NULL)
    {
        MessageBox(NULL, TEXT("Can not create Main Window"), TEXT("Error"), MB_OK | MB_ICONINFORMATION);
        return FALSE;
    }
    DragAcceptFiles(_ghWnd, TRUE);

    _pEditWin=new UEditWin(_gHInstance,_ghWnd);
    _ghEditWin=_pEditWin->UCreate();
    if(_ghEditWin==NULL)return FALSE;

    CRegistryOperation op;
    op.GetIzlar(&m_Izlar);

    UINTERFACE_LANG lang=_pEditWin->UGetInterfaceLang();
    UINT ResID=IDR_RES_ULY;
    if(lang==LANG_JPN)
    {
        ResID=IDR_RES_JPN;
    }
    else if(lang==LANG_ENG)
    {
        ResID=IDR_RES_ENG;
    }
    else if(lang==LANG_CHN)
    {
        ResID=IDR_RES_CHN;
    }
    else if(lang==LANG_UEY)
    {
        ResID=IDR_RES_UEY;
    }
    else if(lang==LANG_USY)
    {
        ResID=IDR_RES_USY;
    }
    else if(lang==LANG_GER)
    {
        ResID=IDR_RES_GER;
    }

    _resCnt=UGetLangResource(ResID);
    ::SetWindowLong( _ghWnd, GWL_USERDATA, (LONG)this );

    INITCOMMONCONTROLSEX icex;
    icex.dwSize = sizeof(INITCOMMONCONTROLSEX);
    icex.dwICC	= ICC_COOL_CLASSES|ICC_BAR_CLASSES;
    InitCommonControlsEx(&icex);
    _ghStatusBar=CreateStatusWindow(WS_CHILD|WS_VISIBLE|SBARS_SIZEGRIP,UYGHUREDIT_VERSION,_ghWnd,UM_WINDOWSTATUS);
    UCreateStatusPane();

    UCreateToolBar();
    SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_KUNUPKA_KONA,0);
    USetWindowsTitle();
    USetMenu_ToolStatus();
    mhImla=gLoadImlaDll();
    if(USetUILang!=NULL)
    {
        USetUILang(lang);
    }
    USetWindowLayout(lang);
    _UCaption.UInstall(_gHInstance,_ghWnd,_pEditWin->UGetKunupka(),lang);
    return TRUE;
}

void UyghurEditMain::USetFileName(wchar_t *fileNm,ULONG tPos)
{
    wchar_t fileName[MAX_PATH];
    wmemset(fileName,0x0,MAX_PATH);

    int rPos,wPos;
    rPos=0;
    wPos=0;
    wchar_t Herp=fileNm[rPos];
    while(Herp!=0x0)
    {
        Herp=fileNm[rPos++];
        if(Herp=='"')continue;
        fileName[wPos++]=Herp;
    }
    fileName[wPos]=0x0;
    _pEditWin->USetFileName(fileName);
    int i;


    CRegistryOperation op;
    op.GetIzlar(&m_Izlar);

    for(i=m_Izlar.m_IzSani; i>0; i--)
    {
        wcscpy(m_Izlar.m_IzNami[i],m_Izlar.m_IzNami[i-1]);
        m_Izlar.m_IzPos[i]=m_Izlar.m_IzPos[i-1];
    }
    wcscpy(m_Izlar.m_IzNami[0],fileName);
    m_Izlar.m_IzPos[0]=tPos;

    bool find=false;
    for(i=1; i<=m_Izlar.m_IzSani; i++)
    {
        if(wcscmp(fileName,m_Izlar.m_IzNami[i])==0)
        {
            find=true;
            break;
        }
    }
    if(find)
    {
        int st=i;
        m_Izlar.m_IzPos[0]=m_Izlar.m_IzPos[st];
        for(i=st; i<=m_Izlar.m_IzSani; i++)
        {
            wcscpy(m_Izlar.m_IzNami[i],m_Izlar.m_IzNami[i+1]);
            m_Izlar.m_IzPos[i]=m_Izlar.m_IzPos[i+1];
        }
    }
    else
    {
        m_Izlar.m_IzSani++;
        if(m_Izlar.m_IzSani>=MAX_IZ_SANI)
        {
            m_Izlar.m_IzSani=MAX_IZ_SANI;
        }
    }
    USetIzMenu();
    op.SetIzlar(&m_Izlar);
}

void UyghurEditMain::USetIzMenu()
{
    // Bu Yerdin Bashlap Bash Menuni Ozgertidu
    HMENU hMenu=::GetMenu(_ghWnd);
    if(hMenu==NULL) return;
    HMENU subMenu=GetSubMenu(hMenu,0);
    subMenu=GetSubMenu(subMenu,9);
    if(subMenu==NULL) return;
    UINT styC=MF_STRING|MF_BYPOSITION;
    int i;
    for(i=0; i<m_Izlar.m_IzSani; i++)
    {
        DeleteMenu(subMenu,0,styC);
    }

    for(i=0; i<m_Izlar.m_IzSani; i++)
    {
        InsertMenu(subMenu,i,styC,HOJJET_IZ+i,m_Izlar.m_IzNami[i]);
    }
}

void UyghurEditMain::UCreateToolBar()
{
    TBBUTTON btns[27];
    btns[0]=_tbNew;
    btns[1]=_tbOpen;
    btns[2]=_tbSave;
    btns[3]=_tbSep;
    btns[4]=_tbPrint;
    btns[5]=_tbSep;
    btns[6]=_tbCut;
    btns[7]=_tbCopy;
    btns[8]=_tbPaste;
    btns[9]=_tbSep;
    btns[10]=_tbUndo;
    btns[11]=_tbRedo;
    btns[12]=_tbSep;
    btns[13]=_tbFind;
    btns[14]=_tbFindCon;
    btns[15]=_tbSep;
    btns[16]=_tbSpel;
    btns[17]=_tbSep;
    btns[18]=_tbUEY;
    btns[19]=_tbULY;
    btns[20]=_tbUSY;
    btns[21]=_tbSep;
    btns[22]=_tbUMY;
    btns[23]=_tbSep;
    btns[24]=_tbRTL;
    btns[25]=_tbSep;
    btns[26]=_tbTIZ;

    // Rebar Yasash

    REBARINFO     rbi;
    REBARBANDINFO rbBand;
    RECT  rcToolBar;

    //  レバーコントロールの作成
    _ghRebar =::CreateWindowExW(WS_EX_CLIENTEDGE,TEXT("ReBarWindow32"), NULL,WS_CHILD | WS_VISIBLE | WS_CLIPSIBLINGS | WS_BORDER |WS_CLIPCHILDREN | RBS_VARHEIGHT | CCS_NODIVIDER|RBS_BANDBORDERS|CCS_NODIVIDER|CCS_NOPARENTALIGN,0,0,200,100, _ghWnd,NULL, _gHInstance, NULL );

    rbi.cbSize = sizeof( REBARINFO );
    rbi.fMask  = 0;
    rbi.himl   = (HIMAGELIST)NULL;
    SendMessage( _ghRebar, RB_SETBARINFO, 0, (LPARAM)&rbi);

    _ghToolBar=CreateToolbarEx(_ghWnd,WS_CHILD|CCS_NOPARENTALIGN|CCS_NORESIZE|CCS_NODIVIDER|TBSTYLE_FLAT|TBSTYLE_TOOLTIPS,UM_WINDOWTOOLBAR,17,_gHInstance,IDR_TOOLBAR,btns,27,33,18,33,18,sizeof(TBBUTTON));

#if WINVER >= 0x0600
    rbBand.cbSize = 80;//sizeof( REBARBANDINFO );
#else
    rbBand.cbSize = sizeof( REBARBANDINFO );
#endif
    rbBand.fMask  = RBBIM_STYLE |RBBIM_CHILDSIZE |RBBIM_SIZE |RBBIM_CHILD |RBBIM_ID;
    rbBand.fStyle = RBBS_CHILDEDGE |RBBS_GRIPPERALWAYS;
    GetWindowRect( _ghToolBar, &rcToolBar );
    rbBand.wID		  = IDR_TOOLBAR;
    rbBand.hwndChild  = _ghToolBar;
    rbBand.cxMinChild = 0;
    rbBand.cyMinChild = 24;
    rbBand.cx		  = rcToolBar.right - rcToolBar.left;
    SendMessage(_ghRebar, RB_INSERTBAND, (WPARAM)-1, (LPARAM)&rbBand);
}

BOOL UyghurEditMain::UOnSize(WPARAM wParam, LPARAM lParam)
{
    int nWidth = LOWORD(lParam);  // クライアント領域の幅
//    int nHeight= HIWORD(lParam);

    RECT rc;
    RECT rcTool;
    RECT rcStatus;
    ::GetClientRect(_ghWnd,&rc);
    ::GetWindowRect(_ghRebar,&rcTool);
    ::GetWindowRect(_ghStatusBar,&rcStatus);

    int toolH=rcTool.bottom-rcTool.top;
    int statusH=rcStatus.bottom-rcStatus.top;
    int x=0;
    int y=toolH;
    int height=rc.bottom-(toolH+statusH);
    /*	::MoveWindow(_ghToolBar,0,0,rc.right,toolH,TRUE);
    	::MoveWindow(_ghEditWin,x,y,width,height,TRUE);
    	::MoveWindow(_ghStatusBar,0,rc.bottom-statusH,rc.right,statusH,TRUE);*/

    HDWP hdwp;
    hdwp = BeginDeferWindowPos (3);
    DeferWindowPos (hdwp, _ghRebar, NULL, 0, 0, nWidth, toolH, SWP_NOZORDER);
    DeferWindowPos (hdwp, _ghEditWin, NULL, x, y, nWidth, height, SWP_NOZORDER);
    DeferWindowPos (hdwp, _ghStatusBar, NULL, 0, rc.bottom-statusH, nWidth, statusH, SWP_NOZORDER);
    EndDeferWindowPos (hdwp);
    return TRUE;
}


void UyghurEditMain::UShowWindow(int val)
{
    if(_resCnt>0)
    {
        USetMenuText();
    }
    ShowWindow(_ghWnd, val);
    UpdateWindow(_ghWnd);
    if(showMuqeddime)
    {
        _pEditWin->UBeginWaitCursor();
        DialogBox(_gHInstance, MAKEINTRESOURCE(IDD_MUQEDDIME), _ghWnd, (DLGPROC)Muqeddime);
        _pEditWin->UEndWaitCursor();
    }
}

int UyghurEditMain::URun(LPSTR lpszArgument)
{
    MSG msg;
    HACCEL hAccelTable;

    wchar_t *fileName=gUGetUnicodeBuf(CP_ACP,lpszArgument);
    if(fileName!=NULL && wcslen(fileName)!=0)
    {
        if(wcscmp(fileName,L"-new")==0)
        {
            showMuqeddime=false;
            this->USetIzMenu();
        }
        else if(wcscmp(fileName,L"-clipboard")==0)
        {
            showMuqeddime=false;
            PostMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)TEHRIR_CHAPLASH,0);
            this->USetIzMenu();
        }
        else
        {
            USetFileName(fileName,0);
            UReadFromCodePage(CP_ACP);
        }
        delete[] fileName;
    }
    else
    {
        this->USetIzMenu();
    }

    hAccelTable = LoadAccelerators(_gHInstance, TEXT("IDR_ACCEL"));
    while (GetMessage (&msg, NULL, 0, 0))
    {
        if( !TranslateAccelerator (msg.hwnd, hAccelTable, &msg) )
        {
            /* Translate virtual-key messages into character messages */
            TranslateMessage(&msg);
            /* Send message to WindowProcedure */
            DispatchMessage(&msg);
        }
    }

    if(_pEditWin!=NULL) delete _pEditWin;
    return msg.wParam;
}

void UyghurEditMain::UShowKunupka()
{
    wchar_t *mnText;
    mnText=gUGetVal(L"MSG_TITLEKUNUPKA");
    _Kunupka=new CDialog(mnText);
    HBITMAP hbm=(HBITMAP)LoadBitmap(_gHInstance,MAKEINTRESOURCE(RESIM_KUNUPKA));
    _Kunupka->SetBitmap(hbm);
    _Kunupka->DoModeless(_gHInstance,_ghWnd,IDD_KUNUPKA,SW_SHOW);
}
void UyghurEditMain::UShowElipbe()
{
    wchar_t *mnText;
    mnText=gUGetVal(L"MSG_TITLEELIPBE");
    _Elipbe=new CDialog(mnText);
    HBITMAP hbm=(HBITMAP)LoadBitmap(_gHInstance,MAKEINTRESOURCE(RESIM_ELIPBE));
    _Elipbe->SetBitmap(hbm);
    _Elipbe->DoModeless(_gHInstance,_ghWnd,IDD_ELIPBE,SW_SHOW);
}

void UyghurEditMain::UShowAbout()
{
    wchar_t *about=L"UyghurEdit Heqqide";
    _About=new CDialog(about);
    _About->DoModal(_gHInstance,_ghWnd,IDD_ABOUTBOX);
}


void UyghurEditMain::UProcessCommand(HWND hwnd,WPARAM wParam, LPARAM lParam)
{
    int cmdID;
//    int cmdEvnt;
    cmdID    = LOWORD(wParam);
//    cmdEvnt = HIWORD(wParam);
    int len;
    wchar_t *mnText=NULL;
    switch( cmdID )
    {
    case HOJJET_YENGI:
        UYengiHojjet();
        break;
    case HOJJET_ECHISH:
        UOnOpen();
        break;
    case HOJJET_SAQLASH:
        UOnSave();
        break;
    case HOJJET_BSAQLASH:
        UOnSaveAs();
        break;
    case HOJJET_HTML:
        UOnSaveAsHTML();
        break;
    case HOJJET_BESISH:
        UOnPrint();
        break;
    case HOJJET_QEKINISH:
        if(UOnClose()==TRUE)
        {
            DestroyWindow(hwnd);
        }
        break;
    case HOJJET_BOQUSH_BOGHDA:
        UReadFromCodePage(CP_BOGHDA);
        break;
    case HOJJET_BOQUSH_WEIFANGDOS:
        UReadFromCodePage(CP_WEIDOS);
        break;
    case HOJJET_BOQUSH_WEIFANGWIN:
        UReadFromCodePage(CP_WEIWIN);
        break;

    case HOJJET_BOQUSH_UTF_16LE:
        UReadFromCodePage(CP_UTF16LE);
        break;
    case HOJJET_BOQUSH_UTF_16BE:
        UReadFromCodePage(CP_UTF16BE);
        break;
    case HOJJET_BOQUSH_UTF_8:
        UReadFromCodePage(CP_UTF8);
        break;
    case HOJJET_BOQUSH_UTF_7:
        UReadFromCodePage(CP_UTF7);
        break;
    case HOJJET_BOQUSH_ISO8859_1:
        UReadFromCodePage(CP_1252);
        break;
    case HOJJET_BOQUSH_1250:
        UReadFromCodePage(CP_1250);
        break;
    case HOJJET_BOQUSH_932:
        UReadFromCodePage(CP_932);
        break;
    case HOJJET_BOQUSH_JEUC:
        UReadFromCodePage(CP_JEUC);
        break;
    case HOJJET_BOQUSH_GB2312:
        UReadFromCodePage(CP_936);
        break;
    case HOJJET_BOQUSH_950:
        UReadFromCodePage(CP_950);
        break;
    case HOJJET_BOQUSH_1251:
        UReadFromCodePage(CP_1251);
        break;
    case HOJJET_BOQUSH_1253:
        UReadFromCodePage(CP_1253);
        break;
    case HOJJET_BOQUSH_1254:
        UReadFromCodePage(CP_1254);
        break;
    case HOJJET_BOQUSH_1255:
        UReadFromCodePage(CP_1255);
        break;
    case HOJJET_BOQUSH_1256:
        UReadFromCodePage(CP_1256);
        break;
    case HOJJET_BOQUSH_1257:
        UReadFromCodePage(CP_1257);
        break;
    case TEHRIR_IZDESH:
    case TEHRIR_IZDESH_DAWAMLASHTURUSH:
        if(mhImla==NULL)mhImla=gLoadImlaDll();
        if(mhImla!=NULL)
        {
            PostMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)cmdID,(LPARAM)0);
        }
        break;
    case BASHQA_SOLDINONG:
    {
        BOOL rtl;
        if(_pEditWin->UIsRTL())
        {
            rtl=FALSE;
        }
        else
        {
            rtl=TRUE;
        }
        PostMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_SOLDINONG,(LPARAM)rtl);
        break;
    }
    case BASHQA_TIZISHABZAS:
    case BASHQA_TIZISHHEMME:
    case BASHQA_XETNUSXISI:
    case TEHRIR_YENIWELISH:
    case TEHRIR_QILISH:
    case TEHRIR_KOCHURUSH:
    case TEHRIR_CHAPLASH:
    case TEHRIR_KESISH:
    case TEHRIR_OCHURUSH:
    case TEHRIR_HEM_TAL:
    case TEHRIR_HOJJETBESHI:
    case TEHRIR_HOJJETAHIRI:
    case TEHRIR_TALNIUKY:
    case TEHRIR_TALNIKONA:
    case TEHRIR_TALNICHONG:
    case TEHRIR_TALNIKICHIK:
    case TEHRIR_KOCHURUSH_ALL:
    case TEHRIR_TALNISLAWIYAN:
    case TEHRIR_TALSLAWIYANUEY:
    case TEHRIR_TALNITURK:
    case TEHRIR_TALTURKUEY:
    case TEHRIR_BCHAPLASH_UYGHURSOFT:
    case TEHRIR_BCHAPLASH_ILIKYURT:
    case TEHRIR_BCHAPLASH_UIGHUR_NOTEPAD:
    case TEHRIR_BCHAPLASH_DULDUL:
    case TEHRIR_BCHAPLASH_BASHQILAR:
    case KOCHUR_ALA2UYGHUR:
    case BASHQA_UBUNTU:
    case BASHQA_UEY:
    case BASHQA_ULY:
    case BASHQA_USY:
    case BASHQA_OTY:
    case BASHQA_UMY:
    case BASHQA_UYGHUR2LATIN:
    case BASHQA_UYGHUR2SLAWIYAN:
    case BASHQA_UYGHUR2MEWHUM:
    case BASHQA_LATIN2UYGHUR:
    case BASHQA_LATIN2SLAWIYAN:
    case BASHQA_LATIN2MEWHUM:
    case BASHQA_SLAWIYAN2UYGHUR:
    case BASHQA_SLAWIYAN2LATIN:
    case BASHQA_SLAWIYAN2MEWHUM:
    case BASHQA_MEWHUM2UYGHUR:
    case BASHQA_MEWHUM2LATIN:
    case BASHQA_MEWHUM2SLAWIYAN:
        PostMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)cmdID,(LPARAM)0);
        break;
    case BASHQA_IMLA:
        if(mhImla==NULL)mhImla=gLoadImlaDll();
        if(mhImla!=NULL)
        {
            PostMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)cmdID,(LPARAM)0);
        }
        break;
    case BASHQA_UKYGEAYLAN:
        UOnToULY();
        break;
    case BASHQA_KONAGHAAYLAN_TXT:
        UOnToUEY_TXT();
        break;
    case BASHQA_KONAGHAAYLAN_PRG:
        UOnToUEY_PRG();
        break;
    case BASHQA_KONAGHAAYLAN_INF:
        UOnToUEY_INF();
        break;
//		case BASHQA_UYGHUR2SLAWIYAN:
//			UOnUyghurToSlawiyan();
//			break;
//		case BASHQA_SLAWIYAN2UYGHUR:
//			UOnSlawiyanToUyghur();
//			break;
//		case BASHQA_UYGHUR2TURK:
//			UOnUyghurToTurk();
//			break;
//		case BASHQA_TURK2UYGHUR:
//			UOnTurkToUyghur();
//			break;

    case BASHQA_KUNUPKA:
        PostMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_KUNUPKA,lParam);
        break;
    case USERMSG_SOZGEPARCHILASH:
    case USERMSG_SOZGEPARCHILASH_YOQ:
    case USERMSG_ABZASQA_PARCHILASH:
    case USERMSG_APTOMATIC_TOGHRILA:
        SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)cmdID,lParam);
        this->USetWindowsTitle();
        break;
    case USERLG_JAPANESE:
        _pEditWin->USetInterfaceLang(LANG_JPN);
        len=UGetLangResource(IDR_RES_JPN);
        if(len!=0)
        {
            USetMenuText();
            USetWindowLayout(LANG_JPN);
            RECT rc;
            GetClientRect(_ghEditWin,&rc);
            InvalidateRect(_ghEditWin,&rc,TRUE);
        }
        mnText=NULL;

        break;
    case USERLG_ENGLISH:
        _pEditWin->USetInterfaceLang(LANG_ENG);
        len=UGetLangResource(IDR_RES_ENG);
        if(len!=0)
        {
            USetMenuText();
            USetWindowLayout(LANG_ENG);
            RECT rc;
            GetClientRect(_ghEditWin,&rc);
            InvalidateRect(_ghEditWin,&rc,TRUE);
        }
        mnText=NULL;
        break;
    case USERLG_CHINESE:
        _pEditWin->USetInterfaceLang(LANG_CHN);
        len=UGetLangResource(IDR_RES_CHN);
        if(len!=0)
        {
            USetMenuText();
            USetWindowLayout(LANG_CHN);
            RECT rc;
            GetClientRect(_ghEditWin,&rc);
            InvalidateRect(_ghEditWin,&rc,TRUE);
        }
        mnText=NULL;
        break;
    case USERLG_GERMAN:
        _pEditWin->USetInterfaceLang(LANG_GER);
        len=UGetLangResource(IDR_RES_GER);
        if(len!=0)
        {
            USetMenuText();
            USetWindowLayout(LANG_GER);
            RECT rc;
            GetClientRect(_ghEditWin,&rc);
            InvalidateRect(_ghEditWin,&rc,TRUE);
        }
        mnText=NULL;
        break;
    case USERLG_ULY:
    case USERLG_UEY:
    case USERLG_USY:
        if(cmdID==USERLG_UEY)
        {
            _pEditWin->USetInterfaceLang(LANG_UEY);
            len=UGetLangResource(IDR_RES_UEY);
            USetWindowLayout(LANG_UEY);
        }
        else if(cmdID==USERLG_ULY)
        {
            _pEditWin->USetInterfaceLang(LANG_ULY);
            len=UGetLangResource(IDR_RES_ULY);
            USetWindowLayout(LANG_ULY);
        }
        else
        {
            _pEditWin->USetInterfaceLang(LANG_USY);
            len=UGetLangResource(IDR_RES_USY);
            USetWindowLayout(LANG_USY);
        }
        if(len!=0)
        {
            USetMenuText();
            RECT rc;
            GetClientRect(_ghEditWin,&rc);
            InvalidateRect(_ghEditWin,&rc,TRUE);
        }
        mnText=NULL;
        break;
    case YARDEM_KUNUPKA:
        UShowKunupka();
        mnText=NULL;
        break;
    case YARDEM_ELIPPE:
        UShowElipbe();
        mnText=NULL;
        break;
    case YARDEM_HEQQIDE:
        UShowAbout();
        mnText=NULL;
        break;
    case BASHQA_KUNUPKA_OZGERT:
        UKunupkaOzgert();
        break;
    case HOJJET_IZ:
    case HOJJET_IZ+1:
    case HOJJET_IZ+2:
    case HOJJET_IZ+3:
    case HOJJET_IZ+4:
    case HOJJET_IZ+5:
    case HOJJET_IZ+6:
    case HOJJET_IZ+7:
    case HOJJET_IZ+8:
    case HOJJET_IZ+9:
    case HOJJET_IZ+10:
        len=cmdID-HOJJET_IZ;
        UIzniOqush(len);
        mnText=NULL;
        break;
    default:
        mnText=NULL;
        break;
    }
    if(mnText!=NULL)
    {
        m_UMsgBox.UShow(_gHInstance,_ghWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),mnText,MB_OK);
    }
}

/*
void UyghurEditMain::UKunupkaOzgert()
{
    KUNUPKA hazirqisi=_pEditWin->UGetKunupka();
    KUNUPKA yengi;
    if(hazirqisi==KUNUPKA_SYSTEM){
        yengi=KUNUPKA_UYGHUR;
    }else if(hazirqisi==KUNUPKA_LATIN){
        yengi=KUNUPKA_SYSTEM;
    }else{
        yengi=KUNUPKA_LATIN;
    }
    PostMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_KUNUPKA,(LPARAM)yengi);
}
*/

void UyghurEditMain::UKunupkaOzgert()
{
    KUNUPKA hazirqisi=_pEditWin->UGetKunupka();
    KUNUPKA yengi;
    if(hazirqisi==KUNUPKA_UYGHUR)
    {
        yengi=KUNUPKA_LATIN;
    }
    else
    {
        yengi=KUNUPKA_UYGHUR;
    }
    PostMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_KUNUPKA,(LPARAM)yengi);
}

void UyghurEditMain::USetWindowLayout(UINTERFACE_LANG lang)
{
    long exSt;
    _UCaption.USetUILang(lang);
    if(LANG_UEY==lang)
    {
        exSt=GetWindowLong(_ghWnd,GWL_EXSTYLE);
        exSt|=WS_EX_LAYOUTRTL|WS_EX_RTLREADING;
        SetWindowLong(_ghWnd,GWL_EXSTYLE,exSt);
        exSt=GetWindowLong(_ghStatusBar,GWL_EXSTYLE);
        exSt|=WS_EX_LAYOUTRTL|WS_EX_RTLREADING;
        SetWindowLong(_ghStatusBar,GWL_EXSTYLE,exSt);
    }
    else
    {
        exSt=GetWindowLong(_ghWnd,GWL_EXSTYLE);
        exSt&=~WS_EX_LAYOUTRTL;
        SetWindowLong(_ghWnd,GWL_EXSTYLE,exSt);
        exSt=GetWindowLong(_ghStatusBar,GWL_EXSTYLE);
        exSt&=~WS_EX_LAYOUTRTL;
        SetWindowLong(_ghStatusBar,GWL_EXSTYLE,exSt);
    }
}

int UyghurEditMain::UGetLangResource(UINT resID)
{
    HRSRC      hrsrc;
    HGLOBAL    hglob;
    char       *resBuf;
    wchar_t    *resSt;
    unsigned int len;

    CUyghurcheKodAlmashturush uka;

    if(resID==IDR_RES_ULY||resID==IDR_RES_USY||resID==IDR_RES_UEY)
    {
        hrsrc      = FindResource(_gHInstance, MAKEINTRESOURCE(IDR_RES_UEY), TEXT("TEXT"));
        if(hrsrc==NULL) return 0;
        len = SizeofResource(_gHInstance, hrsrc);
        hglob      = LoadResource(_gHInstance, hrsrc);
        resBuf     = (char*) LockResource(hglob);
        if (hglob==NULL  || resBuf==NULL  ||  len==0)
        {
            return 0;
        }
        else
        {
            if(_app_ResBuf!=NULL) delete[] _app_ResBuf;
            _app_ResBuf=NULL;
            resSt=gUGetUnicodeBuf(CP_UTF8,(resBuf+3));

            if(resID!=IDR_RES_UEY)
            {
                len=wcslen(resSt);
                _app_ResBuf=new wchar_t[2*len];

                if(resID==IDR_RES_ULY)
                {
                    uka.UyghurToLatin(resSt,_app_ResBuf);
                }
                else
                {
                    uka.UyghurToSlawiyan(resSt,_app_ResBuf);
                }
                delete[] resSt;
            }
            else
            {
                _app_ResBuf=resSt;
            }
        }
    }
    else
    {
        wchar_t resFileName[MAX_PATH];

        GetModuleFileName(_gHInstance,resFileName,MAX_PATH);
        PathRemoveFileSpec(resFileName);
        if(resID==IDR_RES_JPN)
        {
            PathAppend( resFileName, RES_NAME_JPN );
        }
        else if(resID==IDR_RES_ENG)
        {
            PathAppend(resFileName, RES_NAME_ENG );
        }
        else if(resID==IDR_RES_CHN)
        {
            PathAppend(resFileName,RES_NAME_CHN);
        }
        else if(resID==IDR_RES_UEY)
        {
            PathAppend(resFileName,RES_NAME_UEY);
        }
        else if(resID==IDR_RES_GER)
        {
            PathAppend(resFileName,RES_NAME_GER);
        }

        FILE *fp=_wfopen(resFileName,L"rb");
        if(fp!=NULL)
        {
            long len=(long)filelength(_fileno(fp));
            resBuf=new char[len+2];
            fread(resBuf,1,len,fp);
            fclose(fp);
            resBuf[len]=0x0;
            resBuf[len+1]=0x0;
            if(_app_ResBuf!=NULL) delete[] _app_ResBuf;
            _app_ResBuf=gUGetUnicodeBuf(CP_UTF8,(resBuf+3));
            delete[] resBuf;
        }
        else
        {
            return _resCnt;
        }
    }

    if(_app_ResBuf==NULL) return 0;
    long rPos=0, wPos=0;
    wchar_t Herp;
    while(_app_ResBuf[rPos]!=0x0)
    {
        Herp=_app_ResBuf[rPos++];
        if(Herp==QURBELGISI_R||Herp==QURBELGISI_L)
        {
            if(_app_ResBuf[rPos]==QURBELGISI_L)
            {
                rPos++;
            }
            Herp=QURBELGISI_R;
        }
        _app_ResBuf[wPos++]=Herp;
    }
    _app_ResBuf[wPos]=0x0;

    wchar_t    *buf;
    buf=_app_ResBuf;
    _resCnt=0;
    wchar_t *key;
    wchar_t *val=NULL;
    key=buf;
    if(buf[0]==0xFEFF)
    {
        key=&buf[1];
    }

    while(*buf!=0x00)
    {
        if(*buf=='=')
        {
            *buf=0x0;
            buf++;
            val=buf;
            if(resID==IDR_RES_ULY)
            {
                val[0]=gUToUpperULY(val[0]);
            }
            else if(resID==IDR_RES_USY)
            {
                val[0]=gUToUpperSlawiyan(val[0]);
            }
        }
        else if(*buf==QURBELGISI_R)
        {
            *buf=0x0;
            _resKey[_resCnt]=key;
            _resVal[_resCnt]=val;
            _resCnt++;
            buf++;
            key=buf;
        }
        else
        {
            buf++;
        }
    }
    return _resCnt;
}



void UyghurEditMain::USetMenuText()
{
    // Bu Yerdin Bashlap Bash Menuni Ozgertidu
    HMENU hMenu=::GetMenu(_ghWnd);
    HMENU subMenu;

    if(hMenu==NULL) return;
    wchar_t *mnText;
    mnText=gUGetVal(L"BASH_HOJJET");

    UINT styM=MF_STRING|MF_BYPOSITION;//|MFT_RIGHTORDER|MFT_RIGHTJUSTIFY;
    UINT styC=MF_STRING|MF_BYCOMMAND;//|MFT_RIGHTORDER|MFT_RIGHTJUSTIFY;

    ModifyMenu(hMenu,0,styM,0,mnText);

    mnText=gUGetVal(L"BASH_TEHRIR");
//	ModifyMenu(hMenu,1,MF_OWNERDRAW |MF_STRING|MF_BYPOSITION,0,mnText);
    ModifyMenu(hMenu,1,styM,0,mnText);

    mnText=gUGetVal(L"BASH_BASHQA");
    ModifyMenu(hMenu,2,styM,0,mnText);

    mnText=gUGetVal(L"BASH_TIL");
    ModifyMenu(hMenu,3,styM,0,mnText);

    mnText=gUGetVal(L"BASH_YARDEM");
    ModifyMenu(hMenu,4,styM,0,mnText);


    // Hojetning Barliq Menusini Alidu
    mnText=gUGetVal(L"HOJJET_YENGI");
    ModifyMenu(hMenu,HOJJET_YENGI,styC,HOJJET_YENGI,mnText);
    mnText=gUGetVal(L"HOJJET_ECHISH");
    ModifyMenu(hMenu,HOJJET_ECHISH,styC,HOJJET_ECHISH,mnText);
    mnText=gUGetVal(L"HOJJET_SAQLASH");
    ModifyMenu(hMenu,HOJJET_SAQLASH,styC,HOJJET_SAQLASH,mnText);
    mnText=gUGetVal(L"HOJJET_BSAQLASH");
    ModifyMenu(hMenu,HOJJET_BSAQLASH,styC,HOJJET_BSAQLASH,mnText);
    mnText=gUGetVal(L"HOJJET_HTML");
    ModifyMenu(hMenu,HOJJET_HTML,styC,HOJJET_HTML,mnText);
    mnText=gUGetVal(L"HOJJET_BESISH");
    ModifyMenu(hMenu,HOJJET_BESISH,styC,HOJJET_BESISH,mnText);

    mnText=gUGetVal(L"HOJJET_QEKINISH");
    ModifyMenu(hMenu,HOJJET_QEKINISH,styC,HOJJET_QEKINISH,mnText);
    /*
    	mnText=gUGetVal(L"HOJJET_BOQUSH_BOGHDA");
    	ModifyMenu(hMenu,HOJJET_BOQUSH_BOGHDA,MF_STRING|MF_BYCOMMAND|MFT_LEFTJUSTIFY,HOJJET_BOQUSH_BOGHDA,mnText);
    	mnText=gUGetVal(L"HOJJET_BOQUSH_WEIFANGDOS");
    	ModifyMenu(hMenu,HOJJET_BOQUSH_WEIFANGDOS,MF_STRING|MF_BYCOMMAND|MFT_LEFTJUSTIFY,HOJJET_BOQUSH_WEIFANGDOS,mnText);
    	mnText=gUGetVal(L"HOJJET_BOQUSH_WEIFANGWIN");
    	ModifyMenu(hMenu,HOJJET_BOQUSH_WEIFANGWIN,MF_STRING|MF_BYCOMMAND|MFT_LEFTJUSTIFY,HOJJET_BOQUSH_WEIFANGWIN,mnText);
    */
    //Tehrirlesh
    mnText=gUGetVal(L"TEHRIR_YENIWELISH");
    ModifyMenu(hMenu,TEHRIR_YENIWELISH,styC,TEHRIR_YENIWELISH,mnText);
    mnText=gUGetVal(L"TEHRIR_QILISH");
    ModifyMenu(hMenu,TEHRIR_QILISH,styC,TEHRIR_QILISH,mnText);

    mnText=gUGetVal(L"TEHRIR_KOCHURUSH");
    ModifyMenu(hMenu,TEHRIR_KOCHURUSH,styC,TEHRIR_KOCHURUSH,mnText);
    mnText=gUGetVal(L"TEHRIR_CHAPLASH");
    ModifyMenu(hMenu,TEHRIR_CHAPLASH,styC,TEHRIR_CHAPLASH,mnText);
    mnText=gUGetVal(L"TEHRIR_KESISH");
    ModifyMenu(hMenu,TEHRIR_KESISH,styC,TEHRIR_KESISH,mnText);
    mnText=gUGetVal(L"TEHRIR_OCHURUSH");
    ModifyMenu(hMenu,TEHRIR_OCHURUSH,styC,TEHRIR_OCHURUSH,mnText);

    mnText=gUGetVal(L"TEHRIR_IZDESH");
    ModifyMenu(hMenu,TEHRIR_IZDESH,styC,TEHRIR_IZDESH,mnText);
    mnText=gUGetVal(L"TEHRIR_IZDESH_DAWAMLASHTURUSH");
    ModifyMenu(hMenu,TEHRIR_IZDESH_DAWAMLASHTURUSH,styC,TEHRIR_IZDESH_DAWAMLASHTURUSH,mnText);

    mnText=gUGetVal(L"TEHRIR_HEM_TAL");
    ModifyMenu(hMenu,TEHRIR_HEM_TAL,styC,TEHRIR_HEM_TAL,mnText);

    mnText=gUGetVal(L"TEHRIR_HOJJETBESHI");
    ModifyMenu(hMenu,TEHRIR_HOJJETBESHI,styC,TEHRIR_HOJJETBESHI,mnText);
    mnText=gUGetVal(L"TEHRIR_HOJJETAHIRI");
    ModifyMenu(hMenu,TEHRIR_HOJJETAHIRI,styC,TEHRIR_HOJJETAHIRI,mnText);

    mnText=gUGetVal(L"TEHRIR_TALNIUKY");
    ModifyMenu(hMenu,TEHRIR_TALNIUKY,styC,TEHRIR_TALNIUKY,mnText);
    mnText=gUGetVal(L"TEHRIR_TALNIKONA");
    ModifyMenu(hMenu,TEHRIR_TALNIKONA,styC,TEHRIR_TALNIKONA,mnText);
    mnText=gUGetVal(L"TEHRIR_TALNISLAWIYAN");
    ModifyMenu(hMenu,TEHRIR_TALNISLAWIYAN,styC,TEHRIR_TALNISLAWIYAN,mnText);
    mnText=gUGetVal(L"TEHRIR_TALSLAWIYANUEY");
    ModifyMenu(hMenu,TEHRIR_TALSLAWIYANUEY,styC,TEHRIR_TALSLAWIYANUEY,mnText);
    mnText=gUGetVal(L"TEHRIR_TALNITURK");
    ModifyMenu(hMenu,TEHRIR_TALNITURK,styC,TEHRIR_TALNITURK,mnText);
    mnText=gUGetVal(L"TEHRIR_TALTURKUEY");
    ModifyMenu(hMenu,TEHRIR_TALTURKUEY,styC,TEHRIR_TALTURKUEY,mnText);


    mnText=gUGetVal(L"TEHRIR_TALNICHONG");
    ModifyMenu(hMenu,TEHRIR_TALNICHONG,styC,TEHRIR_TALNICHONG,mnText);
    mnText=gUGetVal(L"TEHRIR_TALNIKICHIK");
    ModifyMenu(hMenu,TEHRIR_TALNIKICHIK,styC,TEHRIR_TALNIKICHIK,mnText);

    mnText=gUGetVal(L"TEHRIR_KOCHURUSH_ALL");
    ModifyMenu(hMenu,TEHRIR_KOCHURUSH_ALL,styC,TEHRIR_KOCHURUSH_ALL,mnText);

    // Bashqa
    mnText=gUGetVal(L"BASHQA_IMLA");
    ModifyMenu(hMenu,BASHQA_IMLA,styC,BASHQA_IMLA,mnText);

    mnText=gUGetVal(L"BASHQA_TIZISHABZAS");
    ModifyMenu(hMenu,BASHQA_TIZISHABZAS,styC,BASHQA_TIZISHABZAS,mnText);
    mnText=gUGetVal(L"BASHQA_TIZISHHEMME");
    ModifyMenu(hMenu,BASHQA_TIZISHHEMME,styC,BASHQA_TIZISHHEMME,mnText);
    mnText=gUGetVal(L"BASHQA_XETNUSXISI");
    ModifyMenu(hMenu,BASHQA_XETNUSXISI,styC,BASHQA_XETNUSXISI,mnText);

    mnText=gUGetVal(L"BASHQA_SOLDINONG");
    ModifyMenu(hMenu,BASHQA_SOLDINONG,styC,BASHQA_SOLDINONG,mnText);

    mnText=gUGetVal(L"BASHQA_UKYGEAYLAN");
    ModifyMenu(hMenu,BASHQA_UKYGEAYLAN,styC,BASHQA_UKYGEAYLAN,mnText);

    mnText=gUGetVal(L"BASHQA_KONAGHAAYLAN_TXT");
    ModifyMenu(hMenu,BASHQA_KONAGHAAYLAN_TXT,styC,BASHQA_KONAGHAAYLAN_TXT,mnText);
    mnText=gUGetVal(L"BASHQA_KONAGHAAYLAN_PRG");
    ModifyMenu(hMenu,BASHQA_KONAGHAAYLAN_PRG,styC,BASHQA_KONAGHAAYLAN_PRG,mnText);
    mnText=gUGetVal(L"BASHQA_KONAGHAAYLAN_INF");
    ModifyMenu(hMenu,BASHQA_KONAGHAAYLAN_INF,styC,BASHQA_KONAGHAAYLAN_INF,mnText);

//	mnText=gUGetVal(L"BASHQA_UYGHUR2SLAWIYAN");
//	ModifyMenu(hMenu,BASHQA_UYGHUR2SLAWIYAN,styC,BASHQA_UYGHUR2SLAWIYAN,mnText);
//	mnText=gUGetVal(L"BASHQA_SLAWIYAN2UYGHUR");
//	ModifyMenu(hMenu,BASHQA_SLAWIYAN2UYGHUR,styC,BASHQA_SLAWIYAN2UYGHUR,mnText);

//	mnText=gUGetVal(L"BASHQA_UYGHUR2TURK");
//	ModifyMenu(hMenu,BASHQA_UYGHUR2TURK,styC,BASHQA_UYGHUR2TURK,mnText);
//	mnText=gUGetVal(L"BASHQA_TURK2UYGHUR");
//	ModifyMenu(hMenu,BASHQA_TURK2UYGHUR,styC,BASHQA_TURK2UYGHUR,mnText);

    // User language
    ModifyMenu(hMenu, USERLG_UEY,styC,USERLG_UEY,L"ئۇيغۇرچە");
    ModifyMenu(hMenu, USERLG_ULY,styC,USERLG_ULY,L"Uyghurche");
    ModifyMenu(hMenu, USERLG_USY,styC,USERLG_USY,L"Уйғурчә");
    ModifyMenu(hMenu,USERLG_JAPANESE,styC,USERLG_JAPANESE,L"日本語");
    ModifyMenu(hMenu,USERLG_ENGLISH,styC,USERLG_ENGLISH,L"English");
    ModifyMenu(hMenu,USERLG_CHINESE,styC,USERLG_CHINESE,L"简体中文");
    ModifyMenu(hMenu,USERLG_GERMAN,styC,USERLG_GERMAN,L"Deutsch");

    // yardem
    mnText=gUGetVal(L"YARDEM_KUNUPKA");
    ModifyMenu(hMenu,YARDEM_KUNUPKA,styC,YARDEM_KUNUPKA,mnText);
    mnText=gUGetVal(L"YARDEM_ELIPPE");
    ModifyMenu(hMenu,YARDEM_ELIPPE,styC,YARDEM_ELIPPE,mnText);
    mnText=gUGetVal(L"YARDEM_HEQQIDE");
    ModifyMenu(hMenu,YARDEM_HEQQIDE,styC,YARDEM_HEQQIDE,mnText);

    // Bu Yerdin bashlap Ana Menularni ongshaydu(POPUP menuni)
    subMenu=GetSubMenu(hMenu,0);
    mnText=gUGetVal(L"HOJJET_BOQUSH");
    ModifyMenu(subMenu,7,styM,0,mnText);

    mnText=gUGetVal(L"HOJJET_IZLAR");
    ModifyMenu(subMenu,9,styM,0,mnText);

    subMenu=GetSubMenu(hMenu,1);
    mnText=gUGetVal(L"TEHRIR_BCHAPLASH");
    ModifyMenu(subMenu,25,styM,TEHRIR_BCHAPLASH,mnText);

    subMenu=GetSubMenu(hMenu,2);
    mnText=gUGetVal(L"BASHQA_KONAGHAAYLAN");
    ModifyMenu(subMenu,10,styM,BASHQA_KONAGHAAYLAN,mnText);

    //Check Language Menu
    UINTERFACE_LANG lang=_pEditWin->UGetInterfaceLang();
    if(lang==LANG_JPN)
    {
        CheckMenuItem(hMenu,USERLG_JAPANESE,MF_BYCOMMAND|MFS_CHECKED);
    }
    else if(lang==LANG_ENG)
    {
        CheckMenuItem(hMenu,USERLG_ENGLISH,MF_BYCOMMAND|MFS_CHECKED);
    }
    else if(lang==LANG_CHN)
    {
        CheckMenuItem(hMenu,USERLG_CHINESE,MF_BYCOMMAND|MFS_CHECKED);
    }
    else if(lang==LANG_UEY)
    {
        CheckMenuItem(hMenu,USERLG_UEY,MF_BYCOMMAND|MFS_CHECKED);
    }
    else if(lang==LANG_USY)
    {
        CheckMenuItem(hMenu,USERLG_USY,MF_BYCOMMAND|MFS_CHECKED);
    }
    else if(lang==LANG_ULY)
    {
        CheckMenuItem(hMenu,USERLG_ULY,MF_BYCOMMAND|MFS_CHECKED);
    }
    else if(lang==LANG_GER)
    {
        CheckMenuItem(hMenu,USERLG_GERMAN,MF_BYCOMMAND|MFS_CHECKED);
    }
    _pEditWin->UILangChanged();
    DrawMenuBar(_ghWnd);
}

void UyghurEditMain::USetMenu_ToolStatus()
{
    HMENU hMenu=::GetMenu(_ghWnd);
    UINT st;
    if(_pEditWin->UIsFileNameEmpty())
    {
        st=MFS_DISABLED;
    }
    else
    {
        st=MFS_ENABLED;
    }

    SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)BASHQA_OTY,(LPARAM)MAKELONG(FALSE,0));

    EnableMenuItem(hMenu,HOJJET_BOQUSH_BOGHDA,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_WEIFANGDOS,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_WEIFANGWIN,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_UTF_16LE,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_UTF_16BE,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_UTF_8,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_UTF_7,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_ISO8859_1,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_1250,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_932,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_JEUC,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_GB2312,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_950,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_1251,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_1253,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_1254,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_1255,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_1256,MF_BYCOMMAND|st);
    EnableMenuItem(hMenu,HOJJET_BOQUSH_1257,MF_BYCOMMAND|st);


    if(gIsClipBoradEmpty())
    {
        EnableMenuItem(hMenu,TEHRIR_CHAPLASH,MFS_DISABLED|MF_BYCOMMAND);
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_CHAPLASH,(LPARAM)MAKELONG(FALSE,0));
    }
    else
    {
        EnableMenuItem(hMenu,TEHRIR_CHAPLASH,MFS_ENABLED|MF_BYCOMMAND);
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_CHAPLASH,(LPARAM)MAKELONG(TRUE,0));
    }


    if(_pEditWin->UIsTextSelected())
    {
        EnableMenuItem(hMenu,TEHRIR_KOCHURUSH,MF_BYCOMMAND|MFS_ENABLED);
        EnableMenuItem(hMenu,TEHRIR_KOCHURUSH_ALL,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_KESISH,MF_BYCOMMAND|MFS_ENABLED);
        EnableMenuItem(hMenu,TEHRIR_OCHURUSH,MF_BYCOMMAND|MFS_ENABLED);

        EnableMenuItem(hMenu,TEHRIR_TALNIUKY,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_TALNIKONA,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_TALNISLAWIYAN,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_TALSLAWIYANUEY,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_TALNITURK,MFS_ENABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_TALTURKUEY,MFS_ENABLED|MF_BYCOMMAND);

        EnableMenuItem(hMenu,TEHRIR_TALNIKICHIK,MF_BYCOMMAND|MFS_ENABLED);
        EnableMenuItem(hMenu,TEHRIR_TALNICHONG,MF_BYCOMMAND|MFS_ENABLED);
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_KOCHURUSH,(LPARAM)MAKELONG(TRUE,0));
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_KESISH,(LPARAM)MAKELONG(TRUE,0));
    }
    else
    {
        EnableMenuItem(hMenu,TEHRIR_KOCHURUSH,MF_BYCOMMAND|MFS_DISABLED);
        EnableMenuItem(hMenu,TEHRIR_KOCHURUSH_ALL,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_KESISH,MF_BYCOMMAND|MFS_DISABLED);
        EnableMenuItem(hMenu,TEHRIR_OCHURUSH,MF_BYCOMMAND|MFS_DISABLED);

        EnableMenuItem(hMenu,TEHRIR_TALNIUKY,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_TALNIKONA,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_TALNISLAWIYAN,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_TALSLAWIYANUEY,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_TALNITURK,MFS_DISABLED|MF_BYCOMMAND);
        EnableMenuItem(hMenu,TEHRIR_TALTURKUEY,MFS_DISABLED|MF_BYCOMMAND);

        EnableMenuItem(hMenu,TEHRIR_TALNIKICHIK,MF_BYCOMMAND|MFS_DISABLED);
        EnableMenuItem(hMenu,TEHRIR_TALNICHONG,MF_BYCOMMAND|MFS_DISABLED);
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_KOCHURUSH,(LPARAM)MAKELONG(FALSE,0));
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_KESISH,(LPARAM)MAKELONG(FALSE,0));
    }

    if(_pEditWin->UGetKunupka()==KUNUPKA_UYGHUR)
    {
        SendMessage(_ghToolBar,TB_CHECKBUTTON,(WPARAM)BASHQA_KUNUPKA_UKY,(LPARAM)MAKELONG(FALSE,0));
        SendMessage(_ghToolBar,TB_CHECKBUTTON,(WPARAM)BASHQA_KUNUPKA_KONA,(LPARAM)MAKELONG(TRUE,0));
        CheckMenuItem(hMenu,BASHQA_KUNUPKA_KONA,MF_BYCOMMAND|MF_CHECKED);
        CheckMenuItem(hMenu,BASHQA_KUNUPKA_UKY,MF_BYCOMMAND|MF_UNCHECKED);
    }
    else if(_pEditWin->UGetKunupka()==KUNUPKA_LATIN)
    {
        SendMessage(_ghToolBar,TB_CHECKBUTTON,(WPARAM)BASHQA_KUNUPKA_UKY,(LPARAM)MAKELONG(TRUE,0));
        SendMessage(_ghToolBar,TB_CHECKBUTTON,(WPARAM)BASHQA_KUNUPKA_KONA,(LPARAM)MAKELONG(FALSE,0));
        CheckMenuItem(hMenu,BASHQA_KUNUPKA_KONA,MF_BYCOMMAND|MF_UNCHECKED);
        CheckMenuItem(hMenu,BASHQA_KUNUPKA_UKY,MF_BYCOMMAND|MF_CHECKED);
    }
    else
    {
        CheckMenuItem(hMenu,BASHQA_KUNUPKA_KONA,MF_BYCOMMAND|MF_UNCHECKED);
        CheckMenuItem(hMenu,BASHQA_KUNUPKA_UKY,MF_BYCOMMAND|MF_UNCHECKED);
        SendMessage(_ghToolBar,TB_CHECKBUTTON,(WPARAM)BASHQA_KUNUPKA_UKY,(LPARAM)MAKELONG(FALSE,0));
        SendMessage(_ghToolBar,TB_CHECKBUTTON,(WPARAM)BASHQA_KUNUPKA_KONA,(LPARAM)MAKELONG(FALSE,0));
    }
    if(_pEditWin->UCanUndo())
    {
        EnableMenuItem(hMenu,TEHRIR_YENIWELISH,MF_BYCOMMAND|MFS_ENABLED);
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_YENIWELISH,(LPARAM)MAKELONG(TRUE,0));
    }
    else
    {
        EnableMenuItem(hMenu,TEHRIR_YENIWELISH,MF_BYCOMMAND|MFS_DISABLED);
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_YENIWELISH,(LPARAM)MAKELONG(FALSE,0));
    }

    if(_pEditWin->UCanRedo())
    {
        EnableMenuItem(hMenu,TEHRIR_QILISH,MF_BYCOMMAND|MFS_ENABLED);
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_QILISH,(LPARAM)MAKELONG(TRUE,0));
    }
    else
    {
        EnableMenuItem(hMenu,TEHRIR_QILISH,MF_BYCOMMAND|MFS_DISABLED);
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_QILISH,(LPARAM)MAKELONG(FALSE,0));
    }

    if(_pEditWin->UIsRTL())
    {
        CheckMenuItem(hMenu,BASHQA_SOLDINONG,MF_BYCOMMAND|MF_UNCHECKED);
    }
    else
    {
        CheckMenuItem(hMenu,BASHQA_SOLDINONG,MF_BYCOMMAND|MF_CHECKED);
    }



    if(mhImla==NULL)mhImla=gLoadImlaDll();
    if(mhImla==NULL)
    {
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_IZDESH,(LPARAM)MAKELONG(FALSE,0));
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_IZDESH_DAWAMLASHTURUSH,(LPARAM)MAKELONG(FALSE,0));
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)BASHQA_IMLA,(LPARAM)MAKELONG(FALSE,0));
        EnableMenuItem(hMenu,TEHRIR_IZDESH,MF_BYCOMMAND|MFS_DISABLED);
        EnableMenuItem(hMenu,TEHRIR_IZDESH_DAWAMLASHTURUSH,MF_BYCOMMAND|MFS_DISABLED);
        EnableMenuItem(hMenu,BASHQA_IMLA,MF_BYCOMMAND|MFS_DISABLED);
    }
    else
    {
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_IZDESH,(LPARAM)MAKELONG(TRUE,0));
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)TEHRIR_IZDESH_DAWAMLASHTURUSH,(LPARAM)MAKELONG(TRUE,0));
        SendMessage(_ghToolBar,TB_ENABLEBUTTON,(WPARAM)BASHQA_IMLA,(LPARAM)MAKELONG(TRUE,0));
        EnableMenuItem(hMenu,TEHRIR_IZDESH,MF_BYCOMMAND|MFS_ENABLED);
        EnableMenuItem(hMenu,TEHRIR_IZDESH_DAWAMLASHTURUSH,MF_BYCOMMAND|MFS_ENABLED);
        EnableMenuItem(hMenu,BASHQA_IMLA,MF_BYCOMMAND|MFS_ENABLED);
    }


}


void UyghurEditMain::UShowMenuHelp(UINT menuID)
{
    wchar_t *mnText=NULL;
    switch(menuID)
    {
    case HOJJET_YENGI:
        mnText=gUGetVal(L"MSG_HOJJET_YENGI");
        break;
    case HOJJET_ECHISH:
        mnText=gUGetVal(L"MSG_HOJJET_ECHISH");
        break;
    case HOJJET_SAQLASH:
        mnText=gUGetVal(L"MSG_HOJJET_SAQLASH");
        break;
    case HOJJET_BSAQLASH:
        mnText=gUGetVal(L"MSG_HOJJET_BSAQLASH");
        break;
    case HOJJET_HTML:
        mnText=gUGetVal(L"MSG_HOJJET_HTML");
        break;
    case HOJJET_BESISH:
        mnText=gUGetVal(L"MSG_HOJJET_BESISH");
        break;
    case HOJJET_QEKINISH:
        mnText=gUGetVal(L"MSG_HOJJET_QEKINISH");
        break;
    case HOJJET_BOQUSH_BOGHDA:
        mnText=gUGetVal(L"MSG_HOJJET_BOQUSH_BOGHDA");
        break;
    case HOJJET_BOQUSH_WEIFANGDOS:
        mnText=gUGetVal(L"MSG_HOJJET_BOQUSH_WEIFANGDOS");
        break;
    case HOJJET_BOQUSH_WEIFANGWIN:
        mnText=gUGetVal(L"MSG_HOJJET_BOQUSH_WEIFANGWIN");
        break;
    case TEHRIR_YENIWELISH:
        mnText=gUGetVal(L"MSG_TEHRIR_YENIWELISH");
        break;
    case TEHRIR_QILISH:
        mnText=gUGetVal(L"MSG_TEHRIR_QILISH");
        break;
    case TEHRIR_KOCHURUSH:
        mnText=gUGetVal(L"MSG_TEHRIR_KOCHURUSH");
        break;
    case TEHRIR_CHAPLASH:
        mnText=gUGetVal(L"MSG_TEHRIR_CHAPLASH");
        break;
    case TEHRIR_KESISH:
        mnText=gUGetVal(L"MSG_TEHRIR_KESISH");
        break;
    case TEHRIR_OCHURUSH:
        mnText=gUGetVal(L"MSG_TEHRIR_OCHURUSH");
        break;
    case TEHRIR_IZDESH:
        mnText=gUGetVal(L"MSG_TEHRIR_IZDESH");
        break;
    case TEHRIR_IZDESH_DAWAMLASHTURUSH:
        mnText=gUGetVal(L"MSG_TEHRIR_IZDESH_DAWAMLASHTURUSH");
        break;
    case TEHRIR_HEM_TAL:
        mnText=gUGetVal(L"MSG_TEHRIR_HEM_TAL");
        break;
    case TEHRIR_HOJJETBESHI:
        mnText=gUGetVal(L"MSG_TEHRIR_HOJJETBESHI");
        break;
    case TEHRIR_HOJJETAHIRI:
        mnText=gUGetVal(L"MSG_TEHRIR_HOJJETAHIRI");
        break;
    case TEHRIR_TALNIUKY:
        mnText=gUGetVal(L"MSG_TEHRIR_TALNIUKY");
        break;
    case TEHRIR_TALNIKONA:
        mnText=gUGetVal(L"MSG_TEHRIR_TALNIKONA");
        break;
    case TEHRIR_TALNISLAWIYAN:
        mnText=gUGetVal(L"MSG_TEHRIR_TALNISLAWIYAN");
        break;
    case TEHRIR_TALSLAWIYANUEY:
        mnText=gUGetVal(L"MSG_TEHRIR_TALSLAWIYANUEY");
        break;
    case TEHRIR_TALNITURK:
        mnText=gUGetVal(L"MSG_TEHRIR_TALNITURK");
        break;
    case TEHRIR_TALTURKUEY:
        mnText=gUGetVal(L"MSG_TEHRIR_TALTURKUEY");
        break;
    case TEHRIR_TALNICHONG:
        mnText=gUGetVal(L"MSG_TEHRIR_TALNICHONG");
        break;
    case TEHRIR_TALNIKICHIK:
        mnText=gUGetVal(L"MSG_TEHRIR_TALNIKICHIK");
        break;
    case TEHRIR_KOCHURUSH_ALL:
        mnText=gUGetVal(L"MSG_TEHRIR_KOCHURUSH_ALL");
        break;
    case TEHRIR_BCHAPLASH_UYGHURSOFT:
        mnText=gUGetVal(L"MSG_TEHRIR_BCHAPLASH_UYGHURSOFT");
        break;
    case TEHRIR_BCHAPLASH_UIGHUR_NOTEPAD:
        mnText=gUGetVal(L"MSG_TEHRIR_BCHAPLASH_UIGHUR_NOTEPAD");
        break;
    case TEHRIR_BCHAPLASH_ILIKYURT:
        mnText=gUGetVal(L"MSG_TEHRIR_BCHAPLASH_ILIKYURT");
        break;
    case TEHRIR_BCHAPLASH_DULDUL:
        mnText=gUGetVal(L"MSG_TEHRIR_BCHAPLASH_DULDUL");
        break;
    case BASHQA_IMLA:
        mnText=gUGetVal(L"MSG_BASHQA_IMLA");
        break;
    case BASHQA_TIZISHABZAS:
        mnText=gUGetVal(L"MSG_BASHQA_TIZISHABZAS");
        break;
    case BASHQA_TIZISHHEMME:
        mnText=gUGetVal(L"MSG_BASHQA_TIZISHHEMME");
        break;
    case BASHQA_XETNUSXISI:
        mnText=gUGetVal(L"MSG_BASHQA_XETNUSXISI");
        break;
    case BASHQA_SOLDINONG:
        mnText=gUGetVal(L"MSG_BASHQA_SOLDINONG");
        break;

    case BASHQA_UKYGEAYLAN:
        mnText=gUGetVal(L"MSG_BASHQA_UKYGEAYLAN");
        break;

    case BASHQA_KONAGHAAYLAN_TXT:
        mnText=gUGetVal(L"MSG_BASHQA_KONAGHAAYLAN_TXT");
        break;
    case BASHQA_KONAGHAAYLAN_PRG:
        mnText=gUGetVal(L"MSG_BASHQA_KONAGHAAYLAN_PRG");
        break;
    case BASHQA_KONAGHAAYLAN_INF:
        mnText=gUGetVal(L"MSG_BASHQA_KONAGHAAYLAN_INF");
        break;
//		case BASHQA_UYGHUR2SLAWIYAN:
//			mnText=gUGetVal(L"MSG_BASHQA_UYGHUR2SLAWIYAN");
//			break;
//		case BASHQA_SLAWIYAN2UYGHUR:
//			mnText=gUGetVal(L"MSG_BASHQA_SLAWIYAN2UYGHUR");
//			break;
//		case BASHQA_UYGHUR2TURK:
//			mnText=gUGetVal(L"MSG_BASHQA_UYGHUR2TURK");
//			break;
//		case BASHQA_TURK2UYGHUR:
//			mnText=gUGetVal(L"MSG_BASHQA_TURK2UYGHUR");
//			break;
    case BASHQA_KUNUPKA_KONA:
        mnText=gUGetVal(L"MSG_BASHQA_KUNUPKA_KONA");
        break;
    case BASHQA_KUNUPKA_UKY:
        mnText=gUGetVal(L"MSG_BASHQA_KUNUPKA_UKY");
        break;
    case USERLG_ULY:
        mnText=gUGetVal(L"MSG_USERLG_ULY");
        break;
    case USERLG_JAPANESE:
        mnText=gUGetVal(L"MSG_USERLG_JAPANESE");
        break;
    case USERLG_ENGLISH:
        mnText=gUGetVal(L"MSG_USERLG_ENGLISH");
        break;
    case USERLG_CHINESE:
        mnText=gUGetVal(L"MSG_USERLG_CHINESE");
        break;
    case YARDEM_KUNUPKA:
        mnText=gUGetVal(L"MSG_YARDEM_KUNUPKA");
        break;
    case YARDEM_ELIPPE:
        mnText=gUGetVal(L"MSG_YARDEM_ELIPPE");
        break;
    case YARDEM_HEQQIDE:
        mnText=gUGetVal(L"MSG_YARDEM_HEQQIDE");
        break;
    default:
        mnText=UYGHUREDIT_VERSION;
        break;
    }
    SendMessage(_ghStatusBar,SB_SETTEXT,(WPARAM)0,(LPARAM)mnText);
}


void UyghurEditMain::USetWindowsTitle(void)
{
    wchar_t *ayaq=L" - UyghurEdit";
    wchar_t  title[MAX_PATH+20];
    title[0]=0x0;
    if(_pEditWin->UIsFileNameEmpty())
    {
        wcscpy(title,gUGetVal(L"MSG_NOFILENAME"));
    }
    else
    {
        wcscpy(title,::PathFindFileName(_pEditWin->UGetFileName()));
    }
    wcscat(title,ayaq);
    SetWindowText(_ghWnd,title);
}



// Yengi Hojjet Degen Menu Tallanghanda
void UyghurEditMain::UYengiHojjet()
{
    /*    if(UNormalmu()==false) return;
    	SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)HOJJET_YENGI,0);
    	this->USetWindowsTitle();*/
    wchar_t parApp[MAX_PATH];
    int len=GetModuleFileName(_gHInstance,parApp,MAX_PATH);
    if(len==0) return;

    wcscat(parApp,L" -new");

    PROCESS_INFORMATION pi;
    STARTUPINFO si;
    ZeroMemory(&si,sizeof(si));
    si.cb=sizeof(si);
    CreateProcess(NULL,parApp,NULL,NULL,FALSE,NORMAL_PRIORITY_CLASS,NULL,NULL,&si,&pi);
}

void UyghurEditMain::UOnOpen()
{
    if(UNormalmu()==false) return;

    wchar_t Type[2048];
    Type[0]=0x0;
    wcscat(Type,gUGetVal(L"MSG_OPENFILETYPE"));
    CUFileDialog dlg(TRUE,L"",Type);
    if(dlg.UShow(_gHInstance,_ghWnd)!=0)
    {
        USetFileName(dlg.UGetFileName(),0);
        UReadFromCodePage(dlg.UGetCodePage());
    }
    this->USetWindowsTitle();
}

bool UyghurEditMain::UNormalmu()
{
    if(wcscmp(_pEditWin->UGetFileName(),m_Izlar.m_IzNami[0])==0)
    {
        m_Izlar.m_IzPos[0]=_pEditWin->UGetSelPos();
    }
    if(_pEditWin->UTuzitildimu())
    {
        int ret;
        ret=UShowAgahlandurush(L"MSG_SAQLASH",MB_YESNOCANCEL);
        if(ret==IDYES)
        {
            if(_pEditWin->UIsFileNameEmpty())
            {
                if(USaveDialog()!=IDOK)
                {
                    return false;
                }
            }
            USaveFile();
        }
        else if(ret==IDCANCEL)
        {
            return false;
        }
    }
    return true;
}

int UyghurEditMain::USaveDialog(void)
{
    wchar_t Type[2048];
    Type[0]=0x0;

    wchar_t newFileName[MAX_PATH];
    newFileName[0]=0x0;
    if(wcslen(_pEditWin->UGetFileName())==0)
    {
        wcscpy(newFileName,L"Namsiz.uut");
    }
    else
    {
        wcscpy(newFileName,_pEditWin->UGetFileName());
    }

    wcscat(Type,gUGetVal(L"MSG_SAVEFILETYPE"));
    CUFileDialog dlg(FALSE,newFileName,Type,TRUE,_pEditWin->UGetSaveBOM());
    if(dlg.UShow(_gHInstance,_ghWnd)!=0)
    {
        USetFileName(dlg.UGetFileName(),_pEditWin->UGetSelPos());
        _pEditWin->USetSaveCodePage(dlg.UGetCodePage());
        _pEditWin->USetSaveBaseCode(dlg.UGetAsasiy());
        _pEditWin->USetSaveBOM(dlg.UGetBelge());
        return IDOK;
    }
    return IDCANCEL;
}

void UyghurEditMain::UReadFromCodePage(int codePage)
{
    _pEditWin->UBeginWaitCursor();
    _pEditWin->UReadFromCodePage(codePage);
    _pEditWin->USetSelPos(m_Izlar.m_IzPos[0]);
    _pEditWin->UEndWaitCursor();
    this->USetWindowsTitle();
}

void UyghurEditMain::UIzniOqush(int izPos)
{
    wchar_t izFilename[MAX_PATH];
    ULONG   selPos;
    izFilename[0]=0x0;
    wcscpy(izFilename,m_Izlar.m_IzNami[izPos]);
    selPos=m_Izlar.m_IzPos[izPos];
    m_Izlar.m_IzPos[0]=_pEditWin->UGetSelPos();
    if(UNormalmu()==false) return;
    USetFileName(izFilename,selPos);
    UReadFromCodePage(CP_ACP);
    FILE *fp=_wfopen(izFilename,L"rb");
    if(fp==NULL)
    {
        for(int i=1; i<=m_Izlar.m_IzSani; i++)
        {
            wcscpy(m_Izlar.m_IzNami[i-1],m_Izlar.m_IzNami[i]);
            m_Izlar.m_IzPos[i-1]=m_Izlar.m_IzPos[i];
        }
        m_Izlar.m_IzSani--;
        if(m_Izlar.m_IzSani<0)m_Izlar.m_IzSani=0;
        CRegistryOperation op;
        USetIzMenu();
        op.SetIzlar(&m_Izlar);
    }
    else
    {
        fclose(fp);
    }
}


void UyghurEditMain::UOnSaveAs()
{
    if(USaveDialog()==IDOK)
    {
        USaveFile();
    }
    this->USetWindowsTitle();
}

void UyghurEditMain::USaveFile()
{
    _pEditWin->USaveFile();
    m_Izlar.m_IzPos[0]=_pEditWin->UGetSelPos();
    CRegistryOperation op;
    op.SetIzlar(&m_Izlar);
}

void UyghurEditMain::UOnSaveAsHTML(void)
{
    wchar_t Type[2048];
    Type[0]=0x0;

    wchar_t newFileName[MAX_PATH];
    newFileName[0]=0x0;
    if(wcslen(_pEditWin->UGetFileName())==0)
    {
        wcscpy(newFileName,L"namsiz");
    }
    else
    {
        wcscpy(newFileName,_pEditWin->UGetFileName());
    }
    wchar_t *ext=PathFindExtension(newFileName);
    if(ext!=NULL)
    {
        *ext=0x0;
    }
    wcscat(newFileName,L".html");
    wcscat(Type,gUGetVal(L"MSG_HTMLSAVE"));
    CUFileDialog dlg(FALSE,newFileName,Type,TRUE,_pEditWin->UGetSaveBOM());
    if(dlg.UShow(_gHInstance,_ghWnd,TRUE)==0) return;
    int ret=_pEditWin->USaveFileAsHTML(dlg.UGetFileName(),CP_UTF8,dlg.UGetAsasiy(),dlg.UGetBelge());
    if(ret==-1)
    {

    }
}


void UyghurEditMain::UOnSave()
{
    if(_pEditWin->UIsFileNameEmpty())
    {
        if(USaveDialog()==IDOK)
        {
            USaveFile();
        }
    }
    else
    {
        USaveFile();
    }
    this->USetWindowsTitle();
}

BOOL UyghurEditMain::UOnClose()
{
    ShowWindow(_ghWnd, SW_SHOWNORMAL);
    if(UNormalmu()==false) return FALSE;
    return TRUE;
}

void UyghurEditMain::UOnToULY()
{
    int ret;
    ret=UShowAgahlandurush(L"MSG_AWAL",MB_YESNOCANCEL);
    if(ret==IDYES)
    {
        if(_pEditWin->UIsFileNameEmpty())
        {
            if(USaveDialog()!=IDOK)
            {
                return;
            }
        }
        USaveFile();
    }
    else if(ret==IDCANCEL)
    {
        return;
    }
    SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_UKYGEAYLAN,(LPARAM)0);
    this->USetWindowsTitle();
}

void UyghurEditMain::UOnToUEY_TXT()
{
    int ret;
    ret=UShowAgahlandurush(L"MSG_AWAL",MB_YESNOCANCEL);
    if(ret==IDYES)
    {
        if(_pEditWin->UIsFileNameEmpty())
        {
            if(USaveDialog()!=IDOK)
            {
                return;
            }
        }
        USaveFile();
    }
    else if(ret==IDCANCEL)
    {
        return;
    }
    SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_KONAGHAAYLAN_TXT,(LPARAM)0);
    this->USetWindowsTitle();
}

void UyghurEditMain::UOnToUEY_PRG()
{
    SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_KONAGHAAYLAN_PRG,(LPARAM)0);
    this->USetWindowsTitle();
}

void UyghurEditMain::UOnToUEY_INF()
{
    SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_KONAGHAAYLAN_INF,(LPARAM)0);
    this->USetWindowsTitle();
}


void UyghurEditMain::UOnUyghurToSlawiyan()
{
    int ret;
    ret=UShowAgahlandurush(L"MSG_AWAL",MB_YESNOCANCEL);
    if(ret==IDYES)
    {
        if(_pEditWin->UIsFileNameEmpty())
        {
            if(USaveDialog()!=IDOK)
            {
                return;
            }
        }
        USaveFile();
    }
    else if(ret==IDCANCEL)
    {
        return;
    }
//	SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_UYGHUR2SLAWIYAN,(LPARAM)0);
    this->USetWindowsTitle();
}


void UyghurEditMain::UOnSlawiyanToUyghur()
{
    int ret;
    ret=UShowAgahlandurush(L"MSG_AWAL",MB_YESNOCANCEL);
    if(ret==IDYES)
    {
        if(_pEditWin->UIsFileNameEmpty())
        {
            if(USaveDialog()!=IDOK)
            {
                return;
            }
        }
        USaveFile();
    }
    else if(ret==IDCANCEL)
    {
        return;
    }
//	SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_SLAWIYAN2UYGHUR,(LPARAM)0);
    this->USetWindowsTitle();
}

void UyghurEditMain::UOnUyghurToTurk()
{
    int ret;
    ret=UShowAgahlandurush(L"MSG_AWAL",MB_YESNOCANCEL);
    if(ret==IDYES)
    {
        if(_pEditWin->UIsFileNameEmpty())
        {
            if(USaveDialog()!=IDOK)
            {
                return;
            }
        }
        USaveFile();
    }
    else if(ret==IDCANCEL)
    {
        return;
    }
//	SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_UYGHUR2TURK,(LPARAM)0);
    this->USetWindowsTitle();
}


void UyghurEditMain::UOnTurkToUyghur()
{
    int ret;
    ret=UShowAgahlandurush(L"MSG_AWAL",MB_YESNOCANCEL);
    if(ret==IDYES)
    {
        if(_pEditWin->UIsFileNameEmpty())
        {
            if(USaveDialog()!=IDOK)
            {
                return;
            }
        }
        USaveFile();
    }
    else if(ret==IDCANCEL)
    {
        return;
    }
//	SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)BASHQA_TURK2UYGHUR,(LPARAM)0);
    this->USetWindowsTitle();
}

void UyghurEditMain::UOnPrint()
{
    PRINTDLG  prnDlg;
    memset(&prnDlg, 0, sizeof(PRINTDLG));
    prnDlg.lStructSize=sizeof(PRINTDLG);
    prnDlg.hwndOwner=_ghWnd;
    prnDlg.hDevMode=NULL;
    prnDlg.hDevNames=NULL;
    prnDlg.Flags=PD_COLLATE|PD_HIDEPRINTTOFILE | PD_RETURNDC | PD_USEDEVMODECOPIES|PD_NOSELECTION;
    prnDlg.nMinPage=1;
    prnDlg.nMaxPage=1000;
    prnDlg.nCopies=1;
    prnDlg.hInstance=_gHInstance;
//    prnDlg.lpfnPrintHook=UPrintDlgHookProc;
    if(PrintDlg(&prnDlg))
    {
        SendMessage(_ghEditWin,UM_BUYRUQ,(WPARAM)HOJJET_BESISH,(LPARAM)&prnDlg);
    }
    else
    {

    }
}

void UyghurEditMain::UHojjetTashlandi(WPARAM wParam, LPARAM lParam)
{
    HDROP hDrop = (HDROP) wParam;
    wchar_t fileName[MAX_PATH];
    int len=DragQueryFile(hDrop,0,fileName,MAX_PATH);
    DragFinish(hDrop);
    if(len==0) return;
    fileName[len]=0x0;

    if(UNormalmu()==false) return;
    USetFileName(fileName,0);
    UReadFromCodePage(CP_ACP);
}

void UyghurEditMain::UMeasureItem(WPARAM wParam, LPARAM lParam)
{
    UINT id=(UINT)wParam;
    if(id!=0) return;
    LPMEASUREITEMSTRUCT  itemSt=(LPMEASUREITEMSTRUCT )lParam;
    if(itemSt->CtlType!=ODT_MENU) return;
    wchar_t *menuStr=(wchar_t*)itemSt->itemData;
    m_UMsgBox.UShow(_gHInstance,_ghWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),menuStr,MB_OK);
//    NONCLIENTMETRICS nm;
    SIZE sz;
//    nm.cbSize = sizeof(NONCLIENTMETRICS);
//	SystemParametersInfo(SPI_GETNONCLIENTMETRICS, nm.cbSize,&nm, 0);
//	HFONT hMenuFont=CreateFontIndirect(&nm.lfMenuFont);
    HDC hDC=GetDC(_ghWnd);
//	hMenuFont=(HFONT)SelectObject(hDC,hMenuFont);
    GetTextExtentPoint32(hDC,menuStr,(int)wcslen(menuStr),&sz);
//	hMenuFont=(HFONT)SelectObject(hDC,hMenuFont);
    ReleaseDC(_ghWnd,hDC);
//	DeleteObject(hMenuFont);

    itemSt->itemHeight=sz.cy;
    itemSt->itemWidth=sz.cx;
}

void UyghurEditMain::UDrawItem(WPARAM wParam, LPARAM lParam)
{
    UINT id=(UINT)wParam;
    LPDRAWITEMSTRUCT itemSt=(LPDRAWITEMSTRUCT)lParam;
    //id=0 bolsa bu menu bolghan bolidu
    if(id!=0) return;
//	m_UMsgBox.UShow(_gHInstance,_ghWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),L"Draw Item",MB_OK);
//	wchar_t menuStr[128];
//	menuStr[0]=0x0;
//	int disCnt=GetMenuString(hmenu,itemSt->itemID,menuStr,127,MF_BYPOSITION);
//	menuStr[disCnt]=0x0;
//	wsprintf(menuStr,L"L=%d T=%d R=%d B=%d ID=%d",itemSt->rcItem.left,itemSt->rcItem.top,itemSt->rcItem.right,itemSt->rcItem.bottom,itemSt->itemID);
//	m_UMsgBox.UShow(_gHInstance,_ghWnd,gUGetVal(L"MSG_UCHUR_CAPTION"),menuStr,MB_OK);
    wchar_t *menuStr=(wchar_t*)itemSt->itemData;
    int disCnt=(int)wcslen(menuStr);
    SIZE sz;
    //int Ig=itemSt->rcItem.bottom-itemSt->rcItem.top;
    GetTextExtentPoint32(itemSt->hDC,menuStr,disCnt,&sz);
    //int x,y;
    //if(sz.cy>Ig)
    //{
    //    x=itemSt->rcItem.left;
    //    y=itemSt->rcItem.top+(sz.cy-Ig)/2;
    //}
    //else
    //{
    //    x=itemSt->rcItem.left;
    //    y=itemSt->rcItem.top;
    //}
//	TextOutW(itemSt->hDC,x,y,menuStr,disCnt);
    DrawTextW(itemSt->hDC,menuStr,disCnt,&itemSt->rcItem,DT_LEFT|DT_VCENTER|DT_SINGLELINE);
}
