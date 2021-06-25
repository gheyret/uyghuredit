#ifndef UEDITMAIN_H
#define UEDITMAIN_H 1

#include <windows.h>
#include <commctrl.h>
#include <shlwapi.h>
#include <io.h>
#include "UEditWin.h"
#include "CDialog.h"
#include "UCaptionButton.h"
#include "UMessageBox.h"
#include "UCommon.h"
#include "UFileDialog.h"
#include "resource.h"
#include "ortaq.h"

#define UYGHUREDIT_NAME TEXT("UyghurEdit")
#define UYGHUREDIT_VERSION   TEXT("UyghurEdit 3.5(2017/07/18), Aptor: Gheyret T.Kenji")

class UyghurEditMain
{
public:
	UyghurEditMain();
	~UyghurEditMain();
	BOOL UInit(HINSTANCE hThisInstance);
	int URun(LPSTR lpszArgument);
	void UShowWindow(int val);
	LRESULT UProcessMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

private:
	wchar_t *_app_ResBuf;
	UEditWin *_pEditWin;
	HINSTANCE _gHInstance;
	HWND      _ghWnd;
	HWND      _ghEditWin;
	HWND      _ghStatusBar;
	HWND      _ghToolBar;
	HWND      _ghRebar;

	HMODULE     mhImla;

	CDialog *_Kunupka;
	CDialog *_Elipbe;
	CDialog *_About;

	UCaptionButton _UCaption;
	UMessageBox m_UMsgBox;

	wchar_t *UGetTextFromResource(UINT textID);
	int  UGetLangResource(UINT resID);
	void USetMenuText();
	void UShowKunupka();
	void UShowAbout();
	void UShowElipbe();
	void UOnOpen();

	int  UShowAgahlandurush(wchar_t *msgKey,UINT mb);

	void UProcessCommand(HWND hwnd,WPARAM wParam, LPARAM lParam);
	void UYengiHojjet();
	void USetMenu_ToolStatus();
	TBBUTTON _tbNew;
	TBBUTTON _tbOpen;
	TBBUTTON _tbSave;
	TBBUTTON _tbPrint;
	TBBUTTON _tbCut;
	TBBUTTON _tbCopy;
	TBBUTTON _tbPaste;
	TBBUTTON _tbUndo;
	TBBUTTON _tbRedo;
	TBBUTTON _tbFind;
	TBBUTTON _tbFindCon;
	TBBUTTON _tbSpel;
	TBBUTTON _tbUEY;
	TBBUTTON _tbULY;
	TBBUTTON _tbUSY;
	TBBUTTON _tbUMY;
	TBBUTTON _tbRTL;
	TBBUTTON _tbSep;
	TBBUTTON _tbTIZ;

	BOOL UOnSize(WPARAM wParam, LPARAM lParam);
	void UCreateToolBar();
	void UShowMenuHelp(UINT menuID);
	void UUpdateStatusbar();
	void UCreateStatusPane(void);
	void UProcessNotify(WPARAM wp,LPARAM lp);
	void USetWindowsTitle(void);
	int  USaveDialog(void);
	void UReadFromCodePage(int codePage);
	void UOnSaveAs();
	void UOnSave();
	BOOL UOnClose();
	void UOnToULY();
	void UOnToULYINF();
	void UOnToUEY_TXT();
	void UOnToUEY_PRG();
	void UOnToUEY_INF();
	void UOnPrint();
	void UOnSaveAsHTML();

	void UOnUyghurToSlawiyan();
	void UOnSlawiyanToUyghur();
	void UOnUyghurToTurk();
	void UOnTurkToUyghur();

	void USetWindowLayout(UINTERFACE_LANG lang);

	RECT m_rcU,m_rcL;
	HWND _UUBut,_ULBut;
	void UPaintCaptionBut(HWND hWnd);
	void UCalcCaptionButPos(HWND hWnd);
    void UHojjetTashlandi(WPARAM wParam, LPARAM lParam);
    void UMeasureItem(WPARAM wParam, LPARAM lParam);
    void UDrawItem(WPARAM wParam, LPARAM lParam);
    void UKunupkaOzgert();
    IZLAR m_Izlar;
    void USetFileName(wchar_t *fileName,ULONG Pos);
    void USetIzMenu();
    void USaveFile();
	void UIzniOqush(int izPos);
	bool UNormalmu();
};
#endif
