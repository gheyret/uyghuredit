#include "RegistryOperation.h"

CRegistryOperation::CRegistryOperation()
{
}

void CRegistryOperation::Associate()
{
	wchar_t *dis=L"UyghurEdit File";
	wchar_t *extName=L".uut";

	wchar_t *Doc=L"UyghurEdit.Doc";
	wchar_t *defIcon=L"UyghurEdit.Doc\\DefaultIcon";
	wchar_t *shell=L"UyghurEdit.Doc\\shell\\open\\command";

	wchar_t progName[MAX_PATH];
	GetModuleFileName(NULL,progName,MAX_PATH);
	wchar_t icon[MAX_PATH+20];
	wsprintf(icon,L"%s,%d",progName,1);

	if(Exist(HKEY_CLASSES_ROOT,extName)) return;

	HKEY hKey;
	if(Open(HKEY_CLASSES_ROOT,extName,&hKey)==FALSE) return;
	SetStrVal(hKey,NULL,Doc);
	Close(hKey);

	if(Open(HKEY_CLASSES_ROOT,Doc,&hKey)==FALSE) return;
	SetStrVal(hKey,NULL,dis);
	Close(hKey);

	if(Open(HKEY_CLASSES_ROOT,defIcon,&hKey)==FALSE) return;
	SetStrVal(hKey,NULL,icon);
	Close(hKey);

	if(Open(HKEY_CLASSES_ROOT,shell,&hKey)==FALSE) return;
	wsprintf(icon,L"%s \"%c%d\"",progName,L'%',1);
	SetStrVal(hKey,NULL,icon);
	Close(hKey);

}


CRegistryOperation::~CRegistryOperation()
{

}

BOOL CRegistryOperation::Open(HKEY htopKey, wchar_t *subkey,PHKEY hKey)
{
	BOOL ret=TRUE;
    DWORD dwDisposition;
	LONG res=RegCreateKeyEx(htopKey, subkey, 0, L"", REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, hKey, &dwDisposition );
	if(res!=ERROR_SUCCESS)
		ret=FALSE;
	return ret;
}

BOOL CRegistryOperation::Exist(HKEY htopKey, wchar_t *subkey)
{
	BOOL ret=FALSE;
	HKEY hKey;
	LONG res=RegOpenKeyEx(htopKey, subkey,0x0,KEY_ALL_ACCESS,&hKey);
	if(res==ERROR_SUCCESS)
	{
		RegCloseKey(hKey);
		ret=TRUE;
	}
	return ret;
}


void CRegistryOperation::SetStrVal(HKEY hKey, wchar_t *Item ,wchar_t *val  )
{
	DWORD dwSize=(wcslen(val)+1)*2;
    RegSetValueEx(hKey, Item, 0, REG_SZ, (CONST BYTE *)val, dwSize );
}

void CRegistryOperation::SetByteVal(HKEY hKey, wchar_t *Item ,LPBYTE val,int len  )
{
    RegSetValueEx(hKey, Item, 0, REG_BINARY, (CONST BYTE *)val, (DWORD)len);
}


void CRegistryOperation::Close(HKEY hKey)
{
	RegCloseKey(hKey);
}

BOOL CRegistryOperation::GetSettings(LPUEDIT pFont)
{
	BOOL ret=TRUE;
	HKEY hTop;
	LONG re;
	DWORD len=(DWORD)sizeof(UEDIT);
	DWORD type=REG_BINARY;
	if(Open(HKEY_CURRENT_USER,UYGHUREDITKEY,&hTop))
	{
		re=RegQueryValueEx(hTop,KEY_CONFIG,0,&type,(LPBYTE)pFont,&len);
		if(re!=ERROR_SUCCESS)
		{
			ret=FALSE;
		}
		Close(hTop);
	}
	else
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CRegistryOperation::SetSettings(LPUEDIT pFont)
{
	BOOL ret=TRUE;
	HKEY hTop;
	if(Open(HKEY_CURRENT_USER,UYGHUREDITKEY,&hTop))
	{
		this->SetByteVal(hTop,KEY_CONFIG,(LPBYTE)pFont,sizeof(UEDIT));
		Close(hTop);
	}
	else
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CRegistryOperation::GetIzlar(LPIZLAR Data)
{
	BOOL ret=TRUE;
	HKEY hTop;
	LONG re;
	DWORD len=(DWORD)sizeof(IZLAR);
	DWORD type=REG_BINARY;
	if(Open(HKEY_CURRENT_USER,UYGHUREDITKEY,&hTop))
	{
		re=RegQueryValueEx(hTop,KEY_IZLAR,0,&type,(LPBYTE)Data,&len);
		if(re!=ERROR_SUCCESS)
		{
			ret=FALSE;
		}
		Close(hTop);
	}
	else
	{
		ret=FALSE;
	}
	return ret;
}

BOOL CRegistryOperation::SetIzlar(LPIZLAR Data)
{
	BOOL ret=TRUE;
	HKEY hTop;
	if(Open(HKEY_CURRENT_USER,UYGHUREDITKEY,&hTop))
	{
		this->SetByteVal(hTop,KEY_IZLAR,(LPBYTE)Data,sizeof(IZLAR));
		Close(hTop);
	}
	else
	{
		ret=FALSE;
	}
	return ret;
}
