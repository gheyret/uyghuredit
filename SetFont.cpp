#include "SetFont.h"
#include "ortaq.h"

USetFont *g_FontDlg;
extern wchar_t* gUGetVal(wchar_t *Key);
extern int gUSetWindowCenter(HWND hWnd,int width,int height);
extern int gUSetWindowCenter(HWND hWnd);
extern BOOL gUIsUyghur(wchar_t Herip);

INT_PTR CALLBACK USetFontDlgProc(HWND hwndDlg,UINT uMsg,WPARAM wParam,LPARAM lParam)
{
	INT_PTR ret=FALSE;
	switch( uMsg )
	{
		case WM_CTLCOLORDLG:
//			ret=TRUE;
			break;
		case WM_INITDIALOG:
			g_FontDlg->UOnInitDialog(hwndDlg);
//			ret=TRUE;
			break;
		case WM_COMMAND:
		{
//			ret= TRUE;
			UINT msg=HIWORD(wParam);
			UINT item=LOWORD(wParam);
			if((item==IDC_COMBO1||item==IDC_COMBO2||item==IDC_COMBO3||item==IDC_COMBO4) && msg==CBN_SELCHANGE)
			{
				g_FontDlg->UUpdateData();
			}
			else if((item==IDC_CHECK1||item==IDC_CHECK2) && msg==BN_CLICKED)
			{
				g_FontDlg->UUpdateData();
			}
			else if(item==SETFONT_TAMAM && msg==BN_CLICKED)
			{
				EndDialog(hwndDlg,SETFONT_TAMAM);
			}
			else  if(item==SETFONT_CANCEL && msg==BN_CLICKED)
			{
				EndDialog(hwndDlg,SETFONT_CANCEL);
			}
			break;
		}
		case WM_DRAWITEM:
            g_FontDlg->UShowSample();
            break;
		case WM_PAINT:
			g_FontDlg->UOnPaint(hwndDlg);
			ret=TRUE;
			break;
		case WM_CLOSE:
			EndDialog(hwndDlg,SETFONT_CANCEL);
			break;
		default:
//			ret=FALSE;
			break;
	}
	return ret;
}


USetFont::USetFont(LPUEDIT Uef)
{
	m_UygFont=NULL;
	m_UygFont=NULL;
	memcpy(&m_UEFont,Uef,sizeof(UEDIT));
	g_FontDlg=this;
}

INT_PTR USetFont::UShowModal(HINSTANCE hInstance, HWND hwndParent)
{
	mUyghurEditInst=hInstance;
	return::DialogBox(
		mUyghurEditInst,
		MAKEINTRESOURCE(IDD),
		hwndParent,
		(DLGPROC)USetFontDlgProc
	);
}

void USetFont::UGetSettings(LPUEDIT Uef)
{
	memcpy(Uef,&m_UEFont,sizeof(UEDIT));
	return;
}

USetFont::~USetFont()
{
	if(m_UygFont!=NULL)
	{
		DeleteObject(m_UygFont);
		m_UygFont=NULL;
	}

	if(m_LocFont!=NULL)
	{
		DeleteObject(m_LocFont);
		m_LocFont=NULL;
	}
}

void USetFont::UOnPaint(HWND hWnd)
{
    PAINTSTRUCT ps;
    BeginPaint (hWnd, &ps);
	UShowSample();
    EndPaint (hWnd, &ps);
}

void USetFont::UShowSample()
{
	wchar_t Buf[50];
	int x,y=0;
	COLORREF frColor;
	RECT rc;

	Buf[0]=0xfe97;
	Buf[1]=0xfeea;
	Buf[2]=0xfedb;
	Buf[3]=0xfee0;
	Buf[4]=0xfbe9;
	Buf[5]=0xfee4;
	Buf[6]=0xfe8e;
	Buf[7]=0xfedb;
	Buf[8]=0xfe8e;
	Buf[9]=0xfee5;
	Buf[10]=0x20;
	Buf[11]=0xfed7;
	Buf[12]=0xfbd8;
	Buf[13]=0xfee3;
	Buf[14]=0xfee0;
	Buf[15]=0xfbd8;
	Buf[16]=0xfed7;
	Buf[17]=0xfef0;
	Buf[18]=0x0A;
	Buf[19]=0x0;

	::wcscat(Buf,L"iqulmuQ nakamilkeT");

	HWND wnd=GetDlgItem(m_hWnd,IDC_KORNUSH);
	HDC dc=GetDC(wnd);
	SetBkMode(dc,TRANSPARENT);
	SetMapMode(dc,MM_TEXT);
	UCreateFont(dc);

	GetClientRect(wnd,&rc);
	HDC dcm;
	dcm=CreateCompatibleDC(dc);

	HBITMAP memBmp;
	memBmp=CreateCompatibleBitmap(dcm,rc.right,rc.bottom);
	SelectObject(dcm,memBmp);
	HBRUSH backGround=CreateSolidBrush(m_UEFont.mue_UEkran_Color);
	FillRect(dcm,&rc,backGround);

	x=rc.right-2;
	int width[1];
	int i=0;
	while(Buf[i]!=0x0)
	{
		if(Buf[i]==0x0A)
		{
			y+=this->qurIgizligi;
			x=rc.right-2;
		}
		else
		{
			if(gUIsUyghur(Buf[i]))
			{
				SelectObject(dcm,m_UygFont);
				frColor=m_UEFont.mue_UUYG_ForeColor;
			}
			else
			{
				SelectObject(dcm,m_LocFont);
				frColor=RGB(0,255,255);
			}
			GetCharWidth32(dcm,Buf[i],Buf[i],&width[0]);
			x=x-width[0];
			SetTextColor(dcm,frColor);
			TextOutW(dcm,x,y,&Buf[i],1);
		}
		i++;
	}

//	dc->StretchBlt(0,0,rc.right,rc.bottom,&dcm,0,0,rc.right,rc.bottom,SRCCOPY);
	BitBlt(dc,0,0,rc.right,rc.bottom,dcm,0,0,SRCCOPY);
	DeleteObject(memBmp);
	DeleteObject(backGround);
	DeleteDC(dcm);
	ReleaseDC(wnd,dc);
}

void USetFont::UCreateFont(HDC dc)
{
	if(m_UygFont!=NULL) DeleteObject(m_UygFont);
	if(m_LocFont!=NULL) DeleteObject(m_LocFont);

	LOGFONT logFnt;
	int reso=GetDeviceCaps(dc,LOGPIXELSY);
	memset(&logFnt,0x0,sizeof(LOGFONT));

	logFnt.lfHeight=-MulDiv((int)(m_UEFont.mue_FontPoint*10),reso,720);

	logFnt.lfItalic=m_UEFont.mue_Qiypash;
	if(m_UEFont.mue_Tom==TRUE)
	{
		logFnt.lfWeight=FW_BOLD;
	}
	else
	{
		logFnt.lfWeight=FW_REGULAR;
	}

	logFnt.lfOutPrecision=OUT_DEFAULT_PRECIS;
	logFnt.lfClipPrecision=CLIP_DEFAULT_PRECIS;
	logFnt.lfQuality=ANTIALIASED_QUALITY;
	logFnt.lfPitchAndFamily=DEFAULT_PITCH;

	wcscpy(logFnt.lfFaceName,m_UEFont.mue_UyghurFaceName);
	m_UygFont=CreateFontIndirect(&logFnt);

	wcscpy(logFnt.lfFaceName,m_UEFont.mue_LocalFaceName);
	m_LocFont=CreateFontIndirect(&logFnt);

	HFONT old=(HFONT)SelectObject(dc, m_UygFont);
	TEXTMETRIC tm;
	GetTextMetrics(dc,&tm);
	qurIgizligi=tm.tmHeight+tm.tmExternalLeading+m_UEFont.mue_QurArlighi;
	if(old!=NULL)DeleteObject(old);
}

void USetFont::UUpdateData()
{
	wchar_t retVal[100];
	retVal[0]=0x0;
	if(UGetSelectedItem(IDC_COMBO1,retVal)!=CB_ERR)
	{
		wcscpy(m_UEFont.mue_UyghurFaceName,retVal);
	}
	retVal[0]=0x0;
	if(UGetSelectedItem(IDC_COMBO2,retVal)!=CB_ERR)
	{
		wcscpy(m_UEFont.mue_LocalFaceName,retVal);
	}

	retVal[0]=0x0;
	if(UGetSelectedItem(IDC_COMBO3,retVal)!=CB_ERR)
	{
		m_UEFont.mue_FontPoint=(double)(_wtoi(retVal));
	}

	retVal[0]=0x0;
	if(UGetSelectedItem(IDC_COMBO4,retVal)!=CB_ERR)
	{
		m_UEFont.mue_QurArlighi=_wtoi(retVal);
	}

	m_UEFont.mue_Tom=(BYTE)(UGetCheckBoxVal(IDC_CHECK1));
	m_UEFont.mue_Qiypash=(BYTE)(UGetCheckBoxVal(IDC_CHECK2));

	UShowSample();
}

BOOL USetFont::UGetCheckBoxVal(UINT id)
{
	HWND wnd;
	wnd=GetDlgItem(m_hWnd,id);
	LRESULT ret=SendMessage(wnd,BM_GETCHECK,0x0,0x0);
	return ret;
}

void USetFont::USetCheckBoxVal(UINT id,BOOL val)
{
	HWND wnd;
	wnd=GetDlgItem(m_hWnd,id);
	if(val)
	{
		SendMessage(wnd,BM_SETCHECK,(WPARAM)BST_CHECKED,0x0);
	}
	else
	{
		SendMessage(wnd,BM_SETCHECK,(WPARAM)BST_UNCHECKED,0x0);
	}
}


BOOL USetFont::UOnInitDialog(HWND hWnd)
{
	m_hWnd=hWnd;

	HICON hIconSm=::LoadIcon(mUyghurEditInst, MAKEINTRESOURCE(IDR_UYGHUREDITICO_S));
	SendMessage(m_hWnd,WM_SETICON,ICON_SMALL,(LPARAM)hIconSm);

	UFillQurArlighi();
	UFillUyghurFace();
	UFillLocalFace();
	UFillFontPoint();


	SetTexts();

	wchar_t item[100];
	USetSelectItem(IDC_COMBO1,m_UEFont.mue_UyghurFaceName);
	USetSelectItem(IDC_COMBO2,m_UEFont.mue_LocalFaceName);

	wsprintf(item,L" %2d",(int)m_UEFont.mue_FontPoint);
	USetSelectItem(IDC_COMBO3,item);

	wsprintf(item,L" %2d",m_UEFont.mue_QurArlighi);
	USetSelectItem(IDC_COMBO4,item);

	USetCheckBoxVal(IDC_CHECK1,m_UEFont.mue_Tom);
	USetCheckBoxVal(IDC_CHECK2,m_UEFont.mue_Qiypash);

	gUSetWindowCenter(m_hWnd);

	UShowSample();
	return TRUE;
}

void USetFont::USetSelectItem(UINT id, wchar_t *item)
{
	HWND wnd;
	wnd=GetDlgItem(m_hWnd,id);
	SendMessage(wnd,CB_SELECTSTRING,(WPARAM)0, (LPARAM)item);
}


int USetFont::UGetSelectedItem(UINT id,wchar_t *str)
{
	HWND wnd;
	wnd=GetDlgItem(m_hWnd,id);
	LRESULT ret=SendMessage(wnd,CB_GETCURSEL,(WPARAM)0, (LPARAM)0);
	if(ret!=CB_ERR)
	{
		ret=SendMessage(wnd,CB_GETLBTEXT,(WPARAM)ret, (LPARAM)str);
	}
	return ret;
}

// korsetmilaerni ozgertidu
// Yeni barliq Uyghurche korsetmilerni
void USetFont::SetTexts()
{
	wchar_t* msg=gUGetVal(L"MSG_FONT_TITLE");
	SetWindowText(m_hWnd,msg);
	HWND wnd;
	wnd=GetDlgItem(m_hWnd,LABFONT_UYGHUR);
	SetWindowText(wnd,gUGetVal(L"MSG_LABFONT_UYGHUR"));
	wnd=GetDlgItem(m_hWnd,LABFONT_SYSTEM);
	SetWindowText(wnd,gUGetVal(L"MSG_LABFONT_SYSTEM"));
	wnd=GetDlgItem(m_hWnd,LABFONT_SIZE);
	SetWindowText(wnd,gUGetVal(L"MSG_LABFONT_SIZE"));
	wnd=GetDlgItem(m_hWnd,LABFONT_BOSHLUQ);
	SetWindowText(wnd,gUGetVal(L"MSG_LABFONT_BOSHLUQ"));
	wnd=GetDlgItem(m_hWnd,LABFONT_KORNUSH);
	SetWindowText(wnd,gUGetVal(L"MSG_LABFONT_KORNUSH"));
	wnd=GetDlgItem(m_hWnd,IDC_CHECK1);
	SetWindowText(wnd,gUGetVal(L"MSG_IDC_CHECK1"));
	wnd=GetDlgItem(m_hWnd,IDC_CHECK2);
	SetWindowText(wnd,gUGetVal(L"MSG_IDC_CHECK2"));
	wnd=GetDlgItem(m_hWnd,SETFONT_TAMAM);
	SetWindowText(wnd,gUGetVal(L"MSG_SETFONT_TAMAM"));
	wnd=GetDlgItem(m_hWnd,SETFONT_CANCEL);
	SetWindowText(wnd,gUGetVal(L"MSG_SETFONT_CANCEL"));
}



void USetFont::UFillQurArlighi()
{
	wchar_t buf[10];
	for(int i=-10;i<=10;i+=2)
	{
		wsprintf(buf,L" %2d",i);
		UAddString(IDC_COMBO4,buf);
	}
}

void USetFont::UFillFontPoint()
{
	wchar_t buf[100];
	int sizePoint[]={8,9,10,11,12,14,16,18,20,22,24,26,28,30,36,40,48,72};
	for(int i=0;i<19;i++)
	{
		wsprintf(buf,L" %2d",sizePoint[i]);
		UAddString(IDC_COMBO3,buf);
	}
}


// Barliq Uyghurche Fontlarni yeni arabic fontlarni bu yerde korsitidu
void USetFont::UFillUyghurFace()
{
    HDC dc = GetDC(m_hWnd);
	LOGFONTW log;
	memset(&log,0x0,sizeof(LOGFONTW));
	log.lfCharSet=ARABIC_CHARSET;
    EnumFontFamiliesExW(dc , &log, (FONTENUMPROC)EnumFontFamProcU, (LPARAM)this,0x0);
    ReleaseDC(m_hWnd,dc);
}

void USetFont::UAddString(UINT ctrlID,wchar_t *str)
{
	HWND wnd;
	wnd=GetDlgItem(m_hWnd,ctrlID);
	LRESULT ret=SendMessage(wnd,CB_FINDSTRINGEXACT,(WPARAM)-1, (LPARAM)str);
	if(ret==CB_ERR)
	{
		SendMessage(wnd,CB_ADDSTRING,0x0, (LPARAM)str);
	}
}

void USetFont::UFillLocalFace()
{
    HDC dc= GetDC(m_hWnd);
	LOGFONTW log;
	memset(&log,0x0,sizeof(LOGFONTW));
	log.lfCharSet=DEFAULT_CHARSET;
    EnumFontFamiliesExW(dc , &log, (FONTENUMPROC)EnumFontFamProcL, (LPARAM)this,0x0);
    ReleaseDC(m_hWnd,dc);
}


int CALLBACK USetFont::EnumFontFamProcU(ENUMLOGFONTEX *lpelf, NEWTEXTMETRICEX *lpntm, DWORD FontType, LPARAM lParam)
{
    if(FontType != TRUETYPE_FONTTYPE)
        return 1;
    wchar_t *facename = lpelf->elfLogFont.lfFaceName;
    USetFont* pDlg = (USetFont*)lParam;
    pDlg->UAddString(IDC_COMBO1,facename);
    return 1;
}


int CALLBACK USetFont::EnumFontFamProcL(ENUMLOGFONTEX *lpelf, NEWTEXTMETRICEX *lpntm, DWORD FontType, LPARAM lParam)
{
    if(FontType != TRUETYPE_FONTTYPE)
        return 1;
    wchar_t *facename = lpelf->elfLogFont.lfFaceName;
    USetFont* pDlg = (USetFont*)lParam;
    pDlg->UAddString(IDC_COMBO2,facename);
    return 1;
}
