#include "resource.h"
#include "UFileDialog.h"
#include "UCommon.h"

CUFileDialog *gFileDlg;
extern wchar_t* gUGetVal(wchar_t *Key);
extern int gUSetWindowCenter(HWND hWnd,int width,int height);
extern int gUSetWindowCenter(HWND hWnd);

UINT CALLBACK UHookProc(HWND hdlg , UINT uiMsg , WPARAM wp , LPARAM lp) {
	switch(uiMsg)
	{
		case WM_INITDIALOG:
			gFileDlg->OnInitDialog(hdlg,wp,lp);
			return FALSE;
		case WM_COMMAND:
			{
				UINT msg=HIWORD(wp);
				UINT item=LOWORD(wp);
				if(item==UFILEOPEN_CODE&& msg==CBN_SELCHANGE)
				{
					gFileDlg->OnCbnSelchangeCode();
					return TRUE;
				}
				else if(item==UFILEOPEN_BELGISI&& msg==BN_CLICKED)
				{
					gFileDlg->OnBnClickedBelgisi();
					return TRUE;
				}
				else if(item==UFILEOPEN_ASASIRAYON&& msg==BN_CLICKED)
				{
					gFileDlg->OnBnClickedAsasirayon();
					return TRUE;
				}
			};
			break;
		default:
			break;
	}
	return FALSE;
}


CUFileDialog::CUFileDialog(BOOL bOpenFileDialog,wchar_t *lpszFileName,wchar_t *lpszFilter,BOOL asasiy,BOOL belge)
{
	m_Open=bOpenFileDialog;
	wcscpy(m_FileName,lpszFileName);
	m_Filter=lpszFilter;
	int i=0;
	while(m_Filter[i]!=0x0)
	{
		if(m_Filter[i]=='|')
		{
			m_Filter[i]=0x0;
		}
		i++;
	}

	this->m_bAsasiy=asasiy;
	this->m_bBelge=belge;
	if(this->m_Open==TRUE)
	{
		this->m_CodePage=CP_ACP;
	}
	else
	{
		this->m_CodePage=CP_UTF8;
	}
	gFileDlg=this;
}

BOOL CUFileDialog::OnInitDialog( HWND hwnd, WPARAM wParam, LPARAM lParam )
{
	m_Belge=::GetDlgItem(hwnd,UFILEOPEN_BELGISI);
	m_Asasiy=::GetDlgItem(hwnd,UFILEOPEN_ASASIRAYON);
	m_comCodePage=::GetDlgItem(hwnd,UFILEOPEN_CODE);
	if(m_Open)
	{
		wchar_t* oPage[]={L"System",
			L"Bogha,Fangzheng hojjiti",
			L"Weifang DOS hojjiti",
			L"Weifang Windows hojjiti",
			L"Unicode(UTF-16LE)",
			L"Unicode(UTF-16BE)",
			L"Unicode(UTF-8)",
			L"Unicode(UTF-7)",
		    L"Latin I(ISO-8859-1/CP1252)",
		    L"Central/Eastern European(CP1250)",
		    L"Japanese(Shift JIS/CP932)",
    		L"Japanese(EUC)",
		    L"Simplified Chinese(GB2312/CP936)",
    		L"Traditional Chinese(CP950)",
    		L"Cyrillic(CP1251)",
    		L"Greek(CP1253)",
    		L"Turkish(CP1254)",
    		L"Hebrew(CP1255)",
    		L"Arabic(CP1256)",
    		L"Baltic(CP1257)",
    	};


		ShowWindow(m_Belge,SW_HIDE);
		ShowWindow(m_Asasiy,SW_HIDE);
		for(int i=0;i<20;i++)
		{
			SendMessage(m_comCodePage,CB_ADDSTRING,0x0, (LPARAM)oPage[i]);
		}
	}
	else
	{
		wchar_t *sPage[]={L"Unicode(UTF-8)",L"Unicode(UTF-16LE)"};
		for(int i=0;i<2;i++)
		{
			SendMessage(m_comCodePage,CB_ADDSTRING,0x0, (LPARAM)sPage[i]);
		}
		if(m_bBelge==TRUE)
		{
            SendMessage(m_Belge,BM_SETCHECK,(WPARAM)BST_CHECKED,0x0);
		}
		else
		{
		    SendMessage(m_Belge,BM_SETCHECK,(WPARAM)BST_UNCHECKED,0x0);
		}

		SendMessage(m_Asasiy,BM_SETCHECK,(WPARAM)BST_CHECKED,0x0);
	}
	SendMessage(m_comCodePage,CB_SETCURSEL ,(WPARAM)0, 0);
	if(m_HideSel)
	{
		ShowWindow(m_comCodePage,SW_HIDE);
		ShowWindow(GetDlgItem(hwnd,UFILEOPEN_CODELBL),SW_HIDE);
	}
	SetTexts(hwnd);
//	_mCaptionBut.UInstall(_mHInstance,GetParent(hwnd),KUNUPKA_SYSTEM);
	gUSetWindowCenter(GetParent(hwnd));
	return true;
}

void CUFileDialog::SetTexts(HWND hwnd)
{
	HWND tmp=GetDlgItem(hwnd,UFILEOPEN_CODELBL);
	SetWindowText(tmp,gUGetVal(L"MSG_UFILEOPEN_CODELBL"));
	SetWindowText(m_Belge,gUGetVal(L"MSG_UFILEOPEN_BELGISI"));
	SetWindowText(m_Asasiy,gUGetVal(L"MSG_UFILEOPEN_ASASIRAYON"));
}

int CUFileDialog::UGetCodePage()
{
	return m_CodePage;
}

BOOL CUFileDialog::UGetBelge()
{
	return m_bBelge;
}
BOOL CUFileDialog::UGetAsasiy()
{
	return m_bAsasiy;
}

void CUFileDialog::OnBnClickedAsasirayon()
{
	UINT ret=SendMessage(m_Asasiy,BM_GETCHECK,0x0,0x0);
	if(ret==BST_CHECKED)
	{
		this->m_bAsasiy=TRUE;
	}
	else if(ret==BST_UNCHECKED)
	{
		this->m_bAsasiy=FALSE;
	}
}

void CUFileDialog::OnBnClickedBelgisi()
{
	UINT ret=SendMessage(m_Belge,BM_GETCHECK,0x0,0x0);
	if(ret==BST_CHECKED)
	{
		this->m_bBelge=TRUE;
	}
	else if(ret==BST_UNCHECKED)
	{
		this->m_bBelge=FALSE;
	}
}

void CUFileDialog::OnCbnSelchangeCode()
{
	int index=SendMessage(m_comCodePage,CB_GETCURSEL ,0x0, 0x0);
	if(this->m_Open==TRUE)
	{
		switch(index)
		{
			case 0:
				this->m_CodePage=CP_ACP;
				break;
			case 1:
				this->m_CodePage=CP_BOGHDA;
				break;
			case 2:
				this->m_CodePage=CP_WEIDOS;
				break;
			case 3:
				this->m_CodePage=CP_WEIWIN;
				break;
			case 4:
				this->m_CodePage=CP_UTF16LE;
				break;
			case 5:
				this->m_CodePage=CP_UTF16BE;
				break;
			case 6:
				this->m_CodePage=CP_UTF8;
				break;
			case 7:
				this->m_CodePage=CP_UTF7;
				break;
			case 8:
				this->m_CodePage=CP_1252;
				break;
			case 9:
				this->m_CodePage=CP_1250;
				break;
			case 10:
				this->m_CodePage=CP_932;
				break;
			case 11:
				this->m_CodePage=CP_JEUC;
				break;
			case 12:
				this->m_CodePage=CP_936;
				break;
			case 13:
				this->m_CodePage=CP_950;
				break;
			case 14:
				this->m_CodePage=CP_1251;
				break;
			case 15:
				this->m_CodePage=CP_1253;
				break;
			case 16:
				this->m_CodePage=CP_1254;
				break;
			case 17:
				this->m_CodePage=CP_1255;
				break;
			case 18:
				this->m_CodePage=CP_1256;
				break;
			case 19:
				this->m_CodePage=CP_1257;
				break;
		}
	}
	else
	{
		switch(index)
		{
			case 0:
				this->m_CodePage=CP_UTF8;
				break;
			default:
				this->m_CodePage=CP_UTF16LE;
				break;
		}
	}
}

UINT CUFileDialog::UShow(HINSTANCE _gHInstance,HWND _ghWnd, BOOL HideCharSet)
{
		m_HideSel=HideCharSet;
		_mHInstance=_gHInstance;
		::ZeroMemory(&m_ofn, sizeof(OPENFILENAMEEX));
		m_ofn.lStructSize = sizeof (OPENFILENAME);
		m_ofn.hwndOwner = _ghWnd;
		m_ofn.lpstrFilter =m_Filter;
		m_ofn.nMaxCustFilter = 256;
		m_ofn.nFilterIndex = 0;
		m_ofn.lpstrFile = m_FileName;
		m_ofn.nMaxFile = MAX_PATH;
		m_ofn.Flags = OFN_FILEMUSTEXIST|OFN_EXPLORER|OFN_ENABLETEMPLATE|OFN_ENABLEHOOK|OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT ;
		m_ofn.hInstance=_gHInstance;
		m_ofn.lpTemplateName=MAKEINTRESOURCE(IDD_UFILEOPEN);
		m_ofn.lpfnHook=UHookProc;
		if(m_Open)
		{
			m_ofn.lpstrTitle=gUGetVal(L"MSG_TITLEOPEN");
			return::GetOpenFileName(&m_ofn);
		}
		else
		{
			m_ofn.lpstrTitle=gUGetVal(L"MSG_TITLESAVE");
			return::GetSaveFileName(&m_ofn);
		}
}
wchar_t *CUFileDialog:: UGetFileName()
{
	wchar_t *p=m_FileName;
	return p;
}
