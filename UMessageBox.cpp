#include "UMessageBox.h"

UMessageBox *cMain=NULL;
extern wchar_t* gUGetVal(wchar_t *Key);
extern int gUSetWindowCenter(HWND hWnd,int width,int height);
extern int gUSetWindowCenter(HWND hWnd);


INT_PTR CALLBACK UWindowProc(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	if(uMsg==WM_INITDIALOG)
	{
		cMain=(UMessageBox*)lParam;
	}
	if(cMain!=NULL)
	{
		return cMain->UPMessage(hwndDlg,uMsg,wParam,lParam);
	}
	else{
		return DefWindowProc(hwndDlg,uMsg,wParam,lParam);
	}
} 

INT_PTR UMessageBox::UShow(HINSTANCE hInstance, HWND hwndOwner,wchar_t *Title,wchar_t *Uchur, UINT buttons)
{
	m_hInstance=hInstance;
	m_UTitle=Title;
	m_UUchur=Uchur;
	m_UButtons=buttons;
	return::DialogBoxParam(hInstance,MAKEINTRESOURCE(IDD),hwndOwner,(DLGPROC)UWindowProc,(LPARAM)this);
}


UMessageBox::~UMessageBox()
{
}

INT_PTR UMessageBox::UPMessage(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	switch (uMsg)
	{
		case WM_INITDIALOG:
			{
				m_hWnd=hwndDlg;
				HICON hIconSm=::LoadIcon(m_hInstance, MAKEINTRESOURCE(IDR_UYGHUREDITICO_S));
				SendMessage(m_hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIconSm);
				SetTexts();
				gUSetWindowCenter(hwndDlg);
			}
			return TRUE;
			break;
		case WM_CLOSE:
			{
				EndDialog(hwndDlg,IDCANCEL);
			}
			break;
		case WM_COMMAND:
			{
				UINT msg=HIWORD(wParam);
				UINT item=LOWORD(wParam);
				if(msg==BN_CLICKED)
				{
					if(item==TAL_BTN_HE)
					{
						EndDialog(hwndDlg,IDYES);
					}
					else if(item==TAL_BTN_YAQ)
					{
						EndDialog(hwndDlg,IDNO);
					}
					else if(item==SETFONT_CANCEL||item==TAL_BTN_TOHTA)
					{
						EndDialog(hwndDlg,IDCANCEL);
					}
					else if(item==SETFONT_TAMAM)
					{
						EndDialog(hwndDlg,IDOK);
					}
					else if(item==TAL_BTN_HEMMNI)
					{
						EndDialog(hwndDlg,TAL_BTN_HEMMNI);
					}
				}
			}
			return TRUE;
			break;
		case WM_PAINT:
			UOnPaint();
			return TRUE;
		default:
			return FALSE;
	}
	return FALSE;
}

// korsetmilaerni ozgertidu
// Yeni barliq Uyghurche korsetmilerni 
void UMessageBox::SetTexts()
{
	SetWindowText(m_hWnd,m_UTitle);
	
	HWND wndHE,wndYAQ,wndALL,wndTAMAM,wndINAWETSIZ,wndSTOP;

	wndHE=GetDlgItem(m_hWnd,TAL_BTN_HE);
	if(wndHE!=NULL)SetWindowText(wndHE,gUGetVal(L"MSG_TAL_BTN_HE"));
	
	wndALL=GetDlgItem(m_hWnd,TAL_BTN_HEMMNI);
	if(wndALL!=NULL)SetWindowText(wndALL,gUGetVal(L"MSG_TAL_BTN_HEMMNI"));
	
	wndYAQ=GetDlgItem(m_hWnd,TAL_BTN_YAQ);
	if(wndYAQ!=NULL)SetWindowText(wndYAQ,gUGetVal(L"MSG_TAL_BTN_YAQ"));

	wndSTOP=GetDlgItem(m_hWnd,TAL_BTN_TOHTA);
	if(wndSTOP!=NULL)SetWindowText(wndSTOP,gUGetVal(L"MSG_TAL_BTN_TOHTA"));
	
	wndTAMAM=GetDlgItem(m_hWnd,SETFONT_TAMAM);
	if(wndTAMAM!=NULL)SetWindowText(wndTAMAM,gUGetVal(L"MSG_SETFONT_TAMAM"));
	
	wndINAWETSIZ=GetDlgItem(m_hWnd,SETFONT_CANCEL);
	if(wndINAWETSIZ!=NULL)SetWindowText(wndINAWETSIZ,gUGetVal(L"MSG_SETFONT_CANCEL"));
	

	RECT rc,rcBut;
	int left,top;
	int butH,butW;
	int arliq=5;
	GetClientRect(m_hWnd,&rc);
	GetClientRect(wndTAMAM,&rcBut);
	butH=rcBut.bottom-rc.top+2;
	butW=rcBut.right-rcBut.left+3;
	top=42;
	if(m_UButtons==MB_OK)
	{
		ShowWindow(wndTAMAM,SW_SHOW);
		ShowWindow(wndHE,SW_HIDE);
		ShowWindow(wndYAQ,SW_HIDE);
		ShowWindow(wndALL,SW_HIDE);
		ShowWindow(wndINAWETSIZ,SW_HIDE);
		ShowWindow(wndSTOP,SW_HIDE);
		left=((rc.right-rc.left)-butW)/2;
		MoveWindow(wndTAMAM,left,top,butW,butH,TRUE);
	}
	else if(m_UButtons==MB_YESNOCANCEL)
	{
		ShowWindow(wndSTOP,SW_HIDE);
		ShowWindow(wndTAMAM,SW_HIDE);
		ShowWindow(wndALL,SW_HIDE);
		ShowWindow(wndHE,SW_SHOW);
		ShowWindow(wndYAQ,SW_SHOW);
		ShowWindow(wndINAWETSIZ,SW_SHOW);

		left=((rc.right-rc.left)-(butW*3+2*arliq))/2;

		MoveWindow(wndHE,left,top,butW,butH,TRUE);
		left=left+butW+arliq;
		MoveWindow(wndYAQ,left,top,butW,butH,TRUE);
		left=left+butW+arliq;
		MoveWindow(wndINAWETSIZ,left,top,butW,butH,TRUE);
		
	}
	else if(m_UButtons==MB_YESNOSTOP)
	{
		ShowWindow(wndTAMAM,SW_HIDE);
		ShowWindow(wndALL,SW_HIDE);
		ShowWindow(wndINAWETSIZ,SW_HIDE);
		ShowWindow(wndHE,SW_SHOW);
		ShowWindow(wndYAQ,SW_SHOW);
		ShowWindow(wndSTOP,SW_SHOW);
		
		left=((rc.right-rc.left)-(butW*3+2*arliq))/2;

		MoveWindow(wndHE,left,top,butW,butH,TRUE);
		left=left+butW+arliq;
		MoveWindow(wndYAQ,left,top,butW,butH,TRUE);
		left=left+butW+arliq;
		MoveWindow(wndSTOP,left,top,butW,butH,TRUE);
	}
	
	else if(m_UButtons==MB_YESNO)
	{
		ShowWindow(wndHE,SW_SHOW);
		ShowWindow(wndYAQ,SW_SHOW);
		ShowWindow(wndALL,SW_HIDE);
		ShowWindow(wndTAMAM,SW_HIDE);
		ShowWindow(wndINAWETSIZ,SW_HIDE);
		ShowWindow(wndSTOP,SW_HIDE);
		left=((rc.right-rc.left)-(butW*2+arliq))/2;
		
		MoveWindow(wndHE,left,top,butW,butH,TRUE);
		left=left+butW+arliq;
		MoveWindow(wndYAQ,left,top,butW,butH,TRUE);
	}
	
	else if(m_UButtons==MB_YESNOALLSTOP)
	{
		ShowWindow(wndHE,SW_SHOW);
		ShowWindow(wndYAQ,SW_SHOW);
		ShowWindow(wndALL,SW_SHOW);
		ShowWindow(wndSTOP,SW_SHOW);
		ShowWindow(wndINAWETSIZ,SW_HIDE);
		ShowWindow(wndTAMAM,SW_HIDE);
		
		left=((rc.right-rc.left)-(butW*4+3*arliq))/2;
		MoveWindow(wndHE,left,top,butW,butH,TRUE);
		left=left+butW+arliq;
		MoveWindow(wndYAQ,left,top,butW,butH,TRUE);
		left=left+butW+arliq;
		MoveWindow(wndALL,left,top,butW,butH,TRUE);
		left=left+butW+arliq;
		MoveWindow(wndSTOP,left,top,butW,butH,TRUE);
	}
}

UMessageBox::UMessageBox()
{
}


void UMessageBox::UOnPaint()
{
	PAINTSTRUCT ps;
    HDC dc = BeginPaint(m_hWnd, &ps);
    SIZE sz;
	RECT rc;
	int left;
	
	HFONT font=(HFONT)SendMessage(m_hWnd,WM_GETFONT,0,0);
	if(font!=NULL)
	{
		SelectObject(dc,font);
	}
	GetClientRect(m_hWnd,&rc);
	SetBkMode(dc,TRANSPARENT);	
	GetTextExtentPoint32W(dc,m_UUchur,(int)wcslen(m_UUchur),&sz);
	left=(rc.right-sz.cx)/2;
	TextOutW(dc, left,10 ,m_UUchur,(int)wcslen(m_UUchur));
    EndPaint(m_hWnd, &ps); 
}
