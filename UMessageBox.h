#ifndef UMESSAGEBOX_H
#define UMESSAGEBOX_H 1

#include <windows.h>
#include "resource.h"
#include "UCommon.h"
#include "ortaq.h"

#define   UMESSAGEBOX_NAME L"UMESSAGEBOX"

class UMessageBox
{
private:
	enum { IDD = IDD_TALLASHDLG_DIALOG };
	void SetTexts();
	HWND m_hWnd;
	HINSTANCE m_hInstance;
	wchar_t *m_UTitle;
	wchar_t *m_UUchur;
	UINT    m_UButtons;

public:
	UMessageBox();
	~UMessageBox();
	INT_PTR UShow(HINSTANCE hInstance, HWND hwndOwner,wchar_t *Title,wchar_t *Uchur, UINT buttons);
	INT_PTR UPMessage(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam);
	void UOnPaint();
};

#endif
