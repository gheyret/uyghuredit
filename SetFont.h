#ifndef USETFONT_H
#define USETFONT_H 1

#include <windows.h>
#include <io.h>
#include "resource.h"
#include "UCommon.h"
#include "UCaptionButton.h"
#include "ortaq.h"

class USetFont
{
private:
	UEDIT        m_UEFont;
	BOOL UOnInitDialog();

	HFONT        m_UygFont;
	HFONT        m_LocFont;

	HINSTANCE   mUyghurEditInst;
	HWND         m_hWnd;
//	UCaptionButton _mCaptionBut;

	void        UCreateFont(HDC dc);
	void        UFillQurArlighi();
	void        UFillUyghurFace();
	void        UFillLocalFace();
	void        UFillFontPoint();
	static int	CALLBACK EnumFontFamProcU(ENUMLOGFONTEX *lpelf, NEWTEXTMETRICEX *lpntm, DWORD FontType, LPARAM lParam);
	static int  CALLBACK EnumFontFamProcL(ENUMLOGFONTEX *lpelf, NEWTEXTMETRICEX *lpntm, DWORD FontType, LPARAM lParam);
	int         qurIgizligi;
	BOOL        UGetCheckBoxVal(UINT id);
	void        USetCheckBoxVal(UINT id,BOOL val);
	void        USetSelectItem(UINT id, wchar_t *item);
	int         UGetSelectedItem(UINT id,wchar_t *str);
public:
	USetFont(LPUEDIT Uef);
	void        UShowSample();
	void        UGetSettings(LPUEDIT Uef);
	void        UAddString(UINT ctrlID,wchar_t *str);
	virtual     ~USetFont();
	enum { IDD = IDD_SETFONT };
	void        SetTexts();
	INT_PTR     UShowModal(HINSTANCE hInstance, HWND hwndParent);
	BOOL        UOnInitDialog(HWND wnd);
	void        UUpdateData();
	void        UOnPaint(HWND wnd);
};

#endif
