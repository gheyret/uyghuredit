#ifndef REGISTRYOPERATION_H
#define REGISTRYOPERATION_H 1
#include <windows.h>
#include "UCommon.h"
#include "ortaq.h"

#define UYGHUREDITKEY   L"Software\\Kenjisoft\\Uyghuredit2"
#define KEY_CONFIG         L"Config"
#define KEY_IZLAR         L"Izlar"

class CRegistryOperation
{
private:
	BOOL Open(HKEY htopKey, wchar_t *subkey,PHKEY hKey);
	void SetStrVal(HKEY htopKey, wchar_t *Item ,wchar_t *val);
	void SetByteVal(HKEY hKey, wchar_t *Item ,LPBYTE val,int len  );
	void Close(HKEY hKey);
	BOOL Exist(HKEY htopKey, wchar_t *subkey);
public:

	BOOL SetSettings(LPUEDIT Data);
	BOOL GetSettings(LPUEDIT Data);

	BOOL SetIzlar(LPIZLAR Data);
	BOOL GetIzlar(LPIZLAR Data);

	CRegistryOperation();
	virtual ~CRegistryOperation();
	void Associate();
};
#endif
