#include "CDialog.h"
#include "resource.h"

INT_PTR CALLBACK MyDialogProc(
	HWND hwndDlg,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam
)
{
	CDialog* pCDialog;
	switch( uMsg ){
	case WM_INITDIALOG:
		pCDialog = ( CDialog* )lParam;
		if( NULL != pCDialog ){
			return pCDialog->DispatchEvent( hwndDlg, uMsg, wParam, lParam );
		}else{
			return FALSE;
		}
	default:
		pCDialog = ( CDialog* )::GetWindowLong( hwndDlg, DWL_USER );
		if( NULL != pCDialog ){
			return pCDialog->DispatchEvent( hwndDlg, uMsg, wParam, lParam );
		}else{
			return FALSE;
		}
	}
}

void CDialog::SetBitmap(HBITMAP bmp)
{
	m_hBitmap=bmp;
}
CDialog::CDialog(TCHAR *title)
{
	m_hBitmap=NULL;
	m_hInstance = NULL;
	m_hwndParent = NULL;
	m_hWnd  = NULL;
	m_nShowCmd = SW_SHOW;
	m_xPos = -1;
	m_yPos = -1;
	m_nWidth = -1;
	m_nHeight = -1;
	m_DID=-1;
	m_strTitle=title;
	return;

}
CDialog::~CDialog()
{
	CloseDialog( 0 );
	return;
}

INT_PTR CDialog::DoModal( HINSTANCE hInstance, HWND hwndParent, int nDlgTemplete )
{
	m_bInited = FALSE;
	m_bModal = TRUE;
	m_hInstance = hInstance;
	m_hwndParent = hwndParent;
	m_DID=nDlgTemplete;
	return::DialogBoxParam(
		m_hInstance,
		MAKEINTRESOURCE( nDlgTemplete ),
		m_hwndParent,
		(DLGPROC)MyDialogProc,
		(LPARAM)this
	);
}

HWND CDialog::DoModeless( HINSTANCE hInstance, HWND hwndParent, int nDlgTemplete, int nCmdShow)
{
	m_bInited = FALSE;
	m_bModal = FALSE;
	m_hInstance = hInstance;
	m_hwndParent = hwndParent;
	m_DID=nDlgTemplete;
	m_hWnd =::CreateDialogParam(
		m_hInstance,
		MAKEINTRESOURCE( nDlgTemplete ),
		m_hwndParent,
		(DLGPROC)MyDialogProc,
		(LPARAM)this
	);
	if( NULL != m_hWnd ){
		::ShowWindow( m_hWnd, nCmdShow );
	}
	return m_hWnd;
}

void CDialog::CloseDialog( int nModalRetVal )
{
	if( NULL != m_hWnd ){
		if( m_bModal ){
			::EndDialog( m_hWnd, nModalRetVal );
		}else{
			::DestroyWindow( m_hWnd );
		}
		if(m_hBitmap!=NULL)
		{
			DeleteObject(m_hBitmap);
		}
		if(m_DID!=-1)
		{
			PostMessage(m_hwndParent,UM_WINDOWCLOSED,(WPARAM)m_DID,0x0);
		}
		m_hWnd = NULL;
	}
	return;
}

void CDialog::USetWindowCenter()
{
    RECT Parentrc;
    RECT New,rc;
    int width,height;
    if(m_hBitmap!=NULL)
    {
		BITMAP bm;
		GetObject(m_hBitmap,sizeof(BITMAP),&bm);
		width=bm.bmWidth;
		height=bm.bmHeight;
		LONG st=GetWindowLong(m_hWnd,GWL_STYLE);
		New.left=0;
		New.top=0;
		New.right=width;
		New.bottom=height;
		AdjustWindowRectEx(&New,st,FALSE,0x0);
		width=New.right-New.left;
		height=New.bottom-New.top;
    }
    else
    {
		GetWindowRect(m_hWnd,&rc);
		width=rc.right-rc.left;
		height=rc.bottom-rc.top;
	}
    GetWindowRect(m_hwndParent, (LPRECT)&Parentrc);
    New.left = Parentrc.left +(Parentrc.right-Parentrc.left - width)/2;
    New.top = Parentrc.top+(Parentrc.bottom -Parentrc.top- height)/2;
	New.bottom =height;
	New.right =width;
	MoveWindow(m_hWnd, New.left ,New.top ,New.right,New.bottom ,TRUE);
}


BOOL CDialog::OnInitDialog( HWND hwndDlg, WPARAM wParam, LPARAM lParam )
{
	m_hWnd = hwndDlg;
	::SetWindowLong( m_hWnd, DWL_USER, lParam );
	m_bInited = TRUE;
	if(m_strTitle!=NULL)::SetWindowText(m_hWnd,m_strTitle);
	HICON hIconSm=::LoadIcon(m_hInstance, MAKEINTRESOURCE(IDR_UYGHUREDITICO_S));
	SendMessage(m_hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIconSm);
	USetWindowCenter();
//	_mCaptionBut.UInstall(m_hInstance,hwndDlg,KUNUPKA_SYSTEM);
	return TRUE;
}

HWND CDialog::GetDlgItem(UINT id)
{
	return::GetDlgItem(m_hWnd,id);
}

BOOL CDialog::OnDestroy( void )
{
	m_hWnd = NULL;
	return TRUE;
}


BOOL CDialog::OnBnClicked( int wID )
{
	switch( wID ){
	case IDCANCEL:
		CloseDialog( 0 );
		return TRUE;
	case IDOK:
		CloseDialog( 0 );
		return TRUE;
	}
	return FALSE;
}


BOOL CDialog::OnSize( WPARAM wParam, LPARAM lParam )
{
	RECT	rc;
	::GetWindowRect( m_hWnd, &rc );
	m_xPos = rc.left;
	m_yPos = rc.top;
	m_nWidth = rc.right - rc.left;
	m_nHeight = rc.bottom - rc.top;
	return FALSE;

}

BOOL CDialog::OnMove( WPARAM wParam, LPARAM lParam )
{
	if( FALSE == m_bInited ){
		return TRUE;
	}
	RECT	rc;
	::GetWindowRect( m_hWnd, &rc );

	m_xPos = rc.left;
	m_yPos = rc.top;
	m_nWidth = rc.right - rc.left;
	m_nHeight = rc.bottom - rc.top;
	return TRUE;

}

BOOL CDialog::OnDrawItem( WPARAM wParam, LPARAM lParam)
{
	if( FALSE == m_bInited){
		return FALSE;
	}
	if(m_hBitmap==NULL) return FALSE;
	//int a;
	RECT rc;
	PAINTSTRUCT ps;
	HDC muDC = BeginPaint (m_hWnd, &ps);
	SetMapMode(muDC,MM_TEXT);
	GetClientRect(m_hWnd,&rc);
	HDC memDC=CreateCompatibleDC(muDC);
	SelectObject(memDC,m_hBitmap);
	BitBlt(muDC,0,0,rc.right,rc.bottom,memDC,0,0,SRCCOPY);
	DeleteDC(memDC);
	EndPaint(m_hWnd,&ps);
	return TRUE;
}

/* ダイアログのメッセージ処理 */
INT_PTR CDialog::DispatchEvent( HWND hwndDlg, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg ){
	case WM_INITDIALOG:	return OnInitDialog( hwndDlg, wParam, lParam );
	case WM_DESTROY:	return OnDestroy();
	case WM_COMMAND:	return OnCommand( wParam, lParam );
	case WM_NOTIFY:		return OnNotify( wParam, lParam );
	case WM_SIZE:
		m_hWnd = hwndDlg;
		return OnSize( wParam, lParam );
	case WM_MOVE:
		m_hWnd = hwndDlg;
		return OnMove( wParam, lParam );
	case WM_DRAWITEM:	return OnDrawItem( wParam, lParam );
	case WM_PAINT:
		OnDrawItem( wParam, lParam );
		return FALSE;
	case WM_TIMER:		return OnTimer( wParam );
	case WM_KEYDOWN:	return OnKeyDown( wParam, lParam );
	case WM_KILLFOCUS:	return OnKillFocus( wParam, lParam );
	case WM_ACTIVATE:	return OnActivate( wParam, lParam );
	case WM_VKEYTOITEM:	return OnVKeyToItem( wParam, lParam );
	case WM_CHARTOITEM:	return OnCharToItem( wParam, lParam );
	}
	return FALSE;
}

BOOL CDialog::OnCommand( WPARAM wParam, LPARAM lParam )
{
	WORD	wNotifyCode;
	WORD	wID;
	HWND	hwndCtl;
	wNotifyCode = HIWORD(wParam);
	wID			= LOWORD(wParam);
	hwndCtl		= (HWND) lParam;
	switch( wNotifyCode ){

	case CBN_SELCHANGE:	return OnCbnSelChange( hwndCtl, wID );
	case LBN_DBLCLK:	return OnLbnDblclk( wID );
	case EN_CHANGE:		return OnEditChange( hwndCtl, wID );
	case BN_CLICKED:	return OnBnClicked( wID );
	}
	return FALSE;
}


