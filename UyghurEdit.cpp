/* Creation of a simple Windows API program */
#include <windows.h>
#include "UyghurEditMain.h"

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance,LPSTR lpszArgument,int nFunsterStil)
{
	UyghurEditMain main;
	int ret=-1;
	if(main.UInit(hThisInstance)==TRUE)
	{
		main.UShowWindow(nFunsterStil);
		ret=main.URun(lpszArgument);
	}
	return ret;
}

