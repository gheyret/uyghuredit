#include <windows.h>
#include "resource.h"
#include "UCaptionButton.h"


LRESULT CALLBACK CapButtonWinProc (HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	UCaptionButton *cMain=(UCaptionButton*)GetProp(hwnd, UNAME);
	if(cMain!=NULL)
	{
		return cMain->UProcessMessage(hwnd,message,wParam,lParam);
	}
	else
	{
    	return DefWindowProc (hwnd, message, wParam, lParam);
    }
}

UCaptionButton::UCaptionButton()
{
}

UCaptionButton::~UCaptionButton()
{
	if(hUUBitmap!=NULL) DeleteObject(hUUBitmap);
	if(hULBitmap!=NULL) DeleteObject(hULBitmap);
}

void UCaptionButton::UInstall(HINSTANCE hInstance,HWND hwnd,KUNUPKA kun,UINTERFACE_LANG lang)
{
	_gHInstance=hInstance;
	SetProp(hwnd, UNAME, (HANDLE)this);
	hUUBitmap=(HBITMAP)LoadBitmap(_gHInstance,MAKEINTRESOURCE(UEDIT_BITKONA));
	hULBitmap=(HBITMAP)LoadBitmap(_gHInstance,MAKEINTRESOURCE(UEDIT_BITUKY));
	wpOldProc = (WNDPROC)SetWindowLong(hwnd, GWL_WNDPROC, (LONG)CapButtonWinProc);

	if(kun==KUNUPKA_SYSTEM)
	{
		m_UUPushed=FALSE;
		m_ULPushed=FALSE;
	}
	else if(kun==KUNUPKA_LATIN)
	{
		m_UUPushed=FALSE;
		m_ULPushed=TRUE;
	}
	else if(kun==KUNUPKA_UYGHUR)
	{
		m_UUPushed=TRUE;
		m_ULPushed=FALSE;
	}else if(kun==KUNUPKA_ALAHIDE)
	{
		m_UUPushed=TRUE;
		m_ULPushed=TRUE;
	}
	m_CurrentKey=kun;
	USetUILang(lang);
	PostMessage(hwnd,WM_COMMAND,BASHQA_KUNUPKA,m_CurrentKey);
}

void  UCaptionButton::USetUILang(UINTERFACE_LANG lang)
{
	if(LANG_UEY==lang)
	{
		m_RTL=TRUE;
	}
	else
	{
		m_RTL=FALSE;
	}
}

LRESULT UCaptionButton::UProcessMessage(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	BOOL ret=FALSE;
	switch(message)
	{
	   case WM_NCACTIVATE:
			DefWindowProc(hwnd, message, wParam, lParam );
			UPaintCaptionBut(hwnd);
			if ((BOOL)wParam == FALSE)
			{
		        ret=TRUE;
		    }
		    break;
		case WM_NCPAINT:
			DefWindowProc( hwnd, message, wParam, lParam );
   			UCalcCaptionButPos(hwnd);
			UPaintCaptionBut( hwnd);
			break;
		case WM_SETTEXT:
			DefWindowProc( hwnd, message, wParam, lParam );
			UPaintCaptionBut( hwnd);
			break;
		case WM_NCHITTEST:
			ret=UNCHitTest(hwnd, wParam, lParam);
			break;
		case WM_NCLBUTTONDBLCLK:
		case WM_NCLBUTTONDOWN:
			ret=UNCLButtonDown(hwnd, message, wParam, lParam);
			break;
		case WM_NCLBUTTONUP:
			ret=UNCLButtonUp(hwnd,wParam, lParam);
			break;
		case WM_COMMAND:
		{
			UINT cmdID= LOWORD(wParam);
			if(cmdID==BASHQA_KUNUPKA_KONA)
			{
				USetKunupka(hwnd,KUNUPKA_UYGHUR);
				ret=FALSE;
			}
			else if(cmdID==BASHQA_KUNUPKA_UKY)
			{
				USetKunupka(hwnd,KUNUPKA_LATIN);
				ret=FALSE;
			}
			else if(cmdID==BASHQA_KUNUPKA_OZGERT){//ctrl+k ni bir terep qilidu
                UKunupkaOzgert(hwnd);
				ret=FALSE;
			}
			else if(cmdID==BASHQA_KUNUPKA_ALAHIDE){
                USetKunupka(hwnd,KUNUPKA_ALAHIDE);
				ret=FALSE;
			}
			else if(cmdID==BASHQA_KUNUPKA_SYSTEM)
			{
				ret=FALSE;
				USetKunupka(hwnd,KUNUPKA_SYSTEM);
			}
			else{
				ret=CallWindowProc(wpOldProc, hwnd, message, wParam, lParam);
			}
			break;
		}
		default:
			ret=CallWindowProc(wpOldProc, hwnd, message, wParam, lParam);
	}
	return ret;
}

void UCaptionButton::UKunupkaOzgert(HWND hwnd)
{
    KUNUPKA yengi;
    if(m_CurrentKey==KUNUPKA_SYSTEM)
    {
        yengi=KUNUPKA_UYGHUR;
    }
    else if(m_CurrentKey==KUNUPKA_UYGHUR){
        yengi=KUNUPKA_LATIN;
    }
    else if(m_CurrentKey==KUNUPKA_LATIN)
    {
        yengi=KUNUPKA_ALAHIDE;
    }
    else if(m_CurrentKey==KUNUPKA_ALAHIDE){
        yengi=KUNUPKA_SYSTEM;
    }
    else{
        yengi=KUNUPKA_UYGHUR;
    }
    USetKunupka(hwnd,yengi);
}


LRESULT UCaptionButton::UNCHitTest(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	POINT pt;
	UINT  ret;
	pt.x = (short)LOWORD(lParam);
	pt.y = (short)HIWORD(lParam);

	ret = CallWindowProc(wpOldProc, hwnd, WM_NCHITTEST, wParam, lParam);

	//If the mouse is in the caption, then check to
	//see if it is over one of our buttons
	if(ret == HTCAPTION)
	{
		GetWindowRect(hwnd,&rc);
		// Bu Yerde Pt Putkun Ekrangah nisbeten etqandiki kordinati. uni hazirqi ramkining kordinatigha aylandurush zorur
		if(m_RTL==TRUE)
		{
			pt.x=rc.right-pt.x;
		}
		else
		{
			pt.x=pt.x-rc.left;
		}
		pt.y=pt.y-rc.top;
		if(PtInRect(&m_rcU, pt) || PtInRect(&m_rcL,pt))
		{
//			wchar_t buf[1024];
//			wsprintf(buf,L"(%d,%d,%d,%d),(%d,%d)",m_rcU.left,m_rcU.top,m_rcU.right,m_rcU.bottom,pt.x,pt.y);
//			SetWindowText(hwnd,buf);
			return HTBORDER;
		}
	}
	return ret;
}


LRESULT UCaptionButton::UNCLButtonDown(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	POINT pt;
	UINT  ret;
	pt.x = (short)LOWORD(lParam);
	pt.y = (short)HIWORD(lParam);

	ret = CallWindowProc(wpOldProc, hwnd, msg, wParam, lParam);

	//If the mouse is in the caption, then check to
	//see if it is over one of our buttons
	if(wParam == HTBORDER)
	{
		GetWindowRect(hwnd,&rc);
		// Bu Yerde Pt Putkun Ekrangah nisbeten etqandiki kordinati. uni hazirqi ramkining kordinatigha aylandurush zorur
		if(m_RTL==TRUE)
		{
			pt.x=rc.right-pt.x;
		}
		else
		{
			pt.x=pt.x-rc.left;
		}

		pt.y=pt.y-rc.top;
		if(PtInRect(&m_rcU, pt))
		{
			m_UUPushed=TRUE;
			m_ULPushed=FALSE;
			UPaintCaptionBut(hwnd);
			return 0;
		}
		else if(PtInRect(&m_rcL,pt))
		{
			m_UUPushed=FALSE;
			m_ULPushed=TRUE;
			UPaintCaptionBut(hwnd);
			return 0;
		}
	}
	return ret;
}

void UCaptionButton::USetKunupka(HWND hwnd, KUNUPKA kun)
{
	if(m_CurrentKey!=KUNUPKA_UYGHUR&&m_CurrentKey!=KUNUPKA_SYSTEM&&m_CurrentKey!=KUNUPKA_LATIN &&m_CurrentKey!=KUNUPKA_ALAHIDE)
	{
		m_CurrentKey=KUNUPKA_SYSTEM;
	}
	if(kun==KUNUPKA_UYGHUR && m_CurrentKey==KUNUPKA_UYGHUR)
	{
		m_CurrentKey=KUNUPKA_SYSTEM;
		m_UUPushed=FALSE;
		m_ULPushed=FALSE;
	}
	else if(kun==KUNUPKA_LATIN && m_CurrentKey==KUNUPKA_LATIN)
	{
		m_CurrentKey=KUNUPKA_SYSTEM;
		m_UUPushed=FALSE;
		m_ULPushed=FALSE;
	}
	else if(kun==KUNUPKA_UYGHUR)
	{
		m_CurrentKey=kun;
		m_UUPushed=TRUE;
		m_ULPushed=FALSE;
	}
	else if(kun==KUNUPKA_LATIN)
	{
		m_CurrentKey=kun;
		m_UUPushed=FALSE;
		m_ULPushed=TRUE;
	}
	else if(kun==KUNUPKA_SYSTEM){
		m_CurrentKey=KUNUPKA_SYSTEM;
		m_UUPushed=FALSE;
		m_ULPushed=FALSE;
	}else if(kun==KUNUPKA_ALAHIDE){
		m_CurrentKey=KUNUPKA_ALAHIDE;
		m_UUPushed=TRUE;
		m_ULPushed=TRUE;
	}
	UPaintCaptionBut(hwnd);
	SendMessage(hwnd,WM_COMMAND,BASHQA_KUNUPKA,m_CurrentKey);
}

LRESULT UCaptionButton::UNCLButtonUp(HWND hwnd, WPARAM wParam, LPARAM lParam)
{
	RECT rc;
	POINT pt;
	UINT  ret;
	pt.x = (short)LOWORD(lParam);
	pt.y = (short)HIWORD(lParam);

	ret = CallWindowProc(wpOldProc, hwnd, WM_NCLBUTTONUP, wParam, lParam);

	//If the mouse is in the caption, then check to
	//see if it is over one of our buttons
	if(wParam == HTBORDER)
	{
		GetWindowRect(hwnd,&rc);
		// Bu Yerde Pt Putkun Ekrangah nisbeten etqandiki kordinati. uni hazirqi ramkining kordinatigha aylandurush zorur
		if(m_RTL==TRUE)
		{
			pt.x=rc.right-pt.x;
		}
		else
		{
			pt.x=pt.x-rc.left;
		}
		pt.y=pt.y-rc.top;
		if(PtInRect(&m_rcU, pt)&&m_UUPushed)
		{
			if(m_CurrentKey!=KUNUPKA_UYGHUR&&m_CurrentKey!=KUNUPKA_SYSTEM&&m_CurrentKey!=KUNUPKA_LATIN)
			{
				m_CurrentKey=KUNUPKA_SYSTEM;
			}
			if(m_CurrentKey==KUNUPKA_UYGHUR)
			{
				m_UUPushed=FALSE;
				m_CurrentKey=KUNUPKA_SYSTEM;
			}
			else
			{
				m_UUPushed=TRUE;
				m_CurrentKey=KUNUPKA_UYGHUR;
			}
			m_ULPushed=FALSE;
			UPaintCaptionBut(hwnd);
		}
		else if(PtInRect(&m_rcL,pt)&&m_ULPushed)
		{
			if(m_CurrentKey==KUNUPKA_LATIN)
			{
				m_ULPushed=FALSE;
				m_CurrentKey=KUNUPKA_SYSTEM;
			}
			else
			{
				m_ULPushed=TRUE;
				m_CurrentKey=KUNUPKA_LATIN;
			}
			m_UUPushed=FALSE;
			UPaintCaptionBut(hwnd);
		}
		SendMessage(hwnd,WM_COMMAND,BASHQA_KUNUPKA,m_CurrentKey);
		return 0;
	}
	return ret;
}

void UCaptionButton::UCalcCaptionButPos(HWND hWnd)
{
       RECT rcW;
       GetWindowRect( hWnd, (LPRECT)&rcW );

	   int butW=GetSystemMetrics( SM_CXSIZE );
	   int butH=GetSystemMetrics( SM_CYSIZE );

	   int bodW=GetSystemMetrics( SM_CXBORDER );
	   int bodH=GetSystemMetrics( SM_CYBORDER );

       int frmW=GetSystemMetrics(SM_CXSIZEFRAME);
       int frmH=GetSystemMetrics(SM_CYSIZEFRAME);


	   int right=(rcW.right-rcW.left)-(bodW+frmW);

	   m_rcU.top=bodH+frmH;
	   m_rcL.top=bodH+frmH;

	   m_rcU.bottom=m_rcU.top+butH-2;
	   m_rcL.bottom=m_rcL.top+butH-2;

	   m_rcU.right=right;
	   m_rcU.left=m_rcU.right-(butW+4);

	   m_rcL.right=m_rcU.left-1;
	   m_rcL.left=m_rcL.right-(butW+4);


       DWORD dwStyle = GetWindowLong(hWnd, GWL_STYLE);
       right=0;
       if(dwStyle & WS_SYSMENU)
	   {
			right+=butW;
	   }
	   if(dwStyle & (WS_MINIMIZEBOX | WS_MAXIMIZEBOX) )
	   {
			right+=2*butW;
	   }
       DWORD dwExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);
       if(dwExStyle & WS_EX_CONTEXTHELP)
	   {
			right+=butW;
	   }

	   m_rcU.left-=right;
	   m_rcU.right-=right;

	   m_rcL.left-=right;
	   m_rcL.right-=right;

}

void UCaptionButton::UPaintCaptionBut(HWND hWnd)
{
      HDC hDC = GetWindowDC( hWnd );
  	  COLORREF colorOld=GetSysColor(COLOR_3DFACE);
	  if(m_UUPushed)
	  {
      	DrawEdge(hDC,&m_rcU, EDGE_SUNKEN, BF_RECT);
      	colorOld=RGB(0,255,0);
      }
      else
      {
      	DrawEdge(hDC,&m_rcU, EDGE_RAISED, BF_RECT);
      }

	  UShowBitMap(hDC,&m_rcU,hUUBitmap,colorOld);

  	  colorOld=GetSysColor(COLOR_3DFACE);
      if(m_ULPushed)
      {
      	DrawEdge(hDC,&m_rcL, EDGE_SUNKEN, BF_RECT);
      	colorOld=RGB(0,255,0);
      }
      else
      {
      	DrawEdge(hDC,&m_rcL, EDGE_RAISED, BF_RECT);
      }

	  UShowBitMap(hDC,&m_rcL,hULBitmap,colorOld);
      ReleaseDC( hWnd, hDC );
}

void UCaptionButton::UShowBitMap(HDC hDC,RECT *rect,HBITMAP hBitmap, COLORREF colorOld)
{
	BITMAP bm;
	int cx;
	int cy;

	RECT rc;
	rc.left=rect->left;
	rc.top=rect->top;
	rc.right=rect->right;
	rc.bottom=rect->bottom;
	InflateRect(&rc,-2,-2);

	GetObject(hBitmap, sizeof bm, &bm);
	cx = bm.bmWidth;
	cy = bm.bmHeight;

	HDC memdc = CreateCompatibleDC(hDC);
    SetBkMode(memdc,TRANSPARENT);
	HBITMAP hOldBM = (HBITMAP)SelectObject(memdc, hBitmap);
	colorOld=SetBkColor(hDC,colorOld);
	StretchBlt(hDC, rc.left, rc.top, rc.right-rc.left, rc.bottom-rc.top, memdc, 0, 0,cx,cy, SRCCOPY);
	SetBkColor(hDC, colorOld);
	SelectObject(memdc, hOldBM);
	DeleteDC(memdc);
}

