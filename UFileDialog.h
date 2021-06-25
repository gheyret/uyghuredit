#ifndef CUFILEDIALOG_H
#define CUFILEDIALOG_H -1
#include "CDialog.h"
#include <windows.h>
#include "ortaq.h"

class CUFileDialog
{
public:
	CUFileDialog(BOOL bOpenFileDialog,wchar_t *lpszFileName,wchar_t *lpszFilter,BOOL asasiy=TRUE,BOOL belge=TRUE);
	UINT   UShow(HINSTANCE _gHInstance,HWND _ghWnd,BOOL HideCharSet=FALSE);
	int    UGetCodePage();
	BOOL   UGetBelge();
	BOOL   UGetAsasiy();
	HWND   m_PrnWnd;
	BOOL   OnInitDialog( HWND, WPARAM wParam, LPARAM lParam );
	wchar_t *UGetFileName();
	void    OnBnClickedAsasirayon();
	void    OnBnClickedBelgisi();
	void    OnCbnSelchangeCode();
private:
	struct OPENFILENAMEEX: public OPENFILENAME
	{
		void*	pvReserved;
		DWORD	dwReserved;
		DWORD	FlagsEx;
	};
	OPENFILENAMEEX	m_ofn;

	HWND	m_Belge;
	HWND    m_Asasiy;
	HWND    m_comCodePage;
	BOOL	m_Open;
	BOOL    m_bBelge;
	BOOL    m_bAsasiy;
	int     m_CodePage;
	void    SetTexts(HWND hwnd);
	wchar_t m_FileName[MAX_PATH];
	wchar_t *m_Filter;
	BOOL    m_HideSel;

	HINSTANCE _mHInstance;
};
#endif
