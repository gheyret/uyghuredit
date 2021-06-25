#ifndef _CDIALOG_H_
#define _CDIALOG_H_ 1
#include <windows.h>
#include "UCaptionButton.h"
#include "ortaq.h"

class CDialog
{
public:
	CDialog(TCHAR *title);
	virtual ~CDialog();
	HWND   GetDlgItem(UINT id);
	virtual INT_PTR DispatchEvent( HWND, UINT, WPARAM, LPARAM );
	INT_PTR DoModal( HINSTANCE, HWND, int);
	HWND DoModeless( HINSTANCE, HWND, int, int );
	void CloseDialog( int );
	virtual BOOL OnInitDialog( HWND, WPARAM wParam, LPARAM lParam );
	void    USetWindowCenter();
	virtual BOOL OnDestroy( void );
	virtual BOOL OnNotify( WPARAM wParam, LPARAM lParam ){return FALSE;}
	virtual BOOL OnSize( WPARAM wParam, LPARAM lParam );
	virtual BOOL OnMove( WPARAM wParam, LPARAM lParam );
	virtual BOOL OnDrawItem( WPARAM wParam, LPARAM lParam );
	virtual BOOL OnTimer( WPARAM wParam ){return TRUE;}
	virtual BOOL OnKeyDown( WPARAM wParam, LPARAM lParam ){return TRUE;}
	virtual BOOL OnDeviceChange( WPARAM wParam, LPARAM lParam ){return TRUE;}
	virtual int GetData( void ){return 1;}
	virtual void SetData( void ){return;}
	virtual BOOL OnBnClicked( int );
	virtual BOOL OnCbnSelChange( HWND hwndCtl, int wID ){return FALSE;}
	virtual BOOL OnEditChange( HWND hwndCtl, int wID ){return FALSE;}

	virtual BOOL OnLbnDblclk( int wID ){return FALSE;}
	virtual BOOL OnKillFocus( WPARAM wParam, LPARAM lParam ){return FALSE;}
	virtual BOOL OnActivate( WPARAM wParam, LPARAM lParam ){return FALSE;};
	virtual int OnVKeyToItem( WPARAM wParam, LPARAM lParam ){ return -1; }
	virtual LRESULT OnCharToItem( WPARAM wParam, LPARAM lParam ){ return -1; }

	virtual void SetBitmap(HBITMAP hbmp);

	HINSTANCE		m_hInstance;
	HWND			m_hwndParent;
	HWND			m_hWnd;
	LPARAM			m_lParam;
	BOOL			m_bModal;
	int				m_nShowCmd;
	int				m_nWidth;
	int				m_nHeight;
	int				m_xPos;
	int				m_yPos;
	BOOL			m_bInited;
	int             m_DID;
	HBITMAP         m_hBitmap;
	TCHAR           *m_strTitle;
protected:
	BOOL OnCommand( WPARAM, LPARAM );
//	UCaptionButton _mCaptionBut;
};

#endif /* _CDIALOG_H_ */

