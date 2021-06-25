#ifndef CAPTIONBUTTON_INCLUDED
#define CAPTIONBUTTON_INCLUDED 1

#include "UCommon.h"
#include "ortaq.h"

#define UNAME L"U_EDIT_PR"

class UCaptionButton
{
private:
	WNDPROC		wpOldProc;
	RECT m_rcU,m_rcL;
	HWND _UUBut,_ULBut;

	BOOL      m_UUPushed;
	BOOL      m_ULPushed;
	BOOL      m_RTL;
	void UPaintCaptionBut(HWND hWnd);
	void UCalcCaptionButPos(HWND hWnd);
	HINSTANCE _gHInstance;
	LRESULT UNCHitTest(HWND hwnd, WPARAM wParam, LPARAM lParam);
	LRESULT UNCLButtonDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);
	LRESULT UNCMouseMove(HWND hwnd, WPARAM wParam, LPARAM lParam);
	LRESULT UNCLButtonUp(HWND hwnd, WPARAM wParam, LPARAM lParam);
	void UShowBitMap(HDC hDC,RECT *m_rcU,HBITMAP hBitmap,COLORREF bkColor);
	void USetKunupka(HWND hwnd, KUNUPKA kun);
	void UKunupkaOzgert(HWND hwnd);
	KUNUPKA m_CurrentKey;
	HBITMAP hUUBitmap;
	HBITMAP hULBitmap;
	
public:
	UCaptionButton();
	~UCaptionButton();
	void UInstall(HINSTANCE hInstance,HWND hwnd,KUNUPKA kun,UINTERFACE_LANG lang);
	LRESULT UProcessMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);
	void  USetUILang(UINTERFACE_LANG lang);
};

#endif
